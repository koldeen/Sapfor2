//
// Created by Vladislav Volodkin on 12/17/19.
//

#include "ReadWriteAnylyser.h"

using namespace std;

ReadWriteAnylyser::ReadWriteAnylyser(SgStatement* anylyzedSt) : anylyzedSts(vector<SgStatement*>(1, anylyzedSt))
{
    init();
}

ReadWriteAnylyser::ReadWriteAnylyser(std::vector<SgStatement*> anylyzedSts) : anylyzedSts(anylyzedSts)
{
    init();
}

void ReadWriteAnylyser::init()
{
    try {
        for (auto &st : anylyzedSts)
            processStatement(st);

        rw_undefined = false;
    } catch (NotImplemented &e) {
        rw_undefined = true;
    }
}

rw_tuple ReadWriteAnylyser::processStatement(SgStatement* st)
{
    if (st->variant() == ASSIGN_STAT)
        return processAssignment(st);
    else if (st->variant() == LOOP_NODE)
        return processLoop(st);
    else
        throw NotImplemented();
}

rw_tuple ReadWriteAnylyser::processAssignment(SgStatement* st)
{
    return rw_tuple(findVarsInExpr(st->expr(0)), findVarsInExpr(st->expr(1)));
}

rw_tuple ReadWriteAnylyser::processLoop(SgStatement* loop)
{
    auto loop_reads = std::unordered_set<SgSymbol*>();
    auto loop_writes = std::unordered_set<SgSymbol*>();

    SgStatement* runner = loop;
    while (runner != loop->lastNodeOfStmt())
    {
        auto reads = std::unordered_set<SgSymbol*>();
        auto writes = std::unordered_set<SgSymbol*>();

        tie(reads, writes) = processStatement(runner);

        loop_reads.insert(reads.begin(), reads.end());
        loop_writes.insert(writes.begin(), writes.end());
    }

    return rw_tuple(loop_reads, loop_writes);
}

unordered_set<SgSymbol*> ReadWriteAnylyser::findVarsInExpr(SgExpression* expr)
{
    return unordered_set<SgSymbol*>();
}

unordered_set<SgSymbol*> ReadWriteAnylyser::get_modified()  // may raise NotImplemented
{
    if (rw_undefined)
        throw NotImplemented();

    return reads;
}

unordered_set<SgSymbol*> ReadWriteAnylyser::get_read()  // may raise NotImplemented
{
    if (rw_undefined)
        throw NotImplemented();

    return writes;
}

void ReadWriteAnylyser::update(ReadWriteAnylyser &to_add)
{
    rw_undefined |= to_add.rw_undefined;
    if (rw_undefined)
        return;

    anylyzedSts.insert(anylyzedSts.end(), to_add.anylyzedSts.begin(), to_add.anylyzedSts.end());
    reads.insert(to_add.get_read().begin(), to_add.get_read().end());
    writes.insert(to_add.get_modified().begin(), to_add.get_modified().end());
}