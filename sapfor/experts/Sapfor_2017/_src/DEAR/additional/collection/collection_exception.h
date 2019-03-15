#ifndef COLLECTION_EXCEPTION_H
#define COLLECTION_EXCEPTION_H

#include "collection.h"
#include "exception.h"


namespace Collection
{
	namespace Exception
	{
		class CollectionException : public ::Exception::IException
		{
		};

		class OperationNotImplementException : public CollectionException
		{			
		};

		class CollectionIsFullException : public CollectionException
		{
			int maxSize;
		public:
			CollectionIsFullException (int maxSize)
			{
				this->maxSize = maxSize;
			}
		};

		class IndexOutOfRangeException : public CollectionException
		{
			int leftBound;
			int rightBound;
			int index;
		public:
			IndexOutOfRangeException (int lb, int rb, int index)
			{
				this->leftBound = lb;
				this->rightBound = rb;
				this->index = index;
			}
		};

		class NegativeMaxSizeException : public CollectionException
		{
			int maxSize;
		public:
			NegativeMaxSizeException (int maxSize)
			{
				this->maxSize = maxSize;
			}
		};


	}
}

#endif