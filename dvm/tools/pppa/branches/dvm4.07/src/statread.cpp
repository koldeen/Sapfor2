#define _STATFILE_
#include "zlib.h"
#include <string.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <new>
#include "bool.h"
#include "strall.h"
#include "inter.h"
#include "treeinter.h"
#include "potensyn.h"
#include "statread.h"
using namespace std;
extern short reverse,szsh,szl,szd,szv,torightto,torightfrom;
// read intervals and synchronyzation times from file
CStatRead::CStatRead(const char * name,int iIM,int jIM,short sore)
// name - file name
{
	gzFile  ff=NULL;
	valid=TRUE;
	valid_warning=0;
	BOOL valid_synchro=TRUE;
	valid_synchro=TRUE;
	pclfrag=NULL;
	pclsyn=NULL;
	pic=NULL;
	pch_vmssize=NULL;
	pvers=NULL;
	pvms *pb_vms=NULL;
	proccount=0;
	ff=gzopen(name,"rb");
	if (ff==NULL) {
		valid=FALSE;
		sprintf(texterr,"Can't open file %s \n",name);
		return;
	}
	unsigned long lbufcompr,lbufuncompr=0,luncompr,luncomprread;
	pbufcompr=NULL;pbufuncompr=NULL;
	char lbufplusch[12]={0};
	char nprocch[12]={0};
	int s; // for gzread
	long l; // for gztell
	short sz[QV_CONST];
	unsigned char *psz; //struc sz
	gzplus =0; // sign of file gz/ gz+
	if (strstr(name,".gz+") !=NULL) { //file gz+
		gzplus=1;
		int k;
		for (k=0;;k++) { // number of compressed bytes
			if (gzread(ff,&(lbufplusch[k]),1)!=1) {
				valid=FALSE;
				sprintf(texterr,"Can't read from file %s \n",name);
				return;
			}
			if (lbufplusch[k]==0) break;
		}
		lbufuncompr=atol(lbufplusch); // size of buffer
		for (k=0;k<12;k++) lbufplusch[k]=0;
		for (k=0;;k++) { // number of processors
			if (gzread(ff,&(nprocch[k]),1)!=1) {
				valid=FALSE;
				sprintf(texterr,"Can't read from file %s \n",name);
				return;
			}
			if (nprocch[k]==0) break;
		}
		for (k=0;;k++) { // number of compressed bytes
			if (gzread(ff,&(lbufplusch[k]),1)!=1) {
				valid=FALSE;
				sprintf(texterr,"Can't read from file %s \n",name);
				return;
			}
			if (lbufplusch[k]==0) break;
		}
		lbufcompr=atol(lbufplusch);
		pbufcompr=new unsigned char[lbufcompr];
		if (pbufcompr==NULL) throw("Out of memory\n");
		luncompr=lbufuncompr+lbufuncompr/1000+12; // length uncompressed buffer
		luncomprread=luncompr;
		if (pbufcompr!=NULL) {
			pbufuncompr=new unsigned char[luncompr];
			if (pbufuncompr==NULL) throw("Out of memory\n");
		}
		s=gzread(ff,pbufcompr,lbufcompr);
		if (s!=(int)lbufcompr) {
			valid=FALSE;
			sprintf(texterr,"Can't read from file %s l=%ld\n",name,lbufcompr);
			return;
		}
		int err=uncompress(pbufuncompr,&luncomprread,pbufcompr,lbufcompr);
		if (err!=Z_OK || luncomprread!=lbufuncompr) {
			valid=FALSE;
			sprintf(texterr,"Can't uncompress l=%ld\n",lbufcompr);
			return;
		}
		psz=pbufuncompr;
	} else { // file gz or other files
		l=gztell(ff);
		psz=(unsigned char *)(&(sz[0]));
		// read const information about size of variables and reverse
		s=gzread(ff,&sz,sizeof(sz));
		if (s!=(int)sizeof(sz)) {
			valid=FALSE;
			sprintf(texterr,"Can't read from file %s addr=%ld size=%d\n",
				name,l,(int)sizeof(sz));
			return;
		}
	}
	// data presentation
	memcpy(&reverse,psz,2); // variables reverse and toright for CPYMEM
	if (reverse!=1) {
		short imcpy,sh1=0;
		for (imcpy=sizeof(reverse)-1;imcpy>=0;imcpy--)	{ 
			*((unsigned char*)(&sh1)+imcpy)=
				*((unsigned char *)(&reverse)+sizeof(reverse)-1-imcpy);
		}
		if (sh1!=1) {
			valid=FALSE;
			sprintf(texterr,"Analyzing file %s is not statistics\n",name);
			return;
		}
		reverse=1;
	}else reverse=0;
	short left=1; torightto=0;torightfrom=0;
	char *pleft=(char *)&left;
	if (reverse==1) { // data reverse
		if (pleft[0]==0 ) torightto=1;else torightfrom=1;
	}
	// size of used variables
	CPYMEM(szsh,psz+2,2);
	CPYMEM(szl,psz+4,2);
	CPYMEM(szv,psz+6,2);
	CPYMEM(szd,psz+8,2);
	if ((szsh!=SZSH) || /*(szl>SZL) || (szv>SZV) ||*/ (szd!=SZD)) {
		valid=FALSE;
		sprintf(texterr,"Size of accumulating data > size of machine data %d>%d\n",
		szsh,(int)SZSH);
		return;
	}
	if ((szl>SZL) || (szv>SZV) ) {
		sprintf(textwarning[valid_warning],"Number of operation may be incorrect. Data size not equal. %d>%d %d>%d\n",
		szl,(int)SZL,szv,(int)SZV);
		valid_warning++;
	}
	// calculate size of const information
	int lvms=QV_SHORT*szsh+QV_LONG*szl+QV_VOID*szv+QV_DOUBLE*szd;
	// read const information from file
	unsigned char *pch_vms=NULL;
	if (gzplus==1) pch_vms=pbufuncompr+sizeof(sz);
	else {
		pch_vms=new unsigned char[lvms];
		if (pch_vms==NULL) throw("Out of memory\n");
		l=gztell(ff);
		s=gzread(ff,pch_vms,lvms);
		if (s!=lvms) {
			valid=FALSE;
			sprintf(texterr,"Can't read from file %s addr=%ld size=%d\n",
				name,l,lvms);
			return;
		}
	}
	unsigned long linter=0; // read there only for control
	CPYMEM(linter,pch_vms+MAKELONG(pb_vms,linter,proccount,QV_SHORT),szl);
	if (linter<=0) {
		valid=FALSE;
		sprintf(texterr,"Execution was exit with statistics error. \n");
		return;
	}
	// smallbuff - not enough memory in buffer,not all data accumulated
	CPYMEM(smallbuff,pch_vms+MAKESHORT(pb_vms,smallbuff,rank),szsh);
	if (smallbuff==1) {
		sprintf(textwarning[valid_warning],
			"Not all times of collective operations were accumulated\n");
		valid_warning++;
	}
	CPYMEM(rank,pch_vms+MAKESHORT(pb_vms,rank,rank),szsh);
	// global size of const information
	size_t lvms_add=lvms+szl*rank+QV_CONST*2;
	// size of VMS run
	pch_vmssize=new unsigned char[szl*rank];
	if (pch_vmssize==NULL) throw("Out of memory\n");
	if (gzplus==1) memcpy(pch_vmssize,pbufuncompr+sizeof(sz)+lvms,szl*rank);
	else {
		l=gztell(ff);
		s=gzread(ff,pch_vmssize,szl*rank);
		if (s!=szl*rank) {
			valid=FALSE;
			sprintf(texterr,"Can't read from file %s addr=%ld size=%d\n",
					name,l,szl*rank);
			return;
		}
	}
	CPYMEM(maxnlevel,pch_vms+MAKESHORT(pb_vms,maxnlev,rank),szsh);
	CPYMEM(proccount,pch_vms+MAKELONG(pb_vms,proccount,proccount,QV_SHORT),szl);
	pclfrag=new CTreeInter*[proccount]; 
	if (pclfrag==NULL) throw("Out of memory\n");
	unsigned long i;
	for (i=0;i<proccount;i++) pclfrag[i]=NULL;
	// allocate memory for pointer of synchronization times
	pclsyn=new CSynchro*[proccount];
	if (pclsyn==NULL) throw("Out of memory\n");
	// proccount - number of processors, the main loop
	for (i=0;i<proccount;i++) pclsyn[i]=NULL;
	unsigned long lsynchro=0;
	for (i=0;i<proccount;i++) {// main processor's loop 
		unsigned long qfrag=0;
		short maxn=0;
		// qfrag - number of intervals
		CPYMEM(qfrag,pch_vms+MAKELONG(pb_vms,qfrag,proccount,QV_SHORT),szl);
		// maxn - number of levels
		CPYMEM(maxn,pch_vms+MAKESHORT(pb_vms,maxnlev,rank),szsh);
		// linter - size of all intervals in bytes
		CPYMEM(linter,pch_vms+MAKELONG(pb_vms,linter,proccount,QV_SHORT),szl); //all variables on other processors may be not equivalent
		char *pbuffer=NULL;
		CPYMEM(pbuffer,pch_vms+MAKEVOID(pb_vms,pbuffer,pbuffer,QV_SHORT,QV_LONG),szv);
		// length of version, platform and processor name
		short lvers=0;
		CPYMEM(lvers,pch_vms+MAKESHORT(pb_vms,lvers,rank),szsh);
		// different values on each processor 
		if (lvers<=0) {
			valid=FALSE;
			sprintf(texterr,"Incorrect version\n");
			return;
		}
		pvers=new char[lvers];
		if (pvers==NULL) throw("Out of memory\n");
		l=gztell(ff);
		if (gzplus==1) {
			memcpy(pvers,(char *)(pbufuncompr+sizeof(sz)+lvms+szl*rank),lvers);
		} else {
			// read from file platform, version number, processor name and time
			s=gzread(ff,pvers,lvers);
			if (s!=lvers) {
				valid=FALSE;
				sprintf(texterr,"Can't read from file %s addr=%ld size=%d\n",
					name,l,lvers);
				return;
			}
		}
		pbuffer=pbuffer+lvms_add+lvers;
		unsigned char * pinterinbuff;
		if (gzplus==1) pinterinbuff=pbufuncompr+lvms_add+lvers;
		else pinterinbuff=NULL;
		// processor name
		char * pprocname=pvers+strlen(pvers)+strlen(pvers+strlen(pvers)+1)+2;
		double proct=0.;// processor time
		CPYMEM(proct,pch_vms+MAKEDOUBLE(pb_vms,proctime,proctime,QV_SHORT,QV_LONG,QV_VOID),szd);
		// create interval tree
		pclfrag[i]=new CTreeInter(ff,linter,pbuffer,i,qfrag,maxn,
			pprocname,proct,iIM,jIM,sore,pinterinbuff);
		if (pclfrag[i]==NULL) throw("Out of memory\n");
		valid=pclfrag[i]->Valid();
		if (!valid) {
			pclfrag[i]->TextErr(texterr);
			return;
		}
		unsigned long lbuf=0;
		// lbuf - size of buffer
		CPYMEM(lbuf,pch_vms+MAKELONG(pb_vms,lbuf,proccount,QV_SHORT),szl);
		// lsynchro - size of synchronyzation times in bytes
		if (valid_synchro==FALSE) lsynchro=0; // out of memory for synchro operations
		else CPYMEM(lsynchro,pch_vms+MAKELONG(pb_vms,lsynchro,proccount,QV_SHORT),szl);
		// set it the first time
		unsigned char *psynchroinbuff;
		if (gzplus==1) {
			psynchroinbuff=lbuf-lsynchro+pbufuncompr;
			//psynchroinbuff=pinterinbuff+lbuf-lsynchro-linter-lvms_add-lvers;
		} else {
			psynchroinbuff=NULL;
			if (z_off_t zo=gzseek(ff,lbuf-lsynchro-linter-lvms_add-lvers,SEEK_CUR)==-1) {
				sprintf(texterr,"Can't read from file %s addr=%ld size=%ld\n",
				name,l,lbuf-lsynchro-linter-lvms_add-lvers);
				valid=FALSE;
				return;
			}
		}
		if (lsynchro>0) {
			l=gztell(ff);
			// create array of synchronization times
			try {
				pclsyn[i]= new CSynchro(ff,lsynchro,psynchroinbuff);
				if (pclsyn[i]==NULL) throw("Out of memory\n");
			}
			catch (bad_alloc e) {
			    valid_synchro=FALSE;
			    //lsynchro=0;
			    for (unsigned int j=0;j<=i;j++) {
             		if (pclsyn[j]!=NULL) {
						pclsyn[j]->~CSynchro();
						pclsyn[j]=NULL;
					}
				}
				sprintf(textwarning[valid_warning],"Out of memory for synchronization operations\n");
				valid_warning++;
			}	// end catch
			catch (char *str) {
			    valid_synchro=FALSE;
			    //lsynchro=0;
			    for (unsigned int j=0;j<=i;j++) {
             		if (pclsyn[j]!=NULL) {
						pclsyn[j]->~CSynchro();
						pclsyn[j]=NULL;
					}
				}
				sprintf(textwarning[valid_warning],"Out of memory for synchronization operations\n");
				valid_warning++;
			}	// end catch
			if (pclsyn[i]!=NULL) {
				valid=pclsyn[i]->Valid();
                if (!valid) {
					pclsyn[i]->TextErr(texterr);
					return;
				}
			} // end if
		} else {
			// synchronization times not accumulated
			pclsyn[i]=0;
			if (lsynchro >0 && gzplus==0) {
				if (gzseek(ff,lsynchro,SEEK_CUR)!=0) {
					valid=FALSE;
					return;
				}
			}
		}
		if (gzplus==1) {delete []pbufcompr; pbufcompr=NULL;}
		if (i!=proccount-1) {
			if (gzplus==1) {
				for (int k=0;;k++) {
					if (gzread(ff,&(lbufplusch[k]),1)!=1) {
						valid=FALSE;
						sprintf(texterr,"Can't read from file %s \n",name);
						return;
					}
					if (lbufplusch[k]==0) break;
				}
				lbufcompr=atol(lbufplusch);
				pbufcompr=new unsigned char[lbufcompr];
				if (pbufcompr==NULL) throw("Out of memory\n");
				s=gzread(ff,pbufcompr,lbufcompr);
				if (s!=(int)lbufcompr) {
					valid=FALSE;
					sprintf(texterr,"Can't read from file %s l=%ld\n",name,lbufcompr);
					return;
				}
				int err=uncompress(pbufuncompr,&luncomprread,pbufcompr,lbufcompr);
				if (err!=Z_OK || luncomprread!=lbufuncompr) {
					valid=FALSE;
					sprintf(texterr,"Can't uncompress l=%ld\n",lbufcompr);
					return;
				}
			} else {
				s=gzread(ff,&sz,sizeof(sz));
				if (s!=sizeof(sz)) {
					valid=FALSE;
					sprintf(texterr,"Can't read from file %s addr=%ld size=%d\n",
					name,l,(int)sizeof(sz));
					return;
				}
				s=gzread(ff,pch_vms,lvms);
				if (s!=lvms) {
					valid=FALSE;
					sprintf(texterr,"Can't read from file %s addr=%ld size=%d\n",
					name,l,lvms);
					return;
				}
			}
			CPYMEM(rank,pch_vms+MAKESHORT(pb_vms,rank,rank),szsh);
			if (gzplus==1) pch_vms=pbufuncompr+sizeof(sz);
			else {
				l=gztell(ff);
				s=gzread(ff,pch_vmssize,szl*rank);
				if (s!=szl*rank) {
					valid=FALSE;
					sprintf(texterr,"Can't read from file %s addr=%ld size=%d\n",
					name,l,szl*rank);
					return;
				}
				l=gztell(ff);
				delete [] pvers; pvers=NULL;
			}
		}
	}
	if (gzplus==1) {delete []pbufuncompr; pbufuncompr=NULL;}
	pic=new CInter*[proccount];
	if (pic==NULL) throw("Out of memory\n");
	// add synchronization times to interval characteristics
	if (lsynchro>0) {
		unsigned long n=BeginTreeWalk();
		while (n!=0) {
			BOOL b=Synchro();
			if (b==1) return;
			n=TreeWalk();
		}
		for (i=0;i<proccount;i++) {
			pclsyn[i]->~CSynchro();
		}
	}//lsynchro
	// sum interval characteristics
	for (i=0;i<proccount;i++){
		pclfrag[i]->SumLevel();
		pclsyn[i]=NULL;
	}
		// Idle, Load imbalance
	unsigned long n=BeginTreeWalk();
	while (n!=0) {
		double max=0.0,maxi=0.0;
		double time,time1;
		// calculate maximal values
		for (i=0;i<proccount;i++) {
			if (pic[i]!=NULL) {
				pic[i]->ReadTime(EXEC,time);
				if (time>max) max=time;
				pic[i]->ReadTime(CPU,time);
				pic[i]->ReadTime(CPUUSR,time1);
				if (time+time1>maxi) maxi=time+time1;
			}
		}
		// calculate maximal - current
		for (i=0;i<proccount;i++) {
			if (pic[i]!=NULL) {
				double qproc;
				pic[i]->ReadTime(PROC,qproc);
				if (qproc!=n) {
					// interval execute not on all processors
					for (i=0;i<proccount;i++) {
						if (pic[i]!=NULL) {
							pic[i]->WriteTime(IDLE,0);
							pic[i]->WriteTime(LOST,0);
							pic[i]->WriteTime(IMB,0);
							pic[i]->WriteTime(PROC,0);
						}
					}
					break;
				} else {
					pic[i]->ReadTime(EXEC,time);
					if (max-time>0.0) {
						pic[i]->AddTime(IDLE,max-time);
						pic[i]->AddTime(LOST,max-time);
					}
					pic[i]->ReadTime(CPU,time);
					pic[i]->ReadTime(CPUUSR,time1);
					if (maxi-time-time1>0.0)
						pic[i]->AddTime(IMB,maxi-time-time1);
				}
			}
		}
		n=TreeWalk();
	}
	if (gzplus!=1) {
		if (pch_vms!=NULL) {delete [] pch_vms;pch_vms=NULL;}
	}
	gzclose(ff);
}
//--------------------------------------------------
// deallocate memory for trees and syn times
CStatRead::~CStatRead(void)
{
	if (pvers!=NULL) delete []pvers;
	if (gzplus==1) {
        if (pbufcompr!=NULL) delete []pbufcompr; 
		if (pbufuncompr!=NULL) delete []pbufuncompr; 
	} else {
		if (pch_vms!=NULL) delete [] pch_vms;
	}
	if (pclfrag!=NULL) {
		for (unsigned long i=0;i<proccount;i++) {
			if (pclfrag[i]!=NULL) pclfrag[i]->~CTreeInter();
			pclfrag[i]=NULL;
			if (pic!=NULL) pic[i]=NULL;
			if (pclsyn!=NULL) {
				if (pclsyn[i]!=NULL) pclsyn[i]->~CSynchro();
				pclsyn[i]=NULL;
			}
		}
		delete [] pclfrag;
	}
	// deallocate memory for data-member
	if (pclsyn!=NULL) delete [] pclsyn;
	if (pch_vmssize!=NULL) delete []pch_vmssize;
	if (pic!=NULL) delete [] pic;
}
//--------------------------------------------------
// begin tree-walk
unsigned long CStatRead::BeginTreeWalk(void)
// return number of intervals
{
	unsigned long n=0;
	for (unsigned long i=0;i<proccount;i++) {
		pclfrag[i]->BeginInter();
		pic[i]=NULL;
	}
	ident *id;
	for(curnproc=0;curnproc<proccount;curnproc++) {
		pclfrag[curnproc]->NextInter(&id);
		if (id!=NULL) {
			for (unsigned long j=0;j<proccount;j++) {
				pic[j]=pclfrag[j]->FindInter(id);
				if (pic[j]!=NULL) n++;
			}
			return(n);
		}
	}
	return(n);
}
//------------------------------------------------
// continue tree-walk
unsigned long CStatRead::TreeWalk(void)
// return number of intervals
{
	unsigned long n=0;
	ident *id;
	pclfrag[curnproc]->NextInter(&id);
	if (id!=NULL) {
		for (unsigned long j=0;j<proccount;j++) {
			pic[j]=pclfrag[j]->FindInter(id);
			if (pic[j]!=NULL) n++;
		}
		if (n!=0)return(n);
	}
	for(unsigned long i=curnproc+1;i<proccount;i++) {
		pclfrag[i]->NextInter(&id);
		if (id!=NULL) {
			curnproc=i;
			for (unsigned long j=0;j<proccount;j++) {
				pic[j]=pclfrag[j]->FindInter(id);
				if (pic[j]!=NULL) n++;
			}
			return(n);
		}
	}
	return(n);
}
//------------------------------------------------
// calculate synchronization times, variation times and overlap
BOOL CStatRead::Synchro(void)
// return 0 - OK
{
	unsigned long nint=0;
	for (unsigned long k=0;k<proccount;k++) {
		if (pic[k]!=NULL) {
			// nint - number of current interval 
			nint=pic[k]->ninter;
			BOOL b=pclsyn[k]->Count(nint,smallbuff);
			if (b!=0) {
				pclsyn[k]->TextErr(texterr);
				valid=FALSE;
				return(1);
			}
		}
	}
	if (nint==0) return(0);
	for (short i=1;i<=QCOLLECT+QCOLLECT;i++) {
		if ((i&3)!=0 && (i&3)!=2) { //4 type not used
			typegrp t1;
			typecom t2;
			if (i<=QCOLLECT) {
				t1=SYN;
				t2=(typecom)((i)>>2);
			}else{
				t1=VAR;
				t2=(typecom)((i-QCOLLECT)>>2);
			}
			int min=INT_MAX;
			unsigned long j;		
			for (j=0;j<proccount;j++) {
				if (pic[j]!=NULL) {
					// n - number of times in the interval
					int n=pclsyn[j]->GetCount((typecollect)(i));
					if (min!=INT_MAX && n!=min && smallbuff==0) {
						valid=FALSE;
						sprintf(texterr,
"Number of synhro or variation times not equivalent on other processors %ld %ld numbers %d %d %\n",j+1,j,n,min);
						return(1);
					}
					if (min>n) min=n;
				}
			}
			if (min!=0) { 
				// times is accumulated 
				for ( int k=0; k<min; k++) {
					double max=0.0;
					// calculate maximal value
					for (j=0;j<proccount;j++) {
						if (pic[j]!=NULL) {
							double time=pclsyn[j]->Find((typecollect)i);
							if (time-max>0.0) max=time;
						}
					}
					double maxs=0.0;
					if (i<QCOLLECT && (i&3)==3) { 
						// overlap for wait_operation
						for (j=0;j<proccount;j++) {
							if (pic[j]!=NULL) {
								double time=pclsyn[j]->FindNearest
									((typecollect)(i+QCOLLECT-1)); //Start_operation
								if (time==0.0 && smallbuff==0) {
									valid=FALSE;
sprintf(texterr,"Number of call operations != number of wait operations\n");
									return(1);
								}
								if (time-maxs>0.0) maxs=time;
							}
						}
					} 
					for (j=0;j<proccount;j++) {
						if (pic[j]!=NULL) {
							double time=pclsyn[j]->GetCurr();
							// write overlap
							if (maxs>0.0 && time-maxs>0.0 ) {
								pic[j]->AddTime(OVERLAP,t2,time-maxs);
							}
							// write syn and variation times
							if (max-time>0.0) {
								pic[j]->AddTime(t1,t2,max-time);
							}
						}
					} 
				}
			}
		}
	}
	return(0);
}
//------------------------------------------------
// return result of constructor execution
BOOL CStatRead::Valid(int *warn)
{
	*warn=valid_warning;
	return(valid);
}
//---------------------------------------------------
// error message
void CStatRead::TextErr(char *t)
{
	strcpy(t,texterr);
	return;
}
// warning message
//---------------------------------------------------
// return number of processors
unsigned long CStatRead::QProc(void)
{
	return(proccount);
}
//--------------------------------------------
// size of VMS
void CStatRead::VMSSize(char *str)
{
	str[0]='\0';
	char n[11];
	long l=0;
	for (int i=0;i<rank;i++) {
		CPYMEM(l,pch_vmssize+i*szl,szl);
		sprintf(n,"%ld",l);
		if(i==rank-1) strcat(str,n);
		else {
			strcat(str,n);
			strcat(str,"*");
		}
	}
}
//-----------------------------------------------
// warning message
void CStatRead::WasErrAccum(char *str)
{
if (valid_warning==0) str[0]='\0';
else {
	strcpy(str,textwarning[valid_warning-1]);
	valid_warning--;
}
return;
}
//---------------------------------------------
// return number of calls of collective operations
long CStatRead::ReadCall(typecom t)
{
	double val=0.0;
	long calll=0;
	for (unsigned long i=0;i<proccount;i++) {
		if (pic[i]!=NULL) {
			double v;
			pic[i]->ReadTime(CALL,t,v);
			val=val+v;
		}
	}
	calll=(long)(val/1);
	if (val-calll!=0.0) calll++;
	return(calll);
}
//---------------------------------------------
// identifier information of interval
// set number of current characteristics =0
// return number of level
short CStatRead::ReadTitle(char *str)
{
	short nlev=0;
	ident *id=NULL;
	// nenter = number of enters / weight
	double nenter=0.0;
	for (unsigned long i=0;i<proccount;i++) {
		if (pic[i]!=NULL) {
			pic[i]->ReadIdent(&id);
			nlev=id->nlev;
			nenter=nenter+id->nenter;

		}
	}
	long nent=(long)(nenter/1);
	if (nenter-nent!=0.0) nent++;
	char type[10];
	switch((int)(id->t)) {
	case REDUC:strcpy(type,"REDUC");
		break;
	case SREDUC:strcpy(type,"SREDUC");
		break;
	case WREDUC:strcpy(type,"WREDUC");
		break;
	case SHAD:strcpy(type,"SHAD");
		break;
	case SSHAD:strcpy(type,"SSHAD");
		break;
	case WSHAD:strcpy(type,"WSHAD");
		break;
	case RACC:strcpy(type,"RACC");
		break;
	case SRACC:strcpy(type,"SRACC");
		break;
	case WRACC:strcpy(type,"WRACC");
		break;
	case REDISTR:strcpy(type,"REDISTR");
		break;
	case SREDISTR:strcpy(type,"SREDISTR");
		break;
	case WREDISTR:strcpy(type,"WREDISTR");
		break;
	case PREFIX:strcpy(type,"PREFIX");
		break;
	case SEQ:strcpy(type,"SEQ");
		break;
	case PAR: strcpy(type,"PAR");
		break;
	case USER: strcpy(type,"USER");
		break;
	default: sprintf(str,"Statread ReadTitle:Incorrect type\n");
		return(0);
	}
	if (id->nlev==0) type[0]='\0';
	if (id->pname==NULL) {
		if (id->expr==Fic_index) 
		sprintf(str,"INTERVAL ( NLINE=%ld ) LEVEL=%d %s EXE_COUNT=%ld\n",
		id->nline,id->nlev,type,nent);
		else sprintf(str,"INTERVAL ( NLINE=%ld ) LEVEL=%d %s EXE_COUNT=%ld EXPR=%ld\n",
			id->nline,id->nlev,type,nent,id->expr);
	}else {
		if (id->expr==Fic_index) 
		sprintf(str,"INTERVAL ( NLINE=%ld SOURCE=%s ) LEVEL=%d %s EXE_COUNT=%ld\n",
		id->nline,id->pname,id->nlev,type,nent);
		else sprintf(str,"INTERVAL ( NLINE=%ld SOURCE=%s ) LEVEL=%d %s EXE_COUNT=%ld EXPR=%ld\n",
			id->nline,id->pname,id->nlev,type,nent,id->expr);
	}
	curntime=0;
	return(nlev);
}
//--------------------------------------------------------
// return version number on accumulation
char *CStatRead::ReadVers(void)
{  
	return(pvers);
}
//--------------------------------------------------------
// return platform information on accumulation
char *CStatRead::ReadPlatform(void)
{  
	return(pvers+strlen(pvers)+1);
}
//-----------------------------------------------------------
//name and time of processor
void CStatRead::NameTimeProc(unsigned long n,char **name,double *time)
{
	pclfrag[n]->ReadProcName(name);
	pclfrag[n]->ReadProcTime(*time);
	return;
}
//-------------------------------------------------------
// read current time characteristics
// use after ReadTitle()
BOOL CStatRead::ReadProc(typeprint t,unsigned long *pnumb,int qnumb,short fmt,
						 double sum,char *str)
