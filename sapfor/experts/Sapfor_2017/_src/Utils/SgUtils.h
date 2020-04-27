#pragma once

#include "dvm.h"
#include "utils.h"
#include "../Distribution/Distribution.h"
#include "../GraphCall/graph_calls.h"
#include "../DynamicAnalysis/gcov_info.h"

SgStatement* declaratedInStmt(SgSymbol *toFind, std::vector<SgStatement*> *allDecls = NULL, bool printInternal = true);

#include "DefUseList.h"
#include "CommonBlock.h"

std::string removeIncludeStatsAndUnparse(SgFile *file, const char *fileName, const char *fout, std::set<std::string> &allIncludeFiles, bool outFree, const std::map<std::string, std::set<std::string>> &moduleUsesByFile, const std::map<std::string, std::string>& moduleDelcs, bool toString);
SgSymbol* findSymbolOrCreate(SgFile *file, const std::string toFind, SgType *type = NULL, SgStatement *scope = NULL);
void recExpressionPrint(SgExpression *exp);
void removeSubstrFromStr(std::string &str, const std::string &del);
void getModulesAndFunctions(SgFile *file, std::vector<SgStatement*> &modulesAndFunctions);
void findModulesInFile(SgFile *file, std::vector<SgStatement*> &modules);
void tryToFindPrivateInAttributes(SgStatement *st, std::set<std::string> &privatesVars);

void fillNonDistrArraysAsPrivate(SgStatement *st,
                                 const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaredArrays,
                                 const std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> &declaratedArraysSt,
                                 std::set<std::string> &privatesVars);

DIST::Array* getArrayFromDeclarated(SgStatement *st, const std::string &arrayName);

void initTags();
bool isDVM_stat(SgStatement *st);
bool isSPF_stat(SgStatement *st);
bool isEqExpressions(SgExpression *left, SgExpression *right, std::map<SgExpression*, std::string> &collection);
void getCommonBlocksRef(std::map<std::string, std::vector<SgExpression*>> &commonBlocks, SgStatement *start, SgStatement *end, const std::string *nameToSkip = NULL);

std::tuple<int, std::string, std::string> getFromUniqTable(SgSymbol *symb);
std::tuple<int, std::string, std::string> getUniqName(const std::map<std::string, std::vector<SgExpression*>> &commonBlocks, SgStatement *decl, SgSymbol *symb);
SgStatement* findMainUnit(SgProject *proj, std::map<std::string, std::vector<Messages>>& SPF_messages);

template<typename IN_TYPE, typename OUT_TYPE>
const std::vector<OUT_TYPE> getAttributes(IN_TYPE st, const std::set<int> dataType);

template<typename IN_TYPE>
void deleteAttributes(IN_TYPE st, const std::set<int> dataType);

void constructDefUseStep1(SgFile *file, std::map<std::string, std::vector<DefUseList>> &defUseByFunctions, std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, std::vector<Messages> &messages);
void constructDefUseStep2(SgFile *file, std::map<std::string, std::vector<DefUseList>> &defUseByFunctions);
std::set<std::string> getAllDefVars(const std::string &funcName);
std::set<std::string> getAllUseVars(const std::string &funcName);
const std::vector<DefUseList>& getAllDefUseVarsList(const std::string &funcName);
const std::vector<DefUseList> getAllDefUseVarsList(const std::string &funcName, const std::string varName);
int printDefUseSets(const char *fileName, const std::map<std::string, std::vector<DefUseList>> &defUseLists);
int printCommonBlocks(const char *fileName, const std::map<std::string, CommonBlock> &commonBlocks);
void groupDeclarations(SgFile *file);

bool ifSymbolExists(SgFile *file, const std::string &symbName);
std::string checkSymbNameAndCorrect(const std::string& symbName, const std::string complite = "_");
const CommonBlock* isArrayInCommon(const std::map<std::string, CommonBlock> &commonBlocks, const DIST::Array *array);

std::vector<DIST::Array*> fillArraysFromDir(Statement *st);

SgSymbol* getFromModule(const std::map<std::string, std::set<SgSymbol*>> &byUse, SgSymbol *orig, const std::set<std::string>& usedInBlock, bool processAsModule = false);
std::map<std::string, std::set<std::string>> createMapOfModuleUses(SgFile* file);
void printSymbolTable(SgFile *file, std::string filter = "");
SgStatement* getFuncStat(SgStatement *st, const std::set<int> additional = std::set<int>());
std::map<SgStatement*, std::vector<DefUseList>> createDefUseMapByPlace();
SgStatement* duplicateProcedure(SgStatement* toDup, const std::string& newName, bool withAttributes = false, bool withComment = false, bool withSameLines = true);

void fillModuleUse(SgFile* file, std::map<std::string, std::set<std::string>>& moduleUses, std::map<std::string, std::string>& moduleDecls);
void filterModuleUse(std::map<std::string, std::set<std::string>>& moduleUses, std::map<std::string, std::string>& moduleDecls);
SgExpression* makeExprList(const std::vector<SgExpression*>& items);
std::string unparseProjectToString(SgFile* file, const int curr_regime);

SgStatement* makeDeclaration(SgStatement* curr, const std::vector<SgSymbol*>& s, std::vector<SgExpression*>* inits = NULL);

int parseFiles(const char* proj, std::vector<std::string>& filesCompilationOrder);
int pppaAnalyzer(const char* options);

int getNextFreeLabel();

void fillUsedModulesInFunction(SgStatement *st, std::vector<SgStatement*> &useStats);
void fillVisibleInUseVariables(SgStatement *useSt, std::map<string, SgSymbol*> &vars);