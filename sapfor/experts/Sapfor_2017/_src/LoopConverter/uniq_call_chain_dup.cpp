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
            SgSymbol* par = callList->lhs()->symbol();
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
                SgSymbol *par = prog->parameter(z);                
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

//TODO: remove? not call
void extendWithFullCalls(map<FuncInfo*, set<FuncInfo*>> &groups, const map<string, FuncInfo*>& mapOfFunc)
{
    for (auto& elem : groups)
    {
        set<FuncInfo*> toUpdate;
        for (auto& inGroup : elem.second)
        {
            set<FuncInfo*> fullCalls = getFullCallsFrom(inGroup, mapOfFunc);
            toUpdate.insert(fullCalls.begin(), fullCalls.end());
        }
        elem.second.insert(toUpdate.begin(), toUpdate.end());
    }
}

static bool checkSymbName(const string &symbName)
{
    bool found = false;
    SgFile *oldFile = current_file;

    for (int i = 0; !found && (i < CurrentProject->numberOfFiles()); ++i)
    {
        SgFile *file = &(CurrentProject->file(i));
        found = ifSymbolExists(file, symbName);
    }

    if (SgFile::switchToFile(oldFile->filename()) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return found;
}

static string testAndCorrectName(string symbName)
{
    while (checkSymbName(symbName))
        symbName = symbName + "_";
    return symbName;
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

static void copyGroup(const map<string, FuncInfo*> &mapOfFunc, const vector<FuncInfo*> &toCopyGroups, map<FuncInfo*, callInfo> &funcInfoOfCall)
{
    if (toCopyGroups.size() == 0)
        return;

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

                string newName = testAndCorrectName(orig->identifier() + string("_spf_") + to_string(numCopy));
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
                    for (int z = 0; z < 3; ++z)
                        fillOrigCopyEx(origStat->expr(z), copyStat->expr(z), origCopyEx);
                }

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
                        //proc->setSymbol(*newS);
                    }
                    else if (places.second == FUNC_CALL)
                    {
                        SgExpression* proc = (SgExpression*)places.first;
                        SgStatement* parent = SgStatement::getStatmentByExpression(proc);
                        if (SgFile::switchToFile(parent->fileName()) == -1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        SgSymbol* newS = &proc->symbol()->copy();
                        newS->changeName(newName.c_str());
                        toChangeEx[parent->fileName()][proc] = newS;
                        //proc->setSymbol(*newS);
                    }
                    else
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

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

void duplicateFunctions(const map<string, vector<FuncInfo*>> &allFuncs, const map<DIST::Array*, set<DIST::Array*>>& arrayLinksByFuncCall)
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

    copyGroup(mapOfFunc, toCopyVec, funcInfoOfCall);
}
