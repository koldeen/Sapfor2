#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "ParRegions_func.h"
#include "resolve_par_reg_conflicts.h"

#include "SgUtils.h"

#include "../GraphCall/graph_calls_func.h"

using std::map;
using std::pair;
using std::set;
using std::vector;
using std::string;
using std::make_pair;

static bool recursiveFindCall(SgExpression *exp, const string &funcName)
{
    if (exp)
    {
        if (exp->variant() == FUNC_CALL)
            if (funcName == exp->symbol()->identifier())
                return true;

        return recursiveFindCall(exp->rhs(), funcName) || recursiveFindCall(exp->lhs(), funcName);
    }

    return false;
}

static void findCall(const FuncInfo *funcFrom, const FuncInfo *funcTo, bool &callsFromRegion, bool &callsFromCode)
{
    if (SgFile::switchToFile(funcTo->fileName) != -1)
    {
        bool isRegion = false;
        SgStatement *iterator = funcTo->funcPointer->GetOriginal();
        SgStatement *end = SgStatement::getStatementByFileAndLine(funcTo->fileName, funcTo->linesNum.second);

        for (; iterator != end; iterator = iterator->lexNext())
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
                retVal = retVal || recursiveFindCall(iterator->expr(i), funcFrom->funcName);

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

static void fillRegionCover(FuncInfo *func, const map<string, FuncInfo*> &funcMap)
{
    if (func->funcPointer->variant() != ENTRY_STAT)
    {
        if (SgFile::switchToFile(func->fileName) != -1)
        {
            SgStatement *iterator = func->funcPointer;
            FuncInfo *entry = NULL;
            bool isFuncCovered = true;
            bool isEntryCovered = true;
            bool isRegion = false;

            // ALEX, TODO: а DVM директивы €вл€еютс€ нужными?
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
                    break;
                case SPF_END_PARALLEL_REG_DIR:
                    isRegion = false;
                    break;
                case ENTRY_STAT:
                    if (entry && isEntryCovered)
                        entry->setIsCoveredByRegion();

                    entry = getFuncInfo(funcMap, string(iterator->symbol()->identifier()));
                    isEntryCovered = true;
                    break;
                default:
                    if (isSPF_stat(iterator) || isDVM_stat(iterator))
                        break;

                    if (!isRegion)
                    {
                        isFuncCovered = false;
                        isEntryCovered = false;
                    }
                    break;
                }
            }

            // ALEX, TODO: а проверка на entry?
            // SERG, TODO: а нужно? флаг isEntryCovered выставл€етс€ в true, только если встретилс€ entry
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

static bool isImplicit(const ParallelRegionLines &regionLines)
{
    return regionLines.stats.first == NULL && regionLines.stats.second == NULL;
}

static void recursiveFill(SgExpression *exp,
                          ParallelRegion *region,
                          const ParallelRegionLines &lines,
                          const string &functionName,
                          const map<string, CommonBlock> &commonBlocks,
                          set<string> &allUsedCommonArrays,
                          map<string, ParallelRegionArray> &allCommonArrays)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            SgSymbol *arraySymbol = exp->symbol();
            string arrayName = string(arraySymbol->identifier());

            if (isInCommon(commonBlocks, arrayName))
            {
                region->AddUsedCommonArray(arrayName);
                allUsedCommonArrays.insert(arrayName);

                //new type
                region->AddCommonArray(arrayName, arraySymbol, NULL, lines);

                auto it = allCommonArrays.find(arrayName);
                if (it == allCommonArrays.end())
                {
                    vector<SgStatement*> declStatemets;
                    declaratedInStmt(arraySymbol, &declStatemets);
                    allCommonArrays.insert(it, std::make_pair(arrayName, ParallelRegionArray(arrayName, arraySymbol, NULL, declStatemets, lines)));
                }
            }
            else
            {
                region->AddUsedLocalArray(functionName, arrayName);

                //new type
                region->AddLocalArray(functionName, arrayName, arraySymbol, NULL, lines);
            }
        }

        recursiveFill(exp->rhs(), region, lines, functionName, commonBlocks, allUsedCommonArrays, allCommonArrays);
        recursiveFill(exp->lhs(), region, lines, functionName, commonBlocks, allUsedCommonArrays, allCommonArrays);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions, const map<string, CommonBlock> &commonBlocks, set<string> &allUsedCommonArrays, map<string, ParallelRegionArray> &allCommonArrays)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLines())
        {
            // switch to current file
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                for (auto &regionLines : fileLines.second)
                {
                    SgStatement *iterator = regionLines.stats.first;
                    SgStatement *end = regionLines.stats.second;
                    string functionName = "";

                    // implicit lines
                    if (isImplicit(regionLines))
                    {
                        iterator = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.first);
                        end = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.second);
                    }

                    while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
                        iterator = iterator->controlParent();

                    functionName = iterator->symbol()->identifier();

                    if (isImplicit(regionLines))
                        iterator = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.first);
                    else
                        iterator = regionLines.stats.first;

                    for (; iterator && iterator != end; iterator = iterator->lexNext())
                    {
                        if (isSPF_stat(iterator) || isDVM_stat(iterator))
                            continue;

                        for (int i = 0; i < 3; ++i)
                            recursiveFill(iterator->expr(i), region, regionLines, functionName, commonBlocks, allUsedCommonArrays, allCommonArrays);
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
}

