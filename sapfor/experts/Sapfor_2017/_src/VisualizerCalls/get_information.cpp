#ifdef NDEBUG
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <assert.h>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "../Utils/errors.h"
#include "../Utils/version.h"
#include "get_information.h"
#include "dvm.h"
#include "../Sapfor.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../GraphCall/graph_calls_func.h"
#include "../Utils/utils.h"
#include "../Sapfor.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "SendMessage.h"
#include "../Predictor/PredictScheme.h"
#include "../DynamicAnalysis/gcov_info.h"
#include "../DynamicAnalysis/gCov_parser_func.h"

using std::string;
using std::wstring;
using std::map;
using std::set;
using std::vector;
using std::pair;
using std::tuple;
using std::to_string;

static void setOptions(const int *options)
{
    //staticShadowAnalysis = options[STATIC_SHADOW_ANALYSIS];
    staticPrivateAnalysis = options[STATIC_PRIVATE_ANALYSIS];
    out_free_form = options[FREE_FORM];
    keepDvmDirectives = 0;// options[KEEP_DVM_DIRECTIVES];
    keepSpfDirs = options[KEEP_SPF_DIRECTIVES];
    parallizeFreeLoops = options[PARALLIZE_FREE_LOOPS];
    //out_upper_case = 1;
}

static int strLen(const short *shString)
{
    int t = 0;
    if (shString == NULL)
        return 0;

    while (shString[t] != '|')
        t++;
    return t;
}

static bool tryOpenProjectFile(const char *project)
{
    bool ret = true;
    FILE *f = fopen(project, "rb");
    if (f == NULL)
        ret = false;
    else
        fclose(f);
    return ret;
}

static void ConvertShortToChar(const short *projName, int &strL, char *&prName)
{
    if (projName == NULL)
        return;

    strL = strLen(projName);
    prName = new char[strL + 1];

    for (int i = 0; i < strL; ++i)
        prName[i] = (char)projName[i];
    prName[strL] = '\0';
}

static void copyStringToShort(short *&result, const string &resVal, bool withEnd = true)
{
    result = new short[resVal.size() + 1];
    for (int i = 0; i < resVal.size(); ++i)
        result[i] = resVal[i];

    if (withEnd)
        result[resVal.size()] = (short)'\0';
}

int passDone = 0;
static int rethrow = 0;
static void runPassesLoop(const vector<passes> &passesToRun, const char *prName, const char *folderNameChar)
{    
    try
    {
        setPassValues();
        printf("SAPFOR: all passes num %zd\n", passesToRun.size());
        for (int i = 0; i < passesToRun.size(); ++i)
        {
            printf("SAPFOR: run pass %d -> %s\n", passesToRun[i], passNames[passesToRun[i]]);
            runPass(passesToRun[i], prName, folderNameChar);
        }
    }
    catch (boost::thread_interrupted&)
    {
        printf("SAPFOR: thread was terminated\n");
        fflush(NULL);
        return;
    }
    catch (int ex)
    {
        __spf_print(1, "catch code %d\n", ex);
        rethrow = ex;
    }
    catch (...)
    {
        rethrow = -1;
    }

    printf("SAPFOR: exit with pass == 1\n");
    passDone = 1;
}

static void runPassesForVisualizer(const short *projName, const vector<passes> &passesToRun, const short *folderName = NULL)
{
    int strL = 0, strF = 0;
    char *prName = NULL;
    char *folderNameChar = NULL;
    ConvertShortToChar(projName, strL, prName);
    ConvertShortToChar(folderName, strF, folderNameChar);

    try
    {
        if (strL == 0)
        {
            prName = new char[16];
            sprintf(prName, "dvm.proj");
        }
        
        if (tryOpenProjectFile(prName) == false)
            throw (-1);
             
        passDone = 0;
        rethrow = 0;
        boost::thread thread { runPassesLoop, passesToRun, prName, folderNameChar };
        int timeToWait = 10;
        int steps = 0;
        while (passDone == 0)
        {
            FILE *interrupt = fopen("INTERRUPT", "r");
            if (interrupt)
            {
                printf("SAPFOR: file exists, start interruption\n");
                fflush(NULL);
                thread.interrupt();
                fclose(interrupt);
                passDone = 2;
            }
            //printf("SAPFOR: sleep %d ms\n", timeToWait);
            _sleep(timeToWait);
            
            if (steps > 4)
            {
                if (timeToWait < 1000)
                    timeToWait *= 2;
                steps = 0;
            }
            else 
                steps++;
        }
        
        printf("SAPFOR: start wait thread join, pass == %d\n", passDone);
        thread.join();
        printf("SAPFOR: end wait thread join\n");

        if (passDone == 2)
            rethrow = 1;
    }
    catch (...)
    {
        rethrow = -1;
    }

    if (prName)
        delete []prName;
    if (folderNameChar)
        delete []folderNameChar;
    
    if (rethrow == 1)
    {
        printf("SAPFOR: rethrow\n");
        fflush(NULL);
        throw -99;
    }
    else if (rethrow != 0)
        throw rethrow;
}

