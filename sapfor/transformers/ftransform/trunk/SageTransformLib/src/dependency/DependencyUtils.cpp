#include "dependency/DependencyUtils.hpp"

#include <algorithm>

using std::sort;
using namespace SageTransform;

set<Dependency> DependencyUtils::filterDepsType(const set<Dependency> & deps, int depTypeMask) {
	set<Dependency> result;
	for (set<Dependency>::const_iterator it = deps.begin(); it != deps.end(); ++it) {
		if (it->getType() & depTypeMask) {
			result.insert(*it);
		}
	}
	return result;
}

set<Dependency> DependencyUtils::filterDepsDistance(const set<Dependency> & deps, uint distanceMinInc, uint distanceMaxInc) {
	set<Dependency> result;
	for (set<Dependency>::const_iterator it = deps.begin(); it != deps.end(); ++it) {
		if (it->getDistance() >= distanceMinInc && it->getDistance() <= distanceMaxInc) {
			result.insert(*it);
		}
	}
	return result;
}

vector<uint> DependencyUtils::getFroms(const set<Dependency> & deps) {
	vector<uint> result;
	for (set<Dependency>::const_iterator it = deps.begin(); it != deps.end(); ++it) {
		result.push_back(it->getFrom());
	}
	sort(result.begin(), result.end());
	return result;
}

set<uint> DependencyUtils::getTos(const set<Dependency> & deps) {
	set<uint> result;
	for (set<Dependency>::const_iterator it = deps.begin(); it != deps.end(); ++it) {
		result.insert(it->getTo());
	}
	return result;
}
