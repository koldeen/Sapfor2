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
using std::make_pair;

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

static void fillPrivateAndReductionFromComment(SgStatement *st, set<SgSymbol*> &privates, 
                                               map<string, set<SgSymbol*>> &reduction,
                                               map<string, set<tuple<SgSymbol*, SgSymbol*, int>>> &reduction_loc)
{
    for (auto &data : getAttributes<SgStatement*, SgStatement*>(st, set<int>{ SPF_ANALYSIS_DIR }))
    {
        fillPrivatesFromComment(new Statement(data), privates);
        fillReductionsFromComment(new Statement(data), reduction);
        fillReductionsFromComment(new Statement(data), reduction_loc);
    }
}

static pair<SgForStmt*, depGraph*> getDepGraph(LoopGraph *loopGraph, const map<LoopGraph*, depGraph*> &depInfoForLoopGraph)
{
    SgForStmt *sgForStmt = NULL;
    depGraph *dg = NULL;

    if (depInfoForLoopGraph.count(loopGraph) == 0)
        __spf_print(1, "getDepGraph for loop at %d. No depGraph found\n", loopGraph->lineNum);
    else 
    {
        dg = depInfoForLoopGraph.at(loopGraph);
        sgForStmt = isSgForStmt(dg->loop);
        if (sgForStmt == NULL) 
            __spf_print(1, "getDepGraph for loop at %d. SgForStmt missing for depGraph\n", loopGraph->lineNum);
    }

    return make_pair(sgForStmt, dg);
}

static ddnature fromDepNode(depNode *node)
{
    //std::cout << node->typedep << std::endl;
    if (node->typedep == SCALARDEP || node->typedep == PRIVATEDEP || node->typedep == REDUCTIONDEP) 
    {
        ddnature nature = (ddnature) node->kinddep;
        switch (nature) 
        {
            case ddflow:               
            case ddanti:               
            case ddoutput:               
            case ddreduce:
                return nature;
            default:
                break;
        }
    }

    return dd_unknown;
}


static void printDepGraph(depGraph *dg) 
{
    if(dg == NULL)
        return;

    for (depNode *dn : dg->getNodes())
    {
        dn->displayDep();
        //std::cout << (int) fromDepNode(dn) << std::endl;
        int out = dn->stmtout != NULL ? dn->stmtout->lineNumber() : -1;
        int in = dn->stmtin != NULL ? dn->stmtin->lineNumber() : -1;
        __spf_print(1, "dep from %d --> %d\n", out, in);
    }
}

static void addToMap(SgStatement *in, SgStatement *out, depGraph *outerDepGraph, map<SgSymbol*, ddnature> &depMap)
{
    depNode *node = outerDepGraph->isThereAnEdge(in, out);
    if (node != NULL)
    {
        ddnature type = fromDepNode(node);
        SgSymbol *symbol = node->varout->symbol();
        //std::cout << symbol << std::endl;
        depMap.insert(make_pair(symbol, type));
    }
}

static SgStatement* getLastLoopStatement(SgForStmt* pForLoop) 
{
    SgStatement* stmt = pForLoop->body();
    while (stmt &&
          !(isSgControlEndStmt(stmt) && stmt->controlParent() && stmt->controlParent()->id() == pForLoop->id())) 
        stmt = stmt->lexNext();
    
    return stmt;
}

