#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <assert.h>

#if _WIN32 && NDEBUG && __BOOST
#include <boost/thread.hpp>
#endif
extern int passDone;

#include "../Distribution/Distribution.h"
#include "../Distribution/GraphCSR.h"
#include "../Distribution/Arrays.h"
#include "../ParallelizationRegions/ParRegions.h"

#include "../Utils/errors.h"
#include "loop_analyzer.h"
#include "directive_parser.h"
#include "directive_creator.h"

#include "../Utils/SgUtils.h"
#include "../Utils/AstWrapper.h"

#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ParallelizationRegions/ParRegions_func.h"
#include "../DynamicAnalysis/gCov_parser_func.h"

#include "../ExpressionTransform/expr_transform.h"
#include "../SageAnalysisTool/depInterfaceExt.h"
#ifdef _WIN32
#include "../VisualizerCalls/get_information.h"
#endif

using std::vector;
using std::pair;
using std::tuple;
using std::map;
using std::set;
using std::make_pair;
using std::make_tuple;
using std::get;
using std::string;
using std::wstring;

#define PRINT_ARRAY_ARCS  0
#define PRINT_LOOP_STRUCT 0
#define PRINT_PROF_INFO   0

static REGIME currRegime = UNDEF;
static vector<Messages> *currMessages;

extern int parallizeFreeLoops;
extern int mpiProgram;
extern int ignoreIO;

static bool hasArrayAccessInSubscr(SgExpression *exp)
{
    bool retVal = false;
    if (exp->variant() == ARRAY_REF)
        return true;

    if (exp->lhs())
        retVal |= hasArrayAccessInSubscr(exp->lhs());
    if (exp->rhs())
        retVal |= hasArrayAccessInSubscr(exp->rhs());

    return retVal;
}

bool checkExistence(SgExpression *exp, SgSymbol *doName)
{
    bool retVal = false;
    if (exp->variant() == VAR_REF)
        if (exp->symbol()->id() == doName->id())
            retVal = true;

    if (exp->lhs())
        retVal |= checkExistence(exp->lhs(), doName);
    if (exp->rhs())
        retVal |= checkExistence(exp->rhs(), doName);

    return retVal;
}

static pair<bool, string> constructArrayRefForPrint(SgArrayRefExp *arrayRef, const int dimNum, SgExpression *subscr)
{
    bool needToPrint = true;
    const int num = arrayRef->numberOfSubscripts();
    string ref(arrayRef->symbol()->identifier());
    ref += "(";
    for (int i = 0; i < num; ++i)
    {
        if (i == dimNum)
        {
            char *copySub = copyOfUnparse(subscr->unparse());
            ref += copySub;
            if (subscr->variant() == INT_VAL)
                needToPrint = false;
#ifdef _WIN32
            removeFromCollection(copySub);
#endif
            delete []copySub;
        }
        else
            ref += "*";

        if (i != num - 1)
            ref += ",";
        else
            ref += ")";
    }
    std::transform(ref.begin(), ref.end(), ref.begin(), ::toupper);
    return make_pair(needToPrint, ref);
}

static void addInfoToMaps(map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, SgForStmt *position, SgSymbol *symb, 
                          SgArrayRefExp *arrayRefIn, const int dimNum, const REMOTE_BOOL &value, const int currLine,
                          const int maxDimSize)
{
    ArrayRefExp *arrayRef = new ArrayRefExp(arrayRefIn);
    auto it = loopInfo.find(position);
    if (loopInfo.end() == it)
        it = loopInfo.insert(it, make_pair(position, map<SgSymbol*, ArrayInfo>()));

    auto it1 = it->second.find(symb);
    if (it1 == it->second.end())
        it1 = it->second.insert(it1, make_pair(symb, ArrayInfo()));

    auto it2 = it1->second.arrayAccessUnrec.find(arrayRef);
    if (it2 == it1->second.arrayAccessUnrec.end())
    {
        it2 = it1->second.arrayAccessUnrec.insert(it2, make_pair(arrayRef, make_pair(currLine, vector<unsigned char>())));

        it2->second.second.resize(maxDimSize);
        std::fill(it2->second.second.begin(), it2->second.second.end(), REMOTE_NONE);
    }

    it2->second.second[dimNum] |= value;
}

enum { READ_OP, WRITE_OP, UNREC_OP };
static void addInfoToVectors(map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, SgForStmt *position, SgSymbol *symb, 
                             const int dimNum, const pair<int, int> newCoef, int type, const int maxDimSize, const double currentW)
{
    auto itLoop = loopInfo.find(position);
    if (itLoop == loopInfo.end())
        itLoop = loopInfo.insert(itLoop, make_pair(position, map<SgSymbol*, ArrayInfo>()));

    auto itSymb = itLoop->second.find(symb);
    if (itSymb == itLoop->second.end())
        itSymb = itLoop->second.insert(itSymb, make_pair(symb, ArrayInfo()));

    if (itSymb->second.dimSize < maxDimSize)
    {
        itSymb->second.readOps.resize(maxDimSize);
        itSymb->second.writeOps.resize(maxDimSize);
        itSymb->second.unrecReadOps.resize(maxDimSize);
        itSymb->second.dimSize = maxDimSize;
    }

    if (type == READ_OP)
    {
        auto itAdd = itSymb->second.readOps[dimNum].coefficients.find(newCoef);
        //add only uniq 
        if (itAdd == itSymb->second.readOps[dimNum].coefficients.end())
            itAdd = itSymb->second.readOps[dimNum].coefficients.insert(itAdd, make_pair(newCoef, currentW));        
    }
    else if (type == WRITE_OP)
    {
        auto itAdd = itSymb->second.writeOps[dimNum].coefficients.find(newCoef);
        if (itAdd == itSymb->second.writeOps[dimNum].coefficients.end())
            itAdd = itSymb->second.writeOps[dimNum].coefficients.insert(itAdd, make_pair(newCoef, currentW));        
    }
    else if (type == UNREC_OP)
        itSymb->second.unrecReadOps[dimNum] = true;
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}


static vector<int> matchSubscriptToLoopSymbols(const vector<SgForStmt*> &parentLoops, SgExpression *subscr,
                                               SgArrayRefExp *arrayRefIn, const int side, const int dimNum,
                                               map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo,
                                               const int currLine, const int numOfSubscriptions, const double currentW)
{
    SgExpression *origSubscr = subscr;
    ArrayRefExp *arrayRef = new ArrayRefExp(arrayRefIn);
    
    // REVERT_SUBS has been done before REMOTE_ACC PASS
    if (currRegime == REMOTE_ACC)
    {
        auto data = getAttributes<SgExpression*, SgExpression*>(arrayRefIn, set<int>{ ARRAY_REF });
        if (data.size() == 1)
        {
            SgExpression *dataS = data[0]->lhs();
            for (int z = 0; z < dimNum; ++z)
                dataS = dataS->rhs();
            subscr = dataS->lhs();
        }
    }

    int countOfSymbols = 0;
    int position = -1;
    vector<int> allPositions;
    bool hasArrayAcc = hasArrayAccessInSubscr(subscr);
    SgSymbol *currOrigArrayS = OriginalSymbol(arrayRef->symbol());

    if (!hasArrayAcc)
    {
        for (int i = 0; i < (int)parentLoops.size(); ++i)
        {
            if (checkExistence(subscr, parentLoops[i]->doName()))
            {
                countOfSymbols++;
                position = i;
                allPositions.push_back(i);
            }
        }
    }

    pair<int, int> coefs = pair<int, int>(0, 0);
    // more than one loop symbol in subscription
    if (countOfSymbols > 1)
    {
        __spf_print(PRINT_ARRAY_ARCS, " <%d|%d> ", 0, 0);
        if (currRegime == DATA_DISTR)
        {
            const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, origSubscr);
            __spf_print(1, "WARN: array ref '%s' at line %d has more than one loop's variables\n", arrayRefString.second.c_str(), currLine);

            wstring messageE, messageR;
            __spf_printToLongBuf(messageE, L"array ref '%s' has more than one loop's variables", to_wstring(arrayRefString.second).c_str());
#if _WIN32
            __spf_printToLongBuf(messageE, R54, to_wstring(arrayRefString.second).c_str());
#endif
            if (currLine > 0)
                currMessages->push_back(Messages(WARR, currLine, messageR, messageE, 1021));
        }

        for (int i = 0; i < allPositions.size(); ++i)
        {
            if (currRegime == REMOTE_ACC)
            {
                if (side == RIGHT)
                    addInfoToMaps(loopInfo, parentLoops[allPositions[i]], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
            }
            else
                addInfoToVectors(loopInfo, parentLoops[allPositions[i]], currOrigArrayS, dimNum, make_pair(0, 0), UNREC_OP, numOfSubscriptions, currentW);
        }
    }
    // no loop symbol in subscription
    else if (countOfSymbols == 0)
    {
        __spf_print(PRINT_ARRAY_ARCS, " <%d|%d> ", 0, 0);
        if (currRegime == REMOTE_ACC)
        {
            if (side == RIGHT)
                for (int i = 0; i < (int)parentLoops.size(); ++i)
                    addInfoToMaps(loopInfo, parentLoops[i], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
        }
        else if (currRegime == DATA_DISTR)
        {
            const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, origSubscr);

            if (!hasArrayAcc)
            {
                if (parentLoops.size() != 0 && (arrayRefString.first || side == LEFT))
                {
                    __spf_print(1, "WARN: array ref '%s' at line %d does not have loop variables\n", arrayRefString.second.c_str(), currLine);

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"array ref '%s' does not have loop variables", to_wstring(arrayRefString.second).c_str());
#if _WIN32
                    __spf_printToLongBuf(messageR, R55, to_wstring(arrayRefString.second).c_str());
#endif
                    if (currLine > 0)
                        currMessages->push_back(Messages(WARR, currLine, messageR, messageE, 1021));
                }
            }
            else
            {
                __spf_print(1, "WARN: array ref '%s' at line %d has indirect access\n", arrayRefString.second.c_str(), currLine);

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"array ref '%s' has indirect access", to_wstring(arrayRefString.second).c_str());
#if _WIN32
                __spf_printToLongBuf(messageR, R56, to_wstring(arrayRefString.second).c_str());
#endif
                if (currLine > 0)
                    currMessages->push_back(Messages(WARR, currLine, messageR, messageE, 1022));
            }
        }
    }
    else
    {
        bool needToCacl = true;
        if (subscr->variant() == VAR_REF)
        {
            if (subscr->symbol()->id() == (parentLoops[position]->doName())->id())
            {
                coefs.first = 1;
                needToCacl = false;
            }
        }

        if (needToCacl)
            getCoefsOfSubscript(coefs, subscr, parentLoops[position]->doName());
        __spf_print(PRINT_ARRAY_ARCS, " <%d %d> ", coefs.first, coefs.second);

        if (coefs.first == 0) // && coefs.second == 0)
        {
            if (currRegime == REMOTE_ACC)
            {
                if (side == RIGHT)
                    addInfoToMaps(loopInfo, parentLoops[position], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
            }
            else if (currRegime == DATA_DISTR)
            {                
                const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, origSubscr);
                __spf_print(1, "WARN: can not calculate index expression for array ref '%s' at line %d\n", arrayRefString.second.c_str(), currLine);
                addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, UNREC_OP, numOfSubscriptions, currentW);
                if (side == LEFT)
                    allPositions.clear();

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"can not calculate index expression for array ref '%s'", to_wstring(arrayRefString.second).c_str());
#if _WIN32
                __spf_printToLongBuf(messageR, R57, to_wstring(arrayRefString.second).c_str());
#endif
                if (currLine > 0)
                    currMessages->push_back(Messages(WARR, currLine, messageR, messageE, 1023));
            }
        }
        else
        {
            if (currRegime == REMOTE_ACC)
            {
                if (side == RIGHT)
                {
                    //TODO: remove with call of addInfoToVectors
                    auto itLoop = loopInfo.find(parentLoops[position]);
                    if (itLoop == loopInfo.end())
                        itLoop = loopInfo.insert(itLoop, make_pair(parentLoops[position], map<SgSymbol*, ArrayInfo>()));

                    auto itSymb = itLoop->second.find(currOrigArrayS);
                    if (itSymb == itLoop->second.end())
                        itSymb = itLoop->second.insert(itSymb, make_pair(currOrigArrayS, ArrayInfo()));

                    auto itArrayAcc = itSymb->second.arrayAccess.find(arrayRef);
                    if (itArrayAcc == itSymb->second.arrayAccess.end())
                        itArrayAcc = itSymb->second.arrayAccess.insert(itArrayAcc, make_pair(arrayRef, make_pair(currLine, std::vector<ArrayOp>())));

                    if (itArrayAcc->second.second.size() < numOfSubscriptions)
                        itArrayAcc->second.second.resize(numOfSubscriptions);

                    //add only uniq 
                    auto itAdd = itArrayAcc->second.second[dimNum].coefficients.find(coefs);
                    if (itAdd == itArrayAcc->second.second[dimNum].coefficients.end())
                        itAdd = itArrayAcc->second.second[dimNum].coefficients.insert(itAdd, make_pair(coefs, currentW));
                }

                //if we found regular access to array - set it false
                addInfoToMaps(loopInfo, parentLoops[position], currOrigArrayS, arrayRef, dimNum, REMOTE_FALSE, currLine, numOfSubscriptions);
            }

            if (coefs.first < 0)
            {
                if (currRegime == DATA_DISTR)
                {
                    const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, origSubscr);
                    const int line = (currLine < 0) ? parentLoops[position]->localLineNumber() : currLine;

                    __spf_print(1, "WARN: coefficient A in A*x+B is not positive for array ref '%s' at line %d, inverse distribution in not supported yet\n", arrayRefString.second.c_str(), line);
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, UNREC_OP, numOfSubscriptions, currentW);

                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"coefficient A in A*x+B is not positive for array ref '%s', inverse distribution in not supported yet", to_wstring(arrayRefString.second).c_str());
