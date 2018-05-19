#pragma once

#include <vector>
#include <set>
#include <string>

#include "set.h"
////////////////////////////////////////////////////////////
// to deal with data dep, scalar are considered apart
// but included as special nodes in the dep grap...
////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// class dep graph used for restructuring
// two classes, the graph and the graph node
//////////////////////////////////////////////////////////////

class depNode {
public:
  SgStatement *stmtin;
  SgStatement *stmtout;
  SgExpression *varin; // this is var;
  SgExpression *varout; // this is var;
  int          typedep; // WRONGDEP something wrong happend, ARRAYDEP array dependence, > 1 SCALAR DEP
  int          kinddep; // ddflow, ddanti, ddoutput
  int lenghtvect;
  std::vector<signed short> distance;
  std::vector<signed short> knowndist;

  depNode(SgStatement *sin,SgStatement *sout, SgExpression *vin, SgExpression *vout, int tdep, int kdep, int *dist, int *kdist, int le);
  ~depNode();
  void displayDep() const;
  std::string createDepMessagebetweenArrays() const;
};

//////////////////////////////////////////////////////////////
// The graph is represented by 
//////////////////////////////////////////////////////////////

class depGraph {
    std::vector<depNode*> nodes;    
public:
    const std::set<std::string> privVars;
    SgFile *file;
    Set *arrayRef;
    Set *induc;
    SgSymbol     *tsymb[40/*MAXNESTEDLOOP*/];
    int          loopnum;
    SgStatement *func;
    SgStatement *loop;
    int perfectNestedLevel;
    int nbstmt;
    SgStatement **tabstat;
    int *tabtag;
    depGraph(SgFile *fi, SgStatement *f, SgStatement *l, const std::set<std::string> &privVars);
    ~depGraph();
    void addAnEdge(SgStatement *sin, SgStatement *sout, SgExpression *vin, SgExpression *vout, int tdep, int kdep, int *dist, int *kdist, int le);

    void display();
    void scalarRefAnalysis(SgStatement *loop);
    void redoScalarRefAnalysis(SgStatement *loop);
    depNode *firstNode();
    int isLoopCarryingTheDep(SgStatement *loop, depNode *node);
    depNode *isThereAnEdge(SgStatement *s1, SgStatement *s2);
    int isThereAnEdgeSCC(SgStatement *s1, SgStatement *s2, SgStatement *doloop);
    void depthTraversal(int stmtid, SgStatement *doloop);
    void depthTraversalReverse(int stmtid, int mark, SgStatement *doloop);
    int getHigherMark();
    int getZeroMark();
    int computeSCC(SgStatement *stmtin);
    const std::vector<depNode*>& getNodes();
    // ... much more here
};
