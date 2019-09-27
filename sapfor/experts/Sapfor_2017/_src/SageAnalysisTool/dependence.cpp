#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif

#if __SPF && NDEBUG && __BOOST
#include <boost/thread.hpp>
extern int passDone;
#endif

#include "sage++user.h"
#include "definesValues.h"
#include "set.h"
#include "definitionSet.h"
#include "inducVar.h"

#include "arrayRef.h"
#include "dependence.h"

/* to link with the omega Test */
#include "OmegaForSage/include/portable.h"
#include "OmegaForSage/include/affine.h"

extern void SetSTuff();
extern "C" void SetOmegaDebug();
extern "C" void initAnnotation();
extern "C" void Look_For_Align_Declaration();
extern void dd_omega_test(a_access access1, a_access access2, ddnature oitype, ddnature iotype, uint nest1, uint nest2, uint bnest);

///////////////////////////////////////////////////////////////////////////
// Some global declaration 
///////////////////////////////////////////////////////////////////////////

SgStatement  *currentStmtIn = NULL;
SgStatement  *currentStmtOut = NULL;
SgExpression *currentVarIn = NULL;
SgExpression *currentVarOut = NULL;
int WarningOutForNegativeStep = 0;
int TurnIfConstructionOf = 0;

// Kolganov A.S. 31.07.2017
// try to process loop with negative step: inverse the iteration space
#define PROCESS_LOOPS_WITH_NEG_STEP 1

// Needs to provide dummy function
int dummyEqual(void *e1, void *e2)
{
    return (e1 == e2);
}

void dummyPrint(void *e1)
{
    printf("Dummy print\n");
}

///////////////////////////////////////////////////////////////////////////
// comming from depGraph.c
///////////////////////////////////////////////////////////////////////////
#include "depGraph.h"
extern depGraph *currentDepGraph;

///////////////////////////////////////////////////////////////////////////
// here we call the omega test routine.... First some routine to do the job
// compute the data dependencies using the Omega Test....
///////////////////////////////////////////////////////////////////////////

affine_expr *makeOmegaAffine(int size, var_id *induc, int *linear, int cst, int notaffine, Set *setForDealocatingMemory)
{
    int i, finalsize;
    affine_expr *ptaff, *init;
    if (!induc || !linear)
        return  &not_affine;
    if (!notaffine)
        return  &not_affine;
    if (WarningOutForNegativeStep)
        return  &not_affine;
    ptaff = new affine_expr;
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, ptaff, 1);
#endif
    setForDealocatingMemory->addElement((void *)ptaff);
    ptaff->nterms = size + 1;
    ptaff->other_branch = NULL;
    (ptaff->terms[0]).tiny_var = NULL;
    (ptaff->terms[0]).coefficient = cst;
    if (size >= maxVars)
    {
        Message("Too many variable in makeOmegaAffine\n");
        return NULL;
    }
    finalsize = 0;
    for (i = 1; i <= size; i++)
    {
        if (linear[i - 1] != 0)
        {
            finalsize++;
            (ptaff->terms[finalsize]).tiny_var = induc[i - 1];
            (ptaff->terms[finalsize]).coefficient = linear[i - 1];
        }
    }
    ptaff->nterms = finalsize + 1;
    return ptaff;
}

