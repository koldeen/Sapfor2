#include "../Utils/leak_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "dvm.h"
#include "ParRegions.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops.h"
#include "../Distribution/Distribution.h"
#include "../ExpressionTransform/expr_transform.h"

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::map;
using std::set;
using std::wstring;

extern void createMapLoopGraph(map<int, LoopGraph*> &sortedLoopGraph, const vector<LoopGraph*> *loopGraph);

static map<string, int> regionIdByName;
static map<string, ParallelRegion*> regionByName;

static int regionIdConuter = 1;

void clearRegionStaticData()
{
    regionIdByName.clear();
    regionByName.clear();
    regionIdConuter = 1;
}


static inline void extendRegionInfo(SgStatement *st, map<string, pair<Statement*, Statement*>> &startEnd, map<string, pair<int, int>> &lines_, bool addEndSt = false)
{
    auto it_st_en = startEnd.find(st->fileName());
    if (it_st_en == startEnd.end())
    {
        startEnd.insert(it_st_en, make_pair(st->fileName(), make_pair<Statement*, Statement*>(new Statement(st), NULL)));
        lines_[st->fileName()] = make_pair(st->lineNumber(), 0);
    }
    else
    {
        if (addEndSt)
        {
            Statement *toAdd = new Statement(st);
            it_st_en->second.second = toAdd;
        }
        lines_[st->fileName()].second = st->lineNumber();
    }
}

static void findFuncCalls(SgExpression *ex, set<string> &calls, const string &prefix, const map<string, FuncInfo*>& mapFuncs)
{
    if (ex == NULL)
        return;

    if (ex->variant() == FUNC_CALL)
    {
        string fullName = ex->symbol()->identifier();
        //check contains
        if (mapFuncs.find(prefix + fullName) != mapFuncs.end())
            fullName = prefix + fullName;
        calls.insert(fullName);
    }

    findFuncCalls(ex->lhs(), calls, prefix, mapFuncs);
    findFuncCalls(ex->rhs(), calls, prefix, mapFuncs);
}

static inline SgStatement* getParentStat(SgStatement *st)
{
    if (!st)
        return NULL;

    SgStatement *iterator = st;

    while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
        iterator = iterator->controlParent();

    while (iterator->controlParent()->variant() == PROG_HEDR || iterator->controlParent()->variant() == PROC_HEDR || iterator->controlParent()->variant() == FUNC_HEDR)
        iterator = iterator->controlParent();

    return iterator;
}

static void updateRegionInfo(SgStatement *st, map<string, pair<Statement*, Statement*>> &startEnd, map<string, pair<int, int>> &lines_,
                             set<string> &funcCallFromReg, const map<string, FuncInfo*> &mapFuncs)
{    
    string containsPrefix = "";
    SgStatement *st_ps = getParentStat(st);
    const string funcName = st_ps->symbol()->identifier(); // DEBUG
    if (st_ps->variant() == PROC_HEDR || st_ps->variant() == PROG_HEDR || st_ps->variant() == FUNC_HEDR)
        containsPrefix = st_ps->symbol()->identifier() + string(".");

    extendRegionInfo(st, startEnd, lines_);
    if (st->variant() == PROC_STAT)
    {
        string fullName = st->symbol()->identifier();
        //check contains
        if (mapFuncs.find(containsPrefix + fullName) != mapFuncs.end())
            fullName = containsPrefix + fullName;
        funcCallFromReg.insert(fullName);
    }

    for (int z = 0; z < 3; ++z)
        findFuncCalls(st->expr(z), funcCallFromReg, containsPrefix, mapFuncs);
}

static void fillArrayNamesInReg(set<string> &usedArrayInRegion, SgExpression *exp)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF && OriginalSymbol(exp->symbol()))
            usedArrayInRegion.insert(OriginalSymbol(exp->symbol())->identifier());

        fillArrayNamesInReg(usedArrayInRegion, exp->lhs());
        fillArrayNamesInReg(usedArrayInRegion, exp->rhs());
    }
}

