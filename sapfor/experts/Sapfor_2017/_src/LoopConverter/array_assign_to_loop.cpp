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
    for (int i = 0; i < decl->numberOfAttributes(); ++i)
    {
        if (decl->attributeType(i) == ALLOCATE_STMT)
        {
            SgStatement *data = (SgStatement *)(decl->getAttribute(i)->getAttributeData());
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
    if (subs->lhs() && subs->lhs()->variant() == DDOT)
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
            if (subs->lhs()->lhs() != NULL)
                get<0>(section) = subs->lhs()->lhs()->copyPtr();

            if (subs->lhs()->rhs() != NULL)
                get<1>(section) = subs->lhs()->rhs()->copyPtr();
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

static void checkAndinsertFixedDimentionValue(SgExpression *subs, const tuple<SgExpression*, SgExpression*, SgExpression*> &bounds, 
                                              int &rMinus, bool &flag)
{
    if (get<0>(bounds) && get<1>(bounds))
        if (string(get<0>(bounds)->unparse()) == string(get<1>(bounds)->unparse())) // fixed dimension value
        {
            subs->setLhs(get<0>(bounds)->copy());
            rMinus = 1;
            flag = false; //needFor or fixedDim flag
        }
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

    if (get<2>(rightBounds))
    {
        if (get<2>(rightBounds)->isInteger() && get<2>(rightBounds)->valueInteger() != 1)
            idxVar = &(*idxVar * get<2>(rightBounds)->copy());
    }

    if (get<2>(leftBounds))
    {
        if (get<2>(leftBounds)->isInteger() && get<2>(leftBounds)->valueInteger() != 1)
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

static SgStatement* convertFromAssignToLoop(SgStatement *assign, SgFile *file)
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

    for (int deep = 0; deep < leftBound.size(); ++deep, ++lIdx, ++rIdx)
    {
        bool needSwapLR = false;
        
        tuple<SgExpression*, SgExpression*, SgExpression*> leftBounds = leftBound[lIdx];
        tuple<SgExpression*, SgExpression*, SgExpression*> rightBounds = rightBound[rIdx];

        if (leftSubs != 0)
            if (!fillSectionInfo(subsL, leftBounds))
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);        

        if (rightSubs != 0)
            if (!fillSectionInfo(subsR, rightBounds))
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        
        if (rIdx < rightBound.size() && leftSubs != 0 && rightSubs != 0)
            needSwapLR = needSwap(get<2>(leftBounds), get<2>(rightBounds));

        int rMinus = 0;
        bool needFor = true;

        if (leftSubs == 0)
            leftArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep))));
        else
        {
            if (needSwapLR)
            {
                SgExpression *shift = &(get<0>(leftBound[rIdx])->copy() - get<0>(rightBounds)->copy());
                insertMinorPart(subsL, file, deep, rightBounds, leftBounds, shift);
            }
            else
            {
                insertMainPart(subsL, file, deep, leftBounds);
                checkAndinsertFixedDimentionValue(subsL, leftBounds, rMinus, needFor);
            }

            subsL = subsL->rhs();
        }

        if (rIdx < rightBound.size() && needFor)
        {
            if (needSwapLR)
            {
                insertMainPart(subsR, file, deep, rightBounds);
                subsR = subsR->rhs();
            }
            else
            {
                SgExpression *shift = &(get<0>(rightBound[rIdx])->copy() - get<0>(leftBounds)->copy());
                bool fixedDim = false;
                while (!fixedDim)
                {
                    fixedDim = true;
                    if (rightSubs == 0)
                        rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep))) + *shift);
                    else
                    {
                        insertMinorPart(subsR, file, deep, leftBounds, rightBounds, shift);

                        int tmp;
                        checkAndinsertFixedDimentionValue(subsR, rightBounds, tmp, fixedDim);

                        subsR = subsR->rhs();
                    }
                }
            }
        }

        SgStatement *body;
        if (needFor)
        {
            if (!bodyInserted)
            {
                body = copy;
                bodyInserted = true;
            }
            else
                body = retVal;

            tuple<SgExpression*, SgExpression*, SgExpression*> bounds;
            if (!needSwapLR)
                bounds = leftBounds;
            else
                bounds = rightBounds;

            if (get<2>(bounds)) // has step
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(deep)), get<0>(bounds)->copy(), get<1>(bounds)->copy(), get<2>(bounds)->copy(), *body);
            else
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(deep)), get<0>(bounds)->copy(), get<1>(bounds)->copy(), *body);
        }

        rIdx -= rMinus;
    } 

    while (rIdx < rightBound.size() - 1) // if fixed dims at the end
    {
        tuple<SgExpression*, SgExpression*, SgExpression*> rightBounds;
        if (!fillSectionInfo(subsR, rightBounds))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (get<0>(rightBounds) && get<1>(rightBounds))
        {
            if (string(get<0>(rightBounds)->unparse()) == string(get<1>(rightBounds)->unparse())) // fixed dimension value
                subsR->setLhs(get<0>(rightBounds)->copy());
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        rIdx++;
        subsR = subsR->rhs();
    }

    return retVal;
}

void convertFromAssignToLoop(SgFile *file)
{
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        vector<pair<SgStatement*, SgStatement*>> toMove;

        for ( ; st != lastNode; st = st->lexNext())
        {
            if (st->variant() == ASSIGN_STAT)
            {
                SgStatement *conv = convertFromAssignToLoop(st, file);
                if (conv)
                {
                    st->insertStmtBefore(*conv, *st->controlParent());
                    toMove.push_back(make_pair(st, conv));

                    SgStatement *end = conv->lastNodeOfStmt();
                    for (SgStatement *st1 = conv; st1 != end; st1 = st1->lexNext())
                        st1->setlineNumber(getNextNegativeLineNumber());
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
            for (int i = 0; i < st->numberOfAttributes(); ++i)
            {
                if (st->attributeType(i) == ASSIGN_STAT)
                {
                    SgStatement *data = (SgStatement*)(st->getAttribute(i)->getAttributeData());
                    if (data->lineNumber() < 0)
                        toMove.push_back(make_pair(st, data));
                }
            }
        }

        for (auto &move : toMove)
            move.second->extractStmt();
    }
}