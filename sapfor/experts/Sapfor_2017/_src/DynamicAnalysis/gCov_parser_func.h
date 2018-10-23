#pragma once

#include <string>
#include <map>

#include "../Utils/errors.h"

#include "gcov_info.h"

void parse_gcovfile(const std::string basefileName, std::map<int, Gcov_info> &gCovInfo);

