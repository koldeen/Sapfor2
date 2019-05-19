#pragma once

#include "../Utils/utils.h"

#include "./gcov_info.h"
#include "../CreateInterTree/CreateInterTree.h"
#include "../GraphCall/graph_calls.h"

#include <map>
#include <vector>

struct SpfRegion 
{
    int id;

    double time;
    SgStatement *start;
    SgStatement *end;

    SpfRegion(int id_, int time_, SgStatement *start_, SgStatement *end_) : 
              id(id_), time(time_), start(start_), end(end_) {}

    SpfRegion& operator+=(const SpfRegion &rg) 
    {
        if (this != &rg)
        {
            end = rg.end;
            time += rg.time;
        }
        return *this;
    }
};

void createParallelRegions(SgProject *project, SpfInterval *mainInterval, const std::map<std::string, std::map<int, Gcov_info>> &gCovInfo, const std::map<std::string, std::vector<FuncInfo*>> &funcInfo);