#include <stdio.h>
#include <string.h>

#include <exception>
#include <fstream>
#include <iomanip>
#include <vector>
#include <math.h>
//====
#ifdef _MSC_VER
/*Windows*/
#include <io.h>
#else
/*Unix*/
#include <sys/types.h>
#include <dirent.h>
#endif
//=***
 
#include "Ver.h"
#include "Ps.h"
#include "TraceLine.h"
#include "FuncCall.h"
#include "Interval.h"
#include "Vm.h"
#include "ModelStructs.h"
using namespace std;


ofstream prot; 
int search_opt_mode;

vector<long>	SizeArray;

//====
extern long StrToLong(char* str, int base);

struct tr_line
{ int func_id;
	double time;
	char *mask;
	long **extra_koef;
};
//=***

// External functions

extern void		SaveHTMLInterval(ofstream hfile);

extern void		TraceParsingCleanup();
extern			FuncType GetFuncType(Event func_id);
ofstream		hfile;
extern double grig_time_call;
extern long currentAM_ID;


//grig
typedef std::vector<long> long_vect;
typedef std::vector<long_vect> long2_vect;
long_vect MinSizesOfAM; // для автоматического поиска

extern bool FirstTrace;
extern _PSInfo			*PSInfo	;
extern _AMInfo			*AMInfo	;
extern _AMViewInfo		*AMViews;

void resetInfos()
{
_PSInfo::count		= 0;
_AMInfo::count		= 0;
_AMViewInfo::count	= 0;
if(PSInfo!=NULL) {free(PSInfo); PSInfo=NULL;}
if(AMInfo!=NULL) {free(AMInfo); AMInfo=NULL;}
if(AMViews!=NULL) {free(AMViews); AMViews=NULL;}
}

//\grig
	
/*
void ModelExec(VectorTraceLine * tl)
{ 
 	FuncCall * func_call;
	while (!tl->end()) {
		func_call = new FuncCall(tl);

		FuncType func_type = GetFuncType(func_call->func_id);

#ifdef P_DEBUG
			prot << " func_id = " << func_call->func_id
				 << " time = " << procElapsedTime[0]
				 << " file = " << func_call->source_file 
				 << " line = " << func_call->source_line
				 << endl;
#endif

		if (func_call->func_id == Event_dvm_exit)
			return;

		switch(func_type) {
			case __IntervalFunc :
			  func_call->IntervalTime();
			  break;
			case __IOFunc :
			  func_call->IOTime();
			  break;
			case __MPS_AMFunc :
			  func_call->MPS_AMTime();
			  break;
			case __DArrayFunc :
			  func_call->DArrayTime();
			  break;
			case __ShadowFunc :
			  func_call->ShadowTime();
			  break;
			case __ReductFunc :
			  func_call->ReductTime();
			  break;
			case __ParLoopFunc :
			  func_call->ParLoopTime();
			  break;
			case __RemAccessFunc :
			  func_call->RemAccessTime();
			  break;
			case __RegularFunc :
			  func_call->RegularTime();
			  break;
			case __UnknownFunc :
			  func_call->UnknownTime();
			  break;
		}
		delete func_call; 
	}
}
*/
void CreateHTMLfile()
{
	//====// сколько цифр после запятой
    hfile << setiosflags(ios::fixed) << setprecision(3);
	
	// Write intervals in output file
	if (CurrInterval->count == 0) {
		// there is no nested intervals
		CurrInterval->SaveTree(hfile, 1, CurrInterval->ID, CurrInterval->ID);
	} else {
		CurrInterval->SaveTree(hfile, 1, 
			CurrInterval->nested_intervals[0]->ID, 
				CurrInterval->nested_intervals[CurrInterval->count - 1]->ID);
	}

	// close output file
	hfile.close();
}


static void message()
{
	std::cerr << "ERROR  : missing required command line parameter." << endl;
	std::cerr << "SYNTAX : predictor <param_file> <trc_file> <html_file> <processors>" << endl;
	std::cerr << "where  : <param_file> - parameter file name," << endl;
	std::cerr << "       : <trc_file> - trace file name" << endl;
	std::cerr << "       : <html_file> - resulting HTML file name," << endl;
	std::cerr << "       : <processors> - processors topology," << endl; 
	std::cerr << "                        i.e. extension on each dimension," << endl;
	std::cerr << "                        separated by the space." << endl;
	exit(EXIT_FAILURE);
}


