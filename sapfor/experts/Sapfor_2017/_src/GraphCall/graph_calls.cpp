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
#include "../GraphLoop/graph_loops.h"
#include "../GraphLoop/graph_loops_func.h"
#include "graph_calls.h"
#include "../LoopAnalyzer/directive_parser.h"
#include "../Utils/SgUtils.h"

using std::vector;
using std::map;
using std::set;
using std::pair;
using std::tuple;
using std::string;
using std::make_pair;
using std::to_string;
using std::cout;
using std::endl;

#define DEBUG 0

//TODO: improve parameter checking 
static void correctNameIfContains(SgStatement *call, SgExpression *exCall, string &name, 
                                  const vector<SgStatement*> &containsFunctions, const string &prefix)
{
    if (containsFunctions.size() <= 0)
        return;

    if (call == NULL && exCall == NULL)
        return;

    for (auto &func : containsFunctions)
    {
        if (func->symbol()->identifier() == name)
        {
            int numPar = 0;
            if (call && call->variant() == PROC_STAT)
                numPar = isSgCallStmt(call)->numberOfArgs();
            else if (exCall && exCall->variant() == FUNC_CALL)
                numPar = isSgFunctionCallExp(exCall)->numberOfArgs();
            else
                return;

            SgProgHedrStmt *f = (SgProgHedrStmt*)func;
            //XXX
            if (f->numberOfParameters() == numPar)
                name = prefix  + name;
            break;
        }
    }
}

extern map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaratedArrays;
extern map<SgStatement*, set<tuple<int, string, string>>> declaratedArraysSt;

