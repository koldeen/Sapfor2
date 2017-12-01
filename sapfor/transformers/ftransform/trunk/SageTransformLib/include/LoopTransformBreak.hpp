#ifndef LOOP_TRANSFORM_BREAK_HPP
#define LOOP_TRANSFORM_BREAK_HPP

#include <vector>

#include "user.h"

using std::vector;

typedef unsigned int uint;

namespace SageTransform {
	class LoopTransformBreak {
	public:
		//valid break comment has a fixed prefix and several lists of statement nums
		//lists are separated with hyphens, statements in list are separated with spaces
		//!PRG remote access 1 2 - 3 4
		//if all statements are represented - comment is valid
		static bool hasValidBreakComment(SgForStmt * outerForLoopNode);

		//from the comment
		static vector<vector<uint>> getBreakSchema(SgForStmt * outerForLoopNode);

		//get schema where each statement is in a separate loop
		static vector<vector<uint>> getFullBreakSchema(SgForStmt * outerForLoopNode);
		
		//break loop body into several parts - loop header is replicated (loop can be multidimensional)
		static void breakLoop(SgForStmt * outerForLoopNode, SgForStmt * innerForLoopNode, const vector<vector<uint>> &breakSchema);
	};
}

#endif //LOOP_TRANSFORM_SPLIT_HPP
