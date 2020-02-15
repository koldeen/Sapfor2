#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <assert.h>

#include "dvm.h"

#include "../ParallelizationRegions/ParRegions_func.h"

#include "../Distribution/GraphCSR.h"
#include "../Distribution/Arrays.h"
#include "../Distribution/Distribution.h"
#include "../Distribution/DvmhDirective_func.h"

#include "../Utils/errors.h"
#include "loop_analyzer.h"
#include "directive_parser.h"
#include "../Utils/SgUtils.h"
#include "../Sapfor.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../LoopConverter/loop_transform.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../GraphCall/graph_calls_func.h"

#include "../Utils/AstWrapper.h"

#define PRINT_DIR_RESULT 0

#define FIRST(x)  get<0>(x)
#define SECOND(x) get<1>(x)
#define THIRD(x)  get<2>(x)

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

static bool matchParallelAndDist(const pair<DIST::Array*, const DistrVariant*> &currDist, const ParallelDirective *currParDir, vector<bool> &saveDistr, const int regionId)
{
    DIST::Array *parallelOn = currParDir->arrayRef;
    const vector<pair<string, pair<int, int>>> &ruleOn = currParDir->on;
    DIST::Array *templArray = currDist.first;

    //return true if need to skeep
    if (parallelOn->IsTemplate())
    {
        if (parallelOn != templArray)
            return true;
    }
    else if (parallelOn->GetTemplateArray(regionId) != templArray)
        return true;

    vector<bool> touched(templArray->GetDimSize());
    std::fill(touched.begin(), touched.end(), false);
    saveDistr.resize(templArray->GetDimSize(), false);
    bool conflict = false;
    
    vector<int> linkWithTempl;
    if (parallelOn->IsTemplate())
        for (int i = 0; i < templArray->GetDimSize(); ++i)
            linkWithTempl.push_back(i);
    else
        linkWithTempl = parallelOn->GetLinksWithTemplate(regionId);

    for (int i = 0; i < parallelOn->GetDimSize(); ++i)
    {
        // link does not exist
        if (linkWithTempl[i] == -1)
            continue;
        touched[linkWithTempl[i]] = true;
        if (ruleOn[i].first != "*")
        {
            if (currDist.second->distRule[linkWithTempl[i]] == dist::BLOCK)
                saveDistr[linkWithTempl[i]] = true;
        }
        else
        {
            if (currDist.second->distRule[linkWithTempl[i]] == dist::BLOCK)
                conflict = true;
        }
    }

    for (int i = 0; i < touched.size(); ++i)
    {
        if (!touched[i])
        {
            if (currDist.second->distRule[i] == dist::BLOCK)
                conflict = true;
        }
    }
        
    if (conflict)
    {
        int countOfBlockToNone = 0;
        for (int z = 0; z < saveDistr.size(); ++z)
        {
            if (saveDistr[z] == false && currDist.second->distRule[z] == dist::BLOCK)
                countOfBlockToNone++;
        }

        vector<int> idxCandidates;
        for (int z = 0; z < currParDir->parallel.size(); ++z)
        {
            const string currLetter = currParDir->parallel[z];
            for (int k = 0; k < currParDir->on.size(); ++k)
            {
                if (currParDir->on[k].first == currLetter)
                {
                    if (currDist.second->distRule[linkWithTempl[k]] == dist::NONE)
                        idxCandidates.push_back(linkWithTempl[k]);                    
                    break;
                }
            }
        }

        if (idxCandidates.size())
            for (int k = 0; k < std::min(countOfBlockToNone, (int)idxCandidates.size()); ++k)
                saveDistr[idxCandidates[k]] = true;        
    }

    return !conflict;
}

