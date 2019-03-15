/********************************************************************************************
 * Класс GCDTwoNumbers соответствует НОД двух чисел fn (first number), sn (second number).	*
 * Для вычисления НОД используется расширенный алгоритм Евклида:							*
 *			Входные данные: два целых числа fn, sn.											*
 *			Результат алгоритма:															*
 *								- НОД (fn, sn) - gcd > 0									*
 *								- два целых числа fnc, snc: fnc * fn + snc * sn = gcd		*
 ********************************************************************************************/
#ifndef MATH_GCD_TWO_NUMBER_H
#define MATH_GCD_TWO_NUMBER_H

#include <cmath>

namespace Mathematics
{
	class GCDTwoNumbers 
	{
	private:		
		int fn, sn; //числа, которым соответствует НОД
		int gcd, fnc, snc;	//fnc * fn + snc * sn = gcd
		
		void Calculate (int a, int b) //функция вычисления НОД для положительных чисел
		{
			if (b == 0) 
			{
				gcd =  a;
				fnc = 1;
				snc = 0;
			}
			else
			{
				int temp; 
				Calculate (b, a % b);
				temp = fnc;
				fnc = snc;
				snc = temp - a / b * snc;
			}			
		}

		void Calculate () //функция вычисления НОД в общем случае
		{
			Calculate (abs (fn), abs (sn));	
			if (fn < 0) fnc = - fnc;
			if (sn < 0) snc = - snc;
		}
	public:
		GCDTwoNumbers (int fn, int sn)
		{
			this->fn = fn;
			this->sn = sn;
			Calculate ();				
		}
		
		int GetGCD () {return gcd;}	//возвращает НОД
		int GetFirstNumber () {return fn; }     //возвращает первое число
		int GetSecondNumber () {return sn; }		//возвращает второе число
		int GetFNCoeff () {return fnc;}	//возвращает коэффициент при первом числе
		int GetSNCoeff () {return snc;}	//возвращает коэффициент при втором числе
	};
}

#endif