#include <cstdio>
#include <cstring>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>

#include "swap_array_dims.h"
#include "../Distribution/Array.h"
#include "dvm.h"

#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"

using namespace std;

static bool recSwapExpression(SgExpression *ex, const map<string, vector<int>> &arraysToSwap)
{
    bool res = false;
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            string arrayName = ex->symbol()->identifier();
            auto it = arraysToSwap.find(arrayName);
            if (it != arraysToSwap.end() && ex->lhs())
            {
                vector<SgExpression*> last;

                for (SgExpression *list = ex->lhs(); list; list = list->rhs())
                    last.push_back(list->lhs());

                int i = 0;
                if (last.size() == it->second.size())
                {
                    for (SgExpression *list = ex->lhs(); list; list = list->rhs(), ++i)
                        list->setLhs(last[it->second[i]]);

                    res = true;
                }
            }
        }

        bool tmpR = recSwapExpression(ex->lhs(), arraysToSwap);
        res = res || tmpR;
        tmpR = recSwapExpression(ex->rhs(), arraysToSwap);
        res = res || tmpR;
    }

    return res;
}

//TODO: use Array
void SwapArrayDims(SgFile *file, const map<string, vector<int>> &arraysToSwap)
{
    bool wasDecl = false;
    bool wasExec = false;

    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        for (SgStatement* st = file->firstStatement(); st; st = st->lexNext())
        {
            bool isExec = isSgExecutableStatement(st);
            for (int i = 0; i < 3; ++i)
            {
                bool res = recSwapExpression(st->expr(i), arraysToSwap);
                if (isExec)
                    wasExec = wasExec || res;
                else
                    wasDecl = wasDecl || res;
            }
        }
    }

    if (wasExec)
        __spf_print(1, "wasExec swap in file %s\n", file->filename());
    if (wasDecl)
        __spf_print(1, "wasDECL swap in file %s\n", file->filename());
}

static void addToNonDecl(SgExpression *ex, set<SgSymbol*> &notDeclarated)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF || ex->variant() == ARRAY_REF)
        {
            auto toCheck = OriginalSymbol(ex->symbol());
            if (toCheck->variant() != FUNCTION_NAME)
            {
                if (declaratedInStmt(toCheck, NULL, false) == NULL)
                    notDeclarated.insert(toCheck);
            }
        }
        addToNonDecl(ex->lhs(), notDeclarated);
        addToNonDecl(ex->rhs(), notDeclarated);
    }
}

static void makeInit(SgExpression *exList, const set<string> &argNames, const set<string> &commonNames)
{
    for (auto ex = exList; ex; ex = ex->rhs())
    {
        auto s = ex->lhs()->symbol();
        if (s)
        {
            bool isInData = (s->attributes() & DATA_BIT) != 0;
            if (!isInData && s->type() && s->type()->variant() != T_STRING &&
                ex->lhs()->variant() != ASSGN_OP &&
                ex->lhs()->symbol()->variant() != FUNCTION_NAME &&
                ex->lhs()->symbol()->variant() != CONST_NAME &&
                argNames.find(ex->lhs()->symbol()->identifier()) == argNames.end() &&
                commonNames.find(ex->lhs()->symbol()->identifier()) == commonNames.end())
            {
                //printf("%d\n", ex->lhs()->symbol()->variant());
                SgExpression* initOp = NULL;

                if (s->type()->variant() == T_BOOL)
                    initOp = new SgExpression(ASSGN_OP, ex->lhs(), new SgValueExp(false));
                else if (s->type()->variant() != T_STRUCT)
                    initOp = new SgExpression(ASSGN_OP, ex->lhs(), new SgValueExp(0));

                if (initOp)
                    ex->setLhs(initOp);
            }
        }
    }
}

