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

#include "../Utils/errors.h"
#include "loop_analyzer.h"
#include "directive_parser.h"
#include "../Utils/SgUtils.h"
#include "../transform.h"

using std::string;
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
    {
        result = new SgStatement(DVM_PARALLEL_ON_DIR, NULL, NULL, NULL, NULL, NULL);
        for (int i = 0; i < 3; ++i)
            if (exprs[i])
                result->setExpression(i, *exprs[i]);
    }
    else if (exprs.size() == 4)
    {
        result = new SgStatement(DVM_REDISTRIBUTE_DIR, NULL, NULL, NULL, NULL, NULL);
        for (int i = 0; i < 3; ++i)
            if (exprs[i])
                result->setExpression(i, *exprs[i]);
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    
    return result;
}

static void removeDoubleRedistribute(map<int, vector<vector<Expression*>>> &toInsertMap)
{
    for (auto it = toInsertMap.begin(); it != toInsertMap.end(); ++it)
    {
        vector<vector<Expression*>> newVal;

        for (int z = 1; z < it->second.size(); ++z)
        {
            if (it->second[z].size() == 4)
                if (it->second[z].size() == it->second[z - 1].size())
                    continue;
            newVal.push_back(it->second[z - 1]);
        }
        newVal.push_back(it->second.back());
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
    int funcNum = file->numberOfFunctions();

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

    removeDoubleRedistribute(toInsertMap);
    vector<SgStatement*> toDel;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        
        int numSt = 0;
        do
        {
            if (st->variant() == CONTAINS_STMT)
                break;

            currProcessing.second = st;
            if (numSt != 0)
                st = st->lexNext();

            if (st == NULL)
            {
                string message;
                __spf_printToBuf(message, "internal error in analysis, parallel directives will not be generated for this file!");
                messagesForFile.push_back(Messages(ERROR, 1, message, 3008));

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
                    var == DVM_SHADOW_DIR)
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
                toDel[k]->deleteStmt();
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

    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
            currProcessing.second = st;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            const int var = st->variant();
            //for details see dvm_tag.h
            if ((var >= 128 && var <= 129) || 
                (var >= 146 && var <= 149) ||
                (var >= 211 && var <= 224) ||
                (var >= 247 && var <= 249) ||
                (var >= 605 && var <= 634) ||
                (var >= 900 && var <= 949) ||
                (var == 277 || var == 299))
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
            currProcessing.second = elem;

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
            currProcessing.second = elem;

            moveComment(elem);
            elem->deleteStmt();
        }
    }
}

static inline string genTemplateDelc(const DIST::Array *templ, const bool common = true)
{
    string templDecl = (common) ? "!DVM$ TEMPLATE, COMMON :: " : "!DVM$ TEMPLATE ";
    const vector<pair<int, int>> &sizes = templ->GetSizes();

    templDecl += templ->GetShortName() + "(";
    for (int z = 0; z < sizes.size(); ++z)
    {
        templDecl += std::to_string(sizes[z].first) + ":" + std::to_string(sizes[z].second);
        if (z != sizes.size() - 1)
            templDecl += ",";
    }
    templDecl += ")\n";

    return templDecl;
}

static inline string genTemplateDistr(const DIST::Array *templ, const vector<string> &distrRules,
                                      const int regionId, const int templIdx)
{
    string templDist = "";
    const vector<pair<int, int>> &sizes = templ->GetSizes();

    if (regionId > 0)
    {
        templDist += "!DVM$ DISTRIBUTE ";
        templDist += templ->GetShortName() + "(";
        for (int z = 0; z < sizes.size(); ++z)
        {
            templDist += "*";
            if (z != sizes.size() - 1)
                templDist += ",";
        }
        templDist += ")\n";
    }
    else // for default region
        templDist += "!DVM$ DISTRIBUTE " + distrRules[templIdx] + "\n";

    return templDist;
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
        fullDir += splitDirective(std::get<0>(templDir));
        fullDir += splitDirective(std::get<1>(templDir));
        fullDir += splitDirective(std::get<2>(templDir));
    }
    else
        fullDir += std::get<0>(templDir) + std::get<1>(templDir) + std::get<2>(templDir);
    
    return fullDir;
}

