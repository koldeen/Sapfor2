#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <map>
#include <vector>
#include <set>
#include <string>

#include "../Utils/errors.h"
#include "graph_calls.h"
#include "../Distribution/Distribution.h"

using std::vector;
using std::map;
using std::string;
using std::set;
using std::to_string;
using std::tuple;
using std::pair;

void createMapOfFunc(const vector<FuncInfo*> &allFuncInfo, map<pair<string, int>, FuncInfo*> &mapFuncInfo)
{
    for (auto &func : allFuncInfo)
        mapFuncInfo[make_pair(func->fileName, func->linesNum.first)] = func;
}

void createMapOfFunc(const vector<FuncInfo*> &allFuncInfo, map<string, FuncInfo*> &mapFuncInfo)
{
    for (auto &func : allFuncInfo)
        mapFuncInfo[func->funcName] = func;
}

void createMapOfFunc(const map<string, vector<FuncInfo*>> &allFuncInfo, map<string, FuncInfo*> &mapFuncInfo)
{
    for (auto it = allFuncInfo.begin(); it != allFuncInfo.end(); ++it)
        for (int k = 0; k < it->second.size(); ++k)
            mapFuncInfo[it->second[k]->funcName] = it->second[k];
}

string removeString(const string &toRemove, const string &inStr)
{
    string outStr(inStr);
    const size_t found = outStr.find(toRemove);
    if (found != string::npos)
        outStr.erase(found, toRemove.length());
    return outStr;
}

void updateFuncInfo(const map<string, vector<FuncInfo*>> &allFuncInfo) // const here
{
    bool changesDone = false;
    map<string, FuncInfo*> mapFuncInfo;
    createMapOfFunc(allFuncInfo, mapFuncInfo);

    do
    {
        changesDone = false;
        for (auto &it : mapFuncInfo)
        {
            FuncInfo *currInfo = it.second;
            for(auto &funcCall : currInfo->funcsCalledFromThis)
            {
                // Find pointer to info of called function
                auto itCalledFunc = mapFuncInfo.find(funcCall.CalledFuncName);

                if (itCalledFunc != mapFuncInfo.end())
                {
                    FuncInfo *calledFunc = itCalledFunc->second;

                    // check for io usage
                    if (calledFunc->usesIO && !currInfo->usesIO) {
                    	currInfo->usesIO = true;
                    	changesDone = true;
                    }

                    // check for pureness
                    if (!calledFunc->isPure && currInfo->isPure) {
                    	currInfo->isPure = false;
                    	changesDone = true;
                    }

                    // check for using parameter as index

                    // Iterate through all pars of the call
                    int parNo = 0;

                    for (auto &parOfCalled : funcCall.NoOfParamUsedForCall)
                    {
                        // If this par of called func is used as index change
                        if (calledFunc->isParamUsedAsIndex[parNo])
                        {
                            // Then pars of calling func which are used in this par of called
                            // are also used as index
                            for (auto &parOfCalling : parOfCalled)
                            {
                                if (!currInfo->isParamUsedAsIndex[parOfCalling])
                                {
                                    changesDone = true;
                                    currInfo->isParamUsedAsIndex[parOfCalling] = true;
                                }
                            }
                        }
                        parNo++;
                    }
                }
                //else // Error! No funcInfo of called func
                //     ;
            }
        }
    } while (changesDone);
}

int CreateCallGraphViz(const char *fileName, const map<string, vector<FuncInfo*>> &funcByFile, map<string, CallV> &V, vector<string> &E)
{
    map<string, FuncInfo*> allFuncs;
    createMapOfFunc(funcByFile, allFuncs);

    string graph = "";
    graph += "digraph G{\n";

    auto it = funcByFile.begin();
    int fileNum = 0;
    set<string> inCluster;
    set<string> unknownCluster;

    char buf[1024];
    while (it != funcByFile.end())
    {
        sprintf(buf, "subgraph cluster%d {\n", fileNum);
        graph += buf;

        const int dimSize = (int)it->second.size();
        set<string> uniqNames;
        for (int k = 0; k < dimSize; ++k)
        {
            const string currfunc = it->second[k]->funcName;
            auto it = uniqNames.find(currfunc);
            if (it == uniqNames.end())
            {
                uniqNames.insert(it, currfunc);
                inCluster.insert(currfunc);
                sprintf(buf, "\"%s\"\n", currfunc.c_str());
                graph += buf;
            }
        }
        sprintf(buf, "label = \"file <%s>\"\n", removeString(".\\", it->first).c_str());
        graph += buf;
        graph += "}\n";

        fileNum++;
        it++;
    }

    it = funcByFile.begin();
    while (it != funcByFile.end())
    {
        const char *formatString = "\"%s\" -> \"%s\" [minlen=2.0];\n";
        const int dimSize = (int)it->second.size();
        for (int k = 0; k < dimSize; ++k)
        {
            const string &callFrom = it->second[k]->funcName;
            const FuncInfo *callFromP = it->second[k];

            for (auto &callItem : it->second[k]->callsFrom)
            {
                sprintf(buf, formatString, callFrom.c_str(), callItem.c_str());
                graph += buf;

                if (inCluster.find(callFrom) == inCluster.end())
                    unknownCluster.insert(callFrom);
                if (inCluster.find(callItem) == inCluster.end())
                    unknownCluster.insert(callItem);

                if (V.find(callFrom) == V.end())
                {
                    V[callFrom] = CallV(callFromP->funcName, callFromP->fileName, callFromP->isMain);
                    V[callFrom].inRegion = callFromP->inRegion;
                }

                if (V.find(callItem) == V.end())
                {
                    auto it = allFuncs.find(callItem);
                    if (it == allFuncs.end())
                        V[callItem] = CallV(callItem);
                    else
                    {
                        auto currF = it->second;
                        V[callItem] = CallV(callItem, currF->fileName, currF->isMain);
                        V[callItem].inRegion = currF->inRegion;
                    }
                }


                E.push_back(callFrom);
                E.push_back(callItem);
            }
        }
        it++;
    }

    if (unknownCluster.size() > 0)
    {
        sprintf(buf, "subgraph cluster%d {\n", fileNum);
        graph += buf;

        for (auto &func : unknownCluster)
        {
            sprintf(buf, "\"%s\"\n", func.c_str());
            graph += buf;
        }
        sprintf(buf, "label = \"file <UNKNOWN>\"\n");
        graph += buf;
        graph += "}\n";
    }

    graph += "overlap=false\n";
    graph += "}\n";

    if (fileName)
    {
        FILE *out = fopen(fileName, "w");
        if (out == NULL)
        {
            __spf_print(1, "can not open file %s\n", fileName);
            return -1;
        }

        fprintf(out, graph.c_str());
        fclose(out);
    }
    return 0;
}

