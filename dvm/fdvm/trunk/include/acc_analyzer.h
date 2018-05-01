#pragma once
#define ACCAN_DEBUG 0

#define USE_INTRINSIC_DVM_LIST 1

#define PRIVATE_ANALYSIS_NOT_CONDUCTED 650
#define PRIVATE_ANALYSIS_ADD_VAR 651
#define PRIVATE_ANALYSIS_REMOVE_VAR 652
#define PRIVATE_ANALYSIS_NO_RECURSION_ANALYSIS 653

#ifdef __SPF
extern "C" void printLowLevelWarnings(const char *fileName, const int line, const char *message, const int group);
extern "C" void printLowLevelNote(const char *fileName, const int line, const char *message, const int group);

extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
bool IsPureProcedureACC(SgSymbol* s);
#endif

struct AnalysedCallsList;

class ControlFlowItem
{
    int stmtNo;
    SgLabel* label;
    ControlFlowItem *jmp;
    SgLabel* label_jump;
    ControlFlowItem *next;
    bool leader;
    int bbno;
    bool is_parloop_start;
    SgExpression* private_list;
    bool is_parloop_end;
    SgStatement* prl_stmt;
    AnalysedCallsList* call;
    SgFunctionCallExp* func;
    SgExpression* pPl;
    bool fPl;
    AnalysedCallsList* thisproc;
    int refs;
    SgStatement* originalStatement;
    union
    {
        SgStatement *stmt;
        SgExpression *expr;
    };
public:
    inline ControlFlowItem(AnalysedCallsList* proc) : stmtNo(-1), label(NULL), jmp(NULL), label_jump(NULL), next(NULL), leader(false), bbno(0), stmt(NULL), is_parloop_start(false), is_parloop_end(false), private_list(NULL), call(NULL), func(NULL), thisproc(proc), refs(0), originalStatement(NULL)
    { };

    inline ControlFlowItem(SgStatement *s, ControlFlowItem *n, AnalysedCallsList* proc, AnalysedCallsList* c = NULL) : stmtNo(-1), label(s ? s->label() : NULL), jmp(NULL), label_jump(NULL), next(n), leader(false), bbno(0), refs(0), stmt(s), is_parloop_start(false), is_parloop_end(false), private_list(NULL), call(c), func(NULL), thisproc(proc), originalStatement(NULL)
    { };

    inline ControlFlowItem(SgExpression *e, ControlFlowItem *j, ControlFlowItem *n, SgLabel* l, AnalysedCallsList* proc, AnalysedCallsList* c = NULL) : stmtNo(-1), label(l), jmp(j), label_jump(NULL), next(n), leader(false), refs(0), bbno(0), expr(e), is_parloop_start(false), is_parloop_end(false), private_list(NULL), call(c), func(NULL), thisproc(proc), originalStatement(NULL)
    { };

    inline ControlFlowItem(SgExpression *e, SgLabel* j, ControlFlowItem* n, SgLabel* l, AnalysedCallsList* proc, AnalysedCallsList* c = NULL) : stmtNo(-1), label(l), jmp(NULL), label_jump(j), next(n), leader(false), bbno(0), refs(0), expr(e), is_parloop_start(false), is_parloop_end(false), private_list(NULL), call(c), func(NULL), thisproc(proc), originalStatement(NULL)
    { };

    inline void setOriginalStatement(SgStatement* s)
    { originalStatement = s; }

    inline SgStatement* getOriginalStatement()
    { return originalStatement; }

    inline bool isEnumerated()
    { return stmtNo >= 0; }

    inline void setBBno(int bb)
    { bbno = bb; }

    inline int getBBno()
    { return bbno; }

    inline void AddNextItem(ControlFlowItem *n)
    { next = n; }

    inline void MakeParloopStart()
    { is_parloop_start = true; }

    inline void MakeParloopEnd()
    { is_parloop_end = true; }

    inline bool IsParloopStart()
    { return is_parloop_start; }

    inline bool IsParloopEnd()
    { return is_parloop_end; }

