//
// Created by Vladislav Volodkin on 12/24/19.
//

#include "TypedSymbol.h"


using namespace std;


TypedSymbol::TypedSymbol(SgExpression* orig_exp) : orig(orig_exp->symbol())
{
    type = VAR_UNDEFINED;

    if (orig_exp->variant() == VAR_REF)
    {
        type = VAR_SCALAR;
        return;
    }

    if (orig_exp->variant() == ARRAY_REF)
        type = VAR_ARR;

    if (!getArrayFromDeclarated(declaratedInStmt(orig), orig->identifier())->GetNonDistributeFlag())
        type = VAR_DISTR_ARR;
}

bool operator== (const TypedSymbol &lhs, const TypedSymbol &rhs)
{
    // symbols are the same, if they have one name and are defined in one scope, TODO: is orig->id() enough?
    return string(lhs.orig->identifier()) == string(rhs.orig->identifier()) && lhs.orig->scope()->id() == rhs.orig->scope()->id();
}