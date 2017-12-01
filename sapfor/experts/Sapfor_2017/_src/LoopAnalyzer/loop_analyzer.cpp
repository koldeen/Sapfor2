#include "../leak_detector.h"

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

#include "../errors.h"
#include "loop_analyzer.h"
#include "../directive_parser.h"
#include "../SgUtils.h"
#include "../AstWrapper.h"

#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ParallelizationRegions/ParRegions_func.h"

#include "../ExpressionTransform/expr_transform.h"
#include "../SageAnalysisTool/depInterfaceExt.h"

using std::vector;
using std::pair;
using std::tuple;
using std::map;
using std::set;
using std::make_pair;
using std::make_tuple;
using std::get;
using std::string;

#define PRINT_ARRAY_ARCS  0
#define PRINT_LOOP_STRUCT 0
#define PRINT_PROF_INFO   0

static REGIME currRegime = UNDEF;
static vector<Messages> *currMessages;

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

bool checkExistence(SgExpression *exp, SgSymbol doName)
{
    bool retVal = false;
    if (exp->variant() == VAR_REF)
        if (exp->symbol()->id() == doName.id())
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
                                               const int currLine, const int numOfSubscriptions)
{
    ArrayRefExp *arrayRef = new ArrayRefExp(arrayRefIn);
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

    // more than one loop symbol in subscription
    if (countOfSymbols > 1)
    {     
        print(PRINT_ARRAY_ARCS, " <%d|%d> ", 0, 0);
        if (currRegime == DATA_DISTR)
        {
            const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, subscr);
            print(1, "WARN: array ref '%s' at line %d has more than one loop's variables\n", arrayRefString.second.c_str(), currLine);

            string message;
            printToBuf(message, "array ref '%s' has more than one loop's variables", arrayRefString.second.c_str());
            currMessages->push_back(Messages(WARR, currLine, message));
        }

        for (int i = 0; i < allPositions.size(); ++i)
        {
            if (currRegime == REMOTE_ACC)
            {
                if (side == RIGHT)
                    addInfoToMaps(loopInfo, parentLoops[allPositions[i]], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
            }
            else
                addInfoToVectors(loopInfo, parentLoops[allPositions[i]], currOrigArrayS, dimNum, make_pair(0, 0), UNREC_OP, numOfSubscriptions);
        }
    }
    // no loop symbol in subscription
    else if (countOfSymbols == 0)
    {
        print(PRINT_ARRAY_ARCS, " <%d|%d> ", 0, 0);
        if (currRegime == REMOTE_ACC)
        {
            if (side == RIGHT)
                for (int i = 0; i < (int)parentLoops.size(); ++i)
                    addInfoToMaps(loopInfo, parentLoops[i], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
        }
        else if (currRegime == DATA_DISTR)
        {
            const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, subscr);

            if (!hasArrayAcc)
            {
                if (parentLoops.size() != 0 && (arrayRefString.first || side == LEFT))
                {
                    print(1, "WARN: array ref '%s' at line %d has not loop's variables\n", arrayRefString.second.c_str(), currLine);

                    string message;
                    printToBuf(message, "array ref '%s' has not loop's variables", arrayRefString.second.c_str());
                    currMessages->push_back(Messages(WARR, currLine, message));
                }
            }
            else
            {
                print(1, "WARN: array ref '%s' at line %d has indirect access\n", arrayRefString.second.c_str(), currLine);

                string message;
                printToBuf(message, "array ref '%s' has indirect access", arrayRefString.second.c_str());
                currMessages->push_back(Messages(WARR, currLine, message));
            }
        }
    }
    else
    {
        pair<int, int> coefs = pair<int, int>(0, 0);
        bool needToCacl = true;
        if (subscr->variant() == VAR_REF)
        {
            if (subscr->symbol()->id() == (parentLoops[position]->doName()).id())
            {
                coefs.first = 1;
                needToCacl = false;
            }
        }

        if (needToCacl)
            getCoefsOfSubscript(coefs, subscr, parentLoops[position]->doName());
        print(PRINT_ARRAY_ARCS, " <%d %d> ", coefs.first, coefs.second);

        if (coefs.first == 0 && coefs.second == 0)
        {
            if (currRegime == REMOTE_ACC)
            {
                if (side == RIGHT)
                    addInfoToMaps(loopInfo, parentLoops[position], currOrigArrayS, arrayRef, dimNum, REMOTE_TRUE, currLine, numOfSubscriptions);
            }
            else if (currRegime == DATA_DISTR)
            {
                const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, subscr);
                print(1, "WARN: can not calculate index expression for array ref '%s' at line %d\n", arrayRefString.second.c_str(), currLine);
                addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, UNREC_OP, numOfSubscriptions);

                string message;
                printToBuf(message, "can not calculate index expression for array ref '%s'", arrayRefString.second.c_str());
                currMessages->push_back(Messages(WARR, currLine, message));
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
                }

                //if we found regular access to array - set it false                
                addInfoToMaps(loopInfo, parentLoops[position], currOrigArrayS, arrayRef, dimNum, REMOTE_FALSE, currLine, numOfSubscriptions);
            }
            
            if (coefs.first < 0)
            {
                if (currRegime == DATA_DISTR)
                {
                    const pair<bool, string> &arrayRefString = constructArrayRefForPrint(arrayRef, dimNum, subscr);
                    print(1, "WARN: coefficient A in A*x+B is not positive for array ref '%s' at line %d, inverse distribution in not supported yet\n", arrayRefString.second.c_str(), currLine);
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, UNREC_OP, numOfSubscriptions);
                    
                    string message;
                    printToBuf(message, "coefficient A in A*x+B is not positive for array ref '%s', inverse distribution in not supported yet", arrayRefString.second.c_str());
                    currMessages->push_back(Messages(WARR, currLine, message));
                }
            }
            else
            {
                if (side == LEFT)
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, WRITE_OP, numOfSubscriptions);
                else
                    addInfoToVectors(loopInfo, parentLoops[position], currOrigArrayS, dimNum, coefs, READ_OP, numOfSubscriptions);
            }
        }        
    }

    return allPositions;
}

