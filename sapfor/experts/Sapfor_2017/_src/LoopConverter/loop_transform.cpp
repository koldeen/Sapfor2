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
    if (node->typedep == SCALARDEP || node->typedep == PRIVATEDEP) 
    {
        ddnature nature = (ddnature) node->kinddep;
        switch (nature) 
        {
            case ddflow:
            case ddanti:
            case ddoutput:
                return nature;
            default:
                break;
        }
    }

    return dd_unknown;
}

static void displayDep(const depNode *dn)
{
    SgExpression *ex1, *ex2;
    int i;
    ddnature nature;
    ex1 = dn->varin;
    ex2 = dn->varout;


    if (!dn->typedep)
    {
        __spf_print(1, "UNKNOWN DATA DEPENDENCE\n");
        return;
    }

    if (dn->typedep == ARRAYDEP)
    {
        nature = (ddnature)dn->kinddep;
        __spf_print(1, "------> ");
        switch (nature)
        {
        case ddflow:
            __spf_print(1, "FLOW dependence between ");
            break;
        case ddanti:
            __spf_print(1, "ANTI dependence between ");
            break;
        case ddoutput:
            __spf_print(1, "OUTPUT dependence between ");
            break;
        case ddreduce:
            __spf_print(1, "REDUCE dependence between ");
            break;
        }
        
        __spf_print(1, "%s", ex1->unparse());
        __spf_print(1, " (line %d) and ", dn->stmtin->lineNumber());
        __spf_print(1, "%s", ex2->unparse());
        __spf_print(1, " (line %d) with vector (", dn->stmtout->lineNumber());
        for (i = 1; i <= dn->lenghtvect; i++)
        {
            if (dn->knowndist[i])
                __spf_print(1, "%d", dn->distance[i]);
            else
            {
                if (dn->distance[i] & DEPZERO)
                    __spf_print(1, "0");
                if (dn->distance[i] & DEPGREATER)
                    __spf_print(1, "+");
                if (dn->distance[i] & DEPLESS)
                    __spf_print(1, "-");
            }

            if (i < dn->lenghtvect)
                __spf_print(1, ", ");
        }
        __spf_print(1, ")\n");
    }
    else
    {
        __spf_print(1, "------> ");
        __spf_print(1, "This is a Scalar Dep on ");
        __spf_print(1, "%s", ex1->unparse());
        if (dn->typedep == PRIVATEDEP)
            __spf_print(1, " and variable can be PRIVATE");
        if (dn->typedep == REDUCTIONDEP)
            __spf_print(1, " and variable can be REDUCTION with kind %d", dn->kinddep);
        __spf_print(1, "\n");
    }
}

static void printDepGraph(depGraph *dg) 
{
    if(dg == NULL)
        return;

    for (depNode *dn : dg->getNodes())
    {
        displayDep(dn);
        /*int out = dn->stmtout != NULL ? dn->stmtout->lineNumber() : -1;
        int in = dn->stmtin != NULL ? dn->stmtin->lineNumber() : -1;
        __spf_print(1, "dep from %d --> %d\n", out, in);*/
    }
}

static void addToMap(SgStatement *stmt, depGraph *depGraph, map<SgSymbol*, ddnature> &depMap)
{
    depNode *node = NULL;

    for (auto &dn : depGraph->getNodes())
    {
        //TODO: process ARRAYDEP!
        if (dn->typedep > ARRAYDEP && dn->stmtin == stmt)
        {
            node = dn;
            break;
        }
    }

    if (node != NULL)
    {
        ddnature type = fromDepNode(node);
        if (node->typedep == SCALARDEP)
            type = ddoutput;

        SgSymbol *symbol = node->varin->symbol();

        auto it = depMap.find(symbol);
        if(it != depMap.end())
            depMap[symbol] = (it->second < type ? type : it->second);
        else
            depMap.insert(make_pair(symbol, type));
    }
}

