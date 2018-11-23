#ifndef TEST_ARRAY_PREPROCCESSING_H
#define TEST_ARRAY_PREPROCCESSING_H

#include "test.h"
#include "test_chain.h"
#include "mu_array.h"
#include "mu_array_usage.h"
#include "isg_expression.h"
#include "linear_expression.h"
#include "index_variable.h"

using namespace Expression;

namespace Analyzer
{
	namespace Test
	{		
		class PreArrayTest : public ITest
		{
			ISgExpression* iSgExpr; //преобразуемое в данный момент выражение			

			//поиск индексной переменной с идентификатором в БД varId 
			//в дереве тесно вложенных циклов 
			//ищем среди индесных переменных определенных на данном уровне и выше
			IndexVariable*  GetIndexVar (int varId, ProgramUnit* pu)
			{
				if (!pu) return NULL;				

				IndexVariable* iVar = pu->GetIndexVariable (varId);
				if (iVar) return iVar;
				
				return GetIndexVar (varId, pu->GetExternalPU ());
			}

			//возвращает индексную переменную, соответствующую var, или NULL			
			IndexVariable* GetIndexVar (ISgExpression* var)
			{
				if (!var->IsVariable ()) return NULL;
				
				return GetIndexVar (var->GetId (), pu);
			}

			//преобразование iSgExpr в линейное выражение
			//проверка на линейность не выполняется
			//возвращаемое значение: указатель на линейное выражение,
			//либо NULL, если ЛИНЕЙНОЕ выражение нельзя преобразовать
			LinearExpression* ToLinear ()
			{				
				int len = iSgExpr->LinearLength ();
				int freeTerm = 0;							
				int coeff;
				LinearExpression* lExpr = new LinearExpression (len);
				ISgExpression** factor1 = NULL;
				ISgExpression** factor2 = NULL;
				IndexVariable* iVar = NULL;
				
				iSgExpr->GetLinearExpr (&factor1, &factor2);	

				for (int i = 0; i < len; i++)
				{						
					if (factor1 [i]->IsConstant () && factor1 [i]->IsInteger ())
					{
						coeff = factor1 [i]->GetIntegerValue ();
						if (!factor2 [i]) 
						{
							freeTerm += coeff;						
							continue;
						}
						else 
							iVar = GetIndexVar (factor2 [i]);						
					}
					else 
					{	
						if (!factor2 [i])
							coeff = 1;							
						else if (factor2 [i]->IsConstant () && factor2 [i]->IsInteger ())						
							coeff = factor2 [i]->GetIntegerValue ();					
						else
						{							
							DELETE_POINTER (lExpr) //не можем преобразовать 
							break;
						}

						iVar = GetIndexVar (factor1 [i]);																
					}	
					//необходимо клонировать iVar для корректного удаления, ДОДЕЛАТЬ										
					if (iVar)
						lExpr->AddMonom (new IntegerValue (coeff), iVar, NOT_CLONE);
					else 
					{							
						DELETE_POINTER (lExpr) //не можем преобразовать 
						break; 
					}
				}		

				if (lExpr)			
					lExpr->SetFreeTerm (new IntegerValue (freeTerm), NOT_CLONE);
				
				DELETE_POINTER_ARRAY (factor1, len)
				DELETE_POINTER_ARRAY (factor2, len)	
				
				return lExpr;
			}

			//преобразование iSgExpr		
			IExpression* Conversion ()
			{					
				if (iSgExpr->IsConstant () && iSgExpr->IsInteger ())	
				{
#if DEBUG & DBG_TEST_ARRAY
					iSgExpr->GetSgExpr ()->unparsestdout();
					cout << " IS CONVERTED TO IntegerValue"<< endl;
#endif
					return new IntegerValue (iSgExpr->GetIntegerValue ());						
				}
				else if (iSgExpr->IsLinear ())
				{
#if DEBUG & DBG_TEST_ARRAY
					//iSgExpr - будет удален в AddIndexExpr							
					iSgExpr->GetSgExpr ()->unparsestdout ();
					cout << " IS CONVERTED TO LinearExpression"<< endl;																					
#endif				
					return ToLinear ();										
				}	
				return NULL;
			}

			void IVarBoundsConversion ()
			{
				TightlyNestedLoops* tnl = dynamic_cast <TightlyNestedLoops*> (pu);

				if (!tnl) return;
				
				IndexVariable* iVar = NULL;
				IExpression* expr = NULL;

				for (int i = 0; i < tnl->GetIndexVariableNumbers (); i++)
				{
					iVar = tnl->GetIndexVariable2 (i);
					iSgExpr = dynamic_cast <ISgExpression*> (iVar->GetLeftBound());
					if (iSgExpr) 
					{
						expr = Conversion ();
						if (expr) iVar->SetLeftBound (expr, NOT_CLONE);
					}

					iSgExpr = dynamic_cast <ISgExpression*> (iVar->GetRightBound());
					if (iSgExpr)
					{
						expr = Conversion ();
						if (expr) iVar->SetRightBound (expr, NOT_CLONE);
					}

					iSgExpr = dynamic_cast <ISgExpression*> (iVar->GetStep());
					if (iSgExpr)
					{						
						expr = Conversion ();
						if (expr) iVar->SetStep (expr, NOT_CLONE);
					}
				}				
			}
		public:
			PreArrayTest (int testId) : ITest (testId) 			
			{
				iSgExpr = NULL;				
			}

			bool IsApplicable ()
			{
#if DEBUG & DBG_TEST_ARRAY
				cout << "PreArrayTest :: IsApplicable ()" << endl;
#endif 
				ITest :: IsApplicable ();

				if (!mu->IsScalar ()) return true;
				return false;
			}

			TestResult Execute ()
			{//DBG_START		
#if DEBUG & DBG_TEST_ARRAY
				cout << "PreArrayTest :: Execute ()" << endl;
#endif 
				if (!IsApplicable ()) return NOT_APPLICABLE;

				if (pu->GetDepTestInfo (mu)->GetIsTested ()) return SUCCESS;

				iSgExpr = NULL;							

				IVarBoundsConversion ();
				
				MemoryUnitUsage* firstInLoop = pu->GetFirstUsage (mu);
				MemoryUnitUsage* lastInLoop = pu->GetLastUsage (mu);
				MemoryUnitUsage* usage = firstInLoop;		
				ArrayUsage* aUsage = NULL;
				IExpression* expr = NULL;
				
				while (usage != lastInLoop->GetNextUsage ())
				{
					aUsage = dynamic_cast <ArrayUsage*> (usage);
					if (!aUsage) continue;
						
					for (int dim = 0; dim < aUsage->GetIndexNumber (); dim++)
					{					
						iSgExpr = dynamic_cast <ISgExpression*> (aUsage->GetIndexExpr (dim));
						if (!iSgExpr) continue; //если не ISgExpression, то во что-то уже преобразовано, либо expr == NULL, не изменяем

						expr = Conversion ();										
						if (expr)
							aUsage->AddIndexExpr (dim, expr, NOT_CLONE);
					}

					usage = usage->GetNextUsage ();
				}
				
				return FAILURE;				
			}

	
		};
	}
}


#endif