#pragma once

#include <vector>
#include <map>

#include "AstWrapper.h"

typedef std::pair<std::pair<int, int>, std::pair<int, int>> attrType;

struct ArrayOp
{
    // stored ARRAY[A*x + B] -> (A, B)
    std::vector<std::pair<int, int>> coefficients;
};

struct ArrayInfo
{
    int dimSize;

    std::vector<ArrayOp> writeOps;
    std::vector<ArrayOp> readOps;
    std::vector<bool> unrecReadOps;

    //for remote in parallel
    std::map<ArrayRefExp*, std::pair<int, std::vector<ArrayOp>>> arrayAccess;
    //for remote
    std::map<ArrayRefExp*, std::pair<int, std::vector<unsigned char>>> arrayAccessUnrec;

    ArrayInfo() : dimSize(0) { }
};
