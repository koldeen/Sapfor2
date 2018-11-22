/************************************************************************************
 *	 ласс IndexVariableCollection представл€ет собой описание коллекции,			*			
 *	используемой дл€ хранени€ информации об индексных переменных,					*
 *	принадлежащих гнезду циклов.													*
 *																					*
 *	»ндексные переменные упор€дочены в соответствие с принадлежностью циклам.		*
 *	Ќе допускаетс€ пропусков, то есть forall i: 0 <= i < size => iVars [i] != NULL.	*
 *																					*
 *	ƒанна€ коллекци€ €вл€етс€ динамической,											*
 *	дл€ нее возможно указание начального размера.									*		 
 *																					*
 *	√лубокого копировани€ параметров в методах не производитс€.						*
 ************************************************************************************/
#ifndef INDEX_VARIABLE_COLLECTION_H
#define INDEX_VARIABLE_COLLECTION_H

#include "collection.h"
#include "index_variable.h"
#include "macros.h"

#include <cstdlib>

using namespace Collection;

namespace Analyzer
{
	namespace Loop
	{
		class IndexVariableCollection: public ICollection <IndexVariable*>
		{		
			IndexVariable** iVars;			

		public:
			IndexVariableCollection (int iVarsNum) : ICollection <IndexVariable*> (iVarsNum)
			{
				if (iVarsNum == 0) iVars = NULL;
				else NEW_POINTER_ARRAY (iVars, this->allocatedSize, IndexVariable)	
			}
			
			~IndexVariableCollection ()
			{
				DELETE_POINTER_ARRAY (iVars, allocatedSize)
			}		

			ICollection <IndexVariable*>* Clone () 
			{
				IndexVariableCollection* newColl = new IndexVariableCollection (this->allocatedSize);
				for (int i = 0; i < this->size; i++)
					newColl->Add ((IndexVariable*)iVars [i]->Clone());

				return newColl;
			}

			int Add (IndexVariable* iVar); //доделать упор€доченность, NULL?
			int AddRange (IndexVariable** varsRange, int rangeSize); //доделать упор€доченность

			IndexVariable* Update(int index, IndexVariable* iVar)
			{
				CheckIndexRangeEx (index);

				IndexVariable *temp = iVars [index];
				iVars [index] = iVar;

				if (!iVar) 
				{
					//сдвигаем коллекцию во избежании пропусков
					size--;
					for (int i = index; i < size; i++)
						iVars [i] = iVars [i+1];
					iVars [size] = NULL;
				}
				
				return temp;
			}

			void Delete (int index) 
			{
				CheckIndexRangeEx (index);				
				
				DELETE_POINTER (iVars [index])		

				//сдвигаем коллекцию во избежании пропусков
				size--;
				for (int i = index; i < size; i++)
					iVars [i] = iVars [i+1];
				iVars [size] = NULL;

			}

			void Delete (IndexVariable* iVar) 
			{
				CHECK_NULL_POINTER (iVar)

				for (int i = 0; i < size; i++)
					if (*iVars [i] == *iVar) 
					{
						Delete (i); //не эффективно
						continue;
					}
			}

			int Find (IndexVariable* iVar)
			{
				CHECK_NULL_POINTER (iVar)

				for (int i = 0; i < size; i++)
					if (*iVars [i] == *iVar) return i;
				return ELEMENT_NOT_FOUND;
			}			

			int Find (int varId)
			{
				for (int i = 0; i < size; i++)
					if (iVars [i]->GetId () == varId) return i;
				return ELEMENT_NOT_FOUND;
			}
			
			IndexVariable* operator[] (int index) 
			{
				CheckIndexRangeEx (index);
				return iVars [index];
			}

			IndexVariable* operator[] (IndexVariable* iVar)
			{
				CHECK_NULL_POINTER (iVar)

				for (int i = 0; i < size; i++)
					if (*iVars [i] == *iVar) return iVars [i];
				return NULL;
			}

			int GetLoopsNumber ()
			{
				if (size == 0) return 0;

				int prevLoop = iVars [0]->GetLoopId ();
				int loopsCount = 1;

				for (int i = 0; i < size; i++)
					if (iVars [i]->GetLoopId () != prevLoop) 
					{						
						loopsCount++;
						prevLoop = iVars [i]->GetLoopId ();
					}

				return loopsCount;

			}			

			//отдел€ем индексные переменные, соответствующие последним loopsNum циклам
			IndexVariableCollection* SplitCollection (int loopsNum)
			{
				if (size == 0) return new IndexVariableCollection (0);
				
				int prevLoop = iVars [size - 1]->GetLoopId ();
				int loopsCount = 1;
				int i = size - 2;
				IndexVariableCollection* newColl;

				while (loopsCount <= loopsNum && i >= 0)
				{
					if (iVars [i]->GetLoopId () != prevLoop) 
					{
						prevLoop = iVars [i]->GetLoopId ();
						loopsCount++;
					}
					i--;
				}

				if (loopsCount > loopsNum) 
				{
					i++;
					i++;

					newColl = new IndexVariableCollection (size - i);
					
					for (int j = i; j < size; j++) 
					{
						newColl->iVars [newColl->size++] = iVars [j];
						iVars [j] = NULL;
					}
					size = i;					
				}
				else
				{
					//в коллекции разлчиных циклов не больше, чем loopsNum

					newColl = new IndexVariableCollection (0);
					newColl->iVars = iVars;
					newColl->size = size;
					newColl->allocatedSize = allocatedSize;
					this->iVars = NULL;
					this->size = 0;
					this->allocatedSize = 0;					
				}

				return newColl;
			}


		};
	}
}

#endif