//
// Created by Vladislav Volodkin on 12/24/19.
//

#ifndef SAPFOR_TYPEDSYMBOL_H
#define SAPFOR_TYPEDSYMBOL_H
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
    friend bool operator== (const TypedSymbol &lhs, const TypedSymbol &rhs);
};

namespace std
{
    template <>
    struct hash<TypedSymbol>
    {
        std::size_t operator()(const TypedSymbol& s) const
        {
            using std::size_t;
            using std::hash;

            return hash<int>()(s.orig->id());
        }
    };
};


#endif //SAPFOR_TYPEDSYMBOL_H