int fillOmegaAccess(PT_ACCESSARRAY  el1, a_access access1, const Set *induc, var_id *inducom, 
                    context_iterator firstcontiter, char *name, int inif, Set *setForDealocatingMemory)
{
    int i, j;
    sub_iterator itern = NULL;
    sub_iterator firstiter;
    PT_INDUCVAR ind, cur;
    firstiter = NULL;
    for (j = 0; j < el1->nbdim; j++)
    {
        if (firstiter)
        {
            itern->next = new struct omegaIterator;
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, itern->next, 1);
#endif
            setForDealocatingMemory->addElement((void *)itern->next);
            itern = itern->next;
            itern->next = NULL;
        }
        else
        {
            itern = new struct omegaIterator;
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, itern, 1);
#endif
            setForDealocatingMemory->addElement((void *)itern);
            firstiter = itern;
            itern->next = NULL;
        }
        if (el1->isLinear[j] && !el1->scalar)
        {
            itern->isaffine = TRUE;
            itern->affine = makeOmegaAffine(induc->size(), inducom, el1->linear[j], el1->cst[j], el1->isLinear[j], setForDealocatingMemory);
        }
        else
        {
            itern->isaffine = FALSE;
            itern->affine = &not_affine;
        }
        itern->cstvalue = 0;
        itern->constante = NULL;
    }

    //
    access1->str = new char[256];
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, access1->str, 2);
#endif
    setForDealocatingMemory->addElement((void *)access1->str);
    strcpy(access1->str, name);
    access1->symb = NULL;
    access1->subiter = firstiter;
    access1->context = firstcontiter;
    access1->line = el1->stmt->lineNumber();
    access1->cdepth = -1;
    access1->tdepth = -1;
    access1->idforsage = el1->var->id();
    access1->inIfStmt = inif;
    // look at for the level;
    cur = NULL;
    for (j = 0; j < induc->size(); j++)
    {
        ind = (PT_INDUCVAR)induc->getElement(j);
        if (ind && (ind->loopnum == el1->level))
        {
            cur = ind;
            break;
        }
    }
    if (cur)
    {
        access1->depth = cur->level;
    }
    else
        access1->depth = 0;
    access1->pri = 0;
    access1->level = el1->level; // temporary setting;
    if (el1->rw)
    {
        access1->fetch = FALSE;
        access1->store = TRUE;
    }
    else
    {
        access1->fetch = TRUE;
        access1->store = FALSE;
    }
    access1->update = 0;
    access1->lexord = 1; // temporary setting;
    return access1->depth;
}


// answer yes if el1 >> el2; to be optimize by checking procedure control_end
int lexOrder(PT_ACCESSARRAY  el1, PT_ACCESSARRAY el2)
{
    SgStatement *stmt;
    if (!el1 || !el2)
        return FALSE;
    if (el1->stmt == el2->stmt)
        return FALSE;
    if (!el1->stmt || !el2->stmt)
        return FALSE;
    stmt = el1->stmt;
    while (stmt)
    {
        if (stmt == el2->stmt)
            return TRUE;
        stmt = stmt->lexNext();
    }
    return FALSE;
}

context_iterator makeOmegaIf(int depth, SgStatement  *stmt, context_iterator next, int brelse, Set *setForDealocatingMemory)
{
    if_context ifstat;
    context_iterator contiter;

    if (!stmt)
        return NULL;
    // dealing with the conditions later...
    contiter = new struct omegaContIter;
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, contiter, 1);
#endif
    setForDealocatingMemory->addElement((void *)contiter);
    contiter->next = next;
    contiter->depth = depth;
    contiter->loopiter = FALSE;
    contiter->line = stmt->lineNumber();
    contiter->loop = NULL;
    ifstat = new struct omegaIf;
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, ifstat, 1);
#endif
    setForDealocatingMemory->addElement((void *)ifstat);
    ifstat->oper = greater_eq;
    ifstat->ident = stmt->id();
    ifstat->left = &not_affine;
    ifstat->right = &not_affine;
    ifstat->condOK = FALSE;
    ifstat->partelse = brelse;
    contiter->ifstmt = ifstat;
    return contiter;
}

