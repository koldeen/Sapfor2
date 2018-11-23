/*
 
 */
#ifndef TEST_INDEX_INFO_H
#define TEST_INDEX_INFO_H

#include "test_dep_info.h"
#include "test_info.h"
#include "macros.h"

using namespace Analyzer :: Test :: Dependences;

namespace Analyzer
{
	namespace Test
	{		
		class IndexTestInfo: public TestInfo
		{
			int dimsNumber;
			DepTestInfo** deps;

		public:
			IndexTestInfo (int dimsNumber)
			{
				this->dimsNumber = dimsNumber;
				deps = new DepTestInfo* [dimsNumber];

				/*for (int i = 0; i < dimsNumber; i++)
					deps [i] = new DepTestInfo ();*/
			}

			~IndexTestInfo ()
			{
				DELETE_POINTER_ARRAY (deps, dimsNumber)
			}

			int GetDimsNumber () {return dimsNumber;}

			DepTestInfo* GetDepTestInfo (int dim)
			{
				CHECK_INDEX_RANGE (dim, 0, dimsNumber)

				return deps [dim];
			}
		};				
	}
}

#endif