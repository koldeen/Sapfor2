////////////////////////////////////////////////////////////////////////////////////////
/////// Interface for data dependence analysis using the attributes mechanisn///////////
///// FB. July 94 Indiana University ///////////////////////////////////////////////////

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <string>

#include "sage++user.h"
#include "depInterfaceExt.h"

//////////////////////////////////// A set of routines for interfacing the dep analysis //////////////////////////////////

static int initializeTheAnnotationSystem = 1;

void initAnnotationsSysExt(const int printannotation)
{
    if (initializeTheAnnotationSystem)
    {
        if (printannotation)
            initAnnotationSystem(1);
        else
            initAnnotationSystem(0);
        initializeTheAnnotationSystem = 0;
    }
}

void doDependenceAnalysisOnTheFullFile(SgFile *file, int printdep, int printannotation, int verbose)
{
    SgForStmt *doloop;
    int i, j, nbfunc;
    SgStatement *func, *temp, *last;
    depGraph *depg;
    depNode *datadep;
    int nbatt, typeat;

    if (!file) 
        return;
    initAnnotationsSysExt(printannotation);
    
    // delete the attributes first;
    nbfunc = file->numberOfFunctions();
    for (i = 0; i < nbfunc; i++)
    {
        func = file->functions(i);
        if (func)
        {
            last = func->lastNodeOfStmt();
            for (temp = func; temp && (temp != last); temp = temp->lexNext())
            {
                nbatt = temp->numberOfAttributes();
                for (j = 0; j < nbatt; j++)
                {
                    typeat = temp->attributeType(j);
                    if ((typeat == DEPGRAPH_ATTRIBUTE) ||
                        (typeat == INDUCTION_ATTRIBUTE) ||
                        (typeat == ACCESS_ATTRIBUTE) ||
                        (typeat == DEPENDENCE_ATTRIBUTE))
                    {
                        temp->deleteAttribute(j);
                        j--;
                    }
                }
            }
        }
    }

    nbfunc = file->numberOfFunctions();
    for (i = 0; i < nbfunc; i++)
    {
        func = file->functions(i);
        doDependenceAnalysisForAFunction(file, func, printdep, printannotation, verbose);        
    }
}



void doDependenceAnalysisForAFunction(SgFile *file, SgStatement *func, int printdep, int printannotation, int verbose)
{
    SgForStmt *doloop;
    int i, j, nbfunc;
    SgStatement  *temp, *last;
    depGraph *depg;
    depNode *datadep;
    int nbatt, typeat;

    if (!file || !func) 
        return;
    initAnnotationsSysExt(printannotation);

    last = func->lastNodeOfStmt();
    for (temp = func; temp && (temp != last); temp = temp->lexNext())
    {
        nbatt = temp->numberOfAttributes();
        for (j = 0; j < nbatt; j++)
        {
            typeat = temp->attributeType(j);
            if ((typeat == DEPGRAPH_ATTRIBUTE) ||
                (typeat == INDUCTION_ATTRIBUTE) ||
                (typeat == ACCESS_ATTRIBUTE) ||
                (typeat == DEPENDENCE_ATTRIBUTE))
            {
                temp->deleteAttribute(j);
                j--;
            }
        }
    }

    if (verbose)
        printf(" -init dependence for function %s\n", func->symbol()->identifier());

    //!!!!!!
    //TODO: add allFuncs if needed, now it does not work!
    throw(-991);
    //initializeDepAnalysisForFunction(file, func);

    //!!!!!!

    // now compute the dependence graph for each loop;
    last = func->lastNodeOfStmt();
    for (temp = func; temp && (temp != last); temp = temp->lexNext())
    {
        if (doloop = isSgForStmt(temp))
        {
            depg = new depGraph(file, func, temp, std::set<std::string>());
            if (depg)
            {
                if (printdep)
                    depg->display();

                const std::vector<depNode*> &nodes = depg->getNodes();
                
                //printf("data dep for loop on line %d is = %d\n", doloop->lineNumber(), nodes.size());
                // add the attributes here;
                /*doloop->addAttribute(DEPGRAPH_ATTRIBUTE, (void *)depg, 0);
                doloop->addAttribute(INDUCTION_ATTRIBUTE, (void *)depg->induc, 0);
                doloop->addAttribute(ACCESS_ATTRIBUTE, (void *)depg->arrayRef, 0);

                const std::vector<depNode*> &nodes = depg->getNodes();
                for (int i = 0; i < nodes.size(); ++i)
                {
                    datadep = nodes[i];
                    doloop->addAttribute(DEPENDENCE_ATTRIBUTE, (void *)datadep, 0);
                }*/

                //TODO: save needed info
                delete depg;
            }
            else
                if (verbose)
                    Message("no data dependence graph found", temp->lineNumber());
            // skip the loop;
            temp = doloop->lastNodeOfStmt();            
        }
    }
}


