#include "../Utils/leak_detector.h"
#if NEW_CFG
#include "dvm.h"
#include "CFGraph.h"
#include "CFG_Common.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "calls.h"

using namespace std;

static const CFG_IntrinsicSubroutineData intrinsicData[] = {
    {"date_and_time", 4, { {-1, "date", INTRINSIC_OUT}, {-1, "time", INTRINSIC_OUT }, {-1, "zone", INTRINSIC_OUT }, {-1, "values", INTRINSIC_OUT } } },
    {"mod", 2, { {1, NULL, INTRINSIC_IN}, {2, NULL, INTRINSIC_IN} } },
    {"dvtime", 0, {}},
    {"abs", 1, { {1, NULL, INTRINSIC_IN} } },
    {"max", 2, { {1, NULL, INTRINSIC_IN}, {2, NULL, INTRINSIC_IN} } },
    {"min", 2, { {1, NULL, INTRINSIC_IN}, {2, NULL, INTRINSIC_IN} } },
    {"wtime", 1, { {1, NULL, INTRINSIC_IN} } },
    {"dble", 1, { {1, NULL, INTRINSIC_IN } } },
    {"dabs", 1, { {1, NULL, INTRINSIC_IN } } },
    {"dmax1", 2, { {1, NULL, INTRINSIC_IN}, {2, NULL, INTRINSIC_IN } } },
    {"dmin1", 2, { {1, NULL, INTRINSIC_IN}, {2, NULL, INTRINSIC_IN } } },
    {"dsqrt", 1, { {1, NULL, INTRINSIC_IN} } },
    {"dcos", 1, { {1, NULL, INTRINSIC_IN} } },
    {"datan2", 2, { {1, NULL, INTRINSIC_IN}, {2, NULL, INTRINSIC_IN} } },
    {"dsign", 2, { {1, NULL, INTRINSIC_IN}, {2, NULL, INTRINSIC_IN} } },
    {"dlog", 1, { {1, NULL, INTRINSIC_IN} } },
    {"dexp", 1, { {1, NULL, INTRINSIC_IN} } },
    {"omp_get_wtime", 0, {}},
    {"sqrt", 1, { {1, NULL, INTRINSIC_IN} } },
    {"int", 1, { {1, NULL, INTRINSIC_IN} } },
    {"iabs", 1, { {1, NULL, INTRINSIC_IN} } },
    {"fnpr", 4, { {1, NULL, INTRINSIC_IN},{ 2, NULL, INTRINSIC_IN },{ 3, NULL, INTRINSIC_IN },{ 4, NULL, INTRINSIC_IN } } },
    {"isnan", 1, { {1, NULL, INTRINSIC_IN } } }
};

bool CFG_CallData::IsArgIn(int i, CFG_ArrayVarEntryInfo *&p) const
{
    const int stored = SwitchFile(this->file_id);
    SgProcHedrStmt* h = isSgProcHedrStmt(header);
    CFG_VarSet* use = graph->GetUse();
    SgSymbol* par = h->parameter(i);

    const CFG_VarItem* result = use->Belongs(par);
    if (result && result->var->GetVarType() == VAR_REF_ARRAY_EXP && p)
        p = (CFG_ArrayVarEntryInfo*)result->var;

    SwitchFile(stored);
    return result;
}

bool CFG_CallData::IsArgOut(int i, CFG_ArrayVarEntryInfo *&p) const
{
    const int stored = SwitchFile(this->file_id);
    SgProcHedrStmt* h = isSgProcHedrStmt(header);
    checkNull(h, convertFileName(__FILE__).c_str(), __LINE__);

    graph->PrivateAnalyzer();
    CFG_VarSet* def = graph->GetDef();
    SgSymbol* par = h->parameter(i);

    const CFG_VarItem* result = def->Belongs(par);
    if (result && result->var->GetVarType() == VAR_REF_ARRAY_EXP && p)
        p = (CFG_ArrayVarEntryInfo*)result->var;

    SwitchFile(stored);
    return result;
}

CFG_ControlFlowGraph* GetControlFlowGraphWithCalls(bool main, SgStatement* start, CFG_Call* calls, CFG_CommonData* commons)
{
    if (start == NULL)
    {
        //is_correct = "no body for call found";
        return NULL;
    }

    CFG_ControlFlowGraph *cfgRet = NULL;

    doLoops l;
    CFG_ControlFlowItem *last_tmp = NULL;
    SgStatement *lastAnStmt_tmp = NULL;
    CFG_ControlFlowItem *funcGraph = getControlFlowList(start, start->lastNodeOfStmt(), last_tmp, lastAnStmt_tmp, &l, calls, commons);
    fillLabelJumps(funcGraph);
    setLeaders(funcGraph);

    cfgRet = new CFG_ControlFlowGraph(false, main, funcGraph, NULL);    
    return cfgRet;
}

