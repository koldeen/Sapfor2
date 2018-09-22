/*********************************************************************/
/*                   D A T A    B A S E   W R I T I N G    2008      */
/*********************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <map>

//#include "vrd_db.h"
#include "anl.h"
using std::map;

char *text_atr[4] = { "data","save", "equivalence","association" };
char *text_mode[3] = { "NULL","READ","WRITE" };

static map<int, SgSymbol*> vars;

//char *text_atr[4] = {"DATA","SAVE", "EQUIVALENCE","ASSOCIATION"};
/*
int put_in_files(char *filename)
int put_in_routines(char *ident, int file, int line, int root)
int put_in_vars(char *ident, int routine, char *type, int dimno)
int put_in_dims(int array, int dims, int low, int high)
int put_in_atr(int var, char *mode)
int put_in_dummies(int routine, int var, int pos)
int put_in_comid(char *ident)
int put_in_comdef()
int put_in_comvars(int def, int var)
int put_in_comdecl(int pe, int com, int def)
int put_in_expressions(SgExpression *e)
int put_in_postfix(int expr, SgExpression *e)
int put_in_linexpr(int expr, int monom)
int put_in_monoms(int coeff, int var)
int put_in_loops(int line, float time, int var, int first, int last, int step)
int put_in_looptree(int self, int parent, int tightly)
int put_in_operators(int loop, int line)
int put_in_branches(int self, int next, int weight)
int put_in_usage(int oper, int var, char *mode)
int put_in_indexes(int use, int ind, int expr)
int put_in_calls(int oper, int routine)
int put_in_arguments(int call, int pos, int expr)
int put_in_expr_usage(int expr, int use)
int put_in_io(int oper, int mode)
int put_in_depends(int loop, char* type, int var, char *redop)
int put_in_analyzed(int scal_dep, int arr_dep, int priv_dep)
int put_in_userdir(int oper, int line, char *dir)
int put_in_classes(char *ident, char *comment)
int put_in_classizes(int class, int var, int value)
*/

/***************************/
MemoryUnit *dep_add_memory_unit(SgSymbol *s, int varid);
/***************************/

void printVars()
{
    for (auto &elem : vars)
        printf("var_id = %d, name %s\n", elem.first, elem.second->identifier());
}

int put_in_classes()
//puts row in table classes
//row of table classes:(int id,char *ident, char *comment)
{
    sprintf(db_buf, "%d, '%s', '%s'", ++id_classes, "default", "no comment");
    //vrd_put_row("classes",db_buf);
    return(id_classes);
}

void put_in_classizes(int classid, int var, int value)
// puts row in table classizes
{
    sprintf(db_buf, "%d, %d, %d", classid, var, value);
    //vrd_put_row("classizes",db_buf);
}

int put_in_files(char *filename)
{//puts row in table files
    int l;
    char *name;

    id_files++;
    l = strlen(filename);
    name = new char[l + 1];
    strcpy(name, filename);
    nameoffile[id_files] = name;
    if (id_files == NFILE)
        ErrMessage("Table of files is full", 0);

    sprintf(db_buf, "%d, '%s'", id_files, filename);
    //vrd_put_row("files",db_buf);
    return(id_files);
}

int put_in_loops(SgStatement *stmt)
{//puts row in table loops for routine header or for DO statement
 // row of table loops: (int line, float time, int var, int first, int last, int step)
    int *id;

    if (stmt->variant() != FOR_NODE)
    {
        sprintf(db_buf, "%d, %d, %d, NULL, NULL, NULL, NULL", ++id_loops, stmt->lineNumber(), 0);
        //vrd_put_row("loops",db_buf);
    }
    else
    {
        SgForStmt *stdo;
        SgExpression *estep;
        stdo = isSgForStmt(stmt);
        estep = stdo->step();
        if (!estep)
            estep = new SgValueExp(1);
        sprintf(db_buf, "%d, %d, %d, %d, %d, %d, %d", ++id_loops, stdo->lineNumber(), 1,
            idOfVars(stdo->symbol()), ExprWithPostfix(stdo->start()), ExprWithPostfix(stdo->end()), ExprWithPostfix(estep));
        //idOfVars(stdo->symbol()),ExprWithLinearForm(stdo->start()),ExprWithLinearForm(stdo->end()),ExprWithLinearForm(estep));

        //vrd_put_row("loops",db_buf);  
    }
    // adding attribute loop_id to stmt
    id = new int;
    *id = id_loops;
    stmt->addAttribute(LOOP_ID, (void *)id, sizeof(int));

    return(id_loops);
}


