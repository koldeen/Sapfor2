/* affine.h,v 1.1 1993/09/17 22:14:06 fbodin Exp */

#ifndef Already_Included_Affine
#define Already_Included_Affine 1

#include "lang-interf.h"
#include "ip.h"

/* This file defines the affine_expr structure and macros & functions
   that are independent of tiny - that is, code that examines existing
   affine expressions.  Code that builds affine expressions from the
   parse tree, or part of the parse tree, is in find_affine.h, as that
   code is tiny-specific.
 */

typedef struct {
    var_id tiny_var;    /* pointer to symbol table entry */
    int   coefficient; /* co-efficient */
} affine_term;

typedef struct _affine_expr {
    int  nterms;
    affine_term terms[maxVars];         /* 1st entry var is always 0 */
    struct _affine_expr *other_branch;  /* if min or max */
} affine_expr;


#define is_affine(AE)          ( (AE) != &not_affine )
#define node_is_affine(NODE)   ( (NODE)->nodeaffine != (void *)&not_affine )

extern bool nodes_subs_are_affine(a_access A);
/* the above is needed only for one assertion - for some
   array access A, return true iff all subscripts of A are affine */

#ifdef __cplusplus 
extern "C" affine_expr not_affine;
#else
extern affine_expr not_affine;
#endif
/* affine_expr should point to not_affine if expression is not affine */

/* compare 2 affine exprs.
   return 1 if different, 0 if same
 */
int   CmpAffineExprs(affine_expr *, affine_expr *);

/* return a copy allocated with malloc */
affine_expr *CopyAffineExpr(affine_expr *);
void      FreeAffineExpr(affine_expr *);


#endif
