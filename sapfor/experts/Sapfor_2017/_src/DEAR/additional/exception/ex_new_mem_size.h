#ifndef EX_NEW_MEMORY_SIZE_H
#define EX_NEW_MEMORY_SIZE_H

#include "exception.h"

#define MIN_NEW_MEMORY_SIZE 1

namespace Exception
{	
	class AllocatedMemorySizeException : public IException
	{
		int size;
	public:
		AllocatedMemorySizeException (int size)
		{
			this->size = size; 
		}

		int GetSize () {return size;}
	};
}


#endif