#pragma once

#include "dvm.h"
#include "acc_analyzer.h"
#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../Utils/SgUtils.h"
#include "ReadWriteAnalyzer.h"
#include "DvmhRegion.h"

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <utility>
#include <memory>


typedef std::set<DIST::Array* > ArraySet;
struct ReadWrite
{
    ArraySet read;
    ArraySet write;
};
typedef std::map<int, ReadWrite> UsageByLine;
typedef std::map<std::string, UsageByLine> UsageByFile;


class DvmhRegionInserter 
{
    // input data
    SgFile *file;
    const std::vector<LoopGraph*> &loopGraph;
    const std::map<std::string, FuncInfo*>& allFunctions;

    ReadWriteAnalyzer& rw_analyzer;
    std::set<FuncInfo*> parallel_functions;
    std::set<DIST::Array*> writesToArraysInParallelLoop;
    std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls;
    // operating data
    std::vector<DvmhRegion*> regions;

    // region directives
    void findEdgesForRegions(const std::vector<LoopGraph*>&);
    bool hasLimitsToDvmhParallel(const LoopGraph*) const;
    void insertRegionDirectives();

    // actual directives
    ArraySet symbs_to_arrs(std::set<SgSymbol*>) const;
    ArraySet get_used_arrs(SgStatement* st, int usage_type) const;
    ArraySet get_used_arrs_for_block(SgStatement* st, int usage_type) const;
    SgStatement* processSt(SgStatement *st, const std::vector<ParallelRegion*>* regs);
    void insertActualDirectives(const std::vector<ParallelRegion*>* regs);
    void insertActualDirective(SgStatement*, const ArraySet&, int, bool, const std::set<std::string>* = NULL);

    void parFuncsInNode(LoopGraph *loop, bool isParallel);
    bool isLoopParallel(const LoopGraph *loop) const;
    std::vector<SgExpression*> getArrayList(Statement* start, Statement* end, bool left = false) const;
public:
    DvmhRegionInserter(
        SgFile* curFile,
        const std::vector<LoopGraph*>& curLoopGraph,
        ReadWriteAnalyzer& rws,
        std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls,
        const std::map<std::string, FuncInfo*>& allFunctions
    ) : file(curFile), loopGraph(curLoopGraph), rw_analyzer(rws), arrayLinksByFuncCalls(arrayLinksByFuncCalls), allFunctions(allFunctions) { }

    void insertDirectives(const std::vector<ParallelRegion*>* regs = NULL);
    void updateParallelFunctions(const std::map<std::string, std::vector<LoopGraph*>>& loopGraphs);
    void createInterfaceBlock();

    ~DvmhRegionInserter()
    {
        for (auto& reg : regions)
            delete reg;
    }
};
