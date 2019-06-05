#define _LEAK_
#include "../Utils/leak_detector.h"
#if NEW_CFG
#include "dvm.h"
#include "CFGraph.h"
#include "CFG_Common.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"
#include "calls.h"

using namespace std;

CFG_PrivateDelayedItem *G_privateDelayedList;
const CFG_CallData* G_currentProcedure = NULL;
const CFG_CallData* G_mainProcedure = NULL;
CFG_DoLoopDataList* G_doLoopList = NULL;
CFG_CommonData* G_pCommons = NULL;
CFG_Call* G_pCalls = NULL;
const char* G_is_correct = NULL;
const char* G_failed_proc_name = NULL;

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
    if (result && result->Var()->GetVarType() == VAR_REF_ARRAY_EXP && p)
        p = (CFG_ArrayVarEntryInfo*)result->Var();

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
    if (result && result->Var()->GetVarType() == VAR_REF_ARRAY_EXP && p)
        p = (CFG_ArrayVarEntryInfo*)result->Var();

    SwitchFile(stored);
    return result;
}

struct LabelCFI
{
    int l;
    CFG_ControlFlowItem* item;
};

static void fillLabelJumps(CFG_ControlFlowItem* cfList)
{
    if (cfList != NULL) 
    {
        CFG_ControlFlowItem* temp = cfList;
        CFG_ControlFlowItem* temp2;
        unsigned int label_no = 0;
        while (temp != NULL)
        {
            if (temp->GetLabel() != NULL)
                label_no++;
            temp = temp->GetNext();
        }

        LabelCFI* table = new LabelCFI[label_no + 1];
        unsigned int li = 0;
        for (temp = cfList; temp != NULL; temp = temp->GetNext()) 
        {
            SgLabel* label;
            if ((label = temp->GetLabel()) != NULL) 
            {
                table[li].item = temp;
                table[li++].l = label->id();
            }
            temp2 = temp;
        }

        temp = new CFG_ControlFlowItem(G_currentProcedure);
        temp2->AddNextItem(temp);
        table[label_no].item = temp2;
        table[label_no].l = -1;
        for (temp = cfList; temp != NULL; temp = temp->GetNext()) 
        {
            SgLabel* jump = temp->GetLabelJump();
            int l;
            if (jump != NULL) {
                l = jump->id();
                for (unsigned int i = 0; i < label_no + 1; i++) 
                {
                    if (table[i].l == l || i == label_no) {
                        temp->InitJump(table[i].item);
                        break;
                    }
                }
            }
        }
        delete[] table;
    }
}

static void setLeaders(CFG_ControlFlowItem* cfList)
{
    if (cfList != NULL)
        cfList->SetLeader();
    while (cfList != NULL)
    {
        if (cfList->GetJump() != NULL)
        {
            cfList->GetJump()->SetLeader();
            if (cfList->GetNext() != NULL)
                cfList->GetNext()->SetLeader();
        }

        if (cfList->GetCall() != NULL)
        {
            if (cfList->GetNext() != NULL)
                cfList->GetNext()->SetLeader();
        }
        cfList = cfList->GetNext();
    }
}

CFG_ControlFlowGraph* GetControlFlowGraphWithCalls(bool main, SgStatement* start, CFG_Call* calls, CFG_CommonData* commons)
{
    if (start == NULL)
    {
        //is_correct = "no body for call found";
        return NULL;
    }

    CFG_ControlFlowGraph *cfgRet = NULL;

    CFG_DoLoops l;
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

    const CFG_CallData* prev = G_currentProcedure;
    p = AddHeader(header, isFun, name, g->file_id);    
    if (!p->isIntrinsic) 
    {
        G_currentProcedure = p;
        int stored = SwitchFile(g->file_id);
        CFG_ControlFlowGraph* graph = GetControlFlowGraphWithCalls(false, header, this, commons);
        //if (graph == NULL)
            //failed_proc_name = name->identifier();
        SwitchFile(stored);
        AssociateGraphWithHeader(header, graph);
        commons->MarkEndOfCommon(p);
        G_currentProcedure = prev;
    }
    
    return p;
}

