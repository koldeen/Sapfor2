#include <iostream>
#include "SageUtils.hpp"
#include "SageTransformException.hpp"

using namespace SageTransform;
using std::string;

SgStatement *SageUtils::getLastLoopStatement(SgForStmt *pForLoop) {
    SgStatement *stmt = pForLoop->body();
    while (stmt &&
           !(isSgControlEndStmt(stmt) && stmt->controlParent() && stmt->controlParent()->id() == pForLoop->id())) {
        stmt = stmt->lexNext();
    }
    return stmt;
}

SgStatement *SageUtils::getNthLoopStatement(SgForStmt *pForLoop, int n) {
    SgStatement *stmt = pForLoop->lexNext();
    for (int i = 0; i < n; ++i) {
        stmt = stmt->lexNext();
    }
    return stmt;
}

bool SageUtils::checkTightlyNested(SgForStmt *outerLoop, int depth) {
    SgForStmt *innermostLoop = outerLoop;
    for (int i = 0; i < depth - 1; ++i) {
        if (isSgForStmt(innermostLoop->lexNext())) {
            innermostLoop = isSgForStmt(innermostLoop->lexNext());
        } else {
            return false;
        }
    }
    SgStatement *controlEnd = SageUtils::getLastLoopStatement(innermostLoop);
    for (int i = 0; i < depth - 1; ++i) {
        if (isSgControlEndStmt(controlEnd->lexNext())) {
            controlEnd = isSgControlEndStmt(controlEnd->lexNext());
        } else {
            return false;
        }
    }
    return true;
}

SgForStmt *SageUtils::getInnermostForStmt(SgForStmt *outerLoop) {
    SgForStmt *innermostLoop = outerLoop;
    while (isSgForStmt(innermostLoop->lexNext())) {
        innermostLoop = isSgForStmt(innermostLoop->lexNext());
    }
    return innermostLoop;
}

vector<SgForStmt *> SageUtils::getInnermostForStmt(vector<SgForStmt *> outerForLoops) {
    vector<SgForStmt *> result;
    for (vector<SgForStmt *>::iterator it = outerForLoops.begin(); it != outerForLoops.end(); ++it) {
        result.push_back(getInnermostForStmt(*it));
    }
    return result;
}

bool SageUtils::checkEmptyLoop(SgForStmt *outerForLoop) {
    SgForStmt *innerFor = getInnermostForStmt(outerForLoop);
    SgStatement *controlEnd = getLastLoopStatement(innerFor);
    return innerFor->lexNext() == controlEnd;
}

SgVariableSymb *SageUtils::getLhsSymbol(SgAssignStmt *pAssignment) {
    SgExpression *lhsExpr = pAssignment->lhs();
    SgSymbol *symbol = isSgVarRefExp(lhsExpr)->symbol();
    return isSgVariableSymb(symbol);
}

bool SageUtils::hasAttribute(SgStatement *stmt, int attrType) {
    SgAttribute *attr = stmt->getAttribute(0, attrType);
    return attr != NULL;
}

int SageUtils::getAttributeInt(SgStatement *stmt, int attrType) {
    SgAttribute *attr = stmt->getAttribute(0, attrType);
    int a = *((int *) attr->getAttributeData());
    return a;
}

void SageUtils::setAttributeInt(SgStatement *stmt, int attrType, int *value) {
    SgAttribute *attr = stmt->getAttribute(0, attrType);
    if (attr != NULL) {
        int *data = (int *) attr->getAttributeData();
        *data = *value;
    } else {
        SgAttribute *stmtIdAttr = new SgAttribute(attrType, value, sizeof(*value), *stmt, 0/*not used*/);
        stmt->addAttribute(stmtIdAttr);
    }
}

bool SageUtils::equalExpressions(const SgExpression *expr1const, const SgExpression *expr2const) {
    //const hack, Sage lib does not use consts, but we will
    SgExpression *expr1 = (SgExpression *) (void *) expr1const;
    SgExpression *expr2 = (SgExpression *) (void *) expr2const;
    if (expr1 == nullptr || expr2 == nullptr) {
        throw SageTransformException("nullptr instead of expression in SageUtils#equalExpression");
    }
    string e1 = expr1->unparse();
    string e2 = expr2->unparse();
    bool result = e1.compare(e2) == 0;
    std::cout << "Comparing " << e1 << " and " << e2 << " == " << result << std::endl;
    return result;
}

bool SageUtils::compareExpression(const SgExpression * expr1const, string& matchString) {
    SgExpression *expr1 = (SgExpression *) (void *) expr1const;
    if (expr1 == nullptr) {
        throw SageTransformException("nullptr instead of expression in SageUtils#equalExpression");
    }
    return string(expr1->unparse()).compare(matchString) == 0;
}

vector<SgStatement *> SageUtils::body(SgForStmt * loop) {
    vector<SgStatement *> body;
    SgStatement * bodyStmt = loop->lexNext();
    SgStatement * end = getLastLoopStatement(loop);
    while (bodyStmt != end) {
        body.push_back(bodyStmt);
        bodyStmt = bodyStmt->lexNext();
    }
    return body;
}

string SageUtils::getLineNumber(SgStatement *sgStatement) {
    if (sgStatement == nullptr) {
        return string("null");
    } else {
        return std::to_string(sgStatement->lineNumber());
    }
}

SgForStmt *SageUtils::lexNextLoop(SgStatement *pStmt, SgStatement *end) {
    SgStatement *pClosestDo = pStmt;
    while (!isSgForStmt(pClosestDo) && pClosestDo != end) {
        pClosestDo = pClosestDo->lexNext();
    }
    return isSgForStmt(pClosestDo);
}

SgControlEndStmt *SageUtils::lexPrevEnddo(SgStatement *pStmt, SgStatement *end) {
    SgStatement *pClosestEndDo = pStmt;
    while (!isSgControlEndStmt(pClosestEndDo) && pClosestEndDo != end) {
        pClosestEndDo = pClosestEndDo->lexPrev();
    }
    return isSgControlEndStmt(pClosestEndDo);
}
