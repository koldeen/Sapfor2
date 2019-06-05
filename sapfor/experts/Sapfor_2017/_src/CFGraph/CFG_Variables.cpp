#define _LEAK_
#include "../Utils/leak_detector.h"
#if NEW_CFG
#include <algorithm>
#include <set>

#include "dvm.h"
#include "CFG_Variables.h"

#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"

using namespace std;

#define DEBUG_ALLOC 0

#if DEBUG_ALLOC
static vector<CFG_ArrayVarEntryInfo*> allocA;
static vector<CFG_ScalarVarEntryInfo*> allocS;
#endif

vector<CFG_VarItem*> removeFromList(const set<int> &nums, const vector<CFG_VarItem*> &list)
{
    //TODO: REMOVE
    vector<CFG_VarItem*> retVal;
    for (int z = 0; z < list.size(); ++z)
    {
        if (nums.find(z) == nums.end())
            retVal.push_back(list[z]);
        else
            delete list[z];
    }

    return retVal;
}

static bool GetExpressionAndCoefficientOfBound(SgExpression* exp, SgExpression** end, int* coef)
{
    if (exp->variant() == SUBT_OP) 
    {
        if (exp->rhs() && exp->rhs()->variant() == INT_VAL) 
        {
            *end = exp->lhs();
            *coef = -exp->rhs()->valueInteger();
            return true;
        }
    }

    if (exp->variant() == ADD_OP) 
    {
        if (exp->lhs() && exp->lhs()->variant() == INT_VAL) 
        {
            *end = exp->rhs();
            *coef = exp->lhs()->valueInteger();
            return true;
        }

        if (exp->rhs() && exp->rhs()->variant() == INT_VAL) 
        {
            *end = exp->lhs();
            *coef = exp->lhs()->valueInteger();
            return true;
        }
    }
    return false;
}

bool CFG_VarSet::Equal(CFG_VarSet* p2) const
{
    if (p2 == NULL)
        return false;

    for (auto& p : list)
    {
        if (!p2->Belongs(p->Var()) && (p->Var()->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(p->Var()))->HasActiveElements()))
            return false;
    }

    for (auto& p : p2->list)
    {
        if (!Belongs(p->Var()) && (p->Var()->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(p->Var()))->HasActiveElements()))
            return false;
    }
    return true;
}

void CFG_VarSet::AddToSet(const CFG_VarEntryInfo* var, SgStatement* source, CFG_VarEntryInfo* ov)
{
    bool added = false;
    if (var->GetVarType() != VAR_REF_ARRAY_EXP) 
    {
        const CFG_VarItem* p = Belongs(var, false);
        added = (p == NULL);
    }
    else 
    {
        CFG_ArrayVarEntryInfo* av = (CFG_ArrayVarEntryInfo*)var;
        const CFG_VarItem* p = GetArrayRef(av);
        if (p == NULL)
            added = true;
        else 
        {
            CFG_ArrayVarEntryInfo* fv = (CFG_ArrayVarEntryInfo*)p->Var();
            *fv += *av;
        }
    }

    if (added)
    {
        CFG_VarItem *p = new CFG_VarItem();
        p->AddNewVar(var->Clone());
        p->AddOVar(ov);
        p->SetFile(current_file_id);
        list.push_back(p);
    }
}

void CFG_VarSet::Remove(const CFG_VarEntryInfo* var)
{
    int z;
    for (z = 0; z < list.size(); ++z)
    {
        if (var == list[z]->Var())
            break;
    }
    
    if (z < list.size())
    {
        //TODO: REMOVE
        delete list[z];
        list.erase(list.begin() + z);
    }    
}

const CFG_VarItem* CFG_VarSet::Belongs(const CFG_VarEntryInfo* var, bool os) const
{
    for (auto& elem : list)
    {
        if ((*elem->Var() == *var))
            return elem;
        if (os && OriginalSymbol(elem->Var()->GetSymbol()) == OriginalSymbol(var->GetSymbol()))
            return elem;
    }    
    return NULL;
}

