/* ddomega-use.c,v 1.1 1993/09/17 22:13:50 fbodin Exp */


/*
   calls to omega test to determine data dependencies from a problem
   (as defined in ddomega.c & built by the code in ddomega-build.c)
 */

#include <assert.h>
#include "include/portable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/debug.h"
#include "include/lang-interf.h"
#include "include/ip.h"
#include "include/ddomega-build.h"
#include "include/ddomega-use.h"
#include "include/ddomega.h"
#include "include/omega2flags.h"
#include "include/refine.h"
#include "include/cover.h"
#include "include/missing.h"
#include "include/Exit.h"
#include "include/timeTrials.h"

 /* information about nodes involved in dependence */
typedef struct {
    a_access access1, access2;
    ddnature oitype, iotype;
    uint nest1, nest2, commonNesting;
} situation;

void out_of_memory()
{
    fprintf(debug2, "Memory Allocation failed\n");
    Exit(2);
}


static dddirection dd_convert[] = { ddgt, ddeq, ddlt };
/* dd_convert(i+1) is dddirection for i */

#if !defined SPEED

static char *dir_and_dist_as_str(dir_and_dist_info *d_info, ddnature type, a_access from_access, a_access to_access)
{
    static char buf[TINYBUFSIZ];
    char f[TINYBUFSIZ];
    uint n, l, l0;
    char ch;
    dddirection thisdd;

    strcpy(f, access_as_string(from_access));
    { char *ss;
    switch (type) {
    case ddflow:    ss = "flow";   break;
    case ddanti:    ss = "anti";   break;
    case ddoutput:  ss = "output"; break;
    case ddreduce:  ss = "reduce"; break;
    default:        ss = ""; /* make compiler happy */
        ErrAssert("dir_and_dist_as_str: wrong dependence type");
    }
    sprintf(buf, "%-6s %3ld: %-15.15s --> %3ld: %-15.15s ", ss,
        accesss_lineno(from_access), f,
        accesss_lineno(to_access), access_as_string(to_access));
    }

    l0 = l = strlen(buf);

    ch = '(';
    for (n = 1; n <= d_info->nest; ++n) {
        buf[l++] = ch;
        ch = ',';
        thisdd = ddextract1(d_info->direction, n);
        if (d_info->distanceKnown[n]) {
            sprintf(&(buf[l]), "%ld", d_info->distance[n]);
            l = strlen(buf);
        }
        else if (thisdd == ddlt + ddeq + ddgt) {
            buf[l++] = '*';
        }
        else {
            if (ddtest1(thisdd, ddeq)) buf[l++] = '0';
            if (ddtest1(thisdd, ddlt)) buf[l++] = '+';
            if (ddtest1(thisdd, ddgt)) buf[l++] = '-';
        }
    }
    if (d_info->nest > 0)
        buf[l++] = ')';

    while (l < l0 + 18)
        buf[l++] = ' ';
    buf[l] = 0;

    append_dd_flags(buf, d_info->direction);

    return buf;
}
#endif


/*
   do refinement, cover, and termination tests, set appropriate flags,
   then store dependence.
 */

