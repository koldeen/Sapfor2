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

using std::vector;
using std::map;
using std::string;
using std::stack;
using std::pair;
using std::to_string;

static void markNestedIntervals(SpfInterval *interval)
{
    for (auto &item : interval->nested)
    {
        item->isNested = true;

        if (!item->begin->switchToFile())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (item->begin->symbol()->identifier() != NULL)
            markNestedIntervals(item);
    }
}

static int countOfIntervals(const SpfInterval *interval, const SpfInterval *mainInterval)
{
    int count = 0;
    for (auto &item : mainInterval->nested)
    {
        if (item == interval)
            count++;
        else
            count += countOfIntervals(interval, item);
    }

    return count;
}

static void performFuncTime(const map<string, vector<FuncInfo*>> &funcInfo, map<string, int> &countFunc)
{
    int count = 0;
    for (auto &str : funcInfo) 
    {
        count = 0;
        for (auto *info : str.second)
        {
            count += (info->callsTo).size();
            
            if (countFunc.find(info->funcName) != countFunc.end())
                countFunc[info->funcName] += count;
            else
                countFunc.insert(make_pair(info->funcName, count));
        }
    }
}

double performTime(SgProject* project, SgStatement *src, const map<string, map<int, Gcov_info>> &gCovInfo, map<string, int> &calls, int recLevel)
{
    SgStatement* stmt = src;
    
    if (!src->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (!isSgExecutableStatement(stmt))
        return 0.0;

    auto gCovForFile = gCovInfo.find(string(stmt->fileName()));
    if (gCovForFile == gCovInfo.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    auto gCovForStmt = gCovForFile->second.find(stmt->lineNumber());
    if (gCovForStmt == gCovForFile->second.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    const Gcov_info& info = gCovForStmt->second;
    double count = 0.0;

    switch (stmt->variant()) 
    {  
        case PROC_STAT:
        {
            if (recLevel <= 5)
            {
                SgCallStmt *call = (SgCallStmt*)src;
                if (info.getCountCalls() == 0)
                    break;
                SgStatement *body = NULL;
                string funcName(call->name()->identifier());
                auto num = calls.find(funcName);
                // its not a user function
                if (num == calls.end()) 
                    break;

                for (int j = 0; j < project->numberOfFiles(); ++j)
                {
                    SgFile& file = project->file(j);
                    if (SgFile::switchToFile(file.filename()) == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    for (int i = 0; i < file.numberOfFunctions(); ++i) 
                    {
                        if (!strcmp(file.functions(i)->symbol()->identifier(), funcName.c_str()))
                        {
                            body = file.functions(i);
                            break;
                        }
                    }
                }
                if (body == NULL)
                    break;

                while (body && body->variant() != RETURN_STAT)
                {
                    count += performTime(project, body, gCovInfo, calls, recLevel + 1);
                   
                    if (!body->switchToFile())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    body = body->lexNext();
                }

                count /= num->second;
            }
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
                t += performTime(project, tmp, gCovInfo, calls, recLevel + 1);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[0].getPercent()) * 0.01 * t;
            t = 0;
            tmp = ifSt->falseBody();
            while (tmp && tmp->variant() != CONTROL_END)
            {
                t += performTime(project, tmp, gCovInfo, calls, recLevel + 1);
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
                count += performTime(project, tmp, gCovInfo, calls, recLevel + 1);
                
                if (!tmp->switchToFile())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

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
                count += performTime(project, tmp, gCovInfo, calls, recLevel + 1);
               
                if (!tmp->switchToFile())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

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

typedef pair<vector<SpfInterval*>, int> PositionInVector;
typedef stack<PositionInVector> IntervalStack;

double performIntervalTime(SgProject* project, const SpfInterval *interval, const map<string, map<int, Gcov_info>> &gCovInfo, map<string, int> &calls)
{
    double time = 0.0;
    for (SgStatement *stat = interval->begin; stat != interval->ends[interval->ends.size() - 1]; stat = stat->lexNext())
    {
        time += performTime(project, stat, gCovInfo, calls, 0);
        if (!stat->switchToFile())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    }

    return time;
}

void createParallelRegions(SgProject* project, SpfInterval *mainInterval, const map<string, map<int, Gcov_info>> &gCovInfo, const map<string, vector<FuncInfo*>> &funcInfo)
{
    double percent = 0.8;
    vector<SpfRegion> regions;
    map<string, int> calls;

    performFuncTime(funcInfo, calls);
    if (mainInterval == NULL)
    {
        __spf_print(1, "internal error in analysis, directives will not be generated for this file!\n");
        return;
    }

   
    double sumTime = performIntervalTime(project, mainInterval, gCovInfo, calls);
 
    double alreadyHavePercent = 0.0;
    int id = 1;
    int i = 0;
    IntervalStack stack;
    vector<SpfInterval*> iterated;
    vector<SpfInterval*> nested;

    iterated.push_back(mainInterval);

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

        double time = performIntervalTime(project, interval, gCovInfo, calls);
        int count = countOfIntervals(interval, mainInterval);
        if (count != 0) time *= count;
        double percentOfInterval = time / sumTime;

        if (percentOfInterval + alreadyHavePercent <= percent)
        {
            __spf_print(1, "Add interval with %f percent, we have %f percent\n", percentOfInterval, percentOfInterval + alreadyHavePercent);
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
                stack.push(make_pair(vector<SpfInterval*>(iterated.begin(), iterated.end()), i + 1));
            
            iterated.clear();
            iterated = vector<SpfInterval*>(interval->nested.begin(), interval->nested.end());
            i = 0;
        }      
    }

    i = 0;
    while (i < regions.size()) 
    {
        if (i > 0 && !regions[i-1].end->switchToFile())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (i > 0 && regions[i - 1].end->lexNext() == regions[i].start)
        {
            regions[i - 1].end = regions[i].end;
            regions.erase(regions.begin() + i);

            continue;
        }
        
        i++;
    }

    __spf_print(1, "Coverage of region is %f percent, count of regions is %d\n", alreadyHavePercent, regions.size());

    for (auto &item : regions) 
    {
        if (!item.start->switchToFile())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        SgStatement *startRegion = new SgStatement(SPF_PARALLEL_REG_DIR);
        SgStatement *endRegion = new SgStatement(SPF_END_PARALLEL_REG_DIR);        

        startRegion->setSymbol(*(new SgSymbol(VARIABLE_NAME, to_string(item.id).c_str())));
        
        SgStatement *st = item.start;
        while (!isSgExecutableStatement(st))
            st = st->lexNext();
            
        startRegion->setFileId(st->getFileId());
        startRegion->setProject(st->getProject());
        startRegion->setlineNumber(st->lineNumber());
        startRegion->setFileName(st->fileName());

        st->insertStmtBefore(*startRegion, *st->controlParent());

        SgStatement *next = item.end->lexNext();
        startRegion->setFileId(next->getFileId());
        startRegion->setProject(next->getProject());
        startRegion->setlineNumber(next->lineNumber());
        startRegion->setFileName(next->fileName());

        next->insertStmtBefore(*endRegion, *next->controlParent());
    }
}
