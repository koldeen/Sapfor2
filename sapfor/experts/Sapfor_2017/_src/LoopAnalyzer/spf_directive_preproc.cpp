#include "../leak_detector.h"

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
#include "../transform.h"
#include "../GraphLoop/graph_loops.h"
#include "../SageAnalysisTool/depInterfaceExt.h"
#include "../SgUtils.h"
#include "../errors.h"
#include "../directive_parser.h"
#include "../ExpressionTransform/expr_transform.h"

using std::string;
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


    curr->addAttribute(variant, toAdd, sizeof(SgStatement));
    //copy comments to st
    if (toAttr->comments())
    {
        string comments(toAttr->comments());

        if (curr->comments())
            comments += "\n" + string(curr->comments());
        if (comments.size() != 0)
            curr->setComments(comments.c_str());
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
        fillPrivatesFromComment(data, privates);

        retVal = retVal || privates.find(symbol->identifier()) != privates.end();
        if (retVal)
            break;
    }

    return retVal;
}

#define BAD_POSITION(NEED_PRINT, ERR_TYPE, PLACE, BEFORE_VAR, BEFORE_DO, LINE) do { \
   __spf_print(1, "bad directive position on line %d, it can be placed only %s %s %s\n", LINE, PLACE, BEFORE_VAR, BEFORE_DO); \
   string message;\
   __spf_printToBuf(message, "bad directive position, it can be placed only %s %s %s", PLACE, BEFORE_VAR, BEFORE_DO); \
   messagesForFile.push_back(Messages(ERR_TYPE, LINE, message, 1001)); \
} while(0)

