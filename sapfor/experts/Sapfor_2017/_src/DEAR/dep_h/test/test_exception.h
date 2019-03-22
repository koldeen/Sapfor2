#ifndef TEST_EXCEPTION_H
#define TEST_EXCEPTION_H

#include "exception.h"

namespace Analyzer
{
	namespace Test
	{
		namespace Exception
		{
			class TestException: public :: Exception :: IException
			{
			};
			
		}
	}
}

#endif