#include "private_arrays_breeder.h"
#include "../GraphLoop/graph_loops.h"
#include "../Utils/SgUtils.h"
#include "../Utils/utils.h"
#include "../Utils/errors.h"
#include "../LoopAnalyzer/directive_parser.h"

#include <set>
#include <queue>
#include <vector>

using std::string;
using std::set;
using std::map;
using std::queue;
using std::vector;

static void printExp(SgExpression* exp) {
    queue<SgExpression*> qq;
    qq.push(exp);
    printf("Expression: ");
    while(!qq.empty())
    {
        SgExpression* exp = qq.front();
        qq.pop();

        printf("[%s]: %s\n", tag[exp->variant()], exp->unparse());
        if(exp->variant() == TYPE_OP)
        {
            if(exp->symbol())
                printf("%s, %s", exp->symbol()->identifier(), tag[exp->symbol()->variant()]);
        }

        if(exp->lhs())
            qq.push(exp->lhs());
        if(exp->rhs())
            qq.push(exp->rhs());
    }
}

static void printSt(SgStatement* st)
{
    printf("Statement [%s]: %s\n", tag[st->variant()], st->unparse());
    queue<SgExpression*> qq;
    for(int i=0;i<3;++i)
        if(st->expr(i))
        {
            printf("[%d,%s]: %s\n",i, tag[st->expr(i)->variant()], st->expr(i)->unparse());
            qq.push(st->expr(i));
        }
    while(!qq.empty())
    {
        SgExpression* exp = qq.front();
        qq.pop();

        printf("[%s]: %s\n", tag[exp->variant()], exp->unparse());
        if(exp->variant() == TYPE_OP)
        {
            if(exp->symbol())
                printf("%s, %s", exp->symbol()->identifier(), tag[exp->symbol()->variant()]);
        }

        if(exp->lhs())
            qq.push(exp->lhs());
        if(exp->rhs())
            qq.push(exp->rhs());
    }
}

static char* constructNewArrayName(const char* oldName, bool breed)
{
    string name(oldName), newName;
    name += breed ? "_br" : "_debr";
    newName = name + std::to_string(1);
    for(int n = 2; ifSymbolExists(current_file, newName); ++n)
        newName = name + std::to_string(n);

    char* newNameChar = (char*)malloc((newName.size() + 1) * sizeof(char));
    addToCollection(__LINE__, __FILE__, newNameChar, 0);
    if (newNameChar)
        strcpy(newNameChar, newName.c_str());
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return newNameChar;
}

static const string constructNewBoundName(const char* oldName, int loopLineNumber, const char *add)
{
    string name(oldName), newName;
    name += "_loop_" + std::to_string(loopLineNumber);
    name += add;// start ? "_start" : "_end";
    newName = name;
    for(int n = 0; ifSymbolExists(current_file, newName); ++n)
        newName = name + "_" + std::to_string(n);
    return newName;
}

static SgSymbol* createNewArrayNameSymbol(SgExpression* declaration, bool breed)
{
    SgType *type = new SgType(T_ARRAY);
    SgSymbol* newName = new SgSymbol(VARIABLE_NAME, constructNewArrayName(declaration->symbol()->identifier(), breed), type, NULL);
    return newName;
}

static void extendArrayDeclaration(const vector<int> &dimensions, SgExpression *&expressionToExtend, SgSymbol* newArraySymbol)
{
    expressionToExtend->setSymbol(newArraySymbol);
    SgExpression *newTail = NULL;
    for (int i = dimensions.size() - 1; i >= 0; --i)
    {
        SgExpression *breededIndex = new SgExpression(DDOT);//new SgValueExp(dimensions[i]);
        newTail = new SgExpression(EXPR_LIST, breededIndex, newTail, (SgSymbol*) NULL);
    }

    SgExpression *oldTail = expressionToExtend->lhs();
    if (oldTail == NULL) // create array from scalar
    {
        expressionToExtend = new SgArrayRefExp(*newArraySymbol);
        expressionToExtend->setLhs(newTail);
    }
    else
    {
        while (oldTail->rhs() != NULL)
        {
            oldTail->setLhs(new SgExpression(DDOT));
            oldTail = oldTail->rhs();
        }
        oldTail->setLhs(new SgExpression(DDOT));
        oldTail->setRhs(newTail);
    }
}

