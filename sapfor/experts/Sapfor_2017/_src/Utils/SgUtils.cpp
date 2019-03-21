#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <string>
#include <assert.h>
#include <locale>
#include <algorithm>

#include "SgUtils.h"
#include "errors.h"
#include "../Sapfor.h"

#include "../LoopAnalyzer/directive_parser.h"
#include "../Distribution/Distribution.h"

#include "../GraphCall/graph_calls.h"
#include "../GraphCall/graph_calls_func.h"
#include "../CreateInterTree/CreateInterTree.h"
#include "../Predictor/PredictScheme.h"

using std::map;
using std::pair;
using std::tuple;
using std::set;
using std::vector;
using std::string;
using std::make_pair;
using std::make_tuple;

const char *tag[];

static bool ifIntervalExists(const vector<pair<int, int>> &intervals, const pair<int, int> &toFind)
{
    bool retVal = false;

    for (auto &elem : intervals)
    {
        if (toFind.first <= elem.first && toFind.second >= elem.second)
        {
            retVal = true;
            break;
        }
    }

    return retVal;
}

static bool ifDir(const string &line)
{
    if (line.size() >= 10 && (line[0] == '!' || line[0] == 'c'))
    {
        string dir(line.begin() + 1, line.begin() + 1 + 4);
        if (dir == "$spf" || dir == "dvm$")
            return true;
    }
    return false;
}
 
static string replaceTabsToSpaces(const string &in)
{
    string ret = ""; 
    for (auto &elem : in)
    {
        if (elem == '\t')
            ret += "    ";
        else
            ret += elem;
    }
    return ret;
}
static map<string, pair<string, vector<pair<int, int>> > > findIncludes(FILE *currFile)
{
    map<string, pair<string, vector<pair<int, int>> > > includeFiles;
    bool notClosed = false;
    // TODO: extend buff size in dynamic
    char buf[8192];
    int lineBefore = 0;
    while (!feof(currFile))
    {
        char *read = fgets(buf, 8192, currFile);
        if (read)
        {
            const string orig(replaceTabsToSpaces(read));
            string line(read);
            convertToLower(line);
            line = replaceTabsToSpaces(line);

            size_t posF = line.find("include");
            if (posF != string::npos)
            {
                //check if 'inclide' - operator
                for (size_t k = 0; k < posF; ++k)
                {
                    if (line[k] != ' ')
                    {
                        posF = -1;
                        break;
                    }
                }
                if (posF == -1)
                {
                    ++lineBefore;
                    continue;
                }

                posF += sizeof("include") - 1;
                int tok = 0;
                size_t st = -1, en;

                for (size_t k = posF; k < line.size(); ++k)
                {
                    if (line[k] == '\'' && tok == 1)
                        break;
                    else if (line[k] == '\'')
                        tok++;
                    else if (tok == 1 && st == -1)
                        st = k;
                    else
                        en = k;
                }
                const string inclName(orig.begin() + st, orig.begin() + en + 1);

                auto toInsert = includeFiles.find(inclName);
                if (toInsert == includeFiles.end())
                {
                    toInsert = includeFiles.insert(toInsert, make_pair(inclName, make_pair(orig, vector<pair<int, int>>())));
                    toInsert->second.second.push_back(make_pair(lineBefore, -1));
                    notClosed = true;
                }
                else
                {
                    toInsert->second.second.push_back(make_pair(lineBefore, -1));
                    notClosed = true;
                }
                //printf("insert %s -> %s\n", inclName.c_str(), line.c_str());
            }
            else if ((line[0] != 'c' && line[0] != '!' && line != "" && line[0] != '\n') || ifDir(line))
            {
                if (notClosed)
                {
                    for (auto &elem : includeFiles)
                        for (auto &pair : elem.second.second)
                            if (pair.second == -1)
                                pair.second = lineBefore + 1;
                    notClosed = false;
                }
            }
        }
        ++lineBefore;
    }

    return includeFiles;
}

