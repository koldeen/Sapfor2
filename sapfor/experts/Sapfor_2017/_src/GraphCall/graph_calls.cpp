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
#include "../GraphLoop/graph_loops_func.h"
#include "graph_calls_func.h"
#include "../LoopAnalyzer/directive_parser.h"
#include "../Utils/SgUtils.h"
#include "../ParallelizationRegions/ParRegions_func.h"
#include "../DynamicAnalysis/gCov_parser_func.h"
#include "acc_analyzer.h"

using std::vector;
using std::map;
using std::set;
using std::pair;
using std::tuple;
using std::string;
using std::wstring;
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
                name = prefix + name;
            break;
        }
    }
}

extern map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaratedArrays;
extern map<SgStatement*, set<tuple<int, string, string>>> declaratedArraysSt;

static void fillParam(const int i, SgSymbol *parIn, FuncParam *currParams, const map<string, vector<SgExpression*>> &commonBlocks)
{
    SgSymbol *par = OriginalSymbol(parIn);
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
            else if (type->equivalentToType(new SgType(T_COMPLEX)))
                currParams->parametersT[i] = SCALAR_CMPLX_FLOAT_T;
            else if (type->equivalentToType(new SgType(T_DCOMPLEX)))
                currParams->parametersT[i] = SCALAR_CMPLX_DOUBLE_T;
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

            wstring message;            
            __spf_printToLongBuf(message, L"substitute statement function with name '%s'", to_wstring(funcName).c_str());
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
            currProcessing.second = st->lineNumber();
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
                    currInfo.allUsedArrays.insert(arrayRef);
                }
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

static void fillIn(FuncInfo *currF, SgExpression *ex, const map<string, int> &parNames)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF || ex->variant() == ARRAY_REF)
        {
            const char *name = ex->symbol()->identifier();
            if (name && name != string(""))
            {
                auto it = parNames.find(name);
                if (it != parNames.end())
                    currF->funcParams.inout_types[it->second] |= IN_BIT;
            }
        }

        fillIn(currF, ex->lhs(), parNames);
        fillIn(currF, ex->rhs(), parNames);
    }
}

