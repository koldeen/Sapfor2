#include "../Utils/leak_detector.h"

#include <set>
#include <map>
#include <string>
#include <vector>

#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../GraphCall/graph_calls.h"
#include "directive_parser.h"
#include "../Distribution/DvmhDirective_func.h"
#include "../Utils/SgUtils.h"

#include "shadow.h"
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

                        // 50 %
                        if (dimSize * 0.5 < maxSpec)
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

static SgStatement *getLast(SgStatement *nextStart, SgStatement *st, SgStatement *end)
{
    SgStatement *last = st;
    if (nextStart->lineNumber() > st->lineNumber())
    {
        if (nextStart->lineNumber() > end->lineNumber())
            last = nextStart->controlParent()->lastNodeOfStmt();
        else
            last = end;
    }

    return last;
}

static void findNext(SgStatement *st, SgStatement *end, vector<pair<ShadowNode*, set<string>>> &next,  const map<void*, ShadowNode*> &allShadowNodes, 
                     const ShadowNode *currDir, map<int, SgStatement*> &labeledStmts, set<string> arrayAssigns)
{
    for (; st != end; st = st->lexNext())
    {
        const int var = st->variant();
        if (var == DVM_PARALLEL_ON_DIR)
        {
            next.push_back(make_pair(allShadowNodes.find(st)->second, arrayAssigns));
            break;
        }
        else
        {
            if (var == IF_NODE)
            {
                SgIfStmt *tmp = (SgIfStmt*)st;
                SgStatement *last = st;
                while (last->variant() != CONTROL_END)
                    last = last->lastNodeOfStmt();

                auto tb = tmp->trueBody();
                auto fb = tmp->falseBody();

                vector<pair<SgStatement*, SgStatement*>> bounds;
                if (fb)
                {
                    while (fb->variant() != CONTROL_END)
                    {
                        if (tmp->variant() == IF_NODE)
                            bounds.push_back(make_pair(tmp->lexNext(), fb));
                        else
                            bounds.push_back(make_pair(tmp, fb));

                        if (fb->variant() == ELSEIF_NODE)
                        {
                            tmp = (SgIfStmt*)fb;
                            tb = tmp->trueBody();
                            fb = tmp->falseBody();
                        }
                        else
                        {
                            bounds.push_back(make_pair(fb, last));
                            fb = last;
                        }
                    }
                }

                if (bounds.size() == 0)
                    bounds.push_back(make_pair(tmp->lexNext(), last));
                
                for (auto &elem : bounds)
                    findNext(elem.first, elem.second, next, allShadowNodes, currDir, labeledStmts, arrayAssigns);

                st = st->lastNodeOfStmt();
            }
            else if (var == FOR_NODE || var == WHILE_NODE)
            {
                findNext(st->lexNext(), st->lastNodeOfStmt(), next, allShadowNodes, currDir, labeledStmts, arrayAssigns);
                st = st->lastNodeOfStmt();
            }
            else if (var == GOTO_NODE)
            {
                SgGotoStmt *gotoS = (SgGotoStmt*)st;
                int labNum = gotoS->branchLabel()->thelabel->stateno;
                auto nextStart = labeledStmts[labNum];
                
                SgStatement *last = getLast(nextStart, st, end);                
                findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, arrayAssigns);
                
                break;
            }
            else if (var == COMGOTO_NODE)
            {
                SgComputedGotoStmt* cgt = (SgComputedGotoStmt*)(st);
                SgExpression* label = cgt->labelList();

                set<int> uniqLab;
                while (label)
                {
                    uniqLab.insert(((SgLabelRefExp *)(label->lhs()))->label()->thelabel->stateno);
                    label = label->rhs();
                }

                for (auto &lab : uniqLab)
                {
                    auto nextStart = labeledStmts[lab];
                    SgStatement *last = getLast(nextStart, st, end);
                    findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, arrayAssigns);
                }
                break;
            }
            else if (var == CONTROL_END)
            {
                auto cp = st->controlParent();
                if (((SgStatement*)currDir->dir)->controlParent() == cp)
                {
                    if (cp->variant() == FOR_NODE || cp->variant() == WHILE_NODE)
                        findNext(cp->lexNext(), st, next, allShadowNodes, currDir, labeledStmts, arrayAssigns);
                }
            }
            else if (var == ASSIGN_STAT)
            {
                if (st->expr(0)->variant() == ARRAY_REF)
                    arrayAssigns.insert(st->expr(0)->symbol()->identifier());
            }
            else if (var == LOGIF_NODE)
            {
                findNext(st->lexNext(), st->lexNext()->lexNext(), next, allShadowNodes, currDir, labeledStmts, arrayAssigns);
                st = st->lastNodeOfStmt();
            }
            else if (var == ARITHIF_NODE)
            {
                SgArithIfStmt *arith = (SgArithIfStmt*)st;
                for (int i = 0; i < 2; ++i)
                {
                    auto nextStart = labeledStmts[((SgLabelRefExp*)(arith->label(i)))->label()->thelabel->stateno];
                    SgStatement *last = getLast(nextStart, st, end);
                    findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, arrayAssigns);
                }
                break;
            }
            //TODO
            /*else if (var == SWITCH_NODE)
            {

            }*/
        }
    }
}

