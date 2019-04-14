#pragma once

#include <vector>
#include <string>
#include <map>
#include "dvm.h"
#include "../Utils/errors.h"

#include "../ParallelizationRegions/ParRegions.h"
#include "../ParallelizationRegions/ParRegions_func.h"
#include "../Utils/CommonBlock.h"

bool EquivalenceChecker(SgFile *file, const std::string &fileName, const std::vector<ParallelRegion*> &regions, std::map<std::string, std::vector<Messages>> &currM);
bool CommonBlockChecker(SgFile *file, const std::string &fileName, const std::map<std::string, CommonBlock> &commonBlocks, std::vector<Messages> &currMessages);
bool EndDoLoopChecker(SgFile *file, std::vector<Messages> &currM);
bool IncludeChecker(SgFile *file, const std::string &fileName, std::vector<Messages> &currM);
void VarDeclCorrecter(SgFile *file);
bool DvmDirectiveChecker(SgFile *file, std::map<std::string, std::vector<int>> &errors, const int, const int);
bool FunctionsChecker(SgFile *file, std::map<std::string, std::pair<std::string, int>> &funcNames, std::map<std::string, std::vector<Messages>> &currMessages);
int VerifyFile(SgFile *file);
void fixUseOnlyStmt(SgFile *file, const std::vector<ParallelRegion*> &regs);
void correctModuleProcNames(SgFile *file);
void restoreCorrectedModuleProcNames(SgFile *file);
bool checkArgumentsDeclaration(SgProject *project, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo, const std::vector<ParallelRegion*> &regions, std::map<std::string, std::vector<Messages>> &SPF_messages);