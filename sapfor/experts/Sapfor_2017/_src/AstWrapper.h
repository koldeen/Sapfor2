#pragma once

#if !__SPC
#include "dvm.h"

class Statement : public SgStatement
{
    void *orig;
public:
    explicit Statement(SgStatement *init) : SgStatement(*init) { orig = init; }
};

class Expression : public SgExpression
{
    void *orig;
public:
    explicit Expression(SgExpression *init) : SgExpression(*init) { orig = init; }
};

class File : public SgFile
{
    void *orig;
public:
    explicit File(SgFile *init) : SgFile(*init) { orig = init; }
};

class ArrayRefExp : public SgArrayRefExp
{
    void *orig;
public:
    explicit ArrayRefExp(SgArrayRefExp *init) : SgArrayRefExp(*init) { orig = init; }
};

class Symbol : public SgSymbol
{
    void *orig;
public:
    explicit Symbol(SgSymbol *init) : SgSymbol(*init) { orig = init; }
};
#else

//fix this include for your needs!
class Statement
{
public:
    //TODO:
    std::string fileName() { return ""; }
};

class Expression
{

};

class File
{

};

class ArrayRefExp
{

};

class Symbol
{

};
#endif