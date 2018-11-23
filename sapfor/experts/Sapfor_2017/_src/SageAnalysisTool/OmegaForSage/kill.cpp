/* kill.c,v 1.1 1993/09/17 22:13:59 fbodin Exp */

/*
   Dependence kill tests ("quick" and "accurate")

   Naming convention: Many of these functions and structures
   refer to "read iteration" or "write iteration" as if a
   test were being performed on flow dependence(s), even when
   the test works for other forms of dependence.
 */


#include <assert.h>
#include <string.h>
#include "include/portable.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/debug.h"
#include "include/ip.h"
#include "include/lang-interf.h"
#include "include/ddomega-build.h"
#include "include/ddomega-use.h"
#include "include/kill.h"
#include "include/missing.h"
#include "include/timeTrials.h"
#include "include/Exit.h"

 /* The following table shows the possible results
     of combining two direction vectors:

         !    +    0    0+   -    +-   0-   *
     !   !    !    !    !    !    !    !    !
     +   !    +    +    +    *    *    *    *
     0   !    +    0    0+   -    +-   0-   *
     0+  !    +    0+   0+   *    *    *    *
     -   !    *    -    *    -    *    -    *
     +-  !    *    +-   *    *    *    *    *
     0-  !    *    0-   *    -    *    0-   *
     *   !    *    *    *    *    *    *    *
 */


static int ddCombine[8][8] =
{ 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 7, 7, 7, 7,
0, 1, 2, 3, 4, 5, 6, 7,
0, 1, 3, 3, 7, 7, 7, 7,
0, 7, 4, 7, 4, 7, 4, 7,
0, 7, 5, 7, 7, 7, 7, 7,
0, 7, 6, 7, 4, 7, 6, 7,
0, 7, 7, 7, 7, 7, 7, 7 };

/*
  Test to see if flow dependence f (from middle_acc to to_acc) kills
  the flow dependence dd (from from_acc to to_acc)
  via the output dependence o (from from_acc to middle_acc).
  */

