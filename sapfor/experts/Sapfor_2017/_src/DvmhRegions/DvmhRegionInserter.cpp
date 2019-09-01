#include "leak_detector.h"
/*
 * DvmhDvmhRegionIsertor.cpp
 *
 *  Created on: May 14, 2018
 *      Author: vladislav
 */

#include "DvmhRegionInserter.h"

using namespace std;

void DvmhRegionInsertor::printFuncName(SgStatement* st)
{
    if (st->variant() == PROG_HEDR)
    {
        SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
        cout << "Program: " << progH->symbol()->identifier() << endl;
    }
    else if (st->variant() == PROC_HEDR)
    {
        SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
        cout << "Procedure: " << procH->symbol()->identifier() << endl;
    }
    else if (st->variant() == FUNC_HEDR)
    {
        SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
        cout << "Function: " << funcH->symbol()->identifier() << endl;
    }
}

// TODO: init first and last statements
void DvmhRegionInsertor::findEdgesForRegions(const vector<LoopGraph*> &loops) // here as link
{
    for (auto &loopNode : loops)
    {
        if (!hasLimitsToDvmhParallel(loopNode))
        {
            SgStatement* func_st = getFuncStat(loopNode->loop);
            string fun_name = func_st->symbol()->identifier();
            DvmhRegion *dvmhRegion = new DvmhRegion(loopNode, fun_name);
            regions.push_back(dvmhRegion);
        }
        else if (loopNode->children.size() > 0)
            findEdgesForRegions(loopNode->children);
    }
}

bool DvmhRegionInsertor::hasLimitsToDvmhParallel(const LoopGraph *loop) const
{
    bool hasDirective = false;
    if (loop->lineNum > 0 || (loop->lineNum < 0 && loop->altLineNum > 0))
        hasDirective = (loop->loop->GetOriginal()->lexPrev()->variant() == DVM_PARALLEL_ON_DIR);

    return loop->hasGoto || loop->hasPrints || loop->hasImpureCalls || !loop->directive || !hasDirective;
}

void DvmhRegionInsertor::insertRegionDirectives()
{
    for (auto &region : regions)
    {
        if (region->getLoops().size() == 0)
            continue;

        SgStatement *regionStartSt = new SgStatement(ACC_REGION_DIR);

        SgStatement *statementBefore = region->getFirstSt()->lexPrev();
        if (!statementBefore || statementBefore->variant() != DVM_PARALLEL_ON_DIR) 
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        //move comments before
        if (statementBefore->comments())
        {
            regionStartSt->setComments(statementBefore->comments());
            statementBefore->delComments();
        }
        statementBefore->insertStmtBefore(*regionStartSt, *statementBefore->controlParent());

        SgStatement *regionEndSt = new SgStatement(ACC_END_REGION_DIR);
        SgStatement *lastStOfTheLoop = region->getLastSt();
        lastStOfTheLoop->insertStmtAfter(*regionEndSt, *region->getFirstSt()->controlParent());
    }
}

// checks loop node itself, doesn't check its children
LoopCheckResults DvmhRegionInsertor::checkLoopForPurenessAndIO(LoopGraph *loopNode, const map<string, FuncInfo*> &allFuncs)
{
    LoopCheckResults loopCheckResults;

    for (auto &nameAndLineOfFuncCalled : loopNode->calls)
    {
        FuncInfo *calledFuncInfo = NULL;

        auto it = allFuncs.find(nameAndLineOfFuncCalled.first);
        if (it != allFuncs.end())
            calledFuncInfo = it->second;

        if (!calledFuncInfo)
        {
            if (isIntrinsicFunctionName(nameAndLineOfFuncCalled.first.c_str()))
                continue;
            else
            { // if funcInfo was not found assume func to be impure
                loopCheckResults.hasImpureCalls = true;
                loopCheckResults.usesIO = true;
                break;
            }
        }

        if (!calledFuncInfo->isPure) 
            loopCheckResults.hasImpureCalls = true;

        if (calledFuncInfo->usesIO())
            loopCheckResults.usesIO = true;

        if (loopCheckResults.usesIO && loopCheckResults.hasImpureCalls)
            break;
    }

    return loopCheckResults;
}

