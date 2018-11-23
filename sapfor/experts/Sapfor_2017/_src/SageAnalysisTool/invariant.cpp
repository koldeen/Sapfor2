#include <stdio.h>
#include <malloc.h>
#include "sage++user.h"
#include "definesValues.h"
#include "set.h"
#include "definitionSet.h"

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
#endif

extern Set *genSet[MAXNODE];
extern Set *killSet[MAXNODE];
extern Set *inSet[MAXNODE];
extern Set *outSet[MAXNODE];

//
// used in compute loop invariant
//

int stmtEqual(void *e1, void *e2)
{
    SgStatement *ex1, *ex2;
    if (!e1 && !e2)
        return 1;
    if (!e1 || !e2)
        return 0;

    ex1 = (SgStatement *)e1;
    ex2 = (SgStatement *)e2;

    if (ex1 != ex2)
        return 0;
    else
        return 1;
}

void stmtPrint(void *e1)
{
    SgStatement *ex1;
    if (!e1)
        return;

    ex1 = (SgStatement *)e1;
    printf("statement at line %d:\n", ex1->lineNumber());
    ex1->unparsestdout();
}



void exprPrint(void *e1)
{
    SgExpression *ex1;
    if (!e1)
        return;
    ex1 = (SgExpression *)e1;
    ex1->unparsestdout();
    printf("\n");
}

//
//function to Compute Loop Invariant Computation
// assume Reaching definition has been done
// and also the used and defined for each statment has also been computed
//

Set *loopInvariantStmt(SgStatement *func, SgStatement *stmt)
{
    SgStatement *last, *first, *defreach, *temp, *cp;
    SgForStmt *loop;
    Set *invariant, *reachdef;
    SgExpression *use, *pt, *usevar, *expr;
    int change, id, inloop, inv, step;
    PT_ELSET     el;
    int i;
    if (!stmt || !func)
        return NULL;

    if (!(loop = isSgForStmt(stmt)))
        return NULL;

    last = stmt->lastNodeOfStmt();
    invariant = new Set(stmtEqual, NULL, stmtPrint);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, invariant, 1);
#endif
    change = 1;
    step = 0;
    while (change)
    {
        change = 0;
        step++;
        for (temp = stmt->lexNext(); temp; temp = temp->lexNext())
        {
            // only if assgn_stat...;
            if (!isSgAssignStmt(temp))
            {
                if (temp == last)
                    break;
                else
                    continue;
            }
            id = temp->id();
            use = (SgExpression *)temp->attributeValue(0, USEDLIST_ATTRIBUTE);
            //Used[id];
            reachdef = inSet[id];
            // look at all the use of ;
            inv = 1;
            for (pt = use; pt && (inv == 1); pt = pt->rhs())
            {
                usevar = pt->lhs();
                if (usevar)
                {// look at if the definition is the reaching set;
                    for (i = 0; i < reachdef->size(); i++)
                    {
                        el = (PT_ELSET)reachdef->getElement(i);
                        if (el)
                        {
                            defreach = el->stmt;
                            expr = el->expr;
                            if (expr)
                            {
                                if (expr->symbol() && usevar->symbol() &&
                                    (expr->symbol() == usevar->symbol()))
                                {
                                    // we have a definition of the variable;
                                    if (!invariant->isInSet((void *)defreach))
                                    {
                                        // look at if in the loop body;
                                        inloop = 0;
                                        cp = defreach;
                                        while (cp)
                                        {
                                            if (cp == stmt)
                                            {
                                                inloop = 1;
                                                break;
                                            }
                                            if ((cp->variant() == GLOBAL) || (cp == func))
                                            {
                                                inloop = 0;
                                                break;
                                            }
                                            cp = cp->controlParent();
                                        }
                                        if (inloop)
                                        {
                                            inv = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (inv && !invariant->isInSet((void *)temp) && (step < MAXITDATAFLOW))
            {
                invariant->addElement((void *)temp);
                change = 1;
            }
            if (step >= MAXITDATAFLOW)
                Message("invariant computation is Looping", 0);
            if (temp == last)
                break;
        }
    }
    return  invariant;
}