static dddirection
do_test_for_kill_via(dir_and_dist_info *dd, char *dd_as_string,
    a_access from_acc, a_access middle_acc, a_access to_acc,
    dd_current f, dd_current o,
    int commonDepth)
{
    read_prob_desc rpd;  /* write1s = A[i]
                write2s = B[j]
                reads   = C[k]
                we project onto i and k, so it doesn't
                matter that either A or C or neither
                could be the read */
    Problem reads;
    dir_and_dist_info tmp_ddi;
    var_id sc_vars[maxVars], r_vars[maxVars], rs_vars[maxVars];
    var_id w1_vars[maxVars], w1s_vars[maxVars];
    var_id w2_vars[maxVars], w2s_vars[maxVars];

    int from_depth, middle_depth, to_depth;
    int Nrs, Nw1s, Nw2s, Nsc;
    int j, red_complete;

#if ! defined NDEBUG
    int eqs, geqs;
#endif

    assert(access_store_p(middle_acc) || access_update_p(middle_acc));

    from_depth = accesss_depth(from_acc);
    middle_depth = accesss_depth(middle_acc);
    to_depth = accesss_depth(to_acc);

#if defined newTimeTrials
    if (storeResult) killTests++;
#endif

#ifndef SPEED
    if (omegaPrintResult) {
        fprintf(debug2, "continuing check for KILL\n");
        fprintf(debug2, "Does %s\n", dd_current_as_string(f));
        fprintf(debug2, "Kill %s\n", dd_as_string);
        fprintf(debug2, "via  %s\n", dd_current_as_string(o));
    }
#endif

    /* Quick check to see if direction vectors are feasible */
    assert(commonDepth <= dd_current_nest(o));

    for (j = 1; j <= commonDepth; j++) {
        if (dd->distanceKnown[j] &&
            dd_current_dist_known(f, j) &&
            dd_current_dist_known(o, j))
        {
            if (dd_current_dist(f)[j] + dd_current_dist(o)[j] !=
                dd->distance[j])
                break;
        }
        else {
            int m = ddCombine[ddextract1(dd_current_dir(f), j)]
                [ddextract1(dd_current_dir(o), j)];
            int t = ddextract1(dd->direction, j);
            if ((m & t) != t) break;
        }
    }
    if (j <= commonDepth) {  /* break occured */
        if (omegaPrintResult) {
            fprintf(debug2,
                "kill not feasible because of dddir at level %d\n",
                j);
        }
        return 0;
    }

    /* PART 1: find sets of variables to be used in problem */

    Nrs = Nw1s = Nw2s = Nsc = 0;

    load_bounds_and_count_steps(to_acc, r_vars, rs_vars, &Nrs);
    load_bounds_and_count_steps(from_acc, w1_vars, w1s_vars, &Nw1s);
    load_bounds_and_count_steps(middle_acc, w2_vars, w2s_vars, &Nw2s);
    load_constants_for_bounds(to_acc, sc_vars, &Nsc);
    load_constants_for_bounds(from_acc, sc_vars, &Nsc);
    load_constants_for_bounds(middle_acc, sc_vars, &Nsc);
    load_constants_for_subscripts(to_acc, sc_vars, &Nsc);
    load_constants_for_subscripts(from_acc, sc_vars, &Nsc);
    load_constants_for_subscripts(middle_acc, sc_vars, &Nsc);

    /* PART 2: assign columns to variables
       Protect variables representing symbolic constants,
       read iteration  and 1st write values of loop indices,
       because we wish to test if S implies T
       for all values of them. */

    read_init(&rpd, &reads, sc_r_and_w1, Nsc, sc_vars,
        to_depth, r_vars, Nrs, rs_vars,
        from_depth, w1_vars, Nw1s, w1s_vars,
        middle_depth, w2_vars, Nw2s, w2s_vars);

    /* PART 3: build problem */

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
    assert(reads._numEQs == 0);
    assert(reads._numGEQs == 0);
    eqs = geqs = 0;
#endif

    /* TRY TO SET UP RED "T" PROBLEM:
       "j in [B] ^ A(i) << B(j) << C(k) ^ A(i) sub= B(j) sub= C(k)"
       If C is not exit, we can omit A(i) sub= B(j), as it is
       redundant with B(j) sub= C(k) and A(i) sub= C(k)
       IF WE CAN'T ESTABLISH COMPLETE RED BOUNDS, DON'T KILL */

       /*     j in [B] */
    red_complete =
        bound_indices_and_conditionals(&reads, &rpd.write2s,
            &rpd.w2steps, &rpd.nonloops,
            red, middle_acc);

    if (to_acc != ExitNode) {

        /*     B(j) sub= C(k) */
        /*     equate_subs can't return 0 */
        red_complete = red_complete &&
            equate_subscripts(&reads, &rpd.reads, &rpd.write2s,
                &rpd.nonloops,
                red, to_acc, middle_acc) == complete;
    }
    else {

        /*     B(j) sub= A(i) */
        /*     equate_subs can't return 0 */
        red_complete = red_complete &&
            equate_subscripts(&reads, &rpd.write1s, &rpd.write2s,
                &rpd.nonloops,
                red, from_acc, middle_acc) == complete;
    }

    if (!red_complete)
    {
        if (omegaPrintResult) {
            fprintf(debug2, "not checking KILL - incomplete red bounds \n");
        }
        read_cleanup(&rpd);
        return 0;
    }

    /*     B(j) << C(k) */
    ddnode_to_dir_and_dist(f, &tmp_ddi);
    constrain_with_dd(&reads, &rpd.reads, &rpd.write2s, &tmp_ddi, red);

    /*     A(i) << B(j) */
    ddnode_to_dir_and_dist(o, &tmp_ddi);
    constrain_with_dd(&reads, &rpd.write2s, &rpd.write1s, &tmp_ddi, red);


#if ! defined NDEBUG
    read_inv(&rpd, &reads);
    for ( /* eqs as it is */; eqs < reads._numEQs; eqs++)
    {
        assert(reads._EQs[eqs].color == red);
    }
    for ( /* geqs as it is */; geqs < reads._numGEQs; geqs++)
    {
        assert(reads._GEQs[geqs].color == red);
    }
#endif

    /* SET UP BLACK "S" PROBLEM:
       "i in [A] ^ k in [C] ^ A(i) << C(k) ^ A(i) sub= C(k)" */

       /* i in [A] */
    bound_indices_and_conditionals(&reads, &rpd.write1s, &rpd.w1steps,
        &rpd.nonloops, black, from_acc);

    /* k in [C] */
    bound_indices_and_conditionals(&reads, &rpd.reads, &rpd.rsteps,
        &rpd.nonloops, black, to_acc);

    /*     A(i) sub= C(k) */
    /*     this must be possible, or there would not be a dependence */

    equate_subscripts(&reads, &rpd.reads, &rpd.write1s, &rpd.nonloops,
        black, to_acc, from_acc);

    /*     A(i) << C(k) */
    constrain_with_dd(&reads, &rpd.reads, &rpd.write1s, dd, black);

#if ! defined NDEBUG
    for (/* eqs as it is */; eqs < reads._numEQs; eqs++) {
        assert(reads._EQs[eqs].color == black);
    }
    for (/* geqs as it is */; geqs < reads._numGEQs; geqs++) {
        assert(reads._GEQs[geqs].color == black);
    }
#endif

    /* PART 4: clean up */

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif
    read_cleanup(&rpd);

    /* PART 5: CHECK FOR KILL: Forall i,k,Sym, does S imply T? */

    if (omegaPrintResult) {
        fprintf(debug2, "checking for KILL in: \n");
        printProblem(&reads);
    }

#if defined newTimeTrials
    if (storeResult) realKillTests++;
#endif

    /* There must be a solution to the black equations,
       because they describe a flow dependence from A to C */

    if (!hasRedEquations(&reads, 0)) {
        if (omegaPrintResult) {
            fprintf(debug2, "verified KILL:\n");
            printProblem(&reads);
        }
#if defined newTimeTrials
        if (storeResult) realKills++;
#endif	
        return ddkilled;
    }
    else {
        if (omegaPrintResult) {
            fprintf(debug2, "no KILL:\n");
            printProblem(&reads);
        }
        return 0;
    }
}


