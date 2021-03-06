#include "../Utils/leak_detector.h"

#if _WIN32 && NDEBUG && __SPF && __BOOST
#include <boost/thread.hpp>
#endif
extern int passDone;

#include "dvm.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <iterator>
#include <fstream>
#include <chrono>

#include "../ParallelizationRegions/ParRegions.h"
#include "../ParallelizationRegions/ParRegions_func.h"
#include "../GraphLoop/graph_loops.h"
#include "../GraphCall/graph_calls.h"
#include "../GraphCall/graph_calls_func.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
#include "../Distribution/Distribution.h"
#include "../VisualizerCalls/get_information.h"
#include "expr_transform.h"

using std::pair;
using std::map;
using std::set;
using std::tuple;
using std::vector;
using std::string;
using std::iterator;
using std::make_pair;
using std::queue;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

#define PRINT_SUBSTITUTION_ABORT 1
#define PRINT_PROF_INFO 0
#define PRINT_PROF_INFO_TIME 0
/*
 * Contains original SgExpressions.
 * map <string, ...> key is a file, where replacements take place
 * map <SgStatement*, vector<SgExpression*>> key is a changed SgStetement, value - 3 SgEpression*'s
 * [i] SgExpresson* is null, if it has not been changed
 *
 * NOTE: 2 levels of replacements: first -- replace constant values, second -- replace other expressions with CFG  
 */

static map<string, map<SgStatement*, vector<SgExpression*>>> replacementsOfConstsInFiles;
static map<string, map<SgStatement*, vector<SgExpression*>>> replacementsInFiles;
static map<SgStatement*, vector<SgExpression*>>* curFileReplacements;

static set<SgStatement*> visitedStatements;
static CommonVarsOverseer overseer;
static GraphsKeeper *graphsKeeper = NULL;
static unsigned int substitutionsCounter = 0;
static void incrementSubstitutionsCounter(int print_prof_info) {
    if(print_prof_info)
        substitutionsCounter++;
}

SgStatement* findReplacedExpression(SgExpression *ex)
{
    const int id = ex->id();
    for (auto& byFile : replacementsInFiles)
    {
        for (auto& elem : byFile.second)
        {
            SgStatement* ret = elem.first;
            for (int z = 0; z < elem.second.size(); ++z)
                if (elem.second[z] == ex)
                    if (elem.second[z]->id() == id)
                        return ret;
        }
    }
    return NULL;
}

void GraphsKeeper::deleteGraphsKeeper()
{
    if(graphsKeeper)
        delete graphsKeeper;
    graphsKeeper = NULL;
}

GraphsKeeper* GraphsKeeper::getGraphsKeeper() {
    if(graphsKeeper == NULL)
        graphsKeeper = new GraphsKeeper();
    return graphsKeeper;
}

GraphItem* GraphsKeeper::buildGraph(SgStatement* st)
{
    GraphItem* result = new GraphItem();

    SetUpVars(&result->commons, &result->calls, result->calls.AddHeader(st, false, st->symbol(), current_file_id), &result->dldl);

    result->CGraph = GetControlFlowGraphWithCalls(true, st, &result->calls, &result->commons);
    result->calls.AssociateGraphWithHeader(st, result->CGraph);
    result->commons.MarkEndOfCommon(GetCurrentProcedure());
    result->file_id = current_file_id;

    /*std::fstream fs;
    fs.open("graph.txt", std::fstream::out);
    fs << result->CGraph->GetVisualGraph(&result->calls);
    fs.close();*/

    auto inserted = graphs.insert(make_pair(st, result));
    return inserted.first->second;
}


