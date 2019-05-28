#include "../Utils/leak_detector.h"
#if NEW_CFG
#include "dvm.h"
#include "CFGraph.h"
#include "CFG_Variables.h"
#include "CFG_Common.h"

// is a copied function
static SgStatement * lastStmtOfDoACC(SgStatement *stdo)
{    
    SgStatement *st;
    // second version  (change 04.03.08) 
    st = stdo;
RE: st = st->lastNodeOfStmt();
    if ((st->variant() == FOR_NODE) || (st->variant() == WHILE_NODE))
        goto RE;

    else if (st->variant() == LOGIF_NODE)
        return(st->lexNext());

    else
        return(st);
}

static CFG_ControlFlowItem* getFuncCallsForExpr(SgExpression* e, CFG_Call* calls, CFG_ControlFlowItem** last, CFG_CommonData* commons, SgStatement* os)
{
    if (e == NULL) {
        *last = NULL;
        return NULL;
    }
    SgFunctionCallExp* f = isSgFunctionCallExp(e);
    if (f) 
    {
        CFG_ControlFlowItem* head = new CFG_ControlFlowItem(NULL, NULL, CFG_GLOBAL_DATA::currentProcedure, calls->GetLinkToCall(e, NULL, commons));
        head->SetOriginalStatement(os);
        CFG_ControlFlowItem* curl = head;
        head->SetFunctionCall(f);
        CFG_ControlFlowItem* l1, *l2;
        CFG_ControlFlowItem* tail1 = getFuncCallsForExpr(e->lhs(), calls, &l1, commons, os);
        CFG_ControlFlowItem* tail2 = getFuncCallsForExpr(e->rhs(), calls, &l2, commons, os);
        *last = head;
        if (tail2 != NULL) 
        {
            l2->AddNextItem(head);
            head = tail2;
        }

        if (tail1 != NULL)
        {
            l1->AddNextItem(head);
            head = tail1;
        }
        return head;
    }

    f = isSgFunctionCallExp(e->lhs());
    if (f) 
    {
        CFG_ControlFlowItem* head = new CFG_ControlFlowItem(NULL, NULL, CFG_GLOBAL_DATA::currentProcedure, calls->GetLinkToCall(e->lhs(), NULL, commons));
        head->SetOriginalStatement(os);
        head->SetFunctionCall(f);
        CFG_ControlFlowItem* l1, *l2, *l3;
        CFG_ControlFlowItem* tail1 = getFuncCallsForExpr(e->lhs()->lhs(), calls, &l1, commons, os);
        CFG_ControlFlowItem* tail2 = getFuncCallsForExpr(e->lhs()->rhs(), calls, &l2, commons, os);
        CFG_ControlFlowItem* tail3 = getFuncCallsForExpr(e->rhs(), calls, &l3, commons, os);
        *last = head;
        if (tail2 != NULL) 
        {
            l2->AddNextItem(head);
            head = tail2;
        }

        if (tail1 != NULL) 
        {
            l1->AddNextItem(head);
            head = tail1;
        }

        if (tail3 != NULL)
        {
            (*last)->AddNextItem(tail3);
            *last = l3;
        }
        return head;
    }
    return getFuncCallsForExpr(e->rhs(), calls, last, commons, os);
}

static CFG_ControlFlowItem* addFunctionCalls(SgStatement* st, CFG_Call* calls, CFG_ControlFlowItem** last, CFG_CommonData* commons)
{
    CFG_ControlFlowItem* retv = getFuncCallsForExpr(st->expr(0), calls, last, commons, st);
    CFG_ControlFlowItem* l2 = NULL;
    CFG_ControlFlowItem* second = getFuncCallsForExpr(st->expr(1), calls, &l2, commons, st);
    if (retv == NULL)
    {
        retv = second;
        *last = l2;
    }
    else if (second != NULL) 
    {
        (*last)->AddNextItem(second);
        *last = l2;
    }
    CFG_ControlFlowItem* l3 = NULL;
    CFG_ControlFlowItem* third = getFuncCallsForExpr(st->expr(2), calls, &l3, commons, st);
    if (retv == NULL) 
    {
        retv = third;
        *last = l3;
    }
    else if (third != NULL) 
    {
        (*last)->AddNextItem(third);
        *last = l3;
    }
    return retv;
}

