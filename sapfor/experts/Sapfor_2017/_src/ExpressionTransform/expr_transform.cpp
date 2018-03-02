#include "../leak_detector.h"

#include "dvm.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <iterator>

#include "../ParallelizationRegions/ParRegions.h"
#include "../GraphLoop/graph_loops.h"
#include "../GraphCall/graph_calls_func.h"
#include "../utils.h"
#include "../SgUtils.h"
#include "../Distribution/Distribution.h"
#include "expr_transform.h"

using std::pair;
using std::map;
using std::set;
using std::tuple;
using std::vector;
using std::string;
using std::iterator;
using std::make_pair;

#define PRINT_PROF_INFO 0
/*
 * Contains original SgExpressions.
 * map <string, ...> key is a file, where replacements take place
 * map <StatementObj, vector<SgExpression*>> key is a changed SgStetement, value - 3 SgEpression*'s
 * [i] SgExpresson* is null, if it has not been changed
 */

map<string, map<StatementObj, vector<SgExpression*>>> replacementsInFiles;
map<StatementObj, vector<SgExpression*>>* curFileReplacements;

map<SgStatement*, map<StatementObj, vector<SgExpression*>>> replacementsInFunctions;
map<StatementObj, vector<SgExpression*>>* curFunctionReplacements;
//map<string, map<pair<pair<void*, REPLACE_PTR_TYPE>, int>, pair<SgExpression*, int>>> replacementsInFiles;
set<SgStatement*> visitedStatements;
GraphsKeeper graphsKeeper;

void GraphsKeeper::addInDefs(ControlFlowGraph* targetGraph, ControlFlowGraph* parentGraph, map<SymbolKey, map<string, SgExpression*>>* inDefs)
{
    //TODO

    for (auto it = graphs.begin(); it != graphs.end(); ++it)
        if (it->CGraph == targetGraph)
        {
            auto founded = it->in_defs.find(parentGraph);
            if (founded == it->in_defs.end())
                it->in_defs.insert(founded, make_pair(parentGraph, map<SymbolKey, map<string, SgExpression*>>()));
            mergeDefs(&(founded->second), inDefs, NULL);
            return;
        }

    graphs.push_back(GraphAdjustmentItem(targetGraph));
    graphs[graphs.size() - 1].in_defs.insert(make_pair(parentGraph, map<SymbolKey, map<string, SgExpression*>>()));
    mergeDefs(&(graphs[graphs.size() - 1].in_defs.begin()->second), inDefs, NULL);
    graphs[graphs.size() - 1].in_defs.begin();

}

void GraphsKeeper::deleteInDefs(ControlFlowGraph* targetGraph, ControlFlowGraph* parentGraph)
{
    for (auto it = graphs.begin(); it != graphs.end(); ++it)
        if (it->CGraph == targetGraph)
        {
            auto founded = it->in_defs.find(parentGraph);
            if (founded != it->in_defs.end())
                founded->second.clear();
        }
}

map<SymbolKey, map<string, SgExpression*>>* GraphsKeeper::getInDefsFor(ControlFlowGraph* CGraph)
{
    //TODO//отфильтровать и полностью подготовить множество
    return NULL;
    map<SymbolKey, map<string, SgExpression*>>* result = new map<SymbolKey, map<string, SgExpression*>>();
    for (int i = 0; i < graphs.size(); ++i)
    {
        if (graphs[i].CGraph == CGraph)
        {
            for (auto it = graphs[i].in_defs.begin(); it != graphs[i].in_defs.end(); ++it)
                mergeDefs(result, &(it->second), NULL);
        }
    }
    return result;

}

ControlFlowGraph* GraphsKeeper::getGraphForAdjustment()
{
    for (int i = 0; i < graphs.size(); ++i)
        if (graphs[i].needAdjustment)
        {
            graphs[i].needAdjustment = false;
            return graphs[i].CGraph;
        }

    return NULL;
}

void GraphsKeeper::deleteGraphs()
{
    //TODO Delete all graphs or only main?
    for (int i = 0; i < graphs.size(); ++i)
        delete graphs[i].CGraph;
}

void revertReplacements(SgStatement* function)
{
    auto tmpF = replacementsInFunctions.find(function);
    if (tmpF == replacementsInFunctions.end())
        return;

    auto replacements = &(tmpF->second);
    for (auto it = replacements->begin(); it != replacements->end(); ++it)
    {
        SgStatement *parent = it->first.stmt;
        for (int i = 0; i < 3; ++i)
        {
            if (it->second[i] != NULL)
            {
                SgExpression* replacement = parent->expr(i);
                parent->setExpression(i, *(it->second[i]));
                it->second[i] = replacement;
            }
        }
    }
}

