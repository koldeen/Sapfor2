/*
 * DvmhDvmhRegionIsertor.cpp
 *
 *  Created on: May 14, 2018
 *      Author: vladislav
 */

#include "DvmhRegionInserter.h"

using namespace std;

LoopCheckResults::LoopCheckResults() : usesIO(false), hasImpureCalls(false) {}

LoopCheckResults::LoopCheckResults(bool io, bool calls) :
	usesIO(io),
	hasImpureCalls(calls)
{}

void DvmhRegionInsertor::printFuncName(SgStatement* st)
{
	if (st->variant() == PROG_HEDR)
	{
		SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
		std::cout << "Program: " << progH->symbol()->identifier() << std::endl;
	}
	else if (st->variant() == PROC_HEDR)
	{
		SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
		std::cout << "Procedure: " << procH->symbol()->identifier() << std::endl;
	}
	else if (st->variant() == FUNC_HEDR)
	{
		SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
		std::cout << "Function: " << funcH->symbol()->identifier() << std::endl;
	}
}

// TODO: init first and last statements
void DvmhRegionInsertor::findEdgesForRegions(std::vector<LoopGraph *> loops) // here as link
{
	for (auto &loopNode : loops)
	{
		if (!hasLimitsToDvmhParallel(loopNode))
		{
			SgStatement* func_st = getFuncStat(loopNode->loop);
			string fun_name = func_st->symbol()->identifier();
			DvmhRegion dvmhRegion(loopNode, fun_name);
			regions.push_back(dvmhRegion);
		}
		else if (loopNode->children.size() > 0)
			findEdgesForRegions(loopNode->children);
	}
}

bool DvmhRegionInsertor::hasLimitsToDvmhParallel(LoopGraph *loop)
{
	return loop->hasGoto || loop->hasPrints || loop->hasImpureCalls || !loop->directive;
}

void DvmhRegionInsertor::insertRegionDirectives()
{
	for (auto &region : regions)
	{
		if (region.loops.size() < 1) {
			printf("Warning, empty region.\n");
			continue;
		}
		SgStatement *regionStartSt = new SgStatement(ACC_REGION_DIR);

		SgStatement *statementBefore = region.getFirstSt()->lexPrev();
		if (!statementBefore || statementBefore->variant() != DVM_PARALLEL_ON_DIR) {
			printf("Error: no parallel statement before the region.");
			continue;
		}
		regionStartSt->setComments(statementBefore->comments());
		statementBefore->setComments("");
		statementBefore->insertStmtBefore(*regionStartSt);

		SgStatement *regionEndSt = new SgStatement(ACC_END_REGION_DIR);
		SgStatement *lastStOfTheLoop = region.getLastSt();
		lastStOfTheLoop->insertStmtAfter(*regionEndSt);
	}
}

