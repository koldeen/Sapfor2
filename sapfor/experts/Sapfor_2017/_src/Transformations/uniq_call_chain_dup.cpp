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
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"

#include "uniq_call_chain_dup.h"
#include "../GraphCall/graph_calls.h"
#include "../GraphCall/graph_calls_func.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../VerificationCode/verifications.h"

using namespace std;

struct callVars
{
    callVars() { }
    callVars(const pair<void*, int>& place, const vector<void*>& var) : callVariant(var) 
    {
        callPlaces.push_back(place);
    }

    vector<pair<void*, int>> callPlaces;
    vector<void*> callVariant;
    string copiedName;
};

struct callInfo
{
    callInfo() { countCalls = 0; }

    int countCalls;
    vector<callVars> variantCall;
};

static bool checkUniqAndAdd(vector<callVars> &vars, const vector<void*> &current, const pair<void*, int> &callPlace)
{
    for (auto& elem : vars)
    {
        if (elem.callVariant == current)
        {
            elem.callPlaces.push_back(callPlace);
            return false;
        }
    }

    vars.push_back(callVars(callPlace, current));
    return true;
}

static vector<void*> createParamCalls(const pair<void*, int> &callPointer, const string &fileN)
{
    if (SgFile::switchToFile(fileN) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgExpression *callList = NULL;
    if (callPointer.second == PROC_STAT)
        callList = ((SgStatement*)callPointer.first)->expr(0);
    else if (callPointer.second == FUNC_CALL)
        callList = ((SgExpression*)callPointer.first)->lhs();
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    vector<void*> packCall;

    while (callList)
    {
        auto curr = callList->lhs();
        if (curr->variant() == ARRAY_REF)
        {
            SgSymbol* par = OriginalSymbol(callList->lhs()->symbol());
            DIST::Array* array = getArrayFromDeclarated(declaratedInStmt(par), par->identifier());
            if (array)
            {
                if (array->GetNonDistributeFlag() == false)
                    packCall.push_back(array);
                else
                    packCall.push_back(NULL);
            }
            else
                packCall.push_back(NULL);
        }
        else
            packCall.push_back(NULL);
        callList = callList->rhs();
    }

    return packCall;
}

static map<FuncInfo*, callInfo> countOfCalls(const map<string, vector<FuncInfo*>> &allFuncs, const map<string, FuncInfo*> &mapOfFunc)
{
    map<FuncInfo*, int> count;    
    map<FuncInfo*, vector<callVars>> variantCall;

    for (auto& fromFile : allFuncs)
    {
        for (auto& elem : fromFile.second)
        {
            count[elem] = 0;
            variantCall[elem] = vector<callVars>();
        }
    }

    for (auto& fromFile : allFuncs)
    {
        for (auto& elem : fromFile.second)
        {
            int p = 0;
            for (auto& detailed : elem->detailCallsFrom)
            {
                auto it = mapOfFunc.find(detailed.first);
                if (it != mapOfFunc.end())
                {
                    auto var = variantCall.find(it->second);
                    auto createPackCall = createParamCalls(elem->pointerDetailCallsFrom[p], elem->fileName);
                    if (checkUniqAndAdd(var->second, createPackCall, elem->pointerDetailCallsFrom[p]))
                        count[it->second]++;
                }
                ++p;
            }
        }
    }

    map<FuncInfo*, callInfo> retInfo;
    for (auto& elem : count)
        retInfo[elem.first].countCalls = elem.second;
    for (auto& elem : variantCall)
        retInfo[elem.first].variantCall = elem.second;
    return retInfo;
}

static int getRealCallCount(const callInfo &info, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCall)
{
    if (info.variantCall.size() > 1)
        return info.countCalls;
    else if (info.variantCall.size() == 0)
        return 0;
    else
    {
        const callVars& var = info.variantCall[0];
        for (int z = 0; z < var.callVariant.size(); ++z)
        {
            if (var.callVariant[z])
            {
                DIST::Array* ref = (DIST::Array*)var.callVariant[z];
                set<DIST::Array*> realRefs;
                getRealArrayRefs(ref, ref, realRefs, arrayLinksByFuncCall);
                if (realRefs.size() > 1)
                    return 2;
            }
        }

        return 1;
    }
}

static vector<FuncInfo*> detect(const map<string, vector<FuncInfo*>> &allFuncs, const map<string, FuncInfo*> &mapOfFunc, 
                                map<FuncInfo*, callInfo> &funcInfoOfCall, const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCall)
{    
    vector<FuncInfo*> retVal;
    funcInfoOfCall = countOfCalls(allFuncs, mapOfFunc);

    for (auto &fromFile : allFuncs)
    {
        if (SgFile::switchToFile(fromFile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto &elem : fromFile.second)
        {
            SgProgHedrStmt *prog = isSgProgHedrStmt(elem->funcPointer->GetOriginal());
            checkNull(prog, convertFileName(__FILE__).c_str(), __LINE__);

            if (prog->variant() == PROG_HEDR)
                continue;

            if (getRealCallCount(funcInfoOfCall[elem], arrayLinksByFuncCall) <= 1)
                continue;

            for (int z = 0; z < prog->numberOfParameters(); ++z)
            {
                SgSymbol *par = OriginalSymbol(prog->parameter(z));
                DIST::Array *array = getArrayFromDeclarated(declaratedInStmt(par), par->identifier());

                if (array)
                {
                    if (array->GetNonDistributeFlag() == false)
                    {
                        retVal.push_back(elem);
                        break;
                    }
                }
            }
        }
    }

    return retVal;
}

static set<FuncInfo*> getFullCallsFrom(FuncInfo *from, const map<string, FuncInfo*> &mapOfFunc)
{
    set<FuncInfo*> callsFromFull;
    callsFromFull.insert(from);

    bool change = true;
    while (change)
    {
        change = false;
        set<FuncInfo*> newAdd;
        for (auto& func: callsFromFull)
        {
            for (auto& elem : func->callsFrom)
            {
                auto it = mapOfFunc.find(elem);
                if (it != mapOfFunc.end())
                {
                    auto it2 = callsFromFull.find(it->second);
                    if (callsFromFull.end() == it2)
                    {
                        newAdd.insert(it->second);
                        change = true;
                    }
                }
            }
        }

        for (auto& elem : newAdd)
            callsFromFull.insert(elem);
    }

    return callsFromFull;
}

static bool isAllDone(const vector<bool>& done)
{
    for (const auto& elem : done)
        if (elem == false)
            return false;
    return true;
}

static map<FuncInfo*, set<FuncInfo*>> groupByMainCall(const vector<FuncInfo*> &toCopy, const map<string, FuncInfo*> &mapOfFunc)
{
    set<FuncInfo*> copySet(toCopy.begin(), toCopy.end());

    vector<bool> done(toCopy.size());
    std::fill(done.begin(), done.end(), false);

    map<FuncInfo*, set<FuncInfo*>> groups;

    while (!isAllDone(done))
    {
        int z = 0;
        for (; z < done.size(); ++z)
        {
            if (!done[z])
            {
                for (auto& callsTo : toCopy[z]->callsTo)
                {
                    if (copySet.find(callsTo) != copySet.end())
                        continue;
                }
                done[z] = true;
                break;
            }
        }

        if (z == done.size() + 1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        groups[toCopy[z]] = set<FuncInfo*>();

        set<FuncInfo*> fullCalls = getFullCallsFrom(toCopy[z], mapOfFunc);
        for (int p = 0; p < done.size(); ++p)
        {
            //self
            if (p == z)
                continue;

            if (fullCalls.find(toCopy[p]) != fullCalls.end())
            {
                groups[toCopy[z]].insert(toCopy[p]);
                done[p] = true;
            }
        }
    }

    return groups;
}

static void fillOrigCopyEx(SgExpression *orig, SgExpression *copy, map<SgExpression*, SgExpression*> &origCopyEx)
{
    if (orig)
    {
        origCopyEx[orig] = copy;

        fillOrigCopyEx(orig->lhs(), copy->lhs(), origCopyEx);
        fillOrigCopyEx(orig->rhs(), copy->rhs(), origCopyEx);
    }
}

static void findAllFunctionCalls(SgExpression* ex, const vector<void*> &paramVar, 
                                 const string& file, set<SgExpression*>& toChange)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            pair<void*, int> callPointer = make_pair(ex, FUNC_CALL);
            if (createParamCalls(callPointer, file) == paramVar)
                toChange.insert(ex);
        }

        if (ex->lhs())
            findAllFunctionCalls(ex->lhs(), paramVar, file, toChange);
        if (ex->rhs())
            findAllFunctionCalls(ex->rhs(), paramVar, file, toChange);
    }
}