static void fillParam(const int i, SgSymbol *par, FuncParam *currParams, const map<string, vector<SgExpression*>> &commonBlocks)
{
    SgType *type = par->type();
    if (type)
    {
        const int varT = type->variant();
        if (isSgArrayType(type))
        {
            currParams->parametersT[i] = ARRAY_T;

            SgStatement *decl = declaratedInStmt(par);
            auto uniqKey = getUniqName(commonBlocks, decl, par);
            auto itArray = declaratedArrays.find(uniqKey);
            if (itArray == declaratedArrays.end())
            {
                __spf_print(1, "array was not in declarated list %s\n", par->identifier());
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            currParams->parameters[i] = itArray->second.first;
        }
        else
        {
            if (type->equivalentToType(SgTypeInt()))
                currParams->parametersT[i] = SCALAR_INT_T;
            else if (type->equivalentToType(SgTypeFloat()))
                currParams->parametersT[i] = SCALAR_FLOAT_T;
            else if (type->equivalentToType(SgTypeDouble()))
                currParams->parametersT[i] = SCALAR_DOUBLE_T;
            else if (type->equivalentToType(SgTypeChar()))
                currParams->parametersT[i] = SCALAR_CHAR_T;
            else if (type->equivalentToType(SgTypeBool()))
                currParams->parametersT[i] = SCALAR_BOOL_T;
            else
                currParams->parametersT[i] = UNKNOWN_T;
        }
    }
    else
        currParams->parametersT[i] = UNKNOWN_T;
}

static void fillFuncParams(FuncInfo *currInfo, const map<string, vector<SgExpression*>> &commonBlocks, SgProgHedrStmt *procHeader)
{
    int numOfParams = procHeader->numberOfParameters();

    FuncParam *currParams = &currInfo->funcParams;
    currParams->init(numOfParams);

    if (numOfParams > 0)
        for (int i = 0; i < numOfParams; ++i)
            fillParam(i, procHeader->parameter(i), currParams, commonBlocks);
}

static void fillFuncParams(FuncInfo *currInfo, const map<string, vector<SgExpression*>> &commonBlocks, SgStatement *entryHeader)
{
    SgExpression *parList = entryHeader->expr(0);
    int numOfParams = 0;
    for (SgExpression *p = parList; p; p = p->rhs())
        numOfParams++;

    FuncParam *currParams = &currInfo->funcParams;
    currParams->init(numOfParams);

    if (numOfParams > 0)
    {
        SgExpression *p = parList;
        for (int i = 0; i < numOfParams; ++i, p = p->rhs())
        {
            fillParam(i, p->lhs()->symbol(), currParams, commonBlocks);

            currInfo->funcParams.identificators.push_back(p->lhs()->symbol()->identifier());
            currInfo->isParamUsedAsIndex.push_back(false);
        }
    }
}

void createMapOfFunc(const map<string, vector<FuncInfo*>> &allFuncInfo, map<string, FuncInfo*> &mapFuncInfo)
{
    for (auto it = allFuncInfo.begin(); it != allFuncInfo.end(); ++it)
        for (int k = 0; k < it->second.size(); ++k)
            mapFuncInfo[it->second[k]->funcName] = it->second[k];
}

string removeString(const string toRemove, const string inStr)
{
    string outStr(inStr);
    const size_t found = outStr.find(toRemove);
    if (found != string::npos)
        outStr.erase(found, toRemove.length());
    return outStr;
}

//TODO:: add values
static void processActualParams(SgExpression *parList, const map<string, vector<SgExpression*>> &commonBlocks, FuncParam *currParams)
{
    int numOfPar = 0;

    for (SgExpression *ex = parList; ex != NULL; ex = ex->rhs())
        numOfPar++;

    currParams->init(numOfPar);
    if (numOfPar > 0)
    {
        int num = 0;
        for (SgExpression *ex = parList; ex != NULL; ex = ex->rhs())
        {
            if (ex->lhs()->symbol())
                fillParam(num, ex->lhs()->symbol(), currParams, commonBlocks);
            else
            {
                const int var = ex->lhs()->variant();
                if (var == INT_VAL)
                {
                    currParams->parametersT[num] = SCALAR_INT_T;
                    currParams->parameters[num] = new int[1];
#ifdef _WIN32
                    addToCollection(__LINE__, __FILE__, currParams->parameters[num], 2);
#endif
                    ((int*)currParams->parameters[num])[0] = ex->valueInteger();
                }
                else if (var == FLOAT_VAL)
                    currParams->parametersT[num] = SCALAR_FLOAT_T;
                else if (var == DOUBLE_VAL)
                    currParams->parametersT[num] = SCALAR_DOUBLE_T;
                else if (var == CHAR_VAL)
                    currParams->parametersT[num] = SCALAR_CHAR_T;
                else if (var == BOOL_VAL)
                    currParams->parametersT[num] = SCALAR_BOOL_T;
                else
                    currParams->parametersT[num] = UNKNOWN_T;

                int t = 0;
            }
            num++;
        }
    }
}

static void findFuncCalls(SgExpression *curr, vector<FuncInfo*> &entryProcs, const int line, 
                          const map<string, vector<SgExpression*>> &commonBlocks, const set<string> &macroNames,
                          const vector<SgStatement*> &containsFunctions, const string &prefix)
{
    if (curr->variant() == FUNC_CALL && macroNames.find(curr->symbol()->identifier()) == macroNames.end())
    {
        for (auto &proc : entryProcs)
        {
            string nameOfCallFunc = curr->symbol()->identifier();
            correctNameIfContains(NULL, curr, nameOfCallFunc, containsFunctions, prefix);

            proc->callsFrom.insert(nameOfCallFunc);
            proc->detailCallsFrom.push_back(make_pair(nameOfCallFunc, line));
            proc->pointerDetailCallsFrom.push_back(make_pair(curr, FUNC_CALL));
            proc->actualParams.push_back(FuncParam());
            processActualParams(curr->lhs(), commonBlocks, &proc->actualParams.back());
        }
    }

    if (curr->lhs())
        findFuncCalls(curr->lhs(), entryProcs, line, commonBlocks, macroNames, containsFunctions, prefix);
    if (curr->rhs())
        findFuncCalls(curr->rhs(), entryProcs, line, commonBlocks, macroNames, containsFunctions, prefix);
}

static void findReplaceSymbolByExpression(SgExpression *parentEx, SgExpression *findIn, int pos, 
                                      const string &symbol, SgExpression *replace,
                                      vector<tuple<SgExpression*, int, SgExpression*>> &replaces)
{
    if (findIn)
    {
        if (findIn->symbol())
            if (findIn->symbol()->identifier() == symbol)
                replaces.push_back(std::make_tuple(parentEx, pos, replace->copyPtr()));

        findReplaceSymbolByExpression(findIn, findIn->lhs(), 0, symbol, replace, replaces);
        findReplaceSymbolByExpression(findIn, findIn->rhs(), 1, symbol, replace, replaces);
    }
}

static void doMacroExpand(SgStatement *parent, SgExpression *parentEx, SgExpression *findIn, int pos,
                          const map<string, SgStatement*> &macroStats,
                          const set<string> &macroNames, bool &needToIterate,
                          vector<Messages> &messages)
{
    if (findIn)
    {
        if(findIn->variant() == FUNC_CALL && macroNames.find(string(findIn->symbol()->identifier())) != macroNames.end())
        {
            const string funcName = string(findIn->symbol()->identifier());
            auto it = macroStats.find(funcName);
            SgStatement *macroStat = it->second;

            vector<SgExpression*> parameters;
            for (SgExpression *list = findIn->lhs(); list; list = list->rhs())
                parameters.push_back(list->lhs()->copyPtr());

            SgExpression *toInsert = macroStat->expr(0)->lhs()->copyPtr();
            if (parentEx == NULL)
                parent->setExpression(pos, *toInsert);
            else
            {
                if (pos == 0)
                    parentEx->setLhs(*toInsert);
                else if (pos == 1)
                    parentEx->setRhs(*toInsert);
            }

            SgSymbol *declSymb = macroStat->expr(0)->symbol();
            int parN = lenghtOfParamList(declSymb->thesymb);

            vector<tuple<SgExpression*, int, SgExpression*>> replaces;
            for (int z = 0; z < parN; ++z)
            {
                SgSymbol *toExpand = SymbMapping(GetThParam(declSymb->thesymb, z));
                findReplaceSymbolByExpression(toInsert, toInsert->lhs(), 0, toExpand->identifier(), parameters[z], replaces);
                findReplaceSymbolByExpression(toInsert, toInsert->rhs(), 1, toExpand->identifier(), parameters[z], replaces);
            }

            for (auto &repl : replaces)
            {
                if (std::get<1>(repl) == 0)
                    std::get<0>(repl)->setLhs(std::get<2>(repl));
                else if (std::get<1>(repl) == 1)
                    std::get<0>(repl)->setRhs(std::get<2>(repl));
            }
            needToIterate = true;

            string message;
            __spf_printToBuf(message, "substitute statement function with name '%s'", funcName.c_str());
            messages.push_back(Messages(NOTE, parent->lineNumber(), message, 2006));
        }

        doMacroExpand(parent, findIn, findIn->lhs(), 0, macroStats, macroNames, needToIterate, messages);
        doMacroExpand(parent, findIn, findIn->rhs(), 1, macroStats, macroNames, needToIterate, messages);
    }
}

void doMacroExpand(SgFile *file, vector<Messages> &messages)
{
    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        map<string, SgStatement*> macroStats;
        set<string> macroNames;
        while (st != lastNode)
        {
            currProcessing.second = st;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (!isSgExecutableStatement(st))
            {
                if (st->variant() == STMTFN_STAT)
                {
                    macroStats.insert(make_pair(st->expr(0)->symbol()->identifier(), st));
                    macroNames.insert(st->expr(0)->symbol()->identifier());
                }
            }
            else
                break;
            st = st->lexNext();
        }

        if (macroStats.size() > 0)
        {
            bool needToIterate = true;
            while (needToIterate)
            {
                needToIterate = false;
                for (SgStatement *stat = st; stat != lastNode; stat = stat->lexNext())
                    for (int i = 1; i < 3; ++i)
                        if (stat->expr(i))
                            doMacroExpand(stat, NULL, stat->expr(i), i, macroStats, macroNames, needToIterate, messages);
            }
        }
    }
}

static void findIdxRef(SgExpression *exp, FuncInfo &currInfo)
{
    if (exp)
    {
        if (exp->variant() == VAR_REF)
        {
            for (int i = 0; i < currInfo.funcParams.identificators.size(); i++)
            {
                if (exp->symbol()->identifier() == currInfo.funcParams.identificators[i])
                    currInfo.isParamUsedAsIndex[i] = true;
            }
        }

        findIdxRef(exp->lhs(), currInfo);
        findIdxRef(exp->rhs(), currInfo);
    }
}

static void findArrayRef(SgExpression *exp, FuncInfo &currInfo, bool isWrite)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            DIST::Array *arrayRef = NULL;
            SgSymbol *symbS = OriginalSymbol(exp->symbol());
            const string symb = symbS->identifier();

            if (symbS)
                arrayRef = getArrayFromDeclarated(declaratedInStmt(symbS), symb);
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            if (arrayRef)
            {
                // only distributed arrays were added
                if (arrayRef->GetNonDistributeFlag() == false)
                {
                    // Through all indexes
                    for (SgExpression *ex = exp; ex != NULL; ex = ex->rhs())
                        findIdxRef(exp->lhs(), currInfo);
                }

                if (isWrite)
                    currInfo.writeToArray.insert(arrayRef);
            }
        }
        else
        {
            findArrayRef(exp->lhs(), currInfo, isWrite);
            findArrayRef(exp->rhs(), currInfo, isWrite);
        }
    }
}