void Getsimplefactors(std::vector<long> & result,int N)   // получить все простые множители!!!
{
	int i;
	int del1;
	int tempN;

	result.resize(0);
	tempN=N;
     
	i=1;
	while(true)
	{
		if(i>sqrt(N)) break;
		del1=tempN/i;
		if(i*del1==tempN) //- делитель
		{
//			printf("%d ",i);
			tempN=del1;
			result.push_back(i);		
			if(i==1)
				i++;
		}		
		else
			i++;
	}
	if(tempN!=1)
	{
	result.push_back(tempN);
//	printf("%d ",tempN);
	}

//	printf("\n");
}

void GetAllFactors(std::vector<long>& result,int N)   // получить все делители числа
{
	int i;
	int i1;
	result.resize(0);
	for(i=1;i<=N;i++)
	{
		i1=N/i;
		if(i1*i==N) result.push_back(i);
	}
}

void getRNK(std::vector<long> res,int N,int K,std::vector<long_vect>& glob_res) // получить разложение N на K множителей
{
	if(K==1)
	{
		std::vector<long> temp1;
		temp1=res;
		temp1.push_back(N);
	  //res.push_back(N);
	  glob_res.push_back(temp1);
	}
	else
	{
	  std::vector<long> temp_fact;
 	  GetAllFactors(temp_fact,N);
	  for(int i=0;i<temp_fact.size();i++)
	  {
		  std::vector<long> temp_2;
		  temp_2=res;
		  temp_2.push_back(temp_fact[i]);		  
		  getRNK(temp_2,N/temp_fact[i],K-1,glob_res);
	  }
	}
}

void getNK(std::vector<long_vect>& res,int N,int K)   // получить все разложения N на K множителей
{
	res.resize(0);
	std::vector<long> temp;
	temp.resize(0);
	getRNK(temp,N,K,res);
}

bool MakeAllConfigurations(int proc_number,int rank,std::vector<long_vect>& result)
{
	// получить разложение  proc_number на множители
	// проверить количество  этих множителей 
	// если их меньше чем ранк  то не судьба 	
	//==// а точнее, такая конфигурация уже встречается при меньшем ранге, 
	//==// поэтому если мы пробегаем по всем рангам, то не стоит этого делать еще раз, а если не пробегаем, то надо сделать
	//==// я выбрал путь не пробегать !
	std::vector<long> factors;

	Getsimplefactors(factors,proc_number);

//==//	if(factors.size()<rank)		return false;

	getNK(result,proc_number,rank);
	return true;
}

float GetEuristik(long j, long a_size /*, long p, long first_p, long last_p*/)
{
	long q;
	double ost;

	q=(long)ceil(((float)a_size)/j);
	ost=(double)((a_size%q)?(a_size%q):q);

	if(q*(j-1)+ost>a_size)// то есть на последнем проце нет элементов, потому что все разобрали раньше, 
		ost=0; //	что уступает всегда случаю с меньшим количеством процессоров

	ost/=q;

	return ost;

}

int CheckEuristik(std::vector<long> & who)
{ bool mode=0, flag=1;
	int i;
	double ost, min_ost=10001;

	for(i=0;i<who.size();i++)
	{
		if(who[i]>MinSizesOfAM[i])	return 0; // always bad
	}

	for(i=0;i<who.size();i++)
	{

		ost=GetEuristik(who[i],MinSizesOfAM[i]);
		
		if(ost<min_ost) min_ost=ost;
	}

	if(mode) for(int ii=0;ii<who.size();ii++) printf("%d ",who[ii]); 
		
	return (int)(min_ost*10000); 
}  

bool IsBestConfiguration(Interval* best,Interval * current)
{
//	prot<<"curr="<<current->GetEffectiveParameter() <<"; best="<<best->GetEffectiveParameter()<<"\n";
	if(best->GetEffectiveParameter() <= current->GetEffectiveParameter())
		return false;
	return true;
}

