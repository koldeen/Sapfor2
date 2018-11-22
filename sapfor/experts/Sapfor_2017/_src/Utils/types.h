#pragma once

#include <vector>
#include <map>

class ArrayRefExp;

typedef std::pair<std::pair<int, int>, std::pair<int, int>> attrType;

struct ArrayOp
{
    // stored ARRAY[A*x + B] -> (A, B)
    std::vector<std::pair<int, int>> coefficients;

    ArrayOp() { }
    ArrayOp(const std::pair<int, int> &pair) { coefficients.push_back(pair); }
    ArrayOp(const std::vector<std::pair<int, int>> &coefficients) : coefficients(coefficients) { }
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
