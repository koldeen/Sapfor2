#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "sage++user.h"
#include "definesValues.h"
#include "set.h"
#include "definitionSet.h"

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif

//
// Global table to store the use and def 
//

// Not used anymore, replaced by attributes;
// SgExpression *Used[MAXNODE];
// SgExpression *Defined[MAXNODE];

//
// declaration for the  data flow  framework
//

extern Set *genSet[MAXNODE];
extern Set *killSet[MAXNODE];
extern Set *inSet[MAXNODE];
extern Set *outSet[MAXNODE];

extern void iterativeForwardFlowAnalysis(SgFile *file,
    SgStatement *func,
    Set *(*giveGenSet)(SgStatement *func, SgStatement *stmt),
    Set *(*giveKillSet)(SgStatement *func, SgStatement *stmt),
    int(*feq)(void *e1, void *e2),
    void *(*fcomb)(void *e1, void *e2),
    void(*fp)(void *e1));

extern void generalIterativeFlowAnalysis(SgFile *file,
    SgStatement *func,
    Set *(*transfertSet)(SgStatement *func, SgStatement *stmt, Set *setin),
    int(*feq)(void *e1, void *e2),
    void* (*fcomb)(void *e1, void *e2),
    void(*fp)(void *e1));

/////////////////////////////////////////////////////////////////////
// from the intrinsic.C file
/////////////////////////////////////////////////////////////////////

extern int isSymbolIntrinsic(SgSymbol *symb);

/////////////////////////////////////////////////////////////////////
// computes the definition for each file;
/////////////////////////////////////////////////////////////////////

