/************************************************************************
 *	В файле описаны интерфейсы, предоставляемые для решения уравнений.	*
 *																		*
 *	Класс IEquation предоставляет базовый интерфейс						*
 *	для взаимодействия с системой уравнений.							*
 *																		*
 *	Класс ISyatemEquations предоставляет базовый интейрфейс				*
 *	для взаимодействия с системой уравнений.							*
 ************************************************************************/

#ifndef MATH_EQUATIONS_H
#define MATH_EQUATIONS_H

#include "object.h"

#define SOLVED true
#define NOT_SOLVED false

#define SOLUTION_EXIST true
#define SOLUTION_NOT_EXIST false

typedef bool SolutionExistence;
typedef bool SolvingStatus;
typedef int EquationNumber;

using namespace Object;

namespace Mathematics
{
	class IEquation : public IObject
	{
	public:		
		virtual void Solve () = 0;
		virtual SolutionExistence IsSolutionExist () = 0;
		virtual SolvingStatus IsSolved () = 0;
	};

	class ISystemEquations : public IObject
	{
	public:
		virtual void AddEquation (IEquation* equation, bool notClone = CLONE) = 0;
		virtual void Solve () = 0;
		virtual SolutionExistence IsSolutionExist () = 0;
		virtual SolvingStatus IsSolved () = 0;
		virtual EquationNumber GetEquationsNumber () = 0;
		virtual IEquation* GetEquation (EquationNumber equationNumber) = 0;
	};
}

#endif