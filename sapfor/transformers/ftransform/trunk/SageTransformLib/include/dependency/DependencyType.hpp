//
// Created by baa on 30.09.17.
//

#ifndef FTRANSFORM_DEPENDENCYTYPE_HPP
#define FTRANSFORM_DEPENDENCYTYPE_HPP

#include "SageAnalysisTool/depGraph.h"

typedef int DepType;
namespace SageTransform {    
    namespace DependencyType {
        const DepType FLOW_DEP = 1;
        const DepType ANTI_DEP = 2;
        const DepType OUTPUT_DEP = 3;
        const DepType PRIVATE_DEP = 4;
        const DepType REDUCTION_DEP = 5;
        const DepType UNKNOWN_DEP = -1;

        DepType fromDepNode(depNode* node);
    };
}

#endif //FTRANSFORM_DEPENDENCYTYPE_HPP
