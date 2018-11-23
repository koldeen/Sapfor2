#ifndef TEST_INDEX_H
#define TEST_INDEX_H

#include "debug.h"

#include "test.h"
#include "test_usages.h"

#include "macros.h"

namespace Analyzer
{
	namespace Test
	{
		class IndexTest: public ITest
		{
			TestsChain* first;
			TestsChain* last;	
			IEPairArrayTest* curTest;		

			Dependence** usagesDep;			
			
			TestResult ExecuteChain (ArrayUsage* aUsage1, ArrayUsage* aUsage2, int dim)
			{
#if DEBUG & DBG_TEST_ARRAY
				cout << "TestResult IndexTest ::  ExecuteChain (ArrayUsage*, ArrayUsage*)" << endl;
#endif 
				TestsChain* tChain = first;							

				while (tChain)
				{
					curTest = dynamic_cast <IEPairArrayTest*> (tChain->GetValue ());
					if (!curTest) throw Analyzer :: Test :: Exception :: TestException ();		
					
					curTest->SetPUnit (pu);
					curTest->SetMUnit (mu);						
					curTest->SetPrevAUsage (aUsage1);						
					curTest->SetPostAUsage (aUsage2);					
					curTest->SetDimension (dim);					

					switch (curTest->Execute ())
					{
					case SUCCESS :
						return SUCCESS;
						break;
					case NOT_APPLICABLE :
					case FAILURE :
						tChain = tChain->GetNext ();					
						break;
					default :
						throw Analyzer :: Test :: Exception :: TestException ();				
					}					
				}
				return FAILURE;
			}

			void TestUsages (ArrayUsage* aUsage1, ArrayUsage* aUsage2)
			{
				/*int ch;
				cin >> ch;
				cout << ((IntegerValue*)((LinearExpression*)aUsage1->GetIndexExpr(0))->GetCoeffitient (0))->GetValue() <<" * i  + " << 
					((IntegerValue*)((LinearExpression*)aUsage1->GetIndexExpr(0))->GetFreeTerm ())->GetValue () << endl;
				cout << ((IntegerValue*)((LinearExpression*)aUsage2->GetIndexExpr(0))->GetCoeffitient (0))->GetValue() <<" * i  + " << 
					((IntegerValue*)((LinearExpression*)aUsage2->GetIndexExpr(0))->GetFreeTerm ())->GetValue () << endl; */
#if DEBUG & DBG_TEST_ARRAY
				cout << "Dependence* IndexTest ::  TestUsages (ArrayUsage*, ArrayUsage*)" << endl;
#endif 
				TestResult res;
				Dependence* temp = NULL;				
				
				for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
					usagesDep [loop]->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_EXACTLY); //предполагаем существование зависимости						
				
				for (int i = 0; i < aUsage1->GetIndexNumber () && i < aUsage2->GetIndexNumber (); i++)
				{						
					res = ExecuteChain (aUsage1, aUsage2, i);
					
					/*cout << "1: ";
					((Dependence*)curTest->GetDependence (0))->Print ();
					cout << endl;*/

					for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
					{				
						//как только по некоторому измерению в некотором цикле нет зависимости, пропускаем
						if (usagesDep [loop]->IsAlwaysNotExists ()) continue; 	
						
						if (res == SUCCESS)
							temp = usagesDep [loop]->UnionIntersect (curTest->GetDependence (loop), DEP_NOT_EXIST);					
						else
						{//если протестировать не смогли, то предполагаем существование зависимости по измерению
							Dependence* temp1 = new Dependence ();
							temp = usagesDep [loop]->UnionIntersect (temp1, DEP_NOT_EXIST);						
							DELETE_POINTER (temp1);
						}					

						DELETE_POINTER (usagesDep [loop])
						usagesDep [loop] = temp;
						temp = NULL;

						/*cout << "2: ";
						usagesDep [0]->Print ();
						cout << endl;*/

#if (DEBUG & DBG_TEST_ARRAY && DEBUG & DBG_DEP)
						cout << "loop: " << loop << endl;
						usagesDep [loop]->Print ();	
#endif					
					}					
				}

				if (aUsage1->GetIndexNumber () != aUsage2->GetIndexNumber () ||
					aUsage1->GetIndexNumber () < ((ArrayUnit*)mu)->GetDimsNumber ()) 
				{
					//если в использованиях разное число индексных выражений, 
					//или их меньше чем измерений массива, например, при вызове функции
					//то по не протестированным измерениям предполагаем возможную зависимость
					for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
					{
						Dependence* temp1 = new Dependence ();
						temp = usagesDep [loop]->UnionIntersect (temp1, DEP_NOT_EXIST);						
						DELETE_POINTER (temp1);	

						DELETE_POINTER (usagesDep [loop])
						usagesDep [loop] = temp;
						temp = NULL;
					}
				}				
			}
		public:
			IndexTest (TestIdentifier testId) : ITest (testId)
			{				
				first = NULL;
				last = NULL;
				curTest = NULL;
				usagesDep = NULL;
			}

