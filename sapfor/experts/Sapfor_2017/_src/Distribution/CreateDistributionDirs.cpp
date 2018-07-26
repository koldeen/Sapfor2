#include "../Utils/leak_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <map>

#include "Distribution.h"
#include "GraphCSR.h"
#include "Arrays.h"

#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../GraphLoop/graph_loops.h"

using std::vector;
using std::set;
using std::string;
using std::get;
using std::make_pair;
using std::map;
using std::pair;
using std::tuple;

static set<string> arraysWithErrors;
static void checkDimsSizeOfArrays(const DIST::Arrays<int> &allArrays, map<string, vector<Messages>> &allMessages,
                                  const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    const set<DIST::Array*> &arraysBase = allArrays.GetArrays();
    set<DIST::Array*> arrays;

    for (auto &array : arraysBase)
        getRealArrayRefs(array, array, arrays, arrayLinksByFuncCalls);
        
    bool ok = true;
    for (auto &array : arrays)
    {
        const vector<pair<int, int>> &sizes = array->GetSizes();
        for (int k = 0; k < sizes.size(); ++k)
        {
            if (sizes[k].first == -1 && sizes[k].second == -1)
            {
                if (arraysWithErrors.find(array->GetShortName()) == arraysWithErrors.end())
                {
                    auto declPlaces = array->GetDeclInfo();
                    for (auto &place : declPlaces)
                    {
                        string declF = place.first;
                        int declL = place.second;

                        char buf[256];
                        sprintf(buf, "More information is required about sizes of array '%s', decl line %d, decl file %s\n", array->GetShortName().c_str(), declL, declF.c_str());
                        addToGlobalBufferAndPrint(buf);
                        arraysWithErrors.insert(array->GetShortName());

                        vector<Messages> &currM = allMessages[declF];
                        sprintf(buf, "More information is required about sizes of array '%s'", array->GetShortName().c_str());
                        currM.push_back(Messages(ERROR, declL, buf, 1012));
                    }
                }
                ok = false;
            }
        }
    }

    if (!ok)
    {
        char buf[256];
        sprintf(buf, "Can not create distribution - unknown sizes\n");
        addToGlobalBufferAndPrint(buf);
        throw(-1);
    }
}

