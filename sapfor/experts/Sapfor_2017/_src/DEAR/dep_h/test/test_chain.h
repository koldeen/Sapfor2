#ifndef TEST_CHAIN_H
#define TEST_CHAIN_H

#include "collection.h"
#include "coll_list_element.h"
#include "macros.h"

#include "tn_loops.h"
#include "memory_unit.h"

#include "test.h"
#include "test_usages.h"
#include "test_exception.h"

using namespace Collection;
using namespace Collection :: Exception;
using namespace Analyzer :: Loop;
using namespace Analyzer :: Memory;

namespace Analyzer
{
	namespace Test
	{
		typedef ListElement<ITest*> TestsChain;

		class TestsCollection: public ICollection<ITest*>
		{
			TestsChain* first;
			TestsChain* last;
			TestsChain* lastAccess;
			int lAccessIndex;
		public:
			TestsCollection ()
			{
				first = NULL;
				last = NULL;
				lastAccess = NULL;
				lAccessIndex = 0;
			}

			~TestsCollection ()
			{
				DELETE_POINTER (first)				
				last = NULL;
				lastAccess = NULL;
			}

		private:
			ICollection<ITest*>* Clone () 
			{
				throw  OperationNotImplementException ();
			}
		
		public:
			int Add (ITest* test)
			{
				if (!first) lastAccess = last = first = new TestsChain (test);
				else last = last->SetNextValue (test);
				
				allocatedSize++;
				size++;
				return size - 1;
			}

		private:
			int AddRange (ITest*[], int) 
			{
				throw  OperationNotImplementException ();
			}

			ITest* Update (int, ITest*)
			{
				throw  OperationNotImplementException ();
			}

			void Delete (int) 
			{ 
				throw OperationNotImplementException ();
			}

			void Delete (ITest*) 
			{ 
				throw OperationNotImplementException ();
			}

			int Find (ITest*)
			{ 
				throw OperationNotImplementException ();
			}			

			ITest* operator [] (ITest*)
			{ 
				throw OperationNotImplementException ();
			}

			ITest* operator [] (int index)
			{ 
				CheckIndexRangeEx (index);
				
				if (index < lAccessIndex)
				{
					lAccessIndex = 0;
					lastAccess = first;
				}				

				for (; lAccessIndex < index; lAccessIndex++)
						lastAccess = lastAccess->GetNext ();

				return lastAccess->GetValue ();
			}
		public:		

			TestResult Execute (ProgramUnit *pu, MemoryUnit* mu)
			{
				TestsChain* tChain = first;
				ITest* test = NULL;
				TestResult res = FAILURE;
				
				while (tChain)
				{
					test = tChain->GetValue ();
					test->SetPUnit (pu);
					test->SetMUnit (mu);						

					res = test->Execute ();

					switch (res)
					{
					case SUCCESS :
						return res;
						break;
					case NOT_APPLICABLE :
					case FAILURE :
						tChain = tChain->GetNext ();					
						break;
					default :
						throw Analyzer :: Test :: Exception :: TestException ();				
					}
				}

				return res;
			}
		};
	}
}

#endif