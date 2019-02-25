/****************************************************************************************************
 *	Класс ICollection в пространстве имен Collection является абстрактным классом,					*
 *	описывающим интерфейса работы с различного рода коллекциями, созданными на его основе. 			*
 *																									*					
 *	Текущее количесвто элементов в коллекции описывается защищенным членом size,					*
 *	член allocatedSize описывает сколько элементов может быть добавлено в коллекцию					*
 *	без дополнительного выделения памяти.															*
 *																									*
 *	Унаследованным классам предоставляются следующие защищенные функции:							*
 *		- CheckIndexRangeEx (int index) - проверяет, что index лежит в диапазоне [0, size),			*
 *		в случае не выполнения условия выбрасывается исключение IndexOutOfRangeException.			*
 *		- CheckCollectionCapacityEx () - провряет, что статическая коллекция еще не заполнена,		*
 *		в случае невыполнения условия выбрасывается исключение CollectionIsFullException			*
 *		- СheckCollectionapacityEx (int requiredSize) - проверяет, что в статической коллекции		*
 *		свободного пространства не меньше чем requiredSize, в случае невыполнения условия			*
 *		выбрасывается исключение CollectionIsFullException.											*
 *		- аналогичные функции, но без суффикса Ex, возвращают false вместо генерации исключения.	*
 *																									*
 *	Открытые методы класса ICollection:																*
 *		- ICollection () - конструктор создает динамическую коллекцию.								*
 *		- ICollection (int maxSize) - конструктор создает статическую коллекцию размера maxSize.	*
 *		- int GetAllocatedSize () - возвращает число элементов,										*
 *		под которые выдеkена память в динамической коллекции.										*
 *		- int GetSize () - возвращает число элементов в коллекции.									*
 *		- ICollection* Clone () - осуществляет глубокое копирование объекта.						*
 *		- int Add (Element) - добавление одного элемента в коллекцию,								*
 *		возвращает ключ, по которому он может быть найден;											*
 *		если ничего не было добавлено, то возвращается NOTHING_ADD;									*
 *		если ключ не предусмотрен, то возвращается KEY_NOT_DEFINED.									*
 *		- int AddRange (Element[], int) - добавление массива элементов,	заданного размера;			*
 *		возвращает ключ первого элемента массива;													*
 *		если ничего не было добавлено, то возвращается NOTHING_ADD;									*
 *		если ключ не предусмотрен, то возвращается KEY_NOT_DEFINED.									*
 *		- Element Update (int, Element) - заменяет элемент с заданным ключем, на заданный,			*
 *		возвращает старое значение элемента.														*
 *		- Delete (int) - удаляет элемент с заданным ключем из коллекции.							*
 *		- Delete (Element) - удаляет заданный элемент или все элементы								*
 *		(в зависимости от реализации) из коллекции.													*
 *		- int Find (Element) - ищет некоторое вхождение элемента в коллекцию;						* 
 *		если ключ не предусмотрен, то возвращается KEY_NOT_DEFINED;									*
 *		ecли элемент не найден, то возвращается ELEMENT_NOT_FOUND.									*
 *		- bool Exists (Element) - ищет некоторое вхождение элемента в коллекцию.					*
 *		- Element operator [int] - оператор доступа по ключу.										*
 *		- Element operator [Element] - оператор доступа по элементу.								*
 *		- bool operator== (ICollection&) - оператор сравнения двух коллекций,						*
 *		по умолчанию сравниваются адреса.															*
 *		- bool operator!= (ICollection&) - оператор сравнения двух коллекций,						*
 *		по умолчанию сравниваются адреса.															*
 ****************************************************************************************************/
#ifndef COLLECTION_H
#define COLLECTION_H

#include "collection_exception.h"

#define NOTHING_ADD -1
#define KEY_NOT_DEFINED -2
#define ELEMENT_NOT_FOUND -3

namespace Collection
{	
	template <class Element> class ICollection
	{		
	protected:		
		int allocatedSize;
		int size;

		void CheckIndexRangeEx (int index)
		{
			if (index < 0 || index >= size) throw Exception :: IndexOutOfRangeException (0, size, index);
		}

		void CheckCollectionCapacityEx ()
		{
			if (size >= allocatedSize) throw Exception :: CollectionIsFullException (allocatedSize);
		}
		
		bool CheckCollectionCapacity ()
		{
			if (size >= allocatedSize) return false;
			return true;
		}

		void CheckCollectionCapacityEx (int requiredSize)
		{
			if (allocatedSize - size < requiredSize) throw Exception :: CollectionIsFullException (allocatedSize);
		}

		bool CheckCollectionCapacity (int requiredSize)
		{
			if (allocatedSize - size < requiredSize) return false;
			return true;
		}
		
	public:
		ICollection ()
		{			
			this->allocatedSize = 0;
			this->size = 0;
		}

		ICollection (int collSize)
		{
			if (collSize < 0) throw Exception :: NegativeMaxSizeException (collSize);			
			this->size = 0;
			this->allocatedSize	= collSize;
		}		
		
		int GetAllocatedSize () {return allocatedSize;}
		int GetSize () {return size;}

		virtual ICollection* Clone () = 0;

		virtual int Add (Element) = 0;
		virtual int AddRange (Element*, int) = 0;

		virtual Element Update (int, Element) = 0;

		virtual void Delete (int) = 0;
		virtual void Delete (Element) = 0;

		virtual int Find (Element) = 0;
		virtual bool Exists (Element elem) {return Find (elem) != ELEMENT_NOT_FOUND;}

		virtual Element operator [] (int) = 0;
		virtual Element operator [] (Element) = 0;		

		virtual bool operator== (ICollection& coll) {return this == &coll;}
		virtual bool operator!= (ICollection& coll) {return this != &coll;}
	};
}


#endif