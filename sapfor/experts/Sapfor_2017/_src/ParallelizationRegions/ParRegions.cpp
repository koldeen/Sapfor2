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

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::map;
using std::set;

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

static void findFuncCalls(SgExpression *ex, set<string> &calls)
{
    if (ex == NULL)
        return;

    if (ex->variant() == FUNC_CALL)
        calls.insert(ex->symbol()->identifier());

    findFuncCalls(ex->lhs(), calls);
    findFuncCalls(ex->rhs(), calls);
}

static void updateRegionInfo(SgStatement *st, map<string, pair<Statement*, Statement*>> &startEnd, map<string, pair<int, int>> &lines_,
                             set<string> &funcCallFromReg)
{
    extendRegionInfo(st, startEnd, lines_);
    if (st->variant() == PROC_STAT)
        funcCallFromReg.insert(st->symbol()->identifier());
    for (int z = 0; z < 3; ++z)
        findFuncCalls(st->expr(z), funcCallFromReg);
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

<<<<<<< HEAD
void fillRegionLines(SgFile *file, vector<ParallelRegion*> &regions, vector<LoopGraph*> *loops)
=======
static void setExplicitFlag(const string &name, const map<string, FuncInfo*> &mapFuncs)
{
    auto it = mapFuncs.find(name);
    if (it != mapFuncs.end())
        it->second->inRegion = 1;
}

void fillRegionLines(SgFile *file, vector<ParallelRegion*> &regions, vector<LoopGraph*> *loops, vector<FuncInfo*> *funcs)
>>>>>>> master
{
    map<string, FuncInfo*> mapFuncs;
    if (funcs)
        createMapOfFunc(*funcs, mapFuncs);

    //fill default
    SgStatement *st = file->firstStatement();
    ParallelRegion *defaultR = regions[0];
    pair<int, int> lines(st->lineNumber(), 0);

    while (st)
    {
        st = st->lastNodeOfStmt();
        lines.second = st->lineNumber();
        st = st->lexNext();
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

        set<string> usedArrayInRegion;

        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != NULL && st != lastNode)
        {
            currProcessing.second = st;
            if (st->variant() == CONTAINS_STMT)
                break;

            SgStatement *prev = st->lexPrev();
            SgStatement *next = st->lexNext();

            if (prev && prev->variant() == SPF_PARALLEL_REG_DIR)
            {
                SgStatement *data = prev;

                regionStarted = true;
                regionName = data->symbol()->identifier();
<<<<<<< HEAD

            }
            else if (next && next->variant() == SPF_END_PARALLEL_REG_DIR)
            {
                updateRegionInfo(st, startEnd, lines_, funcCallFromReg);
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

                filterUserDirectives(currReg, usedArrayInRegion, userDvmDistrDirs, userDvmAlignDirs, userDvmShadowDirs);
                currReg->AddUserDirectives(userDvmRealignDirs, DVM_REALIGN_DIR);
                currReg->AddUserDirectives(userDvmRedistrDirs, DVM_REDISTRIBUTE_DIR);

=======
                if (funcs)
                    setExplicitFlag(file->functions(i)->symbol()->identifier(), mapFuncs);
            }
            else if (next && next->variant() == SPF_END_PARALLEL_REG_DIR)
            {
                updateRegionInfo(st, startEnd, lines_, funcCallFromReg);
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

                filterUserDirectives(currReg, usedArrayInRegion, userDvmDistrDirs, userDvmAlignDirs, userDvmShadowDirs);
                currReg->AddUserDirectives(userDvmRealignDirs, DVM_REALIGN_DIR);
                currReg->AddUserDirectives(userDvmRedistrDirs, DVM_REDISTRIBUTE_DIR);

>>>>>>> master
                startEnd.clear();
                lines_.clear();
                funcCallFromReg.clear();

                userDvmRealignDirs.clear();
                userDvmRedistrDirs.clear();

                usedArrayInRegion.clear();
            }


            if (regionStarted)
            {
                updateRegionInfo(st, startEnd, lines_, funcCallFromReg);
                for (int i = 0; i < 3; ++i)
                    fillArrayNamesInReg(usedArrayInRegion, st->expr(i));
            }

            switch (st->variant())
            {
            case DVM_VAR_DECL:
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
                break;
            case DVM_REDISTRIBUTE_DIR:
                if (regionStarted)
                    userDvmRedistrDirs.push_back(new Statement(st));
                break;
            case DVM_PARALLEL_ON_DIR:
                if (st->lexNext()->variant() == FOR_NODE)
                {
                    SgForStmt *forStat = (SgForStmt*)(st->lexNext());
                    auto it = allLoopsInFile.find(forStat->lineNumber());
                    if (it != allLoopsInFile.end())
                        it->second->userDvmDirective = new Statement(st);
                }
                break;
            default:
                break;
            }

            st = st->lexNext();
        }
    }
}

