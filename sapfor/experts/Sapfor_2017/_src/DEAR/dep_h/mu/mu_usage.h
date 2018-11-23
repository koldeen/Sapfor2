/****************************************************************************************************************
 *	Абстрактный класс MemoryUnitUsage содержит общую информацию об использовании некоторой области памяти.		*
 *	Данный класс является базовым, более детальное описание возможно через базовые классы.						*	
 *	Класс MemoruUnitUsage предоставляет информацию:																*
 *		- о типе использования (перечислимый тип UsageType);													*
 *		- о cледующем использовании.																			*
 *																												*
 *	Интерфейс, предоставляемый классом:																			*
 *		- MemoryUnitUsage (UsageType usageType) - конструктор новой точки использования,						*
 *		с типом использования usageType.																		*
 *		- MemoryUnitUsage* Clone () - осуществляет глубокое копирование объекта.								*
 *		- UsageType GetUsageType () - возвращает тип использования области памяти.								*
 *		- MemoryUnitUsage* GetNextUsage () - возвращает указатель на следующую точку использования.				*
 *		- bool operator== (MemoryUnitUsage& muu) - сравнивает два списка использования, начинающиеся с this.	*
 ****************************************************************************************************************/
#ifndef MEMORY_UNIT_USAGE_H
#define MEMORY_UNIT_USAGE_H

#include "memory_unit.h"
#include "macros.h"

namespace Analyzer
{	
	namespace Memory
	{
		enum UsageType 
		{
			INVALID_TYPE = 0,
			FIRST_TYPE = 1, 
			NOT_USAGE = 1,
			READ = 2, 
			UNKNOWN = 3, 
			WRITE = 4, 
			LAST_TYPE = 4
		};	
		
		class MemoryUnitUsage
		{
		protected:
			UsageType usageType;			
			MemoryUnitUsage* nextUsage;		
					
			void AddNextUsage (MemoryUnitUsage* newUsage)
			{				
				CHECK_NULL_POINTER (newUsage)			
				
				if (nextUsage) newUsage->AddNextUsage (nextUsage);
				nextUsage = newUsage;					
			}

			friend MemoryUnitUsage* MemoryUnit :: AddUsage (MemoryUnitUsage*, bool);
		public:		
			MemoryUnitUsage (UsageType usageType) 
			{				
				this->usageType = usageType;
				this->nextUsage = NULL;					
			}

			~MemoryUnitUsage ()
			{					
				DELETE_POINTER (nextUsage)				
			}

			virtual MemoryUnitUsage* Clone () = 0;				

			UsageType GetUsageType () {return usageType;}

			void SetUsageType (UsageType usageType) {this->usageType = usageType;}

			MemoryUnitUsage* GetNextUsage () {return nextUsage;}	

			virtual bool operator== (MemoryUnitUsage& muu)
			{
				if (this == &muu) return true;

				if (usageType != muu.usageType) return false;
				if (nextUsage == muu.nextUsage) return true; //если ссылка на одну и ту же область памяти или оба NULL, то равны
				return *nextUsage == *muu.nextUsage;
			}

			virtual bool operator!= (MemoryUnitUsage& muu)
			{
				return !(*this == muu);
			}
		};		
	}
}
#endif