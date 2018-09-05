#pragma once

#include "ParRegions.h"
#include "../Utils/SgUtils.h"
#include "Utils/SgUtils.h"
#include "../GraphCall/graph_calls.h"

void fillRegionArrays(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, const std::map<std::string, CommonBlock> &commonBlocks, std::set<DIST::Array*> &allUsedCommonArrays);
void fillRegionFunctions(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::set<FuncInfo*> &allCommonFunctions);

bool checkRegions(const std::vector<ParallelRegion*> &regions, std::map<std::string, std::vector<Messages>> &SPF_messages);

void resolveParRegions(std::vector<ParallelRegion*> &regions, const std::map<std::string, CommonBlock> &commonBlocks, const std::set<FuncInfo*> &allCommonFunctions, const std::set<DIST::Array*> &allUsedCommonArrays, std::map<FuncInfo*, std::map<DIST::Array*, std::pair<SgSymbol*, SgSymbol*>>> &createdCommonArrays, std::map<FuncInfo*, SgStatement*> &createdCommonBlocks);

int printCheckRegions(const char *fileName, const std::vector<ParallelRegion*> &regions, const std::set<DIST::Array*> &allUsedCommonArrays, const std::set<FuncInfo*> &allCommonFunctions);
