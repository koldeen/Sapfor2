#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "resolve_par_reg_conflicts.h"
#include "SgUtils.h"

#include "../GraphCall/graph_calls_func.h"

using std::map;
using std::pair;
using std::set;
using std::vector;
using std::string;
using std::make_pair;

static set<ParallelRegion*> getRegionByLine2(const vector<ParallelRegion*> &regions, const string &file, const int line)
{
    set<ParallelRegion*> regFound;

    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        regFound.insert(regions[0]);
    else if (regions.size() > 0)
    {
        for (int i = 0; i < regions.size(); ++i)
            if (regions[i]->HasThisLine(line, file))
                regFound.insert(regions[i]);
    }

    return regFound;
}

static bool recursiveFindCall(SgExpression *exp, const FuncInfo* func)
{
    if (exp)
    {
        if (exp->variant() == FUNC_CALL)
            if (func->funcName == exp->symbol()->identifier())
                return true;

        return recursiveFindCall(exp->rhs(), func) || recursiveFindCall(exp->lhs(), func);
    }

    return false;
}

static void findCall(const FuncInfo* funcFrom, const FuncInfo* funcTo, bool &callsFromRegion, bool &callsFromCode)
{
    if (switchToFile(funcTo->fileName) != -1)
    {
        bool isRegion = false;

        for (SgStatement *iterator = funcTo->funcPointer; iterator->lineNumber() != funcTo->linesNum.second; iterator = iterator->lexNext())
        {
            if (iterator->variant() == SPF_PARALLEL_REG_DIR)
                isRegion = true;

            if (iterator->variant() == SPF_END_PARALLEL_REG_DIR)
                isRegion = false;

            if (isSPF_stat(iterator) || isDVM_stat(iterator))
                continue;

            bool retVal = false;

            if (iterator->variant() == PROC_STAT)
                if (iterator->symbol()->identifier() == funcFrom->funcName)
                    retVal = true;

            for (int i = 0; i < 3; ++i)
                retVal = retVal || recursiveFindCall(iterator->expr(i), funcFrom);

            if (retVal)
            {
                if (isRegion)
                    callsFromRegion = true;
                else
                    callsFromCode = true;
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static FuncInfo* getFuncInfo(const map<string, FuncInfo*> &funcMap, const string &funcName)
{
    auto it = funcMap.find(funcName);
    if (it == funcMap.end())
        return NULL;

    return it->second;
}

static void fillRegionCover(FuncInfo* func, const map<string, FuncInfo*> &funcMap)
{
    if (func->funcPointer->variant() != ENTRY_STAT)
    {
        if (switchToFile(func->fileName) != -1)
        {
            SgStatement *iterator = func->funcPointer;
            FuncInfo *entry = NULL;
            bool isFuncCovered = true;
            bool isEntryCovered = true;
            bool isRegion = false;

            for (; !isSgExecutableStatement(iterator) && !isSPF_stat(iterator) && iterator->variant() != ENTRY_STAT; iterator = iterator->lexNext())
            {
                // skip not executable and not necessary statements
            }

            for (; iterator->lineNumber() < func->linesNum.second; iterator = iterator->lexNext())
            {
                switch (iterator->variant())
                {
                case SPF_PARALLEL_REG_DIR:
                    isRegion = true;
                    continue;
                case SPF_END_PARALLEL_REG_DIR:
                    isRegion = false;
                    continue;
                case ENTRY_STAT:
                    if (entry && isEntryCovered)
                        entry->setIsCoveredByRegion();

                    entry = getFuncInfo(funcMap, string(iterator->symbol()->identifier()));
                    isEntryCovered = true;
                    continue;
                default:
                    if (isSPF_stat(iterator) || isDVM_stat(iterator))
                        continue;

                    if (!isRegion)
                    {
                        isFuncCovered = false;
                        isEntryCovered = false;
                    }
                    break;
                }
            }

            if (isEntryCovered)
                entry->setIsCoveredByRegion();

            if (isFuncCovered)
                func->setIsCoveredByRegion();
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
}

static bool isInCommon(const map<string, CommonBlock> &commonBlocks, const string &arrayName)
{
    for (auto &commonBlockPair : commonBlocks)
        for (auto &variable : commonBlockPair.second.getVariables())
            if (variable.getName() == arrayName)
                return true;

    return false;
}

static bool isImplicit(const ParallelRegionLines &regionLines) { return regionLines.stats.first == NULL && regionLines.stats.second == NULL; }

static void recursiveFill(SgExpression *exp,
                          ParallelRegion *region,
                          const string &functionName,
                          const map<string, CommonBlock> &commonBlocks,
                          set<string> &allUsedCommonArrays)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            string arrayName = string(exp->symbol()->identifier());

            if (isInCommon(commonBlocks, arrayName))
            {
                region->AddCommonArray(arrayName);
                allUsedCommonArrays.insert(arrayName);
            }
            else
                region->AddLocalArray(functionName, arrayName);
        }

        recursiveFill(exp->rhs(), region, functionName, commonBlocks, allUsedCommonArrays);
        recursiveFill(exp->lhs(), region, functionName, commonBlocks, allUsedCommonArrays);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions, const map<string, CommonBlock> &commonBlocks, set<string> &allUsedCommonArrays)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    for (auto &region : regions)
    {
        map<string, set<string>> localArrayFound;
        set<string> commonArrayFound;

        for (auto &fileLines : region->GetAllLines())
        {
            // switch to current file
            if (switchToFile(fileLines.first) != -1)
            {
                for (auto &regionLines : fileLines.second)
                {
                    SgStatement *iterator = regionLines.stats.first;
                    SgStatement *end = regionLines.stats.second;
                    string functionName = "";

                    // implicit lines
                    if (isImplicit(regionLines))
                    {
                        iterator = getStatementByFileAndLine(fileLines.first, regionLines.lines.first);
                        end = getStatementByFileAndLine(fileLines.first, regionLines.lines.second);
                    }

                    while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
                        iterator = iterator->controlParent();

                    functionName = iterator->symbol()->identifier();

                    if (isImplicit(regionLines))
                        iterator = getStatementByFileAndLine(fileLines.first, regionLines.lines.first);
                    else
                        iterator = regionLines.stats.first;

                    for (; iterator && iterator != end; iterator = iterator->lexNext())
                    {
                        if (isSPF_stat(iterator) || isDVM_stat(iterator))
                            continue;

                        for (int i = 0; i < 3; ++i)
                            recursiveFill(iterator->expr(i), region, functionName, commonBlocks, allUsedCommonArrays);
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
}

void fillRegionFunctions(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> allFuncInfo, set<string> &allCommonFunctions)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    // funcName -> funcInfo
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (auto &region : regions)
    {
        for (auto &functionName : region->GetAllFuncCalls())
        {
            auto func = funcMap.find(functionName);
            if (func != funcMap.end())
            {
                auto callingRegions = getRegionByLine2(regions, func->second->fileName, func->second->linesNum.first);
                if (callingRegions.size() > 1)
                    region->AddCrossedFunc(functionName);
            }
        }
    }

    for (auto &funcPair : funcMap)
    {
        bool callsFromRegion = false;
        bool callsFromCode = false;

        fillRegionCover(funcPair.second, funcMap);
        //__spf_print(1, "  func '%s' at lines %d-%d is covered %d\n", funcPair.second->funcName.c_str(),
        //            funcPair.second->linesNum.first, funcPair.second->linesNum.second, funcPair.second->isCoveredByRegion); // remove

        for (auto &call : funcPair.second->callsTo)
            findCall(funcPair.second, call, callsFromRegion, callsFromCode);

        if (callsFromCode && callsFromRegion)
            allCommonFunctions.insert(funcPair.first);
    }
}

bool checkRegions(const vector<ParallelRegion*> &regions, map<string, vector<Messages>> &SPF_messages)
{
    bool noError = true;

    // check
    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLines())
        {
            for (auto &regionLine : fileLines.second)
            {
                if (!isImplicit(regionLine))
                {
                    for (auto &regionLine2 : fileLines.second)
                    {
                        if (isImplicit(regionLine2) && regionLine2.lines.first <= regionLine.lines.first && regionLine2.lines.second >= regionLine.lines.second)
                        {
                            __spf_print(1, "parallel region '%s' is included in file '%s' on line %d\n", region->GetName().c_str(),
                                        fileLines.first.c_str(), regionLine2.lines.first);
                            string message;
                            __spf_printToBuf(message, "parallel region '%s' is included in file '%s'", region->GetName().c_str(), fileLines.first.c_str());

                            auto itM = SPF_messages.find(fileLines.first);
                            if (itM == SPF_messages.end())
                                itM = SPF_messages.insert(itM, make_pair(fileLines.first, vector<Messages>()));

                            itM->second.push_back(Messages(ERROR, regionLine2.lines.first, message, 1033));

                            noError = false;
                        }
                    }
                }
            }
        }
    }

    return noError;
}

static void copyLocalArray(const string &arrayName, const map<string, FuncInfo*> &funcMap)
{
    
}

static void copyCommonArray(const string &arrayName, const map<string, FuncInfo*> &funcMap)
{
    
}

static void copyFunction(ParallelRegion *region,
                         const string &funcName,
                         const string &suffix,
                         const map<string, FuncInfo*> &funcMap)
{
    auto func = getFuncInfo(funcMap, funcName);
    if (func)
    {
        if (switchToFile(func->fileName) != -1)
        {
            SgSymbol *funcSymb = func->funcPointer->symbol();
            SgSymbol *newFuncSymb = NULL;
            string newFuncName = string(funcSymb->identifier()) + string("_") + suffix;

            __spf_print(1, "function name: '%s'\n", funcSymb->identifier()); // remove
            __spf_print(1, "  scope line: %d\n", funcSymb->scope()->lineNumber()); // remove
            __spf_print(1, "new function name '%s'\n", newFuncName.c_str()); // remove

            newFuncSymb = new SgSymbol(funcSymb->variant(), newFuncName.c_str(), funcSymb->type(), funcSymb->scope());
            *newFuncSymb = funcSymb->copySubprogram(*(func->funcPointer));

            region->AddReplacedSymbols(func->fileName, funcSymb, newFuncSymb);
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
}

void createFunctionsAndArrays(vector<ParallelRegion*> &regions,
                              const map<string, FuncInfo*> &funcMap,
                              const set<string> &allCommonFunctions,
                              const set<string> &allUsedCommonArrays)
{
    for (auto &region : regions)
    {
        // creating new functions
        if (region->GetCrossedFuncs().size())
            for (auto &crossedFunc : region->GetCrossedFuncs())
                copyFunction(region, crossedFunc, region->GetName(), funcMap);

        if (allCommonFunctions.size())
            for (auto &commonFunc : allCommonFunctions)
                copyFunction(region, commonFunc, string("copy"), funcMap);

        // creating new arrays
        for (auto &elem : region->GetLocalArrays())
            for (auto &localArray : elem.second)
                copyLocalArray(localArray, funcMap);
    }

    // creating common-blocks
    for (auto &commonArray : allUsedCommonArrays)
        copyCommonArray(commonArray, funcMap);
}

static void recursiveReplace(SgExpression *exp, const ParallelRegion *region, SgSymbol *from, SgSymbol *to)
{
    if (exp)
    {
        if (exp->symbol() && exp->symbol() == from)
            exp->setSymbol(to);

        recursiveReplace(exp->lhs(), region, from, to);
        recursiveReplace(exp->rhs(), region, from, to);
    }
}

void replaceFunctionsAndArrays(const vector<ParallelRegion*> &regions,
                               const map<string, FuncInfo*> &funcMap,
                               const set<string> &allCommonFunctions)
{
    for (auto &region : regions)
    {
        auto regionSymbols = region->GetReplacedSymbols();

        for (auto &fileLines : region->GetAllLines())
        {
            // switch to current file
            if (switchToFile(fileLines.first) != -1)
            {
                for (auto &regionLines : fileLines.second)
                {
                    SgStatement *iterator = regionLines.stats.first;
                    SgStatement *end = regionLines.stats.second;

                    // explicit lines
                    if (!isImplicit(regionLines))
                    {
                        for (; iterator && iterator != end; iterator = iterator->lexNext())
                        {
                            for (int i = 0; i < 3; ++i)
                            {
                                // recursiveReplace(iterator->expr(i), region);
                            }
                        }
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
}

void printCheckRegions(const vector<ParallelRegion*> &regions, set<string> &allUsedCommonArrays, const set<string> &allCommonFunctions)
{
    for (auto &region : regions)
    {
        string toPrint = "";
        for (auto &elem : region->GetLocalArrays())
        {
            toPrint += "function '" + elem.first + "': ";
            for (auto &arrayName : elem.second)
            {
                toPrint += arrayName + " ";
            }
        }

        if (toPrint != "")
            __spf_print(1, "[%s]: local arrays: %s\n", region->GetName().c_str(), toPrint.c_str());

        toPrint = "";
        for (auto &elem : region->GetCommonArrays())
        {
            toPrint += elem + " ";
        }

        if (toPrint != "")
            __spf_print(1, "[%s]: common arrays: %s\n", region->GetName().c_str(), toPrint.c_str());

        toPrint = "";
        for (auto &elem : region->GetCrossedFuncs())
            toPrint += elem + " ";

        if (toPrint != "")
            __spf_print(1, "[%s]: crossed functions: %s\n", region->GetName().c_str(), toPrint.c_str());
    }

    string toPrint = "";
    for (auto &elem : allUsedCommonArrays)
        toPrint += elem + " ";

    if (toPrint != "")
        __spf_print(1, "all common arrays: %s\n", toPrint.c_str());

    toPrint = "";
    for (auto &elem : allCommonFunctions)
        toPrint += elem + " ";

    if (toPrint != "")
        __spf_print(1, "all common functions: %s\n", toPrint.c_str());
}

int printCheckRegions(const char *fileName, const vector<ParallelRegion*> &regions, set<string> &allUsedCommonArrays, const set<string> &allCommonFunctions)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        __spf_print(1, "can not open file %s\n", fileName);
        return -1;
    }

    for (auto &region : regions)
    {
        fprintf(file, "*** REGION '%s'\n", region->GetName().c_str());
        fprintf(file, "  COMMON ARRAYS:");

        for (auto &elem : region->GetCommonArrays())
            fprintf(file, " %s", elem.c_str());

        fprintf(file, "\n");
        fprintf(file, "  LOCAL ARRAYS in [FUNC, ARRAY]:");

        for (auto &elem : region->GetLocalArrays())
            for (auto &arrayName : elem.second)
                fprintf(file, " [%s, %s]", elem.first.c_str(), arrayName.c_str());

        fprintf(file, "\n");
        fprintf(file, "  CROSSED FUNCTIONS:");

        for (auto &elem : region->GetCrossedFuncs())
            fprintf(file, " %s", elem.c_str());

        fprintf(file, "\n\n");
    }

    fprintf(file, "*** SUMMARY\n");
    fprintf(file, "  ALL GLOBAL ARRAYS:");

    for (auto &elem: allUsedCommonArrays)
        fprintf(file, " %s", elem.c_str());

    fprintf(file, "\n");
    fprintf(file, "  ALL COMMON FUNCTIONS:");

    for (auto &elem : allCommonFunctions)
        fprintf(file, " %s", elem.c_str());

    fprintf(file, "\n");

    fclose(file);
    return 0;
}
