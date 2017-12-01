/**************************************************************\
* Fortran DVM                                                  * 
*                                                              *
*   Generating statements and restructuring program for        *
*            Debugger and Performance Analyzer                 *
\**************************************************************/

#include "dvm.h"

/***************************************************************\
 *         Debugging mode functions                            *
\***************************************************************/ 
void D_AddToDoList (int Nloop, int Nline, SgLabel *lab, SgSymbol *var)
{D_do_list *doel;
//adding element to D_do_list correcponding current loop
  if(!cur_do) { //list is empty
     cur_do = new D_do_list;
     cur_do->No = Nloop;
     cur_do->num_line = Nline;
     cur_do->end_lab = lab;
     cur_do->do_var = var;
     cur_do->next = NULL;
  } else if (!free_list) {  //list of free elements is empty, creating new element
     doel =  new D_do_list;
     doel->No = Nloop;
     doel->num_line = Nline;
     doel->end_lab = lab;
     doel->do_var = var;
     doel->next = cur_do;
     cur_do = doel;
  }
    else {  // taking free element
     doel = free_list;
     free_list = free_list->next;
     doel->No = Nloop;
     doel->num_line = Nline;
     doel->end_lab = lab;
     doel->do_var = var;
     doel->next = cur_do;
     cur_do = doel;
   }
}

void D_DelFromDoList ()
{D_do_list *doel;
   if(!cur_do)  //list is empty
     return;
   doel = cur_do;
   cur_do = cur_do->next;
   doel->next = free_list;
   free_list = doel; 
}

void ArrayRegistration ()
{ symb_list *sl;
  SgSymbol *ar;
  int count;
  count = 0;
  registration_array = CreateRegistrationArraySymbol();
  for(sl=registration; sl; sl=sl->next) {
     ar = sl->symb;
     if(IN_MODULE){
       int *index = new int;
       count_reg++;
       *index = count_reg; 
       ar->addAttribute(DEBUG_AR_INDEX,(void*) index, sizeof(int));
     }
     Registrate_Ar(ar); 

  }      
}

void AllocatableArrayRegistration (SgStatement *stmt)
{SgExpression *alce,*al;
 //SgSymbol *ar;
 
 LINE_NUMBER_AFTER(stmt,stmt);

 for(al=stmt->expr(0); al; al=al->rhs()) {
   alce = al->lhs(); //allocation
   if(isSgRecordRefExp(alce)) 
     alce = RightMostField(alce);
   //ar = alce->symbol();
   Registrate_Allocatable(alce,stmt);
 }
}

void Registrate_Ar(SgSymbol *ar)
{ SgExpression *ehead, *size_array;
  SgStatement *if_st,*savest;   
  int ia,idvm;
  idvm=ndvm;
  savest = where; 
  ia = ar->attributes(); 
  if(!VarType(ar) || (ia & INHERIT_BIT) || (ia & HEAP_BIT) || IS_POINTER(ar) || IS_DUMMY(ar) || (ia & ALLOCATABLE_BIT) || (ia & POINTER_BIT) || (IN_COMMON(ar) && (ar->scope()->variant() != PROG_HEDR)) ||  (!strcmp(ar->identifier(),"heap")) )
       return;
  if(ALIGN_RULE_INDEX(ar))  return;  

  if(ORIGINAL_SYMBOL(ar)->scope()->variant() == MODULE_STMT) {
    if_st = doIfThenConstrWithArElem (registration_array,DEBUG_INDEX(ar));
    where = if_st->lexNext();  // reffer to ENDIF statement   
  }
  ehead = HEADER(ar) ?  GetAddresDVM(HeaderRefInd(ar,1)) : GetAddresMem(FirstArrayElement(ar));
  size_array = doSizeArray(ar, NULL); 
  InsertNewStatementBefore( D_RegistrateArray(Rank(ar),VarType(ar), ehead, size_array,
 new SgArrayRefExp(*ar)),where);
  SET_DVM(idvm);
  where = savest;
  return;
}

void Registrate_Allocatable(SgExpression *alce, SgStatement *stmt)
{SgSymbol *ar;
 SgExpression *ehead, *size_array;
 SgStatement *savest; 
 int idvm;

 idvm=ndvm;
 savest = where;  
 ar = alce->symbol();

 if(VarType(ar)) {
   ehead = GetAddresMem(FirstArrayElement(ar));
   size_array = dvm_array_ref();     // SizeArray reference
   InsertNewStatementAfter( D_RegistrateArray(Rank(ar),VarType(ar), ehead, size_array, new SgArrayRefExp(*ar)),cur_st,stmt->controlParent());
   where = cur_st;
   doSizeAllocArray(ar,alce,stmt,RTS1);
   cur_st=cur_st->lexNext(); // call registration function drarr()
 }
 SET_DVM(idvm);
 where = savest;
 return;
}

