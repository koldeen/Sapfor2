/* lang-interf.h,v 1.2 1994/07/05 15:34:09 fbodin Exp */

#ifndef Already_Included_Lang_Interf
#define Already_Included_Lang_Interf 1


/* 
   Omega-test to programming language interface spec

   To adapt the omega test to do data dependence for some language other
   than tiny, use the files ip.[hc], ddomega.[hc], ddomega-use.[hc],
   ddomega-build.[hc], cover.[ch], kill.[ch], refine.[ch], add-assert.[ch],
   debug.[hc], and portable.h unchanged.

   Modify affine.c to create affine_expr structures for each expression
   that may be relevent to the omega test (loop bounds and array
   subscripts).  You may or may not need to modify affine.h.

   Modify ddodriver.c, or provide your own code, to call the omega test
   for all the array pairs where you need to test for dependence, and
   call the test_for_cover, test_for_termination, quick_test_for_kill
   and accurate_test_for_kill if you wish to use them.  If you are
   feeling bold, you may even want to try to get the "zap" functions
   "possible_to_eliminate" and "try_to_eliminate" (in add-assert.c) to
   work.

   The flags in omega2flags.h control some of the optional behaviors
   that can be obtained from the dependence killing & refining code.
   They affect both ddodriver.c and the files that you do not need to
   change.

   If you want to have debugging output, make sure you open the debug
   file and set omegaPrintResult to 1.

   Create a file lang-interf.h, defining numerous macros that the
   omega test needs to access the parsed program.  Your lang-interf.h
   can be based on this generic version, or the lang-interf.h that we
   wrote for tiny, depending on whether you prefer to read my cryptic
   comments here or my even more cryptic code there.  In the generic
   version, the macros are defined to produce a meaningless result of
   the right type, so that ddomega.c, ddomega-use.c, and ddomega-build.c
   can all be compiled.

   In case of trouble, please feel free to contact me at:
   davew@cs.umd.edu
   Department of Computer Science
   A. V. Williams Building
   University of Maryland
   College Park, Maryland 20742

   Remember that it is a federal crime to send explosives or certain
   other dangerous materials in the U.S. Mail.

   David Wonnacott
 */
   

#define NOT_TINY 1

/* include for the sage macro */
/* #include "macro.h"*/

struct _affine_expr; /* define later in affine.h */
struct omegaIterator ; /* define later in this file */
struct omegaLoop;   /* define later in this file */
struct omegaIf;   /* define later in this file */
struct omegaVar;   /* define later in this file */
struct omegaContIter;

/* Note:
   The omega test data dependence functions, and the macros defined
   here, often require strings giving the printed representations of
   data dependences or array accesses, etc.  These strings are used
   only for generating debugging output in trace.out.  If you don't
   care about debugging output, you can just make anything with the
   word "string" in it = "".
 */

/* define the maximum length of a data dependence vector */
#define maxCommonNest 6   /* (32 bits - 6 used in dddir.h) / 4 bits per dd */

typedef enum { ddflow, ddanti, ddoutput, ddreduce } ddnature; 


/* define the type "a_access", which identifies an array access,
   and provides access to information about the access (such as
   its depth, line number, the symbol accessed, and the type of
   access (read or write)).

   It must also be possible to extract information about the
   subscript expressions used in the access, with "sub_i_for_access",
   information about the "context" of an access (the enclosing reads
   & writes), with "cont_i_for_access", and information about the
   dependences to or from an access, as per the stuff later in this file.

   accesss_cover_depth and accesss_terminator_depth must be lvalues
   where we can store the depth at which the access is covered or
   terminated.  These should both be initialized to -1.

   accesss_shared_depth must give the number of loops contianing both
   A1 and A2.

   Two a_accesses must be equal in a self-dependence test

   If there is no existing structure that provides all this information,
   you may need to create an aggregate with pointers to the different
   structures you use.
 */

struct omegaAccess {
  
  char *str;
  struct omegaVar *symb;
  struct omegaIterator *subiter;
  struct omegaContIter *context;
  int    inIfStmt;
  int  line,cdepth,tdepth;
  int  depth;
  int idforsage;  
  int  shareddepth;
  int pri;
  int level;
  int fetch;
  int store;
  int update;
  int lexord; 
};

typedef struct omegaAccess *a_access;

