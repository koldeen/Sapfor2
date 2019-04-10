#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>

using std::vector;
using std::map;
using std::unordered_map;
using std::tuple;
using std::set;
using std::string;
using std::wstring;
using std::pair;
using std::make_pair;
using std::get;

#include "graph_loops.h"
#include "../GraphCall/graph_calls_func.h"
#include "../Utils/errors.h"
#include "../Distribution/Distribution.h"
#include "../ParallelizationRegions/ParRegions.h"
#ifdef _WIN32
#include "../VisualizerCalls/get_information.h"
#endif

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
    for (auto &elemFrom : from.coefficients)
    {
        auto it = to.coefficients.find(elemFrom.first);
        if (it == to.coefficients.end())
            it = to.coefficients.insert(it, elemFrom);
        else
            it->second += elemFrom.second;
    }
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
                part1 = part1->children[0];
            for (int i = 0; i < depth - 2; ++i)
                part2 = part2->children[0];

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
        for (int i = 0; i < currLoop->children.size(); ++i)
            uniteChildReadInfo(currLoop->children[i]);
    }
}

static void fillConflictState(LoopGraph *currLoop, map<DIST::Array*, bool> &foundConflicts, map<DIST::Array*, vector<ArrayOp>> &unitedWROps)
{
    for (int i = 0; i < currLoop->children.size(); ++i)
    {
        if (i > 0)
        {
            foundConflicts.clear();
            unitedWROps.clear();
        }
        fillConflictState(currLoop->children[i], foundConflicts, unitedWROps);
    }

    for (auto it = currLoop->writeOps.begin(); it != currLoop->writeOps.end(); ++it)
    {
        DIST::Array *arrayN = it->first;
        vector<ArrayOp> currWrites = it->second;

        //TODO: почему раньше надо было смотреть и чтени€?! ¬едь эти конфликты разрешаютс€ c помощью REMOTE
        /*auto itRead = currLoop->readOps.find(arrayN);
        if (itRead != currLoop->readOps.end())
        {
            const vector<ArrayOp> &currReads = itRead->second.first;
            for (int i = 0; i < currWrites.size(); ++i)
                uniteVectors(currReads[i], currWrites[i]);
        }*/

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
                {
                    for (auto &oldWrites : currWrites[i].coefficients)
                    {
                        auto it = unitedW[i].coefficients.find(oldWrites.first);
                        if (it == unitedW[i].coefficients.end())
                            it = unitedW[i].coefficients.insert(it, make_pair(oldWrites.first, 0));
                        it->second += oldWrites.second;
                    }
                }
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

#define GROUP_BY_REQUEST 1

#if GROUP_BY_REQUEST
class GroupItem
{
private:
    int maxDim1;
    int maxDim2;
    vector<pair<pair<int, int>, map<attrType, double>>> coeffs;    

public:
    GroupItem(int maxD1, int maxD2) : maxDim1(maxD1), maxDim2(maxD2), coeffs(maxD1 * maxD2) { }
    void inline AddToGroup(int dim1, int dim2, const attrType &key, const double currW)
    {
        int pos = dim2 * maxDim1 + dim1;
        auto &current = coeffs[pos];
        current.first = make_pair(dim1, dim2);

        auto it = current.second.find(key);
        if (it == current.second.end())
            it = current.second.insert(it, make_pair(key, 0.0));
        it->second += currW;
    }

    const vector<pair<pair<int, int>, map<attrType, double>>>& GetCoeffs() const { return coeffs; }
};


static void inline addGroup(DIST::GraphCSR<int, double, attrType> &G,
                            DIST::Arrays<int> &allArrays,
                            const map<pair<DIST::Array*, DIST::Array*>, GroupItem> &group,
                            const links linkType)
{
    for (auto &elem : group)
    {
        DIST::Array *from = elem.first.first;
        DIST::Array *to = elem.first.second;
                
        for (auto &coeffs : elem.second.GetCoeffs())
        {
            const auto &arc = coeffs.first;
            for (auto &weight : coeffs.second)
                AddArrayAccess(G, allArrays, from, to, arc, weight.second, weight.first, linkType);
        }
    }
}
#endif

static double calculateSizes(const vector<pair<int, int>> &in, vector<int> &out)
{
    double all = 1.0;
    for (auto &elem : in)
    {
        if (elem.first >= elem.second)
        {
            out.push_back(2);
            all *= 2;
        }
        else
        {
            out.push_back(elem.second - elem.first + 1);
            all *= (elem.second - elem.first + 1);
        }
    }

    return all;
}

static bool addToGraph(DIST::GraphCSR<int, double, attrType> &G,
                       DIST::Arrays<int> &allArrays,
                       const ArrayInfo *from, DIST::Array *fromSymb,
                       const ArrayInfo *to, DIST::Array *toSymb, const links linkType)
{
    bool loopHasWrite = false;
#if GROUP_BY_REQUEST
    map<pair<DIST::Array*, DIST::Array*>, GroupItem> ww_links;
    map<pair<DIST::Array*, DIST::Array*>, GroupItem> wr_links;
    map<pair<DIST::Array*, DIST::Array*>, GroupItem> rr_links;
#endif

    auto sizesFromPair = fromSymb->GetSizes();
    auto sizesToPair = toSymb->GetSizes();
    
    vector<int> sizesFrom;
    vector<int> sizesTo;
    
    double allFrom = calculateSizes(sizesFromPair, sizesFrom);
    double allTo = calculateSizes(sizesToPair, sizesTo);

    if (linkType == WW_link)
    {
        // add W-R and W-W
        for (int dimFrom = 0; dimFrom < from->dimSize; ++dimFrom)
        {
            for (int dimTo = 0; dimTo < to->dimSize; ++dimTo)
            {
                if ((from->writeOps[dimFrom].coefficients.size() != 0) || (to->writeOps[dimTo].coefficients.size() != 0))
                    loopHasWrite = true;

                if ((from->writeOps[dimFrom].coefficients.size() != 0 || from->readOps[dimFrom].coefficients.size() != 0) &&
                    (to->writeOps[dimTo].coefficients.size() != 0 || to->readOps[dimTo].coefficients.size() != 0))
                {
                    for (auto &writeFrom : from->writeOps[dimFrom].coefficients)
                    {
                        for (auto &writeTo : to->writeOps[dimTo].coefficients)
#if GROUP_BY_REQUEST
                        {
                            const auto key = make_pair(fromSymb, toSymb);
                            auto it = ww_links.find(key);
                            if (it == ww_links.end())
                                it = ww_links.insert(it, make_pair(key, GroupItem(fromSymb->GetDimSize(), toSymb->GetDimSize())));

                            it->second.AddToGroup(dimFrom, dimTo, make_pair(writeFrom.first, writeTo.first), writeTo.second * allTo + writeFrom.second * allFrom);
                        }
#else
                            AddArrayAccess(G, allArrays, fromSymb, toSymb, make_pair(dimFrom, dimTo), writeTo.second * allTo + writeFrom.second * allFrom, make_pair(writeFrom.first, writeTo.first), WW_link);
#endif
                    }
                }
            }
        }
    }

    if (linkType == WR_link)
    {
        for (int dimFrom = 0; dimFrom < from->dimSize; ++dimFrom)
        {
            for (int dimTo = 0; dimTo < to->dimSize; ++dimTo)
            {
                if ((from->writeOps[dimFrom].coefficients.size() != 0) || (to->writeOps[dimTo].coefficients.size() != 0))
                    loopHasWrite = true;

                if ((from->writeOps[dimFrom].coefficients.size() != 0 || from->readOps[dimFrom].coefficients.size() != 0) &&
                    (to->writeOps[dimTo].coefficients.size() != 0 || to->readOps[dimTo].coefficients.size() != 0))
                {
                    for (auto &writeFrom : from->writeOps[dimFrom].coefficients)
                    {
                        for (auto &readTo : to->readOps[dimTo].coefficients)
#if GROUP_BY_REQUEST
                        {
                            const auto key = make_pair(fromSymb, toSymb);
                            auto it = wr_links.find(key);
                            if (it == wr_links.end())
                                it = wr_links.insert(it, make_pair(key, GroupItem(fromSymb->GetDimSize(), toSymb->GetDimSize())));

                            it->second.AddToGroup(dimFrom, dimTo, make_pair(writeFrom.first, readTo.first), readTo.second * allTo);
                        }
#else
                            AddArrayAccess(G, allArrays, fromSymb, toSymb, make_pair(dimFrom, dimTo), readTo.second * allTo, make_pair(writeFrom.first, readTo.first), WR_link);
#endif
                    }
                }
            }
        }
    }

    //add R-R, if no W
    if (linkType == RR_link)    
    {
        for (int dimFrom = 0; dimFrom < from->dimSize; ++dimFrom)
            for (int dimTo = 0; dimTo < to->dimSize; ++dimTo)
                if (from->readOps[dimFrom].coefficients.size() != 0 && to->readOps[dimTo].coefficients.size() != 0)
                    for (auto &readFrom : from->readOps[dimFrom].coefficients)
                        for (auto &readTo : to->readOps[dimTo].coefficients)
#if GROUP_BY_REQUEST
                        {
                            const auto key = make_pair(fromSymb, toSymb);
                            auto it = rr_links.find(key);
                            if (it == rr_links.end())
                                it = rr_links.insert(it, make_pair(key, GroupItem(fromSymb->GetDimSize(), toSymb->GetDimSize())));

                            it->second.AddToGroup(dimFrom, dimTo, make_pair(readFrom.first, readTo.first), readTo.second  * std::max(allTo, allFrom));
                        }
#else
                            AddArrayAccess(G, allArrays, fromSymb, toSymb, make_pair(dimFrom, dimTo), readTo.second * std::max(allTo, allFrom), make_pair(readFrom.first, readTo.first), RR_link);
#endif
    }

#if GROUP_BY_REQUEST
    addGroup(G, allArrays, ww_links, WW_link);
    addGroup(G, allArrays, wr_links, WR_link);
    addGroup(G, allArrays, rr_links, RR_link);
#endif

    return loopHasWrite;
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

static bool processLinks(const vector<pair<DIST::Array*, const ArrayInfo*>> &currAccessesV,
                         DIST::Arrays<int> &allArrays, map<DIST::Array*, set<DIST::Array*>> &realArrayRefs,
                         DIST::GraphCSR<int, double, attrType> &G, const links linkType)
{
    bool has_Wr_Ww_edges = false;
    for (int z = 0; z < currAccessesV.size(); ++z)
    {
        const ArrayInfo &fromUniq = *currAccessesV[z].second;
        allArrays.AddArrayToGraph(currAccessesV[z].first);

        for (auto &fromSymb : realArrayRefs[currAccessesV[z].first])
        {
            for (int z1 = (linkType == WR_link) ? 0 : z + 1; z1 < currAccessesV.size(); ++z1)
            {
                if (z1 == z)
                    continue;

                const ArrayInfo &toUniq = *(currAccessesV[z1].second);
                allArrays.AddArrayToGraph(currAccessesV[z1].first);
                for (auto &toSymb : realArrayRefs[currAccessesV[z1].first])
                {
                    bool res = addToGraph(G, allArrays, &fromUniq, fromSymb, &toUniq, toSymb, linkType);
                    has_Wr_Ww_edges |= res;
                }
            }
        }
    }

    return has_Wr_Ww_edges;
}

void addToDistributionGraph(const map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> &loopInfo,
                            const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    for (auto it = loopInfo.begin(); it != loopInfo.end(); it++)
    {
#if _WIN32 && NDEBUG
        createNeededException();
#endif
        ParallelRegion *currReg = it->first->region;
        if (currReg == NULL)
        {
            __spf_print(1, "Skip loop on line %d - no parallel region for this loop\n", it->first->lineNum);
            continue;
        }

        DIST::GraphCSR<int, double, attrType> &G = currReg->GetGraphToModify();
        DIST::Arrays<int> &allArrays = currReg->GetAllArraysToModify();

        //printf("for loop on line %d: \n", it->first->lineNum);
        const map<DIST::Array*, const ArrayInfo*> &currAccesses = it->second;
        map<DIST::Array*, set<DIST::Array*>> realArrayRefs;
        for (auto &access : currAccesses)
            getRealArrayRefs(access.first, access.first, realArrayRefs[access.first], arrayLinksByFuncCalls);

        const vector<pair<DIST::Array*, const ArrayInfo*>> currAccessesV(currAccesses.begin(), currAccesses.end());
        bool has_Wr_edges = false, has_Ww_edges = false;
        has_Wr_edges = processLinks(currAccessesV, allArrays, realArrayRefs, G, WW_link);
        has_Ww_edges |= processLinks(currAccessesV, allArrays, realArrayRefs, G, WR_link);
        if (!has_Wr_edges && !has_Ww_edges)
            processLinks(currAccessesV, allArrays, realArrayRefs, G, RR_link);
        
        /*for (auto &accessFrom : currAccesses)
        {
            const ArrayInfo &fromUniq = *accessFrom.second;
            allArrays.AddArrayToGraph(accessFrom.first);

            for (auto &fromSymb : realArrayRefs[accessFrom.first])
            {
                for (auto &accessTo : currAccesses)
                {
                    if (&accessTo == &accessFrom)
                        continue;

                    const ArrayInfo &toUniq = *accessTo.second;
                    allArrays.AddArrayToGraph(accessTo.first);
                    for (auto &toSymb : realArrayRefs[accessTo.first])
                    {
                        bool t, t1;
                        t = addToGraph(G, allArrays, &fromUniq, fromSymb, &toUniq, toSymb, WW_link);
                        t1 = addToGraph(G, allArrays, &fromUniq, fromSymb, &toUniq, toSymb, WR_link);
                        if (!t && !t1)
                            addToGraph(G, allArrays, &fromUniq, fromSymb, &toUniq, toSymb, RR_link);
                    }
                }
            }
        }*/
    }
}

bool addToDistributionGraph(const LoopGraph *loopInfo, const string &inFunction)
{
    ParallelRegion *currReg = loopInfo->region;

    if (currReg == NULL || loopInfo->hasLimitsToParallel())
    {
        __spf_print(1, "Skip loop on line %d\n", loopInfo->lineNum);
        return false;
    }

    const double currWeight = loopInfo->countOfIterNested;

    DIST::GraphCSR<int, double, attrType> &G = currReg->GetGraphToModify();
    DIST::Arrays<int> &allArrays = currReg->GetAllArraysToModify();
        
    string fullLoopName = loopInfo->genLoopArrayName(inFunction);
    string loopName = fullLoopName;

    vector<string> regs;
    regs.push_back(currReg->GetName());

    DIST::Array *loopArray = new DIST::Array(fullLoopName, loopName, 1, getUniqArrayId(), loopInfo->fileName, 
                                             loopInfo->lineNum, make_pair(DIST::l_LOCAL, inFunction), NULL, regs, 0);
    
    if (loopInfo->calculatedCountOfIters == 0)
    {
        if (loopInfo->startEndExpr.first && loopInfo->startEndExpr.second)
        {
            const vector<pair<Expression*, Expression*>> toAdd = { loopInfo->startEndExpr };
            loopArray->SetSizesExpr(toAdd);
        }
    }
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

static void printLoopGraphLvl(FILE *file, const vector<LoopGraph*> &childs, const int lvl, bool withRegs = false)
{
    for (int k = 0; k < (int)childs.size(); ++k)
    {
        bool needToPrint = true;
        if (withRegs)
            if (childs[k]->region == NULL)
                needToPrint = false;

        if (needToPrint)
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
        }
        printLoopGraphLvl(file, childs[k]->children, lvl + 1, withRegs);
    }
}

int printLoopGraph(const char *fileName, const map<string, vector<LoopGraph*>> &loopGraph, bool withRegs)
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
        printLoopGraphLvl(file, it->second, 1, withRegs);
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}


static void isAllOk(const vector<LoopGraph*> &loops, vector<Messages> &currMessages, set<void*> &isNotOkey, set<wstring> &uniqMessages)
{
    for (int i = 0; i < loops.size(); ++i)
    {
        if (loops[i]->region)
        {            
            if (loops[i]->countOfIters == 0 && loops[i]->region)
            {
                std::wstring bufw;
                __spf_printToLongBuf(bufw, L"Can not calculate count of iterations for this loop, information about iterations in all loops in parallel regions '%s' will be ignored", 
                                     to_wstring(loops[i]->region->GetName()).c_str());

                auto itM = uniqMessages.find(bufw);
                if (itM == uniqMessages.end())
                {
                    uniqMessages.insert(itM, bufw);

                    currMessages.push_back(Messages(NOTE, loops[i]->lineNum, bufw, 1016));
                    __spf_print(1, "Can not calculate count of iterations for loop on line %d, information about iterations in all loops in parallel regions '%s' will be ignored\n", loops[i]->lineNum, loops[i]->region->GetName().c_str());
                }
                isNotOkey.insert(loops[i]->region);
            }
            isAllOk(loops[i]->children, currMessages, isNotOkey, uniqMessages);
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
            setToDefaultCountIter(loops[i]->children, isNotOkey);
        }
    }
}

static void multiplyCountIter(vector<LoopGraph*> &loops, const double allCount)
{
    for (int i = 0; i < loops.size(); ++i)
    {
        loops[i]->countOfIterNested = loops[i]->countOfIters * allCount;
        multiplyCountIter(loops[i]->children, loops[i]->countOfIterNested);
    }
}

static void recAddToChildren(vector<LoopGraph*> &loops, const double coef, map<LoopGraph*, double> &interprocCoefs)
{
    for (auto &loop : loops)
    {
        auto it = interprocCoefs.find(loop);
        if (it == interprocCoefs.end())
            it = interprocCoefs.insert(it, make_pair(loop, 0.0));
        it->second += coef;
        
        recAddToChildren(loop->children, coef, interprocCoefs);
    }
}

static void multiplyCountIterIP(vector<LoopGraph*> &loops, const double allCount, map<LoopGraph*, double> &interprocCoefs)
{
    for (auto &loop : loops)
    {
        const double coef = loop->countOfIters * allCount;
        recAddToChildren(loop->funcChildren, coef, interprocCoefs);
        multiplyCountIterIP(loop->funcChildren, coef, interprocCoefs);
    }
}

static void fillInterprocLinks(const map<string, FuncInfo*> &mapFunc, vector<LoopGraph*> &loops, const map<string, vector<LoopGraph*>> &allLoops)
{
    for (auto &loop : loops)
    {
        set<string> funNames;
        for (auto &call : loop->calls)
            funNames.insert(call.first);

        if (funNames.size())
        {
            for (auto &call : funNames)
            {
                auto it = mapFunc.find(call);
                if (it != mapFunc.end())
                {
                    FuncInfo *currF = it->second;

                    for (auto &loopInFunc : currF->loopsInFunc)
                        loop->funcChildren.push_back(loopInFunc);                    
                }
            }
        }
                
        fillInterprocLinks(mapFunc, loop->children, allLoops);
    }
}

void checkCountOfIter(map<string, vector<LoopGraph*>> &loopGraph, const map<string, vector<FuncInfo*>> &allFuncInfo, map<string, vector<Messages>> &SPF_messages)
{
    set<void*> isNotOkey;
    map<string, FuncInfo*> mapFunc;
    
    createMapOfFunc(allFuncInfo, mapFunc);
    for (auto &loopsInFile : loopGraph)
        fillInterprocLinks(mapFunc, loopsInFile.second, loopGraph);

    for (auto &loopsInFile : loopGraph)
    {
        set<wstring> uniqMessages;

        auto itM = SPF_messages.find(loopsInFile.first);
        if (itM == SPF_messages.end())
            itM = SPF_messages.insert(itM, make_pair(loopsInFile.first, vector<Messages>()));
        isAllOk(loopsInFile.second, itM->second, isNotOkey, uniqMessages);
    }

    if (isNotOkey.size() != 0)
    {
        for (auto &loopsInFile : loopGraph)
            setToDefaultCountIter(loopsInFile.second, isNotOkey);
    }

    for (auto &loopsInFile : loopGraph)
        multiplyCountIter(loopsInFile.second, 1.0);
        
    set<LoopGraph*> linkTo;
    for (auto &loopsInFile : loopGraph)
    {
        for (auto &loop : loopsInFile.second)
        {
            for (auto &ch : loop->children)
                linkTo.insert(ch);
            for (auto &ch : loop->funcChildren)
                linkTo.insert(ch);
        }
    }

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto &loop : linkTo)
        {
            for (auto &ch : loop->children)
            {
                if (linkTo.find(ch) == linkTo.end())
                {
                    linkTo.insert(ch);
                    changed = true;
                }
            }
            for (auto &ch : loop->funcChildren)
            {
                if (linkTo.find(ch) == linkTo.end())
                {
                    linkTo.insert(ch);
                    changed = true;
                }
            }
        }
    }

    set<LoopGraph*> dontLink;
    for (auto &loopsInFile : loopGraph)
        for (auto &loop : loopsInFile.second)
            if (linkTo.find(loop) == linkTo.end())
                dontLink.insert(loop);

    map<LoopGraph*, double> interprocCoefs;
    auto tmpParam = vector<LoopGraph*>(dontLink.begin(), dontLink.end());
    multiplyCountIterIP(tmpParam, 1.0, interprocCoefs);
    
    for (auto &loop : interprocCoefs)
        loop.first->countOfIterNested *= loop.second;
}