int put_in_routines(SgStatement *stmt, int fileid, int root)
{//puts row in table routines (for routine header)
    int routine_id, fid;
    SgSymbol *rs;
    char *name;

    rs = stmt->symbol();
    routine_id = idOfRoutines(rs); //RoutineId(rs);
    fid = idOfFiles(stmt->fileName());
    name = rs->identifier();
    if (!strcmp(name, "_MAIN"))
        name = "";

    sprintf(db_buf, "%d, '%s', %d, %d, %d", routine_id, name, fid, stmt->lineNumber(), root);
    //vrd_put_row("routines",db_buf);
    return(routine_id);
}

int put_in_routines_nobody(int routine_id, char *name, SgStatement *stmt)
{//puts row in table routines (for no body routine)
    int fid, line;
    if (!stmt)
        sprintf(db_buf, "%d, '%s', NULL, NULL, NULL", routine_id, name);
    else // dummy argument
    {
        fid = idOfFiles(stmt->fileName());
        line = stmt->lineNumber();
        sprintf(db_buf, "%d, '%s', %d, %d, NULL", routine_id, name, fid, line);
    }
    //vrd_put_row("routines",db_buf);
    return(routine_id);
}

void put_in_vars(SgStatement *func, int routine)
{//row of table: [int id, char *ident, int routine, char *type, int dimno]
 //puts rows in table vars for all variables with scope func (routine header) 
    SgSymbol *s, *sf, *sfnext;
    SgStatement *next_func;
    int var;
    int *id;
    next_func = func->lastNodeOfStmt()->lexNext();
    sf = func->symbol();

    sfnext = next_func ? next_func->symbol() : NULL;
    for (s = sf; s != NULL && s->scope() != next_func; s = s->next()) //for(s=sf; s!=sfnext; s=s->next())
    {
        if (s->variant() == VARIABLE_NAME && s->scope() != func)
            continue;
        if (!IS_DUMMY(s))
        {
            if (s->variant() == FUNCTION_NAME && s != sf
                || s->variant() == VARIABLE_NAME && ((s->attributes() & EXTERNAL_BIT) || (s->attributes() & INTRINSIC_BIT))
                || s->variant() == PROGRAM_NAME
                || s->variant() == ROUTINE_NAME
                || s->variant() == PROCEDURE_NAME
                || (!s->type()))
                continue;
        }
        /*
        if(s->variant()==FUNCTION_NAME && s!=sf && !IS_DUMMY(s)
        || s->variant()==VARIABLE_NAME && (s->attributes() & EXTERNAL_BIT) && !IS_DUMMY(s)
        || s->variant()==PROGRAM_NAME
        ||(s->variant()==ROUTINE_NAME  || s->variant()==PROCEDURE_NAME) && !IS_DUMMY(s)
        || s->variant()==VARIABLE_NAME && s->scope() != func
        || (! s->type()) )
        {            //if(s->variant()==FUNCTION_NAME)
        // TestIntrinsicName(s);
        continue;
        }
        */
        ++id_vars;

        vars[id_vars] = s;

        sprintf(db_buf, "%d, '%s', %d, '%s', %d", id_vars, s->identifier(), routine, T_type(s), Rank(s));
        //vrd_put_row("vars",db_buf);
        id = new int;
        var = *id = id_vars;
        s->addAttribute(VAR_ID, (void *)id, sizeof(int));
        if (IN_DATA(s))
            put_in_atr(id_vars, DATA_);
        if (IN_EQUIVALENCE(s))
            put_in_atr(id_vars, EQUIVALENCE_);
        if (IS_SAVE(s))
            put_in_atr(id_vars, SAVE_);

        dep_add_memory_unit(s, id_vars);
    }
}

void put_in_atr(int var, int iatr)
// row of table atr:(int var, char *mode)
// puts in table atr one row for var with attribute atr
{
    sprintf(db_buf, "%d, '%s'", var, text_atr[iatr]);
    //vrd_put_row("atr",db_buf);
}

int put_in_dummies(SgStatement *func, int routine)
// row of table: (int routine, int var, int pos)
// put in table dummies rows for all dummies of routine header 'func'
{
    PTR_SYMB  dummy;
    SgSymbol *darg, *sf;
    int var, i;
    int *pvar;
    sf = func->symbol();
    dummy = sf->thesymb->entry.proc_decl.in_list;
    i = 0;
    while (dummy)
    {
        darg = SymbMapping(dummy);
        pvar = VAR(darg);
        if (pvar)
            var = *pvar;
        else
        {
            var = 0;
            //err("no var id  for dummy", 2, func);
        }
        sprintf(db_buf, "%d, %d, %d", routine, var, ++i);
        //vrd_put_row("dummies",db_buf);
        dummy = dummy->entry.var_decl.next_in;
    }
    return(i);
}

