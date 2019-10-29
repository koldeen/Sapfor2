#ifndef _SYSSTAT_H
#define _SYSSTAT_H
typedef struct {
	double  CallCount; 
	double  ProductTime;
	double  LostTime;
}s_GRPTIMES;

#define StatGrpCount 18
#define UserGrp       0 
#define MsgPasGrp     1  
#define StartRedGrp   2  
#define WaitRedGrp    3  
#define RedGrp        4  
#define StartShdGrp   5  
#define WaitShdGrp    6  
#define ShdGrp        7  
#define DistrGrp      8  
#define ReDistrGrp    9  
#define MapPLGrp     10  
#define DoPLGrp      11  
#define ProgBlockGrp 12  
#define IOGrp        13  
#define RemAccessGrp 14  
#define UserDebGrp   15  
#define StatistGrp   16  
#define SystemGrp    17  

#endif
