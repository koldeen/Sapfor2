#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>

#include "../Utils/errors.h"
#include "../Utils/types.h"
#include "../Distribution/DvmhDirective.h"
#include "../Distribution/Distribution.h"

struct DistrVariant;
struct ParallelDirective;
struct ParallelRegion;
class Statement;
struct FuncInfo;

namespace Distribution
{
    class Array;
}
namespace DIST = Distribution;

void getRealArrayRefs(DIST::Array* addTo, DIST::Array* curr, std::set<DIST::Array*>& realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);
void getAllArrayRefs(DIST::Array* addTo, DIST::Array* curr, std::set<DIST::Array*>& realArrayRefs, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);

struct LoopGraph
{
private:
    std::vector<std::pair<DIST::Array*, DistrVariant*>> redistributeRules;
    LoopGraph* needToSwapWith;

    //for local directive creating in MPI mode
    DIST::GraphCSR<int, double, attrType> accessGraph;
    DIST::GraphCSR<int, double, attrType> reducedAccessGraph;    
    DataDirective dataDirectives;
    //

public:
    LoopGraph()
    {
        lineNumAfterLoop = lineNum = altLineNum = -1;
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
        hasUnknownDistributedMap = false;
        hasDifferentAlignRules = false;
        hasNonPureProcedures = false;
        hasDvmIntervals = false;
        hasImpureCalls = false;
        hasStops = false;
        directive = NULL;
        oldDirective = NULL;
        directiveForLoop = NULL;
        region = NULL;
        needToSwapWith = NULL;
        countOfIters = 0;
        countOfIterNested = 1;
        loop = NULL;
        parent = NULL;
        userDvmDirective = NULL;
        startVal = endVal = stepVal = -1;
        calculatedCountOfIters = 0;
        executionTimeInSec = -1.0;
        inDvmhRegion = 0;
        isFor = false;
        inCanonicalFrom = false;
    }

    ~LoopGraph()
    {
        needToSwapWith = NULL;
        if (directive != NULL)
            delete directive;

        if (directiveForLoop != NULL)
            delete directiveForLoop;

        for (int i = 0; i < children.size(); ++i)
            delete children[i];

        calls.clear();
        readOpsArray.clear();
        readOps.clear();
        writeOps.clear();
        hasConflicts.clear();
        acrossOutAttribute.clear();
        accessGraph.ClearGraphCSR();
        reducedAccessGraph.ClearGraphCSR();
    }

    void setForSwap(LoopGraph* with) { needToSwapWith = with; }

    LoopGraph* getForSwap() const { return needToSwapWith; }

    void clearForSwap() 
    {
        for (auto& ch : children)
            ch->clearForSwap();
        needToSwapWith = NULL; 
    }

    bool hasLimitsToParallel() const
    {
        return hasUnknownArrayDep || hasUnknownScalarDep || hasGoto || hasPrints || (hasConflicts.size() != 0) || hasStops || hasNonPureProcedures ||
               hasUnknownArrayAssigns || hasNonRectangularBounds || hasIndirectAccess || hasWritesToNonDistribute || hasDifferentAlignRules || hasDvmIntervals ||
               !isFor;
    }
    
    bool hasLimitsToSplit() const
    {
        return hasUnknownArrayDep || hasUnknownScalarDep || hasGoto || hasStops || !isFor || hasPrints;
    }

