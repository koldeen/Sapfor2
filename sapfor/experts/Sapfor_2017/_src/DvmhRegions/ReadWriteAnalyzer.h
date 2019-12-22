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
#include <exception>


class ReadWriteAnalyzer
{
    SgProject &project;

    std::unordered_map<SgStatement*, std::vector<bool>> modified_pars;  // func -> params, TODO: not inited
    std::unordered_map<SgStatement*, VarUsages> usages_by_statement;    // maps statements to variables used in them

    bool initialized = false;
    void init();

    VarUsages findUsagesInStatement(SgStatement* st);
    VarUsages findUsagesInAssignment(SgStatement* st);

    const std::unordered_set<int> compound_statements = {FOR_NODE, LOOP_NODE, FUNC_HEDR, PROC_HEDR};
    VarUsages gatherUsagesForCompound(SgStatement* st);
public:
    explicit ReadWriteAnalyzer(SgProject &prjct, std::unordered_map<SgStatement*, std::vector<bool>> &modified_pars) :
    project(prjct), modified_pars(modified_pars)
    { };

    void invalidate() { initialized = false; } ;

    VarUsages get_usages(SgStatement*);  // may raise out_of_range
    VarUsages get_usages(std::vector<SgStatement*>&);  // may raise out_of_range

    VarUsages findUsagesInExpr(SgExpression* exp);
    VarUsages findUsagesInFuncCall(SgExpression* exp);

    void print();

    static std::unordered_map<SgStatement*, std::vector<bool>> load_modified_pars(std::map<std::string, std::vector<FuncInfo*>>);
};


#endif //SAPFOR_READWRITEANALYZER_H