static void fillInOut(FuncInfo *currF, SgStatement *start, SgStatement *last)
{
    if (currF->funcParams.countOfPars == 0)
        return;

    map<string, int> parNames;

    for (int i = 0; i < currF->funcParams.identificators.size(); ++i)
        parNames[currF->funcParams.identificators[i]] = i;

    for (auto st = start; st != last; st = st->lexNext())
    {
        if (st->variant() == CONTAINS_STMT)
            break;

        if (isSgExecutableStatement(st) == NULL)
            continue;

        if (st->variant() == ASSIGN_STAT)
        {
            SgExpression *left = st->expr(0);

            fillIn(currF, left->lhs(), parNames);
            fillIn(currF, left->rhs(), parNames);
            fillIn(currF, st->expr(1), parNames);
            
            if (left->symbol())
            {
                auto it = parNames.find(left->symbol()->identifier());
                if (it != parNames.end())
                    currF->funcParams.inout_types[it->second] |= OUT_BIT;
            }
        }
        else if (st->variant() == READ_STAT) // TODO
        {
            //printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        else if (st->variant() == WRITE_STAT) // TODO
        {
            //printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        else
        {
            for (int i = 0; i < 3; ++i)
                fillIn(currF, st->expr(i), parNames);
        }
    }
}

void functionAnalyzer(SgFile *file, map<string, vector<FuncInfo*>> &allFuncInfo, vector<LoopGraph*> &loops, bool dontFillFuncParam)
{
    map<int, LoopGraph*> mapLoopGraph;
    createMapLoopGraph(loops, mapLoopGraph);

    int funcNum = file->numberOfFunctions();
    __spf_print(DEBUG, "functions num in file = %d\n", funcNum);
    vector<SgStatement*> containsFunctions;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
                
        string containsPrefix = "";
        SgStatement *st_cp = st->controlParent();
        if (st_cp->variant() == PROC_HEDR || st_cp->variant() == PROG_HEDR || st_cp->variant() == FUNC_HEDR)
            containsPrefix = st_cp->symbol()->identifier() + string(".");
        
        string currFunc = "";
        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
            currFunc = progH->nameWithContains();
            __spf_print(DEBUG, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
            currFunc = procH->nameWithContains();
            __spf_print(DEBUG, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
            currFunc = funcH->nameWithContains();
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
        hasThisIds(st, currInfo->linesOfIO, { WRITE_STAT, READ_STAT, OPEN_STAT, CLOSE_STAT, PRINT_STAT });
        hasThisIds(st, currInfo->linesOfStop, { STOP_STAT, PAUSE_NODE });
        currInfo->isMain = (st->variant() == PROG_HEDR);

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

            if (!dontFillFuncParam)
                fillFuncParams(currInfo, commonBlocks, procFuncHedr);
            
            // Fill in names of function parameters
            for (int i = 0; i < procFuncHedr->numberOfParameters(); ++i)
            {
                currInfo->funcParams.identificators.push_back((procFuncHedr->parameter(i))->identifier());
                currInfo->isParamUsedAsIndex.push_back(false);
            }

            if (!dontFillFuncParam)
                fillInOut(currInfo, st, st->lastNodeOfStmt());
        }

        if (isSPF_NoInline(new Statement(st->lexNext())))
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
            currProcessing.second = st->lineNumber();
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

            if (!__gcov_doesThisLineExecuted(st->fileName(), st->lineNumber()))
            {
                st = st->lexNext();
                continue;
            }

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
                    if (!dontFillFuncParam)
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
                if (st->expr(i) && !dontFillFuncParam)
                    findFuncCalls(st->expr(i), entryProcs, st->lineNumber(), commonBlocks, macroNames, containsFunctions, prefix);

            if (st->variant() == ENTRY_STAT)
            {
                string entryName = st->symbol()->identifier();
                FuncInfo *entryInfo = new FuncInfo(entryName, make_pair(st->lineNumber(), lastNode->lineNumber()), new Statement(st));
                hasThisIds(st, entryInfo->linesOfIO, { WRITE_STAT, READ_STAT, OPEN_STAT, CLOSE_STAT, PRINT_STAT });
                hasThisIds(st, entryInfo->linesOfStop, { STOP_STAT, PAUSE_NODE });

                if (!dontFillFuncParam)
                    fillFuncParams(entryInfo, commonBlocks, st);

                if (isSPF_NoInline(new Statement(st->lexNext())))
                {
                    __spf_print(1, "set NOINLINE attribute for function '%s'\n", entryName.c_str());
                    entryInfo->doNotInline = true;
                }
                it->second.push_back(entryInfo);
                entryProcs.push_back(entryInfo);
            }

            if (isSgExecutableStatement(st))
            {
                for (auto &proc : entryProcs)
                    if (proc->isParamUsedAsIndex.size())
                        for (int i = 0; i < 3; i++)
                            findArrayRef(st->expr(i), *proc, st->variant() == ASSIGN_STAT && i == 0);

                if (st->variant() == FOR_NODE)
                {
                    auto itL = mapLoopGraph.find(st->lineNumber());
                    if (itL != mapLoopGraph.end())
                    {
                        for (auto &proc : entryProcs)
                            proc->loopsInFunc.push_back(itL->second);
                    }
                }
            }

            st = st->lexNext();
        }
    }
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
        std::wstring bufw;
        __spf_printToLongBuf(bufw, L"Function '%s' needs to be inlined due to count of call parameters are not enouth", to_wstring(def->funcName).c_str());

        if (needToAddErrors)
        {
            messages.push_back(Messages(NOTE, line, bufw, 1013));
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
                    std::wstring bufw;
                    __spf_printToLongBuf(bufw, L"Function '%s' needs to be inlined due to different type of call and def parameter %d", to_wstring(def->funcName).c_str(), i);

                    if (needToAddErrors)
                    {
                        messages.push_back(Messages(NOTE, line, bufw, 1013));
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
                    std::wstring bufw;
                    __spf_printToLongBuf(bufw, L"Function '%s' needs to be inlined, only full array passing was supported", to_wstring(def->funcName).c_str());

                    if (needToAddErrors)
                    {
                        messages.push_back(Messages(NOTE, line, bufw, 1013));
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

static bool hasCuttingDims(SgExpression *ex)
{
    if (ex->lhs())
    {
        if (ex->lhs()->variant() == EXPR_LIST)
        {
            SgExpression *list = ex->lhs();

            for  (auto list = ex->lhs(); list; list = list->rhs())
            {
                if (list->lhs() && list->lhs()->variant() == DDOT)
                    return true;
            }
        }
    }

    return false;
}

static bool checkParameter(SgExpression *ex, vector<Messages> &messages, const int statLine, 
                           SgForStmt *loop, bool needToAddErrors, const FuncInfo *func, int parNum,
                           const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            SgArrayRefExp *arrayRef = isSgArrayRefExp(ex);
            SgType *type = ex->symbol()->type();
            if (arrayRef && type && type->variant() != T_STRING)
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
                        bool type1 = (func->funcParams.inout_types[parNum] & OUT_BIT) != 0;
                        bool type2 = func->funcParams.parametersT[parNum] == ARRAY_T;

                        string add = "";
                        if (type1)
                            add += "(as out argument";
                        if (type2)
                        {
                            if (type1)
                                add += ", as array in function)";
                            else
                                add += "(as array in function)";
                        }
                        else
                            add += ")";

                        if (!isPassFullArray(ex))
                        {
                            bool _hasCuttingDims = hasCuttingDims(ex);
                            
                            if (_hasCuttingDims)
                            {
                                if (needToAddErrors)
                                {
                                    if (loop)
                                    {
                                        std::wstring bufw;
                                        __spf_printToLongBuf(bufw, L"Function '%s' needs to be inlined due to non private array reference '%s' under loop on line %d %s", 
                                                             to_wstring(func->funcName).c_str(), to_wstring(symb->identifier()).c_str(), loop->lineNumber(), to_wstring(add).c_str());

                                        messages.push_back(Messages(ERROR, statLine, bufw, 1013));
                                        __spf_print(1, "Function '%s' needs to be inlined due to non private array reference '%s' under loop on line %d %s\n", func->funcName.c_str(), symb->identifier(), loop->lineNumber(), add.c_str());
                                    }
                                    else
                                    {
                                        std::wstring bufw;
                                        __spf_printToLongBuf(bufw, L"Function '%s' needs to be inlined due to non private array reference '%s' %s", 
                                                             to_wstring(func->funcName).c_str(), to_wstring(symb->identifier()).c_str(), to_wstring(add).c_str());

                                        messages.push_back(Messages(ERROR, statLine, bufw, 1013));
                                        __spf_print(1, "Function '%s' needs to be inlined due to non private array reference '%s' %s\n", func->funcName.c_str(), symb->identifier(), add.c_str());
                                    }
                                }
                                ret = true;
                            }
                            else
                            {
                                //deprecate N first dims to distribute
                                if (type2)
                                {
                                    DIST::Array *inFunction = (DIST::Array*)func->funcParams.parameters[parNum];
                                    DIST::Array *mainArray = getArrayFromDeclarated(decl, symb->identifier());

                                    if (mainArray == NULL)
                                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                    set<DIST::Array*> realArrayRefs;
                                    getRealArrayRefs(mainArray, mainArray, realArrayRefs, arrayLinksByFuncCalls);
                                    
                                    const int toDepDims = inFunction->GetDimSize();
                                    for (auto &array : realArrayRefs)
                                        for (int z = 0; z < toDepDims; ++z)

                                            array->DeprecateDimension(z);
                                    for (int z = 0; z < toDepDims; ++z)
                                        mainArray->DeprecateDimension(z);

                                    inFunction->DeprecateAllDims();
                                    inFunction->SetNonDistributeFlag(DIST::NO_DISTR);

                                    std::wstring bufw;
                                    if (inFunction->GetDimSize() == 1)
                                        __spf_printToLongBuf(bufw, L"First dimension of array '%s' were deprecated to distributon due to function call '%s'", 
                                                             to_wstring(symb->identifier()).c_str(), to_wstring(func->funcName).c_str());
                                    else
                                        __spf_printToLongBuf(bufw, L"First %d dimensions of array '%s' were deprecated to distributon due to function call '%s'", 
                                                             inFunction->GetDimSize(), to_wstring(symb->identifier()).c_str(), to_wstring(func->funcName).c_str());

                                    messages.push_back(Messages(NOTE, statLine, bufw, 1040));
                                }
                            }
                        }
                        else // check dim sizes between formal and actual parameters
                        {
                            if (type2)
                            {
                                DIST::Array *inFunction = (DIST::Array*)func->funcParams.parameters[parNum];
                                DIST::Array *mainArray = getArrayFromDeclarated(decl, symb->identifier());

                                if (mainArray == NULL)
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                if (mainArray->GetDimSize() != inFunction->GetDimSize() && 
                                    !(inFunction->GetNonDistributeFlag() && !mainArray->GetNonDistributeFlag()))
                                {
                                    std::wstring bufw;
                                    __spf_printToLongBuf(bufw, L"Function '%s' needs to be inlined due to different dimension sizes in formal (size = %d) and actual(size = %d) parameters for array reference '%s'", 
                                             to_wstring(func->funcName).c_str(), inFunction->GetDimSize(), mainArray->GetDimSize(), to_wstring(symb->identifier()).c_str());

                                    messages.push_back(Messages(ERROR, statLine, bufw, 1013));
                                    __spf_print(1, "Function '%s' needs to be inlined due to different dimension sizes in formal (size = %d) and actual(size = %d) parameters for array reference '%s'\n", 
                                                    func->funcName.c_str(), inFunction->GetDimSize(), mainArray->GetDimSize(), symb->identifier());
                                    ret = true;
                                }                                
                            }
                            else
                            {
                                std::wstring bufw;
                                __spf_printToLongBuf(bufw, L"Type mismatch in function '%s' in formal and actual parameters for array reference '%s'\n", 
                                                     to_wstring(func->funcName).c_str(), to_wstring(symb->identifier()).c_str());

                                messages.push_back(Messages(ERROR, statLine, bufw, 1013));
                                __spf_print(1, "Type mismatch in function '%s' in formal and actual parameters for array reference '%s'\n", func->funcName.c_str(), symb->identifier());
                                ret = true;
                            }
                        }
                    }
                }
            }
        }

        if (ex->lhs())
        {
            bool res = checkParameter(ex->lhs(), messages, statLine, loop, needToAddErrors, func, parNum, arrayLinksByFuncCalls);
            ret |= res;
        }
        if (ex->rhs())
        {
            bool res = checkParameter(ex->rhs(), messages, statLine, loop, needToAddErrors, func, parNum, arrayLinksByFuncCalls);
            ret |= res;
        }
    }

    return ret;
}

