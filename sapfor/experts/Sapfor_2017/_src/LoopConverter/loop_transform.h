#pragma once

#include <map>
#include <stack>
#include "../SageAnalysisTool/depGraph.h"
#include "../GraphLoop/graph_loops.h"

void reverseCreatedNestedLoops(const std::string &file, std::vector<LoopGraph*> &loopsInFile);
bool createNestedLoops(LoopGraph *current, const std::map<LoopGraph*, depGraph*> &depInfoForLoopGraph,
                       std::vector<Messages> &messages);