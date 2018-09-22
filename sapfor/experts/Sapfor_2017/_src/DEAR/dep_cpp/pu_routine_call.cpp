#include "pu_routine_call.h"
#include "pu_routine.h"

namespace Analyzer
{
	namespace Loop
	{
		PURoutineCall :: PURoutineCall (PURoutine* routine)
		{
#if DEBUG & DBG_TREE_CREATE
			cout << "PURoutineCall (PURoutine*, MemoryUnitUsage**, bool)" << endl;							
#endif
			CHECK_NULL_POINTER (routine)

#if DEBUG & DBG_TREE_CREATE
			routine->Print ();
			cout << endl;
#endif

			//if (routine->GetParamsNumber () > 0) throw :: Exception :: IException ("wrong params number in routine call");

			this->routine = routine;			

			if (routine->GetParamsNumber () > 0)
			{	
				NEW_POINTER_ARRAY (this->params, routine->GetParamsNumber (), MemoryUnit)
				NEW_POINTER_ARRAY (this->pUsage, routine->GetParamsNumber (), MemoryUnitUsage)
			}

		}

		/*PURoutineCall :: PURoutineCall (PURoutine* routine, MemoryUnitUsage** params, bool notClone)
		{
#if DEBUG & DBG_TREE_CREATE
			cout << "PURoutineCall (PURoutine*, MemoryUnitUsage**, bool)" << endl;							
#endif
			CHECK_NULL_POINTER (routine)				

#if DEBUG & DBG_TREE_CREATE
			routine->Print ();
			cout << endl;
#endif
			if (routine->GetParamsNumber () == 0 && params)				
				throw :: Exception :: IException ("wrong params number in routine call");

			this->routine = routine;	

			if (notClone)
					this->params = params;
			else
			{
				NEW_POINTER_ARRAY (this->params, routine->GetParamsNumber (), MemoryUnitUsage)

				for (int i = 0; i < routine->GetParamsNumber (); i++)
					this->params [i] = params [i];					
			}					
		}*/

		void PURoutineCall :: AddParameter (MemoryUnit* param, MemoryUnitUsage* pUsage, int paramNumber)
		{			
			paramNumber--; //нумерация с нуля, а paramNumber - с единицы
			CHECK_INDEX_RANGE (paramNumber, 0, routine->GetParamsNumber ())
			CHECK_NULL_POINTER (param)

			this->params [paramNumber] = param;
			this->pUsage [paramNumber++] = pUsage;
		}

		MemoryUnit* PURoutineCall :: GetParameter (int pNumber)
		{
			CHECK_INDEX_RANGE (pNumber, 0, routine->GetParamsNumber ())
			
			return params [pNumber];
		}

		MemoryUnitUsage* PURoutineCall :: GetParameterUsage (int pNumber)
		{
			CHECK_INDEX_RANGE (pNumber, 0, routine->GetParamsNumber ())
			
			return pUsage [pNumber];
		}

		int PURoutineCall ::GetParamsNumber () {return routine->GetParamsNumber ();}

		bool PURoutineCall :: operator== (PURoutineCall& call)
		{
			if (*routine != *call.routine) return false;
			for (int i = 0; i < routine->GetParamsNumber (); i++)
			{
				if (!(*params [i] == *call.params [i])) return false;
				if (*pUsage [i] != *call.pUsage [i]) return false;
			}

			return true;
		}			
	}
}