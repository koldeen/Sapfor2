#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "dvm.h"
#include "../Sapfor.h"
#include "../GraphLoop/graph_loops.h"
#include "../GraphCall/graph_calls_func.h"
#include "../SageAnalysisTool/depInterfaceExt.h"
#include "../Utils/SgUtils.h"
#include "../Utils/errors.h"
#include "directive_parser.h"
#include "../ExpressionTransform/expr_transform.h"

using std::string;
using std::wstring;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::tuple;

static void addToattribute(SgStatement *toAttr, SgStatement *curr, const int variant)
{
    // move SgStatement to attribute
    SgStatement *toAdd = new SgStatement(toAttr->variant(), NULL, toAttr->symbol(), toAttr->expr(0), toAttr->expr(1), toAttr->expr(2));
    toAdd->setlineNumber(toAttr->lineNumber());
    toAdd->setLocalLineNumber(777);

    curr->addAttribute(variant, toAdd, sizeof(SgStatement));
    //copy comments to st
    if (toAttr->comments() && variant != SPF_END_PARALLEL_REG_DIR && variant != SPF_PARALLEL_REG_DIR)
    {
        string comments(toAttr->comments());

        if (curr->comments())
            comments += "\n" + string(curr->comments());
        if (comments.size() != 0)
            curr->setComments(comments.c_str());
    }
}

void fillVars(SgExpression* exp, const set<int>& types, set<string>& identifierList, vector<SgExpression*>& funcCalls)
{
    if (exp)
    {
        if (exp->variant() == FUNC_CALL)
            funcCalls.push_back(exp);

        if (types.find(exp->variant()) != types.end())
        {
            if (exp->symbol())
                identifierList.insert(OriginalSymbol(exp->symbol())->identifier());
            else if (exp->variant() == DDOT)
                identifierList.insert(exp->symbol()->identifier()); // BAD solution
        }

        fillVars(exp->lhs(), types, identifierList, funcCalls);
        fillVars(exp->rhs(), types, identifierList, funcCalls);
    }
}

void fillVars(SgExpression *exp, const set<int> &types, set<SgSymbol*> &identifierList, vector<SgExpression*> &funcCalls)
{
    if (exp)
    {
        if (exp->variant() == FUNC_CALL)
            funcCalls.push_back(exp);

        if (types.find(exp->variant()) != types.end())
        {
            if (exp->symbol())
                identifierList.insert(OriginalSymbol(exp->symbol()));
            else if (exp->variant() == DDOT)
                identifierList.insert((SgSymbol*)exp); // BAD solution
        }
        
        fillVars(exp->lhs(), types, identifierList, funcCalls);
        fillVars(exp->rhs(), types, identifierList, funcCalls);
    }
}

static bool isPrivateVar(SgStatement *st, SgSymbol *symbol)
{
    bool retVal = false;
    
    for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ SPF_ANALYSIS_DIR }))
    {
        set<string> privates;
        fillPrivatesFromComment(new Statement(data), privates);

        retVal = retVal || privates.find(symbol->identifier()) != privates.end();
        if (retVal)
            break;
    }

    return retVal;
}

#define BAD_POSITION_FULL(NEED_PRINT, ERR_TYPE, PLACE_E, PLACE_R, BEFORE_VAR_E, BEFORE_VAR_R, BEFORE_DO_E, BEFORE_DO_R, LINE) do { \
   __spf_print(1, "bad directive position on line %d, it can be placed only %s %s %s\n", LINE, PLACE_E, BEFORE_VAR_E, BEFORE_DO_E); \
   wstring messageE, messageR;\
   __spf_printToLongBuf(messageE, L"bad directive position, it can be placed only %s %s %s", to_wstring(PLACE_E).c_str(), to_wstring(BEFORE_VAR_E).c_str(), to_wstring(BEFORE_DO_E).c_str()); \
   __spf_printToLongBuf(messageR, R1, PLACE_R, BEFORE_VAR_R, BEFORE_DO_R); \
   messagesForFile.push_back(Messages(ERR_TYPE, LINE, messageR, messageE, 1001)); \
} while(0)

static SgStatement* skipDvmDirs(SgStatement *st)
{
    while (isDVM_stat(st))
        st = st->lexNext();
    return st;
}

static void fillVarsSets(SgStatement *iterator, SgStatement *end, set<string> &varDef, set<string> &varUse)
{
    for ( ;iterator != end; iterator = iterator->lexNext())
    {
        vector<SgExpression*> funcCalls;
        if (iterator->variant() == PROC_STAT)
        {// TODO: procedures may have IN, INOUT, OUT parameters
            fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varDef, funcCalls);
            fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varUse, funcCalls);
        }
        else
        {
            if (iterator->variant() == ASSIGN_STAT || isSgExecutableStatement(iterator) == NULL)
                fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varDef, funcCalls);
            else
                fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varUse, funcCalls);

            fillVars(iterator->expr(1), { ARRAY_REF, VAR_REF }, varUse, funcCalls);
            fillVars(iterator->expr(2), { ARRAY_REF, VAR_REF }, varUse, funcCalls);

            if (iterator->variant() == FOR_NODE)
            {
                auto loop = isSgForStmt(iterator);
                varDef.insert(loop->doName()->identifier());
                varUse.insert(loop->doName()->identifier());
            }

            vector<SgExpression*> dummy;
            // TODO: functions may have IN, INOUT, OUT parameters
            for (auto &func : funcCalls)
                fillVars(func, { ARRAY_REF, VAR_REF }, varDef, dummy);
        }        
    }
}

static bool checkPrivate(SgStatement *st,
                         SgStatement *attributeStatement,
                         const set<SgSymbol*> &privates,
                         vector<Messages> &messagesForFile)
{    
    // PRIVATE(VAR)
    const int var = st->variant();
    bool retVal = true;

    if (!isSgExecutableStatement(st) || var == FOR_NODE)
    {
        st = skipDvmDirs(st);
        SgStatement *iterator = st;
        SgStatement *end = (var == FOR_NODE) ? st->lastNodeOfStmt() : st->lexNext();
        set<string> varDef;
        set<string> varUse;

        fillVarsSets(iterator, end, varDef, varUse);
        
        set<string> wrongPrivFromOmpParallel;

        for (auto &privElemS : privates)
        {
            const string privElem = privElemS->identifier();
            bool defCond = true;
            bool useCond = true;

            if (varDef.find(privElem) == varDef.end())
                defCond = false;
            if (varUse.find(privElem) == varUse.end())
                useCond = false;

            if (var == FOR_NODE)
            {
                if (!defCond && !useCond)
                {
                    if (attributeStatement->localLineNumber() != 888)
                    {
                        __spf_print(1, "variable '%s' is not used in loop on line %d\n", privElem.c_str(), attributeStatement->lineNumber());
                        wstring messageE, messageR;
                        __spf_printToLongBuf(messageE, L"variable '%s' is not used in loop", to_wstring(privElem.c_str()).c_str());

                        __spf_printToLongBuf(messageR, R21, to_wstring(privElem.c_str()).c_str());

                        messagesForFile.push_back(Messages(WARR, attributeStatement->lineNumber(), messageR, messageE, 1002));
                    }
                    else
                        wrongPrivFromOmpParallel.insert(privElem);
                }
                else if (!defCond && useCond)
                {
                    __spf_print(1, "variable '%s' is not changed in loop on line %d\n", privElem.c_str(), attributeStatement->lineNumber());
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"variable '%s' is not changed in loop", to_wstring(privElem.c_str()).c_str());

                    __spf_printToLongBuf(messageR, R23, to_wstring(privElem.c_str()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1003));
                    retVal = false;
                }
            }
            else
            {
                if (!defCond)
                {
                    BAD_POSITION_FULL(1, ERROR, "before", RR1_1, "variable declaration or", RR1_2, "DO statement", RR1_3, attributeStatement->lineNumber());
                    retVal = false;
                }
            }
        }

        if (var == FOR_NODE && wrongPrivFromOmpParallel.size()) // remove unnecessary
        {
            if (wrongPrivFromOmpParallel.size() == privates.size()) // remove all
                attributeStatement->expr(0)->lhs()->setLhs(NULL);
            else
            {
                SgExpression* list = attributeStatement->expr(0)->lhs()->lhs();
                vector<SgExpression*> newList;
                for (auto ex = list; ex; ex = ex->rhs())
                {
                    string currV = ex->lhs()->symbol()->identifier();
                    if (wrongPrivFromOmpParallel.find(currV) == wrongPrivFromOmpParallel.end())
                        newList.push_back(ex->lhs());
                }
                attributeStatement->expr(0)->lhs()->setLhs(makeExprList(newList));
            }
        }
    }
    else
    {
        BAD_POSITION_FULL(1, ERROR, "before", RR1_1, "variable declaration or", RR1_2, "DO statement", RR1_3, attributeStatement->lineNumber());
        retVal = false;
    }

    return retVal;
}