// try to manage non nested loops;;;
context_iterator fillOmegaLoop(PT_ACCESSARRAY  el1, const Set *induc, var_id *inducom, SgSymbol **tsymb, int *inif, Set *setForDealocatingMemory)
{
    int i, j, inbrelse, k;
    PT_INDUCVAR ind, cur;
    context_iterator contiter, firstcontiter;
    loop_context loop;
    if_context ifstat;
    int    linear[MAXNESTEDLOOP];
    int cst, loopnum, curnum;
    var_id  tempvar;
    SgExpression  *step;
    SgForStmt     *stloop;
    SgStatement   *currentstmt, *cp, *tmp;

    if (!el1 || !induc || !tsymb)
        return NULL;
    // look for the induction variable corresponding to the loop...;
    // examine for duplicate symbols first so the linear loop bounds are set right;
    loopnum = el1->level;
    while (loopnum != -1)
    {
        cur = NULL;
        for (j = 0; j < induc->size(); j++)
        {
            ind = (PT_INDUCVAR)induc->getElement(j);
            if (ind && (!ind->constante) && (ind->loopnum == loopnum))
            {
                cur = ind;
                // check if there is multiple uses of the same variable;
                // to set curnum to the righ symbol;
                // the first one has to be taken;
                // this is related to the linear expression;
                for (k = 0; k < j; k++)
                {
                    ind = (PT_INDUCVAR)induc->getElement(k);
                    if (ind->var->symbol() == cur->var->symbol())
                    {
                        // switch the position in inducom so the;
                        // linear expression for the loops bound are right;
                        tempvar = inducom[k];
                        inducom[k] = inducom[j];
                        inducom[j] = tempvar;
                        break;
                    }
                }
                break;
            }
        }
        if (!cur)
            break;
        loopnum = cur->include;
    }
    loopnum = el1->level;
    firstcontiter = NULL;
    contiter = NULL;
    curnum = -1;
    currentstmt = el1->stmt;
    *inif = FALSE;
    while (loopnum != -1)
    {
        cur = NULL;
        for (j = 0; j < induc->size(); j++)
        {
            ind = (PT_INDUCVAR)induc->getElement(j);
            if (ind && (!ind->constante) && (ind->loopnum == loopnum))
            {
                cur = ind;
                curnum = j;
                // check if there is multiple uses of the same variable;
                // to set curnum to the righ symbol;
                // the first one has to be taken;
                // this is related to the linear expression;
                for (k = 0; k < j; k++)
                {
                    ind = (PT_INDUCVAR)induc->getElement(k);
                    if (ind->var->symbol() == cur->var->symbol())
                    {
                        curnum = k; // position has been switch before;
                        break;
                    }
                }
                break;
            }
        }
        if (cur)
        {
            if (TurnIfConstructionOf)
            {
                // is in IF Statement; problems with the ELSE IF STUFF;
                if (currentstmt && currentstmt->controlParent() &&
                    ((currentstmt->controlParent()->variant() == IF_NODE) ||
                    (currentstmt->controlParent()->variant() == ELSEIF_NODE)))
                {
                    // which branch of the IF???;
                    cp = currentstmt->controlParent();
                    inbrelse = TRUE;
                    if (!(currentstmt->controlParent()->variant() == ELSEIF_NODE))
                    {
                        for (i = 0; i < cp->numberOfChildrenList1(); i++)
                        {
                            tmp = cp->childList1(i);
                            if (tmp == currentstmt)
                            {
                                inbrelse = FALSE;
                                break;
                            }
                        }
                        *inif = TRUE;
                        firstcontiter = makeOmegaIf(cur->level, currentstmt->controlParent(), firstcontiter, inbrelse, setForDealocatingMemory);
                    }
                }
                // end of if statement;
            }


            contiter = new struct omegaContIter;
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, contiter, 1);
#endif
            setForDealocatingMemory->addElement((void *)contiter);
            contiter->next = firstcontiter;
            firstcontiter = contiter;
            contiter->depth = cur->level;
            contiter->loopiter = TRUE;
            contiter->line = cur->stmt->lineNumber();
            currentstmt = cur->stmt;
            contiter->loop = new struct omegaLoop;
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, contiter->loop, 1);
#endif
            setForDealocatingMemory->addElement((void *)contiter->loop);
            loop = contiter->loop;
            // for different non perfectly nested loop
            // the index variable must be the same, so there is a pb here;
            loop->symb = inducom[curnum];
            // build the linear rep ;
            cst = 0;
            for (i = 0; i < MAXNESTEDLOOP; i++)
                linear[i] = 0;
            if (cur->lbound->linearRepresentation(linear, tsymb, &cst, induc->size()))
            {
                loop->startl = makeOmegaAffine(induc->size(), inducom, linear, cst, 1, setForDealocatingMemory);
            }
            else
            {
                loop->startl = &not_affine;
                //            if (VeryVerbose)
                //           Message("Non Linear Starting Bound of Loop",cur->stmt->lineNumber());
            }
            loop->cstvaluestart = 0;
            loop->constantestart = NULL;
            cst = 0;
            for (i = 0; i < MAXNESTEDLOOP; i++)
                linear[i] = 0;
            if (cur->ubound->linearRepresentation(linear, tsymb, &cst, induc->size()))
            {
                loop->endl = makeOmegaAffine(induc->size(), inducom, linear, cst, 1, setForDealocatingMemory);
            }
            else
            {
                loop->endl = &not_affine;
                //            if (VeryVerbose)
                //             Message("Non Linear Ending Bound of Loop",cur->stmt->lineNumber());
            }

            loop->cstvaluesend = 0;
            loop->constanteend = NULL;
            // deal with the step of the loop;
            if (stloop = isSgForStmt(cur->stmt))
            {
                if (step = stloop->step())
                {
                    if (step->isInteger())
                    {
                        loop->hasstep = TRUE;
                        loop->stepl = step->valueInteger();
                        loop->knownstep = TRUE;
                        if (loop->stepl < 0)
                        {
                #if PROCESS_LOOPS_WITH_NEG_STEP
                            loop->stepl = -loop->stepl;
                            std::swap(loop->startl, loop->endl);
                #else
                            loop->hasstep = FALSE;
                            loop->stepl = 1;
                            loop->knownstep = FALSE;

                            loop->startl = &not_affine;
                            loop->endl = &not_affine;
                            if (!WarningOutForNegativeStep)
                            {
                                Message("Negative Steps found: Ignored loop bounds", stloop->lineNumber());
                                WarningOutForNegativeStep = 1;
                            }
                #endif
                        }
                    }
                    else
                    {
                        loop->hasstep = FALSE;
                        loop->stepl = 1;
                        loop->knownstep = FALSE;
                    }
                }
                else
                {
                    loop->hasstep = FALSE;
                    loop->stepl = 1;
                    loop->knownstep = TRUE;
                }
            }
            else
            {
                loop->hasstep = FALSE;
                loop->stepl = 1;
                loop->knownstep = FALSE;
            }
        }
        else
            break;
        loopnum = cur->include;
    }
    return firstcontiter;
}

