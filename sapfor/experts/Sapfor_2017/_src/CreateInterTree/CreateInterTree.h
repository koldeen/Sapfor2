#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "dvm.h"

#include "../GraphLoop/graph_loops_func.h"

struct Interval
{
    int tag = 0;
    long int calls = 0;
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

void createInterTree(SgFile*, std::vector<Interval*>&, bool, bool);
void printTree(Interval* inter);
void assignCallsToFile(const std::string&, std::vector<Interval*>&);
void removeNodes(int, std::vector<Interval*>&, std::vector<std::string>&);
void insertIntervals(SgFile*, const std::vector<Interval*>&);