//TODO: read includes and find last lines, all included files
void removeIncludeStatsAndUnparse(SgFile *file, const char *fileName, const char *fout, 
                                  set<string> &allIncludeFiles, bool outFree)
{ 
    fflush(NULL);

    int funcNum = file->numberOfFunctions();
    FILE *currFile = fopen(fileName, "r");
    if (currFile == NULL)
    {
        char buf[256];
        sprintf(buf, "ERROR: Can't open file %s for read", fileName);
        addToGlobalBufferAndPrint(buf);
        throw(-1);
    }

    // name -> unparse comment
    map<string, pair<string, vector<pair<int, int>> > > includeFiles = findIncludes(currFile);
    //add spaces if needed
    if (!outFree)
    {
        for (auto &elem : includeFiles)
        {
            int countSpaces = 0;
            for (int z = 0; z < elem.second.first.size() && elem.second.first[z] == ' '; ++z, ++countSpaces) { }

            if (countSpaces < 6)
            {
                while (countSpaces != 6)
                {
                    elem.second.first.insert(elem.second.first.begin(), ' ');
                    countSpaces++;
                }
            }
        }
    }

    const string fileN = file->filename();
    //insert comment
    int lineBefore = -1;

    map<string, vector<pair<int, int>> > insertedIncludeFiles;
    map<int, pair<int, int>> placesForInsert;

    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        string currFileName = st->fileName();
        if (currFileName != fileN)
        {
            allIncludeFiles.insert(currFileName);
            auto it = includeFiles.find(currFileName);

            if (it != includeFiles.end())
            {
                pair<int, int> lines = make_pair(lineBefore, -1);

                SgStatement *locSt = st->lexNext();
                set<string> nearIncludes;

                while (locSt && (locSt->fileName() != fileN || locSt->lineNumber() <= 0))
                {
                    const string locName = locSt->fileName();

                    if (locName != fileN)
                    {
                        allIncludeFiles.insert(locName);
                        if (locName != currFileName)
                        {
                            auto itNear = includeFiles.find(locName);
                            if (itNear != includeFiles.end())
                                nearIncludes.insert(locName);
                        }
                    }
                    locSt = locSt->lexNext();
                }

                if (locSt)
                {
                    lines.second = locSt->lineNumber();
                    st = locSt;

                    bool change = true;
                    while (change)
                    {
                        change = false;
                        SgStatement *prev = locSt->lexPrev();
                        if (prev && 
                            (prev->variant() == DVM_PARALLEL_ON_DIR || 
                             prev->variant() == SPF_ANALYSIS_DIR || 
                             prev->variant() == SPF_TRANSFORM_DIR ||
                             prev->variant() == DVM_INTERVAL_DIR))
                        {
                            locSt = prev;
                            change = true;
                        }
                    }
                    placesForInsert.insert(make_pair(locSt->id(), lines));
                }
            }           
        }
        else
            lineBefore = st->lineNumber();
    }

    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        for (auto &it : includeFiles)
        {
            auto found = placesForInsert.find(st->id());
            if (found != placesForInsert.end())
            {
                if (ifIntervalExists(it.second.second, found->second))
                {
                    allIncludeFiles.insert(it.first);
                    if (st->comments())
                    {
                        string comments = st->comments();
                        if (comments.find(it.second.first) == string::npos)
                        {
                            const size_t pos = comments.rfind("include");
                            if (pos == string::npos)
                                st->setComments((it.second.first + comments).c_str());
                            else
                                st->setComments((comments.insert(comments.find('\n', pos) + 1, it.second.first)).c_str());
                        }
                    }
                    else
                        st->addComment(it.second.first.c_str());
                }
            }
        }
    }

    for (auto &inserted : insertedIncludeFiles)
    {
        auto it = includeFiles.find(inserted.first);
        if (it == includeFiles.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (inserted.second.size() != it->second.second.size())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    //remove
    //XXX: use Sage hack!!
    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
        if (st->fileName() != fileN || st->getUnparseIgnore())
            st->setVariant(-1 * st->variant());

#ifdef _WIN32
    FILE *fOut;
    errno_t err = fopen_s(&fOut, fout, "w");
#else
    int err = 0;
    FILE *fOut = fopen(fout, "w");
#endif
    if (fOut == NULL)
    {
        if (fout)
            __spf_print(1, "can not open file to write with name '%s' with error %d\n", fout, err);
        else
            __spf_print(1, "can not open file to write with name 'NULL'\n");
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    file->unparse(fOut);
    fclose(fOut);
    fclose(currFile);

    //restore
    //XXX: use Sage hack!!
    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
        if (st->fileName() != fileN && st->variant() < 0 || st->getUnparseIgnore())
            st->setVariant(-1 * st->variant());
}

static map<SgFile*, map<string, vector<SgSymbol*>>> allCreatedSymbols;

SgSymbol* findSymbolOrCreate(SgFile *file, const string toFind, SgType *type, SgStatement *scope)
{
    auto createdSymbols = allCreatedSymbols.find(file);
    if (createdSymbols == allCreatedSymbols.end())
        createdSymbols = allCreatedSymbols.insert(createdSymbols, make_pair(file, map<string, vector<SgSymbol*>>()));    

    SgSymbol *symb = file->firstSymbol();

    while (symb)
    {
        if (symb->identifier() == toFind)
        {
            if (symb->scope() == scope)
                if (symb->type() && symb->type()->equivalentToType(type))
                    return symb;
        }
        symb = symb->next();
    }

    auto result = createdSymbols->second.find(toFind);

    if (result == createdSymbols->second.end())
        result = createdSymbols->second.insert(result, make_pair(toFind, vector<SgSymbol*>()));

    SgSymbol *newS = NULL;
    for (auto &symbs : result->second)
    {
        if (symbs->scope() == scope && scope)
        {
            if (symbs->type() && type)
            {
                if (symbs->type()->equivalentToType(type))
                {
                    newS = symbs;
                    break;
                }
            }
            else
            {
                newS = symbs;
                break;
            }
        }
        else
        {
            newS = symbs;
            break;
        }
    }

    if (newS == NULL)
    {
        newS = new SgSymbol(VARIABLE_NAME, toFind.c_str(), type, scope);
        result->second.push_back(newS);
    }    
    return newS;
}

static string getValue(SgExpression *exp)
{
    if (exp == NULL)
        return "";

    string ret = "";
    if (exp->symbol())
    {
        if (exp->symbol()->identifier())
            ret = "(" + string(exp->symbol()->identifier()) + ")";
    }
    else if (exp->variant() == INT_VAL)
        ret = "(" + std::to_string(exp->valueInteger()) + ")";
    else if (exp->variant() == ADD_OP)
        ret = "(+)";
    else if (exp->variant() == SUBT_OP)
        ret = "(-)";
    else if (exp->variant() == MULT_OP)
        ret = "(*)";
    else if (exp->variant() == DIV_OP)
        ret = "(/)";
    else if (exp->variant() == MOD_OP)
        ret = "(mod)";
    else if (exp->variant() == EXP_OP)
        ret = "(**)";
    else if (exp->variant() == KEYWORD_VAL)
        ret = "(" + string(((SgKeywordValExp*)exp)->value()) + ")";
    return ret;
}

static void recExpressionPrint(SgExpression *exp, const int lvl, const char *LR, const int currNum, int &allNum)
{
    if (exp)
    {
        SgExpression *lhs = exp->lhs();
        SgExpression *rhs = exp->rhs();
        int lNum, rNum;

        string vCurr = getValue(exp);
        string vL = getValue(lhs);
        string vR = getValue(rhs);

        if (lhs && rhs)
        {
            lNum = allNum + 1;
            rNum = allNum + 2;
            allNum += 2;
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_L_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), lNum, lvl + 1, tag[lhs->variant()], vL.c_str());
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_R_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), rNum, lvl + 1, tag[rhs->variant()], vR.c_str());
        }
        else if (lhs)
        {
            lNum = allNum + 1;
            allNum++;
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_L_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), lNum, lvl + 1, tag[lhs->variant()], vL.c_str());
        }
        else if (rhs)
        {
            rNum = allNum + 1;
            allNum++;
            printf("\"%d_%d_%s_%s_%s\" -> \"%d_%d_R_%s_%s\";\n", currNum, lvl, LR, tag[exp->variant()], vCurr.c_str(), rNum, lvl + 1, tag[rhs->variant()], vR.c_str());
        }
        if (lhs)
            recExpressionPrint(lhs, lvl + 1, "L", lNum, allNum);
        if (rhs)
            recExpressionPrint(rhs, lvl + 1, "R", rNum, allNum);
    }
}

void recExpressionPrint(SgExpression *exp)
{
    printf("digraph G{\n");
    int allNum = 0;
    recExpressionPrint(exp, 0, "L", allNum, allNum);
    if (allNum == 0 && exp)
        printf("\"%d_%d_%s_%s_%s\";\n", allNum, 0, "L", tag[exp->variant()], getValue(exp).c_str());    
    printf("};\n");
    fflush(NULL);
}

