#include <SageTransformException.hpp>
#include "LoopTransformTighten.hpp"

#include "StringUtils.hpp"
#include "MapUtils.hpp"
#include "SageUtils.hpp"
#include "SageTransformUtils.hpp"
#include "Log.hpp"

using std::vector;
using std::to_string;
using namespace SageTransform;
using StringUtils::split;
using StringUtils::tokenize;
using SageUtils::getLineNumber;
using SageUtils::lexNextLoop;
using SageUtils::lexPrevEnddo;
using SageUtils::lexDist;
using SageTransformUtils::moveStatements;
using MapUtils::getOrDefault;

string LoopTransformTighten::COMMENT_PREFIX("!PRG dimension access");

map<string, stack<pair<SgStatement *, LineReorderRecord>>> LoopTransformTighten::LAUNCHES;

void LoopTransformTighten::storeLaunch(SgStatement * pStmt, const LineReorderRecord& reorder) {
    string filename = SageUtils::getFilename(pStmt);
    if (LAUNCHES.count(filename) == 0) {
        LAUNCHES.insert({filename, stack<pair<SgStatement *, LineReorderRecord>>()});
    }
    stack<pair<SgStatement *, LineReorderRecord>> &stack = LAUNCHES.at(filename);
    stack.push(std::make_pair(pStmt, reorder));
}

bool LoopTransformTighten::hasTightenComment(SgForStmt *pStmt) {
    if (pStmt->comments()) {
        vector<string> comments = split(string(pStmt->comments()), '\n');
        for (vector<string>::iterator it = comments.begin(); it != comments.end(); ++it) {
            if (!it->compare(0, COMMENT_PREFIX.size(), COMMENT_PREFIX)) {
                return true;
            }
        }
    }
    return false;
}

int LoopTransformTighten::getTightness(SgForStmt *pForLoop) {
    int nestnessLevel = 1;
    SgForStmt *nextOuterLoop = pForLoop;
    while (nextOuterLoop) {
        SgStatement *outerLoopControlEnd = SageUtils::getLastLoopStatement(nextOuterLoop);
        SgStatement *outerLoopNextStmt = nextOuterLoop->lexNext();
        SgStatement *nextInnerLoop = nextOuterLoop->lexNext();
        while (!isSgForStmt(nextInnerLoop) && nextInnerLoop != outerLoopControlEnd) {
            nextInnerLoop = nextInnerLoop->lexNext();
        }
        if (nextInnerLoop == outerLoopControlEnd) {
            //no for loops found in outerloop
            nextOuterLoop = NULL;
        } else {
            //inner for loop found

            //check control ends
            SgForStmt *innerLoop = isSgForStmt(nextInnerLoop);
            SgStatement *innerControlEnd = SageUtils::getLastLoopStatement(innerLoop);
            if (innerControlEnd->lexNext() == outerLoopControlEnd && innerLoop == outerLoopNextStmt) {
                //loop headers are tight, controls are tight
                nestnessLevel++;
                nextOuterLoop = innerLoop;
            } else {
                //not tight inner loop
                nextOuterLoop = NULL;
            }
        }
    }
    return nestnessLevel;
}

int LoopTransformTighten::canTighten(SgForStmt *pForLoop) {
    int nestnessLevel = 1;
    SgForStmt *nextOuterLoop = pForLoop;
    while (nextOuterLoop) {
        SgStatement *outerLoopControlEnd = SageUtils::getLastLoopStatement(nextOuterLoop);
        SgStatement *nextInnerLoop = nextOuterLoop->lexNext();
        while (!isSgForStmt(nextInnerLoop) && nextInnerLoop != outerLoopControlEnd) {
            nextInnerLoop = nextInnerLoop->lexNext();
        }
        if (nextInnerLoop == outerLoopControlEnd) {
            //no for loops found in outerloop
            nextOuterLoop = NULL;
        } else {
            //inner for loop found

            //check control ends
            SgForStmt *innerLoop = isSgForStmt(nextInnerLoop);
            SgStatement *innerControlEnd = SageUtils::getLastLoopStatement(innerLoop);
            if (innerControlEnd->lexNext() == outerLoopControlEnd) {
                //controls are tight, can tighten this
                nestnessLevel++;
                nextOuterLoop = innerLoop;
            } else {
                //TODO: invariants after loop body
                //cannot tighten loop further, stop here
                nextOuterLoop = NULL;
            }
        }
    }
    if (nestnessLevel == 1) {
        return 0;
    } else {
        return nestnessLevel;
    }
}

int LoopTransformTighten::canTighten(SgForStmt *pForLoop, std::map<SgSymbol *, DependencyType> &dependencies) {
    int nestDepth = 1;
    SgForStmt *processedLoop = pForLoop;
    while (canTightenSingleLevel(processedLoop, dependencies)) {
        processedLoop = lexNextLoop(processedLoop->lexNext(), NULL);
        nestDepth++;
    }
    return nestDepth;
}