int commonDepth(context_iterator iti1, context_iterator iti2)
{
    context_iterator it1, it2;
    it1 = iti1;
    it2 = iti2;
    int depth = 0;
    while (!cont_i_done(it1) && !cont_i_done(it2))
    {
        if (cont_i_cur_loop_p(it1) && cont_i_cur_loop_p(it2))
        {
            if (loop_var_id(cont_i_cur_loop(it1)) != loop_var_id(cont_i_cur_loop(it2)))
                return depth;
            depth++;
        }
        // common depth does not go in If (I guess);
        //      else
        //  { 
        //           if (cont_i_cur_if_p(it1) && cont_i_cur_if_p(it2))
        //             {
        //               if (cont_i_cur_if(it1)->ident != cont_i_cur_if(it2)->ident)
        //                 return depth;
        //               depth++;
        //             }
        //  }
        cont_i_next(it1);
        cont_i_next(it2);
    }
    return depth;
}

//from dep_analyzer.cpp
extern bool isRemovableDependence(const depNode *toCheck, const std::set<std::string> &privVars);

static int isDependent(PT_ACCESSARRAY el1, PT_ACCESSARRAY el2, const Set *induc, int &countOfNodes)
{
    ///////////////////////////////////////////////////////////////////////////
    // deallocation Set
    ///////////////////////////////////////////////////////////////////////////

    // in that set we store everything that must be deallocated at some
    // point in the program

    Set *setForDealocatingMemory = NULL;

    int i, j;
    PT_INDUCVAR ind;
    SgExpression  *ex2;
    SgSymbol      *tsymb[MAXNESTEDLOOP];
    a_access access1, access2, access3;
    ddnature oitype, iotype;
    uint nest1, nest2, nest3, bnest;
    context_iterator firstcontiter, firstcontiter1;
    var_id           inducom1[MAXNESTEDLOOP];
    var_id           inducom2[MAXNESTEDLOOP];
    var_id           ptvar;
    int              inif;

    if (!el1 || !el2)
        return -2;
    // do not accept scalar variables here 
    if (el1->scalar || el2->scalar)
    {
        //      not treated here but in depGraph.C   
        //      if (!currentDepGraph)
        //       {
        //          Message("No current Dep Graph",0);
        //          return -2;
        //        }
        //      currentDepGraph->addAnEdge(el1->stmt,el2->stmt,
        //                                 el1->var,el2->var,
        //                                 SCALARDEP,0,NULL,NULL,0);
        return 0;
    }
    // create the set for deallocation of memory;
    setForDealocatingMemory = new Set(dummyEqual, NULL, dummyPrint);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, setForDealocatingMemory, 1);
