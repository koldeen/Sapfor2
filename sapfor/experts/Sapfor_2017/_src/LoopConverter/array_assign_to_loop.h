#pragma once
#include <vector>

#include "dvm.h"
#include "../errors.h"

void convertFromAssignToLoop(SgFile *file, std::vector<Messages> &messagesForFile);
void restoreAssignsFromLoop(SgFile *file);