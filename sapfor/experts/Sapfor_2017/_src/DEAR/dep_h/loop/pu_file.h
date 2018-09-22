#ifndef PU_FILE_H
#define PU_FILE_H

#include "program_unit.h"
#include "pu_routine.h"
#include "macros.h"

namespace Analyzer
{
	namespace Loop
	{
		class PUFile : public ProgramUnit
		{
			int fileId;			

			PUFile (int fileId, ProgramUnit* externalNest) : ProgramUnit (externalNest)
			{
				this->fileId = fileId;										
			}

		public:
//********************************* constructors *********************************
			PUFile (int fileId)
			{
				this->fileId = fileId;				
			}		

//**************************** tree creation methods *****************************
			virtual ProgramUnit* Clone ()
			{
				PUFile * temp = new PUFile(fileId, externalPU);				
				temp->musUsage = (RegionUsageCollection*)musUsage->Clone ();
				temp->internalPUs = (ProgramUnitCollection*)internalPUs->Clone ();				
				
				return temp;
			}			

			PURoutine* AddRoutine (int routineId, int paramsNumber)
			{
#if DEBUG & DBG_TREE_CREATE
				cout << "PURoutine* PUFile :: AddRoutine (int, int)" << endl;					
#endif
				PURoutine* routine = new PURoutine (routineId, paramsNumber);

#if DEBUG & DBG_TREE_CREATE
				routine->Print ();
				cout << endl;
#endif
				SetExternalPU (routine, this);

				return (PURoutine*)(*internalPUs) [internalPUs->Add (routine)];
			}		

//****************************** Get... methods **********************************
			int GetId () {return fileId;}			

			bool operator== (ProgramUnit& pu)
			{
				if (this == &pu) return true;
				
				PUFile* file = dynamic_cast <PUFile*> (&pu);
				if (!file) return false;

				if (fileId != file->GetId ()) return false;
				
				return	true;	
			}

#if DEBUG
			void Print ()
			{
				cout << "PUFile :: Print ()" << endl;
				cout << GetId () << " - id" << endl;								
				cout << internalPUs->GetSize () << " - internal routines" << endl;
				cout << musUsage->GetSize () << " - memory units are used" << endl;
			}
#endif
		};
	}
}

#endif
