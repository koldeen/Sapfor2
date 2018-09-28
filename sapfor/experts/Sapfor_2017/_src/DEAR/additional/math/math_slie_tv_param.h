/************************************************************************************
 *	Данный класс находит целочисленное значения параметра R при котором система:	*
 *	y1 = u1 + v1 * t																*
 *	y2 = u2 + v2 * t																*
 *	y1 ! = y2																		*
 *	0 <= y1 <= R																	*
 *	0 <= y2 <= R																	*
 *	c целыми коэффициентами имеет целочисленное решение.							*
 ************************************************************************************/
#ifndef MATH_SLIE_TV_PARAMEMTER_H
#define MATH_SLIE_TV_PARAMEMTER_H

#include "math_functions.h"
#include "main_exception.h"
#include <cmath>

namespace Mathematics
{
	//system of linear inequality with two variable and parameter
	class SLIneqTVParameter
	{
		int u1, v1;
		int u2, v2;
		int yMin;
		bool isSolutionExist;		

		int tL1, tR1; //ближайшие целые слева и справа от пересечения y1 и 0 соответственно
		int tL2, tR2; //ближайшие целые слева и справа от пересечения y2 и 0 соответственно
		int tLInt, tRInt;	//tInt = (u1 - u2) / (v2 - v1) - точка пересечения прямых y1 и y2
							//если они пересекаются
							//tLInt, tRInt - ближайшие целые слева и справа от tLInt соответственно

		//v1 == v2 - прямые y1 и y2 параллельны
		void IfParallel () 
		{
			if (v1 > 0) 
				if (u1 > u2) 	
					yMin = MathFunctions :: LinearFunction2 (u1, v1, tR2); 
				else 
					yMin = MathFunctions :: LinearFunction2 (u2, v2, tR1); 
			else 
				if (u1 > u2)
					yMin = MathFunctions :: LinearFunction2 (u1, v1, tL2); 						
				else				
					yMin = MathFunctions :: LinearFunction2 (u2, v2, tL1);
			}
		//0 < v1 < v2 - обе прямые образуют острый угол с оью Ox
		void IfAcuteAngleOx ()
		{	
			int tMin;
			if (tR2 == tRInt && tLInt == tRInt && 
				(tL2 == tR2 || tR1 <= tLInt))
				yMin = MathFunctions :: LinearFunction2 (u1, v1, tR2 + 1); //либо а.2, либо б
			else if (tL1 > tRInt || 
					 tL1 == tRInt ||
					 tL1 == tLInt && tLInt == tRInt ||
					 tL1 == tLInt && tL1 != tR1 && tL2 != tL1)
				yMin = MathFunctions :: LinearFunction2 (u2, v2, tR1); //в)
			else
				yMin = MathFunctions :: LinearFunction2 (u1, v1, tR2); //a.1)			
		}

		//v1 < v2 < 0 - обе прямые образуют тупой угол с оью Ox	
		void IfObtuseAngleOx ()
		{
			int tMin;
			if (tLInt == tRInt && tL1 == tLInt &&
				(tR1 == tL1 || tL2 >= tRInt))
				 MathFunctions :: LinearFunction2 (u2, v2, tL1 + 1); //либо а.2, либо б
			else if (tL1 > tRInt || 
					 tR2 == tLInt ||
					 tR2 == tRInt && tRInt == tLInt ||
					 tR2 == tRInt && tR2 != tL2 && tR1 != tR2)
				 MathFunctions :: LinearFunction2 (u1, v1, tL2);
			else
				 MathFunctions :: LinearFunction2 (u2, v2, tL1);					
		}

		//v1 < 0 < v2 - прямые образуют тупой и острый углы с осью Ox
		void IfDiffAngleOx ()
		{
			if (0 > min (MathFunctions :: LinearFunction2 (u1, v1, tLInt), 
						 MathFunctions :: LinearFunction2 (u2, v2, tRInt)) ||
				0 == MathFunctions :: LinearFunction2 (u1, v1, tRInt)) //б)
				isSolutionExist = false;
			else if (tL1 == tR2 && tL2 == tR1) //в)
				yMin = min (MathFunctions :: LinearFunction2 (u1, v1, tLInt - 1), 
							MathFunctions :: LinearFunction2 (u1, v1, tRInt + 1));
			else 
			{
				if (tL2 == tL1 ||
					tLInt == tRInt && tR2 == tL1 && tR2 == tLInt)
					isSolutionExist = false;
				else if (tLInt == tRInt)
				{
					if (tR2 == tLInt)
						yMin = MathFunctions :: LinearFunction2 (u1, v1, tRInt + 1);
					else if (tL1 == tRInt)
						yMin = MathFunctions :: LinearFunction2 (u1, v1, tLInt - 1);
					else
						yMin = min (MathFunctions :: LinearFunction2 (u1, v1, tLInt - 1), 
									MathFunctions :: LinearFunction2 (u1, v1, tRInt + 1));
				}
				else 
					yMin = min (MathFunctions :: LinearFunction2 (u1, v1, tLInt), 
								MathFunctions :: LinearFunction2 (u1, v1, tRInt));
			}
		}

		void Solve ()
		{
			tL1 = MathFunctions :: LeftIntegerPart (- u1, v1); 
			tR1 = MathFunctions :: RightIntegerPart (- u1, v1); 
				
			tL2 = MathFunctions :: LeftIntegerPart (- u2, v2); 
			tR2 = MathFunctions :: RightIntegerPart (- u2, v2); 

			if (v1 == v2)
				IfParallel ();	
			else
			{
				if (v1 > v2)
				{	//меняем функции местами, чтобы v1 <= v2					
					int temp;
					temp = u1;
					u1 = u2; 
					u2 = temp;

					temp = v1;					
					v1 = v2;					
					v2 = temp;
				}
				//возможны случаи: 
				//1. v1 > 0, тогда v2 > 0
				//2. v2 < 0, тогда v1 < 0
				//3. v1 < 0 < v2

				tLInt = MathFunctions :: LeftIntegerPart (u1 - u2, v2 - v1);	
				tRInt = MathFunctions :: LeftIntegerPart (u1 - u2, v2 - v1);
				if (v1 > 0) 
					 IfAcuteAngleOx ();
				else if (v2 < 0) IfObtuseAngleOx ();
				else IfDiffAngleOx ();
			}
		}

	public:
		SLIneqTVParameter (int u1, int v1, int u2, int v2)
		{
			if (v1 == 0 || v2 == 0) throw :: Exception :: IException ("division by zero");
			this->u1 = u1;
			this->v1 = v1;
			this->u2 = u2;
			this->v2 = v2;
			
			Solve ();
		}		
		
		int GetYMin () {return yMin;}

		bool IsSolutionExist () {return isSolutionExist;}
	};
}

#endif