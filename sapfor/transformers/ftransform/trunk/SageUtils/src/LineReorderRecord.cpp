//
// Created by baa on 10.12.17.
//

#include "LineReorderRecord.hpp"
#include "MapUtils.hpp"

using namespace SageTransform;
using std::map;
using MapUtils::getOrDefault;

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

LineReorderRecord LineReorderRecord::combine(LineReorderRecord& lrr) {
    LineReorderRecord result;
    for (auto const &x : relativeMoves) {
        result.addMove(x.first, getOrDefault(lrr.relativeMoves, x.second, x.second));
    }
    //if we have less numbers then given record
    for (int i = this->maxSourceInt + 1; i <= lrr.maxSourceInt; i++) {
        result.addMove(i, getOrDefault(lrr.relativeMoves, i, i));
    }
    return result;
}