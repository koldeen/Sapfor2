/*********************************************************************/
/*                   ANALYZER  V.2    2008                           */
/*********************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

//#include "vrd_db.h"

#define IN_ANAL_
#include "anl.h"
#undef IN_ANAL_
#include "dep_analyzer.h"

/************  D E P E N D E N C E    T E S T ***************/

//TightlyNestedLoops *dep_loop[200];
ProgramUnit *NLoop, *dep_root, *dep_loop[200];
int l_i = 0;
int dep_rank[200];
int nclosed;
PURoutine *deprnode[NRTN];
int depnum[NRTN];
MemoryUnitUsage **dep_params, *dep_muse;
MemoryUnitUsage *parameters[10];

#define DEP_CREATE__LOOP(A,I,LINE)   (A) = new PUFile(1);  dep_root = A; dep_loop_push(A,I);nclosed=0; printf("create nest [%d]  line=%d\n",dep_rank[l_i],LINE); printf("ROOT: %d l_i=%d\n",dep_loop[l_i],l_i);
#define DEP_CLOSE__PROGRAM(LINE1,LINE2)  printf("close program[%d] lines %d : %d\n",dep_rank[l_i],LINE1,LINE2); dep_loop[l_i]->AddMULastUsage(); printf("CLOSED:%d l_i=%d\n",dep_loop[l_i],l_i); dep_loop_pop(); nclosed=0;
#define DEP_ADD__NODE(A,RID,I,LINE)  (A)=deprnode[RID]; dep_loop_push(A,I); nclosed=0; printf("add nest[%d] line=%d \n",I,LINE);printf("ADDED:%d l_i=%d\n",dep_loop[l_i],l_i); 
#define DEP_ADD__LOOP(A,B,I,LINE)    if(dep_rank[l_i]) (A)= ((TightlyNestedLoops *)B)->AddNest(I); else (A) = ((PURoutine*)B)->AddNest(I); dep_loop_push(A,I); nclosed=0; printf("add nest[%d] line=%d \n",I,LINE);printf("ADDED:%d l_i=%d\n",dep_loop[l_i],l_i); 
#define DEP_CLOSE__LOOP(LINE1,LINE2)  printf("close nest[%d] lines %d : %d\n",dep_rank[l_i],LINE1,LINE2); dep_loop[l_i]->CloseProgramUnit(); printf("CLOSED:%d l_i=%d\n",dep_loop[l_i],l_i); dep_loop_pop(); nclosed=0; 
#define DEP_SPLIT__LOOP(A,I,LINE1,LINE2) dep_loop[l_i]->AddMULastUsage(); (A)=((TightlyNestedLoops *)A)->SplitNest(I); dep_loop[l_i]=A; dep_rank[l_i]=dep_rank[l_i]-I;  printf("split nest[%d] lines %d : %d\n",I,LINE1,LINE2); nclosed=0;
#define DEP_ADD__CALL(A)              dep_add_call(A);
#define MEM_UNIT(A) ((MemoryUnit*)(A)->attributeValue(0,M_UNIT))

void dep_loop_header(SgStatement *stmt);
void dep_loop_end(SgStatement *stmt);
void dep_loop_pop();
//void dep_loop_push(TightlyNestedLoops *lp, int rank);
void dep_loop_push(ProgramUnit *lp, int rank);
MemoryUnit *dep_add_memory_unit(SgSymbol *s, int varid);
MemoryUnitUsage *dep_add_scalar_usage(SgExpression *ref, int mode);
ArrayUsage *dep_add_array_usage(SgExpression *ref, int mode);
int NumberOfIndexes(SgExpression *ref);
void dep_add_index_expr(ArrayUsage *dep_use, int dim, SgExpression *ei);
void add_index_var(SgStatement *st);
void dep_print_mu_list(MemoryUnit *mu, int isArray);
void dep_print_usage_lists(SgStatement *func);
int DepMode(int mode);
int dep_add_dummies(SgStatement *func);
void dep_add_paramsNumber(int n);
PURoutineCall *dep_add_call(SgSymbol *s);
void dep_argument(SgSymbol *s, PURoutineCall *dep_call, int i);
int NumberOfParams(SgStatement *func);
/***************************/

char *minF[6] = { "amin1","amin0","dmin1","min","min1","min0" };
char *maxF[6] = { "amax1","amax0","dmax1","max","max1","max0" };


int start_dep_analyzer(SgProject *project)
{ 
    char *source_name;
    int i, j, k, n, num_routines;
    int fileid;

    SgFile *file;

    initVariantNames();
    initialize();

    fin_name = new char[80];

    n = project->numberOfFiles();
    fin_name = project->fileName(n - 1);
    
    //vrd_open(db_name);
    // put  variant of problem in table classes 
    put_in_classes();
    // put analyzing mode in table analyzed
    put_in_analyzed(0, 0, 1, 0);
    DEP_CREATE__LOOP(NLoop, 0, 0)
        // building program structure 
        // looking through the file list of project (first time)
        for (i = n - 1; i >= 0; i--)
        {
            file = &(project->file(i));
            ProgramStructure(file);
        }
    num_routines = id_routines; //the number of program units

                                // looking through the file list of project (second time)
    for (i = n - 1; i >= 0; i--)
    {
        file = &(project->file(i));
        current_file = file;   // global variable 
        i_file = i;
        fin_name = project->fileName(i);
        printf("<<<<<  Analyzing   %s  >>>>>\n", fin_name);

        fileid = put_in_files(fin_name);
        AnalyseFile(file, fileid);
    }
    DEP_CLOSE__PROGRAM(0, 0)

    try
    {
        PUFile* file = dynamic_cast <PUFile*> (dep_root);
        if (!file) throw ::Exception::NullPointerException();

        TestController* tController = new TestController();
        LoopTreePrint lTPrint(file);
        _timeb timebuffer;
        time_t test_time;
        unsigned short millitm;

        tController->SetTestedProject(file);

        _ftime64_s(&timebuffer);

        test_time = timebuffer.time;
        millitm = timebuffer.millitm;

        cout << endl << "start dependence analysis..." << endl;
        tController->ExecuteTests();
        cout << "end dependence analysis" << endl << endl;

        _ftime64_s(&timebuffer);
        test_time = timebuffer.time - test_time;
        millitm = timebuffer.millitm - millitm;
        if (millitm < 0)
        {
            test_time--;
            millitm = -millitm;
        }

        //lTPrint.SetIsDepTested(true);
        //lTPrint.SetTestTime(test_time, millitm);
        //lTPrint.Print();
        put_in_analyzed(1, 1, 0, 0);
    }
    catch (::Exception::IException& e)
    {
        cout << typeid (e).name() << endl;
        cout << e.ToString() << endl;
        exit(1);
    }

    //vrd_close();
    printf("\n*****  Done  *****\n");
    printVars();
    return 0;
}

void initVariantNames() 
{
    for (int i = 0; i < MAXTAGS; i++) 
        tag[i] = NULL;
#include "tag.h"
}

void initialize()
{
    id_files = 0;
    id_routines = 1;
    n_routines = 0;
    id_vars = 0;
    id_comid = 0;
    id_comdef = 0;
    id_expressions = 0;
    id_monoms = 0;
    id_loops = 0;
    id_operators = 0;
    id_usage = 0;
    id_calls = 0;
    id_classes = 0;
    in_arg_list = 0;
    first_common = NULL;
    default_integer_size = 4;
    default_real_size = 4;
    VAL_1 = new SgValueExp(1);
}

void ProgramStructure(SgFile *file)
{// numerating program units for table routines
    SgStatement *stat;
    char *func_name, *file_name;
    SgSymbol *sf;
    int l;
    printf("program structure\n");
    // grab the first statement in the file.
    stat = file->firstStatement(); // file header   
    for (stat = stat->lexNext(); stat; stat = end_of_unit->lexNext())
    {
        sf = stat->symbol();
        if (sf && (stat->variant() == FUNC_HEDR || stat->variant() == PROC_HEDR || stat->variant() == PROG_HEDR))
            //(sf->variant()==FUNCTION_NAME || sf->variant()==PROCEDURE_NAME || sf->variant()==PROGRAM_NAME))
        {
            l = strlen(sf->identifier());
            func_name = new char[l + 1];
            strcpy(func_name, sf->identifier());
            if (stat->variant() == PROG_HEDR)
                rname[1] = func_name;
            else
                rname[++id_routines] = func_name;
            
            if (stat->variant() == PROG_HEDR)
                depnum[id_routines] = 0;
            else
                depnum[id_routines] = ((SgProgHedrStmt*)stat)->numberOfParameters();
            printf("%d\n", depnum[id_routines]); 
            deprnode[id_routines] = ((PUFile *)dep_root)->AddRoutine(id_routines, depnum[id_routines]);  
            printf("add routine[%d] %s on line=%d with %d params \n", id_routines, rname[id_routines], (stat)->lineNumber(), depnum[id_routines]);

            if (id_routines == NRTN)
            {
                ErrMessage("Table of routines is full", 0);
                exit(1);
            }
        }
        end_of_unit = stat->lastNodeOfStmt();
    }
}

void AnalyseFile(SgFile *file, int fileid)
{
    SgStatement *func, *stat;
    no_name_symb = NULL;
    // grab the first statement in the file.
    stat = file->firstStatement(); // file header
    file_header = stat;

    //NLoop = new TightlyNestedLoops (0); 
    //  DEP_CREATE__LOOP(NLoop,0,0) 

    //numfun = file->numberOfFunctions(); //  number of functions
    // function is program unit accept BLOCKDATA and MODULE (F90),i.e. 
    // PROGRAM, SUBROUTINE, FUNCTION
    has_contains = NULL;
    for (stat = stat->lexNext(); stat; stat = end_of_unit->lexNext())
    {
        //end of external procedure with CONTAINS statement
        if (has_contains && stat->variant() == CONTROL_END && has_contains->controlParent() == stat->controlParent())
        {
            end_of_unit = stat; has_contains = NULL;
            continue;
        }
        if (stat->variant() == BLOCK_DATA)  //BLOCK_DATA header 
        {
            end_of_unit = stat->lastNodeOfStmt();
            //AnalyzeBlockData(stat); 
            continue;
        }
        // PROGRAM, SUBROUTINE, FUNCTION header
        func = stat;
        cur_func = func;
        //printf("%s ...\n", func->symbol()->identifier());
        // analysing the function (program unit)
        if (stat->variant() == FUNC_HEDR || stat->variant() == PROC_HEDR || stat->variant() == PROG_HEDR)
            AnalyseProgramUnit(func, fileid);
    }

    //DEP_CLOSE__LOOP(0,0)
}

