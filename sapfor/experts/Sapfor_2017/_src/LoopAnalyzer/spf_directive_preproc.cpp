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

void fillVars(SgExpression *exp, const set<int> &types, set<SgSymbol*> &identifierList)
{
    if (exp)
    {
        if (types.find(exp->variant()) != types.end())
        {
            if (exp->symbol())
                identifierList.insert(OriginalSymbol(exp->symbol()));
            else if (exp->variant() == DDOT)
                identifierList.insert((SgSymbol*)exp); // BAD solution
        }
        
        fillVars(exp->lhs(), types, identifierList);
        fillVars(exp->rhs(), types, identifierList);
    }
}

static bool isPrivateVar(SgStatement *st, SgSymbol *symbol)
{
    bool retVal = false;

    for (int i = 0; i < st->numberOfAttributes() && !retVal; ++i)
    {
        SgAttribute *attribute = st->getAttribute(i);
        SgStatement *attributeStatement = (SgStatement *)(attribute->getAttributeData());
        int type = st->attributeType(i);

        if (type == SPF_ANALYSIS_DIR)
        {
            set<string> privates;
            fillPrivatesFromComment(attributeStatement, privates);

            retVal = retVal || privates.find(symbol->identifier()) != privates.end();
        }
    }

    return retVal;
}

static bool hasForName(SgExpression *exp, const string &forName)
{
    if (exp)
    {
        SgSymbol *symb = exp->symbol();
        SgExpression *lhs = exp->lhs();
        SgExpression *rhs = exp->rhs();

        if (symb)
            if (string(symb->identifier()) == forName)
                return true;

        return hasForName(lhs, forName) || hasForName(rhs, forName);
    }

    return false;
}

static int hasTextualInclude(SgExpression *exp, const string &varName)
{
    string stringExp = exp->unparse();
    int count = 0;
    auto pos = stringExp.find(varName, 0);

    while (pos != string::npos)
    {
        ++count;
        pos = stringExp.find(varName, pos + 1);
        //__spf_print(1, "I AM ('%s') number %d FOUND!\n", varName.c_str(), count);
    }

    return count;
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

        while (iterator != end)
        {
            fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varDef);
            fillVars(iterator->expr(1), { ARRAY_REF, VAR_REF }, varUse);
            fillVars(iterator->expr(2), { ARRAY_REF, VAR_REF }, varUse);
            iterator = iterator->lexNext();
        }

        for (auto &privElem : privates)
        {
            bool defCond = true;
            bool useCond = true;

            if (varDef.find(privElem) == varDef.end())
                defCond = false;
            if (varUse.find(privElem) == varUse.end())
                useCond = false;

            if (var == FOR_NODE && !defCond && !useCond)
            {
                __spf_print(1, "variable '%s' is not used in loop on line %d\n", privElem->identifier(), attributeStatement->lineNumber());
                string message;
                __spf_printToBuf(message, "variable '%s' is not used in loop", privElem->identifier());
                messagesForFile.push_back(Messages(WARR, attributeStatement->lineNumber(), message));
            }
            if (var == FOR_NODE && !defCond && useCond)
            {
                __spf_print(1, "variable '%s' is not changed in loop on line %d\n", privElem->identifier(), attributeStatement->lineNumber());
                string message;
                __spf_printToBuf(message, "variable '%s' is not changed in loop", privElem->identifier());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                retVal = false;
            }
        }
    }
    else
    {
        __spf_print(1, "bad directive position on line %d, it can be placed only before variable declaration or DO statement\n", 
                  attributeStatement->lineNumber());
        string message;
        __spf_printToBuf(message, "bad directive position, it can be placed only before variable declaration or DO statement");
        messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
        retVal = false;
    }

    return retVal;
}

