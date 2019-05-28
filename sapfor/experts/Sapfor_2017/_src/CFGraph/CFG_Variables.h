#pragma once
#if NEW_CFG
#include "dvm.h"
#include <vector>
#include "CFGraph.h"

class CFG_VarEntryInfo;
class CFG_VarSet;
class CFG_ArrayVarEntryInfo;

struct CFG_ArraySubscriptData;
struct CFG_VarItem;

enum CFG_eVariableType
{
    VAR_REF_VAR_EXP,
    VAR_REF_RECORD_EXP,
    VAR_REF_ARRAY_EXP
};

struct CFG_ArraySubscriptData
{
    bool defined;
    int bound_modifiers[2];
    int step;
    int coefs[2];
    const CFG_DoLoopDataItem *loop;
    SgExpression* left_bound;
    SgExpression* right_bound;

    CFG_ArraySubscriptData() : loop(NULL), left_bound(NULL), right_bound(NULL) { }    
};

struct CFG_VarItem
{
    CFG_VarEntryInfo* var;
    CFG_VarEntryInfo* ov;
    int file_id;

    CFG_VarItem() : var(NULL), ov(NULL), file_id(-1) { }
};

class CFG_VarSet
{
    std::vector<CFG_VarItem> list;

public:
    void AddToSet(const CFG_VarEntryInfo*, SgStatement*, CFG_VarEntryInfo* ov = NULL);
    void PossiblyAffectArrayEntry(const CFG_ArrayVarEntryInfo*) const;
    void Intersect(const CFG_VarSet*, bool, bool);
    void Unite(const CFG_VarSet*, bool);
    void Minus(const CFG_VarSet*, bool complete = false);
    void MinusFinalize(const CFG_VarSet*, bool complete = false);
    bool RecordBelong(const CFG_VarEntryInfo*) const;
    void LeaveOnlyRecords();
    void RemoveDoubtfulCommonVars(CFG_CallData*);
    const CFG_VarItem* GetArrayRef(const CFG_ArrayVarEntryInfo*) const;
    const CFG_VarItem* Belongs(const CFG_VarEntryInfo*, bool os = false) const;
    const CFG_VarItem* Belongs(SgSymbol*, bool os = false) const;
    bool Equal(CFG_VarSet*) const;
    int Count() const { return list.size(); }
    void Print() const;
    void Remove(const CFG_VarEntryInfo*);
    const std::vector<CFG_VarItem>& GetList() const { return list; }

    inline bool isEmpty() const { return list.size() == 0; }
};

class CFG_VarEntryInfo
{
    SgSymbol* symbol;
    int references;

public:
    CFG_VarEntryInfo(SgSymbol* s) : symbol(s), references(1) { }

    virtual ~CFG_VarEntryInfo() { }
    virtual CFG_eVariableType GetVarType() const = 0;
    virtual CFG_VarEntryInfo* Clone(SgSymbol*) const = 0;
    virtual CFG_VarEntryInfo* Clone() const = 0;
    virtual const CFG_VarEntryInfo* GetLeftmostParent() const = 0;
    virtual void RegisterUsage(const CFG_VarSet* def, CFG_VarSet* use, SgStatement* st) = 0;
    virtual void RegisterDefinition(CFG_VarSet* def, const CFG_VarSet* use, SgStatement* st) = 0;
    SgSymbol* GetSymbol() const { return symbol; }
    virtual bool operator==(const CFG_VarEntryInfo& rhs) const = 0;
    void AddReference() { references++; }
    bool RemoveReference() 
    { 
        --references; 
        return references == 0; 
    }
    void SwitchSymbol(SgSymbol* s) { symbol = s; }
};

class CFG_ArrayVarEntryInfo : public CFG_VarEntryInfo
{
    int subscripts;
    bool disabled;
    std::vector<CFG_ArraySubscriptData> data;
public:
    CFG_ArrayVarEntryInfo(SgSymbol* s, SgArrayRefExp* r);
    CFG_ArrayVarEntryInfo(SgSymbol* s, int sub, int ds, const std::vector<CFG_ArraySubscriptData>& d);

