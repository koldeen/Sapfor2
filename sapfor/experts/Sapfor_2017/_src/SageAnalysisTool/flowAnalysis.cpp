#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "sage++user.h"
#include "definesValues.h"
#include "set.h"

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif

//
// Control FLOW part of declaration
//

extern void controlFlow(SgStatement *stmt, SgStatement *func,
    SgStatement **pred, SgStatement **suc,
    int *predin, int *sucint);

Set *genSet[MAXNODE];
Set *killSet[MAXNODE];
Set *inSet[MAXNODE];
Set *outSet[MAXNODE];

//
// Main function for data flow analysis, take some functions as a parameter 
//


void iterativeForwardFlowAnalysis(SgFile *file,
    SgStatement *func,
    Set *(*giveGenSet)(SgStatement *func, SgStatement *stmt),
    Set *(*giveKillSet)(SgStatement *func, SgStatement *stmt),
    int(*feq)(void *e1, void *e2),
    void *(*fcomb)(void *e1, void *e2),
    void(*fp)(void *e1))
{
    SgStatement *last, *first, *lastfunc, *temp;
    SgStatement *pred[MAXP], *suc[MAXP];
    int nbpred, nbsuc;
    int size, i, j;
    Set *tps, *oldout, *tpt, *pt1, *pt2, *comb;
    int change, step;
    int cid;
    if (!file || !func || !giveGenSet || !giveKillSet)
    {
        Message("iterativeForwardFlowAnalysis: Some Argument are NULL", 0);
        return;
    }
    lastfunc = func->lastNodeOfStmt();
    // should use the max id instead;
    for (i = 0; i < MAXNODE; i++)
    {
        genSet[i] = NULL;
        killSet[i] = NULL;
        outSet[i] = NULL;
        inSet[i] = NULL;
    }
    // initialize the gen and kill set;
    for (temp = func; temp; temp = temp->lexNext())
    {
        if (temp->id() > MAXNODE)
        {
            Message("Too many nodes in program: Fatal", 0);
            exit(1);
        }
        genSet[temp->id()] = (*giveGenSet)(func, temp);
        killSet[temp->id()] = (*giveKillSet)(func, temp);
        if (temp == lastfunc)
            break;
    }
    // initialize the out set;
    for (temp = func; temp; temp = temp->lexNext())
    {
        if (genSet[temp->id()])
        {
            pt2 = genSet[temp->id()];
            outSet[temp->id()] = pt2->copy();
        }
        else
            outSet[temp->id()] = NULL;
        inSet[temp->id()] = NULL;
        if (temp == lastfunc)
            break;
    }
    change = 1;
    step = 0;
    while (change)
    {
        step++;
        change = 0;
        for (temp = func; temp; temp = temp->lexNext())
        {
            cid = temp->id();
            controlFlow(temp, func, pred, suc, &nbpred, &nbsuc);
            if (inSet[cid])
            {
#ifdef __SPF
                removeFromCollection(inSet[cid]);
#endif
                delete inSet[cid];
            }
            tps = new Set(feq, fcomb, fp);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, tps, 1);
#endif
            for (i = 0; i < nbpred; i++)
            {
                tps->unionSet(outSet[pred[i]->id()]);
            }

            inSet[cid] = tps;

            oldout = outSet[cid];
            outSet[cid] = new Set(feq, fcomb, fp);
            tpt = new Set(feq, fcomb, fp);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, outSet[cid], 1);
            addToCollection(__LINE__, __FILE__, tpt, 1);
#endif
            tpt->diffSet(inSet[cid], killSet[cid]);

            outSet[cid]->unionSet(genSet[cid]);
            outSet[cid]->unionSet(tpt);
            pt1 = outSet[cid];
            outSet[cid] = pt1->compact();
#ifdef __SPF
            removeFromCollection(pt1);
#endif
            delete pt1;
            if (!oldout && outSet[cid])
                change = 1;
            else
                if (!oldout->equalSet(outSet[cid]))
                    change = 1;
            if (oldout)
            {
#ifdef __SPF
                removeFromCollection(oldout);
#endif
                delete oldout;
            }
            if (tpt)
            {
#ifdef __SPF
                removeFromCollection(tpt);
#endif
                delete tpt;
            }

            if (temp == lastfunc)
                break;
        }
        if (step > MAXITDATAFLOW)
        {
            Message("data flow analysis not converging", 0);
            return;
        }
        printf("Data flow analysis at step %d\n", step);
    }
}

