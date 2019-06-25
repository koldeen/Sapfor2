#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "dvm.h"

#include "../Distribution/GraphCSR.h"
#include "../Distribution/Arrays.h"
#include "../Distribution/Distribution.h"
#include "../Distribution/DvmhDirective_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../GraphCall/graph_calls_func.h"

#include "../Utils/errors.h"
#include "loop_analyzer.h"
#include "directive_parser.h"
#include "../Utils/SgUtils.h"
#include "../Sapfor.h"

using std::string;
using std::wstring;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::tuple;
using std::make_pair;
using std::make_tuple;

//the size of vector indiceates type of DVM_DIR
static SgStatement* createStatFromExprs(const vector<Expression*> &exprs)
{
    SgStatement *result = NULL;
    if (exprs.size() == 3)
        result = new SgStatement(DVM_PARALLEL_ON_DIR, NULL, NULL, NULL, NULL, NULL);
    else if (exprs.size() == 4)
        result = new SgStatement(DVM_REDISTRIBUTE_DIR, NULL, NULL, NULL, NULL, NULL);
    else if (exprs.size() == 5)
        result = new SgStatement(DVM_REALIGN_DIR, NULL, NULL, NULL, NULL, NULL);
    else if (exprs.size() == 6)
        result = new SgStatement(DVM_DISTRIBUTE_DIR, NULL, NULL, NULL, NULL, NULL);
    else if (exprs.size() == 7)
        result = new SgStatement(HPF_TEMPLATE_STAT, NULL, NULL, NULL, NULL, NULL);
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    
    for (int i = 0; i < 3; ++i)
        if (exprs[i])
            result->setExpression(i, *exprs[i]);
    return result;
}

static void filterInsertMap(map<int, vector<vector<Expression*>>> &toInsertMap)
{
    for (auto it = toInsertMap.begin(); it != toInsertMap.end(); ++it)
    {
        vector<vector<Expression*>> newVal;
        for (int z = 1; z < it->second.size(); ++z)
        {
            //removeDoubleRedistribute
            if (it->second[z].size() == 4)
                if (it->second[z].size() == it->second[z - 1].size())
                    continue;
            newVal.push_back(it->second[z - 1]);
        }
        newVal.push_back(it->second.back());

        //sort by type
        map<int, vector<vector<Expression*>>> toSort;
        for (auto &elem : newVal)
            toSort[elem.size()].push_back(elem);

        newVal.clear();
        for (auto itR = toSort.rbegin(); itR != toSort.rend(); itR++)
        {
            for (auto &elem : itR->second)
                newVal.push_back(elem);
        }
        it->second = newVal;
    }
}

// TODO: optimize REDISTR dirs with CFG
static set<SgFile*> genVersionDone;
void insertDirectiveToFile(SgFile *file, const char *fin_name, const vector<pair<int, pair<string, vector<Expression*>>>> &toInsert, 
                           const bool extractDir, vector<Messages> &messagesForFile)
{
    /*for (int i = 0; i < toInsert.size(); ++i)
        printf("%d -> %s\n", toInsert[i].first, toInsert[i].second.first.c_str());*/
    if (genVersionDone.find(file) == genVersionDone.end())
    {
        file->firstStatement()->addComment(printVersionAsFortranComm().c_str());
        genVersionDone.insert(file);
    }

    map<int, vector<vector<Expression*>>> toInsertMap;
    for (int i = 0; i < toInsert.size(); ++i)
    {
        auto it = toInsertMap.find(toInsert[i].first);
        if (it == toInsertMap.end())
        {
            vector<vector<Expression*>> tmp;
            tmp.push_back(toInsert[i].second.second);
            toInsertMap.insert(it, make_pair(toInsert[i].first, tmp));
        }
        else
            it->second.push_back(toInsert[i].second.second);
    }

    filterInsertMap(toInsertMap);
    vector<SgStatement*> toDel;

    vector<SgStatement*> modulesAndFuncs;
    getModulesAndFunctions(file, modulesAndFuncs);

    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        SgStatement *st = modulesAndFuncs[i];
        SgStatement *lastNode = st->lastNodeOfStmt();

        if (extractDir && st->variant() == MODULE_STMT)
        {
            if (st->symbol()->identifier() == string("dvmh_Template_Mod"))
            {
                st->deleteStmt();
                continue;
            }
        }

        int numSt = 0;
        do
        {
            if (st->variant() == CONTAINS_STMT)
                break;

            currProcessing.second = st->lineNumber();
            if (numSt != 0)
                st = st->lexNext();

            if (st == NULL)
            {
#ifdef _WIN32
                messagesForFile.push_back(Messages(ERROR, 1, R128, L"internal error in analysis, parallel directives will not be generated for this file!", 3008));
#endif
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (!strcmp(st->fileName(), fin_name))
            {
                auto it = toInsertMap.find(st->lineNumber());
                if (it != toInsertMap.end())
                {
                    if (extractDir == false)
                    {
                        for (int i1 = 0; i1 < it->second.size(); ++i1)
                        {
                            SgStatement *dirToInsert = createStatFromExprs((it->second[i1]));
                            const int varSt = st->variant();
                            if (varSt == PROC_HEDR || varSt == PROG_HEDR || varSt == FUNC_HEDR || varSt == MODULE_STMT)
                                st->insertStmtAfter(*dirToInsert, *st);
                            else
                                st->insertStmtBefore(*dirToInsert, *(st->controlParent()));
                            if (st->comments())
                            {
                                char *comms = st->comments();
                                string comments(comms);
                                st->delComments();

                                st->lexPrev()->addComment(comments.c_str());
                            }
                        }
                    }
                    toInsertMap.erase(it);
                }
            }

            if (extractDir)
            {
                const int var = st->variant();
                if (var == DVM_PARALLEL_ON_DIR ||
                    var == DVM_REDISTRIBUTE_DIR ||
                    var == DVM_REALIGN_DIR ||
                    var == DVM_REMOTE_ACCESS_DIR ||
                    var == DVM_SHADOW_DIR ||
                    var == DVM_INHERIT_DIR ||
                    var == DVM_DYNAMIC_DIR ||
                    (var == USE_STMT && st->lineNumber() < 0) ||
                    var == HPF_TEMPLATE_STAT || 
                    var == DVM_ALIGN_DIR ||
                    var == DVM_DISTRIBUTE_DIR || 
                    var == DVM_VAR_DECL)
                {
                    toDel.push_back(st);

                    //move comment to next statement
                    if (st->comments())
                    {
                        char *comms = st->comments();
                        string comments(comms);
                        st->delComments();

                        SgStatement *next = st->lexNext();
                        if (next)
                            next->addComment(comments.c_str());
                    }
                }
            }
            numSt++;
        } while (st != lastNode);

        if (extractDir)
        {
            for (int k = 0; k < toDel.size(); ++k)
            {
                if (toDel[k]->lineNumber() > 0)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                toDel[k]->deleteStmt();
            }
        }
    }
}

static void moveComment(SgStatement *elem, const string addNew = "")
{
    string comms = "";
    if (elem->comments())
        comms = elem->comments();
    comms += addNew;

    if (comms != "")
    {
        auto toAddComm = elem;
        while (toAddComm)
        {
            toAddComm = toAddComm->lexNext();
            if (toAddComm && !isDVM_stat(toAddComm))
                break;
        }
        if (toAddComm->lexNext() == NULL)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        
        string comms2 = "";
        if (toAddComm->comments())
            comms2 = toAddComm->comments();
        comms += comms2;

        if (comms != "")
            toAddComm->setComments(comms.c_str());
    }
}

static void replaceComment(string &dir, const char *firstChar)
{
    const string templ = firstChar + string("DVM$");
    size_t offset = 0;
    for (; ; )
    {
        offset = dir.find(templ, offset);
        if (offset == string::npos)
            break;
        else
        {
            dir.insert(offset + 1, " ");
            offset += 6;
        }
    }
}