static bool checkParameter(SgExpression *parList, vector<Messages> &messages, bool needToAddErrors, 
                           const FuncInfo *func, const int funcOnLine, SgForStmt *loop,
                           const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    int parNum = 0;
    bool needInsert = false;
    while (parList)
    {
        bool res = checkParameter(parList->lhs(), messages, funcOnLine, loop, needToAddErrors, func, parNum, arrayLinksByFuncCalls);
        needInsert |= res;
        ++parNum;
        parList = parList->rhs();
    }
    return needInsert;
}

static vector<int> findNoOfParWithLoopVar(SgExpression *pars, const string &loopSymb) 
{
    vector<int> parsWithLoopSymb;

    int parNo = 0;
    for (SgExpression *par = pars; par != NULL; par = par->rhs(), parNo++)
    {
        if (findLoopVarInParameter(par->lhs(), loopSymb))
            parsWithLoopSymb.push_back(parNo);
    }

    return parsWithLoopSymb;
}

static bool processParameterList(SgExpression *parList, SgForStmt *loop, const FuncInfo *func, const int funcOnLine, bool needToAddErrors,
                                 vector<Messages> &messages, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    bool needInsert = false;
    bool hasLoopVar = false;

    if (loop)
        hasLoopVar = findLoopVarInParameter(parList, loop->symbol()->identifier());

    if (hasLoopVar)
    {
        const vector<int> parsWithLoopSymb = findNoOfParWithLoopVar(parList, loop->symbol()->identifier());

        int idx = -1;
        for (auto &par : parsWithLoopSymb)
        {
            if (func->isParamUsedAsIndex[par])
            {
                idx = par + 1;
                break;
            }
        }

        if (idx != -1)
        {
            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"Function '%s' needs to be inlined due to use of loop's symbol on line %d as index of an array inside this call, in parameter num %d", 
                                 to_wstring(func->funcName).c_str(), loop->lineNumber(), idx);
            if (needToAddErrors)
            {
                messages.push_back(Messages(ERROR, funcOnLine, bufw, 1013));
                __spf_print(1, "Function '%s' needs to be inlined due to use of loop's symbol  on line %d as index of an array inside this call, in parameter num %d\n", 
                                func->funcName.c_str(), loop->lineNumber(), idx);
            }

            needInsert = true;
        }
        else
            needInsert = checkParameter(parList, messages, needToAddErrors, func, funcOnLine, loop, arrayLinksByFuncCalls);
    }
    else
        needInsert = checkParameter(parList, messages, needToAddErrors, func, funcOnLine, loop, arrayLinksByFuncCalls);

    return needInsert;
}

