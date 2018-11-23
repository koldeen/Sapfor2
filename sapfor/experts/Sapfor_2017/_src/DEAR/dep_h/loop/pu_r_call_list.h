#ifndef PU_ROUTINE_CALL_LIST_H
#define PU_ROUTINE_CALL_LIST_H

#include "coll_list_element.h"
#include "pu_routine_call.h"
#include "macros.h"

namespace Analyzer
{
	namespace Loop
	{
		typedef ListElement<PURoutineCall*> PURCallList;

		class PURoutineCallList
		{
			PURCallList* first;
			PURCallList* last;
		public:


		}
	}
}

#endif