static bool checkReduction(SgStatement *st,
                           SgStatement *attributeStatement,
                           const map<string, set<SgSymbol*>> &reduction,
                           vector<Messages> &messagesForFile)
{
    // REDUCTION(OP(VAR))
    const int var = st->variant();
    bool retVal = true;

    if (var == FOR_NODE)
    {
        SgStatement *iterator = st->lexNext();
        SgStatement *end = st->lastNodeOfStmt();
        set<string> varDef;
        set<string> varUse;

        fillVarsSets(iterator, end, varDef, varUse);

        for (auto &redElem : reduction)
        {
            for (auto &setElemS : redElem.second)
            {
                const string setElem = setElemS->identifier();
                bool defCond = true;
                bool useCond = true;

                if (varDef.find(setElem) == varDef.end())
                    defCond = false;
                if (varUse.find(setElem) == varUse.end())
                    useCond = false;

                if (var == FOR_NODE && !defCond && !useCond)
                {
                    __spf_print(1, "variable '%s' is not used in loop on line %d\n", setElem.c_str(), attributeStatement->lineNumber());
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"variable '%s' is not used in loop", to_wstring(setElem.c_str()).c_str());

                    __spf_printToLongBuf(messageR, R22, to_wstring(setElem.c_str()).c_str());

                    messagesForFile.push_back(Messages(WARR, attributeStatement->lineNumber(), messageR, messageE, 1002));
                }
                if (var == FOR_NODE && !defCond && useCond)
                {
                    __spf_print(1, "variable '%s' is not changed in loop on line %d\n", setElem.c_str(), attributeStatement->lineNumber());
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"variable '%s' is not changed in loop", to_wstring(setElem.c_str()).c_str());

                    __spf_printToLongBuf(messageR, R24, to_wstring(setElem.c_str()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1003));
                    retVal = false;
                }
            }
        }
    }
    else
    {
        BAD_POSITION_FULL(1, ERROR, "before", RR1_1, "", L"", "DO statement", RR1_3, attributeStatement->lineNumber());
        retVal = false;
    }

    return retVal;
}

static bool checkReduction(SgStatement *st,
                           SgStatement *attributeStatement,
                           const map<string, set<tuple<SgSymbol*, SgSymbol*, int>>> &reduction,
                           vector<Messages> &messagesForFile)
{
    // REDUCTION(MIN/MAXLOC(VAR, ARRAY, CONST))
    bool retVal = true;    

    for (auto &redElem : reduction)
    {
        set<SgSymbol*> vars;
        set<SgSymbol*> arrs;

        set<string> varsS;
        set<string> arrsS;

        for (auto &setElem : redElem.second)
        {
            vars.insert(std::get<0>(setElem));
            varsS.insert(std::get<0>(setElem)->identifier());

            arrs.insert(std::get<1>(setElem));
            arrsS.insert(std::get<1>(setElem)->identifier());

            // CHECK ARRAY DECLARATION && DIMENTION
            SgSymbol *arraySymbol = std::get<1>(setElem);
            SgStatement *declStatement = declaratedInStmt(arraySymbol);
            SgArrayType *arrayType = NULL;
            int count = std::get<2>(setElem);

            if (arraySymbol->type())
                arrayType = isSgArrayType(arraySymbol->type());

            if (arrayType)
            {
                const int dim = arrayType->dimension();

                if (dim != 1)
                {
                    __spf_print(1, "dimention of array '%s' is %d, but must be 1 on line %d\n", arraySymbol->identifier(), dim, attributeStatement->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"dimention of array '%s' is %d, but must be 1", to_wstring(arraySymbol->identifier()).c_str(), dim);

                    __spf_printToLongBuf(messageR, R25, to_wstring(arraySymbol->identifier()).c_str(), dim);

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1004));

                    retVal = false;
                }

                if (!arrayType->baseType()->equivalentToType(SgTypeInt()))
                {
                    __spf_print(1, "type of array '%s' must be INTEGER on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"type of array '%s' but must be INTEGER", to_wstring(arraySymbol->identifier()).c_str());

                    __spf_printToLongBuf(messageR, R26, to_wstring(arraySymbol->identifier()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1005));

                    retVal = false;
                }
            }
            else
            {
                __spf_print(1, "type of variable '%s' must be array on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"type of variable '%s' must be array", to_wstring(arraySymbol->identifier()).c_str());

                __spf_printToLongBuf(messageR, R27, to_wstring(arraySymbol->identifier()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1006));

                retVal = false;
            }

            SgStatement *iterator = st;
            SgStatement *end = st;
            vector<SgExpression*> dimentions;
            
            while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
                iterator = iterator->controlParent();

            while (iterator != end)
            {
                if (isSPF_stat(iterator) || isDVM_stat(iterator))
                {
                    iterator = iterator->lexNext();
                    continue;
                }

                if (!isSgExecutableStatement(iterator))
                {
                    for (SgExpression *exp = iterator->expr(0); exp; exp = exp->rhs())
                        if (exp->lhs()->symbol() == arraySymbol)
                            for (SgExpression *list = exp->lhs()->lhs(); list; list = list->rhs())
                                dimentions.push_back(list->lhs());

                    if (dimentions.size())
                    {
                        if (dimentions.size() != 1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        int size;
                        int err = CalculateInteger(dimentions[0], size);

                        if (err != 0)
                        {
                            // Expression can not be computed
                            __spf_print(1, "array size can't be computed on line %d\n", attributeStatement->lineNumber());

                            wstring messageE, messageR;
                            __spf_printToLongBuf(messageE, L"array size can't be computed");
                            __spf_printToLongBuf(messageR, R30);

                            messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1007));

                            retVal = false;
                        }
                        else if (size != count)
                        {
                            __spf_print(1, "size of array '%s' is %d, but you enter %d on line %d\n",
                                        arraySymbol->identifier(), size, count, attributeStatement->lineNumber());

                            wstring messageE, messageR;
                            __spf_printToLongBuf(messageE, L"size of array '%s' is %d, but you enter %d", to_wstring(arraySymbol->identifier()).c_str(), size, count);
                            __spf_printToLongBuf(messageR, R31, to_wstring(arraySymbol->identifier()).c_str(), size, count);

                            messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1008));

                            retVal = false;
                        }
                        break;
                    }
                }
                else
                    break;

                iterator = iterator->lexNext();
            }
        }

        map<string, set<SgSymbol*>> reductionVar;
        map<string, set<SgSymbol*>> reductionArr;

        reductionVar[redElem.first] = vars;
        reductionArr[redElem.first] = arrs;

        retVal = checkReduction(st, attributeStatement, reductionVar, messagesForFile) && checkReduction(st, attributeStatement, reductionArr, messagesForFile);
    }

    return true;
}

static bool checkShadowAcross(SgStatement *st,
                              SgStatement *attributeStatement,
                              const vector<pair<pair<SgSymbol*, string>, vector<pair<int, int>>>> &data,
                              vector<Messages> &messagesForFile)
{
    // SHADOW (VAR(list of  shadows)) / ACROSS (VAR(list of  shadows))
    const int var = st->variant();
    bool retVal = true;

    if (var == FOR_NODE)
    {
        for (int i = 0; i < data.size(); ++i)
        {
            SgSymbol *arraySymbol = data[i].first.first;
            SgStatement *declStatement = declaratedInStmt(arraySymbol);
            const vector<pair<int, int>> &arrayDisc = data[i].second;
            bool notPrivCond = true;

            if (arraySymbol->type()->variant() != T_ARRAY)
            {
                __spf_print(1, "variable '%s' is not array on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"variable '%s' is not array", to_wstring(arraySymbol->identifier()).c_str());
                __spf_printToLongBuf(messageR, R28, to_wstring(arraySymbol->identifier()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1006));
                retVal = false;
            }

            notPrivCond = !isPrivateVar(st, arraySymbol) && !isPrivateVar(declStatement, arraySymbol);

            if (!notPrivCond)
            {
                __spf_print(1, "array '%s' on line %d is private\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"array '%s' is private", to_wstring(arraySymbol->identifier()).c_str());

                __spf_printToLongBuf(messageR, R33, to_wstring(arraySymbol->identifier()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1009));
                retVal = false;
            }
            
            SgArrayType *arrayType = NULL; 
            if (arraySymbol->type())
                arrayType = isSgArrayType(arraySymbol->type());

            if (arrayType)
            {
                int dim = arrayType->dimension();

                if (dim != arrayDisc.size())
                {
                    __spf_print(1, "dimention of array '%s' is %d, but you enter %d on line %d\n",
                                arraySymbol->identifier(), arrayType->dimension(), (int)arrayDisc.size(), attributeStatement->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"dimention of array '%s' is %d, but you enter %d",
                                         to_wstring(arraySymbol->identifier()).c_str(), arrayType->dimension(), (int)arrayDisc.size());

                    __spf_printToLongBuf(messageR, R32,
                                         to_wstring(arraySymbol->identifier()).c_str(), arrayType->dimension(), (int)arrayDisc.size());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1008));
                    retVal = false;
                }
            }
            else
            {
                __spf_print(1, "variable '%s' is not array on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"variable '%s' is not array", to_wstring(arraySymbol->identifier()).c_str());

                __spf_printToLongBuf(messageR, R29, to_wstring(arraySymbol->identifier()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1006));
                retVal = false;
            }

            for (auto &array : arrayDisc)
            {
                if (array.first < 0 || array.second < 0)
                {
                    __spf_print(1, "only positive numbers are supported on line %d\n", attributeStatement->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"only positive numbers are supported");

                    __spf_printToLongBuf(messageR, R35);

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1010));
                    retVal = false;
                }
            }
        }
    }
    else
    {
        BAD_POSITION_FULL(1, ERROR, "before", RR1_1, "", L"", "DO statement", RR1_3, attributeStatement->lineNumber());
        retVal = false;
    }

    return retVal;
}


