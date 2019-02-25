//
// Created by Bulanov on 11.08.17.
//
#ifndef FTRANSFORM_LOOPCOMBINE_H
#define FTRANSFORM_LOOPCOMBINE_H

#include <string>
#include <vector>
#include "user.h"
#include "BaseTransform.hpp"

using std::string;
using std::vector;

namespace SageTransform {
    class LoopCombine: public BaseTransform {
    public:
        static string COMBINE_PREFIX;

        static bool hasComment(SgStatement *sgStatement);

        SgStatement *apply(SgForStmt *sgForStmt);

        void removeComment(SgStatement *sgStatement);

    private:
        bool isSameHeadersCombination(vector<SgForStmt *> &combined) const;

        SgStatement *applySameHeaders(vector<SgForStmt *> &combined);

        bool isContinuousHeadersCombination(vector<SgForStmt *> &combined) const;

        SgStatement *applyContinuousHeaders(vector<SgForStmt *> &combined);

        int getCombineCount(SgStatement *statementWithComment) const;

        vector<SgForStmt *> getCombinedLoops(SgForStmt *startingForStmt, int count) const;
    };
}
#endif //FTRANSFORM_LOOPCOMBINE_H