int CreateFuncInfo(const char *fileName, const map<string, vector<FuncInfo*>> &funcByFile)
{
    string funcOut = "";
    for (auto &byFile : funcByFile)
    {
        funcOut += "FILE " + byFile.first + ":\n";
        for (auto &func : byFile.second)
        {
            funcOut += "  FUNCTION '" + func->funcName + "'\n";
            char buf[256];
            sprintf(buf, "    LINES [%d, %d] \n", func->linesNum.first, func->linesNum.second);
            funcOut += buf;
            sprintf(buf, "    PARAMETERS %d:\n", func->funcParams.countOfPars);
            funcOut += buf;
            for (int z = 0; z < func->funcParams.countOfPars; ++z)
            {
                bool in = func->funcParams.isArgIn(z);
                bool out = func->funcParams.isArgOut(z);
                const char *inout = "";
                if (in && out)
                    inout = "IN/OUT";
                else if (in)
                    inout = "IN";
                else if (out)
                    inout = "OUT";

                sprintf(buf, "      %s: type '%s', %s\n", func->funcParams.identificators[z].c_str(),
                    paramNames[func->funcParams.parametersT[z]],
                    inout);
                funcOut += buf;
            }
        }
    }

    if (fileName)
    {
        FILE *out = fopen(fileName, "w");
        if (out == NULL)
        {
            __spf_print(1, "can not open file %s\n", fileName);
            return -1;
        }

        fprintf(out, funcOut.c_str());
        fclose(out);
    }
    return 0;
}

extern map<string, vector<FuncInfo*>> allFuncInfo; // file -> Info  
FuncInfo* isUserFunctionInProject(const string &func)
{
    FuncInfo *ret = NULL;
    for (auto &it : allFuncInfo)
    {
        for (auto &currF : it.second)
        {
            if (currF->funcName == func)
            {
                ret = currF;
                break;
            }
        }

        if (ret)
            break;
    }
    return ret;
}

string convertToString(const FuncInfo *currFunc)
{
    string result = "";
    if (currFunc)
    {
        result += "|" + currFunc->funcName + "|" + to_string(currFunc->linesNum.first) + 
            " " + to_string(currFunc->linesNum.second) +
            " " + to_string(currFunc->detailCallsFrom.size()) +
            " " + to_string(currFunc->needToInline) + " " + to_string(currFunc->doNotInline) + 
            " " + to_string(currFunc->doNotAnalyze) + " " + to_string((int)currFunc->isMain);

        for (int i = 0; i < currFunc->detailCallsFrom.size(); ++i)
            result += "|" + currFunc->detailCallsFrom[i].first + "|" + to_string(currFunc->detailCallsFrom[i].second);
    }
    return result;
}

// Find dead functions and fill callTo information
void findDeadFunctionsAndFillCallTo(map<string, vector<FuncInfo*>> &allFuncInfo, map<string, vector<Messages>> &allMessages, bool noPrint)
{
    map<string, FuncInfo*> mapFuncInfo;
    createMapOfFunc(allFuncInfo, mapFuncInfo);

    set<string> allChildCalls;
    for (auto &it : mapFuncInfo)
    {
        FuncInfo *currInfo = it.second;
        allChildCalls.insert(currInfo->callsFrom.begin(), currInfo->callsFrom.end());
    }

    for (auto &it : mapFuncInfo)
    {
        FuncInfo *currInfo = it.second;
        if (allChildCalls.find(it.first) == allChildCalls.end())
            if (!currInfo->isMain)
                currInfo->deadFunction = currInfo->doNotAnalyze = true;
    }

    if (!noPrint)
    {
        for (auto &it : allFuncInfo)
        {
            const string &currF = it.first;
            auto itM = allMessages.find(currF);
            if (itM == allMessages.end())
                itM = allMessages.insert(itM, make_pair(currF, vector<Messages>()));

            for (auto &func : it.second)
                if (func->deadFunction)
                    itM->second.push_back(Messages(NOTE, func->linesNum.first, "This function is not called in current project", 1015));
        }
    }

    for (auto &it : mapFuncInfo)
    {
        FuncInfo *currInfo = it.second;
        for (auto &k : currInfo->callsFrom)
        {
            auto itFound = mapFuncInfo.find(k);
            if (itFound != mapFuncInfo.end())
            {
                FuncInfo *callFrom = itFound->second;
                callFrom->callsTo.push_back(currInfo);
            }
        }
    }
}
