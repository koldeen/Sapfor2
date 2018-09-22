#ifndef TEST_GCD_H
#define TEST_GCD_2_H

#include "math.h"

#include "debug.h"

#include "test.h"
#include "test_usages.h"
#include "mu_array_usage.h"

#include "isg_expression.h"
#include "linear_expression.h"
#include "int_expression.h"

#include "test_dependence.h"
#include "test_index_info.h"

#include "math_gcd.h"

using namespace Mathematics;
using namespace Expression;

namespace Analyzer
{
	namespace Test
	{
		class GCDTest: public IEPairArrayTest
		{	
			int a, b, c;	
			IndexVariable* iVar;

			//поиск индексной переменной с идентификатором в БД varId 
			//в дереве тесно вложенных циклов 
			//ищем среди индесных переменных определенных на данном уровне и выше
			bool  IsUpper (int varId, TightlyNestedLoops* tNLoops)
			{
				if (!tNLoops) return false;
				if (tNLoops->GetIndexVariable (varId)) return true;					

				return IsUpper (varId, dynamic_cast <TightlyNestedLoops*> (tNLoops->GetExternalPU ()));
			}	

		public:
			GCDTest (int testId) : IEPairArrayTest (testId)
			{	
				a = b = c = 1;
				iVar = NULL;
			}

			~GCDTest ()
			{
				iVar = NULL;
			}

			bool IsApplicable ()
			{
#if DEBUG & DBG_TEST_LINEAR_2
				cout << "GCDTest :: IsApplicable ()" << endl;
#endif 
				IEPairArrayTest :: IsApplicable ();

				if (mu->IsScalar ()) return false;	

				IndexVariable* iVar1 = NULL;
				IndexVariable* iVar2 = NULL;

				IntegerValue* coeff1 = NULL;
				IntegerValue* coeff2 = NULL;
			
				IntegerValue* freeTerm1 = NULL;
				IntegerValue* freeTerm2 = NULL;			

				LinearExpression* iLExpr1 = NULL;
				LinearExpression* iLExpr2 = NULL;						

				IExpression* expr1 = NULL;
				IExpression* expr2 = NULL;							
			
				expr1 = prevAUsage->GetIndexExpr (dim);
				expr2 = postAUsage->GetIndexExpr (dim);
				if (!expr1 || !expr2) return false;

				iLExpr1 = dynamic_cast <LinearExpression*> (expr1);
				iLExpr2 = dynamic_cast <LinearExpression*> (expr2);

				if (!iLExpr1)
				{
					//возможно, это просто константа
					freeTerm1 = dynamic_cast <IntegerValue*> (expr1);
					if (!freeTerm1) return false;

					if (!iLExpr2) return false; //по крайней мере одно выражение должно быть линейным					
				}
				else if (iLExpr1->GetVariablesNumber () == 1)
				{
					iVar1 = dynamic_cast <IndexVariable*> (iLExpr1->GetVariable (0));					
					coeff1 = dynamic_cast <IntegerValue*>  (iLExpr1->GetCoeffitient (0));
					freeTerm1 = dynamic_cast <IntegerValue*> (iLExpr1->GetFreeTerm ());	
					
					if (!iVar1 || !coeff1 || !freeTerm1) return false;	
				}
				else return false;
				
				if (!iLExpr2)
				{
					//возможно, это просто константа
					freeTerm2 = dynamic_cast <IntegerValue*> (expr2);
					if (!freeTerm2) return false;

					if (!iLExpr1) return false; //по крайней мере одно выражение должно быть линейным
				} 
				else if (iLExpr2 && iLExpr2->GetVariablesNumber () == 1)
				{
					iVar2 = dynamic_cast <IndexVariable*> (iLExpr2->GetVariable (0));
					coeff2 = dynamic_cast <IntegerValue*>  (iLExpr2->GetCoeffitient (0));
					freeTerm2 = dynamic_cast <IntegerValue*> (iLExpr2->GetFreeTerm ());

					if (!iVar2 || !coeff2 || !freeTerm2) return false;
				}				
				else return false;				

				if (iVar1 && iVar2 && iVar1->GetId () != iVar2->GetId ()) return false; //если разные id, то тест не применим

				c = freeTerm2->GetValue () - freeTerm1->GetValue ();				

				if (iVar1) a = coeff1->GetValue ();
				else a = 0;
				
				if (iVar2) b = - coeff2->GetValue ();		
				else b = 0;

				//По крайней мере одна из них не NULL
				//Id - одинаковые
				if (iVar1) iVar = iVar1;
				else iVar = iVar2;

				return true;
			}

