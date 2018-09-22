#ifndef PU_ROUTINE_CALL_H
#define PU_ROUTINE_CALL_H

#include "mu_usage.h"
#include "exception.h"

using namespace Analyzer :: Memory;

namespace Analyzer
{
	namespace Loop
	{
		class PURoutine;

		class PURoutineCall
		{
			PURoutine* routine;
			MemoryUnit** params;
			MemoryUnitUsage** pUsage;
			int lastParam;

		public:
			PURoutineCall (PURoutine* routine);			
			
			//PURoutineCall (PURoutine* routine, MemoryUnitUsage** params, bool notClone = false);

			~PURoutineCall ()
			{
				routine = NULL;
				DELETE_ARRAY (params)
			}
			
			PURoutineCall* Clone ()
			{
				PURoutineCall* temp = new PURoutineCall (routine);
				for (int i = 0; i < lastParam; i++)
				{
					temp->params [i] = params [i];
					temp->pUsage [i] = pUsage [i];
				}

				return temp;
			}

			void AddParameter (MemoryUnit* param, MemoryUnitUsage* pUsage, int paramNumber);			

			MemoryUnit* GetParameter (int pNumber);

			MemoryUnitUsage* GetParameterUsage (int pNumber);
			
			PURoutine* GetRoutine ()
			{
				return routine;
			}

			int GetParamsNumber ();
			
			bool operator== (PURoutineCall& call);
			
			bool operator!= (PURoutineCall& call)
			{
				return !(*this == call);
			}

		};
	}
}

#endif