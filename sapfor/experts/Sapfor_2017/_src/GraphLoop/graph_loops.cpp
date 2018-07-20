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
#include "../ParallelizationRegions/ParRegions_func.h"
#include "../ExpressionTransform/expr_transform.h"

#include "../Distribution/GraphCSR.h"
#include "../Distribution/Arrays.h"
#include "../Distribution/Distribution.h"

#include "graph_loops.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"

#include "../Utils/errors.h"
#include "../Utils/AstWrapper.h"

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

static bool recInderectFind(SgExpression *ex, bool wasArrayref)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            if (wasArrayref)
                return true;
            else
                wasArrayref = true;
        }

        ret = ret || recInderectFind(ex->lhs(), wasArrayref);
        ret = ret || recInderectFind(ex->rhs(), wasArrayref);
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

static SgStatement *getLoopControlParent(SgStatement *inSt)
{
    SgStatement *cp = inSt->controlParent();
    while (!isSgForStmt(cp) && cp)
        cp = cp->controlParent();
    return cp;
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
                if (recVariantFind(curr->expr(i), EXIT_STMT) && getLoopControlParent(curr) == loop)
                {
                    linesOfIntGoTo.push_back(curr->lineNumber());
                    has = true;
                }
            }
        }

        processLables(curr, gotoLabels);

        if (curr->variant() == EXIT_STMT && getLoopControlParent(curr) == loop)
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
    SgExpression *copyExp = expr->copyPtr();
    replaceConstatRec(copyExp);
    calculate(copyExp);
    if (CalculateInteger(copyExp, res) == -1)
        return -1;
    return 0;
}

static inline int calculateLoopIters(SgExpression *start, SgExpression *end, SgExpression *step, std::tuple<int, int, int> &result)
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
    {
        std::get<0>(result) = startV;
        std::get<1>(result) = endV;
        std::get<2>(result) = stepV;
        return count;
    }
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
    has = has || recInderectFind(start, false) || recInderectFind(end, false) || recInderectFind(step, false);
    
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