/*
  Test to see if flow dependence dd2 (from write_acc2 to read_acc) kills
  the flow dependence dd1 (frow write_acc1 to read_acc).
  This should be called if quick_test_for_kill returns 0.
  */

dddirection
accurate_test_for_kill(dir_and_dist_info *dd, char *dd_as_string,
    a_access from_acc, a_access to_acc,
    dd_current this_dep)
{
    dd_in_iterator potential_killers;

#ifndef SPEED
    if (omegaPrintResult) {
        fprintf(debug2, "starting check for KILL of dependence:\n");
        fprintf(debug2, "%s\n", dd_as_string);
    }
#endif

    potential_killers = dd_i_i_for_access(to_acc);

    while (!dd_i_i_done(potential_killers))
    {
        /* search for intervening writes or different updates */
        if ((access_store_p(dd_i_i_cur_src(potential_killers)) ||
            (access_update_p(dd_i_i_cur_src(potential_killers)) &&
                !access_same_update_type_p(dd_i_i_cur_src(potential_killers),
                    to_acc) &&
                !access_same_update_type_p(dd_i_i_cur_src(potential_killers),
                    from_acc))) &&
            !dd_i_i_cur_is(potential_killers, this_dep))
        {
            dd_out_iterator o;
            int commonDepth;

            commonDepth = MIN(dd->nest, dd_current_nest(dd_i_i_current(potential_killers)));

            o = dd_o_i_for_access(from_acc);
            while (!dd_o_i_done(o))
            {
                if (dd_i_i_cur_src(potential_killers) == dd_o_i_cur_dest(o))
                {
                    /* test for kill with output dep "o" */
                    dddirection d;

                    d = do_test_for_kill_via(dd, dd_as_string,
                        from_acc, dd_o_i_cur_dest(o),
                        to_acc,
                        dd_i_i_current(potential_killers),
                        dd_o_i_current(o), commonDepth);
                    if (d)
                        return d;
                }
                dd_o_i_next(o);
            }
        }

        dd_i_i_next(potential_killers);
    }

    return 0;
}


