#pragma once

#include <vector>
using namespace std;

typedef std::vector<long> long_vect; 
typedef std::vector<int> int_vect;

//========================================== Structs Info ===================================================

// Common CallInfo structures

struct IDOnlyInfo {
   long ID;
};

// Interval structures

struct binter_Info {
    long	line;
    char *	file;
	long	index;

	~binter_Info() { delete file; }
};

typedef struct IDOnlyInfo  einter_Info;

// Message sending structures

typedef struct IDOnlyInfo  rtl_BarrierInfo;

struct rtl_BcastInfo {
    long	Count; 
	long	Size;
};

// MPS/AM/AMView structures 

typedef struct IDOnlyInfo  CreateVMSInfo;
typedef struct IDOnlyInfo  getam_Info;

struct crtps_Info {
	long				PSRef;			// ID
	long				PSRefParent;
	std::vector<long>	InitIndexArray;
	std::vector<long>	LastIndexArray;	 
	long				StaticSign;
};

struct getps_Info {
	long				PSRef;
	long				AMRef;
};

struct psview_Info {
	long				PSRef;			// ID
	long				PSRefParent;
	long				Rank;
	std::vector<long>	SizeArray;
	long				StaticSign;
};

struct setelw_Info {
	long				PSRef;			// 16
	long				AMViewRef;		// 16
	long				AddrNumber;		// 10
	std::vector<long>	WeightNumber;
	// length = sun i = [0,AddrNumber-1] WeightNumber[i]  
	std::vector<double>	LoadWeight;
};

typedef struct IDOnlyInfo  delps_Info;

struct getamr_Info {
	long				AMRef;			// ID
	long				AMViewRef;
	std::vector<long>	IndexArray;		
};

struct getamv_Info {
	long				ArrayHeader;	// ArrayHeader
	long				AMViewRef;
};

struct mapam_Info {
	long				AMRef;	
	long				PSRef;
};

typedef struct IDOnlyInfo  runam_Info;

struct crtamv_Info {
    long				ID;				// AMViewRef
    long				AM_ID;			// AMRef
	long				StaticSign;		// StaticSign
	std::vector<long>	SizeArray;		// Rank + SizeArray
};

typedef struct IDOnlyInfo  delamv_Info;

//====
struct blkdiv_Info {
	long				ID;				// AMViewRef
	std::vector<long>	AMVAxisDiv;		// AMVAxisDiv[]
};
//=***
 
struct distr_Info {
    long				ID;				// AMViewRef
	long				PSRef;			// PSRef
	std::vector<long>	AxisArray;		// AxisArray[]
	std::vector<long>	DistrParamArray;// DistrParamArray[]
};

struct redis_Info {
	long				ID;				// AMViewRef
	long				AID;			// ArrayHeader
	long				PSRef;			// PSRef
	std::vector<long>	AxisArray;		// AxisArray[]
	std::vector<long>	DistrParamArray;// DistrParamArray[]
    long				NewSign;
};

// DArray structures

struct crtda_Info {
    long				ArrayHandlePtr;	// ArrayHandlePtr
	long				ArrayHeader;	// ArrayHeader
    long				TypeSize;
	long				StaticSign;		//
	long				ReDistrSign;	//
	std::vector<long>	SizeArray;
	std::vector<long>	LowShdWidthArray;
	std::vector<long>	HiShdWidthArray;
};

struct align_Info
{
	long				ArrayHeader;	// ArrayHeader
	long				ArrayHandlePtr;	// ArrayHandlePtr
	long				PatternRefPtr;	// PatternRefPtr
	long				PatternRef;		// PatternRef
	int					PatternType;	// AMView = 1, DisArray = 2
    std::vector<long>	AxisArray;
	std::vector<long>	CoeffArray;
	std::vector<long>	ConstArray;
};

typedef struct IDOnlyInfo  delda_Info;

struct realn_Info {
	long				ArrayHandlePtr;	// ArrayHandlePtr
	long				ArrayHeader;	// ArrayHeader
	long				PatternRefPtr;	// PatternRefPtr
	long				PatternRef;		// PatternRef
	int					PatternType;	// AMView = 1, DisArray = 2
    std::vector<long>	AxisArray;
    std::vector<long>	CoeffArray;
    std::vector<long>	ConstArray;
    long				NewSign;
};

