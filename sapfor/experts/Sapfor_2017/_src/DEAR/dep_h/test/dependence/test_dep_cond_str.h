#ifndef TEST_DEP_STRING_CONDITION_H
#define TEST_DEP_STRING_CONDITION_H

#include "test_dep_cond.h"
#include "macros.h"
#include <string>

namespace Analyzer
{
	namespace Test
	{
		namespace Dependences
		{
			class StringCondition : public Condition
			{
				char* cond;				
			public:
				StringCondition (char* cond, bool notClone = false)
				{
					CHECK_NULL_POINTER (cond)

					if (notClone) this->cond = cond;
					else
					{
						this->cond = new char [strlen (cond) + 1];
						for (int i = 0; i < strlen (cond) + 1; i++)
							this->cond [i] = cond [i];
					}
				}

				StringCondition (:: std :: string cond)
				{
					this->cond = new char [cond.size () + 1];
					
					for (int i = 0; i < cond.size () + 1; i++)
						this->cond [i] = cond [i];					
				}

				~StringCondition ()
				{
					DELETE_ARRAY (cond);
				}
				
				virtual :: std :: string ToString ()
				{
					return :: std :: string (cond);
				}

				Condition* Clone () {return new  StringCondition (cond);}

				
				Condition& operator! ()
				{
					char* newCond = new char [strlen (cond) + 4];
					int i = 0;
					int j;
					newCond [i++] = '!';
					newCond [i++] = '(';				

					for (j = 0; j < strlen (cond); j++, i++)
						newCond [i] = cond [j];

					newCond [i++] = ')';
					newCond [i++] = '\0';

					return *(new  StringCondition (newCond));
				}
				
				Condition& operator|| (Condition& condition)
				{
					:: std :: string cond_str = condition.ToString ();

					char* newCond = new char [strlen (cond) + cond_str.size () + 9];
					
					int i = 0;
					int j;
					newCond [i++] = '(';

					for (j = 0; j < strlen (cond); j++, i++)
						newCond [i] = cond [j];

					newCond [i++] = ')';
					newCond [i++] = ' ';
					newCond [i++] = '||';
					newCond [i++] = ' ';
					newCond [i++] = '(';


					for (j = 0; j <  cond_str.size (); j++, i++)
						newCond [i] = cond_str [j];

					newCond [i++] = ')';
					newCond [i++] = '\0';
					 

					return *(new  StringCondition (newCond));
				}
				
				Condition& operator&& (Condition& condition)
				{
					:: std :: string cond_str = condition.ToString ();

					char* newCond = new char [strlen (cond) + cond_str.size () + 9];
					
					int i = 0;
					int j;
					newCond [i++] = '(';

					for (j = 0; j < strlen (cond); j++, i++)
						newCond [i] = cond [i];

					newCond [i++] = ')';
					newCond [i++] = ' ';
					newCond [i++] = '&&';
					newCond [i++] = ' ';
					newCond [i++] = '(';


					for (j = 0; j < cond_str.size (); j++, i++)
						newCond [i] = cond_str [j];

					newCond [i++] = ')';
					newCond [i++] = '\0';
					 

					return *(new  StringCondition (newCond));
				}
			};
		}
	}
}

#endif