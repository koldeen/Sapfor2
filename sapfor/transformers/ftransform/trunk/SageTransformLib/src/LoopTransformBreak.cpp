#include "LoopTransformBreak.hpp"

#include <iostream>
#include <algorithm>
#include <SageTransformConstants.hpp>
#include "StringUtils.hpp"
#include "SageUtils.hpp"

using namespace SageTransform;

using SageUtils::decodeStmtVariant;
using SageTransform::Constants::TRANSFORM_CMD_PREFIX;

bool LoopTransformBreak::hasValidBreakComment(SgForStmt *outerForLoopNode) {
    char *c = outerForLoopNode->comments();
    string comment;
    comment.append(" remote access no dependencies").insert(0, TRANSFORM_CMD_PREFIX);
    if (c) {
        vector<string> lines = StringUtils::tokenize(string(c), '\n');
        for (uint i = 0; i < lines.size(); ++i) {
            bool breakComment = StringUtils::startsWith(lines.at(i), comment);
            if (breakComment) {
                std::cout << "WARN: Not checking that break comment has all statements mentioned" << std::endl;
                return true;
            }
        }
    }
    return false;
}

vector<vector<uint>> LoopTransformBreak::getFullBreakSchema(SgForStmt *outerForLoopNode) {
    vector<vector<uint>> result;
    SgForStmt *innerForLoop = SageUtils::getInnermostForStmt(outerForLoopNode);
    SgStatement *innerControlEnd = SageUtils::getLastLoopStatement(innerForLoop);
    SgStatement *stmt = innerForLoop->lexNext();
    int stmtNum = 0;
    while (stmt != innerControlEnd) {
        vector<uint> group;
        group.push_back(stmtNum);
        result.push_back(group);
        stmt = stmt->lexNext();
        stmtNum++;
    }
    return result;
}

vector<vector<uint>> LoopTransformBreak::getBreakSchema(SgForStmt *outerForLoopNode) {
    vector<vector<uint>> result;
    char *c = outerForLoopNode->comments();
    string &comment = string(" remote access").insert(0, TRANSFORM_CMD_PREFIX);
    if (c) {
        vector<string> lines = StringUtils::tokenize(string(c), '\n');
        for (uint i = 0; i < lines.size(); ++i) {
            bool breakComment = StringUtils::startsWith(lines.at(i), comment);
            if (breakComment) {
                vector<string> parts = StringUtils::tokenize(lines.at(i), ' ');
                vector<uint> group;
                for (uint j = 3; j < parts.size(); ++j) {
                    if (parts.at(j).compare("-") == 0) {
                        //new group starts
                        result.push_back(group);
                        group = vector<uint>();
                    } else {
                        group.push_back(atoi(parts.at(j).c_str()));
                    }
                }
                result.push_back(group);
                //only one break comment is allowed - first one is used
                break;
            }
        }
    }
    return result;
}

void LoopTransformBreak::breakLoop(SgForStmt *outerForLoopNode, SgForStmt *innerForLoopNode,
                                   const vector<vector<uint>> &breakSchema) {
    int bodyLength = innerForLoopNode->numberOfChildrenList1() - 1;
//    SgStatement *outerLoopControlEnd;
//    outerLoopControlEnd = SageUtils::getLastLoopStatement(outerForLoopNode);

    vector<SgForStmt *> outerLoops;
    vector<SgForStmt *> innerLoops;
    for (uint groupI = 0; groupI < breakSchema.size(); ++groupI) {
        std::cout << "LTB::bl() Creating group " << groupI << std::endl;
        SgForStmt *outerLoopCopy = isSgForStmt(outerForLoopNode->copyPtr());
        SgForStmt *innerLoopCopy = SageUtils::getInnermostForStmt(outerLoopCopy);
        outerForLoopNode->insertStmtBefore(*outerLoopCopy);

        outerLoops.push_back(outerLoopCopy);
        innerLoops.push_back(innerLoopCopy);

        //the first resulting loop gets all old comments
        if (groupI == 0) {
            //lost all comments, need to remove !PRG from comments and save others
            outerLoopCopy->setComments((TRANSFORM_CMD_PREFIX + " loop split\n").c_str());
        }

        int deleted = 0;
        for (int stmtI = 0; stmtI < bodyLength; ++stmtI) {
            int effectiveStmtIndex = stmtI - deleted;
            if (std::find(breakSchema.at(groupI).begin(), breakSchema.at(groupI).end(), stmtI) !=
                breakSchema.at(groupI).end()) {
                /* contains */
                //keep stmt
                std::cout << "LTB::bL()   keeping stmt " << stmtI << " "
                          << decodeStmtVariant(innerLoopCopy->childList1(effectiveStmtIndex)->variant()) << std::endl;
            } else {
                /* does not contain */
                //remove stmt from this loop copy
                std::cout << "LTB::bL()   remove  stmt " << stmtI << " "
                          << decodeStmtVariant(innerLoopCopy->childList1(effectiveStmtIndex)->variant()) << std::endl;

                innerLoopCopy->childList1(effectiveStmtIndex)->setComments("!If you see this, split went wrong\n");
                innerLoopCopy->childList1(effectiveStmtIndex)->deleteStmt(); //extractStmt()->
                deleted++;
            }
        }
    }

    for (uint i = 0; i < outerLoops.size(); ++i) {
        if (SageUtils::checkEmptyLoop(innerLoops.at(i))) {
            outerLoops.at(i)->deleteStmt();
        }
    }
    outerForLoopNode->deleteStmt();
}	
