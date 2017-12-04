#include "../leak_detector.h"

#include <cstdio>
#include <cstring>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>

#include "dvm.h"
#include "enddo_loop_converter.h"
#include "../errors.h"
#include "../utils.h"

using namespace std;

static vector<Messages> *currMessages;
static set<int> allLables;

static void copyLabelAndComentsToNext(SgStatement *curr)
{
    if (curr->hasLabel())
        curr->lexNext()->setLabel(*curr->label());
    if (curr->comments())
        curr->lexNext()->setComments(curr->comments());
}

static SgLabel* getUniqLabel(unsigned was)
{
    while (1)
    {
        was++;
        if (allLables.find(was) == allLables.end())
            break;
    }

    SgLabel *ret = new SgLabel(was);
    return ret;
}

static void tryToCorrectLoop(SgForStmt *&forSt, map<SgForStmt*, SgLabel*> &endOfLoops)
{
    SgLabel *tmp = endOfLoops[forSt];    
    SgStatement *curr = forSt->lexNext();
    SgStatement *lastNode;

    // find the last node of this FOR with label
    while (curr)
    {
        if (curr->hasLabel())
            if (curr->label() == tmp)
                break;
        curr = curr->lexNext();
    }
    lastNode = curr;

    // replace last node with CONTINUE with NEW label and replace all FOR labels to new label
    lastNode->insertStmtAfter(*new SgContinueStmt(), *(curr->controlParent()));
    SgStatement *next = lastNode->lexNext();

    SgLabel *newLab = getUniqLabel(curr->label()->getLabNumber());
    next->setLabel(*newLab);
    lastNode = next;

    curr = forSt;
    while (curr != lastNode)
    {        
        if (curr->variant() == FOR_NODE || curr->variant() == WHILE_NODE)
        {
            SgLabel *currLab = ((SgForStmt*)curr)->endOfLoop();
            if (currLab)
                if (currLab->getLabNumber() == tmp->getLabNumber())
                    BIF_LABEL_USE(curr->thebif) = newLab->thelabel;
        }
        curr = curr->lexNext();
    }

    curr = forSt->lexNext();
    // convert all arithmetic if to simple if with goto
    while (curr != lastNode)
    {
        if (curr->variant() == ARITHIF_NODE)
        {
            const int lineNum = curr->lineNumber();

            SgExpression *cond = curr->expr(0);
            SgExpression *lb = curr->expr(1);
            SgLabel *arith_lab[3];

            int i = 0;
            while (lb)
            {
                SgLabel *lab = ((SgLabelRefExp *)(lb->lhs()))->label();
                arith_lab[i] = lab;
                i++;
                lb = lb->rhs();
            }

            SgStatement *replaceSt = 
                    new SgIfStmt(*cond < *new SgValueExp(0), 
                                 *new SgGotoStmt(*arith_lab[0]), 
                                 *new SgIfStmt(SgEqOp(*cond, *new SgValueExp(0)), *new SgGotoStmt(*arith_lab[1]), *new SgGotoStmt(*arith_lab[2])));

            curr->insertStmtAfter(*replaceSt, *curr->controlParent());
            copyLabelAndComentsToNext(curr);

            SgStatement *toDel = curr;
            curr = curr->lexNext();
            toDel->deleteStmt();

            char buf[512];
            sprintf(buf, "converted arithmetic IF to simple IF on line %d\n", lineNum);
            addToGlobalBufferAndPrint(buf);

            sprintf(buf, "converted arithmetic IF to simple I");
            currMessages->push_back(Messages(NOTE, lineNum, buf));

            continue;
        }
        curr = curr->lexNext();
    }
}

static void tryToConverLoop(SgForStmt *&forSt, map<SgForStmt*, SgLabel*> &endOfLoops)
{
    const int lineNum = forSt->lineNumber();
    if (forSt->isEnddoLoop() == false)
    {        
        int result = forSt->convertLoop();
        if (result == 0)
        {    
            tryToCorrectLoop(forSt, endOfLoops);
            result = forSt->convertLoop();
            if (result == 0)
            {
                char buf[512];
                sprintf(buf, "ERROR: can not convert to END DO loop on line %d\n", lineNum);
                addToGlobalBufferAndPrint(buf);

                sprintf(buf, "can not convert to END DO loop\n");
                currMessages->push_back(Messages(ERROR, lineNum, buf));
            }
        }

        if (result > 0)
        {
            char buf[512];
            sprintf(buf, "converted to END DO loop on line %d\n", lineNum);
            addToGlobalBufferAndPrint(buf);

            sprintf(buf, "converted to END DO loop\n");
            currMessages->push_back(Messages(NOTE, lineNum, buf));
        }
    }
}

static void getAllLabels(SgFile *file)
{
    allLables.clear();
    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        while (st && st != lastNode)
        {
            if (st->hasLabel())
            {
                SgLabel *lab = st->label();
                if (lab)
                    allLables.insert(lab->getLabNumber());
            }
            st = st->lexNext();
        }
    }
}

static void fillEndOfLoop(SgStatement *st, map<SgForStmt*, SgLabel*> &endOfLoops, map<int, SgForStmt*> &toProcessLoops)
{
    SgStatement *lastNode = st->lastNodeOfStmt();
    while (st && st != lastNode)
    {
        if (st->variant() == FOR_NODE)
        {
            SgForStmt *forSt = (SgForStmt*)st;
            if (forSt->isEnddoLoop() == false)
            {
                SgLabel *endOfLoop = forSt->endOfLoop();
                if (endOfLoop != NULL)
                {
                    endOfLoops[forSt] = endOfLoop;
                    auto it = toProcessLoops.find(endOfLoop->getLabNumber());
                    if (it == toProcessLoops.end())
                        toProcessLoops.insert(it, make_pair(endOfLoop->getLabNumber(), forSt));
                }
                else
                    __spf_print(1, " Can not find end of labeled loop on line %d\n", forSt->lineNumber());
            }            
        }
        st = st->lexNext();
    }
}

void ConverToEndDo(SgFile *file, vector<Messages> &messagesForFile)
{    
    currMessages = &messagesForFile;
    getAllLabels(file);

    int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        vector<SgForStmt*> parentLoops;

        map<SgForStmt*, SgLabel*> endOfLoops;
        map<int, SgForStmt*> toProcessLoops;
        fillEndOfLoop(st, endOfLoops, toProcessLoops);

        for (auto it = toProcessLoops.begin(); it != toProcessLoops.end(); ++it)
            tryToConverLoop(it->second, endOfLoops);
    }
}
