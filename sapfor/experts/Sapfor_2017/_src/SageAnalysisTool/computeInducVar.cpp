#include <stdio.h>
#include <malloc.h>
#include "sage++user.h"
#include "definesValues.h"
#include "set.h"
#include "definitionSet.h"
#include "inducVar.h"

extern Set *genSet[MAXNODE];
extern Set *killSet[MAXNODE];
extern Set *inSet[MAXNODE];
extern Set *outSet[MAXNODE];

#ifdef _WIN32
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif
//
// Here we compute the induction variables for a loop
// this use the result of recheing analysis and invariant computation in loop.
// we use as element of sets the following structure.
//

//
// Set Operation
//
int inducVarEqual(void *e1, void *e2)
{
    SgExpression *ex1, *ex2;
    SgSymbol     *s1, *s2;
    PT_INDUCVAR     el1, el2;
    if (!e1 && !e2)
        return 1;
    if (!e1 || !e2)
        return 0;

    el1 = (PT_INDUCVAR)e1;
    el2 = (PT_INDUCVAR)e2;
    if (el1->level != el2->level)
        return 0;
    if (el1->include != el2->include)
        return 0;
    if (el1->loopnum != el2->loopnum)
        return 0;
    if (el1->constante != el2->constante)
        return 0;

    ex1 = el1->var;
    ex2 = el2->var;

    if ((s1 = ex1->symbol()) && (s2 = ex2->symbol()))
    {
        if (s1 == s2)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}


void inducVarPrint(void *e1)
{
    SgExpression *ex1;
    PT_INDUCVAR     el1;
    if (!e1)
        return;
    el1 = (PT_INDUCVAR)e1;
    ex1 = el1->var;
    if (el1->constante)
        printf("Constante ");
    if (ex1->symbol())
        printf("%s (%d-%d-%d)", ex1->symbol()->identifier(), el1->level, el1->loopnum, el1->include);
    else
        ex1->unparsestdout();
    printf(" = ");
    ex1 = el1->lbound;
    if (ex1)
        ex1->unparsestdout();
    printf(",");
    ex1 = el1->ubound;
    if (ex1)
        ex1->unparsestdout();
    printf(",");
    ex1 = el1->stride;
    if (ex1)
        ex1->unparsestdout();
    printf("\n");
}


//
// Indicate if a variable is subject to modification in a stmt
// Based on the Definition for each statement....
// defvar is a varref;
//

int definitionInStmt(SgStatement *func, SgStatement *stmtin, SgExpression *defvar)
{
    SgStatement *last, *stmt;
    SgExpression *def, *expr;

    if (!stmtin || !func)
        return FALSE;

    last = stmtin->lastNodeOfStmt();

    for (stmt = stmtin; stmt; stmt = stmt->lexNext())
    {
        def = (SgExpression *)stmt->attributeValue(0, DEFINEDLIST_ATTRIBUTE);
        //Defined[stmt->id()];
        while (def)
        {
            expr = def->lhs();
            if (expr && expr->symbol() && defvar->symbol() &&
                (expr->symbol() == defvar->symbol()))
            {
                return TRUE;
            }
            def = def->rhs();
        }
        if (stmt == last)
            break;
    }
    return FALSE;
}


//same as before but avoid the first statement (for instance the loop header)
// so can be used fo checking the basic induction variable;
int definitionOnlyInsideStmt(SgStatement *func, SgStatement *stmtin, SgExpression *defvar)
{
    SgStatement *last, *stmt;
    SgExpression *def, *expr;

    if (!stmtin || !func)
        return FALSE;

    last = stmtin->lastNodeOfStmt();

    for (stmt = stmtin->lexNext(); stmt; stmt = stmt->lexNext())
    {
        def = (SgExpression *)stmt->attributeValue(0, DEFINEDLIST_ATTRIBUTE);
        // Defined[stmt->id()];
        while (def)
        {
            expr = def->lhs();
            if (expr && expr->symbol() && defvar->symbol() &&
                (expr->symbol() == defvar->symbol()))
            {
                return TRUE;
            }
            def = def->rhs();
        }
        if (stmt == last)
            break;
    }
    return FALSE;
}


//
// For a statement create an induction var set that contains the SCALAR constante
// based on the use set which have to be defined later
//

Set *
computeConstanteInStmt(SgStatement *func, SgStatement *stmtin)
{
    SgStatement *last, *stmt;
    SgExpression *use, *expr;
    Set *constante;
    PT_INDUCVAR     elin;
    int cst;

    if (!stmtin || !func)
        return NULL;
    last = stmtin->lastNodeOfStmt();
    constante = new Set(inducVarEqual, NULL, inducVarPrint);
#ifdef _WIN32
    addToCollection(__LINE__, __FILE__, constante, 1);
#endif
    for (stmt = stmtin; stmt; stmt = stmt->lexNext())
    {
        use = (SgExpression *)stmt->attributeValue(0, USEDLIST_ATTRIBUTE);
        // Used[stmt->id()];
        while (use)
        {
            expr = use->lhs();
            if (definitionInStmt(func, stmtin, expr))
                cst = 0;
            else
                cst = 1;
            if (cst)
            {
                elin = new struct inducvar;
#ifdef _WIN32
                addToCollection(__LINE__, __FILE__, elin, 1);
#endif
                elin->constante = TRUE;
                elin->stmt = stmtin;
                elin->var = use->lhs();
                elin->lbound = NULL;
                elin->ubound = NULL;
                elin->stride = NULL;
                elin->level = 0;
                elin->loopnum = 0;
                constante->addElement((void *)elin);
            }
            use = use->rhs();
        }
        if (stmt == last)
            break;
    }
    if (constante)
        constante->compact();
    return constante;
}

//
// compute effectively induction variables (limited to basic induction variable for now)
//

Set *
computeInductionVariables(SgStatement *func, SgStatement *stmt)
{
    SgStatement *last, *first, *defreach, *temp, *cp;
    SgForStmt *loop;
    Set *induc, *reachdef;
    SgExpression *use, *def, *pt, *defvar, *expr;
    int change, id, inloop, inv, step;
    PT_ELSET     el;
    PT_INDUCVAR     elin;
    int i, inducF;
    if (!stmt || !func)
        return NULL;

    if (!(loop = isSgForStmt(stmt)))
        return NULL;

    induc = new Set(inducVarEqual, NULL, inducVarPrint);
#ifdef _WIN32
    addToCollection(__LINE__, __FILE__, induc, 1);
#endif
    def = (SgExpression *)stmt->attributeValue(0, DEFINEDLIST_ATTRIBUTE);
    // Defined[stmt->id()];
    if (def)
    { // basic induction var;
        defvar = def->lhs(); // the loop modify the induction var only;
        // check if it is constant;
        if (!definitionOnlyInsideStmt(func, loop, defvar))
            inducF = 1;
        else
        {
            inducF = 1;
            Message("Induction variable may be defined", stmt->lineNumber());
        }
        if (inducF)
        {
            elin = new struct inducvar;
#ifdef _WIN32
            addToCollection(__LINE__, __FILE__, elin, 1);
#endif
            elin->constante = FALSE;
            elin->stmt = stmt;
            elin->var = def->lhs();
            elin->lbound = loop->start();
            elin->ubound = loop->end();
            elin->stride = loop->step();
            elin->level = 0;
            elin->loopnum = 0;
            induc->addElement((void *)elin);
        }
        else
        {
            Message("Basic Induction Var not Found: dependence Test will abort",
                loop->lineNumber());
        }
        // limited to basic induction variable for the moment...;
    }
    return induc;
}




//Get all induction var ;

Set *
getAllInductionVar(SgStatement *func, SgStatement *stmt, int level, int *num, int include)
{
    SgStatement       *temp, *child;
    int               i, newlevel;
    Set               *induc, *tpt;
    PT_INDUCVAR       el;
    int tmpincl;
    if (!stmt)
        return NULL;
    induc = NULL;
    if (isSgForStmt(stmt))
    {
        *num = *num + 1;
        tmpincl = *num;
        induc = computeInductionVariables(func, stmt);
        if (induc)
        {
            for (i = 0; i < induc->size(); i++)
            {
                el = (PT_INDUCVAR)induc->getElement(i);
                if (el)
                {
                    el->level = level;
                    el->loopnum = *num;
                    el->include = include;
                }
            }
        }
    }
    else
        tmpincl = include;
    i = 1;
    temp = stmt;
    child = temp->childList1(0);
    while (child)
    {
        if (isSgForStmt(child))
            newlevel = level + 1;
        else
            newlevel = level;
        if (induc)
        {
            induc->unionSet(tpt = getAllInductionVar(func, child, newlevel, num, tmpincl));
            if (tpt)
            {
#ifdef _WIN32
                removeFromCollection(tpt);
#endif
                delete tpt;
            }
        }
        else
            induc = getAllInductionVar(func, child, newlevel, num, tmpincl);
        child = temp->childList1(i);
        i++;
    }
    i = 1;
    temp = stmt;
    child = temp->childList2(0);
    while (child)
    {
        if (isSgForStmt(child))
            newlevel = level + 1;
        else
            newlevel = level;
        if (induc)
        {
            induc->unionSet(tpt = getAllInductionVar(func, child, newlevel, num, tmpincl));
            if (tpt)
            {
#ifdef _WIN32
                removeFromCollection(tpt);
#endif
                delete tpt;
            }
        }
        else
            induc = getAllInductionVar(func, child, newlevel, num, tmpincl);
        child = temp->childList2(i);
        i++;
    }
    return induc;
}