static bool filterUserDirectives(set<string> &usedArrayInRegion, vector<Statement*> &userDvmDirs, vector<Statement*> &userDvmDirsF)
{
    vector<Statement*> filtered;
    bool changed = false;
    for (auto &distr : userDvmDirs)
    {
        set<string> usedIndir;
        for (int i = 0; i < 3; ++i)
            fillArrayNamesInReg(usedIndir, distr->GetOriginal()->expr(i));

        bool ok = false;
        for (auto &elem : usedIndir)
        {
            if (usedArrayInRegion.find(elem) != usedArrayInRegion.end())
            {
                ok = true;
                break;
            }
        }

        if (ok)
        {
            usedArrayInRegion.insert(usedIndir.begin(), usedIndir.end());
            userDvmDirsF.push_back(distr);
            changed = true;
        }
        else
            filtered.push_back(distr);
    }
    userDvmDirs = filtered;

    return changed;
}

static void filterUserDirectives(ParallelRegion *currReg, set<string> usedArrayInRegion, vector<Statement*> userDvmDistrDirs,
                                 vector<Statement*> userDvmAlignDirs, vector<Statement*> userDvmShadowDirs)
{
    vector<Statement*> userDvmDistrDirsF;
    vector<Statement*> userDvmAlignDirsF;
    vector<Statement*> userDvmShadowDirsF;

    bool changed = false;
    do
    {
        changed = false;

        bool ret = filterUserDirectives(usedArrayInRegion, userDvmDistrDirs, userDvmDistrDirsF);
        changed = changed || ret;

        ret = filterUserDirectives(usedArrayInRegion, userDvmAlignDirs, userDvmAlignDirsF);
        changed = changed || ret;

        ret = filterUserDirectives(usedArrayInRegion, userDvmShadowDirs, userDvmShadowDirsF);
        changed = changed || ret;
                
    } while (changed);

    currReg->AddUserDirectives(userDvmDistrDirsF, DVM_DISTRIBUTE_DIR);
    currReg->AddUserDirectives(userDvmAlignDirsF, DVM_ALIGN_DIR);
    currReg->AddUserDirectives(userDvmShadowDirsF, DVM_SHADOW_DIR);
}

static void setExplicitFlag(const string &name, const map<string, FuncInfo*> &mapFuncs)
{
    auto it = mapFuncs.find(name);
    if (it != mapFuncs.end())
        it->second->inRegion = 1;
}

static void fillDvmDirs(SgStatement *st, vector<Statement*> &userDvmDistrDirs, vector<Statement*> &userDvmAlignDirs,
                        vector<Statement*> &userDvmShadowDirs, vector<Statement*> &userDvmRealignDirs, vector<Statement*> &userDvmRedistrDirs,
                        vector<Statement*>& userDvmRealignDirsDef, vector<Statement*>& userDvmRedistrDirsDef,
                        const bool &regionStarted, const map<int, LoopGraph*> &allLoopsInFile)
{
    switch (st->variant())
    {
    case DVM_VAR_DECL:
    {
        string unparsed = st->unparse();
        convertToLower(unparsed);
        if (unparsed.find("distribute") != string::npos)
            userDvmDistrDirs.push_back(new Statement(st));
        else if (unparsed.find("align") != string::npos)
            userDvmAlignDirs.push_back(new Statement(st));
    }
    break;
    case DVM_DISTRIBUTE_DIR:
        userDvmDistrDirs.push_back(new Statement(st));
        break;
    case DVM_ALIGN_DIR:
        userDvmAlignDirs.push_back(new Statement(st));
        break;
    case DVM_SHADOW_DIR:
        userDvmShadowDirs.push_back(new Statement(st));
        break;
    case DVM_REALIGN_DIR:
        if (regionStarted)
            userDvmRealignDirs.push_back(new Statement(st));
        userDvmRealignDirsDef.push_back(new Statement(st));
        break;
    case DVM_REDISTRIBUTE_DIR:
        if (regionStarted)
            userDvmRedistrDirs.push_back(new Statement(st));
        userDvmRedistrDirsDef.push_back(new Statement(st));
        break;
    case DVM_PARALLEL_ON_DIR:
        if (st->lexNext()->variant() == FOR_NODE)
        {
            SgForStmt* forStat = (SgForStmt*)(st->lexNext());
            auto it = allLoopsInFile.find(forStat->lineNumber());
            if (it != allLoopsInFile.end())
                it->second->userDvmDirective = new Statement(st);
        }
        break;
    default:
        break;
    }
}

