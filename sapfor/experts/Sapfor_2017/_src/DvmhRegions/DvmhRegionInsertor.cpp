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
	int funcNum = file.numberOfFunctions();

	for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file.functions(i);
		SgStatement *lastNode = st->lastNodeOfStmt();
		while (st != lastNode)
        {
            if (st == NULL || st->variant() == CONTAINS_STMT)
                continue;

            DvmhRegion* region1 = getContainingRegion(st);
            if (region1)
                cout << "[Region] ";
            else
                cout << "[Sequent] ";
                
            st->unparsestdout();
            
            /*
            std::set<SgSymbol *> symbols = getUsedSymbols(st);
            // debug 
            if (symbols.size() > 0) {
                insertActualDirectiveBefore(st, *symbols.begin());
                break;
            }

            DvmhRegion* region = getContainingRegion(st);
            for (auto& symbol : symbols) {
                set<SgStatement*> defenitions = getDefenitions(st, symbol);

                if (region) {
                    // Searching for defenition not in region
                    bool symbolDeclaredInSequentPart = false;
                    for (auto& defenition : defenitions) {
                        DvmhRegion* containingRegion = getContainingRegion(defenition);
                        if (!containingRegion) {
                            symbolDeclaredInSequentPart = true;
                            break;
                        }
                    }

                    if (symbolDeclaredInSequentPart) {}
                        region->needActualisation.push_back(*symbol);
                } else {
                    // Seatching for defenition in region
                    bool symbolDeclaredInRegion = false;
                    for (auto& defenition : defenitions) {
                        DvmhRegion* containingRegion = getContainingRegion(defenition);
                        if (containingRegion) {
                            symbolDeclaredInRegion = true;
                            break;
                        }
                    }

                    if (symbolDeclaredInRegion)
                        insertActualDirectiveBefore(st, symbol);
                }
            }
            */
			st = st->lexNext();
		}
	}
}

void DvmhRegionInsertor::insertDirectives()
{
    findEdgesForRegions(loopGraph);
    insertRegionDirectives();
	insertActualDirectives();
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

// TODO: implement me
set<SgStatement*> DvmhRegionInsertor::getDefenitions(SgStatement *st, SgSymbol *symbol) {
    set<SgStatement*> result;
    return result;
}

void DvmhRegionInsertor::insertActualDirectiveBefore(SgStatement *st, SgSymbol *symbol) {
    SgStatement *getActualSt = new SgStatement(ACC_GET_ACTUAL_DIR);
	st->insertStmtBefore(*getActualSt);
}