#pragma once

#include <vector>
#include <map>
#include <set>

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

static inline std::set<std::pair<int, int>> uniqFromVector(const std::vector<std::pair<int, int>> &in)
{
    return std::set<std::pair<int, int>>(in.begin(), in.end());
}

static inline void uniqFromAllVector(std::vector<ArrayOp> &in)
{
    for (int z = 0; z < in.size(); ++z)
    {
        if (in[z].coefficients.size())
        {
            const std::set<std::pair<int, int>> uniq = uniqFromVector(in[z].coefficients);
            in[z].coefficients.clear();
            for (auto &elem : uniq)
                in[z].coefficients.push_back(elem);
        }
    }
}

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

    void createUniqCoefs()
    {
        uniqFromAllVector(writeOps);
        uniqFromAllVector(readOps);
    }
};
