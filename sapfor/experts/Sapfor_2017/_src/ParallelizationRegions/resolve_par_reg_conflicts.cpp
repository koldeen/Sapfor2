#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "resolve_par_reg_conflicts.h"
#include "SgUtils.h"

#include "../GraphCall/graph_calls_func.h"

using std::map;
using std::pair;
//using std::tuple;
using std::set;
using std::vector;
using std::string;
using std::make_pair;

extern set<string> allUsedCommonArrays;
extern set<string> allCommonFunctions;

set<ParallelRegion*> getRegionByLine2(const vector<ParallelRegion*> &regions, const string &file, const int line)
{
    set<ParallelRegion*> regFound;

    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
    {
        regFound.insert(regions[0]);
        return regFound;
    }
    else if (regions.size() > 0)
    {
        for (int i = 0; i < regions.size(); ++i)
            if (regions[i]->HasThisLine(line, file))
                regFound.insert(regions[i]);

        return regFound;
    }
}

static bool isInCommon(const map<string, CommonBlock> &commonBlocks, const string &arrayName)
{
    for (auto &commonBlockPair : commonBlocks)
        for (auto &variable : commonBlockPair.second.getVariables())
            if (variable.getName() == arrayName)
                return true;

    return false;
}

static void recursiveFill(SgExpression *exp,
                          const string &functionName,
                          const map<string, CommonBlock> &commonBlocks,
                          map<string, set<string>> &localArrayFound,
                          set<string> &commonArrayFound)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            string arrayName = string(exp->symbol()->identifier());

            if (isInCommon(commonBlocks, arrayName))
            {
                commonArrayFound.insert(arrayName);
                allUsedCommonArrays.insert(arrayName);
            }
            else
            {
                auto it = localArrayFound.find(functionName);
                if (it == localArrayFound.end())
                    it = localArrayFound.insert(it, make_pair(functionName, set<string>()));

                it->second.insert(arrayName);
            }
        }

        recursiveFill(exp->rhs(), functionName, commonBlocks, localArrayFound, commonArrayFound);
        recursiveFill(exp->lhs(), functionName, commonBlocks, localArrayFound, commonArrayFound);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions, const map<string, CommonBlock> &commonBlocks)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    for (auto &region : regions)
    {
        map<string, set<string>> localArrayFound;
        set<string> commonArrayFound;

        for (auto &fileLines : region->GetAllLines())
        {
            // switch to current file
            if (switchToFile(fileLines.first) != -1)
            {
                for (auto &regionLines : fileLines.second)
                {
                    // int iteratorLine = regionLines.lines.first;
                    // int endLine = regionLines.lines.second;
                    SgStatement *iterator = regionLines.stats.first;
                    SgStatement *end = regionLines.stats.second;
                    string functionName = "";

                    // implicit lines
                    if (!iterator)
                        continue;

                    while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
                        iterator = iterator->controlParent();

                    functionName = iterator->symbol()->identifier();
                    iterator = regionLines.stats.first;

                    // need to check implicit lines too!
                    for (; iterator && iterator != end; iterator = iterator->lexNext())
                    {
                        if (isSPF_stat(iterator) || isDVM_stat(iterator))
                            continue;

                        for (int i = 0; i < 3; ++i)
                            recursiveFill(iterator->expr(i), functionName, commonBlocks, localArrayFound, commonArrayFound);
                    }
                }
            }
        }

        string toPrint = "";
        for (auto &elem : localArrayFound)
        {
            toPrint += "function '" + elem.first + "': ";
            for (auto &arrayName : elem.second)
            {
                region->AddLocalArray(elem.first, arrayName);
                toPrint += arrayName + " ";
            }
        }

        if (toPrint != "")
            __spf_print(1, "[%s]: local arrays: %s\n", region->GetName().c_str(), toPrint.c_str());

        toPrint = "";
        for (auto &elem : commonArrayFound)
        {
            region->AddCommonArray(elem);
            toPrint += elem + " ";
        }

        if (toPrint != "")
            __spf_print(1, "[%s]: common arrays: %s\n", region->GetName().c_str(), toPrint.c_str());
    }

    string toPrint = "";
    for (auto &elem : allUsedCommonArrays)
        toPrint += elem + " ";

    if (toPrint != "")
        __spf_print(1, "all common arrays: %s\n", toPrint.c_str());
}

void fillRegionFunctions(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> allFuncInfo)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    // funcName -> funcInfo
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (auto &region : regions)
    {
        for (auto &functionName : region->GetAllFuncCalls())
        {
            auto func = funcMap.find(functionName);
            if (func != funcMap.end())
            {
                auto callingRegions = getRegionByLine2(regions, func->second->fileName, func->second->linesNum.first);
                if (callingRegions.size() > 1)
                    region->AddCrossedFunc(functionName);
            }
        }

        string toPrint = "";
        for (auto &elem : region->GetCrossedFuncs())
            toPrint += elem + " ";

        if (toPrint != "")
            __spf_print(1, "[%s]: crossed functions: %s\n", region->GetName().c_str(), toPrint.c_str());
    }

    for (auto &funcPair : funcMap)
    {
        bool callsFromRegion = false;
        bool callsFromCode = false;

        for (auto &call : funcPair.second->callsTo)
            if (getRegionByLine2(regions, call->fileName, call->linesNum.first).size())
                callsFromRegion = true;
            else
                callsFromCode = true;

        if (callsFromCode && callsFromRegion)
            allCommonFunctions.insert(funcPair.first);
    }

    string toPrint = "";
    for (auto &elem : allCommonFunctions)
        toPrint += elem + " ";

    if (toPrint != "")
        __spf_print(1, "all common functions: %s\n", toPrint.c_str());
}

void resolveRegions(const vector<ParallelRegion*> &regions)
{

}