extern map<string, vector<LoopGraph*>> loopGraph; // file -> Info
int SPF_GetGraphLoops(int winHandler, int *options, short *projName, short *&result, short *&output, int *&outputSize, 
                      short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;    
    try
    {
        runPassesForVisualizer(projName, { LOOP_GRAPH } );

        string resVal = "";
        for (auto f = loopGraph.begin(); f != loopGraph.end(); ++f)
        {
            if (resVal != "")
                resVal += "|";
            
            int realLoops = 0;
            for (int i = 0; i < f->second.size(); ++i)
                if (f->second[i]->lineNum > 0)
                    realLoops++;

            resVal += f->first + "|" + to_string(realLoops);
            for (int i = 0; i < f->second.size(); ++i)
            {
                string localRes = "";
                convertToString(f->second[i], localRes);
                resVal += localRes;
            }
        }

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size() + 1;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); } catch (...) { }
        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");

    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, vector<FuncInfo*>> allFuncInfo; // file -> Info  
int SPF_GetGraphFunctions(int winHandler, int *options, short *projName, short *&result, short *&output, int *&outputSize, 
                          short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;    
    try
    {
        runPassesForVisualizer(projName, { FILL_PAR_REGIONS_LINES } );
         
        string resVal = "";
        resVal = to_string(allFuncInfo.size());
        for (auto f = allFuncInfo.begin(); f != allFuncInfo.end(); ++f)
        {
            resVal += "|" + f->first + "|" + to_string(f->second.size());
            for (int i = 0; i < f->second.size(); ++i)
                resVal += convertToString(f->second[i]);
        }

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size() + 1;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); } catch (...) { }
        if (ex == -99)
            return -99;
        else
            retSize = -1;   
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");

    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_GetGraphVizOfFunctions(int *options, short *projName, short *&result, short *&output, int *&outputSize,
                               short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;
    try
    {
        runPassesForVisualizer(projName, { FILL_PAR_REGIONS_LINES });

        map<string, CallV> V;
        vector<string> E;
        CreateCallGraphViz(NULL, allFuncInfo, V, E);
        
        string graph = to_string(V.size()) += "|";
        for (auto &v : V)
            graph += v.second.to_string() + "|";

        graph += to_string(E.size()) + "|";
        for (auto &e : E)
            graph += e + "|";
        //erase last "|"
        graph.erase(graph.end() - 1);

        copyStringToShort(result, graph, false);
        retSize = (int)graph.size();
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); }
        catch (...) {}
        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    //convertGlobalBuffer(output, outputSize);
    //convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");

    MessageManager::setWinHandler(-1);
    return retSize;
}

extern int PASSES_DONE[EMPTY_PASS];
extern int *ALGORITHMS_DONE[EMPTY_ALGO];
extern const char *passNames[EMPTY_PASS + 1];

int SPF_GetPassesState(int *&passInfo)
{
    MessageManager::clearCache();
    passInfo = PASSES_DONE;
    return EMPTY_PASS;
}

