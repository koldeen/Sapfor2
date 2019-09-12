#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <locale>
#include <set>
#include <map>
#include <assert.h>

#include "directive_parser.h"
#include "../Utils/SgUtils.h"
#include "../LoopAnalyzer/loop_analyzer.h"
#include "../Utils/AstWrapper.h"

using std::string;
using std::vector;
using std::set;
using std::tuple;
using std::map;
using std::make_pair;
using std::pair;

bool isSPF_NoInline(Statement *stIn)
{
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ SPF_TRANSFORM_DIR }))
        {
            SgExpression *exprList = data->expr(0);
            while (exprList)
            {
                if (exprList->lhs()->variant() == SPF_NOINLINE_OP)
                {
                    //__spf_print(1, "found no inline\n");
                    return true;
                }
                exprList = exprList->rhs();
            }
        }
    }
    return false;
}

static map<SgSymbol*, Symbol*> dictCreated;

static inline string getData(SgExpression *symb, string*) { return OriginalSymbol(symb->symbol())->identifier(); }
static inline SgSymbol* getData(SgExpression *symb, SgSymbol**) { return OriginalSymbol(symb->symbol()); }
static inline SgExpression* getData(SgExpression *symb, SgExpression**) { return symb; }

static inline Symbol* getData(SgExpression *symb, Symbol**)
{
    SgSymbol *symbOr = OriginalSymbol(symb->symbol());
    auto it = dictCreated.find(symbOr);
    if (it == dictCreated.end())
        it = dictCreated.insert(it, make_pair(symbOr, new Symbol(symbOr)));
    return it->second;
}

template<typename fillType>
void fillPrivatesFromComment(Statement *stIn, set<fillType> &privates)
{
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        if (st->variant() == SPF_ANALYSIS_DIR)
        {
            SgExpression *exprList = st->expr(0);
            while (exprList)
            {
                if (exprList->lhs()->variant() == ACC_PRIVATE_OP)
                {                    
                    SgExpression *list = exprList->lhs()->lhs();
                    while (list)
                    {
                        fillType *dummy = NULL;
                        privates.insert(getData(list->lhs(), dummy));
                        list = list->rhs();
                    }
                    break;
                }
                exprList = exprList->rhs();
            }
        }
    }
}

template void fillPrivatesFromComment(Statement *st, set<string> &privates);
template void fillPrivatesFromComment(Statement *st, set<SgSymbol*> &privates);
template void fillPrivatesFromComment(Statement *st, set<Symbol*> &privates);

//for simple reduction
template<typename fillType>
void fillReductionsFromComment(Statement *stIn, map<string, set<fillType>> &reduction)
{    
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        if (st->variant() == SPF_ANALYSIS_DIR)
        {
            SgExpression *exprList = st->expr(0);
            while (exprList)
            {
                if (exprList->lhs()->variant() == REDUCTION_OP)
                {
                    SgExpression *list = exprList->lhs()->lhs();
                    while (list)
                    {
                        SgExpression *currRed = list->lhs();
                        
                        fillType redSymb, *dummy = NULL;
                        //minloc/maxloc
                        if (currRed->rhs()->variant() == EXPR_LIST)
                            redSymb = getData(currRed->rhs()->lhs(), dummy);
                        else
                            redSymb = getData(currRed->rhs(), dummy);
                        string oper = ((SgKeywordValExp *)(currRed->lhs()))->value();
                        
                        auto it = reduction.find(oper);                        
                        if (oper == "minloc" || oper == "maxloc")
                        {
                            //skip
                            //__spf_print(1, "  MAXLOC/MINLOC operation from SPF not supported yet, ignored\n");                            
                        }
                        else
                        {
                            if (it == reduction.end())
                                it = reduction.insert(it, make_pair(oper, set<fillType>()));
                            it->second.insert(redSymb);
                        }
                        list = list->rhs();
                    }
                }
                exprList = exprList->rhs();
            }
        }
    }
}

template void fillReductionsFromComment(Statement *st, map<string, set<string>> &reduction);
template void fillReductionsFromComment(Statement *st, map<string, set<SgSymbol*>> &reduction);

