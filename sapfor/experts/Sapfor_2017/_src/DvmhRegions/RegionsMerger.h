//
// Created by Vladislav Volodkin on 12/17/19.
//

#ifndef SAPFOR_REGIONSMERGER_H
#define SAPFOR_REGIONSMERGER_H
#include "DvmhRegions/DvmhRegionInserter.h"

class RegionsMerger
{
    std::vector<DvmhRegion*> &regions;
    ReadWriteAnalyzer &rw_analyzer;

    bool canBeMoved(SgStatement* st, DvmhRegion *region);
    std::vector<SgStatement*> getStatementsToMove(DvmhRegion *first, const DvmhRegion *second);

    void moveStatements(std::vector<SgStatement*> sts, DvmhRegion *region);

    static bool compareByStart(const DvmhRegion *a, const DvmhRegion *b);
    bool sets_intersect(std::unordered_set<SgSymbol*>, std::unordered_set<SgSymbol*>);
public:
    explicit RegionsMerger(std::vector<DvmhRegion*> &old_regions, ReadWriteAnalyzer &rw) : regions(old_regions), rw_analyzer(rw) { };
    std::vector<DvmhRegion*> mergeRegions();
};

#endif //SAPFOR_REGIONSMERGER_H
