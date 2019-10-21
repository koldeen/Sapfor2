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

using namespace std;

typedef unordered_set<DIST::Array* > ArraySet;
struct ReadWrite
{
    ArraySet read;
    ArraySet write;
};
typedef unordered_map<int, ReadWrite> UsageByLine;
typedef unordered_map<string, UsageByLine> UsageByFile;

class ArrayUsage
{
    UsageByFile usages_by_file; // [file, [line, (read, write)]]

public:
    ArrayUsage(UsageByFile init) : usages_by_file(init) { }; 
    ArraySet get_read_arrs(SgStatement* st);
    ArraySet get_write_arrs(SgStatement* st);
};

class ArrayUsageFactory
{
public:
    static unique_ptr<ArrayUsage> from_array_access(map<DIST::Array*, DIST::ArrayAccessInfo*> arrays_with_access);
};

struct LoopCheckResults 
{
    bool usesIO;
    bool hasImpureCalls;

    vector<int> linesOfIO;

    LoopCheckResults() : usesIO(false), hasImpureCalls(false) { }
    LoopCheckResults(bool io, bool calls) : usesIO(io), hasImpureCalls(calls) { }
};

class DvmhRegion 
{
private:
    vector<LoopGraph*> loops;

    string fun_name;
    set<string> needActualisation;
    set<string> needActualisationAfter;

public:
    DvmhRegion() { }
    DvmhRegion(LoopGraph *loopNode, const string &fun_name);

    SgStatement* getFirstSt() const;
    SgStatement* getLastSt() const;

    bool addToActualisation(const string &s) 
    {
        if (needActualisation.find(s) != needActualisation.end())
            return false;
        else
            needActualisation.insert(s);
        return true;
    }

    bool addToActualisationAfter(const string &s)
    {
        if (needActualisationAfter.find(s) != needActualisationAfter.end())
            return false;
        else
            needActualisationAfter.insert(s);
        return true;
    }

    void addLoop(LoopGraph* newLoop) { loops.push_back(newLoop); }
    const string& getFunName() const { return fun_name; }
    void setFunName(const string& newName) { fun_name = newName; }
    const vector<LoopGraph*>& getLoops() const { return loops; }
    const set<string>& getActualisation() const {return needActualisation; }
    const set<string>& getActualisationAfter() const { return needActualisationAfter; }
};

class DvmhRegionInsertor 
{
    SgFile *file;
    const vector<LoopGraph*> &loopGraph;
    vector<DvmhRegion*> regions;
    unique_ptr<ArrayUsage> array_usage;

    DvmhRegion* getRegionByStart(SgStatement *) const;
    void printFuncName(SgStatement *);
    void findEdgesForRegions(const vector<LoopGraph*>&);
    bool hasLimitsToDvmhParallel(const LoopGraph*) const;
    void insertActualDirectives();
    void insertRegionDirectives();
    void insertActualDirective(SgStatement*, const ArraySet&, int, bool, bool empty = false);
    void mergeRegions();
    LoopCheckResults checkLoopForPurenessAndIO(LoopGraph*, const map<string, FuncInfo*> &allFuncs);
    LoopCheckResults updateLoopNode(LoopGraph*, const map<string, FuncInfo*> &allFuncs);

public:

    DvmhRegionInsertor(SgFile*, const vector<LoopGraph*>&);
    DvmhRegionInsertor(
        SgFile*, 
        const vector<LoopGraph*>&, 
        const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>>&
    );
    void updateLoopGraph(const map<string, FuncInfo*> &allFuncs);
    void insertDirectives();
    ~DvmhRegionInsertor()
    {
        for (auto& reg : regions)
            delete reg;
    }
};

static tuple<set<SgSymbol *>, set<SgSymbol *>> getUsedDistributedArrays(SgStatement* st);
