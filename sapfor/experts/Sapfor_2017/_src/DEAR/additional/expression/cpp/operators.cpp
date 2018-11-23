#include "exception.h"
#include "expr_exception.h"
#include "isg_expression.h"

int ExpCompare(SgExpression *e1, SgExpression *e2);
namespace Expression
{
	IExpression& operator+ (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		IExpression* expr = NULL;		

		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (!expr) throw Expression :: Exceptions :: OpNotDefException ('+', typeid (expr1).name());
		return *expr; 	
	}	
	IExpression& operator- (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		IExpression* expr = NULL;

		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (!expr) throw Expression :: Exceptions :: OpNotDefException ('-', typeid (expr1).name());
		return *expr; 	
	}
	IExpression& operator* (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		IExpression* expr = NULL;

		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (!expr) throw Expression :: Exceptions :: OpNotDefException ('*', typeid (expr1).name());
		return *expr; 	
	}

	IExpression& operator/ (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		IExpression* expr = NULL;

		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (!expr) throw Expression :: Exceptions :: OpNotDefException ('/', typeid (expr1).name());
		return *expr; 	
	}

	bool operator== (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		bool res;
		bool opNotDef = true;

		if (typeid (expr1) == typeid (Analyzer::ISgExpression&))
			if (typeid (expr2) == typeid (Analyzer::ISgExpression&))
			{
				opNotDef = false;
				res = (ExpCompare (((Analyzer::ISgExpression&)expr1).expr, ((Analyzer::ISgExpression&)expr2).expr) == 1); 
			}
				
		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (opNotDef) throw Expression :: Exceptions :: OpNotDefException ('==', typeid (expr1).name());
		return res; 	
	}	
	bool operator!= (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{	
		return (!(expr1 == expr2));
	}

	bool operator< (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		bool res = false;
		bool opNotDef = true;

		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (opNotDef) throw Expression :: Exceptions :: OpNotDefException ('<', typeid (expr1).name());
		return res; 	
	}	
	bool operator<= (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		bool res = false;
		bool opNotDef = true;

		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (opNotDef) throw Expression :: Exceptions :: OpNotDefException ('<=', typeid (expr1).name());
		return res; 	
	}	
	bool operator> (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		bool res = false;
		bool opNotDef = true;

		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (opNotDef) throw Expression :: Exceptions :: OpNotDefException ('>', typeid (expr1).name());
		return res; 	
	}	
	bool operator>= (IExpression& expr1, IExpression& expr2) throw (Expression :: Exceptions :: OpNotDefException)
	{		
		bool res = false;
		bool opNotDef = true;
		
		if (expr1.IsTemp()) delete &expr1;
		if (expr2.IsTemp()) delete &expr2;
		if (opNotDef) throw Expression :: Exceptions :: OpNotDefException ('>=', typeid (expr1).name());
		return res; 	
	}	
}