const CFG_VarItem* CFG_VarSet::Belongs(SgSymbol* s, bool os) const
{
    for (auto& elem : list)
    {
        if ((elem->Var()->GetSymbol() == s))
            if (elem->Var()->GetVarType() == VAR_REF_ARRAY_EXP)
                return ((CFG_ArrayVarEntryInfo*)(elem->Var()))->HasActiveElements() ? elem : NULL;
        
        if (os && OriginalSymbol(elem->Var()->GetSymbol()) == OriginalSymbol(s))
            return elem;
    }
    return NULL;
}

const CFG_VarItem* CFG_VarSet::GetArrayRef(const CFG_ArrayVarEntryInfo* info) const
{
    for (auto& it : list)
    {
        CFG_VarEntryInfo* v = it->Var();
        if (v->GetVarType() == VAR_REF_ARRAY_EXP) 
        {
            if (OriginalSymbol(info->GetSymbol()) == OriginalSymbol(v->GetSymbol()))
                return it;
        }
    }
    return NULL;
}

bool CFG_VarSet::RecordBelong(const CFG_VarEntryInfo* rec) const
{
    if (rec->GetVarType() != VAR_REF_RECORD_EXP)
        return false;

    const CFG_RecordVarEntryInfo* rrec = static_cast<const CFG_RecordVarEntryInfo*>(rec);
    const CFG_VarEntryInfo* lm = rrec->GetLeftmostParent();

    for (auto &p : list)
    {
        if (*lm == *(p->Var()->GetLeftmostParent()))
            return true;
    }
    return false;
}

void CFG_VarSet::Print() const
{
    for (auto &l : list)
    {
        if (l->Var()->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(l->Var()))->HasActiveElements())
            printf("%s ", l->Var()->GetSymbol()->identifier());
    }
    putchar('\n');
}

void CFG_VarSet::LeaveOnlyRecords()
{    
    set<int> toDel;
    for (int z = 0; z < list.size(); ++z)
    {
        CFG_VarItem *p = list[z];
        if (p->Var()->GetVarType() == VAR_REF_RECORD_EXP)
        {
            const CFG_VarEntryInfo* rrec = p->Var()->GetLeftmostParent();
            CFG_VarEntryInfo* old = p->Var();
            if (old->RemoveReference())
            {
                p->AddNewVar(NULL);
                delete old;
            }

            if (!Belongs(rrec))
                p->AddVar((CFG_VarEntryInfo*)rrec);
            else
                toDel.insert(z);
        }
    }
    list = removeFromList(toDel, list);
}

void CFG_VarSet::Unite(const CFG_VarSet* set, bool la)
{    
    for(auto &arg2 : set->list)
    {
        const CFG_VarItem* n = Belongs(arg2->Var());
        if (n == NULL)
        {
            CFG_VarItem *n = new CFG_VarItem();
            if (arg2->Var()->GetVarType() == VAR_REF_ARRAY_EXP)
                n->AddNewVar(arg2->Var()->Clone());
            else 
                n->AddVar(arg2->Var());

            n->AddOVar(arg2->Ov());
            n->SetFile(arg2->GetFile());

            list.push_back(n);
        }
        else 
        {
            if (n->Var()->GetVarType() == VAR_REF_ARRAY_EXP) 
                *(CFG_ArrayVarEntryInfo*)(n->Var()) += *(CFG_ArrayVarEntryInfo*)(arg2->Var());
        }
    }
}

