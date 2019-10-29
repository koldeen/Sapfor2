#ifndef _TREEINTER_H
#define _TREEINTER_H
#include "zlib.h"
#include "inter.h"
#include "strall.h"
#include "stdio.h"
#include "bool.h"
typedef struct ttree{
	unsigned long up,next,down;
	int sign;
	CInter *pint;
} ptree;
struct inter_short{
	short nlev,type;
};
struct inter_long{
	unsigned long nline,nline_end,expr,qproc,ninter,SendCallCount,RecvCallCount;
};
struct inter_void{
	void *up,*next,*down,*ptimes;
};
struct inter_double{
	double nenter,SendCallTime,MinSendCallTime,
	MaxSendCallTime,RecvCallTime,MinRecvCallTime,
	MaxRecvCallTime,
	times[3*StatGrpCount*StatGrpCount];
};
typedef struct tinter {
        inter_double d;
        inter_void v;
        inter_long l;
	inter_short sh;
}pinter;
#define QI_SHORT sizeof(inter_short)/SZSH
#define QI_LONG sizeof(inter_long)/SZL
#define QI_VOID sizeof(inter_void)/SZV
#define QI_DOUBLE sizeof(inter_double)/SZD
class CTreeInter {
public:
	CTreeInter(gzFile stream,unsigned long lint,char* pbuf,unsigned int n,
		unsigned long qfrag,short maxn,char * ppn,double proct,int i,int j,short sore,unsigned char *pbuffer);
	~CTreeInter();
	BOOL Valid();
	void TextErr(char *t);
	void BeginInter(void);
	void NextInter(ident **p);
	CInter *FindInter(ident *id);
	void SumLevel(void);
	void ReadProcTime(double &time);
	void ReadProcName(char **name);
	ptree (*pt);
protected:
	unsigned int nproc;
	unsigned long qinter;
	unsigned long curninter;
	short maxnlev;
	BOOL valid;
	char texterr[80];
	char *pprocname;
	unsigned char * sign_buffer;
	double proctime;
};
#endif
