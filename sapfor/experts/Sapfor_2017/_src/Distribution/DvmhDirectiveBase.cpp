#include "../Utils/leak_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

#include "DvmhDirective.h"
#include "../Distribution/Array.h"
#include "../Distribution/Arrays.h"
#include "../Distribution/GraphCSR.h"
#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../GraphCall/graph_calls_func.h"

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

template<typename setT>
static void uniteSets(const set<setT> &first, const set<setT> &second, set<setT> &result)
{
    vector<setT> unitedVector(first.size() + second.size());
    auto it = set_union(first.begin(), first.end(), second.begin(), second.end(), unitedVector.begin());
    unitedVector.resize(it - unitedVector.begin());
    for (int i = 0; i < (int)unitedVector.size(); ++i)
        result.insert(unitedVector[i]);
}

template<typename keyT, typename valT>
static void uniteSets(const map<keyT, valT> &first, const map<keyT, valT> &second, map<keyT, valT> &result)
{
    vector<pair<keyT, valT>> unitedVector(first.size() + second.size());
    auto it = set_union(first.begin(), first.end(), second.begin(), second.end(), unitedVector.begin());
    unitedVector.resize(it - unitedVector.begin());
    for (int i = 0; i < (int)unitedVector.size(); ++i)
        result.insert(unitedVector[i]);
}

template<typename keyT, typename valT>
static void uniteReduction(const map<keyT, valT> &first, const map<keyT, valT> &second, map<keyT, valT> &result)
{
    auto itF = first.begin();
    for (auto &redList : result)
    {
        auto itFound = second.find(redList.first);
        if (itFound != second.end())
            uniteSets(itF->second, itFound->second, redList.second);
        ++itF;
    }

    for (auto redList : second)
    {
        auto itFound = result.find(redList.first);
        if (itFound == result.end())
            result.insert(itFound, redList);
    }
}

template<typename vTuples>
static vTuples uniteOnRules(const vTuples &first, const vTuples &second)
{
    vTuples result(first.size());
    for (int i = 0; i < (int)first.size(); ++i)
    {
        bool firstStar = first[i].first == "*";
        bool secondStar = second[i].first == "*";
        if (firstStar && secondStar)
            result[i].first = "*";
        else if (firstStar)
            result[i] = second[i];
        else
            result[i] = first[i];
    }
    return result;
}

ParallelDirective* operator+(const ParallelDirective &left, const ParallelDirective &right)
{
    const ParallelDirective *first = &left;
    const ParallelDirective *second = &right;

    ParallelDirective *result = NULL;
    checkNull(first, convertFileName(__FILE__).c_str(), __LINE__);
    checkNull(second, convertFileName(__FILE__).c_str(), __LINE__);

    if (first->arrayRef == second->arrayRef)
    {
        if (first->on.size() != second->on.size())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        result = new ParallelDirective();

        result->langType = first->langType;
        result->file = first->file;
        result->line = first->line;
        result->col = first->col;

        result->arrayRef = first->arrayRef;
        result->arrayRef2 = first->arrayRef2;

        result->parallel = vector<string>(first->parallel.size() + second->parallel.size());
        result->on = vector<pair<string, pair<int, int>>>(first->on.size());

        for (int i = 0; i < (int)first->parallel.size(); ++i)
            result->parallel[i] = first->parallel[i];

        for (int i = 0; i < (int)second->parallel.size(); ++i)
            result->parallel[i + first->parallel.size()] = second->parallel[i];

        result->on = uniteOnRules(first->on, second->on);
        result->on2 = uniteOnRules(first->on2, second->on2);

        uniteVectors(first->across, second->across, result->across);
        uniteVectors(first->shadowRenew, second->shadowRenew, result->shadowRenew);

        uniteSets(first->privates, second->privates, result->privates);
        uniteSets(first->remoteAccess, second->remoteAccess, result->remoteAccess);

        result->reduction = first->reduction;
        result->reductionLoc = first->reductionLoc;

        uniteReduction(first->reduction, second->reduction, result->reduction);
        uniteReduction(first->reductionLoc, second->reductionLoc, result->reductionLoc);
    }
    else
        result = new ParallelDirective(left);
    return result;
}