static CFG_ControlFlowItem* ifItem(SgStatement* stmt, CFG_ControlFlowItem* empty, SgStatement** lastAnStmt, doLoops* loops, bool ins, CFG_Call* calls, CFG_CommonData* commons)
{
    if (stmt == NULL)
        return empty;
    SgIfStmt* cond;
    if (stmt->variant() == ELSEIF_NODE)
        cond = (SgIfStmt*)stmt;
    if (stmt->variant() == ELSEIF_NODE || (!ins && (cond = isSgIfStmt(stmt)) != NULL))
    {
        SgExpression* c = &(SgNotOp((cond->conditional()->copy())));
        CFG_ControlFlowItem *n, *j;
        CFG_ControlFlowItem* last;
        if ((n = getControlFlowList(cond->trueBody(), NULL, &last, lastAnStmt, loops, calls, commons)) == NULL)
            return NULL;
        j = ifItem(cond->falseBody(), empty, lastAnStmt, loops, cond->falseBody() != NULL ? cond->falseBody()->variant() == IF_NODE : false, calls, commons);
        CFG_ControlFlowItem* gotoEmpty = new CFG_ControlFlowItem(NULL, empty, j, NULL, CFG_GLOBAL_DATA::currentProcedure);
        if (last != NULL)
            last->AddNextItem(gotoEmpty);
        else
            n = gotoEmpty;
        CFG_ControlFlowItem* tn = new CFG_ControlFlowItem(c, j, n, stmt->label(), CFG_GLOBAL_DATA::currentProcedure);
        tn->SetOriginalStatement(stmt);
        return tn;
    }
    else
    {
        CFG_ControlFlowItem* last;
        CFG_ControlFlowItem* ret;
        if ((ret = getControlFlowList(stmt, NULL, &last, lastAnStmt, loops, calls, commons)) == NULL)
            return NULL;
        last->AddNextItem(empty);
        return ret;
    }
}