static void updateLoopIoAndStopsByFuncCalls(vector<LoopGraph*> &loopGraph, map<string, FuncInfo*> mapFunc)
{
    for (auto &loop : loopGraph)
    {
        vector<pair<pair<string, int>, set<string>>> funNames;
        for (auto &call : loop->calls)
        {
            string currF = call.first;
            set<string> recCalls;
            recCalls.insert(currF);
            bool changed = true;

            while (changed)
            {
                changed = false;
                set<string> local = recCalls;
                for (auto &elem : local)
                {
                    auto itF = mapFunc.find(elem);
                    if (itF != mapFunc.end())
                    {
                        for (auto &toAdd : itF->second->callsFrom)
                        {
                            if (recCalls.find(toAdd) == recCalls.end())
                            {
                                recCalls.insert(toAdd);
                                changed = true;
                            }
                        }
                    }
                }
            }
            funNames.push_back(make_pair(call, recCalls));
        }
        
        if (funNames.size())
        {
            for (auto &calls : funNames)
            {
                const int lineInLoop = calls.first.second;
                for (auto &call : calls.second)
                {
                    auto itF = mapFunc.find(call);
                    if (itF != mapFunc.end())
                    {
                        if (itF->second->linesOfIO.size() != 0)
                        {
                            loop->hasPrints = true;
                            auto it = std::find(loop->linesOfIO.begin(), loop->linesOfIO.end(), lineInLoop);
                            if (it == loop->linesOfIO.end())
                                loop->linesOfIO.push_back(calls.first.second);
                        }
                        if (itF->second->linesOfStop.size() != 0)
                        {
                            loop->hasStops = true;
                            auto it = std::find(loop->linesOfStop.begin(), loop->linesOfStop.end(), lineInLoop);
                            if (it == loop->linesOfStop.end())
                                loop->linesOfStop.push_back(calls.first.second);
                        }
                    }
                }
            }
        }

        updateLoopIoAndStopsByFuncCalls(loop->children, mapFunc);
    }
}

