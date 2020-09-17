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
#include "../ParallelizationRegions/ParRegions.h"

#include "../GraphCall/graph_calls_func.h"

using std::vector;
using std::string;
using std::wstring;
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
                //CONVERT all decls to F90
                //if (is_assign && st->variant() == VAR_DECL && !st->expr(2))
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
            bool hasTemplateUse = false;
            set<DIST::Array*> needToAdd;

            for (auto st = func; st != func->lastNodeOfStmt(); st = st->lexNext())
            {
                if (isSgExecutableStatement(st))
                    break;

                if (st->variant() == USE_STMT)
                {
                    SgExpression *ex = st->expr(0);
                    string modName = st->symbol()->identifier();

                    auto it = mod.find(modName);
                    if (modName == "dvmh_Template_Mod")
                    {
                        hasTemplateUse = true;
                        break;
                    }
                        
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

                        //set<DIST::Array*> needToAdd;
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

                        /*for (auto &array : needToAdd)
                        {
                            if (allS.find(array->GetShortName()) == allS.end())
                            {
                                SgExpression *newEx = new SgExpression(EXPR_LIST);
                                newEx->setRhs(ex->lhs());
                                auto s = findSymbolOrCreate(file, array->GetShortName());
                                newEx->setLhs(new SgExpression(RENAME_NODE, new SgVarRefExp(s), NULL, s));
                                ex->setLhs(newEx);
                            }
                        }*/
                    }
                }
            }

            if (!hasTemplateUse && needToAdd.size())
            {
                SgStatement* useSt = new SgStatement(USE_STMT);
                useSt->setSymbol(*findSymbolOrCreate(file, "dvmh_Template_Mod"));
                useSt->setlineNumber(getNextNegativeLineNumber());

                func->insertStmtBefore(*useSt, *func);
            }
        }
    }
}