// checks loop node itself, doesn't check its children
LoopCheckResults DvmhRegionInsertor::checkLoopForPurenessAndIO(LoopGraph *loopNode) {
	LoopCheckResults loopCheckResults;

	for (auto &nameAndLineOfFuncCalled : loopNode->calls)
	{
		FuncInfo *calledFuncInfo = NULL;

		// TODO: search for func in whole project
		for (auto &funcNode : funcGraph)
		{
			if (funcNode->funcName == nameAndLineOfFuncCalled.first)
			{
				calledFuncInfo = funcNode;
				break;
			}
		}

		if (!calledFuncInfo)
			continue;

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

LoopCheckResults DvmhRegionInsertor::updateLoopNode(LoopGraph *loop) {
	LoopCheckResults loopChecks = checkLoopForPurenessAndIO(loop);
	bool hasImpureCalls = loopChecks.hasImpureCalls;
	bool usesIO = loopChecks.usesIO;

	for (auto &nestedLoop : loop->children) {
		loopChecks = updateLoopNode(nestedLoop);

		hasImpureCalls |= loopChecks.hasImpureCalls;
		usesIO |= loopChecks.usesIO;
	}

	loop->hasImpureCalls = hasImpureCalls;
	loop->hasPrints |= usesIO;

	return LoopCheckResults(loop->hasPrints, loop->hasImpureCalls);
}

// Return whether this loop 
std::vector<LoopGraph *>  DvmhRegionInsertor::updateLoopGraph()
{
	for (auto &loopNode : loopGraph)
	{
		updateLoopNode(loopNode);
	}

	return loopGraph;
}


/*
	1. ���������� ������ ������ ������ �������
	2. ������ ���������� � ����� ������� ���������
	3. ���� ����� ��������� ���-�� ����:
		�) ��� ��������� �����-����
		�) ���� ����������� ���������� -- ��������� ������ (����� ���������, ���� ������ �� ������������ � ����. �������)
		�) ���� ����� ������� -- ������������ �� ������ �� ����������������� � ���� �������*
*/

static bool SymbDefinedIn(SgSymbol* var, SgStatement* st)
{
	return st->variant() == ASSIGN_STAT && st->expr(0)->variant() == ARRAY_REF && st->expr(0)->symbol()->identifier() == var->identifier();
}

// Finds the closest variable's defenition (test only)
// static std::map<SymbolKey, std::set<SgExpression*> > dummyDefenitions(SgStatement* st)
// {
// 	std::map<SymbolKey, std::set<SgExpression*> > result;

// 	set<SgSymbol*> usedSymbols = getUsedSymbols(st);

// 	for (auto& var : usedSymbols)
// 	{
// 		SgStatement* prev = st->lexPrev();

// 		std::set<SgExpression*> defs;
// 		while (prev)
// 		{
// 			if (SymbDefinedIn(var, prev)) {
// 				defs.insert(prev->expr(1));
// 				break;
// 			}

// 			prev = prev->lexPrev();
// 		}

// 		result[SymbolKey(var, false)] = defs;
// 	}

// 	return result;
// }

void DvmhRegionInsertor::insertActualDirectives() {
	int funcNum = file.numberOfFunctions();

	for (int i = 0; i < funcNum; ++i)
	{
		SgStatement *st = file.functions(i);
		SgStatement *lastNode = st->lastNodeOfStmt();
		while (st && st != lastNode)
		{
			if (!isSgExecutableStatement(st) || st->variant() == CONTAINS_STMT || isSgControlEndStmt(st)) {
				st = st->lexNext();
				continue;
			}

			DvmhRegion* region = getContainingRegion(st);
			if (st->variant() == FOR_NODE || isDVM_stat(st))
			{
				st = st->lexNext();
				continue;
			}
			const std::map<SymbolKey, std::set<ExpressionValue*> > vars = getReachingDefinitionsExt(st); // todo: c
			//const std::map<SymbolKey, std::set<SgExpression*> > vars = dummyDefenitions(st);

			std::vector<SgSymbol*> toActualise;
			for (auto& var : vars) {
				SgSymbol *symbol = (SgSymbol *)var.first.getSymbol();
				if (!isSgArrayType(symbol->type())) // if var's not an array, skip it
					continue;

				DIST::Array* arr;
				try {
					arr = getArrayFromDeclarated(declaratedInStmt(symbol), var.first.getVarName());
				}
				catch (...) {
					continue;
				}
				if (arr->GetNonDistributeFlag()) // if array's not distributed, skip it
					continue;
				/*
				// DEBUG
				std::cout << "~~~~~~~~~~~~~~~~~~~~~" << std::endl;
				st->unparsestdout();
				std::cout << var.first.getVarName() + ": " << std::endl;
				for (auto &def : var.second) {
					if (def) {
						def->unparsestdout();
					}
				}
				std::cout << "********************" << std::endl;
				// END OF DEBUG
				*/
				if (region) {
					// Searching for defenition not in region
					bool symbolDeclaredInSequentPart = false;
					for (auto& defenition : var.second) {
						auto saveName = current_file->filename();

						auto stEx = SgStatement::getStatmentByExpression(defenition->getExp());
						if (!stEx) { // couldn't find defenition for statement
							printf("Unable to find statement for expr:\n");
							printf("%s\n", defenition->getUnparsed());
							printInternalError(saveName, st->lineNumber());
							continue;
						}

						if (!stEx->switchToFile())
							printInternalError(saveName, st->lineNumber());

						DvmhRegion* containingRegion = getContainingRegion(stEx);
						if (!containingRegion) {
							symbolDeclaredInSequentPart = true;
							break;
						}

						if (SgFile::switchToFile(saveName) == -1)
							printInternalError(saveName, st->lineNumber());
					}
					if (symbolDeclaredInSequentPart)
						region->addToActualisation(symbol);
				}
				else {
					// Searching for defenition in region
					bool symbolDeclaredInRegion = false;
					for (auto& defenition : var.second) {
						auto saveName = current_file->filename();
						auto stEx = SgStatement::getStatmentByExpression(defenition->getExp());
						if (!stEx) { // couldn't find defenition for statement
							printf("Unable to find statement for expr:\n");
							printf("%s\n", defenition->getUnparsed());
							printInternalError(saveName, st->lineNumber());
							continue;
						}
						if (!stEx->switchToFile())
							printInternalError(saveName, st->lineNumber());

						DvmhRegion* containingRegion = getContainingRegion(stEx);
						if (containingRegion) {
							symbolDeclaredInRegion = true;
							break;
						}

						if (SgFile::switchToFile(saveName) == -1)
							printInternalError(saveName, st->lineNumber());
					}
					if (symbolDeclaredInRegion)
						toActualise.push_back(symbol);
				}
			}
			insertActualDirectiveBefore(st, toActualise, ACC_GET_ACTUAL_DIR);
			st = st->lexNext();
		}
	}

	for (auto& region : regions) {
		if (region.loops.size() > 0) {
			insertActualDirectiveBefore(region.getFirstSt()->lexPrev()->lexPrev(), region.needActualisation, ACC_ACTUAL_DIR);
		}
		else
			printf("Warning, empty region.\n");
	}
}

static bool compareByStart(const DvmhRegion &a, const DvmhRegion &b)
{
	if (a.loops.size() < 1 || b.loops.size() < 1) {// TODO: report error
		return false;
		printf("Warning, empty region.\n");
	}

	return a.loops[0]->loop->lineNumber() < b.loops[0]->loop->lineNumber();
}

static bool areNeighbours(DvmhRegion& first, DvmhRegion& second)
{
	std::set<int> toSkip = { DVM_PARALLEL_ON_DIR };
	SgStatement* mediumSt = first.getLastSt()->lexNext();
	while (toSkip.count(mediumSt->variant())) // skip statements which don't prevent from merging
		mediumSt = mediumSt->lexNext();

	SgStatement* firstSt = second.getFirstSt();
	return mediumSt->fileName() == firstSt->fileName() && mediumSt->lineNumber() == firstSt->lineNumber();
}
void DvmhRegionInsertor::mergeRegions()
{
	if (regions.size() < 2)
		return;

	std::sort(regions.begin(), regions.end(), compareByStart);

	std::vector<DvmhRegion> newRegions;
	DvmhRegion newRegion;
	DvmhRegion& regionPrev = regions[0];
	bool isFirst = true;
	for (auto& loop : regions[0].loops)
		newRegion.loops.push_back(loop);

	int i = 0;
	for (auto& region : regions)
	{
		if (newRegion.fun_name == "" && region.loops.size() > 0) {
			SgStatement* func_st = getFuncStat(region.loops[0]->loop);
			string fun_name = func_st->symbol()->identifier();
			newRegion.fun_name = fun_name;
		}
		printf("Merge number %d\n", i++);
		if (isFirst) // skip first region
		{
			isFirst = false;
			continue;
		}

		if (!areNeighbours(regionPrev, region)) // logic of intermediate derectives here, in perspective they can be accumulated and moved
		{
			newRegions.push_back(newRegion);
			newRegion = DvmhRegion();
		}

		regionPrev = region;
		for (auto& loop : region.loops)
			newRegion.loops.push_back(loop);
		for (auto s : region.needActualisation)
			newRegion.addToActualisation(s);
	}
	newRegions.push_back(newRegion);

	regions = newRegions;
}

void DvmhRegionInsertor::insertDirectives()
{
	__spf_print(1, "Find edges for regions\n");
	findEdgesForRegions(loopGraph);
	__spf_print(1, "Merging regions\n");
	mergeRegions();
	__spf_print(1, "Insert regions\n");
	insertRegionDirectives();
	//__spf_print(1, "Insert actuals\n");
	//insertActualDirectives();
	// vector<DvmhRegion*> l_regions;
	// for (auto &region : regions)
	// 	l_regions.push_back(&region);

	// __spf_print(1, "Constructing Abstract Graph\n");
	// AFlowGraph graph = AFlowGraph(file, l_regions);
}

DvmhRegionInsertor::~DvmhRegionInsertor()
{
	// TODO Auto-generated destructor stub
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion() {}

DvmhRegion::DvmhRegion(LoopGraph *loopNode, string fun_name) : fun_name(fun_name)
{
	loops.push_back(loopNode);
}

bool DvmhRegion::isInRegion(SgStatement *st) {
	if (!st)
		return false;

	int line = st->lineNumber();
	bool inLoop = false;
	for (auto& loop : loops)
		inLoop |= (st->fileName() == loop->fileName && line >= loop->lineNum && line < loop->lineNumAfterLoop);
	return inLoop;
}

DvmhRegion* DvmhRegionInsertor::getContainingRegion(SgStatement *st) {
	for (auto& region : regions) {
		if (region.isInRegion(st)) {
			return &region;
		}
	}
	return NULL;
}

void DvmhRegionInsertor::insertActualDirectiveBefore(SgStatement *st, std::vector<SgSymbol*> symbols, int directive) {
	if (symbols.size() < 1 || !st)
		return;

	SgStatement *actualizingSt = new SgStatement(directive);

	SgExprListExp t;
	for (auto symbol : symbols) {
		SgExpression *expr = new SgVarRefExp(symbol);
		t.append(*expr);
	}

	actualizingSt->setExpression(0, *t.rhs());
	st->insertStmtBefore(*actualizingSt);
	/*
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	getActualSt->unparsestdout();
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	*/
}

SgStatement* DvmhRegion::getFirstSt() {
	if (loops.size() < 1) {
		printf("Warning, empty region.\n");
		return NULL;
	}

	return loops.front()->loop;
}

SgStatement* DvmhRegion::getLastSt() {
	if (loops.size() < 1) {
		printf("Warning, empty region.\n");
		return NULL;
	}

	return loops.back()->loop->lastNodeOfStmt();
}

/* AFlowGraph*/
DFGNode::DFGNode(CBasicBlock* bblock) {
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

DFGNode::DFGNode(vector<DFGNode*> elements) {
	if (elements.size() == 0)
		return;

	// Add all initial bblocks of all element-nodes to the new one
	for (auto node : elements) 
		initial.insert(initial.end(), node->initial.begin(), node->initial.end());

	// Add predecessors of first element-node to the new one
	
	vector<DFGNode*> succ;
	vector<SgStatement*> content;
	vector<SgSymbol*> d_arrays;
	DFGType type;
	int id;
	bool isRegion;
}

set<SgSymbol *> DFGNode::getSymbolsFromExpression(SgExpression *exp) 
{
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

set<SgSymbol *> DFGNode::getUsedSymbols(SgStatement* st) 
{
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

string DFGNode::getInfo() const
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

	string info = "id [" 		+ to_string(id)			+ "]\n" +\
				+ "type ["		+ to_string(type)		+ "]\n" +\
				+ "content["	+ s_content				+ "]\n" +\
				+ "prev["		+ s_prev				+ "]\n" +\
				+ "succ["		+ s_succ				+ "]\n" +\
				+ "d_arrays["	+ s_d_arrays			+ "]\n";
	return info;
}

bool DFGNode::addSucc(DFGNode* new_succ) 
{
	for (auto old_succ : succ)
		if (old_succ == new_succ || old_succ->id == new_succ->id)
			return false;
	succ.push_back(new_succ);
	return true;
}

bool DFGNode::addPrev(DFGNode* new_prev) 
{
	for (auto old_prev : prev)
		if (old_prev == new_prev || old_prev->id == new_prev->id)
			return false;
	
	prev.push_back(new_prev);
	return true;
}

DFGNode* AFlowGraph::getNode(string fun_name, int id)
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

AFlowGraph::AFlowGraph(SgFile file, vector<DvmhRegion*> regions) 
{
	// Build initial full CFG
	SgStatement *st = file.functions(0);
	GraphsKeeper* graphsKeeper = GraphsKeeper::getGraphsKeeper();
	ControlFlowGraph* CGraph = graphsKeeper->buildGraph(st)->CGraph;

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

	// Join nodes, composing regions
	for (auto region : regions)
	{
		// Accumulate all nodes composing region
		vector<DFGNode*> elements;
		for (auto loop : region->loops)
		{
			SgStatement* st = loop->loop;
			SgStatement* end = loop->loop->lastNodeOfStmt();
			while (st && st != end)
			{
				CBasicBlock* bb = graphsKeeper->findBlock(st);
				if (bb)
				{
					cout << "func_name: " << region->fun_name << endl;
					DFGNode* node = getNode(region->fun_name, bb->getNum());
					elements.push_back(node);
				} else
				{
					cout << "Failed to find bblock for statement:" << endl;
					st->unparsestdout();
				}

				st = st->lexNext();
			}
		}
		DFGNode* region_node = new DFGNode(elements);
		// TODO: Set links to the new node
		// TODO: Replace old nodes with new one
	}
	/*
	// Remove verticies which doesn't reference destributed arrays
	for (auto graph: fun_graphs) {
		vector<DFGNode*> shrinked_graph;
		for (auto node: graph.second) {
			if (node->d_arrays.size() > 0 || node->isParLoop) {
				shrinked_graph.push_back(node);
				continue;
			}
			
			// link successors with predecessors directly
			for (auto prev_node: node->prev) {
				for (auto succ_node: node->succ) {
					prev_node->addSucc(succ_node);
					succ_node->addPrev(prev_node);
				}
			}
			for (auto prev_node: node->prev) {
				// delete node itself from succ of its predecessor	
				auto node_in_succ = find(prev_node->succ.begin(), prev_node->succ.end(), node);
				if (node_in_succ == prev_node->succ.end()) {
					cout << "cannot find node in succ of its predecessor" << endl;
					continue;
				}
				prev_node->succ.erase(node_in_succ);
			}
			for (auto succ_node: node->succ) {
				// delete node itself from prev of its successor	
				auto node_in_prev = find(succ_node->prev.begin(), succ_node->prev.end(), node);
				if (node_in_prev == succ_node->prev.end()) {
					cout << "cannot find node in prev of its successor" << endl;
					continue;
				}
				succ_node->prev.erase(node_in_prev);
			}

			delete(node);
		}
		fun_graphs[graph.first] = shrinked_graph;
	}
	*/
	//Debug print
	for (auto graph: fun_graphs) {
		cout << "Graph for function: " << graph.first << endl;
		for (auto node: graph.second) {
			cout << node->getInfo(); // debug
			cout << "___________" << endl;
		}
	}
	cout << "Graph printed" << endl;
}