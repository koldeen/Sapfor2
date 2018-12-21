#ifndef MEMORY_UNIT_EXCEPTION_H
#define MEMORY_UNIT_EXCEPTION_H

#include "../../additional/exception/exception.h"

namespace Analyzer
{
	namespace Memory
	{
		namespace Exception
		{
			class MemoryUnitException : public ::Exception::IException
			{
			};

			class MUInternalSync : public MemoryUnitException
			{
			};
		}
	}
}

#endif
