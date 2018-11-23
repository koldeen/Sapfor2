#include "dependency/Dependency.hpp"

using namespace SageTransform;

int Dependency::ALL_DEP = 0xFFFF;
int Dependency::FLOW_DEP = 1 << 0;
int Dependency::ANTI_DEP = 1 << 1;
int Dependency::OUTPUT_DEP = 1 << 2;

Dependency::Dependency(int inType, unsigned int inFrom, unsigned int inTo, unsigned int inDistance) {
	type = inType;
	from = inFrom;
	to = inTo;
	distance = inDistance;
}

bool Dependency::operator<( const Dependency& other ) const {
	if (to < other.to) {
		return true;
	} else if (to == other.to && from < other.from) {
		return true;
	} else if (to == other.to && from == other.from && distance < other.distance) {
		return true;
	} else if (to == other.to && from == other.from && distance == other.distance && type < other.type) {
		return true;
	}
	return false;
}