#define access_as_string(A)  (A->str)  /* only used in debugging output */
#define accesss_sym(A)	     (A->symb) /* currently only used in 1 assertion */
#define accesss_lineno(A)    (A->line) /* currently only in debugging output */
#define accesss_cover_depth(A)         (A->cdepth)
#define accesss_terminator_depth(A)    (A->tdepth)
#define accesss_depth(A)               (A->depth)
#define accesss_shared_depth(A1,A2)     (A1->shareddepth)
/* this is wrong
#define accesss_shared_depth(A1,A2)    ((A1->depth > A2->depth)?(A1->depth - A2->depth):(A2->depth > A1->depth))
*/

/* does A access a private var - if so, at what level is it private? */
#define access_private_var_p(A)     (A->pri)
#define access_private_var_level(A) (A->level)

#define access_fetch_p(A)  (A->fetch)
#define access_store_p(A)  (A->store)
#define access_update_p(A) (A->update)
/* Are A1 and A2 updates of the same kind (ie both += or both *=) */
#define access_same_update_type_p(A1, A2) 0

/* can we execute A1 and then A2 without going to another iteration */
#define access_lexically_preceeds(A1, A2) (A1->lexord > A2->lexord)


/* pointers to Entry and Exit node for testing for dependence to
   points before or after the routine being analyzed.  It must
   be possible to compare these to a variable of type a_access */

#define Entry		((a_access)0)
#define ExitNode	((a_access)0)

/* define the type "sub_iterator" - an iterator over the
   subscripts of an array access.  We need to test these
   subscripts to see if they are affine expressions of the
   loop index variables and symbolic constants, and if so,
   find the associated affine_expr structure.
   We also need to have access to all the variables used in
   the expression (for the purpose of building the set of
   variables used), via the function sub_i_map_over_cur_vars,
   which calls F(V,ARGS) for each variable V in the expression.
 */
struct omegaIterator {
  
  struct omegaIterator *next;
  int isaffine;
  struct _affine_expr *affine;
  struct omegaVar *constante;
  int cstvalue;
  
} ;

typedef struct omegaIterator *sub_iterator;


#define sub_i_for_access(A)        ((A)->subiter)
#define sub_i_next(SUBI)           (SUBI = SUBI->next)
#define sub_i_done(SUBI)           (SUBI == NULL)
#define sub_i_cur_is_affine(SUBI)  (SUBI->isaffine)
#define sub_i_cur_affine(SUBI)     (SUBI->affine)
/*
#define sub_i_map_over_cur_vars(SUBI,F,ARGS) {(F)(SUBI->constante,ARGS);}
*/
#define sub_i_map_over_cur_vars(SUBI,F,ARGS)


/* define the type "sub_iterator" - an iterator over the
   enclosing contexts of an array access.  Each cont_i_next
   operation must select the next enclosing loop or if.
   We must be able to tell which we have selected, and
   get a "loop_context" or "if_context" object from it.
 */

struct omegaContIter {
  struct omegaContIter *next;
  int depth;
  int line;
  struct omegaLoop *loop;
  struct omegaIf   *ifstmt;
  int loopiter;
};

typedef struct omegaContIter *context_iterator;


/*extern context_iterator cont_i_for_access(a_access a);*/
#define cont_i_for_access(A) (A->context)

#define cont_i_next(C)        (C = C->next)
#define cont_i_done(C)        (C == NULL)
#define cont_i_cur_loop_p(C)  (C->loopiter)
#define cont_i_cur_if_p(C)    (!(C->loopiter))
#define cont_i_cur_if(C)      (C->ifstmt)
#define cont_i_cur_loop(C)    (C->loop)
#define cont_i_cur_depth(C)   (C->depth) 

/* cur_depth valid for loops - # of loops around stmts in this loop */
/* cur_depth is also needed for ifs as of release 3.0 */
/* #define access_is_in_then_or_else_of(A,C) ((A)->inIfStmt)*/
extern int access_is_in_then_or_else_of(a_access A,context_iterator C);



 /* access A is in the then or the else part of C,
    where cont_i_cur_if_p must be true of C */
#define cont_i_cur_lineno(C)  (C->line)


/* a "loop_context" provides information about a loop.
   We need to be able to find affine_exprs for the start
   and end bounds (if a bound is not affine, we should
   get a result for which "is_affine" is false).
   We also need to know if there is a step expression,
   and whether it is known at compile time, and if so,
   what it is.  These last two must be answered by the
   function "loops_step(LOOP,S,KNOWN)", which sets *KNOWN
   to true if the step is known at compile time, and sets
   *S to the step if it is known.
   We must also be able to map a function over all the
   variables used in the start and end bounds (as we did
   for the variables used in the step expressions).
 */