static bool checkReduction(SgStatement *st,
                           SgStatement *attributeStatement,
                           const map<string, set<SgSymbol*>> &reduction,
                           vector<Messages> &messagesForFile)
{
    // REDUCTION(OP(VAR), MIN/MAXLOC(VAR, ARRAY, CONST))
    const int var = st->variant();
    bool retVal = true;

    if (var == FOR_NODE)
    {
        SgStatement *iterator = st->lexNext();
        SgStatement *end = st->lastNodeOfStmt();
        set<SgSymbol*> varDef;
        set<SgSymbol*> varUse;

        while (iterator != end)
        {
            fillVars(iterator->expr(0), { ARRAY_REF, VAR_REF }, varDef);
            fillVars(iterator->expr(1), { ARRAY_REF, VAR_REF }, varUse);
            fillVars(iterator->expr(2), { ARRAY_REF, VAR_REF }, varUse);
            iterator = iterator->lexNext();
        }

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
                    messagesForFile.push_back(Messages(WARR, attributeStatement->lineNumber(), message));
                }
                if (var == FOR_NODE && !defCond && useCond)
                {
                    __spf_print(1, "variable '%s' is not changed in loop on line %d\n", setElem->identifier(), attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "variable '%s' is not changed in loop", setElem->identifier());
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                    retVal = false;
                }
            }
        }
    }
    else
    {
        __spf_print(1, "bad directive position on line %d, it can be placed only before DO statement\n", attributeStatement->lineNumber());
        string message;
        __spf_printToBuf(message, "bad directive position, it can be placed only before DO statement");
        messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
        retVal = false;
    }

    return retVal;
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
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                retVal = false;
            }

            //__spf_print(1, "isPriv(decl, %s) = %d\n", arraySymbol->identifier(), varIsPrivate(declStatement, arraySymbol));
            notPrivCond = !isPrivateVar(st, arraySymbol) && !isPrivateVar(declStatement, arraySymbol);

            if (!notPrivCond)
            {
                __spf_print(1, "array '%s' on line %d is private\n", arraySymbol->identifier(), attributeStatement->lineNumber());
                string message;
                __spf_printToBuf(message, "array '%s' is private", arraySymbol->identifier());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
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
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                    retVal = false;
                }
            }
            else
            {
                __spf_print(1, "'%s' is not array on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());
                string message;
                __spf_printToBuf(message, "'%s' is not array", arraySymbol->identifier());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                retVal = false;
            }

            for (auto &array : arrayDisc)
            {
                if (array.first < 0 || array.second < 0)
                {
                    __spf_print(1, "only positive numbers are supported on line %d\n", attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "only positive numbers are supported");
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                    retVal = false;
                }
            }
        }
    }
    else
    {
        __spf_print(1, "bad directive position on line %d, it can be placed only before DO statement\n", attributeStatement->lineNumber());
        string message;
        __spf_printToBuf(message, "bad directive position, it can be placed only before DO statement");
        messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
        retVal = false;
    }

    return retVal;
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

            fillVars(remElem.second, { ARRAY_REF }, arraySymbols);
            for (auto &arraySymbol : arraySymbols)
            {
                declStatement = declaratedInStmt(arraySymbol);
                bool notPrivCond = !isPrivateVar(st, arraySymbol) && !isPrivateVar(declStatement, arraySymbol);

                if (!notPrivCond)
                {
                    __spf_print(1, "array '%s' is private on line %d\n", arraySymbol->identifier(), attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "array '%s' is private", arraySymbol->identifier());
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
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
                        if (hasTextualInclude(remoteExp->lhs(), forVar.first))
                        {
                            ++forVarsCount;
                            ++forVar.second;

                            if (retVal && forVarsCount > 1 || forVar.second > 1)
                            {
                                __spf_print(1, "bad directive expression: too many for variables on line %d\n", attributeStatement->lineNumber());
                                string message;
                                __spf_printToBuf(message, "bad directive expression: too many for variables");
                                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                                retVal = false;
                            }

                            // CHECK TREE: i OR a * i OR a * i + b
                            SgExpression *list = remoteExp->lhs();
                            bool isRemoteSubTreeCond = false;

                            if (list->variant() == ADD_OP)
                            {
                                if (list->lhs()->variant() == MULT_OP && !hasTextualInclude(list->rhs(), forVar.first))
                                {
                                    if (hasTextualInclude(list->lhs(), forVar.first) == 1)
                                        isRemoteSubTreeCond = true;
                                }
                                else if (list->rhs()->variant() == MULT_OP && !hasTextualInclude(list->lhs(), forVar.first))
                                {
                                    if (hasTextualInclude(list->rhs(), forVar.first) == 1)
                                        isRemoteSubTreeCond = true;
                                }
                                else if (hasTextualInclude(list, forVar.first) == 1)
                                    isRemoteSubTreeCond = true;
                            }
                            else if (list->variant() == MULT_OP)
                            {
                                if (!hasTextualInclude(list->lhs(), forVar.first) && hasTextualInclude(list->rhs(), forVar.first) == 1 ||
                                    !hasTextualInclude(list->rhs(), forVar.first) && hasTextualInclude(list->lhs(), forVar.first) == 1)
                                    isRemoteSubTreeCond = true;
                            }
                            else if (hasTextualInclude(list, forVar.first) == 1)
                                isRemoteSubTreeCond = true;

                            if (!isRemoteSubTreeCond)
                            {
                                __spf_print(1, "bad directive expression: only a * i + b on line %d\n", attributeStatement->lineNumber());
                                string message;
                                __spf_printToBuf(message, "bad directive expression: only a * i + b");
                                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                                retVal = false;
                            }
                        }
                    }

                    remoteExp = remoteExp->rhs();
                }
            }

            //SgStatement *iterator = var == FOR_NODE ? st->lexNext() : st;
            SgStatement *iterator = st;
            SgStatement *end = var == FOR_NODE ? st->lastNodeOfStmt() : st->lexNext();

            while (iterator != end)
            {
                //print(1, "%s\n", iterator->unparse());
                map<SgExpression*, string> collection;
                for (int i = 0; i < 3; ++i)
                {
                    if (iterator->expr(i))
                    {
                        //recExpressionPrint(iterator->expr(i));
                        //recExpressionPrint(remElem.second);
                        //__spf_print(1, "%s\n\n", iterator->expr(i)->unparse());
                    }
                    if (hasRemoteExpressions(iterator->expr(i), remElem.second, collection))
                        cond = true;
                }

                iterator = iterator->lexNext();
            }

            if (!cond)
            {
                __spf_print(1, "no such expression '%s' on line %d\n", remElem.second->unparse(), attributeStatement->lineNumber());
                string message;
                __spf_printToBuf(message, "no such expression '%s' on loop", remElem.second->unparse());
                messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                retVal = false;
            }
        }
    }
    else
    {
        __spf_print(1, "bad directive position on line %d, it can be placed only before DO statement\n", attributeStatement->lineNumber());
        string message;
        __spf_printToBuf(message, "bad directive position, it can be placed only before DO statement");
        messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
        retVal = false;
    }

    return retVal;
}