void put_in_dims(SgSymbol *s, int array, SgArrayType *artype)
// row of table dims:(int array, int dims, int low, int high)
// put in table dims for all dimensions of array
{
    int i, n, il, iu;
    SgExpression *el, *eu;
    n = artype->dimension();
    for (i = 0; i<n; i++)
    {
        el = LowerBound(artype, i);
        if (!el)
            continue;
        eu = UpperBound(artype, i);
        if (!eu)
            continue;

        il = ExprWithPostfix(el);
        iu = ExprWithPostfix(eu);
        sprintf(db_buf, "%d, %d, %d, %d", array, i + 1, il, iu);
        //vrd_put_row("dims",db_buf);

    }
}

int put_in_comid(SgSymbol *sn)
{ //puts row in table comid for common block with name 'ident':
  //row of table comid: (int id, char *T_ident)
    int id, l;
    char *name, *ident;

    ++id_comid;
    ident = sn->identifier();
    l = strlen(ident);
    name = new char[l + 1];
    strcpy(name, ident);
    comname[id_comid] = name;
    if (id_comid == NCOM)
        ErrMessage("Table of common blocks is full", 0);
    if (!strcmp("NO_NAME_COMMON", ident))
        ident = "";
    sprintf(db_buf, "%d, '%s'", id_comid, ident);
    //vrd_put_row("comid",db_buf);
    return(id_comid);
}

int put_in_comdef()
{ //puts row in table comdef
  //row of table comdef: (int id)
    sprintf(db_buf, "%d", ++id_comdef);
    //vrd_put_row("comdef",db_buf);
    return(id_comdef);
}

void put_in_comdecl(SgSymbol *sn, int pe, int com, int def)
{ //puts row in table comdecl for common with symbol sn
  //row of table comdecl: (int routine_id, int comid-id, int comdef_id)

    sprintf(db_buf, "%d, %d, %d", pe, com, def);
    //vrd_put_row("comdecl",db_buf);

}

void put_in_comvars(int def, SgSymbol *s)
{ //puts row in table comvars for variable s
  //row of table comvars: (int comdef_id, int var)
    sprintf(db_buf, "%d, %d", def, *VAR(s));
    //vrd_put_row("comvars",db_buf);
}

int put_in_operators(SgStatement *stmt)
{//puts row in table operators for statement stmt
 //row of table operators: (int id, int loop, int line)
    int *id;
    sprintf(db_buf, "%d, %d, %d", ++id_operators, IdOfLoops(stmt), stmt->lineNumber());
    //vrd_put_row("operators",db_buf);
    // adding attribute oper_id to stmt
    id = new int;
    *id = id_operators;
    stmt->addAttribute(OPER_ID, (void *)id, sizeof(int));

    return(id_operators);
}

int put_in_calls(SgSymbol *s)
{//puts row in table calls 
 //row of table calls:(int id, int oper, int routine)
    int routine_id;
    routine_id = idOfCalledRoutine(s);//idOfRoutines(s);
    if (!routine_id)
        routine_id = NoBodyRoutine(s);
    if (routine_id)
    {
        sprintf(db_buf, "%d, %d, %d", ++id_calls, id_operators, routine_id);
        //vrd_put_row("calls",db_buf);
        return(id_calls);
    }
    return(0);

    // if(IS_INTRINSIC_FUNC(s) || IS_DUMMY(s))
    //if(IS_DUMMY(s))
    //  return(0);
    // cr = new calls_row;
    //  cr->id = ++id_calls;
    //  cr->oper = id_operators;
    //  cr->symb = s;
    //  return(id_calls);

}

void put_in_arguments(int call, int pos, int expr)
{//puts row in table arguments for i-th argument 
 //row of table calls:(int call, int pos, int expr)
    sprintf(db_buf, "%d, %d, %d", call, pos, expr);
    //vrd_put_row("arguments",db_buf);
    return;
}

int put_in_usage(SgSymbol *s, int mode)
{//puts row in table usage for using variable 's'
 //row of table usage: (int id, int oper, int var, char *mode)    
    if (mode != NUL_)
        sprintf(db_buf, "%d, %d, %d, '%s'", ++id_usage, id_operators, idOfVars(s), text_mode[mode]);
    else   // for arguments of functions
        sprintf(db_buf, "%d, %d, %d, NULL", ++id_usage, id_operators, idOfVars(s));

    //vrd_put_row("usage",db_buf);
    return(id_usage);
}

