#pragma once

#include "graph_loops.h"

void loopGraphAnalyzer(SgFile *file, std::vector<LoopGraph*> &loopGraph);
void getRealArrayRefs(DIST::Array *addTo, DIST::Array *curr, std::set<DIST::Array*> &realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);
void getAllArrayRefs(DIST::Array *addTo, DIST::Array *curr, std::set<DIST::Array*> &realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);
void findAllRefsToLables(SgStatement *st, std::map<int, std::vector<int>> &labelsRef);