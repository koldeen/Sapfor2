#include "../include/SageTransformUtils.hpp"

#include <iostream>
#include <SageUtils.hpp>
#include <StringUtils.hpp>

using std::cerr;
using std::endl;
using std::string;
using std::to_string;
using namespace SageTransform;

SgForStmt *
SageTransformUtils::createForStmt(SgStatement *createAfter,
                                  SgSymbol *tmpVar, SgExpression *start,
                                  SgExpression *end, SgExpression *step, vector<SgStatement *> body) {
    SgStatement *body0 = body[0];
    SgForStmt *result = new SgForStmt(tmpVar, start, end, step, body0);
    for (int i = 1; i < body.size(); ++i) {
        result->lastExecutable()->insertStmtAfter(*body[i], *result);
    }

//    vector<SgStatement *> toMove;
//    SgStatement *stmt = createAfter->lexNext();
//    while (stmt != controlEndBeforeThis) {
//        if (stmt->controlParent() == controlParent) {
//            toMove.push_back(stmt);
//        }
//        stmt = stmt->lexNext();
//    }
//    vector<SgStatement *>::reverse_iterator rit;
//    for (rit = toMove.rbegin(); rit != toMove.rend(); ++rit) {
//        std::cout << "Adding from line " << (*rit)->lineNumber() << std::endl;
//        SgStatement *copy = (*rit)->copyPtr();
//        (*rit)->deleteStmt();
//        result->insertStmtAfter(*copy, *result);
//    }
    if (createAfter != NULL) {
        SgStatement *controlParent = sameLevelControlParent(createAfter);
        createAfter->insertStmtAfter(*result, *controlParent);
        result = isSgForStmt(createAfter->lexNext());
    }
    return result;
}

SgIfStmt *
SageTransformUtils::createIfStmt(SgStatement *createAfter, SgExpression *condition, vector<SgStatement *> trueBody) {
    SgStatement *trueBody0 = trueBody[0];
    SgIfStmt *result = new SgIfStmt(*condition, *trueBody0);
    for (int i = 1; i < trueBody.size(); ++i) {
        result->lastExecutable()->insertStmtAfter(*trueBody[i], *result);
    }
    if (createAfter != NULL) {
        SgStatement *controlParent = sameLevelControlParent(createAfter);
        createAfter->insertStmtAfter(*result, *controlParent);
        result = isSgIfStmt(createAfter->lexNext());
    }
    return result;
}

SgExpression *SageTransformUtils::variableInBetween(SgExpression *low, SgExpression *high, SgSymbol *variable) {
    SgVarRefExp *varRefExp1 = new SgVarRefExp(variable);
    SgExpression *lowLeVar = new SgExpression(LTEQL_OP, low, varRefExp1, NULL, NULL);
    SgVarRefExp *varRefExp2 = new SgVarRefExp(variable);
    SgExpression *varleHigh = new SgExpression(LTEQL_OP, varRefExp2, high, NULL, NULL);
    SgExpression *andE = new SgExpression(AND_OP, lowLeVar, varleHigh, NULL, NULL);
    return andE;
}

vector<SgStatement *> SageTransformUtils::copyStatements(const vector<SgStatement *> &originals) {
    vector<SgStatement *> result;
    for (int i = 0; i < originals.size(); ++i) {
        result.push_back(originals[i]->copyPtr());
    }
    return result;
}

vector<SgStatement *> SageTransformUtils::copyStatements(const vector<SgForStmt *> &originals) {
    vector<SgStatement *> result;
    for (int i = 0; i < originals.size(); ++i) {
        result.push_back(originals[i]->copyPtr());
    }
    return result;
}

SgStatement* SageTransformUtils::swapWithLexPrev(SgStatement *pStmt) {
    SgStatement *previous = pStmt->lexPrev();
    SgStatement *newControlParent = nullptr;
    if (pStmt->controlParent() == previous->controlParent()) {
        newControlParent = previous->controlParent();
    } else if (pStmt->controlParent() == previous){
        newControlParent = previous->controlParent();
    } else {
        //todo case when enddo is moved up can appear
        newControlParent = previous->controlParent();
    }
    SgStatement *extracted = pStmt->extractStmt();
    previous->insertStmtBefore(*extracted, *newControlParent);
    return previous->lexPrev();
}

