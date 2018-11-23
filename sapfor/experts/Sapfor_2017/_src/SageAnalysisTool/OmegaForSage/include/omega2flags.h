/* omega2flags.h,v 1.1 1993/09/17 22:14:18 fbodin Exp */

/* compile time and run time flags that control the behavior of the
   code that eliminates dead dependences */


#ifndef Already_Included_Omega2flags
#define Already_Included_Omega2flags


#if defined SKIP_OMEGA2
#define skipping_omega2 1
#else
extern int skipping_omega2;
#endif

#if defined SKIP_ZAPPABLE
#define skipping_zappable 1
#else
#define skipping_zappable 0
#endif


#if defined ONLY_CHANGE_FLOW_LEVEL
#define skipping_plus_refinement 1
#define skipping_o_a_tightening  1
#else
#define skipping_plus_refinement 0
#define skipping_o_a_tightening  0
#endif

#if ! defined skipping_all_tightening
#define skipping_all_tightening  0
#endif

#if ! defined skipping_bailout
#define skipping_bailout	 0
#endif

#if defined EXTRAVAGANT
#define doing_all_accurate_kills 1
/* do refinement of all kinds of dds: "skipping_plus_refinement" still works */
#define doing_all_refines	 1
#else
#define doing_all_accurate_kills 0
/* do refinement of all kinds of dds: "skipping_plus_refinement" still works */
#define doing_all_refines	 0
#endif

#endif