void AllocArrayRegistration( SgStatement *stmt)
{SgSymbol *p;
 SgStatement *stat;
 SgExpression *size_array,*array_adr,*desc,*heap;
 int rank,type,idvm;
 stat = where; //store value of  where
 idvm = ndvm;
 where = stmt;
 p = stmt->expr(0)->symbol();
 if(!IS_POINTER(p))
    return;
 
 if(!stmt->expr(1)->lhs()) {// empty argument list of allocate function call
      err("Wrong argument list of ALLOCATE function call", 262, stmt);
      return;
  }
 if(!stmt->expr(1)->lhs()->rhs()) {// argument list length < 2
        //err("Wrong argument list of ALLOCATE function call", 262, stmt);
      return;
  }
 heap =  stmt->expr(1)->lhs()->rhs()->lhs(); //heap array reference
 if(!heap  || !isSgArrayRefExp(heap) || heap->lhs())
    return;
 rank =  PointerRank(p);

 desc = stmt->expr(1)->lhs()->lhs(); //descriptor array reference
 array_adr =  new SgArrayRefExp(*heap->symbol(),*(stmt->expr(0)));
 size_array = ReverseDim(desc,rank); 
 type = TestType(PointerType(p));
 if(type) {
    InsertNewStatementAfter(D_RegistrateArray(rank, type, GetAddresMem(array_adr),size_array,stmt->expr(0) ) ,where,where->controlParent());
    LINE_NUMBER_AFTER(where,where);
 } 
 SET_DVM(idvm);
 where = stat; //restore where
}


void RegistrateAllocArray( stmt_list *alloc_st)
{SgSymbol *p,*heap;
 SgStatement *stmt,*stat;
 stmt_list *stl;
 SgExpression *size_array,*array_adr,*desc;
 int rank,type,idvm;
 stat = where; //store value of  where
 SET_DVM(ndvm);
 idvm = ndvm = maxdvm+1;
 for (stl=alloc_st; stl; stl=stl->next) {
    stmt = stl->st;
    where = stmt;
    p = stmt->expr(0)->symbol();
    if(!IS_POINTER(p))
      continue;
    heap = HeapForPointer(p);
    if(!heap)
      continue;
    rank =  PointerRank(p);
    desc = stmt->expr(1)->lhs()->lhs(); //descriptor array reference
    array_adr =  new SgArrayRefExp(*heap,*(stmt->expr(0)));
    size_array = ReverseDim(desc,rank); 
    type = TestType(PointerType(p));
    if(type)
      InsertNewStatementAfter(D_RegistrateArray(rank, type, GetAddresMem(array_adr),size_array,stmt->expr(0) ) ,where,where->controlParent());
    SET_DVM(idvm);
 }
 where = stat; //restore where
}


int isDoVar(SgSymbol *s)
{
 return(SYMB_ATTR(s->thesymb) & DO_VAR_BIT); 
}

void SetDoVar(SgSymbol *s)
{
 SYMB_ATTR(s->thesymb)=SYMB_ATTR(s->thesymb) | DO_VAR_BIT;
}

void OffDoVar(SgSymbol *s)
{
 SYMB_ATTR(s->thesymb)=SYMB_ATTR(s->thesymb) & (~ DO_VAR_BIT);
}

void D_ReplaceDoLab(SgLabel *lab, SgLabel *newlab)
{D_do_list *dol;
 dol = cur_do;
 while(LABEL_STMTNO(dol->end_lab->thelabel) == LABEL_STMTNO(lab->thelabel)) {
    dol->end_lab = newlab;
    dol = dol->next;
 }     
}

