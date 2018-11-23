/****************************************************************************************************
 *	Класс Dependence предоставляет данные по некоторой зависимости.									*
 *	Для каждой зависимости возможы следующие состояния:												*
 *		- точно есть;																				*
 *		- точно нет;																				*
 *		- ничего нельзя сказать;																	*
 *		- точно есть, если выполнено некоторое условие;												*
 *		- точно нет, если выполнено некоторое условие.												*
 *																									*
 *	Предоставляемый интерфейс:																		*
 *		- Dependence (bool isExists, bool isExactly) - конструктор, создащий описание зависимости.	*
 *		- bool IsExists () - указывает на существование (true) или отсутствие (false) зависимости.	*
 *		- bool IsExactly () - указывает на точность информации по зависимости. 						* 
 *		Услоивие в случае неточной зависимости устанавливается в NULL								*
 *		- Condition* GetCondition () - возвращает условие, уточняющее зависимость или NULL.			*
 ****************************************************************************************************/
#ifndef TEST_DEPENDENCE_H
#define TEST_DEPENDENCE_H

#include "test_dep_cond.h"

namespace Analyzer
{
	namespace Test
	{
		namespace Dependences
		{	
			class IDependence
			{
			public:
				virtual bool IsExists () = 0;
				virtual bool IsExactly () = 0;
				virtual Condition* GetCondition () = 0;
			};

			class Dependence : public IDependence
			{
				bool isExists;
				bool isExactly;
				Condition* сondition;

			public:
				Dependence (bool isExists, bool isExactly)
				{					
					this->isExists = isExists;
					this->isExactly = isExactly;
					this->сondition = NULL;
				}

				void SetExistence (bool isExists) {this->isExists = isExists;}
				
				void SetExactness (bool isExactly) 
				{
					this->isExactly = isExactly;
					if (!isExactly) DELETE_POINTER (сondition);
				}				

				void SetCondition (Condition* cond) 
				{
					DELETE_POINTER (сondition)
					this->сondition = cond;
				}		

				bool IsExists () {return isExists;}

				bool IsExactly () {return isExactly;}

				Condition* GetCondition () {return сondition;}
			};
		}
	}
}

#endif