/****************************************************************************************************
 *	Класс ArrayUsage уточняет порядок использования памяти в случае массивов.						*
 *																									*
 *	Класс ArrayUsage предоставляет следующий интерфейс:												*
 *		- void AddIndexExpr (int dim, IExpression* expr) - указывает, что при обращении к массиву	*
 *		в измерении dim используется выражение expr.												*
 *		- IExpression* GetIndexExpr (int dim) - возвращает индексное выражение в измерении dim,		*
 *		если выражение неизвестно, то возвращается NULL.											*	
 *		- int GetIndexNumber () - возвращает число индесных выражений в обращении к массиву.		*
 ****************************************************************************************************/
#ifndef MU_ARRAY_USAGE_H
#define MU_ARRAY_USAGE_H

#include "debug.h"

#include "mu_usage.h"
#include "macros.h"
#include "expression.h"

using namespace Expression;

namespace Analyzer
{
	namespace Memory
	{
		class ArrayUsage : public MemoryUnitUsage
		{
			IExpression **indexExprs;
			int indexNum;
		public:
			ArrayUsage (UsageType usageType, int indexNum) : MemoryUnitUsage (usageType) 
			{				
				this->indexNum = indexNum;

				if (indexNum == 0) indexExprs = NULL;
				else NEW_POINTER_ARRAY (indexExprs, this->indexNum, IExpression)
			}

			~ArrayUsage ()
			{
				DELETE_POINTER_ARRAY (indexExprs, indexNum) 
			}

			MemoryUnitUsage* Clone ()
			{
				ArrayUsage *arr_usage = new ArrayUsage (usageType, indexNum);

				if (nextUsage) arr_usage->AddNextUsage (nextUsage->Clone ());

				for (int i = 0; i < indexNum; i++)
					arr_usage->AddIndexExpr(i, indexExprs[i]);

				return arr_usage;
			}

			void AddIndexExpr (int dim, IExpression* expr, bool notClone = false)
			{
#if DEBUG & DBG_TREE_CREATE
					cout << "ArrayUsage :: AddIndexExpr (int, IExpression*, bool)" << endl;
					cout << dim << endl;
					if (!expr) cout << "expr IS NULL" << endl;
					else cout << "expr NOT NULL" << endl;
#endif					
				CHECK_INDEX_RANGE (dim, 0, indexNum)				
				DELETE_POINTER (indexExprs [dim]);
				if (notClone || !expr)	indexExprs [dim] = expr;
				else indexExprs [dim] = expr->Clone ();			
			}			

			IExpression* GetIndexExpr (int dim) 
			{ 			
				CHECK_INDEX_RANGE (dim, 0, indexNum)

				return indexExprs [dim];
			}

			int GetIndexNumber () {return indexNum;}

			bool operator== (MemoryUnitUsage& muu)
			{
				if (typeid (muu) != typeid (ArrayUsage)) return false;

				ArrayUsage& arr_usage = (ArrayUsage&)muu;

				if (indexNum != arr_usage.indexNum) return false;
				for (int i = 0; i < indexNum; i++)
					if (indexExprs [i] != arr_usage.indexExprs [i] && 
						(!indexExprs [i] || 
						 !arr_usage.indexExprs [i] || 
						 *indexExprs [i] != *arr_usage.indexExprs [i])) 
						return false; //false, если адреса не совпадают и либо один из ардесов NULL, либо содержимое не совпадает

				return MemoryUnitUsage :: operator== (muu);
			}
		};
	}
}

#endif