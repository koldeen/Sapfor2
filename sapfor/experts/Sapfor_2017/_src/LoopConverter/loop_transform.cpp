#include "../leak_detector.h"

#include "loop_transform.h"

#include <LoopTransformTighten.hpp>
#include <SageTransformException.hpp>
#include <SageUtils.hpp>
#include "SageAnalysisTool/OmegaForSage/include/lang-interf.h"
#include <SageAnalysisTool/definesValues.h>
#include "../utils.h"

//TODO: NOT FOUND
//using SageTransform::SageUtils::lexNextLoop; //
//using SageTransform::SageUtils::lexPrevEnddo; // not used
using SageTransform::SageUtils::getLastLoopStatement;
using Sapfor2017::CreateNestedLoopsUtils;
using std::pair;
using std::map;

bool createNestedLoops(LoopGraph *current, const map<LoopGraph*, depGraph*> &depInfoForLoopGraph, vector<Messages> &messages)
{
    bool wasTigtened = false;
    // has non nested child loop
    print(1, "createNestedLoops for loop at %d. Start\n", current->lineNum);
    bool outerTigtened = false;
    bool loopCondition = current->childs.size() == 1 && current->perfectLoop == 1 && !current->hasLimitsToParallel();
    
    if (loopCondition)
    {
        //not using inner loop dependencies for now
        //pair<SgForStmt*, depGraph*> innerLoopDependencies = Sapfor2017::CreateNestedLoopsUtils::getDepGraph(current->childs.at(0), depInfoForLoopGraph);
        pair<SgForStmt*, depGraph*> outerLoopDependencies = Sapfor2017::CreateNestedLoopsUtils::getDepGraph(current, depInfoForLoopGraph);
        if (outerLoopDependencies.first && outerLoopDependencies.second) {
            SgForStmt *outerLoop = outerLoopDependencies.first;

            SageTransform::LoopTransformTighten loopTransformTighten;
            map<SgSymbol *, DepType> depMap = CreateNestedLoopsUtils::buildTransformerDependencyMap(outerLoop,
                                                                                                    outerLoopDependencies.second,
                                                                                                    nullptr);
            if (loopTransformTighten.canTighten(outerLoop, depMap) >= 2) {
                outerTigtened = loopTransformTighten.tighten(outerLoop, 2);
                LoopGraph *firstChild = current->childs.at(0);
                if (outerTigtened) {
                    firstChild->perfectLoop = ((SgForStmt *) firstChild->loop)->isPerfectLoopNest();
                }
                print(1, "createNestedLoops for loop at %d. Tighten success: %d\n", current->lineNum, outerTigtened);

                char buf[256];
                sprintf(buf, "loops on lines %d and %d were combined\n", current->lineNum, firstChild->lineNum);
                messages.push_back(Messages(NOTE, current->lineNum, buf));
            }
        }
    }

    wasTigtened = outerTigtened;
    for (int i = 0; i < current->childs.size(); ++i) 
    {
        print(1, "createNestedLoops for loop at %d. Transform child %d\n", current->lineNum, i);
        bool result = createNestedLoops(current->childs[i], depInfoForLoopGraph, messages);
        wasTigtened = wasTigtened || result;
    }    
    
    //update perfect loop
    current->perfectLoop = ((SgForStmt*)current->loop)->isPerfectLoopNest();
    print(1, "createNestedLoops for loop at %d. End\n", current->lineNum);
    return wasTigtened;
}

pair<SgForStmt*, depGraph*> Sapfor2017::CreateNestedLoopsUtils::getDepGraph(LoopGraph *loopGraph, const map<LoopGraph*, depGraph*> &depInfoForLoopGraph)
{
    depGraph *dg = nullptr;
    if (depInfoForLoopGraph.count(loopGraph) == 0) {
        print(1, "getDepGraph for loop at %d. No depGraph found\n", loopGraph->lineNum);
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    } else {
        dg = depInfoForLoopGraph.at(loopGraph);
    }
    SgForStmt *sgForStmt = isSgForStmt(dg->loop);
    if (sgForStmt == nullptr) {
        print(1, "getDepGraph for loop at %d. SgForStmt missing for depGraph\n", loopGraph->lineNum);
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    return std::make_pair(sgForStmt, dg);
}

void printDepGraph(depGraph *dg) 
{
    for (depNode *dn : dg->getNodes())
    {
        dn->displayDep();
        int out = dn->stmtout != nullptr ? dn->stmtout->lineNumber() : -1;
        int in = dn->stmtin != nullptr ? dn->stmtin->lineNumber() : -1;
        //print(1, "dep from %d --> %d\n", out, in);
    }
}

std::map<SgSymbol*, DepType>
  Sapfor2017::CreateNestedLoopsUtils::buildTransformerDependencyMap(SgForStmt *outerLoop, depGraph *outerDepGraph, depGraph *innerDepGraph)
{
    //print(1, "Print outer depgraph START\n");
    //printDepGraph(outerDepGraph);
    //print(1, "Print outer depgraph END\n");
    //print(1, "Print inner depgraph START\n");
    //printDepGraph(innerDepGraph);
    //print(1, "Print inner depgraph END\n");
    SgStatement *outerEnddo = getLastLoopStatement(outerLoop);
    //TODO: NOT FOUND
    SgForStmt *innerLoop = NULL; //lexNextLoop(outerLoop->lexNext(), outerEnddo);
    SgStatement *pClosestDo = outerLoop->lexNext();
    while (!isSgForStmt(pClosestDo) && pClosestDo != outerEnddo)
        pClosestDo = pClosestDo->lexNext();   
    innerLoop = isSgForStmt(pClosestDo);

    SgStatement *innerEnddo = getLastLoopStatement(innerLoop);
    std::map<SgSymbol*, DepType> depMap;

    for (SgStatement *stmt = outerLoop->lexNext(); stmt != innerLoop; stmt = stmt->lexNext()) 
    {
        //loop through invariants before inner loop
        for (SgStatement *bodyStmt = innerLoop->lexNext(); bodyStmt != innerEnddo; bodyStmt = bodyStmt->lexNext()) 
        {
            depNode *node = outerDepGraph->isThereAnEdge(stmt, bodyStmt);
            if (node != nullptr) {
                DepType type = CreateNestedLoopsUtils::fromDepNode(node);
                SgSymbol *symbol = node->varout->symbol();
                depMap.insert(std::make_pair(symbol, type));
            }
        }
    }

    return depMap;
}

DepType CreateNestedLoopsUtils::fromDepNode(depNode *node) 
{
    if (node->typedep == SCALARDEP) 
    {
        ddnature nature = (ddnature) node->kinddep;
        switch (nature) 
        {
            case ddflow:
                return SageTransform::DependencyType::FLOW_DEP;
            case ddanti:
                return SageTransform::DependencyType::ANTI_DEP;
            case ddoutput:
                return SageTransform::DependencyType::OUTPUT_DEP;
            case ddreduce:
                return SageTransform::DependencyType::REDUCTION_DEP;
            default:
                break;
        }
    }
    return SageTransform::DependencyType::UNKNOWN_DEP;
}