static int hasName(SgExpression *exp, const string &varName)
{
    if (exp)
    {
        SgSymbol *symb = exp->symbol();
        SgExpression *lhs = exp->lhs();
        SgExpression *rhs = exp->rhs();

        if (symb)
            if (string(symb->identifier()) == varName)
                return 1;

        return hasName(lhs, varName) + hasName(rhs, varName);
    }

    return 0;
}

static bool isRemoteExpressions(SgExpression *exp, SgExpression *remoteExp, map<SgExpression*, string> &collection)
{
    if (exp == remoteExp)
        return true;

    bool retVal = true;

    while (retVal && exp != NULL && remoteExp != NULL)
    {
        if (remoteExp->lhs())
            if (remoteExp->lhs()->variant() != DDOT)
                retVal = retVal && isEqExpressions(exp->lhs(), remoteExp->lhs(), collection);

        exp = exp->rhs();
        remoteExp = remoteExp->rhs();
    }

    return retVal;
}

static bool hasRemoteExpressions(SgExpression *exp, SgExpression *remoteExp, map<SgExpression*, string> &collection)
{
    if (exp)
    {
        SgExpression *lhs = exp->lhs();
        SgExpression *rhs = exp->rhs();

        if (exp->variant() == ARRAY_REF && string(exp->symbol()->identifier()) == remoteExp->symbol()->identifier())
            if (isRemoteExpressions(exp->lhs(), remoteExp->lhs(), collection))
                return true;

        return hasRemoteExpressions(lhs, remoteExp, collection) || hasRemoteExpressions(rhs, remoteExp, collection);
    }

    return false;
}

static bool checkRemote(SgStatement *st,
                        SgStatement *attributeStatement,
                        const map<pair<SgSymbol*, string>, Expression*> &remote,
                        vector<Messages> &messagesForFile)
{
    // REMOTE_ACCESS (EXPR)
    const int var = st->variant();
    bool retVal = true;

    if (var == FOR_NODE || isSgExecutableStatement(st))
    {
        for (auto &remElem : remote)
        {
            bool cond = false;
            SgStatement *declStatement = declaratedInStmt(remElem.first.first);
            set<SgSymbol*> arraySymbols;

            vector<SgExpression*> dummy;
            fillVars(remElem.second, { ARRAY_REF }, arraySymbols, dummy);
            for (auto &arraySymbol : arraySymbols)
            {
                declStatement = declaratedInStmt(arraySymbol);
                bool notPrivCond = !isPrivateVar(st, arraySymbol) && !isPrivateVar(declStatement, arraySymbol);

                if (!notPrivCond)
                {
                    __spf_print(1, "array '%s' is private on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"array '%s' is private", to_wstring(arraySymbol->identifier()).c_str());

                    __spf_printToLongBuf(messageR, R34, to_wstring(arraySymbol->identifier()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1009));
                    retVal = false;
                }
            }

            if (var == FOR_NODE)
            {
                SgStatement *iterator = st;
                SgStatement *end = st->lastNodeOfStmt();
                map<string, int> forVars;

                while (iterator != end)
                {
                    SgForStmt *forSt = isSgForStmt(iterator);

                    if (forSt)
                    {
                        SgSymbol *forName = forSt->doName();
                        forVars.insert(make_pair(string(forName->identifier()), 0));
                    }

                    iterator = iterator->lexNext();
                }

                // CHECK: i AND a * i + b
                // remElem.second links to b(i,j,k)
                // remElem.second->lhs() links to i,j,k
                SgExpression *remoteExp = remElem.second->lhs();
                while (remoteExp)
                {
                    int forVarsCount = 0;

                    for (auto &forVar : forVars)
                    {
                        if (hasName(remoteExp->lhs(), forVar.first))
                        {
                            ++forVarsCount;
                            ++forVar.second;

                            if (retVal && forVarsCount > 1 || forVar.second > 1)
                            {
                                __spf_print(1, "bad directive expression: too many DO variables on line %d\n", attributeStatement->lineNumber());

                                wstring messageE, messageR;
                                __spf_printToLongBuf(messageE, L"bad directive expression: too many DO variables");

                                __spf_printToLongBuf(messageR, R2);

                                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1001));
                                retVal = false;
                            }

                            // CHECK TREE: i OR a * i OR a * i + b
                            SgExpression *list = remoteExp->lhs();
                            bool isRemoteSubTreeCond = false;

                            if (list->variant() == ADD_OP)
                            {
                                if (list->lhs()->variant() == MULT_OP && !hasName(list->rhs(), forVar.first))
                                {
                                    if (hasName(list->lhs(), forVar.first) == 1)
                                        isRemoteSubTreeCond = true;
                                }
                                else if (list->rhs()->variant() == MULT_OP && !hasName(list->lhs(), forVar.first))
                                {
                                    if (hasName(list->rhs(), forVar.first) == 1)
                                        isRemoteSubTreeCond = true;
                                }
                                else if (hasName(list, forVar.first) == 1)
                                    isRemoteSubTreeCond = true;
                            }
                            else if (list->variant() == MULT_OP)
                            {
                                if (!hasName(list->lhs(), forVar.first) && hasName(list->rhs(), forVar.first) == 1 ||
                                    !hasName(list->rhs(), forVar.first) && hasName(list->lhs(), forVar.first) == 1)
                                    isRemoteSubTreeCond = true;
                            }
                            else if (hasName(list, forVar.first) == 1)
                                isRemoteSubTreeCond = true;

                            if (!isRemoteSubTreeCond)
                            {
                                __spf_print(1, "bad directive expression: only a * i + b on line %d\n", attributeStatement->lineNumber()); 

                                wstring messageE, messageR;
                                __spf_printToLongBuf(messageE, L"bad directive expression: only a * i + b");

                                __spf_printToLongBuf(messageR, R3);

                                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1001));
                                retVal = false;
                            }
                        }
                    }

                    remoteExp = remoteExp->rhs();
                }
            }
                        
            st = skipDvmDirs(st);
            SgStatement *iterator = st;
            SgStatement *end = (var == FOR_NODE) ? st->lastNodeOfStmt() : st->lexNext();

            while (iterator != end)
            {
                map<SgExpression*, string> collection;
                for (int i = 0; i < 3; ++i)
                    if (hasRemoteExpressions(iterator->expr(i), remElem.second, collection))
                        cond = true;                

                iterator = iterator->lexNext();
            }

            if (!cond)
            {
                __spf_print(1, "no such expression '%s' on line %d\n", remElem.second->unparse(), attributeStatement->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"no such expression '%s' on loop", to_wstring(remElem.second->unparse()).c_str());

                __spf_printToLongBuf(messageR, R36, to_wstring(remElem.second->unparse()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1011));
                retVal = false;
            }
        }
    }
    else
    {
        BAD_POSITION_FULL(1, ERROR, "before", RR1_1, "", L"", "DO statement", RR1_3, attributeStatement->lineNumber());
        retVal = false;
    }

    return retVal;
}

static void findAllRefs(SgExpression *ex, set<string> &names)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF || ex->variant() == ARRAY_REF)
            if (ex->symbol())
                names.insert(ex->symbol()->identifier());

        findAllRefs(ex->lhs(), names);
        findAllRefs(ex->rhs(), names);
    }
}

