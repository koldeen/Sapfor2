#pragma once

#include "../GraphLoop/graph_loops_func.h"
#include "../GraphCall/graph_calls_func.h"

#include <vector>
#include <string>
#include <map>

struct LoopCheckResults
{
    bool usesIO;
    bool hasImpureCalls;

    std::vector<int> linesOfIO;

    LoopCheckResults() : usesIO(false), hasImpureCalls(false) { }
    LoopCheckResults(bool io, bool calls) : usesIO(io), hasImpureCalls(calls) { }
};

class LoopChecker 
{
    std::vector<LoopGraph*> &loopGraph;

    LoopCheckResults checkLoopForPurenessAndIO(const LoopGraph *loopNode, const std::map<std::string, FuncInfo*> &allFuncs) const;
    LoopCheckResults updateLoopNode(LoopGraph *loop, const std::map<std::string, FuncInfo*> &allFuncs);
public:
    explicit LoopChecker(std::vector<LoopGraph*> &graph) : loopGraph(graph) { }
    void updateLoopGraph(const std::map<std::string, FuncInfo*> &allFuncs);
};
