/* ddomega-build.c,v 1.1 1993/09/17 22:13:49 fbodin Exp */


/*
  Functions that are used in the construction of
  an omega test problem from a source program.
  */


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/portable.h"
#include "include/debug.h"
  /*
     #include "lang-interf.h"
     #include "ip.h"
  */
#include "include/affine.h"
#include "include/ddomega-build.h"
#include "include/Exit.h"


var_id *current_set_of_vars;

void init_prob(Problem *p, uint Nvars, uint Nprot,
    char *(*getVarName)(unsigned int, void *),
    void *getVarNameArgs)
{
    initializeProblem(p);

    assert(!(Nvars > maxVars));

    p->_nVars = Nvars;
    p->_safeVars = Nprot;
    p->_numEQs = 0;
    p->_numGEQs = 0;

    p->_getVarName = getVarName;
    p->_getVarNameArgs = getVarNameArgs;
}


/* allocate a new _EQs with uninitialized co-efficients */
/*   The touched flag only makes a difference on GEQ's */

uint prob_add_EQ(Problem *p, int color)
{
    ++p->_numEQs;
    assert(!(p->_numEQs > maxEQs));
    p->_EQs[p->_numEQs - 1].color = color;
    return p->_numEQs - 1;
}

/* allocate a new _EQs with all co-efficients 0 */

uint prob_add_zero_EQ(Problem *p, int color)
{
    uint c;
    c = p->_numEQs++;
    assert(!(p->_numEQs > maxEQs));
    eqnnzero(&p->_EQs[c], p->_nVars);
    p->_EQs[c].color = color;

    return c;
}


/* allocate a new _GEQs with uninitialized co-efficients */

uint prob_add_GEQ(Problem *p, int color)
{
    ++p->_numGEQs;
    assert(!(p->_numGEQs > maxGEQs));
    p->_GEQs[p->_numGEQs - 1].touched = 1;
    p->_GEQs[p->_numGEQs - 1].color = color;
    return p->_numGEQs - 1;
}

/* allocate a new _GEQs with all co-efficients 0 */

uint prob_add_zero_GEQ(Problem *p, int color)
{
    uint c;
    c = (p->_numGEQs)++;
    assert(!(p->_numGEQs > maxGEQs));
    eqnnzero(&p->_GEQs[c], p->_nVars);
    p->_GEQs[c].touched = 1;
    p->_GEQs[c].color = color;

    return c;
}

/* delta = access1 - access2, so for flow dep, delta = write - read */

void set_deltas(Problem *p, int delta_color, range *deltas, range *a1, range *a2)
{
    uint e, c;

    assert(r_length(deltas) <= r_length(a1) && r_length(deltas) <= r_length(a2));

    for (e = 0; e < r_length(deltas); e++) {
        c = prob_add_zero_EQ(p, delta_color);
        p->_EQs[c].coef[e + r_first(deltas)] = 1;
        p->_EQs[c].coef[e + r_first(a1)] = 1;
        p->_EQs[c].coef[e + r_first(a2)] = -1;
    }
}


/*
   Constrain a problem with the minimal constraints needed to
   enforce the direction vector in dd.
   Use restraint vector unless it is not convex
   It is also tempting to use the or the direction vector instead
     if it is "=", but that does not seem to speed things up (?)
     The loss of speed is less significant if we test for eqs
     in constrain_with_convex_dddir below.
*/

void constrain_with_dd(Problem *pr, range *dd_to, range *dd_from,
    dir_and_dist_info *dd, int color)
{
    int j;

    for (j = 1; j <= dd->nest; j++) {
        int thisr;
        thisr = ddextract1(dd->restraint, j);
        if (((thisr&ddgt) && (thisr&ddlt) && !(thisr&ddeq)) /* restr = "+-" */
            || (ddextract1(dd->direction, j) == ddeq))       /* direc = "0"  */
        {
            constrain_with_convex_dddir(pr, dd_to, dd_from,
                &dd->direction, j, color);
        }
        else {
            constrain_with_convex_dddir(pr, dd_to, dd_from,
                &dd->restraint, j, color);
        }
    }
}

/*
   Constrain *pr with the DIRECTION vector in dd.
*/
void constrain_with_dddirs(Problem *pr, range *dd_to, range *dd_from,
    dir_and_dist_info *dd, int color)
{
    int j;

    for (j = 1; j <= dd->nest; j++) {
        constrain_with_convex_dddir(pr, dd_to, dd_from,
            &dd->direction, j, color);
    }
}

