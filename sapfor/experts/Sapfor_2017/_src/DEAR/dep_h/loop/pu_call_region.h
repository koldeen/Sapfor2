#ifndef PU_CALL_REGION_H
#define PU_CALL_REGION_H

#include "pu_r_call_collection.h"
#include "pu_routine_call.h"
#include "macros.h"

#define NO_ROUTINE_CALL -1

namespace Analyzer
{
	namespace Loop
	{
		class PUCallRegion
		{
			PURoutineCallCollection* routineCalls;
			bool isCreator; //создатель коллекции

			int firstRoutineCall;
			int lastRoutineCall;	

		public:
			PUCallRegion () 
			{
				this->routineCalls = new PURoutineCallCollection ();
				this->isCreator = true;
				this->firstRoutineCall = NO_ROUTINE_CALL;
				this->lastRoutineCall = NO_ROUTINE_CALL;
			}
			PUCallRegion (PUCallRegion* parentRegion) 
			{
				CHECK_NULL_POINTER (parentRegion)

				this->routineCalls = parentRegion->routineCalls;
				this->isCreator = false;
				this->firstRoutineCall = NO_ROUTINE_CALL;
				this->lastRoutineCall = NO_ROUTINE_CALL;
			}

			~PUCallRegion () 
			{
				if (this->isCreator) 
					DELETE_POINTER (this->routineCalls)
				else
					this->routineCalls = NULL;			
			}

			PUCallRegion* Clone ()
			{
				PUCallRegion* temp = new PUCallRegion ();

				if (isCreator)
					temp->routineCalls = (PURoutineCallCollection*)routineCalls->Clone ();
				else 
					temp->routineCalls = routineCalls;
				temp->isCreator = isCreator;
				temp->firstRoutineCall = firstRoutineCall;
				temp->lastRoutineCall = lastRoutineCall;

				return temp;
			}

			PURoutineCall* GetFirstRoutineCall ()
			{
				if (firstRoutineCall == NO_ROUTINE_CALL) return NULL;				
				return (*routineCalls) [firstRoutineCall];
			}			

			PURoutineCall* GetLastRoutineCall ()
			{
				if (lastRoutineCall == NO_ROUTINE_CALL) return NULL;	
				return (*routineCalls) [lastRoutineCall];
			}

			PURoutineCall* GetRoutineCall (int index)
			{
				CHECK_INDEX_RANGE (index, 0, lastRoutineCall - firstRoutineCall + 1)

				return (*routineCalls) [firstRoutineCall + index ];
			}

			int GetCallsNumber ()
			{
				if (firstRoutineCall == NO_ROUTINE_CALL ||
					lastRoutineCall == NO_ROUTINE_CALL)
					return 0;
				return lastRoutineCall - firstRoutineCall + 1;
			}

			void AddNextRoutineCall (PURoutineCall* nextRCall)
			{
				CHECK_NULL_POINTER (nextRCall)

				routineCalls->Add (nextRCall);			
			}

			void StartRegion ()
			{
				firstRoutineCall = routineCalls->GetSize () - 1;
			}

			void EndRegion ()
			{
				lastRoutineCall = routineCalls->GetSize () - 1;
			}
		};
	}
}

#endif