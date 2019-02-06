#pragma once

#include "ParRegions.h"
#include "../GraphCall/graph_calls.h"
#include "../GraphLoop/graph_loops.h"

void fillRegionLines(SgFile *file, std::vector<ParallelRegion*> &regions, std::vector<LoopGraph*> *loops = NULL, std::vector<FuncInfo*> *funcs = NULL);
void fillRegionLinesStep2(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, std::vector<LoopGraph*>> *loopGraph = NULL);
int printParalleRegions(const char *fileName, std::vector<ParallelRegion*> &regions);
bool buildGraphFromUserDirectives(const std::vector<Statement*> &userDvmAlignDirs, DIST::GraphCSR<int, double, attrType> &G, DIST::Arrays<int> &allArrays, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);
void clearRegionStaticData();
void calculateLinesOfCode(std::vector<ParallelRegion*> &allRegions);