int SPF_GetPassesStateStr(short *&passInfo)
{
    MessageManager::clearCache();
    string donePasses = "";
    for (int i = 0; i < EMPTY_PASS; ++i)
    {
        printf("SAPFOR: pass %d is %d with name %s\n", 1, PASSES_DONE[i], passNames[i]);
        if (PASSES_DONE[i] == 1)
        {
            donePasses += passNames[i] + string("|");
        }
    }

    //erase last "|"
    if (donePasses != "" && donePasses[donePasses.size() - 1] == '|')
        donePasses.erase(donePasses.end() - 1);

    copyStringToShort(passInfo, donePasses);
    return (int)donePasses.size();
}


extern std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaratedArrays;
static void printDeclArraysState()
{
    printf("SAPFOR: decl state: \n");
    int dist = 0, priv = 0, err = 0;
    for (auto it = declaratedArrays.begin(); it != declaratedArrays.end(); ++it)
    {
        if (it->second.first->GetNonDistributeFlag() == false)
            //printf("array '%s' is DISTR\n", it->second.first->GetShortName().c_str());
            dist++;
        else if (it->second.first->GetNonDistributeFlag() == true)
            //printf("array '%s' is PRIVATE\n", it->second.first->GetShortName().c_str());
            priv++;
        else
            //printf("array '%s' is ERROR\n", it->second.first->GetShortName().c_str());
            err++;        
    }
    printf("   PRIV %d, DIST %d, ERR %d, ALL %d\n", priv, dist, err, dist + priv + err);
}

