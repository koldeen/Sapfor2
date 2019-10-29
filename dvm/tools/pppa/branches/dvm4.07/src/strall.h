#if !defined( __STRALL_H )
#define __STRALL_H
#if defined (_STATFILE_)
#include "sysstat.h"
#endif
#define SZSH sizeof(short)
#define SZL sizeof(long)
#define SZINT sizeof(int)
#define SZD sizeof(double)
#define SZV sizeof(void*)
enum typecollect {INOUT=1,SINOUT,WINOUT,NINOUT,REDUC,SREDUC,WREDUC,NREDUC,
SHAD,SSHAD,WSHAD,NSHAD,RACC,SRACC,WRACC,NRACC,REDISTR,SREDISTR,WREDISTR,
NREDISTR}; /* new operation insert before REDISTR */
#define QCOLLECT NREDISTR  /* 4 type for 5 collective operation */

enum typefrag {PREFIX=QCOLLECT,SEQ,PAR,USER};
#if !defined (_STATFILE_)
struct vms_const {
	unsigned char  reverse[2],szsh[2],szl[2],
		szv[2],szd[2];
};
struct vms_short {
	unsigned char  rank[SZSH],maxnlev[SZSH],
			 smallbuff[SZSH],lvers[SZSH];
};
struct vms_long{
	unsigned char proccount[SZL],mpstype[SZL],ioproc[SZL],
			 qfrag[SZL],lbuf[SZL],linter[SZL],lsynchro[SZL];
};
struct vms_void{
	unsigned char pbuffer[SZV];
};
struct vms_double{
	unsigned char proctime[SZD];
};
/* if change here chahge statread.h */
typedef struct tvms_ch {
	struct vms_const shc;
	struct vms_short sh;
	struct vms_long l;
	struct vms_void v;
	struct vms_double d;
} *pvms_ch;

struct inter_short {
	unsigned char nlev[SZSH],type[SZSH];
};
struct inter_long {
	unsigned char nline[SZL],nline_end[SZL],valvar[SZL],qproc[SZL],
		ninter[SZL],SendCallCount[SZL],RecvCallCount[SZL];
};
struct inter_void{
	unsigned char up[SZV],next[SZV],down[SZV],
        ptimes[SZV];
};
struct inter_double{
	unsigned char nenter[SZD],SendCallTime[SZD],MinSendCallTime[SZD],
	MaxSendCallTime[SZD],RecvCallTime[SZD],MinRecvCallTime[SZD],
	MaxRecvCallTime[SZD],
	times[3*StatGrpCount*StatGrpCount][SZD];
};
/* if change here change treeinter.h*/
typedef struct tinter_ch {
	struct inter_short sh;
	struct inter_long l;
	struct inter_void v;
	struct inter_double d;		
}*pinter_ch;
struct syn_short{
	unsigned char nitem[SZSH];
};
struct syn_long{
	unsigned char ninter[SZL];
};
struct syn_void{
	unsigned char pgrp[SZV];
};
struct syn_double{
	unsigned char time[SZD];
};
/* if change here change potensyn.h*/
typedef struct tsyn_ch {
       struct syn_short sh;
	   struct syn_long l;
	   struct syn_void v;
	   struct syn_double d;
}*psyn_ch;
#define CPYMEM(to,from)\
 memcpy(&(to),&(from),sizeof(to));
#define CPYMEMC(to,from)\
	smfrom=0;\
        stcond = sizeof(from)>sizeof(to);\
	if (stcond && toright==1) smfrom=sizeof(from)-sizeof(to);\
	memcpy(&(to),(unsigned char *)(&(from))+smfrom,sizeof(to));
#else
#define min(a,b) (((a) <(b)) ? (a):(b))
#define MAKESHORT(p,nm,nmfirst)\
	(&(p->sh.nm)-&(p->sh.nmfirst))*szsh
#define MAKELONG(p,nm,nmfirst,q_short)\
	q_short*szsh+(&(p->l.nm)-&(p->l.nmfirst))*szl
#define MAKEVOID(p,nm,nmfirst,q_short,q_long)\
	q_short*szsh+q_long*szl+(&(p->v.nm)-&(p->v.nmfirst))*szv
#define MAKEDOUBLE(p,nm,nmfirst,q_short,q_long,q_void)\
	q_short*szsh+q_long*szl+q_void*szv+(&(p->d.nm)-&(p->d.nmfirst))*szd
#define MAKEDOUBLEA(p,nm,nmfirst,q_short,q_long,q_void,a)\
	a=q_short*szsh+q_long*szl+q_void*szv+(&(p->d.nm)-&(p->d.nmfirst))*szd;
	
#define CPYMEM(to,pfrom,sz_var)\
{\
	int sz_to;\
	int smfrom=0,smto=0,mmin;\
	sz_to=sizeof(to);\
	mmin=min(sz_to,sz_var);\
	if (sz_to!=sz_var) {\
		if (sz_to>sz_var) {\
			if (torightto==1)	smto=sz_to-sz_var;\
		} else {\
			if (torightfrom==1) smfrom=sz_var-sz_to;\
		}\
	}\
	if (reverse!=1) {\
		memcpy((unsigned char *)(&(to))+smto,pfrom+smfrom,mmin);\
	} else {\
		int imcpy;\
		for (imcpy=mmin-1;imcpy>=0;imcpy--) {\
			*((unsigned char*)(&(to))+imcpy+smto)=\
				*(pfrom+smfrom+mmin-1-imcpy);\
		}\
	}\
}
#endif
#endif
