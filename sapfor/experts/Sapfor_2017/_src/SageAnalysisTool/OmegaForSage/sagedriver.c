/* sagedriver.c,v 1.2 1994/07/05 15:34:07 fbodin Exp */

/*
   Driver routine for dependence testing with the omega test.

   A different driver is used for several reasons:
    - we use coverage information to decide whether or not to check for
      a flow dependence
    - we don't want the funky values for the loop nesting
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define DEBUG 0
 
#include "include/portable.h"
#include "include/ip.h"
#include "include/affine.h"  /* for an assertion about node_is_affine */
#include "include/lang-interf.h"

#define GLOB 
#include "include/flags.h"

/* to be define later */
affine_expr not_affine = { -1, { 0 }, 0 };

extern int toBeCalledByOmegaTest(int tdep, int kdep, int *dist, int *kdist, int le, int from, int to);
/*
 * Do closing procedures
 */

extern void ExitFromOmegaTest(const int c);
void Exit(int c) 
{
    switch (c) {
    case 0:
        break;
    case 1:
        fprintf(stderr, "Exit apparently due to user error (exit code 1)\n");
        break;
    case 2:
    case -2:
        fprintf(stderr, "Exit apparently due to system limitation or error (exit code %d)\n", c);
        break;
    default:
        fprintf(stderr, "Something really bad happened (exit code %d)\n", c);
        break;
    }

    ExitFromOmegaTest(c);
}

/*
 * Assertion failed
 */
void ErrAssert(char *t) {
    if (Argv)
        fprintf(stderr, "\n%s: %s\n", &Argv[0][0], t);
    else
        fprintf(stderr, " %s\n", t);
    Exit(-2);
}

int dd_carried_by(dddirection dv, int length)
{
    int depth;

    for (depth = 1; (depth <= length && ddextract1(dv, depth) == ddeq); depth++)
        ;

    /* dd dirs [1..depth-1] are 0 */
    return depth;
}

int leading_zeros(dddirection dv, int length)
{
    int depth;

    for (depth = 1; (depth <= length && ddextract1(dv, depth) == ddeq); depth++)
        ;

    /* dd dirs [1..depth-1] are 0 */
    return depth - 1;
}


void append_dd_flags(char *line, dddirection dv)
{
    if (dv & ddkilled ||
        dv & ddisCovered || dv & ddisTerminated || dv & ddisRefined ||
        dv & ddrefined || dv & ddcovers || dv & ddterminates ||
        dv & ddzappable || dv & ddzappableWC)
    {
        strcat(line, " [");
        if (dv & ddcovers)     strcat(line, "C");
        if (dv & ddterminates) strcat(line, "T");
        if (dv & ddrefined)    strcat(line, "R");
        if (!(dv & ddcovers) &&
            !(dv & ddterminates) &&
            !(dv & ddrefined)) strcat(line, " ");

        if (dv & ddkilled)    strcat(line, "k");
        if (dv & ddisCovered) strcat(line, "c");
        if (dv & ddisTerminated) strcat(line, "t");
        if (dv & ddisRefined)   strcat(line, "r");

        if (dv & ddzappable)  strcat(line, "Z");
        if (dv & ddzappableWC)  strcat(line, "?");

        strcat(line, "]");
    }
}



/* some temporary definition of functions, to be modified later */
void ddnode_to_dir_and_dist(dd_current a, dir_and_dist_info *b)
{
    printf(" Calling ddnode_to_dir_and_dist\n");
}

/* coming from the sage part */
#define MAXNESTEDLOOP 100
#define DEPZERO 1
#define DEPGREATER 2
#define DEPLESS 4
#define WRONGDEP     0
#define ARRAYDEP     1
#define PRIVATEDEP   2
#define REDUCTIONDEP 3
#define SCALARDEP    4

