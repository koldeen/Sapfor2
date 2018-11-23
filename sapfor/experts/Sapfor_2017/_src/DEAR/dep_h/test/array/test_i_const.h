#ifndef TEST_INDEX_CONST_H
#define TEST_INDEX_CONST_H

#include "math.h"

#include "debug.h"

#include "test.h"
#include "test_usages.h"
#include "mu_array_usage.h"
#include "isg_expression.h"
#include "test_dependence.h"
#include "test_index_info.h"

namespace Analyzer
{
	namespace Test
	{
		class ConstIndexTest: public IEPairArrayTest
		{			
			IntegerValue* iVal1;
			IntegerValue* iVal2; 				
			
		public:
			ConstIndexTest (TestIdentifier testId): IEPairArrayTest (testId)
			{
				iVal1 = NULL;
				iVal2 = NULL;				
			}

			~ConstIndexTest ()
			{
				iVal1 = NULL;
				iVal2 = NULL;				
			}					
			
			bool IsApplicable ()
			{
				IEPairArrayTest :: IsApplicable ();

				if (mu->IsScalar ()) return false;								
				
				IExpression* expr1 = NULL;
				IExpression* expr2 = NULL;			
			
				expr1 = prevAUsage->GetIndexExpr (dim);
				expr2 = postAUsage->GetIndexExpr (dim);
				if (!expr1 || !expr2) return false;

				iVal1 = dynamic_cast <IntegerValue*> (expr1);
				iVal2 = dynamic_cast <IntegerValue*> (expr2);
				if (!iVal1 || !iVal2) return false;					

				return true;
			}

			TestResult Execute ()
			{				
				if (!IsApplicable ()) return NOT_APPLICABLE;					

				Dependence* depTemp = new Dependence ();

				if (prevAUsage == postAUsage || iVal1->GetValue () == iVal2->GetValue ()) 					
					depTemp->SetExistenceCond (DEP_EXIST, DEP_ALWAYS, DEP_EXACTLY);
				else 
					depTemp->SetExistenceCond (DEP_NOT_EXIST, DEP_ALWAYS, DEP_EXACTLY);

				for (int i = 0; i < loopsNumber; i++)
					dep [i] = (Dependence*)depTemp->Clone ();

				DELETE_POINTER (depTemp)

				return SUCCESS;
			}			
		};
	}
}


#endif