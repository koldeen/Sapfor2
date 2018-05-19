#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "dvm.h"

struct Interval
{
	int calls = 0;
    SgStatement* begin;
    std::vector<SgStatement*> ends;

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
void assignCallsToAllFiles(std::vector<std::string> &filenames);
void insertIntervals();
