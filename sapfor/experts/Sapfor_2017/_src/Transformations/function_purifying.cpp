#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <map>
#include <vector>
#include <set>
#include <string>

#include "dvm.h"
#include "../GraphCall/graph_calls_func.h"
#include "../Utils/SgUtils.h"
#include "../Utils/CommonBlock.h"
#include "../Utils/DefUseList.h"
#include "ExpressionTransform/expr_transform.h"
#include "../VerificationCode/verifications.h"
#include "../DvmhRegions/DvmhRegionInserter.h"
#include "function_purifying.h"

using std::vector;
using std::map;
using std::set;
using std::pair;
using std::tuple;
using std::string;
using std::wstring;
using std::make_pair;
using std::to_string;

static bool checkOutCalls(const set<string>& outCalls)
{
    for (auto& elem : outCalls)
        if (isIntrinsicFunctionName(elem.c_str()) == 0)
            return true;

    return false;
}

static void setPureStatus(FuncInfo* func)
{
    if (func->isPure && !func->isMain)
    {
        SgStatement* header = func->funcPointer->GetOriginal();
        if (header->switchToFile() == false)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        bool isFunc = (header->variant() == FUNC_HEDR);
        bool hasOut = false;
        for (int z = 0; z < func->funcParams.countOfPars; ++z)
            hasOut |= func->funcParams.isArgOut(z);
        bool hasPure = (header->expr(2) != NULL) || ((header->symbol()->attributes() & PURE_BIT) != 0);
        bool hasOutCalls = checkOutCalls(func->callsFrom);
        bool hasIO = func->linesOfIO.size() || func->linesOfStop.size();

        //TODO: with hasOutCalls 
        if (!hasPure && !hasIO && !hasOutCalls && ((isFunc == false) || (isFunc && hasOut == false)))
        {
            DvmhRegionInserter::createInterfaceBlockForOutCalls(func);
            header->setExpression(2, new SgExpression(PURE_OP));
            header->symbol()->setAttribute(header->symbol()->attributes() | PURE_BIT);
        }
    }
}

void setPureStatus(const map<string, vector<FuncInfo*>>& allFuncInfo)
{
    for (auto& funcByFile : allFuncInfo)
        for (auto& func : funcByFile.second)
            setPureStatus(func);
}

static void insertIntents(vector<string> identificators, SgStatement* header, map <string, SgSymbol*> parSym, int intentVariant, int intentBit)
{ 
    SgStatement* last = header->lastNodeOfStmt();
    SgStatement* lastDecl = header;
    for (auto stmt = header->lexNext(); stmt && stmt != last; stmt = stmt->lexNext())
    {
        if (stmt->variant() == CONTAINS_STMT)
            break;

        if (isSgExecutableStatement(stmt))
            break;

        lastDecl = stmt;
        if (stmt->variant() == VAR_DECL_90) 
        {
            SgVarDeclStmt* s = (SgVarDeclStmt*)stmt;
            for (int i = 0; i < s->numberOfAttributes(); i++) 
            {
                if (s->attribute(i)->variant() == intentVariant)
                {
                    for (int i = 0; i < s->numberOfVars(); i++) 
                    {
                        for (auto it = identificators.begin(); it != identificators.end(); it++) 
                        {
                            if (*it == s->var(i)->symbol()->identifier()) 
                            {
                                identificators.erase(it);
                                break;
                            }
                        }
                    }
                }
            }
        }
        else if (stmt->variant() == INTENT_STMT) 
        {
            SgIntentStmt* s = (SgIntentStmt*)stmt;
            if (s->attribute()->variant() == intentVariant) 
            {
                for (int i = 0; i < s->numberOfVars(); i++) 
                {
                    for (auto it = identificators.begin(); it != identificators.end(); it++) 
                    {
                        if (*it == s->var(i)->symbol()->identifier()) 
                        {
                            identificators.erase(it);
                            break;
                        }
                    }
                }
            }
        }
    }

    if (identificators.size() > 0) 
    {
        SgExpression* attr = new SgExpression(intentVariant);
        SgExpression* args = NULL;
        for (auto& par : identificators) 
        {
            SgExprListExp* tempArgs = new SgExprListExp();
            SgVarRefExp* tempPar = new SgVarRefExp(parSym[par]);
            tempArgs->setLhs(tempPar);
            if (args)
                tempArgs->setRhs(args);
            args = tempArgs;
            parSym[par]->setAttribute(parSym[par]->attributes() | intentBit);
        }

        if (args)
        {
            SgIntentStmt* intent = new SgIntentStmt(*args, *attr);
            lastDecl->insertStmtAfter(*intent, (header == lastDecl) ? *header : *lastDecl->controlParent());
        }
    }
}