static void
flag_and_store_dependence(ddnature nature,
    a_access from_access, a_access to_access,
    dir_and_dist_info *d_info)
{
    store_dependence(nature, from_access, to_access, d_info);

    if (!skipping_omega2) {
#if !defined SPEED
        char *str = dir_and_dist_as_str(d_info, nature, from_access, to_access);
#else
        char *str = "Tiny must be compiled without -DSPEED for debug2 output";
#endif

        if ((nature == ddflow || nature == ddoutput) &&
            from_access != Entry && to_access != ExitNode)
        {
            int covers, j;
            covers = test_for_coverage(from_access, to_access,
                accesss_depth(from_access),
                accesss_depth(to_access),
                d_info->nest, d_info, str);
            assert(covers < 2);
            if (!covers && because(non_affine_red_bound)) {
                /* see if all 0's covers */
                dir_and_dist_info new_info = *d_info;
#if !defined SPEED
                char *str2 = dir_and_dist_as_str(d_info, nature,
                    from_access, to_access);
#else
                char *str2 = "Tiny must be compiled without -DSPEED for debug2 output";
#endif
                new_info.nest = d_info->nest;
                for (j = 1; j <= new_info.nest; j++)
                {
                    assert(dddirtest(d_info->direction, ddeq, j));
                    /* otherwise we would have no cover because 'didnt_test' */
                    dddirsetonly(new_info.direction, ddeq, j);
                    dddirsetonly(new_info.restraint, ddeq, j);
                    new_info.distanceKnown[j] = 1;
                    new_info.distance[j] = 0;
                }
                if (test_for_coverage(from_access, to_access,
                    accesss_depth(from_access),
                    accesss_depth(to_access),
                    new_info.nest, &new_info, str2))
                {
                    if (!(d_info->direction & ddrefined))
                        clone_dd_graph_node_for_refinement(d_info->dd_graph_node_to_be_cloned);
                    *d_info = new_info;
                    d_info->direction |= ddrefined;
                    covers = 2;
                }
            }
            if (covers)
            {
                d_info->direction |= ddcovers;
                if (covers != 2 && !skipping_all_tightening &&
                    (!skipping_o_a_tightening || nature == ddflow))
                {
                    tighten_cover(from_access, to_access, d_info, str);
                }
                accesss_cover_depth(to_access) = MAX(accesss_cover_depth(to_access), dd_carried_by(d_info->direction, d_info->nest) - 1);
            }
        }
        if ((nature == ddoutput || nature == ddanti) &&
            from_access != ExitNode && to_access != Entry)
        {
            int terminates, j;
            terminates = test_for_termination(from_access, to_access,
                accesss_depth(from_access),
                accesss_depth(to_access),
                d_info->nest, d_info, str);
            assert(terminates < 2);
            if (!terminates && because(non_affine_red_bound)) {
                /* see if all 0's terminates */
                dir_and_dist_info new_info = *d_info;
#if !defined SPEED
                char *str2 = dir_and_dist_as_str(d_info, nature, from_access, to_access);
#else
                char *str2 = "Tiny must be compiled without -DSPEED for debug2 output";
#endif
                new_info.nest = d_info->nest;
                for (j = 1; j <= new_info.nest; j++)
                {
                    assert(dddirtest(d_info->direction, ddeq, j));
                    /* otherwise we would have no cover because 'didnt_test' */
                    dddirsetonly(new_info.direction, ddeq, j);
                    dddirsetonly(new_info.restraint, ddeq, j);
                    new_info.distanceKnown[j] = 1;
                    new_info.distance[j] = 0;
                }
                if (test_for_termination(from_access, to_access,
                    accesss_depth(from_access),
                    accesss_depth(to_access),
                    new_info.nest, &new_info, str2))
                {
                    if (!(d_info->direction & ddrefined))
                        clone_dd_graph_node_for_refinement(d_info->dd_graph_node_to_be_cloned);
                    *d_info = new_info;
                    d_info->direction |= ddrefined;
                    terminates = 2;
                }
            }
            if (terminates)
            {
                d_info->direction |= ddterminates;
                if (terminates != 2 && !skipping_o_a_tightening &&
                    !skipping_all_tightening)
                {
                    tighten_terminator(from_access, to_access, d_info, str);
                }
                accesss_terminator_depth(from_access) = MAX(accesss_terminator_depth(from_access), dd_carried_by(d_info->direction, d_info->nest) - 1);
            }
        }

#if !defined NDEBUG
        d_info_inv(d_info);
#endif

        /* copy all the changes into the ddnode */
#if defined newTimeTrials
        if (storeResult)
            dir_and_dist_into_ddnode(d_info,
                d_info->dd_graph_node_to_be_cloned);
#else
        dir_and_dist_into_ddnode(d_info, d_info->dd_graph_node_to_be_cloned);
#endif
    }

#if defined newTimeTrials
    if (!storeResult)
        return;
    else
        stores++;
#endif
}

