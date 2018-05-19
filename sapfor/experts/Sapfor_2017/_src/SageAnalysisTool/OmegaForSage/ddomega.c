/* ddomega.c,v 1.1 1993/09/17 22:13:51 fbodin Exp */

/*
   Basic data dependence test using the omega test -
   dd_omega_test determines if two array accesses might access the same element

   Also, functions to manipulate the structures used to
   represent various sorts of problems that we pass to the
   omega test.

   Naming convention: Many of these functions and structures
   refer to "read iteration" or "write iteration" as if a
   test were being performed on flow dependence(s), even when
   the test works for other forms of dependence.
 */


#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/flags.h"
#include "include/portable.h"
#include "include/debug.h"
#include "include/ip.h"
#include "include/lang-interf.h"
#include "include/ddomega-build.h"
#include "include/ddomega-use.h"
#include "include/ddomega.h"
#include "include/Exit.h"
#include "include/timeTrials.h"

Problem deltas;    /* original problem -- needed in refine */


/*
   perform the omega test on the array accesses access1 and access2
   see dddriver.h for a description of arguments.

 * Entry -> fetch/update dependencies.
 * write/update -> ExitNode dependencies.
 * Added by vadik 11/08/92.
 */



PROC void dd_omega_test(a_access access1, a_access access2,
    ddnature oitype, ddnature iotype,
    uint nest1, uint nest2, uint bnest)
{
    Problem prob;
    delta_prob_desc dpd;   /* must have extent >= that of "prob" */
    int subs_may_equal;

#if defined newTimeTrials
    if (storeResult) omegaTests++;
#endif

    assert(access1 == Entry || access2 == ExitNode ||
        accesss_sym(access2) == accesss_sym(access1)); /* same var */
    assert(!(access_fetch_p(access1) && access_store_p(access2)));
    assert(oitype != ddanti);

    /* if omitTopLevel, we are only interested in parallelizing loops,
       and thus don't care about data dependencies between things
       that don't share any common loops */

    if (omitTopLevel && bnest == 0)
    {
        dir_and_dist_info d_info;

        d_info.nest = 0;
        d_info.dd_graph_node_to_be_cloned = 0;

        if (access_lexically_preceeds(access1, access2))
        {
            store_dependence(oitype, access1, access2, &d_info);
        }
        else if (access_lexically_preceeds(access2, access1))
        {
            store_dependence(iotype, access2, access1, &d_info);
        }
        /* else access1 == access2 or they're in different branches of an if */
        return;
    }

    subs_may_equal = build_delta_prob_desc(&dpd, &prob, access1, access2,
        nest1, nest2, bnest);

    if (omegaPrintResult == 1) {
        fprintf(debug2, "\n\nconsidering dependency:\n");
        fprintf(debug2, "\tfrom a %s of %s at statement %d\n",
            access_store_p(access1) || access1 == Entry ? "store" :
            (access_fetch_p(access1) ? "read" : "update"),
            access_as_string(access1), accesss_lineno(access1));
        fprintf(debug2, "\tto a %s of %s at statement %d\n",
            access_store_p(access2) ? "store" :
            (access_fetch_p(access2) || access2 == ExitNode ? "read" : "update"),
            access_as_string(access2), accesss_lineno(access2));
        printProblem(&prob);
    }

    if (subs_may_equal && simplifyProblem(&prob)) {

        /* call omega test to add directions */
        calculateDDVectors(&prob, access1, access2, oitype, iotype,
            nest1, nest2, bnest, r_length(&dpd.nonloops));
    }

#if defined newTimeTrials
    if (storeResult) realOmegaTests++;
#endif

}/* dd_omega_test */



/* functions used to build "delta problem description" */

int build_delta_prob_desc(delta_prob_desc *dpd, Problem *prob,
    a_access access1, a_access access2,
    int nest1, int nest2, int bnest)
{
    var_id consts[maxVars],
        vars1[maxVars], vars2[maxVars],
        steps1[maxVars], steps2[maxVars];
    int Nconsts, Nsteps1, Nsteps2, subs_may_equal;

    /* PART 1: find sets of variables to be used in problem */

    Nsteps1 = Nsteps2 = Nconsts = 0;

    load_bounds_and_count_steps(access1, vars1, steps1, &Nsteps1);
    load_bounds_and_count_steps(access2, vars2, steps2, &Nsteps2);
    load_constants_for_bounds(access1, consts, &Nconsts);
    load_constants_for_bounds(access2, consts, &Nconsts);
    load_constants_for_subscripts(access1, consts, &Nconsts);
    load_constants_for_subscripts(access2, consts, &Nconsts);

    /* PART 2: assign columns to variables */

    delta_init(dpd, prob, black, bnest,
        nest1, vars1, nest2, vars2, Nconsts, consts,
        Nsteps1, steps1, Nsteps2, steps2);

    assert(bnest == prob->_safeVars);

    /* PART 3: build problem */

    bound_indices_and_conditionals(prob, &dpd->access1s, &dpd->steps1,
        &dpd->nonloops,
        black, access1);
    bound_indices_and_conditionals(prob, &dpd->access2s, &dpd->steps2,
        &dpd->nonloops,
        black, access2);
    subs_may_equal = equate_subscripts(prob, &dpd->access1s, &dpd->access2s,
        &dpd->nonloops,
        black, access1, access2);

    /* PART 4: clean up */

#if ! defined NDEBUG
    delta_inv(dpd, prob);
#endif

    delta_cleanup(dpd);

    return subs_may_equal;
}


