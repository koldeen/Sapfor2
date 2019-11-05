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
#include <utility>
#include <unordered_set> 
#include <unordered_map>

typedef std::unordered_set<DIST::Array* > ArraySet;  // TODO: добавить урезанную инфу
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

public:
    ArrayUsage(UsageByFile init) : usages_by_file(init) { }; 
    ArraySet get_read_arrs(SgStatement* st);
    ArraySet get_write_arrs(SgStatement* st);
    ArraySet get_read_arrs_for_block(SgStatement* st, bool ignore_regions, bool ignore_dvm);
    ArraySet get_write_arrs_for_block(SgStatement* st, bool ignore_regions, bool ignore_dvm);
};

class ArrayUsageFactory
{
public:
    static std::unique_ptr<ArrayUsage> from_array_access(std::map<DIST::Array*, DIST::ArrayAccessInfo*> arrays_with_access);
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
    std::set<std::string> needActualisation;
    std::set<std::string> needActualisationAfter;

public:
    DvmhRegion() { }
    DvmhRegion(LoopGraph *loopNode, const std::string &fun_name);

    SgStatement* getFirstSt() const;
    SgStatement* getLastSt() const;

    bool addToActualisation(const std::string &s)
    {
        if (needActualisation.find(s) != needActualisation.end())
            return false;
        else
            needActualisation.insert(s);
        return true;
    }

    bool addToActualisationAfter(const std::string &s)
    {
        if (needActualisationAfter.find(s) != needActualisationAfter.end())
            return false;
        else
            needActualisationAfter.insert(s);
        return true;
    }

    void addLoop(LoopGraph* newLoop) { loops.push_back(newLoop); }
    const std::string& getFunName() const { return fun_name; }
    void setFunName(const std::string& newName) { fun_name = newName; }
    const std::vector<LoopGraph*>& getLoops() const { return loops; }
    const std::set<std::string>& getActualisation() const {return needActualisation; }
    const std::set<std::string>& getActualisationAfter() const { return needActualisationAfter; }

};

class DvmhRegionInsertor 
{
    SgFile *file;
    const std::vector<LoopGraph*> &loopGraph;
    std::vector<DvmhRegion*> regions;
    std::unique_ptr<ArrayUsage> array_usage;

    DvmhRegion* getRegionByStart(SgStatement *) const;
    void printFuncName(SgStatement *);
    void findEdgesForRegions(const std::vector<LoopGraph*>&);
    bool hasLimitsToDvmhParallel(const LoopGraph*) const;
    SgStatement* processSt(SgStatement *st);
    void insertActualDirectives();
    void insertRegionDirectives();
    void insertActualDirective(SgStatement*, const ArraySet&, int, bool, bool empty = false);
    void mergeRegions();
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