    inline bool isUnconditionalJump()
    { return ((jmp != NULL || label_jump != NULL) && expr == NULL); }

    inline void AddRef()
    { refs++; }

    inline bool RemRef()
    { return --refs == 0; }

    inline SgStatement* getStatement()
    {
        if (jmp == NULL)
            return stmt;
        else
            return NULL;
    }

    inline SgExpression* getExpression()
    {
        if (jmp != NULL)
            return expr;
        else
            return NULL;
    }

    inline ControlFlowItem* getJump()
    { return jmp; }

    inline ControlFlowItem* getNext()
    { return next; }

    inline void setLeader()
    { leader = true; }

    inline unsigned int getStmtNo()
    { return stmtNo; }

    inline void setStmtNo(unsigned int no)
    { stmtNo = no; }

    inline int isLeader()
    { return leader; }

    inline void setLabel(SgLabel* l)
    { label = l; }

    inline SgLabel* getLabel()
    { return label; }

    inline void setLabelJump(SgLabel* l)
    { label_jump = l; }

    inline SgLabel* getLabelJump()
    { return label_jump; }

    inline void initJump(ControlFlowItem* item)
    { jmp = item; }

    inline void setPrivateList(SgExpression* p, SgStatement* s, SgExpression* m, bool mf)
    { private_list = p; prl_stmt = s; pPl = m; fPl = mf; }

    inline SgExpression* getPrivateList()
    { return private_list; }

    inline SgStatement* getPrivateListStatement()
    { return prl_stmt; }

    inline SgExpression* getExpressionToModifyPrivateList(bool* rhs)
    { if (rhs) *rhs = fPl; return pPl; }

    inline AnalysedCallsList* getCall()
    { return call; }

    inline void setFunctionCall(SgFunctionCallExp* f)
    { func = f; }

    inline SgFunctionCallExp* getFunctionCall()
    { return func; }

    inline AnalysedCallsList* getProc()
    { return thisproc; }

#if ACCAN_DEBUG
    void printDebugInfo();

#endif

    ~ControlFlowItem()
    {
        /*if (jmp != NULL)
            delete expr; */// XXX: removing SgExpression may be dangerous
    }
};

class doLoopItem{
    int label;
    SgSymbol* name;
    ControlFlowItem* iter;
    ControlFlowItem* emptyAfter;
    bool current;
    doLoopItem* next;
    int parallel_depth;
    SgExpression* prl;
    SgExpression* pPl;
    bool plf;
    SgStatement* prs;
public:
    inline doLoopItem(int l, SgSymbol* s, ControlFlowItem* i, ControlFlowItem* e) : label(l), name(s), iter(i), emptyAfter(e), current(true), next(NULL), parallel_depth(-1)
    { }
    inline void HandleNewItem(doLoopItem* it)
    { setParallelDepth(it->parallel_depth, it->prl, it->prs, it->pPl, it->plf); }
    inline void setNext(doLoopItem* n)
    { next = n; }
    inline void setNewLabel(int l)
    { label = l; }
    inline ControlFlowItem* getSourceForCycle()
    { return iter; }
    inline ControlFlowItem* getSourceForExit()
    { return emptyAfter; }
    inline SgSymbol* getName()
    { return name; }
    inline doLoopItem* getNext()
    { return next; }
    inline int getLabel()
    { return label; }
    inline void setParallelDepth(int k, SgExpression* pl, SgStatement* ps, SgExpression* pPl, bool plf)
    { parallel_depth = k; prl = pl; prs = ps; this->pPl = pPl; this->plf = plf; }
    inline SgStatement* GetParallelStatement()
    { return prs; }
    inline bool isLastParallel()
    {
        if (parallel_depth > 0)
            return --parallel_depth == 0;
        return 0;
    }
    inline SgExpression* getPrivateList()
    { return prl; }
    inline SgExpression* getExpressionToModifyPrivateList(bool* rhs)
    { if (rhs) *rhs = plf; return pPl; }
};

