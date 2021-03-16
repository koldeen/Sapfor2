#include "loops_combiner.h"

#include "../LoopAnalyzer/loop_analyzer.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../Utils/errors.h"
#include <string>
#include <vector>
#include <queue>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::make_pair;
using std::queue;
using std::wstring;


static bool expressionsAreEqual(SgExpression *exp1, SgExpression *exp2) 
{
    if (exp1 == NULL && exp2 == NULL)
        return true;

    if (exp1 != NULL && exp2 != NULL) 
    {
        string str1 = exp1->unparse();
        string str2 = exp2->unparse();
        return str1 == str2;
    }

    return false;
}

/**
 * Проверить, что объединение возможно и заодно вернуть соответсивие между итерационными переменными.
 */
static bool combinationIsPossible(const vector<SgForStmt*>& basisLoops, LoopGraph *loop, map<SgSymbol*, SgSymbol*>& symbols) 
{
    int perfectLoop = loop->perfectLoop;
    LoopGraph *curLoop = loop;

    for (int i = 0; i < basisLoops.size(); ++i)
    {
        if (curLoop->hasLimitsToSplit())
            return false;

        SgForStmt *loopStmt = (SgForStmt*) (curLoop->loop->GetOriginal());
        if (!expressionsAreEqual(basisLoops[i]->start(), loopStmt->start()))
            return false;

        if (!expressionsAreEqual(basisLoops[i]->end(), loopStmt->end()))
            return false;

        if (!expressionsAreEqual(basisLoops[i]->step(), loopStmt->step()))
            return false;

        if (string(basisLoops[i]->doName()->identifier()) != string(loopStmt->doName()->identifier()))
            symbols.insert(make_pair(loopStmt->doName(), basisLoops[i]->doName()));

        if (i != basisLoops.size() - 1)
        {
            if (curLoop->children.size() != 1)
                return false;

            curLoop = curLoop->children[0];
        }
    }

    return true;
}

/**
 * Переименовать итерационные переменные цикла, который мы соединяем с основным.
 */
static void renameIterationVariables(const map<SgSymbol*, SgSymbol*> &symbols, SgExpression *ex) 
{
    if (ex)
    {
        if (ex->variant() == VAR_REF)
        {
            auto founded = symbols.find(ex->symbol());
            if (founded != symbols.end())
                ex->setSymbol(founded->second);
        }
        else
        {
            renameIterationVariables(symbols, ex->lhs());
            renameIterationVariables(symbols, ex->rhs());
        }
    }
}

static SgForStmt* getInnerLoop(LoopGraph *loop, int deep)
{
    int perfectLoop = loop->perfectLoop;
    LoopGraph *curLoop = loop;
    SgForStmt *result = NULL;

    for (int i = 0; i < deep ; ++i) 
    {
        result = (SgForStmt*) (curLoop->loop->GetOriginal());
        if (i != perfectLoop - 1) 
            curLoop = curLoop->children[0];
    }

    return result;
}

static void moveBody(SgForStmt *from, SgForStmt *to, const map<SgSymbol*, SgSymbol*>& symbols)
{
    for (auto st = from->lexNext(); st != from->lastNodeOfStmt(); st = st->lexNext())
        for (int i = 0; i < 3; ++i)
            renameIterationVariables(symbols, st->expr(i));

    auto loopBody = from->extractStmtBody();
    to->lastExecutable()->insertStmtAfter(*loopBody, *to);
}

/**
 * Собственно объединение
 */