extern vector<ParallelRegion*> parallelRegions;
extern uint64_t currentAvailMemory;
extern int QUALITY;
extern int SPEED;
int SPF_GetArrayDistribution(int winHandler, int *options, short *projName, short *&result, short *&output, int *&outputSize,
                             short *&outputMessage, int *&outputMessageSize, uint64_t availMemory, int quality_1, int quality_2, int onlyAnalysis)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    printDeclArraysState();
    clearGlobalMessagesBuffer();
    setOptions(options);

    //use only 80% of available memory
    currentAvailMemory = availMemory * 0.8;
    int retSize = -1;
    try
    {
        printf("SAPFOR: current quality = %d, speed = %d\n", quality_1, quality_2);
        if (quality_1 >= 0 && quality_1 <= 100)
            QUALITY = quality_1;
        else
            QUALITY = 0;
        
        if (quality_2 >= 0 && quality_2 <= 100)
            SPEED = quality_2;
        else
            SPEED = 0;

        if (onlyAnalysis)
            runPassesForVisualizer(projName, { LOOP_ANALYZER_DATA_DIST_S1 });
        else
            runPassesForVisualizer(projName, { CREATE_DISTR_DIRS });

        string resVal = "";
        resVal += to_string(parallelRegions.size());
        for (int i = 0; i < parallelRegions.size(); ++i)
            resVal += parallelRegions[i]->toString();

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size() + 1;
    }
    catch (int ex)
    {
        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL with code %d\n", retSize);
    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, PredictorStats> allPredictorStats;
extern SgProject *project;
extern map<string, vector<SpfInterval*>> intervals;
extern vector<vector<long>> topologies;

int SPF_CreateParallelVariant(int winHandler, int *options, short *projName, short *folderName, int64_t *variants, int *varLen,
                              short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize, short *&predictorStats)
{
    MessageManager::clearCache();
    if (folderName == NULL)
        MessageManager::setWinHandler(-1);
    else
        MessageManager::setWinHandler(winHandler);

    allPredictorStats.clear();
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = 0;
    try
    {
        if (varLen == NULL || variants == NULL)
            throw (-2);
        if ((*varLen % 3) != 0)
            throw (-5);

        map<int, vector<pair<int64_t, int64_t>>> varLens;
        for (int i = 0, k = 0; i < *varLen; i += 3, ++k)
        {
            printf("SAPFOR: input pack %d: %lld %lld %lld\n", k, variants[i], variants[i + 1], variants[i + 2]);
            varLens[(int)variants[i + 2]].push_back(std::make_pair(variants[i], variants[i + 1]));
        }

        if (varLens.size() != parallelRegions.size())
            throw (-6);

        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            auto it = varLens.find(parallelRegions[z]->GetId());
            if (it == varLens.end())
                throw (-7);

            const vector<pair<int64_t, int64_t>> &currVars = it->second;
            const DataDirective &dataDirectives = parallelRegions[z]->GetDataDir();

            vector<int> currentVariant(dataDirectives.distrRules.size());
            if (currVars.size() != dataDirectives.distrRules.size())
            {
                printf("SAPFOR: currV %d, dataDirectives.distrRules %d\n", (int)currVars.size(), (int)dataDirectives.distrRules.size());
                throw (-3);
            }

            map<int64_t, int> varMap;
            for (int i = 0; i < currVars.size(); ++i)
                varMap[currVars[i].first] = (int)currVars[i].second;

            map<int64_t, int> templateIdx;
            for (int i = 0; i < dataDirectives.distrRules.size(); ++i)
            {
                printf("SAPFOR: template address %lld with num %d\n", (int64_t)dataDirectives.distrRules[i].first, i);
                templateIdx[(int64_t)dataDirectives.distrRules[i].first] = i;
            }

            for (auto it = varMap.begin(); it != varMap.end(); ++it)
            {
                auto itF = templateIdx.find(it->first);
                if (itF == templateIdx.end())
                    throw (-4);

                printf("SAPFOR: found %lld address\n", it->first);
                currentVariant[itF->second] = it->second;
            }
            parallelRegions[z]->SetCurrentVariant(currentVariant);
        }

        printf("SAPFOR: set all info done\n");
        runPassesForVisualizer(projName, { INSERT_PARALLEL_DIRS }, folderName);

        string predictRes = "";
        PredictorStats summed;
        for (auto &predFile : allPredictorStats)
        {
            summed.IntervalCount += predFile.second.IntervalCount;
            summed.ParallelCount += predFile.second.ParallelCount;
            summed.RedistributeCount += predFile.second.RedistributeCount;
            summed.RemoteCount += predFile.second.RemoteCount;
            summed.ParallelStat.AcrossCount += predFile.second.ParallelStat.AcrossCount;
            summed.ParallelStat.ReductionCount += predFile.second.ParallelStat.ReductionCount;
            summed.ParallelStat.RemoteCount += predFile.second.ParallelStat.RemoteCount;
            summed.ParallelStat.ShadowCount += predFile.second.ParallelStat.ShadowCount;
        }
        predictRes += summed.to_string();

        if (folderName == NULL)
        {
            SpfInterval *mainIterval = getMainInterval(project, intervals);
            const int idxBest = mainIterval->getBestTimeIdx();
            double speedUpBest = 1;
            int procCount = 1;
            string topo = "";
            if (idxBest != -1 && mainIterval->exec_time != 0)
            {
                speedUpBest = mainIterval->exec_time / mainIterval->predictedTimes[idxBest];
                topo += "[";
                for (int z = 0; z < topologies[idxBest].size(); ++z)
                {
                    topo += to_string(topologies[idxBest][z]);
                    procCount *= topologies[idxBest][z];
                    if (z != topologies[idxBest].size() - 1)
                        topo += "x";
                }
                topo += "]";
            }
            char buf[256];
            sprintf(buf, "%.2f", speedUpBest / procCount * 100.0);
            predictRes += "|" + string(buf) + topo;
        }
        else
            predictRes += "|0";

        copyStringToShort(predictorStats, predictRes);
        retSize = (int)predictRes.size();
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); } catch (...) { }
        if (ex == -99)
            return -99;
        else
            retSize = -1;
        retSize = ex;
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_GetVersionAndBuildDate(short *&result)
{
    MessageManager::clearCache();
    string resVal = "";
    resVal += string(VERSION) + " |" + __DATE__ + "| |" +__TIME__ + "| ";

    copyStringToShort(result, resVal);
    return (int)resVal.size() + 1;
}

extern set<string> intrinsicF;
extern void initIntrinsicFunctionNames();

int SPF_GetIntrinsics(short *&result)
{
    MessageManager::clearCache();
    initIntrinsicFunctionNames();

    string resVal = "";
    
    for (auto it = intrinsicF.begin(); it != intrinsicF.end(); ++it)
    {
        if (it != intrinsicF.begin())
            resVal += " " + *it;
        else
            resVal += *it;
    }

    copyStringToShort(result, resVal);
    return (int)resVal.size() + 1;
}

