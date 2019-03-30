#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <map>
#include <set>

#include "../ParallelizationRegions/ParRegions.h"
#include "../Distribution/Arrays.h"

#include "../Utils/errors.h"
#include "directive_parser.h"
#include "directive_creator.h"

#define FIRST(x)  get<0>(x)
#define SECOND(x) get<1>(x)
#define THIRD(x)  get<2>(x)

#define PRINT_PROF_INFO  1
#define PRINT_DIR_RESULT 0

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
    std::pair<int, int> mainAccess;
    bool underAcross;
};

static LoopGraph* createDirectiveForLoop(LoopGraph *currentLoop, MapToArray &mainArray,
                                         map<int, LoopGraph*> &sortedLoopGraph, 
                                         const set<DIST::Array*> &acrossOutArrays)
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

    directive->parallel.push_back(currentLoop->loopSymbol);
    directive->arrayRef = mainArray.arrayRef;

    DIST::Array *tmp = mainArray.arrayRef;
    if (tmp != NULL)
    {
        for (int i = 0; i < tmp->GetDimSize(); ++i)
        {
            if (i == pos)
                directive->on.push_back(make_pair(currentLoop->loopSymbol, mainAccess));
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

    pair<pair<string, string>, vector<pair<int, int>>> *toAdd = NULL;
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
            for (auto &reads : currInfo.readOps[idx].coefficients)
            {
                auto &readPair = reads.first;
                if (readPair.second != 0)
                {
                    int left = 0, right = 0;
                    if (readPair.second < 0)
                        left = -readPair.second;
                    else
                        right = readPair.second;

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

static void findRegularReads(const ArrayInfo &currInfo, DIST::Array *arrayUniqKey, const int i, int &maxDim, MapToArray &mainArray)
{
    map<pair<int, int>, int> countAcc;
    for (auto &reads : currInfo.readOps[i].coefficients)
    {
        auto it = countAcc.find(reads.first);
        if (it == countAcc.end())
            countAcc.insert(it, make_pair(reads.first, 1));
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

static inline pair<int, int> 
getShadowsAcross(const string &array, const int pos,
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
            for (auto &elem : acceses.coefficients)
                uniqAccess.insert(elem.first);

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

void createParallelDirectives(const map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> &loopInfos,
                              vector<ParallelRegion*> regions, map<int, LoopGraph*> &sortedLoopGraph,
                              const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
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
                                    std::wstring bufw;
                                    __spf_printToLongBuf(bufw, L"arrays '%s' and '%s' have different align rules in this loop according to their write accesses",
                                                         to_wstring(array1->GetShortName()).c_str(), to_wstring(array2->GetShortName()).c_str());
                                    messages.push_back(Messages(WARR, loopInfo.first->lineNum, bufw, 4011));
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
                pair<int, int> mainAccess = mainArray.mainAccess;
                const int dimPos = mainArray.dimentionPos;

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
                    if (mainArray.underAcross == false)
                    {
                        for (int i = 0; i < mainArrayOfLoop->GetDimSize(); ++i)
                        {
                            if (i == dimPos)
                                parDir->on2.push_back(make_pair(loopInfo.first->loopSymbol, mainAccess));
                            else
                                parDir->on2.push_back(make_pair("*", make_pair(0, 0)));
                        }

                        for (int z = 0; z < parDir->on2.size(); ++z)
                            if (parDir->on2[z].first != "*" && parDir->on2[z].second == make_pair(0, 0))
                                parDir->on2[z].second = mainAccess;
                    }
                    else
                        parDir->on2 = parDir->on;
                    
                    addShadowFromAnalysis(parDir, currAccesses);
                    loop->directiveForLoop = new ParallelDirective(*loop->directive);
                }
                __spf_print(PRINT_DIR_RESULT, "   directive created\n");
            }
        }
    }
}

#undef PRINT_PROF_INFO
#undef PRINT_DIR_RESULT 