static bool checkParallelRegions(SgStatement *st,
                                 const map<string, CommonBlock> *commonBlocks,
                                 vector<Messages> &messagesForFile)
{
    bool retVal = true;

    bool execNext = isSgExecutableStatement(st->lexNext());

    if (execNext || st->lexNext()->variant() == ENTRY_STAT)
    {
        if (st->variant() == SPF_PARALLEL_REG_DIR)
        {
            SgSymbol *identSymbol = st->symbol();

            // declaration checking
            SgStatement *iterator = st;
            SgStatement *end = st;

            while (iterator->variant() != PROG_HEDR && iterator->variant() != PROC_HEDR && iterator->variant() != FUNC_HEDR)
                iterator = iterator->controlParent();

            for (; iterator != end && retVal; iterator = iterator->lexNext())
            {
                if (isSPF_stat(iterator) || isDVM_stat(iterator))
                    continue;
                
                if (!isSgExecutableStatement(iterator))
                {
                    if (iterator->variant() == VAR_DECL || iterator->variant() == VAR_DECL_90)
                    {
                        set<string> names;
                        findAllRefs(iterator->expr(0), names);
                        if (names.find(identSymbol->identifier()) != names.end())
                        {
                            __spf_print(1, "wrong parallel region identifier: variable '%s' was declared on line %d on line %d\n",
                                            identSymbol->identifier(), iterator->lineNumber(), st->lineNumber());

                            wstring messageE, messageR;
                            __spf_printToLongBuf(messageE, L"wrong parallel region identifier: variable '%s' was declared on line %d",
                                                           to_wstring(identSymbol->identifier()).c_str(), iterator->lineNumber());

                            __spf_printToLongBuf(messageR, R63,
                                                           to_wstring(identSymbol->identifier()).c_str(), iterator->lineNumber());

                            messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1031));

                            retVal = false;
                        }
                    }
                }
                else
                    break;
            }

            if (commonBlocks)
            {
                // common blocks checking
                for (auto &commonBlockPair : *commonBlocks)
                {
                    for (auto &variable : commonBlockPair.second.getVariables())
                    {
                        if (variable.getName() == identSymbol->identifier())
                        {
                            __spf_print(1, "wrong parallel region identifier: variable '%s' was declared in common block '%s' on line %d\n",
                                        identSymbol->identifier(), commonBlockPair.first.c_str(), st->lineNumber());

                            wstring messageE, messageR;
                            __spf_printToLongBuf(messageE, L"wrong parallel region identifier: variable '%s' was declared in common block '%s'",
                                                 to_wstring(identSymbol->identifier()).c_str(), to_wstring(commonBlockPair.first).c_str());

                            __spf_printToLongBuf(messageR, R64,
                                                 to_wstring(identSymbol->identifier()).c_str(), to_wstring(commonBlockPair.first).c_str());

                            messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1032));

                            retVal = false;
                        }
                    }
                }
            }

            // try to find SPF_END_PARALLEL_REG_DIR
            iterator = st->lexNext();
            bool found = false;

            for (; iterator && !found; iterator = iterator->lexNext())
            {
                const int var = iterator->variant();
                if (var == SPF_PARALLEL_REG_DIR)
                {
                    // intersection
                    __spf_print(1, "bad directive position: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s', but got 'SPF PARALLEL_REG_DIR' on line %d\n",
                                identSymbol->identifier(), st->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"bad directive position: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s', but got 'SPF PARALLEL_REG_DIR'",
                                         to_wstring(identSymbol->identifier()).c_str());

                    __spf_printToLongBuf(messageR, R4,
                                         to_wstring(identSymbol->identifier()).c_str());

                    messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1001));

                    retVal = false;
                    break;
                }
                else if (var == SPF_END_PARALLEL_REG_DIR)
                {
                    found = true;

                    if (iterator->controlParent() != st->controlParent())
                    {
                        __spf_print(1, "bad directive position: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s' at the same scope on line %d\n",
                                    identSymbol->identifier(), st->lineNumber());

                        wstring messageE, messageR;
                        __spf_printToLongBuf(messageE, L"bad directive position: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s' at the same scope",
                                             to_wstring(identSymbol->identifier()).c_str());

                        __spf_printToLongBuf(messageR, R5,
                                             to_wstring(identSymbol->identifier()).c_str());

                        messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1001));

                        retVal = false;
                    }

                    break;
                }
            }

            if (!found && retVal)
            {
                __spf_print(1, "bad directive position: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s' on line %d\n", identSymbol->identifier(), st->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"bad directive position: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s'",
                                     to_wstring(identSymbol->identifier()).c_str());

                __spf_printToLongBuf(messageR, R6,
                                     to_wstring(identSymbol->identifier()).c_str());

                messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1001));

                retVal = false;
            }
        }
        else
        {
            // type == SPF_END_PARALLEL_REG_DIR
            // try to find SPF_PARALLEL_REG_DIR
            SgStatement *iterator = st->lexPrev();
            SgStatement *end = st->controlParent();
            bool found = false;
            
            for (; iterator != end && retVal && !found; iterator = iterator->lexPrev())
            {
                const int var = iterator->variant();
                if (var == SPF_END_PARALLEL_REG_DIR)
                {
                    // intersection
                    __spf_print(1, "bad directive position: expected 'SPF PARALLEL_REG_DIR', but got 'SPF END PARALLEL_REG_DIR' on line %d\n", st->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"bad directive position: expected 'SPF PARALLEL_REG_DIR', but got 'SPF END PARALLEL_REG_DIR'");

                    __spf_printToLongBuf(messageR, R7);

                    messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1001));

                    retVal = false;
                    break;
                }
                else if (var == SPF_PARALLEL_REG_DIR)
                {
                    found = true;

                    if (iterator->controlParent() != st->controlParent())
                    {
                        __spf_print(1, "bad directive position: expected 'SPF PARALLEL_REG_DIR' at the same scope on line %d\n", st->lineNumber());
  
                        wstring messageE, messageR;
                        __spf_printToLongBuf(messageE, L"bad directive position: expected 'SPF PARALLEL_REG_DIR' at the same scope");

                        __spf_printToLongBuf(messageR, R8);

                        messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1001));

                        retVal = false;
                    }

                    break;
                }
            }

            if (!found && retVal)
            {
                __spf_print(1, "bad directive position: expected 'SPF PARALLEL_REG_DIR' on line %d\n", st->lineNumber());
   
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"bad directive position: expected 'SPF PARALLEL_REG_DIR'");

                __spf_printToLongBuf(messageR, R9);

                messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1001));

                retVal = false;
            }
        }
    }
    else
    {
        BAD_POSITION_FULL(1, ERROR, "after", RR1_4, "", L"", "all declaration statements", RR1_5, st->lineNumber());
        retVal = false;
    }

    return retVal;
}

static inline void addSPFtoAttr(SgStatement *st, const string &currFile)
{
    bool cond = false;
    SgStatement *iterator = skipDvmDirs(st);
    do
    {
        SgStatement *prev = iterator->lexPrev();
        const int prevVar = prev->variant();
        cond = (isSPF_stat(prev) && prevVar != SPF_END_PARALLEL_REG_DIR);
        if (cond)
        {
            addToattribute(prev, st, prevVar);

            if ((prev->fileName() == currFile) && prevVar != SPF_PARALLEL_REG_DIR)
                prev->deleteStmt();
            else
                iterator = prev;
        }
    } while (cond);
}

static bool checkFissionPrivatesExpansion(SgStatement *st,
                                          SgStatement *attributeStatement,
                                          const string &currFile,
                                          vector<Messages> &messagesForFile,
                                          bool checkVars = false)
{
    bool retVal = true;
    if (attributeStatement)
    {
        vector<string> vars;
        fillFissionPrivatesExpansionFromComment(new Statement(attributeStatement), vars);

        if (checkVars && !vars.size())
        {
            __spf_print(1, "bad directive expression: expected list of variables on line %d\n", attributeStatement->lineNumber());

            wstring messageE, messageR;
            __spf_printToLongBuf(messageE, L"bad directive expression: expected list of variables");

            __spf_printToLongBuf(messageR, R76);

            messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1043));

            retVal = false;
        }

        if (vars.size())
        {
            // move next SPF directives to atributes
            for (auto s = st; s != st->lastNodeOfStmt()->lexNext(); s = s->lexNext())
                addSPFtoAttr(s, currFile);

            SgForStmt *forSt = (SgForStmt*)st;
            if (vars.size() > forSt->isPerfectLoopNest())
            {
                __spf_print(1, "bad directive expression: expected %d nested loops on line %d but got %d on line %d\n",
                            (int)vars.size(), attributeStatement->lineNumber(), forSt->isPerfectLoopNest(), st->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"bad directive expression: expected %d nested loops on line %d but got %d",
                                     (int)vars.size(), attributeStatement->lineNumber(), forSt->isPerfectLoopNest());

                __spf_printToLongBuf(messageR, R77,
                                     (int)vars.size(), attributeStatement->lineNumber(), forSt->isPerfectLoopNest());

                messagesForFile.push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1043));

                retVal = false;
            }
        }

        for (int i = 0; retVal && i < vars.size(); ++i)
        {
            SgForStmt *forSt = (SgForStmt*)st;
            if (forSt->doName()->identifier() != vars[i])
            {
                __spf_print(1, "bad directive expression: expected variable '%s' at %d position on line %d\n",
                            forSt->doName()->identifier(), i + 1, attributeStatement->lineNumber());

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"bad directive expression: expected variable '%s' at %d position",
                                     to_wstring(forSt->doName()->identifier()).c_str(), i + 1);

                __spf_printToLongBuf(messageR, R78,
                                     to_wstring(forSt->doName()->identifier()).c_str(), i + 1);

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1043));

                retVal = false;
            }
            st = st->lexNext();
        }
    }
    return retVal;
}