static void reduceArray(const vector<int> &indexes, SgExpression *&expressionToReduce) {
    SgExpression *preTail = expressionToReduce;
    SgExpression *tail = expressionToReduce->lhs();
    for(int i=0;i<indexes.size();++i) {
        if(indexes[i] == 1) {
            if(preTail == expressionToReduce)
                preTail->setLhs(tail->rhs());
            else
                preTail->setRhs(tail->rhs());
        } else {
            preTail = tail;
            tail = tail->rhs();
        }
    }
}

static SgExpression* extendArrayRef(const vector<SgSymbol*> &indexes, SgExpression *expressionToExtend, SgSymbol *newSymbol, const vector<SgExpression*> &lowBounds)
{
    SgExpression *newTail = NULL;
    for (int i = indexes.size() - 1; i >= 0; --i)
    {
        SgExpression *breededIndex = new SgVarRefExp(indexes[i]);
        newTail = new SgExpression(EXPR_LIST, breededIndex, newTail, (SgSymbol*) NULL);
    }

    SgExpression *oldTail = expressionToExtend->lhs();
    if(oldTail == NULL) 
    {
        if (expressionToExtend->variant() == VAR_REF) // create array from scalar
        {
            expressionToExtend = new SgArrayRefExp(*newSymbol);
            expressionToExtend->setLhs(newTail);
        }
        else if (expressionToExtend->variant() == ARRAY_REF) // create array from full array ref
        {
            SgArrayRefExp *curr = (SgArrayRefExp*)expressionToExtend;
            expressionToExtend->setSymbol(newSymbol);
            for (auto &elem : lowBounds) // add low bounds
                curr->addSubscript(*elem); 
            curr->addSubscript(*newTail);
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    else
    {
        while (oldTail->rhs() != NULL)
            oldTail = oldTail->rhs();
        oldTail->setRhs(newTail);
        expressionToExtend->setSymbol(newSymbol);
    }

    return expressionToExtend;
}

static void setAllocatable(SgStatement *newDecl, SgSymbol *origSymbol)
{
    //Обычное объявление
    if(newDecl->variant() == VAR_DECL)
    {
        SgExpression *params = newDecl->expr(2);
        if(params != NULL) { //ALLOCATABLE может уже быть
            while(params != NULL) {
                if(params->lhs()->variant() == ALLOCATABLE_OP)
                    return;
                params = params->rhs();
            }
        }

        //В объявлении нет ALLOCATABLE
        params = newDecl->expr(2);
        SgExpression newParams (EXPR_LIST, new SgExpression(ALLOCATABLE_OP), params, (SgSymbol*)NULL);
        newDecl->setExpression(2, newParams);
    }
    //объявление с DIMENSION или с ALLOCATABLBE
    else
    {
        newDecl->setVariant(VAR_DECL);
        newDecl->setExpression(1, *(new SgTypeExp(*origSymbol->type()->baseType())));
        newDecl->setExpression(2, *(new SgExpression(ALLOCATABLE_OP)));
    }


}

static SgSymbol* alterArrayDeclaration(SgStatement* declarationStatement, SgSymbol *arraySymbol, vector<int> &dimensions, bool breed) {
    SgSymbol *newArraySymbol = NULL;
    for(SgExpression *exprList = declarationStatement->expr(0); exprList != NULL; exprList = exprList->rhs())
    {
        SgExpression *array = exprList->lhs();
        if(!strcmp(array->symbol()->identifier(), arraySymbol->identifier()))
        {//нашли объявление исходного массива

            SgExpression *newArray = array->copyPtr();
            newArraySymbol = createNewArrayNameSymbol(newArray, breed);
            if(breed)
                extendArrayDeclaration(dimensions, newArray, newArraySymbol);
            else {
                newArray->setSymbol(newArraySymbol);
                reduceArray(dimensions, newArray);
            }

            SgExpression newExprList(EXPR_LIST, newArray, (SgExpression*)NULL, (SgSymbol*)NULL);
            declarationStatement->setExpression(0,newExprList);
            break;

        }
    }
    setAllocatable(declarationStatement, arraySymbol);
    //На самом деле, newArraySymbol не может быть NULL
    if(newArraySymbol == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return newArraySymbol;

}

static void extendArrayRefs(const vector<SgSymbol*> &indexes, SgStatement *st, SgSymbol *arraySymbol, SgSymbol *newArraySymbol, const vector<SgExpression*> &lowBounds) 
{
    queue<SgExpression*> toCheck;

    for (int i = 0; i < 3; ++i)
    {
        if (st->expr(i))
        {
            if (st->expr(i)->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), st->expr(i)->symbol()->identifier()))
                extendArrayRef(indexes, st->expr(i), newArraySymbol, lowBounds);
            else if (st->expr(i)->variant() == VAR_REF && !strcmp(arraySymbol->identifier(), st->expr(i)->symbol()->identifier()))
            {
                SgExpression *extended = extendArrayRef(indexes, st->expr(i), newArraySymbol, lowBounds);
                st->setExpression(i, *extended);
            }
            else
                toCheck.push(st->expr(i));
        }
    }

    while(!toCheck.empty())
    {
        SgExpression *parent = toCheck.front();
        toCheck.pop();

        SgExpression *lhs = parent->lhs(), *rhs = parent->rhs();
        if(lhs)
        {
            if(lhs->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), lhs->symbol()->identifier()))
                extendArrayRef(indexes, lhs, newArraySymbol, lowBounds);
            else if(lhs->variant() == VAR_REF && !strcmp(arraySymbol->identifier(), lhs->symbol()->identifier()))
            {
                SgExpression *extended = extendArrayRef(indexes, lhs, newArraySymbol, lowBounds);
                parent->setLhs(extended);
            }
            else
                toCheck.push(lhs);
        }

        if(rhs)
        {
            if (rhs->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), rhs->symbol()->identifier()))
                extendArrayRef(indexes, rhs, newArraySymbol, lowBounds);
            else if (rhs->variant() == VAR_REF && !strcmp(arraySymbol->identifier(), rhs->symbol()->identifier()))
            {
                SgExpression *extended = extendArrayRef(indexes, rhs, newArraySymbol, lowBounds);
                parent->setRhs(extended);
            }
            else
                toCheck.push(rhs);
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
    SgStatement *newDeclaration = originalDeclaration->copyPtr();

    newDeclaration->setExpression(0, newExprList);
    firstStmtOfFile->insertStmtAfter(*newDeclaration, *firstStmtOfFile->controlParent());

    return newDeclaration;
}

