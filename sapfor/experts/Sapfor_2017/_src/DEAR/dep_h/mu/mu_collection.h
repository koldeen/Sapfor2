#ifndef MEMORY_UNIT_COLLECTION_H
#define MEMORY_UNIT_COLLECTION_H

#include "collection.h"
#include "memory_unit.h"
#include "macros.h"

#include <cstdlib>

using namespace Collection;

namespace Analyzer
{
	namespace Memory
	{
		class MemoryUnitCollection: public ICollection <MemoryUnit*>
		{		
			MemoryUnit** mus;			

		public:
			MemoryUnitCollection (int musNumber) : ICollection <MemoryUnit*> (musNumber)
			{
				if (musNumber == 0) mus = NULL;
				else NEW_POINTER_ARRAY (mus, this->allocatedSize, MemoryUnit)	
			}
			
			~MemoryUnitCollection ()
			{
				DELETE_ARRAY (mus)
			}		

			ICollection <MemoryUnit*>* Clone () 
			{
				MemoryUnitCollection* newColl = new MemoryUnitCollection (this->allocatedSize);
				for (int i = 0; i < this->size; i++)
					newColl->Add (mus [i]->Clone());

				return newColl;
			}

			int Add (MemoryUnit* mu)
			{
				CHECK_NULL_POINTER (mu)
				CheckCollectionCapacityEx();			
				mus [size++] = mu;			
								
				return size - 1;			
			}

			int AddRange (MemoryUnit** musRange, int rangeSize)
			{
				if (rangeSize <= 0) return NOTHING_ADD;

				CHECK_NULL_POINTER (musRange)
					
				CheckCollectionCapacityEx (rangeSize);
				
				for (int i = 0; i < rangeSize; i++)
				{
					CHECK_NULL_POINTER (musRange [i])
					mus [size++] = musRange [i];				
				}
				
				return size - rangeSize;
			}		

			MemoryUnit* Update(int index, MemoryUnit* mu)
			{
				CheckIndexRangeEx (index);

				MemoryUnit *temp = mus [index];
				mus [index] = mu;

				if (!mu) 
				{
					//сдвигаем коллекцию во избежании пропусков
					size--;
					for (int i = index; i < size; i++)
						mus [i] = mus [i+1];
					mus [size] = NULL;
				}
				
				return temp;
			}

			void Delete (int index) 
			{
				CheckIndexRangeEx (index);				
				
				DELETE_POINTER (mus [index])		

				//сдвигаем коллекцию во избежании пропусков
				size--;
				for (int i = index; i < size; i++)
					mus [i] = mus [i+1];
				mus [size] = NULL;

			}

			void Delete (MemoryUnit* mu) 
			{
				CHECK_NULL_POINTER (mu)

				for (int i = 0; i < size; i++)
					if (*mus [i] == *mu) 
					{
						Delete (i); //не эффективно
						continue;
					}
			}

			int Find (MemoryUnit* mu)
			{
				CHECK_NULL_POINTER (mu)

				for (int i = 0; i < size; i++)
					if (*mus [i] == *mu) return i;
				return ELEMENT_NOT_FOUND;
			}		

			int Find (int varId)
			{
				for (int i = 0; i < size; i++)
					for (int j = 0; j < mus [i]->GetVarsNumber (); j++)
						if (mus [i]->GetVarsId (j) == varId) return i;
				return ELEMENT_NOT_FOUND;
			}
			
			MemoryUnit* operator[] (int index) 
			{
				CheckIndexRangeEx (index);
				return mus [index];
			}

			MemoryUnit* operator[] (MemoryUnit* mu)
			{
				CHECK_NULL_POINTER (mu)

				for (int i = 0; i < size; i++)
					if (*mus [i] == *mu) return mus [i];
				return NULL;
			}			

		};
	}
}

#endif