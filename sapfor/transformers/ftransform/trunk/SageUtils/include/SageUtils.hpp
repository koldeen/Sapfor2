#ifndef SAGE_UTILS_HPP
#define SAGE_UTILS_HPP

#include "user.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace SageTransform {
    namespace SageUtils {
        //Get next statement skipping body of a scope creating ones.
        //For example skips entire loop body, or entire if statements
        //return next same scope statement or null if none available
        //SgStatement *nextSameScope(SgStatement *); //not implemented

        //Get control end for the loop
        //return pointer to the loop control end
        SgStatement *getLastLoopStatement(SgForStmt *);

        //Get Nth loop statement, n = 0, 1, ...
        //No checks are performed
        //return pointer to the loop control end
        SgStatement *getNthLoopStatement(SgForStmt *, int n);

        /**
         * Count lexical distance from base to check.
         * @param sBase base to count from
         * @param sCheck target line
         * @return 0 if sBase == sCheck,
         *         positive value if sCheck = sBase->lexNext()...->lexNext(),
         *         negative value if sCheck = sBase->lexPrev()...->lexPrev(),
         *         if value cannot be reached, LEX_INFINITY is returned
         *
         */
        int lexDist(SgStatement *sBase, SgStatement *sCheck);
        const int LEX_INFINITY = 1000000;

        /**
         * Search for next closest SgForStmt until {@param end} is reached.
         * @param pStmt search from this stmt, inclusive
         * @param end search stops at this element, inclusive. It must be lexNext'able from {@param pStmt}.
         * @return next SgForStmt
         */
        SgForStmt *lexNextLoop(SgStatement *pStmt, SgStatement *end);

        /**
         * Search for previous closest ENDDO statement until {@param end} is reached.
         * @param pStmt search from this stmt, inclusive
         * @param end search stops at this element, inclusive. It must be lexNext'able from {@param pStmt}.
         * @return next SgForStmt
         */
        SgControlEndStmt *lexPrevEnddo(SgStatement *pStmt, SgStatement *end);

        //Check if #outerForLop is a tightly nested loop of length #depth
        bool checkTightlyNested(SgForStmt *outerForLoop, int depth);

        //return the deepest for statement in for #outerForLoop.
        //#outerForLoop is expected to be tightly packed
        SgForStmt *getInnermostForStmt(SgForStmt *outerForLoop);

        //bulk overload of getInnermostForStmt(SgForStmt *)
        vector<SgForStmt *> getInnermostForStmt(vector<SgForStmt *> outerForLoops);

        //return true if this loop nest body has no statements
        //return false otherwise
        bool checkEmptyLoop(SgForStmt *outerForLoop);

        //return symbol object assigned in statement
        SgVariableSymb *getLhsSymbol(SgAssignStmt *pAssignment);

        bool hasAttribute(SgStatement *stmt, int attrType);

        int getAttributeInt(SgStatement *stmt, int attr_type);

        void setAttributeInt(SgStatement *stmt, int attrType, int *value);

        /**
         * Conservative equals check.
         * If equality cannot be ensured - false is returned.
         * @param expr1 compared expression
         * @param expr2 compared expression
         * @return true if expression values are expected to be equal at runtime, false if not or unknown.
         */
        bool equalExpressions(const SgExpression *expr1, const SgExpression *expr2);

        /**
         * Unparsed Expr is compared textually to matched string.
         * @param expr checkedExpression
         * @param toMatch matchString
         * @return true if expression is equal to matchedString
         */
        bool compareExpression(const SgExpression *expr, string &matchString);

        /*
         * Collect do-enddo loop body into a vector.
         */
        vector<SgStatement *> body(SgForStmt *loop);

        /**
         * Shorthand for std::to_string(sgStatement->lineNumber) with null check.
         * @param sgStatement can be null
         * @return result of to_string for line number or 'null' if statement pointer is nullptr.
         */
        string getLineNumber(SgStatement *sgStatement);

        /** Decodes Sage node type into human-readable form.
         * @param variant - Sage statement variant id
         * @return textual name of the variant
         */
        const char *decodeStmtVariant(int variant);
    }
}

#endif //SAGE_UTILS_HPP
