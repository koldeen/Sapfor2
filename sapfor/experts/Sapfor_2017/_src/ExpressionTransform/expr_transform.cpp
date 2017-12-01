#include "../leak_detector.h"

#include "dvm.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <iterator>

#include "acc_analyzer.h"

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
//map<string, map<pair<pair<void*, REPLACE_PTR_TYPE>, int>, pair<SgExpression*, int>>> replacementsInFiles;

set<SgStatement*> visitedStatements;

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
            if (it->second[i] != NULL)
            {
                SgExpression* replacement = parent->expr(i);
                parent->setExpression(i, *(it->second[i]));
                it->second[i] = replacement;
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
                result = make_pair(lRes.first  *rRes.second + rRes.first  *lRes.second, lRes.second  *rRes.second);
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
                result = res.first  *res.second;
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
    if(founded != b->getGen()->end())
        if(!valueWithFunctionCall(founded->second))
            if(!valueWithRecursion(founded->first, founded->second))
                exp = founded->second;

    //second, check defs from previous blocks
    auto founded_inDefs = b->getInDefs()->find(SymbolKey(var->symbol()));
    if(founded_inDefs != b->getInDefs()->end())
        //if smth is founded_inDefs, it has single value
        //thanks to CorrectInDefs(ControlFlowGraph*) function
        exp = founded_inDefs->second.begin()->second;

    return exp;
}

void createBackup(SgStatement* stmt, int expNumber)
{
    SgExpression* exp = stmt->expr(expNumber);
    auto foundedParent = curFileReplacements->find(stmt);
    if(foundedParent == curFileReplacements->end())
    {
        auto inserted = curFileReplacements->insert(std::make_pair(StatementObj(stmt), vector<SgExpression*>()));
        foundedParent = inserted.first;
        foundedParent->second.resize(3);
        for(int i=0;i<2;++i)
            foundedParent->second[i] = NULL;
    }
    if(foundedParent->second[expNumber] == NULL)
    {
        SgExpression* expToCopy = exp->copyPtr();
        foundedParent->second[expNumber] = expToCopy;
    }
}

bool replaceVarsInExpression(SgStatement *parent, int expNumber, CBasicBlock *b, bool replaceFirstVar)
{
    std::queue<SgExpression*> toCheck;
    bool wereReplacements = false;
    SgExpression* exp = parent->expr(expNumber);
    if(exp->variant() == VAR_REF && !replaceFirstVar)
        return wereReplacements;

    //If SgExpression is a single VAR
    if(exp->variant() == VAR_REF)
    {
        SgExpression* newExp = valueOfVar(exp, b);
        if(newExp != NULL)
        {
            createBackup(parent, expNumber);
            print(PRINT_PROF_INFO, "%s -> ", exp->unparse());
            print(PRINT_PROF_INFO, "%s\n", newExp->unparse());
            SgExpression* expToCopy = newExp->copyPtr();
            parent->setExpression(expNumber, *expToCopy);
            wereReplacements = true;
        }
    }//If not :)
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
                        print(PRINT_PROF_INFO, "%s -> ", exp->rhs()->unparse());
                        print(PRINT_PROF_INFO, "%s\n", newExp->unparse());
                        SgExpression* expToCopy = newExp->copyPtr();
                        exp->setRhs(expToCopy);
                        wereReplacements = true;
                    }
                }
                else
                    toCheck.push(exp->rhs());
            }
            if (exp->lhs())
            {
                if (exp->lhs()->variant() == VAR_REF)
                {
                    SgExpression* newExp = valueOfVar(exp->lhs(), b);
                    if (newExp != NULL)
                    {
                        createBackup(parent, expNumber);
                        print(PRINT_PROF_INFO, "%s -> ", exp->lhs()->unparse());
                        print(PRINT_PROF_INFO, "%s\n", newExp->unparse());
                        SgExpression* expToCopy = newExp->copyPtr();
                        exp->setLhs(expToCopy);
                        wereReplacements = true;
                    }
                }
                else
                    toCheck.push(exp->lhs());
            }
        }
    }

    exp = parent->expr(expNumber);
    if(exp->variant() != INT_VAL)
        if(exp->isInteger())
        {
            SgExpression* intExp = new SgValueExp(exp->valueInteger());
            parent->setExpression(expNumber, *intExp);
            //parent-> = new SgValueExp(exp->valueInteger());
        }
    return wereReplacements;
}

