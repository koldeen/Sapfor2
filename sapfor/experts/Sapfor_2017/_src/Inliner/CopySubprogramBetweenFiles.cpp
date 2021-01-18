#include "../Utils/leak_detector.h"

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "dvm.h"
#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
#include "../GraphCall/graph_calls_func.h"
#include "inliner.h"

using std::set;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using std::wstring;
using std::to_string;

#define DEB 0

static map<string, SgExpression*> createMapOfArgs(SgStatement* tempHedr, SgExpression* actualArgs)
{
    __spf_print(DEB, "------create map of vars------\n"); // DEBUG
    map<string, SgExpression*> vars;

    int i = 0;
    while (actualArgs)
    {
        auto actualArg = actualArgs->lhs();
        auto formalArg = ((SgFunctionSymb*)tempHedr->symbol())->parameter(i++);

        auto it = vars.find(formalArg->identifier());
        if (it == vars.end())
            vars.insert(it, make_pair(formalArg->identifier(), actualArg));
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        actualArgs = actualArgs->rhs();
    }

    return vars;
}

static map<string, map<string, SgSymbol*>> createdByFunc;
static map<string, int> createdVarCounterByName;
static map<string, map<string, pair<SgSymbol*, string>>> replacedConstRef;
static map<string, set<SgValueExp*>> dataDeclsByFunc;

static inline SgSymbol* createSymbAndDecl(const string& funcName, const string& varName, SgSymbol* newS, set<SgSymbol*>& newSymbols, SgType* type = NULL)
{
    int* count;
    if (createdVarCounterByName.find(varName) == createdVarCounterByName.end())
    {
        createdVarCounterByName[varName] = 0;
        count = &createdVarCounterByName[varName];
    }
    else
        count = &createdVarCounterByName[varName];

    const string base = varName + "_";
    int nextCount = checkSymbNameAndCorrect(base, count[0]);
    const string newName = base + to_string(nextCount);

    if (newS)
    {
        if (isSgConstantSymb(newS))
        {
            if (funcName != "null" && createdByFunc[funcName].find(varName) == createdByFunc[funcName].end() ||
                funcName == "null")
            {

                auto it = replacedConstRef[funcName].find(newS->identifier());
                if (it != replacedConstRef[funcName].end() && it->second.first->identifier() != it->second.second)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                if (it == replacedConstRef[funcName].end())
                {
                    //check replaces
                    SgSymbol* wasDone = NULL;
                    for (auto& elem : replacedConstRef[funcName])
                        if (elem.second.second == varName)
                            wasDone = elem.second.first;

                    if (wasDone == NULL)
                    {
                        replacedConstRef[funcName][newS->identifier()] = make_pair(newS, newName.c_str());
                        newS->changeName(newName.c_str());
                    }
                    else
                        newS = wasDone;
                }
            }
            else if (funcName != "null" && createdByFunc[funcName].find(varName) != createdByFunc[funcName].end())
            {
                ; //skip
            }
            else
                newS->changeName(newName.c_str());
        }
        else
            newS->changeName(newName.c_str());
    }
    else
        newS = findSymbolOrCreate(current_file, newName, type);

    if (newS->variant() == PROCEDURE_NAME)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (funcName != "null")
    {
        auto itS = createdByFunc[funcName].find(varName);
        if (itS == createdByFunc[funcName].end())
        {
            createdByFunc[funcName][varName] = newS;
            count[0] = nextCount;
        }
        else
            newS = itS->second;
    }
    //printf("newS %s = %d\n", newS->identifier(), newS->id());
    newSymbols.insert(newS);
    return newS;
}

static SgValueExp* oneExpr = NULL;
static SgValueExp* zeroExpr = NULL;
//TODO: for allocatable
static vector<SgExpression*> getLowBounds(SgSymbol* arrayS)
{   
    if (oneExpr == NULL)
        oneExpr = new SgValueExp(1);

    auto type = isSgArrayType(arrayS->type());
    auto list = type->getDimList();

    vector<SgExpression*> bounds;
    while (list)
    {
        SgExpression* elem = list->lhs();
        if (elem->variant() == DDOT)
            bounds.push_back(elem->lhs());
        else
            bounds.push_back(oneExpr);
        list = list->rhs();
    }
    return bounds;
}


//TODO: for allocatable
static vector<SgExpression*> getBoundsExpression(SgSymbol* arrayS)
{
    auto type = isSgArrayType(arrayS->type());
    auto list = type->getDimList();

    vector<SgExpression*> bounds;
    while (list)
    {
        SgExpression* elem = list->lhs();
        if (elem->variant() == DDOT)
            bounds.push_back(&(elem->rhs()->copy() -  elem->lhs()->copy() + *new SgValueExp(1)));
        else
            bounds.push_back(elem->copyPtr());
        list = list->rhs();
    }
    return bounds;
}

static SgArrayRefExp* addressPass(SgArrayRefExp* result, SgArrayRefExp* arrayExpOld, SgArrayRefExp* arrayExpNew,
                                  const vector<SgExpression*>& boundsOld, const vector<SgExpression*>& boundsNew,
                                  map<SgExpression*, string>& collection)
{
    //TODO: check dims position
    for (int z = 0; z < boundsOld.size(); ++z)
    {
        checkNull(boundsOld[z], convertFileName(__FILE__).c_str(), __LINE__);
        checkNull(boundsNew[z], convertFileName(__FILE__).c_str(), __LINE__);
        if (isEqExpressions(boundsOld[z], boundsNew[z], collection))
            result->addSubscript(arrayExpOld->subscript(z)->copy());
        else
            result->addSubscript(arrayExpOld->subscript(z)->copy() + (boundsNew[z]->copy() - boundsOld[z]->copy()));
    }
    return result;
}

