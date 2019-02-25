#pragma once 

#include <vector>
#include <list>
#include "../Distribution/Distribution.h"
#include "../CreateInterTree/CreateInterTree.h"

int predictScheme(ParallelRegion *reg, const std::vector<std::pair<DIST::Array*, const DistrVariant*>> &distVar, 
                  const std::set<DIST::Array*> &allArrays, const std::map<LoopGraph*, ParallelDirective*> &dirsToPredict,
                  std::map<std::string, std::vector<SpfInterval*>> &intervals, std::map<std::string, std::vector<Messages>> &messagesByFile, 
                  const std::vector<std::tuple<DIST::Array*, std::vector<long>, std::pair<std::string, int>>> &allSingleRemotes,
                  const int maxSizeDist, const int procNum);

std::vector<std::vector<long>> getTopologies(const int procNum, const int maxSizeDist);