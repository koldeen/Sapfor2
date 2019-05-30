#define _LEAK_
#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>
#include <vector>
#include <fstream>

#include "../GraphCall/graph_calls.h"
#include "private_analyzer.h"
#include "dvm.h"
#include "../CFGraph/CFGraph.h"

using std::vector;

void PrivateAnalyzer(SgFile *file, vector<FuncInfo*> &funcs)
{    
    for (int i = 0; i < funcs.size(); ++i)
        if (funcs[i]->doNotAnalyze == false && funcs[i]->deadFunction == false)
            Private_Vars_Analyzer(funcs[i]->funcPointer);
}

#if NEW_CFG
static void SetUpVars(CFG_CommonData* commons, CFG_Call *calls, const CFG_CallData *m, CFG_DoLoopDataList* list)
{
    G_pCommons = commons;
    G_pCalls = calls;
    G_currentProcedure = m;
    G_mainProcedure = G_currentProcedure;
    G_doLoopList = list;
}

static void FillCFGSets(CFG_ControlFlowGraph* graph)
{
    graph->PrivateAnalyzer();
}

static void ClearMemoryAfterDelay(CFG_ActualDelayedData* d)
{
    while (d != NULL) 
    {
        d->commons.clear();
        delete d->buse;
        CFG_ActualDelayedData* tmp = d;
        d = d->next;
        delete tmp;
    }
}

static void FillPrivates(CFG_ControlFlowGraph* graph)
{
    CFG_ActualDelayedData* d = graph->ProcessDelayedPrivates(G_pCommons, G_mainProcedure, NULL, NULL, false, -1);
    ClearMemoryAfterDelay(d);
    if (G_privateDelayedList)
    {
        //TODO::
        //G_privateDelayedList->PrintWarnings();
    }
}

void PrivateAnalyzerForMain(SgStatement* start)
{
    if (start->variant() != PROG_HEDR)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    CFG_Call calls;
    CFG_CommonData commons;
    CFG_DoLoopDataList doloopList;
    SetUpVars(&commons, &calls, calls.AddHeader(start, false, start->symbol(), current_file_id), &doloopList);

    //stage 1: preparing graph data
    CFG_ControlFlowGraph* CGraph = GetControlFlowGraphWithCalls(true, start, &calls, &commons);
    calls.AssociateGraphWithHeader(start, CGraph);
    commons.MarkEndOfCommon(G_currentProcedure);

    //DEBUG: graphvis
    /*
    std::fstream fs;
    fs.open("graph.txt", std::fstream::out);
    fs << CGraph->GetVisualGraph(&calls);
    fs.close();
    */

    G_currentProcedure->graph->GetPrivate();

    //DEBUG
    //calls.PrintControlFlows();

    //stage 2: data flow analysis
    FillCFGSets(CGraph);
    //stage 3: fulfilling loop data
    FillPrivates(CGraph);

    delete CGraph;
    if (G_privateDelayedList)
        delete G_privateDelayedList;
    G_privateDelayedList = NULL;
}
#endif