void revertReplacements(string filename)
{
    auto tmpF = replacementsInFiles.find(filename);
    if (tmpF == replacementsInFiles.end())
        return;

    auto replacements = &(tmpF->second);
    for (auto it = replacements->begin(); it != replacements->end(); ++it)
    {
        SgStatement *parent = it->first.stmt;
        for (int i = 0; i < 3; ++i)
        {
            if (it->second[i] != NULL)
            {
                SgExpression* replacement = parent->expr(i);
                parent->setExpression(i, *(it->second[i]));
                it->second[i] = replacement;
            }
        }
    }
}

SgExpression* ReplaceParameter(SgExpression *e)
{
    if (!e)
        return e;
    if (e->variant() == CONST_REF)
    {
        SgConstantSymb *sc = isSgConstantSymb(e->symbol());
        if (!sc->constantValue())
            return e;
        return (ReplaceParameter(&(sc->constantValue()->copy())));
    }
    e->setLhs(ReplaceParameter(e->lhs()));
    e->setRhs(ReplaceParameter(e->rhs()));
    return e;
}

SgExpression* ReplaceConstant(SgExpression *e)
{
    SgExpression *er;
    er = ReplaceParameter(&(e->copy()));

    if (er->isInteger())
        return (new SgValueExp(er->valueInteger()));
    else
        return er;
}

SgExpression* ReplaceArrayBoundSizes(SgExpression *edim)
{
    SgSubscriptExp *sbe = NULL;
    SgExpression *low = NULL;

    if (!edim)
        return edim;

    if ((sbe = isSgSubscriptExp(edim)) != NULL) //DDOT
    {
        if (!sbe->ubound())
            return edim;

        edim = new SgExpression(DDOT);
        edim->setLhs(ReplaceArrayBoundSizes(sbe->lbound()));
        edim->setRhs(ReplaceArrayBoundSizes(sbe->ubound()));
    }
    else
        edim = ReplaceConstant(edim);
    return edim;
}

static pair<int, int> getCoefsOfSubscript(SgExpression *exp, SgSymbol *doName, int &err)
{
    pair<int, int> result;
    pair<int, int> lRes = make_pair(0, 0), rRes = make_pair(0, 0);
    int lErr = 0, rErr = 0;
    const int op = exp->variant();

    if (exp->lhs())
        lRes = getCoefsOfSubscript(exp->lhs(), doName, lErr);
    if (exp->rhs())
        rRes = getCoefsOfSubscript(exp->rhs(), doName, rErr);

    switch (op)
    {
    case ADD_OP:
        if (lErr != -1 && rErr != -1)
            result = make_pair(lRes.first + rRes.first, lRes.second + rRes.second);
        else
            err = -1;
        break;
    case MINUS_OP:
        if (lErr != -1)
            result = make_pair(-lRes.first, lRes.second);
        else
            err = -1;
        break;
    case MULT_OP:
        if (lErr != -1 && rErr != -1)
        {
            if (lRes.first != 0 && rRes.first != 0)
                err = -1;
            else
                result = make_pair(lRes.first * rRes.second + rRes.first * lRes.second, lRes.second * rRes.second);
        }
        else
            err = -1;
        break;
    case SUBT_OP:
        if (lErr != -1 && rErr != -1)
            result = make_pair(lRes.first - rRes.first, lRes.second - rRes.second);
        else
            err = -1;
        break;
    case DIV_OP:
        if (lErr != -1 && rErr != -1)
        {
            if (rRes.first != 0 || rRes.second == 0)
                err = -1;
            else
                result = make_pair(lRes.first / rRes.second, lRes.second / rRes.second);
        }
        else
            err = -1;
        break;
    case MOD_OP:
        if (lErr != -1 && rErr != -1)
        {
            if (rRes.first != 0 || rRes.second == 0)
                err = -1;
            else
                result = make_pair(lRes.first % rRes.second, lRes.second % rRes.second);
        }
        else
            err = -1;
        break;
    case VAR_REF:
        if (strcmp(exp->symbol()->identifier(), doName->identifier()) == 0)
            result = make_pair(1, 0);
        else
            err = -1;
        break;
    case INT_VAL:
        result = make_pair(0, exp->valueInteger());
        break;
    default:
        err = -1;
    }

    if (err != -1)
        return result;
    else
        return make_pair(0, 0);
}

