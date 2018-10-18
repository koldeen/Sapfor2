#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "dvm.h"

struct Interval
{
    int tag = 0;
    int calls = 0;
    bool ifInclude = true;
    SgStatement* begin;
    Interval* parent = NULL;

    std::vector<SgStatement*> ends;
    std::vector<int> exit_levels;

    std::vector<Interval*> includes;
};

struct FileProfile
{
    std::map<int, int> profile;
};

void createInterTree(SgFile*, std::vector<Interval*>&);
void printTree(Interval* inter);
void assignCallsToAllFiles(std::vector<std::string> filenames);
void removeNodes(int threshold, std::map<std::string, std::vector<Interval*>> &allIntervals);
void insertIntervals(SgFile*, const std::vector<Interval*>&);
