#include "LoopTransformMerge.hpp"

#include "SageUtils.hpp"
#include "SageTransformConstants.hpp"
#include "StringUtils.hpp"

using std::string;
using std::vector;
using namespace SageTransform;
using SageUtils::getLastLoopStatement;
using SageTransform::Constants::TRANSFORM_CMD_PREFIX;

const string LoopTransformMerge::MERGE_PREFIX(Constants::TRANSFORM_CMD_PREFIX + " merge");
const string LoopTransformMerge::ALIGN_PREFIX(Constants::TRANSFORM_CMD_PREFIX + " align");

bool LoopTransformMerge::checkSameAlignment(const set<set<string>> &groups, SgArrayRefExp *arrayRefA,
                                            SgArrayRefExp *arrayRefB) {
    vector<int> alignA;
    vector<int> alignB;
    for (set<set<string>>::iterator it = groups.begin(); it != groups.end(); ++it) {
        alignA = isInAlignmentGroup(*it, arrayRefA);
        if (!alignA.empty()) {
            alignB = isInAlignmentGroup(*it, arrayRefB);
            if (!alignB.empty() && vectorEquals(alignA, alignB)) {
                return true;
            }
        }
    }
    return false;
}

int LoopTransformMerge::getMergeGroupNumber(SgForStmt *pForLoopStmt) {
    int result = -1;
    char *pCharComments = pForLoopStmt->comments();
    if (pCharComments) {
        vector<string> comments = StringUtils::split(pCharComments, '\n');
        for (vector<string>::iterator pComment = comments.begin(); pComment != comments.end(); ++pComment) {
            if (StringUtils::startsWith(*pComment, MERGE_PREFIX)) {
                vector<string> tokens = StringUtils::tokenize(*pComment, ' ');
                result = atoi(tokens.at(2).c_str());
                break;
            }
        }
    }
    return result;
}

vector<SgForStmt *> LoopTransformMerge::getMergeGroupOuterLoopNodes(SgForStmt *pFirstForStmt) {
    vector<SgForStmt *> result;
    SgForStmt *next = pFirstForStmt;
    int globalGroupNumber = getMergeGroupNumber(next);
    while (next) {
        int groupNumber = getMergeGroupNumber(next);
        if (groupNumber == globalGroupNumber) {
            result.push_back(next);
        } else {
            //merged loops group collected
            break;
        }
        next = isSgForStmt(SageUtils::getLastLoopStatement(next)->lexNext());
    }
    return result;
}

SgStatement *LoopTransformMerge::merge(SgForStmt *pForStmtStart) {
    set<set<string>> sameAlignmentGroups = getSameAlignmentGroups(pForStmtStart);
    vector<SgForStmt *> outerLoops = getMergeGroupOuterLoopNodes(pForStmtStart);
    vector<SgForStmt *> innerLoops = SageUtils::getInnermostForStmt(outerLoops);
    vector<vector<vector<int>>> mergePossibilities = mergeGroups(sameAlignmentGroups, outerLoops, innerLoops);

    vector<SgStatement *> movedStmts;
    vector<uint> moveTargetLoops;
    for (uint loopI = 0; loopI < mergePossibilities.size(); ++loopI) {
        for (uint stmtI = 0; stmtI < mergePossibilities.at(loopI).size(); ++stmtI) {
            for (uint targetLoop = 0; targetLoop < mergePossibilities.at(loopI).at(stmtI).size(); ++targetLoop) {
                //just use first option
                SgStatement *stmt = SageUtils::getNthLoopStatement(innerLoops.at(loopI), stmtI);
                movedStmts.push_back(stmt);
                moveTargetLoops.push_back(mergePossibilities.at(loopI).at(stmtI).at(targetLoop));
                break;
            }
        }
        for (uint moved = 0; moved < movedStmts.size(); ++moved) {
            SgForStmt *targetLoopHeader = innerLoops.at(moveTargetLoops.at(moved));
            SgStatement *targetControlEnd = SageUtils::getLastLoopStatement(targetLoopHeader);
            SgStatement *movedStatement = movedStmts.at(moved);

            SgStatement *extracted = movedStatement->extractStmt();
            targetControlEnd->insertStmtBefore(*extracted);
        }
        movedStmts.clear();
        moveTargetLoops.clear();
    }

    SgStatement *next = SageUtils::getLastLoopStatement(outerLoops.at(outerLoops.size() - 1))->lexNext();

    for (uint i = 0; i < outerLoops.size(); ++i) {
        if (SageUtils::checkEmptyLoop(innerLoops.at(i))) {
            outerLoops.at(i)->deleteStmt();
        }
    }

    return next;
}

bool LoopTransformMerge::vectorEquals(const vector<int> &vA, const vector<int> &vB) {
    if (vA.size() != vB.size()) {
        return false;
    } else {
        for (uint i = 0; i < vA.size(); ++i) {
            if (vA.at(i) != vB.at(i)) {
                return false;
            }
        }
    }
    return true;
}