extern int isStatementFunction(SgSymbol *s);
const CFG_CallData* CFG_Call::GetLinkToCall(SgExpression* e, SgStatement* s, CFG_CommonData* commons)
{
    SgStatement* header = NULL;
    SgSymbol* name;
    bool isFun;
    graph_node* g = NULL;
    if (e == NULL) 
    {
        //s - procedure call
        SgCallStmt* f = isSgCallStmt(s);
        SgSymbol* fdaf = f->name();
        if (ATTR_NODE(f->name()) != NULL)
            g = GRAPHNODE(f->name());
        if (g == NULL) 
        {
            //TODO:
            //is_correct = "no header for procedure";
            //failed_proc_name = f->name()->identifier();
            return (CFG_CallData*)(-1);
        }
        if (g)
            header = isSgProcHedrStmt(g->st_header);
        name = f->name();
        isFun = false;
        //intr = isIntrinsicFunctionNameACC(f->name()->identifier()) && !IsUserFunctionACC(f->name());
        //IsPureProcedureACC(f->name());
    }
    else 
    {
        //e - function call
        SgFunctionCallExp* f = isSgFunctionCallExp(e);
        if (isStatementFunction(f->funName()))
            return (CFG_CallData*)(-2);
        if (ATTR_NODE(f->funName()) != NULL)
            g = GRAPHNODE(f->funName());
        if (g == NULL) 
        {
            //TODO:
            //is_correct = "no header for function";
            //failed_proc_name = f->funName()->identifier();
            return (CFG_CallData*)(-1);
        }
        header = isSgFuncHedrStmt(g->st_header);
        name = f->funName();
        isFun = true;
    }

    const CFG_CallData* p = IsHeaderInList(header);
    if (p) 
    {
        recursion_flag = recursion_flag || p->graph != NULL;
        return p;
    }

    CFG_CallData* prev = CFG_GLOBAL_DATA::currentProcedure;
    p = AddHeader(header, isFun, name, g->file_id);
    CFG_GLOBAL_DATA::currentProcedure = (CFG_CallData*)p;
    if (!p->isIntrinsic) 
    {
        int stored = SwitchFile(g->file_id);
        CFG_ControlFlowGraph* graph = GetControlFlowGraphWithCalls(false, header, this, commons);
        //if (graph == NULL)
            //failed_proc_name = name->identifier();
        SwitchFile(stored);
        AssociateGraphWithHeader(header, graph);
        commons->MarkEndOfCommon(p);
    }
    CFG_GLOBAL_DATA::currentProcedure = prev;
    return p;
}

const CFG_IntrinsicSubroutineData* isAnIntrinsicSubroutine(const char* name)
{
    for (int i = 0; i < sizeof(intrinsicData) / sizeof(intrinsicData[0]); i++)
        if (strcmp(name, intrinsicData[i].name) == 0)
            return &(intrinsicData[i]);
    return NULL;
}

CFG_CallData* CFG_Call::AddHeader(SgStatement* st, bool isFun, SgSymbol* name, int fid)
{
    //test
    bool add_intr = isAnIntrinsicSubroutine(name->identifier()) != NULL;
    bool isUser = (name->attributes() & USER_PROCEDURE_BIT);
    bool isPure = false;
    {
        SgSymbol *shedr = NULL;
        if (ATTR_NODE(name))
            shedr = (GRAPHNODE(name)->symb);

        if (shedr)
            isPure = (shedr->attributes() & PURE_BIT);
        else
            isPure = false;
    }
    CFG_CallData l = CFG_CallData(st, (isIntrinsicFunctionNameACC(name->identifier()) || add_intr) && !isUser, isPure, isFun, name->identifier(), fid);
    calls_list.push_back(l);    
    return &calls_list.back();
}

const CFG_CallData* CFG_Call::IsHeaderInList(SgStatement* header) const
{
    if (header == NULL)
        return NULL;
    
    for (auto &p: calls_list)
        if (p.header == header)
            return &p;    
    return NULL;
}

void CFG_Call::AssociateGraphWithHeader(SgStatement* st, CFG_ControlFlowGraph *gr)
{
    for (auto &l : calls_list)
    {
        if (l.header == st) 
        {
            if (gr == l.graph && gr != NULL)
                gr->AddRef();
            l.graph = gr;
            return;
        }
    }
    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
}

static void printControlFlowList(CFG_ControlFlowItem* list, CFG_ControlFlowItem* last = NULL)
{
    printf("DEBUG PRINT START\n");
    unsigned int stmtNo = 0;
    CFG_ControlFlowItem* list_copy = list;
    while (list != NULL)
    {
        list->SetStmtNo(++stmtNo);
        if (list == last)
            break;
        list = list->GetNext();
    }

    list = list_copy;
    while (list != NULL)
    {
        list->PrintDebugInfo();
        if (list == last)
            break;
        list = list->GetNext();
    }
    printf("DEBUG PRINT END\n\n");
}

void CFG_Call::PrintControlFlows() const
{
    for (auto &l : calls_list)
    {
        if (!l.isIntrinsic && l.graph != NULL && l.header != NULL) 
        {
            CFG_ControlFlowGraph* g = l.graph;
            SgStatement* h = l.header;
            printf("CFI for %s\n\n", h->symbol()->identifier());
            if (g != NULL)
                printControlFlowList(g->getCFI());            
            else
                printf("ERROR: DOES NOT HAVE CFI\n");
        }
    }
}