static pair<tuple<string, string, string>, string> getNewTemplateDirective(DIST::Array *alignArray, const DIST::Arrays<int> &allArrays,
                                                       DIST::GraphCSR<int, double, attrType> &reducedG,
                                                       const DataDirective &dataDir, const vector<string> &distrRules,
                                                       const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                                       const int regionId)
{   
    DIST::Array *templ = findLinkWithTemplate(alignArray, allArrays, reducedG, regionId);   

    //checkNull(templ, convertFileName(__FILE__).c_str(), __LINE__);
    //TODO: improve and check this!!
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

        int templIdx = findTeplatePosition(templ, dataDir);
        string templDecl = genTemplateDelc(templ);
        string templDist = genTemplateDistr(templ, distrRules, regionId, templIdx);
        string templDyn = "!DVM$ DYNAMIC " + templ->GetShortName() + "\n";

        return make_pair(make_tuple(templDecl, templDist, templDyn), "!DVM$ INHERIT\n");
    }
    else
    {
        int templIdx = findTeplatePosition(templ, dataDir);
        string templDecl = genTemplateDelc(templ);
        string templDist = genTemplateDistr(templ, distrRules, regionId, templIdx);
        string templDyn = "!DVM$ DYNAMIC " + templ->GetShortName() + "\n";

        return make_pair(make_tuple(templDecl, templDist, templDyn), templ->GetShortName());
    }
}

static pair<DIST::Array*, string>
getNewDirective(const string &fullArrayName, 
                const vector<string> &distrRules,
                const vector<string> &alignRules,
                const DataDirective &dataDir)
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
            out += "!DVM$ " + alignRules[i] + "\n";
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
        createShadowSpec(loopGraph[i]->childs, shadowSpecs);
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
    char *str = CMNT_STRING(BIF_CMNT(where->thebif));
    string source(str);
    removeSubstrFromStr(source, what.c_str());
    sprintf(str, "%s", source.c_str());
}

//NOTE: this function inserts also local templates for parallel loop with out distributed arrays!
void insertTempalteDeclarationToMainFile(SgFile *file, const DataDirective &dataDir,
                                        map<string, string> templateDeclInIncludes,
                                        const vector<string> &distrRules, const DIST::Arrays<int> &allArrays, 
                                        const bool extractDir, const int regionId,
                                        const set<string> &includedToThisFile)
{
    vector<SgStatement*> modulesAndFuncs;
    getModulesAndFunctions(file, modulesAndFuncs);

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

            const set<DIST::Array*> &arrays = allArrays.GetArrays();
            for (auto &array : arrays)
            {
                if (array->isTemplate() && !array->isLoopArray())
                {
                    int templIdx = findTeplatePosition(array, dataDir);
                    string templDecl = genTemplateDelc(array);
                    string templDist = genTemplateDistr(array, distrRules, regionId, templIdx);
                    string templDyn = "!DVM$ DYNAMIC " + array->GetShortName() + "\n";

                    string fullDecl = createFullTemplateDir(make_tuple(templDecl, templDist, templDyn));
                    SgStatement *nextSt = st->lexNext();
                              
                    bool needToInsert = true;
                    auto inIncl = templateDeclInIncludes.find(fullDecl);
                    if (inIncl != templateDeclInIncludes.end())
                    {
                        auto hasInThisFunc = includes.find(inIncl->first);
                        if (hasInThisFunc != includes.end())
                            needToInsert = false;
                    }

                    if (needToInsert && includedToThisFile.find(fullDecl) == includedToThisFile.end())
                    {
                        if (extractDir)
                            extractComments(nextSt, fullDecl);
                        else
                            nextSt->addComment(fullDecl.c_str());
                    }
                }
            }
        }
    }

    const set<DIST::Array*> &arrays = allArrays.GetArrays();
    set<DIST::Array*> loopArrays;
    for (auto &array : arrays)
        if (array->isTemplate() && array->isLoopArray())
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
                    string templDecl = genTemplateDelc(array, false);
                    string templDist = genTemplateDistr(array, distrRules, regionId, templIdx);
                    string templDyn = "";

                    string fullDecl = createFullTemplateDir(make_tuple(templDecl, templDist, templDyn));
                    SgStatement *nextSt = st->lexNext();

                    if (includedToThisFile.find(fullDecl) == includedToThisFile.end())
                    {
                        if (extractDir)
                            extractComments(nextSt, fullDecl);
                        else
                            nextSt->addComment(fullDecl.c_str());
                    }
                }
            }
        }
    }
}