static void matchArrayToLoopSymbols(const vector<SgForStmt*> &parentLoops, SgExpression *currExp, const int side,
                                    map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, const int currLine,
                                    map<int, LoopGraph*> &sortedLoopGraph)
{
    SgArrayRefExp *arrayRef = (SgArrayRefExp*)currExp;
    int numOfSubs = arrayRef->numberOfSubscripts();
    
    currExp = currExp->lhs();
    vector<int> wasFound(parentLoops.size());
    std::fill(wasFound.begin(), wasFound.end(), 0);

    for (int i = 0; i < numOfSubs; ++i)
    {
        vector<int> matchToLoops = matchSubscriptToLoopSymbols(parentLoops, currExp->lhs(), arrayRef, side, i, loopInfo, currLine, numOfSubs);
        for (int k = 0; k < matchToLoops.size(); ++k)
            wasFound[matchToLoops[k]] = 1;
        currExp = currExp->rhs();
    }
    
    if (side == LEFT)
    {
        int countOfFound = 0;
        for (int i = 0; i < wasFound.size(); ++i)
            if (wasFound[i] == 1)
                countOfFound++;
         
        bool ifUnknownWriteFound = false;
        vector<int> canNotMapToLoop;
        for (int i = 0; i < wasFound.size(); ++i)
        {
            if (wasFound[i] == 0)
            {
                auto itLoop = sortedLoopGraph.find(parentLoops[i]->lineNumber());
                if (itLoop == sortedLoopGraph.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                ifUnknownWriteFound = itLoop->second->hasUnknownArrayAssignes = true;
                canNotMapToLoop.push_back(parentLoops[i]->lineNumber());
            }
        }

        if (ifUnknownWriteFound && (currRegime == DATA_DISTR))
        {
            const string arrayRefS = arrayRef->unparse();
            for (auto &line : canNotMapToLoop)
            {
                print(1, "WARN: can not map write to array '%s' to loop on line %d\n", arrayRefS.c_str(), line);

                string message;
                printToBuf(message, "can not map write to array '%s' to this loop", arrayRefS.c_str());
                currMessages->push_back(Messages(WARR, line, message));
            }
        }
    }
}

static inline void findArrayRefInParameters(SgExpression *parList, const set<string> &privatesVars, const char *procName, const int line);
static void findArrayRef(const vector<SgForStmt*> &parentLoops, SgExpression *currExp, const int lineNum, const int side, 
                         map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, const int currLine, const set<string> &privatesVars,
                         map<int, LoopGraph*> &sortedLoopGraph)
{
    if (currExp->variant() == ARRAY_REF)
    {
        //... and current array is not in private list
        if (privatesVars.find(string(OriginalSymbol(currExp->symbol())->identifier())) == privatesVars.end())
        {
            const char *printSide = NULL;
            if (PRINT_ARRAY_ARCS)
                printBlanks(2, (int)parentLoops.size());
            if (side == LEFT)
                printSide = "W_OP";
            else
                printSide = "R_OP";

            print(PRINT_ARRAY_ARCS, "%s to array <%s> on line %d: ", printSide, OriginalSymbol(currExp->symbol())->identifier(), lineNum);
            matchArrayToLoopSymbols(parentLoops, currExp, side, loopInfo, currLine, sortedLoopGraph);
            print(PRINT_ARRAY_ARCS, "\n");
        }
    }
    else if (currExp->variant() == FUNC_CALL)
    {
        SgFunctionCallExp *funcExp = (SgFunctionCallExp*)currExp;
        if (isUserFunctionInProject(funcExp->funName()->identifier()))
            findArrayRefInParameters(funcExp->args(), privatesVars, funcExp->funName()->identifier(), lineNum);
    }

    if (currExp->lhs())
        findArrayRef(parentLoops, currExp->lhs(), lineNum, side, loopInfo, currLine, privatesVars, sortedLoopGraph);
    if (currExp->rhs())
        findArrayRef(parentLoops, currExp->rhs(), lineNum, side, loopInfo, currLine, privatesVars, sortedLoopGraph);
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

static void getArraySizes(vector<pair<int, int>> &sizes, SgSymbol *symb, SgStatement *delc)
{
    SgArrayType *type = isSgArrayType(symb->type());
    if (type != NULL)
    {
        SgExpression *dimList = type->getDimList();
        int consistInAllocates = 0;
        SgExpression *alloc = NULL;

        while (dimList)
        {
            SgExpression *res = ReplaceArrayBoundSizes(dimList->lhs());
            if (res->variant() == INT_VAL)
                sizes.push_back(make_pair(1, res->valueInteger()));
            else if (res->variant() == DDOT)
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
                    sizes.push_back(make_pair(left, right));
                else
                {
                    if (alloc == NULL)
                    {
                        for (int i = 0; i < delc->numberOfAttributes(); ++i)
                        {
                            SgAttribute *attr = delc->getAttribute(i);
                            int type = delc->attributeType(i);
                            if (type == ALLOCATE_STMT)
                            {
                                SgStatement *data = (SgStatement *)(attr->getAttributeData());
                                SgExpression *list = data->expr(0);
                                if (data->variant() != ALLOCATE_STMT)
                                    continue;

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
                    }

                    if (consistInAllocates != 1)
                        sizes.push_back(make_pair(-1, -1));
                    else
                    {
                        SgExpression *result = ReplaceArrayBoundSizes(alloc->lhs());
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
                            sizes.push_back(make_pair(1, result->valueInteger()));
                        else if (result->variant() == DDOT)
                        {
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
                            sizes.push_back(make_pair(-1, -1));

                        alloc = alloc->rhs();
                    }
                }
            }
            else
                sizes.push_back(make_pair(-1, -1));
            dimList = dimList->rhs();
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
                        print(1, "ERROR: %d %s: array '%s' in function '%s' at line %d is not a private\n", __LINE__, convertFileName(__FILE__).c_str(), arrayName, procName, line);
                        print(1, "  this functionality has not supported yet\nSTOP\n");

                        string message;
                        printToBuf(message, "array '%s' in function '%s' is not a private, this functionality has not supported yet", arrayName, procName);
                        currMessages->push_back(Messages(ERROR, line, message));

                        throw(-1);
                    }
                }
            }
        }
        parList = parList->rhs();
    }
}

static set<string> getPrivatesFromModule(SgStatement *mod, 
                                         map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                         map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
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
            tryToFindPrivateInAttributes(mod, declaratedArrays, declaratedArraysSt, privates);
        mod = mod->lexNext();
    }
    return privates;
}

