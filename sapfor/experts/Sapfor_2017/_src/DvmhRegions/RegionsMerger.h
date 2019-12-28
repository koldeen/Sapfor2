#pragma once

#include "DvmhRegions/DvmhRegionInserter.h"

class RegionsMerger
{
    std::vector<DvmhRegion*> &regions;
    ReadWriteAnalyzer &rw_analyzer;

    bool canBeMoved(SgStatement* st, const DvmhRegion *region) const;
    std::vector<SgStatement*> getStatementsToMove(const DvmhRegion *first, const DvmhRegion *second, bool&) const;
    void moveStatements(const std::vector<SgStatement*>& sts, const DvmhRegion* region);        
    bool sets_intersect(const std::set<SgSymbol*>&, const std::set<SgSymbol*>&) const;

    static bool compareByStart(const DvmhRegion* a, const DvmhRegion* b);
public:
    explicit RegionsMerger(std::vector<DvmhRegion*>& old_regions, ReadWriteAnalyzer& rw) : regions(old_regions), rw_analyzer(rw) { }
    std::vector<DvmhRegion*> mergeRegions();
};
