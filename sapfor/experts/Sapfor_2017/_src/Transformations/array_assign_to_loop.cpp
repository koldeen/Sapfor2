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
#include "../GraphCall/graph_calls_func.h"
#include "../VerificationCode/verifications.h"

using std::vector;
using std::set;
using std::map;
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

    bool symbFound = false;
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
            {
                symbFound |= (ex->lhs()->symbol()->identifier() == toFind);
                checkAlloc(ex, alloc, toFind);
            }
        }
    }

    if (symbFound && alloc == NULL)
    {
        for (SgExpression *ex = decl->expr(2); ex; ex = ex->rhs())
        {
            if (ex->lhs() && ex->lhs()->variant() == DIMENSION_OP)
            {
                alloc = ex->lhs()->lhs();
                break;
            }
        }
    }

    if (alloc == NULL)        
        return false;
    
    for ( ; alloc; alloc = alloc->rhs())
    {
        if (alloc->lhs()->variant() == DDOT)
        {
            if (alloc->lhs()->lhs() == NULL || alloc->lhs()->rhs() == NULL)
                return false;
            bounds.push_back(std::make_tuple(alloc->lhs()->lhs()->copyPtr(), alloc->lhs()->rhs()->copyPtr(), (SgExpression*)NULL));
            
        }
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

static bool isNonDistrArray(SgSymbol *symb)
{
    SgStatement *decl = declaratedInStmt(symb);

    SgType *type = symb->type();
    if (type && type->variant() == T_STRING)
        return false;

    DIST::Array *array = getArrayFromDeclarated(decl, OriginalSymbol(symb)->identifier());
    checkNull(array, convertFileName(__FILE__).c_str(), __LINE__);    
    return array->GetNonDistributeFlag();    
}

static vector<SgStatement*> convertFromAssignToLoop(SgStatement *assign, SgFile *file, vector<Messages> &messagesForFile)
{
    vector<SgStatement*> result;

    if (assign->variant() != ASSIGN_STAT)
        return result;

    if (assign->expr(0) == NULL || assign->expr(1) == NULL)
        return result;

    if (assign->expr(0)->variant() != ARRAY_REF || assign->expr(1)->variant() != ARRAY_REF)
        return result;

    if (isNonDistrArray(assign->expr(0)->symbol()) && isNonDistrArray(assign->expr(1)->symbol()))
        return result;

    SgArrayRefExp *leftPart = (SgArrayRefExp*)assign->expr(0);
    SgArrayRefExp *rightPart = (SgArrayRefExp*)assign->expr(1);

    if (!hasSections(leftPart) || !hasSections(rightPart))
        return result;

    const int leftSubs = leftPart->numberOfSubscripts();
    const int rightSubs = rightPart->numberOfSubscripts();

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> leftBound;
    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> rightBound;

    bool resL = fillBounds(OriginalSymbol(leftPart->symbol()), leftBound);
    bool resR = fillBounds(OriginalSymbol(rightPart->symbol()), rightBound);

    if (!resL || !resR)
        return result;

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
#ifdef _WIN32
        messagesForFile.push_back(Messages(WARR, assign->lineNumber(), R94, L"can not convert array assign to loop", 2001));
#endif
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

    result.push_back(retVal);
    
    return result;
}

static vector<SgStatement*> convertFromStmtToLoop(SgStatement *assign, SgFile *file, vector<Messages> &messagesForFile)
{
    vector<SgStatement*> result;

    if (assign->variant() != ASSIGN_STAT)
        return result;

    if (assign->expr(0) == NULL || assign->expr(1) == NULL)
        return result;

    if (assign->expr(1)->lhs() == NULL || assign->expr(1)->rhs() == NULL)
        return result;
        
    if (assign->expr(0)->variant() != ARRAY_REF ||
        assign->expr(1)->rhs()->variant() != ARRAY_REF ||
        assign->expr(1)->lhs()->variant() != ARRAY_REF)
        return result;

    if (isNonDistrArray(assign->expr(0)->symbol()) || 
        isNonDistrArray(assign->expr(1)->rhs()->symbol()) ||
        isNonDistrArray(assign->expr(1)->lhs()->symbol()) )
        return result;

    SgArrayRefExp *leftPart = (SgArrayRefExp*)assign->expr(1)->lhs();
    SgArrayRefExp *rightPart = (SgArrayRefExp*)assign->expr(1)->rhs();
    SgArrayRefExp *assignPart = (SgArrayRefExp*)assign->expr(0);

    if (!hasSections(leftPart) || !hasSections(rightPart) || !hasSections(assignPart))
        return result;

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> leftBound;
    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> rightBound;
    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> assignBound;

    bool resL = fillBounds(OriginalSymbol(leftPart->symbol()), leftBound);
    bool resR = fillBounds(OriginalSymbol(rightPart->symbol()), rightBound);
    bool resA = fillBounds(OriginalSymbol(assignPart->symbol()), assignBound);

    if (!resL || !resR || !resA)
        return result;

    SgForStmt *retVal = NULL;
    SgStatement *copy = assign->copyPtr();

    SgArrayRefExp *leftArrayRef = (SgArrayRefExp*)copy->expr(1)->lhs();
    SgArrayRefExp *rightArrayRef = (SgArrayRefExp*)copy->expr(1)->rhs();
    SgArrayRefExp *assignArrayRef = (SgArrayRefExp*)copy->expr(0);

    SgExpression *subsL = leftArrayRef->lhs();
    SgExpression *subsR = rightArrayRef->lhs();
    SgExpression *subsA = assignArrayRef->lhs();

    int lIdx = 0;
    int rIdx = 0;
    int aIdx = 0;
    bool bodyInserted = false;

    SgStatement *scope = assign;

    const int leftSubs = leftPart->numberOfSubscripts();
    const int rightSubs = rightPart->numberOfSubscripts();
    const int assignSubs = assignPart->numberOfSubscripts();

    while (true)
    {
        if (scope->variant() == PROG_HEDR || scope->variant() == FUNC_HEDR || scope->variant() == PROC_HEDR)
            break;
        scope = scope->controlParent();
    }

    vector<bool> fixedLeft(leftBound.size()), fixedRight(rightBound.size()), fixedAssign(assignBound.size());
    for (int i = 0; i < leftBound.size(); ++i)
        fixedLeft[i] = false;
    for (int i = 0; i < fixedRight.size(); ++i)
        fixedRight[i] = false;
    for (int i = 0; i < fixedAssign.size(); ++i)
        fixedAssign[i] = false;

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> leftSections, rightSections, assignSections;

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

    ex = subsA;
    for (int i = 0; i < assignSubs; ++i)
    {
        tuple<SgExpression*, SgExpression*, SgExpression*> bounds = assignBound[aIdx];
        if (!fillSectionInfo(ex, bounds))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (get<0>(bounds) && get<1>(bounds))
            if (string(get<0>(bounds)->unparse()) == string(get<1>(bounds)->unparse())) // fixed dimension value
                fixedAssign[i] = true;

        if (!fixedAssign[i])
            assignSections.push_back(bounds);
        ex = ex->rhs();
    }

    //fill default
    if (assignSubs == 0)
        assignSections = assignBound;

    if (leftSections.size() != rightSections.size() || 
        leftSections.size() != assignSections.size() ||
        rightSections.size() != assignSections.size())
    {
        __spf_print(1, "WARN: can not convert array assign to loop on line %d\n", assign->lineNumber());
#ifdef _WIN32
        messagesForFile.push_back(Messages(WARR, assign->lineNumber(), R95, L"can not convert array assign to loop", 2001));
#endif
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

        if (!assignSections.size())
            assignSections = assignBound;

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

        if (leftSubs == 0)
        {
            for (int i = 0; i < leftSections.size(); ++i)
            {
                SgExpression *shiftA = get<0>(leftBound[i]);
                shiftA = CalculateInteger(shiftA);
                leftArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftA);
            }
        }
        else 
        {
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
        }
            
        if (rightSubs == 0)
        {
            for (int i = 0; i < rightSections.size(); ++i)
            {
                SgExpression *shiftB = get<0>(rightBound[i]);
                shiftB = CalculateInteger(shiftB);
                rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftB);
            }
        }
        else
        {
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

        if (assignSubs == 0)
        {
            for (int i = 0; i < assignSections.size(); ++i)
            {
                SgExpression *shiftC = get<0>(assignBound[i]);
                shiftC = CalculateInteger(shiftC);
                assignArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftC);
            }
        }
        else
        {
            ex = subsA;
            for (int i = 0, freeIdx = 0; i < assignSubs; ++i, subsA = subsA->rhs())
            {
                if (!fixedAssign[i])
                {
                    SgExpression *shiftC = get<0>(assignSections[freeIdx]);
                    if (shiftC == NULL)
                        shiftC = get<0>(assignBound[freeIdx]);
                    shiftC = CalculateInteger(shiftC);

                    SgExpression *stepC = get<2>(assignSections[freeIdx]);
                    if (stepC != NULL)
                        stepC = CalculateInteger(stepC);

                    insertMainPart(subsA, file, freeIdx, shiftC, stepC, scope);

                    ++freeIdx;
                }
            }
        }

    }

    __spf_print(1, "%s", string(retVal->unparse()).c_str());

    result.push_back(retVal);

    return result;
}


