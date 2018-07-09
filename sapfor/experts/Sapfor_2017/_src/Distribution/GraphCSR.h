#pragma once

#include <vector>
#include <map>
#include <set>
#include <tuple>

#include "Cycle.h"
#include "Arrays.h"
#include "../Utils/errors.h"

typedef enum links { RR_link, WR_link, WW_link } LinkType;

#define MAX_LOOP_DIM  8
#define MAX_CHAIN_LEN 8

namespace Distribution
{
    template<typename vType, typename wType, typename attrType>
    class GraphCSR
    {
    private:
        vType numVerts;
        vType numEdges;
        vType lastNumOfV;

        std::vector<vType> neighbors;
        std::vector<vType> edges;
        std::vector<wType> weights;
        std::vector<uint8_t> linkType;
        std::vector<attrType> attributes;
        std::vector<vType> localIdx;
        std::vector<vType> globalIdx;

        //for finding
        std::vector<vType> color;
        vType *activeV;
        vType *activeE;
        std::pair<wType, attrType> *activeArcs;
        uint64_t usedMem;

        int activeCounter;
        vType findFrom;
        bool hardLinksWasUp;

        int maxChainLen;
        int maxLoopDim;
        uint64_t maxAvailMemory;

        std::map<vType, std::map<vType, std::tuple<int, Array*, std::pair<float, float>>>> cacheLinks;
        int countRequestsToAdd, countMissToAdd;
    private:
        GraphCSR(const std::vector<vType> &neighbors, const std::vector<vType> &edges,
                 const std::vector<wType> &weights, const std::vector<vType> &localIdx,
                 const std::vector<vType> &globalIdx, const std::vector<attrType> &attributes,
                 const std::vector<uint8_t> &linkType, const bool hardLinksWasUp) :
                 neighbors(neighbors), edges(edges), weights(weights), localIdx(localIdx),
                 globalIdx(globalIdx), attributes(attributes), linkType(linkType), hardLinksWasUp(hardLinksWasUp)
        {
            numVerts = (int)neighbors.size() - 1;
            numEdges = (int)edges.size();
        }

        vType GetLocalVNum(const vType &V, bool &ifNew);
        void AddEdgeToGraph(const vType &V1, const vType &V2, const wType &W, const attrType &attr, const bool &ifNew, const uint8_t linkType);
        void IncreaseWeight(const int &idx, const int &idxRev, const wType &W);
        int CheckExist(const vType &V1, const vType &V2, const attrType &attr, const bool &ifNew);        
        std::set<vType> FindTrees(std::vector<vType> &inTree, std::vector<std::vector<vType>> &vertByTrees);

        //old algorithm without sort in the fly
        //TODO: need to update
        void FindLoop(std::vector<Cycle<vType, wType, attrType>> &cycles, const vType V, const vType VPrev);        
        void FindLoop(std::vector<std::map<std::vector<unsigned>, Cycle<vType, wType, attrType>>> &cycles, const vType V, const vType VPrev, const std::vector<vType> &numbers);
        void RemoveDuplicates(std::vector<Cycle<vType, wType, attrType>> &cycles);
        bool findLink(const vType v1, std::pair<int, int> &inGraphAttr1, const vType v2, std::pair<int, int> &inGraphAttr2);
        std::pair<float, float> findLinkWithTempate2(const vType v1, int &templV, Array *&templ, const Arrays<vType> &allArrays, std::set<vType> wasDone);
        int findDimNumLink(const vType v, const Array *to, const Arrays<vType> &allArrays, std::set<vType> &wasDone) const;
        bool checkFirstCoefOfNode(vType node);
        bool getOptimalBoundsForNode(vType nodeFrom, vType nodeTo, int &needBound, std::pair<int, int> &bounds);        
        bool hasLinkWithTempate(const vType root, const Arrays<vType> &allArrays);
    public:
        GraphCSR()
        {
            cleanData();
        }

        GraphCSR(const GraphCSR &G) : GraphCSR(G.neighbors, G.edges, G.weights, G.localIdx, G.globalIdx, G.attributes, G.linkType, G.hardLinksWasUp)
        {
            this->lastNumOfV = G.lastNumOfV;
            this->maxLoopDim = G.maxLoopDim;
            this->maxChainLen = G.maxChainLen;
            this->maxAvailMemory = G.maxAvailMemory;
            this->countRequestsToAdd = G.countRequestsToAdd;
            this->countMissToAdd = G.countMissToAdd;
        }

