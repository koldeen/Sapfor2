#include <stdio.h>
#include <stdlib.h>

#include "sage++user.h"
#include "definesValues.h"
#include "set.h"
#include "definitionSet.h"
#include "constanteSet.h"

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
#endif

//
// Program part for constant propagation.
//

//
// Set Operation
//
int constPropEqual(void *e1, void *e2)
{
    SgExpression *ex1, *ex2;
    SgSymbol     *s1, *s2;
    PT_CONSTPROP     el1, el2;
    if (!e1 && !e2)
        return 1;
    if (!e1 || !e2)
        return 0;

    el1 = (PT_CONSTPROP)e1;
    el2 = (PT_CONSTPROP)e2;

    ex1 = el1->var;
    ex2 = el2->var;

    if ((s1 = ex1->symbol()) && (s2 = ex2->symbol()))
    {
        if ((s1 == s2) && (el1->flag == el2->flag) && (el1->value == el2->value))
            return 1;
        else
            return 0;
    }
    else
        return 0;
}


void constPropPrint(void *e1)
{
    SgExpression *ex1;
    PT_CONSTPROP     el1;
    if (!e1)
        return;
    el1 = (PT_CONSTPROP)e1;
    ex1 = el1->var;
    if (ex1->symbol())
    {
        printf("%s (from stmt %d):", ex1->symbol()->identifier(), el1->stmt->lineNumber());
        switch (el1->flag)
        {
        case UNDEFFLAG:
            printf("undefined\n");
            break;
        case NONCONSTFLAG:
            printf("non constant\n");
            break;
        case CONSTFLAG:
            printf("%d\n", el1->value);
            break;
        }
    }
    else
        printf("Bizarre\n");
}

//
// Here we need th combine operation, combine two elements
// return NULL if combine possible
//
void *
constPropCombine(void *e1, void *e2)
{
    SgExpression *ex1, *ex2;
    SgSymbol     *s1, *s2;
    PT_CONSTPROP     el1, el2;

    if (!e1)
        return e2;
    if (!e2)
        return e1;

    el1 = (PT_CONSTPROP)e1;
    el2 = (PT_CONSTPROP)e2;

    ex1 = el1->var;
    ex2 = el2->var;

    if ((s1 = ex1->symbol()) && (s2 = ex2->symbol()))
    {
        if (s1 == s2)
        {
            if (el1->flag == UNDEFFLAG)
                return e1;
            if (el2->flag == UNDEFFLAG)
                return e2;
            if (el1->flag == NONCONSTFLAG)
                return e1;
            if (el2->flag == NONCONSTFLAG)
                return e2;

            if (el1->value == el2->value)
                return e1;
            else
            {
                el1->flag = NONCONSTFLAG;
                return e1;
            }
        }
        else
            return NULL;
    }
    else
        return NULL;
}

//
// this function evaluate the value of the 
//
// some functions from the low_level are used for that function so that Evaluate Expression can use
// the value of some variables
//

// extern "C" void resetPresetEvaluate();
// extern "C" void addElementEvaluate(...);

Set *transConstante(SgStatement *func, SgStatement *stmt, Set *setin)
{
    Set *outset;
    SgExpression *def, *defvar, *expr;
    SgSymbol     *symb;
    int val;
    int i;
    PT_CONSTPROP  el = NULL;
    PT_CONSTPROP  el1 = NULL;
    if (!func || !stmt)
    {
        Message("transConstante some parameters are null", 0);
        return NULL;
    }

    if (isSgCallStmt(stmt) || isSgInputOutputStmt(stmt))
    {
        if (!setin)
            return NULL;
        else
        {
            outset = new Set(constPropEqual, constPropCombine, constPropPrint);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, outset, 1);
#endif
            for (i = 0; i < setin->size(); i++)
            {
                el = (PT_CONSTPROP)setin->getElement(i);
                if (el)
                { // create new one otherwise side effect can appear;
                    el1 = new struct constprop;
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, el1, 1);
#endif
                    el1->flag = UNDEFFLAG;
                    el1->var = el->var;
                    el1->value = 0;
                    el1->stmt = el->stmt;
                    el1->expr = el->expr;
                    outset->addElement((void *)el1);
                }
            }
            // should add the parameter list with undefined;

            // this has been completly copied so allow to deallocate element too;
  //          setin->setDealllocateElem(); other element need also to be copied
            return outset;
        }
    }
    if (!isSgAssignStmt(stmt))
    {
        if (!setin)
            return NULL;
        else
            return  setin->copy();
    }
    if (setin)
        outset = setin->copy();
    else
    {
        outset = new Set(constPropEqual, constPropCombine, constPropPrint);
#ifdef __SPF
        addToCollection(__LINE__, __FILE__, outset, 1);
#endif
    }
    // before evaluating the expression set the Value set ;
    if (setin)
    {
        for (i = 0; i < setin->size(); i++)
        {
            el = (PT_CONSTPROP)setin->getElement(i);
            if (el)
            {
                if ((el->flag == CONSTFLAG) &&
                    el->var &&
                    el->var->symbol())
                {
                    addElementEvaluate(el->var->symbol()->thesymb, el->value);
                }
            }
        }
    }
    // just call Evaluate Expression ;
    def = (SgExpression *)stmt->attributeValue(0, DEFINEDLIST_ATTRIBUTE);
    //Defined[stmt->id()];
    if (def)
    {
        defvar = def->lhs();
        if (isSgVarRefExp(defvar))
        {
            symb = defvar->symbol();
            if (symb && symb->type() && (symb->type()->variant() == T_INT))
            {
                if (setin)
                {
                    // remove all definition to the symbol;
                    for (i = 0; i < outset->size(); i++)
                    {
                        el = (PT_CONSTPROP)outset->getElement(i);
                        if (el)
                        {
                            if (el->var->symbol() == symb)
                                outset->rmElement(i);
                        }
                    }
                }
                expr = stmt->expr(1);
                el = new struct constprop;
#ifdef __SPF
                addToCollection(__LINE__, __FILE__, el, 1);
#endif
                if (!el)
                {
                    Message("No more Memory", 0);
                    exit(1);
                }
                if (expr && expr->isInteger())
                {
                    val = expr->valueInteger();
                    el->flag = CONSTFLAG;
                    el->var = defvar;
                    el->value = val;
                    el->stmt = stmt;
                    el->expr = expr;
                    outset->addElement((void *)el);
                }
                else
                {
                    el->flag = UNDEFFLAG;
                    el->var = defvar;
                    el->value = 0;
                    el->stmt = stmt;
                    el->expr = expr;
                    outset->addElement((void *)el);
                }
            }
        }
    }
    resetPresetEvaluate();
    //  printf("intermediate print line %d\n", stmt->lineNumber());
    //  outset->printSet();
    return outset;
}
