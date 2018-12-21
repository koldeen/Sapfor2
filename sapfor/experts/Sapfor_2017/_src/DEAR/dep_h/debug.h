#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>		

using namespace std;

#ifndef TEST_MODE
#define TEST_MODE

	#define TRUE 1
	#define FALSE 0
	
	#define TEST_SCALAR TRUE
	#define TEST_READ_ONLY TRUE

	#define TEST_INDEX TRUE
	#define TEST_INDEX_CONST TRUE
	#define TEST_INDEX_LINEAR_2 TRUE


	#define TEST_USE_PRE_INFO FALSE

#endif

#ifndef DEBUG

	#define DBG_NO 0
	#define DBG_BASE 1
	#define DBG_DEP 2
	#define DBG_TREE_CREATE 4
	#define	DBG_EXPRESSION 8
	#define DBG_TEST 16
	#define DBG_TEST_SCALAR 32
	#define DBG_TEST_ARRAY 64
	#define DBG_TEST_LINEAR_2 128

#define DEBGU DBG_NO
//#define DEBUG (DBG_BASE | DBG_DEP | DBG_TEST_ARRAY)
//#define DEBUG (DBG_BASE | DBG_TREE_CREATE | DBG_BASE_TEST)
//#define DEBUG DBG_BASE 

	#if DEBUG 
		

		#define DBG_START \
		{ \
			int x = 0; \
			cout << 1 / x << endl; \
		}
	#else
		#define DBG_START ;
	#endif

#endif





