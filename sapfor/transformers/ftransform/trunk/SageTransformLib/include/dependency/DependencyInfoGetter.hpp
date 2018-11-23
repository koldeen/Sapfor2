#ifndef DEPENDENCY_INFO_GETTER_HPP
#define DEPENDENCY_INFO_GETTER_HPP

#include <string>

#include "user.h"

#include "../SageTransformConstants.hpp"
#include "DependencyInfo.hpp"

using std::string;

namespace SageTransform {
	/**
	 * Reads dependencies from comments
	 */
	class DependencyInfoGetter {
	public:
		//get dependency graph info from comments
		//comments are parsed as "!PRG [flow|anti|output] N M othersIgnored"
		//where !PRG is just a special comment start
		//      [flow|anti|output] specifies dependency type
		//      N is arc start (on this statement we depend)   
		//      M is arc end (this statement depends on previous)
		//      other info (e.g. distance) is ignored now
		//ignores distances now
		DependencyInfo getDependencyInfo(char *dependencyComments, int scopeStmtCount);

		//return true if this loop node has Dependency info in comments
		static bool hasDependencyInfo(SgStatement * pForStmt);
	};
}

#endif //DEPENDENCY_INFO_GETTER_HPP
