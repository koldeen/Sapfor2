#include "../Utils/leak_detector.h"
#if NEW_CFG
#include "dvm.h"
#include "CFGraph.h"
#include "CFG_Common.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "calls.h"

using namespace std;

void CFG_BasicBlock::AddToPrev(CFG_BasicBlock* bb, bool for_jump_flag, bool c, CFG_ControlFlowItem* check)
{
    CFG_BasicBlockItem n;
    n.block = bb;    
    n.for_jump_flag = for_jump_flag;
    n.cond_value = c;
    n.jmp = check;
    prev.push_back(n);
}

void CFG_BasicBlock::AddToSucc(CFG_BasicBlock* bb, bool for_jump_flag, bool c, CFG_ControlFlowItem* check)
{
    CFG_BasicBlockItem n;
    n.block = bb;
    n.for_jump_flag = for_jump_flag;
    n.cond_value = c;
    n.jmp = check;
    succ.push_back(n);
}

void CFG_BasicBlock::SetDefAndUse()
{
    CFG_ControlFlowItem* p = start;
    while (p != NULL && (p == start || !p->IsLeader()))
    {
        if (p->GetJump() == NULL)
        {
            SgStatement* st = p->GetStatement();
            SgFunctionCallExp* f = p->GetFunctionCall();

            if (f != NULL)
            {
                bool add_intr = isAnIntrinsicSubroutine(f->funName()->identifier()) != NULL; // strcmp(f->funName()->identifier(), "date_and_time") == 0;
                bool intr = (isIntrinsicFunctionNameACC(f->funName()->identifier()) || add_intr) && !(f->funName()->attributes() & USER_PROCEDURE_BIT);
                bool pure = false;
                {
                    SgSymbol *shedr = NULL;
                    if (ATTR_NODE(f->funName()))
                        shedr = (GRAPHNODE(f->funName())->symb);

                    if (shedr)
                        pure = (shedr->attributes() & PURE_BIT);
                    else
                        pure = false;
                }

                const CFG_CallData* c = p->GetCall();
                if (!intr && !pure && c && c != (CFG_CallData*)(-1) && c != (CFG_CallData*)(-2) && !(c->IsIntrinsic()))
                {
                    if (c->header == NULL) 
                    {
                        //TODO:
                        //is_correct = "no header for procedure";
                        //failed_proc_name = c->funName;
                    }
                    else 
                        ProcessUserProcedure(true, f, c);
                }
                else if (c == (CFG_CallData*)(-1) || c == (CFG_CallData*)(-2))
                    ProcessProcedureWithoutBody(true, f, c == (CFG_CallData*)(-1));
                else if (intr || (c && c->IsIntrinsic())) 
                    ProcessIntrinsicProcedure(true, f->numberOfArgs(), f, f->funName()->identifier());                
                else
                    ProcessProcedureHeader(true, isSgProcHedrStmt(GRAPHNODE(f->funName())->st_header), f, f->funName()->identifier());
            }

            if (st != NULL)
            {
                switch (st->variant())
                {
                case ASSIGN_STAT:
                {
                    SgAssignStmt* s = isSgAssignStmt(st);
                    SgExpression* l = s->lhs();
                    SgExpression* r = s->rhs();

                    set<SgExpression*> tmp;
                    AddExprToUse(r, tmp);
                    AddOneExpressionToDef(l, st, NULL);
                    break;
                }
                case PRINT_STAT:
                case WRITE_STAT:
                case READ_STAT:
                {
                    SgInputOutputStmt* s = isSgInputOutputStmt(st);
                    if (s) 
                    {
                        SgExpression* ex = s->itemList();
                        while (ex && ex->lhs()) 
                        {
                            if (st->variant() == READ_STAT) 
                                AddOneExpressionToDef(ex->lhs(), st, NULL);                            
                            else 
                            {
                                set<SgExpression*> tmp;
                                AddExprToUse(ex->lhs(), tmp);
                            }
                            ex = ex->rhs();
                        }
                    }
                    break;
                }
                case PROC_STAT:
                {
                    SgCallStmt* f = isSgCallStmt(st);
                    bool add_intr = isAnIntrinsicSubroutine(f->name()->identifier()) != NULL;
                    bool intr = (isIntrinsicFunctionNameACC(f->name()->identifier()) || add_intr) && !(f->name()->attributes() & USER_PROCEDURE_BIT);
                    bool pure = false;
                    {
                        SgSymbol *shedr = NULL;
                        if (ATTR_NODE(f->name()))
                            shedr = (GRAPHNODE(f->name())->symb);

                        if (shedr)
                            pure = (shedr->attributes() & PURE_BIT);
                        else
                            pure = false;
                    }

                    if (!intr && !pure) 
                    {
                        const CFG_CallData* c = p->GetCall();                        
                        ProcessUserProcedure(false, f, c);
                        break;
                    }
                    if (intr) 
                    {
                        ProcessIntrinsicProcedure(false, f->numberOfArgs(), f, f->name()->identifier());
                        break;
                    }
                    ProcessProcedureHeader(false, isSgProcHedrStmt(GRAPHNODE(f->name())->st_header), f, f->name()->identifier());
                }
                default:
                    break;
                }
            }
        }
        else
        {
            set<SgExpression*> tmp;
            AddExprToUse(p->GetExpression(), tmp);
        }
        p = p->GetNext();
    }
}

