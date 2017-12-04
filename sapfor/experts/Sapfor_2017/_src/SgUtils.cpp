#include "leak_detector.h"

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
#include "transform.h"

#include "directive_parser.h"
#include "Distribution/Distribution.h"

using std::map;
using std::pair;
using std::tuple;
using std::set;
using std::vector;
using std::string;
using std::make_pair;

const char *tag[];

void removeIncludeStatsAndUnparse(SgFile *file, const char *fileName, const char *fout, set<string> &allIncludeFiles)
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
    map<string, string> includeFiles;

    // TODO: extend buff size in dynamic
    char buf[8192];
    while (!feof(currFile))
    {
        char *read = fgets(buf, 8192, currFile);
        if (read)
        {
            string line(read);
            convertToLower(line);

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
                    continue;

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
                string inclName(line.begin() + st, line.begin() + en + 1);

                auto toInsert = includeFiles.find(inclName);
                if (toInsert == includeFiles.end())
                    includeFiles.insert(toInsert, make_pair(inclName, line));
                //printf("insert %s -> %s\n", inclName.c_str(), line.c_str());
            }
        }
    }

    vector<string> needDel;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        set<string> toInsert;
        SgStatement *first = NULL;
        bool start = false;

        while (st != lastNode)
        {
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (strcmp(st->fileName(), fileName))
            {
                string fileToIns(st->fileName());
                convertToLower(fileToIns);

                toInsert.insert(fileToIns);
                allIncludeFiles.insert(fileToIns);
                start = true;
            }
            else if (start && first == NULL)
                first = st;
            st = st->lexNext();
        }

        for (auto it = toInsert.begin(); it != toInsert.end(); ++it)
        {
            auto foundIt = includeFiles.find(*it);
            if (foundIt != includeFiles.end())
            {
                if (first)
                {
                    if (first->comments() == NULL)
                        first->addComment(foundIt->second.c_str());
                    else
                    {
                        const char *comments = first->comments();
                        if (strstr(comments, foundIt->second.c_str()) == NULL)
                            first->addComment(foundIt->second.c_str());
                    }
                }
                else //TODO
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
        }

        // remove code from 'include' only from file, not from Sage structures
        start = file->functions(i);
        st = file->functions(i);
        lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (strcmp(st->fileName(), fileName))
            {
                string toSplit(st->unparse());
                convertToLower(toSplit);
                splitString(toSplit, '\n', needDel);
            }
            st = st->lexNext();
        }
    }

    FILE *fOut = fopen(fout, "w");
    if (fOut == NULL)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    file->unparse(fOut);
    fclose(fOut);

    if (needDel.size() > 0)
    {
        fOut = fopen(fout, "r");

        string currFile = "";
        int idxDel = 0;
        while (!feof(fOut))
        {
            fgets(buf, 8192, fOut);
            const int len = strlen(buf);
            if (len > 0)
                buf[len - 1] = '\0';

            string toCmp(buf);
            convertToLower(toCmp);
            //printf("%s\n", toCmp.c_str());
            if (needDel.size() > idxDel)
            {
                if (needDel[idxDel] == toCmp)
                    idxDel++;
                else
                {
                    currFile += toCmp;
                    currFile += "\n";
                }
            }
            else
            {
                currFile += toCmp;
                currFile += "\n";
            }
        }
        fclose(fOut);

        fOut = fopen(fout, "w");
        fwrite(currFile.c_str(), sizeof(char), currFile.length(), fOut);
        fclose(fOut);
    }
}

static map<string, SgSymbol*> createdSymbols;

SgSymbol* findSymbolOrCreate(SgFile *file, const string toFind)
{
    SgSymbol *symb = file->firstSymbol();

    while (symb)
    {
        if (symb->identifier() == toFind)
            return symb;
        symb = symb->next();
    }

    auto result = createdSymbols.find(toFind);
    if (result == createdSymbols.end())
    {
        SgSymbol *newS = new SgSymbol(VARIABLE_NAME, toFind.c_str());
        createdSymbols.insert(result, make_pair(toFind, newS));
        return newS;
    }
    else
        return result->second;
}

