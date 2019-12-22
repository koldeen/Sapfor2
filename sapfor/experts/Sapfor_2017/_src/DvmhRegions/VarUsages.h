//
// Created by Vladislav Volodkin on 12/21/19.
//

#ifndef SAPFOR_VARUSAGES_H
#define SAPFOR_VARUSAGES_H


#include "dvm.h"
#include "../Utils/SgUtils.h"
#include "Exceptions.h"
#include <unordered_set>


enum VAR_TYPE { VAR_ARR, VAR_DISTR_ARR, VAR_SCALAR, VAR_ANY };


class VarUsages {
    std::unordered_set<SgSymbol*> reads;
    std::unordered_set<SgSymbol*> writes;
    bool undefined;

public:
    VarUsages() : undefined(false) { };
    void extend(VarUsages);

    void insert_undefined(SgSymbol* s);
    void insert_read(SgSymbol*);
    void insert_write(SgSymbol*);

    bool is_undefined();
    std::unordered_set<SgSymbol*> get_reads(VAR_TYPE);  // May raise not implemented
    std::unordered_set<SgSymbol*> get_writes(VAR_TYPE);  // May raise not implemented
    std::unordered_set<SgSymbol*> get_all(VAR_TYPE);

    std::unordered_set<SgSymbol*> get_reads();  // May raise not implemented
    std::unordered_set<SgSymbol*> get_writes();  // May raise not implemented
    std::unordered_set<SgSymbol*> get_all();

    static bool check_var_type(SgSymbol* s, VAR_TYPE var_type);
    static std::unordered_set<SgSymbol*> filter(std::unordered_set<SgSymbol*>&, VAR_TYPE);

    void print();
};


#endif //SAPFOR_VARUSAGES_H