static bool findFuncCall(SgExpression *ex, const FuncInfo *func, vector<Messages> &messages, const int statLine, SgForStmt *loop, bool needToAddErrors,
                         const map<string, FuncInfo*> &funcByName,
                         const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls, 
                         bool processAll = false, set<string> *funcChecked = NULL, set<string> *needToInsert = NULL)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            if (processAll)
            {
                if (funcChecked && needToInsert)
                {
                    const string fName = ex->symbol()->identifier();
                    if (funcChecked->find(fName) == funcChecked->end())
                    {
                        funcChecked->insert(fName);
                        auto itF = funcByName.find(fName);
                        if (itF != funcByName.end())
                        {
                            ret = processParameterList(ex->lhs(), loop, itF->second, statLine, needToAddErrors, messages, arrayLinksByFuncCalls);
                            if (ret)
                                needToInsert->insert(fName);
                        }
                    }
                }
                else
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            else
            {
                if (ex->symbol()->identifier() == func->funcName)
                {
                    bool res = processParameterList(ex->lhs(), loop, func, statLine, needToAddErrors, messages, arrayLinksByFuncCalls);
                    ret |= res;
                }
            }
        }

        bool resL = findFuncCall(ex->lhs(), func, messages, statLine, loop, needToAddErrors, funcByName, arrayLinksByFuncCalls, processAll, funcChecked, needToInsert);
        bool resR = findFuncCall(ex->rhs(), func, messages, statLine, loop, needToAddErrors, funcByName, arrayLinksByFuncCalls, processAll, funcChecked, needToInsert);
        ret |= resL || resR;
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

    SwitchFile(itS->second->getFileId());
    return itS->second;
}

