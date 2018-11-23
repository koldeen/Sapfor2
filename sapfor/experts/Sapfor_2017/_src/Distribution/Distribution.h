#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "GraphCSR.h"
#include "Arrays.h"
#include "Array.h"

namespace DIST = Distribution;
namespace Distribution
{
    template<typename vType, typename wType, typename attrType>
    int AddArrayAccess(GraphCSR<vType, wType, attrType> &G, Arrays<vType> &allArrays, 
                       Array *arr1, Array *arr2, std::pair<int, int> arc, wType arcWeight, 
                       const attrType &arcAttr, const uint8_t linkType);

    template<typename vType, typename wType, typename attrType>
    void createOptimalDistribution(GraphCSR<vType, wType, attrType> &G, GraphCSR<vType, wType, attrType> &reducedG,
                                   const Arrays<vType> &allArrays, const int regionNum, bool onlyGraph);
}
