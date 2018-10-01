#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <string>
#include <fstream>
#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <assert.h>

#include "../Distribution/DvmhDirective.h"
#include "../GraphLoop/graph_loops.h"
#include "DirectiveAnalyzer.h"
#include "../Utils/utils.h"

using std::vector;
using std::map;

static void recUniteAcrossOut(LoopGraph *currLoop)
{
    if (currLoop->perfectLoop > 1)
    {
        recUniteAcrossOut(currLoop->childs[0]);
        if (currLoop->directive)
            currLoop->acrossOutAttribute.insert(currLoop->childs[0]->acrossOutAttribute.begin(), currLoop->childs[0]->acrossOutAttribute.end());
    }
}

static void recUnite(vector<LoopGraph*> &loopGraph)
{
    for (int i = 0; i < loopGraph.size(); ++i)
    {
        LoopGraph &currLoop = *loopGraph[i];
        if (currLoop.perfectLoop > 1)
        {
            vector<ParallelDirective*> united;
            vector<ParallelDirective*> elems;

            LoopGraph *elem = loopGraph[i];
            for (int k = 0; k < currLoop.perfectLoop; ++k)
            {
                elems.push_back(elem->directive);
                if (k != currLoop.perfectLoop - 1)
                    elem = elem->childs[0];
            }

            united.push_back(elems.back());
            for (int k = currLoop.perfectLoop - 2; k >= 0; --k)
            {
                ParallelDirective *first = elems[k];
                ParallelDirective *second = united.back();
                ParallelDirective *newDir = NULL;
                if (first != NULL && second != NULL)
                    newDir = *first + *second;
                else if (first != NULL)
                    newDir = new ParallelDirective(*first);

                united.push_back(newDir);
            }

            elem = loopGraph[i];
            for (int k = 0; k < currLoop.perfectLoop - 1; ++k)
            {
                if (elem->directive)
                    delete elem->directive;

                elem->directive = united[currLoop.perfectLoop - k - 1];
                elem = elem->childs[0];
            }
            recUniteAcrossOut(loopGraph[i]);
        }
        else
            recUnite(currLoop.childs);
    }
}

extern void createMapLoopGraph(std::map<int, LoopGraph*> &sortedLoopGraph, const std::vector<LoopGraph*> *loopGraph);
void UniteNestedDirectives(vector<LoopGraph*> &loopGraph)
{
    recUnite(loopGraph);

    /*map<int, LoopGraph*> sortedLoopGraph;
    createMapLoopGraph(sortedLoopGraph, &loopGraph);*/
}