#include "../Utils/leak_detector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <map>
#include <climits>

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
                        
                        std::wstring bufE, bufR;
                        __spf_printToLongBuf(bufE, L"More information is required about sizes of array '%s'", to_wstring(array->GetShortName()).c_str());
#ifdef _WIN32
                        __spf_printToLongBuf(bufR, R37, to_wstring(array->GetShortName()).c_str());
#endif
                        getObjectForFileFromMap(declF.c_str(), allMessages).push_back(Messages(ERROR, declL, bufR, bufE, 1012));
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

#define WITH_REMOVE 1
static int templateCount = 0;
static DIST::Array* createTemplate(DIST::Array *distArray, DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays)
{
    // find not connected dimentions and deprecate them 
    vector<int> vInGraph;
    int err = allArrays.GetAllVertNumber(distArray, vInGraph);
    if (err != 0)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (!distArray->IsLoopArray())
    {
        int countOfDepr = 0;
        for (int z = 0; z < vInGraph.size(); ++z)
        {
            int count = reducedG.CountOfConnectedForArray(vInGraph[z]);
            if (count <= 0)
                countOfDepr++;
        }

        if (countOfDepr == distArray->GetDimSize())
        {
            for (int z = 0; z < distArray->GetDimSize(); ++z)
            {
                if (!distArray->IsDimMapped(z))
                    distArray->DeprecateDimension(z);
            }
        }
        else
        {
            for (int z = 0; z < vInGraph.size(); ++z)
            {
                int count = reducedG.CountOfConnectedForArray(vInGraph[z]);
                if (count <= 0)
                    distArray->DeprecateDimension(z);
            }
        }
    }

    DIST::Array *templ = new DIST::Array(*distArray);
    templ->ChangeName("dvmh_temp" + std::to_string(templateCount++));
    templ->SetId(0);
    templ->SetTemplateFlag(true);

    if (distArray->IsLoopArray())
        for (int z = 0; z < templ->GetDimSize(); ++z)
            templ->SetMappedDim(z);

    vector<pair<int, int>> initTemplSize(distArray->GetDimSize());
    for (int i = 0; i < distArray->GetDimSize(); ++i)
        initTemplSize[i] = make_pair((int)INT_MAX, (int)INT_MIN);
    templ->SetSizes(initTemplSize, true);

    bool ifRemAll = false;
#if WITH_REMOVE
    ifRemAll = templ->RemoveUnpammedDims();
#endif
    for (int i = 0, templIdx = 0; i < distArray->GetDimSize(); ++i)
    {
        int vert = -1;
        const int err = allArrays.GetVertNumber(distArray, i, vert);
        if (err != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        pair<DIST::Array*, int> result = make_pair(distArray, i);
        set<int> wasDone;
        reducedG.FindLinkWithMaxDim(vert, allArrays, result, wasDone);

        if ((distArray->IsDimMapped(i) || distArray->IsLoopArray()) && !distArray->IsDimDepracated(i))
        {
            AddArrayAccess(reducedG, allArrays, templ, result.first, make_pair(templIdx, result.second), 1.0, make_pair(make_pair(1, 0), make_pair(1, 0)), RR_link);
            if (result.first != distArray)
                templ->ExtendDimSize(templIdx, result.first->GetSizes()[result.second]);
            templIdx++;
        }
#if !WITH_REMOVE
        else
            templ->ExtendDimSize(templIdx++, make_pair(1, 1));
#else
        else
        {
            if (ifRemAll)
            {
                AddArrayAccess(reducedG, allArrays, templ, result.first, make_pair(templIdx, result.second), 1.0, make_pair(make_pair(1, 0), make_pair(1, 0)), RR_link);
                templ->DeprecateDimension(i, false);
                if (result.first != distArray)
                    templ->ExtendDimSize(templIdx, result.first->GetSizes()[result.second]);
                templIdx++;
            }
        }
#endif
    }

    return templ;
}
#undef WITH_REMOVE

static vector<DIST::Array*> GetArrayWithMaximumDim(const vector<DIST::Array*> &arrays)
{
    int maxDimSize = -1;
    vector<DIST::Array*> retVal;

    for (int i = 0; i < arrays.size(); ++i)
    {
        DIST::Array *tmp = arrays[i];
        if (maxDimSize < tmp->GetDimSize())
        {
            maxDimSize = tmp->GetDimSize();
            retVal.clear();
            retVal.push_back(tmp);
        }
        else if (maxDimSize == tmp->GetDimSize())
        {
            const vector<pair<int, int>> &size1 = retVal.back()->GetSizes();
            const vector<pair<int, int>> &size2 = tmp->GetSizes();

            if (size1 == size2)
                retVal.push_back(tmp);
            else
            {
                bool ifGT = true;
                for (int k = 0; k < size1.size(); ++k)
                    if ((size1[k].second - size1[k].first) + 1 > (size2[k].second - size2[k].first) + 1)
                        ifGT = false;

                if (ifGT)
                {
                    retVal.clear();
                    retVal.push_back(tmp);
                }
            }
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

static DIST::Array* findBestInEqual(vector<DIST::Array*> &arrays, DIST::GraphCSR<int, double, attrType> &reducedG, DIST::Arrays<int> &allArrays)
{
    DIST::Array *retVal = NULL;
    vector<vector<attrType>> coefsByDims;
    for (auto &array : arrays)
    {
        vector<int> verts;
        int err = allArrays.GetAllVertNumber(array, verts);
        if (err != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        if (retVal == NULL)
        {
            retVal = array;
            for (auto &V : verts)
                coefsByDims.push_back(reducedG.GetAllAttributes(V));
        }
        else
        {
            vector<vector<attrType>> toCmp;
            for (auto &V : verts)
                toCmp.push_back(reducedG.GetAllAttributes(V));
            for (int z = 0; z < toCmp.size(); ++z)
            {
                if (toCmp[z].size() && coefsByDims[z].size())
                {
                    if (toCmp[z].back().first.first > coefsByDims[z].back().first.first)
                    {
                        coefsByDims = toCmp;
                        retVal = array;
                        break;
                    }
                }
            }
        }
    }

    return retVal;
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
            hasTemplates = hasTemplates || realArray->IsTemplate();
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
            vector<DIST::Array*> distrArrayV = GetArrayWithMaximumDim(i->second);
            if (distrArrayV.size() == 0)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            DIST::Array *distrArray = findBestInEqual(distrArrayV, reducedG, allArrays);

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
                if (realArray->IsTemplate())
                    arraysToDist.push_back(realArray);
            }
        }
    }

    if (arraysToDist.size())
        dataDirectives.createDirstributionVariants(arraysToDist);
}


static void createNewAlignRule(DIST::Array *alignArray, const DIST::Arrays<int> &allArrays,
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

        if (allInAlign.size() >= countOfFree)
        {
            int k = 0;
            for (int i = 0; i < rules.size(); ++i)
            {
                if (get<0>(rules[i]) == NULL || alignArray->IsDimDepracated(i))
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
                
        newRule.alignRuleWith.push_back(make_pair(alignToDim, get<2>(rules[z])));
        if (get<2>(rules[z]).first == 0 && get<2>(rules[z]).second == 0)
            continue;

        //correct template sizes
        const pair<int, int> &rule = get<2>(rules[z]);

        if (alignWith->GetShortName().find("dvmh") != string::npos)
        {
            pair<int, int> oldSizes = alignArray->GetSizes()[z];
            if (!(oldSizes.first == oldSizes.second && oldSizes.first == -1))
            {
                oldSizes.first = oldSizes.first * rule.first + rule.second;
                oldSizes.second = oldSizes.second * rule.first + rule.second;
                alignWith->ExtendDimSize(alignToDim, oldSizes);
            }
        }
    }
    dataDirectives.alignRules.push_back(newRule);
}

static string printRule(const vector<tuple<DIST::Array*, int, pair<int, int>>> &rule)
{
    string print = get<0>(rule[0])->GetShortName() + " : ";
    for (auto &elem : rule)
        print +=  "(" + std::to_string(get<2>(elem).first) + "," + std::to_string(get<2>(elem).second) + ")";
    return print;
}

typedef vector<vector<tuple<DIST::Array*, int, attrType>>> AssignType;
int createAlignDirs(DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays, DataDirective &dataDirectives, 
                    const int regionId, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls, map<string, vector<Messages>> &SPF_messages)
{
    set<DIST::Array*> distArrays;
    const set<DIST::Array*> &arrays = allArrays.GetArrays();

    if (dataDirectives.distrRules.size() == 0)
    {
        for (auto &array : arrays)
            if (array->IsTemplate())
                distArrays.insert(array);

        if (distArrays.size() == 0)
            return 1;
    }
    else
    {
        for (int i = 0; i < dataDirectives.distrRules.size(); ++i)
            distArrays.insert(dataDirectives.distrRules[i].first);
    }

    bool repeat = true;
    int countRep = 0;
    while (repeat)
    {
        ++countRep;
        repeat = false;
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
                    int err = reducedG.GetAlignRuleWithTemplate(arrays, allArrays, rules[i], regionId);
                    if (err == 101)
                    {
                        reducedG.cleanCacheLinks();
                        dataDirectives.alignRules.clear();
                        repeat = true;
                        break;
                    }
                    bool nonDistr = arrays->GetNonDistributeFlag();
                    allNonDistr = allNonDistr && nonDistr;
                    partlyNonDistr = partlyNonDistr || nonDistr;
                    ++i;
                }

                if (repeat)
                    break;

                if (allNonDistr)
                    continue;
                if (partlyNonDistr)
                {
                    __spf_print(1, "detected distributed and non distributed array links by function's calls for array %s\n", array->GetName().c_str());
                    auto allDecl = array->GetDeclInfo();
                    for (auto &decl : allDecl)
                    {
                        std::wstring bufE, bufR;
                        __spf_printToLongBuf(bufE, L"detected distributed and non distributed array links by function's calls for array '%s'\n", to_wstring(array->GetShortName()).c_str());
#ifdef _WIN32
                        __spf_printToLongBuf(bufR, R140, to_wstring(array->GetShortName()).c_str());
#endif
                        getObjectForFileFromMap(decl.first.c_str(), SPF_messages).push_back(Messages(ERROR, decl.second, bufR, bufE, 3020));
                    }
                    
                    for (auto &realR : realArrayRefs)
                    {
                        if (realR != array)
                        {
                            auto allDecl = realR->GetDeclInfo();
                            for (auto &decl : allDecl)
                            {
                                std::wstring bufE, bufR;
                                if (realR->GetNonDistributeFlag())
                                {
                                    __spf_printToLongBuf(bufR, L"detected non distributed array '%s'\n", to_wstring(realR->GetShortName()).c_str());
#ifdef _WIN32
                                    __spf_printToLongBuf(bufE, L"Обнаружен не распределяемый массив '%s', передаваемый в качестве параметра в процедуру\n", to_wstring(realR->GetShortName()).c_str());
#endif
                                }
                                else
                                {
                                    __spf_printToLongBuf(bufE, L"detected distributed array '%s'\n", to_wstring(realR->GetShortName()).c_str());
#ifdef _WIN32
                                    __spf_printToLongBuf(bufR, R141, to_wstring(realR->GetShortName()).c_str());
#endif
                                }
                                getObjectForFileFromMap(decl.first.c_str(), SPF_messages).push_back(Messages(ERROR, decl.second, bufR, bufE, 3020));
                            }
                        }
                    }
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                if (isAllRulesEqualWithoutArray(rules))
                    createNewAlignRule(array, allArrays, rules[0], dataDirectives);
                else
                    manyDistrRules.insert(make_pair(array, rules));
            }
        }

        if (countRep > 500)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (repeat)
            continue;

        if (manyDistrRules.size() > 0)
        {
            for (auto &array : manyDistrRules)
            {
                __spf_print(1, "different align rules for array %s was found\n", array.first->GetName().c_str());
                for (auto &rule : array.second)
                    __spf_print(1, "  -> %s\n", printRule(rule).c_str());

                std::wstring bufE, bufR;
                __spf_printToLongBuf(bufE, L"different align rules for array %s were found\n", to_wstring(array.first->GetShortName()).c_str());
#ifdef _WIN32
                __spf_printToLongBuf(bufR, R142, to_wstring(array.first->GetShortName()).c_str());
#endif
                for (auto &declPlace : array.first->GetDeclInfo())
                    getObjectForFileFromMap(declPlace.first.c_str(), SPF_messages).push_back(Messages(ERROR, declPlace.second, bufR, bufE, 3020));
            }
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
    return 0;
}