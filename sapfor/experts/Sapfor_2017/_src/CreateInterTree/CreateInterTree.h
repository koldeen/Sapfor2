#pragma once

#include <iostream>
#include <vector>

#include "dvm.h"

struct Interval
{
    SgStatement* begin;
    std::vector<SgStatement*> ends;

    std::vector<Interval*> includes;
};

void createInterTree(SgFile*);
void insertIntervals();
void printTree(Interval*, int depth);