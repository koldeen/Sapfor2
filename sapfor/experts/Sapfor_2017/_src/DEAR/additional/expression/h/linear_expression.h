/****************************************************************************************************
 *	Данный класс содержит информацию о линейном выражении.											*
 *	Линейным выражением считается функция вида: fn (vars) * vn + ... + f1 (vars) * v1 + f0 (vars),	*
 *	где fi - некоторая функция от переменных из множества vars, а									*
 *	vi - некоторые переменные, не вошедшие в vars.													*
 ****************************************************************************************************/
#ifndef LINER_EXPRESSION_H
#define LINER_EXPRESSION_H

#include "expression.h"
//#include "expr_variable.h"
#include "index_variable.h"
#include "int_expression.h"

#include "macros.h"

using namespace Expression :: Exceptions;
using namespace Analyzer :: Loop;

#define EXPR_ADDITIONAL_SIZE 5

typedef IndexVariable Variable;

namespace Expression
{
	class LinearExpression : public IExpression
	{
		IExpression* freeTerm; //если не задан, то 0
		IExpression** coeffs; // если не задан, то 1
		Variable** vars;
		int varsNumber;
		int firstFree;
		
		LinearExpression (int varsNumber, bool isIndep) : IExpression (isIndep)
		{
			this->firstFree = 0;
			this->varsNumber = varsNumber;
			this->freeTerm = new IntegerValue (0);

			NEW_POINTER_ARRAY (coeffs, varsNumber, IExpression)
			NEW_POINTER_ARRAY (vars, varsNumber, Variable)			
		}
	public:
		LinearExpression (int varsNumber)
		{
			this->firstFree = 0;
			this->varsNumber = varsNumber;
			this->freeTerm = new IntegerValue (0);

			NEW_POINTER_ARRAY (coeffs, varsNumber, IExpression)
			NEW_POINTER_ARRAY (vars, varsNumber, Variable)
		}

		~LinearExpression ()
		{
			DELETE_POINTER_ARRAY (coeffs, varsNumber)
			DELETE_POINTER_ARRAY (vars, varsNumber)
			DELETE_POINTER (freeTerm)
		}

		IExpression* GetFreeTerm ()	{return freeTerm;}

		void SetFreeTerm (IExpression* freeTerm, bool notClone = false) 
		{
			CHECK_NULL_POINTER (freeTerm)
			DELETE_POINTER (this->freeTerm)

			if (notClone) this->freeTerm = freeTerm;
			else this->freeTerm = freeTerm->Clone ();			
		}

		void AddMonom (IExpression* coeff, Variable* var, bool notClone = false)
		{
			CHECK_NULL_POINTER (coeff)
			CHECK_NULL_POINTER (var)

			if (firstFree >= varsNumber)
			{				
				IExpression** tempCoeffs;
				Variable** tempVars;
				
				NEW_POINTER_ARRAY (tempCoeffs, varsNumber + EXPR_ADDITIONAL_SIZE, IExpression)
				NEW_POINTER_ARRAY (tempVars, varsNumber + EXPR_ADDITIONAL_SIZE, Variable)

				for (int i = 0; i < varsNumber; i++)
				{
					tempCoeffs [i] = coeffs [i];
					coeffs [i] = NULL;

					tempVars [i] = vars [i];
					vars [i] = NULL;
				}

				DELETE_POINTER (coeffs)
				DELETE_POINTER (vars)

				coeffs = tempCoeffs;
				vars = tempVars;	
				
				tempCoeffs = NULL;
				tempVars = NULL;
			}
							
			if (notClone)
			{
				coeffs [firstFree] = coeff;
				vars [firstFree] = var;
			}
			else
			{
				coeffs [firstFree] = coeff->Clone ();
				vars [firstFree] = (Variable*)var->Clone ();
			}
			firstFree++;
		}

		void SubtractMonom (int i)
		{
			CHECK_INDEX_RANGE (i, 0, firstFree)

			DELETE_POINTER (coeffs [i])
			DELETE_POINTER (vars [i])
						
			firstFree--;
			for (; i < firstFree; i++) 
			{
				coeffs [i] = coeffs [i+1];
				vars [i] = vars [i+1];
			}
			
			coeffs [firstFree] = NULL;
			vars [firstFree] = NULL;
			
		}

		/*void SubstituteVariable (Variable* var)
		{
			LinearExpression* lExpr = dynamic_cast <LinearExpression*> (var->GetValue ());
			if (!lExpr) throw :: Exception ::TypeCastException (typeid (var->GetValue).name (), typeid (this).name ());

			for (int i = 0; i < varsNumber; i++)
				if (vars [i] == var) 
				{
					*this = *this + lExpr * coeffs [i];
					this->SubtractMonom (i);	
				}
		}*/
		IExpression* GetCoeffitient (int i) 
		{
			CHECK_INDEX_RANGE (i, 0, firstFree)
			return coeffs [i];
		}

		Variable* GetVariable (int i) 
		{
			CHECK_INDEX_RANGE (i, 0, firstFree)
			return vars [i];
		}

		int GetVariablesNumber () {return firstFree;}

		virtual IExpression* Clone ()
		{			
			LinearExpression* temp = new LinearExpression (varsNumber);			
			
			temp->firstFree = firstFree;
			temp->freeTerm = freeTerm->Clone ();
			
			for (int i = 0; i < temp->GetVariablesNumber (); i++)
			{
				temp->coeffs [i] = coeffs [i]->Clone ();
				temp->vars [i] = (Variable*)vars [i]->Clone ();
			}
						
			return temp;
		}
		virtual std :: string ToString ()
		{
			return std :: string ("class Expression :: LinearExpression");
		}

		virtual IExpression& operator= (IExpression& expr)
		{
			LinearExpression* lExpr = dynamic_cast <LinearExpression*> (&expr);
			if (!lExpr) throw OpNotDefException ('=', typeid (*this).name());

			DELETE_POINTER (freeTerm)
			freeTerm = lExpr->freeTerm->Clone ();

			if (varsNumber < lExpr->varsNumber) 
			{
				DELETE_POINTER_ARRAY (coeffs, varsNumber)
				DELETE_POINTER_ARRAY (vars, varsNumber)

				varsNumber = lExpr->varsNumber;
				NEW_POINTER_ARRAY (coeffs, varsNumber, IExpression)
				NEW_POINTER_ARRAY (vars, varsNumber, Variable)
			}
			else
			{
				for (int i = lExpr->firstFree; i < varsNumber; i++)
				{
					DELETE_POINTER (coeffs [i])
					DELETE_POINTER (vars [i])
				}
			}

			for (int i = 0; i < lExpr->firstFree; i++)
			{
				coeffs [i] = lExpr->coeffs [i]->Clone ();
				vars [i] = (Variable*)lExpr->vars [i]->Clone ();
			}

			if (expr.IsTemp ()) delete &expr;
			return *this;
		}

		/*IExpression& operator+ (IExpression& expr)
		{
			LinearExpression* lExpr = dynamic_cast <LinearExpression*> (expr);
			
			LinearExpression* newExpr = new LinearExpression* 

			if (!lExpr) 
			else 
			{
				LinearExpression
				for (int i = 0; i < GetVariablesNumber (); i++)
			}
		}*/
		
	};
}

#endif