static void findInterfaceBlockAndDuplicate(SgStatement* func, const string& ifaceName, const string& ifaceCopy, int variant)
{
    if (SgFile::switchToFile(func->fileName()) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement* end = func->lastNodeOfStmt();
    for ( ; func != end; func = func->lexNext())
    {
        if (func->variant() == INTERFACE_STMT)
        {
            SgStatement* ifaceEnd = func->lastNodeOfStmt();
            bool found = false;
            for (auto st = func->lexNext(); st != ifaceEnd; st = st->lexNext())
            {
                if (st->variant() == variant && st->symbol()->identifier() == ifaceName)
                {
                    auto copy = st->copyBlockPtr();
                    st->insertStmtBefore(*copy, *st->controlParent());
                    SgSymbol* copyS = &copy->symbol()->copy();
                    copyS->changeName(ifaceCopy.c_str());
                    copy->setSymbol(*copyS);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if (isSgExecutableStatement(func) && !isDVM_stat(func) && !isSPF_stat(func))
            break;
        if (func->variant() == CONTAINS_STMT)
            break;
    }
}

static void copyGroup(const map<string, FuncInfo*> &mapOfFunc, const vector<FuncInfo*> &toCopyGroups, map<FuncInfo*, callInfo> &funcInfoOfCall)
{
    if (toCopyGroups.size() == 0)
        return;

    // function -> functions witn interface to thisF
    map<FuncInfo*, set<FuncInfo*>> interfaceInfo;

    for (auto& func: mapOfFunc)
        for (auto& interf : func.second->interfaceBlocks)
            interfaceInfo[interf.second].insert(func.second);

    bool changed = true;
    map<FuncInfo*, int> numCopyF;

    map<string, map<SgStatement*, SgSymbol*>> toChangeSt;
    map<string, map<SgExpression*, SgSymbol*>> toChangeEx;

    int iterCount = 0;
    while (changed)
    {
        changed = false;
        SgStatement::cleanParentStatsForExprs();

        for (auto& currFunc : toCopyGroups)
        {
            auto info = funcInfoOfCall.find(currFunc);
            if (info == funcInfoOfCall.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            if (numCopyF.find(currFunc) == numCopyF.end())
                numCopyF[currFunc] = 1;            
            for (auto& varCall : info->second.variantCall)
            {
                int numCopy = numCopyF[currFunc];
                if (varCall.copiedName.size() != 0)
                    continue;

                changed = true;
                if (SgFile::switchToFile(currFunc->fileName) == -1)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                SgStatement* pointToF = currFunc->funcPointer->GetOriginal();

                SgSymbol* orig = pointToF->symbol();
                SgSymbol* copied = &orig->copySubprogram(*current_file->firstStatement());

                string origName = orig->identifier();
                origName = getOrigName(pointToF->fileName(), origName);

                string newName = checkSymbNameAndCorrect(origName + string("_spf_") + to_string(numCopy));
                varCall.copiedName = newName;
                copied->changeName(newName.c_str());

                //move 
                SgStatement* toMove = current_file->firstStatement()->lexNext()->extractStmt();
                pointToF->insertStmtBefore(*toMove, *pointToF->controlParent());

                map<SgStatement*, SgStatement*> origCopySt;
                map<SgExpression*, SgExpression*> origCopyEx;
                // set line numbers and pointer to attributes
                for (auto origStat = pointToF, copyStat = toMove;
                    origStat != pointToF->lastNodeOfStmt()->lexNext();
                    origStat = origStat->lexNext(), copyStat = copyStat->lexNext())
                {
                    if (copyStat->variant() != origStat->variant())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    copyStat->setlineNumber(origStat->lineNumber());
                    BIF_FILE_NAME(copyStat->thebif) = BIF_FILE_NAME(origStat->thebif);
                    if (origStat->numberOfAttributes() > 0)
                        copyStat->addAttributeTree(origStat->getAttribute(0));
                    origCopySt[origStat] = copyStat;
                    if (origStat->comments())
                        copyStat->setComments(origStat->comments());

                    for (int z = 0; z < 3; ++z)
                        fillOrigCopyEx(origStat->expr(z), copyStat->expr(z), origCopyEx);
                }

                int varOfCall = PROC_HEDR;
                //replace calls
                for (auto& places : varCall.callPlaces)
                {
                    if (places.second == PROC_STAT)
                    {
                        SgStatement* proc = (SgStatement*)places.first;
                        if (SgFile::switchToFile(proc->fileName()) == -1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        SgSymbol* newS = &proc->symbol()->copy();
                        newS->changeName(newName.c_str());
                        toChangeSt[proc->fileName()][proc] = newS;
                    }
                    else if (places.second == FUNC_CALL)
                    {
                        varOfCall = FUNC_HEDR;
                        SgExpression* proc = (SgExpression*)places.first;
                        SgStatement* parent = SgStatement::getStatmentByExpression(proc);
                        if (parent == NULL)
                            parent = findReplacedExpression(proc);
                        checkNull(parent, convertFileName(__FILE__).c_str(), __LINE__);

                        if (SgFile::switchToFile(parent->fileName()) == -1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        SgSymbol* newS = &proc->symbol()->copy();
                        set<SgExpression*> allPlaces;
                        for (int z = 0; z < 3; ++z)
                            findAllFunctionCalls(parent->expr(z), varCall.callVariant, parent->fileName(), allPlaces);
                        if (allPlaces.size() == 0)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        newS->changeName(newName.c_str());
                        for (auto &elem : allPlaces)
                            toChangeEx[parent->fileName()][elem] = newS;
                    }
                    else
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                //duplicate interfaces
                auto itInterf = interfaceInfo.find(currFunc);
                if (itInterf != interfaceInfo.end())
                    for (auto& func : itInterf->second)
                        findInterfaceBlockAndDuplicate(func->funcPointer->GetOriginal(), origName, newName, varOfCall);

                // fill additional places to next replaces
                for (int z = 0; z < currFunc->pointerDetailCallsFrom.size(); ++z)
                {
                    pair<void*, int> place = currFunc->pointerDetailCallsFrom[z];
                    if (place.second == PROC_STAT)
                    {
                        SgStatement* proc = (SgStatement*)place.first;
                        if (SgFile::switchToFile(proc->fileName()) == -1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        SgStatement* copyPoint = origCopySt[proc];
                        const string toFind = proc->symbol()->identifier();

                        auto itF = mapOfFunc.find(toFind.c_str());
                        if (itF == mapOfFunc.end())
                            continue;

                        FuncInfo* toAdd = itF->second;
                        auto infoAdd = funcInfoOfCall.find(toAdd);
                        if (infoAdd == funcInfoOfCall.end())
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        vector<void*> tmp;
                        infoAdd->second.variantCall.push_back(callVars(make_pair(copyPoint, PROC_STAT), tmp));
                    }
                    else if (place.second == FUNC_CALL)
                    {
                        SgExpression* proc = (SgExpression*)place.first;
                        SgStatement* parent = (SgStatement*)currFunc->parentForPointer[z];
                        checkNull(parent, convertFileName(__FILE__).c_str(), __LINE__);
                        if (SgFile::switchToFile(parent->fileName()) == -1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        SgExpression* copyPoint = origCopyEx[proc];
                        const string toFind = proc->symbol()->identifier();

                        auto itF = mapOfFunc.find(toFind.c_str());
                        if (itF == mapOfFunc.end())
                            continue;

                        FuncInfo* toAdd = itF->second;
                        auto infoAdd = funcInfoOfCall.find(toAdd);
                        if (infoAdd == funcInfoOfCall.end())
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        vector<void*> tmp;
                        infoAdd->second.variantCall.push_back(callVars(make_pair(copyPoint, FUNC_CALL), tmp));
                    }
                    else
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                numCopyF[currFunc]++;
            }
        }        
        ++iterCount;
    }

    for (auto& elem : toChangeSt)
    {
        if (SgFile::switchToFile(elem.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& toSet : elem.second)
            toSet.first->setSymbol(*toSet.second);
    }

    for (auto& elem : toChangeEx)
    {
        if (SgFile::switchToFile(elem.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& toSet : elem.second)
            toSet.first->setSymbol(*toSet.second);
    }
}

static bool checkForData(FuncInfo* info, map<string, vector<Messages>>& messages)
{
    bool retVal = true;
    if (info->isMain || info->isInterface)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement* funcP = info->funcPointer->GetOriginal();
    if (!funcP->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    for (auto st = funcP; st != funcP->lastNodeOfStmt(); st = st->lexNext())
    {
        if (st->variant() == CONTAINS_STMT)
            break;
        if (isSgExecutableStatement(st))
            break;
        if (st->variant() == VAR_DECL || st->variant() == VAR_DECL_90)
        {
            SgExpression* list = st->expr(0);
            while (list)
            {
                auto value = list->lhs();
                if (value->variant() == ASSGN_OP)
                {
                    wstring bufE, bufR;
                    __spf_printToLongBuf(bufE, L"SAVE or DATA operators prevent function duplication: variable '%s'",
                                         to_wstring(value->lhs()->symbol()->identifier()).c_str());
                    __spf_printToLongBuf(bufR, R174, to_wstring(value->lhs()->symbol()->identifier()).c_str());

                    messages[st->fileName()].push_back(Messages(ERROR, st->lineNumber(), bufR, bufE, 2013));
                    retVal = false;
                }
                else if (value->symbol() && (value->symbol()->attributes() & DATA_BIT))
                {
                    wstring bufE, bufR;
                    __spf_printToLongBuf(bufE, L"SAVE or DATA operators prevent function duplication: variable '%s'", to_wstring(value->symbol()->identifier()).c_str());
                    __spf_printToLongBuf(bufR, R174, to_wstring(value->symbol()->identifier()).c_str());

                    messages[st->fileName()].push_back(Messages(ERROR, st->lineNumber(), bufR, bufE, 2013));
                    retVal = false;
                }
                list = list->rhs();
            }
        }
        else if (st->variant() == SAVE_DECL || st->variant() == DATA_DECL)
        {
            wstring bufE, bufR;
            __spf_printToLongBuf(bufE, L"SAVE or DATA operators prevent function duplication");
            __spf_printToLongBuf(bufR, R173);

            messages[st->fileName()].push_back(Messages(ERROR, st->lineNumber(), bufR, bufE, 2012));
            retVal = false;
        }
    }

    return retVal;
}

bool duplicateFunctions(const map<string, vector<FuncInfo*>> &allFuncs, const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCall,
                        map<string, vector<Messages>>& messages)
{
    map<string, FuncInfo*> mapOfFunc;
    createMapOfFunc(allFuncs, mapOfFunc);

    map<FuncInfo*, callInfo> funcInfoOfCall;
    vector<FuncInfo*> toCopy = detect(allFuncs, mapOfFunc, funcInfoOfCall, arrayLinksByFuncCall);
    map<FuncInfo*, set<FuncInfo*>> toCopyGroups = groupByMainCall(toCopy, mapOfFunc);

    vector<FuncInfo*> toCopyVec;
    for (auto& elem : toCopyGroups)
        toCopyVec.push_back(elem.first);

    for (auto& elem : toCopyGroups)
        for (auto &inG : elem.second)
            toCopyVec.push_back(inG);

    bool checkOk = true;
    //check for save vars
    for (auto& func : toCopyVec)
    {
        bool res = checkForData(func, messages);
        checkOk = checkOk && res;
    }
    if (checkOk)
        copyGroup(mapOfFunc, toCopyVec, funcInfoOfCall);
    return checkOk;
}

static void changeFuncNameInDvmDirs(SgExpression* ex, const string& to, const string& from, map<SgSymbol*, string>& changed)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF)
        {
            auto s = ex->symbol();
            if (s->identifier() == from || from.find("::") != string::npos && from.find(s->identifier()) != string::npos)
            {
                changed[s] = s->identifier();
                s->changeName(to.c_str());
            }
        }

        changeFuncNameInDvmDirs(ex->lhs(), to, from, changed);
        changeFuncNameInDvmDirs(ex->rhs(), to, from, changed);
    }
}

static map<SgSymbol*, string> changeFuncNameInDvmDirs(const string& to, const string &from, SgStatement* func)
{
    map<SgSymbol*, string> changed;
    SgStatement* st = func;
    SgStatement* last = st->lastNodeOfStmt();
    while (st != last)
    {
        if (isDVM_stat(st))
            for (int z = 0; z < 3; ++z)
                changeFuncNameInDvmDirs(st->expr(z), to, from, changed);
        st = st->lexNext();
    }
    return changed;
}

static map<FuncInfo*, set<FuncInfo*>> getUniqCopies(const vector<FuncInfo*> &toCmp)
{
    map<string, set<FuncInfo*>> dict;
    string cmpName = "testCmpName";
    for (auto& elem : toCmp)
    {
        SgSymbol *s = elem->funcPointer->GetOriginal()->symbol();
        string saveName = s->identifier();
        s->changeName(cmpName.c_str());
        
        map<SgSymbol*, string> changed;
        if (elem->funcPointer->GetOriginal()->variant() == FUNC_HEDR)
            changed = changeFuncNameInDvmDirs(cmpName, saveName, elem->funcPointer->GetOriginal());

        const char* buf = elem->funcPointer->GetOriginal()->unparse();
        dict[buf].insert(elem);

        s->changeName(saveName.c_str());
        for (auto& elem : changed)
            elem.first->changeName(elem.second.c_str());
    }

    map<FuncInfo*, set<FuncInfo*>> uniq;
    for (auto& elem : dict)
    {
        auto it = elem.second.begin();
        FuncInfo* base = *it;
        uniq[base] = set<FuncInfo*>();
        for (it++; it != elem.second.end(); it++)
            uniq[base].insert(*it);
    }

    return uniq;
}

static map<string, set<FuncInfo*>> removed;
static map<string, set<SgStatement*>> copied;
static map<string, string> newNamesOfUniqCopies;
map<SgSymbol*, pair<string, string>> replaced;
static map<string, set<SgStatement*>> hiddenInterfaceBlocks;

static bool removeThisFunctions(const string &file, const map<FuncInfo*, set<FuncInfo*>> &uniqCopies, const vector<FuncInfo*>& toRem)
{
    bool wasRemoved = false;
    for (auto& rem : toRem)
    {
        if (uniqCopies.find(rem) == uniqCopies.end() && removed[file].find(rem) == removed[file].end())
        {
            SgStatement* orig = rem->funcPointer->GetOriginal();
            SgStatement* last = orig->lastNodeOfStmt();
            while (orig != last)
            {
                orig->setVariant(orig->variant() * -1);
                orig = orig->lexNext();
            }
            wasRemoved = true;
            removed[file].insert(rem);
        }
    }

    return wasRemoved;
}

static bool removeThisFunctions(const string& file, FuncInfo* toRem)
{
    vector<FuncInfo*> tmp = { toRem };
    map<FuncInfo*, set<FuncInfo*>> info;
    return removeThisFunctions(file, info, tmp);
}

static void restoreFunctions(const string &file)
{
    for (auto& elem : removed[file])
    {
        SgStatement* orig = elem->funcPointer->GetOriginal();
        SgStatement* last = orig->lastNodeOfStmt();
        while (orig != last)
        {
            orig->setVariant(orig->variant() * -1);
            orig = orig->lexNext();
        }
    }
    removed[file].clear();
}

static string clearName(const string &in)
{
    char fromChar;
    if (in.find('.') == string::npos)
    {
        if (in.find("::") == string::npos)
            return in;
        else
            fromChar = ':';
    }
    else
        fromChar = '.';

    string ret = in;
    auto it = ret.rfind(fromChar);
    if (it == string::npos)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    ret = ret.substr(it + 1);
    return ret;
}

static void createCopies(const string &file, const string &baseName, const  map<FuncInfo*, set<FuncInfo*>> &uniqCopies)
{
    int newNum = 0;
    for (auto& toCopy : uniqCopies)
    {
        const string newName = newNum > 0 ? baseName + "_spfr_" + to_string(newNum) : baseName;
        ++newNum;

        SgStatement* duplicated = duplicateProcedure(toCopy.first->funcPointer->GetOriginal(), clearName(newName), true, true);
        if (duplicated->variant() == FUNC_HEDR)
            changeFuncNameInDvmDirs(clearName(newName), toCopy.first->funcPointer->GetOriginal()->symbol()->identifier(), duplicated);

        copied[toCopy.first->funcPointer->GetOriginal()->fileName()].insert(duplicated);
        newNamesOfUniqCopies[toCopy.first->funcName] = newName;
        for (auto &theSame : toCopy.second)
            newNamesOfUniqCopies[theSame->funcName] = newName;

        removeThisFunctions(file, toCopy.first);
    }
}

static void doReplacements(SgSymbol* s, map<SgSymbol*, pair<string, string>> &replaced)
{
    auto itR = replaced.find(s);
    if (itR == replaced.end())
    {
        auto it = newNamesOfUniqCopies.find(s->identifier());
        if (it != newNamesOfUniqCopies.end())
        {
            s->changeName(it->second.c_str());
            replaced.insert(itR, make_pair(s, *it));
        }
        else // for modules and contains?
        {
            vector<string> toReplace;
            string ident = s->identifier();
            for (auto& elem : newNamesOfUniqCopies)
                if (clearName(elem.first) == ident)
                    toReplace.push_back(elem.second);

            if (toReplace.size() == 1)
            {
                s->changeName(clearName(toReplace[0]).c_str());
                replaced.insert(itR, make_pair(s, make_pair(ident, toReplace[0])));
            }
        }
    }
}

static void doReplacements(SgExpression* ex, map<SgSymbol*, pair<string, string>> *replaced)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            SgSymbol* s = ex->symbol();
            if (replaced)
                doReplacements(s, *replaced);
            else
                doReplacements(s, ::replaced);
        }

        doReplacements(ex->lhs(), replaced);
        doReplacements(ex->rhs(), replaced);
    }
}

static void doReplacements(SgStatement* st, SgStatement* last, map<SgSymbol*, pair<string, string>> *replaced = NULL)
{
    while (st != last)
    {
        if (st->variant() == PROC_STAT)
        {
            SgSymbol *s = st->symbol();

            if (replaced)
                doReplacements(s, *replaced);
            else
                doReplacements(s, ::replaced);
        }
        for (int z = 0; z < 3; ++z)
            doReplacements(st->expr(z), replaced);

        st = st->lexNext();
    }
}

static void hiddenInterfaces(SgStatement* func)
{
    SgStatement* last = func;
    const string fileName = func->fileName();

    for (auto st = func->lexNext(); st != last; st = st->lexNext())
    {
        if (st->variant() == CONTAINS_STMT)
            break;
        if (isSgExecutableStatement(st) && !isDVM_stat(st) && !isSPF_stat(st))
            break;

        if (st->variant() == INTERFACE_STMT)
        {
            int total = 0;
            map<string, set<SgStatement*>> objects;
            SgStatement* iEnd = st->lastNodeOfStmt();
            for (auto iSt = st->lexNext(); iSt != iEnd; iSt = iSt->lexNext())
            {
                if (iSt->variant() == PROC_HEDR || iSt->variant() == FUNC_HEDR)
                    objects[iSt->symbol()->identifier()].insert(iSt);
                total++;
                iSt = iSt->lastNodeOfStmt();
            }

            if (objects.size() != total)
            {
                for (auto& uniq : objects)
                {
                    int first = 0;
                    for (auto& obj : uniq.second)
                    {
                        if (first)
                        {
                            obj->setVariant(-obj->variant());
                            hiddenInterfaceBlocks[fileName].insert(obj);
                            --total;
                        }
                        ++first;
                    }
                }
            }

            if (total == 0)
            {
                st->setVariant(-st->variant());
                hiddenInterfaceBlocks[fileName].insert(st);
            }
            st = iEnd;
        }
    }
}

static void replaceNewNames(const map<string, vector<FuncInfo*>> &allFuncs)
{
    for (auto& byfile : allFuncs)
    {
        if (SgFile::switchToFile(byfile.first) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& func : byfile.second)
        {
            if (func->funcPointer->GetOriginal()->variant() < 0)
                continue;

            SgStatement* p = func->funcPointer->GetOriginal();
            doReplacements(p, p->lastNodeOfStmt());
            hiddenInterfaces(p);
        }

        map<SgSymbol*, pair<string, string>> replaced_tmp;
        if (copied.find(byfile.first) != copied.end())
        {
            for (auto& func : copied[byfile.first])
                doReplacements(func, func->lastNodeOfStmt(), &replaced_tmp);
        }
    }
}

void removeCopies(const map<string, vector<FuncInfo*>>& allFuncs)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto& byFile : allFuncs)
        {
            string fileS = byFile.first;
            if (SgFile::switchToFile(fileS) == -1)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            for (auto& func : byFile.second)
            {
                if (func->fullCopiesOfThisFunction.size() && removed[fileS].find(func) == removed[fileS].end())
                {
                    map<FuncInfo*, set<FuncInfo*>> uniqCopies = getUniqCopies(func->fullCopiesOfThisFunction);
                    if (uniqCopies.size() == func->fullCopiesOfThisFunction.size())
                        continue;
                    if (uniqCopies.size() == 0)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    bool ret1 = removeThisFunctions(fileS, uniqCopies, func->fullCopiesOfThisFunction);
                    bool ret2 = removeThisFunctions(fileS, func);
                    changed = ret1 || ret2;
                    if (changed)
                        createCopies(fileS, func->funcName, uniqCopies);
                }
            }
        }
        replaceNewNames(allFuncs);
    }
}

void restoreCopies(SgFile* file)
{
    const string fileName = file->filename();

    restoreFunctions(fileName);
    for (auto& elem : copied[file->filename()])
        elem->deleteStmt();
    copied[file->filename()].clear();

    for (auto& elem : replaced)
        elem.first->changeName(elem.second.first.c_str());
    replaced.clear();
    newNamesOfUniqCopies.clear();

    auto it = hiddenInterfaceBlocks.find(fileName);
    if (it != hiddenInterfaceBlocks.end())
    {
        for (auto& obj : it->second)
            if (obj->variant() < 0)
                obj->setVariant(-obj->variant());

        hiddenInterfaceBlocks.erase(it);
    }
}
