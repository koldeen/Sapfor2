#pragma once

//
// Here we compute the induction variables for a loop
// this use the result of recheing analysis and invariant computation in loop.
// we use as element of sets the following structure.
//

struct constprop 
{
    int flag; // can be UNDEFFLAG, NONCONSTFLAG, CONSTFLAG
    SgExpression *var; // this is a var ref;
    int value;
    SgStatement *stmt;
    SgExpression *expr;
};

typedef struct constprop *PT_CONSTPROP;

