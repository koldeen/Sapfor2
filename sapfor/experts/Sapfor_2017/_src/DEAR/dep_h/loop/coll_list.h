#ifndef COLLECTION_LIST_H
#define COLLECTION_LIST_H

#include "collection.h"
#include "coll_list_element.h"
#include "macros.h"

using namespace Collection;
using namespace Analyzer :: Memory;

namespace Collection
{	

	typedef ListElement<Element> ElementList;

	template <class Element> class ListCollection : public ICollection <Element>
	{
		ElementList* first;
		ElementList* last;
		ElementList* lastAccess;
		int lAccessIndex;

	public:
		ListCollection () 
		{
			this->first = NULL;
			this->last = NULL;
			lastAccess = NULL;
			lAccessIndex = 0;
		}			
		~ListCollection ()
		{
			DELETE_POINTER (first)
			last = NULL;
			lastAccess = NULL;
		}

		ICollection <Element>* Clone ()
		{
			RegionUsageCollection *newColl = new RegionUsageCollection ();
			RegionUsageList* temp = first;

			for (int i = 0; i < size; i++)
			{
				newColl->Add (temp->GetValue ()->Clone ());
				temp = temp->GetNext();
			}

			return newColl;
		}
		
		int Add (RegionUsage* ru)
		{
			if (!first) lastAccess = last = first = new RegionUsageList (ru);
			else last = last->SetNextValue (ru);
			
			allocatedSize++;
			size++;
			return size - 1;
		}
		int AddRange (RegionUsage** rus, int rangeSize) 
		{
			CHECK_NULL_POINTER (rus)

			if (rangeSize <= 0) return NOTHING_ADD;

			int res = Add (rus [0]);
			
			for (int i = 1; i < rangeSize; i++)				
				last = last->SetNextValue (rus [i]);

			allocatedSize += rangeSize - 1;
			size = allocatedSize;

			return res;
		}

		RegionUsage* Update (int index, RegionUsage* ru) 
		{
			CheckIndexRangeEx (index);
			
			RegionUsage* prev;
			RegionUsageList* temp;

			if (index = size - 1) temp = last;
			else
			{
				temp = first;
				for (int i = 0; i < index; i++)
					temp = temp->GetNext ();					
			}
			prev = temp->SetValue (ru);
			
			return prev;
		}
		
		virtual void Delete (int index) 
		{ 
			CheckIndexRangeEx (index);

			RegionUsageList* del = NULL;

			if (index == 0) 
			{
				del = first;
				first = first->SetNext (NULL);
			}
			else
			{
				RegionUsageList* temp = first;

				for (int i = 0; i < index - 1; i++)
					temp = temp->GetNext ();

				del = temp->GetNext ();
				temp->SetNext (del->SetNext (NULL));	
			}
			size--;
			allocatedSize--;
			
			DELETE_POINTER (del)
			
		}
		virtual void Delete (RegionUsage* ru) 
		{
			CHECK_NULL_POINTER (ru)

			if (!first) return;
			
			RegionUsageList* del = NULL;

			while (*ru == *first->GetValue ())
			{
				del = first;
				first = first->SetNext (NULL);

				size--;
				allocatedSize--;
					
				DELETE_POINTER (del)
			}

			ListElement<RegionUsage*>* temp = first;
			
			for (int i = 0; i < size; i++)
			{					
				if (ru == temp->GetValue () ||
					(*ru) == (*(temp->GetNext ()->GetValue ())))
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

		virtual int Find (RegionUsage* ru) 
		{
			CHECK_NULL_POINTER (ru)

			RegionUsageList* temp = first;				
			
			for (int i = 0; i < size; i++)
			{					
				if (ru == temp->GetValue() || 
					(*ru) == (*(temp->GetValue ()))) return i;
				temp = temp->GetNext ();					
			}

			return ELEMENT_NOT_FOUND;
		}		

		RegionUsage* operator[] (int index)
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

		RegionUsage* operator[] (RegionUsage* ru)
		{
			CHECK_NULL_POINTER (ru)

			RegionUsageList* temp = first;				
			
			for (int i = 0; i < size; i++)
			{					
				if (ru == temp->GetValue () ||
					(*ru) == (*(temp->GetValue ()))) return temp->GetValue ();
				temp = temp->GetNext ();					
			}

			return NULL;		
		}
		RegionUsage* operator[] (MemoryUnit* mu)
		{
			CHECK_NULL_POINTER (mu)				

			RegionUsageList* temp = first; 

			for (int i = 0; i < size; i++)
			{					
				if (mu == temp->GetValue ()->GetMemoryUnit () ||
					*mu == *(temp->GetValue ()->GetMemoryUnit ())) return temp->GetValue ();
				temp = temp->GetNext ();					
			}

			return NULL;	
		}
	};		
}

#endif