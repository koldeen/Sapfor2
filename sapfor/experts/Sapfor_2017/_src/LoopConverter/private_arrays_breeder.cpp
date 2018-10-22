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
    while(oldTail->rhs() != NULL) {
        oldTail->setLhs(new SgExpression(DDOT));
        oldTail = oldTail->rhs();
    }
    oldTail->setLhs(new SgExpression(DDOT));
    oldTail->setRhs(newTail);
}

static void extendArrayRef(const vector<SgSymbol*> &indexes, SgExpression *expressionToExtend)
{
    SgExpression *newTail = NULL;
    for (int i = indexes.size() - 1; i >= 0; --i)
    {
        SgExpression *breededIndex = new SgVarRefExp(indexes[i]);
        newTail = new SgExpression(EXPR_LIST, breededIndex, newTail, (SgSymbol*) NULL);
    }

    SgExpression *oldTail = expressionToExtend->lhs();
    while (oldTail->rhs() != NULL)
        oldTail = oldTail->rhs();
    oldTail->setRhs(newTail);
}

static void setAllocatable(SgStatement *newDecl)
{
    SgExpression *params = newDecl->expr(2);
    if(params != NULL) { //ALLOCATABLE может уже быть
        while(params != NULL) {
            if(params->lhs()->variant() == ALLOCATABLE_OP)
                return;
            params = params->rhs();
        }
    }

    params = newDecl->expr(2);
    SgExpression newParams (EXPR_LIST, new SgExpression(ALLOCATABLE_OP), params, (SgSymbol*)NULL);
    newDecl->setExpression(2, newParams);
}

