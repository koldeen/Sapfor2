#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <vector>

#include "dvm.h"
#include "verifications.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "../ParallelizationRegions/ParRegions.h"

#include "../GraphCall/graph_calls_func.h"

using std::vector;
using std::string;
using std::map;
using std::pair;
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

static void fillUseStatement(SgStatement *st,
                             set<string> &useMod,
                             map<string, vector<pair<SgSymbol*, SgSymbol*>>> &modByUse,
                             map<string, vector<pair<SgSymbol*, SgSymbol*>>> &modByUseOnly)
{
    if (st->variant() == USE_STMT)
    {
        SgExpression *ex = st->expr(0);
        string modName = st->symbol()->identifier();
        useMod.insert(modName);

        if (ex)
        {
            SgExpression *start = ex;
            bool only = false;
            if (ex->variant() == ONLY_NODE)
            {
                start = ex->lhs();
                only = true;
            }

            for (auto exI = start; exI; exI = exI->rhs())
            {
                if (exI->lhs()->variant() == RENAME_NODE)
                {
                    SgSymbol *left = NULL, *right = NULL;
                    if (exI->lhs()->lhs()->symbol())
                        left = exI->lhs()->lhs()->symbol();
                    if (exI->lhs()->rhs() && exI->lhs()->rhs()->symbol())
                        right = exI->lhs()->rhs()->symbol();
                    if (only)
                        modByUseOnly[modName].push_back(std::make_pair(left, right));
                    else
                        modByUse[modName].push_back(std::make_pair(left, right));
                }
            }
        }
    }
}

struct ModuleInfo
{
    set<string> useMod;
    map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUse;
    map<string, vector<pair<SgSymbol*, SgSymbol*>>> modByUseOnly;
    set<string> functions;
};

static void fillInfo(SgStatement *mod, map<string, ModuleInfo> &modsInfo)
{
    ModuleInfo currInfo;
    for (SgStatement *st = mod->lexNext(); st != mod->lastNodeOfStmt(); st = st->lexNext())
    {
        fillUseStatement(st, currInfo.useMod, currInfo.modByUse, currInfo.modByUseOnly);
        if (st->variant() == CONTAINS_STMT)
            break;
        if (st->variant() == PROC_HEDR || st->variant() == FUNC_HEDR)
            break;
    }
    modsInfo[mod->symbol()->identifier()] = currInfo;
}

static void changeNameOfModuleFunc(string funcName, SgSymbol *curr, const map<string, ModuleInfo> &modsInfo, SgStatement *cp)
{
    //string funcName = procS->identifier();
    auto itUse = modsInfo.find(cp->symbol()->identifier());
    if (itUse == modsInfo.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    const ModuleInfo &info = itUse->second;
    string callInMod = "";
    string byUseName = "";
    for (auto &elem : info.modByUse)
    {
        if (callInMod != "")
            break;
        string fromMod = elem.first;
        for (auto &k : elem.second)
        {
            if (k.first->identifier() == funcName)
            {
                callInMod = fromMod;
                byUseName = k.second->identifier();
                break;
            }
        }
    }

    for (auto &elem : info.modByUseOnly)
    {
        if (callInMod != "")
            break;
        string fromMod = elem.first;
        for (auto &k : elem.second)
        {
            if (k.first->identifier() == funcName)
            {
                callInMod = fromMod;
                byUseName = k.second->identifier();
                break;
            }
        }
    }

    if (callInMod == "")
    {
        set<pair<string, string>> filter;
        for (auto &mods : info.useMod)
        {
            auto it = modsInfo.find(mods);
            if (it == modsInfo.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            auto funcs = it->second.functions;
            for (auto &func : funcs)
            {
                if (func == funcName)
                    if (info.modByUseOnly.find(mods) == info.modByUseOnly.end())
                        filter.insert(make_pair(mods, func));
            }
        }

        if (filter.size() == 1)
            callInMod = (*filter.begin()).first;
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    string newName = (byUseName == "" ? callInMod + "::" + string(curr->identifier()) : byUseName);

    char *lastName = new char[256];
    addToCollection(__LINE__, __FILE__, lastName, 2);
    sprintf(lastName, "%s", curr->identifier());
    curr->addAttribute(VARIABLE_NAME, lastName, sizeof(char*));
    curr->changeName(newName.c_str());
}

static void correctModuleProcNamesEx(SgExpression *ex, SgStatement *cp, const map<string, ModuleInfo> &modsInfo)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            if (!isIntrinsicFunctionName(ex->symbol()->identifier()))
            {
                SgSymbol *procS = OriginalSymbol(ex->symbol());
                if (cp->variant() != MODULE_STMT)
                {
                    if (ex->symbol() != procS)
                    {
                        //printf(":: var %d, line %d, change %s -> %s\n", st->variant(), st->lineNumber(), st->symbol()->identifier(), procS->identifier());
                        ex->symbol()->addAttribute(VARIABLE_NAME, procS, sizeof(SgSymbol));
                        ex->setSymbol(*procS);
                    }
                }
                else
                    changeNameOfModuleFunc(procS->identifier(), ex->symbol(), modsInfo, cp);
            }
        }

        correctModuleProcNamesEx(ex->lhs(), cp, modsInfo);
        correctModuleProcNamesEx(ex->rhs(), cp, modsInfo);
    }
}

