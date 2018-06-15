#include "../leak_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <string>
#include <algorithm>

#include "DvmhDirective.h"
#include "../errors.h"
#include "../transform.h"

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

ParallelDirective* operator+(const ParallelDirective &left, const ParallelDirective &right)
{
    const ParallelDirective *first = &left;
    const ParallelDirective *second = &right;

    ParallelDirective *result = NULL;
    assert(first);
    assert(second);

    if (first->arrayRef == second->arrayRef)
    {
        assert(first->on.size() == second->on.size());

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

        for (int i = 0; i < (int)first->on.size(); ++i)
        {
            bool firstStar = first->on[i].first == "*";
            bool secondStar = second->on[i].first == "*";
            if (firstStar && secondStar)
                result->on[i].first = "*";
            else if (firstStar)
                result->on[i] = second->on[i];
            else
                result->on[i] = first->on[i];
        }

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
        return false;

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
        if (parallelOnRule[get<1>(ruleForOn[dimInTepml])].first == "*")
            return true;

    return false;
}

static inline void findDimentions(vector<tuple<DIST::Array*, int, pair<int, int>>> &rule, const DIST::Arrays<int> &allArrays)
{
    for (int i = 0; i < rule.size(); ++i)
    {
        if (get<0>(rule[i]) == NULL)
            continue;
        int alignTo = -1;
        int ok = allArrays.GetDimNumber(get<0>(rule[i]), (get<1>(rule[i])), alignTo);
        if (ok != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        (get<1>(rule[i])) = alignTo;
    }
}

static inline string calculateShifts(DIST::GraphCSR<int, double, attrType> &reducedG,
                                     const DIST::Arrays<int> &allArrays,
                                     DIST::Array *arrayRef, DIST::Array *calcForArray,
                                     const pair<pair<string, string>, vector<pair<int, int>>> &coeffs,
                                     vector<pair<int, int>> &shifts,
                                     vector<map<pair<int, int>, int>> &shiftsByAccess,
                                     const vector<pair<string, pair<int, int>>> on,
                                     const map<DIST::Array*, pair<vector<ArrayOp>, vector<bool>>> &readOps, const bool isAcross,
                                     const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                                     const vector<pair<string, pair<int, int>>> &parallelOnRule,
                                     const int regionId)
{
    string out = "";

    vector<tuple<DIST::Array*, int, pair<int, int>>> ruleForOn;
    reducedG.GetAlignRuleWithTemplate(arrayRef, allArrays, ruleForOn, regionId);

    vector<tuple<DIST::Array*, int, pair<int, int>>> ruleForShadow;
    reducedG.GetAlignRuleWithTemplate(calcForArray, allArrays, ruleForShadow, regionId);
    
    const pair<vector<ArrayOp>, vector<bool>> *currReadOp = NULL;
    auto readIt = readOps.find(calcForArray);
    if (readIt != readOps.end())
        currReadOp = &(readIt->second);
        
    findDimentions(ruleForOn, allArrays);
    findDimentions(ruleForShadow, allArrays);
    
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
            if (currReadOp->second[k] == false)
            {
                if (get<0>(ruleForShadow[k]) != NULL)
                {
                    const pair<int, int> currRuleShadow = get<2>(ruleForShadow[k]);

                    pair<int, pair<int, int>> currRuleOn;
                    int err = findRule(get<1>(ruleForShadow[k]), ruleForOn, currRuleOn);
                    if (err == 0)
                    {
                        const pair<int, int> loopRule = on[currRuleOn.first].second;

                        if (loopRule.first != 0)
                        {
                            int minShift = 9999999;
                            int maxShift = -9999999;

                            for (int z = 0; z < currReadOp->first[k].coefficients.size(); ++z)
                            {
                                auto currAccess = currReadOp->first[k].coefficients[z];
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

                            if (minShift == maxShift)
                            {
                                if (minShift == 0)
                                {
                                    shift[k].first = -coeffs.second[k].first;
                                    shift[k].second = -coeffs.second[k].second;
                                }
                                else
                                {
                                    shift[k].first = -minShift;
                                    shift[k].second = minShift;

                                    if (shift[k].first > 0 && shift[k].second < 0)
                                        shift[k].second = 0;
                                    else if (shift[k].first < 0 && shift[k].second > 0)
                                        shift[k].first = 0;
                                }
                            }
                            else if (currReadOp->first[k].coefficients.size() > 0)
                            {
                                shift[k].first = std::abs(minShift) - coeffs.second[k].first;
                                shift[k].second = std::abs(maxShift) - coeffs.second[k].second;
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
            shift[k].first = 0;
            shift[k].second = 0;
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
                                    vector<map<pair<int, int>, int>> &shiftsByAccess) const
{
    DIST::Array *shadowArray = allArrays.GetArrayByName(shadowOp.first.second);
    checkNull(shadowArray, convertFileName(__FILE__).c_str(), __LINE__);
    
    string ret = "";
    if (isAcross)
    {
        arraysInAcross.insert(shadowArray);
        ret = calculateShifts(reducedG, allArrays, arrayRef, shadowArray, shadowOp, shadowOpShift, shiftsByAccess, on, readOps, isAcross, distribution, on, regionId);
    }
    else
    {
        if (arraysInAcross.find(shadowArray) == arraysInAcross.end())
            ret = calculateShifts(reducedG, allArrays, arrayRef, shadowArray, shadowOp, shadowOpShift, shiftsByAccess, on, readOps, isAcross, distribution, on, regionId);
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
        alignEachDim[alignRuleWith[i].first] = genStringExpr(alignNames[i], alignRuleWith[i].second);

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