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
using std::to_string;
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

static void recursiveFill(SgExpression *exp,
                          ParallelRegion *region,
                          const ParallelRegionLines &lines,
                          const string &functionName,
                          const string &fileName,
                          const map<string, CommonBlock> &commonBlocks,
                          set<DIST::Array*> &allUsedCommonArrays,
                          map<string, ParallelRegionArray> &allCommonArrays)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            SgSymbol *arraySymbol = exp->symbol();
            string arrayName = string(arraySymbol->identifier());
            DIST::Array *array = getArrayFromDeclarated(arraySymbol->declaredInStmt(), arrayName);

            if (isInCommon(commonBlocks, arrayName))
            {
                region->AddUsedCommonArray(array);
                allUsedCommonArrays.insert(array);

                //new type
                region->AddCommonArray(arrayName, fileName, arraySymbol, NULL, lines);

                auto it = allCommonArrays.find(arrayName);
                if (it == allCommonArrays.end())
                {
                    vector<SgStatement*> declStatemets;
                    declaratedInStmt(arraySymbol, &declStatemets);
                    allCommonArrays.insert(it, make_pair(arrayName, ParallelRegionArray(arrayName, fileName, arraySymbol, NULL, lines, declStatemets)));
                }
            }
            else
            {
                region->AddUsedLocalArray(array);

                //new type
                region->AddLocalArray(functionName, arrayName, fileName, arraySymbol, NULL, lines);
            }
        }

        recursiveFill(exp->rhs(), region, lines, functionName, fileName, commonBlocks, allUsedCommonArrays, allCommonArrays);
        recursiveFill(exp->lhs(), region, lines, functionName, fileName, commonBlocks, allUsedCommonArrays, allCommonArrays);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions, const map<string, CommonBlock> &commonBlocks, set<DIST::Array*> &allUsedCommonArrays, map<string, ParallelRegionArray> &allCommonArrays)
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
                    if (regionLines.isImplicit())
                    {
                        iterator = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.first);
                        end = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.second);
                    }

                    while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
                        iterator = iterator->controlParent();

                    functionName = iterator->symbol()->identifier();

                    if (regionLines.isImplicit())
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

