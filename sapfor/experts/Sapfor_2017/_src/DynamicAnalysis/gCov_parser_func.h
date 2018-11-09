#pragma once

#include <string>
#include <map>

#include "dvm.h"
#include "../Utils/errors.h"
#include "gcov_info.h"

void parse_gcovfile(SgFile *file, const std::string &basefileName, std::map<int, Gcov_info> &gCovInfo);

