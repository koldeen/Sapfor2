/* cover.c,v 1.1 1993/09/17 22:13:48 fbodin Exp */

/*
   coverage and termination tests

   Naming convention: Many of these functions and structures
   refer to "read iteration" or "write iteration" as if a
   test were being performed on flow dependence(s), even when
   the test works for other forms of dependence.
 */


#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/portable.h"
#include "include/debug.h"
#include "include/ip.h"
#include "include/lang-interf.h"
#include "include/ddomega-build.h"
#include "include/ddomega-use.h"
#include "include/kill.h"
#include "include/cover.h"

 /*
 #include "timeTrials.h"
 */
possible_reasons why_no_cover_or_terminator;


/*
   test to see if a dependence covers its destination.
 */

int test_for_coverage(a_access write_acc, a_access read_acc,
    uint write_nest, uint read_nest, uint common_nest,
    dir_and_dist_info *dd, char *dd_as_string)
{
    var_id sc_vars[maxVars], r_vars[maxVars], rs_vars[maxVars];
    var_id w_vars[maxVars], ws_vars[maxVars];

    int Nrs, Nws, Nsc, leading_0s;

    read_prob_desc rpd;   /* write1s = A[i]
                 write2s unused in coverage test
                 reads   = B[j] */
    Problem reads;

    int j, red_complete, cover;
#if ! defined NDEBUG
    int eqs, geqs;
#endif

    if (access_update_p(write_acc)) {
        set_reason(didnt_test);
        return(0);
    }

    assert(write_acc == Entry || access_store_p(write_acc));

#if defined newTimeTrials
    if (storeResult) coverTests++;
#endif

    /* If this test is changed or removed, change ddomega-use.c
       to reflect that we could have non-coverage due to some
       reason other than "didnt_test" if we haven't got all 0's */
    for (j = 1; j <= common_nest; j++) {
        if (!dddirtest(dd->direction, ddeq, j)) {
            if (omegaPrintResult) {
                fprintf(debug2, "coverage unlikely, not bothering to test:\n");
                fprintf(debug2, "  %s\n", dd_as_string);
            }
            set_reason(didnt_test);
            return 0;
        }
    }

    leading_0s = leading_zeros(dd->direction, dd->nest);

    /* PART 1: find sets of variables to be used in problem */

    Nrs = Nws = Nsc = 0;

    load_bounds_and_count_steps(read_acc, r_vars, rs_vars, &Nrs);
    load_bounds_and_count_steps(write_acc, w_vars, ws_vars, &Nws);
    load_constants_for_bounds(read_acc, sc_vars, &Nsc);
    load_constants_for_bounds(write_acc, sc_vars, &Nsc);
    load_constants_for_subscripts(read_acc, sc_vars, &Nsc);
    load_constants_for_subscripts(write_acc, sc_vars, &Nsc);

    /* PART 2: assign columns to variables
               Protect variables representing symbolic constants and
           read iteration values of loop indices, because
           we wish to test if S implies T for all values of them.*/

    read_init(&rpd, &reads, sc_and_r, Nsc, sc_vars,
        read_nest, r_vars, Nrs, rs_vars,
        write_nest, w_vars, Nws, ws_vars,
        0, NIL, 0, NIL);

    /* PART 3: build problem */

#if !defined NDEBUG
    read_inv(&rpd, &reads);
    assert(reads.getNumEqs() == 0);
    assert(reads.getNumGEqs() == 0);
    eqs = geqs = 0;
#endif

    /* TRY TO SET UP RED "T" PROBLEM:
       "i in [A] ^ A(i) << B(j) ^ A(i) sub= B(j)"
       If we can't completely describe the red problem, we can't
       test for cover - set red_complete to 0 to indicate this.
     */

     /*     i in [A] */
    red_complete =
        bound_inner_indices_and_conditionals(&reads, &rpd.write1s,
            &rpd.w1steps, &rpd.nonloops,
            leading_0s, read_acc,
            red, write_acc);

    if (!red_complete)
    {
        if (omegaPrintResult) {
            fprintf(debug2, "not checking for COVER - incomplete red bounds\n");
            fprintf(debug2, "of  %s\n", dd_as_string);
        }
        read_cleanup(&rpd);
        set_reason(non_affine_red_bound);
        return 0;
    }

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif

    /*     A(i) sub= B(j) */
    /*     equate_sub won't be 0, or there would not be a dependence */
    red_complete =
        equate_subscripts(&reads, &rpd.reads, &rpd.write1s, &rpd.nonloops,
            red, read_acc, write_acc) == complete;

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif

    if (!red_complete)
    {
        if (omegaPrintResult) {
            fprintf(debug2, "not checking for COVER - incomplete red subscripts\n");
            fprintf(debug2, "of  %s\n", dd_as_string);
        }
        read_cleanup(&rpd);
        set_reason(non_affine_red_sub);
        return 0;
    }

    /*     A(i) << B(j) */
    constrain_with_dd(&reads, &rpd.reads, &rpd.write1s, dd, red);

#if !defined NDEBUG
    read_inv(&rpd, &reads);
    for (; eqs < reads.getNumEqs(); eqs++) {
        assert(reads._EQs[eqs].color == red);
    }
    for (; geqs < reads.getNumGEqs(); geqs++) {
        assert(reads._GEQs[geqs].color == red);
    }
#endif

    /* SET UP BLACK "S" PROBLEM:  "j in [B]" */

    bound_indices_and_conditionals(&reads, &rpd.reads, &rpd.rsteps,
        &rpd.nonloops, black, read_acc);

#if ! defined NDEBUG
    read_inv(&rpd, &reads);

    for (; eqs < reads.getNumEqs(); eqs++) {
        assert(reads._EQs[eqs].color == black);
    }
    for (; geqs < reads.getNumGEqs(); geqs++) {
        assert(reads._GEQs[geqs].color == black);
    }
#endif

    /* PART 4: clean up */

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif
    read_cleanup(&rpd);

    /* PART 5: CHECK FOR COVERAGE: Forall j, Sym, does S imply T? */

    /* there must be a solution to the black equations,
       since they represent only j in [B] - if this were not true,
       there would be no flow dependencies at all */

    if (omegaPrintResult) {
        fprintf(debug2, "starting check for COVER\n");
        fprintf(debug2, "of  %s\n", dd_as_string);
        printProblem(&reads);
    }

    cover = !hasRedEquations(&reads, 0);

    if (omegaPrintResult) {
        if (cover)
            fprintf(debug2, "verified COVER:\n");
        else
            fprintf(debug2, "no COVER:\n");
        printProblem(&reads);
    }

#if defined newTimeTrials
    if (storeResult) {
        realCoverTests++;
        if (cover) realCovers++;
    }
#endif

    set_reason((possible_reasons)cover);
    return cover;
}

