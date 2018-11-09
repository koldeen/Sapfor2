#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>

#include "dvm.h"
#include "array_assign_to_loop.h"
#include "../Utils/SgUtils.h"
#include "../ExpressionTransform/expr_transform.h"

using std::vector;
using std::set;
using std::pair;
using std::tuple;
using std::make_pair;
using std::string;
using std::to_string;
using std::get;

static void checkAlloc(SgExpression *toCheck, SgExpression *&alloc, const string &toFind)
{
    if (toCheck->lhs()->symbol()->identifier() == toFind)
        alloc = toCheck->lhs()->lhs();
}

static bool fillBounds(SgSymbol *symb, vector<tuple<SgExpression*, SgExpression*, SgExpression*>> &bounds)
{
    SgStatement *decl = declaratedInStmt(symb);

    int consistInAllocates = 0;
    SgExpression *alloc = NULL;

    for (auto &data : getAttributes<SgStatement*, SgStatement*>(decl, set<int>{ ALLOCATE_STMT }))
    {
        SgExpression *list = data->expr(0);
        if (data->variant() != ALLOCATE_STMT)
            continue;

        while (list)
        {
            SgArrayRefExp *arrayRef = isSgArrayRefExp(list->lhs());
            if (arrayRef != NULL)
            {
                if (string(OriginalSymbol(arrayRef->symbol())->identifier()) == string(symb->identifier()))
                {
                    consistInAllocates++;
                    alloc = list->lhs()->lhs();
                    break;
                }
            }
            list = list->rhs();
        }
    }

    if (consistInAllocates > 1)
        return false;
        
    if (IS_ALLOCATABLE(symb) && consistInAllocates == 0)
        return false;

    if (consistInAllocates == 0)
    {
        const string toFind = string(symb->identifier());

        for (SgExpression *ex = decl->expr(0); ex && (alloc == NULL); ex = ex->rhs())
        {
            if (ex->lhs()->variant() == ASSGN_OP)
            {
                if (ex->lhs()->lhs() && ex->lhs()->lhs()->symbol())
                    checkAlloc(ex->lhs(), alloc, toFind);
            }
            else if (ex->lhs() && ex->lhs()->symbol())
                checkAlloc(ex, alloc, toFind);
        }
    }

    if (alloc == NULL)
        return false;
    
    for ( ; alloc; alloc = alloc->rhs())
    {
        if (alloc->lhs()->variant() == DDOT)
            bounds.push_back(std::make_tuple(alloc->lhs()->lhs()->copyPtr(), alloc->lhs()->rhs()->copyPtr(), (SgExpression*)NULL));
        else
            bounds.push_back(std::make_tuple(new SgValueExp(1), alloc->lhs()->copyPtr(), (SgExpression*)NULL));
    }

    for (auto &bound : bounds)
        get<0>(bound) = CalculateInteger(get<0>(bound));
    return true;
}

static bool fillSectionInfo(SgExpression *subs, tuple<SgExpression*, SgExpression*, SgExpression*> &section)
{
    if (subs->lhs())
    {
        if (subs->lhs()->variant() == DDOT)
        {
            if (subs->lhs()->lhs() && subs->lhs()->lhs()->variant() == DDOT)
            {
                if (subs->lhs()->lhs()->lhs() != NULL) // low section
                    get<0>(section) = CalculateInteger(subs->lhs()->lhs()->lhs()->copyPtr());

                if (subs->lhs()->lhs()->rhs() != NULL) // high section
                    get<1>(section) = CalculateInteger(subs->lhs()->lhs()->rhs()->copyPtr());

                if (subs->lhs()->rhs() != NULL) // step of section
                    get<2>(section) = CalculateInteger(subs->lhs()->rhs()->copyPtr());
            }
            else
            {
                if (subs->lhs()->lhs() != NULL) // low section
                    get<0>(section) = CalculateInteger(subs->lhs()->lhs()->copyPtr());

                if (subs->lhs()->rhs() != NULL) // high section
                    get<1>(section) = CalculateInteger(subs->lhs()->rhs()->copyPtr());
            }
        }
        else
        {   // low and high sections
            get<0>(section) = CalculateInteger(subs->lhs()->copyPtr());
            get<1>(section) = CalculateInteger(subs->lhs()->copyPtr());
        }
        return true;
    }
    else
        return false;
}

