#include "../leak_detector.h"

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
#include "../SgUtils.h"
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
    bool ok = true;
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
            bounds.push_back(std::make_tuple(alloc->lhs()->lhs(), alloc->lhs()->rhs(), (SgExpression*)NULL));
        else
            bounds.push_back(std::make_tuple(new SgValueExp(1), alloc->lhs(), (SgExpression*)NULL));
    }

    return ok;
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
                    get<0>(section) = subs->lhs()->lhs()->lhs()->copyPtr();

                if (subs->lhs()->lhs()->rhs() != NULL) // high section
                    get<1>(section) = subs->lhs()->lhs()->rhs()->copyPtr();

                if (subs->lhs()->rhs() != NULL) // step of section
                    get<2>(section) = subs->lhs()->rhs()->copyPtr();
            }
            else
            {
                if (subs->lhs()->lhs() != NULL) // low section
                    get<0>(section) = subs->lhs()->lhs()->copyPtr();

                if (subs->lhs()->rhs() != NULL) // high section
                    get<1>(section) = subs->lhs()->rhs()->copyPtr();
            }
        }
        else
        {   // low and high sections
            get<0>(section) = subs->lhs()->copyPtr();
            get<1>(section) = subs->lhs()->copyPtr();
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

static bool needSwap(SgExpression *leftStep, SgExpression *rightStep)
{
    if (leftStep == NULL || rightStep == NULL)
        return false;

    pair<bool, int> left, right;
    if (leftStep->isInteger())
        left = make_pair(true, leftStep->valueInteger());
    else
        left.first = false;

    if (rightStep->isInteger())
        right = make_pair(true, rightStep->valueInteger());
    else
        right.first = false;

    if (right.first && left.first)
        if (left.second > right.second)
            return true;    

    return false;
}

static void insertMainPart(SgExpression *subsL, SgFile *file, const int deep, const tuple<SgExpression*, SgExpression*, SgExpression*> &bounds)
{
    subsL->setLhs(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep))));
}