class doLoops{
    doLoopItem* first;
    doLoopItem* current;
    doLoopItem* findLoop(SgSymbol*);
public:
    inline doLoops() : first(NULL), current(NULL)
    { }
    void addLoop(int l, SgSymbol* s, ControlFlowItem* i, ControlFlowItem* e);
    inline ControlFlowItem* getSourceForCycle()
    { return current ? current->getSourceForCycle() : NULL; }
    inline ControlFlowItem* getSourceForCycle(SgSymbol* loop)
    { return loop ? findLoop(loop)->getSourceForCycle() : getSourceForCycle(); }
    inline ControlFlowItem* getSourceForExit()
    { return current ? current->getSourceForExit() : NULL; }
    inline ControlFlowItem* getSourceForExit(SgSymbol* loop)
    { return loop ? findLoop(loop)->getSourceForExit() : getSourceForExit(); }
    ControlFlowItem* endLoop(ControlFlowItem* last);
    ControlFlowItem* checkStatementForLoopEnding(int label, ControlFlowItem* item);
    inline void setParallelDepth(int k, SgExpression* pl, SgStatement* ps, SgExpression* pPl, bool plf)
    { current->setParallelDepth(k, pl, ps, pPl, plf); }
    inline SgStatement* GetParallelStatement()
    { return current->GetParallelStatement(); }
    inline bool isLastParallel()
    {  return current && current->isLastParallel(); }
    inline SgExpression* getPrivateList()
    { return current->getPrivateList(); }
    inline SgExpression* getExpressionToModifyPrivateList(bool* rhs)
    { return current->getExpressionToModifyPrivateList(rhs); }
    inline ~doLoops();
};

struct LabelCFI{
    int l;
    ControlFlowItem* item;
};

struct CLAStatementItem
{
    SgStatement* stmt;
    CLAStatementItem* next;
    ~CLAStatementItem();
    CLAStatementItem* GetLast();
};

enum eVariableType
{
    VAR_REF_VAR_EXP,
    VAR_REF_RECORD_EXP,
    VAR_REF_ARRAY_EXP
};


#define PRIVATE_GET_LAST_ASSIGN 0

class CVarEntryInfo;

struct VarItem
{
    CVarEntryInfo* var;
    int file_id;
    //CLAStatementItem* lastAssignments;
#if PRIVATE_GET_LAST_ASSIGN
    std::list<SgStatement*> lastAssignments;
#endif
    VarItem* next;
};

class CArrayVarEntryInfo;

class VarSet
{
    VarItem* list;
public:
    inline VarSet() : list(NULL)
    {}

    void addToSet(CVarEntryInfo*, SgStatement*);
    void intersect(VarSet*, bool);
    void unite(VarSet*, bool);
    void minus(VarSet*);
    void minusFinalize(VarSet*);
    bool RecordBelong(CVarEntryInfo*);
    void LeaveOnlyRecords();
    void RemoveDoubtfulCommonVars(AnalysedCallsList*);
    VarItem* GetArrayRef(CArrayVarEntryInfo*);
    //VarItem* belongs(SgVarRefExp*, bool os = false);
    VarItem* belongs(const CVarEntryInfo*, bool os = false);
    bool equal(VarSet*);
    int count();
    void print();
    void remove(const CVarEntryInfo*);
    VarItem* getFirst();
    ~VarSet();
    inline bool isEmpty()
    {
        return list == NULL;
    }
};

class CVarEntryInfo
{
    SgSymbol* symbol;
    int references;
public:
    CVarEntryInfo(SgSymbol* s) : symbol(s), references(1) {};
    virtual ~CVarEntryInfo() {};
    virtual eVariableType GetVarType() const = 0;
    virtual CVarEntryInfo* Clone(SgSymbol*) const = 0;
    virtual CVarEntryInfo* Clone() const = 0;
    virtual CVarEntryInfo* GetLeftmostParent() = 0;
    virtual void RegisterUsage(VarSet* def, VarSet* use, SgStatement* st) = 0;
    virtual void RegisterDefinition(VarSet* def, SgStatement* st) = 0;
    SgSymbol* GetSymbol() const { return symbol; }
    virtual bool operator==(const CVarEntryInfo& rhs) const = 0;
    void AddReference() { references++; }
    bool RemoveReference() { return --references == 0; }
};

