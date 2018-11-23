/************************************************************************************************************
 *	Класс Dependence предоставляет данные по некоторой зависимости.											*
 *																											*
 *	Состояние зависимости определяется следующим образом:													*
 *	зависимость существует, если выполнено заданное условие, и												*
 *	не существует, если выполнено другое заданное условие, а												*
 *	в остальных случаях ничего сказать нельзя.																*
 *	Таким образом возможны восемь состояний описывающих зависимость:										*
 *		1. всегда ЕСТЬ;																						*
 *		2. всегда НЕТ;																						*
 *		3. НИЧЕГО НЕЛЬЗЯ СКАЗАТЬ;																			*
 *		4. ЕСТЬ, если выполнено некоторое условие, и НЕТ, если оно не выполнено;							*
 *		5. НЕТ, если выполнено некоторое условие, и ЕСТЬ, если оно не выполнено;							*
 *		6. ЕСТЬ, если выполнено некоторое условие, и НИЧЕГО НЕЛЬЗЯ СКАЗАТЬ, если оно не выполнено;			*
 *		7. НЕТ, если выполнено некоторое условие, и НИЧЕГО НЕЛЬЗЯ СКАЗАТЬ, если оно не выполнено;			*
 *		8. ЕСТЬ, если выполнено некоторое условие, НЕТ, если выполнено некоторое другое условие,			*
 *		НИЧЕГО НЕЛЬЗЯ СКАЗАТЬ в остальных случаях.															*		
 *																											*
 *	Предоставляемый интерфейс:																				*
 *		- Dependence () - конструктор, создающий возможно существующую (НИЧЕГО НЕЛЬЗЯ СКАЗАТЬ) зависимость.	*
 *		- void SetExistenceCond (Existence isExists, Condition* cond, Exactness isExactly) - устанавливает	*
 *		состояние зависимости:																				*	
 *			- SetExistenceCond (DEP_EXISTS, DEP_ALWAYS, DEP_EXACTLY)										*
 *				- зависимость всегда существует.															*
 *			- SetExistenceCond (DEP_NOT_EXISTS, DEP_ALWAYS, DEP_EXACTLY)									*
 *				- зависимость никогда не существует.														*
 *			- SetExistenceCond (DEP_EXISTS, DEP_ALWAYS, DEP_NOT_EXACTLY) или								*
 *			- SetExistenceCond (DEP_NOT_EXISTS, DEP_ALWAYS, DEP_NOT_EXACTLY)								*
 *				- ничего сказать о зависимости нельзя.														*
 *			- SetExistenceCond (DEP_EXISTS, condition, DEP_EXACTLY)											*
 *				- зависимость существует, если выполнено условие, и											*
 *				не существует, если выполнено ранее установленное условие.									*
 *				Если ранее не было установлено ни одно условие,												*
 *				то зависимость не существует во всех остальных случаях.										*
 *			- SetExistenceCond (DEP_NOT_EXISTS, condition, DEP_EXACTLY)										*
 *				- зависимость не существует, если выполнено условие, и										*
 *				существует, если выполнено ранее установленное условие.										*
 *			- SetExistenceCond (DEP_EXISTS, condition, DEP_NOT_EXACTLY)										*
 *				- зависимость существует, если выполнено условие, и											*
 *				ничего сказать о зависимости нельзя, если условие не выполнено.								*
 *			- SetExistenceCond (DEP_NOT_EXISTS, condition, DEP_NOT_EXACTLY)									*
 *				- зависимость не существует, если выполнено условие, и										*
 *				ничего сказать о зависимости нельзя, если условие не выполнено.								*
  ***********************************************************************************************************/
#ifndef TEST_DEPENDENCE_H
#define TEST_DEPENDENCE_H

#define DEP_EXIST true
#define DEP_NOT_EXIST false

#define DEP_EXACTLY true
#define DEP_NOT_EXACTLY false

#define DEP_ALWAYS NULL

#include "test_dep_cond.h"
#include "debug.h"

namespace Analyzer
{
	namespace Test
	{
		namespace Dependences
		{	
			typedef bool Existence;
			typedef bool Exactness;

