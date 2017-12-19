#ifndef LOOP_TRANSFORM_TIGHTEN_HPP
#define LOOP_TRANSFORM_TIGHTEN_HPP

#include <string>
#include <map>
#include <stack>
#include "user.h"
#include "SageTransformConstants.hpp"
#include "Dependencies.hpp"
#include "BaseTransform.hpp"
#include "LineReorderRecord.hpp"

using std::string;
using std::map;
using std::vector;
using std::stack;
using std::pair;
using SageTransform::Constants::TRANSFORM_CMD_PREFIX;

namespace SageTransform {
    class LoopTransformTighten : public BaseTransform {
    private: //static fields and functions
        //map<filename, vector<{forloop, applied reorder}>>
        static map<string, stack<pair<SgStatement *, LineReorderRecord>>> LAUNCHES;
    public:
        static map<string, stack<pair<SgStatement *, LineReorderRecord>>> *getLaunches() { return &LAUNCHES; }
    private:
        static void storeLaunch(SgStatement * pStmt, const LineReorderRecord& reorder);

    public:
        bool hasTightenComment(SgForStmt *pForLoop);

        //returns positive number - depth of tightness of #pForLoop
        int getTightness(SgForStmt *pForLoop);

        //check if by sinking statements into nested loop bodies
        //#pForLoop can be tightened
        //returns 0 of cannot tighten this loops' inner loops,
        //        2+ if this level of nested loop can be achieved
        int canTighten(SgForStmt *pForLoop);

        /**
         * Access amount of achievable tightening by moving invariants inside internal loops.
         * Performs correctness validations.
         *
         * @param pForLoop outer loop for tightening
         * @param dependencies info for symbols in internal loops
         * @return achievable level of tightening, value is 2+ or 0 if cannot transform
         */
        /*deprecated*/
        int canTighten(SgForStmt *pForLoop, std::map<SgSymbol *, DependencyType> &dependencies);

        //expects that pForLoop contains single level other loop and some statements before inner loop header
        //several same scope child loops are not allowed
        //statements after inner loop are not allowed
//        int canTighten(SgForStmt *pForLoop,
//                       std::pair<SgForStmt *, depGraph *> &outerLoopDependencies,
//                       std::pair<SgForStmt *, depGraph *> &innerLoopDependencies);

        /**
         * tighten #level-1 nested loops after given to create a #level nested loop
         * return true if succeeded, false otherwise (loop stays untouched then)
         * Moves statements before and after inner loop.
         */
        //todo example for after moving
        //todo test rainy day untouched
        bool tighten(SgForStmt *pForLoop, int level = 2);

        //remove "!PRG dimension access" from outer loop
        void removeComment(SgStatement *sgStatement);

        static string COMMENT_PREFIX;
    private:
        bool canTightenSingleLevel(SgForStmt *pForLoop, std::map<SgSymbol *, DependencyType> &dependencies);

        bool validateInvariantStatementBeforeLoop(SgStatement *invBegin, SgStatement *invEnd,
                                                  std::map<SgSymbol *, DependencyType> &dependencies);

        bool validateInvariantStatementAfterLoop(SgStatement *invBegin, SgStatement *invEnd,
                                                 std::map<SgSymbol *, DependencyType> &dependencies);

        LineReorderRecord tightenSingleLevel(SgForStmt *pForLoop, SgForStmt *topLevelForLoop);

        /**
         * Sinks pStmt into nearest next same-scope loop in following code if possible.
         * @param pStmt
         * @return reference to new SgStatement
         */
        SgStatement *sinkIntoNextNearestLoop(SgStatement *pStmt, SgStatement *nextLoop);

        /**
         * Sinks pStmt into nearest previous same-scope loop in preceding code if possible.
         * @param pStmt
         * @return reference to new SgStatement
         */
        SgStatement *sinkIntoPreviousNearestLoop(SgStatement *pStmt);
    };
}

#endif //LOOP_TRANSFORM_TIGHTEN_HPP
