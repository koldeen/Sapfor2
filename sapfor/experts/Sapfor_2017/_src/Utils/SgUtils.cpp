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
#include <fcntl.h>
#include <mutex>
#include <thread>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h> 
#endif

#include "SgUtils.h"
#include "errors.h"
#include "../Sapfor.h"

#include "../LoopAnalyzer/directive_parser.h"
#include "../Distribution/Distribution.h"

#include "../GraphCall/graph_calls.h"
#include "../GraphCall/graph_calls_func.h"
#include "../CreateInterTree/CreateInterTree.h"
#include "../Predictor/PredictScheme.h"
#include "../VisualizerCalls/get_information.h"
#include "../VisualizerCalls/SendMessage.h"

using std::map;
using std::pair;
using std::tuple;
using std::set;
using std::vector;
using std::string;
using std::make_pair;
using std::make_tuple;
using std::wstring;

#ifdef _MSC_VER
#include <io.h>
#define popen _popen 
#define pclose _pclose
#define stat _stat 
#define dup _dup
#define dup2 _dup2
#define fileno _fileno
#define close _close
#define pipe _pipe
#define read _read
#define eof _eof
#else
#include <unistd.h>
#endif

#ifndef STD_OUT_FD 
#define STD_OUT_FD (fileno(stdout)) 
#endif 

