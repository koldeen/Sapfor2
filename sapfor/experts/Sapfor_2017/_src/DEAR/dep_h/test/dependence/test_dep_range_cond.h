#ifndef TEST_DEP_RANGE_CONDITION_H
#define TEST_DEP_RANGE_CONDITION_H

#include "test_dep_cond_str.h"
#include "macros.h"
#include <string>
#include <math.h>
#include <stdio.h>
#include <algorithm>

#define INFINITY true
#define NOT_INFINITY false

//[leftBound, rightBound]

namespace Analyzer
{
	namespace Test
	{
		namespace Dependences
		{
			class RangeCondition : public Condition
			{
				int id;
				char* varName;
				bool isLeftBInfinity;
				bool isRightBInfinity;
				int leftBound;
				int rightBound;
			public:
				RangeCondition (int id, :: std :: string varName)
				{
					this->varName = new char [varName.size () + 1];
					for (int i = 0; i < varName.size () + 1; i++)
						this->varName [i] = varName [i];
					
					isLeftBInfinity = INFINITY;
					isRightBInfinity = INFINITY;	
					this->id = id;
				}
				RangeCondition (int id, char* varName, bool notClone = CLONE)
				{
					CHECK_NULL_POINTER (varName)

					if (notClone) this->varName = varName;
					else
					{
						this->varName = new char [strlen (varName) + 1];
						for (int i = 0; i < strlen (varName) + 1; i++)
							this->varName [i] = varName [i];
					}

					isLeftBInfinity = INFINITY;
					isRightBInfinity = INFINITY;	
					this->id = id;
				}

				RangeCondition (int id, char* varName, int leftBound, int rightBound, bool notClone = CLONE)
				{
					CHECK_NULL_POINTER (varName)

					if (notClone) this->varName = varName;
					else
					{
						this->varName = new char [strlen (varName) + 1];
						for (int i = 0; i < strlen (varName) + 1; i++)
							this->varName [i] = varName [i];
					}

					this->leftBound = leftBound;
					this->rightBound = rightBound;
					this->id = id;
				}
				
				~RangeCondition ()
				{
					DELETE_ARRAY (varName);
				}
				
				virtual :: std :: string ToString ()
				{
					:: std :: string lb;
					:: std :: string rb;
					:: std :: string str;
					

					if (isLeftBInfinity) lb = "";
					else
					{
						char s[10];
						sprintf (s, "%d <= ", leftBound);
						lb = :: std :: string (s);
					}

					if (isRightBInfinity) rb = "";
					else
					{
						char s[10];
						sprintf (s, " <= %d", rightBound);
						rb = :: std :: string (s);
					}		

					char sId [10];
					sprintf (sId, " (%d)", id);

					str =	lb + 							
							:: std :: string (varName) +
							:: std :: string (sId) +
							rb;
					
					return str;
				}
				
				int GetId () {return id;}

				int GetLeftBound () {return leftBound;}

				void SetLeftBound (int leftBound) 
				{
					this->leftBound = leftBound;
					this->isLeftBInfinity = NOT_INFINITY;
				}
				int GetRightBound () {return rightBound;}

				void SetRightBound (int rightBound) 
				{
					this->rightBound = rightBound;
					this->isRightBInfinity = NOT_INFINITY;
				}

