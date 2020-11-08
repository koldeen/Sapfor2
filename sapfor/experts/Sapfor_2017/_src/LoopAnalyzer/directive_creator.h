#pragma once

#include "../Distribution/Distribution.h"
#include "../Utils/errors.h"
#include "../GraphLoop/graph_loops.h"
#include "../Utils/types.h"

void createParallelDirectives(const std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo,
                              std::vector<ParallelRegion*> regions, std::map<int, LoopGraph*> &sortedLoopGraph,
                              const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                              std::vector<Messages> &messagesForFile);

void selectParallelDirectiveForVariant(File* file,
                                       ParallelRegion* currReg,
                                       DIST::GraphCSR<int, double, attrType>& reducedG,
                                       DIST::Arrays<int>& allArrays,
                                       const std::vector<LoopGraph*>& loopGraph,
                                       const std::map<int, LoopGraph*>& mapLoopGraph,
                                       const std::map<std::string, FuncInfo*>& mapFuncInfo,
                                       const std::vector<std::pair<DIST::Array*, const DistrVariant*>>& distribution,
                                       const std::vector<AlignRule>& alignRules,
                                       std::vector<std::pair<int, std::pair<std::string, std::vector<Expression*>>>>& toInsert,
                                       const uint64_t regionId,
                                       const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls,
                                       const std::map<LoopGraph*, void*>& depInfoForLoopGraph,
                                       std::vector<Messages>& messages);

void filterParallelDirectives(const std::map<std::string, std::vector<LoopGraph*>>& loopGraph,
                              std::map<std::string, std::vector<std::pair<int, std::pair<std::string, std::vector<Expression*>>>>>& createdDirectives);

bool analyzeLoopBody(LoopGraph* loopV,
                     std::map<DIST::Array*, std::vector<std::pair<bool, std::pair<std::string, int>>>>& leftValues,
                     std::map<DIST::Array*, std::vector<std::pair<bool, std::map<std::string, std::pair<int, int>>>>>& rightValues,
                     std::string& base,
                     const std::map<DIST::Array*, std::vector<bool>>& dimsNotMatch,
                     const std::map<std::string, FuncInfo*>& mapFuncInfo);

bool addRedistributionDirs(File *file, const std::vector<std::pair<DIST::Array*, const DistrVariant*>> &distribution,
                           std::vector<std::pair<int, std::pair<std::string, std::vector<Expression*>>>> &toInsert,
                           LoopGraph *current, const std::map<int, LoopGraph*> &loopGraph,
                           ParallelDirective *currParDir, const uint64_t regionId, std::vector<Messages> &messages,
                           const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);

std::vector<std::pair<std::string, std::vector<Expression*>>> groupRealignsDirs(const std::vector<std::pair<std::string, std::vector<Expression*>>>& toRealign);