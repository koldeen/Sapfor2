#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <assert.h>

#include "dvm.h"
#include "loop_analyzer.h"
#include "../Utils/types.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "../Distribution/Arrays.h"
#include "../GraphCall/graph_calls.h"
#include "../GraphLoop/graph_loops_func.h"

using std::vector;
using std::pair;
using std::tuple;
using std::map;
using std::set;
using std::make_pair;
using std::make_tuple;
using std::get;
using std::string;
using std::wstring;

#define FIRST(x)  get<0>(x)
#define SECOND(x) get<1>(x)
#define THIRD(x)  get<2>(x)
#define DEB       0

static DIST::Array* GetArrayByShortName(const DIST::Arrays<int> &allArrays, SgSymbol *name)
{
    auto uniqKey = getFromUniqTable(name);
    string nameFromUniq = getShortName(uniqKey);
    return allArrays.GetArrayByName(nameFromUniq);
}

static bool findAllArraysForRemote(SgStatement *current, SgExpression *expr, const map<int, LoopGraph*> &sortedLoopGraph,
                                   vector<SgExpression*> &remotes, const DIST::Arrays<int> &allArrays, 
                                   const DataDirective &data, const vector<int> &currVar, const uint64_t regionID,
                                   const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    bool retVal = false;

    if (expr == NULL)
        return retVal;

    if (expr->variant() == ARRAY_REF && expr->symbol() && expr->symbol()->type()->variant() != T_STRING)
    {
        DIST::Array *currArray = GetArrayByShortName(allArrays, OriginalSymbol(expr->symbol()));

        set<DIST::Array*> realRefs;
        getRealArrayRefs(currArray, currArray, realRefs, arrayLinksByFuncCalls);

        for (auto array : realRefs)
        {
            if (array != NULL)
            {
                // find distributed dims
                DIST::Array *templ = array->GetTemplateArray(regionID);
                checkNull(templ, convertFileName(__FILE__).c_str(), __LINE__);
                auto links = array->GetLinksWithTemplate(regionID);

                bool needToAdd = false;
                for (int i = 0; i < data.distrRules.size(); ++i)
                {
                    if (data.distrRules[i].first == templ)
                    {
                        const vector<dist> &rule = data.distrRules[i].second[currVar[i]].distRule;
                        for (int k = 0; k < links.size(); ++k)
                        {
                            const int idx = links[k];
                            if (idx >= 0)
                            {
                                if (rule[idx] == BLOCK)
                                {
                                    needToAdd = true;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }

                //and add, if found any distributed dim
                if (needToAdd)
                {
                    remotes.push_back(expr->copyPtr());
                    retVal = true;
                    break;
                }
            }
        }
    }

    bool cond = true;
    if (expr->variant() == FUNC_CALL)
        cond = isIntrinsic(((SgFunctionCallExp*)expr)->funName()->identifier());

    if (cond) 
    {
        if (expr->lhs())
        {
            bool tmp = findAllArraysForRemote(current, expr->lhs(), sortedLoopGraph, remotes, allArrays, data, currVar, regionID, arrayLinksByFuncCalls);
            retVal = retVal || tmp;
        }
        if (expr->rhs())
        {
            bool tmp = findAllArraysForRemote(current, expr->rhs(), sortedLoopGraph, remotes, allArrays, data, currVar, regionID, arrayLinksByFuncCalls);
            retVal = retVal || tmp;
        }
    }
    return retVal;
}

static bool checkExpr(SgExpression *ex, const set<int>& noSimpleVars)
{
    bool retVal = true;
    if (ex == NULL)
        return true;

    const int var = ex->variant();
    if (noSimpleVars.find(var) != noSimpleVars.end())
        return false;

    if (ex->lhs())
        retVal = retVal && checkExpr(ex->lhs(), noSimpleVars);
    if (ex->rhs())
        retVal = retVal && checkExpr(ex->rhs(), noSimpleVars);

    return retVal;
}

static inline bool isSimpleRef(SgExpression *subs, const set<int> noSimpleVars)
{
    bool retVal = true;
    while (subs && retVal)
    {
        retVal = retVal && checkExpr(subs->lhs(), noSimpleVars);
        subs = subs->rhs();
    }

    return retVal;
}

static bool inline hasDirs(SgStatement *st, const int var)
{
    SgStatement *last = st->lastNodeOfStmt();
    for ( ;st != last; st = st->lexNext())
        if (st->variant() == var)
            return true;

    return false;
}

static bool isDistributed(SgSymbol *in)
{
    SgSymbol *s = OriginalSymbol(in);
    DIST::Array *decl = getArrayFromDeclarated(declaratedInStmt(s), s->identifier());
    if (!decl)
        return false;
    else
        return !(decl->GetNonDistributeFlag());
}

//TODO: need to add IPA (functions)
static void fillRead(SgExpression *ex, SgStatement *cp, SgStatement *st,
                     map<string, map<string, pair<set<SgStatement*>, set<SgStatement*>>>> &readArrays)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
            if (isDistributed(ex->symbol()))
            {
                readArrays[ex->symbol()->identifier()][string(ex->unparse())].first.insert(cp);
                readArrays[ex->symbol()->identifier()][string(ex->unparse())].second.insert(st);
            }

        fillRead(ex->lhs(), cp, st, readArrays);
        fillRead(ex->rhs(), cp, st, readArrays);
    }
}

bool isNeedToConvertIfCondition(SgExpression *ex)
{
    map<string, map<string, pair<set<SgStatement*>, set<SgStatement*>>>> readArrays;
    fillRead(ex, NULL, NULL, readArrays);
    return (readArrays.size() != 0);
}

static bool inline hasSpecialIfCond(SgStatement* stIn)
{
    if (stIn->variant() != IF_NODE)
        return false;

    auto ex = stIn->expr(0);
    if (!ex)
        return false;
    
    if (ex->variant() == NOT_OP)
    {
        ex = ex->lhs();
        if (ex->variant() == VAR_REF && !ex->lhs() && !ex->rhs())
        {
            if (string(ex->symbol()->identifier()).find("spf_If_C") != string::npos)
                return true;
        }
    }
    return false;
}

static bool inline hasAssignsToArray(SgStatement *stIn)
{
    // array -> unparse access -> pair [ control par, original stat]
    map<string, map<string, pair<set<SgStatement*>, set<SgStatement*>>>> arrayAccessWrite;
    map<string, map<string, pair<set<SgStatement*>, set<SgStatement*>>>> arrayAccessRead;
    
    SgStatement *last = stIn->lastNodeOfStmt();
    for (auto st = stIn; st != last; st = st->lexNext())
    {
        if (st->variant() == ASSIGN_STAT)
        {
            SgExpression *ex = st->expr(0);
            if (ex->variant() == ARRAY_REF)
            {
                SgSymbol *s = ex->symbol();
                if (isDistributed(s))
                {
                    arrayAccessWrite[s->identifier()][string(ex->unparse())].first.insert(st->controlParent());
                    arrayAccessWrite[s->identifier()][string(ex->unparse())].second.insert(st);
                }
            }
        }
    }

    for (auto st = stIn; st != last; st = st->lexNext())
    {
        SgStatement *cp = st->controlParent();
        if (st->variant() != ASSIGN_STAT)
        {
            for (int z = 0; z < 3; ++z)
                fillRead(st->expr(z), cp, st, arrayAccessRead);
        }
        else
        {
            for (int z = 1; z < 3; ++z)
                fillRead(st->expr(z), cp, st, arrayAccessRead);
            SgExpression *left = st->expr(0);
            fillRead(left->lhs(), cp, st, arrayAccessRead);
            fillRead(left->rhs(), cp, st, arrayAccessRead);
        }
    }

    for (auto &readPair : arrayAccessRead)
    {
        string arrayName = readPair.first;
        auto it = arrayAccessWrite.find(arrayName);

        //TODO: 
        if (it != arrayAccessWrite.end())
        {
            return true;
            /*for (auto &read : readPair.second)
            {
                auto mapW = it->second.find(read.first);

                if (mapW == it->second.end())
                    return true;
                else
                {
                    for (auto &cpW : mapW->second.first)
                    {
                        for (auto &cpR : read.second.first)
                            if (cpW != cpR && cpW->variant() == FOR_NODE)
                                return true;
                    }

                    for (auto &cpW : mapW->second.second)
                        if (read.second.second.find(cpW) == read.second.second.end())
                            return true;
                }
            }*/
        }
    }
    return false;
}

static void converToDDOT(SgExpression *spec)
{
    while (spec)
    {
        spec->setLhs(new SgExpression(DDOT));
        spec = spec->rhs();
    }
}

static void getAllSymbols(SgExpression *ex, set<string> &symbs)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF)
            symbs.insert(ex->symbol()->identifier());
        getAllSymbols(ex->lhs(), symbs);
        getAllSymbols(ex->rhs(), symbs);
    }
}

