#pragma once

#include "ParRegions.h"
#include "SgUtils.h"
#include "../GraphCall/graph_calls.h"

std::set<ParallelRegion*> getRegionByLine2(const std::vector<ParallelRegion*> &regions, const std::string &file, const int line);
void fillRegionArrays(std::vector<ParallelRegion*> &regions, const std::map<std::string, CommonBlock> &commonBlocks, std::set<std::string> &allUsedCommonArrays);
void fillRegionFunctions(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> allFuncInfo, std::set<std::string> &allCommonFunctions);
bool checkRegions(const std::vector<ParallelRegion*> &regions);
void resolveRegions(const std::vector<ParallelRegion*> &regions);
