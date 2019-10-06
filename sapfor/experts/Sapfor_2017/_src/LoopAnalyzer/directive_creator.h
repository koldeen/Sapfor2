#pragma once

#include "../Distribution/Distribution.h"
#include "../Utils/errors.h"
#include "../GraphLoop/graph_loops.h"
#include "../Utils/types.h"

void createParallelDirectives(const std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo,
                              std::vector<ParallelRegion*> regions, std::map<int, LoopGraph*> &sortedLoopGraph,
                              const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                              std::vector<Messages> &messagesForFile);