void defUseVar(SgStatement *stmt, SgStatement *func, SgExpression **def, SgExpression **use)
{
    SgExpression *expr1, *expr2;
    SgExpression *temp, *pt, *pt1;
    SgArrayRefExp *aref;
    SgExprListExp *exprli;
    SgFunctionCallExp *fc;
    SgInputOutputStmt *iostmt;
    SgCallStmt *callStat;
    int change;
    if (!stmt || !func)
        return;

    *def = NULL;
    *use = NULL;

    switch (stmt->variant())
    {
    case  ASSIGN_STAT:
        expr1 = stmt->expr(0);
        expr2 = stmt->expr(1);
        // need to be recursively applied later;
        if (expr1)
            *def = expr1->symbRefs();
        else
            *def = NULL;
        if (expr2)
            *use = expr2->symbRefs();
        else
            *use = NULL;
        for (temp = *def; temp; temp = temp->rhs())
        {
            if (aref = isSgArrayRefExp(temp->lhs()))
            {
                pt = aref->subscripts();
                if (pt)
                {
                    pt1 = pt->symbRefs();
                    // we add it to the end of use;
                    if (*use)
                    {
                        if (pt1 && (exprli = isSgExprListExp(*use)))
                        {
                            exprli->linkToEnd(*pt1);
                        }
                    }
                    else
                        *use = pt1;
                }
            }
        }
        for (temp = *use; temp; temp = temp->rhs())
        {
            if (aref = isSgArrayRefExp(temp->lhs()))
            {
                pt = aref->subscripts();
                if (pt)
                {
                    pt1 = pt->symbRefs();
                    // we add it to the end of use;
                    if (pt1 && (exprli = isSgExprListExp(*use)))
                    {
                        exprli->linkToEnd(*pt1);
                    }
                }
            }
            if (fc = isSgFunctionCallExp(temp->lhs()))
            {
                pt = fc->args();
                if (pt)
                {
                    pt1 = pt->symbRefs();
                    // we add it to the end of use;
                    if (pt1 && (exprli = isSgExprListExp(*use)))
                    {
                        exprli->linkToEnd(*pt1);
                    }
                    // if not an intrinsic, needs to be added to the def list;
                    if (!isSymbolIntrinsic(fc->funName()))
                    {
                        pt1 = pt->symbRefs();
                        if (pt1 && (exprli = isSgExprListExp(*def)))
                        {
                            exprli->linkToEnd(*pt1);
                        }
                        else
                            *def = pt1;
                    }
                }
            }
        }
        break;
    case FOR_NODE:
    {
        SgExprListExp *el;
        SgVarRefExp   *vr;
        if (stmt->symbol())
        {
            vr = new SgVarRefExp(*(stmt->symbol()));
            *def = new SgExprListExp(*vr);
            *use = new SgExprListExp(*vr);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, vr, 1);
            addToCollection(__LINE__, __FILE__, *def, 1);
            addToCollection(__LINE__, __FILE__, *use, 1);
#endif
        }
        else
        {
            *use = NULL;
            *def = NULL;
        }
        // Borne inf and sup are also sunject to use;
        expr1 = stmt->expr(0);
        expr2 = stmt->expr(1);
        // need to be recursively applied later;
        if (expr1)
        {
            pt1 = expr1->symbRefs();
            if (*use)
            {
                if (pt1 && (exprli = isSgExprListExp(*use)))
                {
                    exprli->linkToEnd(*pt1);
                }
            }
            else
                *use = pt1;
        }
        if (expr2)
        {
            pt1 = expr2->symbRefs();
            if (*use)
            {
                if (pt1 && (exprli = isSgExprListExp(*use)))
                {
                    exprli->linkToEnd(*pt1);
                }
            }
            else
                *use = pt1;
        }
        for (temp = *use; temp; temp = temp->rhs())
        {
            if (aref = isSgArrayRefExp(temp->lhs()))
            {
                pt = aref->subscripts();
                if (pt)
                {
                    pt1 = pt->symbRefs();
                    // we add it to the end of use;
                    if (pt1 && (exprli = isSgExprListExp(*use)))
                    {
                        exprli->linkToEnd(*pt1);
                    }
                }
            }
            if (fc = isSgFunctionCallExp(temp->lhs()))
            {
                pt = fc->args();
                if (pt)
                {
                    pt1 = pt->symbRefs();
                    // we add it to the end of use;
                    if (pt1 && (exprli = isSgExprListExp(*use)))
                    {
                        exprli->linkToEnd(*pt1);
                    }
                    // if not an intrinsic, needs to be added to the def list;
                    if (!isSymbolIntrinsic(fc->funName()))
                    {
                        pt1 = pt->symbRefs();
                        if (pt1 && (exprli = isSgExprListExp(*def)))
                        {
                            exprli->linkToEnd(*pt1);
                        }
                        else
                            *def = pt1;
                    }
                }
            }
        }
    }
    break;
    case LOGIF_NODE:
    case CONT_STAT:
    case CONTROL_END: // here we should check if loop...
    case IF_NODE:
    case WHILE_NODE:
    case DO_WHILE_NODE:
        expr2 = stmt->expr(0);
        // need to be recursively applied later;
        if (expr2)
            *use = expr2->symbRefs();
        else
            *use = NULL;
        *def = NULL;
        for (temp = *use; temp; temp = temp->rhs())
        {
            if (aref = isSgArrayRefExp(temp->lhs()))
            {
                pt = aref->subscripts();
                if (pt)
                {
                    pt1 = pt->symbRefs();
                    // we add it to the end of use;
                    if (pt1 && (exprli = isSgExprListExp(*use)))
                    {
                        exprli->linkToEnd(*pt1);
                    }
                }
            }
            if (fc = isSgFunctionCallExp(temp->lhs()))
            {
                pt = fc->args();
                if (pt)
                {
                    pt1 = pt->symbRefs();
                    // we add it to the end of use;
                    if (pt1 && (exprli = isSgExprListExp(*use)))
                    {
                        exprli->linkToEnd(*pt1);
                    }
                    // if not an intrinsic, needs to be added to the def list;
                    if (!isSymbolIntrinsic(fc->funName()))
                    {
                        pt1 = pt->symbRefs();
                        if (pt1 && (exprli = isSgExprListExp(*def)))
                        {
                            exprli->linkToEnd(*pt1);
                        }
                        else
                            *def = pt1;
                    }
                }
            }
        }
        break;

    case READ_STAT:
        iostmt = isSgInputOutputStmt(stmt);
        if (iostmt)
        {
            if (iostmt->itemList())
                *def = iostmt->itemList()->symbRefs();
            else
                *def = NULL;
            *use = NULL;
        }
        else
            Message("internal error : IO statements not found\n", 0);
        break;

    case WRITE_STAT:
    case PRINT_STAT:
        iostmt = isSgInputOutputStmt(stmt);
        if (iostmt)
        {
            if (iostmt->itemList())
                *use = iostmt->itemList()->symbRefs();
            else
                *use = NULL;
            *def = NULL;
        }
        else
            Message("internal error : IO statements not found\n", 0);
        break;
    case PROC_STAT:
        callStat = (SgCallStmt*)stmt;
        
        pt = callStat->expr(0);
        if (pt)
        {
            *use = pt->symbRefs();
            // if not an intrinsic, needs to be added to the def list;
            if (!isSymbolIntrinsic(callStat->name()))
                *def = pt->symbRefs();            
            /*pt->unparsestdout();
            printf("\n");
            printf("%s %d\n", callStat->name()->identifier(), stmt->lineNumber());
            if (*use)
            {
                (*use)->unparsestdout();
                printf("\n");
            }
            printf("\n");*/
        }        
        break;
    case GOTO_NODE:
    case STOP_STAT:
    case RETURN_STAT:
    case RETURN_NODE:
    case ELSEIF_NODE:
    case ARITHIF_NODE:
    case WHERE_NODE:
    case WHERE_BLOCK_STMT:
    case SWITCH_NODE:
    case CASE_NODE:
    case BREAK_NODE:
    case EXIT_STMT:
    case ASSGOTO_NODE:
    case COMGOTO_NODE:
    default:
        *def = NULL;
        *use = NULL;
        break;
    }
}