void put_in_indexes(int use, int ind, int expr)
{//puts row in table indexes
 //row of table indexes: (int use, int ind, int expr)
    sprintf(db_buf, "%d, %d, %d", use, ind, expr);
    //vrd_put_row("indexes",db_buf);
}

void put_in_expr_usage(int expr, int use)
{//puts row in table expr_usage
 //row of table expr_usage: ( int expr, int use)
    sprintf(db_buf, "%d, %d", expr, use);
    //vrd_put_row("expr_usage",db_buf);
}

void put_in_looptree(SgStatement *dost, SgStatement *parent, int tightly)
{//puts row in table looptree for do-loop
 //row of table indexes: (int self, int parent, int tightly)

    sprintf(db_buf, "%d, %d, %d", *LOOP(dost), *LOOP(parent), tightly);
    //vrd_put_row("looptree",db_buf);
    //printf("DO on line %d    in  DO on line %d    tightly as   %d\n", dost->lineNumber(),parent->lineNumber(),tightly);  
}

void put_root_in_looptree(int root)
{//puts row in table looptree for root of tree (header of routine)
    sprintf(db_buf, "%d, NULL, %d", root, 0);
    //vrd_put_row("looptree",db_buf);  
}

void put_in_io(int oper, int mode)
{//puts row in table io for input/output statement
    sprintf(db_buf, "%d, %d", oper, mode);
    //vrd_put_row("io",db_buf);  
}

void put_in_branches(int self, int next, int weight)
{//puts row in table branches
    sprintf(db_buf, "%d,%d,%d", self, next, weight);
    //vrd_put_row("branches",db_buf);  
}

void put_in_analyzed(int scal_dep, int arr_dep, int red_dep, int priv_dep)
{//puts row in table analyzed
    sprintf(db_buf, "%d, %d, %d, %d", scal_dep, arr_dep, red_dep, priv_dep);
    //vrd_put_row("analyzed",db_buf);  
}

void put_in_depends(int loop, char* type, int var, char *redop)
{//puts row in table depends
    sprintf(db_buf, "%d, '%s', %d, '%s'", loop, type, var, redop);
    //vrd_put_row("depends",db_buf); 
}

void put_in_userdir(int oper, int line, char *dir)
{//puts row in table userdir
    sprintf(db_buf, "%d, %d, '%s'", oper, line, dir);
    //vrd_put_row("userdir",db_buf); 
}

int ExprWithPostfix(SgExpression *e)
{
    char *pfix, *te;
    exlist *ele;
    //is the same expression in table expressions ?
    ele = isInTableExpressions(e);
    if (!ele) // not
    {
        //puts row for 'e' in table expressions
        //row of table expressions: (int id,char *text)
        te = UnparseExpr(e);
        sprintf(db_buf, "%d, '%s'", ++id_expressions, te);
        //vrd_put_row("expressions",db_buf);
        ele = AddToExprList(e, id_expressions);
    }
    // is in table postfix ?
    if (ele->flag_p == 0)  // not
    {
        //puts row for 'e' in table postfix if there is postfix record for 'e' 
        //row of table postfix: (int expr, char *pfix) 
        if (pfix = Postfix(e))
        {
            sprintf(db_buf, "%d, '%s'", ele->id, pfix);
            //vrd_put_row("postfix",db_buf);
            ele->flag_p = 1;  // has postfix record
        }
        else
            ele->flag_p = -1; // has not postfix record
    }
    return(ele->id);
}

int ExprWithLinearForm(SgExpression *e)
{
    char  *te;
    exlist *ele;

    //is the same expression in table expressions ?
    ele = isInTableExpressions(e);
    if (!ele) // not
    {
        //puts row for 'e' in table expressions
        //row of table expressions: (int id,char *text)
        te = UnparseExpr(e);
        sprintf(db_buf, "%d, '%s'", ++id_expressions, te);
        //vrd_put_row("expressions",db_buf);
        ele = AddToExprList(e, id_expressions);
    }
    // is in table linexpr ?
    if (ele->flag_l == 0)  // not
    {
        // puts rows for all monoms of linear form (if it is) in table monoms and in table linexpr      
        if (isLinearForm(e))
        {
            LinearForm(e, ele->id);
            ele->flag_l = 1; // has linear form
        }
        else
            ele->flag_l = -1; // has not linear form
    }
    return(ele->id);
}

int Expr(SgExpression *e)
{
    char  *te;

    //puts row for 'e' in table expressions
    //row of table expressions: (int id,char *text)
    te = UnparseExpr(e);
    sprintf(db_buf, "%d, '%s'", ++id_expressions, te);
    //vrd_put_row("expressions",db_buf);
    return(id_expressions);
}


