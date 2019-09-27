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
        for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
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

    if (wasExec)
        __spf_print(1, "wasExec swap in file %s\n", file->filename());
    if (wasDecl)
        __spf_print(1, "wasDECL swap in file %s\n", file->filename());
}