/* split a set of flow, anti, or output dependencies into
    pieces that are all forward in time

   if   we have a situation with an exposed 0+ followed
        by an exposed -,
   then filterValid will call itself recursively to split
        the 0+ into 0 and + (eliminating the 0...- case)
   else filterValid will store only one dependency

   these dependeces are passed to flag_and_store_dependence.
 */

static void
filterValid(ddnature nature, a_access from_access, a_access to_access,
    int commonNesting, dir_and_dist_info *d_info, int allEQallowed)
{
    int less_at, j;
    int forbidden;

    /*
     * For private variables:            -- vadik 11/05/92
     * dependencies can not be carried by loops-privatizers
     */
    if (from_access != Entry && from_access != ExitNode &&
        to_access != ExitNode && to_access != Entry &&
        access_private_var_p(from_access))
    {
        int PrivLev = access_private_var_level(from_access);
        assert(PrivLev <= commonNesting);
        for (j = 1; j <= PrivLev; j++) {
            dddirreset(d_info->direction, ddlt | ddgt, j);
            if (!dddirtest(d_info->direction, ddgt | ddlt | ddeq, j))
                return;
            dddirreset(d_info->restraint, ddlt | ddgt, j);
            d_info->distance[j] = 0;
            d_info->distanceKnown[j] = 1;
        }
    }

#if 0
    /*
     * Reduction dependences aren't forward or backward in time,
     * so they all are valid by default ??? -- vadik
     * However, we have to ignore (0,0,...,0) reduction dependences.
     */
    if (nature == ddreduce) {
        for (j = 1; j <= commonNesting; ++j) {
            if (dddirtest(d_info->direction, ddlt | ddgt, j))
                break;
        }
        if (j <= commonNesting || from_access != to_access) {
            flag_and_store_dependence(nature, from_access, to_access, d_info);
        }
        return;
    }
#endif

    /* remove all -'s before 1st + */
    for (j = 1; j <= commonNesting; ++j) {
        if (!dddirtest(d_info->direction, ddlt | ddeq, j))
            return;
        if (dddirtest(d_info->direction, ddgt, j)) {
            dddirreset(d_info->direction, ddgt, j);
            d_info_do_eq(d_info, j);
            dddirreset(d_info->restraint, ddgt, j);
        }
        if (dddirtest(d_info->direction, ddlt, j)) break;
    }

    /* check for all 0's or no common Nesting */
    less_at = j;
    if (less_at > commonNesting) {
        if (allEQallowed) {
            flag_and_store_dependence(nature, from_access, to_access, d_info);
        }
        return;
    }

    /* if we start with 0+ rather than just +, check for possible all 0's */

    if (dddirtest(d_info->direction, ddeq, less_at)) {
        for (j = less_at + 1;
            j <= commonNesting && !dddirtest(d_info->direction, ddlt | ddgt, j);
            j++);
        if (j <= commonNesting && !dddirtest(d_info->direction, ddlt | ddeq, j))
        {
            /* we have some 0's, a 0+, more 0's, then a - so, 0+ -> just + */
            dddirreset(d_info->direction, ddeq, less_at);
            dddirreset(d_info->restraint, ddeq, less_at);
        }
        else {
            /* we have some 0's, a 0+, more 0's,
               then either 0- or something with a + */

            forbidden = !allEQallowed;
            for (j = commonNesting; j >= less_at; j--) {
                forbidden = dddirtest(d_info->direction, ddgt, j) ||
                    (dddirtest(d_info->direction, ddeq, j) && forbidden);
                /* "forbidden" = some loop outside j must
                   force this dependence to go strictly forward in time */
            }

            if (forbidden) {
                /* split into leading 0 vs. leading + */
                dir_and_dist_info plus, zero;
                plus = zero = *d_info;
                dddirreset(plus.direction, ddeq, less_at);
                dddirreset(plus.restraint, ddeq, less_at);
                dddirreset(zero.direction, ddlt, less_at);
                dddirreset(zero.restraint, ddlt, less_at);
                zero.distance[less_at] = 0;
                zero.distanceKnown[less_at] = 1;
                filterValid(nature, from_access, to_access, commonNesting,
                    &plus, allEQallowed);
                filterValid(nature, from_access, to_access, commonNesting,
                    &zero, allEQallowed);
                return;
            }
        }
    }

    flag_and_store_dependence(nature, from_access, to_access, d_info);

    if (omegaPrintResult == 1) {
        fprintf(debug2, ">>>>>>>>>>>>>>>>>>>>>>>> (");
        for (j = 1; j <= commonNesting; j++) {
            if (dddirtest(d_info->restraint, ddeq, j)) fprintf(debug2, "0");
            if (dddirtest(d_info->restraint, ddlt, j)) fprintf(debug2, "+");
            if (dddirtest(d_info->restraint, ddgt, j)) fprintf(debug2, "-");
            if (j < commonNesting) fprintf(debug2, ",");
        }
        fprintf(debug2, ")\n");
        fprintf(debug2, "------------------------ (");
        for (j = 1; j <= commonNesting; j++) {
            if (dddirtest(d_info->direction, ddeq, j)) fprintf(debug2, "0");
            if (dddirtest(d_info->direction, ddlt, j)) fprintf(debug2, "+");
            if (dddirtest(d_info->direction, ddgt, j)) fprintf(debug2, "-");
            if (j < commonNesting) fprintf(debug2, ",");
        }
        fprintf(debug2, ")\n");
    }
}