/*
   Constrain *pr with dimension j of *dir.
   Use equations of color "color".
*/
void constrain_with_convex_dddir(Problem *pr, range *dd_to, range *dd_from,
    dddirection *dir, int j, int color)
{
    int e;

    if (ddextract1(*dir, j) == ddeq)
    {
        e = prob_add_zero_EQ(pr, color);
        pr->_EQs[e].coef[r_first(dd_to) - 1 + j] = -1;
        pr->_EQs[e].coef[r_first(dd_from) - 1 + j] = 1;
        return;
    }
    if (!dddirtest(*dir, ddlt, j))
    {
        /* no +, so dd_to - dd_from <= 0 or < 0
           ie,  dd_from - dd_to   >= 0 or > 0
           ie,  dd_from - dd_to   >= 0 or ... -1 >= 0 */
        e = prob_add_zero_GEQ(pr, color);
        pr->_GEQs[e].coef[r_first(dd_to) - 1 + j] = -1;
        pr->_GEQs[e].coef[r_first(dd_from) - 1 + j] = 1;
        pr->_GEQs[e].coef[0] = -!dddirtest(*dir, ddeq, j);
    }
    if (!dddirtest(*dir, ddgt, j))
    {
        /* no -, so dd_to - dd_from >= 0 or > 0
           ie,    dd_to - dd_from >= 0 or ... -1 >= 0 */
        e = prob_add_zero_GEQ(pr, color);
        pr->_GEQs[e].coef[r_first(dd_to) - 1 + j] = 1;
        pr->_GEQs[e].coef[r_first(dd_from) - 1 + j] = -1;
        pr->_GEQs[e].coef[0] = -!dddirtest(*dir, ddeq, j);
    }
}



/*
  For each term in ae, add sign * its co-efficient to e.
  Declarations of symbolic constants must have been tagged with
  their column number already
  Colunm numbers of indices are their depth + r_first(indices)
  */

static void add_coefficients(Eqn e, range *indices, int sign, affine_expr *ae)
{
    int v;

    assert(ae->terms[0].tiny_var == NIL);
    e->coef[0] += sign * ae->terms[0].coefficient;

    for (v = 1; v < ae->nterms; v++) {
        if (var_id_index_p(ae->terms[v].tiny_var)) { /* index */
            int loop = var_ids_loop_no(ae->terms[v].tiny_var);
            e->coef[r_first(indices) - 1 + loop] +=
                sign * ae->terms[v].coefficient;
        }
        else { /* sym. const */
            assert(var_id_const_p(ae->terms[v].tiny_var));
            e->coef[var_ids_tag(ae->terms[v].tiny_var)] +=
                sign * ae->terms[v].coefficient;
        }
    }
}



/* for the lower bound, lb <= i ===  i - lb >= 0
   for the upper bound, i <= ub === -i + ub >= 0
   define bound types so that establish_one_bound works out...
   */

typedef enum { upper = 1, lower = -1 } which_bound;


/* return 1 if boundable, 0 if not affine */

static int
establish_one_bound(Problem *p, int color,
    range *indices, which_bound b,
    affine_expr *ae, uint depth)
{
    if (!is_affine(ae))
        return 0;

    while (ae != NIL) {
        uint c;  /* new constraint */

        assert(is_affine(ae));

        c = prob_add_zero_GEQ(p, color);
        add_coefficients(&p->_GEQs[c], indices, b, ae);
        //assert(p->_GEQs[c].coef[r_first(indices) - 1 + depth] == 0);
        if (p->_GEQs[c].coef[r_first(indices) - 1 + depth] != 0)
            return 0;

        p->_GEQs[c].coef[r_first(indices) - 1 + depth] = -b;
        ae = ae->other_branch;
    }
    return 1;
}


/*
  start_expr should point to the 1st expression taken on by the loop
  return 1 if bound, 0 if not
  */

