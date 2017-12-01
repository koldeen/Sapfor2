#ifndef STATEMENT_RESHUFFLER_HPP
#define STATEMENT_RESHUFFLER_HPP

#include <vector>
#include "Dependencies.hpp"

using std::vector;

namespace SageTransform {

	class StatementReshuffler {
	public:
		/**
		 * Tries to build new statement order which has less reverse dependency arcs.
		 *
		 * @param info current DependencyGraph
		 * @return same or re-shuffled statements
		 */
		vector<uint> reshuffle(DependencyInfo& info);

	private:
		bool hasLeftwardDependency(const DependencyInfo& info);
		Dependency getLeftwardDependency(const DependencyInfo& info);
		uint countRightLimit(uint stmtNum, const DependencyInfo& info);
		uint countRightRequirement(uint stmtNum, const DependencyInfo& info);
		vector<uint> getOrderVector(uint thisOldPosIs, uint beforeThisOldPos, uint size);
		vector<uint> product(vector<uint> reorderSecond, vector<uint> reorderFirst);
	};
}
#endif //STATEMENT_RESHUFFLER_HPP
