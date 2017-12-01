/* add-assert.c,v 1.1 1993/09/17 22:13:46 fbodin Exp */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
/* #include "portable.h"
 #include "lang-interf.h"*/

#include "include/add-assert.h"
#include "include/ddomega.h"
#include "include/ddomega-build.h"
#include "include/ip.h"
#include "include/debug.h"
#include "include/flags.h"

//#include "include/screen.h"
#include "include/Exit.h"

 /*
 #include "message.h"
 #include "getword.h"
 #include "timeTrials.h" 
 */

 /*
    zap problem description contains information needed
    to associate variable accesses in the tiny program with
    variables in the integer programming problem that is
    used to try determine the gist of the dependence.

    zap problems are very much like delta problems,
    except that there are no deltas and the symbolic constants
    are protected

  */

typedef struct {
    range nonloops;  /* symbolic constants */
    range deltas;    /* deltas for common indices  */
    range access1s;  /* index variables for access 1 */
    range access2s;  /* index variables for access 2 */
    range steps1;    /* step constraints for a1 */
    range steps2;    /* step constraints for a1 */
    var_id vars[maxVars];
} zap_prob_desc;

#define zap_Nvars(zpd)     (r_last(&(zpd)->steps2))

#if ! defined NDEBUG
static int is_step_expr(var_id n)
{
    return n == 0;
}

static void zap_inv(zap_prob_desc *zpd, Problem *p)
{
    int v;

    assert(p->_nVars < maxVars);
    assert(p->_nVars >= zap_Nvars(zpd));
    assert(p->_safeVars == r_length(&zpd->nonloops));
    assert(r_first(&zpd->nonloops) == 1);
    assert(r_last(&zpd->nonloops) + 1 == r_first(&zpd->access1s));
    assert(r_last(&zpd->access1s) + 1 == r_first(&zpd->access2s));
    assert(r_last(&zpd->access2s) + 1 == r_first(&zpd->steps1));
    assert(r_last(&zpd->steps1) + 1 == r_first(&zpd->steps2));

    for (v = 0; v < r_length(&zpd->access1s); v++) {
        assert(var_id_index_p(zpd->vars[v + r_first(&zpd->access1s)]));
        assert(var_ids_loop_no(zpd->vars[v + r_first(&zpd->access1s)]) == v + 1);
    }

    for (v = 0; v < r_length(&zpd->access2s); v++) {
        assert(var_id_index_p(zpd->vars[v + r_first(&zpd->access2s)]));
        assert(var_ids_loop_no(zpd->vars[v + r_first(&zpd->access2s)]) == v + 1);
    }

    for (v = 0; v < r_length(&zpd->nonloops); v++) {
        assert(var_id_const_p(zpd->vars[v + r_first(&zpd->nonloops)]));

        assert((var_ids_tag(zpd->vars[v + r_first(&zpd->nonloops)]) ==
            v + r_first(&zpd->nonloops)) ||
            (var_ids_tag(zpd->vars[v + r_first(&zpd->nonloops)]) == UNTAGGED));
    }

    for (v = 0; v < r_length(&zpd->steps1); v++) {
        assert(is_step_expr(zpd->vars[v + r_first(&zpd->steps1)]));
    }
    for (v = 0; v < r_length(&zpd->steps2); v++) {
        assert(is_step_expr(zpd->vars[v + r_first(&zpd->steps2)]));
    }

    for (v = 0; v < p->_numGEQs; v++) {
        assert(p->_GEQs[v].touched);
    }
}
#endif 

#define MaxNameLen   254
#define MaxSuffixLen 1

static char *zap_getVarName(uint v, void *args)
{
    zap_prob_desc *zpd = (zap_prob_desc*)args;
    static char name[MaxNameLen + MaxSuffixLen + 1];

    assert(v <= zap_Nvars(zpd));

    if (zpd->vars[v] &&
        (var_id_index_p(zpd->vars[v]) || var_id_const_p(zpd->vars[v])))
    {
        strncpy(name, var_ids_name(zpd->vars[v]), MaxNameLen);
        name[MaxNameLen] = 0;
    }
    else {
        assert(is_step_expr(zpd->vars[v]));
        strcpy(name, "<trip>");
    }

    if (r_in(&zpd->access1s, v) || r_in(&zpd->steps1, v))
        strcat(name, "1");
    else if (r_in(&zpd->access2s, v) || r_in(&zpd->steps2, v))
        strcat(name, "2");

    return name;
}


