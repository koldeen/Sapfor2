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
        for (auto &call : loop->calls)  // mark call as parallel
            parallel_functions[call.first] = loop->fileName;

    // recursion: check nested loops, TODO: check if recursion is required
    for (auto& nestedLoop : loop->children)
        parFuncsInNode(nestedLoop, isParallel);
}

void DvmhRegionInserter::updateParallelFunctions(const vector<LoopGraph*> &loopGraphs, const map<string, vector<FuncInfo*>> &callGraphs)
{    
    for (auto& loopNode : loopGraphs)
    {
        bool isParallel = isLoopParallel(loopNode);
        parFuncsInNode(loopNode, isParallel);
    }

    auto funcsInfo = FuncsInfoByFile();
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

SgStatement* DvmhRegionInserter::processSt(SgStatement *st)
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
    if (!isSgExecutableStatement(st) || isDVM_stat(st) || var == ALLOCATE_STMT || var == DEALLOCATE_STMT)
        return st->lexNext();

    insertActualDirective(st, get_used_arrs(st, DVMH_REG_RD), ACC_GET_ACTUAL_DIR, true);
    insertActualDirective(st->lexNext(), get_used_arrs(st, DVMH_REG_WT), ACC_ACTUAL_DIR, false);

    if (st->variant() == LOGIF_NODE)
        return st->lexNext()->lexNext();
    else
        return st->lexNext();
}

void DvmhRegionInserter::insertActualDirectives() 
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
            st = processSt(st);
    }
}

void DvmhRegionInserter::insertDirectives()
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
    insertActualDirectives();
}

void DvmhRegionInserter::insertActualDirective(SgStatement *st, const ArraySet &arraySet, int variant, bool moveComments)
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
    
        st_reads = st_writes = st_usages.get_all(VAR_DISTR_ARR);
    else 
    {
        st_reads = st_usages.get_reads(VAR_DISTR_ARR);
        st_writes = st_usages.get_writes(VAR_DISTR_ARR);
    }

    if (usage_type == DVMH_REG_RD)
        return symbs_to_arrs(st_reads);
    else
        return symbs_to_arrs(st_writes);
}

ArraySet DvmhRegionInserter::get_used_arrs_for_block(SgStatement* st, int usage_type) const
{
    auto usages = ArraySet();
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