const CFG_CallData* CFG_Call::GetDataForGraph(const CFG_ControlFlowGraph *s) const 
{
    for (auto &it : calls_list)
        if (it.graph == s)
            return &it;
    return NULL;
}

void CFG_CommonData::RegisterCommonBlock(SgStatement *st, CFG_CallData *cur)
{
    //TODO: multiple common blocks in one procedure with same name
    for (SgExpression *common = st->expr(0); common; common = common->rhs())
    {
        bool newBlock = false;
        SgExprListExp* vars = (SgExprListExp*)common->lhs();
        if (vars == NULL)
            continue;

        const string currCommonName = (common->symbol()) ? common->symbol()->identifier() : "spf_unnamed";

        CFG_CommonDataItem *it = GetItemForName(currCommonName, cur);        
        if (!it) 
        {
            it = new CFG_CommonDataItem();
            it->cb = st;
            it->name = currCommonName;
            it->isUsable = true;
            it->proc = cur;
            it->first = cur;
            it->onlyScalars = true;
            newBlock = true;

            for (int z = 0; z < list.size(); ++z)
            {
                CFG_CommonDataItem *i = list[z];
                if (i->name == currCommonName && i->isUsable)
                    it->first = i->first;
            }
        }
        it->commonRefs.push_back(common);

        for (int i = 0; i < vars->length(); ++i)
        {
            SgVarRefExp *e = isSgVarRefExp(vars->elem(i));
            if (e && !IS_ARRAY(e->symbol()))
            {
                CFG_CommonVarInfo c;
                c.var = new CFG_ScalarVarEntryInfo(e->symbol());
                c.isPendingLastPrivate = false;
                c.isInUse = false;
                c.parent = it;
                it->info.push_back(c);                
            }
            else if (isSgArrayRefExp(vars->elem(i))) 
                it->onlyScalars = false;            
            else 
            {
                CFG_CommonVarInfo c;
                c.var = new CFG_ArrayVarEntryInfo(vars->elem(i)->symbol(), isSgArrayRefExp(vars->elem(i)));
                c.isPendingLastPrivate = false;
                c.isInUse = false;
                c.parent = it;
                it->info.push_back(c);                
                it->onlyScalars = false;
            }
        }

        if (newBlock)
            list.push_back(it);
    }
}

void CFG_CommonData::MarkEndOfCommon(const CFG_CallData* cur)
{
    for (auto &elem : list)    
    {
        if (elem->first == cur)
            elem->isUsable = false;
    }
}

void CFG_CommonData::MarkAsUsed(const CFG_VarSet *use, const CFG_CallData* lst)
{
    for (auto &it : list)
    {
        if (it->proc == lst) 
        {
            for (auto &v : it->info)
            {
                const CFG_VarEntryInfo *r = v.var;
                if (use->Belongs(r))
                    v.isInUse = true;
            }
        }
    }
}

bool CFG_CommonData::CanHaveNonScalarVars(const CFG_CommonDataItem* item) const
{
    for (auto &it : list)
        if (it->name == item->name && it->first == item->first && !it->onlyScalars)
            return true;
    
    bool res = !item->onlyScalars;
    //printf("CommonData::CanHaveNonScalarVars: %d\n", res);
    return res;
}

CFG_CommonDataItem* CFG_CommonData::IsThisCommonUsedInProcedure(const CFG_CommonDataItem* item, const CFG_CallData *p) const
{
    for (auto &it : list)
    {
        if (it->proc == p) 
        {
            if (it->name == item->name)
                return it;
        }
    }
    return NULL;
}

CFG_CommonDataItem* CFG_CommonData::GetItemForName(const string &name, const CFG_CallData *call) const
{
    for (auto &it : list)
        if (it->name == name && it->proc == call)
            return it;
    
    return NULL;
}

vector<CFG_CommonVarInfo> CFG_CommonData::GetCommonsForVarSet(const CFG_VarSet* set, const CFG_CallData *call) const
{
    vector<CFG_CommonVarInfo> res;
    for (auto &i : list)
        if (i->proc == call) 
            for (auto &v : i->info)
                if (set->Belongs(v.var)) 
                    res.push_back(v);    
    return res;
}

CFG_CommonDataItem* CFG_CommonData::IsThisCommonVar(const CFG_VarItem &item, const CFG_CallData *call) const
{
    for (auto &it : list)
    {
        if (it->proc == call) 
        {
            for (auto &inf : it->info)
            {
                if (inf.var && item.var && *inf.var == *item.var)
                    return it;
            }
        }
    }
    return NULL;
}



void CFG_VarSet::RemoveDoubtfulCommonVars(CFG_CallData* call)
{
    set<int> toDel;
    for (int z = 0; z < list.size(); ++z)
    {
        auto it = list[z];
        CFG_CommonDataItem *d = CFG_GLOBAL_DATA::pCommons->IsThisCommonVar(it, call);
        if (d &&CFG_GLOBAL_DATA::pCommons->CanHaveNonScalarVars(d))
            toDel.insert(z);
    }

    list = removeFromList(toDel, list);
}
#endif