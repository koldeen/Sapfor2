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

using std::vector;
using std::set;
using std::pair;
using std::tuple;
using std::make_pair;
using std::string;
using std::to_string;
using std::get;

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
        for (SgExpression *ex = decl->expr(0); ex; ex = ex->rhs())
        {
            if (OriginalSymbol(ex->lhs()->symbol())->identifier() == string(symb->identifier()))
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
        auto leftBounds = leftBound[lIdx];
        int rMinus = 0;
        bool needFor = true;

        if (leftSubs == 0)
            leftArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep))));
        else
        {
            if (!fillSectionInfo(subsL, leftBounds))
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            subsL->setLhs(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep))));
            if (get<0>(leftBounds) && get<1>(leftBounds))
                if (string(get<0>(leftBounds)->unparse()) == string(get<1>(leftBounds)->unparse())) // fixed dimension value
                {
                    subsL->setLhs(get<0>(leftBounds)->copy());
                    rMinus = 1;
                    needFor = false;
                }
            subsL = subsL->rhs();
        }

        if (rIdx < rightBound.size() && needFor)
        {
            SgExpression *shift = &(get<0>(rightBound[rIdx])->copy() - get<0>(leftBounds)->copy());
            bool fixedDim = true;
            while (fixedDim)
            {
                fixedDim = false;
                if (rightSubs == 0)
                    rightArrayRef->addSubscript(*new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep))) + *shift);
                else
                {
                    tuple<SgExpression*, SgExpression*, SgExpression*> rightBounds;
                    if (!fillSectionInfo(subsR, rightBounds))
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    SgExpression *idxVar = new SgVarRefExp(findSymbolOrCreate(file, "i_" + to_string(deep)));
                    if (get<2>(leftBounds))
                        idxVar = &(*idxVar / get<2>(leftBounds)->copy());
                    if (get<2>(rightBounds))
                        idxVar = &(*idxVar * get<2>(rightBounds)->copy());

                    if (get<0>(rightBounds))
                        shift = &(get<0>(rightBounds)->copy() - get<0>(leftBounds)->copy());

                    subsR->setLhs(*idxVar + *shift);
                    if (get<0>(rightBounds) && get<1>(rightBounds))
                        if (string(get<0>(rightBounds)->unparse()) == string(get<1>(rightBounds)->unparse())) // fixed dimension value
                        {
                            subsR->setLhs(get<0>(rightBounds)->copy());
                            fixedDim = true;
                        }
                    subsR = subsR->rhs();
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

            if (get<2>(leftBounds)) // has step
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(deep)), get<0>(leftBounds)->copy(), get<1>(leftBounds)->copy(), get<2>(leftBounds)->copy(), *body);
            else
                retVal = new SgForStmt(*findSymbolOrCreate(file, "i_" + to_string(deep)), get<0>(leftBounds)->copy(), get<1>(leftBounds)->copy(), *body);
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