/* name information for buffers in getVarName fns */
#define MaxNameLen   254
#define MaxSuffixLen 1

#if ! defined NDEBUG
static int var_id_is_step_expr(var_id n)
{
    return n == 0;
}

void delta_inv(delta_prob_desc *dpd, Problem *p)
{
    int v;

    assert(p->_nVars < maxVars);
    assert(p->_nVars >= delta_Nvars(dpd));
    assert(p->_safeVars == r_length(&dpd->deltas));
    assert(r_length(&dpd->deltas) <= r_length(&dpd->access1s));
    assert(r_length(&dpd->deltas) <= r_length(&dpd->access2s));
    assert(r_first(&dpd->deltas) == 1);
    assert(r_last(&dpd->deltas) + 1 == r_first(&dpd->access1s));
    assert(r_last(&dpd->access1s) + 1 == r_first(&dpd->access2s));
    assert(r_last(&dpd->access2s) + 1 == r_first(&dpd->nonloops));
    assert(r_last(&dpd->nonloops) + 1 == r_first(&dpd->steps1));
    assert(r_last(&dpd->steps1) + 1 == r_first(&dpd->steps2));

    for (v = 0; v < r_length(&dpd->deltas); v++) {
        assert(var_id_index_p(dpd->vars[v + r_first(&dpd->deltas)]));
        assert(var_ids_loop_no(dpd->vars[v + r_first(&dpd->deltas)]) == v + 1);
        assert(var_id_index_p(dpd->vars[v + r_first(&dpd->access1s)]));
        assert(var_ids_loop_no(dpd->vars[v + r_first(&dpd->access1s)]) == v + 1);
        assert(var_id_index_p(dpd->vars[v + r_first(&dpd->access2s)]));
        assert(var_ids_loop_no(dpd->vars[v + r_first(&dpd->access2s)]) == v + 1);
    }

    for (v = r_length(&dpd->deltas); v < r_length(&dpd->access1s); v++) {
        assert(var_id_index_p(dpd->vars[v + r_first(&dpd->access1s)]));
        assert(var_ids_loop_no(dpd->vars[v + r_first(&dpd->access1s)]) == v + 1);
    }

    for (v = r_length(&dpd->deltas); v < r_length(&dpd->access2s); v++) {
        assert(var_id_index_p(dpd->vars[v + r_first(&dpd->access2s)]));
        assert(var_ids_loop_no(dpd->vars[v + r_first(&dpd->access2s)]) == v + 1);
    }

    for (v = 0; v < r_length(&dpd->nonloops); v++) {
        assert(var_id_const_p(dpd->vars[v + r_first(&dpd->nonloops)]));

        assert((var_ids_tag(dpd->vars[v + r_first(&dpd->nonloops)]) ==
            v + r_first(&dpd->nonloops)) ||
            (var_ids_tag(dpd->vars[v + r_first(&dpd->nonloops)]) == UNTAGGED));
    }

    for (v = 0; v < r_length(&dpd->steps1); v++) {
        assert(var_id_is_step_expr(dpd->vars[v + r_first(&dpd->steps1)]));
    }
    for (v = 0; v < r_length(&dpd->steps2); v++) {
        assert(var_id_is_step_expr(dpd->vars[v + r_first(&dpd->steps2)]));
    }

    for (v = 0; v < p->_numGEQs; v++) {
        assert(p->_GEQs[v].touched);
    }
}
#endif 


static char *delta_getVarName(uint v, void *args)
{
    delta_prob_desc *dpd = (delta_prob_desc*)args;

    static char name[MaxNameLen + MaxSuffixLen + 1];

    assert(v <= delta_Nvars(dpd));

    if (dpd->vars[v] &&
        (var_id_index_p(dpd->vars[v]) || var_id_const_p(dpd->vars[v])))
    {
        strncpy(name, var_ids_name(dpd->vars[v]), MaxNameLen);
        name[MaxNameLen] = 0;
    }
    else {
        assert(var_id_is_step_expr(dpd->vars[v]));
        strcpy(name, "<trip>");
    }

    if (r_in(&dpd->deltas, v))
        strcat(name, "^");
    else if (r_in(&dpd->access1s, v) || r_in(&dpd->steps1, v))
        strcat(name, "1");
    else if (r_in(&dpd->access2s, v) || r_in(&dpd->steps2, v))
        strcat(name, "2");

    return name;
}