#endif
    setForDealocatingMemory->setDealllocateElem();

    // we have to prepare the data structure for the omega test 

    SetSTuff(); // initialize the omega test

    // format the variable for the omega test;

    for (j = 0; j < induc->size(); j++)
    {
        ind = (PT_INDUCVAR)induc->getElement(j);
        ptvar = (omegaVar*)malloc(sizeof(omegaVar));
#ifdef __SPF
        addToCollection(__LINE__, __FILE__, ptvar, 0);
#endif
        setForDealocatingMemory->addElement((void *)ptvar);
        inducom1[j] = ptvar;
        inducom2[j] = ptvar;
        //      ptvar->loop = ind->loopnum;
        ptvar->loop = ind->level; // seems to be more correct...
        if (ind->constante)
        {
            ptvar->indexp = FALSE; // constante variable;
            ptvar->constp = TRUE;
        }
        else
        {
            ptvar->indexp = TRUE; // index variable;
            ptvar->constp = FALSE;
        }
        ptvar->tag = UNTAGGED;
        ptvar->name = ind->var->symbol()->identifier();
    }
    inducom1[induc->size()] = NULL;
    inducom2[induc->size()] = NULL;
    for (i = 0; i < induc->size(); i++)
    {
        ind = (PT_INDUCVAR)induc->getElement(i);
        if (ex2 = ind->var)
        {
            tsymb[i] = ex2->symbol();
        }
    }

    access1 = (omegaAccess*)malloc(sizeof(omegaAccess));
    setForDealocatingMemory->addElement((void *)access1);
    access2 = (omegaAccess*)malloc(sizeof(omegaAccess));
    setForDealocatingMemory->addElement((void *)access2);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, access1, 0);
    addToCollection(__LINE__, __FILE__, access2, 0);
