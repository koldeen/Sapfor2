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

#ifdef __BOOST
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#endif

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
#include "../Distribution/CreateDistributionDirs.h"
#include "../LoopAnalyzer/loop_analyzer.h"
#include <thread>
#include <exception>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#define _sleep(x) usleep(x * 1000)
#endif

using std::string;
using std::wstring;
using std::map;
using std::set;
using std::vector;
using std::pair;
using std::tuple;
using std::to_string;
using std::make_pair;

extern set<short*> allocated;
extern set<int*> allocatedInt;

static bool showDebug = false;

static inline int strLen(const short* shString)
{
    int t = 0;
    if (shString == NULL)
        return 0;

    while (shString[t] != '\0')
        t++;
    return t;
}

static char* ConvertShortToChar(const short* source, int& strL)
{
    char* dist = NULL;
    if (source == NULL)
        return dist;

    strL = strLen(source);
    dist = new char[strL + 1];

    for (int i = 0; i < strL; ++i)
        dist[i] = (char)source[i];
    dist[strL] = '\0';

    return dist;
}

static void setOptions(const short *options)
{
    if (!optionNames[STATIC_SHADOW_ANALYSIS])
    {
        optionNames[STATIC_SHADOW_ANALYSIS] = "STATIC_SHADOW_ANALYSIS";
        optionNames[STATIC_PRIVATE_ANALYSIS] = "STATIC_PRIVATE_ANALYSIS";
        optionNames[FREE_FORM] = "FREE_FORM";
        optionNames[KEEP_DVM_DIRECTIVES] = "KEEP_DVM_DIRECTIVES";
        optionNames[KEEP_SPF_DIRECTIVES] = "KEEP_SPF_DIRECTIVES";
        optionNames[PARALLIZE_FREE_LOOPS] = "PARALLIZE_FREE_LOOPS";
        optionNames[MAX_SHADOW_WIDTH] = "MAX_SHADOW_WIDTH";
        optionNames[OUTPUT_UPPER] = "OUTPUT_UPPER";
        optionNames[TRANSLATE_MESSAGES] = "TRANSLATE_MESSAGES";
        optionNames[KEEP_LOOPS_CLOSE_NESTING] = "KEEP_LOOPS_CLOSE_NESTING";
        optionNames[KEEP_GCOV] = "KEEP_GCOV";
        optionNames[ANALYSIS_OPTIONS] = "ANALYSIS_OPTIONS";
        optionNames[DEBUG_PRINT_ON] = "DEBUG_PRINT_ON";
        optionNames[MPI_PROGRAM] = "MPI_PROGRAM";
        optionNames[IGNORE_IO_SAPFOR] = "IGNORE_IO_SAPFOR";
        optionNames[EMPTY_OPTION] = "EMPTY_OPTION";
    }

    int len;
    char* conv = ConvertShortToChar(options, len);
    string convS(conv);
    delete []conv;

    vector<string> splited;
    vector<int> intOptions;
    splitString(convS, '|', splited);

    intOptions.resize(EMPTY_OPTION);
    std::fill(intOptions.begin(), intOptions.end(), -1);

    for (int z = STATIC_SHADOW_ANALYSIS; z <= EMPTY_OPTION; ++z) //TODO: extend
    {
        if (splited.size() == z)
            break;

        __spf_print(1, "read value '%s' to '%s' option\n", splited[z].c_str(), optionNames[z]);
        if (z != ANALYSIS_OPTIONS)
        {
            if (sscanf(splited[z].c_str(), "%d", &intOptions[z]) != 1)
            {
                __spf_print(1, "!wrong value!\n");
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }
        else
            intOptions[z] = -1;
    }

    //staticShadowAnalysis = intOptions[STATIC_SHADOW_ANALYSIS];
    staticPrivateAnalysis = intOptions[STATIC_PRIVATE_ANALYSIS];
    out_free_form = intOptions[FREE_FORM];
    keepDvmDirectives = intOptions[KEEP_DVM_DIRECTIVES];
    keepSpfDirs = intOptions[KEEP_SPF_DIRECTIVES];
    parallizeFreeLoops = (mpiProgram == 1) ? 0 : intOptions[PARALLIZE_FREE_LOOPS];
    maxShadowWidth = intOptions[MAX_SHADOW_WIDTH];
    out_upper_case = intOptions[OUTPUT_UPPER];
#if _WIN32
    langOfMessages = intOptions[TRANSLATE_MESSAGES];
#else
    langOfMessages = 0;
#endif
    removeNestedIntervals = (intOptions[KEEP_LOOPS_CLOSE_NESTING] == 1);
    showDebug = (intOptions[DEBUG_PRINT_ON] == 1);
    //mpiProgram = intOptions[MPI_PROGRAM];
    //ignoreIO = (mpiProgram == 1) ? 1 : intOptions[IGNORE_IO_SAPFOR];

    string optAnalisys = splited.size() > ANALYSIS_OPTIONS ? splited[ANALYSIS_OPTIONS] : "";
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

static void copyStringToShort(short *&result, const string &resVal, bool withEnd = true)
{
    result = new short[resVal.size() + 1];
    allocated.insert(result);

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
        if (showDebug)
            printf("SAPFOR: all passes num %zd\n", passesToRun.size());
        for (int i = 0; i < passesToRun.size(); ++i)
        {
            if (showDebug)
                printf("SAPFOR: run pass %d -> %s\n", passesToRun[i], passNames[passesToRun[i]]);
            __spf_print(1, "SAPFOR: run pass %d -> %s\n", passesToRun[i], passNames[passesToRun[i]]);
            runPass(passesToRun[i], prName, folderNameChar);
        }
    }
#if  __BOOST
    catch (boost::thread_interrupted&)
    {
        if (showDebug)
            printf("SAPFOR: thread was terminated\n");
        fflush(NULL);
        return;
    }
#endif
    catch (std::exception& ex)
    {
        printf("SAPFOR: thread was terminated with exception: %s\n", ex.what());
        fflush(NULL);
        rethrow = -1;
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

    if (showDebug)
        printf("SAPFOR: exit with pass == 1\n");
    passDone = 1;
}

static void runPassesForVisualizer(const short *projName, const vector<passes> &passesToRun, const short *folderName = NULL)
{
    int strL = 0, strF = 0;
    char *prName = ConvertShortToChar(projName, strL);
    char *folderNameChar = ConvertShortToChar(folderName, strF);    

    try
    {
        if (strL == 0)
        {
            prName = new char[16];
            sprintf(prName, "dvm.proj");
        }
        
        if (tryOpenProjectFile(prName) == false)
        {
            __spf_print(1, "Can not open project '%s'\n", prName);
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
             
        passDone = 0;
        rethrow = 0;

        std::thread thread { runPassesLoop, passesToRun, prName, folderNameChar };

        int timeToWait = 10;
        int steps = 0;
        while (passDone == 0)
        {
            FILE* interrupt_old = fopen("INTERRUPT", "r");
            FILE* interrupt = fopen("visualiser_data/INTERRUPT", "r");
            if (interrupt || interrupt_old)
            {
                if (showDebug)
                    printf("SAPFOR: file exists, start interruption\n");
                fflush(NULL);

                if (interrupt_old)
                    fclose(interrupt_old);
                if (interrupt)
                    fclose(interrupt);
                passDone = 2;
            }
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
        if (showDebug)
            printf("SAPFOR: start wait thread join, pass == %d\n", passDone);
        thread.join();
        if (showDebug)
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
        if (showDebug)
            printf("SAPFOR: rethrow\n");
        fflush(NULL);
        throw -99;
    }
    else if (rethrow != 0)
        throw rethrow;
}

int SPF_StatisticAnalyzer(void*& context, int winHandler, short* options, short* pppaOptions, short*& output, int*& outputSize,
                          short*& outputMessage, int*& outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int tmp;
    char* optionsStr = ConvertShortToChar(pppaOptions, tmp);

    int retSize = -1;
    try
    {
        if (pppaAnalyzer(optionsStr) != 0)
            retSize = 1;
        else
            retSize = 0;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); }
        catch (...) { }

        if (ex == -99)
            return -99;
        else
            retSize = ex;
    }
    catch (...)
    {
        retSize = -1;
    }
    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);
    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_ParseFiles(void*& context, int winHandler, short *options, short* projName, short*& output, int*& outputSize, 
                   short*& outputMessage, int*& outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;
    try
    {
        runPassesForVisualizer(projName, { PARSE_FILES });

        retSize = 0;
    }
    catch (int ex)
    {
        try { __spf_print(1, "catch code %d\n", ex); }
        catch (...) {}
        if (ex == -99)
            return -99;
        else
            retSize = ex;
    }
    catch (...)
    {
        retSize = -1;
    }
    convertGlobalBuffer(output, outputSize);
    convertGlobalMessagesBuffer(outputMessage, outputMessageSize);
    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, vector<LoopGraph*>> loopGraph; // file -> Info
int SPF_GetGraphLoops(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize,
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
    if (showDebug)
        printf("SAPFOR: return from DLL\n");

    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, vector<FuncInfo*>> allFuncInfo; // file -> Info  
int SPF_GetGraphFunctions(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize,
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
    if (showDebug)
        printf("SAPFOR: return from DLL\n");

    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_GetGraphVizOfFunctions(void*& context, short *options, short *projName, short *&result, short *&output, int *&outputSize,
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
    if (showDebug)
        printf("SAPFOR: return from DLL\n");

    MessageManager::setWinHandler(-1);
    return retSize;
}

extern int PASSES_DONE[EMPTY_PASS];
extern int *ALGORITHMS_DONE[EMPTY_ALGO];
extern const char *passNames[EMPTY_PASS + 1];

int SPF_GetPassesState(void*& context, int *&passInfo)
{
    MessageManager::clearCache();
    passInfo = PASSES_DONE;
    return EMPTY_PASS;
}

int SPF_GetPassesStateStr(void*& context, short *&passInfo)
{
    MessageManager::clearCache();
    string donePasses = "";
    for (int i = 0; i < EMPTY_PASS; ++i)
    {
        if (showDebug)
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


extern std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaredArrays;
static void printDeclArraysState()
{
    if (showDebug)
        printf("SAPFOR: decl state: \n");
    int dist = 0, priv = 0, err = 0;
    for (auto it = declaredArrays.begin(); it != declaredArrays.end(); ++it)
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
    if (showDebug)
        printf("   PRIV %d, DIST %d, ERR %d, ALL %d\n", priv, dist, err, dist + priv + err);
}

extern vector<ParallelRegion*> parallelRegions;
int SPF_GetArrayDistribution(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize,
                             short *&outputMessage, int *&outputMessageSize, int onlyAnalysis)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    printDeclArraysState();
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = -1;
    try
    {
        if (onlyAnalysis)
            runPassesForVisualizer(projName, { LOOP_ANALYZER_DATA_DIST_S1 });
        else
            runPassesForVisualizer(projName, { CREATE_TEMPLATE_LINKS });

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
    if (showDebug)
        printf("SAPFOR: return from DLL with code %d\n", retSize);
    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, vector<Messages>> SPF_messages;
extern map<DIST::Array*, set<DIST::Array*>> arrayLinksByFuncCalls;

//toModify[0] = size, toModify[1] arrayAddr, all triplets to modify for each dims
//ex: toModify A[1*J + 1]: [0] = 4, [1] = x000A, [2] = 0, [3] = 1, [4] = 1
int SPF_ModifyArrayDistribution(void*& context, int winHandler, short *options, short *projName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize,
                                int regId, int64_t *toModify)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    printDeclArraysState();
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retSize = 0;
    try
    {
        if (toModify == NULL || regId < 0)
            throw (-22);

        ParallelRegion *reg = NULL;
        for (int k = 0; k < parallelRegions.size(); ++k)
        {
            if (regId == parallelRegions[k]->GetId())
            {
                reg = parallelRegions[k];
                break;
            }
        }

        if (reg == NULL)
            throw (-23);

        map<DIST::Array*, vector<pair<int, int>>> data;
        auto arrays = reg->GetAllArrays().GetArrays();
        set<DIST::Array*> realRefsArrays;
        for (auto& elem : arrays)
        {
            if (elem->IsArray())
            {
                set<DIST::Array*> realRefs;
                getRealArrayRefs(elem, elem, realRefs, arrayLinksByFuncCalls);
                realRefsArrays.insert(realRefs.begin(), realRefs.end());
            }
        }

        int countOfArray = realRefsArrays.size();

        int z = 1;
        int last = *toModify;

        set<DIST::Array*> templates;
        for ( ; z < last; ++z)
        {
            int64_t addr = toModify[z];
            auto it = arrays.find((DIST::Array*)addr);
            if (it == arrays.end())
                throw (-24);

            DIST::Array* array = *it;
            DIST::Array* templ = array->GetTemplateArray(regId);
            if (!templ || !templ->IsTemplate())
                throw (-30);
            templates.insert(templ);

            if (array->IsLoopArray())
                throw (-26);
            if (array->IsTemplate())
                throw (-27);

            auto it2 = data.find(array);
            if (it2 != data.end())
                throw (-25);

            it2 = data.insert(it2, make_pair(array, vector<pair<int, int>>()));
            it2->second.resize(array->GetDimSize());
            std::fill(it2->second.begin(), it2->second.end(), make_pair(0, 0));

            ++z;
            int k = z;
            for ( ; k < z + 3 * array->GetDimSize(); k += 3)
                if (toModify[k] != -1)
                    it2->second[toModify[k]] = make_pair((int)toModify[k + 1], (int)toModify[k + 2]);
            z = k - 1;
        }
        if (z != last)
            throw (-28);

        DIST::GraphCSR<int, double, attrType> &reducedG = reg->GetReducedGraphToModify();
        DIST::Arrays<int> &allArrays = reg->GetAllArraysToModify();
        DataDirective &dataDirectives = reg->GetDataDirToModify();

        if (countOfArray != data.size())
            throw (-29);

        // recalculate links
        reducedG.cleanCacheLinks();
        dataDirectives.alignRules.clear();

        map<DIST::Array*, vector<pair<int, int>>> toDelete;
        toDelete = data;
        for (auto& elem : templates)
        {
            toDelete.insert(make_pair(elem, vector<pair<int, int>>()));
            elem->SetDimSizesToMaxMin(true);
        }
        reducedG.RemoveAllEdgesFromGraph(toDelete, allArrays);

        // add new rules and modify reduced graph
        for (auto& arrayP : data)
        {
            DIST::Array* array = arrayP.first;
            auto links = array->GetLinksWithTemplate(regId);
            auto templ = array->GetTemplateArray(regId);
            if (!templ)
                throw (-32);

            for (int z = 0; z < links.size(); ++z)
            {
                if (links[z] != -1)
                {
                    array->AddLinkWithTemplate(z, links[z], templ, arrayP.second[z], regId);
                    int err = DIST::AddArrayAccess(reducedG, allArrays, array, templ, make_pair(z, links[z]), 1.0, make_pair(make_pair(1, 0), arrayP.second[z]), WW_link);
                    if (err != 0)
                        throw (-33);
                }
                else
                {
                    if (arrayP.second[z].first != 0)
                        throw (-31);                    
                }
            }
        }

        createAlignDirs(reducedG, allArrays, dataDirectives, reg->GetId(), arrayLinksByFuncCalls, SPF_messages);

        __spf_print(1, "*** NEW RULES FOR PARALLEL REGION '%s':\n", reg->GetName().c_str());
        auto result = dataDirectives.GenAlignsRules();

        for (int i = 0; i < result.size(); ++i)
            __spf_print(1, "  %s\n", result[i].c_str());

        // clear user directives from all loops
        for (auto& byFile : loopGraph)
        {
            if (SgFile::switchToFile(byFile.first) == -1)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            for (auto& loop : byFile.second)
                loop->clearUserDirectives();
        }

        // clear other dirs
        set<int> varsToClear = { ACC_REGION_DIR, ACC_END_REGION_DIR, ACC_ACTUAL_DIR, ACC_GET_ACTUAL_DIR, 
                                 DVM_SHADOW_DIR, DVM_REALIGN_DIR, DVM_REDISTRIBUTE_DIR, DVM_INHERIT_DIR, DVM_DYNAMIC_DIR };
        removeStatementsFromAllproject(varsToClear);
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
    if (showDebug)
        printf("SAPFOR: return from DLL with code %d\n", retSize);
    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, PredictorStats> allPredictorStats;
extern map<string, vector<SpfInterval*>> intervals;
extern vector<vector<long>> topologies;

int SPF_CreateParallelVariant(void*& context, int winHandler, short *options, short *projName, short *folderName, int64_t *variants, int *varLen,
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
            if (showDebug)
                printf("SAPFOR: input pack %d: %lld %lld %lld\n", k, variants[i], variants[i + 1], variants[i + 2]);
            varLens[(int)variants[i + 2]].push_back(make_pair(variants[i], variants[i + 1]));
        }

        if (varLens.size() != parallelRegions.size())
            throw (-6);

        int countOfDist = 0;
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
                if (showDebug)
                    printf("SAPFOR: currV %d, dataDirectives.distrRules %d\n", (int)currVars.size(), (int)dataDirectives.distrRules.size());
                throw (-3);
            }

            map<int64_t, int> varMap;
            for (int i = 0; i < currVars.size(); ++i)
                varMap[currVars[i].first] = (int)currVars[i].second;

            map<int64_t, int> templateIdx;
            for (int i = 0; i < dataDirectives.distrRules.size(); ++i)
            {
                if (showDebug)
                    printf("SAPFOR: template address %lld with num %d\n", (int64_t)dataDirectives.distrRules[i].first, i);
                templateIdx[(int64_t)dataDirectives.distrRules[i].first] = i;                
            }

            for (auto it = varMap.begin(); it != varMap.end(); ++it)
            {
                auto itF = templateIdx.find(it->first);
                if (itF == templateIdx.end())
                    throw (-4);

                if (showDebug)
                    printf("SAPFOR: found %lld address\n", it->first);
                currentVariant[itF->second] = it->second;

                for (auto &elem : dataDirectives.distrRules[itF->second].second[it->second].distRule)                    
                {
                    if (elem == BLOCK)
                        countOfDist++;
                }
            }
            parallelRegions[z]->SetCurrentVariant(currentVariant);
        }

        if (showDebug)
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

            summed.TotalScoreComm += predFile.second.TotalScoreComm;
            summed.TotalScoreDist += predFile.second.TotalScoreDist;
            summed.TotalScorePar += predFile.second.TotalScorePar;
        }                
        predictRes += summed.to_string();
        //predictRes += "|" + to_string((summed.TotalScoreComm != 0 ? 1.0 / summed.TotalScoreComm : 0.0 )+ (double)summed.TotalScorePar * 1000 + (countOfDist == 0 ? -5000 : countOfDist));
        if (countOfDist == 0)
            predictRes += "|x";
        else
            predictRes += "|" + to_string(-1 * (summed.ParallelStat.AcrossCount + summed.ParallelStat.RemoteCount + summed.RedistributeCount + summed.RemoteCount));
        //predictRes += "|0";

        //TODO: need to rewrite to new algo
        /*if (folderName == NULL)
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
            predictRes += "|0";*/

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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_GetVersionAndBuildDate(void*& context, short *&result)
{
    MessageManager::clearCache();
    string resVal = "";
    resVal += string(VERSION) + " |" + __DATE__ + "| |" +__TIME__ + "| ";

    copyStringToShort(result, resVal);
    return (int)resVal.size() + 1;
}

extern set<string> intrinsicF;
extern void initIntrinsicFunctionNames();

int SPF_GetIntrinsics(void*& context, short *&result)
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
int SPF_GetIncludeDependencies(void*& context, int winHandler, short *options, short *projName, short *&result)
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

int SPF_SetFunctionsToInclude(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize,
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

int SPF_GetAllDeclaratedArrays(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize,
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
        for (auto f = declaredArrays.begin(); f != declaredArrays.end(); ++f)
        {
            if (f != declaredArrays.begin())
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, int> lineInfo;
extern map<string, pair<set<int>, set<int>>> dirsInfo;
int SPF_GetFileLineInfo(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize,
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

            auto itD = dirsInfo.find(it->first);
            if (itD == dirsInfo.end())
                resVal += it->first + "@" + to_string(it->second) + "_0_0";
            else
                resVal += it->first + "@" + to_string(it->second) + "_" + to_string(itD->second.first.size()) + "_" + to_string(itD->second.second.size());
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
}

extern map<string, int> keyValueFromGUI;
int SPF_SetDistributionFlagToArray(void*& context, char *key, int flag)
{
    MessageManager::clearCache();

    if (flag != DIST::DISTR && flag != DIST::NO_DISTR)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    string keyStr(key);
    try
    {
        if (declaredArrays.size())
        {
            for (auto& array : declaredArrays)
            {
                const auto key = array.second.first->GetName();
                if (key == keyStr)
                {
                    __spf_print(1, "change flag for array '%s': %d -> %d\n", key.c_str(), array.second.first->GetNonDistributeFlag(), flag);                    

                    if (flag == DIST::DISTR)
                        array.second.first->SetNonDistributeFlag(DIST::DISTR);
                    else
                        array.second.first->SetNonDistributeFlag(DIST::NO_DISTR);
                    break;
                }
            }
        }
        else
            keyValueFromGUI[keyStr] = flag;
    }
    catch (...)
    {
        return -1;
    }

    return 0;
}

int SPF_SetDistributionFlagToArrays(void*& context, const char* keys, const char* flags)
{
    MessageManager::clearCache();

    if (!keys || !flags)
        return 0;

    try
    {
        vector<string> keysS;
        vector<string> flagsS;

        splitString(keys, '|', keysS);
        splitString(flags, '|', flagsS);
        
        if (keysS.size() != flagsS.size())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        map<string, DIST::Array*> allArrays;
        for (auto& array : declaredArrays)
            allArrays[array.second.first->GetIndepUniqName()] = array.second.first;

        if (allArrays.size())
        {
            for (int z = 0; z < keysS.size(); ++z)
            {
                auto it = allArrays.find(keysS[z]);
                if (it == allArrays.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                int flag = -1;
                if (sscanf(flagsS[z].c_str(), "%d", &flag) != 1)
                {
                    __spf_print(1, "!wrong value!\n");
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                if (flag != DIST::DISTR && flag != DIST::NO_DISTR)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                __spf_print(1, "change flag for array '%s': %d -> %d\n", keysS[z].c_str(), it->second->GetNonDistributeFlag(), flag);

                if (flag == DIST::DISTR)
                    it->second->SetNonDistributeFlag(DIST::DISTR);
                else
                    it->second->SetNonDistributeFlag(DIST::NO_DISTR);
            }
        }
        else
        {
            for (int z = 0; z < keysS.size(); ++z)
            {
                int flagI = -1;
                if (sscanf(flagsS[z].c_str(), "%d", &flagI) == -1)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                keyValueFromGUI[keysS[z]] = flagI;
            }
        }
    }
    catch (...)
    {
        return -1;
    }
    return 0;
}

static int simpleTransformPass(const passes PASS_NAME, short *options, short *projName, short *folderName,
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retCode;
}


int SPF_CorrectCodeStylePass(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                             int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(CORRECT_CODE_STYLE, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_DuplicateFunctionChains(void*& context, int winHandler, short *options, short* projName, short* folderName, short*& output,
                                int*& outputSize, short*& outputMessage, int*& outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(DUPLICATE_FUNCTIONS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_ResolveParallelRegionConflicts(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                                       int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(RESOLVE_PAR_REGIONS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_PrivateExpansion(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                         int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(PRIVATE_ARRAYS_BREEDING, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}
int SPF_PrivateShrinking(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                         int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(PRIVATE_ARRAYS_SHRINKING, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_LoopFission(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                    int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(LOOPS_SPLITTER, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_LoopUnion(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                  int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(LOOPS_COMBINER, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_CreateIntervalsTree(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                            int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(INSERT_INTER_TREE, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_RemoveDvmDirectives(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                            int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(REMOVE_DVM_DIRS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_RemoveDvmDirectivesToComments(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                                      int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(REMOVE_DVM_DIRS_TO_COMMENTS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

int SPF_RemoveDvmIntervals(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                           int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    return simpleTransformPass(REMOVE_DVM_INTERVALS, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

static inline void convertBackSlash(char *str, int strL)
{
    for (int z = 0; z < strL; ++z)
        if (str[z] == '\\')
            str[z] = '/';
}

//TODO: need to extend 'outFileName' to vector
static int inline runModificationPass(passes passName, short* projName, short* folderName,
                                      int& size, int*& sizes, short*& newFilesNames, short*& newFiles,
                                      const string outFileName)
{
    PASSES_DONE[passName] = 0;
    runPassesForVisualizer(projName, { passName }, folderName);

    //fill data
    // size - число файлов для мод.
    // sizes - размеры границ в буфере newFiles
    // newFilesNames - имена файлов для мод., разд. '|'
    // newFiles - буфер

    string newFile;

    size = 1;

    if (SgFile::switchToFile(outFileName.c_str()) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    newFile = unparseProjectToString(current_file, EXPAND_EXTRACT_PAR_REGION);

    sizes = new int[size + 1];
    newFilesNames = new short[outFileName.size()];
    newFiles = new short[newFile.size()];

    allocated.insert(newFilesNames);
    allocated.insert(newFiles);
    allocatedInt.insert(sizes);

    sizes[0] = 0;
    sizes[1] = sizes[0] + newFile.size();
    copyStringToShort(newFilesNames, outFileName);
    copyStringToShort(newFiles, newFile);

    return (int)outFileName.size() + 1;
}

extern tuple<string, int, int, int> inData;
extern map<string, string> outData;
int SPF_ChangeSpfIntervals(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output,
                           int *&outputSize, short *&outputMessage, int *&outputMessageSize, 
                           short *fileNameToMod, int *toModifyLines,
                           int &size, int *&sizes, short *&newFilesNames, short *&newFiles)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retCode = 0;
    try
    {
        int strL;
        char *file_c = ConvertShortToChar(fileNameToMod, strL);
        convertBackSlash(file_c, strL);

        std::get<0>(inData) = file_c;
        std::get<1>(inData) = toModifyLines[0];
        std::get<2>(inData) = toModifyLines[1];
        std::get<3>(inData) = toModifyLines[2];
        retCode = runModificationPass(EXPAND_EXTRACT_PAR_REGION, projName, folderName, size, sizes, newFilesNames, newFiles, file_c);
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retCode;
}

extern vector<tuple<string, string, int>> inDataProc;
int SPF_InlineProcedure(void*& context, int winHandler, short *options, short* projName, short* folderName,
                        short* name, short* file, int line, 
                        short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize,
                        int& size, int*& sizes, short*& newFilesNames, short*& newFiles)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retCode = 0;
    try
    {
        int tmp;
        char* name_c = ConvertShortToChar(name, tmp);
        char* file_c = ConvertShortToChar(file, tmp);
        convertBackSlash(file_c, tmp);

        inDataProc.push_back(std::make_tuple(file_c, name_c, line));
        retCode = runModificationPass(INLINE_PROCEDURES, projName, folderName, size, sizes, newFilesNames, newFiles, file_c);
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retCode;
}

extern pair<string, int> inOnlyForloopOnPlace;
int SPF_LoopUnionCurrent(void*& context, int winHandler, short* options, short* projName, short* folderName,
                         short* file, int line,
                         short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize,
                         int& size, int*& sizes, short*& newFilesNames, short*& newFiles)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retCode = 0;
    try
    {
        int tmp;
        char* file_c = ConvertShortToChar(file, tmp);
        if (!file_c)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        convertBackSlash(file_c, tmp);

        inOnlyForloopOnPlace = make_pair(file_c, line);
        retCode = runModificationPass(LOOPS_COMBINER, projName, folderName, size, sizes, newFilesNames, newFiles, file_c);
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retCode;
}

int SPF_InlineProcedures(void*& context, int winHandler, short* options, short* projName, short* folderName,
                         short* names, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);
    clearGlobalMessagesBuffer();
    setOptions(options);

    int retCode = 0;
    try
    {
        int tmp = 0;
        char* names_c = ConvertShortToChar(names, tmp);
        if (tmp != 0)
        {
            string allNames(names_c);
            vector<string> result;
            splitString(allNames, '|', result);

            if (result.size())
            {
                for (auto& elem : result)
                    inDataProc.push_back(make_tuple(elem, elem, -1));

                PASSES_DONE[INLINE_PROCEDURES] = 0;
                runPassesForVisualizer(projName, { INLINE_PROCEDURES }, folderName);

                inDataProc.clear();
            }
        }
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retCode;
}


extern set<string> filesToInclude;
int SPF_InsertIncludesPass(void*& context, int winHandler, short *options, short *projName, short *folderName, char *filesToInclude,
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

int SPF_LoopEndDoConverterPass(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize)
{
    MessageManager::clearCache();
    MessageManager::setWinHandler(winHandler);

    return simpleTransformPass(CONVERT_TO_ENDDO, options, projName, folderName, output, outputSize, outputMessage, outputMessageSize);
}

extern map<string, map<int, Gcov_info>> gCovInfo;
int SPF_GetGCovInfo(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize,
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

    if (showDebug)
        printf("SAPFOR: return from DLL\n");
    MessageManager::setWinHandler(-1);
    return retSize;
    
}

extern void deleteAllAllocatedData(bool enable);
void SPF_deleteAllAllocatedData(void*& context)
{
    MessageManager::clearCache();

    for (auto& elem : allocated)
        delete[]elem;
    for (auto& elem : allocatedInt)
        delete[]elem;
    allocated.clear();
    allocatedInt.clear();

    deleteAllAllocatedData(true);
}

extern bool runAsClient;
static wstring finishJniCall(int retCode, const short* result, const short* output, const int* outputSize,
                             const short* outputMessage, const int* outputMessageSize, const short* predictorStats = NULL);
void createNeededException()
{
    if (passDone == 2)
    {
        if (runAsClient)
        {
            printf("[CLIENT]: send error code -99\n");
            sendErrorCode(finishJniCall(-99, NULL, NULL, NULL, NULL, NULL, NULL));
            printf("[CLIENT]: wait 1 second\n");
            _sleep(1000);
            printf("[CLIENT]: exit with -99 code\n");
            exit(-99);
        }
        else
            throw std::runtime_error("Interrupted by user\n");
    }
}

static void* context = NULL;
static short* toShort(const char* str)
{
    int len = str != NULL ? strlen(str) : 0; 
    short* arr = new short[len + 1];
    for (int z = 0; z < len; ++z)
        arr[z] = str[z];
    arr[len] = '\0';
    return arr;
}

static wstring toWstring(const short* array, int size)
{
    if (size == 0)
        return L"";

    wstring str = L"";
    for (int z = 0; z < size; ++z)
        str += array[z];
    return str;
}

static wstring toWstring(const int* array, int size)
{
    if (size == 0)
        return L"";

    wstring str = L"";
    for (int z = 0; z < size; ++z)
    {
        if (z != 0)
            str += L"|";
        str += std::to_wstring(array[z]);
    }
    return str;
}


static void codeInfo(wstring& total, const wstring& toAdd)
{
    total += std::to_wstring(toAdd.size()) + L" " + toAdd;
}

static wstring finishJniCall(int retCode, const short* result, const short* output, const int* outputSize, 
                             const short* outputMessage, const int* outputMessageSize, const short* predictorStats)
{ 
    wstring codedResult = L"";

    codedResult += std::to_wstring(retCode) + L" ";
    codeInfo(codedResult, toWstring(result, (result) ? strLen(result) : 0));
    codeInfo(codedResult, toWstring(output, (outputSize) ? (outputSize[0]) : 0));
    codeInfo(codedResult, toWstring(outputMessage, (outputMessageSize) ? (outputMessageSize[0]) : 0));
    codeInfo(codedResult, toWstring(predictorStats, (predictorStats) ? strLen(predictorStats) : 0));

    return codedResult;
}

static wstring finishJniCall(const int size, const int* sizes, const short* newFilesNames, const short* newFiles)
{
    wstring codedResult = L"";

    codeInfo(codedResult, toWstring(sizes, (sizes) ? (size + 1) : 0));
    codeInfo(codedResult, toWstring(newFilesNames, (newFilesNames) ? strLen(newFilesNames) : 0));
    codeInfo(codedResult, toWstring(newFiles, (newFiles) ? strLen(newFiles) : 0));

    return codedResult;
}

static void fillInfo(const vector<string>& data, int64_t*& arr1, int& arr2)
{
    if (data.size() < 4)
        return;
    int idx = 0;
    arr2 = std::stoi(data[idx++]) * 3;
    arr1 = new int64_t[arr2];
    for (int z = 0; z < arr2; ++z, ++idx)
        arr1[z] = std::stoll(data[idx]);

    if (data.size() != idx)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void fillInfo(const string& data, int*& arr)
{
    vector<string> splited;
    splitString(data, '|', splited);

    int idx = 0;
    int count = std::stoi(splited[idx++]);
    arr = new int[count];
    for (int z = 0; z < count; ++z, ++idx)
        arr[z] = std::stoi(splited[idx]);
}

static void fillInfo(const string& data, int64_t*& arr)
{
    vector<string> splited;
    splitString(data, '|', splited);

    int idx = 0;
    int count = std::stoi(splited[idx++]);
    arr = new int64_t[count];
    for (int z = 0; z < count; ++z, ++idx)
        arr[z] = std::stoll(splited[idx]);
}

const wstring Sapfor_RunAnalysis(const char* analysisName_c, const char* options_c, const char* projName_c, int winHandler)
{
    const string whichRun = analysisName_c;
    int retCode = 0;

    short* result = NULL, * output = NULL, * outputMessage = NULL;
    int* outputSize = NULL, * outputMessageSize = NULL;

    short* projSh = toShort(projName_c);
    short* optSh = toShort(options_c);

    winHandler = -2;
    try
    {
        if (whichRun == "SPF_GetGraphLoops")
            retCode = SPF_GetGraphLoops(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_GetGraphFunctions")
            retCode = SPF_GetGraphFunctions(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_GetGraphVizOfFunctions")
            retCode = SPF_GetGraphVizOfFunctions(context, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_GetArrayDistribution")
            retCode = SPF_GetArrayDistribution(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize, 0);
        else if (whichRun == "SPF_GetArrayDistributionOnlyAnalysis")
            retCode = SPF_GetArrayDistribution(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize, 1);
        else if (whichRun == "SPF_SetFunctionsToInclude")
            retCode = SPF_SetFunctionsToInclude(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_GetAllDeclaratedArrays")
            retCode = SPF_GetAllDeclaratedArrays(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_GetFileLineInfo")
            retCode = SPF_GetFileLineInfo(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_GetIncludeDependencies")
            retCode = SPF_GetIncludeDependencies(context, winHandler, optSh, projSh, result);
        else if (whichRun == "SPF_GetGCovInfo")
            retCode = SPF_GetGCovInfo(context, winHandler, optSh, projSh, result, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_ParseFiles")
            retCode = SPF_ParseFiles(context, winHandler, optSh, projSh, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_StatisticAnalyzer")
            retCode = SPF_StatisticAnalyzer(context, winHandler, optSh, projSh, output, outputSize, outputMessage, outputMessageSize);
        else if (whichRun == "SPF_GetPassesStateStr")
            retCode = SPF_GetPassesStateStr(context, result);
        else if (whichRun == "SPF_GetVersionAndBuildDate")
            retCode = SPF_GetVersionAndBuildDate(context, result);
        else if (whichRun == "SPF_GetIntrinsics")
            retCode = SPF_GetIntrinsics(context, result);
        else if (whichRun == "SPF_deleteAllAllocatedData")
            SPF_deleteAllAllocatedData(context);
        else if (whichRun == "SPF_СhangeDirectory")
        {
            if (options_c == NULL)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            if (chdir(options_c) != 0)
            {
                __spf_print(1, "can not change directory to '%s'\n", options_c);
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }
        else if (whichRun == "SPF_ChangeDirectory")
        {
            if (options_c == NULL)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            if (chdir(options_c) != 0)
            {
                __spf_print(1, "can not change directory to '%s'\n", options_c);
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }
        else
        {
            if (showDebug)
                printf("SAPFOR: unknown function call, given '%s' name\n", whichRun.c_str());
            retCode = -1001;
        }
    }
    catch (...)
    {
        printf("SAPFOR: wrong exit from main DLL block for JAVA\n");
        convertGlobalBuffer(output, outputSize);
        convertGlobalMessagesBuffer(outputMessage, outputMessageSize);
        retCode = -1004;
    }

    delete[]projSh;
    delete[]optSh;

    fflush(NULL);
    const wstring codedResult = finishJniCall(retCode, result, output, outputSize, outputMessage, outputMessageSize);
    return codedResult;
}

const wstring Sapfor_RunTransformation(const char* transformName_c, const char* options_c, const char* projName_c,
                                       const char* folder_c, const char* addOpt_c, int winHandler)
{
    const string whichRun = transformName_c;
    int retCode = 0;

    short* result = NULL, * output = NULL, * outputMessage = NULL;
    int* outputSize = NULL, * outputMessageSize = NULL;
    short* predStats = NULL;

    short* projSh = toShort(projName_c);
    short* optSh = toShort(options_c);
    short* fold = toShort(folder_c); if (string("") == folder_c) fold = NULL;
    short* addOpt = toShort(addOpt_c);

    winHandler = -2;
    if (whichRun == "SPF_CorrectCodeStylePass")
        retCode = SPF_CorrectCodeStylePass(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_RemoveDvmDirectives")
        retCode = SPF_RemoveDvmDirectives(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_RemoveDvmDirectivesToComments")
        retCode = SPF_RemoveDvmDirectivesToComments(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_InsertIncludesPass")
        retCode = SPF_InsertIncludesPass(context, winHandler, optSh, projSh, fold, (char*)addOpt_c, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_ResolveParallelRegionConflicts")
        retCode = SPF_ResolveParallelRegionConflicts(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_LoopEndDoConverterPass")
        retCode = SPF_LoopEndDoConverterPass(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_CreateParallelVariant")
    {
        vector<string> splited;
        string orig(addOpt_c);
        splitString(orig, '|', splited);

        int64_t* variants = NULL;
        int varLen = -1;

        fillInfo(splited, variants, varLen);
        retCode = SPF_CreateParallelVariant(context, winHandler, optSh, projSh, fold, variants, &varLen, output, outputSize, outputMessage, outputMessageSize, predStats);

        if (retCode > 0)
            delete[]variants;
    }
    else if (whichRun == "SPF_LoopFission")
        retCode = SPF_LoopFission(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_LoopUnion")
        retCode = SPF_LoopUnion(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_PrivateExpansion")
        retCode = SPF_PrivateExpansion(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_PrivateShrinking")
        retCode = SPF_PrivateShrinking(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_CreateIntervalsTree")
        retCode = SPF_CreateIntervalsTree(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_RemoveDvmIntervals")
        retCode = SPF_RemoveDvmIntervals(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_DuplicateFunctionChains")
        retCode = SPF_DuplicateFunctionChains(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize);
    else if (whichRun == "SPF_InlineProcedures")
        retCode = SPF_InlineProcedures(context, winHandler, optSh, projSh, fold, output, addOpt, outputSize, outputMessage, outputMessageSize);
    else
    {
        if (showDebug)
            printf("SAPFOR: unknown function call, given '%s' name\n", whichRun.c_str());
        retCode = -1002;
    }

    delete[]projSh;
    delete[]optSh;
    delete[]fold;
    delete[]addOpt;

    fflush(NULL);
    const wstring codedResult = finishJniCall(retCode, result, output, outputSize, outputMessage, outputMessageSize, predStats);
    return codedResult;
}

const wstring Sapfor_RunModification(const char* modifyName_c, const char* options_c, const char* projName_c,
                                     const char* folder_c, const char* addOpt1_c, const char* addOpt2_c, 
                                     int winHandler)
{
    const string whichRun = modifyName_c;
    int retCode = 0;

    short* result = NULL, * output = NULL, * outputMessage = NULL;
    int* outputSize = NULL, * outputMessageSize = NULL;
    int size = 0, * sizes = NULL;
    short* newFilesNames = NULL, * newFiles = NULL;

    short* projSh = toShort(projName_c);
    short* optSh = toShort(options_c);
    short* fold = toShort(folder_c);

    winHandler = -2;
    if (whichRun == "SPF_ModifyArrayDistribution")
    {
        int regId = atoi(addOpt1_c);
        int64_t* modify = NULL;
        fillInfo(addOpt2_c, modify);

        retCode = SPF_ModifyArrayDistribution(context, winHandler, optSh, projSh, output, outputSize, outputMessage, outputMessageSize, regId, modify);
        delete[]modify;
    }
    else if (whichRun == "SPF_InlineProcedure")
    {
        vector<string> splitS;
        splitString(addOpt1_c, '|', splitS);

        vector<short*> tmpPar = { toShort(splitS[0].c_str()), toShort(splitS[1].c_str()) };
        int line = std::stoi(addOpt2_c);
        retCode = SPF_InlineProcedure(context, winHandler, optSh, projSh, fold, tmpPar[0], tmpPar[1], line, output, outputSize, outputMessage, outputMessageSize, size, sizes, newFiles, newFilesNames);

        delete[]tmpPar[0];
        delete[]tmpPar[1];
    }
    else if (whichRun == "SPF_LoopUnionCurrent")
    {
        short* file = toShort(addOpt1_c);
        int line = std::stoi(addOpt2_c);
        retCode = SPF_LoopUnionCurrent(context, winHandler, optSh, projSh, fold, file, line, output, outputSize, outputMessage, outputMessageSize, size, sizes, newFiles, newFilesNames);
        delete[]file;
    }
    else if (whichRun == "SPF_ChangeSpfIntervals")
    {
        short* fileNameToMod = toShort(addOpt1_c);
        int* toModifyLines = NULL;
        fillInfo(addOpt2_c, toModifyLines);
        retCode = SPF_ChangeSpfIntervals(context, winHandler, optSh, projSh, fold, output, outputSize, outputMessage, outputMessageSize, fileNameToMod, toModifyLines, size, sizes, newFiles, newFilesNames);
        delete[]fileNameToMod;
        delete[]toModifyLines;
    }
    else if (whichRun == "SPF_SetDistributionFlagToArray")
    {
        int flag = atoi(addOpt2_c);
        retCode = SPF_SetDistributionFlagToArray(context, (char*)addOpt1_c, flag);

        convertGlobalBuffer(output, outputSize);
        convertGlobalMessagesBuffer(outputMessage, outputMessageSize);
    }
    else if (whichRun == "SPF_SetDistributionFlagToArrays")
    {
        retCode = SPF_SetDistributionFlagToArrays(context, addOpt1_c, addOpt2_c);

        convertGlobalBuffer(output, outputSize);
        convertGlobalMessagesBuffer(outputMessage, outputMessageSize);
    }
    else
    {
        if (showDebug)
            printf("SAPFOR: unknown function call, given '%s' name\n", whichRun.c_str());
        retCode = -1003;
    }

    delete[]projSh;
    delete[]optSh;
    delete[]fold;

    fflush(NULL);
    wstring codedResult = finishJniCall(retCode, result, output, outputSize, outputMessage, outputMessageSize);
    codedResult += finishJniCall(size, sizes, newFilesNames, newFiles);

    return codedResult;
}

#ifdef JAVA
static jcharArray StringToJCharArray(const wstring& nativeString, JNIEnv* env)
{
    jcharArray arr = env->NewCharArray(nativeString.size());
    unsigned short* tmpBuf = new unsigned short[nativeString.size()];
    for (int z = 0; z < nativeString.size(); ++z)
        tmpBuf[z] = nativeString[z];
    env->SetCharArrayRegion(arr, 0, nativeString.size(), (jchar*)tmpBuf);
    delete []tmpBuf;
    return arr;
}

JNIEXPORT jcharArray JNICALL Java_components_Sapfor_SPF_1RunAnalysis(
          JNIEnv* env, jobject obj, jstring analysisName, jint winHandler, jstring options, jstring projName)
{
    const char* analysisName_c = env->GetStringUTFChars(analysisName, NULL);
    const char* options_c = env->GetStringUTFChars(options, NULL);
    const char* projName_c = env->GetStringUTFChars(projName, NULL);

    return StringToJCharArray(Sapfor_RunAnalysis(analysisName_c, options_c, projName_c, winHandler), env);
}

JNIEXPORT jcharArray JNICALL Java_components_Sapfor_SPF_1RunTransformation(
        JNIEnv* env, jobject obj, jstring transformName, jint winHandler, jstring options, jstring projName, jstring folder, jstring addOptions)
{
    const char* transformName_c = env->GetStringUTFChars(transformName, NULL);
    const char* options_c = env->GetStringUTFChars(options, NULL);
    const char* projName_c = env->GetStringUTFChars(projName, NULL);
    const char* folder_c = env->GetStringUTFChars(folder, NULL);
    const char* addOpt_c = env->GetStringUTFChars(addOptions, NULL);
    
    return StringToJCharArray(Sapfor_RunTransformation(transformName_c, options_c, projName_c, folder_c, addOpt_c, winHandler), env);
}

JNIEXPORT jcharArray JNICALL Java_components_Sapfor_SPF_1RunModification(
        JNIEnv* env, jobject obj, jstring modifyName, jint winHandler, jstring options, jstring projName, jstring folder, jstring addOpt1, jstring addOpt2)
{
    const char* modifyName_c = env->GetStringUTFChars(modifyName, NULL);
    const char* options_c = env->GetStringUTFChars(options, NULL);
    const char* projName_c = env->GetStringUTFChars(projName, NULL);
    const char* folder_c = env->GetStringUTFChars(folder, NULL);
    const char* addOpt1_c = env->GetStringUTFChars(addOpt1, NULL);
    const char* addOpt2_c = env->GetStringUTFChars(addOpt2, NULL);

    return StringToJCharArray(Sapfor_RunModification(modifyName_c, options_c, projName_c, folder_c, addOpt1_c, addOpt2_c, winHandler), env);
}
#endif