void initTags()
{
    for (int i = 0; i < MAXTAGS; i++)
        tag[i] = NULL;

#include "tag.h"
}


void findModulesInFile(SgFile *file, vector<SgStatement*> &modules)
{
    SgStatement *first = file->firstStatement();
    set<SgStatement*> functions;

    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
        functions.insert(file->functions(i));

    while (first)
    {
        if (first->variant() == MODULE_STMT)
        {
            modules.push_back(first);
            first = first->lastNodeOfStmt();
        }
        else
        {
            if (functions.size())
            {
                auto it = functions.find(first);
                if (it != functions.end())
                    first = (*it)->lastNodeOfStmt();
            }
        }

        first = first->lexNext();
    }
}

void getModulesAndFunctions(SgFile *file, vector<SgStatement*> &modulesAndFunctions)
{
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
        modulesAndFunctions.push_back(file->functions(i));

    findModulesInFile(file, modulesAndFunctions);
}

bool isSPF_comment(const int var)
{    
    return var == SPF_ANALYSIS_DIR || var == SPF_PARALLEL_DIR || var == SPF_TRANSFORM_DIR || var == SPF_PARALLEL_REG_DIR || var == SPF_END_PARALLEL_REG_DIR;
}

void tryToFindPrivateInAttributes(SgStatement *st, set<string> &privatesVars)
{
    for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ SPF_ANALYSIS_DIR, SPF_PARALLEL_DIR }))
    {
        if (data)
        {
            Statement *sData = new Statement(data);
            fillPrivatesFromComment(sData, privatesVars);

            // try to find reductions and set its symbols as private in 
            // current loop analysis for correct scalar detection in 
            // tryToFindDependencies() function
            map<string, set<string>> reductions;
            map<string, set<tuple<string, string, int>>> reductionsLoc;

            fillReductionsFromComment(sData, reductions);
            fillReductionsFromComment(sData, reductionsLoc);

            for (auto &redList : reductions)
                privatesVars.insert(redList.second.begin(), redList.second.end());

            for (auto &redLocList : reductionsLoc)
            {
                for (auto &groupList : redLocList.second)
                {
                    privatesVars.insert(std::get<0>(groupList));
                    privatesVars.insert(std::get<1>(groupList));
                }
            }
        }
    }
}

void fillNonDistrArraysAsPrivate(SgStatement *st,
                                 const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                 const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                                 set<string> &privatesVars)
{
    // fill as private all non distributed arrays
    auto it = declaratedArraysSt.find(st);
    if (it != declaratedArraysSt.end())
    {
        for (auto itSet = it->second.begin(); itSet != it->second.end(); ++itSet)
        {
            auto itD = declaratedArrays.find(*itSet);
            if (itD != declaratedArrays.end())
                if (itD->second.first->GetNonDistributeFlag())
                    privatesVars.insert(itD->second.first->GetShortName());
        }
    }
}

extern  map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaratedArrays;
extern  map<SgStatement*, set<tuple<int, string, string>>> declaratedArraysSt;

DIST::Array* getArrayFromDeclarated(SgStatement *st, const string &arrayName)
{
    DIST::Array *found = NULL;

    auto it = declaratedArraysSt.find(st);
    if (it != declaratedArraysSt.end())
    {
        for (auto itSet = it->second.begin(); itSet != it->second.end() && !found; ++itSet)
        {
            auto itD = declaratedArrays.find(*itSet);
            if (itD != declaratedArrays.end())
                if (itD->second.first->GetShortName() == arrayName)
                    found = itD->second.first;
        }
    }
    return found;
}

static bool findSymbol(SgExpression *declLst, const string &toFind)
{
    bool ret = false;
    if (declLst)
    {
        if (declLst->lhs())
        {
            if (declLst->lhs()->variant() == EXPR_LIST || declLst->lhs()->variant() == ASSGN_OP)
                ret = ret || findSymbol(declLst->lhs(), toFind);
            else if (declLst->lhs()->symbol())
            {
                if (declLst->lhs()->symbol()->identifier() == toFind)
                    return true;
            }
        }

        if (declLst->rhs())
            ret = ret || findSymbol(declLst->rhs(), toFind);
    }
    return ret;
}

extern map<string, vector<Messages>> SPF_messages;
SgStatement* declaratedInStmt(SgSymbol *toFind, vector<SgStatement*> *allDecls, bool printInternal)
{
    //need to call this function for MODULE symbols!
    toFind = OriginalSymbol(toFind);
    vector<SgStatement*> inDecl;
    SgStatement *start = toFind->scope();

    if (start)
    {
        SgStatement *end = start->lastNodeOfStmt();
        while (start != end)
        {
            //error ?
            if (start == NULL)
                break;

            //printf("%d\n", start->variant());
            if (start->variant() == VAR_DECL ||
                start->variant() == VAR_DECL_90 ||
                start->variant() == ALLOCATABLE_STMT ||
                start->variant() == DIM_STAT || 
                start->variant() == COMM_STAT || 
                start->variant() == HPF_TEMPLATE_STAT || 
                start->variant() == DVM_VAR_DECL)
            {
                for (int i = 0; i < 3; ++i)
                {
                    SgExpression *declLst = start->expr(i);
                    if (findSymbol(declLst, toFind->identifier()))
                        inDecl.push_back(start);
                }
            }
            start = start->lexNext();
        }
    }

    /*if (inDecl.size() == 0)
    {
        SgStatement *lowLevelDecl = toFind->declaredInStmt();
        if (lowLevelDecl)
            inDecl.push_back(lowLevelDecl);
    }*/

    if (inDecl.size() == 0)
    {
        if (printInternal)
        {
            __spf_print(1, "can not find declaration for symbol '%s'\n", toFind->identifier());

            auto itM = SPF_messages.find(start->fileName());
            if (itM == SPF_messages.end())
                itM = SPF_messages.insert(itM, make_pair(start->fileName(), vector<Messages>()));

            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"Can not find declaration for symbol '%s' in current scope", to_wstring(toFind->identifier()).c_str());
            itM->second.push_back(Messages(ERROR, toFind->scope()->lineNumber(), bufw, 1017));
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        return NULL;
    }

    if (allDecls)
        *allDecls = inDecl;

    //return statement by priority: VAR_DECL, VAR_DECL_90, ALLOCATABLE_STMT, DIM_STAT, other
    if (inDecl.size() > 1)
    {
        for (int i = 0; i < inDecl.size(); ++i)
            if (inDecl[i]->variant() == VAR_DECL || inDecl[i]->variant() == VAR_DECL_90)
                return inDecl[i];

        for (int i = 0; i < inDecl.size(); ++i)
            if (inDecl[i]->variant() == ALLOCATABLE_STMT)
                return inDecl[i];

        for (int i = 0; i < inDecl.size(); ++i)
            if (inDecl[i]->variant() == DIM_STAT)
                return inDecl[i];

        for (int i = 0; i < inDecl.size(); ++i)
            if (inDecl[i]->variant() == COMM_STAT)
                return inDecl[i];

        for (int i = 0; i < inDecl.size(); ++i)
            if (inDecl[i]->variant() == HPF_TEMPLATE_STAT)
                return inDecl[i];

        for (int i = 0; i < inDecl.size(); ++i)
            if (inDecl[i]->variant() == DVM_VAR_DECL)
                return inDecl[i];

        for (int i = 0; i < inDecl.size(); ++i)
            return inDecl[i];

        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        return NULL;
    }
    else
        return inDecl[0];
}

