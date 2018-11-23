//
// Created by baa on 25.12.17.
//

#include "LoopWrapTransform.hpp"
#include "SageTransformUtils.hpp"
#include "SageUtils.hpp"

using namespace SageTransform;

SgForStmt *LoopWrapTransform::wrapWithOneIteration(SgSymbol *symbol, SgStatement *start, SgStatement *end) {
    int distance = SageUtils::lexDist(start, end);
    if (distance != SageUtils::LEX_INFINITY && distance >= 0) {
        //we have to either use different index var,
        // to ensure original var keeps its value after loop
        string iterateVarName = SageTransformUtils::getNewVariableName(symbol->identifier());
        SgSymbol *iterateVar = SageTransformUtils::addScalarVariable(start->getScopeForDeclare(),
                                                           iterateVarName.c_str(),
                                                           symbol->type());
        SgForStmt *oneIterLoop = SageTransformUtils::createOneIterationLoop(iterateVar, symbol);
        start->insertStmtBefore(*oneIterLoop, *(start->controlParent()));
        SageTransformUtils::moveStatements(start, end->lexNext(), oneIterLoop);
        //replace symbol with new var in new loop body
        SageTransformUtils::replaceSymbolInStatements(symbol, iterateVar, start, end);
        return oneIterLoop;
    } else {
        return nullptr;
    }
}

SgForStmt *LoopWrapTransform::wrapWithOneIteration(SgSymbol *symbol, SgForStmt *loop) {
    return this->wrapWithOneIteration(symbol, loop, SageUtils::getLastLoopStatement(loop));
}