CFG_VarSet* CFG_BasicBlock::GetMrdIn(bool la)
{
    if (mrd_in == NULL)
    {
        CFG_BasicBlock* delayed = NULL;
        CFG_VarSet* res = new CFG_VarSet();
        
        bool first = true;
        for (auto &p : prev)        
        {
            CFG_BasicBlock* b = p.block;
            if (b != NULL && !b->undef && b->HasPrev())
            {
                if (!p.for_jump_flag && first) 
                {
                    if (first) 
                    {
                        res->Unite(b->GetMrdOut(la), la);
                        if (delayed) 
                        {
                            res->Intersect(delayed->GetMrdOut(la), la, true);
                            delayed = NULL;
                        }
                        first = false;
                    }
                    else
                        res->Intersect(b->GetMrdOut(la), la, p.for_jump_flag);
                }
                else 
                    delayed = b;                
            }        
        }

        if (delayed) 
        {
            if (first)
                res->Unite(delayed->GetMrdOut(la), la);
            else
                res->Intersect(delayed->GetMrdOut(la), la, true);
        }
        mrd_in = res;
    }
    return mrd_in;
}

static bool isPresentInExprList(SgExpression* ex, const set<SgExpression*> &lst)
{
    auto it = lst.find(ex);
    return (it != lst.end());    
}

void CFG_BasicBlock::AddExprToUse(SgExpression* ex, set<SgExpression*> lst, CFG_ArrayVarEntryInfo* v = NULL)
{
    if (ex != NULL)
    {
        lst.insert(ex);
        SgFunctionCallExp* f = isSgFunctionCallExp(ex);
        if (!f) 
        {
            if (!isPresentInExprList(ex->lhs(), lst))
                AddExprToUse(ex->lhs(), lst, v);
            if (!isSgUnaryExp(ex))
                if (!isPresentInExprList(ex->rhs(), lst))
                    AddExprToUse(ex->rhs(), lst, v);
            AddOneExpressionToUse(ex, NULL, v);
        }
    }
}

static CFG_RecordVarEntryInfo* addRecordVarRef(SgRecordRefExp* ref)
{
    if (isSgRecordRefExp(ref->lhs())) 
    {
        CFG_VarEntryInfo* parent = addRecordVarRef(isSgRecordRefExp(ref->lhs()));
        if (parent)
            return new CFG_RecordVarEntryInfo(ref->rhs()->symbol(), parent);
        return NULL;
    }
    if (isSgVarRefExp(ref->lhs())) 
    {
        CFG_VarEntryInfo* parent = new CFG_ScalarVarEntryInfo(isSgVarRefExp(ref->lhs())->symbol());
        return new CFG_RecordVarEntryInfo(ref->rhs()->symbol(), parent);
    }
    if (isSgArrayRefExp(ref->lhs())) 
    {
        CFG_VarEntryInfo* parent = new CFG_ArrayVarEntryInfo(isSgArrayRefExp(ref->lhs())->symbol(), isSgArrayRefExp(ref->lhs()));
        return new CFG_RecordVarEntryInfo(ref->rhs()->symbol(), parent);
    }
    return NULL;
}

//TODO: many NEW
void CFG_BasicBlock::AddOneExpressionToUse(SgExpression* ex, SgStatement* st, CFG_ArrayVarEntryInfo* v)
{
    CFG_VarEntryInfo* var = NULL;
    SgVarRefExp* r;
    if ((r = isSgVarRefExp(ex)))
        var = new CFG_ScalarVarEntryInfo(r->symbol());
    SgArrayRefExp* ar;
    if ((ar = isSgArrayRefExp(ex))) 
    {
        if (!v)
            var = new CFG_ArrayVarEntryInfo(ar->symbol(), ar);
        else 
        {
            var = v->Clone();
            var->SwitchSymbol(ar->symbol());
        }
    }

    SgRecordRefExp* rr;
    if ((rr = isSgRecordRefExp(ex)))
        var = addRecordVarRef(rr);
    if (var) 
    {
        var->RegisterUsage(def, use, st);
        delete var;
    }
}

