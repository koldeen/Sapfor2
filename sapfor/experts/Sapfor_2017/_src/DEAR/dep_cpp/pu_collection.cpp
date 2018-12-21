#include "../dep_h/loop/pu_collection.h"
#include "../dep_h/loop/program_unit.h"

namespace Analyzer
{
	namespace Loop
	{
		//клонирование частичное, так как дерево считается глобальным
		//для клонирования всего дерева, возможно написание отдельной функции ICollection <TightlyNestedLoops*>* CloneTree ()
		ICollection <ProgramUnit*>* ProgramUnitCollection :: Clone ()
		{
			ProgramUnitCollection *newColl = new ProgramUnitCollection ();
			PUnitList* temp = first;

			for (int i = 0; i < size; i++)
			{
				newColl->Add (temp->GetValue ());
				temp = temp->GetNext();
			}

			return newColl;
		}

		void ProgramUnitCollection :: Delete (ProgramUnit* tnl)
		{				
			CHECK_NULL_POINTER (tnl)

			if (!first) return;
			
			PUnitList* del = NULL;

			while (*tnl == *first->GetValue ())
			{
				del = first;
				first = first->SetNext (NULL);

				size--;
				allocatedSize--;
					
				DELETE_POINTER (del)
			}

			PUnitList* temp = first;
			
			for (int i = 0; i < size; i++)
			{					
				if (tnl == temp->GetValue () ||
					(*tnl) == (*(temp->GetNext ()->GetValue ())))
				{
					del = temp->GetNext ();
					temp->SetNext (del->SetNext (NULL));	

					size--;
					allocatedSize--;
					
					DELETE_POINTER (del)
				}
				temp = temp->GetNext ();
			}				
		}

		int ProgramUnitCollection :: Find (ProgramUnit* tnl)
		{
			CHECK_NULL_POINTER (tnl)

			PUnitList* temp = first;				
			
			for (int i = 0; i < size; i++)
			{					
				if (tnl == temp->GetValue() || 
					(*tnl) == (*(temp->GetValue ()))) return i; //узкое место, можно сравнивать указатели
				temp = temp->GetNext ();					
			}

			return ELEMENT_NOT_FOUND;
		}

		ProgramUnit* ProgramUnitCollection :: operator [] (ProgramUnit* tnl)
		{
			CHECK_NULL_POINTER (tnl)

			PUnitList* temp = first;				
			
			for (int i = 0; i < size; i++)
			{					
				if (tnl == temp->GetValue () ||
					(*tnl) == (*(temp->GetValue ()))) return temp->GetValue ();
				temp = temp->GetNext ();					
			}

			return NULL;		
		}
	}
}