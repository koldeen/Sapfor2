#pragma once
#if NEW_CFG
#include <vector>
#include <set>
#include <string>

#include "dvm.h"
#include "CFG_Variables.h"
#include "CFG_BasicBlock.h"

using namespace std;

struct CFG_CallData;
class CFG_Call;
struct CFG_DoLoopDataItem;
class CFG_DoLoopDataList;
class CFG_CommonData;
struct CFG_CommonDataItem;
class CFG_ControlFlowGraph;
class CFG_BasicBlock;
class CFG_ControlFlowItem;
class CFG_PrivateDelayedItem;
class CFG_DoLoops;
class CFG_DoLoopDataList;
class CFG_ArrayVarEntryInfo;
class CFG_VarEntryInfo;
class CFG_VarSet;
struct CFG_ActualDelayedData;
struct CFG_CallAnalysisLog;
struct CFG_VarItem;

extern CFG_PrivateDelayedItem* G_privateDelayedList;
extern const CFG_CallData* G_currentProcedure;
extern const CFG_CallData* G_mainProcedure;
extern CFG_DoLoopDataList* G_doLoopList;
extern CFG_CommonData* G_pCommons;
extern CFG_Call* G_pCalls;
extern const char* G_is_correct;
extern const char* G_failed_proc_name;

struct CFG_CallData
{
    SgStatement* header;
    CFG_ControlFlowGraph* graph;
    bool isIntrinsic;
    bool isPure;
    bool isFunction;    
    bool hasBeenAnalysed;
    bool isCurrent;
    int file_id;
    const char* funName;

public:
    CFG_CallData(SgStatement* h, bool intr, bool pure, bool fun, const char* name, int fid) :
        header(h), isIntrinsic(intr), isPure(pure), isFunction(fun), hasBeenAnalysed(false), graph(NULL), funName(name), file_id(fid)
    { }

    bool IsArgIn(int num, CFG_ArrayVarEntryInfo*&) const;
    bool IsArgOut(int num, CFG_ArrayVarEntryInfo*&) const;
    const char* GetFuncName() const { return funName; }
    bool IsIntrinsic() const { return isIntrinsic; }
};

class CFG_Call
{
    std::vector<CFG_CallData*> calls_list;
    bool recursion_flag;

public:
    CFG_Call() : recursion_flag(false) { }

    const CFG_CallData* GetLinkToCall(SgExpression*, SgStatement*, CFG_CommonData*);
    const CFG_CallData* AddHeader(SgStatement*, bool isFun, SgSymbol* name, int fid);
    void AssociateGraphWithHeader(SgStatement*, CFG_ControlFlowGraph*);
    const CFG_CallData* IsHeaderInList(SgStatement*) const;
    const CFG_CallData* GetDataForGraph(const CFG_ControlFlowGraph*) const;
    
    void PrintControlFlows() const;
    //REMOVE
    ~CFG_Call();
};

struct CFG_DoLoopDataItem
{
    int file_id;
    SgStatement* statement;
    SgExpression* l;
    SgExpression* r;
    SgExpression* st;
    SgSymbol* loop_var;

    inline CFG_DoLoopDataItem() : l(NULL), r(NULL), st(NULL), loop_var(NULL), statement(NULL), file_id(-1) { }
};

class CFG_DoLoopDataList
{
    vector<CFG_DoLoopDataItem> list;

public:    
    inline void AddLoop(int file_id, SgStatement* st, SgExpression* l, SgExpression* r, SgExpression* step, SgSymbol* lv)     
    {
        CFG_DoLoopDataItem nt;
        nt.file_id = file_id;
        nt.statement = st;
        nt.l = l;
        nt.r = r;
        nt.st = step;
        nt.loop_var = lv;
        list.push_back(nt);
    }

    inline const CFG_DoLoopDataItem* FindLoop(SgStatement* st)
    {
        for (auto &elem : list)
            if (elem.statement == st)
                return &elem;        
        return NULL;
    }
};


