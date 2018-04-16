#pragma once

#include "graph_calls.h"
#include "../GraphLoop/graph_loops.h"

void functionAnalyzer(SgFile *file, std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);
int CreateCallGraphWiz(const char *fileName, const std::map<std::string, std::vector<FuncInfo*>> &funcByFile);
int CheckFunctionsToInline(SgProject *proj, const std::map<std::string, int> &files, const char *fileName,
    std::map<std::string, std::vector<FuncInfo*>> &funcByFile, const std::map<std::string, std::vector<LoopGraph*>> &loopGraph,
    std::map<std::string, std::vector<Messages>> &allMessages, bool needToAddErrors);
std::string removeString(const std::string toRemove, const std::string inStr);
FuncInfo* isUserFunctionInProject(const std::string &func);
std::string convertToString(const FuncInfo *currFunc);
void checkForRecursion(SgFile *file, std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::vector<Messages> &messagesForFile);
void findDeadFunctionsAndFillCallTo(std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, std::vector<Messages>> &allMessages);
void createLinksBetweenFormalAndActualParams(std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                                            const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays);
bool isPassFullArray(SgExpression *ex);
void createMapOfFunc(const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::map<std::string, FuncInfo*> &mapFuncInfo);
void doMacroExpand(SgFile *file, std::vector<Messages> &messages);
void updateFuncInfo(const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);
void printParInfo(const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);