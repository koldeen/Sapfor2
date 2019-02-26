#include "../Utils/leak_detector.h"

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
#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"

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

static void makeDeclaration(SgStatement *curr, SgSymbol *s)
{
    SgStatement *decl = s->makeVarDeclStmt();
    SgStatement *place = curr;
    while (place->variant() != PROG_HEDR && place->variant() != PROC_HEDR && place->variant() != FUNC_HEDR)
        place = place->controlParent();
    auto scope = place;
    while (isSgExecutableStatement(place) == NULL)
        place = place->lexNext();
    place->insertStmtBefore(*decl, *scope);
}

static vector<SgStatement*> convertArithIf(SgStatement *curr)
{
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

    SgStatement *replaceSt;

    SgType *type = NULL;
    if (cond->type())
        type = cond->type();
    else
        type = SgTypeInt();

    auto condS = new SgSymbol(VARIABLE_NAME, ("arithIfCond" + std::to_string(curr->lineNumber())).c_str(), type, curr->getScopeForDeclare());
    SgStatement *assignCond = new SgAssignStmt(*new SgVarRefExp(*condS), *cond);

    makeDeclaration(curr, condS);

    if (arith_lab[1]->getLabNumber() == arith_lab[2]->getLabNumber())
        replaceSt = new SgIfStmt(*new SgVarRefExp(*condS) < *new SgValueExp(0), *new SgGotoStmt(*arith_lab[0]), *new SgGotoStmt(*arith_lab[1]));
    else
        replaceSt = new SgIfStmt(*new SgVarRefExp(*condS) < *new SgValueExp(0),
                    *new SgGotoStmt(*arith_lab[0]),
                    *new SgIfStmt(*new SgVarRefExp(*condS) == *new SgValueExp(0), *new SgGotoStmt(*arith_lab[1]), *new SgGotoStmt(*arith_lab[2])));

    return { assignCond, replaceSt };
}

static vector<SgStatement*> convertComGoto(SgStatement *curr)
{
    SgExpression *cond = curr->expr(1);
    SgExpression *lb = curr->expr(0);
    vector<SgLabel*> labs;

    while (lb)
    {
        labs.push_back(((SgLabelRefExp *)(lb->lhs()))->label());
        lb = lb->rhs();
    }

    SgStatement *replace = NULL;

    auto condS = new SgSymbol(VARIABLE_NAME, ("comGotoCond" + std::to_string(curr->lineNumber())).c_str(), SgTypeInt(), curr->getScopeForDeclare());
    SgStatement *assignCond = new SgAssignStmt(*new SgVarRefExp(*condS), *cond);
    
    makeDeclaration(curr, condS);
       
    if (labs.size() == 1)
        replace = new SgIfStmt(*new SgVarRefExp(*condS) == *new SgValueExp(1), *new SgGotoStmt(*labs[0]));
    else
        replace = new SgIfStmt(*new SgVarRefExp(*condS) == *new SgValueExp((int)labs.size()), *new SgGotoStmt(*labs.back()));
        
    for (int z = (int)labs.size() - 2; z >= 0; --z)
        replace = new SgIfStmt(*new SgVarRefExp(*condS) == *new SgValueExp(z + 1), *new SgGotoStmt(*labs[z]), *replace);
    
    return { assignCond, replace };
}

template<vector<SgStatement*> funcConv(SgStatement*)>
static void convert(SgStatement *&curr, const string &message)
{
    const int lineNum = curr->lineNumber();
    vector<SgStatement*> replaceSt = funcConv(curr);

    for (int k = (int)replaceSt.size() - 1; k >= 0; --k)
        curr->insertStmtAfter(*(replaceSt[k]), *curr->controlParent());
    copyLabelAndComentsToNext(curr);

    SgStatement *toDel = curr;
    curr = curr->lexNext();
    toDel->deleteStmt();

    char buf[512];
    sprintf(buf, (message + " on line %d\n").c_str(), lineNum);
    addToGlobalBufferAndPrint(buf);

    sprintf(buf, message.c_str());
    currMessages->push_back(Messages(NOTE, lineNum, buf, 2002));
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
    // convert all arithmetic if and computed goto to simple if with goto
    //TODO: add ASSIGN GOTO
    while (curr != lastNode)
    {
        if (curr->variant() == ARITHIF_NODE)
        {
            convert<convertArithIf>(curr, "convert arithmetic IF to simple IF");            
            continue;
        }
        else if (curr->variant() == COMGOTO_NODE)
        {
            convert<convertComGoto>(curr, "convert computed GOTO to simple IF");
            continue;
        }
        else if (curr->variant() == ASSGOTO_NODE)
        {
            SgExpression *lb = curr->expr(0);
            SgSymbol *assignedS = curr->symbol();
            //TODO
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

                sprintf(buf, "can not convert to END DO loop");
                currMessages->push_back(Messages(ERROR, lineNum, buf, 2003));
            }
        }

        if (result > 0)
        {
            char buf[512];
            sprintf(buf, "convert to END DO loop on line %d\n", lineNum);
            addToGlobalBufferAndPrint(buf);

            sprintf(buf, "convert to END DO loop");
            currMessages->push_back(Messages(NOTE, lineNum, buf, 2004));
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
        currProcessing.second = st->lineNumber();
        if (st->variant() == CONTAINS_STMT)
            break;

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

    const int funcNum = file->numberOfFunctions();
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        vector<SgForStmt*> parentLoops;

        map<SgForStmt*, SgLabel*> endOfLoops;
        map<int, SgForStmt*> toProcessLoops;
        fillEndOfLoop(st, endOfLoops, toProcessLoops);

        for (auto &loop : toProcessLoops)
            tryToConverLoop(loop.second, endOfLoops);
    }
}
