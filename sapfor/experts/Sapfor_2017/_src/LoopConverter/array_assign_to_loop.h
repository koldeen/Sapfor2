#pragma once
#include <vector>

#include "dvm.h"
#include "../Utils/errors.h"

void convertFromAssignToLoop(SgFile *file, std::vector<Messages> &messagesForFile);
void restoreAssignsFromLoop(SgFile *file);
void restoreConvertedLoopForParallelLoops(SgFile *file, bool reversed = false);