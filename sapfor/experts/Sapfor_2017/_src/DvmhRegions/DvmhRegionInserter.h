#pragma once
/*
 * DvmhRegionIsertor.h
 *
 *  Created on: May 14, 2018
 *    Author: vladislav
 */
#pragma once
#include "dvm.h"
#include "acc_analyzer.h"
#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../Utils/SgUtils.h"
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

struct LoopCheckResults 
{
    bool usesIO;
    bool hasImpureCalls;

    LoopCheckResults() : usesIO(false), hasImpureCalls(false) { }
    LoopCheckResults(bool io, bool calls) : usesIO(io), hasImpureCalls(calls) { }
};

struct DvmhRegion 
{
    std::vector<LoopGraph*> loops;

    std::string fun_name;
    std::vector<SgSymbol*> needActualisation;
    std::vector<SgSymbol*> needActualisationAfter;

    DvmhRegion() { }
    DvmhRegion(LoopGraph *loopNode, const std::string &fun_name);

    bool isInRegion(SgStatement *);
    SgStatement* getFirstSt() const;
    SgStatement* getLastSt() const;

    bool addToActualisation(SgSymbol* s) 
    {
        for (auto &present : needActualisation) 
            if (s == present) 
                return false;       

        needActualisation.push_back(s);
        return true;
    }
};

class DvmhRegionInsertor 
{
    SgFile *file;
    const std::vector<LoopGraph*> &loopGraph;
    std::vector<DvmhRegion*> regions;

    DvmhRegion* getContainingRegion(SgStatement *);
    void printFuncName(SgStatement *);
    void findEdgesForRegions(const std::vector<LoopGraph*>&);
    bool hasLimitsToDvmhParallel(const LoopGraph*) const;
    void insertActualDirectives();
    void insertRegionDirectives();
    void insertActualDirectiveBefore(SgStatement *, std::vector<SgSymbol*>, int);
    void mergeRegions();
    //void insertActualForRedistribute();
    LoopCheckResults checkLoopForPurenessAndIO(LoopGraph*, const std::map<std::string, FuncInfo*> &allFuncs);
    LoopCheckResults updateLoopNode(LoopGraph*, const std::map<std::string, FuncInfo*> &allFuncs);

public:

    DvmhRegionInsertor(SgFile*, const std::vector<LoopGraph*>&);
    void updateLoopGraph(const std::map<std::string, FuncInfo*> &allFuncs);
    void insertDirectives();
    ~DvmhRegionInsertor()
    {
        for (auto& reg : regions)
            delete reg;
    }
};

// Reaching defenitions for every symbol used in the statement
typedef std::map<SgSymbol*, std::set<SgStatement*>> StDefs;

// Keeps reaching defenitions for every statement of the project
class RDKeeper 
{
    /* Finds set of symbols used in the expression. */
    static std::set<SgSymbol*> getSymbolsFromExpression(SgExpression *exp);

    /* Finds set of symbols used in whole statement containing several expressions. */
    static std::set<SgSymbol*> getUsedSymbols(SgStatement* st);
public:
    std::map<SgStatement*, StDefs > defsByStatement;

    RDKeeper(SgFile*);
    StDefs getDefs(SgStatement *);
};

// enum DFGType {block, par_loop};

// /*   Distributed Flow Graph Node.
//      Node represents either:
//      (1) basic block, containing usages of distibuted arrays;
//      (2) set of basic blocks, composing parallel loop.
// */
// class DFGNode {
// public:
//  vector<CBasicBlock *> initial;
//  vector<DFGNode*> prev;
//  vector<DFGNode*> succ;
//  vector<SgStatement*> content;
//  vector<SgSymbol*> d_arrays;
//  DFGType type;
//  int id;

//  /* Initializes DFGNode (1) from CBasicBlock. */
//  DFGNode(CBasicBlock* bblock);

//  /* Initializes DFGNode (2) from list of DFGNode's. */
//  DFGNode(vector<DFGNode*> elements);

//  /* Finds set of symbols used in the expression. */
//  static set<SgSymbol *> getSymbolsFromExpression(SgExpression *exp);

//  /* Finds set of symbols used in whole statement containing several expressions. */
//  static set<SgSymbol *> getUsedSymbols(SgStatement* st);

//  /* Returns std::string containing human readable information representing DFGNode. */
//  std::string getInfo() const;

//  /* Links new successor for the DFGNode. Returns false if this successor was already linked. */
//  bool addSucc(DFGNode* new_succ);

//  /* Links new predecessor for the DFGNode. Returns false if this predecessor was already linked. */
//  bool addPrev(DFGNode* new_prev);
// };

// /*   Abstract control flow graph. Consists of linked DFGNodes. */
// class AFlowGraph {
//  std::map<std::string, std::vector<DFGNode*> > fun_graphs;
//  // TODO: memory cleaning
// public:
//  /* Returns DFGNode by function name and node id. */
//  DFGNode* getNode(std::string fun_name, int id);

//  /* Builds AFlowGraph from scratch. Result of intermediate construction of the classic Contlor Flow Graph is used. */
//  AFlowGraph(SgFile file, vector<DvmhRegion*> regions);
// };
