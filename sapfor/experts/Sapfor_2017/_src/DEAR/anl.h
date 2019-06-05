#include "user.h"
#include "dep_test.h"
#include <stdlib.h>

#ifdef IN_ANAL_
#define EXTERN
#else
#define EXTERN extern
#endif


#define MAXTAGS 1000
#define NVARS  200
#define NRTN   10000
#define NCOM   1000
#define NFILE  1000
#define DECL(A)  ((A)->thesymb->decl)

struct exlist {
       SgExpression *ex;
       exlist *list;
       int id;
       int flag;
       int flag_l;
       int flag_p;
};

struct calls_row {
       int id;
       int oper;
       SgSymbol *symb;
};

struct label_oper {
       int num;
       int oper;
       SgStatement *stat;
       label_oper *next;
};

struct redop {
       int oper;
       SgSymbol *symb;
       SgStatement *red_stat;
       redop *next;
};


struct commonlist {
       commonlist *next;
       char *name;
       int  id;
       int  atr;
       int  type;
       int  len;
       int  rank;
       int  lbound[10];
       int  rbound[10];
};

struct commonblock {
       commonblock *next;
       commonlist  *list; //SgExpression *comlist; 
       int id; //SgSymbol *scom; 
       int numfile;  
};

struct commondef {
       int routine;
       int comid;
       int comdef;
       SgExpression *list;
       commonblock *cblock;
};

const int VAR_ID    = 1001;
const int COM_ID    = 1002;
const int EXPR_ID   = 1003;
const int LOOP_ID   = 1004;
const int ROUTINE_ID= 1005;
const int USE_ID    = 1006;
const int OPER_ID   = 1007;
const int RED_OP    = 1008;
const int M_UNIT    = 1009;

enum {DATA_,SAVE_,EQUIVALENCE_,ASSOCIATION_};
enum {NUL_,READ_,WRITE_};
enum {UNIT_,FMT_,REC_,ERR_,IOSTAT_,END_,NML_,EOR_,SIZE_,ADVANCE_};
enum {U_,FILE_,STATUS_,ER_,IOST_,ACCESS_,FORM_,RECL_,BLANK_,EXIST_,
OPENED_,NUMBER_,NAMED_,NAME_,SEQUENTIAL_,DIRECT_,NEXTREC_,FORMATTED_,
UNFORMATTED_,POSITION_,ACTION_,READWRITE_,RD_,WR_,DELIM_,PAD_};


EXTERN char * fin_name;   //source file name
EXTERN char *tag[MAXTAGS];
EXTERN SgStatement *cur_func;  // current function (program unit)
EXTERN SgStatement *cur_st;  // current statement 
EXTERN int errcnt;  // counter of errors in file
EXTERN char db_buf[2048];  // buffer for writing row in table
EXTERN SgStatement *has_contains;   // contains statement in current function
EXTERN SgStatement *end_of_unit; //last statement of program unit
EXTERN SgStatement *file_header; //header of current file
EXTERN int saveall; //= 1 if there is SAVE without name-list in current function(procedure)
EXTERN int kt; 
EXTERN SgSymbol *symu[NVARS];
EXTERN int  modu[NVARS];
EXTERN int  useid[NVARS];
EXTERN int  rtid[NRTN];
EXTERN char *rname[NRTN];
EXTERN char *comname[NCOM];
EXTERN char *nameoffile[NFILE];
EXTERN label_oper *lab_list;
EXTERN exlist *Lexp;       // list of expressions of routine putting in table expressions 
EXTERN int in_arg_list;    // flag to specify that reference appears in argument list
EXTERN int use_mode;
EXTERN int has_implicit_loop;
EXTERN SgSymbol *no_name_symb; // symbol for unnamed common
EXTERN commonblock *first_common, *routine_common, *cur_common;
EXTERN int i_file; 
EXTERN int default_integer_size;
EXTERN int default_real_size;
//EXTERN TightlyNestedLoops *NLoop;
EXTERN SgExpression *VAL_1;

EXTERN int id_files;       // counter of rows in table files
EXTERN int id_routines;    // counter of rows in table routines
EXTERN int n_routines;     // counter of rows in table routines
EXTERN int id_vars;        // counter of rows in table vars
EXTERN int id_comid;       // counter of rows in table comid
EXTERN int id_comdef;      // counter of rows in table comdef
EXTERN int id_expressions; // counter of rows in table expressions
EXTERN int id_monoms;      // counter of rows in table monoms
EXTERN int id_loops;       // counter of rows in table loops
EXTERN int id_operators;   // counter of rows in table operators
EXTERN int id_usage;       // counter of rows in table usage
EXTERN int id_calls;       // counter of rows in table calls
EXTERN int id_classes;     // counter of rows in table classes

void printVars();