void  DebugLoop(SgStatement *stmt)
{int No,ino;
 SetDoVar(stmt->symbol());
 LINE_NUMBER_BEFORE(stmt,stmt);
 DebugVarArrayRef(stmt->expr(0),stmt);
 DebugVarArrayRef(stmt->expr(1),stmt); 
 No =++Dloop_No; 
 AddAttrLoopNumber(No,stmt);
 ino = ndvm;
 doAssignStmtBefore(new SgValueExp(No),stmt); /*FREE_DVM(1);*/

 InsertNewStatementBefore(D_Begsl(ino),stmt); 

 if(dbg_if_regim) {
   SgStatement *stnew,*if_stmt;
   stnew = D_Iter(stmt->symbol(),LoopVarType(stmt->symbol(),stmt));
   if_stmt = new SgLogIfStmt(*DebugIfCondition(),*stnew);
   InsertNewStatementAfter(if_stmt,stmt,stmt);
   (if_stmt->lexNext()->lexNext()) -> extractStmt(); //extract ENDIF 
 } else
   InsertNewStatementAfter(D_Iter(stmt->symbol(),LoopVarType(stmt->symbol(),stmt)),stmt,stmt);

 /*
 SetDoVar(stmt->symbol());
 InsertNewStatementBefore(D_Lnumb(stmt->lineNumber()),stmt);
 No =++Dloop_No; 
 AddAttrLoopNumber(No,stmt);
 InsertNewStatementBefore(D_Begsl(No),stmt); 
 InsertNewStatementAfter(D_Iter(stmt->symbol()),stmt,stmt);
 */

 /**
 // generating Logical IF statement:
       // begin_lab  IF (dosl(No,Init,Last,Step) .EQ. 0) GO TO end_lab
       // and inserting it before  loop 
       stn = stmt->lexPrev();
       LINE_NUMBER_AFTER(stmt,stn);
       begin_lab = GetLabel();
       stn->lexNext()-> setLabel(*begin_lab); 
       end_lab   = GetLabel();
       dopl = (dvm_debug && dbg_if_regim) ? doPLmb(iplp) : doLoop(iplp);
       if_stmt = new SgLogIfStmt(SgEqOp(*dopl , c0), *new SgGotoStmt(*end_lab));
 
          cur_st->insertStmtAfter(*if_stmt);
     
          (if_stmt->lexNext()->lexNext()) -> extractStmt(); //extract ENDIF
                                                            // (error Sage)
 **/      
 if(dbg_if_regim)  
 {SgStatement *stwhile;
  SgForStmt *stdo;
 int iout;
 stdo = (SgForStmt *) stmt;
 iout=ndvm; 
 doAssignStmtBefore(stdo->start(),stmt);
 doAssignStmtBefore(stdo->end(), stmt);
 doAssignStmtBefore((stdo->step()) ? stdo->step() : new SgValueExp(1),stmt);
 stwhile = new SgWhileStmt(WHILE_NODE);
 stwhile->setExpression(0,SgEqOp(*doSL(ino,iout) , *new SgValueExp(1)) );//0->1
 stmt->insertStmtBefore(*stwhile); 
 stdo->setStart(*DVM000(iout));   
 stdo->setEnd(*DVM000(iout+1));   
 }  
  
}

void  DebugTaskRegion(SgStatement *stmt)
{int ino;
 taskreg_No =++Dloop_No;
 //AddAttrLoopNumber(No,stmt);
 LINE_NUMBER_AFTER(stmt,stmt); 
 ino = ndvm; 
 doAssignStmtAfter(new SgValueExp(taskreg_No)); FREE_DVM(1);
 InsertNewStatementAfter(D_Begtr(ino),cur_st,stmt->controlParent()); 
}

void CloseTaskRegion(SgStatement *tr_st,SgStatement *stmt)
{int ino;
 if(!tr_st) return;
 ino = ndvm;
 LINE_NUMBER_AFTER(stmt,stmt); 
 doAssignStmtAfter(new SgValueExp(taskreg_No)); 
 doAssignStmtAfter(new SgValueExp(tr_st->lineNumber()));
 InsertNewStatementAfter( D_Endl(ino,ino+1),cur_st,stmt->controlParent()); 
}

void  DebugParLoop(SgStatement *stmt,int rank, int iinit)
{
 pardo_No = ++Dloop_No;
 LINE_NUMBER_AFTER_WITH_CP(par_do,stmt,par_do->controlParent());
   
 doAssignStmtAfter(new SgValueExp(pardo_No)); 
 FREE_DVM(1); 
 InsertNewStatementAfter(D_Begpl(ndvm,rank,iinit),cur_st,cur_st->controlParent());
           
}

