#include "../h/expr_language.h"

namespace Expression
{
	namespace Language
	{
		std :: string Lang :: error = "Error";
		std :: string Lang :: inExprOfType = "In expression of type";
		std :: string Lang :: inOperator = "In operator";
		std :: string Lang :: opNotDef = "Operation not defined";

		std :: string Lang :: GetError () {return error;}
		std :: string Lang :: GetInExprOfType () {return inExprOfType;}
		std :: string Lang :: GetInOperator () {return inOperator;}
		std :: string Lang :: GetOpNotDef () {return opNotDef;}

		void Lang :: Russion ()
		{
			error = "Ошибка";
			inExprOfType = "В выражении типа";
			inOperator = "В операторе";
			opNotDef = "Операция не определена";
		}

		void Lang :: English ()
		{
			error = "Error";
			inExprOfType = "In expression of type";
			inOperator = "In operator";
			opNotDef = "Operation not defined";
		}
	}
}
