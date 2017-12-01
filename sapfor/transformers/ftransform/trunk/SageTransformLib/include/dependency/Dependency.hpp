#ifndef DEPENDENCY_HPP
#define DEPENDENCY_HPP

#include "user.h"
#include "DependencyType.hpp"

typedef unsigned int uint;
namespace SageTransform {

    /**
     * Class for an arc or edge in the dependency graph.
     */
    class Dependency {
    public:
        static int ALL_DEP, FLOW_DEP, ANTI_DEP, OUTPUT_DEP;

        Dependency(int type, uint from, uint to, uint distance);

        bool operator<(const Dependency &other) const;

        inline uint getFrom() const { return from; }

        inline uint getTo() const { return to; }

        inline uint getDistance() const { return distance; }

        inline uint getType() const { return type; }

    private:
        uint from, to, distance;
        int type;
    };
}
#endif //DEPENDENCY_HPP
