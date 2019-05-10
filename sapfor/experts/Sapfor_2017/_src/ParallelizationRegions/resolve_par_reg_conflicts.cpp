#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string.h>

#include "ParRegions_func.h"
#include "resolve_par_reg_conflicts.h"

#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"

using std::map;
using std::pair;
using std::set;
using std::vector;
using std::string;
using std::wstring;
using std::to_string;
using std::make_pair;

static inline int getRegionExplicitLine(SgStatement *startR)
{
    checkNull(startR, convertFileName(__FILE__).c_str(), __LINE__);

    const string saveName = current_file->filename();
    startR->switchToFile();

    SgStatement *regSt = startR->lexPrev();
    checkNull(regSt, convertFileName(__FILE__).c_str(), __LINE__);

    SgFile::switchToFile(saveName);
    return regSt->lineNumber();
}

static int getIntervalNumber(const int fileId, const int lineNumber, const int regionId)
{
    int fileMask = 0xFF;
    int lineMask = 0x7FFFF;
    int regionMask = 0xF;

    int filePart = fileMask & fileId;
    int linePart = lineMask & lineNumber;
    int regionPart = regionMask & regionId;

    filePart = filePart << 4;
    linePart = linePart << 12;
    int number = 1 << 31;

    number = number | filePart | linePart | regionPart;

    return number;
}

// array -> common-block
static map<DIST::Array*, const CommonBlock*> allUsedCommonArrays;

static bool checkSymbName(const string &symbName)
{
    bool found = false;
    SgFile *oldFile = current_file;
    
    for (int i = 0; !found && (i < CurrentProject->numberOfFiles()); ++i)
    {
        SgFile *file = &(CurrentProject->file(i));
        found = ifSymbolExists(file, symbName);
    }

    if (SgFile::switchToFile(oldFile->filename()) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return found;
}

static bool isSPF_reg(SgStatement *st)
{
    return st->variant() == SPF_PARALLEL_REG_DIR || st->variant() == SPF_END_PARALLEL_REG_DIR;
}

static const vector<const Variable*> getArraySynonyms(DIST::Array *array)
{
    auto arrayBlock = allUsedCommonArrays.find(array);
    if (arrayBlock == allUsedCommonArrays.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    // find array position
    int pos = -1;
    for (auto &var : arrayBlock->second->getVariables())
    {
        if (var.getName() == arrayBlock->first->GetShortName() && var.getType() == ARRAY)
            pos = var.getPosition();
    }

    // get all variables with this position
    return arrayBlock->second->getVariables(pos);
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

static void insertStringDeclarations(SgStatement *insertPlace, DIST::Array *array)
{
    auto varsOnPos = getArraySynonyms(array);
    if (varsOnPos.size() && varsOnPos[0]->getName() == array->GetShortName())
    {
        SgSymbol *varSymb = varsOnPos[0]->getSymbol();
        string varName = varSymb->identifier();
        string newName = varName + "_c";
        varSymb->changeName(newName.c_str());
        string decl = getStringDeclaration(varsOnPos[0]->getSymbol());
        varSymb->changeName(varName.c_str());
        insertPlace->addComment(decl.c_str());
    }
}

static void createSetOfCalledFuncs(const string &funcName, const map<string, FuncInfo*> &funcMap, set<FuncInfo*> &callSet)
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

//TODO: remove commented
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

            // ALEX, TODO: � DVM ��������� ��������� �������?
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
                    //if (entry && isEntryCovered)
                    //    entry->setIsCoveredByRegion(1);

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

            // ALEX, TODO: � �������� �� entry?
            // SERG, TODO: � �����? ���� isEntryCovered ������������ � true, ������ ���� ���������� entry
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
}

static void recursiveFill(SgStatement *st,
                          SgExpression *exp,
                          ParallelRegion *region,
                          const string &fileName,
                          const string &funcName,
                          const ParallelRegionLines &lines,
                          const map<string, FuncInfo*> &funcMap,
                          const map<string, CommonBlock> &commonBlocks)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            SgArrayRefExp *arrayRef = isSgArrayRefExp(exp);
            SgType *type = exp->symbol()->type();
            if (arrayRef && type && type->variant() != T_STRING)
            {
                SgSymbol *arraySymbol = exp->symbol();
                string arrayName = string(arraySymbol->identifier());
                DIST::Array *array = getArrayFromDeclarated(declaratedInStmt(arraySymbol), arrayName);
                FuncInfo *func = getFuncInfo(funcMap, funcName);

                checkNull(array, convertFileName(__FILE__).c_str(), __LINE__);
                checkNull(func, convertFileName(__FILE__).c_str(), __LINE__);

                if (!array->GetNonDistributeFlag())
                {
                    auto commonBlock = isArrayInCommon(commonBlocks, array);
                    if (commonBlock)
                    {
                        if (isSgExecutableStatement(st))
                            region->AddUsedCommonArray(func, array, lines);

                        allUsedCommonArrays.insert(make_pair(array, commonBlock));
                    }
                    else if (!lines.isImplicit())
                        region->AddUsedLocalArray(func, array, lines);
                }
            }
        }

        recursiveFill(st, exp->rhs(), region, fileName, funcName, lines, funcMap, commonBlocks);
        recursiveFill(st, exp->lhs(), region, fileName, funcName, lines, funcMap, commonBlocks);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions,
                      const map<string, vector<FuncInfo*>> &allFuncInfo,
                      const map<string, CommonBlock> &commonBlocks)
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
                        iterator = regionLines.stats.first->GetOriginal();

                    for (; iterator && iterator != end->lexNext(); iterator = iterator->lexNext())
                    {
                        if (isSPF_stat(iterator) || isDVM_stat(iterator))
                            continue;

                        for (int i = 0; i < 3; ++i)
                            recursiveFill(iterator, iterator->expr(i), region, fileLines.first, funcName, regionLines, funcMap, commonBlocks);
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
}

