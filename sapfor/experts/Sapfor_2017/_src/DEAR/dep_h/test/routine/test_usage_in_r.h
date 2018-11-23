#ifndef TEST_USAGE_IN_ROUTINE_H
#define TEST_USAGE_IN_ROUTINE_H

#include "test.h"
#include "mu_usage.h"

using namespace Analyzer :: Memory;

namespace Analyzer
{
	namespace Test
	{
		class UsageInRoutineTest : public ITest
		{
		public: 
			UsageInRoutineTest (int testId) : ITest (testId) {}
			
			virtual bool IsApplicable ()
			{
				if (pu->GetRoutineCallsNumber () > 0) return true;
				return false;
			}

			virtual TestResult Execute ()
			{
				if (!IsApplicable ()) return NOT_APPLICABLE;

				PURoutineCall* call = NULL;
				PURoutine* routine = NULL;
				MemoryUnit* formalParam = NULL;
				MemoryUnit* factParam = NULL;
				MemoryUnitUsage* factParamUsage = NULL;				
				
				for (int i = 0; i < pu->GetRoutineCallsNumber (); i++)
				{
					call = pu->GetRoutineCall (i);
					routine = call->GetRoutine ();

					for (int j = 0; j < routine->GetParamsNumber (); j++)
					{
						formalParam = routine->GetParameter (j); 					
						factParam = call->GetParameter (j);
						if (!factParam) continue; //если параметр не ссылка, то переходим к следющему

						factParamUsage = call->GetParameterUsage (j);

						if (!routine->IsUse (formalParam))
							factParamUsage->SetUsageType (NOT_USAGE);
						else
						{
							UsageType temp = routine->GetDepTestInfo (formalParam)->GetUsageType ();
							factParamUsage->SetUsageType (temp);						
						}
					}
						
				}
				return FAILURE;
			}
		};
	}
}

#endif