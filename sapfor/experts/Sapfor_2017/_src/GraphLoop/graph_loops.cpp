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
#include "../Sapfor.h"
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

#include "../LoopAnalyzer/directive_parser.h"
#include "../DynamicAnalysis/gCov_parser_func.h"

#include "../GraphCall/graph_calls_func.h"

using std::vector;
using std::map;
using std::set;
using std::string;
using std::wstring;
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

static void recInderectFind(SgExpression *ex, set<DIST::Array*> &usedArrays)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            DIST::Array *arrayRef = NULL;
            SgSymbol *symbS = OriginalSymbol(ex->symbol());
            const string symb = symbS->identifier();

            if (symbS)
                arrayRef = getArrayFromDeclarated(declaratedInStmt(symbS), symb);
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            // only distributed arrays were added
            if (arrayRef)
                if (arrayRef->GetNonDistributeFlag() == false)
                    usedArrays.insert(arrayRef);
        }

        recInderectFind(ex->lhs(), usedArrays);        
        recInderectFind(ex->rhs(), usedArrays);        
    }
}

bool recSymbolFind(SgExpression *ex, const string &symb, const int var)
{
    bool ret = false;
    if (ex)
    {
        if (ex->variant() == var)
        {
            if (ex->symbol())
                if (ex->symbol()->identifier() == symb)
                    return true;
        }

        ret = ret || recSymbolFind(ex->lhs(), symb, var);
        ret = ret || recSymbolFind(ex->rhs(), symb, var);
    }

    return ret;
}

static inline void processLables(SgStatement *curr, map<int, vector<int>> &labelsList, bool includeWrite = true)
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
    else if (curr->variant() == PRINT_STAT && includeWrite)
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
    else if (curr->variant() == WRITE_STAT && includeWrite)
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

static inline bool hasGoto(SgStatement *begin, SgStatement *end, vector<int> &linesOfIntGoTo, vector<int> &linesOfExtGoTo, const map<int, vector<int>> &labelsRef)
{
    bool has = false;
    SgStatement *curr = begin->lexNext();
    map<int, vector<int>> gotoLabels;
    map<int, vector<int>> inFragLabels;

    while (curr != end)
    {
        if (curr->hasLabel())
            inFragLabels[curr->label()->getLabNumber()].push_back(curr->lineNumber());

        for (int i = 0; i < 3; ++i)
        {
            if (curr->expr(i))
            {
                if (recVariantFind(curr->expr(i), EXIT_STMT) && getLoopControlParent(curr) == begin)
                {
                    linesOfIntGoTo.push_back(curr->lineNumber());
                    has = true;
                }
            }
        }

        processLables(curr, gotoLabels);

        if (curr->variant() == EXIT_STMT && getLoopControlParent(curr) == begin)
        {
            linesOfIntGoTo.push_back(curr->lineNumber());
            has = true;
        }
        curr = curr->lexNext();
    }

    // if loop has no labels from goto 
    for (auto it = gotoLabels.begin(); it != gotoLabels.end(); ++it)
    {
        if (inFragLabels.find(it->first) == inFragLabels.end())
        {
            has = true;
            for (int z = 0; z < it->second.size(); ++z)
                linesOfIntGoTo.push_back(it->second[z]);
        }
    }
        
    // if loop has labels with extern goto
    for (auto it = inFragLabels.begin(); it != inFragLabels.end(); ++it)
    {
        auto labRef = labelsRef.find(it->first);

        if (labRef != labelsRef.end())
        {
            for (auto &line : labRef->second)
            {
                if (!(line > begin->lineNumber() && line <= end->lineNumber()))
                {
                    has = true;
                    linesOfExtGoTo.push_back(line);
                }
            }
        }
    }
        
    return has;
}

