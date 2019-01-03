#include "private_arrays_breeder.h"
#include "../GraphLoop/graph_loops.h"
#include "../Utils/SgUtils.h"
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
    SgType *type = new SgType(T_ARRAY);
    SgSymbol* newName = new SgSymbol(VARIABLE_NAME, constructNewArrayName(declaration->symbol()->identifier()), type, NULL);
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

static SgExpression* extendArrayRef(const vector<SgSymbol*> &indexes, SgExpression *expressionToExtend, SgSymbol* newSymbol)
{
    SgExpression *newTail = NULL;
    for (int i = indexes.size() - 1; i >= 0; --i)
    {
        SgExpression *breededIndex = new SgVarRefExp(indexes[i]);
        newTail = new SgExpression(EXPR_LIST, breededIndex, newTail, (SgSymbol*) NULL);
    }

    SgExpression *oldTail = expressionToExtend->lhs();
    if(oldTail == NULL) // create array from scalar
    {
        expressionToExtend = new SgArrayRefExp(*newSymbol); //TODO delete old SgExpression maybe?
        expressionToExtend->setLhs(newTail);
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

static SgSymbol* alterArrayDeclaration(SgStatement* declarationStatement, SgSymbol *arraySymbol, vector<int> &dimensions) {
    SgSymbol *newArraySymbol = NULL;
    for(SgExpression *exprList = declarationStatement->expr(0); exprList != NULL; exprList = exprList->rhs())
    {
        SgExpression *array = exprList->lhs();
        if(!strcmp(array->symbol()->identifier(), arraySymbol->identifier()))
        {//нашли объявление исходного массива
            SgExpression *newArray = array->copyPtr();
            newArraySymbol = createNewArrayNameSymbol(newArray);
            extendArrayDeclaration(dimensions, newArray, newArraySymbol);

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

static void extendArrayRefs(const vector<SgSymbol*> &indexes, SgStatement* st, SgSymbol *arraySymbol, SgSymbol *newArraySymbol) {
    queue<SgExpression*> toCheck = queue<SgExpression*>();

    for (int i = 0; i < 3; ++i)
    {
        if (st->expr(i))
        {
            if (st->expr(i)->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), st->expr(i)->symbol()->identifier()))
                extendArrayRef(indexes, st->expr(i), newArraySymbol);
            else if (st->expr(i)->variant() == VAR_REF && !strcmp(arraySymbol->identifier(), st->expr(i)->symbol()->identifier()))
            {
                SgExpression *extended = extendArrayRef(indexes, st->expr(i), newArraySymbol);
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
                extendArrayRef(indexes, lhs, newArraySymbol);
            else if(lhs->variant() == VAR_REF && !strcmp(arraySymbol->identifier(), lhs->symbol()->identifier()))
            {
                SgExpression *extended = extendArrayRef(indexes, lhs, newArraySymbol);
                parent->setLhs(extended);
            }
            else
                toCheck.push(lhs);

        }

        if(rhs)
        {
            if (rhs->variant() == ARRAY_REF && !strcmp(arraySymbol->identifier(), rhs->symbol()->identifier()))
                extendArrayRef(indexes, rhs, newArraySymbol);
            else if (rhs->variant() == VAR_REF && !strcmp(arraySymbol->identifier(), rhs->symbol()->identifier()))
            {
                SgExpression *extended = extendArrayRef(indexes, rhs, newArraySymbol);
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
    firstStmtOfFile->insertStmtAfter(*newDeclaration);

    return newDeclaration;
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
    if(arrayRef->variant() == VAR_REF)// create array from scalar
    {
        arrayRef = new SgArrayRefExp(*arrayRef->symbol());
        arrayRef->setLhs(newTail);
    }
    else
        attachTo->setRhs(newTail);

    return new SgExpression(EXPR_LIST, arrayRef, (SgExpression*)NULL, (SgSymbol*)NULL);
}

static void insertAllocDealloc(LoopGraph *forLoop, SgStatement *originalDeclaration, SgSymbol *origArraySymbol, SgSymbol *arraySymbol, int depthOfBreed) 
{
    SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());

    SgExpression *origArray = NULL;
    for (origArray = originalDeclaration->expr(0); strcmp(origArray->lhs()->symbol()->identifier(), origArraySymbol->identifier()); origArray = origArray->rhs())
    {}// Yes-yes-yes, YEEEEEEESSSSS!!!
    origArray = origArray->lhs();

    SgExpression *arrayAllocation = constructArrayAllocationExp(forLoop, origArray, arraySymbol, depthOfBreed);
    SgExpression *arrayDeallocation = new SgExpression(EXPR_LIST, new SgExpression(ARRAY_REF, (SgExpression*)NULL, (SgExpression*)NULL, arraySymbol), (SgExpression*)NULL, (SgSymbol*)NULL);

    SgStatement *allocate = new SgStatement(ALLOCATE_STMT, (SgLabel*)NULL, (SgSymbol*)NULL, arrayAllocation, (SgExpression*)NULL, (SgExpression*)NULL);
    SgStatement *deallocate = new SgStatement(DEALLOCATE_STMT, (SgLabel*)NULL, (SgSymbol*)NULL, arrayDeallocation, (SgExpression*)NULL, (SgExpression*)NULL);

    loopStmt->insertStmtBefore(*allocate, *loopStmt->controlParent());
    loopStmt->lastNodeOfStmt()->insertStmtAfter(*deallocate, *loopStmt->controlParent());
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
        dimensions[i] = curLoop->calculatedCountOfIters;
        indexes[i] = loopStmt->doName();

        if(curLoop->children.size() == 1)
            curLoop = curLoop->children[0];
        else if (i != depthOfBreed - 1)
        {
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            return;
        }
    }
    std::reverse(indexes.begin(), indexes.end());

    SgStatement *originalDeclaration = declaratedInStmt(arraySymbol);
    SgStatement *copiedOriginalArrayDeclaration = createNewDeclarationStatemnet(originalDeclaration, arraySymbol);
    SgSymbol *newArraySymbol = alterArrayDeclaration(copiedOriginalArrayDeclaration, arraySymbol, dimensions);

    SgForStmt *loopStmt = (SgForStmt*)(forLoop->loop->GetOriginal());
    if (newArraySymbol)
    {
        insertAllocDealloc(forLoop, originalDeclaration, arraySymbol, newArraySymbol, indexes.size());
        for (SgStatement *st = loopStmt->lexNext(); st != loopStmt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
            if (st->variant() != ALLOCATE_STMT && st->variant() != DEALLOCATE_STMT)
                extendArrayRefs(indexes, st, arraySymbol, newArraySymbol);
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

        set<SgSymbol*> privates;
        set<SgSymbol*> arrayPrivates;
        for (auto &spf : attrsPriv)
            fillPrivatesFromComment(new Statement(spf), privates);
        for (auto &s : privates)
            if (s->type()->variant() == T_ARRAY)
                arrayPrivates.insert(s);

        arrayPrivates.insert(doForThisPrivates.begin(), doForThisPrivates.end());

        if (arrayPrivates.size() == 0)
        {
            string str;
            __spf_printToBuf(str, "Can not do PRIVATE EXPANSION for this loop - privates not found");

            messages.push_back(Messages(NOTE, loop->lineNum, str, 2008));
            __spf_print(1, "%s on line ", str.c_str(), loop->lineNum);
            return -1;
        }
        else
        {
            for (auto attr : attrsTr)
            {
                SgExpression *list = attr->expr(0);
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
            }
            return 0;
        }
    }   
}