/*
int LoopTransformTighten::canTighten(SgForStmt *outerLoop,
                                     std::pair<SgForStmt *, depGraph *> &outerLoopDeps,
                                     std::pair<SgForStmt *, depGraph *> &innerLoopDeps) {
    SgStatement *outerEnddo = SageUtils::getLastLoopStatement(outerLoop);
    SgForStmt *innerLoop = lexNextLoop(outerLoop->lexNext(), outerEnddo);
    SgStatement *innerEnddo = SageUtils::getLastLoopStatement(innerLoop);
    depGraph *outerDepGraph = outerLoopDeps.second;
    std::map<SgSymbol *, DepType> depMap;
    for (SgStatement *stmt = outerLoop->lexNext(); stmt != innerLoop; stmt = stmt->lexNext()) {
        //loop through invariants before inner loop

        for (SgStatement *bodyStmt = innerLoop->lexNext(); bodyStmt != innerEnddo; bodyStmt = bodyStmt->lexNext()) {
            depNode *node = outerDepGraph->isThereAnEdge(stmt, bodyStmt);
            if (node != nullptr) {
                DepType type = DependencyType::fromDepNode(node);
                SgSymbol *symbol = node->varout->symbol();
                depMap.insert(std::make_pair(symbol, type));
            }
        }
    }
    return canTighten(outerLoop, depMap);
}
*/

bool
LoopTransformTighten::canTightenSingleLevel(SgForStmt *outerLoop, std::map<SgSymbol *, DependencyType> &dependencies) {
    SgStatement *outerEnddo = SageUtils::getLastLoopStatement(outerLoop);
    SgForStmt *innerLoop = lexNextLoop(outerLoop->lexNext(), outerEnddo);
    if (innerLoop != NULL) {
        bool beforeValid = validateInvariantStatementBeforeLoop(
                outerLoop->lexNext(),
                innerLoop,
                dependencies);
        bool afterValid = validateInvariantStatementAfterLoop(
                SageUtils::getLastLoopStatement(innerLoop)->lexNext(),
                outerEnddo,
                dependencies);
        return beforeValid && afterValid;
    } else {
        return false;
    }
}

bool LoopTransformTighten::validateInvariantStatementBeforeLoop(SgStatement *invBegin, SgStatement *invEnd,
                                                                std::map<SgSymbol *, DependencyType> &dependencies) {
    //by type check
    SgStatement *stmt = invBegin;
    bool allAssignment = true;
    while (stmt != invEnd && allAssignment) {
        allAssignment = allAssignment && isSgAssignStmt(stmt);
        stmt = stmt->lexNext();
    }
    if (allAssignment) {
        bool hasFlowDep = false;
        stmt = invBegin;
        while (stmt != invEnd && !hasFlowDep) {
            SgAssignStmt *assignStmt = isSgAssignStmt(stmt);
            SgSymbol *symbol = assignStmt->lhs()->symbol();
            hasFlowDep = hasFlowDep
                         || getOrDefault(dependencies, symbol, DependencyType::NO_VALUE) == DependencyType::FLOW_DEP
                         || getOrDefault(dependencies, symbol, DependencyType::NO_VALUE) == DependencyType::UNKNOWN_DEP;
            stmt = stmt->lexNext();
        }
        if (hasFlowDep) {
            bool noAntiOrOutputDep = true;
            stmt = invBegin;
            while (stmt != invEnd && noAntiOrOutputDep) {
                SgAssignStmt *assignStmt = isSgAssignStmt(stmt);
                SgSymbol *symbol = assignStmt->lhs()->symbol();
                noAntiOrOutputDep = noAntiOrOutputDep && getOrDefault(dependencies, symbol, DependencyType::NO_VALUE) == DependencyType::ANTI_DEP;
                noAntiOrOutputDep = noAntiOrOutputDep && getOrDefault(dependencies, symbol, DependencyType::NO_VALUE) == DependencyType::OUTPUT_DEP;
                noAntiOrOutputDep = noAntiOrOutputDep && getOrDefault(dependencies, symbol, DependencyType::NO_VALUE) == DependencyType::UNKNOWN_DEP;
                stmt = stmt->lexNext();
            }
            if (noAntiOrOutputDep) {
                string msg = "Only flow dependencies present, can tighten.";
                this->addMessage(0, invBegin->lineNumber(), msg);
                return true;
            }
        } else {
            string msg = "Invariant value not used in loop, can tighten.";
            this->addMessage(0, invBegin->lineNumber(), msg);
            return true;
        }
    }
    string msg = "Invariant cannot be moved into loop.";
    this->addMessage(0, invBegin->lineNumber(), msg);
    return false;
}

bool LoopTransformTighten::validateInvariantStatementAfterLoop(SgStatement *invBegin, SgStatement *invEnd,
                                                               std::map<SgSymbol *, DependencyType> &dependencies) {
    if (invBegin == invEnd) {
        string msg = "No invariants after loop";
        this->addMessage(0, invBegin->lineNumber(), msg);
        return true; //no after invariant;
    }
    string msg = "There are invariants after loop, cannot tighten";
    this->addMessage(0, invBegin->lineNumber(), msg);
    return false; //unknown, why would loop need that
}

