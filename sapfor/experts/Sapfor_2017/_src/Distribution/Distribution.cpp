#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <algorithm>
#include <chrono>
#include <climits>
#include <cstring>

#if _WIN32 && NDEBUG && __BOOST
#include <boost/thread.hpp>
#endif
extern int passDone;

using std::pair;
using std::set;
using std::make_pair;
using std::string;
using std::wstring;
using std::tuple;
using std::vector;
using namespace std::chrono;

#include "GraphCSR.h"
#include "Arrays.h"
#include "Array.h"
#include "Distribution.h"
#include "../Utils/utils.h"
#include "../Utils/errors.h"
#include "../Utils/types.h"
#include "../Distribution/Cycle.h"
#include "../VisualizerCalls/get_information.h"
#include "../VisualizerCalls/SendMessage.h"

extern int keepFiles;

#define ERROR_CHECK(err) do { if (err != 0) return err; } while(0)
#define FIRST(x)  get<0>(x)
#define SECOND(x) get<1>(x)
#define THIRD(x)  get<2>(x)

namespace Distribution
{
    template<typename vType, typename wType, typename attrType>
    int AddArrayAccess(GraphCSR<vType, wType, attrType> &G, Arrays<vType> &allArrays,
                       Array *arr1, Array *arr2, pair<int, int> arc, wType arcWeight, const attrType &arcAttr,
                       const uint8_t linkType)
    {
        int err = 0;
        allArrays.AddArrayToGraph(arr1);
        allArrays.AddArrayToGraph(arr2);

        vType V1, V2;
        ERROR_CHECK(allArrays.GetVertNumber(arr1, arc.first, V1));
        ERROR_CHECK(allArrays.GetVertNumber(arr2, arc.second, V2));

        //fix attributes: pair< pair<int, int>, pair<int, int> > 
        pair<int, int> left = arcAttr.first;
        pair<int, int> right = arcAttr.second;

        if (left.first == right.first)
        {
            if (left.second == right.second)
                left.second = right.second = 0;
            else if (left.second != 0 && right.second != 0)
            {
                int diffZeroL = abs(left.second - 0);
                int diffZeroR = abs(right.second - 0);
                if (diffZeroL < diffZeroR)
                {
                    if (left.second > 0)
                    {
                        left.second -= diffZeroL;
                        right.second -= diffZeroL;
                    }
                    else
                    {
                        left.second += diffZeroL;
                        right.second += diffZeroL;
                    }
                }
                else
                {
                    if (right.second > 0)
                    {
                        left.second -= diffZeroR;
                        right.second -= diffZeroR;
                    }
                    else
                    {
                        left.second += diffZeroR;
                        right.second += diffZeroR;
                    }
                }
            }
        }

        G.AddToGraph(V1, V2, arcWeight, make_pair(left, right), linkType);
        return err;
    }

    template<typename vType, typename wType, typename attrType>
    static int GetIdxOfNextCycle(const vector<tuple<vType, vType, attrType>> &localDelArcs,
                                 const vector<Cycle<vType, wType, attrType>> &cycles,
                                 const vector<pair<int, int>> &indexOfConflict,
                                 const int idxStart = 0)
    {
        int idx = -1;
        for (int i = idxStart; i < (int)indexOfConflict.size(); ++i)
        {
            const Cycle<vType, wType, attrType> &currCycle = cycles[indexOfConflict[i].first];
            if (localDelArcs.size() == 0)
            {
                idx = i;
                break;
            }
            else
            {
                const vector<pair<vType, vType>> &arcs = currCycle.GetArcs();
                const vector<attrType> &attributes = currCycle.GetAttributesArcs();
                bool same = false;

                for (int k = 0; k < (int)arcs.size(); ++k)
                {
                    const tuple<vType, vType, attrType> toCheck = make_tuple(arcs[k].first, arcs[k].second, attributes[k]);
                    const tuple<vType, vType, attrType> toCheckRev = make_tuple(arcs[k].second, arcs[k].first, make_pair(attributes[k].second, attributes[k].first));

                    same = false;
                    for (int m = 0; m < (int)localDelArcs.size(); ++m)
                    {
                        if (toCheck == localDelArcs[m] || toCheckRev == localDelArcs[m])
                        {
                            same = true;
                            break;
                        }
                    }
                    if (same)
                        break;
                }
                if (same)
                    continue;
                else
                {
                    idx = i;
                    break;
                }
            }
        }
        return idx;
    }

