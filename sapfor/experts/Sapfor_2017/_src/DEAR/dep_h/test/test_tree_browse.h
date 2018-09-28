#ifndef TEST_TREE_BROWSE_H
#define TEST_TREE_BROWSE_H

#include "tn_loops.h"
#include "macros.h"

using namespace Analyzer :: Loop;

namespace Analyzer
{
	namespace Test
	{
		class TNLTreeBrowse
		{
			ProgramUnit* root;
			ProgramUnit* curTNL;
			MemoryUnit* curMU;	
		
		public:
			TNLTreeBrowse ()
			{
				root = NULL;
				curTNL = NULL;
				curMU = NULL;						
			}

			~TNLTreeBrowse ()
			{
				DELETE_POINTER (root)
				curTNL = NULL;
				curMU = NULL;
			}

			ProgramUnit* GetTNLoops () {return root;}
			ProgramUnit* SetTNLoops (ProgramUnit* tnl) 
			{				
				ProgramUnit* temp = root;
				
				root = tnl;
				curTNL = root;
				curMU = NULL;		

				if (root) 
				{
					while (curTNL->GetInternalPUsNumber () !=0)
						curTNL = curTNL->GetInternalPU (0);				

					if (curTNL->GetMemoryUnitsNumber () == 0) //в цикле не используется ни одна переменная
						curTNL = curTNL->GetExternalPU ();

					if (curTNL) curMU = curTNL->GetMemoryUnit (0); 
				}
								
				return temp;
			}

			ProgramUnit* GetCurrentTNLoops () {return curTNL;}
			MemoryUnit* GetCurrentMUnit () {return curMU;}

			void Next ()
			{
				CHECK_NULL_POINTER (root)

				curMU = curTNL->GetNextMemoryUnit (curMU);
					
				if (!curMU)	//если просмотрели все MemoryUnit, то переходим к следующему гнезду
				{
					ProgramUnit* temp = curTNL->GetExternalPU (); 
										
					if (!temp) //curTNL указывает на корень
					{
						curTNL = NULL;
						return;
					}

					curTNL = temp->GetNextInternalPU (curTNL);

					if (!curTNL) curTNL = temp; //все что ниже temp уже просмотрено
					else 
					{
						while (curTNL->GetInternalPUsNumber () !=0) //спускаемся по самой левой ветви в поддереве с корнем в curTNL
							curTNL = curTNL->GetInternalPU (0);
					}

					//если в текущем гнезде не используется ниодна переменная, то
					//во внешнем гнезде должно быть по крайней мере одно использование, так как
					//иначе гнезда слились бы в одно тесно вложенное гнездо					
					if (curTNL->GetMemoryUnitsNumber () == 0) curTNL = curTNL->GetExternalPU ();
					//теперь curTNL == temp или лежит ниже
					//(temp никогда не лист (temp = curTNL->GetExternalNest ()), а отсутствие MemoryUnit возможно только в листе),
					//поэтому curTNL != NULL
					
					curMU = curTNL->GetMemoryUnit (0);					
				}
			}

			bool IsAllView () {return curTNL == root->GetExternalPU ();}
		};
	}
}

#endif