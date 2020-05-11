#pragma once

#include "../GraphCall/graph_calls.h"
#include <map>
#include <string>
#include <vector>

bool duplicateFunctions(const std::map<std::string, std::vector<FuncInfo*>> &allFuncs, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCall, std::map<std::string, std::vector<Messages>>& messages);

void removeCopies(const std::map<std::string, std::vector<FuncInfo*>>& funcs);
void restoreCopies(SgFile* file);