static SgExpression* constructBoundCall(bool upBound, SgSymbol *array, int dim) {

    const char* boundName = NULL;
    upBound ? boundName = "ubound": boundName = "lbound";

    SgSymbol boundS = SgSymbol(FUNCTION_NAME, boundName);

    SgExpression *dimParam = new SgExpression(EXPR_LIST, new SgValueExp(dim), NULL, NULL);
    SgExpression params(EXPR_LIST, new SgExpression(ARRAY_REF, NULL, NULL, array), dimParam, NULL);

    return new SgFunctionCallExp(boundS, params);
}

static SgExpression* constructReducedAllocation(LoopGraph *forLoop, SgExpression *origArray, SgSymbol *arraySymbol, vector<int> *indexes) {
    SgExpression *arrayRef = origArray->copyPtr();
    arrayRef->setSymbol(arraySymbol);
    reduceArray(*indexes, arrayRef);
    return new SgExpression(EXPR_LIST, arrayRef, (SgExpression*)NULL, (SgSymbol*)NULL);
}

static SgExpression* constructArrayAllocationExp(LoopGraph *forLoop, SgExpression *origArray, SgSymbol *arraySymbol, int depthOfBreed, vector<SgExpression*> &lowBounds)
{

    SgExpression *arrayRef = origArray->copyPtr();
    arrayRef->setSymbol(arraySymbol);
    vector<SgExpression*> dimensions(depthOfBreed);
    LoopGraph *curLoop = forLoop;
    for (int i = 0; i < depthOfBreed; ++i)
    {
        SgForStmt *loopStmt = (SgForStmt*)(curLoop->loop->GetOriginal());
        dimensions[depthOfBreed - 1 - i] = new SgExpression(DDOT, loopStmt->start()->copyPtr(), loopStmt->end()->copyPtr(), NULL);
        if(i+1 != depthOfBreed)
            curLoop = curLoop->children[0];
    }

    SgExpression *newTail = NULL;
    for (int i = dimensions.size() - 1; i >= 0; --i)
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

        if (oldTail->lhs()->variant() == DDOT)
            lowBounds.push_back(oldTail->lhs()->lhs());
        else
            lowBounds.push_back(new SgValueExp(1));

        oldTail = oldTail->rhs();
        if (oldTail)
            attachTo = oldTail;
    }

    if (arrayRef->variant() == VAR_REF)// create array from scalar
    {
        arrayRef = new SgArrayRefExp(*arrayRef->symbol());
        arrayRef->setLhs(newTail);
    }
    else
        attachTo->setRhs(newTail);

    return new SgExpression(EXPR_LIST, arrayRef, (SgExpression*)NULL, (SgSymbol*)NULL);
}

