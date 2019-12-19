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
        {
            auto st_reads = std::unordered_set<SgSymbol*>();
            auto st_writes = std::unordered_set<SgSymbol*>();
            tie(st_reads,  st_writes) = processStatement(st);

            reads.insert(st_reads.begin(), st_reads.end());
            writes.insert(st_writes.begin(), st_writes.end());
        }


        rw_undefined = false;
    } catch (NotImplemented &e) {
        rw_undefined = true;
    }
}

rw_tuple ReadWriteAnylyser::processStatement(SgStatement* st)
{
    if (st->variant() == ASSIGN_STAT)
        return processAssignment(st);
    else if (st->variant() == FOR_NODE)
        return processLoop(st);
    else
        throw NotImplemented();
}

rw_tuple ReadWriteAnylyser::processAssignment(SgStatement* st)
{
    return rw_tuple(findVarsInExpr(st->expr(1)), findVarsInExpr(st->expr(0)));
}

rw_tuple ReadWriteAnylyser::processLoop(SgStatement* loop)
{
    auto loop_reads = std::unordered_set<SgSymbol*>();
    auto loop_writes = std::unordered_set<SgSymbol*>();

    // TODO: process loop header

    // process loop body
    auto reads = std::unordered_set<SgSymbol*>();
    auto writes = std::unordered_set<SgSymbol*>();

    tie(reads, writes) = processBlock(loop->lexNext(), loop->lastNodeOfStmt());

    loop_reads.insert(reads.begin(), reads.end());
    loop_writes.insert(writes.begin(), writes.end());

    return rw_tuple(loop_reads, loop_writes);
}

rw_tuple ReadWriteAnylyser::processBlock(SgStatement* start, SgStatement *end)
{
    auto loop_reads = std::unordered_set<SgSymbol*>();
    auto loop_writes = std::unordered_set<SgSymbol*>();

    SgStatement* runner = start;
    while (runner != end)
    {
        auto reads = std::unordered_set<SgSymbol*>();
        auto writes = std::unordered_set<SgSymbol*>();

        tie(reads, writes) = processStatement(runner);

        loop_reads.insert(reads.begin(), reads.end());
        loop_writes.insert(writes.begin(), writes.end());

        runner = runner->lexNext();
    }

    return rw_tuple(loop_reads, loop_writes);
}

unordered_set<SgSymbol*> ReadWriteAnylyser::findVarsInExpr(SgExpression* exp)
{
    auto vars = unordered_set<SgSymbol*>();

    queue<SgExpression*> buf;
    buf.push(exp);

    while (!buf.empty())
    {
        auto cur = buf.front();
        buf.pop();

        if (!cur)
            continue;

        auto e_type = cur->variant();

        if (e_type == VAR_REF || e_type == ARRAY_REF || e_type == RECORD_REF)
        {
            SgSymbol *s = OriginalSymbol(exp->symbol());  // TODO: exp->symbol == NULL -- WHY?
            vars.insert(s);
        }

        buf.push(cur->lhs());
        buf.push(cur->rhs());
    }

    return vars;
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

void ReadWriteAnylyser::print()
{
    printf("reads: ");
    for (auto& s : reads)
        printf("%s ", s->identifier());
    printf("\n");

    printf("writes: ");
    for (auto& s : writes)
        printf("%s ", s->identifier());
    printf("\n");

    printf("not ok: %d\n", rw_undefined);
}