char *Postfix(SgExpression *e)
{
    char *pfix;

    if (!hasPostfix(e))
        return(NULL);
    pfix = PfixRecord(e->thellnd);
    return(pfix);
}

int hasPostfix(SgExpression *e)
{
    int is;

    if (!e || e->variant() == STAR_RANGE)
        return(0);
    if (isSgValueExp(e) || isSgVarRefExp(e) || e->variant() == CONST_REF || (isSgArrayRefExp(e) && !e->lhs()))
        return(1);

    switch (e->variant())
    {
    case(UNARY_ADD_OP):
    case(MINUS_OP):
        return(hasPostfix(e->lhs()));

    case(ADD_OP):
    case(SUBT_OP):
    case(MULT_OP):
    case(DIV_OP):
    case(EXP_OP):
        is = hasPostfix(e->lhs()) && hasPostfix(e->rhs());
        return(is);

    default:
        return(0);
    }
}

int isValueOrVarRef(SgExpression *e)
{ // is integer constant or variable reference ?
  //if(isSgValueExp(e) || isSgVarRefExp(e))
    if (e->variant() == VAR_REF || e->variant() == INT_VAL)
        return(1);
    return(0);
}

int isMonom(SgExpression *e)
{
    int is;
    // is monom: [<integer_constant>] [*] [<variable_reference>]  ?

    if (!e) return(0);

    if (isValueOrVarRef(e))
        return(1);
    if (e->variant() == MULT_OP
        && isValueOrVarRef(e->lhs()) && isValueOrVarRef(e->rhs())
        && e->lhs()->variant() != e->rhs()->variant())
        return(1);
    return(0);
}


int isLinearForm(SgExpression *e)
{//is linear form expression ?

    if (isMonom(e))
        return(1);
    switch (e->variant())
    {
    case(ADD_OP):
        if (isMonom(e->lhs()))
            return(isLinearForm(e->rhs()));
        else if (isMonom(e->rhs()))
            return(isLinearForm(e->lhs()));
        else
            return(0);
    case(SUBT_OP):      if (isMonom(e->rhs()))
        return(isLinearForm(e->lhs()));
                        else
                            return(0);

        //   case(MULT_OP):       return( isMonom(e));                         

    default:             return(0);

    }
}

void LinearForm(SgExpression *e, int id)
{
    if (isMonom(e))
        Monom(e, id);
    switch (e->variant())
    {
    case(ADD_OP):
        if (isMonom(e->lhs()))
        {
            Monom(e->lhs(), id);
            LinearForm(e->rhs(), id);
        }
        else //if(isMonom(e->rhs()))
        {
            Monom(e->rhs(), id);
            LinearForm(e->lhs(), id);
        }
        break;
    case(SUBT_OP):      //if(isMonom(e->rhs()))
    { //MinusMonom(e->rhs(),id);
        LinearForm(e->lhs(), id);
        MinusMonom(e->rhs(), id);
    }
    break;
    default:            break;

    }

}

void Monom(SgExpression *e, int id)
// puts row for for the monom of linear form expression in table monoms
// and in table linexpr
//row of table monoms:  (int monom_id, int coeff, int var_id)
//row of table linexpr: (int expr, int monom_id)
{
    int coeff, var;
    switch (e->variant())
    {
    case(INT_VAL): coeff = (e->thellnd)->entry.ival;
        var = NULL;
        break;
    case(VAR_REF): coeff = 1;
        var = *VAR(e->symbol());
        break;
    case(MULT_OP): if (e->lhs()->variant() == INT_VAL)
    {
        coeff = (e->lhs()->thellnd)->entry.ival;
        var = *VAR(e->rhs()->symbol());
    }
                   else
                   {
                       coeff = (e->rhs()->thellnd)->entry.ival;
                       var = *VAR(e->lhs()->symbol());
                   }
                   break;
    default: break;
    }
    if (var)
        sprintf(db_buf, "%d, %d, %d", ++id_monoms, coeff, var);
    else
        sprintf(db_buf, "%d, %d, NULL", ++id_monoms, coeff, var);

    //vrd_put_row("monoms",db_buf);

    sprintf(db_buf, "%d, %d", id, id_monoms);
    //vrd_put_row("linexpr",db_buf);    
}

