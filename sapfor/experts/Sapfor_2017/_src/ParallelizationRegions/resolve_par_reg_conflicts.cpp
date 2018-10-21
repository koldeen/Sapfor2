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

static void recPrint(SgStatement *st, SgExpression *exp)
{
    if (exp)
    {
        if (exp->symbol())
            __spf_print(1, "line %d, symb %s, id %d\n", st->lineNumber(), exp->symbol()->identifier(), exp->symbol()->id());

        recPrint(st, exp->lhs());
        recPrint(st, exp->rhs());
    }
}

static void statPrint(SgStatement *start, SgStatement *end)
{
    for (auto st = start; st != end; st = st->lexNext())
        for (auto i = 0; i < 3; ++i)
            recPrint(st, st->expr(i));

    __spf_print(1, "end\n");
}

static void funcPrint(const FuncInfo *func)
{
    statPrint(func->funcPointer->GetOriginal(), func->funcPointer->GetOriginal()->lastNodeOfStmt());
}

static void symbPrint(SgFile *file)
{
    __spf_print(1, "symbols in file %s:\n", file->filename());

    for (auto s = file->firstSymbol(); s; s = s->next())
        __spf_print(1, "  SYMB ID: %d, NAME : %s\n", s->id(), s->identifier());
}

static bool checkSymbName(const string &symbName)
{
    bool found = false;
    set<string> vars;
    SgFile *oldFile = current_file;
    
    for (int i = 0; i < CurrentProject->numberOfFiles(); ++i)
    {
        SgFile *file = &(CurrentProject->file(i));

        if (SgFile::switchToFile(file->filename()) != -1)
        {
            for (auto symb = file->firstSymbol(); symb; symb = symb->next())
                if (symb->identifier())
                    vars.insert(symb->identifier());
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    if (SgFile::switchToFile(oldFile->filename()) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (vars.find(symbName) != vars.end())
        found = true;
    
    return found;
}

static bool isSPF_reg(SgStatement *st)
{
    return st->variant() == SPF_PARALLEL_REG_DIR || st->variant() == SPF_END_PARALLEL_REG_DIR;
}

static SgStatement* getFuncStat(SgStatement *st)
{
    if (!st)
        return NULL;

    SgStatement *iterator = st;

    while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
        iterator = iterator->controlParent();

    return iterator;
}

static string getStringDeclaration(SgSymbol *symb)
{
    string decl;
    SgFile *oldFile = current_file;

    if (SgFile::switchToFile(symb->getFile()->filename()) != -1)
        decl = symb->makeVarDeclStmt()->unparse();
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (SgFile::switchToFile(oldFile->filename()) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return decl;
}

static void makeStringDeclarations(SgStatement *insertPlace, const map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays)
{
    for (auto &arrayBlock : allUsedCommonArrays)
    {
        // check if need to add array
        int pos = -1;
        for (auto &var : arrayBlock.second->getVariables())
        {
            if (var.getName() == arrayBlock.first->GetShortName() && var.getType() == ARRAY)
                pos = var.getPosition();
        }

        auto varsOnPos = arrayBlock.second->getVariables(pos);
        if (varsOnPos.size() && varsOnPos[0]->getName() == arrayBlock.first->GetShortName())
        {
            SgSymbol *varSymb = varsOnPos[0]->getSymbol();
            string varName = varSymb->identifier();
            string newName = varName + "_reg";
            varSymb->changeName(newName.c_str());
            string decl = getStringDeclaration(varsOnPos[0]->getSymbol());
            varSymb->changeName(varName.c_str());
            insertPlace->addComment(decl.c_str());
        }
    }
}

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

static void findCall(const FuncInfo *func, const FuncInfo *callFunc, bool &callsFromRegion, bool &callsFromCode)
{
    if (SgFile::switchToFile(callFunc->fileName) != -1)
    {
        bool isRegion = false;
        SgStatement *iterator = callFunc->funcPointer->GetOriginal();
        SgStatement *end = SgStatement::getStatementByFileAndLine(callFunc->fileName, callFunc->linesNum.second);

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
                if (iterator->symbol()->identifier() == func->funcName)
                    retVal = true;

            for (int i = 0; i < 3; ++i)
                retVal = retVal || recursiveFindCall(iterator->expr(i), func->funcName);

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

static void createSetOfCalledFunc(const string &funcName, const map<string, FuncInfo*> &funcMap, set<FuncInfo*> &callSet)
{
    set<string> queue;

    queue.insert(funcName);

    while (queue.size())
    {
        auto it = queue.begin();
        FuncInfo *func = getFuncInfo(funcMap, *it);
        queue.erase(it);

        for (auto &call : func->callsFrom)
        {
            FuncInfo *callFunc = getFuncInfo(funcMap, call);
            auto it2 = callSet.find(callFunc);
            if (it2 == callSet.end() && callFunc)
            {
                callSet.insert(it2, callFunc);
                queue.insert(call);
            }
        }
    }
}

static void fillRegionCover(FuncInfo *func, const map<string, FuncInfo*> &funcMap)
{
    if (func->funcPointer->variant() != ENTRY_STAT)
    {
        if (SgFile::switchToFile(func->fileName) != -1)
        {
            SgStatement *iterator = func->funcPointer->GetOriginal();
            FuncInfo *entry = NULL;
            bool isFuncCovered = true;
            bool isEntryCovered = false;
            bool isRegion = false;

            // ALEX, TODO: а DVM директивы €вл€еютс€ нужными?
            for (; !isSgExecutableStatement(iterator) && !isSPF_reg(iterator) && iterator->variant() != ENTRY_STAT; iterator = iterator->lexNext())
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
                        entry->setIsCoveredByRegion(1);

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
                entry->setIsCoveredByRegion(1);

            if (isFuncCovered)
                func->setIsCoveredByRegion(1);
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
}

static const CommonBlock* isInCommon(const map<string, CommonBlock> &commonBlocks, const string &arrayName)
{
    for (auto &commonBlockPair : commonBlocks)
        for (auto &variable : commonBlockPair.second.getVariables())
            if (variable.getName() == arrayName)
                return &commonBlockPair.second;

    return NULL;
}

static void recursiveFill(SgStatement *st,
                          SgExpression *exp,
                          ParallelRegion *region,
                          const string &fileName,
                          const string &funcName,
                          const ParallelRegionLines &lines,
                          const map<string, FuncInfo*> &funcMap,
                          const map<string, CommonBlock> &commonBlocks,
                          map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            SgSymbol *arraySymbol = exp->symbol();
            string arrayName = string(arraySymbol->identifier());
            DIST::Array *array = getArrayFromDeclarated(declaratedInStmt(arraySymbol), arrayName);
            FuncInfo *func = getFuncInfo(funcMap, funcName);

            auto commonBlock = isInCommon(commonBlocks, arrayName);
            if (commonBlock)
            {
                auto it = region->GetCrossedFuncs().find(func);
                if (isSgExecutableStatement(st))
                    region->AddUsedCommonArray(func, array, lines);

                allUsedCommonArrays.insert(make_pair(array, commonBlock));
            }
            else if (!lines.isImplicit())
                region->AddUsedLocalArray(func, array, lines);
        }

        recursiveFill(st, exp->rhs(), region, fileName, funcName, lines, funcMap, commonBlocks, allUsedCommonArrays);
        recursiveFill(st, exp->lhs(), region, fileName, funcName, lines, funcMap, commonBlocks, allUsedCommonArrays);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions,
                      const map<string, vector<FuncInfo*>> &allFuncInfo,
                      const map<string, CommonBlock> &commonBlocks,
                      map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);
    
    for (auto &region : regions)
    {
        auto funcSymbols = region->GetFuncSymbols();

        for (auto &fileLines : region->GetAllLines())
        {
            // switch to current file
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                auto it = funcSymbols.find(fileLines.first);
                if (it == funcSymbols.end())
                    region->AddFileForFuncSymbols(fileLines.first);

                for (auto &regionLines : fileLines.second)
                {
                    SgStatement *iterator = NULL;
                    SgStatement *end = NULL;
                    string funcName = "";

                    // implicit lines
                    if (regionLines.isImplicit())
                    {
                        iterator = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.first);
                        end = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.second);
                    }
                    else
                    {
                        iterator = regionLines.stats.first->GetOriginal();
                        end = regionLines.stats.second->GetOriginal();
                    }

                    iterator = getFuncStat(iterator);
                    funcName = iterator->symbol()->identifier();

                    if (regionLines.isImplicit())
                        iterator = SgStatement::getStatementByFileAndLine(fileLines.first, regionLines.lines.first);
                    else
                        iterator = regionLines.stats.first;

                    for (; iterator && iterator != end; iterator = iterator->lexNext())
                    {
                        if (isSPF_stat(iterator) || isDVM_stat(iterator))
                            continue;

                        for (int i = 0; i < 3; ++i)
                            recursiveFill(iterator, iterator->expr(i), region, fileLines.first, funcName, regionLines, funcMap, commonBlocks, allUsedCommonArrays);
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
        //            funcPair.second->linesNum.first, funcPair.second->linesNum.second, funcPair.second->isCoveredByRegion); // DEBUG

        for (auto &call : funcPair.second->callsTo)
            findCall(funcPair.second, call, callsFromRegion, callsFromCode);

        if (callsFromCode && callsFromRegion)
            allCommonFunctions.insert(funcPair.second);
    }

    set<FuncInfo*> callSet;
    for (auto &commFunc : allCommonFunctions)
        createSetOfCalledFunc(commFunc->funcName, funcMap, callSet);

    for (auto &region : regions)
        for (auto &func : callSet)
            region->AddCrossedFunc(func);
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
        if (exp->variant() == ARRAY_REF || exp->variant() == VAR_REF || exp->variant() == FUNC_CALL)
        {
            if (exp->symbol() && exp->symbol()->identifier() == from)
            {
                exp->setSymbol(to);

                //__spf_print(1, "  replace symbol '%s' to '%s'\n", from.c_str(), to->identifier()); // DEBUG
            }
        }

        recursiveReplace(exp->lhs(), from, to);
        recursiveReplace(exp->rhs(), from, to);
    }
}

static void replaceSymbol(const string &fileName, const ParallelRegionLines &regionLines, const string &origSymbName, SgSymbol *newSymb)
{
    if (SgFile::switchToFile(fileName) != -1)
    {
        // explicit lines
        if (!regionLines.isImplicit())
        {
            SgStatement *iterator = regionLines.stats.first->GetOriginal();
            SgStatement *end = regionLines.stats.second->GetOriginal()->lexNext();

            for (; iterator != end; iterator = iterator->lexNext())
            {
                // skip not executable statements and change symbols only in executable section
                if (!isSgExecutableStatement(iterator) && (iterator->variant() != VAR_DECL && iterator->variant() != EXTERN_STAT))
                    continue;

                if (iterator->symbol() && iterator->symbol()->identifier() == origSymbName)
                {
                    iterator->setSymbol(*newSymb);

                    /*
                    __spf_print(1, "  replace symbol '%s' to '%s' in file %s on line %d\n",
                                origSymbName.c_str(),
                                newSymb->identifier(),
                                fileName.c_str(),
                                iterator->lineNumber()); // DEBUG
                    */
                }

                for (int i = 0; i < 3; ++i)
                    recursiveReplace(iterator->expr(i), origSymbName, newSymb);
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static SgStatement* createCommonBlock(SgFile *file,
                                      const map<string, CommonBlock> &commonBlocks,
                                      const map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays,
                                      map<string, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>> &createdCommonArrays,
                                      map<string, SgStatement*> &createdCommonBlocks)
{
    string fileName = file->filename();

    if (SgFile::switchToFile(fileName) != -1)
    {
        auto it = createdCommonBlocks.find(fileName);
        if (it == createdCommonBlocks.end())
        {
            // new common-block is not created at this file, so create it
            // creating new common-block statement
            string commBlockName = "reg";
            SgStatement *commDecl = new SgStatement(COMM_STAT);

            // TODO: check new common-block name
            
            SgSymbol *commSymb = new SgSymbol(VARIABLE_NAME, commBlockName.c_str());
            SgExprListExp *commList = new SgExprListExp(COMM_LIST);
            SgExprListExp *curNode = NULL;
            commDecl->setExpression(0, *commList);
            commList->setSymbol(commSymb);

            for (auto &arrayBlock : allUsedCommonArrays)
            {
                // check if need to add array
                int pos = -1;
                for (auto &var : arrayBlock.second->getVariables())
                {
                    if (var.getName() == arrayBlock.first->GetShortName() && var.getType() == ARRAY)
                        pos = var.getPosition();
                }

                auto varsOnPos = arrayBlock.second->getVariables(pos);
                if (varsOnPos.size() && varsOnPos[0]->getName() == arrayBlock.first->GetShortName())
                {
                    // need to add
                    // check if need to create new common array symbol
                    SgSymbol *newArrSymb = NULL;

                    auto it = createdCommonArrays.find(fileName);
                    if (it == createdCommonArrays.end())
                        it = createdCommonArrays.insert(it, make_pair(fileName, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>()));

                    auto itt = it->second.find(arrayBlock.first);
                    if (itt == it->second.end())
                    {
                        // need to create symbol
                        string newArrName = arrayBlock.first->GetShortName() + "_" + commBlockName;

                        // TODO: check new array name

                        newArrSymb = new SgSymbol(VARIABLE_NAME, newArrName.c_str(), file->firstStatement());
                        itt = it->second.insert(itt, make_pair(arrayBlock.first, make_pair((SgSymbol*)NULL, newArrSymb)));
                    }
                    else
                    {
                        // just use previous created symbol
                        newArrSymb = itt->second.second;
                    }

                    if (!newArrSymb)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    // inserting newArrSymb to COMM_STAT
                    if (!curNode)
                    {
                        curNode = new SgExprListExp();
                        commList->setLhs(curNode);
                    }
                    else
                    {
                        SgExprListExp *newNode = new SgExprListExp();
                        curNode->setRhs(newNode);
                        curNode = (SgExprListExp*)curNode->rhs();
                    }

                    SgExpression *arrNode = new SgExpression(VAR_REF, NULL, NULL, newArrSymb);
                    curNode->setLhs(arrNode);
                }
            }

            createdCommonBlocks.insert(make_pair(fileName, commDecl));

            //__spf_print(1, "  new common block 'reg' in file %s created\n", fileName.c_str()); // DEBUG

            return commDecl;
        
        }

        return it->second;
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return NULL;
}

static void insertCommonBlock(FuncInfo *func,
                              const map<string, CommonBlock> &commonBlocks,
                              const map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays,
                              map<string, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>> &createdCommonArrays,
                              map<string, SgStatement*> &createdCommonBlocks,
                              set<FuncInfo*> &insertedCommonBlocks)
{
    SgFile *file = func->funcPointer->GetOriginal()->getFile();
    SgStatement *commDecl = createCommonBlock(file, commonBlocks, allUsedCommonArrays, createdCommonArrays, createdCommonBlocks);
    SgStatement *copyDecl = commDecl->copyPtr();
    SgStatement *insertPlace = NULL;

    for (auto iterator = func->funcPointer->GetOriginal()->lexNext();
         !isSgExecutableStatement(iterator) || isSPF_stat(iterator);
         iterator = iterator->lexNext())
        insertPlace = iterator;

    if (!insertPlace)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    insertPlace->insertStmtAfter(*copyDecl, *insertPlace->controlParent());
    insertedCommonBlocks.insert(func);

    /*
    __spf_print(1, "  new common block 'reg' inserted in file %s in func '%s' at line %d\n",
                funcArrays.first->fileName.c_str(), funcArrays.first->funcName.c_str(), insertPlace->lineNumber()); // DEBUG
    */

    // create declarations via comment
    makeStringDeclarations(insertPlace->lexNext()->lexNext(), allUsedCommonArrays);
}

// file -> lines -> arrays; lines where arrays copying is inserted
static map<string, map<ParallelRegionLines, set<string>>> copiedArrays;

static void insertArrayCopying(const string &fileName, const ParallelRegionLines &regionLines, SgSymbol *origSymb, SgSymbol *newSymb)
{
    if (SgFile::switchToFile(fileName) != -1)
    {
        if (regionLines.isImplicit())
            return;

        auto it = copiedArrays.find(fileName);
        if (it == copiedArrays.end())
            it = copiedArrays.insert(it, make_pair(fileName, map<ParallelRegionLines, set<string>>()));

        auto it2 = it->second.find(regionLines);
        if (it2 == it->second.end())
            it2 = it->second.insert(it2, make_pair(regionLines, set<string>()));

        string arrName = origSymb->identifier();
        auto it3 = it2->second.find(arrName);

        if (it3 == it2->second.end())
        {
            // A_reg = A
            // TODO: use SgAssignStmt
            SgStatement *assign = new SgStatement(ASSIGN_STAT);
            SgExpression *left = new SgArrayRefExp(*newSymb);
            SgExpression *right = new SgArrayRefExp(*origSymb);

            assign->setExpression(0, *left);
            assign->setExpression(1, *right);
            regionLines.stats.first->GetOriginal()->lexPrev()->insertStmtBefore(*assign, *regionLines.stats.first->GetOriginal()->controlParent());

            //__spf_print(1, "insert '%s = %s'\n", newSymb->identifier(), origSymb->identifier()); // DEBUG

            // A = A_reg
            assign = new SgStatement(ASSIGN_STAT);
            left = new SgArrayRefExp(*origSymb);
            right = new SgArrayRefExp(*newSymb);
            assign->setExpression(0, *left);
            assign->setExpression(1, *right);
            regionLines.stats.second->GetOriginal()->lexNext()->insertStmtAfter(*assign, *regionLines.stats.first->GetOriginal()->controlParent());

            it2->second.insert(arrName);

            //__spf_print(1, "insert '%s = %s'\n", origSymb->identifier(), newSymb->identifier()); // DEBUG

            // TODO: SPF_ANALYSIS(decl)
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void replaceCommonArray(const string &fileName,
                               const string &arrayName,
                               const ParallelRegionLines &lines,
                               const map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays,
                               const map<string, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>> &createdCommonArrays,
                               const bool needInsertCopying = false)
{
    auto it = createdCommonArrays.find(fileName);
    if (it == createdCommonArrays.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement *iterator = getFuncStat(lines.stats.first->GetOriginal());
    SgStatement *end = iterator->lastNodeOfStmt();

    // get common-blocks ref
    const string commName = "reg";
    map<string, vector<SgExpression*>> commonBlocksRef;
    getCommonBlocksRef(commonBlocksRef, iterator, end, &commName);

    for (auto &commonBlockRef : commonBlocksRef)
    {
        for (auto &commExp : commonBlockRef.second)
        {
            for (auto exp = commExp->lhs(); exp; exp = exp->rhs())
            {
                SgSymbol *varSymb = exp->lhs()->symbol();
                string varName = varSymb->identifier();

                if (varName == arrayName)
                {
                    DIST::Array *array = getArrayFromDeclarated(declaratedInStmt(varSymb), varName);

                    if (array)
                    {
                        auto arrayBlock = allUsedCommonArrays.find(array);
                        int pos = -1;
                        for (auto &var : arrayBlock->second->getVariables())
                        {
                            if (var.getName() == varName && var.getType() == ARRAY)
                                pos = var.getPosition();
                        }

                        auto varsOnPos = arrayBlock->second->getVariables(pos);

                        if (pos == -1 || !varsOnPos.size())
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        auto var = varsOnPos[0];

                        if (SgFile::switchToFile(var->getSymbol()->getFile()->filename()) != -1)
                        {
                            DIST::Array *commArr = getArrayFromDeclarated(declaratedInStmt(var->getSymbol()), var->getName());

                            if (!commArr)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            auto itt = it->second.find(commArr);
                            if (itt == it->second.end())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            replaceSymbol(fileName, lines, varName, itt->second.second);
                            if (needInsertCopying) // if (!array->GetNonDistributeFlag())
                                insertArrayCopying(fileName, lines, varSymb, itt->second.second);
                        }
                        else
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }
                }
            }
        }
    }
}

static pair<SgSymbol*, SgSymbol*> copyArray(const pair<string, int> &place,
                                            const DIST::Array *array,
                                            const string &suffix = "")
{
    string fileName = place.first;

    if (SgFile::switchToFile(fileName) != -1)
    {
        string newArrName = array->GetShortName() + suffix;
        SgSymbol *arrSymb = array->GetDeclSymbol()->GetOriginal();
        SgSymbol *newArrSymb = NULL;
        SgStatement *decl = SgStatement::getStatementByFileAndLine(place.first, place.second);
        SgStatement *newDecl = NULL;

        // TODO: check new array name
        
        while (!isSgExecutableStatement(decl) || isSPF_stat(decl))
            decl = decl->lexNext();
        decl = decl->lexPrev();

        newArrSymb = &arrSymb->copy();
        newArrSymb->changeName(newArrName.c_str());
        newDecl = newArrSymb->makeVarDeclStmt();
        decl->insertStmtAfter(*newDecl, *decl->controlParent());

        /*
        __spf_print(1, "  new array '%s' as copy of array '%s' (line: %d)\n",
                    newArrName.c_str(),
                    arrSymb->identifier(),
                    decl->lineNumber()); // DEBUG
        */

        if (IS_ALLOCATABLE(arrSymb))
        {
            // add parameter to allocatable operator
            vector<SgStatement*> allDecls;
            declaratedInStmt(arrSymb, &allDecls);

            for (auto &decl : allDecls)
            {
                if (decl->variant() == ALLOCATABLE_STMT)
                {
                    SgExpression *list = decl->expr(0);
                    SgExprListExp *newNode = new SgExprListExp();
                    SgArrayRefExp *newArrRef = new SgArrayRefExp(*newArrSymb);

                    while (list && list->rhs())
                    {
                        list = list->rhs();
                    }

                    list->setRhs(newNode);
                    newNode->setLhs(newArrRef);
                    break;
                }
            }

            // add allocate/deallocate operators
            for (auto &data : getAttributes<SgStatement*, SgStatement*>(decl, set<int>{ ALLOCATE_STMT, DEALLOCATE_STMT }))
            {
                SgExpression *list = data->expr(0);
                while (list)
                {
                    SgArrayRefExp *arrayRef = isSgArrayRefExp(list->lhs());
                    if (arrayRef != NULL)
                    {
                        if (string(OriginalSymbol(arrayRef->symbol())->identifier()) == string(arrSymb->identifier()))
                        {
                            SgExprListExp *newNode = new SgExprListExp();
                            SgArrayRefExp *newArrRef = new SgArrayRefExp(*newArrSymb);

                            // add parameter to allocate() operator
                            if (data->variant() == ALLOCATE_STMT)
                            {
                                while (list->rhs())
                                {
                                    list = list->rhs();
                                }

                                list->setRhs(newNode);
                                newNode->setLhs(newArrRef);
                                
                                SgExprListExp *curNode = (SgExprListExp*)newArrRef;
                                list = arrayRef->lhs();
                                while (list)
                                {
                                    newNode = new SgExprListExp();
                                    SgExpression *valNode = new SgExpression(*list->lhs());

                                    curNode->setLhs(newNode);
                                    newNode->setLhs(valNode);

                                    curNode = (SgExprListExp*)valNode;
                                    list = list->lhs()->lhs();
                                }
                            }
                            // add parameter to deallocate() operator
                            else if (data->variant() == DEALLOCATE_STMT)
                            {
                                newNode->setLhs(newArrRef);
                                newNode->setRhs(data->expr(0));
                                data->setExpression(0, *newNode);
                            }

                            break;
                        }
                    }
                    list = list->rhs();
                }
            }
        }

        return make_pair(arrSymb, newArrSymb);
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void copyFunction(ParallelRegion *region,
                         const FuncInfo *func,
                         const map<string, CommonBlock> &commonBlocks,
                         const map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays,
                         map<string, vector<ParallelRegionLines>> &linesToEdit,
                         map<string, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>> &createdCommonArrays,
                         map<string, SgStatement*> &createdCommonBlocks,
                         const string &suffix = "")
{
    if (SgFile::switchToFile(func->fileName) != -1)
    {
        SgSymbol *funcSymb = func->funcPointer->GetOriginal()->symbol();
        SgSymbol *newFuncSymb = NULL;
        SgFile *file = func->funcPointer->GetOriginal()->getFile();
        string newFuncName = string(funcSymb->identifier()) + suffix;

        // create copy function symbol and copy function for original function
        newFuncSymb = &(funcSymb->copySubprogram(*(file->firstStatement())));
        newFuncSymb = &newFuncSymb->copy();
        newFuncSymb->changeName(newFuncName.c_str());
        file->firstStatement()->lexNext()->setSymbol(*newFuncSymb);

        // create copy function symbol in other region files
        for (auto &fileSymbs : region->GetFuncSymbols())
        {
            if (fileSymbs.first != file->filename())
            {
                if (SgFile::switchToFile(fileSymbs.first) != -1)
                {
                    for (auto symb = current_file->firstSymbol(); symb; symb = symb->next())
                    {
                        if ((symb->variant() == PROCEDURE_NAME || symb->variant() == FUNCTION_NAME) && symb->identifier() == func->funcName)
                        {
                            newFuncSymb = new SgSymbol(symb->variant(), newFuncName.c_str());
                            region->AddFuncSymbols(fileSymbs.first, symb, newFuncSymb);
                        }
                    }
                }
                else
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }

        if (SgFile::switchToFile(func->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        /*
        __spf_print(1, "  new function '%s' as copy of function '%s' (scope: %d) for file %s\n",
                    newFuncName.c_str(), funcSymb->identifier(), funcSymb->scope()->lineNumber(), func->fileName.c_str()); // DEBUG
        */

        // set line numbers
        for (auto origStat = func->funcPointer->GetOriginal(), copyStat = file->firstStatement()->lexNext();
             origStat != func->funcPointer->GetOriginal()->lastNodeOfStmt()->lexNext();
             origStat = origStat->lexNext(), copyStat = copyStat->lexNext())
        {
            copyStat->setlineNumber(origStat->lineNumber());
            //copyStat->setFileName(origStat->fileName());
        }

        // add copy function lines to explicit lines for next changes
        Statement *begin = new Statement(file->firstStatement()->lexNext());
        Statement *end = new Statement(file->firstStatement()->lexNext()->lastNodeOfStmt());
        pair<Statement*, Statement*> beginEnd = make_pair(begin, end);
        pair<int, int> newLines = make_pair(beginEnd.first->lineNumber(), beginEnd.second->lineNumber());

        auto it = linesToEdit.find(func->fileName);
        if (it == linesToEdit.end())
            it = linesToEdit.insert(it, make_pair(func->fileName, vector<ParallelRegionLines>()));
        it->second.push_back(ParallelRegionLines(newLines, beginEnd));

        /*
        __spf_print(1, "    lines %d-%d added with statement ids %d,%d\n",
                    newLines.first, newLines.second,
                    beginEnd.first->id(), beginEnd.second->id()); // DEBUG
        */

        region->AddFuncSymbols(func->fileName, funcSymb, newFuncSymb);

        /*
        __spf_print(1, "    add replaced symbols (%s, %s) for file %s\n",
                    funcSymb->identifier(), newFuncSymb->identifier(), func->fileName.c_str()); // DEBUG
        */

        // try to find common-block and add new if common-block exists
        for (auto origStat = func->funcPointer->GetOriginal(), copyStat = file->firstStatement()->lexNext();
             origStat && (!isSgExecutableStatement(origStat) || isSPF_stat(origStat));
             origStat = origStat->lexNext(), copyStat = copyStat->lexNext())
        {
            if (origStat->variant() == COMM_STAT)
            {
                SgStatement *commDecl = createCommonBlock(file, commonBlocks, allUsedCommonArrays, createdCommonArrays, createdCommonBlocks);
                SgStatement *copyDecl = commDecl->copyPtr();

                while (!isSgExecutableStatement(copyStat) || isSPF_stat(copyStat))
                    copyStat = copyStat->lexNext();

                copyStat = copyStat->lexPrev();
                copyStat->insertStmtAfter(*copyDecl, *copyStat->controlParent());

                /*
                __spf_print(1, "  new common block 'reg' inserted in file %s in func '%s' at line %d\n",
                            func->fileName.c_str(), newFuncName.c_str(), copyStat->lineNumber()); // DEBUG
                */

                // making declaration of new common array symbols
                // make declarations via comment through files
                makeStringDeclarations(copyStat->lexNext(), allUsedCommonArrays);

                auto it = createdCommonArrays.find(file->filename());
                if (it == createdCommonArrays.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                // replace common arrays to new common arrays in executable code section
                SgStatement *iterator = begin->GetOriginal();

                for (; iterator != end->GetOriginal() && (!isSgExecutableStatement(iterator) || isSPF_stat(iterator)); iterator = iterator->lexNext())
                    ;

                Statement *start = new Statement(iterator);
                ParallelRegionLines lines(make_pair(start->lineNumber(), end->lineNumber()), make_pair(start, end));

                // get common-blocks ref
                map<string, vector<SgExpression*>> commonBlocksRef;
                getCommonBlocksRef(commonBlocksRef, func->funcPointer->GetOriginal(), func->funcPointer->GetOriginal()->lastNodeOfStmt());

                for (auto &commonBlockRef : commonBlocksRef)
                {
                    for (auto &commExp : commonBlockRef.second)
                    {
                        for (auto exp = commExp->lhs(); exp; exp = exp->rhs())
                        {
                            SgSymbol *varSymb = exp->lhs()->symbol();
                            string varName = varSymb->identifier();
                            DIST::Array *array = getArrayFromDeclarated(declaratedInStmt(varSymb), varName);

                            if (array)
                            {
                                auto arrayBlock = allUsedCommonArrays.find(array);
                                int pos = -1;
                                for (auto &var : arrayBlock->second->getVariables())
                                {
                                    if (var.getName() == varName && var.getType() == ARRAY)
                                        pos = var.getPosition();
                                }

                                auto varsOnPos = arrayBlock->second->getVariables(pos);

                                if (pos == -1 || !varsOnPos.size())
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                auto var = varsOnPos[0];

                                if (SgFile::switchToFile(var->getSymbol()->getFile()->filename()) != -1)
                                {
                                    DIST::Array *commArr = getArrayFromDeclarated(declaratedInStmt(var->getSymbol()), var->getName());

                                    if (!commArr)
                                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                    auto itt = it->second.find(commArr);
                                    if (itt == it->second.end())
                                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                    replaceSymbol(func->fileName, lines, varName, itt->second.second);
                                }
                                else
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            }
                        }
                    }
                }

                break;
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

void resolveParRegions(vector<ParallelRegion*> &regions,
                       const map<string, vector<FuncInfo*>> &allFuncInfo,
                       const map<string, CommonBlock> &commonBlocks,
                       const set<FuncInfo*> &allCommonFunctions,
                       const map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays,
                       map<string, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>> &createdCommonArrays,
                       map<string, SgStatement*> &createdCommonBlocks,
                       set<FuncInfo*> &insertedCommonBlocks)
{
    for (auto &region : regions)
    {
        __spf_print(1, "[%s]: create local arrays\n", region->GetName().c_str()); // DEBUG

        // creating new local arrays
        for (auto &funcArrays : region->GetUsedLocalArrays())
        {
            for (auto &arrayLines : funcArrays.second)
            {
                auto place = *arrayLines.first->GetDeclInfo().begin();
                auto origCopy = copyArray(place, arrayLines.first, string("_") + region->GetName());

                for (auto &lines : arrayLines.second)
                {
                    replaceSymbol(place.first, lines, origCopy.first->identifier(), origCopy.second);
                    if (!arrayLines.first->GetNonDistributeFlag())
                        insertArrayCopying(place.first, lines, origCopy.first, origCopy.second);
                }
            }
        }

        __spf_print(1, "[%s]: create common arrays\n", region->GetName().c_str()); // DEBUG

        // creating new common arrays
        map<string, FuncInfo*> funcMap;
        createMapOfFunc(allFuncInfo, funcMap);

        // creating new common-block for files with explicit lines
        for (auto &fileLines : region->GetAllLines())
        {
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                for (auto &lines : fileLines.second)
                {
                    if (!lines.isImplicit())
                    {
                        SgStatement *iterator = getFuncStat(lines.stats.first->GetOriginal());
                        string funcName = iterator->symbol()->identifier();
                        FuncInfo *func = getFuncInfo(funcMap, funcName);

                        auto it = insertedCommonBlocks.find(func);
                        if (it == insertedCommonBlocks.end())
                            // need to insert common-block
                            insertCommonBlock(func, commonBlocks, allUsedCommonArrays, createdCommonArrays, createdCommonBlocks, insertedCommonBlocks);
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }

        // replace common arrays and insert array copying
        for (auto &funcArrays : region->GetUsedCommonArrays())
        {
            // replace common arrays to new common arrays and insert copying
            for (auto &arrayLines : funcArrays.second)
            {
                for (auto &lines : arrayLines.second)
                {
                    if (lines.isImplicit())
                    {
                        // finding explicit lines where implicit lines are called from
                        // forall lines, lines2: lines.isImplicit(), lines2.isExplicit ==>
                        //     exists func, func2: lines in func, lines2 in func2, func2 calls func explicit or implicit ==>
                        //         insert copying of common-arrays in lines2 used in lines
                        Statement *begin = new Statement(SgStatement::getStatementByFileAndLine(funcArrays.first->fileName, lines.lines.first));
                        Statement *end = new Statement(SgStatement::getStatementByFileAndLine(funcArrays.first->fileName, lines.lines.second));

                        SgStatement *iterator = getFuncStat(begin->GetOriginal());
                        string funcName = iterator->symbol()->identifier();
                        FuncInfo *func = getFuncInfo(funcMap, funcName);

                        for (auto &fileLines : region->GetAllLines())
                        {
                            if (SgFile::switchToFile(fileLines.first) != -1)
                            {
                                for (auto &lines2 : fileLines.second)
                                {
                                    if (!lines2.isImplicit())
                                    {
                                        iterator = getFuncStat(lines2.stats.first->GetOriginal());
                                        string func2Name = iterator->symbol()->identifier();
                                        set<FuncInfo*> callSet;
                                        createSetOfCalledFunc(func2Name, funcMap, callSet);

                                        auto it = callSet.find(func);
                                        if (it != callSet.end())
                                            // need to insert copying
                                            replaceCommonArray(fileLines.first, arrayLines.first->GetShortName(), lines2, allUsedCommonArrays, createdCommonArrays, true);
                                    }
                                }
                            }
                            else
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                    }
                    else
                        replaceCommonArray(funcArrays.first->fileName, arrayLines.first->GetShortName(), lines, allUsedCommonArrays, createdCommonArrays, true);
                }
            }
        }

        __spf_print(1, "[%s]: create functions\n", region->GetName().c_str()); // DEBUG

        // creating new functions
        auto crossedFuncs = region->GetCrossedFuncs();
        auto allFuncs = region->GetAllFuncCalls();

        map<string, vector<ParallelRegionLines>> newLinesToEdit; // file -> lines

        for (auto &crossedFunc : crossedFuncs)
            copyFunction(region, crossedFunc, commonBlocks, allUsedCommonArrays, newLinesToEdit, createdCommonArrays, createdCommonBlocks, string("_") + region->GetName());

        for (auto &commonFunc : allCommonFunctions)
        {
            auto it = crossedFuncs.find(commonFunc);
            auto itt = region->GetAllFuncCalls().find(commonFunc);
            // check that commonFunc is called in this region and not copied before as crossed function
            if (it == crossedFuncs.end() && itt != region->GetAllFuncCalls().end())
                copyFunction(region, commonFunc, commonBlocks, allUsedCommonArrays, newLinesToEdit, createdCommonArrays, createdCommonBlocks, string("_") + region->GetName());
        }

        // forall funcs B, C: B is not crossed & C is crossed & B calls C ==> need to change B
        //                    B is not common
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

                        auto it = newLinesToEdit.find(func->fileName);
                        if (it == newLinesToEdit.end())
                            it = newLinesToEdit.insert(it, make_pair(func->fileName, vector<ParallelRegionLines>()));
                        it->second.push_back(ParallelRegionLines(funcLines, beginEnd));

                        /*
                        __spf_print(1, "    lines %d-%d added with statement ids %d,%d\n",
                                    funcLines.first, funcLines.second,
                                    beginEnd.first->GetOriginal()->id(), beginEnd.second->GetOriginal()->id()); // DEBUG
                        */
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
                    for (auto &lines : fileLines.second)
                        replaceSymbol(fileLines.first, lines, origCopy.first->identifier(), origCopy.second);
            }
        }

        for (auto &fileLines : newLinesToEdit)
        {
            auto it = funcSymbols.find(fileLines.first);
            if (it != funcSymbols.end())
            {
                for (auto &origCopy : it->second)
                    for (auto &lines : fileLines.second)
                        replaceSymbol(fileLines.first, lines, origCopy.first->identifier(), origCopy.second);
            }
        }
    }
}

int printCheckRegions(const char *fileName, const vector<ParallelRegion*> &regions,
                      const map<DIST::Array*, const CommonBlock*> &allUsedCommonArrays,
                      const set<FuncInfo*> &allCommonFunctions)
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

    for (auto &commonArrayCommonBlock : allUsedCommonArrays)
        outText += " " + commonArrayCommonBlock.first->GetShortName();

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
