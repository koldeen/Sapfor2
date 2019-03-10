#include "LoopTransformSplit.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>

#include "SageUtils.hpp"
#include "Dependencies.hpp"
#include "LoopTransformMerge.hpp"
#include "TempArrayTransform.hpp"

using std::find;
using std::set;
using namespace SageTransform;
using SageUtils::getLastLoopStatement;
using SageUtils::getLhsSymbol;
using SageUtils::decodeStmtVariant;

using DependencyUtils::filterDepsDistance;
using DependencyUtils::getTos;
using DependencyUtils::getFroms;
using TempArrayTransform::replaceRhsScalarWithTempArray;

void LoopTransformSplit::intersectInplace(set<uint> &theSet, const vector<uint> & aVector) {
	set<uint> tmpSet;
	for (set<uint>::iterator it = theSet.begin(); it != theSet.end(); ++it) {
		uint element = *it;
		if (find(aVector.begin(), aVector.end(), element) != aVector.end()) {
			tmpSet.insert(element);
		}
	}
	theSet.erase(theSet.begin(), theSet.end());
	theSet.insert(tmpSet.begin(), tmpSet.end());
}

bool LoopTransformSplit::containsAll(const set<uint> source, const set<uint> & checked) {
	for (set<uint>::iterator it = checked.begin(); it != checked.end(); ++it) {
		if (find(source.begin(), source.end(), *it) == source.end()) {
			return false;
		}
	}
	return true;
}

bool LoopTransformSplit::containsAll(const vector<uint> source, const set<uint> & checked) {
	for (set<uint>::iterator it = checked.begin(); it != checked.end(); ++it) {
		if (find(source.begin(), source.end(), *it) == source.end()) {
			return false;
		}
	}
	return true;
}

int LoopTransformSplit::getLoopStmtId(SgStatement * stmt) {
	return SageUtils::getAttributeInt(stmt, ATTR_LOOP_STMT_ID);
}

void LoopTransformSplit::setLoopStmtId(SgStatement *stmt, int *value) {
	SageUtils::setAttributeInt(stmt, ATTR_LOOP_STMT_ID, value);
}

//check if loop has statement with LOOP_STMT_ID attribute equal to #loopStmtId
//we work only with one attribute
SgStatement * LoopTransformSplit::hasLoopStmt(SgForStmt * innerLoop, int loopStmtId) {
	SgStatement * result = NULL;
	SgStatement * innerLoopControlEnd = getLastLoopStatement(innerLoop);
	for (SgStatement * stmt = innerLoop->lexNext(); stmt != innerLoopControlEnd; stmt = stmt->lexNext()) {
		if (stmt->numberOfAttributes() > 0) {
			if (getLoopStmtId(stmt) == loopStmtId) {
				result = stmt;
				break;
			}
		}
	}
	return result;
}

set<uint> LoopTransformSplit::getFlowDist0Dependants(const DependencyInfo & depInfo, uint stmtI, const vector<uint> &filterVector) {
	set<Dependency> dependants = depInfo.getStatementDependants(Dependency::FLOW_DEP, stmtI);
	dependants = filterDepsDistance(dependants, 0, 0);
	set<uint> dependantOnes = getTos(dependants);
	intersectInplace(dependantOnes, filterVector);
	return dependantOnes;
}

vector<uint> LoopTransformSplit::getFlowDist0DependenciesRecursive(const DependencyInfo & depInfo, uint stmtI) {
	set<Dependency> result;
	uint size = result.size();
	set<Dependency> dependencies = depInfo.getStatementDependencies(Dependency::FLOW_DEP, stmtI);
	dependencies = filterDepsDistance(dependencies, 0, 0);
	result.insert(dependencies.begin(), dependencies.end());
	while (size < result.size()) {
		for (set<Dependency>::iterator it = result.begin(); it != result.end(); ++it) {
			dependencies = depInfo.getStatementDependencies(Dependency::FLOW_DEP, it->getFrom());
			dependencies = filterDepsDistance(dependencies, 0, 0);
			result.insert(dependencies.begin(), dependencies.end());
		}
		size = result.size();
	}
	result = filterDepsDistance(result, 0, 0);
	vector<uint> resultIndices = getFroms(result);
	return resultIndices;
}

