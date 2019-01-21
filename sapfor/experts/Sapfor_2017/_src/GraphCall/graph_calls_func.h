#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>

#include "graph_calls.h"
#include "../GraphLoop/graph_loops.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../DynamicAnalysis/gCov_parser_func.h"

namespace Distribution
{
    class ArrayAccessInfo;
}
namespace DIST = Distribution;

int CreateCallGraphViz(const char *fileName, const std::map<std::string, std::vector<FuncInfo*>> &funcByFile, std::map<std::string, CallV> &V, std::vector<std::string> &E);
int CreateFuncInfo(const char *fileName, const std::map<std::string, std::vector<FuncInfo*>> &funcByFile);
std::string removeString(const std::string &toRemove, const std::string &inStr);
FuncInfo* isUserFunctionInProject(const std::string &func);
std::string convertToString(const FuncInfo *currFunc);
void findDeadFunctionsAndFillCallTo(std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, std::vector<Messages>> &allMessages, bool noPrint = false);
void createLinksBetweenFormalAndActualParams(std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                                            const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays);
void createMapOfFunc(const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, FuncInfo*> &mapFuncInfo);
void createMapOfFunc(const std::vector<FuncInfo*> &allFuncInfo, std::map<std::string, FuncInfo*> &mapFuncInfo);
void createMapOfFunc(const std::vector<FuncInfo*> &allFuncInfo, std::map<std::pair<std::string, int>, FuncInfo*> &mapFuncInfo);

void updateFuncInfo(const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);

#if __SPF
void functionAnalyzer(SgFile *file, std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, bool dontFillFuncParam = false);
int CheckFunctionsToInline(SgProject *proj, const std::map<std::string, int> &files, const char *fileName,
                           std::map<std::string, std::vector<FuncInfo*>> &funcByFile, const std::map<std::string, std::vector<LoopGraph*>> &loopGraph,
                           std::map<std::string, std::vector<Messages>> &allMessages, bool needToAddErrors,
                           const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls, const std::vector<ParallelRegion*> &regions);
void checkForRecursion(SgFile *file, std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::vector<Messages> &messagesForFile);
bool isPassFullArray(SgExpression *ex);
void doMacroExpand(SgFile *file, std::vector<Messages> &messages);
std::map<std::string, std::set<SgSymbol*>> moduleRefsByUseInFunction(SgStatement *stIn);
#endif

