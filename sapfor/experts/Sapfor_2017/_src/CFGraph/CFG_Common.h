#pragma once
#include "dvm.h"

#include "CFGraph.h"
#include "CFG_Variables.h"
#include "CFG_BasicBlock.h"

#define INTRINSIC_IN 1
#define INTRINSIC_OUT 2

static inline bool isIntrinsicFunctionNameACC(char* name)
{
    return isIntrinsicFunctionName(name);
}

class CFG_ControlFlowItem;
class CFG_DoLoops;
class CFG_Call;
class CFG_CommonData;

int SwitchFile(const int file_id);
CFG_ControlFlowItem* getControlFlowList(SgStatement *firstSt, SgStatement *lastSt, CFG_ControlFlowItem *&last, SgStatement *&lastAnStmt, CFG_DoLoops* loops, CFG_Call *calls, CFG_CommonData *commons);