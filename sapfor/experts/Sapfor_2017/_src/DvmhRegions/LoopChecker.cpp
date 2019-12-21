//
// Created by Vladislav Volodkin on 12/20/19.
//

#include "LoopChecker.h"


using namespace std;


void LoopChecker::updateLoopGraph(const map<string, FuncInfo*> &allFuncs)
{
    for (auto &loopNode : loopGraph)
        updateLoopNode(loopNode, allFuncs);
}

LoopCheckResults LoopChecker::updateLoopNode(LoopGraph *loop, const map<string, FuncInfo*> &allFuncs)
{
    LoopCheckResults loopChecks = checkLoopForPurenessAndIO(loop, allFuncs);
    bool hasImpureCalls = loopChecks.hasImpureCalls;
    bool usesIO = loopChecks.usesIO;

    if (loopChecks.linesOfIO.size() && usesIO)
        for (auto& elem : loopChecks.linesOfIO)
            loop->linesOfIO.push_back(elem);

    for (auto &nestedLoop : loop->children)
    {
        loopChecks = updateLoopNode(nestedLoop, allFuncs);
        hasImpureCalls |= loopChecks.hasImpureCalls;
        usesIO |= loopChecks.usesIO;
    }

    loop->hasImpureCalls |= hasImpureCalls;
    loop->hasPrints |= usesIO;

    return LoopCheckResults(loop->hasPrints, loop->hasImpureCalls);
}


// checks loop node itself, doesn't check its children
LoopCheckResults LoopChecker::checkLoopForPurenessAndIO(LoopGraph *loopNode, const map<string, FuncInfo*> &allFuncs)
{
    LoopCheckResults loopCheckResults;

    for (auto &nameAndLineOfFuncCalled : loopNode->calls)
    {
        FuncInfo *calledFuncInfo = NULL;

        auto it = allFuncs.find(nameAndLineOfFuncCalled.first);
        if (it != allFuncs.end())
            calledFuncInfo = it->second;

        if (!calledFuncInfo)
        {
            if (isIntrinsicFunctionName(nameAndLineOfFuncCalled.first.c_str()))
                continue;
            else
            { // if funcInfo was not found assume func to be impure
                loopCheckResults.hasImpureCalls = true;
                loopCheckResults.usesIO = true;
                loopCheckResults.linesOfIO.push_back(nameAndLineOfFuncCalled.second);
            }
            continue;
        }

        if (!calledFuncInfo->isPure)
            loopCheckResults.hasImpureCalls = true;

        if (calledFuncInfo->usesIO())
        {
            loopCheckResults.usesIO = true;
            loopCheckResults.linesOfIO.push_back(nameAndLineOfFuncCalled.second);
        }
    }

    return loopCheckResults;
}
