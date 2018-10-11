/********************************************************************************
 *	Класс ScalarUsage уточняет порядок использования памяти в случае скаляров.	*
 ********************************************************************************/
#ifndef MU_SCALAR_USAGE_H
#define MU_SCALAR_USAGE_H

#include "mu_usage.h"

namespace Analyzer
{
	namespace Memory
	{
		class ScalarUsage : public MemoryUnitUsage
		{
		public:
			ScalarUsage (UsageType usageType) : MemoryUnitUsage (usageType) {}
			MemoryUnitUsage* Clone () 
			{
				ScalarUsage *temp = new ScalarUsage (usageType);				
				if (nextUsage) temp->AddNextUsage (nextUsage->Clone ());

				return temp;
			}

			bool operator== (MemoryUnitUsage& muu)
			{
				if (typeid (muu) != typeid (ScalarUsage)) return false;

				return MemoryUnitUsage :: operator== (muu);
			}
		};
	}
}

#endif