SgStatement *CloseLoop(SgStatement *stmt)
{//generates and insertes debugging statements for closing all sequential loops of nest:
 // call dendl(...)
 //stmt is last statement of loop nest (DO statements with the same label)
 //returns last statement of outer most sequential loop  of resturtured loop nest
 SgStatement *stat, *parent, *lst, *dst, *est;
 //SgForStmt *do_st;
 int No,Ni,ino;

 parent=stmt->controlParent();
 cur_st = lst = stmt;
 if(parent->symbol())
   OffDoVar(parent->symbol());
 if(parent->variant()==WHILE_NODE) {
   if(stmt->lineNumber()) {
     LINE_NUMBER_AFTER_WITH_CP(stmt,cur_st,parent->controlParent());
   }
   seq_loop_nest=1;
   stat = new SgStatement(CONT_STAT);
   InsertNewStatementAfter(stat,cur_st,parent->controlParent());
 }
 else if((No=LoopNumber(parent)) != 0){
   if(stmt->lineNumber()) {
     LINE_NUMBER_AFTER_WITH_CP(stmt,cur_st,parent->controlParent());
           //InsertNewStatementAfter(D_Lnumb(stmt->lineNumber()),cur_st,parent->controlParent());
   }
   seq_loop_nest=1;
   ino = ndvm;
   stat = D_Endl(ino,ino+1);
   dst = cur_st;
   InsertNewStatementAfter(stat,cur_st,parent->controlParent());
   doAssignStmtBefore(new SgValueExp(No),cur_st); 
   doAssignStmtBefore(new SgValueExp(parent->lineNumber()),cur_st);
   dst = dst->lexNext(); 
   est = NULL;
   if( perf_analysis && (Ni = IntervalNumber(parent)) != 0){
     close_loop_interval = close_loop_interval - 1;
     est = cur_st;
     InsertNewStatementAfter(St_Enloop(ino+2,ino+1),cur_st,parent->controlParent());
     doAssignStmtBefore(new SgValueExp(Ni),cur_st);
     est = est->lexNext(); 
        //InsertNewStatementAfter(St_Enloop(Ni,parent->lineNumber()),cur_st,parent->controlParent());
   }
   SET_DVM(ino);
       //ReplaceGoToLabelInsideLoop(parent,lst,lab_after);
   ReplaceGoToInsideLoop(parent,lst,dst,est);

   if(dbg_if_regim){
     SgWhileStmt *stwhile;
     stwhile=(SgWhileStmt *) parent->lexPrev();
     parent->extractStmt();
     stwhile->replaceBody(*parent);
     //cur_st=stmt->lexNext(); //ENDDO
     lst=stmt->lexNext(); //ENDDO
     parent=stwhile;
   }  
 }
 if(!stmt->label()) //DO construct without label
   return(lst);
 //looking through the loop nest with the same label
 parent = parent->controlParent();
 while((parent->variant()==FOR_NODE || parent->variant()==WHILE_NODE) && BIF_LABEL_USE(parent->thebif)  && ( LABEL_STMTNO(BIF_LABEL_USE(parent->thebif))==LABEL_STMTNO(stmt->label()->thelabel)))
//while((do_st=isSgForStmt(parent)) && do_st->endOfLoop() && ( LABEL_STMTNO(do_st->endOfLoop()->thelabel)==LABEL_STMTNO(stmt->label()->thelabel)))
 { 
   if(parent->variant()==WHILE_NODE) {
     seq_loop_nest=1;
     cur_st=ReplaceDoLabel(cur_st,GetLabel());
     lst = cur_st;
     stat = new SgStatement(CONT_STAT);
     InsertNewStatementAfter(stat,cur_st,parent->controlParent());
     parent = parent->controlParent();
     continue;
   }
   else if((No=LoopNumber(parent)) != 0){
     seq_loop_nest=1;
     OffDoVar(parent->symbol());
     ReplaceDoLabel(cur_st,GetLabel());
     lst = cur_st->lexNext();
     ino = ndvm;
     stat = D_Endl(ino,ino+1);
     dst = lst;
     InsertNewStatementAfter(stat,cur_st->lexNext(),parent->controlParent());
     doAssignStmtBefore(new SgValueExp(No),cur_st); 
     doAssignStmtBefore(new SgValueExp(parent->lineNumber()),cur_st);
     dst = dst->lexNext();
     /*
     stat = D_Endl(No,parent->lineNumber());
     InsertNewStatementAfter(stat,cur_st->lexNext(),parent->controlParent());
     */
     est = NULL;
     if(perf_analysis && (Ni=IntervalNumber(parent)) != 0){
       close_loop_interval = close_loop_interval - 1;
       est = cur_st; 
       InsertNewStatementAfter(St_Enloop(ino+2,ino+1),cur_st,parent->controlParent());
       doAssignStmtBefore(new SgValueExp(Ni),cur_st);
       est = est->lexNext(); 
     }
     SET_DVM(ino);
     ReplaceGoToInsideLoop(parent,lst,dst,est);

   }
   else
     break;

   if(dbg_if_regim){
     SgWhileStmt *stwhile;
     stwhile=(SgWhileStmt *) parent->lexPrev();
     parent->extractStmt();
     stwhile->replaceBody(*parent);
     //cur_st=stmt->lexNext(); //ENDDO
     lst=stmt->lexNext(); //ENDDO
     parent=stwhile;
   }  
   parent = parent->controlParent();
 }

 /*
 for(parent = parent->controlParent();
  ((do_st=isSgForStmt(parent)) && LABEL_STMTNO(do_st->endOfLoop()->thelabel)==LABEL_STMTNO(stmt->label()->thelabel));
                  parent = parent->controlParent()) {
   OffDoVar(parent->symbol());
   if(No=LoopNumber(parent)){
     ReplaceDoLabel(cur_st,GetLabel());
     stat = D_Endl(No,parent->lineNumber());
     InsertNewStatementAfter(stat,cur_st->lexNext(),parent->controlParent());
   }
 } 
 */ 
 
 return (lst); 
}

void FreeDoList()
{int Numlab;
 Numlab =LABEL_STMTNO(cur_do->end_lab->thelabel);
 while(cur_do && LABEL_STMTNO(cur_do->end_lab->thelabel) == Numlab)
   D_DelFromDoList ();   
}

