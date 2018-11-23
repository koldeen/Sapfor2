/********************************************************************************
 *	Класс ISgExpression предоставляет интерфейс для доступа к объектам			*
 *	класс SgExpression, основанный на возможностях базового класса IExpression.	*
 *																				*
 *	При создании глубокого копирования объекта SgExpression не производится.	*
 *	При удалении объекта память отведенная под SgExpression не освобождается.	*
 ********************************************************************************/
#ifndef ISAGE_EXPRESSION_H
#define ISAGE_EXPRESSION_H

#include "debug.h"

#include "user.h"
#include "expression.h"
#include "expr_exception.h"
#include "macros.h"

using namespace Expression;

int idOfVars(SgSymbol *s);

namespace Analyzer
{
	class ConstSgExpr;

	class ISgExpression : public IExpression
	{
		SgExpression* expr;

	protected:
		ISgExpression (SgExpression* expr, bool isIndep) : IExpression (isIndep) 
		{
			CHECK_NULL_POINTER (expr)

			this->expr = expr;
		}

		bool IsInteger (SgExpression* e) //доделать тип всего выражения
		{
			if (e->variant () == MINUS_OP)
				return IsInteger (e->lhs ());	
			
			return (e->variant () == INT_VAL);
		} 
		
		bool IsVariable (SgExpression *e) {return (e->variant () == VAR_REF);}

		bool IsConstant (SgExpression *e) //const * const == const && const + const == const - ?
		{
			switch (e->variant ())
			{
			case INT_VAL: case FLOAT_VAL: 
			case DOUBLE_VAL: case CHAR_VAL: 
			case STRING_VAL: case COMPLEX_VAL: 
				return true; break;
			case MINUS_OP:
				return IsConstant (e->lhs ());
			default: return false;
			}
		}

		int GetIntegerValue (SgExpression *e, int minusNum)
		{			
			if (e->variant () == MINUS_OP) 
				return GetIntegerValue (e->lhs (), minusNum + 1);

			if (minusNum % 2 == 0)
				return ((SgValueExp*)e)->intValue ();
			else return -((SgValueExp*)e)->intValue ();
		}

		bool IsMonom (SgExpression* e)
		{
#if DEBUG & DBG_EXPRESSION
			cout << "bool IsMonom (SgExpression*)" << endl;			
			CHECK_NULL_POINTER (e)
#endif
			if (IsVariable (e) || IsConstant (e)) return true;
			if (e->variant () == MULT_OP &&
				(IsVariable (e->lhs ()) && IsConstant (e->rhs ()) ||
				 IsConstant (e->lhs ()) && IsVariable (e->rhs ())))
				 return true;
			/*if (e->variant () == MINUS_OP)
				return IsMonom (e->lhs ());*/
			return false;
		}

		//вызов: LinearLength (e, 1)
		//функция посчитает число плюсов и прибавит к входному параметру
		int LinearLength (SgExpression* e, int len)
		{
#if DEBUG & DBG_EXPRESSION
			cout << "int LinearLength (SgExpression*, len)" << endl;
			cout << "len: " << len << endl;
#endif
			if (IsMonom (e)) return len;

			int left, right;
			
			switch (e->variant())
			{
			case ADD_OP: 
			case SUBT_OP: 								
				left = LinearLength (e->lhs (), len + 1);				
				if (left < 0) return -1;

				right = LinearLength (e->rhs (), 0);								
				if (right < 0) return -1;

				return left + right;
				break;
			default: return -1;    
			}
		}

		int GetLinearExpr (ISgExpression** factor1, ISgExpression** factor2, int curMonomNum, SgExpression* e, int op)
		{
#if DEBUG & DBG_EXPRESSION
			cout << "int GetLinearExpr (ISgExpression**, ISgExpression**, int, SgExpression*)" << endl;	
			cout << "e: ";
			e->unparsestdout ();
			cout << endl;
#endif
			if (IsMonom (e)) 
			{				
				if (IsVariable (e) || IsConstant (e))
				{
					SgExpression* temp = e;
					factor2 [curMonomNum] = NULL;


					if (op == SUBT_OP)
						if (IsConstant (e) && IsInteger (e))
							temp = new SgValueExp (GetIntegerValue (e, 1)); //утечка памяти
						else 
							factor2 [curMonomNum] = new ISgExpression (new SgValueExp (-1)); //утечка памяти					

					factor1 [curMonomNum] = new ISgExpression (temp);
				}
				else
				{
					factor1 [curMonomNum] = new ISgExpression (e->lhs ());
					factor2 [curMonomNum] = new ISgExpression (e->rhs ());
				}
				curMonomNum++;
				return curMonomNum;
			}

			switch (e->variant())
			{
			case ADD_OP: 
			case SUBT_OP: 								
				curMonomNum = GetLinearExpr (factor1, factor2, curMonomNum, e->lhs (),ADD_OP);				
				return GetLinearExpr (factor1, factor2, curMonomNum, e->rhs (), e->variant ());								
				break;
			default: throw Exceptions :: ExprException ("ISgExpression"); 
			}
		}

