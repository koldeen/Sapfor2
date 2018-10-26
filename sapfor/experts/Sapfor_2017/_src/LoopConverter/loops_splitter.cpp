#include "loops_splitter.h"
#include <string>

using std::string;

static void splitLoop(LoopGraph *loopGraph, int depthOfSplit)
{
    if(depthOfSplit < 0 || depthOfSplit > loopGraph->perfectLoop)
        depthOfSplit = loopGraph->perfectLoop;

    printf("Hey!\n");
}

void splitLoops(SgFile *file, std::vector<LoopGraph*> &loopGraphs)
{
    if(string(file->filename()) == "z_solve_inlined.f")
        for(auto& loopGraph : loopGraphs)
        {
            splitLoop(loopGraph, -1);
        }
}