//for min/max loc reduction
template<typename fillType>
void fillReductionsFromComment(Statement *stIn, map<string, set<tuple<fillType, fillType, int>>> &reduction)
{
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        if (st->variant() == SPF_ANALYSIS_DIR)
        {
            SgExpression *exprList = st->expr(0);
            while (exprList)
            {
                if (exprList->lhs()->variant() == REDUCTION_OP)
                {
                    SgExpression *list = exprList->lhs()->lhs();
                    while (list)
                    {
                        SgExpression *currRed = list->lhs();

                        fillType redSymb, *dummy = NULL;
                        //minloc/maxloc
                        if (currRed->rhs()->variant() == EXPR_LIST)
                            redSymb = getData(currRed->rhs()->lhs(), dummy);
                        else
                            redSymb = getData(currRed->rhs(), dummy);
                        string oper = ((SgKeywordValExp *)(currRed->lhs()))->value();

                        auto it = reduction.find(oper);
                        if (oper == "minloc" || oper == "maxloc")
                        {
                            fillType arraySymb = getData(currRed->rhs()->rhs()->lhs(), dummy);
                            int dim = currRed->rhs()->rhs()->rhs()->lhs()->valueInteger();

                            if (it == reduction.end())
                                it = reduction.insert(it, make_pair(oper, set<tuple<fillType, fillType, int>>()));
                            it->second.insert(std::make_tuple(redSymb, arraySymb, dim));
                        }
                        else
                        {
                            //skip
                        }
                        list = list->rhs();
                    }
                }
                exprList = exprList->rhs();
            }
        }
    }
}

template void fillReductionsFromComment(Statement *st, map<string, set<tuple<string, string, int>>> &reduction);
template void fillReductionsFromComment(Statement *st, map<string, set<tuple<SgSymbol*, SgSymbol*, int>>> &reduction);

template<typename fillType>
static void fillShadowAcross(const int type, Statement *stIn, vector<pair<pair<fillType, string>, vector<pair<int, int>>>> &data, set<fillType> *corner = NULL)
{
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        for (int list = 0; list < 3; ++list)
        {
            SgExpression *exprList = st->expr(list);
            while (exprList)
            {
                if (exprList->lhs()->variant() == type)
                {
                    SgExpression *listExp = exprList->lhs()->lhs();
                    while (listExp)
                    {
                        SgExpression *list = listExp;
                        bool needCornerAdd = false;
                        if (list->lhs()->variant() == ARRAY_OP)
                        {
                            list = list->lhs();
                            needCornerAdd = true;
                        }

                        SgSymbol *symb = OriginalSymbol(list->lhs()->symbol());

                        fillType arrayName, *dummy = NULL;
                        arrayName = getData(list->lhs(), dummy);
                        bool cond = false;

                        if (corner && needCornerAdd)
                            corner->insert(arrayName);

                        pair<pair<fillType, string>, vector<pair<int, int>>> *toAdd;
                        for (int i = 0; i < data.size(); ++i)
                        {
                            if (data[i].first.first == arrayName)
                            {
                                toAdd = &data[i];
                                cond = true;
                                break;
                            }
                        }

                        if (!cond)
                        {
                            auto uniqKey = getFromUniqTable(symb);
                            data.push_back(make_pair(make_pair(arrayName, getShortName(uniqKey)), vector<pair<int, int>>()));
                            toAdd = &data.back();
                        }

                        SgExpression *listEx = list->lhs()->lhs();
                        int idx = 0;
                        while (listEx)
                        {
                            SgExpression *width = listEx->lhs();
                            const int left = width->lhs()->valueInteger();
                            const int right = width->rhs()->valueInteger();
                            if (toAdd->second.size() <= idx)
                                toAdd->second.push_back(make_pair(left, right));
                            else
                            {
                                toAdd->second[idx].first = std::max(toAdd->second[idx].first, left);
                                toAdd->second[idx].second = std::max(toAdd->second[idx].second, right);
                            }
                            idx++;
                            listEx = listEx->rhs();
                        }

                        listExp = listExp->rhs();
                    }
                }
                exprList = exprList->rhs();
            }
        }
    }
}


template<typename fillType>
void fillShadowAcrossFromComment(const int type, Statement *stIn, vector<pair<pair<fillType, string>, vector<pair<int, int>>>> &data)
{
    if (stIn)
        if (stIn->GetOriginal()->variant() == SPF_PARALLEL_DIR)
            fillShadowAcross(type, stIn, data);
}

template void fillShadowAcrossFromComment(const int type, Statement *st, vector<pair<pair<string, string>, vector<pair<int, int>>>> &data);
template void fillShadowAcrossFromComment(const int type, Statement *st, vector<pair<pair<SgSymbol*, string>, vector<pair<int, int>>>> &data);


template<typename fillType>
void fillShadowAcrossFromParallel(const int type, Statement *stIn, vector<pair<pair<fillType, string>, vector<pair<int, int>>>> &data, set<fillType> &corner)
{
    if (stIn)
        if (stIn->GetOriginal()->variant() == DVM_PARALLEL_ON_DIR)
            fillShadowAcross(type, stIn, data, &corner);
}

