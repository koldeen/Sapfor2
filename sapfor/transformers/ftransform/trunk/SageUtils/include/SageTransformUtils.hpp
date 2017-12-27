#ifndef SAGE_TRANSFORM_UTILS_HPP
#define SAGE_TRANSFORM_UTILS_HPP

#include <vector>
#include "user.h"

using std::vector;

namespace SageTransform {
    namespace SageTransformUtils {
        /**
         * Create new do-enddo loop around specified code part.
         *
         * --previous code
         * --headerAfterThis--
         * do i = start, end, step
         *   <body statements in order given>
         * enddo
         * --further code
         *
         * @return reference to new loop
         */
        SgForStmt *createForStmt(SgStatement *createAfter,
                                 SgSymbol *tmpVar, SgExpression *start,
                                 SgExpression *end, SgExpression *step, vector<SgStatement *> body);

        /**
         * Create a fake loop with 1 iteration of given symbol
         * @param index variable
         * @return created for loop
         */
        SgForStmt *createOneIterationLoop(SgSymbol *indexVariable);

        SgIfStmt *createIfStmt(SgStatement *createAfter, SgExpression *condition, vector<SgStatement *> body);

        SgExpression *variableInBetween(SgExpression *low, SgExpression *high, SgSymbol *variable);

        vector<SgStatement *> copyStatements(const vector<SgStatement *> &originals);

        vector<SgStatement *> copyStatements(const vector<SgForStmt *> &originals);

        /**
         * Move a statement one line to beginning.
         * @param pStmt statement to move
         * @return new position of the pStmt
         */
        SgStatement* swapWithLexPrev(SgStatement *pStmt);

        //Swap target statements lexically
        void swapLexStmt(SgStatement *, SgStatement *);

        //Swap target and next statement.
        //For Loop is swapped with its body, same for If statement
        void swapScopeStmt(SgStatement *, SgStatement *);

        //move bunch of statements to new location
        //location is not allowed to be among moved statements
        void moveStatements(SgStatement *beginInclusive, SgStatement *endExclusive, SgStatement *moveAfterThis);

        /**
         * Mechanically merge 2 loop bodies under one loop header.
         * Loop headers should be the same.
         * After merging the first loop contains: [body of first loop] + [body of second loop].
         * Second loop stays, but is [empty].
         * @param loop1 first loop to merge.
         * @param loop2 second loop to merge. Should be in the same block as first loop, and after it.
         */
        void moveLoopBody(SgForStmt *recipientLoop, SgForStmt *sourceLoop);

        void removeLoop(SgForStmt *removeLoop);

        /**
         * Checks whether loops have same iteration space.
         * @param loop1 checked loop
         * @param loop2 checked loop
         * @return true if loops have same iteration space.
         */
        bool isLoopsHaveSameHeader(SgForStmt *loop1, SgForStmt *loop2);

        /**
         * Short to check all loops have the same header.
         * Uses {@link isLoopsHaveSameHeader()} inside.
         * @param loops list of loop references
         * @return true if all loops have the same header
         */
        bool isLoopsHaveSameHeader(vector<SgForStmt *> &loops);

        /**
         * Check whether two loops have continuous iteration space.
         * @param loop1 checked loop
         * @param loop2 checked loop
         * @return true if loop1 gracefully continues into loop2 within iteration space.
         */
        bool isLoopsHaveContinuousHeaders(SgForStmt *loop1, SgForStmt *loop2);

        /**
         * Short to check all loops have continuous iteration space.
         * Uses {@link isLoopsHaveContinuousHeaders()} inside.
         * @param loops list of loop references
         * @return true if all loops continue in a chain
         */
        bool isLoopsHaveContinuousHeaders(vector<SgForStmt *> &loops);

        //Add new acalar variable to scope #func with type #type
        //return pointer to new variable symbol
        SgVariableSymb *addScalarVariable(SgStatement *funcHeader, char *varName, SgType *type);

        //Add new array variable to #func with basetype #type and #ranges
        //return pointer to new variable symbol
        SgVariableSymb *addArrayVariable(SgStatement *funcHeader, SgType *basetype, vector<SgExpression *> &ranges);

        //Add new array variable to #func with #arraytype and #varName
        //return pointer to new variable symbol
        SgVariableSymb *addArrayVariable(SgStatement *funcHeader, char *varName, SgArrayType *arrayType);

        //Add new array variable to #func with basetype #type and #ranges
        //return pointer to new variable symbol
        SgVariableSymb *addArrayVariable(SgStatement *funcHeader, SgArrayType *arrayType);

        //return new tmp variable identifier
        char *getNewVariableName();

        //return new tmp variable identifier
        char *getNewVariableName(char *includedName);

        /**
         * returns input if it is DO header or IF header
         * For simple statements returns control parent
         */
        SgStatement *sameLevelControlParent(SgStatement *sgStatement);
    }
}

#endif //SAGE_TRANSFORM_UTILS_HPP