static vector<SgStatement*> convertFromSumToLoop(SgStatement *assign, SgFile *file, vector<Messages> &messagesForFile)
{
    vector <SgStatement*> result;

    if (assign->expr(0) == NULL || assign->expr(1) == NULL)
        return result;

    if (assign->expr(1)->lhs() == NULL || assign->expr(1)->lhs()->lhs() == NULL ||
        assign->expr(1)->lhs()->lhs()->variant() != ARRAY_REF)
        return result;

    if (isNonDistrArray(assign->expr(1)->lhs()->lhs()->symbol()))
        return result;

    SgForStmt *retVal = NULL;
    SgStatement *copy = assign->copyPtr();

    copy->setExpression(1, assign->expr(1)->lhs()->lhs()->copy());

    SgExpression *leftPart = assign->expr(0);
    SgArrayRefExp *rightPart = (SgArrayRefExp*)assign->expr(1)->lhs()->lhs();
    const int Subs = rightPart->numberOfSubscripts();

    if (!hasSections(rightPart))
        return result;

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> rightBound;

    bool resR = fillBounds(OriginalSymbol(rightPart->symbol()), rightBound);
    if (!resR)
        return result;

    SgArrayRefExp *rightArrayRef = (SgArrayRefExp*)copy->expr(1);
    SgExpression *subsR = rightArrayRef->lhs();

    int rIdx = 0;
    bool bodyInserted = false;

    SgStatement *scope = assign;

    const int rightSubs = rightPart->numberOfSubscripts();

    while (true)
    {
        if (scope->variant() == PROG_HEDR || scope->variant() == FUNC_HEDR || scope->variant() == PROC_HEDR)
            break;
        scope = scope->controlParent();
    }

    vector<bool> fixedRight(rightBound.size());
    for (int i = 0; i < fixedRight.size(); ++i)
        fixedRight[i] = false;

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> rightSections;

    SgExpression *ex = subsR;
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

    __spf_print(1, "was on line %d file %s\n", assign->lineNumber(), assign->fileName());
    __spf_print(1, "%s", string(assign->unparse()).c_str());

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> forBounds;
    // create DO bounds

    if (!rightSections.size())
        rightSections = rightBound;


    for (int i = 0; i < rightSections.size(); ++i)
    {
        SgExpression *maxBound = NULL;

        if (get<2>(rightSections[i]))
            maxBound = &((*(get<1>(rightSections[i])) - *get<0>(rightSections[i])) / *get<2>(rightSections[i]));
        else
            maxBound = &(*(get<1>(rightSections[i])) - *get<0>(rightSections[i]));
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

    if (rightSubs == 0)
    {
        for (int i = 0; i < rightSections.size(); ++i)
        {
            SgExpression *shiftB = get<0>(rightBound[i]);
            shiftB = CalculateInteger(shiftB);
            rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftB);
        }
    }
    else
    {
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

    
    SgAssignStmt *init = new SgAssignStmt(*(assign->expr(0)), *(new SgValueExp(0)));   //      sum = 0 

    __spf_print(1, "%s\n", " _______ ");
    __spf_print(1, "%s", string(init->unparse()).c_str());

    SgExpression *newRightPart = new SgExpression(ADD_OP);
    newRightPart->setLhs(copy->expr(0)->copyPtr());
    newRightPart->setRhs(copy->expr(1));
    copy->setExpression(1, *newRightPart);

    result.push_back(retVal);
    result.push_back(init);
    __spf_print(1, "%s", string(retVal->unparse()).c_str());

    return result;
}

static vector<SgStatement*> convertFromWhereToLoop(SgStatement *assign, SgFile *file, vector<Messages> &messagesForFile)
{
    vector <SgStatement*> result;
    
    if (assign->expr(0) == NULL || assign->expr(1) == NULL)
        return result;

    if (assign->expr(0)->lhs() == NULL ||
        assign->expr(0)->lhs()->variant() != ARRAY_REF ||
        assign->expr(1)->variant() != ARRAY_REF)
        return result;

    /*
    if (!strcmp(assign->expr(0)->lhs()->symbol()->identifier(),
                assign->expr(1)->symbol()->identifier()))
        return result;
    */
    __spf_print(1, "%s\n", " _______ ");

    SgForStmt *retVal = NULL;
    SgStatement *copy = assign->copyPtr();

    SgExpression *leftPart = assign->expr(0);
    SgArrayRefExp *rightPart = (SgArrayRefExp*)assign->expr(1);
    const int Subs = rightPart->numberOfSubscripts();

    if (!hasSections(rightPart))
        return result;

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> rightBound;

    bool resR = fillBounds(OriginalSymbol(rightPart->symbol()), rightBound);
    if (!resR)
        return result;

    SgArrayRefExp *rightArrayRef = (SgArrayRefExp*)copy->expr(1);
    SgExpression *subsR = rightArrayRef->lhs();

    int rIdx = 0;
    bool bodyInserted = false;

    SgStatement *scope = assign;

    const int rightSubs = rightPart->numberOfSubscripts();

    while (true)
    {
        if (scope->variant() == PROG_HEDR || scope->variant() == FUNC_HEDR || scope->variant() == PROC_HEDR)
            break;
        scope = scope->controlParent();
    }

    vector<bool> fixedRight(rightBound.size());
    for (int i = 0; i < fixedRight.size(); ++i)
        fixedRight[i] = false;

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> rightSections;

    SgExpression *ex = subsR;
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

    __spf_print(1, "was on line %d file %s\n", assign->lineNumber(), assign->fileName());
    __spf_print(1, "%s", string(assign->unparse()).c_str());

    vector<tuple<SgExpression*, SgExpression*, SgExpression*>> forBounds;
    // create DO bounds

    if (!rightSections.size())
        rightSections = rightBound;


    for (int i = 0; i < rightSections.size(); ++i)
    {
        SgExpression *maxBound = NULL;

        if (get<2>(rightSections[i]))
            maxBound = &((*(get<1>(rightSections[i])) - *get<0>(rightSections[i])) / *get<2>(rightSections[i]));
        else
            maxBound = &(*(get<1>(rightSections[i])) - *get<0>(rightSections[i]));
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

    if (rightSubs == 0)
    {
        for (int i = 0; i < rightSections.size(); ++i)
        {
            SgExpression *shiftB = get<0>(rightBound[i]);
            shiftB = CalculateInteger(shiftB);
            rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i), SgTypeInt(), scope)) + *shiftB);
        }
    }
    else
    {
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

    SgIfStmt *ret = (SgIfStmt*) new SgStatement(EXPR_IF);
   
    ret->setExpression(0, *retVal->lexNext()->expr(0));
    ret->expr(0)->setLhs(retVal->lexNext()->expr(1));
    ret->setExpression(1, *retVal->lexNext()->expr(1));
    ret->setExpression(2, *retVal->lexNext()->expr(2));
    
    retVal->setLexNext(*ret);
  
    __spf_print(1, "%s\n", " _______ ");
    __spf_print(1, "%s", string(retVal->unparse()).c_str());

    return result;
}

