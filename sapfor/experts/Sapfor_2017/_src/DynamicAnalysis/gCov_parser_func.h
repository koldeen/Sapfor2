#pragma once

#include <string>
#include <map>
#include <vector>

#include "dvm.h"
#include "../Utils/errors.h"
#include "gcov_info.h"
#include "../CreateInterTree/CreateInterTree.h"

void parse_gcovfile(SgFile *file, const std::string &basefileName, std::map<int, Gcov_info> &gCovInfo, bool keep);
bool __gcov_doesThisLineExecuted(const std::string &file, const int line);
std::pair<int, int64_t> __gcov_GetExecuted(const std::string &file, const int line);
void parseTimesDvmStatisticFile(const std::string &file, std::map<std::string, std::vector<Interval*>> &intervals);