void MinusMonom(SgExpression *e, int id)
// puts row for for the (-monom) of linear form expression in table monoms
// and in table linexpr
//row of table monoms:  (int monom_id, int coeff, int var_id)
//row of table linexpr: (int expr, int monom_id)
{
    int coeff, var;
    switch (e->variant())
    {
    case(INT_VAL): coeff = -(e->thellnd)->entry.ival;
        var = NULL;
        break;
    case(VAR_REF): coeff = -1;
        var = *VAR(e->symbol());
        break;
    case(MULT_OP): if (e->lhs()->variant() == INT_VAL)
    {
        coeff = -(e->lhs()->thellnd)->entry.ival;
        var = *VAR(e->rhs()->symbol());
    }
                   else
                   {
                       coeff = -(e->rhs()->thellnd)->entry.ival;
                       var = *VAR(e->lhs()->symbol());
                   }
                   break;
    default: break;
    }
    if (var)
        sprintf(db_buf, "%d, %d, %d", ++id_monoms, coeff, var);
    else
        sprintf(db_buf, "%d, %d, NULL", ++id_monoms, coeff, var);

    //vrd_put_row("monoms",db_buf);

    sprintf(db_buf, "%d, %d", id, id_monoms);
    //vrd_put_row("linexpr",db_buf);    
}

int Rank(SgSymbol *s)
{
    SgArrayType *artype;
    //if(IS_POINTER(s))
    //  return(PointerRank(s));
    artype = isSgArrayType(s->type());
    if (artype)
        return (artype->dimension());
    else
        return (0);
}

char *T_type(SgSymbol *s)
{
    SgType *t;
    SgArrayType *artype;
    char *t_tp = new char[20];
    char *tt = new char[50];
    char *t_len;
    SgExpression *len;

    if (IS_DUMMY(s) && s->variant() == VARIABLE_NAME && ((s->attributes() & EXTERNAL_BIT) || (s->attributes() & INTRINSIC_BIT)))
        return("procedure");
    t = s->type();
    if (!t)
        return("no type"); // ?????
    artype = isSgArrayType(t);
    if (artype)
    {
        t = artype->baseType();
        put_in_dims(s, id_vars, artype);
    }
    len = TypeLengthExpr(t);
    switch (t->variant()) {
    case T_BOOL:    t_tp = "logical"; break;
    case T_INT:     t_tp = "integer"; break;
    case T_FLOAT:   t_tp = "real";    break;
    case T_DOUBLE:  t_tp = "doubleprecision"; break;
    case T_COMPLEX: t_tp = "complex"; break;
    case T_DCOMPLEX:t_tp = "doublecomplex"; break;
    case T_STRING:  t_tp = "character"; break;
    default:        t_tp = "notype";
    }
    if (IS_INTRINSIC_TYPE(t))
        return (t_tp);
    else if (len && len->variant() == INT_VAL) // (isSgValueExp(len) )
    {
        t_len = UnparseExpr(len);
        sprintf(tt, "%s*%s", t_tp, t_len);
        return(tt);
    }
    else
    {
        t_len = UnparseExpr(len);
        sprintf(tt, "%s*(%s)", t_tp, t_len);
        return(tt);
    }
}


int NumericTypeLength(SgType *t)
{
    SgExpression *le;
    SgValueExp *ve;
    if (t->variant() == T_STRING)   return (0);
    if (TYPE_RANGES(t->thetype)) {
        le = t->length();
        if ((ve = isSgValueExp(le)))
            return (ve->intValue());
        else
            return (0);
    }
    if (TYPE_KIND_LEN(t->thetype)) {
        le = t->selector()->lhs();
        if ((ve = isSgValueExp(le)))
            if (t->variant() == T_COMPLEX || t->variant() == T_DCOMPLEX)
                return (2 * ve->intValue());
            else
                return (ve->intValue());
        else
            return (0);
    }
    return(0);
}

SgExpression * TypeLengthExpr(SgType *t)
{
    SgExpression *len;
    SgExpression *selector;
    //if(t->variant() == T_DERIVED_TYPE) return(new SgValueExp(StructureSize(t->symbol())));

    len = TYPE_RANGES(t->thetype) ? t->length() : NULL;

    selector = TYPE_KIND_LEN(t->thetype) ? t->selector() : NULL;
    if (!len && !selector) //the number of bytes is not specified in type declaration statement
        return (new SgValueExp(IntrinsicTypeSize(t)));
    else if (len && !selector)   //INTEGER*2,REAL*8,CHARACTER*(N+1)
        return(Calculate(len));
    else
        return(Calculate(LengthOfKindExpr(t, selector, len))); //specified kind or/and len

}