			enum DepType 
			{
				DEP_UNKNOWN = 0,
				DEP_ALWAYS_EXIST = 1,
				DEP_ALWAYS_NOT_EXIST = 2,				
				DEP_COND_EXIST = 4,
				DEP_COND_NOT_EXIST = 8,
				DEP_CONDITIONAL = (4 | 8),
				DEP_COND_EXIST_UNKNOWN = 16,
				DEP_COND_NOT_EXIST_UNKNOWN = 32,
			};

			class IDependence
			{
			public:
				virtual DepType GetType () = 0;

				virtual bool IsAlwaysExists () = 0;
				virtual bool IsAlwaysNotExists () = 0;
				virtual bool IsUnkonwn () = 0;
				
				virtual bool IsCondExists () = 0;
				virtual bool IsCondNotExists () = 0;
				virtual bool IsConditional () = 0;
				virtual bool IsCondExistsUnkonwn () = 0;
				virtual bool IsCondNotExistsUnknown () = 0;
				
				virtual Condition* GetCondition (Existence) = 0;				

				virtual IDependence* Clone () = 0;
			};

			class Dependence : public IDependence
			{
				Existence isExists;
				Exactness isExactly;
				Condition* existsCond;
				Condition* notExistsCond;

			public:
				Dependence ()
				{
					//зависимость возможно существует
					this->isExists = DEP_EXIST;
					this->isExactly = DEP_NOT_EXACTLY;
					this->existsCond = DEP_ALWAYS;
					this->notExistsCond = DEP_ALWAYS;
				}

				~Dependence ()
				{
					DELETE_POINTER (existsCond)
					DELETE_POINTER (notExistsCond)	
				}

				void SetExistenceCond (Existence isExists, Condition* cond, Exactness isExactly, bool notClone = CLONE)
				{
					this->isExists = isExists;
					this->isExactly = isExactly;				

					if (cond == DEP_ALWAYS || isExactly == DEP_NOT_EXACTLY)
					{
						DELETE_POINTER (existsCond)
						DELETE_POINTER (notExistsCond)						
					} 
					else if (isExists == DEP_EXIST) DELETE_POINTER (existsCond)
					else DELETE_POINTER (notExistsCond)
					
					if (cond != DEP_ALWAYS)
						if (isExists == DEP_EXIST) 
							if (notClone) existsCond = cond;
							else existsCond = cond->Clone ();
						else 
							if (notClone) notExistsCond = cond;
							else notExistsCond = cond->Clone ();
				}
//**************************************************** IDependence class methods *****************************************************
				DepType GetType ()
				{
					if (isExactly)													//(isExists, isExactly, existsCond, notExistsCond)
					{
						if (existsCond && notExistsCond) return DEP_CONDITIONAL;	//(-, 1, 1, 1)
						else if (existsCond) return DEP_COND_EXIST;					//(1, 1, 1, 0)
						else if (notExistsCond) return DEP_COND_NOT_EXIST;			//(0, 1, 0, 1)				
						else if (isExists) return DEP_ALWAYS_EXIST;					//(1, 1, 0, 0)
						else if (!isExists) return DEP_ALWAYS_NOT_EXIST;			//(0, 1, 0, 0)
					}
					else if (existsCond) return DEP_COND_EXIST_UNKNOWN;				//(1, 0, 1, 0)
					else if (notExistsCond) return DEP_COND_NOT_EXIST_UNKNOWN;		//(0, 0, 0, 1)
					else return DEP_UNKNOWN;										//(-, 0, 0, 0)
				}

				bool IsAlwaysExists () {return isExists && isExactly && !existsCond;}		

				bool IsAlwaysNotExists () {return !isExists && isExactly && !notExistsCond;}	

				bool IsUnkonwn () {return !isExactly && !existsCond && !notExistsCond;}			
		
				bool IsCondExists () {return isExactly && existsCond;}

				bool IsCondNotExists () {return isExactly && notExistsCond;}

				bool IsConditional () {return isExactly && existsCond && notExistsCond;}

				bool IsCondExistsUnkonwn () {return !isExactly && existsCond;}

