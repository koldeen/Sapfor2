#pragma once

#include <vector>
#include <string>
#include <map>
#include "dvm.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../ParallelizationRegions/ParRegions_func.h"

using std::vector;

void EndDoLoopChecker(SgFile *file, std::vector<int> &errors);
void IncludeChecker(SgFile *file, const std::string &fileName, std::set<std::pair<std::string, int>> &errors);
void EquivalenceChecker(SgFile *file, const std::string &fileName, vector<ParallelRegion*> &regions, std::set<std::pair<std::string, int>> &errors);
void VarDeclCorrecter(SgFile *file);
void DvmDirectiveChecker(SgFile *file, std::map<std::string, std::vector<int>> &errors);
int VerifyFile(SgFile *file);