#include "leak_detector.h"

#include "DvmhRegionInserter.h"
#include "../VerificationCode/verifications.h"
#include "DvmhRegions/RegionsMerger.h"


using namespace std;


#define DVMH_REG_RD 0
#define DVMH_REG_WT 1

typedef set<string> Calls;
typedef map<string, Calls> FuncsWithCalls;
typedef map<string, FuncsWithCalls> FuncsInfoByFile;

void DvmhRegionInserter::findEdgesForRegions(const vector<LoopGraph*> &loops)
{
    for (auto &loopNode : loops)
    {
        if (!hasLimitsToDvmhParallel(loopNode))
        {
            SgStatement* func_st = getFuncStat(loopNode->loop);
            string fun_name = func_st->symbol()->identifier();
            DvmhRegion *dvmhRegion = new DvmhRegion(loopNode, fun_name);
            // loopNode->inDvmhRegion = true;  // <-- propagation
            regions.push_back(dvmhRegion);
        }
        else if (loopNode->children.size() > 0)
            findEdgesForRegions(loopNode->children);
    }
}

bool DvmhRegionInserter::hasLimitsToDvmhParallel(const LoopGraph *loop) const
{
    bool hasDirective = false;
    if (loop->lineNum > 0 || (loop->lineNum < 0 && loop->altLineNum > 0 && loop->directive))
        hasDirective = (loop->loop->GetOriginal()->lexPrev()->variant() == DVM_PARALLEL_ON_DIR);

    return loop->hasGoto || loop->hasPrints || loop->hasImpureCalls || !loop->directive || !hasDirective;
}

void DvmhRegionInserter::insertRegionDirectives()
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

bool DvmhRegionInserter::isLoopParallel(const LoopGraph *loop) const
{
    auto prev_st = loop->loop->lexPrev();

    while (prev_st && isDVM_stat(prev_st))
    {
        if (prev_st->variant() == DVM_PARALLEL_ON_DIR)
            return true;
        prev_st = prev_st->lexPrev();
    }
    return false;
}

void DvmhRegionInserter::parFuncsInNode(LoopGraph *loop, bool isParallel)
{
    // check for parallel
    isParallel |= isLoopParallel(loop);

    // meat: save parallel calls
    if (isParallel)
    {
        for (auto& call : loop->calls)  // mark call as parallel
            parallel_functions[call.first] = loop->fileName;
        writesToArraysInParallelLoop.insert(loop->usedArraysWriteAll.begin(), loop->usedArraysWriteAll.end());
    }
    else    
        for (auto& nestedLoop : loop->children)
            parFuncsInNode(nestedLoop, isParallel);
}