class CScalarVarEntryInfo: public CVarEntryInfo
{
public:
    CScalarVarEntryInfo(SgSymbol* s) : CVarEntryInfo(s) {};
    ~CScalarVarEntryInfo() {};
    eVariableType GetVarType() const { return VAR_REF_VAR_EXP; }
    CVarEntryInfo* Clone(SgSymbol* s) const { return new CScalarVarEntryInfo(s); }
    CVarEntryInfo* Clone() const { return new CScalarVarEntryInfo(GetSymbol()); }
    bool operator==(const CVarEntryInfo& rhs) const { return rhs.GetVarType() == VAR_REF_VAR_EXP && rhs.GetSymbol() == GetSymbol(); }
    CVarEntryInfo* GetLeftmostParent() { return this; }
    void RegisterUsage(VarSet* def, VarSet* use, SgStatement* st) {
        if (def == NULL || !def->belongs(this))
            use->addToSet(this, st);
    }
    void RegisterDefinition(VarSet* def, SgStatement* st) { def->addToSet(this, st); };
};

class CRecordVarEntryInfo : public CVarEntryInfo
{
    CVarEntryInfo* parent;
public:
    CRecordVarEntryInfo(SgSymbol* s, CVarEntryInfo* ptr) : CVarEntryInfo(s), parent(ptr) {};
    ~CRecordVarEntryInfo()
    {
        if (parent->RemoveReference())
            delete parent;
    }
    eVariableType GetVarType() const { return VAR_REF_RECORD_EXP; }
    CVarEntryInfo* Clone(SgSymbol* s) const { return new CRecordVarEntryInfo(s, parent->Clone()); }
    CVarEntryInfo* Clone() const { return new CRecordVarEntryInfo(GetSymbol(), parent->Clone()); }
    bool operator==(const CVarEntryInfo& rhs) const { return rhs.GetVarType() == VAR_REF_RECORD_EXP && rhs.GetSymbol() == GetSymbol() &&
        parent && static_cast<const CRecordVarEntryInfo&>(rhs).parent && *static_cast<const CRecordVarEntryInfo&>(rhs).parent == *parent; }
    CVarEntryInfo* GetLeftmostParent() { return parent->GetLeftmostParent(); }
    void RegisterUsage(VarSet* def, VarSet* use, SgStatement* st) {
        if (def == NULL || !def->belongs(this))
            use->addToSet(this, st);
    }
    void RegisterDefinition(VarSet* def, SgStatement* st) { def->addToSet(this, st); };
};

struct ArraySubscriptData
{
    int coefs[2];
    SgStatement* fs;
};

class CArrayVarEntryInfo : public CVarEntryInfo
{
    int subscripts;
    ArraySubscriptData* data;
public:
    CArrayVarEntryInfo(SgSymbol* s, SgArrayRefExp* r);
    CArrayVarEntryInfo(SgSymbol* s, int sub, ArraySubscriptData* d);
    ~CArrayVarEntryInfo() { if (subscripts > 0) delete[] data; }
    bool CompareSubscripts(const CArrayVarEntryInfo&) const;
    CVarEntryInfo* Clone(SgSymbol* s) const { return new CArrayVarEntryInfo(s, subscripts, data); }
    CVarEntryInfo* Clone() const { return new CArrayVarEntryInfo(GetSymbol(), subscripts, data); }
    bool operator==(const CVarEntryInfo& rhs) const { return rhs.GetVarType() == VAR_REF_ARRAY_EXP && rhs.GetSymbol() == GetSymbol() &&
        CompareSubscripts(static_cast<const CArrayVarEntryInfo&>(rhs)); }
    friend CArrayVarEntryInfo* operator-(const CArrayVarEntryInfo&, const CArrayVarEntryInfo&);
    friend CArrayVarEntryInfo* operator+(const CArrayVarEntryInfo&, const CArrayVarEntryInfo&);
    CArrayVarEntryInfo& operator+=(const CArrayVarEntryInfo&);
    CArrayVarEntryInfo& operator*=(const CArrayVarEntryInfo&);
    friend CArrayVarEntryInfo* operator*(const CArrayVarEntryInfo&, const CArrayVarEntryInfo&);
    eVariableType GetVarType() const { return VAR_REF_ARRAY_EXP; }
    CVarEntryInfo* GetLeftmostParent() { return this; }
    void RegisterUsage(VarSet* def, VarSet* use, SgStatement* st);
    void RegisterDefinition(VarSet* def, SgStatement* st);
};

