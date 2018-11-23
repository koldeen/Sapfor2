#ifndef CommCostH
#define CommCostH

//////////////////////////////////////////////////////////////////////
//
// CommCost.h: interface for the CommCost class.
//
//////////////////////////////////////////////////////////////////////

#include <cmath>
#include <vector>
#include <algorithm>

#include "Vm.h"
#include "DArray.h"
#include "DimBound.h"

//====
#include "LoopBlock.h"
//=***

typedef std::vector<long> lvector;
typedef std::vector<lvector> Dim2Array;


class VM;
class Block;
//====
class LoopBlock;
//=***

// коммуникационные издержки
class CommCost {  

public:


	// массив содержащий информацию о количестве байтов 
	// пересылаемых между парой процессоров виртуальной машины vm 
	Dim2Array transfer;	
	VM *vm;  
	
	CommCost(VM *Avm);
	CommCost();
	virtual ~CommCost();

	// копирование распределенного массива на все процессоры
	void CopyUpdate(DArray *FromArray, Block & readBlock);
//====
	void CopyUpdateDistr(DArray * FromArray, Block &readBlock, long p1);
	long GetLSize();
//	void calculate(); //убрать так как это внутренн€€ функци€
	void Across(double call_time, long LoopSZ, LoopBlock** ProcBlock,int type_size);
//=***

	void BoundUpdate(DArray *daPtr, std::vector<DimBound> & dimInfo, bool IsCorner);

	// машиннозависима€ функци€ возвращающа€ стоимость 
	// накладнных расходов доступа к удаленным данным
	double GetCost();

	CommCost & operator =(const CommCost &);

	// измен€ет массив transfer в соответствии
	// с возникающими пересылками между процессорами VM в результате 
	// перехода от одного распределени€ массива к другому
	void Update(DArray *oldDA, DArray *newDA);

};


#endif 