static CFG_ControlFlowItem* switchItem(SgStatement* stmt, CFG_ControlFlowItem* empty, SgStatement** lastAnStmt, doLoops* loops, CFG_Call* calls, CFG_CommonData* commons)
{
    SgSwitchStmt* sw = isSgSwitchStmt(stmt);
    SgExpression* sw_cond = (sw->selector());
    stmt = stmt->lexNext();
    *lastAnStmt = stmt;
    CFG_ControlFlowItem* last_sw = NULL;
    CFG_ControlFlowItem* first = NULL;
    bool is_def_last = false;
    SgStatement* not_def_last;
    while (stmt->variant() == CASE_NODE || stmt->variant() == DEFAULT_NODE)
    {
        if (stmt->variant() == DEFAULT_NODE) 
        {
            while (stmt->variant() != CONTROL_END && stmt->variant() != CASE_NODE)
                stmt = stmt->lexNext();
            if (stmt->variant() == CONTROL_END)
                stmt = stmt->lexNext();
            is_def_last = true;
            continue;
        }

        SgExpression* c = ((SgCaseOptionStmt*)stmt)->caseRange(0);
        SgExpression *lhs = NULL;
        SgExpression *rhs = NULL;
        if (c->variant() == DDOT) 
        {
            lhs = c->lhs();
            rhs = c->rhs();
            if (rhs == NULL)
                c = &(*lhs <= *sw_cond);
            else if (lhs == NULL)
                c = &(*sw_cond <= *rhs);
            else
                c = &(*lhs <= *sw_cond && *sw_cond <= *rhs);
        }
        else
            c = &SgNeqOp(*sw_cond, *c);
        CFG_ControlFlowItem *n, *j;
        CFG_ControlFlowItem* last;
        if ((n = getControlFlowList(stmt->lexNext(), NULL, &last, lastAnStmt, loops, calls, commons)) == NULL)
            return NULL;
        j = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* gotoEmpty = new CFG_ControlFlowItem(NULL, empty, j, NULL, CFG_GLOBAL_DATA::currentProcedure);
        if (last != NULL)
            last->AddNextItem(gotoEmpty);
        else
            n = gotoEmpty;
        CFG_ControlFlowItem* cond = new CFG_ControlFlowItem(c, j, n, stmt->label(), CFG_GLOBAL_DATA::currentProcedure);
        cond->SetOriginalStatement(stmt);
        if (last_sw == NULL)
            first = cond;
        else
            last_sw->AddNextItem(cond);
        last_sw = j;
        is_def_last = false;
        not_def_last = *lastAnStmt;
        stmt = *lastAnStmt;
    }
    SgStatement* def = sw->defOption();
    if (def != NULL) {
        CFG_ControlFlowItem* last;
        CFG_ControlFlowItem* n;
        if ((n = getControlFlowList(def->lexNext(), NULL, &last, lastAnStmt, loops, calls, commons)) == NULL)
            return NULL;
        if (last != NULL)
            last->AddNextItem(empty);
        if (last_sw == NULL)
            first = n;
        else
            last_sw->AddNextItem(n);
        last_sw = last;
    }
    last_sw->AddNextItem(empty);
    if (!is_def_last)
        *lastAnStmt = not_def_last;
    return first;
}