static map<string, set<string>> dynamicDirsByFile;
static map<string, set<string>> alignArraysByFile;
static map<string, map<string, pair<SgExpression*, SgExpression*>>> insertedShadowByFile;

static inline void addStringToComments(const vector<string> &toInsert, map<string, map<int, set<string>>> &commentsToInclude,
                                       const string fileName, const int line)
{
    auto currF = commentsToInclude.find(fileName);
    if (currF == commentsToInclude.end())
        currF = commentsToInclude.insert(currF, make_pair(fileName, map<int, set<string>>()));

    auto place = currF->second.find(line);
    if (place == currF->second.end())
        place = currF->second.insert(place, make_pair(line, set<string>()));

    for (auto str : toInsert)
    {
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

void insertDistributionToFile(SgFile *file, const char *fin_name, const DataDirective &dataDir, 
                              const set<string> &distrArrays, const vector<string> &distrRules, 
                              const vector<string> &alignRules, const map<string, vector<LoopGraph*>> &loopGraph,
                              const DIST::Arrays<int> &allArrays,
                              DIST::GraphCSR<int, double, attrType> &reducedG,
                              map<string, map<int, set<string>>> &commentsToInclude,
                              map<string, string> templateDeclInIncludes,
                              const bool extractDir, vector<Messages> &messagesForFile,
                              const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                              const int regionId)
{
    vector<SgStatement*> modulesAndFuncs;
    getModulesAndFunctions(file, modulesAndFuncs);
        
    map<string, pair<SgExpression*, SgExpression*>> &insertedShadow = insertedShadowByFile[fin_name];
    set<string> &dynamicDirs = dynamicDirsByFile[fin_name];
    set<string> &alignArrays = alignArraysByFile[fin_name];

    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        SgStatement *st = modulesAndFuncs[i];
        SgStatement *lastNode = st->lastNodeOfStmt();
        set<string> templateDelc;
        
        pair<SgStatement*, SgStatement*> inheritDir; // PAIR<dir, insertBefore>        
        while (st != lastNode)
        {
            if (st == NULL)
            {
                string message;
                __spf_printToBuf(message, "internal error in analysis, parallel directives will not be generated for this file!");
                messagesForFile.push_back(Messages(ERROR, 1, message, 3008));

                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }
            
            if (st->variant() == CONTAINS_STMT)
                break;

            const int currV = st->variant();
            if (currV == VAR_DECL || currV == VAR_DECL_90 || currV == DIM_STAT)
            {
                SgVarDeclStmt *varDecl = (SgVarDeclStmt*)st;
                SgExpression *varList = varDecl->varList();

                set<DIST::Array*> dynamicArrays;
                set<DIST::Array*> dynamicArraysLocal;
                map<string, DIST::Array*> dynamicArraysStr;
                while (varList)
                {
                    if (varList->lhs()->variant() == ARRAY_REF)
                    {
                        if (distrArrays.find(OriginalSymbol(varList->lhs()->symbol())->identifier()) != distrArrays.end())
                        {
                            SgSymbol *currSymb = OriginalSymbol(varList->lhs()->symbol());
                            const string currArray(currSymb->identifier());
                            auto toFind = std::make_pair(currSymb->identifier(), declaratedInStmt(currSymb)->lineNumber());
                            auto itS = tableOfUniqNames.find(toFind);

                            if (itS != tableOfUniqNames.end())
                            {
                                const string fullArrayName = getShortName(itS->second);
                                pair<DIST::Array*, string> dirWithArray = getNewDirective(fullArrayName, distrRules, alignRules, dataDir);
                                
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

                                    const pair<tuple<string, string, string>, string> &templDir =
                                        getNewTemplateDirective(dirWithArray.first, allArrays, reducedG, dataDir, distrRules, arrayLinksByFuncCalls, regionId);
                                    string templDecl = std::get<0>(templDir.first);

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

                                    if (templateDelc.find(templDecl) == templateDelc.end())
                                        templateDelc.insert(templDecl);
                                    else
                                        templDecl = "";
                                    
                                    if (templDecl != "")
                                        templDecl = createFullTemplateDir(templDir.first);

                                    if (!strcmp(st->fileName(), fin_name))
                                    {
                                        if (modulesAndFuncs[i]->variant() == PROG_HEDR)
                                            templDecl = "";

                                        const string toAdd = templDecl + toInsert;
                                        if (extractDir)
                                            extractComments(st, toAdd); 
                                        else
                                            st->addComment(toAdd.c_str());
                                    }
                                    else
                                    {
                                        addStringToComments({ templDecl, toInsert }, commentsToInclude, st->fileName(), st->lineNumber());
                                        templateDeclInIncludes[st->fileName()] = templDecl;
                                    }
                                }
                            }
                        }
                    }
                    varList = varList->rhs();
                }

                string toInsert = "!DVM$ DYNAMIC ";
                int z = 0;
                for (auto &array : dynamicArraysLocal)
                {
                    if (array->GetLocation().first != 0) // not local
                    {
                        if (z != 0)
                            toInsert += ",";
                        toInsert += array->GetShortName();
                        ++z;
                    }
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
                inheritDir.second->insertStmtBefore(*inheritDir.first, *inheritDir.second->controlParent());
            else
                inheritDir.second->lexPrev()->deleteStmt();
        }
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

    map<string, pair<SgExpression*, SgExpression*>> &insertedShadow = insertedShadowByFile[fin_name];

    for (int i = 0; i < modulesAndFuncs.size(); ++i)
    {
        SgStatement *st = modulesAndFuncs[i];
        SgStatement *lastNode = st->lastNodeOfStmt();
                
        while (st != lastNode)
        {
            if (st == NULL)
            {
                string message;
                __spf_printToBuf(message, "internal error in analysis, parallel directives will not be generated for this file!");
                messagesForFile.push_back(Messages(ERROR, 1, message, 3008));

                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            const int currV = st->variant();
            if (currV == VAR_DECL || currV == VAR_DECL_90 || currV == DIM_STAT)
            {
                SgVarDeclStmt *varDecl = (SgVarDeclStmt*)st;
                SgExpression *varList = varDecl->varList();
                
                set<DIST::Array*> declaratedDistrArrays;
                while (varList)
                {
                    if (varList->lhs()->variant() == ARRAY_REF)
                    {
                        if (distrArrays.find(OriginalSymbol(varList->lhs()->symbol())->identifier()) != distrArrays.end())
                        {
                            SgSymbol *currSymb = OriginalSymbol(varList->lhs()->symbol());
                            auto toFind = std::make_pair(currSymb->identifier(), declaratedInStmt(currSymb)->lineNumber());
                            auto itS = tableOfUniqNames.find(toFind);

                            if (itS != tableOfUniqNames.end())
                                declaratedDistrArrays.insert(declaratedArrays.find(itS->second)->second.first);
                        }
                    }
                    varList = varList->rhs();
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