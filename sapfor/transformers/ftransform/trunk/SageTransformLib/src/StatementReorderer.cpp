#include "StatementReorderer.hpp"

using namespace SageTransform;

void StatementReorderer::reorderStatements(SgStatement * zeroNumStatement, const vector<uint>& newOrder) {
	SgStatement * base = zeroNumStatement->lexPrev();
	SgStatement * stmt, * stmtCopy;
	for (uint i = 0; i < newOrder.size(); ++i) {
		uint oldIndex = newOrder.at(i);
		stmt = lexNext(zeroNumStatement, oldIndex);
		stmtCopy = stmt->copyPtr();
		base->insertStmtAfter(*stmtCopy, *(stmt->controlParent()));
		base = stmtCopy;
	}
	uint descCounter = newOrder.size() - 1;
	for (uint i = 0; i < newOrder.size(); ++i, --descCounter) {

		lexNext(zeroNumStatement, descCounter)->deleteStmt();
	}
}

SgStatement * StatementReorderer::lexNext(SgStatement * base, uint num) {
	SgStatement * result = base;
	for (uint i = 0; i < num; ++i) {
		result = result->lexNext();
	}
	return result;
}
