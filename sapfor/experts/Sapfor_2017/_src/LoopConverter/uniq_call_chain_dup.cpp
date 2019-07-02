#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>

#include "dvm.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"

#include "uniq_call_chain_dup.h"
#include "../GraphCall/graph_calls.h"
#include "../GraphCall/graph_calls_func.h"

using namespace std;

static bool checkUniqAndAdd(vector<vector<void*>> &vars, const vector<void*> &current)
{
    for (auto& elem : vars)
    {
        if (elem == current)
            return false;
    }

    vars.push_back(current);
    return true;
}

static vector<void*> createParamCalls(const pair<void*, int> &callPointer, const string &fileN)
{
    if (SgFile::switchToFile(fileN) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgExpression *callList = NULL;
    if (callPointer.second == PROC_STAT)
        callList = ((SgStatement*)callPointer.first)->expr(0);
    else if (callPointer.second == FUNC_CALL)
        callList = ((SgExpression*)callPointer.first)->lhs();
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    vector<void*> packCall;

    while (callList)
    {
        auto curr = callList->lhs();
        if (curr->variant() == ARRAY_REF)
        {
            SgSymbol* par = callList->lhs()->symbol();
            DIST::Array* array = getArrayFromDeclarated(declaratedInStmt(par), par->identifier());
            if (array)
            {
                if (array->GetNonDistributeFlag() == false)
                    packCall.push_back(array);
                else
                    packCall.push_back(NULL);
            }
            else
                packCall.push_back(NULL);
        }
        else
            packCall.push_back(NULL);
        callList = callList->rhs();
    }

    return packCall;
}

static map<FuncInfo*, int> countOfCalls(const map<string, vector<FuncInfo*>> &allFuncs, const map<string, FuncInfo*> &mapOfFunc)
{
    map<FuncInfo*, int> count;    
    map<FuncInfo*, vector<vector<void*>>> variantCall;

    for (auto& fromFile : allFuncs)
    {
        for (auto& elem : fromFile.second)
        {
            count[elem] = 0;
            variantCall[elem] = vector<vector<void*>>();
        }
    }

    for (auto& fromFile : allFuncs)
    {
        for (auto& elem : fromFile.second)
        {
            int p = 0;
            for (auto& detailed : elem->detailCallsFrom)
            {
                auto it = mapOfFunc.find(detailed.first);
                if (it != mapOfFunc.end())
                {
                    auto var = variantCall.find(it->second);
                    auto createPackCall = createParamCalls(elem->pointerDetailCallsFrom[p], elem->fileName);
                    if (checkUniqAndAdd(var->second, createPackCall))
                        count[it->second]++;
                }
                ++p;
            }
        }
    }
    return count;
}

static vector<FuncInfo*> detect(const map<string, vector<FuncInfo*>> &allFuncs, const map<string, FuncInfo*> &mapOfFunc)
{    
    vector<FuncInfo*> retVal;
    map<FuncInfo*, int> countOfCall = countOfCalls(allFuncs, mapOfFunc);

    for (auto &fromFile : allFuncs)
    {
        if (SgFile::switchToFile(fromFile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto &elem : fromFile.second)
        {
            SgProgHedrStmt *prog = isSgProgHedrStmt(elem->funcPointer->GetOriginal());
            checkNull(prog, convertFileName(__FILE__).c_str(), __LINE__);

            if (prog->variant() == PROG_HEDR)
                continue;

            if (countOfCall[elem] <= 1)
                continue;

            for (int z = 0; z < prog->numberOfParameters(); ++z)
            {
                SgSymbol *par = prog->parameter(z);
                
                DIST::Array *array = getArrayFromDeclarated(declaratedInStmt(par), par->identifier());
                if (array)
                {
                    if (array->GetNonDistributeFlag() == false)
                    {
                        retVal.push_back(elem);
                        break;
                    }
                }
            }
        }
    }

    return retVal;
}

static set<FuncInfo*> getFullCallsFrom(FuncInfo *from, const map<string, FuncInfo*> &mapOfFunc)
{
    set<FuncInfo*> callsFromFull;
    callsFromFull.insert(from);

    bool change = true;
    while (change)
    {
        change = false;
        set<FuncInfo*> newAdd;
        for (auto& func: callsFromFull)
        {
            for (auto& elem : func->callsFrom)
            {
                auto it = mapOfFunc.find(elem);
                if (it != mapOfFunc.end())
                {
                    auto it2 = callsFromFull.find(it->second);
                    if (callsFromFull.end() == it2)
                    {
                        newAdd.insert(it->second);
                        change = true;
                    }
                }
            }
        }

        for (auto& elem : newAdd)
            callsFromFull.insert(elem);
    }

    return callsFromFull;
}

static bool isAllDone(const vector<bool>& done)
{
    for (const auto& elem : done)
        if (elem == false)
            return false;
    return true;
}

static map<FuncInfo*, vector<FuncInfo*>> groupByMainCall(const vector<FuncInfo*> &toCopy, const map<string, FuncInfo*> &mapOfFunc)
{
    set<FuncInfo*> copySet(toCopy.begin(), toCopy.end());

    vector<bool> done(toCopy.size());
    std::fill(done.begin(), done.end(), false);

    map<FuncInfo*, vector<FuncInfo*>> groups;

    while (!isAllDone(done))
    {
        int z = 0;
        for (; z < done.size(); ++z)
        {
            if (!done[z])
            {
                for (auto& callsTo : toCopy[z]->callsTo)
                {
                    if (copySet.find(callsTo) != copySet.end())
                        continue;
                }
                done[z] = true;
                break;
            }
        }

        if (z == done.size() + 1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        groups[toCopy[z]] = vector<FuncInfo*>();

        set<FuncInfo*> fullCalls = getFullCallsFrom(toCopy[z], mapOfFunc);
        for (int p = 0; p < done.size(); ++p)
        {
            //self
            if (p == z)
                continue;

            if (fullCalls.find(toCopy[p]) != fullCalls.end())
            {
                groups[toCopy[z]].push_back(toCopy[p]);
                done[p] = true;
            }
        }
    }

    return groups;
}

void duplicateFunctions(const map<string, vector<FuncInfo*>> &allFuncs)
{
    map<string, FuncInfo*> mapOfFunc;
    createMapOfFunc(allFuncs, mapOfFunc);

    vector<FuncInfo*> toCopy = detect(allFuncs, mapOfFunc);
    map<FuncInfo*, vector<FuncInfo*>> toCopyGroups = groupByMainCall(toCopy, mapOfFunc);

    printf("");
}
