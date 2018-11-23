/****************************************************
 *	Базовый класс для исключений различного рода.	*
 ****************************************************/
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

namespace Exception
{
	class IException
	{
	protected:
		std :: string msg;
	public:
		IException () {}
		IException (std :: string msg) {this->msg = msg;}		
		virtual std :: string ToString () {return msg;}
	};
}

#endif