bool checkRegionEntries(SgStatement *begin,
                        SgStatement *end,
                        const map<string, FuncInfo*> &funcMap,
                        const vector<ParallelRegion*> &parallelRegions,
                        map<string, vector<Messages>> &SPF_messages)
{
    bool noError = true;

    SgStatement *st = begin;
    SgSymbol *regIdent = begin->symbol();

    // get func statement
    while (st->variant() != PROG_HEDR && st->variant() != PROC_HEDR && st->variant() != FUNC_HEDR)
        st = st->controlParent();

    // check GOTO
    map<int, vector<int>> labelsRef;
    findAllRefsToLables(st, labelsRef);

    vector<int> linesOfIntGoTo;
    vector<int> linesOfExtGoTo;
    hasGoto(begin, end, linesOfIntGoTo, linesOfExtGoTo, labelsRef);

    if (linesOfExtGoTo.size())
    {
        __spf_print(1, "wrong parallel region position: there are several entries in fragment '%s' caused by GOTO on line %d\n", regIdent->identifier(), begin->lineNumber());

        wstring messageE, messageR;
        __spf_printToLongBuf(messageE, L"wrong parallel region position: there are several entries in fragment '%s' caused by GOTO", to_wstring(regIdent->identifier()).c_str());
#ifdef _WIN32
        __spf_printToLongBuf(messageR, R11, to_wstring(regIdent->identifier()).c_str());
#endif
        getObjectForFileFromMap(begin->fileName(), SPF_messages).push_back(Messages(ERROR, begin->lineNumber(), messageR, messageE, 1001));

        noError = false;
    }

    // check ENTRY
    auto oldFile = current_file->filename();
    for (auto &funcPair : funcMap)
    {
        auto func = funcPair.second;
        if (SgFile::switchToFile(func->fileName) != -1)
        {
            SgStatement *funcSt = func->funcPointer->GetOriginal();
            ParallelRegion *reg = NULL;
            if (funcSt->variant() == ENTRY_STAT && func->callsTo.size() && (reg = getRegionByLine(parallelRegions, func->fileName, funcSt->lineNumber())))
            {
                __spf_print(1, "wrong parallel region position: there are several entries in fragment '%s' caused by ENTRY on line %d\n", reg->GetName().c_str(), funcSt->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"wrong parallel region position: there are several entries in fragment '%s' caused by ENTRY", to_wstring(reg->GetName()).c_str());
#ifdef _WIN32
                __spf_printToLongBuf(messageR, R10, to_wstring(reg->GetName()).c_str());
#endif
                getObjectForFileFromMap(func->fileName.c_str(), SPF_messages).push_back(Messages(ERROR, funcSt->lineNumber(), messageR, messageE, 1001));

                noError = false;
            }
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    if (SgFile::switchToFile(oldFile) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return noError;
}

bool hasThisIds(SgStatement *start, vector<int> &lines, const set<int> &IDs)
{
    bool has = false;
    SgStatement *end = start->lastNodeOfStmt();
    SgStatement *curr = start;
    
    while (curr != end)
    {
        const int var = curr->variant();
        if (var == CONTAINS_STMT || var == ENTRY_STAT)
            break;

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

void findAllRefsToLables(SgStatement *st, map<int, vector<int>> &labelsRef, bool includeWrite)
{
    SgStatement *last = st->lastNodeOfStmt();
    for ( ; st != last; st = st->lexNext())
        processLables(st, labelsRef, includeWrite);
}

static bool hasNonRect(SgForStmt *st, const vector<LoopGraph*> &parentLoops, vector<Messages> &messages)
{
    SgExpression *start = st->start();
    SgExpression *end = st->end();
    SgExpression *step = st->step();

    set<DIST::Array*> usedArrays;

    bool has1 = recVariantFind(start, FUNC_CALL) || recVariantFind(end, FUNC_CALL) || recVariantFind(step, FUNC_CALL);
    recInderectFind(start, usedArrays);
    recInderectFind(end, usedArrays);
    recInderectFind(step, usedArrays);
    bool has = has1 || (usedArrays.size() > 0);
    
    for (auto &array : usedArrays)
    {
        wstring bufE, bufR;
        __spf_printToLongBuf(bufE, L"Array '%s' can not be distributed", to_wstring(array->GetShortName()).c_str());
#ifdef _WIN32
        __spf_printToLongBuf(bufR, L"ћассив '%s' не может быть распределен", to_wstring(array->GetShortName()).c_str());
#endif
        messages.push_back(Messages(ERROR, st->lineNumber(), bufR, bufE, 1047));
        array->SetNonDistributeFlag(DIST::SPF_PRIV);
    }

    if (has == false)
    {
        for (auto &upLoop : parentLoops)
        {
            SgForStmt *up = (SgForStmt*)upLoop->loop;
            SgSymbol *symb = up->symbol();
            if (symb)
            {
                const string strSymb = symb->identifier();

                has = has || recSymbolFind(start, strSymb, VAR_REF);
                has = has || recSymbolFind(end, strSymb, VAR_REF);
                has = has || recSymbolFind(step, strSymb, VAR_REF);

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

static void findArrayRef(SgExpression *exp, bool isWirte, set<DIST::Array*> &allUsedArrays, set<DIST::Array*> &writeUsedArrays)
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

            // only distributed arrays were added
            if (arrayRef)
            {
                if (arrayRef->GetNonDistributeFlag() == false)
                {
                    allUsedArrays.insert(arrayRef);
                    if (isWirte)
                        writeUsedArrays.insert(arrayRef);
                }
            }

        }
        else
        {
            findArrayRef(exp->lhs(), false, allUsedArrays, writeUsedArrays);
            findArrayRef(exp->rhs(), false, allUsedArrays, writeUsedArrays);
        }
    }
}

//TODO: add IPO analysis
static void findArrayRefs(LoopGraph *loop)
{
    for (SgStatement *st = loop->loop->lexNext(); st != loop->loop->lastNodeOfStmt(); st = st->lexNext())
    {
        if (isSgExecutableStatement(st))
        {
            for (int z = 0; z < 3; ++z)
            {
                bool isWrite = false;
                if (z == 0 && st->variant() == ASSIGN_STAT)
                    isWrite = true;
                findArrayRef(st->expr(z), isWrite, loop->usedArrays, loop->usedArraysWrite);
            }
        }
    }
}

void loopGraphAnalyzer(SgFile *file, vector<LoopGraph*> &loopGraph, const vector<SpfInterval*> &intervalTree, vector<Messages> &messages)
{
    map<int, SpfInterval*> mapIntervals;
    createMapOfinterval(mapIntervals, intervalTree);

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
            currProcessing.second = st->lineNumber();
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
                newLoop->hasGoto = hasGoto(st, st->lastNodeOfStmt(), newLoop->linesOfInternalGoTo, newLoop->linesOfExternalGoTo, labelsRef);
                newLoop->hasPrints = hasThisIds(st, newLoop->linesOfIO, { WRITE_STAT, READ_STAT, OPEN_STAT, CLOSE_STAT, PRINT_STAT } ); // FORMAT_STAT
                newLoop->hasStops = hasThisIds(st, newLoop->linesOfStop, { STOP_STAT, PAUSE_NODE });
                newLoop->hasNonRectangularBounds = hasNonRect(((SgForStmt*)st), parentLoops, messages);
                auto itTime = mapIntervals.find(newLoop->lineNum);
                if (itTime != mapIntervals.end() && itTime->second->exec_time != 0)
                    newLoop->executionTimeInSec = itTime->second->exec_time / itTime->second->exec_count;
                else if (mapIntervals.size())
                {
#ifdef _WIN32
                    messages.push_back(Messages(NOTE, newLoop->lineNum, L"Ќевозможно считать DVM-статистику дл€ получени€ времен", L"Can not find execution time in statistic", 3016));
#endif
                }

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
                else
                {
                    SgExpression *start = currLoopRef->start();
                    SgExpression *end = currLoopRef->end();
                    SgExpression *step = currLoopRef->step();

                    Expression *endE = NULL;
                    Expression *startE = NULL;
                    if (step == NULL)
                    {
                        startE = new Expression(start);
                        endE = new Expression(end);
                    }
                    else
                    {
                        int res = -1;
                        int err = CalculateInteger(step, res);
                        if (err == 0 && res != 0)
                        {
                            if (res > 0)
                            {
                                startE = new Expression(start);
                                endE = new Expression(&((*end - *start + *step) / *step));
                            }
                            else
                            {
                                endE = new Expression(end);
                                endE = new Expression(&((*start - *end + *step) / *step));
                            }
                        }
                    }

                    newLoop->startEndExpr = std::make_pair(startE, endE);
                }

                newLoop->loop = new Statement(st);
                newLoop->loopSymbol = st->symbol()->identifier();
                findArrayRefs(newLoop);

                SgStatement *lexPrev = st->lexPrev();
                if (lexPrev->variant() == DVM_PARALLEL_ON_DIR)
                    newLoop->userDvmDirective = new Statement(lexPrev);

                if (parentLoops.size() == 0)
                    loopGraph.push_back(newLoop);
                else
                {
                    currLoop->children.push_back(newLoop);
                    currLoop->children.back()->parent = parentLoops.back();
                    currLoop->children.back()->funcParent = parentLoops.back();
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
                for (auto &loop : parentLoops)
                    loop->calls.push_back(make_pair(pureNameOfCallFunc, st->lineNumber()));
            }
            else if (currLoop)
            {
                for (int i = 0; i < 3; ++i)
                {
                    set<string> funcCalls;
                    findFuncCalls(st->expr(i), funcCalls);

                    for (auto &loop : parentLoops)
                        for (auto k = funcCalls.begin(); k != funcCalls.end(); ++k)
                            loop->calls.push_back(make_pair(*k, st->lineNumber()));
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
    for (auto &loop : children)
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

static int calculateNormalChildSize(const LoopGraph *currLoop)
{
    int count = 0;
    for (auto &elem : currLoop->children)
        count += (elem->lineNum > 0) ? 1 : 0;
    return count;
}

void convertToString(const LoopGraph *currLoop, string &result)
{
    if (currLoop && currLoop->lineNum > 0)
    {
        char buf[512];
        result += " " + std::to_string(currLoop->calls.size());
        for (int i = 0; i < currLoop->calls.size(); ++i)
            result += " " + currLoop->calls[i].first + " " + std::to_string(currLoop->calls[i].second);
        printToBuffer(currLoop, calculateNormalChildSize(currLoop), buf);
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

        for (int i = 0; i < (int)currLoop->children.size(); ++i)
            convertToString(currLoop->children[i], result);
    }
}

void createMapLoopGraph(const vector<LoopGraph*> &loops, map<int, LoopGraph*> &mapGraph)
{
    for (auto &elem : loops)
    {
        if (mapGraph.find(elem->lineNum) != mapGraph.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        mapGraph[elem->lineNum] = elem;
    }

    for (auto &elem : loops)
        createMapLoopGraph(elem->children, mapGraph);
}

map<LoopGraph*, ParallelDirective*> findAllDirectives(SgFile *file, const vector<LoopGraph*> &loops, const int regId)
{
    if (loops.size() == 0)
        return map<LoopGraph*, ParallelDirective*>();

    map<LoopGraph*, ParallelDirective*> retVal;

    map<int, LoopGraph*> mapGraph;
    createMapLoopGraph(loops, mapGraph);


    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        if (st->variant() == DVM_PARALLEL_ON_DIR)
        {
            auto next = st->lexNext();
            if (next->variant() != FOR_NODE)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            auto it = mapGraph.find(next->lineNumber());
            if (it == mapGraph.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            if (it->second->region && it->second->region->GetId() == regId)
                retVal[it->second] = it->second->directive;            
        }
    }

    return retVal;
}

static void fillFromList(SgExpression *list, vector<long> &coords, DIST::Array *currArr)
{
    if (list)
    {
        int idx = 0;
        while (list)
        {
            if (list->lhs())
            {
                const int var = list->lhs()->variant();
                if (var == DDOT || var == KEYWORD_VAL)
                    coords[currArr->GetDimSize() - 1 - idx] = -1;
                else
                    coords[currArr->GetDimSize() - 1 - idx] = 0;
            }
            else
                coords[currArr->GetDimSize() - 1 - idx] = -1;
            idx++;
            list = list->rhs();
        }
    }
    else // full
        std::fill(coords.begin(), coords.end(), -1);
}

map<DIST::Array*, vector<long>> fillRemoteInParallel(Statement *loop)
{
    map<DIST::Array*, vector<long>> toRet;
    if (!loop->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement *st = loop->lexPrev();
    if (st->variant() == DVM_PARALLEL_ON_DIR)
    {       
        map<pair<SgExpression*, string>, Expression*> remotes;
        fillRemoteFromComment(new Statement(st), remotes, false, DVM_PARALLEL_ON_DIR);

        for (auto &newRem : remotes)
        {
            auto key = make_pair(string(newRem.first.first->symbol()->identifier()), newRem.first.second);                
            DIST::Array *currArr = getArrayFromDeclarated(declaratedInStmt(newRem.first.first->symbol()), key.first);
            newRem.first.first->addAttribute(ARRAY_REF, currArr, sizeof(DIST::Array));                
            if (toRet.find(currArr) != toRet.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            vector<long> coords(currArr->GetDimSize());
            SgExpression *list = newRem.second->GetOriginal();
            fillFromList(list, coords, currArr);

            toRet[currArr] = coords;
        }        
    }

    return toRet;
}

vector<std::tuple<DIST::Array*, vector<long>, pair<string, int>>> findAllSingleRemotes(SgFile *file, const int regId, vector<ParallelRegion*> &regions)
{
    vector<std::tuple<DIST::Array*, vector<long>, pair<string, int>>> retVal;

    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        if (st->variant() == DVM_REMOTE_ACCESS_DIR)
        {
            ParallelRegion *currReg = getRegionByLine(regions, st->fileName(), st->lineNumber());
            if (currReg)
            {
                map<pair<SgSymbol*, string>, Expression*> remotes;
                fillRemoteFromComment(new Statement(st), remotes, false, DVM_REMOTE_ACCESS_DIR);

                for (auto &array : remotes)
                {
                    auto arrName = array.first.first;
                    DIST::Array *currArr = getArrayFromDeclarated(declaratedInStmt(array.first.first), array.first.first->identifier());
                    checkNull(currArr, convertFileName(__FILE__).c_str(), __LINE__);

                    vector<long> coords(currArr->GetDimSize());
                    SgExpression *list = array.second->GetOriginal();
                    fillFromList(list, coords, currArr);

                    retVal.push_back(std::make_tuple(currArr, coords, std::make_pair(st->lexNext()->fileName(), st->lexNext()->lineNumber())));
                }
            }
        }
    }

    return retVal;
}

#undef DEBUG
