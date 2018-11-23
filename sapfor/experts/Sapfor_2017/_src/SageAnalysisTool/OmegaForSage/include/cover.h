/* cover.h,v 1.1 1993/09/17 22:14:07 fbodin Exp */

#ifndef Already_Included_cover
#define Already_Included_cover

/* 
   test to see if a dependence covers to_acc
   can be used for flow or output dependences
 */
int test_for_coverage(a_access from_acc, a_access to_acc,
		      uint from_nest, uint to_nest, uint common_nest,
		      dir_and_dist_info *dd, char *dd_as_string);

/*
   test to see if a dependence terminates from_acc
   can be used for output or anti dependences
 */
int test_for_termination(a_access from_acc, a_access to_acc,
			 uint from_nest, uint to_nest, uint common_nest,
			 dir_and_dist_info *dd, char *dd_as_string);
			 

typedef enum { really_not_there = 0,
		   really_there = 1,
		   didnt_test,
		   non_affine_red_bound,
		   non_affine_red_sub } possible_reasons;
extern possible_reasons why_no_cover_or_terminator;

#define set_reason(X)         (why_no_cover_or_terminator = (X))
#define because(X)            (why_no_cover_or_terminator == (X))
/* use: if (!cover(...))
	    if(because(non_affine_red)) ...
 */

#endif
