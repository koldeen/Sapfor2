#pragma once

#include <map>
#include <string>
#include "dvm.h"
#include "../Distribution/Distribution.h"
#include "../GraphLoop/graph_loops.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../GraphCall/graph_calls.h"

struct VariableItem;
class VarsKeeper;
class DataFlowItem;

SgExpression* ReplaceParameter(SgExpression *e);
SgExpression* ReplaceArrayBoundSizes(SgExpression *edim);
SgExpression* ReplaceConstant(SgExpression *e);
void getCoefsOfSubscript(std::pair<int, int> &retCoefs, SgExpression *exp, SgSymbol *doName);
int CalculateInteger(SgExpression *expr, int &result);
void expressionAnalyzer(SgFile *file);
//void expressionAnalyzer(SgStatement *function);
void calculate(SgExpression *&exp);
void replaceConstatRec(SgExpression *&exp);

enum REPLACE_PTR_TYPE { SG_EXPRESSION, SG_STATEMENT };

void revertReplacements(std::string filename);

struct StatementObj {
    SgStatement* stmt;

    StatementObj(SgStatement* st): stmt(st) { }

    inline bool operator<(const StatementObj& rhs) const
    {
        return stmt->id() < rhs.stmt->id();
    }
};