void  AnalyseProgramUnit(SgStatement *func, int fileid)
{
    SgSymbol *s;
    SgStatement *stmt, *first_exec, *parent;
    int root, routine, oper_id;
    SgLabel *labop;
    int n;
    //initialisation
    Lexp = NULL;
    lab_list = NULL;
    routine_common = NULL;

    DECL(func->symbol()) = 1;
    root = put_in_loops(func);
    routine = put_in_routines(func, fileid, root);
    //put_root_in_looptree(root);
    end_of_unit = func->lastNodeOfStmt();
    //saveall = is_SAVE_inRoutine(func);
    testSAVEandCOMMONinRoutine(func);
    put_in_vars(func, routine); // put_in_vars(func,put_in_routines(func, fileid, put_in_loops(func)));
    put_in_dummies(func, routine);

    DEP_ADD__NODE(NLoop, routine, 0, func->lineNumber())
    dep_add_dummies(func);
    //dep_add_paramsNumber(n);
    //depnum[routine] = n;

    // follow the statements of the program unit in lexical order
    // until first executable statement
    for (stmt = func->lexNext(); stmt && (stmt != end_of_unit); stmt = stmt->lexNext())
    {
        if (!isSgExecutableStatement(stmt)) //is Fortran specification statement
                                            // isSgExecutableStatement: 
                                            //               FALSE  -  for specification statement of Fortan 90
                                            //               TRUE   -  for executable statement of Fortan 90 and
                                            //                         all directives of F-DVM 
        {
            // analizing PARAMETER statement
            if (stmt->variant() == PARAM_DECL)
            {
                ParameterList(stmt->expr(0));
                continue;
            }
            if (stmt->variant() == COMM_STAT)
            {
                CommonList(stmt, routine);
                continue;
            }
            if (stmt->variant() == STMTFN_STAT)
            {
                DECL(stmt->expr(0)->symbol()) = 2;     //flag of statement function name
                continue;
            }

            continue;
        } //end if executable
        if ((stmt->variant() == FORMAT_STAT))
            continue;
        //dvm_specification directives

        // all declaration statements are processed,
        // current statement is executable (F77/DVM)

        break;
    } //end for

      // testing common-blok definitions, if necessary adding attribute ASSOCIATION in table atr
    TestingCommon();
    first_exec = stmt;
    // follow the executable statements in lexical order until last statement
    // of the program unit
    for (; stmt && (stmt != end_of_unit->lexNext()); stmt = stmt->lexNext())
    {
        cur_st = stmt; //printf("line: %d\n",stmt->lineNumber()); 
                       // FORMAT_STAT, ENTRY_STAT, DATA_DECL may appear among executable statements
                       // putting row in table operators
        switch (stmt->variant())
        {
        case ENTRY_STAT: //error
        case FORMAT_STAT:
        case DATA_DECL:
            // case RETURN_STAT:
            // case STOP_STAT:
            // case PAUSE_NODE:
            continue; //break;    
        default:
            oper_id = put_in_operators(stmt);
            break;
        }
        AnalyzeComment(stmt);
        // looking for expressions in statement;
        // putting rows in tables: 
        //         expressions, usage, indexes, call, arguments, expr_usage, io, loops 

        kt = 0;
        //stmt->unparsestdout();
        //printf("   \n");
        switch (stmt->variant())
        {
        case ASSIGN_STAT:           // Assign statement               
            RefInExpr(stmt->expr(1), READ_);
            RefInExpr(stmt->expr(0), WRITE_);
            TestReduction(stmt);
            break;
        case SWITCH_NODE:           // SELECT CASE ...
        case ARITHIF_NODE:          // Arithmetical IF
        case IF_NODE:               // IF... THEN
        case WHILE_NODE:            // DO WHILE (...)
        case CASE_NODE:             // CASE ...
        case ELSEIF_NODE:           // ELSE IF...
        case LOGIF_NODE:            // Logical IF 
            RefInExpr(stmt->expr(0), READ_);
            break;
        case COMGOTO_NODE:          // Computed GO TO
            RefInExpr(stmt->expr(1), READ_);
            break;
        case PROC_STAT:              // CALL
            Call(stmt->symbol(), stmt->expr(0));
            break;
        case FOR_NODE:
            put_in_loops(stmt);
            usage_in_do_stmt(stmt);
            dep_loop_header(stmt);
            break;

        case OPEN_STAT:
        case CLOSE_STAT:
        case INQUIRE_STAT:
        {SgExpression *ioc[30] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
        int io_err, mode;
        mode = (stmt->variant() == INQUIRE_STAT) ? 4 : 0;
        io_err = control_list_open(stmt->expr(1), ioc); // control_list analisys
        if (ioc[ERR_]) {
            put_in_io(oper_id, 8);
            if (mode)
                put_in_io(oper_id, mode);
            //err("END= and ERR= specifiers are illegal in FDVM", 186,stmt);
            break;
        }
        else
            put_in_io(oper_id, mode);
        }
        break;

        case BACKSPACE_STAT:
        case ENDFILE_STAT:
        case REWIND_STAT:
        {SgExpression *ioc[10] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };

        control_list1(stmt->expr(1), ioc); // control_list analisys
        if (ioc[END_] || ioc[ERR_])
            put_in_io(oper_id, 8);
        //err("END= and ERR= specifiers are not allowed in FDVM", 186,stmt);
        else
            put_in_io(oper_id, 0);
        }
        break;

        case WRITE_STAT:
        case READ_STAT:
        case PRINT_STAT:
        {SgSymbol *sio;
        SgExpression *e, *iol;
        SgExpression *ioc[10] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
        int IOtype, io_err;
        if (stmt->variant() == WRITE_STAT)
        {
            put_in_io(oper_id, 1);
            use_mode = READ_;
        }
        else if (stmt->variant() == READ_STAT)
        {
            put_in_io(oper_id, 2);
            use_mode = WRITE_;
        }
        else
        {
            put_in_io(oper_id, 3);
            use_mode = READ_;
        }
        has_implicit_loop = 0;
        //defines type of Input/Output
        //if(e->variant() == EXPR_LIST)
        // e = e->rhs()->lhs(); // value of second element of IO-list -
        // Format

        // analizes IO control list and sets on ioc[]                       
        e = stmt->expr(1); // IO control
        io_err = IOcontrol(e, ioc, stmt->variant());
        if (ioc[END_] || ioc[ERR_] || ioc[EOR_]) {
            put_in_io(oper_id, 8);
            //err("END=, EOR= and ERR= specifiers are illegal in FDVM", 186,stmt);
            break;
        }

        if (ioc[UNIT_] && (ioc[UNIT_]->type()->variant() == T_STRING)) {
            SgKeywordValExp *kwe;
            if ((kwe = isSgKeywordValExp(ioc[UNIT_])) && (!strcmp(kwe->value(), "*")))
                //"*" - system unit
                ;
            else { // I/O to internal file           
                if (!TestIOList(stmt->expr(0), stmt))
                    put_in_io(oper_id, 6);
                if (has_implicit_loop)
                    put_in_io(oper_id, 5);
                break;
            }
        }

        // analizes format specifier and determines type of I/O
        if (ioc[FMT_]) {

            SgKeywordValExp * kwe;
            kwe = isSgKeywordValExp(ioc[FMT_]);
            if (kwe) // Format
                if (!strcmp(kwe->value(), "*"))
                    IOtype = 1; // formatted IO, controlled by IO-list  
                else {
                    IOtype = 0; // illegal format specifier ?? 
                    err("Invalid format specification", 189, stmt);
                    break;
                }
            else
                IOtype = 2; // formatted IO, controlled by format
                            // specification or NAMELIST
        }
        else
            IOtype = 3; // unformatted IO
        if (ioc[NML_])
            IOtype = 2; // formatted IO, controlled by  NAMELIST
        if (IOtype != 1)
            put_in_io(oper_id, 7);
        //looking through the IO-list
        if (!TestIOList(stmt->expr(0), stmt))
            put_in_io(oper_id, 6);
        if (has_implicit_loop)
            put_in_io(oper_id, 5);
        break;
        }

        default:
            break;
        }
        // statement with label:
        //       creating list of label for building control graph
        labop = stmt->label();
        if (labop)  // adding to label list
        {
            label_oper *elo;
            elo = new label_oper;
            elo->num = LABEL_STMTNO(labop->thelabel);
            elo->oper = oper_id;
            elo->stat = stmt;
            elo->next = lab_list;
            lab_list = elo;
        }
        // creating loop's tree
        if (isDoEndStmt(stmt))  //last statement of do-loop
        {
            SgStatement *parent, *stdo, *next;
            SgForStmt *do_parent;
            SgLabel *lab, *labdo;
            int tightly;
            //stmt->unparsestdout();
            dep_loop_end(stmt);
            stdo = stmt->controlParent();
            parent = ParentOfDo(stdo); //header->controlParent();
            lab = stmt->label();
            next = (stmt->variant() != LOGIF_NODE) ? NextExecStat(stmt) : NextExecStat(stmt->lexNext());
            do_parent = isSgForStmt(parent);
            if (lab)
                //looking through the nest of loops with the same label 
                for (; (do_parent = isSgForStmt(parent)); stdo = parent, parent = ParentOfDo(parent))
                    if ((labdo = ((SgForStmt *)parent)->endOfLoop()) && LABEL_STMTNO(lab->thelabel) == LABEL_STMTNO(labdo->thelabel))
                    {
                        if (parent->lexNext() == stdo) // the loop header follows enclosing loop header
                            tightly = 1;
                        else
                            tightly = 0;
                        put_in_looptree(stdo, parent, tightly);
                    }
                    else
                        break;
            /*   if(do_parent)
            printf("   do parent %d\n",parent->lineNumber());
            else
            printf("no do parent %d\n",parent->lineNumber());
            */
            if (!do_parent)
                tightly = 0;
            else if (parent->lexNext() == stdo && next->controlParent() == parent &&
                (next->variant() == CONT_STAT || next->variant() == CONTROL_END))
                tightly = 1;
            else
                tightly = 0;

        ENDLOOP: put_in_looptree(stdo, parent, tightly); // end of performing do-loop nest 
        }

    } //end for

      //printf("close program unit\n");
    DEP_CLOSE__LOOP(func->lineNumber(), end_of_unit->lineNumber())  // closing program unit

                                                                    // creating control graph (branches)
                                                                    // follow the executable statements in lexical order until last statement
                                                                    // of the program unit (second time)
        for (stmt = first_exec; stmt && (stmt != end_of_unit); stmt = stmt->lexNext())
        {
        NEXT_ST:
            cur_st = stmt;
            oper_id = (OPER(stmt)) ? *(OPER(stmt)) : 0;  // idOfOper(stmt); 
            switch (stmt->variant())
            {
            case ENTRY_STAT:
            case FORMAT_STAT:
            case DATA_DECL:
            case RETURN_STAT:
            case STOP_STAT:
                continue;
            case GOTO_NODE:             // GO TO
                put_in_branches(oper_id, OperWithLab(((SgGotoStmt *)stmt)->branchLabel()), 1);
                continue;

            case ARITHIF_NODE:          // Arithmetical IF
            {SgExpression *el;
            SgLabel *labgo;
            for (el = stmt->expr(1); el; el = el->rhs())
            {
                labgo = ((SgLabelRefExp *)(el->lhs()))->label();
                put_in_branches(oper_id, OperWithLab(labgo), 1);
            }
            }
            continue;

            case COMGOTO_NODE:          // Computed GO TO
            {SgExpression *el;
            SgLabel *labgo;
            for (el = stmt->expr(0); el; el = el->rhs())
            {
                labgo = ((SgLabelRefExp *)(el->lhs()))->label();
                put_in_branches(oper_id, OperWithLab(labgo), 1);
            }
            parent = stmt->controlParent();
            if (parent->variant() == LOGIF_NODE)
                continue;
            if (isDoEndStmt_f90(stmt))  //last statement of do-loop
                put_in_branches(oper_id, idOfOper(parent), 1);
            else
                put_in_branches(oper_id, idOfOper(NextByControl(stmt)), 1);
            }
            continue;

            case ASSGOTO_NODE:             // Assign GO TO
                warn("Assigned GO TO", 5, stmt);
                continue;

            case IF_NODE:               // IF... THEN
            case ELSEIF_NODE:           // ELSE IF...
            {SgStatement *stb;
            stb = ((SgIfStmt *)stmt)->trueBody();
            put_in_branches(oper_id, idOfOper(stb), 1);
            stb = ((SgIfStmt *)stmt)->falseBody();
            if (stb)
                put_in_branches(oper_id, idOfOper(stb), 1);
            else
                put_in_branches(oper_id, idOfOper(NextByControl(lastStmtOfIf(stmt))), 1);
            }
            continue;
            case LOGIF_NODE:            // Logical IF
            {SgStatement *next;
            next = stmt->lexNext();
            put_in_branches(oper_id, idOfOper(next), 1);

            if (isDoEndStmt_f90(stmt))  //last statement of do-loop
            {
                put_in_branches(oper_id, idOfOper(stmt->controlParent()), 1);
                if (next->variant() == COMGOTO_NODE)
                {
                    put_in_branches(idOfOper(next), idOfOper(stmt->controlParent()), 1);
                    stmt = next;
                    goto NEXT_ST;
                }
                if (next->variant() == RETURN_STAT || next->variant() == STOP_STAT || next->variant() == GOTO_NODE || next->variant() == ASSGOTO_NODE || next->variant() == ARITHIF_NODE)
                {
                    stmt = next;    goto NEXT_ST;
                }

                put_in_branches(idOfOper(next), idOfOper(stmt->controlParent()), 1);
            }
            else
            {
                put_in_branches(oper_id, idOfOper(NextByControl(next)), 1);
                //stmt=stmt->lexNext();
                if (next->variant() == COMGOTO_NODE)
                {
                    put_in_branches(idOfOper(next), idOfOper(NextByControl(next)), 1);
                    stmt = next;
                    goto NEXT_ST;
                }
                if (next->variant() == RETURN_STAT || next->variant() == STOP_STAT || next->variant() == GOTO_NODE || next->variant() == ASSGOTO_NODE || next->variant() == ARITHIF_NODE)
                {
                    stmt = next; goto NEXT_ST;
                }

                put_in_branches(idOfOper(next), idOfOper(NextByControl(next)), 1);
            }
            stmt = stmt->lexNext();  //next
            }
            continue;
            case WHILE_NODE:            // DO [<label>] WHILE (...)
            case FOR_NODE:              // DO [<label>] <dovar> = ...
                put_in_branches(oper_id, idOfOper(NextExecStat(stmt)), 0);
                parent = stmt->controlParent();
                if ((parent->variant() == FOR_NODE || parent->variant() == WHILE_NODE) && (parent->lastNodeOfStmt() == stmt))
                    //with the same label
                    put_in_branches(oper_id, idOfOper(parent), 0);
                else
                    put_in_branches(oper_id, idOfOper(NextByControl(lastStmtOfDo(stmt))), 0);
                RetestReduction(stmt);
                continue;
            case CONTROL_END:
                parent = stmt->controlParent();
                if (parent == func)
                {
                    continue;
                }
                switch (parent->variant())
                {
                case (FOR_NODE):
                case (WHILE_NODE):
                    put_in_branches(oper_id, idOfOper(parent), 1);
                    break;
                case (IF_NODE):
                case (ELSEIF_NODE):
                    if (lastStmtOfIf(parent) == stmt) // scip ELSE statement
                        put_in_branches(oper_id, idOfOper(NextByControl(stmt)), 1);
                    break;
                default:
                    break;
                }
                continue;

                /*
                case CASE_NODE:             // CASE ...
                case SWITCH_NODE:           // SELECT CASE ...

                case input/output:
                */
            default:
                if (isDoEndStmt_f90(stmt))  //last statement of do-loop
                {
                    parent = stmt->controlParent();
                    put_in_branches(oper_id, idOfOper(parent), 1);
                }
                else
                    put_in_branches(oper_id, idOfOper(NextByControl(stmt)), 1);

                break;
            }

        }  //end for

           //dep_print_usage_lists(func);
    return;
}