static vector<SgExpression*> insertAllocDealloc(LoopGraph *forLoop, SgStatement *originalDeclaration, SgSymbol *origArraySymbol, SgSymbol *arraySymbol, int depthOfBreed, vector<int> *indexes = NULL)
{
    SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());
    vector<SgExpression*> lowBounds;

    SgExpression *origArray = NULL;
    for (origArray = originalDeclaration->expr(0); strcmp(origArray->lhs()->symbol()->identifier(), origArraySymbol->identifier()); origArray = origArray->rhs())
    { }// Yes-yes-yes, YEEEEEEESSSSS!!!
    origArray = origArray->lhs();

    SgExpression *arrayAllocation = indexes == NULL
            ? constructArrayAllocationExp(forLoop, origArray, arraySymbol, depthOfBreed, lowBounds)
            : constructReducedAllocation(forLoop, origArray, arraySymbol, indexes);
    SgExpression *arrayDeallocation = new SgExpression(EXPR_LIST, new SgExpression(ARRAY_REF, (SgExpression*)NULL, (SgExpression*)NULL, arraySymbol), (SgExpression*)NULL, (SgSymbol*)NULL);

    SgStatement *allocate = new SgStatement(ALLOCATE_STMT, (SgLabel*)NULL, (SgSymbol*)NULL, arrayAllocation, (SgExpression*)NULL, (SgExpression*)NULL);
    SgStatement *deallocate = new SgStatement(DEALLOCATE_STMT, (SgLabel*)NULL, (SgSymbol*)NULL, arrayDeallocation, (SgExpression*)NULL, (SgExpression*)NULL);

    loopStmt->insertStmtBefore(*allocate, *loopStmt->controlParent());
    loopStmt->lastNodeOfStmt()->insertStmtAfter(*deallocate, *loopStmt->controlParent());

    return lowBounds;
}

static bool containsFunctionCall(SgExpression *exp) 
{
    bool retVal = false;

    if (exp)
    {
        if (exp->variant() == FUNC_CALL)
            retVal = true;

        if (exp->lhs())
            retVal = retVal || containsFunctionCall(exp->lhs());
        if (exp->rhs())
            retVal = retVal || containsFunctionCall(exp->rhs());
    }
    return retVal;
}

static SgSymbol* createVarDeclaration(SgForStmt* loopStmt, const char *add)
{
    SgSymbol *doName = loopStmt->doName();
    SgSymbol *newName = new SgSymbol(VARIABLE_NAME, constructNewBoundName(doName->identifier(), loopStmt->lineNumber(), add).c_str(), doName->type(), NULL);

    SgStatement *decl = declaratedInStmt(doName);

    SgStatement* newDecl = decl->copyPtr();
    newDecl->setExpression(0, new SgExpression(EXPR_LIST, new SgVarRefExp(newName), NULL, NULL));
    decl->insertStmtAfter(*newDecl, *decl->controlParent());

    return newName;
}

static SgStatement* createBoundVariableAssign(SgSymbol *varName, SgExpression *value)
{
    SgAssignStmt *assign = new SgAssignStmt(*new SgVarRefExp(varName), *value);
    return assign;
}

static void replaceFunctionBounds(SgExpression *ex, SgForStmt* loopStmt, SgForStmt* topLoopStmt, const string &kind)
{
    if (containsFunctionCall(ex))
    {
        SgSymbol* newStart = createVarDeclaration(loopStmt, kind.c_str());
        SgStatement* assignment = createBoundVariableAssign(newStart, ex);

        topLoopStmt->insertStmtBefore(*assignment, *topLoopStmt->controlParent());
        if (kind == "_start")
            loopStmt->setStart(*assignment->expr(0));
        if (kind == "_end")
            loopStmt->setEnd(*assignment->expr(0));
        if (kind == "_step")
            loopStmt->setStep(*assignment->expr(0));
    }
}

static void replaceFunctionBounds(LoopGraph *forLoop, int depthOfBreed)
{
    LoopGraph *curLoop = forLoop;
    SgForStmt *topLoopStmt = (SgForStmt*) (curLoop->loop->GetOriginal());
    for (int i = 0; i < depthOfBreed; ++i)
    {
        SgForStmt *loopStmt = (SgForStmt*) (curLoop->loop->GetOriginal());
        
        replaceFunctionBounds(loopStmt->start(), loopStmt, topLoopStmt, "_start");
        replaceFunctionBounds(loopStmt->end(), loopStmt, topLoopStmt, "_end");
        replaceFunctionBounds(loopStmt->step(), loopStmt, topLoopStmt, "_step");
        
        if(i+1 != depthOfBreed)
            curLoop = curLoop->children[0];
    }
}

