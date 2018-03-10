#include "CreateInterTree.h"

SgStatement* currentSt;
std::vector<Interval*> intervals;

void findIntervals(Interval* interval){
	while(currentSt != interval->end){
		currentSt = currentSt->lexNext();
		
		if(currentSt == interval->end)
			return;
		
		Interval* inter = new Interval();
		inter->begin = currentSt;
		inter->end = currentSt->lastNodeOfStmt();
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
	std::cout << "End " << tag[inter->end->variant()] << std::endl;
}

void createInterTree(SgFile *file){
	int funcNum = file->numberOfFunctions();
    
    for (int i = 0; i < funcNum; i++){
    	Interval* func_inters = new Interval();
		func_inters->begin = file->functions(i);
		func_inters->end = func_inters->begin->lastNodeOfStmt();

		currentSt = func_inters->begin;
		findIntervals(func_inters);

		intervals.push_back(func_inters);
    }

    for(int i = 0; i < funcNum; i++)
    	printTree(intervals[i]);
}