//-------------------------------------------------------------------------------------------------
void PrintSymbolTable(SgFile *f)
{
    SgSymbol *s;
    printf("\nS Y M B O L   T A B L E \n");
    for (s = f->firstSymbol(); s; s = s->next())
        //printf(" %s/%d/     ", s->identifier(), s->id() );
        printSymb(s);
}

void printSymb(SgSymbol *s)
{
    char *head;
    head = isHeaderStmtSymbol(s) ? "HEADER  " : "        ";
    printf("SYMB[%3d]  scope=STMT[%3d]  V[%3d] : %s    %s", s->id(), (s->scope()) ? (s->scope())->id() : -1, s->variant(), s->identifier(), head);
    //printVariantName(s->variant()); printf("     ");
    printType(s->type());
    printf("\n");
}

void printType(SgType *t)
{
    SgArrayType *arrayt;
    /*SgExpression *e = new SgExpression(TYPE_RANGES(t->thetype));*/
    int i, n;
    if (!t) { printf("no type "); return; }
    else   printf("TYPE[%d]:", t->id());
    if (arrayt = isSgArrayType(t))
    {
        printf("dimension(");
        n = arrayt->dimension();

        for (i = 0; i < n; i++)
        {
            (arrayt->sizeInDim(i))->unparsestdout();
            if (i < n - 1)  printf(", ");
        }
        printf(") ");
    }
    else
        printIntrinsicType(t);

    /*  if(e) e->unparsestdout();*/
    if (t->hasBaseType())
    {
        printf("of ");
        printIntrinsicType(t->baseType());
    }
}

void printIntrinsicType(SgType *t)
{
    switch (t->variant())
    {
    case  T_INT:      printf("integer "); break;
    case  T_FLOAT:    printf("real "); break;
    case  T_DOUBLE:   printf("double precision "); break;
    case  T_CHAR:     printf("character "); break;
    case  T_STRING:   printf("Character ");
        if (TYPE_RANGES(t->thetype))
            UnparseLLND(TYPE_RANGES(t->thetype));
        /*if(t->length()) printf("[%d]",t->length()->variant());*/
        /*((SgArrayType *) t)->getDimList()->unparsestdout();*/
        break;
    case  T_BOOL:     printf("logical "); break;
    case  T_COMPLEX:  printf("complex "); break;
    case  T_DCOMPLEX:  printf("double complex "); break;

    default: break;
    }
}

void PrintTypeTable(SgFile *f)
{
    SgType *t;
    printf("\nT Y P E   T A B L E \n");
    for (t = f->firstType(); t; t = t->next())
    {
        printType(t); printf("\n");
    }

}

char * OnlyName(char *filename)
{
    char *basename;
    int i;
    basename = (char *)malloc((unsigned)(strlen(filename) + 4));

    strcpy(basename, filename);

    for (i = strlen(filename) - 1; i >= 0; i--)
    {
        if (basename[i] == '.')
        {
            basename[i] = '\0';
            break;
        }
    }

    return(basename);
}

void ScanSymbolTable(SgFile *f)
{
    SgSymbol *s;
    for (s = f->firstSymbol(); s; s = s->next())
        if (isHeaderStmtSymbol(s))
            printSymb(s);
}

int is_SAVE_inRoutine(SgStatement *func)
{
    SgStatement *stmt, *last;
    last = func->lastNodeOfStmt();
    for (stmt = func->lexNext(); stmt && (stmt != last); stmt = stmt->lexNext())
    {
        if (!isSgExecutableStatement(stmt)) //is Fortran specification statement
                                            // isSgExecutableStatement: 
                                            //               FALSE  -  for specification statement of Fortan 90
                                            //               TRUE   -  for executable statement of Fortan 90 and
                                            //                         all directives of F-DVM 
        {
            // analizing SAVE statement
            if (stmt->variant() == SAVE_DECL)
            {
                if (!stmt->expr(0))  //SAVE without name-list
                    saveall = 1;
                break;    //continue;
            }
            else
                continue;
        }
        if ((stmt->variant() == FORMAT_STAT))
            continue;
        // all declaration statements are processed,
        // current statement is executable (F77/DVM)

        break;

    }
    return(saveall);
}

void testSAVEandCOMMONinRoutine(SgStatement *func)
{
    SgStatement *stmt, *last;
    last = func->lastNodeOfStmt();
    for (stmt = func->lexNext(); stmt && (stmt != last); stmt = stmt->lexNext())
    {
        if (!isSgExecutableStatement(stmt)) //is Fortran specification statement
                                            // isSgExecutableStatement: 
                                            //               FALSE  -  for specification statement of Fortan 90
                                            //               TRUE   -  for executable statement of Fortan 90 and
                                            //                         all directives of F-DVM 
        {

            // analizing SAVE statement
            if (stmt->variant() == SAVE_DECL)
            {
                if (!stmt->expr(0))  //SAVE without name-list
                    saveall = 1;
                continue;
            }
            if (stmt->variant() == COMM_STAT)
            {
                SgExpression *ec, *el;
                SgSymbol *sc;
                for (ec = stmt->expr(0); ec; ec = ec->rhs()) // looking through COMM_LIST
                    for (el = ec->lhs(); el; el = el->rhs()) {
                        sc = el->lhs()->symbol();
                        if (sc)
                            SYMB_ATTR(sc->thesymb) = SYMB_ATTR(sc->thesymb) | COMMON_BIT;
                    }

                continue;
            }
            continue;
        }
        if ((stmt->variant() == FORMAT_STAT))
            continue;
        // all declaration statements are processed,
        // current statement is executable (F77/DVM)

        break;

    } //end for

}

void ParameterList(SgExpression *el)
{
    SgExpression *ep, *ell, *ev;
    SgSymbol *sc;
    int var, value;
    PTR_LLND ecn;
    for (ell = el; ell; ell = ell->rhs()) // looking through the parameter list
    {
        ep = ell->lhs();
        sc = ep->symbol();
        var = *VAR(sc);
        ecn = SYMB_VAL(sc->thesymb);  // sc->thesymb->entry.const_value;

        if (ecn->variant == INT_VAL)
        {
            put_in_classizes(id_classes, var, ecn->entry.ival);
            continue;
        }
        ev = Calculate(LlndMapping(ecn));
        if (ev->variant() == INT_VAL)
            put_in_classizes(id_classes, var, ev->thellnd->entry.ival);

    }
}

