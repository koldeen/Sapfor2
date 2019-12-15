#include "../Utils/leak_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <string>
#include <algorithm>

#include "../Utils/types.h"
#include "DvmhDirective.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "../Sapfor.h"
#include "../GraphCall/graph_calls_func.h"

#include "dvm.h"

using std::vector;
using std::tuple;
using std::get;
using std::string;
using std::pair;
using std::set;
using std::map;

using std::set_union;
using std::make_pair;
using std::min;
using std::max;

static bool findArrayRefAndCheck(SgExpression *ex, const string &arrayName, const vector<map<pair<int, int>, int>> &shiftsByAccess, const int line)
{
    bool res = false;
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            if (ex->symbol() && OriginalSymbol(ex->symbol())->identifier() == arrayName)
            {
                SgSymbol *symb = OriginalSymbol(ex->symbol());
                SgStatement *decl = declaratedInStmt(symb);
                const DIST::Array *currArray = getArrayFromDeclarated(decl, arrayName);

                SgArrayRefExp *ref = (SgArrayRefExp*)ex;

                int countOfShadows = 0;
                for (int i = 0; i < ref->numberOfSubscripts(); ++i)
                {
                    const vector<int*> &coefs = getAttributes<SgExpression*, int*>(ref->subscript(i), set<int>{ INT_VAL });
                    if (coefs.size() == 1)
                    {
                        const pair<int, int> coef(coefs[0][0], coefs[0][1]);
                        auto it = shiftsByAccess[i].find(coef);
                        if (it != shiftsByAccess[i].end())
                            if (it->second != 0)
                                countOfShadows++;
                    }
                    else if (coefs.size() == 0)
                    {
                        if (!currArray->IsDimDepracated(i))
                        {
                            __spf_print(1, "error in ARRAY_REF coeffs: %s at line %d at %d subscript\n", arrayName.c_str(), line, i);
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                    }
                }

                if (countOfShadows > 1)
                    return true;
            }
        }

        if (ex->lhs())
        {
            bool tmp = findArrayRefAndCheck(ex->lhs(), arrayName, shiftsByAccess, line);
            res = res || tmp;
        }

        if (ex->rhs())
        {
            bool tmp = findArrayRefAndCheck(ex->rhs(), arrayName, shiftsByAccess, line);
            res = res || tmp;
        }
    }
    return res;
}

static bool needCorner(const string &arrayName, const vector<map<pair<int, int>, int>> &shiftsByAccess, Statement *loop)
{
    bool need = false;

    SgStatement *orig = loop->GetOriginal();
    
    for (auto st = orig; st != orig->lastNodeOfStmt() && !need; st = st->lexNext())
    {
        if (st->variant() == ASSIGN_STAT)
            need = findArrayRefAndCheck(st->expr(1), arrayName, shiftsByAccess, st->lineNumber());        
        else
        {
            for (int i = 0; i < 3; ++i)
                need = need || findArrayRefAndCheck(st->expr(i), arrayName, shiftsByAccess, st->lineNumber());
        }
    }
    return need;
}


vector<SgExpression*> genSubscripts(const vector<pair<int, int>> &shadowRenew, const vector<pair<int, int>> &shadowRenewShifts)
{
    vector<SgExpression*> subs;
    for (int z = 0; z < shadowRenew.size(); ++z)
    {
        SgValueExp *tmp = new SgValueExp(shadowRenew[z].first + shadowRenewShifts[z].first);
        SgValueExp *tmp1 = new SgValueExp(shadowRenew[z].second + shadowRenewShifts[z].second);
        subs.push_back(new SgExpression(DDOT, tmp, tmp1, NULL));
    }
    return subs;
}

SgExpression* createAndSetNext(const int side, const int variant, SgExpression *p)
{
    if (side == LEFT)
    {
        SgExpression *tmp = new SgExpression(variant);
        p->setLhs(tmp);
        return p->lhs();
    }
    else if (side == RIGHT)
    {
        SgExpression *tmp = new SgExpression(variant);
        p->setRhs(tmp);
        return p->rhs();
    }

    return NULL;
}