//t - type of information of characteristics for each processor,
//pnumb - pointer to array of processor numbers, for which characteristics are to be output,
//qnumb - number of elements of processor number array,
//sum - total characteristic value for each processor,
//str - string where characteristic name and time values are written.
{
	int q,prec,lstr;
	if (t==PRGEN) q=ITER;else q=RED;
	//char ss[1024];
	curntime++;
	if (sum==0.0) {
		str[0]='\0';
		if (curntime>q) curntime=0;
		return(TRUE);
	}
	if (t==PRGEN) {
		sprintf(str,"%s",nameGen[curntime-1]);
		//sprintf(ss,"%s",nameGen[curntime-1]);
	} else {
		// nameCom for VAR,OVERLAP,SYN,COM,RCOM 
		sprintf(str,"%s",nameCom[curntime-1]);
		strcat(str,"       ");
	}
	lstr=strlen(nameGen[curntime-1]);
	// list of processor numbers - pnumb
	// pr=TRUE - number is in list
	for (unsigned long i=0;i<proccount;i++) {
		BOOL pr=FALSE;
		if (pic[i]!=NULL) {
			if (pnumb!=NULL) {
				for (int j=0;j<qnumb;j++) {
					if (i+1>=pnumb[j] && i+1<=pnumb[j+1]) pr=TRUE;
				}
			} else pr=TRUE;
			if (pr==TRUE) {
				// read time characteristic
				double time;
				switch (t) {
				case PRGEN:
					pic[i]->ReadTime((typetime)(curntime-1),time);
					break;
				case PRCOM:
					pic[i]->ReadTime(COM,(typecom)(curntime-1),time);
					break;
				case PRRCOM:
					pic[i]->ReadTime(RCOM,(typecom)(curntime-1),time);
					break;
				case PRSYN:
					pic[i]->ReadTime(SYN,(typecom)(curntime-1),time);
					break;
				case PRVAR:
					pic[i]->ReadTime(VAR,(typecom)(curntime-1),time);
					break;
				case PROVER:
					pic[i]->ReadTime(OVERLAP,(typecom)(curntime-1),time);
					break;
				default:sprintf(str,"Statread ReadProc:Incorrect type=%d\n",t);
				return(FALSE);
				}
				if ((t==PRGEN) && ((typetime)(curntime-1)==PROC ||
					(typetime)(curntime-1)==ITER)) prec=0;else prec=PREC;
				sprintf((str+lstr),"%*.*lf ",fmt,prec,time);
				//sprintf(ss+lstr,"%*.*lf",fmt,prec,time);
				lstr=strlen(str);
			} 
		}
	}
	if (curntime>q) curntime=0;
	return(TRUE);
}
//--------------------------------------------------------
// calculate min,max,sum time characteristics
void CStatRead::MinMaxSum(typeprint t,double *min,unsigned long *nprocmin,
						  double*max,unsigned long *nprocmax,
						  double *sum)
