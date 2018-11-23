#ifndef TEST_R_ARRAY_PARAMETER_H
#define TEST_R_ARRAY_PARAMETER_H

#include "test.h"

namespace Analyzer
{
	namespace Test
	{
		class ArrayParamRTest : public ITest
		{
			bool  IsUpper (int varId, TightlyNestedLoops* tNLoops)
			{
				if (!tNLoops) return false;
				if (tNLoops->GetIndexVariable (varId)) return true;					

				return IsUpper (varId, dynamic_cast <TightlyNestedLoops*> (tNLoops->GetExternalPU ()));
			}	
		public: 
			ArrayParamRTest (int testId) : ITest (testId) {}
			
			virtual bool IsApplicable ()
			{
				PURoutineCall* call = NULL;
				PURoutine* routine = NULL;
				PURoutine* testedR;
				ProgramUnit* temp = pu;

				testedR = dynamic_cast <PURoutine*> (temp);
				while (temp && !testedR)
				{
					temp = temp->GetExternalPU ();
					testedR = dynamic_cast <PURoutine*> (temp);
				}

				for (int i = 0; i < pu->GetRoutineCallsNumber (); i++)
				{
					call = pu->GetRoutineCall (i);
					routine = call->GetRoutine ();

					for (int j = 0; j < routine->GetParamsNumber (); j++)
					{	
						if (!call->GetParameter (j))
							continue;

						for (int id = 0; id < call->GetParameter (j)->GetVarsNumber (); id++)
							if (IsUpper (call->GetParameter (j)->GetVarsId (id), dynamic_cast <TightlyNestedLoops*> (pu)))
								return false;
												
						
						for (int pI = 0; pI < testedR->GetParamsNumber (); pI++)
							if (call->GetParameter (j) == testedR->GetParameter (pI))
								return false;
					}
				}

				if (pu->GetRoutineCallsNumber () > 0) return true;

				return false;
			}

			virtual TestResult Execute ()
			{					
				if (!IsApplicable ()) return NOT_APPLICABLE;

			//	DBG_START

				PURoutineCall* call = NULL;
				PURoutine* routine = NULL;
				
				MemoryUnit* formalParam = NULL;
				MemoryUnit* factParam = NULL;
				MemoryUnitUsage* factParamUsage = NULL;
				
				ArrayUnit* formArr = NULL;
				ArrayUnit* factArr = NULL;	
				ArrayUsage* factUsage = NULL;
				
				DepTestInfo* dTInfo = NULL;
				IDependence* formalDep = NULL;
				IDependence* factDep = NULL;
				IDependence* temp;

				for (int i = 0; i < pu->GetRoutineCallsNumber (); i++)
				{
					call = pu->GetRoutineCall (i);
					routine = call->GetRoutine ();

					for (int j = 0; j < routine->GetParamsNumber (); j++)
					{
						formalParam = routine->GetParameter (j); 
						factParam = call->GetParameter (j);
						factParamUsage = call->GetParameterUsage (j);						

						if (!factParam ||
							formalParam->IsScalar () ||
							!routine->IsUse (formalParam)  ||
							pu->GetDepTestInfo (factParam)->GetIsTested ())							
							continue;
						
						formArr = dynamic_cast <ArrayUnit*> (formalParam);
						factArr = dynamic_cast <ArrayUnit*> (factParam);
						factUsage = dynamic_cast <ArrayUsage*> (factParamUsage);

						if (!formArr || !factArr || !factUsage) 
							continue;

						for (int dim = 0; dim < formArr->GetDimsNumber () && dim < factArr->GetDimsNumber (); dim++)
						{
							int index = factArr->GetDimsNumber () - dim - 1;
							if (factUsage->GetIndexNumber () <= index ||
								!dynamic_cast <IntegerValue*> (factUsage->GetIndexExpr (index)))
								continue; //если передаются на разных итерациях разные участки массива, то тест не применим
						}
							
						dTInfo = pu->GetDepTestInfo (factParam);							
						formalDep = routine->GetDependence (formalParam, 0);

						bool isExact = true;
						DepType dType;
						for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
						{
							temp = pu->GetDependence (factParam, loop);								
							factDep = ((Dependence*)temp)->UnionIntersect (formalDep, DEP_EXIST);
							dTInfo->SetDependence (loop, (Dependence*)factDep, NOT_CLONE); //temp будет удален при вызове

							dType = factDep->GetType ();
							if (dType == DEP_UNKNOWN ||
								dType == DEP_COND_EXIST_UNKNOWN ||
								dType == DEP_COND_NOT_EXIST_UNKNOWN)
								isExact = false;
						}		
						if (isExact)
							dTInfo->SetIsTested ();
					}

					return FAILURE;
						
				}
			}
		};
	}
}

#endif