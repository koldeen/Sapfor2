//
// Created by baa on 10.12.17.
//

#include "LineReorderer.hpp"
#include <vector>
#include <SageTransformException.hpp>
#include <Log.hpp>

using namespace SageTransform;
using std::map;
using std::vector;

int getByValue(const map<int, int> &theMap, int value, int defaultValue) {
    for (auto &x : theMap) {
        if (x.second == value) {
            return value;
        }
    }
    return defaultValue;
}

void shiftKeyToValue(map<int, int> *theMap, int keyToShift) {
    int newKey = theMap->at(keyToShift);
    int shiftFrom = newKey + 1;
    int shiftTo = keyToShift - 1;
    if (shiftFrom <= shiftTo) {
        for (int i = shiftTo; i >= shiftFrom; i--) {
            theMap->at(i + 1) = theMap->at(i);
        }
    }
    theMap->at(newKey) = newKey;
}

void swapWithLexPrev(SgStatement *st) {
    st->insertStmtAfter(*(st->lexPrev()));
}


void LineReorderer::apply(SgStatement *baseStatement, LineReorderRecord &record) {
    auto moves = *record.getMoves();
    int startLineNum = 1;
    int maxLineNum = record.getMaxLineNumber();

    map<SgStatement *, int> statements;
    statements.insert({baseStatement, 0});
    SgStatement *stmt = baseStatement;
    for (int i = startLineNum; i <= maxLineNum; ++i) {
        stmt = stmt->lexNext();
        statements.insert({stmt, i});
    }

    int current, backShiftsToDo;
    for (int placeTo = startLineNum; placeTo <= maxLineNum; placeTo++) {
        current = getByValue(moves, placeTo, 0xFFFF);
        if (current == 0xFFFF) {
            throw SageTransformException("Illegal State in reorderer");
        }
        stmt = baseStatement;
        for (int i = 0; i < current; ++i) {
            stmt = stmt->lexNext();
        }
        backShiftsToDo = current - placeTo;
        Log::debug("moving back " + string(stmt->unparse()) + " to position " + std::to_string(placeTo));
        while (backShiftsToDo > 0) {
            //move statements backward
            swapWithLexPrev(stmt);
            backShiftsToDo--;
        }
    }
}