static void fillVarsSets(SgStatement *iterator, SgStatement *end, set<SgSymbol*> &varDef, set<SgSymbol*> &varUse)
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
            if (iterator->variant() == ASSIGN_STAT || isSgExecutableStatement(iterator) == false)
                fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varDef, funcCalls);
            else
                fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varUse, funcCalls);

            fillVars(iterator->expr(1), { ARRAY_REF, VAR_REF }, varUse, funcCalls);
            fillVars(iterator->expr(2), { ARRAY_REF, VAR_REF }, varUse, funcCalls);

            if (iterator->variant() == FOR_NODE)
            {
                auto loop = isSgForStmt(iterator);
                varDef.insert(loop->doName());
                varUse.insert(loop->doName());
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
        SgStatement *iterator = var == FOR_NODE ? st->lexNext() : st;
        SgStatement *end = var == FOR_NODE ? st->lastNodeOfStmt() : st->lexNext();
        set<SgSymbol*> varDef;
        set<SgSymbol*> varUse;

        fillVarsSets(iterator, end, varDef, varUse);
        
        for (auto &privElem : privates)
        {
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
                    __spf_print(1, "variable '%s' is not used in loop on line %d\n", privElem->identifier(), attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "variable '%s' is not used in loop", privElem->identifier());
                    messagesForFile.push_back(Messages(WARR, attributeStatement->lineNumber(), message, 1002));
                }
                else if (!defCond && useCond)
                {
                    __spf_print(1, "variable '%s' is not changed in loop on line %d\n", privElem->identifier(), attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "variable '%s' is not changed in loop", privElem->identifier());
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1003));
                    retVal = false;
                }
            }
            else
            {
                if (!defCond)
                {
                    BAD_POSITION(1, ERROR, "before", "variable declaration or", "DO statement", attributeStatement->lineNumber());                    
                    retVal = false;
                }
            }
        }
    }
    else
    {
        BAD_POSITION(1, ERROR, "before", "variable declaration or", "DO statement", attributeStatement->lineNumber());
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
        set<SgSymbol*> varDef;
        set<SgSymbol*> varUse;

        fillVarsSets(iterator, end, varDef, varUse);

        for (auto &redElem : reduction)
        {
            for (auto &setElem : redElem.second)
            {
                bool defCond = true;
                bool useCond = true;

                if (varDef.find(setElem) == varDef.end())
                    defCond = false;
                if (varUse.find(setElem) == varUse.end())
                    useCond = false;

                if (var == FOR_NODE && !defCond && !useCond)
                {
                    __spf_print(1, "variable '%s' is not used in loop on line %d\n", setElem->identifier(), attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "variable '%s' is not used in loop", setElem->identifier());
                    messagesForFile.push_back(Messages(WARR, attributeStatement->lineNumber(), message, 1002));
                }
                if (var == FOR_NODE && !defCond && useCond)
                {
                    __spf_print(1, "variable '%s' is not changed in loop on line %d\n", setElem->identifier(), attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "variable '%s' is not changed in loop", setElem->identifier());
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1003));
                    retVal = false;
                }
            }
        }
    }
    else
    {
        BAD_POSITION(1, ERROR, "before", "", "DO statement", attributeStatement->lineNumber());
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
    map<string, set<SgSymbol*>> reductionVar;
    map<string, set<SgSymbol*>> reductionArr;

    for (auto &redElem : reduction)
    {
        set<SgSymbol*> vars;
        set<SgSymbol*> arrs;

        for (auto &setElem : redElem.second)
        {
            vars.insert(std::get<0>(setElem));
            arrs.insert(std::get<1>(setElem));

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

                    string message;
                    __spf_printToBuf(message, "dimention of array '%s' is %d, but must be 1", arraySymbol->identifier(), dim);
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1004));

                    retVal = false;
                }

                if (!arrayType->baseType()->equivalentToType(SgTypeInt()))
                {
                    __spf_print(1, "type of array '%s' must be INTEGER on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                    string message;
                    __spf_printToBuf(message, "type of array '%s' but must be INTEGER", arraySymbol->identifier());
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1005));

                    retVal = false;
                }
            }
            else
            {
                __spf_print(1, "type of variable '%s' must be array on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());

                string message;
                __spf_printToBuf(message, "type of variable '%s' must be array", arraySymbol->identifier());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1006));

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

                            string message;
                            __spf_printToBuf(message, "array size can't be computed");
                            messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1007));

                            retVal = false;
                        }
                        else if (size != count)
                        {
                            __spf_print(1, "size of array '%s' is %d, but you enter %d on line %d\n",
                                arraySymbol->identifier(), size, count, attributeStatement->lineNumber());

                            string message;
                            __spf_printToBuf(message, "size of array '%s' is %d, but you enter %d", arraySymbol->identifier(), size, count);
                            messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1008));

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

        reductionVar.insert(reductionVar.begin(), make_pair(redElem.first, vars));
        reductionArr.insert(reductionArr.begin(), make_pair(redElem.first, arrs));

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
                string message;
                __spf_printToBuf(message, "variable '%s' is not array", arraySymbol->identifier());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1006));
                retVal = false;
            }
            //__spf_print(1, "isPriv(decl, %s) = %d\n", arraySymbol->identifier(), varIsPrivate(declStatement, arraySymbol));
            notPrivCond = !isPrivateVar(st, arraySymbol) && !isPrivateVar(declStatement, arraySymbol);

            if (!notPrivCond)
            {
                __spf_print(1, "array '%s' on line %d is private\n", arraySymbol->identifier(), attributeStatement->lineNumber());
                string message;
                __spf_printToBuf(message, "array '%s' is private", arraySymbol->identifier());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1009));
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
                    __spf_print(1, "dimention of array '%s' is %d, but you enter %d on line %d\n", arraySymbol->identifier(), arrayType->dimension(), (int)arrayDisc.size(), attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "dimention of array '%s' is %d, but you enter %d", arraySymbol->identifier(), arrayType->dimension(), (int)arrayDisc.size());
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1008));
                    retVal = false;
                }
            }
            else
            {
                __spf_print(1, "variable '%s' is not array on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());
                string message;
                __spf_printToBuf(message, "variable '%s' is not array", arraySymbol->identifier());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1006));
                retVal = false;
            }

            for (auto &array : arrayDisc)
            {
                if (array.first < 0 || array.second < 0)
                {
                    __spf_print(1, "only positive numbers are supported on line %d\n", attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "only positive numbers are supported");
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1010));
                    retVal = false;
                }
            }
        }
    }
    else
    {
        BAD_POSITION(1, ERROR, "before", "", "DO statement", attributeStatement->lineNumber());
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
                    string message;
                    __spf_printToBuf(message, "array '%s' is private", arraySymbol->identifier());
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1009));
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
                                string message;
                                __spf_printToBuf(message, "bad directive expression: too many DO variables");
                                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1001));
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
                                string message;
                                __spf_printToBuf(message, "bad directive expression: only a * i + b");
                                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1001));
                                retVal = false;
                            }
                        }
                    }

                    remoteExp = remoteExp->rhs();
                }
            }
                        
            SgStatement *iterator = st;
            SgStatement *end = var == FOR_NODE ? st->lastNodeOfStmt() : st->lexNext();

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
                string message;
                __spf_printToBuf(message, "no such expression '%s' on loop", remElem.second->unparse());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message, 1111));
                retVal = false;
            }
        }
    }
    else
    {
        BAD_POSITION(1, ERROR, "before", "", "DO statement", attributeStatement->lineNumber());
        retVal = false;
    }

    return retVal;
}