			TestResult Execute ()
			{
#if DEBUG & DBG_TEST_LINEAR_2
				cout << "GCDTest :: Execute ()" << endl;
#endif 
				if (!IsApplicable ()) return NOT_APPLICABLE;	

				GCDTwoNumbers gcd (a, b);
								
				//iVarLoopNum - номер цикла, в котором определена iVar
				//-1, если iVar принадлежит объемлющим гнездам.
				//loopsNumber, если принадлежит внутренним гнездам.
				int iVarLoopNum = -1; 
				Dependence* depUpper = new Dependence ();				
				Dependence* depInner = new Dependence ();

				if (!pu->GetIndexVariable (iVar->GetId ()))
					if (IsUpper (iVar->GetId (), dynamic_cast <TightlyNestedLoops*> (pu->GetExternalPU ())))
						iVarLoopNum = -1;
					else
						iVarLoopNum = loopsNumber;
				else 
				{			
					int loopId;
					TightlyNestedLoops* tnl = dynamic_cast <TightlyNestedLoops*> (pu);
					if (tnl)
					{
						for (	iVarLoopNum = 0, loopId = tnl->GetLoopId (iVarLoopNum); 
								loopId != iVar->GetLoopId (); 
								iVarLoopNum++, loopId = tnl->GetLoopId (iVarLoopNum));
					}
					else iVarLoopNum = 0; //никогда не выполнится доделать
				}				

				if (iVarLoopNum > 0)
				{
					//Тестируем циклы из гнезда pu, охватывающие цикл iVar->GetLoopId ().
					//В prevUsage и postUsage iVar может быть как одинаковой, так и разной.				
					if (c == 0 ||							//iVar - любая
						a + b != 0 && c % (a + b) == 0 ||	//iVar = c / (a + b)										
						c % gcd.GetGCD ())					/*рашаем a * iVar + b * iVar' = c
														  a != 0 || b != 0, так как иначе индексные выражения были бы константами
														  => gcd != 0*/					
						depUpper->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_NOT_EXACTLY);			
					else					
						depUpper->SetExistenceCond (DEP_NOT_EXIST, DEP_ALWAYS, DEP_EXACTLY);
				}

				if (iVarLoopNum > -1 && iVarLoopNum < loopsNumber)
				{
					dep [iVarLoopNum] = new Dependence ();
					//Tестируем на зваисимость цикл из гнезда pu, в котором описана iVar.
					//В prevUsage и postUsage iVar должна принимать разные значения.
					//Решаем a * iVar + b * iVar' = c		
					if (c == 0 && b != -a ||					//a != 0 || b != 0, так как иначе индексные выражения были бы константами
						c != 0 && c % gcd.GetGCD () == 0)			
						dep [iVarLoopNum]->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_NOT_EXACTLY);																
					else
						dep [iVarLoopNum]->SetExistenceCond (DEP_NOT_EXIST, DEP_ALWAYS, DEP_EXACTLY);				
				}

				if (iVarLoopNum < loopsNumber - 1)
				{
					//Тестируем циклы из гнезда pu, вложенные в цикл iVar->GetLoopId ().
					//В prevUsage и postUsage iVar должна быть одинаковой.			
					if (c == 0 ||
						a + b != 0 && c % (a + b) == 0)						
						depInner->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_NOT_EXACTLY);			
					else 
						depInner->SetExistenceCond (DEP_NOT_EXIST, DEP_ALWAYS, DEP_EXACTLY);		
				}

				
				for (int loop = 0; loop < iVarLoopNum; loop++)
					dep [loop] = (Dependence*)depUpper->Clone ();			

				for (int loop = iVarLoopNum + 1; loop < loopsNumber; loop++)
					dep [loop] = (Dependence*)depInner->Clone ();		

				DELETE_POINTER (depUpper)
				DELETE_POINTER (depInner)

					
#if DEBUG & DBG_TEST_LINEAR_2
				cout << endl << "!!!!!!!!!!!!RESULT!!!!!!!!!!!" << endl;
				cout << a << " * iVar + " << b << " * iVar' = " << c << endl;
				cout << "iVarId: " << iVar->GetId ();
				cout << " iVarLoopId: " << iVar->GetLoopId () << endl;

				for (int i = 0; i < loopsNumber; i++)
				{					
					cout << "loop: " << i << " loopId: " << pu->GetLoopId (i) << endl;				

					dep[i]->Print ();
				}
				cout << "!!!!!!!!!!END RESULT!!!!!!!!!" << endl << endl;
#endif
								
				return FAILURE;
			}
		};
	}
}

#endif