struct CFG_CommonVarInfo
{
    CFG_VarEntryInfo* var;
    bool isPendingLastPrivate;
    bool isInUse;
    CFG_CommonDataItem* parent;

    CFG_CommonVarInfo() : var(NULL), parent(NULL) { }
};

struct CFG_CommonDataItem
{
    SgStatement *cb;
    std::vector<SgExpression*> commonRefs;
    bool isUsable;
    bool onlyScalars;
    std::string name;
    const CFG_CallData* proc;
    const CFG_CallData* first;
    std::vector<CFG_CommonVarInfo> info;

    CFG_CommonDataItem() : cb(NULL), proc(NULL), first(NULL), info(NULL) { }
};

class CFG_CommonData
{
    std::vector<CFG_CommonDataItem*> list;

public:
    const std::vector<CFG_CommonDataItem*>& getList() const { return list; }
    void RegisterCommonBlock(SgStatement*, const CFG_CallData*);
    void MarkEndOfCommon(const CFG_CallData*);
    void MarkAsUsed(const CFG_VarSet*, const CFG_CallData*);
    bool CanHaveNonScalarVars(const CFG_CommonDataItem*) const ;
    //void ProcessDelayedPrivates(PrivateDelayedItem*);
    CFG_CommonDataItem* IsThisCommonUsedInProcedure(const CFG_CommonDataItem*, const CFG_CallData*) const;
    CFG_CommonDataItem* GetItemForName(const std::string&, const CFG_CallData*) const;
    vector<CFG_CommonVarInfo> GetCommonsForVarSet(const CFG_VarSet*, const CFG_CallData*) const;
    CFG_CommonDataItem* IsThisCommonVar(const CFG_VarItem*, const CFG_CallData*) const;

    //TODO: REMOVE
    ~CFG_CommonData()
    {
        for (auto &i : list)            
            delete i;
    }
};

class CFG_ControlFlowGraph
{
    CFG_BasicBlock* last;
    CFG_BasicBlock* first;
    CFG_VarSet* def;
    CFG_VarSet* use;
    CFG_VarSet* pri;
    std::vector<CFG_CommonVarInfo> common_def;
    bool cdf;
    std::vector<CFG_CommonVarInfo> common_use;
    bool cuf;
    bool temp;
    bool main;
    int refs;
    bool hasBeenAnalyzed;
    void LiveAnalysis();

    //TODO:
/*#ifdef __SPF
    std::set<SymbolKey> pointers;
#endif*/
public:
    CFG_ControlFlowGraph(bool temp, bool main, CFG_ControlFlowItem* item, CFG_ControlFlowItem* end);
    ~CFG_ControlFlowGraph();
    CFG_VarSet* GetPrivate();
    CFG_VarSet* GetUse();
    CFG_VarSet* GetDef();
    void PrivateAnalyzer();
    bool ProcessOneParallelLoop(CFG_ControlFlowItem* lstart, CFG_BasicBlock* of, CFG_BasicBlock*& p, bool);
    CFG_ActualDelayedData* ProcessDelayedPrivates(CFG_CommonData*, const CFG_CallData*, CFG_CallAnalysisLog*, void*, bool, int);
    bool IsMain() { return main; } // change to refs
    void AddRef() { refs++; }
    bool RemoveRef() { return --refs == 0; }
    CFG_ControlFlowItem* getCFI();
    const std::vector<CFG_CommonVarInfo>& getCommonDef() const { return common_def; }
    const std::vector<CFG_CommonVarInfo>& getCommonUse() const { return common_use; }
    inline CFG_BasicBlock* getFirst() { return first; }
    inline CFG_BasicBlock* getLast() { return last; }

