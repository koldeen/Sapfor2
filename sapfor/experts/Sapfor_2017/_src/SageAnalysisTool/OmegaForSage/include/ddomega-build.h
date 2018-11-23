/* ddomega-build.h,v 1.1 1993/09/17 22:14:08 fbodin Exp */

#ifndef Already_Included_DDOmega_Build
#define Already_Included_DDOmega_Build

#include "range.h"
#include "ip.h"

/* adjust the problem to include equality of subscript expressions at
   nodes access1 and access2.  Index variables for access1 are looked
   up in range i1, and those for access2 in range i2.  The non-index
   variables are looked up in the range non_i.
   
   returns 0 if subscripts could not possibly be equal
   returns 1 if the conditions for their equality have been completely
             described by the constraints added to p
   returns 2 if there was a non-affine expression, in which case the
             constraints added to p must be true for equality (but they
	     may also be true for some non-equal cases).  If color==red,
	     we stop trying to bound subscripts immediately.
   */
typedef enum { not_possible = 0, complete = 1, partial = 2 } equate_descr;

equate_descr equate_subscripts(Problem *p, range *i1, range *i2, range *non_i,
			       int color, a_access access1, a_access access2);

/* Establish bounds for the loop indices and conditionals
   that enclose node n.
   If we come across a non-affine expression return 0.
   If we successfully bound everything       return 1.
   Note that we finish doing all the bounds we can,
   in either case, so zapping will work well.

   Assume that "outer" outer loops have been taken care of
   in some other way - i.e. that we are building the red
   part of some problem which represents a dependence with
   "outer" leading 0's, so we will take care of these
   variables by setting them equal to the black loop indices.

   If "skip_outer_ifs_containing_me" is non-nil, any ifs
   that are within exactly "outer" loops and contain it in
   either the "then" or "else" code.

   This corresponds to the situation:
     for1
       for2
         if1 then
	   if2a then
             access a
           endif
	   if2b then
             access skip_outer_ifs_containing_me
           endif
         endif
       endfor
     endfor

   in which we want to skip if1 when bounding a in the 0,0 dependence
   from a to skip_outer_ifs_containing_me.  Note that we don't have to
   distinguish between the then & else parts, as we can't have a 0,0
   if one access is is each.
 */

int
bound_inner_indices_and_conditionals(Problem *p,
				     range *indices,range *steps,range *non_i,
				     int outer, a_access skip_outer_ifs_containing_me,
				     int color, a_access a);


#define bound_indices_and_conditionals(P,IND,ST,NONI,COL,A) \
    bound_inner_indices_and_conditionals(P,IND,ST,NONI,0,NULL,COL,A)

/* in the functions below, 
   var_id points to op_declare for symbolic constants,
                    op_dolimit for index variables
		 or some sort of expression for iteration #'s
   in 1st & 2nd cases, node's value points to S.T. entry */


/* set bounds[1...depth(n)] to point to the dolimits of the loops containing n
   set *Nsteps to the # of loops that have step expressions
   set steps[0  ... *Nsteps - 1] to point to these step expressions
   also set the nodetag field of any step expressions to their index
        into the steps array.  Steps for inner loops come first in "steps".
 */
void load_bounds_and_count_steps(a_access n, var_id bounds[],
				 var_id steps[], int *Nsteps);

/* ensure that all symbolic constants used in affine subscript
   expressions appear in consts[0..*Nconsts-1], and that they
   are tagged with their indices.
   *Nconsts should be set before calling this function
 */
void load_constants_for_subscripts(a_access access,
				   var_id consts[], int *Nconsts);

/* same for affine expressions used in loop bounds of loops surrounding n
   *Nconsts should be set before calling this function
 */
void load_constants_for_bounds(a_access n, var_id consts[], int *Nconsts);



/* low-level more problem manipulation functions */

void init_prob(Problem *p, uint Nvars, uint Nprot,
	       char *(*getVarName)(unsigned int, void *),
	       void *getVarNameArgs);
uint prob_add_EQ(Problem *p, int color);
uint prob_add_zero_EQ(Problem *p, int color);
uint prob_add_GEQ(Problem *p, int color);
uint prob_add_zero_GEQ(Problem *p, int color);

/* delta = access1 - access2, so for flow dep, delta = write - read */
void set_deltas(Problem *p, int delta_color,
		range *deltas, range *a1, range *a2);


/*
   Constrain a problem with the minimal constraints needed to 
   enforce the direction vector in dd.
   Use restraint vector unless it is not convex or the direction
   vector is "=".
*/

void constrain_with_dd(Problem *pr, range *dd_to, range *dd_from,
			   dir_and_dist_info *dd, int color);

/*
   Constrain *pr with the direction vector in dd.
*/
void constrain_with_dddirs(Problem *pr, range *dd_to, range *dd_from,
			   dir_and_dist_info *dd, int color);

/*
   *dir MUST NOT BE +-
   Constrain *pr with dimension j of *dir.
   Use equations of color "color".

   It handles 0 by adding both var[j] >= 0 and var[j] <= 0,
   which is not bad, because red equalities are just converted back
   to pairs of inequalities anyway.  Perhaps it would be better to
   add special case code for black 0's.
*/
void constrain_with_convex_dddir(Problem *pr, range *dd_to, range *dd_from,
				 dddirection *dir, int j, int color);
#endif
