#define _STATFILE_
#include "treeinter.h"
#include <stdio.h>
#include <string.h>
extern short reverse,szsh,szd,szv,szl,torightto,torightfrom;
// list of intervals for each processor
CTreeInter::CTreeInter(gzFile stream,unsigned long lint,char *pbuff,
					   unsigned int n,unsigned long qint,short maxn,
					   char * ppn,double proct,
					   int iIM,int jIM,short sore,
					   unsigned char *pbuffer)
// stream-file descriptor pointer,
//lint- information length in bytes,
// pbuff - beginning of the buffer at the collection stage,
//n - processor number,
//qint - number of intervals
//maxn - maximal nesting level
// ppn - processor name
// proct - processor time
//iIm- 0/1 sign of summing on index i
//jIM-0/1 sign of summing on index j
//sore - sign of summing or elements print
//pbuffer - file gz+,data have been read
{
	valid=TRUE;
	nproc=n;
	qinter=qint;
	maxnlev=maxn;
	curninter=1;
	pt=NULL;
	pprocname=NULL;
	sign_buffer=NULL;
	unsigned char *buffer;
	if (ppn!=NULL) {// processor name
		pprocname=new char[strlen(ppn)+1];
		if (pprocname==NULL) throw("Out of memory\n");
		strcpy(pprocname,ppn);
	}
	proctime=proct;
	// dynamically allocate memory for intervals of struct tinter_ch
	if (pbuffer==NULL) { //data had not been read
		buffer=new unsigned char[lint];
		if (buffer==NULL) throw("Out of memory\n");
		sign_buffer=buffer;
		long l=gztell(stream);
		// read interval information from file
		int s=gzread(stream,buffer,lint);
		if ((unsigned long)s!=lint) {
			valid=FALSE;
			sprintf(texterr,"Can't read intervals from file, addr=%ld, length=%ld\n",
			l,lint);
			delete []sign_buffer;
			sign_buffer=NULL;
			return;
		}
	} else buffer=pbuffer;
	unsigned char *pch=buffer;
	pinter *pi=NULL;
	// allocate memory for intervals of struct ttree
	pt=new ptree[qinter];
	if (pt==NULL) throw("Out of memory\n");
	ident id;
	// calculate size of interval without name of DVM-programm
	int lintone=QI_SHORT*szsh+QI_LONG*szl+QI_VOID*szv+QI_DOUBLE*szd;
	s_GRPTIMES times[StatGrpCount][StatGrpCount];
	int a=MAKEDOUBLE(pi,times[0],nenter,QI_SHORT,QI_LONG,QI_VOID);
	a=MAKELONG(pi,nline,nline,QI_SHORT);
	for (unsigned long ll=0;ll<qinter;ll++) {
		int lt=0;
		// copy time characteristics from file
		for (int i=0;i<StatGrpCount;i++) {
			for (int j=0;j<StatGrpCount;j++) {
                                times[i][j].CallCount=0.0; times[i][j].ProductTime=0.0; times[i][j].LostTime=0.0;  
				CPYMEM(times[i][j].CallCount,
					pch+MAKEDOUBLE(pi,times[lt],nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
				CPYMEM(times[i][j].ProductTime,
					pch+MAKEDOUBLE(pi,times[lt+1],nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
				CPYMEM(times[i][j].LostTime,
					pch+MAKEDOUBLE(pi,times[lt+2],nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
				lt=lt+3;
			}
		}
		// add information to interval matrix
		s_SendRecvTimes addinfo;
                addinfo.SendCallTime=0.0;
                addinfo.MinSendCallTime=0.0;
		addinfo.MaxSendCallTime=0.0;
                addinfo.SendCallCount=0;
                addinfo.RecvCallTime=0.0;
                addinfo.MinRecvCallTime=0.0;
                addinfo.MaxRecvCallTime=0.0;
                addinfo.RecvCallCount=0;
		CPYMEM(addinfo.SendCallTime,pch+MAKEDOUBLE(pi,SendCallTime,nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
		CPYMEM(addinfo.MinSendCallTime,pch+MAKEDOUBLE(pi,MinSendCallTime,nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
		CPYMEM(addinfo.MaxSendCallTime,pch+MAKEDOUBLE(pi,MaxSendCallTime,nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
		CPYMEM(addinfo.SendCallCount,pch+MAKELONG(pi,SendCallCount,nline,QI_SHORT),szl);
		CPYMEM(addinfo.RecvCallTime,pch+MAKEDOUBLE(pi,RecvCallTime,nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
		CPYMEM(addinfo.MinRecvCallTime,pch+MAKEDOUBLE(pi,MinRecvCallTime,nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
		CPYMEM(addinfo.MaxRecvCallTime,pch+MAKEDOUBLE(pi,MaxRecvCallTime,nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
		CPYMEM(addinfo.RecvCallCount,pch+MAKELONG(pi,RecvCallCount,nline,QI_SHORT),szl);
		id.pname=(char *)(pch+lintone);
		// copy identifier information
                id.nline=0; id.nline_end=0; id.proc=0;id.nenter=0,0; id.expr=0;id.nlev=0;
		CPYMEM(id.nline,pch+MAKELONG(pi,nline,nline,QI_SHORT),szl);
                CPYMEM(id.nline_end,pch+MAKELONG(pi,nline_end,nline,QI_SHORT),szl);
		CPYMEM(id.proc,pch+MAKELONG(pi,qproc,nline,QI_SHORT),szl);
		CPYMEM(id.nlev,pch+MAKESHORT(pi,nlev,nlev),szsh);
		CPYMEM(id.expr,pch+MAKELONG(pi,expr,nline,QI_SHORT),szl);
		CPYMEM(id.nenter,pch+MAKEDOUBLE(pi,nenter,nenter,QI_SHORT,QI_LONG,QI_VOID),szd);
		short sh=0;
		CPYMEM(sh,pch+MAKESHORT(pi,type,nlev),szsh);
		id.t=(typefrag)sh;
		unsigned char *pptr=NULL;
		unsigned long l0=0;
		// copy referenses on up, down and next intervals
		CPYMEM(pptr,pch+MAKEVOID(pi,up,up,QI_SHORT,QI_LONG),szv);
		if (pptr==NULL) {memcpy(&pt[ll].up,&l0,sizeof(l0));
		} else {
			long l=(char*)pptr-pbuff;
			pptr=buffer+l;
                        pt[ll].up=0;  
			CPYMEM(pt[ll].up,pptr+MAKELONG(pi,ninter,nline,QI_SHORT),szl);
		}
                pptr=NULL;
		CPYMEM(pptr,pch+MAKEVOID(pi,down,up,QI_SHORT,QI_LONG),szv);
		if (pptr==NULL) {memcpy(&pt[ll].down,&l0,sizeof(l0));
		} else {
			long l=(char*)pptr-pbuff;
			pptr=buffer+l;
                        pt[ll].down=0;
			CPYMEM(pt[ll].down,pptr+MAKELONG(pi,ninter,nline,QI_SHORT),szl);
		}
                pptr=NULL;
		CPYMEM(pptr,pch+MAKEVOID(pi,next,up,QI_SHORT,QI_LONG),szv);
		if (pptr==NULL) {memcpy(&pt[ll].next,&l0,sizeof(l0));
		} else {
			long l=(char *)pptr-pbuff;
			pptr=buffer+l;
			pt[ll].next=0;
			CPYMEM(pt[ll].next,pptr+MAKELONG(pi,ninter,nline,QI_SHORT),szl);
		}
		// time characteristics for each interval
		pt[ll].pint=new CInter(times,addinfo,id,ll+1,iIM,jIM,sore);
		if (pt[ll].pint==NULL) throw("Out of memory\n");
		pch=pch+lintone+1+strlen((char*)(pch+lintone));
	}
	if (sign_buffer!=NULL) {delete []sign_buffer; sign_buffer=NULL;}
	return;
}
//----------------------------------------
//return result of constructor execution
BOOL CTreeInter::Valid()
{
	return(valid);
}
//-------------------------------------------
// error message
void CTreeInter::TextErr(char *p)
{
	strcpy(p,texterr);
}

//-------------------------------------------------
//set current interval at the first interval
void CTreeInter::BeginInter(void)
{
	for (unsigned long i=0;i<qinter;i++) {
		pt[i].sign=0;
	}
	curninter=1;
	return;
}
//--------------------------------------------------
//read identifier information of current interval
void CTreeInter::NextInter(ident **id)
{
	*id=NULL;
	for (unsigned long i=curninter;i<=qinter;i++) {
		if (pt[i-1].sign==0) {
			pt[i-1].sign=1;
			curninter=i;
			CInter *p=pt[i-1].pint;
			p->ReadIdent(id);
			return;
		}
	}
	return;
	
}
//------------------------------------------------
// return pointer to interval with the same identifier information
// set current interval
CInter *CTreeInter::FindInter(ident *id)
//id - identifier information
{
	unsigned long n;
	ident *idcur;
	pt[curninter-1].pint->ReadIdent(&idcur);
	if (id==idcur) return(pt[curninter-1].pint); //the same processor
	if (id->nlev==idcur->nlev) { // the same level
		n=pt[curninter-1].up;
		if (n>0) n=pt[n-1].down;
		else n=curninter;// first interval 
		while(n>0) {
			if (pt[n-1].sign==0 && pt[n-1].pint->CompIdent(id)==1) {
				pt[n-1].sign=1;
				curninter=n;
				return(pt[n-1].pint);
			}
			n=pt[n-1].next;
		}
		return(NULL);
	}
	// need level > current level
	n=curninter;
	if (id->nlev>idcur->nlev) {
		// find need down level
		while (id->nlev>idcur->nlev) {
			n=pt[n-1].down;
			if (n==0) return(NULL);
			pt[n-1].pint->ReadIdent(&idcur);
		}
		// find need interval on finded level
		while(n>0) {
			if (pt[n-1].sign==0 && pt[n-1].pint->CompIdent(id)==1) {
				pt[n-1].sign=1;
				curninter=n;
				return(pt[n-1].pint);
			}
			n=pt[n-1].next;
		}
		return(NULL);
	} else {
		// find need up level
		while (id->nlev<idcur->nlev) {
			n=pt[n-1].up;
			if (n==0) return(NULL);
			pt[n-1].pint->ReadIdent(&idcur);
		}
		unsigned long n1=n;
		n=pt[n-1].up;
		if (n>0) n=pt[n-1].down;else n=n1;
		while(n>0) {
			if (pt[n-1].sign==0 && pt[n-1].pint->CompIdent(id)==1) {
				pt[n-1].sign=1;
				curninter=n;
				return(pt[n-1].pint);
			}
			n=pt[n-1].next;
		}
	}
	return(NULL);
}
//--------------------------------------------------
//sum time characteristics  
void CTreeInter::SumLevel(void)
{
	for (short i=maxnlev;i>0;i--) {
		for (unsigned long j=0;j<qinter;j++) {
			ident *id;
			pt[j].pint->ReadIdent(&id);
			if (id->nlev==i) {
				// psum - up level
				unsigned long up=pt[j].up;
				CInter *psum=pt[up-1].pint;
				pt[j].pint->SumInter(psum);
			}
		}
	}
	pt[0].pint->SumInter(NULL);
}
//---------------------------------------------------
//processor time
void CTreeInter::ReadProcTime(double &time)
{
	time=proctime;
}
//---------------------------------------------------
//processor name
void CTreeInter::ReadProcName(char **name)
{
	*name=pprocname;
}
//--------------------------------------------------
// deallocate memory for tree interval
CTreeInter::~CTreeInter()
{
	if (pprocname!=NULL) delete []pprocname;
	if (sign_buffer!=NULL) delete []sign_buffer;
	if (pt==NULL) return;
	for (unsigned long i=0;i<qinter;i++) {
		if (pt[i].pint!=NULL) pt[i].pint->~CInter();
		pt[i].pint=NULL;
	}
	 delete []pt;
}