static SgExpression* genComplexExpr(const pair<string, string> &digitConv, const int digit)
{
    SgExpression *tmp;
    if (digitConv.first == " - ")
        tmp = new SgUnaryExp(MINUS_OP, *new SgValueExp(-digit));
    else
        tmp = new SgValueExp(digit);
    return tmp;
}

static SgExpression* genSgExpr(SgFile *file, const string &letter, const pair<int, int> expr)
{
    SgExpression *retVal;
    SgSymbol *symbLetter = findSymbolOrCreate(file, letter);
    if (expr.first == 0 && expr.second == 0)
        retVal = new SgVarRefExp(findSymbolOrCreate(file, "*"));
    else if (expr.second == 0)
    {
        if (expr.first == 1)
            retVal = new SgVarRefExp(symbLetter);
        else
        {
            pair<string, string> digit2 = convertDigitToPositive(expr.first);

            SgVarRefExp *tmp = new SgVarRefExp(symbLetter);
            retVal = new SgExpression(MULT_OP, genComplexExpr(digit2, expr.first), tmp, NULL);
        }
    }
    else
    {
        pair<string, string> digit1 = convertDigitToPositive(expr.second);
        SgExpression *d1 = genComplexExpr(digit1, expr.second);
        if (expr.first == 1)
        {
            SgVarRefExp *tmp = new SgVarRefExp(symbLetter);
            retVal = new SgExpression(ADD_OP, tmp, d1, NULL);
        }
        else
        {
            pair<string, string> digit2 = convertDigitToPositive(expr.first);
            SgExpression *d2 = genComplexExpr(digit2, expr.first);

            SgVarRefExp *tmp = new SgVarRefExp(symbLetter);
            SgExpression *tmp1 = new SgExpression(MULT_OP, d2, tmp, NULL);
            retVal = new SgExpression(ADD_OP, tmp1, d1, NULL);
        }
    }
    return retVal;
}

static map<string, Symbol*> setToMapWithSortByStr(const set<Symbol*> &setIn)
{
    map<string, Symbol*> retMap;
    for (auto& elem : setIn)
        retMap[elem->identifier()] = elem;
    return retMap;
}

static void fillUsedSymbols(SgExpression* ex, set<SgSymbol*> &used)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF || ex->variant() == VAR_REF)
            used.insert(ex->symbol());
        fillUsedSymbols(ex->lhs(), used);
        fillUsedSymbols(ex->rhs(), used);
    }
}
static set<string> fillUsedSymbols(SgStatement *loop)
{
    set<SgSymbol*> used;
    SgStatement* last = loop->lastNodeOfStmt();
    for (SgStatement* st = loop->lexNext(); st != last; st = st->lexNext())
        for (int z = 0; z < 3; ++z)
            if (st->expr(z))
                fillUsedSymbols(st->expr(z), used);

    set<string> usedS;
    for (auto& elem : used)
        usedS.insert(elem->identifier());
    return usedS;
}

static SgStatement* getRealStat(Statement *loop, const char *file, const int line, const int altLine)
{
    SgStatement* local = SgStatement::getStatementByFileAndLine(file, line);
    if (local == NULL)
        local = SgStatement::getStatementByFileAndLine(file, altLine);
    checkNull(local, convertFileName(__FILE__).c_str(), __LINE__);
    return local;
}

static string correctSymbolModuleName(const string& origFull)
{
    auto it = origFull.find("::");
    if (it == string::npos)
        return origFull;
    else
        return origFull.substr(it + 2);
}

static SgStatement* getModuleScope(const string& origFull, vector<SgStatement*>& moduleList, SgStatement *local)
{
    auto it = origFull.find("::");
    if (it == string::npos)
        return local;

    string modName = origFull.substr(0, it);
    for (auto& elem : moduleList)
        if (elem->symbol()->identifier() == modName)
            return elem;

    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return local;
}

extern int mpiProgram;

