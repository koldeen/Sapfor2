#include "bool.h"
#define _STATFILE_
#include "statread.h"
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <exception>
#include <new>
#include "dvmvers.h"
#include "statprintf.h"
using namespace std;

int main (int argv,char **argc)
{
	//sfn outfn -l d>=0 -c d=-1..9 -n d-d>=0 -m text 
	if (argv<3) {
		printf("Performance analyser parameters: <file _name1> <file_name2> [-l  <level>]\n");
		printf("         [-n <list>] [-c <compression_level>] [-m <matrix>]\n");
		printf("<file_name1> - statistics file name \n");
		printf("<file_name2> - output file name \n");
		printf("<level> - interval level number \n");
		printf("<list> - list of processor numbers, 0 - without processor characteristics \n");
		printf("<compression_level> - -1..9 - compression level of output file,-1-no compression \n");
		printf("<matrix> - <i[:<groupname>]|j[:<groupname>]\n");
		printf("i|j - sum of row or column elements of matrix of interval characteristics \n");
		printf("<groupname> - name of group, set to output row or column per elements. Groups names :\n");
		printf("	          UserGrp|MsgPasGrp|StartRedGrp|WaitRedGrp|RedGrp|StartShdGrp|\n");
		printf("              WaitShdGrp|ShdGrp|DistrGrp|ReDistrGrp|MapPLGrp|DoPLGrp|\n");
		printf("              ProgBlockGrp|IOGrp|RemAccessGrp|UserDebGrp|StatistGrp|SystemGrp\n");
		return 0;
	}
	if (argv>10) {
		printf("Incorrect number of parameters\n");
		exit(1);
	}
	BOOL proc=TRUE,comp=TRUE,gen=TRUE;
	char compr[3],mode[5];
	strcpy(mode,"wb0");
	int nlevel=9999,qnumb=1;
	unsigned long *pnumb=NULL;
	int iIM=0,jIM=0,nparin=0,nparout=0;
	short sore=0;
	size_t st=0;
	//new_handler set_new_handler(NULL);
	nparin=1;// statistics file
	nparout=2;// output file
	for (int npar=3; npar<argv;npar++) { // key parameters
		int i,cc;
		char let;
		char arrs[24] = "                       "; // strlen nameGen[i]
		if (argc[npar][2]!=0) {
			printf("Incorrect parameter %s\n",argc[npar]);
			exit(1);
		}
		if (argv==npar+1) {
			printf("Parameter for %s not set\n",argc[npar]);
			exit(1);
		}
		switch(argc[npar][1]) {
			case 'l':
			//interval level
			npar++;
			nlevel=atoi(argc[npar]);
		if (nlevel<0 || (nlevel==0 && strcmp(argc[npar],"0")!=0)) {
			printf("Incorrect number of level %s \n",argc[npar]);
			exit(1);
		}
			break;
		case 'c':
			// compression level
			npar++;
			mode[0]=0;compr[0]=0;
			cc=atoi(argc[npar]);
			if (cc<-1 || cc>9) {
				printf("Incorrect compression level of file %s \n",argc[3]);
				exit(1);
			}
			if (cc==-1) {
				strcpy(compr,"0");
			} else {
				int comprd;
				if (cc==0) strcpy(compr,"-1");
				else {
					comprd=cc;
					sprintf(compr,"%d",comprd);
				}
			}
			strcpy(mode,"wb");
			strcat(mode,compr);
			break;
		case 'n':
			// list of processor numbers
			npar ++;
			qnumb=1;
			i=0;
			while (argc[npar][i]!=0) {
				if (argc[npar][i]==',') qnumb++;
				i++;
			}
			pnumb=new unsigned long(qnumb*2);
			if (pnumb==NULL) throw("Out of memory\n");
			char * token;
			token=strtok(argc[npar],",/n");
			i=0;
			while (token!=NULL) {
				char *tdiap=strchr(token,'-');
				if (tdiap==NULL) {
					pnumb[i]=atoi(token);
					pnumb[i+1]=pnumb[i];
				}else {
					pnumb[i+1]=atoi(tdiap+1);
					tdiap[0]='\0';
					pnumb[i]=atoi(token);
				}
				token=strtok(NULL,",\n");
				i=i+2;
			} // end while
			// -n 0 - not print processor characteristics
			if (qnumb==1 && pnumb[0]==0 && pnumb[1]==0) proc=FALSE;
			break;
		case 'm':
			// interval matrix
			npar++;
			let=argc[npar][0];
			if (let!='i' && let!='j') {
				printf("Incorrect %d parameter %c, must be i/j\n",npar,let);
				exit(1);
			}
			sore=1; 
			if (let=='i') iIM=1;else jIM=1;
			st=strlen(argc[npar]);
			if (st==1) break;
			sore=0;  // element
			if (argc[npar][1]!=':') {
				printf("Incorrect %d parameter %s, must be i=<groupname>/j=<groupname>\n",npar,argc[npar]);
				exit(1);
			}
			strncpy(arrs,&(argc[npar][2]),st-2);
			iIM=0;jIM=0;
			for (i=1;i<=StatGrpCount;i++) {
				if (strcmp(nameGenMT[i-1],arrs)==0) {
					if (let=='i') iIM=i;
					else jIM=i;
					break;
				}
			} // end for
			if (iIM==0 && jIM==0) {
				printf("Incorrect group name %s \n",argc[npar]);
				exit(1);
			}
			break;
		default:
			printf("Incorrect parameter %s\n",argc[npar]);
			exit(1);
			break;
		} // end switch
	} // end for key parameters
	// read time characteristics and syn times
	try {
	CStatRead stat(argc[nparin],iIM,jIM,sore);
	int warn;
	if (stat.Valid(&warn)!=TRUE) {
		char t[80];
		stat.TextErr(t);
		printf("%s",t);
		exit(1);
	}
	unsigned long qproc=stat.QProc();
	if (qproc==0) exit(1);
	// string for processor characteristics - max
	// printf for compressed and not compressed out file
	CStatPrintf statpr(argc[nparout],1024,mode);
	if (statpr.Valid()!=TRUE) {
		char t[80];
		statpr.TextErr(t);
		printf("%s",t);
		exit (1);
	}
	double min[ITER+1];
	double max[ITER+1];
	double sum[ITER+1];
	// communication
	double minc[RED+1];
	double maxc[RED+1];
	double sumc[RED+1];
	// real communication
	double minrc[RED+1];
	double maxrc[RED+1];
	double sumrc[RED+1];
	// synchronization
	double mins[RED+1];
	double maxs[RED+1];
	double sums[RED+1];
	// variation
	double minv[RED+1];
	double maxv[RED+1];
	double sumv[RED+1];
	// overlap
	double minov[RED+1];
	double maxov[RED+1];
	double sumov[RED+1];
	// number of processor
	unsigned long nprocmin[ITER+1],nprocmax[ITER+1]; 
	unsigned long nprocminc[RED+1],nprocmaxc[RED+1]; 
	unsigned long nprocminrc[RED+1],nprocmaxrc[RED+1]; 
	unsigned long nprocmins[RED+1],nprocmaxs[RED+1]; 
	unsigned long nprocminv[RED+1],nprocmaxv[RED+1]; 
	unsigned long nprocminov[RED+1],nprocmaxov[RED+1]; 
	char *namecomp[3]={"Tmin","Tmax","Tmid"};
	int ltxt=strlen(nameCom[0])+1;
	char p_heading[80];
	int lenstr=0;
	char *poutstr;
	int i;
	stat.VMSSize(p_heading);
	statpr.StatPrintf("Processor system=%s\n",p_heading);
	char * pvers=stat.ReadVers();
	char *pplat=stat.ReadPlatform();
	statpr.StatPrintf("Statistics has been accumulated on DVM-system version %s, platform %s\n",pvers,pplat);
	statpr.StatPrintf("Analyzer is executing on DVM-system version %s, platform %s\n",VERS,PLATFORM);	
	for (i=0;i<warn;i++) { // warning message
		stat.WasErrAccum(p_heading);
		statpr.StatPrintf("!! %s",p_heading);
	}
	short dig_time=0;
	unsigned long n=stat.BeginTreeWalk();
    while (n!=0) {
        short nlev=stat.ReadTitle(p_heading);
		if (nlev<=nlevel) {
            statpr.StatPrintf("%s","-------------------------------------------------------------------------\n");
			statpr.StatPrintf("%s",p_heading);
			// calculate min,max,sum values for all times
			stat.MinMaxSum(PRGEN,min,nprocmin,max,nprocmax,sum);
			stat.MinMaxSum(PRCOM,minc,nprocminc,maxc,nprocmaxc,sumc);
			stat.MinMaxSum(PRRCOM,minrc,nprocminrc,maxrc,nprocmaxrc,sumrc);
			stat.MinMaxSum(PRSYN,mins,nprocmins,maxs,nprocmaxs,sums);
			stat.MinMaxSum(PRVAR,minv,nprocminv,maxv,nprocmaxv,sumv);
			stat.MinMaxSum(PROVER,minov,nprocminov,maxov,nprocmaxov,sumov);
			if (dig_time==0) { // format for print
				double max_val=0.0;
				for (i=0;i<=RED;i++) {
                    if (max_val<sumc[i]) max_val=sumc[i];
					if (max_val<sumrc[i]) max_val=sumrc[i];
					if (max_val<sums[i]) max_val=sums[i];
					if (max_val<sumv[i]) max_val=sumv[i];
					if (max_val<sumov[i]) max_val=sumov[i];
				} // end for
				char tval[80];
				sprintf(tval,"%*.*lf",DIGTIME,PREC,max_val);
				dig_time=(short)strlen(tval);
				lenstr=(dig_time+1)*qproc+strlen(nameGen[0])+1;
				if (lenstr<=1024) lenstr=1024;else statpr.ChangeLenStr(lenstr);
				poutstr=new char[lenstr];
				if (poutstr==NULL) throw("Out of memory\n");
			}
			if (gen==TRUE) {
				statpr.StatPrintf("--- The main characteristics --- \n");
				double time1,prodcpu,timef,prod;
				timef=sum[IOTIME];
				prodcpu=sum[CPU];
				prod=sum[CPU]+sum[CPUUSR]+timef;
				if ((n)*max[EXEC]==0) time1=0.0;
				else time1=prod/(n*max[EXEC]);
			    statpr.StatPrintf("%s %*.*lf \n","Parallelization efficiency ",dig_time,PREC,time1);
				statpr.StatPrintf("%s %*.*lf \n",    "Execution time             ",dig_time,PREC,max[EXEC]);
				statpr.StatPrintf("%s %d\n",       "Processors                          ",n);
				statpr.StatPrintf("%s %*.*lf\n",     "Total time                 ",dig_time,PREC,(n)*max[EXEC]);
				if (prod!=0.0) {
				statpr.StatPrintf("%s %*.*lf %s %.*lf %s %.*lf %s %.*lf %c\n","Productive time            ",
				dig_time,PREC,prod,"( CPU=",PREC,sum[CPUUSR]," Sys=",
				PREC,prodcpu,"I/O=",PREC,timef,')');
				}
				if(sum[LOST]>0.0)statpr.StatPrintf("%s %*.*lf \n","Lost  time                 ",dig_time,PREC,sum[LOST]);
				if (sum[INSUFUSR]+sum[INSUF]!=0.0) 
				statpr.StatPrintf("%s %*.*lf %s %.*lf %s %.*lf %c\n","   Insufficient parallelism",dig_time,PREC,sum[INSUFUSR]+sum[INSUF],
				"( User=",PREC,sum[INSUFUSR],"Sys=",PREC,sum[INSUF],')');
				if (sum[SUMCOM]!=0.0)
				statpr.StatPrintf("%s %*.*lf %s %.*lf %s %.*lf %c\n","   Communication           ",dig_time,PREC,sum[SUMCOM],
				"( Real_sync=",PREC,sum[SUMRCOM],"Starts=",PREC,sum[START],')'); 
				if (sum[IDLE]!=0.0)   statpr.StatPrintf("%s %*.*lf\n","   Idle time               ",dig_time,PREC,sum[IDLE]);
				if (sum[IMB]!=0.0)statpr.StatPrintf("%s %*.*lf\n","Load imbalance             ",
					dig_time,PREC,sum[IMB]);
				if (sum[SUMSYN]!=0.0) statpr.StatPrintf("%s %*.*lf\n","Synchronization            ",dig_time,PREC,sum[SUMSYN]);
				if (sum[SUMVAR]!=0.0) statpr.StatPrintf("%s %*.*lf\n","Time variation             ",dig_time,PREC,sum[SUMVAR]);
				if (sum[SUMOVERLAP]>0.0)statpr.StatPrintf("%s %*.*lf\n","Overlap                    ",dig_time,PREC,
				sum[SUMOVERLAP]);
				long ncall=0;
				int dig_stat=DIGSTAT;
				for (i=0;i<=RED;i++) ncall=ncall+stat.ReadCall(typecom(i));
				if (ncall>0) {
                    statpr.StatPrintf("%*c",ltxt,' ');
					char tval[20];
					sprintf(tval,"%ld",ncall);
					int l=strlen(tval);
					if (l>DIGSTAT)dig_stat=l; 
					statpr.StatPrintf("%*s",dig_stat," Nop ");
					for (int j=SUMCOM;j<=SUMOVERLAP;j++) {
						if (sum[j]>0.0) 
						statpr.StatPrintf("%*s ",dig_time,nameOper[j-SUMCOM]);
					} // end for
					statpr.StatPrintf("\n");
				}// end if
                for (i=0;i<=RED;i++) {
                    ncall=stat.ReadCall(typecom(i));
					if (ncall>0) {
						statpr.StatPrintf("%s",nameCom[i]);
						statpr.StatPrintf("%*d ",dig_stat,ncall);
						if (sum[SUMCOM]>0.0)statpr.StatPrintf("%*.*lf ",dig_time,PREC,sumc[i]);
						if (sum[SUMRCOM]>0.0)statpr.StatPrintf("%*.*lf ",dig_time,PREC,sumrc[i]);
						if (sum[SUMSYN]>0.0)statpr.StatPrintf("%*.*lf ",dig_time,PREC,sums[i]);
						if (sum[SUMVAR]>0.0)statpr.StatPrintf("%*.*lf ",dig_time,PREC,sumv[i]);
						if (sum[SUMOVERLAP]>0.0)statpr.StatPrintf("%*.*lf ",dig_time,PREC,sumov[i]);
						statpr.StatPrintf("\n");
					} // end if ncall>0
				} // end for
				if (iIM>0 || jIM>0) { // statistics matrix
					for (unsigned long np=1;np<=qproc;np++) {
					double prod[StatGrpCount],lost[StatGrpCount],sumprod=0.0,sumlost=0.0;
					double calls[StatGrpCount],sumcalls=0.0;
					stat.GrpTimes(prod,lost,calls,np);
					sprintf(p_heading,"%ld",np);
					int ll=strlen(nameGen[0])-strlen(p_heading)-strlen(" Nproc=")-2;
					statpr.StatPrintf("%s %d %*c %*s %*s %*s\n"," Nproc=",np,ll,' ',
						dig_time,"CALL COUNT",dig_time,"PRODUCT TIME",dig_time,
						"LOST TIME");
					for (i=0;i<StatGrpCount;i++) {
						sumprod=sumprod+prod[i];
						sumlost=sumlost+lost[i];
						sumcalls=sumcalls+calls[i];
						//if (calls[i]>0 || prod[i]!=0.0 || lost[i]!=0.0 ) {
							statpr.StatPrintf("%s %*.*lf %*.*lf %*.*lf \n",nameGenMT[i],
								dig_time,PREC,calls[i],
								dig_time,PREC,prod[i],
								dig_time,PREC,lost[i]);
						//}
					} // end for
					statpr.StatPrintf("%s %*.*lf %*.*lf %*.*lf \n","      Total:           ",
					dig_time,PREC,sumcalls,dig_time,PREC,sumprod,dig_time,PREC,sumlost);
					} // end for qproc
				} // end statistics matrix
			} // end main characteristics
			if (comp==TRUE) {
				// comparative characteristics
				statpr.StatPrintf("--- The comparative characteristics --- \n");
				poutstr[0]=0;
				statpr.StatPrintf ("%*c",strlen(nameGen[0])+1,' ');
				int i;
				for (i=0;i<3;i++) {
					if (i==2)statpr.StatPrintf("%*s\n",dig_time,namecomp[i]);
					else statpr.StatPrintf("%*s %*s",dig_time,namecomp[i],
						DIGSTAT,"N proc");
				}
				// general characteristics
				for (i=0;i<=ITER;i++) {
					if (sum[i]>0.0) {
						int prec;
						double tt=sum[i]/n;
						if ((typetime)(i)==PROC || (typetime)(i)==ITER)
							prec=0;else prec=PREC;
						statpr.StatPrintf("%s %*.*lf %*d %*.*lf %*d %*.*lf \n",
							nameGen[i],dig_time,prec,
							min[i],DIGSTAT,nprocmin[i],dig_time,prec,max[i],DIGSTAT,
							nprocmax[i],dig_time,prec,tt);
					}
				}
				long ncall=0;
				// characteristics of collective operations
				for (i=0;i<=RED;i++) ncall=ncall+stat.ReadCall(typecom(i));
				if (ncall>0) {
					statpr.StatPrintf("%*c",ltxt-2,' ');
					for (int j=SUMCOM;j<=SUMOVERLAP;j++) {
						if (sum[j]>0.0) 
						statpr.StatPrintf("%*s  ",dig_time+DIGSTAT,nameOper[j-SUMCOM]);
					}
					statpr.StatPrintf("\n");
					for (i=0;i<=RED;i++) {
					for (int k=0;k<3;k++) {
						if (sumc[i]==0.0 && sumrc[i]==0.0 && sums[i]==0.0 &&
							sumv[i]==0.0 &&sumov[i]==0.0) break;
						double t[CALL];//com,realcom,syn,var,overlap
						unsigned long pnp[CALL];
						// 0 - min; 1 - max; 2 - sum
						switch (k) {
							case 0:
								t[0]=minc[i];t[1]=minrc[i];
								t[2]=mins[i];t[3]=minv[i];
								t[4]=minov[i];
								pnp[0]=nprocminc[i];
								pnp[1]=nprocminrc[i];
								pnp[2]=nprocmins[i];
								pnp[3]=nprocminv[i];
								pnp[4]=nprocminov[i];
								break;
							case 1:
								t[0]=maxc[i];t[1]=maxrc[i];
								t[2]=maxs[i];t[3]=maxv[i];
								t[4]=maxov[i];
								pnp[0]=nprocmaxc[i];
								pnp[1]=nprocmaxrc[i];
								pnp[2]=nprocmaxs[i];
								pnp[3]=nprocmaxv[i];
								pnp[4]=nprocmaxov[i];
								break;
							case 2:
								t[0]=sumc[i]/n;t[1]=sumrc[i]/n;
								t[2]=sums[i]/n;t[3]=sumv[i]/n;
								t[4]=sumov[i]/n;
								pnp[0]=0;
								pnp[1]=0;
								pnp[2]=0;
								pnp[3]=0;
								pnp[4]=0;
								break;
							default:
								statpr.StatPrintf("Unknown type=%d\n",k);
								exit(1);
						}// end switch
						statpr.StatPrintf("%s%s",nameCom[i],namecomp[k]);
						for (int j=SUMCOM;j<=SUMOVERLAP;j++) {
							if (sum[j]>0.0) {
								if (pnp[0]==0) {
								statpr.StatPrintf("%*.*lf ",
								dig_time,PREC,t[j-SUMCOM]);
								statpr.StatPrintf("%*c",DIGSTAT+1,' ');
								}
								else 
								statpr.StatPrintf("%*.*lf %*d ",
								dig_time,PREC,t[j-SUMCOM],
								DIGSTAT,pnp[j-SUMCOM]);
							}
						}
						statpr.StatPrintf("\n");
					} //end for
				}//end for
				}
			}
			if (proc==TRUE) {
				// execution characteristics
				statpr.StatPrintf("--- The execution characteristics --- \n");
				statpr.StatPrintf("%s","                       ");
				unsigned long i;
				// print numbers of processor
				for (i=0;i<n;i++) {//!!! qproc
					int pr=FALSE;
					if (pnumb==NULL) pr=TRUE;
					else {
						for (int j=0; j<qnumb;j++) {
							if(i+1>=pnumb[j] && i+1<=pnumb[j+1]) pr=TRUE;
						}
					}
					if (pr==TRUE) {
						statpr.StatPrintf("%*d ",dig_time,i+1); // probel
					}
				}
				statpr.StatPrintf("\n");
				// general characteristics
				for (i=0;i<=ITER;i++) {
					stat.ReadProc(PRGEN,pnumb,qnumb,dig_time,sum[i],poutstr);
					if (poutstr[0]!='\0')statpr.StatPrintf("%s\n",poutstr);
					//statpr.StatPrintf("\n");
				}
				//statpr.StatPrintf("\n");
				// characteristics of collective operatios
				long ncall=0;
				for (int k=0;k<=RED;k++) ncall=ncall+stat.ReadCall(typecom(k));
					for (int j=SUMCOM;j<=SUMOVERLAP;j++) {
						double *ps;
						switch (j) {
						case SUMCOM: ps=sumc;break;
						case SUMRCOM: ps=sumrc;break;
						case SUMSYN: ps=sums;break;
						case SUMVAR: ps=sumv;break;
						case SUMOVERLAP: ps=sumov;break;
						default:statpr.StatPrintf("Unknown type=%d\n",j);
						exit(1);
					}// end for j
					int i=0;
					//if (j==SUMOVERLAP) ncall=0; //for pc sum[j]=0.0
					if (sum[j]>0.0 && ncall>0) {
						statpr.StatPrintf("           %s\n",nameGen[j]);
						for (i=0;i<=RED;i++) {
							stat.ReadProc((typeprint)(j-SUMCOM+1),pnumb,qnumb,dig_time,ps[i],poutstr);
							if (poutstr[0]!='\0')statpr.StatPrintf("%s\n",poutstr);
						}
					}
				} // end for k
			}//exec characteristics
		} // if nlev<=nlevel
		n=stat.TreeWalk();
	}
	//names and times of processors
	char *pname=NULL,*pnamemin=NULL,*pnamemax=NULL;
	double time,mintime=DBL_MAX,maxtime=0.0,sumtime=0.0;
	stat.NameTimeProc(0,&pname,&time);
	if (pname==NULL) exit(1); // not MPI
	unsigned long minn=0,maxn=0;
	statpr.StatPrintf("%s","-------------------------------------------------------------------------\n");
	statpr.StatPrintf("Name (number) and performance time of processors\n");
	for (unsigned long i1=0;i1<qproc;i1++) {
		stat.NameTimeProc(i1,&pname,&time);
		sumtime=sumtime+time;
		if (time<mintime) {mintime=time;minn=i1+1;pnamemin=pname;}
		if (time>maxtime) {maxtime=time; maxn=i1+1;pnamemax=pname;}
		statpr.StatPrintf("%s(%d) %lf\n",pname,i1+1,time);
	}
	statpr.StatPrintf("min - %s(%d) %lf; max - %s(%d) %lf; mid - %lf\n",
		pnamemin,minn,mintime,pnamemax,maxn,maxtime,sumtime/qproc);
	} // end try
	catch (bad_alloc ex) {
		printf("Out of memory\n");
		exit(1);
	}
	catch (exception ex) {
		printf("Exception in standart library %s\n",ex.what());
		exit(1);
	}
	catch (char *str) {
		printf("%s\n",str);
		exit(1);
	}
	return 0;
}

