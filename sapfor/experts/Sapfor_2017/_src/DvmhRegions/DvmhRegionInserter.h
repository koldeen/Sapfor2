#pragma once

#include "dvm.h"
#include "acc_analyzer.h"
#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../Utils/SgUtils.h"
#include "DvmhRegions/Exceptions.h"
#include "ReadWriteAnylyser.h"

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

class ArrayUsage
{
    UsageByFile usages_by_file; // [file, [line, (read, write)]]
    // TODO: добавить урезанную инфу [file, [line, Usage(arr, underFunctionPar, funName)]]
public:
    ArrayUsage(UsageByFile init) : usages_by_file(init) { };

    ArraySet get_op_arrs(SgStatement* st, int type); // 0 -read, 1 - write
    ArraySet get_op_arrs_for_block(SgStatement* st, bool ignore_regions, bool ignore_dvm, int type);// 0 -read, 1 - write
};

class ArrayUsageFactory
{
public:
    static std::unique_ptr<ArrayUsage> from_array_access(std::map<DIST::Array*, DIST::ArrayAccessInfo*> arrays_with_access, bool dist_only);
};

struct LoopCheckResults 
{
    bool usesIO;
    bool hasImpureCalls;

    std::vector<int> linesOfIO;

    LoopCheckResults() : usesIO(false), hasImpureCalls(false) { }
    LoopCheckResults(bool io, bool calls) : usesIO(io), hasImpureCalls(calls) { }
};

class DvmhRegion 
{
private:
    std::vector<LoopGraph*> loops;
    std::string fun_name;

public:
    ReadWriteAnylyser rw_info; // info about vars, read and modified

    DvmhRegion() { }
    DvmhRegion(LoopGraph *loopNode, const std::string &fun_name);

    SgStatement* getFirstSt() const;
    SgStatement* getLastSt() const;

    void addLoop(LoopGraph* newLoop) { loops.push_back(newLoop); }
    const std::string& getFunName() const { return fun_name; }
    void setFunName(const std::string& newName) { fun_name = newName; }
    const std::vector<LoopGraph*>& getLoops() const { return loops; }
    std::string getFileName() const { return this->getFirstSt()->fileName(); }
    std::unordered_set<SgSymbol*> get_modified();  // may raise NotImplemented
    std::unordered_set<SgSymbol*> get_read();  // may raise NotImplemented
    void append(DvmhRegion& region);
};

class DvmhRegionInsertor 
{
    SgFile *file;
    const std::vector<LoopGraph*> &loopGraph;
    std::vector<DvmhRegion*> regions;
    std::unique_ptr<ArrayUsage> array_usage;

    void printFuncName(SgStatement *);
    void findEdgesForRegions(const std::vector<LoopGraph*>&);
    bool hasLimitsToDvmhParallel(const LoopGraph*) const;
    SgStatement* processSt(SgStatement *st);
    void insertActualDirectives();
    void insertRegionDirectives();
    void insertActualDirective(SgStatement*, const ArraySet&, int, bool);

    LoopCheckResults checkLoopForPurenessAndIO(LoopGraph*, const std::map<std::string, FuncInfo*> &allFuncs);
    LoopCheckResults updateLoopNode(LoopGraph*, const std::map<std::string, FuncInfo*> &allFuncs);
public:

    DvmhRegionInsertor(SgFile*, const std::vector<LoopGraph*>&);
    DvmhRegionInsertor(
        SgFile*, 
        const std::vector<LoopGraph*>&,
        const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>>&
    );
    void updateLoopGraph(const std::map<std::string, FuncInfo*> &allFuncs);
    void insertDirectives();
    ~DvmhRegionInsertor()
    {
        for (auto& reg : regions)
            delete reg;
    }
};

static std::tuple<std::set<SgSymbol *>, std::set<SgSymbol *>> getUsedDistributedArrays(SgStatement* st);