static int
handle_nonunit_increments(Problem *p, range *indices, int *which_step, int color, loop_context l, sint incr, uint depth)
{
    affine_expr *start_expr = loop_start(l);

    assert(incr >= 1);  /* can't handle any others yet */

    if (abs(incr) == 1)
        return 1;

    /* if lower bound is linear AND HAS NO "MAX"
        add the constraint:   index = lower_bound + gensym * step
        otherwise, don't add any new constraints, unless color == red */

    assert(start_expr != NIL);

    if (is_affine(start_expr) && start_expr->other_branch == NIL)
    {
        int c, v, i2;
        c = prob_add_zero_EQ(p, color);
        add_coefficients(&p->_EQs[c], indices, 1, start_expr);

        /* we now have the EQ "lower_bound = 0" */

        //assert(p->_EQs[c].coef[r_first(indices) - 1 + depth] == 0);
        if (p->_EQs[c].coef[r_first(indices) - 1 + depth] != 0)
            return 0;

        p->_EQs[c].coef[r_first(indices) - 1 + depth] = -1;

        /* we now have the EQ "lower_bound - index = 0" */

        /* we can reduce the co-efficients to their value mod(step),
           since we're adding gensym()*step */

        i2 = incr / 2;
        for (v = 1; v <= p->_nVars; v++) {
            int tmp = intMod(p->_EQs[c].coef[v], incr);
            if (tmp > i2) tmp -= incr;
            p->_EQs[c].coef[v] = tmp;
        }

        p->_EQs[c].coef[*which_step] = incr;
        (*which_step)++;

        return 1;
    }
    else {
        return 0;
    }
}

/* Create constraints in prob for the loop index whose dolimit
   is pointed to by limits.
   May add one or more(min or max) upper and lower constraints
   May add an equality constraint if the increment != 0

   return 1 if completely bound, 0 if we had any non-affine stuff
*/

static int bound_index(Problem *p, int color, loop_context limits, range *indices, range *non_i, int *which_step, uint depth)
{
    sint incr;
    bool known;

    incr = 1; known = 1;

    if (loop_has_step_p(limits)) {
        /* there is an increment expression */
        loops_step(limits, &incr, &known);
    }

    if (!(known && incr >= 1))
        ErrAssert("DO loop step must be positive");

    if (known) {
        if (incr > 0) {
            int l, u, i;
            l = establish_one_bound(p, color, indices, lower, loop_start(limits), depth);
            u = establish_one_bound(p, color, indices, upper, loop_end(limits), depth);
            i = handle_nonunit_increments(p, indices, which_step, color, limits, incr, depth);
            return l && u && i;
        }
        else if (incr < 0) {
            /* assertion checking is off */
            int l, u, i;

            fprintf(stderr, "can't handle negative step yet\n");
            Exit(2);

            l = establish_one_bound(p, color, indices, lower, loop_end(limits), depth);
            u = establish_one_bound(p, color, indices, upper, loop_start(limits), depth);
            i = handle_nonunit_increments(p, indices, which_step, color, limits, incr, depth);
            return l && u && i;
        }
        else {
            /* assertion checking is off */
            fprintf(stderr, "What do you mean by having a step of 0?  What are you, stupid?\n");
            Exit(1);
            return 0;
        }
    }
    else {
        /* assertion checking is off */
        fprintf(stderr, "can't handle unknown step\n");
        Exit(2);
        return 0;
    }
}


/* Create constraints in problem for the conditional.
   May add any number of GEQ or EQ constraints

   return 1 if completely bound, 0 if we had any non-affine stuff

   This initial version only works with the puny subset of conditionals
   described in affine.c, and is tiny-specific.
   A conservative tiny-free alternative is to just return 0.
*/

static struct {
    int lhs_sign;
    int rhs_sign;
    int constant;
} conditionals[4] = {
    { 1, -1, -1 },  /* gt */
    { 1, -1, 0  },  /* ge */
    { -1, 1, -1 },  /* lt */
    { -1, 1, 0  }   /* le */
};

