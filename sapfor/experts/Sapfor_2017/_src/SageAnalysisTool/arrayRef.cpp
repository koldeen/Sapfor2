#include <stdio.h>
#include <malloc.h>
#include <set>
#include <string>

#include "sage++user.h"
#include "definesValues.h"
#include "set.h"
#include "definitionSet.h"
#include "inducVar.h"

#include "arrayRef.h"

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif

int NbLinearRef = 0;
int NbNonLinearRef = 0;

extern Set *genSet[MAXNODE];
extern Set *killSet[MAXNODE];
extern Set *inSet[MAXNODE];
extern Set *outSet[MAXNODE];


extern Set* getAllInductionVar(SgStatement *func, SgStatement *stmt, int level, int *num, int include);

using std::set;
using std::string;
//
// for an array ref build the linear representation
// return 0 if failed
//

int linearRepArray(SgExpression  *ex1, SgSymbol **symb, int size, int linear[MAXDIMARRAY][MAXNESTEDLOOP], int *cst, int isLinear[MAXDIMARRAY])
{
    SgArrayRefExp *ar;
    SgExpression  *lin;
    int i;
    int returnVal;

    if (!ex1 || !symb || !cst)
        return 0;

    if (!(ar = isSgArrayRefExp(ex1)))
        return 0;
    returnVal = 1;
    for (i = 0; i < ar->numberOfSubscripts(); i++)
    {
        lin = ar->subscript(i);
        isLinear[i] = 1;
        if (!lin)
        {
            returnVal = 0;
            isLinear[i] = 0;
        }
        else
            if (!lin->linearRepresentation(linear[i], symb, &cst[i], size))
            {
                returnVal = 0;
                isLinear[i] = 0;
            }

    }
    return returnVal;
}


//
// Set Operations
//
int arrayEqual(void *e1, void *e2)
{
    SgExpression *ex1, *ex2;
    SgSymbol     *s1, *s2;
    PT_ACCESSARRAY     el1, el2;
    int i;
    if (!e1 && !e2)
        return 1;
    if (!e1 || !e2)
        return 0;

    el1 = (PT_ACCESSARRAY)e1;
    el2 = (PT_ACCESSARRAY)e2;

    ex1 = el1->var;
    ex2 = el2->var;

    if (el1->type != el2->type)
        return 0;

    if (ex1 && ex2 && (s1 = ex1->symbol()) && (s2 = ex2->symbol()))
    {
        if (s1 != s2)
            return 0;
        // need to check more, at which condition, two sections are equal;
        // pattern matching should be ok;
    }

    return 1;
}

void arrayPrint(void *e1)
{
    SgExpression *ex1;
    PT_ACCESSARRAY   el1;
    int i, j;
    if (!e1)
        return;
    el1 = (PT_ACCESSARRAY)e1;
    ex1 = el1->var;
    printf("%d :", el1->level);
    ex1->unparsestdout();
    printf("\n");
    if (el1->scalar)
        printf("scalar variable\n");
    if (el1->rw)
        printf("written\n");
    else
        printf("read\n");
    if (el1->type)
        printf("Linear\n");
    for (i = 0; i < MAXDIMARRAY; i++)
    {
        if (el1->isLinear[i])
        {
            printf("Linear (%d) :", i);
            for (j = 0; j < el1->size; j++)
                printf("%d  ", el1->linear[i][j]);
            printf(" cst = %d", el1->cst[i]);
            printf("\n");
        }
        else
            printf("NonLinear (%d) \n", i);
    }

    printf("\n");
}


