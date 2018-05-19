
/////////////////// TO BE INCLUDED FOR USING DATA DEPENDENCE ///////////////////////

#include "depInterface.h"

// initialize for a full file;

extern void doDependenceAnalysisOnTheFullFile(SgFile *file, int printdep, int printannotation, int verbose);
extern void doDependenceAnalysisForAFunction(SgFile *file,  SgStatement *func, int printdep, int printannotation, int verbose);
extern int isThereEquivalenceStatement(SgStatement *func);
extern int isWriteToSymbolInStatement(SgSymbol *symb, SgStatement *loop, depGraph *depg);
extern int leadingDimension(depNode *datadep,int entryLevel);
extern int numberOfOuterParallelLoops(SgStatement *loop, depGraph *depg,int entryLevel);
extern void initAnnotationsSysExt(const int printannotation);