void updateLoopIoAndStopsByFuncCalls(map<string, vector<LoopGraph*>> &loopGraph, const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    map<string, FuncInfo*> mapFunc;
    createMapOfFunc(allFuncInfo, mapFunc);

    for (auto &byFile : loopGraph)
        updateLoopIoAndStopsByFuncCalls(byFile.second, mapFunc);    
}

static void checkArraysMapping(vector<LoopGraph*> &loopList, map<DIST::Array*, vector<int>> flagUse, vector<Messages> &messages, const int topLine, set<DIST::Array*> &checked);
static void fillFromLoop(LoopGraph *loop, map<DIST::Array*, vector<int>> flagUse, vector<Messages> &messages, const int topLine, set<DIST::Array*> &checked)
{
    for (auto &write_op : loop->writeOps)
    {
        DIST::Array *array = write_op.first;
        if (flagUse.find(array) == flagUse.end())
        {
            vector<int> tmp(array->GetDimSize());
            std::fill(tmp.begin(), tmp.end(), 0);
            flagUse[array] = tmp;
            checked.insert(array);
        }

        for (int dim = 0; dim < write_op.second.size(); ++dim)
        {
            for (auto &coef : write_op.second[dim].coefficients)
            {
                if (coef.first.first != 0)
                {
                    flagUse[array][dim]++;
                    break;
                }
            }
        }
    }
    checkArraysMapping(loop->children, flagUse, messages, topLine, checked);
}

