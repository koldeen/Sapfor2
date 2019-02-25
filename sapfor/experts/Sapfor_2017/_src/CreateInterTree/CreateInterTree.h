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
    long long calls_count = 0;
    bool ifInclude = true;
    SgStatement *begin;
    std::pair<int, std::string> lineFile;
    SpfInterval *parent = NULL;

    std::vector<SgStatement*> ends;
    std::vector<int> exit_levels;        
    std::vector<SpfInterval*> nested;

    //from statistic after execution
    int exec_count = 0;
    double exec_time = 0;
    std::vector<double> predictedTimes;
    std::vector<double> predictedRemoteTimes;

    int getBestTimeIdx()
    {
        int idx = -1;
        double best = 0;
        for (int z = 0; z < predictedTimes.size(); ++z)
        {
            if (idx == -1 || best > predictedTimes[z])
            {
                best = predictedTimes[z];
                idx = z;
            }
        }

        return idx;
    }
};

struct FileProfile
{
    std::map<int, long long> profile;
};

void saveIntervals(const std::string &fileName, std::map<std::string, std::vector<SpfInterval*>> &intervals);
void createInterTree(SgFile*, std::vector<SpfInterval*>&, bool);
void assignCallsToFile(const std::string&, std::vector<SpfInterval*>&);
void removeNodes(long long, std::vector<SpfInterval*>&, std::vector<std::string>&);
void insertIntervals(SgFile*, const std::vector<SpfInterval*>&);
void createMapOfinterval(std::map<int, SpfInterval*> &mapIntervals, const std::vector<SpfInterval*> &intervals);
void initTimeForIntervalTree(const int numOfTopologies, std::vector<SpfInterval*> &intervals);
void aggregatePredictedTimes(std::vector<SpfInterval*> &itervals);
SpfInterval* getMainInterval(SgProject *project, const std::map<std::string, std::vector<SpfInterval*>> &intervals);
void uniteIntervalsBetweenProcCalls(std::map<std::string, std::vector<SpfInterval*>> &intervals, const std::map<std::string, std::vector<FuncInfo*>> &allFuncInfo);
SpfInterval* findNearestUp(const std::map<SgStatement*, SpfInterval*> &intervals, SgStatement *st);
SpfInterval* findNearestDown(const std::map<SgStatement*, SpfInterval*> &intervals, SgStatement *st);