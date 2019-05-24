#include "../Utils/leak_detector.h"
#if NEW_CFG
#include "dvm.h"
#include "CFGraph.h"
#include "../Utils/errors.h"
#include "../Utils/SgUtils.h"


bool CFG_CallData::IsArgIn(int i, CFG_ArrayVarEntryInfo *&p) const
{
    const int stored = SwitchFile(this->file_id);
    SgProcHedrStmt* h = isSgProcHedrStmt(header);
    CFG_VarSet* use = graph->getUse();
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

    graph->privateAnalyzer();
    CFG_VarSet* def = graph->getDef();
    SgSymbol* par = h->parameter(i);

    const CFG_VarItem* result = def->Belongs(par);
    if (result && result->var->GetVarType() == VAR_REF_ARRAY_EXP && p)
        p = (CFG_ArrayVarEntryInfo*)result->var;

    SwitchFile(stored);
    return result;
}
#endif