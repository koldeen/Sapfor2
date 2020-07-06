#include "dvm.h"
#include "../GraphLoop/graph_loops.h"
#include "../SageAnalysisTool/depGraph.h"
#include <vector>

int combineLoops(SgFile *file, std::vector<LoopGraph*> &loopGraphs, std::vector<Messages> &messages, const std::pair<std::string, int>& onPlace);
