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

//TODO: may be remove
static void fillFromFunction(const string& s, set<DIST::Array*>& writesTo,
                             const map<string, FuncInfo*>& mapFuncs, 
                             const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls)
{
    if (isIntrinsicFunctionName(s.c_str()) == false)
    {
        auto it = mapFuncs.find(s);
        if (it != mapFuncs.end())
            addRealArraysRef(writesTo, it->second->usedArraysWrite, arrayLinksByFuncCalls);        
    }
}

static void findFuncCalls(SgExpression* ex, vector<NextNode>& next, 
                          const map<void*, ShadowNode*>& allShadowNodes,
                          const set<DIST::Array*>& writesTo)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            if (isIntrinsicFunctionName(ex->symbol()->identifier()) == false)
                if (allShadowNodes.find(ex) != allShadowNodes.end())
                    next.push_back(NextNode(allShadowNodes.find(ex)->second, writesTo));
        }

        findFuncCalls(ex->lhs(), next, allShadowNodes, writesTo);
        findFuncCalls(ex->rhs(), next, allShadowNodes, writesTo);
    }
}

//TODO:
static SgStatement* nextWithSkipElse(SgStatement *current)
{
    SgStatement* cp = current->controlParent();
    if (cp->variant() == IF_NODE || cp->variant() == ELSEIF_NODE)
    {
        SgIfStmt* tmp = (SgIfStmt*)cp;

        auto tb = tmp->trueBody();
        auto fb = tmp->falseBody();
        auto next = current->lexNext();
        if (next->variant() == CONTROL_END)
        {
            if (next->controlParent() == tmp)
                next = next->lexNext();
        }
        if (fb && fb->variant() != ELSEIF_NODE && fb == next)
            return tmp->lastNodeOfStmt()->lexNext();
    }
    return current->lexNext();
}

static void findNext(SgStatement* st, SgStatement* end, vector<NextNode>& next, const map<void*, ShadowNode*>& allShadowNodes,
                     const ShadowNode* currDir, map<int, SgStatement*>& labeledStmts, set<DIST::Array*> writesTo,
                     const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls,
                     const map<string, FuncInfo*>& mapFuncs, bool hasRealings)
{
    for (; st != end; st = st->lexNext())
    {
        const int var = st->variant();
        if (var == DVM_PARALLEL_ON_DIR)
        {
            next.push_back(NextNode(allShadowNodes.find(st)->second, writesTo, hasRealings));
            break;
        }
        else if (var == DVM_REALIGN_DIR || var == DVM_REDISTRIBUTE_DIR)
            hasRealings = true;
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
                        if (tmp->variant() == IF_NODE || tmp->variant() == ELSEIF_NODE)
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

                int lastSize = next.size();
                for (auto& elem : bounds)
                    findNext(elem.first, elem.second, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);

                if (lastSize != next.size() && bounds.size() != 1)
                    break;

                st = st->lastNodeOfStmt();
            }
            else if (var == FOR_NODE || var == WHILE_NODE)
            {
                findNext(st->lexNext(), st->lastNodeOfStmt(), next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);
                st = st->lastNodeOfStmt();
            }
            else if (var == GOTO_NODE)
            {
                SgGotoStmt* gotoS = (SgGotoStmt*)st;
                int labNum = gotoS->branchLabel()->thelabel->stateno;
                auto nextStart = labeledStmts[labNum];

                SgStatement* last = getLast(nextStart, st, end);
                findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);

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
                    findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);
                }
                break;
            }
            else if (var == CONTROL_END)
            {
                auto cp = st->controlParent();
                if (cp->variant() == FOR_NODE || cp->variant() == WHILE_NODE)
                {
                    SgStatement* tmpSt = NULL;
                    if (currDir->type != FUNCTION_CALL)
                        tmpSt = ((SgStatement*)currDir->info);
                    else
                        tmpSt = SgStatement::getStatementByFileAndLine(currDir->location.first->fileName, currDir->location.second);
                    checkNull(tmpSt, convertFileName(__FILE__).c_str(), __LINE__);
                    if (tmpSt->controlParent() == cp)
                        findNext(cp->lexNext(), st, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);
                }
            }
            else if (var == ASSIGN_STAT)
            {
                if (st->expr(0)->variant() == ARRAY_REF)
                {
                    auto s = st->expr(0)->symbol();
                    DIST::Array* inPar = getArrayFromDeclarated(declaratedInStmt(s), s->identifier());
                    if (inPar)
                        addRealArraysRef(writesTo, { inPar }, arrayLinksByFuncCalls);
                }
            }
            else if (var == LOGIF_NODE)
            {
                findNext(st->lexNext(), st->lexNext()->lexNext(), next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);
                st = st->lastNodeOfStmt();
            }
            else if (var == ARITHIF_NODE)
            {
                SgArithIfStmt* arith = (SgArithIfStmt*)st;
                for (int i = 0; i < 2; ++i)
                {
                    auto nextStart = labeledStmts[((SgLabelRefExp*)(arith->label(i)))->label()->thelabel->stateno];
                    SgStatement* last = getLast(nextStart, st, end);
                    findNext(nextStart, last, next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);
                }
                break;
            }            
            else if (var == SWITCH_NODE)
            {
                SgSwitchStmt *sw = (SgSwitchStmt*)st;
                int tmp = sw->numberOfCaseOptions();
                vector<SgStatement*> cases;
                for (int z = 0; z < sw->numberOfCaseOptions(); ++z)
                    cases.push_back(sw->caseOption(z));
                auto defaultOp = sw->defOption();
                if (defaultOp)
                    cases.push_back(defaultOp);
                st = st->lastNodeOfStmt();
                cases.push_back(st);
                int lastSize = next.size();
                for (int z = 0; z < cases.size() - 1; ++z)
                    findNext(cases[z]->lexNext(), cases[z + 1], next, allShadowNodes, currDir, labeledStmts, writesTo, arrayLinksByFuncCalls, mapFuncs, hasRealings);
                if (lastSize != next.size())
                    break;
            }
            else if (var == PROC_STAT)
            {
                if (isIntrinsicFunctionName(st->symbol()->identifier()) == false)
                {
                    if (allShadowNodes.find(st) != allShadowNodes.end())
                    {
                        next.push_back(NextNode(allShadowNodes.find(st)->second, writesTo, hasRealings));
                        break;
                    }                    
                }
            }
            else if (var == STOP_STAT || var == RETURN_STAT)
            {
                if (allShadowNodes.find(st) != allShadowNodes.end())
                {
                    next.push_back(NextNode(allShadowNodes.find(st)->second, writesTo, hasRealings));
                    break;
                }
            }
            else if (var == CONTAINS_STMT)
            {
                st = st->controlParent()->lastNodeOfStmt();
                break;
            }
            else if (var == CASE_NODE || var == DEFAULT_NODE || var == ELSEIF_NODE)
            {
                if (var == ELSEIF_NODE)
                {
                    auto cp = st->controlParent();
                    while (cp->variant() != CONTROL_END)
                        cp = cp->lastNodeOfStmt();
                    st = cp;
                }
                else
                    st = st->controlParent()->lastNodeOfStmt();
            }

            //TODO: need to check
            int lastSize = next.size();
            //find func calls
            for (int z = 0; z < 3; ++z)
                findFuncCalls(st->expr(z), next, allShadowNodes, writesTo);

            if (lastSize != next.size())
                break;
        }
    }

    if (st->variant() == CONTROL_END)
        if (allShadowNodes.find(st) != allShadowNodes.end())
            next.push_back(NextNode(allShadowNodes.find(st)->second, writesTo, hasRealings));
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

