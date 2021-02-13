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
    return loops.front()->loop->GetOriginal();
}

SgStatement* DvmhRegion::getLastSt() const
{
    if (loops.size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return loops.back()->loop->GetOriginal()->lastNodeOfStmt();
}

void DvmhRegion::append(DvmhRegion& region)
{
    for (auto& loop : region.getLoops())
        addLoop(loop);
}

int DvmhRegion::getLineForSort() const
{
    if (loops.size() == 0)
        return -1;

    int line = loops[0]->lineNum;
    if (line < 0)
        line = loops[0]->altLineNum;
    return line;
}