void fillRegionFunctions(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> &allFuncInfo, set<string> &allCommonFunctions)
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
                auto callingRegions = getAllRegionsByLine(regions, func->second->fileName, func->second->linesNum.first);
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

    // check if region includes itself
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

static void copyLocalArray(ParallelRegion *region, const string &arrayName, const string &suffix)
{

}

static void copyCommonArray(ParallelRegion *region, const string &arrayName, const string &suffix)
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
        if (SgFile::switchToFile(func->fileName) != -1)
        {
            SgSymbol *funcSymb = func->funcPointer->symbol();
            SgSymbol *newFuncSymb = NULL;
            string newFuncName = string(funcSymb->identifier()) + string("_") + suffix;

            __spf_print(1, "function name: '%s'\n", funcSymb->identifier()); // remove
            __spf_print(1, "  scope line: %d\n", funcSymb->scope()->lineNumber()); // remove
            __spf_print(1, "new function name '%s'\n", newFuncName.c_str()); // remove

            //SgFile *file = &CurrentProject->file(func->funcPointer->getFileId());
            SgFile *file = &CurrentProject->file(func->funcPointer->GetOriginal()->getFileId());
            //SgFile *file2 = &func->funcPointer->getProject()->file(func->funcPointer->getFileId());
            SgFile *file2 = &func->funcPointer->getProject()->file(func->funcPointer->GetOriginal()->getFileId());

            //newFuncSymb = &(funcSymb->copySubprogram(*(file->firstStatement())));
            newFuncSymb = &(funcSymb->copySubprogram(*(file2->firstStatement())));
            //newFuncSymb = &(funcSymb->copySubprogram(*(func->funcPointer)));

            // TODO: set new name

            region->AddReplacedSymbols(func->funcName, funcSymb, newFuncSymb);
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
        for (auto &elem : region->GetUsedLocalArrays())
            for (auto &localArray : elem.second)
                copyLocalArray(region, localArray, string("copy"));

        // creating common-blocks
        for (auto &commonArray : allUsedCommonArrays)
            copyCommonArray(region, commonArray, string("copy"));
    }
}