static inline int findRule(const int alingDim, const vector<tuple<DIST::Array*, int, pair<int, int>>> &rule, pair<int, pair<int, int>> &retVal)
{
    for (int i = 0; i < rule.size(); ++i)
    {
        if (get<1>(rule[i]) == alingDim)
        {
            retVal = make_pair(i, get<2>(rule[i]));
            return 0;
        }
    }
    return -1;
}

static inline bool isNonDistributedDim(const vector<tuple<DIST::Array*, int, pair<int, int>>> &ruleForOn,
                                       const vector<tuple<DIST::Array*, int, pair<int, int>>> &ruleForShadow,
                                       const int dimN, 
                                       const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                                       const vector<pair<string, pair<int, int>>> &parallelOnRule)
{
    if (ruleForShadow.size() <= dimN)
        return false;

    if (get<0>(ruleForShadow[dimN]) == NULL)
        return true;

    //check for distributed in declaration or in redistr. rules
    const tuple<DIST::Array*, int, pair<int, int>> &toCheck = ruleForShadow[dimN];
    const int dimInTepml = get<1>(toCheck);

    for (auto &templ : distribution)
    {
        if (templ.first == get<0>(toCheck))
        {            
            if (templ.second->distRule[dimInTepml] == NONE)
                return true;
        }
    }

    //check for distributed in loop
    if (dimInTepml >= 0 && dimInTepml < parallelOnRule.size())
        if (parallelOnRule[dimInTepml].first == "*")
            return true;

    return false;
}

vector<tuple<DIST::Array*, int, pair<int, int>>> 
    getAlignRuleWithTemplate(DIST::Array *array, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                             DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays,
                             const int regionId)
{
    vector<tuple<DIST::Array*, int, pair<int, int>>> retVal;

    set<DIST::Array*> realRefs;
    getRealArrayRefs(array, array, realRefs, arrayLinksByFuncCalls);

    vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> allRuleForShadow(realRefs.size());
    int idx = 0;
    for (auto &array : realRefs)
        reducedG.GetAlignRuleWithTemplate(array, allArrays, allRuleForShadow[idx++], regionId);

    if (realRefs.size() == 1)
        retVal = allRuleForShadow[0];
    else
    {
        bool eq = isAllRulesEqual(allRuleForShadow);
        if (eq == false)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        else
            retVal = allRuleForShadow[0];
    }

    return retVal;
}