struct arrcpy_Info {

	long				FromBufferPtr;
	long				FromArrayHeader;
	long				FromArrayHandlePtr;
    std::vector<long>	FromInitIndexArray;
	std::vector<long>	FromLastIndexArray;
	std::vector<long>	FromStepArray;

	long				ToBufferPtr;
	long				ToArrayHeader;
	long				ToArrayHandlePtr;
    std::vector<long>	ToInitIndexArray;
	std::vector<long>	ToLastIndexArray;
	std::vector<long>	ToStepArray;

    long				CopyRegim;
	long				CopyFlagPtr;
};

struct waitcp_Info {
	long CopyFlagPtr;
};

// ParLoop structures

struct crtpl_Info {
    long	ID;
    long	Rank;
};

struct mappl_Info {
    long				LoopRef;		//ID; 
	long				PatternRefPtr;
	long				PatternRef;
	int					PatternType;	// AMView = 1, DisArray = 2
    std::vector<long>	AxisArray;
    std::vector<long>	CoeffArray;
    std::vector<long>	ConstArray;
    std::vector<long>	InInitIndexArray;
    std::vector<long>	InLastIndexArray;
    std::vector<long>	InStepArray;
};

typedef struct IDOnlyInfo  dopl_Info;
typedef struct IDOnlyInfo  endpl_Info;

//grig
struct  dopl_full_Info
{
  long ID;
  std::vector<long>   Dim;
  std::vector<long>   Step;
  std::vector<long>   Lower;
  std::vector<long>   Upper;
	long ReturnVar; // DoPL //====//
};
//\grig

// Reduction structures

typedef struct IDOnlyInfo  crtrg_Info;

struct crtred_Info {
	long	ID;
    long	RedArrayType; 
	long	RedArrayLength; 
	long	LocElmLength;
};

struct insred_Info {
	long	RG_ID; 
	long	RV_ID;
};

typedef struct IDOnlyInfo  delrg_Info;
typedef struct IDOnlyInfo  delred_Info;
typedef struct IDOnlyInfo  strtrd_Info;
typedef struct IDOnlyInfo  waitrd_Info;

// Shadow structures

struct crtshg_Info {
	long StaticSign;
	long ShadowGroupRef;
};

struct inssh_Info {
	char event_func;
//	Event				func;				// function ID
    long				ShadowGroupRef;		// SHG_ID;
	long				ArrayHeader;		//
	long				ArrayHandlePtr;		// DA_ID;
    long				FullShdSign;		// only for inssh_, incsh_
	long				MaxShdCount;		// only for insshd_, incshd
	std::vector<long>	ShdSignArray;		// for insshd_, incshd_

    std::vector<long>	LowShdWidthArray;
	std::vector<long>	HiShdWidthArray;

    std::vector<long>	InitDimIndex;
	std::vector<long>	LastDimIndex;

    std::vector<long>	InitLowShdIndex;
	std::vector<long>	LastLowShdIndex;

    std::vector<long>	InitHiShdIndex;
	std::vector<long>	LastHiShdIndex;
};

struct exfrst_Info{
	long			ID;					// LoopRef
	long			ShadowGroupRef;
};

struct imlast_Info{
	long			ID;					// LoopRef
	long			ShadowGroupRef;
};

struct across_Info {
	long	AcrossType; 
	long	OldShadowGroupRef; 
	long	NewShadowGroupRef; 
	double	PipeLinePar;

	long	CondPipeLine;
	long	ErrPipeLine;
	long	PipeLinePLAxis;
};

/*
AcrossType=1; 
OldShadowGroupRef=9b7ac0;
NewShadowGroupRef=9b77c0;
PipeLinePar=0.000000;
CondPipeLine=0 
ErrPipeLine=60
*/

typedef struct IDOnlyInfo  delshg_Info;
typedef struct IDOnlyInfo  strtsh_Info;
typedef struct IDOnlyInfo  waitsh_Info;
typedef struct IDOnlyInfo  sendsh_Info;
typedef struct IDOnlyInfo  recvsh_Info;

// Regular access to remote data