void intentInsert(FuncInfo* func)
{
    if (func->isMain)
        return;

    vector <string> InIdentificators;
    vector <string> OutIdentificators;
    vector <string> InOutIdentificators;

    for (int i = 0; i < func->funcParams.countOfPars; i++)
    {
        if (func->funcParams.isArgInOut(i))
            InOutIdentificators.push_back(func->funcParams.identificators[i]);
        else if (func->funcParams.isArgIn(i))
            InIdentificators.push_back(func->funcParams.identificators[i]);
        else if (func->funcParams.isArgOut(i))
            OutIdentificators.push_back(func->funcParams.identificators[i]);
    }

    SgStatement* headerSt = func->funcPointer->GetOriginal();
    SgProgHedrStmt* header = (SgProgHedrStmt*)headerSt;
    map <string, SgSymbol*> parSym;
    for (int i = 0; i < header->numberOfParameters(); i++)
        parSym[header->parameter(i)->identifier()] = header->parameter(i);

    insertIntents(InOutIdentificators, headerSt, parSym, INOUT_OP, INOUT_BIT);
    insertIntents(InIdentificators, headerSt, parSym, IN_OP, IN_BIT);
    insertIntents(OutIdentificators, headerSt, parSym, OUT_OP, OUT_BIT);        
}

void intentInsert(const vector<FuncInfo*>& allFuncInfo) 
{
    for (auto& func: allFuncInfo) 
        intentInsert(func);
}

//DEBUG
/*static void printcvu(map<string, vector<int>>& commonVarsUsed)
{
    for (auto& common : commonVarsUsed)
    {
        printf(">%s\n", common.first.c_str());
        for (int posVar : common.second)
            printf("\t%d\n", posVar);
    }
}*/

static void collectForChange(map<string, vector<FuncInfo*>> funcsName, set<FuncInfo*>& allForChange, FuncInfo* start)
{
    allForChange.insert(start);
    for (auto& call : start->pointerDetailCallsFrom)
    {
        bool found = false;
        if (call.second == FUNC_CALL)
        {
            SgFunctionCallExp* callExp = (SgFunctionCallExp*)call.first;
            for (auto& func : funcsName[callExp->funName()->identifier()])
            {
                for (auto& callTo : func->callsTo)
                {
                    if (callTo == start)
                    {
                        collectForChange(funcsName, allForChange, func);
                        found = true;
                    }
                    if (found)
                        break;
                }
                if (found)
                    break;
            }
        }
        else
        {
            SgCallStmt* callSt = (SgCallStmt*)call.first;
            for (auto& func : funcsName[callSt->name()->identifier()])
            {
                for (auto& callTo : func->callsTo)
                {
                    if (callTo == start)
                    {
                        collectForChange(funcsName, allForChange, func);
                        found = true;
                    }
                    if (found)
                        break;
                }

                if (found)
                    break;
            }
        }
    }
}

template<typename CallExp>
static void transferVarToArg(const map<string, vector<int>>& commonVarsUsed, const map<string, CommonBlock>& commonBlocks, 
                             const FuncInfo* curFunc, CallExp* callExp)
{
    for (auto& common : commonVarsUsed)
    {
        for (auto& posVar : common.second)
        {
            Variable var = commonBlocks.find(common.first)->second.getGroupedVars().find(posVar)->second[0];
            string name = "";
            if (curFunc->isMain && curFunc->commonBlocks.count(common.first) > 0)
            {
                for (auto& v : commonBlocks.find(common.first)->second.getVariables(curFunc->fileName, curFunc->funcName))
                {
                    if (v->getPosition() == posVar)
                    {
                        name = v->getName();
                        break;
                    }
                }
            }
            else if ((int)(string(var.getName()).find("c_" + common.first + "_")) < 0)
                name = "c_" + common.first + "_" + var.getName();
            else
                name = var.getName();
            SgSymbol* s = new SgSymbol(var.getSymbol()->variant(), name.c_str());
            callExp->addArg(*new SgVarRefExp(*s));
        }
    }
}

