#pragma once

//fix this include for your needs!
#include "dvm.h"

class Statement : public SgStatement
{
public:
    explicit Statement(SgStatement *init) : SgStatement(*init) { }
};

class Expression : public SgExpression
{
public:
    explicit Expression(SgExpression *init) : SgExpression(*init) { }
};

class File : public SgFile
{
public:
    explicit File(SgFile *init) : SgFile(*init) { }
};

class ArrayRefExp : public SgArrayRefExp
{
public:
    explicit ArrayRefExp(SgArrayRefExp *init) : SgArrayRefExp(*init) { }
};

class Symbol : public SgSymbol
{
public:
    explicit Symbol(SgSymbol *init) : SgSymbol(*init) { }
};