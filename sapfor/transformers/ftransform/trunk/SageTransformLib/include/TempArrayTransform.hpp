#ifndef TEMP_ARRAY_TRANSFORM_HPP
#define TEMP_ARRAY_TRANSFORM_HPP

#include <vector>
#include "user.h"

using std::vector;

namespace SageTransform {
	namespace TempArrayTransform {
		//replace scalar usage by temp array usage
		//adds new assign statement to store scalar value before its usage
		//before: a(i, j) = C + D - E
		//after : _tmpXXXX(i, j) = E
		//        a(i, j) = C + D - _tmpXXXX(i, j)
		//returns new array symbol
		SgVariableSymb * replaceRhsScalarWithTempArray(SgStatement * pFuncHeader, SgAssignStmt * pAssignStmt, SgVariableSymb * pVarSymbToReplace, SgStatement * pStoreAfterStmt);

		//replace scalar usage by temp array usage in all input assigns
		//adds new assign statement to store scalar value after specified statement
		//returns new array symbol
		SgVariableSymb * replaceRhsScalarWithTempArray(SgStatement * pFuncHeader, const vector<SgAssignStmt *> & pAssignStmts, SgVariableSymb * pVarSymbToReplace, SgStatement * pStoreAfterStmt);
	}
}
#endif //TEMP_ARRAY_TRANSFORM_HPP