    void addConflictMessages(std::vector<Messages> *messages)
    {
        const int line = altLineNum > 0 ? altLineNum : lineNum;
        if (hasUnknownArrayDep)
            messages->push_back(Messages(NOTE, line, R113, L"unknown array dependency prevents parallelization of this loop", 3006));

        if (hasUnknownScalarDep)
            messages->push_back(Messages(NOTE, line, R114, L"unknown scalar dependency prevents parallelization of this loop", 3006));

        if (hasGoto)
            messages->push_back(Messages(NOTE, line, R115, L"internal/external moves via GOTO or EXIT operations prevent parallelization of this loop", 3006));

        if (hasPrints)
            messages->push_back(Messages(NOTE, line, R116, L"IO operations prevent parallelization of this loop", 3006));

        if (hasStops)
            messages->push_back(Messages(NOTE, line, R117, L"stop operations prevent parallelization of this loop", 3006));

        if (hasConflicts.size() != 0)
            messages->push_back(Messages(NOTE, line, R118, L"conflict writes operations prevent parallelization of this loop", 3006));

        if (hasUnknownArrayAssigns)
            messages->push_back(Messages(NOTE, line, R119, L"unknown array reference for writes prevent parallelization of this loop", 3006));

        if (hasNonRectangularBounds)
            messages->push_back(Messages(NOTE, line, R144, L"non rectangular bounds prevent parallelization of this loop", 3006));

        if (hasIndirectAccess)
            messages->push_back(Messages(NOTE, line, R120, L"indirect access by distributed array prevents parallelization of this loop", 3006));

        if (hasWritesToNonDistribute)
            messages->push_back(Messages(NOTE, line, R121, L"writes to non distributed array prevents parallelization of this loop", 3006));

        if (hasDifferentAlignRules)
            messages->push_back(Messages(NOTE, line, R122, L"different aligns between writes to distributed array prevents parallelization of this loop", 3006));

        if (hasNonPureProcedures)
            messages->push_back(Messages(NOTE, line, R123, L"non pure procedures prevent parallelization of this loop", 3006));

        if (hasDvmIntervals)
            messages->push_back(Messages(NOTE, line, R145, L"DVM intervals prevent parallelization of this loop", 3006));

        if (!isFor || !inCanonicalFrom)
            messages->push_back(Messages(NOTE, line, R178, L"This type of loop is not supported by the system", 3006));
    }

    void setNewRedistributeRules(const std::vector<std::pair<DIST::Array*, DistrVariant*>> &newRedistributeRules)
    {
        // set to top and for all childs
        redistributeRules = newRedistributeRules;
        for (int i = 0; i < children.size(); ++i)
            children[i]->setNewRedistributeRules(newRedistributeRules);
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
                next = next->children[0];
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

        for (int i = 0; i < children.size(); ++i)
            children[i]->restoreDirective();
    }

    void setRegionToChilds()
    {
        for (auto &loop : children)
        {
            loop->region = region;
            loop->setRegionToChilds();
        }
    }

    void recalculatePerfect();

    void setWithOutDistrFlagToFalse()
    {
        for (auto &loop : children)
        {
            loop->withoutDistributedArrays = false;
            loop->setWithOutDistrFlagToFalse();
        }
    }

    void propagateUserDvmDir()
    {
        for (auto &loop : children)
        {
            if (loop->userDvmDirective == NULL)
                loop->userDvmDirective = userDvmDirective;
            loop->propagateUserDvmDir();
        }
    }