//TODO: many NEW
void CFG_BasicBlock::AddOneExpressionToDef(SgExpression* ex, SgStatement* st, CFG_ArrayVarEntryInfo* v)
{
    CFG_VarEntryInfo* var = NULL;
    SgVarRefExp* r;
    if ((r = isSgVarRefExp(ex)))
        var = new CFG_ScalarVarEntryInfo(r->symbol());
    SgRecordRefExp* rr;
    if ((rr = isSgRecordRefExp(ex)))
        var = addRecordVarRef(rr);
    SgArrayRefExp* ar;
    if ((ar = isSgArrayRefExp(ex))) 
    {
        if (!v)
            var = new CFG_ArrayVarEntryInfo(ar->symbol(), ar);
        else 
        {
            var = v->Clone();
            var->SwitchSymbol(ar->symbol());
        }
    }
    if (var) 
    {
        var->RegisterDefinition(def, use, st);
        delete var;
    }
}

void CFG_BasicBlock::ProcessUserProcedure(bool isFun, void* call, const CFG_CallData *c)
{
    if (c != (CFG_CallData*)(-1) && c != (CFG_CallData*)(-2) && c != NULL && c->graph != NULL)
    {
        int stored_file_id = SwitchFile(c->file_id);
        c->graph->GetPrivate(); //all sets actually
        SgStatement *cp = c->header->controlParent();
        SwitchFile(stored_file_id);

        if (proc && proc->header->variant() == PROC_HEDR && cp == proc->header)
        {
            CFG_VarSet* use_c = new CFG_VarSet();
            use_c->Unite(c->graph->GetUse(), false);
            while (use_c->GetList().size())            
            {
                const CFG_VarItem &exp = use_c->GetList()[0];
                if (exp.var->GetSymbol()->scope() == proc->header) 
                {
                    set<SgExpression*> tmp;
                    AddExprToUse(new SgVarRefExp(exp.var->GetSymbol()), tmp); // TESTING
                }
                use_c->Remove(exp.var);
            }
            delete use_c;

            CFG_VarSet* def_c = new CFG_VarSet();
            def_c->Unite(c->graph->GetDef(), true);
            while (def_c->GetList().size())            
            {
                const CFG_VarItem &exp = def_c->GetList()[0];
                if (exp.var->GetSymbol()->scope() == proc->header) 
                    def->AddToSet(exp.var, NULL);
                def_c->Remove(exp.var);
            }
            delete def_c;
        }

        CFG_GLOBAL_DATA::pCommons->MarkAsUsed(c->graph->GetUse(), c);
        SgProcHedrStmt* header = isSgProcHedrStmt(c->header);
        if (!header) 
        {
            //TODO:
            //is_correct = "no header for procedure";
            //failed_proc_name = c->funName;
            return;
        }
    }

    for (int i = 0; i < getNumberOfArguments(isFun, call); ++i)
    {
        SgExpression* ar = getProcedureArgument(isFun, call, i);
        CFG_ArrayVarEntryInfo* tp = NULL;
        if (c == (CFG_CallData*)(-1) || c == (CFG_CallData*)(-2) || c == NULL || c->graph == NULL || c->IsArgIn(i, tp))
        {
            set<SgExpression*> tmp;
            AddExprToUse(ar, tmp, tp);
        }
        tp = NULL;
        if (c == (CFG_CallData*)(-1) || c == NULL || c->graph == NULL || c->IsArgOut(i, tp))
            AddOneExpressionToDef(getProcedureArgument(isFun, call, i), NULL, tp);
    }

    if (c != (CFG_CallData*)(-1) && c != (CFG_CallData*)(-2) && c != NULL && c->graph != NULL) 
    {
        for (auto &cu : c->graph->getCommonUse())
        //for (CommonVarSet* cu = c->graph->getCommonUse(); cu != NULL; cu = cu->next)
        {
            const CFG_CommonVarInfo* v = &cu;
            const CFG_CallData* tp = start->GetProc();
            CFG_CommonDataItem* p = v->parent;
            if (CFG_CommonDataItem* it = CFG_GLOBAL_DATA::pCommons->IsThisCommonUsedInProcedure(p, tp))
            {
                if (CFG_GLOBAL_DATA::pCommons->CanHaveNonScalarVars(it))
                    continue;
                //TODO:
                CommonVarInfo* i = it->info;
                CommonVarInfo* j = p->info;
                while (j != v) 
                {
                    j = j->next;
                    if (i)
                        i = i->next;
                    else
                        continue;
                }
                if (!i)
                    continue;
                SgVarRefExp* var = new SgVarRefExp(i->var->GetSymbol());

                set<SgExpression*> tmp;
                AddExprToUse(var, tmp);
            }
            else 
                common_use.push_back(cu);
        }

        for (auto &cd : c->graph->getCommonDef())        
        {
            const CFG_CommonVarInfo* v = &cd;
            const CFG_CallData* tp = start->GetProc();
            CFG_CommonDataItem* p = v->parent;
            if (CFG_CommonDataItem* it = CFG_GLOBAL_DATA::pCommons->IsThisCommonUsedInProcedure(p, tp))
            {
                if (CFG_GLOBAL_DATA::pCommons->CanHaveNonScalarVars(it))
                    continue;
                //TODO:
                CommonVarInfo* i = it->info;
                CommonVarInfo* j = p->info;
                while (j != v) {
                    j = j->next;
                    if (i)
                        i = i->next;
                }
                if (!i)
                    continue;
                def->AddToSet(i->var, NULL);
            }
            else 
                common_def.push_back(cd);
        }
    }
}