void fillUseStatement(SgStatement *st, set<string> &useMod,
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

static map<string, map<SgSymbol*, pair<string, string>>> moduleRenameByFile;
static map<SgSymbol*, pair<string, string>>* currModuleRename = NULL;

string getOrigName(const string& file, const string& s)
{
    auto it = moduleRenameByFile.find(file);
    if (it != moduleRenameByFile.end())
        for (auto& elem : it->second)
            if (elem.second.second == s)
                return elem.second.first;
    return s;
}

static void changeNameOfModuleFunc(string funcName, SgSymbol *curr, const map<string, ModuleInfo> &modsInfo, SgStatement *cp,
                                   const set<string> &globalF)
{
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

    string newName = "";

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

        // find in current module
        if (filter.size() == 0)
        {
            auto funcs = info.functions;
            for (auto &func : funcs)
            {
                if (func == funcName)
                    filter.insert(make_pair(cp->symbol()->identifier(), func));
            }
        }

        if (filter.size() == 1)
            callInMod = (*filter.begin()).first;
        else
        {
            //XXX
            if (funcName.find("::") != string::npos)
                newName = funcName;
            else
            {
                //extern function call, TODO: check this
                if (globalF.find(funcName) == globalF.end())
                    __spf_print(1, "  unknown func: '%s' in '%s' location\n", funcName.c_str(), cp->symbol()->identifier());
                return;
                //printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }
    }

    if (newName == "")
        newName = (byUseName == "" ? callInMod + "::" + string(curr->identifier()) : byUseName);

    if (currModuleRename->find(curr) == currModuleRename->end())
    {
        (*currModuleRename)[curr] = make_pair(curr->identifier(), newName);
        curr->changeName(newName.c_str());     
    }
}

static void moduleUses(SgStatement *st, set<string> &ret)
{
    while (st)
    {
        if (st->variant() == CONTAINS_STMT)
            break;
        if (isSgExecutableStatement(st))
            break;
        if (st->variant() == USE_STMT)
            ret.insert(st->symbol()->identifier());
        st = st->lexNext();
    }
}

//TODO: need to additional check of function name
static void extendCheckAndFindProcName(map<string, set<string>> &containsFuncs, const set<string> &globalFuncs, 
                                       const map<string, set<string>> &moduleFuncs, SgStatement *st, SgSymbol *procS,
                                       set<SgSymbol*> &changed)
{
    SgStatement *currCP = st->controlParent();
    while (currCP->variant() != PROG_HEDR && currCP->variant() != FUNC_HEDR && currCP->variant() != PROC_HEDR)
        currCP = currCP->controlParent();

    SgStatement *realCP = currCP;
    if (realCP->controlParent()->variant() != GLOBAL)
        realCP = realCP->controlParent();

    const string currName = procS->identifier();

    const string parentName = realCP->symbol()->identifier();
    auto itP = containsFuncs.find(parentName);
    //XXX
    if (itP == containsFuncs.end())
        itP = containsFuncs.insert(itP, make_pair(parentName, set<string>()));

    //in local scope
    auto itL = itP->second.find(currName);
    if (itL != itP->second.end())
        return;

    //in global scope
    auto itG = globalFuncs.find(currName);
    if (itG != globalFuncs.end())
        return;

    set<string> foundInMod;
    set<string> modUses;
    moduleUses(currCP, modUses);
    if (currCP != realCP)
        moduleUses(realCP, modUses);

    // in module, XXX, TODO
    for (auto &mod : moduleFuncs)
    {
        if (mod.second.find(currName) != mod.second.end())
            if (modUses.find(mod.first) != modUses.end())
                foundInMod.insert(mod.first);
    }

    if (foundInMod.size() > 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    else if (foundInMod.size() == 0)
        return;

    if (currModuleRename->find(procS) == currModuleRename->end())
    {
        (*currModuleRename)[procS] = make_pair(procS->identifier(), *foundInMod.begin() + "::" + procS->identifier());
        procS->changeName((*foundInMod.begin() + "::" + procS->identifier()).c_str());
    }   
    changed.insert(procS);
}

static map<SgSymbol*, SgSymbol*> byUseMapping;
static void correctModuleProcNamesEx(SgExpression *ex, SgStatement *st, SgStatement *cp, const map<string, ModuleInfo> &modsInfo,
                                     map<string, set<string>> &containsFuncs, const set<string> &globalFuncs, 
                                     const map<string, set<string>> &moduleFuncs, set<SgSymbol*> &changed, const set<string> &globalF)
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
                    SgSymbol* toSwap = ex->symbol();
                    if (toSwap != procS)
                    {
                        //printf(":: var %d, line %d, change %s -> %s\n", st->variant(), st->lineNumber(), toSwap->identifier(), procS->identifier());
                        ex->setSymbol(*procS);
                        byUseMapping[procS] = toSwap;
                        byUseMapping[toSwap] = procS;
                    }
                    else if (changed.find(procS) == changed.end())
                        extendCheckAndFindProcName(containsFuncs, globalFuncs, moduleFuncs, st, procS, changed);
                }
                else
                    changeNameOfModuleFunc(procS->identifier(), ex->symbol(), modsInfo, cp, globalF);
            }
        }

        correctModuleProcNamesEx(ex->lhs(), st, cp, modsInfo, containsFuncs, globalFuncs, moduleFuncs, changed, globalF);
        correctModuleProcNamesEx(ex->rhs(), st, cp, modsInfo, containsFuncs, globalFuncs, moduleFuncs, changed, globalF);
    }
}

bool needToReplaceInterfaceName(SgStatement *interf)
{
    if (interf->variant() != INTERFACE_STMT)
        return false;

    bool allModulSynonim = true;
    for (auto st_l = interf->lexNext(); st_l != interf->lastNodeOfStmt(); st_l = st_l->lexNext())
        if (st_l->variant() != MODULE_PROC_STMT)
            allModulSynonim = false;
    return allModulSynonim;
}

