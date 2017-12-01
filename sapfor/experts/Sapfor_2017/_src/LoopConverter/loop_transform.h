#pragma once

#include <map>
#include "../SageAnalysisTool/depGraph.h"
#include <dependency/DependencyType.hpp>
#include "../GraphLoop/graph_loops.h"

bool createNestedLoops(LoopGraph *current, const std::map<LoopGraph*, depGraph*> &depInfoForLoopGraph,
                       std::vector<Messages> &messages);

namespace Sapfor2017
{
    class CreateNestedLoopsUtils
    {
    public:
        static std::pair<SgForStmt *, depGraph *> getDepGraph(LoopGraph *loopGraph, const std::map<LoopGraph*, depGraph*> &depInfoForLoopGraph);
        static std::map<SgSymbol *, DepType> buildTransformerDependencyMap(SgForStmt *outerLoop, depGraph *outerDepGraph, depGraph *innerDepGraph);
        static DepType fromDepNode(depNode *node);
    };
}