/* The following table shows whether dd1 is strictly <  dd2,
                                            strictly <= dd2,
                         or possibly >  dd2.

   It is used in dd_is_shorter

   If      + in dd1, dd1 p> dd2
   else if 0 in dd1,     if - in dd2, dd1 p> dd2
                    else if dd2 == +, dd1 <  dd2
                    else (0 or 0+)    dd1 <= dd2
   else (dd1 == -)       if - in dd2, dd1 p> dd2
                    else              dd1 <  dd2
 */

typedef enum { pg = 0, le, lt } ddComparison;

/* compare[dd1][dd2] */
ddComparison ddCompare[8][8] =
{
    /*       DD2     +   0  0+   -  +-  0-   *   */
    /* DD1 */
    /*    */  { pg, pg, pg, pg, pg, pg, pg, pg },
    /* +  */  { pg, pg, pg, pg, pg, pg, pg, pg },
    /* 0  */  { pg, lt, le, le, pg, pg, pg, pg },
    /* 0+ */  { pg, pg, pg, pg, pg, pg, pg, pg },
    /*  - */  { pg, lt, lt, lt, pg, pg, pg, pg },
    /* +- */  { pg, pg, pg, pg, pg, pg, pg, pg },
    /* 0- */  { pg, lt, le, le, pg, pg, pg, pg },
    /*  * */  { pg, pg, pg, pg, pg, pg, pg, pg }
};


/* if possibly_shorter is strictly shorter than possibly_longer, return true
   if possibly_shorter might be scum than possibly_longer, return false
   if possibly_shorter is shorter or of equal length, return what_if_equal

   possibly_shorter is assumed to be a covering dependence to the
     same destination as possibly_longer, and thus possibly_longer
     may be "partially refined".
 */

static int
dd_is_shorter(dd_current possibly_shorter,
    dir_and_dist_info *possibly_longer,
    int what_if_equal)
{
    ddComparison c;
    int j;

    int minLength = MIN(possibly_longer->nest, dd_current_nest(possibly_shorter));

    for (j = 1; j <= minLength; j++)
    {
        if (dd_current_dist_known(possibly_shorter, j) &&
            possibly_longer->distanceKnown[j])
        {
            c = dd_current_dist(possibly_shorter)[j] < possibly_longer->distance[j] ? lt :
                (dd_current_dist(possibly_shorter)[j] == possibly_longer->distance[j] ? le : pg);
        }
        else {
            c = ddCompare[ddextract1(dd_current_dir(possibly_shorter), j)]
                [ddextract1(possibly_longer->direction, j)];
        }
        switch (c) {
        case lt:
            return 1;
        case pg:
            return 0;
            break;
        case le:
            if (!dddirtest(dd_current_dir(possibly_shorter), ddlt, j)) {
                if (dddirtest(possibly_longer->direction, ddlt, j)) {
                    if (!(possibly_longer->direction & ddrefined))
                    {
                        clone_dd_graph_node_for_refinement(possibly_longer->dd_graph_node_to_be_cloned);
                        possibly_longer->direction |= ddrefined;
                    }
                    dddirreset(possibly_longer->direction, ddlt, j);
                    d_info_do_eq(possibly_longer, j);
                };
                if (!dddirtest(dd_current_dir(possibly_shorter), ddeq, j)
                    && dddirtest(possibly_longer->direction, ddeq, j))
                {
                    if (!(possibly_longer->direction & ddrefined))
                    {
                        clone_dd_graph_node_for_refinement(possibly_longer->dd_graph_node_to_be_cloned);
                        possibly_longer->direction |= ddrefined;
                    }
                    dddirreset(possibly_longer->direction, ddeq, j);
                };
            };
            break;
        }
    }
    /* le in all directions if we get here. */
    return what_if_equal;
}

