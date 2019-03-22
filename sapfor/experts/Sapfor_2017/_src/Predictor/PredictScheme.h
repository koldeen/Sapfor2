#pragma once
#include <vector>
#include "dvm.h"

class ParallelStats
{
public:
    ParallelStats()
    {
        RemoteCount = ShadowCount = ReductionCount = AcrossCount = 0;
    }
     
    int RemoteCount;
    int ShadowCount;
    int ReductionCount;
    int AcrossCount;
};

class PredictorStats
{
public:
    PredictorStats()
    {
        ParallelCount = RemoteCount = RedistributeCount = IntervalCount = 0;
    }
     
    ParallelStats ParallelStat;
    int ParallelCount;
    int RemoteCount;
    int RedistributeCount;
    int IntervalCount;

    std::string to_string()
    {
        std::string res = "";
        res += std::to_string(ParallelCount) + "|";
        res += std::to_string(RemoteCount) + "|";
        res += std::to_string(RedistributeCount) + "|";
        res += std::to_string(IntervalCount) + "|";

        res += std::to_string(ParallelStat.RemoteCount) + "|";
        res += std::to_string(ParallelStat.ShadowCount) + "|";
        res += std::to_string(ParallelStat.ReductionCount) + "|";
        res += std::to_string(ParallelStat.AcrossCount);

        return res;
    }
};

void processFileToPredict(SgFile *file, PredictorStats &predictorCounts);