#include "private_arrays_breeder.h"
#include "../GraphLoop/graph_loops.h"
#include "../Utils/SgUtils.h"

#include <set>
#include <queue>
#include <vector>

using std::string;
using std::set;
using std::queue;
using std::vector;

static char* constructNewArrayName(const char* oldName)
{
    string name(oldName), newName;
    name += "_br";
    newName = name + std::to_string(1);
    for(int n = 2; ifSymbolExists(current_file, newName); ++n)
        newName = name + std::to_string(n);

    char* newNameChar = (char*)malloc((newName.size() + 1) * sizeof(char));
    strcpy(newNameChar, newName.c_str());
    return newNameChar;
}

static SgSymbol* createNewArrayNameSymbol(SgExpression* declaration)
{
    SgSymbol* newName = new SgSymbol(VARIABLE_NAME, constructNewArrayName(declaration->symbol()->identifier()));
    declaration->setSymbol(newName);
    return newName;
}

static void extendArrayDeclaration(const vector<int> &dimensions, SgExpression *expressionToExtend)
{
    SgExpression *newTail = NULL;
    for (int i = dimensions.size() - 1; i >= 0; --i)
    {
        SgExpression *breededIndex = new SgExpression(DDOT);//new SgValueExp(dimensions[i]);
        newTail = new SgExpression(EXPR_LIST, breededIndex, newTail, (SgSymbol*) NULL);
    }

    SgExpression *oldTail = expressionToExtend->lhs();
    while(oldTail->rhs() != NULL)
        oldTail = oldTail->rhs();
    oldTail->setRhs(newTail);
}

static void extendArrayRef(const vector<SgSymbol*> &indexes, SgExpression *expressionToExtend)
{
    SgExpression *newTail = NULL;
    for(int i = indexes.size()-1; i >= 0; --i)
    {
        SgExpression *breededIndex = new SgVarRefExp(indexes[i]);
        newTail = new SgExpression(EXPR_LIST, breededIndex, newTail, (SgSymbol*)NULL);
    }

    SgExpression *oldTail = expressionToExtend->lhs();
    while(oldTail->rhs() != NULL)
        oldTail = oldTail->rhs();
    oldTail->setRhs(newTail);
}

static SgSymbol* alterArrayDeclaration(SgStatement* declarationStatement, SgSymbol *arraySymbol, vector<int> &dimensions) {

    for(SgExpression *exprList = declarationStatement->expr(0); exprList != NULL; exprList = exprList->rhs())
    {
        SgExpression *array = exprList->lhs();
        if(array && array->variant() == ARRAY_REF && !strcmp(array->symbol()->identifier(), arraySymbol->identifier()))
        {//нашли объявление исходного массива
            extendArrayDeclaration(dimensions, array);
            createNewArrayNameSymbol(array);

            SgExpression *newRhs = new SgExpression(EXPR_LIST, array, exprList->rhs(), (SgSymbol*)NULL);
            exprList->setRhs(newRhs);

            return array->symbol();
        }
    }
    return NULL;
}