    CFG_VarEntryInfo* Clone(SgSymbol* s) const { return new CFG_ArrayVarEntryInfo(s, subscripts, disabled, data); }
    CFG_VarEntryInfo* Clone() const { return new CFG_ArrayVarEntryInfo(GetSymbol(), subscripts, disabled, data); }
    bool operator==(const CFG_VarEntryInfo& rhs) const { return rhs.GetVarType() == VAR_REF_ARRAY_EXP && rhs.GetSymbol() == GetSymbol(); }
    friend CFG_ArrayVarEntryInfo* operator-(const CFG_ArrayVarEntryInfo&, const CFG_ArrayVarEntryInfo&);
    friend CFG_ArrayVarEntryInfo* operator+(const CFG_ArrayVarEntryInfo&, const CFG_ArrayVarEntryInfo&);
    CFG_ArrayVarEntryInfo& operator+=(const CFG_ArrayVarEntryInfo&);
    CFG_ArrayVarEntryInfo& operator-=(const CFG_ArrayVarEntryInfo&);
    CFG_ArrayVarEntryInfo& operator*=(const CFG_ArrayVarEntryInfo&);
    CFG_eVariableType GetVarType() const { return VAR_REF_ARRAY_EXP; }
    const CFG_VarEntryInfo* GetLeftmostParent() const { return this; }
    void RegisterUsage(const CFG_VarSet* def, CFG_VarSet* use, SgStatement* st);
    void RegisterDefinition(CFG_VarSet* def, const CFG_VarSet* use, SgStatement* st);
    bool HasActiveElements() const;
    void MakeInactive();
    void ProcessChangesToUsedEntry(const CFG_ArrayVarEntryInfo*);        
};

class CFG_ScalarVarEntryInfo : public CFG_VarEntryInfo
{
public:
    CFG_ScalarVarEntryInfo(SgSymbol* s) : CFG_VarEntryInfo(s) { }
    
    CFG_eVariableType GetVarType() const { return VAR_REF_VAR_EXP; }
    CFG_VarEntryInfo* Clone(SgSymbol* s) const { return new CFG_ScalarVarEntryInfo(s); }
    CFG_VarEntryInfo* Clone() const { return new CFG_ScalarVarEntryInfo(GetSymbol()); }
    bool operator==(const CFG_VarEntryInfo& rhs) const { return rhs.GetVarType() == VAR_REF_VAR_EXP && rhs.GetSymbol() == GetSymbol(); }
    const CFG_VarEntryInfo* GetLeftmostParent() const { return this; }
    void RegisterUsage(const CFG_VarSet* def, CFG_VarSet* use, SgStatement* st)
    {
        if (def == NULL || !def->Belongs(this))
            use->AddToSet(this, st);
    }
    void RegisterDefinition(CFG_VarSet* def, const CFG_VarSet* use, SgStatement* st) { def->AddToSet(this, st); }
};

class CFG_RecordVarEntryInfo : public CFG_VarEntryInfo
{
    CFG_VarEntryInfo* parent;
public:
    CFG_RecordVarEntryInfo(SgSymbol* s, CFG_VarEntryInfo* ptr) : CFG_VarEntryInfo(s), parent(ptr) { }

    ~CFG_RecordVarEntryInfo()
    {
        if (parent->RemoveReference())
            delete parent;
    }

    CFG_eVariableType GetVarType() const { return VAR_REF_RECORD_EXP; }
    CFG_VarEntryInfo* Clone(SgSymbol* s) const { return new CFG_RecordVarEntryInfo(s, parent->Clone()); }
    CFG_VarEntryInfo* Clone() const { return new CFG_RecordVarEntryInfo(GetSymbol(), parent->Clone()); }
    bool operator==(const CFG_VarEntryInfo& rhs) const 
    {
        return rhs.GetVarType() == VAR_REF_RECORD_EXP && rhs.GetSymbol() == GetSymbol() &&
            parent && static_cast<const CFG_RecordVarEntryInfo&>(rhs).parent && *static_cast<const CFG_RecordVarEntryInfo&>(rhs).parent == *parent;
    }
    const CFG_VarEntryInfo* GetLeftmostParent() const { return parent->GetLeftmostParent(); }
    void RegisterUsage(const CFG_VarSet* def, CFG_VarSet* use, SgStatement* st)
    {
        if (def == NULL || !def->Belongs(this))
            use->AddToSet(this, st);
    }
    void RegisterDefinition(CFG_VarSet* def, const CFG_VarSet* use, SgStatement* st) { def->AddToSet(this, st); }
};

std::vector<CFG_VarItem> removeFromList(const std::set<int> &nums, const std::vector<CFG_VarItem> &list);
#endif