static void addLoopVariablesToPrivateList(SgForStmt *currLoopRef)
{
    SgStatement *spfStat = new SgStatement(SPF_ANALYSIS_DIR);
    spfStat->setlineNumber(currLoopRef->lineNumber());
    spfStat->setFileName(currLoopRef->fileName());

    SgExpression *toAdd = new SgExpression(EXPR_LIST, new SgExpression(ACC_PRIVATE_OP), NULL, NULL);
    set<SgSymbol*> privateDoSymbs = { currLoopRef->symbol() };

    SgStatement *end = currLoopRef->lastNodeOfStmt();
    for (SgStatement *st = currLoopRef->lexNext(); st != end; st = st->lexNext())
    {
        SgForStmt *currFor = isSgForStmt(st);
        if (currFor)
            privateDoSymbs.insert(currFor->symbol());
    }

    spfStat->setExpression(0, *toAdd);
    toAdd = toAdd->lhs();
    bool first = true;
    for (auto &elem : privateDoSymbs)
    {
        if (first)
        {
            toAdd->setLhs(new SgExpression(EXPR_LIST));
            toAdd = toAdd->lhs();
            first = false;
        }
        else
        {
            toAdd->setRhs(new SgExpression(EXPR_LIST));
            toAdd = toAdd->rhs();
        }
        toAdd->setLhs(new SgVarRefExp(elem));
    }

    currLoopRef->addAttribute(SPF_ANALYSIS_DIR, spfStat, sizeof(SgStatement));
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
            currProcessing.second = st;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            //printf("new st with var = %d, on line %d\n", st->variant(), st->lineNumber());
            if (st->variant() == FOR_NODE)
            {
                LoopGraph *newLoop = new LoopGraph();
                newLoop->lineNum = st->lineNumber();

                SgStatement *afterLoop = st->lastNodeOfStmt()->lexNext();
                //< 0 was appear after CONVERT_ASSIGN_TO_LOOP pass
                while (afterLoop->lineNumber() < 0)
                {
                    afterLoop = afterLoop->lastNodeOfStmt();
                    afterLoop = afterLoop->lexNext();
                }
                newLoop->lineNumAfterLoop = afterLoop->lineNumber();

                newLoop->fileName = st->fileName();
                newLoop->perfectLoop = ((SgForStmt*)st)->isPerfectLoopNest();
                newLoop->hasGoto = hasGoto(st, newLoop->linesOfInternalGoTo, newLoop->linesOfExternalGoTo, labelsRef);
                newLoop->hasPrints = hasThisIds(st, newLoop->linesOfIO, { WRITE_STAT, READ_STAT, FORMAT_STAT, OPEN_STAT, CLOSE_STAT } );
                newLoop->hasStops = hasThisIds(st, newLoop->linesOfStop, { STOP_STAT, PAUSE_NODE });
                newLoop->hasNonRectangularBounds = hasNonRect(((SgForStmt*)st), parentLoops);

                SgForStmt *currLoopRef = ((SgForStmt*)st);

                std::tuple<int, int, int> loopInfoSES;
                newLoop->countOfIters = calculateLoopIters(currLoopRef->start(), currLoopRef->end(), currLoopRef->step(), loopInfoSES);
                if (newLoop->countOfIters != 0)
                {
                    newLoop->calculatedCountOfIters = newLoop->countOfIters;
                    newLoop->startVal = std::get<0>(loopInfoSES);
                    newLoop->endVal = std::get<1>(loopInfoSES);
                    newLoop->stepVal = std::get<2>(loopInfoSES);
                }
                newLoop->loop = new Statement(st);

                SgStatement *lexPrev = st->lexPrev();
                if (lexPrev->variant() == DVM_PARALLEL_ON_DIR)
                    newLoop->userDvmDirective = new Statement(lexPrev);

                if (parentLoops.size() == 0)
                    loopGraph.push_back(newLoop);
                else
                {
                    currLoop->childs.push_back(newLoop);
                    currLoop->childs.back()->parent = parentLoops.back();
                }

                parentLoops.push_back(newLoop);
                currLoop = newLoop;

                addLoopVariablesToPrivateList(currLoopRef);
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

    for (auto &loop : loopGraph)
        loop->propagateUserDvmDir();
}

void LoopGraph::recalculatePerfect()
{
    perfectLoop = ((SgForStmt*)(loop->GetOriginal()))->isPerfectLoopNest();
    for (auto &loop : childs)
        loop->recalculatePerfect();
}

extern int PASSES_DONE[EMPTY_PASS];
static void printToBuffer(const LoopGraph *currLoop, const int childSize, char buf[512])
{
    int loopState = 0; // 0 - unknown, 1 - good, 2 - bad
    if (PASSES_DONE[CREATE_TEMPLATE_LINKS])
    {
        if (currLoop->hasLimitsToParallel())
            loopState = 2;
        else
            loopState = 1;
    }
    else
    {
        if (currLoop->hasLimitsToParallel())
            loopState = 2;
    }

    sprintf(buf, " %d %d %d %d %d %d %d",
        currLoop->lineNum, currLoop->lineNumAfterLoop, currLoop->perfectLoop, currLoop->hasGoto, currLoop->hasPrints, childSize, loopState);
}

void convertToString(const LoopGraph *currLoop, string &result)
{
    if (currLoop && currLoop->lineNum > 0)
    {
        char buf[512];
        result += " " + std::to_string(currLoop->calls.size());
        for (int i = 0; i < currLoop->calls.size(); ++i)
            result += " " + currLoop->calls[i].first + " " + std::to_string(currLoop->calls[i].second);
        printToBuffer(currLoop, (int)currLoop->childs.size(), buf);
        result += string(buf);

        result += " " + std::to_string(currLoop->linesOfExternalGoTo.size());
        for (int i = 0; i < currLoop->linesOfExternalGoTo.size(); ++i)
            result += " " + std::to_string(currLoop->linesOfExternalGoTo[i]);

        result += " " + std::to_string(currLoop->linesOfInternalGoTo.size());
        for (int i = 0; i < currLoop->linesOfInternalGoTo.size(); ++i)
            result += " " + std::to_string(currLoop->linesOfInternalGoTo[i]);

        result += " " + std::to_string(currLoop->linesOfIO.size());
        for (int i = 0; i < currLoop->linesOfIO.size(); ++i)
            result += " " + std::to_string(currLoop->linesOfIO[i]);

        for (int i = 0; i < (int)currLoop->childs.size(); ++i)
            convertToString(currLoop->childs[i], result);
    }
}
#undef DEBUG
