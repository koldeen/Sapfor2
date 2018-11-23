#include <stdio.h>
#include <malloc.h>
#include "sage++user.h"
#include "definesValues.h"


//
// Control Flow functions -------> should become a method of the statement class
// return an array of successor and predecessor 
// the function compute the control flow.
// this is assumed to be applied on a function.
// func is the function we are in
//


void
controlFlow(SgStatement *stmt, SgStatement *func, SgStatement **pred, SgStatement **suc, int *predin, int *sucint)
{
    SgLabel *lab, *labtemp;
    SgStatement *last, *cp, *temp;
    SgGotoStmt  *gt;
    SgLabelListStmt *gtl;
    SgExpression *expr, *te;
    SgLabelRefExp *le;
    int nbpred, nbsuc;
    if (!stmt || !func)
        return;

    nbpred = 0;
    nbsuc = 0;

    if (lab = stmt->label())
    { // there is a label, look at the goto on it;
        last = func->lastNodeOfStmt();
        // look at the goto statement going to the statement;
        for (temp = func; temp && (temp != last); temp = temp->lexNext())
        {
            if (gt = isSgGotoStmt(temp))
            {
                labtemp = gt->label();
                if (labtemp && (labtemp->id() == lab->id()))
                {
                    pred[nbpred] = temp;
                    nbpred++;
                }
            }
            else
            {
                if (gtl = isSgLabelListStmt(temp))
                {
                    expr = gtl->labelList();
                    for (te = expr; te; te = te->rhs())
                    {
                        if (le = isSgLabelRefExp(te->lhs()))
                        {
                            labtemp = le->label();
                            if (labtemp && (labtemp->id() == lab->id()))
                            {
                                pred[nbpred] = temp;
                                nbpred++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    // there is no label;
    // depending on the statement we compute the predecessors;
    // and the successor;
    // here we use a big case;
    switch (stmt->variant())
    {
    case CONT_STAT:
    case   CONTROL_END:
        cp = stmt->controlParent();
        if (cp)
        {
            switch (cp->variant())
            {
            case WHILE_NODE:
            case FOR_NODE:
                pred[nbpred] = stmt->nodeBefore();
                nbpred++;
                suc[nbsuc] = stmt->lexNext();
                nbsuc++;
                suc[nbsuc] = cp;
                nbsuc++;
                break;
            default:
                pred[nbpred] = stmt->nodeBefore();
                suc[nbsuc] = stmt->lexNext();
                nbpred++;
                nbsuc++;
            }
        }
        else
        {
            pred[nbpred] = stmt->nodeBefore();
            suc[nbsuc] = stmt->lexNext();
            nbpred++;
            nbsuc++;
        }
        break;
    case IF_NODE:
        suc[nbsuc] = stmt->childList1(0);
        nbsuc++;
        if (stmt->childList2(0))
        {
            suc[nbsuc] = stmt->childList2(0);
            nbsuc++;
        }
        else
        {
            suc[nbsuc] = stmt->lastNodeOfStmt()->lexNext();
            nbsuc++;
        }
        pred[nbpred] = stmt->nodeBefore();
        nbpred++;
        break;
    case WHILE_NODE:
    case FOR_NODE:
        pred[nbpred] = stmt->nodeBefore();
        nbpred++;
        pred[nbpred] = stmt->lastNodeOfStmt();
        nbpred++;
        suc[nbsuc] = stmt->lexNext();
        nbsuc++;
        suc[nbsuc] = stmt->lastNodeOfStmt()->lexNext();
        nbsuc++;
        break;
    case DO_WHILE_NODE:
        pred[nbpred] = stmt->nodeBefore();
        nbpred++;
        pred[nbpred] = stmt->lastNodeOfStmt();
        nbpred++;
        suc[nbsuc] = stmt->lexNext();
        nbsuc++;
        break;
    case GOTO_NODE:
        if (gt = isSgGotoStmt(stmt))
        {
            if (lab = gt->label())
            { // there is a label, look at the goto on it;
                last = func->lastNodeOfStmt();
                // look at the goto statement going to the statement;
                for (temp = func; temp && (temp != last); temp = temp->lexNext())
                {
                    labtemp = temp->label();
                    if (labtemp && (labtemp->id() == lab->id()))
                    {
                        suc[nbsuc] = temp;
                        nbsuc++;
                    }
                }
            }
        }
        break;
    case LOGIF_NODE:
        suc[nbsuc] = stmt->childList1(0);
        nbsuc++;
        suc[nbsuc] = stmt->lastNodeOfStmt()->lexNext();
        nbsuc++;
        pred[nbpred] = stmt->nodeBefore();
        nbpred++;
        break;
    case STOP_STAT:
    case RETURN_STAT:
    case RETURN_NODE:
        pred[nbpred] = stmt->nodeBefore();
        nbpred++;
        suc[nbsuc] = func->lastNodeOfStmt();
        nbsuc++;
        break;
    case  ELSEIF_NODE:
        //    case ARITHIF_NODE:
    case WHERE_NODE:
    case WHERE_BLOCK_STMT:
    case SWITCH_NODE:
    case CASE_NODE:
    case BREAK_NODE:
    case EXIT_STMT:
    case ASSGOTO_NODE:
    case COMGOTO_NODE:
        printf("Statement line %d not implemented for control flow\n", stmt->lineNumber());
        break;
    default:
        // cas du if a voir ici...
        cp = stmt->controlParent();
        if (cp)
        {
            switch (cp->variant())
            {
            case IF_NODE:
                if (cp->childList1(0) == stmt)
                {
                    pred[nbpred] = cp;
                    nbpred++;
                    suc[nbsuc] = stmt->lexNext();
                    nbsuc++;
                }
                else
                    if (cp->childList2(0) == stmt)
                    {
                        pred[nbpred] = cp;
                        nbpred++;
                        suc[nbsuc] = stmt->lexNext();
                        nbsuc++;
                    }
                    else
                    {
                        pred[nbpred] = stmt->nodeBefore();
                        suc[nbsuc] = stmt->lexNext();
                        nbpred++;
                        nbsuc++;
                    }
                break;
                // for node should also be taken into account
            default:
                pred[nbpred] = stmt->nodeBefore();
                suc[nbsuc] = stmt->lexNext();
                nbpred++;
                nbsuc++;
            }
        }
        else
        {
            pred[nbpred] = stmt->nodeBefore();
            suc[nbsuc] = stmt->lexNext();
            nbpred++;
            nbsuc++;
        }
    }
    *predin = nbpred;
    *sucint = nbsuc;
}
