#include "leak_detector.h"
#include "ReadWriteAnalyzer.h"

using namespace std;

void ReadWriteAnalyzer::init(SgFile* forFile)
{
    auto save = current_file->filename();
    
    modified_pars = ReadWriteAnalyzer::load_modified_pars(funcInfo);
    for (int j = 0; j < forFile->numberOfFunctions(); ++j)
    {
        SgStatement* func_hdr = forFile->functions(j);
        SgStatement* last = func_hdr->lastNodeOfStmt();

        for (SgStatement* runner = func_hdr->lexNext(); runner != last; runner = runner->lexNext())
        {
            // TODO: is it ok to skip all of them?
            if (!isSgExecutableStatement(runner) || isDVM_stat(runner) || isSPF_stat(runner))
                continue;

            if (runner->variant() == CONTAINS_STMT)
                break;

            VarUsages usages = findUsagesInStatement(runner);

            auto it = usages_by_statement.find(runner);
            if (it != usages_by_statement.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            usages_by_statement[runner] = usages;
        }
    }    
    initialized.insert(forFile->filename());

    if (SgFile::switchToFile(save) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

VarUsages ReadWriteAnalyzer::findUsagesInStatement(SgStatement* st) const
{
    // *special* statements, TODO: what i've missed?
    if (st->variant() == ASSIGN_STAT)
        return findUsagesInAssignment(st);

    if (st->variant() == PROC_STAT)
        return findUsagesInFuncCall(st->expr(0), st->symbol()->identifier());
    else if (!isDVM_stat(st) && !isSPF_stat(st))
    {        
        VarUsages st_usages;
        for (int i = 0; i < 3; ++i)
            st_usages.extend(findUsagesInExpr(st->expr(i)));
        return st_usages;
    }
    return VarUsages();
}

VarUsages ReadWriteAnalyzer::findUsagesInAssignment(SgStatement* st) const
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

VarUsages ReadWriteAnalyzer::findUsagesInExpr(SgExpression* exp) const
{
    VarUsages usages;

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
            usages.extend(findUsagesInFuncCall(cur->lhs(), cur->symbol()->identifier()));

        buf.push(cur->lhs());
        buf.push(cur->rhs());
    }
    return usages;
}

VarUsages ReadWriteAnalyzer::findUsagesInFuncCall(SgExpression* params_tree, const string& func_key) const
{
    VarUsages usages;

    vector<int> inOutTypes;
    if (!isIntrinsicFunctionName(func_key.c_str()))
    {
        auto it = modified_pars.find(func_key);
        if (it != modified_pars.end())
            inOutTypes = it->second;
    }

    int param_no = 0;
    while (params_tree)
    {
        SgExpression* param = params_tree->lhs();

        if (param->variant() == VAR_REF || param->variant() == ARRAY_REF)
        {
            if (inOutTypes.size())
            {
                if (param_no >= inOutTypes.size())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                if (FuncParam::isArgIn((int64_t)inOutTypes[param_no]))
                    usages.insert_read(param);
                if (FuncParam::isArgOut((int64_t)inOutTypes[param_no]))
                    usages.insert_write(param);
            }
            else
                usages.insert_read(param);
        }

        param_no++;
        params_tree = params_tree->rhs();
    }

    return usages;
}

VarUsages ReadWriteAnalyzer::get_usages(SgStatement* st)
{
    if (initialized.find(st->fileName()) == initialized.end())
        init(st->getFile());

    VarUsages usages;
    // if statement is compound
    if (compound_statements.find(st->variant()) != compound_statements.end())
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

VarUsages ReadWriteAnalyzer::gatherUsagesForCompound(SgStatement* compoundStatement) const
{
    VarUsages all_usages;

    SgStatement* last = compoundStatement->lastNodeOfStmt();
    SgStatement* runner = compoundStatement;
    while (runner != last)
    {
        if (runner->variant() == CONTAINS_STMT)
            break;

        if (!isSgExecutableStatement(runner) || isDVM_stat(runner) || isSPF_stat(runner))
        {
            runner = runner->lexNext();
            continue;
        }

        all_usages.extend(findUsagesInStatement(runner));
        runner = runner->lexNext();
    }
    return all_usages;
}

void ReadWriteAnalyzer::print() const
{
    auto save = current_file->filename();

    for (int i = 0; i < CurrentProject->numberOfFiles(); i++)
    {
        printf("file: %s\n", CurrentProject->file(i).filename());
        for (int j = 0; j < CurrentProject->file(i).numberOfFunctions(); j++)
        {
            printf("function: %s\n", CurrentProject->file(i).functions(j)->symbol()->identifier());
            SgStatement* runner = CurrentProject->file(i).functions(j);
            auto last = runner->lastNodeOfStmt();

            while (runner != last)
            {
                if (runner->variant() == CONTAINS_STMT)
                    break;
                
                auto it = usages_by_statement.find(runner);
                if (it != usages_by_statement.end())
                {
                    runner->unparsestdout();
                    it->second.print();
                }
                runner = runner->lexNext();
            }
        }
    }

    if (SgFile::switchToFile(save) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

map<string, vector<int>> ReadWriteAnalyzer::load_modified_pars(const map<string, vector<FuncInfo*>> &files)
{
    map<string, vector<int>> res;

    for (auto& funcs : files)
    {
        string file_name = funcs.first;

        for (auto& func : funcs.second)
        {
            string func_key = func->funcName;
            res[func_key] = func->funcParams.inout_types;
        }
    }
    return res;
}