static void findInsertedFuncLoopGraph(const vector<LoopGraph*> &childs, set<string> &needToInsert, SgFile *currF, 
                                      vector<Messages> &messages, bool needToAddErrors, const map<string, FuncInfo*> &funcByName,
                                      const map<string, map<int, SgStatement*>> &statByLine, 
                                      const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls, set<string> &funcChecked)
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
                funcChecked.insert(funcName);

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

                if (var == PROC_STAT)
                {
                    bool res = processParameterList(func->expr(0), loop, it->second, funcOnLine, needToAddErrors, messages, arrayLinksByFuncCalls);
                    needInsert |= res;
                }
                else
                    for (int z = 0; z < 3; ++z)
                    {
                        bool res = findFuncCall(func->expr(z), it->second, messages, funcOnLine, loop, needToAddErrors, funcByName, arrayLinksByFuncCalls);
                        needInsert |= res;
                    }

                if (needInsert)
                    needToInsert.insert(childs[k]->calls[i].first);
            }
        }
        findInsertedFuncLoopGraph(childs[k]->children, needToInsert, currF, messages, needToAddErrors, funcByName, statByLine, arrayLinksByFuncCalls, funcChecked);
    }
}

static bool runCheckOutOfLoop(SgExpression *parList, const FuncInfo *func, const int lineFromCall, bool needToAddErrors,
                              vector<Messages> &messages, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    bool needInsert = processParameterList(parList, NULL, func, lineFromCall, needToAddErrors, messages, arrayLinksByFuncCalls);
    return needInsert;
}

