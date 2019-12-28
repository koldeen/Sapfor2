// Created by Vladislav Volodkin on 12/20/19.

#pragma once

#include "dvm.h"
#include "TypedSymbol.h"
#include <set>


class VarUsages 
{
    std::set<TypedSymbol> reads;
    std::set<TypedSymbol> writes;
    bool undefined;

public:
    VarUsages() : undefined(false) { }
    void extend(VarUsages);

    void insert_undefined(const TypedSymbol&);
    void insert_read(const TypedSymbol&);
    void insert_write(const TypedSymbol&);

    bool is_undefined();
    std::set<SgSymbol*> get_reads(VAR_TYPE);
    std::set<SgSymbol*> get_writes(VAR_TYPE);
    std::set<SgSymbol*> get_all(VAR_TYPE);

    std::set<SgSymbol*> get_reads();
    std::set<SgSymbol*> get_writes();
    std::set<SgSymbol*> get_all();

    static std::set<SgSymbol*> filter(const std::set<TypedSymbol>&, VAR_TYPE);
    void print();
};
