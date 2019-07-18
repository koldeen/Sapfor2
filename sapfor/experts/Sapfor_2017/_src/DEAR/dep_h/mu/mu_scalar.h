/********************************************************************************	
 *	Класс ScalarUnit из пространства имен MemoryUnit							*
 *	уточняет информацию по используемой памяти в случае скалярных переменных.	*	
 ********************************************************************************/
#ifndef MEMORY_UNIT_SCALAR_H
#define MEMORY_UNIT_SCALAR_H

#include "memory_unit.h"

namespace Analyzer
{
	namespace Memory
	{
		class ScalarUnit: public MemoryUnit
		{
		public:
			ScalarUnit (int varId) : MemoryUnit (varId) {}
			
			ScalarUnit (int* varsId, int varsNum) : MemoryUnit (varsId, varsNum) {}
			
			MemoryUnit* Clone () 
			{
				ScalarUnit* clone = new ScalarUnit (varsId, varsNum);
				
				CLONE_MU (clone)

				return clone;				
			}
			
			bool IsScalar () {return true;}			

			bool operator== (MemoryUnit& mu)
			{
				//if (typeid (mu) != typeid (ScalarUnit)) return false;

				return MemoryUnit::operator == (mu);				
			}
		};
	}
}
#endif