static bool checkShrink(SgStatement *st,
                        SgStatement *attributeStatement,
                        const string &currFile,
                        vector<Messages> &messagesForFile)
{
    bool retVal = true;
    
    vector<pair<SgSymbol *, vector<int>>> varDims;
    fillShrinkFromComment(new Statement(attributeStatement), varDims);

    for (auto &p : varDims)
    {
        auto var = p.first;
        auto dims = p.second;

        // check variable type
        SgArrayType *arrType = isSgArrayType(var->type());
        if (!arrType)
        {
            __spf_print(1, "variable in shrink clause must be array in file '%s' on line %d\n", st->fileName(), attributeStatement->lineNumber());
            wstring messageE, messageR;
            __spf_printToLongBuf(messageE, L"variable in shrink clause must be array in file '%s'", to_wstring(st->fileName()).c_str());

            __spf_printToLongBuf(messageR, R154, to_wstring(st->fileName()).c_str());

            messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1053));
            retVal = false;
        }
        else
        {
            // check private directives
            set<SgSymbol*> privates;
            for (int i = 0; i < st->numberOfAttributes(); ++i)
            {
                SgAttribute *attr = st->getAttribute(i);
                SgStatement *attributeStatement = (SgStatement *)(attr->getAttributeData());
                fillPrivatesFromComment(new Statement(attributeStatement), privates);
            }

            auto it = privates.find(var);
            if (it == privates.end())
            {
                __spf_print(1, "array '%s' in shrink clause must be also declared in private clause in file '%s' on line %d\n",
                            var->identifier(), st->fileName(), attributeStatement->lineNumber());
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"array '%s' in shrink clause must be also declared in private clause in file '%s'",
                                     to_wstring(var->identifier()).c_str(), to_wstring(st->fileName()).c_str());

                __spf_printToLongBuf(messageR, R157, to_wstring(var->identifier()).c_str(), to_wstring(st->fileName()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1056));
                retVal = false;
            }
            
            // check mask dimensions
            if (dims.size() != arrType->dimension())
            {
                __spf_print(1, "length of mask for array '%s' must be %d, but you enter only %d dimenions in file '%s' on line %d\n",
                            var->identifier(), arrType->dimension(), dims.size(), st->fileName(), attributeStatement->lineNumber());
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"length of mask for array '%s' must be %d, but you enter only %d dimenions in file '%s'",
                                     to_wstring(var->identifier()).c_str(), arrType->dimension(), dims.size(),
                                     to_wstring(st->fileName()).c_str());

                __spf_printToLongBuf(messageR, R155, to_wstring(var->identifier()).c_str(), arrType->dimension(), dims.size(), to_wstring(st->fileName()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1054));
                retVal = false;
            }

            for (auto i = 0; i < dims.size(); ++i)
            {
                auto dimVal = dims[i];
                if (dimVal != 0 && dimVal != 1)
                {
                    __spf_print(1, "wrong mask value in %d position for array '%s': it can be only 0 or 1 in file '%s' on line %d\n",
                                i + 1, var->identifier(), st->fileName(), attributeStatement->lineNumber());
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"wrong mask value in %d position of array '%s': it can be only 0 or 1 in file '%s'",
                                         i + 1, to_wstring(var->identifier()).c_str(), to_wstring(st->fileName()).c_str());

                    __spf_printToLongBuf(messageR, R156, i + 1, to_wstring(var->identifier()).c_str(), to_wstring(st->fileName()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 1055));
                    retVal = false;
                }
            }
        }
    }

    return retVal;
}

bool recIsVarUsed(SgStatement *st, SgExpression *exp, const string &varName)
{
    if (exp)
    {
        if (exp->symbol() && exp->symbol()->identifier() == varName)
            return true;
        return recIsVarUsed(st, exp->lhs(), varName) || recIsVarUsed(st, exp->rhs(), varName);
    }
    return false;
}

static bool isVarUsed(SgStatement *st, const string &varName)
{
    if (st)
    {
        auto funcSt = getFuncStat(st);
        checkNull(funcSt, convertFileName(__FILE__).c_str(), __LINE__);
        for (auto st = funcSt; st != funcSt->lastNodeOfStmt(); st = st->lexNext())
        {
            for (auto i = 0; i < 3; ++i)
            {
                bool found = recIsVarUsed(st, st->expr(i), varName);
                if (found)
                    return true;
            }
        }
    }
    return false;
}

static bool checkCheckpoint(SgStatement *st,
                            SgStatement *attributeStatement,
                            const map<int, SgExpression*> &clauses,
                            const set<SgSymbol*> &vars,
                            vector<Messages> &messagesForFile)
{
    bool retVal = true;
    bool hasInterval = clauses.find(SPF_INTERVAL_OP) == clauses.end();
    bool isExecutable = isSgExecutableStatement(st);

    for (auto &p : clauses)
    {
        auto op = p.first;
        SgExpression *exprList = p.second;
        switch (op)
        {
        case SPF_INTERVAL_OP:
        {
            int count = 0;
            while (exprList)
            {
                if (exprList->lhs())
                    ++count;
                exprList = exprList->rhs();
            }
            if (count != 1)
            {
                __spf_print(1, "INTERVAL clause can be used only once in file '%s' on line %d.\n",
                            st->fileName(), attributeStatement->lineNumber());
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"INTERVAL clause can be used only once in file '%s'.",
                                     to_wstring(st->fileName()).c_str());

                __spf_printToLongBuf(messageR, R170, to_wstring(st->fileName()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 5001));
                retVal = false;
            }
            exprList = p.second->lhs();
            if (!exprList || exprList->lhs()->variant() != SPF_TIME_OP &&
                             exprList->lhs()->variant() != SPF_ITER_OP ||
                             exprList->rhs()->variant() != INT_VAL)
            {
                __spf_print(1, "The first argument must be TIME or ITER and the second must be integer in INTERVAL clause in file '%s' on line %d.\n",
                            st->fileName(), attributeStatement->lineNumber());
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"The first argument must be TIME or ITER and the second must be integer in INTERVAL clause in file '%s'.",
                                     to_wstring(st->fileName()).c_str());

                __spf_printToLongBuf(messageR, R165, to_wstring(st->fileName()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 5001));
                retVal = false;
            }
            if (!isExecutable)
            {
                __spf_print(1, "CHECKPOINT directive with INTERVAL clause can be only at executable code section in file '%s' on line %d.\n",
                            st->fileName(), attributeStatement->lineNumber());
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"CHECKPOINT directive with INTERVAL clause can be only at executable code section in file '%s'.",
                                     to_wstring(st->fileName()).c_str());

                __spf_printToLongBuf(messageR, R166, to_wstring(st->fileName()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 5002));
                retVal = false;
            }
            break;
        }
        case SPF_FILES_COUNT_OP:
            if (!isExecutable)
            {
                __spf_print(1, "CHECKPOINT directive with FILES clause can be only at executable code section in file '%s' on line %d.\n",
                            st->fileName(), attributeStatement->lineNumber());
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"CHECKPOINT directive with FILES clause can be only at executable code section in file '%s'.",
                                     to_wstring(st->fileName()).c_str());

                __spf_printToLongBuf(messageR, R166, to_wstring(st->fileName()).c_str());

                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 5002));
                retVal = false;
            }
            else
            {
                bool error = false;
                int count = 0;
                while (exprList)
                {
                    if (exprList->lhs())
                        ++count;
                    exprList = exprList->rhs();
                }
                exprList = p.second;
                if (count != 1 || exprList && exprList->lhs()->variant() != INT_VAL)
                {
                    __spf_print(1, "CHECKPOINT directive with FILES clause must contain one integer value in file '%s' on line %d.\n",
                                st->fileName(), attributeStatement->lineNumber());
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"CHECKPOINT directive with FILES clause must contain one integer value in file '%s'.",
                                         to_wstring(st->fileName()).c_str());

                    __spf_printToLongBuf(messageR, R167, to_wstring(st->fileName()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 5003));
                    retVal = false;
                }
            }
            break;
        case SPF_VARLIST_OP:
        case SPF_EXCEPT_OP:
        {
            for (auto &var : vars)
            {
                bool local;
                vector<SgStatement*> allDecls;
                SgStatement *decl = declaratedInStmt(var, &allDecls, false);
                local = isVarUsed(st, var->identifier());
                // TODO: check modules
                if (!local)
                {
                    __spf_print(1, "Variable '%s' in %s clause must be declared at the same module in file '%s' on line %d.\n",
                                var->identifier(), op == SPF_VARLIST_OP ? "VARLIST" : "EXCEPT",
                                st->fileName(), attributeStatement->lineNumber());
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"Variable '%s' in %s clause must be declared at the same module in file '%s'.",
                                         to_wstring(var->identifier()),
                                         op == SPF_VARLIST_OP ? to_wstring("VARLIST") : to_wstring("EXCEPT"),
                                         to_wstring(st->fileName()).c_str());

                    __spf_printToLongBuf(messageR, R168, to_wstring(st->fileName()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 5004));
                    retVal = false;
                }
            }
            break;
        }
        case SPF_TYPE_OP:
        {
            int count = 0;
            exprList = exprList->rhs();
            while (exprList)
            {
                if (exprList->lhs() && exprList->lhs()->variant() != ACC_ASYNC_OP &&
                                       exprList->lhs()->variant() != SPF_FLEXIBLE_OP)
                {
                    __spf_print(1, "Illegal option in TYPE clause in file '%s' on line %d.\n",
                                st->fileName(), attributeStatement->lineNumber());
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"Illegal option in TYPE clause in file '%s'.",
                                         to_wstring(st->fileName()).c_str());

                    __spf_printToLongBuf(messageR, R169, to_wstring(st->fileName()).c_str());

                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), messageR, messageE, 5005));
                    retVal = false;
                }
                ++count;
                exprList = exprList->rhs();
            }
            break;
        }
        default:
            retVal = false;
            break;
        }
    }

    return retVal;
}

