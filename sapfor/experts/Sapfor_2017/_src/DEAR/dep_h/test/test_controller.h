#ifndef TEST_CONTROLLER_H
#define TEST_CONTROLLER_H

#include "tn_loops.h"
#include "macros.h"

#include "test_status.h"
#include "test_chain.h"
#include "test_tree_browse.h"

#include "test_scalar.h"
#include "test_read_only.h"
#include "test_array_preproc.h"
#include "test_index.h"
#include "test_i_const.h"
#include "test_gcd.h"
#include "test_i_linear2.h"
#include "test_il_2_cstep.h"
#include "test_usage_in_r.h"
#include "test_r_arr_p.h"

#include "pu_routine.h"

using namespace Analyzer :: Loop;

namespace Analyzer
{
	namespace Test
	{
		class TestController 
		{			
			TestsCollection* testsChain;			
			TNLTreeBrowse* treeBrowse;	
			PUFile* project;
			int execTestNumber;

			TestingStatus* ExecRoutineTest (PURoutine* routine)
			{				
				treeBrowse->SetTNLoops (routine);

#if DEBUG & DBG_DEP
				cout << "TestController :: ExecuteTests ()" << endl;
				cout << "c - continue\nn - not stop" << endl;

				char ch = '\0';
				int numTNL = 0; 
				int numMUxTNL = 0;
				ProgramUnit* prevTNL = NULL;
#endif
				while (!treeBrowse->IsAllView ())
				{	
#if DEBUG & DBG_DEP
					numMUxTNL++;
					if (ch != 'n')
					{						
						ch = '\0';
						while (ch != 'c' && ch != 'n') 
						{
							cout << ">";					
							cin >> ch;
						}
					}
					
					if (prevTNL != treeBrowse->GetCurrentTNLoops ())
					{
						numTNL++;
						prevTNL = treeBrowse->GetCurrentTNLoops ();
						cout << endl << "CURRENT NEST" << endl << endl;
						prevTNL->Print ();
						cout << endl;
					}

					cout << "***************** before testing *****************" << endl;					
					treeBrowse->GetCurrentTNLoops ()->Print (treeBrowse->GetCurrentMUnit ());
					
					if (ch != 'n')
					{						
						ch = '\0';
						while (ch != 'c'  && ch != 'n')
						{
							cout << ">";					
							cin >> ch;
						}
					}
					
					
#endif			
					
					testsChain->Execute (treeBrowse->GetCurrentTNLoops (), treeBrowse->GetCurrentMUnit ());
					
	
#if DEBUG & DBG_DEP
					cout << "***************** after testing ******************" << endl;
					treeBrowse->GetCurrentTNLoops ()->Print (treeBrowse->GetCurrentMUnit ());
					cout << endl;

#endif

					treeBrowse->Next ();
					
				}	

#if DEBUG & DBG_DEP
				cout << numTNL << " - tightly nested loops were tested" << endl;
				cout << endl << numMUxTNL << " - (memory units >< tightly nested loops) were tested" << endl << endl;
#endif

				return NULL;
			}

			TestingStatus* ExecTest (PURoutine* routine)
			{
				execTestNumber++;
				PURoutine* intRoutine;

				
				for (int i = 0; 
					 i < routine->GetRoutineCallsNumber () &&
					 execTestNumber <= project->GetInternalPUsNumber (); //если число запусков теста больше, чем число процедур, то 
																		 //существует рекурсия => чтобы не зациклится останавливаемся.
					i++)
					{						
						intRoutine = routine->GetRoutineCall (i)->GetRoutine ();						
						if (!intRoutine->GetIsTested ())							
							ExecTest (intRoutine);								
					}
				ExecRoutineTest (routine);
				routine->SetIsTested ();
				
				return NULL;
			}
			
		public:
			TestController ()
			{
				int muTId = 0;
				testsChain = new TestsCollection ();
				treeBrowse = new TNLTreeBrowse ();	

				testsChain->Add (new UsageInRoutineTest (muTId++));

#if TEST_SCALAR
				testsChain->Add (new ScalarTest (muTId++));
#endif

#if TEST_READ_ONLY
				testsChain->Add (new ReadOnlyTest (muTId++));
#endif

#if TEST_INDEX
				testsChain->Add (new PreArrayTest (muTId++));

				IndexTest* iTest = new IndexTest (muTId++);
#if TEST_INDEX_CONST
				iTest->Add (new ConstIndexTest (iTest->GetTestId ()));				
#endif

#if TEST_INDEX_LINEAR_2
				iTest->Add (new GCDTest (iTest->GetTestId ()));
				iTest->Add (new Linear2IndexTest (iTest->GetTestId ()));
				iTest->Add (new Linear2CStepIndexTest (iTest->GetTestId ()));
#endif
				testsChain->Add (iTest);
#endif
				testsChain->Add (new ArrayParamRTest (muTId++));
				
			}

			~TestController ()
			{
				DELETE_POINTER (testsChain)	
				DELETE_POINTER (treeBrowse)				
			}

			ProgramUnit* GetTestedProject () {return project;}
			
			PUFile* SetTestedProject (PUFile* project) 
			{
				PUFile* temp = this->project;
				this->project = project;

				return temp;
			}		

			TestingStatus* ExecuteTests ()
			{				
				if (!project) return NULL;
				execTestNumber = 0;

				PURoutine* mainRoutine = dynamic_cast <PURoutine*> (project->GetInternalPU (0));
				if (!mainRoutine) return NULL;

				return ExecTest (mainRoutine);			
			}

		};
	}
}

#endif