void CFG_VarSet::Intersect(const CFG_VarSet* set, bool la, bool array_mode = false)
{
    std::set<int> toDel;
    for (int z = 0; z < list.size(); ++z)
    {
        CFG_VarItem *p = list[z];
        const CFG_VarItem* n = set->Belongs(p->Var());
        if (n == NULL)
        {
            if (!array_mode) 
                toDel.insert(z);
        }
        else 
        {
            if (p->Var()->GetVarType() == VAR_REF_ARRAY_EXP)
            {
                if (!array_mode)
                    *(CFG_ArrayVarEntryInfo*)(p->Var()) *= *(CFG_ArrayVarEntryInfo*)(n->Var());
                else
                    *(CFG_ArrayVarEntryInfo*)(p->Var()) += *(CFG_ArrayVarEntryInfo*)(n->Var());
            }
        }
    }

    list = removeFromList(toDel, list);
}

//allocate
CFG_ArrayVarEntryInfo* operator-(const CFG_ArrayVarEntryInfo& a, const CFG_ArrayVarEntryInfo& b)
{
    CFG_ArrayVarEntryInfo* nv = (CFG_ArrayVarEntryInfo*)a.Clone();
    *nv -= b;
    return nv;
}

//allocate
CFG_ArrayVarEntryInfo* operator+(const CFG_ArrayVarEntryInfo& a, const CFG_ArrayVarEntryInfo& b)
{
    CFG_ArrayVarEntryInfo* nv = (CFG_ArrayVarEntryInfo*)a.Clone();
    *nv += b;
    return nv;
}

void CFG_ArrayVarEntryInfo::RegisterDefinition(CFG_VarSet* def, const CFG_VarSet* use, SgStatement* st)
{
    def->AddToSet(this, st);
    use->PossiblyAffectArrayEntry(this);
}

void CFG_VarSet::PossiblyAffectArrayEntry(const CFG_ArrayVarEntryInfo* var) const
{
    const CFG_VarItem* it = GetArrayRef(var);
    if (it)
        ((CFG_ArrayVarEntryInfo*)(it->Var()))->ProcessChangesToUsedEntry(var);
}

void CFG_ArrayVarEntryInfo::ProcessChangesToUsedEntry(const CFG_ArrayVarEntryInfo* var)
{
    if (disabled || var->disabled || subscripts != var->subscripts)
        return;

    for (int i = 0; i < subscripts; i++)
    {
        if (!data[i].defined)
            continue;

        if (data[i].loop == var->data[i].loop && data[i].loop != NULL)
        {
            if (data[i].coefs[0] == var->data[i].coefs[0])
            {
                if (data[i].coefs[1] < var->data[i].coefs[1])
                {
                    if (data[i].left_bound && data[i].left_bound->variant() == INT_VAL)
                    {
                        data[i].bound_modifiers[0] = data[i].left_bound->valueInteger() + data[i].bound_modifiers[0];
                        data[i].bound_modifiers[1] = data[i].left_bound->valueInteger() + var->data[i].coefs[1] - 1;
                        data[i].left_bound = data[i].right_bound = NULL;
                    }
                    else
                    {
                        //maybe add something, not sure
                    }
                }
            }
        }
    }
}

CFG_ArrayVarEntryInfo& CFG_ArrayVarEntryInfo::operator*=(const CFG_ArrayVarEntryInfo& b)
{
    if (subscripts == 0)
    {
        if (b.HasActiveElements())
            disabled = true;
        return *this;
    }

    if (b.subscripts == 0)
    {
        if (HasActiveElements())
            MakeInactive();
        return *this;
    }

    if (subscripts != b.subscripts || subscripts == 0 || b.subscripts == 0 || !data.size() || !b.data.size() || !(data[0].defined) || !(b.data[0].defined))
        return *this;

    for (int i = 0; i < subscripts; i++)
    {
        if (b.disabled)
            data[i].left_bound = data[i].right_bound = NULL;

        if (data[i].left_bound == b.data[i].left_bound)
            data[i].bound_modifiers[0] = std::max(data[i].bound_modifiers[0], b.data[i].bound_modifiers[0]);

        if (data[i].right_bound == b.data[i].right_bound)
            data[i].bound_modifiers[1] = std::min(data[i].bound_modifiers[1], b.data[i].bound_modifiers[1]);
    }
    return *this;
}

