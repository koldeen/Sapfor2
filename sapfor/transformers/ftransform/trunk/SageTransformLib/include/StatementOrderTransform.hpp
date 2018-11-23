#ifndef STATEMENT_ORDER_TRANSFORM_HPP
#define STATEMENT_ORDER_TRANSFORM_HPP

#include "user.h"

namespace SageTransform {
	class StatementOrderTransform {
	public:
		void transformLoop(SgForStmt * outerForStmt, SgForStmt * innerForStmt);
	};
}

#endif //STATEMENT_ORDER_TRANSFORM_HPP
