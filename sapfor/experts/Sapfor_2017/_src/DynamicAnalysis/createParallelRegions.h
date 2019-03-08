#pragma once

#include "../Utils/utils.h"

#include "./gcov_info.h"
#include "../CreateInterTree/CreateInterTree.h"
#include "../GraphCall/graph_calls.h"

#include <map>
#include <vector>

float performTime(SgFile *file, SgStatement *src, std::map<int, Gcov_info> &gCovInfo, std::map<std::string, std::vector<FuncInfo*>> &funcInfo, int rec_level = 0);
void createParallelRegions(SgFile *file, std::vector<SpfInterval*> &fileIntervals, std::map<int, Gcov_info> &gCovInfo, std::map<std::string, std::vector<FuncInfo*>> &funcInfo);