struct crtrbl_Info {
	long	RemArrayHeader;
	long	BufferHeader;
	long	StaticSign;
	long	LoopRef;
	std::vector<long>	AxisArray;  
	std::vector<long>	CoeffArray;  
	std::vector<long>	ConstArray;  
};

struct crtrbp_Info {
	long	ID;			//	BufferHeader;
	long	RemArrayHeader;
	long	StaticSign;
	long	PSRef;
	long	IsLocal;
	std::vector<long>	CoordArray;  
};

struct loadrb_Info {
	long	ID;			//	BufferHeader;
	long	RenewSign;
};
 
typedef struct IDOnlyInfo  waitrb_Info;

struct srmem_Info {
	long				MemoryCount;
	std::vector<long>	LengthArray;  
};

// Root info
struct root_Info {
     long VProcCount;
     long VPSRank;
     std::vector<long>	VPSSize;
};


//================================================ Classes ===========================================================



enum Event {

   Unknown_Func					= -1,
   Root_func					= 0,
   dvm_Init,
   Event_dvm_exit,

	 //====
	 blkdiv_,
	 //=***

   delrg_,
   insred_,
   arrcpy_,
   aarrcp_,
   waitcp_,
   crtda_,
   getam_,
   crtamv_,
   align_ ,
   getps_,
   saverv_,
   tstelm_,
   rwelm_,
   rlocel_,
   delda_,
   delobj_,
   copelm_,
   elmcpy_,
   wlocel_,
   clocel_,
   getlen_,
   tron_,
   delamv_,
   distr_,
   crtred_,
   delred_,
   begbl_,
   endbl_, 
   crtpl_,
   mappl_,
   endpl_,
   locind_,
   tstda_,
   srmem_, 
   tstio_, 
   getrnk_,
   getsiz_,
   realn_,
   redis_,
   arrmap_,
   setpsw_,
   setind_,
   locsiz_,
   imlast_,
   malign_,
   crtrg_,
   mrealn_,
   strtrd_,
   waitrd_,
   amvmap_,
   exfrst_,
   dopl_,
   mdistr_,
   mredis_,
   delarm_,
   delmvm_,

   crtshg_,
   inssh_,
   insshd_,
   incsh_,
   incshd_,
   strtsh_,
   waitsh_,
   delshg_,
   recvsh_,
   sendsh_,
   across_,

   getind_,
   addhdr_,
   delhdr_,
   troff_,
   biof_,
   eiof_,

   crtps_,
   psview_,
   delps_,
   setelw_,
   getamv_,	
   mapam_,	
   runam_,	
   stopam_,	
   getamr_,
   dprstv_,
   dstv_,
   dldv_,
   dbegpl_,
   dbegsl_,
   dendl_,
   diter_,
   drmbuf_,
   dskpbl_,

   binter_,
   einter_,
   bsloop_,
   bploop_,
   eloop_,

   crtrbl_,
   crtrbp_,
   loadrb_,
   waitrb_,
   crtbg_,
   insrb_,
   loadbg_,
   waitbg_,

   dvm_fopen,
   dvm_fclose,
   dvm_void_vfprintf,
   dvm_vfprintf,
   dvm_fwrite,
   dvm_fread,
   dvm_vscanf,
   dvm_fscanf,
   dvm_scanf,
   dvm_vfscanf,
   dvm_clearerr,
   dvm_feof,
   dvm_ferror,
   dvm_fflush,
   dvm_fgetc,
   dvm_fgetpos,
   dvm_fgets,
   dvm_fputc,
   dvm_fputs,
   dvm_freopen,
   dvm_fseek,
   dvm_fsetpos,
   dvm_ftell,
   dvm_getc,
   dvm_getchar,
   dvm_gets,
   dvm_putc,
   dvm_putchar,
   dvm_puts,
   dvm_rewind,
   dvm_setbuf,
   dvm_setvbuf,
   dvm_tmpfile,
   dvm_ungetc,
   dvm_void_fprintf,
   dvm_fprintf,
   dvm_void_printf,
   dvm_printf,
   dvm_void_vprintf,
   dvm_vprintf,
   dvm_remove,
   dvm_rename,
   dvm_tmpnam,
   dvm_close,
   dvm_fstat,
   dvm_lseek,
   dvm_open,
   dvm_read,
   dvm_write,
   dvm_access,
   dvm_stat,
   mps_Bcast,
   mps_Barrier,
   dvm_dfread,
   dvm_dfwrite
};
//============================================= Class FuncCall =======================================================

