//
// Created by Vladislav Volodkin on 12/21/19.
//
#include "leak_detector.h"
#include "VarUsages.h"

using namespace std;


void VarUsages::extend(VarUsages to_insert)
{
    undefined |= to_insert.undefined;

    reads.insert(to_insert.reads.begin(), to_insert.reads.end());
    writes.insert(to_insert.writes.begin(), to_insert.writes.end());
}

set<SgSymbol*> VarUsages::get_reads(VAR_TYPE var_type) 
{
    if (undefined)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return filter(reads, var_type);
}

set<SgSymbol*> VarUsages::get_writes(VAR_TYPE var_type) 
{
    if (undefined)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return filter(writes, var_type);
}

set<SgSymbol*> VarUsages::get_all(VAR_TYPE var_type)
{
    auto all_usages = set<TypedSymbol>();
    all_usages.insert(reads.begin(), reads.end());
    all_usages.insert(writes.begin(), writes.end());

    return filter(all_usages, var_type);
}

set<SgSymbol*> VarUsages::get_reads() { return get_reads(VAR_ANY); }
set<SgSymbol*> VarUsages::get_writes() { return get_writes(VAR_ANY); }
set<SgSymbol*> VarUsages::get_all() { return get_all(VAR_ANY); }

set<SgSymbol*> VarUsages::filter(const set<TypedSymbol> &symbols, VAR_TYPE var_type)
{
    auto filtered = set<SgSymbol*>();
    for (auto& s : symbols)
        if (var_type == VAR_ANY || s.type == var_type)
            filtered.insert(s.orig);
    return filtered;
}

void VarUsages::insert_undefined(const TypedSymbol& s)
{
    undefined = true;

    reads.insert(s);
    writes.insert(s);
}

void VarUsages::insert_read(const TypedSymbol& s) { reads.insert(s); }
void VarUsages::insert_write(const TypedSymbol& s) { writes.insert(s); }

void VarUsages::print()
{
    printf("reads: ");
    if (undefined)
        printf("not_defined");
    else
    {
        for (auto& s : reads)
            printf("%s ", s.orig->identifier());
    }
    printf("\n");

    printf("writes: ");
    if (undefined)
        printf("not_defined");
    else
    {
        for (auto& s : writes)
            printf("%s ", s.orig->identifier());
    }
    printf("\n");

    printf("all: ");
    for (auto& s : get_all(VAR_ANY))
        printf("%s ", s->identifier());
    printf("\n");

    printf("***\n");
}

bool VarUsages::is_undefined() { return undefined; }
