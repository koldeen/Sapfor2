//
// Created by baa on 10.12.17.
//

#include "LineReorderRecord.hpp"

using namespace SageTransform;
using std::map;

void LineReorderRecord::addMove(int originalLineNum, int newLineNum) {
    relativeMoves.insert({originalLineNum, newLineNum});
}

map<int, int> LineReorderRecord::buildReverse() {
    map<int, int> result;
    for (auto const& x : relativeMoves) {
        result.insert({x.second, x.first});
    }
    return result;
}