    template<typename vType, typename wType, typename attrType>
    static int GetIdxOfNextCycle(const unsigned *fastCache, const vector<unsigned> &localDelArcsShort,
                                 const vector<Cycle<vType, wType, attrType>> &cycles,
                                 const vector<pair<int, int>> &indexOfConflict,
                                 const int idxStart = 0)
    {
        int idx = -1;
        const pair<int, int> *data = indexOfConflict.data();
        for (int i = idxStart; i < (int)indexOfConflict.size(); ++i)
        {
            const Cycle<vType, wType, attrType> &currCycle = cycles[data[i].first];
            if (localDelArcsShort.size() == 0)
            {
                idx = i;
                break;
            }
            else
            {
                const vector<unsigned> &shortInfo = currCycle.GetShortInfo();
                bool same = false;
                for (int k = 0; k < (int)shortInfo.size(); ++k)
                {                    
                    if (fastCache[shortInfo[k]] == 1)
                    {
                        same = true;
                        break;
                    }
                }
                if (same)
                    continue;
                else
                {
                    idx = i;
                    break;
                }
            }
        }
        return idx;
    }

    static inline bool checkGraphTrue(const int startV, const int realV, const GraphCSR<int, double, attrType> &G)
    {
        return true;
    }

    static inline bool checkGraph(const int startV, const int realV, const GraphCSR<int, double, attrType> &G)
    {
        return realV == G.CountOfConnected(startV);
    }

    template<typename vType, typename wType, typename attrType, bool check(const int startV, const int realV, const GraphCSR<vType, wType, attrType> &G)>
    static void FindBestSequenceForDelArcs(double &globalSum, vector<tuple<vType, vType, attrType>> &globalDelArcs,
                                           const double localSum, vector<tuple<vType, vType, attrType>> &localDelArcs,
                                           vector<unsigned> &localDelArcsShort,
                                           unsigned *fastCache,
                                           const vector<Cycle<vType, wType, attrType>> &cycles, const vector<pair<int, int>> &indexOfConflict,
                                           const int lastIndexOfConflict, const int countInTree,
                                           const GraphCSR<vType, wType, attrType> &graph)
    {
        int nextConflict = GetIdxOfNextCycle(fastCache, localDelArcsShort, cycles, indexOfConflict, lastIndexOfConflict + 1);
        if (nextConflict == -1)
        {
            globalSum = localSum;
            globalDelArcs = localDelArcs;

            //char buf[256];
            //sprintf(buf, "  global sum = %f, last idx of conflict %d\n", globalSum, lastIndexOfConflict);
            printf("SAPFOR: global sum = %f, last idx of conflict %d\n", globalSum, lastIndexOfConflict);
            //addToGlobalBufferAndPrint(buf);
#if _WIN32
            createNeededException();
#endif
        }
        else
        {
            const Cycle<vType, wType, attrType> &conflicCycle = cycles[indexOfConflict[nextConflict].first];
            const vector<pair<vType, vType>> &arcs = conflicCycle.GetArcs();
            const vector<unsigned> &shortInfo = conflicCycle.GetShortInfo();
            const vector<wType> &weights = conflicCycle.GetWeigthsArcs();
            const vector<attrType> &attributes = conflicCycle.GetAttributesArcs();

            for (int i = 0; i < (int)arcs.size(); ++i)
            {
                const pair<vType, vType> &currArc = arcs[i];
                const wType currW = weights[i];
                const attrType &currAttr = attributes[i];

                if (!check(currArc.first, countInTree, graph))
                    continue;
                else
                {
                    if (localSum + currW < globalSum)
                    {
                        localDelArcs.push_back(make_tuple(currArc.first, currArc.second, currAttr));
                        localDelArcsShort.push_back(shortInfo[i]);
                        fastCache[shortInfo[i]] = 1;

                        FindBestSequenceForDelArcs
                            <vType, wType, attrType, check>
                                (globalSum, globalDelArcs, localSum + currW, localDelArcs, localDelArcsShort, fastCache, cycles, indexOfConflict, nextConflict, countInTree, graph);

                        fastCache[shortInfo[i]] = 0;
                        localDelArcs.pop_back();
                        localDelArcsShort.pop_back();
                    }
                    else
                    {
#if _WIN32
                        createNeededException();
#endif
                        break;
                    }
                }
            }
        }
    }

