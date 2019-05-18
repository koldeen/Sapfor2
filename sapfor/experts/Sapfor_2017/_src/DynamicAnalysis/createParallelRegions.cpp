#include "dvm.h"
#include <stdio.h>
#include <iostream>

#include "./createParallelRegions.h"

#include "../CreateInterTree/CreateInterTree.h"
#include "../GraphCall/graph_calls.h"
#include "./gcov_info.h"
#include "./gCov_parser_func.h"
#include "../Utils/leak_detector.h"

#include <map>
#include <vector>
#include <string>
#include <stack>

// find main interval in interval tree after createInterTree
SpfInterval* findMainInterval(std::vector<SpfInterval*> &fileIntervals)
{
    for (SpfInterval* interval : fileIntervals)
    {
        if (interval->begin->variant() == PROG_HEDR)
        {
            return interval;
        }
    }

    return nullptr;
}

void markNestedIntervals(SpfInterval* interval) 
{
      for (auto* item : interval->nested) 
    {
        item->isNested = true;
        if (item->begin->symbol()->identifier() != NULL)
        markNestedIntervals(item);
    }
}

void performFuncTime(SgFile *file, std::map<std::string, std::vector<FuncInfo*>> &funcInfo, std::map<std::string, int> &countFunc)
{
    int count = 0;
    for (auto str : funcInfo) 
    {
        count = 0;
        for (auto info : str.second) 
            count += (info->callsTo).size();

        if (countFunc.find(str.first) != countFunc.end())
            countFunc[str.first] += count;
        else
            countFunc.insert(std::make_pair(str.first, count));
    }
}

double performTime(SgFile *file, SgStatement *src, std::map<int, Gcov_info> &gCovInfo, 
    std::map<std::string, int> &calls, int recLevel)
{
    SgStatement* stmt = src;
    Gcov_info info = gCovInfo[stmt->lineNumber()];
    double count = 0.0;

    switch (stmt->variant()) 
    {  
        case PROC_STAT:
        if (recLevel <= 5)
        {
            SgCallStmt *call = (SgCallStmt*) src;

            if (info.getCountCalls() == 0)
                break;

            SgStatement *tmp = NULL;
                
            for (int i = 0; i < file->numberOfFunctions(); i++)
                if (!strcmp(file->functions(i)->symbol()->identifier(), call->name()->identifier()))
                    tmp = file->functions(i);

            if (tmp == NULL)
                break;
               
            while (tmp && tmp->variant() != RETURN_STAT)
            {
                count += performTime(file, tmp, gCovInfo, calls, recLevel + 1);
                tmp = tmp->lexNext();
            }
        }
        break;
        case IF_NODE:
        case LOGIF_NODE:
        case ELSEIF_NODE:
        {
            SgIfStmt* ifSt = (SgIfStmt*)src;
            SgStatement* tmp = ifSt->trueBody();
            int t = 0;
            while (tmp->variant() != CONTROL_END)
            {
                t += performTime(file, tmp, gCovInfo, calls, recLevel + 1);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[0].getPercent()) * 0.01 * t;
            t = 0;
            tmp = ifSt->falseBody();
            while (tmp && tmp->variant() != CONTROL_END)
            {
                t += performTime(file, tmp, gCovInfo, calls, recLevel + 1);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[1].getPercent()) * 0.01 * t;
            break;
        }
        case WHILE_NODE:
        {
            SgWhileStmt* whileSt = (SgWhileStmt*)src;
            SgStatement* tmp = whileSt->body();
            while (tmp->variant() != CONTROL_END)
            {
                count += performTime(file, tmp, gCovInfo, calls, recLevel + 1);
                tmp = tmp->lexNext();
            }
            break;
        }
        case FOR_NODE:
        {
            SgForStmt* forSt = (SgForStmt*)src;
            SgStatement* tmp = forSt->body();
            while (tmp->variant() != CONTROL_END)
            {
                count += performTime(file, tmp, gCovInfo, calls, recLevel + 1);
                tmp = tmp->lexNext();
            }
            break;
        }
        case ADD_OP:
        case MULT_OP:
        case DIV_OP:
        case SUB_OP:
        case ASSGN_OP:
        case ASSIGN_STAT:
            // let frequency be about 2 GHerz 
            count += 0.0000000005 * info.getExecutedCount();
            break;
        case WRITE_STAT:
        case READ_STAT:
            // read/write operations are slower
            count += 0.0000000015 * info.getExecutedCount();
            break;
        default:
            break;
    }

    return count;
}

typedef std::pair<std::vector<SpfInterval*>, int> PositionInVector;
typedef std::stack<PositionInVector> IntervalStack;

