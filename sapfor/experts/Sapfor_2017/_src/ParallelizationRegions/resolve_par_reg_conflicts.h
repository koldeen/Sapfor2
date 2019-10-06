#pragma once

#include "ParRegions.h"
#include "../Utils/SgUtils.h"
#include "../Utils/errors.h"
#include "../GraphCall/graph_calls.h"

void fillRegionIntervals(std::vector<ParallelRegion*> &regions);
void fillRegionArrays(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, const std::map<std::string, CommonBlock> &commonBlocks);
void fillRegionFunctions(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);
bool checkRegions(const std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, std::vector<Messages>> &SPF_messages);
int printCheckRegions(const char *fileName, const std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);

bool checkRegionsResolving(const std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, const std::map<std::string, CommonBlock> &commonBlocks, std::map<std::string, std::vector<Messages>> &SPF_messages, bool mpiProgram);
int resolveParRegions(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, std::vector<Messages>> &SPF_messages, bool mpiProgram);
void insertRealignsBeforeFragments(ParallelRegion* reg, SgFile* file, const std::set<DIST::Array*>& distrArrays, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);