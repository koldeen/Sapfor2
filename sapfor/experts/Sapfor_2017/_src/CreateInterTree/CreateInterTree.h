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

struct FileIntervals
{
    std::vector<Interval*> intervals;
};

void createInterTree(SgFile*);
void printTree(Interval* inter, int depth);
void assignCallsToAllFiles(std::vector<std::string> filenames);
void removeNodes(int threshold);
void insertIntervals();
