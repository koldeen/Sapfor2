//
// Created by baa on 30.09.17.
//

#ifndef FTRANSFORM_DEPENDENCYTYPE_HPP
#define FTRANSFORM_DEPENDENCYTYPE_HPP

namespace SageTransform {
    enum class DependencyType {
        FLOW_DEP,
        ANTI_DEP,
        OUTPUT_DEP,

        //from omega test
        PRIVATE_DEP,
        REDUCTION_DEP,

        UNKNOWN_DEP,
        NO_VALUE
    };
}

#endif //FTRANSFORM_DEPENDENCYTYPE_HPP
