//доделать lastAccess (Delete, Update и др.)

#ifndef TN_LOOPS_COLLECTION_H
#define TN_LOOPS_COLLECTION_H

#include "collection.h"
#include "coll_list_element.h"

using namespace Collection;

namespace Analyzer
{
	namespace Loop
	{
		class ProgramUnit;		
		typedef ListElement<ProgramUnit*> PUnitList;

		class ProgramUnitCollection : public ICollection <ProgramUnit*>
		{
			PUnitList* first;
			PUnitList* last;
			PUnitList* lastAccess;
			int lAccessIndex;

		public:
			ProgramUnitCollection ()
			{
				first = NULL;
				last = NULL;
				lastAccess = NULL;
				lAccessIndex = 0;
			}

			~ProgramUnitCollection ()
			{
				DELETE_POINTER (first); 
				last = NULL; //delete last выполнено автоматически при удалении first
				lastAccess = NULL;
			}

			ICollection <ProgramUnit*>* Clone ();

			int Add (ProgramUnit* tnl)
			{   
				if (!first) lastAccess = last = first = new PUnitList (tnl);
				else last = last->SetNextValue (tnl);
				
				allocatedSize++;
				size++;				
				return size - 1;
			}

			int AddRange (ProgramUnit** tnls, int rangeSize)
			{
				CHECK_NULL_POINTER (tnls)

				if (rangeSize <= 0) return NOTHING_ADD;

				int res = Add (tnls [0]);
				
				for (int i = 1; i < rangeSize; i++)				
					last = last->SetNextValue (tnls [i]);

				allocatedSize += rangeSize - 1;
				size = allocatedSize;

				return res;
			}

			ProgramUnit* Update (int index, ProgramUnit* tnl)
			{
				CheckIndexRangeEx (index);
				
				ProgramUnit* prev;
				PUnitList* temp;

				if (index = size - 1) temp = last;
				else
				{
					temp = first;
					for (int i = 0; i < index; i++)
						temp = temp->GetNext ();					
				}
				prev = temp->SetValue (tnl);
				
				return prev;
			}

			void Delete (int index)
			{
				CheckIndexRangeEx (index);

				PUnitList* del = NULL;

				if (index == 0) 
				{
					del = first;
					first = first->SetNext (NULL);
				}
				else
				{
					PUnitList* temp = first;

					for (int i = 0; i < index - 1; i++)
						temp = temp->GetNext ();

					del = temp->GetNext ();
					temp->SetNext (del->SetNext (NULL));	
				}
				size--;
				allocatedSize--;
				
				DELETE_POINTER (del)	
			}

			void Delete (ProgramUnit* tnl);
			
			int Find (ProgramUnit* tnl);
			
			ProgramUnit* operator [] (int index)
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

			ProgramUnit* operator [] (ProgramUnit* tnl);		
		};

	}
}

#endif