// this function should be extended to handle non loop statement...
Set *loopArrayAccessAnalysis(SgStatement *func, SgStatement *stmt, SgSymbol **tsymb, Set **induc, const set<string> &privVars)
{
    Set               *inducvar, *cstset, *tpt, *arset;
    SgStatement       *temp1, *temp2, *last;
    SgExpression      *def1, *def2, *use1, *use2;
    SgExpression      *ex1, *ex2, *r1, *r2;
    int               linear1[MAXDIMARRAY][MAXNESTEDLOOP];
    int               i, j, size, res1, res2, cst1[MAXDIMARRAY];
    int               level, ptstack = 0, LevStack[MAXNESTEDLOOP], nbloop;
    PT_INDUCVAR       ind;
    PT_ACCESSARRAY    el;
    int                numloop = 0;
    int isLinear[MAXDIMARRAY];

    if (!isSgForStmt(stmt) || !func)
        return NULL;
    last = stmt->lastNodeOfStmt();
    // get induction variables;
    inducvar = getAllInductionVar(func, stmt, 1, &numloop, -1);
    // add the constante to the induction set variable;
    // cstset = computeConstanteInStmt(func,stmt);
    //   if (cstset)
    //     cstset->printSet();
    //   inducvar->unionSet(cstset);
    //   delete cstset;
    if (!inducvar)
    {
        Message("no induction variables", stmt->lineNumber());
        return NULL;
    }

    // load the array of symbol with induction var;
    if (inducvar->size() >= MAXNESTEDLOOP)
    {
        Message("Too many induction variables\n", stmt->lineNumber());
        return NULL;
    }
    tpt = inducvar;
    inducvar = inducvar->compact();
#ifdef __SPF
    removeFromCollection(tpt);
#endif
    delete tpt;
    *induc = inducvar;
    arset = new Set(arrayEqual, NULL, arrayPrint);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, arset, 1);