bool isDVM_stat(SgStatement *st)
{
    bool ret = false;

    const int var = st->variant();

    //for details see dvm_tag.h
    if ((var >= 128 && var <= 129) ||
        (var >= 146 && var <= 149) ||
        (var >= 211 && var <= 224) ||
        (var >= 247 && var <= 249) ||
        (var >= 605 && var < 626) ||
        (var > 626 && var <= 634) ||
        (var >= 900 && var <= 949) ||
        (var == 277 || var == 299) ||
        (var == 296) ||
        (var >= 705 && var == 740))
        ret = true;
    return ret;
}

bool isSPF_stat(SgStatement *st)
{
    bool ret = false;

    const int var = st->variant();
    //for details see dvm_tag.h
    if (var >= 950 && var <= 958)
        ret = true;
    return ret;
}

static map<SgExpression*, string>::const_iterator getStringExpr(SgExpression *ex, map<SgExpression*, string> &collection)
{
    auto it = collection.find(ex);
    if (it == collection.end())
        it = collection.insert(it, make_pair(ex, ex->unparse()));
    return it;
}

bool isEqExpressions(SgExpression *left, SgExpression *right, map<SgExpression*, string> &collection)
{
    if (left == right)
        return true;
    else if (left == NULL || right == NULL)
        return false;
    else
        return getStringExpr(left, collection)->second == getStringExpr(right, collection)->second;
}

static string getCommonName(SgExpression *common)
{
    if (common->symbol())
        return string(common->symbol()->identifier());
    else
        return string("spf_unnamed");
}

void getCommonBlocksRef(map<string, vector<SgExpression*>> &commonBlocks, SgStatement *start, SgStatement *end, const string *nameToSkip)
{
    while (start != end)
    {
        if (start->variant() == CONTAINS_STMT)
            break;

        if (start->variant() == COMM_STAT)
        {
            // fill all common blocks
            for (SgExpression *exp = start->expr(0); exp; exp = exp->rhs())
            {
                const string commonName = getCommonName(exp);

                if (nameToSkip && *nameToSkip == commonName)
                    continue;

                auto it = commonBlocks.find(commonName);
                if (it == commonBlocks.end())
                    it = commonBlocks.insert(it, make_pair(commonName, vector<SgExpression*>()));
                it->second.push_back(exp);
            }
        }
        start = start->lexNext();
    }
}

static SgExpression* isInCommon(const vector<SgExpression*> &commonBlocks, const char *arrayName, int &commonPos)
{
    commonPos = 0;
    for (auto &common : commonBlocks)
    {
        for (SgExpression *currCommon = common->lhs(); currCommon; currCommon = currCommon->rhs())
        {
            if (!strcmp(currCommon->lhs()->symbol()->identifier(), arrayName))
                return common;
            commonPos++;
        }
    }
    return NULL;
}