				bool IsCondNotExistsUnknown () {return !isExactly && notExistsCond;}				
				
				Condition* GetCondition (Existence existence) 
				{
					if (existence == DEP_EXIST) return existsCond;
					else return notExistsCond;
				}
				IDependence* Clone ()
				{
					Dependence* newDep = new Dependence ();

					newDep->isExists = this->isExists;
					newDep->isExactly = this->isExactly;
					if (!this->existsCond) newDep->existsCond = NULL;
					else newDep->existsCond = this->existsCond->Clone();

					if (!this->notExistsCond) newDep->notExistsCond = NULL;
					else newDep->notExistsCond = this->notExistsCond->Clone();

					return newDep;
				}
//************************************************************************************************************************************
				//Операция пересечения двух зависимостей по !depUnion (условие наличия или отсутствия зависимости) и
				//объединения по depUnion
				Dependence* UnionIntersect (IDependence* dep, Existence depUnion)
				{//static int x = 0;
				//cout << 1 / x << endl;
#if DEBUG & DBG_DEP
					cout << "Dependence* Dependence :: UnionIntersect (IDependence*, Existence)" << endl;
					cout << "depUnion: ";
					if (depUnion) cout << "DEP_EXIST";
					else cout << "DEP_NOT_EXIST";
					cout << endl;
#endif 
					Dependence* resDep = new Dependence ();					

					//если depUnion = DEP_EXIST, то depUnionCond - условие существования новой зависимости,
					//иначе - условие отсутствия
					Condition* depUnionCond = DEP_ALWAYS; 
					Condition* depIntCond = DEP_ALWAYS;

					IDependence* dep1 = this;
					IDependence* dep2 = dep;					

					if (this->GetType () > dep->GetType ()) //чтобы не рассматривать лишние сочетания типов в switch
					{
						dep1 = dep;
						dep2 = this;
					}
					DepType dep1Type = dep1->GetType ();
					DepType dep2Type = dep2->GetType ();					

					//cущестует ли зависимость в dep (this) (хотя бы в некотором случае)
					//приобретает верное значение в процессе выполнения (в switch)
					bool isDep1Exist = DEP_NOT_EXIST; 
					bool isDep2Exist = DEP_NOT_EXIST;

					if	((depUnion == DEP_NOT_EXIST && 
							(dep1Type == DEP_ALWAYS_NOT_EXIST || dep2Type == DEP_ALWAYS_NOT_EXIST)) ||
						(depUnion == DEP_EXIST && 
							(dep1Type == DEP_ALWAYS_EXIST || dep2Type == DEP_ALWAYS_EXIST)))
					{
						resDep->SetExistenceCond (depUnion, DEP_ALWAYS, DEP_EXACTLY);
						return resDep;
					}					

					//рассматриваем сочетания: (меньший тип, больший тип)
					switch (dep1Type)
					{
					case DEP_UNKNOWN:
						switch (dep2Type)
						{
						case DEP_UNKNOWN:
						case DEP_ALWAYS_EXIST:
						case DEP_ALWAYS_NOT_EXIST:														
							break; // resDep установлен в DEP_UNKONWN по умолчанию
						case DEP_COND_EXIST:
							isDep2Exist = DEP_EXIST;
						case DEP_COND_NOT_EXIST:
							if (depUnion == isDep2Exist)
								depUnionCond = dep2->GetCondition (depUnion);
							else 
								depUnionCond = &(!(*dep2->GetCondition (!depUnion))); 

							resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);
							break;
						case DEP_CONDITIONAL:
							depUnionCond = &(*dep2->GetCondition (depUnion));
							depIntCond = &(*dep2->GetCondition (!depUnion));								

							resDep->SetExistenceCond (!depUnion, depIntCond, DEP_EXACTLY);														
							resDep->SetExistenceCond (depUnion, depUnionCond, DEP_EXACTLY);
							break;		

						case DEP_COND_EXIST_UNKNOWN:
							isDep2Exist = DEP_EXIST;
						case DEP_COND_NOT_EXIST_UNKNOWN:
							if (depUnion == isDep2Exist)
								depUnionCond = &(*dep2->GetCondition (depUnion));
							//else depUnionCond = DEP_ALWAYS - задано по умолчанию
							resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);
							break;

						default: 
							throw ::Exception::IException ("UnionIntersect dependence error");
						}
						break;

