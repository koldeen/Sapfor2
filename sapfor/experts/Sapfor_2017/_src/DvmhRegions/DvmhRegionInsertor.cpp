/*
 * DvmhDvmhRegionIsertor.cpp
 *
 *  Created on: May 14, 2018
 *      Author: vladislav
 */

#include "DvmhRegionInsertor.h"

LoopCheckResults::LoopCheckResults() : usesIO(false), hasImpureCalls(false) {}

void DvmhRegionInsertor::printFuncName(SgStatement* st)
{
    if (st->variant() == PROG_HEDR)
    {
        SgProgHedrStmt *progH = (SgProgHedrStmt*) st;
        std::cout << "Program: " << progH->symbol()->identifier() << std::endl;
    }
    else if (st->variant() == PROC_HEDR)
    {
        SgProcHedrStmt *procH = (SgProcHedrStmt*) st;
        std::cout << "Procedure: " << procH->symbol()->identifier() << std::endl;
    }
    else if (st->variant() == FUNC_HEDR)
    {
        SgFuncHedrStmt *funcH = (SgFuncHedrStmt*) st;
        std::cout << "Function: " << funcH->symbol()->identifier() << std::endl;
    }
}

CallData DvmhRegionInsertor::getControlFlowGraph()
{
    int funcNum = file.numberOfFunctions();

    CallData calls;
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file.functions(i);

        CommonData commons;
        SetUpVars(&commons, &calls, calls.AddHeader(st, false, st->symbol(), current_file_id));

        ControlFlowGraph* CGraph = GetControlFlowGraphWithCalls(true, st, &calls, &commons);
        calls.AssociateGraphWithHeader(st, CGraph);
        commons.MarkEndOfCommon(GetCurrentProcedure());
    }

    return calls;
}

void DvmhRegionInsertor::findEdgesForRegions()
{
    for (auto &loopNode: loopGraph)
    {
    	if(!hasLimitsToDvmhParallel(loopNode))
    	{
			DvmhRegion dvmhRegion(loopNode->loop);
			regions.push_back(dvmhRegion);
    	}
    }
}

bool DvmhRegionInsertor::hasLimitsToDvmhParallel(LoopGraph *loop)
{
	bool hasUnpureCalls = true;
	// TODO: check unpure, improve prints
	std::cout << "loop->hasGoto: " << loop->hasGoto << std::endl;
	std::cout << "loop->hasPrints: " << loop->hasPrints << std::endl;
	std::cout << "loop->hasImpureCalls: " << loop->hasImpureCalls << std::endl;

	return loop->hasGoto || loop->hasPrints || loop->hasImpureCalls;
}

void DvmhRegionInsertor::insertRegionDirectives()
{
	for(auto &region: regions)
	{
		SgStatement *regionStartSt = new SgStatement(ACC_REGION_DIR);
		region.getLoop()->insertStmtBefore(*regionStartSt);

		SgStatement *regionEndSt = new SgStatement(ACC_END_REGION_DIR);
		SgStatement *lastStOfTheLoop = region.getLoop()->lastNodeOfStmt();
		lastStOfTheLoop->insertStmtAfter(*regionEndSt);
	}
}

// checks loop node itself, doesn't check its children
LoopCheckResults DvmhRegionInsertor::checkLoopForPurenessAndIO(LoopGraph * loopNode) {
	LoopCheckResults loopCheckResults;

	for (auto &nameAndLineOfFuncCalled: loopNode->calls)
	{
		FuncInfo *calledFuncInfo;

		// TODO: search for func in whole project
		for (auto &funcNode: funcGraph)
		{
			if (funcNode->funcName == nameAndLineOfFuncCalled.first)
			{
				calledFuncInfo = funcNode;
				break;
			}
		}

		if (!calledFuncInfo || !calledFuncInfo->isPure) // if funcInfo was not found assume func to be impure
			loopCheckResults.hasImpureCalls = true;

		if (!calledFuncInfo || calledFuncInfo->usesIO)
			loopCheckResults.usesIO = true;

		if (loopCheckResults.usesIO && loopCheckResults.hasImpureCalls)
			break;
	}

	return loopCheckResults;
}

DvmhRegionInsertor::DvmhRegionInsertor(SgFile *curFile,
		std::vector<LoopGraph *> curLoopGraph,
		std::vector<FuncInfo *> allFuncInfo) :
		file(*curFile),
		loopGraph(curLoopGraph),
		funcGraph(allFuncInfo)
		{}


// TODO: rename it
std::vector<LoopGraph *> DvmhRegionInsertor::updateGraphCall()
{
	for (auto &loopNode: loopGraph)
	{
		// loop itself
		LoopCheckResults loopChecks = checkLoopForPurenessAndIO(loopNode);
		bool hasImpureCalls = loopChecks.hasImpureCalls;
		bool usesIO = loopChecks.usesIO;

		// nested loops
		for (auto &nestedLoop: loopNode->childs) {
			if (hasImpureCalls && usesIO)
				break;

			loopChecks = checkLoopForPurenessAndIO(nestedLoop);

			hasImpureCalls |= loopChecks.hasImpureCalls;
			usesIO |= loopChecks.usesIO;
		}

		loopNode->hasImpureCalls = hasImpureCalls;
		loopNode->hasPrints |= usesIO;	// result of check for loop body is already in this field,
										// we've checked it's func calls, that's why |=
	}

	return loopGraph;
}

void DvmhRegionInsertor::insertDirectives()
{
	updateGraphCall();
    findEdgesForRegions();
    insertRegionDirectives();
/*
	getControlFlowGraph();
    setUpReachingDefenitions();
    insertActualDirectives();
    deleteControlFlowGraph();
*/
}

DvmhRegionInsertor::~DvmhRegionInsertor()
{
	// TODO Auto-generated destructor stub
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion() {}

DvmhRegion::DvmhRegion(SgStatement *st) : loop(st) {}

SgStatement *DvmhRegion::getLoop()
{
	return loop;
}











