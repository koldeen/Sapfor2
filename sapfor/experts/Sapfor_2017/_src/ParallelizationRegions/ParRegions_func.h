#pragma once

#include "ParRegions.h"
#include "../GraphCall/graph_calls.h"
#include "../GraphLoop/graph_loops.h"

void fillRegionLines(SgFile *file, std::vector<ParallelRegion*> &regions);
ParallelRegion* getRegionByLine(const std::vector<ParallelRegion*> &regions, const std::string &file, const int line);
void fillRegionLinesStep2(std::vector<ParallelRegion*> &regions, std::map<std::string, std::vector<FuncInfo*>> allFuncInfo, std::map<std::string, std::vector<LoopGraph*>> &loopGraph);
int printParalleRegions(const char *fileName, std::vector<ParallelRegion*> &regions);