/*
   Do quick but possibly indecisive kill tests to see
   if dependence dd (from write_acc2 to read_acc) kills
   the flow dependence dd1 (frow write_acc1 to read_acc).

   If dd1 is obviously killed by dd2, this function will return
    either ddiscovered or ddisterminated.
   Otherwise, this function returns 0 (is which case dd2 may
    or may not be killed - call accurate_test_for_kill to find out).

   This function may update dd1 if dd1 is partly killed by dd2.
   In this case, dd1's ddrefined bit will be set.
 */

dddirection
quick_test_for_kill(dir_and_dist_info *dd, char *dd_as_string,
    a_access from_acc, a_access to_acc,
    dd_current this_dep)
{
    dd_in_iterator covers_dest;  /* search for a dd that covers to_acc */
    dd_out_iterator terms_src;   /* search for a dd that terminates from_acc */
    dddirection oldDirection = dd->direction;

    assert(!ddisDead(dd->direction));
#ifndef SPEED
    if (omegaPrintResult) {
        fprintf(debug2, "starting quick kill check for:\n");
        fprintf(debug2, "%s\n", dd_as_string);
    }
#endif

    covers_dest = dd_i_i_for_access(to_acc);
    while (!dd_i_i_done(covers_dest))
    {
        a_access cur_src = dd_i_i_cur_src(covers_dest);
#if ! defined NOT_TINY
        assert(covers_dest->ddsucc == to_acc);
#endif
        if (!dd_i_i_cur_is(covers_dest, this_dep) &&
            dd_i_i_cur_cover_p(covers_dest) &&
            dd_is_shorter(dd_i_i_current(covers_dest), dd,
            (accesss_shared_depth(from_acc, cur_src)
                == dd->nest) &&
                access_lexically_preceeds(from_acc, cur_src)))
        {
            if (omegaPrintResult) {
                fprintf(debug2,
                    "Yes: there is a closer cover of the destination:\n");
                fprintf(debug2, "%s\n",
                    dd_current_as_string(dd_i_i_current(covers_dest)));
            }
            return ddisCovered;
        }
        dd_i_i_next(covers_dest);
    }

    terms_src = dd_o_i_for_access(from_acc);

    while (!dd_i_i_done(terms_src))
    {
        a_access cur_dest = dd_o_i_cur_dest(terms_src);
#if ! defined NOT_TINY
        assert(terms_src->ddpred == from_acc);
#endif
        if (!dd_o_i_cur_is(terms_src, this_dep) &&
            dd_o_i_cur_terminate_p(terms_src) &&
            dd_is_shorter(dd_o_i_current(terms_src), dd,
            (accesss_shared_depth(to_acc, cur_dest)
                == dd->nest) &&
                access_lexically_preceeds(cur_dest, to_acc)))
        {
            if (omegaPrintResult) {
                fprintf(debug2,
                    "Yes: there is a closer terminator of the source:\n");
                fprintf(debug2, "%s\n",
                    dd_current_as_string(dd_i_i_current(terms_src)));
            }
            return ddisTerminated;
        }
        dd_o_i_next(terms_src);
    }

    if (omegaPrintResult) {
        if (oldDirection != dd->direction)
            fprintf(debug2, "direction vector refined but not killed\n");
        else fprintf(debug2, "quick kill check indecisive\n");
    }

    return 0;
}


/* functions for manipulating "read problem descriptions" */

/* name information for buffers in getVarName fns */
#define MaxNameLen   254
#define MaxSuffixLen 1

#if ! defined NDEBUG
static int var_id_is_step_expr(var_id n)
{
    return n == 0;
}

