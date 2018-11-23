#pragma once

struct inducvar 
{
    int constante; // indicate if constante or induction
    SgStatement *stmt;
    SgExpression *var; // this is a var ref;
    SgExpression *stride;
    SgExpression *lbound;
    SgExpression *ubound;
    Set *reachdef;
    int level;
    int loopnum;
    int include;
};

typedef struct inducvar *PT_INDUCVAR;