void replaceConstatRec(SgExpression *&exp)
{
    if (exp->variant() == CONST_REF)
    {
        SgExpression *ret = ReplaceParameter(exp);
        if (ret->isInteger())
            exp = new SgValueExp(ret->valueInteger());
    }

    if (exp->lhs())
    {
        SgExpression *left = exp->lhs();
        replaceConstatRec(left);
        exp->setLhs(left);
    }

    if (exp->rhs())
    {
        SgExpression *right = exp->rhs();
        replaceConstatRec(right);
        exp->setRhs(right);
    }
}

int CalculateInteger(SgExpression *expr, int &result)
{
    if (expr->variant() == INT_VAL)
    {
        result = expr->valueInteger();
        return 0;
    }
    else
    {
        pair<int, int> err = make_pair(-1, -1);
        pair<int, int> res;
        if (expr->lhs())
            err.first = CalculateInteger(expr->lhs(), res.first);
        if (expr->rhs())
            err.second = CalculateInteger(expr->rhs(), res.second);

        switch (expr->variant())
        {
        case ADD_OP:
            if (err.first != -1 && err.second != -1)
            {
                result = res.first + res.second;
                return 0;
            }
            else
                return -1;
            break;
        case MINUS_OP:
            if (err.first != -1)
            {
                result = -res.first;
                return 0;
            }
            else
                return -1;
            break;
        case MULT_OP:
            if (err.first != -1 && err.second != -1)
            {
                result = res.first * res.second;
                return 0;
            }
            else
                return -1;
            break;
        case SUBT_OP:
            if (err.first != -1 && err.second != -1)
            {
                result = res.first - res.second;
                return 0;
            }
            else
                return -1;
            break;
        case DIV_OP:
            if (err.first != -1 && err.second != -1 && res.second != 0)
            {
                result = res.first / res.second;
                return 0;
            }
            else
                return -1;
            break;
        case MOD_OP:
            if (err.first != -1 && err.second != -1 && res.second != 0)
            {
                result = res.first % res.second;
                return 0;
            }
            else
                return -1;
            break;
        case EXP_OP:
            if (err.first != -1 && err.second != -1)
            {
                result = (int) pow(res.first, res.second);
                return 0;
            }
            else
                return -1;
            break;
        default:
            return -1;
        }
    }
}

void calculate(SgExpression *&exp)
{
    SgExpression *left, *right;
    int res, err;
    if (exp->lhs())
    {
        left = exp->lhs();
        err = CalculateInteger(left, res);
        if (err != -1)
            exp->setLhs(new SgValueExp(res));
        else
            calculate(left);
    }

    if (exp->rhs())
    {
        right = exp->rhs();
        err = CalculateInteger(right, res);
        if (err != -1)
            exp->setRhs(new SgValueExp(res));
        else
            calculate(right);
    }
}

static bool isNeedFinishCalc(SgExpression *exp, string doName)
{
    bool ret = true;
    if (exp->variant() == VAR_REF)
    {
        if (string(exp->symbol()->identifier()) != doName)
            ret = false;
    }

    if (exp->lhs())
        ret &= isNeedFinishCalc(exp->lhs(), doName);

    if (exp->rhs())
        ret &= isNeedFinishCalc(exp->rhs(), doName);

    return ret;
}

static void replaceVarRefToZero(SgExpression *&exp, int &countVarRefs)
{
    if (exp->variant() == VAR_REF)
    {
        exp = new SgValueExp(0);
        countVarRefs++;
    }

    SgExpression *tmp;
    if (exp->lhs())
    {
        tmp = exp->lhs();
        replaceVarRefToZero(tmp, countVarRefs);
        exp->setLhs(tmp);
    }

    if (exp->rhs())
    {
        tmp = exp->rhs();
        replaceVarRefToZero(tmp, countVarRefs);
        exp->setRhs(tmp);
    }
}

void getCoefsOfSubscript(pair<int, int> &retCoefs, SgExpression *exp, SgSymbol *doName)
{
    SgExpression *copyExp = &(exp->copy());
    replaceConstatRec(copyExp);
    calculate(copyExp);

    if (isNeedFinishCalc(copyExp, doName->identifier()))
    {
        int err = 0;
        retCoefs = getCoefsOfSubscript(copyExp, doName, err);
    }
    else
        retCoefs = make_pair(0, 0);
}