        void cleanData()
        {
            lastNumOfV = numVerts = numEdges = 0;
            hardLinksWasUp = false;
            neighbors.resize(0);
            edges.resize(0);
            weights.resize(0);
            linkType.resize(0);
            localIdx.resize(0);
            globalIdx.resize(0);
            attributes.resize(0);

            maxAvailMemory = 0;
            maxLoopDim = MAX_LOOP_DIM;
            maxChainLen = MAX_CHAIN_LEN;

            cacheLinks.clear();
            countRequestsToAdd = 0;
            countMissToAdd = 0;
        }

        void ClearGraphCSR()
        {
            lastNumOfV = numVerts = numEdges = 0;
            hardLinksWasUp = false;
            neighbors.resize(0);
            edges.resize(0);
            weights.resize(0);
            linkType.resize(0);
            localIdx.resize(0);
            globalIdx.resize(0);
            attributes.resize(0);

            maxLoopDim = MAX_LOOP_DIM;
            maxChainLen = MAX_CHAIN_LEN;
            maxAvailMemory = 0;
            countRequestsToAdd = 0;
            countMissToAdd = 0;
        }

        bool SaveGraphToFile(FILE *file);
        bool LoadGraphFromFile(FILE *file);
        int AddToGraph(const vType &V1, const vType &V2, const wType &W, const attrType &attr, const uint8_t linkType);
        void GetAllSimpleLoops(std::vector<std::vector<Cycle<vType, wType, attrType>>> &cycles, bool needPrint);
        int SortLoopsBySize(std::vector<Cycle<vType, wType, attrType>> &cycles, bool needPrint);
        int SortLoopsByWeight(std::vector<Cycle<vType, wType, attrType>> &cycles, bool needPrint);
        int GetConflictCycles(const std::vector<Cycle<vType, wType, attrType>> &cycles, const Arrays<vType> &allArrays, std::vector<std::pair<int, int>> &indexOfConflict, bool needPrint);
        void RemoveMultipleArcsByWeights();
        void RemoveMultipleArcsOptimal();
        int CreateGraphWiz(const char *fileName, const std::vector<std::tuple<vType, vType, attrType>> &toDelArcs, const Arrays<vType> &allArrays, const bool onlyTree);
        void RemovedEdges(const std::vector<std::tuple<vType, vType, attrType>> &toDelArcs, const Arrays<vType> &allArrays);
        void HighlightLinks();

        //NOTE, it correctly works only with reduce graph
        bool hasTheSameAlignment(const vType v1, const std::pair<int, int> &attr1, const vType v2, const std::pair<int, int> &attr2);
        int GetAlignRuleForArray(Array *inputArray, const Arrays<vType> &allArrays, std::vector<std::vector<std::tuple<Array*, vType, attrType>>> &assignedArrays);
        int GetAlignRuleWithTemplate(Array *inputArray, const Arrays<vType> &allArrays, std::vector<std::tuple<Array*, vType, std::pair<int, int>>> &rules, const int regionId);
        void FindLinksBetweenArrays(const Arrays<vType> &allArrays, const Array *from, const Array *to, std::vector<int> &links) const;
        void FindLinkWithMaxDim(const vType from, const Arrays<vType> &allArrays, std::pair<Array*, int> &result, std::set<int> &wasDone);
        int FindAllArraysTrees(std::map<Array*, int> &trees, const Arrays<vType> &allArrays);

        vType GetNumberOfV() const { return numVerts; }
        vType GetNumberOfE() const { return numEdges; }

        void SetMaxLoopDim(const int newMaxLoopDim) { maxLoopDim = newMaxLoopDim; }
        void SetMaxChainLen(const int newMaxChainLen) { maxChainLen = newMaxChainLen; }
        int GetMaxLoopDim() const { return maxLoopDim; }
        int GetMaxChainLen() const { return maxChainLen; }
        void SetMaxAvailMemory(const uint64_t memSize) { maxAvailMemory = memSize; }
        void ChangeQuality(const int newMaxLoopDim, const int newMaxChainLen) { SetMaxLoopDim(newMaxLoopDim); SetMaxChainLen(newMaxChainLen); }
        int getCountOfReq() const { return countRequestsToAdd; }
        int getCountOfMiss() const { return countMissToAdd; }
    };

    std::pair<int, int> Fx(const std::pair<int, int> &x, const std::pair<int, int> &F);
}