void DvmhRegionInserter::updateParallelFunctions(const map<string, vector<LoopGraph*>> &loopGraphs, const map<string, vector<FuncInfo*>> &callGraphs)
{    
    for (auto& loopGraph : loopGraphs)
    {
        auto save = current_file->filename();

        if (SgFile::switchToFile(loopGraph.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        for (auto& loopNode : loopGraph.second)
        {
            bool isParallel = isLoopParallel(loopNode);
            parFuncsInNode(loopNode, isParallel);
        }

        if (SgFile::switchToFile(save) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    ArraySet newSet = writesToArraysInParallelLoop;
    for (auto& elem : writesToArraysInParallelLoop)
        getRealArrayRefs(elem, elem, newSet, arrayLinksByFuncCalls);
    writesToArraysInParallelLoop = newSet;

    //TODO: check this
    FuncsInfoByFile funcsInfo;
    for (auto &file : callGraphs)
    {
        funcsInfo[file.first] = FuncsWithCalls();

        for (auto &func : file.second)
        {
            funcsInfo[file.first][func->funcName] = Calls();

            for (auto &call : func->callsFrom)
                funcsInfo[file.first][func->funcName].insert(call);
        }

    }

    bool changes_done = true;
    while (changes_done)
    {
        changes_done = false;

        for (auto &funcs : parallel_functions)
        {
            auto file_name = funcs.second;
            auto calls = funcsInfo[file_name][funcs.first];

            for (auto &call : calls)
            {
                if (parallel_functions.find(call) == parallel_functions.end())
                {
                    parallel_functions[call] = file_name;
                    changes_done = true;
                }
            }
        }
    }
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

static void createExceptList(SgExpression *ex, set<string> &symbs)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            SgExpression* list = ex->lhs();
            while (list)
            {
                int listVar = list->lhs()->variant();
                if (listVar == ARRAY_REF)
                    symbs.insert(list->lhs()->symbol()->identifier());
                else
                    createExceptList(list->lhs(), symbs);
                list = list->rhs();
            }
        }
        else
        {
            createExceptList(ex->lhs(), symbs);
            createExceptList(ex->rhs(), symbs);
        }
    }
}

//TODO:
SgStatement* DvmhRegionInserter::processSt(SgStatement *st, const vector<ParallelRegion*>* regs)
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

        auto readBlocks = get_used_arrs_for_block(st, DVMH_REG_RD);
        auto writeBlocks = get_used_arrs_for_block(st, DVMH_REG_WT);

        insertActualDirective(block_dir, readBlocks, ACC_GET_ACTUAL_DIR, true);
        insertActualDirective(st->lastNodeOfStmt()->lexNext(), writeBlocks, ACC_ACTUAL_DIR, false);

        return st->lastNodeOfStmt()->lexNext();
    }

    // Skip useless
    const int var = st->variant();


    if (!isSgExecutableStatement(st) || isDVM_stat(st) ||
        var == ALLOCATE_STMT || var == DEALLOCATE_STMT || 
        st->lastNodeOfStmt() != st || isSPF_stat(st))
    {
        return st->lexNext();
    }

    // Skip operators out of parallel regions 
    if (regs && getAllRegionsByLine(*regs, st->fileName(), st->lineNumber()).size() == 0)
            return st->lexNext();

    //TODO: read and write !!!
    if (var != PROC_STAT && var != READ_STAT)
    {
        set<string> exceptSymbsForActual;
        if (var != WRITE_STAT)
            for (int z = 0; z < 3; ++z)
                createExceptList(st->expr(z), exceptSymbsForActual);

        //filtering by writes in DVMH regions
        auto readArrays = get_used_arrs(st, DVMH_REG_RD);
        ArraySet newReadArrays;
        for (auto& elem : readArrays)
        {
            ArraySet newSet;
            getRealArrayRefs(elem, elem, newSet, arrayLinksByFuncCalls);

            for (auto& orig : newSet)
                if (writesToArraysInParallelLoop.find(orig) != writesToArraysInParallelLoop.end())
                    newReadArrays.insert(elem);
        }

        insertActualDirective(st, newReadArrays, ACC_GET_ACTUAL_DIR, true, &exceptSymbsForActual);
    }

    if (var != PROC_STAT && var != WRITE_STAT)
    {
        set<string> exceptSymbsForActual;
        if (var != READ_STAT)
            for (int z = 0; z < 3; ++z)
                createExceptList(st->expr(z), exceptSymbsForActual);

        insertActualDirective(st->lexNext(), get_used_arrs(st, DVMH_REG_WT), ACC_ACTUAL_DIR, false, &exceptSymbsForActual);
    }
    return st->lexNext();
}

void DvmhRegionInserter::insertActualDirectives(const vector<ParallelRegion*>* regs)
{
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        // skip parallel funcs
        string func_name = st->symbol()->identifier();
        if (parallel_functions.find(func_name) != parallel_functions.end())
            continue;

        st = st->lexNext();
        while (st != lastNode && st != NULL && st->variant() != CONTAINS_STMT)
            st = processSt(st, regs);
    }
}

vector<SgExpression*> DvmhRegionInserter::getArrayList(Statement* start, Statement* end, bool left) const
{
    vector<SgExpression*> varList;
    if (start && end)
    {
        for (auto st = start->GetOriginal(); st != end->GetOriginal(); st = st->lexNext())
        {
            if (st->variant() == ASSIGN_STAT)
            {
                SgExpression* ref = (left ? st->expr(0) : st->expr(1));
                if (ref->variant() == ARRAY_REF)
                    varList.push_back(ref);
            }
        }
    }
    return varList;
}

void DvmhRegionInserter::insertDirectives(const vector<ParallelRegion*> *regs)
{
    __spf_print(1, "Find edges for regions\n");
    findEdgesForRegions(loopGraph);

    __spf_print(1, "Merging regions\n");
    auto merger = RegionsMerger(regions, rw_analyzer);
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
    insertActualDirectives(regs);

    if (regs)
    {
        __spf_print(1, "Insert actuals for arrays copying before and after parallelization areas\n");
        for (auto& area : *regs)
        {
            auto lines = area->GetLines(file->filename());
            if (lines)
            {
                for (auto& regLine : *lines)
                {
                    if (!regLine.isImplicit())
                    {
                        auto forActual = getArrayList(regLine.intervalBefore.first, regLine.intervalBefore.second, true);
                        auto forGetActual = getArrayList(regLine.intervalAfter.first, regLine.intervalAfter.second, false);
                        
                        Statement* forActualSt = regLine.intervalBefore.second;
                        Statement* forGetActualSt = regLine.intervalAfter.first;
                        
                        if (forActual.size())
                        {
                            checkNull(forActualSt, convertFileName(__FILE__).c_str(), __LINE__);
                            auto st = forActualSt->GetOriginal();
                            st->insertStmtBefore(*new SgStatement(ACC_ACTUAL_DIR, NULL, NULL, makeExprList(forActual)), *st->controlParent());
                        }
                        
                        if (forGetActual.size())
                        {
                            checkNull(forGetActualSt, convertFileName(__FILE__).c_str(), __LINE__);
                            auto st = forGetActualSt->GetOriginal();
                            st->insertStmtAfter(*new SgStatement(ACC_GET_ACTUAL_DIR, NULL, NULL, makeExprList(forGetActual)), *st->controlParent());
                        }
                    }
                }
            }
        }
    }
}

