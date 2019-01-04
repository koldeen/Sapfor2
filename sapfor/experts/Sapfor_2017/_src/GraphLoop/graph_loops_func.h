#pragma once

#include <vector>
#include <map>
#include "graph_loops.h"
#include "../Distribution/DvmhDirective.h"

struct Interval;

void loopGraphAnalyzer(SgFile *file, std::vector<LoopGraph*> &loopGraph, const std::vector<Interval*> &statisticTimes, std::vector<Messages> &messages);
void findAllRefsToLables(SgStatement *st, std::map<int, std::vector<int>> &labelsRef, bool includeWrite = true);
std::map<LoopGraph*, ParallelDirective*> findAllDirectives(SgFile *file, const std::vector<LoopGraph*> &loops, const int regId);