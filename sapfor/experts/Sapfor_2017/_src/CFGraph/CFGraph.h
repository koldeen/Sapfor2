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

namespace CFG_GLOBAL_DATA
{
    //static PrivateDelayedItem* privateDelayedList = NULL;
    CFG_CallData* currentProcedure = NULL;
    CFG_CallData* mainProcedure = NULL;
    DoLoopDataList* doLoopList = NULL;
    CFG_CommonData* pCommons;
    CFG_CallData* pCalls;
}

static int SwitchFile(const int file_id)
{
    if (file_id == current_file_id)
        return file_id;
    int stored_file_id = current_file_id;
    current_file_id = file_id;
    current_file = &(CurrentProject->file(current_file_id));
    return stored_file_id;
}

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
    std::vector<CFG_CallData> calls_list;
    bool recursion_flag;

public:
    CFG_Call() : recursion_flag(false) { }

    const CFG_CallData* GetLinkToCall(SgExpression*, SgStatement*, CFG_CommonData*);
    CFG_CallData* AddHeader(SgStatement*, bool isFun, SgSymbol* name, int fid);
    void AssociateGraphWithHeader(SgStatement*, CFG_ControlFlowGraph*);
    const CFG_CallData* IsHeaderInList(SgStatement*) const;
    const CFG_CallData* GetDataForGraph(const CFG_ControlFlowGraph*) const;
    
    void PrintControlFlows() const;
    //REMOVE
    ~CFG_Call()
    {
        for (auto &l : calls_list)
        {
            if (!l.isIntrinsic && l.graph)
            {
                if (l.graph->RemoveRef() && !l.graph->IsMain())
                {
                    delete l.graph;
                    l.graph = NULL;
                }
            }
        }
        calls_list.clear();
    }
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
    CFG_CallData* proc;
    CFG_CallData* first;
    std::vector<CFG_CommonVarInfo> info;

    CFG_CommonDataItem() : cb(NULL), proc(NULL), first(NULL), info(NULL) { }
};

class CFG_CommonData
{
    std::vector<CFG_CommonDataItem*> list;

public:
    const std::vector<CFG_CommonDataItem*>& getList() const { return list; }
    void RegisterCommonBlock(SgStatement*, CFG_CallData*);
    void MarkEndOfCommon(const CFG_CallData*);
    void MarkAsUsed(const CFG_VarSet*, const CFG_CallData*);
    bool CanHaveNonScalarVars(const CFG_CommonDataItem*) const ;
    //void ProcessDelayedPrivates(PrivateDelayedItem*);
    CFG_CommonDataItem* IsThisCommonUsedInProcedure(const CFG_CommonDataItem*, const CFG_CallData*) const;
    CFG_CommonDataItem* GetItemForName(const std::string&, const CFG_CallData*) const;
    vector<CFG_CommonVarInfo> GetCommonsForVarSet(const CFG_VarSet*, const CFG_CallData*) const;
    CFG_CommonDataItem* IsThisCommonVar(const CFG_VarItem&, const CFG_CallData*) const;

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
    void liveAnalysis();

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
    ActualDelayedData* ProcessDelayedPrivates(CFG_CommonData*, AnalysedCallsList*, CallAnalysisLog*, void*, bool, int);
    bool IsMain() { return main; } // change to refs
    void AddRef() { refs++; }
    bool RemoveRef() { return --refs == 0; }
    CFG_ControlFlowItem* getCFI() { return first->getStart(); }
    const std::vector<CFG_CommonVarInfo>& getCommonDef() const { return common_def; }
    const std::vector<CFG_CommonVarInfo>& getCommonUse() const { return common_use; }
    inline CFG_BasicBlock* getFirst() { return first; }
    inline CFG_BasicBlock* getLast() { return last; }

    std::string GetVisualGraph(CFG_CallData*);
    void ResetDrawnStatusForAllItems();

    inline void addCFItoCollection(std::set<CFG_ControlFlowItem*> &collection) const
    {
        for (CFG_BasicBlock *bb = first; bb != NULL; bb = bb->GetLexNext())
            bb->AddUniqObjects(collection);
    }
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
    int file_id;

public:
    CFG_PrivateDelayedItem(CFG_VarSet* d, CFG_VarSet* o, CFG_VarSet* p, CFG_ControlFlowItem* l, CFG_ControlFlowGraph* g, CFG_VarSet* dl, int fd) :
        detected(d), original(o), lp(p), lstart(l), graph(g), delay(dl), file_id(fd)
    { }
    ~CFG_PrivateDelayedItem();

    void PrintWarnings();
    void MoveFromPrivateToLastPrivate(CFG_VarEntryInfo*);
    CFG_VarSet* getDetected() { return detected; }
    CFG_VarSet* getDelayed() { return delay; }
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


// FUNCTIONS
const CFG_IntrinsicSubroutineData* isAnIntrinsicSubroutine(const char* name);
#endif