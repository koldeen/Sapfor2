#include "dvm.h"
#include "../GraphLoop/graph_loops.h"
#include <string>
#include <vector>
#include <set>


int breedArrays(SgFile *file, std::vector<LoopGraph*> &loopGraphs, const std::set<SgSymbol*> &doForThisPrivates, std::vector<Messages> &messages);