extern map<DIST::Array*, std::tuple<int, string, string>> tableOfUniqNamesByArray;
static map<LoopGraph*, map<DIST::Array*, const ArrayInfo*>> 
       convertLoopInfo(const map<SgForStmt*, map<SgSymbol*, ArrayInfo>> &loopInfo, 
                       const map<int, LoopGraph*> &sortedLoopGraph,
                       const set<string> &privateArrays,
                       const map<string, SgStatement*> &commonBlocks,
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

        const map<SgSymbol*, ArrayInfo> &toConvert = it->second;
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
            }
        }
        outInfo[itGraph->second] = toAdd;
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
                tryToFindPrivateInAttributes(decl, declaratedArrays, declaratedArraysSt, privatesVars);
            }
        }
    }

    fillPrivatesFromDecl(ex->rhs(), delcsSymbViewed, delcsStatViewed, declaratedArrays, declaratedArraysSt, privatesVars);
    fillPrivatesFromDecl(ex->lhs(), delcsSymbViewed, delcsStatViewed, declaratedArrays, declaratedArraysSt, privatesVars);
}

extern void createMapLoopGraph(std::map<int, LoopGraph*> &sortedLoopGraph, const std::vector<LoopGraph*> *loopGraph);
void loopAnalyzer(SgFile *file, vector<ParallelRegion*> regions, map<tuple<int, string, string>, DIST::Array*> &createdArrays, 
                  vector<Messages> &messagesForFile, REGIME regime, const vector<FuncInfo*> &funcInfo, 
                  map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                  map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                  const map<DIST::Array*, set<DIST::Array*>> &arrayLinksByFuncCalls,
                  vector<LoopGraph*> *loopGraph)
{

    currMessages = &messagesForFile;
    currRegime = regime;

    map<string, SgStatement*> commonBlocks;
    map<int, LoopGraph*> sortedLoopGraph;
    map<int, pair<SgForStmt*, set<string>>> allLoops;

    createMapLoopGraph(sortedLoopGraph, loopGraph);

    int funcNum = file->numberOfFunctions();
    print(PRINT_PROF_INFO,"functions num in file = %d\n", funcNum);

    vector<SgStatement*> modules;
    findModulesInFile(file, modules);

    map<string, SgStatement*> modulesByName;
    for (int i = 0; i < modules.size(); ++i)
        modulesByName[modules[i]->symbol()->identifier()] = modules[i];

    map<string, set<string>> privatesByModule;
    for (int i = 0; i < modules.size(); ++i)
        privatesByModule[modules[i]->symbol()->identifier()] = getPrivatesFromModule(modules[i], declaratedArrays, declaratedArraysSt, modulesByName);

    for (int i = 0; i < funcNum; ++i)
    {
        set<SgSymbol*> delcsSymbViewed;
        set<SgStatement*> delcsStatViewed;

        if (funcInfo[i]->doNotAnalyze)
            continue;

        map<SgForStmt*, map<SgSymbol*, ArrayInfo>> loopInfo;
        set<string> privatesVars;

        SgStatement *st = file->functions(i);
        if (st->variant() == PROG_HEDR)
        {
            SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
            print(PRINT_PROF_INFO, "*** Program <%s> started at line %d / %s\n", progH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == PROC_HEDR)
        {
            SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
            print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", procH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        else if (st->variant() == FUNC_HEDR)
        {
            SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
            print(PRINT_PROF_INFO, "*** Function <%s> started at line %d / %s\n", funcH->symbol()->identifier(), st->lineNumber(), st->fileName());
        }
        getCommonBlocksRef(commonBlocks, st, st->lastNodeOfStmt());
        print(PRINT_PROF_INFO, "  number of common blocks %d\n", (int)commonBlocks.size());
                
        SgStatement *lastNode = st->lastNodeOfStmt();
        vector<SgForStmt*> parentLoops;

        //For remote access
        pair<SgForStmt*, LoopGraph*> *under_dvm_dir = NULL;
        map<string, SgArrayRefExp*> uniqRemotes;

        startLineControl(file->filename(), st->lineNumber(), lastNode->lineNumber());
        bool breakLineControl = false;

        while (st != lastNode)
        {
#if _WIN32 && NDEBUG
            if (passDone == 2)
                throw boost::thread_interrupted();
#endif
            if (st == NULL)
            {
                string message;
                printToBuf(message, "internal error in analysis, parallel directives will not be generated for this file!");
                currMessages->push_back(Messages(ERROR, 1, message));

                print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");                
                break;
            }
            else if (checkThisLine(st->fileName(), st->lineNumber()) == -1)
            {
                string message;
                printToBuf(message, "Internal error in analysis, parallel directives will not be generated for this file!");
                currMessages->push_back(Messages(ERROR, 1, message));

                print(1, "Internal error in analysis, parallel directives will not be generated for this file!\n");
                breakLineControl = true;
                break;
            }

            ParallelRegion *currReg = getRegionByLine(regions, st->fileName(), st->lineNumber());
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
                tryToFindPrivateInAttributes(st, declaratedArrays, declaratedArraysSt, privatesVars);
                
                if (PRINT_LOOP_STRUCT)
                    printBlanks(2, (int)parentLoops.size());
                print(PRINT_LOOP_STRUCT, "FOR NODE on line %d\n", st->lineNumber());

                parentLoops.push_back((SgForStmt*)st);
                
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
                        allLoops[contrlParent->lineNumber()] = make_pair((SgForStmt*)contrlParent, privatesVars);
                        parentLoops.pop_back();

                        if (regime == REMOTE_ACC)
                        {
                            if (under_dvm_dir)
                            {
                                if (contrlParent == under_dvm_dir->first)
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
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), LEFT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph);
                if (st->expr(1))
                    findArrayRef(parentLoops, st->expr(1), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph);

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
                            fillVars(st->expr(0), { DDOT }, ddots);
                            fillVars(st->expr(1), { DDOT }, ddots);

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
                                createRemoteDir<1>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages);
                        }
                    }
                }
            }
            else if (currV == IF_NODE || currV == ELSEIF_NODE || currV == LOGIF_NODE || currV == SWITCH_NODE)
            {
                if (st->expr(0))
                {
                    findArrayRef(parentLoops, st->expr(0), st->lineNumber(), RIGHT, loopInfo, st->lineNumber(), privatesVars, sortedLoopGraph);
                    if (regime == REMOTE_ACC)
                    {
                        const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();

                        if (under_dvm_dir == NULL)
                            createRemoteDir<0>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages);
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
                    printToBuf(message, "Module with name '%s' must in file", st->symbol()->identifier());
                    currMessages->push_back(Messages(ERROR, st->lineNumber(), message));

                    print(1, "Module at line %d with name '%s' must in file\n", st->lineNumber(), st->symbol()->identifier());
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                for (auto it = itF->second.begin(); it != itF->second.end(); ++it)
                    privatesVars.insert(*it);
            }
            else
            {
                tryToFindPrivateInAttributes(st, declaratedArrays, declaratedArraysSt, privatesVars);

                if (isDVM_stat(st) == false)
                {
                    if (isSgExecutableStatement(st) && st->expr(0) && regime == REMOTE_ACC &&
                        (currV == SWITCH_NODE || currV == FORALL_STAT || currV == WHILE_NODE ||
                         currV == WHERE_NODE || currV == ALLDO_NODE || currV == ARITHIF_NODE ||
                         currV == ASSGOTO_NODE || currV == COMGOTO_NODE))
                    {
                        const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();
                        if (under_dvm_dir == NULL)
                            createRemoteDir<0>(st, sortedLoopGraph, allArrays, currReg->GetDataDir(), currReg->GetCurrentVariant(), currReg->GetId(), *currMessages);
                    }
                }
            }

            st = st->lexNext();
        }
        
        if (breakLineControl)
            return;

        if (regime == DATA_DISTR)
        {
            auto convertedLoopInfo = convertLoopInfo(loopInfo, sortedLoopGraph, privatesVars, commonBlocks, declaratedArrays, arrayLinksByFuncCalls, createdArrays);
            processLoopInformationForFunction(convertedLoopInfo);

            //find dependencies for loops in function
            initAnnotationsSysExt(0);
            set<SgStatement*> funcWasInit;
            map<SgExpression*, string> collection;
            for (auto it = convertedLoopInfo.begin(); it != convertedLoopInfo.end(); ++it)
                tryToFindDependencies(it->first, allLoops, funcWasInit, file, regions, currMessages, collection);
                        
            addToDistributionGraph(convertedLoopInfo, arrayLinksByFuncCalls);
        }
        else if (regime == COMP_DISTR)
            createParallelDirectives(loopInfo, regions, createdArrays, commonBlocks, sortedLoopGraph, arrayLinksByFuncCalls);
        
        print(PRINT_PROF_INFO, "Function ended\n");
    }     
}