/*
   set up all fields in delta_prob_desc
   copy info from a1_vars, a2_vars, and sc_vars into "omega_vars"
   a1_vars and a2_vars have been set by load_bounds_and_count_steps
     that is, they run from element 1 to depth+Nsteps
   sc_vars have been set up by the load_constants functions
     it runs from 0 to Nconsts - 1
   change tags on nodes for symbolic constants to be the
     indices into "vars" -- that is, the indices in the IP variable array
   change order of steps to be outer loop to inner and
     adjust tags accordingly (this way the common loop steps
     can (and will) be aligned)
   add equalities for the definitions of the deltas to p
 */

void delta_init(delta_prob_desc *dpd, Problem *p,
    int delta_color, uint Nd,
    uint Na1, var_id a1_vars[],
    uint Na2, var_id a2_vars[],
    uint Nsc, var_id sc_vars[],
    uint Ns1, var_id s1_vars[],
    uint Ns2, var_id s2_vars[])
{
    int v;

    dpd->deltas._first = 1;
    dpd->deltas._length = Nd;
    dpd->access1s._first = 1 + Nd;
    dpd->access1s._length = Na1;
    dpd->access2s._first = 1 + Nd + Na1;
    dpd->access2s._length = Na2;
    dpd->nonloops._first = 1 + Nd + Na1 + Na2;
    dpd->nonloops._length = Nsc;
    dpd->steps1._first = 1 + Nd + Na1 + Na2 + Nsc;
    dpd->steps1._length = Ns1;
    dpd->steps2._first = 1 + Nd + Na1 + Na2 + Nsc + Ns1;
    dpd->steps2._length = Ns2;

    if (delta_Nvars(dpd) > maxVars) {
        assert(0 && "Problem too big");
        fprintf(stderr, "Too many variables for omega test\n");
        Exit(2);
        /* We really should add all possible dependencies here */
    }

    dpd->vars[0] = 0;

    /* a1[1..Na1] and a2[1..Na2] are valid */

    for (v = 0; v < r_length(&dpd->deltas); v++) {
        assert(a1_vars[v + 1] == a2_vars[v + 1]);
        assert(a1_vars[v + 1] != NIL);
        dpd->vars[v + r_first(&dpd->deltas)] =
            dpd->vars[v + r_first(&dpd->access1s)] =
            dpd->vars[v + r_first(&dpd->access2s)] = a1_vars[v + 1];
    }

    for (v = r_length(&dpd->deltas); v < r_length(&dpd->access1s); v++) {
        assert(a1_vars[v + 1] != NIL);
        dpd->vars[v + r_first(&dpd->access1s)] = a1_vars[v + 1];
    }

    for (v = r_length(&dpd->deltas); v < r_length(&dpd->access2s); v++) {
        assert(a2_vars[v + 1] != NIL);
        dpd->vars[v + r_first(&dpd->access2s)] = a2_vars[v + 1];
    }

    /* sc_vars[0..Nsc-1] are valid */
    for (v = 0; v < Nsc; v++) {
        assert(sc_vars[v] != NIL);
        dpd->vars[v + r_first(&dpd->nonloops)] = sc_vars[v];
        var_ids_tag(sc_vars[v]) = v + r_first(&dpd->nonloops);
    }

    /* s1_vars[0..Ns1] and s2_vars[0..Ns2] hold steps
       FROM INNERMOST TO OUTERMOST LOOPS */

    for (v = 0; v < Ns1; v++) {
        assert(s1_vars[Ns1 - 1 - v] == NIL);
        dpd->vars[v + r_first(&dpd->steps1)] = s1_vars[Ns1 - 1 - v];
    }
    for (v = 0; v < Ns2; v++) {
        assert(s2_vars[Ns2 - 1 - v] == NIL);
        dpd->vars[v + r_first(&dpd->steps2)] = s2_vars[Ns2 - 1 - v];
    }

    init_prob(p, delta_Nvars(dpd), r_length(&dpd->deltas),
        delta_getVarName, dpd);

    set_deltas(p, delta_color, &dpd->deltas, &dpd->access1s, &dpd->access2s);

#if ! defined NDEBUG
    delta_inv(dpd, p);
#endif

}


/* clear the tags for symbolic constants */

void delta_cleanup(delta_prob_desc *dpd)
{
    int v;

    for (v = 0; v < r_length(&dpd->nonloops); v++) {
        var_ids_tag(dpd->vars[v + r_first(&dpd->nonloops)]) = UNTAGGED;
    }
}
