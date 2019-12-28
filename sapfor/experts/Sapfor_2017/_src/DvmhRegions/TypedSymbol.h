#pragma once

#include "dvm.h"
#include "../Utils/SgUtils.h"
#include <string>

enum VAR_TYPE { VAR_ARR, VAR_DISTR_ARR, VAR_SCALAR, VAR_ANY, VAR_UNDEFINED };

class TypedSymbol
{
public:
    SgSymbol* orig;
    VAR_TYPE type;

    TypedSymbol(SgExpression*);
    friend bool operator== (const TypedSymbol& lhs, const TypedSymbol& rhs);
    friend bool operator< (const TypedSymbol& lhs, const TypedSymbol& rhs);
};
