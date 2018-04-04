#include "../leak_detector.h"

#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "dvm.h"
#include "verifications.h"
#include "../utils.h"
#include "../SgUtils.h"

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::make_pair;

void EndDoLoopChecker(SgFile *file, vector<int> &errors)
{
    int funcNum = file->numberOfFunctions();
    
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

            if (st->variant() == FOR_NODE)
            {
                SgForStmt *currSt = (SgForStmt*)st;
                if (currSt->isEnddoLoop() == 0)
                    errors.push_back(st->lineNumber());
            }
            st = st->lexNext();
        }
    }
}

void DvmDirectiveChecker(SgFile *file, map<string, vector<int>> &errors)
{
    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        for ( ; st != lastNode; st = st->lexNext())
        {
            currProcessing.second = st;
            
            if (isDVM_stat(st) && (st->variant() != DVM_INTERVAL_DIR && st->variant() != DVM_ENDINTERVAL_DIR))
                errors[st->fileName()].push_back(st->lineNumber());
        }
    }
}