static int countSPF_OP(Statement *stIn, const int type, const int op)
{
    int count = 0;
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ type }))
        {
            SgExpression *exprList = data->expr(0);
            while (exprList)
            {
                if (exprList->lhs()->variant() == op)
                    ++count;

                exprList = exprList->rhs();
            }
        }
    }
    return count;
}

static bool isSPF_OP(Statement *stIn, const int op)
{
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        SgExpression *exprList = st->expr(0);
        while (exprList)
        {
            if (exprList->lhs() && exprList->lhs()->variant() == op)
                return true;
            exprList = exprList->rhs();
        }
    }
    return false;
}

static inline bool processStat(SgStatement *st, const string &currFile,
                               const map<string, CommonBlock> *commonBlocks,
                               vector<Messages> &messagesForFile)
{
    bool retVal = true;

    if (st->variant() == SPF_PARALLEL_REG_DIR || st->variant() == SPF_END_PARALLEL_REG_DIR)
    {
        bool result = checkParallelRegions(st, commonBlocks, messagesForFile);
        retVal = retVal && result;
    }
    
    // ignore SPF statements
    if (isSPF_stat(st))
        return retVal;

    addSPFtoAttr(st, currFile);

    for (int i = 0; i < st->numberOfAttributes(); ++i)
    {
        SgAttribute *attr = st->getAttribute(i);
        SgStatement *attributeStatement = (SgStatement *)(attr->getAttributeData());
        int type = st->attributeType(i);
        if (type == SPF_ANALYSIS_DIR)
        {
            // !$SPF ANALYSIS
            // PRIVATE(VAR)
            set<SgSymbol*> privates;
            fillPrivatesFromComment(new Statement(attributeStatement), privates);
            if (privates.size())
            {
                bool result = checkPrivate(st, attributeStatement, privates, messagesForFile);
                retVal = retVal && result;
            }

            // REDUCTION(OP(VAR), MIN/MAXLOC(VAR, ARRAY, CONST))
            map<string, set<SgSymbol*>> reduction;
            map<string, set<tuple<SgSymbol*, SgSymbol*, int>>> reductionLoc;
            fillReductionsFromComment(new Statement(attributeStatement), reduction);
            fillReductionsFromComment(new Statement(attributeStatement), reductionLoc);
            if (reduction.size())
            {
                bool result = checkReduction(st, attributeStatement, reduction, messagesForFile);
                bool resultLoc = checkReduction(st, attributeStatement, reductionLoc, messagesForFile);
                retVal = retVal && result && resultLoc;
            }
        }
        else if (type == SPF_PARALLEL_DIR)
        {
            // !$SPF PARALLEL
            // SHADOW (VAR(list of  shadows)) / ACROSS (VAR(list of  shadows))
            vector<pair<pair<SgSymbol*, string>, vector<pair<int, int>>>> data;
            fillShadowAcrossFromComment(SHADOW_OP, new Statement(attributeStatement), data);
            fillShadowAcrossFromComment(ACROSS_OP, new Statement(attributeStatement), data);
            if (data.size())
            {
                bool result = checkShadowAcross(st, attributeStatement, data, messagesForFile);
                retVal = retVal && result;
            }

            // REMOTE_ACCESS (EXPR)
            map<pair<SgSymbol*, string>, Expression*> remote;
            fillRemoteFromComment(new Statement(attributeStatement), remote, true);
            if (remote.size())
            {
                bool result = checkRemote(st, attributeStatement, remote, messagesForFile);
                retVal = retVal && result;
            }
        }
        else if (type == SPF_TRANSFORM_DIR)
        {
            // !$SPF TRANSFORM
            int count;

            // NOINLINE
            if (isSPF_NoInline(new Statement(st)))
            {
                SgStatement *prev = st->lexPrev();
                const int prevVar = prev->variant();
                if (prevVar != PROC_HEDR && prevVar != FUNC_HEDR)
                {
                    BAD_POSITION_FULL(1, ERROR, "after", RR1_4, "", L"", "function statements", RR1_6, attributeStatement->lineNumber());
                    retVal = false;
                }
            }

            // FISSION
            if (isSPF_OP(new Statement(attributeStatement), SPF_FISSION_OP) && (count = countSPF_OP(new Statement(st), SPF_TRANSFORM_DIR, SPF_FISSION_OP)))
            {
                attributeStatement->setLocalLineNumber(-1);
                if (count > 1 || st->variant() != FOR_NODE)
                {
                    BAD_POSITION_FULL(1, ERROR, "once", RR1_7, "before", RR1_1, "DO statement", RR1_3, attributeStatement->lineNumber());
                    retVal = false;
                }
                else
                    retVal = checkFissionPrivatesExpansion(st, attributeStatement, currFile, messagesForFile, true);
            }

            // PRIVATES_EXPANSION
            if (isSPF_OP(new Statement(attributeStatement), SPF_PRIVATES_EXPANSION_OP) && (count = countSPF_OP(new Statement(st), SPF_TRANSFORM_DIR, SPF_PRIVATES_EXPANSION_OP)))
            {
                attributeStatement->setLocalLineNumber(-1);
                if (count > 1 || st->variant() != FOR_NODE)
                {
                    BAD_POSITION_FULL(1, ERROR, "once", RR1_7, "before", RR1_1, "DO statement", RR1_3, attributeStatement->lineNumber());
                    retVal = false;
                }
                else
                    retVal = checkFissionPrivatesExpansion(st, attributeStatement, currFile, messagesForFile);
            }

            // SHRINK
            if (isSPF_OP(new Statement(attributeStatement), SPF_SHRINK_OP))
            {
                attributeStatement->setLocalLineNumber(-1); // is it needed?
                if (st->variant() != FOR_NODE)
                {
                    BAD_POSITION_FULL(1, ERROR, "only", RR1_8, "before", RR1_1, "DO statement", RR1_3, attributeStatement->lineNumber());
                    retVal = false;
                }
                else
                    retVal = checkShrink(st, attributeStatement, currFile, messagesForFile);
            }
        }
        else if (type == SPF_CHECKPOINT_DIR)
        {
            map<int, SgExpression*> clauses;
            set<SgSymbol*> vars;
            fillCheckpointFromComment(new Statement(attributeStatement), clauses, vars);
            if (clauses.size())
                retVal = checkCheckpoint(st, attributeStatement, clauses, vars, messagesForFile);
        }
    }

    return retVal;
}

static bool processModules(vector<SgStatement*> &modules, const string &currFile, const map<string, CommonBlock> *commonBlocks, vector<Messages> &messagesForFile)
{
    bool retVal = true;

    for (int i = 0; i < modules.size(); ++i)
    {
        SgStatement *modIterator = modules[i];
        SgStatement *modEnd = modules[i]->lastNodeOfStmt();
        while (modIterator != modEnd)
        {
            if (modIterator->variant() == CONTAINS_STMT)
                break;

            bool result = processStat(modIterator, currFile, commonBlocks, messagesForFile);
            retVal = retVal && result;

            SgStatement *next = modIterator->lexNext();
            if (next)
                if (next->variant() == SPF_END_PARALLEL_REG_DIR)
                    addToattribute(next, modIterator, SPF_END_PARALLEL_REG_DIR);

            modIterator = modIterator->lexNext();
        }
    }

    return retVal;
}

