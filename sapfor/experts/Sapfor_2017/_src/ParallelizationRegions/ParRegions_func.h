#pragma once

#include "ParRegions.h"
#include "resolve_par_reg_conflicts.h"
#include "../GraphCall/graph_calls.h"
#include "../GraphLoop/graph_loops.h"

void fillRegionLines(SgFile *file, std::vector<ParallelRegion*> &regions, std::vector<LoopGraph*> &loops);
ParallelRegion* getRegionByLine(const std::vector<ParallelRegion*> &regions, const std::string &file, const int line);
void fillRegionLinesStep2(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, std::vector<LoopGraph*>> &loopGraph);
int printParalleRegions(const char *fileName, std::vector<ParallelRegion*> &regions);