static map<SgSymbol*, ddnature> buildTransformerDependencyMap(SgForStmt *outerLoop, depGraph *outerDepGraph, SgForStmt *innerLoop, depGraph *innerDepGraph)
{
    __spf_print(1, "Print outer depgraph START\n");
    printDepGraph(outerDepGraph);
    __spf_print(1, "Print outer depgraph END\n");
    
    __spf_print(1, "Print inner depgraph START\n");
    printDepGraph(innerDepGraph);
    __spf_print(1, "Print inner depgraph END\n");

    map<SgSymbol*, ddnature> depMap;

    for (SgStatement *stmt = outerLoop->lexNext(); stmt != outerLoop->lastNodeOfStmt(); stmt = stmt->lexNext())
    {
        addToMap(stmt, innerDepGraph, depMap);
        addToMap(stmt, outerDepGraph, depMap);
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

static bool validateInvariantStatement(SgStatement* invBegin, SgStatement* invEnd, const map<SgSymbol*, ddnature> &dependencies) 
{
    //by type check
    SgStatement* stmt = invBegin;
    bool allAssignmentOrIf = true;
    while (stmt != invEnd && allAssignmentOrIf) 
    {
        allAssignmentOrIf = allAssignmentOrIf && (isSgAssignStmt(stmt) || isSgIfStmt(stmt) || isSgLogIfStmt(stmt) || isSgControlEndStmt(stmt));
        SgStatement* ass = isSgAssignStmt(stmt);
        //TODO:
        if (ass)
        {
            if (ass->expr(0)->variant() == ARRAY_REF)
            {
                allAssignmentOrIf = false;
                break;
            }
        }
        stmt = stmt->lexNext();
    }

    if (allAssignmentOrIf) 
    {
        bool hasFlowDep = false;
        stmt = invBegin;
        while (stmt != invEnd && !hasFlowDep) 
        {
            SgAssignStmt* assignStmt = isSgAssignStmt(stmt);
            if(assignStmt)
            {
                SgSymbol* symbol = assignStmt->lhs()->symbol();
                auto dependency = getOrDefault(dependencies, symbol, ddnovalue);
                hasFlowDep = hasFlowDep
                    || dependency == ddflow
                    || dependency == dd_unknown;
            }
            stmt = stmt->lexNext();
        }

        if (hasFlowDep) 
        {
            bool hasAntiOrOutputDep = false;
            stmt = invBegin;
            while (stmt != invEnd && !hasAntiOrOutputDep) 
            {
                SgAssignStmt* assignStmt = isSgAssignStmt(stmt);
                if(assignStmt)
                {
                    SgSymbol* symbol = assignStmt->lhs()->symbol();
                    auto dependency = getOrDefault(dependencies, symbol, ddnovalue);
                    hasAntiOrOutputDep = hasAntiOrOutputDep
                        || dependency == ddanti
                        || dependency == ddoutput
                        || dependency == dd_unknown;
                }
                stmt = stmt->lexNext();
            }

            if (!hasAntiOrOutputDep) 
            {
                __spf_print(1, "%d : Only flow dependencies present, can tighten.\n", invBegin->lineNumber());
                return true;
            }
        }
        else 
        {
            __spf_print(1, "%d : Invariant value not used in loop, can tighten.\n", invBegin->lineNumber());
            return true;
        }
    }
    __spf_print(1, "%d : Invariant cannot be moved into loop.\n", invBegin->lineNumber());
    return false;
}

static bool canTightenSingleLevel(SgForStmt* outerLoop, const map<SgSymbol*, ddnature> &dependencies) 
{
    SgStatement* outerEnddo = outerLoop->lastNodeOfStmt();
    SgForStmt* innerLoop = lexNextLoop(outerLoop->lexNext(), outerEnddo);
    if (innerLoop != NULL) 
    {
        bool beforeValid = validateInvariantStatement(outerLoop->lexNext(), innerLoop, dependencies);
        //TODO:
        //validateInvariantStatement(innerLoop->lastNodeOfStmt()->lexNext(), outerEnddo, dependencies);
        bool afterValid = (outerLoop->lastNodeOfStmt() == innerLoop->lastNodeOfStmt()->lexNext());

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
        SgStatement* outerLoopControlEnd = nextOuterLoop->lastNodeOfStmt();
        SgStatement* nextInnerLoop = nextOuterLoop->lexNext();
        while (!isSgForStmt(nextInnerLoop) && nextInnerLoop != outerLoopControlEnd)
            nextInnerLoop = nextInnerLoop->lexNext();
        
        if (nextInnerLoop == outerLoopControlEnd) //no for loops found in outerloop            
            nextOuterLoop = NULL;        
        else //inner for loop found
        {
            nestnessLevel++;
            nextOuterLoop = isSgForStmt(nextInnerLoop);
        }
    }
    if (nestnessLevel == 1) 
        return 0;
    else 
        return nestnessLevel;    
}

static SgStatement* sinkIntoNextNearestLoop(SgStatement* pStmt, SgStatement* nextLoop) 
{
    __spf_print(1, "%d : SinkIntoNextNearestLoop\n", pStmt->lineNumber());

    if(!isSgIfStmt(pStmt->controlParent()))
    {
        SgStatement *extr = pStmt->extractStmt();
        nextLoop->insertStmtAfter(*extr, *nextLoop);
    }
    
    return pStmt;
}

static SgStatement* sinkIntoPreviousNearestLoop(SgStatement* pStmt, SgStatement* prevLoop, SgStatement* afterStmt) 
{
    __spf_print(1, "%d : sinkIntoPreviousNearestLoop\n", pStmt->lineNumber());

    if(!isSgIfStmt(pStmt->controlParent()))
    {
        SgStatement *extr = pStmt->extractStmt();
        afterStmt->insertStmtAfter(*extr, *prevLoop);
    }

    return pStmt;
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
        SgStatement* begin = outerLoop->lastNodeOfStmt()->lexPrev();
        SgStatement* end = innerLoop->lastNodeOfStmt();
        SgStatement* afterStmt = end->lexPrev();
        SgStatement* stmt = begin;
        SgStatement* next;
        while (stmt != end) 
        {
            next = stmt->lexPrev();
            sinkIntoPreviousNearestLoop(stmt, innerLoop, afterStmt);
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

        if (outerLoopDependencies.first && outerLoopDependencies.second && innerLoopDependencies.first && innerLoopDependencies.second) 
        {
            SgForStmt *outerLoop = outerLoopDependencies.first;

            map<SgSymbol*, ddnature> depMap = buildTransformerDependencyMap(outerLoop, outerLoopDependencies.second, innerLoopDependencies.first, innerLoopDependencies.second);
            if (canTighten(outerLoop, depMap) >= 2) 
            {
                outerTightened = tighten(outerLoop, 2);
                LoopGraph *firstChild = current->children.at(0);

                if (outerTightened)
                    firstChild->perfectLoop = ((SgForStmt *) firstChild->loop)->isPerfectLoopNest();

                __spf_print(1, "createNestedLoops for loop at %d. Tighten success: %d\n", current->lineNum, outerTightened);

                wchar_t buf[256];
#ifdef _WIN32
                std::wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"Loops on lines %d and %d were combined", current->lineNum, firstChild->lineNum);
                __spf_printToLongBuf(messageR, R100, current->lineNum, firstChild->lineNum);
                
                messages.push_back(Messages(NOTE, current->lineNum, messageR, messageE, 2005));
#endif
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