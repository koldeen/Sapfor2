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

// TODO: init first and last statements
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
	return loop->hasGoto || loop->hasPrints || loop->hasImpureCalls;
}

void DvmhRegionInsertor::insertRegionDirectives()
{
	for(auto &region: regions)
	{
		if (region.loops.size() < 1) {
			printf("Warning, empty region.\n");
			continue;
		}
		SgStatement *regionStartSt = new SgStatement(ACC_REGION_DIR);

		SgStatement *statementBefore = region.getFirstSt()->lexPrev();
		if (!statementBefore || statementBefore->variant() != DVM_PARALLEL_ON_DIR) {
			// TODO: report an error: region's illegal
			continue;
		}
		statementBefore->insertStmtBefore(*regionStartSt);

		SgStatement *regionEndSt = new SgStatement(ACC_END_REGION_DIR);
		SgStatement *lastStOfTheLoop = region.getLastSt();
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
        б) если объявляются переменные -- перенести наверх (можно перенести, если данные не используются в пред. регионе)
        в) если вызов функции -- используются ли данные из предыдущегрегиона в этой функции*
*/

static bool SymbDefinedIn(SgSymbol* var, SgStatement* st)
{
	return st->variant() == ASSIGN_STAT && st->expr(0)->variant() == ARRAY_REF && st->expr(0)->symbol()->identifier() == var->identifier();
}

// Finds the closest variable's defenition
static std::map<SymbolKey, std::set<SgExpression*> > dummyDefenitions(SgStatement* st)
{
	std::map<SymbolKey, std::set<SgExpression*> > result;

	set<SgSymbol*> usedSymbols = getUsedSymbols(st);

	for (auto& var : usedSymbols) 
	{
		SgStatement* prev = st->lexPrev();

		std::set<SgExpression*> defs;
		while (prev)
		{
			if (SymbDefinedIn(var, prev)) {
				defs.insert(prev->expr(1));
				break;
			}

			prev = prev->lexPrev();
		}

		result[SymbolKey(var, false)] = defs;
	}

	return result;
}

void DvmhRegionInsertor::insertActualDirectives() {
	std::cout << "IN INSERT ACTUALS" << std::endl;
	int funcNum = file.numberOfFunctions();
	
	for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file.functions(i);
		SgStatement *lastNode = st->lastNodeOfStmt();
		while (st && st != lastNode)
        {
            if (isSgExecutableStatement(st) == NULL) {
                st = st->lexNext();
                continue;
            }

			if (st->variant() == CONTAINS_STMT) {
				st = st->lexNext();
				continue;
			}
			
			DvmhRegion* region = getContainingRegion(st);
            //const std::map<SymbolKey, std::set<SgExpression*> > vars = getReachingDefinitions(st);
			const std::map<SymbolKey, std::set<SgExpression*> > vars = dummyDefenitions(st);
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

				DIST::Array* arr;
				try {
					arr = getArrayFromDeclarated(declaratedInStmt(symbol), var.first.getVarName());
				}
				catch(...) {
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

						auto stEx = SgStatement::getStatmentByExpression(defenition);
						if (!stEx) { // couldn't find defenition for statement
							printf("Unable to find statement for expr:\n");
							defenition->unparsestdout();
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
						region->needActualisation.push_back(symbol); 
				} 
				else {
					// Searching for defenition in region
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

			insertActualDirectiveBefore(st, toActualise, ACC_GET_ACTUAL_DIR);

			st = st->lexNext();
		}
	}

	for (auto& region : regions) {
		if (region.loops.size() > 0)
			insertActualDirectiveBefore(region.getFirstSt()->lexPrev()->lexPrev(), region.needActualisation, ACC_ACTUAL_DIR);
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

	for (auto& region: regions)
	{
		if (isFirst) // first region in sequence to merge
		{
			regionPrev = region;
			isFirst = false;
			continue;
		}

		if (areNeighbours(regionPrev, region)) // logic of intermediate derectives here, in perspective they can be accumulated and moved
		{
			regionPrev = region;
			for (auto& loop : region.loops) 
				newRegion.loops.push_back(loop);
		}
		else 
		{
			isFirst = true;
			newRegions.push_back(newRegion);
			newRegion = DvmhRegion();
			for (auto& loop : region.loops)
				newRegion.loops.push_back(loop);
		}
	}
	newRegions.push_back(newRegion);

	regions = newRegions;
}

void DvmhRegionInsertor::insertDirectives()
{
    findEdgesForRegions(loopGraph);
	mergeRegions();
    insertRegionDirectives();
	insertActualDirectives();
}

DvmhRegionInsertor::~DvmhRegionInsertor()
{
	// TODO Auto-generated destructor stub
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion() {}

DvmhRegion::DvmhRegion(LoopGraph *loopNode) 
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