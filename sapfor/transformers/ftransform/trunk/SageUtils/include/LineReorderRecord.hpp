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
    public: //methods
        void addMove(int originalLineNum, int newLineNum);
        /**
         * Build map with info how to reverse its reorder record.
         * @return map<new line number, original line number> relative to some base
         */
        std::map<int, int> buildReverse();
    private: //methods
    };
}

#endif //FTRANSFORM_LINEREORDERRECORD_HPP
