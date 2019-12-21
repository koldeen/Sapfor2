#pragma once

#include "dvm.h"
#include "acc_analyzer.h"
#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../Utils/SgUtils.h"
#include "DvmhRegions/Exceptions.h"
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
#include <unordered_set> 
#include <unordered_map>
#include <memory>


typedef std::unordered_set<DIST::Array* > ArraySet;
struct ReadWrite
{
    ArraySet read;
    ArraySet write;
};
typedef std::unordered_map<int, ReadWrite> UsageByLine;
typedef std::unordered_map<std::string, UsageByLine> UsageByFile;


class DvmhRegionInsertor 
{
    // input data
    SgFile *file;
    const std::vector<LoopGraph*> &loopGraph;
    ReadWriteAnalyzer rw_analyzer;

    // operating data
    std::vector<DvmhRegion*> regions;

    // region directives
    void findEdgesForRegions(const std::vector<LoopGraph*>&);
    bool hasLimitsToDvmhParallel(const LoopGraph*) const;
    void insertRegionDirectives();

    // actual directives
    ArraySet symbs_to_arrs(std::unordered_set<SgSymbol*>);
    ArraySet get_used_arrs(SgStatement* st, USAGE_TYPE usage_type);
    ArraySet get_used_arrs_for_block(SgStatement* st, USAGE_TYPE usage_type);
    SgStatement* processSt(SgStatement *st);
    void insertActualDirectives();
    void insertActualDirective(SgStatement*, const ArraySet&, int, bool);
public:
    DvmhRegionInsertor(
        SgFile* curFile,
        const std::vector<LoopGraph*>& curLoopGraph,
        ReadWriteAnalyzer &rws
    ) : file(curFile), loopGraph(curLoopGraph), rw_analyzer(rws) { };

    void insertDirectives();

    ~DvmhRegionInsertor()
    {
        for (auto& reg : regions)
            delete reg;
    }
};

static std::tuple<std::set<SgSymbol *>, std::set<SgSymbol *>> getUsedDistributedArrays(SgStatement* st);
