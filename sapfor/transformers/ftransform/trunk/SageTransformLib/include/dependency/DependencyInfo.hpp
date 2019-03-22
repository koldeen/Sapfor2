#ifndef DEPENDENCY_INFO_HPP
#define DEPENDENCY_INFO_HPP

#include <vector>
#include <set>
#include <string>
#include "user.h"

#include "Dependency.hpp"

using std::vector;
using std::set;
using std::string;
typedef unsigned int uint;

namespace SageTransform {
	/**
	 * Class representing a Statement Dependencies Graph.
	 */
	//WARN: currently distance in iteration between dependent statements is ignored
	class DependencyInfo {		
	public:
		/**
		 * returns number of statements in graph
		 */
		uint getStatementCount() const;
		/**
		 * sets number of statements in graph
		 */
		void setStatementCount(uint inStmtCount);

		/* if dependency (to:stmtDepends <--- from:onThisStmt) exists
		 *   returns const pointer to Dependency object with merged types
		 * else returns NULL
		 */
		const Dependency * getDependency(int typeMask, uint stmtDepends, uint onThisStmt) const;

		/* add Dependency
		 */
		void addDependency(const Dependency& dependency);

		/* add multiple Dependencies
		 */		
		void addDependencies(const set<Dependency>& dependencies);

		/* remove dependency
		 */
		void removeDependency(const Dependency& dependency);

		/* returns set of Dependency objects where "to" field == stmtNum
		 */
		set<Dependency> getStatementDependencies(int typeMask, uint stmtNum) const;

		/* returns set of Dependency objects where "from" field == stmtNum
		 */
		set<Dependency> getStatementDependants(int typeMask, uint stmtNum) const;

		/* verifies that stored dependencies correspond with statement count
		 * if verification is successful puts all dependencies 
		 *   from A to B into one Dependency object with merged type param
		 * you MUST call this method to ensure correct work with current depedencies
		 */
		bool verifyAndCollapseDependencies();

		/* reorders statements.
		 * all dependency info will be updated to new order
		 */
		void reorderStatements(const vector<uint>& newOrder);

		/* set private identifiers
		 */
		inline void setPrivateVarIdentifers(set<string> &identifiers) { privateVarIdents.insert(identifiers.begin(), identifiers.end());}

		/* get private identifiers
		 */
		inline set<int> getPrivateStatements() const { return privateEffectStatement;}


		/* update this dependency info using private variables
		 * some dependency links may be removed
		 * info about private variables can help split loop body
		 */
		void usePrivateVars(SgStatement * pZerothStmt);

	private:
		//inner structure
		//  set of all Dependency objects of all types
		uint statementCount;
		set<Dependency> dependencies;
		set<string> privateVarIdents;
		set<int> privateEffectStatement;

		void loadToMatrix(const set<Dependency>& deps, int ** types, uint distance);
		void loadFromMatrix(set<Dependency> & deps, int ** pTypes, uint distance);
		int ** getZeroMatrix(uint size);
		void deleteMatrix(int ** pMatrix, uint size);
	};
}

#endif //DEPENDENCY_INFO_HPP