    std::string GetVisualGraph(CFG_Call*);
    void ResetDrawnStatusForAllItems();
    void addCFItoCollection(std::set<CFG_ControlFlowItem*> &collection) const;
    //TODO
/*#ifdef __SPF
    std::set<SymbolKey>* getPointers() { return &pointers; };
#endif*/
};

class CFG_PrivateDelayedItem
{
    CFG_VarSet* detected;
    CFG_VarSet* original;
    CFG_VarSet* lp;
    CFG_VarSet* delay;
    CFG_ControlFlowItem* lstart;
    CFG_ControlFlowGraph* graph;
    CFG_PrivateDelayedItem *next;
    int file_id;

public:
    CFG_PrivateDelayedItem(CFG_VarSet* d, CFG_VarSet* o, CFG_VarSet* p, CFG_ControlFlowItem* l, CFG_PrivateDelayedItem *n, CFG_ControlFlowGraph* g, CFG_VarSet* dl, int fd) :
        detected(d), original(o), lp(p), lstart(l), graph(g), delay(dl), file_id(fd), next(n)
    { }

    CFG_PrivateDelayedItem() { }
    ~CFG_PrivateDelayedItem();

    void PrintWarnings();
    void MoveFromPrivateToLastPrivate(CFG_VarEntryInfo*);
    CFG_VarSet* GetDetected() { return detected; }
    CFG_VarSet* GetDelayed() { return delay; }
};

struct CFG_IntrinsicParameterData
{
    int index;
    const char* name;
    unsigned char status;
};

struct CFG_IntrinsicSubroutineData
{
    const char* name;
    int args;
    CFG_IntrinsicParameterData parameters[10];
};

class CFG_DoLoopItem
{
    int label;
    SgSymbol* name;
    CFG_ControlFlowItem* iter;
    CFG_ControlFlowItem* emptyAfter;
    bool current;
    CFG_DoLoopItem* next;
    int parallel_depth;
    SgExpression* prl;
    SgExpression* pPl;
    bool plf;
    SgStatement* prs;
public:
    inline CFG_DoLoopItem(int l, SgSymbol* s, CFG_ControlFlowItem* i, CFG_ControlFlowItem* e) :
        label(l), name(s), iter(i), emptyAfter(e), current(true), next(NULL), parallel_depth(-1)
    { } 

    inline void HandleNewItem(CFG_DoLoopItem* it) { SetParallelDepth(it->parallel_depth, it->prl, it->prs, it->pPl, it->plf); }
    inline void SetNext(CFG_DoLoopItem* n) { next = n; }
    inline void SetNewLabel(int l) { label = l; }
    inline CFG_ControlFlowItem* GetSourceForCycle() const { return iter; }
    inline CFG_ControlFlowItem* GetSourceForExit() const { return emptyAfter; }
    inline SgSymbol* GetName() const { return name; }
    inline CFG_DoLoopItem* GetNext() const { return next; }
    inline int GetLabel() const { return label; }

    inline void SetParallelDepth(int k, SgExpression* pl, SgStatement* ps, SgExpression* pPl, bool plf)
    {
        parallel_depth = k; prl = pl; prs = ps; this->pPl = pPl; this->plf = plf;
    }

    inline SgStatement* GetParallelStatement() const { return prs; }
    inline bool IsLastParallel() 
    {
        if (parallel_depth > 0)
            return --parallel_depth == 0;
        return 0;
    }
    inline SgExpression* GetPrivateList() const { return prl; }
    inline SgExpression* GetExpressionToModifyPrivateList(bool &rhs) const { rhs = plf; return pPl; }
};

class CFG_DoLoops
{
    CFG_DoLoopItem* first;
    CFG_DoLoopItem* current;

    inline CFG_DoLoopItem* FindLoop(SgSymbol *s) const
    {
        CFG_DoLoopItem* l = first;
        while (l != NULL) 
        {
            if (l->GetName() == s)
                return l;
            l = l->GetNext();
        }
        return NULL;
    }

public:
    inline CFG_DoLoops() : first(NULL), current(NULL) { }

