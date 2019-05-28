#pragma once
#if NEW_CFG
#include <vector>
#include <set>
#include <string>

#include "dvm.h"
#include "CFG_Variables.h"
#include "CFGraph.h"
#include "CFG_Common.h"

class CFG_BasicBlock;
struct CFG_BasicBlockItem;
class CFG_ControlFlowItem;

struct CFG_BasicBlockItem
{
    CFG_BasicBlock* block;
    bool for_jump_flag;
    bool cond_value;
    bool drawn;
    CFG_ControlFlowItem* jmp;

    CFG_BasicBlockItem() : drawn(false) { }    
};

static int getNumberOfArguments(bool isF, void* f)
{
    if (isF)
    {
        SgFunctionCallExp* fc = (SgFunctionCallExp*)f;
        return fc->numberOfArgs();
    }
    SgCallStmt* pc = (SgCallStmt*)f;
    return pc->numberOfArgs();
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

class CFG_BasicBlock
{
    int num;
    CFG_ControlFlowGraph* parent;
    CFG_ControlFlowItem* start;
    CFG_CallData *proc;
    std::vector<CFG_BasicBlockItem> prev;
    std::vector<CFG_BasicBlockItem> succ;
    CFG_BasicBlock* lexNext;
    CFG_BasicBlock* lexPrev;
    CFG_VarSet* def;
    CFG_VarSet* use;
    CFG_VarSet* old_mrd_out;
    CFG_VarSet* old_mrd_in;
    CFG_VarSet* mrd_in;
    CFG_VarSet* mrd_out;
    CFG_VarSet* old_lv_out;
    CFG_VarSet* old_lv_in;
    CFG_VarSet* lv_in;
    CFG_VarSet* lv_out;
    std::vector<CFG_CommonVarInfo> common_def;
    std::vector<CFG_CommonVarInfo> common_use;
    bool undef;
    bool lv_undef;    
    char prev_status;
    bool temp;        
    std::vector<CFG_PrivateDelayedItem> privdata;
    CFG_VarEntryInfo* findentity;
    std::string visname;
    std::string visunparse;

    void SetDefAndUse();
    void AddExprToUse(SgExpression* e, std::set<SgExpression*>, CFG_ArrayVarEntryInfo* = NULL);
    void AddOneExpressionToUse(SgExpression*, SgStatement*, CFG_ArrayVarEntryInfo*);
    void AddOneExpressionToDef(SgExpression*, SgStatement*, CFG_ArrayVarEntryInfo*);

    /*
#ifdef __SPF
    bool varIsPointer(SgSymbol* symbol);
    void processAssignThroughPointer(SgSymbol *symbol, SgExpression *right, SgStatement *st);
    void processPointerAssignment(SgSymbol *symbol, SgExpression *right, SgStatement *st);
    void processReadStat(SgStatement* readSt);
    void addVarUnknownToGen(SymbolKey var, SgStatement *defSt);

    std::map <SymbolKey, std::set<SgExpression*>> gen_p;
    std::set <SymbolKey> kill_p;
    std::map <SymbolKey, std::set<ExpressionValue*>> in_defs_p;
    std::map <SymbolKey, std::set<ExpressionValue*>> out_defs_p;

    std::map <SymbolKey, ExpressionValue*> gen;
    std::set <SymbolKey> kill;
    std::map <SymbolKey, std::set<ExpressionValue*>> in_defs;
    std::map <SymbolKey, std::set<ExpressionValue*>> out_defs;

    std::set <ExpressionValue*> e_gen;
    std::set <ExpressionValue*> e_in;
    std::set <ExpressionValue*> e_out;
#endif*/

public:
    inline CFG_BasicBlock(bool t, CFG_ControlFlowItem* st, int n, CFG_ControlFlowGraph* par, CFG_CallData *pr) :
        temp(t), num(n), start(st), prev(NULL), lexNext(NULL), def(NULL), use(NULL), mrd_in(new CFG_VarSet()), mrd_out(new CFG_VarSet()), undef(true),
        lv_in(new CFG_VarSet()), lv_out(new CFG_VarSet()), lv_undef(false), succ(NULL), lexPrev(NULL), prev_status(-1), parent(par), common_def(NULL),
        common_use(NULL), old_mrd_in(NULL), old_mrd_out(NULL), old_lv_in(NULL), old_lv_out(NULL), privdata(NULL), findentity(NULL), proc(pr)
    { }

    ~CFG_BasicBlock();

    inline const std::vector<CFG_CommonVarInfo>& GetCommonDef() const { return common_def; }
    inline const std::vector<CFG_CommonVarInfo>& GetCommonUse() const { return common_use; }

    inline void SetNext(CFG_BasicBlock* next) { lexNext = next; }
    inline void SetPrev(CFG_BasicBlock* prev) { lexPrev = prev; }

    void AddToPrev(CFG_BasicBlock* pr, bool, bool, CFG_ControlFlowItem*);
    void AddToSucc(CFG_BasicBlock* su, bool, bool, CFG_ControlFlowItem*);

    inline CFG_VarSet* GetDef()
    {
        if (def == NULL)
        {
            def = new CFG_VarSet();
            use = new CFG_VarSet();
            SetDefAndUse();
        }
        return def;
    }

    inline CFG_VarSet* GetUse()
    {
        if (use == NULL)
        {
            use = new CFG_VarSet();
            def = new CFG_VarSet();
            SetDefAndUse();
        }
        return use;
    }

    CFG_VarSet* GetMrdIn(bool);

    inline CFG_VarSet* GetMrdOut(bool la)
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

    inline CFG_VarSet* GetLVIn()
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

    inline CFG_VarSet* GetLVOut()
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

    inline bool StepMrdIn(bool la)
    {
        if (old_mrd_in)
            delete old_mrd_in;

        old_mrd_in = mrd_in;
        mrd_in = NULL;
        GetMrdIn(la);
        return (mrd_in->Equal(old_mrd_in));
    }

    inline bool StepMrdOut(bool la)
    {
        if (old_mrd_out)
            delete old_mrd_out;

        old_mrd_out = mrd_out;
        mrd_out = NULL;
        GetMrdOut(la);
        undef = false;
        return (mrd_out->Equal(old_mrd_out));        
    }

    inline bool StepLVIn()
    {
        if (old_lv_in)
            delete old_lv_in;

        old_lv_in = lv_in;
        lv_in = NULL;
        GetLVIn();
        return (lv_in->Equal(old_lv_in));
    }

    inline bool StepLVOut()
    {
        if (old_lv_out)
            delete old_lv_out;

        old_lv_out = lv_out;
        lv_out = NULL;
        GetLVOut();
        lv_undef = false;        
        return (lv_out->Equal(old_lv_out));
    }

    inline CFG_ControlFlowItem* containsParloopStart() const
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

    inline CFG_ControlFlowItem* containsParloopEnd() const
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

    inline  CFG_ControlFlowItem* getStart() const { return start; }
    inline  CFG_ControlFlowItem* getEnd() const
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

    inline CFG_BasicBlock* GetLexNext() { return lexNext; }
    inline CFG_BasicBlock* GetLexPrev() { return lexPrev; }
    inline const std::vector<CFG_BasicBlockItem>& GetPrev() const { return prev; }
    inline const std::vector<CFG_BasicBlockItem>& GetSucc() const { return succ; }
    inline std::vector<CFG_BasicBlockItem>& GetSuccToMod() { return succ; }
    inline CFG_VarSet* GetLiveIn() { return lv_in; }
    inline int GetNum() { return num; }
    inline void SetDelayedData(const std::vector<CFG_PrivateDelayedItem> &p) { privdata = p; }
    inline const std::vector<CFG_PrivateDelayedItem>& GetDelayedData() const { return privdata; }

    inline void Print() const
    {
        printf("block %d: prev: ", num);
        for (auto &p : prev)
            printf("%d ", p.block->num);        
        printf("\n");
    }

    inline void MarkAsReached()
    {
        prev_status = 1;        
        for (auto &s : succ)
        {
            CFG_BasicBlock* b = s.block;
            if (b->prev_status == -1)
                b->MarkAsReached();
        }
    }

    inline bool HasPrev() const { return prev_status == 1; }

    static inline SgExpression* getProcedureArgument(bool isF, void *f, const int i)
    {
        SgExpression *arg = NULL;
        if (isF)
        {
            SgFunctionCallExp* fc = (SgFunctionCallExp*)f;
            arg = fc->arg(i);
        }
        else
        {
            SgCallStmt *pc = (SgCallStmt*)f;
            arg = pc->arg(i);
        }
        return arg;
    }

    inline void ProcessProcedureHeader(bool isF, SgProcHedrStmt *header, void *f, const char* name)
    {
        if (!header)
        {
            //TODO:
            //is_correct = "no header found";
            //failed_proc_name = name;
            return;
        }

        for (int i = 0; i < header->numberOfParameters(); ++i)
        {
            int stored = SwitchFile(header->getFileId());
            SgSymbol *arg = header->parameter(i);
            SwitchFile(stored);

            if (arg->attributes() & (IN_BIT))
            {
                SgExpression *ar = getProcedureArgument(isF, f, i);
                std::set<SgExpression*> tmp;
                AddExprToUse(ar, tmp);
            }
            else if (arg->attributes() & (INOUT_BIT))
            {
                std::set<SgExpression*> tmp;
                AddExprToUse(getProcedureArgument(isF, f, i), tmp);
                AddOneExpressionToDef(getProcedureArgument(isF, f, i), NULL, NULL);
            }
            else if (arg->attributes() & (OUT_BIT))
                AddOneExpressionToDef(getProcedureArgument(isF, f, i), NULL, NULL);
            else
            {
                //TODO:
                //is_correct = "no bitflag set for pure procedure";
                break;
            }
        }
    }

    inline void ProcessIntrinsicProcedure(bool isF, int narg, void* f, const char* name)
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

    void ProcessUserProcedure(bool isFun, void* call, const CFG_CallData *c);

    inline void ProcessProcedureWithoutBody(bool isF, void* f, bool out) 
    {
        for (int i = 0; i < getNumberOfArguments(isF, f); i++) 
        {
            std::set<SgExpression*> tmp;
            AddExprToUse(getProcedureArgument(isF, f, i), tmp);
            if (out)
                AddOneExpressionToDef(getProcedureArgument(isF, f, i), NULL, NULL);
        }
    }

    inline SgSymbol* GetProcedureName(bool isFunc, void* f) const
    {
        if (isFunc) 
        {
            SgFunctionCallExp* fc = (SgFunctionCallExp*)f;
            return fc->funName();
        }
        SgCallStmt* pc = (SgCallStmt*)f;
        return pc->name();
    }

    inline void PrivateAnalysisForAllCalls()
    {
        CFG_ControlFlowItem* p = start;
        while (p != NULL && (p == start || !p->IsLeader())) 
        {
            CFG_CallData* c = p->GetCall();
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

    ActualDelayedData* GetDelayedDataForCall(CallAnalysisLog*);

    inline bool IsVarDefinedAfterThisBlock(CFG_VarEntryInfo* var, bool os)
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

    bool ShouldThisBlockBeCheckedAgain(CFG_VarEntryInfo* var) { return findentity && var && *var == *findentity; }

    inline std::string GetGraphVisDescription()
    {
        if (visname.length() != 0)
            return visname;
        char tmp[16];
        sprintf(tmp, "%d", num);
        visname = tmp;
        return visname;
    }

    inline std::string GetGraphVisData()
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

    bool IsEmptyBlock() const
    {
        for (CFG_ControlFlowItem* it = start; it != NULL && (it->IsLeader() == false || it == start); it = it->GetNext()) 
        {
            if (!it->IsEmptyCFI())
                return false;
        }
        return true;
    }

    std::string GetEdgesForBlock(const std::string &name, bool original, const std::string&);

    inline void AddUniqObjects(std::set<CFG_ControlFlowItem*> &pointers) const
    {
        for (CFG_ControlFlowItem *it = start; it != NULL; it = it->GetNext())
            pointers.insert(it);
    }

    /*
#ifdef __SPF
    AnalysedCallsList* getProc() { return proc; }
    void clearGenKill() { gen.clear(); kill.clear(); e_gen.clear(); }
    void clearGenKillPointers() { gen_p.clear(); kill_p.clear(); }
    void clearDefs() { in_defs.clear(); out_defs.clear(); e_in.clear(); e_out.clear(); }
    void clearDefsPointers() { in_defs_p.clear(); out_defs_p.clear(); }
    void addVarToGen(SymbolKey var, SgExpression* value, SgStatement *defSt);
    void addVarToKill(const SymbolKey &key);
    void checkFuncAndProcCalls(ControlFlowItem* cfi);
    void adjustGenAndKill(ControlFlowItem* cfi);
    void adjustGenAndKillP(ControlFlowItem* cfi);
    std::set<SymbolKey>* getOutVars();
    void correctInDefsSimple();
    bool correctInDefsIterative();
    bool expressionIsAvailable(ExpressionValue* expValue);
    //const std::map<SymbolKey, std::set<SgExpression*>> getReachedDefinitions(SgStatement* stmt);
    const std::map<SymbolKey, std::set<ExpressionValue*>> getReachedDefinitionsExt(SgStatement* stmt);
    void initializeOut();
    void initializeEOut(std::set<ExpressionValue*>& allEDefs);
    bool updateEDefs();

    inline std::map<SymbolKey, std::set<SgExpression*>>* getGenP() { return &gen_p; }
    inline std::set<SymbolKey>* getKillP() { return &kill_p; }
    inline void setInDefsP(std::map<SymbolKey, std::set<ExpressionValue*>>* inDefsP) { in_defs_p = *inDefsP; }
    inline std::map<SymbolKey, std::set<ExpressionValue*>>* getInDefsP() { return &in_defs_p; }
    inline std::map<SymbolKey, std::set<ExpressionValue*>>* getOutDefsP() { return &out_defs_p; }

    inline std::map<SymbolKey, ExpressionValue*>* getGen() { return &gen; }
    inline std::set<SymbolKey>* getKill() { return &kill; }
    inline void setInDefs(std::map<SymbolKey, std::set<ExpressionValue*>>* inDefs) { in_defs = *inDefs; }
    inline std::map<SymbolKey, std::set<ExpressionValue*>>* getInDefs() { return &in_defs; }
    inline std::map<SymbolKey, std::set<ExpressionValue*>>* getOutDefs() { return &out_defs; }

    inline std::set<ExpressionValue*>* getEGen() { return &e_gen; }
    inline std::set<ExpressionValue*>* getEIn() { return &e_in; }
    inline std::set<ExpressionValue*>* getEOut() { return &e_out; }
#endif
    */
};

class CFG_ControlFlowItem
{
    int stmtNo;
    SgLabel* label;
    CFG_ControlFlowItem *jmp;
    bool for_jump_flag;
    SgLabel* label_jump;
    CFG_ControlFlowItem* prev;
    CFG_ControlFlowItem *next;
    bool leader;
    int bbno;
    bool is_parloop_start;
    SgExpression* private_list;
    bool is_parloop_end;
    SgStatement* prl_stmt;
    const CFG_CallData* call;
    SgFunctionCallExp* func;
    SgExpression* pPl;
    bool fPl;
    bool drawn;
    const CFG_CallData* thisproc;    
    SgStatement* originalStatement;
    CFG_ControlFlowItem* conditionFriend;

    SgStatement *stmt;
    SgExpression *expr;

public:
    inline CFG_ControlFlowItem(const CFG_CallData *proc) : 
        stmtNo(-1), label(NULL), jmp(NULL), label_jump(NULL), next(NULL), leader(false), bbno(0), 
        stmt(NULL), is_parloop_start(false), is_parloop_end(false), private_list(NULL), call(NULL), 
        func(NULL), thisproc(proc), originalStatement(NULL), for_jump_flag(false), drawn(false),
        prev(NULL), conditionFriend(NULL)
    { }

    inline CFG_ControlFlowItem(SgStatement *s, CFG_ControlFlowItem *n, const CFG_CallData *proc, const CFG_CallData *c = NULL) :
        stmtNo(-1), label(s ? s->label() : NULL), jmp(NULL), label_jump(NULL), next(n), leader(false), 
        bbno(0), stmt(s), is_parloop_start(false), is_parloop_end(false), private_list(NULL), 
        call(c), func(NULL), thisproc(proc), originalStatement(NULL), for_jump_flag(false), drawn(false),
        prev(NULL), conditionFriend(NULL)
    {
        if (n)
            n->prev = this;
    }

    inline CFG_ControlFlowItem(SgExpression *e, CFG_ControlFlowItem *j, CFG_ControlFlowItem *n, SgLabel* l, const CFG_CallData *proc, bool fjf = false, const CFG_CallData *c = NULL) :
        stmtNo(-1), label(l), jmp(j), label_jump(NULL), next(n), leader(false), bbno(0), 
        expr(e), is_parloop_start(false), is_parloop_end(false), private_list(NULL), call(c), 
        func(NULL), thisproc(proc), originalStatement(NULL), for_jump_flag(fjf), drawn(false),
        prev(NULL), conditionFriend(NULL)
    {
        if (n)
            n->prev = this;        
    }

    inline CFG_ControlFlowItem(SgExpression *e, SgLabel* j, CFG_ControlFlowItem* n, SgLabel* l, const CFG_CallData* proc, const CFG_CallData* c = NULL) :
        stmtNo(-1), label(l), jmp(NULL), label_jump(j), next(n), leader(false), bbno(0), 
        expr(e), is_parloop_start(false), is_parloop_end(false), private_list(NULL), call(c), 
        func(NULL), thisproc(proc), originalStatement(NULL), for_jump_flag(false), drawn(false),
        prev(NULL), conditionFriend(NULL)
    {
        if (n)
            n->prev = this;        
    }

    inline void SetOriginalStatement(SgStatement* s) { originalStatement = s; }
    inline SgStatement* GetOriginalStatement() const { return originalStatement; }

    inline bool IsEnumerated() const { return stmtNo >= 0; }

    inline void SetBBno(int bb) { bbno = bb; }
    inline int GetBBno() const { return bbno; }

    inline void AddNextItem(CFG_ControlFlowItem *n) { next = n; if (n) n->prev = this; }

    inline void MakeParloopStart() { is_parloop_start = true; }
    inline void MakeParloopEnd() { is_parloop_end = true; }
    inline bool IsParloopStart() const { return is_parloop_start; }
    inline bool IsParloopEnd() const { return is_parloop_end; }
    inline bool IsUnconditionalJump() const { return ((jmp != NULL || label_jump != NULL) && expr == NULL); }

    inline SgStatement* GetStatement() const
    {
        if (jmp == NULL)
            return stmt;
        else
            return NULL;
    }

    inline SgExpression* GetExpression() const 
    {
        if (jmp != NULL)
            return expr;
        else
            return NULL;
    }

    inline CFG_ControlFlowItem* GetJump() const { return jmp; }
    inline CFG_ControlFlowItem* GetNext() const { return next; }
    inline void SetLeader() { leader = true; }
    inline unsigned int GetStmtNo() const { return stmtNo; }
    inline void SetStmtNo(unsigned int no) { stmtNo = no; }
    inline int IsLeader() const { return leader; }
    inline void SetLabel(SgLabel* l) { label = l; }
    inline SgLabel* GetLabel() const { return label; }
    inline void SetLabelJump(SgLabel* l) { label_jump = l; }
    inline SgLabel* GetLabelJump() const { return label_jump; }
    inline void InitJump(CFG_ControlFlowItem* item) { jmp = item; }

    inline void SetPrivateList(SgExpression* p, SgStatement* s, SgExpression* m, bool mf)
    { private_list = p; prl_stmt = s; pPl = m; fPl = mf; }

    inline SgExpression* GetPrivateList() const { return private_list; }
    inline SgStatement* GetPrivateListStatement() const { return prl_stmt; }
    inline SgExpression* GetExpressionToModifyPrivateList(bool* rhs) const { if (rhs) *rhs = fPl; return pPl; }
    inline const CFG_CallData* GetCall() const { return call; }
    inline void SetFunctionCall(SgFunctionCallExp* f) { func = f; }
    inline SgFunctionCallExp* GetFunctionCall() const { return func; }
    inline const CFG_CallData* GetProc() const { return thisproc; }
    inline bool IsForJumpFlagSet() const { return for_jump_flag; }
    inline bool IsEmptyCFI() const { return GetStatement() == NULL; }
    inline void SetIsDrawn() { drawn = true; }
    inline void ResetDrawnStatus() { drawn = false; }
    inline bool IsDrawn() const { return drawn; }
    inline CFG_ControlFlowItem* GetPrev() { return prev; }
    inline void SetConditionFriend(CFG_ControlFlowItem* f) { conditionFriend = f; }
    inline CFG_ControlFlowItem* GetFriend() const { return conditionFriend; }

    inline int GetLineNumber()
    {
        if (GetStatement() == NULL)
            return 0;
        if (GetStatement()->lineNumber() == 0) 
        {
            if (GetOriginalStatement() == NULL)
                return 0;
            return GetOriginalStatement()->lineNumber();
        }
        return GetStatement()->lineNumber();
    }

    void PrintDebugInfo() const
    {
        if (jmp == NULL && stmt == NULL && func != NULL)
            printf("FUNCTION CALL: %s\n", func->unparse());
        if (jmp == NULL)
        {
            if (stmt != NULL)
            {
                if (label != NULL)
                    printf("%d: %s %s %s lab %4d %s", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ", label->id(), stmt->unparse());
                else
                    printf("%d: %s %s %s          %s", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ", stmt->unparse());
            }
            else
            {
                if (label != NULL)
                    printf("%d: %s %s %s lab %4d \n", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ", label->id());
                else
                    printf("%d: %s %s %s         \n", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ");
            }
        }
        else
        {
            if (expr == NULL)
            {
                if (label != NULL)
                    printf("%d: %s %s %s lab %4d       goto %d\n", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ", label->id(), jmp->GetStmtNo());
                else
                    printf("%d: %s %s %s                goto %d\n", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ", jmp->GetStmtNo());
            }
            else
            {
                if (label != NULL)
                    printf("%d: %s %s %s lab %4d       if %s goto %d\n", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ", label->id(), expr->unparse(), jmp->GetStmtNo());
                else
                    printf("%d: %s %s %s                if %s goto %d\n", stmtNo, this->IsLeader() ? "L" : " ", this->IsParloopStart() ? "S" : " ", this->IsParloopEnd() ? "E" : " ", expr->unparse(), jmp->GetStmtNo());
            }
        }
    }
};
#endif