static SgArrayRefExp* linearize(SgArrayRefExp* result, SgArrayRefExp* arrayExpOld, SgExpression* oldExp,
                                map<string, vector<pair<SgSymbol*, SgExpression*>>>& argVarsLinearForm,
                                const vector<SgExpression*>& boundsOld, const vector<SgExpression*>& boundsNew,
                                map<SgExpression*, string>& collection)
{
    const string arrayName = oldExp->symbol()->identifier();
    const int numOldSubs = arrayExpOld->numberOfSubscripts();

    auto itL = argVarsLinearForm.find(arrayName);
    if (itL == argVarsLinearForm.end())
    {
        vector<pair<SgSymbol*, SgExpression*>> newVars;
        int boundsN = 0;
        auto initDeclareBounds = getBoundsExpression(oldExp->symbol());
        for (int z = 0; z < boundsOld.size() - 1; ++z)
        {
            pair<SgSymbol*, SgExpression*> forDim;
            string dimName = "s_";
            int nextBoound = checkSymbNameAndCorrect(dimName, boundsN);
            dimName += to_string(nextBoound);

            forDim.first = new SgSymbol(VARIABLE_NAME, dimName.c_str());
            forDim.second = initDeclareBounds[z];
            newVars.push_back(forDim);
        }
        itL = argVarsLinearForm.insert(itL, make_pair(arrayName, newVars));
    }

    SgExpression* linearForm = NULL;
    if (numOldSubs != 0)
    {
        for (int z = 0; z < boundsOld.size(); ++z)
        {
            SgExpression* nextArg = &(arrayExpOld->subscript(z)->copy() - boundsOld[z]->copy());

            for (int p = 0; p < z; ++p)
                nextArg = &(*nextArg * *new SgVarRefExp(itL->second[p].first));

            if (linearForm)
                linearForm = &(*linearForm + *nextArg);
            else
                linearForm = nextArg;
        }

        int numS = result->numberOfSubscripts();
        if (!isEqExpressions(zeroExpr, boundsNew[0], collection) && numS == 0)
            linearForm = &(*linearForm + boundsNew[0]->copy());

        if (numS == 0)
            result->addSubscript(*linearForm);
        else if (numS == 1)
            result->replaceSubscripts(*result->subscript(0) + *linearForm);
        else // TODO
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    
    return result;
}

static SgExpression* doReplace(SgExpression* oldExp, SgExpression* newExp, map<SgExpression*, string>& collection, 
                               map<string, vector<pair<SgSymbol*, SgExpression*>>>& argVarsLinearForm)
{
    if (oneExpr == NULL)
        oneExpr = new SgValueExp(1);

    if (zeroExpr == NULL)
        zeroExpr = new SgValueExp(0);

    SgExpression* retVal = NULL;
    if (oldExp)        
    {
        if (oldExp->variant() == ARRAY_REF && oldExp->symbol() && oldExp->symbol()->type()->variant() == T_ARRAY)
        {
            if (newExp->variant() != ARRAY_REF)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            SgArrayRefExp* arrayExpOld = isSgArrayRefExp(oldExp);
            SgArrayRefExp* arrayExpNew = isSgArrayRefExp(newExp);

            //arrayExpOld->unparsestdout();
            //arrayExpNew->unparsestdout();

            auto boundsOld = getLowBounds(oldExp->symbol());
            auto boundsNew = getLowBounds(newExp->symbol());

            const int numOldSubs = arrayExpOld->numberOfSubscripts();
            const int numNewSubs = arrayExpNew->numberOfSubscripts();
            if (numNewSubs == 0)
            {
                SgArrayRefExp* result = (SgArrayRefExp*)arrayExpNew->copyPtr();
                if (boundsOld.size() != boundsNew.size() && boundsNew.size() != 1 && boundsOld.size() != 1)
                {
                    arrayExpOld->unparsestdout();
                    arrayExpNew->unparsestdout();
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                if (boundsNew.size() == 1 && boundsOld.size() > 1)
                    result = linearize(result, arrayExpOld, oldExp, argVarsLinearForm, boundsOld, boundsNew, collection);
                else if (boundsNew.size() > 1 && boundsOld.size() == 1)
                {
                    arrayExpOld->unparsestdout();
                    arrayExpNew->unparsestdout();
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
                else if (numOldSubs != 0)
                    result = addressPass(result, arrayExpOld, arrayExpNew, boundsOld, boundsNew, collection);
                retVal = result;
            }
            else if (numNewSubs >= numOldSubs && numOldSubs != 0)
            {
                SgArrayRefExp* result = new SgArrayRefExp(*arrayExpNew->symbol());
                if (boundsOld.size() > boundsNew.size())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                result = addressPass(result, arrayExpOld, arrayExpNew, boundsOld, boundsNew, collection);
                for (int z = 0; z < boundsNew.size() - boundsOld.size(); ++z)
                    result->addSubscript(arrayExpNew->subscript(boundsOld.size() + z)->copy());

                retVal = result;
            }
            else
            {
                if (boundsNew.size() == 1 && boundsOld.size() > 1)
                {
                    SgArrayRefExp* result = (SgArrayRefExp*)arrayExpNew->copyPtr();
                    retVal = linearize(result, arrayExpOld, oldExp, argVarsLinearForm, boundsOld, boundsNew, collection);
                }
                else
                {
                    retVal = newExp->copyPtr();
                    retVal->setLhs(oldExp->lhs());
                    retVal->setRhs(oldExp->rhs());
                }
            }
        }
        else
            retVal = newExp->copyPtr();
    }    
    if (retVal == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return retVal;
}

//return 0 - local, 1 - common, 2 - module
//TODO: common synonyms
static int isGlobal(SgStatement* st, SgSymbol* toCheckS, vector<SgSymbol*>* allInCommon = NULL, string* globalName = NULL)
{
    //by USE
    if (toCheckS != OriginalSymbol(toCheckS))
    {
        //TODO for module
        //globalName = 
        return 2;
    }

    const string toCheck = toCheckS->identifier();
    SgStatement* func = getFuncStat(st);
    map<string, vector<SgExpression*>> commonBlocksRef;
    getCommonBlocksRef(commonBlocksRef, func, func ? func->lastNodeOfStmt() : NULL);

    int isCommon = 0;
    for (auto& commonBlockRef : commonBlocksRef)
    {
        for (auto& commExp : commonBlockRef.second)
        {
            for (auto exp = commExp->lhs(); exp; exp = exp->rhs())
            {
                SgSymbol* varSymb = exp->lhs()->symbol();
                string varName = varSymb->identifier();

                if (toCheck == varName)
                {
                    if (globalName)
                        globalName[0] = commonBlockRef.first;
                    isCommon = 1;
                    break;
                }
            }
            if (isCommon == 1)
                break;
        }

        if (isCommon == 1 && allInCommon)
            for (auto& commExp : commonBlockRef.second)
                for (auto exp = commExp->lhs(); exp; exp = exp->rhs())
                    allInCommon[0].push_back(exp->lhs()->symbol());

        if (isCommon == 1)
            break;
    }
    return isCommon;
}

inline static void findAllConstRef(SgExpression* ex, set<SgSymbol*>& result)
{
    if (ex)
    {
        if (ex->variant() == CONST_REF)
        {
            result.insert(ex->symbol());
            auto constS = isSgConstantSymb(ex->symbol());
            if (!constS)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            auto val = constS->constantValue();
            if (!val)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            findAllConstRef(val, result);
        }

        findAllConstRef(ex->lhs(), result);
        findAllConstRef(ex->rhs(), result);
    }
}

static void detectTypeOfSymbol(const string& funcName, SgSymbol* s, int globalType, set<SgSymbol*>& newSymbols, 
                               const vector<SgSymbol*>& allInCommon, const string& globalName)
{
    if (newSymbols.find(s) == newSymbols.end())
    {
        char* newAttr = new char[globalName.size() + 1];
        strcpy(newAttr, globalName.c_str());
        if (globalType == 1)
        {
            if (allInCommon.size() == 0)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            int pos = 0;
            for (auto& commS : allInCommon)
            {
                commS->addAttribute(COMM_STAT, newAttr, sizeof(char*));
                int* posS = new int[1];
                posS[0] = pos;
                commS->addAttribute(COMM_LIST, posS, sizeof(int*));

                if (isSgArrayType(commS->type()))
                {
                    set<SgSymbol*> constInDecl;
                    auto arrT = isSgArrayType(commS->type());
                    findAllConstRef(arrT->getDimList(), constInDecl);

                    for (auto& elem : constInDecl)
                    {
                        auto itS = replacedConstRef[funcName].find(elem->identifier());
                        if (itS == replacedConstRef[funcName].end())
                        {
                            replacedConstRef[funcName][elem->identifier()] = make_pair(elem, elem->identifier());
                            newSymbols.insert(elem);
                        }
                    }
                }
                newSymbols.insert(commS);
                ++pos;
            }
        }
        else if (globalType == 2)
            s->addAttribute(MODULE_STMT, newAttr, sizeof(char*));
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        newSymbols.insert(s);
    }
}

static void replaceSymbInExp(SgStatement* st, SgExpression* exp, SgExpression* par, const int expIdx, const bool isLeft,
                             const map<string, SgExpression*>& argVars, map<string, SgSymbol*>& locVars, set<SgSymbol*>& newSymbols,
                             const string& funcName, SgSymbol*& newHedrSymb, map<SgExpression*, string>& collection,
                             map<string, vector<pair<SgSymbol*, SgExpression*>>>& argVarsLinearForm)
{
    if (exp)
    {
        replaceSymbInExp(st, exp->lhs(), exp, expIdx, true, argVars, locVars, newSymbols, funcName, newHedrSymb, collection, argVarsLinearForm);
        replaceSymbInExp(st, exp->rhs(), exp, expIdx, false, argVars, locVars, newSymbols, funcName, newHedrSymb, collection, argVarsLinearForm);

        const int var = exp->variant();
        if (var == FUNC_CALL && exp->symbol())
            if (!isIntrinsicFunctionName(exp->symbol()->identifier()))
                newSymbols.insert(exp->symbol());

        if ((var == VAR_REF || var == ARRAY_REF || var == CONST_REF || var == IOACCESS) && exp->symbol())
        {
            const string varName = exp->symbol()->identifier();
            auto it = argVars.find(varName);
            if (it != argVars.end())
            {
                SgExpression* copy = NULL;
                if (!par)
                {
                    copy = doReplace(st->expr(expIdx), it->second, collection, argVarsLinearForm);
                    st->setExpression(expIdx, copy);
                }
                else
                {
                    copy = doReplace((isLeft ? par->lhs() : par->rhs()), it->second, collection, argVarsLinearForm);
                    isLeft ? par->setLhs(copy) : par->setRhs(copy);
                }
            }
            else
            {
                auto expS = exp->symbol();
                string globalName;
                vector<SgSymbol*> allInCommon;
                int globalType = isGlobal(st, expS, &allInCommon, &globalName);
                if (globalType == 0)
                {
                    auto it = locVars.find(varName);
                    if (it == locVars.end())
                    {
                        auto symb = createSymbAndDecl(funcName, varName, &expS->copy(), newSymbols);
                        it = locVars.insert(it, make_pair(varName, symb));

                        if (varName == funcName && !newHedrSymb)
                            newHedrSymb = symb;

                        if (newHedrSymb != symb)
                        {
                            auto arrType = isSgArrayType(symb->type());
                            if (arrType)
                            {
                                auto allList = arrType->getDimList();
                                while (allList)
                                {
                                    auto list = allList;
                                    if (list && list->lhs())
                                        replaceSymbInExp(NULL, list->lhs(), list, -1, true, argVars, locVars, newSymbols, funcName, newHedrSymb, collection, argVarsLinearForm);
                                    allList = allList->rhs();
                                }
                            }
                        }
                    }
                    exp->setSymbol(*it->second);
                }
                else
                    detectTypeOfSymbol(funcName, expS, globalType, newSymbols, allInCommon, globalName);
            }
        }
    }
}

inline static void replaceSymbInStat(SgStatement* st, SgStatement* tempHedr,
                                     const map<string, SgExpression*>& argVars, map<string, SgSymbol*>& locVars, set<SgSymbol*>& newSymbols,
                                     const string& funcName, SgSymbol*& newHedrSymb, map<SgExpression*, string>& collection,
                                     map<string, vector<pair<SgSymbol*, SgExpression*>>>& argVarsLinearForm)
{
    if (st->symbol() && st->variant() != PROC_STAT)
    {
        auto s = st->symbol();        
        const string varName = s->identifier();
        auto it = argVars.find(varName);
        if (it != argVars.end())
            st->setSymbol(*it->second->symbol());
        else
        {
            string globalName;
            vector<SgSymbol*> allInCommon;
            int globalType = isGlobal(st, s, &allInCommon, &globalName);
            if (globalType == 0)
            {
                auto it = locVars.find(varName);
                if (it == locVars.end())
                {
                    auto symb = createSymbAndDecl(funcName, varName, &s->copy(), newSymbols);
                    it = locVars.insert(it, make_pair(varName, symb));

                    if (varName == funcName && !newHedrSymb)
                        newHedrSymb = symb;
                }
                st->setSymbol(*it->second);
            }
            else
                detectTypeOfSymbol(funcName, s, globalType, newSymbols, allInCommon, globalName);
        }
    }

    for (int i = 0; i < 3; ++i)
        replaceSymbInExp(st, st->expr(i), NULL, i, false, argVars, locVars, newSymbols, funcName, newHedrSymb, collection, argVarsLinearForm);
}

static inline void remapVars(SgStatement* tempHedr,
                             const map<string, SgExpression*>& argVars, map<string, SgSymbol*>& locVars,
                             set<SgSymbol*>& newSymbols, const string& funcName, SgSymbol*& newHedrSymb)
{    
    map<SgExpression*, string> collection;
    map<string, vector<pair<SgSymbol*, SgExpression*>>> argVarsLinearForm;

    for (auto st = tempHedr; st != tempHedr->lastNodeOfStmt(); st = st->lexNext())
    {
        if (st->variant() == CONTAINS_STMT)
            break;

        if (isSgExecutableStatement(st))
            replaceSymbInStat(st, tempHedr, argVars, locVars, newSymbols, funcName, newHedrSymb, collection, argVarsLinearForm);
        else
            if (st->variant() == DATA_DECL)
                dataDeclsByFunc[funcName].insert((SgValueExp*)st->expr(0));
    }

    if (argVarsLinearForm.size())
    {
        SgStatement* lastDecl = tempHedr;
        for (auto st = tempHedr; st != tempHedr->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;

            auto next = st->lexNext();

            if (next && isSgExecutableStatement(next))
            {
                lastDecl = st;
                break;
            }
        }

        SgExpression* tmp = new SgExprListExp();
        map<string, vector<pair<SgSymbol*, SgExpression*>>> dummy;
        for (auto& bySymb : argVarsLinearForm)
        {
            for (auto& elem : bySymb.second)
            {
                newSymbols.insert(elem.first);
               
                tmp->setLhs(elem.second);
                
                replaceSymbInExp(NULL, tmp->lhs(), tmp, -1, true, argVars, locVars, newSymbols, funcName, newHedrSymb, collection, dummy);
                
                SgAssignStmt* init = new SgAssignStmt(*new SgVarRefExp(elem.first), *tmp->lhs());
                lastDecl->insertStmtAfter(*init, *tempHedr);
            }
        }
    }
}

static void insert(SgStatement* callSt, SgStatement* tempHedr, SgStatement* begin, SgSymbol* newHedrSymb, vector<SgStatement*>& toDelete)
{
    auto prev = callSt->lexPrev();
    auto last = tempHedr->lastNodeOfStmt();

    auto firstExec = begin->lexNext();
    for (; firstExec && firstExec != tempHedr->lastNodeOfStmt(); firstExec = firstExec->lexNext())
        if (isSgExecutableStatement(firstExec) && firstExec->variant() != FORMAT_STAT)
            break;
    checkNull(firstExec, convertFileName(__FILE__).c_str(), __LINE__);

    tempHedr->extractStmt();

    prev->insertStmtAfter(*firstExec, *callSt->controlParent());
    for (auto st = prev->lexNext(); st != callSt; st = st->lexNext())
    {
        if (st->lineNumber() > 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        st->setlineNumber(getNextNegativeLineNumber());
    }

    last->extractStmt();

    if (callSt->variant() == PROC_STAT)
        toDelete.push_back(callSt);
    else
    {
        callSt->setExpression(1, new SgExpression(VAR_REF));
        callSt->expr(1)->setSymbol(newHedrSymb);
    }
}

static int clean(const string& funcName, SgStatement* funcSt, const map<string, FuncInfo*>& funcMap, vector<SgStatement*>& toDelete)
{
    // site-independent transformation
    int gotoLabelId = -1;
    SgLabel* contLab = NULL;
    SgStatement* cont = NULL;

    // return goto label if entry function is called
    auto it = funcMap.find(funcName);
    if (it != funcMap.end() && it->second->funcPointer->variant() == ENTRY_STAT)
    {
        auto test = it->second->funcPointer->variant();
        gotoLabelId = getNextFreeLabel();
    }

    // TODO: move all ENTRY points to the top of the subprogram
    for (auto st = funcSt; st != funcSt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
    {
        switch (st->variant())
        {
        case ENTRY_STAT:
        {
            SgLabel* gotoLab = new SgLabel(getNextFreeLabel());
            SgContinueStmt* contSt = new SgContinueStmt();
            contSt->setLabel(*gotoLab);
            st->insertStmtBefore(*contSt, *st->controlParent());

            // return goto label if entry function is called
            auto test = st->symbol();
            if (st->symbol()->identifier() == funcName)
                gotoLabelId = gotoLab->getLabNumber();

            toDelete.push_back(st);
            break;
        }
        case RETURN_STAT:
        {
            if (st->lexNext()->variant() == CONTROL_END && funcSt->lastNodeOfStmt() == st->lexNext())
            {
                toDelete.push_back(st);
                break;
            }

            if (!cont) // create CONT_STAT
            {
                contLab = new SgLabel(getNextFreeLabel());
                cont = new SgStatement(CONT_STAT);
                cont->setLabel(*contLab);
                auto test = funcSt->lastNodeOfStmt();
                funcSt->lastNodeOfStmt()->insertStmtBefore(*cont, *funcSt);
            }

            SgGotoStmt* gotoSt = new SgGotoStmt(*contLab);
            st->insertStmtBefore(*gotoSt, *st->controlParent());

            toDelete.push_back(st);
            break;
        }
        default:
            break;
        }
    }

    // TODO: move all FORMAT statements into the top level routine

    // TODO: remap all local subprogram variables by creating new unconflicting top level variables
    return gotoLabelId;
}

// true if inserted
static inline bool insert(SgFile* file, SgStatement* callSt, SgStatement* funcStat,
                          SgExpression* args, set<SgSymbol*>& newSymbols, 
                          const map<string, FuncInfo*>& funcMap, vector<SgStatement*>& toDelete)
{
    SgSymbol* funcSymb = funcStat->symbol();
    bool isEntry = false;
    SgSymbol* entrySymb = NULL;

    SgStatement* tempHedr = NULL;
    SgSymbol* tempSymb = NULL;

    // TODO: check arguments
    //if (!TestConformability())
    //    return false;

    __spf_print(DEB, "------creating template------\n"); // DEBUG
    // 2.a create function template
    auto funcSt = funcSymb->body();
    if (funcSt->variant() == ENTRY_STAT)
    {
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        //TODO:
        isEntry = true;
        entrySymb = funcSymb;

        while (funcSt && funcSt->variant() != FUNC_HEDR)
            funcSt = funcSt->lexPrev();
        checkNull(funcSt, convertFileName(__FILE__).c_str(), __LINE__);
        funcSymb = funcSt->symbol();
    }

    // insert template after global statement in current file
    tempHedr = duplicateProcedure(funcStat, NULL, true, false, false);
    tempSymb = tempHedr->symbol();

    if (string(tempSymb->identifier()) != funcSymb->identifier())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    // set first inserting statement
    SgStatement* begin = NULL;
    if (isEntry)
    {
        for (auto st = tempHedr; st != tempHedr->lastNodeOfStmt(); st = st->lexNext())
            if (st->variant() == ENTRY_STAT && st->symbol()->identifier() == string(entrySymb->identifier()))
                begin = st;
    }
    else
        begin = tempHedr;
    checkNull(begin, convertFileName(__FILE__).c_str(), __LINE__);

    // create map of arguments
    SgSymbol* newHedrSymb = NULL; // requires for function with return variable
    map<string, SgExpression*> argVars = createMapOfArgs(tempHedr, args); // local argument variable -> top argument variable    
    map<string, SgSymbol*> locVars; // local varname -> new local var

    remapVars(tempHedr, argVars, locVars, newSymbols, begin->symbol()->identifier(), newHedrSymb);

    if (!newHedrSymb && tempSymb->variant() == FUNCTION_NAME) // if no textual use of return variable, create new anyway
        newHedrSymb = createSymbAndDecl("null", string(tempSymb->identifier()) + "_spf", &tempSymb->copy(), newSymbols);

    // clean function
    int gotoLabId = clean(funcSymb->identifier(), tempHedr, funcMap, toDelete);
    if (gotoLabId != -1)
    {
        SgLabel* gotoLab = new SgLabel(gotoLabId);
        SgGotoStmt* gotoSt = new SgGotoStmt(*gotoLab);
        callSt->insertStmtBefore(*gotoSt, *callSt->controlParent());
    }

    /*
    // 2.b perform site_specific transformations
    if (st->variant() == ASSIGN_STAT)
        RemapFunctionResultVar(stmt->expr(0), scopy);
    ConformActualAndFormalParameters(scopy, args, stmt);
    */

    // 2.c
    /*
    // 2.d transform all references to subprogram variables to "top level" form
    expanded_stmt = TranslateSubprogramReferences(header_work);

    // 2.e insert template
    */
    insert(callSt, tempHedr, begin, newHedrSymb, toDelete);
    return true;
}

static inline void replaceCall(SgExpression* exp, SgExpression* par, const int i, const bool lhs,
                               SgStatement* callSt, set<SgSymbol*>& newSymbols, SgStatement* insertPlace)
{
    // create new call variable for this call and its declaration
    SgSymbol* v = createSymbAndDecl("null", "arg", &exp->symbol()->copy(), newSymbols);

    SgAssignStmt* assign = new SgAssignStmt(*new SgVarRefExp(*v), *exp->copyPtr());
    assign->setlineNumber(getNextNegativeLineNumber());
    insertPlace->insertStmtBefore(*assign, *callSt->controlParent());

    // replace function call to a new variable
    if (!par)
        callSt->setExpression(i, new SgVarRefExp(*v));
    else
        lhs ? par->setLhs(new SgVarRefExp(*v)) : par->setRhs(new SgVarRefExp(*v));
}

static void recFindFuncCall(SgExpression* exp, SgExpression* par, const int i, const bool lhs,
                            const string& funcName, bool& foundCall,
                            SgStatement* callSt, set<SgSymbol*>& newSymbols, SgStatement* insertPlace)
{
    if (exp)
    {
        recFindFuncCall(exp->rhs(), exp, i, false, funcName, foundCall, callSt, newSymbols, insertPlace);
        recFindFuncCall(exp->lhs(), exp, i, true, funcName, foundCall, callSt, newSymbols, insertPlace);

        if (exp->variant() == FUNC_CALL && exp->symbol() && exp->symbol()->identifier() == funcName)
        {
            foundCall = true;
            if (par) // do not extract external func call
                replaceCall(exp, par, i, lhs, callSt, newSymbols, insertPlace);
        }
    }
}

static int ParameterType(SgExpression* exp, SgStatement* st)
{
    if (isSgVarRefExp(exp) ||                                    // scalar variable
        isSgArrayRefExp(exp) ||                                  // array variable
        exp->variant() == CONST_REF ||                           // symbol (named) constant
        isSgValueExp(exp))// && exp->type()->variant() != T_STRING) // literal constant
        return 1;
    return 0;
}

static inline void PrecalculateExpression(SgSymbol* sp, SgExpression* e, SgStatement* stmt)
{
    SgStatement* newst;
    newst = new SgAssignStmt(*new SgVarRefExp(sp), *e);
    newst->setlineNumber(getNextNegativeLineNumber());
    stmt->insertStmtBefore(*newst, *stmt->controlParent());
}

static SgType* SgTypeFromFile(SgFile* f, int type)
{
    SgType* t;
    for (t = f->firstType(); t; t = t->next())
        if (t->variant() == type)
            return t;

    return new SgType(type);
}

//TODO: more types
static SgType* getTrueType(SgType* inExp, parF funcParType)
{
    if (funcParType == SCALAR_FLOAT_T)
        return SgTypeFloat();
    else if (funcParType == SCALAR_DOUBLE_T)
        return SgTypeDouble();
    else if (funcParType == SCALAR_CMPLX_FLOAT_T)
        return SgTypeFromFile(current_file, T_COMPLEX);
    else if (funcParType == SCALAR_CMPLX_DOUBLE_T)
        return SgTypeFromFile(current_file, T_DCOMPLEX);
    else
        return inExp;
}

static inline void PrecalculateActualParameters(SgStatement* st, SgSymbol* s, SgExpression* e, 
                                                const FuncInfo* func, set<SgSymbol*>& newSymbols)
{
    // Precalculate actual parameter expressions
    // e - actual parameter list
    SgExpression* el;
    SgSymbol* sp;
    if (!e) 
        return;

//TODO: added exclude list!
    //if (is_NoExpansionFunction(s)) 
        //return;

    int i = 0;
    for (el = e; el; el = el->rhs(), i++)
    {
        switch (ParameterType(el->lhs(), st))
        {
        case 1:
            break; // actual parameter can be accessed by reference
        //case 2:  PrecalculateSubscripts(el->lhs(),stmt); break;
        default:            
            sp = createSymbAndDecl("null", "arg", NULL, newSymbols, getTrueType(el->lhs()->type(), func->funcParams.parametersT[i]));
            PrecalculateExpression(sp, el->lhs(), st); //to support access by reference 
            el->setLhs(new SgVarRefExp(sp)); //replace actual parameter expression by 'sp' reference
            break;
        }
    }
}

static bool run_inliner(const map<string, FuncInfo*>& funcMap, set<SgStatement*>& toInsert, map<string, vector<Messages>>& SPF_messages,
                        const string& fileName, const FuncInfo* func, map<SgStatement*, set<SgSymbol*>>& newSymbsToDeclare)
{
    bool isInlined = false;
    const string& funcName = func->funcName;
    for (auto& callSt : toInsert)
    {
        SgStatement* insertPlace = callSt;
        SgStatement* currentFunc = getFuncStat(callSt);

        SgStatement* funcStat = func->funcPointer->GetOriginal();
        set<SgSymbol*> newSymbols;

        bool foundCall = false;

        if (!callSt || !isSgExecutableStatement(callSt))
        {
            wstring messageE, messageR;
            __spf_printToLongBuf(messageE, L"It is allowed to inline function only at execution code section.");
#ifdef _WIN32
            __spf_printToLongBuf(messageR, R177);
#endif
            getObjectForFileFromMap(fileName.c_str(), SPF_messages).push_back(Messages(ERROR, insertPlace->lineNumber(), messageR, messageE, 2011));
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }

        __spf_print(DEB, "------start inliner-----\n"); // DEBUG        
        __spf_print(DEB, "---statement preprocessing---\n"); // DEBUG

        //simple convertation
        if (callSt->controlParent()->variant() == LOGIF_NODE)
            callSt->controlParent()->setVariant(IF_NODE);

        SgStatement* begin = callSt->lexPrev();
        SgStatement* end = callSt->lexNext();

        // 1.a: make statement preprocessing
        // if call statement contains several inlining functions, split every such call
        for (int i = 0; i < 3; ++i)
            recFindFuncCall(callSt->expr(i), NULL, i, false, funcName, foundCall, callSt, newSymbols, insertPlace);

        __spf_print(DEB, "---argument preprocessing---\n"); // DEBUG
        // 1.b: make argument preprocessing        
        checkNull(begin, convertFileName(__FILE__).c_str(), __LINE__);

        // if call statement has any expression as its artument, split this expression for separate statement
        // if call statement has any function as its argument, split this call
        for (auto st = begin->lexNext(); st != end; st = st->lexNext())
        {
            if (st->variant() == ASSIGN_STAT)
            {
                auto s = st->expr(1)->symbol();
                if (s && s->identifier() == funcName)
                    if (isSgVarRefExp(st->expr(0)) || isSgArrayRefExp(st->expr(0)) && !isSgArrayType(st->expr(0)->type()))
                        PrecalculateActualParameters(st, s, st->expr(1)->lhs(), func, newSymbols);                
            }
            else if (st->variant() == PROC_STAT)
            {
                if (st->symbol() && st->symbol()->identifier() == funcName)
                {
                    foundCall = true;
                    if (st->expr(0))
                        PrecalculateActualParameters(st, st->symbol(), st->expr(0), func, newSymbols);
                }
            }
        }

        __spf_print(DEB, "---start inlining---\n"); // DEBUG
        // 2. create function template to modify and insert it
        if (foundCall)
        {
            bool change = true;

            while (change)
            {
                change = false;
                vector<SgStatement*> toDelete;
                for (auto st = begin->lexNext(); st != end; st = st->lexNext())
                {
                    switch (st->variant())
                    {
                    case ASSIGN_STAT:
                    {
                        auto rPart = st->expr(1);
                        if (rPart->variant() == FUNC_CALL && rPart->symbol() && rPart->symbol()->identifier() == funcName)
                        {
                            bool doInline = insert(current_file, st, funcStat, rPart->lhs(), newSymbols, funcMap, toDelete);
                            change |= doInline;
                            isInlined |= doInline;
                        }
                    }
                    continue;
                    case PROC_STAT:
                        if (st->symbol() && st->symbol()->identifier() == funcName)
                        {
                            bool doInline = insert(current_file, st, funcStat, st->expr(0), newSymbols, funcMap, toDelete);
                            change |= doInline;
                            isInlined |= doInline;
                        }
                        continue;
                    default:
                        continue;
                    }
                }

                for (auto& st : toDelete)
                    st->extractStmt();
            }            
        }

        newSymbsToDeclare[currentFunc].insert(newSymbols.begin(), newSymbols.end());
    }

    return isInlined;
}

static vector<pair<SgStatement*, SgStatement*>> getNextBounds(SgStatement* point)
{
    vector<pair<SgStatement*, SgStatement*>> parts;
    pair<SgStatement*, SgStatement*> newPart;
    bool sectionStarted = false;

    for (auto st = point; st != point->lastNodeOfStmt(); st = st->lexNext())
    {
        if (st->variant() == CONTAINS_STMT)
            break;

        if (st->variant() == GLOBAL)
        {
            if (!sectionStarted)
            {
                newPart.first = st;
                sectionStarted = true;
            }
            else if (sectionStarted)
            {
                newPart.second = st;
                parts.push_back(newPart);
                sectionStarted = false;
            }
        }
    }
    if (sectionStarted)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return parts;
}

static void fillNewFunctions(SgExpression* ex, SgStatement* main,
                             map<FuncInfo*, set<SgStatement*>>& nextInfo,
                             const map<string, FuncInfo*>& funcMap)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
            if (funcMap.find(ex->symbol()->identifier()) != funcMap.end())
                nextInfo[funcMap.at(ex->symbol()->identifier())].insert(main);

        fillNewFunctions(ex->lhs(), main, nextInfo, funcMap);
        fillNewFunctions(ex->rhs(), main, nextInfo, funcMap);
    }
}

static void fillNewFunctions(SgStatement* begin, SgStatement* end,
                             map<FuncInfo*, set<SgStatement*>>& nextInfo, 
                             const map<string, FuncInfo*>& funcMap)
{
    for (auto st = begin; st != end; st = st->lexNext())
    {
        if (st->variant() == PROC_STAT)
            if (funcMap.find(st->symbol()->identifier()) != funcMap.end())
                nextInfo[funcMap.at(st->symbol()->identifier())].insert(st);

        for (int z = 0; z < 3; ++z)
            fillNewFunctions(st->expr(z), st, nextInfo, funcMap);
    }
}

static map<FuncInfo*, set<SgStatement*>> fillNextDeep(const set<SgStatement*>& insertedIn, const map<string, FuncInfo*>& funcMap)
{
    map<FuncInfo*, set<SgStatement*>> nextInfo;

    for (auto& point : insertedIn)
        for (auto& part : getNextBounds(point))
            fillNewFunctions(part.first, part.second, nextInfo, funcMap);

    return nextInfo;
}

bool inliner(const string& fileName_in, const string& funcName, const int lineNumber,
             const map<string, vector<FuncInfo*>>& allFuncInfo, map<string, vector<Messages>>& SPF_messages, 
             map<SgStatement*, set<SgSymbol*>>& newSymbsToDeclare, int deepLvl)
{   
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    auto func = getFuncInfo(funcMap, funcName);
    const string& fileName = (fileName_in == "") ? func->fileName : fileName_in;

    if (func && !func->doNotInline)
    {
        if (SgFile::switchToFile(fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        //TODO:
        // now function is expected to be declared in the target file
        set<SgStatement*> toInsert;
        if (lineNumber > 0)
        {
            SgStatement* callSt = SgStatement::getStatementByFileAndLine(fileName, lineNumber);
            if (callSt)
                toInsert.insert(callSt);
        }
        else
        {
            for (auto& callTo : func->callsTo)
            {
                for (auto& callFrom : callTo->detailCallsFrom)
                {
                    if (callFrom.first == funcName)
                    {
                        SgStatement* callSt = SgStatement::getStatementByFileAndLine(fileName, callFrom.second);
                        if (callSt)
                            toInsert.insert(callSt);
                    }
                }
            }
        }

        set<SgStatement*> insertedIn;
        set<SgStatement*> markers;
        for (auto& elem : toInsert)
        {
            bool dontInline = false;
            for (int k = 0; k < elem->numberOfAttributes(); ++k)
                if (elem->getAttribute(k)->getAttributeType() == BOOL_VAL)
                    dontInline = true;

            if (dontInline)
            {
                __spf_print(1, " skip call in statement with line %d by attribute\n", elem->lineNumber());
                continue;
            }

            insertedIn.insert(getFuncStat(elem));
            //insert bounds
            auto cp = elem->controlParent();
            auto boundAfter = new SgStatement(GLOBAL);
            auto boundBefore = new SgStatement(GLOBAL);

            elem->insertStmtBefore(*boundAfter, *cp);
            elem->insertStmtAfter(*boundBefore, *cp);

            markers.insert(boundAfter);
            markers.insert(boundBefore);
        }

        if (markers.size() == 0)
            return 0;

        __spf_print(1, "INLINE %s\n", func->funcName.c_str());
        //1 level
        bool isInlined = run_inliner(funcMap, toInsert, SPF_messages, fileName, func, newSymbsToDeclare);

        if (deepLvl >= 0 && isInlined)
        {
            int currDeep = 0;
            bool changed = true;
            while (changed)
            {
                changed = false;
                currDeep++;
                if (deepLvl > 0 && deepLvl <= currDeep)
                    break;

                for (auto& next : fillNextDeep(insertedIn, funcMap))
                {
                    for (int p = 0; p < currDeep; ++p)
                        __spf_print(1, "  ");

                    if (next.first->doNotInline)
                    {
                        __spf_print(1, "skip %s by flag\n", next.first->funcName.c_str());
                        continue;
                    }
                    __spf_print(1, "INLINE %s\n", next.first->funcName.c_str());
                    bool isInlined = run_inliner(funcMap, next.second, SPF_messages, fileName, next.first, newSymbsToDeclare);
                    changed |= isInlined;
                }
            }
        }

        for (auto& marker : markers)
            marker->extractStmt();
    }
    return true;
}

bool inliner(const string& allInFunc, const map<string, vector<FuncInfo*>>& allFuncInfo, 
             map<string, vector<Messages>>& SPF_messages,
             map<SgStatement*, set<SgSymbol*>>& newSymbsToDeclare,
             int deepLvl)
{
    bool result = true;
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    auto func = getFuncInfo(funcMap, allInFunc);
    if (func && !func->doNotInline)
    {
        if (SgFile::switchToFile(func->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& callFrom : func->detailCallsFrom)
        {
            bool res = inliner("", callFrom.first, callFrom.second, allFuncInfo, SPF_messages, newSymbsToDeclare, deepLvl);
            result = result && res;
        }
    }
    return result;
}

static vector<SgSymbol*> sortConstRefs(const map<string, SgSymbol*>& constRefs)
{
    map<SgSymbol*, set<string>> deps;
    map<SgSymbol*, string> constRefByFunc;
    for (auto& byF : replacedConstRef)
        for (auto& s : byF.second)
            constRefByFunc[s.second.first] = byF.first;

    bool printInternal = false;
    for (auto& elem : constRefs)
    {
        SgSymbol* s = elem.second;
        string inFunc = "";
        if (constRefByFunc.find(s) == constRefByFunc.end())
        {
            __spf_print(1, " const not found '%s' with id %d\n", s->identifier(), s->id());
            printInternal = true;
            continue;
        }
        inFunc = constRefByFunc[s];
        map<string, pair<SgSymbol*, string>>& byFuncRefpl = replacedConstRef[inFunc];

        deps[s] = set<string>();
        set<SgSymbol*> tmp;
        findAllConstRef(isSgConstantSymb(elem.second)->constantValue(), tmp);
        for (auto& ref : tmp)
        {
            auto itS = byFuncRefpl.find(ref->identifier());
            if (itS != byFuncRefpl.end())
            {
                auto newName = itS->second.second.c_str();
                ref->changeName(newName);
                deps[elem.second].insert(newName);
            }
            else
                deps[s].insert(ref->identifier());
        }
    }

    if (printInternal)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    set<string> added;
    vector<SgSymbol*> result;
    for (auto& elem : deps)
    {
        bool existInRef = false;
        for (auto& dep : elem.second)
            if (constRefs.find(dep) != constRefs.end())
                existInRef = true;

        if (!existInRef)
        {
            result.push_back(elem.first);
            added.insert(elem.first->identifier());
        }
    }

    while (result.size() != constRefs.size())
    {
        for (auto& elem : deps)
        {
            if (added.find(elem.first->identifier()) != added.end())
                continue;

            bool needToAdd = true;
            for (auto& dep : elem.second)
                if (added.find(dep) == added.end())
                    needToAdd = false;
            if (needToAdd)
            {
                result.push_back(elem.first);
                added.insert(elem.first->identifier());
            }
        }
    }
    return result;
}

void createDeclarations(const map<SgStatement*, set<SgSymbol*>>& newSymbsToDeclare)
{
    map<string, map<string, string>> preprocDataByFunc;
    for (auto& dataByF : dataDeclsByFunc)
        preprocDataByFunc[dataByF.first] = splitData(dataByF.second);

    map<SgSymbol*, pair<string, string>> originalInfo;
    for (auto& elem : createdByFunc)
        for (auto& s : elem.second)
            originalInfo[s.second] = make_pair(elem.first, s.first);

    for (auto& byFunc : newSymbsToDeclare)
    {
        if (!byFunc.first->switchToFile())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        map<string, map<string, vector<SgSymbol*>>> groups;
        map<string, map<string, vector<SgSymbol*>>> groupsConstRefs;
        map<string, map<int, SgSymbol*>> commons;
        map<string, SgSymbol*> constRefs;
        map<string, SgSymbol*> saveRefs;
        map<SgSymbol*, string> declRefs;

        SgStatement* place = byFunc.first;
        while (isSgProgHedrStmt(place) == NULL && place->variant() != MODULE_STMT)
            place = place->controlParent();
        SgStatement* scope = place;

        set<string> declared;
        while (isSgExecutableStatement(place) == NULL && place != scope->lastNodeOfStmt())
        {
            if (place->variant() == VAR_DECL || place->variant() == VAR_DECL_90)
            {
                SgExpression* list = place->expr(0);
                while (list)
                {
                    auto elem = list->lhs();
                    if (elem && elem->symbol())
                        declared.insert(elem->symbol()->identifier());
                    list = list->rhs();
                }
            }
            place = place->lexNext();
        }

        for (auto& toDec : byFunc.second)
        {
            if (declared.find(toDec->identifier()) != declared.end())
                continue;

            if (isSgConstantSymb(toDec))
                constRefs[toDec->identifier()] = toDec;

            if (toDec->attributes())
            {
                if (toDec->attributes() & SAVE_BIT || toDec->attributes() & DATA_BIT)
                    saveRefs[toDec->identifier()] = toDec;

                if (toDec->attributes() & DATA_BIT)
                {
                    auto itD = originalInfo.find(toDec);
                    if (itD == originalInfo.end())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    auto itDF = preprocDataByFunc.find(itD->second.first);
                    if (itDF == preprocDataByFunc.end())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    
                    auto info = itDF->second.find(itD->second.second);
                    if (info == itDF->second.end())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    declRefs[toDec] = info->second;
                }
            }

            int globalType = isGlobal(byFunc.first, toDec);
            if (globalType != 0)
                continue;
            else
            {
                auto attrsC = getAttributes<SgSymbol*, char*>(toDec, set<int> { COMM_STAT });
                if (attrsC.size() && attrsC.size() != 1)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                if (attrsC.size())
                {
                    auto attrsPos = getAttributes<SgSymbol*, int*>(toDec, set<int> { COMM_LIST });
                    if (attrsPos.size() && attrsPos.size() != 1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    commons[attrsC[0]][*attrsPos[0]] = toDec; // sort by position
                }

                auto attrsM = getAttributes<SgSymbol*, char*>(toDec, set<int> { MODULE_STMT });
                if (attrsM.size())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            string newDecl = makeDeclaration(NULL, { toDec })->unparse();
            auto it = newDecl.find("::");
            if (it == string::npos)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            if (isSgConstantSymb(toDec))
                groupsConstRefs[newDecl.substr(0, it)][toDec->identifier()].push_back(toDec);
            else
                groups[newDecl.substr(0, it)][toDec->identifier()].push_back(toDec);
        }

        //insert PARAMETER
        if (constRefs.size())
        {
            for (auto& toDecls : groupsConstRefs)
            {
                vector<SgSymbol*> unitedList;
                for (auto& elem : toDecls.second)
                    unitedList.push_back(elem.second[0]);
                makeDeclaration(byFunc.first, unitedList);
            }

            SgParameterStmt* param = new SgParameterStmt();
            for (auto& elem : sortConstRefs(constRefs))
                param->addConstant(elem);

            place->insertStmtBefore(*param, *scope);
        }

        for (auto& toDecls : groups)
        {
            vector<SgSymbol*> unitedList;
            for (auto& elem : toDecls.second)
                unitedList.push_back(elem.second[0]);
            makeDeclaration(byFunc.first, unitedList);
        }

        vector<SgStatement*> newCommons;
        for (auto& byCommon : commons)
        {
            vector<SgExpression*> refs;
            for (auto& s : byCommon.second)
                refs.push_back(new SgVarRefExp(s.second));
            std::reverse(refs.begin(), refs.end());

            SgStatement* common = new SgStatement(COMM_STAT);
            common->setExpression(0, new SgExpression(COMM_LIST, makeExprList(refs), NULL, new SgSymbol(COMMON_NAME, byCommon.first.c_str())));

            newCommons.push_back(common);
        }

        if (newCommons.size())
            for (auto& elem : newCommons)
                place->insertStmtBefore(*elem, *scope);

        //insert SAVE
        if (saveRefs.size())
        {
            SgStatement* save = new SgStatement(SAVE_DECL);
            vector<SgExpression*> refs;
            for (auto& s : saveRefs)
                refs.push_back(new SgVarRefExp(s.second));
            save->setExpression(0, makeExprList(refs));

            place->insertStmtBefore(*save, *scope);
        }

        if (declRefs.size())
        {
            SgStatement* decl = new SgStatement(DATA_DECL);
            SgExpression* value = new SgExpression(STMT_STR);

            string dataS = "data ";
            int z = 0;
            for (auto& elem : declRefs)
            {
                dataS += elem.first->identifier() + string("/") + elem.second + "/";
                if (z != declRefs.size() - 1)
                    dataS += ",";
                ++z;
            }

            value->thellnd->entry.string_val = new char[dataS.size() + 1];
            strcpy(value->thellnd->entry.string_val, dataS.c_str());

            decl->setExpression(0, value);
            place->insertStmtBefore(*decl, *scope);
        }
    }
}
