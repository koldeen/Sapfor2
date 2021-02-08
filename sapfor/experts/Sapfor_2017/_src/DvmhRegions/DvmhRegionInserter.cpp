#include "leak_detector.h"

#include "DvmhRegionInserter.h"
#include "../VerificationCode/verifications.h"
#include "DvmhRegions/RegionsMerger.h"
#include "../Transformations/function_purifying.h"

using namespace std;


#define DVMH_REG_RD 0
#define DVMH_REG_WT 1

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

    // save parallel calls
    if (isParallel)
    {
        for (auto& call : loop->calls)  // mark call as parallel
        {
            auto it = allFunctions.find(call.first);
            if (it == allFunctions.end())
            {
                if (!isIntrinsicFunctionName(call.first.c_str()))
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            else
                parallel_functions.insert(it->second);
        }
        writesToArraysInParallelLoops.insert(loop->usedArraysWriteAll.begin(), loop->usedArraysWriteAll.end());
        usedArraysInParallelLoops.insert(loop->usedArraysAll.begin(), loop->usedArraysAll.end());
    }
    else    
        for (auto& nestedLoop : loop->children)
            parFuncsInNode(nestedLoop, isParallel);
}

void DvmhRegionInserter::updateParallelFunctions(const map<string, vector<LoopGraph*>> &loopGraphs)
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

    ArraySet newSet = writesToArraysInParallelLoops;
    for (auto& elem : writesToArraysInParallelLoops)
        getRealArrayRefs(elem, elem, newSet, arrayLinksByFuncCalls);
    writesToArraysInParallelLoops = newSet;

    newSet = usedArraysInParallelLoops;
    for (auto& elem : usedArraysInParallelLoops)
        getRealArrayRefs(elem, elem, newSet, arrayLinksByFuncCalls);
    usedArraysInParallelLoops = newSet;

    bool changes_done = true;
    while (changes_done)
    {
        changes_done = false;
        set<FuncInfo*> newList;
        for (auto& funcPair : allFunctions)
        {
            FuncInfo* func = funcPair.second;
            for (auto& callsTo : func->callsTo)
            {
                if (parallel_functions.find(callsTo) != parallel_functions.end() && 
                    parallel_functions.find(func) == parallel_functions.end())
                {
                    newList.insert(func);
                    changes_done = true;
                }
            }
        }

        for (auto& newElem : newList)
            parallel_functions.insert(newElem);
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
        if (isSgProgHedrStmt(cp) || cp->variant() == MODULE_STMT) // if function in contains region
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

ArraySet DvmhRegionInserter::excludePrivates(const ArraySet& block) const
{
    ArraySet tmp;
    for (auto& array : block)
    {
        set<DIST::Array*> realArrayRefs;
        getRealArrayRefs(array, array, realArrayRefs, arrayLinksByFuncCalls);

        bool isNotPrivate = true;
        for (auto& elem : realArrayRefs)
            if (elem->IsPrivateInLoop())
                isNotPrivate = false;

        if (!array->IsOmpThreadPrivate() && isNotPrivate)
            tmp.insert(array);
    }
    return tmp;
}

ArraySet DvmhRegionInserter::applyUseFilter(const ArraySet& block, const set<DIST::Array*>& filter) const
{
    ArraySet newBlock;
    for (auto& elem : block)
    {
        ArraySet newSet;
        getRealArrayRefs(elem, elem, newSet, arrayLinksByFuncCalls);

        for (auto& orig : newSet)
            if (filter.find(orig) != filter.end())
                newBlock.insert(elem);
    }
    return newBlock;
}

static bool hasLoopsWithDir(LoopGraph* loop)
{
    bool retVal = loop->directive;
    for (auto& ch : loop->children)
        retVal |= hasLoopsWithDir(ch);
    return retVal;
}

//TODO:
SgStatement* DvmhRegionInserter::processSt(SgStatement *st, const vector<ParallelRegion*>* regs)
{
    if (st == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (st->variant() < 0)
        return st->lastNodeOfStmt()->lexNext();

    // Skip regions
    if (st->variant() == ACC_REGION_DIR)
        return skipDvmhRegionInterval(st);

    bool forBlock = false;
    if (st->variant() == FOR_NODE && st->lineNumber() > 0)
    {
        auto it = loopGraphMap.find(st->lineNumber());
        if (it != loopGraphMap.end())
        {
            LoopGraph* loop = it->second;
            if (hasLoopsWithDir(loop) == false)
            {
                set<string> outCalls;
                for (auto& elem : loop->calls)
                    outCalls.insert(elem.first);

                if (checkOutCalls(outCalls) == false)
                    forBlock = true;
                else //TODO
                    ;
            }
        }
    }

    // Actualization before remote dir, parallel loops blocks, loops blocks
    if (st->variant() == DVM_REMOTE_ACCESS_DIR || 
        st->variant() == DVM_PARALLEL_ON_DIR || 
        st->variant() == LOGIF_NODE ||
        forBlock)
    {
        if (st->variant() == LOGIF_NODE && ((SgLogIfStmt*)st)->body() &&
            (((SgLogIfStmt*)st)->body()->variant() == DEALLOCATE_STMT ||
             ((SgLogIfStmt*)st)->body()->variant() == ALLOCATE_STMT))
        {
            return st->lexNext();
        }

        SgStatement* block_dir = st;
        while (isDVM_stat(st))
            st = st->lexNext();

        auto readBlocks = get_used_arrs_for_block(st, DVMH_REG_RD);
        auto writeBlocks = get_used_arrs_for_block(st, DVMH_REG_WT);

        readBlocks = excludePrivates(readBlocks);
        writeBlocks = excludePrivates(writeBlocks);

        ArraySet unite;        
        std::merge(readBlocks.begin(), readBlocks.end(), writeBlocks.begin(), writeBlocks.end(), std::inserter(unite, unite.end()));

        insertActualDirective(block_dir, unite, ACC_GET_ACTUAL_DIR, true);
        insertActualDirective(st->lastNodeOfStmt()->lexNext(), writeBlocks, ACC_ACTUAL_DIR, false);

        return st->lastNodeOfStmt()->lexNext();
    }

    // Skip useless
    const int var = st->variant();
    bool skipGetActualIfProcCall = false;
    bool skipActualIfProcCall = false;

    set<string> exceptSymbsForGetActual, exceptSymbsForActual;
    if (var == PROC_STAT)
    {
        const char* procName = st->symbol()->identifier();
        if (isIntrinsicFunctionName(procName) == 0)
        {
            skipGetActualIfProcCall = skipActualIfProcCall = true;
        }
    }    

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
    if (!skipGetActualIfProcCall && var != READ_STAT)
    {
        if (var != WRITE_STAT)
            for (int z = 0; z < 3; ++z)
                createExceptList(st->expr(z), exceptSymbsForGetActual);
                
        auto readArrays = get_used_arrs(st, DVMH_REG_RD);

        //filtering by writes in DVMH regions
        readArrays = applyUseFilter(readArrays, writesToArraysInParallelLoops);
        readArrays = excludePrivates(readArrays);

        insertActualDirective(st, readArrays, ACC_GET_ACTUAL_DIR, true, &exceptSymbsForGetActual);
    }

    if (!skipActualIfProcCall && var != WRITE_STAT)
    {
        if (var != READ_STAT)
            for (int z = 0; z < 3; ++z)
                createExceptList(st->expr(z), exceptSymbsForActual);

        auto writeArrays = get_used_arrs(st, DVMH_REG_WT);
        writeArrays = excludePrivates(writeArrays);
        //filtering by use in DVMH regions
        writeArrays = applyUseFilter(writeArrays, usedArraysInParallelLoops);
        insertActualDirective(st->lexNext(), writeArrays, ACC_ACTUAL_DIR, false, &exceptSymbsForActual);
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
        bool needToSkip = false;
        for (auto& func : parallel_functions)
            if (func->funcPointer->GetOriginal()->thebif == st->thebif)
                needToSkip = true;

        if (needToSkip)
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
            bool needToGetBefore = false;
            if (arrayList)
            {
                SgExpression* listA = arrayList->lhs();

                if (listA && listA->variant() == EXPR_LIST)
                    if (listA->lhs() && listA->lhs()->variant() == DDOT)
                        if (listA->lhs()->lhs() && listA->lhs()->lhs()->variant() == DDOT)
                        {
                            arrayList->setLhs(NULL);
                            needToGetBefore = true;
                        }
            }

            if (needToGetBefore)
            {
                SgStatement* getBefore = new SgStatement(ACC_GET_ACTUAL_DIR);
                getBefore->setExpression(0, makeExprList(list));
                prev->insertStmtBefore(*getBefore, *prev->controlParent());
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

static string getInterfaceBlock(SgStatement* func, const FuncParam& pars)
{
    string oldFile = current_file->filename();
    if (!func->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    auto copy = duplicateProcedure(func, NULL, false, false, false, true);

    const set<string> ident(pars.identificators.begin(), pars.identificators.end());

    //remove all exec
    SgStatement* st = copy->lexNext();
    SgStatement* last = copy->lastNodeOfStmt();
    vector<SgStatement*> toExtract;
    while (st != last)
    {
        if (isDVM_stat(st) || isSPF_stat(st))
        {
            if (st->variant() != ACC_ROUTINE_DIR)
            {
                SgStatement* next = st->lexNext();
                st->extractStmt();
                st = next;
            }
            else
                st = st->lexNext();
        }
        else if (isSgExecutableStatement(st))
        {
            SgStatement* next = st->lastNodeOfStmt();
            if (next != last)
                next = next->lexNext();
            toExtract.push_back(st);
            st = next;
        }
        else
            st = st->lexNext();
    }  

    //remove unused declarations
    st = copy->lexNext();
    while (st != last)
    {
        if (st->variant() == VAR_DECL 
            || st->variant() == VAR_DECL_90
            || st->variant() == DIM_STAT
            || st->variant() == INTENT_STMT)
        {
            SgExpression* list = st->expr(0);
            vector<SgExpression*> newList;
            while (list)
            {
                if (ident.find(list->lhs()->symbol()->identifier()) != ident.end())
                    newList.push_back(list->lhs());
                list = list->rhs();
            }

            if (newList.size() == 0)
            {
                SgStatement* next = st->lexNext();
                toExtract.push_back(st);
                st = next;
                continue;
            }
            else
                st->setExpression(0, makeExprList(newList));
        }
        else
            toExtract.push_back(st);

        if (st->variant() == CONTAINS_STMT)
            break;
        st = st->lexNext();
    }

    for (auto& elem : toExtract)
        elem->extractStmt();

    string retVal = copy->unparse();

    if (SgFile::switchToFile(oldFile) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return retVal;
}

static void insertInterface(SgStatement* func, const string& iface)
{
    string oldFile = current_file->filename();
    if (!func->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement* st = func->lexNext();
    SgStatement* last = func->lastNodeOfStmt();
    while (st != last)
    {
        if (isSgExecutableStatement(st))
            break;
        st = st->lexNext();
    }
    SgStatement* ifaceBlock = new SgStatement(INTERFACE_STMT);
    addControlEndToStmt(ifaceBlock->thebif);

    ifaceBlock->setlineNumber(st->lineNumber());
    ifaceBlock->setFileName(st->fileName());
    st->insertStmtBefore(*ifaceBlock, *st->controlParent());    
    ifaceBlock->lastNodeOfStmt()->addComment(iface.c_str());

    if (SgFile::switchToFile(oldFile) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void insertRoutine(SgStatement* func)
{
    string oldFile = current_file->filename();
    if (!func->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    
    SgStatement* st = func->lexNext();
    SgStatement* last = func->lastNodeOfStmt();
    bool has = false;
    while (st != last)
    {
        if (st->variant() == ACC_ROUTINE_DIR)
        {
            has = true;
            break;                
        }
        st = st->lexNext();
    }

    if (has == false)
    {
        st = func->lexNext();
        st->insertStmtBefore(*new SgStatement(ACC_ROUTINE_DIR), *st->controlParent());
    }

    if (SgFile::switchToFile(oldFile) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

}

static bool isPure(SgStatement* func)
{
    string oldFile = current_file->filename();
    if (!func->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    bool retVal = ((func->symbol()->attributes() & PURE_BIT) != 0);

    if (SgFile::switchToFile(oldFile) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return retVal;
}

void DvmhRegionInserter::createInterfaceBlock()
{
    for (auto& parF : parallel_functions)
    {        
        for (auto& callTo : parF->callsTo)
        {
            if (callTo->fileName != parF->fileName)
            {
                if (callTo->interfaceBlocks.find(parF->funcName) == callTo->interfaceBlocks.end() 
                    && parF->funcParams.countOfPars > 0 
                    && isPure(parF->funcPointer->GetOriginal()))
                {
                    insertRoutine(parF->funcPointer->GetOriginal());
                    callTo->interfaceBlocks[parF->funcName] = parF;
                    insertInterface(callTo->funcPointer, getInterfaceBlock(parF->funcPointer->GetOriginal(), parF->funcParams));
                }
            }
        }
    }
}

void DvmhRegionInserter::createInterfaceBlockForOutCalls(FuncInfo* func)
{
    for (auto& callFrom : func->callsFromV)
    {
        if (func->interfaceBlocks.find(callFrom->funcName) == func->interfaceBlocks.end()
            && callFrom->funcParams.countOfPars > 0
            && isPure(callFrom->funcPointer->GetOriginal()))
        {
            if (callFrom->fileName != func->fileName)
                insertRoutine(func->funcPointer->GetOriginal());

            func->interfaceBlocks[callFrom->funcName] = callFrom;
            insertInterface(func->funcPointer, getInterfaceBlock(callFrom->funcPointer->GetOriginal(), callFrom->funcParams));            
        }
    }
}