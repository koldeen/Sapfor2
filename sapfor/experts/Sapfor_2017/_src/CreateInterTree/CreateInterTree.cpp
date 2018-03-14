#include "CreateInterTree.h"

SgStatement* currentSt;
std::vector<Interval*> intervals;

bool checkIfHasCall(SgExpression* exp){
	if(exp){
		if(exp->variant() == FUNC_CALL || exp->variant() == PROC_CALL)
			return true;

		return checkIfHasCall(exp->lhs()) || (checkIfHasCall(exp->rhs()));
	}

	return false;
}

void findIntervals(Interval* interval){
	bool if_has_call;
	int currentVar;

	while(currentSt != interval->ends[0]){
		currentSt = currentSt->lexNext();

		if_has_call = checkIfHasCall(currentSt->expr(0)) || checkIfHasCall(currentSt->expr(1)) || checkIfHasCall(currentSt->expr(2));
		currentVar = currentSt->variant();

		if(currentVar == RETURN_STAT)
			interval->ends.push_back(currentSt);

		if((currentVar != FOR_NODE && currentVar != PROG_HEDR && currentVar != FUNC_HEDR && currentVar != PROC_HEDR && !if_has_call)
		 || currentSt == interval->ends[0])
			continue;
		
		Interval* inter = new Interval();
		inter->begin = currentSt;
		inter->ends.push_back(currentSt->lastNodeOfStmt());
		interval->includes.push_back(inter);

		findIntervals(inter);
	}
}

void printTree(Interval* inter, int depth = 0){
	for(int i = 0; i < depth; i++) std::cout << "  ";
	std::cout << "Begin " << tag[inter->begin->variant()] << std::endl;

	for(int i = 0; i < inter->includes.size(); i++)
		printTree(inter->includes[i], depth + 1);

	for(int i = 0; i < depth; i++) std::cout << "  ";
	for(int i = 0; i < inter->ends.size(); i++)
		std::cout << "End " << i << " " << tag[inter->ends[i]->variant()] << std::endl;
}

void createInterTree(SgFile *file){
	int funcNum = file->numberOfFunctions();
    
    for (int i = 0; i < funcNum; i++){
    	Interval* func_inters = new Interval();
		func_inters->begin = file->functions(i);
		func_inters->ends.push_back(func_inters->begin->lastNodeOfStmt());

		currentSt = func_inters->begin;
		findIntervals(func_inters);

		intervals.push_back(func_inters);
    }

    for(int i = 0; i < funcNum; i++)
    	printTree(intervals[i]);
}