#define IS_INTRINSIC_TYPE(T) (!TYPE_RANGES((T)->thetype) && !TYPE_KIND_LEN((T)->thetype) && ((T)->variant() != T_DERIVED_TYPE))
#define VAR(A)  ((int*)(A)->attributeValue(0,VAR_ID))
#define EXPR(A) ((exlist*)(A)->attributeValue(0,EXPR_ID))
#define LOOP(A)  ((int*)(A)->attributeValue(0,LOOP_ID))
#define ROUTINE(A) ((int*)(A)->attributeValue(0,ROUTINE_ID))
#define USE(A) ((int*)(A)->attributeValue(0,USE_ID))
#define OPER(A) ((int*)(A)->attributeValue(0,OPER_ID))
#define REDOP(A) ((int*)(A)->attributeValue(0,RED_OP))



#define COMM(A)  ((commondef*)(A)->attributeValue(0,COM_ID))
#define IN_DATA(A)  ((A)->attributes() & DATA_BIT) 
#define IN_EQUIVALENCE(A)  ((A)->attributes() & EQUIVALENCE_BIT)
#define IN_COMMON(A)  ((A)->attributes() & COMMON_BIT) 
#define IS_DUMMY(A)  ((A)->thesymb->entry.var_decl.local == IO)  
#define IS_SAVE(A) (((A)->attributes() & SAVE_BIT) || (saveall && !IN_COMMON(A) && !IS_DUMMY(A)) )
#define IS_INTRINSIC_FUNC(A)  ((A)->attributes() & INTRINSIC_BIT) 
#define HAS_ASSOCIATION_ATR(A)  ((A)->attributes() & ASSOCIATION_BIT)


//#define CREATE_LOOP(I,LOOPID)  (/*TightlyNestedLoops(I);*/ printf("create nest %d\n",LOOPID);)
//#define ADD_LOOP(A,I,LOOPID)  (/*(A)->AddNest(I);*/ printf("add nest %d\n",LOOPID);)
//------------------------------------------------------------------
/* analyzer2.cpp */
void PrintTypeTable(SgFile *f);
void printType(SgType *t);
void printIntrinsicType (SgType *t);
void printSymb(SgSymbol *s);
void PrintSymbolTable(SgFile *f);
int isHeaderStmtSymbol(SgSymbol *s);
void initialize();
void initVariantNames();
char * OnlyName(char *filename);
void AnalyseFile(SgFile *file, int fileid);
void  AnalyseProgramUnit(SgStatement *func, int fileid);
int is_SAVE_inRoutine(SgStatement *func);
void testSAVEandCOMMONinRoutine(SgStatement *func);
char *Postfix(SgExpression *e);
int hasPostfix(SgExpression *e);
void CommonList(SgStatement *stmt,int routine);
void ParameterList(SgExpression *el);
commondef *isComdefForRoutine(SgSymbol *sn, int routine);
void Call(SgSymbol *s, SgExpression *e);
void Argument(SgExpression *e, int i, int call, MemoryUnitUsage **params);
//void Index(SgExpression *e, int use, int ind);
void RefInExpr(SgExpression *e, int mode);
int isInUsage(SgSymbol *s, int mode);
void RefInArg(SgExpression *e, int expr);
int isDoEndStmt(SgStatement *stmt);
int isDoEndStmt_f90(SgStatement *stmt);
SgStatement * lastStmtOfDo(SgStatement *stdo);
void ProgramStructure(SgFile *file);
int Usage(SgExpression *e);
int isIntrinsicFunctionName(const char *name);
SgStatement *NextExecStat(SgStatement *stmt);
SgStatement *ParentOfDo(SgStatement *dost);
int control_list1(SgExpression *e, SgExpression *ioc[]);
int control_list_open(SgExpression *e, SgExpression *ioc[]);
int IOcontrol(SgExpression *e, SgExpression *ioc[],int type);
int TestIOList(SgExpression *iol,SgStatement *stmt);
int ImplicitLoopTest(SgExpression *eim,SgStatement *stmt);
int IOitemTest(SgExpression *e,SgStatement *stmt);
int OperWithLab(SgLabel *lab);
SgStatement *NextByControl(SgStatement *stmt);
int idOfOper(SgStatement *stmt);
SgStatement * lastStmtOfIf(SgStatement *stif);
void TestReduction(SgStatement *stmt);
SgStatement *ParentDo(SgStatement *st);
int TestArgsRedOp(SgExpression *rve,SgExpression *args);
int isMaxMinFunc(char *name);
char *TextOp(int iop);
void TestSymbRed(redop *p, SgStatement *loop);
void  RetestReduction(SgStatement *loop);
int TestVarRef(SgSymbol *s,SgExpression *e);
int TestRedArg(SgExpression *rve,SgExpression *arg);
void AddReductionAttribute(SgStatement *loop, int iop, SgStatement *redst, SgSymbol *sr);
SgStatement *ParentLoop(SgStatement *st);
int TestRedCondition(int vrnt);
void AnalyzeReductions(SgStatement *loop, int n);
int isOperandOfOper(SgExpression *ev, SgExpression *e, int oper);
void AnalyzeComment(SgStatement *stmt);
SgSymbol *UnnamedCommon();
int CompareDims(SgArrayType *artype1, SgArrayType *artype2);
int SameObjects (SgSymbol *rs, SgSymbol *s);
SgType *Base_Type(SgType *t);
int CompareObjects(SgSymbol *rs, SgSymbol *s, int flag);
void CompareCommonDefs(commonblock *rcom, commonblock *com);
void TestingCommon();
int NumbOf(SgType *t);
int ValueOf(SgExpression *e);
void Bounds(int n, SgArrayType *artype, int lbound[], int rbound[]);
commonlist *createElementList(SgExpression *e);
commonlist *Connect_Common_List(commonlist *clist,SgExpression *elist);
commonlist *Create_Common_List(SgExpression *elist);
void CompareCommonDefinitions(commonlist *rcoml, commonlist *coml);
int CompareCommonObjects(commonlist *rcl, commonlist *cl, int flag);
int SameCommonObjects (commonlist *rcl, commonlist *cl);
void usage_in_do_stmt(SgStatement *stmt);


