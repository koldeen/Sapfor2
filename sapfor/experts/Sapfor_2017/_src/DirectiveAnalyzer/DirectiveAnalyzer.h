#pragma once

#include "dvm.h"
#include <vector>

#include "../GraphLoop/graph_loops.h"


void UniteNestedDirectives(SgFile *file, std::vector<LoopGraph*> &loopGraph);