					case DEP_ALWAYS_EXIST:	
#if DEBUG & DBG_DEP
						cout << "DEP_ALWAYS_EXIST"<<endl;
#endif
					case DEP_ALWAYS_NOT_EXIST: 
#if DEBUG & DBG_DEP
						cout << "DEP_ALWAYS_NOT_EXIST"<<endl;
#endif
						DELETE_POINTER (resDep)							
						resDep = (Dependence*)dep2->Clone (); //подправить ?????????????????????????????						
						break; //тип dep1 не совпадает с depUnion, а т. к. dep1 - точная, то ничего не изменится

					case DEP_COND_EXIST: 
						isDep1Exist = DEP_EXIST;						
					case DEP_COND_NOT_EXIST: //isDep1Exist установлен в DEP_NOT_EXIST по умолчанию						
						if (depUnion == isDep1Exist)
							depUnionCond = dep1->GetCondition (depUnion); 
						else 
							depUnionCond = &(!(*dep1->GetCondition (!depUnion))); 

						switch (dep2Type)
						{
						case DEP_COND_EXIST:
							isDep2Exist = DEP_EXIST;	
						case DEP_COND_NOT_EXIST: //isDep2Exist установлен в DEP_NOT_EXIST по умолчанию		
							if (depUnion == isDep2Exist) 
								depUnionCond = &((*dep2->GetCondition (depUnion)) || (*depUnionCond));								
							else
								depUnionCond = &(!(*dep2->GetCondition (!depUnion)) || (*depUnionCond));	
						
							resDep->SetExistenceCond (depUnion, depUnionCond, DEP_EXACTLY);
							break;

						case DEP_CONDITIONAL:
							depUnionCond = &(*dep2->GetCondition (depUnion) || (*depUnionCond));
							depIntCond = &(*dep2->GetCondition (!depUnion) && !(*depUnionCond));								
							resDep->SetExistenceCond (!depUnion, depIntCond, DEP_EXACTLY);														
							resDep->SetExistenceCond (depUnion, depUnionCond, DEP_EXACTLY);
							break;		
						
						case DEP_COND_EXIST_UNKNOWN:
							isDep2Exist = DEP_EXIST;
						case DEP_COND_NOT_EXIST_UNKNOWN: 							
							if (depUnion = isDep2Exist)
							{
								depUnionCond = &(*dep2->GetCondition (depUnion) || (*depUnionCond));								
								resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);
							}
							else 
							{
								depIntCond = &(*dep2->GetCondition (!depUnion) && !(*depUnionCond));								
								resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);
								resDep->SetExistenceCond (!depUnion, depIntCond, DEP_EXACTLY);								
							}
							break;																										

						default: throw ::Exception::IException ("UnionIntersect dependence error");
						}
						break;

					case DEP_CONDITIONAL:
						depUnionCond = dep1->GetCondition (depUnion);
						depIntCond = dep1->GetCondition (!depUnion);
						switch (dep2Type)
						{
						case DEP_COND_EXIST_UNKNOWN:
							isDep2Exist = DEP_EXIST;
						case DEP_COND_NOT_EXIST_UNKNOWN:
							if (depUnion == isDep2Exist)
							{
								depUnionCond = &(*dep2->GetCondition (depUnion) || *depUnionCond);
								resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);
							}
							else 
							{
								depIntCond = &(*dep2->GetCondition (!depUnion) && *depIntCond);
								resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);
								resDep->SetExistenceCond (!depUnion, depIntCond, DEP_EXACTLY);
							}
							break;

						case DEP_CONDITIONAL:
							depUnionCond = &(*dep1->GetCondition (depUnion) || *dep2->GetCondition (depUnion));
							depIntCond = &(*dep1->GetCondition (!depUnion) && *dep2->GetCondition (!depUnion));								

