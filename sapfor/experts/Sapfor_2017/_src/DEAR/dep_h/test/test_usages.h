/********************************************************************************************************************
 *	Данный класс является базовым для тестов, работающиз с отдельными измерениями массивов							*
 *	на уровне отдельных использований.																				*
 *	Считается, что prevAUsage предшествует postAUsage в последовательности обращений к области памяти.				*
 *																													*
 *	Предоставляемый интерфейс:																						*
 *		- ArrayUsage* GetPrevAUsage () - возвращает, первое из пары анализируемых использований.					*
 *		- void SetPrevAUsage (ArrayUsage* prevAUsage) - задает, первое из пары анализируемых использований.			*
 *		- ArrayUsage* GetPostAUsage () - возвращает, второе из пары анализируемых использований.					*
 *		- void SetPostAUsage (ArrayUsage* prevAUsage) - задает, второе из пары анализируемых использований.			*
 *		- int GetDimension () - возвращает тестируемое измерение (по умолчанию - TEST_DIM_NOT_SET)					*
 *		- void SetDimension (int dim) - устанавливает тестируемое измерение.										*
 *		- IDependence* GetDependence () - возвращает описание зависимости. 											*
 ********************************************************************************************************************/
#ifndef TEST_USAGES_H
#define TEST_USAGES_H

#include "test.h"
#include "test_dependence.h"
#include "mu_usage.h"

#define TEST_DIM_NOT_SET -1

using namespace Analyzer :: Test :: Dependences;

namespace Analyzer
{
	namespace Test
	{
		class IEPairArrayTest: public ITest
		{
		protected:
			ArrayUsage* prevAUsage;
			ArrayUsage* postAUsage;
			int dim;

			Dependence** dep;
			int loopsNumber;

			IEPairArrayTest (TestIdentifier testId) : ITest (testId)
			{
				dim = TEST_DIM_NOT_SET;
				prevAUsage = NULL;
				postAUsage = NULL;
				
				dep = NULL;
				loopsNumber = 0;
			}

		public:

			~IEPairArrayTest ()
			{
				prevAUsage = NULL;
				postAUsage = NULL;

				DELETE_POINTER_ARRAY (dep, loopsNumber)
			}

			ArrayUsage* GetPrevAUsage () {return prevAUsage;}

			void SetPrevAUsage(ArrayUsage* prevAUsage) 
			{			
				this->prevAUsage = prevAUsage;
			}

			ArrayUsage* GetPostAUsage () {return postAUsage;}

			void SetPostAUsage(ArrayUsage* postAUsage) 
			{				
				this->postAUsage = postAUsage;
			}

			int GetDimension() {return dim;}

			void SetDimension (int dim) 
			{				
				this->dim = dim;
			}

			IDependence* GetDependence (int loopNumber) 
			{
				CHECK_INDEX_RANGE (loopNumber, 0, loopsNumber)
				return dep [loopNumber];
			}	

			virtual bool IsApplicable () 
			{
#if DEBUG & DBG_TEST_ARRAY
				cout << "IEPairArrayTest :: IsApplicable ()" << endl;
#endif 
				CHECK_NULL_POINTER (prevAUsage)
				CHECK_NULL_POINTER (postAUsage)
				
				CHECK_INDEX_RANGE (dim, 0, prevAUsage->GetIndexNumber ());
				CHECK_INDEX_RANGE (dim, 0, postAUsage->GetIndexNumber ());

				DELETE_POINTER_ARRAY (dep, loopsNumber)
				
				loopsNumber = pu->GetLoopsNumber ();
				NEW_POINTER_ARRAY (dep, loopsNumber, Dependence)

				return ITest :: IsApplicable ();
			}
			
			virtual TestResult Execute () 
			{
#if DEBUG & DBG_TEST_ARRAY
				cout << "IEPairArrayTest :: Execute ()" << endl;
#endif 
				ITest :: Execute ();

				CHECK_NULL_POINTER (prevAUsage)
				CHECK_NULL_POINTER (postAUsage)				
				CHECK_INDEX_RANGE (dim, 0, prevAUsage->GetIndexNumber ());
				CHECK_INDEX_RANGE (dim, 0, postAUsage->GetIndexNumber ());

				DELETE_POINTER_ARRAY (dep, loopsNumber)
				
				loopsNumber = pu->GetLoopsNumber ();
				NEW_POINTER_ARRAY (dep, loopsNumber, Dependence)
				
				return FAILURE;				
			}
		};
	}
}

#endif