#ifndef TEST_SCALAR_H
#define TEST_SCALAR_H

#include "debug.h"
#include "test.h"
#include "test_dep_info.h"

using namespace Analyzer :: Test :: Dependences;

namespace Analyzer
{
	namespace Test
	{
		class ScalarTest : public ITest
		{		
			//firstUsage != NULL 
			//view: [firstUsage, lastUsage)
			UsageType MaxUsage (MemoryUnitUsage* firstUsage, MemoryUnitUsage* lastUsage)
			{
#if DEBUG & DBG_TEST_SCALAR		
				cout << "UsageType ScalarTest :: MaxUsage (MemoryUnitUsage*, MemoryUnitUsage*)" << endl;
#endif
				MemoryUnitUsage* usage = firstUsage;
				UsageType type = FIRST_TYPE;
				UsageType tempType;					

				while (usage != lastUsage)
				{					
#if DEBUG & DBG_TEST_SCALAR		
					cout << "CHECK_NULL_POINTER (usage)" << endl;
					CHECK_NULL_POINTER (usage)				
#endif
					tempType = usage->GetUsageType ();					
					if (tempType == LAST_TYPE) //WRITE
					{
						return LAST_TYPE;
					}
					else if (tempType > type) 
					{
						type = tempType;
						continue;
					}					
					usage = usage->GetNextUsage ();
				}
				return type;
			}

		public:
			ScalarTest (int testId) : ITest (testId) {}
			bool IsApplicable ()
			{
				ITest :: IsApplicable ();

				if (mu->IsScalar ()) return true;
				return false;
			}

			TestResult Execute ()
			{				
#if DEBUG & DBG_TEST_SCALAR
				cout << "ScalarTest :: Execute ()" << endl;
#endif 
				if (!IsApplicable ()) return NOT_APPLICABLE;

				MemoryUnitUsage* firstInLoop = pu->GetFirstUsage (mu);
				MemoryUnitUsage* lastInLoop = pu->GetLastUsage (mu);			
				DepTestInfo* dTInfo = pu->GetDepTestInfo (mu);
				Dependence* depTemp = new Dependence ();

#if TEST_USE_PRE_INFO												

				//проводим тестриование, если еще не проводили
				if (!dTInfo->GetIsTested ()) 
				{

#if DEBUG & DBG_TEST_SCALAR
					cout << "not tested yet" << endl;
#endif

					UsageType type1 = FIRST_TYPE;
					UsageType type2 = FIRST_TYPE;
					MemoryUnitUsage* sTRegion = dTInfo->GetStartTestedRegion ();
					MemoryUnitUsage* eTRegion = dTInfo->GetEndTestedRegion ();
					
					//Если уже протестированная область не задана, то sTRegion == NULL.
					//В этом случае будет протестирована вся область [firstInLoop, lastInLoop].
					if (sTRegion)
						type1 = MaxUsage (firstInLoop, sTRegion);										
					else 
						type1 = MaxUsage (firstInLoop, lastInLoop->GetNextUsage ());					

					//Если уже протестированная область не задана, то eTRegion == NULL
					if (eTRegion && type1 != LAST_TYPE)
					{						
						type2 = MaxUsage (eTRegion->GetNextUsage (), lastInLoop->GetNextUsage ());				
						if (type2 > type1) type1 = type2;
					}
					
					switch (type1)
					{
					case NOT_USAGE:
					case READ:		//нет зависимости
						depTemp->SetExistenceCond (DEP_NOT_EXIST, DEP_ALWAYS, DEP_EXACTLY);							
						break;
					case UNKNOWN:	//возможная зависимость (в силу корректности информации о зависимости уже задана)
						break;
					case WRITE:		//точная зависимость
						depTemp->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_EXACTLY);							
						break;
					default:
						throw Memory :: Exception :: MemoryUnitException ();
					}
					dTInfo->SetIsTested ();

					dTInfo->SetUsageType (type1);
					//для разных циклов, дублируются указатели, но область памяти одна и та же
					for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
						dTInfo->SetDependence (loop, depTemp, NOT_CLONE);
				}

#if DEBUG & DBG_TEST_SCALAR
				cout << "mu is tested" << endl;
#endif
				
				//текущее гнездо протестировано, помещаем информацию во внешнее гнездо
				
				IDependence* dep = pu->GetDependence (mu, 0); //по скалярам, одинаковая зависимость во всех циклах гнезда
				ProgramUnit* externalPU = pu->GetExternalPU ();				

				if (externalPU)	//текущее гнездо - не корень
				{
					DepTestInfo* eDTInfo = externalPU->GetDepTestInfo (mu);
					if	(!eDTInfo->GetIsTested ())	//внешнее гнездо еще не протестировано (например за счет соседних c данным гнезд)
					{
						if (dep->IsAlwaysExists ())
						{
							//устанавливаем наличие точной зависимости
							eDTInfo->SetIsTested ();
							eDTInfo->SetUsageType (WRITE);
							Dependence* depTemp = new Dependence ();
							depTemp->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_EXACTLY);															
							for (int loop = 0; loop < externalPU->GetLoopsNumber (); loop++)							
								eDTInfo->SetDependence (loop, depTemp, CLONE);												
							DELETE_POINTER (depTemp)
						}
						else
						{						
							//обновляем протестированную область
							if (!eDTInfo->GetStartTestedRegion ())
								eDTInfo->SetStartTestedRegion (firstInLoop);
							eDTInfo->SetEndTestedRegion (lastInLoop);
						}						
					}			
				}
#if DEBUG & DBG_TEST_SCALAR
				cout << "end test" << endl;
#endif 

#else
					UsageType type = MaxUsage (firstInLoop, lastInLoop->GetNextUsage ());
					switch (type)
					{
					case NOT_USAGE:
					case READ:		//нет зависимости
						depTemp->SetExistenceCond (DEP_NOT_EXIST, DEP_ALWAYS, DEP_EXACTLY);	
						break;
					case UNKNOWN:	//возможная зависимость (в силу корректности информации о зависимости уже задана)
						break;
					case WRITE:		//точная зависимость
						depTemp->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_EXACTLY);	
						break;
					default:
						throw new Memory :: Exception :: MemoryUnitException ();
					}
					dTInfo->SetIsTested ();						

					dTInfo->SetUsageType (type);

					for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
						dTInfo->SetDependence (loop, depTemp, CLONE);
#endif
				return SUCCESS; 
				
			}
		};
	}
}

#endif