set<uint> LoopTransformSplit::getFromsSet(const set<Dependency> & deps) {
	set<uint> result;
	vector<uint> froms = getFroms(deps);
	result.insert(froms.begin(), froms.end());
	return result;
}

bool LoopTransformSplit::loopContainsStmt(SgForStmt * forLoop, int loopStmtAttrId) {
	for (SgStatement * it = forLoop->lexNext(); it != getLastLoopStatement(forLoop); it = it->lexNext()) {
		SgAttribute * pAttr = it->getAttribute(0, ATTR_LOOP_STMT_ID);
		if (pAttr) {
			int loopStmtIdAttr = getLoopStmtId(it);
			if (loopStmtIdAttr == loopStmtAttrId) {
				return true;
			}
		}
	}
	return false;
}

SgStatement * LoopTransformSplit::findMinGreater(SgForStmt * forLoop, int loopStmtAttrId) {
	int minGreater = 1000000000; //no program should have such loop
	SgStatement * result = getLastLoopStatement(forLoop);
	for (SgStatement * it = forLoop->lexNext(); it != getLastLoopStatement(forLoop); it = it->lexNext()) {
		if (it->getAttribute(0, ATTR_LOOP_STMT_ID)) {
			int stmtId = getLoopStmtId(it);
			if (stmtId > loopStmtAttrId && stmtId < minGreater) {
				minGreater = stmtId;
				result = it;
			}
		}
	}
	return result;
}

SgStatement * LoopTransformSplit::findByStmtId(SgForStmt * forLoop, int loopStmtAttrId) {
	for (SgStatement * it = forLoop->lexNext(); it != getLastLoopStatement(forLoop); it = it->lexNext()) {
		if (it->getAttribute(0, ATTR_LOOP_STMT_ID)) {
			int stmtId = getLoopStmtId(it);
			if (stmtId == loopStmtAttrId) {
				return it;
			}
		}
	}
	return NULL;
}

vector<uint> LoopTransformSplit::getLoopStmtIds(SgForStmt * targetLoopHeader, SgStatement * targetControlEnd) {
	vector<uint> result;
	for (SgStatement * stmt = targetLoopHeader->lexNext(); stmt != targetControlEnd; stmt = stmt->lexNext()) {
		if (SageUtils::hasAttribute(stmt, ATTR_LOOP_STMT_ID)) {
			result.push_back(getLoopStmtId(stmt));
		}
	}
	return result;
}