CFG_ArrayVarEntryInfo& CFG_ArrayVarEntryInfo::operator+=(const CFG_ArrayVarEntryInfo& b)
{
    if (subscripts == 0)
    {
        if (b.HasActiveElements())
            disabled = true;
        return *this;
    }

    if (b.subscripts == 0)
    {
        if (HasActiveElements())
            MakeInactive();
        return *this;
    }

    if (disabled && !b.disabled && b.data.size())
    {
        for (int i = 0; i < subscripts; i++)
            data[i] = b.data[i];
        disabled = false;
        return *this;
    }

    if (subscripts != b.subscripts || subscripts == 0 || b.subscripts == 0 || !data.size() || !b.data.size() || disabled || b.disabled)
        return *this;

    for (int i = 0; i < subscripts; i++)
    {

        if (data[i].left_bound == b.data[i].left_bound)
            data[i].bound_modifiers[0] = std::min(data[i].bound_modifiers[0], b.data[i].bound_modifiers[0]);

        if (data[i].right_bound == b.data[i].right_bound)
            data[i].bound_modifiers[1] = std::max(data[i].bound_modifiers[1], b.data[i].bound_modifiers[1]);

        if (data[i].left_bound == NULL && data[i].right_bound == NULL && (b.data[i].left_bound != NULL || b.data[i].right_bound != NULL))
        {
            const CFG_ArraySubscriptData& tmp = data[i];
            data[i] = b.data[i];
            if (data[i].left_bound && data[i].left_bound->variant() == INT_VAL)
            {
                if (tmp.bound_modifiers[1] == data[i].left_bound->valueInteger() + data[i].bound_modifiers[0] - 1)
                    data[i].bound_modifiers[0] -= (1 + tmp.bound_modifiers[1] - tmp.bound_modifiers[0]);

            }

            if (data[i].right_bound && data[i].right_bound->variant() == INT_VAL)
            {
                if (tmp.bound_modifiers[0] == data[i].left_bound->valueInteger() + data[i].bound_modifiers[1] + 1)
                    data[i].bound_modifiers[1] += (1 + tmp.bound_modifiers[1] - tmp.bound_modifiers[0]);
            }
        }
    }
    return *this;
}

CFG_ArrayVarEntryInfo& CFG_ArrayVarEntryInfo::operator-=(const CFG_ArrayVarEntryInfo& b)
{
    if (subscripts == 0)
    {
        if (b.HasActiveElements())
            disabled = true;
        return *this;
    }

    if (b.subscripts == 0)
    {
        if (HasActiveElements())
            MakeInactive();
        return *this;
    }

    if (subscripts != b.subscripts || !data.size() || !b.data.size() || !(data[0].defined) || !(b.data[0].defined))
        return *this;

    for (int i = 0; i < subscripts; i++)
    {
        if (b.data[i].left_bound == NULL)
        {
            if (data[i].left_bound && data[i].left_bound->variant() == INT_VAL)
            {
                if (data[i].left_bound->valueInteger() + data[i].bound_modifiers[0] == b.data[i].bound_modifiers[0])
                {
                    data[i].bound_modifiers[0]++;
                    continue;
                }
            }
        }

        if (data[i].left_bound == NULL && b.data[i].left_bound == NULL &&
            data[i].right_bound == NULL && b.data[i].right_bound == NULL)
        {
            if (data[i].bound_modifiers[0] < b.data[i].bound_modifiers[0])
            {
                data[i].bound_modifiers[1] = b.data[i].bound_modifiers[0] - 1;
                continue;
            }

            if (data[i].bound_modifiers[1] > b.data[i].bound_modifiers[1])
            {
                data[i].bound_modifiers[0] = b.data[i].bound_modifiers[1] + 1;
                continue;
            }
            data[i].defined = false;
        }

        if (data[i].left_bound == b.data[i].left_bound && data[i].bound_modifiers[0] < b.data[i].bound_modifiers[0])
        {
            data[i].bound_modifiers[0] = data[i].bound_modifiers[0];
            data[i].bound_modifiers[1] = b.data[i].bound_modifiers[0] - 1;
            data[i].right_bound = data[i].left_bound;
        }

        if (data[i].right_bound == b.data[i].right_bound && data[i].bound_modifiers[1] > b.data[i].bound_modifiers[1])
        {
            data[i].bound_modifiers[0] = b.data[i].bound_modifiers[1] + 1;
            data[i].bound_modifiers[1] = data[i].bound_modifiers[1];
            data[i].left_bound = data[i].right_bound;
        }

        if (b.data[i].left_bound == NULL && b.data[i].right_bound == NULL &&
            (data[i].left_bound != NULL || data[i].right_bound != NULL))
            continue;
        else
        {
            data[i].bound_modifiers[0] = data[i].bound_modifiers[1] = 0;
            data[i].left_bound = NULL;
            data[i].right_bound = NULL;
            data[i].defined = false;
            //empty set
        }
    }
    return *this;
}

