//
// Created by Vladislav Volodkin on 12/17/19.
//

#include "ReadWriteAnalyzer.h"

using namespace std;

/* DELETE ME */
static string getValue(SgExpression *exp)
{
    if (exp == NULL)
        return "";

    string ret = "";
    if (exp->symbol())
    {
        if (exp->symbol()->identifier())
            ret = "(" + string(exp->symbol()->identifier()) + ")";
    }
    else if (exp->variant() == INT_VAL)
    {
        char buf[256];
        sprintf(buf, "%d", exp->valueInteger());
        ret = "(" + string(buf) + ")";
    }
    else if (exp->variant() == ADD_OP)
        ret = "(+)";
    else if (exp->variant() == SUBT_OP)
        ret = "(-)";
    else if (exp->variant() == MULT_OP)
        ret = "(*)";
    else if (exp->variant() == DIV_OP)
        ret = "(/)";
    else if (exp->variant() == MOD_OP)
        ret = "(mod)";
    else if (exp->variant() == EXP_OP)
        ret = "(**)";
    else if (exp->variant() == KEYWORD_VAL)
        ret = "(" + string(((SgKeywordValExp*)exp)->value()) + ")";
    return ret;
}

static void recExpressionPrint(SgExpression* exp, const int lvl, const char* LR, const int currNum, int& allNum)
{
    if (exp)
    {
        SgExpression* lhs = exp->lhs();
        SgExpression* rhs = exp->rhs();
        int lNum, rNum;

        string vCurr = getValue(exp);
        string vL = getValue(lhs);
        string vR = getValue(rhs);

        if (lhs && rhs)
        {
            lNum = allNum + 1;
            rNum = allNum + 2;
            allNum += 2;
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_L_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), lNum, lvl + 1, tag[lhs->variant()], vL.c_str());
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_R_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), rNum, lvl + 1, tag[rhs->variant()], vR.c_str());
        }
        else if (lhs)
        {
            lNum = allNum + 1;
            allNum++;
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_L_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), lNum, lvl + 1, tag[lhs->variant()], vL.c_str());
        }
        else if (rhs)
        {
            rNum = allNum + 1;
            allNum++;
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_R_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), rNum, lvl + 1, tag[rhs->variant()], vR.c_str());
        }
        if (lhs)
            recExpressionPrint(lhs, lvl + 1, "L", lNum, allNum);
        if (rhs)
            recExpressionPrint(rhs, lvl + 1, "R", rNum, allNum);
    }
}
void recExpressionPrintFdvm(SgExpression *exp)
{
    printf("digraph G{\n");
    int allNum = 0;
    recExpressionPrint(exp, 0, "L", allNum, allNum);
    if (allNum == 0 && exp)
        printf("\"%d_%d_%s_%s_%s\";\n", allNum, 0, "L", tag[exp->variant()], getValue(exp).c_str());
    printf("}\n");
    fflush(NULL);
}
/* DELETE ME */

void ReadWriteAnalyzer::init()
{
    for (int i = 0; i < project.numberOfFiles(); i++)
        for (int j = 0; j < project.file(i).numberOfFunctions(); j++)
        {
            SgStatement* func_hdr = project.file(i).functions(j);
            SgStatement* last = func_hdr->lastNodeOfStmt();

            SgStatement* runner = func_hdr->lexNext();
            while (runner != last)
            {
                VarUsages usages = findUsagesInStatement(runner);
                usages_by_statement[runner] = usages;

                runner = runner->lexNext();
            }
        }
}

VarUsages ReadWriteAnalyzer::findUsagesInStatement(SgStatement* st)
{
    // *special* statements, TODO: what i've missed?
    if (st->variant() == ASSIGN_STAT)
        return findUsagesInAssignment(st);
    if (st->variant() == PROC_STAT)
    {
        st->unparsestdout();
        printf("%d\n", st->variant());
        recExpressionPrintFdvm(st->expr(0));
        recExpressionPrintFdvm(st->expr(1));
        recExpressionPrintFdvm(st->expr(2));

        throw NotImplemented();
    }

    // common statements
    auto st_usages = VarUsages();
    for (int i = 0; i < 3; i++)
    {
        auto expr_usages = findUsagesInExpr(st->expr(i));
        st_usages.extend(expr_usages);
    }

    return st_usages;
}

VarUsages ReadWriteAnalyzer::findUsagesInAssignment(SgStatement* st)
{
    // load read & writes from the right part
    VarUsages usages = findUsagesInExpr(st->expr(1));

    // load usages from array indexes
    VarUsages usages_in_arr_indexing = findUsagesInExpr(st->expr(1)->lhs());
    usages.extend(usages_in_arr_indexing);
    usages_in_arr_indexing = findUsagesInExpr(st->expr(1)->rhs());
    usages.extend(usages_in_arr_indexing);

    // finally add explicitly modified var
    usages.insert_write(st->expr(0)->symbol());

    return usages;
}

VarUsages ReadWriteAnalyzer::findUsagesInExpr(SgExpression* exp)
{
    auto usages = VarUsages();

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
            usages.insert_read(s);
        }
        else if (e_type == FUNC_CALL || e_type == PROC_CALL)
        {
            VarUsages modified_in_fun = findUsagesInFuncCall(cur);
            usages.extend(modified_in_fun);
        }

        buf.push(cur->lhs());
        buf.push(cur->rhs());
    }

    return usages;
}

VarUsages ReadWriteAnalyzer::findUsagesInFuncCall(SgExpression* exp)
{
    recExpressionPrintFdvm(exp);  // todo: stopped here
    throw exception();
}

VarUsages ReadWriteAnalyzer::get_usages(SgStatement* st)  // may raise out_of_range
{
    if (!initialized)
        init();

    VarUsages usages;
    if (compound_statements.find(st->variant()) == compound_statements.end())  // if statement is compound
        usages = gatherUsagesForCompound(st);
    else
        usages = usages_by_statement.at(st);

    return usages;
}

VarUsages ReadWriteAnalyzer::get_usages(std::vector<SgStatement*> &statements) // may raise NotImplemented, out_of_range
{
    auto usages = VarUsages();

    for (auto st : statements)
    {
        auto st_usages = get_usages(st);
        usages.extend(st_usages);
    }

    return usages;
}

VarUsages ReadWriteAnalyzer::gatherUsagesForCompound(SgStatement* compoundStatement)
{
    auto all_usages = VarUsages();

    SgStatement* last = compoundStatement->lastNodeOfStmt();
    SgStatement* runner = compoundStatement->lexNext();
    while (runner != last)
    {
        VarUsages st_usages = findUsagesInStatement(runner);
        all_usages.extend(st_usages);

        runner = runner->lexNext();
    }

    return all_usages;
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
                runner->unparsestdout();
                auto st_usages = usages_by_statement[runner];
                st_usages.print();

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