void correctModuleProcNames(SgFile *file, const set<string> &globalF)
{
    currModuleRename = &moduleRenameByFile[file->filename()];

    vector<SgStatement*> modules;
    findModulesInFile(file, modules);

    map<string, ModuleInfo> modsInfo;
    map<string, set<string>> moduleFuncs;
    map<string, set<string>> containsFuncs;

    for (auto &mod : modules)
        moduleFuncs[mod->symbol()->identifier()] = set<string>();

    for (int z = 0; z < file->numberOfFunctions(); ++z)
    {
        SgStatement *func = file->functions(z);
        SgStatement *cp = func->controlParent();
        if (cp->variant() == MODULE_STMT)
        {
            set<string> &curr = moduleFuncs[cp->symbol()->identifier()];
            string key = func->symbol()->identifier();
            auto it = curr.find(key);
            if (it != curr.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            curr.insert(it, key);
        }
        else if (cp->variant() == PROC_HEDR || cp->variant() == FUNC_HEDR || cp->variant() == PROG_HEDR)
        {
            SgStatement *cpcp = cp->controlParent();
            string keyF = "";
            if (cpcp->variant() == GLOBAL)
                keyF = cp->symbol()->identifier();
            else if (cpcp->variant() == MODULE_STMT)
                keyF = string(cpcp->symbol()->identifier()) + "::" + cp->symbol()->identifier();

            auto itF = containsFuncs.find(keyF);
            if (itF == containsFuncs.end())
                itF = containsFuncs.insert(itF, make_pair(keyF, set<string>()));

            string keyAdd = func->symbol()->identifier();
            auto it = itF->second.find(keyAdd);
            if (it != itF->second.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            itF->second.insert(it, keyAdd);
        }
    }

    for (auto &mod : modules)
    {
        fillInfo(mod, modsInfo);
        const string modName = mod->symbol()->identifier();
        SgStatement* last = mod->lastNodeOfStmt();
        for (SgStatement *st = mod->lexNext(); st != last; st = st->lexNext())
        {
            bool needToTransform = false;
            if (st->variant() == PROC_HEDR || st->variant() == FUNC_HEDR)
                needToTransform = true;
            else if (st->variant() == INTERFACE_STMT)
                needToTransform = needToReplaceInterfaceName(st);

            if (needToTransform)
            {
                SgSymbol* s = st->symbol();
                modsInfo[modName].functions.insert(s->identifier());
                if (currModuleRename->find(s) == currModuleRename->end())
                {
                    (*currModuleRename)[s] = make_pair(s->identifier(), modName + "::" + s->identifier());
                    s->changeName((modName + "::" + s->identifier()).c_str());
                }
            }
        }
    }

    if (modules.size() == 0)
        return;

    map<string, set<string>> moduleMapUse;
    moduleMapUse = createMapOfModuleUses(file);

    set<string> globalFuncs;
    for (int z = 0; z < file->numberOfFunctions(); ++z)
    {
        SgStatement *func = file->functions(z);
        if (func->controlParent()->variant() == GLOBAL)
        {
            string key = func->symbol()->identifier();
            auto it = globalFuncs.find(key);
            if (it != globalFuncs.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            globalFuncs.insert(it, key);
        }
    }

    set<SgSymbol*> changed;
    for (int z = 0; z < file->numberOfFunctions(); ++z)
    {
        SgStatement *func = file->functions(z);
        for (SgStatement *st = func->lexNext(); st != func->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;

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
                            SgSymbol *toSwap = st->symbol();
                            if (toSwap != procS)
                            {
                                //printf(":: var %d, line %d, change %s -> %s\n", st->variant(), st->lineNumber(), toSwap->identifier(), procS->identifier());
                                st->addAttribute(VARIABLE_NAME, toSwap, sizeof(SgSymbol));
                                st->setSymbol(*procS);
                            }                           
                            else if (changed.find(procS) == changed.end())
                                extendCheckAndFindProcName(containsFuncs, globalFuncs, moduleFuncs, st, procS, changed);
                        }
                        else
                            changeNameOfModuleFunc(procS->identifier(), st->symbol(), modsInfo, cp, globalF);
                    }
                }
                else
                    for (int z = 0; z < 3; ++z)
                        correctModuleProcNamesEx(st->expr(z), st, cp, modsInfo, containsFuncs, globalFuncs, moduleFuncs, changed, globalF);
            }
        }
    }
}