#ifdef _WIN32
                    __spf_printToLongBuf(messageR, R58, to_wstring(arrayRefString.second).c_str());
#endif
                    if (line > 0)
                        currMessages->push_back(Messages(WARR, line, messageR, messageE, 1024));
                }
            }
            else
            {
                if (side == LEFT)
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, WRITE_OP, numOfSubscriptions, currentW);
                else
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, READ_OP, numOfSubscriptions, currentW);
            }
        }
    }

    if (currRegime == PRIVATE_STEP4)
    {
        int *valueSubs = new int[2];
        valueSubs[0] = coefs.first;
        valueSubs[1] = coefs.second;
#ifdef __SPF
        addToCollection(__LINE__, __FILE__, valueSubs, 2);
#endif
        const vector<int*> &coefs = getAttributes<SgExpression*, int*>(subscr, set<int>{ INT_VAL });
        if (coefs.size() == 0)
        {
            subscr->addAttribute(INT_VAL, valueSubs, sizeof(int*));
            if (position != -1 && allPositions.size() == 1 && position < parentLoops.size())
                subscr->addAttribute(FOR_NODE, parentLoops[position], sizeof(SgStatement));
        }
    }

    return allPositions;
}

static vector<int> matchArrayToLoopSymbols(const vector<SgForStmt*> &parentLoops, SgExpression *currExp, const int side,
                                    map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, const int currLine,
                                    map<int, LoopGraph*> &sortedLoopGraph, const ParallelRegion *reg, const double currentW,
                                    const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    SgArrayRefExp *arrayRef = (SgArrayRefExp*)currExp;
    int numOfSubs = arrayRef->numberOfSubscripts();

    currExp = currExp->lhs();    
    vector<int> wasFound(parentLoops.size());
    vector<int> matched(numOfSubs);
    vector<int> matchedToDim(parentLoops.size());
    std::fill(wasFound.begin(), wasFound.end(), 0);
    std::fill(matched.begin(), matched.end(), -1);
    std::fill(matchedToDim.begin(), matchedToDim.end(), -1);
    int maxMatched = 0;
    int sumMatched = 0;

    for (int i = 0; i < numOfSubs; ++i)
    {
        vector<int> matchToLoops = matchSubscriptToLoopSymbols(parentLoops, currExp->lhs(), arrayRef, side, i, loopInfo, currLine, numOfSubs, currentW);
        for (int k = 0; k < matchToLoops.size(); ++k)
        {
            wasFound[matchToLoops[k]]++;
            matchedToDim[matchToLoops[k]] = i;
        }

        matched[i] = matchToLoops.size();
        sumMatched += matchToLoops.size();
        maxMatched = std::max(maxMatched, (int)matchToLoops.size());
        currExp = currExp->rhs();
    }

    //full array is used, add unknown operations to all loops
    if (numOfSubs == 0)
    {
        SgSymbol *currOrigArrayS = OriginalSymbol(arrayRef->symbol());
        auto arrType = isSgArrayType(currOrigArrayS->type());
        if (arrType != NULL)
        {
            for (int d = 0; d < arrType->dimension(); ++d)
                for (int i = 0; i < parentLoops.size(); ++i)
                    addInfoToVectors(loopInfo, parentLoops[i], currOrigArrayS, d, make_pair(0, 0), UNREC_OP, arrType->dimension(), currentW);
        }
    }

    if (currRegime == PRIVATE_STEP4)
        return wasFound;

    bool ifUnknownFound = false;
    vector<int> canNotMapToLoop;
    for (int i = 0; i < wasFound.size(); ++i)
    {
        if (wasFound[i] != 1)
        {
            auto itLoop = sortedLoopGraph.find(parentLoops[i]->lineNumber());
            if (itLoop == sortedLoopGraph.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            ifUnknownFound = true;
            if (side == LEFT && (currRegime == DATA_DISTR || currRegime == COMP_DISTR))
                itLoop->second->hasUnknownArrayAssigns = true;

            itLoop->second->hasUnknownDistributedMap = true;
            canNotMapToLoop.push_back(parentLoops[i]->lineNumber());
        }
    }

    if (side == LEFT)
    {
        if (ifUnknownFound && (currRegime == DATA_DISTR))
        {
            const string arrayRefS = arrayRef->unparse();
            for (auto &line : canNotMapToLoop)
            {
                __spf_print(1, "WARN: can not map write to array '%s' to loop on line %d\n", arrayRefS.c_str(), line);

                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"can not map write to array '%s' to this loop", to_wstring(arrayRefS).c_str());
#if _WIN32
                __spf_printToLongBuf(messageR, R59, to_wstring(arrayRefS).c_str());
#endif
                if (line > 0)
                    currMessages->push_back(Messages(WARR, line, messageR, messageE, 1025));
            }
        }
    }
    else if (side == RIGHT)
    {
        SgSymbol *currOrigArrayS = OriginalSymbol(arrayRef->symbol());

        if (currRegime == REMOTE_ACC)
        {
            if (sumMatched != parentLoops.size() && sumMatched == numOfSubs)
            {
                DIST::Array *currArray = getArrayFromDeclarated(declaratedInStmt(currOrigArrayS), currOrigArrayS->identifier());
                if (currArray)
                {
                    set<DIST::Array*> realArrayRefs;
                    getRealArrayRefs(currArray, currArray, realArrayRefs, arrayLinksByFuncCalls);

                    bool ok = true;
                    DIST::Array *templ = NULL;
                    vector<int> alignCoefs;
                    for (auto &real : realArrayRefs)
                    {
                        DIST::Array *curr = real->GetTemplateArray(reg->GetId());
                        alignCoefs = currArray->GetLinksWithTemplate(reg->GetId());

                        if (templ == NULL)
                            templ = curr;
                        else if (templ != curr)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }

                    //check array's alignment
                    for (int z = 0; z < wasFound.size() && ok; ++z)
                    {
                        if (wasFound[z])
                        {
                            auto it = sortedLoopGraph.find(parentLoops[z]->lineNumber());
                            if (it == sortedLoopGraph.end())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            LoopGraph *loop =  it->second;
                            if (!templ)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                            
                            const DataDirective &dataDirectives = reg->GetDataDir();
                            const vector<int> &currentVariant = reg->GetCurrentVariant();

                            auto &tmp = dataDirectives.distrRules;
                            pair<DIST::Array*, const DistrVariant*> currentVar;
                            for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                            {
                                if (tmp[z1].first == templ)
                                {
                                    currentVar = make_pair(tmp[z1].first, &tmp[z1].second[currentVariant[z1]]);
                                    break;
                                }
                            }
                            if (!currentVar.first)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            if (!(loop->directiveForLoop))
                                continue;
                            DIST::Array *loopT = loop->directiveForLoop->arrayRef;

                            int dimToMap = -1;
                            for (int z = 0; z < loopT->GetDimSize(); ++z)
                                if (loop->directiveForLoop->on[z].first != "*")
                                    dimToMap = z;
                            if (dimToMap != -1)
                            {
                                if (loopT != templ)
                                {
                                    DIST::Array *loopTempl = loopT->GetTemplateArray(reg->GetId());
                                    if (templ != loopTempl)
                                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                    auto loopAlignCoefs = loopT->GetLinksWithTemplate(reg->GetId());
                                    if (loopAlignCoefs[dimToMap] == -1)
                                    {
                                        if (loop->loop->GetOriginal()->lexPrev()->variant() == DVM_PARALLEL_ON_DIR)
                                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                                        else
                                            continue;
                                    }
                                    else
                                        dimToMap = loopAlignCoefs[dimToMap];
                                }

                                if (matchedToDim[z] != -1 && currentVar.second->distRule[alignCoefs[matchedToDim[z]]] == distType::BLOCK)
                                {
                                    bool found = false;

                                    for (int l = 0; l < alignCoefs.size(); ++l)
                                    {
                                        if (alignCoefs[l] == dimToMap)
                                            found = true;
                                    }
                                    ok = found;

                                    if (!ok)
                                        addInfoToMaps(loopInfo, parentLoops[z], currOrigArrayS, arrayRef, matchedToDim[z], REMOTE_TRUE, currLine, numOfSubs);
                                }
                            }
                            else
                                ;//printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                        }
                    }

                    if (ok)
                        for (int z = 0; z < wasFound.size(); ++z)
                            wasFound[z] = 1;
                }
            }
        }

        if (ifUnknownFound && (currRegime == REMOTE_ACC))
        {
            if (sumMatched != numOfSubs || 
                maxMatched != 1 || 
                sumMatched != parentLoops.size() // && sumMatched != numOfSubs
                )
            {
                int local = 0;
                bool hasLimits = false;
                for (int i = 0; i < wasFound.size(); ++i)
                {
                    if (wasFound[i] == 1)
                    {
                        auto itLoop = sortedLoopGraph.find(parentLoops[i]->lineNumber());
                        if (itLoop == sortedLoopGraph.end())
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                        if (itLoop->second->hasLimitsToParallel())
                            hasLimits = true;
                    }
                }
                for (int i = 0; i < wasFound.size(); ++i)
                {
                    if (wasFound[i] != 1)
                    {
                        for (int k = 0; k < numOfSubs; ++k)
                            if (hasLimits)
                                addInfoToMaps(loopInfo, parentLoops[i], currOrigArrayS, arrayRef, k, REMOTE_TRUE, currLine, numOfSubs);                        
                    }
                }
            }
        }
    }

    return wasFound;
}

static void findArrayRef(const vector<SgForStmt*> &parentLoops, SgExpression *currExp, const int lineNum, const int side, 
                         map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, const int currLine, const set<string> &privatesVars,
                         map<int, LoopGraph*> &sortedLoopGraph, const map<string, vector<SgExpression*>> &commonBlocks,
                         const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays, 
                         bool wasDistributedArrayRef, map<string, pair<SgSymbol*, SgStatement*>> &notMappedDistributedArrays,
                         set<string> &mappedDistrbutedArrays, SgStatement *currentSt, const ParallelRegion *reg, const double currentW,
                         const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls)
{
    int nextSide = side;
    if (currExp->variant() == ARRAY_REF)
    {
        //... and current array is not in private list
        if (privatesVars.find(string(OriginalSymbol(currExp->symbol())->identifier())) == privatesVars.end())
        {
            if (wasDistributedArrayRef)
            {
                int depth = 1;
                for (int i = parentLoops.size() - 1; i >= 0; --i, ++depth)
                {
                    auto itLoop = sortedLoopGraph.find(parentLoops[i]->lineNumber());
                    if (itLoop == sortedLoopGraph.end())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    if (itLoop->second->perfectLoop != depth)
                        break;
                    itLoop->second->hasIndirectAccess = true;
                }
                SgSymbol *symb = currExp->symbol();
                if (symb->type()->variant() == T_ARRAY)
                    notMappedDistributedArrays[symb->identifier()] = make_pair(symb, currentSt);
            }
            else
            {
                wasDistributedArrayRef = true;
                const char *printSide = NULL;
                if (PRINT_ARRAY_ARCS)
                    printBlanks(2, (int)parentLoops.size());
                if (side == LEFT)
                    printSide = "W_OP";
                else
                    printSide = "R_OP";
                
                __spf_print(PRINT_ARRAY_ARCS, "%s to array <%s> on line %d: ", printSide, OriginalSymbol(currExp->symbol())->identifier(), lineNum);
                bool wasMapped = false;
                vector<int> matched = matchArrayToLoopSymbols(parentLoops, currExp, side, loopInfo, currLine, sortedLoopGraph, reg, currentW, arrayLinksByFuncCalls);
                for (int z = 0; z < matched.size(); ++z)
                    wasMapped |= (matched[z] != 0);

                if (parentLoops.size() == 0)
                {
                    SgSymbol *symb = currExp->symbol();
                    if (symb->type()->variant() == T_ARRAY)
                        notMappedDistributedArrays[symb->identifier()] = make_pair(symb, currentSt);
                }
                else
                {
                    if (wasMapped)
                        mappedDistrbutedArrays.insert(currExp->symbol()->identifier());
                    else
                    {
                        SgSymbol *symb = currExp->symbol();
                        if (symb->type()->variant() == T_ARRAY)
                            notMappedDistributedArrays[symb->identifier()] = make_pair(symb, currentSt);
                    }
                }
                __spf_print(PRINT_ARRAY_ARCS, "\n");
            }
        }
        else
        {
            if (currRegime == DATA_DISTR && side == LEFT)
            {
                auto symb = OriginalSymbol(currExp->symbol());
                SgStatement *decl = declaratedInStmt(symb);
                auto uniqKey = getUniqName(commonBlocks, decl, symb);

                auto itFound = declaratedArrays.find(uniqKey);
                if (itFound == declaratedArrays.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                //TODO: array access to non distributed arrays, add CONSISTENT
                if (itFound->second.first->GetNonDistributeFlagVal() != DIST::DISTR)
                {
                    set<string> loopsPrivates;
                    set<string> loopsRedUnited;
                    map<string, set<string>> loopsReductions;
                    map<string, set<tuple<string, string, int>>> loopsReductionsLoc;

                    
                    for (auto &loop : parentLoops)
                    {
                        for (auto &data : getAttributes<SgStatement*, SgStatement*>(loop, set<int>{ SPF_ANALYSIS_DIR }))
                        {
                            fillPrivatesFromComment(new Statement(data), loopsPrivates);
                            fillReductionsFromComment(new Statement(data), loopsReductions);
                            fillReductionsFromComment(new Statement(data), loopsReductionsLoc);
                        }
                    }

                    for (auto &elem : loopsReductions)
                    {
                        for (auto &setElem : elem.second)
                        {
                            loopsPrivates.insert(setElem);
                            loopsRedUnited.insert(setElem);
                        }
                    }

                    for (auto &elem : loopsReductionsLoc)
                    {
                        for (auto &setElem : elem.second)
                        {
                            loopsPrivates.insert(get<0>(setElem));
                            loopsPrivates.insert(get<1>(setElem));
                            loopsRedUnited.insert(get<0>(setElem));
                            loopsRedUnited.insert(get<1>(setElem));
                        }
                    }

                    const string key = string(OriginalSymbol(currExp->symbol())->identifier());
                    if (loopsPrivates.find(key) == loopsPrivates.end())
                    {
                        if (mpiProgram == 0)
                        {
                            for (auto& loop : parentLoops)
                            {
                                __spf_print(1, "WARN: write to non distributed array '%s' in loop on line %d\n", symb->identifier(), loop->lineNumber());

                                wstring messageE, messageR;
                                __spf_printToLongBuf(messageE, L"write to non distributed array '%s' in this loop", to_wstring(symb->identifier()).c_str());
#if _WIN32
                                __spf_printToLongBuf(messageR, R61, to_wstring(symb->identifier()).c_str());
#endif
                                if (loop->lineNumber() > 0)
                                    currMessages->push_back(Messages(WARR, loop->lineNumber(), messageR, messageE, 1026));
                                sortedLoopGraph[loop->lineNumber()]->hasWritesToNonDistribute = true;
                            }
                        }
                    }
                    else if (loopsRedUnited.find(key) == loopsRedUnited.end())
                    {
                        auto saveReg = currRegime;
                        currRegime = PRIVATE_STEP4;
                        bool wasMapped = false;
                        map<SgForStmt*, map<SgSymbol*, ArrayInfo>> tmpLoopInfo = loopInfo;

                        vector<int> matched = matchArrayToLoopSymbols(parentLoops, currExp, side, tmpLoopInfo, currLine, sortedLoopGraph, reg, currentW, arrayLinksByFuncCalls);
                        for (int z = 0; z < matched.size(); ++z)
                            wasMapped |= (matched[z] != 0);

                        currRegime = saveReg;

                        if (wasMapped)
                        {
                            int z = 0;
                            if (mpiProgram == 0)
                            {
                                for (auto& loop : parentLoops)
                                {
                                    if (tmpLoopInfo.find(loop) != tmpLoopInfo.end() && matched[z])
                                    {
                                        wstring messageE, messageR;
                                        __spf_printToLongBuf(messageE, L"write to non distributed array '%s' in this loop", to_wstring(symb->identifier()).c_str());
#if _WIN32
                                        __spf_printToLongBuf(messageR, R60, to_wstring(symb->identifier()).c_str());
#endif
                                        if (loop->lineNumber() > 0)
                                            currMessages->push_back(Messages(WARR, loop->lineNumber(), messageR, messageE, 1026));
                                        sortedLoopGraph[loop->lineNumber()]->hasWritesToNonDistribute = true;
                                    }
                                    ++z;
                                }
                            }
                        }
                    }
                }
            }
        }
        nextSide = (side == LEFT) ? RIGHT : side;
    }

    bool needToContinue = true;
    if (currExp->variant() == FUNC_CALL)
    {
        SgFunctionCallExp *funcExp = (SgFunctionCallExp*)currExp;
        auto currFunc = isUserFunctionInProject(funcExp->funName()->identifier());
        if (currFunc)
        {
            for (int z = 0; z < funcExp->numberOfArgs(); ++z)
            {
                if ((currFunc->funcParams.inout_types[z] & OUT_BIT) != 0)
                    nextSide = LEFT;
                else
                    nextSide = RIGHT;
                findArrayRef(parentLoops, funcExp->arg(z), lineNum, nextSide, loopInfo, currLine, privatesVars, sortedLoopGraph, 
                             commonBlocks, declaratedArrays, wasDistributedArrayRef, notMappedDistributedArrays, 
                             mappedDistrbutedArrays, currentSt, reg, currentW, arrayLinksByFuncCalls);
            }
            needToContinue = false;
        }
    }
    
    if (needToContinue)
    {
        if (currExp->lhs())
            findArrayRef(parentLoops, currExp->lhs(), lineNum, nextSide, loopInfo, currLine, privatesVars, sortedLoopGraph, 
                         commonBlocks, declaratedArrays, wasDistributedArrayRef, notMappedDistributedArrays, 
                         mappedDistrbutedArrays, currentSt, reg, currentW, arrayLinksByFuncCalls);
        if (currExp->rhs())
            findArrayRef(parentLoops, currExp->rhs(), lineNum, nextSide, loopInfo, currLine, privatesVars, sortedLoopGraph, 
                         commonBlocks, declaratedArrays, wasDistributedArrayRef, notMappedDistributedArrays,
                         mappedDistrbutedArrays, currentSt, reg, currentW, arrayLinksByFuncCalls);
    }
}

#define FIRST(x)  get<0>(x)
#define SECOND(x) get<1>(x)
#define THIRD(x)  get<2>(x)

map<string, string> shortFileNames;
static int uniqfileNames = 0;

string getShortName(const tuple<int, string, string> &uniqKey)
{
    const char *declFileName = SECOND(uniqKey).c_str();
    const char *varName = THIRD(uniqKey).c_str();
    const int position = FIRST(uniqKey);

    map<string, string>::iterator it;
    it = shortFileNames.find(string(declFileName));

    string retVal = "";
    if (it == shortFileNames.end())
    {
        retVal = string("f") + std::to_string(uniqfileNames) + string("_");
        shortFileNames[string(declFileName)] = retVal;
        uniqfileNames++;
    }
    else
        retVal = it->second;
    return retVal + std::to_string(position) + string("_") + string(varName);
}

static int fillSizes(SgExpression *res, int &left, int &right)
{
    int err = 0;
    if (res->lhs()->variant() == INT_VAL)
        left = res->lhs()->valueInteger();
    else if (res->lhs()->variant() == MINUS_OP)
        left = -1 * res->lhs()->lhs()->valueInteger();
    else
        err = -1;

    if (res->rhs()->variant() == INT_VAL)
        right = res->rhs()->valueInteger();
    else if (res->rhs()->variant() == MINUS_OP)
        right = -1 * res->rhs()->lhs()->valueInteger();
    else
        err = -1;

    return err;
}

static pair<Expression*, Expression*> getElem(SgExpression *exp)
{
    if (exp->lhs() && exp->rhs())
        return make_pair(new Expression(exp->lhs()), new Expression(exp->rhs()));
    else if (exp->lhs())
        return make_pair(new Expression(exp->lhs()), (Expression*)NULL);
    else if (exp->rhs())
        return make_pair((Expression*)NULL, new Expression(exp->rhs()));
    else
        return make_pair((Expression*)NULL, (Expression*)NULL);
}

static void fillIdsFromEx(SgExpression* ex, set<string>& ids)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF)
            ids.insert(ex->symbol()->identifier());

        fillIdsFromEx(ex->lhs(), ids);
        fillIdsFromEx(ex->rhs(), ids);
    }
}