static bool combine(LoopGraph *firstLoop, const vector<LoopGraph*>& nextLoops, set<LoopGraph*>& combinedLoops, vector<Messages>& messages)
{
    bool wasCombine = false;
    int perfectLoop = firstLoop->perfectLoop;
    LoopGraph* curLoop = firstLoop;
    vector<SgForStmt*> basisLoops(perfectLoop);

    for (int i = 0; i < perfectLoop; ++i) 
    {
        SgForStmt *loopStmt = (SgForStmt*) (curLoop->loop->GetOriginal());
        basisLoops[i] = loopStmt;
        
        if (curLoop->hasLimitsToSplit())
            return false;

        if (i != perfectLoop - 1) 
            curLoop = curLoop->children[0];
    }

    SgForStmt *innerMainLoop = getInnerLoop(firstLoop, basisLoops.size());
    for (auto& loop : nextLoops)
    {
        map<SgSymbol*, SgSymbol*> symbols;
        if (combinationIsPossible(basisLoops, loop, symbols))
        {
            moveBody(getInnerLoop(loop, basisLoops.size()), innerMainLoop, symbols);
            if (loop->loop->comments())
                firstLoop->loop->addComment(string(loop->loop->comments()).c_str());

            loop->loop->extractStmt();

            combinedLoops.insert(loop);
            wasCombine = true;

            if (loop->perfectLoop < perfectLoop)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            //move in structure
            LoopGraph* deep = loop;
            for (int p = 0; p < perfectLoop - 1; ++p)
                deep = deep->children[0];

            for (auto& toMove : deep->children)
            {
                firstLoop->children.push_back(toMove);
                toMove->parent = firstLoop;
            }
            deep->children.clear();

#ifdef _WIN32
            wstring strR, strE;
            __spf_printToLongBuf(strE, L"Loops on line %d and on line %d were combined", firstLoop->lineNum, loop->lineNum);
            __spf_printToLongBuf(strR, R100, firstLoop->lineNum, loop->lineNum);

            messages.push_back(Messages(NOTE, firstLoop->lineNum, strR, strE, 2005));
#endif
            __spf_print(1, "Loops on lines %d and %d were combined\n", firstLoop->lineNum, loop->lineNum);
        }
        else
        {
            break;
        }
    }

    return wasCombine;
}

/**
 * Возвращает следующие loopsAmount циклов после nextAfterThis.
 * Если loopsAmount < 0, вернёт все последующие циклы, до первого оператора-не-цикла.
 */
static vector<LoopGraph*> getNextLoops(LoopGraph *nextAfterThis, vector<LoopGraph*>& loops, int loopsAmount) 
{
    vector<LoopGraph*> result;
    SgStatement *lastSt = nextAfterThis->loop->lastNodeOfStmt();

    int z = 0;
    for (; z < loops.size(); ++z)
        if (loops[z] == nextAfterThis)
            break;
    if (z == loops.size())
        return result;
    else
        z++;

    for (; z < loops.size(); ++z)
    {
        if (loopsAmount == 0)
            break;

        SgStatement *loopSt = loops[z]->loop->GetOriginal();
        if (lastSt->lexNext() != loopSt)
            break;
        else
        {
            lastSt = loopSt->lastNodeOfStmt();
            result.push_back(loops[z]);
            --loopsAmount;
        }
    }

    return result;
}


static bool tryToCombine(vector<LoopGraph*>& loopGraphs, vector<Messages>& messages)
{
    if (loopGraphs.size() == 0)
        return false;

    bool change = false;
    vector<LoopGraph*> newloopGraphs;
    for (int z = 0; z < loopGraphs.size(); ++z)
    {
        auto& loop = loopGraphs[z];
        newloopGraphs.push_back(loop);
        vector<LoopGraph*> nextLoops = getNextLoops(loop, loopGraphs, -1);

        set<LoopGraph*> combinedLoops;
        change = false;
        if (nextLoops.size())
            change = combine(loop, nextLoops, combinedLoops, messages);

        if (change && loop->parent)
            loop->parent->recalculatePerfect();

        if (combinedLoops.size())
        {
            for (auto& elem : combinedLoops)
                delete elem;
            z += combinedLoops.size();
        }
    }
    loopGraphs = newloopGraphs;

    if (change == false)
    {
        for (auto& ch : loopGraphs)
        {
            bool res = tryToCombine(ch->children, messages);
            change |= res;
        }
    }
    return change;
}

int combineLoops(SgFile *file, vector<LoopGraph*>& loopGraphs, vector<Messages>& messages, const pair<string, int> &onPlace)
{
    map<int, LoopGraph*> mapGraph;
    createMapLoopGraph(loopGraphs, mapGraph);

    if (onPlace.second > 0)
    {
        if (onPlace.first != file->filename())
            return 0;
        else
        {
            const int onLine = onPlace.second;

            auto it = mapGraph.find(onLine);
            if (it == mapGraph.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            vector<LoopGraph*> nextLoops = getNextLoops(it->second, it->second->parent ? it->second->parent->children : loopGraphs, 1);
            set<LoopGraph*> combinedLoops;
            if (nextLoops.size())
                combine(it->second, nextLoops, combinedLoops, messages);

            return 0;
        }
    }

    bool change = true; 
    while (change)
        change = tryToCombine(loopGraphs, messages);
    return 0;
}
