#pragma once

#include <map>
#include <set>
#include <string>
#include "dvm.h"
#include "../Distribution/Distribution.h"
#include "../GraphLoop/graph_loops.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../GraphCall/graph_calls.h"
#include "../Utils/SgUtils.h"

#include "acc_analyzer.h"


struct VariableItem;
class VarsKeeper;
class DataFlowItem;

void deleteGraphsKeeper();
SgExpression* ReplaceParameter(SgExpression *e);
SgExpression* ReplaceArrayBoundSizes(SgExpression *edim);
SgExpression* ReplaceConstant(SgExpression *e);
void getCoefsOfSubscript(std::pair<int, int> &retCoefs, SgExpression *exp, SgSymbol *doName);
int CalculateInteger(SgExpression *expr, int &result);
SgExpression* CalculateInteger(SgExpression *expr);
void expressionAnalyzer(SgFile *file,
        const std::map<std::string, std::vector<DefUseList>> &defUseByFunctions,
        const std::map<std::string, CommonBlock> &commonBlocks,
        const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo,
        const std::vector<ParallelRegion*> &regions);

void calculate(SgExpression *&exp);
void replaceConstatRec(SgExpression *&exp);

enum REPLACE_PTR_TYPE { SG_EXPRESSION, SG_STATEMENT };

void revertReplacements(const std::string &filename, bool back = false);

struct GraphItem {
    GraphItem(): CGraph(NULL), file_id(-1), calls(CallData()), commons(CommonData()), dldl(DoLoopDataList()), privateDone(false) {}
    int file_id;
    ControlFlowGraph* CGraph;
    CallData calls;
    CommonData commons;
    DoLoopDataList dldl;
    bool privateDone;
    ~GraphItem() { if(CGraph) delete CGraph; }
};

class GraphsKeeper {
private:
    std::map<SgStatement*, GraphItem*> graphs;
    GraphsKeeper(): graphs(std::map<SgStatement*, GraphItem*>()) {}
public:
    static GraphsKeeper* getGraphsKeeper();
    static void deleteGraphsKeeper();
    ~GraphsKeeper()
    {
        for (auto &it : graphs)
            if (it.second)
            {
                delete it.second;
                it.second = NULL;
            }
        graphs.clear();
    }

    GraphItem* buildGraph(SgStatement* st);
    GraphItem* getGraph(SgStatement *header);
    CBasicBlock* findBlock(SgStatement* stmt);
};

struct FuncCallSE
{
    std::string funcName;
    std::set<std::string> calls;
    FuncCallSE(std::string &n, std::set<std::string>& v) : funcName(n), calls(v) {}
};

class CommonVarsOverseer
{
private:
    bool inited;

public:
    std::map<std::string, std::set<SgSymbol*>> funcKillsVars;
    CommonVarsOverseer() : inited(false), funcKillsVars(std::map<std::string, std::set<SgSymbol*>>()) {}
    bool isInited() { return inited; }
    void riseInited() { inited = true; }
    void addKilledVar(SgSymbol* symbol, const std::string &funcName)
    {
        auto founded = funcKillsVars.find(funcName);
        if (founded == funcKillsVars.end())
            funcKillsVars.insert(founded, std::make_pair(funcName, std::set<SgSymbol*>()))->second.insert(symbol);
        else
            founded->second.insert(symbol);
    }

    std::set<SgSymbol*>* killedVars(const std::string &funcName)
    {
        auto founded = funcKillsVars.find(funcName);
        if (founded == funcKillsVars.end())
            return NULL;
        return &(founded->second);
    }
};

std::map<SgStatement*, std::pair<std::set<SgStatement*>, std::set<SgStatement*>>> buildRequireReachMapForLoop(SgStatement *since, SgStatement *till, std::set<std::string> &privates);
const std::map<SymbolKey, std::set<ExpressionValue*>> getReachingDefinitionsExt(SgStatement* stmt);
void FillCFGInsAndOutsDefs(ControlFlowGraph*, std::map<SymbolKey, std::set<ExpressionValue*>> *inDefs, CommonVarsOverseer *overseer_Ptr);
void CorrectInDefs(ControlFlowGraph*);
void ClearCFGInsAndOutsDefs(ControlFlowGraph*);
bool valueWithRecursion(const SymbolKey&, SgExpression*);
bool valueWithFunctionCall(SgExpression*);
bool valueWithArrayReference(SgExpression *exp);
bool argIsReplaceable(int i, AnalysedCallsList* callData);
bool argIsUsed(int i, AnalysedCallsList* callData);
bool symbolInExpression(const SymbolKey &symbol, SgExpression *exp);
void showDefs(std::map<SymbolKey, std::set<ExpressionValue>> *defs);
void showDefs(std::map<SymbolKey, SgExpression*> *defs);
void showDefsOfGraph(ControlFlowGraph *CGraph);
void debugStructure(ControlFlowGraph *CGraph, const std::string &filename);
bool findCFIsForStmt(SgStatement *st, std::vector <ControlFlowItem*> &cfis);
std::map<SymbolKey, std::set<ExpressionValue*>> createHeaderInDefs(SgStatement *header);
ControlFlowGraph* BuildUnfilteredReachingDefinitionsFor(SgStatement *header);
void runPrivateAnalysis(SgStatement *main);
SgStatement* findReplacedExpression(SgExpression* ex);