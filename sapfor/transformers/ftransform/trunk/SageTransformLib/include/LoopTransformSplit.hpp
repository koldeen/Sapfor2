#ifndef LOOP_TRANSFORM_SPLIT_HPP
#define LOOP_TRANSFORM_SPLIT_HPP

#include <vector>
#include "user.h"

#include "dependency/DependencyInfo.hpp"

using std::vector;

typedef unsigned int uint;

namespace SageTransform {
	class LoopTransformSplit {
	public:
		static void split(SgForStmt * outerForLoopNode, SgForStmt * innerForLoopNode, const vector<vector<uint>> & splitSchema, const DependencyInfo & depInfo);
	private:
		static const int ATTR_LOOP_STMT_ID = 27032015;
		static int getLoopStmtId(SgStatement * stmt);
		static void setLoopStmtId(SgStatement *stmt, int *value);
		static bool loopContainsStmt(SgForStmt * forLoop, int loopStmtAttrId);
		static SgStatement * hasLoopStmt(SgForStmt * innerLoop, int loopStmtId);
		static SgStatement * findByStmtId(SgForStmt * forLoop, int loopStmtAttrId);
		static vector<uint> getLoopStmtIds(SgForStmt * targetLoopHeader, SgStatement * targetControlEnd);

		static set<uint> getFlowDist0Dependants(const DependencyInfo & depInfo, uint stmtI, const vector<uint> &filterVector);
		static vector<uint> getFlowDist0DependenciesRecursive(const DependencyInfo & depInfo, uint stmtI);
		static SgStatement * findMinGreater(SgForStmt * forLoop, int loopStmtAttrId);

		//TODO move all these to utility classes
		static void intersectInplace(set<uint> &theSet, const vector<uint> & aVector);
		static bool containsAll(const set<uint> source, const set<uint> & checked);
		static bool containsAll(const vector<uint> source, const set<uint> & checked);
		static set<uint> getFromsSet(const set<Dependency> & deps);
	};
}

#endif //LOOP_TRANSFORM_SPLIT_HPP