static bool ifRange(SgExpression* spec)
{
    while (spec)
    {
        if (spec->lhs()->variant() == DDOT)
        {
            if (!spec->lhs()->lhs() || !spec->lhs()->rhs())
                return true;
            if (string(spec->lhs()->lhs()->unparse()) != string(spec->lhs()->rhs()->unparse()))
                return true;
        }        
        spec = spec->rhs();
    }

    return false;
}

static bool isAlloc(SgStatement* st)
{
    return st->variant() == ALLOCATE_STMT || st->variant() == DEALLOCATE_STMT;
}

template<int NUM>
bool createRemoteDir(SgStatement *st, const map<int, LoopGraph*> &sortedLoopGraph, const DIST::Arrays<int> &allArrays, 
                     const DataDirective &data, const vector<int> &currVar, const uint64_t regionId, vector<Messages> &currMessages,
                     const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    //for parallel loops after vector assign convertion
    if (st->lexPrev()->variant() == DVM_PARALLEL_ON_DIR)
        return false;

    if (isAlloc(st))
        return false;
    if (st->variant() == LOGIF_NODE)
        if (((SgLogIfStmt*)st)->body())
            if (isAlloc(((SgLogIfStmt*)st)->body()))
                return false;

    vector<SgExpression*> remotes;
    string leftPartOfAssign = "";
    if (st->variant() == ASSIGN_STAT)
        leftPartOfAssign = string(st->expr(0)->unparse());

    if (findAllArraysForRemote(st, st->expr(NUM), sortedLoopGraph, remotes, allArrays, data, currVar, regionId, arrayLinksByFuncCalls))
    {
        SgStatement *remoteDir = new SgStatement(DVM_REMOTE_ACCESS_DIR);
        SgExpression *exprList = new SgExpression(EXPR_LIST);
        remoteDir->setExpression(0, *exprList);
        
        //exclude left part of assign: A(i,j,k) = A(i,j,k) + 5
        if (leftPartOfAssign != "")
        {
            int z = 0;
            while (z != remotes.size())
            {
                if (leftPartOfAssign == string(remotes[z]->unparse()))
                    remotes.erase(remotes.begin() + z);
                else
                    z++;
            }
        }

        vector<SgExpression*> allSubs;
        for (auto &rem : remotes)
            allSubs.push_back(rem->lhs());

        if (remotes.size() > 0)
        {
            //TODO: use CFG and RD analysis
            set<string> usedSymbols;
            for (auto &access : remotes)
                getAllSymbols(access, usedSymbols);

            SgStatement *toInsert = st;
            vector<SgStatement*> allToInsert = { toInsert };
            int lvlUp = 0;
            //find the uppest control parent
            do
            {
                SgStatement *parent = toInsert->controlParent();
                const int var = parent->variant();
                if (var == FUNC_HEDR || var == PROC_HEDR || var == PROG_HEDR ||
                    hasDirs(parent, DVM_PARALLEL_ON_DIR) || hasDirs(parent, DVM_REMOTE_ACCESS_DIR) || 
                    hasAssignsToArray(parent) ||
                    hasSpecialIfCond(parent))
                    break;
                toInsert = parent;
                allToInsert.push_back(toInsert);
                ++lvlUp;
            } while (1);
                        
            for (int idx = allToInsert.size() - 1; idx >= 0; --idx)
            {
                const int var = allToInsert[idx]->variant();
                if (var == ELSEIF_NODE)
                {
                    if (idx != 0)
                        toInsert = allToInsert[idx - 1];
                    else
                        break;
                }
                else
                    break;
                --lvlUp;
            }

            if (toInsert->variant() == FOR_NODE)
            {
                for (auto &elem : allSubs)
                {
                    const bool isSimple = isSimpleRef(elem, { ARRAY_OP, ARRAY_REF, VAR_REF });
                    if (!isSimple)
                        converToDDOT(elem);
                }
            }
            else
            {
                const int cpV = toInsert->controlParent()->variant(); 
                const int varI = toInsert->variant();
                //dont convert to a(:,:,:) before assign operators
                if (lvlUp == 0 &&
                    ((varI == ASSIGN_STAT) || (varI != FOR_NODE && (cpV == FUNC_HEDR || cpV == PROC_HEDR || cpV == PROG_HEDR))))
                {
                    for (auto& elem : allSubs)
                        if (ifRange(elem) || !isSimpleRef(elem, { ARRAY_OP, ARRAY_REF}))
                            converToDDOT(elem);
                }
                else 
                {
                    for (auto &elem : allSubs)
                        converToDDOT(elem);
                }
            }

            //create remote dir with uniq expressions
            set<string> exist;
            int add = 0;
            for (int z = 0; z < remotes.size(); ++z, ++add)
            {
                string currRem = remotes[z]->unparse();
                auto itR = exist.find(currRem);
                if (itR == exist.end())
                {
                    if (add != 0)
                    {
                        exprList->setRhs(new SgExpression(EXPR_LIST));
                        exprList = exprList->rhs();
                    }

                    exprList->setLhs(remotes[z]);
                    exist.insert(itR, currRem);
                }
            }
            exist.clear();

            SgStatement *prev = toInsert->lexPrev();
            if (prev)
            {
                if (prev->variant() != DVM_REMOTE_ACCESS_DIR)
                    toInsert->insertStmtBefore(*remoteDir, *toInsert->controlParent());
                else // aggregate this
                {
                    set<string> existsRemotes;
                    for (SgExpression *list = prev->expr(0); list; list = list->rhs())
                        existsRemotes.insert(list->lhs()->unparse());
                    
                    SgExpression *list = prev->expr(0);
                    for (auto &rem : remotes)
                    {
                        const string curr = rem->unparse();
                        auto exist = existsRemotes.find(curr);
                        if (exist == existsRemotes.end())
                        {
                            existsRemotes.insert(exist, curr);
                            SgExpression *newList = new SgExpression(EXPR_LIST);
                            newList->setLhs(rem);
                            newList->setRhs(list);

                            list = newList;
                        }
                    }
                    prev->setExpression(0, *list);
                }
            }
            else
                toInsert->insertStmtBefore(*remoteDir, *toInsert->controlParent());
        }
        return true;
    }
    return false;
}