struct omegaLoop {  
  struct omegaVar *symb;
  struct _affine_expr *startl;
  struct _affine_expr *endl;
  int hasstep;
  int stepl;
  int knownstep;
  struct omegaVar *constantestart;
  int cstvaluestart;
  struct omegaVar *constanteend;
  int cstvaluesend;
};

typedef struct omegaLoop  *loop_context;

#define loop_var_id(LOOP)        (LOOP->symb)
#define loop_start(LOOP)         (LOOP->startl)
#define loop_end(LOOP)           (LOOP->endl)
#define loop_has_step_p(LOOP)    (LOOP->hasstep)
#define loops_step(LOOP,S,KNOWN) { *S = LOOP->stepl; *KNOWN = LOOP->knownstep; }
/*
#define loop_map_over_start_vars(LOOP,F,ARGS) {(F)(LOOP->constantestart,ARGS);}
#define loop_map_over_end_vars(LOOP,F,ARGS)   {(F)(LOOP->constanteend,ARGS);}
*/
#define loop_map_over_start_vars(LOOP,F,ARGS) 
#define loop_map_over_end_vars(LOOP,F,ARGS) 

/* an "if context" provides information about the conditions
   surrounding an array access.
   The current code can handle ifs with single >, >=, <, or <= conditions.
   Note that it is not OK to just leave this out - it will prevent the
   refinement, cover, termination, and kill tests from determining whether
   or not they have exact information.
   If, for some reason, you can not supply this information,
   make sure that the context iterator for an array access in an if
   yeilds one if_context for which if_condition_ok is false
 */



typedef enum { greater = 0, greater_eq = 1, less = 2, less_eq = 3 }
	if_compare_operators;


struct omegaIf {  
  int condOK;
  int ident;
  if_compare_operators oper;
  struct _affine_expr *left;
  struct _affine_expr *right;
  int partelse;
};

typedef struct omegaIf  *if_context;

#define if_condition_ok(IC)	(IC->condOK)
#define if_compare_op(IC)	(IC->oper)  /* one of if_compare_operators */
#define if_compare_left(IC)	(IC->left)  /* lhs of compare op */
#define if_compare_right(IC)	(IC->right)  /* rhs of compare op */
#define if_else_branch(IC)	(IC->partelse)      /* true in body of "else" clause */
#define if_map_over_vars(IC,F,ARGS)


/* define the type used to identify a variable (typically
   a pointer into the symbol table or some such).
   It must be possible to tell the difference between a loop
   index and a symbolic constant, and for a loop index, we must
   be able to find the depth of the loop.
   We must also be able to associate a integer "tag" with each
   variable - all tags must start out with the value UNTAGGED.
 */

struct omegaVar {
  int loop;
  int constp;
  int indexp;
  int tag;
  char *name;
};


typedef struct omegaVar *var_id;

#define var_id_const_p(AE_VAR)   (AE_VAR->constp)
#define var_id_index_p(AE_VAR)   (AE_VAR->indexp)
#define var_ids_loop_no(AE_VAR)  (AE_VAR->loop)
#define var_ids_tag(AE_VAR)      (AE_VAR->tag)
#define var_ids_name(AE_VAR)     (AE_VAR->name)  /* only for debug */
#define UNTAGGED -1


/* representations of Data Dependences follow -
   You probably should not change these, but simply convert from
   this format into whatever you use, and vice versa, when getting
   information from/to the omega test
 */

/* information about dd direction vectors.
   works only if unsigned long int has at least 32 bits */
#include "dddir.h"

/*
   A dir_and_dist_info structure contains information about a dependence
   This is the form in which some of the omega test functions expect
   dependence information.
*/

#include "portable.h"
typedef struct {
    uint         nest;
    dddirection  direction;
    dddirection  restraint;
    bool         distanceKnown[maxCommonNest];
    int          distance[maxCommonNest];
    void *       dd_graph_node_to_be_cloned;
	/*  dd_graph_node_to_be_cloned points to the structure 
	    that must be duplicated when we need to make a copy
	    of an existing entry in the dependence graph using
	    the function clone_dd_graph_node_for_refinement */
} dir_and_dist_info;