//
// Look in the subroutine if there is equivalence statement (drop it if yes for now)
//

int isThereEquivalenceStatement(SgStatement *func)
{
    SgStatement *temp, *last;

    if (!func)
        return FALSE;

    last = func->lastNodeOfStmt();
    for (temp = func; temp && (temp != last); temp = temp->lexNext())
    {
        if (EQUI_STAT == temp->variant())
            return TRUE;
    }
    return FALSE;
}

int isWriteToSymbolInStatement(SgSymbol *symb, SgStatement *loop, depGraph *depg)
{
    int i;
    PT_ACCESSARRAY access1;

    for (i = 0; i < depg->arrayRef->size(); i++)
    {
        access1 = (PT_ACCESSARRAY)depg->arrayRef->getElement(i);
        if (loop->isIncludedInStmt(*(access1->stmt)))
        {
            if (access1 && access1->scalar && access1->rw)
            {
                if (access1->var->symbol() == symb)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

//
// take a data dep and return the first dimension with a non zero distance
//

int leadingDimension(depNode *datadep, int entryLevel)
{
    int i, j;
    int carried;
    if (!datadep)
        return 0;


    if (datadep->typedep == ARRAYDEP)
    {
        if (entryLevel)
        { // check that the dependence is not carried by the outer loops first
            for (i = 1; (i <= datadep->lenghtvect) && (i <= entryLevel); i++)
            {
                if (datadep->knowndist[i])
                {
                    if (datadep->distance[i] != 0)
                    {
                        return datadep->lenghtvect;
                    }
                }
                else
                {
                    if (!(datadep->distance[i] & DEPZERO))
                    {
                        return datadep->lenghtvect;
                    }
                }
            }
        }

        for (i = 1 + entryLevel; i <= datadep->lenghtvect; i++)
        {
            if (datadep->knowndist[i])
            {
                if (datadep->distance[i] != 0)
                {
                    return i - 1;
                }
            }
            else
            {
                if ((datadep->distance[i] & DEPGREATER) ||
                    (datadep->distance[i] & DEPLESS))
                {
                    return i - 1;
                }
            }
        }
        return datadep->lenghtvect;
    }
    else
        return 0;
}

int numberOfOuterParallelLoops(SgStatement *loop, depGraph *depg, int entryLevel)
{
    depNode *datadep;
    int Min, t;

    if (!loop)
        return 0;
    Min = MAXNESTEDLOOP;

    const std::vector<depNode*> &nodes = depg->getNodes();
    for (int i = 0; i < nodes.size(); ++i)
    {
        datadep = nodes[i];
        if (datadep->typedep == ARRAYDEP)
        {
            // source and sink must be included in the loop;
            if (datadep->stmtin && datadep->stmtout &&
                loop->isIncludedInStmt(*(datadep->stmtin)) &&
                loop->isIncludedInStmt(*(datadep->stmtout)))
            {
                t = leadingDimension(datadep, entryLevel);
                if (t < Min)
                    Min = t;
            }
        }
    }
    return Min - entryLevel;
}


