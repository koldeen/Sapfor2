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
#include <vector>

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
public:
	DvmhRegionInsertor(SgFile *, std::vector<LoopGraph *>, std::vector<FuncInfo *>);
	std::vector<LoopGraph *>  updateLoopGraph();
	void insertDirectives();
	virtual ~DvmhRegionInsertor();
};



#endif /* SAPFOR_EXPERTS_SAPFOR_2017__SRC_DVMHREGIONS_DVMHREGIONINSERTOR_H_ */