static void rename(SgExpression* ex, const map<SgSymbol*, SgSymbol*>& orig_rename)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF || ex->variant() == VAR_REF)
        {
            SgSymbol* s = ex->symbol();
            SgSymbol* sOrig = OriginalSymbol(ex->symbol());
            if (s != sOrig)
            {
                auto itF = orig_rename.find(sOrig);
                if (itF != orig_rename.end() && string(s->identifier()) != itF->second->identifier())
                    ex->setSymbol(itF->second);
            }
        }

        rename(ex->lhs(), orig_rename);
        rename(ex->rhs(), orig_rename);
    }
}

static void fillOrigRename(SgExpression *ex, map<SgSymbol*, set<SgSymbol*>> &orig_rename)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF || ex->variant() == VAR_REF)
        {
            SgSymbol* s = ex->symbol();
            SgSymbol* sOrig = OriginalSymbol(ex->symbol());
            if (s != sOrig)
                orig_rename[sOrig].insert(s);
        }

        fillOrigRename(ex->lhs(), orig_rename);
        fillOrigRename(ex->rhs(), orig_rename);
    }
}

//switch to only one synonym for each module renaming 
void correctModuleSymbols(SgFile *file)
{
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *stF = file->functions(i);
        map<SgSymbol*, set<SgSymbol*>> orig_rename;

        for (auto st = stF->lexNext(); st != stF->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;
            if (!isSgExecutableStatement(st))
                continue;
            for (int z = 0; z < 3; ++z)
                fillOrigRename(st->expr(z), orig_rename);
        }

        map<SgSymbol*, SgSymbol*> orig_rename_2;
        for (auto& elem : orig_rename)
        {
            if (elem.second.size() > 1)
            {
                map<string, SgSymbol*> byName;
                for (auto& elem2 : elem.second)
                    byName[elem2->identifier()] = elem2;
                orig_rename_2[elem.first] = byName.begin()->second;
            }
        }
        
        if (orig_rename_2.size())
        {
            for (auto st = stF->lexNext(); st != stF->lastNodeOfStmt(); st = st->lexNext())
            {
                if (st->variant() == CONTAINS_STMT)
                    break;
                if (!isSgExecutableStatement(st))
                    continue;
                for (int z = 0; z < 3; ++z)
                    rename(st->expr(z), orig_rename_2);
            }
        }
    }
}

static void changeNameAndSwap(SgSymbol* s, set<SgSymbol*>& swaped)
{
    if (currModuleRename->find(s) == currModuleRename->end())
        return;

    if (swaped.find(s) != swaped.end())
        return;

    swaped.insert(s);
    pair<string, string> oldVal = (*currModuleRename)[s];

    s->changeName(oldVal.first.c_str());
    std::swap(oldVal.first, oldVal.second);
    (*currModuleRename)[s] = oldVal;
}

static void restoreInFunc(SgExpression *ex, set<SgSymbol*> &swaped, const map<SgSymbol*, SgSymbol*> &byUseMapping)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
        {
            SgSymbol *toSwap = ex->symbol();
            changeNameAndSwap(toSwap, swaped);

            auto it = byUseMapping.find(toSwap);
            if (it != byUseMapping.end())
                ex->setSymbol(it->second);
                        
        }
        restoreInFunc(ex->lhs(), swaped, byUseMapping);
        restoreInFunc(ex->rhs(), swaped, byUseMapping);
    }
}