static string getValue(SgExpression *exp)
{
    if (exp == NULL)
        return "( )";

    string ret = "( )";
    if (exp->symbol())
        ret = "(" + string(exp->symbol()->identifier()) + ")";
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
        else
            ;// printf("%d_%d -> (NULL NULL)\n", lvl, exp->variant());

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
    vector<SgStatement*> functions;

    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
        functions.push_back(file->functions(i));

    int inV = functions.size() > 0 ? 0 : -1;

    while (first)
    {
        if (first->variant() == MODULE_STMT)
        {
            modules.push_back(first);
            first = first->lastNodeOfStmt();
        }
        else
        {
            if (inV >= 0)
            {
                if (first == functions[inV])
                {
                    first = functions[inV]->lastNodeOfStmt();
                    inV++;
                }
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

bool isSPF_comment(SgStatement *st)
{
    const int var = st->variant();
    return var == SPF_ANALYSIS_DIR || var == SPF_PARALLEL_DIR || var == SPF_TRANSFORM_DIR || var == SPF_PARALLEL_REG_DIR || var == SPF_END_PARALLEL_REG_DIR;
}

void tryToFindPrivateInAttributes(SgStatement *st, 
                                  const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                  const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                                  set<string> &privatesVars)
{
    for (int z = 0; z < st->numberOfAttributes(); ++z)
    {
        SgAttribute *attr = st->getAttribute(z);
        int type = st->attributeType(z);
        if (type == SPF_ANALYSIS_DIR || type == SPF_PARALLEL_DIR)
        {
            SgStatement *data = (SgStatement *)(attr->getAttributeData());
            if (data)
            {
                fillPrivatesFromComment(data, privatesVars);

                // try to find reductions and set its symbols as private in 
                // current loop analysis for correct scalar detection in 
                // tryToFindDependencies() function
                map<string, set<string>> reductions;
                map<string, set<tuple<string, string, int>>> reductionsLoc;

                fillReductionsFromComment(data, reductions);
                fillReductionsFromComment(data, reductionsLoc);

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

static bool findSymbol(SgExpression *declLst, const string &toFind)
{
    bool ret = false;
    if (declLst)
    {
        if (declLst->symbol())
            if (declLst->symbol()->identifier() == toFind)
                return true;

        if (declLst->lhs())
            ret = ret || findSymbol(declLst->lhs(), toFind);

        if (declLst->rhs())
            ret = ret || findSymbol(declLst->rhs(), toFind);
    }
    return ret;
}

extern map<string, vector<Messages>> SPF_messages;
SgStatement* declaratedInStmt(SgSymbol *toFind)
{
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
                start->variant() == DIM_STAT)
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

    if (inDecl.size() == 0)
    {
        SgStatement *lowLevelDecl = toFind->declaredInStmt();
        if (lowLevelDecl)
            inDecl.push_back(lowLevelDecl);
    }

    if (inDecl.size() == 0)
    {
        __spf_print(1, "can not find declaration for symbol '%s'\n", toFind->identifier());

        auto itM = SPF_messages.find(start->fileName());
        if (itM == SPF_messages.end())
            itM = SPF_messages.insert(itM, std::make_pair(start->fileName(), vector<Messages>()));

        char buf[256];
        sprintf(buf, "Can not find declaration for symbol '%s' in current scope", toFind->identifier());
        itM->second.push_back(Messages(ERROR, start->lineNumber(), buf));

        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }

    //return statement y priority: VAR_DECL, VAR_DECL_90, ALLOCATABLE_STMT, DIM_STAT, other
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
    if (var >= 950 && var <= 956)
        ret = true;
    return ret;
}

static map<SgExpression*, string>::const_iterator getStringExpr(SgExpression *ex, map<SgExpression*, string> &collection)
{
    auto it = collection.find(ex);
    if (it == collection.end())
        it = collection.insert(it, std::make_pair(ex, ex->unparse()));
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

void getCommonBlocksRef(map<string, SgStatement*> &commonBlocks, SgStatement *start, SgStatement *end)
{
    while (start != end)
    {
        if (start->variant() == COMM_STAT)
        {
            const string commonName(start->expr(0)->symbol()->identifier());
            map<string, SgStatement*>::iterator it = commonBlocks.find(commonName);
            //TODO: check eq of common blocks with the same name
            if (it == commonBlocks.end())
                commonBlocks.insert(it, make_pair(commonName, start));
        }
        start = start->lexNext();
    }
}

static bool isInCommon(SgStatement *commonBlock, const char *arrayName, int &commonPos)
{
    SgExpression *exp = commonBlock->expr(0);
    exp = exp->lhs();
    commonPos = 0;
    while (exp)
    {
        if (!strcmp(exp->lhs()->symbol()->identifier(), arrayName))
            return true;
        commonPos++;
        exp = exp->rhs();
    }
    return false;
}

map<pair<string, int>, tuple<int, string, string>> tableOfUniqNames;
tuple<int, string, string> getUniqName(const map<string, SgStatement*> &commonBlocks, SgStatement *decl, SgSymbol *symb)
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
        for (auto i = commonBlocks.begin(); i != commonBlocks.end(); i++)
        {
            inCommon = isInCommon(i->second, symb->identifier(), commonPos);
            if (inCommon)
            {
                foundCommon = i->second->expr(0);
                break;
            }
        }
    }

    tuple<int, string, string> retVal;
    if (inCommon)
        retVal = make_tuple(commonPos, string("common_") + string(foundCommon->symbol()->identifier()), string(symb->identifier()));
    else
        retVal = make_tuple(decl->lineNumber(), string(decl->fileName()), string(symb->identifier()));

    auto it = tableOfUniqNames.find(make_pair(symb->identifier(), decl->lineNumber()));
    if (it == tableOfUniqNames.end())
        tableOfUniqNames.insert(it, make_pair(make_pair(symb->identifier(), decl->lineNumber()), retVal));
    return retVal;
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