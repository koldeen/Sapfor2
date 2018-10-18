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

#if _WIN32 && NDEBUG
#include <boost/thread.hpp>
extern int passDone;
#endif

#include "../Distribution/Distribution.h"
#include "../Distribution/GraphCSR.h"
#include "../Distribution/Arrays.h"
#include "../ParallelizationRegions/ParRegions.h"

#include "../Utils/errors.h"
#include "loop_analyzer.h"
#include "directive_parser.h"
#include "../Utils/SgUtils.h"
#include "../Utils/AstWrapper.h"

#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ParallelizationRegions/ParRegions_func.h"

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
                             const int dimNum, const pair<int, int> newCoef, int type, const int maxDimSize)
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
        itSymb->second.readOps[dimNum].coefficients.push_back(newCoef);
    else if (type == WRITE_OP)
        itSymb->second.writeOps[dimNum].coefficients.push_back(newCoef);
    else if (type == UNREC_OP)
        itSymb->second.unrecReadOps[dimNum] = true;
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}


static vector<int> matchSubscriptToLoopSymbols(const vector<SgForStmt*> &parentLoops, SgExpression *subscr,
                                               SgArrayRefExp *arrayRefIn, const int side, const int dimNum,
                                               map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo,
                                               const int currLine, const int numOfSubscriptions, bool &wasMapped)
{
    wasMapped = false;
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

            string message;
            __spf_printToBuf(message, "array ref '%s' has more than one loop's variables", arrayRefString.second.c_str());
            if (currLine > 0)
                currMessages->push_back(Messages(WARR, currLine, message, 1021));
        }

        for (int i = 0; i < allPositions.size(); ++i)
        {
            if (currRegime == REMOTE_ACC)
            {
                if (side == RIGHT)
                {
                    addInfoToMaps(loopInfo, parentLoops[allPositions[i]], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
                    wasMapped = true;
                }
            }
            else
            {
                addInfoToVectors(loopInfo, parentLoops[allPositions[i]], currOrigArrayS, dimNum, make_pair(0, 0), UNREC_OP, numOfSubscriptions);
                wasMapped = true;
            }
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
                {
                    addInfoToMaps(loopInfo, parentLoops[i], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
                    wasMapped = true;
                }
        }
        else if (currRegime == DATA_DISTR)
        {
            const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, origSubscr);

            if (!hasArrayAcc)
            {
                if (parentLoops.size() != 0 && (arrayRefString.first || side == LEFT))
                {
                    __spf_print(1, "WARN: array ref '%s' at line %d does not have loop variables\n", arrayRefString.second.c_str(), currLine);

                    string message;
                    __spf_printToBuf(message, "array ref '%s' does not have loop variables", arrayRefString.second.c_str());
                    if (currLine > 0)
                        currMessages->push_back(Messages(WARR, currLine, message, 1021));
                }
            }
            else
            {
                __spf_print(1, "WARN: array ref '%s' at line %d has indirect access\n", arrayRefString.second.c_str(), currLine);

                string message;
                __spf_printToBuf(message, "array ref '%s' has indirect access", arrayRefString.second.c_str());
                if (currLine > 0)
                    currMessages->push_back(Messages(WARR, currLine, message, 1022));
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
                {
                    addInfoToMaps(loopInfo, parentLoops[position], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
                    wasMapped = true;
                }
            }
            else if (currRegime == DATA_DISTR)
            {                
                const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, origSubscr);
                __spf_print(1, "WARN: can not calculate index expression for array ref '%s' at line %d\n", arrayRefString.second.c_str(), currLine);
                addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, UNREC_OP, numOfSubscriptions);
                wasMapped = true;

                string message;
                __spf_printToBuf(message, "can not calculate index expression for array ref '%s'", arrayRefString.second.c_str());
                if (currLine > 0)
                    currMessages->push_back(Messages(WARR, currLine, message, 1023));
            }
        }
        else
        {
            if (currRegime == REMOTE_ACC)
            {
                if (side == RIGHT)
                {
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

                    itArrayAcc->second.second[dimNum].coefficients.push_back(coefs);
                    wasMapped = true;
                }

                //if we found regular access to array - set it false
                addInfoToMaps(loopInfo, parentLoops[position], currOrigArrayS, arrayRef, dimNum, REMOTE_FALSE, currLine, numOfSubscriptions);
                wasMapped = true;
            }

            if (coefs.first < 0)
            {
                if (currRegime == DATA_DISTR)
                {
                    const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, origSubscr);
                    const int line = (currLine < 0) ? parentLoops[position]->localLineNumber() : currLine;

                    __spf_print(1, "WARN: coefficient A in A*x+B is not positive for array ref '%s' at line %d, inverse distribution in not supported yet\n", arrayRefString.second.c_str(), line);
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, UNREC_OP, numOfSubscriptions);
                    wasMapped = true;

                    string message;
                    __spf_printToBuf(message, "coefficient A in A*x+B is not positive for array ref '%s', inverse distribution in not supported yet", arrayRefString.second.c_str());
                    if (line > 0)
                        currMessages->push_back(Messages(WARR, line, message, 1024));
                }
            }
            else
            {
                if (side == LEFT)
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, WRITE_OP, numOfSubscriptions);
                else
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, READ_OP, numOfSubscriptions);
                wasMapped = true;
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

