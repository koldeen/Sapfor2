#pragma once

#include <vector>
#include <map>
#include "graph_loops.h"
#include "../Distribution/DvmhDirective.h"

void loopGraphAnalyzer(SgFile *file, std::vector<LoopGraph*> &loopGraph);
void findAllRefsToLables(SgStatement *st, std::map<int, std::vector<int>> &labelsRef);
std::map<LoopGraph*, ParallelDirective*> findAllDirectives(SgFile *file, const std::vector<LoopGraph*> &loops, const int regId);