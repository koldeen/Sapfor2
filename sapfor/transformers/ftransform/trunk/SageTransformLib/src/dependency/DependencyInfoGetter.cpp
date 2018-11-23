#include "dependency/DependencyInfoGetter.hpp"
#include "StringUtils.hpp"
#include "SageTransformException.hpp"
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;
using std::transform;
using namespace SageTransform;
using StringUtils::split;
using StringUtils::tokenize;
using SageTransform::Constants::TRANSFORM_CMD_PREFIX;

int getIntParam(string token, string prefix, int defaultValue) {
    if (!token.compare(0, prefix.size(), prefix)) {
        vector<string> tokens = StringUtils::tokenize(token, '=');
        if (tokens.size() > 1) {
            return atoi(tokens.at(1).c_str());
        }
    }
    return defaultValue;
}

DependencyInfo DependencyInfoGetter::getDependencyInfo(char *dependencyComments, int scopeStmtCount) {
    string flow = string("flow");
    string anti = string("anti");
    string output = string("output");
    string privatePrefix = string("private");
    string distancePrefix = string("distance=");

    DependencyInfo result = DependencyInfo();
    result.setStatementCount(scopeStmtCount);

    vector<string> comments = split(string(dependencyComments), '\n');
    vector<string> commentsTmp = comments;
    comments.clear();
    for (vector<string>::iterator it = commentsTmp.begin(); it != commentsTmp.end(); ++it) {
        if (!it->compare(0, TRANSFORM_CMD_PREFIX.size(), TRANSFORM_CMD_PREFIX)) {
            comments.push_back(*it);
        }
    }
    //cleared out all non PRG comments
    //TODO need to keep old comments
    vector<vector<string>> tokens;
    for (vector<string>::iterator i = comments.begin(); i != comments.end(); i++) {
        tokens.push_back(tokenize(*i, ' '));
    }
    int stmtDep, onThisStmt, distance;
    set<string> privateIdents;
    for (vector<vector<string>>::iterator i = tokens.begin(); i != tokens.end(); i++) {
        if (!(*i).at(1).compare(flow)) {
            onThisStmt = atoi((*i).at(2).c_str());
            stmtDep = atoi((*i).at(3).c_str());
            distance = getIntParam((*i).at(4), distancePrefix, -1);
            if (distance < 0) {
                throw SageTransformException("No distance in PRG dependency comment");
            }
            result.addDependency(Dependency(Dependency::FLOW_DEP, onThisStmt, stmtDep, distance));
        }
        if (!(*i).at(1).compare(anti)) {
            onThisStmt = atoi((*i).at(2).c_str());
            stmtDep = atoi((*i).at(3).c_str());
            distance = getIntParam((*i).at(4), distancePrefix, -1);
            if (distance < 0) {
                throw "No distance in PRG dependency comment";
            }
            result.addDependency(Dependency(Dependency::ANTI_DEP, onThisStmt, stmtDep, distance));
        }
        if (!(*i).at(1).compare(output)) {
            onThisStmt = atoi((*i).at(2).c_str());
            stmtDep = atoi((*i).at(3).c_str());
            distance = getIntParam((*i).at(4), distancePrefix, -1);
            if (distance < 0) {
                throw "No distance in PRG dependency comment";
            }
            result.addDependency(Dependency(Dependency::OUTPUT_DEP, onThisStmt, stmtDep, distance));
        }
        if (!(*i).at(1).compare(privatePrefix)) {
            for (unsigned int privateIdentNum = 2; privateIdentNum < i->size(); privateIdentNum++) {
                string privateVarName(i->at(privateIdentNum));
                transform(privateVarName.begin(), privateVarName.end(), privateVarName.begin(), ::tolower);
                privateIdents.insert(privateVarName);
            }
        }
    }
    result.setPrivateVarIdentifers(privateIdents);
    return result;
}

bool DependencyInfoGetter::hasDependencyInfo(SgStatement *pForStmt) {
    if (pForStmt->comments()) {
        vector<string> comments = split(string(pForStmt->comments()), '\n');
        for (vector<string>::iterator it = comments.begin(); it != comments.end(); ++it) {
            if (it->compare(0, TRANSFORM_CMD_PREFIX.size(), TRANSFORM_CMD_PREFIX) == 0) {
                vector<string> tokens = tokenize(*it, ' ');
                if (tokens.size() >= 2) {
                    if (tokens[1].compare("flow") == 0
                        || tokens[1].compare("output") == 0
                        || tokens[1].compare("anti") == 0
                        || tokens[1].compare("private") == 0) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
