#ifndef LOOP_TREE_PRINT_H
#define LOOP_TREE_PRINT_H

#include "debug.h"

#include <iostream>
#include "program_unit.h"
#include "pu_file.h"

extern void put_in_depends(int loop, char* type, int var, char *redop);

using namespace std;
using namespace Analyzer :: Loop;
using namespace Analyzer ::	Memory;
using namespace Analyzer :: Test;

namespace Analyzer
{
	class LoopTreePrint
	{
		PUFile* project;
		bool isDepTested;

		time_t sec;
		unsigned short millitm;

		void PrintInDataBase (TightlyNestedLoops *tnl)
		{
			IDependence* dep = NULL;
			MemoryUnit* mu = NULL;

			for (int muNumber = 0; muNumber < tnl->GetMemoryUnitsNumber (); muNumber++)
			{
				mu = tnl->GetMemoryUnit (muNumber);
				for (int loop = 0; loop < tnl->GetLoopsNumber (); loop++)
				{
					dep = tnl->GetDependence (mu, loop);
					if (dep->IsAlwaysExists ())
					{
						for (int i = 0; i < mu->GetVarsNumber (); i++)
							put_in_depends (tnl->GetLoopId (i), "VAR_DEP_IS", mu->GetVarsId (i), "");
					}
					else if (!dep->IsAlwaysNotExists ())
					{
						for (int i = 0; i < mu->GetVarsNumber (); i++)							
							put_in_depends (tnl->GetLoopId (i), "VAR_DEP_POS", mu->GetVarsId (i), "");
					}
				}
			}
		}

		void PrintTNLoops (ProgramUnit* pu)
		{
			ProgramUnit* intPU = NULL;
			TightlyNestedLoops* tnl = NULL;
			
			for (int i = 0; i < pu->GetInternalPUsNumber (); i++)
			{
				cout << endl << "******************* TIGHTLY NEST *******************" << endl;
				intPU = pu->GetInternalPU (i);
				intPU->PrintAll ();
				tnl = dynamic_cast<TightlyNestedLoops*> (intPU);

				if (tnl)
					 PrintInDataBase (tnl);
					
				PrintTNLoops (intPU);
				cout << endl <<"***************** END TIGHTLY NEST *****************" << endl;
			}
		}
			
	public:
		LoopTreePrint (PUFile* project)
		{
			this->project = project;
		}

		~LoopTreePrint ()
		{
			project = NULL;
		}

		void SetIsDepTested (bool isDepTested)
		{
			this->isDepTested = isDepTested;
		}

		void SetTestTime (time_t sec, unsigned short millitm)
		{
			this->sec = sec;
			this->millitm = millitm;
		}

		void Print ()
		{
			PURoutine* routine = NULL;

			cout << "************************* Results of analysis *************************" << endl;
			if (isDepTested)
			{
				cout << "Dependence analysis was executed" << endl;
				cout << "Dependence analysis time: " << sec << "." << millitm << " seconds" << endl;
			}
			else
				cout << "Dependence analysis was not executed" << endl;

			cout << endl << "Extended loops tree" << endl;

			cout << endl << "************************** PROGRAM **************************" << endl;
			routine = dynamic_cast <PURoutine*> (project->GetInternalPU (0));
			if (!routine) throw :: Exception :: NullPointerException ();
			routine->Print ();
			PrintTNLoops (routine);				
			cout << endl << "************************ END PROGRAM ************************" << endl;

			for (int i = 1; i < project->GetInternalPUsNumber (); i++)
			{
				cout << endl << "************************* PROCEDURE *************************" << endl;
				routine = routine = dynamic_cast <PURoutine*> (project->GetInternalPU (i));
				if (!routine) throw :: Exception :: NullPointerException ();
				routine->Print ();
				PrintTNLoops (routine);				
				cout << endl << "*********************** END PROCEDURE ***********************" << endl;
			}			
		
			cout << endl << "*********************** End results of analysis ***********************" << endl;
		}

	};
}


#endif