//TODO split the method, too huge
void LoopTransformSplit::split(SgForStmt * outerForLoopNode, SgForStmt * innerForLoopNode, const vector<vector<uint>> & splitSchema, const DependencyInfo & depInfo) {
	int bodyLength = innerForLoopNode->numberOfChildrenList1() - 1;
	SgStatement * outerLoopControlEnd;
	SgStatement * innerLoopControlEnd;
	if (!(outerLoopControlEnd = getLastLoopStatement(outerForLoopNode))) {
		std::cerr << "LoopSplitter:split() No CONTROL_END Statement found for loop" << std::endl;
		std::cerr.flush();
		exit(1);
	}	
	innerLoopControlEnd = getLastLoopStatement(innerForLoopNode);
	set<int> privateStmts = depInfo.getPrivateStatements();
	set<uint> alreadyUsedStmts;
	SgStatement ** tmpArrayStoreAfter = new SgStatement*[bodyLength];
	for (int i = 0; i < bodyLength; i++) {
		tmpArrayStoreAfter[i] = NULL;
	}	
	int number = 0;	
	int * numbers = new int[bodyLength];	
	for (SgStatement * stmt = innerForLoopNode->lexNext(); stmt != innerLoopControlEnd; stmt = stmt->lexNext()) {
		numbers[number] = number;
		SageUtils::setAttributeInt(stmt, ATTR_LOOP_STMT_ID, numbers + number);
		number++;
	}
	vector<SgForStmt *> outerLoops;
	vector<SgForStmt *> innerLoops;
	for (uint groupI = 0; groupI < splitSchema.size(); ++groupI) {	
		std::cout << "Creating group " << groupI << std::endl;
		const vector<uint>& curGroup = splitSchema.at(groupI);
		SgForStmt * outerLoopCopy = isSgForStmt(outerForLoopNode->copyPtr());
		SgForStmt * innerLoopCopy = SageUtils::getInnermostForStmt(outerLoopCopy);
		for (SgStatement *stmtCpy = innerLoopCopy->lexNext(), *stmtOrig = innerForLoopNode->lexNext(); 
			 stmtCpy != getLastLoopStatement(innerLoopCopy) && stmtOrig != innerLoopControlEnd; 
			 stmtCpy = stmtCpy->lexNext(), stmtOrig = stmtOrig->lexNext()
		) {
			int origI = getLoopStmtId(stmtOrig);
			setLoopStmtId(stmtCpy, numbers + origI);
		}
		outerForLoopNode->insertStmtBefore(*outerLoopCopy);

		outerLoops.push_back(outerLoopCopy);
		innerLoops.push_back(innerLoopCopy);
		
		//the first resulting loop gets all old comments
		if (groupI == 0) outerLoopCopy->setComments(outerForLoopNode->comments());

		//todo
		//assemble bodies manually, stmt by stmt, by ADDING not REMOVING needed stmts
		//if stmt was already used earlier (need to switch order from first group to last)
		//  and is needed here => we have a flow dependency => we need to get assigned value
		//  so we find this value usage in current statement, replace it with tmp array usage
		//  and we add after assignment new one, storing value to a tmp array (this new assignment will be in another group)
		set<uint> scalarRemoved;
		//if (false) //debug disable scalar removal
		for (int stmtI = 0; stmtI < bodyLength; ++stmtI) {
			if (alreadyUsedStmts.find(stmtI) == alreadyUsedStmts.end()) {
				//#stmtI statement was not used in previous groups
				//pass
			} else if (find(splitSchema.at(groupI).begin(), splitSchema.at(groupI).end(), stmtI) != splitSchema.at(groupI).end()
				&& find(privateStmts.begin(), privateStmts.end(), stmtI) != privateStmts.end()) {
				//#stmtI statement was used in previous groups
				//#stmtI has private effect
				//and is needed in current #groupI				

				//we will replace its lhs symbol usage with tmp array in current group
				//and add a storing assignment after previous #stmtI usage
				//TODO: check if temp array replacement is valid
				set<Dependency> dependants = depInfo.getStatementDependants(Dependency::FLOW_DEP, stmtI);
				dependants = filterDepsDistance(dependants, 0, 0);
				set<uint> dependantOnes = getTos(dependants);
				intersectInplace(dependantOnes, splitSchema.at(groupI));				

				//removed statement depends on <st1, st2, stk>
				//for each sti check that
				//  all statements that depend on sti - if they are removed - can remove sti
				set<Dependency> dependancies = depInfo.getStatementDependencies(Dependency::FLOW_DEP, stmtI);
				dependancies = filterDepsDistance(dependancies, 0, 0);
				vector<uint> dependenciesIds = getFroms(dependancies);
				for (vector<uint>::reverse_iterator it = dependenciesIds.rbegin(); it != dependenciesIds.rend(); ++it) {
					//if #*it was not removed yet
					if (find(privateStmts.begin(), privateStmts.end(), *it) == privateStmts.end()) {						
						//get statements that depend on #*it
						set<uint> iDependants = getFlowDist0Dependants(depInfo, *it, splitSchema.at(groupI));
						//if all of dependant statements are already removed
						//TODO: scalar removed does not yet contains stmtI
						if (containsAll(scalarRemoved, iDependants)) {
							//no need for current private statement too
							scalarRemoved.insert(*it);
						};
					}
				}

				//got a set of all flow(dist=0) dependant statements
				//need to check that all dependant statements have non-private effect, are assignments to arrays
				bool allNonPrivate = true;
				for (set<uint>::iterator it = dependantOnes.begin(); it != dependantOnes.end(); ++it) {
					SgAssignStmt * dependantAssign = isSgAssignStmt(innerLoopCopy->childList1(*it));
					if (!isSgArrayRefExp(dependantAssign->lhs())) {
						allNonPrivate = false; 
						break;
					}
				}
				if (allNonPrivate) {					
					for (set<uint>::iterator it = dependantOnes.begin(); it != dependantOnes.end(); ++it) {
						SgAssignStmt * dependantAssign = isSgAssignStmt(innerLoopCopy->childList1(*it));
						//replacing only for assignments into arrays
						//others are assignments into private vars - no need to modify them
						if (isSgArrayRefExp(dependantAssign->lhs())) {
							replaceRhsScalarWithTempArray(
								outerForLoopNode->getScopeForDeclare(),
								isSgAssignStmt(innerLoopCopy->childList1(*it)), //TODO: make not assignments only
								getLhsSymbol(isSgAssignStmt(innerLoopCopy->childList1(stmtI))),
								tmpArrayStoreAfter[stmtI] // store value where it is calculated (in one of previous group in other loop)
							);
							//added storing assignment after, move pointer accordingly
							tmpArrayStoreAfter[stmtI] = tmpArrayStoreAfter[stmtI]->lexNext();
						}
					}
					scalarRemoved.insert(stmtI);
				}
			}
		}
		uint scalarRemovedSize = 0;
		while (scalarRemovedSize != scalarRemoved.size()) {
			scalarRemovedSize = scalarRemoved.size();
			vector<uint> newRemoved;
			for (set<uint>::iterator stmtI = scalarRemoved.begin(); stmtI != scalarRemoved.end(); ++stmtI) {
				//get all statements we need - depend on
				vector<uint> dependencies = getFroms(depInfo.getStatementDependencies(Dependency::FLOW_DEP, *stmtI));
				
				for (vector<uint>::iterator dependencyI = dependencies.begin(); dependencyI != dependencies.end(); ++dependencyI) {					
					if (find(privateStmts.begin(), privateStmts.end(), *stmtI) != privateStmts.end()) {
						//#dependencyI statement has private effect - is assignment to a scalar

						set<uint> dependants = getTos(depInfo.getStatementDependants(Dependency::FLOW_DEP, *dependencyI));
						intersectInplace(dependants, curGroup);

						//if all dependants are removed - nobody needs us - we can remove #dependencyI statement as well
						bool allRemoved = true;
						for (set<uint>::iterator dependantI = dependants.begin(); dependantI != dependants.end(); ++dependantI) {
							if (find(scalarRemoved.begin(), scalarRemoved.end(), *dependantI) == scalarRemoved.end()) {
								//one of the dependant statements is still needed
								//this statement will live then
								allRemoved = false;
								break;
							}
						}
						if (allRemoved) {
							newRemoved.push_back(*dependencyI);
						}
					}
				}
			}
			scalarRemoved.insert(newRemoved.begin(), newRemoved.end());
		}
		//todo need to track new dependency info
		int deleted = 0;
		for (int stmtI = 0; stmtI < bodyLength; ++stmtI) {
			int effectiveStmtIndex = stmtI - deleted;
			if (find(splitSchema.at(groupI).begin(), splitSchema.at(groupI).end(), stmtI) != splitSchema.at(groupI).end()
				&& find(scalarRemoved.begin(), scalarRemoved.end(), stmtI) == scalarRemoved.end()) {
				/* contains */
				//keep stmt					
				std::cout << "  keeping stmt " << stmtI << " " << decodeStmtVariant(innerLoopCopy->childList1(effectiveStmtIndex)->variant()) << std::endl;				

				alreadyUsedStmts.insert(stmtI);
				if (!tmpArrayStoreAfter[stmtI]) {
					tmpArrayStoreAfter[stmtI] = innerLoopCopy->childList1(effectiveStmtIndex);
				}
				if (false /*debug*/) {
					string debugComment("! st_id ");
					std::ostringstream oss;
					oss << getLoopStmtId(innerLoopCopy->childList1(effectiveStmtIndex)) << std::endl;
					debugComment += oss.str();
					innerLoopCopy->childList1(effectiveStmtIndex)->setComments((char *)debugComment.c_str());
				}
			} else {
				/* does not contain */
				//remove stmt from this loop copy
				std::cout << "  remove  stmt " << stmtI << " " << decodeStmtVariant(innerLoopCopy->childList1(effectiveStmtIndex)->variant()) << std::endl;				

				innerLoopCopy->childList1(effectiveStmtIndex)->setComments("!If you see this, split went wrong\n");
				innerLoopCopy->childList1(effectiveStmtIndex)->deleteStmt(); //extractStmt()->
				deleted++;
			}
		}
	}
	
	for (int i = 0; i < bodyLength; i++) {
		std::cout << "numbers[" << i << "]=" << numbers[i] << std::endl;
	}

	set<set<string>> alignGroups = LoopTransformMerge::getSameAlignmentGroups(outerForLoopNode);
	vector<vector<vector<int>>> mergePossibilities = LoopTransformMerge::mergeGroups(alignGroups, outerLoops, innerLoops);

	vector<SgStatement *> movedStmts;
	vector<uint> moveTargetLoops;
	for (int i = 0; i < bodyLength; i++) {
		numbers[i] = i;
	}
	//if (false) //debug disable merging loops
	for (uint loopI = 0; loopI < mergePossibilities.size(); ++loopI) {
		for (uint stmtI = 0; stmtI < mergePossibilities.at(loopI).size(); ++stmtI) {
			for (uint targetLoop = 0; targetLoop < mergePossibilities.at(loopI).at(stmtI).size(); ++targetLoop) {
				//just use first option
				SgStatement * stmt = SageUtils::getNthLoopStatement(innerLoops.at(loopI), stmtI);
				int loopStmtId = getLoopStmtId(stmt);
				if (loopStmtId) {}
				movedStmts.push_back(stmt);
				moveTargetLoops.push_back(mergePossibilities.at(loopI).at(stmtI).at(targetLoop));
				break;
			}
		}
		for (uint moved = 0; moved < movedStmts.size(); ++moved) {		
			//todo: to merge correctly need to include tmp scalar savers into dep info
			//TODO: need to drag dependencies with moved statement or keep statement if dependencies cannot be moved
			SgForStmt * targetLoopHeader = innerLoops.at(moveTargetLoops.at(moved));
			SgStatement * targetControlEnd = SageUtils::getLastLoopStatement(targetLoopHeader);
			SgForStmt * originLoopHeader = innerLoops.at(loopI);
			SgStatement * originControlEnd = SageUtils::getLastLoopStatement(originLoopHeader);
			SgStatement * movedStatement = movedStmts.at(moved);
			vector<uint> fullFroms = getFlowDist0DependenciesRecursive(depInfo, getLoopStmtId(movedStatement));
			//todo filter out fullFroms which are not in originating loop
			set<uint> fromsSet;
			fromsSet.insert(fullFroms.begin(), fullFroms.end());
			vector<uint> loopStmts = getLoopStmtIds(originLoopHeader, originControlEnd);
			intersectInplace(fromsSet, loopStmts);
			for (set<uint>::iterator pCopyForMergeStmt = fromsSet.begin(); pCopyForMergeStmt != fromsSet.end(); ++pCopyForMergeStmt) {
				if (!loopContainsStmt(targetLoopHeader, *pCopyForMergeStmt)) {
					SgStatement * hostPlace = findMinGreater(targetLoopHeader, *pCopyForMergeStmt);
					SgStatement * copied = findByStmtId(isSgForStmt(movedStatement->controlParent()), *pCopyForMergeStmt);
					SgStatement * copy = copied->copyPtr();
					setLoopStmtId(copy, numbers + getLoopStmtId(copied));
					hostPlace->insertStmtBefore(*copy);
				}
			}
			if (false /*debug*/) {
				std::ostringstream oss; 
				oss << "! stmtLoopId2 " << getLoopStmtId(movedStatement)<< std::endl;
				movedStatement->addComment((char *)oss.str().c_str());
			}

			SgStatement * extracted = movedStatement->extractStmt();
			targetControlEnd->insertStmtBefore(*extracted);			
		}
		movedStmts.clear();
		moveTargetLoops.clear();
	}

	for (uint i = 0; i < outerLoops.size(); ++i) {
		if (SageUtils::checkEmptyLoop(innerLoops.at(i))) {
			outerLoops.at(i)->deleteStmt();
		}
	}
	for (int i = 0; i < bodyLength; i++) {
		std::cout << "numbers[" << i << "]=" << numbers[i] << std::endl;
	}
	outerForLoopNode->deleteStmt();	

	delete[] tmpArrayStoreAfter;
	delete[] numbers;
}
