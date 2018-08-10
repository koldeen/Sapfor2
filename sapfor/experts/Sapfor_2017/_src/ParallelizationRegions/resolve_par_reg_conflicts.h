#pragma once

#include "ParRegions.h"
#include "../Utils/SgUtils.h"
#include "Utils/SgUtils.h"
#include "../GraphCall/graph_calls.h"

void fillRegionArrays(std::vector<ParallelRegion*> &regions, const std::map<std::string, CommonBlock> &commonBlocks, std::set<std::string> &allUsedCommonArrays, std::map<std::string, ParallelRegionArray> &allCommonArrays);
void fillRegionFunctions(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::set<std::string> &allCommonFunctions);

bool checkRegions(const std::vector<ParallelRegion*> &regions, std::map<std::string, std::vector<Messages>> &SPF_messages);

void createFunctionsAndArrays(std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, const std::set<std::string> &allCommonFunctions, const std::set<std::string> &allUsedCommonArrays);
void replaceFunctionsAndArrays(const std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, const std::set<std::string> &allCommonFunctions);
void insertArraysCopy(const std::vector<ParallelRegion*> &regions, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);

void printCheckRegions(const std::vector<ParallelRegion*> &regions, const std::set<std::string> &allUsedCommonArrays, const std::set<std::string> &allCommonFunctions, const std::map<std::string, ParallelRegionArray> &allCommonArrays);
int printCheckRegions(const char *fileName, const std::vector<ParallelRegion*> &regions, const std::set<std::string> &allUsedCommonArrays, const std::set<std::string> &allCommonFunctions, const std::map<std::string, ParallelRegionArray> &allCommonArrays);