template bool createRemoteDir<0>(SgStatement*, const map<int, LoopGraph*>&, const DIST::Arrays<int>&, const DataDirective&, const vector<int>&, const uint64_t, vector<Messages>&, const map<DIST::Array*, set<DIST::Array*>>&);
template bool createRemoteDir<1>(SgStatement*, const map<int, LoopGraph*>&, const DIST::Arrays<int>&, const DataDirective&, const vector<int>&, const uint64_t, vector<Messages>&, const map<DIST::Array*, set<DIST::Array*>>&);

static inline bool isArrayRefHasDifferentVars(SgExpression *ex, set<string> &vars)
{
    bool retVal = true;
    if (ex == NULL)
        return true;

    const int var = ex->variant();
    if (var == VAR_REF)
    {
        string newVar = string(ex->symbol()->identifier());
        if (vars.find(newVar) != vars.end())
            return false;
        vars.insert(newVar);
    }

    if (ex->lhs())
        retVal = retVal && isArrayRefHasDifferentVars(ex->lhs(), vars);
    if (ex->rhs())
        retVal = retVal && isArrayRefHasDifferentVars(ex->rhs(), vars);
    return retVal;
}

static inline void addRemoteLink(SgArrayRefExp *expr, map<string, SgArrayRefExp*> &uniqRemotes, const set<string>& remotesInParallel,
                                 set<SgArrayRefExp*> &addedRemotes, vector<Messages> &messages, const int line, bool withConv = true)
{
    //TODO: tmp solution, convert all links to arrRef(:,:,:) 
    SgArrayRefExp* copyExpr = NULL;
    
    bool isSimple = false;
    if (withConv)
    {
        copyExpr = (SgArrayRefExp*) & (expr->copy());
        SgExpression* subs = copyExpr->subscripts();

        set<string> tmp;
        isSimple = isSimpleRef(subs, { ARRAY_OP, ARRAY_REF, VAR_REF });
        //const bool isDiffInSubs = isArrayRefHasDifferentVars(subs, tmp);
        if (!isSimple) // && !isDiffInSubs)
            converToDDOT(subs);
    }
    else
        copyExpr = expr;

    string remoteExp(copyExpr->unparse());
    auto rem = uniqRemotes.find(remoteExp);
    if (rem == uniqRemotes.end() && remotesInParallel.find(remoteExp) == remotesInParallel.end())
    {
        rem = uniqRemotes.insert(rem, make_pair(remoteExp, copyExpr));
        addedRemotes.insert(copyExpr);

        if (line > 0 && !isSimple)
        {
            string remoteExp(expr->unparse());
            __spf_print(1, "WARN: added remote access for array ref '%s' on line %d can significantly reduce performance\n", remoteExp.c_str(), line);

            wstring bufE, bufR;
            __spf_printToLongBuf(bufE, L"Added remote access for array ref '%s' can significantly reduce performance", to_wstring(remoteExp).c_str());
            __spf_printToLongBuf(bufR, R129, to_wstring(remoteExp).c_str());

            messages.push_back(Messages(WARR, line, bufR, bufE, 3009));
        }
    }
}

