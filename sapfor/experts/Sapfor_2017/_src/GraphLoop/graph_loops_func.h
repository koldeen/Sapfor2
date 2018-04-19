#pragma once

#include <vector>
#include <map>
#include "graph_loops.h"

void loopGraphAnalyzer(SgFile *file, std::vector<LoopGraph*> &loopGraph);
void findAllRefsToLables(SgStatement *st, std::map<int, std::vector<int>> &labelsRef);
