#include "../Utils/leak_detector.h"

#include <set>
#include <map>
#include <string>
#include <vector>

#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../GraphLoop/graph_loops_func.h"

#include "dvm.h"

using std::set;
using std::map;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;

static void findShadowAndRemote(SgExpression *spec, SgExpression *&shadow, SgExpression *&remote, SgExpression *&beforeSh)
{
    remote = shadow = NULL;
    beforeSh = spec;

    for (auto iter = spec, iterB = spec; iter; iter = iter->rhs())
    {
        if (iter->lhs()->variant() == SHADOW_RENEW_OP)
        {
            beforeSh = iterB;
            shadow = iter->lhs();
        }
        else if (iter->lhs()->variant() == REMOTE_ACCESS_OP)
            remote = iter->lhs();

        if (iterB != iter)
            iterB = iterB->rhs();
    }
}

static set<string> getAllRemoteWithDDOT(SgExpression *remote)
{
    set<string> allRemoteWithDDOT;
    for (auto iter = remote->lhs(); iter; iter = iter->rhs())
    {
        SgExpression *elem = iter->lhs();
        if (elem->variant() == ARRAY_REF)
        {
            bool allDDOT = true;
            for (auto iterL = elem->lhs(); iterL; iterL = iterL->rhs())
                if (iterL->lhs()->variant() != DDOT)
                    allDDOT = false;

            if (allDDOT)
                allRemoteWithDDOT.insert(elem->symbol()->identifier());
        }
    }

    return allRemoteWithDDOT;
}