bool check_par_reg_dirs(SgFile *file, vector<Messages> &messagesForFile)
{
    int funcNum = file->numberOfFunctions();
    const string currFile = file->filename();

    bool noError = true;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        while (st != lastNode)
        {            
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            if (st->variant() == SPF_PARALLEL_REG_DIR || st->variant() == SPF_END_PARALLEL_REG_DIR)
            {
                bool result = checkParallelRegions(st, NULL, messagesForFile);
                noError = noError && result;
            }                       
            st = st->lexNext();
        }
    }

    return noError;
}

bool preprocess_spf_dirs(SgFile *file, const map<string, CommonBlock> &commonBlocks, vector<Messages> &messagesForFile)
{
    int funcNum = file->numberOfFunctions();
    const string currFile = file->filename();

    bool noError = true;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        while (st != lastNode)
        {            
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            bool result = processStat(st, currFile, &commonBlocks, messagesForFile);
            noError = noError && result;

            SgStatement *next = st->lexNext();
            if (next)
                if (next->variant() == SPF_END_PARALLEL_REG_DIR)
                    addToattribute(next, st, SPF_END_PARALLEL_REG_DIR);
            st = st->lexNext();
        }
    }

    vector<SgStatement*> modules;
    findModulesInFile(file, modules);
    bool result = processModules(modules, currFile, &commonBlocks, messagesForFile);
    noError = noError && result;
    return noError;
}

static void LinkTree(SgExpression *mainExp, SgExpression *exp) 
{
    SgExpression *copyExp = &(exp->copy());
    SgExpression *rhs = mainExp->rhs();
    while (rhs) 
    {
        SgExpression *a = rhs;
        rhs = mainExp->rhs();
        mainExp = a;
    }
    mainExp->setRhs(copyExp);
}       

static void OptimizeTree(SgExpression *exp) 
{
    while (exp) 
    {
        SgExpression *checkExp = exp->lhs();
        SgExpression *currExp = exp->rhs();

        SgExpression *prevExp = exp;
        int var = checkExp->variant();

        while (currExp) 
        {
            SgExpression *lhs = currExp->lhs();
            SgExpression *rhs = currExp->rhs();
            if (lhs) 
            {
                if (lhs->variant() == var) 
                {
                    prevExp->setRhs(rhs);
                    LinkTree(checkExp->lhs(), lhs->lhs());
                }
                else
                    prevExp = currExp;
                currExp = rhs;
            }
        }
        exp = exp->rhs();
    }
}

static SgStatement* GetOneAttribute(const vector<SgStatement*> &sameAtt) 
{
    set<string> uniqAttrs;
    SgStatement *toAddExp = NULL;
    for (auto &elem : sameAtt) 
    {
        if (elem->expr(0) == NULL)
            continue;

        const string currAtr(elem->unparse());
        auto it = uniqAttrs.find(currAtr);
        if (it == uniqAttrs.end())
            uniqAttrs.insert(it, currAtr);
        else
            continue;

        if (toAddExp) 
        {
            SgExpression *exp = elem->expr(0);
            LinkTree(toAddExp->expr(0), exp);
        }
        else
            toAddExp = &(elem->copy());
    }
    
    if (toAddExp)
        OptimizeTree(toAddExp->expr(0));

    //check null of expressions
    if (toAddExp)
    {
        vector<SgExpression*> list;
        SgExpression* ex = toAddExp->expr(0);

        bool deleted = false;
        while (ex)
        {
            if (ex->lhs()->lhs())
                list.push_back(ex->lhs());
            else
                deleted = true;
            ex = ex->rhs();
        }
        if (deleted)
            toAddExp->setExpression(0, makeExprList(list));
    }

    return toAddExp;
}

static vector<SgStatement*> filterUserSpf(const vector<SgStatement*> &toFilter)
{
    vector<SgStatement*> ret;
    for (auto &elem : toFilter)
        if (elem->localLineNumber() == 777 || elem->localLineNumber() == 888) // user and omp
            ret.push_back(elem);

    return ret;
}

