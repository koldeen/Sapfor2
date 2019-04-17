/*
 * DvmhRegionIsertor.h
 *
 *  Created on: May 14, 2018
 *      Author: vladislav
 */
#pragma once
#include "dvm.h"
#include "acc_analyzer.h"
#include "../GraphCall/graph_calls_func.h"
#include "../GraphLoop/graph_loops_func.h"
#include "../ExpressionTransform/expr_transform.h"
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>

using namespace std;

#ifndef NULL
#define NULL   ((void *) 0)
#endif

#ifndef SAPFOR_EXPERTS_SAPFOR_2017__SRC_DVMHREGIONS_DVMHREGIONINSERTOR_H_
#define SAPFOR_EXPERTS_SAPFOR_2017__SRC_DVMHREGIONS_DVMHREGIONINSERTOR_H_

struct LoopCheckResults {
	bool usesIO;
	bool hasImpureCalls;

	LoopCheckResults();

	LoopCheckResults(bool, bool);
};

struct DvmhRegion {
	std::vector<LoopGraph *> loops;

	std::vector<SgSymbol*> needActualisation;
	std::vector<SgSymbol*> needActualisationAfter;
	DvmhRegion();
	DvmhRegion(LoopGraph *loopNode);
	bool isInRegion(SgStatement *);
	SgStatement* getFirstSt();
	SgStatement* getLastSt();

	bool addToActualisation(SgSymbol* s) {
		for (auto present : needActualisation) {
			if (s == present) {
				return false;
			}
		}

		needActualisation.push_back(s);
		return true;
	}
};

class DvmhRegionInsertor {
	SgFile &file;
	std::vector<LoopGraph *> loopGraph;
	std::vector<FuncInfo*> funcGraph;
	std::vector<DvmhRegion> regions;

	DvmhRegion* getContainingRegion(SgStatement *);
	void printFuncName(SgStatement *);
	void findEdgesForRegions(std::vector<LoopGraph *>);
	bool hasLimitsToDvmhParallel(LoopGraph *);
	void insertActualDirectives();
	void insertRegionDirectives();
	void insertActualDirectiveBefore(SgStatement *, std::vector<SgSymbol*>, int);
	void mergeRegions();
	//void insertActualForRedistribute();
	LoopCheckResults checkLoopForPurenessAndIO(LoopGraph *);
	LoopCheckResults updateLoopNode(LoopGraph *);
	void DvmhRegionInsertor::printControlFlowGraph()
	{
		int funcNum = file.numberOfFunctions();
		for (int i = 0; i < funcNum; ++i)
		{
			SgStatement *st = file.functions(i);
			auto graphsKeeper = new GraphsKeeper();

			ControlFlowGraph* CGraph = graphsKeeper->buildGraph(st)->CGraph;

			printFuncName(st);
			CBasicBlock* bb = CGraph->getFirst();
			while (bb) 
			{
				// ControlFlowItem* start = (bb->getStart()->getNext()) ? bb->getStart()->getNext() : bb->getStart();
				// ControlFlowItem* end = (bb->getEnd()->getNext()) ? bb->getEnd()->getNext() : bb->getEnd();
				ControlFlowItem* start = bb->getStart();
				ControlFlowItem* end = bb->getEnd();
				BasicBlockItem* prev = bb->getPrev();
				vector<int> prev_ids;
				while (prev) {
					prev_ids.push_back(prev->block->getNum());
					prev = prev->next;
				}
				string s_prev_ids = "";
				for (auto id : prev_ids)
					s_prev_ids = s_prev_ids + to_string(id) + " | ";
				printf("Basic block [%d]: start [%d], end [%d], prev blocks [%s].\n", bb->getNum(), start->GetLineNumber(), end->GetLineNumber(), s_prev_ids);
				while (start && start->getBBno() == bb->getNum()) {
					start->printDebugInfo();
					start = start->getNext();
				}
				printf("______________________\n");

				bb = bb->getLexNext();
			}
		}
		printf("Graph printed.\n");
	}

public:
	DvmhRegionInsertor(SgFile *, std::vector<LoopGraph *>, std::vector<FuncInfo *>);
	std::vector<LoopGraph *>  updateLoopGraph();
	void insertDirectives();
	virtual ~DvmhRegionInsertor();
};

enum DFGType {block, par_loop};

class DFGNode {
public:
	vector<CBasicBlock *> initial;
	vector<DFGNode*> prev;
	vector<DFGNode*> succ;
	vector<SgStatement*> content;
	vector<SgSymbol*> d_arrays;
	DFGType type;
	int id;

	DFGNode(CBasicBlock* bblock) {
		initial.push_back(bblock);
		type = block;
		id = bblock->getNum();

		// Fill containing statements
		ControlFlowItem* cfi = bblock->getStart();
		while (cfi && cfi->getBBno() == bblock->getNum()) 
		{
			if (cfi->getStatement())
				content.push_back(cfi->getStatement());

			cfi = cfi->getNext();
		}

		// Fill used distributed array (interface is nuts)
		VarSet* vars = bblock->getUse();
		VarItem* var_i = vars->getFirst();
		while (var_i) {
			SgSymbol* symbol = var_i->var->GetSymbol();
			try {
				DIST::Array* arr = getArrayFromDeclarated(declaratedInStmt(symbol), symbol->identifier());
				bool isDistr = !arr->GetNonDistributeFlag();
				if (isDistr)
					d_arrays.push_back(symbol);
			}
			catch (...) {
				cout << "Disribute array assertion having some fun." << endl;
			}

			var_i = var_i->next;
		}
	}

	operator std::string() const
    {
		string s_content = "";
		for (auto st: content)
			s_content = s_content + st->unparse() + "\n";

		string s_d_arrays = "";
		for (auto arr: d_arrays)
			s_d_arrays = string(arr->identifier()) + " , ";

        string info = "id [" 		+ to_string(id)		+ "]\n" +\
					+ "type ["		+ to_string(type)	+ "]\n" +\
					+ "content["	+ s_content			+ "]\n" +\
					+ "d_arrays["	+ s_d_arrays		+ "]\n";
		return info;
    }
};

/*	Abstract control flow graph 
	Nodes: 
		1) bblocks, referencing destibuted arrays;
		2) par_loops;
*/
class AFlowGraph {
	map<string, vector<DFGNode*> > fun_graphs;
public:
	AFlowGraph(SgFile file) 
	{
		// Build initial full CFG
		SgStatement *st = file.functions(0);
		auto graphsKeeper = new GraphsKeeper();
		graphsKeeper->buildGraph(st);

		// Build initial abstract CFG
		int funcNum = file.numberOfFunctions();
		for (int i = 0; i < funcNum; ++i)
		{
			vector<DFGNode*> fun_graph;
			string func_name = file.functions(i)->symbol()->identifier();
			ControlFlowGraph* CGraph = graphsKeeper->getGraph(func_name)->CGraph;
			if (!CGraph) 
			{
				cout << "Failed to find graph for function " << func_name << endl;
				continue;
			}

			CBasicBlock* bb = CGraph->getFirst();
			while (bb) 
			{
				fun_graph.push_back(new DFGNode(bb));
				cout << fun_graph.back(); // debug
				bb = bb->getLexNext();
			}
		}

		// Remove verticies which doesn't reference destributed arrays

		// Join nodes, composing parallel loops
	}
};



#endif /* SAPFOR_EXPERTS_SAPFOR_2017__SRC_DVMHREGIONS_DVMHREGIONINSERTOR_H_ */