static void checkArraysMapping(vector<LoopGraph*> &loopList, map<DIST::Array*, vector<int>> flagUse, 
                               vector<Messages> &messages, const int topLine, set<DIST::Array*> &checked)
{
    if (loopList.size() > 0)
    {
        for (auto &loop : loopList)
            fillFromLoop(loop, flagUse, messages, topLine, checked);
    }
    else
    {
        for (auto &elem : flagUse)
        {
            for (int z = 0; z < elem.second.size(); ++z)
            {
                if (elem.second[z] > 1)
                {
                    if (!elem.first->IsDimDepracated(z))
                    {
                        std::wstring bufw, bufR;
                        __spf_printToLongBuf(bufw, L"Array '%s' can not be distributed due to different writes to %d dimension, this dimension will deprecated",
                                             to_wstring(elem.first->GetShortName()).c_str(), z + 1);
#ifdef _WIN32
                        __spf_printToLongBuf(bufR, L"%d измерение массива '%s' не может быть распределено из-за различных отображений на циклы в операци€х присваиваний",
                                                   z + 1,to_wstring(elem.first->GetShortName()).c_str());
#endif
                        messages.push_back(Messages(ERROR, topLine, bufR, bufw, 1047));
                        elem.first->DeprecateDimension(z);                        
                    }
                }
            }
        }
    }
}