static DIST::Array* getArrayFromAttribute(SgExpression *elem)
{
    DIST::Array *currArray = NULL;
    for (int i = 0; i < elem->numberOfAttributes() && currArray == NULL; ++i)
        if (elem->attributeType(i) == ARRAY_REF)
            currArray = (DIST::Array *)(elem->getAttribute(i)->getAttributeData());

    if (currArray == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return currArray;
}


static vector<pair<int, int>> fillShadowSpec(SgExpression *elem)
{
    vector<pair<int, int>> toDel;
    for (SgExpression *list = elem->lhs(); list; list = list->rhs())
        toDel.push_back(make_pair(list->lhs()->lhs()->valueInteger(), list->lhs()->rhs()->valueInteger()));

    return toDel;
}

static void devourShadow(SgExpression *spec, SgStatement *stat)
{
    if (spec)
    {
        SgExpression *shadow, *remote, *beforeSh;
        findShadowAndRemote(spec, shadow, remote, beforeSh);
        
        if (shadow && remote)
        {
            const set<string> allRemoteWithDDOT = getAllRemoteWithDDOT(remote);

            auto currShadowP = shadow;
            int numActiveSh = 0;

            for (auto iter = shadow->lhs(); iter; iter = iter->rhs())
            {
                SgExpression *elem = iter->lhs();
                //if shadow has CORNER
                if (elem->variant() == ARRAY_OP)
                    elem = elem->lhs();

                if (elem->variant() == ARRAY_REF)
                {
                    if (allRemoteWithDDOT.find(elem->symbol()->identifier()) != allRemoteWithDDOT.end())
                    {
                        DIST::Array *currArray = getArrayFromAttribute(elem);
                        vector<pair<int, int>> toDel = fillShadowSpec(elem); 

                        currArray->RemoveShadowSpec(toDel);
                        if (currShadowP == shadow)
                            shadow->setLhs(iter->rhs());
                        else
                            currShadowP->setRhs(iter->rhs());
                    }
                    else
                    {
                        ++numActiveSh;
                        if (currShadowP == shadow)
                            currShadowP = shadow->lhs();
                        else
                            currShadowP = currShadowP->rhs();
                    }
                }
            }

            //remove shadow dir
            if (numActiveSh == 0)
            {
                if (spec->lhs()->variant() == SHADOW_RENEW_OP)
                    stat->setExpression(1, *(spec->rhs()));
                else
                    beforeSh->setRhs(beforeSh->rhs()->rhs());
            }
        }
    }
}

static void convertShadowToDDOTRemote(SgExpression *spec)
{
    while (spec)
    {
        spec->setLhs(new SgExpression(DDOT));
        spec = spec->rhs();
    }
}

static void replaceShadowByRemote(SgExpression *spec, SgStatement *stat)
{
    if (spec)
    {
        SgExpression *shadow, *remote, *beforeSh;
        findShadowAndRemote(spec, shadow, remote, beforeSh);

        if (shadow)
        {
            SgExpression *newRemote = NULL;
            SgExpression *pRem = NULL;
            if (!remote)
                pRem = newRemote = new SgExpression(REMOTE_ACCESS_OP);
            else
                pRem = remote;
            
            bool remoteWasAdded = false;
            auto currShadowP = shadow;
            int numActiveSh = 0;

            for (auto iter = shadow->lhs(); iter; iter = iter->rhs())
            {
                SgExpression *elem = iter->lhs();
                //if shadow has CORNER
                if (elem->variant() == ARRAY_OP)
                    elem = elem->lhs();

                if (elem->variant() == ARRAY_REF)
                {
                    DIST::Array *currArray = getArrayFromAttribute(elem);
                    vector<pair<int, int>> spec = fillShadowSpec(elem);
                    auto arraySizes = currArray->GetSizes();

                    //check sizes
                    for (auto &dim : arraySizes)
                        if (dim.first > dim.second)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    
                    if (spec.size() != arraySizes.size())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    bool replaceByRemote = false;
                    for (int z = 0; z < spec.size(); ++z)
                    {
                        float maxSpec = std::max(spec[z].first, spec[z].second);
                        float dimSize = arraySizes[z].second - arraySizes[z].first + 1;

                        // 15 %
                        if (dimSize * 0.15 < maxSpec)
                        {
                            replaceByRemote = true;
                            break;
                        }
                    }

                    if (replaceByRemote)
                    {
                        currArray->RemoveShadowSpec(spec);

                        SgExpression *toAdd = new SgExpression(EXPR_LIST);
                        toAdd->setLhs(elem);
                        toAdd->setRhs(pRem->lhs());
                        pRem->setLhs(toAdd);
                        remoteWasAdded = true;

                        convertShadowToDDOTRemote(elem->lhs());
                        
                        if (currShadowP == shadow)
                            shadow->setLhs(iter->rhs());
                        else
                            currShadowP->setRhs(iter->rhs());
                    }
                    else
                    {
                        ++numActiveSh;
                        if (currShadowP == shadow)
                            currShadowP = shadow->lhs();
                        else
                            currShadowP = currShadowP->rhs();
                    }
                }
            }

            //remove shadow dir
            if (numActiveSh == 0)
            {
                if (spec->lhs()->variant() == SHADOW_RENEW_OP)
                    stat->setExpression(1, *(spec->rhs()));
                else
                    beforeSh->setRhs(beforeSh->rhs()->rhs());
            }

            if (newRemote && remoteWasAdded)
                stat->setExpression(1, *new SgExpression(EXPR_LIST, newRemote, stat->expr(1), NULL));
        }
    }
}

void devourShadowByRemote(SgFile *file)
{
    for (SgStatement *stat = file->firstStatement(); stat; stat = stat->lexNext())
    {
        if (stat->variant() == DVM_PARALLEL_ON_DIR)
        {
            devourShadow(stat->expr(1), stat);
            replaceShadowByRemote(stat->expr(1), stat);
        }
    }
}

void transformShadowIfFull(SgFile *file, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    for (SgStatement *first = file->firstStatement(); first; first = first->lexNext())
    {
        if (first->variant() == DVM_PARALLEL_ON_DIR)
        {
            SgExpression *spec = first->expr(1);
            if (spec)
            {
                SgExpression *shadow = NULL;
                for (auto iter = spec; iter; iter = iter->rhs())
                {
                    if (iter->lhs()->variant() == SHADOW_RENEW_OP)
                    {
                        shadow = iter->lhs();
                        break;
                    }
                }

                if (shadow)
                {
                    for (auto iter = shadow->lhs(); iter; iter = iter->rhs())
                    {
                        SgExpression *elem = iter->lhs();
                        //if shadow has CORNER
                        if (elem->variant() == ARRAY_OP)
                            elem = elem->lhs();

                        if (elem->variant() == ARRAY_REF)
                        {
                            DIST::Array *currArray = NULL;
                            for (int i = 0; i < elem->numberOfAttributes() && currArray == NULL; ++i)
                                if (elem->attributeType(i) == ARRAY_REF)
                                    currArray = (DIST::Array *)(elem->getAttribute(i)->getAttributeData());

                            if (currArray == NULL)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            
                            set<DIST::Array*> arrays;
                            getRealArrayRefs(currArray, currArray, arrays, arrayLinksByFuncCalls);

                            if (arrays.size() == 0)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            auto shadowSpec = (*arrays.begin())->GetShadowSpec();
                            if (shadowSpec.size() != currArray->GetDimSize())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            SgArrayRefExp *ref = (SgArrayRefExp*)elem;
                            if (ref->numberOfSubscripts() != currArray->GetDimSize())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            bool eq = true;
                            for (int i = 0; i < currArray->GetDimSize(); ++i)
                            {
                                SgExpression *subs = ref->subscript(i);
                                if (subs->variant() == DDOT)
                                {
                                    if (subs->lhs()->isInteger() && subs->rhs()->isInteger())
                                    {
                                        if (subs->lhs()->valueInteger() != shadowSpec[i].first ||
                                            subs->rhs()->valueInteger() != shadowSpec[i].second)
                                        {
                                            eq = false;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        eq = false;
                                        break;
                                    }
                                }
                                else
                                {
                                    eq = false;
                                    break;
                                }
                            }

                            //remove
                            if (eq)
                                elem->setLhs(NULL);
                        }
                    }
                }
            }
        }
    }
}