#define N_ELEMENTS(ARRAY)   ( sizeof(ARRAY)/sizeof(ARRAY[0]) )
static int
puny_bound_condition(Problem *p, int color, if_context cond,
    range *indices, range *non_i)
{
    if (if_condition_ok(cond))
    {
        int c, kind;
        kind = if_compare_op(cond);

        if (kind < 0 || kind >= N_ELEMENTS(conditionals)) {
            assert(!"What the heck?  How did that get to be affine?");
            return 0;
        }

        if (if_else_branch(cond)) {
            kind = N_ELEMENTS(conditionals) - kind;
        }
        else {
#if ! defined NOT_TINY
            assert(cond->nodeop == op_then ||
                cond->nodeparent->nodeop == op_assert);
#endif
        }

        c = prob_add_zero_GEQ(p, color);
        add_coefficients(&p->_GEQs[c], indices, conditionals[kind].lhs_sign,
            if_compare_left(cond));
        add_coefficients(&p->_GEQs[c], indices, conditionals[kind].rhs_sign,
            if_compare_right(cond));
        p->_GEQs[c].coef[0] += conditionals[kind].constant;

#if ! defined NOT_TINY
        assert(!cond->nodeparent->nodeaffine->other_branch->other_branch);
#endif
        return 1;
    }
    else {
        return 0;
    }
}


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
   that are within exactly "outer" loops and contain it.

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
    range *indices, range *steps, range *non_i,
    int outer, a_access skip_outer_ifs_containing_me,
    int color, a_access a)
{
    int result;
    int which_step = r_first(steps);
    context_iterator c;

    if (a == Entry || a == ExitNode)
        return(1);

    c = cont_i_for_access(a);
    result = 1;

    while (!cont_i_done(c))
    {
        if (cont_i_cur_loop_p(c)) {
            if (cont_i_cur_depth(c) <= outer)
                return result;

#if ! defined NOT_TINY
            assert(do_op(c->nodeparent->nodeop));
#endif

            if (!bound_index(p, color, cont_i_cur_loop(c),
                indices, non_i, &which_step,
                cont_i_cur_depth(c)))
            {
                assert(which_step <= r_last(steps) + 1);
                result = 0;
            }
        }
        else {
            assert(cont_i_cur_if_p(c));
#if ! defined NOT_TINY
            assert(c->nodeparent->nodeop == op_if);
#endif
            if (!(skip_outer_ifs_containing_me
                && cont_i_cur_depth(c) <= outer
                && access_is_in_then_or_else_of(skip_outer_ifs_containing_me, c))
                && !puny_bound_condition(p, color, cont_i_cur_if(c),
                    indices, non_i))
            {
                result = 0;
            }
        }

        cont_i_next(c);
    }
    assert(which_step <= r_last(steps) + 1);

#if ! defined NOT_TINY
    for (c = Assertions; c; c = c->nodelink)
    {
        assert(c->nodeop == op_assert);
        if (!puny_bound_condition(p, color, c->nodechild, indices, non_i))
        {
            result = 0;
        }
    }
#endif

    return result;
}


/* adjust the problem to include equality of subscript expressions at
   nodes access1 and access2.  Index variables for access1 are looked
   up in range i1, and those for access2 in range i2.  The non-index
   variables are looked up in the range non_i.

   returns 0 if subscripts could not possibly be equal.
             In this case, we may not finish adding the equalities.
   returns 1 if the conditions for their equality have been completely
             described by the constraints added to p
   returns 2 if there was a non-affine expression, in which case the
             constraints added to p must be true for equality (but they
         may also be true for some non-equal cases).  If color==red,
         we FINISH trying to bound subscripts (for zapping).
   */

equate_descr equate_subscripts(Problem *p, range *i1, range *i2, range *non_i,
    int color, a_access access1, a_access access2)
{
    sub_iterator sub1, sub2;
    int is_complete = complete;

    if (access1 == Entry || access1 == ExitNode ||
        access2 == Entry || access2 == ExitNode)
        return (equate_descr)1;

    /* we assume children of the node are subscripts,
       so scalars MUST have no nodechildren
    assert(array_op(access1->nodeop) || access1->nodechild == NIL);
    */

    sub1 = sub_i_for_access(access1);
    sub2 = sub_i_for_access(access2);

    while (!sub_i_done(sub1))
    {
        assert(!sub_i_done(sub2));  /* must have same # of subscripts */
        assert(sub_i_cur_affine(sub1) != NIL && sub_i_cur_affine(sub2) != NIL);

        if (sub_i_cur_is_affine(sub1) && sub_i_cur_is_affine(sub2)) {
            uint c;  /* new constraint # */
            int i;

            assert((sub_i_cur_affine(sub1)->other_branch == NIL) &&
                (sub_i_cur_affine(sub2)->other_branch == NIL));

            c = prob_add_zero_EQ(p, color);
            add_coefficients(&p->_EQs[c], i1, 1, sub_i_cur_affine(sub1));
            add_coefficients(&p->_EQs[c], i2, -1, sub_i_cur_affine(sub2));

            for (i = p->_nVars; i > 0; i--)
                if (p->_EQs[c].coef[i] != 0)
                    break;
            if (i == 0) {   /* linearity = 0 */
                if (p->_EQs[c].coef[0] != 0)
                    return not_possible;   /* never equal */
                p->_numEQs--;   /* always equal: don't add equation */
            }
        }
        else {
            is_complete = partial;
        }
        sub_i_next(sub1);
        sub_i_next(sub2);
    }

    assert(sub_i_done(sub2));  /* must have same # of subscripts */
    return (equate_descr)is_complete;
}

/* postcondition: n < maxVars */
static void NeedNVars(int n)
{
    if (n >= maxVars) {
        fprintf(debug2, "Out of Omega variables\n");
        Exit(2);
    }
}

