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
                          const string &fileName,
                          const string &funcName,
                          const ParallelRegionLines &lines,
                          const map<string, FuncInfo*> &funcMap,
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
            FuncInfo *func = getFuncInfo(funcMap, funcName);

            if (isInCommon(commonBlocks, arrayName))
            {
                region->AddUsedCommonArray(func, array, lines);
                allUsedCommonArrays.insert(array);

                // new types
                auto it = allCommonArrays.find(arrayName);
                if (it == allCommonArrays.end())
                {
                    vector<SgStatement*> declStatemets;
                    declaratedInStmt(arraySymbol, &declStatemets);
                    allCommonArrays.insert(it, make_pair(arrayName, ParallelRegionArray(arrayName, fileName, arraySymbol, NULL, lines, declStatemets)));
                }
            }
            else if (!lines.isImplicit())
                region->AddUsedLocalArray(func, array, lines);
        }

        recursiveFill(exp->rhs(), region, fileName, funcName, lines, funcMap, commonBlocks, allUsedCommonArrays, allCommonArrays);
        recursiveFill(exp->lhs(), region, fileName, funcName, lines, funcMap, commonBlocks, allUsedCommonArrays, allCommonArrays);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions,
                      const map<string, vector<FuncInfo*>> &allFuncInfo,
                      const map<string, CommonBlock> &commonBlocks,
                      set<DIST::Array*> &allUsedCommonArrays,
                      map<string, ParallelRegionArray> &allCommonArrays)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);
    
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
                            recursiveFill(iterator->expr(i), region, fileLines.first, functionName, regionLines, funcMap, commonBlocks, allUsedCommonArrays, allCommonArrays);
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

static void recursiveReplace(SgExpression *exp, const string &from, SgSymbol *to)
{
    if (exp)
    {
        // Alex, TODO: exp->symbol()->identifier()
        if (exp->symbol() && exp->symbol()->identifier() == from)
        {
            exp->setSymbol(to);
            __spf_print(1, "  replace symbol '%s' to '%s'\n", from.c_str(), to->identifier()); // remove
        }

        recursiveReplace(exp->lhs(), from, to);
        recursiveReplace(exp->rhs(), from, to);
    }
}

