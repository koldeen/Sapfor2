#include "StatementsSplitter.hpp"

#include <algorithm>
using namespace SageTransform;

bool StatementsSplitter::canSplit(const DependencyInfo & info) {
	return getValidSplit(info).size() != 1;
}

vector<vector<uint>> StatementsSplitter::getValidSplit(const DependencyInfo& info) {
	vector<vector<uint>> result;
	uint nextAdded = 0;
	while (nextAdded < info.getStatementCount()) {
		vector<uint> group = getSplitGroupFor((uint)(nextAdded), info);
		nextAdded = group.at(group.size() - 1) + 1;
		//skip full private groups - they do nothing
		if (!isFullPrivate(group, info.getPrivateStatements())) {
			result.push_back(group);
		}
	}
	result = mergeBackIllegalSplits(result, info);
	return result;
}

bool StatementsSplitter::isFullPrivate(const vector<uint>& group, const set<int>& privates) {
	for (uint i = 0; i < group.size(); ++i) {
		int ind = group.at(i);
		if (std::find(privates.begin(), privates.end(), ind) == privates.end()) {
			return false;
		}
	}
	return true;
}

vector<uint> StatementsSplitter::getSplitGroupFor(uint stmtNum, const DependencyInfo & info) {
	vector<uint> result;
	vector<uint> toProcess;
	set<uint> processed;
	toProcess.push_back(stmtNum);
//	uint border = stmtNum;
	set<int> privates = info.getPrivateStatements();
	while (!toProcess.empty()) {
		uint inProcess = toProcess.at(toProcess.size() - 1);
		processed.insert(inProcess);
		toProcess.pop_back();

		set<uint> flowDeps =
			getFroms(
				filterDepsDistance(
					info.getStatementDependencies(Dependency::FLOW_DEP, inProcess), 0, 0
				)
			);
		//todo TAKE ONLY PRIVATE FLOW DEPS
		//todo OTHER FLOW DEPS COME OK from previous cycle
		for (set<uint>::iterator it = flowDeps.begin(); it != flowDeps.end(); ++it) {
			if (std::find(processed.begin(), processed.end(), *it) == processed.end()) {
				toProcess.push_back(*it);
			}
		}		
		/*
		what logic was here ???
		//adding statements needed due to dependencies
		uint needUpTo = countMaxRequiredStatementNum(processed, info);
		if (needUpTo > border) {
			for (uint i = border + 1; i <= needUpTo; ++i) {
				toProcess.push_back(i);
			}
			border = needUpTo;
		}*/
	}
	result.insert(result.begin(), processed.begin(), processed.end());
	std::sort(result.begin(), result.end());
	return result;
}

//???
vector<vector<uint>> StatementsSplitter::mergeBackIllegalSplits(vector<vector<uint>> splitSchema, const DependencyInfo & info) {
	//!!! can make bad split schema, with leftward arcs	
	for (int groupIdRev = splitSchema.size() - 1; groupIdRev >= 0; groupIdRev--) {
		uint groupId = (uint) groupIdRev;
		for (int stmtIdRev = splitSchema.at(groupId).size() - 1; stmtIdRev >= 0; stmtIdRev--) {
			uint stmtId = (uint) stmtIdRev;
			set<Dependency> deps = info.getStatementDependencies(Dependency::FLOW_DEP, splitSchema.at(groupId).at(stmtId));
			for (set<Dependency>::iterator depI = deps.begin(); depI != deps.end(); depI++) {				
				if (info.getDependency(Dependency::OUTPUT_DEP, depI->getFrom(), depI->getFrom())) {
					//the data source stmt is output dependant from itself -> rewrites itself
					//ignoring distance for now
					splitSchema.at(groupId).insert(splitSchema.at(groupId).begin() + stmtId, depI->getFrom());
					stmtIdRev++; //compensate for added element
				}
			}
		}
	}
	return splitSchema;
}

vector<vector<uint>> StatementsSplitter::mergeGroups(const vector<vector<uint>> &groups, uint group1index, uint group2index) {	
	//nothing to do if merging into self
	if (group1index == group2index) return groups;

	vector<vector<uint>> result;
	//prepare merged group
	vector<uint> group1 = result.at(group1index);
	vector<uint> group2 = result.at(group2index);
	vector<uint> mergedGroup;
	mergedGroup.insert(mergedGroup.end(), group1.begin(), group1.end());
	mergedGroup.insert(mergedGroup.end(), group2.begin(), group2.end());
	
	uint firstGroup, secondGroup;
	firstGroup = group1index < group2index ? group1index : group2index;
	secondGroup = group1index < group2index ? group2index : group1index;

	//copy first part
	for (uint i = 0; i < firstGroup; i++) {
		result.push_back(groups.at(i));
	}
	if (group1index == firstGroup) {
		//if first group is group destination
		result.push_back(mergedGroup);
	}
	//copy middle part
	for (uint i = firstGroup + 1; i < secondGroup; i++) {		
		result.push_back(groups.at(i));
	}
	if (group1index == secondGroup) {
		//if second group is group destination
		result.push_back(mergedGroup);
	}	
	//copy end part
	for (uint i = secondGroup + 1; i < groups.size(); i++) {
		result.push_back(groups.at(i));
	}	
	return result;
}


uint StatementsSplitter::countMaxRequiredStatementNum(uint stmtNum, const DependencyInfo & info) {
	set<Dependency> dependencies = info.getStatementDependencies(Dependency::ALL_DEP, stmtNum);
	uint result = stmtNum;
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		if (it->getFrom() > result) {
			result = it->getFrom();
		}
	}
	return result;
}

set<Dependency> StatementsSplitter::filterDepsType(const set<Dependency> & deps, int depTypeMask) {
	set<Dependency> result;
	for (set<Dependency>::iterator it = deps.begin(); it != deps.end(); ++it) {
		if (it->getType() & depTypeMask) {
			result.insert(*it);
		}
	}
	return result;
}

set<Dependency> StatementsSplitter::filterDepsDistance(const set<Dependency> & deps, uint distanceMinInc, uint distanceMaxInc) {
	set<Dependency> result;
	for (set<Dependency>::iterator it = deps.begin(); it != deps.end(); ++it) {
		if (it->getDistance() >= distanceMinInc && it->getDistance() <= distanceMaxInc) {
			result.insert(*it);
		}
	}
	return result;
}

set<uint> StatementsSplitter::getFroms(const set<Dependency> & deps) {
	set<uint> result;
	for (set<Dependency>::iterator it = deps.begin(); it != deps.end(); ++it) {
		result.insert(it->getFrom());
	}
	return result;
}