class CBasicBlock;
class ControlFlowGraph;
struct AnalysedCallsList;
class PrivateDelayedItem;

struct BasicBlockItem
{
    CBasicBlock* block;
    BasicBlockItem* next;
};

struct CommonVarSet;
struct ActualDelayedData;

struct CallAnalysisLog
{
    AnalysedCallsList* el;
    int depth;
    CallAnalysisLog* prev;
};

struct CExprList
{
    SgExpression* entry;
    CExprList* next;
};

#ifdef __SPF
class SymbolKey {
private:
    SgSymbol* var;
public:
    SymbolKey(SgSymbol* v): var(v) {}
    SymbolKey(std::string& varName): var(new SgSymbol(VARIABLE_NAME, varName.c_str())) {}

    inline SgSymbol* getVar() const { return var; }

    inline bool operator<(const SymbolKey& rhs) const
    {
        return strcmp(var->identifier(), rhs.var->identifier()) < 0;
    }

    inline bool operator==(const SymbolKey& rhs) const
    {
        return strcmp(var->identifier(), rhs.var->identifier()) == 0;
    }

    inline bool operator==(SgSymbol* rhs) const
    {
        return strcmp(var->identifier(), rhs->identifier()) == 0;
    }
};
#endif

class CBasicBlock
{
    int num;
    ControlFlowGraph* parent;
    ControlFlowItem* start;
    AnalysedCallsList* proc;
    BasicBlockItem* prev;
    BasicBlockItem* succ;
    CBasicBlock* lexNext;
    CBasicBlock* lexPrev;
    VarSet* def;
    VarSet* use;
    VarSet* old_mrd_out;
    VarSet* old_mrd_in;
    VarSet* mrd_in;
    VarSet* mrd_out;
    VarSet* old_lv_out;
    VarSet* old_lv_in;
    VarSet* lv_in;
    VarSet* lv_out;
    CommonVarSet* common_def;
    CommonVarSet* common_use;
    bool undef;
    bool lv_undef;
    void setDefAndUse();
    char prev_status;
    bool temp;
    void addExprToUse(SgExpression* e, CExprList*);
    void AddOneExpressionToUse(SgExpression*, SgStatement*);
    void AddOneExpressionToDef(SgExpression*, SgStatement*);
    PrivateDelayedItem* privdata;
    CVarEntryInfo* findentity;
#ifdef __SPF
    std::map <SymbolKey, SgExpression*> gen;
    std::set <SymbolKey> kill;
    std::map <SymbolKey, std::map<std::string, SgExpression*>> in_defs;
    std::map <SymbolKey, std::map<std::string, SgExpression*>> out_defs;
#endif
public:
    inline CBasicBlock(bool t, ControlFlowItem* st, int n, ControlFlowGraph* par, AnalysedCallsList* pr) : temp(t), num(n), start(st), prev(NULL), lexNext(NULL), def(NULL), use(NULL), mrd_in(new VarSet()), mrd_out(new VarSet()), undef(true),
        lv_in(new VarSet()), lv_out(new VarSet()), lv_undef(false), succ(NULL), lexPrev(NULL), prev_status(-1), parent(par), common_def (NULL), common_use(NULL), old_mrd_in(NULL), old_mrd_out(NULL), old_lv_in(NULL), old_lv_out(NULL),
        privdata(NULL), findentity(NULL), proc(pr)
    { st->AddRef(); }

