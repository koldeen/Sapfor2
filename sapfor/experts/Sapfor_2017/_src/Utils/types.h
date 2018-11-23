#pragma once

#include <vector>
#include <map>
#include <set>

class ArrayRefExp;

typedef std::pair<std::pair<int, int>, std::pair<int, int>> attrType;

struct ArrayOp
{
    // stored ARRAY[A*x + B] -> (A, B) with weight
    std::map<std::pair<int, int>, double> coefficients;

    ArrayOp() { }
    ArrayOp(const std::pair<std::pair<int, int>, double> &pair) { coefficients[pair.first] = pair.second; }
    ArrayOp(const std::map<std::pair<int, int>, double> &coefficients) : coefficients(coefficients) { }
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
