//
// Created by Vladislav Volodkin on 12/17/19.
//

#ifndef SAPFOR_READWRITEANALYZER_H
#define SAPFOR_READWRITEANALYZER_H
#include "dvm.h"
#include "../Utils/SgUtils.h"
#include "DvmhRegions/Exceptions.h"
#include "VarUsages.h"
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <queue>
#include <vector>


enum VAR_TYPE { VAR_ARR, VAR_DISTR_ARR, VAR_SCALAR, VAR_ALL };
enum USAGE_TYPE { USAGE_READ, USAGE_WRITE, USAGE_ALL };

typedef std::tuple<std::unordered_set<SgSymbol*>, std::unordered_set<SgSymbol*>> rw_tuple; // (reads, writes)


class ReadWriteAnalyzer
{
    SgProject &project;

    std::unordered_map<SgStatement*, std::vector<bool>> modified_pars;  // func -> params
    std::unordered_map<SgStatement*, VarUsages> data;  // Maps statements to variables used in them.
                                                       // Parent statements, like functions, loops, if-else, etc..
                                                       // contain usage data for all variables from their body

    bool initialized;
    void init();

    rw_tuple processAssignment(SgStatement* st);
    rw_tuple processLoop(SgStatement* st);
    rw_tuple processBlock(SgStatement* start, SgStatement *end);

    rw_tuple processStatement(SgStatement* st);

    std::unordered_set<SgSymbol*> filter(std::unordered_set<SgSymbol*>, VAR_TYPE);
public:
    explicit ReadWriteAnalyzer(SgProject &prjct, std::unordered_map<SgStatement*, std::vector<bool>> &modified_pars) :
    project(prjct), initialized(false), modified_pars(modified_pars)
    { };

    void invalidate() { initialized = false; } ;

    std::unordered_set<SgSymbol*> get_usages(SgStatement*, VAR_TYPE, USAGE_TYPE);  // may raise NotImplemented, out_of_range
    std::unordered_set<SgSymbol*> get_usages(std::vector<SgStatement*>&, VAR_TYPE, USAGE_TYPE);  // may raise NotImplemented, out_of_range

    rw_tuple findUsagesInExpr(SgExpression* exp);
    rw_tuple findUsagesInFuncCall(SgExpression* exp);

    void print();
    void printOne(SgStatement*);

    static std::unordered_map<SgStatement*, std::vector<bool>> load_modified_pars(std::map<std::string, std::vector<FuncInfo*>>);
};


#endif //SAPFOR_READWRITEANALYZER_H