void read_inv(read_prob_desc *rpd, Problem *p)
{
    int v;

    assert(p->_nVars < maxVars);
    assert(p->_nVars >= read_Nvars(rpd));

    assert(r_first(&rpd->nonloops) == 1);
    assert(r_last(&rpd->nonloops) + 1 == r_first(&rpd->reads));
    assert(r_last(&rpd->reads) + 1 == r_first(&rpd->rsteps));
    assert(r_last(&rpd->rsteps) + 1 == r_first(&rpd->write1s));
    assert(r_last(&rpd->write1s) + 1 == r_first(&rpd->w1steps));
    assert(r_last(&rpd->w1steps) + 1 == r_first(&rpd->write2s));
    assert(r_last(&rpd->write2s) + 1 == r_first(&rpd->w2steps));

    for (v = 0; v < r_length(&rpd->nonloops); v++) {
        assert(rpd->vars[v + r_first(&rpd->nonloops)] != NIL);
        assert(var_id_const_p(rpd->vars[v + 1]));
        assert(var_ids_tag(rpd->vars[v + 1]) == v + 1);
    }

    for (v = 0; v < r_length(&rpd->reads); v++) {
        assert(rpd->vars[v + r_first(&rpd->reads)] != NIL);
        assert(var_id_index_p(rpd->vars[v + r_first(&rpd->reads)]));
        assert(var_ids_loop_no(rpd->vars[v + r_first(&rpd->reads)]) == v + 1);
    }
    for (v = 0; v < r_length(&rpd->rsteps); v++) {
        assert(var_id_is_step_expr(rpd->vars[v + r_first(&rpd->rsteps)]));
    }

    for (v = 0; v < r_length(&rpd->write1s); v++) {
        assert(rpd->vars[v + r_first(&rpd->write1s)] != NIL);
        assert(var_id_index_p(rpd->vars[v + r_first(&rpd->write1s)]));
        assert(var_ids_loop_no(rpd->vars[v + r_first(&rpd->write1s)]) == v + 1);
    }
    for (v = 0; v < r_length(&rpd->w1steps); v++) {
        assert(var_id_is_step_expr(rpd->vars[v + r_first(&rpd->w1steps)]));
    }

    for (v = 0; v < r_length(&rpd->write2s); v++) {
        assert(rpd->vars[v + r_first(&rpd->write2s)] != NIL);
        assert(var_id_index_p(rpd->vars[v + r_first(&rpd->write2s)]));
        assert(var_ids_loop_no(rpd->vars[v + r_first(&rpd->write2s)]) == v + 1);
    }
    for (v = 0; v < r_length(&rpd->w2steps); v++) {
        assert(var_id_is_step_expr(rpd->vars[v + r_first(&rpd->w2steps)]));
    }

    for (v = 0; v < p->_numGEQs; v++) {
        assert(p->_GEQs[v].touched);
    }
}
#endif

static char *read_getVarName(uint v, void *args)
{
    read_prob_desc *rpd = (read_prob_desc*)args;

    static char name[MaxNameLen + MaxSuffixLen + 1];

    assert(v <= read_Nvars(rpd));

    if (rpd->vars[v] &&
        (var_id_const_p(rpd->vars[v]) || var_id_index_p(rpd->vars[v]))) {
        strncpy(name, var_ids_name(rpd->vars[v]), MaxNameLen);
        name[MaxNameLen] = 0;
    }
    else {
        assert(var_id_is_step_expr(rpd->vars[v]));
        strcpy(name, "<trip>");
    }

    if (r_in(&rpd->reads, v) || r_in(&rpd->rsteps, v))
        strcat(name, "0");
    else if (r_in(&rpd->write1s, v) || r_in(&rpd->w1steps, v))
        strcat(name, "1");
    else if (r_in(&rpd->write2s, v) || r_in(&rpd->w2steps, v))
        strcat(name, "2");

    return name;
}


