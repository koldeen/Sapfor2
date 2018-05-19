#pragma once

#include <map>
#include <stack>
#include "../SageAnalysisTool/depGraph.h"
#include <dependency/DependencyType.hpp>
#include "../GraphLoop/graph_loops.h"

void reverseCreatedNestedLoops(const std::string &file, std::vector<LoopGraph*> &loopsInFile);
bool createNestedLoops(LoopGraph *current, const std::map<LoopGraph*, depGraph*> &depInfoForLoopGraph,
                       std::vector<Messages> &messages);

namespace Sapfor2017 {
    using SageTransform::DependencyType;

    class CreateNestedLoopsUtils {
    public:
        static std::pair<SgForStmt *, depGraph *>
        getDepGraph(LoopGraph *loopGraph, const std::map<LoopGraph *, depGraph *> &depInfoForLoopGraph);

        static std::map<SgSymbol *, DependencyType>
        buildTransformerDependencyMap(SgForStmt *outerLoop, depGraph *outerDepGraph, depGraph *innerDepGraph);

        static DependencyType fromDepNode(depNode *node);
    };
}
