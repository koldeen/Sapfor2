/*
 * DvmhDvmhRegionIsertor.cpp
 *
 *  Created on: May 14, 2018
 *      Author: vladislav
 */

#include "DvmhRegionInsertor.h"

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

/*
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
} */

void DvmhRegionInsertor::findEdgesForRegions(std::vector<LoopGraph *> loops) // here as link
{
    for (auto &loopNode: loops)
    {
			if(!hasLimitsToDvmhParallel(loopNode))
			{
				if (loopNode->loop->lexPrev()->variant() == DVM_PARALLEL_ON_DIR) {
					DvmhRegion dvmhRegion(loopNode);
					regions.push_back(dvmhRegion);
				}
			} else if (loopNode->loop->lexPrev()->variant() != DVM_PARALLEL_ON_DIR && loopNode->children.size() > 0) 
				findEdgesForRegions(loopNode->children); 
    }
}

bool DvmhRegionInsertor::hasLimitsToDvmhParallel(LoopGraph *loop)
{
	bool hasUnpureCalls = true;

	return loop->hasGoto || loop->hasPrints || loop->hasImpureCalls;
}

void DvmhRegionInsertor::insertRegionDirectives()
{
	for(auto &region: regions)
	{
		SgStatement *regionStartSt = new SgStatement(ACC_REGION_DIR);
		region.loop->loop->insertStmtBefore(*regionStartSt);

		SgStatement *regionEndSt = new SgStatement(ACC_END_REGION_DIR);
		SgStatement *lastStOfTheLoop = region.loop->loop->lastNodeOfStmt();
		lastStOfTheLoop->insertStmtAfter(*regionEndSt);
	}
}

// checks loop node itself, doesn't check its children
LoopCheckResults DvmhRegionInsertor::checkLoopForPurenessAndIO(LoopGraph *loopNode) {
	LoopCheckResults loopCheckResults;

	for (auto &nameAndLineOfFuncCalled: loopNode->calls)
	{
		FuncInfo *calledFuncInfo = NULL;

		// TODO: search for func in whole project
		for (auto &funcNode: funcGraph)
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

	for (auto &nestedLoop: loop->children) {
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
	for (auto &loopNode: loopGraph)
	{
		updateLoopNode(loopNode);
	}

	return loopGraph;
}

/*
    TODO:
    1. Искать только распределенные массивы: getArrayFromDeclarated
    2. Брать оригинальный символ originalSymb.. 
    3. Получить место определения
*/

static set<SgSymbol *> getSymbolsFromExpression(SgExpression *exp) {
    set<SgSymbol *> result;

    if (exp)
    {
        if (exp->variant() == ARRAY_REF) // TODO: check of destributed ref through getArrayFromDeclarated
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
        if (st->variant() == ASSIGN_STAT &&  i == 0) { 
            continue;
        }

        if (st->expr(i)) {
            set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(st->expr(i));
            result.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
        }
    }
        
    return result;
}

/*
    1. Объединять идущие строго подряд регионы
    2. Должны находиться в одной области видимости
    3. Если между регионами что-то есть:
        а) нет переходов вверх-вниз
        б) если объявляются переменные -- перенести наверх
        в) если вызов функции -- используются ли данные из предыдущегрегиона в этой функции*
*/

void DvmhRegionInsertor::insertActualDirectives() {
	std::cout << "IN INSERT ACTUALS" << std::endl;
	int funcNum = file.numberOfFunctions();

	
	for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file.functions(i);
		SgStatement *lastNode = st->lastNodeOfStmt();
		while (st != lastNode && st != NULL && st->variant() != CONTAINS_STMT)
        {
            if (isSgExecutableStatement(st) == NULL) {
                st = st->lexNext();
                continue;
            }
			
			DvmhRegion* region = getContainingRegion(st);
            const std::map<SymbolKey, std::set<SgExpression*> > vars = getReachingDefinitions(st);
			set<SgSymbol*> usedSymbols = getUsedSymbols(st); 

			std::vector<SgSymbol*> toActualise;
            for (auto& var : vars) {
				bool found = false;
				for (auto& symbol : usedSymbols) {
					if (var.first.getVarName() == symbol->identifier()) {
						found = true;
						break;
					}
				}

				if (!found) // skip unused symbols
					continue;

				SgSymbol *symbol = (SgSymbol *) var.first.getSymbol();
				if (!isSgArrayType(symbol->type())) // if var's not an array, skip it
					continue;
				printf("3");
				DIST::Array* arr = getArrayFromDeclarated(declaratedInStmt(symbol), var.first.getVarName());
				if (arr->GetNonDistributeFlag()) // if array's not distributed, skip it
					continue;
				
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
				if (region) {
					// Searching for defenition not in region
					bool symbolDeclaredInSequentPart = false;
					for (auto& defenition : var.second) {
						if (!SgStatement::getStatmentByExpression(defenition)) {
							printf("Unable to find statement for expr:\n");
							defenition->unparsestdout();
						}
						/*
						DvmhRegion* containingRegion = getContainingRegion(SgStatement::getStatmentByExpression(defenition));
						if (!containingRegion) {
							symbolDeclaredInSequentPart = true;
							break;
						}
						*/
					}
					if (symbolDeclaredInSequentPart)
						region->needActualisation.push_back(*symbol); 
				} 
				else {
					// Seatching for defenition in region
					bool symbolDeclaredInRegion = false;
					for (auto& defenition : var.second) {
						DvmhRegion* containingRegion = getContainingRegion(SgStatement::getStatmentByExpression(defenition));
						if (containingRegion) {
							symbolDeclaredInRegion = true;
							break;
						}
					}
					if (symbolDeclaredInRegion)
						toActualise.push_back(symbol);
				}
            } 

			if (toActualise.size() > 0)
				insertActualDirectiveBefore(st, toActualise);

			st = st->lexNext();
		}
	}
}

void DvmhRegionInsertor::insertDirectives()
{
    findEdgesForRegions(loopGraph);
    insertRegionDirectives();
	insertActualDirectives();
}

DvmhRegionInsertor::~DvmhRegionInsertor()
{
	// TODO Auto-generated destructor stub
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion() {}

DvmhRegion::DvmhRegion(LoopGraph *loopNode) : loop(loopNode) {}

bool DvmhRegion::isInRegion(SgStatement *st) {
    int line = st->lineNumber();
    if (line >= loop->lineNum && line < loop->lineNumAfterLoop)
        return true;
    else
        return false;
}

DvmhRegion* DvmhRegionInsertor::getContainingRegion(SgStatement *st) {
    for (auto& region : regions) {
        if (region.isInRegion(st)) {
            return &region;
        }
    }
    return NULL;
}

void DvmhRegionInsertor::insertActualDirectiveBefore(SgStatement *st, std::vector<SgSymbol*> symbols) {
    SgStatement *getActualSt = new SgStatement(ACC_GET_ACTUAL_DIR);

	SgExprListExp t;
	for (auto symbol : symbols) {
		SgExpression *expr = new SgVarRefExp(symbol);
		t.append(*expr);
	}

	getActualSt->setExpression(0, *t.rhs());
	st->insertStmtBefore(*getActualSt);
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	getActualSt->unparsestdout();
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
}