static void checkForEmpty(SgStatement *start, SgStatement *end, vector<Messages>& messagesForFile)
{
    bool wasStarted = false;
    int lineStarted = -1;

    while (start != end)
    {
        if (start->variant() == CONTAINS_STMT)
            break;

        if (start->variant() == SPF_PARALLEL_REG_DIR)
        {
            wasStarted = true;
            lineStarted = start->lineNumber();
        }
        else if (start->variant() == SPF_END_PARALLEL_REG_DIR)
        {
            if (wasStarted)
            {
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"Empty parallel regions is forbidden.");
#ifdef _WIN32
                __spf_printToLongBuf(messageR, R151);
#endif
                messagesForFile.push_back(Messages(ERROR, lineStarted, messageR, messageE, 3021));
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }
        else
        {
            wasStarted = false;
            lineStarted = -1;
        }
        start = start->lexNext();
    }
}

void fillRegionLines(SgFile *file, vector<ParallelRegion*> &regions, vector<Messages>& messagesForFile, vector<LoopGraph*> *loops, vector<FuncInfo*> *funcs)
{
    map<string, FuncInfo*> mapFuncs;
    if (funcs)
        createMapOfFunc(*funcs, mapFuncs);

    //fill default
    ParallelRegion* defaultR = regions[0];
    pair<int, int> lines;
    //pair<SgStatement*, SgStatement*> startEndDef(NULL, NULL);
    {
        SgStatement* st = file->firstStatement();
        st = st->lexNext();
        lines = make_pair(st->lineNumber(), 0);
        //startEndDef.first = st;

        while (st)
        {
            st = st->lastNodeOfStmt();
            lines.second = st->lineNumber();
            //startEndDef.second = st;
            st = st->lexNext();
        }
    }
    defaultR->AddLines(lines, file->filename());

    map<int, LoopGraph*> allLoopsInFile;
    if (loops)
        createMapLoopGraph(allLoopsInFile, loops);

    //fill user's
    int funcNum = file->numberOfFunctions();
    string regionName = "";
    map<string, pair<Statement*, Statement*>> startEnd;
    map<string, pair<int, int>> lines_;
    set<string> funcCallFromReg;
    bool regionStarted = false;

    for (int i = 0; i < funcNum; ++i)
    {
        vector<Statement*> userDvmDistrDirs;
        vector<Statement*> userDvmAlignDirs;
        vector<Statement*> userDvmShadowDirs;
        vector<Statement*> userDvmRealignDirs;
        vector<Statement*> userDvmRedistrDirs;

        vector<Statement*> userDvmRealignDirsDef;
        vector<Statement*> userDvmRedistrDirsDef;

        set<string> usedArrayInRegion;

        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        string containsPrefix = "";
        SgStatement *st_cp = st->controlParent();
        if (st_cp->variant() == PROC_HEDR || st_cp->variant() == PROG_HEDR || st_cp->variant() == FUNC_HEDR)
            containsPrefix = st_cp->symbol()->identifier() + string(".");
        const string funcName = containsPrefix + file->functions(i)->symbol()->identifier();

        checkForEmpty(st, lastNode, messagesForFile);
        while (st != NULL && st != lastNode)
        {
            if (st->variant() == CONTAINS_STMT)
                break;

            SgStatement *prev = st->lexPrev();
            SgStatement *next = st->lexNext();

            if (prev && prev->variant() == SPF_PARALLEL_REG_DIR)
            {
                SgStatement *data = prev;

                regionStarted = true;
                regionName = data->symbol()->identifier();
                if (funcs)
                {
                    auto itFunc = mapFuncs.find(funcName);
                    if (itFunc != mapFuncs.end())
                    {
                        itFunc->second->inRegion = 3;
                        itFunc->second->callRegions.insert(0);
                    }
                }
            }

            if (next && next->variant() == SPF_END_PARALLEL_REG_DIR)
            {
                updateRegionInfo(st, startEnd, lines_, funcCallFromReg, mapFuncs);
                SgStatement *data = next;

                lines.second = data->lineNumber();
                regionStarted = false;

                if (regionName == "")
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                auto it = regionIdByName.find(regionName);
                ParallelRegion *currReg = NULL;
                if (it == regionIdByName.end())
                {
                    it = regionIdByName.insert(it, make_pair(regionName, regionIdConuter));
                    currReg = new ParallelRegion(regionIdConuter, regionName);
                    regions.push_back(currReg);
                    regionByName[regionName] = currReg;
                    regionName = "";
                    regionIdConuter++;
                }
                else
                    currReg = regionByName[regionName];

                if (currReg == NULL)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                extendRegionInfo(st, startEnd, lines_, true);
                for (auto itRegInfo = startEnd.begin(); itRegInfo != startEnd.end(); ++itRegInfo)
                    currReg->AddLines(lines_[itRegInfo->first], itRegInfo->first, &itRegInfo->second);

                for (auto &func : funcCallFromReg)
                    currReg->AddFuncCalls(func);

                filterUserDirectives(currReg, usedArrayInRegion, userDvmRedistrDirs, userDvmRealignDirs, userDvmShadowDirs);
                currReg->AddUserDirectives(userDvmRealignDirs, DVM_REALIGN_DIR);
                currReg->AddUserDirectives(userDvmRedistrDirs, DVM_REDISTRIBUTE_DIR);

                startEnd.clear();
                lines_.clear();
                funcCallFromReg.clear();

                userDvmRealignDirs.clear();
                userDvmRedistrDirs.clear();

                usedArrayInRegion.clear();
            }


            if (regionStarted)
            {
                updateRegionInfo(st, startEnd, lines_, funcCallFromReg, mapFuncs);
                for (int i = 0; i < 3; ++i)
                    fillArrayNamesInReg(usedArrayInRegion, st->expr(i));
            }

            fillDvmDirs(st, userDvmDistrDirs, userDvmAlignDirs, userDvmShadowDirs, userDvmRealignDirs, userDvmRealignDirs, userDvmRealignDirsDef, userDvmRealignDirsDef, regionStarted, allLoopsInFile);
            st = st->lexNext();
        }

        //for default
        defaultR->AddUserDirectives(userDvmDistrDirs, DVM_DISTRIBUTE_DIR);
        defaultR->AddUserDirectives(userDvmAlignDirs, DVM_ALIGN_DIR);
        defaultR->AddUserDirectives(userDvmShadowDirs, DVM_SHADOW_DIR);
        defaultR->AddUserDirectives(userDvmRealignDirsDef, DVM_REALIGN_DIR);
        defaultR->AddUserDirectives(userDvmRedistrDirsDef, DVM_REDISTRIBUTE_DIR);
    }

    vector<SgStatement*> modules;
    findModulesInFile(file, modules);
    regionStarted = false;

    for (auto& mod : modules)
    {
        vector<Statement*> userDvmDistrDirs;
        vector<Statement*> userDvmAlignDirs;
        vector<Statement*> userDvmShadowDirs;
        vector<Statement*> userDvmRealignDirs;
        vector<Statement*> userDvmRedistrDirs;

        vector<Statement*> userDvmRealignDirsDef;
        vector<Statement*> userDvmRedistrDirsDef;


        for (SgStatement* st = mod->lexNext(); st; st = st->lexNext())
        {
            if (isSgExecutableStatement(st))
                break;
            fillDvmDirs(st, userDvmDistrDirs, userDvmAlignDirs, userDvmShadowDirs, userDvmRealignDirs, userDvmRealignDirs, userDvmRealignDirsDef, userDvmRealignDirsDef, regionStarted, allLoopsInFile);
        }

        //for default
        defaultR->AddUserDirectives(userDvmDistrDirs, DVM_DISTRIBUTE_DIR);
        defaultR->AddUserDirectives(userDvmAlignDirs, DVM_ALIGN_DIR);
        defaultR->AddUserDirectives(userDvmShadowDirs, DVM_SHADOW_DIR);
        defaultR->AddUserDirectives(userDvmRealignDirsDef, DVM_REALIGN_DIR);
        defaultR->AddUserDirectives(userDvmRedistrDirsDef, DVM_REDISTRIBUTE_DIR);
    }
}

