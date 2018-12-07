#pragma once

#include <string>
#include <map>

#include "dvm.h"
#include "../Utils/errors.h"
#include "gcov_info.h"

void parse_gcovfile(SgFile *file, const std::string &basefileName, std::map<int, Gcov_info> &gCovInfo, bool keep);
bool __gcov_doesThisLineExecuted(const std::string &file, const int line);
std::pair<int, int> __gcov_GetExecuted(const std::string &file, const int line);
void parseTimesDvmStatisticFile(const char *file, std::map<std::string, std::map<int, double>> &timesFromDvmStat);
