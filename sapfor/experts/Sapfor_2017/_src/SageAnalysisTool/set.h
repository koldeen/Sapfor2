#pragma once 

#include <stdio.h>
#include <malloc.h>
#include <sage++user.h>

//
// class Set used for data flow analysis...
//

class Set {
    void **data;
    int nbelement;
    int nballocated;
    int deallocelem;
    SgStatement *stmt;

    // used to compare two elements
    int(*equal)(void *e1, void *e2);
    void *(*combine)(void *e1, void *e2);
    void(*printEl)(void *e1);

public:
    Set(int(*feq)(void *e1, void *e2),
        void *(*fcomb)(void *e1, void *e2),
        void(*fp)(void *e1))
        /* end of fp */;
    ~Set();
    void interSet(Set *s1, Set *s2);
    void unionSet(Set *s1);
    Set *combineSet();
    void diffSet(Set *s1, Set *s2);
    int equalSet(Set *s1);
    int isInSet(void *e1);
    void setDealllocateElem() { deallocelem = 1; }
    void resetDealllocateElem() { deallocelem = 0; }
    void printSet();
    int size() const { return nbelement; }
    void addElement(void *el);
    void *rmElement(int i);
    void* getElement(int i) const;
    Set *compact();
    Set *copy();
    void setStmt(SgStatement *s) { stmt = s; }
    SgStatement* getStmt() const { return stmt; }
    // add a chunk to the size ;
    void Reallocatedata();
};