static void dd_to_debug(dir_and_dist_info *d_info)
{
    int j;

    fprintf(debug2, "(");
    for (j = 1; j <= d_info->nest; j++) {
        if (d_info->distanceKnown[j])
            fprintf(debug2, "%d", d_info->distance[j]);
        else if (ddextract1(d_info->direction, j) == ddall)
            fprintf(debug2, "*");
        else {
            if (dddirtest(d_info->direction, ddeq, j)) fprintf(debug2, "0");
            if (dddirtest(d_info->direction, ddlt, j)) fprintf(debug2, "+");
            if (dddirtest(d_info->direction, ddgt, j)) fprintf(debug2, "-");
        }
        if (j < d_info->nest) fprintf(debug2, ",");
    }
    fprintf(debug2, ") restraint = (");
    for (j = 1; j <= d_info->nest; j++) {
        if (ddextract1(d_info->restraint, j) == ddall)
            fprintf(debug2, "*");
        else {
            if (dddirtest(d_info->restraint, ddeq, j)) fprintf(debug2, "0");
            if (dddirtest(d_info->restraint, ddlt, j)) fprintf(debug2, "+");
            if (dddirtest(d_info->restraint, ddgt, j)) fprintf(debug2, "-");
        }
        if (j < d_info->nest) fprintf(debug2, ",");
    }
    fprintf(debug2, ")");
}

/*
   call filterValid for the dependence from access1 to access2,
   and if they are distinct, for the dependence the other way.
 */

