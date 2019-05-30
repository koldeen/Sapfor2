#define _LEAK_
#include "../Utils/leak_detector.h"
#if NEW_CFG
#include "dvm.h"

#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "calls.h"

#include "CFGraph.h"
#include "CFG_Common.h"
#include "CFG_Variables.h"

using namespace std;

CFG_BasicBlock::CFG_BasicBlock(bool t, CFG_ControlFlowItem* st, int n, CFG_ControlFlowGraph* par, const CFG_CallData *pr) :
    temp(t), num(n), start(st), prev(NULL), lexNext(NULL), def(NULL), use(NULL), mrd_in(new CFG_VarSet()), mrd_out(new CFG_VarSet()), undef(true),
    lv_in(new CFG_VarSet()), lv_out(new CFG_VarSet()), lv_undef(false), succ(NULL), lexPrev(NULL), prev_status(-1), parent(par), common_def(NULL),
    common_use(NULL), old_mrd_in(NULL), old_mrd_out(NULL), old_lv_in(NULL), old_lv_out(NULL), privdata(NULL), findentity(NULL), proc(pr)
{ }

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

void CFG_BasicBlock::AddExprToUse(SgExpression* ex, set<SgExpression*> lst, CFG_ArrayVarEntryInfo* v)
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
                const CFG_VarItem *exp = use_c->GetList()[0];
                if (exp->Var()->GetSymbol()->scope() == proc->header) 
                {
                    set<SgExpression*> tmp;
                    AddExprToUse(new SgVarRefExp(exp->Var()->GetSymbol()), tmp); // TESTING
                }
                use_c->Remove(exp->Var());
            }
            delete use_c;

            CFG_VarSet* def_c = new CFG_VarSet();
            def_c->Unite(c->graph->GetDef(), true);
            while (def_c->GetList().size())            
            {
                const CFG_VarItem *exp = def_c->GetList()[0];
                if (exp->Var()->GetSymbol()->scope() == proc->header)
                    def->AddToSet(exp->Var(), NULL);
                def_c->Remove(exp->Var());
            }
            delete def_c;
        }

        G_pCommons->MarkAsUsed(c->graph->GetUse(), c);
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
        {
            const CFG_CommonVarInfo* v = &cu;
            const CFG_CallData* tp = start->GetProc();
            CFG_CommonDataItem* p = v->parent;
            if (CFG_CommonDataItem* it = G_pCommons->IsThisCommonUsedInProcedure(p, tp))
            {
                if (G_pCommons->CanHaveNonScalarVars(it))
                    continue;                
                //TODO: check and correct
                if (it->info.size() != p->info.size())
                    continue;

                SgVarRefExp* var = NULL;
                int z = 0;
                for ( ; z < it->info.size(); ++z)
                {
                    if (*it->info[z].var == *v->var)
                        break;
                }
                if (z == it->info.size())
                    continue;
                var = new SgVarRefExp(p->info[z].var->GetSymbol());
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
            if (CFG_CommonDataItem* it = G_pCommons->IsThisCommonUsedInProcedure(p, tp))
            {
                if (G_pCommons->CanHaveNonScalarVars(it))
                    continue;
                //TODO: check and correct
                int z = 0;
                for (; z < it->info.size(); ++z)
                {
                    if (*it->info[z].var == *v->var)
                        break;
                }
                if (z == it->info.size())
                    continue;
                def->AddToSet(p->info[z].var, NULL);
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

CFG_VarSet* CFG_BasicBlock::GetMrdOut(bool la)
{
    if (mrd_out == NULL)
    {
        CFG_VarSet* res = new CFG_VarSet();
        res->Unite(GetMrdIn(la), la);
        res->Unite(GetDef(), la);
        mrd_out = res;
    }
    return mrd_out;
}

CFG_VarSet* CFG_BasicBlock::GetLVIn()
{
    if (lv_in == NULL)
    {
        CFG_VarSet* res = new CFG_VarSet();
        res->Unite(GetLVOut(), false);
        res->Minus(GetDef());
        res->Unite(GetUse(), false);
        lv_in = res;
    }
    return lv_in;
}

CFG_VarSet* CFG_BasicBlock::GetLVOut()
{
    if (lv_out == NULL)
    {
        CFG_VarSet* res = new CFG_VarSet();
        for (auto &p : succ)
        {
            CFG_BasicBlock* b = p.block;
            if (b != NULL && !b->lv_undef)
                res->Unite(b->GetLVIn(), false);
        }
        lv_out = res;
    }
    return lv_out;
}

bool CFG_BasicBlock::StepMrdIn(bool la)
{
    if (old_mrd_in)
        delete old_mrd_in;

    old_mrd_in = mrd_in;
    mrd_in = NULL;
    GetMrdIn(la);
    return (mrd_in->Equal(old_mrd_in));
}

bool CFG_BasicBlock::StepMrdOut(bool la)
{
    if (old_mrd_out)
        delete old_mrd_out;

    old_mrd_out = mrd_out;
    mrd_out = NULL;
    GetMrdOut(la);
    undef = false;
    return (mrd_out->Equal(old_mrd_out));
}

bool CFG_BasicBlock::StepLVIn()
{
    if (old_lv_in)
        delete old_lv_in;

    old_lv_in = lv_in;
    lv_in = NULL;
    GetLVIn();
    return (lv_in->Equal(old_lv_in));
}

bool CFG_BasicBlock::StepLVOut()
{
    if (old_lv_out)
        delete old_lv_out;

    old_lv_out = lv_out;
    lv_out = NULL;
    GetLVOut();
    lv_undef = false;
    return (lv_out->Equal(old_lv_out));
}

CFG_ControlFlowItem* CFG_BasicBlock::ContainsParloopStart() const
{
    CFG_ControlFlowItem* p = start;
    while (p != NULL && (p == start || !p->IsLeader()))
    {
        if (p->IsParloopStart())
            return p;
        p = p->GetNext();
    }
    return NULL;
}

CFG_ControlFlowItem* CFG_BasicBlock::ContainsParloopEnd() const
{
    CFG_ControlFlowItem* p = start;
    while (p != NULL && (p == start || !p->IsLeader()))
    {
        if (p->IsParloopEnd())
            return p;
        p = p->GetNext();
    }
    return NULL;
}

static SgExpression* CheckIntrinsicParameterFlag(const char* name, int arg, SgExpression* p, unsigned char flag)
{
    const CFG_IntrinsicSubroutineData* info = isAnIntrinsicSubroutine(name);
    if (!info)
        return NULL; //better avoid this
    for (int i = 0; i < info->args; i++)
    {
        const CFG_IntrinsicParameterData* pd = &(info->parameters[i]);
        if (pd->index == arg + 1)
            return (pd->status & flag) != 0 ? p : NULL;
        SgKeywordArgExp* kw = isSgKeywordArgExp(p);
        if (kw)
        {
            SgExpression* a = kw->arg();
            SgExpression* val = kw->value();
            if (strcmp(a->unparse(), pd->name) == 0)
                return (pd->status & flag) != 0 ? val : NULL;
        }
    }
    return NULL;
}

void CFG_BasicBlock::ProcessIntrinsicProcedure(bool isF, int narg, void* f, const char* name)
{
    for (int i = 0; i < narg; i++)
    {
        SgExpression* ar = getProcedureArgument(isF, f, i);
        if (isAnIntrinsicSubroutine(name))
        {
            SgExpression* v = CheckIntrinsicParameterFlag(name, i, ar, INTRINSIC_IN);
            if (v)
            {
                std::set<SgExpression*> tmp;
                AddExprToUse(v, tmp);
            }
        }
        else
        {
            std::set<SgExpression*> tmp;
            AddExprToUse(ar, tmp);
        }
        AddOneExpressionToDef(CheckIntrinsicParameterFlag(name, i, ar, INTRINSIC_OUT), NULL, NULL);
    }
}

CFG_ControlFlowItem* CFG_BasicBlock::GetEnd() const
{
    CFG_ControlFlowItem* p = start;
    CFG_ControlFlowItem* end = p;
    while (p != NULL && (p == start || !p->IsLeader()))
    {
        end = p;
        p = p->GetNext();
    }
    return end;
}

void CFG_BasicBlock::AddUniqObjects(std::set<CFG_ControlFlowItem*> &pointers) const
{
    for (CFG_ControlFlowItem *it = start; it != NULL; it = it->GetNext())
        pointers.insert(it);
}

std::string CFG_BasicBlock::GetGraphVisData()
{
    if (visunparse.length() != 0)
        return visunparse;
    std::string result;
    for (CFG_ControlFlowItem* it = start; it != NULL && (it->IsLeader() == false || it == start); it = it->GetNext())
    {
        if (it->GetStatement() != NULL)
        {
            int ln = it->GetLineNumber();
            char tmp[16];
            sprintf(tmp, "%d: ", ln);
            result += tmp;
            result += it->GetStatement()->unparse();
        }
    }
    visunparse = result;
    return result;
}

bool CFG_BasicBlock::IsEmptyBlock() const
{
    for (CFG_ControlFlowItem* it = start; it != NULL && (it->IsLeader() == false || it == start); it = it->GetNext())
    {
        if (!it->IsEmptyCFI())
            return false;
    }
    return true;
}

void CFG_BasicBlock::PrivateAnalysisForAllCalls()
{
    CFG_ControlFlowItem* p = start;
    while (p != NULL && (p == start || !p->IsLeader()))
    {
        CFG_CallData* c = (CFG_CallData*)p->GetCall();
        //TODO:
        //const char* oic = is_correct;
        //const char* fpn = failed_proc_name;
        //is_correct = NULL;
        //failed_proc_name = NULL;
        if (c != NULL && c != (CFG_CallData*)(-1) && c != (CFG_CallData*)(-2) && c->header != NULL && !c->hasBeenAnalysed)
        {
            c->hasBeenAnalysed = true;
            int stored_fid = SwitchFile(c->file_id);
            c->graph->PrivateAnalyzer();
            SwitchFile(stored_fid);
        }
        //TODO:
        //is_correct = oic;
        //failed_proc_name = fpn;
        p = p->GetNext();
    }
}

CFG_VarSet* CFG_BasicBlock::GetDef()
{
    if (def == NULL)
    {
        def = new CFG_VarSet();
        use = new CFG_VarSet();
        SetDefAndUse();
    }
    return def;
}

CFG_VarSet* CFG_BasicBlock::GetUse()
{
    if (use == NULL)
    {
        use = new CFG_VarSet();
        def = new CFG_VarSet();
        SetDefAndUse();
    }
    return use;
}

bool CFG_BasicBlock::IsVarDefinedAfterThisBlock(CFG_VarEntryInfo* var, bool os)
{
    findentity = var;
    if (def->Belongs(var, os))
    {
        findentity = NULL;
        return true;
    }

    for (auto &p : succ)
    {
        CFG_BasicBlock* b = p.block;
        if (b->ShouldThisBlockBeCheckedAgain(var) && b->IsVarDefinedAfterThisBlock(var, os))
        {
            findentity = NULL;
            return true;
        }
    }
    findentity = NULL;
    return false;
}

bool CFG_BasicBlock::ShouldThisBlockBeCheckedAgain(CFG_VarEntryInfo* var) { return findentity && var && *var == *findentity; }

CFG_ActualDelayedData* CFG_BasicBlock::GetDelayedDataForCall(CFG_CallAnalysisLog* log)
{
    for (CFG_ControlFlowItem* it = start; it != NULL && (!it->IsLeader() || it == start); it = it->GetNext())
    {
        const CFG_CallData* c = it->GetCall();
        void* cf = it->GetFunctionCall();
        bool isFun = true;
        if (!cf) 
        {
            cf = it->GetStatement();
            isFun = false;
        }

        if (c != NULL && c != (CFG_CallData*)(-1) && c != (CFG_CallData*)(-2) && c->graph != NULL)
            return c->graph->ProcessDelayedPrivates(G_pCommons, c, log, cf, isFun, it->GetProc()->file_id);
    }
    return NULL;
}
#endif