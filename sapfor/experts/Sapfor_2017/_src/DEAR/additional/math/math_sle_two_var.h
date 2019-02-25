/****************************************************************************************	
 *	Данный класс предназначен для решений системы линейных уравнений					*
 *	с целыми коэффициентами в целых числах.												*
 *																						*
 *	Каждое уравнение системы зависяит от двух переменных: a_i * x_i + b_i * y_i = c_i.	*
 ****************************************************************************************/
#ifndef MATH_SLE_TWO_VARIABLE_H
#define MATH_SLE_TWO_VARIABLE_H

#include "math_le_two_var.h"
#include "macros.h"

#include "coll_list_element.h"
#include "collection_exception.h"
#include "main_exception.h"

typedef Collection :: ListElement<Mathematics :: LETwoVariable*> LETwoVariablesList;

namespace Mathematics
{	
	class SLETwoVariable : public ISystemEquations
	{
		LETwoVariablesList* firstLEElement;
		LETwoVariablesList* lastLEElement;
		
		int equationsNumber;

		SolvingStatus isSolved;
		SolutionExistence isSExist;
	public:

		SLETwoVariable ()
		{
			this->equationsNumber = 0;
			this->firstLEElement = NULL;
			this->lastLEElement = NULL;

			isSolved = NOT_SOLVED;
			isSExist = SOLUTION_EXIST;
		}

		~SLETwoVariable ()
		{
			DELETE_POINTER (firstLEElement);
			lastLEElement = NULL;
		}

		virtual void AddEquation (IEquation* equation, bool notClone = CLONE)
		{
			LETwoVariable* lEquation = dynamic_cast<LETwoVariable*> (equation);
			if (!lEquation) throw :: Exception :: TypeCastException ("IEquation", "LETwoVariable");

			if (!notClone) lEquation = (LETwoVariable*)lEquation->Clone ();

			if (!firstLEElement) 
				firstLEElement = lastLEElement = new LETwoVariablesList (lEquation);
			else 
				lastLEElement->SetNextValue (lEquation);
			equationsNumber++;	

			isSolved = SOLVED;
		}

		virtual void Solve () 
		{
			LETwoVariable* currEquation = firstLEElement->GetValue ();
			LETwoVariablesList* currSystem = firstLEElement;

			currEquation->Solve ();

			if (currEquation->IsSolutionExist () == SOLUTION_NOT_EXIST)
			{
				isSolved = SOLVED;
				isSExist = SOLUTION_NOT_EXIST;
				return;
			}			
			
			currSystem = currSystem->GetNext ();
			currSystem->GetValue ()

		}

		virtual SolutionExistence IsSolutionExist () = 0;

		virtual SolvingStatus IsSolved () {return isSolved;}

		virtual EquationNumber GetEquationsNumber () {return equationsNumber;}

		virtual IEquation* GetEquation (EquationNumber equationNumber) 
		{
			CHECK_INDEX_RANGE (equationNumber, 0, equationsNumber)

			LETwoVariablesList* equationElem = firstLEElement;

			for (int i = 0; i < equationNumber; i++)
			{
				equationElem = equationElem->GetNext ();
			}

			return equationElem->GetValue ();
		}		

	};
}


#endif