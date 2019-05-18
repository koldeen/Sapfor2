#pragma once

#include "../Utils/utils.h"

#include "./gcov_info.h"
#include "../CreateInterTree/CreateInterTree.h"
#include "../GraphCall/graph_calls.h"

#include <map>
#include <vector>

struct SpfRegion {
    int id;

    float time;
    SgStatement *start;
    SgStatement *end;

    SpfRegion(int id_, int time_, SgStatement *start_, SgStatement *end_) :
        id(id_), time(time_), start(start_), end(end_) {}

    SpfRegion& operator+=(SpfRegion rg)
    {
        if (this != &rg)
        {
            end = rg.end;
            time += rg.time;
        }
        return *this;
    }
};

SpfInterval* findMainInterval(std::vector<SpfInterval*> &fileIntervals);
float performTime(SgFile *file, SgStatement *src, std::map<int, Gcov_info> &gCovInfo, std::map<std::string, std::vector<FuncInfo*>> &funcInfo, int rec_level = 0);
void createParallelRegions(SgFile *file, std::vector<SpfInterval*>&fileIntervals, std::map<int, Gcov_info> &gCovInfo, std::map<std::string, std::vector<FuncInfo*>> &funcInfo);