static SgSymbol* createReducedToVariableArray(SgStatement *copiedDeclaration, int lineNumber, SgSymbol *arraySymbol) {
    SgType *type = copiedDeclaration->expr(1)->type();
    SgSymbol *newName = new SgSymbol(VARIABLE_NAME, constructNewBoundName(arraySymbol->identifier(), lineNumber, "_reduced").c_str(), type, NULL);

    copiedDeclaration->setExpression(0, new SgExpression(EXPR_LIST, new SgVarRefExp(newName), NULL, NULL));
    return newName;
}

static void reduceArrayRefs(SgStatement *st, SgSymbol *arraySymbol, SgSymbol *newSymbol, bool reduceToVariable, vector<int> &indexes) {

    queue<SgExpression*> toCheck;
    SgExpression *newVariableExpression = NULL;

    for (int i = 0; i < 3; ++i)
    {
        if (st->expr(i))
        {
            SgExpression *exp = st->expr(i);
            if (exp->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), exp->symbol()->identifier())) {
                if(reduceToVariable)
                    st->setExpression(i, new SgVarRefExp(newSymbol));
                else
                    reduceArray(indexes, exp);
            } else
                toCheck.push(exp);
        }
    }

    while(!toCheck.empty())
    {
        SgExpression *parent = toCheck.front();
        toCheck.pop();

        SgExpression *lhs = parent->lhs(), *rhs = parent->rhs();
        if(lhs)
        {
            if(lhs->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), lhs->symbol()->identifier())) {
                if(reduceToVariable)
                    parent->setLhs(new SgVarRefExp(newSymbol));
                else
                    reduceArray(indexes, lhs);
            } else
                toCheck.push(lhs);
        }

        if(rhs)
        {
            if (rhs->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), rhs->symbol()->identifier())) {
                if(reduceToVariable)
                    parent->setRhs(new SgVarRefExp(newSymbol));
                else
                    reduceArray(indexes, rhs);
            } else
                toCheck.push(rhs);
        }
    }
}

static void debreedArray(LoopGraph *forLoop, SgSymbol *arraySymbol, vector<int> &indexes) {

    int maxDepth = forLoop->perfectLoop;
    LoopGraph *curLoop = forLoop;
    bool reduceToVariable = true;
    for(int i = 0; i < maxDepth; ++i)
    {
        if(indexes[i] != 1)
            reduceToVariable = false;
        if(curLoop->children.size() == 1)
            curLoop = curLoop->children[0];
        else if (i != maxDepth - 1)
        {
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            return;
        }
    }


    replaceFunctionBounds(forLoop, maxDepth);
    SgStatement *originalDeclaration = declaratedInStmt(arraySymbol);
    SgStatement *copiedDeclaration = createNewDeclarationStatemnet(originalDeclaration, arraySymbol);

    SgSymbol *newSymbol = reduceToVariable
            ? createReducedToVariableArray(copiedDeclaration, forLoop->lineNum, arraySymbol)
            : alterArrayDeclaration(copiedDeclaration, arraySymbol, indexes, false);

    if(newSymbol) {
        SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());
        if(!reduceToVariable) {
            auto lowBounds = insertAllocDealloc(forLoop, originalDeclaration, arraySymbol, newSymbol, indexes.size(), &indexes);
        }
        for (SgStatement *st = loopStmt->lexNext(); st != loopStmt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
            if (st->variant() != ALLOCATE_STMT && st->variant() != DEALLOCATE_STMT)
                reduceArrayRefs(st, arraySymbol, newSymbol, reduceToVariable, indexes);
    }

}