void fillRegionFunctions(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    // funcName -> funcInfo
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (auto &nameFunc : funcMap)
    {
        auto func = nameFunc.second;

        fillRegionCover(func, funcMap);

        // add DEFAULT region (regionId == 0)
        if (func->isIndirect())
        {
            for (auto &elem : func->detailCallsFrom)
            {
                auto line = elem.second;
                auto call = elem.first;
                auto callF = getFuncInfo(funcMap, call);
                auto regs = getAllRegionsByLine(regions, func->fileName, line).size();
                if (callF && !getAllRegionsByLine(regions, func->fileName, line).size())
                    callF->callRegions.insert(0);
            }
        }
    }

    // move DEFAULT region (regionId == 0)
    bool changes = true;
    while (changes)
    {
        changes = false;
        for (auto &nameFunc : funcMap)
        {
            auto func = nameFunc.second;
            if (func->callRegions.size() > 1 && func->callRegions.find(0) != func->callRegions.end())
            {
                for (auto &call : func->callsFrom)
                {
                    auto callF = getFuncInfo(funcMap, call);
                    if (callF && callF->callRegions.find(0) == callF->callRegions.end())
                    {
                        changes = true;
                        callF->callRegions.insert(0);
                    }
                }
            }
        }
    }
}

void fillRegionIntervals(vector<ParallelRegion*> &regions)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return;

    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLinesToModify())
        {
            // switch to current file
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                for (auto &lines : fileLines.second)
                {
                    // explicit lines
                    if (!lines.isImplicit())
                    {
                        SgStatement *start = NULL;
                        SgStatement *end = NULL;

                        // try to find interval before explicit lines
                        end = lines.stats.first->GetOriginal()->lexPrev()->lexPrev(); // before SPF_PARALLEL_REG_DIR
                        if (end && end->variant() == DVM_ENDINTERVAL_DIR)
                        {
                            for (auto st = end; st; st = st->lexPrev())
                            {
                                if (st->variant() == DVM_INTERVAL_DIR)
                                {
                                    start = st;

                                    Statement *intervalStart = new Statement(start);
                                    Statement *intervalEnd = new Statement(end);
                                    lines.intervalBefore = make_pair(intervalStart, intervalEnd);

                                    break;
                                }
                            }
                        }

                        // try to find interval after explicit lines
                        start = lines.stats.second->GetOriginal()->lexNext()->lexNext(); // after SPF_END_PARALLEL_REG_DIR
                        if (start && start->variant() == DVM_INTERVAL_DIR)
                        {
                            for (auto st = start; st; st = st->lexNext())
                            {
                                if (st->variant() == DVM_ENDINTERVAL_DIR)
                                {
                                    end = st;

                                    Statement *intervalStart = new Statement(start);
                                    Statement *intervalEnd = new Statement(end);
                                    lines.intervalAfter = make_pair(intervalStart, intervalEnd);

                                    break;
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

bool checkRegions(const vector<ParallelRegion*> &regions,
                  const map<string, vector<FuncInfo*>> &allFuncInfo,
                  map<string, vector<Messages>> &SPF_messages)
{
    bool noError = true;

    // check if region includes itself
    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLines())
        {
            for (auto &lines : fileLines.second)
            {
                if (!lines.isImplicit())
                {
                    for (auto &lines2 : fileLines.second)
                    {
                        if (lines2.isImplicit() && lines2.lines.first <= lines.lines.first && lines2.lines.second >= lines.lines.second)
                        {
                            __spf_print(1, "parallel region '%s' is included in file '%s' on line %d\n", region->GetName().c_str(),
                                        fileLines.first.c_str(), lines2.lines.first);
                            wstring messageE, messageR;
                            __spf_printToLongBuf(messageE, L"parallel region '%s' is included in file '%s'",
                                                 to_wstring(region->GetName()).c_str(), to_wstring(fileLines.first).c_str());
#ifdef _WIN32
                            __spf_printToLongBuf(messageR, L"������� ����������������� '%s' �������� ���� ���� � ����� '%s'",
                                                 to_wstring(region->GetName()).c_str(), to_wstring(fileLines.first).c_str());
#endif
                            getObjectForFileFromMap(fileLines.first.c_str(), SPF_messages).push_back(Messages(ERROR, lines2.lines.first, messageR, messageE, 1033));
                            noError = false;
                        }
                    }
                }
            }
        }
    }

    // check if explicit region lines are included by another region
    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLines())
        {
            for (auto &lines : fileLines.second)
            {
                if (!lines.isImplicit())
                {
                    for (auto line = lines.lines.first; line <= lines.lines.second; ++line)
                    {
                        auto inRegs = getAllRegionsByLine(regions, fileLines.first, line);
                        if (inRegs.size() > 1)
                        {
                            __spf_print(1, "parallel region '%s' has line included in another region on line %d\n", region->GetName().c_str(), line);

                            wstring messageE, messageR;
                            __spf_printToLongBuf(messageE, L"parallel region '%s' has line included in another region", to_wstring(region->GetName()).c_str());
#ifdef _WIN32
                            __spf_printToLongBuf(messageR, L"������� ����������������� '%s'�������� ������, ������� ��������� � ������ �������",
                                                 to_wstring(region->GetName()).c_str());
#endif
                            getObjectForFileFromMap(fileLines.first.c_str(), SPF_messages).push_back(Messages(ERROR, line, messageR, messageE, 1041));

                            noError = false;
                        }
                    }
                }
            }
        }
    }

    // check if there are several entries in each fragment
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLines())
        {
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                for (auto &lines : fileLines.second)
                {
                    if (!lines.isImplicit())
                    {
                        noError = noError && checkRegionEntries(lines.stats.first->GetOriginal()->lexPrev(), lines.stats.second->GetOriginal()->lexNext(), funcMap, regions, SPF_messages);
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }

    return noError;
}

static void recursiveReplace(SgStatement *st, SgExpression *exp, const string &from, SgSymbol *to)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF || exp->variant() == VAR_REF || exp->variant() == FUNC_CALL)
        {
            if (exp->symbol() && exp->symbol()->identifier() == from)
            {
                exp->setSymbol(to);
            }
        }

        recursiveReplace(st, exp->lhs(), from, to);
        recursiveReplace(st, exp->rhs(), from, to);
    }
}

