#include "../Utils/leak_detector.h"

#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "dvm.h"
#include "verifications.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
#include "../Utils/errors.h"

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::make_pair;

bool EndDoLoopChecker(SgFile *file, vector<Messages> &currMessages)
{
    int funcNum = file->numberOfFunctions();
    bool checkOK = true;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
            currProcessing.second = st;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            if (st->variant() == FOR_NODE)
            {
                SgForStmt *currSt = (SgForStmt*)st;
                if (currSt->isEnddoLoop() == 0)
                {
                    __spf_print(1, "  ERROR: Loop on line %d does not have END DO\n", st->lineNumber());
                    currMessages.push_back(Messages(ERROR, st->lineNumber(), "This loop does not have END DO format", 1018));
                    checkOK = false;
                }
            }
            st = st->lexNext();
        }
    }
    return checkOK;
}
 
bool DvmDirectiveChecker(SgFile *file, map<string, vector<int>> &errors, const int keepDvmDirectives, const int ignoreDvmChecker)
{
    if (keepDvmDirectives != 0)
        return true;

    int funcNum = file->numberOfFunctions();
    bool checkOK = true;
    __spf_print(1, "  ignoreDvmChecker = %d\n", ignoreDvmChecker);

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        for ( ; st != lastNode; st = st->lexNext())
        {
            currProcessing.second = st;
            if (st->variant() == CONTAINS_STMT)
                break;

            if (isDVM_stat(st) && (st->variant() != DVM_INTERVAL_DIR && st->variant() != DVM_ENDINTERVAL_DIR))
                errors[st->fileName()].push_back(st->lineNumber());
        }
    }

    return checkOK;
}