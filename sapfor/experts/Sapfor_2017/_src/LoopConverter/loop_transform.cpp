#include "../leak_detector.h"

#include "loop_transform.h"

#include <LoopTransformTighten.hpp>
#include <SageTransformException.hpp>
#include <LineReorderer.hpp>
#include <SageUtils.hpp>
#include "SageAnalysisTool/OmegaForSage/include/lang-interf.h"
#include <SageAnalysisTool/definesValues.h>
#include "../utils.h"

using SageTransform::SageUtils::getLastLoopStatement;
using SageTransform::DependencyType;
using Sapfor2017::CreateNestedLoopsUtils;
using std::pair;
using std::map;
using std::stack;

static void buildLoopMap(LoopGraph *current, map<SgForStmt*, LoopGraph*> &loopMap)
{
    loopMap[(SgForStmt*)(current->loop)] = current;
    for (int i = 0; i < current->childs.size(); ++i)
        buildLoopMap(current->childs[i], loopMap);
}

void reverseCreatedNestedLoops(const string &file, vector<LoopGraph*> &loopsInFile)
{
    map<SgForStmt*, LoopGraph*> loopMap;
    for (auto &elem : loopsInFile)
        buildLoopMap(elem, loopMap);

    auto *launches = SageTransform::LoopTransformTighten::getLaunches();
    if (launches->count(file) == 0) {
        __spf_print(1, "nothing to revert in %s\n", file.c_str());
        return;
    }
    stack<pair<SgForStmt*, SageTransform::LineReorderRecord>> &backOrder = launches->at(file);
    while (backOrder.size())
    {
        auto &elem = backOrder.top();
        backOrder.pop();
        auto it = loopMap.find(elem.first);
        if (it == loopMap.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        auto reorder = elem.second.buildReverse();
        SageTransform::LineReorderer::apply(elem.first, reorder);
        it->second->recalculatePerfect();
    }
}

bool createNestedLoops(LoopGraph *current, const map<LoopGraph*, depGraph*> &depInfoForLoopGraph, vector<Messages> &messages)
{
    bool wasTigtened = false;
    // has non nested child loop
    __spf_print(1, "createNestedLoops for loop at %d. Start\n", current->lineNum);
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
            map<SgSymbol *, DependencyType> depMap = CreateNestedLoopsUtils::buildTransformerDependencyMap(outerLoop,
                                                                                                    outerLoopDependencies.second,
                                                                                                    nullptr);
            if (loopTransformTighten.canTighten(outerLoop, depMap) >= 2) {
                outerTigtened = loopTransformTighten.tighten(outerLoop, 2);
                LoopGraph *firstChild = current->childs.at(0);
                if (outerTigtened) {
                    firstChild->perfectLoop = ((SgForStmt *) firstChild->loop)->isPerfectLoopNest();
                }
                __spf_print(1, "createNestedLoops for loop at %d. Tighten success: %d\n", current->lineNum, outerTigtened);

                char buf[256];
                sprintf(buf, "loops on lines %d and %d were combined\n", current->lineNum, firstChild->lineNum);
                messages.push_back(Messages(NOTE, current->lineNum, buf));
            }
        }
    }

    wasTigtened = outerTigtened;
    for (int i = 0; i < current->childs.size(); ++i) 
    {
        __spf_print(1, "createNestedLoops for loop at %d. Transform child %d\n", current->lineNum, i);
        bool result = createNestedLoops(current->childs[i], depInfoForLoopGraph, messages);
        wasTigtened = wasTigtened || result;
    }    
    
    //update perfect loop
    current->recalculatePerfect();
    __spf_print(1, "createNestedLoops for loop at %d. End\n", current->lineNum);
    return wasTigtened;
}

pair<SgForStmt*, depGraph*> Sapfor2017::CreateNestedLoopsUtils::getDepGraph(LoopGraph *loopGraph, const map<LoopGraph*, depGraph*> &depInfoForLoopGraph)
{
    SgForStmt *sgForStmt = nullptr;
    depGraph *dg = nullptr;
    if (depInfoForLoopGraph.count(loopGraph) == 0) {
        __spf_print(1, "getDepGraph for loop at %d. No depGraph found\n", loopGraph->lineNum);
    } else {
        dg = depInfoForLoopGraph.at(loopGraph);
        sgForStmt = isSgForStmt(dg->loop);
        if (sgForStmt == nullptr) {
            __spf_print(1, "getDepGraph for loop at %d. SgForStmt missing for depGraph\n", loopGraph->lineNum);
        }
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
        //__spf_print(1, "dep from %d --> %d\n", out, in);
    }
}

std::map<SgSymbol*, DependencyType>
  Sapfor2017::CreateNestedLoopsUtils::buildTransformerDependencyMap(SgForStmt *outerLoop, depGraph *outerDepGraph, depGraph *innerDepGraph)
{
    //__spf_print(1, "Print outer depgraph START\n");
    //printDepGraph(outerDepGraph);
    //__spf_print(1, "Print outer depgraph END\n");
    //__spf_print(1, "Print inner depgraph START\n");
    //printDepGraph(innerDepGraph);
    //__spf_print(1, "Print inner depgraph END\n");
    SgStatement *outerEnddo = getLastLoopStatement(outerLoop);
    //TODO: NOT FOUND
    SgForStmt *innerLoop = NULL; //lexNextLoop(outerLoop->lexNext(), outerEnddo);
    SgStatement *pClosestDo = outerLoop->lexNext();
    while (!isSgForStmt(pClosestDo) && pClosestDo != outerEnddo)
        pClosestDo = pClosestDo->lexNext();   
    innerLoop = isSgForStmt(pClosestDo);

    SgStatement *innerEnddo = getLastLoopStatement(innerLoop);
    std::map<SgSymbol*, DependencyType> depMap;

    for (SgStatement *stmt = outerLoop->lexNext(); stmt != innerLoop; stmt = stmt->lexNext()) 
    {
        //loop through invariants before inner loop
        for (SgStatement *bodyStmt = innerLoop->lexNext(); bodyStmt != innerEnddo; bodyStmt = bodyStmt->lexNext()) 
        {
            depNode *node = outerDepGraph->isThereAnEdge(stmt, bodyStmt);
            if (node != nullptr) {
                DependencyType type = CreateNestedLoopsUtils::fromDepNode(node);
                SgSymbol *symbol = node->varout->symbol();
                depMap.insert(std::make_pair(symbol, type));
            }
        }
    }

    return depMap;
}

DependencyType CreateNestedLoopsUtils::fromDepNode(depNode *node)
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