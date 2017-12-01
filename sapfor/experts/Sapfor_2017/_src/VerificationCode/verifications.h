#pragma once

#include <vector>
#include "dvm.h"

void EndDoLoopChecker(SgFile *file, std::vector<int> &errors);
void IncludeChecker(SgFile *file, const std::string &fileName, std::set<std::pair<std::string, int>> &errors);
void VarDeclCorrecter(SgFile *file);
void DvmDirectiveChecker(SgFile *file, std::vector<int> &errors);
int VerifyFile(SgFile *file);