void ShadowNode::moveShadow(pair<pair<string, string>, vector<pair<int, int>>> &shadowIn, set<string> &cornerIn)
{
    bool found = false;
    for (auto &elem : newShadows)
    {
        if (elem.first == shadowIn.first)
        {
            for (int i = 0; i < elem.second.size(); ++i)
            {
                elem.second[i].first = std::max(elem.second[i].first, shadowIn.second[i].first);
                elem.second[i].second = std::max(elem.second[i].second, shadowIn.second[i].second);
            }

            auto it = cornerIn.find(shadowIn.first.first);
            if (it != cornerIn.end())
            {
                newCorner.insert(*it);
                cornerIn.erase(it);
            }

            found = true;
            break;
        }
    }

    if (!found)
    {
        newShadows.push_back(shadowIn);
        auto it = cornerIn.find(shadowIn.first.first);
        if (it != cornerIn.end())
        {
            newCorner.insert(*it);
            cornerIn.erase(it);
        }
    }
}

void GroupShadowStep1(SgFile *file, vector<FuncInfo*> &funcs, DIST::Arrays<int> &allArrays)
{
    map<string, FuncInfo*> mapF;
    for (auto &elem : funcs)
        mapF[elem->funcName] = elem;

    for (int f = 0; f < file->numberOfFunctions(); ++f)
    {
        SgStatement *func = file->functions(f);

        auto it = mapF.find(((SgProgHedrStmt*)func)->nameWithContains());
        if (it == mapF.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        FuncInfo *currF = it->second;

        //find all PARALLEL dirs
        for (SgStatement *st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == DVM_PARALLEL_ON_DIR)
            {
                auto newShNode = new ShadowNode(st);
                currF->allShadowNodes[st] = newShNode;

                fillShadowAcrossFromParallel(SHADOW_RENEW_OP, st, newShNode->shadows, newShNode->corner);
                newShNode->newShadows = newShNode->shadows;
                newShNode->newCorner = newShNode->corner;

                st = st->lexNext();
                if (st->variant() != FOR_NODE)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                st = st->lastNodeOfStmt();
            }
        }

        if (currF->allShadowNodes.size() == 0)
            continue;

        if (currF->allShadowNodes.size() != 1)
        {
            //find first
            for (SgStatement *st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
            {
                if (st->variant() == DVM_PARALLEL_ON_DIR)
                {
                    currF->shadowTree = currF->allShadowNodes[st];
                    break;
                }
            }
        }
        else
        {
            currF->shadowTree = currF->allShadowNodes.begin()->second;
            continue;
        }
        
        map<int, SgStatement*> labeledStmts;
        for (auto st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
            if (st->label())
                labeledStmts[st->label()->thelabel->stateno] = st;

        // set next
        for (auto &elem : currF->allShadowNodes)
        {
            SgStatement *start = (SgStatement*)elem.first;
            //            loop           end loop         
            auto tmp = start->lexNext()->lastNodeOfStmt();           

            set<string> arrayAssigns;
            for (auto st = start->lexNext(); st != start->lexNext()->lastNodeOfStmt(); st = st->lexNext())
            {
                if (st->variant() == ASSIGN_STAT)
                    if (st->expr(0)->variant() == ARRAY_REF)
                        arrayAssigns.insert(st->expr(0)->symbol()->identifier());
            }
            start = tmp->lexNext();
            findNext(start, func->lastNodeOfStmt(), elem.second->next, currF->allShadowNodes, elem.second, labeledStmts, arrayAssigns);
        }

        //check for internal error
        for (auto &elem : currF->allShadowNodes)
        {
            set<pair<ShadowNode*, set<string>>> tmpl;
            for (auto &listElem : elem.second->next)
                tmpl.insert(listElem);
            if (tmpl.size() != elem.second->next.size())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }

        // set prev
        for (auto &elem : currF->allShadowNodes)
        {
            for (auto &next : elem.second->next)
                next.first->prev.push_back(elem.second);
        }

        // grouping
        bool changes = true;
        int moveCount = 0;
        while (changes)
        {
            changes = false;
            for (auto &shadow : currF->allShadowNodes)
            {
                for (auto &next : shadow.second->next)
                {
                    ShadowNode *nextNode = next.first;
                    vector<set<string>> writes;
                    for (auto &prev : next.first->prev)
                    {
                        for (int i = 0; i < prev->next.size(); ++i)
                        {
                            if (prev->next[i].first == nextNode)
                            {
                                writes.push_back(prev->next[i].second);
                                break;
                            }
                        }
                    }
                    if (writes.size() != next.first->prev.size())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    auto rewriteSh = next.first->newShadows;
                    rewriteSh.clear();

                    for (auto &sh : next.first->newShadows)
                    {
                        bool checkOK = true;
                        for (auto &wr : writes)
                            if (wr.find(sh.first.first) != wr.end())
                                checkOK = false;

                        if (checkOK)
                        {
                            for (int i = 0; i < next.first->prev.size(); ++i)
                            {
                                if (i != next.first->prev.size() - 1)
                                {
                                    auto tmpCopy = next.first->newCorner;
                                    shadow.second->moveShadow(sh, tmpCopy);
                                }
                                else
                                    shadow.second->moveShadow(sh, next.first->newCorner);
                                
                                changes = true;
                                ++moveCount;
                            }
                        }
                        else
                            rewriteSh.push_back(sh);
                    }
                    next.first->newShadows = rewriteSh;
                }
            }
        }

        __spf_print(1, "  shadow moveCount %d\n", moveCount);

        //replacing
        if (moveCount != 0)
        {            
            for (auto &shadow : currF->allShadowNodes)
            {
                if (shadow.second->newShadows != shadow.second->shadows || shadow.second->newCorner != shadow.second->corner)
                {
                    int inserted = 0;
                    auto expr = new SgExpression(EXPR_LIST);
                    auto p = expr;
                    for (auto &currSh : shadow.second->newShadows)
                    {
                        DIST::Array *currArray = allArrays.GetArrayByName(currSh.first.second);

                        if (inserted != 0)
                            p = createAndSetNext(RIGHT, EXPR_LIST, p);                        
                        else if (inserted == 0)
                        {
                            p = createAndSetNext(LEFT, SHADOW_RENEW_OP, p);
                            p = createAndSetNext(LEFT, EXPR_LIST, p);
                        }

                        SgArrayRefExp *newArrayRef = new SgArrayRefExp(*currArray->GetDeclSymbol());
                        newArrayRef->addAttribute(ARRAY_REF, currArray, sizeof(DIST::Array));

                        auto zeroShifts = currSh.second;
                        std::fill(zeroShifts.begin(), zeroShifts.end(), make_pair(0, 0));

                        for (auto &elem : genSubscripts(currSh.second, zeroShifts))
                            newArrayRef->addSubscript(*elem);

                        if (shadow.second->newCorner.find(currSh.first.first) != shadow.second->newCorner.end())
                        {
                            SgExpression *tmp = new SgExpression(ARRAY_OP, newArrayRef, NULL, NULL);
                            p->setLhs(*tmp);

                            SgKeywordValExp *tmp1 = new SgKeywordValExp("CORNER");
                            p->lhs()->setRhs(tmp1);
                        }
                        else
                            p->setLhs(newArrayRef);

                        inserted++;
                    }

                    SgExpression *dirExp = ((SgStatement*)shadow.first)->expr(1);
                    if (inserted)
                    {
                        bool changed = false;
                        while (dirExp)
                        {
                            if (dirExp->lhs()->variant() == SHADOW_RENEW_OP)
                            {
                                dirExp->setLhs(expr->lhs());
                                changed = true;
                                break;
                            }
                            dirExp = dirExp->rhs();
                        }

                        if (!changed)
                        {
                            SgExpression *dirExp = ((SgStatement*)shadow.first)->expr(1);
                            SgExpression *tmp = new SgExpression(EXPR_LIST);
                            tmp->setLhs(expr->lhs());
                            tmp->setRhs(dirExp);
                            dirExp = tmp;

                            ((SgStatement*)shadow.first)->setExpression(1, *dirExp);
                        }
                    }
                    else
                    {
                        vector<SgExpression*> newList;
                        while (dirExp)
                        {
                            if (dirExp->lhs()->variant() != SHADOW_RENEW_OP)
                                newList.push_back(dirExp->lhs());
                            dirExp = dirExp->rhs();
                        }

                        SgExpression *list = new SgExpression(EXPR_LIST);
                        SgExpression *tmp = list;
                        for (int z = 0; z < newList.size(); ++z)
                        {
                            tmp->setLhs(newList[z]);
                            if (z != newList.size() - 1)
                            {
                                tmp->setRhs(new SgExpression(EXPR_LIST));
                                tmp = tmp->rhs();
                            }
                            else
                                tmp->setRhs(NULL);
                        }

                        ((SgStatement*)shadow.first)->setExpression(1, *list);
                    }
                }
            }
        }
    }
}