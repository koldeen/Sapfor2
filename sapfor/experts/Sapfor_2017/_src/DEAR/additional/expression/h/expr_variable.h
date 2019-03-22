/****************************************************************
 *	Данный класс описывает выржение, являющееся переменной.		*
 *	Переменная одна и та же, если совпадают указатели.			*
 *	Переменная и выражение равны, если совпадают их значения.	*
 ****************************************************************/

#ifndef EXPR_VARIABLE_H
#define EXPR_VARIABLE_H

#include "expression.h"
#include "macros.h"
#include <stdio.h>
#include <cstring>

namespace Expression
{
	class Variable: public IExpression 
	{		
		IExpression* value;
	public:
		Variable ()
		{
			this->value = NULL;
		}
		Variable (IExpression* value, bool notClone = CLONE)
		{
			this->SetValue (value, notClone);
		}

		~Variable ()
		{
			DELETE_POINTER (value);
		}

		IExpression* Clone ()
		{
			Variable* var = new Variable (value);

			if (IsTemp ()) DELETE_POINTER (this);

			return var;
		}
		:: std :: string ToString ()
		{
			char s[30];
			sprintf (s, "value of variable %d is ", this);
			
			return :: std :: string (s) + value->ToString ();			
		}	
		
		IExpression* GetValue () {return value;}

		void SetValue (IExpression* value, bool notClone = CLONE) 
		{
			if (!value || (notClone && !value->IsTemp ())) 
				this->value = value;
			else
			{
				this->value = value->Clone ();			
				if (value->IsTemp ()) DELETE_POINTER (value);
			}
		}	

		IExpression& operator= (IExpression& expr)
		{
			Variable* var = dynamic_cast <Variable*> (&expr);

			DELETE_POINTER (value);

			if (var) this->value = var->GetValue ()->Clone ();
			else
			{
				value = expr->Clone ();
			}

			if (expr.IsTemp ()) DELETE_POINTER (&expr);
		}

		bool operator== (IExpression& expr)
		{
			if (this == &expr) return true;

			return *value == expr;
		}

		bool operator!= (IExpression& expr)
		{
			return !(*this == expr);
		}
	};		
				
}

#endif