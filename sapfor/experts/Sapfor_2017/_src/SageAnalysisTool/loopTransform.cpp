#include <stdio.h>
#include "sage++user.h"
#include "definesValues.h"
#include "set.h"
#include "definitionSet.h"
#include "inducVar.h"
#include "depGraph.h"
#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif


///////////////////////////////////////////////////////////////////////////////////////
// some global declarations
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Loop Transformation Sets. (the validity checkings for the transformations
// are in the depGraph method.
///////////////////////////////////////////////////////////////////////////////////////

//
// b is the outer loopm 
// permut specify the loop permutations
// the n outermost loops must be perfectly nested
// permut start at 0; Example
// do i = 0
//    do j = 8
//      do k = 1
//       ....
// permut = [2,1,0]
// gives
// do  k = 1
//    do j = 8
//      do i = 0
//       ....
//

int loopInterchange(SgStatement *b, int *permut, int n)
{
    SgSymbol *tab_symb[MAXNESTEDLOOP];
    SgExpression *tab_bf[MAXNESTEDLOOP];
    SgExpression * tab_bi[MAXNESTEDLOOP];
    SgExpression * tab_step[MAXNESTEDLOOP];
    SgForStmt *loop, *tloop;
    int i;
    if (!(loop = isSgForStmt(b)))
        return 0;

    if (n > loop->isPerfectLoopNest())
    {
        Message("Interchange loop error, loops are not perfectly nested", loop->lineNumber());
        return 0;
    }
    tloop = loop;
    for (i = 0; (i < n); i++)
    {
        tab_symb[i] = tloop->symbol();
        tab_bf[i] = tloop->start();
        tab_bi[i] = tloop->end();
        tab_step[i] = tloop->step();
        tloop = isSgForStmt(tloop->getNextLoop());
    }

    tloop = loop;
    for (i = 0; (i < n); i++)
    {
        if (tab_symb[permut[i]])
            tloop->setSymbol(*tab_symb[permut[i]]);
        if (tab_bf[permut[i]])
            tloop->setStart(*tab_bf[permut[i]]);
        if (tab_bi[permut[i]])
            tloop->setEnd(*tab_bi[permut[i]]);
        if (tab_step[permut[i]])
            tloop->setStep(*tab_step[permut[i]]);
        tloop = isSgForStmt(tloop->getNextLoop());
    }
    return 1;
}


//
// Tile a loop.
// assumed to be perfectly nested.
// size is NO_STEP we do not want it to be tiled
//

int tileLoops(SgStatement *func, SgStatement *b, int *size, int nb)
{
    int i, j;
    SgSymbol *tab_symb[MAXNESTEDLOOP];
    SgStatement *body, *ptstmt;
    SgForStmt *internal_loop, *temp, *last_loop;
    SgForStmt *loop, *temloo;
    SgExpression *borne_inf[MAXNESTEDLOOP];
    SgExpression *borne_sup[MAXNESTEDLOOP];
    SgExpression *step[MAXNESTEDLOOP];
    SgType *typint;
    SgSymbol  *min_fonc;
    char strfoname[256];

    if (!(loop = isSgForStmt(b)) || !func)
        return 0;
    if (nb > loop->isPerfectLoopNest())
    {
        Message("loop Tilling error, loops are not perfectly nested", loop->lineNumber());
        return 0;
    }
    if (nb == 0) return 0;

    if (nb >= MAXNESTEDLOOP)
    {
        Message("Too many nested level", b->lineNumber());
        return 0;
    }
    for (i = 0; i < MAXNESTEDLOOP; i++)
    {
        tab_symb[i] = NULL;
        borne_inf[i] = NULL;
        borne_sup[i] = NULL;
        step[i] = NULL;
    }
    last_loop = loop;
    for (i = 0; i < nb; i++)
    {
        if (size[i] != NO_STEP)
        {
            if (last_loop->step())
            {
                Message("Cannot tile loop, there is already a step", last_loop->lineNumber());
                return 0;
            }
        }
        last_loop = isSgForStmt(last_loop->getNextLoop());
    }
    // Get integer type;
    typint = SgTypeInt();
    // get the indexes of the loops;
    temloo = loop;
    for (i = 0; i < nb; i++)
    {
        tab_symb[i] = temloo->symbol();
        internal_loop = temloo;
        temloo = isSgForStmt(temloo->getNextLoop());
    }
    if (!internal_loop)
    {
        Message("Internal loop not found", loop->lineNumber());
        return 0;
    }
    // generate the new symbol and declare them
    for (i = 0; i < nb; i++)
    {
        sprintf(strfoname, "iT%d_%d", loop->id(), i);
        tab_symb[i + nb] = new SgVariableSymb(strfoname);
#ifdef __SPF
        addToCollection(__LINE__, __FILE__, tab_symb[i + nb], 1);
#endif
        tab_symb[i + nb]->declareTheSymbol(*func);
    }
    last_loop = loop;
    for (i = 0; i < nb; i++)
    {
        if (size[i] != NO_STEP)
        {
            SgValueExp *tmp = (new SgValueExp(size[i] + 1));
            last_loop->setStep(*tmp);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, tmp, 1);
#endif
        }
        last_loop = isSgForStmt(last_loop->getNextLoop());
    }

    // create a min function; 
    min_fonc = new SgSymbol(FUNCTION_NAME, "min", *typint, *(loop->controlParent()));
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, min_fonc, 1);
#endif
    // creation of the bound expressions;
    last_loop = loop;
    for (i = 0; i < nb; i++)
    {
        if (size[i] != NO_STEP)
        {
            SgFunctionCallExp *cexp;
            borne_inf[i + nb] = new SgValueExp(0);
            cexp = new SgFunctionCallExp(*min_fonc);
            borne_sup[i + nb] = cexp;

            SgValueExp *tmp = (new SgValueExp(size[i]));
            SgVarRefExp *tmp1 = (new SgVarRefExp(*tab_symb[i]));
            cexp->addArg(((last_loop->end())->copy()) - *tmp1);
            cexp->addArg(*tmp);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, borne_inf[i + nb], 1);
            addToCollection(__LINE__, __FILE__, cexp, 1);
            addToCollection(__LINE__, __FILE__, tmp, 1);
            addToCollection(__LINE__, __FILE__, tmp1, 1);
#endif
        }
        else
        {
            borne_inf[i + nb] = new SgValueExp(1);
            borne_sup[i + nb] = &((last_loop->end())->copy());

#ifdef __SPF
            addToCollection(__LINE__, __FILE__, borne_inf[i + nb], 1);
#endif
        }
        step[i + nb] = NULL;
        last_loop = isSgForStmt(last_loop->getNextLoop());
    }
    // remove the loop body;
    // update the steps;
    body = internal_loop->extractStmtBody();
    // upper bound for NO_STEP loops
    last_loop = loop;
    for (i = 0; i < nb; i++)
    {
        if (size[i] == NO_STEP)
        {
            SgValueExp *tmp = (new SgValueExp(1));
            last_loop->setEnd(*tmp);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, tmp, 1);
#endif
        }
        last_loop = isSgForStmt(last_loop->getNextLoop());
    }
    // create the new loop;
    last_loop = internal_loop;
    for (i = 0; i < nb; i++)
    {
        loop = new SgForStmt(tab_symb[i + nb], borne_inf[i + nb], borne_sup[i + nb], step[i + nb], NULL);
#ifdef __SPF
        addToCollection(__LINE__, __FILE__, loop, 1);
#endif
        last_loop->insertStmtAfter(*loop, *last_loop);
        last_loop = loop;
    }

    // update the loop body;
    if (!body || !last_loop)
    {
        Message("The loop may not have a body or internal error", 0);
        return 0;
    }
    last_loop->insertStmtAfter(*body, *last_loop);

    for (j = 0; j < last_loop->numberOfChildrenList1(); j++)
    {
        ptstmt = last_loop->childList1(j);
        if (ptstmt)
        {
            for (i = 0; i < nb; i++)
            {
                if (size[i] != NO_STEP)
                {
                    SgVarRefExp *tmp = (new SgVarRefExp(*tab_symb[i]));
                    SgVarRefExp *tmp1 = (new SgVarRefExp(*tab_symb[i + nb]));
                    ptstmt->replaceSymbByExp(*tab_symb[i], *tmp + *tmp1);
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, tmp, 1);
                    addToCollection(__LINE__, __FILE__, tmp1, 1);
#endif
                }
                else
                {
                    SgVarRefExp *tmp = (new SgVarRefExp(*tab_symb[i]));
                    ptstmt->replaceSymbByExp(*tab_symb[i], *tmp);
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, tmp, 1);
#endif
                }
            }
        }
    }
    return 1;
}