static void findArrayRefs(SgExpression *ex, 
                          const map<string, SgStatement*> &commonBlocks, 
                          const vector<SgStatement*> &modules,
                          map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                          map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt,
                          const set<string> &privates, bool isExecutable, SgStatement *declSt, 
                          const string &currFunctionName, bool isWrite)
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
                SgStatement *decl = isExecutable ? declaratedInStmt(symb) : declSt;

                auto uniqKey = getUniqName(commonBlocks, decl, symb);
                pair<int, string> arrayLocation;
                if (symb != ex->symbol())
                    arrayLocation = make_pair(2, "MODULE"); //TODO: find module name
                else if (get<1>(uniqKey).find("common_") != string::npos)
                    arrayLocation = make_pair(1, get<1>(uniqKey).substr(strlen("common_")));
                else
                    arrayLocation = make_pair(0, currFunctionName);

                auto itNew = declaratedArrays.find(uniqKey);
                if (itNew == declaratedArrays.end())
                {
                    DIST::Array *arrayToAdd = new DIST::Array(getShortName(uniqKey), symb->identifier(), ((SgArrayType*)(symb->type()))->dimension(), 
                                                              getUniqArrayId(), decl->fileName(), decl->lineNumber(), arrayLocation);

                    if (privates.find(symb->identifier()) != privates.end())
                    {
                        itNew = declaratedArrays.insert(itNew, make_pair(uniqKey, make_pair(arrayToAdd, new DIST::ArrayAccessInfo())));
                        arrayToAdd->SetNonDistributeFlag(true);
                    }
                    else
                    {
                        itNew = declaratedArrays.insert(itNew, make_pair(uniqKey, make_pair(arrayToAdd, new DIST::ArrayAccessInfo())));
                        arrayToAdd->SetNonDistributeFlag(false);
                    }                    
                    
                    vector<pair<int, int>> sizes;
                    getArraySizes(sizes, symb, decl);
                    arrayToAdd->SetSizes(sizes);

                    tableOfUniqNamesByArray[arrayToAdd] = uniqKey;
                }

                if (isExecutable)
                    itNew->second.second->AddAccessInfo(make_pair(declSt->lineNumber(), isWrite ? 1 : 0), declSt->fileName());

                auto itDecl = declaratedArraysSt.find(decl);
                if (itDecl == declaratedArraysSt.end())
                    itDecl = declaratedArraysSt.insert(itDecl, make_pair(decl, set<tuple<int, string, string>>()));
                itDecl->second.insert(uniqKey);
            }
        }
    }

    if (ex->lhs())
        findArrayRefs(ex->lhs(), commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, isExecutable, declSt, currFunctionName, isWrite);
    if (ex->rhs())
        findArrayRefs(ex->rhs(), commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, isExecutable, declSt, currFunctionName, isWrite);
}

