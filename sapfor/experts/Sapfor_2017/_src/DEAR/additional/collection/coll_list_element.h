/********************************************************************************************************************
 *	 ласс ListElement €вл€етс€ вспомогательным классом, используемым дл€ реализации списков.						*
 *																													*
 *	ѕредоставл€емый интерфейс:																						*
 *		- ListElement (Value* val) - конструктор дл€ создани€ объекта, содержащего в качестве значени€ val			*
 *		- Value GetValue () - возвращает значение, соответствующий текущему (this) элементу.						*
 *		- Value SetTNLoops (Value val) - ставит в соответствие элементу значение val и	возвращает старое значение.	*
 *		- ListElement* SetNextValue (Value val) - добавл€ет в список после текущего (this) элемента,				*
 *		элемент, соответствующий val, возвращает указатель на элемент, ранее следующий за текущим.					*
 *		- ListElement* GetNext () - возвращает указатель на следующий элемент за текущим (this).					*
 *		- ListElement* SetNext (ListElement* lElem) - задает элемент, следующий за текущим (this),					*
 *		возвращает указатель на элемент, ранее следующий за текущим.												*
 ********************************************************************************************************************/

#ifndef COLLECTION_LIST_ELEMENT_H
#define COLLECTION_LIST_ELEMENT_H

#include "macros.h"

namespace Collection
{
	template <class Value> class  ListElement
	{
		Value val;
		ListElement* next;

		ListElement (Value val, ListElement *next)
		{
			this->val = val;
			this->next = next;
		}
	public:	
		ListElement (Value val)
		{
			this->val = val;
			this->next = NULL;
		}

		~ListElement ()
		{
			DELETE_POINTER (val)
			DELETE_POINTER (next)
		}

		Value GetValue () {return val;}

		Value SetValue (Value val) 
		{
			Value temp = this->val;
			this->val = val;

			return temp;
		}			

		ListElement* SetNextValue (Value val) 
		{
			this->next = new ListElement (val, this->next);
			return this->next;
		}

		ListElement* GetNext () {return next;}

		ListElement* SetNext (ListElement* lElem) 
		{				
			ListElement* res = this->next;
			this->next = lElem;

			return res;
		}
	};
}

#endif