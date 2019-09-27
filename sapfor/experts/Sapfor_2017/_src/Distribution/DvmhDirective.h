#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

#include "Array.h"
#include "DvmhDirectiveBase.h"
#include "../Utils/AstWrapper.h"
#include "../Utils/types.h"
#include "../Utils/utils.h"

namespace Distribution
{
    template<typename vType, typename wType, typename attrType> class GraphCSR;
    template<typename vType> class Arrays;
}
namespace DIST = Distribution;

struct AlignRule : public AlignRuleBase
{
public:
    Statement* GenRule(File *file, const int variant) const;
};

struct DistrVariant : public DistrVariantBase
{
public:
    DistrVariant(const std::vector<dist> &distRule) : DistrVariantBase(distRule) { }
    void GenRule(File *file, Expression *arrayRef, const std::vector<int> &newOrder) const;
    std::vector<Expression*> GenRuleSt(File *file, const std::vector<int> &newOrder) const;
};

struct DataDirective : Directive
{
public:
    std::vector<AlignRule> alignRules;
    std::vector<std::pair<DIST::Array*, std::vector<DistrVariant>>> distrRules;
public:
    std::vector<std::pair<DIST::Array*, std::vector<DistrVariant>>> GetDistrRules() const { return distrRules; }
    void createDirstributionVariants(const std::vector<DIST::Array*> &arraysToDist);
    std::vector<std::string> GenRule(const std::vector<int> &rules) const;
    std::vector<std::string> GenAlignsRules() const;
    std::vector<AlignRule> GenAlignsRules(void*) { return alignRules; }
    std::vector<Statement*> GenRule(File *file, const std::vector<int> &rules, const int variant) const; 
    std::vector<std::vector<dist>> GenRule(const std::vector<int> &rules, int) const;
    std::vector<Statement*> GenAlignsRules(File *file, const int variant) const;
    void UpdateLinks(const std::map<DIST::Array*, DIST::Array*> &oldNewArrays)
    {
        for (int i = 0; i < distrRules.size(); ++i)
            distrRules[i].first = oldNewArrays.find(distrRules[i].first)->second;
    }

    ~DataDirective()
    {
        for (auto &elem : distrRules)
        {
            if (elem.first && elem.first->IsTemplate())
            {
                delete elem.first;
                elem.first = NULL;
            }
        }
    }
};

struct ParallelDirective : Directive
{
public:
    std::vector<std::string> parallel;
    // tuple of <varName, A, B> on A*x + B
    std::vector<std::pair<std::string, std::pair<int, int>>> on;
    DIST::Array *arrayRef; // template
    
    DIST::Array *arrayRef2;// main array in loop
    std::vector<std::pair<std::string, std::pair<int, int>>> on2;

    std::string cloneOfTemplate; // if loop has realigns before 

    std::set<Symbol*> privates;
    //                               origin_Name   uniqName                   bounds
    std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> shadowRenew;
    std::vector<std::vector<std::pair<int, int>>> shadowRenewShifts;

    //                               origin_Name   uniqName                   bounds
    std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> across;
    std::vector<std::vector<std::pair<int, int>>> acrossShifts;

    std::map<std::pair<std::string, std::string>, Expression*> remoteAccess;

    std::map<std::string, std::set<std::string>> reduction;
    std::map<std::string, std::set<std::tuple<std::string, std::string, int>>> reductionLoc;

public:
    ParallelDirective() { }
    ParallelDirective(const ParallelDirective &copyFrom) : Directive(copyFrom)
    {
        parallel = copyFrom.parallel;
        on = copyFrom.on;
        on2 = copyFrom.on2;

        arrayRef = copyFrom.arrayRef;
        arrayRef2 = copyFrom.arrayRef2;

        privates = copyFrom.privates;
        shadowRenew = copyFrom.shadowRenew;
        shadowRenewShifts = copyFrom.shadowRenewShifts;
        across = copyFrom.across;
        acrossShifts = copyFrom.acrossShifts;
        remoteAccess = copyFrom.remoteAccess;
        reduction = copyFrom.reduction;

        cloneOfTemplate = copyFrom.cloneOfTemplate;        
    }

    std::pair<std::string, std::vector<Expression*>> 
        genDirective(File *file, const std::vector<std::pair<DIST::Array*, const DistrVariant*>> &distribution,
                     const std::vector<AlignRule> &alignRules,
                     DIST::GraphCSR<int, double, attrType> &reducedG,
                     DIST::Arrays<int> &allArrays,
                     const std::set<DIST::Array*> &acrossOutAttribute, 
                     const std::map<DIST::Array*, std::pair<std::vector<ArrayOp>, std::vector<bool>>> &readOps,
                     Statement *loop, const int line, const int altLine, const int regionId,
                     const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls);

    friend ParallelDirective* operator+(const ParallelDirective &first, const ParallelDirective &second);

    ~ParallelDirective()
    {
        parallel.clear();
        on.clear();
        privates.clear();
        shadowRenew.clear();
        across.clear();
        acrossShifts.clear();
        reduction.clear();
        for (auto it = remoteAccess.begin(); it != remoteAccess.end(); ++it)
        {
#ifdef _WIN32
            removeFromCollection(it->second);      
#endif
            delete it->second;
        }
    }

private:
    std::string genBounds(const std::vector<AlignRule> &alignRules,
                                const std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>> &shadowOp,
                                std::vector<std::pair<int, int>> &shadowOpShift,
                                DIST::GraphCSR<int, double, attrType> &reducedG,
                                DIST::Arrays<int> &allArrays,
                                const std::map<DIST::Array*, std::pair<std::vector<ArrayOp>, std::vector<bool>>> &readOps,
                                const bool isAcross, const int regionId,
                                const std::vector<std::pair<DIST::Array*, const DistrVariant*>> &distribution,
                                std::set<DIST::Array*> &arraysInAcross,
                                std::vector<std::map<std::pair<int, int>, int>> &shiftsByAccess,
                                const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls) const;
};

std::string genStringExpr(const std::string &letter, const std::pair<int, int> expr);
std::pair<std::string, std::string> convertDigitToPositive(const int digit);