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
#include "AstWrapper.h"
#include "transform.h"
#include "errors.h"

extern std::map<std::string, std::string> shortFileNames;

int staticShadowAnalysis = 1; // always on
int staticPrivateAnalysis = 0;
int keepDvmDirectives = 0;
int keepFiles = 0;
int keepSpfDirs = 0;
int consoleMode = 0;
int genAllVars = 0; //generate ALL distribution variants
int genSpecificVar = -1; //generate specific distribution variant
uint64_t currentAvailMemory = 0;
static int activeState = 0;


std::map<DIST::Array*, std::tuple<int, std::string, std::string>> tableOfUniqNamesByArray;

std::vector<ParallelRegion*> parallelRegions;

// for LOOP_ANALYZER_DATA_DIST
std::map<std::tuple<int, std::string, std::string>, DIST::Array*> createdArrays;

std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaratedArrays;
std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> declaratedArraysSt; // St -> set<KEY>

int QUALITY; // quality of conflicts search in graph
//

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
std::set<std::string> filesToInclude;
//

//for PASSES DEPENDENSIES
std::map<passes, std::vector<passes>> passesDependencies;
std::set<passes> passesIgnoreStateDone;
//

//for files info
std::map<std::string, int> lineInfo; // file -> lines count
std::map<std::string, std::set<std::string>> includeDependencies; // file -> includes
//

//for FILL_COMMON_BLOCKS
std::map<std::string, CommonBlock> commonBlocks; // name -> commonBlock
//

std::map<std::string, std::vector<Messages>> SPF_messages; //file ->messages

//for DEF USE
map<string, vector<DefUseList>> defUseByFunctions;

const char *passNames[EMPTY_PASS + 1];
bool passNamesWasInit = false;

std::map<int, std::map<std::pair<std::string, int>, SgStatement*>> statsByLine; // fileID -> [ map<FileName, line>, SgSt*]
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
    std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaratedArrays;
    
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

        for (auto &elem : ::declaratedArrays)
            oldNewLinks[elem.second.first] = new DIST::Array(*elem.second.first);

        declaratedArrays = ::declaratedArrays;
        createdArrays = ::createdArrays;

        //fix links to new Array
        for (auto &elem : declaratedArrays)
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
            ::declaratedArrays = declaratedArrays;
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