void read_init(read_prob_desc *rpd, Problem *p,
    protect_in_read protect_which, uint Nsc, var_id  sc_vars[],
    uint Nr, var_id   r_vars[], uint Nrs, var_id  rs_vars[],
    uint Nw1, var_id  w1_vars[], uint Nw1s, var_id w1s_vars[],
    uint Nw2, var_id  w2_vars[], uint Nw2s, var_id w2s_vars[])
{
    int v;

    rpd->nonloops._first = 1;
    rpd->nonloops._length = Nsc;
    rpd->reads._first = 1 + Nsc;
    rpd->reads._length = Nr;
    rpd->rsteps._first = 1 + Nsc + Nr;
    rpd->rsteps._length = Nrs;
    rpd->write1s._first = 1 + Nsc + Nr + Nrs;
    rpd->write1s._length = Nw1;
    rpd->w1steps._first = 1 + Nsc + Nr + Nrs + Nw1;
    rpd->w1steps._length = Nw1s;
    rpd->write2s._first = 1 + Nsc + Nr + Nrs + Nw1 + Nw1s;
    rpd->write2s._length = Nw2;
    rpd->w2steps._first = 1 + Nsc + Nr + Nrs + Nw1 + Nw1s + Nw2;
    rpd->w2steps._length = Nw2s;

    if (read_Nvars(rpd) > maxVars) {
        assert(0 && "Problem too big");
        fprintf(stderr, "Too many variables for omega test\n");
        Exit(2);
        /* Could we handle this by not doing r/k/c? */
    }

    rpd->vars[0] = 0;

    /* sc_vars[0..Nsc-1] are valid */
    for (v = 0; v < Nsc; v++) {
        assert(sc_vars[v] != NIL);
        rpd->vars[v + r_first(&rpd->nonloops)] = sc_vars[v];
        var_ids_tag(sc_vars[v]) = v + r_first(&rpd->nonloops);
    }

    /* r_vars[1..Nr] are valid */
    for (v = 0; v < r_length(&rpd->reads); v++) {
        assert(r_vars[v + 1] != NIL);
        rpd->vars[v + r_first(&rpd->reads)] = r_vars[v + 1];
    }
    for (v = 0; v < r_length(&rpd->write1s); v++) {
        assert(w1_vars[v + 1] != NIL);
        rpd->vars[v + r_first(&rpd->write1s)] = w1_vars[v + 1];
    }
    for (v = 0; v < r_length(&rpd->write2s); v++) {
        assert(w2_vars[v + 1] != NIL);
        rpd->vars[v + r_first(&rpd->write2s)] = w2_vars[v + 1];
    }

    /* rs_vars[0..Nrs] hold steps FROM INNERMOST TO OUTERMOST LOOPS */
    for (v = 0; v < Nrs; v++) {
        assert(rs_vars[Nrs - 1 - v] == NIL);
        rpd->vars[v + r_first(&rpd->rsteps)] = rs_vars[Nrs - 1 - v];
    }
    for (v = 0; v < Nw1s; v++) {
        assert(w1s_vars[Nw1s - 1 - v] == NIL);
        rpd->vars[v + r_first(&rpd->w1steps)] = w1s_vars[Nw1s - 1 - v];
    }
    for (v = 0; v < Nw2s; v++) {
        assert(w2s_vars[Nw2s - 1 - v] == NIL);
        rpd->vars[v + r_first(&rpd->w2steps)] = w2s_vars[Nw2s - 1 - v];
    }

    init_prob(p, read_Nvars(rpd),
        protect_which == sc_and_r ? Nsc + Nr + Nrs : Nsc + Nr + Nrs + Nw1 + Nw1s,
        read_getVarName, rpd);
}


/* clear the tags for symbolic constants */

void read_cleanup(read_prob_desc *rpd)
{
    int v;

    for (v = 0; v < r_length(&rpd->nonloops); v++) {
        var_ids_tag(rpd->vars[v + r_first(&rpd->nonloops)]) = UNTAGGED;
    }
}

