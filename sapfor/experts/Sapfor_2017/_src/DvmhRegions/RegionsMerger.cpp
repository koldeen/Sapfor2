//
// Created by Vladislav Volodkin on 12/17/19.
//

#include "RegionsMerger.h"

using namespace std;

bool RegionsMerger::compareByStart(const DvmhRegion *a, const DvmhRegion *b)
{
    if (a->getLoops().size() < 1 || b->getLoops().size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return a->getLoops()[0]->loop->lineNumber() < b->getLoops()[0]->loop->lineNumber();
}

bool RegionsMerger::canBeMoved(SgStatement* st, DvmhRegion *region)
{
    // For now: st [a, d = b + c] can be moved IF [b, c] are not modified in region AND [a, d] not used for read in region
    try {
        auto rw_data = ReadWriteAnylyser(st);

        for (auto& read : rw_data.get_read())  // check that [b, c] not modified in region
            if (inSet(region->get_modified(), read))
                return false;

        for (auto& modified : rw_data.get_read())  // check that [a, d] not read in region
            if (inSet(region->get_read(), modified))
                return false;
    }
    catch (NotImplemented &e) {
        return false;
    }

    return true;  // everything's ok
}

vector<SgStatement*> RegionsMerger::getStatementsToMove(DvmhRegion *first, const DvmhRegion *second)
{
    if (first->getFileName() != second->getFileName() || first->getFunName() != second->getFunName())
        throw NotMergeable();

    auto toMove = vector<SgStatement*>();
    SgStatement* mediumSt = first->getLastSt()->lexNext();
    while (mediumSt->id() != second->getFirstSt()->id())
    {
        if (mediumSt->variant() == DVM_PARALLEL_ON_DIR)
        {
            mediumSt = mediumSt->lexNext();
            continue;
        }

        if (canBeMoved(mediumSt, first))
            toMove.push_back(mediumSt);
        else
            throw NotMergeable();

        mediumSt = mediumSt->lexNext();
    }

    return toMove;
}

void RegionsMerger::moveStatements(vector<SgStatement*> sts, DvmhRegion *region) // Places statements before region
{
    SgStatement* prev = region->getFirstSt()->lexPrev();
    while (isDVM_stat(prev))
        prev = prev->lexPrev();

    for (auto& st : sts)
    {
        SgStatement *toInsert = st->copyPtr();
        prev->insertStmtAfter(*toInsert, *prev->controlParent());
        prev = toInsert;
        st->deleteStmt();
    }
    // TODO: здесь нужно как-то перестроить array_usage
}

vector<DvmhRegion*> RegionsMerger::mergeRegions()
{
    if (regions.size() < 2)
        return regions;

    sort(regions.begin(), regions.end(), compareByStart);

    vector<DvmhRegion*> newRegions;
    DvmhRegion *newRegion = new DvmhRegion();
    DvmhRegion *regionPrev = regions[0];

    bool isFirst = true;
    for (auto& loop : regions[0]->getLoops())
        newRegion->addLoop(loop);

    for (auto& region : regions)
    {
        if (newRegion->getFunName() == "" && region->getLoops().size() > 0)
        {
            SgStatement* func_st = getFuncStat(region->getLoops()[0]->loop);
            string fun_name = func_st->symbol()->identifier();
            newRegion->setFunName(fun_name);
        }
        //printf("Merge number %d\n", i++);
        if (isFirst) // skip first region
        {
            isFirst = false;
            continue;
        }

        try {
            auto toMove = getStatementsToMove(regionPrev, region);
            moveStatements(toMove, regionPrev);
        } catch (NotMergeable e) {
            printf("cannot be merged\n");
            newRegions.push_back(newRegion);
            newRegion = new DvmhRegion();
        }

        newRegion->append(*region);
        regionPrev = region;
    }
    newRegions.push_back(newRegion);

    for (auto& old : regions)
        delete old;
    regions.clear();

    return newRegions;
}

bool RegionsMerger::inSet(std::unordered_set<SgSymbol*> container, SgSymbol* needle)
{
    auto it = container.find(needle);

    if (it == container.end())
        return false;
    else
        return true;
}
