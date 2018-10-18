#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include "main_exception.h"

namespace Mathematics
{
	class MathFunctions
	{
	public:
		static int MathFunctions :: RightIntegerPart (int q, int p)
		{
			if (p == 0) throw :: Exception :: IException ("division by zero");
			if (q % p == 0 || q * p < 0) 
				return q / p;
			else return q / p + 1;
		}

		static int MathFunctions :: LeftIntegerPart (int q, int p)
		{
			if (p == 0) throw :: Exception :: IException ("division by zero");
			if (q % p == 0 || q * p > 0) 
				return q / p;
			else return q / p - 1;
		}	

		static int LinearFunction2 (int u, int v, int t)
		{
			return u + v * t;
		}
	};
}

#endif