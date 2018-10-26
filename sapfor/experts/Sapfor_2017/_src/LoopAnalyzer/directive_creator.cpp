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

#include "../Utils/AstWrapper.h"

#define PRINT_DIR_RESULT 0
#define PRINT_PROF_INFO  1

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

struct MapToArray
{
public:
    MapToArray() : underAcross(false) { }

public:
    DIST::Array *arrayRef;
    int dimentionPos;
    int hasWrite;
    pair<int, int> mainAccess;
    bool underAcross;
};

static pair<pair<string, string>, vector<pair<int, int>>>* 
    findShadowArraysOrCreate(vector<pair<pair<string, string>, vector<pair<int, int>>>> &shadow, 
                             const vector<pair<pair<string, string>, vector<pair<int, int>>>> &across,
                             DIST::Array *symb)
{
    const string &arrayName = symb->GetShortName();

    bool existInAcross = false;
    for (int i = 0; i < across.size(); ++i)
    {
        if (across[i].first.first == arrayName)
        {
            return NULL;
            break;
        }
    }

    pair<pair<string, string>, vector<pair<int, int>>> *toAdd;
    bool cond = false;    
    for (int i = 0; i < shadow.size(); ++i)
    {
        if (shadow[i].first.first == arrayName)
        {
            toAdd = &shadow[i];
            cond = true;
            break;
        }
    }
    
    if (!cond)
    {
        shadow.push_back(make_pair(make_pair(arrayName, symb->GetName()), vector<pair<int, int>>()));
        toAdd = &shadow.back();
    }

    return toAdd;
}

static void addShadowFromAnalysis(ParallelDirective *dir, const map<DIST::Array*, const ArrayInfo*> &currAccesses)
{
    if (staticShadowAnalysis == 0)
        return;

    vector<pair<pair<string, string>, vector<pair<int, int>>>> &shadow = dir->shadowRenew;
    const vector<pair<pair<string, string>, vector<pair<int, int>>>> &across = dir->across;

    for (auto &access : currAccesses)
    {
        const int dimSize = access.first->GetDimSize();
        const ArrayInfo &currInfo = *(access.second);

        pair<pair<string, string>, vector<pair<int, int>>> *toAdd = NULL;
        
        bool needBreak = false;
        for (int idx = 0; idx < dimSize; ++idx)
        {
            for (int k = 0; k < currInfo.readOps[idx].coefficients.size(); ++k)
            {
                if (currInfo.readOps[idx].coefficients[k].second != 0)
                {
                    int left = 0, right = 0;
                    if (currInfo.readOps[idx].coefficients[k].second < 0)
                        left = -currInfo.readOps[idx].coefficients[k].second;
                    else
                        right = currInfo.readOps[idx].coefficients[k].second;

                    if (toAdd == NULL)
                    {
                        toAdd = findShadowArraysOrCreate(shadow, across, access.first);
                        if (toAdd == NULL)
                        {
                            needBreak = true;
                            break;
                        }
                    }
                    if (toAdd->second.size() < dimSize)
                    {
                        toAdd->second.resize(dimSize);
                        for (int z = 0; z < dimSize; ++z)
                            toAdd->second[z] = make_pair(0, 0);
                    }

                    toAdd->second[idx].first = std::max(toAdd->second[idx].first, left);
                    toAdd->second[idx].second = std::max(toAdd->second[idx].second, right);
                }
            }
            if (needBreak)
                break;
        }
    }
}