template void fillShadowAcrossFromParallel(const int type, Statement *st, vector<pair<pair<string, string>, vector<pair<int, int>>>> &data, set<string> &corner);
template void fillShadowAcrossFromParallel(const int type, Statement *st, vector<pair<pair<SgSymbol*, string>, vector<pair<int, int>>>> &data, set<SgSymbol*> &corner);


template<typename fillType>
void fillRemoteFromComment(Statement *stIn, map<pair<fillType, string>, Expression*> &remote, bool isFull, int type)
{
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        if (st->variant() == type)
        {
            SgExpression *exprList = NULL;
            if (type == SPF_PARALLEL_DIR || type == DVM_REMOTE_ACCESS_DIR)
                exprList = st->expr(0);
            else if (type == DVM_PARALLEL_ON_DIR)
                exprList = st->expr(1);            

            while (exprList)
            {
                if (exprList->lhs()->variant() == REMOTE_ACCESS_OP || type == DVM_REMOTE_ACCESS_DIR)
                {
                    SgExpression *list;
                    if (type == DVM_REMOTE_ACCESS_DIR)
                        list = exprList;
                    else
                        list = exprList->lhs()->lhs();

                    while (list)
                    {
                        fillType arrayName, *dummy = NULL;
                        arrayName = getData(list->lhs(), dummy);
                        
                        char *str;
                        if (list->lhs()->lhs())
                            str = list->lhs()->lhs()->unparse();
                        else
                            str = "";

                        if (isFull)
                            remote.insert(make_pair(make_pair(arrayName, string(str)), new Expression(list->lhs())));
                        else
                        {
                            if (list->lhs()->lhs())
                                remote.insert(make_pair(make_pair(arrayName, string(str)), new Expression(list->lhs()->lhs())));
                            else
                                remote.insert(make_pair(make_pair(arrayName, string(str)), new Expression(new SgExprListExp())));
                        }
                        list = list->rhs();
                    }
                }

                if (type == DVM_REMOTE_ACCESS_DIR)
                    break;
                exprList = exprList->rhs();
            }
        }
    }
}

template void fillRemoteFromComment(Statement *st, map<pair<string, string>, Expression*> &remote, bool isFull, int type);
template void fillRemoteFromComment(Statement *st, map<pair<SgSymbol*, string>, Expression*> &remote, bool isFull, int type);
template void fillRemoteFromComment(Statement *st, map<pair<SgExpression*, string>, Expression*> &remote, bool isFull, int type);

void fillAcrossInfoFromDirectives(const LoopGraph *loopInfo, vector<pair<pair<string, string>, vector<pair<int, int>>>> &acrossInfo)
{
    SgForStmt *currentLoop = (SgForStmt*)loopInfo->loop;
    for (auto &data : getAttributes<SgStatement*, SgStatement*>(currentLoop, set<int>{ SPF_ANALYSIS_DIR, SPF_PARALLEL_DIR, SPF_TRANSFORM_DIR }))
        fillShadowAcrossFromComment(ACROSS_OP, new Statement(data), acrossInfo);
}

void fillFissionPrivatesExpansionFromComment(Statement *stIn, vector<string> &vars)
{
    if (stIn)
    {
        SgStatement *st = stIn->GetOriginal();
        if (st->variant() == SPF_TRANSFORM_DIR)
        {
            SgExpression *exprList = st->expr(0);
            while (exprList)
            {
                if (exprList->lhs() && (exprList->lhs()->variant() == SPF_FISSION_OP || exprList->lhs()->variant() == SPF_PRIVATES_EXPANSION_OP))
                {
                    SgExpression *list = exprList->lhs()->lhs();
                    while (list)
                    {
                        if (list->lhs()->variant() == VAR_REF)
                            vars.push_back(list->lhs()->symbol()->identifier());

                        list = list->rhs();
                    }
                }
                exprList = exprList->rhs();
            }
        }
    }
}

void fillInfoFromDirectives(const LoopGraph *loopInfo, ParallelDirective *directive)
{
    SgForStmt *currentLoop = (SgForStmt*)loopInfo->loop;

    for (auto &data : getAttributes<SgStatement*, SgStatement*>(currentLoop, set<int>{ SPF_ANALYSIS_DIR, SPF_PARALLEL_DIR, SPF_TRANSFORM_DIR }))
    {
        Statement *sData = new Statement(data);
        fillPrivatesFromComment(sData, directive->privates);
        fillReductionsFromComment(sData, directive->reduction);
        fillReductionsFromComment(sData, directive->reductionLoc);
        fillShadowAcrossFromComment(SHADOW_OP, sData, directive->shadowRenew);
        fillShadowAcrossFromComment(ACROSS_OP, sData, directive->across);
        fillRemoteFromComment(sData, directive->remoteAccess);
    }
}