void removeDvmDirectives(SgFile *file, const bool toComment)
{
    vector<SgStatement*> toDel;
    const string currFile = file->filename();

    vector<SgStatement*> toProcess;
    getModulesAndFunctions(file, toProcess);
    for (int i = 0; i < toProcess.size(); ++i)
    {
        SgStatement *st = toProcess[i];
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
            currProcessing.second = st->lineNumber();
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            const int var = st->variant();
            //for details see dvm_tag.h
            if ((var >= 146 && var <= 149) ||
                (var >= 211 && var <= 224) ||
                (var >= 247 && var <= 249) ||
                (var >= 605 && var <= 640) ||
                (var >= 900 && var <= 949) ||
                (var >= 296 && var <= 299) ||
                (var == 277))
            {
                if (st->fileName() == currFile)
                    toDel.push_back(st);
            }

            st = st->lexNext();
        }
    }

    if (toComment)
    {
        for (auto &elem : toDel)
        {
            currProcessing.second = elem->lineNumber();

            moveComment(elem);
            elem->delComments();

            char *tmp = elem->unparse();
            if (tmp == NULL)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            string dir(tmp);
            convertToUpper(dir);
            
            replaceComment(dir, "!");
            replaceComment(dir, "C");
            
            moveComment(elem, dir);
            elem->deleteStmt();
        }
    }
    else
    {
        for (auto &elem : toDel)
        {
            currProcessing.second = elem->lineNumber();

            moveComment(elem);
            elem->deleteStmt();
        }
    }
}

static inline pair<string, SgExpression*> genBoundsOfDim(const pair<int, int> &intBounds, const pair<Expression*, Expression*> &exprBounds)
{
    if (intBounds.first > intBounds.second)
    {
        if (exprBounds.first == NULL || exprBounds.second == NULL)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        else
        {
            return make_pair(string(exprBounds.first->unparse()) + ":" + string(exprBounds.second->unparse()), 
                             new SgExpression(DDOT, exprBounds.first, exprBounds.second, NULL));
        }
    }
    else
        return make_pair(std::to_string(intBounds.first) + ":" + std::to_string(intBounds.second),
                         new SgExpression(DDOT, new SgValueExp(intBounds.first), new SgValueExp(intBounds.second), NULL));
}

