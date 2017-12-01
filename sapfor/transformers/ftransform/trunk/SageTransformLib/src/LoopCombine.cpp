//
// Created by Bulanov on 11.08.17.
//

#include <SageTransformException.hpp>
#include <Log.hpp>
#include "LoopCombine.h"
#include "SageTransformUtils.hpp"
#include "StringUtils.hpp"
#include "SageUtils.hpp"

using namespace SageTransform;
using SageUtils::getLineNumber;

string LoopCombine::COMBINE_PREFIX("!PRG combine");

bool LoopCombine::hasComment(SgStatement *sgStatement) {
    char *pCharComments = sgStatement->comments();
    if (pCharComments) {
        vector<string> comments = StringUtils::split(pCharComments, '\n');
        for (vector<string>::iterator pComment = comments.begin(); pComment != comments.end(); ++pComment) {
            if (StringUtils::startsWith(*pComment, COMBINE_PREFIX)) {
                return true;
            }
        }
    }
    return false;
}

void LoopCombine::removeComment(SgStatement *sgStatement) {
    char *pCharComments = sgStatement->comments();
    if (pCharComments) {
        StringUtils::removeLineStartingWith(pCharComments, COMBINE_PREFIX);
    } else {
        Log::warn("Try to remove comments from " + getLineNumber(sgStatement) +
                                     " but it has no comments");
    }
}

SgStatement *LoopCombine::apply(SgForStmt *sgForStmt) {
    vector<SgForStmt *> combined = getCombinedLoops(sgForStmt, getCombineCount(sgForStmt));
    if (combined.empty()) {
        Log::warn("Nothing to combine for " + getLineNumber(sgForStmt));
        return nullptr;
    } if (isSameHeadersCombination(combined)) {
        return applySameHeaders(combined);
    } else if (isContinuousHeadersCombination(combined)) {
        return applyContinuousHeaders(combined);
    } else {
        string msg = "Loop Combine unapplicable to given loop sequence at" + getLineNumber(sgForStmt);
        Log::error(msg);
        if (suppressThrows) return nullptr;
        throw SageTransformException(msg);
    }
}

bool LoopCombine::isSameHeadersCombination(vector<SgForStmt *> &combined) const {
    return SageTransformUtils::isLoopsHaveSameHeader(combined);
}

SgStatement *LoopCombine::applySameHeaders(vector<SgForStmt *> &combined) {
    SgForStmt *host = combined[0];
    SgStatement *next = SageUtils::getLastLoopStatement(combined.back())->lexNext();
    for (int i = 1; i < combined.size(); ++i) {
        SageTransformUtils::moveLoopBody(host, combined[i]);
        SageTransformUtils::removeLoop(combined[i]);
    }
    return next;
}

bool LoopCombine::isContinuousHeadersCombination(vector<SgForStmt *> &combined) const {
    return SageTransformUtils::isLoopsHaveContinuousHeaders(combined);
}

SgStatement *LoopCombine::applyContinuousHeaders(vector<SgForStmt *> &combined) {
    //create big loop
    //create ifs in new big loop
    //remove old partial loops
    SgForStmt *first = combined.front();
    SgForStmt *last = combined.back();
    SgSymbol *iterateVar = first->symbol();
    for (int i = 1; i < combined.size(); ++i) {
        if (iterateVar != combined[i]->symbol()) {
            iterateVar = NULL;
            break;
        }
    }
    if (iterateVar == NULL) {
        iterateVar = SageTransformUtils::addScalarVariable(combined.front()->getScopeForDeclare(),
                                                           SageTransformUtils::getNewVariableName(),
                                                           SgTypeInt());
    }
    //create ifs in new big loop
    vector<SgStatement *> ifs;
    for (int i = 0; i < combined.size(); ++i) {
        SgForStmt *forStmt = combined[i];
        vector<SgStatement *> body = SageTransformUtils::copyStatements(SageUtils::body(forStmt));
        SgSymbol *iteratingSymb = forStmt->symbol();
        for (int j = 0; j < body.size(); ++j) {
            body[j]->replaceSymbBySymb(*iteratingSymb, *iterateVar);
        }
        SgExpression *iterInRangeExpr = SageTransformUtils::variableInBetween(forStmt->start()->copyPtr(),
                                                                              forStmt->end()->copyPtr(), iterateVar);
        SgStatement *ifStmt = SageTransformUtils::createIfStmt(NULL, iterInRangeExpr, body);
        ifs.push_back(ifStmt);
    }
    //create big loop - here
    SgForStmt *singleLoop = SageTransformUtils::createForStmt(first->lexPrev(), iterateVar, first->start()->copyPtr(),
                                                              last->end()->copyPtr(),
                                                              nullptr, ifs);
    //remove old partial loops
    for (int i = 0; i < combined.size(); ++i) {
        combined[i]->deleteStmt();
    }
    return SageUtils::getLastLoopStatement(singleLoop)->lexNext();
}

int LoopCombine::getCombineCount(SgStatement *sgStatementWithComment) const {
    char *pCharComments = sgStatementWithComment->comments();
    if (pCharComments) {
        vector<string> comments = StringUtils::split(pCharComments, '\n');
        for (vector<string>::iterator pComment = comments.begin(); pComment != comments.end(); ++pComment) {
            if (StringUtils::startsWith(*pComment, COMBINE_PREFIX)) {
                vector<string> tokens = StringUtils::tokenize(*pComment, ' ');
                return atoi(tokens.at(2).c_str());
            }
        }
    }
    string msg = "Missing combine loop count for " + getLineNumber(sgStatementWithComment) + ". Syntax: !PRG combine ###";
    Log::error(msg);
    if (suppressThrows) return -1;
    throw SageTransformException(msg);
}

vector<SgForStmt *> LoopCombine::getCombinedLoops(SgForStmt *startingForStmt, int count) const {
    vector<SgForStmt *> result;
    result.push_back(startingForStmt);
    SgForStmt *next = startingForStmt;
    SgStatement *tmp;
    for (int i = 1; i < count; ++i) {
        tmp = SageUtils::getLastLoopStatement(next);
        tmp = tmp->lexNext();
        next = isSgForStmt(tmp);
        if (!next) {
            if (suppressThrows) return vector<SgForStmt *>(); //empty vector
            throw SageTransformException(
                    string("Combine supports only 'for' loops. Found ") + SageUtils::decodeStmtVariant(tmp->variant()));
        } else {
            result.push_back(next);
        }
    }
    return result;
}