void initDefUseTable(SgStatement *func)
{
    SgStatement *last, *first, *lastfunc, *temp;
    SgExpression *def, *use, *pt;
    int i;
    int nbatt, typeat, j;

    if (!func)
        return;

    lastfunc = func->lastNodeOfStmt();


    for (temp = func; temp; temp = temp->lexNext())
    {
        if (isSgExecutableStatement(temp))
        {
            nbatt = temp->numberOfAttributes();
            for (j = 0; j < nbatt; j++)
            {
                typeat = temp->attributeType(j);
                if ((typeat == USEDLIST_ATTRIBUTE) ||
                    (typeat == DEFINEDLIST_ATTRIBUTE))
                {
                    temp->deleteAttribute(j);
                    j--;
                }
            }
        }
        if (temp == lastfunc)
            break;
    }

    for (temp = func; temp; temp = temp->lexNext())
    {
        if (isSgExecutableStatement(temp))
        {
            defUseVar(temp, func, &def, &use);
            temp->addAttribute(USEDLIST_ATTRIBUTE, (void *)use, 0);
            temp->addAttribute(DEFINEDLIST_ATTRIBUTE, (void *)def, 0);
        }
        if (temp == lastfunc)
            break;
    }
}

//
// Example of functions for flow analysis
//
int symbRefEqual(void *e1, void *e2)
{
    SgExpression *ex1, *ex2;
    SgSymbol     *s1, *s2;
    PT_ELSET     el1, el2;
    if (!e1 && !e2)
        return 1;
    if (!e1 || !e2)
        return 0;

    el1 = (PT_ELSET)e1;
    el2 = (PT_ELSET)e2;

    ex1 = el1->expr;
    ex2 = el2->expr;

    if ((s1 = ex1->symbol()) && (s2 = ex2->symbol()))
    {
        if (s1 == s2)
        {
            if (el1->stmt == el2->stmt)
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}

void myPrint(void *e1)
{
    SgExpression *ex1;
    PT_ELSET     el1;
    if (!e1)
        return;
    el1 = (PT_ELSET)e1;
    ex1 = el1->expr;
    if (el1->stmt)
        printf("(id = %d, line = %d, ", el1->stmt->id(), el1->stmt->lineNumber());
    else
        printf("(id = -, line = -, ");
    if (ex1->symbol())
        printf("%s", ex1->symbol()->identifier());
    else
        ex1->unparsestdout();
    printf(")");
    printf(",");
}

//
// Example of function to compute gen and kill  sets for Reaching Definition.
// NOARRAYREF indicate if we want array ref in

Set *makeGenSet(SgStatement *func, SgStatement *stmt)
{
    SgExpression *def, *use, *pt;
    PT_ELSET     el;
    Set *defset, *pts;

    if (!func || !stmt)
        return NULL;

    def = (SgExpression *)stmt->attributeValue(0, DEFINEDLIST_ATTRIBUTE);
    // Defined[stmt->id()];
    defset = new Set(symbRefEqual, NULL, myPrint);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, defset, 1);
#endif
    if (def)
    {
        for (pt = def; pt; pt = pt->rhs())
        {
            if (!isSgTypeExp(pt->lhs()))
            {
                if (!NOARRAYREF || !isSgArrayRefExp(pt->lhs()))
                {
                    el = new struct elset;
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, el, 1);
#endif
                    el->stmt = stmt;
                    el->expr = pt->lhs();
                    defset->addElement((void *)el);
                }
            }
        }
    }

    pts = defset;
    //  printf("Printing defset:\n");
    //  defset->printSet();
    defset = defset->compact();
    if (pts)
    {
#ifdef __SPF
        removeFromCollection(pts);
#endif
        delete pts;
    }
    //   defset->printSet();
    return defset;

}


