#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "ParRegions_func.h"
#include "resolve_par_reg_conflicts.h"

#include "../Utils/SgUtils.h"

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
                          const string &fileName,
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
                region->AddCommonArray(arrayName, fileName, arraySymbol, NULL, lines);

                auto it = allCommonArrays.find(arrayName);
                if (it == allCommonArrays.end())
                {
                    vector<SgStatement*> declStatemets;
                    declaratedInStmt(arraySymbol, &declStatemets);
                    allCommonArrays.insert(it, std::make_pair(arrayName, ParallelRegionArray(arrayName, fileName, arraySymbol, NULL, lines, declStatemets)));
                }
            }
            else
            {
                region->AddUsedLocalArray(functionName, arrayName);

                //new type
                region->AddLocalArray(functionName, arrayName, fileName, arraySymbol, NULL, lines);
            }
        }

        recursiveFill(exp->rhs(), region, lines, functionName, fileName, commonBlocks, allUsedCommonArrays, allCommonArrays);
        recursiveFill(exp->lhs(), region, lines, functionName, fileName, commonBlocks, allUsedCommonArrays, allCommonArrays);
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
                            recursiveFill(iterator->expr(i), region, regionLines, functionName, fileLines.first, commonBlocks, allUsedCommonArrays, allCommonArrays);
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

