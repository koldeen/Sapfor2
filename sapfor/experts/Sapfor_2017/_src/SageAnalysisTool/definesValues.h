
// set of the defined values used for the data dependence analsysis;
// for most of the files

#define MAXITDATAFLOW 100
// needs to be bigger than real loop, symbols may appear twice.
#define MAXNESTEDLOOP 40
#define MAXDIMARRAY 7
#define MAXP 100
#define MAXNODE 10000
#define NOARRAYREF 0
#define NO_STEP 10000


//constanteSet.C
#define  UNDEFFLAG     1
#define  NONCONSTFLAG  2
#define  CONSTFLAG     3

//depGraph.C
#define WRONGDEP     0
#define ARRAYDEP     1
#define PRIVATEDEP   2
#define REDUCTIONDEP 3
#define SCALARDEP    4
#define DEPZERO 1
#define DEPGREATER 2
#define DEPLESS 4

//dependence.C
#define OUTDEP    1
#define FLOWDEP   2
#define ANTIDEP   3
#define UNKNOWNDEP 4  

//reductionCode.C
#define UNKNOWREDUCTION 0
//SUM
#define SADDREDUCTION   2
#define DADDREDUCTION   3
#define IADDREDUCTION   4
//MULT
#define SMULREDUCTION   5 
#define DMULREDUCTION   6
#define IMULREDUCTION   7
//DIV
#define SDIVREDUCTION   8 
#define DDIVREDUCTION   9
#define IDIVREDUCTION   10
//MAX
#define SMAXREDUCTION   11 
#define DMAXREDUCTION   12
#define IMAXREDUCTION   13
//MIN
#define SMINREDUCTION   14 
#define DMINREDUCTION   15
#define IMINREDUCTION   16
//LOGICAL
#define ANDREDUCTION    17
#define ORREDUCTION     18
#define EQVREDUCTION    19
#define NEQVREDUCTION   20

// set.C
#define MAXELEMENT 10000000
#define ALLOCATECHUNKSET 10000
