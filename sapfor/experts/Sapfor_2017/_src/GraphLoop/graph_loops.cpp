#include "../leak_detector.h"

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
#include "../ParallelizationRegions/ParRegions_func.h"
#include "../ExpressionTransform/expr_transform.h"

#include "../Distribution/GraphCSR.h"
#include "../Distribution/Arrays.h"
#include "../Distribution/Distribution.h"

#include "graph_loops.h"
#include "../utils.h"

#include "../errors.h"
#include "../AstWrapper.h"

using std::vector;
using std::map;
using std::set;
using std::string;
using std::pair;

#define DEBUG 0
static inline void insertLabels(SgExpression *lb, map<int, vector<int>> &gotoLabels, const int line)
{
    while (lb)
    {
        SgLabel *lab = ((SgLabelRefExp *)(lb->lhs()))->label();
        gotoLabels[lab->getLabNumber()].push_back(line);
        lb = lb->rhs();
    }
}

static bool recVariantFind(SgExpression *ex, const int var)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == var)
            return true;

        ret = ret || recVariantFind(ex->lhs(), var);
        ret = ret || recVariantFind(ex->rhs(), var);
    }

    return ret;
}

static bool recScalaraSymbolFind(SgExpression *ex, const string &symb)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == VAR_REF)
        {
            if (ex->symbol())
                if (ex->symbol()->identifier() == symb)
                    return true;
        }

        ret = ret || recScalaraSymbolFind(ex->lhs(), symb);
        ret = ret || recScalaraSymbolFind(ex->rhs(), symb);
    }

    return ret;
}

static inline void processLables(SgStatement *curr, map<int, vector<int>> &labelsList)
{
    if (curr->variant() == GOTO_NODE)
    {
        SgGotoStmt *gotoS = (SgGotoStmt *)curr;
        labelsList[gotoS->branchLabel()->getLabNumber()].push_back(curr->lineNumber());
    }
    else if (curr->variant() == ARITHIF_NODE)
    {
        SgExpression *lb = curr->expr(1);
        insertLabels(lb, labelsList, curr->lineNumber());
    }
    else if (curr->variant() == COMGOTO_NODE)
    {
        SgExpression *lb = ((SgComputedGotoStmt*)curr)->labelList();
        insertLabels(lb, labelsList, curr->lineNumber());
    }
    else if (curr->variant() == PRINT_STAT)
    {
        SgInputOutputStmt *ioStat = (SgInputOutputStmt*)curr;
        SgExpression *spec = ioStat->specList();
        if (spec)
        {
            if (spec->rhs())
            {
                if (spec->rhs()->variant() == LABEL_REF)
                {
                    SgLabelRefExp *labRef = (SgLabelRefExp*)spec->rhs();
                    if (labRef->label())
                        labelsList[labRef->label()->getLabNumber()].push_back(curr->lineNumber());
                }
            }
        }
    }
    else if (curr->variant() == WRITE_STAT)
    {
        SgInputOutputStmt *ioStat = (SgInputOutputStmt*)curr;
        SgExpression *spec = ioStat->specList();
        if (spec->rhs())
        {
            if (spec->rhs()->lhs())
            {
                if (spec->rhs()->lhs()->rhs())
                {
                    if (spec->rhs()->lhs()->rhs()->variant() == LABEL_REF)
                    {
                        SgLabelRefExp *labRef = (SgLabelRefExp*)spec->rhs()->lhs()->rhs();
                        if (labRef->label())
                            labelsList[labRef->label()->getLabNumber()].push_back(curr->lineNumber());
                    }
                }
            }
        }
    }
}

