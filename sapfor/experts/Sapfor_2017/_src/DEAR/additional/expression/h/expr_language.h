#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>

namespace Expression
{
	namespace Language
	{
		class Lang
		{
		private:
			static std :: string error;
			static std :: string inExprOfType;
			static std :: string inOperator;
			static std :: string opNotDef;
			
		public:
			static std :: string GetError ();
			static std :: string GetInExprOfType ();
			static std :: string GetInOperator ();
			static std :: string GetOpNotDef ();

			static void Russion ();
			static void English ();
		};
	}
}

#endif