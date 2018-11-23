#ifndef TNL_EXCEPTION_H
#define TNL_EXCEPTION_H

#include "exception.h"
#include "string.h"

namespace Analyzer
{
	namespace Loop
	{
		namespace Exception
		{
			class TNLoopsException : public ::Exception::IException
			{
			public: 
				TNLoopsException (std::string msg) : ::Exception::IException(msg) {}
			};
		}
	}
}

#endif