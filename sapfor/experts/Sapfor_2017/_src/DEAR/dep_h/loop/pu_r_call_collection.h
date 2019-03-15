#ifndef PU_R_CALL_COLLECTION_H
#define PU_R_CALL_COLLECTION_H

#include "collection.h"
#include "coll_list_element.h"
#include "pu_routine_call.h"
#include "macros.h"

using namespace Collection;

namespace Analyzer
{	
	namespace Loop
	{
		typedef ListElement<PURoutineCall*> PURCallList;

		class PURoutineCallCollection : public ICollection <PURoutineCall*>
		{
			PURCallList* first;
			PURCallList* last;
			PURCallList* lastAccess;
			int lAccessIndex;

		public:
			PURoutineCallCollection () 
			{
				this->first = NULL;
				this->last = NULL;
				lastAccess = NULL;
				lAccessIndex = 0;
			}			
			~PURoutineCallCollection ()
			{
				DELETE_POINTER (first)
				last = NULL;
				lastAccess = NULL;
			}

			ICollection <PURoutineCall*>* Clone ()
			{
				PURoutineCallCollection *newColl = new PURoutineCallCollection ();
				PURCallList* temp = first;

				for (int i = 0; i < size; i++)
				{
					newColl->Add (temp->GetValue ()->Clone ());
					temp = temp->GetNext();
				}

				return newColl;
			}
			
			int Add (PURoutineCall* call)
			{
				if (!first) lastAccess = last = first = new PURCallList (call);
				else last = last->SetNextValue (call);
				
				allocatedSize++;
				size++;
				return size - 1;
			}
			int AddRange (PURoutineCall** calls, int rangeSize) 
			{
				CHECK_NULL_POINTER (calls)

				if (rangeSize <= 0) return NOTHING_ADD;

				int res = Add (calls [0]);
				
				for (int i = 1; i < rangeSize; i++)				
					last = last->SetNextValue (calls [i]);

				allocatedSize += rangeSize - 1;
				size = allocatedSize;

				return res;
			}

			PURoutineCall* Update (int index, PURoutineCall* call) 
			{
				CheckIndexRangeEx (index);
				
				PURoutineCall* prev;
				PURCallList* temp;

				if (index = size - 1) temp = last;
				else
				{
					temp = first;
					for (int i = 0; i < index; i++)
						temp = temp->GetNext ();					
				}
				prev = temp->SetValue (call);
				
				return prev;
			}
			
			virtual void Delete (int index) 
			{ 
				CheckIndexRangeEx (index);

				PURCallList* del = NULL;

				if (index == 0) 
				{
					del = first;
					first = first->SetNext (NULL);
				}
				else
				{
					PURCallList* temp = first;

					for (int i = 0; i < index - 1; i++)
						temp = temp->GetNext ();

					del = temp->GetNext ();
					temp->SetNext (del->SetNext (NULL));	
				}
				size--;
				allocatedSize--;
				
				DELETE_POINTER (del)
				
			}
			virtual void Delete (PURoutineCall* call) 
			{
				CHECK_NULL_POINTER (call)

				if (!first) return;
				
				PURCallList* del = NULL;

				while (*call == *first->GetValue ())
				{
					del = first;
					first = first->SetNext (NULL);

					size--;
					allocatedSize--;
						
					DELETE_POINTER (del)
				}

				PURCallList* temp = first;
				
				for (int i = 0; i < size; i++)
				{					
					if (call == temp->GetValue () ||
						(*call) == (*(temp->GetNext ()->GetValue ())))
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

			virtual int Find (PURoutineCall* call) 
			{
				CHECK_NULL_POINTER (call)

				PURCallList* temp = first;				
				
				for (int i = 0; i < size; i++)
				{					
					if (call == temp->GetValue() || 
						(*call) == (*(temp->GetValue ()))) return i;
					temp = temp->GetNext ();					
				}

				return ELEMENT_NOT_FOUND;
			}		

			PURoutineCall* operator[] (int index)
			{
				CheckIndexRangeEx (index);
				
				if (index < lAccessIndex)
				{
					lAccessIndex = 0;
					lastAccess = first;
				}				

				for (; lAccessIndex < index; lAccessIndex++)
						lastAccess = lastAccess->GetNext ();

				return lastAccess->GetValue ();
			}	

			PURoutineCall* operator[] (PURoutineCall* call)
			{
				CHECK_NULL_POINTER (call)

				PURCallList* temp = first;				
				
				for (int i = 0; i < size; i++)
				{					
					if (call == temp->GetValue () ||
						(*call) == (*(temp->GetValue ()))) return temp->GetValue ();
					temp = temp->GetNext ();					
				}

				return NULL;		
			}			
		};
	}	
}

#endif