extern map<string, set<string>> includeDependencies;
int SPF_GetIncludeDependencies(int winHandler, int *options, short *projName, short *&result)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    string resVal = "";

    setOptions(options);
    int retSize = 0;
    try
    {
        runPassesForVisualizer(projName, { BUILD_INCLUDE_DEPENDENCIES });

        int i = 0;
        for (auto &deps : includeDependencies)
        {
            if (i != 0)
                resVal += "@";
            resVal += deps.first + "@";
            int k = 0;
            for (auto &incl : deps.second)
            {
                if (k != 0)
                    resVal += "|";
                resVal += incl;
                ++k;
            }
            ++i;
        }

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size() + 1;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); } catch (...) { }
        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_SetFunctionsToInclude(int winHandler, int *options, short *projName, short *&result, short *&output, int *&outputSize,
                              short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;
    try
    {
        runPassesForVisualizer(projName, { FIND_FUNC_TO_INCLUDE });

        string resVal = "";
        resVal = to_string(allFuncInfo.size());
        for (auto f = allFuncInfo.begin(); f != allFuncInfo.end(); ++f)
        {
            resVal += "|" + f->first + "|" + to_string(f->second.size());
            for (int i = 0; i < f->second.size(); ++i)
                resVal += convertToString(f->second[i]);
        }

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size() + 1;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); } catch (...) { }
        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_GetAllDeclaratedArrays(int winHandler, int *options, short *projName, short *&result, short *&output, int *&outputSize,
                               short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;
    try
    {
        runPassesForVisualizer(projName, { GET_ALL_ARRAY_DECL });

        string resVal = "";
        for (auto f = declaratedArrays.begin(); f != declaratedArrays.end(); ++f)
        {
            if (f != declaratedArrays.begin())
                resVal += "@";
            resVal += f->second.first->toString();
        }

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size() + 1;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); } catch(...) { }

        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, int> lineInfo;
