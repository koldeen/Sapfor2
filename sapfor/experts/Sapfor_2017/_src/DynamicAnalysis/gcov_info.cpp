#include <iostream>

#include "gcov_info.h"

Gcov_info::Gcov_info(){
	numLine=-1;
	executedCount=-1;
	countCalls=0;
	countBranches=0;
}

Gcov_info::Gcov_info(int a, int b){
	numLine=a;
	executedCount=b;
}

/*
Gcov_info::~Gcov_info(){
	if (calls) {
//////////////////////////////////
	}
	if (branches) {
//////////////////////////////////
	}
}
*/

void Gcov_info::set(int a, int b, int c, int d){
	numLine=a;
	executedCount=b;
	countCalls=c;
	countBranches=d;
}

int Gcov_info::getNumLine(){
	return numLine;
}

int Gcov_info::getExecutedCount(){
	return executedCount;
}

void Gcov_info::setNumLine(int a){
	numLine=a;
}

void Gcov_info::setExecutedCount(int a){
	executedCount=a;
}

void Gcov_info::setCall(Perform a){
	countCalls++;
	calls.insert(std::make_pair(a.getNumber(),a));
}

void Gcov_info::setBranch(Perform a){
	countBranches++;
	branches.insert(std::make_pair(a.getNumber(),a));
}

std::map<int,Perform> Gcov_info::getCalls(){
	return calls;
}

std::map<int,Perform> Gcov_info::getBranches(){
	return branches;
}

int Gcov_info::getCountCalls(){
	return countCalls;
}

int Gcov_info::getCountBranches(){
	return countBranches;
}

void Gcov_info::gcov_print(){
//    std::cout<<numLine<<" - "<<executedCount<<std::endl;
    __spf_print(1, "numLine= %d\nexecutedCount= %d\n", numLine, executedCount);
    __spf_print(1, "countCalls= %d\ncountBranches= %d\n", countCalls, countBranches);
}

std::ostream &operator<<(std::ostream &out, const Gcov_info &a){
	out<<"numLine= "<<a.numLine<<"\nexecutedCount= "<<a.executedCount<<
	"\ncountCalls= "<<a.countCalls<<"\ncountBranches= "<<a.countBranches<< std::endl;
	return out;
}

//-------------------------Perform-----------------------------------------

Perform::Perform(){
	number=-1;
	percent=-1;
}

Perform::Perform(int a, int b){
	number=a;
	percent=b;
}

void Perform::set(int a, int b){
	number=a;
	percent=b;
}

int Perform::getNumber(){
	return number;
}

int Perform::getPercent(){
	return percent;
}

void Perform::setNumber(int a){
	number=a;
}

void Perform::setPercent(int a){
	percent=a;
}

void Perform::gcov_print(){
    __spf_print(1, "number= %d\npercent= %d\n", number, percent);
//    std::cout<<number<<" - "<<percent<< std::endl;
}

std::ostream &operator<<(std::ostream &out, const Perform &a){
	out<<"number= "<<a.number<<"\npercent= "<<a.percent<< std::endl;
	return out;
}