static bool checkParallelregions(SgStatement *st,
                                 SgStatement *attributeStatement,
                                 vector<Messages> &messagesForFile)
{
    bool retVal = true;

    // TODO

    return retVal;
}

static inline bool processStat(SgStatement *st, const string &currFile, vector<Messages> &messagesForFile)
{
    bool retVal = true;
    // ignore SPF statements
    if (isSPF_comment(st))
        return retVal;

    bool cond = false;
    SgStatement *iterator = st;
    do
    {
        SgStatement *prev = iterator->lexPrev();
        const int prevVar = prev->variant();
        cond = (isSPF_comment(prev) && prevVar != SPF_END_PARALLEL_REG_DIR);
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
            fillReductionsFromComment(attributeStatement, reduction);
            if (reduction.size())
            {
                bool result = checkReduction(st, attributeStatement, reduction, messagesForFile);
                retVal = retVal && result;
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
                //__spf_print(1, "DIRECTIVE NOINLINE\n");
                SgStatement *prev = st->lexPrev();
                const int prevVar = prev->variant();
                if (prevVar != PROC_HEDR && prevVar != FUNC_HEDR)
                {
                    __spf_print(1, "bad directive position on line %d, it can be placed only after function statement\n", attributeStatement->lineNumber());
                    string message;
                    __spf_printToBuf(message, "bad directive position, it can be placed only after function statement");
                    messagesForFile.push_back(Messages(ERROR, attributeStatement->lineNumber(), message));
                    retVal = false;
                }
            }
        }
        else if (type == SPF_PARALLEL_REG_DIR)
        {
            bool result = checkParallelregions(st, attributeStatement, messagesForFile);
            retVal = retVal && result;
        }
    }

    return retVal;
}

static bool processModules(vector<SgStatement*> &modules, const string &currFile, vector<Messages> &messagesForFile)
{
    bool retVal = true;
    for (int i = 0; i < modules.size(); ++i)
    {
        SgStatement *modIterator = modules[i];
        SgStatement *modEnd = modules[i]->lastNodeOfStmt();
        while (modIterator != modEnd)
        {
            bool result = processStat(modIterator, currFile, messagesForFile);
            retVal = retVal && result;
            modIterator = modIterator->lexNext();
        }
    }

    return retVal;
}

void preprocess_spf_dirs(SgFile *file, vector<Messages> &messagesForFile)
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

            bool result = processStat(st, currFile, messagesForFile);
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
    bool result = processModules(modules, currFile, messagesForFile);
    noError = noError && result;

    //TODO: add error return for visualizer
}