    inline CFG_ControlFlowItem* GetSourceForCycle() const { return current ? current->GetSourceForCycle() : NULL; }
    inline CFG_ControlFlowItem* GetSourceForCycle(SgSymbol* loop) const { return loop ? FindLoop(loop)->GetSourceForCycle() : GetSourceForCycle(); }
    inline CFG_ControlFlowItem* GetSourceForExit() { return current ? current->GetSourceForExit() : NULL; }
    inline CFG_ControlFlowItem* GetSourceForExit(SgSymbol* loop) { return loop ? FindLoop(loop)->GetSourceForExit() : GetSourceForExit(); }
    inline void SetParallelDepth(int k, SgExpression* pl, SgStatement* ps, SgExpression* pPl, bool plf) { current->SetParallelDepth(k, pl, ps, pPl, plf); }
    inline SgStatement* GetParallelStatement() { return current->GetParallelStatement(); }
    inline bool IsLastParallel() { return current && current->IsLastParallel(); }
    inline SgExpression* GetPrivateList() { return current->GetPrivateList(); }
    inline SgExpression* GetExpressionToModifyPrivateList(bool &rhs) { return current->GetExpressionToModifyPrivateList(rhs); }
    inline void AddLoop(int l, SgSymbol* s, CFG_ControlFlowItem* i, CFG_ControlFlowItem* e)
    {
        CFG_DoLoopItem* nl = new CFG_DoLoopItem(l, s, i, e);
        if (first == NULL)
            first = current = nl;
        else {
            current->SetNext(nl);
            nl->HandleNewItem(current);
            current = nl;
        }
    }

    CFG_ControlFlowItem* EndLoop(CFG_ControlFlowItem* last);

    inline CFG_ControlFlowItem* CheckStatementForLoopEnding(int label, CFG_ControlFlowItem* last)
    {
        if (current == NULL || label == -1 || label != current->GetLabel())
            return last;
        return CheckStatementForLoopEnding(label, EndLoop(last));
    }

    inline ~CFG_DoLoops()
    {
        for (CFG_DoLoopItem *it = first; it != NULL; )
        {
            CFG_DoLoopItem *tmp = it;
            it = it->GetNext();
            delete tmp;
        }
    }
};


struct CFG_ActualDelayedData
{
    CFG_PrivateDelayedItem *original;
    vector<CFG_CommonVarInfo> commons;
    CFG_VarSet* buse;    
    const CFG_CallData* call;
    CFG_ActualDelayedData *next;

    void MoveVarFromPrivateToLastPrivate(CFG_VarEntryInfo*, const CFG_CommonVarInfo *c, CFG_VarSet*);
    void RemoveVarFromCommonList(const CFG_CommonVarInfo *c);

    CFG_ActualDelayedData() : original(NULL), commons(NULL), call(NULL), next(NULL)
    { }    
};

//TODO: REMOVE
struct CFG_CallAnalysisLog
{
    const CFG_CallData* el;
    int depth;
    CFG_CallAnalysisLog* prev;

    CFG_CallAnalysisLog() : el(NULL), prev(NULL)
    { }
};

struct CFG_GRAPH
{  
    CFG_Call *calls;
    CFG_CommonData *commons;
    CFG_DoLoopDataList *doloopList;
    CFG_ControlFlowGraph *graph;
};

// FUNCTIONS
void SetUpVars(CFG_CommonData* commons, CFG_Call *calls, const CFG_CallData *m, CFG_DoLoopDataList* list);
const CFG_IntrinsicSubroutineData* isAnIntrinsicSubroutine(const char* name);
CFG_ControlFlowGraph* GetControlFlowGraphWithCalls(bool main, SgStatement* start, CFG_Call* calls, CFG_CommonData* commons);
CFG_GRAPH* buildCFG(SgStatement *mainUnit);
#endif