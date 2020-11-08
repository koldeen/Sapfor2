#pragma once

#include "../GraphLoop/graph_loops.h"
#include "../Utils/errors.h"

void createDistributionDirs(DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays, 
                            DataDirective &dataDirectives, std::map<std::string, std::vector<Messages>> &allMessages, 
                            const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCall, std::set<DIST::Array*> onlyThese = std::set<DIST::Array*>());
int createAlignDirs(DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays, DataDirective &dataDirectives, 
                    const uint64_t regionId, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCall, std::map<std::string, 
                    std::vector<Messages>> &SPF_messages, std::set<DIST::Array*> onlyThese = std::set<DIST::Array*>());
void checkDimsSizeOfArrays(const DIST::Arrays<int>& allArrays, std::map<std::string, std::vector<Messages>>& allMessages,
                           const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);