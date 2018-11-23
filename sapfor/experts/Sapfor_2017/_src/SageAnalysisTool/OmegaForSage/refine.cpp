/* refine.c,v 1.1 1993/09/17 22:14:00 fbodin Exp */

/*
   Refinement tests

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
#include "include/ddomega.h"
#include "include/omega2flags.h"
#include "include/kill.h"
#include "include/cover.h"
#include "include/refine.h"
#include "include/missing.h"
#include "include/timeTrials.h"

 /*
    check to see if a data dependence can be refined at the source,
    and change d_info if so
  */

typedef enum { source, dest } which_end;

static void refine_end(a_access access_A, a_access access_B, which_end which,
    dir_and_dist_info *d_info)
{
    uint access_B_nest = accesss_depth(access_B),
        access_A_nest = accesss_depth(access_A);
    read_prob_desc rpd;  /* write1s = A[i]
                write2s = A[j] (or B[j] if which == dest)
                reads   = B[k] */
    delta_prob_desc dpd; /* original dependence: A[i] --> B[k] */
    Problem reads, new_deltas;
    bool red_complete;
    var_id sc_vars[maxVars], B_indices[maxVars], B_steps[maxVars];
    var_id A_indices[maxVars], A_steps[maxVars];
    int NBsteps, NAsteps, Nsc;
    int l, u, j;

    dd_in_iterator o;
    int anyRefinementPossible = 0;
    int refinementPossible[maxCommonNest];

#if ! defined NDEBUG
    bool possible_dependence, simplified;
#endif
#if defined newTimeTrials
    if (storeResult) refineTests++;
#endif

    assert(!(which == source) || !access_fetch_p(access_A));
    assert(!(which == dest) || !access_fetch_p(access_B));

    if (omegaPrintResult) {
        fprintf(debug2, "attempting refinement of %s of dependence\n",
            which == source ? "source" : "destination");
        fprintf(debug2, "\tfrom a store of %s at statement %d\n",
            access_as_string(access_A), accesss_lineno(access_A));
        fprintf(debug2, "\tto a read of %s at statement %d\n",
            access_as_string(access_B), accesss_lineno(access_B));
        fprintf(debug2, "\tdddir = %x, ", d_info->direction);
        fprintf(debug2, "\trestraint = %x\n", d_info->restraint);
    }

    /* First, verify that the dependence isn't constant */
    for (j = 1; j <= d_info->nest; j++)
        if (!d_info->distanceKnown[j]) break;

    /* if all constant or d_info->nest == 0, no need to refine */
    if (j > d_info->nest) {
        if (omegaPrintResult) {
            fprintf(debug2, "no non-constant distances to refine\n");
        }
        return;
    }

    /* Check which dimensions refinement is feasible in */
    for (j = 1; j <= d_info->nest; j++)
        refinementPossible[j] = 0;

    o = dd_i_i_for_access((which == source) ? access_A : access_B);

    while (!dd_i_i_done(o))
    {
        if (dd_i_i_cur_src(o) == ((which == source) ? access_A : access_B))
        {
            /* self output/reduction dependence to end we're refining */
            assert(dd_i_i_cur_dest(o) == dd_i_i_cur_src(o));
            for (j = 1; j <= d_info->nest; j++) {
                if (!d_info->distanceKnown[j] &&
                    dddirtest(dd_current_dir(dd_i_i_current(o)),
                        ddlt | ddgt, j))
                {
                    refinementPossible[j] = 1;
                    anyRefinementPossible = 1;
                }
            }
        }
        dd_i_i_next(o);
    }

    if (!anyRefinementPossible) {
        if (omegaPrintResult)
            fprintf(debug2, "Fast break out of refinement\n");
        return;
    }

    /* BUILD BLACK PROBLEM IN "new_deltas" :
       i in [A] ^ k in [B] ^ A(i) << B(k) ^ A(i) sub= B(k) */

#if ! defined NDEBUG
    possible_dependence =
#endif
        build_delta_prob_desc(&dpd, &new_deltas, access_A, access_B,
            access_A_nest, access_B_nest, d_info->nest);
    assert(possible_dependence);

    /* The A(i) << B(k) part */
    constrain_with_dd(&new_deltas, &dpd.access2s, &dpd.access1s, d_info, black);

    /* PART 1: find sets of variables to be used in problem */

    NBsteps = NAsteps = Nsc = 0;

    load_bounds_and_count_steps(access_B, B_indices, B_steps, &NBsteps);
    load_bounds_and_count_steps(access_A, A_indices, A_steps, &NAsteps);
    load_constants_for_bounds(access_B, sc_vars, &Nsc);
    load_constants_for_bounds(access_A, sc_vars, &Nsc);
    load_constants_for_subscripts(access_B, sc_vars, &Nsc);
    load_constants_for_subscripts(access_A, sc_vars, &Nsc);

    if (which == source)
    {
        /* PART 2: assign columns to variables */

        read_init(&rpd, &reads, sc_and_r, Nsc, sc_vars,
            access_B_nest, B_indices, NBsteps, B_steps,
            access_A_nest, A_indices, NAsteps, A_steps,
            access_A_nest, A_indices, NAsteps, A_steps);
#if ! defined NDEBUG
        read_inv(&rpd, &reads);
#endif

        /* PART 3: set up equations in "reads" */

        /* SET UP BLACK PROBLEM IN "reads", IDENTICAL TO THAT IN "new_deltas":
           i in [A] ^ k in [B] ^ A(i) << B(k) ^ A(i) sub= B(k) */

           /* SET UP i in [A] */
        bound_indices_and_conditionals(&reads, &rpd.write1s, &rpd.w1steps,
            &rpd.nonloops, black, access_A);

        /* SET UP k in [B] */
        bound_indices_and_conditionals(&reads, &rpd.reads, &rpd.rsteps,
            &rpd.nonloops, black, access_B);

        /* SET UP A(i) sub= B(k)  (this can not return 0) */
#if ! defined NDEBUG
        possible_dependence =
#endif
            equate_subscripts(&reads, &rpd.write1s, &rpd.reads, &rpd.nonloops,
                black, access_A, access_B);
        assert(possible_dependence);

        constrain_with_dd(&reads, &rpd.reads, &rpd.write1s, d_info, black);

        /* TRY TO SET UP RED PROBLEM IN "reads", EXCEPT REFINEMENT VECTOR PART.
           IF WE CAN'T ESTABLISH COMPLETE RED BOUNDS, DON'T REFINE
           IF which == source, RED PROBLEM = j in [A] ^ A(j) sub= B(k)
           */

        red_complete =  /* j in [A] ^ A(j) sub= B(k) */
            ((equate_subscripts(&reads, &rpd.reads, &rpd.write2s, &rpd.nonloops,
                red, access_B, access_A) == complete) &&
                (bound_inner_indices_and_conditionals(&reads, &rpd.write2s,
                    &rpd.w2steps, &rpd.nonloops,
                    leading_zeros(d_info->direction,
                        d_info->nest),
                    access_B,
                    red, access_A)));
    }
    else {
        /* PART 2: assign columns to variables */

        read_init(&rpd, &reads, sc_and_r, Nsc, sc_vars,
            access_A_nest, A_indices, NBsteps, A_steps,
            access_B_nest, B_indices, NBsteps, B_steps,
            access_B_nest, B_indices, NBsteps, B_steps);
#if ! defined NDEBUG
        read_inv(&rpd, &reads);
#endif

        /* PART 3: set up equations in "reads" */

        /* SET UP BLACK PROBLEM IN "reads", IDENTICAL TO THAT IN "new_deltas":
           i in [A] ^ k in [B] ^ A(i) << B(k) ^ A(i) sub= B(k) */

           /* SET UP i in [A] */
        bound_indices_and_conditionals(&reads, &rpd.reads, &rpd.rsteps,
            &rpd.nonloops, black, access_A);

        /* SET UP k in [B] */
        bound_indices_and_conditionals(&reads, &rpd.write2s, &rpd.w2steps,
            &rpd.nonloops, black, access_B);

        /* SET UP A(i) sub= B(k)  (this can not return 0) */
#if ! defined NDEBUG
        possible_dependence =
#endif
            equate_subscripts(&reads, &rpd.reads, &rpd.write2s, &rpd.nonloops,
                black, access_A, access_B);
        assert(possible_dependence);

        constrain_with_dd(&reads, &rpd.write2s, &rpd.reads, d_info, black);

        /* TRY TO SET UP RED PROBLEM IN "reads", EXCEPT REFINEMENT VECTOR PART.
           IF WE CAN'T ESTABLISH COMPLETE RED BOUNDS, DON'T REFINE
           IF which ==   dest, RED PROBLEM = j in [B] ^ A(i) sub= B(j)
           */

        red_complete =  /* j in [B] ^ A(i) sub= B(j) */
            ((equate_subscripts(&reads, &rpd.write1s, &rpd.write2s, &rpd.nonloops,
                red, access_B, access_A) == complete) &&
                (bound_inner_indices_and_conditionals(&reads, &rpd.write2s,
                    &rpd.w2steps, &rpd.nonloops,
                    leading_zeros(d_info->direction,
                        d_info->nest),
                    access_A,
                    red, access_B)));
    }


    if (!red_complete)
    {
        if (omegaPrintResult) {
            fprintf(debug2,
                "not checking for refinement - incomplete red bounds\n");
        }
        read_cleanup(&rpd);
        return;
    }

    /* START WITH REFINEMENT VECTOR = DEPENDENCE VECTOR,
       THEN IN REFINEMENT, WE'LL SHORTEN IT */
    if (which == source) {
        /* SET UP A(j) << B(k) */
        constrain_with_dd(&reads, &rpd.reads, &rpd.write2s, d_info, red);
    }
    else {
        /* SET UP A(i) << B(j) */
        constrain_with_dd(&reads, &rpd.write1s, &rpd.reads, d_info, red);
    }

    /* PART 4: clean up */

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif
    read_cleanup(&rpd);

    /* PART 5: TRY TO REFINE DEPENDENCE */

#if ! defined NDEBUG
    simplified =
#endif
        simplifyProblem(&new_deltas);
    assert(simplified && "new_deltas can be simplified"); /* ferd */

#if defined newTimeTrials
    if (storeResult) semiRealRefineTests++;
#endif

    /* go from outer to inner loops, trying to change + to its minimum */
    for (j = 1; j <= d_info->nest; j++) {
        uint e;

        /* if dddist is unknown, try to refine:
           see if min distance will cancel out all others */
        if (!d_info->distanceKnown[j]) {
            int fiendish;
            if (!refinementPossible[j]) break;

            fiendish = queryVariableBounds(&new_deltas,
                r_first(&dpd.deltas) - 1 + j,
                &l, &u);
            if (fiendish)
                if (ddextract1(d_info->direction, j) == (ddeq | ddlt)) {
                    l = 0;
                    u = posInfinity;
                }
                else
                {
                    int k;
                    Problem new_new_deltas;

                    problemcpy(&new_new_deltas, &new_deltas);
                    for (k = 1; k <= d_info->nest; k++) {
                        if (k != j) {
                            unprotectVariable(&new_new_deltas,
                                r_first(&dpd.deltas) - 1 + k);
                        }
                    }
#if ! defined NDEBUG
                    simplified =
#endif
                        simplifyProblem(&new_new_deltas);
                    assert(simplified && "new_new_deltas can be simplified"); /*ferd*/

                    fiendish = queryVariableBounds(&new_new_deltas,
                        r_first(&dpd.deltas) - 1 + j,
                        &l, &u);

                    if (fiendish) {
                        eliminateRedundant(&new_new_deltas, 0);
                        simplifyProblem(&new_new_deltas);
                        fiendish = queryVariableBounds(&new_new_deltas,
                            r_first(&dpd.deltas) - 1 + j,
                            &l, &u);
                    };

                    if (fiendish) {
                        eliminateRedundant(&new_new_deltas, 1);
                        simplifyProblem(&new_new_deltas);
                        fiendish = queryVariableBounds(&new_new_deltas,
                            r_first(&dpd.deltas) - 1 + j,
                            &l, &u);
                    };

                    if (fiendish) {
#if defined newTimeTrials
                        if (storeResult) {
#endif
                            strange_occurance("Problem still fiendish in refine:\n");
                            /* debug2 and outputFile should always be the same */
                            printProblem(&new_new_deltas);
#if defined newTimeTrials
                        }
#endif
                        break; /* just stop refining */
                    }
                }

            if (l == u) {  /* no need to refine, distance is known */
                if (l == 0) {
                    dddironly(d_info->direction, ddeq, j);
                    d_info_do_eq(d_info, j)
                }
                else if (l > 0) {
                    dddironly(d_info->direction, ddlt, j);
                }
                else {
                    dddironly(d_info->direction, ddgt, j);
                }
                d_info->distanceKnown[j] = 1;
                d_info->distance[j] = l;
            }
            else if (l != negInfinity && !(skipping_plus_refinement && l > 0))
            {
                int result;
                Problem tmpProb;

                problemcpy(&tmpProb, &reads);

                /* Try to constrain delta index variable #j to exactly l
                   in red equations
                   That is, try to strengthen D in "A(j) <<D B(k)"
                       (or,   if refining dest, in "A(i) <<D B(j)") */

                if (which == source) {
                    int varj, vark; /* variable[k] - variable[j] = l */
                    vark = r_first(&rpd.reads) - 1 + j;
                    varj = r_first(&rpd.write2s) - 1 + j;

                    e = prob_add_zero_EQ(&tmpProb, red);
                    tmpProb._EQs[e].coef[varj] = -1;
                    tmpProb._EQs[e].coef[vark] = 1;
                    tmpProb._EQs[e].coef[0] = -l;
                }
                else {
                    int vari, varj; /* variable[j] - variable[i] = l */
                    vari = r_first(&rpd.reads) - 1 + j;
                    varj = r_first(&rpd.write1s) - 1 + j;

                    e = prob_add_zero_EQ(&tmpProb, red);
                    tmpProb._EQs[e].coef[vari] = -1;
                    tmpProb._EQs[e].coef[varj] = 1;
                    tmpProb._EQs[e].coef[0] = -l;
                }
                /* if there are remaining red equations,
                   then ! (black problem  in  red problem), and
                   we can't refine delta j to u, so stop refining */

                   /* the black equations represent the write1 - read
                      flow dependence, so they must have a solution,
                      (if the dep. has not been refined, we wouldn't
                       be here unless there were a dependence.  And
                       refinement can't eliminate all the solutions,
                       since we only restrict the black equations to
                       values that don't constrain the solutions.)
                      Thus, it is ok to call hasRedEquations here. */

                result = hasRedEquations(&tmpProb, 0);
#if defined newTimeTrials
                if (storeResult) realRefineTests++;
#endif

                if (omegaPrintResult) {
                    if (result && !refinementPossible[j])
                        fprintf(debug2, "fast test could have saved refinement check\n");
                    if (!result && !refinementPossible[j])
                        fprintf(debug2, "fast test didn't think refinement was possible\n");
                }
                if (result) break;

#if defined newTimeTrials
                if (storeResult) realRefines++;
#endif
                /* else, refine  delta j to u  in delta and read */

                /* deltas must be constrained in terms of deltas:
                   read - write = l  -->  delta = -l --> delta + l = 0 */

                constrainVariableValue(&new_deltas, black,
                    r_first(&dpd.deltas) - 1 + j,
                    l);

                if (which == source)
                {
                    /* reads must be constrained in terms of read & write */
                    e = prob_add_zero_EQ(&reads, black);
                    reads._EQs[e].coef[r_first(&rpd.reads) - 1 + j] = 1;
                    reads._EQs[e].coef[r_first(&rpd.write1s) - 1 + j] = -1;
                    reads._EQs[e].coef[0] = -l;

                    e = prob_add_zero_EQ(&reads, red);
                    reads._EQs[e].coef[r_first(&rpd.reads) - 1 + j] = 1;
                    reads._EQs[e].coef[r_first(&rpd.write2s) - 1 + j] = -1;
                    reads._EQs[e].coef[0] = -l;
                }
                else {
                    /* reads must be constrained in terms of read & write */
                    e = prob_add_zero_EQ(&reads, black);
                    reads._EQs[e].coef[r_first(&rpd.write2s) - 1 + j] = 1;
                    reads._EQs[e].coef[r_first(&rpd.reads) - 1 + j] = -1;
                    reads._EQs[e].coef[0] = -l;

                    e = prob_add_zero_EQ(&reads, red);
                    reads._EQs[e].coef[r_first(&rpd.write1s) - 1 + j] = 1;
                    reads._EQs[e].coef[r_first(&rpd.reads) - 1 + j] = -1;
                    reads._EQs[e].coef[0] = -l;
                }

                if (!(d_info->direction & ddrefined))
                {
                    clone_dd_graph_node_for_refinement(d_info->dd_graph_node_to_be_cloned);
                    d_info->direction |= ddrefined;
                }
                if (l == 0) {
                    dddironly(d_info->direction, ddeq, j);
                    d_info_do_eq(d_info, j);
                }
                else if (l > 0) {
                    dddironly(d_info->direction, ddlt, j);
                }
                else {
                    dddironly(d_info->direction, ddgt, j);
                }
                d_info->distanceKnown[j] = 1;
                d_info->distance[j] = l;
            }
            else break; /* minimum distance in loop is neg Infinity */
        }
    }
}

