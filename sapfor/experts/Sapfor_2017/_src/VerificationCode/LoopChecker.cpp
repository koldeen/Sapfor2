#include "../leak_detector.h"

#include <cstdio>
#include <vector>

#include "dvm.h"
#include "verifications.h"
#include "../utils.h"
#include "../SgUtils.h"

using std::vector;

void EndDoLoopChecker(SgFile *file, vector<int> &errors)
{
    int funcNum = file->numberOfFunctions();
    
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
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

void DvmDirectiveChecker(SgFile *file, vector<int> &errors)
{
    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }
            
            if (isDVM_stat(st) && (st->variant() != DVM_INTERVAL_DIR || st->variant() != DVM_ENDINTERVAL_DIR))
                errors.push_back(st->lineNumber());

            //FOR DEBUGING DVM DIRS
            /*if (st->variant() == DVM_PARALLEL_ON_DIR || st->variant() == DVM_REDISTRIBUTE_DIR)
            {
                st->unparsestdout();
                for (int k = 0; k < 3; ++k)
                {
                    if (st->expr(k))
                    {
                        printf("EXP %d:\n", k);
                        recExpressionPrint(st->expr(k));
                    }
                }
            }*/

            st = st->lexNext();
        }
    }
}