    ~CBasicBlock();
    inline CommonVarSet* getCommonDef() { return common_def; }
    inline CommonVarSet* getCommonUse() { return common_use; }

    inline void setNext(CBasicBlock* next)
    { lexNext = next; }

    inline void setPrev(CBasicBlock* prev)
    { lexPrev = prev; }

    void addToPrev(CBasicBlock* pr);
    void addToSucc(CBasicBlock* su);
    VarSet* getDef();
    VarSet* getUse();
    VarSet* getMrdIn(bool);
    VarSet* getMrdOut(bool);
    VarSet* getLVIn();
    VarSet* getLVOut();
    bool stepMrdIn(bool);
    bool stepMrdOut(bool);
    bool stepLVIn();
    bool stepLVOut();

    ControlFlowItem* containsParloopStart();
    ControlFlowItem* containsParloopEnd();

    ControlFlowItem* getStart();
    ControlFlowItem* getEnd();

    inline CBasicBlock* getLexNext()
    { return lexNext; }

    inline CBasicBlock* getLexPrev()
    { return lexPrev; }

    inline BasicBlockItem* getPrev()
    { return prev; }

    inline BasicBlockItem* getSucc()
    { return succ; }

    inline VarSet* getLiveIn()
    { return lv_in; }

    inline int getNum()
    { return num; }

    inline void SetDelayedData(PrivateDelayedItem* p)
    { privdata = p; }

    inline PrivateDelayedItem* GetDelayedData()
    { return privdata; }

    void print();
    void markAsReached();
    bool hasPrev();

    void ProcessProcedureHeader(bool, SgProcHedrStmt*, void*, const char*);
    void ProcessIntrinsicProcedure(bool, int narg, void* f, const char*);
    void ProcessUserProcedure(bool isFun, void* call, AnalysedCallsList* c);
    void ProcessProcedureWithoutBody(bool, void*, bool);
    SgExpression* GetProcedureArgument(bool, void*, int);
    int GetNumberOfArguments(bool, void*);
    SgSymbol* GetProcedureName(bool, void*);
    void PrivateAnalysisForAllCalls();
    ActualDelayedData* GetDelayedDataForCall(CallAnalysisLog*);
    bool IsVarDefinedAfterThisBlock(CVarEntryInfo*, bool);
    bool ShouldThisBlockBeCheckedAgain(CVarEntryInfo* var) { return findentity && var && *var == *findentity; }

#ifdef __SPF
    AnalysedCallsList* getProc() { return proc; }
    void clearGenKill() { gen.clear(); kill.clear(); }
    void clearDefs() { in_defs.clear(); out_defs.clear(); }
    void addVarToGen(SgSymbol* var, SgExpression* value);
    void addVarToKill(const SymbolKey &key);
    void checkFuncAndProcCalls(ControlFlowItem* cfi);
    void adjustGenAndKill(ControlFlowItem* cfi);
    std::set<SymbolKey>* getOutVars();
    void correctInDefsSimple();
    bool correctInDefsIterative();
    inline std::map<SymbolKey, SgExpression*>* getGen()
    { return &gen; }

    inline std::set<SymbolKey>* getKill()
    { return &kill; }

    inline void setInDefs(std::map<SymbolKey, std::map<std::string, SgExpression*>>* inDefs)
    { in_defs = *inDefs; }

    inline std::map<SymbolKey, std::map<std::string, SgExpression*>>* getInDefs()
    { return &in_defs; }

    inline std::map<SymbolKey, std::map<std::string, SgExpression*>>* getOutDefs()
    { return &out_defs; }
#endif
};

struct CommonVarInfo;

struct CommonVarSet
{
    CommonVarInfo* cvd;
    CommonVarSet* next;
    CommonVarSet(const CommonVarSet&);
    CommonVarSet() {}
};

struct ActualDelayedData;
class CommonData;


