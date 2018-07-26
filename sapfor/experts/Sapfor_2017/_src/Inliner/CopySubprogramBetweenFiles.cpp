#include "../Utils/leak_detector.h"

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "dvm.h"

using std::map;
using std::string;
using std::vector;
using std::make_pair;

static SgSymbol* copySymbol(const string &from, const string &to, map<SgSymbol*, SgSymbol*> &copiedSymbols, map<SgType*, SgType*> &copiedTypes, SgSymbol *symb);
static SgType* copyType(const string &from, const string &to, map<SgSymbol*, SgSymbol*> &copiedSymbols, map<SgType*, SgType*> &copiedTypes, SgType *type);

//TODO: copy len - SgExpression
static SgType* copyType(const string &from, const string &to,
                     map<SgSymbol*, SgSymbol*> &copiedSymbols, map<SgType*, SgType*> &copiedTypes,
                     SgType *type)
{
    if (type)
    {
        auto itType = copiedTypes.find(type);
        if (itType == copiedTypes.end())
        {
            SgType *base = copyType(from, to, copiedSymbols, copiedTypes, type->baseType());
            SgSymbol *symb = copySymbol(from, to, copiedSymbols, copiedTypes, type->symbol());

            SgFile::switchToFile(to);
            SgType *newT = new SgType(type->variant(), symb, NULL, base);
            SgFile::switchToFile(from);
            
            itType = copiedTypes.find(type);
            if (itType == copiedTypes.end())
                itType = copiedTypes.insert(itType, make_pair(type, newT));
        }

        return itType->second;
    }
    else
        return NULL;
}

static SgSymbol* copySymbol(const string &from, const string &to,
                       map<SgSymbol*, SgSymbol*> &copiedSymbols, map<SgType*, SgType*> &copiedTypes,
                       SgSymbol *symb)
{
    SgSymbol *copy = symb;

    if (copy)
    {
        auto it = copiedSymbols.find(copy);
        if (it == copiedSymbols.end())
        {
            SgType *t = copyType(from, to, copiedSymbols, copiedTypes, copy->type());

            SgFile::switchToFile(to);
            SgSymbol *newS = new SgSymbol(copy->variant(), copy->identifier(), t, NULL);
            SgFile::switchToFile(from);
                        
            it = copiedSymbols.find(copy);
            if (it == copiedSymbols.end())
                it = copiedSymbols.insert(it, make_pair(copy, newS));
        }
        return it->second;
    }
    else
        return NULL;
}

static void copyAllSymbolsAndTypes(const string &from, const string &to, 
                                   map<SgSymbol*, SgSymbol*> &copiedSymbols, map<SgType*, SgType*> &copiedTypes,
                                   SgExpression *ex)
{
    if (ex)
    {
        if (ex->symbol())
            copySymbol(from, to, copiedSymbols, copiedTypes, ex->symbol());
        if (ex->type())
            copyType(from, to, copiedSymbols, copiedTypes, ex->type());
        
        copyAllSymbolsAndTypes(from, to, copiedSymbols, copiedTypes, ex->lhs());
        copyAllSymbolsAndTypes(from, to, copiedSymbols, copiedTypes, ex->rhs());
    }
}

int copySubprogram(SgFile *from, SgFile *to, SgStatement *subProg, SgStatement *out)
{
    int err = 0;

    if (from->filename() != subProg->fileName())
        return -1;

    if (from == to)
    {
        SgSymbol *copyProg = &(subProg->symbol()->copySubprogram(*from->firstStatement()));
        out = from->firstStatement()->lexNext();
    }
    else
    {
        map<SgSymbol*, SgSymbol*> copiedSymbols;
        map<SgType*, SgType*> copiedTypes;

        string fromF(from->filename());
        string toF(to->filename());

        SgFile::switchToFile(fromF);

        for (auto st = subProg; st != subProg->lexNext(); st = st->lexNext())
        {
            copySymbol(fromF, toF, copiedSymbols, copiedTypes, st->symbol());
            for (int i = 0; i < 3; ++i)
                copyAllSymbolsAndTypes(fromF, toF, copiedSymbols, copiedTypes, st->expr(i));            
        }
    }
    return err;
}