static void replaceSymbol(const string &fileName, const vector<ParallelRegionLines> &lines, SgSymbol *origSymb, SgSymbol *newSymb)
{
    if (SgFile::switchToFile(fileName) != -1)
    {
        for (auto &regionLines : lines)
        {
            // explicit lines
            if (!regionLines.isImplicit())
            {
                SgStatement *iterator = regionLines.stats.first->GetOriginal();
                SgStatement *end = regionLines.stats.second->GetOriginal()->lexNext();

                for (; iterator != end; iterator = iterator->lexNext())
                {
                    if (iterator->symbol() && iterator->symbol()->identifier() == string(origSymb->identifier()))
                    {
                        iterator->setSymbol(*newSymb);

                        __spf_print(1, "  replace symbol '%s' to '%s' in file %s on line %d\n",
                                    origSymb->identifier(),
                                    newSymb->identifier(),
                                    fileName.c_str(),
                                    iterator->lineNumber()); // remove
                    }

                    for (int i = 0; i < 3; ++i)
                        recursiveReplace(iterator->expr(i), origSymb->identifier(), newSymb);
                }
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void insertArrayCopying(const string &fileName, const vector<ParallelRegionLines> &lines, SgSymbol *origSymb, SgSymbol *newSymb)
{
    if (SgFile::switchToFile(fileName) != -1)
    {
        for (auto &regionLines : lines)
        {
            if (!regionLines.isImplicit())
            {
                // A_reg = A
                // TODO: use SgAssignStmt
                SgStatement *assign = new SgStatement(ASSIGN_STAT);
                SgExpression *left = new SgArrayRefExp(*newSymb);
                SgExpression *right = new SgArrayRefExp(*origSymb);

                assign->setExpression(0, *left);
                assign->setExpression(1, *right);
                regionLines.stats.first->insertStmtBefore(*assign, *regionLines.stats.first->controlParent());

                __spf_print(1, "insert '%s = %s'\n", newSymb->identifier(), origSymb->identifier()); // remove

                // A = A_reg
                assign = new SgStatement(ASSIGN_STAT);
                left = new SgArrayRefExp(*origSymb);
                right = new SgArrayRefExp(*newSymb);
                assign->setExpression(0, *left);
                assign->setExpression(1, *right);
                regionLines.stats.second->insertStmtAfter(*assign, *regionLines.stats.second->lexNext()->controlParent());

                __spf_print(1, "insert '%s = %s'\n", origSymb->identifier(), newSymb->identifier()); // remove

                // TODO: SPF_ANALYSIS(decl)
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

// TODO: make copyArray(ragion, array, place, suffix="")
static void copyArray(ParallelRegion *region,
                      const pair<string, int> &place,
                      const string &funcName,
                      const DIST::Array *array,
                      const vector<ParallelRegionLines> &lines,
                      const string &suffix = "")
{
    string fileName = place.first;
    // string funcName = decl->controlParent()->symbol()->identifier();

    if (SgFile::switchToFile(fileName) != -1)
    {
        string newArrName = array->GetShortName() + suffix;
        SgSymbol *arrSymb = array->GetDeclSymbol()->GetOriginal();
        SgSymbol *newArrSymb = NULL;
        SgStatement *decl = SgStatement::getStatementByFileAndLine(place.first, place.second);
        SgStatement *newDecl = NULL;

        newArrSymb = &arrSymb->copy();
        newArrSymb->changeName(newArrName.c_str());
        newDecl = newArrSymb->makeVarDeclStmt();
        decl->insertStmtAfter(*newDecl, *decl->controlParent());

        __spf_print(1, "  new array '%s' as copy of array '%s' (line: %d)\n",
                    newArrName.c_str(),
                    arrSymb->identifier(),
                    decl->lineNumber()); // remove

        replaceSymbol(fileName, lines, arrSymb, newArrSymb);
        insertArrayCopying(fileName, lines, arrSymb, newArrSymb);
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void copyFunction(ParallelRegion *region, const FuncInfo *func, const string &suffix = "")
{
    if (SgFile::switchToFile(func->fileName) != -1)
    {
        // create copy function symbol and copy function for original function
        SgSymbol *funcSymb = func->funcPointer->GetOriginal()->symbol();
        SgSymbol *newFuncSymb = NULL;
        SgFile *file = func->funcPointer->GetOriginal()->getFile();
        string newFuncName = string(funcSymb->identifier()) + suffix;

        newFuncSymb = &(funcSymb->copySubprogram(*(file->firstStatement())));
        newFuncSymb = &newFuncSymb->copy();
        newFuncSymb->changeName(newFuncName.c_str());
        file->firstStatement()->lexNext()->setSymbol(*newFuncSymb);

        __spf_print(1, "  new function '%s' as copy of function '%s' (scope: %d) for file %s\n",
                    newFuncName.c_str(), funcSymb->identifier(), funcSymb->scope()->lineNumber(), func->fileName.c_str()); // remove

        // add copy function lines to explicit lines for next changes
        Statement *begin = new Statement(file->firstStatement()->lexNext());
        Statement *end = new Statement(file->firstStatement()->lexNext()->lastNodeOfStmt());
        pair<Statement*, Statement*> startEnd = make_pair(begin, end);
        pair<int, int> newLines = make_pair(startEnd.first->lineNumber(), startEnd.second->lineNumber());
        region->AddLines(newLines, file->filename(), &startEnd);

        __spf_print(1, "    explicit lines %d-%d added with statement ids %d,%d\n",
                    newLines.first, newLines.second,
                    startEnd.first->id(), startEnd.second->id()); // remove

        region->AddFuncSymbols(func->fileName, funcSymb, newFuncSymb);

        __spf_print(1, "    add replaced symbols (%s, %s) for file %s\n",
                    funcSymb->identifier(), newFuncSymb->identifier(), func->fileName.c_str()); // remove
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

void createFunctionsAndArrays(vector<ParallelRegion*> &regions,
                              const set<FuncInfo*> &allCommonFunctions,
                              const set<DIST::Array*> &allUsedCommonArrays)
{
    for (auto &region : regions)
    {
        __spf_print(1, "[%s]: create local arrays\n", region->GetName().c_str()); // remove

        // creating new arrays
        for (auto &funcArrays : region->GetUsedLocalArrays())
        {
            for (auto &arrayLines : funcArrays.second)
            {
                auto place = *arrayLines.first->GetDeclInfo().begin();
                copyArray(region, place, funcArrays.first->funcName, arrayLines.first, arrayLines.second, string("_") + region->GetName());
            }
        }

        __spf_print(1, "[%s]: create functions\n", region->GetName().c_str()); // remove

        // creating new functions
        auto crossedFuncs = region->GetCrossedFuncs();
        auto allFuncs = region->GetAllFuncCalls();
        // map<string, vector<ParallelRegionLines>> linesToEdit;

        for (auto &crossedFunc : crossedFuncs)
            copyFunction(region, crossedFunc, string("_") + region->GetName());

        for (auto &commonFunc : allCommonFunctions)
        {
            auto it = crossedFuncs.find(commonFunc);
            auto itt = region->GetAllFuncCalls().find(commonFunc);
            if (it == crossedFuncs.end() && itt != region->GetAllFuncCalls().end())
                copyFunction(region, commonFunc, string("_") + region->GetName());
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

                        __spf_print(1, "  explicit lines %d-%d added with statement ids %d,%d\n",
                                    funcLines.first, funcLines.second,
                                    beginEnd.first->GetOriginal()->id(), beginEnd.second->GetOriginal()->id()); // remove
                    }
                }
            }
        }

        // replace created functions calls
        auto funcSymbols = region->GetFuncSymbols();

        for (auto &fileLines : region->GetAllLines())
        {
            auto it = funcSymbols.find(fileLines.first);
            if (it != funcSymbols.end())
            {
                for (auto &origCopy : it->second)
                    replaceSymbol(fileLines.first, fileLines.second, origCopy.first, origCopy.second);
            }
        }
    }

    /*
    __spf_print(1, "create common arrays\n"); // remove

    // creating common-blocks
    // TODO: create new common-block
    SgStatement *commDecl = new SgStatement(COMM_STAT);
    SgExprListExp *commList = new SgExprListExp(COMM_LIST);
    commDecl->setExpression(0, *commList);

    // TODO: create new arrays into new common-block
    for (auto &commonArray : allUsedCommonArrays)
    {
        ;
    }
    */
}

void insertArraysCopying(const vector<ParallelRegion*> &regions)
{
    for (auto &region : regions)
    {
        for (auto &origCopy : region->GetFuncSymbols())
        {
            // insert local arrays copying
            for (auto &funcArrays : region->GetUsedLocalArrays())
                for (auto &arrayLines : funcArrays.second)
                    ; // insertArrayCopying(funcArrays.first->fileName, funcArrays.first->funcName, arrayLines.second, origCopy.first, origCopy.second);

            // insert common arrays copying
            for (auto &funcArrays : region->GetUsedCommonArrays())
                for (auto &array : funcArrays.second)
                    ; // insertArrayCopying(funcArrays.first->fileName, funcArrays.first->funcName, arrayLines.second, origCopy.first, origCopy.second);
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

        for (auto &funcArrays : region->GetUsedCommonArrays())
            for (auto &arrayLines : funcArrays.second)
                outText += " " + arrayLines.first->GetShortName();

        outText += "\n";
        outText += "  LOCAL ARRAYS in [FUNC, ARRAY, [LINES]]:\n";
        
        for (auto &funcArrays : region->GetUsedLocalArrays())
        {
            for (auto &arrayLines : funcArrays.second)
            {
                string toPrint = "";
                for (auto &lines : arrayLines.second)
                {
                    toPrint += "[" + to_string(lines.lines.first);
                    toPrint += "-" + to_string(lines.lines.second);
                    toPrint += "]";
                }

                outText += "    [" + funcArrays.first->funcName + ", " + arrayLines.first->GetShortName() + ", " + toPrint + "]\n";
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