void CommonList(SgStatement *stmt, int routine)
{
    SgExpression *ec, *el;
    SgSymbol *sc, *sn;
    commonblock *cb;
    int def, com, size;
    commondef *p;
    char *name;
    for (ec = stmt->expr(0); ec; ec = ec->rhs()) // looking through COMM_LIST
    {
        sn = ec->symbol();  //common block name or null
        if (!sn)
            sn = UnnamedCommon();
        if (!(p = isComdefForRoutine(sn, routine)))
        {
            com = isInTableComid(sn);
            if (!com)
                com = put_in_comid(sn);
            def = put_in_comdef();
            put_in_comdecl(sn, routine, com, def);
            p = new commondef;
            p->routine = routine;
            p->comid = com;
            p->comdef = def;
            p->list = &(ec->lhs()->copy());
            cb = new commonblock;
            p->cblock = cb;
            sn->addAttribute(COM_ID, (void *)p, sizeof(commondef));

            if (cur_common)
                cur_common->next = cb;
            cb->list = Create_Common_List(ec->lhs());
            size = strlen(sn->identifier());
            name = new char[size + 1];
            strcpy(name, sn->identifier());
            //sprintf(name,"%s",sn->identifier());
            cb->id = com;
            cb->numfile = i_file;
            cb->next = NULL;
            cur_common = cb;
            if (!first_common)
                first_common = cb;
            if (!routine_common)
                routine_common = cb;
        }
        else
        {
            com = p->comid;
            def = p->comdef;
            p->cblock->list = Connect_Common_List(p->cblock->list, ec->lhs());
        }
        for (el = ec->lhs(); el; el = el->rhs())
        {
            sc = el->lhs()->symbol();
            if (sc)
                put_in_comvars(def, sc);
        }
    }
}

commondef *isComdefForRoutine(SgSymbol *sn, int routine)
{
    int n, i;
    commondef *p;

    n = sn->numberOfAttributes(COM_ID);

    if (!COMM(sn))
        return(NULL);
    for (i = 0; i<n; i++)
    {
        p = (commondef *)sn->attributeValue(i, COM_ID);
        if (p->routine == routine)
            return(p);
    }
    return(NULL);
}

SgSymbol *UnnamedCommon()
{
    SgSymbol *s;
    //char *name;
    // name = new char[80];
    // sprintf(name,"mem000%s",stype->identifier());  
    // s = new SgSymbol(VARIABLE_NAME,"NO_NAME_COMMON",*file_header);

    if (!no_name_symb)
        no_name_symb = new SgSymbol(VARIABLE_NAME, "NO_NAME_COMMON", *file_header);

    return (no_name_symb);
}

/*
void SearchArrayAndFuncRef(SgStatement *stmt)
{
RefInExpr(stmt->expr(0));
RefInExpr(stmt->expr(1));
RefInExpr(stmt->expr(2));
}
*/

void Index(SgExpression *e, int use, int ind)
{
    int expr_id;
    expr_id = ExprWithLinearForm(e);
    put_in_indexes(use, ind, expr_id);
    RefInExpr(e, READ_);
}


void RefInExpr(SgExpression *e, int mode)
{
    int i, use, call;
    SgExpression *el;
    int *id;
    //ArrayUsage *dep_use;

    if (!e)
        return;

    if (isSgVarRefExp(e))
    {
        use = isInUsage(e->symbol(), mode);
        if (!use)
        {        //printf("*usage %s : %d\n",e->symbol()->identifier(), DepMode(mode)); 
            if (!isSgForStmt(cur_st))
                dep_muse = dep_add_scalar_usage(e, DepMode(mode));
            use = put_in_usage(e->symbol(), mode);
            if (kt<NVARS)
            {
                symu[++kt] = e->symbol();
                modu[kt] = mode;
                useid[kt] = use;
            }
        }
        if (in_arg_list)
        {
            id = new int;
            *id = use;
            e->addAttribute(USE_ID, (void*)id, sizeof(int));
        }
        return;
    }

    if (isSgArrayRefExp(e))
    {
        use = put_in_usage(e->symbol(), mode);
        if (in_arg_list)
        {
            id = new int;
            *id = use;
            e->addAttribute(USE_ID, (void*)id, sizeof(int));
        }
        for (el = e->lhs(), i = 1; el; el = el->rhs(), i++)
            Index(el->lhs(), use, i);
        //printf("*usage array %s : %d\n",e->symbol()->identifier(),DepMode(mode));
        if (!isSgForStmt(cur_st))
        {
            dep_muse = dep_add_array_usage(e, DepMode(mode));
            for (el = e->lhs(), i = 1; el; el = el->rhs(), i++)
                dep_add_index_expr((ArrayUsage *)dep_muse, i - 1, el->lhs());
        }
        return;
    }

    if (isSgFunctionCallExp(e))
    {
        Call(e->symbol(), e->lhs());
        return;
    }
    if (e->variant() == ARRAY_OP)
    {
        RefInExpr(e->lhs(), mode);
        RefInExpr(e->rhs(), READ_);
        return;
    }

    RefInExpr(e->lhs(), mode);
    RefInExpr(e->rhs(), mode);

    return;
}

void RefInArg(SgExpression *e, int expr)
{
    int use;

    if (!e)
        return;
    /*
    if(isSgVarRefExp(e))
    {
    use = Usage(e);
    //if(!use)
    //   ErrMessageF("No id for usage var %s", e->symbol()->identifier(),cur_st);
    if(use)
    put_in_expr_usage(expr,use);
    return;
    }
    */
    if (isSgVarRefExp(e) || isSgArrayRefExp(e))
    {
        use = Usage(e);
        //if(!use) 
        //   ErrMessageF("No id for usage var %s", e->symbol()->identifier(),cur_st);
        if (use)
            put_in_expr_usage(expr, use);
        RefInArg(e->lhs(), expr);
        return;
    }

    RefInArg(e->lhs(), expr);
    RefInArg(e->rhs(), expr);
    return;
}


void Argument(SgExpression *e, int i, int call, PURoutineCall *dep_call)
{
    int expr_id, use, variant;
    expr_id = ExprWithPostfix(e);
    put_in_arguments(call, i, expr_id);

    if (isSgVarRefExp(e))
    {
        variant = e->symbol()->variant();
        if (variant == FUNCTION_NAME || variant == PROCEDURE_NAME || variant == ROUTINE_NAME)
            return;
        RefInExpr(e, NUL_);
        dep_argument(e->symbol(), dep_call, i);
        RefInArg(e, expr_id);

        // use = Usage(e); //isInUsage(e->symbol(),NUL_);
        // if(!use) 
        //    ErrMessageF("No id for usage var %s", e->symbol()->identifier(),cur_st);
        // put_in_expr_usage(expr_id, use);
        return;
    }
    else if (isSgArrayRefExp(e))
    {
        RefInExpr(e, NUL_);
        dep_argument(e->symbol(), dep_call, i);
        RefInArg(e, expr_id);
        //use = Usage(e);
        //if(!use) 
        //   ErrMessageF("No id for usage var %s", e->symbol()->identifier(),cur_st);
        //put_in_expr_usage(expr_id, use);
        //RefInArg(e->lhs(),expr_id);
        return;
    }
    else if (e->variant() == ARRAY_OP)
    {
        RefInExpr(e->lhs(), NUL_);
        RefInExpr(e->rhs(), READ_);
        RefInArg(e, expr_id);
        return;
    }
    else
    {
        RefInExpr(e, READ_);
        //if(hasPostfix(e))
        RefInArg(e, expr_id);
        return;
    }
}

void Call(SgSymbol *s, SgExpression *e)
{
    SgExpression *el;
    int i, call;
    PURoutineCall *dep_call;
    if (DECL(s) == 2)    //is statement function
        call = 0;
    else
    {
        call = put_in_calls(s);
        dep_call = DEP_ADD__CALL(s) //dep_add_call(s);
    }
    if (call)
    {
        if (!e)  //argument list is absent
            return;
        in_arg_list++;
        for (el = e, i = 1; el; el = el->rhs(), i++)
            Argument(el->lhs(), i, call, dep_call);
        in_arg_list--;
    }
    else
    {
        if (DECL(s) != 2 && !isIntrinsicFunctionName(s->identifier()))
        {
            Warning("Call of no body routine  %s", s->identifier(), 3, cur_st);
            RefInExpr(e, NUL_);
        }
        RefInExpr(e, READ_);
    }
    return;
}


int isInUsage(SgSymbol *s, int mode)
{
    int i;
    for (i = kt; i; i--)
    {
        if (symu[i] == s && modu[i] == mode)
            return(useid[i]);
    }
    return(0);
}

int Usage(SgExpression *e)
{
    if (USE(e))
        return(*USE(e));
    else
        return(0);
}

void usage_in_do_stmt(SgStatement *stmt)
{
    SgForStmt *stdo;
    SgExpression *estep;
    stdo = isSgForStmt(stmt);
    estep = stdo->step();
    put_in_usage(stdo->symbol(), WRITE_);
    RefInExpr(stdo->start(), READ_);
    RefInExpr(stdo->end(), READ_);
    if (estep)
        RefInExpr(estep, READ_);
}

int isDoEndStmt(SgStatement *stmt)
{
    SgLabel *lab, *do_lab;
    SgForStmt *parent;
    if (!(lab = stmt->label()) && stmt->variant() != CONTROL_END) //the statement has no label and
        return(0);                                               //is not ENDDO 
    parent = isSgForStmt(stmt->controlParent());
    if (!parent)  //parent isn't DO statement
        return(0);
    do_lab = parent->endOfLoop(); // label of loop end or NULL
    if (do_lab) //  DO statement with label
        if (lab && LABEL_STMTNO(lab->thelabel) == LABEL_STMTNO(do_lab->thelabel))
            // the statement label is the label of loop end  
            return(1);
        else
            return(0);
    else   //  DO statement without label
        if (stmt->variant() == CONTROL_END)
            return(1);
        else
            return(0);
}

int isDoEndStmt_f90(SgStatement *stmt)
{// loop header may be
 //  DO <label> i=N1,N2,N3  or  DO <label> WHILE ( <condition> )

    SgLabel *lab, *do_lab;
    SgStatement *parent;
    if (!(lab = stmt->label()) && stmt->variant() != CONTROL_END) //the statement has no label and
        return(0);                                               //is not ENDDO 
    parent = stmt->controlParent();
    if (parent->variant() != FOR_NODE && parent->variant() != WHILE_NODE)
        return(0);

    if (BIF_LABEL_USE(parent->thebif)) //  DO statement with label
        if (lab && LABEL_STMTNO(lab->thelabel) == LABEL_STMTNO(BIF_LABEL_USE(parent->thebif)))
            // the statement label is the label of loop end  
            return(1);
        else
            return(0);
    else   //  DO statement without label
        if (stmt->variant() == CONTROL_END)
            return(1);
        else
            return(0);
}


