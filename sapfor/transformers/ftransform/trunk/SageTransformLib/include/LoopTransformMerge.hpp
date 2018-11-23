#ifndef LOOP_TRANSFORM_MERGE_HPP
#define LOOP_TRANSFORM_MERGE_HPP

#include <vector>
#include "user.h"

#include "dependency/DependencyInfo.hpp"

using std::vector;

typedef unsigned int uint;

namespace SageTransform {
    class LoopTransformMerge {
    public:
        static const std::string MERGE_PREFIX;
        static const std::string ALIGN_PREFIX;

        //find alignment info in !PRG comments
        //and build groups
        static set<set<string>> getSameAlignmentGroups(SgForStmt *outerForLoopStmt);

        //for '!PRG merge x' special comment
        //there should be only one such comment
        //returns x if such a comment is present, returns -1 if not
        static int getMergeGroupNumber(SgForStmt *pForLoopStmt);

        //collect loop headers to be processed by merge function
        static vector<SgForStmt *> getMergeGroupOuterLoopNodes(SgForStmt *pFirstForStmt);

        //initiate merge from for statement with align groups and merge command
        //collect subsequent for loops with same merge number
        //get align groups
        //no dependencies checks are performed
        //returns next (not affected) statement after last used loop
        static SgStatement *merge(SgForStmt *pForStmtStart);

        //merge split groups for different statements which can be in one loop without degrading parallelization
        //private effect statements can always be merged
        //sameAlignmentGroups are groups of identifiers of arrays which are aligned with each other
        //usages of any arrays from same group can be merged, when indices are equal
        //outerForLoopNodes must match their innerForLoopNodes
        //all Loops must have exactly same headers (and have exactly same depth)
        //return info for each loops'each statements' possible new hosts
        //result.at(loopId).at(stmtId) = vector of possible new hosts
        static vector<vector<vector<int>>> mergeGroups(
                const set<set<string>> &sameAlignmentGroups,
                const vector<SgForStmt *> &outerForLoopNodes,
                const vector<SgForStmt *> &innerForLoopNodes);

        static bool
        checkSameAlignment(const set<set<string>> &groups, SgArrayRefExp *arrayRefA, SgArrayRefExp *arrayRefB);

        static bool vectorEquals(const vector<int> &vA, const vector<int> &vB);

        //non empty with shift if arrayName same, number of indices same, indices in arrayRef not too complex
        //empty if not same
        static vector<int> getAlignShift(const string &varAlignInfo, SgArrayRefExp *arrayRef);

        //if #group contains #arrayRef arrayVariable,
        //  then assuming in #group it had (i,j) indices, and #arrayRef has (f(i), g(j)) indices
        //  return non empty vector of (f(i) - i, g(j) - j)
        //else
        //  return empty vector;
        //a(:) - not supported
        //only f(i) = i +/- const supported now
        static vector<int> isInAlignmentGroup(const set<string> &group, SgArrayRefExp *arrayRef);
    };
}

#endif //LOOP_TRANSFORM_MERGE_HPP