void CFG_VarSet::Minus(const CFG_VarSet* set, bool complete)
{
    std::set<int> toDel;
    for (int z = 0; z < list.size(); ++z)
    {
        CFG_VarItem *p = list[z];

        const CFG_VarItem *d = set->Belongs(p->Var());
        if (d && (p->Var()->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(d->Var()))->HasActiveElements()))
        {
            if (p->Var()->GetVarType() == VAR_REF_ARRAY_EXP && !complete)
                *(CFG_ArrayVarEntryInfo*)(p->Var()) -= *(CFG_ArrayVarEntryInfo*)(d->Var());
            else
                toDel.insert(z);            
        }
    }
    list = removeFromList(toDel, list);    
}

void CFG_VarSet::MinusFinalize(const CFG_VarSet* set, bool complete)
{
    Minus(set, complete);

    std::set<int> toDel;
    for (int z = 0; z < list.size(); ++z)
    {
        auto p = list[z];
        if (set->RecordBelong(p->Var()))
            toDel.insert(z);
    }
    list = removeFromList(toDel, list);
}

void CFG_ArrayVarEntryInfo::RegisterUsage(const CFG_VarSet* def, CFG_VarSet* use, SgStatement* st)
{
    const CFG_VarItem* it = def->GetArrayRef(this);
    CFG_ArrayVarEntryInfo* add = this;

    if (it != NULL)
        add = *this - *(CFG_ArrayVarEntryInfo*)(it->Var());

    if (use != NULL && add != NULL && add->HasActiveElements())
        use->AddToSet(add, st);

    if (add != this)
        delete add;
}

bool CFG_ArrayVarEntryInfo::HasActiveElements() const
{
    bool result = false;
    if (disabled)
        return false;
    if (subscripts == 0)
        return true;
    for (int i = 0; i < subscripts; i++)
    {
        if (!data[i].defined)
            return false;
        if (data[i].left_bound != data[i].right_bound)
            result = true;
        if (data[i].left_bound == data[i].right_bound && data[i].bound_modifiers[0] <= data[i].bound_modifiers[1])
            result = true;
    }
    return result;
}

void CFG_ArrayVarEntryInfo::MakeInactive()
{
    disabled = true;
    for (int i = 0; i < subscripts; i++)
    {
        data[i].left_bound = data[i].right_bound = NULL;
        data[i].bound_modifiers[0] = data[i].bound_modifiers[1] = 0;
    }
}