/*
    if from_acc is a write, call refine_source
    if  to_acc  is a write, call refine_dest
    (If both are writes, I think we could get a bit more refinement
     by having a refine_both, which tries to refine either the source
     or the destination at each loop nest.  I also think this would be
     so rare that its not worth writing the code.)

    *d_info will be updated if refinement is successful
 */
void refine_dependence(a_access from, a_access to,
    dir_and_dist_info *d_info)
{
    /* Read accesses, update operations of the same type as
       one end of the dependence, and the Entry & Exit nodes
       can not kill dependences.  Thus, avoid refining with them. */

    if (!access_fetch_p(from) && !access_update_p(from) && from != Entry)
    {
        assert(access_store_p(from));
        refine_end(from, to, source, d_info);
    }
    if (!access_fetch_p(to) && !access_update_p(to) && to != ExitNode)
    {
        assert(access_store_p(to));
        refine_end(from, to, dest, d_info);
    }
}



/*
  try to refine a cover or terminator's leading 0+'s into 0's.
 */

typedef int(*test_for_one)(a_access, a_access,
    uint, uint, uint, dir_and_dist_info *,
    char *);

static void tighten_cover_or_terminator(a_access from_acc, a_access to_acc,
    dir_and_dist_info *d_info,
    char *dd_as_string,
    test_for_one which_test)
{
    int i;
#if ! defined SPEED
    char str[TINYBUFSIZ + sizeof("tightening of ")];
    strcpy(str, "tightening of ");
    strcat(str, dd_as_string);
#else
    char *str = "Tiny must be compiled without -DSPEED for debugging info";
#endif

    assert((*which_test)(from_acc, to_acc,
        accesss_depth(from_acc),
        accesss_depth(to_acc),
        accesss_shared_depth(from_acc, to_acc),
        d_info, dd_as_string));

#if defined newTimeTrials
    if (storeResult) tightenTests++;
#endif
    /* prototype version - build & solve problem again and again
       profiling suggests that we don't waste significant time here. */

       /* go from outer loops to inner, changing 0+ to 0 */
    for (i = 1; i <= d_info->nest; i++)
    {
        if (ddextract1(d_info->direction, i) == (ddeq | ddlt))
        {
            /* we have a 0+ */
            dir_and_dist_info new_info = *d_info;
            dddirreset(new_info.direction, ddlt, i);
            dddirreset(new_info.restraint, ddlt, i);
#if defined newTimeTrials
            if (storeResult) realTightenTests++;
#endif
            if ((*which_test)(from_acc, to_acc,
                accesss_depth(from_acc),
                accesss_depth(to_acc),
                accesss_shared_depth(from_acc, to_acc),
                &new_info, str))
            {
                if (!(d_info->direction & ddrefined)) {
                    clone_dd_graph_node_for_refinement(d_info->dd_graph_node_to_be_cloned);
                }
                d_info->direction = new_info.direction | ddrefined;
                d_info->restraint = new_info.restraint;
                d_info->distanceKnown[i] = 1;
                d_info->distance[i] = 0;
            }
        }

        if (ddextract1(d_info->direction, i) != ddeq)
            break;
    }
}

void tighten_cover(a_access from_acc, a_access to_acc,
    dir_and_dist_info *d_info,
    char *dd_as_string)
{
    assert(d_info->direction & ddcovers);
    tighten_cover_or_terminator(from_acc, to_acc, d_info, dd_as_string,
        test_for_coverage);
}

void tighten_terminator(a_access from_acc, a_access to_acc,
    dir_and_dist_info *d_info,
    char *dd_as_string)
{
    assert(d_info->direction & ddterminates);
    tighten_cover_or_terminator(from_acc, to_acc, d_info, dd_as_string,
        test_for_termination);
}