    void propagateDvmhRegion(const int flag)
    {
        for (auto& loop : children)
        {
            loop->inDvmhRegion = flag;
            loop->propagateDvmhRegion(flag);
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

    void removeNonDistrArrays()
    {
        std::set<DIST::Array*> newUsedArrays;        
        for (auto &elem : usedArrays)
            if (elem->GetNonDistributeFlagVal() == DIST::DISTR)
                newUsedArrays.insert(elem);
        usedArrays = newUsedArrays;

        std::set<DIST::Array*> newUsedArraysW;        
        for (auto &elem : usedArraysWrite)
            if (elem->GetNonDistributeFlagVal() == DIST::DISTR)
                newUsedArraysW.insert(elem);
        usedArraysWrite = newUsedArraysW;
        
        readOpsArray.clear();
        readOps.clear();
        writeOps.clear();
        hasConflicts.clear();

        for (auto &ch : children)
            ch->removeNonDistrArrays();
    }

    void removeGraphData()
    {
        accessGraph.ClearGraphCSR();
        reducedAccessGraph.ClearGraphCSR();

        for (auto& ch : children)
            ch->removeGraphData();
    }

    void clearUserDirectives();    

    bool isArrayTemplatesTheSame(const uint64_t regId, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls)
    {
        if (mpiProgram != 0)
            return true;

        std::set<DIST::Array*> usedTemplates;        
        for (auto& array : usedArrays)
        {
            std::set<DIST::Array*> realArrayRefs;
            getRealArrayRefs(array, array, realArrayRefs, arrayLinksByFuncCalls);
            for (auto& realArr : realArrayRefs)
                usedTemplates.insert(realArr->GetTemplateArray(regId));
        }

        if (usedArrays.size())
        {
            if (usedTemplates.size() == 0 || usedTemplates.size() > 1)
                return false;
        }
        return true;
    }

    bool hasParallelLoopsInChList();

    DIST::GraphCSR<int, double, attrType>& getGraphToModify() { return accessGraph; }
    const DIST::GraphCSR<int, double, attrType>& getGraph() const { return accessGraph; }

    DataDirective& getDataDirToModify() { return dataDirectives; }
    const DataDirective& getDataDir() const { return dataDirectives; }

    void reduceAccessGraph();

    void createVirtualTemplateLinks(const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls, std::map<std::string, std::vector<Messages>>& SPF_messages);
public:
    int lineNum;
    int altLineNum;
    int lineNumAfterLoop;
    std::string fileName;
    int perfectLoop;
    int countOfIters;
    double countOfIterNested;
    double executionTimeInSec;
    int calculatedCountOfIters; // save calculated

    int startVal;
    int endVal;
    int stepVal;
    std::string loopSymbol;
    std::pair<Expression*, Expression*> startEndExpr;

    bool hasGoto;
    std::vector<int> linesOfInternalGoTo;
    std::vector<int> linesOfExternalGoTo;

    bool hasPrints;
    std::vector<int> linesOfIO;

    bool hasStops;
    std::vector<int> linesOfStop;

    bool hasUnknownScalarDep;
    std::vector<int> linesOfScalarDep;
    
    bool hasImpureCalls;
    
    bool hasUnknownArrayDep;

    bool hasUnknownArrayAssigns;
 
    bool hasNonRectangularBounds;

    bool hasIndirectAccess;

    bool hasWritesToNonDistribute;

    bool withoutDistributedArrays;

    bool hasUnknownDistributedMap;

    bool hasDifferentAlignRules;

    bool hasNonPureProcedures;
    
    bool hasDvmIntervals;

    bool isFor;

    bool inCanonicalFrom;

    std::vector<LoopGraph*> children;
    std::vector<LoopGraph*> funcChildren;
    LoopGraph *parent;
    std::vector<LoopGraph*> funcParents;

    // PAIR<FUNC_NAME, LINE>
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

    std::set<DIST::Array*> usedArrays;// without NON DIST
    std::set<DIST::Array*> usedArraysAll;
    std::set<DIST::Array*> usedArraysWrite; // without NON DIST
    std::set<DIST::Array*> usedArraysWriteAll;

    int inDvmhRegion; // 0 -unknown, -1 - no, 1 - yes
};

void processLoopInformationForFunction(std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>>& loopInfo);
void addToDistributionGraph(const std::map<LoopGraph*, std::map<DIST::Array*, const ArrayInfo*>>& loopInfo, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);
bool addToDistributionGraph(const LoopGraph* loopInfo, const std::string& inFunction);

void convertToString(const LoopGraph* currLoop, std::string& result);
int printLoopGraph(const char* fileName, const std::map<std::string, std::vector<LoopGraph*>>& loopGraph, bool withRegs = false);
void checkCountOfIter(std::map<std::string, std::vector<LoopGraph*>>& loopGraph, const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo, std::map<std::string, std::vector<Messages>>& SPF_messages);

void createMapLoopGraph(const std::vector<LoopGraph*>& loops, std::map<int, LoopGraph*>& mapGraph);
void updateLoopIoAndStopsByFuncCalls(std::map<std::string, std::vector<LoopGraph*>>& loopGraph, const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo);
void checkArraysMapping(std::map<std::string, std::vector<LoopGraph*>>& loopGraph, std::map<std::string, std::vector<Messages>>& SPF_messages, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);
void filterArrayInCSRGraph(std::map<std::string, std::vector<LoopGraph*>>& loopGraph, std::map<std::string, std::vector<FuncInfo*>>& allFuncs, ParallelRegion* reg, const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls, std::map<std::string, std::vector<Messages>>& messages);
void swapLoopsForParallel(std::map<std::string, std::vector<LoopGraph*>>& loopGraph, std::map<std::string, std::vector<Messages>>& SPF_messages, const int rev);
