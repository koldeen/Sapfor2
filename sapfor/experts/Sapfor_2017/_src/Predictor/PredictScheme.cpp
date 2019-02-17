#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <map>
#include <vector>
#include <set>
#include <string>
#include <queue>

#include "dvm.h"
#include "PredictScheme.h"

static void fillParallel(SgExpression *exp, ParallelStats &parStats)
{
    if (exp)
    {
        SgExprListExp *list;
        switch (exp->variant())
        {
        case SHADOW_RENEW_OP:
            list = isSgExprListExp(exp->lhs());
            if (list)            
                parStats.ShadowCount += list->length();
            break;
        case REDUCTION_OP:
            list = isSgExprListExp(exp->lhs());
            if (list)
                parStats.ReductionCount += list->length();
            break;
        case REMOTE_ACCESS_OP:
            list = isSgExprListExp(exp->lhs());
            if (list)
                parStats.RemoteCount += list->length();
            break;
        case ACROSS_OP:
            list = isSgExprListExp(exp->lhs());
            if (list)
                parStats.AcrossCount += list->length();
            break;
        default:
            break;
        }

        fillParallel(exp->rhs(), parStats);
        fillParallel(exp->lhs(), parStats);
    }
}

void processFileToPredict(SgFile *file, PredictorStats &predictorCounts)
{
    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        SgExprListExp *list;
        switch (st->variant())
        {
        case DVM_PARALLEL_ON_DIR:
            predictorCounts.ParallelCount++;
            for (int i = 0; i < 3; ++i)
                fillParallel(st->expr(i), predictorCounts.ParallelStat);
            //
            break;
        case DVM_REDISTRIBUTE_DIR:
        case DVM_REALIGN_DIR:
            predictorCounts.RedistributeCount++;
            break;
        case DVM_REMOTE_ACCESS_DIR:
            for (int i = 0; i < 3; ++i)
            {
                list = isSgExprListExp(st->expr(i));
                if (list)
                    predictorCounts.RemoteCount += list->length();
            }
            break;
        case DVM_INTERVAL_DIR:
        case DVM_ENDINTERVAL_DIR:
        case DVM_EXIT_INTERVAL_DIR:
            predictorCounts.IntervalCount++;
            break;
        default:
            break;
        }
    }
}
