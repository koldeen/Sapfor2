#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <map>
#include <vector>
#include <set>
#include <string>

using std::vector;
using std::map;
using std::set;
using std::string;
using std::pair;
using std::make_pair;

#include "graph_loops.h"
#include "../Utils/errors.h"
#include "../Distribution/Distribution.h"

static void fillWriteReadOps(LoopGraph *&currLoop, DIST::Array *symbol, const ArrayInfo *arrayOps)
{
    auto it = currLoop->readOps.find(symbol);
    if (it == currLoop->readOps.end())
        it = currLoop->readOps.insert(it, make_pair(symbol, make_pair(vector<ArrayOp>(), vector<bool>())));

    const int dim = symbol->GetDimSize();
    it->second.first.resize(dim);
    it->second.second.resize(dim);

    for (int z = 0; z < dim; ++z)
    {
        it->second.first[z] = arrayOps->readOps[z];
        it->second.second[z] = arrayOps->unrecReadOps[z];
    }

    auto it1 = currLoop->writeOps.find(symbol);
    if (it1 == currLoop->writeOps.end())
        it1 = currLoop->writeOps.insert(it1, make_pair(symbol, vector<ArrayOp>()));
    it1->second.resize(dim);
    for (int z = 0; z < dim; ++z)
        it1->second[z] = arrayOps->writeOps[z];
}

static void uniteVectors(const ArrayOp &from, ArrayOp &to)
{
    set <pair<int, int>> fromSet, toSet;
    for (int i = 0; i < from.coefficients.size(); ++i)
        fromSet.insert(from.coefficients[i]);
    for (int i = 0; i < to.coefficients.size(); ++i)
        toSet.insert(to.coefficients[i]);

    vector<pair<int, int>> unitedVector(fromSet.size() + toSet.size());
    auto it = set_union(fromSet.begin(), fromSet.end(), toSet.begin(), toSet.end(), unitedVector.begin());
    unitedVector.resize(it - unitedVector.begin());

    to.coefficients = unitedVector;
}

static void uniteChildReadInfo(LoopGraph *currLoop)
{
    if (currLoop->perfectLoop > 1)
    {
        int depth = currLoop->perfectLoop;
        while (depth != 1)
        {
            LoopGraph *part1 = currLoop, *part2 = currLoop;
            for (int i = 0; i < depth - 1; ++i)
                part1 = part1->childs[0];
            for (int i = 0; i < depth - 2; ++i)
                part2 = part2->childs[0];

            set<DIST::Array*> newToAdd;

            for (auto it = part1->readOps.begin(); it != part1->readOps.end(); ++it)
            {
                auto it2 = part2->readOps.find(it->first);
                if (it2 == part2->readOps.end())
                    newToAdd.insert(it->first);
            }

            for (auto it = part2->readOps.begin(); it != part2->readOps.end(); ++it)
            {
                auto it2 = part1->readOps.find(it->first);
                if (it2 != part1->readOps.end())
                {
                    const vector<ArrayOp> &toAddReads = it2->second.first;
                    const vector<bool> &toAddUnrecReads = it2->second.second;
                    for (int i = 0; i < it->second.first.size(); ++i)
                        uniteVectors(toAddReads[i], it->second.first[i]);

                    for (int i = 0; i < it->second.second.size(); ++i)
                        it->second.second[i] = it->second.second[i] || toAddUnrecReads[i];
                }
            }

            for (auto &arrayMissed : newToAdd)
                part2->readOps[arrayMissed] = part1->readOps[arrayMissed];

            depth--;
        }
    }
    else
    {
        for (int i = 0; i < currLoop->childs.size(); ++i)
            uniteChildReadInfo(currLoop->childs[i]);
    }
}