void addAcrossToLoops(LoopGraph *topLoop,
                      const map<SgSymbol*, tuple<int, int, int>> &acrossToAdd,
                      const map<int, pair<SgForStmt*, set<string>>> &allLoops,
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
            currMessages.push_back(Messages(NOTE, topLoop->lineNum, message));

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
        it->second.first->addAttribute(SPF_PARALLEL_DIR, acrSpf, sizeof(SgStatement));
    }
}

void addPrivatesToLoops(LoopGraph *topLoop, 
                        const vector<const depNode*> &privatesToAdd,
                        const map<int, pair<SgForStmt*, set<string>>> &allLoops,
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
            for (int z = 0; z < itLoop->second.first->numberOfAttributes(); ++z)
            {
                SgAttribute *attr = itLoop->second.first->getAttribute(z);
                int type = itLoop->second.first->attributeType(z);

                if (type == SPF_ANALYSIS_DIR)
                    fillPrivatesFromComment((SgStatement *)(attr->getAttributeData()), added);
            }

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
                currMessages.push_back(Messages(NOTE, addForCurrLoop[k]->stmtin->lineNumber(), message));

                if (k != addForCurrLoop.size() - 1)
                {
                    SgExpression *tmp = new SgExpression(EXPR_LIST);
                    exprList->setRhs(tmp);
                    exprList = exprList->rhs();
                }
            }

            if (uniq > 0)
                itLoop->second.first->addAttribute(SPF_ANALYSIS_DIR, privSpf, sizeof(SgStatement));
        }
    }
}

void addReductionsToLoops(LoopGraph *topLoop,
                          const vector<const depNode*> &reductionsToAdd,
                          const map<int, pair<SgForStmt*, set<string>>> &allLoops,
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
                char *oper = NULL;
                switch (addForCurrLoop[k]->kinddep)
                {
                case SADDREDUCTION:
                case DADDREDUCTION:
                case IADDREDUCTION:
                    {
                        SgExpression *tmp3 = new SgKeywordValExp("SUM");
                        SgExpression *tmp4 = new SgExpression(EXPR_LIST, tmp3, addForCurrLoop[k]->varin, NULL);
                        exprList->setLhs(tmp4);
                        oper = "SUM";
                        wasAdd = true;
                    }
                    break;
                case SMULREDUCTION:
                case DMULREDUCTION:
                case IMULREDUCTION:
                    {
                        SgExpression *tmp3 = new SgKeywordValExp("PRODUCT");
                        SgExpression *tmp4 = new SgExpression(EXPR_LIST, tmp3, addForCurrLoop[k]->varin, NULL);
                        exprList->setLhs(tmp4);
                        oper = "PRODUCT";
                        wasAdd = true;
                    }
                    break;
                case SDIVREDUCTION:
                case DDIVREDUCTION:
                case IDIVREDUCTION:
                    break;
                case SMAXREDUCTION:
                case DMAXREDUCTION:
                case IMAXREDUCTION:
                    {
                        SgExpression *tmp3 = new SgKeywordValExp("MAX");
                        SgExpression *tmp4 = new SgExpression(EXPR_LIST, tmp3, addForCurrLoop[k]->varin, NULL);
                        exprList->setLhs(tmp4);
                        oper = "MAX";
                        wasAdd = true;
                    }
                    break;
                case SMINREDUCTION:
                case DMINREDUCTION:
                case IMINREDUCTION:
                    {
                        SgExpression *tmp3 = new SgKeywordValExp("MIN");
                        SgExpression *tmp4 = new SgExpression(EXPR_LIST, tmp3, addForCurrLoop[k]->varin, NULL);
                        exprList->setLhs(tmp4);
                        oper = "MIN";
                        wasAdd = true;
                    }
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
                    currMessages.push_back(Messages(NOTE, addForCurrLoop[k]->stmtin->lineNumber(), message));
                }
                else
                {
                    if (consoleMode)
                        printf("  unknown type of reduction scalar '%s' on line %d\n", addForCurrLoop[k]->varin->symbol()->identifier(), addForCurrLoop[k]->stmtin->lineNumber());

                    string message;
                    __spf_printToBuf(message, "unknown type of reduction scalar '%s'", addForCurrLoop[k]->varin->symbol()->identifier());
                    currMessages.push_back(Messages(WARR, addForCurrLoop[k]->stmtin->lineNumber(), message));

                    topLoop->hasUnknownScalarDep = true;
                    topLoop->linesOfScalarDep.push_back(addForCurrLoop[k]->stmtin->lineNumber());
                }
            }

            auto it = allLoops.find(topLoop->lineNum);
            if (it == allLoops.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            it->second.first->addAttribute(SPF_ANALYSIS_DIR, redSpf, sizeof(SgStatement));
        }
    }
}