void DvmhRegionInserter::insertActualDirective(SgStatement *st, const ArraySet &arraySet, int variant, bool moveComments, const set<string>* exceptSymbs)
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

        if (exceptSymbs)
            if (exceptSymbs->find(arrayName) != exceptSymbs->end())
                continue;
        list.push_back(new SgVarRefExp(findSymbolOrCreate(file, arrayName)));
    }
    if (list.size() == 0)
        return;
        
    if (variant == ACC_GET_ACTUAL_DIR)
    {
        auto prev = st->lexPrev();
        //filter get_actual list with previuos actual
        if (prev && prev->variant() == ACC_ACTUAL_DIR)
        {
            SgExpression* ex = prev->expr(0);
            set<SgSymbol*> prevActual;
            while (ex)
            {
                prevActual.insert(ex->lhs()->symbol());
                ex = ex->rhs();
            }

            vector<SgExpression*> listNew;
            for (auto& elem : list)
            {
                if (prevActual.find(elem->symbol()) == prevActual.end())
                    listNew.push_back(elem);
            }
            list = listNew;

            if (list.size() == 0)
                return;
        }
    }
    else if (variant == ACC_ACTUAL_DIR)
    {
        auto prev = st->lexPrev();
        if (prev && prev->variant() == ASSIGN_STAT)
        {
            // actualizing only left part of assign
            list.clear();
            list.push_back(prev->expr(0)->copyPtr());

            //check for ranges
            SgExpression* arrayList = list.back();
            if (arrayList)
            {
                SgExpression* list = arrayList->lhs();
                if (list && list->variant() == EXPR_LIST)
                    if (list->lhs() && list->lhs()->variant() == DDOT)
                        if (list->lhs()->lhs() && list->lhs()->lhs()->variant() == DDOT)
                            list->setLhs(list->lhs()->lhs());
            }
        }
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

ArraySet DvmhRegionInserter::symbs_to_arrs(set<SgSymbol*> symbols) const
{
    set<DIST::Array*> arrs;

    for (auto& symbol : symbols)
    {
        DIST::Array* arr = getArrayFromDeclarated(declaratedInStmt(symbol), symbol->identifier());
        arrs.insert(arr);
    }
    return arrs;
}

ArraySet DvmhRegionInserter::get_used_arrs(SgStatement* st, int usage_type) const
{
    VarUsages st_usages = rw_analyzer.get_usages(st);
    set<SgSymbol*> st_reads, st_writes;
    if (st_usages.is_undefined())    
        st_reads = st_writes = st_usages.get_all({ VAR_TYPE::VAR_DISTR_ARR, VAR_TYPE::VAR_ARR });
    else 
    {
        st_reads = st_usages.get_reads({ VAR_TYPE::VAR_DISTR_ARR, VAR_TYPE::VAR_ARR });
        st_writes = st_usages.get_writes({ VAR_TYPE::VAR_DISTR_ARR, VAR_TYPE::VAR_ARR });
    }

    if (usage_type == DVMH_REG_RD)
        return symbs_to_arrs(st_reads);
    else if (usage_type == DVMH_REG_WT)
        return symbs_to_arrs(st_writes);
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

ArraySet DvmhRegionInserter::get_used_arrs_for_block(SgStatement* st, int usage_type) const
{
    ArraySet usages;
    SgStatement *end = st->lastNodeOfStmt()->lexNext();

    while (st != end && st != NULL)
    {
        // Skip regions
        if (st->variant() == ACC_REGION_DIR)
            st = skipDvmhRegionInterval(st);

        // Skip DVM dirs
        if (isDVM_stat(st))
        {
            st = st->lexNext();
            continue;
        }

        ArraySet st_usages = get_used_arrs(st, usage_type);
        usages.insert(st_usages.begin(), st_usages.end());
        st = st->lexNext();
    }
    return usages;
}
