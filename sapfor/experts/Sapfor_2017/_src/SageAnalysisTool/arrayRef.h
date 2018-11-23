#pragma once 

struct arrayAccess {
  SgStatement *stmt;
  SgExpression *var; // this is var;
  int          linear[MAXDIMARRAY][MAXNESTEDLOOP];
  int          isLinear[MAXDIMARRAY];
  int          cst[MAXNESTEDLOOP];
  int          nbdim;
  int          size;
  int          type;
  int          rw;
  int          scalar;
  int          level; // give the loop number
};

typedef struct arrayAccess *PT_ACCESSARRAY;

