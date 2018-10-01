/********************************************************************************************************************
 *	В пространстве имен Expression описаны классы, отвечающие за различные способы представления выражений.			*		 
 *	Например: целое число, текстовая запись, посфиксная запись и др.												*
 *																													*
 *	В случае возникновения ошибки во время выполнения операций над данными классами									*
 *	будет выброшено одно из исключений, описанных в пространстве имен Expression :: Exception						*
 *																													*
 *	Особенности работы с классами пространства имен Expression.														*
 *	В целях за контроля выделяемой памятью для предотвращения ее утечки все объекты, создаваемые во время			*
 *	выполнения методов конкретного класса (кроме метода Clone()), помечаются как временные (temp == true).			*
 *	В момент вызова метода класса или функций друзей используемые объекты проверяются на наличие данной отметки.	*
 *	Если используемые объекты являются временными то выделенная под них память будет высвобождена.					*
 *																													*
 *	Рекомендуется в случае присвоения указателю адреса объекта или инициализации ссылки с помощью объекта,			*
 *	полученного в результате выполнения методов класса или функций друзей, использовать метод Clone(),				*
 *	чтобы данный указатель указывал на объект, помеченный как постоянный.											*
 ********************************************************************************************************************/
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

namespace Expression
{	
	class IExpression
	{
	private:
		bool temp;		//если объект определен как временный, значит вне текущего блока на него ничто не ссылается и он может быть удален без потерь
						//по умолчанию все объекты считаются постоянными
						//все объекты создаваемые внутри класса временные		
	public:					
		IExpression () : temp (false) {}
		IExpression (bool temp) : temp (temp) {}
		bool IsTemp () {return temp;}
		
		virtual IExpression* Clone () = 0;
		virtual std :: string ToString () = 0;			
		virtual IExpression& operator= (IExpression& expr) = 0;

		//дружественные функции (operators.cpp)
		//арифметические операторы
		friend IExpression& operator+ (IExpression& expr1, IExpression& expr2);
		friend IExpression& operator- (IExpression& expr1, IExpression& expr2);
		friend IExpression& operator* (IExpression& expr1, IExpression& expr2);
		friend IExpression& operator/ (IExpression& expr1, IExpression& expr2);

		//условные операторы
		friend bool operator== (IExpression& expr1, IExpression& expr2);
		friend bool operator!= (IExpression& expr1, IExpression& expr2);
		friend bool operator< (IExpression& expr1, IExpression& expr2);
		friend bool operator<= (IExpression& expr1, IExpression& expr2);
		friend bool operator> (IExpression& expr1, IExpression& expr2);
		friend bool operator>= (IExpression& expr1, IExpression& expr2);
	};
}

#endif