#ifndef EX_NULL_POINTER
#define EX_NULL_POINTER

#include "exception.h"

namespace Exception
{
	class NullPointerException : public IException
	{
	public:
		NullPointerException () : IException ("Pointer is null.\n") {}
		NullPointerException (std::string msg) : IException (std::string("Pointer is null.\n") + msg) {}		
	};
}

#endif