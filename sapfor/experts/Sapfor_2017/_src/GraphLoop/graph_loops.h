#pragma once

#include <vector>
#include <string>
#include <map>

#include "../Distribution/DvmhDirective.h"
#include "../ParallelizationRegions/ParRegions.h"
#include "../types.h"

struct LoopGraph
{
private:
    std::vector<std::pair<DIST::Array*, DistrVariant*>> redistributeRules;

public:
    LoopGraph()
    {
        lineNumAfterLoop = lineNum = -1;
        perfectLoop = 0;
        hasGoto = false;
        hasPrints = false;
        hasUnknownArrayDep = false;
        hasUnknownScalarDep = false;
        hasUnknownArrayAssigns = false;
        hasNonRectangularBounds = false;
        hasIndirectAccess = false;
        withoutDistributedArrays = false;
        hasWritesToNonDistribute = false;
        directive = NULL;
        oldDirective = NULL;
        directiveForLoop = NULL;
        region = NULL;
        countOfIters = 0;
        countOfIterNested = 1;
        loop = NULL;
        parent = NULL;
        userDvmDirective = NULL;
        startVal = endVal = stepVal = -1;
    }

    ~LoopGraph()
    {
        if (directive != NULL)
            delete directive;

        if (directiveForLoop != NULL)
            delete directiveForLoop;

        for (int i = 0; i < childs.size(); ++i)
            delete childs[i];

        calls.clear();
        readOpsArray.clear();
        readOps.clear();
        writeOps.clear();
        hasConflicts.clear();
        acrossOutAttribute.clear();
    }

    bool hasLimitsToParallel() const
    {
        return hasUnknownArrayDep || hasUnknownScalarDep || hasGoto || hasPrints || (hasConflicts.size() != 0) || hasStops || 
               hasUnknownArrayAssigns || hasNonRectangularBounds || hasIndirectAccess || hasWritesToNonDistribute;
    }
    
    void addConflictMessages(std::vector<Messages> *messages)
    {
        if (hasUnknownArrayDep)
            messages->push_back(Messages(NOTE, lineNum, "unknown array dependency prevents parallelization of this loop", 3006));
        if (hasUnknownScalarDep)
            messages->push_back(Messages(NOTE, lineNum, "unknown scalar dependency prevents parallelization of this loop", 3006));
        if (hasGoto)
            messages->push_back(Messages(NOTE, lineNum, "internal/external goto operations prevent parallelization of this loop", 3006));
        if (hasPrints)
            messages->push_back(Messages(NOTE, lineNum, "IO operations prevent parallelization of this loop", 3006));
        if (hasStops)
            messages->push_back(Messages(NOTE, lineNum, "stop operations prevent parallelization of this loop", 3006));
        if (hasConflicts.size() != 0)
            messages->push_back(Messages(NOTE, lineNum, "conflict writes operations prevent parallelization of this loop", 3006));
        if (hasUnknownArrayAssigns)
            messages->push_back(Messages(NOTE, lineNum, "unknown array reference for writes prevent parallelization of this loop", 3006));
        if (hasNonRectangularBounds)
            messages->push_back(Messages(NOTE, lineNum, "non rectangular bounds prevent parallelization of this loop", 3006));
        if (hasIndirectAccess)
            messages->push_back(Messages(NOTE, lineNum, "indirect access by distributed array prevents parallelization of this loop", 3006));
        if (hasWritesToNonDistribute)
            messages->push_back(Messages(NOTE, lineNum, "writes to non distributed array prevents parallelization of this loop", 3006));
    }

    void setNewRedistributeRules(const std::vector<std::pair<DIST::Array*, DistrVariant*>> &newRedistributeRules)
    {
        // set to top and for all childs
        redistributeRules = newRedistributeRules;
        for (int i = 0; i < childs.size(); ++i)
            childs[i]->setNewRedistributeRules(newRedistributeRules);
    }

    DistrVariant* getRedistributeRule(const DIST::Array *arrayT) const
    {
        DistrVariant *retVal = NULL;

        for (int i = 0; i < redistributeRules.size(); ++i)
        {
            if (redistributeRules[i].first == arrayT)
            {
                retVal = redistributeRules[i].second;
                break;
            }
        }

        return retVal;
    }