/*
   test to see if dependence terminates its source
   (ie an anti-dep from a read to a write termitates the read)
 */

int test_for_termination(a_access read_acc, a_access write_acc,
    uint read_nest, uint write_nest, uint common_nest,
    dir_and_dist_info *dd, char *dd_as_string)
{
    var_id sc_vars[maxVars], r_vars[maxVars], rs_vars[maxVars];
    var_id w_vars[maxVars], ws_vars[maxVars];

    int Nrs, Nws, Nsc, leading_0s;

    read_prob_desc rpd;
    Problem reads;

    int j, red_complete, termination;
#if ! defined NDEBUG
    int eqs, geqs;
#endif

    if (access_update_p(write_acc)) {
        set_reason(didnt_test);
        return(0);
    }

    assert(write_acc == Entry || access_store_p(write_acc));

#if defined newTimeTrials
    if (storeResult) terminationTests++;
#endif

    /* If this test is changed or removed, change ddomega-use.c
       to reflect that we could have non-termination due to some
       reason other than "didnt_test" if we haven't got all 0's */
    for (j = 1; j <= common_nest; j++) {
        if (!dddirtest(dd->direction, ddeq, j)) {
            if (omegaPrintResult) {
                fprintf(debug2,
                    "termination unlikely, not bothering to test:\n");
                fprintf(debug2, "  %s\n", dd_as_string);
            }
            set_reason(didnt_test);
            return 0;
        }
    }

    leading_0s = leading_zeros(dd->direction, dd->nest);

    /* PART 1: find sets of variables to be used in problem */

    Nrs = Nws = Nsc = 0;

    load_bounds_and_count_steps(read_acc, r_vars, rs_vars, &Nrs);
    load_bounds_and_count_steps(write_acc, w_vars, ws_vars, &Nws);
    load_constants_for_bounds(read_acc, sc_vars, &Nsc);
    load_constants_for_bounds(write_acc, sc_vars, &Nsc);
    load_constants_for_subscripts(read_acc, sc_vars, &Nsc);
    load_constants_for_subscripts(write_acc, sc_vars, &Nsc);

    /* PART 2: assign columns to variables
               Protect variables representing symbolic constants and
           read iteration values of loop indices, because
           we wish to test if S implies T for all values of them.*/

    read_init(&rpd, &reads, sc_and_r, Nsc, sc_vars,
        read_nest, r_vars, Nrs, rs_vars,
        write_nest, w_vars, Nws, ws_vars,
        0, NIL, 0, NIL);

    /* PART 3: build problem */

#if !defined NDEBUG
    read_inv(&rpd, &reads);
    assert(reads.getNumEqs() == 0);
    assert(reads.getNumGEqs() == 0);
    eqs = geqs = 0;
#endif

    /* TRY TO SET UP RED "T" PROBLEM:
       "j in [B] ^ A(i) << B(j) ^ A(i) sub= B(j)"
       If we can't completely describe the red problem, we can't
       test for termination - set red_complete to 0 to indicate this.
     */

     /*     j in [B] */
    red_complete =
        bound_inner_indices_and_conditionals(&reads, &rpd.write1s,
            &rpd.w1steps, &rpd.nonloops,
            leading_0s, read_acc,
            red, write_acc);

    if (!red_complete)
    {
        if (omegaPrintResult) {
            fprintf(debug2,
                "not checking for TERMINATION - incomplete red bounds\n");
            fprintf(debug2, "of  %s\n", dd_as_string);
        }
        read_cleanup(&rpd);
        set_reason(non_affine_red_bound);
        return 0;
    }

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif

    /*     A(i) sub= B(j) */
    /*     equate_sub won't be 0, or there would not be a dependence */
    red_complete =
        equate_subscripts(&reads, &rpd.reads, &rpd.write1s, &rpd.nonloops,
            red, read_acc, write_acc) == complete;

    if (!red_complete)
    {
        if (omegaPrintResult) {
            fprintf(debug2,
                "not checking for TERMINATION - incomplete red subscript\n");
            fprintf(debug2, "of  %s\n", dd_as_string);
        }
        read_cleanup(&rpd);
        set_reason(non_affine_red_sub);
        return 0;
    }

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif

    /*     A(i) << B(j) */
    constrain_with_dd(&reads, &rpd.write1s, &rpd.reads, dd, red);

#if !defined NDEBUG
    read_inv(&rpd, &reads);
    for (; eqs < reads.getNumEqs(); eqs++) {
        assert(reads._EQs[eqs].color == red);
    }
    for (; geqs < reads.getNumGEqs(); geqs++) {
        assert(reads._GEQs[geqs].color == red);
    }
#endif

    /* SET UP BLACK "S" PROBLEM:  "i in [A]" */

    bound_indices_and_conditionals(&reads, &rpd.reads, &rpd.rsteps,
        &rpd.nonloops, black, read_acc);

#if ! defined NDEBUG
    read_inv(&rpd, &reads);

    for (; eqs < reads.getNumEqs(); eqs++) {
        assert(reads._EQs[eqs].color == black);
    }
    for (; geqs < reads.getNumGEqs(); geqs++) {
        assert(reads._GEQs[geqs].color == black);
    }
#endif

    /* PART 4: clean up */

#if ! defined NDEBUG
    read_inv(&rpd, &reads);
#endif
    read_cleanup(&rpd);

    /* PART 5: CHECK FOR TERMINATION: Forall i, Sym, does S imply T? */

    /* there must be a solution to the black equations,
       since they represent only i in [A] - if this were not true,
       there would be no flow dependencies at all */

    if (omegaPrintResult) {
        fprintf(debug2, "starting check for TERMINATION\n");
        fprintf(debug2, "of  %s\n", dd_as_string);
        printProblem(&reads);
    }

    termination = !hasRedEquations(&reads, 0);

    if (omegaPrintResult) {
        if (termination)
            fprintf(debug2, "verified TERMINATION.\n");
        else
            fprintf(debug2, "no TERMINATION.\n");
    }

#if defined newTimeTrials
    if (storeResult) {
        realTerminationTests++;
        if (termination) realTerminators++;
    }
#endif

    set_reason((possible_reasons)termination);
    return termination;
}
