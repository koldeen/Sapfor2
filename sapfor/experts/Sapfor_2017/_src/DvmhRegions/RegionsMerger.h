// Created by Vladislav Volodkin on 12/20/19.

#pragma once

#include "DvmhRegions/DvmhRegionInserter.h"

class RegionsMerger
{
    std::vector<DvmhRegion*> &regions;
    ReadWriteAnalyzer &rw_analyzer;

    bool canBeMoved(SgStatement* st, DvmhRegion *region);
    std::vector<SgStatement*> getStatementsToMove(DvmhRegion *first, const DvmhRegion *second, bool&);

    void moveStatements(std::vector<SgStatement*> sts, DvmhRegion *region);

    static bool compareByStart(const DvmhRegion *a, const DvmhRegion *b);
    bool sets_intersect(const std::set<SgSymbol*>&, const std::set<SgSymbol*>&) const;
public:
    explicit RegionsMerger(std::vector<DvmhRegion*> &old_regions, ReadWriteAnalyzer &rw) : regions(old_regions), rw_analyzer(rw) { };
    std::vector<DvmhRegion*> mergeRegions();
};
