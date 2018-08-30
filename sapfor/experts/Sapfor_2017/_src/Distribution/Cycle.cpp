#include "../Utils/leak_detector.h"

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "Cycle.h"

using std::vector;
using std::pair;

namespace Distribution
{
    template<typename vType, typename wType, typename attrType>
    void Cycle<vType, wType, attrType>::
        AddArc(const pair<vType, vType> &newAcr, const wType wArc, const attrType &attrArc, const unsigned info)
    {
        Arcs.push_back(newAcr);
        wArcs.push_back(wArc);
        attrArcs.push_back(attrArc);
        compressedInfo.push_back(info);
    }

    template<typename vType, typename wType, typename attrType>
    void Cycle<vType, wType, attrType>::
        AddArc(const pair<vType, vType> &newAcr, const pair<wType, attrType> &paramArc, const unsigned info)
    {
        AddArc(newAcr, paramArc.first, paramArc.second, info);
    }

    template<typename vType, typename wType, typename attrType>
    void Cycle<vType, wType, attrType>::
         AddArc(const vType V1, const vType V2, const pair<wType, attrType> &paramArc, const unsigned info)
    {
        AddArc(std::make_pair(V1, V2), paramArc.first, paramArc.second, info);
    }

    template<typename vType, typename wType, typename attrType>
    void Cycle<vType, wType, attrType>::
         AddArc(const vType V1, const vType V2, const wType wArc, const attrType &attrArc, const unsigned info)
    {
        AddArc(std::make_pair(V1, V2), wArc, attrArc, info);
    }

    template<typename vType, typename wType, typename attrType>
    wType Cycle<vType, wType, attrType>::
          GetCycleSum() const
    {
        wType sum = 0.0;
        for (vType i = 0; i < (vType)Arcs.size(); ++i)
            sum += wArcs[i];
        return sum;
    }

    template<typename vType, typename wType, typename attrType>
    void Cycle<vType, wType, attrType>::
         SortArcs()
    {
        vector<pair<wType, vType>> toSort;
        // sort by key
        for (vType i = 0; i < (vType)wArcs.size(); ++i)
            toSort.push_back(std::make_pair(wArcs[i], i));
        sort(toSort.begin(), toSort.end(), comparator);

        vector<pair<vType, vType>> new_Arcs(wArcs.size());
        vector<wType> new_wArcs(wArcs.size());
        vector<attrType> new_attrArcs(wArcs.size());
        vector<unsigned> new_info(wArcs.size());

        // complete sorting
        for (vType i = 0; i < (vType)wArcs.size(); ++i)
        {
            const vType idx = toSort[i].second;
            new_Arcs[i] = Arcs[idx];
            new_wArcs[i] = wArcs[idx];
            new_attrArcs[i] = attrArcs[idx];

            if (compressedInfo.size())
                new_info[i] = compressedInfo[idx];
        }

        attrArcs = new_attrArcs;
        wArcs = new_wArcs;
        Arcs = new_Arcs;
        compressedInfo = new_info;
    }

    template<typename vType, typename wType, typename attrType>
    bool Cycle<vType, wType, attrType>::
         operator<(const Cycle<vType, wType, attrType> &right) const
    {
        return this->GetCycleSum() > right.GetCycleSum();
    }

    template<typename vType, typename wType, typename attrType>
    void Cycle<vType, wType, attrType>::
         PrintValue() const
    {
        printf("acrs\n");
        for (int i = 0; i < Arcs.size(); ++i)
            printf("%d %d\n", Arcs[i].first, Arcs[i].second);
        printf("we\n");
        for (int i = 0; i < wArcs.size(); ++i)
            printf("%f\n", wArcs[i]);
        printf("attr\n");
        for (int i = 0; i < attrArcs.size(); ++i)
            printf("[%d %d] [%d %d]\n", attrArcs[i].first.first, attrArcs[i].first.second, attrArcs[i].second.first, attrArcs[i].second.second);
    }

    template<typename vType, typename wType, typename attrType>
    void Cycle<vType, wType, attrType>::
         PrintArcs() const
    {
        for (int i = 0; i < Arcs.size(); ++i)
            printf("[%d %d] ", Arcs[i].first, Arcs[i].second);
        printf("\n");
    }

    template class Cycle<int, double, attrType>;
}

