#include "WriteDearray.hpp"

#include <iostream>

#include "SageTransformUtils.hpp"
#include "StringUtils.hpp"
#include "SageTransformConstants.hpp"

using namespace SageTransform;

string WriteDearray::DISTRIBUTED_IO_MARKER(" distributed_IO");
const char * FULL_COMMENT_PREFIX = (Constants::TRANSFORM_CMD_PREFIX + WriteDearray::DISTRIBUTED_IO_MARKER).c_str();

bool WriteDearray::hasIOArrayComment(SgStatement * ioStmt) {
	char * comments = ioStmt->comments();
	if (comments != NULL) {
		return !strncmp(comments, FULL_COMMENT_PREFIX, strlen(FULL_COMMENT_PREFIX));
	}
	return false;
}

vector<SgSymbol *> WriteDearray::removeArrayAccess(SgStatement * inStmt) {
	SgInputOutputStmt * ioStmt;
	vector<SgSymbol *> symbols;
	if ((ioStmt = isSgInputOutputStmt(inStmt))) {
		switch (ioStmt->variant()) {
		case WRITE_STAT:
			symbols = removeArrayAccessInWrite(ioStmt);
			break;
		default:
			std::cout << "IO operator variant " << ioStmt->variant() << " not supported yet" << std::endl;
		}
	} else {
		std::cout << "Illegal input parameter - not an IO operator" << std::endl;
	}
	return symbols;
}

vector<SgSymbol *> WriteDearray::removeArrayAccessInWrite(SgInputOutputStmt * writeStmt) {
	vector<SgSymbol *> result;

	//if uncommented causes weird bug
	//writeStmt->setComments("!PRG io removed");
	//SgExpression * specList = writeStmt->specList();	
	SgExpression * itemList = writeStmt->itemList();
	SgExprListExp * newItemList = new SgExprListExp();
	SgExprListExp * exprList = isSgExprListExp(itemList);
	int itemCount = exprList->length();
	for (int i = 0; i < itemCount; ++i) {
		SgExpression * exprI = exprList->elem(i);
		SgArrayRefExp * arrayRefExp;
		if ((arrayRefExp = isSgArrayRefExp(exprI))) {
			char * arrayName = arrayRefExp->symbol()->identifier();
			char * tmpVarName = SageTransformUtils::getNewVariableName(arrayName);
			SgType * arrayBaseType = isSgArrayType(arrayRefExp->symbol()->type())->baseType();			
			SgVariableSymb * tmpVar = SageTransformUtils::addScalarVariable(writeStmt->getScopeForDeclare(), tmpVarName, arrayBaseType);
			result.push_back(tmpVar);
			SgVarRefExp * tmpVarRef = new SgVarRefExp(tmpVar);
			SgAssignStmt * assign = new SgAssignStmt(*tmpVarRef, *arrayRefExp);
			writeStmt->insertStmtBefore(*assign);
			newItemList->append(*tmpVarRef);
		} else {
			newItemList->append(*(exprList->elem(i)));
		}
	}
	writeStmt->setItemList(*newItemList);	
	//TODO: if equal values are in write do not repeat copying them.
	return result;
}