class ControlFlowGraph
{
    CBasicBlock* last;
    CBasicBlock* first;
    VarSet* def;
    VarSet* use;
    VarSet* pri;
    CommonVarSet* common_def;
    bool cdf;
    CommonVarSet* common_use;
    bool cuf;
    bool temp;
    bool main;
    int refs;
    bool hasBeenAnalyzed;
    void liveAnalysis();
public:
    ControlFlowGraph(bool temp, bool main, ControlFlowItem* item, ControlFlowItem* end);
    ~ControlFlowGraph();
    VarSet* getPrivate();
    VarSet* getUse();
    VarSet* getDef();
    void privateAnalyzer();
    bool ProcessOneParallelLoop(ControlFlowItem* lstart, CBasicBlock* of, CBasicBlock*& p, bool);
    ActualDelayedData* ProcessDelayedPrivates(CommonData*, AnalysedCallsList*, CallAnalysisLog*);
    bool IsMain() { return main; } // change to refs
    void AddRef() { refs++; }
    bool RemoveRef() { return --refs == 0; }
    ControlFlowItem* getCFI() { return first->getStart(); }
    CommonVarSet* getCommonDef() { return common_def; }
    CommonVarSet* getCommonUse() { return common_use; }
	inline CBasicBlock* getFirst() { return first; }
	inline CBasicBlock* getLast() { return last; }
};

struct AnalysedCallsList {
    SgStatement* header;
    ControlFlowGraph* graph;
    bool isIntrinsic;
    bool isPure;
    bool isFunction;
    AnalysedCallsList* next;
    bool hasBeenAnalysed;
    bool isCurrent;
    int file_id;
    AnalysedCallsList(SgStatement* h, bool intr, bool pure, bool fun, const char* name, int fid) { header = h; isIntrinsic = intr; isPure = pure; isFunction = fun; hasBeenAnalysed = false; graph = NULL; funName = name; file_id = fid; }
    bool isArgIn(int num);
    bool isArgOut(int num);
    const char* funName;
    bool IsIntrinsic()
    { return isIntrinsic; }
};
class CommonData;

class CallData
{
    AnalysedCallsList* calls_list;
    bool recursion_flag;
public:
    AnalysedCallsList* getLinkToCall(SgExpression*, SgStatement*, CommonData*);
    AnalysedCallsList* AddHeader(SgStatement*, bool isFun, SgSymbol* name, int fid);
    void AssociateGraphWithHeader(SgStatement*, ControlFlowGraph*);
    AnalysedCallsList* IsHeaderInList(SgStatement*);
    CallData() { recursion_flag = false; calls_list = NULL; }
    void printControlFlows();
    ~CallData();
};

struct CommonDataItem;

struct CommonVarInfo
{
    CVarEntryInfo* var;
    bool isPendingLastPrivate;
    bool isInUse;
    CommonDataItem* parent;
    CommonVarInfo* next;
};

struct CommonDataItem
{
    SgStatement *cb;
    std::vector<SgExpression*> commonRefs;
    bool isUsable;
    bool onlyScalars;
    std::string name;
    AnalysedCallsList* proc;
    AnalysedCallsList* first;
    CommonVarInfo* info;
    CommonDataItem* next;
};

class CommonData
{
    CommonDataItem* list;
public:
    CommonDataItem* getList() { return list; }
    void RegisterCommonBlock(SgStatement*, AnalysedCallsList*);
    void MarkEndOfCommon(AnalysedCallsList*);
    void MarkAsUsed(VarSet*, AnalysedCallsList*);
    bool CanHaveNonScalarVars(CommonDataItem*);
    //void ProcessDelayedPrivates(PrivateDelayedItem*);
    CommonDataItem* IsThisCommonUsedInProcedure(CommonDataItem*, AnalysedCallsList*);
    CommonVarSet* GetCommonsForVarSet(VarSet*, AnalysedCallsList*);
    CommonDataItem* IsThisCommonVar(VarItem*, AnalysedCallsList*);
    CommonData() : list(NULL) {}
    ~CommonData();
};