void restoreCorrectedModuleProcNames(SgFile *file)
{
    
    currModuleRename = &moduleRenameByFile[file->filename()];
    /*for (SgSymbol *elem = file->firstSymbol(); elem; elem = elem->next())
    {
        SgSymbol *procS = OriginalSymbol(elem);
        if (procS != elem)
            byUseMapping[procS] = elem;
    }*/

    set<SgSymbol*> swaped;
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
                changeNameAndSwap(st->symbol(), swaped);
            else if (st->variant() == INTERFACE_STMT)
            {
                if (needToReplaceInterfaceName(st))
                    changeNameAndSwap(st->symbol(), swaped);
            }
        }
    }

    for (int z = 0; z < file->numberOfFunctions(); ++z)
    {
        SgStatement *func = file->functions(z);
        for (SgStatement *st = func->lexNext(); st != func->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == CONTAINS_STMT)
                break;

            if (isSgExecutableStatement(st))
            {
                if (st->variant() == PROC_STAT)
                {
                    if (string(st->symbol()->identifier()).find("_spf_") != string::npos)
                        continue;

                    changeNameAndSwap(st->symbol(), swaped);

                    const vector<SgSymbol*> attrs1 = getAttributes<SgStatement*, SgSymbol*>(st, set<int>({ VARIABLE_NAME }));
                    if (attrs1.size() > 0)
                    {
                        if (attrs1.size() != 1)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        SgSymbol *toSwap = st->symbol();
                        st->setSymbol(*attrs1[0]);

                        deleteAttributes(st, set<int>({ VARIABLE_NAME }));
                        st->addAttribute(VARIABLE_NAME, toSwap, sizeof(SgSymbol));
                    }
                }
                else
                    for (int z = 0; z < 3; ++z)
                        restoreInFunc(st->expr(z), swaped, byUseMapping);
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

                                wstring messageE, messageR;
                                __spf_printToLongBuf(messageE, L"function's argument '%s' does not have declaration statement", to_wstring(symb->identifier()).c_str());
#ifdef _WIN32
                                __spf_printToLongBuf(messageR, R81,
                                                     to_wstring(symb->identifier()).c_str(), to_wstring(func->funcName).c_str());
#endif

                                if (func->isInRegion())
                                {
                                    error = true;
                                    getObjectForFileFromMap(file->filename(), SPF_messages).push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1045));
                                }
                                else
                                   getObjectForFileFromMap(file->filename(), SPF_messages).push_back(Messages(WARR, st->lineNumber(), messageR, messageE, 1045));
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

static map<SgFile*, map<string, SgSymbol*>> copied;

static string createKey(const vector<string>& structS, const string& mainS)
{
    string new_name = "";
    for (int z = structS.size() - 1; z >= 0; --z)
        new_name += structS[z] + "_";
    return new_name + mainS;    
}

static void copySymbol(SgSymbol *&toCopy, SgSymbol *mainS, const vector<string> &structS, const int mainLineDecl, map<string, SgSymbol*> &copy)
{
    toCopy = &mainS->copy();
    const string new_name = createKey(structS, mainS->identifier());    
    toCopy->changeName(new_name.c_str());
    copy[new_name] = toCopy;

    SgStatement* decl = toCopy->makeVarDeclStmt();
    decl->setlineNumber(mainLineDecl);
    SgStatement *scope = mainS->scope();
    scope->insertStmtBefore(*decl, *scope->controlParent());
}