static void doReplacement(SgExpression *ex, const map<string, int> &idsToIdx, const map<int, set<int>> &values)
{
    if (ex)
    {
        if (ex->lhs() && ex->lhs()->variant() == VAR_REF)
        {
            string key = ex->lhs()->symbol()->identifier();
            auto it = idsToIdx.find(key);
            if (it != idsToIdx.end())
            {
                const int value = *values.find(it->second)->second.begin();
                ex->setLhs(*new SgValueExp(value));
            }
        }

        if (ex->rhs() && ex->rhs()->variant() == VAR_REF)
        {
            string key = ex->rhs()->symbol()->identifier();
            auto it = idsToIdx.find(key);
            if (it != idsToIdx.end())
            {
                const int value = *values.find(it->second)->second.begin();
                ex->setRhs(*new SgValueExp(value));
            }
        }

        doReplacement(ex->lhs(), idsToIdx, values);
        doReplacement(ex->rhs(), idsToIdx, values);
    }
}

static SgExpression* replaceConstatantProcedurePars(SgExpression *dimList, SgStatement *proc, const map<string, vector<FuncInfo*>>& allFuncInfo)
{
    if (proc == NULL)
        return dimList;
    
    if (allFuncInfo.size() == 0)
        return dimList;

    const string procN = proc->symbol()->identifier();
    map<string, FuncInfo*> mapFunc;
    createMapOfFunc(allFuncInfo, mapFunc);

    auto it = mapFunc.find(procN);
    if (it == mapFunc.end())
        return dimList;

    FuncInfo* currF = it->second;
    if (currF->funcParams.countOfPars == 0)
        return dimList;

    set<string> ids;
    fillIdsFromEx(dimList, ids);

    if (ids.size() == 0)
        return dimList;

    set<int> idxFound;
    map<string, int> idsToIdx;
    for (int z = 0; z < currF->funcParams.countOfPars; ++z)
    {
        if (ids.find(currF->funcParams.identificators[z]) != ids.end())
        {
            idxFound.insert(z);
            idsToIdx[currF->funcParams.identificators[z]] = z;
        }
    }
    
    if (idxFound.size() == 0 || currF->callsTo.size() == 0)
        return dimList;
    
    map<int, set<int>> values;

    //TODO: many call levels of functions
    for (int z = 0; z < currF->callsTo.size(); ++z)
    {
        FuncInfo* callOfThis = currF->callsTo[z];
        for (int p = 0; p < callOfThis->detailCallsFrom.size(); ++p)
        {
            if (callOfThis->detailCallsFrom[p].first == procN)
            {
                for (auto& par : idxFound)
                {
                    auto parType = callOfThis->actualParams[p].parametersT[par];
                    if (parType != SCALAR_INT_T)
                        return dimList;
                    else
                    {
                        if (callOfThis->actualParams[p].parameters[par] == NULL)
                            return dimList;
                        values[par].insert(((int*)(callOfThis->actualParams[p].parameters[par]))[0]);
                    }
                }
            }
        }
    }

    for (auto& elem : values)
        if (elem.second.size() != 1)
            return dimList;

    doReplacement(dimList, idsToIdx, values);
    return dimList;
}