static void getAllLoops(vector<LoopGraph*> &loopGraph, vector<LoopGraph*> &loops)
{
    for (auto &elem : loopGraph)
        loops.push_back(elem);

    for (auto &elem : loopGraph)
        getAllLoops(elem->children, loops);
}

void fillRegionLinesStep2(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> &allFuncInfo, map<string, vector<LoopGraph*>> *loopGraph)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (int i = 0; i < regions.size(); ++i)
    {
        if (regions[i]->GetName() != "DEFAULT")
            for (auto &func : regions[i]->GetFuncCalls())
                setExplicitFlag(func, funcMap);        
    }

    for (int i = 0; i < regions.size(); ++i)
    {
        if (regions[i]->GetName() != "DEFAULT")
        {
            set<string> uniqFuncCalls;
            for (auto &elem : regions[i]->GetFuncCalls())
                uniqFuncCalls.insert(elem);

            bool wasChanged = 1;
            while (wasChanged)
            {
                wasChanged = 0;
                for (auto &uniqF : uniqFuncCalls)
                {
                    auto func = funcMap.find(uniqF);
                    if (func != funcMap.end())
                    {
                        for (auto &calls : func->second->callsFrom)
                        {
                            auto it = uniqFuncCalls.find(calls);
                            if (it == uniqFuncCalls.end())
                            {
                                uniqFuncCalls.insert(it, calls);
                                wasChanged = 1;
                            }
                        }
                    }
                }
            }

            string toPrint = "";
            for (auto &elem : uniqFuncCalls)
            {
                auto it = funcMap.find(elem);
                if (it != funcMap.end())
                {
                    regions[i]->AddLines(it->second->linesNum, it->second->fileName);
                    regions[i]->AddFuncCallsToAllCalls(it->second);

                    if (it->second->inRegion == 0)
                        it->second->inRegion = 2;

                    it->second->callRegions.insert(i);

                    toPrint += elem + " ";
                }
            }

            if (toPrint != "")
                __spf_print(1, "[%s]: funcs: %s\n", regions[i]->GetName().c_str(), toPrint.c_str());
        }
    }

    // remove default region if user's found
    if (regions.size() > 1)
    {
#ifdef _WIN32
        removeFromCollection(regions[0]);
#endif
        delete regions[0];
        regions.erase(regions.begin());
    }

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto &func : funcMap)
        {
            if (func.second->inRegion != 0)
                continue;

            for (auto &callsFrom : func.second->callsFrom)
            {
                auto it = funcMap.find(callsFrom);
                if (it != funcMap.end())
                {
                    if (it->second->inRegion > 0)
                    {
                        func.second->inRegion = 3;
                        func.second->callRegions.insert(0);
                        changed = true;
                        break;
                    }
                    else
                        func.second->callRegions.insert(0);
                }
            }
        }
    }

    if (loopGraph)
    {
        //fill regions for loop 
        vector<LoopGraph*> loops;
        for (auto loop : *loopGraph)
            getAllLoops(loop.second, loops);

        for (auto &loop : loops)
        {
            const int currLine = loop->lineNum < -1 ? loop->loop->localLineNumber() : loop->lineNum;
            set<ParallelRegion*> allRegs = getAllRegionsByLine(regions, loop->fileName, currLine);
            if (allRegs.size() == 1)
                loop->region = *(allRegs.begin());
        }
    }
}

