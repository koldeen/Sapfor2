#include "../Utils/leak_detector.h"

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
#include <omp.h>

#include "dvm.h"
#include "loop_analyzer.h"

#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
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
extern void initializeDepAnalysisForFunction(SgFile *file, SgStatement *func, const map<string, FuncInfo*> &allFuncs);
extern int staticPrivateAnalysis;

static const set<string> *currentNonDistrArrays = NULL;
static map<SgSymbol*, string> varInOut;
static map<SgExpression*, string> *currentCollection = NULL;

bool isRemovableDependence(const depNode *currNode, const set<string> &privVars)
{
    bool result = true;
    bool varIn = false, varOut = false;

    switch (currNode->typedep)
    {
    case WRONGDEP:
        result = false;
        break;
    case ARRAYDEP:
        if (currentNonDistrArrays && currentNonDistrArrays->size() > 0)
        {
            SgSymbol *vIn = OriginalSymbol(currNode->varin->symbol());
            SgSymbol *vOut = OriginalSymbol(currNode->varout->symbol());

            auto found = varInOut.find(vIn);
            if (found == varInOut.end())
                found = varInOut.insert(found, make_pair(vIn, vIn->identifier()));
            varIn = currentNonDistrArrays->find(found->second) != currentNonDistrArrays->end();

            found = varInOut.find(vOut);
            if (found == varInOut.end())
                found = varInOut.insert(found, make_pair(vOut, vOut->identifier()));
            varOut = currentNonDistrArrays->find(found->second) != currentNonDistrArrays->end();
        }
        //dont check if textual identically 
        if ((!isEqExpressions(currNode->varin, currNode->varout, *currentCollection) || varIn || varOut) && (currNode->varin != currNode->varout))
        {
            // TODO: process all loop, not only top loop
            if (currNode->knowndist[1] == 0 || currNode->distance[1] != 0)
            {
                if (currNode->knowndist[1] == 0)
                    result = false;
            }
            else if (varIn || varOut) // found dependencies between non ditributed arrays
            {
                result = false;
            }
        }

        break;
    case PRIVATEDEP:
    case REDUCTIONDEP:
        break;
    case SCALARDEP:
        if (privVars.find(currNode->varin->symbol()->identifier()) == privVars.end())
            result = false;
        break;
    default:
        result = false;
        break;
    }
    return result;
}

static SgStatement* getCurrentFunc(SgStatement *st)
{
    while (st->variant() != PROG_HEDR && st->variant() != PROC_HEDR && st->variant() != FUNC_HEDR)
        st = st->controlParent();
    checkNull(st, convertFileName(__FILE__).c_str(), __LINE__);
    return st;
}

depGraph *getDependenciesGraph(LoopGraph *currLoop, SgFile *file, const set<string> *privVars)
{
    SgForStmt *currLoopRef = (SgForStmt*)currLoop->loop->GetOriginal();
    double t = omp_get_wtime();

    map<SgExpression*, string> tmpCollection;
    currentCollection = &tmpCollection;

    depGraph *depg = new depGraph(file, getCurrentFunc(currLoopRef), currLoopRef, *privVars);
    t = omp_get_wtime() - t;
    if (t > 1.0)
        printf("SAPFOR: time of graph bulding for loop %d = %f sec\n", currLoop->lineNum, t);
    currentCollection = NULL;
    return depg;
}