static void fillConflictState(LoopGraph *currLoop, map<DIST::Array*, bool> &foundConflicts, map<DIST::Array*, vector<ArrayOp>> &unitedWROps)
{
    for (int i = 0; i < currLoop->childs.size(); ++i)
    {
        if (i > 0)
        {
            foundConflicts.clear();
            unitedWROps.clear();
        }
        fillConflictState(currLoop->childs[i], foundConflicts, unitedWROps);
    }

    for (auto it = currLoop->writeOps.begin(); it != currLoop->writeOps.end(); ++it)
    {
        DIST::Array *arrayN = it->first;
        vector<ArrayOp> &currWrites = it->second;
        auto itRead = currLoop->readOps.find(arrayN);
        if (itRead != currLoop->readOps.end())
        {
            const vector<ArrayOp> &currReads = itRead->second.first;
            for (int i = 0; i < currWrites.size(); ++i)
                uniteVectors(currReads[i], currWrites[i]);
        }

        auto it2 = unitedWROps.find(arrayN);
        if (it2 != unitedWROps.end())
        {
            vector<ArrayOp> &unitedW = it2->second;
            for (int i = 0; i < unitedW.size(); ++i)
            {
                if (currWrites[i].coefficients.size() != 0 && unitedW[i].coefficients.size() != 0)
                {
                    foundConflicts[arrayN] = true;
                    currLoop->hasConflicts[arrayN] = true;
                }
                else if (unitedW[i].coefficients.size() == 0)
                    unitedW[i] = currWrites[i];
                else
                    for (int k = 0; k < currWrites[i].coefficients.size(); ++k)
                        unitedW[i].coefficients.push_back(currWrites[i].coefficients[k]);
            }
        }
        else
            it2 = unitedWROps.insert(it2, make_pair(arrayN, currWrites));
    }
}

void processLoopInformationForFunction(map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> &loopInfo)
{
    // fill reads info
    for (auto it = loopInfo.begin(); it != loopInfo.end(); ++it)
    {
        LoopGraph *graphLoop = it->first;
        const map<DIST::Array*, const ArrayInfo*> &currInfo = it->second;

        for (auto it3 = currInfo.begin(); it3 != currInfo.end(); ++it3)
            fillWriteReadOps(graphLoop, it3->first, it3->second);

        for (auto it3 = currInfo.begin(); it3 != currInfo.end(); ++it3)
        {
            const ArrayInfo *currInfo = it3->second;
            bool nulReads = true;
            for (int z = 0; z < currInfo->dimSize; ++z)
            {
                if (currInfo->readOps[z].coefficients.size() != 0)
                {
                    nulReads = false;
                    break;
                }
            }

            if (!nulReads)
                graphLoop->readOpsArray.insert(it3->first);
        }
    }

    // fill conflict state
    for (auto it = loopInfo.begin(); it != loopInfo.end(); ++it)
    {
        map<DIST::Array*, bool> foundConflicts;
        map<DIST::Array*, vector<ArrayOp>> unitedWROps;
        fillConflictState(it->first, foundConflicts, unitedWROps);
    }

    //unite reads info
    for (auto it = loopInfo.begin(); it != loopInfo.end(); ++it)
        uniteChildReadInfo(it->first);
}

static void addToGraph(DIST::GraphCSR<int, double, attrType> &G,
                       DIST::Arrays<int> &allArrays,
                       const double currWeight,
                       const ArrayInfo *from, DIST::Array *fromSymb,
                       const ArrayInfo *to, DIST::Array *toSymb)
{
    bool loopHasWrite = false;

    // add W-R and W-W
    for (int dimFrom = 0; dimFrom < from->dimSize; ++dimFrom)
    {
        for (int dimTo = 0; dimTo < to->dimSize; ++dimTo)
        {
            if ((from->writeOps[dimFrom].coefficients.size() != 0) || (to->writeOps[dimTo].coefficients.size() != 0))
                loopHasWrite = true;

            if (from->writeOps[dimFrom].coefficients.size() != 0 && (to->writeOps[dimTo].coefficients.size() != 0 || to->readOps[dimTo].coefficients.size() != 0))
            {
                for (int z = 0; z < (int)from->writeOps[dimFrom].coefficients.size(); ++z)
                {
                    for (int z1 = 0; z1 < (int)to->writeOps[dimTo].coefficients.size(); ++z1)
                        AddArrayAccess(G, allArrays, fromSymb, toSymb, make_pair(dimFrom, dimTo), currWeight, make_pair(from->writeOps[dimFrom].coefficients[z], to->writeOps[dimTo].coefficients[z1]), WW_link);

                    for (int z1 = 0; z1 < (int)to->readOps[dimTo].coefficients.size(); ++z1)
                        AddArrayAccess(G, allArrays, fromSymb, toSymb, make_pair(dimFrom, dimTo), currWeight, make_pair(from->writeOps[dimFrom].coefficients[z], to->readOps[dimTo].coefficients[z1]), WR_link);
                }
            }
        }
    }

    //add R-R, if no W
    if (loopHasWrite == false)
    {
        for (int dimFrom = 0; dimFrom < from->dimSize; ++dimFrom)
            for (int dimTo = 0; dimTo < to->dimSize; ++dimTo)
                if (from->readOps[dimFrom].coefficients.size() != 0 && to->readOps[dimTo].coefficients.size() != 0)
                    for (int z = 0; z < (int)from->readOps[dimFrom].coefficients.size(); ++z)
                        for (int z1 = 0; z1 < (int)to->readOps[dimTo].coefficients.size(); ++z1)
                            AddArrayAccess(G, allArrays, fromSymb, toSymb, make_pair(dimFrom, dimTo), currWeight, make_pair(from->readOps[dimFrom].coefficients[z], to->readOps[dimTo].coefficients[z1]), RR_link);
    }
}