#endif
    size = inducvar->size();
    for (i = 0; i < inducvar->size(); i++)
    {
        ind = (PT_INDUCVAR)inducvar->getElement(i);
        if (ex2 = ind->var)
        {
            tsymb[i] = ex2->symbol();
        }
    }
    // get all array references, there are contained in the Defined Used set;
    level = 0;
    nbloop = 0;
    for (temp1 = stmt; temp1 && (temp1 != last); temp1 = temp1->lexNext())
    {
        if (isSgForStmt(temp1))
        {
            nbloop++;
            ptstack++;
            if (ptstack >= MAXNESTEDLOOP)
                Message("Stack out of bound in loopArrayAccessAnalysis", 0);
            LevStack[ptstack] = nbloop;
            level = nbloop;
        }

        if (isSgControlEndStmt(temp1) || isSgContinueStmt(temp1))
        {
            if (temp1->controlParent() && (temp1->controlParent()->variant() == FOR_NODE) && (temp1->controlParent()->lastNodeOfStmt() == temp1))
            {
                ptstack--;
                if (ptstack <= 0)
                    Message("Stack out of bound in loopArrayAccessAnalysis", 0);
                level = LevStack[ptstack];
            }
        }

        for (def1 = (SgExpression *)temp1->attributeValue(0, DEFINEDLIST_ATTRIBUTE); def1; def1 = def1->rhs())
            //Defined[temp1->id()]; def1; def1 = def1->rhs())
        {
            for (i = 0; i < MAXDIMARRAY; i++)
            {
                cst1[i] = 0;
                isLinear[i] = 1;
                for (j = 0; j < MAXNESTEDLOOP; j++)
                    linear1[i][j] = 0;
            }
            ex1 = def1->lhs();
            if (isSgArrayRefExp(ex1))
            {
                if (privVars.find(ex1->symbol()->identifier()) == privVars.end())
                {
                    res1 = linearRepArray(ex1, tsymb, size, linear1, cst1, isLinear);
                    el = new struct  arrayAccess;
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, el, 1);
#endif
                    for (i = 0; i < MAXDIMARRAY; i++)
                    {
                        el->isLinear[i] = isLinear[i];
                        for (j = 0; j < MAXNESTEDLOOP; j++)
                            el->linear[i][j] = linear1[i][j];
                        el->cst[i] = cst1[i];
                    }
                    // add the ref;
                    el->stmt = temp1;
                    el->nbdim = MAXDIMARRAY;
                    el->var = ex1;
                    el->type = res1;
                    if (res1)
                        NbLinearRef++;
                    else
                        NbNonLinearRef++;
                    el->size = size;
                    el->rw = 1; // this is a write;
                    el->scalar = 0; // not a scalar var;
                    el->level = level;
                    arset->addElement((void *)el);
                }
            }
            else
            {
                SgSymbol   *ssy;
                int l, trouve;
                // if non induction var ;
                if (!isSgTypeExp(ex1))
                {
                    ssy = ex1->symbol();
                    trouve = 0;
                    for (l = 0; l < size; l++)
                    {
                        if (ssy == tsymb[l])
                        {
                            trouve = 1;
                            break;
                        }
                    }
                }
                else
                    trouve = 1;
                if (!trouve)
                {
                    el = new struct  arrayAccess;
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, el, 1);
#endif
                    // add the ref;
                    el->stmt = temp1;
                    el->var = ex1;
                    el->nbdim = 0;
                    el->type = 0;
                    el->size = 0;
                    el->rw = 1; // this is a write;
                    el->level = level;
                    el->scalar = 1; // not a scalar var;
                    arset->addElement((void *)el);
                }
            }
        }

        for (use1 = (SgExpression *)temp1->attributeValue(0, USEDLIST_ATTRIBUTE); use1; use1 = use1->rhs())
            //  Used[temp1->id()]; use1; use1 = use1->rhs())
        {
            for (i = 0; i < MAXDIMARRAY; i++)
            {
                cst1[i] = 0;
                isLinear[i] = 1;
                for (j = 0; j < MAXNESTEDLOOP; j++)
                    linear1[i][j] = 0;
            }

            ex1 = use1->lhs();
            if (isSgArrayRefExp(ex1))
            {
                if (privVars.find(ex1->symbol()->identifier()) == privVars.end())
                {
                    res1 = linearRepArray(ex1, tsymb, size, linear1, cst1, isLinear);

                    el = new struct arrayAccess;
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, el, 1);
#endif
                    for (i = 0; i < MAXDIMARRAY; i++)
                    {
                        el->isLinear[i] = isLinear[i];
                        for (j = 0; j < MAXNESTEDLOOP; j++)
                            el->linear[i][j] = linear1[i][j];
                        el->cst[i] = cst1[i];
                    }
                    // add the ref;
                    el->stmt = temp1;
                    el->var = ex1;
                    el->nbdim = MAXDIMARRAY;
                    el->type = res1;
                    if (res1)
                        NbLinearRef++;
                    else
                        NbNonLinearRef++;
                    el->size = size;
                    el->rw = 0; // this is a read;
                    el->scalar = 0; // not a scalar var;
                    el->level = level;
                    arset->addElement((void *)el);
                }
            }
            else
            {
                SgSymbol   *ssy;
                int l, trouve;
                if (!isSgTypeExp(ex1))
                {
                    // if non induction var ;
                    ssy = ex1->symbol();
                    trouve = 0;
                    for (l = 0; l < size; l++)
                    {
                        if (ssy == tsymb[l])
                        {
                            trouve = 1;
                            break;
                        }
                    }
                }
                else
                    trouve = 1;
                if (!trouve)
                {
                    el = new struct arrayAccess;
#ifdef __SPF
                    addToCollection(__LINE__, __FILE__, el, 1);
#endif
                    // add the ref;
                    el->stmt = temp1;
                    el->var = ex1;
                    el->nbdim = 0;
                    el->type = 0;
                    el->size = 0;
                    el->level = level;
                    el->rw = 0; // this is a read;
                    el->scalar = 1; // not a scalar var;
                    arset->addElement((void *)el);
                }
            }
        }
    }
    return arset;
}