static int templateCount = 0;
static DIST::Array* createTemplate(DIST::Array *distArray, DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays)
{
    DIST::Array *templ = new DIST::Array(*distArray);
    templ->ChangeName("dvmh_temp" + std::to_string(templateCount++));
    templ->SetId(0);
    templ->SetTemplateFlag(true);

    vector<pair<int, int>> initTemplSize(distArray->GetDimSize());
    for (int i = 0; i < distArray->GetDimSize(); ++i)
        initTemplSize[i] = make_pair((int)INT_MAX, (int)INT_MIN);
    templ->SetSizes(initTemplSize);

    for (int i = 0; i < templ->GetDimSize(); ++i)
    {
        int vert = -1;
        const int err = allArrays.GetVertNumber(distArray, i, vert);
        if (err != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        pair<DIST::Array*, int> result = make_pair(distArray, i);
        set<int> wasDone;
        reducedG.FindLinkWithMaxDim(vert, allArrays, result, wasDone);
        if (result.first != distArray)
            templ->ExtendDimSize(i, result.first->GetSizes()[result.second]);

        AddArrayAccess(reducedG, allArrays, templ, result.first, make_pair(i, result.second), 1.0, make_pair(make_pair(1, 0), make_pair(1, 0)), RR_link);
    }

    return templ;
}

static DIST::Array* GetArrayWithMaximumDim(const vector<DIST::Array*> &arrays)
{
    int maxDimSize = -1;
    DIST::Array *retVal = NULL;

    for (int i = 0; i < arrays.size(); ++i)
    {
        DIST::Array *tmp = arrays[i];
        if (maxDimSize < tmp->GetDimSize())
        {
            maxDimSize = tmp->GetDimSize();
            retVal = tmp;
        }
        else if (maxDimSize == tmp->GetDimSize())
        {
            const vector<pair<int, int>> &size1 = retVal->GetSizes();
            const vector<pair<int, int>> &size2 = tmp->GetSizes();
            bool ifGT = true;
            for (int k = 0; k < size1.size(); ++k)
                if ((size1[k].second - size1[k].first) + 1 >(size2[k].second - size2[k].first) + 1)
                    ifGT = false;

            if (ifGT)
                retVal = tmp;
        }
    }
    return retVal;
}

static void convertTrees(const map<DIST::Array*, int> &treesIn, map<int, vector<DIST::Array*>> &treesOut,
                         const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    for (auto it = treesIn.begin(); it != treesIn.end(); ++it)
    {
        auto foundIt = treesOut.find(it->second);
        if (foundIt == treesOut.end())
            foundIt = treesOut.insert(foundIt, make_pair(it->second, vector<DIST::Array*>()));

        set<DIST::Array*> realRefs;
        getRealArrayRefs(it->first, it->first, realRefs, arrayLinksByFuncCalls);
        for (auto &array : realRefs)
            foundIt->second.push_back(array);
    }
}

static bool ArraySortFunc(DIST::Array *i, DIST::Array *j) { return (i->GetName() < j->GetName()); }

void createDistributionDirs(DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays, DataDirective &dataDirectives, map<string, vector<Messages>> &allMessages,
                            const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    checkDimsSizeOfArrays(allArrays, allMessages, arrayLinksByFuncCalls);

    map<DIST::Array*, int> trees;
    map<int, vector<DIST::Array*>> convTrees;

    int countTrees = reducedG.FindAllArraysTrees(trees, allArrays);
    //create one tree for all array that not found
    bool hasTemplates = false;
    for (auto &array : allArrays.GetArrays())
    {
        set<DIST::Array*> realRefs;
        getRealArrayRefs(array, array, realRefs, arrayLinksByFuncCalls);

        for (auto &realArray : realRefs)
        {
            hasTemplates = hasTemplates || realArray->isTemplate();
            auto it = trees.find(realArray);
            if (it == trees.end())
                trees.insert(it, make_pair(realArray, ++countTrees));
        }
    }

    vector<DIST::Array*> arraysToDist;
    if (hasTemplates == false)
    {
        convertTrees(trees, convTrees, arrayLinksByFuncCalls);
        for (auto i = convTrees.begin(); i != convTrees.end(); ++i)
        {
            std::sort(i->second.begin(), i->second.end(), ArraySortFunc);
            DIST::Array *distrArray = GetArrayWithMaximumDim(i->second);
            checkNull(distrArray, convertFileName(__FILE__).c_str(), __LINE__);

            DIST::Array *templ = createTemplate(distrArray, reducedG, allArrays);
            checkNull(templ, convertFileName(__FILE__).c_str(), __LINE__);
            arraysToDist.push_back(templ);
        }
    }
    else
    {
        for (auto &array : allArrays.GetArrays())
        {
            set<DIST::Array*> realRefs;
            getRealArrayRefs(array, array, realRefs, arrayLinksByFuncCalls);

            for (auto &realArray : realRefs)
            {
                if (realArray->isTemplate())
                    arraysToDist.push_back(realArray);
            }
        }
    }

    dataDirectives.createDirstributionVariants(arraysToDist);
}


static void createNewAlignRule(DIST::Array *alignArray, DIST::Arrays<int> &allArrays,
                               vector<tuple<DIST::Array*, int, pair<int, int>>> &rules,
                               DataDirective &dataDirectives)
{
    DIST::Array *alignWith = NULL;
    bool hasFreeDims = false;
    for (int i = 0; i < rules.size(); ++i)
    {
        if (alignWith == NULL && get<0>(rules[i]) != NULL)
            alignWith = get<0>(rules[i]);
        else if (alignWith != get<0>(rules[i]) && get<0>(rules[i]) != NULL)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (get<0>(rules[i]) == NULL)
            hasFreeDims = true;
    }

    //TODO:
    if (alignWith == NULL)
        __spf_print(1, "can not find align rules for array '%s' (full name '%s')\n", alignArray->GetShortName().c_str(), alignArray->GetName().c_str());
    checkNull(alignWith, convertFileName(__FILE__).c_str(), __LINE__);

    if (hasFreeDims)
    {
        set<int> usedVertDims;
        vector<int> allInAlign;
        allArrays.GetAllVertNumber(alignWith, allInAlign);
        int countOfFree = 0;
        for (int i = 0; i < rules.size(); ++i)
        {
            if (get<0>(rules[i]) != NULL)
                usedVertDims.insert(get<1>(rules[i]));
            else
                countOfFree++;
        }

        for (int i = 0; i < allInAlign.size(); ++i)
        {
            if (usedVertDims.find(allInAlign[i]) != usedVertDims.end())
            {
                allInAlign.erase(allInAlign.begin() + i);
                i--;
            }
        }

        if (allInAlign.size() < countOfFree)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        else
        {
            int k = 0;
            for (int i = 0; i < rules.size(); ++i)
            {
                if (get<0>(rules[i]) == NULL)
                {
                    rules[i] = make_tuple(alignWith, allInAlign[k], make_pair(0, 0));
                    k++;
                }
            }
        }
    }

    AlignRule newRule;
    newRule.alignArray = alignArray;
    newRule.alignWith = alignWith;

    for (int z = 0; z < alignArray->GetDimSize(); ++z)
    {
        newRule.alignRule.push_back(make_pair(1, 0));

        int alignToDim = -1;
        int err = allArrays.GetDimNumber(alignWith, get<1>(rules[z]), alignToDim);
        if (err != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        
        newRule.alignRuleWith.push_back(make_pair(alignToDim, get<2>(rules[z])));
        if (get<2>(rules[z]).first == 0 && get<2>(rules[z]).second == 0)
            continue;

        //correct template sizes
        const pair<int, int> &rule = get<2>(rules[z]);

        if (alignWith->GetShortName().find("dvmh") != string::npos)
        {
            pair<int, int> oldSizes = alignArray->GetSizes()[z];

            oldSizes.first = oldSizes.first * rule.first + rule.second;
            oldSizes.second = oldSizes.second * rule.first + rule.second;
            alignWith->ExtendDimSize(alignToDim, oldSizes);
        }
    }
    dataDirectives.alignRules.push_back(newRule);
}

static string printRule(const vector<tuple<DIST::Array*, int, pair<int, int>>> &rule)
{
    string print = "";
    for (auto &elem : rule)
        print += "(" + std::to_string(get<2>(elem).first) + "," + std::to_string(get<2>(elem).second) + ")";
    return print;
}

typedef vector<vector<tuple<DIST::Array*, int, attrType>>> AssignType;
int createAlignDirs(DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays, DataDirective &dataDirectives, 
                    const int regionId, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    set<DIST::Array*> distArrays;
    const set<DIST::Array*> &arrays = allArrays.GetArrays();

    if (dataDirectives.distrRules.size() == 0)
    {
        for (auto &array : arrays)
            if (array->isTemplate())
                distArrays.insert(array);

        if (distArrays.size() == 0)
            return 1;
    }
    else
    {
        for (int i = 0; i < dataDirectives.distrRules.size(); ++i)
            distArrays.insert(dataDirectives.distrRules[i].first);
    }

    set<pair<DIST::Array*, vector<vector<tuple<DIST::Array*, int, pair<int, int>>>>>> manyDistrRules;

    for (auto &array : arrays)
    {        
        if (distArrays.find((array)) == distArrays.end())
        {
            set<DIST::Array*> realArrayRefs;
            getRealArrayRefs(array, array, realArrayRefs, arrayLinksByFuncCalls);

            vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> rules(realArrayRefs.size());

            int i = 0;
            bool allNonDistr = true;
            bool partlyNonDistr = false;
            for (auto &arrays : realArrayRefs)
            {
                reducedG.GetAlignRuleWithTemplate(arrays, allArrays, rules[i], regionId);
                bool nonDistr = arrays->GetNonDistributeFlag();
                allNonDistr = allNonDistr && nonDistr;
                partlyNonDistr = partlyNonDistr || nonDistr;
                ++i;
            }

            if (allNonDistr)
                continue;
            if (partlyNonDistr)
            {
                __spf_print(1, "detected distributed and non distributed array links by function's calls for array %s\n", array->GetName().c_str());
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            if (isAllRulesEqual(rules))
                createNewAlignRule(array, allArrays, rules[0], dataDirectives);
            else
                manyDistrRules.insert(make_pair(array, rules));
        }
    }
    
    if (manyDistrRules.size() > 0)
    {
        for (auto &array : manyDistrRules)
        {
            __spf_print(1, "diferent align rules for array %s was found\n", array.first->GetName().c_str());
            for (auto &rule : array.second)
                __spf_print(1, "  -> %s\n", printRule(rule).c_str());
        }
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    return 0;
}