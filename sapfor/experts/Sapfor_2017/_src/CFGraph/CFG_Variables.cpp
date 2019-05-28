#include "../Utils/leak_detector.h"
#if NEW_CFG
#include <algorithm>
#include <set>

#include "dvm.h"
#include "CFG_Variables.h"

#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"

using namespace std;

vector<CFG_VarItem> removeFromList(const set<int> &nums, const vector<CFG_VarItem> &list)
{
    //TODO: REMOVE
    vector<CFG_VarItem> retVal;
    for (int z = 0; z < list.size(); ++z)
    {
        if (nums.find(z) == nums.end())
            retVal.push_back(list[z]);
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
        if (!p2->Belongs(p.var) && (p.var->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(p.var))->HasActiveElements()))
            return false;
    }

    for (auto& p : p2->list)
    {
        if (!Belongs(p.var) && (p.var->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(p.var))->HasActiveElements()))
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
            CFG_ArrayVarEntryInfo* fv = (CFG_ArrayVarEntryInfo*)p->var;
            *fv += *av;
        }
    }

    if (added)
    {
        CFG_VarItem p;
        p.var = var->Clone();
        p.ov = ov;        
        p.file_id = current_file_id;
        list.push_back(p);
    }
}

void CFG_VarSet::Remove(const CFG_VarEntryInfo* var)
{
    int z;
    for (z = 0; z < list.size(); ++z)
    {
        if (var == list[z].var)
            break;
    }
    
    if (z < list.size())
    {
        //TODO: REMOVE
        list.erase(list.begin() + z);
    }    
}

const CFG_VarItem* CFG_VarSet::Belongs(const CFG_VarEntryInfo* var, bool os) const
{
    for (auto& elem : list)
    {
        if ((*elem.var == *var))
            return &elem;
        if (os && OriginalSymbol(elem.var->GetSymbol()) == OriginalSymbol(var->GetSymbol()))
            return &elem;
    }    
    return NULL;
}

const CFG_VarItem* CFG_VarSet::Belongs(SgSymbol* s, bool os) const
{
    for (auto& elem : list)
    {
        if ((elem.var->GetSymbol() == s))
            if (elem.var->GetVarType() == VAR_REF_ARRAY_EXP)
                return ((CFG_ArrayVarEntryInfo*)(elem.var))->HasActiveElements() ? &elem : NULL;
        
        if (os && OriginalSymbol(elem.var->GetSymbol()) == OriginalSymbol(s))
            return &elem;
    }
    return NULL;
}

const CFG_VarItem* CFG_VarSet::GetArrayRef(const CFG_ArrayVarEntryInfo* info) const
{
    for (auto& it : list)
    {
        CFG_VarEntryInfo* v = it.var;
        if (v->GetVarType() == VAR_REF_ARRAY_EXP) 
        {
            if (OriginalSymbol(info->GetSymbol()) == OriginalSymbol(v->GetSymbol()))
                return &it;
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
        if (*lm == *(p.var->GetLeftmostParent()))
            return true;
    }
    return false;
}

void CFG_VarSet::Print() const
{
    for (auto &l : list)
    {
        if (l.var->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(l.var))->HasActiveElements())
            printf("%s ", l.var->GetSymbol()->identifier());
    }
    putchar('\n');
}

void CFG_VarSet::LeaveOnlyRecords()
{    
    set<int> toDel;
    for (int z = 0; z < list.size(); ++z)
    {
        auto p = list[z];
        if (p.var->GetVarType() == VAR_REF_RECORD_EXP) 
        {
            const CFG_VarEntryInfo* rrec = p.var->GetLeftmostParent();
            CFG_VarEntryInfo* old = p.var;
            if (old->RemoveReference())
                delete old;

            if (!Belongs(rrec))
                p.var = (CFG_VarEntryInfo*)rrec;
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
        const CFG_VarItem* n = Belongs(arg2.var);
        if (n == NULL)
        {
            CFG_VarItem n;
            if (arg2.var->GetVarType() == VAR_REF_ARRAY_EXP)
                n.var = arg2.var->Clone();
            else 
            {
                n.var = arg2.var;
                n.var->AddReference();
            }
            n.ov = arg2.ov;
            n.file_id = arg2.file_id;

            list.push_back(n);
        }
        else 
        {
            if (n->var->GetVarType() == VAR_REF_ARRAY_EXP) 
                *(CFG_ArrayVarEntryInfo*)(n->var) += *(CFG_ArrayVarEntryInfo*)(arg2.var);
        }
    }
}

void CFG_VarSet::Intersect(const CFG_VarSet* set, bool la, bool array_mode = false)
{
    std::set<int> toDel;
    for (int z = 0; z < list.size(); ++z)
    {
        auto p = list[z];
        const CFG_VarItem* n = set->Belongs(p.var);
        if (n == NULL)
        {
            if (!array_mode) 
                toDel.insert(z);
        }
        else 
        {
            if (p.var->GetVarType() == VAR_REF_ARRAY_EXP) 
            {
                if (!array_mode)
                    *(CFG_ArrayVarEntryInfo*)(p.var) *= *(CFG_ArrayVarEntryInfo*)(n->var);
                else
                    *(CFG_ArrayVarEntryInfo*)(p.var) += *(CFG_ArrayVarEntryInfo*)(n->var);
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
        ((CFG_ArrayVarEntryInfo*)(it->var))->ProcessChangesToUsedEntry(var);
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
        auto p = list[z];

        const CFG_VarItem *d = set->Belongs(p.var);
        if (d && (p.var->GetVarType() != VAR_REF_ARRAY_EXP || ((CFG_ArrayVarEntryInfo*)(d->var))->HasActiveElements()))
        {
            if (p.var->GetVarType() == VAR_REF_ARRAY_EXP && !complete) 
                *(CFG_ArrayVarEntryInfo*)(p.var) -= *(CFG_ArrayVarEntryInfo*)(d->var);
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
        if (set->RecordBelong(p.var))
            toDel.insert(z);
    }
    list = removeFromList(toDel, list);
}

void CFG_ArrayVarEntryInfo::RegisterUsage(const CFG_VarSet* def, CFG_VarSet* use, SgStatement* st)
{
    const CFG_VarItem* it = def->GetArrayRef(this);
    CFG_ArrayVarEntryInfo* add = this;

    if (it != NULL)
        add = *this - *(CFG_ArrayVarEntryInfo*)(it->var);

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
    if (sub > 0)
        data = d;
}
#endif