SgExpression *LengthOfKindExpr(SgType *t, SgExpression *se, SgExpression *le)
{
    switch (t->variant()) {
    case T_INT:
    case T_FLOAT:
    case T_BOOL:
    case T_DOUBLE:
        return(se->lhs());
    case T_COMPLEX:
    case T_DCOMPLEX:
        return(&(*new SgValueExp(2) * (*(se->lhs()))));
    case T_CHAR:
    case T_STRING:
    {   SgExpression *length, *kind;
    if (se->rhs() && se->rhs()->variant() == LENGTH_OP) {
        length = se->rhs()->lhs();
        kind = se->lhs()->lhs();
    }
    else if (se->rhs() && se->rhs()->variant() != LENGTH_OP) {
        length = se->lhs()->lhs();
        kind = se->rhs()->lhs();
    }
    else {
        length = se->lhs();
        kind = NULL;
    }
    length = le ? le : length;
    if (kind)
        return(&(*length * (*kind)));
    //return(Calculate(length)->valueInteger() * Calculate(kind)->valueInteger());
    else
        return(length);
    //return(Calculate(length)->valueInteger());

    /*length = se->rhs() ? (se->rhs()->variant() == LENGTH_OP ? se->rhs()->lhs() : se->lhs()->lhs()) : se->lhs();
    length = le ? le : length;
    if(se->rhs()) // specified KIND and LEN
    return((se->lhs()->lhs()->valueInteger()) * (se->rhs()->lhs()->valueInteger()) ); //kind*len
    else
    return(se->lhs()->valueInteger()); */
    }

    default:
        return(NULL);
    }
}

int IntrinsicTypeSize(SgType *t)
{
    switch (t->variant()) {
    case T_INT:
    case T_BOOL:     return (default_integer_size);
    case T_FLOAT:    return (default_real_size);
    case T_COMPLEX:  return (default_real_size);
    case T_DOUBLE:   return (8);

    case T_DCOMPLEX: return(16);

    case T_STRING:
    case T_CHAR:
        return(1);
    default:
        return(0);
    }
}


SgExpression *LowerBound(SgArrayType *artype, int i)
// lower bound of i-nd dimension of array ar (i= 0,...,Rank(ar)-1)
{
    SgExpression *e;
    SgSubscriptExp *sbe;
    SgValueExp M1(1);
    e = artype->sizeInDim(i);
    if (!e)
    {
        return(NULL);
        //err();
    }
    if ((sbe = isSgSubscriptExp(e)) != NULL) {
        if (sbe->lbound())
            return(sbe->lbound());
        else
            return(new SgValueExp(1));
    }
    else
        return(new SgValueExp(1));  // by default lower bound = 1      
}

SgExpression *UpperBound(SgArrayType *artype, int i)
// upper bound of i-nd dimension of array ar (i= 0,...,Rank(ar)-1)
{
    SgExpression *e;
    SgSubscriptExp *sbe;

    e = artype->sizeInDim(i);
    if (!e)
        return(NULL);
    if ((sbe = isSgSubscriptExp(e)) != NULL) {
        if (sbe->ubound())
            return(sbe->ubound());
        else
            return(NULL);
    }
    //else if(e->variant()==STAR_RANGE)
    //   return(NULL);
    else
        return(e);
    // !!!! test case "*"
}


SgExpression *Calculate(SgExpression *e)
{
    SgExpression *er;
    er = ReplaceParameter(&(e->copy()));
    if (er->isInteger())
        return(new SgValueExp(er->valueInteger()));
    else
        return(e);
}

int ExpCompare(SgExpression *e1, SgExpression *e2)
{//compares two expressions
 // returns 1 if they are textually identical
    if (!e1 && !e2) // both expressions are null
        return(1);
    if (!e1 || !e2) // one of them is null
        return(0);
    if (e1->variant() != e2->variant()) // variants are not equal
        return(0);
    switch (e1->variant()) {
    case INT_VAL:
        return(NODE_IV(e1->thellnd) == NODE_IV(e2->thellnd));
    case FLOAT_VAL:
    case DOUBLE_VAL:
    case BOOL_VAL:
    case CHAR_VAL:
    case STRING_VAL:
        return(!strcmp(NODE_STR(e1->thellnd), NODE_STR(e2->thellnd)));
    case COMPLEX_VAL:
        return(ExpCompare(e1->lhs(), e2->lhs()) && ExpCompare(e1->rhs(), e2->rhs()));
    case CONST_REF:
    case VAR_REF:
        return(e1->symbol() == e2->symbol());
    case ARRAY_REF:
    case FUNC_CALL:
        if (e1->symbol() == e2->symbol())
            return(ExpCompare(e1->lhs(), e2->lhs())); // compares subscript/argument lists
        else
            return(0);
    case EXPR_LIST:
    {SgExpression *el1, *el2;
    for (el1 = e1, el2 = e2; el1&&el2; el1 = el1->rhs(), el2 = el2->rhs())
        if (!ExpCompare(el1->lhs(), el2->lhs()))  // the corresponding elements of lists are not identical
            return(0);
    if (el1 || el2) //one list is shorter than other
        return(0);
    else
        return(1);
    }
    case MINUS_OP:  //unary operations
    case NOT_OP:
    case UNARY_ADD_OP:
        return(ExpCompare(e1->lhs(), e2->lhs())); // compares operands    
    default:
        return(ExpCompare(e1->lhs(), e2->lhs()) && ExpCompare(e1->rhs(), e2->rhs()));
    }
}