static set<string> fillRemotesInParallel(const ParallelDirective* dvm_dir)
{
    set<string> remotesInParallel;
    for (auto& elem : dvm_dir->remoteAccess)
        remotesInParallel.insert(elem.first.first.first + "(" + elem.first.second + ")");
    return remotesInParallel;
}

void createRemoteInParallel(const tuple<SgForStmt*, const LoopGraph*, const ParallelDirective*>& under_dvm_dir,
                            const set<DIST::Array*>& doneInLoops,
                            map<string, SgArrayRefExp*>& uniqRemotes, vector<Messages>& messages)
{
    const set<DIST::Array*> usedArrays = SECOND(under_dvm_dir)->usedArrays;
    const set<DIST::Array*> usedArraysWrite = SECOND(under_dvm_dir)->usedArraysWrite;
    const set<string> remotesInParallel = fillRemotesInParallel(THIRD(under_dvm_dir));
    set<SgArrayRefExp*> addedRemotes;

    for (auto& usedArr : usedArrays)
    {
        if (doneInLoops.find(usedArr) == doneInLoops.end() && usedArraysWrite.find(usedArr) == usedArraysWrite.end())
        {
            SgExpression* ex = new SgExpression(EXPR_LIST);
            SgExpression* p = ex;
            for (int z = 0; z < usedArr->GetDimSize(); ++z)
            {
                p->setLhs(new SgExpression(DDOT));
                if (z != usedArr->GetDimSize() - 1)
                {
                    p->setRhs(new SgExpression(EXPR_LIST));
                    p = p->rhs();
                }
            }
            SgArrayRefExp* newRem = new SgArrayRefExp(*findSymbolOrCreate(current_file, usedArr->GetShortName()), *ex);
            addRemoteLink(newRem, uniqRemotes, remotesInParallel, addedRemotes, messages, -1, false);
            __spf_print(DEB, "CRIP: %d, AFTER MAIN CHECK for arrray '%s'\n", __LINE__, usedArr->GetShortName().c_str());
        }
    }
}