    ParallelDirective* recalculateParallelDirective()
    {
        std::vector<ParallelDirective*> baseDirs(perfectLoop);
        LoopGraph *next = this;
        for (int z = 0; z < perfectLoop; ++z)
        {
            baseDirs[z] = next->directiveForLoop;
            if (z != perfectLoop - 1)
                next = next->childs[0];
        }

        ParallelDirective *parDirective = baseDirs[0];
        for (int z = 1; z < baseDirs.size(); ++z)
        {
            ParallelDirective *old = parDirective;
            parDirective = *parDirective + *baseDirs[z];

            if (z != 1)
                delete old;
        }

        oldDirective = directive;
        directive = parDirective;
        return directive;
    }

    void restoreDirective()
    {
        if (oldDirective)
        {
            delete directive;
            directive = oldDirective;
        }

        for (int i = 0; i < childs.size(); ++i)
            childs[i]->restoreDirective();
    }

    void setRegionToChilds()
    {
        for (auto &loop : childs)
        {
            loop->region = region;
            loop->setRegionToChilds();
        }
    }

    void recalculatePerfect();

    void setWithOutDistrFlagToFalse()
    {
        for (auto &loop : childs)
        {
            loop->withoutDistributedArrays = false;
            loop->setWithOutDistrFlagToFalse();
        }
    }

    std::string genLoopArrayName(const std::string &funcName) const
    {
        return funcName + "_loop_" + std::to_string(lineNum);
    }

    std::set<DIST::Array*> getAllArraysInLoop()
    {
        std::set<DIST::Array*> retVal(readOpsArray);
        for (auto &elem : writeOps)
            retVal.insert(elem.first);
        return retVal;
    }

public:
    int lineNum;
    int lineNumAfterLoop;
    std::string fileName;
    int perfectLoop;
    int countOfIters;
    double countOfIterNested;

    int calculatedCountOfIters; // save calculated

    int startVal;
    int endVal;
    int stepVal;

    bool hasGoto;
    std::vector<int> linesOfInternalGoTo;
    std::vector<int> linesOfExternalGoTo;

    bool hasPrints;
    std::vector<int> linesOfIO;

    bool hasStops;
    std::vector<int> linesOfStop;

    bool hasUnknownScalarDep;
    std::vector<int> linesOfScalarDep;
    
    bool hasUnknownArrayDep;

    bool hasUnknownArrayAssigns;
 
    bool hasNonRectangularBounds;

    bool hasIndirectAccess;

    bool hasWritesToNonDistribute;

    bool withoutDistributedArrays;

    std::vector<LoopGraph*> childs; //fixme typo 'children'
    LoopGraph *parent;

    std::vector<std::pair<std::string, int>> calls;
    
    // agregated read and write operations by arrays
    std::set<DIST::Array*> readOpsArray;
    std::map<DIST::Array*, std::pair<std::vector<ArrayOp>, std::vector<bool>>> readOps;
    std::map<DIST::Array*, std::vector<ArrayOp>> writeOps;
    std::map<DIST::Array*, bool> hasConflicts;
    
    std::set<DIST::Array*> acrossOutAttribute;

    ParallelDirective *directive;        // united directive for nested loops
    ParallelDirective *oldDirective;     // save old directive for reverse
    ParallelDirective *directiveForLoop; // part of directive for loop
    Statement *userDvmDirective;         // user's DVM PARALLEL directive

    ParallelRegion *region;

    Statement *loop;
};

void processLoopInformationForFunction(std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo);
void addToDistributionGraph(const std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo, std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);
bool addToDistributionGraph(const LoopGraph* loopInfo, const std::string &inFunction);

void convertToString(const LoopGraph *currLoop, std::string &result);
int printLoopGraph(const char *fileName, const std::map<std::string, std::vector<LoopGraph*>> &loopGraph);
void checkCountOfIter(std::map<std::string, std::vector<LoopGraph*>> &loopGraph, std::map<std::string, std::vector<Messages>> &SPF_messages);

void getRealArrayRefs(DIST::Array *addTo, DIST::Array *curr, std::set<DIST::Array*> &realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);
void getAllArrayRefs(DIST::Array *addTo, DIST::Array *curr, std::set<DIST::Array*> &realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);

void getRealArrayRefs(DIST::Array *addTo, DIST::Array *curr, std::set<DIST::Array*> &realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);
void getAllArrayRefs(DIST::Array *addTo, DIST::Array *curr, std::set<DIST::Array*> &realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);