#ifndef STD_ERR_FD 
#define STD_ERR_FD (fileno(stderr)) 
#endif

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
string removeIncludeStatsAndUnparse(SgFile *file, const char *fileName, const char *fout, 
                                    set<string> &allIncludeFiles, bool outFree, 
                                    const map<string, set<string>>& moduleUsesByFile, const map<string, string>& moduleDelcs, 
                                    bool toString, bool dontReplaceIncludes)
{ 
    fflush(NULL);

    set<string> moduleIncudeUses;
    auto itM = moduleUsesByFile.find(fileName);
    if (itM != moduleUsesByFile.end())
    {
        for (auto& elem : itM->second)
        {
            auto it2 = moduleDelcs.find(elem);
            if (it2 == moduleDelcs.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            string lowerInclude = it2->second;
            convertToLower(lowerInclude);

            moduleIncudeUses.insert(lowerInclude);
        }
    }

    int funcNum = file->numberOfFunctions();
    FILE *currFile = fopen(fileName, "r");
    if (currFile == NULL)
    {
        char buf[256];
        sprintf(buf, "ERROR: Can't open file %s for read with err %d\n", fileName, errno);
        addToGlobalBufferAndPrint(buf);
        char buff[1024];
        if (getcwd(buff, 1024) == NULL)
             ;//
        else
             __spf_print(1, "curr path %s\n", buff);
        throw(-1);
    }

    // name -> unparse comment and position
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

    const string fileN = fileName;
    //insert comment
    int lineBefore = -1;

    map<string, set<SgStatement*>> insertedIncludeFiles;
    map<int, vector<pair<int, int>>> placesForInsert;

    set<string> foundForIncludes;
    map<int, int> stIdByLine;

    for (SgStatement* st = file->firstStatement(); st; st = st->lexNext())
    {
        if (st->variant() > 0 && st->lineNumber() > 0 && st->fileName() == string(file->filename()))
        {
            stIdByLine[st->lineNumber()] = st->id();
            vector<SgStatement*> attr = getAttributes<SgStatement*, SgStatement*>(st, set<int>{SPF_ANALYSIS_DIR, SPF_NOINLINE_OP});
            for (auto& elem : attr)
                if (stIdByLine.find(elem->lineNumber()) == stIdByLine.end())
                    stIdByLine[elem->lineNumber()] = st->id();
        }
    }

    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        removeOmpDir(st);
        if (st->lineNumber() <= 0 || st->variant() < 0)
            continue;
        string currFileName = st->fileName();
        if (currFileName != fileN)
        {
            allIncludeFiles.insert(currFileName);
            auto it = includeFiles.find(currFileName);

            if (it != includeFiles.end())
            {
                foundForIncludes.insert(currFileName);
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
                            {
                                nearIncludes.insert(locName);
                                foundForIncludes.insert(locName);
                            }
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
                             prev->variant() == DVM_INTERVAL_DIR || 
                             prev->variant() == ACC_REGION_DIR || 
                             prev->variant() == DVM_REALIGN_DIR ||
                             prev->variant() == DVM_REDISTRIBUTE_DIR))
                        {
                            locSt = prev;
                            change = true;
                        }
                    }
                    placesForInsert[locSt->id()].push_back(lines);
                }
            }           
        }
        else
            lineBefore = st->lineNumber();
    }

    //if not found, it indicates that file contains of other include files
    for (auto& incl : includeFiles)
    {
        if (foundForIncludes.find(incl.first) == foundForIncludes.end())
        {
            for (auto& interval : incl.second.second)
            {
                bool added = false;
                for (int z = interval.second; z > interval.first; z--)
                {
                    auto it = stIdByLine.find(z);
                    if (it != stIdByLine.end())
                    {
                        placesForInsert[it->second].push_back(interval);
                        added = true;
                        break;
                    }
                }

                if (added == false)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            
        }
    }

    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
    {
        if (st->variant() < 0)
            continue;

        for (auto &it : includeFiles)
        {
            auto foundV = placesForInsert.find(st->id());
            if (foundV != placesForInsert.end())
            {                
                SgStatement* parent = getFuncStat(st, { BLOCK_DATA, MODULE_STMT });
                if(!parent)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                for (auto& interval : foundV->second)
                {
                    if (ifIntervalExists(it.second.second, interval) && insertedIncludeFiles[it.first].find(parent) == insertedIncludeFiles[it.first].end())
                    {
                        allIncludeFiles.insert(it.first);
                        insertedIncludeFiles[it.first].insert(parent);

                        string lowerInclude = it.first;
                        convertToLower(lowerInclude);

                        if (moduleIncudeUses.find(lowerInclude) == moduleIncudeUses.end())
                        {
                            if (dontReplaceIncludes == false)
                            {
                                if (st->comments())
                                {
                                    string comments = st->comments();
                                    if (comments.find(it.second.first) == string::npos)
                                    {
                                        string commLow = comments;
                                        convertToLower(commLow);
                                        const size_t pos = commLow.rfind("include");
                                        if (pos == string::npos)
                                            st->setComments((it.second.first + comments).c_str());
                                        else
                                            st->setComments((comments.insert(comments.find('\n', pos) + 1, it.second.first)).c_str());
                                    }
                                }
                                else
                                    st->addComment(it.second.first.c_str());
                                __spf_print(1, "   -> restore include '%s' before statement on line %d\n", it.first.c_str(), st->lineNumber());
                            }
                        }
                    }
                }
            }
        }
    }

    for (auto &inserted : insertedIncludeFiles)
    {
        auto it = includeFiles.find(inserted.first);
        if (it == includeFiles.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        //TODO: dont work after subroutine copying 
        /*if (inserted.second.size() != it->second.second.size())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);*/
    }

    set<string> moduleDeclsInFiles;
    for (auto& elem : moduleDelcs)
        moduleDeclsInFiles.insert(elem.second);

    //remove
    //XXX: use Sage hack!!
    for (SgStatement* st = file->firstStatement(); st; st = st->lexNext())
    {
        if (dontReplaceIncludes == false)
        {
            if (st->fileName() != fileN || st->getUnparseIgnore())
                st->setVariant(-1 * st->variant());
        }
        else
        {
            if (st->getUnparseIgnore())
                st->setVariant(-1 * st->variant());
            else if (st->fileName() != fileN)
            {
                if (st->variant() == MODULE_STMT && moduleDeclsInFiles.find(st->fileName()) != moduleDeclsInFiles.end())
                {
                    for (auto mSt = st; mSt != st->lastNodeOfStmt(); mSt = mSt->lexNext())
                        mSt->setVariant(-1 * mSt->variant());

                    st = st->lastNodeOfStmt();
                    st->setVariant(-1 * st->variant());
                }
            }
        }
    }

    string strUnparse = "";
    if (toString)
        strUnparse = string(file->firstStatement()->unparse());    
    else
    {
#ifdef _WIN32
        FILE* fOut;
        errno_t err = fopen_s(&fOut, fout, "w");
#else
        int err = 0;
        FILE* fOut = fopen(fout, "w");
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
    }
    //restore
    //XXX: use Sage hack!!
    for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
        if (st->fileName() != fileN && st->variant() < 0 || st->getUnparseIgnore())
            st->setVariant(-1 * st->variant());
    return strUnparse;
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
            bool scopeC = false;
            bool typeC = false;
            if (scope)
                scopeC = (symb->scope() == scope);
            else
                scopeC = true;

            if (type)
                typeC = (symb->type() && symb->type()->equivalentToType(type));
            else
                typeC = true;
            if (scopeC && typeC)
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
        if ((symbs->scope() == scope && scope) || (!symbs->scope() && !scope))
        {
            if (symbs->type() && type)
            {
                if (symbs->type()->equivalentToType(type))
                {
                    newS = symbs;
                    break;
                }
            }
            else if (!symbs->type() && !type)
            {
                newS = symbs;
                break;
            }
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
    if (exp == NULL || exp->variant() == STMT_STR)
        return "";

    string ret = "";
    if (exp->variant() == CONST_REF)
    {
        if (exp->symbol()->identifier())
        {
            ret = "(" + string(exp->symbol()->identifier());
            auto sc = isSgConstantSymb(exp->symbol());
            if (sc && sc->constantValue())
                ret += string("=") + sc->constantValue()->unparse();
            ret += ")";
        }
    }
    else if (exp->symbol())
    {
        if (exp->symbol()->identifier())
            ret = "(" + string(exp->symbol()->identifier()) + ")";
    }
    else if (exp->variant() == INT_VAL)
        ret = "(" + std::to_string(exp->valueInteger()) + ")";
    else if (exp->variant() == DOUBLE_VAL)
        ret = string("(") + (((SgValueExp*)exp)->doubleValue()) + ")";
    else if (exp->variant() == FLOAT_VAL)
        ret = string("(") + (((SgValueExp*)exp)->floatValue()) + ")";
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
    printf("}\n");
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
    findModulesInFile(file, modulesAndFunctions);

    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
        modulesAndFunctions.push_back(file->functions(i));
}

void tryToFindPrivateInAttributes(SgStatement *st, set<string> &privates)
{
    set<Symbol*> privatesVars;
    for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ SPF_ANALYSIS_DIR, SPF_PARALLEL_DIR }))
    {
        if (data)
        {
            Statement *sData = new Statement(data);
            fillPrivatesFromComment(sData, privatesVars);

            // try to find reductions and set its symbols as private in 
            // current loop analysis for correct scalar detection in 
            // tryToFindDependencies() function
            map<string, set<Symbol*>> reductions;
            map<string, set<tuple<Symbol*, Symbol*, int>>> reductionsLoc;

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

    for (auto& elem : privatesVars)
        privates.insert(elem->GetOriginal()->identifier());
}

void fillNonDistrArraysAsPrivate(SgStatement *st,
                                 const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaredArrays,
                                 const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                                 set<string> &privatesVars)
{
    // fill as private all non distributed arrays
    auto it = declaratedArraysSt.find(st);
    if (it != declaratedArraysSt.end())
    {
        for (auto itSet = it->second.begin(); itSet != it->second.end(); ++itSet)
        {
            auto itD = declaredArrays.find(*itSet);
            if (itD != declaredArrays.end())
                if (itD->second.first->GetNonDistributeFlag())
                    privatesVars.insert(itD->second.first->GetShortName());
        }
    }
}

extern  map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> declaredArrays;
extern  map<SgStatement*, set<tuple<int, string, string>>> declaratedArraysSt;

DIST::Array* getArrayFromDeclarated(SgStatement *st, const string &arrayName)
{
    DIST::Array *found = NULL;

    auto it = declaratedArraysSt.find(st);
    if (it != declaratedArraysSt.end())
    {
        for (auto itSet = it->second.begin(); itSet != it->second.end() && !found; ++itSet)
        {
            auto itD = declaredArrays.find(*itSet);
            if (itD != declaredArrays.end())
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
        if (declLst->variant() == ARRAY_REF || declLst->variant() == VAR_REF)
        {
            if (declLst->symbol()->identifier() == toFind)
                return true;
        }

        if (declLst->lhs())
            ret = ret || findSymbol(declLst->lhs(), toFind);
        if (ret)
            return true;

        if (declLst->rhs())
            ret = ret || findSymbol(declLst->rhs(), toFind);
        if (ret)
            return true;
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
            if (start->variant() == INTERFACE_STMT)
                start = start->lastNodeOfStmt();

            //printf("%d\n", start->variant());
            if (start->variant() == VAR_DECL ||
                start->variant() == VAR_DECL_90 ||
                start->variant() == ALLOCATABLE_STMT ||
                start->variant() == DIM_STAT || 
                start->variant() == COMM_STAT || 
                start->variant() == HPF_TEMPLATE_STAT || 
                start->variant() == DVM_VAR_DECL ||
                start->variant() == STRUCT_DECL)
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

            wstring bufE, bufR;
            __spf_printToLongBuf(bufE, L"Can not find declaration for symbol '%s' in current scope", to_wstring(toFind->identifier()).c_str());
#ifdef _WIN32
            __spf_printToLongBuf(bufR, R49, to_wstring(toFind->identifier()).c_str());
#endif
            itM->second.push_back(Messages(ERROR, toFind->scope()->lineNumber(), bufR, bufE, 1017));
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
    if ((var >= DVM_INTERVAL_DIR && var <= DVM_ENDINTERVAL_DIR) ||
        (var >= DVM_DEBUG_DIR && var <= DVM_TRACEOFF_DIR) ||
        (var >= DVM_PARALLEL_ON_DIR && var <= DVM_SHADOW_DIR) ||
        (var >= DVM_NEW_VALUE_DIR && var <= DVM_POINTER_DIR) ||
        (var >= DVM_TASK_REGION_DIR && var < FORALL_STAT) ||
        (var > FORALL_STAT && var <= DVM_TEMPLATE_DELETE_DIR) ||
        (var >= ACC_REGION_DIR && var <= ACC_ASYNC_OP) ||
        (var == DVM_DISTRIBUTE_DIR || var == DVM_REDISTRIBUTE_DIR) ||
        (var == HPF_TEMPLATE_STAT) ||
        (var >= BLOCK_OP && var <= STAGE_OP) || 
        (var >= INDIRECT_OP && var <= SHADOW_NAMES_OP))
            ret = true;
    return ret;
}

bool isSPF_stat(SgStatement *st)
{
    bool ret = false;

    const int var = st->variant();
    //for details see dvm_tag.h
    if (var >= SPF_ANALYSIS_DIR && var <= SPF_PARAMETER_OP)
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

        auto declCpCp = declCP->controlParent();
        if (declCpCp && declCpCp->variant() == INTERFACE_STMT && needtoCheck)
            needtoCheck = false;
    }
    else if (declCP->variant() == INTERFACE_STMT)
        needtoCheck = false;

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
    {
        auto place = declaratedInStmt(symb);
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    
    return localIt->second;
}

SgStatement* findMainUnit(SgProject *proj, map<string, vector<Messages>> &SPF_messages)
{
    SgStatement *mainUnit = NULL;

    vector<SgStatement*> mainUnits;
    for (int i = proj->numberOfFiles() - 1; i >= 0; --i)
    {
        SgFile *file = &(proj->file(i));
        const char *file_name = file->filename();

        for (int k = 0; k < file->numberOfFunctions(); ++k)
        {
            SgStatement *func = file->functions(k);
            if (func->variant() == PROG_HEDR)
            {
                mainUnit = func;
                mainUnits.push_back(func);
            }
        }
    }

    if (mainUnits.size() != 1)
    {
        for (auto& elem : mainUnits)
        {
            vector<Messages>& currMessages = getObjectForFileFromMap(elem->fileName(), SPF_messages);

            wstring messageE, messageR;
            __spf_printToLongBuf(messageE, L"more than one main unit was found");
#ifdef _WIN32
            __spf_printToLongBuf(messageR, R146);
#endif
            currMessages.push_back(Messages(ERROR, elem->lineNumber(), messageR, messageE, 1050));
        }

        if (mainUnits.size() == 0)
        {
            for (int i = proj->numberOfFiles() - 1; i >= 0; --i)
            {
                SgFile* file = &(proj->file(i));
                const char* file_name = file->filename();

                vector<Messages> &currMessages = getObjectForFileFromMap(file_name, SPF_messages);
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"main unit not found");
#ifdef _WIN32
                __spf_printToLongBuf(messageR, R147);
#endif
                currMessages.push_back(Messages(ERROR, file->firstStatement()->lexNext()->lineNumber(), messageR, messageE, 1050));
            }            
        }
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    
    if (!mainUnit->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

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

template<typename IN_TYPE>
void deleteAttributes(IN_TYPE st, const set<int> dataType)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        int idxDel = -1;
        for (int i = 0; i < st->numberOfAttributes(); ++i)
        {
            SgAttribute* attr = st->getAttribute(i);
            const int type = st->attributeType(i);
            if (dataType.find(type) != dataType.end())
            {
                if (attr->getAttributeData())
                {
                    idxDel = i;
                    break;
                }
            }
        }

        if (idxDel != -1)
        {
            st->deleteAttribute(idxDel);
            changed = true;
        }
    }
}

template const vector<SgSymbol*> getAttributes(SgSymbol *st, const set<int> dataType);
template const vector<SgSymbol*> getAttributes(SgStatement* st, const set<int> dataType);
template const vector<SgSymbol*> getAttributes(SgExpression* st, const set<int> dataType);
template const vector<char*> getAttributes(SgSymbol *st, const set<int> dataType);
template const vector<SgStatement*> getAttributes(SgStatement *st, const set<int> dataType);
template const vector<SgExpression*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<SgStatement*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<DIST::Array*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<int*> getAttributes(SgExpression *st, const set<int> dataType);
template const vector<FuncInfo*> getAttributes(SgStatement *st, const set<int> dataType);

template void deleteAttributes(SgStatement* st, const set<int> dataType);
template void deleteAttributes(SgExpression* st, const set<int> dataType);

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

void constructDefUseStep1(SgFile *file, map<string, vector<DefUseList>> &defUseByFunctions, map<string, vector<FuncInfo*>> &allFuncInfo, vector<Messages> &messages)
{
    map<string, vector<FuncInfo*>> curFileFuncInfo;
    vector<LoopGraph*> tmpL;
    functionAnalyzer(file, curFileFuncInfo, tmpL, messages);

    //functions not found
    if (curFileFuncInfo.size() == 0)
        return;

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
                if (isDVM_stat(st))
                {
                    if (st->variant() != ACC_GET_ACTUAL_DIR && st->variant() != ACC_ACTUAL_DIR)
                        continue;
                }

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

map<SgStatement*, vector<DefUseList>> createDefUseMapByPlace()
{
    map<SgStatement*, vector<DefUseList>> retVal;

    for (auto &byFunc : defUseByFunctions)
        for (auto &elem : byFunc.second)
            retVal[elem.getPlace()].push_back(elem);

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

static bool isDefUseVar(const int paramPosition, const string &funcName, map<string, vector<DefUseList>> &defUseByFunctions, bool defined)
{
    auto founded = defUseByFunctions.find(funcName);
    if(founded == defUseByFunctions.end())
        return true; //No information. Argument can be defined or used.

    vector<DefUseList>& curDefUse = founded->second;
    bool isDefUse = false;

    for (int i = 0; i < curDefUse.size(); ++i)
    {
        if (paramPosition == curDefUse[i].getParameterPositionInFunction())
        {
            if (defined && curDefUse[i].isDef())
            {
                isDefUse = true;
                break;
            }
            else if(!defined && curDefUse[i].isUse())
            {
                isDefUse = true;
                break;
            }
            else
            {
                const string calledFuncName = curDefUse[i].getParamOfFunction();
                if (!calledFuncName.empty())
                {
                    isDefUse = isDefUseVar(curDefUse[i].getParameterPosition(), calledFuncName, defUseByFunctions, defined);
                    if (isDefUse)
                        break;
                }
            }
        }
    }
    return isDefUse;
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
                bool isDef = isDefUseVar(i, header->symbol()->identifier(), defUseByFunctions, true);
                bool isUse = isDefUseVar(i, header->symbol()->identifier(), defUseByFunctions, false);
                if(isDef && isUse)
                    header->parameter(i)->setAttribute(INOUT_BIT);
                else if (isDef)
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

int checkSymbNameAndCorrect(const string& symbName, int complite)
{
    set<string> existedSymbols;
    //if (existedSymbols.size() == 0)
    {
        SgFile* oldFile = current_file;
        for (int i = 0; i < CurrentProject->numberOfFiles(); ++i)
        {
            SgFile* file = &(CurrentProject->file(i));
            SgSymbol* s = file->firstSymbol();
            while (s)
            {
                existedSymbols.insert(s->identifier());
                s = s->next();
            }
        }

        if (SgFile::switchToFile(oldFile->filename()) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    string base = symbName;
    int retNum = complite;
    while (existedSymbols.find(base + std::to_string(retNum)) != existedSymbols.end())
        retNum++;
    //existedSymbols.insert(retName);

    return retNum;
}

string checkSymbNameAndCorrect(const string& symbName, const string complite)
{
    set<string> existedSymbols;
    //if (existedSymbols.size() == 0)
    {
        string oldFileName = current_file->filename();
        for (int i = 0; i < CurrentProject->numberOfFiles(); ++i)
        {
            SgFile* file = &(CurrentProject->file(i));
            SgSymbol* s = file->firstSymbol();
            while (s)
            {
                existedSymbols.insert(s->identifier());
                s = s->next();
            }
        }

        if (SgFile::switchToFile(oldFileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    string retName = symbName;
    while (existedSymbols.find(retName) != existedSymbols.end())
        retName += complite;
    //existedSymbols.insert(retName);

    return retName;
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

SgSymbol* getFromModule(const map<string, set<SgSymbol*>> &byUse, SgSymbol *orig, const set<string> &usedInBlock, bool processAsModule)
{
    if (!processAsModule)
    {
        checkNull(orig->scope(), convertFileName(__FILE__).c_str(), __LINE__);
        if (orig->scope()->variant() != MODULE_STMT)
            return orig;
    }

    if (byUse.size())
    {
        for (auto& elem : byUse)
            for (auto& localS : elem.second)
                if (OriginalSymbol(localS)->thesymb == orig->thesymb)
                    return localS;
    }
    return orig;
}

map<string, set<string>> createMapOfModuleUses(SgFile *file)
{
	map<string, set<string>> retValMap;

	vector<SgStatement*> modules;
	findModulesInFile(file, modules);

	for (int z = 0; z < modules.size(); ++z)
	{
		SgStatement *curr = modules[z];
        string modName = curr->symbol()->identifier();
        for (SgStatement *st = curr->lexNext(); st != curr->lastNodeOfStmt(); st = st->lexNext())
        {
            if (st->variant() == USE_STMT)
                retValMap[modName].insert(st->symbol()->identifier());
            else if (st->variant() == PROC_HEDR || st->variant() == FUNC_HEDR)
                break;
        }
	}

    bool repeat = true;
    while (repeat)
    {
        repeat = false;
        for (auto &elem : retValMap)
        {
            set<string> toAdd(elem.second);
            for (auto &inUse : elem.second)
            {
                auto it = retValMap.find(inUse);
                if (it != retValMap.end())
                {
                    for (auto &inUseToAdd : it->second)
                    {
                        if (toAdd.find(inUseToAdd) == toAdd.end())
                        {
                            toAdd.insert(inUseToAdd);
                            repeat = true;
                        }
                    }
                }
            }
            elem.second = toAdd;
        }
    }

    return retValMap;
}

void printSymbolTable(SgFile *file, string filter)
{
    for (auto s = file->firstSymbol(); s; s = s->next())
    {
        auto t = s->type();
        bool need = true;
        if (filter != "")
            if (filter != s->identifier())
                need = false;
        if (need)
        {
            int line = s->scope() ? s->scope()->lineNumber() : -1;
            printf("[%d] %s type %d (%s), location %d line\n", s->id(), s->identifier(), t ? t->variant() : -1, t ? tag[t->variant()] : "", line);
        }
    }
}

static bool checkAdd(const int var, const set<int> &additional)
{
    if (additional.size())
    {
        if (additional.find(var) == additional.end())
            return true;
        else
            return false;
    }
    else
        return true;
}

SgStatement* getFuncStat(SgStatement *st, const set<int> additional)
{
    if (!st)
        return NULL;

    SgStatement *iterator = st;
    while (iterator && !isSgProgHedrStmt(iterator) && checkAdd(iterator->variant(), additional))
        iterator = iterator->controlParent();

    return iterator;
}

SgStatement* duplicateProcedure(SgStatement *toDup, const string &newName, bool withAttributes, bool withComment, bool withSameLines, bool dontInsert)
{
    if (toDup == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    if (isSgProgHedrStmt(toDup) == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement* global = toDup;
    while (global->variant() != GLOBAL)
    {        
        global = global->controlParent();
        /*if (isSgProgHedrStmt(global))
        {
            auto last = global->lastNodeOfStmt();
            // check for contains
            for (auto st = global; st != last; st = st->lexNext())
            {
                if (st->variant() == CONTAINS_STMT)
                {
                    global = st;
                    break;
                }
            }
            if (global->variant() == CONTAINS_STMT)
                break;
        }*/
    }

    SgSymbol* orig = toDup->symbol();    
    SgSymbol* copied = &orig->copySubprogram(*global);

    //XXX: remove all extra functions
    if (global->lexNext()->symbol()->identifier() != string(copied->identifier()))
    {
        vector<SgStatement*> toDel;
        SgStatement* st = global->lexNext();
        if (!isSgProgHedrStmt(st))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        while (st)
        {
            if (st->symbol() == copied)
                break;
            toDel.push_back(st);
            st = st->lastNodeOfStmt()->lexNext();
        }

        if (st == NULL)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        if (!isSgProgHedrStmt(st))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        if (st->symbol()->identifier() != string(copied->identifier()))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        for (auto& elem : toDel)
            elem->extractStmt();

        if (global->lexNext()->symbol()->identifier() != string(copied->identifier()))
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    //move 
    SgStatement* toMove = global->lexNext()->extractStmt();
    if (dontInsert == false)
        toDup->insertStmtBefore(*toMove, *toDup->controlParent());
    //change name
    if (newName != "")
        copied->changeName(newName.c_str());

    if (!withAttributes && !withComment && !withSameLines)
        return toMove;

    // set line numbers, pointer to attributes and comments
    for (auto origStat = toDup, copyStat = toMove;
        origStat != toDup->lastNodeOfStmt()->lexNext();
        origStat = origStat->lexNext(), copyStat = copyStat->lexNext())
    {
        if (copyStat->variant() != origStat->variant())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        if (withSameLines)
        {
            copyStat->setlineNumber(origStat->lineNumber());
            BIF_FILE_NAME(copyStat->thebif) = BIF_FILE_NAME(origStat->thebif);
        }

        if (withAttributes)
            if (origStat->numberOfAttributes() > 0)
                copyStat->addAttributeTree(origStat->getAttribute(0));

        if (withComment)
        {
            if (origStat->comments())
                copyStat->setComments(origStat->comments());
        }
    }

    return toMove;
}

void fillModuleUse(SgFile *file, map<string, set<string>> &moduleUses, map<string, string> &moduleDecls)
{
    const string currFN = file->filename();
    for (SgStatement* st = file->firstStatement(); st; st = st->lexNext())
    {
        if (st->fileName() == currFN)
        {
            if (st->variant() == USE_STMT)
                moduleUses[currFN].insert(st->symbol()->identifier());

            if (st->variant() == MODULE_STMT)
            {
                string moduleN = st->symbol()->identifier();
                auto it = moduleDecls.find(moduleN);
                if (it != moduleDecls.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                moduleDecls[moduleN] = currFN;
            }
        }
    }
}

void filterModuleUse(map<string, set<string>>& moduleUsesByFile, map<string, string>& moduleDecls)
{
    for (auto& elem : moduleUsesByFile)
    {
        set<string> newSet;
        for (auto& setElem : elem.second)
        {
            auto it = moduleDecls.find(setElem);
            if (it == moduleDecls.end())
                newSet.insert(setElem);
            else if (elem.first != it->second)
                newSet.insert(setElem);
        }
        elem.second = newSet;
    }

    /*map<string, set<string>> modIncludeMod;

    for (auto& mod : moduleDecls)
    {
        string name = mod.first;
        string file = mod.second;

        auto it = moduleUsesByFile.find(file);
        if (it != moduleUsesByFile.end())
            modIncludeMod[name] = it->second;
    }

    bool change = true;
    while (change)
    {
        change = false;
        for (auto& mod : modIncludeMod)
        {
            set<string> newSet = mod.second;
            for (auto& included : mod.second)
            {
                auto it = modIncludeMod.find(included);
                if (it == modIncludeMod.end())
                    continue;

                for (auto& elem : it->second)
                {
                    if (newSet.find(elem) == newSet.end())
                    {
                        newSet.insert(elem);
                        change = true;
                    }
                }
            }
            mod.second = newSet;
        }
    }

    for (auto& elem : moduleUsesByFile)
    {
        set<string> newSet = elem.second;
        for (auto& setElem : elem.second)
        {
            auto it = modIncludeMod.find(setElem);
            if (it != modIncludeMod.end())
                for (auto& toRem : it->second)
                    newSet.erase(toRem);
        }
        elem.second = newSet;
    }*/
}

SgExpression* makeExprList(const vector<SgExpression*>& items)
{
    SgExpression* list = NULL;
    if (items.size() == 0)
        return list;
    list = new SgExpression(EXPR_LIST);
    for (int z = 0; z < items.size(); ++z)
    {
        if (z == 0)
            list->setLhs(items[z]);
        else
        {
            SgExpression* tmp = new SgExpression(EXPR_LIST);
            tmp->setLhs(items[z]);
            tmp->setRhs(list);
            list = tmp;
        }
    }

    return list;
}

//if curr == NULL -> no insertion
SgStatement* makeDeclaration(SgStatement* curr, const vector<SgSymbol*>& sIn, vector<SgExpression*>* inits)
{
    if (sIn.size() == 0)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement* place = curr;
    SgStatement* scope = NULL;

    vector<SgSymbol*> s;
    if (place)
    {
        while (isSgProgHedrStmt(place) == NULL && place->variant() != MODULE_STMT)
            place = place->controlParent();
        scope = place;

        set<string> declared;
        while (isSgExecutableStatement(place) == NULL && place != scope->lastNodeOfStmt())
        {
            if (place->variant() == VAR_DECL || place->variant() == VAR_DECL_90)
            {
                SgExpression* ex = place->expr(0);
                while (ex)
                {
                    if (ex->lhs() && ex->lhs()->symbol())
                        declared.insert(ex->lhs()->symbol()->identifier());
                    ex = ex->rhs();
                }
            }
            place = place->lexNext();
        }

        for (auto& elem : sIn)
        {
            if (declared.find(elem->identifier()) == declared.end())
                s.push_back(elem);
        }
    }
    else
        s = sIn;

    if (s.size() == 0)
        return NULL;

    SgVarDeclStmt* decl = s[0]->makeVarDeclStmt();
    if (inits)
    {
        if ((*inits)[0])
            decl->expr(0)->setLhs(new SgExpression(ASSGN_OP, new SgVarRefExp(s[0]), (*inits)[0]));
    }

    for (int z = 1; z < s.size(); ++z)
    {
        auto tmpDecl = s[z]->makeVarDeclStmt();
        if (inits)
        {
            if ((*inits)[z])
                decl->addVar(*new SgExpression(ASSGN_OP, new SgVarRefExp(s[z]), (*inits)[z]));
            else
                decl->addVar(*tmpDecl->expr(0)->lhs());
        }
        else
            decl->addVar(*tmpDecl->expr(0)->lhs());
    }

    if (place)
        place->insertStmtBefore(*decl, *scope);

    decl->setVariant(VAR_DECL_90);
    return decl;
}

static void findModuleDeclInProject(const string &name, const vector<string> &files, map<string, string> &modDecls)
{
    char** filesList = new char* [files.size()];
    for (int z = 0; z < files.size(); ++z)
        filesList[z] = (char*)files[z].c_str();

    SgProject* tmpProj = new SgProject(name.c_str(), filesList, files.size());
    
    int numF = tmpProj->numberOfFiles();
    set<SgFile*> filesSg;
    for (int z = 0; z < numF; ++z)
    {
        vector<SgStatement*> modules;
        SgFile* currF = &tmpProj->file(z);
        string fileName = currF->filename();
        convertToLower(fileName);

        filesSg.insert(currF);
        
        findModulesInFile(currF, modules);
        for (auto& elem : modules)
        {
            if (string(elem->fileName()) == currF->filename())
            {
                const string name = elem->symbol()->identifier();
                auto it = modDecls.find(name);
                if (it != modDecls.end() && it->second != currF->filename())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                else
                    modDecls.insert(it, make_pair(name, currF->filename()));
            }
        }
    }

    delete[]filesList;
    InitializeTable();
}

class StdCapture
{
public:
    static void Init()
    {
        // make stdout & stderr streams unbuffered
        // so that we don't need to flush the streams
        // before capture and after capture 
        // (fflush can cause a deadlock if the stream is currently being 
        std::lock_guard<std::mutex> lock(m_mutex);
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
    }

    static void BeginCapture()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_capturing)
            return;

        secure_pipe(m_pipe);
        m_oldStdOut = secure_dup(STD_OUT_FD);
        m_oldStdErr = secure_dup(STD_ERR_FD);
        secure_dup2(m_pipe[WRITE], STD_OUT_FD);
        secure_dup2(m_pipe[WRITE], STD_ERR_FD);
        m_capturing = true;
#ifndef _MSC_VER
        secure_close(m_pipe[WRITE]);
#endif
    }
    static bool IsCapturing()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_capturing;
    }
    static void EndCapture()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_capturing)
            return;

        m_captured.clear();
        secure_dup2(m_oldStdOut, STD_OUT_FD);
        secure_dup2(m_oldStdErr, STD_ERR_FD);

        const int bufSize = 1025;
        char buf[bufSize];
        int bytesRead = 0;
        bool fd_blocked(false);
        do
        {
            bytesRead = 0;
            fd_blocked = false;
#ifdef _MSC_VER
            if (!eof(m_pipe[READ]))
                bytesRead = read(m_pipe[READ], buf, bufSize - 1);
#else
            bytesRead = read(m_pipe[READ], buf, bufSize - 1);
#endif
            if (bytesRead > 0)
            {
                buf[bytesRead] = 0;
                m_captured += buf;
            }
            else if (bytesRead < 0)
            {
                fd_blocked = (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR);
                if (fd_blocked)
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        } while (fd_blocked || bytesRead == (bufSize - 1));

        secure_close(m_oldStdOut);
        secure_close(m_oldStdErr);
        secure_close(m_pipe[READ]);
#ifdef _MSC_VER
        secure_close(m_pipe[WRITE]);
#endif
        m_capturing = false;
    }
    static std::string GetCapture()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_captured;
    }
private:
    enum PIPES { READ, WRITE };

    static int secure_dup(int src)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
            ret = dup(src);
            fd_blocked = (errno == EINTR || errno == EBUSY);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);
        return ret;
    }
    static void secure_pipe(int* pipes)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
#ifdef _MSC_VER
            ret = pipe(pipes, 65536, O_BINARY);
#else
            ret = pipe(pipes) == -1;
#endif
            fd_blocked = (errno == EINTR || errno == EBUSY);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);
    }
    static void secure_dup2(int src, int dest)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
            ret = dup2(src, dest);
            fd_blocked = (errno == EINTR || errno == EBUSY);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);
    }

    static void secure_close(int& fd)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
            ret = close(fd);
            fd_blocked = (errno == EINTR);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);

        fd = -1;
    }

    static int m_pipe[2];
    static int m_oldStdOut;
    static int m_oldStdErr;
    static bool m_capturing;
    static std::mutex m_mutex;
    static std::string m_captured;
};

// actually define vars.
int StdCapture::m_pipe[2];
int StdCapture::m_oldStdOut;
int StdCapture::m_oldStdErr;
bool StdCapture::m_capturing;
std::mutex StdCapture::m_mutex;
std::string StdCapture::m_captured;

struct FileInfo
{
    FileInfo()
    {
        fileName = "";
        options = "";
        errPath = "";
        outPath = "";
        outDepPath = "";
        text = "";
        error = -1;
        intcludesAdded = 0;
        style = -1;
        lvl = 0;
    }

    FileInfo(const string& _fileName, const string& _options, const string& _errPath, const string& _outPath, 
             const string& _outDepPath, const string &_text)
    {
        fileName = _fileName;
        options = _options;
        errPath = _errPath;
        outPath = _outPath;
        outDepPath = _outDepPath;
        text = _text;
        error = -1;
        intcludesAdded = 0;
        style = -1;
        lvl = 0;
    }

    int error;
    string fileName;
    string options;
    string errPath;
    string outPath;
    string outDepPath;
    string text;
    int style; // -1 unk, 0 fixed, 1 fixed ext, 2 free
    int intcludesAdded;
    int lvl;
};

static vector<string> splitAndArgvCreate(const string& options)
{
    vector<string> optSplited;
    optSplited.push_back("");
    splitString(options, ' ', optSplited, true);

    vector<string> optSplited1;
    for (auto& elem : optSplited)
        if (elem != "")
            optSplited1.push_back(elem);
    optSplited1.insert(optSplited1.begin(), "");

    for (int z = 0; z < optSplited1.size(); ++z)
    {
        //printf("%s\n", optSplited1[z].c_str());
        if (optSplited1[z][0] == '"' && optSplited1[z][optSplited1[z].size() - 1] == '"')
            optSplited1[z] = optSplited1[z].substr(1, optSplited1[z].size() - 2);
    }
    return optSplited1;
}

static void createIncludeOrder(vector<string> &toIncl,
                               const map<string, string>& moduleDelc, 
                               const map<string, set<string>>& modDirectOrder,
                               set<string> &done, 
                               const string &curr)
{
    if (done.find(curr) == done.end())
    {
        for (auto& elem : modDirectOrder.find(curr)->second)
            createIncludeOrder(toIncl, moduleDelc, modDirectOrder, done, elem);

        if (done.find(curr) == done.end())
        {
            toIncl.push_back(moduleDelc.find(curr)->second);
            done.insert(curr);
        }
    }
}

static string convertStyle(const FileInfo* file, bool needRewrite = true)
{
    string text = file->text;

    vector<string> splited;
    splitString(text, '\n', splited);

    text = "";
    int z = 0;
    for (auto& line : splited)
    {
        if (line[0] == 'c' || line[0] == 'C' || line[0] == 'd' || line[0] == 'D' || line[0] == '*')
            line[0] = '!';

        bool needContinuation = false;
        if (line[0] != '!' && line.size() > 6)
        {
            if (line[5] != ' ' && !(line[5] > '0' && line[5] < '9')) // not label
            {
                line[5] = ' ';
                needContinuation = true;// line[5] = '&';
            }

            int p = 73;
            if (file->style == 1)
                p = 133;
            if (line.size() > p)
            {
                while (line[p] != '\0' && line[p] != '\n' && line[p] != '!')
                {
                    line[p] = ' ';
                    p++;
                    if (p >= line.size())
                        break;
                }
            }
        }

        if (needContinuation)
            text += "&";
        text += (z != 0 ? "\n" : "") + line;
        ++z;
    }

    if (needRewrite)
        writeFileFromStr(file->fileName, text);

    return text;
}

static set<FileInfo*> applyModuleDeclsForFile(FileInfo *forFile, const map<string, FileInfo*> &mapFiles,
                                              const map<string, string>& moduleDelc, 
                                              const map<string, set<string>>& mapModuleDeps,
                                              const map<string, set<string>>& modDirectOrder,
                                              vector<string> &optSplited, 
                                              bool includeForInline = false)
{
    set<FileInfo*> retFilesMod;

    auto itF = mapModuleDeps.find(forFile->fileName);
    if (itF == mapModuleDeps.end() && !includeForInline)
        return retFilesMod;

    vector<string> toIncl;
    set<string> done;
    if (itF != mapModuleDeps.end())
    {
        for (auto& mod : itF->second)
            if (moduleDelc.find(mod) != moduleDelc.end())
                createIncludeOrder(toIncl, moduleDelc, modDirectOrder, done, mod);
    }

    //rewrite files to the next iter of parse    
    set<FileInfo*> allFiles;
    bool needToConvertStyle = false;
    for (auto& incl : toIncl)
    {
        if (mapFiles.find(incl) == mapFiles.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        allFiles.insert(mapFiles.find(incl)->second);
    }
    allFiles.insert(forFile);

    int style = forFile->style;
    for (auto& elem : allFiles)
    {
        if (style != elem->style)
        {
            needToConvertStyle = true;
            break;
        }
    }

    string mainText = forFile->text;
    if (needToConvertStyle)
    {
        for (auto& elem : allFiles)
        {
            if (elem->style != 2)
            {
                retFilesMod.insert(elem);
                if (elem != forFile)
                    auto tmp = convertStyle(elem);
                else
                    mainText = convertStyle(elem, false);
            }
        }

        if (forFile->style != 2)
        {
            for (auto& opt : optSplited)
            {
                if (opt == "-FI" || opt == "-extend_source")
                    opt = "-FR";
            }
        }
    }

    string include = "";
    set<string> included;
    for (auto& incl : toIncl)
    {
        if (included.find(incl) == included.end())
            include += "      include '" + incl + "'\n";
        included.insert(incl);
    }

    vector<string> toInclEnds;
    for (auto& file : mapFiles)
        if (file.second != forFile)
            toInclEnds.push_back(file.second->fileName);

    string includeLast = "";
    if (toInclEnds.size())
        includeLast += "!SPF SHADOW FILES\n";

    for (auto& incl : toInclEnds)
        includeLast += "      include '" + incl + "'\n";

    string data = include + mainText + includeLast;
    writeFileFromStr(forFile->fileName, data);

    forFile->intcludesAdded = toIncl.size() + toInclEnds.size();

    retFilesMod.insert(forFile);
    return retFilesMod;
}

static void restoreOriginalText(const vector<FileInfo>& listOfProject)
{
    for (auto& elem : listOfProject)
        writeFileFromStr(elem.fileName, elem.text);
    fflush(NULL);
}

static inline void restoreOriginalText(const FileInfo& file)
{
    writeFileFromStr(file.fileName, file.text);
}

extern "C" int parse_file(int argc, char* argv[], char* proj_name);
static vector<string> parseList(vector<FileInfo>& listOfProject, 
                                bool needToInclude, bool needToIncludeForInline,
                                const map<string, set<string>> &mapModuleDeps, 
                                const map<string, string> &moduleDelc,
                                const map<string, set<string>> &modDirectOrder)
{
    map<string, FileInfo*> mapFiles;
    for (auto& elem : listOfProject)
        mapFiles[elem.fileName] = &elem;

    vector<string> errors;
    int i = 1;
    int N = listOfProject.size();
    for (auto& elem : listOfProject)
    {
        sendMessage_progress(std::to_wstring((int)(((double)(i++) / N) * 100)));

        string file = elem.fileName;
        string options = elem.options;
        vector<string> optSplited = splitAndArgvCreate(options);

        char** toParse = new char* [optSplited.size() + 1];
        for (int z = 0; z < optSplited.size(); ++z)
        {
            toParse[z] = new char[optSplited[z].size() + 1];
            strcpy(toParse[z], optSplited[z].c_str());
        }
        toParse[optSplited.size()] = new char[file.size() + 1];
        strcpy(toParse[optSplited.size()], file.c_str());

        if (options.find("-FI") != string::npos)
            elem.style = 0;
        else if (options.find("-FR") != string::npos || options.find("-f90") != string::npos)
            elem.style = 2;
        else if (options.find("-extend_source") != string::npos)
            elem.style = 1;

        for (int z = 0; z < optSplited.size(); ++z)
        {
            if (optSplited[z] == "-o")
            {
                if (z + 1 == optSplited.size())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                elem.outDepPath = optSplited[z + 1];
                break;
            }
        }

        FILE* depPath = fopen(elem.outDepPath.c_str(), "r");
        if (depPath)
        {
            fclose(depPath);
            if (elem.error <= 0)
            {
                elem.error = 0;
                errors.push_back("");
                for (int z = 0; z <= optSplited.size(); ++z)
                    delete toParse[z];
                delete[] toParse;
                continue;
            }
        }

#ifdef _WIN32
        sendMessage_2lvl(L" обработка файла '" + to_wstring(file) + L"'");
#else 
        sendMessage_2lvl(L" processing file '" + to_wstring(file) + L"'");
#endif        
        StdCapture::Init();
        string errorMessage = "";
        try
        {
            set<FileInfo*> filesModified;
            StdCapture::BeginCapture();
            if (needToInclude)
                filesModified = applyModuleDeclsForFile(&elem, mapFiles, moduleDelc, mapModuleDeps, modDirectOrder, optSplited, needToIncludeForInline);
            else if (needToIncludeForInline) //TODO for modules
                filesModified = applyModuleDeclsForFile(&elem, mapFiles, moduleDelc, mapModuleDeps, modDirectOrder, optSplited, true);

            int retCode = parse_file(optSplited.size(), toParse, "dvm.proj");
            if (needToInclude || needToIncludeForInline)
            {
                for (auto &elem : filesModified)
                    restoreOriginalText(*elem);
                fflush(NULL);
            }

            elem.error = retCode;
            StdCapture::EndCapture();
            errorMessage = StdCapture::GetCapture();

            if (elem.error != 0)
                elem.lvl++;

            if (errorMessage.find("Warning 308") != string::npos)
                if (elem.error == 0)
                    elem.error = 1;            
        }
        catch (int err)
        {
            StdCapture::EndCapture();
            errorMessage = StdCapture::GetCapture();

            if (needToInclude || needToIncludeForInline)
                restoreOriginalText(listOfProject);
        }
        catch (...)
        {
            StdCapture::EndCapture();
            errorMessage = StdCapture::GetCapture();

            if (needToInclude || needToIncludeForInline)
                restoreOriginalText(listOfProject);
        }
        errors.push_back(errorMessage);
        for (int z = 0; z <= optSplited.size(); ++z)
            delete toParse[z];
        delete[] toParse;

        createNeededException();
    }
    return errors;
}

static string shiftLines(const string &in, const map<string, const FileInfo*> &mapOfFiles, const FileInfo* currF)
{
    int byNum = 0;

    auto it = in.find("on line ");
    if (it != string::npos)
        it += strlen("on line ");

    int d = 0;
    sscanf(in.c_str() + it, "%d", &d);
    
    auto it1 = in.find("of", it + 1);
    if (it1 == string::npos)
        return in;
    it1 += 3;

    string fileN = in.substr(it1, in.find(':', it1) - it1);
    auto itF = mapOfFiles.find(fileN);
    if (itF == mapOfFiles.end())
        return in;
    if (itF->second != currF)
        return in;

    byNum = itF->second->intcludesAdded;
    if (byNum == 0)
        return in;

    d -= byNum;
    if (d <= 0)
    {
        //return in;
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    string newStr = in.substr(0, it) + std::to_string(d) + in.substr(in.find(' ', it + 1));
    return newStr;
}

static int dumpErrors(const vector<FileInfo>& listOfProject, const vector<string>& errors)
{
    int errorsCount = 0;
    map<string, const FileInfo*> mapOfFiles;
    for (auto& elem : listOfProject)
        mapOfFiles[elem.fileName] = &elem;

    int z = 0;
    for (auto& file : listOfProject)
    {
        if (errors[z] == "")
        {
            FILE* ferr = fopen(file.errPath.c_str(), "w");
            if (!ferr)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            fclose(ferr);
            ++z;
            continue;
        }

        FILE* ferr = fopen(file.errPath.c_str(), "w");
        FILE* fout = fopen(file.outPath.c_str(), "w");
        if (!ferr)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        if (!fout)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        string errS = "", outS = "";
        vector<string> splited;
        splitString(errors[z], '\n', splited);
        for (auto& elem : splited)
            if (elem.find("Warning") != string::npos)
                outS += shiftLines(elem, mapOfFiles, &file) + "\n";
            else if (elem.find("Error") != string::npos)
            {
                errS += shiftLines(elem, mapOfFiles, &file) + "\n";
                errorsCount++;
            }

        fprintf(fout, "%s", outS.c_str());
        fprintf(ferr, "%s", errS.c_str());

        fflush(NULL);

        fclose(fout);
        fclose(ferr);
        ++z;
    }

    return errorsCount;
}

static int createMapOfUse(const vector<string>& errors, const vector<FileInfo>& listOfProject, map<string, set<string>> &mapModuleDeps)
{
    int changed = 0;
    for (int z = 0; z < listOfProject.size(); ++z)
    {
        if (listOfProject[z].error >= 0)
        {
            vector<string> splited;
            splitString(errors[z], '\n', splited);
            for (auto& err : splited)
            {
                if (err.find("Warning 308") != string::npos && err.find(listOfProject[z].fileName) != string::npos)
                {
                    auto pos = err.find("Unknown module");
                    if (pos != string::npos)
                    {
                        pos += strlen("Unknown module") + 1;
                        string substr = "";
                        while (err[pos] != ' ' && pos != err.size())
                            substr += err[pos++];
                        mapModuleDeps[listOfProject[z].fileName].insert(substr);
                        changed++;
                    }
                }
            }
        }
    }

    return changed;
}

static map<string, set<string>> createModuleOrder(const map<string, string> &moduleDelc, const map<string, set<string>> &mapModuleDeps)
{
    map<string, set<string>> modDirectOrder;
    for (auto& elem : moduleDelc)
        modDirectOrder[elem.first] = set<string>();

    for (auto& elem : moduleDelc)
    {
        auto itF = mapModuleDeps.find(elem.second);
        if (itF != mapModuleDeps.end())
        {
            for (auto& inFile : itF->second)
            {
                if (moduleDelc.find(inFile) != moduleDelc.end())
                    modDirectOrder[elem.first].insert(inFile);
            }
        }
    }

    return modDirectOrder;
}


int parseFiles(const char* proj, vector<string>& filesCompilationOrder, int parseForInlining)
{
    FILE* list = fopen(proj, "r");
    if (!list)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    vector<string> pathSplit;
    if (string(proj).find('\\') != string::npos)
        splitString(proj, '\\', pathSplit);
    else
        splitString(proj, '/', pathSplit);

    if (pathSplit.size() < 2)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    if (pathSplit[pathSplit.size() - 2] != "visualiser_data")
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    string fullPath = "";
    for (int z = 0; z < pathSplit.size() - 2; ++z)
        fullPath += pathSplit[z] + "/";
    if (fullPath == "")
        fullPath = "./";
    else
    {
        //change dir
        if (chdir(fullPath.c_str()) != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    vector<FileInfo> listOfProject;
    while (!feof(list))
    {
        char buf[1024];
        if (fgets(buf, 1024, list) == NULL)
            continue;

        string toAdd = buf;
        if (toAdd[toAdd.size() - 1] == '\n')
            toAdd = toAdd.erase(toAdd.size() - 1);
        
        string fileNameFixed = "";
        auto idx = toAdd.find(fullPath);
        if (idx != string::npos)
            fileNameFixed = toAdd.substr(idx + fullPath.size());
        else
            fileNameFixed = (toAdd.substr(0, 2) == "./") ? toAdd.substr(2) : toAdd;
        
        const string optPath = fullPath + "visualiser_data/options/" + fileNameFixed + ".opt";
        const string errPath = fullPath + "visualiser_data/options/" + fileNameFixed + ".err";
        const string outPath = fullPath + "visualiser_data/options/" + fileNameFixed + ".out";

        const string fileText = readFileToStr(toAdd);

        FILE* opt = fopen(optPath.c_str(), "r");
        if (!opt)
        {
            __spf_print(1, "can not open path %s\n", optPath.c_str());
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        fgets(buf, 1024, opt);
        string toAddOpt = buf;
        if (toAddOpt[toAddOpt.size() - 1] == '\n')
            toAddOpt = toAddOpt.erase(toAddOpt.size() - 1);

        fclose(opt);
        listOfProject.push_back(FileInfo(fileNameFixed, toAddOpt, errPath, outPath, "", fileText));
    }

    fclose(list);
    vector<string> errors;
    map<string, set<string>> mapModuleDeps;
    map<string, string> moduleDelc;
    map<string, set<string>> modDirectOrder;

    string projName = "tmp";
    int iters = 0;
    int changed = 0;
    int lastChanged = 0;

    int rethrow = 0;
    try
    {
        do
        {
#ifdef _WIN32
            sendMessage_1lvl(L"выполняется " + std::to_wstring((iters + 1)) + L" итерация синтаксического анализа");
#else
            sendMessage_1lvl(L"running " + std::to_wstring((iters + 1)) + L" iteration of syntax analisys");
#endif
            errors = parseList(listOfProject, iters != 0, (parseForInlining != 0), mapModuleDeps, moduleDelc, modDirectOrder);
            changed = createMapOfUse(errors, listOfProject, mapModuleDeps);
            if (iters != 0)
                if (lastChanged <= changed)
                    break;

            createNeededException();

            if (changed)
            {
                vector<string> files;
                for (auto& elem : listOfProject)
                    if (elem.error == 0)
                        files.push_back(elem.outDepPath);
                if (files.size() == 0)
                    break;
                findModuleDeclInProject(projName + std::to_string(iters++), files, moduleDelc);
                modDirectOrder = createModuleOrder(moduleDelc, mapModuleDeps);
            }
            lastChanged = changed;
        } while (changed);

        /*string toPrint = "MODULE DEPS:\n";
        for (auto& elem : mapModuleDeps)
        {
            toPrint += elem.first + '\n';
            for (auto& setEl : elem.second)
                toPrint += " " + setEl + '\n';
        }
        toPrint += "MODULE DIRECT ORDER:\n";
        for (auto& elem : modDirectOrder)
        {
            toPrint += elem.first + '\n';
            for (auto& setEl : elem.second)
                toPrint += " " + setEl + '\n';
        }
        toPrint += "FILES LVL:\n";
        for (auto& elem : listOfProject)
            toPrint += elem.fileName + " " + elem.outDepPath + " lvl = " + std::to_string(elem.lvl) + '\n';
        printf("%s\n", toPrint.c_str());*/

        int added = 0;
        int iter = 0;
        while (added != listOfProject.size())
        {
            for (auto& elem : listOfProject)
            {
                if (elem.lvl == iter)
                {
                    filesCompilationOrder.push_back(elem.fileName);
                    added++;
                }
            }
            ++iter;
        }
    }
    catch (int err)
    {
        rethrow = err;
    }
    catch (...)
    {
        rethrow = -1;
    }

    int errCount = dumpErrors(listOfProject, errors);

    if (rethrow != 0)
        throw rethrow;
    return -errCount;
}

extern int pppa_analyzer(int argv, char** argc);
int pppaAnalyzer(const char* options)
{
    string optionsS(options);
    vector<string> splited = splitAndArgvCreate(optionsS);

    char** argv = new char* [splited.size()];
    for (int z = 0; z < splited.size(); ++z)
        argv[z] = (char*)splited[z].c_str();

    StdCapture::Init();
    string errorMessage = "";
    int retCode = pppa_analyzer(splited.size(), argv);
    StdCapture::EndCapture();
    errorMessage = StdCapture::GetCapture();

    delete[]argv;
    return retCode;
}

int getNextFreeLabel()
{
    PTR_LABEL lab;
    set<int> used;
    for (lab = PROJ_FIRST_LABEL(); lab; lab = LABEL_NEXT(lab))
        used.insert(LABEL_STMTNO(lab));

    for (int z = 1; z < 99999; ++z)
        if (used.find(z) == used.end())
            return z;
    return -1;
}

static void addUseStatements(SgStatement* currF, SgStatement* obj, vector<SgStatement*>& useStats,
                             const vector<SgStatement*>& funcContains)
{
    for (auto& funcSt : funcContains)
    {
        if (currF == funcSt)
        {
            SgStatement* last = obj->lastNodeOfStmt();
            for (SgStatement* st = obj->lexNext(); st != last; st = st->lexNext())
            {
                if (st->variant() == USE_STMT)
                    useStats.push_back(st);
                else if (st->variant() == CONTAINS_STMT)
                    break;
            }
            break;
        }
    }
}

void fillUsedModulesInFunction(SgStatement *st, vector<SgStatement*> &useStats)
{
    checkNull(st, convertFileName(__FILE__).c_str(), __LINE__);

    int var = st->variant();
    while (var != PROG_HEDR && var != PROC_HEDR && var != FUNC_HEDR)
    {
        st = st->controlParent();
        checkNull(st, convertFileName(__FILE__).c_str(), __LINE__);
        var = st->variant();
    }

    for (SgStatement *stat = st->lexNext(); !isSgExecutableStatement(stat); stat = stat->lexNext())
        if (stat->variant() == USE_STMT)
            useStats.push_back(stat);

    for (int i = 0; i < current_file->numberOfFunctions(); ++i)
    {
        vector<SgStatement*> funcContains;
        findContainsFunctions(current_file->functions(i), funcContains);
        addUseStatements(st, current_file->functions(i), useStats, funcContains);        
    }

    vector<SgStatement*> modules;
    findModulesInFile(st->getFile(), modules);
    for (auto &module : modules)
    {
        vector<SgStatement*> funcContains;
        findContainsFunctions(module, funcContains, true);
        addUseStatements(st, module, useStats, funcContains);
    }
}

static void recFillUsedVars(SgExpression *exp, map<string, SgSymbol*> &vars)
{
    if (exp)
    {
        if (exp->symbol() && (exp->variant() == VAR_REF || exp->variant() == ARRAY_REF || exp->variant() == CONST_REF)
            && !(exp->symbol()->attributes() & PRIVATE_BIT))
        {
            const auto key = exp->symbol()->identifier();
            if (vars.find(key) == vars.end())
                vars.insert(make_pair(key, exp->symbol()));
        }
        recFillUsedVars(exp->lhs(), vars);
        recFillUsedVars(exp->rhs(), vars);
    }
}

static inline void fillUsedVars(SgStatement *st, map<string, SgSymbol*> &vars)
{
    if (st)
    {
        for (int i = 0; i < 3; ++i)
        {
            SgExpression *exp = st->expr(i);
            recFillUsedVars(exp, vars);
        }
    }
}

static inline void joinMaps(map<string, SgSymbol*> &map1, const map<string, SgSymbol*> &map2, const map<string, SgSymbol*> &exept = map<string, SgSymbol*>())
{
    for (auto &pair : map2)
        if (exept.find(pair.first) == exept.end() && map1.find(pair.first) == map1.end())
            map1.insert(pair);
}

void fillVisibleInUseVariables(SgStatement *useSt, map<string, SgSymbol*> &vars)
{
    if (useSt)
    {
        if (useSt->variant() == USE_STMT)
        {
            bool only = false;

            map<string, SgSymbol*> localVars;  // local module variables
            map<string, SgSymbol*> useVars;    // variables from other modules
            map<string, SgSymbol*> renamedVas; // renamed variables
            map<string, SgSymbol*> originVars; // origin variables names in USE_STAT

            // check USE_STAT
            // fill from ONLY_NODE and RENAME_NODE
            SgExpression *ex = useSt->expr(0);
            if (ex && ex->variant() == ONLY_NODE)
            {
                only = true;
                ex = ex->lhs();
            }

            for (auto exI = ex; exI; exI = exI->rhs())
            {
                if (exI->lhs()->variant() == RENAME_NODE)
                {
                    SgExpression *ren = exI->lhs();
                    if (ren->lhs()->symbol() && ren->rhs() && ren->rhs()->symbol())
                    {
                        if (renamedVas.find(ren->lhs()->symbol()->identifier()) == renamedVas.end())
                            renamedVas.insert(make_pair(ren->lhs()->symbol()->identifier(), ren->lhs()->symbol()));
                        if (originVars.find(ren->rhs()->symbol()->identifier()) == originVars.end())
                            originVars.insert(make_pair(ren->rhs()->symbol()->identifier(), ren->rhs()->symbol()));
                    }
                    else if (only && ren->lhs()->symbol())
                    {
                        if (renamedVas.find(ren->lhs()->symbol()->identifier()) == renamedVas.end())
                            renamedVas.insert(make_pair(ren->lhs()->symbol()->identifier(), ren->lhs()->symbol()));
                    }
                }
            }

            if (!only)
            {
                // check module
                const string modName(useSt->symbol()->identifier());
                vector<SgStatement*> modules;
                findModulesInFile(useSt->getFile(), modules);

                bool found = false;
                for (auto i = 0; i < modules.size(); ++i)
                {
                    if (modName == modules[i]->symbol()->identifier())
                    {
                        found = true;

                        vector<SgStatement*> useStats;
                        for (SgStatement *st = modules[i]->lexNext(); st != modules[i]->lastNodeOfStmt(); st = st->lexNext())
                        {
                            if (st->variant() == USE_STMT)
                                useStats.push_back(st);
                            else if (st->variant() == CONTAINS_STMT)
                                break;
                            else
                                fillUsedVars(st, localVars);
                        }

                        for (auto &useSt : useStats)
                        {
                            map<string, SgSymbol*> visibleVars;
                            fillVisibleInUseVariables(useSt, visibleVars);
                            joinMaps(useVars, visibleVars);
                        }

                        break;
                    }
                }

                if (!found)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            // fill vars
            // TODO: check renaming
            joinMaps(vars, useVars, originVars);
            joinMaps(vars, localVars, originVars);
            joinMaps(vars, renamedVas);
        }
    }
}

Variable::Variable(SgFile* file, SgStatement* function, SgSymbol* symbol, const std::string& name, const varType type, const int position) :
                   symbol(symbol), name(name), type(type), position(position)
{
    declPace = declaratedInStmt(symbol);
    allUse.push_back(CommonVariableUse(file, function, symbol));
}

string nameWithContains(SgStatement* where, SgSymbol* s)
{
    std::string containsName = "";
    SgStatement* st_cp = where->controlParent();
    if (st_cp->variant() == PROC_HEDR || st_cp->variant() == PROG_HEDR || st_cp->variant() == FUNC_HEDR)
        containsName = st_cp->symbol()->identifier() + std::string(".");

    return containsName + s->identifier();
}