int idOfVars(SgSymbol *s)
{
    int *pint;
    pint = VAR(s);
    if (pint)
        return(*pint);
    else
    {
        ErrMessageF("No id for var %s", s->identifier(), cur_st);
        return(0);
    }
}

exlist *isInTableExpressions(SgExpression *e)
{
    exlist *el;
    //return(NULL);
    for (el = Lexp; el; el = el->list)
        if (ExpCompare(e, el->ex))
            return(el);
        else
            continue;
    return(NULL);
}

/*
int isInTableExpressions(SgExpression *e)
{ exlist *el;
for(el=Lexp;el;el=el->list)
if(ExpCompare(e,el->ex) && EXPR(el->ex))
return(EXPR(el->ex)->id);
else
continue;
return(0);
}
*/
void AddAttributeForExpr(SgExpression *e, int id, int flag)
{
    exlist *el;
    el = new exlist;
    el->id = id;
    el->list = Lexp;
    el->ex = e;
    el->flag = flag;
    Lexp = el;
    e->addAttribute(EXPR_ID, (void *)el, sizeof(exlist));
}

exlist *AddToExprList(SgExpression *e, int id)
{
    exlist *el;
    el = new exlist;
    el->id = id;
    el->list = Lexp;
    el->ex = e;
    el->flag_p = 0;
    el->flag_l = 0;
    Lexp = el;
    return(el);
}

int IdOfLoops(SgStatement *stmt)
{
    SgStatement *st;
    for (st = stmt->controlParent(); st != cur_func; st = st->controlParent())
    {
        if (st->variant() == FOR_NODE)
            break;
        continue;
    }
    if (LOOP(st))
        return(*LOOP(st));
    else
        return(0);
}

int RoutineId(SgSymbol *s)
{
    /* if(!strcmp(rname[++n_routines],s->identifier()))
    return(n_routines);
    else
    */

    return(idOfRoutines(s));
}

int idOfCalledRoutine(SgSymbol *s)
{
    int *ir;
    if (!IS_DUMMY(s))
        return(idOfRoutines(s));

    if ((ir = ROUTINE(s)))
        return(*ir);

    ir = new int;
    *ir = ++id_routines;
    // adding the attribute (ROUTINE_ID) to DUMMY symbol
    s->addAttribute(ROUTINE_ID, (void *)ir, sizeof(int));
    return(*ir);
}

int idOfRoutines(SgSymbol *s)
{
    int i;
    for (i = 1; i <= id_routines; i++)
        if (rname[i] && !strcmp(rname[i], s->identifier()))
            return(i);
    return(0);
}

int idOfFiles(char *fname)
{
    int fid;
    fid = isInTableFiles(fname);
    if (!fid)
        fid = put_in_files(fname);
    return(fid);
}

int isInTableFiles(char *fname)
{
    int i;
    for (i = 1; i <= id_files; i++)
        if (!strcmp(nameoffile[i], fname))
            return(i);
    return(0);
}


int isInTableComid(SgSymbol *s)
{
    int i;
    for (i = 1; i <= id_comid; i++)
        if (!strcmp(comname[i], s->identifier()))
            return(i);
    return(0);
}

int NoBodyRoutine(SgSymbol *sf)
{
    char *func_name;
    int l;

    l = strlen(sf->identifier());
    func_name = new char[l + 1];
    strcpy(func_name, sf->identifier());
    rname[++id_routines] = func_name;
    if (id_routines == NRTN)
    {
        ErrMessage("Table of routines is full", 0);
        exit(1);
    }
    if ((IS_DUMMY(sf) && sf->variant() == VARIABLE_NAME && ((sf->attributes() & EXTERNAL_BIT) || (sf->attributes() & INTRINSIC_BIT))))
        put_in_routines_nobody(id_routines, rname[id_routines], sf->scope()); // routine is dummy argument

    else
        put_in_routines_nobody(id_routines, rname[id_routines], NULL);
    return(id_routines);
}

void  Add_In_Table_Routines(int num_routines)
{// adds in table "routines" all the nobody routines that are called in program
    int i;

    for (i = num_routines + 1; i <= id_routines; i++)
        put_in_routines_nobody(i, rname[i], NULL);
}