void correctModuleProcNames(SgFile *file)
{
    vector<SgStatement*> modules;
    findModulesInFile(file, modules);
        
    map<string, ModuleInfo> modsInfo;
    for (auto &mod : modules)
    {
        fillInfo(mod, modsInfo);
        const string modName = mod->symbol()->identifier();
        for (SgStatement *st = mod->lexNext(); st != mod->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == PROC_HEDR || st->variant() == FUNC_HEDR)
            {
                char *lastName = new char[256];
                addToCollection(__LINE__, __FILE__, lastName, 2);
                sprintf(lastName, "%s", st->symbol()->identifier());
                modsInfo[modName].functions.insert(lastName);

                st->symbol()->changeName((modName + "::" + st->symbol()->identifier()).c_str());
                st->symbol()->addAttribute(VARIABLE_NAME, lastName, sizeof(char*));
            }
        }
    }

    if (modules.size() == 0)
        return;

    for (int z = 0; z < file->numberOfFunctions(); ++z)
    {
        SgStatement *func = file->functions(z);
        for (SgStatement *st = func->lexNext(); st != func->lastNodeOfStmt(); st = st->lexNext())
        {
            if (isSgExecutableStatement(st))
            {
                SgStatement *cp = st->controlParent();
                while (cp->variant() != MODULE_STMT && cp->variant() != PROG_HEDR && cp->variant() != GLOBAL)
                    cp = cp->controlParent();

                if (st->variant() == PROC_STAT)
                {
                    if (!isIntrinsicFunctionName(st->symbol()->identifier()))
                    {
                        SgSymbol *procS = OriginalSymbol(st->symbol());
                        if (cp->variant() != MODULE_STMT)
                        {
                            if (st->symbol() != procS)
                            {
                                //printf(":: var %d, line %d, change %s -> %s\n", st->variant(), st->lineNumber(), st->symbol()->identifier(), procS->identifier());
                                st->symbol()->addAttribute(VARIABLE_NAME, procS, sizeof(SgSymbol));
                                st->setSymbol(*procS);
                            }
                        }
                        else
                            changeNameOfModuleFunc(procS->identifier(), st->symbol(), modsInfo, cp);
                    }
                }
                else
                    for (int z = 0; z < 3; ++z)
                        correctModuleProcNamesEx(st->expr(z), cp, modsInfo);
            }
        }
    }
}

static void restoreInFunc(SgExpression *ex)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            const vector<char*> attrs = getAttributes<SgSymbol*, char*>(ex->symbol(), set<int>({ VARIABLE_NAME }));
            if (attrs.size() > 0)
            {
                if (attrs.size() != 1)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                ex->symbol()->changeName(attrs[0]);
            }
        }

        restoreInFunc(ex->lhs());
        restoreInFunc(ex->rhs());
    }
}

void restoreCorrectedModuleProcNames(SgFile *file)
{
    vector<SgStatement*> modules;
    findModulesInFile(file, modules);

    if (modules.size() == 0)
        return;

    for (auto &mod : modules)
    {
        const string modName = mod->symbol()->identifier();
        for (SgStatement *st = mod->lexNext(); st != mod->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == PROC_HEDR || st->variant() == FUNC_HEDR)
            {                
                const vector<char*> attrs = getAttributes<SgSymbol*, char*>(st->symbol(), set<int>({ VARIABLE_NAME }));
                if (attrs.size() != 1)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                st->symbol()->changeName(attrs[0]);
            }
        }
    }

    for (int z = 0; z < file->numberOfFunctions(); ++z)
    {
        SgStatement *func = file->functions(z);
        for (SgStatement *st = func->lexNext(); st != func->lastNodeOfStmt(); st = st->lexNext())
        {
            if (isSgExecutableStatement(st))
            {
                if (st->variant() == PROC_STAT)
                {
                    const vector<char*> attrs = getAttributes<SgSymbol*, char*>(st->symbol(), set<int>({ VARIABLE_NAME }));
                    if (attrs.size() > 0)
                    {
                        if (attrs.size() != 1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        st->symbol()->changeName(attrs[0]);
                    }
                }
                else
                    for (int z = 0; z < 3; ++z)
                        restoreInFunc(st->expr(z));
            }
        }
    }
}

bool checkArgumentsDeclaration(SgProject *project,
                               const map<string, vector<FuncInfo*>> &allFuncInfo,
                               const vector<ParallelRegion*> &regions, 
                               map<string, vector<Messages>> &SPF_messages)
{
    bool error = false;

    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    for (int i = 0; i < project->numberOfFiles(); ++i)
    {
        SgFile *file = &(project->file(i));

        if (SgFile::switchToFile(file->filename()) != -1)
        {
            for (int j = 0; j < file->numberOfFunctions(); ++j)
            {
                SgStatement *st = file->functions(j);
                SgStatement *lastNode = st->lastNodeOfStmt();

                if (st->variant() != PROG_HEDR)
                {
                    SgProgHedrStmt *procFuncHedr = ((SgProgHedrStmt*)st);

                    for (int k = 0; k < procFuncHedr->numberOfParameters(); ++k)
                    {
                        SgSymbol *symb = procFuncHedr->parameter(k);

                        if (symb)
                        {
                            SgStatement *decl = declaratedInStmt(symb, NULL, false);

                            if (!decl)
                            {
                                FuncInfo *func = getFuncInfo(funcMap, st->symbol()->identifier());
                                checkNull(func, convertFileName(__FILE__).c_str(), __LINE__);

                                __spf_print(1, "function's argument '%s' does not have declaration statement on line %d\n", symb->identifier(), st->lineNumber());

                                string message;
                                __spf_printToBuf(message, "function's argument '%s' does not have declaration statement", symb->identifier());

                                if (func->isInRegion())
                                {
                                    error = true;
                                    getObjectForFileFromMap(file->filename(), SPF_messages).push_back(Messages(ERROR, st->lineNumber(), message, 1045));
                                }
                                else
                                   getObjectForFileFromMap(file->filename(), SPF_messages).push_back(Messages(WARR, st->lineNumber(), message, 1045));
                            }
                        }
                    }
                }
            }
        }
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    return error;
}