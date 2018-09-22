/****************************************************************************************************
 *	¬спомогательный класс Dimension содержит информацию по											*
 *	отдельному измерению массива.																	*
 *																									*
 *	“ак как класс €вл€етс€ вспомогательным и используетс€ только внутри пространства имен Memory	*
 *	глубокого копировани€ граничных выражений не производитс€.										*
 *																									*
 *	≈сли граница неизвестна, то она устанавливаетс€ в NULL.											*
 ****************************************************************************************************/
#ifndef MEMORY_UNIT_DIMENSION_H
#define MEMORY_UNIT_DIMENSION_H

#include "macros.h"
#include "expression.h"

using namespace Expression;

namespace Analyzer
{
	namespace Memory
	{
		class Dimension
		{
			IExpression* leftBound;
			IExpression* rightBound;
		public:
			Dimension (IExpression* leftBound, IExpression* rightBound)
			{
				this->leftBound = leftBound;
				this->rightBound = rightBound;
			}

			~Dimension ()
			{
				DELETE_POINTER (leftBound)
				DELETE_POINTER (rightBound)				
			}

			Dimension* Clone ()
			{
				return new Dimension (leftBound->Clone (), rightBound->Clone ());
			}

			IExpression* GetLeftBound () {return leftBound;}

			IExpression* GetRightBound () {return rightBound;}
		};
	}
}

#endif