bool needReplacements(SgExpression* exp, map<SymbolKey, std::vector<SgExpression*>>* ins, bool checkVar)
{
    if(exp->variant() == VAR_REF)
    {
        if(checkVar)
            for(auto it = ins->begin(); it != ins->end(); ++it)
                if(it->first == exp->symbol())
                    return true;
        return false;
    }
    else
    {
        bool needReplacement = false;
        if(exp->rhs())
            needReplacement = needReplacements(exp->rhs(), ins, true);
        if(exp->lhs() && !needReplacement)
            needReplacement = needReplacements(exp->lhs(), ins, true);
        return needReplacement;
    }
}

bool replaceVarsInBlock(CBasicBlock* b)
{
    bool wereReplacements = false;
    SgStatement* st;
    for (ControlFlowItem* cfi = b->getStart(); cfi != b->getEnd()->getNext(); cfi = cfi->getNext())
        if ((st = cfi->getStatement()) != NULL)
        {

            if(isDVM_stat(st))
                continue;
            if(isSPF_stat(st))
                continue;

            switch (st->variant())
            {
            case ASSIGN_STAT:
                wereReplacements |= replaceVarsInExpression(st, 0, b, false);
                wereReplacements |= replaceVarsInExpression(st, 1, b, true);
                b->adjustGenAndKill(st);
                break;
            default:
                if(st->expr(0))
                    wereReplacements |= replaceVarsInExpression(st, 0, b, true);
                if(st->expr(1))
                    wereReplacements |= replaceVarsInExpression(st, 1, b, true);
                if(st->expr(2))
                    wereReplacements |= replaceVarsInExpression(st, 2, b, true);
                b->adjustGenAndKill(st);
            }
        }
        else if((st = cfi->getOriginalStatement()) != NULL)//if or loop statement condition expressions
        {
            if(visitedStatements.find(st) == visitedStatements.end())
            {
                visitedStatements.insert(st);
                if (st->expr(0))
                    wereReplacements |= replaceVarsInExpression(st, 0, b, true);
                /*if (st->expr(1))
                    wereReplacements |= replaceVarsInExpression(st, 1, b, true);
                if (st->expr(2))
                    wereReplacements |= replaceVarsInExpression(st, 2, b, true);*/
            }
        }
    return wereReplacements;
}

void ExpandExpressions(ControlFlowGraph* CGraph) 
{
    bool wereReplacements = true;
    while(wereReplacements)
    {
        print(PRINT_PROF_INFO, "New substitution iteration\n");
        wereReplacements = false;
        visitedStatements.clear();
        ClearCFGInsAndOutsDefs(CGraph);
        FillCFGInsAndOutsDefs(CGraph);
        CorrectInDefs(CGraph);

        for(CBasicBlock* b = CGraph->getFirst(); b != NULL ; b = b->getLexNext())
        {
            b->clearGenKill(); //Needed for correct expanding within block
            if(replaceVarsInBlock(b))
                wereReplacements = true;
        }
    }
}

void expressionAnalyzer(SgFile *file, vector<Messages> &messagesForFile)
{
    print(PRINT_PROF_INFO, "Expression analyzer!\n");
    
    int funcNum = file->numberOfFunctions();
    print(PRINT_PROF_INFO, "functions num in file = %d\n", funcNum);
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
        SgStatement *lastNode = st->lastNodeOfStmt();

        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*) st;
            print(PRINT_PROF_INFO, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*) st;
            print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*) st;
            print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), st->lineNumber(), st->fileName());
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
        delete CGraph;
    }
}
