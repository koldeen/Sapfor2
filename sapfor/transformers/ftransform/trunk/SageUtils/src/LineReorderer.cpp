//
// Created by baa on 10.12.17.
//

#include "LineReorderer.hpp"

using namespace SageTransform;
using std::map;

void LineReorderer::apply(SgStatement *baseStatement, LineReorderRecord *lrr) {
    map<int, int> reverse = lrr->buildReverse();
    //todo impl
    //todo tests
}
