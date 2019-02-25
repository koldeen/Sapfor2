#include "loops_splitter.h"

#include "../LoopAnalyzer/loop_analyzer.h"

#include <string>
#include <vector>
/*удалить от сих*/
#include "dvm.h"
#include "../GraphLoop/graph_loops.h"
/*до сих*/
using std::string;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;

static SgForStmt* createNewLoop(LoopGraph *globalLoop)
{
    SgStatement *insertBeforeThis = globalLoop->loop->GetOriginal();
    SgStatement *newLoop = NULL;
    LoopGraph *curLoopGraph = globalLoop;
    vector<LoopGraph*> graphs(globalLoop->perfectLoop);

    for(int i = 0; i < globalLoop->perfectLoop; ++i) {
        graphs[i] = curLoopGraph;
        if(curLoopGraph->children.size())
            curLoopGraph = curLoopGraph->children[0];
    }

    for(int i = graphs.size()-1; i > 0; --i) {
        SgForStmt* curForStmt = (SgForStmt*) graphs[i]->loop->GetOriginal();
        newLoop = new SgForStmt(curForStmt->doName(), curForStmt->start(), curForStmt->end(), curForStmt->step(), newLoop);
    }

    SgForStmt *curForStmt = (SgForStmt*) graphs[0]->loop->GetOriginal();
    SgForStmt *newGlobalLoop = new SgForStmt(curForStmt->doName(), curForStmt->start(), curForStmt->end(), curForStmt->step(), newLoop);

    insertBeforeThis->insertStmtBefore(*newGlobalLoop);

    SgStatement *lowestInsertedFor = insertBeforeThis;
    for(int i=0; i< globalLoop->perfectLoop; ++i) //пройти по всем enddo
        lowestInsertedFor = lowestInsertedFor->lexPrev();
    return (SgForStmt*)lowestInsertedFor->lexPrev(); //самый внутренний цикл
}
static void addDepGraph(SgForStmt* loopStmt, vector<pair<LoopGraph*, depGraph*>> &deps, LoopGraph *mainGraph, map<LoopGraph*, depGraph*> &depInfoForLoopGraph)
{
    for(int i=0;i<mainGraph->children.size(); ++i)
        if(mainGraph->children[i]->loop->GetOriginal()->id() == loopStmt->id())
        {
            auto found = depInfoForLoopGraph.find(mainGraph->children[i]);
            deps.push_back(make_pair(mainGraph->children[i], found != depInfoForLoopGraph.end() ? found->second : NULL));
        }
}

static bool dependenciesAreEnclosed(vector<pair<LoopGraph*, depGraph*>> &deps, depGraph *parentDepGraph)
{/*
    printf("parent graph dependencies: ");
    if(parentDepGraph) {
        printf("\n");
        parentDepGraph->display();
    } else
        printf("none\n");
    for(auto& p : deps)
    {
        printf("%s\n",p.first->loop->GetOriginal()->unparse());
        if(p.second)
            p.second->display();
        else
            printf("No dependencies\n");
    }*/
    return false;
}

static bool setupSinceTill(LoopGraph *lowestParentGraph, map<LoopGraph*, depGraph*> &depInfoForLoopGraph, SgStatement *&since, SgStatement *&till)
{
    auto found = depInfoForLoopGraph.find(lowestParentGraph);

    if(lowestParentGraph->children.size() == 0)
        return false;

    const std::set<std::string> privVars;
    depGraph *lowestParentDepGraph = getDependenciesGraph(lowestParentGraph, current_file, &privVars);
    if(lowestParentDepGraph)
        lowestParentDepGraph->display();

    vector<pair<LoopGraph*, depGraph*>> deps;

    //Нет зависиомостей в цикле. выносится каждый подцикл и операции до следующего подцикла
    //для первого цикла захватываются предшествующие операции.
    SgForStmt* loopStmt = since->variant() == FOR_NODE ? (SgForStmt*)since : NULL;
    if(loopStmt)
        addDepGraph(loopStmt, deps, lowestParentGraph, depInfoForLoopGraph);
    till = since->lastNodeOfStmt()->lexNext();
    while(till->variant() != CONTROL_END)
    {
        if(till->variant() == FOR_NODE && loopStmt && dependenciesAreEnclosed(deps, lowestParentDepGraph))
            return true; //Между since и till есть цикл и зависимости позволяют вырвать кусок с since по till
        else loopStmt = (SgForStmt*) till;
        till = till->lastNodeOfStmt()->lexNext();
    }

    return false;
}

static void moveStatements(SgForStmt *newLoop, SgStatement *since, SgStatement *till)
{
    SgStatement *toMoveStmt = since;
    SgStatement *lastInserted = newLoop;
    while(toMoveStmt != till)
    {
        SgStatement *st = toMoveStmt->copyPtr();
        lastInserted->insertStmtAfter(*st);
        lastInserted = lastInserted->lexNext()->lastNodeOfStmt();

        SgStatement *toDelete = toMoveStmt;
        toMoveStmt = toMoveStmt->lastNodeOfStmt()->lexNext();
        toDelete->deleteStmt();
    }
}

static void splitLoop(LoopGraph *loopGraph, std::map<LoopGraph*, depGraph*> &depInfoForLoopGraph)
{
    LoopGraph *lowestParentGraph = loopGraph;
    for(int i = 0; i < loopGraph->perfectLoop; ++i)
    {
        if(lowestParentGraph->children.size() == 1)
            lowestParentGraph = lowestParentGraph->children[0];
    }

    SgStatement *since = ((SgForStmt*)lowestParentGraph->loop->GetOriginal())->body();
    SgStatement *till;
    while(setupSinceTill(lowestParentGraph, depInfoForLoopGraph, since, till))
    {
        moveStatements(createNewLoop(loopGraph), since, till);
        since = till;
    }
}


void splitLoops(SgFile *file, vector<LoopGraph*> &loopGraphs, map<LoopGraph*, depGraph*> &depInfoForLoopGraph)
{
    if(string(file->filename()) == "z_solve_inlined.f")
        for(auto& loopGraph : loopGraphs)
        {
            splitLoop(loopGraph, depInfoForLoopGraph);
        }

    if(string(file->filename()) == "COMPOZ.FOR")
        for(auto& loopGraph : loopGraphs)
        {
            splitLoop(loopGraph, depInfoForLoopGraph);
        }
}
