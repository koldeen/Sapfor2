#pragma once

#include <map>
#include <string>
#include "dvm.h"
#include "../Distribution/Distribution.h"
#include "../GraphLoop/graph_loops.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../GraphCall/graph_calls.h"
#include "../SgUtils.h"

#include "acc_analyzer.h"


struct VariableItem;
class VarsKeeper;
class DataFlowItem;

SgExpression* ReplaceParameter(SgExpression *e);
SgExpression* ReplaceArrayBoundSizes(SgExpression *edim);
SgExpression* ReplaceConstant(SgExpression *e);
void getCoefsOfSubscript(std::pair<int, int> &retCoefs, SgExpression *exp, SgSymbol *doName);
int CalculateInteger(SgExpression *expr, int &result);
void expressionAnalyzer(SgFile *file,
        std::map<std::string, std::vector<DefUseList>> &defUseByFunctions,
        std::map<std::string, CommonBlock> &commonBlocks,
        std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo);
void expressionAnalyzer(SgStatement *function);

void calculate(SgExpression *&exp);
void replaceConstatRec(SgExpression *&exp);

enum REPLACE_PTR_TYPE { SG_EXPRESSION, SG_STATEMENT };

void revertReplacements(std::string filename);

struct StatementObj {
    SgStatement* stmt;

    StatementObj(SgStatement* st): stmt(st) { }

    inline bool operator<(const StatementObj& rhs) const
    {
        return stmt->id() < rhs.stmt->id();
    }
};

struct GraphAdjustmentItem {
    GraphAdjustmentItem(ControlFlowGraph* cg): CGraph(cg), needAdjustment(true), in_defs(std::map<ControlFlowGraph*, std::map<SymbolKey, std::map<std::string, SgExpression*>>>()) {}
    ControlFlowGraph* CGraph;
    bool needAdjustment;
    std::map <ControlFlowGraph*, std::map<SymbolKey, std::map<std::string, SgExpression*>>> in_defs;
};

class GraphsKeeper {
private:
    std::vector<GraphAdjustmentItem> graphs;
public:
    GraphsKeeper(): graphs(std::vector<GraphAdjustmentItem>()) {}
    void addGraph(ControlFlowGraph* CGraph) { graphs.push_back(GraphAdjustmentItem(CGraph)); }
    void addInDefs(ControlFlowGraph* targetGraph, ControlFlowGraph* parentGraph, std::map<SymbolKey, std::map<std::string, SgExpression*>>* inDefs);
    void deleteInDefs(ControlFlowGraph* targetGraph, ControlFlowGraph* parentGraph);
    ControlFlowGraph* getGraphForAdjustment();
    std::map <SymbolKey, std::map<std::string, SgExpression*>>* getInDefsFor(ControlFlowGraph* CGraph);
    void deleteGraphs();

};

