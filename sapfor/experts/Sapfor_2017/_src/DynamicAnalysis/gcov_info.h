#pragma once

#include <stdio.h>
#include <string>
#include <map>

#include "../Utils/utils.h"

//make 'class' - need friend for Gcov_info
struct Perform
{
	int number;
	int percent;

	Perform();
	Perform(int a, int b);
	void set(int a, int b);
	int getNumber();
	int getPercent();
	void setNumber(int a);
	void setPercent(int a);
	void gcov_print();
	friend std::ostream &operator<<(std::ostream &out, const Perform &a);
};

class Gcov_info
{
	int numLine;
	int executedCount;
	int countCalls;
	std::map<int, Perform> calls;
	int countBranches;
    std::map<int, Perform> branches;

public:
	Gcov_info(); 
	Gcov_info(int a, int b);
	void set(int a, int b, int c, int d);
    void clear() { calls.clear(); branches.clear(); countCalls = 0; countBranches = 0; }
	int getNumLine() const;
	int getExecutedCount() const;
	void setNumLine(int a);
	void setExecutedCount(int a);
	int getCountCalls() const;
	int getCountBranches() const;
	std::map<int,Perform> getCalls() const;
	std::map<int,Perform> getBranches() const;
	void setCall(Perform a);
	void setBranch(Perform a);
	void gcov_print() const;
	friend std::ostream &operator<<(std::ostream &out, const Gcov_info &a);
};