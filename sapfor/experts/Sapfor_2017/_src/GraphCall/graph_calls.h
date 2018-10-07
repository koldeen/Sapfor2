#pragma once

#include <string>
#include <set>

#include "../Sapfor.h"
#include "../Utils/AstWrapper.h"
#include "../Utils/utils.h"
#include "../LoopAnalyzer/shadow.h"

typedef enum parF { NONE_T, ARRAY_T, 
                    SCALAR_INT_T, SCALAR_FLOAT_T, SCALAR_DOUBLE_T, SCALAR_CHAR_T, SCALAR_BOOL_T,
                    UNKNOWN_T } paramType;
struct FuncParam
{
    void init(const int numPar)
    {
        countOfPars = numPar;
        if (numPar)
        {
            parameters.resize(numPar);
            parametersT.resize(numPar);
            inout_types.resize(numPar);
            std::fill(parametersT.begin(), parametersT.end(), NONE_T);
            std::fill(inout_types.begin(), inout_types.end(), 0);
        }
    }

    std::vector<std::string> identificators;
    std::vector<void*> parameters;
    std::vector<paramType> parametersT;
    std::vector<int> inout_types;
    int countOfPars;
};

struct NestedFuncCall 
{
    std::string CalledFuncName;
    std::vector<std::vector<int>> NoOfParamUsedForCall;

    NestedFuncCall(std::string funcName) : CalledFuncName(funcName) { }

    NestedFuncCall(std::string funcName, int ParsNum) :
        CalledFuncName(funcName),
        NoOfParamUsedForCall(std::vector<std::vector<int>>(ParsNum))
    { }
};

struct FuncInfo
{
    std::string funcName;
    std::pair<int, int> linesNum;
    std::string fileName;
    Statement *funcPointer;
    
    std::set<std::string> callsFrom; //calls from this function
    std::vector<std::pair<std::string, int>> detailCallsFrom; // <name, line>
    std::vector<std::pair<void*, int>> pointerDetailCallsFrom; // SgStatement for PROC_STAT and SgExpression for FUNC_CALL
    std::vector<FuncParam> actualParams;
    std::map<std::string, std::set<std::string>> commonBlocks;

    std::vector<FuncInfo*> callsTo; //calls of this function
    FuncParam funcParams;
    std::vector<bool> isParamUsedAsIndex;
    std::vector<NestedFuncCall> funcsCalledFromThis; // size = amount of calls in this func;
                                                     // if (FuncsCalledFromThis[func_call_idx].
                                                    // NoOfParamUsedForCall.size() == 0) - no params of cur func used

    ShadowNode *shadowTree;
    std::map<void*, ShadowNode*> allShadowNodes;

    std::set<DIST::Array*> writeToArray;

    bool doNotInline;
    bool doNotAnalyze;
    bool needToInline;
    bool deadFunction;

    int inRegion; // 0 - none, 1 - explicit, 2 - implicit, 3 - indirect

    FuncInfo() :
        doNotInline(false), funcPointer(NULL), doNotAnalyze(false), needToInline(false), deadFunction(false), inRegion(0) { }

    FuncInfo(std::string &funcName, const std::pair<int, int> &lineNum) :
        funcName(funcName), linesNum(lineNum), doNotInline(false), funcPointer(NULL),
        doNotAnalyze(false), needToInline(false), deadFunction(false), inRegion(0) { }

    FuncInfo(std::string &funcName, const std::pair<int, int> &lineNum, Statement *pointer) :
        funcName(funcName), linesNum(lineNum), doNotInline(false), funcPointer(pointer),
        doNotAnalyze(false), needToInline(false), deadFunction(false), inRegion(0) { fileName = pointer->fileName(); }

    std::vector<std::pair<void*, int>> GetDetailedCallInfo(const std::string &funcName)
    {
        std::vector<std::pair<void*, int>> result;
        for (int i = 0; i < pointerDetailCallsFrom.size(); ++i)
        {
            if (detailCallsFrom[i].first == funcName)
                result.push_back(pointerDetailCallsFrom[i]);
        }
        return result;
    }
};

struct CallV
{
    std::string fName;
    std::string fileName;
    bool isMain;
    int inRegion;

    CallV() : inRegion(0) { }

    CallV(const std::string &fName) :
        fName(fName), fileName(""), isMain(false), inRegion(0)
    { }

    CallV(const std::string &fName, const std::string &fileName, bool isMain) : 
        fName(fName), fileName(fileName), isMain(isMain), inRegion(0)
    { }

    std::string to_string()
    {
        return fName + "@" + fileName + "@" + (isMain ? "1" : "0") + "@" + std::to_string(inRegion);
    }
};

