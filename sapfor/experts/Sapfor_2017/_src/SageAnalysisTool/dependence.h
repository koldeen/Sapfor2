#pragma once
//
// for computing loop dependencies
//

struct datadep 
{
    SgStatement *loop;
    int          loopnum;
    SgStatement *stmtin;
    SgStatement *stmtout;
    SgExpression *varin; // this is var;
    SgExpression *varout; // this is var;
    int          typedep;
    int          kinddep;
    int distance[MAXNESTEDLOOP];
};

typedef struct datadep *PT_DEPENDENCE;