/*
   set up all fields in zap_prob_desc
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

static void zap_init(zap_prob_desc *zpd, Problem *p,
    uint Na1, var_id a1_vars[],
    uint Na2, var_id a2_vars[],
    uint Nsc, var_id sc_vars[],
    uint Ns1, var_id s1_vars[],
    uint Ns2, var_id s2_vars[])
{
    int v;

    zpd->nonloops._first = 1;
    zpd->nonloops._length = Nsc;
    zpd->access1s._first = 1 + Nsc;
    zpd->access1s._length = Na1;
    zpd->access2s._first = 1 + Nsc + Na1;
    zpd->access2s._length = Na2;
    zpd->steps1._first = 1 + Nsc + Na1 + Na2;
    zpd->steps1._length = Ns1;
    zpd->steps2._first = 1 + Nsc + Na1 + Na2 + Ns1;
    zpd->steps2._length = Ns2;

    if (zap_Nvars(zpd) > maxVars) {
        assert(0 && "Problem too big");
        fprintf(stderr, "Too many variables for omega test\n");
        Exit(2);
        /* We really should add all possible dependencies here */
    }

    zpd->vars[0] = 0;

    /* a1[1..Na1] and a2[1..Na2] are valid */

    for (v = 0; v < r_length(&zpd->access1s); v++) {
        assert(a1_vars[v + 1] != NIL);
        zpd->vars[v + r_first(&zpd->access1s)] = a1_vars[v + 1];
    }

    for (v = 0; v < r_length(&zpd->access2s); v++) {
        assert(a2_vars[v + 1] != NIL);
        zpd->vars[v + r_first(&zpd->access2s)] = a2_vars[v + 1];
    }

    /* sc_vars[0..Nsc-1] are valid */
    for (v = 0; v < Nsc; v++) {
        assert(sc_vars[v] != NIL);
        zpd->vars[v + r_first(&zpd->nonloops)] = sc_vars[v];
        var_ids_tag(sc_vars[v]) = v + r_first(&zpd->nonloops);
    }

    /* s1_vars[0..Ns1] and s2_vars[0..Ns2] hold steps
       FROM INNERMOST TO OUTERMOST LOOPS */

    for (v = 0; v < Ns1; v++) {
        assert(s1_vars[Ns1 - 1 - v] == NIL);
        zpd->vars[v + r_first(&zpd->steps1)] = s1_vars[Ns1 - 1 - v];
    }
    for (v = 0; v < Ns2; v++) {
        assert(s2_vars[Ns2 - 1 - v] == NIL);
        zpd->vars[v + r_first(&zpd->steps2)] = s2_vars[Ns2 - 1 - v];
    }

    init_prob(p, zap_Nvars(zpd), Nsc, zap_getVarName, zpd);

#if ! defined NDEBUG
    zap_inv(zpd, p);
#endif
}


/* clear the tags for symbolic constants */

static void zap_cleanup(zap_prob_desc *zpd)
{
    int v;

    for (v = 0; v < r_length(&zpd->nonloops); v++) {
        var_ids_tag(zpd->vars[v + r_first(&zpd->nonloops)]) = UNTAGGED;
    }
}



static char *geq_as_string(Problem *p, int geq)
{
    static char buf[81];

    sprintEqn(buf, p, &p->_GEQs[geq], 1, 0);
    return buf;
}

static int find_reds(Problem *p, int reds[])
{
    int i, n_reds = 0;
    for (i = 0; i < p->_numGEQs; i++) {
        if (p->_GEQs[i].color == red) {
            reds[n_reds++] = i;
        }
    }
    return n_reds;
}