static void findParamInParam(SgExpression *exp, FuncInfo &currInfo) 
{
    // Searching through expression, which parameter presented with
    if (exp)
    {
        if (exp->variant() == VAR_REF)
        {
            // check for matching with one of param of func which called this
            //cout << "Checking " << exp->symbol()->identifier() << " for match.." << endl;
            for (int i = 0; i < currInfo.funcParams.identificators.size(); i++)
            {
                const string &parName = currInfo.funcParams.identificators[i];
                //cout << "	with " << parName << ".. ";
                if (exp->symbol()->identifier() == parName)
                {
                    //cout << "Success." << endl;
                    NestedFuncCall &currNestedFuncCall = currInfo.funcsCalledFromThis.back();
                    currNestedFuncCall.NoOfParamUsedForCall.back().push_back(i);
                    break;
                }
            }
        }
        // do not search further if found, cause VAR_REF is always a leaf
        else
        {
            findParamInParam(exp->lhs(), currInfo);
            findParamInParam(exp->rhs(), currInfo);
        }
    }
}

static void findParamUsedInFuncCalls(SgExpression *exp, FuncInfo &currInfo);

static void throughParams(SgExpression *pars, FuncInfo &currInfo)
{
    for (SgExpression *par = pars; par != NULL; par = par->rhs())
    {
        // initialize vector representing parameter #parNo
        NestedFuncCall &currNestedFuncCall = currInfo.funcsCalledFromThis.back();        
        currNestedFuncCall.NoOfParamUsedForCall.push_back(vector<int>());

        findParamInParam(par->lhs(), currInfo);
    }

    // search another func call, possibly used in parameter
    for (SgExpression *par = pars; par != NULL; par = par->rhs())
        findParamUsedInFuncCalls(pars->lhs(), currInfo);    
}

// Takes random expression, finds there func calls and check their parameters 
// for using parameters of func where first is called from
static void findParamUsedInFuncCalls(SgExpression *exp, FuncInfo &currInfo)
{
    if (exp)
    {
        if (exp->variant() == FUNC_CALL)
        {
            // Add func call which we've just found            
            currInfo.funcsCalledFromThis.push_back(NestedFuncCall(exp->symbol()->identifier()));

            // For every found func call iterate through pars
            //cout << "Through params of the call of " << exp->symbol()->identifier() << endl;
            throughParams(exp->lhs(), currInfo);
        }
        else
        {
            // If we've not found func call, search further in all branches
            findParamUsedInFuncCalls(exp->rhs(), currInfo);
            findParamUsedInFuncCalls(exp->lhs(), currInfo);
        }
    }
}

void updateFuncInfo(const map<string, vector<FuncInfo*>> &allFuncInfo) // const here
{
    bool changesDone = false;
    map<string, FuncInfo*> mapFuncInfo;
    createMapOfFunc(allFuncInfo, mapFuncInfo);

    do
    {
        changesDone = false;
        for (auto &it : mapFuncInfo)
        {
            FuncInfo *currInfo = it.second;
            for(auto &funcCall : currInfo->funcsCalledFromThis)
            {
                // Find pointer to info of called function
                auto itCalledFunc = mapFuncInfo.find(funcCall.CalledFuncName);

                if (itCalledFunc != mapFuncInfo.end())
                {
                    FuncInfo *calledFunc = itCalledFunc->second;

                    // Iterate through all pars of the call
                    int parNo = 0;

                    for (auto &parOfCalled : funcCall.NoOfParamUsedForCall)
                    {
                        // If this par of called func is used as index change
                        if (calledFunc->isParamUsedAsIndex[parNo])
                        {
                            // Then pars of calling func which are used in this par of called
                            // are also used as index
                            for (auto &parOfCalling : parOfCalled)
                            {
                                if (!currInfo->isParamUsedAsIndex[parOfCalling])
                                {
                                    changesDone = true;
                                    currInfo->isParamUsedAsIndex[parOfCalling] = true;
                                }
                            }
                        }
                        parNo++;
                    }
                }
                //else // Error! No funcInfo of called func
                //     ;
            }
        }
    } while (changesDone);
}

static void printParInfo(const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    cout << "*********Which parameters of current function are used in func calls inside it*********" << endl;
    for (auto &file1 : allFuncInfo)
    {
        for (auto &currInfo : file1.second)
        {
            cout << currInfo->funcName << " calls to:" << endl;
            for (auto &calledFunc : currInfo->funcsCalledFromThis)
            {
                cout << "	" << calledFunc.CalledFuncName << " with params:" << endl;
                int parNo = 0;
                for (auto &paramOfCalled : calledFunc.NoOfParamUsedForCall) 
                {
                    cout << "		" << parNo << ": ";
                    for (auto &paramOfCalling : paramOfCalled)
                        cout << currInfo->funcParams.identificators[paramOfCalling] << " ";

                    parNo++;
                    cout << endl;
                }
            }
        }
    }

    cout << endl;

    cout << "*********Which parameters of current function are used as indices for arrays*********" << endl;
    for (auto &file1 : allFuncInfo)
    {
        for (auto &currInfo : file1.second)
        {
            cout << currInfo->funcName << endl;

            for (size_t i = 0; i < currInfo->isParamUsedAsIndex.size(); i++)
            {
                cout << currInfo->funcParams.identificators[i] << ": ";
                if (currInfo->isParamUsedAsIndex[i])
                    cout << "used" << endl;
                else
                    cout << "not used" << endl;
            }
        }
    }
    cout << endl;
}

static void findContainsFunctions(SgStatement *st, vector<SgStatement*> &found)
{
    SgStatement *end = st->lastNodeOfStmt();

    bool containsStarted = false;
    for (; st != end; st = st->lexNext())
    {
        if (containsStarted)
        {
            if (st->variant() == PROC_HEDR || st->variant() == FUNC_HEDR)
            {
                found.push_back(st);
                st = st->lastNodeOfStmt();
            }
        }

        if (st->variant() == CONTAINS_STMT)
            containsStarted = true;
    }
}