static vector<pair<Expression*, Expression*>> getArraySizes(vector<pair<int, int>> &sizes, SgSymbol *symb, SgStatement *decl, 
                                                            const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                                                            const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    SgArrayType *type = isSgArrayType(symb->type());
    vector<pair<Expression*, Expression*>> retVal;

    if (type != NULL)
    {
        SgExpression *dimList = type->getDimList();
        int consistInAllocates = 0;
        SgExpression *alloc = NULL;

        
        dimList = replaceConstatantProcedurePars(dimList, getFuncStat(decl), allFuncInfo);
        while (dimList)
        {
            SgExpression *res = ReplaceArrayBoundSizes(dimList->lhs()->copyPtr());
            if (res && res->variant() == INT_VAL)
            {
                sizes.push_back(make_pair(1, res->valueInteger()));
                retVal.push_back(make_pair((Expression*)NULL, new Expression(dimList->lhs())));
            }
            else if (res && res->variant() == DDOT)
            {
                int err, tmpRes;
                if (res->lhs())
                {
                    err = CalculateInteger(res->lhs(), tmpRes);
                    if (err != -1)
                        res->setLhs(new SgValueExp(tmpRes));
                }

                if (res->rhs())
                {
                    err = CalculateInteger(res->rhs(), tmpRes);
                    if (err != -1)
                        res->setRhs(new SgValueExp(tmpRes));
                }

                int left, right;
                bool ok = res->lhs() && res->rhs();
                if (ok)
                {
                    int err = fillSizes(res, left, right);
                    ok = (err == 0);
                }

                if (ok)
                {
                    sizes.push_back(make_pair(left, right));
                    retVal.push_back(getElem(dimList->lhs()));
                }
                else
                {
                    if (alloc == NULL)
                    {
                        for (auto &data : getAttributes<SgStatement*, SgStatement*>(decl, set<int>{ ALLOCATE_STMT }))
                        {
                            if (data->variant() != ALLOCATE_STMT)
                                continue;

                            SgExpression *list = data->expr(0);
                            while (list)
                            {
                                SgArrayRefExp *arrayRef = isSgArrayRefExp(list->lhs());
                                if (arrayRef != NULL)
                                {
                                    SgSymbol *origS = OriginalSymbol(arrayRef->symbol());
                                    DIST::Array *currArray = getArrayFromDeclarated(declaratedInStmt(origS), origS->identifier());

                                    string toCmp = string(origS->identifier());
                                    //TODO: extend 
                                    if (currArray && currArray->GetLocation().first == DIST::l_PARAMETER)
                                    {
                                        auto it = arrayLinksByFuncCalls.find(currArray);
                                        if (it != arrayLinksByFuncCalls.end())
                                        {
                                            bool found = false;
                                            for (auto &elem : it->second)
                                            {
                                                if (elem->GetLocation().first != DIST::l_PARAMETER)
                                                {
                                                    if (elem->GetShortName() == string(symb->identifier()))
                                                    {
                                                        consistInAllocates++;
                                                        alloc = list->lhs()->lhs();
                                                        found = true;
                                                        break;
                                                    }
                                                }
                                            }
                                            if (found)
                                                break;
                                        }
                                    }
                                    else
                                    {
                                        if (toCmp == string(symb->identifier()))
                                        {
                                            consistInAllocates++;
                                            alloc = list->lhs()->lhs();
                                            break;
                                        }
                                    }
                                }
                                list = list->rhs();
                            }
                        }
                    }
                    else // set next in list 
                        alloc = alloc->rhs();

                    if (consistInAllocates != 1)
                    {
                        sizes.push_back(make_pair(-1, -1));
                        retVal.push_back(make_pair((Expression*)NULL, (Expression*)NULL));
                    }
                    else
                    {
                        SgExpression *result = ReplaceArrayBoundSizes(alloc->lhs()->copyPtr());
                        if (result->lhs())
                        {
                            err = CalculateInteger(result->lhs(), tmpRes);
                            if (err != -1)
                                result->setLhs(new SgValueExp(tmpRes));
                        }

                        if (result->rhs())
                        {
                            err = CalculateInteger(result->rhs(), tmpRes);
                            if (err != -1)
                                result->setRhs(new SgValueExp(tmpRes));
                        }

                        if (result->variant() == INT_VAL)
                        {
                            sizes.push_back(make_pair(1, result->valueInteger()));
                            retVal.push_back(make_pair((Expression*)NULL, new Expression(alloc->lhs())));
                        }
                        else if (result->variant() == DDOT)
                        {
                            retVal.push_back(getElem(alloc->lhs()));
                            int left = 0, right = 0;
                            bool ok = result->lhs() && result->rhs();

                            if (ok)
                            {
                                int err = fillSizes(result, left, right);
                                ok = (err == 0);
                            }

                            if (ok)
                                sizes.push_back(make_pair(left, right));
                            else
                                sizes.push_back(make_pair(-1, -1));
                        }
                        else
                        {
                            sizes.push_back(make_pair(-1, -1));
                            retVal.push_back(make_pair((Expression*)NULL, (Expression*)NULL));
                        }
                    }
                }
            }
            else
            {
                sizes.push_back(make_pair(-1, -1));
                retVal.push_back(make_pair((Expression*)NULL, (Expression*)NULL));
            }
            dimList = dimList->rhs();
        }
    }

    return retVal;
}

void recalculateArraySizes(set<DIST::Array*> &arraysDone, const set<DIST::Array*> &allArrays, 
                           const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                           const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    for (auto &array : allArrays)
    {
        auto itF = arraysDone.find(array);
        if (itF == arraysDone.end())
        {
            itF = arraysDone.insert(itF, array);
            Symbol *symb = array->GetDeclSymbol();
            if (symb)
            {
                auto &sizeInfo = array->GetSizes();
                bool needToUpdate = false;
                for (auto &elem : sizeInfo)
                {
                    if (elem.first == elem.second)
                    {
                        needToUpdate = true;
                        break;
                    }
                }

                if (needToUpdate)
                {
                    auto &declInfo = array->GetDeclInfo();
                    bool wasSelect = false;
                    for (auto &elem : declInfo)
                    {
                        int fileId = SgFile::switchToFile(elem.first);
                        if (fileId != -1)
                        {
                            SgFile *tmpfile = &(CurrentProject->file(fileId));
                            wasSelect = true;
                            break;
                        }
                    }

                    if (!wasSelect)
                    {
                        //try to find in includes
                        for (int i = CurrentProject->numberOfFiles() - 1; i >= 0; --i)
                        {                            
                            SgFile *file = &(CurrentProject->file(i));

                            for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
                            {
                                for (auto &elem : declInfo)
                                {
                                    if (make_pair(string(st->fileName()), st->lineNumber()) == elem)
                                    {
                                        wasSelect = true;
                                        break;
                                    }
                                }

                                if (wasSelect)
                                {
                                    //wasSelect = false;
                                    SgStatement *decl = declaratedInStmt(symb);
                                    vector<pair<int, int>> sizes;
                                    auto sizesEx = getArraySizes(sizes, symb, decl, arrayLinksByFuncCalls, allFuncInfo);
                                    array->SetSizes(sizes);
                                    array->SetSizesExpr(sizesEx);
                                }
                            }

                            if (wasSelect)
                                break;                            
                        }

                        if (!wasSelect)
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }
                    else
                    {
                        if (wasSelect)
                        {
                            SgStatement *decl = declaratedInStmt(symb);
                            vector<pair<int, int>> sizes;
                            auto sizesEx = getArraySizes(sizes, symb, decl, arrayLinksByFuncCalls, allFuncInfo);
                            array->SetSizes(sizes);
                            array->SetSizesExpr(sizesEx);
                        }
                        else
                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }
                }
            }
        }
    }
}

bool isIntrinsic(const char *funName)
{
    if (intrinsicF.find(funName) == intrinsicF.end())
        return false;
    else
        return true;
}

