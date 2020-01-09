#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <assert.h>
#include <set>

#include "dvm.h"
#include "../Utils/SgUtils.h"
#include "../Utils/errors.h"

using std::set;
using std::map;
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
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            // save SgStatement PROC call to declaration attribute
            if (st->variant() == ALLOCATE_STMT || st->variant() == DEALLOCATE_STMT)
            {
                SgExpression *list = st->expr(0);
                set<SgStatement*> decls;
                while (list)
                {
                    if (list->lhs()->variant() == ARRAY_REF)
                        decls.insert(declaratedInStmt(OriginalSymbol(isSgArrayRefExp(list->lhs())->symbol())));
                    else if (list->lhs()->variant() == RECORD_REF)
                        decls.insert(declaratedInStmt(OriginalSymbol(isSgRecordRefExp(list->lhs())->fieldName())));

                    list = list->rhs();
                }

                char buf[256];
                for (auto it = decls.begin(); it != decls.end(); ++it)
                {
                    (*it)->addAttribute(st->variant(), st, sizeof(SgStatement*));
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

//TODO: extend ALLOC/DEALLOC moving
//TODO: add support of different files
// only one level of call is supported
void moveAllocatesInterproc(const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    for (auto &array : arrayLinksByFuncCalls)
    {
        if (array.first->GetLocation().first == DIST::l_PARAMETER)
        {
            //check one level of calls
            bool ok = true;
            for (auto &elem : array.second)
                if (elem->GetLocation().first == DIST::l_PARAMETER)
                    ok = false;

            //move to all real arrays
            if (ok)
            {
                auto allPlaces = array.first->GetDeclInfo();
                for (auto &place : allPlaces)
                {
                    if (SgFile::switchToFile(place.first) != -1)
                    {
                        SgStatement *decl = SgStatement::getStatementByFileAndLine(place.first, place.second);
                        checkNull(decl, convertFileName(__FILE__).c_str(), __LINE__);

                        map<SgStatement*, set<SgStatement*>> needToAdd;
                        for (auto &data : getAttributes<SgStatement*, SgStatement*>(decl, set<int>{ ALLOCATE_STMT }))
                        {
                            for (auto &realArray : array.second)
                            {
                                auto allPlacesR = realArray->GetDeclInfo();
                                for (auto &placeR : allPlacesR)
                                {
                                    //the same file
                                    if (placeR.first == place.first)
                                    {
                                        SgStatement* declR = SgStatement::getStatementByFileAndLine(placeR.first, placeR.second);
                                        checkNull(declR, convertFileName(__FILE__).c_str(), __LINE__);

                                        needToAdd[declR].insert(data);                                        
                                    }
                                }
                            }
                        }

                        for (auto& toAdd : needToAdd)
                        {
                            for (auto& list : toAdd.second)
                            {
                                char buf[256];
                                toAdd.first->addAttribute(list->variant(), list, sizeof(SgStatement*));
                                sprintf(buf, "  [INTERPROC] attribute is added to declaration on line %d\n", toAdd.first->lineNumber());
                                addToGlobalBufferAndPrint(buf);
                            }
                        }
                    }
                }
            }
        }
    }
}