class PrivateDelayedItem
{
    VarSet* detected;
    VarSet* original;
    VarSet* lp;
    VarSet* delay;
    ControlFlowItem* lstart;
    ControlFlowGraph* graph;
    PrivateDelayedItem* next;
    int file_id;
public:
    PrivateDelayedItem(VarSet* d, VarSet* o, VarSet* p, ControlFlowItem* l, PrivateDelayedItem* n, ControlFlowGraph* g, VarSet* dl, int fd) : detected(d), original(o), lp(p), lstart(l), next(n), graph(g), delay(dl), file_id(fd) {}
    ~PrivateDelayedItem();
    void PrintWarnings();
    void MoveFromPrivateToLastPrivate(CVarEntryInfo*);
    VarSet* getDetected() { return detected; }
    VarSet* getDelayed() { return delay; }
};

#define MAX_ARGS_FOR_INTRINSIC 10
#define INTRINSIC_IN 1
#define INTRINSIC_OUT 2

struct IntrinsicParameterData
{
    int index;
    const char* name;
    unsigned char status;
};

struct IntrinsicSubroutineData
{
    const char* name;
    int args;
    IntrinsicParameterData parameters[MAX_ARGS_FOR_INTRINSIC];
};

struct ActualDelayedData
{
    PrivateDelayedItem* original;
    CommonVarSet* commons;
    VarSet* buse;
    ActualDelayedData* next;
    AnalysedCallsList* call;
    void MoveVarFromPrivateToLastPrivate(CVarEntryInfo*, CommonVarSet*, VarSet*);
    void RemoveVarFromCommonList(CommonVarSet*);
};

#ifdef __SPF
struct FuncCallSE
{
    std::string funcName;
    std::set<std::string> calls;
    FuncCallSE(std::string &n, std::set<std::string>& v): funcName(n), calls(v) {}
};

class CommonVarsOverseer
{
private:
    bool inited;
public:
    std::map<std::string, std::set<std::string>> funcKillsVars;
    CommonVarsOverseer(): inited(false), funcKillsVars(std::map<std::string, std::set<std::string>>()) {}
    bool isInited() { return inited; }
    void riseInited() { inited = true; }
    void addKilledVar(std::string varName, std::string funcName)
    {
        auto founded = funcKillsVars.find(funcName);
        if(founded == funcKillsVars.end())
            funcKillsVars.insert(founded, std::make_pair(funcName, std::set<std::string>()))->second.insert(varName);
        else
            founded->second.insert(varName);
    }

    std::set<std::string>* killedVars(const std::string& funcName)
    {
        auto founded = funcKillsVars.find(funcName);
        if(founded == funcKillsVars.end())
            return NULL;
        return &(founded->second);
    }
};

#endif

ControlFlowGraph* GetControlFlowGraphWithCalls(bool, SgStatement*, CallData*, CommonData*);
void FillCFGSets(ControlFlowGraph*);
#ifdef __SPF
void FillCFGInsAndOutsDefs(ControlFlowGraph*, std::map<SymbolKey, std::map<std::string, SgExpression*>>* inDefs, CommonVarsOverseer *overseer_Ptr);
void CorrectInDefs(ControlFlowGraph*);
void ClearCFGInsAndOutsDefs(ControlFlowGraph*);
bool valueWithRecursion(SymbolKey, SgExpression*);
bool valueWithFunctionCall(SgExpression*);
bool valueWithArrayReference(SgExpression *exp);
bool argIsReplaceable(int i, AnalysedCallsList* callData);
void mergeDefs(std::map<SymbolKey, std::map<std::string, SgExpression*>> *main, std::map<SymbolKey, std::map<std::string, SgExpression*>> *term, std::set<SymbolKey>* allowedVars);
void showDefsOfGraph(ControlFlowGraph *CGraph);
bool symbolInExpression(const SymbolKey &symbol, SgExpression *exp);
#endif
void SetUpVars(CommonData*, CallData*, AnalysedCallsList*);
AnalysedCallsList* GetCurrentProcedure();