static SgExpression* replaceStructS(SgExpression *ex, map<string, SgSymbol*> &copy)
{
    SgExpression* retF = ex;
    if (ex)
    {
        if (ex->variant() == RECORD_REF)
        {
            SgSymbol* mainS = ex->rhs()->symbol();
            vector<string> structS;
            SgExpression* exS = ex->lhs();

            int lineDecl = -1;
            while (exS->variant() == RECORD_REF)
            {
                structS.push_back(exS->rhs()->symbol()->identifier());
                if (lineDecl == -1)
                {
                    auto declStat = exS->rhs()->symbol()->declaredInStmt();
                    if (declStat)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    lineDecl = declStat->lineNumber();
                }
                exS = exS->lhs();
            }
            structS.push_back(exS->symbol()->identifier());
            if (lineDecl == -1)
            {
                auto declStat = exS->symbol()->declaredInStmt();
                checkNull(declStat, convertFileName(__FILE__).c_str(), __LINE__);
                lineDecl = declStat->lineNumber();
            }

            SgSymbol* toCopy = NULL;
            string key = createKey(structS, mainS->identifier());
            if (copy.find(key) == copy.end())
                copySymbol(toCopy, mainS, structS, lineDecl, copy);
            else
                toCopy = copy[key];
           
            if (ex->rhs()->variant() == ARRAY_REF && ex->rhs()->type()->variant() != T_STRING)
                retF = new SgArrayRefExp(*toCopy);
            else
                retF = new SgVarRefExp(toCopy);

            if (ex->rhs()->lhs())
                retF->setLhs(ex->rhs()->lhs()->copy());
            if (ex->rhs()->rhs())
                retF->setRhs(ex->rhs()->rhs()->copy());
        }
        else
        {
            auto ret = replaceStructS(ex->lhs(), copy);
            if (ret != ex->lhs())
                ex->setLhs(ret);
            ret = replaceStructS(ex->rhs(), copy);
            if (ret != ex->rhs())
                ex->setRhs(ret);
        }
    }
    return retF;
}