DvmhRegionInsertor::DvmhRegionInsertor(SgFile *curFile, const vector<LoopGraph*> &curLoopGraph)
    : file(curFile), loopGraph(curLoopGraph)
{ }

LoopCheckResults DvmhRegionInsertor::updateLoopNode(LoopGraph *loop, const map<string, FuncInfo*> &allFuncs)
{
    LoopCheckResults loopChecks = checkLoopForPurenessAndIO(loop, allFuncs);
    bool hasImpureCalls = loopChecks.hasImpureCalls;
    bool usesIO = loopChecks.usesIO;

    for (auto &nestedLoop : loop->children) 
    {
        loopChecks = updateLoopNode(nestedLoop, allFuncs);
        hasImpureCalls |= loopChecks.hasImpureCalls;
        usesIO |= loopChecks.usesIO;
    }

    loop->hasImpureCalls = hasImpureCalls;
    loop->hasPrints |= usesIO;

    return LoopCheckResults(loop->hasPrints, loop->hasImpureCalls);
}

void DvmhRegionInsertor::updateLoopGraph(const map<string, FuncInfo*> &allFuncs)
{
    for (auto &loopNode : loopGraph)
        updateLoopNode(loopNode, allFuncs);
}


/*
    1. ���������� ������ ������ ������ �������
    2. ������ ���������� � ����� ������� ���������
    3. ���� ����� ��������� ���-�� ����:
        �) ��� ��������� �����-����
        �) ���� ����������� ���������� -- ��������� ������ (����� ���������, ���� ������ �� ������������ � ����. �������)
        �) ���� ����� ������� -- ������������ �� ������ �� ����������������� � ���� �������*
*/

static bool SymbDefinedIn(SgSymbol* var, SgStatement* st)
{
    return st->variant() == ASSIGN_STAT && st->expr(0)->variant() == ARRAY_REF && st->expr(0)->symbol()->identifier() == var->identifier();
}

// Finds the closest variable's defenition (test only)
// static map<SymbolKey, set<SgExpression*> > dummyDefenitions(SgStatement* st)
// {
//  map<SymbolKey, set<SgExpression*> > result;

//  set<SgSymbol*> usedSymbols = getUsedSymbols(st);

//  for (auto& var : usedSymbols)
//  {
//      SgStatement* prev = st->lexPrev();

//      set<SgExpression*> defs;
//      while (prev)
//      {
//          if (SymbDefinedIn(var, prev)) {
//              defs.insert(prev->expr(1));
//              break;
//          }

//          prev = prev->lexPrev();
//      }

//      result[SymbolKey(var, false)] = defs;
//  }

//  return result;
// }

