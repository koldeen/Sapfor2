#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <set>
#include "../GraphLoop/graph_loops.h"
#include "../GraphCall/graph_calls.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../SageAnalysisTool/depInterfaceExt.h"
#include "../AstWrapper.h"

#include "dvm.h"

typedef std::pair<std::pair<int, int>, std::pair<int, int>> attrType;
namespace DIST = Distribution;

enum REGIME { DATA_DISTR, COMP_DISTR, REMOTE_ACC, UNDEF };
enum REMOTE_BOOL { REMOTE_NONE = 0, REMOTE_TRUE = 1, REMOTE_FALSE = 3};

// loop_analyzer.cpp
bool checkExistence(SgExpression *exp, SgSymbol *doName);

void loopAnalyzer(SgFile *file, 
                  std::vector<ParallelRegion*> regions,
                  std::map<std::tuple<int, std::string, std::string>, 
                  DIST::Array*> &createdArrays,
                  std::vector<Messages> &messagesForFile,
                  REGIME regime,
                  const std::vector<FuncInfo*> &funcInfo,
                  std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                  std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> &declaratedArraysSt,
                  const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                  std::vector<LoopGraph*> *loopGraph = NULL);

void processLoopInformationForFunction(std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo);
void addToDistributionGraph(const std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);

void createParallelDirectives(const std::map<SgForStmt*, std::map<SgSymbol*, ArrayInfo>> &loopInfo,
                              std::vector<ParallelRegion*> regions,
                              const std::map<std::tuple<int, std::string, std::string>, DIST::Array*> &createdArrays,
                              const std::map<std::string, std::vector<SgStatement*>> &commonBlocks,
                              std::map<int, LoopGraph*> &sortedLoopGraph,
                              const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);

void selectParallelDirectiveForVariant(SgFile *file, 
                                       ParallelRegion *currReg,
                                       DIST::GraphCSR<int, double, attrType> &reducedG,
                                       DIST::Arrays<int> &allArrays,
                                       const std::vector<LoopGraph*> &loopGraph,
                                       const std::vector<std::pair<DIST::Array*, const DistrVariant*>> &distribution,
                                       const std::vector<AlignRule> &alignRules,
                                       std::vector<std::pair<int, std::pair<std::string, std::vector<Expression*>>>> &toInsert,
                                       const int regionId,
                                       const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                                       const std::map<LoopGraph*, depGraph*> &depInfoForLoopGraph,
                                       std::vector<Messages> &messages);

void printBlanks(const int sizeOfBlank, const int countOfBlanks);
bool isIntrinsic(const char *funName);

std::tuple<int, std::string, std::string> getUniqName(const std::map<std::string, SgStatement*> &commonBlocks, SgStatement *decl, SgSymbol *symb);
std::string getShortName(const std::tuple<int, std::string, std::string> &uniqKey);

void getAllDeclaratedArrays(SgFile *file, std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                            std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> &declaratedArraysSt);
void insertSpfAnalysisBeforeParalleLoops(const std::vector<LoopGraph*> &loops);

// dep_analyzer.cpp
void tryToFindDependencies(LoopGraph *currLoop, const std::map<int, std::pair<SgForStmt*, std::set<std::string>>> &allLoops,
                           std::set<SgStatement*> &funcWasInit, SgFile *file, std::vector<ParallelRegion*> regions, std::vector<Messages> *currMessages,
                           std::map<SgExpression*, std::string> &collection);

// allocations_prepoc.cpp
void preprocess_allocates(SgFile *file);

// insert_directive.cpp
void insertTempalteDeclarationToMainFile(SgFile *file, const DataDirective &dataDir,
                                         std::map<std::string, std::string> templateDeclInIncludes,
                                         const std::vector<std::string> &distrRules, const DIST::Arrays<int> &allArrays,
                                         const bool extractDir, const int regionId,
                                         const std::set<std::string> &includedToThisFile);