void transferCommons(set<FuncInfo*>& allForChange, map <FuncInfo*, map<string, vector<int>>>& funcCommons, map<string, vector<int>>& commonVarsUsed,
                     FuncInfo* curFunc, FuncInfo* precFunc, const map<string, CommonBlock>& commonBlocks, map <FuncInfo*, set<string>>& funcCommonDeclared)
{
    if (commonVarsUsed.empty())
        return;

    if (funcCommons.count(curFunc) == 0)
        funcCommons[curFunc] = map<string, vector<int>>();

    //add params to calls
    if (curFunc != precFunc)
    {
        if (SgFile::switchToFile(curFunc->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& call : curFunc->pointerDetailCallsFrom)
        {
            if (isSgFuncHedrStmt(precFunc->funcPointer->GetOriginal()) && call.second == FUNC_CALL)
            {
                SgFunctionCallExp* callExp = (SgFunctionCallExp*)call.first;
                if (callExp->funName()->identifier() == precFunc->funcName)
                    transferVarToArg(commonVarsUsed, commonBlocks, curFunc, callExp);                
            }
            else if (isSgProcHedrStmt(precFunc->funcPointer->GetOriginal()) && call.second == PROC_STAT)
            {
                SgCallStmt* callSt = (SgCallStmt*)call.first;
                if (callSt->name()->identifier() == precFunc->funcName)
                    transferVarToArg(commonVarsUsed, commonBlocks, curFunc, callSt);
            }
        }
    }

    map<string, vector<int>> nextCommonVarsUsed;
    //find the things we have already done
    for (auto& common : commonVarsUsed)
    {
        if (funcCommons[curFunc].count(common.first) == 0)
            funcCommons[curFunc][common.first] = vector<int>();

        for (auto& var : common.second)
        {
            bool done = false;
            for (auto& v : funcCommons[curFunc][common.first])
                if (v == var)
                    done = true;

            if (!done) 
            {
                funcCommons[curFunc][common.first].push_back(var);
                if (nextCommonVarsUsed.count(common.first) == 0)
                    nextCommonVarsUsed[common.first] = vector<int>();
                nextCommonVarsUsed[common.first].push_back(var);
            }
        }
    }

    for (auto& common : nextCommonVarsUsed)
    {
        bool uses = false;
        map<int, vector <Variable>> groupedVars = commonBlocks.find(common.first)->second.getGroupedVars();
        
        if (curFunc->commonBlocks.count(common.first) > 0) //rename common vars in funcs
        {
            uses = true;
            const vector<const Variable*>& vars = commonBlocks.find(common.first)->second.getVariables(curFunc->fileName, curFunc->funcName);
            if (allForChange.count(curFunc))
            {
                for (auto& var : vars)
                {
                    bool contains = false;
                    for (auto& v : common.second)
                        if (v == var->getPosition())
                            contains = true;

                    if (contains)
                    {
                        for (auto& varUse : var->getAllUse())
                        {
                            if (varUse.getFileName() == curFunc->fileName && varUse.getFunctionName() == curFunc->funcName)
                            {
                                string name;
                                if ((int)(string(groupedVars[var->getPosition()][0].getName()).find("c_" + common.first + "_")) < 0)
                                    name = "c_" + common.first + "_" + groupedVars[var->getPosition()][0].getName();
                                else
                                    name = groupedVars[var->getPosition()][0].getName();
                                varUse.getUseS()->changeName(name.c_str());
                                break;
                            }
                        }
                    }
                }
            }
        }        
        else if (!allForChange.count(curFunc)) //add of commons to main
        {
            SgExprListExp* res = NULL;
            vector <SgSymbol*> varsToDeclare = vector <SgSymbol*>();
            for (auto it = groupedVars.rbegin(); it != groupedVars.rend(); it++)
            {
                string name;
                if ((int)(string(it->second[0].getName()).find("c_" + common.first + "_")) < 0)
                    name = "c_" + common.first + "_" + it->second[0].getName();
                else
                    name = it->second[0].getName();

                SgType* st = it->second[0].getSymbol()->type();
                SgSymbol* s = new SgSymbol(it->second[0].getSymbol()->variant(), name.c_str(), it->second[0].getSymbol()->type(), curFunc->funcPointer);
                SgVarRefExp* vr = new SgVarRefExp(s);
                SgExprListExp* el = new SgExprListExp();
                el->setLhs(vr);
                el->setRhs(res);
                res = el;
                varsToDeclare.push_back(s);
            }

            SgSymbol* commSymb = new SgSymbol(VARIABLE_NAME, common.first.c_str());
            SgExprListExp* commList = new SgExprListExp(COMM_LIST);
            SgStatement* commStat = new SgStatement(COMM_STAT);
            commStat->setExpression(0, *commList);
            commList->setSymbol(commSymb);
            commList->setLhs(res);

            auto lastDecl = curFunc->funcPointer->GetOriginal()->lastDeclaration();
            lastDecl->insertStmtAfter(*commStat, *(lastDecl->controlParent()));

            for (auto& var : varsToDeclare)
            {
                vector<SgSymbol*> varVec = vector<SgSymbol*>();
                varVec.push_back(var);
                SgStatement* decl = makeDeclaration(NULL, varVec);
                for (int i = 0; i < 3; i++)
                {
                    SgExpression* e;
                    if (e = decl->expr(i))
                        decl->setExpression(i, CalculateInteger(ReplaceConstant(e)));
                }
                SgStatement* lastDecl = curFunc->funcPointer->GetOriginal()->lastDeclaration()->lexNext();
                decl->setlineNumber(lastDecl->lineNumber());
                decl->setFileName(lastDecl->fileName());
                lastDecl->insertStmtBefore(*decl, *(curFunc->funcPointer->GetOriginal()->lastDeclaration()->controlParent()));
            }
        }

        //parametrs add
        if (allForChange.count(curFunc))
        {
            for (auto& posVar : common.second)
            {
                Variable var = commonBlocks.find(common.first)->second.getGroupedVars().find(posVar)->second[0];
                string name;
                if ((int)(string(var.getSymbol()->identifier()).find("c_" + common.first + "_")) < 0)
                    name = "c_" + common.first + "_" + var.getSymbol()->identifier();
                else
                    name = var.getSymbol()->identifier();

                SgSymbol* s = new SgSymbol(var.getSymbol()->variant(), name.c_str(), var.getSymbol()->type(), curFunc->funcPointer);
                
                SgStatement* hedr = curFunc->funcPointer->GetOriginal();
                SgExpression* result = hedr->expr(0) == NULL ? NULL : hedr->expr(0)->copyPtr();

                if (isSgFuncHedrStmt(hedr))
                    isSgFuncHedrStmt(hedr)->AddArg(*new SgVarRefExp(s));
                else if (isSgProcHedrStmt(hedr))
                    isSgProcHedrStmt(hedr)->AddArg(*new SgVarRefExp(s));
                else
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                if (result == NULL)
                {
                    if (hedr->expr(0) != NULL)
                        hedr->setExpression(0, NULL);
                }
                else
                {
                    if (hedr->expr(0) != NULL)
                        hedr->setExpression(0, result);
                    else if (string(hedr->expr(0)->unparse()) != result->unparse())
                        hedr->setExpression(0, result);
                }

                curFunc->funcPointer->GetOriginal()->lexNext()->deleteStmt();
                if (!funcCommonDeclared[curFunc].count(common.first))
                {
                    vector<SgSymbol*> varVec = vector<SgSymbol*>();
                    varVec.push_back(s);
                    SgStatement* decl = makeDeclaration(NULL, varVec);
                    for (int i = 0; i < 3; i++)
                    {
                        SgExpression* e;
                        if (e = decl->expr(i))
                            decl->setExpression(i, CalculateInteger(ReplaceConstant(e)));
                    }

                    SgStatement* lastDecl = curFunc->funcPointer->GetOriginal()->lastDeclaration()->lexNext();
                    decl->setlineNumber(lastDecl->lineNumber());
                    decl->setFileName(lastDecl->fileName());
                    lastDecl->insertStmtBefore(*decl, *(curFunc->funcPointer->GetOriginal()->lastDeclaration()->controlParent()));
                }
            }
        }
    }

    for (auto& callFunc : curFunc->callsTo)
        transferCommons(allForChange, funcCommons, nextCommonVarsUsed, callFunc, curFunc, commonBlocks, funcCommonDeclared);    
}

static void fillUsedVars(set<string>& usedVars, SgExpression* exp)
{
    if (exp)
    {
        if (exp->variant() == VAR_REF || exp->variant() == ARRAY_REF)
            usedVars.insert(exp->symbol()->identifier());
        fillUsedVars(usedVars, exp->lhs());
        fillUsedVars(usedVars, exp->rhs());
    }
}

void commonTransfer(const map<string, vector<FuncInfo*>>& allFuncInfo, const map<string, CommonBlock>& commonBlocks)
{
    map <FuncInfo*, map<string, vector<int>>> funcCommons;
    map <FuncInfo*, set<string>> funcCommonDeclared;
    FuncInfo* start = NULL;
    set<FuncInfo*> allForChange;
    map<string, vector<FuncInfo*>> funcsName;
    for (auto& byfile : allFuncInfo)
    {
        if (SgFile::switchToFile(byfile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& func : byfile.second)
        {
            SgStatement* st = func->funcPointer->GetOriginal();
            if (st->variant() < 0 || func->isInterface)
                continue;

            if (func->commonBlocks.size() > 0 && st->variant() != PROG_HEDR)
            {
                for (SgStatement* start = st, *end = st->lastNodeOfStmt(); start != end;) 
                {
                    if (start->variant() == CONTAINS_STMT)
                        break;

                    SgStatement* next = start->lexNext();
                    if (start->variant() == COMM_STAT && string(start->fileName()) == func->fileName) 
                    {
                        if (funcCommonDeclared.count(func) == 0)
                            funcCommonDeclared[func] = set<string>();

                        for (SgExpression* e = start->expr(0); e; e = e->rhs())
                            funcCommonDeclared[func].insert(e->symbol() ? e->symbol()->identifier() : "spf_unnamed");
                        start->deleteStmt();
                    }
                    start = next;
                }
            }

            if (func->isMain)
                start = func;

            if (!funcsName.count(func->funcName))
                funcsName[func->funcName] = vector<FuncInfo*>();

            if (!func->isInterface)
                funcsName[func->funcName].push_back(func);
        }
    }

    checkNull(start, convertFileName(__FILE__).c_str(), __LINE__);
    collectForChange(funcsName, allForChange, start);
    allForChange.erase(start);

    for (auto& func : allForChange)
    {
        if (SgFile::switchToFile(func->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        SgStatement* st = func->funcPointer->GetOriginal();
        if (st->variant() < 0 || st->variant() == PROG_HEDR || func->isInterface)
            continue;

        if (func->commonBlocks.size() > 0) 
        {
            //printf(">%s\n", func->funcName.c_str());
            map<string, vector<int>> commonVarsUsed;
            set<string> usedVars;
            for (SgStatement* start = st->lastDeclaration()->lexNext(), *end = st->lastNodeOfStmt(); start != end; start = start->lexNext()) 
            {
                if (start->variant() == CONTAINS_STMT)
                    break;

                if (isSgExecutableStatement(start))
                    for (int i = 0; i < 3; i++)
                        fillUsedVars(usedVars, start->expr(i));
            }

            for (auto& var : usedVars)
            {
                for (auto& common : func->commonBlocks)
                {
                    const string name = common.first;
                    if (common.second.count(var) > 0)
                    {
                        if (commonVarsUsed.count(common.first) == 0)
                            commonVarsUsed[name] = vector<int>();
                        for (auto& cvar : commonBlocks.find(name)->second.getVariables(func->fileName, func->funcName))
                            if (cvar->getName() == var)
                                commonVarsUsed[name].push_back(cvar->getPosition());
                    }
                }
            }
            transferCommons(allForChange, funcCommons, commonVarsUsed, func, func, commonBlocks, funcCommonDeclared);
        }
    }
}

static string changeData(const string data, const map<string, string>& constSymVars, const map<string, string>& locVars)
{
    int curChar = 0;
    string ident = "";
    string res = "";
    while (curChar < data.length())
    {
        switch (data[curChar])
        {
        case ' ':
        case ',':
        case ')':
        case '(':
        case '=':
        case '*':
        case '/':
        case '\n':
        case '\t':
            if (ident.size() > 0)
            {
                if (constSymVars.count(ident) > 0)
                    res += constSymVars.at(ident);
                else if (locVars.count(ident) > 0)
                    res += locVars.at(ident);
                else
                    res += ident;
                ident = "";
            }
            res += tolower(data[curChar]);
            curChar++;
            break;
        default:
            ident += tolower(data[curChar]);
            curChar++;
            break;
        }
    }
    return res;
}

static void transferSave(map<FuncInfo*, set<FuncInfo*>>& funcAddedVarsFuncs, vector <SgSymbol*>& varsToTransfer, vector <string>& dataToTransfer, 
                         FuncInfo* curFunc, FuncInfo* precFunc, FuncInfo* startFunc)
{
    if (curFunc != precFunc)
    {
        if (SgFile::switchToFile(curFunc->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        for (auto& call : curFunc->pointerDetailCallsFrom)
        {
            if (isSgFuncHedrStmt(precFunc->funcPointer->GetOriginal()) && call.second == FUNC_CALL)
            {
                SgFunctionCallExp* callExp = (SgFunctionCallExp*)call.first;
                if (callExp->funName()->identifier() == precFunc->funcName)
                    for (auto& var : varsToTransfer)
                        callExp->addArg(*new SgVarRefExp(*var));
            }
            else if (isSgProcHedrStmt(precFunc->funcPointer->GetOriginal()) && call.second == PROC_STAT)
            {
                SgCallStmt* callSt = (SgCallStmt*)call.first;
                if (callSt->name()->identifier() == precFunc->funcName)                
                    for (auto& var : varsToTransfer)
                        callSt->addArg(*new SgVarRefExp(*var));
            }
        }
    }

    if (!funcAddedVarsFuncs.count(curFunc))
        funcAddedVarsFuncs[curFunc] = set<FuncInfo*>();
    else if (funcAddedVarsFuncs[curFunc].count(startFunc))
        return;

    funcAddedVarsFuncs[curFunc].insert(startFunc);
    if (!curFunc->isMain)
    {
        SgStatement* st = curFunc->funcPointer->GetOriginal();
        for (auto& var : varsToTransfer)
        {
            ((SgProcHedrStmt*)(st))->AddArg(*new SgVarRefExp(var->copy()));
            st->lexNext()->deleteStmt();
            if (curFunc != startFunc)
            {
                vector<SgSymbol*> varVec = vector<SgSymbol*>();
                varVec.push_back(var);
                SgStatement* decl = makeDeclaration(NULL, varVec);
                for (int i = 0; i < 3; i++)
                {
                    SgExpression* e;
                    if (e = decl->expr(i))
                        decl->setExpression(i, CalculateInteger(ReplaceConstant(e)));
                }
                SgStatement* lastDecl = st->lastDeclaration()->lexNext();
                decl->setlineNumber(lastDecl->lineNumber());
                decl->setFileName(lastDecl->fileName());
                lastDecl->insertStmtBefore(*decl, *(curFunc->funcPointer->GetOriginal()->lastDeclaration()->controlParent()));
            }
        }

        for (auto& callFunc : curFunc->callsTo)
            transferSave(funcAddedVarsFuncs, varsToTransfer, dataToTransfer, callFunc, curFunc, startFunc);
    }
    else
    {
        SgStatement* lastDecl = curFunc->funcPointer->GetOriginal()->lastDeclaration()->lexNext();
        for (auto& var : varsToTransfer)
        {
            vector<SgSymbol*> varVec = vector<SgSymbol*>();
            varVec.push_back(var);
            SgStatement* decl = makeDeclaration(NULL, varVec);
            for (int i = 0; i < 3; i++)
            {
                SgExpression* e;
                if (e = decl->expr(i))
                    decl->setExpression(i, CalculateInteger(ReplaceConstant(e)));
            }

            decl->setlineNumber(lastDecl->lineNumber() - 1);
            decl->setFileName(lastDecl->fileName());
            lastDecl->insertStmtBefore(*decl, *(lastDecl->controlParent()));
        }

        for (auto& data : dataToTransfer)
            lastDecl->addComment(data.c_str());
    }
}

void saveTransfer(const map<string, vector<FuncInfo*>>& allFuncInfo)
{
    FuncInfo* start;
    set<FuncInfo*> allForChange;
    map<string, vector<FuncInfo*>> funcsName;
    map<FuncInfo*, set<FuncInfo*>> funcAddedVarsFuncs;

    for (auto& byfile : allFuncInfo)
    {
        for (auto& func : byfile.second)
        {
            if (func->isMain)
                start = func;
            if (!funcsName.count(func->funcName))
                funcsName[func->funcName] = vector<FuncInfo*>();
            if (!func->isInterface)
                funcsName[func->funcName].push_back(func);
        }
    }

    collectForChange(funcsName, allForChange, start);
    allForChange.erase(start);
    for (auto& func : allForChange)
    {
        if (SgFile::switchToFile(func->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        SgStatement* st = func->funcPointer->GetOriginal();
        vector <SgSymbol*> varsToTransfer;
        vector <string> dataToTransfer;
        map<SgSymbol*, SgExpression*> varInit;
        map<string, string> constSymVars;
        map <string, string> locVars;
        set <string> params;
        bool hasComplType = false;
        SgStatement* lst = st->lastNodeOfStmt();
        SgSymbol* s, * sl;
        bool allSave = false;

        for (SgStatement* start = st, *end = lst; start != end; start = start->lexNext())
        {
            if (start->variant() == CONTAINS_STMT)
                break;

            if (start->variant() == SAVE_DECL && !start->expr(0))
                allSave = true;
        }

        for (auto& s : func->funcParams.identificators)
            params.insert(s);

        sl = lst->lexNext() ? lst->lexNext()->symbol() : NULL;
        for (s = st->symbol(); s != sl && s != NULL; s = s->next())
        {
            SgConstantSymb* sc = isSgConstantSymb(s);
            if (sc && sc->constantValue())
                constSymVars[string(s->identifier())] = string(sc->constantValue()->unparse());

            if (s->scope() == st)
            {
                if (s->attributes() & SAVE_BIT || s->attributes() & DATA_BIT || allSave && s->variant() == VARIABLE_NAME && !params.count(s->identifier()))
                {
                    if ((s->type() ? s->type()->variant() : (T_COMPLEX + 1)) > T_COMPLEX)
                    {
                        hasComplType = true;
                        break;
                    }
                    string newName = "s_" + func->funcName + "_" + s->identifier();
                    locVars[s->identifier()] = newName;
                    s->changeName(newName.c_str());
                    varsToTransfer.push_back(s);
                }
            }
        }

        if (hasComplType)
            continue;

        for (SgStatement* start = st, *end = lst; start != end;)
        {
            SgStatement* next = start->lexNext();
            if (strcmp(start->fileName(), st->fileName()))
            {
                start = next;
                continue;
            }

            if (start->variant() == DATA_DECL)
            {
                dataToTransfer.push_back(changeData(start->sunparse(), constSymVars, locVars));
                start->deleteStmt();
            }
            else if (start->variant() == SAVE_DECL)
                start->deleteStmt();
            else if (start->variant() == VAR_DECL || start->variant() == VAR_DECL_90)
            {
                SgVarDeclStmt* vst = (SgVarDeclStmt*)start;
                for (int i = 0; i < vst->numberOfVars(); i++)
                {
                    if (vst->initialValue(i))
                    {
                        string data = "      data " + vst->var(i)->lhs()->sunparse() + " / " + vst->initialValue(i)->sunparse() + " / \n";
                        dataToTransfer.push_back(changeData(data, constSymVars, locVars));
                        vst->clearInitialValue(i);
                    }
                }

                SgExprListExp* attrsNoSave = new SgExprListExp();
                for (int i = 0; i < vst->numberOfAttributes(); i++)
                    if (vst->attribute(i)->variant() != SAVE_OP)
                        attrsNoSave->append(vst->attribute(i)->copy());

                if (!attrsNoSave->length())
                {
                    SgVarDeclStmt* newVst = new SgVarDeclStmt(vst->varList()->copy(), *attrsNoSave, vst->type()->copy());
                    vst->replaceWithStmt(*newVst);
                }
                else
                {
                    SgVarDeclStmt* newVst = new SgVarDeclStmt(vst->varList()->copy(), vst->type()->copy());
                    vst->replaceWithStmt(*newVst);
                }
            }
            start = next;
        }

        if (varsToTransfer.size())
            transferSave(funcAddedVarsFuncs, varsToTransfer, dataToTransfer, func, func, func);
    }
}

//DEBUG
/*static void printmbu(map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUse)
{
    for (auto& mod : modByUse)
    {
        printf("|%s| \n", mod.first.c_str());
        for (auto& var : mod.second)
            printf("\t%s => %s\n", var.first->identifier(), var.second->identifier());
    }
}*/

static string makeName(SgSymbol* var, map<SgSymbol*, set< SgSymbol*>>& modVarsToAdd, set<string>& useMod, 
                       map<string, vector<pair<SgSymbol*, SgSymbol*>>>& modByUse, 
                       map<string, vector<pair<SgSymbol*, SgSymbol*>>>& modByUseOnly)
{
    string name = "", modName = OriginalSymbol(var)->scope()->symbol()->identifier();
    SgSymbol* modS = OriginalSymbol(var)->scope()->symbol();
    string varOrName = OriginalSymbol(var)->identifier();
    size_t um = useMod.count(modName), mbu = modByUse.count(modName), mbuo = modByUseOnly.count(modName);

    if (um && !mbu && !mbuo)
        name = varOrName;
    else if (mbu)
    {
        for (auto& elem : modByUse[modName])
        {
            if ((elem.second ? elem.second : elem.first)->identifier() == varOrName)
            {
                name = elem.first->identifier();
                break;
            }
        }

        if (!name.length())
            name = varOrName;        
    }
    else if (mbuo)
    {
        for (auto& elem : modByUseOnly[modName])
        {
            if ((elem.second ? elem.second : elem.first)->identifier() == varOrName)
            {
                name = elem.first->identifier();
                break;
            }
        }

        if (!name.length())
        {
            name = "m_" + modName + "_" + varOrName;
            if (!modVarsToAdd.count(modS))
                modVarsToAdd[modS] = set < SgSymbol*>();
            modVarsToAdd[modS].insert(OriginalSymbol(var));
        }
    }
    else
    {
        name = "m_" + modName + "_" + varOrName;
        if (!modVarsToAdd.count(modS))
            modVarsToAdd[modS] = set < SgSymbol*>();
        modVarsToAdd[modS].insert(OriginalSymbol(var));
    }
    return name;
}


static void transferModule(map<FuncInfo*, set<SgSymbol*>>& funcAddedVarsMods, set<FuncInfo*>& allForChange, 
                           vector<SgSymbol*>& varsToTransfer, FuncInfo* curFunc, FuncInfo* precFunc)
{
    SgStatement* st = curFunc->funcPointer->GetOriginal();
    map<SgSymbol*, set< SgSymbol*>> modVarsToAdd;
    if (curFunc != precFunc)
    {
        if (SgFile::switchToFile(curFunc->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        set<string> useMod;
        map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUse;
        map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUseOnly;

        if (!allForChange.count(curFunc))
        {
            for (SgStatement* start = st; start != st->lastNodeOfStmt(); start = start->lexNext())
            {
                if (isSgExecutableStatement(start))
                    break;
                if (start->variant() == CONTAINS_STMT)
                    break;
                if (start != st && (start->variant() == PROC_HEDR || start->variant() == FUNC_HEDR))
                    break;
                fillUseStatement(start, useMod, modByUse, modByUseOnly);
            }
        }

        for (auto& call : curFunc->pointerDetailCallsFrom)
        {
            if (isSgFuncHedrStmt(precFunc->funcPointer->GetOriginal()) && call.second == FUNC_CALL)
            {
                SgFunctionCallExp* callExp = (SgFunctionCallExp*)call.first;
                if (callExp->funName()->identifier() == precFunc->funcName)
                {
                    for (auto& var : varsToTransfer)
                    {
                        if (allForChange.count(curFunc))
                            callExp->addArg(*new SgVarRefExp(*var));
                        else
                        {
                            string name = makeName(var, modVarsToAdd, useMod, modByUse, modByUseOnly);
                            SgSymbol* s = new SgSymbol(VARIABLE_NAME, name.c_str());
                            callExp->addArg(*new SgVarRefExp(*s));
                        }
                    }
                }
            }
            else if (isSgProcHedrStmt(precFunc->funcPointer->GetOriginal()) && call.second == PROC_STAT)
            {
                SgCallStmt* callSt = (SgCallStmt*)call.first;
                if (callSt->name()->identifier() == precFunc->funcName) 
                {
                    for (auto& var : varsToTransfer)
                    {
                        if (allForChange.count(curFunc))
                            callSt->addArg(*new SgVarRefExp(*var));
                        else
                        {
                            string name = makeName(var, modVarsToAdd, useMod, modByUse, modByUseOnly);
                            SgSymbol* s = new SgSymbol(VARIABLE_NAME, name.c_str());
                            callSt->addArg(*new SgVarRefExp(*s));
                        }
                    }
                }
            }
        }
    }

    map<SgSymbol*, set< SgSymbol*>> modVarsNeedToAdd;
    vector <SgSymbol*> nextVarsToTransfer;
    if (!funcAddedVarsMods.count(curFunc))
        funcAddedVarsMods[curFunc] = set<SgSymbol*>();

    for (auto& var : varsToTransfer)
    {
        if (!funcAddedVarsMods[curFunc].count(OriginalSymbol(var)))
        {
            SgSymbol* modS = OriginalSymbol(var)->scope()->symbol();
            if (modVarsToAdd.count(modS) && modVarsToAdd[modS].count(OriginalSymbol(var)))
            {
                if (!modVarsNeedToAdd.count(modS))
                    modVarsNeedToAdd[modS] = set< SgSymbol*>();
                modVarsNeedToAdd[modS].insert(OriginalSymbol(var));
            }
            nextVarsToTransfer.push_back(var);
            funcAddedVarsMods[curFunc].insert(OriginalSymbol(var));
        }
    }

    if (allForChange.count(curFunc))
    {
        for (auto& var : nextVarsToTransfer)
        {
            ((SgProcHedrStmt*)(st))->AddArg(*new SgVarRefExp(var->copy()));
            st->lexNext()->deleteStmt();
            vector<SgSymbol*> varVec = vector<SgSymbol*>();
            varVec.push_back(var);
            SgStatement* decl = makeDeclaration(NULL, varVec);

            /*TODO:: add some other*/
            if (var->attributes() && ALLOCATABLE_BIT)
            {
                SgAttributeExp* a = new SgAttributeExp(ALLOCATABLE_OP);
                SgExprListExp* l = new SgExprListExp();
                l->setLhs(a);
                ((SgVarDeclStmt*)decl)->addAttributeExpression(a);
            }

            for (int i = 0; i < 3; i++)
            {
                SgExpression* e;
                if (e = decl->expr(i))
                {
                    decl->setExpression(i, CalculateInteger(ReplaceConstant(e)));
                }
            }

            SgStatement* lastDecl = st->lastDeclaration()->lexNext();
            decl->setlineNumber(lastDecl->lineNumber() - 1);
            decl->setFileName(lastDecl->fileName());
            lastDecl->insertStmtBefore(*decl, *st);
        }

        for (auto& callFunc : curFunc->callsTo)
            transferModule(funcAddedVarsMods, allForChange, nextVarsToTransfer, callFunc, curFunc);
    }
    else
    {
        for (auto& mod : modVarsNeedToAdd)
        {
            SgSymbol modS = mod.first->copy();
            SgExpression* onlyE = new SgExpression(ONLY_NODE);
            SgExprListExp* renameL = NULL;
            for (auto& var : mod.second)
            {
                string name = "m_" + string(modS.identifier()) + "_" + var->identifier();
                SgSymbol varS = SgSymbol(VARIABLE_NAME, name.c_str());
                SgExprListExp* el = new SgExprListExp();
                SgVarRefExp* nvr = new SgVarRefExp(varS), * vr = new SgVarRefExp(var);
                SgExpression* renameE = new SgExpression(RENAME_NODE, nvr, vr);
                el->setLhs(renameE);
                el->setRhs(renameL);
                renameL = el;
            }
            onlyE->setLhs(renameL);
            SgStatement* useSt = new SgStatement(USE_STMT);
            useSt->setSymbol(modS);
            useSt->setExpression(0, onlyE);
            st->insertStmtAfter(*useSt, *st);
        }
    }
}

static void fillUsedVars(set<SgSymbol*>& usedVars, SgExpression* exp)
{
    if (exp)
    {
        if (exp->variant() == VAR_REF || exp->variant() == ARRAY_REF)
            usedVars.insert(exp->symbol());
        fillUsedVars(usedVars, exp->lhs());
        fillUsedVars(usedVars, exp->rhs());
    }
}

void moduleTransfer(const map<string, vector<FuncInfo*>>& allFuncInfo)
{
    FuncInfo* start;
    set<FuncInfo*> allForChange;
    map<string, vector<FuncInfo*>> funcsName;
    map<FuncInfo*, set<SgSymbol*>> funcAddedVarsMods;
    for (auto& byfile : allFuncInfo)
    {
        for (auto& func : byfile.second)
        {
            if (func->isMain)
                start = func;
            if (!funcsName.count(func->funcName))
                funcsName[func->funcName] = vector<FuncInfo*>();
            if (!func->isInterface)
                funcsName[func->funcName].push_back(func);
        }
    }

    collectForChange(funcsName, allForChange, start);
    allForChange.erase(start);
    for (auto& func : allForChange)
    {
        if (SgFile::switchToFile(func->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        SgStatement* st = func->funcPointer->GetOriginal();
        vector <SgSymbol*> varsToTransfer;
        map <string, string> locVars;
        SgStatement* lst = st->lastNodeOfStmt();
        SgSymbol* s, * sl;
        bool allSave = false;
        set< SgSymbol*> usedVars;

        for (SgStatement* start = st->lexNext(), *end = st->lastNodeOfStmt(); start != end;)
        {
            if (start->variant() == CONTAINS_STMT)
                break;

            SgStatement* next = start->lexNext();
            if (isSgExecutableStatement(start))
                for (int i = 0; i < 3; i++)
                    fillUsedVars(usedVars, start->expr(i));
            
            if (start->variant() == IMPL_DECL)
                start->deleteStmt();
            start = next;
        }

        sl = lst->lexNext() ? lst->lexNext()->symbol() : NULL;
        for (s = st->symbol(); s != sl && s != NULL; s = s->next())
        {
            if (OriginalSymbol(s)->scope()->variant() == MODULE_STMT && s->variant() == VARIABLE_NAME && usedVars.count(s))
            {
                string newName = "m_" + string(OriginalSymbol(s)->scope()->symbol()->identifier()) + "_" + OriginalSymbol(s)->identifier();
                locVars[s->identifier()] = newName;
                s->changeName(newName.c_str());
                varsToTransfer.push_back(s);
            }
        }
        transferModule(funcAddedVarsMods, allForChange, varsToTransfer, func, func);
    }
}
