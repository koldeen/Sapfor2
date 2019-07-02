#pragma once

#include "../GraphCall/graph_calls.h"
#include <map>
#include <string>
#include <vector>

void duplicateFunctions(const std::map<std::string, std::vector<FuncInfo*>> &allFuncs);