static bool hasSections(SgArrayRefExp *array)
{
    const int subs = array->numberOfSubscripts();
    if (subs == 0)
        return true;
    else
    {
        for (int i = 0; i < subs; ++i)
            if (array->subscript(i)->variant() == DDOT)
                return true;
    }
    return false;
}

static void insertMainPart(SgExpression *subsL, SgFile *file, const int deep, SgExpression *shift, SgExpression *step, SgStatement *scope)
{
    auto varRef = new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep), SgTypeInt(), scope));
    bool isNull = false;

    if (shift->isInteger())
        if (shift->valueInteger() == 0)
            isNull = true;

    if (step)
    {
        if (step->variant() == INT_VAL)
        {
            if (step->valueInteger() != 1)
            {
                if (isNull)
                    subsL->setLhs(*varRef * *step);
                else
                    subsL->setLhs(*varRef * *step + *shift);
            }
            else
            {
                if (isNull)
                    subsL->setLhs(*varRef);
                else
                    subsL->setLhs(*varRef + *shift);
            }
        }
        else
        {
            if (isNull)
                subsL->setLhs(*varRef * *step);
            else
                subsL->setLhs(*varRef * *step + *shift);
        }
    }
    else
    {
        if (isNull)
            subsL->setLhs(*varRef);
        else
            subsL->setLhs(*varRef + *shift);
    }
}