static void noteDependence(situation *sit, dir_and_dist_info *d_info)
{
    dddirection deq, dgt, dlt, req, rgt, rlt;
    dir_and_dist_info backward;
    int j;
    backward.dd_graph_node_to_be_cloned = 0;

    deq = ddfilter(d_info->direction, ddeq);
    dlt = ddfilter(d_info->direction, ddlt);
    dgt = ddfilter(d_info->direction, ddgt);
    req = ddfilter(d_info->restraint, ddeq);
    rlt = ddfilter(d_info->restraint, ddlt);
    rgt = ddfilter(d_info->restraint, ddgt);

    if (sit->access1 != sit->access2) {
        backward.direction = backward.restraint = 0;

        ddsetfilter(backward.direction, deq, ddeq);
        ddsetfilter(backward.direction, dlt, ddgt);
        ddsetfilter(backward.direction, dgt, ddlt);
        ddsetfilter(backward.restraint, req, ddeq);
        ddsetfilter(backward.restraint, rlt, ddgt);
        ddsetfilter(backward.restraint, rgt, ddlt);

        backward.nest = d_info->nest;
        for (j = 1; j <= sit->commonNesting; ++j) {
            backward.distanceKnown[j] = d_info->distanceKnown[j];
            if (backward.distanceKnown[j])
                backward.distance[j] = -d_info->distance[j];
        }
    }

    filterValid(sit->oitype, sit->access1, sit->access2,
        sit->commonNesting, d_info,
        access_lexically_preceeds(sit->access1, sit->access2));

    if (omegaPrintResult == 1) {
        fprintf(debug2, "%%%%%%%%%%%%%%%%%%%%%%%% ");
        dd_to_debug(d_info);
        fprintf(debug2, "\n");
    }

    if (sit->access1 != sit->access2) {
        filterValid(sit->iotype, sit->access2, sit->access1,
            sit->commonNesting, &backward,
            access_lexically_preceeds(sit->access2, sit->access1));

        if (omegaPrintResult == 1) {
            fprintf(debug2, "%%%%%%%% backward %%%%%% ");
            dd_to_debug(&backward);
            fprintf(debug2, "\n");
        }
    }
} /* noteDependence */

/* info used during construction */
typedef struct {
    int unknownDirection[maxCommonNest];
    int unknownDirections;
} unknowns;


/*
   process the omega test problem into dependence vectors
   if   dependencies are not coupled, just read them out.
   else break into cases for each possible dependence in (+,0,-)
        in each dimension by doing a recursive call
   each time a dependence vector is found, call noteDependence to store it
 */