void replaceDerivedAssigns(SgFile *file, SgStatement *stToCopy, SgStatement *insertB, const map<string, SgStatement*> &derivedTypesDecl)
{
    map<string, SgSymbol*> &copy = copied[file];

    SgExpression* left = stToCopy->expr(0);
    SgExpression* right = stToCopy->expr(1);

    vector<SgExpression*> structConstructor;
    if (right->variant() == STRUCTURE_CONSTRUCTOR)
    {        
        SgExprListExp *constr = (SgExprListExp *)right->lhs();
        
        for (int z = 0; z < constr->length(); ++z)
            structConstructor.push_back(constr->elem(z));
    }

    auto it = derivedTypesDecl.find(left->symbol()->type()->symbol()->identifier());
    if (it == derivedTypesDecl.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement* derived = it->second;
    vector<string> structSL;
    vector<string> structSR;
    structSL.push_back(left->symbol()->identifier());
    structSR.push_back(right->symbol()->identifier());

    int z = 0;
    for (auto st = derived->lexNext(); st != derived->lastNodeOfStmt(); st = st->lexNext())
    {        
        if (st->variant() == VAR_DECL || st->variant() == VAR_DECL_90)
        {
            SgVarDeclStmt *declStat = (SgVarDeclStmt*)st;
            for (int k = 0; k < declStat->numberOfSymbols(); ++k)
            {
                auto currS = declStat->symbol(k);
                string toFindL = string(left->symbol()->identifier()) + "_" + currS->identifier();
                string toFindR = string(right->symbol()->identifier()) + "_" + currS->identifier();
                SgSymbol *lS = NULL, *rS = NULL;
                for (auto &elem : copy)
                {
                    if (elem.second->identifier() == toFindL)
                        lS = elem.second;
                    else if (elem.second->identifier() == toFindR)
                        rS = elem.second;
                }
                if (!lS)
                    copySymbol(lS, currS, structSL, -2, copy);

                SgStatement *ass = NULL;
                if (structConstructor.size())
                    ass = new SgAssignStmt(*new SgVarRefExp(lS), structConstructor[z++]->copy());
                else
                {
                    if (!rS)
                        copySymbol(rS, currS, structSR, -2, copy);
                    ass = new SgAssignStmt(*new SgVarRefExp(lS), *new SgVarRefExp(rS));
                }
                ass->setProject(stToCopy->getProject());
                ass->setFileId(stToCopy->getFileId());
                ass->setlineNumber(getNextNegativeLineNumber());
                ass->setLocalLineNumber(stToCopy->lineNumber());
                insertB->insertStmtBefore(*ass, *insertB->controlParent());
            }
        }
    }
}

bool isDerivedAssign(SgStatement *st)
{
    if (st->variant() == ASSIGN_STAT)
    {
        auto left = st->expr(0);
        auto right = st->expr(1);
        if (left->variant() == VAR_REF && (right->variant() == VAR_REF || right->variant() == CONST_REF))
        {
            bool nul = !(left->lhs()) || !(left->rhs()) || !(right->lhs()) || !(right->rhs());
            if (nul)
            {
                SgType* lType = left->symbol()->type();
                SgType* rType = right->symbol()->type();
                if (lType == NULL || rType == NULL)
                    return false;

                if (lType->variant() == T_DERIVED_TYPE && rType->variant() == T_DERIVED_TYPE &&
                    !lType->hasBaseType() && !rType->hasBaseType())
                {
                    if (lType->symbol() == rType->symbol())
                    {
                        if (right->variant() == CONST_REF)
                        {
                            SgConstantSymb *sc = isSgConstantSymb(right->symbol());
                            if (sc->constantValue())
                                st->setExpression(1, sc->constantValue());                            
                        }                        
                        return true;
                    }
                }
            }
        }
        else if (left->variant() == VAR_REF && right->variant() == STRUCTURE_CONSTRUCTOR)
        {
            SgType* lType = left->symbol()->type();
            if (lType == NULL)
                return false;

            if (lType->variant() == T_DERIVED_TYPE && !lType->hasBaseType())
                return true;            
        }
    }

    return false;
}

map<string, SgStatement*> createDerivedTypeDeclMap(SgStatement *forS)
{
    map<string, SgStatement*> derivedTypesDecl;
    
    for (SgStatement* st = forS; st != forS->lastNodeOfStmt(); st = st->lexNext())
    {
        if (!isSgExecutableStatement(st))
        {
            if (st->variant() == STRUCT_DECL)
                derivedTypesDecl[st->symbol()->identifier()] = st;
            continue;
        }
        else
            break;
    }
    return derivedTypesDecl;
}

void replaceStructuresToSimpleTypes(SgFile *file)
{
    copied[file] = map<string, SgSymbol*>();

    int numF = file->numberOfFunctions();
    for (int z = 0; z < numF; ++z)
    {        
        for (SgStatement* st = file->functions(z); st != file->functions(z)->lastNodeOfStmt(); st = st->lexNext())
        {
            if (!isSgExecutableStatement(st))
                continue;

            for (int z = 0; z < 3; ++z)
            {
                auto ret = replaceStructS(st->expr(z), copied[file]);
                if (ret != st->expr(z))
                    st->setExpression(z, ret);
            }
        }

        map<string, SgStatement*> derivedTypesDecl = createDerivedTypeDeclMap(file->functions(z));
        for (SgStatement* st = file->functions(z); st != file->functions(z)->lastNodeOfStmt(); st = st->lexNext())
        {
            if (!isSgExecutableStatement(st))
                continue;

            if (isDerivedAssign(st))
                replaceDerivedAssigns(file, st, st, derivedTypesDecl);
        }
    }
}

void removeExecutableFromModuleDeclaration(SgFile *current, const set<string> &filesInProj)
{
    const string currF = current->filename();
    set<string> moduleInFile;
    for (SgStatement* st = current->firstStatement(); st; st = st->lexNext())
    {
        if (st->variant() == MODULE_STMT && st->fileName() != currF)
            if (filesInProj.find(st->fileName()) != filesInProj.end())
                moduleInFile.insert(st->fileName());
    }

    vector<SgStatement*> toDel;
    for (SgStatement* st = current->firstStatement(); st; st = st->lexNext())
    {
        if (isSgProgHedrStmt(st))
            if (moduleInFile.find(st->fileName()) != moduleInFile.end())
                toDel.push_back(st);
    }

    for (auto& elem : toDel)
        elem->deleteStmt();
}
