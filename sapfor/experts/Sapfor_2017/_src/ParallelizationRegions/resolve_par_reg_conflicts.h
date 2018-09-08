#pragma once

#include "ParRegions.h"
#include "../Utils/SgUtils.h"
#include "Utils/SgUtils.h"
#include "../GraphCall/graph_calls.h"

void fillRegionArrays(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, const std::map<std::string, CommonBlock> &commonBlocks, std::map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays);
void fillRegionFunctions(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::set<FuncInfo*> &allCommonFunctions);

bool checkRegions(const std::vector<ParallelRegion*> &regions, std::map<std::string, std::vector<Messages>> &SPF_messages);

void resolveParRegions(std::vector<ParallelRegion*> &regions, const std::map<std::string, CommonBlock> &commonBlocks, const std::set<FuncInfo*> &allCommonFunctions, const std::map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays, std::map<std::string, std::map<DIST::Array*, std::pair<SgSymbol*, SgSymbol*>>> &createdCommonArrays, std::map<std::string, SgStatement*> &createdCommonBlocks, std::set<FuncInfo*> &insertedCommonArrays, std::set<FuncInfo*> &insertedCommonBlocks);

int printCheckRegions(const char *fileName, const std::vector<ParallelRegion*> &regions, const std::map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays, const std::set<FuncInfo*> &allCommonFunctions);