//TODO: need to improve interproc analysis
void checkArraysMapping(map<string, vector<LoopGraph*>> &loopGraph, map<string, vector<Messages>> &SPF_messages, 
                        const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    set<DIST::Array*> checked;
    for (auto &loopByFile : loopGraph)
    {
        auto &messages = getObjectForFileFromMap(loopByFile.first.c_str(), SPF_messages);
        for (auto &loop : loopByFile.second)
        {
            if (loop->children.size() > 0)
            {
                map<DIST::Array*, vector<int>> flagUse;
                fillFromLoop(loop, flagUse, messages, loop->lineNum, checked);
            }
        }
    }

    for (auto &elem : checked)
    {
        if (elem->isAllDeprecated())
        {
            std::wstring bufw, bufR;
            __spf_printToLongBuf(bufw, L"Array '%s' can not be distributed due to all dimensions will deprecated", to_wstring(elem->GetShortName()).c_str());
#ifdef _WIN32
            __spf_printToLongBuf(bufR, L"ћассив '%s' не может быть распределен, так как все его измерени€ запрещены к распределению",
                                        to_wstring(elem->GetShortName()).c_str());
#endif
            for (auto &decl : elem->GetDeclInfo())
                getObjectForFileFromMap(decl.first.c_str(), SPF_messages).push_back(Messages(ERROR, decl.second, bufR, bufw, 1047));
            elem->SetNonDistributeFlag(DIST::SPF_PRIV);
        }
    }    
}