//TODO: check for recursion!!
void getRealArrayRefs(DIST::Array *addTo, DIST::Array *curr,
                      set<DIST::Array*> &realArrayRefs,
                      const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    auto itLink = arrayLinksByFuncCalls.find(curr);
    if (itLink == arrayLinksByFuncCalls.end())
        realArrayRefs.insert(curr);
    else
        for (auto &link : itLink->second)
            getRealArrayRefs(addTo, link, realArrayRefs, arrayLinksByFuncCalls);
}

void getAllArrayRefs(DIST::Array *addTo, DIST::Array *curr,
                     set<DIST::Array*> &allArrayRefs,
                     const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    auto itLink = arrayLinksByFuncCalls.find(curr);
    allArrayRefs.insert(curr);

    if (itLink == arrayLinksByFuncCalls.end())
        return;
    else
        for (auto &link : itLink->second)
            if (allArrayRefs.find(link) == allArrayRefs.end())
                getAllArrayRefs(addTo, link, allArrayRefs, arrayLinksByFuncCalls);
}

void addToDistributionGraph(const map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> &loopInfo,
                            const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    for (auto it = loopInfo.begin(); it != loopInfo.end(); it++)
    {
        ParallelRegion *currReg = it->first->region;
        if (currReg == NULL)
        {
            __spf_print(1, "Skip loop on line %d - no parallel region for this loop\n", it->first->lineNum);
            continue;
        }

        const double currWeight = it->first->countOfIterNested;

        DIST::GraphCSR<int, double, attrType> &G = currReg->GetGraphToModify();
        DIST::Arrays<int> &allArrays = currReg->GetAllArraysToModify();

        //printf("for loop on line %d: \n", it->first->lineNum);
        const map<DIST::Array*, const ArrayInfo*> &currAccesses = it->second;
        map<DIST::Array*, set<DIST::Array*>> realArrayRefs;
        for (auto &access : currAccesses)
            getRealArrayRefs(access.first, access.first, realArrayRefs[access.first], arrayLinksByFuncCalls);

        for (auto &accessFrom : currAccesses)
        {
            const ArrayInfo *from = accessFrom.second;
            allArrays.AddArrayToGraph(accessFrom.first);

            for (auto &fromSymb : realArrayRefs[accessFrom.first])
            {
                for (auto &accessTo : currAccesses)
                {
                    if (&accessTo == &accessFrom)
                        continue;
                                        
                    const ArrayInfo *to = accessTo.second;
                    allArrays.AddArrayToGraph(accessTo.first);
                    for (auto &toSymb : realArrayRefs[accessTo.first])
                        addToGraph(G, allArrays, currWeight, from, fromSymb, to, toSymb);
                }
            }
        }
    }
}

bool addToDistributionGraph(const LoopGraph *loopInfo, const string &inFunction)
{
    ParallelRegion *currReg = loopInfo->region;
    if (currReg == NULL || loopInfo->calculatedCountOfIters == 0 || loopInfo->hasLimitsToParallel())
    {
        __spf_print(1, "Skip loop on line %d\n", loopInfo->lineNum);
        return false;
    }

    const double currWeight = loopInfo->countOfIterNested;

    DIST::GraphCSR<int, double, attrType> &G = currReg->GetGraphToModify();
    DIST::Arrays<int> &allArrays = currReg->GetAllArraysToModify();
        
    string fullLoopName = loopInfo->genLoopArrayName(inFunction);
    string loopName = fullLoopName;

    DIST::Array *loopArray = new DIST::Array(fullLoopName, loopName, 1, getUniqArrayId(), loopInfo->fileName, loopInfo->lineNum, make_pair(0, inFunction), NULL);

    loopArray->ExtendDimSize(0, make_pair(loopInfo->startVal, loopInfo->endVal));
    loopArray->setLoopArray(true);

    allArrays.AddArrayToGraph(loopArray);
    return true;
}

static void printBlanks(FILE *file, const int sizeOfBlank, const int countOfBlanks)
{
    for (int k = 0; k < countOfBlanks; ++k)
        for (int m = 0; m < sizeOfBlank; ++m)
            fprintf(file, " ");
}