static bool matchArrayToLoopSymbols(const vector<SgForStmt*> &parentLoops, SgExpression *currExp, const int side,
                                    map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, const int currLine,
                                    map<int, LoopGraph*> &sortedLoopGraph)
{
    SgArrayRefExp *arrayRef = (SgArrayRefExp*)currExp;
    int numOfSubs = arrayRef->numberOfSubscripts();

    currExp = currExp->lhs();
    vector<int> wasFound(parentLoops.size());
    vector<int> matched(numOfSubs);
    std::fill(wasFound.begin(), wasFound.end(), 0);
    std::fill(matched.begin(), matched.end(), -1);
    int maxMatched = 0;
    int sumMatched = 0;
    bool wasMapped = false;

    for (int i = 0; i < numOfSubs; ++i)
    {
        bool mapped = false;
        vector<int> matchToLoops = matchSubscriptToLoopSymbols(parentLoops, currExp->lhs(), arrayRef, side, i, loopInfo, currLine, numOfSubs, mapped);
        wasMapped |= mapped;

        for (int k = 0; k < matchToLoops.size(); ++k)
            wasFound[matchToLoops[k]]++;

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
                    addInfoToVectors(loopInfo, parentLoops[i], currOrigArrayS, d, make_pair(0, 0), UNREC_OP, arrType->dimension());
        }
    }

    if (currRegime == PRIVATE_STEP4)
        return wasMapped;

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
            if (side == LEFT)
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

                string message;
                __spf_printToBuf(message, "can not map write to array '%s' to this loop", arrayRefS.c_str());
                if (line > 0)
                    currMessages->push_back(Messages(WARR, line, message, 1025));
            }
        }
    }
    else if (side == RIGHT)
    {
        SgSymbol *currOrigArrayS = OriginalSymbol(arrayRef->symbol());
        
        if (ifUnknownFound && (currRegime == REMOTE_ACC)) // TODO: check array's alignment
        {
            if (sumMatched != numOfSubs || 
                maxMatched != 1 || 
                sumMatched != parentLoops.size() // && sumMatched != numOfSubs)
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
                    local += wasFound[i];
                    if (local == sumMatched)
                        break;

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

    return wasMapped;
}

static inline void findArrayRefInParameters(SgExpression *parList, const set<string> &privatesVars, const char *procName, const int line);
static void findArrayRef(const vector<SgForStmt*> &parentLoops, SgExpression *currExp, const int lineNum, const int side, 
                         map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, const int currLine, const set<string> &privatesVars,
                         map<int, LoopGraph*> &sortedLoopGraph, const map<string, vector<SgExpression*>> &commonBlocks,
                         const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays, 
                         bool wasDistributedArrayRef, map<string, pair<SgSymbol*, SgStatement*>> &notMappedDistributedArrays,
                         set<string> &mappedDistrbutedArrays, SgStatement *currentSt)
{
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
                bool wasMapped = matchArrayToLoopSymbols(parentLoops, currExp, side, loopInfo, currLine, sortedLoopGraph);
                                
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
                    map<string, set<string>> loopsReductions;
                    map<string, set<tuple<string, string, int>>> loopsReductionsLoc;

                    
                    for (auto &loop : parentLoops)
                    {
                        for (auto &data : getAttributes<SgStatement*, SgStatement*>(loop, set<int>{ SPF_ANALYSIS_DIR }))
                        {
                            fillPrivatesFromComment(data, loopsPrivates);
                            fillReductionsFromComment(data, loopsReductions);
                            fillReductionsFromComment(data, loopsReductionsLoc);
                        }
                    }

                    for (auto &elem : loopsReductions)
                        for (auto &setElem : elem.second)
                            loopsPrivates.insert(setElem);

                    for (auto &elem : loopsReductionsLoc)
                    {
                        for (auto &setElem : elem.second)
                        {
                            loopsPrivates.insert(get<0>(setElem));
                            loopsPrivates.insert(get<1>(setElem));
                        }
                    }

                    if (loopsPrivates.find(string(OriginalSymbol(currExp->symbol())->identifier())) == loopsPrivates.end())                    
                    {
                        for (auto &loop : parentLoops)
                        {
                            __spf_print(1, "WARN: write to non distributed array '%s' in loop on line %d\n", symb->identifier(), loop->lineNumber());

                            string message;
                            __spf_printToBuf(message, "write to non distributed array '%s' in this loop", symb->identifier());
                            if (loop->lineNumber() > 0)
                                currMessages->push_back(Messages(WARR, loop->lineNumber(), message, 1026));
                            sortedLoopGraph[loop->lineNumber()]->hasWritesToNonDistribute = true;
                        }
                    }
                }
            }
        }
    }
    else if (currExp->variant() == FUNC_CALL)
    {
        SgFunctionCallExp *funcExp = (SgFunctionCallExp*)currExp;
        if (isUserFunctionInProject(funcExp->funName()->identifier()))
            findArrayRefInParameters(funcExp->args(), privatesVars, funcExp->funName()->identifier(), lineNum);
    }

    if (currExp->lhs())
        findArrayRef(parentLoops, currExp->lhs(), lineNum, (side == LEFT) ? RIGHT : side, loopInfo, currLine, privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, wasDistributedArrayRef, notMappedDistributedArrays, mappedDistrbutedArrays, currentSt);
    if (currExp->rhs())
        findArrayRef(parentLoops, currExp->rhs(), lineNum, (side == LEFT) ? RIGHT : side, loopInfo, currLine, privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, wasDistributedArrayRef, notMappedDistributedArrays, mappedDistrbutedArrays, currentSt);
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

