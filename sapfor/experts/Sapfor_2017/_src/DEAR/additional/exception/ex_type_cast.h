#ifndef EXCEPTION_TYPE_CAST_H
#define EXCEPTION_TYPE_CAST_H

#include "exception.h"
#include <cstring>

namespace Exception
{	
	class TypeCastException : public IException
	{
		:: std :: string fromType;
		:: std :: string toType;
	public:
		TypeCastException (:: std :: string type, :: std :: string toType)
		{
			this->fromType = fromType;
			this->toType = toType;
		}
		
		:: std :: string GetFromType () {return fromType;}
		:: std :: string GetToType () {return toType;}
		
	};
}


#endif