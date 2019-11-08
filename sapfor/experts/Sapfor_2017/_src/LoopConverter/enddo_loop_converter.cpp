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

static void copyLabelAndComents(SgStatement *from, SgStatement *to)
{
    if (from->hasLabel())
        to->setLabel(*from->label());
    if (from->comments())
        to->setComments(from->comments());
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

    auto condS = new SgSymbol(VARIABLE_NAME, ("ar_If_C" + std::to_string(curr->lineNumber())).c_str(), type, curr->getScopeForDeclare());
    SgStatement *assignCond = new SgAssignStmt(*new SgVarRefExp(*condS), *cond);

    vector<SgSymbol*> toAdd = { condS };
    makeDeclaration(curr, toAdd);

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

    auto condS = new SgSymbol(VARIABLE_NAME, ("com_Goto_C" + std::to_string(curr->lineNumber())).c_str(), SgTypeInt(), curr->getScopeForDeclare());
    SgStatement *assignCond = new SgAssignStmt(*new SgVarRefExp(*condS), *cond);
    
    vector<SgSymbol*> toAdd = { condS };
    makeDeclaration(curr, toAdd);
       
    if (labs.size() == 1)
        replace = new SgIfStmt(*new SgVarRefExp(*condS) == *new SgValueExp(1), *new SgGotoStmt(*labs[0]));
    else
        replace = new SgIfStmt(*new SgVarRefExp(*condS) == *new SgValueExp((int)labs.size()), *new SgGotoStmt(*labs.back()));
        
    for (int z = (int)labs.size() - 2; z >= 0; --z)
        replace = new SgIfStmt(*new SgVarRefExp(*condS) == *new SgValueExp(z + 1), *new SgGotoStmt(*labs[z]), *replace);
    
    return { assignCond, replace };
}

static pair<SgStatement*, SgStatement*> convertForall(SgStatement *st)
{
    if (st->variant() != FORALL_NODE && st->variant() != FORALL_STAT)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    SgForStmt *ret = NULL;
    SgExpression *ex = st->expr(0);
    SgExpression *cond = st->expr(1);
    vector<pair<SgSymbol*, tuple<SgExpression*, SgExpression*, SgExpression*>>> loops;

    while (ex)
    {
        if (ex->lhs()->variant() != FORALL_OP)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        SgExpression *left = ex->lhs();
        if (left->lhs()->lhs()->variant() == DDOT)
            loops.push_back(make_pair(left->symbol(), make_tuple(left->lhs()->lhs()->lhs(), left->lhs()->lhs()->rhs(), left->lhs()->rhs())));
        else
            loops.push_back(make_pair(left->symbol(), make_tuple(left->lhs()->lhs(), left->lhs()->rhs(), (SgExpression*)NULL)));
        ex = ex->rhs();
    }

    SgStatement *insertPoint = NULL;
    for (int z = loops.size() - 1; z >= 0; --z)
    {
        if (z == loops.size() - 1)
        {
            SgIfStmt *condIf = cond == NULL ? NULL : new SgIfStmt(*cond);
            ret = new SgForStmt(loops[z].first, get<0>(loops[z].second), get<1>(loops[z].second), get<2>(loops[z].second), condIf);
            if (condIf)
                insertPoint = condIf;
            else
                insertPoint = ret;
        }
        else
            ret = new SgForStmt(loops[z].first, get<0>(loops[z].second), get<1>(loops[z].second), get<2>(loops[z].second), ret);
    }
    return make_pair(ret, insertPoint);
}