/* find, and try to get rid of a red in p */
#if 0
static bool mccarthy(Problem *p, var_id vars[])
{
    WINDOW *gist_w;
    int Gist_Lines, Gist_Cols, Gist_Offset;
    int reds[maxGEQs];  /* only handle GEQs now */
    int y, x, i;
    int n_reds, zappee;
    bool check;

    check = hasRedEquations(p, 1);
    assert(check);
    n_reds = find_reds(p, reds);
    assert(n_reds > 0);  /* this seems the right assertion for McCarthy */

    Gist_Lines = n_reds + 5;
    Gist_Cols = COLS;
    Gist_Offset = 0;

    gist_w = newwin(Gist_Lines, Gist_Cols, Gist_Offset, 0);

    if (!gist_w) {
        Message_Add("couldn't create window for equations.");
        screen_update();
        return 0;
    }

    for (x = 1; x < Gist_Cols; x++) screen_waddch(gist_w, 0, x, '-');
    for (x = 1; x < Gist_Cols; x++) screen_waddch(gist_w, 2, x, '-');
    for (y = 1; y < Gist_Lines; y++) screen_waddch(gist_w, y, 0, '|');
    for (y = 1; y < Gist_Lines; y++) screen_waddch(gist_w, y, Gist_Cols - 1, '|');
    for (x = 1; x < Gist_Cols; x++) screen_waddch(gist_w, Gist_Lines - 1, x, '-');

    screen_waddch(gist_w, 0, 0, '+');
    screen_waddch(gist_w, 0, Gist_Cols - 1, '+');
    screen_waddch(gist_w, 2, 0, '+');
    screen_waddch(gist_w, 2, Gist_Cols - 1, '+');
    screen_waddch(gist_w, Gist_Lines - 1, 0, '+');
    screen_waddch(gist_w, Gist_Lines - 1, Gist_Cols - 1, '+');

    for (i = 0; i < n_reds; i++)
        negateGEQ(p, reds[i]);

    screen_wprint(gist_w, 1, 1, "%s",
        "Which of the following is always true (0 for none)?    ");

    for (i = 0; i < n_reds; i++)
    {
        sint j, length;
        char eqn_string[80];

        strcpy(eqn_string, geq_as_string(p, reds[i]));
        length = strlen(eqn_string);
        for (j = 1; j < length - 1; j++)
            eqn_string[j - 1] = eqn_string[j];
        eqn_string[length - 2] = '\0';

        screen_wprint(gist_w, i + 3, 1, "%2d: %-60s\n", i + 1, eqn_string);
    }

    do
        zappee = getint(gist_w, 1, 53);
    while (zappee < 0 || zappee > n_reds);

    if (zappee != 0)
        add_GEQ_assertion(p, vars, reds[zappee - 1]);

    delwin(gist_w);
    screen_touch();
#if ! defined NOT_TINY
    print_tiny(Entry, 1, 0);
#endif

    return zappee != 0;
}
#endif

/*
   try to build the gist problem
   return 1 if it has symbolic constants and there are red equations

   NOTE that reduceWithSubs must be 0
 */