#endif
    firstcontiter = fillOmegaLoop(el1, induc, inducom1, tsymb, &inif, setForDealocatingMemory);
    firstcontiter1 = firstcontiter;
    nest1 = fillOmegaAccess(el1, access1, induc, inducom1, firstcontiter, "Access1", inif, setForDealocatingMemory);
    firstcontiter = fillOmegaLoop(el2, induc, inducom2, tsymb, &inif, setForDealocatingMemory);
    nest2 = fillOmegaAccess(el2, access2, induc, inducom2, firstcontiter, "Access2", inif, setForDealocatingMemory);
    access1->lexord = 2;
    access2->lexord = 1;
    if (!lexOrder(el1, el2))
    {
        access1->lexord = 1;
        access2->lexord = 2;
    }
    if (!el1->rw)
    { // swapp the reference;
        int ts;
        access3 = access1;
        access1 = access2;
        access2 = access3;
        nest3 = nest1;
        nest1 = nest2;
        nest2 = nest3;
    }
    bnest = commonDepth(firstcontiter1, firstcontiter); // should be the common nests see ddnests;
    access1->shareddepth = bnest;
    access2->shareddepth = bnest;
    if (el1->rw && el2->rw)
    {
        oitype = ddoutput;
        iotype = ddoutput;
    }
    else
    {
        oitype = ddflow;
        iotype = ddanti;
    }


    //  printf("Testing dependence Using Omega Test between ");
    //  el1->var->unparsestdout();
    // printf(" line %d and ", el1->stmt->lineNumber());
    //  el2->var->unparsestdout();
    //  printf(" line %d \n", el2->stmt->lineNumber());

    currentStmtIn = el1->stmt;
    currentStmtOut = el2->stmt;
    currentVarIn = el1->var;
    currentVarOut = el2->var;

    dd_omega_test(access1, access2, oitype, iotype, nest1, nest2, bnest);
    
    //check if dependensices is known;
    int result = 0;
    const std::vector<depNode*> &nodes = currentDepGraph->getNodes();
    for (int z = countOfNodes; z < nodes.size(); ++z)
    {
        if (isRemovableDependence(nodes[z], currentDepGraph->privVars) == false)
        {
            result = 5;
            break;
        }
    }
    countOfNodes = nodes.size();
    // should delete all allocated space;
#ifdef __SPF
    removeFromCollection(setForDealocatingMemory);
#endif
    delete setForDealocatingMemory;
    return result;
}

//
// indicates if a statement is before in a loop body stmt1 is assumed to be the first one
//


int beforeInText(SgStatement *func, SgStatement *stmt1, SgStatement *stmt2)
{
    SgStatement *temp, *last;

    if (!func || !stmt1 || !stmt2)
        return -1;
    last = func->lastNodeOfStmt();
    for (temp = func; temp && (temp != last); temp = temp->lexNext())
    {
        if (temp == stmt1)
            return 1;
        if (temp == stmt2)
            return 0;
    }
    Message("None of the statement where found in beforeInText", 0);
    return -1;
}


Set *computeLoopDependencies(SgStatement *func, Set *inset, SgSymbol **tsymb, Set *induc)
{

    PT_INDUCVAR       ind;
    PT_ACCESSARRAY    el1, el2;
    int i, j, k;
    int found;
    int loopnum;
    PT_DEPENDENCE     el;
    Set *depset;
    int datadep;
    int typedep;

    if (!inset || !tsymb || !induc)
        return NULL;
    // not needed anymore
    //  depset =  new Set(dependenceEqual, NULL, dependencePrint);
    WarningOutForNegativeStep = 0;

    int countOfNodes = currentDepGraph->getNodes().size();
    for (i = 0; i < inset->size(); i++)
    {
#if __SPF && NDEBUG && __BOOST
        if (passDone == 2)
            throw boost::thread_interrupted();
#endif
        el1 = (PT_ACCESSARRAY)inset->getElement(i);
        if (el1)
        {
            for (j = i; j < inset->size(); j++)
            {
                datadep = 0;
                el2 = (PT_ACCESSARRAY)inset->getElement(j);
                if (el2)
                {
                    if (el1->var && el2->var &&
                        (el1->rw || el2->rw) &&
                        (el1->var->symbol() == el2->var->symbol()))
                    {
                        int res = isDependent(el1, el2, induc, countOfNodes);
                        if (res == 5)
                        {
                            printf("Sapfor: return from computeLoopDependencies with 5 status with %d graph\n", countOfNodes);
                            return NULL;
                        }                            
                    }
                }
            }
        }
    }
    if (countOfNodes > 1000)
        printf("Sapfor: return from computeLoopDependencies with %d graph\n", countOfNodes);
    return NULL;
}