void setAllDeclsWithInitZero(SgFile* file)
{
    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        set<string> argNames;
        auto func = isSgProgHedrStmt(file->functions(i));
        checkNull(func, convertFileName(__FILE__).c_str(), __LINE__);

        if (func->variant() != PROG_HEDR)
        {
            for (int z = 0; z < func->numberOfParameters(); ++z)
                argNames.insert(func->parameter(z)->identifier());
        }

        map<string, vector<SgExpression*>> commonBlocks;
        getCommonBlocksRef(commonBlocks, func, func->lastNodeOfStmt());

        set<string> commonNames;
        for (auto& elem : commonBlocks)
            for (auto& elemName : elem.second)
                for (SgExpression* currCommon = elemName->lhs(); currCommon; currCommon = currCommon->rhs())
                    commonNames.insert(currCommon->lhs()->symbol()->identifier());

        set<string> dataNames;
        bool hasAllSave = false;
        for (SgStatement* st = func; st; st = st->lexNext())
        {
            if(st->variant() == CONTAINS_STMT)
                break;
            if (isSgExecutableStatement(st))
                break;
            if (st->variant() == SAVE_DECL)
            {
                if (!st->expr(0) && !st->expr(1) && !st->expr(2))
                    hasAllSave = true;
                else
                {
                    for (auto ex = st->expr(0); ex; ex = ex->rhs())
                        dataNames.insert(ex->lhs()->symbol()->identifier());
                }
            }
        }

        if (hasAllSave)
            continue;

        for (SgStatement* st = func; st; st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;
            if (isSgExecutableStatement(st))
                break;

            auto decl = isSgDeclarationStatement(st);
            if (decl && st->variant() != DATA_DECL)
                makeInit(decl->expr(0), argNames, commonNames);
        }

        set<SgSymbol*> notDeclarated;
        for (SgStatement* st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;
            if (!isSgExecutableStatement(st))
                continue;

            for (int z = 0; z < 3; ++z)
                addToNonDecl(st->expr(z), notDeclarated);
        }
        
        if (notDeclarated.size())
        {
            map<int, set<SgSymbol*>> groupedByType;
            for (auto& elem : notDeclarated)
                groupedByType[elem->type()->id()].insert(elem);

            for (auto& gr : groupedByType)
            {
                vector<SgSymbol*> group(gr.second.begin(), gr.second.end());
                auto declStat = makeDeclaration(func, group);
                makeInit(declStat->expr(0), argNames, commonNames);
            }
        }

        //insert SAVE without variables
        /*SgStatement* firstExec = NULL;
        for (SgStatement* st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;
            if (isSgExecutableStatement(st))
            {         
                firstExec = st;
                break;
            }
        }
        firstExec->insertStmtBefore(*new SgStatement(SAVE_DECL), *func);*/
    }

    vector<SgStatement*> modules;
    findModulesInFile(file, modules);

    for (auto& mod : modules)
    {
        for (auto st = mod->lexNext(); st != mod->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;
            auto decl = isSgDeclarationStatement(st);

            set<string> empty;
            if (decl && st->variant() != DATA_DECL)
                makeInit(decl->expr(0), empty, empty);
        }
    }
}

static void addTextInit(SgStatement* decl, map<pair<string, int>, string> &symbols)
{
    for (auto ex = decl->expr(0); ex; ex = ex->rhs())
    {
        if (ex->lhs()->variant() == ASSGN_OP)
            symbols[make_pair(ex->lhs()->lhs()->symbol()->identifier(), decl->lineNumber())] = string("  ") + ex->lhs()->unparse();
        else if (ex->lhs()->symbol() && ((ex->lhs()->symbol()->attributes() & DATA_BIT) != 0))
            symbols[make_pair(ex->lhs()->symbol()->identifier(), decl->lineNumber())] = string("  '") + ex->lhs()->symbol()->identifier() + string("' inited from DATA");
    }
}

void dumpAllDeclsWithInit(SgFile* file, bool create)
{
    string dumpF = string("dump_decls.txt");
    FILE* fDump = NULL;
    if (create)
        fDump = fopen(dumpF.c_str(), "w");
    else
        fDump = fopen(dumpF.c_str(), "a+");

    checkNull(fDump, convertFileName(__FILE__).c_str(), __LINE__);
        
    map<string, string> dumpTextByFunc;
    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        string dumpText = "";

        auto func = isSgProgHedrStmt(file->functions(i));
        checkNull(func, convertFileName(__FILE__).c_str(), __LINE__);
               
        dumpText += string("FOR FUNC ") + func->symbol()->identifier() + "\n";

        map<pair<string, int>, string> symbols;
        for (SgStatement* st = func->lexNext(); st; st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;
            if (isSgExecutableStatement(st))
                break;

            auto decl = isSgDeclarationStatement(st);
            if (decl && st->variant() != DATA_DECL)
                addTextInit(decl, symbols);
        }        

        for (auto& elem : symbols)
            dumpText += elem.second + "\n";

        dumpTextByFunc[func->symbol()->identifier()] = dumpText;
    }
    
    vector<SgStatement*> mods;
    findModulesInFile(file, mods);
    for (auto& mod : mods)
    {
        string dumpText = string("FOR MODULE ") + mod->symbol()->identifier() + "\n";

        map<pair<string, int>, string> symbols;
        for (SgStatement* st = mod->lexNext(); st; st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;
            if (isSgExecutableStatement(st))
                break;

            auto decl = isSgDeclarationStatement(st);
            if (decl && st->variant() != DATA_DECL)
            {
                for (auto ex = decl->expr(0); ex; ex = ex->rhs())
                    addTextInit(decl, symbols);
            }
        }

        for (auto& elem : symbols)
            dumpText += elem.second + "\n";

        dumpTextByFunc[string("_module_") + mod->symbol()->identifier()] = dumpText;

    }

    for (auto& elem : dumpTextByFunc)
        fprintf(fDump, "%s\n", elem.second.c_str());
    
    fclose(fDump);
}