void OpenParLoop(SgStatement *dost)
{SgStatement *st;
 st = cur_st;//save cur_st
 SetDoVar(dost->symbol());
 InsertNewStatementAfter(D_Iter(dost->symbol(),LoopVarType(dost->symbol(),dost)),dost,dost);
 cur_st = st; //resave cur_st
}

void OpenParLoop_Inter(SgStatement *dost, int ind, int indtp, SgSymbol *do_var[],int ndo)
{SgStatement *st;
 int i;
 st = cur_st;//save cur_st
 cur_st = dost;

 if(dbg_if_regim) {
   SgStatement *stnew;
   stnew = CreateIfThenConstr(DebugIfCondition(),D_Iter_I(ind,indtp));
   InsertNewStatementAfter(stnew,dost,dost);
   for(i=0; i<ndo; i++)
     doAssignTo_After(DVM000(ind+i),GetAddres(do_var[i]));
   cur_st = st; //resave cur_st
   return;
 } 

 for(i=0; i<ndo; i++)
   doAssignTo_After(DVM000(ind+i),GetAddres(do_var[i]));
 InsertNewStatementAfter(D_Iter_I(ind,indtp),cur_st,dost);
 
 cur_st = st; //resave cur_st
}

void CloseParLoop(SgStatement *dostmt,SgStatement *stmt,SgStatement *end_stmt)
{SgStatement *st;
 SgForStmt *do_st;
 SgLabel *do_lab;
 int ino;
 int end_line_num = end_stmt->lineNumber();
 if (end_line_num)
 {  
    LINE_NUMBER_AFTER_WITH_CP(end_stmt, stmt, par_do->controlParent());
 }
 ino = ndvm;
 InsertNewStatementAfter( D_Endl(ino,ino+1),cur_st,par_do->controlParent());
 doAssignStmtBefore(new SgValueExp(pardo_No),cur_st); 
 doAssignStmtBefore(new SgValueExp(par_do->lineNumber()),cur_st);  FREE_DVM(2);

   //InsertNewStatementAfter( D_Endl(pardo_No,par_do->lineNumber()),cur_st,par_do->controlParent());

 //InsertNewStatementAfter( D_Endl(pardo_No,par_do->lineNumber()),stmt,stmt->controlParent());
 OffDoVar(dostmt->symbol());
 do_lab=((SgForStmt *)dostmt)->endOfLoop();
 if(!do_lab) //DO statement 'dostmt' without label
     return;
 //looking through the loop nest with the same label
 for(st = dostmt->controlParent();
  ((do_st=isSgForStmt(st)) && do_st->endOfLoop() && LABEL_STMTNO(do_st->endOfLoop()->thelabel) == LABEL_STMTNO(do_lab->thelabel));
                  st = st->controlParent()) 
   OffDoVar(st->symbol());
 //DeleteGoToFromList(par_do);
}

void  CloseDoInParLoop(SgStatement *end_stmt)
{ //on debug regim end_stmt may not be logical IF 
  SgStatement *lst; 
  if(LoopNumber(end_stmt->controlParent()) || end_stmt->controlParent()->variant()==WHILE_NODE) {
                    //most inner loop in parallel loop nest is not parallel
    seq_loop_nest=0;
    lst=CloseLoop(end_stmt); //close all inner non-parallel loops
    //ReplaceDoNestLabel_Above(cur_st,cur_st->lexPrev()->controlParent(),GetLabel());
    if(seq_loop_nest)
      ReplaceParDoNestLabel(cur_st,lst->controlParent(),GetLabel());
                       //replace label and insert CONTINUE with new label for parallel nest
    cur_st = cur_st->lexNext(); //last inserted statement == last statement of parallel nest
  }  
}

void AddAttrLoopNumber(int No,SgStatement *stmt)
{int *loop_No = new int;
 *loop_No = No;
 stmt->addAttribute(LOOP_NUMBER, (void*) loop_No, sizeof(int));
}

int LoopNumber(SgStatement *stmt)
{int *no;
 no=(int*)(stmt)->attributeValue(0,LOOP_NUMBER);
 if(no)
   return(*no);
 else
   return(0);
}

int hasGoToIn(SgStatement *parent,SgLabel *lab_after)
{ //stmt_list *gotol;

 for (; goto_list && goto_list->st->lineNumber() > parent->lineNumber() ; goto_list = delFromStmtList(goto_list))
   if( ToThisLabel(goto_list->st,lab_after))
     return(1);
 return(0);
}

int ToThisLabel(SgStatement *gost, SgLabel *lab_after)
{
  return (LABEL_STMTNO(((SgGotoStmt *)gost)->branchLabel()->thelabel) == LABEL_STMTNO(lab_after->thelabel) );
}

/*
void  ReplaceGoToLabelInsideLoop(SgStatement *parent,SgLabel *lab_after,SgLabel *new_lab)

{ for (; goto_list && goto_list->st->lineNumber() > parent->lineNumber() ; goto_list = delFromStmtList(goto_list))
   if( ToThisLabel(goto_list->st,lab_after))      
     NODE_LABEL(goto_list->st->expr(2)->thellnd)= new_lab->thelabel;
                                                   //replace the label in GOTO statement
}
*/

