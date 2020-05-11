

#ifndef Already_Included_IP
#define Already_Included_IP 1

#include <stdio.h>
#include <vector>
#include <algorithm>

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
    std::vector<int> coef;
    //int coef[maxVars + 1];
} *Eqn;

#define headerWords 3

typedef struct _problem 
{
private:
    int _nVars;
    int _numEQs, _numGEQs, _numSUBs;

    void resizeEqs()
    {
        //printf("%d %d %d -> %d\n", _numEQs, _numGEQs, _numSUBs, _nVars + 2);
        for (int z = 0; z < _numEQs; ++z)
            _EQs[z].coef.resize(_nVars + 2);
        for (int z = 0; z < _numGEQs; ++z)
            _GEQs[z].coef.resize(_nVars + 2);
        for (int z = 0; z < _numSUBs; ++z)
            _SUBs[z].coef.resize(_nVars + 2);
    }
public:
    _problem()
    {
        _numEQs = _numGEQs = 0;
        _numSUBs = 1;
        forwardingAddress.resize(maxVars + 2);
        _var.resize(maxVars + 2);
        _GEQs.resize(maxGEQs);
        _EQs.resize(maxEQs);
        _SUBs.resize(maxVars + 1);
    }

    void _init()
    {
        forwardingAddress.resize(maxVars + 2);
        _var.resize(maxVars + 2);
        _GEQs.resize(maxGEQs);
        _EQs.resize(maxEQs);
        _SUBs.resize(maxVars + 1);
    }

    void _init(int eqs, int ges, int subs, int nvars)
    {
        _nVars = nvars;
        _numEQs = eqs;
        _numGEQs = ges;
        _numSUBs = subs;
        resizeEqs();
    }


    int getVarsN() const { return _nVars; }
    void setVarsN(const int nvars)
    {
        _nVars = nvars;
        resizeEqs();
    }
    void addToVarsN(const int nvars)
    {
        _nVars += nvars;
        resizeEqs();
    }

    int getNumEqs() const { return _numEQs; }
    int getNumGEqs() const { return _numGEQs; }
    int getNumSUBs() const { return _numSUBs; }
    
    void setNumEqs(const int val) 
    {        
        _numEQs = val; 
        //printf("EQ %d -> %d\n", _numEQs, _nVars + 2);
        for (int z = 0; z < _numEQs; ++z)
            _EQs[z].coef.resize(_nVars + 2);
    }
    void setNumGEqs(const int val)
    {        
        _numGEQs = val;
        //printf("GEQ %d -> %d\n", _numGEQs, _nVars + 2);
        for (int z = 0; z < _numGEQs; ++z)
            _GEQs[z].coef.resize(_nVars + 2);
    }
    void setNumSUBs(const int val) 
    {        
        _numSUBs = val; 
        //printf("SUB %d -> %d\n", _numSUBs, _nVars + 2);
        for (int z = 0; z < _numSUBs; ++z)
            _SUBs[z].coef.resize(_nVars + 2);
    }

    void addNumEqs(const int val) 
    {
        _numEQs += val;
        //printf("EQ %d -> %d\n", _numEQs, _nVars + 2);
        for (int z = 0; z < _numEQs; ++z)
            _EQs[z].coef.resize(_nVars + 2);
    }
    void addNumGEqs(const int val) 
    {
        _numGEQs += val;
        //printf("GEQ %d -> %d\n", _numGEQs, _nVars + 2);
        for (int z = 0; z < _numGEQs; ++z)
            _GEQs[z].coef.resize(_nVars + 2);
    }
    void addNumSUBs(const int val) 
    {
        _numSUBs += val; 
        //printf("SUB %d -> %d\n", _numSUBs, _nVars + 2);
        for (int z = 0; z < _numSUBs; ++z)
            _SUBs[z].coef.resize(_nVars + 2);
    }

    int _safeVars;
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

//#define eqnncpy(e1,e2,s) {int *p00,*q00,*r00; p00 = (int *)(e1); q00 = (int *)(e2); r00 = &p00[headerWords+1+s]; while(p00 < r00) *p00++ = *q00++; }

static void eqnncpy(_eqn *dst, const _eqn *src, const int s)
{
    dst->color = src->color;
    dst->key = src->key;
    dst->touched = src->touched;
    dst->coef.resize((src->coef.size() > s + 2) ? src->coef.size() : s + 2);
    std::fill(dst->coef.begin(), dst->coef.end(), 0);

    for (int z = 0; z < ((src->coef.size() < s + 1) ? src->coef.size() : s + 1); ++z)
        dst->coef[z] = src->coef[z];    
}

#define eqncpy(e1,e2) eqnncpy(e1, e2, nVars)
//#define eqnnzero(e,s) { int *p00,*r00; p00 = (int *)(e); r00 = &p00[headerWords+1+(s)]; while(p00 < r00) *p00++ = 0;}

static void eqnnzero(_eqn *dst, const int s)
{
    dst->color = 0;
    dst->key = 0;
    dst->touched = 0;
    dst->coef.resize(s + 2);
    for (int z = 0; z < s + 2; ++z)    
        dst->coef[z] = 0;
}

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

