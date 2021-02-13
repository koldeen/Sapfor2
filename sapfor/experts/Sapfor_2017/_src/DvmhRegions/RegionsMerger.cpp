#include "leak_detector.h"
#include "RegionsMerger.h"

using namespace std;

bool RegionsMerger::compareByStart(const DvmhRegion *a, const DvmhRegion *b)
{
    if (a->getLoops().size() < 1 || b->getLoops().size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    int lineLeft = a->getLoops()[0]->lineNum;
    if (lineLeft < 0)
        lineLeft = a->getLoops()[0]->altLineNum;

    int lineRight = b->getLoops()[0]->lineNum;
    if (lineRight < 0)
        lineRight = b->getLoops()[0]->altLineNum;
    return lineLeft < lineRight;
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

    // skip DVM PARALLEL and hidden stats
    while (mediumSt->variant() == DVM_PARALLEL_ON_DIR || mediumSt->variant() < 0)
        mediumSt = mediumSt->lexNext();

    //no statements between regions, so can
    if (mediumSt == second->getFirstSt() && mediumSt->variant() == FOR_NODE)
    {
        can = true;
        return vector<SgStatement*>();
    } //TODO    
    else
    {
        can = false;
        return vector<SgStatement*>();
    }

    //TODO: need to check and correct
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

    rw_analyzer.invalidate(region->getFileName());
}

vector<DvmhRegion*> RegionsMerger::mergeRegions()
{
    if (regions.size() < 2)
        return regions;

    map<string, map<int, DvmhRegion*>> byFunc;
    for (auto& elem : regions)
    {
        const int line = elem->getLineForSort();
        const string fName = elem->getFunName();
        auto& itF = byFunc[fName];
        if (itF.find(line) != itF.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        itF[line] = elem;
    }

    vector<DvmhRegion*> newRegions;

    for (auto& regsForFunc : byFunc)
    {
        map<int, DvmhRegion*>& regionsByFunc = regsForFunc.second;

        if (regionsByFunc.size() == 0)
            continue;

        DvmhRegion* newRegion = new DvmhRegion();
        DvmhRegion* regionPrev = regionsByFunc.begin()->second;

        bool isFirst = true;
        for (auto& loop : regionPrev->getLoops())
            newRegion->addLoop(loop);

        for (auto& region : regionsByFunc)
        {
            if (newRegion->getFunName() == "" && region.second->getLoops().size() > 0)
            {
                SgStatement* func_st = getFuncStat(region.second->getLoops()[0]->loop);
                string fun_name = func_st->symbol()->identifier();
                newRegion->setFunName(fun_name);
            }

            if (isFirst) // skip first region
            {
                isFirst = false;
                continue;
            }

            bool can = true;
            auto toMove = getStatementsToMove(regionPrev, region.second, can);
            if (can)
            {
                //TODO
                if (toMove.size())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                // moveStatements(toMove, regionPrev);
            }
            else
            {
                __spf_print(1, "   region before loop on line %d (alt %d) cannot be merged\n", 
                            region.second->getLoops()[0]->lineNum, region.second->getLoops()[0]->altLineNum);
                toMove = getStatementsToMove(regionPrev, region.second, can);
                newRegions.push_back(newRegion);
                newRegion = new DvmhRegion();
            }

            newRegion->append(*region.second);
            regionPrev = region.second;
        }
        newRegions.push_back(newRegion);
    }

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
