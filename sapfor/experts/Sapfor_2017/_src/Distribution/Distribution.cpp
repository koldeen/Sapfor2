#include "../leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <algorithm>
#include <omp.h>
#include <limits.h>

using std::pair;
using std::set;
using std::make_pair;
using std::string;
using std::tuple;
using std::vector;

#include "GraphCSR.h"
#include "Arrays.h"
#include "Array.h"
#include "Distribution.h"
#include "../utils.h"

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

        G.AddToGraph(V1, V2, arcWeight, arcAttr, linkType);
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
    static int GetIdxOfNextCycle(const vector<unsigned> &localDelArcsShort,
                                 const vector<Cycle<vType, wType, attrType>> &cycles,
                                 const vector<pair<int, int>> &indexOfConflict,
                                 const int idxStart = 0)
    {
        int idx = -1;
        for (int i = idxStart; i < (int)indexOfConflict.size(); ++i)
        {
            const Cycle<vType, wType, attrType> &currCycle = cycles[indexOfConflict[i].first];
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
                    same = false;
                    for (int m = 0; m < (int)localDelArcsShort.size(); ++m)
                    {
                        if (shortInfo[k] == localDelArcsShort[m])
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
    static void FindBestSequenceForDelArcs(double &globalSum, vector<tuple<vType, vType, attrType>> &globalDelArcs,
                                           const double localSum, vector<tuple<vType, vType, attrType>> &localDelArcs,
                                           vector<unsigned> &localDelArcsShort,
                                           const vector<Cycle<vType, wType, attrType>> &cycles, const vector<pair<int, int>> &indexOfConflict,
                                           const int lastIndexOfConflict)
    {
        int nextConflict = GetIdxOfNextCycle(localDelArcsShort, cycles, indexOfConflict, lastIndexOfConflict + 1);
        if (nextConflict == -1)
        {
            globalSum = localSum;
            globalDelArcs = localDelArcs;

            char buf[256];
            sprintf(buf, "  global sum = %f, last idx of conflict %d\n", globalSum, lastIndexOfConflict);
            addToGlobalBufferAndPrint(buf);
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

                if (localSum + currW < globalSum)
                {
                    localDelArcs.push_back(make_tuple(currArc.first, currArc.second, currAttr));
                    localDelArcsShort.push_back(shortInfo[i]);
                    FindBestSequenceForDelArcs(globalSum, globalDelArcs, localSum + currW, localDelArcs, localDelArcsShort, cycles, indexOfConflict, nextConflict);
                    localDelArcs.pop_back();
                    localDelArcsShort.pop_back();
                }
                else
                    break;
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
    static double CreateOptimalAlignementTree(GraphCSR<vType, wType, attrType> &G, const Arrays<vType> &allArrays,
                                              vector<tuple<vType, vType, attrType>> &toDelArcs, bool needPrint = true)
    {        
        double globalSum = 0;
        vector<vector<Cycle<vType, wType, attrType>>> AllCycles;

        G.GetAllSimpleLoops(AllCycles, needPrint);
        toDelArcs.clear();

        for (int k = 0; k < AllCycles.size(); ++k)
        {
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
                    addToGlobalBufferAndPrint(buf);
                }
            }
                        
            double timeR = omp_get_wtime();
            if (countConflicts != 0)
            {
                const int lastIndexOfConflict = -1;
                FindBestSequenceForDelArcs(globalSumLocal, toDelArcs, 0, localDelArcs, localDelArcShort, cycles, indexOfConflict, lastIndexOfConflict);
                globalSum += globalSumLocal;
            }

            if (needPrint)
            {
                sprintf(buf, "PROF: FindBestSequenceForDelArcs: %f sec\n", omp_get_wtime() - timeR);
                addToGlobalBufferAndPrint(buf);
            }
            timeR = omp_get_wtime();
            FindNonConflictDelArcs(toDelArcs, cycles);
            if (needPrint)
            {
                sprintf(buf, "PROF: FindNonConflictDelArcs %f\n", omp_get_wtime() - timeR);
                addToGlobalBufferAndPrint(buf);
            }
        }
        return globalSum;
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
        if (!onlyGraph)
        {
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
            G.HighlightLinks();

            //old simple algorithm
            //G.RemoveMultipleArcsByWeights();

            //new algorithm with optimal strategy
            G.RemoveMultipleArcsOptimal();

            globalSum = CreateOptimalAlignementTree(G, allArrays, toDelArcs);

            reducedG = G;
            reducedG.RemovedEdges(toDelArcs, allArrays);

            //try to resolve conflicts of 1 type
            const set<Array*> &arrays = allArrays.GetArrays();
            for (auto it = arrays.begin(); it != arrays.end(); ++it)
            {
                Array *currArray = *it;
                vector<vType> verts;

                if (currArray->GetDimSize() == 1)
                    continue;

                int err = allArrays.GetAllVertNumber(currArray, verts);
                if (err != 0)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                attrType tmpPair = make_pair(make_pair(1, 0), make_pair(1, 0));
                for (int i = 0; i < verts.size(); ++i)
                {
                    for (int j = i + 1; j < verts.size(); ++j)
                    {
                        GraphCSR<vType, wType, attrType> findConflict(reducedG);
                        vector<tuple<int, int, attrType>> toDelArcsLocal;
                        findConflict.AddToGraph(verts[i], verts[j], INT_MAX, tmpPair, WW_link);

                        globalSum = CreateOptimalAlignementTree(findConflict, allArrays, toDelArcsLocal, false);
                        if (toDelArcsLocal.size() != 0)
                            reducedG.RemovedEdges(toDelArcsLocal, allArrays);
                    }
                }
            }  

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

        string FullName = "_full_graph_reg" + std::to_string(regionNum) + ".txt";
        string ReducedName = "_reduced_graph_reg" + std::to_string(regionNum) + ".txt";

        if (keepFiles)
        {
            if (!onlyGraph)
            {
                G.CreateGraphWiz(FullName.c_str(), toDelArcs, allArrays, false);
                reducedG.CreateGraphWiz(ReducedName.c_str(), vector<tuple<int, int, attrType>>(), allArrays, true);
            }
            else
            {
                G.CreateGraphWiz(FullName.c_str(), vector<tuple<int, int, attrType>>(), allArrays, true);
                reducedG.CreateGraphWiz(ReducedName.c_str(), vector<tuple<int, int, attrType>>(), allArrays, true);
            }
        }
    }

    template void createOptimalDistribution(GraphCSR<int, double, attrType> &G, GraphCSR<int, double, attrType> &reducedG, const Arrays<int> &allArrays, const int regionNum, bool onlyGraph);
    template int AddArrayAccess(GraphCSR<int, double, attrType> &G, Arrays<int> &allArrays, Array *arr1, Array *arr2, pair<int, int> arc, double arcWeight, const attrType &arcAttr, const uint8_t linkType);
}

#undef ERROR_CHECK
#undef FIRST
#undef SECOND
#undef THIRD