#pragma once

#include <vector>
#include <map>
#include "graph_loops.h"
#include "../Distribution/DvmhDirective.h"

struct SpfInterval;

void loopGraphAnalyzer(SgFile *file, std::vector<LoopGraph*> &loopGraph, const std::vector<SpfInterval*> &statisticTimes, std::vector<Messages> &messages);
void findAllRefsToLables(SgStatement *st, std::map<int, std::vector<int>> &labelsRef, bool includeWrite = true);
std::map<LoopGraph*, ParallelDirective*> findAllDirectives(SgFile *file, const std::vector<LoopGraph*> &loops, const int regId);
std::vector<std::tuple<DIST::Array*, std::vector<long>, std::pair<std::string, int>>> findAllSingleRemotes(SgFile *file, const int regId, std::vector<ParallelRegion*> &regions);
std::map<DIST::Array*, std::vector<long>> fillRemoteInParallel(Statement *st);
bool hasThisIds(SgStatement *loop, std::vector<int> &lines, const std::set<int> &IDs);
bool checkRegionEntries(SgStatement *begin, SgStatement *end, std::vector<Messages> &messagesForFile);