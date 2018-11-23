/****************************************************************
 *	ƒанный класс отвечает за решение в целых числах уравнени€:	*
 *	firstCoeff * x + secondCoeff * y = freeTerm					*
 *	с целыми коэффициентами.									*
 *																*
 *	–ешение предоставл€етс€ в виде:								*
 *	x = fPSolution + fGSCoeff * t								*
 *	y = sPSolution + sGSCoeff * t								*
 ****************************************************************/
#ifndef LE_TWO_VARIABLE_H
#define LE_TWO_VARIABLE_H

#include "math_equations.h"
#include "linear_expression.h"
#include "math_gcd.h"

#include "exception.h"

using namespace Epxpression;

namespace Mathematics
{
	class InvalidExpressionException : public Exception :: IException
	{
	public:
		InvalidExpressionException (:: std :: string msg) : IException (msg) {}
	};

	class LETwoVariable : public IEquation
	{
		LinearExpression* equation;			

		SolutionExistence isSExist;		//is solution exists
		SolvingStatus isSolved;			//is solved

	public:
		LETwoVariable (Expression :: LinearExpression* equation, bool notClone = CLONE)
		{
			CHECK_NULL_POINTER (equation);			

			if (notClone) this->equation = equation;
			else this->equation = equation->Clone ();
			
			LinearExpression* lExpr = NULL;

			switch (equation->GetVariablesNumber ())
			{
			case 0:
			case 1:
				{
					lExpr = new LinearExpression (1);
					lExpr->SetFreeTerm (new IntegerValue (0), NOT_CLONE);
					lExpr->AddMonom (new IntegerValue (1), new Variable (), NOT_CLONE);

					equation->GetVariable (1)->SetValue (lExpr);					
				}
			case 2:
				{
					Variable* param = new Variable ();		

					lExpr = new LinearExpression (1);
					lExpr->SetFreeTerm (new IntegerValue (0), NOT_CLONE);
					lExpr->AddMonom (new IntegerValue (1), param, NOT_CLONE);

					equation->GetVariable (1)->SetValue (lExpr, OT_CLONE);			
					
					lExpr = new LinearExpression (1);
					lExpr->SetFreeTerm (new IntegerValue (0), NOT_CLONE);
					lExpr->AddMonom (new IntegerValue (1), param, NOT_CLONE);

					equation->GetVariable (2)->SetValue (lExpr, NOT_CLONE);
					break;
				}
			default: throw InvalidExpressionException ("must be less then 3 variable in linear equation");
			}

			Variable* param = new Variable ();		

			for (int i = 0; i < equation->GetVariablesNumber (); i++)
			{
				//по умолчанию устанавливаетс€: решение любое целое число
				LinearExpression* lExpr = new LinearExpression (1);
				lExpr->SetFreeTerm (new IntegerValue (0), NOT_CLONE);
				lExpr->AddMonom (new IntegerValue (1), param, NOT_CLONE);
				
				equation->GetVariable (i)->SetValue (lExpr);
			}			
			
			isSolved = NOT_SOLVED;
			isSExist = SOLUTION_EXIST;
		}

		virtual IObject* Clone ()
		{
			LETwoVariable* newEquation =  new LETwoVariable (equation);

			newEquation->isSExist = this->isSExist;
			newEquation->isSolved = this->isSolved;
			
			

			return newEquation;
		}

		virtual void Solve ()
		{	
			if (IsSolutionExist () == SOLUTION_NOT_EXIST) return;
			if (IsSolved () == SOLVED) return;

			//в случае firstCoeff == secondCoeff == freeTerm == 0 решение задано по умолчанию

			GCDTwoNumbers gcd (firstCoeff, secondCoeff);
			int q = equation->GetFreeTerm() / gcd.GetGCD ();

			
			fPSolution = q * gcd.GetFNCoeff ();
			sPSolution = q * gcd.GetSNCoeff ();

			fGSCoeff = - secondCoeff / gcd.GetGCD ();
			sGSCoeff = firstCoeff / gcd.GetGCD ();
		}

		virtual SolutionExistence IsSolutionExist ()
		{
			if (isSolved == SOLVED) return isSExist;

			if (firstCoeff == 0 && secondCoeff == 0)
			{				
				if (freeTerm == 0) isSExist = SOLUTION_EXIST;				
				else isSExist = SOLUTION_NOT_EXIST;
			}
			else
			{
				GCDTwoNumbers gcd (firstCoeff, secondCoeff);
				if (freeTerm % gcd.GetGCD () == 0) return SOLUTION_EXIST;			
				isSExist = SOLUTION_NOT_EXIST;			
			}

			isSolved = SOLVED;			

			return isSExist;
		}

		virtual SolvingStatus IsSolved () {return isSolved;}

		int GetFirstSolution () {return firstSolution;}

		int GetSecondSoultion () {return secondSolution;}
	};
}

#endif