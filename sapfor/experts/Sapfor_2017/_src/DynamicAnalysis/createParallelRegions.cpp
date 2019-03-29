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

struct SpfRegion {
    int id;

    int time;
    SgStatement *start;
    SgStatement *end;

    SpfRegion(int id_, int time_,  SgStatement *start_, SgStatement *end_): 
        id(id_), time(time_), start(start_), end(end_) {}

    SpfRegion& operator+=(SpfRegion rg) 
    {
        if (this != &rg)
        {
            end = rg.end;
            time += rg.time;
        }
        return *this;
    }
};

const SpfInterval* findMainInterval(std::vector<SpfInterval*> &fileIntervals)
{
    for (const SpfInterval* interval : fileIntervals)
        if (interval->tag == PROG_HEDR)
            return interval;
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
            countFunc[str.first] = count;
    }
}

float performTime(SgFile *file, SgStatement *src, std::map<int, Gcov_info> &gCovInfo, 
    std::map<std::string, int> &calls, int recLevel)
{
    SgStatement* stmt = src;
    Gcov_info info = gCovInfo[stmt->lineNumber()];
    float count = 0.0;

    switch (stmt->variant()) 
    {  
        case PROC_STAT:
        if (recLevel <= 1)
        {
            SgCallStmt *call = (SgCallStmt*) src;
            SgStatement *tmp = call->name()->body();
            
            while (tmp && tmp->variant() != RETURN_STAT)
            {
                count += performTime(file, tmp, gCovInfo, calls, recLevel + 1);
                tmp = tmp->lexNext();
            }

            std::cout << calls[(std::string)call->name()->identifier()];
            count = (float)count / calls[call->name()->identifier()];
            
            break;
        }
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
            count += 0.0000000005 * info.getExecutedCount();
            break;
        case WRITE_STAT:
        case READ_STAT:
            count += 0.0000000015 * info.getExecutedCount();
            break;
        default:
            break;
    }

    return count;
}

float performIntervalTime(SgFile *file, SpfInterval *interval, std::map<int, Gcov_info> &gCovInfo, std::map<std::string, int> &calls)
{
    float time = 0.0;
    for (SgStatement *stat = interval->begin; stat != interval->ends[0]; stat = stat->lexNext())
        time += performTime(file, stat, gCovInfo, calls, 1);

    return time;
}


void createParallelRegions(SgFile *file, std::vector<SpfInterval*> &fileIntervals, std::map<int, Gcov_info> &gCovInfo,
    std::map<std::string, std::vector<FuncInfo*>> &funcInfo)
{
    float percent;

    std::map<std::string, int> calls;
    performFuncTime(file, funcInfo, calls);

    float sumTime = 0.0;
    SgStatement *st = file->firstStatement();
    SgStatement *lastNode = st->lastNodeOfStmt();

    while (st != lastNode)
    {
        sumTime += performTime(file, st, gCovInfo, calls, 0);
        st = st->lexNext();
    }

    __spf_print(1, "time of performing of the whole file is %f \n", sumTime);

    std::vector<SpfRegion> intervals;
    
    const SpfInterval* mainInterval;
    mainInterval = findMainInterval(fileIntervals);

    float alreadyHavePercent = 0;
    int id = 1;
    std::vector<SpfInterval*> iterated = mainInterval->nested;

    for (SpfInterval* interval : iterated)
    {
        float time = performIntervalTime(file, interval, gCovInfo, calls);
        float percentOfInterval = time / sumTime;

        if (percentOfInterval + alreadyHavePercent < percent)
        {
            intervals.push_back(SpfRegion(id, time, interval->begin, interval->ends[0]));
            alreadyHavePercent += percentOfInterval;
        }

        if (percentOfInterval + alreadyHavePercent > percent)
        {
            if (alreadyHavePercent >= percent)
                break;
            iterated = interval->nested;
        }
    }
    // TODO
    // 1. выравнивание
    // 2. добавить в анализаторы

    for (auto& item : intervals) 
    {
        SgStatement startRegion = SgStatement(SPF_PARALLEL_REG_DIR),
             endRegion = SgStatement(SPF_END_PARALLEL_REG_DIR);
        
        startRegion.setId(item.id);
        endRegion.setId(item.id);
        
        item.start->insertStmtAfter(startRegion);
        item.end->insertStmtBefore(endRegion);
    }
}