// try to find dependencies: reductions and privates for scalar 
//                           and regular and other for arrrays
//TODO: add optimization - dont call omega test for arrays many times
void tryToFindDependencies(LoopGraph *currLoop, const map<int, pair<SgForStmt*, pair<set<string>, set<string>>>> &allLoops,
                           set<SgStatement*> &funcWasInit, SgFile *file, vector<ParallelRegion*> regions,
                           vector<Messages> *currMessages,
                           map<SgExpression*, string> &collection,
                           const map<string, FuncInfo*> &allFuncs)
{
    auto it = allLoops.find(currLoop->lineNum);
    if (it == allLoops.end())
        return;

    map<int, SgForStmt*> localAllLoopMap;
    for (auto &elem : allLoops)
        localAllLoopMap.insert(make_pair(elem.first, elem.second.first));

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

        const set<string> &privVars = it->second.second.first;
        const set<string> &nonDistrArrays = it->second.second.second;
        
        SgStatement *func = currLoopRef->controlParent();
        if (funcWasInit.find(func) == funcWasInit.end())
        {
            funcWasInit.insert(func);
            initializeDepAnalysisForFunction(file, func, allFuncs);
        }

        currentNonDistrArrays = &nonDistrArrays;
        currentCollection = &collection;
        depGraph *depg = getDependenciesGraph(currLoop, file, &privVars);
        currentNonDistrArrays = NULL;
        currentCollection = NULL;

        /*double t = omp_get_wtime();
        depGraph *depg = new depGraph(file, getCurrentFunc(currLoopRef), currLoopRef, privVars);
        t = omp_get_wtime() - t;
        if (t > 1.0)
            printf("SAPFOR: time of graph bulding for loop %d = %f sec\n", currLoop->lineNum, t);*/

        if (depg)
        {
            const std::vector<depNode*> &nodes = depg->getNodes();
            vector<const depNode*> privatesToAdd;
            vector<const depNode*> reductionsToAdd;
            vector<const depNode*> unknownScalarDep;

            bool findUnknownDepLen = false;
            map<SgSymbol*, tuple<int, int, int>> acrossToAdd;

            bool varIn = false, varOut = false;

            for (int k = 0; k < nodes.size(); ++k)
            {
                const depNode *currNode = nodes[k];
                switch (currNode->typedep)
                {
                case WRONGDEP:
                    break;
                case ARRAYDEP:
                    if (nonDistrArrays.size() > 0)
                    {
                        SgSymbol *vIn = OriginalSymbol(currNode->varin->symbol());
                        SgSymbol *vOut = OriginalSymbol(currNode->varout->symbol());

                        auto found = varInOut.find(vIn);
                        if (found == varInOut.end())
                            found = varInOut.insert(found, make_pair(vIn, vIn->identifier()));
                        varIn = nonDistrArrays.find(found->second) != nonDistrArrays.end();
                        
                        found = varInOut.find(vOut);
                        if (found == varInOut.end())
                            found = varInOut.insert(found, make_pair(vOut, vOut->identifier()));
                        varOut = nonDistrArrays.find(found->second) != nonDistrArrays.end();
                    }
                    //dont check if textual identically 
                    if ((!isEqExpressions(currNode->varin, currNode->varout, collection) || varIn || varOut) && (currNode->varin != currNode->varout))
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

                                    __spf_print(1, "%s\n", (string("  ") + depMessage).c_str());
                                    currMessages->push_back(Messages(NOTE, currNode->stmtin->lineNumber(), depMessage, 3006));

                                    // __spf_print only first unknown dep length
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
                                            existSubs = checkExistence(arrayRef->subscript(z), doName);
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
                        else if (varIn || varOut) // found dependencies between non ditributed arrays
                        {
                            if (!findUnknownDepLen)
                            {
                                string depMessage = currNode->createDepMessagebetweenArrays() + " prevents parallelization";

                                __spf_print(1, "%s\n", (string("  ") + depMessage).c_str());
                                currMessages->push_back(Messages(NOTE, currNode->stmtin->lineNumber(), depMessage, 3006));

                                // __spf_print only first unknown dep length
                                findUnknownDepLen = true;
                                if (!onlyOneStep)
                                    currLoop->hasUnknownArrayDep = true;
                            }
                        }
                    }

                    break;
                case PRIVATEDEP:
                    /*if (staticPrivateAnalysis == 0)
                    {
                        if (privVars.find(currNode->varin->symbol()->identifier()) == privVars.end())
                            privatesToAdd.push_back(currNode);
                    }
                    else
                    {
                        if (privVars.find(currNode->varin->symbol()->identifier()) == privVars.end())
                            unknownScalarDep.push_back(currNode);
                    }*/
                    if (privVars.find(currNode->varin->symbol()->identifier()) == privVars.end())
                        privatesToAdd.push_back(currNode);
                    break;
                case REDUCTIONDEP:
                    if (privVars.find(currNode->varin->symbol()->identifier()) == privVars.end())
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
                addPrivatesToLoops(currLoop, privatesToAdd, localAllLoopMap, *currMessages);
                addReductionsToLoops(currLoop, reductionsToAdd, localAllLoopMap, *currMessages);
                if (!findUnknownDepLen && !currLoop->hasLimitsToParallel())
                    addAcrossToLoops(currLoop, acrossToAdd, localAllLoopMap, *currMessages);
                
                currLoop->hasUnknownScalarDep = (unknownScalarDep.size() != 0);
                for (int k = 0; k < unknownScalarDep.size(); ++k)
                {
                    printf("  unknown scalar dependencies by '%s' on line %d (try to specify its type)\n",
                        unknownScalarDep[k]->varin->symbol()->identifier(), unknownScalarDep[k]->stmtin->lineNumber());

                    string message;
                    __spf_printToBuf(message, "unknown scalar dependencies by '%s' (try to specify its type)", unknownScalarDep[k]->varin->symbol()->identifier());
                    currMessages->push_back(Messages(WARR, unknownScalarDep[k]->stmtin->lineNumber(), message, 3005));

                    currLoop->linesOfScalarDep.push_back(unknownScalarDep[k]->stmtin->lineNumber());
                }
            }

            if (!currLoop->hasLimitsToParallel())
                depInfoForLoopGraph[currLoop] = depg;
            else
            {
                currLoop->addConflictMessages(currMessages);
                delete depg;
            }
        }
    }
    else if (currReg && currLoop->hasLimitsToParallel())
    {
        // loop has limits
        currLoop->addConflictMessages(currMessages);
    }
    
    for (int k = 0; k < currLoop->children.size(); ++k)
        tryToFindDependencies(currLoop->children[k], allLoops, funcWasInit, file, regions, currMessages, collection, allFuncs);
}