static string getConditionWithLineNumber(CFG_ControlFlowItem* eit)
{
    string res;
    if (eit->GetOriginalStatement()) 
    {
        char tmp[16];
        sprintf(tmp, "%d: ", eit->GetOriginalStatement()->lineNumber());
        res = tmp;
    }
    return res + eit->GetExpression()->unparse();
}

static string getActualCondition(CFG_ControlFlowItem *&pItem) 
{
    string res = "";
    CFG_ControlFlowItem *eit = pItem;
    while (true)
    {
        if (eit == NULL || eit->GetJump() != NULL || eit->GetStatement() != NULL)
        {
            if (eit && eit->GetJump() != NULL)
            {
                if (eit->GetExpression() != NULL)
                {
                    pItem = eit;
                    return getConditionWithLineNumber(eit);
                }
                else
                {
                    pItem = NULL;
                    return res;
                }
                break;
            }
            pItem = NULL;
            return res;
        }
        eit = eit->GetPrev();
    }
}

string CFG_BasicBlock::GetEdgesForBlock(const string &name, bool original, const string &modifier)
{
    std::string result;
    for (auto &it : GetSuccToMod())
    {
        if (it.drawn)
            continue;
        else
            it.drawn = true;
        char lo = original;

        string cond;
        CFG_ControlFlowItem* eit = NULL;
        bool pf = false;
        if (it.jmp != NULL) 
        {
            if (it.jmp->GetExpression() != NULL) 
            {
                eit = it.jmp;
                cond = getConditionWithLineNumber(eit);
            }
            else
            {
                pf = true;
                eit = it.jmp->GetPrev();
                cond = getActualCondition(eit);
            }
        }
        if (eit && eit->GetFriend()) 
        {
            lo = false;
            eit = eit->GetFriend();
        }
        if (!it.block->IsEmptyBlock() || cond.length() != 0) 
        {
            if (cond.length() != 0 && eit && !pf) 
            {
                char tmp[32];
                sprintf(tmp, "c_%llx", (uintptr_t)eit);
                if (!eit->IsDrawn()) 
                {
                    result += '\t';
                    result += tmp;
                    result += "[shape=diamond,label=\"";
                    result += cond;
                    result += "\"];\n";
                }
                if (it.cond_value && !pf) 
                {
                    result += '\t' + name + "->";
                    result += tmp;
                    result += modifier;
                    result += '\n';
                }
                eit->SetIsDrawn();
            }

            if (cond.length() != 0) 
            {
                if (lo) 
                {
                    char tmp[32];
                    sprintf(tmp, "c_%llx", (uintptr_t)eit);
                    if (!it.block->IsEmptyBlock()) 
                    {
                        result += '\t';
                        result += tmp;
                        result += "->" + it.block->GetGraphVisDescription();
                        result += "[label=";
                        result += (!pf && it.cond_value) ? "T]" : "F]";
                        result += ";\n";
                    }
                    else 
                    {
                        std::string n = tmp;
                        std::string label;
                        label += "[label=";
                        label += (!pf && it.cond_value) ? "T]" : "F]";
                        result += it.block->GetEdgesForBlock(n, original, label);
                    }
                }
            }
            else 
            {
                result += '\t' + name + " -> " + it.block->GetGraphVisDescription();
                result += modifier;
                result += ";\n";
            }

        }
        else 
            result += it.block->GetEdgesForBlock(name, original, "");        
    }
    return result;
}

CFG_BasicBlock::~CFG_BasicBlock()
{
    common_def.clear();
    common_use.clear();
    prev.clear();
    succ.clear();

    if (def) delete def;
    if (use) delete use;
    if (old_mrd_out) delete old_mrd_out; 
    if (old_mrd_in) delete old_mrd_in;
    if (mrd_in) delete mrd_in; 
    if (mrd_out) delete mrd_out; 
    if (old_lv_out) delete old_lv_out;
    if (old_lv_in) delete old_lv_in; 
    if (lv_in) delete lv_in; 
    if (lv_out) delete lv_out;
}

#endif