static SgStatement* convertFromAssignToLoop(SgStatement *assign, SgFile *file, vector<Messages> &messagesForFile)
{
    if (assign->variant() != ASSIGN_STAT)
        return NULL;

    if (assign->expr(0) == NULL || assign->expr(1) == NULL)
        return NULL;

    if (assign->expr(0)->variant() != ARRAY_REF || assign->expr(1)->variant() != ARRAY_REF)
        return NULL;

    SgArrayRefExp *leftPart = (SgArrayRefExp*)assign->expr(0);
    SgArrayRefExp *rightPart = (SgArrayRefExp*)assign->expr(1);

    if (!hasSections(leftPart) || !hasSections(rightPart))
        return NULL;

    const int leftSubs = leftPart->numberOfSubscripts();
    const int rightSubs = rightPart->numberOfSubscripts();

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> leftBound;
    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> rightBound;

    bool resL = fillBounds(OriginalSymbol(leftPart->symbol()), leftBound);
    bool resR = fillBounds(OriginalSymbol(rightPart->symbol()), rightBound);

    if (!resL || !resR)
        return NULL;

    SgForStmt *retVal = NULL;
    SgStatement *copy = assign->copyPtr();

    SgArrayRefExp *leftArrayRef = (SgArrayRefExp*)copy->expr(0);
    SgArrayRefExp *rightArrayRef = (SgArrayRefExp*)copy->expr(1);

    SgExpression *subsL = leftArrayRef->lhs();
    SgExpression *subsR = rightArrayRef->lhs();

    int lIdx = 0;
    int rIdx = 0;
    bool bodyInserted = false;

    SgStatement *scope = assign;
    //XXX
    while (true)
    {
        if (scope->variant() == PROG_HEDR || scope->variant() == FUNC_HEDR || scope->variant() == PROC_HEDR)
            break;
        scope = scope->controlParent();
    }

    vector<bool> fixedLeft(leftBound.size()), fixedRight(rightBound.size());
    for (int i = 0; i < leftBound.size(); ++i)
        fixedLeft[i] = false;
    for (int i = 0; i < fixedRight.size(); ++i)
        fixedRight[i] = false;

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> leftSections, rightSections;

    SgExpression *ex = subsL;
    for (int i = 0; i < leftSubs; ++i)
    {
        tuple<SgExpression*, SgExpression*, SgExpression*> bounds = leftBound[lIdx];
        if (!fillSectionInfo(ex, bounds))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (get<0>(bounds) && get<1>(bounds))
            if (string(get<0>(bounds)->unparse()) == string(get<1>(bounds)->unparse())) // fixed dimension value
                fixedLeft[i] = true;

        if (!fixedLeft[i])
            leftSections.push_back(bounds);
        ex = ex->rhs();
    }

    //fill default
    if (leftSubs == 0)
        leftSections = leftBound;
    
    ex = subsR;
    for (int i = 0; i < rightSubs; ++i)
    {
        tuple<SgExpression*, SgExpression*, SgExpression*> bounds = rightBound[rIdx];
        if (!fillSectionInfo(ex, bounds))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                
        if (get<0>(bounds) && get<1>(bounds))
            if (string(get<0>(bounds)->unparse()) == string(get<1>(bounds)->unparse())) // fixed dimension value
                fixedRight[i] = true;

        if (!fixedRight[i])
            rightSections.push_back(bounds);
        ex = ex->rhs();
    }

    //fill default
    if (rightSubs == 0)
        rightSections = rightBound;

    if (leftSections.size() != rightSections.size())
    {
        __spf_print(1, "WARN: can not convert array assign to loop on line %d\n", assign->lineNumber());

        string message;
        __spf_printToBuf(message, "can not convert array assign to loop");
        messagesForFile.push_back(Messages(WARR, assign->lineNumber(), message, 2001));
    }
    else
    {
        __spf_print(1, "was on line %d file %s\n", assign->lineNumber(), assign->fileName());
        __spf_print(1, "%s", string(assign->unparse()).c_str());
        
        vector<tuple<SgExpression*, SgExpression*, SgExpression*>> forBounds;
        // create DO bounds
        if (!leftSections.size())
            leftSections = leftBound;
        if (!rightSections.size())
            rightSections = rightBound;

        for (int i = 0; i < leftSections.size(); ++i)
        {
            SgExpression *maxBound = NULL;
            if (get<2>(leftSections[i]))
                maxBound = &((*(get<1>(leftSections[i])) - *get<0>(leftSections[i])) / *get<2>(leftSections[i]));
            else
                maxBound = &(*(get<1>(leftSections[i])) - *get<0>(leftSections[i]));
            //TODO: dont calculate in parallel loops
            maxBound = CalculateInteger(maxBound);

            forBounds.push_back(std::make_tuple(new SgValueExp(0), maxBound, (SgExpression*)NULL));
        }
                
        SgStatement *body = NULL;
        // construct DO bounds
        for (int i = 0; i < forBounds.size(); ++i)
        {
            if (body == NULL)
                body = copy;
            else
                body = retVal;

            if (get<2>(forBounds[i])) // has step
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope), get<0>(forBounds[i])->copy(), get<1>(forBounds[i])->copy(), get<2>(forBounds[i])->copy(), *body);
            else
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope), get<0>(forBounds[i])->copy(), get<1>(forBounds[i])->copy(), *body);
        }
                
        if (leftSubs == 0 && rightSubs == 0)
        {
            // A = B
            for (int i = 0; i < leftSections.size(); ++i)
            {
                SgExpression *shiftA = get<0>(leftBound[i]);
                shiftA = CalculateInteger(shiftA);
                leftArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftA);
            }

            for (int i = 0; i < rightSections.size(); ++i)
            {
                SgExpression *shiftB = get<0>(rightBound[i]);
                shiftB = CalculateInteger(shiftB);
                rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftB);
            }
        }
        else if (leftSubs == 0 && rightSubs != 0)
        {
            // A = B( : : : )                        
            for (int i = 0; i < leftSections.size(); ++i)
            {
                SgExpression *shiftA = get<0>(leftBound[i]);
                shiftA = CalculateInteger(shiftA);
                leftArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftA);
            }

            ex = subsR;
            for (int i = 0, freeIdx = 0; i < rightSubs; ++i, subsR = subsR->rhs())
            {
                if (!fixedRight[i])
                {
                    SgExpression *shiftB = get<0>(rightSections[freeIdx]);
                    if (shiftB == NULL)
                        shiftB = get<0>(rightBound[freeIdx]);
                    shiftB = CalculateInteger(shiftB);

                    SgExpression *stepB = get<2>(rightSections[freeIdx]);
                    if (stepB != NULL)
                        stepB = CalculateInteger(stepB);

                    insertMainPart(subsR, file, freeIdx, shiftB, stepB, scope);

                    ++freeIdx;
                }
            }
        }
        else if (leftSubs != 0 && rightSubs == 0)
        {
            // A( : : : ) = B
            ex = subsL;
            for (int i = 0, freeIdx = 0; i < leftSubs; ++i, subsL = subsL->rhs())
            {
                if (!fixedLeft[i])
                {
                    SgExpression *shiftA = get<0>(leftSections[freeIdx]);
                    if (shiftA == NULL)
                        shiftA = get<0>(leftBound[freeIdx]);
                    shiftA = CalculateInteger(shiftA);

                    SgExpression *stepA = get<2>(leftSections[freeIdx]);
                    if (stepA != NULL)
                        stepA = CalculateInteger(stepA);

                    insertMainPart(subsL, file, freeIdx, shiftA, stepA, scope);

                    ++freeIdx;
                }
            }

            for (int i = 0; i < rightSections.size(); ++i)
            {
                SgExpression *shiftB = get<0>(rightBound[i]);
                shiftB = CalculateInteger(shiftB);
                rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftB);
            }
        }
        else
        {
            //A( : : : ) = B( : : : )
            ex = subsL;
            for (int i = 0, freeIdx = 0; i < leftSubs; ++i, subsL = subsL->rhs())
            {
                if (!fixedLeft[i])
                {
                    SgExpression *shiftA = get<0>(leftSections[freeIdx]);
                    if (shiftA == NULL)
                        shiftA = get<0>(leftBound[freeIdx]);                    
                    shiftA = CalculateInteger(shiftA);

                    SgExpression *stepA = get<2>(leftSections[freeIdx]);
                    if (stepA != NULL)
                        stepA = CalculateInteger(stepA);

                    insertMainPart(subsL, file, freeIdx, shiftA, stepA, scope);

                    ++freeIdx;
                }
            }

            ex = subsR;
            for (int i = 0, freeIdx = 0; i < rightSubs; ++i, subsR = subsR->rhs())
            {
                if (!fixedRight[i])
                {
                    SgExpression *shiftB = get<0>(rightSections[freeIdx]);
                    if (shiftB == NULL)
                        shiftB = get<0>(rightBound[freeIdx]);
                    shiftB = CalculateInteger(shiftB);

                    SgExpression *stepB = get<2>(rightSections[freeIdx]);
                    if (stepB != NULL)
                        stepB = CalculateInteger(stepB);

                    insertMainPart(subsR, file, freeIdx, shiftB, stepB, scope);

                    ++freeIdx;
                }
            }
        }
                
        __spf_print(1, "%s", string(retVal->unparse()).c_str());
    }

    return retVal;
}