int
projectoPermut(PT_ACCESSARRAY el1)
{
    SgSymbol *inducsy;
    int i, j, k;
    PT_INDUCVAR       ind, cur;
    int temp;

    if (!el1)
        return 0;
    if (!el1->type)
        return 0; // non linear;
    for (j = 0; j < el1->size; j++)
    {
        temp = 0;
        for (k = 0; k < MAXDIMARRAY; k++)
        {
            if (el1->linear[k][j] != 0)
            {
                if (temp)
                    return 0;
                temp = 1;
            }
        }
    }
    for (k = 0; k < MAXDIMARRAY; k++)
    {
        temp = 0;
        for (j = 0; j < el1->size; j++)
        {
            if (el1->linear[k][j] != 0)
            {
                if (temp)
                    return 0;
                temp = 1;
            }
        }
    }
    return 1;
}


//
// Between two references is there temporal locality. Limited to permutation o projection
//

int
temporalLocality(PT_ACCESSARRAY el1, SgSymbol **tsymb, Set *induc)
{
    SgSymbol *inducsy;
    int j, k;
    PT_INDUCVAR       ind, cur;
    int loopnum;
    int temporal, temp;

    if (!el1 || !induc || !tsymb)
        return 0;
    inducsy = NULL;
    loopnum = el1->level;
    for (j = 0; j < induc->size(); j++)
    {
        ind = (PT_INDUCVAR)induc->getElement(j);
        if (ind && (ind->loopnum == loopnum))
        {
            inducsy = ind->var->symbol();
            cur = ind;
            break;
        }
    }
    temporal = 0;
    // this is the induction var of the loop.
    if (inducsy)
    {
        while (cur)
        {
            for (j = 0; j < el1->size; j++)
            {
                if (tsymb[j] == inducsy)
                    break;
            } // we have the symbol;
            if (j < el1->size)
            {
                temp = 1;
                for (k = 0; k < MAXDIMARRAY; k++)
                {
                    if (el1->linear[k][j] != 0)
                    {
                        temp = 0;
                    }
                }
                if (temp)
                    temporal = 1;

            }
            if (cur->include == -1)
                break;
            // compute the next one;
            for (j = 0; j < induc->size(); j++)
            {
                ind = (PT_INDUCVAR)induc->getElement(j);

                if (ind && (ind->loopnum == cur->include))
                {
                    inducsy = ind->var->symbol();
                    cur = ind;
                    break;
                }
            }
        }
    }
    return temporal;
}

int
spatialLocality(PT_ACCESSARRAY el1, SgSymbol **tsymb, Set *induc, int CacheLIneSize)
{
    SgSymbol *inducsy;
    int j, k;
    PT_INDUCVAR       ind, cur;
    int loopnum;
    int spatial, temp;

    if (!el1 || !induc || !tsymb)
        return 0;
    inducsy = NULL;
    loopnum = el1->level;
    for (j = 0; j < induc->size(); j++)
    {
        ind = (PT_INDUCVAR)induc->getElement(j);
        if (ind && (ind->loopnum == loopnum))
        {
            inducsy = ind->var->symbol();
            cur = ind;
            break;
        }
    }
    spatial = 0;
    // this is the induction var of the loop.
    if (inducsy)
    {
        // look at  in the dimension where the variable appear;
        spatial = 1;
        // the first dimension is fine where is the column of the symbole;
        for (j = 0; j < el1->size; j++)
        {
            if (tsymb[j] == inducsy)
                break;
        }
        if (j < el1->size)
        {
            for (k = 1; k < MAXDIMARRAY; k++)
            {
                if (el1->linear[k][j] != 0)
                {
                    spatial = 0;
                    break;
                }
            }
            if (el1->linear[0][j] > CacheLIneSize)
                spatial = 0;
        }
        else
        {
            spatial = 0;
        }
    }
    return spatial;
}



