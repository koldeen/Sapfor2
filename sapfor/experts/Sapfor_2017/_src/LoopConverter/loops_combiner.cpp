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


static bool expressionsAreEqual(SgExpression* exp1, SgExpression* exp2) {
    if(exp1 == NULL && exp2 == NULL)
        return true;
    if(exp1 != NULL && exp2 != NULL) {
        //TODO smarter???
        string str1 = exp1->unparse();
        string str2 = exp2->unparse();
        return str1 == str2;
    }
    return false;
}
/**
 * Проверить, что объединение возможно и заодно вернуть соответсивие между итерационными переменными.
 */
static bool combinationIsPossible(vector<SgForStmt*> basisLoops, LoopGraph *loop, map<SgSymbol*, SgSymbol*> &symbols) {

    int perfectLoop = loop->perfectLoop;
    LoopGraph *curLoop = loop;
    for (int i = 0; i < basisLoops.size(); ++i)
    {
        SgForStmt *loopStmt = (SgForStmt*) (curLoop->loop->GetOriginal());

        if(!expressionsAreEqual(basisLoops[i]->start(), loopStmt->start()))
            return false;
        if(!expressionsAreEqual(basisLoops[i]->end(), loopStmt->end()))
            return false;
        if(!expressionsAreEqual(basisLoops[i]->step(), loopStmt->step()))
            return false;

        if(string(basisLoops[i]->doName()->identifier()) != string(loopStmt->doName()->identifier()))
            symbols.insert(make_pair(loopStmt->doName(), basisLoops[i]->doName()));

        if (i != basisLoops.size() - 1)
        {
            if(curLoop->children.size() != 1)
                return false;
            curLoop = curLoop->children[0];
        }
    }

    return true;
}

/**
 * Переименовать итерационные переменные цикла, который мы соединяем с основным.
 */
static void renameIterationVariables(map<SgSymbol*, SgSymbol*> &symbols, SgStatement* stmt) {

    queue<SgExpression*> toCheck;
    for(int i=0;i<3;++i) {
        SgExpression* exp = stmt->expr(i);
        if(exp) {
            if(exp->variant() == VAR_REF) {
                auto founded = symbols.find(exp->symbol());
                if(founded != symbols.end())
                    stmt->setExpression(i, new SgExpression(VAR_REF, NULL, NULL, founded->second, founded->second->type()));
            }
            else
                toCheck.push(exp);
        }
    }

    while(!toCheck.empty()) {
        SgExpression *mainExp = toCheck.front();
        toCheck.pop();

        SgExpression *exp = mainExp->lhs();
        if (exp)
        {
            if (exp->variant() == VAR_REF)
            {
                auto founded = symbols.find(exp->symbol());
                if(founded != symbols.end())
                    mainExp->setLhs(new SgExpression(VAR_REF, NULL, NULL, founded->second, founded->second->type()));
            }
            else
                toCheck.push(exp);
        }

        exp = mainExp->rhs();
        if (exp)
        {
            if (exp->variant() == VAR_REF)
            {
                auto founded = symbols.find(exp->symbol());
                if(founded != symbols.end())
                    mainExp->setRhs(new SgExpression(VAR_REF, NULL, NULL, founded->second, founded->second->type()));
            }
            else
                toCheck.push(exp);
        }
    }
}

static SgForStmt* getInnerLoop(LoopGraph* loop, int deep)
{
    int perfectLoop = loop->perfectLoop;
    LoopGraph *curLoop = loop;
    SgForStmt *result = NULL;
    for(int i = 0; i < deep ; ++i) {
        result = (SgForStmt*) (curLoop->loop->GetOriginal());
        if(i != perfectLoop - 1) {
            curLoop = curLoop->children[0];
        }
    }

    return result;
}

static void moveBody(SgForStmt *from, SgForStmt *to, map<SgSymbol*, SgSymbol*> &symbols)
{
    SgStatement* insertBefore = to->lastNodeOfStmt();
    SgStatement* controlParent = insertBefore->controlParent();
    SgStatement* moveTill = from->lastNodeOfStmt();
    SgStatement* toMove = from->lexNext();
    while(toMove != moveTill) {
        SgStatement *st = toMove;
        toMove = toMove->lastNodeOfStmt()->lexNext();

        renameIterationVariables(symbols, st);
        insertBefore->insertStmtBefore(*st->extractStmt(), *controlParent);
    }
}

/**
 * Собственно объединение
 */
static void combine(LoopGraph *firstLoop, vector<LoopGraph*> &followingLoops) {

    int perfectLoop = firstLoop->perfectLoop;
    LoopGraph* curLoop = firstLoop;
    vector<SgForStmt*> basisLoops(perfectLoop);

    for(int i = 0; i < perfectLoop; ++i) {
        SgForStmt *loopStmt = (SgForStmt*) (curLoop->loop->GetOriginal());
        basisLoops[i] = loopStmt;

        if(i != perfectLoop - 1) {
            curLoop = curLoop->children[0];
        }
    }

/*    for(SgForStmt* basisLoop : basisLoops) {
        printf("%s - ", basisLoop->doName()->identifier());
        printf("%s : ", basisLoop->start()->unparse());
        printf("%s : ", basisLoop->end()->unparse());
        printf("%s\n",  basisLoop->step() == NULL ? "(null)" : basisLoop->step()->unparse());
    }*/

    SgForStmt *innerMainLoop = getInnerLoop(firstLoop, basisLoops.size());


    for(LoopGraph* loop : followingLoops) {
        map<SgSymbol*, SgSymbol*> symbols;
        if(combinationIsPossible(basisLoops, loop, symbols))
        {
/*            for(auto pair : symbols)
                printf("%s - %s\n", pair.first->identifier(), pair.second->identifier());
            printf("\n");*/
            moveBody(getInnerLoop(loop, basisLoops.size()), innerMainLoop, symbols);
            loop->loop->deleteStmt();
        }
        else
            break;
    }
}

/**
 * Возвращает следующие loopsAmount циклов после followAfterThis.
 * Если loopsAmount < 0, вернёт все последующие циклы, до первого оператора-не-цикла.
 */
vector<LoopGraph*> getFollowingLoops(LoopGraph* followAfterThis, vector<LoopGraph*> &loops, int loopsAmount) {

    vector<LoopGraph*> result;
    SgStatement *lastSt = followAfterThis->loop->lastNodeOfStmt();
    for(LoopGraph* loop : loops) {
        SgStatement *loopSt = loop->loop;
        if(loopSt->lineNumber() <= lastSt->lineNumber())
            continue;

        if(loop->loop->lineNumber() == lastSt->lexNext()->lineNumber())
        {
            if(loopsAmount-- == 0)
                break;
            lastSt = loop->loop->lastNodeOfStmt();
            result.push_back(loop);
        }
        else
            break;
    }

    return result;
}

int combineLoops(SgFile *file, vector<LoopGraph*> &loopGraphs, vector<Messages> &messages)
{

    if(string("rhs.f") == file->filename())
    {
        for(LoopGraph* loop : loopGraphs) {
            if(loop->loop->lineNumber() == 152) {
                vector<LoopGraph*> followingLoops = getFollowingLoops(loop, loopGraphs, -1);
                combine(loop, followingLoops);
            }
        }
    }
    return 0;
}