static void printLoopGraphLvl(FILE *file, const vector<LoopGraph*> &childs, const int lvl)
{
    for (int k = 0; k < (int)childs.size(); ++k)
    {
        printBlanks(file, 2, lvl);
        fprintf(file, "FOR on line %d", childs[k]->lineNum);
        if (childs[k]->perfectLoop > 1)
            fprintf(file, " [PERFECT]");
        if (childs[k]->hasGoto)
            fprintf(file, " [HAS GOTO]");
        if (childs[k]->hasPrints)
            fprintf(file, " [HAS I/O OPS]");
        if (childs[k]->region)
            fprintf(file, " [REGION %s]", childs[k]->region->GetName().c_str());
        if (childs[k]->userDvmDirective)
            fprintf(file, " [USER DVM]");

        fprintf(file, " [IT = %d / MULT = %f]", childs[k]->countOfIters, childs[k]->countOfIterNested);
        fprintf(file, "\n");

        for (int i = 0; i < (int)childs[k]->calls.size(); ++i)
        {
            printBlanks(file, 2, lvl);
            fprintf(file, "CALL %s [%d]\n", childs[k]->calls[i].first.c_str(), childs[k]->calls[i].second);
        }
        printLoopGraphLvl(file, childs[k]->childs, lvl + 1);
    }
}

int printLoopGraph(const char *fileName, const map<string, vector<LoopGraph*>> &loopGraph)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        __spf_print(1, "can not open file %s\n", fileName);
        return -1;
    }

    map<string, vector<LoopGraph*>>::const_iterator it;
    for (it = loopGraph.begin(); it != loopGraph.end(); it++)
    {
        fprintf(file, "*** FILE %s\n", it->first.c_str());
        printLoopGraphLvl(file, it->second, 1);
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}


static void isAllOk(const vector<LoopGraph*> &loops, vector<Messages> &currMessages, set<void*> &isNotOkey, set<string> &uniqMessages)
{
    for (int i = 0; i < loops.size(); ++i)
    {
        if (loops[i]->region)
        {
            if (loops[i]->countOfIters == 0 && loops[i]->region)
            {
                char buf[256];
                sprintf(buf, "Can not calculate count of iterations for this loop, information about iterations in all loops in parallel regions '%s' will be ignored", loops[i]->region->GetName().c_str());

                auto itM = uniqMessages.find(buf);
                if (itM == uniqMessages.end())
                {
                    uniqMessages.insert(itM, buf);

                    currMessages.push_back(Messages(NOTE, loops[i]->lineNum, buf, 1016));
                    __spf_print(1, "Can not calculate count of iterations for loop on line %d, information about iterations in all loops in parallel regions '%s' will be ignored\n", loops[i]->lineNum, loops[i]->region->GetName().c_str());
                }
                isNotOkey.insert(loops[i]->region);
            }
            isAllOk(loops[i]->childs, currMessages, isNotOkey, uniqMessages);
        }
    }
}


static void setToDefaultCountIter(vector<LoopGraph*> &loops, const set<void*> &isNotOkey)
{
    for (int i = 0; i < loops.size(); ++i)
    {
        if (loops[i]->region)
        {
            if (isNotOkey.find(loops[i]->region) != isNotOkey.end())
                loops[i]->countOfIters = 2;
            setToDefaultCountIter(loops[i]->childs, isNotOkey);
        }
    }
}

static void multiplyCountIter(vector<LoopGraph*> &loops, const double allCount, const set<void*> &isNotOkey)
{
    for (int i = 0; i < loops.size(); ++i)
    {
        if (isNotOkey.find(loops[i]->region) == isNotOkey.end())
            loops[i]->countOfIterNested = loops[i]->countOfIters * allCount;
        multiplyCountIter(loops[i]->childs, loops[i]->countOfIterNested, isNotOkey);
    }
}

void checkCountOfIter(map<string, vector<LoopGraph*>> &loopGraph, map<string, vector<Messages>> &SPF_messages)
{
    set<void*> isNotOkey;

    for (auto it = loopGraph.begin(); it != loopGraph.end(); ++it)
    {
        set<string> uniqMessages;

        auto itM = SPF_messages.find(it->first);
        if (itM == SPF_messages.end())
            itM = SPF_messages.insert(itM, make_pair(it->first, vector<Messages>()));
        isAllOk(it->second, itM->second, isNotOkey, uniqMessages);
    }

    if (isNotOkey.size() != 0)
    {
        for (auto it = loopGraph.begin(); it != loopGraph.end(); ++it)
            setToDefaultCountIter(it->second, isNotOkey);
    }

    for (auto it = loopGraph.begin(); it != loopGraph.end(); ++it)
        multiplyCountIter(it->second, 1.0, isNotOkey);

}