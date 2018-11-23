/************************************************************************************************************
 *	Основной класс TightlyNestedLoops пространства имен Loop												*
 *	предназначен для хранения информации по структуре дерева циклов.										*
 *																											*
 *	Данный класс описывает гнездо тесно вложенных циклов (далее гнездо). 									*			
 *	Циклы образуют тесно вложенное гнездо, если операторы начала циклов не разделены дургими операторами и 	*
 *	операторы конца циклов также не разделены посторонними оперторами.										*
 *	Одиночный цикл и процедура (функция) также считается таким гнездом.										*
 *																											*
 *	Для каждого гнезда можно получить следующую информацию:													*
 *		- индексные переменный используемые в гнезде														*
 *		с привязкой их к циклам гнезда;																		*
 *		- порядок циклов в гнезде;																			*
 *		- информацию о внутренних и объемлющем гнездах;														*
 *		- информацию по используемой в гнезде памяти.														*
 *																											*
 *	Данный класс предоставляет следующий интерфейс:															*
 *		- TightlyNestedLoops (int) - конструктор, для создания гнезда циклов,								*
 *		включающего в себя заданное число индексных переменных.												*
 *		- TightlyNestedLoops* Clone () - выполняет глубокое копирование объекта.							*
 *		- IndexVariable* AddIndexVariable (IndexVariable*, bool notClone = false) -							*
 *		добавление индесной перменной, можно добавить переменных больше, чем указано в конструкторе,		*	 
 *		но при этом возможно падение производительности.													*
 *		- TightlyNestedLoops* AddNest (int iVarsNumber) - добавление вложенного гнезда циклов,				*
 *		метод возвращает указатель на объект, соответствующий добавленному гнезду.							*
 *		- TightlyNestedLoops* SplitNest (int loopsNum) - разбивает гнездо на два,							*
 *		во внутреннее из двух гнезд войдет loopsNum последних (по порядку добавления) циклов,				*
 *		со всесми идексными переменными, относящимися к ним,												*
 *		оставшиеся индексные переменные будут отнесены ко второму гнезду,									*
 *		метод возвращает указатель на внешнее гнездо.														*
 *		- void AddMUFirstUsage (MemoryUnit* mu) - указывает, что область памяти используется в гнезде и		*
 *		устанавливает точку первого использование, на последние использование, добавленное в список			*
 *		использований области памяти.																		*
 *		- void AddMUFirstUsage (MemoryUnit* mu, MemoryUnitUsage* firstUsage) - устанавливает точку первого	*
 *		использования области памяти в гнезде,																*		
 *		возможны потери производительности относительно предыдущего метода.									*
 *		- AddMULastUsage () - задает точки последнего использований всех областей памяти,					*
 *		ранее добавленных в гнездо, устанавливает их на последние использование,							*
 *		добавленное в список использований соответствуюей области памяти.									*
 *		- AddMULastUsage (MemoryUnit* mu, MemoryUnitUsage* lastUsage) - устанавливает точку последнего		*
 *		использования области памяти в гнезде,																*		
 *		возможны потери производительности относительно предыдущего метода.									*
 *		- TightlyNestedLoops* GetExternalNest () - возвращает указатель на внешнее гнездо.					*
 *		- int GetInternalNestsNumber () - возвращает число гнезд, непосредственно вложенных (не тесно)		*
 *		в данное гнездо.																					*
 *		- TightlyNestedLoops* GetInternalNest (int nestNumber) - возвращает гнездо, непосредственно			*
 *		вложенное (не тесно) в данное и являющееся nestNumber гнездом по счету.								*
 *		- MemoryUnit* GetMemoryUnit (int index) - возвращает index область памяти.							*
 *		- bool IsUse (MemoryUnit* mu) - проверяет используется ли область памяти mu в гнезде.				*
 *		- MemoryUnitUsage* GetFirstUsage (MemoryUnit* mu) - возвращает указатель на первое использование	*	
 *		области памяти в гнезде или NULL.																	*
 *		- MemoryUnitUsage* GetFirstUsage (MemoryUnit* mu) - возвращает указатель на последнее использование	*	
 *		области памяти в гнезде или NULL.																	*
 *		- bool operator== (TightlyNestedLoops& tnl) - выполняет сравнение объектов,							*
 *		два гнезда равны, если они состоят из одних и тех же циклов.										*
 *		- bool operator!= (TightlyNestedLoops& tnl) - выполняет сравнение объектов,							*
 *		два гнезда равны, если они состоят из одних и тех же циклов.										*
 *																											*
 *	При включении режима отладки (DEBUG != 0) доступны дополнительные функции:								*
 *		- void Print () - печатает информацию о гнезде.														* 
 ************************************************************************************************************/
#ifndef TIGHTLY_NESTED_LOOPS_H
#define TIGHTLY_NESTED_LOOPS_H

#include "debug.h"

#if DEBUG 
	#include "mu_array.h"
	#include "mu_array_usage.h"
	#include "test_dep_cond.h"
#endif

#include "macros.h"
#include "program_unit.h"

namespace Analyzer
{
	namespace Loop
	{
		class TightlyNestedLoops : public ProgramUnit
		{
			IndexVariableCollection *iVars; 						

			TightlyNestedLoops (int iVarsNumber, PUCallRegion* parrentRegion, ProgramUnit* externalPU) : ProgramUnit (parrentRegion)
			{
				this->iVars = new IndexVariableCollection (iVarsNumber);				
				this->externalPU = externalPU; //так как конструктор защищенный, проверка: externalNest != NULL - не предусмотрена			
			}

			TightlyNestedLoops (ProgramUnit* externalNest) : ProgramUnit (externalNest)
			{
				this->iVars = NULL;				
			}		