SgStatement *NextExecStat(SgStatement *stmt)
{
    SgStatement *next;
    next = stmt->lexNext();
    while (next->variant() == FORMAT_STAT || next->variant() == ENTRY_STAT || next->variant() == DATA_DECL)
        next = next->lexNext();
    return(next);
}

SgStatement *NextByControl(SgStatement *stmt)
{
    SgStatement *next, *parent, *last;
    next = stmt->lexNext();
    // skipping FORMAT, ENTRY  and DATA statements
    while (next->variant() == FORMAT_STAT || next->variant() == ENTRY_STAT || next->variant() == DATA_DECL)
        next = next->lexNext();
    // next is statement ELSE, branch to corresponding END IF
    parent = next->controlParent();
    if (next->variant() == CONTROL_END && (parent->variant() == IF_NODE || parent->variant() == ELSEIF_NODE) && (last = lastStmtOfIf(parent)) != next)
        next = last;
    // next is statement ELSE IF, branch to corresponding END IF
    if (next->variant() == ELSEIF_NODE)
        next = lastStmtOfIf(parent);

    return(next);
}


SgStatement *ParentOfDo(SgStatement *dost)
{
    SgStatement *parent;
    parent = dost->controlParent();
    while (parent->variant() != FOR_NODE && parent != cur_func)  // parent->variant()!=FUNC_HEDR,PROC_HEDR,PROG_HEDR
    {
        parent = parent->controlParent();
    }
    return(parent);
}

SgStatement * lastStmtOfDo(SgStatement *stdo)
{
    SgStatement *st;

    // second version 
    st = stdo->lastNodeOfStmt();
    if (st->variant() == LOGIF_NODE)
        return(st->lexNext());
    else if (st->variant() == FOR_NODE || st->variant() == WHILE_NODE)
        return(lastStmtOfDo(st));
    else
        return(st);
}


SgStatement * lastStmtOfIf(SgStatement *stif)
{
    SgStatement *st;
    // look for endif
    st = stif;
RE: st = st->lastNodeOfStmt();
    if ((st->variant() == ELSEIF_NODE))
        goto RE;
    else
        return(st);
}

int isMaxMinFunc(char *name)
{
    int i;
    switch (name[0])
    {
    case('a'):
        for (i = 0; i <= 1; i++)
        {
            if (!strcmp(maxF[i], name))
                return(1);
            if (!strcmp(minF[i], name))
                return(2);
        }
        return(0);
    case('d'):
        if (!strcmp(maxF[2], name))
            return(1);
        if (!strcmp(minF[2], name))
            return(2);
        return(0);
    case('m'):
        for (i = 3; i <= 5; i++)
        {
            if (!strcmp(maxF[i], name))
                return(1);
            if (!strcmp(minF[i], name))
                return(2);
        }
        return(0);

    default:   return (0);
    }
    return(0);
}



int control_list_open(SgExpression *e, SgExpression *ioc[])
// analizes control list (e) for OPEN,CLOSE and INQUIRE statements
// and sets on ioc[]
{
    SgKeywordValExp *kwe;
    SgExpression *ee, *el;

    if (e->variant() == SPEC_PAIR) {
        ioc[UNIT_] = e->rhs();
        return(1);
    }
    if (e->variant() == EXPR_LIST) {
        for (el = e; el; el = el->rhs()) {
            ee = el->lhs();
            if (ee->variant() != SPEC_PAIR)
                return(0); // IO_control list error
            kwe = isSgKeywordValExp(ee->lhs());
            if (!kwe)
                return(0);
            if (!strcmp(kwe->value(), "unit"))
                ioc[UNIT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "file"))
                ioc[FILE_] = ee->rhs();
            else if (!strcmp(kwe->value(), "status"))
                ioc[STATUS_] = ee->rhs();
            else if (!strcmp(kwe->value(), "iostat"))
                ioc[IOSTAT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "access"))
                ioc[ACCESS_] = ee->rhs();
            else if (!strcmp(kwe->value(), "err"))
                ioc[ERR_] = ee->rhs();
            else if (!strcmp(kwe->value(), "form"))
                ioc[FORM_] = ee->rhs();
            else if (!strcmp(kwe->value(), "recl"))
                ioc[RECL_] = ee->rhs();
            else if (!strcmp(kwe->value(), "blank"))
                ioc[BLANK_] = ee->rhs();
            else if (!strcmp(kwe->value(), "exist"))
                ioc[EXIST_] = ee->rhs();
            else if (!strcmp(kwe->value(), "opened"))
                ioc[OPENED_] = ee->rhs();
            else if (!strcmp(kwe->value(), "number"))
                ioc[NUMBER_] = ee->rhs();
            else if (!strcmp(kwe->value(), "named"))
                ioc[NAMED_] = ee->rhs();
            else if (!strcmp(kwe->value(), "name"))
                ioc[NAME_] = ee->rhs();
            else if (!strcmp(kwe->value(), "sequential"))
                ioc[SEQUENTIAL_] = ee->rhs();
            else if (!strcmp(kwe->value(), "direct"))
                ioc[DIRECT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "nextrec"))
                ioc[NEXTREC_] = ee->rhs();
            else if (!strcmp(kwe->value(), "formatted"))
                ioc[FORMATTED_] = ee->rhs();
            else if (!strcmp(kwe->value(), "unformatted"))
                ioc[UNFORMATTED_] = ee->rhs();
            else if (!strcmp(kwe->value(), "position"))
                ioc[POSITION_] = ee->rhs();
            else if (!strcmp(kwe->value(), "action"))
                ioc[ACTION_] = ee->rhs();
            else if (!strcmp(kwe->value(), "readwrite"))
                ioc[READWRITE_] = ee->rhs();
            else if (!strcmp(kwe->value(), "read"))
                ioc[RD_] = ee->rhs();
            else if (!strcmp(kwe->value(), "write"))
                ioc[WR_] = ee->rhs();
            else if (!strcmp(kwe->value(), "delim"))
                ioc[DELIM_] = ee->rhs();
            else if (!strcmp(kwe->value(), "pad"))
                ioc[PAD_] = ee->rhs();
            else
                return(0);
        }
        return(1);
    }
    else
        return(0);
}

int control_list1(SgExpression *e, SgExpression *ioc[])
// analizes control list (e) for statements BACKSPACE,REWIND and ENDFILE
// and sets on ioc[]
{
    SgKeywordValExp *kwe;
    SgExpression *ee, *el;
    if (e->variant() == SPEC_PAIR) {
        ioc[UNIT_] = e->rhs();
        return(1);
    }

    if (e->variant() == EXPR_LIST) {
        for (el = e; el; el = el->rhs()) {
            ee = el->lhs();
            if (ee->variant() != SPEC_PAIR)
                return(0); // IO_control list error
            kwe = isSgKeywordValExp(ee->lhs());
            if (!kwe)
                return(0);
            if (!strcmp(kwe->value(), "unit"))
                ioc[UNIT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "iostat"))
                ioc[IOSTAT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "err"))
                ioc[ERR_] = ee->rhs();
            else
                return(0);
        }
        return(1);
    }
    else
        return(0);
}

int IOcontrol(SgExpression *e, SgExpression *ioc[], int type)
// analizes IO_control list (e) and sets on ioc[]
{
    SgKeywordValExp *kwe;
    SgExpression *ee, *el;
    if (e->variant() == SPEC_PAIR) {
        if (type == PRINT_STAT)
            ioc[FMT_] = e->rhs();
        else {
            // ioc[UNIT_] = e->rhs();
            kwe = isSgKeywordValExp(e->lhs());
            if (!kwe)
                return(0);
            if (!strcmp(kwe->value(), "unit"))
                ioc[UNIT_] = e->rhs();
            else if (!strcmp(kwe->value(), "fmt"))
                ioc[FMT_] = e->rhs();
            else
                return(0);
        }
        return(1);
    }

    if (e->variant() == EXPR_LIST) {
        for (el = e; el; el = el->rhs()) {
            ee = el->lhs();
            if (ee->variant() != SPEC_PAIR)
                return(0); // IO_control list error
            kwe = isSgKeywordValExp(ee->lhs());
            if (!kwe)
                return(0);
            if (!strcmp(kwe->value(), "unit"))
                ioc[UNIT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "fmt"))
                ioc[FMT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "nml"))
                ioc[NML_] = ee->rhs();
            else if (!strcmp(kwe->value(), "rec"))
                ioc[REC_] = ee->rhs();
            else if (!strcmp(kwe->value(), "iostat"))
                ioc[IOSTAT_] = ee->rhs();
            else if (!strcmp(kwe->value(), "end"))
                ioc[END_] = ee->rhs();
            else if (!strcmp(kwe->value(), "err"))
                ioc[ERR_] = ee->rhs();
            else if (!strcmp(kwe->value(), "eor"))
                ioc[EOR_] = ee->rhs();
            else if (!strcmp(kwe->value(), "size"))
                ioc[SIZE_] = ee->rhs();
            else if (!strcmp(kwe->value(), "advance"))
                ioc[ADVANCE_] = ee->rhs();
            else
                return(0);
        }
        return(1);
    }
    else
        return(0);
}

int TestIOList(SgExpression *iol, SgStatement *stmt)
{
    SgExpression *el, *e;
    int tst = 1;
    for (el = iol; el; el = el->rhs()) {
        e = el->lhs();  // list item
        if (isSgExprListExp(e)) // implicit loop in output list
            e = e->lhs();
        if (isSgIOAccessExp(e)) {
            tst = ImplicitLoopTest(e, stmt) ? tst : 0;
        }
        else
        {
            tst = IOitemTest(e, stmt) ? tst : 0;
            RefInExpr(e, use_mode);
        }
    }
    return (tst);
}

int ImplicitLoopTest(SgExpression *eim, SgStatement *stmt)
{
    int tst = 1;
    SgExpression *ell, *e;

    has_implicit_loop = 1;

    if (isSgExprListExp(eim->lhs()))
        for (ell = eim->lhs(); ell; ell = ell->rhs()) { //looking through item list of implicit loop
            e = ell->lhs();
            if (isSgExprListExp(e)) // implicit loop in output list
                e = e->lhs();
            if (isSgIOAccessExp(e)) {
                tst = ImplicitLoopTest(e, stmt) ? tst : 0;
            }
            else
                tst = IOitemTest(e, stmt) ? tst : 0;
        }
    else
        tst = IOitemTest(eim->lhs(), stmt) ? tst : 0;
    return(tst);
}

int IOitemTest(SgExpression *e, SgStatement *stmt)
{
    int tst = 1;
    if (!e) return(1);
    if (isSgArrayRefExp(e)) {
        //if( HEADER(e->symbol())) {
        //    Error("Illegal I/O list item: %s",e->symbol()->identifier(),192,stmt);
        //    return (0);
        //} else
        return(1);
    }
    if (e->variant() == ARRAY_OP) //substring
        return(IOitemTest(e->lhs(), stmt));
    if (isSgVarRefExp(e))
        return(1);
    if (isSgValueExp(e))
        return(0);

    tst = IOitemTest(e->lhs(), stmt) ? tst : 0;
    tst = IOitemTest(e->rhs(), stmt) ? tst : 0;
    return(tst);
}

