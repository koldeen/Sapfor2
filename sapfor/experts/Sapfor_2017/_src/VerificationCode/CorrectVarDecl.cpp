#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>
#include <map>

#include "dvm.h"
#include "verifications.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "../ParallelizationRegions/ParRegions.h"
#include <vector>

using std::vector;
using std::string;
using std::map;
using std::set;

void VarDeclCorrecter(SgFile *file)
{
    vector<SgStatement*> funcMod;
    getModulesAndFunctions(file, funcMod);

    for (auto &elem : funcMod)
    {
        SgStatement *st = elem;
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
                
            if (isSgVarDeclStmt(st))
            {
                int is_assign = 0;
                for (SgExpression *el = st->expr(0); el; el = el->rhs())
                {
                    if (el->lhs()->variant() == ASSGN_OP) 
                        is_assign = 1;//with initial value
                }
                if (is_assign && st->variant() == VAR_DECL && !st->expr(2))
                    st->setVariant(VAR_DECL_90);
            }
            st = st->lexNext();
        }
    }
}

void fixUseOnlyStmt(SgFile *file, const vector<ParallelRegion*> &regs)
{
    for (int z = 0; z < file->numberOfFunctions(); ++z)
    {
        vector<SgStatement*> modules;
        findModulesInFile(file, modules);
        map<string, SgStatement*> mod;
        for (auto &elem : modules)
            mod[elem->symbol()->identifier()] = elem;

        if (modules.size())
        {
            SgStatement *func = file->functions(z);
            for (auto st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
            {
                if (isSgExecutableStatement(st))
                    break;

                if (st->variant() == USE_STMT)
                {
                    SgExpression *ex = st->expr(0);
                    string modName = st->symbol()->identifier();

                    auto it = mod.find(modName);
                                        
                    if (ex && ex->variant() == ONLY_NODE && it != mod.end())
                    {
                        set<string> allS;
                        for (auto exI = ex->lhs(); exI; exI = exI->rhs())
                        {
                            if (exI->lhs()->variant() == RENAME_NODE)
                            {
                                if (exI->lhs()->lhs()->symbol())
                                    allS.insert(exI->lhs()->lhs()->symbol()->identifier());
                                if (exI->lhs()->rhs() && exI->lhs()->rhs()->symbol())
                                    allS.insert(exI->lhs()->rhs()->symbol()->identifier());
                            }
                        }

                        set<DIST::Array*> needToAdd;
                        for (auto &parReg : regs)
                        {
                            const DataDirective &dataDir = parReg->GetDataDir();
                            for (auto &rule : dataDir.distrRules)
                            {
                                DIST::Array *curr = rule.first;
                                auto location = curr->GetLocation();
                                if (location.first == 2 && location.second == modName)
                                    needToAdd.insert(curr);
                            }
                        }

                        for (auto &array : needToAdd)
                        {
                            if (allS.find(array->GetShortName()) == allS.end())
                            {
                                SgExpression *newEx = new SgExpression(EXPR_LIST);
                                newEx->setRhs(ex->lhs());
                                auto s = findSymbolOrCreate(file, array->GetShortName());
                                newEx->setLhs(new SgExpression(RENAME_NODE, new SgVarRefExp(s), NULL, s));
                                ex->setLhs(newEx);
                            }
                        }

                    }
                }
            }
        }
    }
}