// Structure for the final stage of file parsing -- call graph with parameters

class FuncCall
{
public:
	// было такое поле в предикторе, а его решил заменить на char					Event		func_id;		// function identifier
//	char event; // не слишком правильно, так как надо было написать тип Event, а это повлекло бы описание всех событий, что в принципе не нужно в библиотеке
	//нельзя заменять - от него зависит деструктор и могут быть несовместимости типов

	Event		func_id;
	double		call_time;		// call time
	double		ret_time;		// return time
	void	*	call_params;	// pointer to structure with function params
	int			source_line;
	char	*	source_file;

	//grig
	vector<double> vcall_time;
	vector<double> vret_time;
	//\grig

 
public:

	FuncCall();
	~FuncCall();

	void RegularTime();
	void UnknownTime();
	void IntervalTime();
	void DArrayTime();
	void crtda();
	void align();
	void delda();
	void realn(); 
	void arrcpy();
	void aarrcp();
	void waitcp();
	void MPS_AMTime();
	void crtps();
	void psview();
	void getps();
	void setelw();
	void delps();
	void getam();
	void getamr();
	void crtamv();
	void delamv();
	void mapam();
	void runam();
	void stopam();
	void blkdiv();
	void distr();
	void RedisTime();

	void ParLoopTime();
	void crtpl();
	void endpl();
	void mappl();
	void dopl();
	void ReductTime();
	void crtrg();
	void crtred();
	void insred();
	void delred();
	void delrg();
	void strtrd();
	void waitrd();
	void across();
	void ShadowTime();
	void crtshg();
	void inssh();
	void insshd();
	void incsh();
	void incshd();
	void delshg();
	void strtsh();
	void waitsh();
	void exfrst();
	void imlast();
	void sendsh();
	void recvsh();
	void IOTime();
	void ciotime();
	void biof();
	void tstio();
	void srmem();
	void eiof();
	void RemAccessTime();
//	void crtbl();
	void crtrbl(); 
	void crtrbp();
	void loadrb();
	void waitrb();
};


//============================================== class Space ===========================================================

#include <algorithm>
#include <fstream>

class Space
{
protected:
	std::vector<long> SizeArray;	// Size of every dimension
	std::vector<long> MultArray;	// Multiplier for each dimension
public:
	Space();
	Space(const std::vector<long>& ASizeArray, std::vector<long> AMultArray);
	Space(const Space &);
 	Space(const std::vector<long>& ASizeArray);
	~Space();

	// еще в этом классе были функции, но они не нужны пользователю библиотеки, а только для реализации других функций библиотеки
};


//================================================ class VM ============================================================

enum mach_Type {
	mach_ETHERNET,			// 0
	mach_TRANSPUTER,		// 1
	mach_MYRINET			// 2
};

class VM : public Space {

	const	VM*			parent;		// pointer to parent VM
	mach_Type			MType;		// system type: 0 - network, 1 - transputers, 2 - myrinet
	int					numChanels;	// number of chanells for myrinet
	double				scale;
	double				TStart;		// информация о реальной машине:  start time
	double				TByte;		// информация о реальной машине:  byte trasfer time
	double				ProcPower;	// relative VM power 
	int					ProcCount;	// number of processors in VM
	std::vector<int>	mapping;	// map to absolute processors numbers
	std::vector<double> weight;		// vector - PS weights		
		
	// calculates number of processors in VM
	int		procCount();


//grig
	std::vector<double> vProcPower; // относительные производительности процессоров
	std::vector<double> vWeights;   // веса элементов измерений установленные процессорной системы
public:



	void SetvWeights(std::vector<double> & varray) { 
		  vWeights.resize(0);
		  vWeights.resize(varray.size());
		for(int i=0;i<varray.size();i++)
			vWeights[i]=varray[i];
	}
	double	getProcPower(int k) { return vProcPower[this->map(k)];}
//\grig

public:
	