void SageTransformUtils::swapLexStmt(SgStatement *pStmtA, SgStatement *pStmtB) {
    SgStatement *pStmtAPre, *pStmtAPost, *pStmtBPre, *pStmtBPost;
    pStmtAPre = pStmtA->lexPrev();
    pStmtAPost = pStmtA->lexNext();
    pStmtBPre = pStmtB->lexPrev();
    pStmtBPost = pStmtB->lexNext();
    pStmtA->replaceWithStmt(*pStmtB);
    pStmtB->replaceWithStmt(*pStmtA);
    //not tested
}

void SageTransformUtils::swapScopeStmt(SgStatement *pStmtA, SgStatement *pStmtB) {
    cerr << "Not implemented: void SageTransform::swapScopeStmt(SgStatement *pStmtA, SgStatement *pStmtB)" << endl;
    exit(1);
}

void
SageTransformUtils::moveStatements(SgStatement *beginInclusive, SgStatement *endExclusive, SgStatement *moveAfterThis) {
    vector<SgStatement *> moves;
    SgStatement *insertAfter = moveAfterThis;
    //no checks for validity of begin, end pointers
    for (SgStatement *pStmt = beginInclusive; pStmt != endExclusive; pStmt = pStmt->lexNext()) {
        moves.push_back(pStmt);
    }
    for (unsigned int i = 0; i < moves.size(); ++i) {
        SgStatement *pStmt = moves.at(i);
        pStmt = pStmt->extractStmt();
        insertAfter->insertStmtAfter(*pStmt);
        insertAfter = insertAfter->lexNext();
    }
}

//TODO: test
void SageTransformUtils::moveLoopBody(SgForStmt *recipientLoop, SgForStmt *sourceLoop) {
    bool sameHeader = isLoopsHaveSameHeader(recipientLoop, sourceLoop);
    if (!sameHeader) {
        //todo validations should be done outside
        throw "Illegal loop body move from " + to_string(sourceLoop->lineNumber())
              + " to " + to_string(recipientLoop->lineNumber()) + ": reason headers are not equal";
    }
    SgStatement *recipientLoopEnd = SageUtils::getLastLoopStatement(recipientLoop)->lexPrev();
    SgStatement *sourceLoopStart = sourceLoop->lexNext();
    SgStatement *sourceLoopEnd = SageUtils::getLastLoopStatement(sourceLoop);
    moveStatements(sourceLoopStart, sourceLoopEnd, recipientLoopEnd);
}

void SageTransformUtils::removeLoop(SgForStmt *removeLoop) {
    removeLoop->deleteStmt();
}

bool SageTransformUtils::isLoopsHaveSameHeader(SgForStmt *loop1const, SgForStmt *loop2const) {
    //const hack, Sage lib does not use consts, but we will
    SgForStmt *loop1 = (SgForStmt *) (void *) loop1const;
    SgForStmt *loop2 = (SgForStmt *) (void *) loop2const;
    std::cout << "Comparing loop headers at " << loop1->lineNumber() << " and " << loop2->lineNumber() << std::endl;
    bool stepsEqual;
    if (loop1->step() == nullptr && loop2->step() == nullptr) {
        stepsEqual = true;
    } else {
        stepsEqual = SageUtils::equalExpressions(loop1->step(), loop2->step());
    }
    bool startsEqual = SageUtils::equalExpressions(loop1->start(), loop2->start());
    bool endsEqual = SageUtils::equalExpressions(loop1->end(), loop2->end());
    return startsEqual && endsEqual && stepsEqual;
}