static void findInsertedFuncLoopGraph(const map<string, vector<LoopGraph*>> &loopGraph, set<string> &needToInsert,
                                      SgProject *proj, const map<string, int> &files, map<string, vector<Messages>> &allMessages,
                                      bool needToAddErrors, const map<string, FuncInfo*> &funcByName,
                                      const map<string, map<int, SgStatement*>> &statByLine,
                                      const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls, const vector<ParallelRegion*> &regions)
{
    set<string> funcChecked;
    
    for (auto &loop : loopGraph)
    {
        const int fileN = files.find(loop.first)->second;
        SgFile *currF = &(proj->file(fileN));
        SwitchFile(fileN);

        auto itM = allMessages.find(loop.first);
        if (itM == allMessages.end())
            itM = allMessages.insert(itM, make_pair(loop.first, vector<Messages>()));
        findInsertedFuncLoopGraph(loop.second, needToInsert, currF, itM->second, needToAddErrors, funcByName, statByLine, arrayLinksByFuncCalls, funcChecked);
    }

    //not checked, out of loops
    for (int f = 0; f < proj->numberOfFiles(); ++f)
    {
        SgFile *currF = &(proj->file(f));
        SwitchFile(f);

        auto itM = allMessages.find(currF->filename());
        if (itM == allMessages.end())
            itM = allMessages.insert(itM, make_pair(currF->filename(), vector<Messages>()));

        for (int z = 0; z < currF->numberOfFunctions(); ++z)
        {
            SgStatement *funcInFile = currF->functions(z);
            for (SgStatement *st = funcInFile->lexNext(); st != funcInFile->lastNodeOfStmt(); st = st->lexNext())
            {
                if (st->variant() == CONTAINS_STMT)
                    break;

                if (st->lineNumber() == -1)
                    continue;

                if (!__gcov_doesThisLineExecuted(st->fileName(), st->lineNumber()))
                    continue;

                set<ParallelRegion*> allRegs = getAllRegionsByLine(regions, st->fileName(), st->lineNumber());
                if (allRegs.size() == 0)
                    continue;

                if (isSgExecutableStatement(st))
                {
                    if (st->variant() == PROC_STAT)
                    {
                        const string fName = st->symbol()->identifier();
                        auto it = funcChecked.find(fName);
                        auto itF = funcByName.find(fName);
                        if (it == funcChecked.end() && itF != funcByName.end())
                        {
                            bool needInsert = runCheckOutOfLoop(st->expr(0), itF->second, st->lineNumber(), needToAddErrors, itM->second, arrayLinksByFuncCalls);
                            if (needInsert)
                                needToInsert.insert(fName);
                        }
                    }
                    else
                        for (int z = 0; z < 3; ++z)
                            findFuncCall(st->expr(z), NULL, itM->second, st->lineNumber(), NULL, needToAddErrors, funcByName, arrayLinksByFuncCalls, true, &funcChecked, &needToInsert);
                }
            }
        }
    }
}