vector<pair<Expression*, Expression*>> getArraySizes(vector<pair<int, int>> &sizes, SgSymbol *symb, SgStatement *decl)
{
    SgArrayType *type = isSgArrayType(symb->type());
    vector<pair<Expression*, Expression*>> retVal;

    if (type != NULL)
    {
        SgExpression *dimList = type->getDimList();
        int consistInAllocates = 0;
        SgExpression *alloc = NULL;

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
                                    if (string(OriginalSymbol(arrayRef->symbol())->identifier()) == string(symb->identifier()))
                                    {
                                        consistInAllocates++;
                                        alloc = list->lhs()->lhs();
                                        break;
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

bool isIntrinsic(const char *funName)
{
    if (intrinsicF.find(funName) == intrinsicF.end())
        return false;
    else
        return true;
}

static inline void findArrayRefInParameters(SgExpression *parList, const set<string> &privatesVars, const char *procName, const int line)
{
    while (parList)
    {
        if (parList->lhs()->variant() == ARRAY_REF)
        {
            if (parList->lhs()->type()->variant() == T_ARRAY)
            {
                const char *arrayName = parList->lhs()->symbol()->identifier();
                auto it = privatesVars.find(arrayName);
                if (it == privatesVars.end())
                {
                    if (!isPassFullArray(parList->lhs()))
                    {
                        __spf_print(1, "ERROR: %d %s: array '%s' in function '%s' at line %d is not a private\n", __LINE__, convertFileName(__FILE__).c_str(), arrayName, procName, line);
                        __spf_print(1, "  this functionality has not supported yet\nSTOP\n");

                        string message;
                        __spf_printToBuf(message, "array '%s' in function '%s' is not a private, this functionality has not supported yet", arrayName, procName);
                        currMessages->push_back(Messages(ERROR, line, message, 1027));

                        throw(-1);
                    }
                }
            }
        }
        parList = parList->rhs();
    }
}

static set<string> getPrivatesFromModule(SgStatement *mod, 
                                         const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                         const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                                         const map<string, SgStatement*> &modulesByName)
{
    set<string> privates;
    SgStatement *end = mod->lastNodeOfStmt();
    while (end != mod)
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
                           map<tuple<int, string, string>, DIST::Array*> &createdArrays)
{
    map<DIST::Array*, const ArrayInfo*> toAdd;
    for (auto it1 = toConvert.begin(); it1 != toConvert.end(); ++it1)
    {
        SgSymbol *currentArray = it1->first;
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

            for (auto linkedArray = links.begin(); linkedArray != links.end(); ++linkedArray)
            {
                if (arrayToAdd == *linkedArray)
                    continue;

                auto key = tableOfUniqNamesByArray[*linkedArray];
                auto value = declaratedArrays.find(key)->second;
                if (value.second == 0 && createdArrays.find(key) == createdArrays.end())
                    createdArrays.insert(make_pair(key, *linkedArray));
            }

            toAdd[arrayToAdd] = currentInfo;

            for (int z = 0; z < currentInfo->dimSize; ++z)
                if (currentInfo->readOps[z].coefficients.size() || currentInfo->writeOps[z].coefficients.size())
                    arrayToAdd->SetMappedDim(z);            
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

    fillPrivatesFromDecl(ex->rhs(), delcsSymbViewed, delcsStatViewed, declaratedArrays, declaratedArraysSt, privatesVars);
    fillPrivatesFromDecl(ex->lhs(), delcsSymbViewed, delcsStatViewed, declaratedArrays, declaratedArraysSt, privatesVars);
}

extern void createMapLoopGraph(std::map<int, LoopGraph*> &sortedLoopGraph, const std::vector<LoopGraph*> *loopGraph);
void loopAnalyzer(SgFile *file, vector<ParallelRegion*> regions, map<tuple<int, string, string>, DIST::Array*> &createdArrays,
                  vector<Messages> &messagesForFile, REGIME regime, const map<string, vector<FuncInfo*>> &AllfuncInfo,
                  const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                  const map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                  vector<LoopGraph*> *loopGraph)
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

        while (st != lastNode)
        {
            currProcessing.second = st;
#if _WIN32 && NDEBUG
            if (passDone == 2)
                throw boost::thread_interrupted();
#endif
            if (st == NULL)
            {
                string message;
                __spf_printToBuf(message, "internal error in analysis, parallel directives will not be generated for this file!");
                currMessages->push_back(Messages(ERROR, 1, message, 3008));

                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

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
                                        const DIST::GraphCSR<int, double, attrType> &reducedG = currReg->GetReducedGraph();
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
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), LEFT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, mappedDistrbutedArrays, st);
                if (st->expr(1))
                    findArrayRef(parentLoops, st->expr(1), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, mappedDistrbutedArrays, st);

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
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, mappedDistrbutedArrays, st);
                    if (regime == REMOTE_ACC)
                    {
                        const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();

                        if (under_dvm_dir == NULL)
                            createRemoteDir<0>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages, arrayLinksByFuncCalls);
                    }
                }
            }
            // TODO: need to think about it
            /*else if (currV == PROC_STAT)
            {
                if (isUserFunctionInProject(st->symbol()->identifier()) != NULL)
                {
                    SgExpression *parList = st->expr(0);
                    findArrayRefInParameters(parList, privatesVars, st->symbol()->identifier(), st->lineNumber());

                    if (regime == REMOTE_ACC)
                    {
                        const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();

                        if (under_dvm_dir == NULL)
                            createRemoteDir<0>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages);
                    }
                }
            }*/
            else if (currV == USE_STMT)
            {
                auto itF = privatesByModule.find(st->symbol()->identifier());
                if (itF == privatesByModule.end())
                {
                    string message;
                    __spf_printToBuf(message, "Module with name '%s' must be placed in current file", st->symbol()->identifier());
                    currMessages->push_back(Messages(ERROR, st->lineNumber(), message, 1028));

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

                if (isDVM_stat(st) == false)
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
                                findArrayRef(parentLoops, st->expr(z), st->lineNumber(), side, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, mappedDistrbutedArrays, st);
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
#ifdef _WIN32
                string fName = file->functions(i)->symbol()->identifier();
                sendMessage_2lvl(wstring(L"обработка цикла ") + std::to_wstring(idx) + L"/" + std::to_wstring(convertedLoopInfo.size()));
#endif
                tryToFindDependencies(loop.first, allLoops, funcWasInit, file, regions, currMessages, collection, funcByName);
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
                                toAdd.readOps.push_back(ArrayOp(make_pair(1, 0)));
                            
                            toConvert[arrayS] = toAdd;
                            convertOneLoop(tmpLoop, convertedLoopInfo, toConvert, privatesVars, commonBlocks, declaratedArrays, arrayLinksByFuncCalls, createdArrays);
                        }
                    }
                }
            }

            addToDistributionGraph(convertedLoopInfo, arrayLinksByFuncCalls);

            for (auto &toDel : tmpLoops)
                delete toDel;            

            for (auto &loop : loopWithOutArrays)
            {
                tryToFindDependencies(sortedLoopGraph[loop], allLoops, funcWasInit, file, regions, currMessages, collection, funcByName);
                sortedLoopGraph[loop]->withoutDistributedArrays = true;
            }

            //only top loop may be parallel
            for (auto &loop : loopWithOutArrays)
            {
                auto loopRef = sortedLoopGraph[loop];
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
            
            for (auto &loop : loopWithOutArrays)
            {
                if (sortedLoopGraph[loop]->withoutDistributedArrays)
                {
                    //TODO: enable linear writes to non distr arrays for CONSISTENT
                    bool hasWritesToArray = false;
                    bool hasReduction = false;
                    //TODO: add IPA for non pure
                    bool hasNonPureProcedures = false;

                    auto loopRef = sortedLoopGraph[loop];
                    SgStatement *loopSt = loopRef->loop;

                    for (auto &data : getAttributes<SgStatement*, SgStatement*>(loopSt, set<int>{ SPF_ANALYSIS_DIR, SPF_PARALLEL_DIR }))
                    {
                        map<string, set<string>> reductions;
                        map<string, set<tuple<string, string, int>>> reductionsLoc;

                        fillReductionsFromComment(data, reductions);
                        fillReductionsFromComment(data, reductionsLoc);

                        hasReduction = (reductions.size() != 0) || (reductionsLoc.size() != 0);
                        if (hasReduction)
                            break;
                    }

                    for (SgStatement *start = loopSt->lexNext(); 
                         start != loopSt->lastNodeOfStmt() && !hasNonPureProcedures;
                         start = start->lexNext())
                    {
                        if (start->variant() == ASSIGN_STAT)
                            if (start->expr(0)->variant() == ARRAY_REF)
                                hasWritesToArray = true;

                        if (start->variant() == PROC_STAT)
                        {
                            if (!IsPureProcedureACC(isSgCallStmt(start)->name()))
                                hasNonPureProcedures = true;
                        }
                    }

                    if ((hasReduction || (!hasReduction && !hasWritesToArray)) && !hasNonPureProcedures)
                    {
                        if (!addToDistributionGraph(loopRef, funcName))
                            loopRef->withoutDistributedArrays = false;
                    }
                    else
                        loopRef->withoutDistributedArrays = false;
                }
            }

#ifdef _WIN32
            sendMessage_2lvl(L"");
#endif
        }
        else if (regime == COMP_DISTR)
        {
            createParallelDirectives(convertedLoopInfo, regions, sortedLoopGraph, arrayLinksByFuncCalls, messagesForFile);

            for (auto &loop : loopWithOutArrays)
            {
                auto loopRef = sortedLoopGraph[loop];
                if (loopRef->withoutDistributedArrays && loopRef->region && !loopRef->hasLimitsToParallel())
                {
                    auto region = loopRef->region;
                    auto allArrays = region->GetAllArrays();

                    string fullLoopName = loopRef->genLoopArrayName(funcName);
                    auto loopArray = allArrays.GetArrayByName(fullLoopName);
                    
                    ArrayInfo tmpArrayInfo;
                    tmpArrayInfo.dimSize = 1;

                    ArrayOp tmpOp;
                    tmpOp.coefficients.push_back(make_pair(1, 0));
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
                
        while (st != lastNode)
        {
            currProcessing.second = st;
#if _WIN32 && NDEBUG
            if (passDone == 2)
                throw boost::thread_interrupted();
#endif
            if (st == NULL)
            {
                string message;
                __spf_printToBuf(message, "internal error in analysis, parallel directives will not be generated for this file!");
                currMessages->push_back(Messages(ERROR, 1, message, 3008));

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
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), LEFT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, mappedDistrbutedArrays, st);
                if (st->expr(1))
                    findArrayRef(parentLoops, st->expr(1), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, mappedDistrbutedArrays, st);
            }
            else if (currV == IF_NODE || currV == ELSEIF_NODE || currV == LOGIF_NODE || currV == SWITCH_NODE)
            {
                if (st->expr(0))
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph, commonBlocks, declaratedArrays, false, notMappedDistributedArrays, mappedDistrbutedArrays, st);
            }
            st = st->lexNext();
        }
        __spf_print(PRINT_PROF_INFO, "Function ended\n");
    }
}

