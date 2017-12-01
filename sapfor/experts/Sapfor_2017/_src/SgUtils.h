#pragma once

#include "dvm.h"
#include "utils.h"
#include "Distribution/Distribution.h"

void removeIncludeStatsAndUnparse(SgFile *file, const char *fileName, const char *fout, std::set<std::string> &allIncludeFiles);
SgSymbol* findSymbolOrCreate(SgFile *file, const std::string toFind);
void recExpressionPrint(SgExpression *exp);
void removeSubstrFromStr(std::string &str, const std::string &del);
void getModulesAndFunctions(SgFile *file, std::vector<SgStatement*> &modulesAndFunctions);
void findModulesInFile(SgFile *file, std::vector<SgStatement*> &modules);
void tryToFindPrivateInAttributes(SgStatement *st, 
                                  const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                  const std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> &declaratedArraysSt,
                                  std::set<std::string> &privatesVars);
SgStatement* declaratedInStmt(SgSymbol *toFind);
bool isSPF_comment(SgStatement *st);
void initTags();
bool isDVM_stat(SgStatement *st);
bool isSPF_stat(SgStatement *st);
bool isEqExpressions(SgExpression *left, SgExpression *right, std::map<SgExpression*, std::string> &collection);
void getCommonBlocksRef(std::map<std::string, SgStatement*> &commonBlocks, SgStatement *start, SgStatement *end);

extern std::map<std::pair<std::string, int>, std::tuple<int, std::string, std::string>> tableOfUniqNames;
std::tuple<int, std::string, std::string> getUniqName(const std::map<std::string, SgStatement*> &commonBlocks, SgStatement *decl, SgSymbol *symb);