void createRemoteInParallel(const tuple<SgForStmt*, const LoopGraph*, const ParallelDirective*> &under_dvm_dir,
                            const DIST::Arrays<int> &allArrays,
                            const map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo,
                            DIST::GraphCSR<int, double, attrType> &reducedG,
                            const DataDirective &data,
                            const vector<int> &currVar,
                            const map<int, pair<SgForStmt*, pair<set<string>, set<string>>>> &allLoops,
                            map<string, SgArrayRefExp*> &uniqRemotes,
                            vector<Messages> &messages,
                            const uint64_t regionId,
                            const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                            set<DIST::Array*>& doneInLoops)
{
    if (!FIRST(under_dvm_dir) || !SECOND(under_dvm_dir) || !THIRD(under_dvm_dir))
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    __spf_print(DEB, "createRemoteInParallel %d, for loop %d\n", __LINE__, FIRST(under_dvm_dir)->lineNumber());
    set<SgArrayRefExp*> addedRemotes;

    auto it = loopInfo.find(FIRST(under_dvm_dir));
    if (it != loopInfo.end())
    {
        const map<SgSymbol*, ArrayInfo> &currInfo = it->second;
        DIST::Array *arrayRefOnDir = THIRD(under_dvm_dir)->arrayRef;
        set<DIST::Array*> realRefArrayOnDir;
        const set<string> remotesInParallel = fillRemotesInParallel(THIRD(under_dvm_dir));

        if (!arrayRefOnDir->IsTemplate())
        {
            getRealArrayRefs(arrayRefOnDir, arrayRefOnDir, realRefArrayOnDir, arrayLinksByFuncCalls);
            if (realRefArrayOnDir.size() != 1)
            {
                vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> allRules(realRefArrayOnDir.size());
                int tmpIdx = 0;
                for (auto& array : realRefArrayOnDir)
                    reducedG.GetAlignRuleWithTemplate(array, allArrays, allRules[tmpIdx++], regionId);

                if (!isAllRulesEqual(allRules))
                {
                    __spf_print(1, "not supported yet\n");
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
                else
                    arrayRefOnDir = *(realRefArrayOnDir.begin());
            }
            else
                arrayRefOnDir = *(realRefArrayOnDir.begin());
        }

        vector<pair<DIST::Array*, ArrayInfo>> writesInLoop;
        //save all write in loop
        for (auto it = currInfo.begin(); it != currInfo.end(); ++it)
        {
            for (int k = 0; k < it->second.dimSize; ++k)
            {
                if (it->second.writeOps[k].coefficients.size() != 0)
                {
                    SgSymbol *tmpS = OriginalSymbol(it->first);
                    DIST::Array *arrayRef = GetArrayByShortName(allArrays, tmpS);

                    set<DIST::Array*> realArrayRef;
                    getRealArrayRefs(arrayRef, arrayRef, realArrayRef, arrayLinksByFuncCalls);
                    
                    for (auto &elem : realArrayRef)
                        writesInLoop.push_back(make_pair(elem, it->second));
                    break;
                }
            }
        }
        
        // for all array accesses in loop
        for (auto it = currInfo.begin(); it != currInfo.end(); ++it)
        {
            SgSymbol *tmpS = OriginalSymbol(it->first);
            DIST::Array *arrayRef = GetArrayByShortName(allArrays, tmpS);
            if (!arrayRef)
                continue;
            doneInLoops.insert(arrayRef);

            auto itInfo = currInfo.find(tmpS);
            if (itInfo == currInfo.end())
                continue;

            const ArrayInfo *currArrayInfo = &(itInfo->second);
            
            set<DIST::Array*> realArrayRef;
            getRealArrayRefs(arrayRef, arrayRef, realArrayRef, arrayLinksByFuncCalls);
            
            for (auto &elem : realArrayRef)
            {
                arrayRef = elem;

                // fill links between current array and array in parallel dir
                vector<int> links;
                if (arrayRef != arrayRefOnDir)
                    links = findLinksBetweenArrays(arrayRef, arrayRefOnDir, regionId);
                else
                {
                    links.resize(arrayRef->GetDimSize());
                    for (int k = 0; k < arrayRef->GetDimSize(); ++k)
                        links[k] = k;
                }

                //fill info links with template
                auto linksWithTempl = arrayRef->GetLinksWithTemplate(regionId);
                auto alignRuleWithTempl = arrayRef->GetAlignRulesWithTemplate(regionId);

                const DIST::Array *templArray = arrayRef->GetTemplateArray(regionId);
                if (!templArray)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                // fill distribute data variant
                const DistrVariant *distrVar = NULL;
                for (int k = 0; k < data.distrRules.size(); ++k)
                {
                    if (data.distrRules[k].first == templArray)
                    {
                        distrVar = &data.distrRules[k].second[currVar[k]];
                        break;
                    }
                }

                if (!distrVar)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                // set new redistribute rule, if exist
                const DistrVariant *newDistVar = SECOND(under_dvm_dir)->getRedistributeRule(templArray);
                if (newDistVar)
                    distrVar = newDistVar;

                set<string> parallelVars;
                parallelVars.insert(THIRD(under_dvm_dir)->parallel.begin(), THIRD(under_dvm_dir)->parallel.end());

                // main check 
                for (int i = 0; i < links.size(); ++i)
                {
                    bool needToCheck = false;
                    if (links[i] != -1 && linksWithTempl[i] != -1)
                    {
                        const bool isInParallel = parallelVars.find(THIRD(under_dvm_dir)->on[links[i]].first) != parallelVars.end();
                        if (distrVar->distRule[linksWithTempl[i]] == BLOCK)
                        {
                            if (THIRD(under_dvm_dir)->on[links[i]].first != "*" && !isInParallel)
                                needToCheck = false;
                            else
                                needToCheck = true;
                        }
                    }
                    else if (linksWithTempl[i] != -1)
                    {
                        // if distributed and used in loop with out link with array on dir
                        if (distrVar->distRule[linksWithTempl[i]] == BLOCK)
                        {
                            // check all unrecognized refs
                            for (auto itA = currArrayInfo->arrayAccessUnrec.begin(); itA != currArrayInfo->arrayAccessUnrec.end(); ++itA)
                            {
                                if (addedRemotes.find(itA->first) != addedRemotes.end())
                                    continue;
                                else if (itA->second.second[i] == REMOTE_TRUE)
                                {
                                    addRemoteLink(itA->first, uniqRemotes, remotesInParallel, addedRemotes, messages, itA->second.first);
                                    __spf_print(DEB, "CRIP: %d, REMOTE_TRUE\n", __LINE__);
                                }
                            }

                            // check all regular refs
                            for (auto itA = currArrayInfo->arrayAccess.begin(); itA != currArrayInfo->arrayAccess.end(); ++itA)
                            {
                                if (addedRemotes.find(itA->first) != addedRemotes.end())
                                    continue;

                                if (arrayRef == arrayRefOnDir)
                                    continue;

                                addRemoteLink(itA->first, uniqRemotes, remotesInParallel, addedRemotes, messages, itA->second.first);
                                __spf_print(DEB, "CRIP: %d, IRREG_REFS\n", __LINE__);
                            }
                            continue;
                        }
                    }

                    // check if current dimention is distributed
                    if (needToCheck)
                    {
                        // check unregular acceses
                        for (auto itA = currArrayInfo->arrayAccessUnrec.begin(); itA != currArrayInfo->arrayAccessUnrec.end(); ++itA)
                        {
                            if (addedRemotes.find(itA->first) != addedRemotes.end())
                                continue;

                            if (itA->second.second[i] == REMOTE_TRUE)
                            {
                                addRemoteLink(itA->first, uniqRemotes, remotesInParallel, addedRemotes, messages, itA->second.first);
                                __spf_print(DEB, "CRIP: %d, IRREG_REFS && REMOTE_TRUE\n", __LINE__);
                            }
                        }

                        // and check regular acceses
                        for (auto &regAccess : currArrayInfo->arrayAccess)
                        {
                            if (addedRemotes.find(regAccess.first) != addedRemotes.end())
                                continue;

                            if (arrayRef == arrayRefOnDir)
                                continue;

                            //if has reads in more than one dim and it dims are dirstributed
                            int countOfDimAcc = 0;
                            for (int z = 0; z < linksWithTempl.size(); ++z)
                            {
                                bool distributed = false;
                                if (linksWithTempl[z] != -1)
                                    distributed = (distrVar->distRule[linksWithTempl[z]] == BLOCK);

                                countOfDimAcc += ((regAccess.second.second[z].coefficients.size() != 0) && distributed) ? 1 : 0;
                            }

                            if (countOfDimAcc > 1 ||
                                countOfDimAcc == 1 && THIRD(under_dvm_dir)->on[links[i]].first == "*")
                            {
                                addRemoteLink(regAccess.first, uniqRemotes, remotesInParallel, addedRemotes, messages, regAccess.second.first);
                                __spf_print(DEB, "CRIP: %d ---\n", __LINE__);
                                continue;
                            }

                            //if has distributed dim but loop maped to *
                            if (THIRD(under_dvm_dir)->on[links[i]].first == "*")
                            {
                                if (linksWithTempl[i] != -1)
                                    if (distrVar->distRule[linksWithTempl[i]] == BLOCK)
                                    {
                                        addRemoteLink(regAccess.first, uniqRemotes, remotesInParallel, addedRemotes, messages, regAccess.second.first);
                                        __spf_print(DEB, "CRIP: %d, NOT MAPPED\n", __LINE__);
                                        continue;
                                    }
                            }

                            //if this array has no map rules to current array and this dim is distributed
                            if (SECOND(under_dvm_dir)->directiveForLoop)
                            {
                                if (SECOND(under_dvm_dir)->directiveForLoop->on[links[i]].first != "*")
                                {
                                    if (regAccess.second.second[i].coefficients.size() == 0)
                                    {
                                        addRemoteLink(regAccess.first, uniqRemotes, remotesInParallel, addedRemotes, messages, regAccess.second.first);
                                        __spf_print(DEB, "CRIP: %d, ----\n", __LINE__);
                                        continue;
                                    }
                                }
                            }

                            const pair<int, int> &alignRuleRead = alignRuleWithTempl[i];
                            bool wasAdd = false;


                            if (writesInLoop.size() == 0)
                                continue;

                            // try to check all writes with ...
                            for (int k = 0; k < writesInLoop.size() && !wasAdd; ++k)
                            {
                                if (writesInLoop[k].first != arrayRef)
                                {
                                    vector<int> tmpLinks = findLinksBetweenArrays(arrayRef, writesInLoop[k].first, regionId);

                                    // find link between currentArray and writeArray
                                    const int writeDim = tmpLinks[i];
                                    if (writeDim != -1)
                                    {
                                        auto writeRulesWithTempl = writesInLoop[k].first->GetAlignRulesWithTemplate(regionId);
                                        auto alignRuleWrite = writeRulesWithTempl[writeDim];

                                        for (auto &writes : writesInLoop[k].second.writeOps[writeDim].coefficients)
                                        {
                                            const pair<int, int> &currWriteAcc = writes.first;

                                            // ... all reads 
                                            for (auto &reads : regAccess.second.second[i].coefficients)
                                            {
                                                const pair<int, int> &currReadAcc = reads.first;
                                                // main check for regular read
                                                //printf("%d %d -- %d %d\n", currWriteAcc.first, alignRuleWrite.first, currReadAcc.first, alignRuleRead.first);
                                                if (currWriteAcc.first * alignRuleWrite.first != currReadAcc.first * alignRuleRead.first)
                                                {
                                                    addRemoteLink(regAccess.first, uniqRemotes, remotesInParallel, addedRemotes, messages, regAccess.second.first);
                                                    __spf_print(DEB, "CRIP: %d, MISS\n", __LINE__);
                                                    wasAdd = true;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } // main check
            }
        }

        if (SECOND(under_dvm_dir)->perfectLoop > 1)
        {
            tuple<SgForStmt*, const LoopGraph*, const ParallelDirective*> nextDir = under_dvm_dir;
            SECOND(nextDir) = SECOND(under_dvm_dir)->children[0];

            auto it = allLoops.find(SECOND(under_dvm_dir)->children[0]->lineNum);
            if (it == allLoops.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            FIRST(nextDir) = it->second.first;
            createRemoteInParallel(nextDir, allArrays, loopInfo, reducedG, data, currVar, allLoops, uniqRemotes, messages, regionId, arrayLinksByFuncCalls, doneInLoops);
        }
    }
}

void addRemotesToDir(const pair<SgForStmt*, LoopGraph*> *under_dvm_dir, const map<string, SgArrayRefExp*> &uniqRemotes)
{
    SgStatement *dir = under_dvm_dir->first->lexPrev();

    for (auto it = uniqRemotes.begin(); it != uniqRemotes.end(); ++it)
    {
        if (!dir)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (dir->variant() != DVM_PARALLEL_ON_DIR)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        SgExpression *list = dir->expr(1);
        SgExpression *remoteList = NULL;
        while (list)
        {
            if (list->lhs())
            {
                if (list->lhs()->variant() == REMOTE_ACCESS_OP)
                {
                    remoteList = list->lhs();
                    break;
                }
            }
            list = list->rhs();
        }
        list = dir->expr(1);
        SgExpression *toAdd = new SgExpression(EXPR_LIST, it->second, NULL, NULL);

        if (!remoteList)
        {
            remoteList = new SgExpression(REMOTE_ACCESS_OP, toAdd, NULL, NULL);
            dir->setExpression(1, *new SgExpression(EXPR_LIST, remoteList, list, NULL));
        }
        else
        {
            SgExpression *lastLhs = remoteList->lhs();
            remoteList->setLhs(toAdd);
            toAdd->setRhs(lastLhs);
        }
    }
}

#undef FIRST
#undef SECOND
#undef THIRD