#pragma once

#include <string>
#include <set>
#include <map>

#include "../Utils/AstWrapper.h"
#include "../GraphLoop/graph_loops.h"
#include "../Distribution/DvmhDirective.h"

bool isSPF_NoInline(Statement *stPrev);

template<typename fillType>
void fillPrivatesFromComment(Statement *st, std::set<fillType> &privates);

template<typename fillType>
void fillReductionsFromComment(Statement *st, std::map<std::string, std::set<fillType>> &reduction, bool moduleNameAdd = false);

template<typename fillType>
void fillReductionsFromComment(Statement *st, std::map<std::string, std::set<std::tuple<fillType, fillType, int>>> &reduction, bool moduleNameAdd = false);

template<typename fillType>
void fillParameterFromComment(Statement *st, std::vector<std::pair<fillType, Expression*>> &identExprs);

template<typename fillType>
void fillShadowAcrossFromComment(const int type, Statement *st, std::vector<std::pair<std::pair<fillType, std::string>, std::vector<std::pair<int, int>>>> &data);

template<typename fillType>
void fillShadowAcrossFromParallel(const int type, Statement *st, std::vector<std::pair<std::pair<fillType, std::string>, std::vector<std::pair<int, int>>>> &data, std::set<fillType> &corner);

template<typename fillType>
void fillRemoteFromComment(Statement *st, std::map<std::pair<fillType, std::string>, Expression*> &remote, bool isFull = false, int type = SPF_PARALLEL_DIR);

void fillAcrossInfoFromDirectives(const LoopGraph *loopInfo, std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> &acrossInfo);
void fillInfoFromDirectives(const LoopGraph *loopInfo, ParallelDirective *directive);

void fillFissionPrivatesExpansionFromComment(Statement *stIn, std::vector<std::string> &vars);

template<typename fillType>
void fillShrinkFromComment(Statement *stIn, std::vector<std::pair<fillType, std::vector<int>>> &varDims);

template<typename fillType>
void fillCheckpointFromComment(Statement *stIn, std::map<int, Expression*> &clauses, std::set<fillType> &vars, std::set<fillType> &expt);

struct OmpDir
{
    std::set<std::string> privVars;
    std::set<std::string> threadPrivVars;
    std::map<std::string, std::set<std::string>> redVars;
    std::set<std::string> keys;
};

void removeOmpDir(void* stIn);
std::vector<OmpDir> parseOmpDirs(void* st, const std::set<std::string>& globalPriv, bool forDo = false);