//
// Created by Vladislav Volodkin on 12/21/19.
//

#ifndef SAPFOR_VARUSAGES_H
#define SAPFOR_VARUSAGES_H


#include "dvm.h"
#include <unordered_set>


struct VarUsages {
    std::unordered_set<SgSymbol*> reads;
    std::unordered_set<SgSymbol*> writes;
    bool undefined;

    void insert(VarUsages&);
};


#endif //SAPFOR_VARUSAGES_H
