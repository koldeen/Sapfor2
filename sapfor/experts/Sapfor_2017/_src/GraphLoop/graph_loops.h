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
        hasUnknownArrayAssignes = false;
        hasNonRectangularBounds = false;
        hasIndirectAccess = false;
        directive = NULL;
        directiveForLoop = NULL;
        region = NULL;
        countOfIters = 0;
        countOfIterNested = 1;
        loop = NULL;
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
        return hasUnknownArrayDep || hasUnknownScalarDep || hasGoto || hasPrints || (hasConflicts.size() != 0) || hasStops || hasUnknownArrayAssignes || hasNonRectangularBounds || hasIndirectAccess;
    }
    
    void addConflictMessages(std::vector<Messages> *messages)
    {
        if (hasUnknownArrayDep)
            messages->push_back(Messages(NOTE, lineNum, "unknown array dependency prevents parallelization of this loop"));
        if (hasUnknownScalarDep)
            messages->push_back(Messages(NOTE, lineNum, "unknown scalar dependency prevents parallelization of this loop"));
        if (hasGoto)
            messages->push_back(Messages(NOTE, lineNum, "internal/external goto operations prevent parallelization of this loop"));
        if (hasPrints)
            messages->push_back(Messages(NOTE, lineNum, "IO operations prevent parallelization of this loop"));
        if (hasStops)
            messages->push_back(Messages(NOTE, lineNum, "stop operations prevent parallelization of this loop"));
        if (hasConflicts.size() != 0)
            messages->push_back(Messages(NOTE, lineNum, "conflict writes operations prevent parallelization of this loop"));
        if (hasUnknownArrayAssignes)
            messages->push_back(Messages(NOTE, lineNum, "unknown array reference for writes prevent parallelization of this loop"));
        if (hasNonRectangularBounds)
            messages->push_back(Messages(NOTE, lineNum, "non rectangular bounds prevent parallelization of this loop"));
        if (hasIndirectAccess)
            messages->push_back(Messages(NOTE, lineNum, "indirect access by distributed array prevents parallelization of this loop"));
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
        if (directive)
            delete directive;
        directive = parDirective;
        return directive;
    }

    void setRegionToChilds()
    {
        for (auto &loop : childs)
        {
            loop->region = region;
            loop->setRegionToChilds();
        }
    }

public:
    int lineNum;
    int lineNumAfterLoop;
    std::string fileName;
    int perfectLoop;
    int countOfIters;
    double countOfIterNested;

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

    bool hasUnknownArrayAssignes;
 
    bool hasNonRectangularBounds;

    bool hasIndirectAccess;

    std::vector<LoopGraph*> childs;
    std::vector<std::pair<std::string, int>> calls;
    
    // agregated read and write operations by arrays
    std::set<DIST::Array*> readOpsArray;
    std::map<DIST::Array*, std::pair<std::vector<ArrayOp>, std::vector<bool>>> readOps;
    std::map<DIST::Array*, std::vector<ArrayOp>> writeOps;
    std::map<DIST::Array*, bool> hasConflicts;
    
    std::set<DIST::Array*> acrossOutAttribute;

    ParallelDirective *directive;        // united directive for nested loops
    ParallelDirective *directiveForLoop; // part of directive for loop
    ParallelRegion *region;

    Statement *loop;
};

void processLoopInformationForFunction(std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo);
void addToDistributionGraph(const std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>> &loopInfo, std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);

void convertToString(const LoopGraph *currLoop, std::string &result);
int printLoopGraph(const char *fileName, const std::map<std::string, std::vector<LoopGraph*>> &loopGraph);
void checkCountOfIter(std::map<std::string, std::vector<LoopGraph*>> &loopGraph, std::map<std::string, std::vector<Messages>> &SPF_messages);