static SgSymbol* alterArrayDeclaration(SgStatement* declarationStatement, SgSymbol *arraySymbol, vector<int> &dimensions) {
    setAllocatable(declarationStatement);

    for(SgExpression *exprList = declarationStatement->expr(0); exprList != NULL; exprList = exprList->rhs())
    {
        SgExpression *array = exprList->lhs();
        if(array && array->variant() == ARRAY_REF && !strcmp(array->symbol()->identifier(), arraySymbol->identifier()))
        {//нашли объявление исходного массива
            SgExpression *newArray = array->copyPtr();
            extendArrayDeclaration(dimensions, newArray);

            SgExpression newExprList(EXPR_LIST, newArray, (SgExpression*)NULL, (SgSymbol*)NULL);
            declarationStatement->setExpression(0,newExprList);
            return createNewArrayNameSymbol(newArray);
        }
    }
    //На самом деле, это недостижимый код
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

static SgStatement* createNewDeclarationStatemnet(SgStatement *originalDeclaration, SgSymbol* arraySymbol)
{
    SgStatement *firstStmtOfFile = NULL;
    for (firstStmtOfFile = originalDeclaration; strcmp(firstStmtOfFile->fileName(), current_file->filename()); firstStmtOfFile = firstStmtOfFile->lexNext())
    {}// Yes, it's an empty for loop

    SgExpression *exprList = NULL;
    for (exprList = originalDeclaration->expr(0); strcmp(exprList->lhs()->symbol()->identifier(), arraySymbol->identifier()); exprList = exprList->rhs())
    {}// More empty loops, MOAR!

    SgExpression newExprList(EXPR_LIST, exprList->lhs(), NULL, NULL);
    SgStatement newDeclaration = originalDeclaration->copy();

    newDeclaration.setExpression(0, newExprList);
    firstStmtOfFile->insertStmtAfter(newDeclaration);

    return firstStmtOfFile->lexNext();
}

static SgExpression* constructBoundCall(bool upBound, SgSymbol *array, int dim) {

    char* boundName = (char*)malloc(7 * sizeof(char));
    upBound ? strcpy(boundName, "ubound") : strcpy(boundName, "lbound");

    SgSymbol boundS = SgSymbol(FUNCTION_NAME, boundName);

    SgExpression *dimParam = new SgExpression(EXPR_LIST, new SgValueExp(dim), NULL, NULL);
    SgExpression params(EXPR_LIST, new SgExpression(ARRAY_REF, NULL, NULL, array), dimParam, NULL);

    return new SgFunctionCallExp(boundS, params);
}

static SgExpression* constructArrayAllocationExp(LoopGraph *forLoop, SgExpression *origArray, SgSymbol *arraySymbol, int depthOfBreed) {

    SgExpression *arrayRef = origArray->copyPtr();
    arrayRef->setSymbol(arraySymbol);
    vector<SgExpression*> dimensions(depthOfBreed);
    LoopGraph *curLoop = forLoop;
    for(int i = 0; i < depthOfBreed; ++i)
    {
        SgForStmt *loopStmt = (SgForStmt*)(curLoop->loop->GetOriginal());
        dimensions[i] = new SgExpression(DDOT, loopStmt->start()->copyPtr(), loopStmt->end()->copyPtr(), (SgSymbol*)NULL);
        curLoop = curLoop->children[0];
    }

    SgExpression *newTail = NULL;
    for(int i=dimensions.size()-1; i>=0 ;--i)
        newTail = new SgExpression(EXPR_LIST, dimensions[i], newTail, (SgSymbol*)NULL);

    SgExpression *oldTail = arrayRef->lhs();
    SgSymbol *origArraySymbol = origArray->symbol();
    int curDim = 0;
    SgExpression *attachTo = oldTail;
    while (oldTail != NULL)
    {
        curDim++;
        if (oldTail->lhs()->variant() == DDOT)
        {
            SgExpression *ddot = oldTail->lhs();
            if (!ddot->lhs())
                ddot->setLhs(constructBoundCall(false, origArraySymbol, curDim));
            if (!ddot->rhs())
                ddot->setRhs(constructBoundCall(true, origArraySymbol, curDim));
        }
        oldTail = oldTail->rhs();
        if(oldTail)
            attachTo = oldTail;
    }
     attachTo->setRhs(newTail);

    return new SgExpression(EXPR_LIST, arrayRef, (SgExpression*)NULL, (SgSymbol*)NULL);
}

static void insertAllocDealloc(LoopGraph *forLoop, SgStatement *originalDeclaration, SgSymbol *origArraySymbol, SgSymbol *arraySymbol, int depthOfBreed) {

    SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());

    SgExpression *origArray = NULL;
    for (origArray = originalDeclaration->expr(0); strcmp(origArray->lhs()->symbol()->identifier(), origArraySymbol->identifier()); origArray = origArray->rhs())
    {}// Yes-yes-yes, YEEEEEEESSSSS!!!
    origArray = origArray->lhs();

    SgExpression *arrayAllocation = constructArrayAllocationExp(forLoop, origArray, arraySymbol, depthOfBreed);
    SgExpression *arrayDeallocation = new SgExpression(EXPR_LIST, new SgExpression(ARRAY_REF, (SgExpression*)NULL, (SgExpression*)NULL, arraySymbol), (SgExpression*)NULL, (SgSymbol*)NULL);

    SgStatement allocate  (ALLOCATE_STMT, (SgLabel*)NULL, (SgSymbol*)NULL, arrayAllocation, (SgExpression*)NULL, (SgExpression*)NULL);
    SgStatement deallocate(DEALLOCATE_STMT, (SgLabel*)NULL, (SgSymbol*)NULL, arrayDeallocation, (SgExpression*)NULL, (SgExpression*)NULL);

    loopStmt->insertStmtBefore(allocate);
    loopStmt->lastNodeOfStmt()->insertStmtAfter(deallocate);
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

    SgStatement *originalDeclaration = declaratedInStmt(arraySymbol);
    SgStatement *copiedOriginalArrayDeclaration = createNewDeclarationStatemnet(originalDeclaration, arraySymbol);
    SgSymbol *newArraySymbol = alterArrayDeclaration(copiedOriginalArrayDeclaration, arraySymbol, dimensions);

    SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());
    if(newArraySymbol)
        insertAllocDealloc(forLoop, originalDeclaration, arraySymbol, newArraySymbol, indexes.size());
        for (SgStatement *st = loopStmt->lexNext(); st != loopStmt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
            if(st->variant() != ALLOCATE_STMT && st->variant() != DEALLOCATE_STMT)
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
    return NULL;
}

//TODO list
/*
 * 1. Добавить индексных новых переменных в существующие обращения - ОК
 * 2. Вычислить размеры новых измерений по циклу - ok
 * 3. Вставить новый массив - в текущий файл - ok
 * 4. Переименовывать массивы, когда расширяем их - ok
 * 5. breeded -> br1, br2, ... - ok
 * 6. Добавлять измерения в хвост, а не в начало - ok
 * 7. Кол-во измерений зависит от depthOfBreed - ok
 * 8. Вычислять размер массива с учётом шага цикла - В топку //TODO
 * 9. Выделять массив как allocateable - ok
 * 10. добавить alllocate/deallocate перед/после цикла
 * 11. что делать с существующими allocate/deallocate? не трогать -ok
 * 12. lbound, rbound для allocatabel массивов - ok
 */
void breedArrays(SgFile *file, std::vector<LoopGraph*> &loopGraphs) {
    if(string(file->filename()) == "z_solve_inlined.f")
        for(auto& loopGraph : loopGraphs)
        {
            SgSymbol *array = findArray(loopGraph, "njac");
            if(array)
                breedArray(loopGraph, array, -1);
        }
}
