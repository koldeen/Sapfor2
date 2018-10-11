#include "../Utils/leak_detector.h"

#include <vector>
#include <string>
#include <set>

#include "loop_transform.h"
#include "../LoopAnalyzer/directive_parser.h"
#include "../SageAnalysisTool/OmegaForSage/include/lang-interf.h"
#include "../SageAnalysisTool/definesValues.h"
#include "../Utils/SgUtils.h"

using std::pair;
using std::map;
using std::tuple;
using std::stack;
using std::string;
using std::vector;
using std::set;

static void buildTopParentLoop(LoopGraph *current, LoopGraph *top, map<LoopGraph*, LoopGraph*> &loopTopMap)
{
    loopTopMap[current] = top;
    for (int i = 0; i < current->children.size(); ++i)
        buildTopParentLoop(current->children[i], top, loopTopMap);
}

static void buildLoopMap(LoopGraph *current, map<PTR_BFND, LoopGraph*> &loopMap)
{
    loopMap[current->loop->thebif] = current;
    for (int i = 0; i < current->children.size(); ++i)
        buildLoopMap(current->children[i], loopMap);
}

void reverseCreatedNestedLoops(const string &file, vector<LoopGraph*> &loopsInFile)
{
    map<PTR_BFND, LoopGraph*> loopMap;
    map<LoopGraph*, LoopGraph*> loopTopMap;

    for (auto &elem : loopsInFile)
    {
        buildLoopMap(elem, loopMap);
        buildTopParentLoop(elem, elem, loopTopMap);
    }

    //TODO: need to rewrite
    /*
    auto *launches = SageTransform::LoopTransformTighten::getLaunches();
    if (launches->count(file) == 0) {
        __spf_print(1, "  nothing to revert in %s\n", file.c_str());
        return;
    }
    stack<pair<SgForStmt*, SageTransform::LineReorderRecord>> &backOrder = launches->at(file);
    set<LoopGraph*> topLoopsToRecalaulate;

    while (backOrder.size())
    {
        auto &elem = backOrder.top();
        auto it = loopMap.find(elem.first->thebif);
        if (it == loopMap.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        auto reorder = elem.second.buildReverse();
        SageTransform::LineReorderer::apply(elem.first, reorder);
        topLoopsToRecalaulate.insert(loopTopMap[it->second]);
        backOrder.pop();
    }

    for (auto &elem : topLoopsToRecalaulate)
    {
        elem->recalculatePerfect();
        elem->restoreDirective();
    }*/
}

//use this for TODO below!
static void fillPrivateAndReductionFromComment(SgStatement *st, set<SgSymbol*> &privates, 
                                               map<string, set<SgSymbol*>> &reduction,
                                               map<string, set<tuple<SgSymbol*, SgSymbol*, int>>> &reduction_loc)
{
    for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ SPF_ANALYSIS_DIR }))
    {
        fillPrivatesFromComment(data, privates);
        fillReductionsFromComment(data, reduction);
        fillReductionsFromComment(data, reduction_loc);
    }
}

//todo parse spf private comments into additional dependency info
bool createNestedLoops(LoopGraph *current, const map<LoopGraph*, depGraph*> &depInfoForLoopGraph, vector<Messages> &messages)
{
    bool wasTightened = false;
    // has non nested child loop
    __spf_print(1, "  createNestedLoops for loop at %d. Start\n", current->lineNum);
    bool outerTightened = false;
<<<<<<< HEAD
    bool loopCondition = current->childs.size() == 1 && current->perfectLoop == 1 && !current->hasLimitsToParallel();
=======
    bool loopCondition = current->children.size() == 1 && current->perfectLoop == 1 && !current->hasLimitsToParallel();
>>>>>>> master

    // TODO: need to rewrite
    /*
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
                outerTightened = loopTransformTighten.tighten(outerLoop, 2);
                LoopGraph *firstChild = current->childs.at(0);
                if (outerTightened) {
                    firstChild->perfectLoop = ((SgForStmt *) firstChild->loop)->isPerfectLoopNest();
                }
                __spf_print(1, "createNestedLoops for loop at %d. Tighten success: %d\n", current->lineNum, outerTightened);

                char buf[256];
                sprintf(buf, "loops on lines %d and %d were combined", current->lineNum, firstChild->lineNum);
                messages.push_back(Messages(NOTE, current->lineNum, buf, 2005));
            }
        }
    }

    wasTightened = outerTightened;
    for (int i = 0; i < current->childs.size(); ++i) 
    {
        __spf_print(1, "createNestedLoops for loop at %d. Transform child %d\n", current->lineNum, i);
        bool result = createNestedLoops(current->childs[i], depInfoForLoopGraph, messages);
        wasTightened = wasTightened || result;
    }    
    
    //update perfect loop
    current->recalculatePerfect();
    __spf_print(1, "createNestedLoops for loop at %d. End\n", current->lineNum);
    */
    return wasTightened;
}

//TODO: need to delete! 
/*
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

static void addToMap(SgStatement *in, SgStatement *out, depGraph *outerDepGraph, std::map<SgSymbol*, DependencyType> &depMap)
{
    depNode *node = outerDepGraph->isThereAnEdge(in, out);
    if (node != nullptr)
    {
        DependencyType type = CreateNestedLoopsUtils::fromDepNode(node);
        SgSymbol *symbol = node->varout->symbol();
        depMap.insert(std::make_pair(symbol, type));
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
            addToMap(stmt, bodyStmt, outerDepGraph, depMap);
            addToMap(bodyStmt, stmt, outerDepGraph, depMap);
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

*/ 