void  ReplaceGoToLabelInsideLoop(SgStatement *parent,SgStatement *lst, SgLabel *lab_after)
{ printf("replace label\n");
 if(lab_after && hasGoToIn(parent,lab_after)){
 SgLabel *new_lab;
 new_lab = GetLabel();  
 (lst->lexNext())->setLabel(*new_lab);
 for (; goto_list && goto_list->st->lineNumber() > parent->lineNumber() ; goto_list = delFromStmtList(goto_list))
   if( ToThisLabel(goto_list->st,lab_after))      
     NODE_LABEL(goto_list->st->expr(2)->thellnd)= new_lab->thelabel;
                                                   //replace the label in GOTO statement
 }
}

void  ReplaceGoToInsideLoop(SgStatement *dost,SgStatement *endst, SgStatement *dst, SgStatement *est)
{ //dost - do-statement, endst - last statement of do-loop
 stmt_list *gol, *prevl;
 SgLabel *golab;
 int branch_line_num; //line number of statement to that goto points
 
 for (gol= goto_list, prevl = NULL; gol && gol->st->lineNumber() > dost->lineNumber() ; gol = gol->next)  
 { 
   if(gol->st->variant() == ARITHIF_NODE)
   {   ReplaceArithIF(gol); goto DELETE_; }
   if(gol->st->variant() == COMGOTO_NODE)
   {   ReplaceComputedGoTo(gol); goto DELETE_; }

   if(gol->st->variant() == GOTO_NODE)
   {
      golab=((SgGotoStmt *)(gol->st))->branchLabel();      
      branch_line_num=LineNumberOfStmtWithLabel(golab);
   }   else
      branch_line_num = 0;   //for case gol->st is RETURN or EXIT
   if(branch_line_num <= dost->lineNumber() || branch_line_num > endst->lineNumber()) //label outside loop
   { //inserting statements for end of loop (call of dendl,eloop) before goto 
     InsertStmtsBeforeGoTo(gol->st,dst,est);
     if(gol->st->variant()!=EXIT_STMT)
     { prevl = gol;
       continue;
     }
   }
DELETE_:
    {//deleting current element (gol) from goto_list
     if(prevl)
       prevl->next = gol->next;
     else
       goto_list = goto_list->next; 
    }
 }  
}

void AddDebugGotoAttribute(SgStatement *gotost,SgStatement *lnumst)
{  SgStatement **dbgst = new (SgStatement *);
    *dbgst = lnumst;
    gotost->addAttribute(DEBUG_GOTO, (void *) dbgst, sizeof(SgStatement *)); 
} 


void InsertStmtsBeforeGoTo(SgStatement *gotost, SgStatement *dst, SgStatement *est)
{SgStatement *lnumst, *save;
 SgStatement **st;
 save=cur_st;
 if(!(st=DEBUG_STMTS_FOR_GOTO(gotost)))  //goto has not attribute (LINE_NUMBER is not yet inserted )
 {  
    LINE_NUMBER_STL_BEFORE(lnumst,gotost,gotost);
    AddDebugGotoAttribute(gotost,lnumst); 
    cur_st = lnumst;
 } else
    cur_st = *st;

 if(dst)
 {  InsertNewStatementAfter( &(dst->copy()),cur_st,cur_st->controlParent());
    InsertNewStatementAfter( &(dst->lexNext()->copy()),cur_st,cur_st->controlParent());
    InsertNewStatementAfter( &(dst->lexNext()->lexNext()->copy()),cur_st,cur_st->controlParent());
 }  
 if(est)
 {  InsertNewStatementAfter( &(est->copy()),cur_st,cur_st->controlParent());
    InsertNewStatementAfter( &(est->lexNext()->copy()),cur_st,cur_st->controlParent());
    if(!dst)
      InsertNewStatementAfter( &(est->lexNext()->lexNext()->copy()),cur_st,cur_st->controlParent());
 } 
 *DEBUG_STMTS_FOR_GOTO(gotost) = cur_st;
 cur_st = save;
} 

SgStatement *StmtWithLabel(SgLabel *lab)
{return (BfndMapping(LABEL_BODY(lab->thelabel)));
}

int LineNumberOfStmtWithLabel(SgLabel *lab)
{return (BIF_LINE(LABEL_BODY(lab->thelabel)));
}

void DeleteGoToFromList(SgStatement *stmt)
{
 for(; goto_list && goto_list->st->lineNumber() > stmt->lineNumber() ; goto_list = delFromStmtList(goto_list)) //deleting from list goto statements appearing inside parallel loop
   ;
}
/***************************************************************\
 *         Performance analyzing  mode functions               *
\***************************************************************/                        
int OpenInterval(SgStatement *stmt)
{
  interval_list *fr = new interval_list;
  fr->prev = NULL;
  fr->No = ++nfrag;
  fr->begin_st = stmt;
  if(!St_frag) 
    St_frag = fr;
  else {
    fr->prev = St_frag;
    St_frag = fr;
  } 
  return (nfrag);
}

