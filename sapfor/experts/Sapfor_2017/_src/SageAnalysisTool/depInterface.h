////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  includes for data dep information ////////////////////////
////// FB July 94 Indiana University ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// the set class
#include "set.h"

#include "definesValues.h"


//////////////////////////////////////////////////////////////////////////////////
// external for the anotation system
//////////////////////////////////////////////////////////////////////////////////
#include "annotationDriver.h"
extern SgAnnotation *getTheAnnotationThatApply(SgStatement *stmt, char *kind);
extern SgAnnotation * getTheAnnotationWithString(char *kind);
extern int isAnnotationWithString(SgStatement *stmt, char *kind, int len);
extern void initAnnotationSystem(int printann);


//////////////////////////////////////////////////////////////////////////////////
// some external from loop transformations
//////////////////////////////////////////////////////////////////////////////////

extern int tileLoops(SgStatement *func, SgStatement *b, int *size, int nb);
extern int distributeLoopSCC(SgStatement *b, int *sccTable, int leadingdim, int numSCC);
extern int loopFusion(SgStatement *loop1,SgStatement *loop2);

///////////////////////////////////////////////////////////////////////////////////////
// Control FLOW part of declaration
///////////////////////////////////////////////////////////////////////////////////////

extern void controlFlow(SgStatement *stmt, SgStatement *func, 
                        SgStatement **pred, SgStatement **suc, 
                        int *predin,int *sucint);

///////////////////////////////////////////////////////////////////////////////////////
// declaration for the  data flow  framework
///////////////////////////////////////////////////////////////////////////////////////

extern Set *genSet[MAXNODE];
extern Set *killSet[MAXNODE];
extern Set *inSet[MAXNODE];  
extern Set *outSet[MAXNODE];

extern void iterativeForwardFlowAnalysis(SgFile *file, 
                                  SgStatement *func, 
                                  Set *(*giveGenSet)(SgStatement *func,SgStatement *stmt),
                                  Set *(*giveKillSet)(SgStatement *func,SgStatement *stmt),
                                  int (*feq)(void *e1, void *e2), 
                                  void *(*fcomb)(void *e1, void *e2),
                                  void (*fp)(void *e1));

extern void generalIterativeFlowAnalysis(SgFile *file, 
                                  SgStatement *func, 
                                  Set *(*transfertSet)(SgStatement *func,SgStatement *stmt, Set *setin),
                                  int (*feq)(void *e1, void *e2), 
                                  void* (*fcomb)(void *e1, void *e2),
                                  void (*fp)(void *e1));

///////////////////////////////////////////////////////////////////////////////////////
// declaration for defuse and reaching definition
///////////////////////////////////////////////////////////////////////////////////////

#include "definitionSet.h"
extern void initDefUseTable(SgStatement *func);
extern Set *makeGenSet(SgStatement *func,SgStatement *stmt);
extern Set *makeKillSet(SgStatement *func,SgStatement *stmt);
extern int symbRefEqual(void *e1, void *e2);
extern void myPrint(void *e1);

///////////////////////////////////////////////////////////////////////////////////////
// Part for constante propagation.....
///////////////////////////////////////////////////////////////////////////////////////

#include "constanteSet.h"
extern int constPropEqual(void *e1, void *e2);
extern void constPropPrint(void *e1);
extern void * constPropCombine(void *e1, void *e2);
extern Set *transConstante(SgStatement *func,SgStatement *stmt, Set *setin);

///////////////////////////////////////////////////////////////////////////////////////
// Part for induction variable
///////////////////////////////////////////////////////////////////////////////////////

#include "inducVar.h"
extern int inducVarEqual(void *e1, void *e2);
extern void inducVarPrint(void *e1);
extern int definitionInStmt(SgStatement *func,SgStatement *stmtin, SgExpression *defvar);
extern Set *computeConstanteInStmt(SgStatement *func,SgStatement *stmtin);
extern Set *computeInductionVariables(SgStatement *func,SgStatement *stmt);
extern Set *getAllInductionVar(SgStatement *func,
                               SgStatement *stmt,int level, int *num,int include);

///////////////////////////////////////////////////////////////////////////////////////
// Part for computing array reference
///////////////////////////////////////////////////////////////////////////////////////

#include "arrayRef.h"
extern int NbLinearRef;
extern int NbNonLinearRef;
extern int linearRepArray(SgExpression  *ex1, SgSymbol **symb, 
                          int size, 
                          int linear[MAXDIMARRAY][MAXNESTEDLOOP], 
                          int *cst);
extern int arrayEqual(void *e1, void *e2);
extern void arrayPrint(void *e1);
extern Set *loopArrayAccessAnalysis(SgStatement *func,SgStatement *stmt, 
                                    SgSymbol **tsymb, Set **induc);

///////////////////////////////////////////////////////////////////////////////////////
// for data dependence computation (uses omega Test)
///////////////////////////////////////////////////////////////////////////////////////

#include "dependence.h"
extern Set *computeLoopDependencies(SgStatement *func,Set *inset, SgSymbol **tsymb, Set *induc);
extern "C" void SetOmegaDebug();

///////////////////////////////////////////////////////////////////////////////////////
// for data dependence computation (uses omega Test)
///////////////////////////////////////////////////////////////////////////////////////

#include "depGraph.h"
extern void initializeDepAnalysisForFunction(SgFile *file, SgStatement *f);

///////////////////////////////////////////////////////////////////////////////////////
// from intrinsic.C
///////////////////////////////////////////////////////////////////////////////////////

extern int isStmtCallToFuncNotIntrinsic(SgStatement *stmt);
extern int isSymbolIntrinsic(SgSymbol *symb);
extern int isExprCallToFuncNotIntrinsic(SgExpression *exp);