int CheckFunctionsToInline(SgProject *proj, const map<string, int> &files, const char *fileName, map<string, vector<FuncInfo*>> &funcByFile, 
                           const map<string, vector<LoopGraph*>> &loopGraph, map<string, vector<Messages>> &allMessages, bool needToAddErrors,
                           const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls, const vector<ParallelRegion*> &regions)
{
    map<string, map<int, SgStatement*>> statByLine; //file -> map    
    //build info
    for (int i = 0; i < proj->numberOfFiles(); ++i)
    {
        map<int, SgStatement*> toAdd;
        SgFile *file = &(proj->file(i));
        SwitchFile(i);

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
    findInsertedFuncLoopGraph(loopGraph, needToInsert, proj, files, allMessages, needToAddErrors, funcByName, statByLine, arrayLinksByFuncCalls, regions);

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

                std::wstring bufw;
                __spf_printToLongBuf(bufw, L"Found recursive chain calls: %s, this function will be ignored", to_wstring(chain).c_str());
                messagesForFile.push_back(Messages(ERROR, currentChainCalls[0]->linesNum.first, bufw, 1014));
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

map<string, set<SgSymbol*>> moduleRefsByUseInFunction(SgStatement *stIn)
{
    int var = stIn->variant();
    while (var != PROG_HEDR && var != PROC_HEDR && var != FUNC_HEDR)
    {
        stIn = stIn->controlParent();
        var = stIn->variant();
    }

    map<string, set<SgSymbol*>> byUse;
    for (SgStatement *stat = stIn->lexNext(); !isSgExecutableStatement(stat); stat = stat->lexNext())
    {
        if (stat->variant() == USE_STMT)
        {
            SgExpression *ex = stat->expr(0);
            if (ex && ex->variant() == ONLY_NODE)
            {
                for (auto exI = ex->lhs(); exI; exI = exI->rhs())
                {
                    if (exI->lhs()->variant() == RENAME_NODE)
                    {
                        SgExpression *ren = exI->lhs();
                        if (ren->lhs()->symbol() && ren->rhs() && ren->rhs()->symbol())
                            byUse[ren->rhs()->symbol()->identifier()].insert(ren->lhs()->symbol());
                    }
                }
            }
            else if (ex && ex->lhs())
            {
                for (auto exI = ex; exI; exI = exI->rhs())
                {
                    if (exI->lhs()->variant() == RENAME_NODE)
                    {
                        SgExpression *ren = exI->lhs();
                        if (ren->lhs()->symbol() && ren->rhs() && ren->rhs()->symbol())
                            byUse[ren->rhs()->symbol()->identifier()].insert(ren->lhs()->symbol());
                    }
                }
            }
        }
    }

    return byUse;
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

static void propagateWritesToArrays(map<string, FuncInfo*> &allFuncInfo)
{
    bool change = true;
    while (change)
    {
        change = false;

        for (auto &func : allFuncInfo)
        {
            if (func.second->funcParams.countOfPars == 0)
                continue;

            for (int z = 0; z < func.second->funcParams.countOfPars; ++z)
            {
                if ((func.second->funcParams.inout_types[z] & OUT_BIT) == 0)
                    continue;

                for (auto &callsTo : func.second->callsTo)
                {
                    map<string, int> parNames;
                    for (int p = 0; p < callsTo->funcParams.countOfPars; ++p)
                        parNames[callsTo->funcParams.identificators[p]] = p;

                    bool ok = callsTo->funcPointer->GetOriginal()->switchToFile();
                    if (!ok)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    for (auto &callFrom : callsTo->pointerDetailCallsFrom)
                    {
                        SgExpression *arg = NULL;

                        if (callFrom.second == PROC_STAT)
                        {
                            SgCallStmt *call = (SgCallStmt*)callFrom.first;
                            if (call->symbol()->identifier() != func.second->funcName)
                                continue;
                            arg = call->arg(z);
                        }
                        else if (callFrom.second == FUNC_CALL)
                        {
                            SgFunctionCallExp *call = (SgFunctionCallExp*)callFrom.first;

                            if (call->symbol()->identifier() != func.second->funcName)
                                continue;
                            arg = call->arg(z);
                        }

                        string argName = "";
                        if (arg->symbol())
                            argName = arg->symbol()->identifier();

                        auto it = parNames.find(argName);
                        if (it != parNames.end() && ((callsTo->funcParams.inout_types[it->second] & OUT_BIT) == 0))
                        {
                            change = true;
                            callsTo->funcParams.inout_types[it->second] |= OUT_BIT;
                            if ((func.second->funcParams.inout_types[z] & IN_BIT) != 0)
                                callsTo->funcParams.inout_types[it->second] |= IN_BIT;
                        }
                    }
                }
            }
        }
    }
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

void propagateArrayFlags(const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    bool change = true;
    while (change)
    {
        bool changeD = propagateFlag(true, arrayLinksByFuncCalls);
        bool changeU = propagateFlag(false, arrayLinksByFuncCalls);

        change = changeD || changeU;
    }
}

static void aggregateUsedArrays(map<string, FuncInfo*> &funcByName, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    //change to real refs
    for (auto &func : funcByName)
    {
        set<DIST::Array*> curr = func.second->allUsedArrays;
        set<DIST::Array*> newRefs;
        for (auto &array : curr)
            getRealArrayRefs(array, array, newRefs, arrayLinksByFuncCalls);
        func.second->allUsedArrays.clear();
        for (auto &newArray : newRefs)
            if (newArray->GetNonDistributeFlag() == false)
                func.second->allUsedArrays.insert(newArray);
    }

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto &func : funcByName)
        {
            for (auto &callsFrom : func.second->callsFrom)
            {
                auto itF = funcByName.find(callsFrom);
                if (itF != funcByName.end())
                {
                    for (auto &usedArray : itF->second->allUsedArrays)
                    {
                        auto itA = func.second->allUsedArrays.find(usedArray);
                        if (itA == func.second->allUsedArrays.end())
                        {
                            changed = true;
                            func.second->allUsedArrays.insert(usedArray);
                        }
                    }
                }
            }
        }
    }
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

    propagateArrayFlags(arrayLinksByFuncCalls);

    //propagate distr state
    bool change = true;
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

    map<string, FuncInfo*> funcByName;
    createMapOfFunc(allFuncInfo, funcByName);

    propagateWritesToArrays(funcByName);
    aggregateUsedArrays(funcByName, arrayLinksByFuncCalls);

    //debug dump
    /*for (auto &elem : declaratedArrays)
    {
        auto array = elem.second.first;
        auto flag = array->GetNonDistributeFlagVal();
        // int { DISTR = 0, NO_DISTR, SPF_PRIV, IO_PRIV } distFlagType;
        string flagS = "";
        if (flag == DIST::DISTR)
            flagS = "DISTR";
        else if (flag == DIST::NO_DISTR)
            flagS = "NO_DISTR";
        else if (flag == DIST::SPF_PRIV)
            flagS = "SPF_PRIV";
        else if (flag == DIST::IO_PRIV)
            flagS = "IO_PRIV";

        printf("%s %s flag %s\n", array->GetShortName(), array->GetName(), flagS.c_str());
    }*/
}
#undef DEBUG
