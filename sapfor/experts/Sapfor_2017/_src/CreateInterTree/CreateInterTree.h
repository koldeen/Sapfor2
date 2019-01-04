#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "dvm.h"

#include "../GraphLoop/graph_loops_func.h"

struct SpfInterval
{
    int tag = 0;
    long long calls = 0;
    bool ifInclude = true;
    SgStatement *begin;
    SpfInterval *parent = NULL;

    std::vector<SgStatement*> ends;
    std::vector<int> exit_levels;        
    std::vector<SpfInterval*> nested;

    //from statistic after execution
    int exec_count = 0;
    double exec_time = 0;
};

struct FileProfile
{
    std::map<int, long long> profile;
};

void saveIntervals(SgFile*, std::vector<SpfInterval*>&);
void createInterTree(SgFile*, std::vector<SpfInterval*>&, bool);
void assignCallsToFile(const std::string&, std::vector<SpfInterval*>&);
void removeNodes(long long, std::vector<SpfInterval*>&, std::vector<std::string>&);
void insertIntervals(SgFile*, const std::vector<SpfInterval*>&);
void createMapOfinterval(std::map<int, SpfInterval*> &mapIntervals, const std::vector<SpfInterval*> &intervals);