float performIntervalTime(SgFile *file, SpfInterval *interval, std::map<int, Gcov_info> &gCovInfo, std::map<std::string, int> &calls)
{
    float time = 0.0;
    for (SgStatement *stat = interval->begin; stat != interval->ends[interval->ends.size() - 1]; stat = stat->lexNext())
        time += performTime(file, stat, gCovInfo, calls, 0);

    return time;
}

int countOfIntervals(SpfInterval* interval, SpfInterval* mainInterval)
{
    int count = 0;
    for (auto item : mainInterval->nested) 
    {
        if (item == interval)
            count++;
        else
            count += countOfIntervals(interval, item);
    }

    return count;
}

void createParallelRegions(SgFile *file, std::vector<SpfInterval*>& fileIntervals, std::map<int, Gcov_info> &gCovInfo,
    std::map<std::string, std::vector<FuncInfo*>> &funcInfo)
{
    float percent = 0.8;

    std::map<std::string, int> calls;
    performFuncTime(file, funcInfo, calls);
;
    double sumTime = 0.0;

    std::vector<SpfRegion> regions;
    std::vector<SpfInterval*> intervals;

    createInterTree(file, intervals, false);
    if (fileIntervals.size() == 0) 
    {
        __spf_print(1, "internal error in analysis, directives will not be generated for this file!\n");
        return;
    }
    
    SpfInterval* mainInterval = findMainInterval(fileIntervals);
    if (mainInterval == nullptr)
    {
        __spf_print(1, "internal error in analysis, directives will not be generated for this file!\n");
        return;
    }

    sumTime = performIntervalTime(file, mainInterval, gCovInfo, calls);
    __spf_print(1, "time of performing of the whole file is about %.10f s\n", sumTime);

    float alreadyHavePercent = 0.0;
    int id = 1;
    int i = 0;
    IntervalStack stack;
    std::vector<SpfInterval*> iterated;
    std::vector<SpfInterval*> nested;

    iterated.push_back(mainInterval);
    if (iterated.size() == 0) 
    {
        __spf_print(1, "internal error in analysis, directives will not be generated for this file!\n");
        return;
    }


    while (alreadyHavePercent <= percent)
    {
        if (i >= iterated.size())
        {
            if (!stack.empty())
            {
                iterated = stack.top().first;
                i = stack.top().second;

                stack.pop();
            }
            else
                break;
        }

        SpfInterval* interval = iterated[i];
        if (!interval || interval->isRegion || interval->isNested) 
        {
            i++;
            continue;
        }

        double time = performIntervalTime(file, interval, gCovInfo, calls);
        int count = countOfIntervals(interval, mainInterval);
        if (count != 0) time *= count;
        float percentOfInterval = time / sumTime;


        if (percentOfInterval + alreadyHavePercent <= percent)
        {
            __spf_print(1, "Add interval with %f percent, we have %f percent ", percentOfInterval, percentOfInterval + alreadyHavePercent);
            SpfRegion region(id, time, interval->begin, interval->ends[0]);
            region.time = time;
            region.id = id;
            iterated[i]->isRegion = true;
            markNestedIntervals(interval);
            id++;
            i++;

            regions.push_back(region);
            alreadyHavePercent += percentOfInterval;
        }
        else
        {
            __spf_print(1, "divide interval with %f percent\n", percentOfInterval);
            if (i < iterated.size() - 1)
                stack.push(std::make_pair(std::vector<SpfInterval*>(iterated.begin(), iterated.end()), i + 1));
            
            iterated.clear();
            iterated = std::vector<SpfInterval*>(interval->nested.begin(), interval->nested.end());
            i = 0;
        }      
    }

    i = 0;
    while (i < regions.size()) 
    {
        if (i > 0 && regions[i - 1].end->lexNext() == regions[i].start)
        {
            regions[i - 1].end = regions[i].end;
            regions.erase(regions.begin() + i);

            continue;
        }
        
        i++;
    }

    __spf_print(1, "Coverage of region is %f percent, count of regions is %d\n", alreadyHavePercent, regions.size());

    for (auto& item : regions) 
    {
        SgStatement *startRegion = new SgStatement(SPF_PARALLEL_REG_DIR),
             *endRegion =  new SgStatement(SPF_END_PARALLEL_REG_DIR);
      
        startRegion->setSymbol(*(new SgSymbol(VARIABLE_NAME, std::to_string(item.id).c_str())));
        endRegion->setSymbol(*(new SgSymbol(VARIABLE_NAME, std::to_string(item.id).c_str())));
        
        while (!isSgExecutableStatement(item.start))
            item.start = item.start->lexNext();
            
        item.start->insertStmtBefore(*startRegion);
        item.end->insertStmtAfter(*endRegion);
    }

    FILE *fOut = fopen("./_regions.f", "w");
    file->unparse(fOut);
}