			~IndexTest ()
			{
				DELETE_POINTER (first)
				last = NULL;
				curTest = NULL;
			}

			void Add (ITest* test)
			{
				if (!first) last = first = new TestsChain (test);
				else last = last->SetNextValue (test);				
			}

			bool IsApplicable ()
			{
				ITest :: IsApplicable ();

				if (!mu->IsScalar ()) return true;
				return false;
			}

			TestResult Execute ()
			{//DBG_START
#if DEBUG & DBG_TEST_ARRAY
				cout << "IndexTest :: Execute ()" << endl;
#endif 
				if (!IsApplicable ()) return NOT_APPLICABLE;

				int i;
				DepTestInfo* dTInfo = pu->GetDepTestInfo (mu);
				if (dTInfo->GetIsTested ()) return SUCCESS;

				MemoryUnitUsage* firstInLoop = pu->GetFirstUsage (mu);
				MemoryUnitUsage* lastInLoop = pu->GetLastUsage (mu);
				MemoryUnitUsage* usage1 = firstInLoop;
				MemoryUnitUsage* usage2 = NULL;

				Dependence** dep = NULL;
				Dependence* temp = NULL;			
				
				NEW_POINTER_ARRAY (usagesDep, pu->GetLoopsNumber (), Dependence)
				NEW_POINTER_ARRAY (dep, pu->GetLoopsNumber (), Dependence)

				for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
				{
					usagesDep [loop] = new Dependence ();
					dep [loop] = new Dependence ();
					dep [loop]->SetExistenceCond (DEP_NOT_EXIST, DEP_ALWAYS, DEP_EXACTLY); //предполагаем отсутствие зависимости	
				}

				while (usage1 != lastInLoop->GetNextUsage ())
				{
					usage2 = usage1; //проверка: "сам с собой" тоже нужна
					while (usage2 != lastInLoop->GetNextUsage ())
					{						
#if DEBUG & DBG_TEST_ARRAY
						cout << "CHECK_NULL_POINTER (usage1)" << endl;
						CHECK_NULL_POINTER (usage1)
						
						cout << "CHECK_NULL_POINTER (usage2)" << endl;
						CHECK_NULL_POINTER (usage2)							
#endif 						
						if ((usage1->GetUsageType () != READ ||
							 usage2->GetUsageType () != READ) &&
							 usage1->GetUsageType () != NOT_USAGE &&
							 usage2->GetUsageType () != NOT_USAGE) 
						{							
							ArrayUsage* aUsage1 = dynamic_cast <ArrayUsage*> (usage1);
							ArrayUsage* aUsage2 = dynamic_cast <ArrayUsage*> (usage2);
							if (!aUsage1 || !aUsage2) throw ::Exception::IException ("usage must be ArrayUsage"); //доделать
								
							PURoutineCall* call = NULL;
							PURoutine* routine = NULL;
							bool notTest = false;
							for (int i = 0; i < pu->GetRoutineCallsNumber (); i++)
							{								
								call = pu->GetRoutineCall (i);
								routine = call->GetRoutine ();

								for (int j = 0; j < routine->GetParamsNumber (); j++)
								{
									if ((call->GetParameterUsage (j) == usage1 ||				
										 call->GetParameterUsage (j) == usage2) &&
										!routine->GetParameter (j)->IsScalar ()) 
									{
										notTest = true;
										break;
									}									
								}
								if (notTest) 
									break;
							}
							

							if (notTest)
							{
								for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
									usagesDep [loop]->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_NOT_EXACTLY);								
							}
							else
								TestUsages (aUsage1, aUsage2); //значение попало в usagesDep
							
							/*cout << "3: ";
							usagesDep [0]->Print ();
							cout << endl;*/
							
							for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
							{
								if (dep [loop]->IsAlwaysExists ()) continue;
								
								temp = dep [loop]->UnionIntersect (usagesDep [loop], DEP_EXIST);

								DELETE_POINTER (dep [loop])
								dep [loop] = temp;
								temp = NULL;									
							}
							/*cout << "4: ";
							dep [0]->Print ();
							cout << endl;*/
						}						
						usage2 = usage2->GetNextUsage ();
					}					
					usage1 = usage1->GetNextUsage ();
				}					

				bool isExact = true;
				DepType dType;
				IDependence* tempDep = NULL;
				for (int loop = 0; loop < pu->GetLoopsNumber (); loop++)
				{					
					dTInfo->SetDependence (loop, dep [loop], NOT_CLONE);
					dType = dep[loop]->GetType ();
					if (dType == DEP_UNKNOWN ||
						dType == DEP_COND_EXIST_UNKNOWN ||
						dType == DEP_COND_NOT_EXIST_UNKNOWN)
						isExact = false;
				}
				
				DELETE_ARRAY (dep)
				DELETE_POINTER_ARRAY (usagesDep, pu->GetLoopsNumber ())

				if (isExact)
				{
					dTInfo->SetIsTested ();
					return SUCCESS;
				}

				return FAILURE;
			}

			
		};
	}
}

#endif