/* set bounds[1...depth(n)] to point to the dolimits of the loops containing n
   set *Nsteps to the # of loops that have step expressions
   set steps[0  ... *Nsteps - 1] to NIL
   */

void load_bounds_and_count_steps(a_access a, var_id bounds[],
    var_id steps[], int *Nsteps)
{
    context_iterator c;

    if (a == Entry || a == ExitNode)
        return;

    c = cont_i_for_access(a);
    while (!cont_i_done(c))
    {
        if (cont_i_cur_loop_p(c)) {
            bounds[cont_i_cur_depth(c)] = loop_var_id(cont_i_cur_loop(c));
            if (loop_has_step_p(cont_i_cur_loop(c))) {
                /* handle step */
                NeedNVars(*Nsteps);
                steps[*Nsteps] = 0;
                (*Nsteps)++;
            }
        }
        else {
            assert(cont_i_cur_if_p(c));
            /* handle if trivially - no new bounds or steps */
        }

        cont_i_next(c);
    }
}

typedef struct {
    var_id *consts;
    int    *Nconsts;
} const_stuff;

static void load_a_const(var_id v, void *args)
{
    const_stuff *cs = (const_stuff *)args;

    if (var_id_const_p(v)) {
        /* not a loop index */
        if (var_ids_tag(v) == UNTAGGED)
        {
            NeedNVars(*cs->Nconsts);
            var_ids_tag(v) = *cs->Nconsts;
            cs->consts[(*cs->Nconsts)++] = v;
        }
        else {
            assert(cs->consts[var_ids_tag(v)] == v);
        }
    }
    else {
        assert(var_id_index_p(v));
    }
}

#if 0
static void load_consts_for_expr(node *expr, var_id consts[], int *Nconsts)
{
    node *nn;

    for (nn = expr; nn != NIL; nn = nn->nodenext) {
        assert(!array_op(nn->nodeop));
        switch (nn->nodeop) {
        case op_fetch:
        case op_store:
            if (get_nodevalue_node(nn)->nodeop == op_declare) {
                /* not a loop index */
                if (get_nodevalue_sym(get_nodevalue_node(nn))->symtag
                    == UNTAGGED)
                {
                    NeedNVars(*Nconsts);
                    get_nodevalue_sym(get_nodevalue_node(nn))->symtag
                        = *Nconsts;
                    consts[(*Nconsts)++] =
                        get_nodevalue_sym(get_nodevalue_node(nn));
                }
                else {
                    assert(consts[get_nodevalue_sym(get_nodevalue_node(nn))
                        ->symtag]
                        == get_nodevalue_sym(get_nodevalue_node(nn)));
                }
            }
            else {
                assert(get_nodevalue_node(nn)->nodeop == op_dolimit);
            }
            break;
        default:
            load_consts_for_expr(nn->nodechild, consts, Nconsts);
        }
    }
}

#endif

/* ensure that all symbolic constants used in affine subscript
   expressions appear in consts[0..*Nconsts-1], and that they
   are tagged with their indices.
   If called with a scalar, do nothing
   */
void load_constants_for_subscripts(a_access a, var_id consts[], int *Nconsts)
{
    const_stuff cs;
    sub_iterator sub;

    if (a == Entry || a == ExitNode)
        return;

    cs.consts = consts;
    cs.Nconsts = Nconsts;

    sub = sub_i_for_access(a);
    while (!sub_i_done(sub)) {
        sub_i_map_over_cur_vars(sub, &load_a_const, &cs);
        sub_i_next(sub);
    }
}

/* same for affine expressions used in loop bounds of loops surrounding n */
void load_constants_for_bounds(a_access a, var_id consts[], int *Nconsts)
{
    const_stuff cs;
    context_iterator c;

    if (a == Entry || a == ExitNode)
        return;

    cs.consts = consts;
    cs.Nconsts = Nconsts;

    c = cont_i_for_access(a);
    while (!cont_i_done(c))
    {
        if (cont_i_cur_loop_p(c)) {
            loop_map_over_start_vars(cont_i_cur_loop(c), &load_a_const, &cs);
            loop_map_over_end_vars(cont_i_cur_loop(c), &load_a_const, &cs);
        }
        else {
            assert(cont_i_cur_if_p(c));
            if_map_over_vars(cont_i_cur_if(c), &load_a_const, &cs);
        }

        cont_i_next(c);
    }

#if ! defined NOT_TINY
    for (c = Assertions; c; c = c->nodelink) {
        if_map_over_vars(c->nodechild, &load_a_const, &cs);
    }
#endif
}