void functionAnalyzer(SgFile *file, map<string, vector<FuncInfo*>> &allFuncInfo)
{
    int funcNum = file->numberOfFunctions();
    __spf_print(DEBUG, "functions num in file = %d\n", funcNum);
    vector<SgStatement*> containsFunctions;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        string containsPrefix = getContainsPrefix(st);

        string currFunc = "";
        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
            currFunc = containsPrefix + progH->symbol()->identifier();
            __spf_print(DEBUG, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
            currFunc = containsPrefix + procH->symbol()->identifier();
            __spf_print(DEBUG, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
            currFunc = containsPrefix + funcH->symbol()->identifier();
            __spf_print(DEBUG, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        SgStatement *lastNode = st->lastNodeOfStmt();

        const string fileName = st->fileName();
        auto it = allFuncInfo.find(fileName);
        if (it == allFuncInfo.end())
            it = allFuncInfo.insert(it, make_pair(fileName, vector<FuncInfo*>()));
        
        map<string, vector<SgExpression*>> commonBlocks;
        getCommonBlocksRef(commonBlocks, st, lastNode);

        if (st->controlParent()->variant() == GLOBAL)
            containsFunctions.clear();

        findContainsFunctions(st, containsFunctions);

        FuncInfo *currInfo = new FuncInfo(currFunc, make_pair(st->lineNumber(), lastNode->lineNumber()), new Statement(st));

        for(auto &item : commonBlocks)
        {
            auto inserted = currInfo->commonBlocks.insert(make_pair(item.first, set<string>()));
            for(auto& list : item.second)
            {
                SgExpression* expr_list = list->lhs();
                while(expr_list != NULL)
                {
                    SgExpression* var = expr_list->lhs();
                    expr_list = expr_list->rhs();
                    inserted.first->second.insert(var->symbol()->identifier());
                }
            }
        }

        if (st->variant() != PROG_HEDR) 
        {
            SgProgHedrStmt *procFuncHedr = ((SgProgHedrStmt*)st);

            fillFuncParams(currInfo, commonBlocks, procFuncHedr);
            
            // Fill in names of function parameters
            for (int i = 0; i < procFuncHedr->numberOfParameters(); ++i)
            {
                currInfo->funcParams.identificators.push_back((procFuncHedr->parameter(i))->identifier());
                currInfo->isParamUsedAsIndex.push_back(false);
            }
        }

        if (isSPF_NoInline(st->lexNext()))
        {
            __spf_print(1, "set NOINLINE attribute for function '%s'\n", currFunc.c_str());
            currInfo->doNotInline = true;
        }

        it->second.push_back(currInfo);

        vector<FuncInfo*> entryProcs;
        entryProcs.push_back(currInfo);

        vector<SgStatement*> macroStats;
        set<string> macroNames;
        while (st != lastNode)
        {
            currProcessing.second = st;
            if (st->variant() == CONTAINS_STMT)
                break;

            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (!isSgExecutableStatement(st))
            {
                if (st->variant() == STMTFN_STAT)
                {
                    macroStats.push_back(st);
                    macroNames.insert(st->expr(0)->symbol()->identifier());
                }
            }
            else
                break;
            st = st->lexNext();
        }


        st = file->functions(i);
        while (st != lastNode)
        {
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            const string prefix = containsPrefix == "" ? currFunc + "." : containsPrefix;
            //printf("var %d, line %d\n", st->variant(), st->lineNumber());
            if (st->variant() == PROC_STAT)
            {
                string pureNameOfCallFunc = removeString("call", st->symbol()->identifier());
                correctNameIfContains(st, NULL, pureNameOfCallFunc, containsFunctions, prefix);

                for (auto &proc : entryProcs)
                {                    
                    proc->callsFrom.insert(pureNameOfCallFunc);
                    proc->detailCallsFrom.push_back(make_pair(pureNameOfCallFunc, st->lineNumber()));
                    proc->pointerDetailCallsFrom.push_back(make_pair(st, PROC_STAT));
                    proc->actualParams.push_back(FuncParam());
                    processActualParams(st->expr(0), commonBlocks, &proc->actualParams.back());

                    // Add func call which we've just found
                    NestedFuncCall funcCall(st->symbol()->identifier());
                    proc->funcsCalledFromThis.push_back(funcCall);

                    // search for using pars of cur func in pars of called
                    throughParams(st->expr(0), *proc);
                }
            }
            else
            {
                for (auto &proc : entryProcs)
                    for (int i = 0; i < 3; ++i)
                        if (st->expr(i))
                            findParamUsedInFuncCalls(st->expr(i), *proc);
            }

            for (int i = 0; i < 3; ++i)
                if (st->expr(i))
                    findFuncCalls(st->expr(i), entryProcs, st->lineNumber(), commonBlocks, macroNames, containsFunctions, prefix);

            if (st->variant() == ENTRY_STAT)
            {
                string entryName = st->symbol()->identifier();
                FuncInfo *entryInfo = new FuncInfo(entryName, make_pair(st->lineNumber(), lastNode->lineNumber()), new Statement(st));
                fillFuncParams(entryInfo, commonBlocks, st);

                if (isSPF_NoInline(st->lexNext()))
                {
                    __spf_print(1, "set NOINLINE attribute for function '%s'\n", entryName.c_str());
                    entryInfo->doNotInline = true;
                }
                it->second.push_back(entryInfo);
                entryProcs.push_back(entryInfo);
            }

            if (isSgExecutableStatement(st))
                for (auto &proc : entryProcs)
                    if (proc->isParamUsedAsIndex.size())
                        for (int i = 0; i < 3; i++)
                            findArrayRef(st->expr(i), *proc, st->variant() == ASSIGN_STAT && i == 0);

            st = st->lexNext();
        }
    }
}

int CreateCallGraphViz(const char *fileName, const map<string, vector<FuncInfo*>> &funcByFile, set<string> &V, vector<string> &E)
{
    string graph = "";
    graph += "digraph G{\n";

    auto it = funcByFile.begin();
    int fileNum = 0;
    set<string> inCluster;
    set<string> unknownCluster;

    char buf[1024];
    while (it != funcByFile.end())
    {
        sprintf(buf, "subgraph cluster%d {\n", fileNum);
        graph += buf;

        const int dimSize = (int)it->second.size();
        set<string> uniqNames;
        for (int k = 0; k < dimSize; ++k)
        {
            const string currfunc = it->second[k]->funcName;
            auto it = uniqNames.find(currfunc);
            if (it == uniqNames.end())
            {
                uniqNames.insert(it, currfunc);
                inCluster.insert(currfunc);
                sprintf(buf, "\"%s\"\n", currfunc.c_str());
                graph += buf;
            }
        }
        sprintf(buf, "label = \"file <%s>\"\n", removeString(".\\", it->first).c_str());
        graph += buf;
        graph += "}\n";

        fileNum++;
        it++;
    }

    it = funcByFile.begin();
    while (it != funcByFile.end())
    {
        const char *formatString = "\"%s\" -> \"%s\" [minlen=2.0];\n";
        const int dimSize = (int)it->second.size();
        for (int k = 0; k < dimSize; ++k)
        {
            const string &callFrom = it->second[k]->funcName;
            for (auto &i : it->second[k]->callsFrom)
            {
                sprintf(buf, formatString, callFrom.c_str(), i.c_str());
                graph += buf;

                if (inCluster.find(callFrom) == inCluster.end())
                    unknownCluster.insert(callFrom);
                if (inCluster.find(i) == inCluster.end())
                    unknownCluster.insert(i);
                                
                V.insert(i);
                V.insert(callFrom);

                E.push_back(callFrom);
                E.push_back(i);                
            }
        }
        it++;
    }

    if (unknownCluster.size() > 0)
    {
        sprintf(buf, "subgraph cluster%d {\n", fileNum);
        graph += buf;

        for (auto &func : unknownCluster)
        {
            sprintf(buf, "\"%s\"\n", func.c_str());
            graph += buf;
        }
        sprintf(buf, "label = \"file <UNKNOWN>\"\n");
        graph += buf;
        graph += "}\n";
    }

    graph += "overlap=false\n";
    graph += "}\n";
    
    if (fileName)
    {
        FILE *out = fopen(fileName, "w");
        if (out == NULL)
        {
            __spf_print(1, "can not open file %s\n", fileName);
            return -1;
        }

        fprintf(out, graph.c_str());
        fclose(out);
    }
    return 0;
}

static bool findLoopVarInParameter(SgExpression *ex, const string &loopSymb)
{
    bool retVal = false;

    if (ex)
    {
        if (ex->variant() == VAR_REF)
        {
            const string ident(ex->symbol()->identifier());
            if (ident == loopSymb)
                retVal = true;
        }

        if (ex->lhs())
            retVal = retVal || findLoopVarInParameter(ex->lhs(), loopSymb);
        if (ex->rhs())
            retVal = retVal || findLoopVarInParameter(ex->rhs(), loopSymb);
    }
    return retVal;
}

static int countList(SgExpression *list)
{
    int num = 0;
    while (list)
    {
        num++;
        list = list->rhs();
    }
    return num;
}

static bool matchCallAndDefinition(SgExpression *callParam, int numFileForCall, const int line, FuncInfo *def, SgProject *proj, const map<string, int> &files, 
                                   vector<Messages> &messages, bool needToAddErrors)
{
    bool result = true;

    int countInCall = countList(callParam);
    int countInDef = -1;
    int numFileForDef = files.find(def->funcName)->second;

    proj->file(numFileForDef);
    SgExpression *defParam = def->funcPointer->expr(0);
    countInDef = countList(defParam);

    if (countInCall != countInDef)
    {
        char buf[256];
        sprintf(buf, "Function '%s' needs to be inlined due to count of call parameters are not enouth", def->funcName.c_str());

        if (needToAddErrors)
        {
            messages.push_back(Messages(NOTE, line, buf, 1013));
            __spf_print(1, "Function '%s' needs to be inlined due to count of call parameters are not enouth\n", def->funcName.c_str());
        }
        result = false;
    }
    else
    {
        for (int i = 0; i < countInCall; ++i)
        {
            proj->file(numFileForCall);
            SgExpression *parCall = callParam->lhs();
            if (parCall->variant() != ARRAY_REF)
            {
                SgType *callType = parCall->type();

                proj->file(numFileForDef);
                if (callType->equivalentToType(defParam->type()) == false)
                {
                    char buf[256];
                    sprintf(buf, "Function '%s' needs to be inlined due to different type of call and def parameter %d", def->funcName.c_str(), i);

                    if (needToAddErrors)
                    {
                        messages.push_back(Messages(NOTE, line, buf, 1013));
                        __spf_print(1, "Function '%s' needs to be inlined due to different type of call and def parameter %d\n", def->funcName.c_str(), i);
                    }
                    result = false;
                }
            }
            else
            {
                SgArrayRefExp *callArrayRef = isSgArrayRefExp(parCall);
                if (callArrayRef == NULL)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                if (callArrayRef->numberOfSubscripts() > 0)
                {
                    char buf[256];
                    sprintf(buf, "Function '%s' needs to be inlined, only full array passing was supported", def->funcName.c_str());

                    if (needToAddErrors)
                    {
                        messages.push_back(Messages(NOTE, line, buf, 1013));
                        __spf_print(1, "Function '%s' needs to be inlined, only full array passing was supported\n", def->funcName.c_str());
                    }
                    result = false;
                }
            }

            callParam = callParam->rhs();
            defParam = defParam->rhs();
        }
    }

    return result;
}

bool isPassFullArray(SgExpression *ex)
{
    if (ex->lhs() == NULL && ex->rhs() == NULL)
        return true;
    else
        return false;
}

static bool checkParameter(SgExpression *ex, vector<Messages> &messages, const int statLine, SgForStmt *loop, bool needToAddErrors, const FuncInfo *func)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            SgArrayRefExp *arrayRef = isSgArrayRefExp(ex);
            if (arrayRef)
            {
                SgSymbol *symb = OriginalSymbol(arrayRef->symbol());
                if (symb)
                {
                    SgStatement *decl = declaratedInStmt(symb);
                    set<string> privatesVars;
                    tryToFindPrivateInAttributes(decl, privatesVars);
                    fillNonDistrArraysAsPrivate(decl, declaratedArrays, declaratedArraysSt, privatesVars);

                    if (privatesVars.find(symb->identifier()) == privatesVars.end())
                    {
                        if (!isPassFullArray(ex))
                        {
                            if (needToAddErrors)
                            {
                                char buf[256];
                                sprintf(buf, "Function '%s' needs to be inlined due to non private array reference '%s' under loop on line %d",
                                        func->funcName.c_str(), symb->identifier(), loop->lineNumber());

                                messages.push_back(Messages(ERROR, statLine, buf, 1013));
                                __spf_print(1, "Function '%s' needs to be inlined due to non private array reference '%s' under loop on line %d\n",
                                      func->funcName.c_str(), symb->identifier(), loop->lineNumber());
                            }
                            ret = true;
                        }
                    }
                }
            }
        }

        if (ex->lhs())
            ret = ret || checkParameter(ex->lhs(), messages, statLine, loop, needToAddErrors, func);
        if (ex->rhs())
            ret = ret || checkParameter(ex->rhs(), messages, statLine, loop, needToAddErrors, func);
    }

    return ret;
}