static map<tuple<string, string, int>, tuple<int, string, string>> tableOfUniqNames;
tuple<int, string, string> getUniqName(const map<string, vector<SgExpression*>> &commonBlocks, SgStatement *decl, SgSymbol *symb)
{
    bool inCommon = false;
    bool needtoCheck = true;
    int commonPos = 0;

    SgExpression *foundCommon = NULL;

    SgStatement *declCP = decl->controlParent();
    // find symbol in parameter list of functions
    if (declCP->variant() == PROC_HEDR || declCP->variant() == FUNC_HEDR)
    {
        if (declCP->variant() == PROC_HEDR)
        {
            const int num = ((SgProcHedrStmt*)declCP)->numberOfParameters();
            for (int i = 0; i < num && needtoCheck; ++i)
                if (!strcmp(((SgProcHedrStmt*)declCP)->parameter(i)->identifier(), symb->identifier()))
                    needtoCheck = false;
        }
        else
        {
            const int num = ((SgFuncHedrStmt*)declCP)->numberOfParameters();
            for (int i = 0; i < num && needtoCheck; ++i)
                if (!strcmp(((SgFuncHedrStmt*)declCP)->parameter(i)->identifier(), symb->identifier()))
                    needtoCheck = false;
        }        
    }

    if (needtoCheck)
    {
        for (auto &common : commonBlocks)
        {
            foundCommon = isInCommon(common.second, symb->identifier(), commonPos);
            if (foundCommon)
            {
                inCommon = true;
                break;
            }
        }
    }

    tuple<int, string, string> retVal;
    if (inCommon)
        retVal = make_tuple(commonPos, string("common_") + getCommonName(foundCommon), string(symb->identifier()));
    else
        retVal = make_tuple(decl->lineNumber(), string(decl->fileName()), string(symb->identifier()));

    auto key = make_tuple(symb->identifier(), decl->fileName(), decl->lineNumber());
    auto it = tableOfUniqNames.find(key);
    if (it == tableOfUniqNames.end())
        tableOfUniqNames.insert(it, make_pair(key, retVal));
    else
    {
        if (it->first != key)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    return retVal;
}

tuple<int, string, string> getFromUniqTable(SgSymbol *symb)
{
    auto place = declaratedInStmt(symb);
    auto localIt = tableOfUniqNames.find(std::make_tuple(symb->identifier(), place->fileName(), place->lineNumber()));
    if (localIt == tableOfUniqNames.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    
    return localIt->second;
}

SgStatement* findMainUnit(SgProject *proj)
{
    SgStatement *mainUnit = NULL;
    
    for (int i = proj->numberOfFiles() - 1; i >= 0; --i)
    {
        SgFile *file = &(proj->file(i));
        current_file_id = i;
        current_file = file;
        const char *file_name = file->filename();

        
        for (int k = 0; k < file->numberOfFunctions(); ++k)
        {
            SgStatement *func = file->functions(k);
            if (func->variant() == PROG_HEDR)
            {
                mainUnit = func;
                break;
            }
        }

        if (mainUnit)
            break;
    }
    return mainUnit;
}

template<typename IN_TYPE, typename OUT_TYPE>
const vector<OUT_TYPE> getAttributes(IN_TYPE st, const set<int> dataType)
{
    vector<OUT_TYPE> outData;

    for (int i = 0; i < st->numberOfAttributes(); ++i)
    {
        SgAttribute *attr = st->getAttribute(i);
        const int type = st->attributeType(i);
        if (dataType.find(type) != dataType.end())
            if (attr->getAttributeData())
                outData.push_back((OUT_TYPE)(attr->getAttributeData()));
    }

    return outData;
}

template const vector<SgSymbol*> getAttributes(SgSymbol *st, const set<int> dataType);
template const vector<char*> getAttributes(SgSymbol *st, const set<int> dataType);
template const vector<SgStatement*> getAttributes(SgStatement *st, const set<int> dataType);
template const vector<SgExpression*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<SgStatement*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<DIST::Array*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<int*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<FuncInfo*> getAttributes(SgStatement *st, const set<int> dataType);

static int isParameterOneOfThese(const string& name, const vector<string>& names)
{
    int parameterOfFunctionItself = -1;
    for (int i = 0; i < names.size(); ++i)
        if (name == names[i])
        {
            parameterOfFunctionItself = i;
            break;
        }
    return parameterOfFunctionItself;
}

#define DEF_T 0
#define USE_T 1
#define DEF_USE_T 2

static void processPartOfAssign(int type, SgExpression *exp, vector<DefUseList> &currentLists, SgFile *file, SgStatement *inStat, 
                                vector<string> &parameterNames, pair<SgSymbol*, string> underCall, int funcPos);

static void addSymbolsToDefUse(const int type, SgExpression *ex, vector<DefUseList> &currentList, 
                               pair<SgSymbol*, string> underCall, int funcPos,
                               SgFile *file, SgStatement *inStat, vector<string>& parameterNames)
{
    if (ex)
    {
        bool next = true;
        if (ex->variant() == VAR_REF || ex->variant() == ARRAY_REF)
        {
            if (ex->symbol())
            {
                string name = string(ex->symbol()->identifier());
                currentList.push_back(DefUseList(type, inStat, ex, file, underCall, make_pair(ex->symbol(), name), funcPos, isParameterOneOfThese(name, parameterNames)));
            }
        }
        else if (ex->variant() == FUNC_CALL)
        {
            underCall = make_pair(ex->symbol(), string(ex->symbol()->identifier()));
            funcPos = 0;

            bool isIntrinsic = isIntrinsicFunctionName(ex->symbol()->identifier());
            for (SgExpression *list = ex->lhs(); list; list = list->rhs(), funcPos++)
            {
                if (!isIntrinsic)
                    processPartOfAssign(DEF_USE_T, list->lhs(), currentList, file, inStat, parameterNames, underCall, funcPos);
                else
                    addSymbolsToDefUse(type, list->lhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
            }
            next = false;
        }

        if (next)
        {
            addSymbolsToDefUse(type, ex->lhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
            addSymbolsToDefUse(type, ex->rhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
        }
    }    
}

static void processPartOfAssign(int type, SgExpression *exp, vector<DefUseList> &currentList, SgFile *file, SgStatement *inStat,
                                vector<string> &parameterNames, pair<SgSymbol*, string> underCall, int funcPos)
{
    if (exp->symbol() && exp->variant() == VAR_REF) // simple assign
    {
        SgSymbol *tmp = exp->symbol();        
        string name = string(tmp->identifier());

        if (type == DEF_USE_T)
        {
            currentList.push_back(DefUseList(DEF_T, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
            currentList.push_back(DefUseList(USE_T, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
        }
        else
            currentList.push_back(DefUseList(DEF_T, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
    }
    //TODO
    else // array ref and etc.
    {
        if (exp->variant() == ARRAY_OP)
        {            
            SgSymbol *tmp = exp->lhs()->symbol();
            string name = string(tmp->identifier());

            if (type == DEF_USE_T)
            {
                currentList.push_back(DefUseList(DEF_T, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
                currentList.push_back(DefUseList(USE_T, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
            }
            else
                currentList.push_back(DefUseList(type, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
            
            addSymbolsToDefUse(1, exp->lhs()->lhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
            addSymbolsToDefUse(1, exp->lhs()->rhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
        }
        else if (exp->variant() == ARRAY_REF)
        {
            SgSymbol *tmp = exp->symbol();            
            string name = string(tmp->identifier());

            if (type == DEF_USE_T)
            {
                currentList.push_back(DefUseList(DEF_T, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
                currentList.push_back(DefUseList(USE_T, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
            }
            else
                currentList.push_back(DefUseList(type, inStat, exp, file, underCall, make_pair(tmp, name), funcPos, isParameterOneOfThese(name, parameterNames)));
            
            addSymbolsToDefUse(1, exp->lhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
            addSymbolsToDefUse(1, exp->rhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
        }
        else
        {
            addSymbolsToDefUse(1, exp->lhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
            addSymbolsToDefUse(1, exp->rhs(), currentList, underCall, funcPos, file, inStat, parameterNames);
        }
    }
}

static void inline addToLists(map<string, vector<DefUseList>> &currentLists, const vector<DefUseList> &tmpList)
{
    for (auto &list : currentLists)
        for (auto &elem : tmpList)
            list.second.push_back(elem);
}

void constructDefUseStep1(SgFile *file, map<string, vector<DefUseList>> &defUseByFunctions, map<string, vector<FuncInfo*>> &allFuncInfo)
{
    map<string, vector<FuncInfo*>> curFileFuncInfo;
    vector<LoopGraph*> tmpL;
    functionAnalyzer(file, curFileFuncInfo, tmpL);
    auto whereToCopy = allFuncInfo.insert(make_pair(file->filename(), vector<FuncInfo*>()));
    for(auto& it : curFileFuncInfo.begin()->second)
        whereToCopy.first->second.push_back(it);

    map<string, FuncInfo*> funcToFuncInfo = map<string, FuncInfo*>();
    for (int i = 0; i < curFileFuncInfo.begin()->second.size(); ++i)
        funcToFuncInfo.insert(make_pair(curFileFuncInfo.begin()->second[i]->funcName, curFileFuncInfo.begin()->second[i]));

    for (int f = 0; f < file->numberOfFunctions(); ++f)
    {
        //function header and entry points
        map<string, vector<DefUseList>> currentLists;
        vector<DefUseList> tmpList;
        vector<string> parameterNames = vector<string>();

        SgStatement *start = file->functions(f);
        SgStatement *end = start->lastNodeOfStmt();
        int pos;

        auto founded = funcToFuncInfo.find(((SgProgHedrStmt*)start)->nameWithContains());
        start->addAttribute(PROC_CALL, (void*)founded->second, sizeof(FuncInfo));

        SgProgHedrStmt *header = isSgProgHedrStmt(start);
        if (header && start->variant() != PROG_HEDR)
            for (int i = 0; i < header->numberOfParameters(); ++i)
                parameterNames.push_back(header->parameter(i)->identifier());

        currentLists[string(start->symbol()->identifier())] = vector<DefUseList>();
        for (SgStatement *st = start->lexNext(); st != end; st = st->lexNext())
        {
            if (isSgExecutableStatement(st))
            {
                tmpList.clear();
                switch (st->variant())
                {
                case ASSIGN_STAT:
                    processPartOfAssign(DEF_T, st->expr(0), tmpList, file, st, parameterNames, make_pair((SgSymbol*)NULL, string("")), -1);
                    addSymbolsToDefUse(USE_T, st->expr(1), tmpList, make_pair((SgSymbol*)NULL, string("")), -1, file, st, parameterNames);

                    addToLists(currentLists, tmpList);                    
                    break;
                case FOR_NODE:
                    if (st->symbol())
                        for (auto &list : currentLists)
                        {
                            string name = string(st->symbol()->identifier());
                            auto vr = new SgVarRefExp(*(st->symbol()));

                            list.second.push_back(DefUseList(1, st, vr, file, make_pair((SgSymbol*)NULL, string("")), make_pair(st->symbol(), name), -1, isParameterOneOfThese(name, parameterNames)));
                            list.second.push_back(DefUseList(0, st, vr, file, make_pair((SgSymbol*)NULL, string("")), make_pair(st->symbol(), name), -1, isParameterOneOfThese(name, parameterNames)));
                        }

                    for (int i = 0; i < 3; ++i)
                        addSymbolsToDefUse(USE_T, st->expr(i), tmpList, make_pair((SgSymbol*)NULL, string("")), -1, file, st, parameterNames);
                    addToLists(currentLists, tmpList);
                    break;                
                case READ_STAT:
                    {
                        SgInputOutputStmt *io = isSgInputOutputStmt(st);
                        auto list = io->itemList();
                        int pos = 0;
                        while (list)
                        {
                            if (list->lhs())
                                processPartOfAssign(DEF_T, list->lhs(), tmpList, file, st, parameterNames, make_pair(io->symbol(), string("READ")), pos);
                            pos++;
                            list = list->rhs();
                        }
                    }
                    addToLists(currentLists, tmpList);
                    break;
                case PROC_STAT:
                    pos = 0;
                    for (SgExpression *ex = st->expr(0); ex; ex = ex->rhs(), pos++)
                        processPartOfAssign(DEF_USE_T, ex->lhs(), tmpList, file, st, parameterNames, make_pair(st->symbol(), string(st->symbol()->identifier())), pos);
                    addToLists(currentLists, tmpList);
                    break;
                case ENTRY_STAT:
                    currentLists[string(st->symbol()->identifier())] = vector<DefUseList>();
                    break;
                case LOGIF_NODE:
                case CONT_STAT:
                case IF_NODE:
                case WHILE_NODE:
                case DO_WHILE_NODE:
                case GOTO_NODE:
                case STOP_STAT:
                case RETURN_STAT:
                case RETURN_NODE:
                case ELSEIF_NODE:
                case ARITHIF_NODE:
                case WHERE_NODE:
                case WHERE_BLOCK_STMT:
                case SWITCH_NODE:
                case CASE_NODE:
                case BREAK_NODE:
                case EXIT_STMT:
                case ASSGOTO_NODE:
                case COMGOTO_NODE:
                case WRITE_STAT:
                case PRINT_STAT:
                default:
                    for (int i = 0; i < 3; ++i)
                        addSymbolsToDefUse(USE_T, st->expr(i), tmpList, make_pair((SgSymbol*)NULL, string("")), -1, file, st, parameterNames);
                    addToLists(currentLists, tmpList);
                    break;
                }
            }
        }

        for (auto &list : currentLists)
        {
            auto it = defUseByFunctions.find(list.first);
            if (it == defUseByFunctions.end())
                it = defUseByFunctions.insert(it, make_pair(list.first, vector<DefUseList>()));
        }

        for (auto &list : currentLists)
        {
            auto it = defUseByFunctions.find(list.first);
            for (auto &elem : list.second)
                it->second.push_back(elem);
        }
    }
}

#undef DEF_T
#undef USE_T
#undef DEF_USE_T

extern map<string, vector<DefUseList>> defUseByFunctions;
set<string> getAllDefVars(const string &funcName)
{
    set<string> retVal;
    for (auto &elem : defUseByFunctions[funcName])
        if (elem.isDef())
            retVal.insert(elem.getVar());
    return retVal;
}

set<string> getAllUseVars(const string &funcName)
{
    set<string> retVal;

    for (auto &elem : defUseByFunctions[funcName])
        if (elem.isUse())
            retVal.insert(elem.getVar());

    return retVal;
}

const vector<DefUseList>& getAllDefUseVarsList(const string &funcName) 
{
    return defUseByFunctions[funcName]; 
}

const vector<DefUseList> getAllDefUseVarsList(const string &funcName, const string varName) 
{
    vector<DefUseList> retVal;
    for (auto &elem : defUseByFunctions[funcName])
        if (elem.getVar() == varName)
            retVal.push_back(elem);    

    return retVal;
}

int printDefUseSets(const char *fileName, const map<string, vector<DefUseList>> &defUseLists)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        __spf_print(1, "can not open file %s\n", fileName);
        return -1;
    }
        
    for (auto &elem : defUseLists)
    {
        fprintf(file, "*** Function %s\n", elem.first.c_str());
        for (auto &inList : elem.second)
            inList.print(file, true);
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

static bool isDefVar(const int paramPosition, const string &funcName, map<string, vector<DefUseList>> &defUseByFunctions)
{
    auto founded = defUseByFunctions.find(funcName);
    if(founded == defUseByFunctions.end())
        return true; //No information. Argument can be changed.

    vector<DefUseList>& curDefUse = founded->second;
    bool isDef = false;

    for (int i = 0; i < curDefUse.size(); ++i)
    {
        if (paramPosition == curDefUse[i].getParameterPositionInFunction())
        {
            if (curDefUse[i].isDef())
            {
                isDef = true;
                break;
            }
            else
            {
                const string calledFuncName = curDefUse[i].getParamOfFunction();
                if (!calledFuncName.empty())
                {
                    isDef = isDefVar(curDefUse[i].getParameterPosition(), calledFuncName, defUseByFunctions);
                    if (isDef)
                        break;
                }
            }
        }
    }
    return isDef;
}

static SgExpression* makeList(const vector<SgExpression*> &list)
{
    if (list.size() == 0)
        return NULL;
    SgExpression *out = new SgExpression(EXPR_LIST);
    SgExpression *ret = out;
    for (int i = 0; i < list.size(); ++i)
    {
        out->setLhs(list[i]);
        if (i != list.size() - 1)
        {
            out->setRhs(new SgExpression(EXPR_LIST));
            out->rhs();
        }
        else
            out->setRhs(NULL);
    }

    return ret;
}

static map<SgStatement*, pair<SgExpression*, SgExpression*>> buildLists(const vector<DefUseList> &list)
{
    map<SgStatement*, pair<vector<SgExpression*>, vector<SgExpression*>>> out;
    for (auto &elem : list)
    {
        if (elem.isDef())
            out[elem.getPlace()].first.push_back(elem.getExpr());
        if (elem.isUse())
            out[elem.getPlace()].second.push_back(elem.getExpr());
    }

    map<SgStatement*, pair<SgExpression*, SgExpression*>> ret;
    for (auto &elem : out)
    {
        ret[elem.first].first = makeList(elem.second.first);
        ret[elem.first].second = makeList(elem.second.second);
    }

    return ret;
}

void constructDefUseStep2(SgFile *file, map<string, vector<DefUseList>> &defUseByFunctions)
{

    for (int f = 0; f < file->numberOfFunctions(); ++f)
    {
        SgProgHedrStmt *header = isSgProgHedrStmt(file->functions(f));
        if (header == NULL || header->variant() == PROG_HEDR)
            continue;

        for (int i = 0; i < header->numberOfParameters(); ++i)
        {
            int currAttr = header->parameter(i)->attributes();
            if ((currAttr & OUT_BIT) == 0 && (currAttr & INOUT_BIT) == 0 && (currAttr & IN_BIT) == 0)
            {
                if (isDefVar(i, header->symbol()->identifier(), defUseByFunctions))
                    header->parameter(i)->setAttribute(OUT_BIT);
                else
                    header->parameter(i)->setAttribute(IN_BIT);
            }
            //TODO: test and replace from defUseVar() in defUse.cpp
            /*auto funcList = defUseByFunctions[header->symbol()->identifier()];
            auto toAdd = buildLists(funcList);
            for (auto &elem : toAdd)
            {                
                elem.first->addAttribute(DEFINEDLIST_ATTRIBUTE, (void*)elem.second.first, 0);
                elem.first->addAttribute(USEDLIST_ATTRIBUTE, (void*)elem.second.second, 0);
            }*/
        }
    }
}

int printCommonBlocks(const char *fileName, const map<string, CommonBlock> &commonBlocks)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        __spf_print(1, "can not open file %s\n", fileName);
        return -1;
    }

    for (auto &commonBlock : commonBlocks)
    {
        fprintf(file, "*** COMMON BLOCK '%s'\n", commonBlock.first.c_str());
        commonBlock.second.print(file);
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

// CommonBlock::
Variable* CommonBlock::hasVariable(const string &name, const varType type, const int position)
{
    for (auto &variable : variables)
        if (variable.getName() == name && variable.getType() == type && variable.getPosition() == position)
            return &variable;

    return NULL;
}

Variable* CommonBlock::hasVariable(SgSymbol *symbol, const varType type, const int position)
{
    return hasVariable(string(symbol->identifier()), type, position);
}

const vector<const Variable*> CommonBlock::getVariables(SgFile *file, SgStatement *function) const 
{
    return getVariables(string(file->filename()), string(function->symbol()->identifier()));
}

const vector<const Variable*> CommonBlock::getVariables(const string &file, const string &function) const
{
    vector<const Variable*> retVariables;
    
    for (auto &variable : variables)
        if (variable.hasUse(file, function))
            retVariables.push_back(&variable);
    
    return retVariables;
}

const vector<const Variable*> CommonBlock::getVariables(int position) const
{
    vector <const Variable*> retVariables;

    auto it = groupedVars.find(position);
    if (it != groupedVars.end())
        for (auto &variable : it->second)
            retVariables.push_back(&variable);

    return retVariables;
}

static void findDeclType(SgExpression *ex, varType &type, const string &toFind)
{
    if (ex && type == ANOTHER)
    {
        if (ex->symbol() && ex->symbol()->identifier() == toFind)
        {
            switch (ex->variant())
            {
            case VAR_REF:
                type = SCALAR;
                break;
            case ARRAY_REF:
                type = ARRAY;
                break;
            case INT_VAL:
            case FLOAT_VAL:
            case DOUBLE_VAL:
            case BOOL_VAL:
            case CHAR_VAL:
            case STRING_VAL:
            case CONST_REF:
                type = CONST;
                break;
            default:
                type = ANOTHER;
                break;
            }
        }

        findDeclType(ex->lhs(), type, toFind);
        findDeclType(ex->rhs(), type, toFind);
    }
}

void CommonBlock::addVariables(SgFile *file, SgStatement *function, const vector<pair<SgSymbol*, int>> &newVariables)
{
    for (auto &varPair : newVariables)
    {        
        SgStatement *declStatement = declaratedInStmt(varPair.first);
        varType type = ANOTHER;

        for (int i = 0; i < 3; ++i)
        {
            findDeclType(declStatement->expr(i), type, varPair.first->identifier());
            if (type != ANOTHER)
                break;
        }

        Variable *exist = hasVariable(varPair.first, type, varPair.second);
        if (exist)
            exist->addUse(file, function, varPair.first);
        else
        {
            variables.push_back(Variable(file, function, varPair.first, string(varPair.first->identifier()), type, varPair.second));

            auto it = groupedVars.find(varPair.second);
            if (it == groupedVars.end())
                it = groupedVars.insert(it, make_pair(varPair.second, vector<Variable>()));

            it->second.push_back(Variable(file, function, varPair.first, string(varPair.first->identifier()), type, varPair.second));
        }
    }
}

void CommonBlock::print(FILE *fileOut) const
{
    fprintf(fileOut, "  [POSITION], [VARIABLE NAME], [TYPE]: \n");
    for (auto &var: variables)
    {        
        var.print(fileOut);
        fprintf(fileOut, "      USE in [FILE, FUNC / BLOCK_DATA]:");

        for (auto &use : var.getAllUse())
            fprintf(fileOut, " [%s, %s]", use.getFileName().c_str(), 
                                          use.isBlockDataUse() ? ("BD_" + use.getFunctionName()).c_str() : ("F_" + use.getFunctionName()).c_str());
        fprintf(fileOut, "\n");
    }
}

// END of CommonBlock::

void groupDeclarations(SgFile *file)
{
    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        SgStatement *func = file->functions(i);
        SgStatement *lastNode = func->lastNodeOfStmt();

        map<SgType*, pair<vector<SgStatement*>, vector<SgExpression*>>> refs;
        
        vector<SgStatement*> toDel;
        for (auto st = func; st != lastNode; st = st->lexNext())
        {
            if (isSgExecutableStatement(st))
                break;
            
            if (st->variant() == VAR_DECL)
            {
                auto varDecl = isSgVarDeclStmt(st);
                SgExpression *varList = varDecl->varList();
                
                int count = 0;
                for (auto lst = varList; lst; lst = lst->rhs())
                    count++;

                vector<SgExpression*> notMoved;

                int countOfMoved = 0;
                for (auto lst = varList; lst; lst = lst->rhs())
                {
                    SgExpression *var = lst->lhs();
                    if (var->variant() == VAR_REF)
                    {
                        auto type = var->symbol()->type();
                        if (st->lineNumber() == 72)
                            printf("type %d, line %d\n", type->variant(), st->lineNumber());
                        if (type && isSgArrayType(type) == NULL && type->variant() != T_STRING)
                        {
                            countOfMoved++;                            
                            refs[type].second.push_back(var);

                            SgStatement *prev = st->lexPrev();
                            while (prev && prev->variant() == SPF_ANALYSIS_DIR)
                            {
                                refs[type].first.push_back(prev->extractStmt());
                                prev = st->lexPrev();
                            }
                        }
                        else
                            notMoved.push_back(var);
                    }
                    else
                        notMoved.push_back(var);
                }
                                
                if (countOfMoved != count)
                {
                    if (countOfMoved != 0)
                    {
                        SgExpression *varList = new SgExpression(EXPR_LIST);
                        SgExpression *pVar = varList;

                        for (int z = 0; z < notMoved.size(); z++)
                        {                            
                            pVar->setLhs(notMoved[z]);
                            if (z != notMoved.size() - 1)
                            {
                                pVar->setRhs(new SgExpression(EXPR_LIST));
                                pVar = pVar->rhs();
                            }
                        }                        
                        st->setExpression(0, *varList);
                    }
                }
                else
                    toDel.push_back(st);
            }
        }

        for (auto st = func; st != lastNode; st = st->lexNext())
        {
            if (isSgExecutableStatement(st->lexNext()))
            {
                for (auto &newDecl : refs)
                {
                    SgVarDeclStmt *newDeclSt = newDecl.second.second[0]->symbol()->makeVarDeclStmt();
                    for (int z = 1; z < newDecl.second.second.size(); ++z)
                        newDeclSt->addVar(*newDecl.second.second[z]);
                    st->insertStmtAfter(*newDeclSt, *func);

                    for (auto &spf : newDecl.second.first)
                        st->insertStmtAfter(*spf, *func);                    
                }                
                break;
            }
        }
          
        //TODO: move comments
        for (auto &elem : toDel)
            elem->deleteStmt();
    }
}

bool ifSymbolExists(SgFile *file, const string &symbName)
{
    if (SgFile::switchToFile(file->filename()) != -1)
    {
        SgSymbol *symb = file->firstSymbol();

        while (symb)
        {
            if (symb->identifier() == symbName)
                return true;

            symb = symb->next();
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return false;
}

const CommonBlock* isArrayInCommon(const map<string, CommonBlock> &commonBlocks, const DIST::Array *array)
{
    for (auto &commonBlockPair : commonBlocks)
        for (auto &variable : commonBlockPair.second.getVariables())
            if (variable.getName() == array->GetShortName() && variable.getType() == ARRAY && array->GetLocation().first == DIST::l_COMMON)
                return &commonBlockPair.second;

    return NULL;
}

static void fillArraysFromDirsRec(SgExpression *ex, vector<DIST::Array*> &toAdd)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            auto attributes = getAttributes<SgExpression*, DIST::Array*>(ex, { ARRAY_REF });
            toAdd.insert(toAdd.end(), attributes.begin(), attributes.end());
        }

        if (ex->lhs())
            fillArraysFromDirsRec(ex->lhs(), toAdd);
        if (ex->rhs())
            fillArraysFromDirsRec(ex->rhs(), toAdd);
    }
}

vector<DIST::Array*> fillArraysFromDir(Statement *st)
{
    vector<DIST::Array*> retVal;
    for (int z = 0; z < 3; ++z)
        fillArraysFromDirsRec(st->GetOriginal()->lexPrev()->expr(z), retVal);
    return retVal;
}

template<typename objT>
objT& getObjectForFileFromMap(const char *fileName, map<string, objT> &mapObject)
{
    auto it = mapObject.find(fileName);
    if (it == mapObject.end())
        it = mapObject.insert(it, std::make_pair(fileName, objT()));
    return it->second;
}
template vector<SpfInterval*>& getObjectForFileFromMap(const char *fileName, map<string, vector<SpfInterval*>>&);
template PredictorStats& getObjectForFileFromMap(const char *fileName, map<string, PredictorStats>&);