CFG_ArrayVarEntryInfo::CFG_ArrayVarEntryInfo(SgSymbol* s, SgArrayRefExp* r) : CFG_VarEntryInfo(s)
{
#if DEBUG_ALLOC
    allocA.push_back(this);
#endif
    // TODO: need to check all alhorithm!!
    disabled = true;

    if (!r)
        subscripts = 0;
    else
        subscripts = r->numberOfSubscripts();
    if (subscripts)
        data.resize(subscripts);

    for (int i = 0; i < subscripts; i++)
    {
        data[i].defined = false;
        data[i].bound_modifiers[0] = data[i].bound_modifiers[1] = 0;
        data[i].step = 1;
        data[i].left_bound = data[i].right_bound = NULL;
        data[i].coefs[0] = data[i].coefs[1] = 0;
        data[i].loop = NULL;
#ifdef __SPF
        const vector<int*> coefs = getAttributes<SgExpression*, int*>(r->subscript(i), set<int>{ INT_VAL });
        const vector<SgStatement*> fs = getAttributes<SgExpression*, SgStatement*>(r->subscript(i), set<int>{ FOR_NODE });
        if (fs.size() == 1)
        {
            if (data[i].loop != NULL)
            {
                if (coefs.size() == 1)
                {
                    data[i].defined = true;
                    data[i].bound_modifiers[0] = data[i].bound_modifiers[1] = coefs[0][1];
                    data[i].coefs[0] = coefs[0][0];
                    data[i].coefs[1] = coefs[0][1];
                    data[i].step = coefs[0][0];
                    int tmp;

                    SgExpression* et;
                    if (GetExpressionAndCoefficientOfBound(data[i].loop->l, &et, &tmp))
                    {
                        data[i].left_bound = et;
                        data[i].bound_modifiers[0] += tmp;
                    }
                    else
                        data[i].left_bound = data[i].loop->l;

                    if (GetExpressionAndCoefficientOfBound(data[i].loop->r, &et, &tmp))
                    {
                        data[i].right_bound = et;
                        data[i].bound_modifiers[1] += tmp;
                    }
                    else
                        data[i].right_bound = data[i].loop->r;
                }
            }
        }
#endif
        if (!data[i].defined)
        {
            SgExpression* ex = r->subscript(i);
            if (ex->variant() == INT_VAL)
            {
                data[i].bound_modifiers[0] = ex->valueInteger();
                data[i].bound_modifiers[1] = ex->valueInteger();
                data[i].defined = true;
            }
            else
            {
                data[i].bound_modifiers[0] = 0;
                data[i].bound_modifiers[1] = 0;
                data[i].left_bound = data[i].right_bound = ex;
                data[i].defined = true;
            }
        }
    }
}

CFG_ArrayVarEntryInfo::CFG_ArrayVarEntryInfo(SgSymbol* s, int sub, int ds, const vector<CFG_ArraySubscriptData>& d) : CFG_VarEntryInfo(s), subscripts(sub), disabled(ds)
{
#if DEBUG_ALLOC
    allocA.push_back(this);
#endif
    if (sub > 0)
        data = d;
}

CFG_VarSet::~CFG_VarSet()
{
    for (auto &elem : list)
        delete elem;
    list.clear();
}

void CFG_VarEntryInfo::AddReference()
{
    references++;
    //printf("add ref: %d for %lld %s\n", references, (void*)symbol, symbol->identifier());
    //fflush(NULL);
}
bool CFG_VarEntryInfo::RemoveReference()
{
    --references;
    //printf("rem ref: %d for %lld %s\n", references, (void*)symbol, symbol->identifier());
    //fflush(NULL);
    return (references == 0);
}

CFG_ScalarVarEntryInfo::~CFG_ScalarVarEntryInfo()
{
#if DEBUG_ALLOC
    auto it = std::find(allocS.begin(), allocS.end(), this);
    if (it == allocS.end())
        printf("");
    allocS.erase(it);
#endif
}

CFG_ArrayVarEntryInfo::~CFG_ArrayVarEntryInfo()
{
#if DEBUG_ALLOC
    auto it = std::find(allocA.begin(), allocA.end(), this);
    if (it == allocA.end())
        printf("");
    allocA.erase(it);
#endif
}

CFG_ScalarVarEntryInfo::CFG_ScalarVarEntryInfo(SgSymbol* s) : CFG_VarEntryInfo(s) 
{
#if DEBUG_ALLOC
    allocS.push_back(this);
#endif
}
#endif