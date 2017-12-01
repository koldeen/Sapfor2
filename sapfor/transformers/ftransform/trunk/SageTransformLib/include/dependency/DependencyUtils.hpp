#ifndef DEPENDENCY_UTILS_HPP
#define DEPENDENCY_UTILS_HPP

#include <set>
#include <vector>

#include "Dependency.hpp"

using std::set;
using std::vector;
typedef unsigned int uint;

namespace SageTransform {
	namespace DependencyUtils {
		set<Dependency> filterDepsType(const set<Dependency> & deps, int depTypeMask);

		set<Dependency> filterDepsDistance(const set<Dependency> & deps, uint distanceMinInc, uint distanceMaxInc);

		//result is sorted in ascending order
		vector<uint> getFroms(const set<Dependency> & deps);

		set<uint> getTos(const set<Dependency> & deps);
	}
}

#endif //DEPENDENCY_UTILS_HPP