static void replaceSymbol(const string &fileName, const ParallelRegionLines &lines, const string &origSymbName, SgSymbol *newSymb, bool replaceFunc = false)
{
    if (SgFile::switchToFile(fileName) != -1)
    {
        // explicit lines
        if (!lines.isImplicit())
        {
            SgStatement *iterator = lines.stats.first->GetOriginal();
            SgStatement *end = lines.stats.second->GetOriginal()->lexNext();

            for (; iterator != end; iterator = iterator->lexNext())
            {
                // skip not executable statements and change symbols only in executable section
                if (!isSgExecutableStatement(iterator) && (iterator->variant() != VAR_DECL && iterator->variant() != EXTERN_STAT))
                    continue;

                if (iterator->symbol() && iterator->symbol()->identifier() == origSymbName)
                    iterator->setSymbol(*newSymb);

                for (int i = 0; i < 3; ++i)
                    recursiveReplace(iterator, iterator->expr(i), origSymbName, newSymb);

                if (replaceFunc && isSgExecutableStatement(iterator))
                    break;
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void recReplaceFuncCalls(SgExpression *exp, const ParallelRegionLines &lines, const map<string, FuncInfo*> &funcMap, int regionId)
{
    if (exp)
    {
        if (exp->variant() == FUNC_CALL)
        {
            string funcName = exp->symbol()->identifier();
            FuncInfo *func = getFuncInfo(funcMap, funcName);

            if (func)
            {
                string newFuncName = func->getFuncNameByRegion(regionId);
                SgSymbol *newSymb = new SgSymbol(exp->symbol()->variant());
                newSymb->changeName(newFuncName.c_str());
                exp->setSymbol(*newSymb);

                // for extern
                replaceSymbol(current_file->filename(), lines, funcName, newSymb, true);
            }
        }

        recReplaceFuncCalls(exp->rhs(), lines, funcMap, regionId);
        recReplaceFuncCalls(exp->lhs(), lines, funcMap, regionId);
    }
}

static void replaceFuncCalls(const ParallelRegionLines &lines, const map<string, FuncInfo*> &funcMap, int regionId = 0)
{
    for (auto st = lines.stats.first->GetOriginal();
         st != lines.stats.second->GetOriginal()->lexNext();
         st = st->lexNext())
    {
        if (st->variant() == PROC_STAT)
        {
            string funcName = st->symbol()->identifier();
            FuncInfo *func = getFuncInfo(funcMap, funcName);
            
            if (func)
            {
                string newFuncName = func->getFuncNameByRegion(regionId);
                SgSymbol *newSymb = new SgSymbol(st->symbol()->variant());
                newSymb->changeName(newFuncName.c_str());
                st->setSymbol(*newSymb);
            }
        }

        for (int i = 0; i < 3; ++i)
            recReplaceFuncCalls(st->expr(i), lines, funcMap, regionId);
    }
}

static map<string, map<DIST::Array*, SgStatement*>> createdCommonBlocks; // file -> array -> new common statement
static map<string, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>> createdCommonArrays; // file -> array -> (orig, copy)

static SgStatement* createCommonBlock(SgFile *file, DIST::Array *array)
{
    auto varsOnPos = getArraySynonyms(array);
    if (!varsOnPos.size())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    string fileName = file->filename();

    if (SgFile::switchToFile(fileName) != -1)
    {
        auto fileArrayBlock = createdCommonBlocks.find(fileName);
        if (fileArrayBlock == createdCommonBlocks.end())
            fileArrayBlock = createdCommonBlocks.insert(fileArrayBlock, make_pair(fileName, map<DIST::Array*, SgStatement*>()));

        auto arrayBlock = fileArrayBlock->second.find(array);
        if (arrayBlock == fileArrayBlock->second.end())
        {
            // new common-block is not created for array at this file, so create it
            // creating new common-block statement
            string commBlockName = array->GetShortName() + "_r";
            SgStatement *commDecl = new SgStatement(COMM_STAT);

            // TODO: check new common-block name

            SgSymbol *commSymb = new SgSymbol(VARIABLE_NAME, commBlockName.c_str());
            SgExprListExp *commList = new SgExprListExp(COMM_LIST);
            SgExprListExp *curNode = NULL;
            commDecl->setExpression(0, *commList);
            commList->setSymbol(commSymb);

            // need to add
            // check if need to create new common array symbol
            SgSymbol *newArrSymb = NULL;

            auto it = createdCommonArrays.find(fileName);
            if (it == createdCommonArrays.end())
                it = createdCommonArrays.insert(it, make_pair(fileName, map<DIST::Array*, pair<SgSymbol*, SgSymbol*>>()));

            auto itt = it->second.find(array);
            if (itt == it->second.end())
            {
                // need to create symbol
                string newArrName = varsOnPos[0]->getName() + "_c";

                // TODO: check new array name

                newArrSymb = new SgSymbol(VARIABLE_NAME, newArrName.c_str(), file->firstStatement());
                SgType *type = new SgType(T_ARRAY);
                newArrSymb->setType(type);
                itt = it->second.insert(itt, make_pair(array, make_pair((SgSymbol*)NULL, newArrSymb)));
            }
            else
                // just use previous created symbol
                newArrSymb = itt->second.second;

            checkNull(newArrSymb, convertFileName(__FILE__).c_str(), __LINE__);

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

            fileArrayBlock->second.insert(make_pair(array, commDecl));

            return commDecl;
        }

        return arrayBlock->second;
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return NULL;
}

// func -> arrays; funcs where new common statement inserted
static map<FuncInfo*, set<DIST::Array*>> insertedCommonBlocks;

static void insertCommonBlock(FuncInfo *func, DIST::Array *array)
{
    SgFile *file = func->funcPointer->GetOriginal()->getFile();
    SgStatement *insertPlace = NULL;

    for (auto iterator = func->funcPointer->GetOriginal()->lexNext();
         !isSgExecutableStatement(iterator) || isSPF_stat(iterator) && !isSPF_reg(iterator);
         iterator = iterator->lexNext())
    {
        insertPlace = iterator;
    }

    //NULL - no decl stats in function!
    if (!insertPlace)
        insertPlace = func->funcPointer->GetOriginal();

    SgStatement *commDecl = createCommonBlock(file, array);
    SgStatement *copyDecl = commDecl->copyPtr();

    auto st = insertPlace->controlParent();
    if (st->variant() == GLOBAL)
        st = insertPlace;

    const int nextLine = insertPlace->lexNext()->lineNumber();
    insertPlace->insertStmtAfter(*copyDecl, *st);
    insertPlace->lexNext()->setlineNumber(nextLine);

    // create declaration via comment
    insertStringDeclarations(insertPlace->lexNext(), array);
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
            assign->setlineNumber(getNextNegativeLineNumber()); // before region
            regionLines.stats.first->GetOriginal()->lexPrev()->insertStmtBefore(*assign, *regionLines.stats.first->GetOriginal()->controlParent());

            // A = A_reg
            assign = new SgStatement(ASSIGN_STAT);
            left = new SgArrayRefExp(*origSymb);
            right = new SgArrayRefExp(*newSymb);
            
            assign->setExpression(0, *left);
            assign->setExpression(1, *right);
            regionLines.stats.second->GetOriginal()->lexNext()->insertStmtAfter(*assign, *regionLines.stats.first->GetOriginal()->controlParent());

            it2->second.insert(arrName);

            // TODO: SPF_ANALYSIS(decl)
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

// return true if error exists
static bool replaceCommonArray(const string &fileName,
                               const set<string> &arraySynonymNames,
                               const ParallelRegionLines &lines,
                               map<string, vector<Messages>> &SPF_messages,
                               const bool needInsertCopying = false)
{
    auto it = createdCommonArrays.find(fileName);
    if (it == createdCommonArrays.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement *begin = getFuncStat(lines.stats.first->GetOriginal());
    SgStatement *end = begin->lastNodeOfStmt();

    // get common-blocks ref
    DIST::Array *array = NULL;
    map<string, vector<SgExpression*>> commonBlocksRef;
    getCommonBlocksRef(commonBlocksRef, begin, end);

    for (auto &commonBlockRef : commonBlocksRef)
    {
        for (auto &commExp : commonBlockRef.second)
        {
            for (auto exp = commExp->lhs(); exp; exp = exp->rhs())
            {
                SgSymbol *varSymb = exp->lhs()->symbol();
                string varName = varSymb->identifier();

                if (arraySynonymNames.find(varName) != arraySynonymNames.end())
                {
                    array = getArrayFromDeclarated(declaratedInStmt(varSymb), varName);

                    if (array)
                    {
                        auto varsOnPos = getArraySynonyms(array);

                        if (!varsOnPos.size())
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        auto var = varsOnPos[0];

                        if (SgFile::switchToFile(var->getSymbol()->getFile()->filename()) != -1)
                        {
                            DIST::Array *commArr = getArrayFromDeclarated(declaratedInStmt(var->getSymbol()), var->getName());
                            checkNull(commArr, convertFileName(__FILE__).c_str(), __LINE__);

                            auto itt = it->second.find(commArr);
                            if (itt == it->second.end())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            replaceSymbol(fileName, lines, varName, itt->second.second);
                            if (needInsertCopying)
                                insertArrayCopying(fileName, lines, varSymb, itt->second.second);

                            // no error
                            return false;
                        }
                        else
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }
                }
            }
        }
    }

    if (!array)
    {
        string toPrint;
        for (auto &arrayName : arraySynonymNames)
            toPrint += " '" + arrayName + '\'';
        __spf_print(1, "wrong parallel region position, there is no common-block in file %s with any of such arrays:%s on line %d\n",
                    fileName.c_str(), toPrint.c_str(), lines.lines.first);

        wstring messageE, messageR;
        __spf_printToLongBuf(messageE, L"wrong parallel region position, there is no common-block in file %s with any of such arrays:%s",
                             to_wstring(fileName).c_str(), to_wstring(toPrint).c_str());
#ifdef _WIN32
        __spf_printToLongBuf(messageR, L"�������� ������������ �������: �� ���������� common-����� � ����� %s �� ���������� ���������:%s",
                             to_wstring(fileName).c_str(), to_wstring(toPrint).c_str());
#endif
        getObjectForFileFromMap(fileName.c_str(), SPF_messages).push_back(Messages(ERROR, lines.lines.first, messageR, messageE, 1034));
        // error
        return true;
    }

    // no error
    return false;
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
        
        while (!isSgExecutableStatement(decl) || isSPF_stat(decl) && !isSPF_reg(decl))
            decl = decl->lexNext();
        decl = decl->lexPrev();

        newArrSymb = &arrSymb->copy();
        newArrSymb->changeName(newArrName.c_str());
        newDecl = newArrSymb->makeVarDeclStmt();
        decl->insertStmtAfter(*newDecl, *decl->controlParent());

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
                         FuncInfo *func,
                         const map<string, FuncInfo*> &funcMap,
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

        if (SgFile::switchToFile(func->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        // set line numbers
        for (auto origStat = func->funcPointer->GetOriginal(), copyStat = file->firstStatement()->lexNext();
             origStat != func->funcPointer->GetOriginal()->lastNodeOfStmt()->lexNext();
             origStat = origStat->lexNext(), copyStat = copyStat->lexNext())
        {
            copyStat->setlineNumber(origStat->lineNumber());
            BIF_FILE_NAME(copyStat->thebif) = BIF_FILE_NAME(origStat->thebif);
        }

        // replace all func calls in copy function
        Statement *begin = new Statement(file->firstStatement()->lexNext());
        Statement *end = new Statement(file->firstStatement()->lexNext()->lastNodeOfStmt());
        pair<Statement*, Statement*> beginEnd = make_pair(begin, end);
        pair<int, int> newLines = make_pair(beginEnd.first->lineNumber(), beginEnd.second->lineNumber());
        ParallelRegionLines newFuncLines(newLines, beginEnd);
        replaceFuncCalls(newFuncLines, funcMap, region->GetId());
        
        if (func->funcPointer->GetOriginal()->variant() == FUNC_HEDR)
            replaceSymbol(current_file->filename(), newFuncLines, func->funcName, newFuncSymb);

        // try to find common-block and add new if common-block exists
        for (auto origStat = func->funcPointer->GetOriginal(), copyStat = file->firstStatement()->lexNext();
             origStat && (!isSgExecutableStatement(origStat) || isSPF_stat(origStat));
             origStat = origStat->lexNext(), copyStat = copyStat->lexNext())
        {
            if (origStat->variant() == COMM_STAT)
            {
                for (auto &arrayBlock : allUsedCommonArrays)
                    createCommonBlock(file, arrayBlock.first);

                auto usedCommonArrays = region->GetUsedCommonArrays().find(func);
                if (usedCommonArrays != region->GetUsedCommonArrays().end())
                {
                    for (auto &arrayLines : usedCommonArrays->second)
                    {
                        SgStatement *commDecl = createCommonBlock(file, arrayLines.first);
                        SgStatement *copyDecl = commDecl->copyPtr();

                        while (!isSgExecutableStatement(copyStat) || isSPF_stat(copyStat))
                            copyStat = copyStat->lexNext();

                        copyStat = copyStat->lexPrev();
                        copyStat->insertStmtAfter(*copyDecl, *copyStat->controlParent());

                        // making declaration of new common array symbol via comment through files
                        insertStringDeclarations(copyStat->lexNext(), arrayLines.first);
                    }

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

                                if (array && !array->GetNonDistributeFlag())
                                {
                                    auto varsOnPos = getArraySynonyms(array);

                                    if (!varsOnPos.size())
                                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                    auto var = varsOnPos[0];

                                    if (SgFile::switchToFile(var->getSymbol()->getFile()->filename()) != -1)
                                    {
                                        DIST::Array *commArr = getArrayFromDeclarated(declaratedInStmt(var->getSymbol()), var->getName());
                                        checkNull(commArr, convertFileName(__FILE__).c_str(), __LINE__);

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
                }

                break;
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

void fillUsedArraysInExp(const pair<Statement*, Statement*> &interval, const int exp, set<DIST::Array*> &varSet)
{
    if (exp > 2 || exp < 0)
        return;

    for (auto st = interval.first->GetOriginal()->lexNext(); st != interval.second->GetOriginal(); st = st->lexNext())
    {
        // after CONVERT_ASSIGN_TO_LOOP
        if (st->variant() == ASSIGN_STAT)
        {
            auto varSymb = st->expr(exp)->symbol();
            checkNull(varSymb, convertFileName(__FILE__).c_str(), __LINE__);
            auto array = getArrayFromDeclarated(declaratedInStmt(varSymb), varSymb->identifier());
            checkNull(array, convertFileName(__FILE__).c_str(), __LINE__);
            varSet.insert(array);
        }
    }
}

bool checkRegionsResolving(const vector<ParallelRegion*> &regions,
                           const map<string, vector<FuncInfo*>> &allFuncInfo,
                           const map<string, CommonBlock> &commonBlocks,
                           map<string, vector<Messages>> &SPF_messages)
{
    bool error = false;

    if (regions.size())
    {
        map<string, FuncInfo*> funcMap;
        createMapOfFunc(allFuncInfo, funcMap);

        // check functions
        for (auto &nameFunc : funcMap)
        {
            auto func = nameFunc.second;
            if (func->callRegions.size() > 1)
            {
                string outText = "";
                for (auto &regId : func->callRegions)
                {
                    auto reg = getRegionById(regions, regId);
                    if (!reg && regId)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    if (regId)
                        outText += "'" + reg->GetName() + "' ";
                    else
                        outText += "'DEFAULT' ";
                }
                __spf_print(1, "parallel regions %shave common function '%s' which is used inside them\n", outText.c_str(), nameFunc.first.c_str());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"parallel regions %shave common function '%s' which is used inside them",
                                     to_wstring(outText).c_str(), to_wstring(nameFunc.first).c_str());
#ifdef _WIN32
                __spf_printToLongBuf(messageR, L"������� ����������������� %s����� ����� ������������ ������� '%s'",
                                     to_wstring(outText).c_str(), to_wstring(nameFunc.first).c_str());
#endif

                ParallelRegion *reg = NULL;
                for (auto &regId : func->callRegions)
                {
                    if (regId)
                    {
                        reg = getRegionById(regions, regId);
                        break;
                    }
                }

                if (!reg)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                auto lines = reg->GetAllLines();
                bool ok = false;
                for (auto &linePair : lines)
                {
                    for (auto &line : linePair.second)
                    {
                        if (line.stats.first && line.stats.second)
                        {
                            getObjectForFileFromMap(linePair.first.c_str(), SPF_messages).push_back(Messages(ERROR, getRegionExplicitLine(line.stats.first), messageR, messageE, 3012));
                            error = true;
                            ok = true;
                            break;
                        }
                    }
                    if (ok)
                        break;
                }
                if (ok == false)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }

        // check local arrays
        for (auto &reg : regions)
        {
            for (auto &funcArrays : reg->GetUsedLocalArrays())
            {
                if (SgFile::switchToFile(funcArrays.first->fileName) != -1)
                {
                    for (auto &arrayLines : funcArrays.second)
                    {
                        auto regsByArr = arrayLines.first->GetRegionsName();
                        bool notResolved = false;

                        if (regsByArr.size() > 1)
                        {
                            // check if array is used only in region and its related interval
                            if (regsByArr.size() == 2 && regsByArr.find("default") != regsByArr.end())
                            {
                                auto array = arrayLines.first;
                                for (auto &line : array->GetUsagePlaces(funcArrays.first->fileName))
                                {
                                    auto inRegs = getAllRegionsByLine(regions, funcArrays.first->fileName, line);
                                    if (!inRegs.size())
                                    {
                                        bool inInterval = false;
                                        for (auto &regLines : arrayLines.second)
                                        {
                                            // check interval existing
                                            if (regLines.intervalBefore.first && regLines.intervalBefore.second && regLines.intervalAfter.first && regLines.intervalAfter.second)
                                            {
                                                if (line > regLines.intervalBefore.first->lineNumber() && line < regLines.intervalAfter.second->lineNumber())
                                                    inInterval = true;
                                            }
                                        }

                                        if (!inInterval)
                                            notResolved = true;
                                    }
                                }
                            }
                            else
                                notResolved = true;
                        }

                        if (notResolved)
                        {

                            string regions = "";
                            for (auto &reg : regsByArr)
                                regions += "'" + reg + "' ";
                            __spf_print(1, "parallel regions %shave local array '%s' which is used inside them\n",
                                        regions.c_str(), arrayLines.first->GetShortName().c_str());

                            wstring messageE, messageR;
                            __spf_printToLongBuf(messageE, L"parallel regions %shave local array '%s' which is used inside them",
                                                 to_wstring(regions).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#ifdef _WIN32
                            __spf_printToLongBuf(messageR, L"������� ����������������� %s����� ����� ������������ ��������� ������",
                                                 to_wstring(regions).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#endif

                            auto lines = reg->GetAllLines();
                            bool ok = false;
                            for (auto &linePair : lines)
                            {
                                for (auto &line : linePair.second)
                                {
                                    if (line.stats.first && line.stats.second)
                                    {
                                        getObjectForFileFromMap(linePair.first.c_str(), SPF_messages).push_back(Messages(ERROR, getRegionExplicitLine(line.stats.first), messageR, messageE, 3013));
                                        error = true;
                                        ok = true;
                                        break;
                                    }
                                }
                                if (ok)
                                    break;
                            }
                            if (ok == false)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                    }
                }
                else
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }

        // check common arrays
        for (auto &reg : regions)
        {
            for (auto &funcArrays : reg->GetUsedCommonArrays())
            {
                for (auto &arrayLines : funcArrays.second)
                {
                    auto commonBlock = isArrayInCommon(commonBlocks, arrayLines.first);
                    checkNull(commonBlock, convertFileName(__FILE__).c_str(), __LINE__);
                    if (!arrayLines.second.size())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    // check common block name and variables count
                    auto lines = arrayLines.second[0].lines;
                    string commonBlockName = commonBlock->getName();
                    auto pos = commonBlockName.rfind("_r");
                    if (!arrayLines.second[0].isImplicit() && (pos != commonBlockName.length() - 2 || commonBlock->getVariables().size() != 1))
                    {
                        __spf_print(1, "parallel region '%s' has common array '%s' which is used inside and outside region on lines %d-%d\n",
                                    reg->GetName().c_str(), arrayLines.first->GetShortName().c_str(), lines.first, lines.second);

                        wstring messageE, messageR;
                        __spf_printToLongBuf(messageE, L"parallel region '%s' has common array '%s' which is used inside and outside region",
                                             to_wstring(reg->GetName()).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#ifdef _WIN32
                        __spf_printToLongBuf(messageR, L"������� ����������������� '%s' �������� common-������ '%s', ������������ � ������� � ��� �",
                                             to_wstring(reg->GetName()).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#endif
                        
                        getObjectForFileFromMap(funcArrays.first->fileName.c_str(), SPF_messages).push_back(Messages(ERROR, getRegionExplicitLine(arrayLines.second[0].stats.first), messageR, messageE, 3014));
                        error = true;
                    }
                }
            }
        }

        // check intervals and arrays copying
        for (auto &reg : regions)
        {
            for (auto &fileLines : reg->GetAllLines())
            {
                if (SgFile::switchToFile(fileLines.first) != -1)
                {
                    // check array copying existing
                    for (auto &lines : fileLines.second)
                    {
                        if (!lines.isImplicit())
                        {
                            // check interval existing
                            if (!lines.intervalBefore.first || !lines.intervalBefore.second || !lines.intervalAfter.first || !lines.intervalAfter.second)
                            {
                                __spf_print(1, "parallel region '%s' does not have DVM interval for fragment on line %d\n",
                                            reg->GetName().c_str(), lines.lines.first);

                                wstring messageE, messageR;
                                __spf_printToLongBuf(messageE, L"parallel region '%s' does not have DVM interval for fragment", to_wstring(reg->GetName()).c_str());
#ifdef _WIN32
                                __spf_printToLongBuf(messageR, L"������� ����������������� '%s' �� ����� DVM-��������� ��� ���������", to_wstring(reg->GetName()).c_str());
#endif

                                getObjectForFileFromMap(fileLines.first.c_str(), SPF_messages).push_back(Messages(ERROR, getRegionExplicitLine(lines.stats.first), messageR, messageE, 3015));
                                error = true;
                            }
                            // check arrays
                            else
                            {
                                set<DIST::Array*> leftBefore;
                                set<DIST::Array*> rightAfter;

                                fillUsedArraysInExp(lines.intervalBefore, 0, leftBefore);
                                fillUsedArraysInExp(lines.intervalAfter, 1, rightAfter);

                                // check left and right sets if common array is used at this lines
                                for (auto funcArrays : reg->GetUsedCommonArrays())
                                {
                                    if (funcArrays.first->fileName == fileLines.first)
                                    {
                                        for (auto &arrayLines : funcArrays.second)
                                        {
                                            for (auto &lines2 : arrayLines.second)
                                            {
                                                if (lines == lines2)
                                                {
                                                    if (leftBefore.find(arrayLines.first) == leftBefore.end() || rightAfter.find(arrayLines.first) == rightAfter.end())
                                                    {
                                                        __spf_print(1, "parallel region '%s' does not have copying of array '%s' in DVM interval on line %d\n",
                                                                    reg->GetName().c_str(), arrayLines.first->GetShortName().c_str(), lines.lines.first);

                                                        wstring messageE, messageR;
                                                        __spf_printToLongBuf(messageE, L"parallel region '%s' does not have copying of array '%s' in DVM interval",
                                                                             to_wstring(reg->GetName()).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#ifdef _WIN32
                                                        __spf_printToLongBuf(messageR, L"������� ����������������� '%s' �� �������� ����������� ������� '%s' � DVM-���������",
                                                                             to_wstring(reg->GetName()).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#endif
                                                        getObjectForFileFromMap(fileLines.first.c_str(), SPF_messages).push_back(Messages(ERROR, lines.lines.first, messageR, messageE, 3018));
                                                        error = true;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                // check left and right sets if local array is used at this lines
                                for (auto funcArrays : reg->GetUsedLocalArrays())
                                {
                                    if (funcArrays.first->fileName == fileLines.first)
                                    {
                                        for (auto &arrayLines : funcArrays.second)
                                        {
                                            for (auto &lines2 : arrayLines.second)
                                            {
                                                if (lines == lines2)
                                                {
                                                    if (leftBefore.find(arrayLines.first) == leftBefore.end() || rightAfter.find(arrayLines.first) == rightAfter.end())
                                                    {
                                                        __spf_print(1, "parallel region '%s' does not have copying of array '%s' in DVM interval on line %d\n",
                                                                    reg->GetName().c_str(), arrayLines.first->GetShortName().c_str(), lines.lines.first);

                                                        wstring messageE, messageR;
                                                        __spf_printToLongBuf(messageE, L"parallel region '%s' does not have copying of array '%s' in DVM interval",
                                                                             to_wstring(reg->GetName()).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#ifdef _WIN32
                                                        __spf_printToLongBuf(messageR, L"������� ����������������� '%s' �� �������� ����������� ������� '%s' � DVM-���������",
                                                                             to_wstring(reg->GetName()).c_str(), to_wstring(arrayLines.first->GetShortName()).c_str());
#endif
                                                        getObjectForFileFromMap(fileLines.first.c_str(), SPF_messages).push_back(Messages(ERROR, lines.lines.first, messageR, messageE, 3017));
                                                        error = true;
                                                    }
                                                }
                                            }
                                        }
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

    return error;
}

int resolveParRegions(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> &allFuncInfo, map<string, vector<Messages>> &SPF_messages)
{
    bool error = false;

    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (auto &region : regions)
    {
        __spf_print(1, "[%s]: create local arrays\n", region->GetName().c_str()); // DEBUG

        // creating new local arrays
        for (auto &funcArrays : region->GetUsedLocalArrays())
        {
            for (auto &arrayLines : funcArrays.second)
            {
                if (arrayLines.first->GetRegionsName().size() > 1)
                {
                    auto place = *arrayLines.first->GetDeclInfo().begin();
                    auto origCopy = copyArray(place, arrayLines.first, string("_l") + to_string(region->GetId()));

                    for (auto &lines : arrayLines.second)
                    {
                        replaceSymbol(place.first, lines, origCopy.first->identifier(), origCopy.second);
                        insertArrayCopying(place.first, lines, origCopy.first, origCopy.second);
                    }
                }
            }
        }

        __spf_print(1, "[%s]: create common arrays\n", region->GetName().c_str()); // DEBUG

        // creating new common-blocks for files with explicit lines
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
                            it = insertedCommonBlocks.insert(it, make_pair(func, set<DIST::Array*>()));

                        for (auto &arrayBlock : allUsedCommonArrays)
                        {
                            auto varsOnPos = getArraySynonyms(arrayBlock.first);
                            auto itt = it->second.find(arrayBlock.first);
                            // insert only one of all array synonyms
                            if (itt == it->second.end() && arrayBlock.first->GetShortName() == varsOnPos[0]->getName())
                            {
                                // need to insert common-block
                                insertCommonBlock(func, arrayBlock.first);
                                it->second.insert(arrayBlock.first);
                            }
                        }
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }

        // insert array copying in explicit lines (and replace common arrays in this lines)
        for (auto &funcArrays : region->GetUsedCommonArrays())
        {
            for (auto &arrayLines : funcArrays.second)
            {
                for (auto &lines : arrayLines.second)
                {
                    // get all synonyms for array
                    set<string> arraySynonyms;
                    auto varsOnPos = getArraySynonyms(arrayLines.first);
                    for (auto &var : varsOnPos)
                        arraySynonyms.insert(var->getName());

                    // replace common arrays to new common arrays and insert copying in explicit lines
                    if (lines.isImplicit())
                    {
                        // replace common arrays in explicit lines and insert copying
                        // finding explicit lines where implicit lines are called from
                        // forall lines, lines2: lines.isImplicit(), lines2.isExplicit ==>
                        //     exists func, func2: lines in func, lines2 in func2, func2 calls func explicit or implicit ==>
                        //         insert copying of common-arrays in lines2 used in lines
                        for (auto &fileLines : region->GetAllLines())
                        {
                            if (SgFile::switchToFile(fileLines.first) != -1)
                            {
                                for (auto &lines2 : fileLines.second)
                                {
                                    if (!lines2.isImplicit())
                                    {
                                        SgStatement *iterator = getFuncStat(lines2.stats.first->GetOriginal());
                                        string func2Name = iterator->symbol()->identifier();
                                        set<FuncInfo*> callSet;
                                        createSetOfCalledFuncs(func2Name, funcMap, callSet);

                                        auto it = callSet.find(funcArrays.first);
                                        if (it != callSet.end())
                                        {
                                            bool tempErr = replaceCommonArray(fileLines.first, arraySynonyms, lines2, SPF_messages, true);
                                            error = error || tempErr;
                                        }
                                    }
                                }
                            }
                            else
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                    }
                    else
                    {
                        if (SgFile::switchToFile(funcArrays.first->fileName) != -1)
                        {
                            bool tempErr = replaceCommonArray(funcArrays.first->fileName, arraySynonyms, lines, SPF_messages, true);
                            error = error || tempErr;
                        }
                        else
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }
                }
            }
        }
    }

    // creating new common-blocks for main program unit
    for (auto &funcPair : funcMap)
    {
        auto func = funcPair.second;
        if (func->isMain)
        {
            if (SgFile::switchToFile(func->fileName) != -1)
            {
                auto it = insertedCommonBlocks.find(func);
                if (it == insertedCommonBlocks.end())
                    it = insertedCommonBlocks.insert(it, make_pair(func, set<DIST::Array*>()));

                for (auto &arrayBlock : allUsedCommonArrays)
                {
                    auto varsOnPos = getArraySynonyms(arrayBlock.first);
                    auto itt = it->second.find(arrayBlock.first);
                    // insert only one of all array synonyms
                    if (itt == it->second.end() && arrayBlock.first->GetShortName() == varsOnPos[0]->getName())
                    {
                        // need to insert common-block
                        insertCommonBlock(func, arrayBlock.first);
                        it->second.insert(arrayBlock.first);
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            break;
        }
    }

    __spf_print(1, "create functions\n"); // DEBUG

    // creating new functions
    for (auto &fileFuncs : allFuncInfo)
    {
        if (SgFile::switchToFile(fileFuncs.first) != -1)
        {
            for (auto &func : fileFuncs.second)
            {
                // callRegions = {i}, i = 1, 2, ...
                if (func->callRegions.size() == 1 && *(func->callRegions.begin()) != 0)
                {
                    // need just create new common-blocks and replace arrays
                    SgFile *file = func->funcPointer->GetOriginal()->getFile();
                    ParallelRegion *region = getRegionById(regions, *(func->callRegions.begin()));

                    auto usedCommonArrays = region->GetUsedCommonArrays().find(func);
                    if (usedCommonArrays != region->GetUsedCommonArrays().end())
                    {
                        for (auto &arrayBlock : allUsedCommonArrays)
                            createCommonBlock(file, arrayBlock.first);

                        auto it = insertedCommonBlocks.find(func);
                        if (it == insertedCommonBlocks.end())
                            it = insertedCommonBlocks.insert(it, make_pair(func, set<DIST::Array*>()));

                        for (auto &arrayLines : usedCommonArrays->second)
                        {
                            auto itt = it->second.find(arrayLines.first);
                            if (itt == it->second.end())
                            {
                                // need to insert common-block
                                insertCommonBlock(func, arrayLines.first);
                                it->second.insert(arrayLines.first);

                                // replace common arrays to new common arrays in executable code section
                                SgStatement *iterator = func->funcPointer->GetOriginal();

                                for (; iterator != func->funcPointer->GetOriginal()->lastNodeOfStmt() &&
                                    (!isSgExecutableStatement(iterator) || isSPF_stat(iterator)); iterator = iterator->lexNext())
                                    ;

                                // get all synonyms for array
                                set<string> arraySynonyms;
                                auto varsOnPos = getArraySynonyms(arrayLines.first);
                                for (auto &var : varsOnPos)
                                    arraySynonyms.insert(var->getName());

                                Statement *start = new Statement(iterator);
                                Statement *end = new Statement(func->funcPointer->GetOriginal()->lastNodeOfStmt());
                                pair<Statement*, Statement*> beginEnd = make_pair(start, end);
                                pair<int, int> funcLines = make_pair(beginEnd.first->GetOriginal()->lineNumber(), beginEnd.second->GetOriginal()->lineNumber());
                                ParallelRegionLines lines(funcLines, beginEnd);
                                bool tempErr = replaceCommonArray(fileFuncs.first, arraySynonyms, lines, SPF_messages);
                                error = error || tempErr;
                            }
                        }
                    }
                }
                // callRegions = {i1, i2, ...}
                else if (func->callRegions.size() > 1)
                {
                    // need copy function for every region, the exeption is defalut region
                    for (auto &regionId : func->callRegions)
                        if (regionId)
                            copyFunction(getRegionById(regions, regionId), func, funcMap, string("_r") + to_string(regionId));
                }
            }
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    // replace function calls in funcs with callRegions = {i}, i = 1, 2, ...
    for (auto &fileFuncs : allFuncInfo)
    {
        if (SgFile::switchToFile(fileFuncs.first) != -1)
        {
            for (auto &func : fileFuncs.second)
            {
                if (func->callRegions.size() == 1 && *(func->callRegions.begin()))
                {
                    int regionId = *(func->callRegions.begin());
                    Statement *begin = func->funcPointer;
                    Statement *end = new Statement(begin->GetOriginal()->lastNodeOfStmt());
                    ParallelRegionLines funcLines(make_pair(begin->GetOriginal()->lineNumber(), end->GetOriginal()->lineNumber()), make_pair(func->funcPointer, end));
                    replaceFuncCalls(funcLines, funcMap, regionId);
                }
            }
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    // replace function calls in explicit lines
    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLines())
        {
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                for (auto &lines : fileLines.second)
                {
                    if (!lines.isImplicit())
                        replaceFuncCalls(lines, funcMap, region->GetId());
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }

    __spf_print(1, "insert DVM intervals\n"); // DEBUG

    // inserting dvm intervals
    for (auto &region : regions)
    {
        for (auto &fileLines : region->GetAllLines())
        {
            if (SgFile::switchToFile(fileLines.first) != -1)
            {
                for (auto &lines : fileLines.second)
                {
                    if (!lines.isImplicit())
                    {
                        // create DVM INTERVAL before region
                        SgStatement *start = NULL;
                        SgStatement *end = lines.stats.first->GetOriginal()->lexPrev()->lexPrev();

                        for (SgStatement *st = end; st && st->lineNumber() < 0; st = st->lexPrev())
                            start = st;

                        if (start)
                        {
                            // DVM INTERVAL N
                            SgStatement *interval = new SgStatement(DVM_INTERVAL_DIR);
                            SgExprListExp *newNode = new SgExprListExp();
                            int val = getIntervalNumber(current_file_id, lines.stats.first->GetOriginal()->lexPrev()->lineNumber(), region->GetId());
                            SgValueExp *valNode = new SgValueExp(val);
                            newNode->setLhs(valNode);
                            interval->setExpression(0, *newNode);
                            interval->setlineNumber(lines.stats.first->GetOriginal()->lineNumber());
                            start->insertStmtBefore(*interval, *start->controlParent());

                            // DVM END INTERVAL
                            interval = new SgStatement(DVM_ENDINTERVAL_DIR);
                            interval->setlineNumber(lines.stats.first->GetOriginal()->lineNumber());
                            end->insertStmtAfter(*interval, *end->controlParent());
                        }

                        // create DVM INTERVAL after region
                        start = lines.stats.second->GetOriginal()->lexNext()->lexNext();
                        end = NULL;

                        for (SgStatement *st = start; st && !st->lineNumber(); st = st->lexNext())
                            end = st;

                        if (end)
                        {
                            // DVM INTERVAL N
                            SgStatement *interval = new SgStatement(DVM_INTERVAL_DIR);
                            SgExprListExp *newNode = new SgExprListExp();
                            int val = getIntervalNumber(current_file_id, lines.stats.second->GetOriginal()->lexNext()->lineNumber(), region->GetId());
                            SgValueExp *valNode = new SgValueExp(val);
                            newNode->setLhs(valNode);
                            interval->setExpression(0, *newNode);
                            interval->setlineNumber(lines.stats.second->GetOriginal()->lineNumber());
                            start->insertStmtBefore(*interval, *start->controlParent());

                            // DVM END INTERVAL
                            interval = new SgStatement(DVM_ENDINTERVAL_DIR);
                            interval->setlineNumber(lines.stats.second->GetOriginal()->lineNumber());
                            end->insertStmtAfter(*interval, *end->controlParent());
                        }
                    }
                }
            }
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }

    return (error ? 1 : 0);
}

int printCheckRegions(const char *fileName, const vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    string outText = "";
    string elems = "";
    
    for (auto &region : regions)
    {
        outText += "*** REGION '" + region->GetName() + "'\n";
        for (auto &nameFunc : funcMap)
        {
            if (nameFunc.second->callRegions.size() > 1)
            {
                for (auto &regId : nameFunc.second->callRegions)
                    if (region->GetId() == regId)
                        elems += " '" + nameFunc.first + '\'';
            }
        }

        if (elems.size())
            outText += "  COMMON FUNCTIONS:" + elems + '\n';

        set<string> arrays;
        for (auto &funcArrays : region->GetUsedCommonArrays())
            for (auto &arrayLines : funcArrays.second)
                arrays.insert(arrayLines.first->GetShortName());

        elems.clear();
        for (auto &arrayName : arrays)
            elems += " '" + arrayName + '\'';

        if (elems.size())
            outText += "  COMMON ARRAYS:" + elems + '\n';

        elems.clear();
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

                elems += "    [" + funcArrays.first->funcName + ", " + arrayLines.first->GetShortName() + ", " + toPrint + "]\n";
            }
        }

        if (elems.size())
            outText += "  LOCAL ARRAYS in [FUNC, ARRAY, [LINES]]:\n" + elems;
    }

    outText += "*** SUMMARY\n";
    
    elems.clear();
    for (auto &nameFunc : funcMap)
        if (nameFunc.second->callRegions.size() > 1)
            elems += " '" + nameFunc.first + '\'';

    if (elems.size())
        outText += "  ALL COMMON FUNCTIONS : " + elems + '\n';

    elems.clear();
    for (auto &commonArrayCommonBlock : allUsedCommonArrays)
        elems += " '" + commonArrayCommonBlock.first->GetShortName() + '\'';

    if (elems.size())
        outText += "  ALL COMMON ARRAYS:" + elems + '\n';
           
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