static pair<vector<int>, vector<pair<string, vector<Expression*>>>>
    genRedistributeDirective(File *file, const vector<pair<DIST::Array*, const DistrVariant*>> distribution, 
                             const LoopGraph *current, const ParallelDirective *currParDir,
                             const int regionId, vector<pair<DIST::Array*, DistrVariant*>> &redistributeRules)
{
    vector<Expression*> dirStatement = { NULL, NULL, NULL, NULL };
    vector<pair<string, vector<Expression*>>> out;
    
    vector<int> selectedIdxOfDistr;
    //TODO: check matchParallelAndDist, need to create redistr for all templates at current scope !!
    for (int i = 0; i < distribution.size(); ++i)
    {
        vector<bool> saveDistr;
        bool result = matchParallelAndDist(distribution[i], currParDir, saveDistr, regionId);
        if (result)
            continue;
        selectedIdxOfDistr.push_back(i);

        vector<dist> newRedistributeRule;

        string directive = "!DVM$ REDISTRIBUTE ";
        directive += distribution[i].first->GetShortName() + "(";

        SgVarRefExp *ref = new SgVarRefExp(*findSymbolOrCreate(file, distribution[i].first->GetShortName()));
        SgExpression *ruleList = new SgExpression(EXPR_LIST);
        SgExpression *pointer = ruleList;
        for (int k = 0; k < saveDistr.size(); ++k)
        {
            if (saveDistr[k])
            {
                newRedistributeRule.push_back(BLOCK);
                directive += "BLOCK";
                SgVarRefExp *tmp = new SgVarRefExp(findSymbolOrCreate(file, "BLOCK"));
                ruleList->setLhs(tmp);
            }
            else
            {
                newRedistributeRule.push_back(NONE);
                directive += "*";
                SgVarRefExp *tmp = new SgVarRefExp(findSymbolOrCreate(file, "*"));
                ruleList->setLhs(tmp);
            }

            if (k != saveDistr.size() - 1)
            {
                directive += ",";
                SgExpression *tmp = new SgExpression(EXPR_LIST);
                ruleList->setRhs(tmp);
            }
            ruleList = ruleList->rhs();
        }
        directive += ")\n";
        dirStatement[0] = new Expression(new SgExpression(EXPR_LIST, ref, NULL, NULL));
        dirStatement[1] = new Expression(pointer);
        
        if (saveDistr.size() != 0)
        {
            out.push_back(make_pair(directive, dirStatement));

            DistrVariant *newRules = new DistrVariant(newRedistributeRule);
            redistributeRules.push_back(make_pair(distribution[i].first, newRules));
        }
    }

    return make_pair(selectedIdxOfDistr, out);
}

static bool ifRuleNull(const DistrVariant *currVar)
{
    for (auto &elem : currVar->distRule)
        if (elem == BLOCK)
            return false;
    return true;
}