bool SageTransformUtils::isLoopsHaveSameHeader(vector<SgForStmt *> &loops) {
    bool result = true;
    if (loops.size() >= 2) {
        //const hack, Sage lib does not use consts, but we will
        SgForStmt *first = (SgForStmt *) (void *) loops.front();
        auto iterator = loops.begin();
        auto end = loops.end();
        iterator++;
        while (result && iterator != end) {
            result = result && isLoopsHaveSameHeader(first, *iterator);
            iterator++;
        }
    }
    return result;
}

bool SageTransformUtils::isLoopsHaveContinuousHeaders(SgForStmt *loop1, SgForStmt *loop2) {
    string one = string("1");
    bool stepsEqual = (loop1->step() == nullptr || SageUtils::compareExpression(loop1->step(), one))
                      && (loop2->step() == nullptr || SageUtils::compareExpression(loop2->step(), one));
    if (!stepsEqual) {
        return false;
    }
    bool continuous = false;
    string loop1End = loop1->end()->unparse();
    continuous |= SageUtils::compareExpression(loop2->start(), loop1End.append(" + 1"));
    if (!continuous && StringUtils::endsWith(loop1End, " - 1")) {
        string loop1EndCut = loop1End.substr(0, loop1End.length() - 4);
        continuous |= SageUtils::compareExpression(loop2->start(), loop1EndCut);
    }
    return continuous;
}

bool SageTransformUtils::isLoopsHaveContinuousHeaders(vector<SgForStmt *> &loops) {
    bool result = true;
    if (loops.size() >= 2) {
        //const hack, Sage lib does not use consts, but we will
        SgForStmt *previous = (SgForStmt *) (void *) loops.front();
        auto iterator = loops.begin();
        auto end = loops.end();
        iterator++;
        while (result && iterator != end) {
            result = result && isLoopsHaveContinuousHeaders(previous, *iterator);
            previous = *iterator;
            iterator++;
        }
    }
    return result;
}

SgVariableSymb *SageTransformUtils::addScalarVariable(SgStatement *funcHeader, char *varName, SgType *type) {
    SgVariableSymb *tmpVar = new SgVariableSymb(varName, *type);
    tmpVar->declareTheSymbol(*funcHeader);
    return tmpVar;
}

SgVariableSymb *
SageTransformUtils::addArrayVariable(SgStatement *funcHeader, SgType *baseType, vector<SgExpression *> &ranges) {
    SgArrayType *arrayType = new SgArrayType(*baseType);
    for (unsigned int i = 0; i < ranges.size(); ++i) {
        arrayType->addRange(*ranges.at(i));
    }
    SgVariableSymb *tmpVar = new SgVariableSymb(SageTransformUtils::getNewVariableName(), *arrayType);
    tmpVar->declareTheSymbol(*funcHeader);
    return tmpVar;
}

SgVariableSymb *SageTransformUtils::addArrayVariable(SgStatement *funcHeader, char *varName, SgArrayType *arrayType) {
    SgVariableSymb *tmpVar = new SgVariableSymb(varName, *arrayType);
    tmpVar->declareTheSymbol(*funcHeader);
    return tmpVar;
}

SgVariableSymb *SageTransformUtils::addArrayVariable(SgStatement *funcHeader, SgArrayType *arrayType) {
    return addArrayVariable(funcHeader, getNewVariableName(), arrayType);
}

char *SageTransformUtils::getNewVariableName() {
    char *buf = new char[4 + 4];
    sprintf(buf, "var_%02d", SageTransformUtils::variableCounter++);
    return buf;
}

char *SageTransformUtils::getNewVariableName(char *includedName) {
    char *buf = new char[4 + 4];
    sprintf(buf, "var_%s_%02d", includedName, SageTransformUtils::variableCounter++);
    return buf;
}

SgStatement *SageTransformUtils::sameLevelControlParent(SgStatement *sgStmt) {
    SgStatement *controlParent;
    if (isSgForStmt(sgStmt) || isSgIfStmt(sgStmt)) {
        controlParent = sgStmt;
    } else if (isSgControlEndStmt(sgStmt)) {
        controlParent = sgStmt->controlParent()->controlParent();
    } else {
        controlParent = sgStmt->controlParent();
    }
    return controlParent;
}
