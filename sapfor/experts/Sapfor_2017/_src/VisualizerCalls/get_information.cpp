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

#include "get_information.h"
#include "dvm.h"
#include "../transform.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../GraphCall/graph_calls_func.h"
#include "../utils.h"
#include "../transform.h"
#include "../errors.h"
#include "../ParallelizationRegions/ParRegions.h"

using std::string;
using std::map;
using std::set;
using std::vector;
using std::pair;
using std::tuple;
using std::to_string;

static void setOptions(const int *options)
{
    if (options[STATIC_SHADOW_ANALYSIS] == 1)
        staticShadowAnalysis = 1;

    if (options[STATIC_PRIVATE_ANALYSIS] == 1)
        staticPrivateAnalysis = 1;

    if (options[FREE_FORM] == 1)
        out_free_form = 1;

    if (options[KEEP_DVM_DIRECTIVES] == 1)
        keepDvmDirectives = 1;

    if (options[KEEP_SPF_DIRECTIVES] == 1)
        keepSpfDirs = 1;
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
    strL = strLen(projName);
    prName = new char[strL + 1];

    for (int i = 0; i < strL; ++i)
        prName[i] = (char)projName[i];
    prName[strL] = '\0';
}

static void copyStringToShort(short *&result, const string &resVal)
{
    result = new short[resVal.size() + 1];
    for (int i = 0; i < resVal.size(); ++i)
        result[i] = resVal[i];
    result[resVal.size()] = (short)'\0';
}

int passDone = 0;
static int rethrow = 0;
static void runPassesLoop(const vector<passes> &passesToRun, const char *prName, const char *folderNameChar)
{
    try
    {
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
    int strL, strF;
    char *prName = NULL;
    char *folderNameChar = NULL;
    ConvertShortToChar(projName, strL, prName);
    ConvertShortToChar(folderName, strF, folderNameChar);
        
    fflush(NULL);
    try
    {
        if (strF == 0)
        {
            delete []folderNameChar;
            folderNameChar = NULL;
        }

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
int SPF_GetGraphLoops(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
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
            resVal += f->first + "|" + to_string(f->second.size());
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
        __spf_print(1, "catch code %d\n", ex);
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
    return retSize;
}

extern map<string, vector<FuncInfo*>> allFuncInfo; // file -> Info  
int SPF_GetGraphFunctions(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;    
    try
    {
        runPassesForVisualizer(projName, { CALL_GRAPH2 } );
         
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
        __spf_print(1, "catch code %d\n", ex);
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
    return retSize;
}

extern int PASSES_DONE[EMPTY_PASS];
extern int *ALGORITHMS_DONE[EMPTY_ALGO];

int SPF_GetPassesState(int *&passInfo)
{
    passInfo = PASSES_DONE;
    return EMPTY_PASS;
}

extern std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaratedArrays;
static void printDeclArraysState()
{
    printf("SAPFOR: decl state: \n");
    for (auto it = declaratedArrays.begin(); it != declaratedArrays.end(); ++it)
    {
        if (it->second.first->GetNonDistributeFlag() == false)
            printf("array '%s' is DISTR\n", it->second.first->GetShortName().c_str());
        else if (it->second.first->GetNonDistributeFlag() == true)
            printf("array '%s' is PRIVATE\n", it->second.first->GetShortName().c_str());
        else
            printf("array '%s' is ERROR\n", it->second.first->GetShortName().c_str());
    }
}

extern vector<ParallelRegion*> parallelRegions;
extern uint64_t currentAvailMemory;
extern int QUALITY;
int SPF_GetArrayDistribution(int *options, short *projName, short *&result, short *&output, int *&outputSize, 
                             short *&outputMessage, int *&outputMessageSize, uint64_t availMemory, int quality)
{
    printDeclArraysState();
    clearGlobalMessagesBuffer();
    setOptions(options);

    //use only 80% of available memory
    currentAvailMemory = availMemory * 0.8;
    int retSize = -1;
    try
    {
        printf("SAPFOR: current quality %d\n", quality);
        if (quality >= 0 && quality <= 100)
            QUALITY = quality;
        else
            QUALITY = 0;
                    
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
    return retSize;
}

int SPF_CreateParallelVariant(int *options, short *projName, short *folderName, int64_t *variants, int *varLen, 
                              short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
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
    }
    catch (int ex)
    {
        __spf_print(1, "catch code %d\n", ex);
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
    return retSize;
}

int SPF_GetVersionAndBuildDate(short *&result)
{
    string resVal = "";
    resVal += string(VERSION) + " |" + __DATE__ + "| |" +__TIME__ + "| ";

    copyStringToShort(result, resVal);
    return (int)resVal.size() + 1;
}

extern set<string> intrinsicF;
extern void initIntrinsicFunctionNames();

int SPF_GetIntrinsics(short *&result)
{
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
int SPF_GetIncludeDependencies(int *options, short *projName, short *&result)
{
    string resVal = "";

    setOptions(options);
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
    return (int)resVal.size() + 1;
}

int SPF_SetFunctionsToInclude(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
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
        __spf_print(1, "catch code %d\n", ex);
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
    return retSize;
}

int SPF_GetAllDeclaratedArrays(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
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
        __spf_print(1, "catch code %d\n", ex);
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
    return retSize;
}

extern map<string, int> lineInfo;
int SPF_GetFileLineInfo(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
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
        __spf_print(1, "catch code %d\n", ex);
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
    return retSize;
}

int SPF_SetDistributionFlagToArray(char *key, int flag)
{
    if (flag != 0 && flag != 1)
        return 0;

    string keyStr(key);
    for (auto it = declaratedArrays.begin(); it != declaratedArrays.end(); ++it)
    {
        if (it->second.first->GetName() == keyStr)
        {
            __spf_print(1, "change flag for array '%s': %d -> %d\n", it->second.first->GetName().c_str(), it->second.first->GetNonDistributeFlag(), flag);
            printf("SAPFOR: change flag for array '%s': %d -> %d\n", it->second.first->GetName().c_str(), it->second.first->GetNonDistributeFlag(), flag);
            
            if (flag == 0)
                it->second.first->SetNonDistributeFlag(false);
            else
                it->second.first->SetNonDistributeFlag(true);
            break;
        }
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
    return retCode;
}


int SPF_CorrectCodeStylePass(int *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    return simpleTransformPass(CORRECT_CODE_STYLE, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

extern set<string> filesToInclude;
int SPF_InsertIncludesPass(int *options, short *projName, short *folderName, char *filesToInclude, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
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
        //__spf_print(1, "file = %s\n", splited[i].c_str());
    }
    return simpleTransformPass(INSERT_INCLUDES, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_LoopEndDoConverterPass(int *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    return simpleTransformPass(CONVERT_TO_ENDDO, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

extern void deleteAllAllocatedData();
void SPF_deleteAllAllocatedData()
{
    deleteAllAllocatedData();
}

void createNeededException()
{
    if (passDone == 2)
        throw boost::thread_interrupted();
}
#endif