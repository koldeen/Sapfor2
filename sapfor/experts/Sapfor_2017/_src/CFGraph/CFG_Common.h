#pragma once
#include "dvm.h"

#define INTRINSIC_IN 1
#define INTRINSIC_OUT 2

static inline bool isIntrinsicFunctionNameACC(char* name)
{
    return isIntrinsicFunctionName(name);
}

CFG_ControlFlowItem* getControlFlowList(SgStatement *firstSt, SgStatement *lastSt, CFG_ControlFlowItem *&last, SgStatement *&lastAnStmt, doLoops* loops, CFG_Call *calls, CFG_CommonData *commons);