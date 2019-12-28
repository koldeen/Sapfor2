#include "leak_detector.h"
#include "RegionsMerger.h"

using namespace std;

bool RegionsMerger::compareByStart(const DvmhRegion *a, const DvmhRegion *b)
{
    if (a->getLoops().size() < 1 || b->getLoops().size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return a->getLoops()[0]->loop->lineNumber() < b->getLoops()[0]->loop->lineNumber();
}

bool RegionsMerger::canBeMoved(SgStatement* st, const DvmhRegion *region) const
{
    // For now: st [a, d = b + c] can be moved IF [b, c] are not modified in region AND [a, d] not used for read in region
    // get usages for statement
    VarUsages st_usages = rw_analyzer.get_usages(st);

    // get usages for region
    auto loop_statements = vector<SgStatement*>();
    for (auto& loop : region->getLoops())
        loop_statements.push_back(loop->loop);

    auto region_usages = rw_analyzer.get_usages(loop_statements);

    // analyze if statement can be placed before region
    if (sets_intersect(st_usages.get_reads(), region_usages.get_writes()))  // check that [b, c] not modified in region
        return false;

    if (sets_intersect(st_usages.get_writes(), region_usages.get_reads()))  // check that [a, d] not read in region
        return false;
    
    return true;  // everything's ok
}

vector<SgStatement*> RegionsMerger::getStatementsToMove(const DvmhRegion *first, const DvmhRegion *second, bool &can) const
{
    // can not, abort operation
    if (first->getFileName() != second->getFileName() || first->getFunName() != second->getFunName())
    {
        can = false;
        return vector<SgStatement*>();
    }

    vector<SgStatement*> toMove;
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
        else // can not, abort operation
        {
            can = false;
            return vector<SgStatement*>();
        }
        mediumSt = mediumSt->lexNext();
    }

    return toMove;
}

// Places statements before region
void RegionsMerger::moveStatements(const vector<SgStatement*>& sts, const DvmhRegion* region) 
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

    rw_analyzer.invalidate();
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

        if (isFirst) // skip first region
        {
            isFirst = false;
            continue;
        }

        /*bool can = true;
        auto toMove = getStatementsToMove(regionPrev, region, can);*/
        //TODO: need to check
        if (false)
            ;// moveStatements(toMove, regionPrev);
        else
        {
            //TODO: extend message
            __spf_print(1, "cannot be merged\n");
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

bool RegionsMerger::sets_intersect(const set<SgSymbol*>& set1, const set<SgSymbol*>& set2) const
{
    for (auto& symb : set1)
        if (set2.find(symb) != set2.end())
            return true;
    return false;
}
