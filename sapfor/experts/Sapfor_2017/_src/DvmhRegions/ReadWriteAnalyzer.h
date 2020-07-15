#pragma once

#include "dvm.h"
#include "../Utils/SgUtils.h"
#include "VarUsages.h"
#include <set>
#include <tuple>
#include <queue>
#include <vector>
#include <exception>
#include <map>


class ReadWriteAnalyzer
{
    std::map<std::string, std::vector<FuncInfo*>> &funcInfo;  // TODO: could be not initilized; should be rebuilt on invalidate()
    std::map<std::string, std::vector<int>> modified_pars;   // func -> used for [in, inout, out] params,
    std::map<SgStatement*, VarUsages> usages_by_statement;    // maps statements to variables used in them

    std::set<std::string> initialized; // files was inited
    void init(SgFile*);

    VarUsages findUsagesInStatement(SgStatement* st) const;
    VarUsages findUsagesInAssignment(SgStatement* st) const;

    const std::set<int> compound_statements = { FOR_NODE, LOOP_NODE, FUNC_HEDR, PROC_HEDR };
    VarUsages gatherUsagesForCompound(SgStatement* st) const;
public:
    explicit ReadWriteAnalyzer(std::map<std::string, std::vector<FuncInfo*>> &funcInfo) : funcInfo(funcInfo) 
    { }

    void invalidate(const std::string& fileName) { initialized.erase(fileName); }

    VarUsages get_usages(SgStatement*);
    VarUsages get_usages(std::vector<SgStatement*>&);

    VarUsages findUsagesInExpr(SgExpression* exp) const;
    VarUsages findUsagesInFuncCall(SgExpression*, const std::string&) const;

    void print() const;

    static std::map<std::string, std::vector<int>> load_modified_pars(const std::map<std::string, std::vector<FuncInfo*>>&);
};
