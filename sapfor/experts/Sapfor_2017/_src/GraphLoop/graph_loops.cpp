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
#include "../Transformations/array_assign_to_loop.h"

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

static inline void processIOlist(SgExpression *spec, const int line, map<int, vector<int>>& labelsList)
{
    while (spec)
    {
        if (spec->lhs())
        {
            SgExpression* specL = spec->lhs();
            if (specL->lhs() && specL->rhs())
            {
                if (specL->lhs()->variant() == KEYWORD_VAL)
                {
                    SgKeywordValExp* keyVal = (SgKeywordValExp*)specL->lhs();

                    if (keyVal->value() != string("fmt"))
                    {
                        if (specL->rhs()->variant() == LABEL_REF)
                        {
                            SgLabelRefExp* labRef = (SgLabelRefExp*)specL->rhs();
                            if (labRef->label())
                                labelsList[labRef->label()->getLabNumber()].push_back(line);
                        }
                    }
                }
            }
        }
        spec = spec->rhs();
    }
}

static inline void processLables(SgStatement *curr, map<int, vector<int>> &labelsList, bool includeWrite = true)
{
    const int var = curr->variant();
    if (var == GOTO_NODE)
    {
        SgGotoStmt *gotoS = (SgGotoStmt *)curr;
        labelsList[gotoS->branchLabel()->getLabNumber()].push_back(curr->lineNumber());
    }
    else if (var == ARITHIF_NODE)
    {
        SgExpression *lb = curr->expr(1);
        insertLabels(lb, labelsList, curr->lineNumber());
    }
    else if (var == COMGOTO_NODE)
    {
        SgExpression *lb = ((SgComputedGotoStmt*)curr)->labelList();
        insertLabels(lb, labelsList, curr->lineNumber());
    }
    else if ((var == PRINT_STAT || var == WRITE_STAT) && includeWrite)
    {
        SgInputOutputStmt *ioStat = (SgInputOutputStmt*)curr;
        SgExpression *spec = ioStat->specList();
        processIOlist(spec, curr->lineNumber(), labelsList);        
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
        __spf_printToLongBuf(messageR, R11, to_wstring(regIdent->identifier()).c_str());

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
                __spf_printToLongBuf(messageR, R10, to_wstring(reg->GetName()).c_str());

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
        __spf_printToLongBuf(bufR, R91, to_wstring(array->GetShortName()).c_str());

        messages.push_back(Messages(NOTE, st->lineNumber(), bufR, bufE, 1047));
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
    if (currLoopRef == NULL)
        return;

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

static void findArrayRefs(LoopGraph *loop)
{
    for (SgStatement *st = loop->loop->lexNext(); st != loop->loop->lastNodeOfStmt(); st = st->lexNext())
    {
        if (isSgExecutableStatement(st) && !isDVM_stat(st) && !isSPF_stat(st))
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

static bool isLoopStat(SgStatement* st)
{
    const int var = st->variant();
    return (var == FOR_NODE || var == WHILE_NODE);
}

void loopGraphAnalyzer(SgFile *file, vector<LoopGraph*> &loopGraph, const vector<SpfInterval*> &intervalTree, vector<Messages> &messages, int mpiProgram)
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
            if (isLoopStat(st))
            {
                LoopGraph *newLoop = new LoopGraph();
                newLoop->lineNum = st->lineNumber();
                if (newLoop->lineNum < 0)
                {
                    if (st->localLineNumber() > 0)
                    {
                        SgStatement* copied = SgStatement::getStatementByFileAndLine(st->fileName(), st->localLineNumber());
                        checkNull(copied, convertFileName(__FILE__).c_str(), __LINE__);
                        if (notDeletedVectorAssign(copied))
                            newLoop->altLineNum = st->localLineNumber();
                    }
                }

                SgStatement *afterLoop = st->lastNodeOfStmt()->lexNext();
                //< 0 was appear after CONVERT_ASSIGN_TO_LOOP pass
                while (afterLoop->lineNumber() < 0)
                {
                    afterLoop = afterLoop->lastNodeOfStmt();
                    afterLoop = afterLoop->lexNext();
                }
                newLoop->lineNumAfterLoop = afterLoop->lineNumber();

                vector<int> tmpLines;

                newLoop->fileName = st->fileName();
                newLoop->perfectLoop = countPerfectLoopNest(st);
                newLoop->hasGoto = hasGoto(st, st->lastNodeOfStmt(), newLoop->linesOfInternalGoTo, newLoop->linesOfExternalGoTo, labelsRef);
                newLoop->hasPrints = hasThisIds(st, newLoop->linesOfIO, { WRITE_STAT, READ_STAT, OPEN_STAT, CLOSE_STAT, PRINT_STAT } ); // FORMAT_STAT
                newLoop->hasStops = hasThisIds(st, newLoop->linesOfStop, { STOP_STAT, PAUSE_NODE });
                newLoop->hasDvmIntervals = hasThisIds(st, tmpLines, { DVM_INTERVAL_DIR, DVM_ENDINTERVAL_DIR, DVM_EXIT_INTERVAL_DIR });
                newLoop->isFor = isSgForStmt(st) ? true : false;
                newLoop->inCanonicalFrom = isSgForStmt(st) ? true : false;

                if (mpiProgram == 0)
                    if (isSgForStmt(st))
                        newLoop->hasNonRectangularBounds = hasNonRect(((SgForStmt*)st), parentLoops, messages);

                auto itTime = mapIntervals.find(newLoop->lineNum);
                if (itTime != mapIntervals.end() && itTime->second->exec_time != 0)
                    newLoop->executionTimeInSec = itTime->second->exec_time / itTime->second->exec_count;
                else if (mapIntervals.size())
                {
                    //messages.push_back(Messages(NOTE, newLoop->lineNum, R137, L"Can not find execution time in statistic", 3016));
                }

                SgForStmt *currLoopRef = isSgForStmt(st);

                if (currLoopRef)
                {
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
                        SgExpression* start = currLoopRef->start();
                        SgExpression* end = currLoopRef->end();
                        SgExpression* step = currLoopRef->step();

                        if (start == NULL || end == NULL)
                            newLoop->inCanonicalFrom = false;

                        Expression* endE = NULL;
                        Expression* startE = NULL;
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
                }
                else
                    newLoop->startEndExpr = std::make_pair((Expression*)NULL, (Expression*)NULL);

                newLoop->loop = new Statement(st);
                newLoop->loopSymbol = st->symbol() ? st->symbol()->identifier() : "unknown";
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
                }

                parentLoops.push_back(newLoop);
                currLoop = newLoop;

                addLoopVariablesToPrivateList(currLoopRef);
            }
            else if (st->variant() == CONTROL_END)
            {
                if (isLoopStat(st->controlParent()))
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
                string pureNameOfCallFunc = removeString("call ", st->symbol()->identifier());
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
    auto loopRef = loop->GetOriginal();
    perfectLoop = isSgForStmt(loopRef) ? countPerfectLoopNest(loop->GetOriginal()) : perfectLoop;
    for (auto &loop : children)
        loop->recalculatePerfect();
}

void LoopGraph::clearUserDirectives()
{
    if (userDvmDirective)
    {
        //move comment to next statement
        if (userDvmDirective->comments())
        {
            char* comms = userDvmDirective->comments();
            string comments(comms);
            userDvmDirective->delComments();

            SgStatement* next = userDvmDirective->lexNext();
            if (next)
                next->addComment(comments.c_str());
        }

        userDvmDirective->GetOriginal()->deleteStmt();
        userDvmDirective = NULL;
    }
    for (auto& ch : children)
        ch->clearUserDirectives();
}

bool LoopGraph::hasParallelLoopsInChList()
{
    bool result = (directive != NULL);
    for (auto& ch : children)
        result |= ch->hasParallelLoopsInChList();
    return result;
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
    sprintf(buf, "#%d#%d#%d#%d#%d#%d#%d#%d",
        currLoop->lineNum, currLoop->lineNumAfterLoop, currLoop->perfectLoop, currLoop->hasGoto, currLoop->hasPrints, childSize, loopState, 
        currLoop->hasNonRectangularBounds);
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
        result += "#" + std::to_string(currLoop->calls.size());
        for (int i = 0; i < currLoop->calls.size(); ++i)
            result += "#" + currLoop->calls[i].first + "#" + std::to_string(currLoop->calls[i].second);
        printToBuffer(currLoop, calculateNormalChildSize(currLoop), buf);
        result += string(buf);

        result += "#" + std::to_string(currLoop->linesOfExternalGoTo.size());
        for (int i = 0; i < currLoop->linesOfExternalGoTo.size(); ++i)
            result += "#" + std::to_string(currLoop->linesOfExternalGoTo[i]);

        result += "#" + std::to_string(currLoop->linesOfInternalGoTo.size());
        for (int i = 0; i < currLoop->linesOfInternalGoTo.size(); ++i)
            result += "#" + std::to_string(currLoop->linesOfInternalGoTo[i]);

        result += "#" + std::to_string(currLoop->linesOfIO.size());
        for (int i = 0; i < currLoop->linesOfIO.size(); ++i)
            result += "#" + std::to_string(currLoop->linesOfIO[i]);

        result += "#" + std::to_string(currLoop->linesOfStop.size());
        for (int i = 0; i < currLoop->linesOfStop.size(); ++i)
            result += "#" + std::to_string(currLoop->linesOfStop[i]);

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

map<LoopGraph*, ParallelDirective*> findAllDirectives(SgFile *file, const vector<LoopGraph*> &loops, const uint64_t regId)
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
        map<pair<Expression*, string>, Expression*> remotes;
        fillRemoteFromComment(new Statement(st), remotes, false, DVM_PARALLEL_ON_DIR);

        for (auto &newRem : remotes)
        {
            auto key = make_pair(string(newRem.first.first->GetOriginal()->symbol()->identifier()), newRem.first.second);                
            DIST::Array *currArr = getArrayFromDeclarated(declaratedInStmt(newRem.first.first->GetOriginal()->symbol()), key.first);
            newRem.first.first->GetOriginal()->addAttribute(ARRAY_REF, currArr, sizeof(DIST::Array));
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

vector<std::tuple<DIST::Array*, vector<long>, pair<string, int>>> findAllSingleRemotes(SgFile *file, const uint64_t regId, vector<ParallelRegion*> &regions)
{
    vector<std::tuple<DIST::Array*, vector<long>, pair<string, int>>> retVal;

    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        if (st->variant() == DVM_REMOTE_ACCESS_DIR)
        {
            ParallelRegion *currReg = getRegionByLine(regions, st->fileName(), st->lineNumber());
            if (currReg)
            {
                map<pair<Symbol*, string>, Expression*> remotes;
                fillRemoteFromComment(new Statement(st), remotes, false, DVM_REMOTE_ACCESS_DIR);

                for (auto &array : remotes)
                {
                    auto arrName = array.first.first->GetOriginal();
                    DIST::Array *currArr = getArrayFromDeclarated(declaratedInStmt(arrName), arrName->identifier());
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

static void processFuncParameters(LoopGraph *loop, SgExpression *list, const FuncInfo* func)
{
    int parNum = 0;
    while (list)
    {
        if (list->lhs() && list->lhs()->variant() == ARRAY_REF)
        {
            SgSymbol* arrayS = OriginalSymbol(list->lhs()->symbol());
            if (arrayS->type()->variant() != T_STRING)
            {
                DIST::Array* array = getArrayFromDeclarated(declaratedInStmt(arrayS), arrayS->identifier());

                checkNull(array, convertFileName(__FILE__).c_str(), __LINE__);

                if (array->GetNonDistributeFlag() == false)
                    if (func->funcParams.isArgOut(parNum))
                        loop->usedArraysWrite.insert(array);
            }
        }
        ++parNum;
        list = list->rhs();
    }
}

static void processExpression(SgExpression *ex, LoopGraph* loop, const map<string, FuncInfo*> &funcByName)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            const string funcName = ex->symbol()->identifier();
            auto itF = funcByName.find(funcName);
            if (itF != funcByName.end())
                processFuncParameters(loop, ex->lhs(), itF->second);
        }
        processExpression(ex->lhs(), loop, funcByName);
        processExpression(ex->rhs(), loop, funcByName);
    }
}

void completeFillOfArrayUsageBetweenProc(const map<string, vector<LoopGraph*>>& loopGraph, const map<string, vector<FuncInfo*>>& allFuncInfo)
{
    map<string, FuncInfo*> funcByName;
    createMapOfFunc(allFuncInfo, funcByName);

    for (auto& byFile : loopGraph)
    {
        map<int, LoopGraph*> loopsMap;
        createMapLoopGraph(byFile.second, loopsMap);

        if (SgFile::switchToFile(byFile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& loop : loopsMap)
        {
            SgStatement* start = loop.second->loop->GetOriginal();
            SgStatement* end = start->lastNodeOfStmt();

            for (SgStatement* st = start; st != end; st = st->lexNext())
            {
                if (st->variant() == PROC_STAT)
                {
                    const string funcName = st->symbol()->identifier();
                    auto itF = funcByName.find(funcName);
                    if (itF != funcByName.end())
                        processFuncParameters(loop.second, st->expr(0), itF->second);
                }
                for (int z = 0; z < 3; ++z)
                    processExpression(st->expr(z), loop.second, funcByName);
            }
        }
    }
}

bool detectMpiCalls(SgProject* proj, map<string, vector<Messages>>& SPF_messages)
{
    bool retVal = false;

    int n = proj->numberOfFiles();
    for (int i = n - 1; i >= 0; --i)
    {
        SgFile* file = &(proj->file(i));
        string fileName = file->filename();

        SgStatement* st = file->firstStatement();
        while (st)
        {
            if (st->variant() == PROC_STAT)
            {
                if (isMpiFunction(st->symbol()->identifier()))
                {
                    retVal = true;

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"Detected mpi call, turn on special regime of paralyzing");
                    __spf_printToLongBuf(messageR, R148);

                    SPF_messages[fileName].push_back(Messages(NOTE, st->lineNumber(), messageR, messageE, 1051));
                }
            }
            st = st->lexNext();
        }
    }   
    return retVal;
}

void swapLoopsForParallel(map<string, vector<LoopGraph*>>& loopGraph, map<string, vector<Messages>>& SPF_messages, const int reverse)
{
    for (auto& byFile : loopGraph)
    {
        map<int, pair<LoopGraph*, LoopGraph*>> loopHeadr;

        if (SgFile::switchToFile(byFile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        map<int, LoopGraph*> mapGraph;
        createMapLoopGraph(byFile.second, mapGraph);
        for (auto& byLoop : mapGraph)
        {
            auto forSwap = byLoop.second->getForSwap();
            if (forSwap)
                loopHeadr[reverse * byLoop.second->lineNum] = std::make_pair(byLoop.second, forSwap);
        }
        for (auto& loopPair : loopHeadr)
            ((SgForStmt*)loopPair.second.first->loop)->interchangeNestedLoops((SgForStmt*)loopPair.second.second->loop);
    }
}

static bool isVectorAssign(SgStatement *st)
{
    bool ifVector = false;
    if (!st)
        return ifVector;

    auto prev = st->lexPrev();
    if (prev && prev->variant() == CONTROL_END)
    {
        auto cp = prev->controlParent();
        if (cp->variant() == FOR_NODE)
            ifVector = cp->lineNumber() < 0 && cp->localLineNumber() > 0;
    }
    return ifVector;
}

int countPerfectLoopNest(SgStatement* st)
{
    int perfect = 1;
    if (st->variant() != FOR_NODE)
        return perfect;

    perfect = 0;
    SgStatement* next = st;
    SgStatement* last = st->lastNodeOfStmt();
    do {
        vector<SgStatement*> attrSpfPar;
        bool ifVector;
        do {
            next = next->lexNext();
            attrSpfPar.clear();
            if (next)
                attrSpfPar = getAttributes<SgStatement*, SgStatement*>(next, set<int>{ SPF_PARAMETER_OP });
            ifVector = isVectorAssign(next);
        } while (next && (ifVector && notDeletedVectorAssign(next) || attrSpfPar.size() != 0));

        do {
            last = last->lexPrev();
            attrSpfPar.clear();
            if (last)
                attrSpfPar = getAttributes<SgStatement*, SgStatement*>(last, set<int>{ SPF_PARAMETER_OP });
            ifVector = isVectorAssign(last);
        } while (last && (ifVector && notDeletedVectorAssign(last) || attrSpfPar.size() != 0));

        ++perfect;
        if (next == NULL || last == NULL)
            break;
    } while (next->variant() == FOR_NODE && last->variant() == CONTROL_END && next->lastNodeOfStmt() == last);

    return perfect;
}

#undef DEBUG
