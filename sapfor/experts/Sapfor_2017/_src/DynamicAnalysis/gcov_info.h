#include <stdio.h>
#include <string>
#include <map>

#include "../Utils/utils.h"

//using namespace std;

enum key_word{
	UNKNOWN,
	BRANCH,
	CALL,
};

struct Perform{ //make 'class' - need friend for Gcov_info
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

class Gcov_info{
	int numLine;
	int executedCount;
	int countCalls;
	std::map<int,Perform> calls;
	int countBranches;
    std::map<int,Perform> branches;
public:
	Gcov_info(); 
	Gcov_info(int a, int b);
//	~Gcov_info();
	void set(int a, int b, int c, int d);
	int getNumLine();
	int getExecutedCount();
	void setNumLine(int a);
	void setExecutedCount(int a);
	int getCountCalls();
	int getCountBranches();
	std::map<int,Perform> getCalls();
	std::map<int,Perform> getBranches();
	void setCall(Perform a);
	void setBranch(Perform a);
	void gcov_print();
	friend std::ostream &operator<<(std::ostream &out, const Gcov_info &a);
};