int printParalleRegions(const char *fileName, vector<ParallelRegion*> &regions)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        __spf_print(1, "can not open file %s\n", fileName);
        return -1;
    }

    int num = 0;
    for (auto &elem : regions)
    {
        fprintf(file, "*** #%d Parallel Region\n", num);
        elem->print(file);
        fprintf(file, "\n");
        ++num;
    }

    fclose(file);
    return 0;
}

static int getIntVal(SgExpression *ex)
{
    SgExpression* calc = CalculateInteger(ex);
    if (calc->variant() == INT_VAL)
        return calc->valueInteger();
    else
        return 0;
}

static void fillMultOp(SgExpression *ex, pair<string, pair<int, int>> &retVal)
{
    const int var = ex->lhs()->variant();
    if (var == INT_VAL || var == CONST_REF || var == MINUS_OP) // -+a * X
    {
        retVal.first = ex->rhs()->symbol()->identifier();        
        retVal.second.first = getIntVal(ex->lhs());        
    }
    else if (var == VAR_REF) // X * -+a
    {
        retVal.first = ex->lhs()->symbol()->identifier();
        retVal.second.first = getIntVal(ex->rhs());
    }
}

static pair<string, pair<int, int>> parseExpression(SgExpression *ex)
{
    pair<string, pair<int, int>> retVal;

    if (ex)
    {
        if (ex->variant() == VAR_REF)
        {
            retVal.first = ex->symbol()->identifier();
            retVal.second = make_pair(1, 0);
        }
        else if (ex->variant() == MULT_OP) // a * X
            fillMultOp(ex, retVal);
        else if (ex->variant() == ADD_OP || ex->variant() == SUBT_OP) // a * X +- b
        {
            int minus = (ex->variant() == ADD_OP) ? 1 : -1;
            if (ex->lhs()->variant() == MULT_OP) // a * X +- b
            {
                fillMultOp(ex->lhs(), retVal);
                retVal.second.second = getIntVal(ex->rhs()) * minus;
            }
            else if (ex->lhs()->variant() == INT_VAL) // b +- [a *] X
            {
                if (ex->rhs()->variant() == MULT_OP)
                    fillMultOp(ex->rhs(), retVal);
                else
                {
                    retVal.first = ex->rhs()->symbol()->identifier();
                    retVal.second.first = minus;
                }
                retVal.second.second = getIntVal(ex->lhs()) * minus;
            }
            else if (ex->lhs()->variant() == VAR_REF && ex->rhs()->variant()) // X +- b
            {
                retVal.first = ex->lhs()->symbol()->identifier();
                retVal.second.first = 1;
                retVal.second.second = getIntVal(ex->rhs()) * minus;
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        else if (ex->variant() == KEYWORD_VAL)
        {
            SgKeywordValExp *keyVal = (SgKeywordValExp*)ex;
            if (keyVal->value())
                retVal = make_pair(keyVal->value(), make_pair(0, 0));
        }
    }
    return retVal;
}

static void fillTemplate(SgExpression *ex, vector<pair<string, pair<int, int>>> &templateArray)
{
    for (SgExpression *list = ex; list; list = list->rhs())
        templateArray.push_back(parseExpression(list->lhs()));
}

static int getTemplateDemention(const string &val, const vector<pair<string, pair<int, int>>> &alignWithTemplate)
{
    int ret = -1;
    for (int k = 0; k < alignWithTemplate.size(); ++k)
    {
        if (alignWithTemplate[k].first == val)
        {
            ret = k;
            break;
        }
    }
    return ret;
}

bool buildGraphFromUserDirectives(const vector<Statement*> &userDvmAlignDirs, DIST::GraphCSR<int, double, attrType> &G, 
                                  DIST::Arrays<int> &allArrays, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls, 
                                  const set<DIST::Array*>& alignedArrays, set<DIST::Array*>& addedArrays)
{
    if (userDvmAlignDirs.size())
    {
        G.cleanData();

        int t = 0;
        for (auto &dir : userDvmAlignDirs)
        {
            if (SgFile::switchToFile(dir->GetFileNameIncludedTo()) == -1)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            vector<DIST::Array*> alignArrays;
            
            vector<pair<string, pair<int, int>>> alignTemplate;

            DIST::Array* alignWithArray = NULL;
            vector<pair<string, pair<int, int>>> alignWithTemplate;

            if (dir->expr(0) == NULL)
                return true;

            for (SgExpression *ex = dir->expr(0); ex; ex = ex->rhs())
            {
                SgExpression *val = ex->lhs();
                if (val->variant() == ARRAY_REF && val->symbol())
                {
                    DIST::Array *newValue = getArrayFromDeclarated(declaratedInStmt(val->symbol()), val->symbol()->identifier());
                    if (newValue)
                        alignArrays.push_back(newValue);
                    else
                        return true;
                }
            }

            map<DIST::Array*, set<DIST::Array*>> realAlignArrayRefs;
            for (auto &access : alignArrays)
                getRealArrayRefs(access, access, realAlignArrayRefs[access], arrayLinksByFuncCalls);

            set<DIST::Array*> realAlignArrayRefsSet;
            for (auto &elem : realAlignArrayRefs)
                realAlignArrayRefsSet.insert(elem.second.begin(), elem.second.end());

            if (dir->expr(1))
                fillTemplate(dir->expr(1), alignTemplate);
            else if (dir->variant() == DVM_VAR_DECL)
                fillTemplate(dir->expr(2)->lhs()->lhs(), alignTemplate);
            else
                return true;

            if (dir->expr(2))
            {
                SgExpression *ex = dir->expr(2);
                if (ex->variant() == EXPR_LIST && ex->lhs()->variant() == ALIGN_OP)
                    ex = ex->lhs()->rhs();

                if (ex && ex->variant() == ARRAY_REF && ex->symbol())
                {
                    alignWithArray = getArrayFromDeclarated(declaratedInStmt(ex->symbol()), ex->symbol()->identifier());
                    if (alignWithArray == NULL)
                        return true;
                    fillTemplate(ex->lhs(), alignWithTemplate);
                }
                else
                    return true;
            }
            else
                return true;

            string tmp;            
            for (auto& elem : realAlignArrayRefsSet)
                tmp += elem->GetName() + " ";
            __spf_print(1, "align arrays from '%s' from user dir in line %d\n", tmp.c_str(), dir->lineNumber());

            for (int i = 0; i < alignTemplate.size(); ++i)
            {
                if (alignTemplate[i].first != "*")
                {
                    int dimT = getTemplateDemention(alignTemplate[i].first, alignWithTemplate);
                    if (dimT == -1)
                        continue;
                    
                    for (auto& array : realAlignArrayRefsSet)
                    {
                        if (!array->GetNonDistributeFlag())
                        {
                            if (alignWithArray->IsTemplate() && alignWithArray->GetShortName().find("_r") != string::npos)
                                continue;

                            //TODO:
                            /*if (alignedArrays.find(array) != alignedArrays.end())
                                continue;*/
                            addedArrays.insert(array);
                            DIST::AddArrayAccess(G, allArrays, array, alignWithArray, make_pair(i, dimT), 1.0, make_pair(make_pair(1, 0), alignWithTemplate[dimT].second), WW_link);
                        }
                    }
                }
            }
        }
    }

    return false;
}

void calculateLinesOfCode(vector<ParallelRegion*> &allRegions)
{
    for (auto &elem : allRegions)
    {
        auto allLines = elem->GetAllLines();
        int lineCounter = 0;
        for (auto &line : allLines)
            for (auto &lineV : line.second)
                lineCounter += (lineV.lines.second - lineV.lines.first);

        __spf_print(1, "Count of lines in region '%s' = %d\n", elem->GetName().c_str(), lineCounter);
    }
}