static void insertMinorPart(SgExpression *subsR, SgFile *file, const int deep, 
                            const tuple<SgExpression*, SgExpression*, SgExpression*> &leftBounds,
                            const tuple<SgExpression*, SgExpression*, SgExpression*> &rightBounds,
                            SgExpression *shift)
{
    SgExpression *idxVar = new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep)));

    bool stepIsEqual = false;
    int valL = 0, valR = 0;

    if (get<2>(rightBounds))
        if (get<2>(rightBounds)->isInteger())
            valR = get<2>(rightBounds)->valueInteger();

    if (get<2>(leftBounds))
        if (get<2>(leftBounds)->isInteger())
            valL = get<2>(leftBounds)->valueInteger();

    if (get<2>(rightBounds) && get<2>(leftBounds))
    {
        if (string(get<2>(rightBounds)->unparse()) == string(get<2>(leftBounds)->unparse()))
            stepIsEqual = true;
        else
        {
            if ((valR < 0 && valL < 0) || (valR < 0 && valL > 0))
            {
                valR = -valR;
                valL = -valL;
            }
        }
    }

    if (get<2>(rightBounds) && !stepIsEqual)
    {
        if (get<2>(rightBounds)->isInteger())
        {
            if (valR != 1)
                idxVar = &(*idxVar * *new SgValueExp(valR));
        }
        else
            idxVar = &(*idxVar * get<2>(rightBounds)->copy());        
    }

    if (get<2>(leftBounds) && !stepIsEqual)
    {
        if (get<2>(leftBounds)->isInteger())
        {
            if (valL != 1)
                idxVar = &(*idxVar / *new SgValueExp(valL));
        }
        else
            idxVar = &(*idxVar / get<2>(leftBounds)->copy());
    }

    if (get<0>(rightBounds))
        shift = &(get<0>(rightBounds)->copy() - get<0>(leftBounds)->copy());

    int res;
    int err = CalculateInteger(shift, res);
    if (err == 0)
    {
        if (res != 0)
            shift = new SgValueExp(res);
        else
            shift = NULL;
    }
        
    if (shift)
        subsR->setLhs(*idxVar + *shift);
    else
        subsR->setLhs(*idxVar);
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

    bool resL = fillBounds(leftPart->symbol(), leftBound);
    bool resR = fillBounds(rightPart->symbol(), rightBound);

    if (!resL && !resR)
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
        vector<tuple<SgExpression*, SgExpression*, SgExpression*>> forBounds;
        // create DO bounds
        if (leftSections.size())
        {
            for (int i = 0; i < leftSections.size(); ++i)
            {
                if (needSwap(get<2>(leftSections[i]), get<2>(rightSections[i])))
                    forBounds.push_back(rightSections[i]);
                else
                    forBounds.push_back(leftSections[i]);
            }
        }
        else
        {
            leftSections = leftBound;
            rightSections = rightBound;

            for (int i = 0; i < leftSections.size(); ++i)
                forBounds.push_back(leftSections[i]);
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
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(i)), get<0>(forBounds[i])->copy(), get<1>(forBounds[i])->copy(), get<2>(forBounds[i])->copy(), *body);
            else
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(i)), get<0>(forBounds[i])->copy(), get<1>(forBounds[i])->copy(), *body);
        }
                
        if (leftSubs == 0 && rightSubs == 0)
        {
            // A = B
            for (int i = 0; i < leftSections.size(); ++i)
                leftArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i))));

            for (int i = 0; i < rightSections.size(); ++i)
            {
                SgExpression *shift = &(get<0>(rightSections[i])->copy() - get<0>(leftSections[i])->copy());

                int res;
                int err = CalculateInteger(shift, res);
                if (err == 0)
                {
                    if (res != 0)
                        shift = new SgValueExp(res);
                    else
                        shift = NULL;
                }
                if (shift)
                    rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i))) + *shift);
                else
                    rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i))));
            }
        }
        else if (leftSubs == 0 && rightSubs != 0)
        {
            // A = B( : : : )
            for (int i = 0; i < leftSections.size(); ++i)
                leftArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i))));

            ex = subsR;
            for (int i = 0, freeIdx = 0; i < rightSubs; ++i, subsR = subsR->rhs())
            {
                if (!fixedRight[i])
                {
                    if (!needSwap(get<2>(leftSections[freeIdx]), get<2>(rightSections[freeIdx])))
                    {
                        SgExpression *shift = &(get<0>(leftSections[freeIdx])->copy() - get<0>(rightSections[freeIdx])->copy());
                        insertMinorPart(subsR, file, freeIdx, leftSections[freeIdx], rightSections[freeIdx], shift);
                    }
                    else
                        insertMainPart(subsR, file, freeIdx, rightSections[freeIdx]);
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
                    if (needSwap(get<2>(leftSections[freeIdx]), get<2>(rightSections[freeIdx])))
                    {
                        SgExpression *shift = &(get<0>(rightSections[freeIdx])->copy() - get<0>(leftSections[freeIdx])->copy());
                        insertMinorPart(subsL, file, freeIdx, rightSections[freeIdx], leftSections[freeIdx], shift);
                    }
                    else
                        insertMainPart(subsL, file, freeIdx, leftSections[freeIdx]);
                    ++freeIdx;
                }
            }

            for (int i = 0; i < rightSections.size(); ++i)
            {
                SgExpression *shift = &(get<0>(rightSections[i])->copy() - get<0>(leftSections[i])->copy());

                int res;
                int err = CalculateInteger(shift, res);
                if (err == 0)
                {
                    if (res != 0)
                        shift = new SgValueExp(res);
                    else
                        shift = NULL;
                }
                if (shift)
                    rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i))) + *shift);
                else
                    rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(i))));
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
                    if (needSwap(get<2>(leftSections[freeIdx]), get<2>(rightSections[freeIdx])))
                    {
                        SgExpression *shift = &(get<0>(rightSections[freeIdx])->copy() - get<0>(leftSections[freeIdx])->copy());
                        insertMinorPart(subsL, file, freeIdx, rightSections[freeIdx], leftSections[freeIdx], shift);
                    }
                    else
                        insertMainPart(subsL, file, freeIdx, leftSections[freeIdx]);
                    ++freeIdx;
                }
            }

            ex = subsR;
            for (int i = 0, freeIdx = 0; i < rightSubs; ++i, subsR = subsR->rhs())
            {
                if (!fixedRight[i])
                {
                    if (!needSwap(get<2>(leftSections[freeIdx]), get<2>(rightSections[freeIdx])))
                    {
                        SgExpression *shift = &(get<0>(leftSections[freeIdx])->copy() - get<0>(rightSections[freeIdx])->copy());
                        insertMinorPart(subsR, file, freeIdx, leftSections[freeIdx], rightSections[freeIdx], shift);
                    }
                    else
                        insertMainPart(subsR, file, freeIdx, rightSections[freeIdx]);
                    ++freeIdx;
                }
            }
        }

        __spf_print(1, "was on line %d file %s\n", assign->lineNumber(), assign->fileName());
        __spf_print(1, "%s", string(assign->unparse()).c_str());
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
            for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ ASSIGN_STAT }))
                if (data->lineNumber() < 0)
                    toMove.push_back(make_pair(st, data));
        }

        for (auto &move : toMove)
            move.second->extractStmt();
    }
}