SgExpression* valueOfVar(SgExpression *var, CBasicBlock *b)
{
    SgExpression* exp = NULL;
    //first, check previous defs within block
    auto founded = b->getGen()->find(SymbolKey(var->symbol()));
    if (founded != b->getGen()->end())
        if (!valueWithFunctionCall(founded->second))
            if (!valueWithRecursion(founded->first, founded->second))
                exp = founded->second;

    if (exp == NULL)
    {
        //second, check defs from previous blocks
        auto founded_inDefs = b->getInDefs()->find(SymbolKey(var->symbol()));
        if (founded_inDefs != b->getInDefs()->end())
            //if smth is founded_inDefs, it has single value
            //thanks to CorrectInDefs(ControlFlowGraph*) function
            exp = founded_inDefs->second.begin()->second;

        //we have to check if this value was killed by gen inside block
        if (exp != NULL)
            for (auto it = b->getGen()->begin(); it != b->getGen()->end(); ++it)
                if (symbolInExpression(it->first.getVar(), exp))
                {
                    exp = NULL;
                    break;
                }
    }
    return exp;
}

static void createLinksToCopy(SgExpression *exOrig, SgExpression *exCopy)
{
    if (exOrig && exCopy)
    {
        if (exOrig->variant() == ARRAY_REF && exCopy->variant() == ARRAY_REF)
        {
            exOrig->addAttribute(ARRAY_REF, exCopy, sizeof(SgExpression*));
            exCopy->addAttribute(ARRAY_REF, exOrig, sizeof(SgExpression*));
        }

        createLinksToCopy(exOrig->lhs(), exCopy->lhs());
        createLinksToCopy(exOrig->rhs(), exCopy->rhs());
    }    
}

static void createBackup(SgStatement* stmt, int expNumber)
{
    SgExpression *exp = stmt->expr(expNumber);

    if (exp == NULL) // no backup is required
        return;

    auto foundedParent = curFileReplacements->find(stmt);
    if (foundedParent == curFileReplacements->end())
    {
        auto inserted = curFileReplacements->insert(std::make_pair(StatementObj(stmt), vector<SgExpression*>()));
        foundedParent = inserted.first;
        foundedParent->second.resize(3);
        for (int i = 0; i < 3; ++i)
            foundedParent->second[i] = NULL;
    }

    if (foundedParent->second[expNumber] == NULL)
    {
        SgExpression* expToCopy = exp->copyPtr();
        foundedParent->second[expNumber] = expToCopy;

        string orig = string(exp->unparse());
        string copy = string(expToCopy->unparse());
        if (orig == copy)
            createLinksToCopy(exp, expToCopy);
    }
}

SgExpression* tryMakeInt(SgExpression* exp)
{
    if (exp->variant() != INT_VAL)
        if (exp->isInteger())
            return new SgValueExp(exp->valueInteger());
    return exp;
}

void setNewSubexpression(SgExpression *parent, bool rightSide, SgExpression *newExp)
{
    SgExpression *oldExp = rightSide ? parent->rhs() : parent->lhs();

    __spf_print(PRINT_PROF_INFO, "%s -> ", oldExp->unparse());
    __spf_print(PRINT_PROF_INFO, "%s\n", newExp->unparse());
    SgExpression* expToCopy = newExp->copyPtr();

    rightSide ? parent->setRhs(tryMakeInt(expToCopy)) : parent->setLhs(tryMakeInt(expToCopy));
}