    template<typename vType, typename wType, typename attrType>
    static void CountConflictVarints(int64_t &countVars, 
                                     vector<unsigned> &localDelArcsShort, unsigned *fastCache,
                                     const vector<Cycle<vType, wType, attrType>> &cycles, const vector<pair<int, int>> &indexOfConflict,
                                     const int lastIndexOfConflict)
    {
        int nextConflict = GetIdxOfNextCycle(fastCache, localDelArcsShort, cycles, indexOfConflict, lastIndexOfConflict + 1);
        if (nextConflict == -1)
        {
            countVars++;
            return;
        }
        else
        {
            const Cycle<vType, wType, attrType> &conflicCycle = cycles[indexOfConflict[nextConflict].first];
            const vector<unsigned> &shortInfo = conflicCycle.GetShortInfo();
            
            for (int i = 0; i < (int)shortInfo.size(); ++i)
            {
                localDelArcsShort.push_back(shortInfo[i]);
                fastCache[shortInfo[i]] = 1;

                CountConflictVarints(countVars, localDelArcsShort, fastCache, cycles, indexOfConflict, nextConflict);

                fastCache[shortInfo[i]] = 0;
                localDelArcsShort.pop_back();                
            }
        }
    }

#define DEGUB_DEL_ALL_CYCLES 0
    template<typename vType, typename wType, typename attrType>
    static void FindNonConflictDelArcs(vector<tuple<vType, vType, attrType>> &delArcs, const vector<Cycle<vType, wType, attrType>> &cycles)
    {
        vector<pair<int, int>> idxOfLoops(cycles.size());
        // fill indexs for all lopps for using 'GetIdxOfNextCycle' procedure
        for (int i = 0; i < (int)cycles.size(); ++i)
#if !DEGUB_DEL_ALL_CYCLES
            idxOfLoops[i] = std::make_pair(i, 0);
#else
        {
            const std::vector<pair<vType, vType>> &arcs = cycles[i].GetArcs();
            const std::vector<attrType> &attrs = cycles[i].GetAttributesArcs();
            for (int i = 0; i < arcs.size(); ++i)
                delArcs.push_back(std::make_tuple(arcs[i].first, arcs[i].second, attrs[i]));
        }
#endif

#if !DEGUB_DEL_ALL_CYCLES
        int idxNext = -1;
        do
        {
            idxNext = GetIdxOfNextCycle(delArcs, cycles, idxOfLoops, idxNext + 1);
            if (idxNext != -1)
            {
                std::pair<vType, vType> arc = cycles[idxNext].GetArcs()[0];
                attrType attr = cycles[idxNext].GetAttributesArcs()[0];
                delArcs.push_back(std::make_tuple(arc.first, arc.second, attr));
            }
        } while (idxNext != -1);
#endif    
    }
#undef DEGUB_DEL_ALL_CYCLES


