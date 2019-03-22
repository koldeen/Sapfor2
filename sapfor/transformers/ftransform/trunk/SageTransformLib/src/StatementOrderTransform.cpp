#include "StatementOrderTransform.hpp"

#include <iostream>

#include "Dependencies.hpp"
#include "LoopTransformSplit.hpp"
#include "StatementReorderer.hpp"
#include "StatementReshuffler.hpp"
#include "StatementsSplitter.hpp"

using std::cout;
using std::endl;

using namespace SageTransform;

void StatementOrderTransform::transformLoop(SgForStmt * outerForStmt, SgForStmt * innerForStmt) {
	DependencyInfoGetter depInfoGetter;
	DependencyInfo pDepInfo;
	StatementsSplitter splitter;
	StatementReshuffler reshuffler;
	StatementReorderer reorderer;
	
	cout << "try to split the loop" << endl;
	int statementsInScope = innerForStmt->numberOfChildrenList1() - 1/*for control_end stmt*/;
	pDepInfo = depInfoGetter.getDependencyInfo(outerForStmt->comments(), statementsInScope);
	pDepInfo.usePrivateVars(innerForStmt->lexNext());
	if (!pDepInfo.verifyAndCollapseDependencies()) throw "StatementOrderTransform::transformLoop() Failed to load dependencies!";
	cout << "Can";
	if (!splitter.canSplit(pDepInfo)) cout << "not";
	cout << " split in current state. Reshuffling anyway" << endl;

	vector<uint> reorder = reshuffler.reshuffle(pDepInfo);
	for (uint i = 0; i < reorder.size(); ++i) {
		if (i != reorder.at(i)) {
			cout << "Reshuffled something successfully" << endl;
			reorderer.reorderStatements(innerForStmt->lexNext(), reorder);
			break;
		}
	}

	if (splitter.canSplit(pDepInfo)) {
		vector<vector<uint>> splitSchema = splitter.getValidSplit(pDepInfo);
		cout << "split schema:" << endl;
		for (unsigned int group = 0; group < splitSchema.size(); group++) {
			if (group == 0) {
				cout << "[[";
			} else {
				cout << " [";
			}
			unsigned int item;
			for (item = 0; item < splitSchema.at(group).size() - 1; item++) {
				cout << splitSchema.at(group).at(item) << ", ";
			}
			if (item == splitSchema.at(group).size() - 1) {
				cout << splitSchema.at(group).at(item);
			}
			cout << "]";
			if (group < splitSchema.size() - 1) {
				cout << "," << endl;
			}
		}
		cout << "]" << endl;
		LoopTransformSplit::split(outerForStmt, innerForStmt, splitSchema, pDepInfo);
	} else {
		cout << "Can't split loop" << endl;
	}	
}