static elimination_possible
build_zap_problem(dd_current dd, Problem *p, zap_prob_desc *zpd)
{
    var_id consts[maxVars],
        a1vars[maxVars], a2vars[maxVars],
        steps1[maxVars], steps2[maxVars];
    int Nconsts, Nsteps1, Nsteps2;
    a_access access1 = dd_current_src(dd), access2 = dd_current_dest(dd);
    uint nest1 = accesss_depth(access1), nest2 = accesss_depth(access2);
    int j;

    assert(!reduceWithSubs);

    if (omegaPrintResult == 1) {
        fprintf(debug2, "\n\nZap: Finding Gist of dependence:\n");
        fprintf(debug2, "%s\n", dd_current_as_string(dd));
    }

#if defined newTimeTrials
    if (storeResult) zapTests++;
#endif

    /* BUILD PROBLEM "p": put things we know as black equations,
       and things we know only if there is a dependence as red equations */

       /* PART 1: find sets of variables to be used in problem */

    Nsteps1 = Nsteps2 = Nconsts = 0;

    load_bounds_and_count_steps(access1, a1vars, steps1, &Nsteps1);
    load_bounds_and_count_steps(access2, a2vars, steps2, &Nsteps2);
    load_constants_for_bounds(access1, consts, &Nconsts);
    load_constants_for_bounds(access2, consts, &Nconsts);
    load_constants_for_subscripts(access1, consts, &Nconsts);
    load_constants_for_subscripts(access2, consts, &Nconsts);

    /* PART 2: assign columns to variables */

    zap_init(zpd, p,
        nest1, a1vars, nest2, a2vars, Nconsts, consts,
        Nsteps1, steps1, Nsteps2, steps2);

    if (Nconsts == 0)
    {
        assert(p->_safeVars == 0);
        zap_cleanup(zpd);
        if (omegaPrintResult == 1) {
            fprintf(debug2, "Zap: No symbolic constants, no way to zap.\n");
        }
        return impossible;
    }

#if ! defined NDEBUG
    zap_inv(zpd, p);
#endif

    /* PART 3: build problem */

    /* add what we know if dd exists as red equations */
    equate_subscripts(p, &zpd->access1s, &zpd->access2s, &zpd->nonloops,
        red, access1, access2);

    /* we don't have to bail out if there are non-affine
       subscript expressions - that just gives us fewer
       (possibly 0) ways to kill */

       /* black equations: things that aren't interesting: */
       /* we're in bounds */
    bound_indices_and_conditionals(p, &zpd->access1s, &zpd->steps1, &zpd->nonloops, black, access1);
    bound_indices_and_conditionals(p, &zpd->access2s, &zpd->steps2, &zpd->nonloops, black, access2);

    /* we're within dddir */
    for (j = 1; j <= dd_current_nest(dd); j++) {
        constrain_with_convex_dddir(p, &zpd->access2s, &zpd->access1s, &dd_current_dir(dd), j, black);
    }

    /* PART 4: clean up */

    zap_cleanup(zpd);

    /* PART 5: compute gist */

    if (omegaPrintResult == 1) {
        fprintf(debug2, "Zap: Finding gist of problem:\n");
        printProblem(p);
    }

#if defined newTimeTrials
    if (storeResult) realZapTests++;
#endif

    if (hasRedEquations(p, 0))
    {
        if (printing_zap_gists)
        {
            fprintf(debug2, "Got red equations:\n");
            printRedEquations(p);
        }
        if (p->_nVars != p->_safeVars)
        {
            if (omegaPrintResult == 1 || printing_zap_gists) {
                fprintf(debug2, "Can't handle splintered problems yet\n");
            }
            return too_hard;
        }
        else {
#if defined newTimeTrials
            if (storeResult) realZappable++;
#endif
            if (omegaPrintResult == 1)
                fprintf(debug2, "Zap possible\n");
            return possible;
        }
    }
    else {
        if (omegaPrintResult == 1 || printing_zap_gists)
            fprintf(debug2, "Zap not possible\n");
        return impossible;
    }
}

bool try_to_eliminate(dd_current dd)
{
    int old_reduceWithSubs;
    Problem p;
    zap_prob_desc zpd;
    bool result;
    elimination_possible ep;

    old_reduceWithSubs = reduceWithSubs;
    reduceWithSubs = 0;  /* to make combining problems easier */

    if ((ep = build_zap_problem(dd, &p, &zpd)) == possible)
    {
        //result = mccarthy(&p, zpd.vars);
    }
    else {
        switch (ep) {
        case too_hard:
            Message_Add("The Gist of this dependence is too complicated");
            if (omegaPrintResult == 1) {
                fprintf(debug2, "Zap:  Gist contains wild cards - give up.\n");
            }
            break;
        case impossible:
            Message_Add("No interesting assertions zap the dependence");
            if (omegaPrintResult == 1) {
                fprintf(debug2, "Zap:  Gist = \"True\" - don't bother asking if we should negate it.\n");
            }
            break;
        case possible:
        default:
            assert(0 && "Can't get here.");
        }
        result = 0;
    }

    reduceWithSubs = old_reduceWithSubs;
    return result;
}

elimination_possible possible_to_eliminate(dd_current dd)
{
    int old_reduceWithSubs;
    Problem p;
    zap_prob_desc zpd;
    elimination_possible result;

    old_reduceWithSubs = reduceWithSubs;
    reduceWithSubs = 0;  /* to make combining problems easier */

    result = build_zap_problem(dd, &p, &zpd);

    reduceWithSubs = old_reduceWithSubs;
    return result;
}
