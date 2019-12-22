//
// Created by Vladislav Volodkin on 12/21/19.
//

#include "VarUsages.h"


void VarUsages::extend(VarUsages to_insert)
{
    undefined |= to_insert.undefined;

    reads.insert(to_insert.reads.begin(), to_insert.reads.end());
    writes.insert(to_insert.writes.begin(), to_insert.writes.end());
}

std::unordered_set<SgSymbol*> VarUsages::get_reads(VAR_TYPE var_type)  // May raise not implemented
{
    if (undefined)
        throw NotImplemented();

    return filter(reads, var_type);
}

std::unordered_set<SgSymbol*> VarUsages::get_writes(VAR_TYPE var_type)  // May raise not implemented
{
    if (undefined)
        throw NotImplemented();

    return filter(writes, var_type);
}

std::unordered_set<SgSymbol*> VarUsages::get_all(VAR_TYPE var_type)
{
    auto all_usages = std::unordered_set<SgSymbol*>();
    all_usages.insert(reads.begin(), reads.end());
    all_usages.insert(writes.begin(), writes.end());

    return filter(all_usages, var_type);
}

std::unordered_set<SgSymbol*> VarUsages::get_reads()  // May raise not implemented
{
    return get_reads(VAR_ANY);
}

std::unordered_set<SgSymbol*> VarUsages::get_writes()  // May raise not implemented
{
    return get_writes(VAR_ANY);
}

std::unordered_set<SgSymbol*> VarUsages::get_all()
{
    return get_all(VAR_ANY);
}

bool VarUsages::check_var_type(SgSymbol* s, VAR_TYPE var_type)
{
    switch (var_type)
    {
        case VAR_ANY:
            return true;
        case VAR_ARR:
            return s->variant() == ARRAY_REF;
        case VAR_DISTR_ARR:
            if (s->variant() != ARRAY_REF)
                return false;

            return !getArrayFromDeclarated(declaratedInStmt(s), s->identifier())->GetNonDistributeFlag();
        case VAR_SCALAR:
            return s->variant() == VAR_REF;
    }
}

std::unordered_set<SgSymbol*> VarUsages::filter(std::unordered_set<SgSymbol*> &symbols, VAR_TYPE var_type)
{
    auto filtered = std::unordered_set<SgSymbol*>();

    for (auto& s : symbols)
        if (check_var_type(s, var_type))
            filtered.insert(s);

    return filtered;
}

void VarUsages::insert_undefined(SgSymbol* s)
{
    undefined = true;

    reads.insert(s);
    writes.insert(s);
}

void VarUsages::insert_read(SgSymbol* s)
{
    reads.insert(s);
}

void VarUsages::insert_write(SgSymbol* s)
{
    writes.insert(s);
}

void VarUsages::print()
{
    printf("reads: ");
    if (undefined)
        printf("not_defined");
    else
    {
        for (auto& s : reads)
            printf("%s ", s->identifier());
    }
    printf("\n");

    printf("writes: ");
    if (undefined)
        printf("not_defined");
    else
    {
        for (auto& s : writes)
            printf("%s ", s->identifier());
    }
    printf("\n");

    printf("all: ");
    for (auto& s : get_all(VAR_ANY))
        printf("%s ", s->identifier());
    printf("\n");

    printf("***\n");
}

bool VarUsages::is_undefined()
{
    return undefined;
}