pair<string, vector<Expression*>> 
ParallelDirective::genDirective(File *file, const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                                const vector<AlignRule> &alignRules,
                                DIST::GraphCSR<int, double, attrType> &reducedG,
                                DIST::Arrays<int> &allArrays,
                                const std::set<DIST::Array*> &acrossOutAttribute,
                                const map<DIST::Array*, pair<vector<ArrayOp>, vector<bool>>> &readOps, 
                                Statement *loop, const int line, const int altLine, const int regionId,
                                const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    string directive = "";
    vector<Expression*> dirStatement = { NULL, NULL, NULL };
        
    SgForStmt *loopG = (SgForStmt *)loop->GetOriginal();
    const set<string> usedInLoop = fillUsedSymbols(loopG);

    vector<SgStatement*> moduleList;
    findModulesInFile(file, moduleList);

    SgStatement* parentFunc = getFuncStat(getRealStat(loop, file->filename(), line, altLine));
    map<string, set<SgSymbol*>> byUseInFunc = moduleRefsByUseInFunction(getRealStat(loop, file->filename(), line, altLine));
    const int nested = loopG->isPerfectLoopNest();
    vector<SgSymbol*> loopSymbs;
    for (int z = 0; z < nested; ++z)
    {
        loopSymbs.push_back(loopG->symbol());
        auto next = loopG->lexNext();
        if (next->variant() != FOR_NODE && z + 1 < nested)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        loopG = (SgForStmt *)next;
    }

    if (langType == LANG_F)
    {
        SgExpression *expr = new SgExpression(EXPR_LIST);
        SgExpression *p = expr;

        directive += "!DVM$ PARALLEL(";
        for (int i = 0; i < (int)parallel.size(); ++i)
        {
            const string pS = (parallel[i] == "*") ? loopSymbs[i]->identifier() : parallel[i];
            if (i == 0)
                directive += pS;
            else
                directive += "," + pS;

            SgVarRefExp *tmp = NULL;
            if (parallel[i] == "*")
                tmp = new SgVarRefExp(loopSymbs[i]);
            else
                tmp = new SgVarRefExp(findSymbolOrCreate(file, parallel[i]));

            p->setLhs(tmp);
            if (i != (int)parallel.size() - 1)
                p = createAndSetNext(RIGHT, EXPR_LIST, p);
            else
                p->setRhs(NULL);
        }
        DIST::Array *mapTo = arrayRef2->IsLoopArray() ? arrayRef : arrayRef2;
        auto onTo = arrayRef2->IsLoopArray() ? on : on2;

        dirStatement[2] = new Expression(expr);
        if (mpiProgram)
            directive += ")";
        else
        {
            directive += ") ON " + mapTo->GetShortName() + "(";

            SgSymbol* symbForPar;
            if (arrayRef->IsTemplate())
            {
                if (mapTo->IsLoopArray())
                    symbForPar = getFromModule(byUseInFunc, findSymbolOrCreate(file, mapTo->GetShortName(), new SgArrayType(*SgTypeInt()), file->GetOriginal()->firstStatement()), usedInLoop);
                else
                    symbForPar = getFromModule(byUseInFunc, mapTo->GetDeclSymbol()->GetOriginal(), usedInLoop);
            }
            else
                symbForPar = getFromModule(byUseInFunc, arrayRef->GetDeclSymbol()->GetOriginal(), usedInLoop);

            SgArrayRefExp* arrayExpr = new SgArrayRefExp(*symbForPar);
            for (int i = 0; i < (int)onTo.size(); ++i)
            {
                const pair<int, int>& coeffs = onTo[i].second;
                assert((coeffs.first != 0 && onTo[i].first != "*") || onTo[i].first == "*");

                if (i != 0)
                    directive += ",";

                if (onTo[i].first == "*")
                {
                    directive += "*";
                    SgVarRefExp* varExpr = new SgVarRefExp(findSymbolOrCreate(file, "*"));
                    arrayExpr->addSubscript(*varExpr);
                }
                else
                {
                    directive += genStringExpr(onTo[i].first, coeffs);
                    arrayExpr->addSubscript(*genSgExpr(file, onTo[i].first, coeffs));
                }
            }
            directive += ")";
            dirStatement[0] = new Expression(arrayExpr);
        }

        expr = new SgExpression(EXPR_LIST);
        p = expr;

        dirStatement[1] = NULL;
        if (privates.size() != 0)
        {
            p = createAndSetNext(LEFT, ACC_PRIVATE_OP, p);

            directive += ", PRIVATE(";
            int k = 0;
            vector<SgExpression*> list;
            for (auto &privVar : setToMapWithSortByStr(privates))
            {
                directive += (k != 0) ? "," + privVar.first : privVar.first;
                list.push_back(new SgVarRefExp(getFromModule(byUseInFunc, privVar.second, usedInLoop)));
                ++k;
            }
            directive += ")";
            dirStatement[1] = new Expression(expr);

            p->setLhs(makeExprList(list));
        }

        set<DIST::Array*> arraysInAcross;
        if (across.size() != 0)
        {
            if (acrossShifts.size() == 0)
            {
                acrossShifts.resize(across.size());
                for (int i = 0; i < across.size(); ++i)
                    acrossShifts[i].resize(across[i].second.size());
            }

            //TODO: add "OUT" key for string representation
            string acrossAdd = ", ACROSS(";
            int inserted = 0;
            SgExpression *acr_out = new SgExpression(EXPR_LIST);
            SgExpression *p_out = acr_out;

            SgExpression *acr_in = new SgExpression(EXPR_LIST);
            SgExpression *p_in = acr_in;

            SgExpression *acr_op = NULL;
            int inCount = 0;
            int outCount = 0;
            for (int i1 = 0; i1 < (int)across.size(); ++i1)
            {
                vector<map<pair<int, int>, int>> shiftsByAccess;

                DIST::Array *currArray = allArrays.GetArrayByName(across[i1].first.second);
                if (currArray == NULL)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                bool isOut = acrossOutAttribute.find(currArray) != acrossOutAttribute.end();
                string bounds = genBounds(alignRules, across[i1], acrossShifts[i1], reducedG, allArrays, readOps, true, regionId, distribution, arraysInAcross, shiftsByAccess, arrayLinksByFuncCalls);
                if (bounds != "")
                {
                    if (inserted != 0)
                    {
                        acrossAdd += ",";
                        if (isOut)
                        {
                            if (outCount > 0)
                                p_out = createAndSetNext(RIGHT, EXPR_LIST, p_out);
                            outCount++;
                            p = p_out;
                        }
                        else
                        {
                            if (inCount > 0)
                                p_in = createAndSetNext(RIGHT, EXPR_LIST, p_in);
                            inCount++;
                            p = p_in;
                        }
                    }
                    else if (inserted == 0)
                    {
                        if (dirStatement[1] != NULL)
                            expr = createAndSetNext(RIGHT, EXPR_LIST, expr);
                        acr_op = createAndSetNext(LEFT, ACROSS_OP, expr);

                        if (isOut)
                        {
                            outCount++;
                            p = p_out;
                        }
                        else
                        {
                            inCount++;
                            p = p_in;
                        }
                    }

                    acrossAdd += across[i1].first.first + "(" + bounds + ")";

                    SgArrayRefExp *newArrayRef = new SgArrayRefExp(*getFromModule(byUseInFunc, currArray->GetDeclSymbol()->GetOriginal(), usedInLoop));
                    newArrayRef->addAttribute(ARRAY_REF, currArray, sizeof(DIST::Array));

                    for (auto &elem : genSubscripts(across[i1].second, acrossShifts[i1]))
                        newArrayRef->addSubscript(*elem);

                    p->setLhs(newArrayRef);
                    inserted++;
                }
            }
            acrossAdd += ")";

            if (inserted > 0)
            {
                directive += acrossAdd;

                if (dirStatement[1] == NULL)
                    dirStatement[1] = new Expression(expr);

                if (acrossOutAttribute.size() > 0)
                {
                    SgExpression *tmp = new SgExpression(DDOT, new SgKeywordValExp("OUT"), acr_out, NULL);
                    acr_op->setLhs(*tmp);
                    if (inCount != 0)
                        acr_op->setRhs(acr_in);
                }
                else
                    acr_op->setLhs(acr_in);
            }
        }

        if (shadowRenew.size() != 0 && mpiProgram == 0)
        {            
            if (shadowRenewShifts.size() == 0)
            {
                shadowRenewShifts.resize(shadowRenew.size());
                for (int i = 0; i < shadowRenew.size(); ++i)
                    shadowRenewShifts[i].resize(shadowRenew[i].second.size());
            }
                        
            string shadowAdd = ", SHADOW_RENEW(";
            int inserted = 0;
            for (int i1 = 0; i1 < (int)shadowRenew.size(); ++i1)
            {
                vector<map<pair<int, int>, int>> shiftsByAccess;
                const string bounds = genBounds(alignRules, shadowRenew[i1], shadowRenewShifts[i1], reducedG, allArrays, readOps, false, regionId, distribution, arraysInAcross, shiftsByAccess, arrayLinksByFuncCalls);
                if (bounds != "")
                {
                    DIST::Array *currArray = allArrays.GetArrayByName(shadowRenew[i1].first.second);

                    if (inserted != 0)
                    {
                        shadowAdd += ",";
                        p = createAndSetNext(RIGHT, EXPR_LIST, p);
                    }
                    else if (inserted == 0)
                    {
                        if (dirStatement[1] != NULL)
                        {
                            expr = createAndSetNext(RIGHT, EXPR_LIST, expr);
                            p = expr;
                        }

                        p = createAndSetNext(LEFT, SHADOW_RENEW_OP, p);
                        p = createAndSetNext(LEFT, EXPR_LIST, p);
                    }

                    shadowAdd += shadowRenew[i1].first.first + "(" + bounds + ")";
                    SgArrayRefExp *newArrayRef = new SgArrayRefExp(*getFromModule(byUseInFunc, currArray->GetDeclSymbol(), usedInLoop));
                    newArrayRef->addAttribute(ARRAY_REF, currArray, sizeof(DIST::Array));

                    for (auto &elem : genSubscripts(shadowRenew[i1].second, shadowRenewShifts[i1]))
                        newArrayRef->addSubscript(*elem);

                    if (shadowRenew[i1].second.size() > 1 && needCorner(currArray->GetShortName(), shiftsByAccess, loop))
                    {
                        SgExpression *tmp = new SgExpression(ARRAY_OP, newArrayRef, NULL, NULL);
                        p->setLhs(*tmp);

                        shadowAdd += "(CORNER)";
                        SgKeywordValExp *tmp1 = new SgKeywordValExp("CORNER");
                        p->lhs()->setRhs(tmp1);
                    }
                    else
                        p->setLhs(newArrayRef);

                    inserted++;
                }
            }
            shadowAdd += ")";
            if (inserted > 0)
            {
                directive += shadowAdd;
                if (dirStatement[1] == NULL)
                    dirStatement[1] = new Expression(expr);
            }
        }
        
        if (reduction.size() != 0)
        {
            if (dirStatement[1] != NULL)
            {
                expr = createAndSetNext(RIGHT, EXPR_LIST, expr);
                p = expr;
            }

            p = createAndSetNext(LEFT, REDUCTION_OP, p);
            p = createAndSetNext(LEFT, EXPR_LIST, p);

            directive += ", REDUCTION(";
            int k = 0;
            for (auto it = reduction.begin(); it != reduction.end(); ++it)
            {
                const string &nameGroup = it->first;
                for (auto &list : it->second)
                {
                    if (k != 0)
                    {
                        directive += ",";
                        p = createAndSetNext(RIGHT, EXPR_LIST, p);
                    }

                    SgSymbol* base = findSymbolOrCreate(file, correctSymbolModuleName(list), NULL, getModuleScope(list, moduleList, parentFunc));
                    SgSymbol* redS = getFromModule(byUseInFunc, base, usedInLoop, list.find("::") != string::npos);
                    directive += nameGroup + "(" + redS->identifier() + ")";

                    SgVarRefExp *tmp2 = new SgVarRefExp(redS);
                    SgFunctionCallExp *tmp1 = new SgFunctionCallExp(*findSymbolOrCreate(file, nameGroup), *tmp2);

                    p->setLhs(tmp1);
                    ++k;
                }
            }
            if (reductionLoc.size() != 0)
                directive += ", ";
            else
            {
                directive += ")";

                if (dirStatement[1] == NULL)
                    dirStatement[1] = new Expression(expr);
            }
        }
   
        if (reductionLoc.size() != 0)
        {
            if (dirStatement[1] != NULL && reduction.size() == 0)
            {
                expr = createAndSetNext(RIGHT, EXPR_LIST, expr);
                p = expr;
            }

            if (reduction.size() == 0)
            {
                p = createAndSetNext(LEFT, REDUCTION_OP, p);
                p = createAndSetNext(LEFT, EXPR_LIST, p);
                directive += ", REDUCTION(";
            }
            else
                p = createAndSetNext(RIGHT, EXPR_LIST, p);

            int k = 0;
            for (auto it = reductionLoc.begin(); it != reductionLoc.end(); ++it)
            {
                const string &nameGroup = it->first;
                for (auto &list : it->second)
                {
                    if (k != 0)
                    {
                        directive += ",";
                        p = createAndSetNext(RIGHT, EXPR_LIST, p);
                    }

                    SgSymbol* base1 = findSymbolOrCreate(file, correctSymbolModuleName(get<0>(list)), NULL, getModuleScope(get<0>(list), moduleList, parentFunc));
                    SgSymbol* base2 = findSymbolOrCreate(file, correctSymbolModuleName(get<1>(list)), NULL, getModuleScope(get<1>(list), moduleList, parentFunc));

                    SgSymbol* redS1 = getFromModule(byUseInFunc, base1, usedInLoop, get<0>(list).find("::") != string::npos);
                    SgSymbol* redS2 = getFromModule(byUseInFunc, base2, usedInLoop, get<1>(list).find("::") != string::npos);

                    directive += nameGroup + "(" + redS1->identifier() + ", " + redS2->identifier() + ", " + std::to_string(get<2>(list)) + ")";

                    SgFunctionCallExp *tmp1 = new SgFunctionCallExp(*findSymbolOrCreate(file, nameGroup));

                    tmp1->addArg(*new SgVarRefExp(redS1));
                    tmp1->addArg(*new SgVarRefExp(redS2));
                    tmp1->addArg(*new SgValueExp(get<2>(list)));

                    p->setLhs(tmp1);
                    ++k;
                }
            }
            directive += ")";

            if (dirStatement[1] == NULL)
                dirStatement[1] = new Expression(expr);
        }

        if (remoteAccess.size() != 0 && mpiProgram == 0)
        {
            if (dirStatement[1] != NULL)
            {
                expr = createAndSetNext(RIGHT, EXPR_LIST, expr);
                p = expr;
            }

            p = createAndSetNext(LEFT, REMOTE_ACCESS_OP, p);
            p = createAndSetNext(LEFT, EXPR_LIST, p);

            directive += ", REMOTE_ACCESS(";
            int k = 0;
            for (auto it = remoteAccess.begin(); it != remoteAccess.end(); ++it, ++k)
            {
                directive += it->first.first + "(";
                directive += it->first.second + ")";
                
                DIST::Array* currArray = allArrays.GetArrayByName(it->first.second);
                SgArrayRefExp *tmp = new SgArrayRefExp(*getFromModule(byUseInFunc, currArray->GetDeclSymbol()->GetOriginal(), usedInLoop), *it->second);
                
                tmp->addAttribute(ARRAY_REF, currArray, sizeof(DIST::Array));
                p->setLhs(tmp);

                if (k != remoteAccess.size() - 1)
                {
                    directive += ",";
                    p = createAndSetNext(RIGHT, EXPR_LIST, p);
                }
            }
            directive += ")";

            if (dirStatement[1] == NULL)
                dirStatement[1] = new Expression(expr);
        }
    }
    else
    {
        //TODO for C LANG
    }
    directive += "\n";
    return make_pair(directive, dirStatement);
}

