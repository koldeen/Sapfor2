#pragma once

#include "ParRegions.h"
#include "../Utils/SgUtils.h"
#include "../Utils/errors.h"

bool extendDecreaseReg(const std::string &fileName, const int startLine, const int endLine, const std::string &regName, const std::vector<ParallelRegion*> &regions, std::vector<Messages> &messagesForFile, const bool toDelete = false);