/* Duplicate the dd graph node, setting "isRefined" in the copy.
   This bit will hopefully get cleaner in the next release */
void clone_dd_graph_node_for_refinement(void *dd_graph_node_to_be_cloned);

#define d_info_do_eq(D_INFO, J) \
    if (ddextract1((D_INFO)->direction,(J)) == ddeq)  \
    { \
	(D_INFO)->distanceKnown[(J)] = 1; \
	(D_INFO)->distance[(J)] = 0; \
    }

#if ! defined NDEBUG
#define d_info_inv(D_INFO) \
    { \
	int i; \
	for (i=1; i<=(D_INFO)->nest; i++) { \
	    if (ddextract1((D_INFO)->direction,i) == ddeq) { \
		assert((D_INFO)->distanceKnown[i] && \
		       (D_INFO)->distance[i] == 0); \
	    } \
	} \
    }
#else
#define d_info_inv(X)
#endif



/* 
	odd_iterators are now obsolete.
	they have been replaced.
 */

/* dd_in_iterators and dd_out_iterators allow iteration thru all the
   dependences into a given access or out of a given access.

   We may need to find the source or destination node of the current
   dependence, or find out whether it is a flow or output dependence,
   and whether it covers or terminates.

   We must also be able to identify a dependence, so that we don't
   test it against itself in certain circumstances

   For either type, we must be able to select the current dependence,
   which we identify with the type dd_current.

   From this current element, we may determine the nesting level, or
   information about the dependence distances or directions or the
   restraint vector.
*/

typedef void *dd_in_iterator;  /* iterate thru dds in to an access */
typedef void *dd_out_iterator; /* iterate thru dds out from an access */

typedef void *dd_current;      /* point to the dd the iterator is on */

#define dd_current_nest(DDC)         (3)
#define dd_current_dist(DDC)         ((int *)0)  /* distance array */
#define dd_current_dist_known(DDC,j) 1 /* dd_current_dist(DDC)[j] meaningful?*/
#define dd_current_dir(DDC)          (*((dddirection *)0)) /* direction */
#define dd_current_restr(DDC)        (*((dddirection *)0)) /* restraint */
#define dd_current_as_string(DDC)    "a dependence"
#define dd_current_src(DDC)          ((a_access) 0)
#define dd_current_dest(DDC)         ((a_access) 0)


#define dd_i_i_for_access(ACC)  ((dd_in_iterator) 0)
#define dd_i_i_done(DD_I_I)     (1)
#define dd_i_i_next(DD_I_I)     

#define dd_i_i_current(DD_I_I)          ((dd_current) 0)
#define dd_i_i_cur_src(DD_I_I)          ((a_access) 0)
#define dd_i_i_cur_dest(DD_I_I)         ((a_access) 0)
#define dd_i_i_cur_flow_p(DD_I_I)       0
#define dd_i_i_cur_output_p(DD_I_I)     0
#define dd_i_i_cur_cover_p(DD_I_I)      0
#define dd_i_i_cur_is(DD_I_I, DEP)      (dd_i_i_current(DD_I_I) == (DEP))

#define dd_o_i_for_access(ACC)  ((dd_out_iterator) 0)
#define dd_o_i_done(DD_O_I)     1
#define dd_o_i_next(DD_O_I)     

#define dd_o_i_current(DD_O_I)          ((dd_current) 0)
#define dd_o_i_cur_src(DD_O_I)          ((a_access) 0)
#define dd_o_i_cur_dest(DD_O_I)         ((a_access) 0)
#define dd_o_i_cur_output_p(DD_O_I)     0
#define dd_o_i_cur_terminate_p(DD_O_I)  0
#define dd_o_i_cur_is(DD_O_I, DEP)      (dd_o_i_current(DD_O_I) == (DEP))


/* the function "store_dependence" will be called when the omega test
   has detected a data dependence.  It should convert from the
   dir_and_dist_info into whatever form is used by the rest of the system */

void store_dependence(ddnature nature, a_access from_access,
		      a_access to_access, dir_and_dist_info *d_info);


/* convert dd nodes into stuff our functions can handle */
void ddnode_to_dir_and_dist(dd_current, dir_and_dist_info *);

/* copy info from a dir_and_dist_info into an existing dd node */
void dir_and_dist_into_ddnode(const dir_and_dist_info *ddi, dd_current);


/* take inequality number GEQ, and turn it into an assertion */
#define add_GEQ_assertion(P, VARS, GEQ) ;


#endif