static bool isMapped(const vector<ArrayOp> &allOps)
{
    bool mapped = false;
    for (auto &ops : allOps)
    {
        for (auto &coefs : ops.coefficients)
        {
            if (coefs.first.first != 0)
            {
                mapped = true;
                break;
            }
        }
        if (mapped)
            break;
    }

    return mapped;
}

static void filterArrayInCSRGraph(vector<LoopGraph*> &loops, const map<string, FuncInfo*> &mapFuncInfo, const ParallelRegion *reg, 
                                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls, const map<DIST::Array*, int> &trees,
                                  map<string, vector<Messages>> &messages)
{
    for (auto &loop : loops)
    {
        if (loop->region == reg)
        {
            if (loop->calls.size())
            {
                bool bounds = loop->hasGoto || loop->hasPrints || loop->hasStops || loop->hasUnknownArrayAssigns ||
                              loop->hasNonRectangularBounds || loop->hasIndirectAccess || loop->hasWritesToNonDistribute || loop->hasDifferentAlignRules;

                if (bounds == false )
                {
                    if (loop->usedArrays.size())
                    {
                        set<DIST::Array*> realRefs;
                        for (auto &array : loop->usedArrays)
                            getRealArrayRefs(array, array, realRefs, arrayLinksByFuncCalls);

                        set<DIST::Array*> wasMapped;
                        for (auto &read : loop->readOps)
                        {
                            set<DIST::Array*> readRefs;
                            getRealArrayRefs(read.first, read.first, readRefs, arrayLinksByFuncCalls);

                            if (isMapped(read.second.first))
                                wasMapped.insert(readRefs.begin(), readRefs.end());
                        }

                        for (auto &write : loop->writeOps)
                        {
                            set<DIST::Array*> writeRefs;
                            getRealArrayRefs(write.first, write.first, writeRefs, arrayLinksByFuncCalls);

                            if (isMapped(write.second))
                                wasMapped.insert(writeRefs.begin(), writeRefs.end());
                        }

                        if (wasMapped.size() == 0)
                            filterArrayInCSRGraph(loop->children, mapFuncInfo, reg, arrayLinksByFuncCalls, trees, messages);
                        else
                        {
                            set<DIST::Array*> deprecated;
                            int treeNum = -1;
                            map<int, int> treeNumCount;
                            //filter by graph loop's arrays
                            //TODO
                            for (auto &array : realRefs)
                            {
                                auto itA = trees.find(array);
                                if (itA == trees.end() || itA->second < 0)
                                {
                                    std::wstring bufw, bufR;
                                    __spf_printToLongBuf(bufw, L"Array '%s' can not be distributed", to_wstring(array->GetShortName()).c_str());
#ifdef _WIN32
                                    __spf_printToLongBuf(bufR, L"ћассив '%s' не может быть распределен",
                                                                to_wstring(array->GetShortName()).c_str());
#endif
                                    getObjectForFileFromMap(loop->fileName.c_str(), messages).push_back(Messages(ERROR, loop->lineNum, bufR, bufw, 1047));
                                    deprecated.insert(array);
                                    array->SetNonDistributeFlag(DIST::SPF_PRIV);
                                }
                                else
                                {
                                    if (treeNumCount.find(itA->second) == treeNumCount.end())
                                        treeNumCount[itA->second] = 1;
                                    else
                                        treeNumCount[itA->second]++;
                                }
                            }

                            if (treeNumCount.size() == 0)
                                continue;

                            auto itT = treeNumCount.begin();
                            treeNum = itT->first;
                            int countT = itT->second;
                            itT++;
                            for (; itT != treeNumCount.end(); itT++)
                            {
                                if (itT->second > countT)
                                {
                                    countT = itT->second;
                                    treeNum = itT->first;
                                }
                            }
                            
                            for (auto &array : realRefs)
                            {
                                auto itA = trees.find(array);
                                if (itA == trees.end() || itA->second != treeNum)
                                {
                                    std::wstring bufw, bufR;
                                    __spf_printToLongBuf(bufw, L"Array '%s' can not be distributed", to_wstring(array->GetShortName()).c_str());
#ifdef _WIN32
                                    __spf_printToLongBuf(bufR, L"ћассив '%s' не может быть распределен",
                                                               to_wstring(array->GetShortName()).c_str());
#endif
                                    getObjectForFileFromMap(loop->fileName.c_str(), messages).push_back(Messages(ERROR, loop->lineNum, bufR, bufw, 1047));
                                    deprecated.insert(array);
                                    array->SetNonDistributeFlag(DIST::SPF_PRIV);
                                }
                            }

                            set<DIST::Array*> inCalls;
                            for (auto &call : loop->calls)
                            {
                                auto itF = mapFuncInfo.find(call.first);
                                if (itF != mapFuncInfo.end())
                                    inCalls.insert(itF->second->allUsedArrays.begin(), itF->second->allUsedArrays.end());
                            }

                            for (auto &inCall : inCalls)
                            {
                                if (realRefs.find(inCall) == realRefs.end() && deprecated.find(inCall) == deprecated.end())
                                {
                                    bool needToDeprecated = false;
                                    if (trees.find(inCall) == trees.end())
                                        needToDeprecated = true;
                                    else
                                    {
                                        if (trees.find(inCall)->second != treeNum)
                                            needToDeprecated = true;
                                    }
                                    if (needToDeprecated)
                                    {
                                        std::wstring bufw, bufR;
                                        __spf_printToLongBuf(bufw, L"Array '%s' can not be distributed", to_wstring(inCall->GetShortName()).c_str());
#ifdef _WIN32
                                        __spf_printToLongBuf(bufR, L"ћассив '%s' не может быть распределен",
                                                                    to_wstring(inCall->GetShortName()).c_str());
#endif
                                        getObjectForFileFromMap(loop->fileName.c_str(), messages).push_back(Messages(ERROR, loop->lineNum, bufR, bufw, 1047));
                                        deprecated.insert(inCall);
                                        inCall->SetNonDistributeFlag(DIST::SPF_PRIV);
                                    }
                                }
                            }
                        }
                    }
                }
                else
                    filterArrayInCSRGraph(loop->children, mapFuncInfo, reg, arrayLinksByFuncCalls, trees, messages);
            }
        }
    }
}

void filterArrayInCSRGraph(map<string, vector<LoopGraph*>> &loopGraph, map<string, vector<FuncInfo*>> &allFuncs, 
                           ParallelRegion *reg, const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                           map<string, vector<Messages>> &messages)
{
    map<string, FuncInfo*> mapFuncInfo;
    map<DIST::Array*, int> trees;
 
    auto arrays = reg->GetAllArrays().GetArrays();
    int count = 0;
    for (auto &array : arrays)
    {
        if (!array->isLoopArray() && !array->isTemplate() && array->GetLocation().first != DIST::l_PARAMETER)
            count++;
    }
    if (count <= 1)
        return;

    reg->GetGraphToModify().FindAllArraysTrees(trees, reg->GetAllArrays());
    createMapOfFunc(allFuncs, mapFuncInfo);

    if (trees.size())
        for (auto &byFile : loopGraph)
            filterArrayInCSRGraph(byFile.second, mapFuncInfo, reg, arrayLinksByFuncCalls, trees, messages);
}