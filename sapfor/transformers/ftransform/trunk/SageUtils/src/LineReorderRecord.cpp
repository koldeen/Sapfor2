//
// Created by baa on 10.12.17.
//

#include "LineReorderRecord.hpp"

using namespace SageTransform;
using std::map;

void LineReorderRecord::addMove(int originalLineNum, int newLineNum) {
    relativeMoves.insert({originalLineNum, newLineNum});
    if (originalLineNum > maxSourceInt) {
        maxSourceInt = originalLineNum;
    }
}

LineReorderRecord LineReorderRecord::buildReverse() {
    LineReorderRecord result;
    for (auto const &x : relativeMoves) {
        result.addMove(x.second, x.first);
    }
    return result;
}