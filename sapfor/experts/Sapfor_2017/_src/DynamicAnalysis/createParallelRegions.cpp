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

struct Region {
    int id;

    int time;
    SgStatement *start;
    SgStatement *end;

    Region(int id_, int time_,  SgStatement *start_, SgStatement *end_): 
        id(id_), time(time_), start(start_), end(end_) {}

    Region& operator+=(Region rg) 
    {
        if (this != &rg)
        {
            end = rg.end;
            time += rg.time;
        }
        return *this;
    }
};

bool performFuncTime(SgFile *file, std::map<std::string, std::vector<FuncInfo>> &funcInfo, std::map<std::string, int> &countFunc)
{
    int count = 0;
    for (auto str : funcInfo) 
    {
        for (auto info : str.second) 
            count += (info.callsTo).size();

        if (countFunc.find(str.first) != countFunc.end())
            countFunc[str.first] = +count;
        else
            countFunc.insert_or_assign(str.first, count);
    }
}

int performTime(SgFile *file, SgStatement *src, std::map<int, Gcov_info> &gCovInfo, std::map<std::string, 
    std::vector<FuncInfo>> &funcInfo, int rec_level)
{
    SgStatement* stmt = src;
    Gcov_info info = gCovInfo[stmt->lineNumber()];
    int count = 0;

    switch (stmt->variant()) 
    {  
        case PROC_CALL:
        {
            std::map<std::string, int> calls;
            performFuncTime(file, funcInfo, calls);

            SgCallStmt *call = (SgCallStmt*)src;
            SgStatement *tmp = call->name()->body();
          
            while (tmp->variant() != RETURN_STAT)
            {
                count += performTime(file, tmp, gCovInfo, funcInfo, rec_level + 1);
                tmp = tmp->lexNext();
            }
            count = (float)count / calls[call->name()->identifier];
            
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
                t += performTime(file, tmp, gCovInfo, funcInfo, rec_level + 1);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[0].getPercent()) * t;
            t = 0;
            tmp = ifSt->falseBody();
            while (tmp && tmp->variant() != CONTROL_END)
            {
                t += performTime(file, tmp, gCovInfo, funcInfo, rec_level + 1);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[1].getPercent()) * t;
            break;
        }
        case WHILE_NODE:
        {
            SgWhileStmt* whileSt = (SgWhileStmt*)src;
            SgStatement* tmp = whileSt->body();
            while (tmp->variant() != CONTROL_END)
            {
                count += performTime(file, tmp, gCovInfo, funcInfo, rec_level + 1);
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
                count += performTime(file, tmp, gCovInfo, funcInfo, rec_level + 1);
                tmp = tmp->lexNext();
            }
            break;
        }
        default:
            count += info.getExecutedCount();
    }

    return count;
}

void createParallelRegions(SgFile *file, std::vector<Interval*> &fileIntervals, std::map<int, Gcov_info> &gCovInfo, 
    std::map<std::string, std::vector<FuncInfo>> &funcInfo)
{
    int constant = 0;
    // понять, чему это равно

    std::map<int, int> perfTime;
    std::vector<Region> regions;

    int time = 0;
    bool wasChanged = true;

    for (const Interval* inter : fileIntervals)
    {
        time = 0;
        if (inter->parent == NULL)
        {
            SgStatement *tmp = inter->begin;
            // понять и осознать, какой нужен end
           // while (tmp != inter->ends) 
            {
                time += performTime(file, tmp, gCovInfo, funcInfo, 0);
                tmp = tmp->lexNext();
            }

            perfTime.insert_or_assign(perfTime.size(), time);
        }
    }

    for (auto item : perfTime) 
        regions.push_back(Region(item.first, item.second, fileIntervals[item.first]->begin, fileIntervals[item.first]->ends));

    while (wasChanged) 
    {
        wasChanged = false;
        for (auto obl : regions) 
        {
            //if (obl.time < C && )
            //if (obl.time < C && )
            {
                // понять, подряд ли склеивать и склеить
                // obl +=
                wasChanged = true;
            }
        }
    }


    // заполнить программу директивами
}