void DistrVariant::GenRule(File *file, Expression *rule, const vector<int> &newOrder) const
{    
    for (int i = 0; i < distRule.size(); ++i)
    {
        SgVarRefExp *toSet = NULL;
        if (newOrder.size() == 0)
        {
            if (distRule[i] == dist::NONE)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "*"));
                rule->setLhs(toSet);
            }
            else if (distRule[i] == dist::BLOCK)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "BLOCK"));
                rule->setLhs(toSet);
            }
        }
        else
        {
            if (distRule[newOrder[i]] == dist::NONE)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "*"));
                rule->setLhs(toSet);
            }
            else if (distRule[newOrder[i]] == dist::BLOCK)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "BLOCK"));
                rule->setLhs(toSet);
            }
        }

        if (i != distRule.size() - 1)
        {
            SgExpression *list = new SgExpression(EXPR_LIST);
            rule->setRhs(list);
            rule = new Expression(rule->rhs());
        }        
    }       
}

vector<Expression*> DistrVariant::GenRuleSt(File *file, const vector<int> &newOrder) const
{
    vector<Expression*> retVal;
    
    for (int i = 0; i < distRule.size(); ++i)
    {
        SgVarRefExp *toSet = NULL;
        if (newOrder.size() == 0)
        {
            if (distRule[i] == dist::NONE)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "*"));
                retVal.push_back(new Expression(toSet));
            }
            else if (distRule[i] == dist::BLOCK)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "BLOCK"));
                retVal.push_back(new Expression(toSet));
            }
        }
        else
        {
            if (distRule[newOrder[i]] == dist::NONE)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "*"));
                retVal.push_back(new Expression(toSet));
            }
            else if (distRule[newOrder[i]] == dist::BLOCK)
            {
                toSet = new SgVarRefExp(findSymbolOrCreate(file, "BLOCK"));
                retVal.push_back(new Expression(toSet));
            }
        }
    }
    return retVal;
}