static DIST::Array* getRealArrayRef(DIST::Array *in, const int regId, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    set<DIST::Array*> out;
    getRealArrayRefs(in, in, out, arrayLinksByFuncCalls);

    set<vector<pair<int, int>>> rules;
    set<vector<int>> links;
    set<DIST::Array*> templ;
    for (auto &array : out)
    {
        rules.insert(array->GetAlignRulesWithTemplate(regId));
        links.insert(array->GetLinksWithTemplate(regId));
        templ.insert(array->GetTemplateArray(regId));
    }

    if (templ.size() != 1 || links.size() != 1 || rules.size() != 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return *out.begin();
}

vector<pair<string, vector<Expression*>>> 
    groupRealignsDirs(const vector<pair<string, vector<Expression*>>>& toRealign)
{
    map<pair<string, string>, vector<vector<Expression*>>> groupedRules;
    for (auto& rule : toRealign)
    {
        auto currRule = rule.second;

        string tRule = string(currRule[2]->unparse());
        string arrRule = string(currRule[1]->unparse());
        groupedRules[make_pair(tRule, arrRule)].push_back(currRule);
    }

    map<pair<string, string>, vector<Expression*>> mergedGroupedRules;
    for (auto& rule : groupedRules)
    {
        SgExprListExp* mergedList = new SgExprListExp();
        for (int z = 0; z < rule.second.size(); ++z)
        {
            if (z == 0)
                mergedList->setLhs(rule.second[z][0]->GetOriginal());
            else
                mergedList->append(*rule.second[z][0]->GetOriginal());
        }
        vector<Expression*> medged = rule.second[0];
        medged[0] = new Expression(mergedList);
        mergedGroupedRules[rule.first] = medged;
    }

    vector<pair<string, vector<Expression*>>> retVal;
    for (auto& elem : mergedGroupedRules)
        retVal.push_back(make_pair("", elem.second));

    return retVal;
}

//create realigns instead of full template redistribution
vector<vector<pair<string, vector<Expression*>>>> 
    createRealignRules(SgStatement *spStat, const int regId, SgFile *file, const string &templClone, 
                       const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls, const set<DIST::Array*> &usedArrays)
{
    vector<vector<pair<string, vector<Expression*>>>> optimizedRules(2);
    auto byUse = moduleRefsByUseInFunction(spStat);

    for (int num = 0; num < 2; ++num)
    {
        for (auto &elem : usedArrays)
        {
            if (elem->GetNonDistributeFlag())
                continue;

            auto realRef = getRealArrayRef(elem, regId, arrayLinksByFuncCalls);
            auto rules = realRef->GetAlignRulesWithTemplate(regId);
            auto links = realRef->GetLinksWithTemplate(regId);
            const auto &templ = realRef->GetTemplateArray(regId);
            if (templ == NULL)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            
            vector<Expression*> realign = { NULL, NULL, NULL, NULL, NULL };
            set<string> tmpUsed;
            SgVarRefExp *ref = new SgVarRefExp(getFromModule(byUse, findSymbolOrCreate(file, elem->GetShortName()), tmpUsed));

            realign[0] = new Expression(ref);
            SgExprListExp *list = new SgExprListExp();
            string base = "iEX";
            for (int z = 0; z < elem->GetDimSize(); ++z)
            {
                if (z == 0)
                    list->setLhs(*new SgVarRefExp(findSymbolOrCreate(file, base + std::to_string(z))));
                else
                    list->append(*new SgVarRefExp(findSymbolOrCreate(file, base + std::to_string(z))));
            }

            realign[1] = new Expression(list);
            if (num == 0)
                realign[2] = new Expression(new SgArrayRefExp(*findSymbolOrCreate(file, templClone, new SgArrayType(*SgTypeInt()))));
            else
                realign[2] = new Expression(new SgArrayRefExp(*findSymbolOrCreate(file, templ->GetShortName(), new SgArrayType(*SgTypeInt()))));

            vector<SgExpression*> templateRuleEx(templ->GetDimSize());
            std::fill(templateRuleEx.begin(), templateRuleEx.end(), (SgExpression*)NULL);
            for (int z = 0; z < elem->GetDimSize(); ++z)
            {
                if (links[z] != -1)
                {
                    SgExpression *toSet = NULL;
                    auto symb = new SgVarRefExp(*findSymbolOrCreate(file, base + std::to_string(z)));
                    if (rules[z] == make_pair(1, 0))
                        toSet = symb;
                    else if (rules[z].second == 0)
                        toSet = &(*new SgValueExp(rules[z].first) * *symb);
                    else if (rules[z].first == 1)
                        toSet = &(*symb + *new SgValueExp(rules[z].second));
                    else
                        toSet = &(*new SgValueExp(rules[z].first) * *symb + *new SgValueExp(rules[z].second));
                    templateRuleEx[links[z]] = toSet;
                }
            }

            for (int z = 0; z < templateRuleEx.size(); ++z)
            {
                SgExpression *toSet = NULL;
                if (templateRuleEx[z] == NULL)
                    toSet = new SgVarRefExp(*findSymbolOrCreate(file, "*"));
                else
                    toSet = templateRuleEx[z];
                ((SgArrayRefExp*)realign[2]->GetOriginal())->addSubscript(*toSet);

            }

            optimizedRules[num].push_back(make_pair("", realign));
        }
    }

    vector<vector<pair<string, vector<Expression*>>>> groupedOptRules(2);
    groupedOptRules[0] = groupRealignsDirs(optimizedRules[0]);
    groupedOptRules[1] = groupRealignsDirs(optimizedRules[1]);
    return groupedOptRules;
}

extern int mpiProgram;
bool addRedistributionDirs(File *file, const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                           vector<pair<int, pair<string, vector<Expression*>>>> &toInsert,
                           LoopGraph *current, const map<int, LoopGraph*> &loopGraph, 
                           ParallelDirective *currParDir, const int regionId, vector<Messages> &messages,
                           const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    vector<pair<DIST::Array*, DistrVariant*>> redistributeRules;
    const pair<vector<int>, vector<pair<string, vector<Expression*>>>> &redistrDirs = genRedistributeDirective(file, distribution, current, currParDir, regionId, redistributeRules);
    
    bool needToSkip = true;

    for (int z = 0; z < redistrDirs.first.size(); ++z)
    {
        if (ifRuleNull(redistributeRules[z].second))
        {
            LoopGraph* cp = current->parent;
            int nestedLvl = 1;
            while (cp)
            {
                const int line = cp->lineNum;

                auto itL = loopGraph.find(line);
                if (itL == loopGraph.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                if (itL->second->directiveForLoop != NULL || itL->second->directive != NULL)
                    return needToSkip;
                nestedLvl = itL->second->perfectLoop;
                if (nestedLvl > 1)
                    return needToSkip;
                cp = cp->parent;
            }
        }
    }

    needToSkip = false;
    if (mpiProgram)
        return false;

    for (int z = 0; z < redistrDirs.first.size(); ++z)
    {
        const int idx = redistrDirs.first[z];
        string redist = "!DVM$ REDISTRIBUTE " + distribution[idx].first->GetShortName();
        redist += distribution[idx].second->GenRuleBase(distribution[idx].first->GetNewTemplateDimsOrder()) + "\n";

        vector<Expression*> redistSt = { NULL, NULL, NULL, NULL };

        SgVarRefExp *ref = new SgVarRefExp(*findSymbolOrCreate(file, distribution[idx].first->GetShortName()));
        vector<Expression*> subs = distribution[idx].second->GenRuleSt(new File(file), distribution[idx].first->GetNewTemplateDimsOrder());

        SgExpression *ruleList = new SgExpression(EXPR_LIST);
        SgExpression *pointer = ruleList;
        for (int i = 0; i < subs.size(); ++i)
        {
            ruleList->setLhs(subs[i]);
            if (i != subs.size() - 1)
            {
                SgExpression *tmp = new SgExpression(EXPR_LIST);
                ruleList->setRhs(tmp);
            }
            else
                ruleList->setRhs(NULL);
            ruleList = ruleList->rhs();
        }
        redistSt[0] = new Expression(new SgExpression(EXPR_LIST, ref, NULL, NULL));
        redistSt[1] = new Expression(pointer);
        //OLD var - full redistribution
        /*toInsert.push_back(make_pair(current->lineNum, redistrDirs.second[z]));
        toInsert.push_back(make_pair(current->lineNumAfterLoop, make_pair(redist, redistSt)));
        __spf_print(1, "WARN: added redistribute for loop on line %d by array '%s' can significantly reduce performance\n", current->lineNum, distribution[idx].first->GetShortName().c_str());

        char buf[512];
        sprintf(buf, "Added redistribute for loop by array '%s' can significantly reduce performance", distribution[idx].first->GetShortName().c_str());
        messages.push_back(Messages(WARR, current->lineNum, buf, 3009));*/

        // New var - realign with global template clones        
        const auto redistrRule = redistributeRules[z].second->distRule;        
        const string newTemplate = distribution[idx].first->AddTemplateClone(redistrRule);

        const auto &toRealign = createRealignRules(current->loop, regionId, file, newTemplate, arrayLinksByFuncCalls, current->usedArrays);
        for (auto &rule : toRealign[0])
            toInsert.push_back(make_pair(current->lineNum, rule));
        for (auto &rule : toRealign[1])
            toInsert.push_back(make_pair(current->lineNumAfterLoop, rule));

        if (toRealign[0].size())
            currParDir->cloneOfTemplate = newTemplate;
    }
    current->setNewRedistributeRules(redistributeRules);

    return needToSkip;
}

static bool splitToBase(SgExpression *ex, pair<SgExpression*, int> &splited)
{
    bool res = true;
    if (ex->variant() == VAR_REF || ex->variant() == ARRAY_REF || ex->variant() == MULT_OP)
        splited = make_pair(ex, 0);
    else
    {
        if (ex->variant() == SUBT_OP || ex->variant() == ADD_OP)
        {
            int minus = (ex->variant() == ADD_OP) ? 1 : -1;
            if (ex->rhs())
            {
                int err, val;
                err = CalculateInteger(ex->rhs(), val);
                if (err == 0)
                {
                    const int nextEx = ex->lhs()->variant();
                    if (nextEx == VAR_REF || nextEx == ARRAY_REF || nextEx == MULT_OP)
                        splited = make_pair(ex->lhs(), minus * val);
                    else if (nextEx == SUBT_OP || nextEx == ADD_OP)
                    {
                        pair<SgExpression*, int> splitedNext;
                        bool res = splitToBase(ex->lhs(), splitedNext);
                        if (res == false)
                            return false;
                        else
                            splited = make_pair(splitedNext.first, minus * val + splitedNext.second);
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    return res;
}


static void analyzeRightPart(SgExpression *ex, map<DIST::Array*, vector<pair<bool, map<string, pair<int, int>>>>> &rightValues,
                             const map<DIST::Array*, vector<bool>> &dimsNotMatch)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            const std::string name = ex->symbol()->identifier();
            for (auto &elem : dimsNotMatch)
            {
                if (elem.first->GetShortName() == name)
                {
                    int idx = 0;
                    for (auto expr = ex->lhs(); expr; expr = expr->rhs(), ++idx)
                    {
                        if (elem.second[idx])
                        {
                            int err, val;
                            err = CalculateInteger(expr->lhs(), val);
                            if (err == 0)
                            {
                                if (rightValues[elem.first][idx].first)
                                {
                                    auto it = rightValues[elem.first][idx].second.find("");
                                    if (it == rightValues[elem.first][idx].second.end())
                                        rightValues[elem.first][idx].second[""] = make_pair(val, val);
                                    else
                                    {
                                        it->second.first = std::min(it->second.first, val);
                                        it->second.second = std::max(it->second.second, val);
                                    }
                                }
                                else
                                {
                                    rightValues[elem.first][idx].first = true;
                                    rightValues[elem.first][idx].second[""] = make_pair(val, val);
                                }
                            }
                            else
                            {
                                pair<SgExpression*, int> splited;
                                bool result = splitToBase(expr->lhs(), splited);
                                if (result)
                                {
                                    if (rightValues[elem.first][idx].first)
                                    {
                                        auto key = string(splited.first->unparse());
                                        auto itS = rightValues[elem.first][idx].second.find(key);
                                        if (itS == rightValues[elem.first][idx].second.end())
                                            itS = rightValues[elem.first][idx].second.insert(itS, make_pair(key, make_pair(splited.second, splited.second)));
                                        else
                                        {
                                            itS->second.first = std::min(itS->second.first, splited.second);
                                            itS->second.second = std::max(itS->second.second, splited.second);
                                        }
                                    }
                                    else
                                    {
                                        rightValues[elem.first][idx].first = true;
                                        rightValues[elem.first][idx].second[string(splited.first->unparse())] = make_pair(splited.second, splited.second);                                     
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }

        analyzeRightPart(ex->lhs(), rightValues, dimsNotMatch);
        analyzeRightPart(ex->rhs(), rightValues, dimsNotMatch);
    }
}

static bool analyzeLeftPart(SgExpression *left, const map<DIST::Array*, vector<bool>>& dimsNotMatch, 
                            map<DIST::Array*, vector<pair<bool, pair<string, int>>>> &leftValues, string &base)
{
    const std::string name = left->symbol()->identifier();
    for (auto& elem : dimsNotMatch)
    {
        if (elem.first->GetShortName() == name)
        {
            int idx = 0;
            for (auto ex = left->lhs(); ex; ex = ex->rhs(), ++idx)
            {
                if (elem.second[idx])
                {
                    int err, val;
                    err = CalculateInteger(ex->lhs(), val);
                    if (err == 0)
                    {
                        if (leftValues[elem.first][idx].first)
                        {
                            if (leftValues[elem.first][idx].second.first != "") // has non zero base expression
                                return false;
                            if (leftValues[elem.first][idx].second.second != val) // has conflict writes
                                return false;
                        }
                        else
                            leftValues[elem.first][idx] = make_pair(true, make_pair("", val));
                    }
                    else // WRITE OP can not recognized
                    {
                        pair<SgExpression*, int> splited;
                        bool result = splitToBase(ex->lhs(), splited);
                        if (result == false)
                            return false;
                        if (leftValues[elem.first][idx].first)
                        {
                            // has conflict writes
                            if (leftValues[elem.first][idx].second.first != string(splited.first->unparse()) ||
                                leftValues[elem.first][idx].second.second != splited.second)
                                return false;
                        }
                        else
                        {
                            base = string(splited.first->unparse());
                            leftValues[elem.first][idx] = make_pair(true, make_pair(base, splited.second));
                        }
                    }
                }
            }
            break;
        }
    }
    return true;
}

bool analyzeLoopBody(LoopGraph* loopV, 
                     map<DIST::Array*, vector<pair<bool, pair<string, int>>>>& leftValues,
                     map<DIST::Array*, vector<pair<bool, map<string, pair<int, int>>>>>& rightValues,
                     string& base,
                     const map<DIST::Array*, vector<bool>> &dimsNotMatch,
                     const map<string, FuncInfo*>& mapFuncInfo)
{
    SgStatement* loop = loopV->loop->GetOriginal();
    for (auto st = loop; st != loop->lastNodeOfStmt(); st = st->lexNext())
    {
        if (st->variant() == ASSIGN_STAT)
        {
            auto left = st->expr(0);
            if (left->variant() == ARRAY_REF)
            {
                bool ok = analyzeLeftPart(left, dimsNotMatch, leftValues, base);
                if (ok == false)
                    return false;
            }
            analyzeRightPart(st->expr(1), rightValues, dimsNotMatch);
        }
        else if (st->variant() == PROC_STAT)
        {
            string name = st->symbol()->identifier();
            if (isIntrinsicFunctionName(name.c_str()) == 0)
            {
                //TODO: contains and modules
                auto it = mapFuncInfo.find(name);
                int z = 0;
                for (SgExpression* ex = st->expr(0); ex; ex = ex->rhs(), ++z)
                {
                    if (ex->lhs()->variant() == ARRAY_REF)
                    {
                        bool ok = true;
                        if (it == mapFuncInfo.end())
                            ok = analyzeLeftPart(ex->lhs(), dimsNotMatch, leftValues, base);
                        else
                        {
                            if (it->second->funcParams.isArgIn(z) && !it->second->funcParams.isArgOut(z))
                                analyzeRightPart(ex->lhs(), rightValues, dimsNotMatch);
                            else
                                ok = analyzeLeftPart(ex->lhs(), dimsNotMatch, leftValues, base);
                        }
                        if (ok == false)
                            return false;
                    }
                    else
                        analyzeRightPart(ex->lhs(), rightValues, dimsNotMatch);
                }
            }
        }
        else
        {
            for (int i = 0; i < 3; ++i)
                analyzeRightPart(st->expr(1), rightValues, dimsNotMatch);
        }
    }

    //is OK ?
    return true;
}

#undef PRINT_DIR_RESULT 
#undef FIRST
#undef SECOND
#undef THIRD
