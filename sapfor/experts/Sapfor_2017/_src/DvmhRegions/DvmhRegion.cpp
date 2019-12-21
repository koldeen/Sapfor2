//
// Created by Vladislav Volodkin on 12/20/19.
//

#include "DvmhRegion.h"


using namespace std;


DvmhRegion::DvmhRegion(LoopGraph *loopNode, const string &fun_name) : fun_name(fun_name), rw_info(loopNode->loop)
{
    loops.push_back(loopNode);
}

SgStatement* DvmhRegion::getFirstSt() const
{
    if (loops.size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return loops.front()->loop;
}

SgStatement* DvmhRegion::getLastSt() const
{
    if (loops.size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return loops.back()->loop->lastNodeOfStmt();
}

std::unordered_set<SgSymbol*> DvmhRegion::get_modified()  // may raise NotImplemented
{
    return rw_info.get_modified();
}

std::unordered_set<SgSymbol*> DvmhRegion::get_read()  // may raise NotImplemented
{
    return rw_info.get_read();
}

void DvmhRegion::append(DvmhRegion& region)
{
    for (auto& loop : region.getLoops())
        this->addLoop(loop);

    rw_info.update(region.rw_info);
}