bool LoopTransformTighten::tighten(SgForStmt *pForLoop, int level) {
    if (level > canTighten(pForLoop)) {
        //cannot do that
        return false;
    }
    int processing = 2;
    SgForStmt *processedLoop = pForLoop;
    LineReorderRecord reorderRecord, levelRecord;
    while (processing <= level) {
        levelRecord = tightenSingleLevel(processedLoop, pForLoop);
        reorderRecord = reorderRecord.combine(levelRecord);
        processedLoop = lexNextLoop(processedLoop->lexNext(), NULL);
        processing++;
    }
    string filename = SageUtils::getFilename(pForLoop);
    storeLaunch(pForLoop, reorderRecord);
    return true;
}

LineReorderRecord LoopTransformTighten::tightenSingleLevel(SgForStmt *outerLoop, SgForStmt *topLevelForLoop) {
    SgForStmt *innerLoop = lexNextLoop(outerLoop->lexNext(), NULL);
    LineReorderRecord reorder;
    {
        //move statements after given loop before the inner loop

        //moving these statements is done in reverse order,
        // because insertion is always after the inner loop header

        int placeBefore = lexDist(topLevelForLoop, innerLoop); //shifted loop header is here
        int placeAfter = lexDist(topLevelForLoop, outerLoop) + 1; // and will be here
        reorder.addMove(placeBefore, placeAfter);
        for (int i = placeAfter; i <= placeBefore - 1; i++) {
            reorder.addMove(i, i + 1);
        }

        //begin := statement before closest inner loop header
        SgStatement *begin = innerLoop->lexPrev();
        SgStatement *end = outerLoop;
        SgStatement *stmt = begin;
        SgStatement *next;
        while (stmt != end) {
            next = stmt->lexPrev();
            sinkIntoNextNearestLoop(stmt, innerLoop);
            stmt = next;
        }
    }
    {
        //move statements before given loop enddo after the inner loop enddo

        //moving these statements is done in normal order,
        // insertion is done before inner loop enddo

        //begin := statement after closest inner loop enddo
        SgStatement *begin = SageUtils::getLastLoopStatement(innerLoop)->lexNext();
        SgStatement *end = SageUtils::getLastLoopStatement(outerLoop);
        SgStatement *stmt = begin;
        SgStatement *next;
        while (stmt != end) {
            next = stmt->lexNext();
            sinkIntoPreviousNearestLoop(stmt);
            stmt = next;
        }
    }
    return reorder;
}

void LoopTransformTighten::removeComment(SgStatement *sgStatement) {
    char *pCharComments = sgStatement->comments();
    if (pCharComments) {
        StringUtils::removeLineStartingWith(pCharComments, COMMENT_PREFIX);
    } else {
        Log::warn("Try to remove comments from " + getLineNumber(sgStatement) +
                 " but it has no comments");
    }
}

SgStatement *LoopTransformTighten::sinkIntoNextNearestLoop(SgStatement *pStmt, SgStatement *nextLoop) {
    Log::debug("sinkIntoNextNearestLoop " + getLineNumber(pStmt));

    SgStatement *extr = pStmt->extractStmt();
    nextLoop->insertStmtAfter(*extr, *nextLoop);
    return pStmt;

    /* OLD VARIANT with copy
    SgForStmt *nextLoop = lexNextLoop(pStmt, NULL);
    SgStatement *pStmtCopy = pStmt->copyPtr();
    pStmt->deleteStmt();
    nextLoop->insertStmtAfter(*pStmtCopy, *nextLoop);
    return pStmtCopy;*/
}

SgStatement *LoopTransformTighten::sinkIntoPreviousNearestLoop(SgStatement *pStmt) {
    Log::debug("sinkIntoPreviousNearestLoop " + getLineNumber(pStmt));

    SgControlEndStmt *ctrlEnd = lexPrevEnddo(pStmt, NULL);
    SgForStmt *scope = isSgForStmt(ctrlEnd->controlParent());
    SgStatement *pStmtCopy = pStmt->extractStmt();
    ctrlEnd->insertStmtBefore(*pStmtCopy, *scope);
    return pStmtCopy;

    /* OLD VARIANT with copy
    SgControlEndStmt *ctrlEnd = lexPrevEnddo(pStmt, NULL);
    SgForStmt *scope = isSgForStmt(ctrlEnd->controlParent());
    SgStatement *pStmtCopy = pStmt->copyPtr();
    pStmt->deleteStmt();
    ctrlEnd->insertStmtBefore(*pStmtCopy, *scope);
    return pStmtCopy;*/
}

/*
bool hasSinkComment(SgStatement * pStmt) {
    if (pStmt->comments()) {
        vector<string> comments = split(string(pStmt->comments()), '\n');
        for (vector<string>::iterator it = comments.begin(); it != comments.end(); ++it) {
            if (!it->compare(0, COMMENT_PREFIX.size(), COMMENT_PREFIX)) {
                return true;
            }
        }
    }
    return false;
}
*/