    template<typename vType, typename wType, typename attrType>
    static pair<bool, double> CreateOptimalAlignementTree(GraphCSR<vType, wType, attrType> &G, const Arrays<vType> &allArrays,
                                              vector<tuple<vType, vType, attrType>> &toDelArcs, bool needPrint = true, bool useSavedQ = false)
    {        
        double globalSum = 0;
        bool allOnlySecondType = true;

        vector<vType> trees;
        vector<vector<vType>> vertByTrees;
        set<vType> unqieTrees = G.FindTrees(trees, vertByTrees);

        __spf_print(needPrint, "GRAPH size: |V| = %d, |E| = %d\n", G.GetNumberOfV(), G.GetNumberOfE() / 2);
        __spf_print(needPrint, "TREES count %d\n", (int)unqieTrees.size());
        vector<unsigned char> tmp;
        for (int z = 0; z < vertByTrees.size(); ++z)
            if (vertByTrees[z].size())
                __spf_print(needPrint, "TREES %d: V = %d, E = %d\n", z, (int)vertByTrees[z].size(), G.MakeConnected(vertByTrees[z][0], tmp).second);
            else
                __spf_print(needPrint, "TREES %d: V = %d, E = %d\n", z, 0, 0);

        toDelArcs = G.CreateMaximumSpanningTree();
        return make_pair(allOnlySecondType, globalSum);

        // OLD ALGORITHM, THIS IS unreachable code !!
        vector<vector<Cycle<vType, wType, attrType>>> AllCycles;

        G.GetAllSimpleLoops(AllCycles, needPrint, useSavedQ);
        toDelArcs.clear();
        
        for (int k = 0; k < AllCycles.size(); ++k)
        {
            unsigned maxElem = 0;
            bool onlySecondConflictType = true;

            for (auto &elem : AllCycles[k])
                for (auto &cycleShortInfo : elem.GetShortInfo())
                    maxElem = std::max(maxElem, cycleShortInfo);

            if (maxElem != 0 && needPrint)
                printf("SAPFOR: max elem for cache %lld, in MB: %f\n", maxElem, maxElem / 1024. / 1024. * sizeof(unsigned));

            unsigned *fastCache = new unsigned[maxElem];
            memset(fastCache, 0, sizeof(unsigned) * maxElem);

            char buf[256];
            if (needPrint)
            {
                sprintf(buf, "PROF: [%d TREE]:\n", k);
                addToGlobalBufferAndPrint(buf);
            }

            double globalSumLocal = (double)INT32_MAX;
            vector<pair<vType, vType>> indexOfConflict;
            vector<Cycle<vType, wType, attrType>> &cycles = AllCycles[k];

            vector<tuple<vType, vType, attrType>> localDelArcs;
            vector<unsigned> localDelArcShort;

            G.SortLoopsBySize(cycles, needPrint);
            G.SortLoopsByWeight(cycles, needPrint);

            for (int i = 0; i < (int)cycles.size(); ++i)
                cycles[i].SortArcs();

            int countConflicts = G.GetConflictCycles(cycles, allArrays, indexOfConflict, needPrint);

            if (needPrint)
            {
                sprintf(buf, " num of conflict cycles %d\n", countConflicts);
                printf("SAPFOR: num of conflict cycles %d\n", countConflicts);
                addToGlobalBufferAndPrint(buf);
            }

            if (countConflicts != 0)
            {
                int typeConflict[2] = { 0, 0 };
                for (int i = 0; i < indexOfConflict.size(); ++i)
                    typeConflict[indexOfConflict[i].second]++;
                if (needPrint)
                {
                    sprintf(buf, " num of type1 = %d, type2 = %d\n", typeConflict[0], typeConflict[1]);
                    printf("SAPFOR: num of type1 = %d, type2 = %d\n", typeConflict[0], typeConflict[1]);
                    addToGlobalBufferAndPrint(buf);
                }

                if (typeConflict[0])
                {
                    onlySecondConflictType = false;
                    allOnlySecondType = false;
                }
            }

#ifdef _WIN32
            if (needPrint)
            {
                wstring treeM = L"разрешение конфликтов, обработка группы " + std::to_wstring(k + 1) + L"/" + std::to_wstring(AllCycles.size());
                sendMessage_2lvl(treeM);
            }
#endif
            auto timeR = steady_clock::now();
            if (countConflicts != 0)
            {
                const int countInTree = G.CountOfConnected(cycles[indexOfConflict[0].first].GetArcs()[0].first);
                const int lastIndexOfConflict = -1;

                if (needPrint)
                    printf("SAPFOR: before del %d\n", countInTree);

                /*int64_t countVars = 0;
                CountConflictVarints(countVars, localDelArcShort, fastCache, cycles, indexOfConflict, lastIndexOfConflict);
                printf("SAPFOR: count of vars %lld\n", countVars);*/

                if (onlySecondConflictType)
                    FindBestSequenceForDelArcs
                        <vType, wType, attrType, checkGraph>
                            (globalSumLocal, toDelArcs, 0, localDelArcs, localDelArcShort, fastCache, cycles, indexOfConflict, lastIndexOfConflict, countInTree, G);
                else
                    FindBestSequenceForDelArcs
                        <vType, wType, attrType, checkGraphTrue>
                            (globalSumLocal, toDelArcs, 0, localDelArcs, localDelArcShort, fastCache, cycles, indexOfConflict, lastIndexOfConflict, countInTree, G);

                if (needPrint)
                {
                    auto tmpReducedG = G;
                    tmpReducedG.RemovedEdges(toDelArcs, allArrays);
                    if (needPrint)
                        printf("SAPFOR: after del %d\n", tmpReducedG.CountOfConnected(cycles[indexOfConflict[0].first].GetArcs()[0].first));
                }
                globalSum += globalSumLocal;
            }

            if (needPrint)
            {
                sprintf(buf, "PROF: FindBestSequenceForDelArcs: %f sec\n", (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
                printf("SAPFOR: time of FindBestSequenceForDelArcs %f sec\n", (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
                addToGlobalBufferAndPrint(buf);
            }

            timeR = steady_clock::now();
            FindNonConflictDelArcs(toDelArcs, cycles);
            if (needPrint)
            {                
                sprintf(buf, "PROF: FindNonConflictDelArcs %f\n", (duration_cast<duration<double>>(steady_clock::now() - timeR)).count());
                addToGlobalBufferAndPrint(buf);
            }

            delete []fastCache;
        }

#ifdef _WIN32
        if (needPrint)
            sendMessage_2lvl(L"");
#endif
        return make_pair(allOnlySecondType, globalSum);
    }

#define TEST 0
    template<typename vType, typename wType, typename attrType>
    void createOptimalDistribution(GraphCSR<vType, wType, attrType> &G, GraphCSR<vType, wType, attrType> &reducedG,
                                   const Arrays<vType> &allArrays, const int regionNum, bool onlyGraph)
    {
        vector<tuple<int, int, attrType>> toDelArcs;

        if (G.GetNumberOfE() == 0)
            return;

        double globalSum = 0;


        string FullName = "_graph_full_reg" + std::to_string(regionNum) + ".txt";
        string ReducedName = "_graph_reduced_reg" + std::to_string(regionNum) + ".txt";
        //__spf_print(1, "flag keepFiles %d, flag onlyGraph %d\n", keepFiles, onlyGraph);
            
        if (keepFiles)
        {
            if (!onlyGraph)
                G.CreateGraphWiz(FullName.c_str(), toDelArcs, allArrays, false);
            else
                G.CreateGraphWiz(FullName.c_str(), vector<tuple<int, int, attrType>>(), allArrays, true);
        }

        if (!onlyGraph)
        {
            G.HighlightLinks();

            //old simple algorithm
            //G.RemoveMultipleArcsByWeights();

            //new algorithm with optimal strategy
            G.RemoveMultipleArcsOptimal();
#if TEST
            string ArrayFileName = "_save_arrays_reg" + std::to_string(regionNum) + ".txt";
            string GraphFileName = "_save_full_graph_reg" + std::to_string(regionNum) + ".txt";
            string ReducedGraphFileName = "_save_reduced_graph_reg" + std::to_string(regionNum) + ".txt";

            FILE *load = fopen(ArrayFileName.c_str(), "r");
            bool needToReSave = true;
            if (load)
            {
                Arrays<vType> allArraysT;
                GraphCSR<vType, wType, attrType> G_local, reducedG_local;

                needToReSave = needToReSave && !allArraysT.LoadArraysFromFile(load, allArrays.GetArrays(), allArrays.GetMaxVertexNum());
                fclose(load);

                if (!needToReSave)
                {
                    load = fopen(GraphFileName.c_str(), "rb");
                    bool loadG_ok = false, loadGR_ok = false;
                    if (load)
                    {
                        loadG_ok = G_local.LoadGraphFromFile(load);
                        fclose(load);
                    }

                    load = fopen(ReducedGraphFileName.c_str(), "rb");
                    if (load)
                    {
                        loadGR_ok = reducedG_local.LoadGraphFromFile(load);
                        fclose(load);
                    }

                    //process
                    if (loadG_ok && loadGR_ok)
                    {

                    }
                    else
                        needToReSave = true;
                }
            }

            if (needToReSave)
            {
                FILE *save = fopen(ArrayFileName.c_str(), "w");
                if (save)
                {
                    allArrays.SaveArraysToFile(save);
                    fclose(save);

                    save = fopen(GraphFileName.c_str(), "wb");
                    if (save)
                    {
                        G.SaveGraphToFile(save);
                        fclose(save);
                    }
                }
                else
                    needToReSave = false;
            }
#endif

            pair<bool, double> retVal = CreateOptimalAlignementTree(G, allArrays, toDelArcs);
            globalSum = retVal.second;
            bool onlySecondType = retVal.first;

            reducedG = G;
            reducedG.RemovedEdges(toDelArcs, allArrays);

            double maxWeight = reducedG.CalculateSumOfWeights() + 1;
            //try to resolve conflicts of 1 type
            const set<Array*> &arrays = allArrays.GetArrays();

            vector<Array*> arraysV;
            arraysV.assign(arrays.begin(), arrays.end());

            for (int z = 0; z < arraysV.size(); ++z)
            {
                const DIST::Array *array = arraysV[z];

#ifdef _WIN32
                wstring treeM = L"разрешение конфликтов, обработка массива " + std::to_wstring(z + 1) + L"/" + std::to_wstring(arrays.size());
                sendMessage_2lvl(treeM);
#endif
                vector<vType> verts;

                if (array->GetDimSize() == 1)
                    continue;

                int err = allArrays.GetAllVertNumber(array, verts);
                if (err != 0)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                attrType tmpPair = make_pair(make_pair(1, 0), make_pair(1, 0));

                for (int i = 0; i < verts.size(); ++i)
                {
                    for (int j = i + 1; j < verts.size(); ++j)
                    {
                        GraphCSR<vType, wType, attrType> findConflict(reducedG);
                        findConflict.AddToGraph(verts[i], verts[j], maxWeight, tmpPair, WW_link);

                        vector<tuple<int, int, attrType>> toDelArcsLocal;
                        globalSum = CreateOptimalAlignementTree(findConflict, allArrays, toDelArcsLocal, false, true).second;
                        if (toDelArcsLocal.size() != 0)
                            reducedG.RemovedEdges(toDelArcsLocal, allArrays);
                    }
                }
            }
#ifdef _WIN32
            sendMessage_2lvl(L"");
#endif

#if TEST
            if (needToReSave)
            {
                FILE *save = NULL;
                if (save)
                {
                    save = fopen(ReducedGraphFileName.c_str(), "wb");
                    if (save)
                    {
                        reducedG.SaveGraphToFile(save);
                        fclose(save);
                    }
                }
            }
#endif
        }
        else
        {
            reducedG = G;
            reducedG.RemoveMultipleArcsByWeights();
        }
        
        if (keepFiles)
        {
            if (!onlyGraph)
                reducedG.CreateGraphWiz(ReducedName.c_str(), vector<tuple<int, int, attrType>>(), allArrays, true);            
            else
                reducedG.CreateGraphWiz(ReducedName.c_str(), vector<tuple<int, int, attrType>>(), allArrays, true);            
        }
    }

    template void createOptimalDistribution(GraphCSR<int, double, attrType> &G, GraphCSR<int, double, attrType> &reducedG, const Arrays<int> &allArrays, const int regionNum, bool onlyGraph);
    template int AddArrayAccess(GraphCSR<int, double, attrType> &G, Arrays<int> &allArrays, Array *arr1, Array *arr2, pair<int, int> arc, double arcWeight, const attrType &arcAttr, const uint8_t linkType);
}

#undef ERROR_CHECK
#undef FIRST
#undef SECOND
#undef THIRD