//
// Created by Vladislav Volodkin on 12/17/19.
//

#include "ReadWriteAnalyzer.h"

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

void ReadWriteAnalyzer::init()
{
    for (int i = 0; i < project.numberOfFiles(); i++)
        for (int j = 0; j < project.file(i).numberOfFunctions(); j++)
            processStatement(project.file(i).functions(j));
}

rw_tuple ReadWriteAnalyzer::processStatement(SgStatement* st)
{
    if (st->variant() == ASSIGN_STAT)
        return processAssignment(st);
    else if (st->variant() == FOR_NODE)
        return processLoop(st);
    else if (st->variant() == CONTROL_END)
        return rw_tuple();
    else
        throw NotImplemented();
}

rw_tuple ReadWriteAnalyzer::processAssignment(SgStatement* st)
{
    auto writes = unordered_set<SgSymbol*>({st->expr(0)->symbol()});
    auto reads = findVarsInExpr(st->expr(1));

    auto more_reads = findVarsInExpr(st->expr(1)->lhs());  // reads from array indexes
    auto even_more_reads = findVarsInExpr(st->expr(1));  // reads from array indexes

    reads.insert(more_reads.begin(), more_reads.end());
    reads.insert(even_more_reads.begin(), even_more_reads.end());

    return rw_tuple(reads, writes);
}

rw_tuple ReadWriteAnalyzer::processLoop(SgStatement* loop)
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

rw_tuple ReadWriteAnalyzer::processBlock(SgStatement* start, SgStatement *end)
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

rw_tuple ReadWriteAnalyzer::findUsagesInExpr(SgExpression* exp)
{
    auto usages = rw_tuple();

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
        else if (e_type == FUNC_CALL || e_type == PROC_CALL)
        {
            auto modified_in_fun = findUsagesInFuncCall(cur);
            usages.insert(modified_in_fun);
        }

        buf.push(cur->lhs());
        buf.push(cur->rhs());
    }

    return vars;
}

rw_tuple ReadWriteAnalyzer::findUsagesInFuncCall(SgExpression* exp)
{
    return rw_tuple();
}

unordered_set<SgSymbol*> ReadWriteAnalyzer::get_usages(SgStatement* st, VAR_TYPE var_type, USAGE_TYPE usage_type)  // may raise NotImplemented, out_of_range
{
    if (!initialized)
        init();

    VarUsages var_usages = data.at(st);

    if (var_usages.undefined && usage_type != USAGE_ALL)
        throw NotImplemented();

    unordered_set<SgSymbol*> usages;
    switch (usage_type) {
        case USAGE_READ:
            usages = var_usages.reads;
            break;
        case USAGE_WRITE:
            usages = var_usages.writes;
            break;
        case USAGE_ALL:
            usages = var_usages.all;
            break;
    }

    if (var_type != VAR_ALL)
        usages = filter(usages, var_type);

    return usages;
}

std::unordered_set<SgSymbol*> ReadWriteAnalyzer::get_usages(std::vector<SgStatement*> &statements, VAR_TYPE var_type, USAGE_TYPE usage_type) // may raise NotImplemented, out_of_range
{
    gif (!initialized)
        init();

    auto usages = std::unordered_set<SgSymbol*>();

    for (auto st : statements)
    {
        auto st_usages = get_usages(st, var_type, usage_type);
        usages.insert(st_usages.begin(), st_usages.end());
    }

    return usages;
}

void ReadWriteAnalyzer::printOne(SgStatement *st)
{
    st->unparsestdout();

    printf("reads: ");
    try {
        for (auto& s : get_usages(st, VAR_ALL, USAGE_READ))
            printf("%s ", s->identifier());
    } catch (NotImplemented &e) {
        printf("not_defined");
    }
    printf("\n");

    try {
        printf("writes: ");
        for (auto &s : get_usages(st, VAR_ALL, USAGE_WRITE))
            printf("%s ", s->identifier());
    } catch (NotImplemented &e) {
        printf("not_defined");
    }

    try {
        printf("all: ");
        for (auto &s : get_usages(st, VAR_ALL, USAGE_ALL))
            printf("%s ", s->identifier());
    } catch (NotImplemented &e) {
        printf("not_defined");
    }

    printf("***\n");
}

void ReadWriteAnalyzer::print()
{
    for (int i = 0; i < project.numberOfFiles(); i++)
    {
        printf("file: %s\n", project.file(i).filename());

        for (int j = 0; j < project.file(i).numberOfFunctions(); j++)
        {
            printf("function: %s\n", project.file(i).functions(j)->symbol()->identifier());

            SgStatement* runner = project.file(i).functions(j);
            auto last = runner->lastNodeOfStmt();

            while (runner != last)
            {
                printOne(runner);
                runner = runner->lexNext();
            }
        }
    }
}

std::unordered_map<SgStatement*, std::vector<bool>> ReadWriteAnalyzer::load_modified_pars(std::map<std::string, std::vector<FuncInfo*>> files)
{
    auto modified_pars = std::unordered_map<SgStatement*, std::vector<bool>>();

    for (auto& funcs : files)
    {
        for (auto& func : funcs.second)
        {
            auto func_pars_info = func->funcParams;
            auto func_pars = std::vector<bool>();

            for (int i = 0; i < func_pars_info.countOfPars; i++)
                func_pars.push_back(func_pars_info.isArgOut(i));

            modified_pars[func->funcPointer] = func_pars;
        }
    }

    return modified_pars;
}