	// constructor for root VM
	VM(const std::vector<long>& ASizeArray, mach_Type AMType, int AnumChanels, 
		double Ascale, double ATStart, double ATByte, double AProcPower, std::vector<double>& AvProcPower);

	// constructor for child VM (crtps_)
	VM(const std::vector<long>& lb, const std::vector<long>& ASizeArray, const VM* Aparent);

	// constructor for child VM (psview_)
	VM(const std::vector<long>& ASizeArray, const VM* Aparent);

	//grig!!!!
	VM(const std::vector<long>& ASizeArray, mach_Type AMType, int AnumChanels, 
		double Ascale, double ATStart, double ATByte,  std::vector<double>& AvProcPower);
	//\grig

	// Destructor
    ~VM();

	double	getTByte() const { return TByte; }
	double	getTStart() const { return TStart; }
	int		getMType() const { return MType; }
	int		getProcCount() const { return ProcCount; }
//comment by grig	double	getProcPower() const { return ProcPower; }
	double	getProcPower() const { return 0; }
	int		getNumChanels() const { return numChanels; }
	double	getScale() const { return scale; }
	const	std::vector<long>& getSizeArray() const { return SizeArray; }
	int		map(int i) const { return mapping[i]; }

	// Set weights for VM
	void setWeight(const std::vector<double>& Aweight);

};

extern VM	*	rootVM;			// pointer to root VM
extern VM	*	currentVM;		// pointer to current VM

inline int	MPSProcCount() { return currentVM->getProcCount(); }


//================================================ class PS ============================================================
#include <iostream>
#include <queue>
#include <string>

//grigory add-on 
using namespace std;

void ClustError (int num_error);

struct ProcInfo
{
	int numClust;
	int numInClust;
	double ProcPower;
};

typedef  struct ProcInfo strProcInfo;

class ClustInfo
{
public :
	int numClust;
	vector <strProcInfo> Procs;
	ClustInfo();
	ClustInfo(int num);
	void AddProc(int num,double power);
	void setNum(int num) {this->numClust=num;}
	//доделать
	void setTStart(double tstart);
	void setTByte(double tbyte);
	//доделать

};

typedef class ClustInfo  classClustInfo;

class CompletePS
{
public :
	vector<classClustInfo> Clusters;
	CompletePS();
	void MakeNewCluster(int numClust);
	void AddProcToClust(int numClust,int numProc,strProcInfo procInfo);	
	void MakeFullMapping(std::vector<double>& result);
	void SortProcessors(std::vector<double> &array_of_productivity);
	
};

class MappedProcs
{
public:
	vector<strProcInfo> Processors;
	void AddProc(strProcInfo& procInfo);
	MappedProcs() ;
	void AddProccessors(int start,int end,int step , ClustInfo &cPS);
};
	//\grigory add-on


typedef std::vector<long> LongVector;
typedef std::vector<double> DoubleVector;

class PS {

	static bool NextOptionLine(std::istream& opt_file, std::string& buffer);

	std::queue<LongVector>		ps_lb_list;		// low bounderies on each dim	 
	std::queue<LongVector>		SizeArray_list;	// extentions  on each dim
	std::queue<DoubleVector>	weight_list;	// list of vectors - PS weights

	mach_Type	Type;
	int			numChanels;		// numbers of parallel chanels in Myrinet
	double	TStart,                                   
					TByte,                                    
					ProcPower,
					scale;	

	//grigory add-on 
public :
	CompletePS completePS;    // процессорная система без учета первого отображения 
	MappedProcs mappedProcs;  // отображенные пользователем процессоры(будут использоваться в сисиетме)
	//std::vector<LongVector> vWeights;
	vector<double> vProcPower;// процессорные мощности процессоров , на которых должна быть выполнена программа

public:
	int getProcCount();
	void CorrectMappedProcs();
	void  PrepareForAutoSearch(std::vector<long>& perstanovki);
	void reset();
	
	//\grigory add-on



	// read PS's configurations from the file
	PS(const char* file_name);
	PS(mach_Type AType, int AnumChanels, double TStart, double TByte, int proc_num);