	public:
		ISgExpression (SgExpression* expr)
		{
			CHECK_NULL_POINTER (expr)

			this->expr = expr;
		}		

		~ISgExpression ()
		{
			expr = NULL;
		}
		
		IExpression* Clone ()
		{
			IExpression *new_expr = new ISgExpression (expr); 
			if (IsTemp ()) delete this; 		 
			return new_expr;
		}

		std :: string ToString () {return std::string ("Analyzer :: ISgExpression");}

		SgExpression* GetSgExpr () {return expr;}

		bool IsInteger () {return IsInteger (expr);}

		bool IsConstant () {return IsConstant (expr);}

		bool IsVariable () {return IsVariable (expr);}		
		
		bool IsMonom () {return IsMonom (expr);}

		bool IsLinear () {return (LinearLength (expr, 1) > 0);}

		int LinearLength () {return LinearLength (expr, 1);}		

		int GetIntegerValue ()
		{
			if (!IsConstant () || !IsInteger ()) throw Exceptions :: ExprException ("ISgExpression");
			return GetIntegerValue (expr, 0);
		}

		int GetId () 
		{
			if (!IsVariable ()) throw Exceptions :: ExprException ("ISgExpression");
			return idOfVars (expr->symbol ());
		}

		void GetLinearExpr (ISgExpression*** factor1, ISgExpression*** factor2)
		{			
			int len = LinearLength ();
			if (len < 0) throw Exceptions :: ExprException ("ISgExpression");

			NEW_POINTER_ARRAY ((*factor1), len, ISgExpression)
			NEW_POINTER_ARRAY ((*factor2), len, ISgExpression)

			GetLinearExpr (*factor1, *factor2, 0, expr, ADD_OP);
		}

		IExpression& operator= (IExpression& expr)
		{
			ISgExpression* iSgExpr = dynamic_cast <ISgExpression*> (&expr);
			if (iSgExpr) this->expr = iSgExpr->expr;

			if (expr.IsTemp ()) delete &expr;
			return *this;
		}			

		/*template <class ValueType> ValueType GetValue ()
		{		
			SgValueExp* sgVExpr = NULL;
			ValueType val;		
			switch (expr->variant ())
			{
			case INT_VAL: 
				sgVExpr = (SgValueExp*) (expr);
				val = (ValueType) (sgVExpr->intValue ());				
				break;
			case FLOAT_VAL: 
			case DOUBLE_VAL: 
			case CHAR_VAL: 
			case COMPLEX_VAL:
			case STRING_VAL: break;			
			default: throw Exceptions :: ExprException ("ISgExpression");
			}
			
			return val;
		}*/	
	
		//дружественные функции (operators.cpp)
		//арифметические операторы
		friend IExpression& Expression :: operator+ (IExpression& expr1, IExpression& expr2);
		friend IExpression& Expression :: operator- (IExpression& expr1, IExpression& expr2);
		friend IExpression& Expression :: operator* (IExpression& expr1, IExpression& expr2);
		friend IExpression& Expression :: operator/ (IExpression& expr1, IExpression& expr2);

		//условные операторы
		friend bool Expression :: operator== (IExpression& expr1, IExpression& expr2);
		friend bool Expression :: operator!= (IExpression& expr1, IExpression& expr2);
		friend bool Expression :: operator< (IExpression& expr1, IExpression& expr2);
		friend bool Expression :: operator<= (IExpression& expr1, IExpression& expr2);
		friend bool Expression :: operator> (IExpression& expr1, IExpression& expr2);
		friend bool Expression :: operator>= (IExpression& expr1, IExpression& expr2);

	};	
}

#endif