static set<string> getPrivatesFromModule(SgStatement *mod, 
                                         const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                         const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                                         const map<string, SgStatement*> &modulesByName)
{
    set<string> privates;
    SgStatement *end = mod->lastNodeOfStmt();
    while (mod != end && mod->lineNumber() > 0)
    {
        if (mod->variant() == USE_STMT)
        {
            auto itF = modulesByName.find(mod->symbol()->identifier());
            if (itF == modulesByName.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            const set<string> recPrivates = getPrivatesFromModule(itF->second, declaratedArrays, declaratedArraysSt, modulesByName);
            for (auto it = recPrivates.begin(); it != recPrivates.end(); ++it)
                privates.insert(*it);
        }
        else
        {
            tryToFindPrivateInAttributes(mod, privates);
            fillNonDistrArraysAsPrivate(mod, declaratedArrays, declaratedArraysSt, privates);
        }
        mod = mod->lexNext();
    }
    return privates;
}

extern map<DIST::Array*, std::tuple<int, string, string>> tableOfUniqNamesByArray;
static void convertOneLoop(LoopGraph *currLoop, map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> &outInfo,
                           const map<SgSymbol*, ArrayInfo> &toConvert,
                           const set<string> &privateArrays,
                           const map<string, vector<SgExpression*>> &commonBlocks,
                           const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                           const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                           map<tuple<int, string, string>, DIST::Array*> &createdArrays,
                           bool freeArrays = false)
{
    map<DIST::Array*, const ArrayInfo*> toAdd;
    for (auto it1 = toConvert.begin(); it1 != toConvert.end(); ++it1)
    {
        SgSymbol *currentArray = OriginalSymbol(it1->first);
        const ArrayInfo *currentInfo = &(it1->second);
        
        DIST::Array *arrayToAdd;

        SgStatement *decl = declaratedInStmt(currentArray);
        const char *symbIdent = currentArray->identifier();

        if (privateArrays.find(symbIdent) == privateArrays.end())
        {
            const tuple<int, string, string> uniqKey = getUniqName(commonBlocks, decl, currentArray);

            auto itFound = createdArrays.find(uniqKey);
            if (itFound == createdArrays.end())
            {
                auto itArray = declaratedArrays.find(uniqKey);
                if (itArray == declaratedArrays.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                arrayToAdd = itArray->second.first;
                itFound = createdArrays.insert(itFound, make_pair(uniqKey, arrayToAdd));
            }
            else
                arrayToAdd = itFound->second;

            if (arrayToAdd->GetNonDistributeFlag() == true)
                continue;

            set<DIST::Array*> links;
            getRealArrayRefs(arrayToAdd, arrayToAdd, links, arrayLinksByFuncCalls);

            int countOflinks = 0;
            for (auto &linkedArray : links)
            {
                if (arrayToAdd == linkedArray)
                    continue;

                ++countOflinks;
                auto key = tableOfUniqNamesByArray[linkedArray];
                auto value = declaratedArrays.find(key)->second;
                if (value.second == 0 && createdArrays.find(key) == createdArrays.end())
                    createdArrays.insert(make_pair(key, linkedArray));
            }

            if (freeArrays)
                if (countOflinks == 0)
                    continue;

            toAdd[arrayToAdd] = currentInfo;

            for (int z = 0; z < currentInfo->dimSize; ++z)
            {
                if (currentInfo->readOps[z].coefficients.size() || currentInfo->writeOps[z].coefficients.size())
                {
                    arrayToAdd->SetMappedDim(z);

                    for (auto &realRef : links)
                        realRef->SetMappedDim(z);
                }
            }
        }
    }
    outInfo[currLoop] = toAdd;
}

static map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> 
       convertLoopInfo(const map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo,
                       const map<int, LoopGraph*> &sortedLoopGraph,
                       const set<string> &privateArrays,
                       const map<string, vector<SgExpression*>> &commonBlocks,
                       const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                       const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                       map<tuple<int, string, string>, DIST::Array*> &createdArrays)
{
    map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> outInfo;

    for (auto it = loopInfo.begin(); it != loopInfo.end(); ++it)
    {
        auto itGraph = sortedLoopGraph.find(it->first->lineNumber());
        if (itGraph == sortedLoopGraph.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        
        convertOneLoop(itGraph->second, outInfo, it->second, privateArrays, commonBlocks, declaratedArrays, arrayLinksByFuncCalls, createdArrays); 
    }

    return outInfo;
}

static inline void fillPrivatesFromDecl(SgExpression *ex, set<SgSymbol*> &delcsSymbViewed, set<SgStatement*> &delcsStatViewed,
                                        const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                        const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                                        set<string> &privatesVars)
{
    if (!ex)
        return;

    if (ex->variant() == ARRAY_REF)
    {
        SgSymbol *symb = ex->symbol();
        if (symb->type())
        {
            if (symb->type()->variant() == T_ARRAY)
            {
                SgSymbol *s = ex->symbol();
                auto it = delcsSymbViewed.find(s);
                if (it == delcsSymbViewed.end())
                {
                    delcsSymbViewed.insert(it, s);
                    SgStatement *decl = declaratedInStmt(s);

                    auto itD = delcsStatViewed.find(decl);
                    if (itD == delcsStatViewed.end())
                    {
                        delcsStatViewed.insert(itD, decl);
                        tryToFindPrivateInAttributes(decl, privatesVars);
                        fillNonDistrArraysAsPrivate(decl, declaratedArrays, declaratedArraysSt, privatesVars);
                    }
                }
            }
        }
    }

    fillPrivatesFromDecl(ex->rhs(), delcsSymbViewed, delcsStatViewed, declaratedArrays, declaratedArraysSt, privatesVars);
    fillPrivatesFromDecl(ex->lhs(), delcsSymbViewed, delcsStatViewed, declaratedArrays, declaratedArraysSt, privatesVars);
}

static void changeLoopWeight(double &currentWeight, const map<int, LoopGraph*> &sortedLoopGraph, const int line, bool increase = true)
{
    auto loopIt = sortedLoopGraph.find(line);
    if (loopIt == sortedLoopGraph.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (increase)
        currentWeight *= loopIt->second->countOfIters;
    else
        currentWeight /= loopIt->second->countOfIters;
}

static bool hasNonPureFunctions(SgExpression *ex, LoopGraph *loopRef, vector<Messages> &messagesForFile, const int line, const map<string, FuncInfo*> &funcByName)
{
    bool retVal = false;

    if (ex == NULL)
        return retVal;

    if (ex->variant() == FUNC_CALL)
    {
        if (isIntrinsicFunctionName(ex->symbol()->identifier()) == 0)
        {
            auto itF = funcByName.find(ex->symbol()->identifier());
            bool isPure = false; 
            if (itF != funcByName.end())
                isPure = itF->second->isPure;

            if (!isPure)
            {
                retVal = true;
                loopRef->hasNonPureProcedures = true;
#ifdef _WIN32
                messagesForFile.push_back(Messages(WARR, line, R79, L"Only pure procedures were supported", 1044));
#endif
            }
        }
    }
    bool retL = false, retR = false;
    if (ex->lhs())
        retL = hasNonPureFunctions(ex->lhs(), loopRef, messagesForFile, line, funcByName);
    if (ex->rhs())
        retR = hasNonPureFunctions(ex->rhs(), loopRef, messagesForFile, line, funcByName);

    return retVal || retL || retR;
}

static void fillFromModule(SgSymbol* s, const map<string, set<string>>& privatesByModule, set<string>& privates)
{
    if (s)
    {
        auto it = privatesByModule.find(s->identifier());
        if (it != privatesByModule.end())
            privates.insert(it->second.begin(), it->second.end());
    }
}

extern void createMapLoopGraph(map<int, LoopGraph*> &sortedLoopGraph, const std::vector<LoopGraph*> *loopGraph);

void loopAnalyzer(SgFile *file, vector<ParallelRegion*> &regions, map<tuple<int, string, string>, DIST::Array*> &createdArrays,
                  vector<Messages> &messagesForFile, REGIME regime, const map<string, vector<FuncInfo*>> &AllfuncInfo,
                  const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                  const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                  const map<SgStatement*, vector<DefUseList>> &defUseByPlace,
                  bool skipDeps, vector<LoopGraph*> *loopGraph)
{
    currMessages = &messagesForFile;
    currRegime = regime;

    map<string, vector<SgExpression*>> commonBlocks;
    map<int, LoopGraph*> sortedLoopGraph;
    map<int, pair<SgForStmt*, pair<set<string>, set<string>>>> allLoops;

    createMapLoopGraph(sortedLoopGraph, loopGraph);

    int funcNum = file->numberOfFunctions();
    __spf_print(PRINT_PROF_INFO,"functions num in file = %d\n", funcNum);

    vector<SgStatement*> modules;
    findModulesInFile(file, modules);

    map<string, SgStatement*> modulesByName;
    for (int i = 0; i < modules.size(); ++i)
        modulesByName[modules[i]->symbol()->identifier()] = modules[i];

    map<string, set<string>> privatesByModule;
    for (int i = 0; i < modules.size(); ++i)
        privatesByModule[modules[i]->symbol()->identifier()] = getPrivatesFromModule(modules[i], declaratedArrays, declaratedArraysSt, modulesByName);

    map<string, FuncInfo*> funcByName;
    createMapOfFunc(AllfuncInfo, funcByName);

    const vector<FuncInfo*> &funcInfo = AllfuncInfo.find(file->filename())->second;

    for (int i = 0; i < funcNum; ++i)
    {
#if _WIN32 && NDEBUG
        createNeededException();
#endif
#ifdef _WIN32
        string fName = file->functions(i)->symbol()->identifier();
        if (file->functions(i)->variant() != MODULE_STMT)
            sendMessage_2lvl(wstring(L"обработка функции '") + wstring(fName.begin(), fName.end()) + L"'");
        else
            sendMessage_2lvl(wstring(L"обработка модуля '") + wstring(fName.begin(), fName.end()) + L"'");
#endif
        set<SgSymbol*> delcsSymbViewed;
        set<SgStatement*> delcsStatViewed;

        if (funcInfo[i]->doNotAnalyze)
            continue;

        map<SgForStmt*, map<SgSymbol*, ArrayInfo>> loopInfo;
        set<int> loopWithOutArrays;

        set<string> privatesVars;

        SgStatement *st = file->functions(i);
        string funcName = "";
        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
            __spf_print(PRINT_PROF_INFO, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
            funcName = progH->symbol()->identifier();
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
            __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
            funcName = procH->symbol()->identifier();
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
            __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), st->lineNumber(), st->fileName());
            funcName = funcH->symbol()->identifier();
        }

        SgStatement* tmpModFind = st;
        while (tmpModFind->variant() != GLOBAL)
        {
            tmpModFind = tmpModFind->controlParent();
            if (tmpModFind->variant() == MODULE_STMT)
                fillFromModule(tmpModFind->symbol(), privatesByModule, privatesVars);
        }
        commonBlocks.clear();
        getCommonBlocksRef(commonBlocks, st, st->lastNodeOfStmt());
        __spf_print(PRINT_PROF_INFO, "  number of common blocks %d\n", (int)commonBlocks.size());

        SgStatement *lastNode = st->lastNodeOfStmt();
        vector<SgForStmt*> parentLoops;
        vector<set<string>> privatesVarsForLoop;

        //For remote access
        pair<SgForStmt*, LoopGraph*> *under_dvm_dir = NULL;
        map<string, SgArrayRefExp*> uniqRemotes;

        map<string, pair<SgSymbol*, SgStatement*>> notMappedDistributedArrays;
        set<string> mappedDistrbutedArrays;

        double currentWeight = 1.0;
        while (st != lastNode)
        {
            currProcessing.second = st->lineNumber();
#if _WIN32 && NDEBUG
            createNeededException();
#endif
            if (st == NULL)
            {
#if _WIN32
                currMessages->push_back(Messages(ERROR, 1, R128, L"internal error in analysis, parallel directives will not be generated for this file!", 3008));
#endif
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            if (!__gcov_doesThisLineExecuted(st->fileName(), st->lineNumber()))
            {
                st = st->lexNext();
                continue;
            }

            const int currentLine = st->lineNumber() < -1 ? st->localLineNumber() : st->lineNumber();
            ParallelRegion *currReg = getRegionByLine(regions, st->fileName(), currentLine);
            if (currReg == NULL)
            {
                st = st->lexNext();
                continue;
            }

            if (isSgExecutableStatement(st) == NULL)
                delcsStatViewed.insert(st);
            else if (!isDVM_stat(st) && !isSPF_stat(st))
                for (int i = 0; i < 3; ++i)
                    fillPrivatesFromDecl(st->expr(i), delcsSymbViewed, delcsStatViewed, declaratedArrays, declaratedArraysSt, privatesVars);

            //printf("new st with var = %d, on line %d\n", st->variant(), st->lineNumber());
            const int currV = st->variant();
            if (currV == FOR_NODE)
            {
                tryToFindPrivateInAttributes(st, privatesVars);
                fillNonDistrArraysAsPrivate(st, declaratedArrays, declaratedArraysSt, privatesVars);
                                
                set<string> toAdd;
                tryToFindPrivateInAttributes(st, toAdd);

                if (PRINT_LOOP_STRUCT)
                    printBlanks(2, (int)parentLoops.size());
                __spf_print(PRINT_LOOP_STRUCT, "FOR NODE on line %d\n", st->lineNumber());

                parentLoops.push_back((SgForStmt*)st);
                changeLoopWeight(currentWeight, sortedLoopGraph, st->lineNumber());                
                privatesVarsForLoop.push_back(toAdd);

                if (regime == REMOTE_ACC)
                {
                    SgStatement *prev = st->lexPrev();
                    if (prev)
                    {
                        if (prev->variant() == DVM_PARALLEL_ON_DIR)
                        {
                            auto it = sortedLoopGraph.find(st->lineNumber());
                            if (it == sortedLoopGraph.end())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            under_dvm_dir = new pair<SgForStmt*, LoopGraph*>((SgForStmt*)st, it->second);
                        }
                    }
                }
            }
            else if (currV == CONTROL_END)
            {
                SgStatement *contrlParent = st->controlParent();
                if (contrlParent)
                {
                    if (contrlParent->variant() == FOR_NODE)
                    {
                        changeLoopWeight(currentWeight, sortedLoopGraph, contrlParent->lineNumber(), false);

                        if (parallizeFreeLoops)
                            if (loopInfo.find((SgForStmt*)contrlParent) == loopInfo.end() && !sortedLoopGraph[contrlParent->lineNumber()]->hasUnknownDistributedMap)
                                loopWithOutArrays.insert(contrlParent->lineNumber());

                        set<string> unitedPrivates;
                        for (int p = 0; p < parentLoops.size(); ++p)
                            for (auto &privVar : privatesVarsForLoop[p])
                                unitedPrivates.insert(privVar);
                        
                        set<string> setDiff;
                        for (auto &privVars : privatesVars)
                            if (unitedPrivates.find(privVars) == unitedPrivates.end())
                                setDiff.insert(privVars);                        

                        allLoops[contrlParent->lineNumber()] = make_pair((SgForStmt*)contrlParent, make_pair(unitedPrivates, setDiff));
                        parentLoops.pop_back();
                        privatesVarsForLoop.pop_back();

                        if (regime == REMOTE_ACC)
                        {
                            if (under_dvm_dir)
                            {
                                if (contrlParent == under_dvm_dir->first && under_dvm_dir->second->userDvmDirective == NULL)
                                {
                                    ParallelRegion *currReg = getRegionByLine(regions, under_dvm_dir->first->fileName(), under_dvm_dir->first->lineNumber());
                                    if (currReg)
                                    {
                                        const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();
                                        DIST::GraphCSR<int, double, attrType> &reducedG = currReg->GetReducedGraphToModify();
                                        const DataDirective &data = currReg->GetDataDir();
                                        const vector<int> &currVar = currReg->GetCurrentVariant();

                                        tuple<SgForStmt*, const LoopGraph*, const ParallelDirective*> currDir
                                            = make_tuple(under_dvm_dir->first, under_dvm_dir->second, under_dvm_dir->second->directive);

                                        createRemoteInParallel(currDir, allArrays, loopInfo, reducedG, data, currVar, allLoops, uniqRemotes, messagesForFile, currReg->GetId(), arrayLinksByFuncCalls);
                                        addRemotesToDir(under_dvm_dir, uniqRemotes);
                                    }

                                    delete under_dvm_dir;
                                    under_dvm_dir = NULL;
                                    uniqRemotes.clear();
                                }
                            }
                        }
                    }
                }
                else
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            else if (currV == ASSIGN_STAT)
            {
                if (st->expr(0))
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), LEFT, loopInfo, st->lineNumber(), privatesVars, 
                                 sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                 mappedDistrbutedArrays, st, currReg, currentWeight, arrayLinksByFuncCalls);
                if (st->expr(1))
                    findArrayRef(parentLoops, st->expr(1), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars,
                                 sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                 mappedDistrbutedArrays, st, currReg, currentWeight, arrayLinksByFuncCalls);

                if (regime == REMOTE_ACC)
                {
                    if (st->expr(1))
                    {
                        bool cond = true;
                        if (st->expr(1)->variant() == FUNC_CALL)
                            cond = isIntrinsic(((SgFunctionCallExp*)st->expr(1))->funName()->identifier());

                        // detect copy operator: A(:, :, :) = B(:, :, :)
                        if (st->expr(1)->variant() == ARRAY_REF && st->expr(0)->variant() == ARRAY_REF)
                        {
                            set<SgSymbol*> ddots;
                            vector<SgExpression*> dummy;
                            fillVars(st->expr(0), { DDOT }, ddots, dummy);
                            fillVars(st->expr(1), { DDOT }, ddots, dummy);

                            if (ddots.size() != 0)
                                cond = false;
                        }

                        // detect copy operator: A = B
                        if (st->expr(1)->variant() == ARRAY_REF && st->expr(0)->variant() == ARRAY_REF)
                        {
                            SgExpression *left = st->expr(0);
                            SgExpression *right = st->expr(1);
                            if (left->lhs() == NULL && left->rhs() == NULL &&
                                right->lhs() == NULL && right->rhs() == NULL)
                                cond = false;
                        }

                        // detect operator: A[(:,:,:)] = F(X[(:,:,:)], Y[(:,:,:)], Z[(:,:,:)], ...)
                        //TODO: check right part
                        if (st->expr(0)->variant() == ARRAY_REF)
                        {
                            SgExpression *left = st->expr(0);
                            set<SgSymbol*> ddots;
                            vector<SgExpression*> dummy;
                            fillVars(st->expr(0), { DDOT }, ddots, dummy);

                            if ((left->lhs() == NULL && left->rhs() == NULL ) || ddots.size() != 0)
                                cond = false;
                        }

                        if (cond)
                        {
                            const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();
                            if (under_dvm_dir == NULL)
                                createRemoteDir<1>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages, arrayLinksByFuncCalls);
                        }
                    }
                }
            }
            else if (currV == IF_NODE || currV == ELSEIF_NODE || currV == LOGIF_NODE || currV == SWITCH_NODE)
            {
                if (st->expr(0))
                {
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, 
                                 sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                 mappedDistrbutedArrays, st, currReg, currentWeight, arrayLinksByFuncCalls);
                    if (regime == REMOTE_ACC)
                    {
                        const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();

                        if (under_dvm_dir == NULL)
                            createRemoteDir<0>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages, arrayLinksByFuncCalls);
                    }
                }
            }
            else if (currV == PROC_STAT)
            {
                auto func = isUserFunctionInProject(st->symbol()->identifier());
                if (func != NULL)
                {
                    SgExpression *parList = st->expr(0);
                    set<DIST::Array*> toRedistr;
                    if (parList)
                    {
                        SgExprListExp *list = isSgExprListExp(parList);
                        for (int z = 0; z < list->length(); ++z)
                        {
                            SgExpression *par = list->elem(z);
                            if ((func->funcParams.inout_types[z] & OUT_BIT) != 0)
                                findArrayRef(parentLoops, par, st->lineNumber(), LEFT, loopInfo, st->lineNumber(), privatesVars, 
                                             sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                             mappedDistrbutedArrays, st, currReg, currentWeight, arrayLinksByFuncCalls);
                            else
                                findArrayRef(parentLoops, par, st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, 
                                             sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                             mappedDistrbutedArrays, st, currReg, currentWeight, arrayLinksByFuncCalls);

                            if (regime == REMOTE_ACC)
                            {
                                if (par->variant() == ARRAY_REF && isPassFullArray(par))
                                {
                                    SgSymbol *s = OriginalSymbol(par->symbol());
                                    DIST::Array *inPar = getArrayFromDeclarated(declaratedInStmt(s), s->identifier());
                                    if (inPar && !inPar->GetNonDistributeFlag())
                                    {
                                        if (func->funcParams.parametersT[z] != ARRAY_T)
                                            toRedistr.insert(inPar->GetTemplateArray(currReg->GetId()));
                                        else
                                        {
                                            if (inPar->GetDimSize() != ((DIST::Array*)func->funcParams.parameters[z])->GetDimSize())
                                                toRedistr.insert(inPar->GetTemplateArray(currReg->GetId()));
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (regime == REMOTE_ACC)
                    {
                        const DataDirective &dataDirectives = currReg->GetDataDir();
                        const vector<int> &currentVariant = currReg->GetCurrentVariant();
                        auto &tmp = dataDirectives.distrRules;
                        std::vector<std::pair<DIST::Array*, const DistrVariant*>> currentVar;
                        for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                            currentVar.push_back(make_pair(tmp[z1].first, &tmp[z1].second[currentVariant[z1]]));

                        for (auto &toRed : toRedistr)
                        {
                            auto cp = st->controlParent();
                            auto redist = new SgStatement(DVM_REDISTRIBUTE_DIR);
                            auto newRule = new SgExprListExp();
                            newRule->setLhs(*new SgExpression(KEYWORD_VAL, "*"));
                            for (int z = 1; z < toRed->GetDimSize(); ++z)
                                newRule->append(*new SgExpression(KEYWORD_VAL, "*"));
                            auto templS = new SgSymbol(VARIABLE_NAME, toRed->GetShortName().c_str());
                            redist->setExpression(0, *new SgVarRefExp(*templS));
                            redist->setExpression(1, *newRule);

                            st->insertStmtBefore(*redist, *cp);
                            
                            redist = new SgStatement(DVM_REDISTRIBUTE_DIR);
                            newRule = new SgExprListExp();
                            
                            const DistrVariant *varD = NULL;
                            for (auto &elem : currentVar)
                            {
                                if (elem.first == toRed)
                                {
                                    varD = elem.second;
                                    break;
                                }
                            }

                            if (!varD)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            for (int z = 0; z < toRed->GetDimSize(); ++z)
                            {
                                char *type = "*";
                                if (varD->distRule[z] == distType::BLOCK)
                                    type = "BLOCK";

                                if (z == 0)
                                    newRule->setLhs(*new SgExpression(KEYWORD_VAL, type));
                                else
                                    newRule->append(*new SgExpression(KEYWORD_VAL, type));
                            }
                            redist->setExpression(0, *new SgVarRefExp(*templS));
                            redist->setExpression(1, *newRule);

                            st->insertStmtAfter(*redist, *cp);
                        }
                    }
                }
            }
            else if (currV == USE_STMT)
            {
                auto itF = privatesByModule.find(st->symbol()->identifier());
                if (itF == privatesByModule.end())
                {
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"Module with name '%s' must be placed in current file", to_wstring(st->symbol()->identifier()).c_str());
#ifdef _WIN32
                    __spf_printToLongBuf(messageR, R62, to_wstring(st->symbol()->identifier()).c_str());
#endif
                    currMessages->push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1028));

                    __spf_print(1, "Module at line %d with name '%s' must be placed in current file\n", st->lineNumber(), st->symbol()->identifier());
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                for (auto it = itF->second.begin(); it != itF->second.end(); ++it)
                    privatesVars.insert(*it);
            }
            else
            {
                tryToFindPrivateInAttributes(st, privatesVars);
                fillNonDistrArraysAsPrivate(st, declaratedArrays, declaratedArraysSt, privatesVars);

                if (isDVM_stat(st) == false && isSgExecutableStatement(st))
                {
                    if (regime == REMOTE_ACC)
                    {
                        if (isSgExecutableStatement(st) && st->expr(0) &&
                            (currV == SWITCH_NODE || currV == FORALL_STAT || currV == WHILE_NODE ||
                                currV == WHERE_NODE || currV == ALLDO_NODE || currV == ARITHIF_NODE ||
                                currV == ASSGOTO_NODE || currV == COMGOTO_NODE))
                        {
                            const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();
                            if (under_dvm_dir == NULL)
                                createRemoteDir<0>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages, arrayLinksByFuncCalls);
                        }
                    }
                    else
                    {
                        int const var = st->variant();
                        int side = (var == READ_STAT || var == WRITE_STAT || var == PRINT_STAT) ? LEFT : RIGHT;

                        for (int z = 0; z < 3; ++z)
                            if (st->expr(z))
                                findArrayRef(parentLoops, st->expr(z), st->lineNumber(), side, loopInfo, st->lineNumber(), privatesVars, 
                                             sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays,
                                             mappedDistrbutedArrays, st, currReg, currentWeight, arrayLinksByFuncCalls);
                    }
                }
            }

            st = st->lexNext();
        }
        
        auto convertedLoopInfo = convertLoopInfo(loopInfo, sortedLoopGraph, privatesVars, commonBlocks, declaratedArrays, arrayLinksByFuncCalls, createdArrays);
        if (regime == DATA_DISTR)
        {
            processLoopInformationForFunction(convertedLoopInfo);

            //find dependencies for loops in function
            initAnnotationsSysExt(0);
            set<SgStatement*> funcWasInit;
            map<SgExpression*, string> collection;

            int idx = 0;
            for (auto &loop : convertedLoopInfo)
            {
                ++idx;
#if _WIN32 && NDEBUG
                createNeededException();
#endif

                if (!skipDeps)
                {
#ifdef _WIN32
                    string fName = file->functions(i)->symbol()->identifier();
                    sendMessage_2lvl(wstring(L"обработка цикла ") + std::to_wstring(idx) + L"/" + std::to_wstring(convertedLoopInfo.size()));
#endif
                    tryToFindDependencies(loop.first, allLoops, funcWasInit, file, regions, currMessages, collection, funcByName, defUseByPlace);
                }
            }

            vector<LoopGraph*> tmpLoops;
            if (file->functions(i)->variant() != PROG_HEDR)
            {
                for (auto &notMapped : notMappedDistributedArrays)
                {
                    if (mappedDistrbutedArrays.find(notMapped.first) == mappedDistrbutedArrays.end())
                    {
                        auto reg = getRegionByLine(regions, notMapped.second.second->fileName(), notMapped.second.second->lineNumber());
                        if (reg)
                        {
                            LoopGraph *tmpLoop = new LoopGraph();

                            tmpLoop->region = reg;
                            tmpLoops.push_back(tmpLoop);

                            map<SgSymbol*, ArrayInfo> toConvert;

                            ArrayInfo toAdd;
                            SgSymbol *arrayS = notMapped.second.first;
                            toAdd.dimSize = ((SgArrayType*)arrayS->type())->dimension();
                            
                            for (int z = 0; z < toAdd.dimSize; ++z)
                                toAdd.readOps.push_back(ArrayOp(make_pair(make_pair(1, 0), 1.0)));
                            
                            toConvert[arrayS] = toAdd;
                            convertOneLoop(tmpLoop, convertedLoopInfo, toConvert, privatesVars, commonBlocks, declaratedArrays, arrayLinksByFuncCalls, createdArrays, true);
                        }
                    }
                }
            }

            addToDistributionGraph(convertedLoopInfo, arrayLinksByFuncCalls);

            for (auto &toDel : tmpLoops)
                delete toDel;

            if (!skipDeps)
            {

                for (auto &loopLine : loopWithOutArrays)
                {
                    if (loopLine > 0)
                    {
                        tryToFindDependencies(sortedLoopGraph[loopLine], allLoops, funcWasInit, file, regions, currMessages, collection, funcByName, defUseByPlace);
                        sortedLoopGraph[loopLine]->withoutDistributedArrays = true;
                    }
                }

                //only top loop may be parallel
                for (auto &loopLine : loopWithOutArrays)
                {
                    auto loopRef = sortedLoopGraph[loopLine];
                    loopRef->setWithOutDistrFlagToFalse();

                    SgForStmt *forSt = (SgForStmt*)(loopRef->loop);
                    SgStatement *cp = forSt->controlParent();
                    while (cp)
                    {
                        if (cp->variant() == FOR_NODE)
                        {
                            auto cpLoopRef = sortedLoopGraph[cp->lineNumber()];
                            if (!cpLoopRef->hasLimitsToParallel())
                                cpLoopRef->setWithOutDistrFlagToFalse();
                        }
                        cp = cp->controlParent();
                    }
                }

                // TODO: add messages!
                for (auto &loopLine : loopWithOutArrays)
                {
                    if (sortedLoopGraph[loopLine]->withoutDistributedArrays && loopLine > 0)
                    {
                        //TODO: enable linear writes to non distr arrays for CONSISTENT
                        bool hasWritesToArray = false;
                        //TODO: add IPA for non pure
                        bool hasNonPureProcedures = false;

                        auto loopRef = sortedLoopGraph[loopLine];
                        SgStatement *loopSt = loopRef->loop;

                        map<string, set<string>> reductions;
                        map<string, set<tuple<string, string, int>>> reductionsLoc;
                        set<string> privates;
                        for (auto &data : getAttributes<SgStatement*, SgStatement*>(loopSt, set<int>{ SPF_ANALYSIS_DIR, SPF_PARALLEL_DIR }))
                        {
                            Statement *dataSt = new Statement(data);
                            fillReductionsFromComment(dataSt, reductions);
                            fillReductionsFromComment(dataSt, reductionsLoc);
                            fillPrivatesFromComment(dataSt, privates);
                        }
                        for (auto &red : reductions)
                            privates.insert(red.second.begin(), red.second.end());
                        for (auto &red : reductionsLoc)
                        {
                            for (auto &elem : red.second)
                            {
                                privates.insert(get<0>(elem));
                                privates.insert(get<1>(elem));
                            }
                        }

                        for (SgStatement *start = loopSt->lexNext(); start != loopSt->lastNodeOfStmt(); start = start->lexNext())
                        {
                            //TODO: detect write in proc calls
                            if (start->variant() == ASSIGN_STAT)
                            {
                                if (start->expr(0)->variant() == ARRAY_REF)
                                    if (privates.find(start->expr(0)->symbol()->identifier()) == privates.end())
                                        if (mpiProgram == 0)
                                            hasWritesToArray = true;
                            }

                            if (start->variant() == PROC_STAT && isIntrinsicFunctionName(start->symbol()->identifier()) == 0)
                            {
                                checkNull(isSgCallStmt(start), convertFileName(__FILE__).c_str(), __LINE__);

                                auto itF = funcByName.find(isSgCallStmt(start)->name()->identifier());
                                bool isPure = false;
                                if (itF != funcByName.end())
                                    isPure = itF->second->isPure;

                                if (!isPure)
                                {
                                    hasNonPureProcedures = true;
                                    loopRef->hasNonPureProcedures = true;
#ifdef _WIN32
                                    messagesForFile.push_back(Messages(WARR, start->lineNumber(), R80, L"Only pure procedures were supported", 1044));
#endif
                                }
                            }

                            for (int z = 1; z < 3; ++z)
                                if (hasNonPureFunctions(start->expr(z), loopRef, messagesForFile, start->lineNumber(), funcByName))
                                    hasNonPureProcedures = true;
                        }

                        if (!hasWritesToArray && !hasNonPureProcedures)
                        {
                            if (!addToDistributionGraph(loopRef, funcName))
                                loopRef->withoutDistributedArrays = false;
                        }
                        else
                            loopRef->withoutDistributedArrays = false;
                    }
                }
            }
#ifdef _WIN32
            sendMessage_2lvl(L"");
#endif
        }
        else if (regime == COMP_DISTR)
        {
            createParallelDirectives(convertedLoopInfo, regions, sortedLoopGraph, arrayLinksByFuncCalls, messagesForFile);

            for (auto &loopLine : loopWithOutArrays)
            {
                auto loopRef = sortedLoopGraph[loopLine];
                if (loopRef->withoutDistributedArrays && loopRef->region && !loopRef->hasLimitsToParallel() && loopLine > 0)
                {
                    auto region = loopRef->region;
                    auto allArrays = region->GetAllArrays();

                    string fullLoopName = loopRef->genLoopArrayName(funcName);
                    auto loopArray = allArrays.GetArrayByName(fullLoopName);
                    
                    ArrayInfo tmpArrayInfo;
                    tmpArrayInfo.dimSize = 1;

                    ArrayOp tmpOp(make_pair(make_pair(1, 0), 1.0));
                    tmpArrayInfo.writeOps.push_back(tmpOp);
                    tmpArrayInfo.readOps.push_back(ArrayOp());
                    map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> convertedLoopInfo;

                    map<DIST::Array*, const ArrayInfo*> tmpAdd;
                    tmpAdd.insert(make_pair(loopArray, &tmpArrayInfo));
                    convertedLoopInfo.insert(make_pair(loopRef, tmpAdd));

                    createParallelDirectives(convertedLoopInfo, regions, sortedLoopGraph, map<DIST::Array*, set<DIST::Array*>>(), messagesForFile);
                }
            }
        }

        __spf_print(PRINT_PROF_INFO, "Function ended\n");
    }
}

void arrayAccessAnalyzer(SgFile *file, vector<Messages> &messagesForFile, const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays, REGIME regime)
{
    currMessages = &messagesForFile;
    currRegime = regime;

    map<string, vector<SgExpression*>> commonBlocks;
    map<int, LoopGraph*> sortedLoopGraph;
    map<int, pair<SgForStmt*, pair<set<string>, set<string>>>> allLoops;
    map<string, pair<SgSymbol*, SgStatement*>> notMappedDistributedArrays;
    set<string> mappedDistrbutedArrays;

    int funcNum = file->numberOfFunctions();
    __spf_print(PRINT_PROF_INFO, "functions num in file = %d\n", funcNum);

    const map<DIST::Array*, set<DIST::Array*>> arrayLinksByFuncCalls;
    for (int i = 0; i < funcNum; ++i)
    {
        map<SgForStmt*, map<SgSymbol*, ArrayInfo>> loopInfo;
        set<string> privatesVars;

        SgStatement *st = file->functions(i);
        string funcName = "";
        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
            __spf_print(PRINT_PROF_INFO, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
            funcName = progH->symbol()->identifier();
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
            __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
            funcName = procH->symbol()->identifier();
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
            __spf_print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), st->lineNumber(), st->fileName());
            funcName = funcH->symbol()->identifier();
        }

        commonBlocks.clear();
        getCommonBlocksRef(commonBlocks, st, st->lastNodeOfStmt());
        __spf_print(PRINT_PROF_INFO, "  number of common blocks %d\n", (int)commonBlocks.size());

        SgStatement *lastNode = st->lastNodeOfStmt();
        vector<SgForStmt*> parentLoops;
                
        double currentWeight = 1.0;
        while (st != lastNode)
        {
            currProcessing.second = st->lineNumber();
#if _WIN32 && NDEBUG
            createNeededException();
#endif
            if (st == NULL)
            {
#ifdef _WIN32
                currMessages->push_back(Messages(ERROR, 1, R128, L"internal error in analysis, parallel directives will not be generated for this file!", 3008));
#endif
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            const int currV = st->variant();
            if (currV == FOR_NODE)
            {
                if (PRINT_LOOP_STRUCT)
                    printBlanks(2, (int)parentLoops.size());
                __spf_print(PRINT_LOOP_STRUCT, "FOR NODE on line %d\n", st->lineNumber());

                parentLoops.push_back((SgForStmt*)st);
                sortedLoopGraph[st->lineNumber()] = new LoopGraph();
            }
            else if (currV == CONTROL_END)
            {
                SgStatement *contrlParent = st->controlParent();
                if (contrlParent)
                {
                    if (contrlParent->variant() == FOR_NODE)
                    {
                        parentLoops.pop_back();
                        delete sortedLoopGraph[contrlParent->lineNumber()];
                        sortedLoopGraph.erase(contrlParent->lineNumber());
                    }
                }
                else
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            else if (currV == ASSIGN_STAT)
            {
                if (st->expr(0))
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), LEFT, loopInfo, st->lineNumber(), privatesVars, 
                                 sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                 mappedDistrbutedArrays, st, NULL, currentWeight, arrayLinksByFuncCalls);
                if (st->expr(1))
                    findArrayRef(parentLoops, st->expr(1), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars,
                                 sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                 mappedDistrbutedArrays, st, NULL, currentWeight, arrayLinksByFuncCalls);
            }
            else if (currV == IF_NODE || currV == ELSEIF_NODE || currV == LOGIF_NODE || currV == SWITCH_NODE)
            {
                if (st->expr(0))
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, 
                                 sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays,
                                 mappedDistrbutedArrays, st, NULL, currentWeight, arrayLinksByFuncCalls);
            }
            else if (currV == PROC_STAT)
            {
                if (st->expr(0))
                {
                    if (isIntrinsicFunctionName(st->symbol()->identifier()))
                        findArrayRef(parentLoops, st->expr(0), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, 
                                     sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, 
                                     mappedDistrbutedArrays, st, NULL, currentWeight, arrayLinksByFuncCalls);
                    else
                    {
                        SgExpression *listEx = st->expr(0);
                        while (listEx)
                        {
                            findArrayRef(parentLoops, listEx->lhs(), st->lineNumber(), LEFT, loopInfo, st->lineNumber(), privatesVars,
                                         sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays,
                                         mappedDistrbutedArrays, st, NULL, currentWeight, arrayLinksByFuncCalls);
                            listEx = listEx->rhs();
                        }
                    }
                }
            }
            st = st->lexNext();
        }
        __spf_print(PRINT_PROF_INFO, "Function ended\n");
    }
}

