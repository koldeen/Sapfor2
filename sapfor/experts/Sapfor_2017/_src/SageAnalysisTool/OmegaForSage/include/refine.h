/* refine.h,v 1.1 1993/09/17 22:14:23 fbodin Exp */

#ifndef Already_Included_refine
#define Already_Included_refine

/*
    if from_acc is a write, try to refine the source
    if  to_acc  is a write, try to refine the destination
    (If both are writes, I think we could get a bit more refinement
     by having a refine_both, which tries to refine either the source
     or the destination at each loop nest.  I also think this would be
     so rare that its not worth writing the code.)

    *d_info will be updated if refinement is successful

    can be used for flow, output, or anti dependences
 */
void refine_dependence(a_access from, a_access to,
		       dir_and_dist_info *d_info);

/*
  try to refine a covers leading 0+'s into 0's.
  can be used for output or flow dependences
 */
void tighten_cover(a_access from_acc, a_access to_acc,
		   dir_and_dist_info *d_info,
		   char *dd_as_string);

/*
  try to refine a terminators leading 0+'s into 0's.
  can be used for output or anti dependences
 */
void tighten_terminator(a_access from_acc, a_access to_acc,
			dir_and_dist_info *d_info,
			char *dd_as_string);

#endif