	// returns next processor's charactiristics
	void	nextPS(std::vector<long>& lb, std::vector<long>& ASizeArray, 
				   mach_Type& AMType, int& AnumChanels, double& Ascale, 
				   double&	ATStart, double&  ATByte, double& AProcPower, vector<double>& AvProcPower);
	void	setTopology(std::vector<long>& ASizeArray);
	void	hardwarePS(int& AMType, double&	ATStart, double&  ATByte, double& AProcPower,vector<double> & AvProcPower);

};

extern	PS *	ps;					// prosessor system object
extern	long	currentPS_ID;		// current PS ID


//============================================ Class Processor =====================================================
enum TimeType {
	  __IO_time = 1,
	  __CPU_time,
	  __CPU_time_sys,
	  __CPU_time_usr,
	  __Wait_reduct,
	  __Wait_shadow,
	  __Remote_access,
	  __Remote_overlap,
	  __Redistribute,
	  __IO_comm,
	  __Other_comm,
	  __Insuff_parall_sys,
	  __Insuff_parall_usr,
	  __Synchronize,
		__Variation,
	  __Reduct_overlap,
	  __Shadow_overlap,
};


class Processor {

	friend class Interval;
public:
	double
		Lost_time,
		Insuff_parallelism,			// Insuff_parallelism_usr + Insuff_parallelism_sys
		Insuff_parallelism_usr,		// User insufficient parallelism
		Insuff_parallelism_sys,		// System Insufficient parallelism 
		Idle,						// Idle time
		Communication,				// Communications
		Synchronization,			// Synchronization
		Real_synchronization,		// Synchronization
		Variation,					// Time  variation
		Overlap,					// Overlap
		Load_imbalance,				// Load imbalance
		Execution_time,				// Execution time
		CPU_time,					// CPU_time_usr + CPU_time_sys
		CPU_time_usr,				// Usefull processor time			
		CPU_time_sys,				// Usefull system time			
		IO_time,
		
		IO_comm,					// IO: Communications
		IO_real_synch,					// IO: Real synch
		IO_synch,					// IO: Synchronization
		IO_vary,					// IO: Time variation
		IO_overlap,					// IO: Overlap
		
		Wait_reduction,				// Reduction: Communications
		Reduction_real_synch,				// Reduction: Real synch
		Reduction_synch,					// Reduction synchronization
		Reduction_vary,					// Time variation
		Reduction_overlap,				// Reduction: Overlap
		
		Wait_shadow,				// Shadow: Communications
		Shadow_real_synch,				// Shadow: Real synch
		Shadow_synch,					// Shadow synchronization
		Shadow_vary,					// Time variation
		Shadow_overlap,				// Shadow: Overlap
		
		Remote_access,				// Remote access: Communications
		Remote_real_synch,				// Remote access: Real synch
		Remote_vary,				// Remote access: Time variation
		Remote_synch,				// Remote access: synchronization
		Remote_overlap,				// Remote access: Overlap
		
		Redistribution,				// Redistribution: Communications
		Redistribution_real_synch,		// Redistribution: Real synch
		Redistribution_synch,		// Redistribution: synchronization
		Redistribution_vary,		// Redistribution: time vary
		Redistribution_overlap;		// Redistribution: Overlap
		

public:

	Processor();
	~Processor() {}

};

extern double	*	procElapsedTime;	// processor's elapsed times vector

//============================================ Class Interval ======================================================
enum IntervalType {
	  __IT_MAIN = 0,
	  __IT_SEQ,
	  __IT_PAR,
	  __IT_USER
};

enum PredType{
	_Lost_time,
	_Insuff_parallelism,
	_Insuff_parallelism_usr,		// User insufficient parallelism
	_Insuff_parallelism_sys,		// System Insufficient parallelism 
	_Idle,						// Idle time
	_Communication,				// Communications
	_Synchronization,			// Synchronization
	_Real_synchronization,		// Synchronization
	_Variation,					// Time  variation
	_Overlap,					// Overlap
	_Load_imbalance,				// Load imbalance
	_Execution_time,				// Execution time
	_CPU_time,					// CPU_time_usr + CPU_time_sys
	_CPU_time_usr,				// Usefull processor time			
	_CPU_time_sys,				// Usefull system time			
	_IO_time,
	
	_IO_comm,					// IO: Communications
	_IO_real_synch,					// IO: Real synch
	_IO_synch,					// IO: Synchronization
	_IO_vary,					// IO: Time variation
	_IO_overlap,					// IO: Overlap
		