static CFG_ControlFlowItem* 
    processOneStatement(SgStatement** stmt, CFG_ControlFlowItem** pred, CFG_ControlFlowItem **list, 
                        CFG_ControlFlowItem* oldcur, doLoops* loops, CFG_Call* calls, CFG_CommonData* commons)
{
    CFG_ControlFlowItem* lastf;
    CFG_ControlFlowItem* funcs = addFunctionCalls(*stmt, calls, &lastf, commons);
    if (funcs != NULL) {
        if (*pred != NULL)
            (*pred)->AddNextItem(funcs);
        else
            *list = funcs;
        *pred = lastf;
    }

    switch ((*stmt)->variant())
    {
    case IF_NODE:
    {
        CFG_ControlFlowItem* emptyAfterIf = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure); //empty item to avoid second pass        
        CFG_ControlFlowItem* cur = ifItem(*stmt, emptyAfterIf, stmt, loops, false, calls, commons);
        emptyAfterIf->SetLabel((*stmt)->label());
        if (*pred != NULL)
            (*pred)->AddNextItem(cur);
        else
            *list = cur;
        return (*pred = emptyAfterIf);
    }
    case ASSIGN_STAT:
    case POINTER_ASSIGN_STAT:
    case PROC_STAT:
    case PRINT_STAT:
    case READ_STAT:
    case WRITE_STAT:
    case ALLOCATE_STMT:
    case DEALLOCATE_STMT:
    {
        CFG_ControlFlowItem* cur = new CFG_ControlFlowItem(*stmt, NULL, CFG_GLOBAL_DATA::currentProcedure, (*stmt)->variant() == PROC_STAT ? calls->GetLinkToCall(NULL, *stmt, commons) : NULL);
        if (*pred != NULL)
            (*pred)->AddNextItem(cur);
        else
            *list = cur;
        return (*pred = loops->checkStatementForLoopEnding(cur->GetLabel() ? cur->GetLabel()->id() : -1, cur));
    }
    case LOGIF_NODE:
    {
        CFG_ControlFlowItem* emptyAfterIf = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure); //empty item to avoid second pass
        SgLogIfStmt* cond = isSgLogIfStmt(*stmt);
        SgLabel* lbl = (*stmt)->label();
        SgExpression* c = &(SgNotOp((cond->conditional()->copy())));
        CFG_ControlFlowItem* cur = new CFG_ControlFlowItem(c, emptyAfterIf, NULL, (*stmt)->label(), CFG_GLOBAL_DATA::currentProcedure);
        cur->SetOriginalStatement(*stmt);
        if (*pred != NULL)
            (*pred)->AddNextItem(cur);
        else
            *list = cur;
        *stmt = (*stmt)->lexNext();
        CFG_ControlFlowItem* body;
        if ((body = processOneStatement(stmt, &cur, list, cur, loops, calls, commons)) == NULL) 
            return NULL;        
        body->AddNextItem(emptyAfterIf);
        return (*pred = loops->checkStatementForLoopEnding(lbl ? lbl->id() : -1, emptyAfterIf));
    }
    case WHILE_NODE:
    {
        SgWhileStmt* cond = isSgWhileStmt(*stmt);
        bool isEndDo = (*stmt)->lastNodeOfStmt()->variant() == CONTROL_END;
        SgExpression* c;
        if (cond->conditional())
            c = &(SgNotOp((cond->conditional()->copy())));
        else
            c = new SgValueExp(1);
        CFG_ControlFlowItem* emptyAfterWhile = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* emptyBeforeBody = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* cur = new CFG_ControlFlowItem(c, emptyAfterWhile, emptyBeforeBody, (*stmt)->label(), CFG_GLOBAL_DATA::currentProcedure);
        cur->SetOriginalStatement(cond);
        CFG_ControlFlowItem* gotoStart = new CFG_ControlFlowItem(NULL, cur, emptyAfterWhile, NULL, CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* emptyBefore = new CFG_ControlFlowItem(NULL, (CFG_ControlFlowItem*)NULL, cur, cond->label(), CFG_GLOBAL_DATA::currentProcedure);
        SgVarRefExp* doName = (isSgVarRefExp((*stmt)->expr(2)));
        int lbl = -1;
        if (!isEndDo) 
        {
            SgStatement* end = lastStmtOfDoACC(cond);
            if (end->controlParent() && end->controlParent()->variant() == LOGIF_NODE)
                lbl = end->controlParent()->label()->id();
            else
                lbl = end->label()->id();
        }
        loops->addLoop(lbl, doName ? doName->symbol() : NULL, gotoStart, emptyAfterWhile);
        CFG_ControlFlowItem* n, *last;
        if (isEndDo) 
        {
            if ((n = getControlFlowList((*stmt)->lexNext(), NULL, &last, stmt, loops, calls, commons)) == NULL)
                return NULL;
            emptyBeforeBody->AddNextItem(n);
            loops->endLoop(last);
        }
        if (*pred != NULL)
            (*pred)->AddNextItem(emptyBefore);
        else
            *list = emptyBefore;
        if (isEndDo)
            return (*pred = emptyAfterWhile);
        return (*pred = emptyBeforeBody);
    }
    case FOR_NODE:
    {
        SgForStmt* fst = isSgForStmt(*stmt);
#if __SPF
        SgStatement *p = NULL;
        for (int i = 0; i < fst->numberOfAttributes(); ++i)
        {
            if (fst->attributeType(i) == SPF_ANALYSIS_DIR)
            {
                p = (SgStatement *)(fst->getAttribute(i)->getAttributeData());
                break;
            }
        }
        bool isParLoop = (p && p->variant() == SPF_ANALYSIS_DIR);
#else
        SgStatement* p = (*stmt)->lexPrev();
        bool isParLoop = (p && p->variant() == DVM_PARALLEL_ON_DIR);
#endif
        SgExpression* pl = NULL;
        SgExpression* pPl = NULL;
        bool pl_flag = true;
        if (isParLoop) 
        {
#if __SPF
            SgExpression* el = p->expr(0);
#else
            SgExpression* el = p->expr(1);
#endif
            pPl = el;
            while (el != NULL)
            {
                SgExpression* e = el->lhs();
                if (e->variant() == ACC_PRIVATE_OP) 
                {
                    pl = e;
                    break;
                }
                pPl = el;
                pl_flag = false;
                el = el->rhs();
            }
        }
        bool isEndDo = fst->isEnddoLoop();
        SgExpression* lh = new SgVarRefExp(fst->symbol());
        SgStatement* fa = new SgAssignStmt(*lh, *fst->start());
        bool needs_goto = true;
#if !__SPF
        // create goto edge if can not calculate count of loop's iterations
        if (fst->start()->variant() == INT_VAL && fst->end()->variant() == INT_VAL && fst->start()->valueInteger() < fst->end()->valueInteger())
            needs_goto = false;
#endif
        //fa->setLabel(*(*stmt)->label());
        CFG_ControlFlowItem* last;
        CFG_ControlFlowItem* emptyAfterDo = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* emptyBeforeDo = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* gotoEndInitial = NULL;
        if (needs_goto) {
            SgExpression* sendc = new SgExpression(GT_OP, new SgVarRefExp(fst->symbol()), fst->end(), NULL);
            gotoEndInitial = new CFG_ControlFlowItem(sendc, emptyAfterDo, emptyBeforeDo, NULL, CFG_GLOBAL_DATA::currentProcedure, true);
            gotoEndInitial->SetOriginalStatement(fst);
        }
        CFG_ControlFlowItem* stcf = new CFG_ControlFlowItem(fa, needs_goto ? gotoEndInitial : emptyBeforeDo, CFG_GLOBAL_DATA::currentProcedure);
        stcf->SetOriginalStatement(fst);
        stcf->SetLabel((*stmt)->label());
        SgExpression* rh = new SgExpression(ADD_OP, new SgVarRefExp(fst->symbol()), new SgValueExp(1), NULL);
        SgStatement* add = new SgAssignStmt(*lh, *rh);
        SgExpression* endc = new SgExpression(GT_OP, new SgVarRefExp(fst->symbol()), fst->end(), NULL);
        CFG_ControlFlowItem* gotoStart = new CFG_ControlFlowItem(NULL, emptyBeforeDo, emptyAfterDo, NULL, CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* gotoEnd = new CFG_ControlFlowItem(endc, emptyAfterDo, gotoStart, NULL, CFG_GLOBAL_DATA::currentProcedure);
        gotoEnd->SetOriginalStatement(fst);
        if (needs_goto) 
            gotoEnd->SetConditionFriend(gotoEndInitial);

        CFG_ControlFlowItem* loop_d = new CFG_ControlFlowItem(add, gotoEnd, CFG_GLOBAL_DATA::currentProcedure);
        loop_d->SetOriginalStatement(fst);
        CFG_ControlFlowItem* loop_emp = new CFG_ControlFlowItem(NULL, loop_d, CFG_GLOBAL_DATA::currentProcedure);
        SgVarRefExp* doName = (isSgVarRefExp((*stmt)->expr(2)));
        int lbl = -1;
        if (!isEndDo) 
        {
            SgStatement* end = lastStmtOfDoACC(fst);
            if (end->variant() == LOGIF_NODE)
                lbl = end->controlParent()->label()->id();
            else
                lbl = end->label()->id();
        }
        loops->addLoop(lbl, doName ? doName->symbol() : NULL, loop_emp, emptyAfterDo);
        doLoopList->AddLoop(current_file_id, *stmt, fst->start(), fst->end(), fst->step(), fst->symbol());
        if (isParLoop) 
        {
#if __SPF
            // all loop has depth == 1 ? is it correct?
            int k = 1;
#else
            SgExpression* par_des = p->expr(2);
            int k = 0;
            while (par_des != NULL && par_des->lhs() != NULL) 
            {
                k++;
                par_des = par_des->rhs();
            }
#endif
            loops->setParallelDepth(k, pl, p, pPl, pl_flag);
        }

        if (loops->isLastParallel())
        {
            SgExpression* ex = loops->getPrivateList();
            emptyBeforeDo->MakeParloopStart();
            bool f;
            SgExpression* e = loops->getExpressionToModifyPrivateList(&f);
            emptyBeforeDo->SetPrivateList(ex, loops->GetParallelStatement(), e, f);
            loop_d->MakeParloopEnd();
        }
        if (isEndDo) {
            CFG_ControlFlowItem* body;
            if ((body = getControlFlowList(fst->body(), NULL, &last, stmt, loops, calls, commons)) == NULL)
                return NULL;
            emptyBeforeDo->AddNextItem(body);
            loops->endLoop(last);
        }
        if (*pred != NULL)
            (*pred)->AddNextItem(stcf);
        else
            *list = stcf;
        if (isEndDo)
            return (*pred = emptyAfterDo);
        return (*pred = emptyBeforeDo);
    }
    case GOTO_NODE:
    {
        SgGotoStmt* gst = isSgGotoStmt(*stmt);
        CFG_ControlFlowItem* gt = new CFG_ControlFlowItem(NULL, gst->branchLabel(), NULL, gst->label(), CFG_GLOBAL_DATA::currentProcedure);
        if (*pred != NULL)
            (*pred)->AddNextItem(gt);
        else
            *list = gt;
        return (*pred = gt);
    }
    case ARITHIF_NODE:
    {
        SgArithIfStmt* arif = (SgArithIfStmt*)(*stmt);
        CFG_ControlFlowItem* gt3 = new CFG_ControlFlowItem(NULL, ((SgLabelRefExp*)(*stmt)->expr(1)->rhs()->rhs()->lhs())->label(), NULL, NULL, CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* gt2 = new CFG_ControlFlowItem(&SgEqOp(*(arif->conditional()), *new SgValueExp(0)), ((SgLabelRefExp*)(*stmt)->expr(1)->rhs()->lhs())->label(), gt3, NULL, CFG_GLOBAL_DATA::currentProcedure);
        gt2->SetOriginalStatement(arif);
        CFG_ControlFlowItem* gt1 = new CFG_ControlFlowItem(&(*arif->conditional() < *new SgValueExp(0)), ((SgLabelRefExp*)(*stmt)->expr(1)->lhs())->label(), gt2, (*stmt)->label(), CFG_GLOBAL_DATA::currentProcedure);
        gt1->SetOriginalStatement(arif);
        if (*pred != NULL)
            (*pred)->AddNextItem(gt1);
        else
            *list = gt1;
        return (*pred = gt3);
    }
    case COMGOTO_NODE:
    {
        SgComputedGotoStmt* cgt = (SgComputedGotoStmt*)(*stmt);
        SgExpression* label = cgt->labelList();
        int i = 0;
        SgLabel* lbl = ((SgLabelRefExp *)(label->lhs()))->label();
        CFG_ControlFlowItem* gt = new CFG_ControlFlowItem(&SgEqOp(*(cgt->exp()), *new SgValueExp(++i)), lbl, NULL, cgt->label(), CFG_GLOBAL_DATA::currentProcedure);
        gt->SetOriginalStatement(cgt);
        if (*pred != NULL)
            (*pred)->AddNextItem(gt);
        else
            *list = gt;
        CFG_ControlFlowItem* old = gt;
        while ((label = label->rhs()))
        {
            lbl = ((SgLabelRefExp *)(label->lhs()))->label();
            gt = new CFG_ControlFlowItem(&SgEqOp(*(cgt->exp()), *new SgValueExp(++i)), lbl, NULL, NULL, CFG_GLOBAL_DATA::currentProcedure);
            gt->SetOriginalStatement(cgt);
            old->AddNextItem(gt);
            old = gt;
        }
        return (*pred = gt);
    }
    case SWITCH_NODE:
    {
        CFG_ControlFlowItem* emptyAfterSwitch = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
        CFG_ControlFlowItem* cur = switchItem(*stmt, emptyAfterSwitch, stmt, loops, calls, commons);
        emptyAfterSwitch->SetLabel((*stmt)->label());
        if (*pred != NULL)
            (*pred)->AddNextItem(cur);
        else
            *list = cur;
        return (*pred = emptyAfterSwitch);
    }
    case CONT_STAT:
    {
        CFG_ControlFlowItem* cur = new CFG_ControlFlowItem(NULL, (CFG_ControlFlowItem*)NULL, NULL, (*stmt)->label(), CFG_GLOBAL_DATA::currentProcedure);
        if (*pred != NULL)
            (*pred)->AddNextItem(cur);
        else
            *list = cur;
        return (*pred = loops->checkStatementForLoopEnding(cur->GetLabel() ? cur->GetLabel()->id() : -1, cur));
    }
    case CYCLE_STMT:
    {
        SgSymbol* ref = (*stmt)->symbol();
        CFG_ControlFlowItem* cur = new CFG_ControlFlowItem(NULL, loops->getSourceForCycle(ref), NULL, (*stmt)->label(), CFG_GLOBAL_DATA::currentProcedure);
        if (*pred != NULL)
            (*pred)->AddNextItem(cur);
        else
            *list = cur;
        return (*pred = cur);
    }
    case EXIT_STMT:
    {
        SgSymbol* ref = (*stmt)->symbol();
        CFG_ControlFlowItem* cur = new CFG_ControlFlowItem(NULL, loops->getSourceForExit(ref), NULL, (*stmt)->label(), CFG_GLOBAL_DATA::currentProcedure);
        if (*pred != NULL)
            (*pred)->AddNextItem(cur);
        else
            *list = cur;
        return (*pred = cur);
    }
    case COMMENT_STAT:
        return *pred;
    case COMM_STAT:
    {
        commons->RegisterCommonBlock(*stmt, CFG_GLOBAL_DATA::currentProcedure);
        return *pred;
    }
    default:
        return *pred;
        //return NULL;
    }
}

static void clearList(CFG_ControlFlowItem *list)
{
    if (list != NULL)
    {
        if (list->GetNext() != NULL)
            clearList(list->GetNext());
        delete list;
    }
}

CFG_ControlFlowItem* getControlFlowList(SgStatement *firstSt, SgStatement *lastSt, CFG_ControlFlowItem *&last, SgStatement *&lastAnStmt, doLoops* loops, CFG_Call *calls, CFG_CommonData *commons)
{
    CFG_ControlFlowItem *list = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
    CFG_ControlFlowItem *cur = list;
    CFG_ControlFlowItem *pred = list;
    SgStatement *stmt;
    for (stmt = firstSt; (
        stmt != lastSt
        && stmt->variant() != CONTAINS_STMT
        && (lastSt != NULL || stmt->variant() != ELSEIF_NODE)
        && (lastSt != NULL || stmt->variant() != CASE_NODE)
        && (lastSt != NULL || stmt->variant() != DEFAULT_NODE));
        stmt = stmt->lexNext())
    {
        if (stmt->variant() == CONTROL_END)
        {
            if (isSgExecutableStatement(stmt))
                break;
        }

        cur = processOneStatement(&stmt, &pred, &list, cur, loops, calls, commons);
        if (cur == NULL)
        {
            clearList(list);
            return NULL;
        }
    }
    if (cur == NULL) {
        cur = list = new CFG_ControlFlowItem(CFG_GLOBAL_DATA::currentProcedure);
    }
    if (last != NULL)
        last = cur;
    if (lastAnStmt != NULL)
        lastAnStmt = stmt;
    return list;
}
#endif