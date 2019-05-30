#pragma once

#include <vector>

#include "dvm.h"
#include "../GraphCall/graph_calls.h"

extern void Private_Vars_Analyzer(SgStatement* start);
void PrivateAnalyzer(SgFile *file, std::vector<FuncInfo*> &funcs);
void PrivateAnalyzerForMain(SgStatement* start);