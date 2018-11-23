#include "dependency/DependencyInfo.hpp"

using namespace SageTransform;

uint DependencyInfo::getStatementCount() const {
	return statementCount;
}

void DependencyInfo::setStatementCount(uint inStmtCount) {
	statementCount = inStmtCount;
}

const Dependency * DependencyInfo::getDependency(int typeMask, uint stmtDepends, uint onThisStmt) const {
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		if ((it->getType() & typeMask) && it->getTo() == stmtDepends && it->getFrom() == onThisStmt) {
			return &(*it);
		}
	}
	return NULL;
}

void DependencyInfo::addDependency(const Dependency& dependency) {
	dependencies.insert(dependency);
}

void DependencyInfo::addDependencies(const set<Dependency>& inDependencies) {	
	dependencies.insert(inDependencies.begin(), inDependencies.end());
}

void DependencyInfo::removeDependency(const Dependency& dependency) {
	dependencies.erase(dependency);
}

set<Dependency> DependencyInfo::getStatementDependencies(int typeMask, uint stmtNum) const {
	set<Dependency> result;
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		if ((it->getType() & typeMask) && it->getTo() == stmtNum) {
			result.insert(*it);
		}
	}
	return result;
}

set<Dependency> DependencyInfo::getStatementDependants(int typeMask, uint stmtNum) const {
	set<Dependency> result;
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		if ((it->getType() & typeMask) && it->getFrom() == stmtNum) {
			result.insert(*it);
		}
	}
	return result;
}

bool DependencyInfo::verifyAndCollapseDependencies() {	
	//verification
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		//for each Dependency
		// it has valid type, valid to, valid from
		if (!(it->getType() && it->getTo() < statementCount && it->getFrom() < statementCount && it->getDistance() >= 0)) {
			return false;
		}
	}
	//verified
	//collapsing
	set<int> distances;
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		distances.insert(it->getDistance());
	}
	set<Dependency> tmp;
	for (set<int>::iterator it = distances.begin(); it != distances.end(); ++it) {	
		int ** depsTmp = getZeroMatrix(statementCount);
		loadToMatrix(dependencies, depsTmp, *it);
	
		loadFromMatrix(tmp, depsTmp, *it);
		deleteMatrix(depsTmp, statementCount);		
	}
	dependencies.clear();
	dependencies.insert(tmp.begin(), tmp.end());
	return true;
}

void DependencyInfo::reorderStatements(const vector<uint>& newOrder) {
	if (newOrder.size() != statementCount) throw "DependencyInfo::reorderStatements() Bad resize vector - wrong number of elements";
	//vector should contain only elements from 0 to N-1, all should be present
	//ignoring distances
	set<int> distances;
	for (set<Dependency>::iterator it = dependencies.begin(); it != dependencies.end(); ++it) {
		distances.insert(it->getDistance());
	}
	set<Dependency> tmp;
	for (set<int>::iterator pDist = distances.begin(); pDist != distances.end(); ++pDist) {
		int ** pDepTypesMatrix = getZeroMatrix(statementCount);
		loadToMatrix(dependencies, pDepTypesMatrix, *pDist);

		int ** pDepTypesTmp = getZeroMatrix(statementCount);
		uint oldIndex;
		for (uint newIndex = 0; newIndex < statementCount; newIndex++) {
			oldIndex = newOrder.at(newIndex);
			for (uint j = 0; j < statementCount; j++) {
				pDepTypesTmp[newIndex][j] = pDepTypesMatrix[oldIndex][j];
			}
		}
		deleteMatrix(pDepTypesMatrix, statementCount);
		//rows swapped
	
		pDepTypesMatrix = getZeroMatrix(statementCount);
		for (uint newIndex = 0; newIndex < statementCount; newIndex++) {
			oldIndex = newOrder.at(newIndex);
			for (uint j = 0; j < statementCount; j++) {
				pDepTypesMatrix[j][newIndex] = pDepTypesTmp[j][oldIndex];
			}
		}
		//columns swapped
		loadFromMatrix(tmp, pDepTypesMatrix, *pDist);
		deleteMatrix(pDepTypesMatrix, statementCount);
		deleteMatrix(pDepTypesTmp, statementCount);
	}
	dependencies.clear();
	dependencies.insert(tmp.begin(), tmp.end());	
}

void DependencyInfo::loadToMatrix(const set<Dependency> &deps, int ** pTypes, uint distance) {
	for (set<Dependency>::iterator it = deps.begin(); it != deps.end(); ++it) {
		if (it->getDistance() == distance) {
			pTypes[it->getTo()][it->getFrom()] |= it->getType();
		}
	}
}

void DependencyInfo::loadFromMatrix(set<Dependency> &deps, int ** pTypes, uint distance) {
	for (uint i = 0; i < statementCount; i++) {
		for (uint j = 0; j < statementCount; j++) {
			if (pTypes[i][j] & Dependency::ALL_DEP) {
				deps.insert(Dependency(pTypes[i][j], j, i, distance));
			}
		}
	}	
}

int ** DependencyInfo::getZeroMatrix(uint size) {
	int ** pMatrix = new int *[size];
	for (uint i = 0; i < size; i++) {
		pMatrix[i] = new int[size];
		for (uint j = 0; j < size; j++) {
			pMatrix[i][j] = 0;
		}
	}
	return pMatrix;
}

void DependencyInfo::deleteMatrix(int ** pMatrix, uint size) {
	for (uint i = 0; i < size; i++) {
		delete[] pMatrix[i];
	}
	delete[] pMatrix;
}

void DependencyInfo::usePrivateVars(SgStatement * pZerothStmt) {
	SgStatement * stmt = pZerothStmt;
	SgAssignStmt * assignStmt;
	SgVarRefExp * varRefExp;
	SgVariableSymb * varSymb;
	for (unsigned int i = 0; i < statementCount; ++i) {
		if ((assignStmt = isSgAssignStmt(stmt))) {
			if ((varRefExp = isSgVarRefExp(assignStmt->lhs()))) {
				if ((varSymb = isSgVariableSymb(varRefExp->symbol()))) {
					string ident(varSymb->identifier());
					if (privateVarIdents.find(ident) != privateVarIdents.end()) {
						privateEffectStatement.insert(i);
						set<Dependency> deps = getStatementDependants(Dependency::OUTPUT_DEP, i);
						set<Dependency>::iterator it;
						for (it = deps.begin(); it != deps.end(); ++it) {
							if (it->getDistance() > 0) {
								removeDependency(*it);
							}
						}
					}
				}
			}
		}
		stmt = stmt->lexNext();
	}
}