ParallelRegion* getRegionByLine(const vector<ParallelRegion*> &regions, const string &file, const int line)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return regions[0];
    else if (regions.size() > 0)
    {
        set<ParallelRegion*> regFound;

        for (int i = 0; i < regions.size(); ++i)
            if (regions[i]->HasThisLine(line, file))
                regFound.insert(regions[i]);

        if (regFound.size() == 0)
            return 0;
        else if (regFound.size() == 1)
            return *regFound.begin();
        else
        {
            __spf_print(1, "WARN: this lines included in more than one region!!\n");
            return NULL;
        }
    }
    else
        return NULL;

    return NULL;
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
                    if (it->second->inRegion == 0)
                        it->second->inRegion = 2;
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

<<<<<<< HEAD
=======
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
                        changed = true;
                        break;
                    }
                }
            }
        }
    }

>>>>>>> master
    if (loopGraph)
    {
        //fill regions for loop 
        vector<LoopGraph*> loops;
        for (auto loop : *loopGraph)
            getAllLoops(loop.second, loops);

        for (auto &loop : loops)
        {
            const int currLine = loop->lineNum < -1 ? loop->loop->localLineNumber() : loop->lineNum;
            loop->region = getRegionByLine(regions, loop->fileName, currLine);
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

static void fillMultOp(SgExpression *ex, pair<string, pair<int, int>> &retVal)
{
    if (ex->lhs()->variant() == INT_VAL || ex->lhs()->variant() == MINUS_OP) // -+a * X
    {
        retVal.first = ex->rhs()->symbol()->identifier();
        retVal.second.first = ex->lhs()->valueInteger();
    }
    else if (ex->lhs()->variant() == VAR_REF) // X * -+a
    {
        retVal.first = ex->lhs()->symbol()->identifier();
        retVal.second.first = ex->rhs()->valueInteger();
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
                retVal.second.second = ex->rhs()->valueInteger() * minus;
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
                retVal.second.second = ex->lhs()->valueInteger() * minus;
            }
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
                                  DIST::Arrays<int> &allArrays, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    if (userDvmAlignDirs.size())
    {
        G.cleanData();

        int t = 0;
        for (auto &dir : userDvmAlignDirs)
        {
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
            else
                return true;

            if (dir->expr(2))
            {
                SgExpression *ex = dir->expr(2);
                if (ex->variant() == ARRAY_REF && ex->symbol())
                {
                    alignWithArray = getArrayFromDeclarated(declaratedInStmt(ex->symbol()), ex->symbol()->identifier());
                    if (alignWithArray == NULL)
                        return true;
                    fillTemplate(ex->lhs(), alignWithTemplate);
                }
            }
            else
                return true;
                        
            /*dir->unparsestdout();
            printf("DIR #%d\n", t++);
            for (int i = 0; i < 3; ++i)
            {
                if (dir->expr(i))
                {
                    printf(" EXP #%d\n", i);
                    recExpressionPrint(dir->expr(i));
                }
            }
            printf("\n");*/

            for (int i = 0; i < alignTemplate.size(); ++i)
            {
                if (alignTemplate[i].first != "*")
                {
                    int dimT = getTemplateDemention(alignTemplate[i].first, alignWithTemplate);
                    if (dimT == -1)
                        return true;
                    //AddArrayAccess(G, allArrays, fromSymb, toSymb, make_pair(dimFrom, dimTo), currWeight, make_pair(from->writeOps[dimFrom].coefficients[z], to->writeOps[dimTo].coefficients[z1]), WW_link);
                    for (auto &arrays : realAlignArrayRefsSet)
                        DIST::AddArrayAccess(G, allArrays, arrays, alignWithArray, make_pair(i, dimT), 1.0, make_pair(make_pair(1, 0), alignWithTemplate[dimT].second), WW_link);
                }
            }
        }
    }

    return false;
}