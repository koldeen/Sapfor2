#pragma once

#if !__SPC
#include "dvm.h"

template<typename T>
class Base
{
    void *orig;
public:
    explicit Base(T init) { orig = init; }
    T GetOriginal() const { return (T)orig; }
};

class Statement : public SgStatement, public Base<SgStatement*>
{
public:
    explicit Statement(SgStatement *init) : SgStatement(*init), Base(init) { }
};

class Expression : public SgExpression, public Base<SgExpression*>
{
public:
    explicit Expression(SgExpression *init) : SgExpression(*init), Base(init) { }
};

class File : public SgFile, public Base<SgFile*>
{
public:
    explicit File(SgFile *init) : SgFile(*init), Base(init) { }
};

class ArrayRefExp : public SgArrayRefExp, public Base<SgArrayRefExp*>
{
public:
    explicit ArrayRefExp(SgArrayRefExp *init) : SgArrayRefExp(*init), Base(init) { }
};

class Symbol : public SgSymbol, public Base<SgSymbol*>
{
public:
    explicit Symbol(SgSymbol *init) : SgSymbol(*init), Base(init) { }
};
#else

#define DVM_DISTRIBUTE_DIR           277
#define DVM_REDISTRIBUTE_DIR         299
#define DVM_ALIGN_DIR                219 
#define DVM_REALIGN_DIR              220 
#define DVM_SHADOW_DIR               224 
#define DVM_VAR_DECL           	     248

//fix this include for your needs!
class Statement
{
public:
    //TODO:
    std::string fileName() { return ""; }
    void extractStmt() { }
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