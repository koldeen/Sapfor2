#pragma once

#include "../GraphLoop/graph_loops.h"
#include "../Utils/errors.h"

void createDistributionDirs(DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays, 
                            DataDirective &dataDirectives, std::map<std::string, std::vector<Messages>> &allMessages, 
                            const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCall);
int createAlignDirs(DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays, DataDirective &dataDirectives, 
                    const int regionId, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCall, std::map<std::string, std::vector<Messages>> &SPF_messages);