//TODO: copy all functions from FDVM and fix them
static inline int getStructureSize(SgSymbol *s)
{
    return 0;
    //printInternalError(convertFileName(__FILE__).c_str(), __LINE__);       
}

static inline int getNumericTypeLength(SgType *t)
{
    SgExpression *le;
    SgValueExp *ve;
    if (t->variant() == T_STRING)  
        return (0);

    if (TYPE_RANGES(t->thetype)) 
    {
        le = t->length();
        if (ve = isSgValueExp(le))
            return ve->intValue();
        else
            return 0;
    }

    if (TYPE_KIND_LEN(t->thetype)) 
    {
        le = t->selector()->lhs();
        if (ve = isSgValueExp(le))
            if (t->variant() == T_COMPLEX || t->variant() == T_DCOMPLEX)
                return 2 * ve->intValue();
            else
                return ve->intValue();
        else
            return 0;
    }

    return 0;
}

static inline int getIntrinsicTypeSize(SgType *t)
{
    const int default_real_size = 4;
    const int default_integer_size = 4;
    switch (t->variant()) 
    {
    case T_INT:
    case T_BOOL:     
        return default_integer_size;
    case T_FLOAT:    
        return default_real_size;
    case T_COMPLEX: 
        return 2 * default_real_size;
    case T_DOUBLE:
        return 2 * default_real_size;
    case T_DCOMPLEX: 
        return 4 * default_real_size;
    case T_STRING:
    case T_CHAR:
        return 1;
    default:
        return 0;
    }
}