bool replaceVarsInExpression(SgStatement *parent, int expNumber, CBasicBlock *b, bool replaceFirstVar)
{
    std::queue<SgExpression*> toCheck;
    bool wereReplacements = false;
    SgExpression* exp = parent->expr(expNumber);
    if (exp->variant() == VAR_REF && !replaceFirstVar)
        return false;

    //If SgExpression is a single VAR
    if (exp->variant() == VAR_REF)
    {

        SgExpression* newExp = valueOfVar(exp, b);
        if (newExp != NULL)
        {
            createBackup(parent, expNumber);
            __spf_print(PRINT_PROF_INFO, "%s -> ", exp->unparse());
            __spf_print(PRINT_PROF_INFO, "%s\n", newExp->unparse());
            SgExpression* expToCopy = newExp->copyPtr();
            parent->setExpression(expNumber, *(tryMakeInt(expToCopy)));
            wereReplacements = true;
        }
    }//If not
    else
    {
        toCheck.push(exp);
        while (!toCheck.empty())
        {
            exp = toCheck.front();
            toCheck.pop();

            if (exp->rhs())
            {
                if (exp->rhs()->variant() == VAR_REF)
                {
                    SgExpression* newExp = valueOfVar(exp->rhs(), b);
                    if (newExp != NULL)
                    {
                        createBackup(parent, expNumber);
                        setNewSubexpression(exp, true, newExp);
                        wereReplacements = true;
                    }
                }
                else
                    toCheck.push(exp->rhs());
            }
            if(exp->variant() != FUNC_CALL)// Funcs' arguments are processed in replaceCallArguments
                if (exp->lhs())
                {
                    if (exp->lhs()->variant() == VAR_REF)
                    {
                        SgExpression* newExp = valueOfVar(exp->lhs(), b);
                        if (newExp != NULL)
                        {
                            createBackup(parent, expNumber);
                            setNewSubexpression(exp, false, newExp);
                            wereReplacements = true;
                        }
                    }
                    else
                        toCheck.push(exp->lhs());
                }
        }
    }
    return wereReplacements;
}

bool needReplacements(SgExpression* exp, map<SymbolKey, std::vector<SgExpression*>>* ins, bool checkVar)
{
    if (exp->variant() == VAR_REF)
    {
        if (checkVar)
            for (auto it = ins->begin(); it != ins->end(); ++it)
                if (it->first == exp->symbol())
                    return true;
        return false;
    }
    else
    {
        bool needReplacement = false;
        if (exp->rhs())
            needReplacement = needReplacements(exp->rhs(), ins, true);
        if (exp->lhs() && !needReplacement)
            needReplacement = needReplacements(exp->lhs(), ins, true);
        return needReplacement;
    }
}

bool replaceVarsInCallArgument(SgExpression *exp, CBasicBlock *b)
{
    bool wereReplacements = false;
    SgExpression *lhs = exp->lhs(), *rhs = exp->rhs();
    //We don't want expand arguments of other functions.
    if(lhs && lhs->variant() != FUNC_CALL)
    {
        if(lhs->variant() == VAR_REF)
        {
            SgExpression* newExp = valueOfVar(lhs, b);
            if (newExp != NULL)
            {
                setNewSubexpression(exp, false, newExp);
                wereReplacements = true;
            }
        }
        else
            replaceVarsInCallArgument(lhs, b);
    }

    if(rhs && rhs->variant() != FUNC_CALL)
    {
        if(rhs->variant() == VAR_REF)
        {
            SgExpression* newExp = valueOfVar(rhs, b);
            if (newExp != NULL)
            {
                setNewSubexpression(exp, true, newExp);
                wereReplacements = true;
            }
        }
        else
            replaceVarsInCallArgument(rhs, b);
    }

    return wereReplacements;
}

bool replaceCallArguments(ControlFlowItem *cfi, CBasicBlock *b)
{
    bool wereReplacements = false;
    int numberOfArgs = 0;
    SgExpression *args = NULL, *arg = NULL;
    SgFunctionCallExp *funcCall = NULL;
    SgStatement *st = cfi->getStatement();
    AnalysedCallsList *callData = cfi->getCall();

    if(callData == NULL)//no info of arguments, can't expand expressions;
        return false;

    if (st != NULL && st->variant() == PROC_STAT) //procedure call
    {
        createBackup(st, 0);
        SgCallStmt *callStmt = isSgCallStmt(cfi->getStatement());
        args = callStmt->expr(0);
        numberOfArgs = callStmt->numberOfArgs();
    }
    else if ((funcCall = cfi->getFunctionCall()) != NULL) //functionCall
    {
        st = cfi->getOriginalStatement();
        for(int i=0;i<3;++i)
            if(st->expr(i)) // TODO: search for expression?
                createBackup(st, i);
        args = funcCall->lhs();
        numberOfArgs = funcCall->numberOfArgs();
    }

    if (args)
        for (int i = 0; i < numberOfArgs; ++i)
        {
            arg = args->lhs();
            if ((arg->variant() != VAR_REF) || argIsReplaceable(i, callData))
                wereReplacements |= replaceVarsInCallArgument(args, b);
            args = args->rhs();
        }

    return wereReplacements;
}
/*
 * Have to run b->adjustGenAndKill(cfi) here to track changes inside block.
 */