static LoopGraph* createDirectiveForLoop(LoopGraph *currentLoop, MapToArray &mainArray,
                                         map<int, LoopGraph*> &sortedLoopGraph, const set<DIST::Array*> &acrossOutArrays)
{
    const int pos = mainArray.dimentionPos;
    const pair<int, int> &mainAccess = mainArray.mainAccess;

    ParallelDirective *directive = new ParallelDirective();
#if __SPF
    directive->langType = LANG_F;
#else
    directive->langType = LANG_C;
#endif
    directive->line = currentLoop->lineNum;
    directive->col = 0;
    directive->file = currentLoop->fileName;
    
    fillInfoFromDirectives(currentLoop, directive);
    
    //remote from SHADOW all arrays from REMOTE
    for (auto it = directive->remoteAccess.begin(); it != directive->remoteAccess.end(); ++it)
    {
        string arrayN = it->first.first;
                
        for (int k = 0; k < directive->shadowRenew.size(); ++k)
        {
            if (directive->shadowRenew[k].first.first == arrayN)
            {
                directive->shadowRenew.erase(directive->shadowRenew.begin() + k);
                break;
            }
        }
    }

    directive->parallel.push_back(currentLoop->loop->symbol()->identifier()); 
    directive->arrayRef = mainArray.arrayRef;

    DIST::Array *tmp = mainArray.arrayRef;
    if (tmp != NULL)
    {
        for (int i = 0; i < tmp->GetDimSize(); ++i)
        {
            if (i == pos)
                directive->on.push_back(make_pair(currentLoop->loop->symbol()->identifier(), mainAccess));
            else
                directive->on.push_back(make_pair("*", make_pair(0, 0)));
        }
    }
         
    auto itFound = sortedLoopGraph.find(currentLoop->lineNum);
    if (itFound == sortedLoopGraph.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    itFound->second->directive = directive;
    for (auto it = itFound->second->readOpsArray.begin(); it != itFound->second->readOpsArray.end(); ++it)
    {
        string shortName = (*it)->GetName();
        string orignName = (*it)->GetShortName();
        pair<string, string> key = make_pair(orignName, shortName);
        bool found = false;
        for (int i = 0; i < directive->shadowRenew.size(); ++i)
        {
            if (directive->shadowRenew[i].first == key)
            {
                found = true;
                break;
            }
        }
                
        if (found == false)
        {
            for (int i = 0; i < directive->across.size(); ++i)
            {
                if (directive->across[i].first == key)
                {
                    found = true;
                    break;
                }
            }

            if (found == false)
            {
                directive->shadowRenew.push_back(make_pair(key, vector<pair<int, int>>()));

                const DIST::Array *arrayRef = (*it);
                for (int i = 0; i < arrayRef->GetDimSize(); ++i)
                    directive->shadowRenew.back().second.push_back(make_pair(0, 0));
            }
        }
    }

    if (itFound->second->directive)
        itFound->second->acrossOutAttribute.insert(acrossOutArrays.begin(), acrossOutArrays.end());
   
    return itFound->second;
}

static inline bool isUnderAcrossDir(const string &array, const vector<pair<pair<string, string>, vector<pair<int, int>>>> &acrossInfo)
{
    bool underAcrossDir = false;
    for (int i = 0; i < acrossInfo.size(); ++i)
    {
        if (acrossInfo[i].first.first == array)
        {
            underAcrossDir = true;
            break;
        }
    }

    return underAcrossDir;
}

static inline pair<int, int> getShadowsAcross(const string &array, const int pos, 
                                              const vector<pair<pair<string, string>, vector<pair<int, int>>>> &acrossInfo)
{
    pair<int, int> shadows = make_pair(0, 0);
    for (int i = 0; i < acrossInfo.size(); ++i)
    {
        if (acrossInfo[i].first.first == array)
        {
            shadows = acrossInfo[i].second[pos];
            break;
        }
    }

    return shadows;
}

static bool checkForConflict(const map<DIST::Array*, const ArrayInfo*> &currAccesses,
                             const LoopGraph *currentLoop,
                             map<DIST::Array*, pair<int, pair<int, int>>> &arrayWriteAcc,
                             const vector<pair<pair<string, string>, vector<pair<int, int>>>> &acrossInfo,
                             set<DIST::Array*> &acrossOutArrays)
{
    bool hasConflict = false;
    
    for (auto &itArray : currAccesses)
    {
        const ArrayInfo &currInfo = *(itArray.second);
        const string &arrayName = itArray.first->GetShortName();


        int countOfWriteDims = 0;
        int lastPosWrite = -1;
        for (int i = 0; i < currInfo.dimSize; ++i)
        {
            if (currInfo.writeOps[i].coefficients.size() != 0)
            {
                lastPosWrite = i;
                countOfWriteDims++;
            }
        }

        if (countOfWriteDims > 1)
        {
            __spf_print(PRINT_DIR_RESULT, "    array %s was found for loop on line %d\n", arrayName.c_str(), currentLoop->lineNum);
            __spf_print(PRINT_DIR_RESULT, "    conflicted writes\n");
            hasConflict = true;
            lastPosWrite = -1;
        }

        if (lastPosWrite == -1)
        {
            __spf_print(PRINT_DIR_RESULT, "   no regular writes for array %s on loop\n", arrayName.c_str());
            continue;
        }
        else
        {
            set<pair<int, int>> uniqAccess;
            const ArrayOp &acceses = currInfo.writeOps[lastPosWrite];
            for (int k = 0; k < (int)acceses.coefficients.size(); ++k)
                uniqAccess.insert(make_pair(acceses.coefficients[k].first, acceses.coefficients[k].second));

            bool underAcross = isUnderAcrossDir(arrayName.c_str(), acrossInfo);
            if (uniqAccess.size() > 1)
            {
                if (!underAcross)
                {
                    __spf_print(PRINT_DIR_RESULT, "    conflicted writes\n");
                    hasConflict = true;
                    continue;
                }
                else
                {
                    int loopStep = currentLoop->stepVal;

                    if (loopStep == 0)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    int shiftMin, shiftMax;
                    bool init = false;
                    for (auto &access : uniqAccess)
                    {
                        if (!init)
                        {
                            shiftMin = shiftMax = access.second;
                            init = true;
                        }
                        else
                        {
                            shiftMin = std::min(shiftMin, access.second);
                            shiftMax = std::max(shiftMax, access.second);
                        }
                    }

                    pair<int, int> needed;// = (loopStep > 0) ? make_pair(0, shiftMin) : make_pair(0, shiftMax);
                    pair<int, int> shiftSize = getShadowsAcross(arrayName.c_str(), lastPosWrite, acrossInfo);
                    if (loopStep > 0)
                        needed.second = shiftMax - shiftSize.second * loopStep;
                    else
                        needed.second = shiftMin - shiftSize.first * loopStep;

                    //TODO: check
                    for (auto &access : uniqAccess)
                    {
                        if (access.second == needed.second)
                        {
                            needed.first = access.first;
                            break;
                        }
                    }
                    if (needed.first == 0)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    arrayWriteAcc.insert(make_pair(itArray.first, make_pair(lastPosWrite, needed)));
                    acrossOutArrays.insert(itArray.first);
                }
            }
            else
                arrayWriteAcc.insert(make_pair(itArray.first, make_pair(lastPosWrite, *uniqAccess.begin())));
        }

        int countOfReadDims = 0;
        int lastPosRead = -1;
        for (int i = 0; i < currInfo.dimSize; ++i)
        {
            if (currInfo.readOps[i].coefficients.size() != 0)
            {
                lastPosRead = i;
                countOfReadDims++;
            }
        }

        if (countOfReadDims > 1 && lastPosRead != lastPosWrite && !isUnderAcrossDir(arrayName, acrossInfo))
        {
            __spf_print(PRINT_DIR_RESULT, "    dependencies between read and write\n");
            hasConflict = true;
            continue;
        }
    }
    return hasConflict;
}

static void findRegularReads(const ArrayInfo &currInfo, DIST::Array *arrayUniqKey, const int i, int &maxDim, MapToArray &mainArray)
{
    map<pair<int, int>, int> countAcc;
    for (int k = 0; k < (int)currInfo.readOps[i].coefficients.size(); ++k)
    {
        auto it = countAcc.find(currInfo.readOps[i].coefficients[k]);
        if (it == countAcc.end())
            countAcc.insert(it, make_pair(currInfo.readOps[i].coefficients[k], 1));
        else
            it->second++;
    }

    int maxVal = 0;
    int maxPos = 0;
    int k = 0;
    for (auto it = countAcc.begin(); it != countAcc.end(); ++it, ++k)
    {
        if (maxVal < it->second)
        {
            maxVal = it->second;
            maxPos = k;
        }
    }

    bool needToUpdate = true;
    if (maxDim == -1)
        maxDim = arrayUniqKey->GetDimSize();
    else
    {
        const int currDim = arrayUniqKey->GetDimSize();
        if (maxDim < currDim)
            maxDim = currDim;
        else
            needToUpdate = false;
    }

    if (needToUpdate)
    {
        mainArray.arrayRef = arrayUniqKey;
        mainArray.dimentionPos = i;
        k = 0;
        for (auto it = countAcc.begin(); it != countAcc.end(); ++it, ++k)
        {
            if (k == maxPos)
            {
                mainArray.mainAccess = it->first;
                break;
            }
        }
    }
}

static bool checkForDependence(const map<DIST::Array*, const ArrayInfo*> &currAccesses, MapToArray &mainArray)
{
    bool hasConflict = false;

    int maxDim = -1;
    for (auto &itArray : currAccesses)
    {
        const ArrayInfo &currInfo = *(itArray.second);
        for (int i = 0; i < currInfo.dimSize; ++i)
        {
            if (currInfo.readOps[i].coefficients.size() != 0)
            {
                // no regular writes on loop, try to find regular reads
                if (!mainArray.hasWrite)
                    findRegularReads(currInfo, itArray.first, i, maxDim, mainArray);
            }
        }
    }
    return hasConflict;
}

static void fillArrays(LoopGraph *loopInfo, set<string> &uniqNames)
{
    vector<pair<pair<string, string>, vector<pair<int, int>>>> acrossInfo;
    fillAcrossInfoFromDirectives(loopInfo, acrossInfo);

    for (int i = 0; i < acrossInfo.size(); ++i)
        uniqNames.insert(acrossInfo[i].first.second);
}

static void fillArraysWithAcrossStatus(LoopGraph *loopInfo, set<string> &uniqNames)
{
    fillArrays(loopInfo, uniqNames);

    LoopGraph *curr = loopInfo;
    while (curr->perfectLoop > 1)
    {
        curr = curr->children[0];
        fillArrays(curr, uniqNames);
    }

    LoopGraph *prev = loopInfo->parent;
    while (prev && prev->perfectLoop > 1)
    {
        fillArrays(prev, uniqNames);
        prev = prev->parent;
    }   
}

void createParallelDirectives(const map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> &loopInfos,
                              std::vector<ParallelRegion*> regions, map<int, LoopGraph*> &sortedLoopGraph,
                              const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls,
                              vector<Messages> &messages)
{
    for (auto &loopInfo : loopInfos)
    {
        ParallelRegion *currReg = getRegionByLine(regions, loopInfo.first->fileName.c_str(), loopInfo.first->lineNum);
        if (currReg == NULL || loopInfo.first->userDvmDirective != NULL)
        {
            __spf_print(PRINT_PROF_INFO, "Skip loop on file %s and line %d\n", loopInfo.first->fileName.c_str(), loopInfo.first->lineNum);
            continue;
        }

        const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();
        DIST::GraphCSR<int, double, attrType> &reducedG = currReg->GetReducedGraphToModify();

        vector<pair<pair<string, string>, vector<pair<int, int>>>> acrossInfo;
        fillAcrossInfoFromDirectives(loopInfo.first, acrossInfo);

        bool hasConflict = false;
        // uniqKey -> pair<position of access, pair<acces>> ///write acceses ///
        map<DIST::Array*, pair<int, pair<int, int>>> arrayWriteAcc;
        // uniqKey -> ///read acceses ///
        map<DIST::Array*, vector<pair<int, int>>> arrayReadAcc;
        set<DIST::Array*> acrossOutArrays;

        __spf_print(PRINT_DIR_RESULT, "  Loop on line %d:\n", loopInfo.first->lineNum);

        const map<DIST::Array*, const ArrayInfo*> &currAccesses = loopInfo.second;
        // find conflict and fill arrayWriteAcc
        hasConflict = checkForConflict(currAccesses, loopInfo.first, arrayWriteAcc, acrossInfo, acrossOutArrays);

        if (hasConflict)
            __spf_print(PRINT_DIR_RESULT, "    has conflict\n");
        else
        {
            MapToArray mainArray;

            mainArray.arrayRef = NULL;
            mainArray.dimentionPos = -1;
            mainArray.hasWrite = true;
            mainArray.mainAccess;

            set<string> uniqNamesWithAcross;
            fillArraysWithAcrossStatus(loopInfo.first, uniqNamesWithAcross);

            if (arrayWriteAcc.size() == 1)
            {
                mainArray.arrayRef = arrayWriteAcc.begin()->first;
                mainArray.dimentionPos = arrayWriteAcc.begin()->second.first;
                mainArray.mainAccess = arrayWriteAcc.begin()->second.second;

                if (uniqNamesWithAcross.size())
                    mainArray.underAcross = true;
            }
            else if (arrayWriteAcc.size() > 1)
            {                
                if (uniqNamesWithAcross.size())
                    mainArray.underAcross = true;

                int posDim = -1;
                int minDim = 999999;
                int k = 0;

                vector<pair<string, pair<int, pair<int, int>>>> accesses;
                for (auto i = arrayWriteAcc.begin(); i != arrayWriteAcc.end(); ++i, ++k)
                {
                    const auto uniqKey = i->first;
                    const string &uniqName = uniqKey->GetName();

                    //ACROSS arrays have priority state for all nested loops!
                    if (uniqNamesWithAcross.size() > 0)
                        if (uniqNamesWithAcross.find(uniqName) == uniqNamesWithAcross.end())
                            continue;
                    
                    const int currDim = i->first->GetDimSize();
                    if (currDim < minDim)
                    {
                        minDim = currDim;
                        posDim = k;
                    }
                    __spf_print(PRINT_DIR_RESULT, "    found writes for array %s -> [%d %d]\n", uniqKey->GetShortName().c_str(), i->second.second.first, i->second.second.second);                    
                    accesses.push_back(make_pair(uniqKey->GetName(), i->second));
                }

                if (posDim == -1)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                vector<set<DIST::Array*>> realArrayRefs(accesses.size());
                for (int i = 0; i < (int)accesses.size(); ++i)
                {
                    DIST::Array *array = allArrays.GetArrayByName(accesses[i].first);
                    getRealArrayRefs(array, array, realArrayRefs[i], arrayLinksByFuncCalls);
                }

                //check the same distribution
                bool statusOk = true;
                for (int i = 0; i < (int)accesses.size(); ++i)
                {
                    for (int k = i + 1; k < (int)accesses.size(); ++k)
                    {
                        DIST::Array *array1 = allArrays.GetArrayByName(accesses[i].first);
                        DIST::Array *array2 = allArrays.GetArrayByName(accesses[k].first);

                        const set<DIST::Array*> &realArrayRefs1 = realArrayRefs[i];
                        const set<DIST::Array*> &realArrayRefs2 = realArrayRefs[k];

                        for (auto &refs1 : realArrayRefs1)
                        {
                            for (auto &refs2 : realArrayRefs2)
                            {
                                auto links = findLinksBetweenArrays(refs1, refs2, currReg->GetId());

                                const int dimFrom = accesses[i].second.first;
                                const int dimTo = accesses[k].second.first;

                                if (dimTo != links[dimFrom])
                                {
                                    __spf_print(1, "arrays '%s' and '%s' have different align dimensions for loop on line %d\n -->\
                                                    %d vs %d(%d) \n", 
                                                array1->GetShortName().c_str(), array2->GetShortName().c_str(), 
                                                loopInfo.first->lineNum, dimTo, links[dimFrom], dimFrom);
                                    statusOk = false;
                                }
                                else
                                {
                                    const auto accessFrom = accesses[i].second.second;
                                    const auto accessTo = accesses[k].second.second;
                                    
                                    auto templRule1 = refs1->GetAlignRulesWithTemplate(currReg->GetId());
                                    auto templRule2 = refs2->GetAlignRulesWithTemplate(currReg->GetId());

                                    if (DIST::Fx(accessFrom, templRule1[dimFrom]) != DIST::Fx(accessTo, templRule2[dimTo]))
                                    {
                                        __spf_print(1, "arrays '%s' and '%s' have different align ruls -- \n  -->\
                                                        F1 = [%d.%d], x1 = [%d.%d], F2 = [%d.%d], x2 = [%d.%d] \n  -->\
                                                        F1(x1) = [%d.%d] != F2(x2) = [%d.%d]\n",
                                                    array1->GetShortName().c_str(), array2->GetShortName().c_str(),
                                                    templRule1[dimFrom].first, templRule1[dimFrom].second, accessFrom.first, accessFrom.second, 
                                                    templRule2[dimTo].first, templRule2[dimTo].second, accessTo.first, accessTo.second, 
                                                    DIST::Fx(accessFrom, templRule1[dimFrom]).first, DIST::Fx(accessFrom, templRule1[dimFrom]).second,
                                                    DIST::Fx(accessTo, templRule2[dimTo]).first, DIST::Fx(accessTo, templRule2[dimTo]).second);
                                        statusOk = false;
                                    }
                                }

                                if (!statusOk)
                                {
                                    char buf[256];
                                    sprintf(buf, "arrays '%s' and '%s' have different align rules in this loop according to their write accesses",
                                                  array1->GetShortName().c_str(), array2->GetShortName().c_str());
                                    messages.push_back(Messages(WARR, loopInfo.first->lineNum, buf, 4011));
                                    sortedLoopGraph[loopInfo.first->lineNum]->hasDifferentAlignRules = true;
                                    break;
                                }
                            }
                            if (!statusOk)
                                break;
                        }
                        if (!statusOk)
                            break;
                    }
                    if (!statusOk)
                        break;
                }

                if (statusOk)
                {
                    k = 0;
                    pair<int, pair<int, int>> mainInfo;
                    for (auto array = arrayWriteAcc.begin(); array != arrayWriteAcc.end(); array++, ++k)
                    {
                        if (k == posDim)
                        {
                            mainArray.arrayRef = array->first;
                            mainArray.dimentionPos = array->second.first;
                            mainArray.mainAccess = array->second.second;

                            mainInfo = array->second;
                            break;
                        }
                    }
                }
                else
                {
                    __spf_print(PRINT_DIR_RESULT, "    has conflict writes\n");
                    hasConflict = true;
                }
            }
            else
            {
                mainArray.hasWrite = false;
                __spf_print(PRINT_DIR_RESULT, "   no regular writes on loop\n");
            }

            // find dependencies and fill mainArray if no regular writes found
            // now OmegaTest is used for searching dependencies 
            if (!hasConflict)
                hasConflict = checkForDependence(currAccesses, mainArray);

            if (!hasConflict &&
                mainArray.arrayRef != NULL && mainArray.dimentionPos != -1 && 
                !sortedLoopGraph[loopInfo.first->lineNum]->hasLimitsToParallel() &&
                loopInfo.first->lineNum > 0)
            {
                DIST::Array *mainArrayOfLoop = mainArray.arrayRef;
                //change array to template if ACROSS was not found
                if (mainArray.underAcross == false)
                {
                    set<DIST::Array*> realArrayRef;
                    getRealArrayRefs(mainArray.arrayRef, mainArray.arrayRef, realArrayRef, arrayLinksByFuncCalls);

                    set<DIST::Array*> templateLink;
                    vector<const vector<pair<int, int>>*> allRules;
                    vector<const vector<int>*> allLinks;

                    for (auto &array : realArrayRef)
                    {
                        DIST::Array *toAdd = array->GetTemplateArray(currReg->GetId());
                        if (toAdd)
                            templateLink.insert(toAdd);
                        allRules.push_back(&(array->GetAlignRulesWithTemplate(currReg->GetId())));
                        allLinks.push_back(&(array->GetLinksWithTemplate(currReg->GetId())));
                    }
                    
                    if (!isAllRulesEqual(allRules))
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    if (templateLink.size() != 1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    const vector<pair<int, int>> &rules = *allRules[0];
                    const vector<int> &links = *allLinks[0];

                    mainArray.arrayRef = *templateLink.begin();
                    mainArray.mainAccess = DIST::Fx(mainArray.mainAccess, rules[mainArray.dimentionPos]);
                    mainArray.dimentionPos = links[mainArray.dimentionPos];
                }

                ParallelDirective *parDir = NULL;
                LoopGraph *loop = createDirectiveForLoop(loopInfo.first, mainArray, sortedLoopGraph, acrossOutArrays);
                parDir = loop->directive;
                if (parDir != NULL)
                {
                    parDir->arrayRef2 = mainArrayOfLoop;
                    addShadowFromAnalysis(parDir, currAccesses);

                    loop->directiveForLoop = new ParallelDirective(*loop->directive);
                }
                __spf_print(PRINT_DIR_RESULT, "   directive created\n");
            }
        }
    }
}

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
                                return false;
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





static bool createLinksWithTemplate(map<DIST::Array*, vector<int>> &links, DIST::Array *templ, 
                                    const std::map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                    DIST::GraphCSR<int, double, attrType> &reducedG,
                                    DIST::Arrays<int> &allArrays, const int regionId)
{
    bool ok = true;
    if (templ == NULL)
        return false;

    for (auto &array : links)
    {
        set<DIST::Array*> realArrayRef;
        getRealArrayRefs(array.first, array.first, realArrayRef, arrayLinksByFuncCalls);

        vector<vector<int>> AllLinks(realArrayRef.size());
        int currL = 0;
        for (auto &array : realArrayRef)
            AllLinks[currL++] = findLinksBetweenArrays(array, templ, regionId);

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

    const DistrVariant *distRuleTempl = NULL;

    for (auto &array : allArraysInLoop)
        arrayLinksWithTmpl[array] = vector<int>();

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
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

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

                    char buf[256];
                    sprintf(buf, "Can not create distributed link for array '%s': dim size of this array is '%d' and it is not equal '%d'", 
                                  dir.arrayRef2->GetShortName().c_str(), dir.arrayRef2->GetDimSize(), (int)links.size());
                    messages.push_back(Messages(ERROR, loopLine, buf, 3007));

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
    
    ok = createLinksWithTemplate(arrayLinksWithTmpl, dir.arrayRef, arrayLinksByFuncCalls, reducedG, allArrays, regionId);
    
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
                    if (dir.on[array.second[i]].first == "*")
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
    if (parallelOn->isTemplate())
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
    if (parallelOn->isTemplate())
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

static bool addRedistributionDirs(SgFile *file, const vector<pair<DIST::Array*, const DistrVariant*>> &distribution,
                                  vector<pair<int, pair<string, vector<Expression*>>>> &toInsert,
                                  LoopGraph *current, const ParallelDirective *currParDir, const int regionId, vector<Messages> &messages)
{    
    vector<pair<DIST::Array*, DistrVariant*>> redistributeRules;
    const pair<vector<int>, vector<pair<string, vector<Expression*>>>> &redistrDirs = genRedistributeDirective(file, distribution, current, currParDir, regionId, redistributeRules);
    
    bool needToSkip = true;

    for (int z = 0; z < redistrDirs.first.size(); ++z)
    {
        if (ifRuleNull(redistributeRules[z].second))
            return needToSkip;
    }

    needToSkip = false;
    for (int z = 0; z < redistrDirs.first.size(); ++z)
    {
        const int idx = redistrDirs.first[z];
        string redist = "!DVM$ REDISTRIBUTE " + distribution[idx].first->GetShortName();
        redist += distribution[idx].second->GenRuleBase() + "\n";

        vector<Expression*> redistSt = { NULL, NULL, NULL, NULL };

        SgVarRefExp *ref = new SgVarRefExp(*findSymbolOrCreate(file, distribution[idx].first->GetShortName()));
        vector<Expression*> subs = distribution[idx].second->GenRuleSt(new File(file));

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

        toInsert.push_back(make_pair(current->lineNum, redistrDirs.second[z]));
        toInsert.push_back(make_pair(current->lineNumAfterLoop, make_pair(redist, redistSt)));
                
        __spf_print(1, "WARN: added redistribute for loop on line %d by array '%s' can significantly reduce performance\n", current->lineNum, distribution[idx].first->GetShortName().c_str());

        char buf[512];
        sprintf(buf, "Added redistribute for loop by array '%s' can significantly reduce performance", distribution[idx].first->GetShortName().c_str());
        messages.push_back(Messages(WARR, current->lineNum, buf, 3009));
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

static void analyzeRightPart(SgExpression *ex, map<DIST::Array*, vector<pair<bool, pair<int, int>>>> &rightValues,
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
                                    rightValues[elem.first][idx].second.first = std::min(rightValues[elem.first][idx].second.first, val);
                                    rightValues[elem.first][idx].second.second = std::max(rightValues[elem.first][idx].second.second, val);
                                }
                                else
                                {
                                    rightValues[elem.first][idx].first = true;
                                    rightValues[elem.first][idx].second = make_pair(val, val);
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


static void propagateTemplateInfo(map<DIST::Array*, vector<pair<bool, pair<int, int>>>> &arrays, const int regId,
    const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
    DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto &elem : arrays)
        {
            auto array = elem.first;
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

static inline bool findAndResolve(bool &resolved, vector<pair<bool, int>> &updateOn,
                                  const map<DIST::Array*, vector<bool>> &dimsNotMatch,
                                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                  DIST::GraphCSR<int, double, attrType> &reducedG, 
                                  const DIST::Arrays<int> &allArrays, const int regId,
                                  ParallelDirective *parDirective,
                                  map<DIST::Array*, vector<pair<bool, int>>> &values, 
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
            return false;// printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        findAndReplaceDimentions(rule, allArrays);

        for (int i = 0; i < elem.second.size(); ++i)
        {
            if (elem.second[i] && values[elem.first][i].first)
            {
                const int idx = get<1>(rule[i]);
                const auto &currRule = get<2>(rule[i]);

                const int mapTo = currRule.first * values[elem.first][i].second + currRule.second;
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

    //try to resolve from write operations
    for (int i = 0; i < updateOn.size(); ++i)
    {
        if (updateOn[i].first)
        {
            if (parDirective->on[i].first != "*")
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            else
            {
                parDirective->on[i].first = std::to_string(updateOn[i].second);
                parDirective->on[i].second = make_pair(1, 0);
                resolved = true;
            }
        }
    }

    return ret;
}

//TODO: calculate not only consts
static bool tryToResolveUnmatchedDims(const map<DIST::Array*, vector<bool>> &dimsNotMatch, SgStatement *loop, const int regId,
                                     ParallelDirective *parDirective, DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays,
                                     const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                     const vector<pair<DIST::Array*, const DistrVariant*>> &distribution)
{
    bool resolved = false;

    map<DIST::Array*, vector<pair<bool, int>>> values;
    map<DIST::Array*, vector<pair<bool, pair<int, int>>>> rightValues;

    for (auto &elem : dimsNotMatch)
    {
        values[elem.first] = vector<pair<bool, int>>(elem.second.size());
        std::fill(values[elem.first].begin(), values[elem.first].end(), make_pair(false, 0));

        rightValues[elem.first] = vector<pair<bool, pair<int, int>>>(elem.second.size());
        std::fill(rightValues[elem.first].begin(), rightValues[elem.first].end(), make_pair(false, make_pair(0, 0)));
    }

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
                                    if (values[elem.first][idx].first)
                                    {
                                        if (values[elem.first][idx].second != val) // CONFLICT WRITES
                                            return false;
                                    }
                                    else
                                        values[elem.first][idx] = make_pair(true, val);                                    
                                }
                                else // WRITE OP can not recognized
                                    return false;
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
            if (elem.second[idx] && (!values[elem.first][idx].first && !rightValues[elem.first][idx].first)) // NOT INFO FOUND
                return false;
    }

    //check multiplied Arrays to BLOCK distr of template
    for (auto &elem : dimsNotMatch)
    {
        const DIST::Array *templ = elem.first->GetTemplateArray(regId);
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

            auto &alignLinks = elem.first->GetLinksWithTemplate(regId);
            const set<int> alingLinksSet(alignLinks.begin(), alignLinks.end());
            for (int z = 0; z < templ->GetDimSize(); ++z)
            {
                if (alingLinksSet.find(z) == alingLinksSet.end())
                {
                    if (var->distRule[z] == BLOCK)
                    {
                        //check all accesses to write
                        for (auto &left : values)
                            for (auto &toCheck : left.second)
                                if (toCheck.first)
                                    return false;
                        return true;
                    }
                }
            }
        }
    }

    vector<pair<bool, int>> updateOn(parDirective->on.size());
    std::fill(updateOn.begin(), updateOn.end(), make_pair(false, 0));

    //try to resolve from write operations
    bool ok = findAndResolve(resolved, updateOn, dimsNotMatch, arrayLinksByFuncCalls, reducedG, allArrays, regId, parDirective, values);
    if (!ok)
        return false;
  
    //try to resolve from read operations
    if (!resolved)
    {
        map<DIST::Array*, vector<pair<bool, int>>> values2;
        for (auto &elem : rightValues)
            for (auto &vElem : elem.second)
                values2[elem.first].push_back(make_pair(vElem.first, vElem.second.first));
        
        ok = findAndResolve(resolved, updateOn, dimsNotMatch, arrayLinksByFuncCalls, reducedG, allArrays, regId, parDirective, values2, true);
        if (!ok)
            return false;
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
                    const auto &leftPartVal = values[elem.first];
                    for (int i = 0; i < leftPartVal.size(); ++i)
                    {
                        if (leftPartVal[i].first || elem.second[i].first)
                        {
                            int foundVal = 0;
                            if (leftPartVal[i].first)
                                foundVal = leftPartVal[i].second;
                            else
                            {
                                auto rules = elem.first->GetAlignRulesWithTemplate(regId);
                                auto links = elem.first->GetLinksWithTemplate(regId);
                                if (links[i] == -1)
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                const auto &currRule = rules[i];
                                foundVal = std::stoi(parDirective->on[links[i]].first) + currRule.second;
                            }

                            auto shadowElem = elem.second[i].second;
                            shadowElem.first -= foundVal;
                            shadowElem.second -= foundVal;

                            if (shadowElem.first > 0)
                                shadowElem.first = 0;
                            if (shadowElem.second < 0)
                                shadowElem.second = 0;

                            shadows.second[i].first = std::max(shadows.second[i].first, abs(shadowElem.first));
                            shadows.second[i].second = std::max(shadows.second[i].second, shadowElem.second);
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
        currProcessing.second = loop->loop;

        if (loop->directive && 
            (loop->hasLimitsToParallel() == false) && 
            (loop->region == currParReg) && 
            (loop->userDvmDirective == NULL))
        {
            if (loop->perfectLoop >= 1)
            {
                bool topCheck = isOnlyTopPerfect(loop, distribution);
                ParallelDirective *parDirective = loop->directive;
                /*if (topCheck == false)
                {  //try to unite loops and recheck
                    bool result = createNestedLoops(loop, depInfoForLoopGraph, messages);
                    if (result)
                    {
                        parDirective = loop->recalculateParallelDirective();
                        topCheck = isOnlyTopPerfect(loop, distribution);
                    }
                } */
                
                bool needToContinue = false;
                if (topCheck)
                {
                     //<Array, linksWithTempl> -> dims not mached
                    map<DIST::Array*, vector<bool>> dimsNotMatch;
                    if (!checkCorrectness(*parDirective, distribution, reducedG, allArrays, arrayLinksByFuncCalls, loop->getAllArraysInLoop(), messages, loop->lineNum, dimsNotMatch, regionId))
                    {
                        if (!tryToResolveUnmatchedDims(dimsNotMatch, loop->loop->GetOriginal(), regionId, parDirective, reducedG, allArrays, arrayLinksByFuncCalls, distribution))
                            needToContinue = addRedistributionDirs(file, distribution, toInsert, loop, parDirective, regionId, messages);
                    }
                }
                else
                    needToContinue = addRedistributionDirs(file, distribution, toInsert, loop, parDirective, regionId, messages);
                
                if (needToContinue)
                    continue;

                vector<pair<DIST::Array*, const DistrVariant*>> newRules;
                constructRules(newRules, distribution, loop);

                // insert parallel dir
                pair<string, vector<Expression*>> dir = 
                    parDirective->genDirective(new File(file), newRules, alignRules, reducedG, allArrays, loop->acrossOutAttribute, loop->readOps, loop->loop, regionId, arrayLinksByFuncCalls);
                toInsert.push_back(make_pair(loop->lineNum, dir));
            }
        }
        else //TODO: add checker for indexing in this loop
        {
            if (loopGraph[i]->children.size() != 0)
                selectParallelDirectiveForVariant(file, currParReg, reducedG, allArrays, loopGraph[i]->children, 
                                                  distribution, alignRules, toInsert, regionId, arrayLinksByFuncCalls, 
                                                  depInfoForLoopGraph, messages);
        }
    }
}

#undef PRINT_DIR_RESULT 
#undef PRINT_PROF_INFO
#undef FIRST
#undef SECOND
#undef THIRD