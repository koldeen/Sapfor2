#pragma once

#include "../Utils/utils.h"
#include <map>

int perform_time(SgFile *file, SgStatement *src, std::map<int, Gcov_info> &gCovInfo, int rec_level = 0);