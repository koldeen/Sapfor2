#pragma once
#if NEW_CFG
#include <vector>
#include <set>
#include <string>

#include "dvm.h"
#include "CFG_Variables.h"

using namespace std;

class CFG_CallData;
class CFG_Call;
struct CFG_DoLoopDataItem;
class CFG_DoLoopDataList;

static int SwitchFile(const int file_id)
{
    if (file_id == current_file_id)
        return file_id;
    int stored_file_id = current_file_id;
    current_file_id = file_id;
    current_file = &(CurrentProject->file(current_file_id));
    return stored_file_id;
}

class CFG_CallData
{
    SgStatement* header;
    ControlFlowGraph* graph;
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

    CFG_CallData* GetLinkToCall(SgExpression*, SgStatement*, CommonData*) const;
    CFG_CallData* AddHeader(SgStatement*, bool isFun, SgSymbol* name, int fid);
    void AssociateGraphWithHeader(SgStatement*, ControlFlowGraph*);
    CFG_CallData* IsHeaderInList(SgStatement*) const;
    CFG_CallData* GetDataForGraph(ControlFlowGraph*) const;
    
    void PrintControlFlows();
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
#endif