#include "private_arrays_breeder.h"
#include "../Utils/SgUtils.h"

#include <set>
#include <queue>
#include <vector>

using std::string;
using std::set;
using std::queue;
using std::vector;


static SgStatement* createNewLoop(SgStatement* orginalArray) {
//    SgStatement *newLoop = new SgDeclarationStatement()0
    return NULL;
}

static char* constructIndexName(int n)
{
    int i = n;
    int extraMem = 0;
    for(i=n; i>0; i/=10)
        extraMem++;

    char *name = (char*)malloc(17 + extraMem + 1);
    strcpy(name, "SPF_breededIndex_");
    name[16 + extraMem + 1] = '\0';

    for(int shift = extraMem; extraMem>0; extraMem--)
    {
        name[16 + extraMem] = char('0' + (n %10));
        n /= 10;
    }

    return name;
}

static SgExpression* constructExtension(int dimensionsAmount, SgExpression *tail)
{
    SgExpression *currList = tail;
    for(int i=0;i<dimensionsAmount;++i)
    {
        char *name = constructIndexName(dimensionsAmount-i);
//        SgExpression* breededIndex = new SgValueExp(dimensionsAmount-i);
        SgExpression* breededIndex = new SgVarRefExp(new SgSymbol(VARIABLE_NAME, name));
        currList = new SgExpression(EXPR_LIST, breededIndex, currList, (SgSymbol*)NULL);
    }

    return currList;
}

static void extendArrayRefs(int dimensionsAmount, SgStatement* st, string &arraySymbol) {

    queue<SgExpression*> toCheck = queue<SgExpression*>();

    for(int i=0;i<3;++i)
        if(st->expr(i))
            toCheck.push(st->expr(i));

    while(!toCheck.empty())
    {
        SgExpression *curExp = toCheck.front();
        toCheck.pop();

        if(curExp->variant() == ARRAY_REF && arraySymbol == string(curExp->symbol()->identifier()))
        {
            curExp->unparsestdout();
            if(curExp->lhs())
            {
                SgExpression* breededIndexes = constructExtension(dimensionsAmount, curExp->lhs());
                curExp->setLhs(breededIndexes);
            }
        }
        else
        {
            if(curExp->lhs())
                toCheck.push(curExp->lhs());
            if(curExp->rhs())
                toCheck.push(curExp->rhs());
        }
    }
}

static void breedArray(LoopGraph *forLoop, string &arraySymbol)
{
    //SgStatement *originalArrayDeclaration = declaratedInStmt(arraySymbol);
    //SgStatement *newLoop = createNewLoop(originalArrayDeclaration);

    SgForStmt *loopStmt = (SgForStmt*)forLoop->loop->GetOriginal();
    if(loopStmt)
    {
        for (SgStatement *st = loopStmt->lexNext(); st != loopStmt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
        {
            extendArrayRefs(forLoop->perfectLoop, st, arraySymbol);
        }
    }
}

//TODO list
/*
 * 1. Добавить индексных новых переменных в существующие обращения - ОК
 * 2. Вычислить размеры новых измерений по циклу
 * 3. Вставить новый масси
 */
void breedArrays(SgFile *file, std::vector<LoopGraph*> &loopGraphs) {


    for(auto& loopGraph : loopGraphs)
    {
        string str("njac");
        //SgSymbol* array = new SgSymbol(ARRAY_REF,"fjac");
        breedArray(loopGraph, str);
        //delete array;
/*
        SgSymbol* array = new SgSymbol("njac");
        breedArray(loopGraph,array);
        delete array;

        SgSymbol* array = new SgSymbol("lhs");
        breedArray(loopGraph,array);
        delete array;*/
    }
}