static inline bool hasGoto(SgStatement *loop, vector<int> &linesOfIntGoTo, vector<int> &linesOfExtGoTo, const map<int, vector<int>> &labelsRef)
{
    bool has = false;
    SgStatement *end = loop->lastNodeOfStmt();
    SgStatement *curr = loop->lexNext();
    map<int, vector<int>> gotoLabels;
    map<int, vector<int>> inForLabels;

    while (curr != end)
    {
        if (curr->hasLabel())
            inForLabels[curr->label()->getLabNumber()].push_back(curr->lineNumber());

        for (int i = 0; i < 3; ++i)
        {
            if (curr->expr(i))
            {
                if (recVariantFind(curr->expr(i), EXIT_STMT))
                {
                    linesOfIntGoTo.push_back(curr->lineNumber());
                    has = true;
                }
            }
        }

        processLables(curr, gotoLabels);

        if (curr->variant() == EXIT_STMT)
        {
            linesOfIntGoTo.push_back(curr->lineNumber());
            has = true;
        }
        curr = curr->lexNext();
    }

    // if loop has not labels from goto 
    for (auto it = gotoLabels.begin(); it != gotoLabels.end(); ++it)
    {
        if (inForLabels.find(it->first) == inForLabels.end())
        {
            has = true;
            for (int z = 0; z < it->second.size(); ++z)
                linesOfIntGoTo.push_back(it->second[z]);
        }
    }
        
    // if loop has labels with extern goto
    for (auto it = inForLabels.begin(); it != inForLabels.end(); ++it)
    {
        if (gotoLabels.find(it->first) == gotoLabels.end() && labelsRef.find(it->first) != labelsRef.end())
        {
            has = true;
            for (int z = 0; z < it->second.size(); ++z)
                linesOfExtGoTo.push_back(it->second[z]);
        }
    }
        
    return has;
}

static inline bool hasThisIds(SgStatement *loop, vector<int> &lines, const set<int> &IDs)
{
    bool has = false;
    SgStatement *end = loop->lastNodeOfStmt();
    SgStatement *curr = loop;
    
    while (curr != end)
    {
        const int var = curr->variant();
        if (IDs.find(var) != IDs.end())
        {
            has = true;
            lines.push_back(curr->lineNumber());
        }
        curr = curr->lexNext();
    }

    return has;
}

static inline void findFuncCalls(SgExpression *ex, set<string> &funcCalls)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
            funcCalls.insert(ex->symbol()->identifier());
        findFuncCalls(ex->lhs(), funcCalls);
        findFuncCalls(ex->rhs(), funcCalls);
    }
}

static inline int tryCalculate(SgExpression *expr, int &res)
{
    SgExpression *copyExp = &(expr->copy());
    replaceConstatRec(copyExp);
    calculate(copyExp);
    if (CalculateInteger(copyExp, res) == -1)
        return -1;
    return 0;
}

static inline int calculateLoopIters(SgExpression *start, SgExpression *end, SgExpression *step)
{
    if (!start && !end)
        return 0;

    int startV;
    int endV;
    int stepV;
    if (!step)
        stepV = 1;
    else
    {
        if (tryCalculate(step, stepV) == -1)
            return 0;
    }

    if (tryCalculate(start, startV) == -1)
        return 0;
    if (tryCalculate(end, endV) == -1)
        return 0;

    if (startV > endV && stepV > 0)
        return 0;
    if (startV < endV && stepV < 0)
        return 0;

    int count = (endV - startV + stepV) / stepV;
    if (count > 0)
        return count;
    else
        return 0;
}

void findAllRefsToLables(SgStatement *st, map<int, vector<int>> &labelsRef)
{
    SgStatement *last = st->lastNodeOfStmt();
    for ( ; st != last; st = st->lexNext())
        processLables(st, labelsRef);
}

static bool hasNonRect(SgForStmt *st, const vector<LoopGraph*> &parentLoops)
{
    SgExpression *start = st->start();
    SgExpression *end = st->end();
    SgExpression *step = st->step();

    bool has = recVariantFind(start, FUNC_CALL) || recVariantFind(end, FUNC_CALL) || recVariantFind(step, FUNC_CALL);
    has = has || recVariantFind(start, ARRAY_REF) || recVariantFind(end, ARRAY_REF) || recVariantFind(step, ARRAY_REF);
    
    if (has == false)
    {
        for (auto &upLoop : parentLoops)
        {
            SgForStmt *up = (SgForStmt*)upLoop->loop;
            SgSymbol *symb = up->symbol();
            if (symb)
            {
                const string strSymb = symb->identifier();
                has = has || recScalaraSymbolFind(start, strSymb);
                has = has || recScalaraSymbolFind(end, strSymb);
                has = has || recScalaraSymbolFind(step, strSymb);

                if (has)
                    break;
            }
        }
    }
    return has;
}