static SgExpression* getLengthOfKindExpr(SgType *t, SgExpression *se, SgExpression *le)
{
    switch (t->variant())
    {
    case T_INT:
    case T_FLOAT:
    case T_BOOL:
    case T_DOUBLE:
        return se->lhs();
    case T_COMPLEX:
    case T_DCOMPLEX:
        return &(*new SgValueExp(2) * (*(se->lhs())));
    case T_CHAR:
    case T_STRING:
    {
        SgExpression *length, *kind;
        if (se->rhs() && se->rhs()->variant() == LENGTH_OP)
        {
            length = se->rhs()->lhs();
            kind = se->lhs()->lhs();
        }
        else if (se->rhs() && se->rhs()->variant() != LENGTH_OP)
        {
            length = se->lhs()->lhs();
            kind = se->rhs()->lhs();
        }
        else
        {
            length = se->lhs();
            kind = NULL;
        }
        length = le ? le : length;
        if (kind)
            return &(*length * (*kind));
        else
            return length;
    }
    default:
        return(NULL);
    }
}

static SgExpression* getTypeLengthExpr(SgType *t)
{
    SgExpression *len;
    SgExpression *selector;
    if (t->variant() == T_DERIVED_TYPE)
        return new SgValueExp(getStructureSize(t->symbol()));

    len = TYPE_RANGES(t->thetype) ? t->length() : NULL;
    selector = TYPE_KIND_LEN(t->thetype) ? t->selector() : NULL;

    if (!len && !selector) //the number of bytes is not specified in type declaration statement
        return (new SgValueExp(getIntrinsicTypeSize(t)));
    else if (len && !selector)   //INTEGER*2,REAL*8,CHARACTER*(N+1)
        return CalculateInteger(len);
    else
        return CalculateInteger(getLengthOfKindExpr(t, selector, len)); //specified kind or/and len
}

int getSizeOfType(SgType *t)
{
    int len = -1;
    if (IS_INTRINSIC_TYPE(t))
        return getIntrinsicTypeSize(t);
    if (t->variant() == T_DERIVED_TYPE)  
        return getStructureSize(t->symbol());
    if (len = getNumericTypeLength(t))
        return len;

    SgExpression *le = getTypeLengthExpr(t);
    if (le->isInteger()) 
    {
        len = le->valueInteger();
        len = len < 0 ? 0 : len; //according to standard F90
    }
    else
        len = -1; //may be error situation
    return len;
}