int OperWithLab(SgLabel *lab)
{
    label_oper *lo;
    char erbuf[40];
    for (lo = lab_list; lo; lo = lo->next)
        if (lo->num == LABEL_STMTNO(lab->thelabel))
            return(lo->oper);

    sprintf(erbuf, "Label %d is not defined", LABEL_STMTNO(lab->thelabel));
    err(erbuf, 4, cur_st);
    return(0);

}

int idOfOper(SgStatement *stmt)
{
    if (OPER(stmt))
        return(*OPER(stmt));
    ErrMessage("No id for operator", stmt->lineNumber());
    return(0);
}

/*
void TestReduction(SgStatement *stmt)
{ SgExpression *le, *re;
SgSymbol *s;
SgStatement *loop;
le = stmt->expr(0);
re = stmt->expr(1);
if(!isSgVarRefExp(le) && !isSgArrayRefExp(le))
return;
s = le->symbol();
//stmt->unparsestdout();
loop = ParentLoop(stmt);
if(!loop)
return;
switch(re->variant())
{
case(FUNC_CALL):
{ int maxmin;

//if(!isIntrinsicFunctionName(re->symbol()->identifier()))
//   return;
maxmin = isMaxMinFunc(re->symbol()->identifier());
//loop = ParentLoop(stmt);
if(maxmin && TestArgsRedOp(le,re->lhs()) )
{  redop *p = new redop;
p->oper = maxmin;
p->symb = s;
p->red_stat = stmt;
loop->addAttribute(RED_OP, (void *) p, sizeof(redop));
//printf("YES\n");
}
}
break;
case(ADD_OP):
{ if( TestRedArg(le,re->lhs()) || TestRedArg(le,re->rhs()) )
AddReductionAttribute(loop, 3, stmt, s);
}
break;
case(SUBT_OP):
{ if( TestRedArg(le,re->lhs()) )
AddReductionAttribute(loop, 3, stmt, s);
}
break;
case(MULT_OP):
{ if( TestRedArg(le,re->lhs()) || TestRedArg(le,re->rhs()) )
AddReductionAttribute(loop, 4, stmt, s);
}
break;
case(OR_OP):
{ if( TestRedArg(le,re->lhs()) || TestRedArg(le,re->rhs()) )
AddReductionAttribute(loop, 5, stmt, s);
}
break;
case(AND_OP):
{ if( TestRedArg(le,re->lhs()) || TestRedArg(le,re->rhs()) )
AddReductionAttribute(loop, 6, stmt, s);
}
break;

default:
break;
}
return;
}
*/

void TestReduction(SgStatement *stmt)
{
    SgExpression *le, *re, *cond;
    SgSymbol *s;
    SgStatement *loop, *parent, *redst;
    int iop, iv;
    //printf("test reduction\n");
    iop = 0;  // number of reduction operation
    le = stmt->expr(0);
    re = stmt->expr(1);
    if (!isSgVarRefExp(le)) // && !isSgArrayRefExp(le)) 
        return;
    s = le->symbol();
    //stmt->unparsestdout();
    loop = ParentLoop(stmt);

    if (!loop)
        return;
    //printf("loop: %d\n", loop->lineNumber());
    if (!TestVarRef(s, re))   // there are not left-part-variable references in right part of assignment 
    {
        parent = stmt->controlParent();
        if ((parent->variant() == LOGIF_NODE || parent->variant() == IF_NODE) && TestRedCondition(parent->expr(0)->variant()))
        {
            iv = parent->expr(0)->variant();
            cond = parent->expr(0);
            if (ExpCompare(le, cond->lhs()) && ExpCompare(re, cond->rhs()))
            {
                iop = (iv == LT_OP || iv == LE_OP) ? 1 : 2; // 1 - max, 2 - min
                redst = parent; goto ADD_RED;
            }
            else if (ExpCompare(le, cond->rhs()) && ExpCompare(re, cond->lhs()))
            {
                iop = (iv == LT_OP || iv == LE_OP) ? 2 : 1; // 1 - max, 2 - min
                redst = parent; goto ADD_RED;
            }
        }
        return;
    }
    redst = stmt;
    switch (re->variant())
    {
    case(FUNC_CALL):
    { int maxmin;
    maxmin = isMaxMinFunc(re->symbol()->identifier());
    if (maxmin && TestArgsRedOp(le, re->lhs()))
        iop = maxmin;
    }
    break;
    case(ADD_OP):
    { if (isOperandOfOper(le, re, ADD_OP))
        // if( ExpCompare(le,re->lhs()) || ExpCompare(le,re->rhs()) )
        iop = 3;
    }
    break;
    case(SUBT_OP):
    { if (ExpCompare(le, re->lhs()))
        iop = 3;
    }
    break;
    case(MULT_OP):
    { if (isOperandOfOper(le, re, MULT_OP))
        //if( ExpCompare(le,re->lhs()) || ExpCompare(le,re->rhs()) )
        iop = 4;
    }
    break;
    case(OR_OP):
    { if (isOperandOfOper(le, re, OR_OP))
        //if( ExpCompare(le,re->lhs()) || ExpCompare(le,re->rhs()) )
        iop = 5;
    }
    break;
    case(AND_OP):
    { if (isOperandOfOper(le, re, AND_OP))
        //if( ExpCompare(le,re->lhs()) || ExpCompare(le,re->rhs()) )
        iop = 6;
    }
    break;

    default:
        break;
    }

ADD_RED:
    if (iop)
    {
        redop *p = new redop;
        p->oper = iop;
        p->symb = s;
        p->red_stat = redst;
        p->next = NULL;
        loop->addAttribute(RED_OP, (void *)p, sizeof(redop));
        //printf("YES\n");
    }

    return;
}

int TestRedCondition(int vrnt)
{
    switch (vrnt)
    {
    case(GTEQL_OP):      //.GE.
    case(GT_OP):
    case(LTEQL_OP):      //.LE.
    case(LT_OP):
        return(1);
    default:
        return(0);
    }
}

int TestArgsRedOp(SgExpression *rve, SgExpression *args)
{
    SgExpression *el;
    for (el = args; el; el = el->rhs())
        if (ExpCompare(el->lhs(), rve))
            return(1);
    return(0);
}

int TestRedArg(SgExpression *rve, SgExpression *arg)
{
    if (ExpCompare(arg, rve))
        return(1);
    else
        return(0);
}

void AddReductionAttribute(SgStatement *loop, int iop, SgStatement *redst, SgSymbol *sr)
{
    redop *p = new redop;
    p->oper = iop;
    p->symb = sr;
    p->red_stat = redst;
    p->next = NULL;
    loop->addAttribute(RED_OP, (void *)p, sizeof(redop));
}

SgStatement *ParentDo(SgStatement *st)
{
    SgStatement *parent;
    parent = st->controlParent();
    while (parent->variant() != FOR_NODE && parent != cur_func)  // parent->variant()!=FUNC_HEDR,PROC_HEDR,PROG_HEDR
    {
        parent = parent->controlParent();
    }
    return(parent);
}

SgStatement *ParentLoop(SgStatement *st)
{
    SgStatement *parent;
    parent = st->controlParent();
    while (parent->variant() != FOR_NODE && parent != cur_func)  // parent->variant()!=FUNC_HEDR,PROC_HEDR,PROG_HEDR
    {
        parent = parent->controlParent();
    }
    if (parent->variant() == FOR_NODE)
        return(parent);
    else
        return(NULL);
}

void ReductionOperations(SgStatement *st)
{
    int n, i;
    redop *p;
    if (!REDOP(st))
        return;
    n = st->numberOfAttributes(RED_OP);
    for (i = 0; i<n; i++)
    {
        p = (redop *)st->attributeValue(i, RED_OP);
    }
    return;
}

void  RetestReduction(SgStatement *loop)
{
    SgSymbol *sr;
    redop *p;
    int i, n;
    if (!REDOP(loop))
        return;
    n = loop->numberOfAttributes(RED_OP);
    AnalyzeReductions(loop, n);
    for (i = 0; i<n; i++)
    {
        p = (redop *)loop->attributeValue(i, RED_OP);
        sr = p->symb;
        if (!sr) continue;
        if (isSgArrayType(sr->type()))  // reduction array-variable is not determined
            continue;
        //printf("reduction: %s\n",sr->identifier());
        TestSymbRed(p, loop);
    }

}

void TestSymbRed(redop *p, SgStatement *loop)
{
    SgStatement *stmt, *end, *redst;
    SgSymbol *sr;
    int test;
    redop *pl;
    sr = p->symb;
    if (!sr)
        return;
    //redst = p->red_stat;
    test = 0;
    end = lastStmtOfDo(loop)->lexNext();
    for (stmt = loop->lexNext(); stmt != end; stmt = stmt->lexNext())
    {
        pl = p;  //printf("line: %d\n", stmt->lineNumber());
    TEST_RED_STAT:
        redst = pl->red_stat;
        //redst->unparsestdout(); 
        if (stmt == redst)
        {
            if (redst->variant() == LOGIF_NODE)
                stmt = stmt->lexNext();
            if (redst->variant() == IF_NODE)
                stmt = stmt->lastNodeOfStmt();

            continue;
        }
        else
        {
            pl = pl->next;
            if (pl)
                goto TEST_RED_STAT;
        }
        switch (stmt->variant())
        {
        case ASSIGN_STAT:           // Assign statement
        case FOR_NODE:
        case COMGOTO_NODE:          // Computed GO TO
            test = test || TestVarRef(sr, stmt->expr(1));
        case SWITCH_NODE:           // SELECT CASE ...
        case ARITHIF_NODE:          // Arithmetical IF
        case IF_NODE:               // IF... THEN
        case WHILE_NODE:            // DO WHILE (...)
        case CASE_NODE:             // CASE ...
        case ELSEIF_NODE:           // ELSE IF...
        case LOGIF_NODE:            // Logical IF
        case READ_STAT:             // Read
        case PROC_STAT:             // CALL 
            test = test || TestVarRef(sr, stmt->expr(0));
            break;
        default:
            break;
        }
    } //end for
    if (!test) // reduction variable is used inside loop in reduction statement only 
        put_in_depends(*LOOP(loop), "REDUCTION", idOfVars(sr), TextOp(p->oper));
}

char *TextOp(int iop)
{
    switch (iop)
    {
    case(1): return("max");
    case(2): return("min");
    case(3): return("sum");
    case(4): return("product");
    case(5): return("or");
    case(6): return("and");

    default: return("NO");
    }
    return("NO");
}


