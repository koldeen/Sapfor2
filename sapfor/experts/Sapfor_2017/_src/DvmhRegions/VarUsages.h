//
// Created by Vladislav Volodkin on 12/21/19.
//

#ifndef SAPFOR_VARUSAGES_H
#define SAPFOR_VARUSAGES_H


#include "dvm.h"
#include "Exceptions.h"
#include "TypedSymbol.h"
#include <unordered_set>


class VarUsages {
    std::unordered_set<TypedSymbol> reads;
    std::unordered_set<TypedSymbol> writes;
    bool undefined;

public:
    VarUsages() : undefined(false) { };
    void extend(VarUsages);

    void insert_undefined(TypedSymbol);
    void insert_read(TypedSymbol);
    void insert_write(TypedSymbol);

    bool is_undefined();
    std::unordered_set<SgSymbol*> get_reads(VAR_TYPE);  // May raise not implemented
    std::unordered_set<SgSymbol*> get_writes(VAR_TYPE);  // May raise not implemented
    std::unordered_set<SgSymbol*> get_all(VAR_TYPE);

    std::unordered_set<SgSymbol*> get_reads();  // May raise not implemented
    std::unordered_set<SgSymbol*> get_writes();  // May raise not implemented
    std::unordered_set<SgSymbol*> get_all();

    static std::unordered_set<SgSymbol*> filter(const std::unordered_set<TypedSymbol>&, VAR_TYPE);

    void print();
};


#endif //SAPFOR_VARUSAGES_H
