//
// Created by baa on 10.12.17.
//

#ifndef FTRANSFORM_LINEREORDERRECORD_HPP
#define FTRANSFORM_LINEREORDERRECORD_HPP

#include <map>

namespace SageTransform {
    class LineReorderRecord {
    private: //fields
        //first int is original line number, second is new line number relative to some base
        std::map<int, int> relativeMoves;
        int maxSourceInt = 0;

        //todo impl continuity checks
    public: //methods
        /**
         * Store new source code line movement
         * @param originalLineNum relative to some position
         * @param newLineNum relative to same position
         */
        void addMove(int originalLineNum, int newLineNum);

        /**
         * Build a reverse LineReorderRecord that undos current one.
         * @return LineReorderRecord that reverts this
         */
        LineReorderRecord buildReverse();

        /**
         * Build a single combination Reorder record that behaves as (this, lrr) applied one after another.
         * @param lrr next reorder
         * @return the resulting reorder
         */
        LineReorderRecord combine(LineReorderRecord& lrr);

        /**
         * Get stored line movements.
         * @return map<original line position, new line position> relative to some base
         */
        const std::map<int, int> *getMoves() { return &relativeMoves; };

        int getMaxLineNumber() { return maxSourceInt; }

    private: //methods
    };
}

#endif //FTRANSFORM_LINEREORDERRECORD_HPP
