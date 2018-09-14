

#ifndef Already_Included_IP
#define Already_Included_IP 1

#include <stdio.h>
#include <vector>

#define maxVars 50
#define maxGEQs 150
#define maxEQs 27


typedef int EqnKey;


typedef struct _eqn 
{
    /*_eqn()
    {
        coef.resize(maxVars + 1);

        std::fill(coef.begin(), coef.end(), 0);
        key = 0;
        touched = 0;
        color = 0;
    }*/

    EqnKey  key;
    int     touched;
    int     color;
    //std::vector<int> coef;
    int coef[maxVars + 1];
} *Eqn;

#define headerWords 3

typedef struct _problem 
{
    _problem()
    {
        forwardingAddress.resize(maxVars + 2);
        _var.resize(maxVars + 2);
        _GEQs.resize(maxGEQs);
        _EQs.resize(maxEQs);
        _SUBs.resize(maxVars + 1);
    }

    int _nVars, _numEQs, _numGEQs, _safeVars,_numSUBs;
    int hashVersion;
    int variablesInitialized;
    int variablesFreed;
    std::vector<int> _var;
    //int _var[maxVars + 2];
    std::vector<int> forwardingAddress;
    //int forwardingAddress[maxVars + 2];
    char *(*_getVarName)(unsigned int var, void *args);
    void *_getVarNameArgs;
    std::vector<_eqn> _GEQs; 
    //_eqn _GEQs [maxGEQs];
    std::vector<_eqn> _EQs;
    //_eqn _EQs[maxEQs];
    std::vector<_eqn> _SUBs;
    //_eqn _SUBs[maxVars + 1];
} Problem;



#define UNKNOWN 2
#define SIMPLIFY 3
#define posInfinity (0x7ffffff)
#define negInfinity (-0x7ffffff)
#define red 1
#define black 0

#define eqnncpy(e1,e2,s) {int *p00,*q00,*r00; p00 = (int *)(e1); q00 = (int *)(e2); r00 = &p00[headerWords+1+s]; while(p00 < r00) *p00++ = *q00++; }

#define eqncpy(e1,e2) eqnncpy(e1, e2, nVars)
#define eqnnzero(e,s) { int *p00,*r00; p00 = (int *)(e); r00 = &p00[headerWords+1+(s)]; while(p00 < r00) *p00++ = 0;}
#define eqnzero(e) eqnnzero(e,nVars)

#define intDiv(a,b) ((1024 * b + a)/b - 1024)
#define intMod(a,b) ((a)-(b)*intDiv(a,b))


#define singleVarGEQ(e,nV) ((e).key != 0 && -maxVars <= (e).key && (e).key <= maxVars)


extern void  initializeOmega();

extern void initializeProblem(Problem *);
extern void problemcpy(Problem *, Problem *);
extern void  printProblem(Problem *);
extern void  printRedEquations(Problem *);
extern void  prettyPrintProblem(Problem *);
extern int  simplifyProblem(Problem *);
extern int  simplifyApproximate(Problem *);
extern void unprotectVariable(Problem *, int var);
extern void negateGEQ(Problem *, int);


/* set extra to 0 for normal use */
extern void printEqn (Problem *p, Eqn e, int is_geq, int extra);
extern void sprintEqn (char *str, Problem *p, Eqn e, int is_geq, int extra);

/*
   Return 1 if red equations constrain the set of possible solutions.
   We assume that there are solutions to the black equations by themselves,
   so if there is no solution to the combined problem, we return 1.
 */
extern int hasRedEquations(Problem * problemPtr, bool expensive);

extern int eliminateRedundant (Problem *problemPtr, bool expensive);
extern void eliminateRed (Problem *problemPtr, bool eliminateAll);

/* constrainVariableSign also unprotects var & simplifies the problem */
extern int
constrainVariableSign(Problem *, int color, int var, int sign); 

/* constrainVariableValue adds an EQ that makes variable var have
   value "value", even if variable i has been substituted out */
extern void 
constrainVariableValue(Problem *problemPtr, int color, int var, int value);

extern int 
queryVariable(Problem *, int var, int *lowerBound, int *upperBound);

extern int
queryVariableSigns(Problem *, int, int, int, int, int, 
int, 
bool *, 
int*);

extern int
queryVariableBounds(Problem * problemPtr, int i, int *l, int *u);

extern int solve(Problem *problemPtr, int desiredResult);

extern void setOutputFile(FILE *file);
     /* set "file" to the file to which the output of printProblem should go */

extern int reduceWithSubs;

extern int omegaPrintResult;
 /* set to non-zero to have constrainVariableSign and simplifyProblem
    print the resulting simplified problems */

extern int firstCheckForRedundantEquations;

extern void (*whenReduced)(Problem *problemPtr);
extern void noProcedure(Problem *problemPtr);
extern void Exit(int c);

#endif