//
// distribute the loops according to the 
// table of SCC.
// for instance consider the following loop
//  
//      do i= 1,100
//[1]      x  =  2
//[2]      do j= 1,100
//           D(j+i) = A(i,j)
//           D(j+i) = A(i,j)
//         enddo
//[3]      x  =  2 
//      enddo
// and the following content of the 
// [[1,3],2] scc table index
//

int distributeLoopSCC(SgStatement *b, int *sccTable, int leadingdim, int numSCC)
{
    int i, j;
    SgStatement *last, **sccloop, **sccextracted, *ptstm;
    SgStatement *previous, *cp, *copl;
    SgForStmt *loop;
    int nbstat;

    if (!(loop = isSgForStmt(b)) || !sccTable)
        return 0;

    nbstat = loop->numberOfChildrenList1() - 1; // does not remove the controlend;
    sccloop = new SgStatement *[numSCC];
    sccextracted = new SgStatement *[nbstat];
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, sccloop, 2);
    addToCollection(__LINE__, __FILE__, sccextracted, 2);
#endif
    for (j = 0; j < nbstat; j++)
    {
        ptstm = loop->childList1(j);
        sccextracted[j] = ptstm;
    }
    for (j = 0; j < nbstat; j++)
    {
        if (sccextracted[j])
            sccextracted[j]->extractStmt();
    }
    // now creates the loop;
    previous = loop->nodeBefore();
    cp = loop->controlParent();
    loop->extractStmt();
    copl = &(loop->copy());
    previous->insertStmtAfter(*loop, *cp);
    sccloop[0] = loop;
    last = loop->lastNodeOfStmt();
    // need to extractloop before doing the copy;

    for (j = 1; j < numSCC; j++)
    {
        if (j == numSCC - 1)
            sccloop[j] = copl;
        else
            sccloop[j] = &(copl->copy());
        last->insertStmtAfter(*(sccloop[j]), *cp);
        last = sccloop[j]->lastNodeOfStmt();
    }

    for (j = 0; j < numSCC; j++)
    {
        for (i = leadingdim - 1; i >= 0; i--)
        {
            // insert in the right body the statement;
            // go revserse order; simpler;
            if (sccTable[j*leadingdim + i])
                if (sccextracted[sccTable[j*leadingdim + i] - 1])
                    sccloop[j]->insertStmtAfter(*sccextracted[sccTable[j*leadingdim + i] - 1], *sccloop[j]);
        }
    }

#ifdef __SPF
    removeFromCollection(sccloop);
    removeFromCollection(sccextracted);
#endif
    delete []sccloop;
    delete []sccextracted;
    return 1;
}


//
// Takes two loops and fusion the bodies
//

int loopFusion(SgStatement *loop1, SgStatement *loop2)
{
    SgForStmt *doloop1;
    SgForStmt *doloop2;
    SgStatement *body, *last;

    if (!(doloop1 = isSgForStmt(loop1)))
        return 0;
    if (!(doloop2 = isSgForStmt(loop2)))
        return 0;

    if (!doloop1->symbol())
        return 0;

    SgVarRefExp *tmp = (new SgVarRefExp(*doloop1->symbol()));
    doloop2->replaceSymbByExp(*doloop2->symbol(), *tmp);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, tmp, 1);
#endif
    body = doloop2->extractStmtBody();
    if (!body)
        return 0;
    last = doloop1->lastNodeOfStmt();
    if (!last)
        return 0;
    last = last->nodeBefore();
    if (!last)
        return 0;
    last->insertStmtAfter(*body, *doloop1);
    doloop2->extractStmt();
    return 1;
}




