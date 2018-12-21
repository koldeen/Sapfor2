#include "../dep_h/mu/memory_unit.h"
#include "../dep_h/mu/mu_usage.h"

namespace Analyzer
{
	namespace Memory
	{
		MemoryUnit :: ~MemoryUnit ()
		{
			DELETE_ARRAY (varsId)
			
			currentUsage = NULL;

			DELETE_POINTER (firstUsage)
		}

		MemoryUnitUsage* MemoryUnit :: AddUsage (MemoryUnitUsage* newUsage, bool notClone)
		{
			CHECK_NULL_POINTER (newUsage)
			
			MemoryUnitUsage* temp;
			if (notClone) temp = newUsage;
			else temp = newUsage->Clone ();

			if (!firstUsage) firstUsage = temp;				
			else currentUsage->AddNextUsage (temp);
			currentUsage = temp;

			return currentUsage;
		}	

		MemoryUnitUsage* MemoryUnit :: GetLastUsage ()
		{
			if (!currentUsage) return NULL;
			
			MemoryUnitUsage* lastUsage = currentUsage;
			while (lastUsage->GetNextUsage ())
			{
				lastUsage = lastUsage->GetNextUsage ();
			}

			return lastUsage;
		}
	}
}