int
spatialNonSelfLocality(PT_ACCESSARRAY el1, PT_ACCESSARRAY el2, SgSymbol **tsymb, Set *induc, int CacheLIneSize)
{
    SgSymbol *inducsy;
    int j, k;
    PT_INDUCVAR       ind, cur;
    int loopnum;
    int spatial, temp;

    if (!el1 || !el2 || !induc || !tsymb)
        return 0;
    inducsy = NULL;
    if (el1->level != el2->level)
        return 0;
    if (!el1->var || !el2->var)
        return 0;
    if (el1->var->symbol() != el2->var->symbol())
        return 0;
    // do they have the same function
    for (k = 0; k < MAXDIMARRAY; k++)
    {
        for (j = 0; j < el1->size; j++)
        {
            if (el1->linear[k][j] != el2->linear[k][j])
            {
                return 0;
            }
        }
    }
    for (k = 1; k < MAXDIMARRAY; k++)
    {
        if (el1->cst[k] != el2->cst[k])
        {
            return 0;
        }
    }
    spatial = el1->cst[0] - el2->cst[0];
    if (spatial < 0)
        spatial = -spatial;
    if (spatial >= CacheLIneSize)
        return 0;

    return 1;
}



int
TemporalNonSelfLocality(PT_ACCESSARRAY el1, PT_ACCESSARRAY el2, SgSymbol **tsymb, Set *induc)
{
    SgSymbol *inducsy;
    int j, k;
    PT_INDUCVAR       ind, cur;
    int loopnum;
    int spatial, temp;
    int flag;
    if (!el1 || !el2 || !induc || !tsymb)
        return 0;
    inducsy = NULL;
    if (el1->level != el2->level)
        return 0;
    if (!el1->var || !el2->var)
        return 0;
    if (el1->var->symbol() != el2->var->symbol())
        return 0;
    // do they have the same function
    for (k = 0; k < MAXDIMARRAY; k++)
    {
        for (j = 0; j < el1->size; j++)
        {
            if (el1->linear[k][j] != el2->linear[k][j])
            {
                return 0;
            }
        }
    }
    // is there one reference with only one constant different
    flag = 0;
    for (k = 0; k < MAXDIMARRAY; k++)
    {
        if (el1->cst[k] != el2->cst[k])
        {
            if (flag)
                return 0;
            flag = k + 1;
        }
    }
    if (flag)
    {
        // check first that the coefficient is not NULL;
        for (j = 0; j < el1->size; j++)
        {
            if (el1->linear[flag - 1][j] != 0)
                return 1;
        }
        return 0;
    }
    else
        return 0;  // that case is considered elsewhere
}


int
isLinearEqual(int size1, int size2, int linear1[MAXDIMARRAY][MAXNESTEDLOOP], int *cst1, int linear2[MAXDIMARRAY][MAXNESTEDLOOP], int *cst2)
{
    int i, j;
    if (!linear1 || !linear2 || !cst1 || !cst2)
        return 0;
    if (size1 != size2)
        return 0;
    for (i = 0; i < MAXDIMARRAY; i++)
    {
        if (cst1[i] != cst2[i])
            return 0;
        for (j = 0; j < size1; j++)
        {
            if (linear1[i][j] != linear2[i][j])
                return 0;
        }
    }
    return 1;
}


int
isLinearEqualNoCst(int size1, int size2, int linear1[MAXDIMARRAY][MAXNESTEDLOOP], int linear2[MAXDIMARRAY][MAXNESTEDLOOP])
{
    int i, j;
    if (!linear1 || !linear2)
        return 0;
    if (size1 != size2)
        return 0;
    for (i = 0; i < MAXDIMARRAY; i++)
    {
        for (j = 0; j < size1; j++)
        {
            if (linear1[i][j] != linear2[i][j])
                return 0;
        }
    }
    return 1;
}

int
isNull(int size, int linear[MAXNESTEDLOOP])
{
    int i;
    if (!linear)
        return 1;
    for (i = 0; i < size; i++)
    {
        if (linear[i] != 0)
            return 0;
    }
    return 1;
}
