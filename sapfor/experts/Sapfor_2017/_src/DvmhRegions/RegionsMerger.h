//
// Created by Vladislav Volodkin on 12/17/19.
//

#ifndef SAPFOR_REGIONSMERGER_H
#define SAPFOR_REGIONSMERGER_H
#include "DvmhRegions/DvmhRegionInserter.h"

class RegionsMerger
{
    std::vector<DvmhRegion*> regions;

    static bool compareByStart(const DvmhRegion *a, const DvmhRegion *b);
    bool canBeMoved(SgStatement* st, DvmhRegion *region);
    std::vector<SgStatement*> getStatementsToMove(DvmhRegion *first, const DvmhRegion *second);
    void moveStatements(std::vector<SgStatement*> sts, DvmhRegion *region);
    bool inSet(std::unordered_set<SgSymbol*>, SgSymbol*);
public:
    explicit RegionsMerger(std::vector<DvmhRegion*> old_regions) : regions(old_regions) { };
    std::vector<DvmhRegion*> mergeRegions();
};

#endif //SAPFOR_REGIONSMERGER_H
