#ifndef STATEMENT_REORDERER_HPP
#define STATEMENT_REORDERER_HPP

#include <vector>
#include "user.h"

using std::vector;

typedef unsigned int uint;

namespace SageTransform {
	class StatementReorderer {
	public:
		/* Reorders N statements according to given order vector.
		 * Method does not check anything and uses next N-2 statements after the given one.
		 */
		void reorderStatements(SgStatement * zeroNumStatement, const vector<uint>& newOrder);
	private:
		SgStatement * lexNext(SgStatement * base, uint num);
	};
}
#endif //STATEMENT_REORDERER_HPP