template<vector<SgStatement*> funcConv(SgStatement*)>
static void convert(SgStatement *&curr, const wstring &messageR, const wstring &messageE)
{
    const int lineNum = curr->lineNumber();
    vector<SgStatement*> replaceSt = funcConv(curr);

    for (int k = (int)replaceSt.size() - 1; k >= 0; --k)
        curr->insertStmtAfter(*(replaceSt[k]), *curr->controlParent());
    copyLabelAndComents(curr, curr->lexNext());

    SgStatement *toDel = curr;
    curr = curr->lexNext();
    toDel->deleteStmt();

    //TODO
    //char buf[512];
    //sprintf(buf, (to_string(messageE) + " on line %d\n").c_str(), lineNum);
    //addToGlobalBufferAndPrint(buf);
        
    currMessages->push_back(Messages(NOTE, lineNum, messageR, messageE, 2002));
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
        wstring bufR = L"";
        if (curr->variant() == ARITHIF_NODE)
        {
#ifdef _WIN32
            __spf_printToLongBuf(bufR, R96);
#endif
            convert<convertArithIf>(curr, L"convert arithmetic IF to simple IF", bufR);
            continue;
        }
        else if (curr->variant() == COMGOTO_NODE)
        {
#ifdef _WIN32
            __spf_printToLongBuf(bufR, R97);
#endif
            convert<convertComGoto>(curr, L"convert computed GOTO to simple IF", bufR);
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
#ifdef _WIN32
                currMessages->push_back(Messages(ERROR, lineNum, R98, L"can not convert to END DO loop", 2003));
#endif
            }
        }

        if (result > 0)
        {
            char buf[512];
            sprintf(buf, "convert to END DO loop on line %d\n", lineNum);
            addToGlobalBufferAndPrint(buf);
#ifdef _WIN32
            currMessages->push_back(Messages(NOTE, lineNum, R99 , L"convert to END DO loop", 2004));
#endif
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

        // convert FORALL
        bool repeat = true;
        while (repeat)
        {
            repeat = false;
            vector<SgStatement*> toDel;
            st = file->functions(i);
            while (st != lastNode)
            {
                currProcessing.second = st->lineNumber();
                if (st->variant() == CONTAINS_STMT)
                    break;

                if (st->variant() == FORALL_STAT || st->variant() == FORALL_NODE)
                {                    
                    pair<SgStatement*, SgStatement*> newSt = convertForall(st);
                    checkNull(newSt.first, convertFileName(__FILE__).c_str(), __LINE__);

                    st->insertStmtBefore(*newSt.first, *st->controlParent());
                    copyLabelAndComents(st, newSt.first);

                    SgStatement *start = st->lexNext();
                    SgStatement *end = st->lastNodeOfStmt();
                    for (; start != end; )
                    {
                        SgStatement *copy = start->copyPtr();
                        if (copy->variant() == FORALL_STAT || copy->variant() == FORALL_NODE)
                            repeat = true;
                        newSt.second->lastNodeOfStmt()->insertStmtBefore(*copy, *newSt.second);
                        copyLabelAndComents(start, copy);

                        if (start->variant() != IF_NODE)
                        {
                            start = start->lastNodeOfStmt();
                            start = start->lexNext();
                        }
                        else
                        {
                            while (start->variant() != CONTROL_END)
                                start = start->lastNodeOfStmt();
                            start = start->lexNext();
                        }
                    }

                    if (st->variant() == FORALL_STAT)
                    {
                        SgStatement *copy = st->lexNext()->copyPtr();
                        newSt.second->lastNodeOfStmt()->insertStmtBefore(*copy, *newSt.second);
                        copyLabelAndComents(start, copy);
                    }
                    toDel.push_back(st);
                }
                st = st->lexNext();
            }

            for (auto &elem : toDel)
                elem->deleteStmt();
        }
    }
}

//return <vector of decls, vector of insert>
vector<SgStatement*> createIfConditions(std::stack<SgExpression*> &conds, std::stack<SgStatement*> &ifBlocks, SgStatement *control)
{
    vector<SgStatement*> ifSt = { NULL, NULL };
    
    const int id = control->getFileId();
    SgProject* proj = control->getProject();
    const int line = control->lineNumber();

    auto scope = getFuncStat(control);

    vector<SgSymbol*> toDecls;
    while (!conds.empty())
    {        
        string nextN = checkSymbNameAndCorrect(string("spf_If_C" + std::to_string(ifBlocks.top()->lineNumber())));
        SgSymbol* s = new SgSymbol(VARIABLE_NAME, nextN.c_str(), SgTypeBool(), scope);
        toDecls.push_back(s);

        SgAssignStmt* check = new SgAssignStmt(*new SgVarRefExp(s), *conds.top());
        check->setFileId(id);
        check->setProject(proj);
        check->setlineNumber(line);

        if (ifSt[0])
        {
            if (ifSt[1])
            {
                ifSt[1] = new SgIfStmt(*new SgExpression(NOT_OP, new SgVarRefExp(s)), *ifSt[1]);
                ifSt[1]->insertStmtAfter(*ifSt[0], *ifSt[1]);
            }
            else
                ifSt[1] = new SgIfStmt(*new SgExpression(NOT_OP, new SgVarRefExp(s)), *ifSt[0]);
            ifSt[1]->setFileId(id);
            ifSt[1]->setProject(proj);
            ifSt[1]->setlineNumber(line);

            ifSt[0] = check;
        }
        else
            ifSt[0] = check;

        ifBlocks.top()->setExpression(0, *new SgVarRefExp(s));
        ifBlocks.pop();
        conds.pop();
    }

    makeDeclaration(scope, toDecls);
    return ifSt;
}