static void recursiveReplace(SgExpression *exp, SgSymbol *from, SgSymbol *to)
{
    if (exp)
    {
        if (exp->symbol() && exp->symbol() == from)
            exp->setSymbol(to);

        recursiveReplace(exp->lhs(), from, to);
        recursiveReplace(exp->rhs(), from, to);
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
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                auto it = regionSymbols.find(fileLines.first);
                if (it != regionSymbols.end())
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
                                for (auto fromTo : it->second)
                                {
                                    if (iterator->symbol() && iterator->symbol() == fromTo.first)
                                        iterator->setSymbol(*fromTo.second);

                                    for (int i = 0; i < 3; ++i)
                                        recursiveReplace(iterator->expr(i), fromTo.first, fromTo.second);
                                }
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

void insertArraysCopy(const vector<ParallelRegion*> &regions, const map<string, FuncInfo*> &funcMap)
{
    for (auto &region : regions)
    {
        for (auto &funcArrays : region->GetUsedLocalArrays())
        {
            string funcName = funcArrays.first;
            auto func = getFuncInfo(funcMap, funcName);

            if (SgFile::switchToFile(func->fileName) != -1)
            {
                for (auto &arrayName : funcArrays.second)
                {
                    for (auto &funcSymbols : region->GetReplacedSymbols())
                    {
                        if (funcSymbols.first == funcName)
                        {
                            for (auto &originCopy : funcSymbols.second)
                            {
                                if (originCopy.first->identifier() == arrayName)
                                {
                                    SgStatement *assign = new SgStatement(ASSIGN_STAT);
                                    SgExpression *left = new SgExpression(originCopy.second->variant(), NULL, NULL, originCopy.second, originCopy.second->type());
                                    SgExpression *right = new SgExpression(originCopy.first->variant(), NULL, NULL, originCopy.first, originCopy.first->type());
                                    assign->setExpression(0, *left);
                                    assign->setExpression(1, *right);

                                    // TODO: insert copy statement

                                    break;
                                }
                            }

                            break;
                        }
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
}

void temp(SgFile *file)
{
    SgStatement *iterator = file->firstStatement();
    SgStatement *end = iterator->lexNext()->lastNodeOfStmt();
    __spf_print(1, "LINES %d-%d\n", iterator->lineNumber(), end->lineNumber());
    for (; iterator->lineNumber() <= end->lineNumber(); iterator = iterator->lexNext()) {
        __spf_print(1, "LINE %d\n", iterator->lineNumber());
        //iterator->unparsestdout();
        if (iterator->lineNumber() == 16) {
            __spf_print(1, "VARIANT %d\n", iterator->variant());
            iterator->unparsestdout();
            recExpressionPrint(iterator->expr(0));
            recExpressionPrint(iterator->expr(1));
            break;
        }
    }
}

void printCheckRegions(const vector<ParallelRegion*> &regions, const set<string> &allUsedCommonArrays, const set<string> &allCommonFunctions, const map<string, ParallelRegionArray> &allCommonArrays)
{
    for (auto &region : regions)
    {
        string toPrint = "";
        for (auto &elem : region->GetUsedLocalArrays())
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
        for (auto &elem : region->GetUsedCommonArrays())
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

    // -------------------------------------
    __spf_print(1, "NEW TYPES:\n");

    for (auto &region : regions)
    {
        string toPrint = "";
        for (auto &funcArrays : region->GetLocalArrays())
        {
            toPrint += "function '" + funcArrays.first + "':";
            for (auto &nameArray : funcArrays.second)
            {
                toPrint += " " + nameArray.first;
                toPrint += " ";
                for (auto &lines : nameArray.second.getAllLines())
                {
                    toPrint += "[" + std::to_string(lines.lines.first);
                    toPrint += "-" + std::to_string(lines.lines.second);
                    toPrint += "]";
                }
            }
        }

        if (toPrint != "")
            __spf_print(1, "[%s]: local arrays: %s\n", region->GetName().c_str(), toPrint.c_str());

        toPrint = "";
        for (auto &elem : region->GetCommonArrays())
        {
            toPrint += elem.first + " ";
        }

        if (toPrint != "")
            __spf_print(1, "[%s]: common arrays: %s\n", region->GetName().c_str(), toPrint.c_str());

        toPrint = "";
        for (auto &elem : region->GetCrossedFuncs())
            toPrint += elem + " ";

        if (toPrint != "")
            __spf_print(1, "[%s]: crossed functions: %s\n", region->GetName().c_str(), toPrint.c_str());
    }
}

int printCheckRegions(const char *fileName, const vector<ParallelRegion*> &regions, const set<string> &allUsedCommonArrays, const set<string> &allCommonFunctions, const map<string, ParallelRegionArray> &allCommonArrays)
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

        for (auto &elem : region->GetUsedCommonArrays())
            fprintf(file, " %s", elem.c_str());

        fprintf(file, "\n");
        fprintf(file, "  LOCAL ARRAYS in [FUNC, ARRAY]:");

        for (auto &elem : region->GetUsedLocalArrays())
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

    // -------------------------------------
    fprintf(file, "\nNEW TYPES:\n");

    for (auto &region : regions)
    {
        fprintf(file, "*** REGION '%s'\n", region->GetName().c_str());
        fprintf(file, "  COMMON ARRAYS:");

        for (auto &elem : region->GetCommonArrays())
            fprintf(file, " %s", elem.first.c_str());

        fprintf(file, "\n");
        fprintf(file, "  LOCAL ARRAYS in [FUNC, ARRAY, [LINES]]:\n");

        for (auto &funcArrays : region->GetLocalArrays())
        {
            for (auto &nameArray : funcArrays.second)
            {
                string toPrint = "";
                for (auto &lines : nameArray.second.getAllLines())
                {
                    toPrint += "[" + std::to_string(lines.lines.first);
                    toPrint += "-" + std::to_string(lines.lines.second);
                    toPrint += "]";
                }

                fprintf(file, "    [%s, %s, %s]\n", funcArrays.first.c_str(), nameArray.first.c_str(), toPrint.c_str());
            }
        }

        fprintf(file, "  CROSSED FUNCTIONS:");

        for (auto &elem : region->GetCrossedFuncs())
            fprintf(file, " %s", elem.c_str());

        fprintf(file, "\n\n");
    }

    fprintf(file, "*** SUMMARY\n");
    fprintf(file, "  ALL GLOBAL ARRAYS:");

    for (auto &elem : allCommonArrays)
        fprintf(file, " %s", elem.first.c_str());

    fprintf(file, "\n");
    fprintf(file, "  ALL COMMON FUNCTIONS:");

    for (auto &elem : allCommonFunctions)
        fprintf(file, " %s", elem.c_str());

    fprintf(file, "\n");

    fclose(file);
    return 0;
}
