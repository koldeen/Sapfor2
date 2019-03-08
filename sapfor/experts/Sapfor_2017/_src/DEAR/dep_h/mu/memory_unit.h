/****************************************************************************************************
 *	Структуры, описывающие использование памяти содержаться в пространстве имен Memory.				*
 *	Базовый класс MemoryUnit содержит общую информацию по используемой в программе памяти.			*
 *	Детализированное описание возможно через дочерние классы.										*
 *	Класс MemoryUnit предоставляет информацию:														*
 *		- об идентификаторах, относящихся к используемой области;									*
 *		- о порядке использования данной области.													*
 *																									* 
 *	Замечания (действительны для всего пространства имен Analyzer):									*
 *																									*
 *	1.	Если среди параметров функции присутствует параметр notClone, 								*
 *	то по умолчанию производится глубокое копирование объекта.										*
 *	Чтобы запретить данный вид копирования для повышения эффективности выполнения программы,		*
 *	возможно установить данный параметр notClone = true.											*
 *																									*
 *	2.	Если функция иницилизации или добавления (конструктор, Set..., Add...)						*
 *	принимающая в качестве параметра указатель на объект, имеет тип возвращаемого значения void,	*
 *	значит в процессе выполнения глубокое копирование не выполняется и								*
 *	в случае передачи в качестве параметра указателя,												*
 *	который может впоследствии стать недействительным, возможны ошибки времени выполнения.			*
 *																									*
 *	Интерфейс, предоставляемый классом:																*
 *		- MemoryUnit (int varId) - конструктор создающий объект, соответствующий одной переменной.	*
 *		- MemoryUnit (int* varsId, int varsNum) - конструктор создающий объект,						*
 *		описывающий область	памяти на которую ссылаются varsNum переменных.							*
 *		- int GetVarsId (int i = 0) - возвращает i - ую переменную соответствующую области памяти.	*
 *		- int GetVarsNumber () - возвращает число переменных соответствующих области памяит.		*
 *		- MemoryUnit* Clone () - осуществляет глубокое копирование объекта.							*
 *		- MemoryUnitUsage* AddUsage (MemoryUnitUsage* newUsage, bool notClone = false) -			*
 *		добавляет точку использования в список использований области памяти.						*
 *		- MemoryUnitUsage* GetFirstUsage () - указывает точку первого использования объекта.		*
 *		- MemoryUnitUsage* GetLastUsage () - указывает точку полседнего использования объекта.		*	
 *		- bool IsScalar () - указывает, соответствует область памяти скаляру или массиву.			*
 *		- operator == (MemoryUnit& mu) - сравнивает два объекта.									*
 ****************************************************************************************************/
#ifndef MEMORY_UNIT_H
#define MEMORY_UNIT_H

#include "stdlib.h"
#include "mu_exception.h"
#include "macros.h"

#define CLONE_MU(clone) \
{ \
	clone->firstUsage = firstUsage->Clone(); \
	\
	MemoryUnitUsage* temp = firstUsage; \
	clone->currentUsage = clone->firstUsage; \
	while (temp && temp != currentUsage) /*если firstUsage == NULL, то цикл выполнится 0 раз и currentUsage == NULL*/ \
	{ \
		temp = temp->GetNextUsage (); \
		clone->currentUsage = clone->currentUsage->GetNextUsage (); \
	} \
	\
	/*проверяем синхронизацию между currentUsage и firstUsage
	либо оба NULL, либо заданы корректно (currentUsage указывает на некоторое использование)*/ \
	if (!temp && firstUsage) throw new Analyzer :: Memory :: Exception :: MemoryUnitException (); \
}

namespace Analyzer
{
	namespace Memory
	{
		class MemoryUnitUsage;

		class MemoryUnit
		{
		protected:	
			int* varsId;		//переменные описывающие даную область: несколько в случае COMMON-блоков							
			int varsNum;		//число переменных ссылающихся на одну область памяти (размер varsId)		
			MemoryUnitUsage* firstUsage;
			MemoryUnitUsage* currentUsage;
		public:
			MemoryUnit (int varId) 
			{ 
				this->varsId = new int [1]; 
				this->varsId [0] = varId;
				this->varsNum = 1;
				this->firstUsage = NULL;
				this->currentUsage = NULL;
			}

			MemoryUnit (int* varsId, int varsNum) 
			{
				this->varsNum = varsNum;
				this->varsId = new int [this->varsNum];
				for (int i = 0; i < varsNum; i++) 
					this->varsId [i] = varsId [i];	
				this->firstUsage = NULL;
				this->currentUsage = NULL;
			}			

			~MemoryUnit (); 

			int GetVarsId (int i = 0) 
			{
				CHECK_INDEX_RANGE (i, 0, varsNum)

				return varsId [i];
			}

			int GetVarsNumber () {return varsNum;}
			
			virtual MemoryUnit* Clone () = 0;
			
			MemoryUnitUsage* AddUsage (MemoryUnitUsage* newUsage, bool notClone = false);
			
			MemoryUnitUsage* GetFirstUsage () {return firstUsage;}
			
			MemoryUnitUsage* GetLastUsage (); 			

			virtual bool IsScalar () = 0;

			virtual bool operator== (MemoryUnit& mu) 
			{
				if (this == &mu) return true;

				if (varsNum != mu.varsNum) return false;
				for (int i = 0; i < varsNum; i++)
					if (varsId [i] != mu.varsId [i]) return false;

				return firstUsage == mu.firstUsage;
			}
				
		};		
	}

}

#endif