int TestVarRef(SgSymbol *s, SgExpression *e)
{
    int i, use, call;
    SgExpression *el;
    int *id;
    if (!e)
        return(0);
    if (isSgVarRefExp(e))
    {
        if (e->symbol() == s)
            return(1);
        else
            return(0);
    }
    if (isSgArrayRefExp(e))
    {
        if (e->symbol() == s)
            return(1);
        return(TestVarRef(s, e->lhs()));
    }

    return(TestVarRef(s, e->lhs()) || TestVarRef(s, e->rhs()));

}

void AnalyzeReductions(SgStatement *loop, int n)
{
    SgStatement *stmt, *redst;
    SgSymbol *sr;
    redop *p, *p2;
    int i, j;
    //loop->unparsestdout();
    for (i = 0; i<n; i++)
    {               //printf("i:%d\n",i);
        p = (redop *)loop->attributeValue(i, RED_OP);
        sr = p->symb;
        if (!sr) continue;
        for (j = i + 1; j<n; j++)
        {
            p2 = (redop *)loop->attributeValue(j, RED_OP);
            if (p2->symb == sr && p2->oper == p->oper)
            {          //printf("j:%d\n",j);
                p2->symb = NULL;
                p->next = p2;
                p = p2;
            }

        }
    }

}

int isOperandOfOper(SgExpression *ev, SgExpression *e, int oper)
{
    int op;
    // is ev operand of multi-operation oper:  a1 .oper. a2 .oper. ... .oper. an
    SgExpression *e1, *e2;
    op = e->variant();
    if (op != oper) return(0);

    if (ExpCompare(ev, e->lhs()) || ExpCompare(ev, e->rhs()))
        return(1);
    return(isOperandOfOper(ev, e->lhs(), oper) || isOperandOfOper(ev, e->rhs(), oper));
}

void AnalyzeComment(SgStatement *stmt)
{
    char *cmnt, *p, *line;
    int nline, n, nprg;
    char *prg_line[200];

    cmnt = stmt->comments();
    if (!cmnt)
        return;

    p = cmnt;
    line = cmnt;
    n = nline = nprg = 0;

    while (*p != '\0')
    {
        n++;
        if (eqn(3, p + 1, "prg"))
        {
            nprg = n;
            prg_line[n] = p;
            *p = 'C';
        }
        else
        {
            prg_line[n] = NULL;
        }
        while (*p != '\n')
            p++;
        p++;
    }
    nline = n;
    //printf("%d:%d\n%s",stmt->lineNumber(),nline,cmnt);
    if (!nprg)
        return;
    for (n = 1; n <= nline; n++)
    {
        if (prg_line[n] != NULL)
        {
            p = prg_line[n];
            while (*p != '\n')
                p++;
            *p = '\0';
            nprg = (stmt->lineNumber()) - nline + n - 1;
            put_in_userdir(idOfOper(stmt), nprg, prg_line[n]);
            *p = '\n';

        }
    }
}

void TestingCommon()
{
    commonblock *com, *rcom;
    if (!first_common || !routine_common)
        return;

    for (rcom = routine_common; rcom; rcom = rcom->next)
        for (com = first_common; com != rcom; com = com->next)
            if (rcom->id == com->id)
                CompareCommonDefinitions(rcom->list, com->list);
    //CompareCommonDefs(rcom,com);
}

/*
int CompareObjects2(SgExpression *re, SgExpression *e, int flag)
{ SgType *t,*rt;
//printf("compareObjects2: %s , %s\n", BIF_SYMB(e->thellnd)->ident,re->symbol()->identifier() );
flag=CompareObjects(SymbMapping(BIF_SYMB(e->thellnd)),re->symbol(),flag);
return(flag);
}
*/

void CompareCommonDefinitions(commonlist *rcoml, commonlist *coml)
{//SgExpression *cl, *rcl, *e, *re;
    SgSymbol *s, *rs;
    int flag = 1;
    commonlist *cl, *rcl;
    for (cl = coml, rcl = rcoml; rcl; rcl = rcl->next, cl = cl->next)
        flag = CompareCommonObjects(rcl, cl, flag);
}
/*
void CompareCommonDefs(commonblock *rcom, commonblock *com)
{SgExpression *cl, *rcl, *e, *re;
SgSymbol *s, *rs;
int flag = 1;

cl = com->comlist;

rcl=rcom->comlist;


for(; rcl; rcl=rcl->rhs(),cl=cl->rhs())
{  e= cl->lhs();  s = e->symbol();


re=rcl->lhs(); rs =re->symbol();
flag=CompareObjects2(re,e,flag);
//flag=CompareObjects(rs,s,flag);
}
}

int CompareObjects(SgSymbol *rs, SgSymbol *s, int flag)
{ SgType *t,*rt;

if(!flag)
{ if(!HAS_ASSOCIATION_ATR(rs))
{  put_in_atr(idOfVars(rs),ASSOCIATION_);
SYMB_ATTR(rs->thesymb)= SYMB_ATTR(rs->thesymb) | ASSOCIATION_BIT;
}
if(!HAS_ASSOCIATION_ATR(s))
{  put_in_atr(idOfVars(s), ASSOCIATION_);
SYMB_ATTR(s->thesymb)= SYMB_ATTR(s->thesymb) | ASSOCIATION_BIT;
}
return(flag);
}
if(SameObjects(rs,s))
return(1);
else
{ if(!HAS_ASSOCIATION_ATR(rs))
{  put_in_atr(idOfVars(rs),ASSOCIATION_);
SYMB_ATTR(rs->thesymb)= SYMB_ATTR(rs->thesymb) | ASSOCIATION_BIT;
}
if(!HAS_ASSOCIATION_ATR(s))
{  put_in_atr(idOfVars(s), ASSOCIATION_);
SYMB_ATTR(s->thesymb)= SYMB_ATTR(s->thesymb) | ASSOCIATION_BIT;
}
return(0);
}
*/


int CompareCommonObjects(commonlist *rcl, commonlist *cl, int flag)
{
    if (!flag)
    {
        if (!(rcl->atr))
        {
            put_in_atr(rcl->id, ASSOCIATION_);
            rcl->atr = 1;
        }
        if (!(cl->atr))
        {
            put_in_atr(cl->id, ASSOCIATION_);
            cl->atr = 1;
        }
        return(flag);
    }
    if (SameCommonObjects(rcl, cl))
        return(1);
    else
    {
        if (!(rcl->atr))
        {
            put_in_atr(rcl->id, ASSOCIATION_);
            rcl->atr = 1;
        }
        if (!(cl->atr))
        {
            put_in_atr(cl->id, ASSOCIATION_);
            cl->atr = 1;
        }
        return(0);
    }

}

SgType *Base_Type(SgType *t)
{
    SgArrayType *artype;
    artype = isSgArrayType(t);
    if (artype)
        t = artype->baseType();
    return(t);
}

int SameObjects(SgSymbol *rs, SgSymbol *s)
{
    SgExpression *len, *rlen;
    SgType *t, *rt;
    SgArrayType *artype, *rartype;
    // comparing names
    if (strcmp(rs->identifier(), s->identifier()))
        return(0);
    // comparing types
    t = s->type(); rt = rs->type();
    if (t->variant() != rt->variant())
        return(0);
    artype = isSgArrayType(t); rartype = isSgArrayType(rt);
    if (artype)
    {
        if (Rank(s) != Rank(rs))
            return(0);
        if (!CompareDims(artype, rartype))
            return(0);
        t = Base_Type(s->type());
        rt = Base_Type(rs->type());
        if (t->variant() != rt->variant())
            return(0);
    }
    len = TypeLengthExpr(t);
    rlen = TypeLengthExpr(rt);
    if (len != rlen)
        return(0);

    return(1);
}

int SameCommonObjects(commonlist *rcl, commonlist *cl)
{
    int i;
    // comparing variable's names
    if (strcmp(rcl->name, cl->name))
        return(0);
    // comparing variable's types
    if (rcl->type != cl->type)
        return(0);
    if (rcl->len != cl->len)
        return(0);
    // comparing array's types
    if (rcl->rank != cl->rank)
        return(0);
    for (i = 0; i<rcl->rank; i++)
    {
        if (rcl->lbound[i] != cl->lbound[i])
            return(0);
        if (rcl->rbound[i] != cl->rbound[i])
            return(0);
    }

    return(1);
}

int CompareDims(SgArrayType *artype1, SgArrayType *artype2)
{
    int n, i;
    SgExpression *e1, *e2;
    n = artype1->dimension();
    for (i = 0; i<n; i++)
    {
        e1 = Calculate(LowerBound(artype1, i));
        e2 = Calculate(LowerBound(artype2, i));
        if (!ExpCompare(e1, e2))
            return(0);
        e1 = Calculate(UpperBound(artype1, i));
        e2 = Calculate(UpperBound(artype2, i));
        if (!ExpCompare(e1, e2))
            return(0);
    }
    return(1);
}

commonlist *Create_Common_List(SgExpression *elist)
{
    commonlist *cfirst, *cl, *clast;
    SgExpression *el;

    cfirst = NULL; //new commonlist;
    clast = NULL;
    for (el = elist; el; el = el->rhs())
    {
        cl = createElementList(el->lhs());
        if (!cfirst)
            cfirst = cl;
        if (clast)
            clast->next = cl;
        clast = cl;
    }
    return(cfirst);
}

commonlist *Connect_Common_List(commonlist *clist, SgExpression *elist)
{
    commonlist  *cl, *c2;
    c2 = Create_Common_List(elist);
    if (!clist)
        return(c2);
    cl = clist;
    while (cl->next)
        cl = cl->next;
    cl->next = c2;
    return(clist);
}

commonlist *createElementList(SgExpression *e)
{
    commonlist *ecl;
    SgSymbol *svar;
    int l;
    char *varname;
    SgType *t;
    SgExpression *elen;

    svar = e->symbol();
    ecl = new commonlist;
    ecl->next = NULL;
    if (!svar)
    {
        ecl->id = 0;
        return(ecl);
    }
    l = strlen(svar->identifier());
    varname = new char[l + 1];
    strcpy(varname, svar->identifier());
    ecl->name = varname;
    ecl->id = idOfVars(svar);
    ecl->atr = 0;
    t = Base_Type(svar->type());
    ecl->type = NumbOf(t);

    ecl->len = ValueOf(TypeLengthExpr(t));
    ecl->rank = Rank(svar);

    if (ecl->rank)
        Bounds(ecl->rank, isSgArrayType(svar->type()), ecl->lbound, ecl->rbound);

    return(ecl);
}

void Bounds(int n, SgArrayType *artype, int lbound[], int rbound[])
{
    int i;
    for (i = 0; i<n; i++)
    {
        lbound[i] = ValueOf(Calculate(LowerBound(artype, i)));
        rbound[i] = ValueOf(Calculate(UpperBound(artype, i)));
    }
}

int ValueOf(SgExpression *e)
{
    if (e->isInteger())
        return(e->valueInteger());
    else
        return(-1);
}