//TODO: support not only direct match
vector<int> LoopTransformMerge::getAlignShift(const string &varAlignInfo, SgArrayRefExp *arrayRef) {
    vector<int> result;
    char *exprAsString = arrayRef->unparse();
    if (strcmp(exprAsString, varAlignInfo.c_str()) == 0) {
        for (int i = 0; i < arrayRef->numberOfSubscripts(); ++i) {
            result.push_back(0);
        }
    }
    return result;
}

vector<int> LoopTransformMerge::isInAlignmentGroup(const set<string> &group, SgArrayRefExp *arrayRef) {
    vector<int> result;
    for (set<string>::iterator it = group.begin(); it != group.end(); ++it) {
        result = getAlignShift(*it, arrayRef);
        if (!result.empty()) {
            break;
        }
    }
    return result;
}


set<set<string>> LoopTransformMerge::getSameAlignmentGroups(SgForStmt *outerForLoopStmt) {
    set<set<string>> result;
    string alignPrefix(ALIGN_PREFIX);

    char *pCharComments = outerForLoopStmt->comments();
    if (pCharComments) {
        vector<string> comments = StringUtils::split(pCharComments, '\n');
        vector<string> commentsTmp = comments;
        comments.clear();
        for (vector<string>::iterator it = commentsTmp.begin(); it != commentsTmp.end(); ++it) {
            if (!it->compare(0, alignPrefix.size(), alignPrefix)) {
                comments.push_back(*it);
            }
        }

        //cleared out all non !PRG align comments
        vector<vector<string>> tokens;
        for (vector<string>::iterator i = comments.begin(); i != comments.end(); i++) {
            tokens.push_back(StringUtils::tokenizeRespectParenthesis(*i, ' '));
        }

        for (uint i = 0; i < tokens.size(); ++i) {
            set<string> group;
            for (uint j = 2; j < tokens.at(i).size(); ++j) {
                group.insert(tokens.at(i).at(j));
            }
            result.insert(group);
        }
    }
    return result;
}

vector<vector<vector<int>>> LoopTransformMerge::mergeGroups(
        const set<set<string>> &sameAlignmentGroups,
        const vector<SgForStmt *> &outerForLoopNodes,
        const vector<SgForStmt *> &innerForLoopNodes
) {
    vector<vector<vector<int>>> result;
    for (uint i = 0; i < outerForLoopNodes.size(); ++i) {
        result.push_back(vector<vector<int>>());
        SgStatement *stmt = innerForLoopNodes.at(i)->lexNext();
        SgStatement *ctrlEnd = getLastLoopStatement(innerForLoopNodes.at(i));
        while (stmt != ctrlEnd) {
            result.at(i).push_back(vector<int>());
            stmt = stmt->lexNext();
        }
    }
//    SgForStmt *hostLoopOuter;
    SgForStmt *hostLoopInner;
    SgStatement *hostLoopInnerControlEnd;
//    SgForStmt *mergedLoopOuter;
    SgForStmt *mergedLoopInner;
    SgStatement *mergedLoopInnerControlEnd;

    for (uint host = 0; host < outerForLoopNodes.size(); ++host) {
        for (uint merged = host + 1; merged < outerForLoopNodes.size(); ++merged) {
//            hostLoopOuter = outerForLoopNodes.at(host);
            hostLoopInner = innerForLoopNodes.at(host);

//            mergedLoopOuter = outerForLoopNodes.at(merged);
            mergedLoopInner = innerForLoopNodes.at(merged);

            hostLoopInnerControlEnd = getLastLoopStatement(hostLoopInner);
            mergedLoopInnerControlEnd = getLastLoopStatement(mergedLoopInner);

            SgStatement *mergedStmt;
            SgStatement *hostStmt = hostLoopInner->lexNext();
            SgAssignStmt *mergedAssign, *hostAssign;
            SgArrayRefExp *mergedArrayRef, *hostArrayRef;

            //for every assignment to array in host loop
            while (hostStmt != hostLoopInnerControlEnd) {
                if ((hostAssign = isSgAssignStmt(hostStmt))) {
                    if ((hostArrayRef = isSgArrayRefExp(hostAssign->lhs()))) {

                        //check if we can get any assignment from next loop to us
                        int mergedStmtI = 0;
                        mergedStmt = mergedLoopInner->lexNext();
                        while (mergedStmt != mergedLoopInnerControlEnd) {
                            if ((mergedAssign = isSgAssignStmt(mergedStmt))) {
                                if ((mergedArrayRef = isSgArrayRefExp(mergedAssign->lhs()))) {

                                    //check if allignment info permits moving #mergedAssign
                                    bool sameAl = checkSameAlignment(sameAlignmentGroups, hostArrayRef, mergedArrayRef);
                                    if (sameAl) {
                                        vector<vector<int>> &l1 = result.at(merged);
                                        vector<int> &l2 = l1.at(mergedStmtI);
                                        l2.push_back(host);
                                        //SgStatement * extracted = mergedAssign->extractStmt();
                                        //hostLoopInnerControlEnd->insertStmtBefore(*extracted);
                                    }
                                }
                            }
                            mergedStmt = mergedStmt->lexNext();
                            mergedStmtI++;
                        }
                    }
                }
                hostStmt = hostStmt->lexNext();
            }
        }
    }
    return result;
}
