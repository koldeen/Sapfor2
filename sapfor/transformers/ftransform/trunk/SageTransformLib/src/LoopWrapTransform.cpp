//
// Created by baa on 25.12.17.
//

#include "LoopWrapTransform.hpp"
#include "SageTransformUtils.hpp"
#include "SageUtils.hpp"

using namespace SageTransform;

SgForStmt *LoopWrapTransform::wrapWithOneIteration(SgSymbol *symbol, SgStatement *start, SgStatement *end) {
    int distance = SageUtils::lexDist(start, end);
    if (distance != SageUtils::LEX_INFINITY && distance > 0) {
        SgForStmt *oneIterLoop = SageTransformUtils::createOneIterationLoop(symbol);
        start->insertStmtBefore(*oneIterLoop, *(start->controlParent()));
        SageTransformUtils::moveStatements(start, end->lexNext(), oneIterLoop);
        return oneIterLoop;
    } else {
        return nullptr;
    }
}

SgForStmt *LoopWrapTransform::wrapWithOneIteration(SgSymbol *symbol, SgForStmt *loop) {
    return this->wrapWithOneIteration(symbol, loop, SageUtils::getLastLoopStatement(loop));
}

