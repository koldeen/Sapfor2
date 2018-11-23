//////////////////////////////////////////////////////////////////////////
// To deals with the intrinsics function call
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "sage++user.h"
#include "definesValues.h"
#include "intrinsic.h"
#include <string>
#include <set>


extern std::set<std::string> intrinsicF;
extern void initIntrinsicFunctionNames();

// return TRUE if OK and FALSE otherwise
int isSymbolIntrinsic(SgSymbol *symb)
{
    initIntrinsicFunctionNames();
        
    SgFunctionSymb *fs;
    char *ident;
    if (fs = isSgFunctionSymb(symb))
    {
        ident = fs->identifier();
        if (!ident)
            return FALSE;
        if (intrinsicF.find(ident) == intrinsicF.end())
            return FALSE;
        else
            return TRUE;
    }
    return FALSE;
}

int isExprCallToFuncNotIntrinsic(SgExpression *exp)
{
    SgFunctionCallExp *fc;

    if (!exp)
        return FALSE;

    if (fc = isSgFunctionCallExp(exp))
    {
        if (!isSymbolIntrinsic(fc->funName()))
            return TRUE;
    }

    if (isExprCallToFuncNotIntrinsic(exp->lhs()))
        return TRUE;
    if (isExprCallToFuncNotIntrinsic(exp->rhs()))
        return TRUE;

    return FALSE;
}


int isStmtCallToFuncNotIntrinsic(SgStatement *stmt)
{
    int i;
    SgStatement *child;

    if (!stmt)
        return FALSE;

    if (isExprCallToFuncNotIntrinsic(stmt->expr(0)))
        return TRUE;
    if (isExprCallToFuncNotIntrinsic(stmt->expr(1)))
        return TRUE;
    if (isExprCallToFuncNotIntrinsic(stmt->expr(2)))
        return TRUE;

    i = 1;
    child = stmt->childList1(0);
    while (child)
    {
        if (isStmtCallToFuncNotIntrinsic(child))
            return TRUE;
        child = stmt->childList1(i);
        i++;
    }
    i = 1;
    child = stmt->childList2(0);
    while (child)
    {
        if (isStmtCallToFuncNotIntrinsic(child))
            return TRUE;
        child = stmt->childList2(i);
        i++;
    }
    return FALSE;
}