static vector<PrevNode> getPrev(ShadowNode* curr, const set<ShadowNode*> allNodes)
{
    vector<PrevNode> retVal;

    for (auto& node : allNodes)
        for (auto& next : node->next)
            if (next.shNode == curr)
                retVal.push_back(PrevNode(node, &next.isBackWard, &next.hasRealigns));

    return retVal;
}

static vector<PrevNode> getPrev(ShadowNode* curr, const map<string, vector<FuncInfo*>>& allFuncs)
{
    vector<PrevNode> retVal;

    for (auto& funcByFile : allFuncs)
        for (auto& currF : funcByFile.second)
            for (auto& node : currF->allShadowNodes)
                    for (auto& next : node.second->next)
                        if (next.shNode == curr)
                            retVal.push_back(PrevNode(node.second, &next.isBackWard, &next.hasRealigns));
    
    return retVal;
}

extern int keepFiles;
static int groupingShadowNodes(set<ShadowNode*>& allShadowNodes, const map<string, vector<FuncInfo*>>& allFuncs,
                               const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls)
{    
    int moveCount = 0;
    bool changes = true;
    while (changes)
    {
        //printf("iter\n");
        changes = false;
        for (auto& shadow : allShadowNodes)
        {
            ShadowNode* currNode = shadow;
            if (currNode->type != PARALLEL_DIR)
                continue;

            vector<set<DIST::Array*>> writes;
            auto prevForCurr = getPrev(currNode, allFuncs);
            for (auto& prev : prevForCurr)
            {
                for (int i = 0; i < prev.shNode->next.size(); ++i)
                {
                    if (prev.shNode->next[i].shNode == currNode)
                    {
                        writes.push_back(prev.shNode->next[i].writeTo);
                        break;
                    }
                }
            }
            if (writes.size() != prevForCurr.size())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            set<DIST::Array*> totalWrites;
            for (auto& wr : writes)
                for (auto& array : wr)
                    totalWrites.insert(array);

            map<DIST::Array*, vector<ShadowElement>> rewriteSh;
            for (auto& sh : currNode->newShadows)
            {
                bool checkOK = true;
                set<DIST::Array*> allRefs;
                getRealArrayRefs(sh.first, sh.first, allRefs, arrayLinksByFuncCalls);

                for (auto& array : totalWrites)
                    if (allRefs.find(array) != allRefs.end())
                        checkOK = false;

                if (checkOK)
                {
                    bool isMoved = false;
                    for (auto& prev : prevForCurr)
                    {
                        //dont move back
                        if ((prev.isBackWard && *prev.isBackWard) || 
                            (prev.hasRealigns && *prev.hasRealigns) ||
                            (prev.shNode->type == START) ||
                            sh.first->GetLocation().first == DIST::l_PARAMETER && currNode->location.first != prev.shNode->location.first)
                        {
                            continue;
                        }
                        isMoved = true;
                        prev.shNode->MoveShadow(sh);
                        //printf("move from %d to %d %s\n", currNode->location.second, prev.shNode->location.second, sh.first->GetName().c_str());

                        changes = true;
                        ++moveCount;
                    }

                    if (!isMoved)
                        rewriteSh[sh.first] = sh.second;
                }
                else
                {
                    //printf(" **add to re ELSE (%d)\n", currNode->location.second);
                    rewriteSh[sh.first] = sh.second;
                }
            }
            currNode->newShadows = rewriteSh;
            //if (rewriteSh.size())
            //    printf("set to sh %d - newSh %d\n", currNode->location.second, rewriteSh.size());
        }

        /*for (auto& sh : allShadowNodes)
        {
            if (sh->newShadows.size())
                printf("sh %d has %d newSh\n", sh->location.second, sh->newShadows.size());
        }*/
    }

    if (moveCount)
        for (auto& shadow : allShadowNodes)
            shadow->MergeNewShadowElements();

    return moveCount;
}