int SPF_GetFileLineInfo(int winHandler, int *options, short *projName, short *&result, short *&output, int *&outputSize,
                         short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;
    try
    {
        runPassesForVisualizer(projName, { FILE_LINE_INFO });

        string resVal = "";
        for (auto it = lineInfo.begin(); it != lineInfo.end(); ++it)
        {
            if (it != lineInfo.begin())
                resVal += "@";
            resVal += it->first + "@" + to_string(it->second);
        }

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size() + 1;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); } catch (...) { }
        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_SetDistributionFlagToArray(char *key, int flag)
{
    MessageManager::clearCache();

    if (flag != 0 && flag != 1)
        return 0;

    string keyStr(key);
    try
    {
        for (auto &array : declaratedArrays)
        {
            if (array.second.first->GetName() == keyStr)
            {
                __spf_print(1, "change flag for array '%s': %d -> %d\n", array.second.first->GetName().c_str(), array.second.first->GetNonDistributeFlag(), flag);
                printf("SAPFOR: change flag for array '%s': %d -> %d\n", array.second.first->GetName().c_str(), array.second.first->GetNonDistributeFlag(), flag);

                if (flag == 0)
                    array.second.first->SetNonDistributeFlag(DIST::DISTR);
                else
                    array.second.first->SetNonDistributeFlag(DIST::NO_DISTR);
                break;
            }
        }
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}

static int simpleTransformPass(const passes PASS_NAME, int *options, short *projName, short *folderName,
                               short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retCode = 0;
    try
    {
        PASSES_DONE[PASS_NAME] = 0;
        runPassesForVisualizer(projName, { PASS_NAME }, folderName);
    }
    catch (int ex)
    {
        __spf_print(1, "catch code %d\n", ex);
        if (ex == -99)
            return -99;
        else
            retCode = -1;
    }
    catch (...)
    {
        retCode = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retCode;
}


int SPF_CorrectCodeStylePass(int winHandler, int *options, short *projName, short *folderName, short *&output, 
                             int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(CORRECT_CODE_STYLE, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_ResolveParallelRegionConflicts(int winHandler, int *options, short *projName, short *folderName, short *&output,
                                       int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(RESOLVE_PAR_REGIONS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_PrivateExpansion(int winHandler, int *options, short *projName, short *folderName, short *&output,
                         int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(PRIVATE_ARRAYS_BREEDING, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_LoopFission(int winHandler, int *options, short *projName, short *folderName, short *&output,
                    int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(LOOPS_SPLITTER, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_CreateIntervalsTree(int winHandler, int *options, short *projName, short *folderName, short *&output,
                            int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(INSERT_INTER_TREE, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_RemoveDvmDirectives(int winHandler, int *options, short *projName, short *folderName, short *&output, 
                            int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(REMOVE_DVM_DIRS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_RemoveDvmDirectivesToComments(int winHandler, int *options, short *projName, short *folderName, short *&output, 
                                      int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(REMOVE_DVM_DIRS_TO_COMMENTS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_RemoveDvmIntervals(int winHandler, int *options, short *projName, short *folderName, short *&output, 
                           int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(REMOVE_DVM_INTERVALS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

extern tuple<string, int, int, int> inData;
extern map<string, string> outData;
int SPF_ChangeSpfIntervals(int winHandler, int *options, short *projName, short *folderName, short *&output,
                           int *&outputSize, short *&outputMessage, int *&outputMessageSize, 
                           short *fileNameToMod, int *toModifyLines,
                           int &size, int *&sizes, short *&newFilesNames, short *&newFiles)
{
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retCode = 0;
    try
    {
        int strL;
        char *filtrName;
        ConvertShortToChar(fileNameToMod, strL, filtrName);
        std::get<0>(inData) = filtrName;
        std::get<1>(inData) = toModifyLines[0];
        std::get<2>(inData) = toModifyLines[1];
        std::get<3>(inData) = toModifyLines[2];

        PASSES_DONE[EXPAND_EXTRACT_PAR_REGION] = 0;
        runPassesForVisualizer(projName, { EXPAND_EXTRACT_PAR_REGION }, folderName);

        //fill data
        // size - ����� ������ ��� ���.
        // sizes - ������� ������ � ������ newFiles
        // newFilesNames - ����� ������ ��� ���., ����. '|'
        // newFiles - �����
    }
    catch (int ex)
    {
        __spf_print(1, "catch code %d\n", ex);
        if (ex == -99)
            return -99;
        else
            retCode = -1;
    }
    catch (...)
    {
        retCode = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retCode;
}

extern set<string> filesToInclude;
int SPF_InsertIncludesPass(int winHandler, int *options, short *projName, short *folderName, char *filesToInclude, 
                           short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);

    if (filesToInclude == NULL)
        return -2;

    vector<string> splited;
    //printf("%s\n", conv);
    splitString(filesToInclude, '|', splited);

    if (splited.size() == 0)
        return -3;

    ::filesToInclude.clear();
    for (int i = 0; i < splited.size(); ++i)
    {
        ::filesToInclude.insert(splited[i]);
        __spf_print(1, "file = %s\n", splited[i].c_str());
    }
    return simpleTransformPass(INSERT_INCLUDES, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_LoopEndDoConverterPass(int winHandler, int *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);

    return simpleTransformPass(CONVERT_TO_ENDDO, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

extern map<string, map<int, Gcov_info>> gCovInfo;
int SPF_GetGCovInfo(int winHandler, int *options, short *projName, short *&result, short *&output, int *&outputSize,
                    short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;
    try
    {
        runPassesForVisualizer(projName, { GCOV_PARSER });

        string resVal = "";
        bool first = true;
        for (auto &byFile : gCovInfo)
        {
            if (!first)
                resVal += "@";
            resVal += byFile.first + "@";
            for (auto &elem : byFile.second)
                resVal += to_string(elem.first) + " " + to_string(elem.second.getExecutedCount()) + " ";            
            first = false;
        }

        copyStringToShort(result, resVal);
        retSize = (int)resVal.size();
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); }
        catch (...) {}

        if (ex == -99)
            return -99;
        else
            retSize = -1;
    }
    catch (...)
    {
        retSize = -1;
    }

    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);

    printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
    
}

extern void deleteAllAllocatedData(bool enable);
void SPF_deleteAllAllocatedData()
{
    MessageManager::clearCache();
    deleteAllAllocatedData(true);
}

void createNeededException()
{
    if (passDone == 2)
        throw boost::thread_interrupted();
}
#endif