							resDep->SetExistenceCond (!depUnion, depIntCond, DEP_EXACTLY);														
							resDep->SetExistenceCond (depUnion, depUnionCond, DEP_EXACTLY);
							break;		
						
						default: throw ::Exception::IException ("UnionIntersect dependence error");
						}
						break;

					case DEP_COND_EXIST_UNKNOWN:
						isDep1Exist = DEP_EXIST;
					case DEP_COND_NOT_EXIST_UNKNOWN:
						if (depUnion == isDep1Exist)
							depUnionCond = dep1->GetCondition (depUnion);
						else 
							depIntCond = dep1->GetCondition (!depUnion);
						 
						switch (dep2Type)
						{
						case DEP_COND_EXIST_UNKNOWN:
							isDep2Exist = DEP_EXIST;
						case DEP_COND_NOT_EXIST_UNKNOWN:
							if (depUnion == isDep2Exist)
							{	if (depUnion == isDep1Exist)	
									depUnionCond = &(*dep2->GetCondition (depUnion) || *depUnionCond);							
								else depUnionCond = dep2->GetCondition (depUnion);
								resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);
							}
							else if (depUnion == isDep1Exist)							
								resDep->SetExistenceCond (depUnion, depUnionCond, DEP_NOT_EXACTLY);							
							else 
							{
								depIntCond = &(*dep2->GetCondition (!depUnion) && *depIntCond);
								resDep->SetExistenceCond (!depUnion, depIntCond, DEP_NOT_EXACTLY);
							}								
							break;

						default: throw ::Exception::IException ("UnionIntersect dependence error");
						}
						break;

					default: throw ::Exception::IException ("UnionIntersect dependence error");
					}

					return resDep;
				}

				Dependence& operator= (Dependence& dep)
				{
					this->isExists = dep.isExists;
					this->isExactly = dep.isExactly;

					DELETE_POINTER (this->existsCond);
					DELETE_POINTER (this->notExistsCond);
					
					if (!dep.existsCond) this->existsCond = NULL;
					else this->existsCond = dep.existsCond->Clone ();
					if (!dep.notExistsCond) this->notExistsCond = NULL;
					else this->notExistsCond = dep.notExistsCond->Clone ();

					return *this;					
				}

				void Print ()
				{
					cout << "dependence: ";
					
					switch (GetType ())
					{
					case DEP_UNKNOWN: cout << "POSSIBLE DEPENDENCE"; break;
					case DEP_ALWAYS_EXIST: cout << "EXACTLY DEPENDENCE"; break;
					case DEP_ALWAYS_NOT_EXIST: cout << "NO DEPENDENCE"; break;
					case DEP_COND_EXIST: cout << "if " << GetCondition (DEP_EXIST)->ToString () << \
											 "\nthen EXACTLY DEPENDENCE,\nelse NO DEPENDENCE"; break;
					case DEP_COND_NOT_EXIST: cout << "if " << GetCondition (DEP_NOT_EXIST)->ToString () << \
											 "\nthen NO DEPENDENCE,\nelse EXACTLY DEPENDENCE"; break;
					case DEP_CONDITIONAL: cout << "if " << GetCondition (DEP_EXIST)->ToString () << \
											 "\nthen EXACTLY DEPENDENCE,\nelse if " << \
											 GetCondition (DEP_NOT_EXIST)->ToString () << \
											 "\nthen NO DEPENDENCE,\nelse POSSIBLE DEPENDENCE"; break;
					case DEP_COND_EXIST_UNKNOWN: cout << "if " << GetCondition (DEP_EXIST)->ToString () << \
											 "\nthen EXACTLY DEPENDENCE,\nelse POSSIBLE DEPENDENCE"; break;
					case DEP_COND_NOT_EXIST_UNKNOWN: cout << "if " << GetCondition (DEP_NOT_EXIST)->ToString () << \
											 "\nthen NO DEPENDENCE,\nelse POSSIBLE DEPENDENCE"; break;
					default: throw ::Exception::IException ("unkonwn dependence type");
					}
					cout << endl;
				}
				
			};
		}
	}
}

#endif