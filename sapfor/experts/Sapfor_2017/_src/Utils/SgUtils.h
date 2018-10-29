#pragma once

#include "dvm.h"
#include "utils.h"
#include "../Distribution/Distribution.h"
#include "../GraphCall/graph_calls.h"

SgStatement* declaratedInStmt(SgSymbol *toFind, std::vector<SgStatement*> *allDecls = NULL);

#include "DefUseList.h"
#include "CommonBlock.h"

void removeIncludeStatsAndUnparse(SgFile *file, const char *fileName, const char *fout, std::set<std::string> &allIncludeFiles, bool outFree);
SgSymbol* findSymbolOrCreate(SgFile *file, const std::string toFind, SgType *type = NULL, SgStatement *scope = NULL);
void recExpressionPrint(SgExpression *exp);
void removeSubstrFromStr(std::string &str, const std::string &del);
void getModulesAndFunctions(SgFile *file, std::vector<SgStatement*> &modulesAndFunctions);
void findModulesInFile(SgFile *file, std::vector<SgStatement*> &modules);
void tryToFindPrivateInAttributes(SgStatement *st, std::set<std::string> &privatesVars);

void fillNonDistrArraysAsPrivate(SgStatement *st,
                                 const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                 const std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> &declaratedArraysSt,
                                 std::set<std::string> &privatesVars);

DIST::Array* getArrayFromDeclarated(SgStatement *st, const std::string &arrayName);

bool isSPF_comment(const int variant);
void initTags();
bool isDVM_stat(SgStatement *st);
bool isSPF_stat(SgStatement *st);
bool isEqExpressions(SgExpression *left, SgExpression *right, std::map<SgExpression*, std::string> &collection);
void getCommonBlocksRef(std::map<std::string, std::vector<SgExpression*>> &commonBlocks, SgStatement *start, SgStatement *end, const std::string *nameToSkip = NULL);

std::tuple<int, std::string, std::string> getFromUniqTable(SgSymbol *symb);
std::tuple<int, std::string, std::string> getUniqName(const std::map<std::string, std::vector<SgExpression*>> &commonBlocks, SgStatement *decl, SgSymbol *symb);
SgStatement* findMainUnit(SgProject *proj);

template<typename IN_TYPE, typename OUT_TYPE>
const std::vector<OUT_TYPE> getAttributes(IN_TYPE st, const std::set<int> dataType);

void constructDefUseStep1(SgFile *file, std::map<std::string, std::vector<DefUseList>> &defUseByFunctions, std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);
void constructDefUseStep2(SgFile *file, std::map<std::string, std::vector<DefUseList>> &defUseByFunctions);
std::set<std::string> getAllDefVars(const std::string &funcName);
std::set<std::string> getAllUseVars(const std::string &funcName);
const std::vector<DefUseList>& getAllDefUseVarsList(const std::string &funcName);
const std::vector<DefUseList> getAllDefUseVarsList(const std::string &funcName, const std::string varName);
int printDefUseSets(const char *fileName, const std::map<std::string, std::vector<DefUseList>> &defUseLists);
int printCommonBlocks(const char *fileName, const std::map<std::string, CommonBlock> &commonBlocks);
void groupDeclarations(SgFile *file);

bool ifSymbolExists(SgFile *file, const std::string &symbName);