//
// Iterative Algorithme for General Frameworks page 690 Aho Ullman
// out is initialise to transfertSet(NULL). in is initialized to NULL (this is T).
// combineSet() is the meet operator (take as input the union or output...)
//

void generalIterativeFlowAnalysis(SgFile *file,
    SgStatement *func,
    Set *(*transfertSet)(SgStatement *func, SgStatement *stmt, Set *setin),
    int(*feq)(void *e1, void *e2),
    void* (*fcomb)(void *e1, void *e2),
    void(*fp)(void *e1))
{
    SgStatement *last, *first, *lastfunc, *temp;
    SgStatement *pred[MAXP], *suc[MAXP];
    int nbpred, nbsuc;
    int size, i, j;
    Set *tps, *oldout, *tpt, *pt1, *pt2, *comb;
    int change, step;
    int cid;
    if (!file || !func || !transfertSet)
    {
        Message("generalIterativeFlowAnalysis: Some Arguments are NULL", 0);
        return;
    }
    lastfunc = func->lastNodeOfStmt();
    // should use the max id instead;
    for (i = 0; i < MAXNODE; i++)
    {
        genSet[i] = NULL;
        killSet[i] = NULL;
        outSet[i] = NULL;
        inSet[i] = NULL;
    }
    // initialize the out Set
    for (temp = func; temp; temp = temp->lexNext())
    {
        if (temp->id() > MAXNODE)
        {
            Message("Too many nodes in program: Fatal", 0);
            exit(1);
        }
        outSet[temp->id()] = (*transfertSet)(func, temp, NULL);
        if (temp == lastfunc)
            break;
    }
    change = 1;
    step = 0;
    while (change)
    {
        step++;
        change = 0;
        for (temp = func; temp; temp = temp->lexNext())
        {
            cid = temp->id();
            controlFlow(temp, func, pred, suc, &nbpred, &nbsuc);
            if (inSet[cid])
            {
#ifdef __SPF
                removeFromCollection(inSet[cid]);
#endif            
                delete inSet[cid];
            }
            tps = new Set(feq, fcomb, fp);
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, tps, 1);
#endif
            for (i = 0; i < nbpred; i++)
            {
                tps->unionSet(outSet[pred[i]->id()]);
            }
            tpt = tps;
            tps = tps->combineSet();
            inSet[cid] = tps;
            if (tpt)
            {
#ifdef __SPF
                removeFromCollection(tpt);
#endif
                delete tpt;
            }

            oldout = outSet[cid];
            outSet[cid] = (*transfertSet)(func, temp, inSet[cid]);
            if (!oldout && outSet[cid])
            {
                change = 1;
                //              printf ("old out is NULL (line %d)\n", temp->lineNumber());
            }
            else
                if (!oldout->equalSet(outSet[cid]))
                {
                    //                printf ("-------debug ouput (line %d)-----------: \n", temp->lineNumber());
                    //                printf ("oldout: \n");
                    //                oldout->printSet();
                    //                printf ("out: \n");
                    //                if (outSet[cid])
                    //                  outSet[cid]->printSet();
                    change = 1;
                }
            if (oldout)
            {
#ifdef __SPF
                removeFromCollection(oldout);
#endif
                delete oldout;
            }
            if (temp == lastfunc)
                break;
        }
        if (step > MAXITDATAFLOW)
        {
            Message("data flow analysis not converging", 0);
            return;
        }
        printf("Data flow analysis at step %d\n", step);
    }
}
