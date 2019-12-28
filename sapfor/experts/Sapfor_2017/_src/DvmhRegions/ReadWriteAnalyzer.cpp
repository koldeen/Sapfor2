//
// Created by Vladislav Volodkin on 12/17/19.
//
#include "leak_detector.h"
#include "ReadWriteAnalyzer.h"

using namespace std;

void ReadWriteAnalyzer::init()
{
    modified_pars = load_modified_pars(funcInfo);

    for (int i = 0; i < project.numberOfFiles(); i++)
    {
        for (int j = 0; j < project.file(i).numberOfFunctions(); j++)
        {
            SgStatement* func_hdr = project.file(i).functions(j);
            SgStatement* last = func_hdr->lastNodeOfStmt();

            for (SgStatement* runner = func_hdr->lexNext(); runner != last; runner = runner->lexNext())
            {
                if (!isSgExecutableStatement(runner))  // TODO: is it ok to skip all of them?
                    continue;

                VarUsages usages = findUsagesInStatement(runner);
                usages_by_statement[runner] = usages;
            }
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
        st->unparsestdout();  // TODO
        printf("%d\n", st->variant());
        recExpressionPrint(st->expr(0));
        recExpressionPrint(st->expr(1));
        recExpressionPrint(st->expr(2));

        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
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
    usages.insert_write(st->expr(0));

    return usages;
}

VarUsages ReadWriteAnalyzer::findUsagesInExpr(SgExpression* exp)
{
    auto usages = VarUsages();

    queue<SgExpression*> buf;
    buf.push(exp);

    while (!buf.empty())
    {
        SgExpression* cur = buf.front();
        buf.pop();

        if (!cur)
            continue;

        int e_type = cur->variant();

        if (e_type == VAR_REF || e_type == ARRAY_REF)
            usages.insert_read(cur);
        else if (e_type == FUNC_CALL)
        {
            VarUsages modified_in_fun = findUsagesInFuncCall(cur);
            usages.extend(modified_in_fun);
        }

        buf.push(cur->lhs());
        buf.push(cur->rhs());
    }

    return usages;
}

VarUsages ReadWriteAnalyzer::findUsagesInFuncCall(SgExpression* fun_call)
{
    VarUsages usages;

    auto params_tree = fun_call->lhs();

    int param_no = 0;
    while (params_tree)
    {
        SgExpression* param = params_tree->lhs();

        if (param->variant() == VAR_REF || param->variant() == ARRAY_REF)
        {
            string func_key = fun_call->symbol()->identifier();  // TODO: use file_name + func_name
            auto is_param_modified = modified_pars[func_key];

            if (is_param_modified.size() >= param_no)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            if (is_param_modified[param_no])
                usages.insert_write(param);
        }

        param_no++;
        params_tree = params_tree->rhs();
    }

    return usages;
}

VarUsages ReadWriteAnalyzer::get_usages(SgStatement* st)  // may raise out_of_range
{
    if (!initialized)
        init();

    VarUsages usages;
    if (compound_statements.find(st->variant()) != compound_statements.end())  // if statement is compound
        usages = gatherUsagesForCompound(st);
    else
    {
        auto it = usages_by_statement.find(st);
        if (it == usages_by_statement.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        usages = it->second;
    }

    return usages;
}

VarUsages ReadWriteAnalyzer::get_usages(vector<SgStatement*> &statements)
{
    auto usages = VarUsages();

    for (auto& st : statements)
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
    SgStatement* runner = compoundStatement;
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

map<string, vector<bool>> ReadWriteAnalyzer::load_modified_pars(const map<string, vector<FuncInfo*>> &files)
{
    auto res = map<string, vector<bool>>();

    for (auto& funcs : files)
    {
        string file_name = funcs.first;

        for (auto& func : funcs.second)
        {
            auto func_pars_info = func->funcParams;
            auto func_pars = vector<bool>();

            for (int i = 0; i < func_pars_info.countOfPars; i++)
                func_pars.push_back(func_pars_info.isArgOut(i));

            string func_key = func->funcName;  // TODO: use file_name + func_name
            res[func_key] = func_pars;
        }
    }

    return res;
}