int NumbOf(SgType *t)
{
    switch (t->variant()) {
    case T_INT:      return (1);
    case T_BOOL:     return (2);
    case T_FLOAT:    return (3);
    case T_DOUBLE:   return (4);
    case T_COMPLEX:  return (5);
    case T_DCOMPLEX: return (6);

    case T_STRING:
    case T_CHAR:     return (7);

    case T_DERIVED_TYPE:
        return (8);

    default:         return (0);
    }

}
//-----------------------------------------------------------------------------------
//                          Dependence Test                                        
//-----------------------------------------------------------------------------------
void dep_loop_header(SgStatement *stmt)
{
    SgStatement *next, *prev, *parent, *stdo;
    int ndo = 1;
    //while(next->variant()==FORMAT_STAT || next->variant()==DATA_DECL)
    //     next=next->lexNext();
    // stmt->unparsestdout();
    next = stmt->lexNext(); //NextExecStat(stmt);
    if (isSgForStmt(next))
        return;

    for (parent = stmt->controlParent(), stdo = stmt; isSgForStmt(parent) && parent->lexNext() == stdo; stdo = parent, parent = parent->controlParent())
        ndo++;
    // stdo - first header of tightly nested loops
    DEP_ADD__LOOP(NLoop, NLoop, ndo, stdo->lineNumber())
        add_index_var(stdo);

    /*  parent = stmt->controlParent();
    prev =  (isSgForStmt(parent) && parent->lexNext()==stmt) ?  :
    if(next->variant() == FOR_NODE)
    return;
    stdo=NULL:
    //if(lab )
    //looking through the nest of loops
    for(parent=stmt->controlParent(); isSgForStmt(parent); stdo=parent,parent= parent->controlParent())

    if((labdo=((SgForStmt *)parent)->endOfLoop()) && LABEL_STMTNO(lab->thelabel) == LABEL_STMTNO(labdo->thelabel))
    { if(parent->lexNext() == stdo) // the loop header follows enclosing loop header
    tightly =1;
    DEP_ADD__LOOP(NLoop,NLoop,1,stmt->lineNumber())
    */
    return;

}

void dep_loop_end(SgStatement *stmt)
{
    SgStatement *parent, *stdo, *next;
    SgForStmt *do_parent;
    SgLabel *lab, *labdo;

    next = (stmt->variant() != LOGIF_NODE) ? NextExecStat(stmt) : NextExecStat(stmt->lexNext());
    lab = stmt->label();
    parent = stmt->controlParent();
    labdo = ((SgForStmt *)parent)->endOfLoop();
    if (labdo)
    {
        for (parent = stmt->controlParent(); isSgForStmt(parent); parent = parent->controlParent())
            if ((labdo = ((SgForStmt *)parent)->endOfLoop()) && LABEL_STMTNO(lab->thelabel) == LABEL_STMTNO(labdo->thelabel))
            {
                nclosed++; stdo = parent;
                if (nclosed == dep_rank[l_i])
                {
                    DEP_CLOSE__LOOP(parent->lineNumber(), stmt->lineNumber())
                }
            }
            else
                break;

    }
    else
    {
        nclosed++; stdo = parent;
        /*  if(nclosed==dep_rank[l_i])
        {  DEP_CLOSE__LOOP(parent->lineNumber(),stmt->lineNumber())
        return;
        }
        parent = parent->controlParent();
        */
    }
    if (!nclosed)
        return;
    if (nclosed == dep_rank[l_i])
    {
        DEP_CLOSE__LOOP(stdo->lineNumber(), stmt->lineNumber())
            return;
    }
    parent = stdo->controlParent();
    printf("%d  %d    %d\n", next->controlParent() == parent, isSgForStmt(parent), (next->variant() == CONT_STAT || next->variant() == CONTROL_END));
    if (next->controlParent() == parent && isSgForStmt(parent) &&
        (next->variant() == CONT_STAT || next->variant() == CONTROL_END))
    {
        printf("YES\n");  return;
    }
    //if(nclosed!=dep_rank[l_i])
    {
        DEP_SPLIT__LOOP(NLoop, nclosed, stdo->lineNumber(), stmt->lineNumber())
    }
    // else
    // { 
    //   DEP_CLOSE__LOOP(stdo->lineNumber(),stmt->lineNumber())
    // }
    return;
}


//void dep_loop_push(TightlyNestedLoops *lp, int rank)
void dep_loop_push(ProgramUnit *lp, int rank)

{
    dep_loop[++l_i] = lp;
    dep_rank[l_i] = rank;
}

void dep_loop_pop()
{
    NLoop = dep_loop[--l_i];
}

void add_index_var(SgStatement *st)
{
    int n;
    SgForStmt *stdo = isSgForStmt(st);
    IndexVariable *ivar;
    SgExpression *estep;

    n = dep_rank[l_i];
    while (n-- && stdo)
    {
        estep = stdo->step();
        if (!estep)
            estep = VAL_1;
        stdo->start()->unparsestdout(); printf(", "); stdo->end()->unparsestdout(); printf(", "); estep->unparsestdout();
        printf(" :  %s [loopid=%d] line=%d\n", stdo->symbol()->identifier(), *LOOP(stdo), stdo->lineNumber());
        ivar = new IndexVariable(idOfVars(stdo->symbol()), *LOOP(stdo), new ISgExpression(stdo->start()), new ISgExpression(stdo->end()), new ISgExpression(estep), true);
        ((TightlyNestedLoops *)dep_loop[l_i])->AddIndexVariable(ivar, true);
        stdo = isSgForStmt(stdo->lexNext());
    }
}


MemoryUnit *dep_add_memory_unit(SgSymbol *s, int varid)
{
    MemoryUnit *mu;
    SgArrayType *artype;
    int i, n, il, iu;
    SgExpression *el, *eu;

    artype = isSgArrayType(s->type());
    if (!artype)
        mu = new ScalarUnit(varid);

    else
    {
        n = artype->dimension();
        mu = new ArrayUnit(varid, n);

        for (i = 0; i<n; i++)
        {
            el = LowerBound(artype, i);
            if (!el)
                continue;
            eu = UpperBound(artype, i);
            if (!eu)
                continue;
            ((ArrayUnit*)mu)->AddDimension(i, new ISgExpression(el), new ISgExpression(eu), true);
        }

    }
    s->addAttribute(M_UNIT, (void *)mu, sizeof(MemoryUnit));

    return(mu);
}

MemoryUnitUsage *dep_add_scalar_usage(SgExpression *ref, int mode)
{
    MemoryUnit *mu;
    MemoryUnitUsage *muse;
    SgSymbol *s;
    s = ref->symbol();
    mu = MEM_UNIT(s);
    muse = new ScalarUsage((UsageType)mode);
    mu->AddUsage(muse, true);
    printf("usage %s: mode=%d\n", s->identifier(), mode);
    if (!(dep_loop[l_i]->IsUse(mu))) //GetFirstUsage(mu)))
    {
        printf("add first usage %s\n", s->identifier());
        dep_loop[l_i]->AddMUFirstUsage(mu);
        //printf("end add first usage %s\n",s->identifier());    
    }

    return(muse);
}

ArrayUsage *dep_add_array_usage(SgExpression *ref, int mode)
{
    MemoryUnit *mu;
    MemoryUnitUsage *muse;
    SgSymbol *s;
    s = ref->symbol();
    mu = MEM_UNIT(s);
    muse = new ArrayUsage((UsageType)mode, NumberOfIndexes(ref));
    mu->AddUsage(muse, true);
    printf("usage %s: mode=%d\n", s->identifier(), mode);
    if (!(dep_loop[l_i]->IsUse(mu))) //GetFirstUsage(mu)))
    {
        printf("add first usage %s\n", s->identifier());
        dep_loop[l_i]->AddMUFirstUsage(mu);
        //printf("end add first usage %s\n",s->identifier());
    }
    return((ArrayUsage*)muse);
}

int NumberOfIndexes(SgExpression *ref)
{
    int n = 0;
    SgExpression *el;
    for (el = ref->lhs(); el; el = el->rhs())
        n++;
    return(n);
}

void dep_add_index_expr(ArrayUsage *dep_use, int dim, SgExpression *ei)
{
    dep_use->AddIndexExpr(dim, new ISgExpression(ei), true);
}

void printUsage(MemoryUnitUsage *muse, int isArray)
{
    if (!isArray)
        return;

}

void dep_print_mu_list(MemoryUnit *mu, int isArray)
{
    MemoryUnitUsage *muse;
    muse = mu->GetFirstUsage();
    while ((muse->GetNextUsage()))
        printUsage(muse, isArray);
}

void dep_print_usage_lists(SgStatement *func)
{
    SgSymbol *s;
    SgStatement *next_func;
    MemoryUnit *mu;
    int isArray;
    printf("*****%s*****\n", func->symbol()->identifier());
    next_func = func->lastNodeOfStmt()->lexNext();
    for (s = func->symbol(); s != NULL && s->scope() != next_func; s = s->next())
    {
        isArray = (isSgArrayType(s->type()) ? 1 : 0);
        if ((mu = MEM_UNIT(s)))
            dep_print_mu_list(mu, isArray);
    }
}

int DepMode(int mode)
{
    if (mode == NUL_)
        return(UNKNOWN);
    else if (mode == READ_)
        return(READ);
    else
        return(WRITE);
}

int dep_add_dummies(SgStatement *func)
{
    PTR_SYMB  dummy;
    SgSymbol *darg, *sf;
    int i;
    MemoryUnit *mu;
    sf = func->symbol(); printf("add dummies to %s\n", sf->identifier());
    dummy = sf->thesymb->entry.proc_decl.in_list;
    i = 0;
    if (func->variant() != PROG_HEDR)
    {
        while (dummy)
        {
            darg = SymbMapping(dummy);
            mu = MEM_UNIT(darg);
            ((PURoutine *)NLoop)->AddFormalParameter(mu);
            //deprnode[id_routines]->AddFormalParameter(mu);    
            dummy = dummy->entry.var_decl.next_in;
            i++;
        }
    }
    return i;
}

void dep_add_paramsNumber(int n)
{
    ((PURoutine *)NLoop)->SetParamsNumber(n);
}


PURoutineCall *dep_add_call(SgSymbol *s)
{
    int routine_id, n;
    PURoutineCall *dep_call;
    //printf("ADD CALL\n");
    dep_params = NULL;
    routine_id = idOfRoutines(s);
    //printf("ADD CALL %d,%d,%d\n",routine_id,deprnode[routine_id],NLoop);
    if (!routine_id || !deprnode[routine_id])
        return(NULL);
    n = depnum[routine_id];
    dep_call = NLoop->AddRoutineCall(deprnode[routine_id]);
    //printf("ADD CALL  %s: %d (%d) \n",rname[routine_id],depnum[routine_id],n); 
    return(dep_call);
}

void dep_argument(SgSymbol *s, PURoutineCall *dep_call, int i)
{
    printf("add_argument %s,  %d   %d\n", s->identifier(), i, dep_muse);
    if (dep_call)
        dep_call->AddParameter(MEM_UNIT(s), dep_muse, i);
}