const CFG_IntrinsicSubroutineData* isAnIntrinsicSubroutine(const char* name)
{
    for (int i = 0; i < sizeof(intrinsicData) / sizeof(intrinsicData[0]); i++)
        if (strcmp(name, intrinsicData[i].name) == 0)
            return &(intrinsicData[i]);
    return NULL;
}

const CFG_CallData* CFG_Call::AddHeader(SgStatement* st, bool isFun, SgSymbol* name, int fid)
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
    CFG_CallData *l = new CFG_CallData(st, (isIntrinsicFunctionNameACC(name->identifier()) || add_intr) && !isUser, isPure, isFun, name->identifier(), fid);
    calls_list.push_back(l);    
    return calls_list.back();
}

const CFG_CallData* CFG_Call::IsHeaderInList(SgStatement* header) const
{
    if (header == NULL)
        return NULL;
    
    for (auto &p: calls_list)
        if (p->header == header)
            return p;    
    return NULL;
}

void CFG_Call::AssociateGraphWithHeader(SgStatement* st, CFG_ControlFlowGraph *gr)
{
    for (auto &l : calls_list)
    {
        if (l->header == st) 
        {
            if (gr == l->graph && gr != NULL)
                gr->AddRef();
            l->graph = gr;
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
        if (!l->isIntrinsic && l->graph != NULL && l->header != NULL) 
        {
            CFG_ControlFlowGraph* g = l->graph;
            SgStatement* h = l->header;
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
        if (it->graph == s)
            return it;
    return NULL;
}

void CFG_CommonData::RegisterCommonBlock(SgStatement *st, const CFG_CallData *cur)
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

CFG_CommonDataItem* CFG_CommonData::IsThisCommonVar(const CFG_VarItem *item, const CFG_CallData *call) const
{
    for (auto &it : list)
    {
        if (it->proc == call) 
        {
            for (auto &inf : it->info)
            {
                if (inf.var && item->Var() && *inf.var == *item->Var())
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
        CFG_CommonDataItem *d = G_pCommons->IsThisCommonVar(it, call);
        if (d &&G_pCommons->CanHaveNonScalarVars(d))
            toDel.insert(z);
    }

    list = removeFromList(toDel, list);
}

CFG_ControlFlowItem* CFG_ControlFlowGraph::getCFI() { return first->GetStart(); }

CFG_Call::~CFG_Call()
{
    for (auto &l : calls_list)
    {
        if (!l->isIntrinsic && l->graph)
        {
            if (l->graph->RemoveRef() && !l->graph->IsMain())
            {
                delete l->graph;
                l->graph = NULL;
            }
        }
        delete l;
    }
    calls_list.clear();
}

void CFG_ControlFlowGraph::addCFItoCollection(std::set<CFG_ControlFlowItem*> &collection) const
{
    for (CFG_BasicBlock *bb = first; bb != NULL; bb = bb->GetLexNext())
        bb->AddUniqObjects(collection);
}

CFG_ControlFlowItem* CFG_DoLoops::EndLoop(CFG_ControlFlowItem* last)
{
    CFG_DoLoopItem* removed = current;
    if (first == current)
        first = current = NULL;
    else
    {
        CFG_DoLoopItem* prev = first;
        while (prev->GetNext() != current)
            prev = prev->GetNext();
        prev->SetNext(NULL);
        current = prev;
    }
    last->AddNextItem(removed->GetSourceForCycle());
    CFG_ControlFlowItem* empty = removed->GetSourceForExit();

    delete removed;
    return empty;
}

CFG_PrivateDelayedItem::~CFG_PrivateDelayedItem()
{
    if (delay) delete delay;
    if (detected) delete detected;
    if (original) delete original;
    if (lp) delete lp;

    if (next) delete next;
}

CFG_ControlFlowGraph::CFG_ControlFlowGraph(bool t, bool m, CFG_ControlFlowItem* list, CFG_ControlFlowItem* end) :
    temp(t), main(m), refs(1), def(NULL), use(NULL), pri(NULL), hasBeenAnalyzed(false)
    //TODO
/*#ifdef __SPF
, pointers(set<SymbolKey>())
#endif*/
{
    int n = 0;
    CFG_ControlFlowItem* orig = list;
    CFG_BasicBlock* prev = NULL;
    CFG_BasicBlock* start = NULL;
    int stmtNo = 0;
    bool ns = list->IsEnumerated();
    if (list != NULL && !ns) 
    {
        while (list != NULL && list != end)
        {
            list->SetStmtNo(++stmtNo);
            list = list->GetNext();
        }
    }

    CFG_ControlFlowItem* last_prev = NULL;
    list = orig;
    while (list != NULL && list != end)
    {
        CFG_BasicBlock* bb = new CFG_BasicBlock(t, list, ++n, this, list->GetProc());
        last = bb;
        bb->SetPrev(prev);
        if (prev != NULL) 
        {
            prev->SetNext(bb);
            if (!last_prev->IsUnconditionalJump()) 
            {
                bb->AddToPrev(prev, last_prev->IsForJumpFlagSet(), false, last_prev);
                prev->AddToSucc(bb, last_prev->IsForJumpFlagSet(), false, last_prev);
            }
        }

        if (start == NULL)
            start = bb;
        prev = bb;
        while (list->GetNext() != NULL && list->GetNext() != end && !list->GetNext()->IsLeader()) 
        {
            list->SetBBno(n);
            list = list->GetNext();
        }

        list->SetBBno(n);
        last_prev = list;
        list = list->GetNext();
    }
    list = orig;
    while (list != NULL && list != end)
    {
        CFG_ControlFlowItem* target;
        if ((target = list->GetJump()) != NULL)
        {
            CFG_BasicBlock* tmp1 = start;
            CFG_BasicBlock* tmp2 = start;
            for (int i = 1; i < target->GetBBno() || i < list->GetBBno(); i++)
            {
                if (i < list->GetBBno()) 
                {
                    tmp2 = tmp2->GetLexNext();
                    if (!tmp2)
                        break;
                }

                if (i < target->GetBBno()) 
                {
                    tmp1 = tmp1->GetLexNext();
                    if (!tmp1)
                        break;
                }
            }
            if (tmp1 && tmp2) 
            {
                tmp1->AddToPrev(tmp2, list->IsForJumpFlagSet(), true, list);
                tmp2->AddToSucc(tmp1, list->IsForJumpFlagSet(), true, list);
            }            
        }
        list = list->GetNext();
    }

    start->MarkAsReached();
    first = start;
    common_use.clear();
    cuf = false;
    common_def.clear();
    cdf = false;
}

CFG_ControlFlowGraph::~CFG_ControlFlowGraph()
{
    common_def.clear();
    common_use.clear();
    
    if (def)
        delete def;

    if (use)
        delete use;

    if (!temp && pri)
        delete pri;

    for (CFG_BasicBlock *bb = first; bb != NULL; )
    {
        CFG_BasicBlock *tmp = bb;
        bb = bb->GetLexNext();
        delete tmp;
    }
}


CFG_VarSet* CFG_ControlFlowGraph::GetUse()
{
    if (use == NULL)
    {
        CFG_BasicBlock* p = first;
        CFG_VarSet* res = new CFG_VarSet();
        while (p != NULL)
        {
            CFG_VarSet* tmp = new CFG_VarSet();
            tmp->Unite(p->GetUse(), false);
            tmp->Minus(p->GetMrdIn(false));
            
            res->Unite(tmp, false);
            delete tmp;
            p = p->GetLexNext();
        }
        use = res;

    }
    if (!cuf)
    {
        const CFG_CallData* call = first->GetStart()->GetProc();
        cuf = true;
        if (call) 
        {
            common_use = G_pCommons->GetCommonsForVarSet(use, call);            
            for (CFG_BasicBlock* i = first; i != NULL; i = i->GetLexNext())
                for (auto &c : i->GetCommonUse())
                    common_use.push_back(c);
        }
    }
    return use;
}

CFG_VarSet* CFG_ControlFlowGraph::GetDef()
{
    if (def == NULL) 
    {
        def = new CFG_VarSet();
        def->Unite(last->GetMrdOut(false), true);
    }

    if (!cdf)
    {
        const CFG_CallData* call = first->GetStart()->GetProc();
        if (call) 
        {
            cdf = true;
            common_def = G_pCommons->GetCommonsForVarSet(def, call);            

            for (CFG_BasicBlock* i = first; i != NULL; i = i->GetLexNext()) 
                for (auto &c : i->GetCommonDef())                
                    common_def.push_back(c);
        }
    }
    return def;
}

CFG_VarSet* CFG_ControlFlowGraph::GetPrivate()
{
    //printControlFlowList(first->getStart(), last->getStart());
    if (pri == NULL)
    {
        bool same = false;
        int it = 0;
        CFG_BasicBlock* p = first;
        /*
        printf("GRAPH:\n");
        while (p != NULL){
            printf("block %d: ", p->getNum());
            p->print();
            p = p->getLexNext();
        }
        */
        p = first;
        while (!same) 
        {
            p = first;
            same = true;
            while (p != NULL) 
            {
                same = p->StepMrdIn(false) && same;
                same = p->StepMrdOut(false) && same;
                p = p->GetLexNext();
            }
            it++;
            //printf("iters: %d\n", it);
        }

        p = first;
        while (p != NULL) 
        {
            p->StepMrdIn(true);
            p->StepMrdOut(true);
            //p->getMrdIn(false)->print();
            p = p->GetLexNext();
        }

        p = first;
        CFG_VarSet* res = new CFG_VarSet();
        CFG_VarSet* loc = new CFG_VarSet();
        bool il = false;
        while (p != NULL)
        {
            res->Unite(p->GetUse(), false);
            loc->Unite(p->GetDef(), false);
            p = p->GetLexNext();
        }
        //printf("USE: ");
        //res->print();
        //printf("LOC: ");
        //loc->print();
        res->Unite(loc, false);
        //printf("GETUSE: ");
        //getUse()->print();

        //res->minus(getUse()); //test!
        res->MinusFinalize(GetUse(), true);
        pri = res;

        delete loc;
    }
    return pri;
}

void CFG_ControlFlowGraph::LiveAnalysis()
{
    bool same = false;
    int it = 0;
    CFG_BasicBlock* p = first;
    p = first;
    while (!same) 
    {
        p = last;
        same = true;
        while (p != NULL) 
        {
            same = p->StepLVOut() && same;
            same = p->StepLVIn() && same;
            p = p->GetLexPrev();
        }
        it++;
        //printf("iters: %d\n", it);
    }
}

std::string CFG_ControlFlowGraph::GetVisualGraph(CFG_Call* calls)
{
    std::string result;
    result += "digraph ";
    char tmp[512];
    const CFG_CallData* cd = calls->GetDataForGraph(this);
    //if (cd == NULL || cd->header == NULL)
    sprintf(tmp, "g_%llx", (uintptr_t)this);
    //else
    //    sprintf(tmp, "g_%500s", cd->header->symbol());
    result += tmp;
    result += "{ \n";
    for (CFG_BasicBlock* b = this->first; b != NULL; b = b->GetLexNext()) 
    {
        if (!b->IsEmptyBlock()) 
        {
            result += '\t' + b->GetGraphVisDescription() + "[shape=box,label=\"";
            result += b->GetGraphVisData() + "\"];\n";
        }
    }

    for (CFG_BasicBlock* b = first; b != NULL; b = b->GetLexNext()) 
    {
        if (!b->IsEmptyBlock())
            result += b->GetEdgesForBlock(b->GetGraphVisDescription(), true, "");
    }
    result += '}';
    ResetDrawnStatusForAllItems();
    return result;
}

void CFG_ControlFlowGraph::ResetDrawnStatusForAllItems() 
{
    for (CFG_BasicBlock* b = first; b != NULL; b = b->GetLexNext())     
        for (CFG_ControlFlowItem* it = b->GetStart(); it != NULL && (it->IsLeader() == false || it == b->GetStart()); it = it->GetNext()) 
            it->ResetDrawnStatus();    
}

void CFG_ControlFlowGraph::PrivateAnalyzer()
{
    if (hasBeenAnalyzed)
        return;
    CFG_BasicBlock* p = first;
    /*
    printf("GRAPH:\n");
    while (p != NULL){
        printf("block %d: ", p->getNum());
        if (p->containsParloopStart())
            printf("start");
        if (p->containsParloopEnd())
            printf("end");
        p->print();
        p = p->getLexNext();
    }
    */
    p = first;
    LiveAnalysis();

    while (1)
    {
        CFG_ControlFlowItem* lstart;
        CFG_BasicBlock* of = p;
        p->PrivateAnalysisForAllCalls();
        if ((lstart = p->ContainsParloopStart()) != NULL)
        {
            if (!ProcessOneParallelLoop(lstart, of, p, true))
                break;
        }
        if (p == last)
            break;
        p = p->GetLexNext();
    }
    hasBeenAnalyzed = true;
}

bool CFG_ControlFlowGraph::ProcessOneParallelLoop(CFG_ControlFlowItem* lstart, CFG_BasicBlock* of, CFG_BasicBlock*& p, bool first)
{
    int stored_fid = SwitchFile(lstart->GetProc()->file_id);
    CFG_ControlFlowItem* lend;
    if (G_is_correct != NULL)
    {
        const char* expanded_log;
        char* tmp = NULL;
        if (G_failed_proc_name)
        {
            tmp = new char[strlen(G_is_correct) + 2 + strlen(G_failed_proc_name) + 1];
            strcpy(tmp, G_is_correct);
            strcat(tmp, ": ");
            strcat(tmp, G_failed_proc_name);
            expanded_log = tmp;
        }
        else
            expanded_log = G_is_correct;

        //TODO
        //Warning("Private analysis is not conducted for loop: '%s'", expanded_log ? expanded_log : "", PRIVATE_ANALYSIS_NOT_CONDUCTED, lstart->GetPrivateListStatement());
        if (tmp)
            delete[] tmp;

    }
    else
    {
        while ((lend = p->ContainsParloopEnd()) == NULL)
        {
            p->PrivateAnalysisForAllCalls();
            p = p->GetLexNext();
            CFG_ControlFlowItem* mstart;
            if ((mstart = p->ContainsParloopStart()) != NULL)
            {
                CFG_BasicBlock* mp = p;
                if (first) {
                    if (!ProcessOneParallelLoop(mstart, of, mp, false)) 
                    {
                        SwitchFile(stored_fid);
                        return false;
                    }
                }
            }
        }

        CFG_BasicBlock* afterParLoop = p->GetLexNext()->GetLexNext();
        CFG_VarSet* l_pri = CFG_ControlFlowGraph(true, false, lstart, lend).GetPrivate();
        if (G_is_correct != NULL)
        {
            const char* expanded_log;
            char* tmp = NULL;
            if (G_failed_proc_name)
            {
                tmp = new char[strlen(G_is_correct) + 2 + strlen(G_failed_proc_name) + 1];
                strcpy(tmp, G_is_correct);
                strcat(tmp, ": ");
                strcat(tmp, G_failed_proc_name);
                expanded_log = tmp;
            }
            else
                expanded_log = G_is_correct;

            //TODO
            //Warning("Private analysis is not conducted for loop: '%s'", expanded_log ? expanded_log : "", PRIVATE_ANALYSIS_NOT_CONDUCTED, lstart->getPrivateListStatement());
            if (tmp)
                delete[] tmp;
            SwitchFile(stored_fid);
            return false;
        }
        CFG_VarSet* p_pri = new CFG_VarSet();
        SgExpression* ex_p = lstart->GetPrivateList();
        if (ex_p != NULL)
            ex_p = ex_p->lhs();
        for (; ex_p != NULL; ex_p = ex_p->rhs())
        {
            SgVarRefExp* pr;
            if (pr = isSgVarRefExp(ex_p->lhs()))
            {
                CFG_ScalarVarEntryInfo* tmp = new CFG_ScalarVarEntryInfo(pr->symbol());
                p_pri->AddToSet(tmp, NULL);
                delete tmp;
            }
            SgArrayRefExp* ar;
            if (ar = isSgArrayRefExp(ex_p->lhs()))
            {
                CFG_ArrayVarEntryInfo* tmp = new CFG_ArrayVarEntryInfo(ar->symbol(), ar);
                p_pri->AddToSet(tmp, NULL);
                delete tmp;
            }
        }

        CFG_VarSet* live = afterParLoop->GetLiveIn();
        CFG_VarSet* adef = afterParLoop->GetDef();
        CFG_VarSet* pri = new CFG_VarSet();
        CFG_VarSet* tmp = new CFG_VarSet();
        CFG_VarSet* delay = new CFG_VarSet();
        tmp->Unite(l_pri, false);

        while (tmp->GetList().size())        
        {
            const CFG_VarItem *exp = tmp->GetList()[0];
            if (!afterParLoop->IsVarDefinedAfterThisBlock(exp->Var(), false))
                delay->AddToSet(exp->Var(), NULL);
            tmp->Remove(exp->Var());
        }

        delete tmp;
        pri->Unite(l_pri, false);
        pri->Minus(live, true);
        G_privateDelayedList = new CFG_PrivateDelayedItem(pri, p_pri, l_pri, lstart, G_privateDelayedList, this, delay, current_file_id);
        of->SetDelayedData(G_privateDelayedList);
    }
    SwitchFile(stored_fid);
    return true;
}

static int IsThisVariableAParameterOfSubroutine(const CFG_CallData *lst, SgSymbol* s)
{
    if (!lst->header)
        return -1;
    int stored = SwitchFile(lst->file_id);
    SgProcHedrStmt* h = isSgProcHedrStmt(lst->header);
    if (!h)
        return -1;
    for (int i = 0; i < h->numberOfParameters(); i++) 
    {
        SgSymbol* par = h->parameter(i);
        if (par == s) 
        {
            SwitchFile(stored);
            return i;
        }
    }
    SwitchFile(stored);
    return -1;
}

static SgExpression* GetProcedureArgument(bool isF, void *f, const int i)
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

CFG_ActualDelayedData* CFG_ControlFlowGraph::ProcessDelayedPrivates(CFG_CommonData* commons, const CFG_CallData* call, CFG_CallAnalysisLog* log, void* c, bool isFun, int file_id)
{
    for (CFG_CallAnalysisLog* i = log; i != NULL; i = i->prev) 
    {
        if (i->el == call) 
        {
            //TODO
            //Warning("Recursion is not analyzed for privates in common blocks '%s'", "", PRIVATE_ANALYSIS_NO_RECURSION_ANALYSIS, call->header);
            return NULL;
        }
    }

    CFG_CallAnalysisLog* nl = new CFG_CallAnalysisLog();
    nl->el = call;
    nl->prev = log;
    if (log == NULL)
        nl->depth = 0;
    else
        nl->depth = log->depth + 1;
    log = nl;

    CFG_ActualDelayedData* my = NULL;
    for (CFG_BasicBlock* bb = first; bb != NULL; bb = bb->GetLexNext()) 
    {
        if (bb->ContainsParloopStart()) 
        {
            if (bb->GetDelayedData()) 
            {
                CFG_ActualDelayedData* data = new CFG_ActualDelayedData();
                data->original = bb->GetDelayedData();
                data->commons = commons->GetCommonsForVarSet(data->original->GetDetected(), call);

                CFG_VarSet* bu = new CFG_VarSet();
                bu->Unite(data->original->GetDelayed(), false);
                CFG_VarSet* tbu = new CFG_VarSet();
                while (!bu->isEmpty())
                {
                    if (IS_BY_USE(bu->GetList()[0]->Var()->GetSymbol()))
                        tbu->AddToSet(bu->GetList()[0]->Var(), NULL);
                    else 
                    {
                        CFG_VarEntryInfo* old = bu->GetList()[0]->Var();
                        int arg_id = IsThisVariableAParameterOfSubroutine(call, bu->GetList()[0]->Var()->GetSymbol());
                        if (arg_id != -1 && c != NULL)
                        {
                            int stored = SwitchFile(file_id);
                            SgExpression* exp = GetProcedureArgument(isFun, c, arg_id);
                            if (isSgVarRefExp(exp) || isSgArrayRefExp(exp))
                            {
                                SgSymbol* sym = exp->symbol();
                                CFG_VarEntryInfo* v;
                                if (isSgVarRefExp(exp)) 
                                    v = new CFG_ScalarVarEntryInfo(sym);
                                else 
                                    v = old->Clone(sym);
                                
                                tbu->AddToSet(v, NULL, old);
                            }
                            SwitchFile(stored);
                        }
                    }
                    bu->Remove(bu->GetList()[0]->Var());
                }
                data->buse = tbu;
                delete bu;
                data->next = my;
                data->call = call;
                my = data;
            }
        }

        CFG_ActualDelayedData* calldata = bb->GetDelayedDataForCall(log);
        while (calldata != NULL) 
        {
            for (auto &t : calldata->commons)
            {            
                CFG_CommonVarInfo &cvd = t;
                CFG_CommonDataItem* d = commons->IsThisCommonUsedInProcedure(cvd.parent, call);
                if (!d || commons->CanHaveNonScalarVars(d))
                    continue;

                if (cvd.parent->info.size() != d->info.size())
                    continue;
                int z = 0;
                for (; z < cvd.parent->info.size(); ++z)
                {
                    if (*cvd.parent->info[z].var == *cvd.var)
                        break;
                }
                if (z == cvd.parent->info.size())
                    continue;

                CFG_VarEntryInfo* var = d->info[z].var;
                if (bb->GetLexNext()->GetLiveIn()->Belongs(var->GetSymbol()) && calldata->original->GetDelayed()->Belongs(cvd.var))
                    calldata->MoveVarFromPrivateToLastPrivate(cvd.var, &t, NULL);
                
                if (bb->IsVarDefinedAfterThisBlock(var, false))
                    calldata->RemoveVarFromCommonList(&t);
            }

            if (log->el->header == calldata->call->header)
            {
                CFG_VarSet* pr = new CFG_VarSet();
                pr->Unite(calldata->original->GetDelayed(), false);
                pr->Intersect(bb->GetLexNext()->GetLiveIn(), false, true);
                while (pr->GetList().size())                
                {
                    const CFG_VarItem *exp = pr->GetList()[0];

                    calldata->MoveVarFromPrivateToLastPrivate(exp->Var(), NULL, NULL);
                    pr->Remove(exp->Var());
                }
                delete pr;
            }

            CFG_VarSet* tmp_use = new CFG_VarSet();
            tmp_use->Unite(calldata->buse, false);
            while (!tmp_use->isEmpty()) 
            {
                const CFG_VarItem *v = tmp_use->GetList()[0];
                CFG_VarEntryInfo* tmp = v->Var()->Clone(OriginalSymbol(v->Var()->GetSymbol()));
                if (bb->GetLexNext()->GetLiveIn()->Belongs(tmp->GetSymbol(), true))
                    calldata->MoveVarFromPrivateToLastPrivate(v->Ov() ? v->Ov() : v->Var(), NULL, calldata->buse);
                
                if (bb->IsVarDefinedAfterThisBlock(v->Var(), true))
                    calldata->buse->Remove(v->Ov() ? v->Ov() : v->Var());
                
                delete tmp;
                tmp_use->Remove(v->Var());
            }

            delete tmp_use;
            CFG_ActualDelayedData* tmp = calldata->next;
            calldata->next = my;
            my = calldata;
            calldata = tmp;
        }
    }
    nl = log;
    log = log->prev;

    delete nl;
    return my;
}

void CFG_ActualDelayedData::MoveVarFromPrivateToLastPrivate(CFG_VarEntryInfo* var, const CFG_CommonVarInfo *c, CFG_VarSet* vs)
{
    original->MoveFromPrivateToLastPrivate(var);
    RemoveVarFromCommonList(c);
    if (vs)
    {
        if (vs->Belongs(var))
            vs->Remove(var);
    }
}

void CFG_ActualDelayedData::RemoveVarFromCommonList(const CFG_CommonVarInfo *c)
{
    if (commons.size() == 0 || c == NULL)
        return;

    int z = 0;
    for ( ; z < commons.size(); ++z)
    {
        if (*commons[z].var == *c->var)
            break;
    }
    commons.erase(commons.begin() + z);    
}

void CFG_PrivateDelayedItem::MoveFromPrivateToLastPrivate(CFG_VarEntryInfo* var)
{
    const CFG_VarItem* el = detected->Belongs(var);
    if (el) 
    {
        CFG_eVariableType storedType = el->Var()->GetVarType();
        detected->Remove(el->Var());
        lp->AddToSet(var, NULL);
    }
}

void SetUpVars(CFG_CommonData* commons, CFG_Call *calls, const CFG_CallData *m, CFG_DoLoopDataList* list)
{
    G_pCommons = commons;
    G_pCalls = calls;
    G_currentProcedure = m;
    G_mainProcedure = G_currentProcedure;
    G_doLoopList = list;
}

CFG_GRAPH* buildCFG(SgStatement *mainUnit)
{
    if (mainUnit->variant() != PROG_HEDR)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    CFG_GRAPH *result = new CFG_GRAPH();

    CFG_Call *calls = new CFG_Call();
    CFG_CommonData *commons = new CFG_CommonData();
    CFG_DoLoopDataList *doloopList = new CFG_DoLoopDataList();
    SetUpVars(commons, calls, calls->AddHeader(mainUnit, false, mainUnit->symbol(), current_file_id), doloopList);

    //stage 1: preparing graph data
    CFG_ControlFlowGraph* CGraph = GetControlFlowGraphWithCalls(true, mainUnit, calls, commons);
    calls->AssociateGraphWithHeader(mainUnit, CGraph);
    commons->MarkEndOfCommon(G_currentProcedure);

    //DEBUG: graphvis
    /*
    std::fstream fs;
    fs.open("graph.txt", std::fstream::out);
    fs << CGraph->GetVisualGraph(&calls);
    fs.close();
    */

    CFG_VarSet *list = G_currentProcedure->graph->GetPrivate();

    //DEBUG
    //calls.PrintControlFlows();

    //stage 2: data flow analysis
    CGraph->PrivateAnalyzer();
    
    result->calls = calls;
    result->commons = commons;
    result->doloopList = doloopList;
    result->graph = CGraph;
    
    if (G_privateDelayedList)
        delete G_privateDelayedList;
    G_privateDelayedList = NULL;

    return result;
}
#endif