//------------------------------------------------------------------
/*  help.cpp */
SgLabel *  firstLabel(SgFile *f);
int isLabel(int num) ;
char * header (int i);
char *UnparseExpr(SgExpression *e) ;
void printVariantName(int i);
void Error(char *s, char *t, int num, SgStatement *stmt);
void err(char *s, int num, SgStatement *stmt);
void Err_g (char *s, char *t, int num);
void Warning(char *s, char *t, int num, SgStatement *stmt);
void warn(char *s, int num,SgStatement *stmt);
void Warn_g (char *s,  char *t, int num);
void errN(char *s, int num,SgStatement *stmt);
void format_num (int num, char num3s[]);
SgExpression *ConnectList(SgExpression *el1, SgExpression *el2);
int is_integer_value(char *str);
void Message(char *s, int l);
char * PfixRecord(PTR_LLND llnd);
void pfix_llnd(PTR_LLND pllnd);
void ErrMessage(char *s, int l);
void ErrMessageF(char *s, char *t, SgStatement *stmt);
int eqn(int n, char *a, char *b);


//------------------------------------------------------------------
/*  database.cpp */
int put_in_classes();
void put_in_classizes(int classid, int var, int value);
int put_in_files(char *filename);
int put_in_loops(SgStatement *stmt);
int put_in_routines(SgStatement *stmt, int fileid, int root);
int put_in_routines_nobody(int rootine_id, char *name, SgStatement *stmt);
void put_in_vars(SgStatement *func, int routine);
int put_in_dummies(SgStatement *func, int routine);
void put_in_dims(SgSymbol *s, int array, SgArrayType *artype);
void put_in_atr(int var, int iatr);
int put_in_comid(SgSymbol *sn);
int put_in_comdef();
void put_in_comdecl (SgSymbol *sn, int pe, int com, int def);
void put_in_comvars (int def, SgSymbol *s);
int put_in_operators(SgStatement *stmt);
int put_in_calls(SgSymbol *s);
void put_in_arguments(int call, int pos,  int expr);
int put_in_usage(SgSymbol *s, int mode);
void put_in_indexes(int use, int ind, int expr);
void put_in_expr_usage(int expr, int use);
void put_in_looptree(SgStatement *dost, SgStatement *parent, int tightly);
void put_root_in_looptree(int root);
void put_in_io(int oper,int mode);
void put_in_branches(int self, int next, int weight);
void put_in_analyzed(int scal_dep, int arr_dep, int red_dep, int priv_dep);
void put_in_depends(int loop, char* type, int var, char *redop);
void put_in_userdir(int oper, int line, char *dir);

int ExprWithPostfix(SgExpression *e);
int ExprWithLinearForm(SgExpression *e);
int Expr(SgExpression *e);
char *T_type(SgSymbol *s);
int Rank (SgSymbol *s);
int NumericTypeLength(SgType *t);
SgExpression * TypeLengthExpr(SgType *t);
SgExpression *LengthOfKindExpr(SgType *t, SgExpression *se, SgExpression *le);
SgExpression *LowerBound(SgArrayType *artype, int i);
SgExpression *UpperBound(SgArrayType *artype, int i);
void MinusMonom(SgExpression *e, int id);
void Monom(SgExpression *e, int id);
void LinearForm(SgExpression *e, int id);
int isLinearForm(SgExpression *e);
int isMonom(SgExpression *e);
int isValueOrVarRef(SgExpression *e);
SgExpression *Calculate(SgExpression *e);
SgExpression *ReplaceParameter(SgExpression *e);
int IdOfLoops(SgStatement *stmt);
void AddAttributeForExpr(SgExpression *e, int id, int flag);
exlist *isInTableExpressions(SgExpression *e);
int idOfVars(SgSymbol *s);
int ExpCompare(SgExpression *e1, SgExpression *e2);
int idOfRoutines(SgSymbol *s);
int RoutineId(SgSymbol *s);
exlist *AddToExprList(SgExpression *e, int id);
int isInTableComid(SgSymbol *s);
int IntrinsicTypeSize(SgType *t);
int isInTableFiles(char *fname);
int idOfFiles(char *fname);
int NoBodyRoutine(SgSymbol *sf); 
void  Add_In_Table_Routines(int num_routines);
int idOfCalledRoutine(SgSymbol *s); 

//----------------------------------
//extern "C" void exit(int status);