static vector<int> findNoOfParWithLoopVar(SgExpression *pars, const string &loopSymb) 
{
    vector<int> parsWithLoopSymb;

    int parNo = 0;
    for (SgExpression *par = pars; par != NULL; par = par->rhs(), parNo++)
    {
        if (findLoopVarInParameter(par, loopSymb))
            parsWithLoopSymb.push_back(parNo);
    }

    return parsWithLoopSymb;
}

static bool processParameterList(SgExpression *parList, SgForStmt *loop, const FuncInfo *func, const int funcOnLine, bool needToAddErrors,
                                 vector<Messages> &messages)
{
    bool needInsert = false;

    bool hasLoopVar = findLoopVarInParameter(parList, loop->symbol()->identifier());
    if (hasLoopVar)
    {
        const vector<int> parsWithLoopSymb = findNoOfParWithLoopVar(parList, loop->symbol()->identifier());
        bool isLoopSymbUsedAsIndex = false;

        int idx = 1;
        for (auto &par : parsWithLoopSymb)
        {
            if (func->isParamUsedAsIndex[par])
            {
                isLoopSymbUsedAsIndex = true;
                break;
            }
            ++idx;
        }

        if (isLoopSymbUsedAsIndex)
        {
            char buf[256];
            sprintf(buf, "Function '%s' needs to be inlined due to use of loop on line %d symbol as index of an array, in parameter num %d", 
                          func->funcName.c_str(), loop->lineNumber(), idx);
            if (needToAddErrors)
            {
                messages.push_back(Messages(ERROR, funcOnLine, buf, 1013));
                __spf_print(1, "Function '%s' needs to be inlined due to use of loop on line %d symbol as index of an array, in parameter num %d\n", 
                                func->funcName.c_str(), loop->lineNumber(), idx);
            }

            needInsert = true;
        }
    }
    else
    {
        while (parList)
        {
            needInsert = needInsert || checkParameter(parList->lhs(), messages, funcOnLine, loop, needToAddErrors, func);
            parList = parList->rhs();
        }
    }

    return needInsert;
}