static inline string calculateShifts(DIST::GraphCSR<int, double, attrType> &reducedG,
                                     const DIST::Arrays<int> &allArrays,
                                     DIST::Array *arrayRef, DIST::Array *calcForArray,
                                     const pair<pair<string, string>, vector<pair<int, int>>> &coeffs,
                                     vector<pair<int, int>> &shifts,
                                     vector<map<pair<int, int>, int>> &shiftsByAccess,
                                     const vector<pair<string, pair<int, int>>> parallelOnRule,
                                     const map<DIST::Array*, pair<vector<ArrayOp>, vector<bool>>> &readOps, const bool isAcross,
                                     const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                                     const int regionId,
                                     const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    string out = "";

    vector<tuple<DIST::Array*, int, pair<int, int>>> ruleForOn =
        getAlignRuleWithTemplate(arrayRef, arrayLinksByFuncCalls, reducedG, allArrays, regionId);    

    vector<tuple<DIST::Array*, int, pair<int, int>>> ruleForShadow = 
        getAlignRuleWithTemplate(calcForArray, arrayLinksByFuncCalls, reducedG, allArrays, regionId);
        
    const pair<vector<ArrayOp>, vector<bool>> *currReadOp = NULL;
    auto readIt = readOps.find(calcForArray);
    if (readIt != readOps.end())
        currReadOp = &(readIt->second);
        
    findAndReplaceDimentions(ruleForOn, allArrays);
    findAndReplaceDimentions(ruleForShadow, allArrays);
    
    const int len = (int)coeffs.second.size();
    vector<pair<int, int>> shift(len);
        
    bool allZero = true;
    for (int k = 0; k < len; ++k)
    {
        shiftsByAccess.push_back(map<pair<int, int>, int>());
        shift[k].first = shift[k].second = 0;

        if (k != 0)
            out += ",";
        char buf[256];

        // calculate correct shifts from readOp info
        if (currReadOp)
        {
            // no unrecognized read operations
            if (currReadOp->second[k] == false)
            {
                if (get<0>(ruleForShadow[k]) != NULL)
                {
                    const pair<int, int> currRuleShadow = get<2>(ruleForShadow[k]);

                    pair<int, pair<int, int>> currRuleOn;
                    int err = findRule(get<1>(ruleForShadow[k]), ruleForOn, currRuleOn);
                    if (err == 0)
                    {
                        const pair<int, int> loopRule = DIST::Fx(parallelOnRule[currRuleOn.first].second, currRuleOn.second);

                        if (loopRule.first != 0)
                        {
                            int minShift = 9999999;
                            int maxShift = -9999999;

                            for (auto &coefs : currReadOp->first[k].coefficients)
                            {
                                auto currAccess = coefs.first;
                                auto result = DIST::Fx(currAccess, currRuleShadow);

                                if (result.first == loopRule.first)
                                {
                                    const int currShift = result.second - loopRule.second;
                                    minShift = std::min(minShift, currShift);
                                    maxShift = std::max(maxShift, currShift);

                                    auto itFound = shiftsByAccess[k].find(currAccess);
                                    if (itFound == shiftsByAccess[k].end())
                                        itFound = shiftsByAccess[k].insert(itFound, make_pair(currAccess, currShift));
                                }
                            }

                            // inconsistent -> may be remote will add later...
                            // or SINGLE position
                            if (minShift == 9999999 && maxShift == -9999999)
                                minShift = maxShift = 0;

                            if (minShift == maxShift)
                            {
                                if (minShift == 0)
                                {
                                    if (parallelOnRule[currRuleOn.first].first != "SINGLE")
                                    {
                                        shift[k].first = -coeffs.second[k].first;
                                        shift[k].second = -coeffs.second[k].second;
                                    }
                                }
                                else
                                {
                                    shift[k].first = -minShift;
                                    shift[k].second = minShift;

                                    if (shift[k].first > 0 && shift[k].second < 0)
                                        shift[k].second = 0;
                                    else if (shift[k].first < 0 && shift[k].second > 0)
                                        shift[k].first = 0;

                                    shift[k].first -= coeffs.second[k].first;
                                    shift[k].second -= coeffs.second[k].second;
                                }
                            }
                            else if (currReadOp->first[k].coefficients.size() > 0)
                            {
                                if (minShift > 0 && maxShift > 0)
                                {
                                    shift[k].first = 0;
                                    shift[k].second = std::abs(maxShift) - coeffs.second[k].second;
                                }
                                else if (minShift < 0 && maxShift < 0)
                                {
                                    shift[k].first = std::abs(minShift) - coeffs.second[k].first;
                                    shift[k].second = 0;
                                }
                                else
                                {
                                    shift[k].first = std::abs(minShift) - coeffs.second[k].first;
                                    shift[k].second = std::abs(maxShift) - coeffs.second[k].second;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (coeffs.second[k].first + shift[k].first < 0)
            shift[k].first = -coeffs.second[k].first;

        if (coeffs.second[k].second + shift[k].second < 0)
            shift[k].second = -coeffs.second[k].second;

        if (isAcross)
        {
            if (coeffs.second[k] == make_pair(0, 0))
                shift[k] = make_pair(0, 0);
        }
        else if (isNonDistributedDim(ruleForOn, ruleForShadow, k, distribution, parallelOnRule))
        {
            shift[k].first = -coeffs.second[k].first;
            shift[k].second = -coeffs.second[k].second;
            shiftsByAccess[k].clear();
        }

        sprintf(buf, "%d:%d", coeffs.second[k].first + shift[k].first, coeffs.second[k].second + shift[k].second);        
        shifts[k] = shift[k];

        if (coeffs.second[k].first + shift[k].first != 0 || coeffs.second[k].second + shift[k].second != 0)
            allZero = false;
        out += buf;
    }

    if (allZero)
        return "";
    else
        return out;
}

string ParallelDirective::genBounds(const vector<AlignRule> &alignRules,
                                    const pair<pair<string, string>, vector<pair<int, int>>> &shadowOp,
                                    vector<pair<int, int>> &shadowOpShift,
                                    DIST::GraphCSR<int, double, attrType> &reducedG,
                                    DIST::Arrays<int> &allArrays,
                                    const map<DIST::Array*, pair<vector<ArrayOp>, vector<bool>>> &readOps,
                                    const bool isAcross,
                                    const int regionId,
                                    const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                                    set<DIST::Array*> &arraysInAcross,
                                    vector<map<pair<int, int>, int>> &shiftsByAccess,
                                    const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls) const
{
    DIST::Array *shadowArray = allArrays.GetArrayByName(shadowOp.first.second);
    checkNull(shadowArray, convertFileName(__FILE__).c_str(), __LINE__);
    
    auto on_ext = on;
    //replace to template align ::on
    if (arrayRef->IsTemplate() == false)
    {
        vector<tuple<DIST::Array*, int, pair<int, int>>> ruleForRef =
            getAlignRuleWithTemplate(arrayRef, arrayLinksByFuncCalls, reducedG, allArrays, regionId);
        findAndReplaceDimentions(ruleForRef, allArrays);

        on_ext.clear();
        for (int i = 0; i < ruleForRef.size(); ++i)
        {
            if (get<0>(ruleForRef[i]))
            {
                on_ext.resize(get<0>(ruleForRef[i])->GetDimSize());
                break;
            }
        }
        if (on_ext.size() == 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        std::fill(on_ext.begin(), on_ext.end(), make_pair("*", make_pair(0, 0)));

        for (int i = 0; i < ruleForRef.size(); ++i)
            if (get<0>(ruleForRef[i]))
                on_ext[get<1>(ruleForRef[i])] = on[i];        
    }

    //replace single dim to key word 'SINGLE'
    for (int i = 0; i < on_ext.size(); ++i)
    {
        if (on_ext[i].first != "*")
        {
            if (std::find(parallel.begin(), parallel.end(), on_ext[i].first) == parallel.end())
                on_ext[i].first = "SINGLE";
        }
    }

    string ret = "";
    if (isAcross)
    {
        arraysInAcross.insert(shadowArray);
        ret = calculateShifts(reducedG, allArrays, arrayRef, shadowArray, shadowOp, shadowOpShift, shiftsByAccess, on_ext, readOps, isAcross, distribution, regionId, arrayLinksByFuncCalls);
    }
    else
    {
        if (arraysInAcross.find(shadowArray) == arraysInAcross.end())
            ret = calculateShifts(reducedG, allArrays, arrayRef, shadowArray, shadowOp, shadowOpShift, shiftsByAccess, on_ext, readOps, isAcross, distribution, regionId, arrayLinksByFuncCalls);
    }

    return ret;
}

static void genVariants(const int dimNum, vector<dist> &currDist, std::vector<DistrVariant> &currdist)
{
    if (dimNum == 1)
    {
        DistrVariant var1(currDist);
        var1.distRule.push_back(dist::NONE);

        DistrVariant var2(currDist);
        var2.distRule.push_back(dist::BLOCK);

        currdist.push_back(var1);
        currdist.push_back(var2);
    }
    else
    {
        vector<dist> next(currDist);
        next.push_back(dist::NONE);
        genVariants(dimNum - 1, next, currdist);
        next.back() = dist::BLOCK;
        genVariants(dimNum - 1, next, currdist);
    }
}

void DataDirective::createDirstributionVariants(const vector<DIST::Array*> &arraysToDist)
{
    for (int i = 0; i < arraysToDist.size(); ++i)
    {
        std::vector<DistrVariant> currdist;
        vector<dist> currDist;
        genVariants(arraysToDist[i]->GetDimSize(), currDist, currdist);

        //deprecate by dims
        for (auto &variant : currdist)
        {
            for (int z = 0; z < arraysToDist[i]->GetDimSize(); ++z)
                if (arraysToDist[i]->IsDimDepracated(z) || !arraysToDist[i]->IsDimMapped(z))
                    variant.distRule[z] = dist::NONE;
        }
        distrRules.push_back(make_pair(arraysToDist[i], currdist));
    }
}

string DistrVariantBase::GenRuleBase() const
{
    string retVal = "";

    retVal += "(";
    for (int i = 0; i < distRule.size(); ++i)
    {
        if (distRule[i] == dist::NONE)
            retVal += "*";
        else if (distRule[i] == dist::BLOCK)
            retVal += "BLOCK";
        if (i != distRule.size() - 1)
            retVal += ",";
    }
    retVal += ")";
    return retVal;
}

vector<string> DataDirective::GenRule(const vector<int> &rules) const
{
    vector<string> retVal;
    if (distrRules.size() < rules.size())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    for (int i = 0; i < rules.size(); ++i)
    {
        if (rules[i] < distrRules[i].second.size())
        {
            string tmp = distrRules[i].first->GetShortName();
            tmp += distrRules[i].second[rules[i]].GenRuleBase();
            retVal.push_back(tmp);
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    return retVal;
}

vector<vector<dist>> DataDirective::GenRule(const vector<int> &rules, int) const
{
    vector<vector<dist>> retVal;
    if (distrRules.size() < rules.size())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    for (int i = 0; i < rules.size(); ++i)
    {
        if (rules[i] < distrRules[i].second.size())
            retVal.push_back(distrRules[i].second[rules[i]].distRule);
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    return retVal;
}

vector<string> DataDirective::GenAlignsRules() const
{
    vector<string> retVal;
    for (int i = 0; i < alignRules.size(); ++i)
        retVal.push_back(alignRules[i].GenRuleBase());
    return retVal;
}

string AlignRuleBase::GenRuleBase() const
{
    string retVal = "";
    retVal += "ALIGN " + alignArray->GetShortName() + "(";
    for (int i = 0; i < alignRule.size(); ++i)
    {
        retVal += genStringExpr(alignNames[i], alignRule[i]);
        if (i != alignRule.size() - 1)
            retVal += ",";
    }

    retVal += ") WITH " + alignWith->GetShortName() + "(";
    vector<string> alignEachDim(alignWith->GetDimSize());
    for (int i = 0; i < alignWith->GetDimSize(); ++i)
        alignEachDim[i] = "*";

    for (int i = 0; i < alignRuleWith.size(); ++i)
    {
        if (alignRuleWith[i].first != -1)
            alignEachDim[alignRuleWith[i].first] = genStringExpr(alignNames[i], alignRuleWith[i].second);
    }

    for (int i = 0; i < alignWith->GetDimSize(); ++i)
    {
        retVal += alignEachDim[i];
        if (i != alignWith->GetDimSize() - 1)
            retVal += ",";
    }
    retVal += ")";

    return retVal;
}

string AlignRuleBase::toString()
{
    string retVal = "";

    if (alignArray)
        retVal += " " + std::to_string((long long)alignArray);
    else
        retVal += " -1";

    if (alignWith)
        retVal += " " + std::to_string((long long)alignWith);
    else
        retVal += " -1";

    retVal += " " + std::to_string(alignRule.size());
    for (int i = 0; i < alignRule.size(); ++i)
        retVal += " " + std::to_string(alignRule[i].first) + " " + std::to_string(alignRule[i].second);

    retVal += " " + std::to_string(alignRuleWith.size());
    for (int i = 0; i < alignRuleWith.size(); ++i)
        retVal += " " + std::to_string(alignRuleWith[i].first)
        + " " + std::to_string(alignRuleWith[i].second.first)
        + " " + std::to_string(alignRuleWith[i].second.second);

    return retVal;
}

pair<string, string> convertDigitToPositive(const int digit)
{
    char buf[16];
    string sign = " + ";
    if (digit < 0)
    {
        sign = " - ";
        int val = -digit;
        sprintf(buf, "%d", val);
    }
    else
        sprintf(buf, "%d", digit);

    return make_pair(sign, buf);
}

string genStringExpr(const string &letter, const pair<int, int> expr)
{
    string retVal = "";
    if (expr.first == 0 && expr.second == 0)
        retVal = "*";
    else if (expr.second == 0)
    {
        if (expr.first == 1)
            retVal = letter;
        else
        {
            pair<string, string> digit2 = convertDigitToPositive(expr.first);
            if (digit2.first == " - ")
                digit2.second = "(-" + digit2.second + ")";
            retVal = digit2.second + string(" * ") + letter;
        }
    }
    else
    {
        pair<string, string> digit1 = convertDigitToPositive(expr.second);
        if (expr.first == 1)
            retVal = letter + digit1.first + digit1.second;
        else
        {
            pair<string, string> digit2 = convertDigitToPositive(expr.first);
            if (digit2.first == " - ")
                digit2.second = "(-" + digit2.second + ")";
            retVal = digit2.second + string(" * ") + letter + digit1.first + digit1.second;
        }
    }
    return retVal;
}

const std::vector<std::string> AlignRuleBase::alignNames = { "iEX1", "iEX2", "iEX3", "iEX4", "iEX5", "iEX6", "iEX7" };