static void
findDirectionVector(Problem * prob, situation *sit,
    dir_and_dist_info *d_info, unknowns *u_info)
{
    int i, j;
    int l, u, coupled;
    int l2, u2, best, score, bestScore;
    int unprotectThese[maxCommonNest];
    int numToUnprotect = 0;
    int simplificationNeeded = u_info->unknownDirections == 0;
    int initialUnknownDirections = u_info->unknownDirections;

    u2 = 2;
    l2 = -2;
    bestScore = 10000;

    best = -1;  /* keep compiler from complaining, allow later assertion */

    for (i = 0; i < u_info->unknownDirections; i++) {
        j = u_info->unknownDirection[i];
        d_info->distanceKnown[j] = 0;
        coupled = queryVariable(prob, j, &l, &u);
        if (l == u) {
            d_info->distanceKnown[j] = 1;
            d_info->distance[j] = l;
        }
        else {
            if (l > 1) l = 1;
            else if (l < -1) l = -1;
            if (u < -1) u = -1;
            else if (u > 1) u = 1;
        }
        if (!coupled || l == u) {
            dddirsetonly(d_info->direction, 0, j);
            if (l < 0)            dddirset(d_info->direction, ddgt, j);
            if (l <= 0 && 0 <= u) dddirset(d_info->direction, ddeq, j);
            if (0 < u)            dddirset(d_info->direction, ddlt, j);
            d_info_do_eq(d_info, j);
            unprotectThese[numToUnprotect++] = j;
            u_info->unknownDirection[i] =
                u_info->unknownDirection[--u_info->unknownDirections];
            i--;
            if (coupled) simplificationNeeded = 1;
        }
        else if (coupled && initialUnknownDirections == 1
            && prob->_nVars + prob->_numSUBs == 2
            && prob->_numEQs + prob->_numSUBs == 1)
        {
            dddirsetonly(d_info->direction,
                queryVariableSigns(prob, j,
                    ddlt, ddeq, ddgt,
                    negInfinity, posInfinity,
                    &(d_info->distanceKnown[j]),
                    &(d_info->distance[j])),
                j);
            d_info_do_eq(d_info, j);
            noteDependence(sit, d_info);
            return;
        }
        else {
            score = 2 * (u - l) + j;
            if (prob->_nVars > 1 && prob->forwardingAddress[j] > 0)
                score -= 3;
            if (score <= bestScore) {
                u2 = u;
                l2 = l;
                best = j;
                bestScore = score;
            }
        }
    }

    if (u_info->unknownDirections == 0) {
        prob->_safeVars = 0;
        prob->_numSUBs = 0;
        if (!simplificationNeeded || solve(prob, UNKNOWN))
            noteDependence(sit, d_info);
    }
    else {
        for (i = 0; i < numToUnprotect; i++) {
            j = unprotectThese[i];
            unprotectVariable(prob, j);
        }
        if (simplificationNeeded ||
            (u_info->unknownDirections == 1 && initialUnknownDirections > 1))
        {
            simplifyProblem(prob);
            findDirectionVector(prob, sit, d_info, u_info);
        }
        else {
            int s;
            int oldUnknownDirections;
            int oldUnknownDirection[maxCommonNest];

            if (u_info->unknownDirections == 2
                && prob->_nVars == 1
                && prob->_numSUBs == 1)
            {
                i = u_info->unknownDirection[0];
                j = u_info->unknownDirection[1];
                if (prob->forwardingAddress[i] != -1) {
                    int t;
                    t = i;
                    i = j;
                    j = t;
                }
                if (prob->forwardingAddress[i] == -1
                    && prob->forwardingAddress[j] == 1)
                {
                    int j1, j2, j3, i1, i2, i3;

                    j1 = ddlt;
                    i1 = queryVariableSigns(prob, i,
                        ddlt, ddeq, ddgt, 1, posInfinity,
                        &(d_info->distanceKnown[i]),
                        &(d_info->distance[i]));
                    if (d_info->distanceKnown[i]) {
                        dddirsetonly(d_info->direction, i1, i);
                        dddirsetonly(d_info->direction, j1, j);
                        /* dddirsetonly(d_info->restraint, i1, i);not needed */
                        dddirsetonly(d_info->restraint, j1, j);
                        noteDependence(sit, d_info);
                        i1 = 0;
                    }
                    j2 = ddeq;
                    i2 = queryVariableSigns(prob, i, ddlt, ddeq, ddgt, 0, 0,
                        &(d_info->distanceKnown[i]),
                        &(d_info->distance[i]));
                    if (d_info->distanceKnown[i]) {
                        int oldDistj = d_info->distance[j];
                        bool oldDistKj = d_info->distanceKnown[j];

                        dddirsetonly(d_info->direction, i2, i);
                        dddirsetonly(d_info->direction, j2, j);
                        assert(j2 == ddeq);
                        d_info->distanceKnown[j] = 1;
                        d_info->distance[j] = 0;

                        /* dddirsetonly(d_info->restraint, i2, i);not needed */
                        dddirsetonly(d_info->restraint, j2, j);
                        noteDependence(sit, d_info);
                        i2 = 0;
                        d_info->distanceKnown[j] = oldDistKj;
                        d_info->distance[j] = oldDistj;
                    }

                    j3 = ddgt;
                    i3 = queryVariableSigns(prob, i,
                        ddlt, ddeq, ddgt, negInfinity, -1,
                        &(d_info->distanceKnown[i]),
                        &(d_info->distance[i]));
                    if (d_info->distanceKnown[i]) {
                        dddirsetonly(d_info->direction, i3, i);
                        dddirsetonly(d_info->direction, j3, j);
                        /* dddirsetonly(d_info->restraint, i3, i);not needed */
                        dddirsetonly(d_info->restraint, j3, j);
                        noteDependence(sit, d_info);
                        i3 = 0;
                    }

                    d_info->distanceKnown[i] = 0;
                    if (i3 == i2) {
                        j2 |= j3;
                        i3 = 0;
                    }
                    if (i2 == i1) {
                        j1 |= j2;
                        i2 = 0;
                    }
                    if (i3 == i1) {
                        j1 |= j3;
                        i3 = 0;
                    }
                    if (i1) {
                        bool oldDisti = d_info->distance[i];
                        bool oldDistKi = d_info->distanceKnown[i];
                        bool oldDistj = d_info->distance[j];
                        bool oldDistKj = d_info->distanceKnown[j];
                        dddirsetonly(d_info->direction, i1, i);
                        dddirsetonly(d_info->direction, j1, j);
                        /* dddirsetonly(d_info->restraint, i1, i);not needed */
                        dddirsetonly(d_info->restraint, j1, j);
                        d_info_do_eq(d_info, i);
                        d_info_do_eq(d_info, j);
                        noteDependence(sit, d_info);
                        d_info->distanceKnown[i] = oldDistKi;
                        if (oldDistKi) d_info->distance[i] = oldDisti;
                        d_info->distanceKnown[j] = oldDistKj;
                        if (oldDistKj) d_info->distance[j] = oldDistj;
                    }
                    if (i2) {
                        bool oldDisti = d_info->distance[i];
                        bool oldDistKi = d_info->distanceKnown[i];
                        bool oldDistj = d_info->distance[j];
                        bool oldDistKj = d_info->distanceKnown[j];
                        dddirsetonly(d_info->direction, i2, i);
                        dddirsetonly(d_info->direction, j2, j);
                        /* dddirsetonly(d_info->restraint, i2, i);not needed */
                        dddirsetonly(d_info->restraint, j2, j);
                        d_info_do_eq(d_info, i);
                        d_info_do_eq(d_info, j);
                        noteDependence(sit, d_info);
                        d_info->distanceKnown[i] = oldDistKi;
                        if (oldDistKi) d_info->distance[i] = oldDisti;
                        d_info->distanceKnown[j] = oldDistKj;
                        if (oldDistKj) d_info->distance[j] = oldDistj;
                    }
                    if (i3) {
                        bool oldDisti = d_info->distance[i];
                        bool oldDistKi = d_info->distanceKnown[i];
                        bool oldDistj = d_info->distance[j];
                        bool oldDistKj = d_info->distanceKnown[j];
                        dddirsetonly(d_info->direction, i3, i);
                        dddirsetonly(d_info->direction, j3, j);
                        /* dddirsetonly(d_info->restraint, i3, i);not needed */
                        dddirsetonly(d_info->restraint, j3, j);
                        d_info_do_eq(d_info, i);
                        d_info_do_eq(d_info, j);
                        noteDependence(sit, d_info);
                        d_info->distanceKnown[i] = oldDistKi;
                        if (oldDistKi) d_info->distance[i] = oldDisti;
                        d_info->distanceKnown[j] = oldDistKj;
                        if (oldDistKj) d_info->distance[j] = oldDistj;
                    }
                    return;
                }
            }

            assert(best >= 0);
            if (omegaPrintResult == 1)
                fprintf(debug2,
                    "doing recursive analysis of %d..%d on var %s (#%d)\n",
                    l2, u2,
                    (*prob->_getVarName)(best, prob->_getVarNameArgs), best);
            j = best;
            i = 0;
            while (u_info->unknownDirection[i] != j)
                i++;
            u_info->unknownDirection[i] =
                u_info->unknownDirection[--u_info->unknownDirections];

            oldUnknownDirections = u_info->unknownDirections;
            for (i = 0; i < u_info->unknownDirections; i++)
                oldUnknownDirection[i] = u_info->unknownDirection[i];

            for (s = l2; s <= u2; s++) {
                Problem tmpProblem;
                dddirection oldDirection = d_info->direction;
                dddirection oldRestraint = d_info->restraint;
                int oldDistj = d_info->distance[j];
                int oldDistKj = d_info->distanceKnown[j];

                problemcpy(&tmpProblem, prob);
                if (omegaPrintResult == 1)
                    fprintf(debug2, "considering sign =  %d of %s (%d)\n", s,
                    (*prob->_getVarName)(best, prob->_getVarNameArgs),
                        best);

                if (s == 0) {
                    d_info->distance[j] = 0;
                    d_info->distanceKnown[j] = 1;
                }
                else {
                    d_info->distanceKnown[j] = 0;
                }

                dddirsetonly(d_info->direction, dd_convert[s + 1], j);
                dddirsetonly(d_info->restraint, dd_convert[s + 1], j);
                d_info_inv(d_info);

                if (constrainVariableSign(&tmpProblem, black, j, s))
                    findDirectionVector(&tmpProblem, sit, d_info, u_info);

                if (s < u2) {
                    d_info->direction = oldDirection;
                    d_info->restraint = oldRestraint;
                    d_info->distance[j] = oldDistj;
                    d_info->distanceKnown[j] = oldDistKj;

                    d_info->dd_graph_node_to_be_cloned = 0;

                    u_info->unknownDirections = oldUnknownDirections;
                    for (i = 0; i < u_info->unknownDirections; i++)
                        u_info->unknownDirection[i] = oldUnknownDirection[i];
                }
            }
        }
    }
} /* findDirectionVector */