static void extendArrayRefs(const vector<SgSymbol*> &indexes, SgStatement* st, SgSymbol *arraySymbol, SgSymbol *newArraySymbol) {

    queue<SgExpression*> toCheck = queue<SgExpression*>();

    for(int i=0;i<3;++i)
        if(st->expr(i))
            toCheck.push(st->expr(i));

    while(!toCheck.empty())
    {
        SgExpression *curExp = toCheck.front();
        toCheck.pop();

        if(curExp->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), curExp->symbol()->identifier()))
        {
            extendArrayRef(indexes, curExp);
            curExp->setSymbol(newArraySymbol);
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

static SgStatement* createNewDeclarationStatemnet(SgSymbol* arraySymbol)
{
    SgStatement *originalDeclaration = declaratedInStmt(arraySymbol);

    SgStatement *firstStmtOfFile = NULL;
    for (firstStmtOfFile = originalDeclaration; strcmp(firstStmtOfFile->fileName(), current_file->filename()); firstStmtOfFile = firstStmtOfFile->lexNext())
    {}// Yes, it's an empty for loop

    SgExpression *exprList = NULL;
    for (exprList = originalDeclaration->expr(0); strcmp(exprList->lhs()->symbol()->identifier(), arraySymbol->identifier()); exprList = exprList->rhs())
    {}// More empty loops, MOAR!

    SgExpression newExprList(EXPR_LIST, exprList->lhs(), NULL, NULL);
    SgStatement newDeclaration = originalDeclaration->copy();

    newDeclaration.setExpression(0, newExprList);
    firstStmtOfFile->insertStmtBefore(newDeclaration);

    SgStatement* inserted = firstStmtOfFile->lexPrev();
    return originalDeclaration;
}

static void breedArray(LoopGraph *forLoop, SgSymbol *arraySymbol, int depthOfBreed)
{
    if(depthOfBreed < 0 || depthOfBreed > forLoop->perfectLoop)
        depthOfBreed = forLoop->perfectLoop;

    vector<int> dimensions(depthOfBreed);
    vector<SgSymbol*> indexes(depthOfBreed);

    LoopGraph *curLoop = forLoop;
    for(int i = 0; i < depthOfBreed; ++i)
    {
        SgForStmt *loopStmt = (SgForStmt*)(curLoop->loop->GetOriginal());
        if(curLoop->calculatedCountOfIters == 0)
            return; //TODO

        dimensions[i] = curLoop->calculatedCountOfIters;
        indexes[i] = loopStmt->doName();

        if(curLoop->children.size() == 1)
            curLoop = curLoop->children[0];
        else if(i != depthOfBreed-1)
            return;
    }

    SgStatement *copiedOriginalArrayDeclaration = createNewDeclarationStatemnet(arraySymbol);
    SgSymbol *newArraySymbol = alterArrayDeclaration(copiedOriginalArrayDeclaration, arraySymbol, dimensions);

    SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());
    if(newArraySymbol)
        for (SgStatement *st = loopStmt->lexNext(); st != loopStmt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
            extendArrayRefs(indexes, st, arraySymbol, newArraySymbol);
}

//for testing
static SgSymbol *findArray(LoopGraph*  forLoop, const char* arrayName)
{
    SgForStmt *loopStmt = (SgForStmt*)forLoop->loop->GetOriginal();
    if(loopStmt)
    {
        for (SgStatement *st = loopStmt->lexNext(); st != loopStmt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
        {
            queue<SgExpression*> toCheck = queue<SgExpression*>();

            for(int i=0;i<3;++i)
                if(st->expr(i))
                    toCheck.push(st->expr(i));

            while(!toCheck.empty())
            {
                SgExpression *curExp = toCheck.front();
                toCheck.pop();

                if(curExp->variant() == ARRAY_REF && !strcmp(arrayName, curExp->symbol()->identifier()))
                    return curExp->symbol();
                else
                {
                    if(curExp->lhs())
                        toCheck.push(curExp->lhs());
                    if(curExp->rhs())
                        toCheck.push(curExp->rhs());
                }
            }
        }
    }
}

//TODO list
/*
 * 1. Добавить индексных новых переменных в существующие обращения - ОК
 * 2. Вычислить размеры новых измерений по циклу - ok
 * 3. Вставить новый массив - в текущий файл - ok
 * 4. Переименовывать массивы, когда расширяем их - ok
 *
 * 1. breeded -> br1, br2, ... - ok
 * 2. Добавлять измерения в хвост, а не в начало - ok
 * 3. Кол-во измерений зависит от depthOfBreed - ok
 * 4. Вычислять размер массива с учётом шага цикла - В топку
 * 5. Выделять массив как allocateable
 * 6. добавить alllocate/deallocate перед/после цикла
 */
void breedArrays(SgFile *file, std::vector<LoopGraph*> &loopGraphs) {
    if(string(file->filename()) == "z_solve_inlined.f")
        for(auto& loopGraph : loopGraphs)
        {
            SgSymbol *array = findArray(loopGraph, "njac");
            if(array)
                breedArray(loopGraph, array, -1);


/*            array = findArray(loopGraph, "fjac");
            if(array)
                breedArray(loopGraph, array);
*/
/*
            SgSymbol* array = new SgSymbol("njac");
            breedArray(loopGraph,array);
            delete array;

            SgSymbol* array = new SgSymbol("lhs");
            breedArray(loopGraph,array);
            delete array;*/
        }
}
