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
		//int funcNum = file.numberOfFunctions();
		//for (int i = 0; i < funcNum; ++i)
		//{
		//	SgStatement *st = file.functions(i);
		//	auto graphsKeeper = new GraphsKeeper();

		//	ControlFlowGraph* CGraph = graphsKeeper->buildGraph(st)->CGraph;

		//	printFuncName(st);
		//	CBasicBlock* bb = CGraph->getFirst();
		//	while (bb) 
		//	{
		//		// ControlFlowItem* start = (bb->getStart()->getNext()) ? bb->getStart()->getNext() : bb->getStart();
		//		// ControlFlowItem* end = (bb->getEnd()->getNext()) ? bb->getEnd()->getNext() : bb->getEnd();
		//		ControlFlowItem* start = bb->getStart();
		//		ControlFlowItem* end = bb->getEnd();
		//		BasicBlockItem* prev = bb->getPrev();
		//		vector<int> prev_ids;
		//		while (prev) {
		//			prev_ids.push_back(prev->block->getNum());
		//			prev = prev->next;
		//		}
		//		string s_prev_ids = "";
		//		for (auto id : prev_ids)
		//			s_prev_ids = s_prev_ids + to_string(id) + " | ";
		//		printf("Basic block [%d]: start [%d], end [%d], prev blocks [%s].\n", bb->getNum(), start->GetLineNumber(), end->GetLineNumber(), s_prev_ids);
		//		while (start && start->getBBno() == bb->getNum()) {
		//			start->printDebugInfo();
		//			start = start->getNext();
		//		}
		//		printf("______________________\n");

		//		bb = bb->getLexNext();
		//	}
		//}
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
			SgStatement *st = cfi->getStatement();
			if (st) {
				content.push_back(st);

				// Fill used distributed arrays
				set<SgSymbol*> symbols = getUsedSymbols(st); 
				// TODO: append used symbols in func call
				for (auto symbol: symbols) {
					try {
						DIST::Array* arr = getArrayFromDeclarated(declaratedInStmt(symbol), symbol->identifier());
						if (arr && !arr->GetNonDistributeFlag())
							d_arrays.push_back(symbol);
					}
					catch (...) {
						cout << "Disribute array assertion having some fun." << endl;
					}
				}
			}

			cfi = cfi->getNext();
		}
	}

	static set<SgSymbol *> getSymbolsFromExpression(SgExpression *exp) {
		set<SgSymbol *> result;

		if (exp)
		{
			if (exp->variant() == ARRAY_REF) 
				result.insert(exp->symbol());

			set<SgSymbol *> lhsSymbols = getSymbolsFromExpression(exp->lhs());
			set<SgSymbol *> rhsSymbols = getSymbolsFromExpression(exp->rhs());

			result.insert(lhsSymbols.begin(), lhsSymbols.end());
			result.insert(rhsSymbols.begin(), rhsSymbols.end());
		}

		return result;
	}

	static set<SgSymbol *> getUsedSymbols(SgStatement* st) {
		set<SgSymbol *> result;

		// ignore not executable statements
		if (!isSgExecutableStatement(st)) {
			return result;
		}

		for (int i = 0; i < 3; ++i) {
			if (st->expr(i)) {
				set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(st->expr(i));
				result.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
			}
		}

		return result;
	}

	string getInfo() const
    {
		string s_content = "";
		for (auto st: content)
			s_content = s_content + st->unparse() + "\n";

		string s_d_arrays = "";
		for (auto arr: d_arrays)
			s_d_arrays = s_d_arrays + string(arr->identifier()) + " , ";

		string s_prev = "";
		for (auto node: prev)
			s_prev = s_prev + to_string(node->id) + " , ";

		string s_succ = "";
		for (auto node: succ)
			s_succ = s_succ + to_string(node->id) + " , ";

        string info = "id [" 		+ to_string(id)		+ "]\n" +\
					+ "type ["		+ to_string(type)	+ "]\n" +\
					+ "content["	+ s_content			+ "]\n" +\
					+ "prev["		+ s_prev			+ "]\n" +\
					+ "succ["		+ s_succ			+ "]\n" +\
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
	DFGNode* getNode(string fun_name, int id)
	{
		auto check = fun_graphs.find(fun_name);
		if (check == fun_graphs.end())
			return NULL;
		
		vector<DFGNode*> graph = fun_graphs[fun_name];
		for (auto node: graph) 
		{
			if (node->id == id)
				return node;
		}

		return NULL;
	}
	AFlowGraph(SgFile file) 
	{
		// Build initial full CFG
		SgStatement *st = file.functions(0);
		auto graphsKeeper = new GraphsKeeper();
		graphsKeeper->buildGraph(st);

		// Build initial abstract CFG
		int funcNum = file.numberOfFunctions();
		// Convert all bblocks to nodes
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
				bb = bb->getLexNext();
			}
			fun_graphs[func_name] = fun_graph;
		}
		// Link nodes
		for (int i = 0; i < funcNum; ++i)
		{
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
				DFGNode* node = getNode(func_name, bb->getNum());
				if (!node) {
					cout << "Node not found" << endl;
					bb = bb->getLexNext();
					continue;
				}

				BasicBlockItem* succ = bb->getSucc();
				while (succ) {
					DFGNode* succ_node = getNode(func_name, succ->block->getNum());
					if (!succ_node) {
						cout << "Succ node not found" << endl;
						succ = succ->next;
						continue;
					}

					node->succ.push_back(succ_node);
					succ = succ->next;
				}
				BasicBlockItem* prev = bb->getPrev();
				while (prev) {
					DFGNode* prev_node = getNode(func_name, prev->block->getNum());
					if (!prev_node) {
						cout << "Prev node not found" << endl;
						prev = prev->next;
						continue;
					}

					node->prev.push_back(prev_node);
					prev = prev->next;
				}

				// cout << node->getInfo(); // debug
				// cout << "___________" << endl;
				bb = bb->getLexNext();
			}
		}

		// Remove verticies which doesn't reference destributed arrays
		// for (auto graph: fun_graphs) {
		// 	vector<DFGNode*> shrinked_graph;
		// 	for (auto node: graph.second) {

		// 	}
		// }
		// Join nodes, composing parallel loops
	}
};



#endif /* SAPFOR_EXPERTS_SAPFOR_2017__SRC_DVMHREGIONS_DVMHREGIONINSERTOR_H_ */