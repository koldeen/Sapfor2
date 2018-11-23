/********************************************************************************************************	
 *	Класс DepTestInfo содержит описание зависимости,													*
 *	а также информацию используемую тестами в процессе тестирования.									*
 *	Считается, что в каждый момент времени предоставляемое описание зависимости является корректным.	*
 *	В начальный момент времени считается, что зависимость возможно существует.							*
 *																										*
 *	Предоставляемый интерфейс:																			*
 *		- Dependence* GetDependence () - предоставляет информацию о зависимости.						*
 *		- void SetExistence (bool isExists) - позволяет задать существование.							*		
 *		- void SetExactness (bool isExactly) - позволяет задать точность.								*
 *		- void SetCondition (Condition* cond) - позволяет задать условие существование (отсутствия)		*
 *		зависимости. Глубокое копирование условия не осуществляется.									*
 *		- bool GetIsTested () - позволяет узнать: завршено ли тестирование.								*
 *		Если true, то тестирование выполнено полностью и ничего больше сказать нельзя.					*
 *		Если false, то либо не тестировали, либо ответ не точный.										*
 *		- void SetIsTested () - указывает, что тестирование завершено.									*
 *																										*
 *	Необходим контроль выделения памяти, так как возможно дублирование указателей без дублирования		*
 *	памяти. Это повлечет повторное удаление (одинаковые Dependence внутри гнезда).						*
 ********************************************************************************************************/
#ifndef TEST_DEPENDENCE_INFO_H
#define TEST_DEPENDENCE_INFO_H

#include "macros.h"
#include "mu_usage.h"

#include "test_dependence.h"
#include "test_info.h"


using namespace Analyzer :: Memory;

namespace Analyzer
{
	namespace Test
	{		
		namespace Dependences
		{
			class DepTestInfo
			{			
				Dependence** dep;			//зависимости по циклам из гнезда
				int loopsNumber;

				bool isTested;	
				MemoryUnitUsage* sTRegion; //начало и 
				MemoryUnitUsage* eTRegion; //конец протестированной области

				TestInfo* tInfo;

				UsageType uType;

			public:
				DepTestInfo (int loopsNumber)
				{
					this->loopsNumber = loopsNumber;
					NEW_POINTER_ARRAY (dep, loopsNumber, Dependence); //по умолчанию все зависимости возможно существуют
					for (int loop = 0; loop < loopsNumber; loop++)
						dep [loop] = new Dependence ();

					isTested = false;
					sTRegion = NULL;
					eTRegion = NULL;
					uType = UNKNOWN;
					tInfo = NULL;
				}		
				
				~DepTestInfo ()
				{
					sTRegion = NULL;
					eTRegion = NULL;
					
					DELETE_POINTER_ARRAY (dep, loopsNumber)
					DELETE_POINTER (tInfo)
				}

//*************************** Dependence overview **********************************
				IDependence* GetDependence (int loop) 
				{
					CHECK_INDEX_RANGE (loop, 0, loopsNumber)
					return (IDependence*)dep [loop];
				}							

				void SetDependence (int loop, Dependence* dep, bool notClone = false)
				{					
					CHECK_INDEX_RANGE (loop, 0, loopsNumber)

					if (notClone)
					{
						DELETE_POINTER (this->dep [loop])
						this->dep [loop] = dep;
					}
					else
					{
						*this->dep [loop] = *dep;
					}
				}

				void SetExistenceCond (int loop, Existence isExists, Condition* cond, Exactness isExactly)
				{
					CHECK_INDEX_RANGE (loop, 0, loopsNumber)

					dep [loop]->SetExistenceCond (isExists, cond, isExactly);
				}		

				int GetLoopsNumber () {return loopsNumber;}
				
//**********************************************************************************

				bool GetIsTested () {return isTested;}

				void SetIsTested () {isTested = true;}

				MemoryUnitUsage* GetStartTestedRegion () {return sTRegion;}
				void SetStartTestedRegion (MemoryUnitUsage* sTRegion) {this->sTRegion = sTRegion;}

				MemoryUnitUsage* GetEndTestedRegion () {return eTRegion;}
				void SetEndTestedRegion (MemoryUnitUsage* eTRegion) {this->eTRegion = eTRegion;}

				UsageType GetUsageType ()
				{
					return uType;
				}

				void SetUsageType (UsageType uType)
				{
					this->uType = uType;
				}

				void AddTestInfo (TestInfo* tInfo)
				{
					this->tInfo = tInfo;
				}

				TestInfo* GetTestInfo (int testId)
				{
					return tInfo;
				}

			};	
		}
	}
}

#endif