void loopGraphAnalyzer(SgFile *file, vector<LoopGraph*> &loopGraph)
{
    int funcNum = file->numberOfFunctions();
    __spf_print(DEBUG, "functions num in file = %d\n", funcNum);

    for (int i = 0; i < funcNum; ++i)
    {
        map<int, vector<int>> labelsRef;

        SgStatement *st = file->functions(i);
        findAllRefsToLables(st, labelsRef);

        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
            __spf_print(DEBUG, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
            __spf_print(DEBUG, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
            __spf_print(DEBUG, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), st->lineNumber(), st->fileName());            
        }

        SgStatement *lastNode = st->lastNodeOfStmt();        
        vector<LoopGraph*> parentLoops;
        LoopGraph *currLoop = NULL;
        
        while (st != lastNode)
        {
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            //printf("new st with var = %d, on line %d\n", st->variant(), st->lineNumber());
            if (st->variant() == FOR_NODE)
            {
                LoopGraph *newLoop = new LoopGraph();
                newLoop->lineNum = st->lineNumber();
                newLoop->lineNumAfterLoop = st->lastNodeOfStmt()->lexNext()->lineNumber();
                newLoop->fileName = st->fileName();
                newLoop->perfectLoop = ((SgForStmt*)st)->isPerfectLoopNest();
                newLoop->hasGoto = hasGoto(st, newLoop->linesOfInternalGoTo, newLoop->linesOfExternalGoTo, labelsRef);
                newLoop->hasPrints = hasThisIds(st, newLoop->linesOfIO, { WRITE_STAT, READ_STAT, FORMAT_STAT, OPEN_STAT, CLOSE_STAT } );
                newLoop->hasStops = hasThisIds(st, newLoop->linesOfStop, { STOP_STAT, PAUSE_NODE });
                newLoop->hasNonRectangularBounds = hasNonRect(((SgForStmt*)st), parentLoops);

                SgForStmt *currLoopRef = ((SgForStmt*)st);
                newLoop->countOfIters = calculateLoopIters(currLoopRef->start(), currLoopRef->end(), currLoopRef->step());
                newLoop->loop = new Statement(st);

                if (parentLoops.size() == 0)
                    loopGraph.push_back(newLoop);
                else
                    currLoop->childs.push_back(newLoop);

                parentLoops.push_back(newLoop);
                currLoop = newLoop;
            }
            else if (st->variant() == CONTROL_END)
            {
                if (st->controlParent()->variant() == FOR_NODE)
                {                    
                    parentLoops.pop_back();
                    if (parentLoops.size() != 0)
                        currLoop = parentLoops.back();
                    else
                        currLoop = NULL;
                }
            }
            else if (currLoop && (st->variant() == PROC_STAT || st->variant() == FUNC_STAT))
            {
                string pureNameOfCallFunc = removeString("call", st->symbol()->identifier());
                currLoop->calls.push_back(make_pair(pureNameOfCallFunc, st->lineNumber()));                
            }
            else if (currLoop)
            {
                for (int i = 0; i < 3; ++i)
                {
                    set<string> funcCalls;
                    findFuncCalls(st->expr(i), funcCalls);
                    for (auto k = funcCalls.begin(); k != funcCalls.end(); ++k)
                        currLoop->calls.push_back(make_pair(*k, st->lineNumber()));
                }
            }
            st = st->lexNext();
        }
        __spf_print(DEBUG, "Function ended\n");
    }
}

#undef DEBUG