static void findArrayRefs(SgExpression *ex, SgStatement *st,
                          const map<string, vector<SgExpression*>> &commonBlocks,
                          const vector<SgStatement*> &modules,
                          map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                          map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                          const set<string> &privates, const set<string> &deprecatedByIO, 
                          bool isExecutable, const string &currFunctionName, bool isWrite,
                          const vector<string> &inRegion,
                          const set<string> &funcParNames)
{
    if (ex == NULL)
        return;

    if (ex->variant() == ARRAY_REF)
    {
        SgSymbol *symb = OriginalSymbol(ex->symbol());

        if (symb->type())
        {
            if (symb->type()->variant() == T_ARRAY)
            {
                const int typeSize = getSizeOfType(symb->type()->baseType());
                if (typeSize == 0)
                {
                    //__spf_print(1, "Wrong type size for array %s\n", symb->identifier());
                    //printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
                
                SgStatement *decl = declaratedInStmt(symb);
                if (decl->variant() == DVM_VAR_DECL || decl->variant() == HPF_TEMPLATE_STAT)
                {
                    const string tmp(decl->unparse());
                    if (tmp.find("!DVM$ TEMPLATE") != string::npos)
                    {
                        auto sTemp = symb->identifier();
                        tuple<int, string, string> uniqKey;
                        bool found = false;
                        for (auto& elem : declaratedArrays)
                        {
                            if (elem.second.first->GetShortName() == sTemp)
                            {
                                uniqKey = elem.first;
                                found = true;
                            }
                        }

                        if (found)
                        {
                            auto itDecl = declaratedArraysSt.find(decl);
                            if (itDecl == declaratedArraysSt.end())
                                itDecl = declaratedArraysSt.insert(itDecl, make_pair(decl, set<tuple<int, string, string>>()));
                            itDecl->second.insert(uniqKey);

                            return;
                        }
                    }
                }

                auto uniqKey = getUniqName(commonBlocks, decl, symb);
                pair<DIST::arrayLocType, string> arrayLocation;
                SgStatement *scope = symb->scope();

                if (symb != ex->symbol() || (scope && scope->variant() == MODULE_STMT))
                {
                    if (scope)
                        arrayLocation = make_pair(DIST::l_MODULE, scope->symbol()->identifier());
                    else //TODO: find module name with another way
                        arrayLocation = make_pair(DIST::l_MODULE, "UNREC_MODULE_NAME");
                }
                else if (get<1>(uniqKey).find("common_") != string::npos)
                    arrayLocation = make_pair(DIST::l_COMMON, get<1>(uniqKey).substr(strlen("common_")));
                else if (funcParNames.find(symb->identifier()) != funcParNames.end())
                    arrayLocation = make_pair(DIST::l_PARAMETER, currFunctionName);
                else
                    arrayLocation = make_pair(DIST::l_LOCAL, currFunctionName);

                auto itNew = declaratedArrays.find(uniqKey);
                if (itNew == declaratedArrays.end())
                {
                    DIST::Array *arrayToAdd = 
                        new DIST::Array(getShortName(uniqKey), symb->identifier(), ((SgArrayType*)(symb->type()))->dimension(), 
                                        getUniqArrayId(), decl->fileName(), decl->lineNumber(), arrayLocation, new Symbol(symb),
                                        inRegion, typeSize);

                    itNew = declaratedArrays.insert(itNew, make_pair(uniqKey, make_pair(arrayToAdd, new DIST::ArrayAccessInfo())));

                    vector<pair<int, int>> sizes; 
                    map<DIST::Array*, set<DIST::Array*>> arrayLinksByFuncCallsNotReady;
                    map<string, vector<FuncInfo*>> allFuncInfoNoReady;
                    auto sizesExpr = getArraySizes(sizes, symb, decl, arrayLinksByFuncCallsNotReady, allFuncInfoNoReady);
                    arrayToAdd->SetSizes(sizes);
                    arrayToAdd->SetSizesExpr(sizesExpr);                    
                    tableOfUniqNamesByArray[arrayToAdd] = uniqKey;
                }

                for (auto &reg : inRegion)
                    itNew->second.first->SetRegionPlace(reg);

                const auto oldVal = itNew->second.first->GetNonDistributeFlagVal();
                if (oldVal == DIST::DISTR || oldVal == DIST::NO_DISTR)
                {
                    if (privates.find(symb->identifier()) != privates.end())
                        itNew->second.first->SetNonDistributeFlag(DIST::SPF_PRIV);
                    else if (deprecatedByIO.find(symb->identifier()) != deprecatedByIO.end())
                        itNew->second.first->SetNonDistributeFlag(DIST::IO_PRIV);
                    else if (isSgConstantSymb(symb))
                        itNew->second.first->SetNonDistributeFlag(DIST::SPF_PRIV);
                    else
                        itNew->second.first->SetNonDistributeFlag(DIST::DISTR);
                }

                if (typeSize == 0) // unknown
                    itNew->second.first->SetNonDistributeFlag(DIST::SPF_PRIV);

                if (!isExecutable)
                    itNew->second.first->AddDeclInfo(make_pair(st->fileName(), st->lineNumber()));
                
                if (isExecutable)
                {
                    itNew->second.second->AddAccessInfo(make_pair(st->lineNumber(), isWrite ? 1 : 0), st->fileName());
                    itNew->second.first->AddUsagePlace(st->fileName(), st->lineNumber());
                }
                
                auto itDecl = declaratedArraysSt.find(decl);
                if (itDecl == declaratedArraysSt.end())
                    itDecl = declaratedArraysSt.insert(itDecl, make_pair(decl, set<tuple<int, string, string>>()));
                itDecl->second.insert(uniqKey);

                if (decl->variant() == DVM_VAR_DECL || decl->variant() == HPF_TEMPLATE_STAT)
                {
                    const string tmp(decl->unparse());
                    if (tmp.find("!DVM$ TEMPLATE") != string::npos)
                    {
                        itNew->second.first->SetTemplateFlag(true);
                        //TODO: analyze align mapping
                        for (int z = 0; z < itNew->second.first->GetDimSize(); ++z)
                            itNew->second.first->SetMappedDim(z);
                    }
                }
            }
        }
    }

    findArrayRefs(ex->lhs(), st, commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, deprecatedByIO, isExecutable, currFunctionName, isWrite, inRegion, funcParNames);
    findArrayRefs(ex->rhs(), st, commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, deprecatedByIO, isExecutable, currFunctionName, isWrite, inRegion, funcParNames);
}

static void findArrayRefInIO(SgExpression *ex, set<string> &deprecatedByIO, const int line, vector<Messages> &currMessages)
{
    if (ex)
    {
        if (ex->variant() == ARRAY_REF)
        {
            auto symb = ex->symbol();
            if (symb->type())
            {
                if (symb->type()->variant() == T_ARRAY)
                {
                    auto found = deprecatedByIO.find(OriginalSymbol(symb)->identifier());
                    if (found == deprecatedByIO.end())
                    {
                        deprecatedByIO.insert(found, OriginalSymbol(symb)->identifier());

                        wstring messageE, messageR;
                        __spf_printToLongBuf(messageE, L"Array '%s' can not be distributed because of DVM's I/O constraints", to_wstring(symb->identifier()).c_str());
#ifdef _WIN32
                        __spf_printToLongBuf(messageR, R68, to_wstring(symb->identifier()).c_str());
#endif
                        currMessages.push_back(Messages(WARR, line, messageR, messageE, 1037));

                        __spf_print(1, "Array '%s' at line %d can not be distributed because of DVM's I/O constraints\n", symb->identifier(), line);
                    }
                }
            }
        }
        
        findArrayRefInIO(ex->lhs(), deprecatedByIO, line, currMessages);
        findArrayRefInIO(ex->rhs(), deprecatedByIO, line, currMessages);
    }
}

static void findReshape(SgStatement *st, set<string> &privates, vector<Messages> &currMessages)
{
    if (st->variant() == ASSIGN_STAT)
    {
        SgExpression *exL = st->expr(0);
        SgExpression *exR = st->expr(1);

        if (exR->variant() == FUNC_CALL && exL->variant() == ARRAY_REF)
        {
            if (exR->symbol()->identifier() == string("reshape"))
            {
                privates.insert(exL->symbol()->identifier());
#ifdef _WIN32
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"Array '%s' can not be distributed because of RESHAPE", to_wstring(exL->symbol()->identifier()).c_str());
                __spf_printToLongBuf(messageR, R90, to_wstring(exL->symbol()->identifier()).c_str());
                currMessages.push_back(Messages(NOTE, st->lineNumber(), messageR, messageE, 1047));
#endif
            }
        }
    }
}

void getAllDeclaratedArrays(SgFile *file, map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                            map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt, vector<Messages> &currMessages,
                            const vector<ParallelRegion*> &regions)
{
    vector<SgStatement*> modules;
    findModulesInFile(file, modules);

    map<string, set<string>> privatesByModule;
    for (auto &mod : modules)
    {
        const string modName = mod->symbol()->identifier();
        privatesByModule[modName] = set<string>();
        auto it = privatesByModule.find(modName);

        for (SgStatement *iter = mod; iter != mod->lastNodeOfStmt(); iter = iter->lexNext())
        {
            if (iter->variant() == CONTAINS_STMT)
                break;

            //after SPF preprocessing 
            for (auto &data : getAttributes<SgStatement*, SgStatement*>(iter, set<int>{ SPF_ANALYSIS_DIR }))
                fillPrivatesFromComment(new Statement(data), it->second);

            //before SPF preprocessing 
            if (iter->variant() == SPF_ANALYSIS_DIR)
                fillPrivatesFromComment(new Statement(iter), it->second);
        }
    }

    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        map<string, vector<SgExpression*>> commonBlocks;
        const string currFunctionName = st->symbol()->identifier();

        getCommonBlocksRef(commonBlocks, st, lastNode);
        set<string> privates;
        set<string> deprecatedByIO;
        map<string, set<string>> reductions;
        map<string, set<tuple<string, string, int>>> reductionsLoc;
        set<string> funcParNames;

        if (st->variant() != PROG_HEDR)
        {
            SgProcHedrStmt *func = (SgProcHedrStmt*)st;
            for (int z = 0; z < func->numberOfParameters(); ++z)
                funcParNames.insert(func->parameter(z)->identifier());
        }

        for (SgStatement *iter = st; iter != lastNode; iter = iter->lexNext())
        {
            if (iter->variant() == CONTAINS_STMT)
                break;

            //after SPF preprocessing 
            for (auto &data : getAttributes<SgStatement*, SgStatement*>(iter, set<int>{ SPF_ANALYSIS_DIR }))
            {
                fillPrivatesFromComment(new Statement(data), privates);
                fillReductionsFromComment(new Statement(data), reductions);
                fillReductionsFromComment(new Statement(data), reductionsLoc);
            }

            //before SPF preprocessing 
            if (iter->variant() == SPF_ANALYSIS_DIR)
            {
                fillPrivatesFromComment(new Statement(iter), privates);
                fillReductionsFromComment(new Statement(iter), reductions);
                fillReductionsFromComment(new Statement(iter), reductionsLoc);
            }

            if (iter->variant() == USE_STMT)
                fillFromModule(iter->symbol(), privatesByModule, privates);

            findReshape(iter, privates, currMessages);
        }

        SgStatement* tmpModFind = st;
        while (tmpModFind->variant() != GLOBAL)
        {
            tmpModFind = tmpModFind->controlParent();
            if (tmpModFind->variant() == MODULE_STMT)
                fillFromModule(tmpModFind->symbol(), privatesByModule, privates);
        }

        SgStatement *currF = st;
        SgStatement *contains = isSgProgHedrStmt(currF->controlParent());
        if (contains)
        {
            for (SgStatement *loc = contains; loc; loc = loc->lexNext())
            {
                if (isSgExecutableStatement(loc))
                    break;
                if (loc->variant() == CONTAINS_STMT)
                    break;

                if (loc->variant() == USE_STMT)
                    fillFromModule(loc->symbol(), privatesByModule, privates);
            }
        }

        for (auto &elem : reductions)
            for (auto &setElem : elem.second)
                privates.insert(setElem);

        for (auto &elem : reductionsLoc)
        {
            for (auto &setElem : elem.second)
            {
                privates.insert(get<0>(setElem));
                privates.insert(get<1>(setElem));
            }
        }

        //analyze IO operations
        if (!ignoreIO)
        {
            for (SgStatement* iter = st; iter != lastNode; iter = iter->lexNext())
            {
                if (iter->variant() == CONTAINS_STMT)
                    break;

                SgInputOutputStmt* stIO = isSgInputOutputStmt(iter);
                if (stIO)
                {
                    int countOfItems = 0;
                    for (SgExpression* items = stIO->itemList(); items; items = items->rhs(), ++countOfItems);

                    //TODO: need to add more checkers!
                    if (countOfItems > 1)
                    {
                        for (SgExpression* items = stIO->itemList(); items; items = items->rhs(), ++countOfItems)
                            findArrayRefInIO(items->lhs(), deprecatedByIO, stIO->lineNumber(), currMessages);
                    }
                    else if (countOfItems == 1)
                    {
                        auto list = stIO->itemList();
                        if (list->lhs()->lhs() != NULL || list->lhs()->rhs() != NULL)
                            findArrayRefInIO(list->lhs(), deprecatedByIO, stIO->lineNumber(), currMessages);
                    }
                }
            }
        }

        while (st != lastNode)
        {
            currProcessing.second = st->lineNumber();
            if (st->variant() == CONTAINS_STMT)
                break;

            if (!isSPF_stat(st))
            {
                set<ParallelRegion*> currRegs = getAllRegionsByLine(regions, st->fileName(), st->lineNumber());
                vector<string> regNames;
                for (auto &reg : currRegs)
                    regNames.push_back(reg->GetName());
                if (regNames.size() == 0)
                    regNames.push_back("default");

                //TODO: need to add IPO analysis for R/WR state for calls and functions
                //TODO: improve WR analysis
                for (int i = 0; i < 3; ++i)
                    findArrayRefs(st->expr(i), st, commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, deprecatedByIO,
                                  isSgExecutableStatement(st) ? true : false, currFunctionName,
                                  (st->variant() == ASSIGN_STAT && i == 0) ? true : false, regNames, funcParNames);
            }
            st = st->lexNext();
        }
    }

    for (auto &mod : modules)
    {
        SgStatement *st = mod->lexNext();
        SgStatement *lastNode = mod->lastNodeOfStmt();
        map<string, vector<SgExpression*>> commonBlocks;
        set<string> privates;
        set<string> deprecatedByIO;
        set<string> funcParNames;

        fillFromModule(st->symbol(), privatesByModule, privates);
        
        while (st != lastNode)
        {
            currProcessing.second = st->lineNumber();
            if (st->variant() == CONTAINS_STMT)
                break;

            if (!isSPF_stat(st))
            {
                //TODO: set clear regions for modules
                set<ParallelRegion*> currRegs = getAllRegionsByLine(regions, st->fileName(), st->lineNumber());
                vector<string> regNames;
                for (auto &reg : currRegs)
                    regNames.push_back(reg->GetName());
                if (regNames.size() == 0)
                    regNames.push_back("default");

                for (int i = 0; i < 3; ++i)
                    findArrayRefs(st->expr(i), st, commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, deprecatedByIO,
                                  false, "NULL", false, regNames, funcParNames);
            }
            st = st->lexNext();
        }
    }
}

void insertSpfAnalysisBeforeParalleLoops(const vector<LoopGraph*> &loops)
{
    for (auto &loop : loops)
    {
        SgStatement *spfStat = new SgStatement(SPF_ANALYSIS_DIR);
        spfStat->setlineNumber(loop->lineNum);
        spfStat->setFileName((char*)current_file->filename());

        if (!loop->hasLimitsToParallel())
        {
            loop->loop->addAttribute(SPF_ANALYSIS_DIR, spfStat, sizeof(SgStatement));
            //uncomment it to debug private analysis
            //loop->loop->insertStmtBefore(*spfStat);
        }
        insertSpfAnalysisBeforeParalleLoops(loop->children);
    }
}
#undef PRINT_ARRAY_ARCS
#undef PRINT_LOOP_STRUCT
#undef PRINT_PROF_INFO
#undef FIRST
#undef SECOND
#undef THIRD
