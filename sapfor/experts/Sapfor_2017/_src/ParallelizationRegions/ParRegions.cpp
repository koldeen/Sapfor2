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

using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::map;
using std::set;

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

void fillRegionLines(SgFile *file, vector<ParallelRegion*> &regions)
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

    //fill user's
    int funcNum = file->numberOfFunctions();
    string regionName = "";
    map<string, pair<Statement*, Statement*>> startEnd;
    map<string, pair<int, int>> lines_;
    set<string> funcCallFromReg;
    bool regionStarted = false;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != NULL && st != lastNode)
        {
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

                    startEnd.clear();
                    lines_.clear();
                    funcCallFromReg.clear();
                }
            }

            if (regionStarted)
                updateRegionInfo(st, startEnd, lines_, funcCallFromReg);
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
            if (regions[i]->hasThisLine(line, file))
                regFound.insert(regions[i]);

        if (regFound.size() == 0)
            return 0;
        else if (regFound.size() == 1)
            return *regFound.begin();
        else
        {
            print(1, "WARN: this lines included in more than one region!!\n");
            return NULL;
        }
    }
    else
        return NULL;

    return NULL;
}

void fillRegionLinesStep2(vector<ParallelRegion*> &regions, map<string, vector<FuncInfo*>> allFuncInfo, map<string, vector<LoopGraph*>> &loopGraph)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (int i = 0; i < regions.size(); ++i)
    {
        if (regions[i]->GetName() != "DEFAULT") 
        {
            set<string> uniqFuncCalls;
            for (auto &elem : regions[i]->GetAllFuncCalls())
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
                print(1, "[%s]: funcs: %s\n", regions[i]->GetName().c_str(), toPrint.c_str());
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
    for (auto it = loopGraph.begin(); it != loopGraph.end(); ++it)
    {
        for (auto &loop : it->second)
        {
            ParallelRegion *parReg = getRegionByLine(regions, it->first, loop->lineNum);
            if (parReg != NULL)
            {
                loop->region = parReg;
                loop->setRegionToChilds();
            }
        }
    }
}