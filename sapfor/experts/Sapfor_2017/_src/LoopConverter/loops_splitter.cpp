#include "loops_splitter.h"
#include <string>
#include <vector>
/*удалить от сих*/
#include "dvm.h"
#include "../GraphLoop/graph_loops.h"
/*до сих*/
using std::string;
using std::vector;

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

static bool setupSinceTill(LoopGraph *lowestParentGraph, depGraph *lowestParentDepGraph, SgStatement *&since, SgStatement *&till)
{
    if(lowestParentDepGraph) // есть зависимости в цикле
    {
        since = till = NULL;
        printf("Splitting of loops with dependencies not implemented yet.\n");
//        lowestParentDepGraph->display();
        return false;
    }
    //Нет зависиомостей в цикле. выносится каждый подцикл и операции до следующего подцикла
    //для первого цикла захватываются предшествующие операции.
    bool hasLoop = since->variant() == FOR_NODE;
    till = since->lastNodeOfStmt()->lexNext();
    while(till->variant() != CONTROL_END)
    {
        if(till->variant() == FOR_NODE && hasLoop)
            return true; //Между since и till есть цикл
        else hasLoop = true;
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
    auto found = depInfoForLoopGraph.find(loopGraph);
    depGraph *lowestParentDepGraph = (found == depInfoForLoopGraph.end() ? NULL : found->second);
    for(int i = 0; i < loopGraph->perfectLoop; ++i)
        if(lowestParentGraph->children.size() == 1) {
            lowestParentGraph = lowestParentGraph->children[0];
            found = depInfoForLoopGraph.find(lowestParentGraph);
            lowestParentDepGraph = (found == depInfoForLoopGraph.end() ? NULL : found->second);
        }

    SgStatement *since = ((SgForStmt*)lowestParentGraph->loop->GetOriginal())->body();
    SgStatement *till;
    while(setupSinceTill(lowestParentGraph, lowestParentDepGraph, since, till))
    {
        moveStatements(createNewLoop(loopGraph), since, till);
        since = till;
    }
}


void splitLoops(SgFile *file, std::vector<LoopGraph*> &loopGraphs, std::map<LoopGraph*, depGraph*> &depInfoForLoopGraph)
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
