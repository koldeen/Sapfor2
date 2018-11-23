/* add-assert.h,v 1.1 1993/09/17 22:14:04 fbodin Exp */

#ifndef Already_Included_AddAssert
#define Already_Included_AddAssert 1

#include "portable.h"
#include "lang-interf.h"

typedef enum { impossible, possible, too_hard } elimination_possible;
elimination_possible possible_to_eliminate(dd_current dd);

#endif