void revertion_spf_dirs(SgFile *file,
                        map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaredArrays,
                        map<SgStatement*, set<tuple<int, string, string>>> declaratedArraysSt)
{
    const string fileName(file->filename());

    vector<SgStatement*> units;
    getModulesAndFunctions(file, units);

    for (int i = 0; i < units.size(); ++i)
    {
        SgStatement *st = units[i];
        SgStatement *lastNode = st->lastNodeOfStmt();

        int count = 0;
        while (st != lastNode) 
        {
            count++;
            if (st == NULL) 
            {
                __spf_print(1, "internal error in analysis, spf directives will not be returned for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            //analyze attributes
            SgAttribute *atrib = st->getAttribute(0);
            SgStatement *toAdd = NULL;

            if (atrib && st->fileName() == fileName)
            {
                //check previosly directives SPF_ANALYSIS
                vector<SgStatement*> sameAtt = filterUserSpf(getAttributes<SgStatement*, SgStatement*>(st, set<int>{SPF_ANALYSIS_DIR}));

                if (sameAtt.size())
                {
                    toAdd = GetOneAttribute(sameAtt);
                    if (toAdd)
                        st->insertStmtBefore(*toAdd, *st->controlParent());
                }

                //check previosly directives SPF_PARALLEL
                if (sameAtt.size())
                {
                    sameAtt = filterUserSpf(getAttributes<SgStatement*, SgStatement*>(st, set<int>{SPF_PARALLEL_DIR}));
                    for (auto &elem : sameAtt)
                    {
                        if (toAdd)
                            toAdd = GetOneAttribute(sameAtt);
                        st->insertStmtBefore(*toAdd, *st->controlParent());
                    }
                } 

                //remaining directives
                sameAtt = filterUserSpf(getAttributes<SgStatement*, SgStatement*>(st, set<int>{SPF_CHECKPOINT_DIR, SPF_TRANSFORM_DIR, SPF_NOINLINE_OP, SPF_REGION_NAME}));
                if (sameAtt.size())
                {
                    for (auto &elem : sameAtt)
                    {
                        SgStatement *data = (SgStatement *)atrib->getAttributeData();
                        SgStatement *toAdd = &(data->copy());

                        if (toAdd)
                            st->insertStmtBefore(*toAdd, *st->controlParent());
                    }
                }
            }
            st = st->lexNext();
        }
    }
}

void addAcrossToLoops(LoopGraph *topLoop,
                      const map<SgSymbol*, tuple<int, int, int>> &acrossToAdd,
                      const map<int, SgForStmt*> &allLoops,
                      vector<Messages> &currMessages)
{
    if (acrossToAdd.size() != 0)
    {
        SgStatement *acrSpf = new SgStatement(SPF_PARALLEL_DIR, NULL, NULL, NULL, NULL, NULL);
        SgExpression *exprList = new SgExpression(EXPR_LIST, new SgExpression(ACROSS_OP), NULL, NULL);
        acrSpf->setExpression(0, *exprList);
        exprList = exprList->lhs();
        SgExpression *newList = new SgExpression(EXPR_LIST);
        exprList->setLhs(newList);
        exprList = exprList->lhs();
        
        int k = 0;
        for (auto it = acrossToAdd.begin(); it != acrossToAdd.end(); ++it, ++k)
        {
            SgSymbol *arrayS = it->first;
            int pos = std::get<2>(it->second);
            pair<int, int> ref = std::make_pair(std::get<0>(it->second), std::get<1>(it->second));

            SgArrayType *arrType = isSgArrayType(arrayS->type());
            if (!arrType)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            if (arrType->dimension() <= pos)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            SgArrayRefExp *toAdd = new SgArrayRefExp(*arrayS);
            for (int z = 0; z < arrType->dimension(); ++z)
            {
                if (z == pos)
                {
                    SgValueExp *tmp = new SgValueExp(ref.first);
                    SgValueExp *tmp1 = new SgValueExp(ref.second);
                    SgExpression *tmp2 = new SgExpression(DDOT, tmp, tmp1, NULL);
                    toAdd->addSubscript(*tmp2);
                }
                else
                {
                    SgValueExp *tmp = new SgValueExp(0);
                    SgValueExp *tmp1 = new SgValueExp(0);
                    SgExpression *tmp2 = new SgExpression(DDOT, tmp, tmp1, NULL);
                    toAdd->addSubscript(*tmp2);
                }
            }

            exprList->setLhs(toAdd);

            if (consoleMode)
                printf("  add across dependencies by array '%s' for loop on line %d\n", arrayS->identifier(), topLoop->lineNum);

            wstring messageE, messageR;
            __spf_printToLongBuf(messageE, L"add across dependencies by array '%s' to loop", to_wstring(arrayS->identifier()).c_str());

            __spf_printToLongBuf(messageR, R108, to_wstring(arrayS->identifier()).c_str());

            currMessages.push_back(Messages(NOTE, topLoop->lineNum, messageR, messageE, 3001));

            if (k != acrossToAdd.size() - 1)
            {
                SgExpression *tmp = new SgExpression(EXPR_LIST);
                exprList->setRhs(tmp);
                exprList = exprList->rhs();
            }
        }
        
        auto it = allLoops.find(topLoop->lineNum);
        if (it == allLoops.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        it->second->addAttribute(SPF_PARALLEL_DIR, acrSpf, sizeof(SgStatement));
    }
}

void addPrivatesToLoops(LoopGraph *topLoop, 
                        const vector<const depNode*> &privatesToAdd,
                        const map<int, SgForStmt*> &allLoops,
                        vector<Messages> &currMessages)
{
    if (privatesToAdd.size() != 0)
    {
        vector<const depNode*> addForCurrLoop;
        for (int i = 0; i < privatesToAdd.size(); ++i)
        {
            const int privLine = privatesToAdd[i]->stmtin->lineNumber();
            if (topLoop->lineNum < privLine && topLoop->lineNumAfterLoop > privLine)
                addForCurrLoop.push_back(privatesToAdd[i]);
        }

        if (addForCurrLoop.size())
        {
            SgStatement *privSpf = new SgStatement(SPF_ANALYSIS_DIR, NULL, NULL, NULL, NULL, NULL);

            SgExpression *tmp = new SgExpression(ACC_PRIVATE_OP);
            SgExpression *exprList = new SgExpression(EXPR_LIST, tmp, NULL, NULL);
            privSpf->setExpression(0, *exprList);
            exprList = exprList->lhs();

            SgExpression *tmp1 = new SgExpression(EXPR_LIST);
            exprList->setLhs(tmp1);
            exprList = exprList->lhs();

            auto itLoop = allLoops.find(topLoop->lineNum);
            if (itLoop == allLoops.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            set<string> added;
            for (auto &data : getAttributes<SgStatement*, SgStatement*>(itLoop->second, set<int>{ SPF_ANALYSIS_DIR }))
                fillPrivatesFromComment(new Statement(data), added);

            int uniq = 0;
            int k = 0;
            while (k != addForCurrLoop.size())
            {
                string identifier = addForCurrLoop[k]->varin->symbol()->identifier();
                auto itF = added.find(identifier);
                if (itF == added.end())
                    itF = added.insert(itF, identifier);
                else
                {
                    addForCurrLoop.erase(addForCurrLoop.begin() + k);
                    continue;
                }
                k++;
                uniq++;
            }

            for (int k = 0; k < addForCurrLoop.size(); ++k)
            {
                string identifier = addForCurrLoop[k]->varin->symbol()->identifier();
                exprList->setLhs(addForCurrLoop[k]->varin);
                if (consoleMode)
                    printf("  add private scalar '%s' for loop on line %d\n", identifier.c_str(), topLoop->lineNum);

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"add private scalar '%s' to loop on line %d", to_wstring(identifier).c_str(), topLoop->lineNum);

                __spf_printToLongBuf(messageR, R109, to_wstring(identifier).c_str(), topLoop->lineNum);

                currMessages.push_back(Messages(NOTE, addForCurrLoop[k]->stmtin->lineNumber(), messageR, messageE, 3002));

                if (k != addForCurrLoop.size() - 1)
                {
                    SgExpression *tmp = new SgExpression(EXPR_LIST);
                    exprList->setRhs(tmp);
                    exprList = exprList->rhs();
                }
            }

            if (uniq > 0)
                itLoop->second->addAttribute(SPF_ANALYSIS_DIR, privSpf, sizeof(SgStatement));
        }
    }
}

static bool addReductionToList(const char *oper, SgExpression *exprList, SgExpression *varin)
{
    SgExpression *tmp3 = new SgKeywordValExp(oper);
    SgExpression *tmp4 = new SgExpression(ARRAY_OP, tmp3, varin, NULL);
    exprList->setLhs(tmp4);
    return true;
}

void addReductionsToLoops(LoopGraph *topLoop,
                          const vector<const depNode*> &reductionsToAdd,
                          const map<int, SgForStmt*> &allLoops,
                          vector<Messages> &currMessages)
{
    if (reductionsToAdd.size() != 0)
    {
        vector<const depNode*> addForCurrLoop;
        for (int i = 0; i < reductionsToAdd.size(); ++i)
        {
            const int privLine = reductionsToAdd[i]->stmtin->lineNumber();
            if (topLoop->lineNum < privLine && topLoop->lineNumAfterLoop > privLine)
                addForCurrLoop.push_back(reductionsToAdd[i]);
        }

        if (addForCurrLoop.size())
        {
            SgStatement *redSpf = new SgStatement(SPF_ANALYSIS_DIR, NULL, NULL, NULL, NULL, NULL);

            SgExpression *tmp = new SgExpression(REDUCTION_OP);
            SgExpression *exprList = new SgExpression(EXPR_LIST, tmp, NULL, NULL);
            redSpf->setExpression(0, *exprList);
            exprList = exprList->lhs();

            SgExpression *tmp1 = new SgExpression(EXPR_LIST);
            exprList->setLhs(tmp1);
            exprList = exprList->lhs();

            bool wasAdd = false;
            for (int k = 0; k < addForCurrLoop.size(); ++k)
            {
                if (k != 0 && wasAdd)
                {
                    SgExpression *tmp = new SgExpression(EXPR_LIST);
                    exprList->setRhs(tmp);
                    exprList = exprList->rhs();
                }

                wasAdd = false;
                const char *oper = NULL;
                switch (addForCurrLoop[k]->kinddep)
                {
                case SADDREDUCTION:
                case DADDREDUCTION:
                case IADDREDUCTION:
                    oper = "sum";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                case SMULREDUCTION:
                case DMULREDUCTION:
                case IMULREDUCTION:
                    oper = "product";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                case SDIVREDUCTION:
                case DDIVREDUCTION:
                case IDIVREDUCTION:
                    break;
                case SMAXREDUCTION:
                case DMAXREDUCTION:
                case IMAXREDUCTION:
                    oper = "max";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                case SMINREDUCTION:
                case DMINREDUCTION:
                case IMINREDUCTION:
                    oper = "min";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                case ANDREDUCTION:
                    oper = "and";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                case ORREDUCTION:
                    oper = "or";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                case EQVREDUCTION:
                    oper = "eqv";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                case NEQVREDUCTION:
                    oper = "neqv";
                    wasAdd = addReductionToList(oper, exprList, addForCurrLoop[k]->varin);
                    break;
                default:
                    break;
                }

                if (wasAdd)
                {
                    if (consoleMode)
                        printf("  add reduction scalar '%s' with operation '%s' to loop on line %d\n", addForCurrLoop[k]->varin->symbol()->identifier(), oper, topLoop->lineNum);

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"add reduction scalar '%s' with operation '%s' to loop on line %d", 
                                         to_wstring(addForCurrLoop[k]->varin->symbol()->identifier()).c_str(), to_wstring(oper).c_str(), topLoop->lineNum);

                    __spf_printToLongBuf(messageR, R110,
                                         to_wstring(addForCurrLoop[k]->varin->symbol()->identifier()).c_str(), to_wstring(oper).c_str(), topLoop->lineNum);

                    currMessages.push_back(Messages(NOTE, addForCurrLoop[k]->stmtin->lineNumber(), messageR, messageE, 3003));
                }
                else
                {
                    if (consoleMode)
                        printf("  unknown type of reduction scalar '%s' on line %d\n", addForCurrLoop[k]->varin->symbol()->identifier(), addForCurrLoop[k]->stmtin->lineNumber());

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"unknown type of reduction scalar '%s'", to_wstring(addForCurrLoop[k]->varin->symbol()->identifier()).c_str());

                    __spf_printToLongBuf(messageR, R111, to_wstring(addForCurrLoop[k]->varin->symbol()->identifier()).c_str());

                    currMessages.push_back(Messages(WARR, addForCurrLoop[k]->stmtin->lineNumber(), messageR, messageE, 3004));

                    topLoop->hasUnknownScalarDep = true;
                    topLoop->linesOfScalarDep.push_back(addForCurrLoop[k]->stmtin->lineNumber());
                }
            }

            auto it = allLoops.find(topLoop->lineNum);
            if (it == allLoops.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            it->second->addAttribute(SPF_ANALYSIS_DIR, redSpf, sizeof(SgStatement));
        }
    }
}