bool replaceVarsInBlock(CBasicBlock* b)
{
    bool wereReplacements = false;
    SgStatement* st;
    for (ControlFlowItem* cfi = b->getStart(); cfi != b->getEnd()->getNext(); cfi = cfi->getNext())
    {
        st = cfi->getStatement();

        if(cfi->getFunctionCall())
        {
            wereReplacements |= replaceCallArguments(cfi, b);
            b->checkFuncAndProcCalls(cfi);
        }

        if (st != NULL)
        {
            if (isDVM_stat(st))
                continue;
            if (isSPF_stat(st))
                continue;

            switch (st->variant())
            {
            case ASSIGN_STAT:
                wereReplacements |= replaceVarsInExpression(st, 0, b, false);
                wereReplacements |= replaceVarsInExpression(st, 1, b, true);
                b->adjustGenAndKill(cfi);
                break;
            case PROC_STAT:
                wereReplacements |= replaceCallArguments(cfi, b);
                b->adjustGenAndKill(cfi);
                break;
            default:
                for (int i = 0; i < 3; ++i)
                    if (st->expr(i))
                        wereReplacements |= replaceVarsInExpression(st, i, b, true);
            }
        }
        else if ((st = cfi->getOriginalStatement()) != NULL)    //if, loop or funcCall statement condition expressions
        {
            if(cfi->getFunctionCall())//processed already
                continue;
            if (visitedStatements.find(st) == visitedStatements.end())
            {
                visitedStatements.insert(st);
                if (st->expr(0))
                    wereReplacements |= replaceVarsInExpression(st, 0, b, true);
            }
        }
    }
    return wereReplacements;
}

void ExpandExpressions(ControlFlowGraph* CGraph)
{
    bool wereReplacements = true;
    while (wereReplacements)
    {
        __spf_print(PRINT_PROF_INFO, "New substitution iteration\n");
        wereReplacements = false;
        visitedStatements.clear();
        ClearCFGInsAndOutsDefs(CGraph);
        FillCFGInsAndOutsDefs(CGraph, graphsKeeper.getInDefsFor(CGraph));
        CorrectInDefs(CGraph);

        for (CBasicBlock* b = CGraph->getFirst(); b != NULL; b = b->getLexNext())
        {
            b->clearGenKill(); //Needed for correct expanding within block
            if (replaceVarsInBlock(b))
                wereReplacements = true;
        }
    }
}

void processFuncCalls(ControlFlowGraph* CGraph)
{
    //TODO пребрать вызовы фунций и процедур в графе
    SgStatement* st;
    CBasicBlock* b = CGraph->getFirst();
    while (b != NULL)
    {
        b->clearGenKill();
        ControlFlowItem *cfi = b->getStart();
        ControlFlowItem *till = b->getEnd()->getNext();
        while (cfi != till)
        {

            AnalysedCallsList* call = cfi->getCall();
            if(call)
                graphsKeeper.addGraph(call->graph);
            cfi = cfi->getNext();
        }
    }
}

void processGraph(ControlFlowGraph* CGraph)
{
    printf("next graph!\n");
    SgStatement* function = CGraph->getFirst()->getStart()->getOriginalStatement();

    /*printf("%ld %ld %ld %ld \n",CGraph, CGraph->getFirst(), CGraph->getFirst()->getStart(), CGraph->getFirst()->getStart()->getOriginalStatement());
    if (function->variant() == PROG_HEDR)
    {
        SgProgHedrStmt *progH = (SgProgHedrStmt*) function;
        __spf_print(PRINT_PROF_INFO, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), function->lineNumber(), function->fileName());
    }
    else if (function->variant() == PROC_HEDR)
    {
        SgProcHedrStmt *procH = (SgProcHedrStmt*) function;
        __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), function->lineNumber(), function->fileName());
    }
    else if (function->variant() == FUNC_HEDR)
    {
        SgFuncHedrStmt *funcH = (SgFuncHedrStmt*) function;
        __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), function->lineNumber(), function->fileName());
    }*/

    printf("expanding!\n");
    ExpandExpressions(CGraph);
    processFuncCalls(CGraph);

}

static void SwitchToFile(const char *fileName) {
    for (int i = 0; i < CurrentProject->numberOfFiles(); ++i)
        if(strcmp(CurrentProject->fileName(i), fileName) == 0)
        {
            SwitchToFile(i);
            current_file = &CurrentProject->file(i);
            current_file_id = i;
        }
}

