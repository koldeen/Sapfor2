#include "leak_detector.h"
/*
 * DvmhDvmhRegionIsertor.cpp
 *
 *  Created on: May 14, 2018
 *      Author: vladislav
 */

#include "DvmhRegionInserter.h"
#include "../VerificationCode/verifications.h"

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
    if (loop->lineNum > 0 || (loop->lineNum < 0 && loop->altLineNum > 0 && loop->directive))
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
                loopCheckResults.linesOfIO.push_back(nameAndLineOfFuncCalled.second);
            }
            continue;
        }

        if (!calledFuncInfo->isPure) 
            loopCheckResults.hasImpureCalls = true;

        if (calledFuncInfo->usesIO())
        {
            loopCheckResults.usesIO = true;
            loopCheckResults.linesOfIO.push_back(nameAndLineOfFuncCalled.second);
        }
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

    if (loopChecks.linesOfIO.size() && usesIO)
        for (auto& elem : loopChecks.linesOfIO)
            loop->linesOfIO.push_back(elem);

    for (auto &nestedLoop : loop->children) 
    {
        loopChecks = updateLoopNode(nestedLoop, allFuncs);
        hasImpureCalls |= loopChecks.hasImpureCalls;
        usesIO |= loopChecks.usesIO;
    }

    loop->hasImpureCalls |= hasImpureCalls;
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

static void findByUse(map<string, vector<pair<SgSymbol*, SgSymbol*>>> &modByUse, const string& varName, 
                      const string& locName, vector<string> &altNames)
{
    for (auto& elem : modByUse)
    {
        if (elem.first == locName)
        {
            for (auto& byUse : elem.second)
            {
                SgSymbol* toCmp = byUse.second ? byUse.second : byUse.first;
                checkNull(toCmp, convertFileName(__FILE__).c_str(), __LINE__);
                if (toCmp->identifier() == varName)
                    altNames.push_back(byUse.first->identifier());
            }
        }
    }
}

static void fillInfo(SgStatement *start,
                     set<string> &useMod,
                     map<string, vector<pair<SgSymbol*, SgSymbol*>>> &modByUse,
                     map<string, vector<pair<SgSymbol*, SgSymbol*>>> &modByUseOnly)
{
    for (SgStatement* st = start; st; st = st->lexNext())
    {
        if (isSgExecutableStatement(st))
            break;
        if (st->variant() == CONTAINS_STMT)
            break;
        if (st != start && (st->variant() == PROC_HEDR || st->variant() == FUNC_HEDR))
            break;
        fillUseStatement(st, useMod, modByUse, modByUseOnly);
    }
}

static SgStatement* findModWithName(const vector<SgStatement*> &modules, const string &name)
{
    for (auto& elem : modules)
        if (elem->variant() == MODULE_STMT)
            if (elem->symbol()->identifier() == name)
                return elem;
    return NULL;
}

static string getNameByUse(SgStatement *loop, const string &varName, const string &locName)
{
    SgStatement* func = getFuncStat(loop);
    if (func == NULL)
        return varName;
    else
    {
        set<string> useMod;
        map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUse;
        map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUseOnly;

        fillInfo(func, useMod, modByUse, modByUseOnly);
        set<string> useModDone;
        bool needRepeat = true;

        vector<SgStatement*> modules;
        findModulesInFile(func->getFile(), modules);

        while (needRepeat)
        {
            needRepeat = false;
            set<string> newUseMod;
            for (auto& useM : useMod)
            {
                if (useModDone.find(useM) == useModDone.end())
                {
                    auto modSt = findModWithName(modules, useM);
                    checkNull(modSt, convertFileName(__FILE__).c_str(), __LINE__);
                    fillInfo(modSt, newUseMod, modByUse, modByUseOnly);
                    useModDone.insert(useM);
                }
            }

            for (auto& newU : newUseMod)
            {
                if (useModDone.find(newU) == useModDone.end())
                {
                    useModDone.insert(newU);
                    needRepeat = true;
                }
            }
        }

        vector<string> altNames;        
        findByUse(modByUse, varName, locName, altNames);
        findByUse(modByUseOnly, varName, locName, altNames);
        
        if (altNames.size() == 0)
            return varName;
        else if (altNames.size() >= 1)
        {
            set<string> setAlt(altNames.begin(), altNames.end());
            return *setAlt.begin();
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
}

void DvmhRegionInsertor::insertActualDirectives() 
{
    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        st->lexNext();
        while (st != lastNode)
        {
            // Skip regions
            DvmhRegion* region = getRegionByStart(st);
            if (region)
            {
                st = region->getLastSt();
                continue;
            }

            // Skip useless (TODO: make it work)
            if (!isSgExecutableStatement(st) || st->variant() == PROG_HEDR || st->variant() == FUNC_HEDR || st->variant() == PROC_HEDR)
                st->lexNext();

            // TODO: process loop separatly (how to get LoopGraph by statement?)
            set<SgSymbol *> used_for_read, used_for_write;
            tie(used_for_read, used_for_write) = getUsedDistributedArrays(st);

            // // debug
            // printf("********\n");
            // st->unparsestdout();
            // printf("_______\n");
            // for (auto& s : used)
            // {
            //     printf("%s", s->identifier());
            // }
            // printf("********\n");
            insertActualDirective(st, used_for_read, ACC_GET_ACTUAL_DIR, true);
            insertActualDirective(st, used_for_write, ACC_ACTUAL_DIR, false);

            st = st->lexNext();
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
}

void DvmhRegionInsertor::insertActualDirective(SgStatement *st, const set<SgSymbol *> &symbols, int varinat, bool before, bool empty)
{
    if (!st || (varinat != ACC_ACTUAL_DIR && varinat != ACC_GET_ACTUAL_DIR) || (!empty && (symbols.size() == 0)))
        return;

    SgStatement *actualizingSt = new SgStatement(varinat);

    SgExprListExp *t = new SgExprListExp();
    for (auto &symbol : symbols) 
    {
        SgExpression *expr = new SgVarRefExp(findSymbolOrCreate(current_file, symbol->identifier()));
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

DvmhRegion* DvmhRegionInsertor::getRegionByStart(SgStatement *st) const
{
    for (auto& region : regions)
    {
        SgStatement *region_start = region->getFirstSt();
        if (st->id() == region_start->id()) 
            return region;
    }

    return NULL;
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion(LoopGraph *loopNode, const string &fun_name) : fun_name(fun_name)
{
    loops.push_back(loopNode);
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

static set<SgSymbol *> getSymbolsFromExpression(SgExpression *exp) 
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

/* Returns tuple (READ, WRITE) of used symbols in the statement */
static tuple<set<SgSymbol *>, set<SgSymbol *>> getUsedDistributedArrays(SgStatement* st) 
{
    set<SgSymbol *> read, write;

    // ignore not executable statements
    if (!isSgExecutableStatement(st) || st->variant() == CONTAINS_STMT || isSgControlEndStmt(st) || isDVM_stat(st) || st->variant() == FOR_NODE)
        return make_tuple(read, write);

    // find write
    write = getSymbolsFromExpression(st->expr(0));

    // find read
    for (int i = 1; i < 3; ++i) {
        if (st->expr(i)) {
            set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(st->expr(i));
            read.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
        }
    }

    return make_tuple(read, write);
}