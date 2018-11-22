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
#include "math_gcd.h"

namespace Mathematics
{
	class LETwoVariable : public IEquation
	{
		int firstCoeff;					//first coefficient
		int secondCoeff;				//second coefficient
		int freeTerm;					//free term

		int fPSolution;					//first partial solution
		int sPSolution;					//second partial solution
		int fGSCoeff;					//first general solution
		int sGSCoeff;					//second general solution

		SolutionExistence isSExist;		//is solution exists
		SolvingStatus isSolved;			//is solved

	public:
		LETwoVariable (int firstCoeff, int secondCoeff, int freeTerm)
		{
			this->firstCoeff = firstCoeff;
			this->secondCoeff = secondCoeff;
			this->freeTerm = freeTerm;

			//по умолчанию устанавливаетс€: решение любое целое число
			this->fPSolution = 0;
			this->sPSolution = 0;
			this->fGSCoeff = 1;
			this->sGSCoeff = 1; 	

			isSolved = NOT_SOLVED;
			isSExist = SOLUTION_EXIST;
		}

		virtual IObject* Clone ()
		{
			LETwoVariable* newEquation =  new LETwoVariable (firstCoeff, secondCoeff, freeTerm);

			newEquation->isSExist = this->isSExist;
			newEquation->isSolved = this->isSolved;
			newEquation->fPSolution = this->fPSolution;
			newEquation->sPSolution = this->sPSolution;
			newEquation->fGSCoeff = this->fGSCoeff;
			newEquation->sGSCoeff = this->sGSCoeff;

			return newEquation;
		}

		virtual void Solve ()
		{	
			if (IsSolutionExist () == SOLUTION_NOT_EXIST) return;
			if (IsSolved () == SOLVED) return;

			//в случае firstCoeff == secondCoeff == freeTerm == 0 решение задано по умолчанию

			GCDTwoNumbers gcd (firstCoeff, secondCoeff);
			int q = freeTerm / gcd.GetGCD ();

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

		int GetFPSolution () {return fPSolution;}

		int GetSPSoultion () {return sPSolution;}

		int GetFGSCoeff () {return fGSCoeff;}

		int GetSGSCoeff () {return sGSCoeff;}


	};
}

#endif