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

void setAllDeclsWithInitZero(SgFile* file)
{
    /*if (file->filename() == string("Output_kin.for"))
        printf("");*/
    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        set<string> argNames;
        auto func = isSgProgHedrStmt(file->functions(i));
        checkNull(func, convertFileName(__FILE__).c_str(), __LINE__);

        for (int z = 0; z < func->numberOfParameters(); ++z)
            argNames.insert(func->parameter(z)->identifier());

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
            {
                for (auto ex = decl->expr(0); ex; ex = ex->rhs())
                {   
                    auto s = ex->lhs()->symbol();
                    if (s)
                    {
                        bool isInData = (s->attributes() & DATA_BIT) != 0;
                        if (!isInData && 
                            ex->lhs()->variant() != ASSGN_OP &&
                            ex->lhs()->symbol()->variant() != FUNCTION_NAME &&
                            ex->lhs()->symbol()->variant() != CONST_NAME &&
                            argNames.find(ex->lhs()->symbol()->identifier()) == argNames.end() &&
                            commonNames.find(ex->lhs()->symbol()->identifier()) == commonNames.end())
                        {
                            //printf("%d\n", ex->lhs()->symbol()->variant());
                            SgExpression* initOp = new SgExpression(ASSGN_OP, ex->lhs(), new SgValueExp(0));
                                ex->setLhs(initOp);
                        }
                    }
                }
            }
        }
    }
}