// functionality: convert A[(...)] = B[(...)] to loop 
//                move (create copy) init assigns in DECL before the first executable
void convertFromAssignToLoop(SgFile *file, vector<Messages> &messagesForFile)
{
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        vector<pair<SgStatement*, SgStatement*>> toMove;

        SgStatement *firstExec = NULL;
        SgStatement *controlParFristExec = NULL;
        for (SgStatement *st = file->functions(i); st != lastNode && !firstExec; st = st->lexNext())
            if (isSgExecutableStatement(st))
                firstExec = st;

        if (firstExec)
            controlParFristExec = firstExec->controlParent();

        for ( ; st != lastNode; st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;

            if (firstExec && isSgDeclarationStatement(st))
            {
                SgVarDeclStmt *declStat = (SgVarDeclStmt*)st;
                for (int k = 0; k < declStat->numberOfSymbols(); ++k)
                {
                    SgExpression *completeInit = declStat->completeInitialValue(k);
                    if (completeInit)
                    {
                        SgStatement *toAdd = new SgStatement(ASSIGN_STAT, NULL, NULL, completeInit->lhs()->copyPtr(), completeInit->rhs()->copyPtr(), NULL);
                        firstExec->insertStmtBefore(*toAdd, *controlParFristExec);

                        toMove.push_back(make_pair(st, toAdd));
                        toAdd->setlineNumber(getNextNegativeLineNumber());
                        toAdd->setLocalLineNumber(st->lineNumber());
                    }
                }
            }

            currProcessing.second = st;
            if (st->variant() == ASSIGN_STAT)
            {
                SgStatement *conv = convertFromAssignToLoop(st, file, messagesForFile);

                if (conv)
                {
                    st->insertStmtBefore(*conv, *st->controlParent());
                    toMove.push_back(make_pair(st, conv));

                    SgStatement *end = conv->lastNodeOfStmt();
                    for (SgStatement *st1 = conv; st1 != end; st1 = st1->lexNext())
                    {
                        st1->setlineNumber(getNextNegativeLineNumber());
                        st1->setLocalLineNumber(st->lineNumber());
                    }
                    end->setlineNumber(getNextNegativeLineNumber());
                    end->setLocalLineNumber(st->lineNumber());
                }
            }
        }

        for (auto &move : toMove)
            move.first->addAttribute(ASSIGN_STAT, move.second, sizeof(SgStatement*));
    }
}