// functionality: convert A[(...)] = B[(...)] to loop 
//                move (create copy) init assigns in DECL before the first executable
void convertFromAssignToLoop(SgFile *file, vector<Messages> &messagesForFile)
{
    int funcNum = file->numberOfFunctions();
    auto useMapMod = createMapOfModuleUses(file);
    
    vector<SgStatement*> modules;
    findModulesInFile(file, modules);
    map<string, SgStatement*> modMap;
    for (auto& elem : modules)
        modMap[elem->symbol()->identifier()] = elem;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        vector<pair<SgStatement*, SgStatement*>> toMove;

        SgStatement *firstExec = NULL;
        SgStatement *controlParFristExec = NULL;

        for (SgStatement* st1 = file->functions(i); st1 != lastNode && !firstExec; st1 = st1->lexNext())
        {
            const int var = st1->variant();
            if (isSgExecutableStatement(st1))
                firstExec = st1;
            if ((var == CONTAINS_STMT || var == PROC_HEDR || var == FUNC_HEDR) && st1 != file->functions(i))
                break;
        }

        if (firstExec)
            controlParFristExec = firstExec->controlParent();

        set<SgStatement*> useMods;
        map<string, set<SgSymbol*>> byUse = moduleRefsByUseInFunction(st);

        map<string, SgStatement*> derivedTypesDecl = createDerivedTypeDeclMap(st);
        for (; st != lastNode; st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;

            //move init assigns before the first statement
            if (firstExec && isSgDeclarationStatement(st))
            {
                SgVarDeclStmt* declStat = (SgVarDeclStmt*)st;
                for (int k = 0; k < declStat->numberOfSymbols(); ++k)
                {
                    SgExpression* completeInit = declStat->completeInitialValue(k);
                    if (completeInit)
                    {
                        auto copyLeft = completeInit->lhs()->copyPtr();
                        auto copyRight = completeInit->rhs()->copyPtr();
                        SgStatement* toAdd = new SgStatement(ASSIGN_STAT, NULL, NULL, copyLeft, copyRight, NULL);

                        if (isDerivedAssign(toAdd))
                            replaceDerivedAssigns(file, toAdd, firstExec, derivedTypesDecl);
                        else
                        {
                            toAdd->setFileId(controlParFristExec->getFileId());
                            toAdd->setProject(controlParFristExec->getProject());

                            firstExec->insertStmtBefore(*toAdd, *controlParFristExec);

                            toAdd->setlineNumber(getNextNegativeLineNumber());
                            toAdd->setLocalLineNumber(st->lineNumber());
                        }
                        toMove.push_back(make_pair(st, toAdd));
                    }
                }
            }

            //move SPF ANALYSIS PARAMETER before current statement
            vector<SgStatement*> parameters;
            for (auto& attr : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ SPF_ANALYSIS_DIR }))
            {
                SgExpression* exprList = attr->expr(0);
                while (exprList)
                {
                    if (exprList->lhs()->variant() == SPF_PARAMETER_OP)
                    {
                        SgExpression* list = exprList->lhs()->lhs();
                        while (list)
                        {
                            if (list->lhs()->variant() != ASSGN_OP)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            parameters.push_back(new SgStatement(ASSIGN_STAT, NULL, NULL, list->lhs()->lhs()->copyPtr(), list->lhs()->rhs()->copyPtr(), NULL));

                            parameters.back()->setFileId(controlParFristExec->getFileId());
                            parameters.back()->setProject(controlParFristExec->getProject());

                            parameters.back()->setlineNumber(getNextNegativeLineNumber());
                            parameters.back()->setLocalLineNumber(attr->lineNumber());

                            list = list->rhs();
                        }
                    }
                    exprList = exprList->rhs();
                }
            }

            for (auto& par : parameters)
            {
                st->insertStmtBefore(*par, *st->controlParent());
                st->nodeBefore()->setUnparseIgnore(true);
            }
            
            if (firstExec && st->variant() == USE_STMT)
                useMods.insert(st);

            //TODO: change names by use
            //TODO: create init of decl for all USE map
            if (firstExec && isSgExecutableStatement(st))
            {
                for (auto& elem : useMods)
                {
                    auto it = modMap.find(elem->symbol()->identifier());
                    if (it == modMap.end())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    for (SgStatement* stM = it->second->lexNext(); stM != it->second->lastNodeOfStmt(); stM = stM->lexNext())
                    {
                        if (isSgExecutableStatement(stM))
                            break;
                        const int var = stM->variant();
                        if (var == PROC_HEDR || var == FUNC_HEDR)
                            break;
                        
                        if (isSgDeclarationStatement(stM))
                        {
                            SgVarDeclStmt* declStat = (SgVarDeclStmt*)stM;
                            bool ifHasParameterAttr = false;
                            
                            for (int z = 0; z < declStat->numberOfAttributes(); ++z)
                                if (declStat->attribute(z)->variant() == PARAMETER_OP)
                                    ifHasParameterAttr = true;

                            if (ifHasParameterAttr)
                            {
                                for (int k = 0; k < declStat->numberOfSymbols(); ++k)
                                {
                                    SgExpression* completeInit = declStat->completeInitialValue(k);
                                    if (completeInit)
                                    {
                                        SgStatement* toAdd = new SgStatement(ASSIGN_STAT, NULL, NULL, completeInit->lhs()->copyPtr(), completeInit->rhs()->copyPtr(), NULL);
                                        toAdd->setFileId(controlParFristExec->getFileId());
                                        toAdd->setProject(controlParFristExec->getProject());

                                        firstExec->insertStmtBefore(*toAdd, *controlParFristExec);

                                        toMove.push_back(make_pair(elem, toAdd));
                                        toAdd->setlineNumber(getNextNegativeLineNumber());
                                        toAdd->setLocalLineNumber(elem->lineNumber());
                                    }
                                }
                            }
                        }
                    }
                }
                firstExec = NULL;
            }

            bool isFCALL = false;
            if (st->variant() == ASSIGN_STAT || st->variant() == WHERE_NODE)
            {
                vector<SgStatement*> conv;
                if (st->expr(1)->variant() == FUNC_CALL )
                {
                    const string fName = st->expr(1)->symbol()->identifier();
                    if (fName == "sum")
                    {
                        conv = convertFromSumToLoop(st, file, messagesForFile);
                        // add SPF ANALYSIS REDUCTION(SUM(<var>)) after convertion
                        if (conv.size())
                        {
                            if (fName == "sum" && conv.size() != 2)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            SgStatement* redDir = new SgStatement(SPF_ANALYSIS_DIR);
                            SgExpression* list = new SgExpression(EXPR_LIST, 
                                new SgExpression(REDUCTION_OP, 
                                    new SgExpression(EXPR_LIST, 
                                        new SgExpression(ARRAY_OP, new SgKeywordValExp("sum"), new SgVarRefExp(conv[1]->expr(0)->symbol())))));
                            redDir->setExpression(0, list);

                            conv[0]->addAttribute(SPF_ANALYSIS_DIR, redDir, sizeof(SgStatement));
                            isFCALL = true;
                        }
                    }
                }
                else
                {
                    if (st->expr(1)->variant() == ADD_OP || st->expr(1)->variant() == MULT_OP || st->expr(1)->variant() == SUBT_OP)
                        conv = convertFromStmtToLoop(st, file, messagesForFile);
                    else
                    {
                        if (st->variant() == WHERE_NODE)
                            conv = convertFromWhereToLoop(st, file, messagesForFile);
                        else
                            conv = convertFromAssignToLoop(st, file, messagesForFile);
                    }
                }

                //TODO: need to check
                if (conv.size() != 0)
                {
                    auto currFile = st->getFileId();
                    auto currProj = st->getProject();

                    for (int i = conv.size() - 1; i >= 0 ; --i)
                        st->insertStmtBefore(*(conv[i]), *st->controlParent());

                    if (conv.size() >= 1)
                        toMove.push_back(make_pair(st, conv[0]));

                    for (int i = 0; i < conv.size(); ++i)
                    {
                        if (conv[i]->variant() != ASSIGN_STAT)
                        {
                            SgStatement *end = conv[i]->lastNodeOfStmt();
                            for (SgStatement *st1 = conv[i]; st1 != end; st1 = st1->lexNext())
                            {
                                st1->setlineNumber(getNextNegativeLineNumber());
                                st1->setLocalLineNumber(st->lineNumber());
                                st1->setFileId(currFile);
                                st1->setProject(currProj);
                            }
                            end->setlineNumber(getNextNegativeLineNumber());
                            end->setLocalLineNumber(st->lineNumber());
                            end->setFileId(currFile);
                            end->setProject(currProj);
                        }
                        else
                        {
                            conv[i]->setlineNumber(getNextNegativeLineNumber());
                            conv[i]->setLocalLineNumber(st->lineNumber());
                            conv[i]->setFileId(currFile);
                            conv[i]->setProject(currProj);
                        }
                    }
                }
            }
        }

        for (auto &move : toMove)
        {
            move.first->addAttribute(ASSIGN_STAT, move.second, sizeof(SgStatement*));
            char *comments = move.first->comments();
            if (comments)
                move.second->setComments(comments);
        }
    }
}