void getAllDeclaratedArrays(SgFile *file, map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                            map<SgStatement*, set<tuple<int, string, string>>> &declaratedArraysSt)
{
    vector<SgStatement*> modules;
    findModulesInFile(file, modules);

    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {        
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        map<string, SgStatement*> commonBlocks;
        const string currFunctionName = st->symbol()->identifier();

        getCommonBlocksRef(commonBlocks, st, lastNode);
        set<string> privates;
        
        while (st != lastNode)
        {   
            //after SPF preprocessing 
            for (int z = 0; z < st->numberOfAttributes(); ++z)
                if (st->attributeType(z) == SPF_ANALYSIS_DIR)
                    fillPrivatesFromComment((SgStatement *)(st->getAttribute(z)->getAttributeData()), privates);

            //before SPF preprocessing 
            if (st->variant() == SPF_ANALYSIS_DIR)
                fillPrivatesFromComment(st, privates);

            //temporary skip decl statements
            //TODO: add IPO analysis for R/WR state for calls and functions
            //TODO: improve WR analysis
            if (isSgExecutableStatement(st))
                for (int i = 0; i < 3; ++i)
                    findArrayRefs(st->expr(i), commonBlocks, modules, declaratedArrays, declaratedArraysSt, privates, 
                                  true, st, currFunctionName, (st->variant() == ASSIGN_STAT && i == 0) ? true : false);
            st = st->lexNext();
        }
    }
}

#undef PRINT_ARRAY_ARCS
#undef PRINT_LOOP_STRUCT
#undef PRINT_PROF_INFO
#undef FIRST
#undef SECOND
#undef THIRD