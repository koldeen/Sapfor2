//
// Created by baa on 30.09.17.
//

#include "user.h"
#include <SageTransformException.hpp>
#include "dependency/DependencyType.hpp"
#include "SageAnalysisTool/OmegaForSage/include/lang-interf.h"
#include <SageAnalysisTool/definesValues.h>

using namespace SageTransform;

DepType DependencyType::fromDepNode(depNode *node) {
    if (node->typedep == SCALARDEP) {
        ddnature nature = (ddnature) node->kinddep;
        switch (nature) {
            case ddflow:
                return FLOW_DEP;
            case ddanti:
                return ANTI_DEP;
            case ddoutput:
                return OUTPUT_DEP;
            case ddreduce:
                return REDUCTION_DEP;
            default:
                break;
        }
    }
    return UNKNOWN_DEP;
}