Set *makeKillSet(SgStatement *func, SgStatement *stmt)
{

    SgExpression *def, *use, *pt, *defstmt, *expr1, *pt1;
    PT_ELSET     el;
    Set *killset, *pts;
    SgStatement *last, *first, *lastfunc, *temp;
    int trouve;
    if (!func || !stmt)
        return NULL;

    killset = new Set(symbRefEqual, NULL, myPrint);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, killset, 1);
#endif
    last = func->lastNodeOfStmt();
    defstmt = (SgExpression *)stmt->attributeValue(0, DEFINEDLIST_ATTRIBUTE);
    //Defined[stmt->id()];
    if (defstmt)
    {
        for (pt1 = defstmt; pt1; pt1 = pt1->rhs())
        {
            expr1 = pt1->lhs();
            if (!isSgArrayRefExp(expr1) && !isSgTypeExp(expr1))
            { // cannot kill an array ref;
                for (temp = func; temp; temp = temp->lexNext())
                {
                    if (temp != stmt)
                    {
                        if (def = (SgExpression *)temp->attributeValue(0, DEFINEDLIST_ATTRIBUTE))
                            //Defined[temp->id()])
                        {
                            for (pt = def; pt; pt = pt->rhs())
                            {
                                if (pt->lhs())
                                {
                                    if (pt->lhs()->symbol() == expr1->symbol())
                                    {
                                        el = new struct elset;
#ifdef __SPF
                                        addToCollection(__LINE__, __FILE__, el, 1);
#endif
                                        el->stmt = temp;
                                        el->expr = pt->lhs();
                                        killset->addElement((void *)el);
                                    }
                                }
                            }
                        }
                    }
                    if (temp == last)
                        break;
                }
            }
        }
    }
    pts = killset;
    //   printf("Printing killset:\n");
    //   killset->printSet();
    killset = killset->compact();
    //   killset->printSet();
    if (pts)
    {
#ifdef __SPF
        removeFromCollection(pts);
#endif
        delete pts;
    }
    return killset;
}