static map<SgSymbol*, ddnature> buildTransformerDependencyMap(SgForStmt *outerLoop, depGraph *outerDepGraph, SgForStmt *innerLoop, depGraph *innerDepGraph)
{
    __spf_print(1, "Print outer depgraph START\n");
    printDepGraph(outerDepGraph);
    __spf_print(1, "Print outer depgraph END\n");
    
    __spf_print(1, "Print inner depgraph START\n");
    printDepGraph(innerDepGraph);
    __spf_print(1, "Print inner depgraph END\n");

    SgStatement *innerEnddo = getLastLoopStatement(innerLoop);
    map<SgSymbol*, ddnature> depMap;

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

static SgForStmt* lexNextLoop(SgStatement* pStmt, SgStatement* end) 
{
    SgStatement* pClosestDo = pStmt;
    while (!isSgForStmt(pClosestDo) && pClosestDo != end)
        pClosestDo = pClosestDo->lexNext();    
    return isSgForStmt(pClosestDo);
}

static ddnature getOrDefault(const map<SgSymbol*, ddnature> &inMap, SgSymbol *key, ddnature defaultValue)
{
    //implementation must be visible to compiler 
    auto it = inMap.find(key);
    if (it == inMap.end())
        return defaultValue;
    else
        return it->second;
};

static bool validateInvariantStatementBeforeLoop(SgStatement* invBegin, SgStatement* invEnd, const map<SgSymbol*, ddnature> &dependencies) 
{
    //by type check
    SgStatement* stmt = invBegin;
    bool allAssignment = true;
    while (stmt != invEnd && allAssignment) 
    {
        allAssignment = allAssignment && isSgAssignStmt(stmt);
        stmt = stmt->lexNext();
    }

    if (allAssignment) 
    {
        bool hasFlowDep = false;
        stmt = invBegin;
        while (stmt != invEnd && !hasFlowDep) 
        {
            SgAssignStmt* assignStmt = isSgAssignStmt(stmt);
            SgSymbol* symbol = assignStmt->lhs()->symbol();
            auto dependency = getOrDefault(dependencies, symbol, ddnovalue);
            hasFlowDep = hasFlowDep
                || dependency == ddflow
                || dependency == dd_unknown;
            stmt = stmt->lexNext();
        }

        if (hasFlowDep) 
        {
            bool hasAntiOrOutputDep = false;
            stmt = invBegin;
            while (stmt != invEnd && !hasAntiOrOutputDep) 
            {
                SgAssignStmt* assignStmt = isSgAssignStmt(stmt);
                SgSymbol* symbol = assignStmt->lhs()->symbol();
                auto dependency = getOrDefault(dependencies, symbol, ddnovalue);
                hasAntiOrOutputDep = hasAntiOrOutputDep
                    || dependency == ddanti
                    || dependency == ddoutput
                    || dependency == dd_unknown;
                stmt = stmt->lexNext();
            }

            if (!hasAntiOrOutputDep) 
            {
                //TODO: add message
                //string msg = "Only flow dependencies present, can tighten.";
                //this->addMessage(0, invBegin->lineNumber(), msg);
                return true;
            }
        }
        else 
        {
            //TODO: add message
            //string msg = "Invariant value not used in loop, can tighten.";
            //this->addMessage(0, invBegin->lineNumber(), msg);
            return true;
        }
    }
    //TODO: add message
    //string msg = "Invariant cannot be moved into loop.";
    //this->addMessage(0, invBegin->lineNumber(), msg);
    return false;
}

static bool validateInvariantStatementAfterLoop(SgStatement* invBegin, SgStatement* invEnd, const map<SgSymbol*, ddnature> &dependencies) 
{
    if (invBegin == invEnd) 
    {
        //TODO: add message
        //string msg = "No invariants after loop";
        //this->addMessage(0, invBegin->lineNumber(), msg);
        return true; //no after invariant;
    }
    //TODO: add message
    //string msg = "There are invariants after loop, cannot tighten";
    //this->addMessage(0, invBegin->lineNumber(), msg);
    return false; //unknown, why would loop need that
}

static bool canTightenSingleLevel(SgForStmt* outerLoop, const map<SgSymbol*, ddnature> &dependencies) 
{
    SgStatement* outerEnddo = getLastLoopStatement(outerLoop);
    SgForStmt* innerLoop = lexNextLoop(outerLoop->lexNext(), outerEnddo);
    if (innerLoop != NULL) 
    {
        bool beforeValid = validateInvariantStatementBeforeLoop(outerLoop->lexNext(), innerLoop, dependencies);
        bool afterValid = validateInvariantStatementAfterLoop(getLastLoopStatement(innerLoop)->lexNext(), outerEnddo, dependencies);
        return beforeValid && afterValid;
    }
    else 
        return false;    
}

static int canTighten(SgForStmt* pForLoop, const map<SgSymbol*, ddnature> &dependencies) 
{
    int nestDepth = 1;
    SgForStmt* processedLoop = pForLoop;
    while (canTightenSingleLevel(processedLoop, dependencies)) 
    {
        processedLoop = lexNextLoop(processedLoop->lexNext(), NULL);
        nestDepth++;
    }

    if (nestDepth == 1) 
        return 0;
    else 
        return nestDepth;    
}

static int canTighten(SgForStmt* pForLoop) 
{
    int nestnessLevel = 1;
    SgForStmt* nextOuterLoop = pForLoop;
    while (nextOuterLoop) 
    {
        SgStatement* outerLoopControlEnd = getLastLoopStatement(nextOuterLoop);
        SgStatement* nextInnerLoop = nextOuterLoop->lexNext();
        while (!isSgForStmt(nextInnerLoop) && nextInnerLoop != outerLoopControlEnd)
            nextInnerLoop = nextInnerLoop->lexNext();
        
        if (nextInnerLoop == outerLoopControlEnd) //no for loops found in outerloop            
            nextOuterLoop = NULL;        
        else //inner for loop found
        {
            //check control ends
            SgForStmt* innerLoop = isSgForStmt(nextInnerLoop);
            SgStatement* innerControlEnd = getLastLoopStatement(innerLoop);
            if (innerControlEnd->lexNext() == outerLoopControlEnd) 
            {
                //controls are tight, can tighten this
                nestnessLevel++;
                nextOuterLoop = innerLoop;
            }
            else
            {
                //TODO: invariants after loop body
                //cannot tighten loop further, stop here
                nextOuterLoop = NULL;
            }
        }
    }
    if (nestnessLevel == 1) 
        return 0;
    else 
        return nestnessLevel;    
}

static SgStatement* sinkIntoNextNearestLoop(SgStatement* pStmt, SgStatement* nextLoop) 
{
    //Log::debug("sinkIntoNextNearestLoop " + getLineNumber(pStmt));

    SgStatement *extr = pStmt->extractStmt();
    nextLoop->insertStmtAfter(*extr, *nextLoop);
    return pStmt;
}

static SgControlEndStmt* lexPrevEnddo(SgStatement* pStmt, SgStatement* end) 
{
    SgStatement* pClosestEndDo = pStmt;
    while (!isSgControlEndStmt(pClosestEndDo) && pClosestEndDo != end)
        pClosestEndDo = pClosestEndDo->lexPrev();    
    return isSgControlEndStmt(pClosestEndDo);
}

static SgStatement* sinkIntoPreviousNearestLoop(SgStatement* pStmt) 
{
    //Log::debug("sinkIntoPreviousNearestLoop " + getLineNumber(pStmt));

    SgControlEndStmt * ctrlEnd = lexPrevEnddo(pStmt, NULL);
    SgForStmt * scope = isSgForStmt(ctrlEnd->controlParent());
    SgStatement * pStmtCopy = pStmt->extractStmt();
    ctrlEnd->insertStmtBefore(*pStmtCopy, *scope);
    return pStmtCopy;
}

static void tightenSingleLevel(SgForStmt* outerLoop, SgForStmt* topLevelForLoop) 
{
    SgForStmt* innerLoop = lexNextLoop(outerLoop->lexNext(), NULL);
    {
        //move statements after given loop before the inner loop

        //moving these statements is done in reverse order,
        // because insertion is always after the inner loop header

        //begin := statement before closest inner loop header
        SgStatement* begin = innerLoop->lexPrev();
        SgStatement* end = outerLoop;
        SgStatement* stmt = begin;
        SgStatement* next;
        while (stmt != end) 
        {
            next = stmt->lexPrev();
            sinkIntoNextNearestLoop(stmt, innerLoop);
            stmt = next;
        }
    }

    {
        //move statements before given loop enddo after the inner loop enddo

        //moving these statements is done in normal order,
        // insertion is done before inner loop enddo

        //begin := statement after closest inner loop enddo
        SgStatement* begin = getLastLoopStatement(innerLoop)->lexNext();
        SgStatement* end = getLastLoopStatement(outerLoop);
        SgStatement* stmt = begin;
        SgStatement* next;
        while (stmt != end) 
        {
            next = stmt->lexNext();
            sinkIntoPreviousNearestLoop(stmt);
            stmt = next;
        }
    }
}

static bool tighten(SgForStmt* pForLoop, int level) 
{
    if (level > canTighten(pForLoop))     
        //cannot do that
        return false;
    
    int processing = 2;
    SgForStmt* processedLoop = pForLoop;

    while (processing <= level) 
    {
        tightenSingleLevel(processedLoop, pForLoop);        
        processedLoop = lexNextLoop(processedLoop->lexNext(), NULL);
        processing++;
    }
    return true;
}

bool createNestedLoops(LoopGraph *current, const map<LoopGraph*, depGraph*> &depInfoForLoopGraph, vector<Messages> &messages)
{
    bool wasTightened = false;
    // has non nested child loop
    __spf_print(1, "  createNestedLoops for loop at %d. Start\n", current->lineNum);
    bool outerTightened = false;
    bool loopCondition = current->children.size() == 1 && current->perfectLoop == 1 && !current->hasLimitsToParallel();

    if (loopCondition)
    {
        pair<SgForStmt*, depGraph*> outerLoopDependencies = getDepGraph(current, depInfoForLoopGraph);
        pair<SgForStmt*, depGraph*> innerLoopDependencies = getDepGraph(current->children.at(0), depInfoForLoopGraph);

        if (outerLoopDependencies.first && outerLoopDependencies.second) 
        {
            SgForStmt *outerLoop = outerLoopDependencies.first;

            map<SgSymbol*, ddnature> depMap = buildTransformerDependencyMap(outerLoop, outerLoopDependencies.second, innerLoopDependencies.first, innerLoopDependencies.second);
            if (canTighten(outerLoop, depMap) >= 2) 
            {
                outerTightened = tighten(outerLoop, 2);
                LoopGraph *firstChild = current->children.at(0);

                if (outerTightened) 
                {
                    firstChild->perfectLoop = ((SgForStmt *) firstChild->loop)->isPerfectLoopNest();
                }

                __spf_print(1, "createNestedLoops for loop at %d. Tighten success: %d\n", current->lineNum, outerTightened);

                wchar_t buf[256];
                //sprintf(buf, "loops on lines %d and %d were combined", current->lineNum, firstChild->lineNum);
                //messages.push_back(Messages(NOTE, current->lineNum, buf, 2005));
            }
        }
    }

    wasTightened = outerTightened;
    for (int i = 0; i < current->children.size(); ++i) 
    {
        __spf_print(1, "createNestedLoops for loop at %d. Transform child %d\n", current->lineNum, i);
        bool result = createNestedLoops(current->children[i], depInfoForLoopGraph, messages);
        wasTightened = wasTightened || result;
    }    
    
    //update perfect loop
    current->recalculatePerfect();
    __spf_print(1, "createNestedLoops for loop at %d. End\n", current->lineNum);
    
    return wasTightened;
}