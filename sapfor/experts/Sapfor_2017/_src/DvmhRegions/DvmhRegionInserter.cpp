#include "leak_detector.h"

#include "DvmhRegionInserter.h"
#include "../VerificationCode/verifications.h"
#include "DvmhRegions/RegionsMerger.h"

using namespace std;

#define DVMH_REG_RD 0
#define DVMH_REG_WT 1

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

void DvmhRegionInsertor::findEdgesForRegions(const vector<LoopGraph*> &loops)
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

DvmhRegionInsertor::DvmhRegionInsertor(SgFile *curFile, const vector<LoopGraph*> &curLoopGraph) : file(curFile), loopGraph(curLoopGraph) { }

DvmhRegionInsertor::DvmhRegionInsertor(
    SgFile *curFile, 
    const vector<LoopGraph*> &curLoopGraph,
    const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays
) : file(curFile), loopGraph(curLoopGraph)
{ 
    auto array_access = createMapOfArrayAccess(declaratedArrays);
    array_usage = ArrayUsageFactory::from_array_access(array_access, true);
}

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
    for (SgStatement* st = start; st != start->lastNodeOfStmt(); st = st->lexNext())
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

static string getNameByUse(SgStatement *place, const string &varName, const string &locName)
{
    SgStatement* func = getFuncStat(place);
    if (func == NULL)
        return varName;
    else
    {
        set<string> useMod;
        map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUse;
        map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUseOnly;

        fillInfo(func, useMod, modByUse, modByUseOnly);
        SgStatement* cp = func->controlParent();
        if (isSgProgHedrStmt(cp)) // if function in contains region
            fillInfo(cp, useMod, modByUse, modByUseOnly);

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
                    if (modSt == NULL && useM == "dvmh_template_mod")
                        continue;

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

static SgStatement* skipDvmhRegionInterval(SgStatement *start)
{
    if (start->variant() != ACC_REGION_DIR)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    auto st = start;    
    while (st->variant() != ACC_END_REGION_DIR)
        st = st->lexNext();
    return st->lexNext();
}

SgStatement* DvmhRegionInsertor::processSt(SgStatement *st)
{
    if (st == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    // Skip regions
    if (st->variant() == ACC_REGION_DIR)
        return skipDvmhRegionInterval(st);

    // Actualization before remote dir and parallel loops blocks
    if (st->variant() == DVM_REMOTE_ACCESS_DIR || st->variant() == DVM_PARALLEL_ON_DIR || st->variant() == LOGIF_NODE)
    {
        SgStatement* block_dir = st;
        while (isDVM_stat(st))
            st = st->lexNext();

        auto readBlocks = array_usage->get_op_arrs_for_block(st, true, true, DVMH_REG_RD);
        auto writeBlocks = array_usage->get_op_arrs_for_block(st, true, true, DVMH_REG_WT);

        insertActualDirective(block_dir, readBlocks, ACC_GET_ACTUAL_DIR, true);
        insertActualDirective(st->lastNodeOfStmt()->lexNext(), writeBlocks, ACC_ACTUAL_DIR, false);

        return st->lastNodeOfStmt()->lexNext();
    }

    // Skip useless
    if (!isSgExecutableStatement(st) || isDVM_stat(st))
        return st->lexNext();

    insertActualDirective(st, array_usage->get_op_arrs(st, DVMH_REG_RD), ACC_GET_ACTUAL_DIR, true);
    insertActualDirective(st->lexNext(), array_usage->get_op_arrs(st, DVMH_REG_WT), ACC_ACTUAL_DIR, false);

    if (st->variant() == LOGIF_NODE)
        return st->lexNext()->lexNext();
    else
        return st->lexNext();
}

void DvmhRegionInsertor::insertActualDirectives() 
{
    int funcNum = file->numberOfFunctions();
    // TODO: if func is parallel -> skip
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        st = st->lexNext();
        while (st != lastNode && st != NULL && st->variant() != CONTAINS_STMT)
            st = processSt(st);
    }
}

void DvmhRegionInsertor::insertDirectives()
{
    __spf_print(1, "Find edges for regions\n");
    findEdgesForRegions(loopGraph);

    __spf_print(1, "Merging regions\n");
    auto merger = RegionsMerger(regions);
    regions = merger.mergeRegions();

    for (auto& elem : regions)
    {
        for (auto& loop : elem->getLoops())
        {
            loop->inDvmhRegion = 1;
            loop->propagateDvmhRegion(1);
        }
    }

    __spf_print(1, "Insert regions\n");
    insertRegionDirectives();

     __spf_print(1, "Insert actuals\n");
    insertActualDirectives();
}

void DvmhRegionInsertor::insertActualDirective(SgStatement *st, const ArraySet &arraySet, int variant, bool moveComments)
{
    if (!st || (variant != ACC_ACTUAL_DIR && variant != ACC_GET_ACTUAL_DIR) || (arraySet.size() == 0))
        return;

    SgStatement *actualizingSt = new SgStatement(variant);

    vector<SgExpression*> list;
    for (auto &arr : arraySet) 
    {
        string arrayName = arr->GetShortName();
        if (arr->GetLocation().first == DIST::l_MODULE)
            arrayName = getNameByUse(st, arrayName, arr->GetLocation().second);

        list.push_back(new SgVarRefExp(findSymbolOrCreate(file, arrayName)));
    }
    actualizingSt->setExpression(0, makeExprList(list));

    st->insertStmtBefore(*actualizingSt, *st->controlParent());

    if (moveComments)
    {
        if (st->comments())
        {
            actualizingSt->addComment(st->comments());
            st->delComments();
        }
    }
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion(LoopGraph *loopNode, const string &fun_name) : fun_name(fun_name), rw_info(loopNode->loop)
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

std::unordered_set<SgSymbol*> DvmhRegion::get_modified()  // may raise NotImplemented
{
    return rw_info.get_modified();
}

std::unordered_set<SgSymbol*> DvmhRegion::get_read()  // may raise NotImplemented
{
    return rw_info.get_read();
}

void DvmhRegion::append(DvmhRegion& region)
{
    for (auto& loop : region.getLoops())
        this->addLoop(loop);

    rw_info.update(region.rw_info);
}

static set<SgSymbol *> getSymbolsFromExpression(SgExpression *exp) 
{
    set<SgSymbol *> result;

    if (exp)
    {
        if (exp->variant() == ARRAY_REF) 
        {
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

    int start = 0;
    if (st->variant() == ASSIGN_STAT)
    {
        start = 1;
        SgExpression* exp = st->expr(0);
        // find write: check modified var 
        if (st->expr(0)->variant() == ARRAY_REF)
        {
            SgSymbol* symbol = exp->symbol();
            DIST::Array*arr = getArrayFromDeclarated(declaratedInStmt(symbol), symbol->identifier());

            if (!arr->GetNonDistributeFlag()) // if array's distributed add it
                write.insert(exp->symbol());
        }
        
        // find reads
        set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(exp->lhs());
        read.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());

        symbolsUsedInExpression = getSymbolsFromExpression(exp->rhs());
        read.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
    }

    // find read
    for (int i = start; i < 3; ++i) 
    {
        if (st->expr(i)) 
        {
            set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(st->expr(i));
            read.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
        }
    }

    return make_tuple(read, write);
}

unique_ptr<ArrayUsage> ArrayUsageFactory::from_array_access(
        map<DIST::Array*, DIST::ArrayAccessInfo*> arrays_with_access,
        bool dist_only
        )
{
    UsageByFile usage_by_file;

    for (auto& arr : arrays_with_access)
    {
        DIST::Array* arr_ptr = arr.first;
        if (dist_only && arr_ptr->GetNonDistributeFlag())
            continue;

        for (auto& file : arr.second->GetAllAccessInfo())
        {
            for (auto& line : file.second) 
            {
                for (auto& usage : line.second)
                {
                    if (usage.underFunctionPar != -1 && !isIntrinsicFunctionName(usage.fName.c_str()))
                        continue;

                    string file_name = file.first;
                    int line_num = line.first;

                    if (usage_by_file.find(file_name) == usage_by_file.end())
                        usage_by_file[file_name] = UsageByLine();
                    if (usage_by_file[file_name].find(line_num) == usage_by_file[file_name].end())
                        usage_by_file[file_name][line_num] = ReadWrite();
                    
                    if (usage.type == 0)
                        usage_by_file[file_name][line_num].read.insert(arr_ptr);
                    if (usage.type == 1)
                        usage_by_file[file_name][line_num].write.insert(arr_ptr);
                }          
            }
        }
    }

    return unique_ptr<ArrayUsage>(new ArrayUsage(usage_by_file));
}

ArraySet ArrayUsage::get_op_arrs(SgStatement* st, int type)
{
    string f_name = st->fileName();
    if (usages_by_file.find(f_name) != usages_by_file.end() &&
        usages_by_file[f_name].find(st->lineNumber()) != usages_by_file[f_name].end())
    {
        if (type == 0)
            return usages_by_file[f_name][st->lineNumber()].read;
        else
            return usages_by_file[f_name][st->lineNumber()].write;
    }

    return ArraySet(); 
}

ArraySet ArrayUsage::get_op_arrs_for_block(SgStatement* st, bool ignore_regions, bool ignore_dvm, int type)
{
    auto usages = ArraySet();
    SgStatement *end = st->lastNodeOfStmt()->lexNext();

    while (st != end && st != NULL)
    {
        // Skip regions
        if (ignore_regions && st->variant() == ACC_REGION_DIR)
            st = skipDvmhRegionInterval(st);

        // Skip DVM dirs
        if (ignore_dvm && isDVM_stat(st))
        {
            st = st->lexNext();
            continue;
        }

        ArraySet st_usages = get_op_arrs(st, type);
        usages.insert(st_usages.begin(), st_usages.end());
        st = st->lexNext();
    }
    return usages;
}