		public:	
//********************* constructors *************************

			TightlyNestedLoops (int iVarsNumber, PUCallRegion* parrentRegion) : ProgramUnit (parrentRegion)
			{
				this->iVars = new IndexVariableCollection (iVarsNumber);				
			}

			~TightlyNestedLoops ()
			{
				DELETE_POINTER (iVars)				
			}

//********************* tree creation function ******************

			ProgramUnit* Clone () 
			{
				TightlyNestedLoops* temp = new TightlyNestedLoops (externalPU);
				temp->iVars = (IndexVariableCollection*)iVars->Clone ();
				temp->callRegion = callRegion->Clone ();
				temp->musUsage = (RegionUsageCollection*)musUsage->Clone ();
				temp->internalPUs = (ProgramUnitCollection*)internalPUs->Clone ();
				return temp;
			}

			IndexVariable* AddIndexVariable (IndexVariable *iVar, bool notClone = false) 
			{
				CHECK_NULL_POINTER (iVar)
						
				IndexVariable* temp;
				if (notClone) temp = iVar;
				else temp = (IndexVariable*)iVar->Clone();

				iVars->Add(temp);

				return temp;
			}

			TightlyNestedLoops* AddNest (int iVarsNumber)
			{
#if DEBUG & DBG_TREE_CREATE

				cout << "TightlyNestedLoops :: AddNest (int iVarsNumber)" << endl;
				cout << "iVarsNumber = " << iVarsNumber << endl << endl;				
				Print ();
#endif							
				return (TightlyNestedLoops*)(*internalPUs) [internalPUs->Add (new TightlyNestedLoops (iVarsNumber, callRegion, this))];
			}

			TightlyNestedLoops* SplitNest (int loopsNum) 
			{
#if DEBUG & DBG_TREE_CREATE

				cout << "TightlyNestedLoops :: SplitNest (int loopsNum)" << endl;
				cout << "loopsNum = " << loopsNum << endl << endl;
				
				Print ();
#endif
				//создаем гнездо, внешнее по отношению к текущему (this)
				//коллекция индексных переменных будет скопирована далее, поэтому ее размер не важен (0)
				TightlyNestedLoops* newNest = new TightlyNestedLoops (externalPU); 
				
				//разбиваем коллекцию индексных переменных
				//loopsNum - число циклов (не индексных переменных) во внутреннем гнезде
				IndexVariableCollection* inIVars = iVars->SplitCollection (loopsNum);				
				newNest->iVars = iVars; 
				iVars = inIVars;				
				
				//устанавливаем связь нового гнезда с текущим
				newNest->internalPUs = new ProgramUnitCollection ();
				newNest->internalPUs->Add (this); 
				
				//устанавливаем связь внешнего гнезда с новым 
				//заменяем указатель (в коллекции внешнего гнезда) на текущее гнездо на новый
				GetInternalPUs (externalPU)->Update(GetInternalPUs (externalPU)->Find(this), newNest);

				//устанавливаем связь текущего гнезда с новым
				this->externalPU = newNest;

				newNest->musUsage = (RegionUsageCollection*)musUsage->Clone();
				newNest->callRegion = (PUCallRegion*)callRegion->Clone ();

#if DEBUG & DBG_TREE_CREATE

				cout << endl << "external nest: newNest" << endl;
				newNest->Print ();				
				cout << "this:" << endl;
				Print ();
#endif
				return newNest;				
			}

//************************* Get... functions **********************
			int GetLoopsNumber () 
			{				
				return iVars->GetLoopsNumber ();	
			}

			int GetLoopId (int loopsNumber)
			{
				CHECK_INDEX_RANGE (loopsNumber, 0, GetLoopsNumber ())

				int loopId = -1;
				int temp;
				int loopNum = -1;
				for (int i = 0; i < iVars->GetSize (); i++)
				{
					temp = (*iVars) [i]->GetLoopId ();
					if (loopId != temp) 
					{
						loopId = temp;
						loopNum++;
					}
					if (loopsNumber == loopNum) break;
				}

				return loopId;
			}

			IndexVariable* GetIndexVariable (int varId)
			{
				int index = iVars->Find (varId);
				if (index == ELEMENT_NOT_FOUND) return NULL;
				
				return (*iVars)[index];
			}		

			int GetIndexVariableNumbers ()
			{
				return iVars->GetSize ();
			}
			IndexVariable* GetIndexVariable2 (int iVarNumber)
			{
				return (*iVars) [iVarNumber];
			}


//************************* overloaded operators ******************************
			
			bool operator== (ProgramUnit& pu) 
			{
				if (this == &pu) return true;
				
				TightlyNestedLoops* tnl = dynamic_cast <TightlyNestedLoops*> (&pu);

				if (!tnl) return false;
				
				return	*this->iVars == *tnl->iVars;						
			}			

//************************* debug functions ************************************

			void Print ()
			{
#if DEBUG
				cout << "TightlyNestedLoops :: Print ()" << endl;
#endif
				cout << "Tight nest:" << endl;
				cout << iVars->GetLoopsNumber () << " - loops in tight nest" << endl;
				cout << iVars->GetSize () << " - index variables in tight nest" << endl;
				cout << "[loopId : iVarId]: ";
				for (int i = 0; i < iVars->GetSize (); i++)
					cout << "[" << (*iVars) [i]->GetLoopId () << " : " << (*iVars) [i]->GetId () << "] "; 
				cout << endl;				
				cout << internalPUs->GetSize () << " - internal tight nests" << endl;
				cout << musUsage->GetSize () << " - memory units are used" << endl;
			}			
		};	
	}
}

#endif