void store_dependence(ddnature nature, a_access from_access, a_access to_access, dir_and_dist_info  *d_info)
{
    int i;
    int tdep;
    int kdep;
    int dist[MAXNESTEDLOOP];
    int kdist[MAXNESTEDLOOP];

    tdep = ARRAYDEP;
    if (d_info)
    {
        switch (nature)
        {
        case ddflow: 
            if (DEBUG)
                printf("Omega test found a FLOW dependence: (");
            kdep = ddflow;
            break;
        case ddanti: 
            if (DEBUG) 
                printf("Omega test found a ANTI dependence: (");
            kdep = ddanti;
            break;
        case ddoutput: 
            if (DEBUG)  
                printf("Omega test found a OUTPUT dependence: (");
            kdep = ddoutput;
            break;
        case ddreduce: 
            if (DEBUG)
                printf("Omega test found a REDUCE dependence: (");
            kdep = ddreduce;
            break;
        default:
            printf("Omega test found an UNKNOWN dependence: (");
            kdep = ddflow;
            tdep = WRONGDEP;
            break;
        }

        for (i = 1; i <= d_info->nest; i++)
        {
            if (d_info->distanceKnown[i])
            {
                if (DEBUG)  
                    printf("%d", d_info->distance[i]);
                kdist[i] = DEPZERO;
                dist[i] = d_info->distance[i];
            }
            else
            {
                kdist[i] = 0;
                dist[i] = 0;
                if (dddirtest(d_info->direction, ddeq, i))
                {
                    dist[i] = dist[i] + 1; /* temporary */
                    if (DEBUG)
                        printf("0");
                }
                if (dddirtest(d_info->direction, ddlt, i))
                {
                    dist[i] = dist[i] + DEPGREATER; /* temporary */
                    if (DEBUG)
                        printf("+");
                }
                if (dddirtest(d_info->direction, ddgt, i))
                {
                    dist[i] = dist[i] + DEPLESS; /* temporary */
                    if (DEBUG) 
                        printf("-");
                }
            }
            if (i < d_info->nest)  
                if (DEBUG) 
                    printf(", ");
        }
        if (DEBUG) 
            printf(")\n");  /*      if (from_access->lexord > to_access->lexord)*/
        toBeCalledByOmegaTest(tdep, kdep, dist, kdist, d_info->nest, from_access->idforsage, to_access->idforsage);
        /*else
           toBeCalledByOmegaTest(tdep,kdep,dist,kdist,d_info->nest,-1);*/
    }
    else
    {
        if (DEBUG)
            printf("Omega Test Found no Dependence\n");
    }
}


void dir_and_dist_into_ddnode(const dir_and_dist_info *ddi, dd_current b)
{
    /*  printf(" Calling  dir_and_dist_into_ddnode\n");*/
}

void Message_Add(char *str)
{
    printf("Message_Add %s\n", str);
}

void clone_dd_graph_node_for_refinement(void *dd_graph_node_to_be_cloned)
{
    /*  printf(" Calling  clone_dd_graph_node_for_refinement\n");*/
}


void SetOmegaDebug()
{
    extern FILE *debug2;
    debugLevel = 3;
    setOutputFile(stdout);
    omegaPrintResult = 1;
    debug2 = stdout;
}

void SetSTuff()
{
    extern FILE *debug2;
    /*  debugLevel = 3;
      setOutputFile(stdout);
      omegaPrintResult = 1;
      debug2 = stdout; */
    initializeOmega();
}


int access_is_in_then_or_else_of(a_access A, context_iterator C)
{
    context_iterator it1, it2;

    if (!C || !A)
        return 0;

    it1 = A->context;
    it2 = C;
    if (!cont_i_cur_loop_p(it2))
        return 0;

    while (!cont_i_done(it1))
    {
        if (!cont_i_cur_loop_p(it1))
        {
            if (cont_i_cur_if(it1)->ident == cont_i_cur_if(it2)->ident)
                return 1;
        }
        cont_i_next(it1);
    }

    return 0;
}
