#include "../Utils/leak_detector.h"

#include <algorithm>
#include <string>
#include <assert.h>
#include <chrono>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include <limits.h>

#if _WIN32 && NDEBUG
#include <boost/thread.hpp>
extern int passDone;
#endif

#include "Cycle.h"
#include "Arrays.h"
#include "Array.h"
#include "../Utils/errors.h"
#include "../Utils/utils.h"

#include "GraphCSR.h"

using std::vector;
using std::queue;
using std::map;
using std::set;
using std::pair;
using std::make_pair;
using std::tuple;
using std::string;
using std::wstring;
using namespace std::chrono;

enum { WHITE, GREY, BLACK };
enum { CONFLICT_TYPE_1, CONFLICT_TYPE_2 };

#define MIN_CYCLE_DIM 2
#define PRINT_TIMES   1

namespace Distribution
{
    template<typename vType, typename wType, typename attrType>
    vType GraphCSR<vType, wType, attrType>::
          GetLocalVNum(const vType &V, bool &ifNew)
    {
        vType localV;
        if (V >= (vType)localIdx.size())
        {
            localV = lastNumOfV;
            if ((vType)localIdx.size() <= V)
            {
                vType oldSize = (vType)localIdx.size();
                localIdx.resize(V + 1);
                for (vType i = oldSize; i < (vType)localIdx.size(); ++i)
                    localIdx[i] = -1;
            }
            localIdx[V] = localV;
            globalIdx.push_back(V);
            lastNumOfV++;
            ifNew = true;
        }
        else
        {
            if (localIdx[V] == -1)
            {
                localV = lastNumOfV;
                lastNumOfV++;
                localIdx[V] = localV;
                globalIdx.push_back(V);
                ifNew = true;
            }
            else
            {
                localV = localIdx[V];
                ifNew = false;
            }
        }

        return localV;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         AddEdgeToGraph(const vType &V1, const vType &V2, const wType &W, const attrType &attr, const bool &ifNew, const uint8_t linkType_)
    {
        if (!ifNew)
        {
            for (vType i = V1 + 1; i < numVerts + 1; ++i)
                neighbors[i]++;
        }
        else
        {
            if (neighbors.size() == 0)
            {
                neighbors.push_back(0);
                neighbors.push_back(1);
            }
            else
                neighbors.push_back(neighbors.back() + 1);
            numVerts++;
        }

        edges.insert(edges.begin() + neighbors[V1], V2);
        weights.insert(weights.begin() + neighbors[V1], W);
        attributes.insert(attributes.begin() + neighbors[V1], attr);
        linkType.insert(linkType.begin() + neighbors[V1], linkType_);
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         IncreaseWeight(const int &idx, const int &idxRev, const wType &W)
    {
        weights[idx] += W;
        weights[idxRev] += W;
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
         CheckExist(const vType &V1, const vType &V2, const attrType &attr, const bool &ifNew, const uint8_t &linkTypeIn)
    {
        int ifExist = -1;
        if (!ifNew)
        {
            auto currNeigh = neighbors.data();
            auto currEdges = edges.data();
            auto currAttr = attributes.data();
            auto currLinks = linkType.data();

            for (vType i = currNeigh[V1]; i < currNeigh[V1 + 1]; ++i)
            {
                const vType k = currEdges[i];
                if (k == V2 && attr == currAttr[i] && linkTypeIn == currLinks[i])
                {
                    ifExist = (int)i;
                    break;
                }
            }
        }
        return ifExist;
    }

    //old algorithm without sort in the fly
    //TODO: need to update
    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         FindLoop(vector<Cycle<vType, wType, attrType>> &cycles, const vType V, const vType VPrev)
    {
        /*color[V] = GREY;
        for (vType i = neighbors[V]; i < neighbors[V + 1]; ++i)
        {
            vType k = edges[i];
            if (k == VPrev)
                continue;

            if (color[k] == WHITE)
            {
                activeV.push_back(k);
                activeArcs.push_back(make_pair(weights[i], attributes[i]));

                FindLoop(cycles, k, V);

                activeV.pop_back();
                activeArcs.pop_back();
            }
            else if (color[k] == GREY && k == findFrom)
            {
                activeArcs.push_back(make_pair(weights[i], attributes[i]));

                auto idx = activeV.end();
                auto idxVal = activeArcs.end();
                Cycle<vType, wType, attrType> newLoop;

                idx--;
                idxVal--;
                vType last = globalIdx[k];
                while (*idx != k)
                {
                    newLoop.AddArc(last, globalIdx[*idx], (*idxVal), 0);
                    last = globalIdx[*idx];
                    idxVal--;
                    idx--;
                }
                newLoop.AddArc(last, globalIdx[k], (*idxVal), 0);
                cycles.push_back(newLoop);
                //cyclesNum++;
                activeArcs.pop_back();
            }
        }
        color[V] = WHITE;*/
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         FindLoop(vector<map<vector<unsigned>, Cycle<vType, wType, attrType>>> &cycles,
                  const vType V, const vType VPrev, const vector<vType> &numbers)
    {
        if (activeCounter > maxChainLen)
            return;

        color[V] = GREY;
#if _WIN32 && NDEBUG
        if (passDone == 2)
            throw boost::thread_interrupted();
#endif

        for (vType i = neighbors[V]; i < neighbors[V + 1]; ++i)
        {
            vType k = edges[i];
            if (k == VPrev)
                continue;

            if (color[k] == WHITE)
            {
                activeV[activeCounter] = k;
                activeE[activeCounter] = numbers[i];
                activeArcs[activeCounter] = make_pair(weights[i], attributes[i]);
                activeCounter++;

                FindLoop(cycles, k, V, numbers);

                activeCounter--;
            }
            else if (color[k] == GREY && k == findFrom)
            {
                activeArcs[activeCounter] = make_pair(weights[i], attributes[i]);
                activeE[activeCounter] = numbers[i];


                int idx = activeCounter - 1;
                int idxE = activeCounter;
                int idxVal = activeCounter;
                Cycle<vType, wType, attrType> newLoop;

                vector<unsigned> shortBitLoop(numEdges / (2 * 32) + 1);
                vType last = k;
                //int dim = 0;
                while (activeV[idx] != k)
                {
                    //dim++;
                    const unsigned position = activeE[idxE];
                    shortBitLoop[position / 32] |= (1 << (position % 32));

                    newLoop.AddArc(activeV[idx], last, activeArcs[idxVal], position);
                    last = activeV[idx];

                    idxVal--;
                    idxE--;
                    idx--;
                }
                //dim++;
                const unsigned position = activeE[idxE];
                shortBitLoop[position / 32] |= (1 << (position % 32));

                newLoop.AddArc(k, last, activeArcs[idxVal], position);
                const int currDimSize = newLoop.GetNumArcs();

                if (currDimSize <= maxLoopDim)
                {
                    auto itFound = cycles[currDimSize].find(shortBitLoop);
                    if (itFound == cycles[currDimSize].end())
                    {
                        usedMem += sizeof(unsigned) * shortBitLoop.capacity() + newLoop.getFullSize() + sizeof(void*);
                        if (usedMem > maxAvailMemory && maxAvailMemory > 0)
                        {
                            printf("used %lld maxAvail %lld\n", usedMem, maxAvailMemory);
                            fflush(NULL);
                            throw -2;
                        }
                        cycles[currDimSize].insert(itFound, make_pair(shortBitLoop, newLoop));
                    }
                }
            }
        }
        color[V] = WHITE;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         RemoveDuplicates(vector<Cycle<vType, wType, attrType>> &cycles)
    {
        auto timeR = steady_clock::now();
        __spf_print(PRINT_TIMES, "PROF: RemoveDuplicates: start removing with %d cycles\n", (int)cycles.size());

        vector<vector<pair<pair<vType, vType>, attrType>>> allUniqEdges(cycles.size());
        //map<int, int> sizes;
        vector<int> parts;
        parts.push_back(0);
        int lastSize = cycles[0].GetNumArcs();

        int maxSize = 0;
        for (vType i = 0; i < (vType)cycles.size(); ++i)
        {
            if (lastSize != cycles[i].GetNumArcs())
            {
                parts.push_back(i);
                lastSize = cycles[0].GetNumArcs();
            }
            //sizes[cycles[i].GetNumArcs()]++;
            maxSize = std::max(maxSize, cycles[i].GetNumArcs());
            const vector<pair<vType, vType>> &currUniqArcs = cycles[i].GetArcs();
            const vector<attrType> &currUniqAttrArcs = cycles[i].GetAttributesArcs();

            for (vType m = 0; m < (vType)currUniqArcs.size(); ++m)
                allUniqEdges[i].push_back(make_pair(currUniqArcs[m], currUniqAttrArcs[m]));

            //TODO: remove multiple arcs
            std::sort(allUniqEdges[i].begin(), allUniqEdges[i].end());
        }
        parts.push_back((int)cycles.size());
        /*for (map<int, int>::iterator it = sizes.begin(); it != sizes.end(); it++)
        printf("%d: %d\n", it->first, it->second);*/

        maxSize++;
        vector<vector<vType>> uniqLoops(maxSize);
        __spf_print(PRINT_TIMES, "PROF: RemoveDuplicates: done inserting\n");

        const vType part = vType((vType)cycles.size() * 0.1);
        auto timeT = steady_clock::now();
        //#pragma omp parallel for schedule(dynamic)
        for (int p = 0; p < (int)parts.size() - 1; ++p)
        {
            for (vType it = parts[p]; it < parts[p + 1]; ++it)
            {
                if (it % part == 0 && PRINT_TIMES)
                {
                    auto timeT1 = steady_clock::now();
                    __spf_print(PRINT_TIMES, "PROF: %d done with time %.3f sec\n", it, (duration_cast<duration<double>>(timeT1 - timeT)).count());
                    timeT = timeT1;
                }

                const int dimention = cycles[it].GetNumArcs();
                if (uniqLoops[dimention].size() == 0)
                    uniqLoops[dimention].push_back(it);
                else
                {
                    const vector<pair<vType, vType>> &currArcs = cycles[it].GetArcs();
                    const vector<attrType> &currAttrArcs = cycles[it].GetAttributesArcs();

                    bool uniq = true;
                    for (int k = (int)uniqLoops[dimention].size() - 1; k >= 0; --k)
                    {
                        const vector<pair<pair<vType, vType>, attrType>> &edgesUniq = allUniqEdges[uniqLoops[dimention][k]];
                        bool sameAll = true;
                        for (vType m = 0; m < (vType)currArcs.size(); ++m)
                        {
                            pair<vType, vType> revCurrArcs = make_pair(currArcs[m].second, currArcs[m].first);
                            /*bool notFound = (edgesUniq.find(make_pair(currArcs[m], currAttrArcs[m])) == edgesUniq.end()) &&
                            (edgesUniq.find(make_pair(revCurrArcs, currAttrArcs[m])) == edgesUniq.end());*/
                            /*bool notFound = (find(edgesUniq.begin(), edgesUniq.end(), (make_pair(currArcs[m], currAttrArcs[m]))) == edgesUniq.end()) &&
                            (find(edgesUniq.begin(), edgesUniq.end(), (make_pair(revCurrArcs, currAttrArcs[m]))) == edgesUniq.end());*/

                            const pair<pair<vType, vType>, attrType> f1 = make_pair(currArcs[m], currAttrArcs[m]);
                            const pair<pair<vType, vType>, attrType> f2 = make_pair(revCurrArcs, currAttrArcs[m]);
                            bool notFound = true;
                            for (int t = 0; t < (int)edgesUniq.size(); ++t)
                            {
                                if (edgesUniq[t] == f1 || edgesUniq[t] == f2)
                                {
                                    notFound = false;
                                    break;
                                }
                            }

                            if (notFound)
                            {
                                sameAll = false;
                                break;
                            }
                        }

                        if (sameAll)
                        {
                            uniq = false;
                            break;
                        }
                    }

                    if (uniq)
                        uniqLoops[dimention].push_back(it);
                }
            }
        }

        vector<Cycle<vType, wType, attrType>> newLoops;
        for (vType k = 0; k < maxSize; ++k)
            for (vType i = 0; i < (vType)uniqLoops[k].size(); ++i)
                newLoops.push_back(cycles[uniqLoops[k][i]]);

        cycles = newLoops;
        __spf_print(PRINT_TIMES, "PROF: RemoveDuplicates: done removing with %d cycles, time %f sec\n", (int)cycles.size(), (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
    }

    template<typename vType, typename wType, typename attrType>
    bool GraphCSR<vType, wType, attrType>::
         findLink(const vType v1, pair<int, int> &inGraphAttr1, const vType v2, pair<int, int> &inGraphAttr2)
    {
        bool wasFound = false;
        for (int k = neighbors[v1]; k < neighbors[v1 + 1]; ++k)
        {
            const vType currV = edges[k];
            if (currV == v2)
            {
                wasFound = true;
                inGraphAttr2 = attributes[k].second;
                inGraphAttr1 = attributes[k].first;
                break;
            }
        }

        if (wasFound)
            return true;
        else
        {
            for (int k = neighbors[v1]; k < neighbors[v1 + 1]; ++k)
            {
                if (color[edges[k]] == 1)
                    continue;

                color[edges[k]] = 1;
                wasFound = findLink(edges[k], inGraphAttr1, v2, inGraphAttr2);

                if (wasFound)
                {
                    inGraphAttr1 = attributes[k].first;
                    break;
                }
            }
        }
        return wasFound;
    }
    
    pair<int, int> Fx(const pair<int, int> &x, const pair<int, int> &F)
    {
        return make_pair(x.first * F.first, x.second * F.first + F.second);
    }

    static pair<double, double> Fx(const pair<double, double> &x, const pair<double, double> &F)
    {
        return make_pair(x.first * F.first, x.second * F.first + F.second);
    }

    static pair<RationalNum, RationalNum> Fx(const pair<RationalNum, RationalNum> &x, const pair<RationalNum, RationalNum> &F)
    {
        return make_pair(x.first * F.first, x.second * F.first + F.second);
    }

    template<typename vType, typename wType, typename attrType>
    bool GraphCSR<vType, wType, attrType>::
        hasLinkWithTempate(const vType root, const Arrays<vType> &allArrays, bool increaseLink, int newValue)
    {
        set<vType> next = { root };
        set<vType> done;
        
        bool found = false;
        while (next.size())
        {
            set<vType> nextLoc;
            for (auto &v1 : next)
            {
                Array *tmp = allArrays.GetArrayByVertex(globalIdx[v1]);
                if (tmp)
                {
                    if (tmp->IsTemplate())
                    {
                        found = true;
                        if (increaseLink)
                        {
                            if (neighbors[v1 + 1] - neighbors[v1] != 1)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            const int k = neighbors[v1];

                            const vType edgeV = edges[k];
                            if (newValue == 0)
                                attributes[k].first.first++;
                            else
                                attributes[k].first.first = newValue;

                            bool done = false;
                            for (int z = neighbors[edgeV]; z < neighbors[edgeV + 1]; ++z)
                            {
                                const vType currV = edges[z];
                                if (currV == v1)
                                {
                                    if (newValue == 0)
                                        attributes[z].second.first++;
                                    else
                                        attributes[z].second.first = newValue;
                                    done = true;
                                    break;
                                }
                            }
                            if (!done)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                        break;
                    }
                }

                for (int k = neighbors[v1]; k < neighbors[v1 + 1]; ++k)
                {
                    const vType currV = edges[k];

                    auto it = done.find(currV);
                    if (it == done.end())
                    {
                        done.insert(it, currV);
                        nextLoc.insert(currV);
                    }
                }
            }
            next = nextLoc;
        }
        return found;
    }

    template<typename vType, typename wType, typename attrType>
    pair<RationalNum, RationalNum> GraphCSR<vType, wType, attrType>::
        findLinkWithTempate2(const vType v1, int &templV, Array *&templ, const Arrays<vType> &allArrays, set<vType> wasDone)
    {
        const pair<RationalNum, RationalNum> nulPair = make_pair(0, 0);

        wasDone.insert(v1);
        bool wasFound = false;
        for (int k = neighbors[v1]; k < neighbors[v1 + 1]; ++k)
        {
            const vType currV = edges[k];
            Array *tmp = allArrays.GetArrayByVertex(globalIdx[currV]);
            if (tmp)
            {
                if (tmp->IsTemplate())
                {
                    wasFound = true;

                    templV = globalIdx[currV];
                    templ = tmp;
                    return make_pair(attributes[k].second.first, attributes[k].second.second);
                    //return make_pair(1.0f, 0.0f);
                }
            }
        }

        auto it = cacheLinks.find(v1);
        if (it == cacheLinks.end())
            it = cacheLinks.insert(it, make_pair(v1, map<vType, tuple<int, Array*, pair<RationalNum, RationalNum>>>()));

        for (int k = neighbors[v1]; k < neighbors[v1 + 1]; ++k)
        {
            if (wasDone.find(edges[k]) != wasDone.end())
                continue;
            
            auto ruleCache = it->second.find(edges[k]);

            pair<RationalNum, RationalNum> ruleToTemplate;
            if (ruleCache == it->second.end())
            {
                ruleToTemplate = findLinkWithTempate2(edges[k], templV, templ, allArrays, wasDone);
                it->second.insert(ruleCache, make_pair(edges[k], make_tuple(templV, templ, ruleToTemplate)));
            }
            else
            {
                templV = std::get<0>(ruleCache->second);
                templ = std::get<1>(ruleCache->second);
                ruleToTemplate = std::get<2>(ruleCache->second);
            }

            if (ruleToTemplate != nulPair)
            {
                auto currAttribute = attributes[k];
                pair<RationalNum, RationalNum> left = currAttribute.first;
                pair<RationalNum, RationalNum> right = currAttribute.second;

                // calculate transition
                pair<RationalNum, RationalNum> X;
                X.first = right.first / left.first;

                left.first *= X.first;
                left.second *= X.first;

                X.second = right.second - left.second;

                return Fx(X, ruleToTemplate);
            }
        }
        
        return nulPair;
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        findDimNumLink(const vType v, const Array *to, const Arrays<vType> &allArrays, set<vType> &wasDone) const
    {
        int foundD = -1;
        int err = -1;
        for (int k = neighbors[v]; k < neighbors[v + 1]; ++k)
        {
            const vType currV = edges[k];
            err = allArrays.GetDimNumber(to, globalIdx[currV], foundD);
            if (err != -1)
                break;
        }

        if (err != -1)
            return foundD;
        else
        {
            for (int k = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                const vType currV = edges[k];
                if (wasDone.find(currV) != wasDone.end())
                    continue;

                wasDone.insert(v);
                foundD = findDimNumLink(currV, to, allArrays, wasDone);
                auto itToErase = wasDone.find(v);
                if (itToErase != wasDone.end())
                    wasDone.erase(itToErase);

                if (foundD != -1)
                    break;
            }
            return foundD;
        }
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        AddToGraph(const vType &V1, const vType &V2, const wType &W, const attrType &attr, const uint8_t linkType)
    {
        if (V1 == V2)
            return -1;

        countRequestsToAdd++;

        vType localV1, localV2;
        bool ifNew1, ifNew2;
        localV1 = GetLocalVNum(V1, ifNew1);
        localV2 = GetLocalVNum(V2, ifNew2);
        attrType attrRev = make_pair(attr.second, attr.first);


        int idxExist = -1, idxExistRev = -1;

        idxExist = CheckExist(localV1, localV2, attr, ifNew1, linkType);
        idxExistRev = CheckExist(localV2, localV1, attrRev, ifNew2, linkType);

        bool ifExist = (idxExist != -1) && (idxExistRev != -1);

        int status = 0;
        if (!ifExist)
        {
            AddEdgeToGraph(localV1, localV2, W, attr, ifNew1, linkType);
            AddEdgeToGraph(localV2, localV1, W, attrRev, ifNew2, linkType);
            numEdges += 2;
            countMissToAdd++;
        }
        else
        {
            IncreaseWeight(idxExist, idxExistRev, W);
            status = 1;
        }

        return status;
    }

    template<typename vType, typename wType, typename attrType>
    set<vType> GraphCSR<vType, wType, attrType>::
        FindTrees(vector<vType> &inTree, vector<vector<vType>> &vertByTrees)
    {
        inTree.resize(numVerts);
        for (int i = 0; i < numVerts; ++i)
            inTree[i] = i;
                
        while (true)
        {
            bool mod = false;
            for (int i = 0; i < numVerts; ++i)
            {
                for (int k = neighbors[i]; k < neighbors[i + 1]; ++k)
                {
                    const vType V = edges[k];
                    if (inTree[i] != inTree[V])
                    {
                        mod = true;
                        if (inTree[i] < inTree[V])
                            inTree[V] = inTree[i];
                        else
                            inTree[i] = inTree[V];
                    }
                }
            }
            if (!mod)
                break;
        }

        set<vType> allTrees;
        for (int i = 0; i < numVerts; ++i)
            allTrees.insert(inTree[i]);
        
        map<vType, vType> newIdx;
        int idx = 0;
        for (auto it = allTrees.begin(); it != allTrees.end(); ++it, ++idx)
            newIdx.insert(make_pair(*it, idx));

        vertByTrees.resize(allTrees.size());
        for (int i = 0; i < numVerts; ++i)
            vertByTrees[newIdx[inTree[i]]].push_back(i);
        return allTrees;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         GetAllSimpleLoops(vector<vector<Cycle<vType, wType, attrType>>> &cycles, bool needPrint, bool useSavedQuality)
    {        
        //cyclesNum = 0;
        if (!useSavedQuality)
            treesQuality.clear();
        cycles.clear();
        color.resize(numVerts);
        activeCounter = 0;

        activeV = new vType[std::max(numVerts, numEdges) + 1];
        activeE = new vType[std::max(numVerts, numEdges) + 1];
        activeArcs = new pair<wType, attrType>[std::max(numVerts, numEdges) + 1];

        map<tuple<pair<vType, vType>, wType, attrType>, int> uniqArcs;
        vector<vType> numbers(edges.size());
        int num = 0;

        for (int i = 0; i < numVerts; ++i)
        {
            for (int k = neighbors[i]; k < neighbors[i + 1]; ++k)
            {
                const vType V = edges[k];
                attrType reverse = make_pair(attributes[k].second, attributes[k].first);
                tuple<pair<vType, vType>, wType, attrType> tmp = std::make_tuple(make_pair(i, V), weights[k], attributes[k]);
                tuple<pair<vType, vType>, wType, attrType> tmp1 = std::make_tuple(make_pair(V, i), weights[k], reverse);
                auto it = uniqArcs.find(tmp);
                if (it == uniqArcs.end())
                {
                    numbers[k] = num;
                    uniqArcs[tmp] = num;
                    uniqArcs[tmp1] = num;
                    num++;
                }
                else
                    numbers[k] = it->second;
            }
        }
        int maxNum = 0;
        for (int i = 0; i < numEdges; ++i)
            maxNum = std::max(maxNum, numbers[i]);
        __spf_print(PRINT_TIMES && needPrint, "max num value = %d\n", maxNum);
        
        auto timeFind = steady_clock::now();
        __spf_print(PRINT_TIMES && needPrint, "graph size: |V| = %d, |E| = %d, quality: [%d, %d]\n", numVerts, numEdges / 2, maxLoopDim, maxChainLen);
        if (maxNum + 1 != numEdges / 2 && maxNum != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        
        if (numVerts == 0 && numEdges == 0)
            return;

        vector<vType> trees;
        vector<vector<vType>> vertByTrees;
        set<vType> unqieTrees = FindTrees(trees, vertByTrees);        
        __spf_print(PRINT_TIMES && needPrint, "trees count %d\n", (int)unqieTrees.size());
        
        if (unqieTrees.size() == 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        vector<vector<map<vector<unsigned>, Cycle<vType, wType, attrType>>>> cyclesTmp(unqieTrees.size());
        usedMem = 0;
        for (int i = 0; i < unqieTrees.size(); ++i)
        {
            cyclesTmp[i].resize(numVerts + 1);
            usedMem += cyclesTmp[i].capacity() * sizeof(map<vector<unsigned>, Cycle<vType, wType, attrType>>);
        }

        __spf_print(PRINT_TIMES && needPrint, "cycles find started\n");
        // find all cycles with dim >= 3
        try
        {
            for (int t = 0; t < vertByTrees.size(); ++t)
            {
                const int vertArraySize = vertByTrees[t].size();
                int wasMaxChainLen = maxChainLen;
                int wasMaxLoopDim = maxLoopDim;

                int newQuality = vertArraySize * maxLoopDim / 100;
                int newSpeed = vertArraySize * maxChainLen / 100;

                if (newQuality < 3) newQuality = 3;
                if (newSpeed < 3)   newSpeed = 3;

                if (!useSavedQuality)
                {
                    maxLoopDim = newQuality;
                    maxChainLen = newSpeed;

                    treesQuality.push_back(make_pair(maxLoopDim, maxChainLen));
                }
                else
                {
                    if (t < treesQuality.size())
                    {
                        maxLoopDim = treesQuality[t].first;
                        maxChainLen = treesQuality[t].second;
                    }
                    else
                    {
                        maxLoopDim = newQuality;
                        maxChainLen = newSpeed;
                    }
                }

                if (needPrint)
                    printf("SAPFOR: [TREE %d], arrays num %d, maxLoopDim %d, maxChainLen %d\n", t, vertArraySize, maxLoopDim, maxChainLen);

#ifdef _WIN32
                wstring treeM;
                if (needPrint)
                    treeM = std::to_wstring(t + 1) + L"/" + std::to_wstring(vertByTrees.size());
#endif
                for (int k = 0; k < vertByTrees[t].size(); ++k)
                {
                    const vType i = vertByTrees[t][k];
                    const vType currentV = i;
                    for (vType k = 0; k < numVerts; ++k)
                        color[k] = WHITE;

                    findFrom = currentV;
#ifdef _WIN32
                    if (needPrint)
                    {
                        wstring vertexM = std::to_wstring(k + 1) + L"/" + std::to_wstring(vertByTrees[t].size());
                        sendMessage_2lvl(wstring(L"поиск простых циклов в графе, обработка дерева ") + wstring(treeM.begin(), treeM.end()) + L" вершины " + wstring(vertexM.begin(), vertexM.end()));
                    }
#endif
                    __spf_print(PRINT_TIMES && needPrint, "v (tree %d) = %d (with neighb %d) ", t, i, neighbors[i + 1] - neighbors[i]);
                    activeV[activeCounter++] = currentV;
                    FindLoop(cyclesTmp[t], currentV, currentV, numbers);
                    activeCounter--;
                    __spf_print(PRINT_TIMES && needPrint, "done with time %f\n", (duration_cast<duration<double>>(steady_clock::now() - timeFind)).count());
                }
                maxChainLen = wasMaxChainLen;
                maxLoopDim = wasMaxLoopDim;
            }
#ifdef _WIN32
            if (needPrint)
                sendMessage_2lvl(L"");
#endif
        }
        catch (int code)
        {
            if (code == -2)
                __spf_print(1, "OUT OF MEMORY: max avail %lld\n", maxAvailMemory);
            throw code;
        }

        int minSize = INT_MAX;
        int maxSize = 0;

        map<int, int> countOfCycles;
        cycles.resize(vertByTrees.size());
        for (int t = 0; t < vertByTrees.size(); ++t)
        {
            map<int, int> countOfCyclesTree;
            for (int i = 0; i < cyclesTmp[t].size(); ++i)
                for (auto k = cyclesTmp[t][i].begin(); k != cyclesTmp[t][i].end(); ++k)
                {
                    cycles[t].push_back(k->second);
                    const int len = k->second.GetNumArcs();
                    minSize = std::min(minSize, len);
                    maxSize = std::max(maxSize, len);
                    {
                        auto itF = countOfCycles.find(len);
                        if (itF == countOfCycles.end())
                            itF = countOfCycles.insert(itF, make_pair(len, 0));
                        itF->second++;
                    }

                    {
                        auto itF = countOfCyclesTree.find(len);
                        if (itF == countOfCyclesTree.end())
                            itF = countOfCyclesTree.insert(itF, make_pair(len, 0));
                        itF->second++;
                    }
                }


            __spf_print(PRINT_TIMES && needPrint, "FOR TREE %d\n", t);
            for (auto it = countOfCyclesTree.begin(); it != countOfCyclesTree.end(); ++it)
                __spf_print(PRINT_TIMES && needPrint, "  found cycles with size %d = %d\n", it->first, it->second);
        }

        int allCycles = 0;
        for (auto it = countOfCycles.begin(); it != countOfCycles.end(); ++it)
        {
            __spf_print(PRINT_TIMES && needPrint, "found cycles with size %d = %d\n", it->first, it->second);
            allCycles += it->second;
        }

        delete []activeV;
        delete []activeE;
        delete []activeArcs;

        __spf_print(PRINT_TIMES && needPrint, "PROF: num cycles %d, time of find %f s\n", allCycles, (duration_cast<duration<double>>(steady_clock::now() - timeFind)).count());
        __spf_print(PRINT_TIMES && needPrint, "PROF: minimum cycle size %d, maximum cycle size %d\n", minSize, maxSize);
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        SortLoopsBySize(vector<Cycle<vType, wType, attrType>> &cycles, bool needPrint)
    {
        auto timeR = steady_clock::now();
        __spf_print(PRINT_TIMES && needPrint, "PROF: SortLoopsBySize: start\n");
        int err = 0;
        vector<Cycle<vType, wType, attrType>> sortedLoops(cycles.size());
        int currIdx = 0;
        for (vType g = MIN_CYCLE_DIM; g <= numVerts; ++g)
        {
            for (vType i = 0; i < (vType)cycles.size(); ++i)
            {
                if (g == cycles[i].GetNumArcs())
                {
                    sortedLoops[currIdx] = cycles[i];
                    currIdx++;
                }
            }
        }

        if (cycles.size() != currIdx)
        {
            char buf[256];
            sprintf(buf, "Can not sort cycles");
            addToGlobalBufferAndPrint(buf);

            err = -1;
        }
        else
            cycles = sortedLoops;
        __spf_print(PRINT_TIMES && needPrint, "PROF: SortLoopsBySize: end %f sec\n", (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
        return err;
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        SortLoopsByWeight(vector<Cycle<vType, wType, attrType>> &cycles, bool needPrint)
    {
        auto timeR = steady_clock::now();
        __spf_print(PRINT_TIMES && needPrint, "PROF: SortLoopsByWeight: start\n");

        if (cycles.size() == 0)
        {
            __spf_print(PRINT_TIMES && needPrint, "PROF: SortLoopsByWeight: end %f sec\n", (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
            return 0;
        }

        int err = 0;
        vector<Cycle<vType, wType, attrType>> sortedLoops;
        vType start = 0, end = 1;
        vType dim = MIN_CYCLE_DIM;
        for (vType i = 1; i < (vType)cycles.size(); ++i, ++end)
        {
            if (cycles[i].GetNumArcs() != dim)
            {
                sort(cycles.begin() + start, cycles.begin() + end);

                start = end;
                dim = cycles[i].GetNumArcs();
            }
        }
        if (start != end)
            sort(cycles.begin() + start, cycles.begin() + end);
        __spf_print(PRINT_TIMES && needPrint, "PROF: SortLoopsByWeight: end %f sec\n", (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
        return err;
    }

#define WITH_CONFLICT_1 1
#define WITH_CONFLICT_2 1
    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        GetConflictCycles(const vector<Cycle<vType, wType, attrType>> &cycles,
                          const Arrays<vType> &allArrays,
                          vector<pair<int, int>> &indexOfConflict, bool needPrint)
    {
        auto timeR = steady_clock::now();
        __spf_print(PRINT_TIMES && needPrint, "PROF: GetConflictCycles: start\n");

        int countOfConflict = 0;
        indexOfConflict.clear();

        const set<Array*> &arrays = allArrays.GetArrays();
        vector<bool> cycleMarked(cycles.size());

        for (vType i = 0; i < (vType)cycles.size(); ++i)
        {
            cycleMarked[i] = false;

#if WITH_CONFLICT_1
            const vector<pair<vType, vType>> &currArcs = cycles[i].GetArcs();
            // check conflict of first type
            map<Array*, set<vType>> uniqInfo;
            for (int i1 = 0; i1 < (int)currArcs.size(); ++i1)
            {
                pair<int, Array*> info;
                int ok = allArrays.GetInfoByVertex(globalIdx[currArcs[i1].first], info);
                if (ok == 0)
                {
                    auto it = uniqInfo.find(info.second);
                    if (it == uniqInfo.end())
                        uniqInfo.insert(it, make_pair(info.second, set<vType>()));
                    it->second.insert(info.first);
                }

                ok = allArrays.GetInfoByVertex(globalIdx[currArcs[i1].second], info);
                if (ok == 0)
                {
                    auto it = uniqInfo.find(info.second);
                    if (it == uniqInfo.end())
                        uniqInfo.insert(it, make_pair(info.second, set<vType>()));
                    it->second.insert(info.first);
                }
            }

            for (auto tmpIt = uniqInfo.begin(); tmpIt != uniqInfo.end(); ++tmpIt)
            {
                if (tmpIt->second.size() > 1)
                {
                    indexOfConflict.push_back(make_pair(i, CONFLICT_TYPE_1));
                    countOfConflict++;
                    cycleMarked[i] = true;
                    break;
                }
            }
#endif

#if WITH_CONFLICT_2
            // check conflict of second type
            if (!cycleMarked[i])
            {
                const vector<pair<vType, vType>> &currArcs = cycles[i].GetArcs();
                const vector<attrType> &currAttributes = cycles[i].GetAttributesArcs();

                // compare attributes on the same vertex
                for (int i1 = 0; i1 < (int)currArcs.size(); ++i1)
                {
                    const pair<vType, vType> &currArc = currArcs[i1];
                    const attrType &currAttrArc = currAttributes[i1];

                    pair<vType, vType> toFindArc;
                    attrType toFindAttrArc;

                    vType sameVertex = -1;
                    // find pair with same vertex
                    for (int i2 = 0; i2 < (int)currArcs.size(); ++i2)
                    {
                        // if not currArc
                        if (i2 != i1)
                        {
                            toFindArc = currArcs[i2];
                            toFindAttrArc = currAttributes[i2];

                            if (currArc.first == toFindArc.first || currArc.first == toFindArc.second)
                            {
                                sameVertex = currArc.first;
                                if (currArc.first == toFindArc.second)
                                    swap(toFindAttrArc.first, toFindAttrArc.second);
                            }
                            else if (currArc.second == toFindArc.first || currArc.second == toFindArc.second)
                            {
                                sameVertex = currArc.second;
                                if (currArc.second == toFindArc.first)
                                    swap(toFindAttrArc.first, toFindAttrArc.second);
                            }

                            if (sameVertex != -1)
                                break;
                        }
                    }

                    if (sameVertex == currArc.first && toFindAttrArc.first != currAttrArc.first ||
                        sameVertex == currArc.second && toFindAttrArc.second != currAttrArc.second)
                    {
                        indexOfConflict.push_back(make_pair(i, CONFLICT_TYPE_2));
                        cycleMarked[i] = true;
                        countOfConflict++;
                        break;
                    }
                }
            }
#endif
        }
        __spf_print(PRINT_TIMES && needPrint, "PROF: GetConflictCycles: end %f sec\n", (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
        return countOfConflict;
    }
#undef WITH_CONFLICT_1 
#undef WITH_CONFLICT_2 

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         RemoveMultipleArcsByWeights()
    {
        for (vType v = 0; v < numVerts; ++v)
        {
            map<vType, pair<int, wType>> tmp;
            for (vType k = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                const vType e = edges[k];
                auto it = tmp.find(e);
                if (it == tmp.end())
                    tmp.insert(make_pair(e, make_pair(0, weights[k])));
                else
                    it->second.second = std::max(it->second.second, weights[k]);
            }

            for (vType k = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                const vType e = edges[k];
                auto  it = tmp.find(e);
                if (it->second.second == weights[k])
                    it->second.first++;
            }

            int removed = 0;
            for (vType k = neighbors[v], k1 = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                const vType e = edges[k1];
                auto it = tmp.find(e);
                if (it->second.second != weights[k1] || (it->second.second == weights[k1] && it->second.first != 1))
                {
                    if (it->second.second == weights[k1])
                        it->second.first--;

                    edges.erase(edges.begin() + k1);
                    weights.erase(weights.begin() + k1);
                    linkType.erase(linkType.begin() + k1);
                    attributes.erase(attributes.begin() + k1);
                    removed++;
                }
                else
                    k1++;
            }

            for (int t = v + 1; t < numVerts + 1; ++t)
                neighbors[t] -= removed;
        }

        // correct graph information 
        numEdges = (vType)edges.size();
    }

    template<typename vType, typename wType, typename attrType>
    bool GraphCSR<vType, wType, attrType>::
        checkFirstCoefOfNode(vType node)
    {
        bool ok = true;
        int firstCoef = attributes[neighbors[node]].first.first;
        for (vType k = neighbors[node] + 1; k < neighbors[node + 1]; ++k)
        {
            if (firstCoef != attributes[k].first.first)
            {
                ok = false;
                break;
            }
        }

        return ok;
    }

    template<typename vType, typename wType, typename attrType>
    bool GraphCSR<vType, wType, attrType>::
        getOptimalBoundsForNode(vType nodeFrom, vType nodeTo, int &needBound, pair<int, int> &bounds)
    {
        bool canCalc = true;
        
        bool initBound = false;
        bool initBounds = false;
        for (vType k = neighbors[nodeFrom]; k < neighbors[nodeFrom + 1]; ++k)
        {
            if (edges[k] != nodeTo)
            {
                if (initBound == false)
                {
                    initBound = true;
                    needBound = attributes[k].first.second;
                }
                else
                {
                    if (needBound != attributes[k].first.second)
                    {
                        canCalc = false;
                        break;
                    }
                }
            }

            if (initBounds == false)
            {
                initBounds = true;
                bounds.first = bounds.second = attributes[k].first.second;
            }
            else
            {
                bounds.first = std::min(bounds.first, attributes[k].first.second);
                bounds.second = std::max(bounds.second, attributes[k].first.second);
            }

        }

        return canCalc;
    }

    static int calcNewBound(int needBound, pair<int, int> &bounds)
    {
        if (needBound < bounds.first || needBound > bounds.second)
        {
            int dist1 = abs(needBound - bounds.first);
            int dist2 = abs(needBound - bounds.second);
            if (dist1 < dist2)
                return bounds.first;
            else
                return bounds.second;
        }
        else
            return needBound;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
        RemoveVerticesByWeight()
    {
        for (vType v = 0; v < numVerts; ++v)
        {
            int removed = 0;
            for (vType k = neighbors[v], k1 = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                if (weights[k1] == -1)
                {
                    edges.erase(edges.begin() + k1);
                    weights.erase(weights.begin() + k1);
                    linkType.erase(linkType.begin() + k1);
                    attributes.erase(attributes.begin() + k1);
                    removed++;
                }
                else
                    k1++;
            }

            for (int t = v + 1; t < numVerts + 1; ++t)
                neighbors[t] -= removed;
        }

        // correct graph information 
        numEdges = (vType)edges.size();
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
        RemoveMultipleArcsOptimal()
    {
        vector<vType> toDel;
        for (vType v = 0; v < numVerts; ++v)
        {
            map<vType, pair<int, vector<vType>>> numLinks;
            
            for (vType k = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                const vType e = edges[k];
                if (v < e)
                {
                    auto it = numLinks.find(e);
                    if (it == numLinks.end())
                        it = numLinks.insert(it, make_pair(e, make_pair(0, vector<int>())));
                    it->second.first++;
                    it->second.second.push_back(k);
                }
            }

            for (auto it = numLinks.begin(); it != numLinks.end(); ++it)
            {
                //has multiple arcs
                if (it->second.first > 1)
                {
                    const vector<vType> &idx = it->second.second;
                    bool hasWW = false;
                    int maxIdxW = -1;
                    double maxW = -1;
                    for (int k = 0; k < idx.size(); ++k)
                    {
                        if (linkType[idx[k]] == WW_link)
                            hasWW = true;
                        if (maxW < weights[idx[k]])
                            maxW = weights[idx[k]];
                    }

                    //try to find non conflict arcs
                    if (!hasWW)
                    {
                        if (checkFirstCoefOfNode(v) && checkFirstCoefOfNode(it->first))
                        {
                            int needBoundL = 0, needBoundH = 0;
                            pair<int, int> boundsL, boundsH;
                            bool canCalcL = getOptimalBoundsForNode(v, it->first, needBoundL, boundsL);
                            bool canCalcH = getOptimalBoundsForNode(it->first, v, needBoundH, boundsH);

                            if (canCalcL && canCalcH)
                            {
                                needBoundL = calcNewBound(needBoundL, boundsL);
                                needBoundH = calcNewBound(needBoundH, boundsH);
                             
                                for (int k = 0; k < idx.size(); ++k)
                                {
                                    int idxS = -1;
                                    for (int k = 0; k < idx.size(); ++k)
                                    {
                                        if (maxW == weights[idx[k]])
                                        {
                                            idxS = k;
                                            break;
                                        }
                                    }

                                    for (int k = 0; k < idx.size(); ++k)
                                    {
                                        if (maxW == weights[idx[k]] && idxS == k)
                                        {
                                            for (vType n = neighbors[edges[idx[k]]]; n < neighbors[edges[idx[k]] + 1]; ++n)
                                            {
                                                if (edges[n] == v &&
                                                    attributes[n].first == attributes[idx[k]].second &&
                                                    attributes[n].second == attributes[idx[k]].first &&
                                                    linkType[n] == linkType[idx[k]])
                                                {
                                                    attributes[n].first.second = needBoundH;
                                                    attributes[n].second.second = needBoundL;
                                                    break;
                                                }
                                            }

                                            attributes[idx[k]].first.second = needBoundL;
                                            attributes[idx[k]].second.second = needBoundH;
                                        }
                                        else
                                            toDel.push_back(idx[k]);
                                    }
                                }
                            }
                            else
                                hasWW = true;
                        }
                        else
                            hasWW = true;
                    }
                    
                    //if has W-W links, set arc with maximum weight
                    if (hasWW)
                    {
                        set<int> uniqMaxIds;
                        for (int k = 0; k < idx.size(); ++k)
                            if (maxW == weights[idx[k]])
                                uniqMaxIds.insert(k);
                        int exceptIdx = -1;
                        if (uniqMaxIds.size() == 0)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        else if (uniqMaxIds.size() == 1)
                            exceptIdx = *uniqMaxIds.begin();
                        else
                        {
                            int minDistToZero = 2147483647; // INT_MAX
                            for (auto& elem : uniqMaxIds)
                            {
                                int sum = abs(0 - attributes[idx[elem]].second.second) + abs(0 - attributes[idx[elem]].first.second);
                                if (minDistToZero > sum)
                                {
                                    minDistToZero = sum;
                                    exceptIdx = elem;
                                }
                            }
                        }

                        if (exceptIdx < 0 || exceptIdx >= idx.size())
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        for (int k = 0; k < idx.size(); ++k)
                            if (k != exceptIdx)
                                toDel.push_back(idx[k]);

                        //OLD ALGORITHM
                        /*bool eqSet = false;
                        for (int k = 0; k < idx.size(); ++k)
                        {
                            if (maxW == weights[idx[k]])
                            {
                                if (eqSet == false)
                                    eqSet = true;
                                else
                                    toDel.push_back(idx[k]);
                            }
                            else
                                toDel.push_back(idx[k]);
                        }*/
                    }
                }
            }
        }

        for (vType k = 0; k < toDel.size(); ++k)
            weights[toDel[k]] = -1;

        // add reverse arcs
        for (vType v = 0; v < numVerts; ++v)
        {
            for (vType k = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                if (weights[k] == -1 && v < edges[k])
                {
                    for (vType z = neighbors[edges[k]]; z < neighbors[edges[k] + 1]; ++z)
                    {
                        if (edges[z] == v &&
                            attributes[z].first == attributes[k].second && 
                            attributes[z].second == attributes[k].first &&
                            linkType[z] == linkType[k])
                        {
                            weights[z] = -1;
                            break;
                        }
                    }
                }
            }
        }

        RemoveVerticesByWeight();
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        CreateGraphWiz(const char *fileName, const vector<tuple<vType, vType, attrType>> &toDelArcs,
                       const Arrays<vType> &allArrays, const bool onlyTree)
    {
        FILE *out = fopen(fileName, "w");
        if (out == NULL)
        {
            char buf[256];
            sprintf(buf, "can not open file %s\n", fileName);
            addToGlobalBufferAndPrint(buf);
            return -1;
        }

        set<tuple<vType, vType, attrType>> dictDel;
        for (int i = 0; i < (int)toDelArcs.size(); ++i)
        {
            vType from = std::get<0>(toDelArcs[i]);
            vType to = std::get<1>(toDelArcs[i]);
            attrType attr = std::get<2>(toDelArcs[i]);
            attrType attrRev = make_pair(attr.second, attr.first);
            dictDel.insert(make_tuple(from, to, attr));
            dictDel.insert(make_tuple(to, from, attrRev));
        }

        fprintf(out, "graph G{\n");

        const set<Array*>& arrays = allArrays.GetArrays();
        set<Array*>::const_iterator it = arrays.begin();
        for (; it != arrays.end(); it++)
        {
            const int dimSize = (*it)->GetDimSize();
            const string arrayName = (*it)->GetName();
            string verts = "";
            bool allNotDefined = true;
            for (int i = 0; i < dimSize; ++i)
            {
                vType retVal;
                allArrays.GetVertNumber(*it, i, retVal);
                char buf[32];
                if (retVal < localIdx.size() && retVal >= 0)
                {
                    sprintf(buf, "%d", localIdx[retVal]);
                    if (localIdx[retVal] != -1)
                        allNotDefined = false;
                }
                else
                    sprintf(buf, "%d", -1);
                verts += buf;
                verts += " ";
            }

            if (!allNotDefined)
            {
                fprintf(out, "subgraph cluster_%s {\n", arrayName.c_str());
                for (int k = 0; k < dimSize; ++k)
                    fprintf(out, "\"%s.%d\"\n", arrayName.c_str(), k);
                fprintf(out, "label = \"array %s (%s)\" \n", arrayName.c_str(), verts.c_str());
                fprintf(out, "}\n");
            }
        }

        for (vType i = 0; i < numVerts; ++i)
        {
            for (vType k = neighbors[i]; k < neighbors[i + 1]; ++k)
            {
                const vType i1 = edges[k];
                const attrType attr = attributes[k];
                if (i < i1)
                {
                    const char *formatString;
                    bool needToPrint = true;
                    if (dictDel.find(make_tuple(i, i1, attr)) != dictDel.end())
                    {
                        formatString = "\"%s\" -- \"%s\" [label=\"%s\", headlabel=\"[%d,%d]\", taillabel=\"[%d,%d]\", color=\"red\", minlen=2.0];\n";
                        if (onlyTree)
                            needToPrint = false;
                    }
                    else
                        formatString = "\"%s\" -- \"%s\" [label=\"%s\", headlabel=\"[%d,%d]\", taillabel=\"[%d,%d]\", minlen=2.0];\n";

                    if (needToPrint)
                    {
                        string v1;
                        string v2;
                        allArrays.GetNameByVertex(globalIdx[i], v1);
                        allArrays.GetNameByVertex(globalIdx[i1], v2);

                        char tmpP[32];
                        sprintf(tmpP, "%.1f  ", weights[k]);
                        string label = string(tmpP);

                        if (linkType[k] == LinkType::RR_link)
                            label += "RR";
                        else if (linkType[k] == LinkType::WR_link)
                            label += "WR";
                        else if (linkType[k] == LinkType::WW_link)
                            label += "WW";
                        else
                            label += "UNK";
                        fprintf(out, formatString, v1.c_str(), v2.c_str(), label.c_str(), attr.first.first, attr.first.second, attr.second.first, attr.second.second);
                    }
                }
            }
        }
        fprintf(out, "overlap=false\n");
        fprintf(out, "}\n");
        fclose(out);

        return 0;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         RemovedEdges(const vector<tuple<vType, vType, attrType>> &toDelArcs, const Arrays<vType> &allArrays)
    {
        set<tuple<vType, vType, attrType>> dictDel;
        for (int i = 0; i < (int)toDelArcs.size(); ++i)
        {
            vType from = std::get<0>(toDelArcs[i]);
            vType to = std::get<1>(toDelArcs[i]);
            attrType attr = std::get<2>(toDelArcs[i]);
            attrType attrRev = make_pair(attr.second, attr.first);
            dictDel.insert(make_tuple(from, to, attr));
            dictDel.insert(make_tuple(to, from, attrRev));
        }

        int totalRemoved = 0;
        vector<vType> removed(numEdges);

        for (vType i = 0; i < numVerts; ++i)
        {
            int k = neighbors[i];
            int k1 = neighbors[i];
            int end = neighbors[i + 1];
            int removed = 0;
            while (k1 != end)
            {
                const vType i1 = edges[k];
                const attrType attr = attributes[k];

                if (dictDel.find(make_tuple(i, i1, attr)) != dictDel.end())
                {
                    edges.erase(edges.begin() + k);
                    weights.erase(weights.begin() + k);
                    linkType.erase(linkType.begin() + k);
                    attributes.erase(attributes.begin() + k);
                    removed++;
                    totalRemoved++;
                }
                else
                    k++;
                k1++;
            }

            for (int t = i + 1; t < numVerts + 1; ++t)
                neighbors[t] -= removed;
        }

        //correct graph information
        numEdges = (vType)edges.size();
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        GetAlignRuleForArray(Array *inputArray, const Arrays<vType> &allArrays, vector<vector<tuple<Array*, vType, attrType>>> &assignedArrays)
    {
        vector<vType> arrayVerts;
        int err = allArrays.GetAllVertNumber(inputArray, arrayVerts);
        if (err != 0)
            return err;

        assignedArrays.resize(arrayVerts.size());

        for (int i = 0; i < arrayVerts.size(); ++i)
        {
            const vType currV = localIdx[arrayVerts[i]];
            int maxDimSize = 0;
            for (int k = neighbors[currV]; k < neighbors[currV + 1]; ++k)
            {
                const vType V1 = edges[k];
                Array *tmp = allArrays.GetArrayByVertex(globalIdx[V1]);
                if (tmp)
                {
                    if (maxDimSize < tmp->GetDimSize())
                    {
                        maxDimSize = tmp->GetDimSize();
                        assignedArrays[i].clear();
                        assignedArrays[i].push_back(make_tuple(tmp, globalIdx[V1], attributes[k]));
                    }
                    else if (maxDimSize == tmp->GetDimSize())
                        assignedArrays[i].push_back(make_tuple(tmp, globalIdx[V1], attributes[k]));
                }
            }
        }

        return 0;
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        GetAlignRuleWithTemplate(Array *inputArray, const Arrays<vType> &allArrays, vector<tuple<Array*, vType, pair<int, int>>> &rules, const int regionId)
    {
        vector<vType> arrayVerts;
        int err = allArrays.GetAllVertNumber(inputArray, arrayVerts);
        if (err != 0)
            return err;

        rules.resize(arrayVerts.size());
        if (inputArray->IsTemplate())
        {
            std::vector<vType> vertsInGraph;
            allArrays.GetAllVertNumber(inputArray, vertsInGraph);
            if (vertsInGraph.size() != arrayVerts.size())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            for (int i = 0; i < arrayVerts.size(); ++i)
                rules[i] = std::make_tuple(inputArray, vertsInGraph[i], make_pair(1, 0));
        }
        else
        {
            for (int i = 0; i < arrayVerts.size(); ++i)
            {
                const vType currV = localIdx[arrayVerts[i]];
                // if current vertex has links
                if (currV != -1)
                {
                    pair<RationalNum, RationalNum> rule = make_pair(0, 0);
                    pair<RationalNum, RationalNum> nul = rule;

                    int alignDim = -1;
                    Array *templ = NULL;

                    set<vType> wasDone;                    
                    if (hasLinkWithTempate(currV, allArrays, false))
                    {
                        rule = findLinkWithTempate2(currV, alignDim, templ, allArrays, wasDone);
                        if (rule != nul)
                        {
                            if ((int)rule.first.getDenominator() != 1 || rule.second.getDenominator() != 1)
                            {
                                __spf_print(1, "Can not find correct align rule for array '%s', found (%d/%d, %d/%d)\n", inputArray->GetShortName().c_str(), 
                                    (int)rule.first.getNumerator(), (int)rule.first.getDenominator(), 
                                    (int)rule.second.getNumerator(), (int)rule.second.getDenominator());

                                //TODO: need to correct
                                //const int newValue = (rule.first.getDenominator() == rule.second.getDenominator()) ? rule.first.getDenominator() : 0;
                                if (!hasLinkWithTempate(currV, allArrays, true))
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                                return 101;
                            }

                            pair<int, int> intRule = make_pair((int)rule.first.getNumerator(), (int)rule.second.getNumerator());
                            
                            rules[i] = make_tuple(templ, alignDim, intRule);
                            int dimNum = -1;
                            int err = allArrays.GetDimNumber(templ, alignDim, dimNum);
                            if (err == -1)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            inputArray->AddLinkWithTemplate(i, dimNum, templ, intRule, regionId);
                        }
                    }
                }
            }
        }
        return 0;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         FindLinksBetweenArrays(const Arrays<vType> &allArrays, const Array *from, const Array *to, vector<int> &links) const
    {
        links.clear();
        links.resize(from->GetDimSize());

        vector<vType> vertNum;
        int err = allArrays.GetAllVertNumber(from, vertNum);
        if (err != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (int i = 0; i < from->GetDimSize(); ++i)
        {
            set<vType> wasDone;
            //no edges in graph
            if (localIdx[vertNum[i]] == -1)
            {
                links[i] = -1;
                continue;
            }

            int foundV = findDimNumLink(localIdx[vertNum[i]], to, allArrays, wasDone);
            links[i] = foundV;
        }
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
         FindLinkWithMaxDim(const vType from, const Arrays<vType> &allArrays, pair<Array*, int> &result, set<int> &wasDone)
    {
        if (numVerts == 0)
            return;

        const vType v = localIdx[from];
        if (v == -1)
            return;

        for (int k = neighbors[v]; k < neighbors[v + 1]; ++k)
        {
            const vType currV = edges[k];

            if (wasDone.find(currV) != wasDone.end())
                continue;

            wasDone.insert(v);

            Array *found = allArrays.GetArrayByVertex(globalIdx[currV]);
            if (found != NULL)
            {
                vType dimNumber = -1;
                int err = allArrays.GetDimNumber(found, globalIdx[currV], dimNumber);
                if (err != -1)
                {
                    const pair<int, int> &sizesRes = result.first->GetSizes()[result.second];
                    const pair<int, int> &sizesFound = found->GetSizes()[dimNumber];

                    //calculate dimention sizes and compare
                    if (sizesRes.second  - sizesRes.first + 1 < sizesFound.second - sizesFound.first + 1)
                    {
                        result.first = found;
                        result.second = dimNumber;
                    }
                }
            }
            FindLinkWithMaxDim(globalIdx[currV], allArrays, result, wasDone);
        }
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        FindAllArraysTrees(map<Array*, int> &trees, const Arrays<vType> &allArrays)
    {
        int treeCount = 1;
        set<Array*> firstInit;
        map<Array*, set<int>> wasDone;

        color.resize(numVerts);
        for (int i = 0; i < numVerts; ++i)
            color[i] = WHITE;
        vector<int> qNextV;

        while (true)
        {
            int nextV = -1;

            if (qNextV.size() == 0)
            {
                for (int i = 0; i < numVerts; ++i)
                {
                    if (color[i] == WHITE)
                    {
                        nextV = i;
                        color[i] = BLACK;
                        break;
                    }
                }
            }
            else
            {
                nextV = qNextV.back();
                qNextV.pop_back();
                if (color[nextV] == BLACK)
                    continue;
                else
                    color[nextV] = BLACK;
            }

            if (nextV == -1)
                break;
            else
            {
                Array *parentArray = allArrays.GetArrayByVertex(globalIdx[nextV]);
                if (parentArray == NULL)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                if (firstInit.find(parentArray) == firstInit.end())
                {
                    vector<vType> vertexes;
                    int err = allArrays.GetAllVertNumber(parentArray, vertexes);
                    if (err != 0)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    for (int i = 0; i < vertexes.size(); ++i)
                    {
                        if (vertexes[i] < localIdx.size())
                        {
                            const int idx = localIdx[vertexes[i]];
                            if (idx != nextV && idx != -1)
                                qNextV.push_back(idx);
                        }
                    }
                    firstInit.insert(parentArray);
                }
                                
                for (int k = neighbors[nextV]; k < neighbors[nextV + 1]; ++k)
                {
                    const vType currV = edges[k];

                    Array *currArray = allArrays.GetArrayByVertex(globalIdx[currV]);
                    if (currArray == NULL)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    auto itParent = trees.find(parentArray);
                    if (itParent == trees.end())
                    {
                        itParent = trees.insert(itParent, make_pair(parentArray, treeCount));
                        treeCount++;
                    }

                    auto itAdd = trees.find(currArray);
                    if (itAdd == trees.end())
                        trees.insert(itAdd, make_pair(currArray, itParent->second));
                    else
                    {
                        if (itParent->second != itAdd->second)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }

                    auto itCurrCheck = wasDone.find(currArray);
                    if (itCurrCheck == wasDone.end())
                        itCurrCheck = wasDone.insert(itCurrCheck, make_pair(currArray, set<int>()));
                    if (itCurrCheck->second.find(currV) == itCurrCheck->second.end())
                    {
                        qNextV.push_back(currV);
                        itCurrCheck->second.insert(currV);
                    }
                }
            }
        }
        return treeCount - 1;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
        HighlightLinks()
    {
        if (hardLinksWasUp)
            return;
        wType sum;
        /*sum = 1.0;
        // count all RR_link weight
        for (int i = 0; i < weights.size(); ++i)
        {
            if (linkType[i] == RR_link)
                sum += weights[i];
        }
        
        // and add it to all WR_link links
        for (int i = 0; i < weights.size(); ++i)
        {
            if (linkType[i] == WR_link)
                weights[i] += sum;
        } */

        sum = 1.0;
        // count all RR_link and WR_link weight
        for (int i = 0; i < weights.size(); ++i)
        {
            if (linkType[i] == RR_link || linkType[i] == WR_link)
                sum += weights[i];
        }

        // and add it to all WW_link links
        for (int i = 0; i < weights.size(); ++i)
        {
            if (linkType[i] == WW_link)
                weights[i] += sum;
        }

        hardLinksWasUp = true;
    }
    
    template<typename vType, typename wType, typename attrType>
    bool GraphCSR<vType, wType, attrType>::
        SaveGraphToFile(FILE *file)
    {
        fwrite(&numVerts, sizeof(vType), 1, file);
        if (ferror(file)) return false;

        fwrite(&numEdges, sizeof(vType), 1, file);
        if (ferror(file)) return false;

        fwrite(&lastNumOfV, sizeof(vType), 1, file);
        if (ferror(file)) return false;

        auto tmpS = neighbors.size();
        fwrite(&tmpS, sizeof(size_t), 1, file);
        fwrite(neighbors.data(), sizeof(vType), neighbors.size(), file);
        if (ferror(file)) return false;

        tmpS = edges.size();
        fwrite(&tmpS, sizeof(size_t), 1, file);
        fwrite(edges.data(), sizeof(vType), edges.size(), file);
        if (ferror(file)) return false;

        tmpS = weights.size();
        fwrite(&tmpS, sizeof(size_t), 1, file);
        fwrite(weights.data(), sizeof(wType), weights.size(), file);
        if (ferror(file)) return false;

        tmpS = linkType.size();
        fwrite(&tmpS, sizeof(size_t), 1, file);
        fwrite(linkType.data(), sizeof(uint8_t), linkType.size(), file);
        if (ferror(file)) return false;
        
        tmpS = attributes.size();
        fwrite(&tmpS, sizeof(size_t), 1, file);
        fwrite(attributes.data(), sizeof(attrType), attributes.size(), file);
        if (ferror(file)) return false;

        tmpS = localIdx.size();
        fwrite(&tmpS, sizeof(size_t), 1, file);
        fwrite(localIdx.data(), sizeof(vType), localIdx.size(), file);
        if (ferror(file)) return false;

        tmpS = globalIdx.size();
        fwrite(&tmpS, sizeof(size_t), 1, file);
        fwrite(globalIdx.data(), sizeof(vType), globalIdx.size(), file);
        if (ferror(file)) return false;

        return true;
    }

    template<typename type>
    static inline void readStdVector(vector<type> &T, const size_t size, FILE *file)
    {
        type *tmp = new type[size];
        fread(tmp, sizeof(type), size, file);
        T.resize(size);
        for (int i = 0; i < size; ++i)
            T[i] = tmp[i];

        delete []tmp;
    }

    template<typename vType, typename wType, typename attrType>
    bool GraphCSR<vType, wType, attrType>::
        LoadGraphFromFile(FILE *file)
    {
        fread(&numVerts, sizeof(vType), 1, file);
        if (ferror(file)) return false;

        fread(&numEdges, sizeof(vType), 1, file);
        if (ferror(file)) return false;

        fread(&lastNumOfV, sizeof(vType), 1, file);
        if (ferror(file)) return false;

        size_t tmpS;
        fread(&(tmpS), sizeof(size_t), 1, file);
        readStdVector(neighbors, tmpS, file);        
        if (ferror(file)) return false;

        fread(&(tmpS), sizeof(size_t), 1, file);
        readStdVector(edges, tmpS, file);
        if (ferror(file)) return false;

        fread(&(tmpS), sizeof(size_t), 1, file);
        readStdVector(weights, tmpS, file);
        if (ferror(file)) return false;

        fread(&(tmpS), sizeof(size_t), 1, file);
        readStdVector(linkType, tmpS, file);
        if (ferror(file)) return false;

        fread(&(tmpS), sizeof(size_t), 1, file);
        readStdVector(attributes, tmpS, file);
        if (ferror(file)) return false;

        fread(&(tmpS), sizeof(size_t), 1, file);
        readStdVector(localIdx, tmpS, file);
        if (ferror(file)) return false;

        fread(&(tmpS), sizeof(size_t), 1, file);
        readStdVector(globalIdx, tmpS, file);
        if (ferror(file)) return false;

        return true;
    }

    template<typename vType, typename wType, typename attrType>
    vector<attrType> GraphCSR<vType, wType, attrType>::
        GetAllAttributes(const int vert) const
    {
        vector<attrType> retVal;
        if (localIdx.size() == 0 || vert >= localIdx.size())
            return retVal;

        int locV = localIdx[vert];
        if (locV < 0)
            return retVal;

        for (int z = neighbors[locV]; z < neighbors[locV + 1]; ++z)
            retVal.push_back(attributes[z]);

        return retVal;
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        CountOfConnected(const vType startV) const
    {
        std::vector<unsigned char> inSet(numVerts);
        std::fill(inSet.begin(), inSet.end(), 0);

        vector<vType> next;
        next.reserve(numVerts);

        next.push_back(startV);
        inSet[startV] = 1;
        int count = 1;

        while (next.size())
        {
            const vType V = next.back();
            next.pop_back();

            for (vType k = neighbors[V]; k < neighbors[V + 1]; ++k)
            {
                const vType toV = edges[k];
                if (inSet[toV] == 0)
                {
                    inSet[toV] = 1;
                    count++;
                    next.push_back(toV);
                }
            }
        }
        return count;
    }

    template<typename vType, typename wType, typename attrType>
    int GraphCSR<vType, wType, attrType>::
        CountOfConnectedForArray(const vType startV) const
    {
        if (startV >= localIdx.size() || startV < 0)
            return 0;
        const int localV = localIdx[startV];
        if (localV == -1)
            return 0;
        else
            return CountOfConnected(localV) - 1;
    }
    template<typename vType, typename wType, typename attrType>
    pair<int, int> GraphCSR<vType, wType, attrType>::
        MakeConnected(const vType startV, vector<unsigned char> &inSet) const
    {
        int count = 0;
        int countE = 0;

        inSet.resize(numVerts);
        std::fill(inSet.begin(), inSet.end(), 0);

        vector<vType> next;
        next.reserve(numVerts);

        next.push_back(startV);
        inSet[startV] = 1;
        count = 1;

        while (next.size())
        {
            const vType V = next.back();
            next.pop_back();

            for (vType k = neighbors[V]; k < neighbors[V + 1]; ++k)
            {
                const vType toV = edges[k];
                if (inSet[toV] == 0)
                {
                    inSet[toV] = 1;
                    count++;
                    next.push_back(toV);
                }
            }
        }

        for (int v = 0; v < numVerts; ++v)
        {
            for (vType k = neighbors[v]; k < neighbors[v + 1]; ++k)
            {
                const vType toV = edges[k];
                if (inSet[toV])
                    countE++;
            }
        }

        return make_pair(count, countE / 2);
    }

    template<typename vType, typename attrType>
    static tuple<vType, vType, attrType> makeReverse(const tuple<vType, vType, attrType> &in)
    {
        vType from = std::get<0>(in);
        vType to = std::get<1>(in);
        attrType attr = std::get<2>(in);
        attrType attrRev = make_pair(attr.second, attr.first);
        
        return std::make_tuple(to, from, attrRev);
    }

    template<typename vType, typename wType, typename attrType>
    vector<tuple<vType, vType, attrType>> GraphCSR<vType, wType, attrType>::
        CreateMaximumSpanningTree()
    {
        set<tuple<vType, vType, attrType>> selected;
                
        set<vType> tmp;
        for (int z = 0; z < numEdges; ++z)
            tmp.insert(edges[z]);
        int countOfRealV = tmp.size();
        tmp.clear();

        tuple<vType, vType, attrType> maxEdge;
        wType startW = -1;
        set<vType> vInserted;

        while (vInserted.size() != countOfRealV)
        {
            startW = -1;
            for (auto &z : vInserted)
            {
                for (vType k = neighbors[z]; k < neighbors[z + 1]; ++k)
                {
                    if (vInserted.find(edges[k]) != vInserted.end())
                        continue;

                    if (startW < weights[k])
                    {
                        startW = weights[k];
                        maxEdge = std::make_tuple(z, edges[k], attributes[k]);
                    }
                }
            }

            if (startW != -1)
            {
                selected.insert(maxEdge);
                selected.insert(makeReverse(maxEdge));

                vInserted.insert(std::get<0>(maxEdge));
                vInserted.insert(std::get<1>(maxEdge));
            } // next tree
            else
            {
                for (vType z = 0; z < numVerts; ++z)
                {
                    for (vType k = neighbors[z]; k < neighbors[z + 1]; ++k)
                    {
                        if (vInserted.find(edges[k]) != vInserted.end())
                            continue;

                        if (startW < weights[k])
                        {
                            startW = weights[k];
                            maxEdge = std::make_tuple(z, edges[k], attributes[k]);
                        }
                    }
                }

                if (startW == -1)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                else
                {
                    selected.insert(maxEdge);
                    selected.insert(makeReverse(maxEdge));

                    vInserted.insert(std::get<0>(maxEdge));
                    vInserted.insert(std::get<1>(maxEdge));
                }
            }
        }

        vector<tuple<vType, vType, attrType>> toDel;
        for (vType z = 0; z < numVerts; ++z)
        {
            for (vType k = neighbors[z]; k < neighbors[z + 1]; ++k)
            {
                if (selected.find(std::make_tuple(z, edges[k], attributes[k])) == selected.end())
                    toDel.push_back(std::make_tuple(z, edges[k], attributes[k]));                    
            }
        }
        return toDel;
    }

    template<typename vType, typename wType, typename attrType>
    void GraphCSR<vType, wType, attrType>::
        RemoveAllEdgesFromGraph(const map<Array*, vector<pair<int, int>>> &toDel, const Arrays<vType>& allArrays)
    {
        for (auto& arrayP : toDel)
        {
            Array* array = arrayP.first;
            checkNull(array, convertFileName(__FILE__).c_str(), __LINE__);
            if (!array->IsArray() && !array->IsTemplate())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            vector<vType> arrayVerts;
            int err = allArrays.GetAllVertNumber(array, arrayVerts);
            if (err != 0)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            for (int i = 0; i < arrayVerts.size(); ++i)
            {
                const vType currV = localIdx[arrayVerts[i]];
                // if current vertex has links
                if (currV != -1)
                {
                    for (int k = neighbors[currV]; k < neighbors[currV + 1]; ++k)
                    {
                        const vType V2 = edges[k];
                        Array* arrayTo = allArrays.GetArrayByVertex(globalIdx[V2]);
                        checkNull(array, convertFileName(__FILE__).c_str(), __LINE__);

                        bool needToDel = true;
                        if (arrayTo->IsArray())
                        {
                            if (toDel.find(arrayTo) == toDel.end())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                        else // tepmlate
                        {
                            if (toDel.find(arrayTo) == toDel.end())
                                needToDel = false;
                        }

                        //remove
                        if (needToDel)
                            weights[k] = -1;
                    }
                }
            }
        }

        //remove from graph
        RemoveVerticesByWeight();
    }

    template class GraphCSR<int, double, attrType>;
}

#undef MIN_CYCLE_DIM
#undef MAX_LOOP_DIM
#undef PRINT_TIMES
