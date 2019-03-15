#ifndef TNL_REGION_USAGE_H
#define TNL_REGION_USAGE_H

#include "memory_unit.h"
#include "mu_usage.h"
#include "test_dep_info.h"
#include "macros.h"

using namespace Analyzer :: Memory;
using namespace Analyzer :: Test :: Dependences;

namespace Analyzer
{
	namespace Loop
	{
		class RegionUsage
		{
			MemoryUnit* mu;
			MemoryUnitUsage* firstUsage;
			MemoryUnitUsage* lastUsage;

			DepTestInfo* dTestInfo; 			
		public:
			RegionUsage (MemoryUnit *mu, int depsNumber)
			{
				CHECK_NULL_POINTER (mu)
				this->mu = mu;
				this->firstUsage = NULL;
				this->lastUsage = NULL;				
				this->dTestInfo = new DepTestInfo (depsNumber);
			}
			
			RegionUsage (MemoryUnit *mu)
			{
				CHECK_NULL_POINTER (mu)
				this->mu = mu;
				this->firstUsage = NULL;
				this->lastUsage = NULL;				
				this->dTestInfo = NULL;
			}

			~RegionUsage ()
			{
				mu = NULL;
				firstUsage = NULL;
				lastUsage = NULL;				
				
				DELETE_POINTER (dTestInfo)
			}

			RegionUsage* Clone () //добавить клонирование зависимостей
			{				
				RegionUsage* temp = new RegionUsage (mu, dTestInfo->GetLoopsNumber ());
				temp->SetFirstUsage (firstUsage);
				temp->SetLastUsage (lastUsage);
				
				return temp;
			}

			void SetFirstUsage (MemoryUnitUsage* firstUsage) 
			{
				CHECK_NULL_POINTER (firstUsage)
				this->firstUsage = firstUsage;
			}
			void SetLastUsage (MemoryUnitUsage* lastUsage) 
			{
				CHECK_NULL_POINTER (lastUsage)
				this->lastUsage = lastUsage;
			}	

			MemoryUnit* GetMemoryUnit () {return mu;}

			MemoryUnitUsage* GetFirstUsage () 
			{
				CHECK_NULL_POINTER (firstUsage)
				return firstUsage;
			}

			MemoryUnitUsage* GetLastUsage () 
			{
				CHECK_NULL_POINTER (lastUsage)
				return lastUsage;
			}
			
			DepTestInfo* GetDepTestInfo () {return dTestInfo;}			

			//RegionUsage существует исходя из того, что не может быть двух одниковых MemoryUnit, 
			//поэтому равенство возможно, только в случае равенства указателей.
			bool operator== (RegionUsage& ru)
			{
				return mu == (ru.mu) && firstUsage == (ru.firstUsage) && lastUsage == (ru.lastUsage);
			}
		};
	}
}
#endif