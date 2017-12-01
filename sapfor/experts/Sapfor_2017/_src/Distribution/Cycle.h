#pragma once

#include <vector>
#include <algorithm>

#include "../types.h"

namespace Distribution
{
    template<typename vType, typename wType, typename attrType>
    class Cycle
    {
    private:
        std::vector<std::pair<vType, vType>> Arcs;
        std::vector<wType> wArcs;
        std::vector<attrType> attrArcs;
        std::vector<unsigned> compressedInfo;

        static bool comparator(std::pair<wType, vType> left, std::pair<wType, vType> right)
        {
            return left.first < right.first;
        }
    public:
        int GetNumArcs() const { return (int)Arcs.size(); }
        const std::vector<std::pair<vType, vType>>& GetArcs() const { return Arcs; }
        const std::vector<wType>& GetWeigthsArcs() const { return wArcs; }
        const std::vector<attrType>& GetAttributesArcs() const { return attrArcs; }

        void AddArc(const std::pair<vType, vType> &newAcr, const wType wArc, const attrType &attrArc, const unsigned info);
        void AddArc(const std::pair<vType, vType> &newAcr, const std::pair<wType, attrType> &paramArc, const unsigned info);
        void AddArc(const vType V1, const vType V2, const std::pair<wType, attrType> &paramArc, const unsigned info);
        void AddArc(const vType V1, const vType V2, const wType wArc, const attrType &attrArc, const unsigned info);
        wType GetCycleSum() const;
        void SortArcs();
        // sort as maximum
        bool operator<(const Cycle<vType, wType, attrType> &right) const;
        void PrintValue() const;
        void PrintArcs() const;
        const std::vector<unsigned>& GetShortInfo() const { return compressedInfo; }

        unsigned getFullSize()
        {
            unsigned fullSize = 0;
            fullSize += (int)Arcs.capacity() * sizeof(vType) * 2;
            fullSize += (int)wArcs.capacity() * sizeof(wType);
            fullSize += (int)attrArcs.capacity() * sizeof(attrArcs);
            fullSize += (int)compressedInfo.capacity();
            return fullSize;
        }
    };
}
