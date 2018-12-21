/* ddomega-use.h,v 1.1 1993/09/17 22:14:09 fbodin Exp */

#ifndef Already_Included_DDOmega_Use
#define Already_Included_DDOmega_Use

/* compute DD vectors, add them to nodes */

void calculateDDVectors(Problem *problemPtr, a_access access1,a_access access2,
			ddnature oitype, ddnature iotype,
			uint nest1, uint nest2, uint bnest, uint nonloops);

#endif
