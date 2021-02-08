#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <string>

#include "ParallelizationRegions/ParRegions.h"
#include "Distribution/Array.h"
#include "GraphCall/graph_calls.h"
#include "GraphLoop/graph_loops.h"
#include "Utils/AstWrapper.h"
#include "DynamicAnalysis/gcov_info.h"
#include "Sapfor.h"
#include "Utils/errors.h"
#include "DynamicAnalysis/createParallelRegions.h"

extern std::map<std::string, std::string> shortFileNames;
static int activeState = 0;

int staticShadowAnalysis = 0;
int staticPrivateAnalysis = 0;
int keepDvmDirectives = 0;
int keepFiles = 0;
int keepSpfDirs = 0;
int predictOn = 0;
//int consoleMode = 0; moved to utils.cpp
int genAllVars = 0; //generate ALL distribution variants
int genSpecificVar = -1; //generate specific distribution variant
int ignoreDvmChecker = 0; // temporary flag
int parallizeFreeLoops = 0; // parallize free loops without arrays with DIST status
int automaticDeprecateArrays = 0; // automatic change DIST status to NON_DIST of Array
int maxShadowWidth = 50; // in percent
int intervals_threshold = 100; // threshold for intervals
bool removeNestedIntervals = false; // nested intervals removal flag
int langOfMessages = 1; // 0 - ENG, 1 - RUS
int mpiProgram = 0; // detected mpi calls
int ignoreIO = 0; // ignore io checker for arrays (DVM IO limitations)
int parseForInlining = 0; // special regime for files parsing for inliner

uint64_t currentAvailMemory = 0;
int QUALITY; // quality of conflicts search in graph
int SPEED;   // speed of conflicts search in graph

std::map<DIST::Array*, std::tuple<int, std::string, std::string>> tableOfUniqNamesByArray;

std::vector<ParallelRegion*> parallelRegions;

// for LOOP_ANALYZER_DATA_DIST
std::map<std::tuple<int, std::string, std::string>, DIST::Array*> createdArrays;

std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaredArrays;
std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> declaratedArraysSt; // St -> set<KEY>

//for CALL_GRAPH 
std::map<std::string, std::vector<FuncInfo*>> allFuncInfo; // file -> Info  
std::map<DIST::Array*, std::set<DIST::Array*>> arrayLinksByFuncCalls;
//

//for LOOP_GRAPH 
std::map<std::string, std::vector<LoopGraph*>> loopGraph; // file -> Info
std::map<LoopGraph*, depGraph*> depInfoForLoopGraph;
//

//for directive creator
std::map<std::string, std::vector<std::pair<int, std::pair<std::string, std::vector<Expression*>>>>> createdDirectives; //file -> directive to insert
//

//for directive inserter
std::map<std::string, std::map<int, std::set<std::string>>> commentsToInclude;
//

//for INSERT_INCLUDES
std::map<std::string, std::set<std::string>> filesToInclude;
//

//for PASSES DEPENDENSIES
std::map<passes, std::vector<passes>> passesDependencies;
std::set<passes> passesIgnoreStateDone;
//

//for files info
std::map<std::string, int> lineInfo; // file -> lines count
std::map<std::string, std::pair<std::set<int>, std::set<int>>> dirsInfo; // file -> dirs <lines SPF, lines DVM> count
std::map<std::string, std::set<std::string>> includeDependencies; // file -> includes
std::vector<std::string> filesCompilationOrder; // order of files for unite to one file
//

//for FILL_COMMON_BLOCKS
std::map<std::string, CommonBlock> commonBlocks; // name -> commonBlock
//

std::map<std::string, std::vector<Messages>> SPF_messages; //file ->messages

//for PARALLEL REGIONS + DVM_CHECKER
std::map<std::string, std::vector<int>> dvmDirErrors; // file->lines
//

//for DEF USE
std::map<std::string, vector<DefUseList>> defUseByFunctions;
//

//for EXPR SUBSTITUTION
std::map<std::string, std::vector<FuncInfo*>> subs_allFuncInfo; // file -> Info  
std::vector<ParallelRegion*> subs_parallelRegions;
//

//for predictior statistic 
std::map<std::string, PredictorStats> allPredictorStats;

//for DVM INTERVALS
std::map<std::string, std::vector<SpfInterval*>> intervals; // file -> intervals
std::vector<std::vector<long>> topologies; // current topologies
//

//for GCOV_PARSER
std::map<std::string, std::map<int, Gcov_info>> gCovInfo; // file -> [lines, info]
//

//for SPF CHANGING
std::tuple<std::string, int, int, int> inData; // file, startLine, endLine, del/add
std::map<std::string, std::string> outData; // file -> new unparsed text
//

//for SPF INLINE PROCEDURES
std::vector<std::tuple<std::string, std::string, int>> inDataProc; // [<proc, file, line>]
std::map<std::string, std::set<std::pair<std::string, int>>> inDataChains;
std::set<std::string> inDataChainsStart;
std::map<std::string, std::vector<SgStatement*>> hiddenData; // [<file -> all hidden stmts]
//