	_Wait_reduction,				// Reduction: Communications
	_Reduction_real_synch,				// Reduction: Real synch
	_Reduction_synch,					// Reduction synchronization
	_Reduction_vary,					// Time variation
	_Reduction_overlap,				// Reduction: Overlap
		
	_Wait_shadow,				// Shadow: Communications
	_Shadow_real_synch,				// Shadow: Real synch
	_Shadow_synch,					// Shadow synchronization
	_Shadow_vary,					// Time variation
	_Shadow_overlap,				// Shadow: Overlap
	
	_Remote_access,				// Remote access: Communications
	_Remote_real_synch,				// Remote access: Real synch
	_Remote_vary,				// Remote access: Time variation
	_Remote_synch,				// Remote access: synchronization
	_Remote_overlap,				// Remote access: Overlap
		
	_Redistribution,				// Redistribution: Communications
	_Redistribution_real_synch,		// Redistribution: Real synch
	_Redistribution_synch,		// Redistribution: synchronization
	_Redistribution_vary,		// Redistribution: time vary
	_Redistribution_overlap,		// Redistribution: Overlap

	_Total_time,
	_Efficiency,
	_Productive_time,
	_Productive_CPU_time,
	_Productive_SYS_time
};

class Interval : public Processor {

	static int		Intervallevel;			// current interval level
	static int		IntervalID;				// current interval ID

	IntervalType	type;					// Interval type
	long			index;
	int				level;					// Interval level
	int				EXE_count;
	int				source_line;
	int				ID;

	//for intelval's tree
	Interval	*	parent_interval;
	int				count;
	Interval	**	nested_intervals;

	Processor	**	Procs;	// processor's vector

	double			Total_time;
	double			Efficiency;
	double			Productive_time;
	double			Productive_CPU_time;
	double			Productive_SYS_time;

public: 

	char *			source_file; //==//
	bool			io_trafic;		// start FORTRAN I/O
	int				num_op_io;
	int				num_op_reduct;
	int				num_op_shadow;
	int				num_op_remote;
	int				num_op_redist;
	char			*html_title;
		
	Interval(int arg); // только чтобы отличаться от конструктора по умолчанию (который настроен на строки трассы)
	// тут еще был конструктор по трассе, но он не нужен для пользователя, так как нет трассы
	~Interval();

	void		AddTime(TimeType InfoType, int proc_no, double TimeDelta);

	void		AddMPSTime(TimeType InfoType, double TimeDelta);
	//grig
	void        AddMPSTime(TimeType InfoType, std::vector<double> vTimeDelta);
	double      GetExecTime(); // получить время выполнения
	double      GetEffectiveParameter(); // получить показатель по которому сраниваются характеристики
	//\grig
	void		AddTimeSynchronize(TimeType InfoType, int proc_no, double TimeDelta);
	void		AddTimeVariation(TimeType InfoType, int proc_no, double TimeDelta);
	void		CalcIdleAndImbalance();
	static void Enter(IntervalType int_type, int line, char* file, long index);
	static void Leave();
	void		Integrate();
	void		SaveInFile(std::ofstream& hfile, int up, int next, int pred);
	void		SaveTree(std::ofstream&	hfile, int up, int next, int pred);
	void		setIOTrafic()  { io_trafic = true; }
	void		resetIOTrafic()  { io_trafic = false; }

	//====
	int copy(Interval* from);
	int copy_poss(Interval* from, double p1, double p2);
	double GetProcPred(int proc_no, PredType pred);
	double GetPred(PredType pred);
	//=***
	friend void CreateHTMLfile();
};

extern Interval * CurrInterval;			// pointer to current interval

//==================================================================================================================
extern int	rootProcCount;		// number of processors in root VM
extern bool FirstTrace;


//------------------------------------------ functions of Predictor ------------------------------------------------
bool MakeAllConfigurations(int proc_number,int rank,std::vector<long_vect>& result);
bool IsBestConfiguration(Interval* best,Interval * current);
int CheckEuristik(std::vector<long> & who);

//int predictor(int argc, char *argv[]);

extern long_vect MinSizesOfAM; // для автоматического поиска
extern long currentAM_ID;
