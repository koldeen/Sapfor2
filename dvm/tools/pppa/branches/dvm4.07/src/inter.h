#ifndef _INTER_H
#define _INTER_H
#include "sysstat.h"
#include "strall.h"
enum typegrp {COM,RCOM,SYN,VAR,OVERLAP,CALL};
enum typetimeim {CALLSMT,LOSTMT,PRODMT};
enum typetime {LOST,INSUFUSR,INSUF,IDLE,SUMCOM,SUMRCOM,SUMSYN,SUMVAR,SUMOVERLAP,IMB,
EXEC,CPUUSR,CPU,IOTIME,START,PROC,ITER};
enum typecom {IO,RD,SH,RA,RED};//5 collective operation. new operation insert before RED
//if insert new time don't forget insert text in the statread.h
//don't insert new time between SUMCOM...SUMOVERLAP
typedef struct tident {
        double nenter;
        unsigned long nline,nline_end,proc;
        long expr;
	short nlev;
	typefrag t;
        char *pname;
}ident;
typedef    struct	{	double	SendCallTime;
		double	MinSendCallTime;
		double	MaxSendCallTime;
		long	SendCallCount;
		double	RecvCallTime;
		double	MinRecvCallTime;
		double	MaxRecvCallTime;
		long	RecvCallCount;
	}	s_SendRecvTimes;	

class CInter {
public:
CInter (s_GRPTIMES (*pt)[StatGrpCount],s_SendRecvTimes ps,ident p,
		unsigned long nint,int i,int j,short sore);
~CInter(void);
void AddTime(typetime t2,double val);
void WriteTime(typetime t2,double val);
void ReadTime(typetime t2,double &val);
void AddTime(typegrp t1,typecom t2,double val);
void ReadTime(typegrp t1,typecom t2,double &val);
void ReadTime(typetimeim t1,int t2,double &val);
int CompIdent(ident *p);
void ReadIdent(ident **p);
void SumInter(CInter *p);
unsigned long ninter;
private:
	double mgen[ITER+1];
	double mcom[RED+1];
	double mrcom[RED+1];
	double msyn[RED+1];
	double mvar[RED+1];
	double moverlap[RED+1];
	double mcall[RED+1];
	double lost[StatGrpCount];
	double prod[StatGrpCount];
	double calls[StatGrpCount];
	double	SendCallTime;
	double	MinSendCallTime;
	double	MaxSendCallTime;
	long	SendCallCount;
	double	RecvCallTime;
	double	MinRecvCallTime;
	double	MaxRecvCallTime;
	long	RecvCallCount;
	ident idint;
};
/*enum typetime {LOST,INSUFUSR,INSUF,IDLE,
SUMCOM,SUMRCOM,SUMSYN,SUMVAR,SUMOVERLAP,
IMB,EXEC,CPUUSR,CPU,IOTIME,START,PROC,USERGRP,MSGPASGRP,
STARTREDGRP,WAITREDGRP,REDGRP,STARTSHDGRP,WAITSHDGRP,SHDGRP,DISRGRP,
REDISTRGRP,MAPPLGRP,DOPLGRP,PROGBLOCKGRP,IOGRP,REMACCESSGRP,USERDEBGRP,
STATISTGRP,SYSTEMGRP,ITER};*/
#endif
