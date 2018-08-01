#pragma once

#include <vector>
#include <string>
#include <map>
#include "dvm.h"
#include "../Utils/errors.h"

bool EndDoLoopChecker(SgFile *file, std::vector<Messages> &currM);
bool IncludeChecker(SgFile *file, const std::string &fileName, std::vector<Messages> &currM);
void VarDeclCorrecter(SgFile *file);
bool DvmDirectiveChecker(SgFile *file, std::map<std::string, std::vector<int>> &errors, const int, const int);
int VerifyFile(SgFile *file);