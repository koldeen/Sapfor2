#include "StatementReshuffler.hpp"

#include <set>

using std::set;
using namespace SageTransform;

vector<uint> StatementReshuffler::reshuffle(DependencyInfo& info) {	
	vector<uint> result = getOrderVector(0, 1, info.getStatementCount());
	while(hasLeftwardDependency(info)) {
		//need to be able to skip bad dependencies, loops etc
		Dependency dep = getLeftwardDependency(info);
		uint rightLimit = countRightLimit(dep.getTo(), info);
		uint rightRequirement = countRightRequirement(dep.getTo(), info);
		if (rightRequirement < rightLimit) {
			vector<uint> newStmtOrder = getOrderVector(dep.getTo(), rightLimit, info.getStatementCount());
			info.reorderStatements(newStmtOrder);
			result = product(newStmtOrder, result);
		} else {
			//cannot do anything
			break;
		}
	}
	return result;
}

bool StatementReshuffler::hasLeftwardDependency(const DependencyInfo& info) {
	for (uint i = 0; i < info.getStatementCount(); ++i) {
		set<Dependency> depsTmp = info.getStatementDependants(Dependency::ALL_DEP, i);
		for (set<Dependency>::iterator it = depsTmp.begin(); it != depsTmp.end(); ++it) {			
			if (it->getTo() < i) {
				//found arc wich goes to left
				return true;
			}
		}
	}
	//leftward arcs not found
	return false;
}

Dependency StatementReshuffler::getLeftwardDependency(const DependencyInfo& info) {
	for (uint i = 0; i < info.getStatementCount(); ++i) {
		set<Dependency> depsTmp = info.getStatementDependants(Dependency::ALL_DEP, i);
		for (set<Dependency>::iterator it = depsTmp.begin(); it != depsTmp.end(); ++it) {			
			if (it->getTo() < i) {
				//found arc wich goes to left				
				return *it;
			}
		}
	}
	//leftward arcs not found
	throw "StatementReshuffler::getLeftwardDependency(). Illegal state reached";
}

uint StatementReshuffler::countRightLimit(uint stmtNum, const DependencyInfo& info) {
	//what dependency type to use?
	uint result = info.getStatementCount();
	set<Dependency> dependants = info.getStatementDependants(Dependency::ALL_DEP, stmtNum);
	for (set<Dependency>::iterator it = dependants.begin(); it != dependants.end(); ++it) {
		if (it->getTo() >= stmtNum && it->getTo() < result) {
			result = it->getTo();
		}
	}
	return result;
}

uint StatementReshuffler::countRightRequirement(uint stmtNum, const DependencyInfo& info) {
	//what dependency type to use?
	uint result = 0; //this should not be the case
	set<Dependency> dependencies = info.getStatementDependencies(Dependency::ALL_DEP, stmtNum);
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		if (it->getFrom() >= stmtNum && it->getFrom() > result) {
			result = it->getFrom();
		}
	}
	return result;
}

vector<uint> StatementReshuffler::getOrderVector(uint thisOldPosIs, uint beforeThisOldPos, uint size) {
	vector<uint> result;
	for (uint i = 0; i < beforeThisOldPos; i++) {
		if (i == thisOldPosIs) continue;
		result.push_back(i);
	}
	result.push_back(thisOldPosIs);
	for (uint i = beforeThisOldPos; i < size; i++) {
		if (i == thisOldPosIs) continue;
		result.push_back(i);
	}
	return result;
}

vector<uint> StatementReshuffler::product(vector<uint> reorderSecond, vector<uint> reorderFirst) {
	vector<uint> result;
	for (uint i = 0; i < reorderSecond.size(); ++i) {
		uint oldIndex = reorderSecond.at(i);
		uint oldOldIndex = reorderFirst.at(oldIndex);
		result.push_back(oldOldIndex);
	}
	return result;
}
