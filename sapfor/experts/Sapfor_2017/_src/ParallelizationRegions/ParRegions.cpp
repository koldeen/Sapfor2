#include "../leak_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "dvm.h"
#include "ParRegions.h"
#include "../utils.h"
#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops.h"

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

void fillRegionLines(SgFile *file, vector<ParallelRegion*> &regions, vector<LoopGraph*> &loops)
{
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
    createMapLoopGraph(allLoopsInFile, &loops);

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
            int attrNum = st->numberOfAttributes();
            for (int k = 0; k < attrNum; ++k)
            {
                SgAttribute *attr = st->getAttribute(k);
                int type = st->attributeType(k);
                if (type == SPF_PARALLEL_REG_DIR)
                {
                    SgStatement *data = (SgStatement *)(attr->getAttributeData());
                    regionStarted = true;
                    regionName = data->symbol()->identifier();
                    updateRegionInfo(st, startEnd, lines_, funcCallFromReg);
                }
                else if (type == SPF_END_PARALLEL_REG_DIR)
                {
                    SgStatement *data = (SgStatement *)(attr->getAttributeData());
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

                    startEnd.clear();
                    lines_.clear();
                    funcCallFromReg.clear();

                    userDvmRealignDirs.clear();
                    userDvmRedistrDirs.clear();

                    usedArrayInRegion.clear();
                }
            }

            if (regionStarted)
            {
                updateRegionInfo(st, startEnd, lines_, funcCallFromReg);
                for (int i = 0; i < 3; ++i)
                    fillArrayNamesInReg(usedArrayInRegion, st->expr(i));
            }

            switch (st->variant())
            {
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
        getAllLoops(elem->childs, loops);
}

void fillRegionLinesStep2(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> &allFuncInfo, map<string, vector<LoopGraph*>> &loopGraph)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

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

    //fill regions for loop 
    vector<LoopGraph*> loops;
    for (auto it = loopGraph.begin(); it != loopGraph.end(); ++it)
        getAllLoops(it->second, loops);

    for (auto &loop : loops)
    {
        const int currLine = loop->lineNum < -1 ? loop->loop->localLineNumber() : loop->lineNum;
        loop->region = getRegionByLine(regions, loop->fileName, currLine);
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
    }

    fclose(file);
    return 0;
}