static bool checkParallelRegions(SgStatement *st,
                                 const map<string, CommonBlock> &commonBlocks,
                                 vector<Messages> &messagesForFile)
{
    bool retVal = true;

    if (isSgExecutableStatement(st->lexNext()))
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
                    for (SgExpression *exp = iterator->expr(0); exp && retVal; exp = exp->rhs())
                    {
                        for (SgExpression *currExp = exp->variant() == COMM_LIST ? exp->lhs() : exp; currExp && retVal; currExp = currExp->rhs())
                        {
                            if (!strcmp(currExp->lhs()->symbol()->identifier(), identSymbol->identifier()))
                            {
                                __spf_print(1, "variable '%s' was declarated on line %d on line %d\n", identSymbol->identifier(), iterator->lineNumber(), st->lineNumber());

                                string message;
                                __spf_printToBuf(message, "variable '%s' was declarated on line %d", identSymbol->identifier(), iterator->lineNumber());
                                messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1031));

                                retVal = false;
                            }
                        }
                    }
                }
                else
                    break;
            }

            // common blocks checking
            for (auto &commonBlockPair : commonBlocks)
            {
                for (auto &variable : commonBlockPair.second.getVariables())
                {
                    if (variable.getName() == identSymbol->identifier())
                    {
                        __spf_print(1, "variable '%s' was declarated in common-block '%s' on line %d\n", identSymbol->identifier(), commonBlockPair.first.c_str(), st->lineNumber());

                        string message;
                        __spf_printToBuf(message, "variable '%s' was declarated in common-block '%s'", identSymbol->identifier(), commonBlockPair.first.c_str());
                        messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1032));

                        retVal = false;
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
                    __spf_print(1, "bad directive expression: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s', but got 'SPF PARALLEL_REG_DIR' on line %d\n", identSymbol->identifier(), st->lineNumber());

                    string message;
                    __spf_printToBuf(message, "bad directive expression: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s', but got 'SPF PARALLEL_REG_DIR'", identSymbol->identifier());
                    messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1001));

                    retVal = false;
                    break;
                }
                else if (var == SPF_END_PARALLEL_REG_DIR)
                {
                    found = true;

                    if (iterator->controlParent() != st->controlParent())
                    {
                        __spf_print(1, "bad directive expression: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s' at the same scope on line %d\n",
                            identSymbol->identifier(), st->lineNumber());

                        string message;
                        __spf_printToBuf(message, "bad directive expression: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s' at the same scope on line",
                            identSymbol->identifier());
                        messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1001));

                        found = true;
                        retVal = false;
                        break;
                    }

                    break;
                }
            }

            if (!found)
            {
                __spf_print(1, "bad directive expression: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s' on line %d\n", identSymbol->identifier(), st->lineNumber());

                string message;
                __spf_printToBuf(message, "bad directive expression: expected 'SPF END PARALLEL_REG_DIR' for identificator '%s'", identSymbol->identifier());
                messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1001));

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
                    __spf_print(1, "bad directive expression: expected 'SPF PARALLEL_REG_DIR', but got 'SPF END PARALLEL_REG_DIR' on line %d\n", st->lineNumber());

                    string message;
                    __spf_printToBuf(message, "bad directive expression: expected 'SPF PARALLEL_REG_DIR', but got 'SPF END PARALLEL_REG_DIR'");
                    messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1001));

                    retVal = false;
                    break;
                }
                else if (var == SPF_PARALLEL_REG_DIR)
                {
                    found = true;

                    if (iterator->controlParent() != st->controlParent())
                    {
                        __spf_print(1, "bad directive expression: expected 'SPF PARALLEL_REG_DIR' at the same scope on line %d\n", st->lineNumber());

                        string message;
                        __spf_printToBuf(message, "bad directive expression: expected 'SPF PARALLEL_REG_DIR' at the same scope");
                        messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1001));

                        retVal = false;
                        break;
                    }

                    break;
                }
            }

            if (!found)
            {
                __spf_print(1, "bad directive expression: expected 'SPF PARALLEL_REG_DIR' on line %d\n", st->lineNumber());

                string message;
                __spf_printToBuf(message, "bad directive expression: expected 'SPF PARALLEL_REG_DIR'");
                messagesForFile.push_back(Messages(ERROR, st->lineNumber(), message, 1001));

                retVal = false;
            }
        }
    }
    else
    {
        BAD_POSITION(1, ERROR, "after", "", "all DATA statements", st->lineNumber());
        retVal = false;
    }

    return retVal;
}

