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
#include "../ExpressionTransform/expr_transform.h"

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

extern int maxShadowWidth;
static void replaceShadowByRemote(SgExpression *spec, SgStatement *stat,
                                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    if (spec)
    {
        SgExpression *shadow, *remote, *beforeSh;
        findShadowAndRemote(spec, shadow, remote, beforeSh);

        if (shadow)
        {            
            set<string> remotesNames;

            SgExpression *newRemote = NULL;
            SgExpression *pRem = NULL;
            if (!remote)
                pRem = newRemote = new SgExpression(REMOTE_ACCESS_OP);
            else
            {
                map<pair<string, string>, Expression*> remotes;
                fillRemoteFromComment(new Statement(stat), remotes, false, DVM_PARALLEL_ON_DIR);
                for (auto &elem : remotes)
                    remotesNames.insert(elem.first.first);
                pRem = remote;
            }
            
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
                    

                    set<DIST::Array*> realRefs;
                    getRealArrayRefs(currArray, currArray, realRefs, arrayLinksByFuncCalls);

                    bool replaceByRemote = false;
                    for (auto &realArray : realRefs)
                    {
                        auto arraySizes = realArray->GetSizes();
                        //check sizes
                        for (auto &dim : arraySizes)
                            if (dim.first > dim.second || (dim.first == -1 && dim.second == -1))
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        if (spec.size() != arraySizes.size())
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                                                
                        for (int z = 0; z < spec.size(); ++z)
                        {
                            float maxSpec = std::max(spec[z].first, spec[z].second);
                            float dimSize = arraySizes[z].second - arraySizes[z].first + 1;

                            // 50 % by default
                            if (dimSize * (maxShadowWidth / 100.) < maxSpec)
                            {
                                replaceByRemote = true;
                                break;
                            }
                        }

                        if (replaceByRemote)
                            break;
                    }

                    if (replaceByRemote)
                    {
                        __spf_print(1, "RemoteAccess[devour]: replace shadow by remote for array '%s'\n", currArray->GetShortName().c_str());
                        currArray->RemoveShadowSpec(spec);

                        SgExpression *toAdd = new SgExpression(EXPR_LIST);
                        toAdd->setLhs(elem);
                        toAdd->setRhs(pRem->lhs());

                        auto it = remotesNames.find(OriginalSymbol(elem->symbol())->identifier());
                        if (it == remotesNames.end())
                        {
                            remotesNames.insert(it, OriginalSymbol(elem->symbol())->identifier());
                            pRem->setLhs(toAdd);
                        }                     

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

void devourShadowByRemote(SgFile *file, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    for (SgStatement *stat = file->firstStatement(); stat; stat = stat->lexNext())
    {
        if (stat->variant() == DVM_PARALLEL_ON_DIR && stat->lineNumber() == 0) // except user dirs
        {
            devourShadow(stat->expr(1), stat);
            replaceShadowByRemote(stat->expr(1), stat, arrayLinksByFuncCalls);
        }
    }
}

void transformShadowIfFull(SgFile *file, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    for (SgStatement *first = file->firstStatement(); first; first = first->lexNext())
    {
        if (first->variant() == DVM_PARALLEL_ON_DIR && first->lineNumber() == 0) // except user dirs
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

static SgStatement* getLast(SgStatement* nextStart, SgStatement* st, SgStatement* end)
{
    SgStatement* last = st;
    if (nextStart->lineNumber() > st->lineNumber())
    {
        if (nextStart->lineNumber() > end->lineNumber())
            last = nextStart->controlParent()->lastNodeOfStmt();
        else
            last = end;
    }

    return last;
}

static void addRealArraysRef(set<DIST::Array*>& writesTo, const set<DIST::Array*>& used,
                             const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls)
{
    for (auto& elem : used)
    {
        set<DIST::Array*> realRef;
        getRealArrayRefs(elem, elem, realRef, arrayLinksByFuncCalls);

        for (auto& realR : realRef)
            writesTo.insert(realR);
    }
}

static void fillFromFunction(const string& s, set<DIST::Array*>& writesTo,
                             const map<string, FuncInfo*>& mapFuncs, 
                             const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls)
{
    if (isIntrinsicFunctionName(s.c_str()) == false)
    {
        auto it = mapFuncs.find(s);
        if (it != mapFuncs.end())
            addRealArraysRef(writesTo, it->second->usedArraysWrite, arrayLinksByFuncCalls);
        else // TODO: fill all used arrays for writes in common and in modules 
        {

        }
    }
}

static void findFuncCalls(SgExpression* ex, set<DIST::Array*>& writesTo,
                          const map<string, FuncInfo*>& mapFuncs, 
                          const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
            fillFromFunction(ex->symbol()->identifier(), writesTo, mapFuncs, arrayLinksByFuncCalls);

        findFuncCalls(ex->lhs(), writesTo, mapFuncs, arrayLinksByFuncCalls);
        findFuncCalls(ex->rhs(), writesTo, mapFuncs, arrayLinksByFuncCalls);
    }
}

static void findNext(SgStatement* st, SgStatement* end, vector<pair<ShadowNode*, set<DIST::Array*>>>& next, const map<void*, ShadowNode*>& allShadowNodes,
                     const ShadowNode* currDir, map<int, SgStatement*>& labeledStmts, set<DIST::Array*> writesTo,
                     const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls,
                     const map<string, FuncInfo*>& mapFuncs)
{
    for (; st != end; st = st->lexNext())
    {
        const int var = st->variant();
        if (var == DVM_PARALLEL_ON_DIR)
        {
            next.push_back(make_pair(allShadowNodes.find(st)->second, writesTo));
            break;
        }
        else
        {
            if (var == IF_NODE)
            {
                SgIfStmt* tmp = (SgIfStmt*)st;
                SgStatement* last = st;
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
                            if (fb == NULL)
                            {
                                bounds.push_back(make_pair(tmp->lexNext(), last));
                                fb = last;
                            }
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

                for (auto& elem : bounds)
                    findNext(elem.first, elem.second, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs);

                st = st->lastNodeOfStmt();
            }
            else if (var == FOR_NODE || var == WHILE_NODE)
            {
                findNext(st->lexNext(), st->lastNodeOfStmt(), next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs);
                st = st->lastNodeOfStmt();
            }
            else if (var == GOTO_NODE)
            {
                SgGotoStmt* gotoS = (SgGotoStmt*)st;
                int labNum = gotoS->branchLabel()->thelabel->stateno;
                auto nextStart = labeledStmts[labNum];

                SgStatement* last = getLast(nextStart, st, end);
                findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs);

                break;
            }
            else if (var == COMGOTO_NODE)
            {
                SgComputedGotoStmt* cgt = (SgComputedGotoStmt*)(st);
                SgExpression* label = cgt->labelList();

                set<int> uniqLab;
                while (label)
                {
                    uniqLab.insert(((SgLabelRefExp*)(label->lhs()))->label()->thelabel->stateno);
                    label = label->rhs();
                }

                for (auto& lab : uniqLab)
                {
                    auto nextStart = labeledStmts[lab];
                    SgStatement* last = getLast(nextStart, st, end);
                    findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs);
                }
                break;
            }
            else if (var == CONTROL_END)
            {
                auto cp = st->controlParent();
                if (((SgStatement*)currDir->dir)->controlParent() == cp)
                {
                    if (cp->variant() == FOR_NODE || cp->variant() == WHILE_NODE)
                        findNext(cp->lexNext(), st, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs);
                }
            }
            else if (var == ASSIGN_STAT)
            {
                if (st->expr(0)->variant() == ARRAY_REF)
                {
                    auto s = st->expr(0)->symbol();
                    DIST::Array* inPar = getArrayFromDeclarated(declaratedInStmt(s), s->identifier());
                    addRealArraysRef(writesTo, { inPar }, arrayLinksByFuncCalls);
                }
            }
            else if (var == LOGIF_NODE)
            {
                findNext(st->lexNext(), st->lexNext()->lexNext(), next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs);
                st = st->lastNodeOfStmt();
            }
            else if (var == ARITHIF_NODE)
            {
                SgArithIfStmt* arith = (SgArithIfStmt*)st;
                for (int i = 0; i < 2; ++i)
                {
                    auto nextStart = labeledStmts[((SgLabelRefExp*)(arith->label(i)))->label()->thelabel->stateno];
                    SgStatement* last = getLast(nextStart, st, end);
                    findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs);
                }
                break;
            }            
            else if (var == SWITCH_NODE) //TODO
            {

            }
            else if (var == PROC_STAT)
                fillFromFunction(st->symbol()->identifier(), writesTo, mapFuncs, arrayLinksByFuncCalls);

            //find func calls
            for (int z = 0; z < 3; ++z)
                findFuncCalls(st->expr(z), writesTo, mapFuncs, arrayLinksByFuncCalls);
        }
    }
}

static void viewGraph(CBasicBlock *first)
{
    auto nexts = first->getSucc();
    auto items = first->getStart();
    auto itemsEnd = first->getEnd();
    while (items != itemsEnd)
    {
        auto stmt = items->getStatement();
        if (stmt)
            printf("%d tag %s\n", stmt->lineNumber(), tag[stmt->variant()]);

        stmt = items->getOriginalStatement();
        if (stmt)
            printf("ORIG %d %s\n", stmt->lineNumber(), tag[stmt->variant()]);

        items = items->getNext();
    }
    
    while (nexts)
    {
        viewGraph(nexts->block);
        nexts = nexts->next;
    }
}

static int getLine(void *dir)
{
    return ((SgStatement*)dir)->lexNext()->lineNumber();
}

static string getNodeName(ShadowNode* node)
{
    return std::to_string(getLine(node->dir)) + ":" + std::to_string(node->newShadows.size()) + ":" + std::to_string(node->newCorners.size());
}

static void buildGraphViz(const map<void*, ShadowNode*>& nodes, ShadowNode* start)
{
    string graph = "digraph G{\n";
    set<string> lines;
    for (auto& elem : nodes)
    {
        string curr = getNodeName(elem.second);
        for (auto& next : elem.second->next)
            lines.insert("\"" + curr + "\"->\"" + getNodeName(next.first) + "\"\n");
    }
    lines.insert(string("\"START") + "\"->\"" + getNodeName(start) + "\"\n");
    for (auto& line : lines)
        graph += line;
    graph += "}\n";
    printf("%s\n", graph.c_str());
}

static int groupingShadowNodes(map<void*, ShadowNode*>& allShadowNodes)
{
    //buildGraphViz(currF->allShadowNodes, currF->shadowTree);
    int moveCount = 0;
    bool changes = true;
    while (changes)
    {
        changes = false;
        for (auto& shadow : allShadowNodes)
        {
            for (auto& next : shadow.second->next)
            {
                //dont move back
                if (shadow.second->IsBackDirection(next.first->location))
                    continue;

                ShadowNode* nextNode = next.first;
                vector<set<DIST::Array*>> writes;
                for (auto& prev : next.first->prev)
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

                vector<pair<DIST::Array*, vector<pair<int, int>>>> rewriteSh;
                for (auto& sh : next.first->newShadows)
                {
                    bool checkOK = true;
                    for (auto& wr : writes)
                        for (auto& array : wr)
                            if (array == sh.first)
                                checkOK = false;

                    if (checkOK)
                    {
                        for (int i = 0; i < next.first->prev.size(); ++i)
                        {
                            if (i != next.first->prev.size() - 1)
                            {
                                auto tmpCopy = next.first->newCorners;
                                shadow.second->MoveShadow(sh, tmpCopy);
                            }
                            else
                                shadow.second->MoveShadow(sh, next.first->newCorners);

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
    return moveCount;
}

static void replacingShadowNodes(map<void*, ShadowNode*>& allShadowNodes)
{
    for (auto& shadow : allShadowNodes)
    {
        if (shadow.second->newShadows != shadow.second->shadows || shadow.second->newCorners != shadow.second->corners)
        {
            int inserted = 0;
            auto expr = new SgExpression(EXPR_LIST);
            auto p = expr;
            for (auto& currSh : shadow.second->newShadows)
            {
                DIST::Array* currArray = currSh.first;

                if (inserted != 0)
                    p = createAndSetNext(RIGHT, EXPR_LIST, p);
                else if (inserted == 0)
                {
                    p = createAndSetNext(LEFT, SHADOW_RENEW_OP, p);
                    p = createAndSetNext(LEFT, EXPR_LIST, p);
                }

                SgArrayRefExp* newArrayRef = new SgArrayRefExp(*currArray->GetDeclSymbol());
                newArrayRef->addAttribute(ARRAY_REF, currArray, sizeof(DIST::Array));

                auto zeroShifts = currSh.second;
                std::fill(zeroShifts.begin(), zeroShifts.end(), make_pair(0, 0));

                for (auto& elem : genSubscripts(currSh.second, zeroShifts))
                    newArrayRef->addSubscript(*elem);

                if (shadow.second->newCorners.find(currArray) != shadow.second->newCorners.end())
                {
                    SgExpression* tmp = new SgExpression(ARRAY_OP, newArrayRef, NULL, NULL);
                    p->setLhs(*tmp);

                    SgKeywordValExp* tmp1 = new SgKeywordValExp("CORNER");
                    p->lhs()->setRhs(tmp1);
                }
                else
                    p->setLhs(newArrayRef);

                inserted++;
            }

            SgExpression* dirExp = ((SgStatement*)shadow.first)->expr(1);
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
                    SgExpression* dirExp = ((SgStatement*)shadow.first)->expr(1);
                    SgExpression* tmp = new SgExpression(EXPR_LIST);
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

                SgExpression* list = new SgExpression(EXPR_LIST);
                SgExpression* tmp = list;
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

static void fillShadowAcrossFromParallel(ShadowNode* newShNode, SgStatement* st, const DIST::Arrays<int>& allArrays)
{
    vector<pair<pair<string, string>, vector<pair<int, int>>>> shadows;
    set<string> corners;

    fillShadowAcrossFromParallel(SHADOW_RENEW_OP, new Statement(st), shadows, corners);

    for (auto& shadow : shadows)
    {
        DIST::Array* array = allArrays.GetArrayByName(shadow.first.second);        
        newShNode->shadows.push_back(make_pair(array, shadow.second));

        auto itCorner = corners.find(shadow.first.first);
        if (itCorner != corners.end())
            newShNode->corners.insert(array);
    }

    newShNode->newShadows = newShNode->shadows;
    newShNode->newCorners = newShNode->corners;
}

static GraphsKeeper *graphsKeeper;
void GroupShadow(const map<string, vector<FuncInfo*>> &allFuncs, 
                 const map<string, vector<LoopGraph*>>& loops, 
                 const DIST::Arrays<int> &allArrays,
                 const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls)
{
    //GraphsKeeper *gk = GraphsKeeper::getGraphsKeeper();

    map<string, FuncInfo*> mapF;
    for (auto& byFile : allFuncs)
        for (auto &elem : byFile.second)
                mapF[elem->funcName] = elem;

    map<FuncInfo*, int> moveCounts;

    //building shadow graph
    for (auto& funcByFile : allFuncs)    
    {
        map<int, LoopGraph*> mapLoops;
        auto itL = loops.find(funcByFile.first);
        if (itL != loops.end())
            createMapLoopGraph(itL->second, mapLoops);

        for (auto& currF : funcByFile.second)
        {
            SgStatement* func = currF->funcPointer->GetOriginal();
            if (func->switchToFile() == false)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            //ControlFlowGraph* CGraph = gk->buildGraph(func)->CGraph;
            //viewGraph(CGraph->getFirst());

            //find all labled statements
            map<int, SgStatement*> labeledStmts;
            for (auto st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
                if (st->label())
                    labeledStmts[st->label()->thelabel->stateno] = st;

            //find all PARALLEL dirs
            for (SgStatement* st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
            {
                if (st->variant() == DVM_PARALLEL_ON_DIR)
                {
                    auto newShNode = new ShadowNode(st, currF, st->lexNext()->lineNumber());
                    currF->allShadowNodes[st] = newShNode;

                    fillShadowAcrossFromParallel(newShNode, st, allArrays);

                    st = st->lexNext();
                    if (st->variant() != FOR_NODE)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    st = st->lastNodeOfStmt();
                }
                else if (st->variant() == CONTAINS_STMT)
                    break;
            }

            if (currF->allShadowNodes.size() == 0)
                continue;

            if (currF->allShadowNodes.size() != 1)
            {
                //find first
                for (SgStatement* st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
                {
                    if (st->variant() == DVM_PARALLEL_ON_DIR)
                    {
                        currF->shadowTree = currF->allShadowNodes[st];
                        break;
                    }
                    else if (st->variant() == CONTAINS_STMT)
                        break;
                }

                if (currF->shadowTree == NULL)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            else
            {
                currF->shadowTree = currF->allShadowNodes.begin()->second;
                continue;
            }

            // set next
            for (auto& elem : currF->allShadowNodes)
            {
                SgForStmt* start = (SgForStmt*)((SgStatement*)elem.first)->lexNext();

                auto itLoop = mapLoops.find(start->lineNumber());
                if (itLoop == mapLoops.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                set<DIST::Array*> writesTo;
                addRealArraysRef(writesTo, itLoop->second->usedArraysWrite, arrayLinksByFuncCalls);

                //TODO: may be replace to GraphKeeper
                findNext(start, func->lastNodeOfStmt(), elem.second->next, currF->allShadowNodes, elem.second, labeledStmts, writesTo, arrayLinksByFuncCalls, mapF);
            }

            //check for internal error
            for (auto& elem : currF->allShadowNodes)
            {
                set<pair<ShadowNode*, set<DIST::Array*>>> tmpl;
                for (auto& listElem : elem.second->next)
                    tmpl.insert(listElem);
                if (tmpl.size() != elem.second->next.size())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            // set prev
            for (auto& elem : currF->allShadowNodes)
                for (auto& next : elem.second->next)
                    next.first->prev.push_back(elem.second);
        }
    }

    //TODO: do it interprocess!
    // grouping
    for (auto& funcByFile : allFuncs)
    {
        for (auto& currF : funcByFile.second)
        {
            moveCounts[currF] = groupingShadowNodes(currF->allShadowNodes);
            __spf_print(1, "  shadow moveCount %d for function '%s'\n", moveCounts[currF], currF->funcName.c_str());
        }
    }

    //replacing
    for (auto& funcByFile : allFuncs)
    {
        for (auto& currF : funcByFile.second)
        {
            if (moveCounts[currF] != 0)
            {
                if (currF->funcPointer->GetOriginal()->switchToFile() == false)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                replacingShadowNodes(currF->allShadowNodes);
            }
        }
    }
}