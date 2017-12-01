#include "../leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <assert.h>

#include "dvm.h"
#include "loop_analyzer.h"

#include "../utils.h"
#include "../SgUtils.h"
#include "../ParallelizationRegions/ParRegions_func.h"
#include "../SageAnalysisTool/depGraph.h"

using std::vector;
using std::pair;
using std::tuple;
using std::map;
using std::set;
using std::make_pair;
using std::make_tuple;
using std::get;
using std::string;

typedef enum { ddflow, ddanti, ddoutput, ddreduce } ddnature;
extern map<LoopGraph*, depGraph*> depInfoForLoopGraph;

// try to find dependencies: reductions and privates for scalar 
//                           and regular and other for arrrays
//TODO: add optimization - dont call omega test for arrays many times
void tryToFindDependencies(LoopGraph *currLoop, const map<int, pair<SgForStmt*, set<string>>> &allLoops,
                           set<SgStatement*> &funcWasInit, SgFile *file, vector<ParallelRegion*> regions,
                           vector<Messages> *currMessages,
                           map<SgExpression*, string> &collection)
{
    auto it = allLoops.find(currLoop->lineNum);
    if (it == allLoops.end())
        return;

    ParallelRegion *currReg = getRegionByLine(regions, it->second.first->fileName(), currLoop->lineNum);
    if (currReg && currLoop->hasLimitsToParallel() == false)
    {
        SgForStmt *currLoopRef = it->second.first;
        bool onlyOneStep = false;
        // if identical
        string startL = string(currLoopRef->start()->unparse());
        string endL = string(currLoopRef->end()->unparse());
        if (startL == endL)
            onlyOneStep = true;

        const set<string> &privVars = it->second.second;

        SgStatement *func = currLoopRef->controlParent();
        if (funcWasInit.find(func) == funcWasInit.end())
        {
            funcWasInit.insert(func);
            initializeDepAnalysisForFunction(file, func);
        }

        depGraph *depg = new depGraph(file, currLoopRef->controlParent(), currLoopRef, privVars);
        if (depg)
        {
            const std::vector<depNode*> &nodes = depg->getNodes();
            vector<const depNode*> privatesToAdd;
            vector<const depNode*> reductionsToAdd;
            vector<const depNode*> unknownScalarDep;

            bool findUnknownDepLen = false;
            map<SgSymbol*, tuple<int, int, int>> acrossToAdd;

            for (int k = 0; k < nodes.size(); ++k)
            {
                const depNode *currNode = nodes[k];
                switch (currNode->typedep)
                {
                case WRONGDEP:
                    break;
                case ARRAYDEP:
                    //dont check if textual identically 
                    if (!isEqExpressions(currNode->varin, currNode->varout, collection))
                    {
                        // TODO: process all loop, not only top loop
                        if (currNode->knowndist[1] == 0 || currNode->distance[1] != 0)
                        {
                            if (currNode->knowndist[1] == 0)
                            {
                                if (!findUnknownDepLen)
                                {
                                    string depMessage = currNode->createDepMessagebetweenArrays();
                                    depMessage += " with unknown distance in loop on line " + std::to_string(currLoopRef->lineNumber()) + " prevents parallelization";

                                    print(1, "%s\n", (string("  ") + depMessage).c_str());
                                    currMessages->push_back(Messages(NOTE, currNode->stmtin->lineNumber(), depMessage));

                                    // print only first unknown dep length
                                    findUnknownDepLen = true;
                                    if (!onlyOneStep)
                                        currLoop->hasUnknownArrayDep = true;
                                }
                            }
                            else if (!findUnknownDepLen) //currNode->distance[1] != 0
                            {
                                const ddnature nature = (ddnature)currNode->kinddep;
                                int position = -1;
                                if (nature == ddflow)
                                    position = 0;
                                else if (nature == ddanti)
                                    position = 1;

                                if (position != -1)
                                {
                                    SgSymbol *arrayS = OriginalSymbol(currNode->varin->symbol());
                                    SgArrayRefExp *arrayRef = (SgArrayRefExp*)(currNode->varin);

                                    bool existSubs = false;

                                    auto it = acrossToAdd.find(arrayS);
                                    if (it == acrossToAdd.end())
                                    {
                                        int subsPos = -1;
                                        SgSymbol *doName = currLoopRef->symbol();
                                        for (int z = 0; z < arrayRef->numberOfSubscripts() && !existSubs; ++z)
                                        {
                                            existSubs = checkExistence(arrayRef->subscript(z), *doName);
                                            if (existSubs)
                                                subsPos = z;
                                        }

                                        if (existSubs)
                                            it = acrossToAdd.insert(it, make_pair(arrayS, make_tuple(0, 0, subsPos)));
                                    }
                                    else
                                        existSubs = true;

                                    if (existSubs)
                                    {
                                        if (position == 0)
                                            get<0>(it->second) = std::max(get<0>(it->second), abs((int)currNode->distance[1]));
                                        else
                                            get<1>(it->second) = std::max(get<1>(it->second), abs((int)currNode->distance[1]));
                                    }
                                }
                            }
                            //currNode->displayDep();
                        }
                    }

                    break;
                case PRIVATEDEP:
                    privatesToAdd.push_back(currNode);
                    break;
                case REDUCTIONDEP:
                    reductionsToAdd.push_back(currNode);
                    break;
                case SCALARDEP:
                    if (privVars.find(currNode->varin->symbol()->identifier()) == privVars.end())
                        unknownScalarDep.push_back(currNode);
                    break;
                default:
                    break;
                }
            }

            if (!onlyOneStep)
            {
                addPrivatesToLoops(currLoop, privatesToAdd, allLoops, *currMessages);
                addReductionsToLoops(currLoop, reductionsToAdd, allLoops, *currMessages);
                if (!findUnknownDepLen && !currLoop->hasLimitsToParallel())
                    addAcrossToLoops(currLoop, acrossToAdd, allLoops, *currMessages);
                
                currLoop->hasUnknownScalarDep = (unknownScalarDep.size() != 0);
                for (int k = 0; k < unknownScalarDep.size(); ++k)
                {
                    printf("  unknown scalar dependencies by '%s' on line %d (try to specify its type)\n",
                        unknownScalarDep[k]->varin->symbol()->identifier(), unknownScalarDep[k]->stmtin->lineNumber());

                    string message;
                    printToBuf(message, "unknown scalar dependencies by '%s' (try to specify its type)", unknownScalarDep[k]->varin->symbol()->identifier());
                    currMessages->push_back(Messages(WARR, unknownScalarDep[k]->stmtin->lineNumber(), message));

                    currLoop->linesOfScalarDep.push_back(unknownScalarDep[k]->stmtin->lineNumber());
                }
            }
            if (!currLoop->hasLimitsToParallel())
                depInfoForLoopGraph[currLoop] = depg;
            else
                delete depg;
        }
    }
    else if (currReg && currLoop->hasLimitsToParallel())
    {
        // loop has limits
        currLoop->addConflictMessages(currMessages);
    }
    
    for (int k = 0; k < currLoop->childs.size(); ++k)
        tryToFindDependencies(currLoop->childs[k], allLoops, funcWasInit, file, regions, currMessages, collection);
}