static inline bool processStat(SgStatement *st, const string &currFile,
                               const map<string, CommonBlock> &commonBlocks,
                               vector<Messages> &messagesForFile)
{
    bool retVal = true;

    if (st->variant() == SPF_PARALLEL_REG_DIR || st->variant() == SPF_END_PARALLEL_REG_DIR)
    {
        bool result = checkParallelRegions(st, commonBlocks, messagesForFile);
        retVal = retVal && result;
    }

    // ignore SPF statements
    if (isSPF_comment(st->variant()))
        return retVal;

    bool cond = false;
    SgStatement *iterator = st;
    do
    {
        SgStatement *prev = iterator->lexPrev();
        const int prevVar = prev->variant();
        cond = (isSPF_comment(prev->variant()) && prevVar != SPF_END_PARALLEL_REG_DIR);
        if (cond)
        {
            addToattribute(prev, st, prevVar);

            if ((prev->fileName() == currFile) && prevVar != SPF_PARALLEL_REG_DIR)
                prev->deleteStmt();
            else
                iterator = prev;
        }
    } while (cond);

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
            fillPrivatesFromComment(attributeStatement, privates);
            if (privates.size())
            {
                bool result = checkPrivate(st, attributeStatement, privates, messagesForFile);
                retVal = retVal && result;
            }

            // REDUCTION(OP(VAR), MIN/MAXLOC(VAR, ARRAY, CONST))
            map<string, set<SgSymbol*>> reduction;
            map<string, set<tuple<SgSymbol*, SgSymbol*, int>>> reductionLoc;
            fillReductionsFromComment(attributeStatement, reduction);
            fillReductionsFromComment(attributeStatement, reductionLoc);
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
            fillShadowAcrossFromComment(SHADOW_OP, attributeStatement, data);
            fillShadowAcrossFromComment(ACROSS_OP, attributeStatement, data);
            if (data.size())
            {
                bool result = checkShadowAcross(st, attributeStatement, data, messagesForFile);
                retVal = retVal && result;
            }

            // REMOTE_ACCESS (EXPR)
            map<pair<SgSymbol*, string>, Expression*> remote;
            fillRemoteFromComment(attributeStatement, remote, true);
            if (remote.size())
            {
                bool result = checkRemote(st, attributeStatement, remote, messagesForFile);
                retVal = retVal && result;
            }
        }
        else if (type == SPF_TRANSFORM_DIR)
        {
            // !$SPF TRANSFORM
            // NOINLINE
            if (isSPF_NoInline(st))
            {
                SgStatement *prev = st->lexPrev();
                const int prevVar = prev->variant();
                if (prevVar != PROC_HEDR && prevVar != FUNC_HEDR)
                {
                    BAD_POSITION(1, ERROR, "after", "", "function statement", attributeStatement->lineNumber());
                    retVal = false;
                }
            }
        }
    }

    return retVal;
}