int CloseInterval()
{int nline;
  if(!St_frag) 
    return(0); 
  //DeleteGoToFromList( St_frag->begin_st);
  nline = St_frag->begin_st->lineNumber();
  St_frag = St_frag->prev;
  return (nline);
  
}

void OverLoopAnalyse(SgStatement *func)
{SgStatement *st;
//St_loop_first = NULL;
//St_loop_last  = NULL;
  for(st=par_do->controlParent(); st!=func; st=st->controlParent()) {
    if(st->variant() == FOR_NODE || st->variant() == WHILE_NODE )
       SeqLoopBegin(st);
    else
       continue;   
  }
  //St_loop_first->prev = St_frag;
  //St_frag = St_loop_last;
  //close_loop_interval = 1;
}

void   FormLoopIntList(SgStatement *st)
{
  interval_list *fr = new interval_list;
  fr->prev = NULL;
  fr->No = ++nfrag;
  fr->begin_st = st;
  if(!St_loop_last){ 
    St_loop_last  = fr;
    St_loop_first = fr;
  }
  else {
     St_loop_first->prev = fr;
     St_loop_first = fr;
  } 
}

int IntervalNumber(SgStatement *stmt)
{int *no;
 no=(int*)(stmt)->attributeValue(0,LOOP_INTERVAL_NUMBER);
 if(no)
   return(*no);
 else
   return(0);
}

void   SeqLoopBegin(SgStatement *st)
{int ind;
  if( !IntervalNumber(st)){
     AddAttrIntervalNumber(st);
     close_loop_interval = close_loop_interval + 1;
     LINE_NUMBER_BEFORE(st,st);
     ind = ndvm; doAssignStmtBefore(new SgValueExp(nfrag),st);
     InsertNewStatementBefore(St_Bsloop(ind),st);
     FREE_DVM(1);
  }   
}

void AddAttrIntervalNumber(SgStatement *stmt)
{int *int_No = new int;
 *int_No = ++nfrag;
 stmt->addAttribute(LOOP_INTERVAL_NUMBER, (void*) int_No, sizeof(int));
}

SgStatement *SeqLoopEnd(SgStatement *end_stmt,SgStatement *stmt)
{int Ni,ind;
 SgStatement *parent,*lst, *est; 
 //SgLabel *lab_after;
  parent = end_stmt->controlParent();
  cur_st = lst = stmt; 
  //lab_after =  stmt->lexNext()->lineNumber() ? stmt->lexNext()->label() :  stmt->lexNext()->lexNext()->label(); //there is (not) inserted CONTINUE statement by ReplaceDoNestLabel_Above
  if( (Ni = IntervalNumber(parent)) != 0){
    close_loop_interval = close_loop_interval - 1;
    ind = ndvm;
    est = cur_st;
    InsertNewStatementAfter(St_Enloop(ind,ind+1),stmt,parent->controlParent());
    doAssignStmtBefore(new SgValueExp(Ni),cur_st);
    doAssignStmtBefore(new SgValueExp(parent->lineNumber()),cur_st);
    est = est->lexNext();
    FREE_DVM(2);
    //ReplaceGoToLabelInsideLoop(parent,lst,lab_after);
    ReplaceGoToInsideLoop(parent,end_stmt,NULL,est);   
  }
 else
   InsertNewStatementAfter(new SgStatement(CONT_STAT),stmt,parent->controlParent());

 if(!end_stmt->label()) // ENDDO is end of DO constuct
   return(lst);
 parent = parent->controlParent();
 while((parent->variant()==FOR_NODE || parent->variant()==WHILE_NODE)
    && BIF_LABEL_USE(parent->thebif)
    && ( LABEL_STMTNO(BIF_LABEL_USE(parent->thebif))==LABEL_STMTNO(end_stmt->label()->thelabel))) {

   if(parent->variant()==WHILE_NODE) {
     cur_st=ReplaceDoLabel(cur_st,GetLabel());
     lst = cur_st;
     InsertNewStatementAfter(new SgStatement(CONT_STAT),cur_st,parent->controlParent());
     parent = parent->controlParent();
     continue;
   }
  
   else if((Ni=IntervalNumber(parent)) != 0){
     close_loop_interval = close_loop_interval - 1;
     ReplaceDoLabel(cur_st,GetLabel());
     lst = cur_st->lexNext();
     ind = ndvm;
     est = lst;
     InsertNewStatementAfter(St_Enloop(ind,ind+1),cur_st->lexNext(), parent->controlParent());
     doAssignStmtBefore(new SgValueExp(Ni),cur_st);
     doAssignStmtBefore(new SgValueExp(parent->lineNumber()),cur_st);
     est = est->lexNext();
     FREE_DVM(2);
     ReplaceGoToInsideLoop(parent,lst,NULL,est);
   }
   else
     break;
  parent = parent->controlParent();
 }
 return (lst);
}

