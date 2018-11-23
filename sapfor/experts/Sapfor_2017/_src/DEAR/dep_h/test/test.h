/****************************************************************************************************************
 *	Класс ITest является базовым для классов, описывающих применяемые тесты.									*
 *	Каждый тест направлен на определение наличия или отсутсвтия зависимости										*
 *	по заданной области памяти (MemoryUnit) в заданном гнезде (TightlyNestedLoops).								*
 *																												*
 *	Набор различных тестов представляет собой цепочку обязанностей.												*
 *	Если некоторый тест не справляется, то запрос на обработку передается следующему.							*
 *	Если ниодин тест не справился с поставленной задачей, то результат анализа на								*
 *	наличие зависимости по конкретной области памяти считается неизвестным.										*	
 *																												*
 *	Интерфейс, предоставляемый данным классом:																	*
 *		- ITest (ITest* nextTest)																				*	
 *		- int GetTestId () - возвращает идентификатор теста.													*		
 *		- TightlyNestedLoops* GetTNLoops () - возвращает тестируемое гнездо.									*
 *		- void SetTNLoops (TightlyNestedLoops* tNLoops) - задает тестируемое гнездо.							*
 *		- MemoryUnit* GetMUnit () - возвращает тестируемую область памяти.										*
 *		- void SetMUnit (MemoryUnit* mu) - задает тестируемую область памяти.									*
 *		- bool IsApplicable () - проверяет применимость теста для заданных гнезда и области памяти.				*
 *		- TestResult Execute () - запускает выполнение цепочки тестов над заданными гнездом и областью памяти.	* 
 ****************************************************************************************************************/
#ifndef TEST_H
#define TEST_H

#include "debug.h"
#include "program_unit.h"
#include "memory_unit.h"
#include "macros.h"

using namespace Analyzer :: Loop;
using namespace Analyzer :: Memory;

namespace Analyzer
{
	namespace Test
	{
		typedef int TestIdentifier;

		enum TestResult {NOT_APPLICABLE, SUCCESS, FAILURE};

		class ITest
		{			
		protected:
			TestIdentifier testId;
			ProgramUnit* pu;
			MemoryUnit* mu;							
		
			ITest (TestIdentifier testId)
			{			
				this->testId = testId;
				this->pu = NULL;
				this->mu = NULL;
			}

		public:

			~ITest ()
			{				
				pu = NULL;
				mu = NULL;
			}

			TestIdentifier GetTestId () {return testId;}

			ProgramUnit* GetPUnit () {return pu;}

			void SetPUnit (ProgramUnit* pu) { this->pu = pu;}

			MemoryUnit* GetMUnit () {return mu;}

			void SetMUnit (MemoryUnit* mu) {this->mu = mu;}			

			virtual bool IsApplicable () 
			{
#if DEBUG & DBG_TEST
				cout << "ITest :: IsApplicable ()" << endl;
#endif 

				CHECK_NULL_POINTER (pu)
				CHECK_NULL_POINTER (mu)

#if DEBUG & DBG_TEST
				cout << "tnl != NULL && mu != NULL" << endl;
#endif 

				return false;
			}
			
			virtual TestResult Execute () 
			{
#if DEBUG & DBG_TEST
				cout << "ITest :: Execute ()" << endl;
#endif 

				CHECK_NULL_POINTER (pu)
				CHECK_NULL_POINTER (mu)	

#if DEBUG & DBG_TEST
				cout << "tnl != NULL && mu != NULL" << endl;
#endif 

				return FAILURE;				
			}
		};
	}
}

#endif