#pragma once

#include <map>
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

void deleteGraphKeeper();
SgExpression* ReplaceParameter(SgExpression *e);
SgExpression* ReplaceArrayBoundSizes(SgExpression *edim);
SgExpression* ReplaceConstant(SgExpression *e);
void getCoefsOfSubscript(std::pair<int, int> &retCoefs, SgExpression *exp, SgSymbol *doName);
int CalculateInteger(SgExpression *expr, int &result);
SgExpression* CalculateInteger(SgExpression *expr);
void expressionAnalyzer(SgFile *file,
        std::map<std::string, std::vector<DefUseList>> &defUseByFunctions,
        std::map<std::string, CommonBlock> &commonBlocks,
        std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo);

void calculate(SgExpression *&exp);
void replaceConstatRec(SgExpression *&exp);

enum REPLACE_PTR_TYPE { SG_EXPRESSION, SG_STATEMENT };

void revertReplacements(const std::string &filename, bool back = false);

struct GraphItem {
    GraphItem(): CGraph(NULL), file_id(-1), calls(CallData()), commons(CommonData()), dldl(DoLoopDataList()) {}
    int file_id;
    ControlFlowGraph* CGraph;
    CallData calls;
    CommonData commons;
    DoLoopDataList dldl;
};

class GraphsKeeper {
private:
    std::map<std::string, GraphItem*> graphs;
public:
    GraphsKeeper(): graphs(std::map<std::string, GraphItem*>()) {}
    ~GraphsKeeper()
    {
        for (auto &it : graphs)
        {
            if (it.second)
            {
                if (it.second->CGraph)
                {
                    delete it.second->CGraph;
                    it.second->CGraph = NULL;
                }
                delete it.second;
                it.second = NULL;
            }
        }
        graphs.clear();
    }

    GraphItem* buildGraph(SgStatement* st);
    GraphItem* getGraph(const std::string &funcName);
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

void FillCFGInsAndOutsDefs(ControlFlowGraph*, std::map<SymbolKey, std::map<std::string, SgExpression*>> *inDefs, CommonVarsOverseer *overseer_Ptr);
void CorrectInDefs(ControlFlowGraph*);
void ClearCFGInsAndOutsDefs(ControlFlowGraph*);
bool valueWithRecursion(const SymbolKey&, SgExpression*);
bool valueWithFunctionCall(SgExpression*);
bool argIsReplaceable(int i, AnalysedCallsList* callData);
bool symbolInExpression(const SymbolKey &symbol, SgExpression *exp);
