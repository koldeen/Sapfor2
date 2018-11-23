//
// Created by baa on 10.12.17.
//

#include "LineReorderer.hpp"
#include "SageTransformException.hpp"
#include "SageTransformUtils.hpp"
#include "Log.hpp"
#include "StringUtils.hpp"

using namespace SageTransform;
using std::map;
using std::vector;

int getKeyByValue(const map<int, int> &theMap, int value, int defaultValue) {
    for (auto &x : theMap) {
        if (x.second == value) {
            return x.first;
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
    //build required sequence starting from required line #1, then line #2, then line #3, etc.
    for (int placeTo = startLineNum; placeTo <= maxLineNum; placeTo++) {
        current = getKeyByValue(moves, placeTo, 0xFFFF);
        if (current == 0xFFFF) {
            throw SageTransformException("Illegal State in LineReorderer, no statement for step " + std::to_string(placeTo));
        }

        if (placeTo == current) {
            Log::debug("Actual move: " + std::to_string(current) + " to " + std::to_string(placeTo) + " - nothing to do");
            continue;
        } else {
            Log::debug("Actual move: " + std::to_string(current) + " to " + std::to_string(placeTo));
        }

        stmt = baseStatement;
        for (int i = 0; i < current; ++i) {
            stmt = stmt->lexNext();
        }
        backShiftsToDo = current - placeTo;
        string unparsed = (stmt->unparse());
        Log::debug("moving back '" + StringUtils::trim(unparsed) + "' to position " + std::to_string(placeTo) + " with " + std::to_string(backShiftsToDo) + " moves");
        while (backShiftsToDo > 0) {
            //move statements backward
            stmt = SageTransformUtils::swapWithLexPrev(stmt);
            backShiftsToDo--;
        }

        for (int i = current; i >= placeTo + 1; i--) {
            //original positions of lines are shifted as we moved all lines in range [placeTo, current - 1] down(+1) for one line
            //and current line to placeTo (-some lines)
            int value = moves.at(i - 1);
            moves.erase(i);
            moves.insert({i, value});
        }
        moves.erase(placeTo);
        moves.insert({placeTo, placeTo});
    }
}