//module includes across all files, need to correct lines and out versions
std::map<std::string, std::set<std::string>> moduleUsesByFile; // file -> use module name
std::map<std::string, std::string> moduleDecls; // module -> file where declared
//

//for LOOPS_COMBINER
std::pair<std::string, int> inOnlyForloopOnPlace;
//

//cache for declaration arrays state switching
std::map<std::string, int> keyValueFromGUI;
//

//for PROCESS_IO
std::map<int, UserFiles> filesInfo; // information about open,close,write and read statements
//

const char* passNames[EMPTY_PASS + 1];
const char* optionNames[EMPTY_OPTION + 1];
bool passNamesWasInit = false;

std::map<PTR_BFND, std::pair<std::string, int>> sgStats;
std::map<PTR_LLND, std::pair<std::string, int>> sgExprs;

static int stateId = 0;
class SapforState
{
private:
    int id;

    std::map<DIST::Array*, std::tuple<int, std::string, std::string>> tableOfUniqNamesByArray;
    std::vector<ParallelRegion*> parallelRegions;

    // for LOOP_ANALYZER_DATA_DIST
    std::map<std::tuple<int, std::string, std::string>, DIST::Array*> createdArrays;
    std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaredArrays;
    
    std::map<DIST::Array*, std::set<DIST::Array*>> arrayLinksByFuncCalls;

    int PASSES_DONE[EMPTY_PASS];
    int *ALGORITHMS_DONE[EMPTY_ALGO];
public:
    //construct new links and copy objects
    SapforState()
    {
        id = stateId;
        stateId++;

        map<DIST::Array*, DIST::Array*> oldNewLinks;

        for (auto &elem : ::declaredArrays)
            oldNewLinks[elem.second.first] = new DIST::Array(*elem.second.first);

        declaredArrays = ::declaredArrays;
        createdArrays = ::createdArrays;

        //fix links to new Array
        for (auto &elem : declaredArrays)
            elem.second.first = oldNewLinks[elem.second.first];

        //fix links to new Array
        for (auto &elem : createdArrays)
            elem.second = oldNewLinks[elem.second];

        //fix links to new Array
        for (auto &elem : ::tableOfUniqNamesByArray)
            tableOfUniqNamesByArray[oldNewLinks[elem.first]] = elem.second;

        //fix links to new Array
        for (auto &elem : ::arrayLinksByFuncCalls)
        {
            DIST::Array *newArray = oldNewLinks[elem.first];
            arrayLinksByFuncCalls.insert(make_pair(newArray, std::set<DIST::Array*>()));
            auto it = arrayLinksByFuncCalls.find(newArray);
            for (auto &setElem : elem.second)
                it->second.insert(oldNewLinks[setElem]);
        }

        for (auto &reg : ::parallelRegions)
            parallelRegions.push_back(new ParallelRegion(*reg));

        //fix links to new Array
        for (auto &reg : parallelRegions)
        {
            auto arrays = reg->GetAllArraysToModify();
            arrays.UpdateLinks(oldNewLinks);

            auto dataDir = reg->GetDataDirToModify();
            dataDir.UpdateLinks(oldNewLinks);
        }

        for (int i = 0; i < EMPTY_PASS; ++i)
            PASSES_DONE[i] = ::PASSES_DONE[i];

        for (int i = 0; i < EMPTY_ALGO; ++i)
        {
            ALGORITHMS_DONE[i] = new int[parallelRegions.size()];
            for (int k = 0; k < parallelRegions.size(); ++k)
                ALGORITHMS_DONE[i][k] = ::ALGORITHMS_DONE[i][k];
        }
    }

    void RestoreState()
    {
        if (activeState != id)
        {
            activeState = id;

            ::tableOfUniqNamesByArray = tableOfUniqNamesByArray;
            ::parallelRegions = parallelRegions;
            ::createdArrays = createdArrays;
            ::declaredArrays = declaredArrays;
            ::declaratedArraysSt = declaratedArraysSt;
            ::arrayLinksByFuncCalls = arrayLinksByFuncCalls;
            ::parallelRegions = parallelRegions;

            for (int i = 0; i < EMPTY_PASS; ++i)
                ::PASSES_DONE[i] = PASSES_DONE[i];

            for (int i = 0; i < EMPTY_ALGO; ++i)
            {
                ALGORITHMS_DONE[i] = new int[parallelRegions.size()];
                for (int k = 0; k < parallelRegions.size(); ++k)
                    ::ALGORITHMS_DONE[i][k] = ALGORITHMS_DONE[i][k];
            }
        }
    }

    //TODO:
    ~SapforState()
    {
        for (int i = 0; i < EMPTY_ALGO; ++i)
            delete []ALGORITHMS_DONE[i];
    }
};

std::vector<SapforState*> states;