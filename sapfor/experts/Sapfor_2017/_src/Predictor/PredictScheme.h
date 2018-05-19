#pragma once
#include <vector>

#include "dvm.h"
#include "../GraphLoop/graph_loops.h"

void processFileToPredict(SgFile *file, std::vector<LoopGraph*> &loops);