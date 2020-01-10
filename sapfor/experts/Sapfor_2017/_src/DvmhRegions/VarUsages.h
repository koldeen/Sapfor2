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
    void extend(const VarUsages&);

    void insert_undefined(const TypedSymbol&);
    void insert_read(const TypedSymbol&);
    void insert_write(const TypedSymbol&);

    bool is_undefined() const;
    std::set<SgSymbol*> get_reads(const std::set<VAR_TYPE>) const;
    std::set<SgSymbol*> get_writes(const std::set<VAR_TYPE>) const;
    std::set<SgSymbol*> get_all(const std::set<VAR_TYPE>) const;

    std::set<SgSymbol*> get_reads() const;
    std::set<SgSymbol*> get_writes() const;
    std::set<SgSymbol*> get_all() const;

    static std::set<SgSymbol*> filter(const std::set<TypedSymbol>&, const std::set<VAR_TYPE>);
    void print() const;
};
