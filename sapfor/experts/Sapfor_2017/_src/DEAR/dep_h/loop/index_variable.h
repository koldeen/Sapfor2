/************************************************************************************************	
 *	Класс IndexVariable отвечает за описание индекснвых переменных,								*
 *	используемых в циклах анализируемой программы.												*
 *																								*
 *	Данный класс предоставляет следующий интерфейс:												*
 *		- int GetId () - возвращает идентификатор соответствующий переменной;					*
 *		- int GetLoopId () - возвращает идентификатор цикла,									*
 *		которому непосредственно принадлежит индексная переменная;								*	
 *		- IExpression* GetLeftBound () - возвращает левую границу изменения переменной,			*
 *		если граница неизвестна, возвращается NULL;												*
 *		- IExpression* GetRightBound () - возвращает правую границу изменения переменной;		*
 *		если граница неизвестна, возвращается NULL;												*				
 *		- IExpression* GetStep () - возвращает шаге изменения переменной,						*
 *		если шаг не известен, возвращается NULL.												*
 *		- IndexVariable* Clone () - обеспечивает глубокой копирование объекта класса			*
 *		на основе функций копирования, предоставляемых членами класса.							*
 *		- bool operator== (IndexVariable&) - осуществляет сравнение двух индексных переменных.	*
 ************************************************************************************************/
#ifndef INDEX_VARIABLE_H
#define INDEX_VARIABLE_H

#include "macros.h"
#include "isg_expression.h"

namespace Analyzer
{
	namespace Loop
	{
		class IndexVariable 
		{
			int id;				//идентификатор соответствующей записи в таблице vars базы данных
			int loopId;			//идентификатор цикла в таблице loops
			IExpression* left;	//левая граница диапазона изменения переменной
			IExpression* right;	//правая граница диапазона изменения переменной
			IExpression* step;	//шаг изменения переменной
		public:
			IndexVariable (int id, int loopId, IExpression* left,  IExpression* right, IExpression* step, bool notClone = false)
			{			
				this->id = id;
				this->loopId = loopId;
				
				if (notClone)
				{
					this->left = left;
					this->right = right;
					this->step = step;
				}
				else
				{
					if (!left) this->left = NULL;
					else this->left = left->Clone();

					if (!right) this->right = NULL;
					else this->right = right->Clone();

					if (!step) this->step = NULL;
					else this->step = step->Clone();
				}
			}

			~IndexVariable ()
			{		
				DELETE_POINTER (left)
				DELETE_POINTER (right)
				DELETE_POINTER (step)
			}

			IndexVariable* Clone ()
			{
				return new IndexVariable (id, loopId, left, right, step);
			}
				
			IExpression* GetLeftBound () {return left;}

			void SetLeftBound (IExpression* left, bool notClone = false)
			{
				DELETE_POINTER (this->left)

				if (!left || notClone)
				{
					this->left = left;
				}
				else this->left = left->Clone();

			}

			IExpression* GetRightBound() {return right;}

			void SetRightBound (IExpression* right, bool notClone = false)
			{
				DELETE_POINTER (this->right)

				if (!right || notClone)
				{
					this->right = right;
				}
				else this->right = right->Clone();

			}

			IExpression* GetStep() {return step;}

			void SetStep (IExpression* step, bool notClone = false)
			{
				DELETE_POINTER (this->step)

				if (!step || notClone)
				{
					this->step = step;
				}
				else this->step = step->Clone();

			}

			int GetId () {return id;}

			int GetLoopId () {return loopId;}

			bool operator== (IndexVariable& iVar) 
			{
				if (this->id == iVar.id && this->loopId == iVar.loopId) return true;
				return false;
			}
		};
	}
}


#endif