void expressionAnalyzer(SgStatement *function)
{
    __spf_print(PRINT_PROF_INFO, "Expression analyzer!\n");
    const char *prevFile = current_file->filename();
    const char *filename = function->fileName();
    SwitchToFile(filename);

    auto itRep = replacementsInFunctions.find(function);
    if (itRep == replacementsInFunctions.end())
        itRep = replacementsInFunctions.insert(itRep, make_pair(function, map<StatementObj, vector<SgExpression*>>()));
    else // replecemets are have been made alredy
    {
        revertReplacements(function);
        return;
    }
    curFunctionReplacements = &(itRep->second);



    printf("Graph!\n");

    CallData calls;
    CommonData commons;
    SetUpVars(&commons, &calls, calls.AddHeader(function, false, function->symbol(), current_file_id));
    //stage 1: preparing graph data
    ControlFlowGraph* CGraph = GetControlFlowGraphWithCalls(true, function, &calls, &commons);
    calls.AssociateGraphWithHeader(function, CGraph);
    commons.MarkEndOfCommon(GetCurrentProcedure());
    //calls.printControlFlows();


    printf("Subs!\n");

    graphsKeeper.addGraph(CGraph);

    while ((CGraph = graphsKeeper.getGraphForAdjustment()) != NULL)
        processGraph(CGraph);
    graphsKeeper.deleteGraphs();
    SwitchToFile(prevFile);
}

void expressionAnalyzer(SgFile *file)
{
    __spf_print(PRINT_PROF_INFO, "Expression analyzer!\n");

    int funcNum = file->numberOfFunctions();
    __spf_print(PRINT_PROF_INFO, "functions num in file = %d\n", funcNum);
    const string &filename = string(file->filename());

    auto itRep = replacementsInFiles.find(filename);
    if (itRep == replacementsInFiles.end())
        itRep = replacementsInFiles.insert(itRep, make_pair(filename, map<StatementObj, vector<SgExpression*>>()));
    else // replecemets are have been made alredy
    {
        revertReplacements(filename);
        return;
    }
    curFileReplacements = &(itRep->second);
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);

        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*) st;
            __spf_print(PRINT_PROF_INFO, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*) st;
            __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*) st;
            __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }

        CallData calls;
        CommonData commons;
        SetUpVars(&commons, &calls, calls.AddHeader(st, false, st->symbol(), current_file_id));
        //stage 1: preparing graph data
        ControlFlowGraph* CGraph = GetControlFlowGraphWithCalls(true, st, &calls, &commons);
        calls.AssociateGraphWithHeader(st, CGraph);
        commons.MarkEndOfCommon(GetCurrentProcedure());
        //calls.printControlFlows();

        ExpandExpressions(CGraph);

        //showDefsOfGraph(CGraph);
        /*
         st = file->firstStatement();
         while(st != NULL)
         {
         st->unparsestdout();
         st = st->nextInChildList();
         }*/
/*
         CBasicBlock* b = CGraph->getFirst();
        while (b != NULL)
        {
            printf("Block:\n");
            SgStatement* st = NULL;
            SgExpression* exp = NULL;
            ControlFlowItem *cfi = b->getStart(), *till = b->getEnd()->getNext();
            while (cfi != till)
            {
                printf("cfi: ");
                if (cfi->getFunctionCall())
                {
                    //if (cfi->getOriginalStatement())
                    //    cfi->getOriginalStatement()->unparsestdout();
                    printf("->%d %s'%s'%d <- ", cfi->getOriginalStatement(), cfi->getFunctionCall()->unparse(), cfi->getCall()->funName, cfi->getCall()->graph);
                }
                AnalysedCallsList* list = cfi->getCall();
                //                if ((st = cfi->getOriginalStatement()) != NULL)
                //              {
                //              printf("%d-%d: %s ",st->lineNumber(), st->variant(), st->unparse());
                //          }
                //        else
                if ((st = cfi->getStatement()) != NULL)
                {
                    printf("%d-%d: %s ", st->lineNumber(), st->variant(), st->unparse());
                    while (list != NULL)
                    {
                        printf("--%s'%d ", list->funName, list->graph);
                        list = list->next;
                    }
                    printf("\n");
                }
                cfi = cfi->getNext();
            }
            printf("\n");
            b = b->getLexNext();
        }
*/
        delete CGraph;
    }
}
