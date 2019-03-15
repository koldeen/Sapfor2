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
    std::map<std::string, int> &calls, int rec_level)
{
    SgStatement* stmt = src;
    Gcov_info info = gCovInfo[stmt->lineNumber()];
    float count = 0.0;

    switch (stmt->variant()) 
    {  
        case PROC_STAT:
        if (rec_level <= 1)
        {
            SgCallStmt *call = (SgCallStmt*) src;
            SgStatement *tmp = call->name()->body();
            
            while (tmp && tmp->variant() != RETURN_STAT)
            {
                count += performTime(file, tmp, gCovInfo, calls, rec_level + 1);
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
                t += performTime(file, tmp, gCovInfo, calls, rec_level + 1);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[0].getPercent()) * 0.01 * t;
            t = 0;
            tmp = ifSt->falseBody();
            while (tmp && tmp->variant() != CONTROL_END)
            {
                t += performTime(file, tmp, gCovInfo, calls, rec_level + 1);
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
                count += performTime(file, tmp, gCovInfo, calls, rec_level + 1);
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
                count += performTime(file, tmp, gCovInfo, calls, rec_level + 1);
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

void createParallelRegions(SgFile *file, std::vector<SpfInterval*> &fileIntervals, std::map<int, Gcov_info> &gCovInfo, 
    std::map<std::string, std::vector<FuncInfo*>> &funcInfo)
{
    int constant = 0;
    // понять, чему это равно

    std::map<std::string, int> calls;
    performFuncTime(file, funcInfo, calls);

    float count = 0.0;
    SgStatement *st = file->firstStatement();
    SgStatement *lastNode = st->lastNodeOfStmt();

    while (st != lastNode)
    {
        count += performTime(file, st, gCovInfo, calls, 0);
        st = st->lexNext();
       
    }

    __spf_print(1, "  time of performing is %f \n", count);

    /*
    std::map<int, int> perfTime;
    std::vector<Region> regions;

    float time = 0.0;
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
    */


    // заполнить программу директивами
}
