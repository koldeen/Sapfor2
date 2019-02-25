#ifndef EXPR_EXCEPTION_H
#define EXPR_EXCEPTION_H

#include "exception.h"
#include "expr_language.h"
#include <string>

namespace Expression
{
	namespace Exceptions
	{
		class ExprException : public :: Exception :: IException
		{
		protected:
			std :: string exprType;			
		public:
			ExprException (std :: string exprType) : exprType (exprType) 
			{
				msg = Expression :: Language :: Lang :: GetError () + ".\n" + 
					Expression :: Language :: Lang :: GetInExprOfType () + " " + exprType + ".\n";
			}
			
			std :: string GetExprType () { return exprType; }		 
		};

		class OperatorException : public ExprException
		{
		protected:
			char op;

		public:
			OperatorException (char op, std :: string exprType) : ExprException (exprType), op (op) 
			{
				msg += Expression :: Language :: Lang :: GetInOperator () + " " + op + ".\n";
			}
		};		
		class OpNotDefException : public OperatorException
		{
		public:
			OpNotDefException (char op, std :: string exprType) : OperatorException (op, exprType)
			{
				msg += Expression :: Language :: Lang :: GetOpNotDef () + ".\n";
			}
		};

	}
}

#endif