static void detectBackWard(ShadowNode* node, set<ShadowNode*> visited, set<ShadowNode*>& allVisited)
{    
    while (node)
    {
        allVisited.insert(node);
        visited.insert(node);
        if (node->next.size() == 0)
            break;

        if (node->next.size() == 1)
        {
            if (visited.find(node->next[0].shNode) != visited.end())
            {
                node->next[0].isBackWard = true;
                break;
            }
            else
                node = node->next[0].shNode;
        }
        else
        {
            for (auto& nodesNext : node->next)
            {
                ShadowNode* next = nodesNext.shNode;
                if (visited.find(next) != visited.end())
                    nodesNext.isBackWard = true;
                else
                {
                    auto visNext = visited;
                    visNext.insert(next);
                    detectBackWard(next, visNext, allVisited);
                }
            }
            break;
        }
    }
}

static void replacingShadowNodes(FuncInfo* currF)
{
    for (auto& shadow : currF->allShadowNodes)
    {
        SgStatement* parallelDir = (SgStatement*)shadow.first;
        if (shadow.second->newShadows != shadow.second->shadows &&
            parallelDir->variant() == DVM_PARALLEL_ON_DIR)
        {
            int inserted = 0;
            auto expr = new SgExpression(EXPR_LIST);
            auto p = expr;
            for (auto& currSh : shadow.second->newShadows)
            {
                DIST::Array* currArray = currSh.first;
                if (currSh.second.size() == 0)
                    continue;

                const ShadowElement& currElement = currSh.second[0];

                if (inserted != 0)
                    p = createAndSetNext(RIGHT, EXPR_LIST, p);
                else if (inserted == 0)
                {
                    p = createAndSetNext(LEFT, SHADOW_RENEW_OP, p);
                    p = createAndSetNext(LEFT, EXPR_LIST, p);
                }

                SgSymbol* s = currArray->GetDeclSymbol()->GetOriginal();

                auto itTmp = currElement.origNameByProc.find(currF);
                if (itTmp == currElement.origNameByProc.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                const string nameInProc = itTmp->second;

                SgArrayRefExp* newArrayRef = NULL;
                if (nameInProc == s->identifier())
                    newArrayRef = new SgArrayRefExp(*s);
                else
                    newArrayRef = new SgArrayRefExp(*findSymbolOrCreate(current_file, nameInProc));
                newArrayRef->addAttribute(ARRAY_REF, currArray, sizeof(DIST::Array));

                auto zeroShifts = currElement.bounds;
                std::fill(zeroShifts.begin(), zeroShifts.end(), make_pair(0, 0));

                for (auto& elem : genSubscripts(currElement.bounds, zeroShifts))
                    newArrayRef->addSubscript(*elem);

                if (currElement.corner)
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

            SgExpression* dirExp = parallelDir->expr(1);
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
                    SgExpression* dirExp = parallelDir->expr(1);
                    SgExpression* tmp = new SgExpression(EXPR_LIST);
                    tmp->setLhs(expr->lhs());
                    tmp->setRhs(dirExp);
                    dirExp = tmp;

                    parallelDir->setExpression(1, *dirExp);
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
                parallelDir->setExpression(1, *makeExprList(newList));
            }
        }
    }
}

static void fillShadowAcrossFromParallel(FuncInfo* currF, ShadowNode* newShNode, SgStatement* st, const DIST::Arrays<int>& allArrays)
{
    vector<pair<pair<string, string>, vector<pair<int, int>>>> shadows;
    set<string> corners;

    fillShadowAcrossFromParallel(SHADOW_RENEW_OP, new Statement(st), shadows, corners);

    for (auto& shadow : shadows)
    {
        DIST::Array* array = allArrays.GetArrayByName(shadow.first.second);
        
        string nameInFunc = shadow.first.first;
        auto isCorner = (corners.find(nameInFunc) != corners.end());
        newShNode->shadows[array].push_back(ShadowElement(shadow.second, make_pair(currF, nameInFunc), isCorner));
    }
}

static string getNodeName(ShadowNode* node, const map<FuncInfo*, int>& keyOfFunc)
{
    int var = -1;
    string symb = "";
    if (node->type != FUNCTION_CALL)
    {
        auto st = ((SgStatement*)node->info);
        if (!st->switchToFile())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        var = st->variant();
        if (st->symbol())
            symb = nameWithContains(st, st->symbol());
    }
    else
    {
        auto ex = ((SgExpression*)node->info);
        if (SgFile::switchToFile(node->location.first->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        var = ex->variant();
        if (ex->symbol())
            symb = nameWithContains(SgStatement::getStatmentByExpression(ex), ex->symbol());
    }

    string ret = "F" + std::to_string(keyOfFunc.find(node->location.first)->second);
    if (node->type == START)
        ret += "_START";
    else if (node->type == PROCEDURE_CALL)
        ret += string("_call_") + symb;
    else if (node->type == FUNCTION_CALL)
        ret += string("_func_call_") + symb;
    else if (node->type == STOP)
        ret += "_STOP";
    else if (node->type == RETURN)
        ret += "_RETURN";
    else if (node->type == END)
        ret += "_END";
    else if (node->type != PARALLEL_DIR)
        ret += "_ERROR";

    ret += "_" + std::to_string(node->location.second);
    return ret;
}

static string getArrays(const NextNode& next)
{
    string ret = "(";
    for (auto& elem : next.writeTo)
        ret += elem->GetShortName() + ",";
    if (ret[ret.size() - 1] == ',')
        ret[ret.size() - 1] = ')';
    else
        ret += ")";
    return ret == "()" ? "" : ret;
}

static string buildGraphVizNext(FuncInfo* currF, const map<FuncInfo*, int>& keyOfFunc, set<string>& nodes)
{
    string graph = "";

    vector<string> lines;
    for (auto& elem : currF->allShadowNodes)
    {
        string curr = getNodeName(elem.second, keyOfFunc);
        nodes.insert(curr);
        for (auto& next : elem.second->next)
        {
            string nextNode = getNodeName(next.shNode, keyOfFunc);
            if (next.shNode->location.first == elem.second->location.first)
                nodes.insert(nextNode);
            string line = "\"" + curr + "\"->\"" + getNodeName(next.shNode, keyOfFunc) + "\"";
            string label = getArrays(next);

            line += "[";
            if (next.isBackWard)
                line += "color=red,penwidth=3.0,";
            if (next.hasRealigns)
                line += "style=dotted,";            
            line += "label=\"" + label + "\"]";

            line += "\n";
            lines.push_back(line);
        }
    }

    for (auto& line : lines)
        graph += line;
    return graph;
}

static string buildGraphVizPrev(FuncInfo* currF, const map<FuncInfo*, int>& keyOfFunc, const map<string, vector<FuncInfo*>>& allFuncs)
{
    string graph = "";

    vector<string> lines;
    for (auto& elem : currF->allShadowNodes)
    {
        string curr = getNodeName(elem.second, keyOfFunc);
        auto prevList = getPrev(elem.second, allFuncs);
        for (auto& prev : prevList)
        {
            string nextPrev = getNodeName(prev.shNode, keyOfFunc);
            string line = "\"" + curr + "\"->" + "\"" + getNodeName(prev.shNode, keyOfFunc) + "\"";
            line += "[color=green,penwidth=0.5]\n";
            lines.push_back(line);
        }
    }

    for (auto& line : lines)
        graph += line;
    return graph;
}

static void buildGraphViz(const map<string, vector<FuncInfo*>>& allFuncs, string fileOut = "", bool withPrev = false)
{
    string graph = "digraph G{\n";
    map<FuncInfo*, int> keyOfFunc;
    int key = 0;
    for (auto& funcByFile : allFuncs)
        for (auto& currF : funcByFile.second)
            keyOfFunc[currF] = key++;

    for (auto& funcByFile : allFuncs)
    {
        for (auto& currF : funcByFile.second)
        {
            set<string> nodes;
            string lines = buildGraphVizNext(currF, keyOfFunc, nodes);
            if (nodes.size())
            {
                graph += lines;
                graph += "subgraph \"cluster_" + currF->funcName + ":" + currF->fileName + "\"{\n";
                for (auto& node : nodes)
                    graph += "\"" + node + "\"\n";
                graph += "label=\"" + currF->funcName + ":" + currF->fileName + "\"\n";
                graph += "}\n";
            }
            if (withPrev)
                graph += buildGraphVizPrev(currF, keyOfFunc, allFuncs);

        }
    }
    graph += "}\n";

    FILE* f = NULL;
    
    if (fileOut == "") 
        f = fopen("_shadowNodes.txt", "w");
    else
        f = fopen(fileOut.c_str(), "w");

    if (f == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    fwrite(graph.c_str(), sizeof(char), graph.size(), f);
    fclose(f);
}

static void removeNode(ShadowNode* node, const map<string, vector<FuncInfo*>>& allFuncs)
{
    for (auto& prev : getPrev(node, allFuncs))
    {
        for (auto& needed : prev.shNode->next)
        {
            if (needed.shNode == node)
            {
                vector<NextNode> newEdges;
                for (auto& next : node->next)
                {
                    NextNode tmp = needed;
                    tmp.isBackWard |= next.isBackWard;
                    tmp.hasRealigns |= next.hasRealigns;
                    tmp.writeTo.insert(next.writeTo.begin(), next.writeTo.end());
                    tmp.shNode = next.shNode;

                    newEdges.push_back(tmp);
                }

                if (newEdges.size())
                {
                    needed = newEdges[0];
                    for (int z = 1; z < newEdges.size(); ++z)
                        prev.shNode->next.push_back(newEdges[z]);
                }
                break;
            }
        }
    }

    /*for (auto& next : node->next)
    {
        for (auto& needed : next.shNode->prev)
        {
            if (needed.shNode == node)
            {
                vector<PrevNode> newEdges = node->prev;
                if (newEdges.size())
                {
                    needed = newEdges[0];
                    for (int z = 1; z < newEdges.size(); ++z)
                        next.shNode->prev.push_back(newEdges[z]);
                }
                break;
            }
        }
    }*/
}

static void removeStartEnd(ShadowNode* node, FuncInfo* currF, const map<string, vector<FuncInfo*>>& allFuncs)
{
    removeNode(node, allFuncs);
    for (auto& elem : currF->allShadowNodes)
    {
        if (elem.second == node)
        {
            currF->allShadowNodes.erase(elem.first);
            break;
        }
    }
}

static void removeStartEnd(const map<string, vector<FuncInfo*>>& allFuncs)
{
    set<ShadowNode*> toDel;
    for (auto& funcByFile : allFuncs)
    {
        for (auto& currF : funcByFile.second)
        {
            auto nodeS = currF->shadowTreeStart;
            auto nodeE = currF->shadowTreeEnd;

            if (nodeS && getPrev(nodeS, allFuncs).size())
            {
                removeStartEnd(nodeS, currF, allFuncs);
                toDel.insert(currF->shadowTreeStart);
                currF->shadowTreeStart = NULL;
            }

            if (nodeE && nodeE->next.size())
            {
                removeStartEnd(nodeE, currF, allFuncs);
                toDel.insert(currF->shadowTreeEnd);
                currF->shadowTreeEnd = NULL;
            }
        }
    }

    for (auto& del : toDel)
        delete del;
}

static void removeStopStats(const map<string, vector<FuncInfo*>>& allFuncs)
{
    for (auto& funcByFile : allFuncs)
    {
        for (auto& currF : funcByFile.second)
        {
            map<void*, ShadowNode*> newNodes;
            set<ShadowNode*> toDel;
            for (auto& elem : currF->allShadowNodes)
            {
                ShadowNode* node = elem.second;
                if (node->type == STOP || node->type == RETURN)
                {
                    toDel.insert(node);
                    removeNode(node, allFuncs);
                }
                else
                    newNodes[elem.first] = elem.second;
            }

            if (toDel.size())
                currF->allShadowNodes = newNodes;
            for (auto& del : toDel)
                delete del;
        }
    }
}

static void setPrevNodes(FuncInfo* currF)
{
    /*for (auto& elem : currF->allShadowNodes)
        for (auto& next : elem.second->next)
            next.shNode->prev.push_back(PrevNode(elem.second, next.isBackWard, next.hasRealigns)); */
}

static void removeUnusedEdges(const map<string, vector<FuncInfo*>>& allFuncs)
{
    //remove loops
    for (auto& funcByFile : allFuncs)
    {
        for (auto& currF : funcByFile.second)
        {
            for (auto& elem : currF->allShadowNodes)
            {
                ShadowNode* node = elem.second;
                vector<NextNode> newNext;
                set<DIST::Array*> writesToTheSame;
                bool hasTheSame = false;
                for (auto& next : node->next)
                {
                    if (next.shNode == node)
                    {
                        hasTheSame = true;
                        writesToTheSame.insert(next.writeTo.begin(), next.writeTo.end());
                    }
                }

                for (auto& next : node->next)
                {
                    if (next.shNode != node)
                    {
                        newNext.push_back(next);
                        newNext.back().writeTo.insert(writesToTheSame.begin(), writesToTheSame.end());
                    }
                }

                if (hasTheSame)
                {
                    node->next = newNext;
                    /*vector<PrevNode> newPrev;
                    for (auto& prev : node->prev)
                        if (prev.shNode != node)
                            newPrev.push_back(prev);

                    if (node->prev.size() == newPrev.size())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    node->prev = newPrev;*/
                }
            }
        }
    }

    //remove same edges
    bool changed = false;
    for (auto& funcByFile : allFuncs)
    {
        for (auto& currF : funcByFile.second)
        {
            for (auto& elem : currF->allShadowNodes)
            {
                ShadowNode* node = elem.second;
                
                map<ShadowNode*, NextNode> newNext;
                for (auto& next : node->next)
                {
                    auto it = newNext.find(next.shNode);
                    if (it == newNext.end())
                        newNext[next.shNode] = next;
                    else
                        it->second.writeTo.insert(next.writeTo.begin(), next.writeTo.end());
                }

                if (newNext.size() != node->next.size())
                {
                    changed = true;
                    node->next.clear();
                    for (auto& elem : newNext)
                        node->next.push_back(elem.second);
                }
            }
        }
    }

    /*if (changed)
    {
        for (auto& funcByFile : allFuncs)
            for (auto& currF : funcByFile.second)
                for (auto& node : currF->allShadowNodes)
                    node.second->prev.clear();

        for (auto& funcByFile : allFuncs)
            for (auto& currF : funcByFile.second)
                setPrevNodes(currF);
    }*/
}

static bool isFunctionEmpty(FuncInfo* func)
{
    if (func->shadowTreeStart->next.size() == 1 && 
        func->shadowTreeStart->next[0].shNode == func->shadowTreeEnd)
        return true;
    else
        return false;
}

static void replaceCalls(const map<string, vector<FuncInfo*>>& allFuncs, const map<string, FuncInfo*>& mapF)
{
    for (auto& funcByFile : allFuncs)
    {
        if (SgFile::switchToFile(funcByFile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& currF : funcByFile.second)
        {
            map<void*, ShadowNode*> newNodes;
            set<ShadowNode*> toDel;
            for (auto& node : currF->allShadowNodes)
            {
                if (node.second->type == PROCEDURE_CALL || node.second->type == FUNCTION_CALL)
                {
                    string callName = "no";
                    if (node.second->type == PROCEDURE_CALL)
                    {
                        auto st = ((SgStatement*)node.second->info);
                        callName = nameWithContains(st, st->symbol());
                    }
                    else
                    {
                        auto ex = ((SgExpression*)node.second->info);
                        callName = nameWithContains(SgStatement::getStatmentByExpression(ex) ,ex->symbol());
                    }

                    auto it = mapF.find(callName);
                    if (it != mapF.end() && it->second->shadowTreeStart && it->second->shadowTreeEnd)
                    {
                        if (!isFunctionEmpty(it->second))
                        {
                            //for (auto& prev : node.second->prev)
                            //    it->second->shadowTreeStart->prev.push_back(prev);
                            for (auto& prev : getPrev(node.second, allFuncs))
                                for (auto& next : prev.shNode->next)
                                    if (next.shNode == node.second)
                                        next.shNode = it->second->shadowTreeStart;
                            //node.second->prev.clear();

                            for (auto& realNext : node.second->next)
                                it->second->shadowTreeEnd->next.push_back(realNext);
                            /*for (auto& realNext : node.second->next)
                                for (auto& prev : realNext.shNode->prev)
                                    if (prev.shNode == node.second)
                                        prev.shNode = it->second->shadowTreeEnd;*/
                            node.second->next.clear();
                        }
                        else
                        {
                            for (auto& elem : node.second->next)
                                elem.writeTo.insert(it->second->shadowTreeStart->next[0].writeTo.begin(), it->second->shadowTreeStart->next[0].writeTo.end());
                            removeNode(node.second, allFuncs);
                        }
                        toDel.insert(node.second);
                    }
                    else
                        newNodes.insert(node);
                }
                else
                    newNodes.insert(node);
            }
            currF->allShadowNodes = newNodes;
            for (auto& del : toDel)
                delete del;
        }
    }
}

static void findFuncCalls(SgStatement* currSt, SgExpression* ex, FuncInfo* currF, const map<string, FuncInfo*>& mapF, const int line)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            if (isIntrinsicFunctionName(ex->symbol()->identifier()) == false)
            {
                if (mapF.find(nameWithContains(currSt, ex->symbol())) != mapF.end())
                    currF->allShadowNodes[ex] = new ShadowNode(ex, FUNCTION_CALL, currF, line);
            }
        }

        findFuncCalls(currSt, ex->lhs(), currF, mapF, line);
        findFuncCalls(currSt, ex->rhs(), currF, mapF, line);
    }
}

static GraphsKeeper *graphsKeeper;
void GroupShadow(const map<string, vector<FuncInfo*>>& allFuncs, 
                 const map<string, vector<LoopGraph*>>& loops, 
                 const DIST::Arrays<int>& allArrays,
                 const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCalls)
{
    GraphsKeeper *gk = GraphsKeeper::getGraphsKeeper();

    map<string, FuncInfo*> mapF;
    for (auto& byFile : allFuncs)
        for (auto &elem : byFile.second)
                mapF[elem->funcName] = elem;

    bool deb = false;
    bool withPrev = false;

    /*for (auto& funcByFile : allFuncs)
    {
        if (SgFile::switchToFile(funcByFile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& currF : funcByFile.second)
        {
            if (currF->isMain && deb)
            {
                SgStatement* func = currF->funcPointer->GetOriginal();
                
                GraphItem* gItem = new GraphItem();
                SetUpVars(&gItem->commons, &gItem->calls, gItem->calls.AddHeader(func, false, func->symbol(), current_file_id), &gItem->dldl);

                gItem->CGraph = GetControlFlowGraphWithCalls(true, func, &gItem->calls, &gItem->commons);
                gItem->calls.AssociateGraphWithHeader(func, gItem->CGraph);
                gItem->commons.MarkEndOfCommon(GetCurrentProcedure());
                gItem->file_id = current_file_id;

                ControlFlowGraph* CGraph = gItem->CGraph;
                printf("%s\n", CGraph->GetVisualGraph(&gItem->calls).c_str());
                //viewGraph(CGraph->getFirst());
            }
        }
    }*/

    //building shadow graph
    for (auto& funcByFile : allFuncs)    
    {
        map<int, LoopGraph*> mapLoops;
        auto itL = loops.find(funcByFile.first);
        if (itL != loops.end())
            createMapLoopGraph(itL->second, mapLoops);

        if (SgFile::switchToFile(funcByFile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& currF : funcByFile.second)
        {
            SgStatement* func = currF->funcPointer->GetOriginal();

            //find all labled statements
            map<int, SgStatement*> labeledStmts;
            for (auto st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
                if (st->label())
                    labeledStmts[st->label()->thelabel->stateno] = st;

            //start node
            currF->shadowTreeStart = currF->allShadowNodes[func] = new ShadowNode(func, START, currF, func->lineNumber());

            //find all NODES
            for (SgStatement* st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
            {
                if (st->variant() == DVM_PARALLEL_ON_DIR)
                {
                    auto newShNode = new ShadowNode(st, PARALLEL_DIR, currF, st->lexNext()->lineNumber());
                    currF->allShadowNodes[st] = newShNode;

                    fillShadowAcrossFromParallel(currF, newShNode, st, allArrays);

                    st = st->lexNext();
                    if (st->variant() != FOR_NODE)
                    {
                        if (st->variant() != ASSIGN_STAT)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        else
                        {
                            bool found = false;
                            for (auto& data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ ASSIGN_STAT }))
                            {
                                if (mapLoops.find(data->lineNumber()) != mapLoops.end())
                                    found = true;
                            }

                            if (!found)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                    }
                    st = st->lastNodeOfStmt();
                }
                else if (st->variant() == CONTAINS_STMT)
                    break;
                else if (st->variant() == STOP_STAT || st->variant() == RETURN_STAT) // end nodes
                    currF->allShadowNodes[st] = new ShadowNode(st, st->variant() == STOP_STAT ? STOP : RETURN, currF, st->lineNumber());
                else if (st->variant() == PROC_STAT)
                {
                    if (isIntrinsicFunctionName(st->symbol()->identifier()) == false)
                        if (mapF.find(nameWithContains(st, st->symbol())) != mapF.end())
                            currF->allShadowNodes[st] = new ShadowNode(st, PROCEDURE_CALL, currF, st->lineNumber());
                }
                else
                {
                    for (int z = 0; z < 3; ++z)
                        findFuncCalls(st, st->expr(z), currF, mapF, st->lineNumber());
                }
            }

            auto lastNode = func->lastNodeOfStmt(); // end node
            auto natureLast = currF->allShadowNodes[lastNode] = new ShadowNode(lastNode, END, currF, lastNode->lineNumber());
            currF->shadowTreeEnd = natureLast;

            if (currF->allShadowNodes.size() <= 1)
                continue;

            // set next
            for (auto& node : currF->allShadowNodes)
            {
                set<DIST::Array*> writesTo;
                auto dir = (SgStatement*)node.first;
                auto type = node.second->type;
                if (type == PARALLEL_DIR)
                {
                    dir = dir->lexNext();
                    SgForStmt* start = isSgForStmt(dir);
                    SgStatement* lastNode = NULL;
                    if (start == NULL && dir->variant() == ASSIGN_STAT)
                    {
                        for (auto& data : getAttributes<SgStatement*, SgStatement*>(dir, set<int>{ ASSIGN_STAT }))
                        {
                            if (mapLoops.find(data->lineNumber()) != mapLoops.end() && data->localLineNumber() == dir->lineNumber())
                            {
                                start = isSgForStmt(data);
                                lastNode = dir->lastNodeOfStmt();
                                break;
                            }
                        }
                    }
                    else if (start)
                        lastNode = start->lastNodeOfStmt();

                    checkNull(start, convertFileName(__FILE__).c_str(), __LINE__);
                    auto itLoop = mapLoops.find(start->lineNumber());
                    if (itLoop == mapLoops.end())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    addRealArraysRef(writesTo, itLoop->second->usedArraysWrite, arrayLinksByFuncCalls);

                    checkNull(lastNode, convertFileName(__FILE__).c_str(), __LINE__);
                    dir = lastNode;
                }
                else if (type == STOP || type == RETURN || type == END)
                {
                    if (type == STOP || type == RETURN)
                        node.second->next.push_back(NextNode(natureLast, writesTo));
                    continue;
                }
                else if (type == FUNCTION_CALL)
                {
                    dir = SgStatement::getStatementByFileAndLine(currF->fileName, node.second->location.second);
                    checkNull(dir, convertFileName(__FILE__).c_str(), __LINE__);
                }

                //TODO: may be replace to GraphKeeper
                findNext(nextWithSkipElse(dir), func->lastNodeOfStmt(), node.second->next, currF->allShadowNodes, node.second, labeledStmts, writesTo, arrayLinksByFuncCalls, mapF, false);
            }

            //remove the same nodes
            for (auto& elem : currF->allShadowNodes)
            {
                set<pair<ShadowNode*, set<DIST::Array*>>> tmpl;
                for (auto& listElem : elem.second->next)
                    tmpl.insert(make_pair(listElem.shNode, listElem.writeTo));
                if (tmpl.size() != elem.second->next.size())
                {
                    elem.second->next.clear();
                    for (auto& uniq : tmpl)
                        elem.second->next.push_back(NextNode(uniq.first, uniq.second));
                }
            }
            //setPrevNodes(currF);
        }
    }

    if (deb)
        buildGraphViz(allFuncs, "_sh0.txt", withPrev);

    removeStopStats(allFuncs);
    removeUnusedEdges(allFuncs);
    if (deb)
        buildGraphViz(allFuncs, "_sh1.txt", withPrev);

    replaceCalls(allFuncs, mapF);
    removeUnusedEdges(allFuncs);
    if (deb)
        buildGraphViz(allFuncs, "_sh2.txt", withPrev);

    removeStartEnd(allFuncs);
    removeUnusedEdges(allFuncs);
    if (deb)
        buildGraphViz(allFuncs, "_sh3.txt", withPrev);

    set<ShadowNode*> allNodes;
    //detect backward
    for (auto& funcByFile : allFuncs)
        for (auto& currF : funcByFile.second)
            for (auto& elem : currF->allShadowNodes)
                allNodes.insert(elem.second);
    
    set<ShadowNode*> visited;
    while (visited.size() != allNodes.size())
    {
        ShadowNode* next = NULL;
        for (auto& elem : allNodes)
        {
            if (visited.find(elem) == visited.end())
            {
                //if (elem->prev.size() == 0)
                if (getPrev(elem, allNodes).size() == 0)
                {
                    next = elem;
                    break;
                }
            }
        }
        if (next)
            detectBackWard(next, { }, visited);
    }
    
    if (deb)
        buildGraphViz(allFuncs, "_sh4.txt", withPrev);

    if (keepFiles)
        buildGraphViz(allFuncs);

    // grouping
    allNodes.clear();
    for (auto& funcByFile : allFuncs)
        for (auto& currF : funcByFile.second)
            for (auto& elem : currF->allShadowNodes)
                allNodes.insert(elem.second);

    map<FuncInfo*, int> moveCounts;
    for (auto& shadow : allNodes)
        shadow->newShadows = shadow->shadows;
    int moves = groupingShadowNodes(allNodes, allFuncs, arrayLinksByFuncCalls);
    __spf_print(1, "  shadow total moveCount %d\n", moves);

    if (moves != 0)
    {
        //replacing
        for (auto& funcByFile : allFuncs)
        {
            for (auto& currF : funcByFile.second)
            {
                if (currF->funcPointer->GetOriginal()->switchToFile() == false)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                replacingShadowNodes(currF);
            }
        }
    }
}