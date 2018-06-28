#include "../leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <assert.h>
#include <set>

#include "dvm.h"
#include "../SgUtils.h"

using std::set;
using std::string;

void preprocess_allocates(SgFile *file)
{
    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
            currProcessing.second = NULL;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }
            if (st->variant() == CONTAINS_STMT)
                break;

            // save SgStatement PROC call to declaration attribute
            if (st->variant() == ALLOCATE_STMT)
            {
                SgExpression *list = st->expr(0);
                set<SgStatement*> decls;
                while (list)
                {
                    SgArrayRefExp *arrayRef = isSgArrayRefExp(list->lhs());
                    decls.insert(declaratedInStmt(OriginalSymbol(arrayRef->symbol())));
                    list = list->rhs();
                }

                char buf[256];
                for (auto it = decls.begin(); it != decls.end(); ++it)
                {
                    (*it)->addAttribute(ALLOCATE_STMT, st, sizeof(SgStatement*));
                    sprintf(buf, "  attribute is added to declaration on line %d\n", (*it)->lineNumber());
                    addToGlobalBufferAndPrint(buf);
                }

                if (decls.size() == 0)
                {
                    sprintf(buf, "ERROR at line %d %s: Can not find declarations for allocation on line %d\n", __LINE__, convertFileName(__FILE__).c_str(), st->lineNumber());
                    addToGlobalBufferAndPrint(buf);
                    throw(-1);
                }
            }
            st = st->lexNext();
        }
    }
}