static bool isUnderParallelLoop(SgStatement *st)
{
    bool isUnder = false;

    while (st)
    {
        const int var = st->variant();
        if (var == FUNC_HEDR || var == PROG_HEDR || var == PROC_HEDR)
            break;

        if (var == FOR_NODE)
        {
            auto prev = st->lexPrev();
            if (prev->variant() == DVM_PARALLEL_ON_DIR)
            {
                isUnder = true;
                break;
            }
        }
        st = st->controlParent();
    }
    return isUnder;
}

static void addToDeclSet(SgExpression *exp, set<SgSymbol*> &symbolSet)
{
    if (exp)
    {
        if (exp->symbol())
            symbolSet.insert(OriginalSymbol(exp->symbol()));

        if (exp->lhs())
            addToDeclSet(exp->lhs(), symbolSet);
        if (exp->rhs())
            addToDeclSet(exp->rhs(), symbolSet);
    }
}

void restoreConvertedLoopForParallelLoops(SgFile *file, bool reversed)
{
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        vector<pair<SgStatement*, SgStatement*>> toMove;
        set<SgSymbol*> newDeclarations;
        set<SgSymbol*> declaratedInFunction;

        SgStatement *lastDeclarated = NULL;
        for (st = file->functions(i); st != lastNode; st = st->lexNext())
        {
            if (isSgExecutableStatement(st))
                break;
            if (st->variant() == CONTAINS_STMT)
                break;

            if (st->variant() != DATA_DECL)
                for (int i = 0; i < 3; ++i)
                    addToDeclSet(st->expr(i), declaratedInFunction);

            if (st->fileName() == file->filename())
                lastDeclarated = st;
        }

        for (st = file->functions(i); st != lastNode; st = st->lexNext())
        {            
            currProcessing.second = st;
            for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ ASSIGN_STAT }))
            {
                if (reversed)
                {
                    if (data->lineNumber() > 0)
                    {
                        toMove.push_back(make_pair(st, data));
                        st->insertStmtAfter(*data, *st->controlParent());

                        data->addAttribute(ASSIGN_STAT, st, sizeof(SgStatement*));
                    }
                }
                else
                {
                    if (data->lineNumber() < 0 && isUnderParallelLoop(st))
                    {
                        toMove.push_back(make_pair(st, data));
                        st->insertStmtAfter(*data, *st->controlParent());

                        data->addAttribute(ASSIGN_STAT, st, sizeof(SgStatement*));

                        for (auto st_loc = data; st_loc != data->lastNodeOfStmt(); st_loc = st_loc->lexNext())                        
                            if (st_loc->variant() == FOR_NODE)
                                newDeclarations.insert(st_loc->symbol());
                    }
                }
            }
        }

        for (auto &move : toMove)
            move.first->extractStmt();

        //insert new declaration of symbols for converted loops
        for (auto &toDecl : newDeclarations)
        {
            auto found = declaratedInFunction.find(toDecl);
            if (found == declaratedInFunction.end())
            {
                auto toInsert = toDecl->makeVarDeclStmt();
                lastDeclarated->insertStmtAfter(*toInsert, *st->controlParent());
            }
        }
    }
}

void restoreAssignsFromLoop(SgFile *file)
{
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        vector<pair<SgStatement*, SgStatement*>> toMove;
        for (st = file->functions(i); st != lastNode; st = st->lexNext())
        {
            currProcessing.second = st;

            if (st->variant() == CONTAINS_STMT)
                break;

            for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ ASSIGN_STAT }))
                if (data->lineNumber() < 0)
                    toMove.push_back(make_pair(st, data));
        }

        for (auto &move : toMove)
            move.second->extractStmt();
    }
}