				Condition* Clone () 
				{
					RangeCondition* newCond = new RangeCondition (id, varName);
					
					newCond->isLeftBInfinity = isLeftBInfinity;
					newCond->isRightBInfinity = isRightBInfinity;

					newCond->leftBound = leftBound;
					newCond->rightBound = rightBound;					
					
					return newCond;
				}

				
				Condition& operator! ()
				{
					if (isLeftBInfinity && !isRightBInfinity)
					{
						RangeCondition* cond = (RangeCondition*)Clone ();
						cond->leftBound = rightBound + 1;
						cond->isRightBInfinity = INFINITY;
						cond->isLeftBInfinity = NOT_INFINITY;
								
						return *cond;						
					}
					else if (isRightBInfinity && !isLeftBInfinity) 
					{
						RangeCondition* cond = (RangeCondition*)Clone ();
						cond->rightBound = leftBound - 1;
						cond->isLeftBInfinity = INFINITY;
						cond->isRightBInfinity = NOT_INFINITY;

						return *cond;
					}
					else if (isLeftBInfinity && isRightBInfinity)
					{
						return *this->Clone ();
					}

					StringCondition* cond = new StringCondition (ToString ());
					StringCondition& res = (StringCondition&)!(*cond);
					
					DELETE_POINTER (cond)
					
					return res;
				}

				
				Condition& operator|| (Condition& condition)
				{
					RangeCondition* rCond = dynamic_cast <RangeCondition*> (&condition);				
					
					if (rCond && id == rCond->id)
					{
						if (isLeftBInfinity && isRightBInfinity) 
							return *this->Clone ();
						else if (rCond->isLeftBInfinity && rCond->isRightBInfinity) 
							return *rCond->Clone ();
						else if (isLeftBInfinity && !isRightBInfinity)
						{	//x <= rb1
							if (isLeftBInfinity && !isRightBInfinity)
							{	// x <= rb2
								RangeCondition* cond = (RangeCondition*)Clone ();
								cond->rightBound = max (rightBound, rCond->rightBound);
								cond->isLeftBInfinity = INFINITY;							
								cond->isRightBInfinity = NOT_INFINITY;

								return *cond;	
							}
							else if (!isLeftBInfinity && !isRightBInfinity)
							{	// lb <= x <= rb2
								RangeCondition* cond = (RangeCondition*)Clone ();
								cond->rightBound = max (rightBound, rCond->rightBound);
								cond->isLeftBInfinity = INFINITY;								
								cond->isRightBInfinity = NOT_INFINITY;

								return *cond;	
							}							
						}
						else if (!isLeftBInfinity && isRightBInfinity)
						{	//lb1 <= x
							if (!isLeftBInfinity && isRightBInfinity)
							{	//lb2 <= x
								RangeCondition* cond = (RangeCondition*)Clone ();
								cond->leftBound = min (leftBound, rCond->leftBound);
								cond->isRightBInfinity = INFINITY;
								cond->isLeftBInfinity = NOT_INFINITY;
								
								return *cond;	
							}
							else if (!isLeftBInfinity && !isRightBInfinity)
							{	// lb <= x <= rb2
								RangeCondition* cond = (RangeCondition*)Clone ();
								cond->leftBound = min (leftBound, rCond->leftBound);
								cond->isRightBInfinity = INFINITY;
								cond->isLeftBInfinity = NOT_INFINITY;
								
								return *cond;	
							}							
						}
						else if (!isLeftBInfinity && !isRightBInfinity)
						{	//lb1 <= x <= rb1
							if (!isLeftBInfinity && isRightBInfinity)
							{	//lb2 <= x
								RangeCondition* cond = (RangeCondition*)Clone ();
								cond->leftBound = min (leftBound, rCond->leftBound);
								cond->isRightBInfinity = INFINITY;
								cond->isLeftBInfinity = NOT_INFINITY;	

								return *cond;	
							}
							else if (isLeftBInfinity && !isRightBInfinity)
							{	// x <= rb2
								RangeCondition* cond = (RangeCondition*)Clone ();
								cond->rightBound = max (rightBound, rCond->rightBound);
								cond->isLeftBInfinity = INFINITY;								
								cond->isRightBInfinity = NOT_INFINITY;

								return *cond;	
							}
							else if (!isLeftBInfinity && !isRightBInfinity)
							{	// lb <= x <= rb2
								if (rightBound >= rCond->leftBound &&
									leftBound <= rCond->rightBound)
								{
									RangeCondition* cond = (RangeCondition*)Clone ();
									cond->leftBound = min (leftBound, rCond->leftBound);
									cond->rightBound = min (rightBound, rCond->rightBound);
									cond->isLeftBInfinity = NOT_INFINITY;
									cond->isRightBInfinity = NOT_INFINITY;

									return *cond;	
								}
							}							
						}
					}

					StringCondition* cond1 = new StringCondition (ToString ());
					StringCondition* cond2 = new StringCondition (condition.ToString ());
					StringCondition& res = (StringCondition&)((*cond1) || (*cond2));
					
					DELETE_POINTER (cond1)
					DELETE_POINTER (cond2)
					
					return res;
				}
				
				Condition& operator&& (Condition& condition)
				{
					StringCondition* cond1 = new StringCondition (ToString ());
					StringCondition* cond2 = new StringCondition (condition.ToString ());
					StringCondition& res = (StringCondition&)((*cond1) && (*cond2));
					
					DELETE_POINTER (cond1)
					DELETE_POINTER (cond2)
					
					return res;
				}
			};
		}
	}
}

#endif