static bool findFuncCall(SgExpression *ex, const FuncInfo *func, vector<Messages> &messages, const int statLine, SgForStmt *loop, bool needToAddErrors)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
            if (ex->symbol()->identifier() == func->funcName)
                ret = ret || processParameterList(ex->lhs(), loop, func, statLine, needToAddErrors, messages);

        ret = ret || findFuncCall(ex->lhs(), func, messages, statLine, loop, needToAddErrors);
        ret = ret || findFuncCall(ex->rhs(), func, messages, statLine, loop, needToAddErrors);
    }

    return ret;
}

static SgStatement* getStatByLine(string file, const int line, const map<string, map<int, SgStatement*>> &statByLine)
{
    auto itF = statByLine.find(file);
    if (itF == statByLine.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    auto itS = itF->second.find(line);
    if (itS == itF->second.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return itS->second;
}

static void findInsertedFuncLoopGraph(const vector<LoopGraph*> &childs, set<string> &needToInsert, SgFile *currF, 
                                      vector<Messages> &messages, bool needToAddErrors, const map<string, FuncInfo*> &funcByName,
                                      const map<string, map<int, SgStatement*>> &statByLine)
{
    for (int k = 0; k < (int)childs.size(); ++k)
    {
        SgForStmt *loop = isSgForStmt(getStatByLine(currF->filename(), childs[k]->lineNum, statByLine));
        if (loop == NULL)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (loop->lineNumber() != childs[k]->lineNum)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        // TODO: find loop variable in common block or module

        //dont check loop outside of parallel region
        if (childs[k]->region)
        {
            for (int i = 0; i < (int)childs[k]->calls.size(); ++i)
            {
                //dont check call with !$SPF NOINLINE
                bool needToCheck = true;
                const string &funcName = childs[k]->calls[i].first;
                auto it = funcByName.find(funcName);
                if (it != funcByName.end())
                    needToCheck = !(it->second->doNotInline == true);
                else // function not found
                    needToCheck = false;

                if (!needToCheck)
                    continue;

                int funcOnLine = childs[k]->calls[i].second;
                SgStatement *func = getStatByLine(currF->filename(), funcOnLine, statByLine);

                bool needInsert = false;
                const int var = func->variant();
                if (var == PROC_STAT || var == FUNC_STAT)
                    needInsert = needInsert || processParameterList(func->expr(0), loop, it->second, funcOnLine, needToAddErrors, messages);
                else
                    for (int z = 0; z < 3; ++z)
                        needInsert = needInsert || findFuncCall(func->expr(z), it->second, messages, funcOnLine, loop, needToAddErrors);

                if (needInsert)
                    needToInsert.insert(childs[k]->calls[i].first);
            }
        }
        findInsertedFuncLoopGraph(childs[k]->childs, needToInsert, currF, messages, needToAddErrors, funcByName, statByLine);
    }
}

static void findInsertedFuncLoopGraph(const map<string, vector<LoopGraph*>> &loopGraph, set<string> &needToInsert,
                                      SgProject *proj, const map<string, int> &files, map<string, vector<Messages>> &allMessages,
                                      bool needToAddErrors, const map<string, FuncInfo*> &funcByName,
                                      const map<string, map<int, SgStatement*>> &statByLine)
{
    for (auto it = loopGraph.begin(); it != loopGraph.end(); it++)
    {
        const int fileN = files.find(it->first)->second;
        SgFile *currF = &(proj->file(fileN));

        auto itM = allMessages.find(it->first);
        if (itM == allMessages.end())
            itM = allMessages.insert(itM, make_pair(it->first, vector<Messages>()));
        findInsertedFuncLoopGraph(it->second, needToInsert, currF, itM->second, needToAddErrors, funcByName, statByLine);
    }
}

int CheckFunctionsToInline(SgProject *proj, const map<string, int> &files, const char *fileName, map<string, vector<FuncInfo*>> &funcByFile, 
                            const map<string, vector<LoopGraph*>> &loopGraph, map<string, vector<Messages>> &allMessages, bool needToAddErrors)
{
    map<string, map<int, SgStatement*>> statByLine; //file -> map    
    //build info
    for (int i = 0; i < proj->numberOfFiles(); ++i)
    {
        map<int, SgStatement*> toAdd;
        SgFile *file = &(proj->file(i));
        SgStatement *st = file->firstStatement();
        string currF = file->filename();
        while (st)
        {
            if (st->lineNumber() != 0 && st->fileName() == currF)
                toAdd[st->lineNumber()] = st;
            st = st->lexNext();
        }

        statByLine[file->filename()] = toAdd;
    }

    map<string, FuncInfo*> funcByName;
    for (auto it = funcByFile.begin(); it != funcByFile.end(); ++it)
    {
        for (int k = 0; k < it->second.size(); ++k)
        {
            string name = it->second[k]->funcName;
            auto itF = funcByName.find(name);
            if (itF == funcByName.end())
                funcByName.insert(itF, make_pair(name, it->second[k]));
            else
            {
                __spf_print(1, "can not find func with name = '%s'\n", name.c_str());
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }
    }

    set<string> needToInsert;
    findInsertedFuncLoopGraph(loopGraph, needToInsert, proj, files, allMessages, needToAddErrors, funcByName, statByLine);

    if (needToInsert.size() > 0)
    {
        for (auto it = needToInsert.begin(); it != needToInsert.end(); ++it)
        {
            auto itF = funcByName.find(*it);
            if (itF != funcByName.end())
                itF->second->needToInline = true;
        }
    }

    if (fileName)
    {
        FILE *out = fopen(fileName, "w");
        if (out == NULL)
        {
            __spf_print(1, "can not open file %s\n", fileName);
            throw - 1;
        }

        fprintf(out, "digraph G{\n");

        auto it = funcByFile.begin();
        set<string> noInline;

        int fileNum = 0;
        while (it != funcByFile.end())
        {
            fprintf(out, "subgraph cluster%d {\n", fileNum);
            const int dimSize = (int)it->second.size();
            set<string> uniqNames;
            for (int k = 0; k < dimSize; ++k)
            {
                const string currfunc = it->second[k]->funcName;
                if (it->second[k]->doNotInline)
                    noInline.insert(currfunc);

                set<string>::iterator it = uniqNames.find(currfunc);
                if (it == uniqNames.end())
                {
                    uniqNames.insert(it, currfunc);
                    fprintf(out, "\"%s\"\n", currfunc.c_str());
                }
            }
            fprintf(out, "label = \"file <%s>\"\n", removeString(".\\", it->first).c_str());
            fprintf(out, "}\n");

            fileNum++;
            it++;
        }

        it = funcByFile.begin();
        while (it != funcByFile.end())
        {
            const char *formatString = "\"%s\" -> \"%s\" [minlen=2.0];\n";
            const int dimSize = (int)it->second.size();
            for (int k = 0; k < dimSize; ++k)
            {
                const string callFrom = it->second[k]->funcName;
                set<string>::const_iterator i = it->second[k]->callsFrom.begin();
                for (; i != it->second[k]->callsFrom.end(); i++)
                    fprintf(out, formatString, callFrom.c_str(), i->c_str());
            }
            it++;
        }

        auto it_set = needToInsert.begin();
        for (; it_set != needToInsert.end(); it_set++)
        {
            if (noInline.find(*it_set) == noInline.end())
                fprintf(out, "\"%s\" [color=red]\n", it_set->c_str());
        }
        fprintf(out, "overlap=false\n");
        fprintf(out, "}\n");
        fclose(out);
    }

    return needToInsert.size();
}

extern map<string, vector<FuncInfo*>> allFuncInfo; // file -> Info  
FuncInfo* isUserFunctionInProject(const string &func)
{
    FuncInfo *ret = NULL;
    for (auto &it : allFuncInfo)
    {
        for (auto &currF : it.second)
        {
            if (currF->funcName == func)
            {
                ret = currF;
                break;
            }
        }

        if (ret)
            break;
    }
    return ret;
}

string convertToString(const FuncInfo *currFunc)
{
    string result = "";
    if (currFunc)
    {
        result += "|" + currFunc->funcName + "|" + to_string(currFunc->linesNum.first) +
               " " + to_string(currFunc->detailCallsFrom.size()) +
               " " + to_string(currFunc->needToInline) + " " + to_string(currFunc->doNotInline) + " " + to_string(currFunc->doNotAnalyze);

        for (int i = 0; i < currFunc->detailCallsFrom.size(); ++i)
            result += "|" + currFunc->detailCallsFrom[i].first + "|" + to_string(currFunc->detailCallsFrom[i].second);
    }
    return result;
}

static string printChainRec(const vector<FuncInfo*> &currentChainCalls)
{
    string out = "";
    for (int i = 0; i < currentChainCalls.size(); ++i)
    {
        out += currentChainCalls[i]->funcName;
        if (i != currentChainCalls.size() - 1)
            out += " -> ";
    }
    return out;
}

static bool hasRecursionChain(vector<FuncInfo*> currentChainCalls, const FuncInfo *current,
                              const map<string, FuncInfo*> &allFuncinfo, vector<Messages> &messagesForFile)
{
    bool retVal = false;

    vector<FuncInfo*> toCallNext;
    for (auto it = current->callsFrom.begin(); it != current->callsFrom.end(); ++it)
    {
        auto itF = allFuncinfo.find(*it);
        if (itF == allFuncinfo.end())
            continue;

        if (std::find(currentChainCalls.begin(), currentChainCalls.end(), itF->second) != currentChainCalls.end())
        {
            if (itF->second == currentChainCalls[0])
            {
                retVal = true;

                currentChainCalls.push_back(itF->second);
                const string &chain = printChainRec(currentChainCalls);
                __spf_print(1, "For function on line %d found recursive chain calls: %s\n", currentChainCalls[0]->linesNum.first, chain.c_str());

                char buf[512];
                sprintf(buf, "Found recursive chain calls: %s, this function will be ignored", chain.c_str());
                messagesForFile.push_back(Messages(ERROR, currentChainCalls[0]->linesNum.first, buf, 1014));
                break;
            }
        }
        else
            toCallNext.push_back(itF->second);
    }

    if (!retVal)
    {
        for (int i = 0; i < toCallNext.size() && !retVal; ++i)
        {
            currentChainCalls.push_back(toCallNext[i]);
            retVal = retVal || hasRecursionChain(currentChainCalls, toCallNext[i], allFuncinfo, messagesForFile);
            currentChainCalls.pop_back();
        }
    }

    return retVal;
}

void checkForRecursion(SgFile *file, map<string, vector<FuncInfo*>> &allFuncInfo, vector<Messages> &messagesForFile)
{
    auto itCurrFuncs = allFuncInfo.find(file->filename());
    if (itCurrFuncs == allFuncInfo.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    map<string, FuncInfo*> mapFuncInfo;
    createMapOfFunc(allFuncInfo, mapFuncInfo);

    for (int i = 0; i < itCurrFuncs->second.size(); ++i)
    {
        __spf_print(1, "run for func %s\n", itCurrFuncs->second[i]->funcName.c_str());
        if (hasRecursionChain( { itCurrFuncs->second[i] }, itCurrFuncs->second[i], mapFuncInfo, messagesForFile))
            itCurrFuncs->second[i]->doNotAnalyze = true;
    }
}

// Find dead functions and fill callTo information
void findDeadFunctionsAndFillCallTo(map<string, vector<FuncInfo*>> &allFuncInfo, map<string, vector<Messages>> &allMessages)
{
    map<string, FuncInfo*> mapFuncInfo;
    createMapOfFunc(allFuncInfo, mapFuncInfo);

    set<string> allChildCalls;
    for (auto &it : mapFuncInfo)
    {
        FuncInfo *currInfo = it.second;
        allChildCalls.insert(currInfo->callsFrom.begin(), currInfo->callsFrom.end());
    }

    for (auto &it : mapFuncInfo)
    {
        FuncInfo *currInfo = it.second;
        if (allChildCalls.find(it.first) == allChildCalls.end())
            if (currInfo->funcPointer->variant() != PROG_HEDR)
                currInfo->deadFunction = currInfo->doNotAnalyze = true;
    }

    for (auto &it : allFuncInfo)
    {
        const string &currF = it.first;
        auto itM = allMessages.find(currF);
        if (itM == allMessages.end())
            itM = allMessages.insert(itM, make_pair(currF, vector<Messages>()));

        for (auto &func : it.second)
            if (func->deadFunction)
                itM->second.push_back(Messages(NOTE, func->linesNum.first, "This function is not called in current project", 1015));
    }

    for (auto &it : mapFuncInfo)
    {
        FuncInfo *currInfo = it.second;
        for (auto &k : currInfo->callsFrom)
        {
            auto itFound = mapFuncInfo.find(k);
            if (itFound != mapFuncInfo.end())
            {
                FuncInfo *callFrom = itFound->second;
                callFrom->callsTo.push_back(currInfo);
            }
        }
    }
}

static inline void addLinks(const FuncParam &actual, const FuncParam &formal, map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    if (actual.parameters.size() != formal.parameters.size())
        return;
    else
    {
        for (int i = 0; i < actual.parameters.size(); ++i)
            if (actual.parametersT[i] == formal.parametersT[i] && formal.parametersT[i] == ARRAY_T)
                arrayLinksByFuncCalls[(DIST::Array*)formal.parameters[i]].insert((DIST::Array*)actual.parameters[i]);
    }
}

static bool propagateUp(DIST::Array *from, set<DIST::Array*> to, DIST::distFlag flag, bool &change)
{
    bool globalChange = false;
    if (from->GetNonDistributeFlagVal() == flag)
    {
        for (auto &realRef : to)
        {
            auto val = realRef->GetNonDistributeFlagVal();            
            if (val != flag)
            {
                //exclude this case
                if (flag == DIST::IO_PRIV && val == DIST::SPF_PRIV)
                    ;
                else
                {
                    realRef->SetNonDistributeFlag(flag);
                    //printf("up: set %d %s\n", flag, realRef->GetName().c_str());
                    change = true;
                    globalChange = true;
                }
            }
        }
    }

    return globalChange;
}

static bool propagateFlag(bool isDown, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    bool globalChange = false;
    bool change = true;
    while (change)
    {
        change = false;
        for (auto &array : declaratedArrays)
        {
            set<DIST::Array*> realArrayRefs;
            getRealArrayRefs(array.second.first, array.second.first, realArrayRefs, arrayLinksByFuncCalls);

            bool allNonDistr = true;
            bool allDistr = true;
            bool nonDistrSpfPriv = false;
            bool nonDistrIOPriv = false;
            bool init = false;

            // propagate SPF to down calls
            for (auto &realRef : realArrayRefs)
            {
                if (realRef != array.second.first)
                {
                    bool nonDistr = realRef->GetNonDistributeFlag();
                    if (realRef->GetNonDistributeFlagVal() == DIST::SPF_PRIV)
                        nonDistrSpfPriv = true;
                    else if (realRef->GetNonDistributeFlagVal() == DIST::IO_PRIV)
                        nonDistrIOPriv = true;

                    allNonDistr = allNonDistr && nonDistr;
                    allDistr = allDistr && !nonDistr;
                    init = true;
                }
            }

            if (init)
            {
                if (allNonDistr && array.second.first->GetNonDistributeFlag() == false)
                {
                    if (isDown)
                    {
                        if (nonDistrSpfPriv)
                        {
                            array.second.first->SetNonDistributeFlag(DIST::SPF_PRIV);
                            //printf("down: set %d %s\n", DIST::SPF_PRIV, array.second.first->GetName().c_str());
                        }
                        else if (nonDistrIOPriv)
                        {
                            array.second.first->SetNonDistributeFlag(DIST::IO_PRIV);
                            //printf("down: set %d %s\n", DIST::IO_PRIV, array.second.first->GetName().c_str());
                        }
                        else
                        {
                            array.second.first->SetNonDistributeFlag(DIST::NO_DISTR);
                            //printf("down: set %d %s\n", DIST::NO_DISTR, array.second.first->GetName().c_str());
                        }
                        change = true;
                        globalChange = true;
                    }
                }
                else
                {
                    if (!isDown)
                    {
                        bool ret = propagateUp(array.second.first, realArrayRefs, DIST::SPF_PRIV, change);
                        globalChange = globalChange || ret;
                        ret = propagateUp(array.second.first, realArrayRefs, DIST::IO_PRIV, change);
                        globalChange = globalChange || ret;
                        //propagateUp(array.second.first, realArrayRefs, DIST::NO_DISTR, change);
                    }
                }
            }
        }
    }

    return globalChange;
}

void createLinksBetweenFormalAndActualParams(map<string, vector<FuncInfo*>> &allFuncInfo, map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                             const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays)
{
    for (auto &funcsOnFile : allFuncInfo)
    {
        for (auto &func : funcsOnFile.second)
        {
            const string &name = func->funcName;
            for (auto &caller : func->callsTo)
                for (int i = 0; i < caller->detailCallsFrom.size(); ++i)
                    if (caller->detailCallsFrom[i].first == name)
                        addLinks(caller->actualParams[i], func->funcParams, arrayLinksByFuncCalls);
        }
    }

    bool change = true;
    while (change)
    {
        bool changeD = propagateFlag(true, arrayLinksByFuncCalls);
        bool changeU = propagateFlag(false, arrayLinksByFuncCalls);

        change = changeD || changeU;
    }

    //propagate distr state
    change = true;
    while (change)
    {
        change = false;
        for (auto &array : declaratedArrays)
        {
            set<DIST::Array*> realArrayRefs;
            getRealArrayRefs(array.second.first, array.second.first, realArrayRefs, arrayLinksByFuncCalls);

            if (realArrayRefs.size() && (*realArrayRefs.begin()) != array.second.first &&
                !(*realArrayRefs.begin())->GetNonDistributeFlag() && array.second.first->GetNonDistributeFlag())
            {
                array.second.first->SetNonDistributeFlag(DIST::DISTR);
                change = true;
            }
        }
    }
}

void propagateWritesToArrays(map<string, vector<FuncInfo*>> &allFuncInfo)
{

}

#undef DEBUG
