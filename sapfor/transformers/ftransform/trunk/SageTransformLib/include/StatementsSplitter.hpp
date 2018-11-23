#ifndef STATEMENTS_SPLITTER_HPP
#define STATEMENTS_SPLITTER_HPP

#include <vector>

#include "dependency/DependencyInfo.hpp"

using std::vector;

namespace SageTransform {

	class StatementsSplitter {
	public:
		//returns true if given body is splitable for parallelization
		bool canSplit(const DependencyInfo & info);

		//returns statement split schema for parallelization
		//use ONLY if canSplit(info) returned true
		vector<vector<uint>> getValidSplit(const DependencyInfo & info);
	private:
		vector<uint> getSplitGroupFor(uint stmtNum, const DependencyInfo & info);

		bool isFullPrivate(const vector<uint>& group, const set<int>& privates);

		vector<vector<uint>> mergeBackIllegalSplits(vector<vector<uint>> splitSchema, const DependencyInfo & info);

		vector<vector<uint>> mergeGroups(const vector<vector<uint>> & groups, uint group1, uint group2);

		uint countMaxRequiredStatementNum(uint stmtNum, const DependencyInfo & info);

		vector<uint> getDependencies(uint stmtNum, const DependencyInfo & info, int depType);

		set<Dependency> filterDepsType(const set<Dependency> & deps, int depTypeMask);

		set<Dependency> filterDepsDistance(const set<Dependency> & deps, uint distanceMinInc, uint distanceMaxInc);

		set<uint> getFroms(const set<Dependency> & deps);
	};
}
#endif //STATEMENTS_SPLITTER_HPP