SgExpression *Value(SgExpression *e)
{int val = FICT_INT;
 return(e ? e : new SgValueExp(val));
}

SgExpression *Value_F95(SgExpression *e)
{
 if(!e)
    return(ConstRef_F95(FICT_INT)); 
 else if(e && e->variant()==INT_VAL)  
    return(ConstRef_F95(e->valueInteger()));
 else
    return(TypeFunction(SgTypeInt(),e,len_DvmType ? new SgValueExp(len_DvmType) : NULL));   
 
}

void  SeqLoopEndInParLoop(SgStatement *end_stmt,SgStatement *stmt)
{ // closing sequential loop intervals in parallel loop nest
  //and restructuring loop nest
  SgStatement *lst; 
  if(IntervalNumber(end_stmt->controlParent()) || end_stmt->controlParent()->variant()==WHILE_NODE) {
                    //most inner loop in parallel loop nest is not parallel
    lst=SeqLoopEnd(end_stmt,stmt); //close all inner non-parallel loop intervals
    ReplaceDoNestLabel_Above(cur_st,lst->controlParent(),GetLabel());
                        //replace label and insert CONTINUE with new label for parallel nest
    cur_st = cur_st->lexNext(); //last inserted statement == last statement of parallel nest
  }  
}

void  SkipParLoopNest(SgStatement *stmt)
{ SgExpression *dovar;
  int i,nloop;
  SgStatement *st,*stl;
  stl = stmt;
  i = nloop = 0;
  // looking through the do_variables list
  for(dovar=stmt->expr(2); dovar; dovar=dovar->rhs())
        nloop++;
  // looking through the loop nest 
  for(st=par_do; i<nloop && isSgForStmt(st); st=st->lexNext(),i++)
     stl = st; 
  cur_st = stl;
}

heap_pointer_list *HeapList(heap_pointer_list *heap_point, SgSymbol *sheap,SgSymbol *sp)
{ heap_pointer_list *l;
  if(!heap_point) {
     heap_point = new heap_pointer_list;
     heap_point->symb_p = sp;
     heap_point->symb_heap = sheap;
     heap_point->next = NULL;
  } else {
     for(l=heap_point; l; l=l->next)
        if(l->symb_p == sp)
           return(heap_point);       
     l = new heap_pointer_list;
     l->symb_p = sp;
     l->symb_heap = sheap;
     l->next = heap_point;
     heap_point = l;
  }
  return(heap_point);
}

SgSymbol *HeapForPointer(SgSymbol *p)
{heap_pointer_list *l;
 SgSymbol *heap = NULL;
  for(l=heap_point; l; l=l->next)
    if(l->symb_p == p){
          heap = l->symb_heap;
          break;
    }
 return(heap);
}

SgStatement *Check(SgStatement *stmt)
{ SgExpression *cl, *vl, *en, *esym,*eop;
 SgSymbol *s;
 //int level;
  cl = stmt->expr(1); //control list
  vl = stmt->expr(0); //variable list
  en = cl ? cl->lhs() : new SgValueExp(stmt->lineNumber());
  en = (en->rhs()) ? en->rhs() : en; // variant is KEYWORD_ARG
  LINE_NUMBER_NEXP_AFTER(en,stmt,stmt->controlParent());
  //for(; cl; cl=cl->rhs())

  for(; vl; vl=vl->rhs()) {
    s = vl->lhs()->symbol();
    eop = vl->lhs();
    if(s->type()->variant() == T_ARRAY && eop->type()->variant() == T_ARRAY) { //!!!calculating SUMMA
      if(!isSgArrayRefExp(eop) || eop->lhs()) {
	Error("Illegal argument: %s",s->identifier(),334,stmt);
        continue;
      }
       if(!check_sum) 
           check_sum = CheckSummaSymbol();
       eop = new SgVarRefExp(check_sum);
       if(HEADER(s)){ 
	 doAssignStmtAfter(SummaOfDistrArray(HeaderRef(s), eop));
         FREE_DVM(1);
       }
       else {
         SgExpression *size_array;
         SgStatement *save_st;
         int ind;
         ind = ndvm;
         doAssignStmtAfter(SummaOfArray(FirstArrayElement(s),Rank(s),DVM000(ind+1),VarType_RTS(s), eop));
         save_st = cur_st; where = cur_st;
         size_array = doSizeArray(s,stmt);
         cur_st = save_st;
         SET_DVM(ind);
       }
    }    
    esym = vl->lhs(); //variable reference
    CheckVarArrayRef(eop,cur_st,esym);
  }
  return(cur_st);
}


