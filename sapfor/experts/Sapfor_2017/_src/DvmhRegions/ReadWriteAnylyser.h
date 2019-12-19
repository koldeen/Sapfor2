//
// Created by Vladislav Volodkin on 12/17/19.
//

#ifndef SAPFOR_READWRITEANYLYSER_H
#define SAPFOR_READWRITEANYLYSER_H
#include "dvm.h"
#include "DvmhRegions/Exceptions.h"

#include <unordered_set>
#include <tuple>
#include <queue>


typedef std::tuple<std::unordered_set<SgSymbol*>, std::unordered_set<SgSymbol*>> rw_tuple; // (reads, writes)

class ReadWriteAnylyser
{
    std::unordered_set<SgSymbol*> reads;
    std::unordered_set<SgSymbol*> writes;

    void init();

    rw_tuple processAssignment(SgStatement* st);
    rw_tuple processLoop(SgStatement* st);
    rw_tuple processBlock(SgStatement* start, SgStatement *end);
public:
    std::vector<SgStatement*> anylyzedSts;  // may be: loops or stand-alone statements
    bool rw_undefined;  // not all constructions are implemented => if met such in statement, set this flag

    ReadWriteAnylyser() {};
    explicit ReadWriteAnylyser(SgStatement* anylyzedSt);
    explicit ReadWriteAnylyser(std::vector<SgStatement*> anylyzedSt);
    void update(ReadWriteAnylyser &to_adds);

    std::unordered_set<SgSymbol*> get_modified();  // may raise NotImplemented
    std::unordered_set<SgSymbol*> get_read();  // may raise NotImplemented

    static std::unordered_set<SgSymbol*> findVarsInExpr(SgExpression* expr);
    rw_tuple processStatement(SgStatement* st);  // may raise NotImplemented

    void print();
};


#endif //SAPFOR_READWRITEANYLYSER_H