static inline pair<string, SgStatement*> genTemplateDelc(DIST::Array *templ, const string &name, SgFile *file, SgStatement *module = NULL, bool isMain = false)
{
    string templDecl = (module == NULL) ? "!DVM$ TEMPLATE, COMMON :: " : "!DVM$ TEMPLATE ";
    SgStatement* templDeclSt = NULL;

    if (module == NULL)
        templDeclSt = new SgStatement(DVM_VAR_DECL);
    else
        templDeclSt = new SgStatement(HPF_TEMPLATE_STAT);

    if (module && templ->IsTemplate() && !templ->IsLoopArray())
        templ->ChangeLocation(DIST::l_MODULE, module->symbol()->identifier());
    
    const vector<pair<int, int>> &sizes = templ->GetSizes();
    const auto &sizesExpr = templ->GetSizesExpr();
        
    for (auto &size : sizes)
    {
        if (templ->IsLoopArray())
        {
            // TODO: move gen sizes to TEMPLATE CREATE directive immediately before parallel loop
            bool ok = true;
            for (auto &elem : sizesExpr)
                if (elem.first.first == NULL || elem.second.first == NULL)
                    ok = false;

            if (size.first > size.second && module == NULL && !ok)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        else
        {
            if (size.first > size.second)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
    
    SgExprListExp *listDim = new SgExprListExp();
    templDecl += name + "(";
    for (int z = 0; z < sizes.size(); ++z)
    {
        auto bounds = genBoundsOfDim(sizes[z], make_pair(sizesExpr[z].first.first, sizesExpr[z].second.first));
        templDecl += bounds.first;
        if (z == 0)
            listDim->setLhs(bounds.second);
        else
            listDim->append(*bounds.second);

        if (z != sizes.size() - 1)
            templDecl += ",";
    }
    templDecl += ")\n";
    if (module != NULL)
        templDeclSt->setExpression(0, new SgArrayRefExp(*findSymbolOrCreate(file, name, new SgArrayType(*SgTypeInt())), *listDim));
    else 
        templDeclSt->setExpression(0, new SgExpression(EXPR_LIST, new SgArrayRefExp(*findSymbolOrCreate(file, name, new SgArrayType(*SgTypeInt())), *listDim), NULL, NULL));
    if (module == NULL)
        templDeclSt->setExpression(2, new SgExpression(EXPR_LIST, new SgExpression(TEMPLATE_OP), new SgExpression(EXPR_LIST, new SgExpression(COMMON_OP), NULL, NULL), NULL));    

    return make_pair(templDecl, templDeclSt);
}

static inline pair<string, SgStatement*> 
    genTemplateDistr(DIST::Array *array, const string &name, const vector<string> &distrRules, const vector<vector<dist>> &distrRulesSt,
                     const int regionId, const int templIdx, bool isMain, SgFile *file)
{
    auto newOrder = array->GetNewTemplateDimsOrder();
    //TODO:!!!
    //"!DVM$ DISTRIBUTE :: " + templ->GetShortName() + "\n";
    SgExpression *ex1 = new SgVarRefExp(*findSymbolOrCreate(file, name));
    SgExprListExp *ex2 = new SgExprListExp();
        
    for (int z = 0; z < distrRulesSt[templIdx].size(); ++z)
    {
        string val = "";
        if (newOrder.size() == 0)
        {
            if (distrRulesSt[templIdx][z] == dist::BLOCK)
                val = "BLOCK";
            else
                val = "*";
        }
        else
        {
            if (distrRulesSt[templIdx][newOrder[z]] == dist::BLOCK)
                val = "BLOCK";
            else
                val = "*";
        }

        if (z == 0)
            ex2->setLhs(new SgKeywordValExp(val.c_str()));
        else
            ex2->append(*new SgKeywordValExp(val.c_str()));
    }
    SgStatement *distrSt = new SgStatement(DVM_DISTRIBUTE_DIR, NULL, NULL, ex1, ex2, NULL);
    return make_pair("!DVM$ DISTRIBUTE " + distrRules[templIdx] + "\n", distrSt);
}

static pair<string, SgStatement*> genDynamicDecl(DIST::Array *templ, SgFile *file)
{
    auto allClones = templ->GetAllClones();
    string templDyn = "!DVM$ DYNAMIC " + templ->GetShortName();

    for (auto &elem : allClones)
        templDyn += ", " + elem.second;
    templDyn += "\n";

    SgStatement* templDynSt = NULL;

    if (allClones.size() == 0)
        templDynSt = new SgStatement(DVM_DYNAMIC_DIR, NULL, NULL, new SgVarRefExp(*findSymbolOrCreate(file, templ->GetShortName())), NULL, NULL);
    else
    {
        SgExprListExp* list = new SgExprListExp();
        list->setLhs(new SgVarRefExp(*findSymbolOrCreate(file, templ->GetShortName())));
        for (auto& elem : allClones)
            list->append(*new SgVarRefExp(*findSymbolOrCreate(file, elem.second)));
        templDynSt = new SgStatement(DVM_DYNAMIC_DIR, NULL, NULL, list, NULL, NULL);
    }

    return make_pair(templDyn, templDynSt);
}

static inline int findTeplatePosition(const DIST::Array *templ, const DataDirective &dataDir)
{
    int templIdx = -1;
    const string templName = templ->GetShortName();
    for (int z = 0; z < dataDir.distrRules.size(); ++z)
    {
        if (dataDir.distrRules[z].first->GetShortName() == templName)
        {
            templIdx = z;
            break;
        }
    }

    if (templIdx == -1)
    {
        __spf_print(1, "can not find template position ['%s']\n", templName.c_str());
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
        
    return templIdx;
}

static inline DIST::Array* findLinkWithTemplate(DIST::Array *alignArray, const DIST::Arrays<int> &allArrays,
                                                DIST::GraphCSR<int, double, attrType> &reducedG, const int regionId)
{
    DIST::Array *templ = NULL;

    vector<tuple<DIST::Array*, int, pair<int, int>>> links;
    reducedG.GetAlignRuleWithTemplate(alignArray, allArrays, links, regionId);

    for (int i = 0; i < links.size(); ++i)
    {
        templ = std::get<0>(links[i]);
        if (templ)
            break;
    }

    return templ;
}

static string createFullTemplateDir(const tuple<string, string, string> &templDir)
{
    string fullDir = "";
    if (!out_free_form)
    {        
        fullDir += splitDirectiveFull(std::get<0>(templDir));
        fullDir += splitDirectiveFull(std::get<1>(templDir));
        fullDir += splitDirectiveFull(std::get<2>(templDir));
    }
    else
        fullDir += std::get<0>(templDir) + std::get<1>(templDir) + std::get<2>(templDir);
    
    return fullDir;
}

struct templateDir
{
    templateDir() { isTemplateInModule = false; }

    pair<string, vector<SgStatement*>> templDecl;
    pair<string, vector<SgStatement*>> templDist;
    pair<string, SgStatement*> templDyn;
    bool isTemplateInModule;
};

static pair<templateDir, string>
    getNewTemplateDirective(DIST::Array *alignArray, const DIST::Arrays<int> &allArrays,
                            DIST::GraphCSR<int, double, attrType> &reducedG,
                            const DataDirective &dataDir, const vector<string> &distrRules,
                            const vector<vector<dist>> &distrRulesSt,
                            const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                            const int regionId, SgStatement *module, bool isMain, SgFile *file)
{   
    DIST::Array *templ = findLinkWithTemplate(alignArray, allArrays, reducedG, regionId);   
    bool templDynSt = false;
    string lastReturn = "";
    
    //checkNull(templ, convertFileName(__FILE__).c_str(), __LINE__);
    if (templ == NULL)
    {
        set<DIST::Array*> realArrayRefs;
        getRealArrayRefs(alignArray, alignArray, realArrayRefs, arrayLinksByFuncCalls);

        vector<DIST::Array*> templates;
        for (auto &array : realArrayRefs)
            templates.push_back(findLinkWithTemplate(array, allArrays, reducedG, regionId));
        
        if (templates.size() == 0)
        {
            __spf_print(1, "can not find templates\n");
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        else if (templates.size() == 1)
            templ = templates[0];
        else
        {
            templ = templates[0];
            for (auto &t : templates)
            {
                if (t != templ)
                {
                    __spf_print(1, "find more then one template: %s and %s\n", t->GetShortName().c_str(), templ->GetShortName().c_str());
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
            }
        }
        
        lastReturn = "!DVM$ INHERIT\n";
    }
    else
        lastReturn = templ->GetShortName();

    auto allClones = templ->GetAllClones();
    templateDir retDir;

    int templIdx = findTeplatePosition(templ, dataDir);

    auto templDecl = genTemplateDelc(templ, templ->GetShortName(), file, module, isMain);
    retDir.templDecl.first = templDecl.first;
    retDir.templDecl.second.push_back(templDecl.second);
    for (auto &elem : allClones)
    {
        auto templDecl = genTemplateDelc(templ, elem.second, file, module, isMain);
        retDir.templDecl.first += templDecl.first;
        retDir.templDecl.second.push_back(templDecl.second);
    }

    auto templDist = genTemplateDistr(templ, templ->GetShortName(), distrRules, distrRulesSt, regionId, templIdx, isMain || module != NULL, file);
    retDir.templDist.first = templDist.first;
    retDir.templDist.second.push_back(templDist.second);

    if (templ->GetLocation().first == DIST::l_MODULE)
        retDir.isTemplateInModule = true;

    for (auto &elem : allClones)
    {
        vector<vector<dist>> tmpRuleSt = { elem.first };
        
        string strRule = elem.second + "(";
        for (int z = 0; z < elem.first.size(); ++z)
        {
            if (z != 0)
                strRule += ",";
            if (elem.first[z] == BLOCK)
                strRule += "BLOCK";
            else if (elem.first[z] == NONE)
                strRule += "*";
            else
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        strRule += ")";
        vector<string> tmpStrRule = { strRule };

        auto templDist = genTemplateDistr(templ, elem.second, tmpStrRule, tmpRuleSt, regionId, 0, isMain || module != NULL, file);
        retDir.templDist.first += templDist.first;
        retDir.templDist.second.push_back(templDist.second);
    }

    retDir.templDyn = genDynamicDecl(templ, file);

    return make_pair(retDir, lastReturn);
}

static pair<DIST::Array*, string>
getNewDirective(const string &fullArrayName, 
                const vector<string> &distrRules,
                const vector<string> &alignRules,
                const DataDirective &dataDir,
                const map<string, set<SgSymbol*>> &byUse,
                bool alignToRealign)
{
    string out = "";
    DIST::Array* outA = NULL;

    for (int i = 0; i < dataDir.distrRules.size(); ++i)
    {
        if (dataDir.distrRules[i].first->GetName() == fullArrayName)
        {
            out += "!DVM$ DISTRIBUTE " + distrRules[i] + "\n";
            if (!out_free_form)
                out = splitDirective(out);

            return make_pair(dataDir.distrRules[i].first, out);
        }
    }

    for (int i = 0; i < dataDir.alignRules.size(); ++i)
    {
        if (dataDir.alignRules[i].alignArray->GetName() == fullArrayName)
        {
            string rule = alignRules[i];
            if (alignToRealign)
            {
                auto it = rule.find("ALIGN");
                while (it != string::npos)
                {
                    rule = rule.replace(it, 5, "REALIGN");
                    it = rule.find("ALIGN", it + 7);
                }

                for (auto byUseElem : byUse)
                {
                    if (byUseElem.second.size() == 0)
                        continue;

                    it = rule.find(byUseElem.first);
                    if (it != string::npos)
                    {
                        if (rule[it + byUseElem.first.size()] == '(' && rule[it - 1] == ' ')
                        {
                            rule = rule.replace(it, byUseElem.first.size(), (*byUseElem.second.begin())->identifier());
                            break;
                        }
                    }
                }
            }

            out += "!DVM$ " + rule + "\n";
            if (!out_free_form)
                out = splitDirective(out);

            return make_pair(dataDir.alignRules[i].alignArray, out);
        }
    }
    
    return make_pair(outA, out);
}

static vector<pair<pair<string, string>, vector<pair<int, int>>>> 
        createFullShadowSpec(const vector<pair<pair<string, string>, vector<pair<int, int>>>> &shadowBase,  const vector<vector<pair<int, int>>> &shadowShifts)
{
    vector<pair<pair<string, string>, vector<pair<int, int>>>> result(shadowBase);
    for (int z = 0; z < result.size(); ++z)
    {
        for (int p = 0; p < result[z].second.size(); ++p)
        {
            result[z].second[p].first += shadowShifts[z][p].first;
            result[z].second[p].second += shadowShifts[z][p].second;
        }
    }

    return result;
}

static void createShadowSpec(const vector<LoopGraph*> &loopGraph, 
                             vector<vector<pair<pair<string, string>, vector<pair<int, int>>>>> &shadowSpecs)
{
    for (int i = 0; i < loopGraph.size(); ++i)
    {
        createShadowSpec(loopGraph[i]->children, shadowSpecs);
        if (loopGraph[i]->directive == NULL)
            continue;
        if (loopGraph[i]->directive->shadowRenew.size() == 0 && loopGraph[i]->directive->across.size() == 0)
            continue;
        if (loopGraph[i]->directive->shadowRenew.size() != loopGraph[i]->directive->shadowRenewShifts.size())
            continue;
        if (loopGraph[i]->directive->across.size() != loopGraph[i]->directive->acrossShifts.size())
            continue;

        vector<pair<pair<string, string>, vector<pair<int, int>>>> fullShadow = createFullShadowSpec(loopGraph[i]->directive->shadowRenew, loopGraph[i]->directive->shadowRenewShifts);
        vector<pair<pair<string, string>, vector<pair<int, int>>>> fullAcross = createFullShadowSpec(loopGraph[i]->directive->across, loopGraph[i]->directive->acrossShifts);

        shadowSpecs.push_back(fullShadow);
        shadowSpecs.push_back(fullAcross);
    }
}

static inline void extractComments(SgStatement *where, const string &what)
{    
    if (BIF_CMNT(where->thebif) && CMNT_STRING(BIF_CMNT(where->thebif)))
    {
        char *str = CMNT_STRING(BIF_CMNT(where->thebif));
        string source(str);
        removeSubstrFromStr(source, what.c_str());
        sprintf(str, "%s", source.c_str());
    }
}

static SgStatement* firstExec(SgStatement *in, const string &currF)
{
    while (in)
    {
        if (isSgExecutableStatement(in) && !isSPF_stat(in) && in->fileName() == currF)
            return in;
        in = in->lexNext();
    }
    return in;
}

//NOTE: this function inserts also local templates for parallel loop without distributed arrays!
void insertTempalteDeclarationToMainFile(SgFile *file, const DataDirective &dataDir,
                                        const map<string, string> &templateDeclInIncludes,
                                        const vector<string> &distrRules, const vector<vector<dist>> &distrRulesSt, 
                                        const DIST::Arrays<int> &allArrays,
                                        const bool extractDir, const int regionId,
                                        const set<string> &includedToThisFile)
{
    vector<SgStatement*> modulesAndFuncs;
    getModulesAndFunctions(file, modulesAndFuncs);

    map<string, SgStatement*> modules;
    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        if (modulesAndFuncs[i]->variant() == MODULE_STMT)
            modules[modulesAndFuncs[i]->symbol()->identifier()] = modulesAndFuncs[i];
    }

    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        SgStatement *st = modulesAndFuncs[i];

        if (st->variant() == PROG_HEDR)
        {
            SgStatement *last = st->lastNodeOfStmt();
            set<string> includes;

            for (SgStatement *stLoc = modulesAndFuncs[i]; stLoc != last; stLoc = stLoc->lexNext())
            {
                if (stLoc->variant() == CONTAINS_STMT)
                    break;

                if (stLoc->fileName() != string(file->filename()))
                    includes.insert(stLoc->fileName());
            }

            vector<SgStatement*> useStmt;
            for (SgStatement *stLoc = modulesAndFuncs[i]; stLoc != last; stLoc = stLoc->lexNext())
            {
                if (stLoc->variant() == USE_STMT)
                    useStmt.push_back(stLoc);
            }

            const set<DIST::Array*> &arrays = allArrays.GetArrays();
            for (auto &array : arrays)
            {
                if (array->IsTemplate() && !array->IsLoopArray() && array->GetLocation().first != DIST::l_MODULE)
                {
                    int templIdx = findTeplatePosition(array, dataDir);
                    auto allClones = array->GetAllClones();
                    vector<SgStatement*> insertList1, insertList2;

                    auto templDeclP = genTemplateDelc(array, array->GetShortName(), file, NULL, true);
                    string templDecl = templDeclP.first;
                    insertList1.push_back(templDeclP.second);

                    for (auto& elem : allClones)
                    {
                        auto tmp = genTemplateDelc(array, elem.second, file, NULL, true);
                        templDecl += tmp.first;
                        insertList1.push_back(tmp.second);
                    }
                    
                    auto tmp = genTemplateDistr(array, array->GetShortName(), distrRules, distrRulesSt, regionId, templIdx, true, file);
                    string templDist = tmp.first;
                    insertList2.push_back(tmp.second);

                    for (auto &elem : allClones)
                    {
                        vector<vector<dist>> tmpRuleSt = { elem.first };

                        string strRule = elem.second + "(";
                        for (int z = 0; z < elem.first.size(); ++z)
                        {
                            if (z != 0)
                                strRule += ",";
                            if (elem.first[z] == BLOCK)
                                strRule += "BLOCK";
                            else if (elem.first[z] == NONE)
                                strRule += "*";
                            else
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                        strRule += ")";
                        vector<string> tmpStrRule = { strRule };

                        tmp = genTemplateDistr(array, elem.second, tmpStrRule, tmpRuleSt, regionId, 0, true, file);
                        templDist += tmp.first;
                        insertList2.push_back(tmp.second);
                    }

                    auto tmpDyn = genDynamicDecl(array, file);
                    const string templDyn = tmpDyn.first;
                    const string fullDecl = createFullTemplateDir(make_tuple(templDecl, templDist, templDyn));                    
                              
                    bool needToInsert = true;
                    auto inIncl = templateDeclInIncludes.find(fullDecl);
                    if (inIncl != templateDeclInIncludes.end())
                    {
                        auto hasInThisFunc = includes.find(inIncl->second);
                        if (hasInThisFunc != includes.end())
                            needToInsert = false;
                    }

                    //check modules
                    if (needToInsert)
                    {
                        for (auto &use : useStmt)
                        {
                            string name = use->symbol()->identifier();
                            auto it = modules.find(name);
                            if (it == modules.end())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            else
                            {
                                auto last = it->second->lastNodeOfStmt();
                                for (SgStatement *stLoc = it->second; stLoc != last; stLoc = stLoc->lexNext())
                                {
                                    const string &templName = array->GetShortName();

                                    if (stLoc->variant() == CONTAINS_STMT)
                                        break;

                                    const char *comment = stLoc->comments();
                                    if (comment)
                                    {
                                        if (string(comment).find(templName) != string::npos)
                                        {
                                            needToInsert = false;
                                            break;
                                        }
                                    }
                                }

                                if (needToInsert)
                                    break;
                            }
                        }
                    }

                    if (needToInsert)
                    {
                        SgStatement *nextSt = firstExec(st->lexNext(), st->fileName());
                        if (!extractDir)
                        {
                            auto cp = nextSt->controlParent();
                            for (int z = 0; z < insertList1.size(); ++z)
                            {
                                nextSt->insertStmtBefore(*insertList1[z], *cp);
                                nextSt->insertStmtBefore(*insertList2[z], *cp);
                            }
                            nextSt->insertStmtBefore(*tmpDyn.second, *cp);
                        }
                    }
                }
            }
        }
    }

    const set<DIST::Array*> &arrays = allArrays.GetArrays();
    set<DIST::Array*> loopArrays;
    for (auto &array : arrays)
        if (array->IsTemplate() && array->IsLoopArray())
            loopArrays.insert(array);
    
    if (loopArrays.size())
    {
        for (int i = 0; i < modulesAndFuncs.size(); ++i)
        {
            SgStatement *st = modulesAndFuncs[i];

            string name = "";
            if (st->variant() == PROG_HEDR || (st->variant() == FUNC_HEDR))
                name = ((SgFuncHedrStmt*)st)->name().identifier();
            else if (st->variant() == PROC_HEDR)
                name = ((SgProcHedrStmt*)st)->name().identifier();

            if (name == "")
                continue;

            for (auto &array : loopArrays)
            {
                const auto &location = array->GetLocation();
                if (location.second == name)
                {
                    int templIdx = findTeplatePosition(array, dataDir);

                    auto templDecl = genTemplateDelc(array, array->GetShortName(), file, (SgStatement*)-1, true);
                    auto templDist = genTemplateDistr(array, array->GetShortName(), distrRules, distrRulesSt, regionId, templIdx, true, file);
                    
                    SgStatement* nextSt = firstExec(st->lexNext(), st->fileName());
                    if (!extractDir)
                    {
                        auto cp = nextSt->controlParent();
                        nextSt->insertStmtBefore(*templDist.second, *cp);
                        nextSt->insertStmtBefore(*templDecl.second, *cp);
                    }
                }
            }
        }
    }
}

static SgStatement* insertDvmhModule(SgStatement *firstSt, const vector<SgStatement*> &modulesAndFuncs)
{
	for (auto &st : modulesAndFuncs)	
    if (st->variant() == MODULE_STMT)
    {
        if (st->symbol()->identifier() == string("dvmh_Template_Mod"))
            return st;
    }

    SgFuncHedrStmt *moduleN = new SgFuncHedrStmt("dvmh_Template_Mod");
    moduleN->setVariant(MODULE_STMT);
    moduleN->setlineNumber(getNextNegativeLineNumber());
    moduleN->setFileId(current_file_id);

    firstSt->insertStmtAfter(*moduleN, *firstSt);
    return moduleN;
}

static void findAllArrayRefs(SgExpression *ex, set<SgSymbol*> &refs)
{
	if (ex)
	{
		if (ex->variant() == ARRAY_REF)
		{
			SgSymbol* symb = ex->symbol();
			if (symb->type())
			{
				if (symb->type()->variant() == T_ARRAY)
					refs.insert(ex->symbol());
			}
		}
		findAllArrayRefs(ex->lhs(), refs);
		findAllArrayRefs(ex->rhs(), refs);
	}
}

void insertTemplateModuleUse(SgFile *file, const set<int> &regNums)
{
	
	int funcNum = file->numberOfFunctions();
    map<string, set<string>> moduleUseMap = createMapOfModuleUses(file);

	for (int i = 0; i < funcNum; ++i)
	{
		SgStatement *st = file->functions(i);
		auto cp = st->controlParent();
		if (cp->variant() != GLOBAL &&
			cp->variant() != PROG_HEDR &&
			cp->variant() != PROC_HEDR &&
			cp->variant() != FUNC_HEDR)
			continue;
        else
        {
            //check for module
            if (cp->variant() == PROC_HEDR || cp->variant() == FUNC_HEDR)
            {
                if (cp->controlParent()->variant() == MODULE_STMT)
                    continue;
            }
        }

		set<SgSymbol*> refs;
		set<string> modUse;
		for (st = st->lexNext(); st; st = st->lexNext())
		{
			if (isSgExecutableStatement(st))
				break;
			if (st->variant() == VAR_DECL || st->variant() == VAR_DECL_90)
			{
				for (int z = 0; z < 3; ++z)
					findAllArrayRefs(st->expr(z), refs);
			}
			else if (st->variant() == USE_STMT)
				modUse.insert(st->symbol()->identifier());
		}

		set<DIST::Array*> templates;
		for (auto &arrayR : refs)
		{
			SgStatement *decl = declaratedInStmt(arrayR);
			DIST::Array *currArray = getArrayFromDeclarated(decl, arrayR->identifier());
			checkNull(currArray, convertFileName(__FILE__).c_str(), __LINE__);

			if (!currArray->GetNonDistributeFlag())
			{
				for (auto& num : regNums)
				{
					auto templ = currArray->GetTemplateArray(num);
					if (templ)
                        if (templ->GetLocation().first == DIST::l_MODULE)
                        {
                            bool needToAdd = true;
                            if (modUse.find("dvmh_Template_Mod") == modUse.end())
                            {
                                for (auto &elem : modUse)
                                {
                                    auto it = moduleUseMap.find(elem);
                                    if (it != moduleUseMap.end())
                                    {
                                        if (it->second.find("dvmh_Template_Mod") != it->second.end())
                                        {
                                            needToAdd = false;
                                            break;
                                        }
                                    }
                                }
                            }
                            if (needToAdd)
                                templates.insert(templ);
                        }
				}
			}
		}
		
		if (templates.size())		
		{
			st = file->functions(i);

			SgStatement* useSt = new SgStatement(USE_STMT);
			useSt->setSymbol(*findSymbolOrCreate(file, "dvmh_Template_Mod"));
			useSt->setlineNumber(getNextNegativeLineNumber());
			st->insertStmtAfter(*useSt, *st);
		}
	}	
}

static vector<SgStatement*> filterAllocateStats(const vector<SgStatement*> &current, const string &array)
{
    vector<SgStatement*> filtered;

    for (auto &stat : current)
    {
        set<string> arraySyns;
        arraySyns.insert(array);

        auto byUse = moduleRefsByUseInFunction(stat);
        for (auto &elem : byUse)
            if (elem.first == array)
                for (auto &newElem : elem.second)
                    arraySyns.insert(newElem->identifier());

        for (auto &syns : arraySyns)
            if (recSymbolFind(stat->expr(0), syns, ARRAY_REF))
                filtered.push_back(stat);        
    }

    if (filtered.size() != 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return filtered;
}

// by file and function
static map<string, map<string, set<string>>> dynamicDirsByFile;
static map<string, map<string, set<string>>> dynamicArraysByFile;
static map<string, map<string, set<string>>> alignArraysByFile;
static map<string, map<string, map<string, pair<SgExpression*, SgExpression*>>>> insertedShadowByFile;

static inline void addStringToComments(const vector<string> &toInsert, map<string, map<int, set<string>>> &commentsToInclude,
                                       const string fileName, const int line)
{
    auto currF = commentsToInclude.find(fileName);
    if (currF == commentsToInclude.end())
        currF = commentsToInclude.insert(currF, make_pair(fileName, map<int, set<string>>()));

    auto place = currF->second.find(line);
    if (place == currF->second.end())
        place = currF->second.insert(place, make_pair(line, set<string>()));

    for (auto &str : toInsert)
    {
        if (str == "")
            continue;

        bool needToInsert = true;        
        for (auto &elem : currF->second)
        {
            for (auto addedStr : elem.second)
            {
                if (addedStr == str)
                {
                    needToInsert = false;
                    break;
                }
            }

            if (needToInsert == false)
                break;
        }

        if (needToInsert)
            place->second.insert(str);
    }
}

static string getFullArrayName(SgSymbol *symb)
{
    string fullArrayName = "";
    if (symb->type()->variant() == T_ARRAY)
    {
        auto uniqKey = getFromUniqTable(symb);
        fullArrayName = getShortName(uniqKey);
    }
    return fullArrayName;
}

static vector<SgExpression*> createVarListFromDecl(const int currV, SgStatement *st)
{
    vector<SgExpression*> varList;
    if (currV == COMM_STAT)
    {
        map<string, vector<SgExpression*>> commonBlocks;
        getCommonBlocksRef(commonBlocks, st, st->lexNext());
        for (auto &elem : commonBlocks)
        {
            for (auto &commList : elem.second)
            {
                SgExpression *list = commList->lhs();
                while (list)
                {
                    varList.push_back(list->lhs());
                    list = list->rhs();
                }
            }
        }
    }
    else
    {
        SgVarDeclStmt *varDecl = (SgVarDeclStmt*)st;
        SgExpression *varL = varDecl->varList();
        while (varL)
        {
            varList.push_back(varL->lhs());
            varL = varL->rhs();
        }
    }

    return varList;
}

void insertDistributionToFile(SgFile *file, const char *fin_name, const DataDirective &dataDir, 
                              const set<string> &distrArrays, const vector<string> &distrRules, 
                              const vector<vector<dist>> &distrRulesSt,
                              const vector<string> &alignRules, const map<string, vector<LoopGraph*>> &loopGraph,
                              const DIST::Arrays<int> &allArrays,
                              DIST::GraphCSR<int, double, attrType> &reducedG,
                              map<string, map<int, set<string>>> &commentsToInclude,
                              map<string, string> &templateDeclInIncludes,
                              const bool extractDir, vector<Messages> &messagesForFile,
                              const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                              const int regionId)
{
    vector<SgStatement*> modulesAndFuncs;
    getModulesAndFunctions(file, modulesAndFuncs);

    SgStatement *dvmhModule = NULL;
    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        SgStatement *isModule = (modulesAndFuncs[i]->variant() == MODULE_STMT) ? modulesAndFuncs[i] : NULL;
        if (isModule)
        {
            dvmhModule = insertDvmhModule(file->firstStatement(), modulesAndFuncs);
            break;
        }
    }    

    map<SgStatement*, set<string>> dvmhModuleSt;
    if (dvmhModule)
        dvmhModuleSt[dvmhModule] = set<string>();

    currProcessing.first = file->filename();
    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        SgStatement *st = modulesAndFuncs[i];
        SgStatement *lastNode = st->lastNodeOfStmt();
        set<string> templateDelc;
        SgStatement *isModule = (st->variant() == MODULE_STMT) ? st : NULL;
        bool isMain = (st->variant() == PROG_HEDR);

        const string modName = st->symbol()->identifier();
        map<string, pair<SgExpression*, SgExpression*>> &insertedShadow = insertedShadowByFile[fin_name][modName];
        set<string> &dynamicDirs = dynamicDirsByFile[fin_name][modName];
        set<string> &dynamicArraysAdded = dynamicArraysByFile[fin_name][modName];
        set<string> &alignArrays = alignArraysByFile[fin_name][modName];

        // PAIR<dir, insertBefore>
        pair<SgStatement*, SgStatement*> inheritDir = make_pair((SgStatement*)NULL, (SgStatement*)NULL);

        while (st != lastNode)
        {
            if (st == NULL)
            {
#ifdef _WIN32
                messagesForFile.push_back(Messages(ERROR, 1, R128, L"internal error in analysis, parallel directives will not be generated for this file!", 3008));
#endif
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }
            
            if (st->variant() == CONTAINS_STMT)
                break;
            currProcessing.second = st->lineNumber();

            const int currV = st->variant();
            if (currV == VAR_DECL || currV == VAR_DECL_90 || currV == DIM_STAT || currV == COMM_STAT)
            {
                auto varList = createVarListFromDecl(currV, st);

                set<DIST::Array*> dynamicArrays;
                set<DIST::Array*> dynamicArraysLocal;
                map<string, DIST::Array*> dynamicArraysStr;
                for (auto &varExp : varList)
                {
                    if (varExp->variant() == ARRAY_REF)
                    {
                        SgSymbol *currSymb = OriginalSymbol(varExp->symbol());
                        const string fullArrayName = getFullArrayName(currSymb);
                        
                        if (distrArrays.find(fullArrayName) != distrArrays.end())
                        {
                            map<string, set<SgSymbol*>> byUseInFunc;

                            const vector<SgStatement*> &allocatableStmtsCopy = getAttributes<SgStatement*, SgStatement*>(st, set<int>{ ALLOCATE_STMT });
                            vector<SgStatement*> allocatableStmts;
                            if (isModule && allocatableStmtsCopy.size())
                            {
                                allocatableStmts = filterAllocateStats(allocatableStmtsCopy, currSymb->identifier());
                                for (auto &alloc : allocatableStmts)
                                {
                                    auto byUse = moduleRefsByUseInFunction(alloc);
                                    for (auto &byUseElem : byUse)
                                        byUseInFunc[byUseElem.first].insert(byUseElem.second.begin(), byUseElem.second.end());
                                }
                            }
                            pair<DIST::Array*, string> dirWithArray = getNewDirective(fullArrayName, distrRules, alignRules, dataDir, byUseInFunc, isModule && allocatableStmts.size() != 0);

                            string toInsert = dirWithArray.second;
                            if (toInsert != "")
                            {
                                auto alignIt = alignArrays.find(fullArrayName);
                                if (alignIt == alignArrays.end() && !extractDir)
                                    alignArrays.insert(alignIt, fullArrayName);
                                else if (alignIt != alignArrays.end() && extractDir)
                                    alignArrays.erase(alignIt);
                                else
                                    toInsert = "";

                                const pair<templateDir, string> &templDir =
                                    getNewTemplateDirective(dirWithArray.first, allArrays, reducedG, dataDir, distrRules, distrRulesSt, arrayLinksByFuncCalls, regionId, isModule, isMain, file);
                                string templDecl = templDir.first.templDecl.first; //std::get<0>(templDir.first);

                                //if array is inherit array 
                                if (templDir.second == "!DVM$ INHERIT\n")
                                {
                                    toInsert = "";

                                    if (inheritDir.first == NULL)
                                    {
                                        if (extractDir == false)
                                        {
                                            inheritDir.first = new SgStatement(DVM_INHERIT_DIR);
                                            SgExpression *list = new SgExpression(EXPR_LIST);
                                            SgExpression *ref = new SgVarRefExp(findSymbolOrCreate(file, dirWithArray.first->GetShortName()));
                                            list->setLhs(ref);
                                            inheritDir.first->setExpression(0, *list);
                                        }
                                        inheritDir.second = st;
                                    }
                                    else 
                                    {
                                        if (extractDir == false)
                                        {
                                            SgExpression *list = new SgExpression(EXPR_LIST);
                                            SgExpression *ref = new SgVarRefExp(findSymbolOrCreate(file, dirWithArray.first->GetShortName()));
                                            list->setLhs(ref);
                                            list->setRhs(inheritDir.first->expr(0));
                                            inheritDir.first->setExpression(0, *list);
                                        }
                                    }
                                }
                                else
                                    dynamicArraysLocal.insert(dirWithArray.first);
                                dynamicArrays.insert(dirWithArray.first);
                                dynamicArraysStr.insert(make_pair(dirWithArray.first->GetName(), dirWithArray.first));
                                    
                                // don't insert template decl for inherit arrays in functions
                                //TODO: need to correct in case of use local arrays in functions
                                if (templDir.second == "!DVM$ INHERIT\n" && templDir.first.isTemplateInModule)
                                    templDecl = "";
                                else
                                {
                                    if (templateDelc.find(templDecl) == templateDelc.end())
                                        templateDelc.insert(templDecl);
                                    else
                                        templDecl = "";

                                    if (templDecl != "")
                                        templDecl = createFullTemplateDir(make_tuple(templDir.first.templDecl.first, templDir.first.templDist.first, templDir.first.templDyn.first));
                                }

                                if (!strcmp(st->fileName(), fin_name))
                                {
                                    if (modulesAndFuncs[i]->variant() == PROG_HEDR)
                                        templDecl = "";
                                    else
                                    {
                                        set<DIST::Array*> realRefs;
                                        getRealArrayRefs(dirWithArray.first, dirWithArray.first, realRefs, arrayLinksByFuncCalls);
                                        for (auto &elem : realRefs)
                                        {                                            
                                            if (elem->GetTemplateArray(regionId)->GetLocation().first == DIST::arrayLocType::l_MODULE)
                                            {
                                                templDecl = "";
                                                break;
                                            }
                                        }
                                    }

                                    string toAdd = "";
                                    if (isModule && dvmhModule)
                                        toAdd = toInsert;
                                    else
                                        toAdd = templDecl + toInsert;

                                    if (extractDir)
                                    {
                                        if (isModule && dvmhModule && allocatableStmts.size())
                                        {
                                            for (auto &elem : allocatableStmts)
                                                extractComments(elem->lexNext(), toAdd);
                                            extractComments(st, ("!DVM$ ALIGN :: " + dirWithArray.first->GetShortName() + "\n").c_str());
                                        }
                                        else
                                            extractComments(st, toAdd);
                                    }
                                    else
                                    {
                                        if (isModule && dvmhModule && allocatableStmts.size())
                                        {
                                            for (auto &elem : allocatableStmts)
                                                elem->lexNext()->addComment(toAdd.c_str());
                                            st->addComment(("!DVM$ ALIGN :: " + dirWithArray.first->GetShortName() + "\n").c_str());
                                        }
                                        else
                                            st->addComment(toAdd.c_str());

                                        if (isModule && dvmhModule)
                                        {
                                            if (dvmhModuleSt[dvmhModule].find(templDir.first.templDyn.first) == dvmhModuleSt[dvmhModule].end())
                                            {
                                                dvmhModule->insertStmtAfter(*templDir.first.templDyn.second, *dvmhModule);
                                                dvmhModuleSt[dvmhModule].insert(templDir.first.templDyn.first);
                                            }

                                            if (dvmhModuleSt[dvmhModule].find(templDir.first.templDecl.first) == dvmhModuleSt[dvmhModule].end())
                                            {
                                                for (int z = 0; z < templDir.first.templDecl.second.size(); ++z)
                                                    dvmhModule->insertStmtAfter(*templDir.first.templDecl.second[z], *dvmhModule);
                                                dvmhModuleSt[dvmhModule].insert(templDir.first.templDecl.first);
                                            }

                                            if (dvmhModuleSt[dvmhModule].find(templDir.first.templDist.first) == dvmhModuleSt[dvmhModule].end())
                                            {
                                                for (int z = 0; z < templDir.first.templDist.second.size(); ++z)
                                                    dvmhModule->insertStmtAfter(*templDir.first.templDist.second[z], *dvmhModule);
                                                dvmhModuleSt[dvmhModule].insert(templDir.first.templDist.first);
                                            }

                                            const string useS = dvmhModule->symbol()->identifier();
                                            string str = string("use ") + useS;
                                            if (dvmhModuleSt[isModule].find(str) == dvmhModuleSt[isModule].end())
                                            {
                                                dvmhModuleSt[isModule].insert(str);

                                                SgStatement *useSt = new SgStatement(USE_STMT);
                                                useSt->setSymbol(*findSymbolOrCreate(file, useS));
                                                useSt->setlineNumber(getNextNegativeLineNumber());
                                                isModule->insertStmtAfter(*useSt, *isModule);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    addStringToComments({ templDecl, toInsert }, commentsToInclude, st->fileName(), st->lineNumber());
                                    if (templDecl != "")
                                        templateDeclInIncludes[templDecl] = st->fileName();
                                }
                            }
                        }
                    }
                }

                string toInsert = "!DVM$ DYNAMIC ";
                vector<string> toInsertArrays;
                for (auto &array : dynamicArraysLocal)
                {
                    if (extractDir)
                    {
                        if (dynamicArraysAdded.find(array->GetShortName()) != dynamicArraysAdded.end())
                        {
                            dynamicArraysAdded.erase(array->GetShortName());
                            toInsertArrays.push_back(array->GetShortName());
                        }
                    }
                    else
                    {
                        if (dynamicArraysAdded.find(array->GetShortName()) == dynamicArraysAdded.end())
                        {
                            dynamicArraysAdded.insert(array->GetShortName());
                            toInsertArrays.push_back(array->GetShortName());
                        }
                    }
                }

                int z = 0;
                for (auto &array : toInsertArrays)
                {
                    if (z != 0)
                        toInsert += ",";
                    toInsert += array;
                    ++z;
                }

                if (z != 0)
                {
                    toInsert += "\n";
                    auto dynIt = dynamicDirs.find(toInsert);

                    if (dynIt == dynamicDirs.end() && !extractDir)
                        dynamicDirs.insert(dynIt, toInsert);
                    else if (extractDir && dynIt != dynamicDirs.end())
                        dynamicDirs.erase(dynIt);
                    else
                        toInsert = "";
                }
                else
                    toInsert = "";
                
                if (dynamicArrays.size() > 0)
                {
                    vector<vector<pair<pair<string, string>, vector<pair<int, int>>>>> shadowSpecsAll;
                    for (auto it = loopGraph.begin(); it != loopGraph.end(); ++it)
                        if (it->second.size() > 0)
                            createShadowSpec(it->second, shadowSpecsAll);

                    for (auto &spec : shadowSpecsAll)
                    {
                        for (int i = 0; i < spec.size(); ++i)
                        {
                            auto dynArray = dynamicArraysStr.find(spec[i].first.second);
                            if (dynArray == dynamicArraysStr.end())
                                continue;

                            set<DIST::Array*> realArrayRefs;
                            getRealArrayRefs(dynArray->second, dynArray->second, realArrayRefs, arrayLinksByFuncCalls);

                            for (auto &array : realArrayRefs)
                                array->ExtendShadowSpec(spec[i].second);
                        }
                    }
                }
                
                if (toInsert != "")
                {
                    if (!strcmp(st->fileName(), fin_name))
                    {
                        if (extractDir)
                            extractComments(st, toInsert); 
                        else
                            st->addComment(toInsert.c_str());
                    }
                    else
                        addStringToComments({ toInsert }, commentsToInclude, st->fileName(), st->lineNumber());
                }
            }
            st = st->lexNext();
        }

        if (inheritDir.second)
        {
            if (extractDir == false)
            {
                inheritDir.second->insertStmtBefore(*inheritDir.first, *inheritDir.second->controlParent());

                SgStatement *dynamicDir = new SgStatement(DVM_DYNAMIC_DIR);
                dynamicDir->setExpression(0, inheritDir.first->expr(0)->copy());
                inheritDir.second->insertStmtBefore(*dynamicDir, *inheritDir.second->controlParent());
            }
        }
    }

    if (extractDir)
    {
        if (dvmhModule)
            dvmhModule->deleteStmt();
    }
}

void insertShadowSpecToFile(SgFile *file, const char *fin_name, const set<string> &distrArrays, 
                            DIST::GraphCSR<int, double, attrType> &reducedG,
                            map<string, map<int, set<string>>> &commentsToInclude,
                            const bool extractDir, vector<Messages> &messagesForFile,
                            const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays)
{
    vector<SgStatement*> modulesAndFuncs;
    getModulesAndFunctions(file, modulesAndFuncs);
    
    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        SgStatement *st = modulesAndFuncs[i];
        SgStatement *lastNode = st->lastNodeOfStmt();

        const string modName = st->symbol()->identifier();
        map<string, pair<SgExpression*, SgExpression*>> &insertedShadow = insertedShadowByFile[fin_name][modName];

        while (st != lastNode)
        {
            if (st == NULL)
            {
#ifdef _WIN32
                messagesForFile.push_back(Messages(ERROR, 1, R128, L"internal error in analysis, parallel directives will not be generated for this file!", 3008));
#endif
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            const int currV = st->variant();
            if (currV == VAR_DECL || currV == VAR_DECL_90 || currV == DIM_STAT || currV == COMM_STAT)
            {
                auto varList = createVarListFromDecl(currV, st);
                                
                set<DIST::Array*> declaratedDistrArrays;
                for (auto &varExpr : varList)
                {
                    if (varExpr->variant() == ARRAY_REF)
                    {
                        SgSymbol *currSymb = OriginalSymbol(varExpr->symbol());
                        const string fullArrayName = getFullArrayName(currSymb);

                        if (distrArrays.find(fullArrayName) != distrArrays.end())
                        {
                            auto uniqKey = getFromUniqTable(currSymb);
                            auto itArr = declaratedArrays.find(uniqKey);
                            if (itArr != declaratedArrays.end())                                
                                declaratedDistrArrays.insert(itArr->second.first);
                        }
                    }
                }

                vector<pair<SgExpression*, SgExpression*>> shadowsSpecs;
                vector<string> shadowsSpecsString;

                for (auto &array : declaratedDistrArrays)
                {
                    const vector<pair<int, int>> currSpec = array->GetShadowSpec();
                    bool needToGen = false;

                    for (auto &elem : currSpec)
                        if (elem.first != 0 || elem.second != 0)
                            needToGen = true;

                    if (needToGen)
                    {
                        string shadowSpecInsert = "!DVM$ SHADOW " + array->GetShortName() + "(";
                        for (int k = 0; k < currSpec.size(); ++k)
                        {
                            char buf[256];
                            sprintf(buf, "%d:%d", currSpec[k].first, currSpec[k].second);
                            shadowSpecInsert += buf;
                            if (k != currSpec.size() - 1)
                                shadowSpecInsert += ",";
                        }
                        shadowSpecInsert += ")\n";

                        shadowsSpecsString.push_back(shadowSpecInsert);
                        pair<SgExpression*, SgExpression*> newSpec = genShadowSpec(file, make_pair(array->GetShortName(), currSpec));
                        if (newSpec.first == NULL || newSpec.second == NULL)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        shadowsSpecs.push_back(newSpec);
                    }
                }
                
                if (shadowsSpecsString.size() > 0)
                {
                    if (!strcmp(st->fileName(), fin_name))
                    {
                        if (extractDir == false)
                        {
                            for (int i = 0; i < shadowsSpecs.size(); ++i)
                            {
                                SgStatement *tmp = new SgStatement(DVM_SHADOW_DIR, NULL, NULL, shadowsSpecs[i].first, shadowsSpecs[i].second, NULL);
                                st->insertStmtAfter(*tmp, *st->controlParent());
                                insertedShadow.insert(make_pair(shadowsSpecs[i].first->unparse(), shadowsSpecs[i]));
                            }
                        }
                        else
                        {
                            for (int i = 0; i < shadowsSpecs.size(); ++i)
                            {
                                auto it = insertedShadow.find(shadowsSpecs[i].first->unparse());
                                if (it != insertedShadow.end())
                                    insertedShadow.erase(it);
                            }
                        }
                    }
                    else
                        addStringToComments(shadowsSpecsString, commentsToInclude, st->fileName(), st->lineNumber());                    
                }
            }
            st = st->lexNext();
        }
    }
}

void insertDistributionToFile(const char *origFile, const char *outFile, const map<int, set<string>> &commentsToInclude)
{
    FILE *F = fopen(origFile, "r");

    vector<string> lines;
    set<string> uniqLines;
    while (!feof(F))
    {
        char buf[8192];
        char *res = fgets(buf, 8192, F);
        if (res)
        {
            string bufStr(buf);
            convertToLower(bufStr);
 
            bool iSPF = isSPF_comment(bufStr);
            if (keepSpfDirs)
            {
                lines.push_back(buf);
                uniqLines.insert(buf);
            }
            else
            {
                if (iSPF)
                {
                    lines.push_back(" ");
                    uniqLines.insert(" ");
                }
                else
                {
                    lines.push_back(buf);
                    uniqLines.insert(buf);
                }
            }
        }
    }
    
    fclose(F);

    // TODO: use existing DVMH directive
    /*for (auto k = commentsToInclude.begin(); k != commentsToInclude.end(); ++k)
    {
        const int line = k->first - 1;
        for (auto it = k->second.begin(); it != k->second.end(); ++it)
        {
            if (uniqLines.find(*it) == uniqLines.end())
                lines.insert(lines.begin() + line, *it);
        }
    }*/

    /*for (int i = 0; i < lines.size(); ++i)
        printf("%s", lines[i].c_str());*/
    
    F = fopen(outFile, "w");    
    //save order 
    int idx = 0;
    for (auto k = commentsToInclude.begin(); k != commentsToInclude.end(); ++k)
    {
        int currLine = k->first - 1;
        if (currLine > idx)
        {
            if (idx < lines.size())
            {
                for ( ; idx < currLine; ++idx)
                    fprintf(F, "%s", lines[idx].c_str());
            }
            for (auto it = k->second.begin(); it != k->second.end(); ++it)
                fprintf(F, "%s", (*it).c_str());
        }
        else
            for (auto it = k->second.begin(); it != k->second.end(); ++it)
                fprintf(F, "%s", (*it).c_str());
    }

    for ( ; idx < lines.size(); ++idx)
        fprintf(F, "%s", lines[idx].c_str());    
    fclose(F);
}

void insertDistributeDirsToParallelRegions(const vector<ParallelRegionLines> *currLines,
                                           const vector<Statement*> &reDistrRulesBefore,
                                           const vector<Statement*> &reDistrRulesAfter,
                                           const vector<Statement*> &reAlignRules)
{
    if (currLines)
    {
        for (int i = 0; i < currLines->size(); ++i)
        {
            SgStatement *insertBefore = (*currLines)[i].stats.first;
            SgStatement *insertAfter = (*currLines)[i].stats.second;

            if (insertBefore == NULL || insertAfter == NULL)
                continue;

            SgStatement *controlParentAfter = insertAfter->controlParent();
            if (insertAfter->variant() == CONTROL_END)
                controlParentAfter = controlParentAfter->controlParent();

            while (insertBefore->lexPrev()->variant() == DVM_PARALLEL_ON_DIR || insertBefore->lexPrev()->variant() == DVM_REDISTRIBUTE_DIR)
                insertBefore = insertBefore->lexPrev();
            
            while (insertAfter->lexPrev()->variant() == DVM_PARALLEL_ON_DIR)
                insertAfter = insertAfter->lexPrev();
            while (insertAfter->lexNext()->variant() == DVM_REDISTRIBUTE_DIR)
                insertAfter = insertAfter->lexNext();

            while (insertBefore && isSgExecutableStatement(insertBefore) == NULL)
                insertBefore = insertBefore->lexNext();

            for (int k = 0; k < reDistrRulesBefore.size(); ++k)
                insertBefore->insertStmtBefore(reDistrRulesBefore[k]->copy(), *insertBefore->controlParent());

            for (int k = 0; k < reDistrRulesAfter.size(); ++k)
                insertAfter->insertStmtAfter(reDistrRulesAfter[k]->copy(), *controlParentAfter);

            for (int k = 0; k < reAlignRules.size(); ++k)
                insertBefore->insertStmtBefore(reAlignRules[k]->copy(), *insertBefore->controlParent());

            // insert redistribute before all return stats
            for (SgStatement *st = (*currLines)[i].stats.first; st->variant() != SPF_END_PARALLEL_REG_DIR; st = st->lexNext())
            {
                if (st->variant() == RETURN_STAT)
                {
                    SgStatement *cp = st->controlParent();
                    if (cp->variant() == LOGIF_NODE)
                        cp = ((SgLogIfStmt*)cp)->convertLogicIf();

                    for (int k = 0; k < reDistrRulesBefore.size(); ++k)
                        st->insertStmtBefore(reDistrRulesAfter[k]->copy(), *cp);
                }
            }

            SgStatement *module = (*currLines)[i].stats.first;
            int modVar = module->variant();
            while (modVar != MODULE_STMT && modVar != FUNC_HEDR && modVar != PROC_HEDR && modVar != PROG_HEDR)
            {
                module = module->controlParent();
                modVar = module->variant();
            }

            map<int, vector<int>> allLabRefs;
            findAllRefsToLables(module, allLabRefs);
            int labNum = 1;

            // insert redistribute after all entry points
            for (SgStatement *st = (*currLines)[i].stats.first->lexNext(); st->variant() != SPF_END_PARALLEL_REG_DIR; st = st->lexNext())
            {
                if (st->variant() == ENTRY_STAT)
                {
                    SgStatement *cp = st->controlParent();
                    SgStatement *afterEntry = st->lexNext();

                    int goToLab = -1;
                    SgLabel *goToLabp = NULL;
                    if (afterEntry->label())
                    {
                        goToLabp = afterEntry->label();
                        goToLab = goToLabp->getLabNumber();
                    }
                    else
                    {
                        while (allLabRefs.find(labNum) != allLabRefs.end())
                            ++labNum;
                        goToLab = labNum;
                        allLabRefs.insert(make_pair(labNum, vector<int>()));
                        ++labNum;

                        goToLabp = new SgLabel(goToLab);
                        afterEntry->setLabel(*goToLabp);
                        BIF_LABEL_USE(afterEntry->thebif) = goToLabp->thelabel;
                    }

                    SgGotoStmt *gotoStat = new SgGotoStmt(*goToLabp);
                    st->insertStmtBefore(*gotoStat, *cp);

                    for (int k = 0; k < reAlignRules.size(); ++k)
                        st->insertStmtAfter(reAlignRules[k]->copy(), *cp);

                    for (int k = 0; k < reDistrRulesBefore.size(); ++k)
                        st->insertStmtAfter(reDistrRulesBefore[k]->copy(), *cp);
                }
            }
        }
    }
}