bool notDeletedVectorAssign(SgStatement *st)
{
    if (!st)
        return false;

    SgExpression* rPart = st->expr(1);
    if (!rPart)
        return false;

    const int var = rPart->variant();
    return (var == ADD_OP || var == MULT_OP || var == SUBT_OP || var == FUNC_CALL && !strcmp(rPart->symbol()->identifier(), "sum"));
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
            for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ ASSIGN_STAT }))
            {
                if (reversed)
                {
                    if (data->lineNumber() > 0)
                    {
                        toMove.push_back(make_pair(st, data));
                        st->lexPrev()->insertStmtAfter(*data, *st->controlParent());

                        data->addAttribute(ASSIGN_STAT, st, sizeof(SgStatement*));
                    }
                }
                else
                {
                    if (data->lineNumber() < 0 && 
                        (isUnderParallelLoop(st) || (notDeletedVectorAssign(st) && st->lexPrev()->variant() == DVM_PARALLEL_ON_DIR)))
                    {
                        toMove.push_back(make_pair(st, data));
                        st->insertStmtAfter(*data, *st->controlParent());

                        //data->addAttribute(ASSIGN_STAT, st, sizeof(SgStatement*));
                        if (data->variant() == FOR_NODE)
                        {
                            for (auto st_loc = data; st_loc != data->lastNodeOfStmt(); st_loc = st_loc->lexNext())
                                if (st_loc->variant() == FOR_NODE)
                                    newDeclarations.insert(st_loc->symbol());
                        }
                        else if (data->variant() == ASSIGN_STAT)
                        {
                            if (data->lexNext()->variant() == FOR_NODE)
                            {
                                for (auto st_loc = data->lexNext(); st_loc != data->lexNext()->lastNodeOfStmt(); st_loc = st_loc->lexNext())
                                    if (st_loc->variant() == FOR_NODE)
                                        newDeclarations.insert(st_loc->symbol());
                            }
                        }
                    }
                }
            }
        }

        for (auto& move : toMove)
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