static void copyLocalArray(ParallelRegion *region,
                           const ParallelRegionArray &array,
                           const string &funcName,
                           const string &arrayName,
                           const string &suffix,
                           const map<string, vector<FuncInfo*>> &allFuncInfo,
                           const map<string, FuncInfo*> &funcMap)
{
    auto func = getFuncInfo(funcMap, funcName);
    if (func)
    {
        if (SgFile::switchToFile(func->fileName) != -1)
        {
            string newArrName = arrayName + string("_") + suffix;
            SgSymbol *arrSymb = array.getOrigSymbol();
            SgSymbol *newArrSymb = NULL;
            SgStatement *decl = declaratedInStmt(arrSymb);
            SgStatement *newDecl = NULL;

            newArrSymb = &arrSymb->copy();
            newArrSymb->changeName(newArrName.c_str());
            newDecl = makeSymbolDeclaration(newArrSymb);
            //decl->insertStmtAfter(*decl, *newDecl);

            decl->unparsestdout();
            newDecl->unparsestdout();

            __spf_print(1, "new array '%s' for '%s' (line: %d)\n",
                newArrName.c_str(), arrSymb->identifier(), decl->lineNumber()); // remove

        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
}

static void copyCommonArray(ParallelRegion *region,
                            const ParallelRegionArray &array,
                            const string &funcName,
                            const string &arrayName,
                            const string &suffix,
                            const map<string, vector<FuncInfo*>> &allFuncInfo,
                            const map<string, FuncInfo*> &funcMap)
{

}

static void copyFunction(ParallelRegion *region,
                         const string &funcName,
                         const string &suffix,
                         const map<string, vector<FuncInfo*>> &allFuncInfo,
                         const map<string, FuncInfo*> &funcMap)
{
    auto func = getFuncInfo(funcMap, funcName);
    if (func)
    {
        if (SgFile::switchToFile(func->fileName) != -1)
        {
            // create copy function symbol and copy function for original function
            SgSymbol *funcSymb = func->funcPointer->GetOriginal()->symbol();
            SgSymbol *newFuncSymb = NULL;
            SgFile *file = func->funcPointer->GetOriginal()->getFile();
            string newFuncName = string(funcSymb->identifier()) + string("_") + suffix;

            newFuncSymb = &(funcSymb->copySubprogram(*(file->firstStatement())));
            newFuncSymb = &newFuncSymb->copy();
            newFuncSymb->changeName(newFuncName.c_str());
            file->firstStatement()->lexNext()->setSymbol(*newFuncSymb);

            __spf_print(1, "new function '%s' as copy of function '%s' (scope: %d) for file %s\n",
                        newFuncName.c_str(), funcSymb->identifier(), funcSymb->scope()->lineNumber(), func->fileName.c_str()); // remove

            // add copy function lines to explicit lines for next changes
            Statement *begin = new Statement(file->firstStatement()->lexNext());
            Statement *end = new Statement(file->firstStatement()->lexNext()->lastNodeOfStmt());
            pair<Statement*, Statement*> startEnd = make_pair(begin, end);
            pair<int, int> newLines = make_pair(startEnd.first->lineNumber(), startEnd.second->lineNumber());
            region->AddLines(newLines, file->filename(), &startEnd);

            __spf_print(1, "explicit lines %d-%d added with statement ids %d,%d\n",
                        newLines.first, newLines.second,
                        startEnd.first->id(), startEnd.second->id()); // remove

            region->AddReplacedSymbols(func->fileName, funcSymb, newFuncSymb);

            __spf_print(1, "  add (%s, %s) for file %s\n",
                        funcSymb->identifier(), newFuncSymb->identifier(), func->fileName.c_str()); // remove
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
}

void createFunctionsAndArrays(vector<ParallelRegion*> &regions,
                              const map<string, vector<FuncInfo*>> &allFuncInfo,
                              const set<string> &allCommonFunctions,
                              const set<string> &allUsedCommonArrays)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (auto &region : regions)
    {
        auto crossedFuncs = region->GetCrossedFuncs();
        auto allFuncs = region->GetAllFuncCalls();

        __spf_print(1, "[%s]: create functions\n", region->GetName().c_str()); // remove

        // creating new functions
        for (auto &crossedFunc : crossedFuncs)
            copyFunction(region, crossedFunc, region->GetName(), allFuncInfo, funcMap);

        for (auto &commonFunc : allCommonFunctions)
        {
            auto it = crossedFuncs.find(commonFunc);
            auto itt = region->GetAllFuncCalls().find(commonFunc);
            if (it == crossedFuncs.end() && itt != region->GetAllFuncCalls().end())
                copyFunction(region, commonFunc, region->GetName(), allFuncInfo, funcMap);
        }

        // forall funcs B, C: B is not crossed & C is crossed & B call C ==> B is explicit
        //                    B is not all-common
        for (auto &funcName : allFuncs)
        {
            auto func = getFuncInfo(funcMap, funcName);
            if (func)
            {
                auto it = crossedFuncs.find(funcName);
                auto itt = allCommonFunctions.find(funcName);
                if (it == crossedFuncs.end() && itt == allCommonFunctions.end())
                {
                    for (auto &crossedFunc : crossedFuncs)
                    {
                        auto it = func->callsFrom.find(crossedFunc);
                        if (it != func->callsFrom.end())
                        {
                            Statement *end = new Statement(func->funcPointer->GetOriginal()->lastNodeOfStmt());
                            pair<Statement*, Statement*> beginEnd = make_pair(func->funcPointer, end);
                            pair<int, int> funcLines = make_pair(beginEnd.first->GetOriginal()->lineNumber(), beginEnd.second->GetOriginal()->lineNumber());
                            region->AddLines(funcLines, func->fileName, &beginEnd);

                            __spf_print(1, "explicit lines %d-%d added with statement ids %d,%d\n",
                                        funcLines.first, funcLines.second,
                                        beginEnd.first->GetOriginal()->id(), beginEnd.second->GetOriginal()->id()); // remove
                        }
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }

        __spf_print(1, "[%s]: create local arrays\n", region->GetName().c_str()); // remove

        // creating new arrays
        for (auto &funcArrays : region->GetLocalArrays())
            for (auto &nameLocalArray : funcArrays.second)
                copyLocalArray(region, nameLocalArray.second, funcArrays.first, nameLocalArray.first, string("copy"), allFuncInfo, funcMap);

        //__spf_print(1, "[%s]: create common arrays\n", region->GetName().c_str()); // remove

        // creating common-blocks
        for (auto &commonArray : allUsedCommonArrays)
            ; // copyCommonArray(region, commonArray, string("copy"), allFuncInfo, funcMap);
    }
}

static void recursiveReplace(SgExpression *exp, const string &from, SgSymbol *to)
{
    if (exp)
    {
        // Alex, TODO: exp->symbol()->identifier()
        if (exp->symbol() && exp->symbol()->identifier() == from)
        {
            exp->setSymbol(to);

            __spf_print(1, "replace '%s' to '%s'\n", from.c_str(), to->identifier()); // remove
        }

        recursiveReplace(exp->lhs(), from, to);
        recursiveReplace(exp->rhs(), from, to);
    }
}

void replaceFunctionsAndArrays(const vector<ParallelRegion*> &regions,
                               const map<string, vector<FuncInfo*>> &allFuncInfo,
                               const set<string> &allCommonFunctions)
{
    for (auto &region : regions)
    {
        auto fileReplacingSymbols = region->GetReplacedSymbols();

        for (auto &fileLines : region->GetAllLines())
        {
            // switch to current file
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                auto it = fileReplacingSymbols.find(fileLines.first);
                if (it != fileReplacingSymbols.end())
                {
                    __spf_print(1, "[%s]: replace in file %s\n", region->GetName().c_str(), fileLines.first.c_str()); // remove

                    for (auto &regionLines : fileLines.second)
                    {
                        // explicit lines
                        if (!isImplicit(regionLines))
                        {
                            SgStatement *iterator = regionLines.stats.first->GetOriginal();
                            SgStatement *end = regionLines.stats.second->GetOriginal()->lexNext();

                            //__spf_print(1, "  explicit lines %d-%d with id %d,%d in fileid %d,%d \n",
                            //            iterator->lineNumber(), end->lineNumber() - 1, iterator->id(), end->id(),
                            //            iterator->getFileId(), end->getFileId()); // remove

                            for (; iterator != end; iterator = iterator->lexNext())
                            {
                                for (auto &fromTo : it->second)
                                {
                                    if (iterator->symbol() && iterator->symbol()->identifier() == string(fromTo.first->identifier()))
                                    {
                                        iterator->setSymbol(*fromTo.second);

                                        __spf_print(1, "replace '%s' to '%s' in file %s on line %d\n",
                                                    fromTo.first->identifier(), fromTo.second->identifier(),
                                                    fileLines.first.c_str(), iterator->lineNumber()); // remove
                                    }

                                    for (int i = 0; i < 3; ++i)
                                        recursiveReplace(iterator->expr(i), fromTo.first->identifier(), fromTo.second);
                                }

                                //__spf_print(1, "CURRENT LINE IS %d WITH ID %d IN FILEID %d, END IS ON LINES %d WITH ID %d IN FILEID %d\n",
                                //            iterator->lineNumber(), iterator->id(), iterator->getFileId(), end->lineNumber(),
                                //            end->id(), end->getFileId()); // remove
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

void insertArraysCopy(const vector<ParallelRegion*> &regions,
                      const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

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
                                    SgExpression *left = new SgArrayRefExp(*originCopy.second);
                                    SgExpression *right = new SgArrayRefExp(*originCopy.first);
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

void printCheckRegions(const vector<ParallelRegion*> &regions, const set<string> &allUsedCommonArrays, const set<string> &allCommonFunctions, const map<string, ParallelRegionArray> &allCommonArrays)
{
    for (auto &region : regions)
    {
        string toPrint = "";
        for (auto &elem : region->GetUsedLocalArrays())
        {
            toPrint += "\n  function '" + elem.first + "': ";
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

    for (auto &region : regions)
    {
        string toPrint = "";
        for (auto &funcArrays : region->GetLocalArrays())
        {
            toPrint += "\n  function '" + funcArrays.first + "':";
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
            __spf_print(1, "[NEW TYPES][%s]: local arrays: %s\n", region->GetName().c_str(), toPrint.c_str());

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
        fprintf(file, "  LOCAL ARRAYS in [FUNC, ARRAY]:\n");

        for (auto &elem : region->GetUsedLocalArrays())
            for (auto &arrayName : elem.second)
                fprintf(file, "    [%s, %s]\n", elem.first.c_str(), arrayName.c_str());

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
