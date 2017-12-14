#pragma once
#define ACCAN_DEBUG 0

#define USE_INTRINSIC_DVM_LIST 1

#define PRIVATE_ANALYSIS_NOT_CONDUCTED 650
#define PRIVATE_ANALYSIS_ADD_VAR 651
#define PRIVATE_ANALYSIS_REMOVE_VAR 652
#define PRIVATE_ANALYSIS_NO_RECURSION_ANALYSIS 653

#ifdef __SPF
extern "C" void printLowLevelWarnings(const char *fileName, const int line, const char *message);

extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
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
public:
    inline doLoopItem(int l, SgSymbol* s, ControlFlowItem* i, ControlFlowItem* e) : label(l), name(s), iter(i), emptyAfter(e), current(true), next(NULL)
    { }
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
};

class doLoops{
    doLoopItem* first;
    doLoopItem* current;
    doLoopItem* findLoop(SgSymbol*);
    int parallel_depth;
    SgExpression* prl;
    SgExpression* pPl;
    bool plf;
    SgStatement* prs;
public:
    inline doLoops() : first(NULL), current(NULL), parallel_depth(0)
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
};

class CArrayVarEntryInfo : public CVarEntryInfo
{
public:
    eVariableType GetVarType() const { return VAR_REF_ARRAY_EXP; }
    CVarEntryInfo* GetLeftmostParent() { return this; }
};

#define PRIVATE_GET_LAST_ASSIGN 0

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
    //VarItem* belongs(SgVarRefExp*, bool os = false);
    VarItem* belongs(const CVarEntryInfo*, bool os = false);
    bool equal(VarSet*);
    int count();
    void print();
    void remove(const CVarEntryInfo*);
    VarItem* getFirst();
    ~VarSet();
    inline bool isEmpty()
    { return list == NULL; }
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
    void clearGenKill() { gen.clear(); kill.clear(); }
    void clearDefs() { in_defs.clear(); out_defs.clear(); }
    void addVarToGen(SgSymbol* var, SgExpression* value);
    void addVarToKill(SgSymbol* var);
    void checkFunctionCalls(SgExpression* exp);
    void adjustGenAndKill(SgStatement* st);
    void correctInDefs();
    inline std::map<SymbolKey, SgExpression*>* getGen()
    { return &gen; }

    inline std::set<SymbolKey>* getKill()
    { return &kill; }

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
    void liveAnalysis();
public:
    ControlFlowGraph(bool temp, bool main, ControlFlowItem* item, ControlFlowItem* end);
    ~ControlFlowGraph();
    VarSet* getPrivate();
    VarSet* getUse();
    VarSet* getDef();
    void privateAnalyzer();
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
    SgStatement* cb;
    bool isUsable;
    bool onlyScalars;
    SgSymbol* name;
    AnalysedCallsList* proc;
    AnalysedCallsList* first;
    CommonVarInfo* info;
    CommonDataItem* next;
};

class CommonData
{
    CommonDataItem* list;
public:
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
    VarSet* getDetected() { return detected;  }
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

ControlFlowGraph* GetControlFlowGraphWithCalls(bool, SgStatement*, CallData*, CommonData*);
void FillCFGSets(ControlFlowGraph*);
#ifdef __SPF
void FillCFGInsAndOutsDefs(ControlFlowGraph*);
void CorrectInDefs(ControlFlowGraph*);
void ClearCFGInsAndOutsDefs(ControlFlowGraph*);
bool valueWithRecursion(SymbolKey, SgExpression*);
bool valueWithFunctionCall(SgExpression*);
#endif
void SetUpVars(CommonData*, CallData*, AnalysedCallsList*);
AnalysedCallsList* GetCurrentProcedure();