void insertDirectiveToFile(SgFile *file, const char *fin_name, const std::vector<std::pair<int, std::pair<std::string, 
                           std::vector<Expression*>>>> &toInsert, const bool extractDir, std::vector<Messages> &messagesForFile);

void insertDistributionToFile(SgFile *file, const char *fin_name, const DataDirective &dataDir,
                              const std::set<std::string> &distrArrays, const std::vector<std::string> &distrRules,
                              const std::vector<std::string> &alignRules, 
                              const std::map<std::string, std::vector<LoopGraph*>> &loopGraph,
                              const DIST::Arrays<int> &allArrays,
                              DIST::GraphCSR<int, double, attrType> &reducedG,
                              std::map<std::string, std::map<int, std::set<std::string>>> &commentsToInclude,
                              std::map<std::string, std::string> templateDeclInIncludes,
                              const bool extractDir, std::vector<Messages> &messagesForFile,
                              const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                              const int regionId);

void insertShadowSpecToFile(SgFile *file, const char *fin_name, const std::set<std::string> &distrArrays,
                            DIST::GraphCSR<int, double, attrType> &reducedG,
                            std::map<std::string, std::map<int, std::set<std::string>>> &commentsToInclude,
                            const bool extractDir, std::vector<Messages> &messagesForFile,
                            const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays);

void insertDistributionToFile(const char *origFile, const char *outFile, const std::map<int, std::set<std::string>> &commentsToInclude);
void removeDvmDirectives(SgFile *file);

void insertDistributeDirsToParallelRegions(const std::vector<ParallelRegionLines> *currLines,
                                           const std::vector<Statement*> &reDistrRulesBefore,
                                           const std::vector<Statement*> &reDistrRulesAfter,
                                           const std::vector<Statement*> &reAlignRules);

// spf_directive_preproc.cpp
bool preprocess_spf_dirs(SgFile *file, std::vector<Messages> &messagesForFile);
void addAcrossToLoops(LoopGraph *topLoop, const std::map<SgSymbol*, std::tuple<int, int, int>> &acrossToAdd, 
                      const std::map<int, std::pair<SgForStmt*, std::set<std::string>>> &allLoops, 
                      std::vector<Messages> &currMessages);
void addPrivatesToLoops(LoopGraph *currLoop, const std::vector<const depNode*> &privatesToAdd, 
                        const std::map<int, std::pair<SgForStmt*, std::set<std::string>>> &allLoops, 
                        std::vector<Messages> &currMessages);
void addReductionsToLoops(LoopGraph *currLoop, const std::vector<const depNode*> &reductionsToAdd, 
                          const std::map<int, std::pair<SgForStmt*, std::set<std::string>>> &allLoops, 
                          std::vector<Messages> &currMessages);
void fillVars(SgExpression *exp, const std::set<int> &types, std::set<SgSymbol*> &identifierList);

// remote_access.cpp
void addRemotesToDir(const std::pair<SgForStmt*, LoopGraph*> *under_dvm_dir, const std::map<std::string, SgArrayRefExp*> &uniqRemotes);
void createRemoteInParallel(const std::tuple<SgForStmt*, const LoopGraph*, const ParallelDirective*> &under_dvm_dir,
                            const DIST::Arrays<int> &allArrays,
                            const std::map<SgForStmt*, std::map<SgSymbol*, ArrayInfo>> &loopInfo,
                            const DIST::GraphCSR<int, double, attrType> &reducedG,
                            const DataDirective &data,
                            const std::vector<int> &currVar,
                            const std::map<int, std::pair<SgForStmt*, std::set<std::string>>> &allLoops,
                            std::map<std::string, SgArrayRefExp*> &uniqRemotes,
                            std::vector<Messages> &messages,
                            const int regionId,
                            const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);

template<int NUM> void createRemoteDir(SgStatement *st, const std::map<int, LoopGraph*> &sortedLoopGraph, const DIST::Arrays<int> &allArrays, 
                                       const DataDirective &data, const std::vector<int> &currVar, const int redionID, std::vector<Messages> &currMessages,
                                       const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);