vector<Statement*> DataDirective::GenRule(File *file, const vector<int> &rules, const int variant) const
{
    vector<Statement*> retVal;
    if (distrRules.size() < rules.size())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    
    for (int i = 0; i < rules.size(); ++i)
    {
        if (rules[i] < distrRules[i].second.size())
        {
            string tmp = distrRules[i].first->GetShortName();
            SgStatement *dir = new SgStatement(variant, NULL, NULL, NULL, NULL, NULL);
            SgVarRefExp *dirstRef = new SgVarRefExp(*findSymbolOrCreate(file, tmp));
            SgExpression *rule = new SgExpression(EXPR_LIST);
            
            distrRules[i].second[rules[i]].GenRule(file, new Expression(rule), distrRules[i].first->GetNewTemplateDimsOrder());

            SgExpression *toAdd = new SgExpression(EXPR_LIST, dirstRef, NULL, NULL);
            dir->setExpression(0, *toAdd);
            dir->setExpression(1, *rule);
            retVal.push_back(new Statement(dir));
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    return retVal;
}

vector<Statement*> DataDirective::GenAlignsRules(File *file, const int variant) const
{
    vector<Statement*> retVal;
    for (int i = 0; i < alignRules.size(); ++i)
    {
        Statement *newRule = alignRules[i].GenRule(file, variant);
        if (newRule)
            retVal.push_back(newRule);
    }
    return retVal;
}

Statement* AlignRule::GenRule(File *file, const int variant) const
{
    // local and realign
    if (alignArray->GetLocation().first == 0 && variant == DVM_REALIGN_DIR)
        return NULL;

    SgStatement *retVal = new SgStatement(variant, NULL, NULL, NULL, NULL, NULL);

    SgVarRefExp *alignRef = new SgVarRefExp(findSymbolOrCreate(file, alignArray->GetShortName()));
    SgExpression *list = new SgExpression(EXPR_LIST, alignRef, NULL, NULL);
    retVal->setExpression(0, *list);

    SgExpression *alignList = new SgExpression(EXPR_LIST);
    retVal->setExpression(1, *alignList);
    for (int i = 0; i < alignRule.size(); ++i)
    {
        alignList->setLhs(genSgExpr(file, alignNames[i], alignRule[i]));        
        if (i != alignRule.size() - 1)
        {
            list = new SgExpression(EXPR_LIST);
            alignList->setRhs(list);
            alignList = alignList->rhs();
        }
    }

    SgSymbol *sAlignWith = &(findSymbolOrCreate(file, alignWith->GetShortName())->copy());
    SgArrayType *arrayType = new SgArrayType(*SgTypeInt());    
    sAlignWith->setType(arrayType);
    SgArrayRefExp *alignWithRef = new SgArrayRefExp(*sAlignWith);

    vector<SgExpression*> alignEachDim(alignWith->GetDimSize());
    for (int i = 0; i < alignWith->GetDimSize(); ++i)
        alignEachDim[i] = new SgVarRefExp(findSymbolOrCreate(file, "*"));    

    for (int i = 0; i < alignRuleWith.size(); ++i)
        if (alignRuleWith[i].first != -1)
            alignEachDim[alignRuleWith[i].first] = genSgExpr(file, alignNames[i], alignRuleWith[i].second);

    auto newOrder = alignWith->GetNewTemplateDimsOrder();
    if (newOrder.size() != 0)
    {
        vector<SgExpression*> alignEachDimNew(alignEachDim);
        for (int i = 0; i < newOrder.size(); ++i)
            alignEachDim[i] = alignEachDimNew[newOrder[i]];
    }

    for (int i = 0; i < alignWith->GetDimSize(); ++i)
        alignWithRef->addSubscript(*alignEachDim[i]);
    retVal->setExpression(2, *alignWithRef);

    return new Statement(retVal);
}

pair<SgExpression*, SgExpression*> genShadowSpec(SgFile *file, const pair<string, const vector<pair<int, int>>> &shadowSpecs)
{
    pair<SgExpression*, SgExpression*> result;

    SgVarRefExp *tmp = new SgVarRefExp(findSymbolOrCreate(file, shadowSpecs.first));
    result.first = new SgExpression(EXPR_LIST, tmp, NULL, NULL, NULL);

    SgExpression *listEx = new SgExpression(EXPR_LIST);
    result.second = listEx;
    bool needInsert = false;
    for (int k = 0; k < shadowSpecs.second.size(); ++k)
    {        
        const int leftVal = shadowSpecs.second[k].first;
        const int rightVal = shadowSpecs.second[k].second;

        SgValueExp *tmp1 = new SgValueExp(leftVal);
        SgValueExp *tmp2 = new SgValueExp(rightVal);
        SgExpression *currDim = new SgExpression(DDOT, tmp1, tmp2, NULL);

        listEx->setLhs(currDim);
        if (shadowSpecs.second[k].first != 0 || shadowSpecs.second[k].second != 0)
            needInsert = true;
        
        if (k != shadowSpecs.second.size() - 1)
        {
            SgExpression *tmp = new SgExpression(EXPR_LIST);
            listEx->setRhs(tmp);
            listEx = listEx->rhs();
        }
    }
    
    if (needInsert)
        return result;
    else
        return make_pair<SgExpression*, SgExpression*>(NULL, NULL);
}

//TODO: check this
void correctShadowSpec(SgExpression *listEx, const vector<pair<int, int>> &shadowSpecs)
{    
    for (int k = 0; k < shadowSpecs.size(); ++k)
    {
        const int leftVal = shadowSpecs[k].first;
        const int rightVal = shadowSpecs[k].second;
        
        if (listEx)
        {
            if (listEx->lhs())
            {
                if (listEx->lhs()->lhs())
                    if (listEx->lhs()->lhs()->valueInteger() < leftVal)
                        ((SgValueExp*)(listEx->lhs()->lhs()))->setValue(leftVal);

                if (listEx->lhs()->rhs())
                    if (listEx->lhs()->rhs()->valueInteger() < rightVal)
                        ((SgValueExp*)(listEx->lhs()->rhs()))->setValue(rightVal);
            }
        }
        else
            break;
        listEx = listEx->rhs();        
    }
}
