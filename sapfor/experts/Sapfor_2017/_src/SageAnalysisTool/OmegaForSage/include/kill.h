/* kill.h,v 1.1 1993/09/17 22:14:14 fbodin Exp */

#ifndef Already_Included_kill
#define Already_Included_kill

/*
   Do quick but possibly indecisive kill tests to see 
   if  dependence dd (from from_acc to to_acc) is killed.

   If dd is obviously killed by an intervening write that
    covers its destination or terminaties its source,
    return ddisCovered or ddisTerminated.
   Otherwise, return 0 (is which case dd may or may not be killed -
    call accurate_test_for_kill to find out).

   this_dep identifies the dependence being tested, so that we will
    not try to kill a dependence with itself.  this_dep will be 
    passed to dd_i_i_cur_is and dd_o_i_cur_is.

   This function may update dd if dd is partly killed.
   In this case, dd's ddrefined bit will be set.

   Quick test for kill works for flow, output, or anti dependences
 */

dddirection
quick_test_for_kill(dir_and_dist_info *dd, char *dd_as_string,
		    a_access from_acc, a_access to_acc,
		    dd_current this_dep);

/* 
  Test to see if flow dependence dd (from from_acc to to_acc)
  can be killed.  If so, return ddisKilled.

  This should be called if quick_test_for_kill returns 0.

  Works for flow and output dependences - why not anti?
  */

dddirection
accurate_test_for_kill(dir_and_dist_info *dd, char *dd_as_string,
		       a_access from_acc, a_access to_acc,
		       dd_current this_dep);


/*
   for "READS" type problems,
   non-index vars and reads are protected

   This type of problem is used in killing, cover & termination testing,
   and in refinement
 */

typedef struct {
    range nonloops;
    range reads;      /* index variables @ time of read */
    range rsteps;
    range write1s;    /* index variables @ time of write #1 */
    range w1steps;
    range write2s;    /* index variables @ time of write #2 */
    range w2steps;
    var_id vars[maxVars];
} read_prob_desc;

/* there is no equivalent to build_delta_prob_desc, as the various
   functions that build read_prob_desc's do so in different ways.  */

typedef enum { sc_and_r, sc_r_and_w1 } protect_in_read;
void read_init(read_prob_desc *rpd, Problem *p,
	       protect_in_read protect_which, uint Nsc,  var_id  sc_vars[],
	       uint Nr,   var_id   r_vars[],  uint Nrs,  var_id  rs_vars[],
	       uint Nw1,  var_id  w1_vars[],  uint Nw1s, var_id w1s_vars[],
	       uint Nw2,  var_id  w2_vars[],  uint Nw2s, var_id w2s_vars[]);
void read_inv(read_prob_desc *rpd, Problem *p);
void read_cleanup(read_prob_desc *rpd);
#define read_Nvars(rpd)    (r_last(&(rpd)->w2steps))


#endif