void fillRegionFunctions(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> &allFuncInfo, set<FuncInfo*> &allCommonFunctions)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    for (auto &region : regions)
    {
        for (auto &func : region->GetAllFuncCalls())
        {
            auto callingRegions = getAllRegionsByLine(regions, func->fileName, func->linesNum.first);
            if (callingRegions.size() > 1)
                region->AddCrossedFunc(func);
        }
    }

    // funcName -> funcInfo
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

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
            allCommonFunctions.insert(funcPair.second);
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
                if (!regionLine.isImplicit())
                {
                    for (auto &regionLine2 : fileLines.second)
                    {
                        if (regionLine2.isImplicit() && regionLine2.lines.first <= regionLine.lines.first && regionLine2.lines.second >= regionLine.lines.second)
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
            newDecl = newArrSymb->makeVarDeclStmt();
            decl->insertStmtAfter(*newDecl, *decl->controlParent());

            decl->unparsestdout();
            newDecl->unparsestdout();
            newDecl->lexPrev()->unparsestdout();
            decl->lexNext()->unparsestdout();
            decl->lexNext()->lexNext()->unparsestdout();

            __spf_print(1, "  array '%s' variant is %d\n", arrSymb->identifier(), arrSymb->variant()); // remove
            __spf_print(1, "  array '%s' variant is %d\n", newArrSymb->identifier(), newArrSymb->variant()); // remove

            __spf_print(1, "new array '%s' as copy of array '%s' (line: %d)\n",
                        newArrName.c_str(), arrSymb->identifier(), decl->lineNumber()); // remove

            region->AddReplacedSymbols(func->fileName, arrSymb, newArrSymb);

            __spf_print(1, "  add (%s, %s) for file %s\n",
                        arrSymb->identifier(), newArrSymb->identifier(), func->fileName.c_str()); // remove

            // TODO: SPF_ANALYSIS(decl)
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

static void copyFunction(ParallelRegion *region, const FuncInfo *func, const string &suffix)
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

        __spf_print(1, "  explicit lines %d-%d added with statement ids %d,%d\n",
                    newLines.first, newLines.second,
                    startEnd.first->id(), startEnd.second->id()); // remove

        // TODO: change replace algorithm for array raplacing
        region->AddReplacedSymbols(func->fileName, funcSymb, newFuncSymb);

        __spf_print(1, "  add (%s, %s) for file %s\n",
                    funcSymb->identifier(), newFuncSymb->identifier(), func->fileName.c_str()); // remove
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

void createFunctionsAndArrays(vector<ParallelRegion*> &regions,
                              const map<string, vector<FuncInfo*>> &allFuncInfo,
                              const set<FuncInfo*> &allCommonFunctions,
                              const set<DIST::Array*> &allUsedCommonArrays)
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
            copyFunction(region, crossedFunc, region->GetName());

        for (auto &commonFunc : allCommonFunctions)
        {
            auto it = crossedFuncs.find(commonFunc);
            auto itt = region->GetAllFuncCalls().find(commonFunc);
            if (it == crossedFuncs.end() && itt != region->GetAllFuncCalls().end())
                copyFunction(region, commonFunc, region->GetName());
        }

        // forall funcs B, C: B is not crossed & C is crossed & B call C ==> B is explicit
        //                    B is not all-common
        for (auto &func : allFuncs)
        {
            auto it = crossedFuncs.find(func);
            auto itt = allCommonFunctions.find(func);
            if (it == crossedFuncs.end() && itt == allCommonFunctions.end())
            {
                for (auto &crossedFunc : crossedFuncs)
                {
                    auto it = func->callsFrom.find(crossedFunc->funcName);
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

        __spf_print(1, "[%s]: create local arrays\n", region->GetName().c_str()); // remove

        // creating new arrays
        for (auto &funcArrays : region->GetLocalArrays())
            for (auto &nameLocalArray : funcArrays.second)
                copyLocalArray(region, nameLocalArray.second, funcArrays.first, nameLocalArray.first, region->GetName(), allFuncInfo, funcMap);
    }

    __spf_print(1, "create common arrays\n"); // remove

    // creating common-block
    // TODO: create new common-block
    SgStatement *commDecl = new SgStatement(COMM_STAT);
    SgExprListExp *commList = new SgExprListExp(COMM_LIST);
    commDecl->setExpression(0, *commList);

    // TODO: create new arrays into new common-block
    for (auto &commonArray : allUsedCommonArrays)
    {
        ;
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
            __spf_print(1, "  replace '%s' to '%s'\n", from.c_str(), to->identifier()); // remove
        }

        recursiveReplace(exp->lhs(), from, to);
        recursiveReplace(exp->rhs(), from, to);
    }
}

void replaceFunctionsAndArrays(const vector<ParallelRegion*> &regions,
                               const map<string, vector<FuncInfo*>> &allFuncInfo,
                               const set<FuncInfo*> &allCommonFunctions)
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
                        if (!regionLines.isImplicit())
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

                                        __spf_print(1, "  replace '%s' to '%s' in file %s on line %d\n",
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

void insertArraysCopying(const vector<ParallelRegion*> &regions,
                         const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (auto &region : regions)
    {
        for (auto &funcArrays : region->GetLocalArrays())
        {
            string funcName = funcArrays.first;
            auto func = getFuncInfo(funcMap, funcName);

            if (SgFile::switchToFile(func->fileName) != -1)
            {
                for (auto &arrayName : funcArrays.second)
                {
                    for (auto &funcSymbols : region->GetReplacedSymbols())
                    {
                        if (funcSymbols.first == func->fileName)
                        {
                            for (auto &originCopy : funcSymbols.second)
                            {
                                if (originCopy.first->identifier() == arrayName.first)
                                {
                                    // insert copy statement
                                    for (auto &regionLines : arrayName.second.getAllLines())
                                    {
                                        if (!regionLines.isImplicit())
                                        {
                                            // A_reg = A
                                            // TODO: use SgAssignStmt
                                            SgStatement *assign = new SgStatement(ASSIGN_STAT);
                                            SgExpression *left = new SgArrayRefExp(*originCopy.second);
                                            SgExpression *right = new SgArrayRefExp(*originCopy.first);

                                            assign->setExpression(0, *left);
                                            assign->setExpression(1, *right);
                                            regionLines.stats.first->insertStmtBefore(*assign, *regionLines.stats.first->controlParent());

                                            __spf_print(1, "insert '%s = %s'\n", originCopy.second->identifier(), originCopy.first->identifier()); // remove

                                            // A = A_reg
                                            assign = new SgStatement(ASSIGN_STAT);
                                            left = new SgArrayRefExp(*originCopy.first);
                                            right = new SgArrayRefExp(*originCopy.second);
                                            assign->setExpression(0, *left);
                                            assign->setExpression(1, *right);
                                            regionLines.stats.second->insertStmtAfter(*assign, *regionLines.stats.second->lexNext()->controlParent());

                                            __spf_print(1, "insert '%s = %s'\n", originCopy.first->identifier(), originCopy.second->identifier()); // remove
                                        }
                                    }

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

int printCheckRegions(const char *fileName, const vector<ParallelRegion*> &regions, const set<DIST::Array*> &allUsedCommonArrays, const set<FuncInfo*> &allCommonFunctions, const map<string, ParallelRegionArray> &allCommonArrays)
{
    string outText = "";    
    for (auto &region : regions)
    {   
        outText += "*** REGION '" + region->GetName() + "'\n";
        outText += "  COMMON ARRAYS:";
        
        for (auto &array : region->GetUsedCommonArrays())
            outText += " " + array->GetShortName();

        outText += "\n";
        outText += "  LOCAL ARRAYS in [FUNC, ARRAY]:\n";
        
        for (auto &array : region->GetUsedLocalArrays())
            outText += "    [" + string(array->GetDeclSymbol()->GetOriginal()->declaredInStmt()->controlParent()->symbol()->identifier()) + ", " + array->GetShortName() + "]\n";

        outText += "  CROSSED FUNCTIONS:";
        
        for (auto &func : region->GetCrossedFuncs())
            outText += " " + func->funcName;

        outText += "\n\n";
    }

    outText += "*** SUMMARY\n";
    outText += "  ALL GLOBAL ARRAYS:";

    for (auto &array : allUsedCommonArrays)
        outText += " " + array->GetShortName();

    outText += "\n";
    outText += "  ALL COMMON FUNCTIONS:";

    for (auto &func : allCommonFunctions)
        outText += " " + func->funcName;
    outText += "\n";

    // -------------------------------------
    outText += "\nNEW TYPES:\n";

    for (auto &region : regions)
    {
        outText += "*** REGION '" + region->GetName() + "'\n";
        outText += "  COMMON ARRAYS:";

        for (auto &elem : region->GetCommonArrays())
            outText += " " + elem.first;

        outText += "\n";
        outText += "  LOCAL ARRAYS in [FUNC, ARRAY, [LINES]]:\n";
        
        for (auto &funcArrays : region->GetLocalArrays())
        {
            for (auto &nameArray : funcArrays.second)
            {
                string toPrint = "";
                for (auto &lines : nameArray.second.getAllLines())
                {
                    toPrint += "[" + to_string(lines.lines.first);
                    toPrint += "-" + to_string(lines.lines.second);
                    toPrint += "]";
                }

                outText += "    [" + funcArrays.first + ", " + nameArray.first + ", " + toPrint + "]\n";                
            }
        }
        outText += "  CROSSED FUNCTIONS:";

        for (auto &func : region->GetCrossedFuncs())
            outText += " " + func->funcName;

        outText += "\n\n";
    }

    outText += "*** SUMMARY\n";
    outText += "  ALL GLOBAL ARRAYS:";

    for (auto &elem : allCommonArrays)
        outText += " " + elem.first;

    outText += "\n";
    outText += "  ALL COMMON FUNCTIONS:";

    for (auto &func : allCommonFunctions)
        outText += " " + func->funcName;

    outText += "\n";
           
    if (fileName == NULL)
        __spf_print(1, "%s", outText.c_str());    
    else
    {
        FILE *file = fopen(fileName, "w");
        if (file == NULL)
        {
            __spf_print(1, "can not open file '%s'\n", fileName);
            return -1;
        }
        fprintf(file, "%s", outText.c_str());
        fclose(file);
    }
    return 0;
}