GraphItem* GraphsKeeper::getGraph(SgStatement *header)
{
    auto it = graphs.find(header);
    if (it == graphs.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    GraphItem* res = graphs.find(header)->second;
    CurrentProject->file(res->file_id);
    return res;
}

CBasicBlock* GraphsKeeper::findBlock(SgStatement* stmt)
{
    for(auto &graph : graphs) {
        if(graph.second->file_id != stmt->getFileId())
            continue;

        stmt->switchToFile();

        CBasicBlock *b = graph.second->CGraph->getFirst();
        while(b != NULL)
        {
            ControlFlowItem *cfi = b->getStart();
            ControlFlowItem *till = b->getEnd()->getNext();
            while(cfi != till)
            {
                SgStatement *st = cfi->getStatement();
                if(st && st->id() == stmt->id())
                    return b;
                st = cfi->getOriginalStatement();
                if(st && st->id() == stmt->id())
                    return b;
                cfi = cfi->getNext();
            }
            b = b->getLexNext();
        }
    }
    return NULL;
}

bool findCFIsForStmt(SgStatement *stmt, vector <ControlFlowItem*> &cfis) {
    CBasicBlock* b = GraphsKeeper::getGraphsKeeper()->findBlock(stmt);
    if(!b)
        return false;

    ControlFlowItem *cfi = b->getStart();
    ControlFlowItem *till = b->getEnd()->getNext();

    while (cfi != till)
    {
        SgStatement *st = cfi->getStatement();
        if (st && st->id() == stmt->id())
            cfis.push_back(cfi);
        else {
            st = cfi->getOriginalStatement();
            if (st && st->id() == stmt->id())
                cfis.push_back(cfi);
        }
        cfi = cfi->getNext();
    }

    return cfis.size() != 0;

}

const map<SymbolKey, set<ExpressionValue*>> getReachingDefinitionsExt(SgStatement* stmt)
{
    CBasicBlock* b = GraphsKeeper::getGraphsKeeper()->findBlock(stmt);
    if(!b)
        return map<SymbolKey, set<ExpressionValue*>>();

    return b->getReachedDefinitionsExt(stmt);
}

static void revertReplacements(map<SgStatement*, vector<SgExpression*>> &toRev, bool constant = false)
{
    for (auto &toReplace : toRev)
    {
        SgStatement *parent = toReplace.first;
        for (int i = 0; i < 3; ++i)
        {
            if (toReplace.second[i] != NULL)
            {
                SgExpression *replacement = parent->expr(i);
                parent->setExpression(i, *(toReplace.second[i]));
                toReplace.second[i] = replacement;
            }
        }
    }
}

void revertReplacements(const string &filename, bool back)
{
    auto constF = replacementsOfConstsInFiles.find(filename);
    auto tmpF = replacementsInFiles.find(filename);

    if (back)
    {
        if (tmpF != replacementsInFiles.end())
            revertReplacements(tmpF->second);
        if (constF != replacementsOfConstsInFiles.end())
            revertReplacements(constF->second, true);
    }
    else
    {        
        if (constF != replacementsOfConstsInFiles.end())
            revertReplacements(constF->second, true);
        if (tmpF != replacementsInFiles.end())
            revertReplacements(tmpF->second);
    }    
}

static SgExpression* getFromConstructor(SgExpression *e, int num)
{
    int i = 1;
    while (e)
    {
        if (i == num)
            return e->lhs();
        ++i;
        e = e->rhs();
    }

    return NULL;
}

SgExpression* ReplaceParameter(SgExpression *e)
{
    if (!e)
        return e;
    
    if (e->variant() == CONST_REF)
    {
        auto t1 = e->type();
        auto t2 = e->symbol()->type();

        SgConstantSymb *sc = isSgConstantSymb(e->symbol());
        if (!sc->constantValue())
            return e;
        auto val = sc->constantValue();
        auto typeVal = val->type();
        //if type of constant does not match type of variable
        if (e->symbol()->type()->variant() == T_DOUBLE && val->variant() == FLOAT_VAL && typeVal->variant() == T_FLOAT)
        {
            char* digit_o = ((SgValueExp*)val)->floatValue();
            SgExpression* val = typeVal->selector();

            char* digit = new char[strlen(digit_o) + 2];
            strcpy(digit, digit_o);
            digit[strlen(digit_o)] = 'f';
            digit[strlen(digit_o) + 1] = '\0';

            SgValueExp* valDouble = new SgValueExp(double(0.0), digit);
            delete[]digit;

            if (val != NULL)
            {
                if (val->valueInteger() == 8) // double
                    return sc->constantValue()->copyPtr();
                else if (val->valueInteger() == 4) // float
                    return valDouble;
                else
                    return valDouble;
            }
            else
                return valDouble;
        }
        else
            return (ReplaceParameter(&(sc->constantValue()->copy())));
    }
    else if (e->variant() == ARRAY_REF)
    {
        SgConstantSymb *sc = isSgConstantSymb(e->symbol());
        if (sc)
        {            
            SgExpression *constructor = sc->constantValue();
            SgArrayRefExp *ref = isSgArrayRefExp(e);
            if (ref->numberOfSubscripts() == 1)
            {
                auto sub = ref->subscript(0);
                if (sub->isInteger())
                {
                    int num = sub->valueInteger();
                    SgExpression *value = getFromConstructor(constructor->lhs(), num);
                    if (value && ((value->lhs() == NULL && value->rhs() == NULL) || value->variant() == MINUS_OP))
                        return (ReplaceParameter(&(value->copy())));
                }
            }
        }
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
    case UNARY_ADD_OP:
        if (lErr != -1)
            result = make_pair(+lRes.first, lRes.second);
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
        int sign = 1;
        SgExpression* toCalc = ret;
        if (ret->variant() == UNARY_ADD_OP)
            toCalc = ret->lhs();
        if (ret->variant() == MINUS_OP)
        {
            toCalc = ret->lhs();
            sign = -1;
        }
        if (toCalc->isInteger())
            exp = new SgValueExp(sign * toCalc->valueInteger());
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
        case UNARY_ADD_OP:
            if (err.first != -1)
            {
                result = res.first;
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
            else if(err.first != -1 && res.first == 0)
            {
                result = 0;
                return 0;
            }
            else if (err.second != -1 && res.second == 0)
            {
                result = 0;
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

SgExpression* CalculateInteger(SgExpression *expr)
{
    int value, res;
    replaceConstatRec(expr);
    res = CalculateInteger(expr, value);
    if (res != -1)
        return new SgValueExp(value);
    else
        return expr;
}

void calculate(SgExpression *&exp)
{
    SgExpression *left, *right;
    int res, err;

    if ((left = exp->lhs()) != NULL)
    {
        err = CalculateInteger(left, res);
        if (err != -1)
            exp->setLhs(new SgValueExp(res));
        else
            calculate(left);
    }

    if ((right = exp->rhs()) != NULL)
    {
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

static SgExpression* valueOfVar(SgExpression *var, CBasicBlock *b)
{
    SgExpression *exp = NULL;
    //first, check previous defs within block
    auto founded = b->getGen()->find(SymbolKey(var->symbol()));
    if (founded != b->getGen()->end())
        if (!valueWithFunctionCall(founded->second->getExp()))
            if (!valueWithRecursion(founded->first, founded->second->getExp()))
                if(!valueWithArrayReference(founded->second->getExp()))
                    if(b->expressionIsAvailable(founded->second))
                        exp = founded->second->getExp();


    if (exp == NULL)
    {
        //second, check defs from previous blocks
        auto founded_inDefs = b->getInDefs()->find(SymbolKey(var->symbol()));
        if (founded_inDefs != b->getInDefs()->end())
        {
            //if smth is founded_inDefs, it has single value
            //thanks to CorrectInDefs(ControlFlowGraph*) function
            ExpressionValue *expVal = *(founded_inDefs->second.begin());
            //we have to check if this value was killed inside block
            if(b->expressionIsAvailable(expVal))
                exp = expVal->getExp();
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
        auto inserted = curFileReplacements->insert(make_pair(stmt, vector<SgExpression*>()));
        foundedParent = inserted.first;
        foundedParent->second.resize(3);
        for (int i = 0; i < 3; ++i)
            foundedParent->second[i] = NULL;
    }

    if (foundedParent->second[expNumber] == NULL)
    {
        SgExpression *expToCopy = exp->copyPtr();
        foundedParent->second[expNumber] = expToCopy;
                
        const string orig = string(exp->unparse());
        const string copy = string(expToCopy->unparse());
        if (orig == copy)
            createLinksToCopy(exp, expToCopy);
    }
}

static SgExpression* tryMakeInt(SgExpression* exp)
{
    if (exp->variant() != INT_VAL)
        if (exp->isInteger())
            return new SgValueExp(exp->valueInteger());
    return exp;
}

static bool typesAreTheSame(SgExpression *oldExp, SgExpression *newExp, int lineNumber) 
{
    paramType oldType = detectExpressionType(oldExp);
    paramType newType = detectExpressionType(newExp);
    if(oldType != newType) 
    {
        char* tmp = oldExp->unparse();
        __spf_print(PRINT_SUBSTITUTION_ABORT, "%d: Substitution aborted %s -> ", lineNumber, tmp);
        __spf_print(PRINT_SUBSTITUTION_ABORT, "%s. Types do not match: %s != %s\n", newExp->unparse(), paramNames[oldType], paramNames[newType]);
        return false;
    }

    return true;
}

static bool setNewSubexpression(SgExpression *parent, bool rightSide, SgExpression *newExp, const int lineNumber)
{
    SgExpression *oldExp = rightSide ? parent->rhs() : parent->lhs();

    __spf_print(PRINT_PROF_INFO, "%d: %s -> ",lineNumber, oldExp->unparse());
    __spf_print(PRINT_PROF_INFO, "%s\n", newExp->unparse());
    incrementSubstitutionsCounter(PRINT_PROF_INFO);

    SgExpression* expToCopy = newExp->copyPtr();
    calculate(expToCopy);

    rightSide ? parent->setRhs(tryMakeInt(expToCopy)) : parent->setLhs(tryMakeInt(expToCopy));

    return true;
}

static bool replaceVarsInExpression(SgStatement *parent, int expNumber, CBasicBlock *b, bool replaceFirstVar)
{
    queue<SgExpression*> toCheck;
    bool wereReplacements = false;
    SgExpression* exp = parent->expr(expNumber);
    if (exp->variant() == VAR_REF && !replaceFirstVar)
        return false;

    //If SgExpression is a single VAR
    if (exp->variant() == VAR_REF)
    {
        SgExpression* newExp = valueOfVar(exp, b);
        if (newExp != NULL && typesAreTheSame(exp, newExp, parent->lineNumber()))
        {
            createBackup(parent, expNumber);

            __spf_print(PRINT_PROF_INFO, "%d: %s -> ",parent->lineNumber(), exp->unparse());
            __spf_print(PRINT_PROF_INFO, "%s\n", newExp->unparse());
            incrementSubstitutionsCounter(PRINT_PROF_INFO);
            SgExpression* expToCopy = newExp->copyPtr();
            calculate(expToCopy);
            parent->setExpression(expNumber, *(tryMakeInt(expToCopy)));
            return true;
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
                    if (newExp != NULL && typesAreTheSame(exp->rhs(), newExp, parent->lineNumber()))
                    {
                        createBackup(parent, expNumber);
                        wereReplacements |= setNewSubexpression(exp, true, newExp, parent->lineNumber());
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
                        if (newExp != NULL && typesAreTheSame(exp->lhs(), newExp, parent->lineNumber()))
                        {
                            createBackup(parent, expNumber);
                            wereReplacements |= setNewSubexpression(exp, false, newExp, parent->lineNumber());
                        }
                    }
                    else
                        toCheck.push(exp->lhs());
                }
        }
    }
    return wereReplacements;
}

static bool needReplacements(SgExpression* exp, map<SymbolKey, vector<SgExpression*>>* ins, bool checkVar)
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

static bool replaceVarsInCallArgument(SgExpression *exp, const int lineNumber, CBasicBlock *b)
{
    bool wereReplacements = false;
    SgExpression *lhs = exp->lhs(), *rhs = exp->rhs();

    if(lhs && lhs->variant() != FUNC_CALL)     //We don't want expand arguments of other functions.
    {
        if(lhs->variant() == VAR_REF)
        {
            SgExpression* newExp = valueOfVar(lhs, b);
            if (newExp != NULL && typesAreTheSame(lhs, newExp, lineNumber))
            {
                wereReplacements |= setNewSubexpression(exp, false, newExp, lineNumber);
            }
        }
        else
            wereReplacements |= replaceVarsInCallArgument(lhs, lineNumber, b);
    }

    if(rhs && rhs->variant() != FUNC_CALL)    //We don't want expand arguments of other functions
    {
        if(rhs->variant() == VAR_REF)
        {
            SgExpression* newExp = valueOfVar(rhs, b);
            if (newExp != NULL && typesAreTheSame(rhs, newExp, lineNumber))
            {
                wereReplacements |= setNewSubexpression(exp, true, newExp, lineNumber);
            }
        }
        else
            wereReplacements |= replaceVarsInCallArgument(rhs, lineNumber, b);
    }

    return wereReplacements;
}

static bool replaceCallArguments(ControlFlowItem *cfi, CBasicBlock *b)
{
    bool wereReplacements = false;
    int numberOfArgs = 0, lineNumber = 0;
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
        lineNumber = callStmt->lineNumber();
    }
    else if ((funcCall = cfi->getFunctionCall()) != NULL) //functionCall
    {
        st = cfi->getOriginalStatement();
        for (int i = 0; i < 3; ++i)
            if (st->expr(i))// TODO: search for expression?
                createBackup(st, i);
        args = funcCall->lhs();
        lineNumber = st->lineNumber();
        numberOfArgs = funcCall->numberOfArgs();
    }

    if (args)
    {
        for (int i = 0; i < numberOfArgs; ++i)
        {
            arg = args->lhs();

            if (arg->variant() == VAR_REF && argIsReplaceable(i, callData))
            {
                SgExpression* newExp = valueOfVar(arg, b);
                if (newExp != NULL && typesAreTheSame(arg, newExp, lineNumber))
                {
                    wereReplacements |= setNewSubexpression(args, false, newExp, lineNumber);
                }
            }
            else if (arg->variant() != VAR_REF)
                wereReplacements |= replaceVarsInCallArgument(arg, lineNumber, b);
            args = args->rhs();
        }
    }

    return wereReplacements;
}

/*
 * Have to run b->adjustGenAndKill(cfi) here to track changes inside block.
 */
static bool replaceVarsInBlock(CBasicBlock* b)
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
            case READ_STAT:
                //TODO ????????????-???? ?????????????????????? ???????????? ???????????? ????????????????????, ?? ?????????????? ???????????????? ??????????, ???? ???????????? ?????
                b->adjustGenAndKill(cfi);
                break;
            case POINTER_ASSIGN_STAT:
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

void ExpandExpressions(ControlFlowGraph* CGraph, map<SymbolKey, set<ExpressionValue*>> &inDefs)
{
    bool wereReplacements = true;
    while (wereReplacements)
    {
        createNeededException();
        __spf_print(PRINT_PROF_INFO_TIME, "New substitution iteration\n");
        
        auto time = high_resolution_clock::now();
        wereReplacements = false;
        visitedStatements.clear();

        __spf_print(PRINT_PROF_INFO_TIME, " clear vis %f\n", 
                    duration_cast<milliseconds>(high_resolution_clock::now() - time).count() / 1000.);
        time = high_resolution_clock::now();

        ClearCFGInsAndOutsDefs(CGraph);
        __spf_print(PRINT_PROF_INFO_TIME, " clear CFG %f\n", 
                    duration_cast<milliseconds>(high_resolution_clock::now() - time).count() / 1000.);
        time = high_resolution_clock::now();

        FillCFGInsAndOutsDefs(CGraph, &inDefs, &overseer);
        __spf_print(PRINT_PROF_INFO_TIME, " fill %f\n", 
                    duration_cast<milliseconds>(high_resolution_clock::now() - time).count() / 1000.);
        time = high_resolution_clock::now();

        CorrectInDefs(CGraph);
        __spf_print(PRINT_PROF_INFO_TIME, " correct %f\n", 
                    duration_cast<milliseconds>(high_resolution_clock::now() - time).count() / 1000.);
        time = high_resolution_clock::now();

        for (CBasicBlock* b = CGraph->getFirst(); b != NULL; b = b->getLexNext())
        {
            b->clearGenKill(); //Needed for correct expanding within block
            if (replaceVarsInBlock(b))
                wereReplacements = true;
        }
        __spf_print(PRINT_PROF_INFO_TIME, " replace %f\n", 
                    duration_cast<milliseconds>(high_resolution_clock::now() - time).count() / 1000.);
    }
}

void BuildUnfilteredReachingDefinitions(ControlFlowGraph* CGraph, map<SymbolKey, set<ExpressionValue*>> &inDefs, const string &filename)
{
    __spf_print(PRINT_PROF_INFO, "Building unfiltered reaching definitions\n");

    visitedStatements.clear();
    ClearCFGInsAndOutsDefs(CGraph);
    FillCFGInsAndOutsDefs(CGraph, &inDefs, &overseer);

    /* Showtime */
//    showDefsOfGraph(CGraph);
//    debugStructure(CGraph, filename);
}

ControlFlowGraph* BuildUnfilteredReachingDefinitionsFor(SgStatement *header) 
{
    auto inDefs = createHeaderInDefs(header);
    ControlFlowGraph *CGraph = GraphsKeeper::getGraphsKeeper()->getGraph(header)->CGraph;
    BuildUnfilteredReachingDefinitions(CGraph, inDefs, header->getFile()->filename());
    return CGraph;
}

static void initOverseer(const map<string, vector<DefUseList>> &defUseByFunctions, const map<string, CommonBlock> &commonBlocks, const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    vector<FuncCallSE> funcCalls;
    for(auto &file : allFuncInfo)
        for(auto& funcInfo : file.second)
            funcCalls.push_back(FuncCallSE(funcInfo->funcName, funcInfo->callsFrom));

    for (auto &commonBlock : commonBlocks)
        for (auto &var : commonBlock.second.getVariables())
            if (var.getType() == SCALAR)
                for (auto &fun : var.getAllUse())
                {
                    bool deffed = false;
                    auto func = fun.getFunctionName();
                    auto foundedDefUse = defUseByFunctions.find(func);
                    if (foundedDefUse != defUseByFunctions.end())
                        for (auto &varDefUse : foundedDefUse->second)
                            if (varDefUse.isDef() && varDefUse.getVar() == var.getName())
                            {
                                deffed = true;
                                break;
                            }
                    if (deffed)
                    {
                        queue<string> killerFuncs = queue<string>();
                        set<string> processed = set<string>();
                        killerFuncs.push(fun.getFunctionName());
                        while (!killerFuncs.empty())
                        {
                            string& curFunc = killerFuncs.front();
                            processed.insert(curFunc);
                            killerFuncs.pop();
                            for (auto &file : allFuncInfo)
                                for (auto &funcInfo : file.second)
                                    if (funcInfo->callsFrom.find(curFunc) != funcInfo->callsFrom.end() &&
                                            processed.find(funcInfo->funcName) == processed.end())
                                        killerFuncs.push(funcInfo->funcName);
                            overseer.addKilledVar(var.getSymbol(), fun.getFunctionName());
                        }
                    }
                }
    overseer.riseInited();
}

static bool findConstRef(SgExpression *ex)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == CONST_REF)
            return true;

        ret = ret || findConstRef(ex->lhs());
        ret = ret || findConstRef(ex->rhs());
    }
    return ret;
}

/*static void copyAttributes(SgExpression *ex, SgExpression *copy)
{
    if (ex && copy)
    {
        if (ex->numberOfAttributes())
            copy->addAttributeTree(ex->getAttribute(0));
        copyAttributes(ex->lhs(), copy->lhs());
        copyAttributes(ex->rhs(), copy->rhs());
    }
}*/

static void replaceOrigFuncSymbols(SgExpression* ex, SgExpression* copy)
{
    if (ex && copy)
    {
        if (ex->variant() == FUNC_CALL)
            copy->setSymbol(ex->symbol());
        replaceOrigFuncSymbols(ex->lhs(), copy->lhs());
        replaceOrigFuncSymbols(ex->rhs(), copy->rhs());
    }
}

static void replaceConstants(const string &file, SgStatement *st)
{
    auto it = replacementsOfConstsInFiles.find(file);
    if (it == replacementsOfConstsInFiles.end())    
        it = replacementsOfConstsInFiles.insert(it, make_pair(file, map<SgStatement*, vector<SgExpression*>>()));
        
    auto last = st->lastNodeOfStmt();
    for (SgStatement *currS = st; currS != last; currS = currS->lexNext())
    {
        if (currS->variant() == CONTAINS_STMT)
            break;

        if (isSgExecutableStatement(currS))
        {
            vector<SgExpression*> toRepl = { NULL, NULL, NULL };
            vector<SgExpression*> original = { NULL, NULL, NULL };

            for (int i = 0; i < 3; ++i)
            {
                if (findConstRef(currS->expr(i)))
                {
                    original[i] = currS->expr(i)->copyPtr();

                    SgExpression *copy = ReplaceConstant(original[i]);
                    calculate(copy);
                    toRepl[i] = copy;

                    currS->setExpression(i, *copy);
                }
            }

            if (toRepl[0] || toRepl[1] || toRepl[2])
            {
                it->second[currS] = original;
                for (int z = 0; z < 3; ++z)
                    replaceOrigFuncSymbols(currS->expr(z), original[z]);
            }
        }
    }
}

static bool isInParallelRegion(SgStatement *func, const vector<ParallelRegion*> &regions)
{
    bool ok = false;
    auto last = func->lastNodeOfStmt();
    for (auto st = func; st != last; st = st->lexNext())
    {
        if (getAllRegionsByLine(regions, st->fileName(), st->lineNumber()).size())
        {
            ok = true;
            break;
        }
    }

    return ok;
}

map<SymbolKey, set<ExpressionValue*>> createHeaderInDefs(SgStatement *header) {
    map<SymbolKey, set<ExpressionValue*>> inDefs;
    ExpressionValue* emptyValue = allocateExpressionValue(NULL, NULL);
    emptyValue->setFrom(header);
    if(header->variant() == PROC_HEDR || header->variant() == FUNC_HEDR)
        for(int i=0; i<((SgProcHedrStmt*)header)->numberOfParameters();++i)
            inDefs.insert(make_pair(((SgProcHedrStmt*)header)->parameter(i), set<ExpressionValue*>()))
            .first->second.insert(emptyValue);
    return inDefs;
}

void expressionAnalyzer(SgFile *file, const map<string, vector<DefUseList>> &defUseByFunctions, 
                        const map<string, CommonBlock> &commonBlocks, const map<string, vector<FuncInfo*>> &allFuncInfo,
                        const vector<ParallelRegion*> &regions)
{
    if(!overseer.isInited())
        initOverseer(defUseByFunctions, commonBlocks, allFuncInfo);

    int funcNum = file->numberOfFunctions();
    __spf_print(PRINT_PROF_INFO, "functions num in file = %d\n", funcNum);
    const string filename = file->filename();

    auto itRep = replacementsInFiles.find(filename);
    if (itRep == replacementsInFiles.end())
        itRep = replacementsInFiles.insert(itRep, make_pair(filename, map<SgStatement*, vector<SgExpression*>>()));
    else // replecemets are have been made already
    {
        revertReplacements(filename);
        return;
    }
    curFileReplacements = &(itRep->second);

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);

        if (isInParallelRegion(st, regions) == false)
        {
            __spf_print(1, "  skip function '%s\n", st->symbol()->identifier());
            continue;
        }

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


        GraphsKeeper* gk = GraphsKeeper::getGraphsKeeper();

        replaceConstants(filename, st);

        ControlFlowGraph* CGraph = gk->buildGraph(st)->CGraph;

        auto inDefs = createHeaderInDefs(st);
        ExpandExpressions(CGraph, inDefs);

        __spf_print(PRINT_PROF_INFO, "%u total substitutions\n", substitutionsCounter);
    }

    for (auto &stmt : *curFileReplacements)
    {
        for (int i = 0; i < 3; ++i)
        {
            auto expr = stmt.first->expr(i);
            if (expr)
            {
                calculate(expr);
                stmt.first->setExpression(i, *expr);
            }
        }
    }

    const string fileName = file->filename();
    int fileId = -1;
    for (SgStatement* st = file->firstStatement(); st; st = st->lexNext())
    {
        if (st->fileName() == fileName)
        {
            fileId = st->getFileId();
            break;
        }
    }

    if (fileId != -1)
        deleteAllocatedExpressionValues(fileId);
}

void runPrivateAnalysis(SgStatement *main)
{
    if (main->variant() != PROG_HEDR)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    GraphsKeeper *gk = GraphsKeeper::getGraphsKeeper();

    GraphItem *gItem = gk->getGraph(main);
    ControlFlowGraph *graph = gItem->CGraph;
    if (gItem->privateDone == false)
    {
        graph->privateAnalyzer();
        gItem->privateDone = true;
    }
}
