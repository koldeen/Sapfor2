/****************************************************************************************************************	
 *	Класс ArrayUnit из пространства имен Memory																	*
 *	уточняет информацию по используемой памяти в случае массивов.												*		
 *																												*
 *	Предоставляемый интерфейс:																					*
 *		- ArrayUnit (int varId, int dimsNumber); ArrayUnit (int* varsId, int varsNum, int dimsNumber) -			*
 *		конструктор, создает новый объект описывающий область памяти, соответствующую массиву					*
 *		с числом измерений dimsNumber.																			*
 *		- int GetDimsNumber () - возвращает число измерений в массиве.											*
 *		- IExpression* GetLeftBound (int dim) - возвращает левую границу измерения с номеров dim.				*	 
 *		- IExpression* GetRightBound (int dim) - возвращает правую границу измерения с номеров dim.				*
 *		- void AddDimension (int dim, IExpression* leftBound, IExpression* rightBound, bool notClone = false) -	* 
 *		задает границы измерения с номером dim.																	*
 ****************************************************************************************************************/
#ifndef MEMORY_UNIT_ARRAY_H
#define MEMORY_UNIT_ARRAY_H

#include "memory_unit.h"
#include "mu_usage.h"
#include "mu_dimension.h"
#include "macros.h"
#include "expression.h"

using namespace Expression;

namespace Analyzer
{
	namespace Memory
	{
		class ArrayUnit: public MemoryUnit
		{
			Dimension** dims;
			int dimsNumber;			
		public:
			ArrayUnit (int varId, int dimsNumber) : MemoryUnit (varId) 
			{
				this->dimsNumber = dimsNumber;
				NEW_POINTER_ARRAY (dims, this->dimsNumber, Dimension)				
			}

			ArrayUnit (int* varsId, int varsNum, int dimsNumber) : MemoryUnit (varsId, varsNum) 
			{
				this->dimsNumber = dimsNumber;
				NEW_POINTER_ARRAY (dims, this->dimsNumber, Dimension)				
			}

			~ArrayUnit ()
			{
				DELETE_POINTER_ARRAY (dims, dimsNumber)
			}
			
			MemoryUnit* Clone () 
			{
				ArrayUnit* clone = new ArrayUnit (varsId, varsNum, dimsNumber);

				CLONE_MU (clone)

				for (int i = 0; i < dimsNumber; i++)
					clone->dims [i] = dims [i]->Clone();

				return clone;
			}

			bool IsScalar () {return false;}

			void AddDimension (int dim, IExpression* leftBound, IExpression* rightBound, bool notClone = false)
			{
				CHECK_INDEX_RANGE (dim, 0, dimsNumber)

				if (dims [dim]) delete dims [dim];
				
				IExpression *lb = NULL;
				IExpression *rb = NULL;
				
				if (notClone) 
				{
					lb = leftBound;
					rb = rightBound;
				}
				else
				{
					if (leftBound) lb = leftBound->Clone ();
					if (rightBound) rb = rightBound->Clone ();
				}

				dims [dim] = new Dimension (lb, rb);				
			}		

			int GetDimsNumber () {return dimsNumber;}

			IExpression* GetLeftBound (int dim) 
			{
				if (!dims [dim]) return NULL;
				return dims [dim]->GetLeftBound (); 
			}

			IExpression* GetRightBound (int dim) 
			{
				if (!dims [dim]) return NULL;
				return dims [dim]->GetRightBound (); 
			}

			bool operator== (MemoryUnit& mu)
			{
				//if (typeid (mu) != typeid (ArrayUnit)) return false;

				if (dimsNumber != ((ArrayUnit&)mu).dimsNumber) return false;
				for (int i = 0; i < varsNum; i++)
					if (dims [i] != ((ArrayUnit&)mu).dims [i]) return false;

				return MemoryUnit::operator == (mu);					
			}
		};		
	}
}
#endif