static bool processModules(vector<SgStatement*> &modules, const string &currFile, const map<string, CommonBlock> &commonBlocks, vector<Messages> &messagesForFile)
{
    bool retVal = true;

    for (int i = 0; i < modules.size(); ++i)
    {
        SgStatement *modIterator = modules[i];
        SgStatement *modEnd = modules[i]->lastNodeOfStmt();
        while (modIterator != modEnd)
        {
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
            currProcessing.second = NULL;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            bool result = processStat(st, currFile, commonBlocks, messagesForFile);
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
    bool result = processModules(modules, currFile, commonBlocks, messagesForFile);
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

SgStatement* GetOneAttribute(vector<SgStatement*> sameAtt) 
{
    SgStatement *toAddExp = NULL;
    for (auto &elem : sameAtt) 
    {
        if (toAddExp) 
        {
            SgExpression *exp = elem->expr(0);
            LinkTree(toAddExp->expr(0), exp);
        }
        else
            toAddExp = &(elem->copy());
    }
    OptimizeTree(toAddExp->expr(0));
    return toAddExp;
}

void revertion_spf_dirs(SgFile *file) 
{
    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; i++) 
    {
        SgStatement *st = file->functions(i);
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
            //analyze attributes
            SgAttribute *atrib = st->getAttribute(0);

            if (atrib) 
            {
                //check previosly directives SPF_ANALYSIS
                vector<SgStatement*> sameAtt = getAttributes<SgStatement*, SgStatement*>(st, set<int>{SPF_ANALYSIS_DIR});

                SgStatement *toAddExp = GetOneAttribute(sameAtt);
                st->insertStmtBefore(*toAddExp);

                //check previosly directives SPF_PARALLEL
                sameAtt = getAttributes<SgStatement*, SgStatement*>(st, set<int>{SPF_PARALLEL_DIR});
                for (auto &elem : sameAtt) 
                {
                    SgStatement *toAddExp = GetOneAttribute(sameAtt);
                    st->insertStmtBefore(*toAddExp);
                }

                //remaining directives            
                sameAtt = getAttributes<SgStatement*, SgStatement*>(st, set<int>{SPF_TRANSFORM_DIR, SPF_NOINLINE_OP, SPF_REGION_NAME});
                for (auto &elem : sameAtt) 
                {
                    SgStatement *data = (SgStatement *)atrib->getAttributeData(); // SgStatement * - statement was hidden
                    SgStatement *toAdd = &(data->copy());

                    st->insertStmtBefore(*toAdd);
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

            string message;
            __spf_printToBuf(message, "add across dependencies by array '%s' to loop", arrayS->identifier());
            currMessages.push_back(Messages(NOTE, topLoop->lineNum, message, 3001));

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
                fillPrivatesFromComment(data, added);

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

                string message;
                __spf_printToBuf(message, "add private scalar '%s' to loop on line %d", identifier.c_str(), topLoop->lineNum);
                currMessages.push_back(Messages(NOTE, addForCurrLoop[k]->stmtin->lineNumber(), message, 3002));

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
    SgExpression *tmp4 = new SgExpression(EXPR_LIST, tmp3, varin, NULL);
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

                    string message;
                    __spf_printToBuf(message, "add reduction scalar '%s' with operation '%s' to loop on line %d", addForCurrLoop[k]->varin->symbol()->identifier(), oper, topLoop->lineNum);
                    currMessages.push_back(Messages(NOTE, addForCurrLoop[k]->stmtin->lineNumber(), message, 3003));
                }
                else
                {
                    if (consoleMode)
                        printf("  unknown type of reduction scalar '%s' on line %d\n", addForCurrLoop[k]->varin->symbol()->identifier(), addForCurrLoop[k]->stmtin->lineNumber());

                    string message;
                    __spf_printToBuf(message, "unknown type of reduction scalar '%s'", addForCurrLoop[k]->varin->symbol()->identifier());
                    currMessages.push_back(Messages(WARR, addForCurrLoop[k]->stmtin->lineNumber(), message, 3004));

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