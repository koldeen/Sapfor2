#include "TempArrayTransform.hpp"

#include "SageTransformUtils.hpp"

using namespace SageTransform;

SgVariableSymb * TempArrayTransform::replaceRhsScalarWithTempArray(
		SgStatement * pFuncHeader, SgAssignStmt * pAssignStmt, SgVariableSymb * pVarSymbToReplace, SgStatement * pStoreAfterStmt
) {
	vector<SgAssignStmt *> assignments;
	assignments.push_back(pAssignStmt);
	return replaceRhsScalarWithTempArray(pFuncHeader, assignments, pVarSymbToReplace, pStoreAfterStmt);
}

SgVariableSymb * TempArrayTransform::replaceRhsScalarWithTempArray(
		SgStatement * pFuncHeader, const vector<SgAssignStmt *> & pAssignStmt, SgVariableSymb * pVarSymbToReplace, SgStatement * pStoreAfterStmt
) {
	SgArrayRefExp * lhsArrayRef = isSgArrayRefExp(pAssignStmt.at(0)->lhs());	
	char * tmpVarName = SageTransformUtils::getNewVariableName(pVarSymbToReplace->identifier());
	SgVariableSymb * lhsArraySymb = isSgVariableSymb(lhsArrayRef->symbol());
	SgArrayType * arrayType = isSgArrayType(lhsArraySymb->type());
	SgArrayType * tmpVarArrayType = isSgArrayType(arrayType->copyPtr());
	//tmp array gets base type from replaced scalar, and ranges from accessed arrays' type
	tmpVarArrayType->setBaseType(*pVarSymbToReplace->type());
	SgVariableSymb * tmpArrayVarSymb = SageTransformUtils::addArrayVariable(pFuncHeader, tmpVarName, tmpVarArrayType);

	SgExpression * tmpArrayRef = lhsArrayRef->copyPtr();
	tmpArrayRef->setSymbol(*tmpArrayVarSymb);
	SgExpression * storedValue = new SgVarRefExp(pVarSymbToReplace);
	SgAssignStmt * scalarStoreAssign = new SgAssignStmt(*tmpArrayRef, *storedValue);
	pStoreAfterStmt->insertStmtAfter(*scalarStoreAssign);
	//SgExpression * tmpArrayRef2 = lhsArrayRef->copyPtr();
	//tmpArrayRef2->setSymbol(*tmpArrayVarSymb);	
	//maybe should make a separate copy of array ref
	for (unsigned int i = 0; i < pAssignStmt.size(); ++i) {
		pAssignStmt.at(i)->replaceSymbByExp(*pVarSymbToReplace, *tmpArrayRef);
	}
	return tmpArrayVarSymb;
}