/*
   calculateDDVectors just calls findDirectionVector now.

   The arrays dddir[] and dddist[] need to have at least
   maxnest+1 spaces allocated
 */

extern int nonConvex;


void calculateDDVectors(Problem *problemPtr, a_access access1, a_access access2,
    ddnature oitype, ddnature iotype,
    uint nest1, uint nest2, uint bnest, uint nonloops)
{
    int i;
    situation sit;
    unknowns u_info;
    dir_and_dist_info d_info;
    d_info.dd_graph_node_to_be_cloned = 0;

    d_info.nest = bnest;

    u_info.unknownDirections = bnest;
    for (i = 0; i < u_info.unknownDirections; i++)
        u_info.unknownDirection[i] = i + 1;

#if defined newTimeTrials
    if (storeResult) {
        int e;
        int reducable = ((problemPtr->_safeVars) == 1);
        int coupledSubstitutions = 0;
        int coupled = 0;
        int nonUnary = 0;

        for (e = problemPtr->_numSUBs - 1; e >= 0; e--)
            if (problemPtr->_SUBs[e].coef[0] != 0)
                reducable = 0;

        for (e = problemPtr->_numGEQs - 1; e >= 0; e--) {
            if (!singleVarGEQ(problemPtr->_GEQs[e], problemPtr->_nVars))
                coupled = 1;

            for (i = problemPtr->_nVars; i > 0; i--)
                if (problemPtr->_GEQs[e].coef[i] > 1
                    || problemPtr->_GEQs[e].coef[i] < -1)
                    nonUnary = 1;
        };

        for (e = problemPtr->_numSUBs - 1; e >= 0; e--) {
            for (i = problemPtr->_nVars; i > 0; i--)
                if (problemPtr->_SUBs[e].coef[i] != 0)
                    coupledSubstitutions = 1;
        };

        ddCategory[0] = 0;
        if (reducable)
            strncat(ddCategory, "r ", TINYBUFSIZ);
        if (coupledSubstitutions)
            strncat(ddCategory, "s ", TINYBUFSIZ);
        if (coupled)
            strncat(ddCategory, "c ", TINYBUFSIZ);
        if (nonUnary)
            strncat(ddCategory, "u ", TINYBUFSIZ);
        if (nonConvex)
            strncat(ddCategory, "v ", TINYBUFSIZ);
    }
#endif
    sit.access1 = access1;
    sit.access2 = access2;
    sit.oitype = oitype;
    sit.iotype = iotype;
    sit.nest1 = nest1;
    sit.nest2 = nest2;
    sit.commonNesting = bnest;

    d_info.direction = 0;
    d_info.restraint = -1;
    /* d_info built by findDirectionVector */
    findDirectionVector(problemPtr, &sit, &d_info, &u_info);
}
