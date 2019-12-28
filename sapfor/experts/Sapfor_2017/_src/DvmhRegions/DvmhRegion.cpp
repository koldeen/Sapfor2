//
// Created by Vladislav Volodkin on 12/20/19.
//

#include "leak_detector.h"
#include "DvmhRegion.h"

DvmhRegion::DvmhRegion(LoopGraph *loopNode, const std::string &fun_name) : fun_name(fun_name)
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

void DvmhRegion::append(DvmhRegion& region)
{
    for (auto& loop : region.getLoops())
        addLoop(loop);
}