static void findArrayRefs(SgExpression *ex,
                          const map<string, vector<SgExpression*>> &commonBlocks,
                          const vector<SgStatement*> &modules,
                          map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                          map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                          const set<string> &privates, const set<string> &deprecatedByIO, 
                          bool isExecutable, SgStatement *declSt, const string &currFunctionName, bool isWrite,
                          const ParallelRegion *inRegion,
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
                SgStatement *decl = declaratedInStmt(symb);

                auto uniqKey = getUniqName(commonBlocks, decl, symb);
                pair<int, string> arrayLocation;
                if (symb != ex->symbol())
                {
                    SgStatement *scope = symb->scope();
                    if (scope)
                        arrayLocation = make_pair(2, scope->symbol()->identifier());
                    else //TODO: find module name with another way
                        arrayLocation = make_pair(2, "UNREC_MODULE_NAME");
                }
                else if (get<1>(uniqKey).find("common_") != string::npos)
                    arrayLocation = make_pair(1, get<1>(uniqKey).substr(strlen("common_")));
                else if (funcParNames.find(symb->identifier()) != funcParNames.end())
                    arrayLocation = make_pair(3, currFunctionName);
                else
                    arrayLocation = make_pair(0, currFunctionName);

                auto itNew = declaratedArrays.find(uniqKey);
                if (itNew == declaratedArrays.end())
                {
                    DIST::Array *arrayToAdd = 
                        new DIST::Array(getShortName(uniqKey), symb->identifier(), ((SgArrayType*)(symb->type()))->dimension(), 
                                        getUniqArrayId(), decl->fileName(), decl->lineNumber(), arrayLocation, new Symbol(symb),
                                        (inRegion != NULL) ? inRegion->GetName() : "");

                    itNew = declaratedArrays.insert(itNew, make_pair(uniqKey, make_pair(arrayToAdd, new DIST::ArrayAccessInfo())));

                    vector<pair<int, int>> sizes;
                    auto sizesExpr = getArraySizes(sizes, symb, decl);
                    arrayToAdd->SetSizes(sizes);
                    arrayToAdd->SetSizesExpr(sizesExpr);
                    tableOfUniqNamesByArray[arrayToAdd] = uniqKey;
                }
                else
                    itNew->second.first->SetRegionPlace((inRegion != NULL) ? inRegion->GetName() : "");
                
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

                if (!isExecutable)
                    itNew->second.first->AddDeclInfo(make_pair(declSt->fileName(), declSt->lineNumber()));
                itNew->second.first->AddDeclInfo(make_pair(decl->fileName(), decl->lineNumber()));
                
                if (isExecutable)
                    itNew->second.second->AddAccessInfo(make_pair(declSt->lineNumber(), isWrite ? 1 : 0), declSt->fileName());
                
                auto itDecl = declaratedArraysSt.find(decl);
                if (itDecl == declaratedArraysSt.end())
                    itDecl = declaratedArraysSt.insert(itDecl, make_pair(decl, set<tuple<int, string, string>>()));
                itDecl->second.insert(uniqKey);

                if (decl->variant() == DVM_VAR_DECL)
                {
                    const string tmp(decl->unparse());
                    if (tmp.find("!DVM$ TEMPLATE") != string::npos)
                        itNew->second.first->SetTemplateFlag(true);
                }
            }
        }
    }

    findArrayRefs(ex->lhs(), commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, deprecatedByIO, isExecutable, declSt, currFunctionName, isWrite, inRegion, funcParNames);
    findArrayRefs(ex->rhs(), commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, deprecatedByIO, isExecutable, declSt, currFunctionName, isWrite, inRegion, funcParNames);
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

                        string message;
                        __spf_printToBuf(message, "Array '%s' can not be distributed because of DVM's I/O constraints", symb->identifier());
                        currMessages.push_back(Messages(WARR, line, message, 1037));

                        __spf_print(1, "Array '%s' at line %d can not be distributed because of DVM's I/O constraints\n", symb->identifier(), line);
                    }
                }
            }
        }
        
        findArrayRefInIO(ex->lhs(), deprecatedByIO, line, currMessages);
        findArrayRefInIO(ex->rhs(), deprecatedByIO, line, currMessages);
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
                fillPrivatesFromComment(data, it->second);

            //before SPF preprocessing 
            if (iter->variant() == SPF_ANALYSIS_DIR)
                fillPrivatesFromComment(iter, it->second);
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
                fillPrivatesFromComment(data, privates);
                fillReductionsFromComment(data, reductions);
                fillReductionsFromComment(data, reductionsLoc);
            }

            //before SPF preprocessing 
            if (iter->variant() == SPF_ANALYSIS_DIR)
            {
                fillPrivatesFromComment(iter, privates);
                fillReductionsFromComment(iter, reductions);
                fillReductionsFromComment(iter, reductionsLoc);
            }

            if (iter->variant() == USE_STMT)
            {
                if (iter->symbol())
                {
                    auto it = privatesByModule.find(iter->symbol()->identifier());
                    if (it != privatesByModule.end())
                        privates.insert(it->second.begin(), it->second.end());
                }
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
        for (SgStatement *iter = st; iter != lastNode; iter = iter->lexNext())
        {
            if (iter->variant() == CONTAINS_STMT)
                break;

            SgInputOutputStmt *stIO = isSgInputOutputStmt(iter);
            if (stIO)
            {
                int countOfItems = 0;
                for (SgExpression *items = stIO->itemList(); items; items = items->rhs(), ++countOfItems);

                //TODO: need to add more checkers!
                if (countOfItems > 1)
                {                    
                    for (SgExpression *items = stIO->itemList(); items; items = items->rhs(), ++countOfItems)
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

        while (st != lastNode)
        {
            currProcessing.second = st;
            if (st->variant() == CONTAINS_STMT)
                break;

            ParallelRegion *currReg = getRegionByLine(regions, st->fileName(), st->lineNumber());

            //TODO: need to add IPO analysis for R/WR state for calls and functions
            //TODO: improve WR analysis
            for (int i = 0; i < 3; ++i)
                findArrayRefs(st->expr(i), commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, deprecatedByIO,
                              isSgExecutableStatement(st) ? true : false, st, currFunctionName,
                              (st->variant() == ASSIGN_STAT && i == 0) ? true : false, currReg, funcParNames);
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
