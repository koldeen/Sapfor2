//
// Created by Vladislav Volodkin on 12/17/19.
//

#include "ReadWriteAnylyser.h"

using namespace std;

/* DELETE ME */
//static string getValue(SgExpression *exp)
//{
//    if (exp == NULL)
//        return "";
//
//    string ret = "";
//    if (exp->symbol())
//    {
//        if (exp->symbol()->identifier())
//            ret = "(" + string(exp->symbol()->identifier()) + ")";
//    }
//    else if (exp->variant() == INT_VAL)
//    {
//        char buf[256];
//        sprintf(buf, "%d", exp->valueInteger());
//        ret = "(" + string(buf) + ")";
//    }
//    else if (exp->variant() == ADD_OP)
//        ret = "(+)";
//    else if (exp->variant() == SUBT_OP)
//        ret = "(-)";
//    else if (exp->variant() == MULT_OP)
//        ret = "(*)";
//    else if (exp->variant() == DIV_OP)
//        ret = "(/)";
//    else if (exp->variant() == MOD_OP)
//        ret = "(mod)";
//    else if (exp->variant() == EXP_OP)
//        ret = "(**)";
//    else if (exp->variant() == KEYWORD_VAL)
//        ret = "(" + string(((SgKeywordValExp*)exp)->value()) + ")";
//    return ret;
//}
//
//static void recExpressionPrint(SgExpression* exp, const int lvl, const char* LR, const int currNum, int& allNum)
//{
//    if (exp)
//    {
//        SgExpression* lhs = exp->lhs();
//        SgExpression* rhs = exp->rhs();
//        int lNum, rNum;
//
//        string vCurr = getValue(exp);
//        string vL = getValue(lhs);
//        string vR = getValue(rhs);
//
//        if (lhs && rhs)
//        {
//            lNum = allNum + 1;
//            rNum = allNum + 2;
//            allNum += 2;
//            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_L_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), lNum, lvl + 1, tag[lhs->variant()], vL.c_str());
//            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_R_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), rNum, lvl + 1, tag[rhs->variant()], vR.c_str());
//        }
//        else if (lhs)
//        {
//            lNum = allNum + 1;
//            allNum++;
//            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_L_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), lNum, lvl + 1, tag[lhs->variant()], vL.c_str());
//        }
//        else if (rhs)
//        {
//            rNum = allNum + 1;
//            allNum++;
//            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_R_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), rNum, lvl + 1, tag[rhs->variant()], vR.c_str());
//        }
//        if (lhs)
//            recExpressionPrint(lhs, lvl + 1, "L", lNum, allNum);
//        if (rhs)
//            recExpressionPrint(rhs, lvl + 1, "R", rNum, allNum);
//    }
//}
//void recExpressionPrintFdvm(SgExpression *exp)
//{
//    printf("digraph G{\n");
//    int allNum = 0;
//    recExpressionPrint(exp, 0, "L", allNum, allNum);
//    if (allNum == 0 && exp)
//        printf("\"%d_%d_%s_%s_%s\";\n", allNum, 0, "L", tag[exp->variant()], getValue(exp).c_str());
//    printf("}\n");
//    fflush(NULL);
//}
/* DELETE ME */
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
    {
//        recExpressionPrintFdvm(st->expr(0));
//        printf("____\n");
//        recExpressionPrintFdvm(st->expr(1));
//        printf("____\n");
//        recExpressionPrintFdvm(st->expr(2));
//        printf("****\n");
        return processLoop(st);
    }
    else if (st->variant() == CONTROL_END)
        return rw_tuple();
    else
        throw NotImplemented();
}

rw_tuple ReadWriteAnylyser::processAssignment(SgStatement* st)
{
    auto writes = unordered_set<SgSymbol*>({st->expr(0)->symbol()});
    auto reads = findVarsInExpr(st->expr(1));

    auto more_reads = findVarsInExpr(st->expr(1)->lhs());  // reads from array indexes
    auto even_more_reads = findVarsInExpr(st->expr(1));  // reads from array indexes

    reads.insert(more_reads.begin(), more_reads.end());
    reads.insert(even_more_reads.begin(), even_more_reads.end());

    return rw_tuple(reads, writes);
}

rw_tuple ReadWriteAnylyser::processLoop(SgStatement* loop)
{
    auto loop_reads = std::unordered_set<SgSymbol*>();
    auto loop_writes = std::unordered_set<SgSymbol*>();

    // process loop header
    auto reads = findVarsInExpr(loop->expr(0));
    loop_reads.insert(reads.begin(), reads.end());

    // process loop body
    reads = std::unordered_set<SgSymbol*>();
    auto writes = std::unordered_set<SgSymbol*>();

    tie(reads, writes) = processBlock(loop->lexNext(), loop->lastNodeOfStmt());

    loop_reads.insert(reads.begin(), reads.end());
    loop_writes.insert(writes.begin(), writes.end());

    // return
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

        runner = runner->lastNodeOfStmt()->lexNext();
    }

    return rw_tuple(loop_reads, loop_writes);
}

unordered_set<SgSymbol*> ReadWriteAnylyser::findVarsInExpr(SgExpression* exp)  // TODO: inter-procedure anylysis
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
            SgSymbol *s = OriginalSymbol(cur->symbol());
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