// t - characteristic type,
//min - pointer to array of minimal characteristic values,
//nprocmin,- pointer to processor number array, corresponding to minimal values,
//max, - pointer to array of maximal characteristic values,
//nprocmax, - pointer to processor number array, corresponding to maximal values,
//sum - pointer to array of total characteristic values.
{
	int q;
	if (t==PRGEN) q=ITER;else q=RED;
	if (t==PRCALLS || t==PRLOST) q=StatGrpCount-1;
	int k;
	for (k=0;k<=q;k++) {
		min[k]=DBL_MAX;
		max[k]=0.0;
		sum[k]=0.0;
		nprocmin[k]=0;
		nprocmax[k]=0;
	}
	for (unsigned long i=0;i<proccount;i++) {
		if (pic[i]!=NULL) {
			for (k=0;k<=q;k++) {
				double time;
				// read time characteristic
				switch (t) {
				case PRGEN:
					pic[i]->ReadTime((typetime)k,time);
					break;
				case PRCOM:
					pic[i]->ReadTime(COM,(typecom)k,time);
					break;
				case PRRCOM:
					pic[i]->ReadTime(RCOM,(typecom)k,time);
					break;
				case PRSYN:
					pic[i]->ReadTime(SYN,(typecom)k,time);
					break;
				case PRVAR:
					pic[i]->ReadTime(VAR,(typecom)k,time);
					break;
				case PRCALLS:
					pic[i]->ReadTime(CALLSMT,k,time);
					break;
				case PRLOST:
					pic[i]->ReadTime(LOSTMT,k,time);
					break;
				case PROVER:
					pic[i]->ReadTime(OVERLAP,(typecom)k,time);
					break;
				default:
					valid=FALSE;
					printf("CStatRead::MinMaxSum Unknown typeprint=%d\n",t);
					return;
				}
				// minimal value
				if (min[k]>time) {
					min[k]=time;
					nprocmin[k]=i+1;
				}
				//maximal value
				if (max[k]<=time) {
					max[k]=time;
					nprocmax[k]=i+1;
				}
				// sum value
				sum[k]=sum[k]+time;
			}
		}

	}
}
//-------------------------------------------------------------------------
// read grp  characteristics
void CStatRead::GrpTimes(double *arrprod,double *arrlost,double *arrcalls,int nproc)
{
	int q=StatGrpCount-1;
	int k;
	for (k=0;k<=q;k++) {
		arrprod[k]=0.0;
		arrlost[k]=0.0;
		arrcalls[k]=0.0;
	}
	unsigned long i=nproc-1;
	//double arr[StatGrpCount];
	if (pic[i]!=NULL) {
        for (k=0;k<=q;k++) {
            // read time characteristic
			pic[i]->ReadTime(CALLSMT,k,arrcalls[k]);
			//arrcalls[k]=(int)arr[k];
			pic[i]->ReadTime(LOSTMT,k,arrlost[k]);
			pic[i]->ReadTime(PRODMT,k,arrprod[k]);
		} // end for
	}// end if 
	return;
}

