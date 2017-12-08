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

int staticShadowAnalysis = 1; // always on
int staticPrivateAnalysis = 0;
int keepDvmDirectives = 1; // always on
int keepFiles = 0;
int keepSpfDirs = 0;
int consoleMode = 0;
int genAllVars = 0;
uint64_t currentAvailMemory = 0;

std::map<DIST::Array*, std::tuple<int, std::string, std::string>> tableOfUniqNamesByArray;

std::vector<ParallelRegion*> parallelRegions;

// for LOOP_ANALYZER_DATA_DIST
extern std::map<std::string, std::string> shortFileNames;
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

//for directive creating
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

std::map<std::string, std::vector<Messages>> SPF_messages; //file ->messages

const char *passNames[EMPTY_PASS + 1];
bool passNamesWasInit = false;