void DvmhRegionInsertor::insertActualDirectives() 
{
    //TODO: rewrite
#if 0
    int funcNum = file->numberOfFunctions();
    RDKeeper rd = RDKeeper(file);

    for (auto const& defsByStatement : rd.defsByStatement)
    {
        SgStatement* st = defsByStatement.first;
        StDefs st_defs = defsByStatement.second;

        DvmhRegion* region = getContainingRegion(st);

        vector<SgSymbol*> toActualise;
        for (auto const& elem : st_defs) 
        {
            SgSymbol* symbol = elem.first;
            set<SgStatement*> defs = elem.second;
            /*
            // DEBUG
            cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
            st->unparsestdout();
            cout << symbol.getVarName() + ": " << endl;
            for (auto &def : defs) {
                if (def) {
                    def->unparsestdout();
                }
            }
            cout << "********************" << endl;
            // END OF DEBUG
            */
            if (region) 
            {
                // Searching for defenition not in region
                bool symbolDeclaredInSequentPart = false;
                for (auto& def : defs) 
                {
                    auto saveName = current_file->filename();

                    if (!def->switchToFile())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    DvmhRegion* containingRegion = getContainingRegion(def);
                    if (!containingRegion) 
                    {
                        symbolDeclaredInSequentPart = true;
                        break;
                    }

                    if (SgFile::switchToFile(saveName) == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
                if (symbolDeclaredInSequentPart)
                    region->addToActualisation(symbol);
            }
            else 
            {
                // Searching for defenition in region
                bool symbolDeclaredInRegion = false;
                for (auto& def : defs) 
                {
                    auto saveName = current_file->filename();

                    if (!def->switchToFile())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    const DvmhRegion* containingRegion = getContainingRegion(def);
                    if (containingRegion) 
                    {
                        symbolDeclaredInRegion = true;
                        break;
                    }

                    if (SgFile::switchToFile(saveName) == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
                if (symbolDeclaredInRegion)
                    toActualise.push_back(symbol);
            }
        }
        insertActualDirective(st, toActualise, ACC_GET_ACTUAL_DIR, true);
    }
#endif

    //TODO: improve and optimize
    for (auto& region : regions)
    {
        for (auto& loop : region->getLoops())
        {
            for (auto& array : loop->usedArrays)
            {
                region->addToActualisation(array->GetShortName());
                if (loop->usedArraysWrite.find(array) != loop->usedArraysWrite.end())
                    region->addToActualisationAfter(array->GetShortName());
            }
        }
    }

    for (auto& region : regions)
    {
        if (region->getLoops().size())
        {
            insertActualDirective(region->getFirstSt()->lexPrev()->lexPrev(), region->getActualisation(), ACC_ACTUAL_DIR, true, false);
            insertActualDirective(region->getLastSt()->lexNext(), region->getActualisationAfter(), ACC_GET_ACTUAL_DIR, false, false);
        }
    }
}

static bool compareByStart(const DvmhRegion *a, const DvmhRegion *b)
{
    if (a->getLoops().size() < 1 || b->getLoops().size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return a->getLoops()[0]->loop->lineNumber() < b->getLoops()[0]->loop->lineNumber();
}

static bool areNeighbours(const DvmhRegion *first, const DvmhRegion *second)
{
    set<int> toSkip = { DVM_PARALLEL_ON_DIR };
    SgStatement* mediumSt = first->getLastSt()->lexNext();
    while (toSkip.count(mediumSt->variant())) // skip statements which don't prevent from merging
        mediumSt = mediumSt->lexNext();

    SgStatement* firstSt = second->getFirstSt();
    return mediumSt->fileName() == firstSt->fileName() && mediumSt->lineNumber() == firstSt->lineNumber();
}

void DvmhRegionInsertor::mergeRegions()
{
    if (regions.size() < 2)
        return;

    sort(regions.begin(), regions.end(), compareByStart);

    vector<DvmhRegion*> newRegions;
    DvmhRegion *newRegion = new DvmhRegion();
    DvmhRegion *regionPrev = regions[0];

    bool isFirst = true;
    for (auto& loop : regions[0]->getLoops())
        newRegion->addLoop(loop);

    for (auto& region : regions)
    {
        if (newRegion->getFunName() == "" && region->getLoops().size() > 0) 
        {
            SgStatement* func_st = getFuncStat(region->getLoops()[0]->loop);
            string fun_name = func_st->symbol()->identifier();
            newRegion->setFunName(fun_name);
        }
        //printf("Merge number %d\n", i++);
        if (isFirst) // skip first region
        {
            isFirst = false;
            continue;
        }

        // logic of intermediate derectives here, in perspective they can be accumulated and moved
        if (!areNeighbours(regionPrev, region))
        {
            newRegions.push_back(newRegion);
            newRegion = new DvmhRegion();
        }

        regionPrev = region;
        for (auto& loop : region->getLoops())
            newRegion->addLoop(loop);
        for (auto& s : region->getActualisation())
            newRegion->addToActualisation(s);
        for (auto& s : region->getActualisationAfter())
            newRegion->addToActualisationAfter(s);
    }
    newRegions.push_back(newRegion);

    for (auto& old : regions)
        delete old;
    regions.clear();

    regions = newRegions;
}

void DvmhRegionInsertor::insertDirectives()
{
    __spf_print(1, "Find edges for regions\n");
    findEdgesForRegions(loopGraph);

    __spf_print(1, "Merging regions\n");
    mergeRegions();

    __spf_print(1, "Insert regions\n");
    insertRegionDirectives();

     __spf_print(1, "Insert actuals\n");
    insertActualDirectives();

    //vector<DvmhRegion*> l_regions;
    //for (auto &region : regions)
    //  l_regions.push_back(&region);

    //__spf_print(1, "Constructing Abstract Graph\n");
    //AFlowGraph graph = AFlowGraph(file, l_regions);
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion(LoopGraph *loopNode, const string &fun_name) : fun_name(fun_name)
{
    loops.push_back(loopNode);
}

bool DvmhRegion::isInRegion(SgStatement *st) 
{
    if (!st)
        return false;

    int line = st->lineNumber();
    bool inLoop = false;
    for (auto& loop : loops)
        inLoop |= (st->fileName() == loop->fileName && line >= loop->lineNum && line < loop->lineNumAfterLoop);
    return inLoop;
}

DvmhRegion* DvmhRegionInsertor::getContainingRegion(SgStatement *st) 
{
    for (auto& region : regions) 
        if (region->isInRegion(st)) 
            return region;
    return NULL;
}

void DvmhRegionInsertor::insertActualDirective(SgStatement *st, const set<string> &symbols, int varinat, bool before, bool empty)
{
    if (!st || (varinat != ACC_ACTUAL_DIR && varinat != ACC_GET_ACTUAL_DIR) || (!empty && (symbols.size() == 0)))
        return;

    SgStatement *actualizingSt = new SgStatement(varinat);

    SgExprListExp *t = new SgExprListExp();
    for (auto &symbol : symbols) 
    {
        SgExpression *expr = new SgVarRefExp(findSymbolOrCreate(current_file, symbol));
        t->append(*expr);
    }

    if (symbols.size())
        actualizingSt->setExpression(0, t->rhs());
    else
        actualizingSt->setExpression(0, t);

    if (before)
    {
        st->insertStmtBefore(*actualizingSt, *st->controlParent());
        if (st->comments())
        {
            actualizingSt->addComment(st->comments());
            st->delComments();
        }
    }
    else
        st->insertStmtAfter(*actualizingSt, *st->controlParent());
}

SgStatement* DvmhRegion::getFirstSt() const 
{
    if (loops.size() < 1) 
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return loops.front()->loop;
}

SgStatement* DvmhRegion::getLastSt() const
{
    if (loops.size() < 1) 
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return loops.back()->loop->lastNodeOfStmt();
}

//TODO: need to remove or rewrite RDKeeper 
RDKeeper::RDKeeper(SgFile *file) 
{
    // Build CFG
    SgStatement *st = file->functions(0);
    GraphsKeeper* graphsKeeper = GraphsKeeper::getGraphsKeeper();
    ControlFlowGraph* CGraph = graphsKeeper->buildGraph(st)->CGraph;

    // Find gen for every bb

    // Find defs for every statement
}

set<SgSymbol *> RDKeeper::getSymbolsFromExpression(SgExpression *exp) 
{
    set<SgSymbol *> result;

    if (exp)
    {
        if (exp->variant() == ARRAY_REF) {
            SgSymbol* symbol = exp->symbol();
            DIST::Array*arr = getArrayFromDeclarated(declaratedInStmt(symbol), symbol->identifier());

            if (!arr->GetNonDistributeFlag()) // if array's distributed add it
                result.insert(exp->symbol());
        }

        set<SgSymbol *> lhsSymbols = getSymbolsFromExpression(exp->lhs());
        set<SgSymbol *> rhsSymbols = getSymbolsFromExpression(exp->rhs());

        result.insert(lhsSymbols.begin(), lhsSymbols.end());
        result.insert(rhsSymbols.begin(), rhsSymbols.end());
    }

    return result;
}

set<SgSymbol *> RDKeeper::getUsedSymbols(SgStatement* st) 
{
    set<SgSymbol *> result;

    // ignore not executable statements
    if (!isSgExecutableStatement(st) || st->variant() == CONTAINS_STMT || isSgControlEndStmt(st) || isDVM_stat(st) || st->variant() == FOR_NODE)
        return result;

    for (int i = 0; i < 3; ++i) {
        if (st->expr(i)) {
            set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(st->expr(i));
            result.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
        }
    }

    return result;
}