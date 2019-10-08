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

static bool isOnlyTopPerfect(LoopGraph *current, const vector<pair<DIST::Array*, const DistrVariant*>> &distribution)
{
    for (auto &elem : distribution)
    {
        if (elem.first == current->directive->arrayRef)
        {
            bool allNone = true;
            for (auto &dist : elem.second->distRule)
            {
                if (dist != NONE)
                {
                    allNone = false;
                    break;
                }
            }
            if (allNone)
                return true;
        }
    }

    LoopGraph *next = current;

    for (int i = 0; i < current->perfectLoop - 1; ++i)
        next = next->children[0];

    if (next->children.size() == 0)
        return true;
    else
    //    return false;
    {
        while (next->children.size() != 0)
        {
            if (next->children.size() > 1)
                return false;
            else
            {
                next = next->children[0];
                bool condition = next->directive != NULL;
                if (condition)
                    condition = next->directive->arrayRef != NULL;

                if (condition)
                {
                    bool found = false;
                    for (int k = 0; k < distribution.size(); ++k)
                    {
                        if (distribution[k].first == next->directive->arrayRef)
                        {
                            int dimPos = -1;
                            for (int p = 0; p < next->directiveForLoop->on.size(); ++p)
                            {
                                if (next->directiveForLoop->on[p].first == next->directiveForLoop->parallel[0])
                                {
                                    dimPos = p;
                                    break;
                                }
                            }

                            if (dimPos == -1)
                            {
                                found = true; //continue;
                                break;
                            }

                            if (distribution[k].second->distRule[dimPos] != NONE)
                                return false;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        return false;
                }
                else
                    return false;
            }
        }
        return true;
    }
}

static bool createLinksBetweenArrays(map<DIST::Array*, vector<int>> &links, DIST::Array *dist, 
                                     const std::map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                     DIST::GraphCSR<int, double, attrType> &reducedG,
                                     DIST::Arrays<int> &allArrays, const int regionId)
{
    bool ok = true;
    if (dist == NULL)
        return false;

    for (auto &array : links)
    {
        set<DIST::Array*> realArrayRef;
        getRealArrayRefs(array.first, array.first, realArrayRef, arrayLinksByFuncCalls);

        vector<vector<int>> AllLinks(realArrayRef.size());
        int currL = 0;
        for (auto &array : realArrayRef)
            AllLinks[currL++] = findLinksBetweenArrays(array, dist, regionId);

        if (isAllRulesEqual(AllLinks))
            array.second = AllLinks[0];

        if (ok == false)
            break;
    }
    return ok;
}

static bool checkCorrectness(const ParallelDirective &dir, 
                             const vector<pair<DIST::Array*, const DistrVariant*>> &distribution, 
                             DIST::GraphCSR<int, double, attrType> &reducedG,
                             DIST::Arrays<int> &allArrays,
                             const std::map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                             const set<DIST::Array*> &allArraysInLoop,
                             vector<Messages> &messages, const int loopLine,
                             map<DIST::Array*, vector<bool>> &dimsNotMatch, const int regionId)
{    
    const pair<DIST::Array*, const DistrVariant*> *distArray = NULL;
    pair<DIST::Array*, const DistrVariant*> *newDistArray = NULL;
    map<DIST::Array*, vector<int>> arrayLinksWithTmpl;
    map<DIST::Array*, vector<int>> arrayLinksWithDirArray;

    const DistrVariant *distRuleTempl = NULL;

    for (auto &array : allArraysInLoop)
        arrayLinksWithDirArray[array] = arrayLinksWithTmpl[array] = vector<int>();

    vector<int> links;
    bool ok = true;

    for (int i = 0; i < distribution.size(); ++i)
    {
        if (dir.arrayRef2 == distribution[i].first)
        {
            distArray = &distribution[i];
            for (int z = 0; z < distArray->first->GetDimSize(); ++z)
                links.push_back(z);
            distRuleTempl = distribution[i].second;
            break;
        }
    }
        
    if (!distArray)
    {
        bool found = false;
        for (int i = 0; i < distribution.size(); ++i)
        {
            DIST::Array *currDistArray = distribution[i].first;

            set<DIST::Array*> realArrayRef;
            getRealArrayRefs(dir.arrayRef2, dir.arrayRef2, realArrayRef, arrayLinksByFuncCalls);

            vector<vector<int>> AllLinks(realArrayRef.size());
            int currL = 0;
            for (auto &array : realArrayRef)
                AllLinks[currL++] = findLinksBetweenArrays(array, currDistArray, regionId);

            if (isAllRulesEqual(AllLinks))
                links = AllLinks[0];
            else
            {
                wstring bufE, bufR;
                __spf_printToLongBuf(bufE, L"Can not create distributed link");
#ifdef _WIN32
                __spf_printToLongBuf(bufR, R127);
#endif

                messages.push_back(Messages(ERROR, loopLine, bufR, bufE, 3007));
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            for (int k = 0; k < links.size(); ++k)
            {
                if (links[k] != -1)
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                if (dir.arrayRef2->GetDimSize() != links.size())
                {
                    __spf_print(1, "Can not create distributed link for array '%s': dim size of this array is '%d' and it is not equal '%d'\n", 
                                    dir.arrayRef2->GetShortName().c_str(), dir.arrayRef2->GetDimSize(), (int)links.size());

                    wstring bufE, bufR;
                    __spf_printToLongBuf(bufE, L"Can not create distributed link for array '%s': dim size of this array is '%d' and it is not equal '%d'", 
                                         to_wstring(dir.arrayRef2->GetShortName()).c_str(), dir.arrayRef2->GetDimSize(), (int)links.size());
#ifdef _WIN32
                    __spf_printToLongBuf(bufR, R126,
                                         to_wstring(dir.arrayRef2->GetShortName()).c_str(), dir.arrayRef2->GetDimSize(), (int)links.size());
#endif

                    messages.push_back(Messages(ERROR, loopLine, bufR, bufE, 3007));

                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                vector<dist> derivedRule(dir.arrayRef2->GetDimSize());
                for (int z = 0; z < links.size(); ++z)
                {
                    if (links[z] != -1)
                        derivedRule[z] = distribution[i].second->distRule[links[z]];
                    else
                        derivedRule[z] = dist::NONE;
                }

                newDistArray = new pair<DIST::Array*, const DistrVariant*>();
                newDistArray->first = dir.arrayRef2;

                DistrVariant *tmp = new DistrVariant(derivedRule);
                newDistArray->second = tmp;
                distArray = newDistArray;
                distRuleTempl = distribution[i].second;
                break;
            }
        }

        if (found == false)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    
    auto templArray = dir.arrayRef;
    if (templArray->IsTemplate() == false)
        templArray = dir.arrayRef->GetTemplateArray(regionId);

    ok = createLinksBetweenArrays(arrayLinksWithTmpl, templArray, arrayLinksByFuncCalls, reducedG, allArrays, regionId);
    if (ok == false)
    {
        if (newDistArray)
        {
            delete newDistArray->second;
            delete newDistArray;
        }
        return ok;
    }

    if (dir.arrayRef->IsTemplate())
        arrayLinksWithDirArray = arrayLinksWithTmpl;
    else
        ok = ok && createLinksBetweenArrays(arrayLinksWithDirArray, dir.arrayRef, arrayLinksByFuncCalls, reducedG, allArrays, regionId);
    
    // check main array
    if (dir.arrayRef2 != dir.arrayRef)
    {
        const vector<dist> &rule = distArray->second->distRule;

        DIST::Array* key = distArray->first;
        dimsNotMatch[key] = vector<bool>(rule.size());
        auto it = dimsNotMatch.find(key);

        std::fill(it->second.begin(), it->second.end(), false);

        for (int i = 0; i < rule.size(); ++i)
        {
            if (rule[i] == dist::BLOCK)
            {
                if (dir.on[links[i]].first == "*")
                {
                    ok = false;
                    it->second[i] = true;
                }
            }
        }
    }

    for (auto &array : arrayLinksWithTmpl)
    {
        auto dirArrayRef = arrayLinksWithDirArray[array.first];

        if (array.first != dir.arrayRef2 && array.first != dir.arrayRef)
        {
            vector<dist> derivedRule(array.first->GetDimSize());

            DIST::Array* key = array.first;
            dimsNotMatch[key] = vector<bool>(array.first->GetDimSize());

            auto it = dimsNotMatch.find(key);
            std::fill(it->second.begin(), it->second.end(), false);

            for (int z = 0; z < array.second.size(); ++z)
            {
                if (array.second[z] != -1)
                    derivedRule[z] = distRuleTempl->distRule[array.second[z]];
                else
                    derivedRule[z] = dist::NONE;
            }

            for (int i = 0; i < derivedRule.size(); ++i)
            {
                if (derivedRule[i] == dist::BLOCK)
                {
                    if (dir.on[dirArrayRef[i]].first == "*")
                    {
                        ok = false;
                        it->second[i] = true;
                    }
                }
            }
        }
    }

    if (newDistArray)
    {
        delete newDistArray->second;
        delete newDistArray;
    }
    return ok;
}

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
    genRedistributeDirective(SgFile *file, const vector<pair<DIST::Array*, const DistrVariant*>> distribution, 
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
static bool addRedistributionDirs(SgFile *file, const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
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
            SgStatement *startSt = current->loop->GetOriginal();
            SgStatement *cp = startSt->controlParent();
            int nestedLvl = 1;
            while (cp)
            {                
                if (cp->variant() == FOR_NODE)
                {
                    const int line = cp->lineNumber();
                    
                    auto itL = loopGraph.find(line);
                    if (itL == loopGraph.end())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    if (itL->second->directiveForLoop != NULL || itL->second->directive != NULL)
                        return needToSkip;
                    nestedLvl = itL->second->perfectLoop;
                    if (nestedLvl > 1)
                        return needToSkip;
                }
                cp = cp->controlParent();
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

static void constructRules(vector<pair<DIST::Array*, const DistrVariant*>>& outRules, const vector<pair<DIST::Array*, const DistrVariant*>> &distribution, LoopGraph *loop)
{
    outRules = distribution;
    for (auto &rule : outRules)
    {
        const DistrVariant *redistRules = loop->getRedistributeRule(rule.first);
        if (redistRules)
            rule.second = redistRules;
    }
}

static void propagateTemplateInfo(map<DIST::Array*, vector<pair<bool, map<string, pair<int, int>>>>> &arrays, const int regId,
                                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                  DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto &arrayElem: arrays)
        {
            auto array = arrayElem.first;
            if (array->GetTemplateArray(regId) == NULL)
            {
                vector<tuple<DIST::Array*, int, pair<int, int>>> templRule =
                    getAlignRuleWithTemplate(array, arrayLinksByFuncCalls, reducedG, allArrays, regId);

                int idx = 0;
                for (auto &elem : templRule)
                {
                    if (get<0>(elem) == NULL)
                    {
                        idx++;
                        continue;
                    }
                    auto templ = get<0>(elem);
                    auto alignDim = get<1>(elem);
                    auto intRule = get<2>(elem);

                    int dimNum = -1;
                    int err = allArrays.GetDimNumber(get<0>(elem), alignDim, dimNum);
                    if (err == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    array->AddLinkWithTemplate(idx, dimNum, templ, intRule, regId);
                    ++idx;
                    changed = true;
                }
            }
        }
    }
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
                    splited = make_pair(ex->lhs(), minus * val);
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

static inline bool findAndResolve(bool &resolved, vector<pair<bool, string>> &updateOn,
                                  const map<DIST::Array*, vector<bool>> &dimsNotMatch,
                                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                  DIST::GraphCSR<int, double, attrType> &reducedG, 
                                  const DIST::Arrays<int> &allArrays, const int regId,
                                  ParallelDirective *parDirective,
                                  map<DIST::Array*, vector<pair<bool, pair<string, int>>>> &values,
                                  const set<string> &deprecateToMatch,
                                  bool fromRead = false)
{
    bool ret = true;

    for (auto &elem : dimsNotMatch)
    {
        vector<tuple<DIST::Array*, int, pair<int, int>>> rule;

        set<DIST::Array*> realRefs;
        getRealArrayRefs(elem.first, elem.first, realRefs, arrayLinksByFuncCalls);

        vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> allRules(realRefs.size());
        int tmpIdx = 0;
        for (auto &array : realRefs)
            reducedG.GetAlignRuleWithTemplate(array, allArrays, allRules[tmpIdx++], regId);

        if (isAllRulesEqual(allRules))
            rule = allRules[0];
        else
            return false;

        findAndReplaceDimentions(rule, allArrays);

        for (int i = 0; i < elem.second.size(); ++i)
        {
            if (elem.second[i] && values[elem.first][i].first)
            {
                const int idx = get<1>(rule[i]);
                const auto &currRule = get<2>(rule[i]);
                //TODO: use rule
                string mapTo = "";
                if (values[elem.first][i].second.first != "")
                {
                    mapTo = values[elem.first][i].second.first;
                    if (values[elem.first][i].second.second != 0)
                        mapTo += " + " + std::to_string(values[elem.first][i].second.second);
                }
                else
                    mapTo = std::to_string(values[elem.first][i].second.second);

                if (deprecateToMatch.find(mapTo) != deprecateToMatch.end())
                    return false;

                if (updateOn[idx].first)
                {
                    if (updateOn[idx].second != mapTo && !fromRead) // DIFFERENT VALUES TO MAP
                        return false;
                }
                else
                    updateOn[idx] = make_pair(true, mapTo);
            }
        }
    }

    for (int i = 0; i < updateOn.size(); ++i)
    {
        if (updateOn[i].first)
        {
            if (parDirective->on[i].first != "*")
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            else
            {
                parDirective->on[i].first = updateOn[i].second;
                parDirective->on[i].second = make_pair(1, 0);
                resolved = true;

                if (!parDirective->arrayRef->IsTemplate())
                {
                    parDirective->on2[i].first = updateOn[i].second;
                    parDirective->on2[i].second = make_pair(1, 0);
                }
                else
                {
                    set<DIST::Array*> realRefsOfPar;
                    getRealArrayRefs(parDirective->arrayRef2, parDirective->arrayRef2, realRefsOfPar, arrayLinksByFuncCalls);

                    vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> allRules(realRefsOfPar.size());
                    int tmpIdx = 0;
                    for (auto &array : realRefsOfPar)
                        reducedG.GetAlignRuleWithTemplate(array, allArrays, allRules[tmpIdx++], regId);

                    if (!isAllRulesEqual(allRules))
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    DIST::Array *arrayRef2 = *realRefsOfPar.begin();
                    auto links = arrayRef2->GetLinksWithTemplate(regId);
                    if (arrayRef2->GetTemplateArray(regId) != parDirective->arrayRef)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    int found = -1;
                    for (int z = 0; z < links.size(); ++z)
                        if (links[z] == i)
                            found = z;
                    if (found == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    if (parDirective->on2[found].first != "*")
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    parDirective->on2[found].first = updateOn[i].second;
                    parDirective->on2[found].second = make_pair(1, 0);
                }
            }
        }
    }

    return ret;
}

//TODO: 
static bool tryToResolveUnmatchedDims(const map<DIST::Array*, vector<bool>> &dimsNotMatch, SgStatement *loop, const int regId,
                                     ParallelDirective *parDirective, DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays,
                                     const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                     const vector<pair<DIST::Array*, const DistrVariant*>> &distribution)
{
    bool resolved = false;

    map<DIST::Array*, vector<pair<bool, pair<string, int>>>> leftValues;
    map<DIST::Array*, vector<pair<bool, map<string, pair<int, int>>>>> rightValues;

    for (auto &elem : dimsNotMatch)
    {
        leftValues[elem.first] = vector<pair<bool, pair<string, int>>>(elem.second.size());
        std::fill(leftValues[elem.first].begin(), leftValues[elem.first].end(), make_pair(false, make_pair("", 0)));

        rightValues[elem.first] = vector<pair<bool, map<string, pair<int, int>>>>(elem.second.size());
        std::fill(rightValues[elem.first].begin(), rightValues[elem.first].end(), make_pair(false, map<string, pair<int, int>>()));
    }

    string base = "";
    for (auto st = loop; st != loop->lastNodeOfStmt(); st = st->lexNext())
    {
        if (st->variant() == ASSIGN_STAT)
        {
            auto left = st->expr(0);
            if (left->variant() == ARRAY_REF)
            {
                const std::string name = left->symbol()->identifier();
                for (auto &elem : dimsNotMatch)
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
            }

            analyzeRightPart(st->expr(1), rightValues, dimsNotMatch);
        }
        else
        {
            for (int i = 0; i < 3; ++i)
                analyzeRightPart(st->expr(1), rightValues, dimsNotMatch);
        }
    }

    // check found info
    for (auto &elem : dimsNotMatch)
    {
        for (int idx = 0; idx < elem.second.size(); ++idx)
            if (elem.second[idx] && (!leftValues[elem.first][idx].first && !rightValues[elem.first][idx].first)) // NOT INFO FOUND
                return false;
    }

    //check multiplied Arrays to BLOCK distr of template
    for (auto &elem : dimsNotMatch)
    {
        set<DIST::Array*> realRefs;
        getRealArrayRefs(elem.first, elem.first, realRefs, arrayLinksByFuncCalls);

        set<DIST::Array*> templates;
        set<vector<int>> links;
        for (auto &realR : realRefs)
        {
            templates.insert(realR->GetTemplateArray(regId));
            links.insert(realR->GetLinksWithTemplate(regId));
        }

        DIST::Array *templ = NULL;
        vector<int> alignLinks;
        if (templates.size() == 1 && links.size() == 1)
        {
            templ = *templates.begin();
            alignLinks = *links.begin();
        }

        if (!templ)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (elem.first->GetDimSize() != templ->GetDimSize())
        {
            const DistrVariant *var = NULL;
            for (auto &distRule : distribution)
            {
                if (distRule.first == templ)
                {
                    var = distRule.second;
                    break;
                }
            }

            if (!var)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        
            const set<int> alingLinksSet(alignLinks.begin(), alignLinks.end());
            for (int z = 0; z < templ->GetDimSize(); ++z)
            {
                if (alingLinksSet.find(z) == alingLinksSet.end())
                {
                    if (var->distRule[z] == BLOCK)
                    {
                        //check all accesses to write
                        for (auto &left : leftValues)
                            for (auto &toCheck : left.second)
                                if (toCheck.first)
                                    return false;
                        return true;
                    }
                }
            }
        }
    }

    vector<pair<bool, string>> updateOn(parDirective->on.size());
    std::fill(updateOn.begin(), updateOn.end(), make_pair(false, ""));

    set<string> deprecateToMatch;
    int nested = ((SgForStmt*)loop)->isPerfectLoopNest();
    SgForStmt *tmpL = (SgForStmt*)loop;
    for (int z = 0; z < nested; ++z)
    {
        deprecateToMatch.insert(tmpL->symbol()->identifier());
        tmpL = (SgForStmt*)(tmpL->lexNext());
    }
    auto tmpL1 = loop->controlParent();
    while (tmpL1->variant() == FOR_NODE)
    {
        deprecateToMatch.insert(((SgForStmt*)tmpL1)->symbol()->identifier());
        tmpL1 = tmpL1->controlParent();
        if (tmpL1 == NULL)
            break;
    }
    //try to resolve from write operations
    bool ok = findAndResolve(resolved, updateOn, dimsNotMatch, arrayLinksByFuncCalls, reducedG, allArrays, regId, parDirective, leftValues, deprecateToMatch);
    if (!ok)
        return false;
    else
    {
        //shift right splited values
        if (base != "")
        {
            for (auto &right : rightValues)
            {
                auto itL = leftValues.find(right.first);
                if (itL == leftValues.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                for (int z = 0; z < right.second.size(); ++z)
                {
                    if (right.second[z].first)
                    {
                        auto itB = right.second[z].second.find(base);
                        if (itB != right.second[z].second.end())
                        {
                            itB->second.first -= itL->second[z].second.second;
                            itB->second.second -= itL->second[z].second.second;
                        }
                    }
                }
            }
        }
    }
  
    //try to resolve from read operations
    if (!resolved)
    {
        return false;
        /*map<DIST::Array*, vector<pair<bool, pair<SgExpression*, int>>>> values2;
        for (auto &elem : rightValues)
            for (auto &vElem : elem.second)
                values2[elem.first].push_back(make_pair(vElem.first, vElem.second.first));
        
        ok = findAndResolve(resolved, updateOn, dimsNotMatch, arrayLinksByFuncCalls, reducedG, allArrays, regId, parDirective, values2, true);
        if (!ok)
            return false;*/
    }   
    
    if (resolved)
    {
        propagateTemplateInfo(rightValues, regId, arrayLinksByFuncCalls, reducedG, allArrays);

        for (auto &elem : rightValues)
        {
            auto &shortName = elem.first->GetShortName();
            
            for (auto &shadows : parDirective->shadowRenew)
            {
                if (shadows.first.first == shortName)
                {
                    const auto &leftPartVal = leftValues[elem.first];
                    for (int i = 0; i < leftPartVal.size(); ++i)
                    {
                        if (leftPartVal[i].first || elem.second[i].first)
                        {
                            int foundVal = 0;
                            if (leftPartVal[i].first)
                                foundVal = leftPartVal[i].second.second;
                            else
                            {
                                auto rules = elem.first->GetAlignRulesWithTemplate(regId);
                                auto links = elem.first->GetLinksWithTemplate(regId);
                                if (links[i] == -1)
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                const auto &currRule = rules[i];
                                if (base == "")
                                    foundVal = std::stoi(parDirective->on[links[i]].first) + currRule.second;
                                else
                                    foundVal = currRule.second;
                            }

                            auto itSh = elem.second[i].second.find(base);
                            if (itSh != elem.second[i].second.end()) // shadow
                            {
                                auto shadowElem = itSh->second;
                                shadowElem.first -= foundVal;
                                shadowElem.second -= foundVal;

                                if (shadowElem.first > 0)
                                    shadowElem.first = 0;
                                if (shadowElem.second < 0)
                                    shadowElem.second = 0;

                                shadows.second[i].first = std::max(shadows.second[i].first, abs(shadowElem.first));
                                shadows.second[i].second = std::max(shadows.second[i].second, shadowElem.second);
                            }
                            else // remote
                            {
                                string bounds = "";
                                SgExprListExp *listB = new SgExprListExp();
                                for (int z = 0; z < elem.first->GetDimSize(); ++z)
                                {
                                    bounds += ":";
                                    if (z != elem.first->GetDimSize() - 1)
                                        bounds += ",";

                                    if (z == 0)
                                        listB->setLhs(*new SgExpression(DDOT));
                                    else
                                        listB->append(*new SgExpression(DDOT));
                                }
                                parDirective->remoteAccess[make_pair(elem.first->GetShortName(), bounds)] = new Expression(listB);
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    return resolved;
}

void selectParallelDirectiveForVariant(SgFile *file, ParallelRegion *currParReg, 
                                       DIST::GraphCSR<int, double, attrType> &reducedG,
                                       DIST::Arrays<int> &allArrays, 
                                       const vector<LoopGraph*> &loopGraph,
                                       const map<int, LoopGraph*> &mapLoopsByFile,
                                       const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                                       const vector<AlignRule> &alignRules,
                                       vector<pair<int, pair<string, vector<Expression*>>>> &toInsert,
                                       const int regionId,
                                       const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                       const map<LoopGraph*, depGraph*> &depInfoForLoopGraph,
                                       vector<Messages> &messages)
{
    for (int i = 0; i < loopGraph.size(); ++i)
    {
        LoopGraph *loop = loopGraph[i];
        currProcessing.second = loop->loop->lineNumber();

        if (loop->directive && 
            (loop->hasLimitsToParallel() == false) && 
            (loop->region == currParReg) && 
            (loop->userDvmDirective == NULL))
        {
            if (loop->perfectLoop >= 1)
            {
                bool topCheck = isOnlyTopPerfect(loop, distribution);
                ParallelDirective *parDirective = loop->directive;
                parDirective->cloneOfTemplate = "";
                if (topCheck == false)
                {  //try to unite loops and recheck
                    bool result = createNestedLoops(loop, depInfoForLoopGraph, messages);
                    if (result)
                    {
                        parDirective = loop->recalculateParallelDirective();
                        topCheck = isOnlyTopPerfect(loop, distribution);
                    }
                }
                
                bool needToContinue = false;
                if (topCheck)
                {
                     //<Array, linksWithTempl> -> dims not mached
                    map<DIST::Array*, vector<bool>> dimsNotMatch;
                    if (!checkCorrectness(*parDirective, distribution, reducedG, allArrays, arrayLinksByFuncCalls, loop->getAllArraysInLoop(), messages, loop->lineNum, dimsNotMatch, regionId))
                    {
                        if (!tryToResolveUnmatchedDims(dimsNotMatch, loop->loop->GetOriginal(), regionId, parDirective, reducedG, allArrays, arrayLinksByFuncCalls, distribution))
                            needToContinue = addRedistributionDirs(file, distribution, toInsert, loop, mapLoopsByFile, parDirective, regionId, messages, arrayLinksByFuncCalls);
                    }
                }
                else
                    needToContinue = addRedistributionDirs(file, distribution, toInsert, loop, mapLoopsByFile, parDirective, regionId, messages, arrayLinksByFuncCalls);
                
                if (needToContinue)
                    continue;

                vector<pair<DIST::Array*, const DistrVariant*>> newRules;
                constructRules(newRules, distribution, loop);

                // insert parallel dir
                pair<string, vector<Expression*>> dir = 
                    parDirective->genDirective(new File(file), newRules, alignRules, reducedG, allArrays, loop->acrossOutAttribute, 
                                               loop->readOps, loop->loop, loop->lineNum, loop->altLineNum, regionId, arrayLinksByFuncCalls);

                if (loop->lineNum < 0)
                {
                    SgStatement* result = new SgStatement(DVM_PARALLEL_ON_DIR, NULL, NULL, NULL, NULL, NULL);
                    for (int i = 0; i < 3; ++i)
                        if (dir.second[i])
                            result->setExpression(i, *dir.second[i]);

                    if (loop->altLineNum == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    SgStatement* local = NULL;
                    local = SgStatement::getStatementByFileAndLine(loop->loop->fileName(), loop->lineNum);
                    if (local == NULL)
                        local = SgStatement::getStatementByFileAndLine(loop->loop->fileName(), loop->altLineNum);
                    checkNull(local, convertFileName(__FILE__).c_str(), __LINE__);

                    local->insertStmtBefore(*result, *local->controlParent());
                    /*SgStatement* local = NULL;
                    int line = loop->altLineNum + 1;
                    while (local == NULL)
                    {
                        local = SgStatement::getStatementByFileAndLine(loop->loop->fileName(), line);
                        ++line;
                    }
                    local->insertStmtBefore(*result, *local->controlParent());*/
                }
                else
                    toInsert.push_back(make_pair(loop->lineNum, dir));
            }
        }
        else //TODO: add checker for indexing in this loop
        {
            if (loopGraph[i]->children.size() != 0)
                selectParallelDirectiveForVariant(file, currParReg, reducedG, allArrays, loopGraph[i]->children, mapLoopsByFile, 
                                                  distribution, alignRules, toInsert, regionId, arrayLinksByFuncCalls, 
                                                  depInfoForLoopGraph, messages);
        }
    }
}

#undef PRINT_DIR_RESULT 
#undef FIRST
#undef SECOND
#undef THIRD