static void breedArray(LoopGraph *forLoop, SgSymbol *arraySymbol, int depthOfBreed)
{
    //Don't delete this, it's a work in progress
/*
    if(true) {
        vector<int> indexes;
        indexes.push_back(1);
        indexes.push_back(1);
        debreedArray(forLoop, arraySymbol, indexes);
        return;
    }*/

    if(depthOfBreed < 0 || depthOfBreed > forLoop->perfectLoop)
        depthOfBreed = forLoop->perfectLoop;

    vector<int> dimensions(depthOfBreed);
    vector<SgSymbol*> indexes(depthOfBreed);

    LoopGraph *curLoop = forLoop;
    for(int i = 0; i < depthOfBreed; ++i)
    {
        SgForStmt *loopStmt = (SgForStmt*)(curLoop->loop->GetOriginal());
        dimensions[depthOfBreed - 1 - i] = curLoop->calculatedCountOfIters;
        indexes[depthOfBreed - 1 - i] = loopStmt->doName();

        if(curLoop->children.size() == 1)
            curLoop = curLoop->children[0];
        else if (i != depthOfBreed - 1)
        {
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            return;
        }
    }

    replaceFunctionBounds(forLoop, depthOfBreed);

    SgStatement *originalDeclaration = declaratedInStmt(arraySymbol);
    SgStatement *copiedOriginalArrayDeclaration = createNewDeclarationStatemnet(originalDeclaration, arraySymbol);
    SgSymbol *newArraySymbol = alterArrayDeclaration(copiedOriginalArrayDeclaration, arraySymbol, dimensions, true);

    if (newArraySymbol)
    {
        SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());
        auto lowBounds = insertAllocDealloc(forLoop, originalDeclaration, arraySymbol, newArraySymbol, indexes.size());
        for (SgStatement *st = loopStmt->lexNext(); st != loopStmt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
            if (st->variant() != ALLOCATE_STMT && st->variant() != DEALLOCATE_STMT)
                extendArrayRefs(indexes, st, arraySymbol, newArraySymbol, lowBounds);
    }
}

//for testing
static SgSymbol *findSymbol(LoopGraph*  forLoop, const char* arrayName)
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

                if((curExp->variant() == ARRAY_REF || curExp->variant() == VAR_REF) && !strcmp(arrayName, curExp->symbol()->identifier()))
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

//Вычислять размер массива с учётом шага цикла - //TODO
int breedArrays(SgFile *file, std::vector<LoopGraph*> &loopGraphs, const set<SgSymbol*> &doForThisPrivates, vector<Messages> &messages)
{
    map<int, LoopGraph*> mapLoopGraph;
    createMapLoopGraph(loopGraphs, mapLoopGraph);

    for (auto &loopPair : mapLoopGraph)
    {
        LoopGraph *loop = loopPair.second;
        auto attrsTr = getAttributes<SgStatement*, SgStatement*>(loop->loop->GetOriginal(), set<int>{ SPF_TRANSFORM_DIR });
        auto attrsPriv = getAttributes<SgStatement*, SgStatement*>(loop->loop->GetOriginal(), set<int>{ SPF_ANALYSIS_DIR });
        
        set<Symbol*> privates;
        set<SgSymbol*> arrayPrivates;
        for (auto &spf : attrsPriv)
            fillPrivatesFromComment(new Statement(spf), privates);
        for (auto &s : privates)
            if (s->type()->variant() == T_ARRAY)
                arrayPrivates.insert(s->GetOriginal());

        arrayPrivates.insert(doForThisPrivates.begin(), doForThisPrivates.end());

        if (arrayPrivates.size() == 0)
        {
            string str;
            __spf_printToBuf(str, "Can not do PRIVATE EXPANSION for this loop - privates not found");

            //messages.push_back(Messages(NOTE, loop->lineNum, str, 2008));
            __spf_print(1, "%s on line %d\n", str.c_str(), loop->lineNum);
        }
        else
        {
            for (auto attr : attrsTr)
            {
                SgExpression *list = attr->expr(0);
                vector<SgExpression*> newL;

                while (list)
                {
                    if (list->lhs()->variant() == SPF_PRIVATES_EXPANSION_OP)
                    {
                        if (list->lhs()->lhs() == NULL)
                        {
                            for (auto &privArr : arrayPrivates)
                                breedArray(loop, privArr, -1);
                        }
                        else
                        {
                            SgExprListExp *listExp = isSgExprListExp(list->lhs()->lhs());
                            checkNull(listExp, convertFileName(__FILE__).c_str(), __LINE__);
                            const int deep = listExp->length();

                            for (auto &privArr : arrayPrivates)
                                breedArray(loop, privArr, deep);
                        }
                    }
                    else
                        newL.push_back(list);
                    list = list->rhs();
                }
                SgExpression *ex = NULL;
                SgExpression *p = NULL;
                for (int z = 0; z < newL.size(); ++z)
                {
                    if (z == 0)
                        p = ex = newL[z];
                    else
                    {
                        ex->setRhs(newL[z]);
                        ex = ex->rhs();
                    }
                }
                attr->setExpression(0, p);
            }
        }
    }

    return 0;
}
