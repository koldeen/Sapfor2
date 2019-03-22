/*
*   Simple SQL-engine wrapper.
*   --------------------------
*   Only one data-base can be opened at a time.
*   Only one table of the current DB can be read at a time.
*   The table is read as a whole. (Memory is freed automatically.)
*   All the data are put|get as character strings.
*   NOTE, that NULL value is something different
*       from an empty string (strlen==0) as the value !
*
*   It should be compiled and statically linked with an application.
*/

// History

// 21.04.08 All fields of type TEXT renamed to T_<old name>

//  12.10.2007 V 0.7 The list of table completely revised
//	"DVM-expert interface" v.3.3 of 12.10.2007
//	Change "#if 1" to "#if 0" (see below) to get the previous version
//////////////////////
//  12.03.2007 V 0.62
//  10.03.2007 V 0.61   fixed spelling
//  20.02.2007 V 0.6
//  -- extentions for SUBROUTINE's and COMMON's
//  -- postfix form of expressions
//  26.05.2006 V 0.1
//  -- print SQL-stmts WITH execution (not "instead of" as before)
//  -- vrd_flush()  splits to transactions (to minimize disk operations)
//  15.05.2006 V 0.0
//  -- the first release

/*
*   This wrapper will be compiled in DEBUGGING MODE
*   if the following define is commented:
*/
#define VRDB
/*
*   In this case no external headers, or libs, or dlls required !
*   Otherwise, the following should be accesible:
*   -- sqlite.h     -- for compiler
*   -- sqlite.lib   -- for linker
*   -- sqlite.dll   -- at execution
*   "Debugging mode" (default) then can be turned off by setting: vrdb_deb=0
*/
extern int vrdb_deb = 0;    // 1 ==> print SQL-commands to <proj>.deb

/***********************************************************/

#include <stdlib.h>
#include <stdio.h>

#ifdef VRDB
#define DLLSPEC _declspec(dllimport)
#include "sqlite.h"
sqlite* curdb=NULL;       // current opened database
char ** vrdb_result=NULL; // current read table data
#endif

FILE * deb;

/*
*   VRDB database schema supposed by this program.
*   (Will be compared with the schema of an opened database file.)
*/

char *schema[] = {
//
// "#if 0" generates the previous version. See "#else"
//
#if 1
/******************************************* 12.10.2007 *********/
"CREATE TABLE -- ИНТЕРФЕЙС DVM-ЭКСПЕРТА  (версия 3.3, Клинов 11.10.07)\n"
"files(\n"
"id INT PRIMARY KEY,\n"
"T_filename\n"
");\n",
"CREATE TABLE routines(\n"
"id INT PRIMARY KEY,\n"
"T_ident,\n"
"file,  -- id таблицы files\n"
"line,  -- номер строки с заголовком ПЕ в файле\n"
"root  -- id таблицы loops, задающий корень дерева циклов для ПЕ\n"
");\n",
"CREATE TABLE vars (\n"
"id INT PRIMARY KEY,\n"
"T_ident,\n"
"routine, -- id таблицы routines\n"
"T_type, -- текстовое представление типа (\n"
"-- INTEGER, INTEGER*2, INTEGER*4, INTEGER*8,\n"
"-- REAL, REAL*4, REAL*8, DOUBLEPRECISION,\n"
"-- COMPLEX, DOUBLECOMPLEX, COMPLEX*16,\n"
"-- LOGICAL, LOGICAL*1, LOGICAL*4, CHARACTER, CHARACTER*<длина>)\n"
"dimno  -- число измерений массива или 0 для скаляров\n"
");\n",
"CREATE TABLE dims (\n"
"array,   -- id таблицы vars\n"
"dim,   -- номер размерности 1..dims\n"
"low, high -- id таблицы expressions\n"
");\n",
"CREATE TABLE atr (\n"
"var,   -- id таблицы vars\n"
"T_mode -- текстовое описание признака переменной\n"
"--Может быть указано\n"
"-- DATA - означает, что у переменной есть описание через оператор DATA\n"
"-- SAVE - у переменной есть признак SAVE\n"
"-- EQUIVALENCE - есть оператор EQUIVALENCE для переменной\n"
"-- COMMON - переменная имеет ассоциацию по памяти на другую переменную\n"
");\n",
"CREATE TABLE dummies (\n"
"routine, -- id таблицы routines\n"
"var,  -- id таблицы vars\n"
"pos   -- порядковый номер параметра в заголовке подпрограммы\n"
"-- (нумерация начинается с 1)\n"
");\n",
"CREATE TABLE comid (\n"
"id INT PRIMARY KEY,\n"
"T_ident\n"
");\n",
"CREATE TABLE comdef (\n"
"id INT PRIMARY KEY\n"
");\n",
"CREATE TABLE comvars (\n"
"def,  -- id таблицы comdef, описание тела блока\n"
"var  -- id таблицы vars\n"
");\n",
"CREATE TABLE comdecl (\n"
"pe, -- id таблицы routines\n"
"com,  -- id таблицы comid, идентификатор блока\n"
"def -- id таблицы comdef, описание тела блока\n"
");\n",
"CREATE TABLE expressions (\n"
"id  INT PRIMARY KEY,\n"
"T_text  -- символьное представление выражения\n"
");\n",
"CREATE TABLE postfix (\n"
"expr,  -- id таблицы expressions,\n"
"T_pfix  -- постфиксная запись выражения (полиз)\n"
");\n",
"CREATE TABLE linexpr (\n"
"expr,  -- id таблицы expressions\n"
"monom -- id таблицы monoms\n"
");\n",
"CREATE TABLE monoms (\n"
"id INT PRIMARY KEY,\n"
"coeff,  -- это неименованная целочисленная константа\n"
"var  -- id таблицы vars или NULL\n"
");\n",
"CREATE TABLE loops (\n"
"id INT PRIMARY KEY,\n"
"line,  -- номер строки заголовка цикла,\n"
"-- заголовком корня дерева циклов является заголовок ПЕ\n"
"F_time, -- оценка времени выполнения одного витка цикла\n"
"-- без учета вложенных в него циклов\n"
"var,   -- id таблицы vars или NULL\n"
"first, last, step  -- id таблицы expressions или NULL\n"
");\n",
"CREATE TABLE looptree (\n"
"self,  -- id таблицы loops\n"
"parent,  -- id таблицы loops или NULL (для корня дерева циклов)\n"
"tightly -- признак тесной вложенности в объемлющий (задается 1, иначе 0)\n"
");\n",
"CREATE TABLE operators (\n"
"id INT PRIMARY KEY,\n"
"loop,  -- id таблицы loops\n"
"line  -- номер строки\n"
");\n",
"CREATE TABLE branches (\n"
"self,  -- id таблицы operators\n"
"next,  -- id таблицы operators\n"
"weight -- веса переходов или NULL\n"
");\n",
"CREATE TABLE usage (\n"
"id INT PRIMARY KEY,\n"
"oper,  -- id таблицы operators\n"
"var,  -- id таблицы vars\n"
"T_mode TEXT -- 'READ' или 'WRITE' или NULL (для вызовов процедур)\n"
");\n",
"CREATE TABLE indexes (\n"
"use,   -- id таблицы usage\n"
"ind,  -- 1..dims\n"
"expr  -- id таблицы expressions\n"
");\n",
"CREATE TABLE calls (\n"
"id INT PRIMARY KEY,\n"
"oper,  -- id таблицы operators\n"
"routine  -- id таблицы routines\n"
");\n",
"CREATE TABLE arguments (\n"
"call, -- id таблицы calls\n"
"pos,  -- номер аргумента\n"
"expr -- id таблицы expressions\n"
");\n",
"CREATE TABLE expr_usage (\n"
"expr, -- id таблицы expressions\n"
"use -- id таблицы usage\n"
");\n",
"CREATE TABLE io (\n"
"oper,  -- id таблицы operators\n"
"mode  -- 0 или N, где N - номер особенности\n"
");\n",
"CREATE TABLE depends (\n"
"loop,  -- id таблицы loops\n"
"T_type, -- 'REDUCTION', 'TEMP', ...\n"
"var,   -- id таблицы vars or NULL (для зависимости EXIT)\n"
"T_redop -- тип операции редукции\n"
"--Набор типов расширяемый. Пока были предусмотрены следующие типы.\n"
"--- Тип REDUCTION задает редукционную зависимость по операции redop над\n"
"--переменной var. Операции могут быть заданы AND, OR, SUM, PRODUCT, MIN,\n"
"--MAX. MAXLOC и MINLOC не предусмотрены. Под переменной подразумевается\n"
"--скаляр, массив, элемент массива.\n"
"--- Тип TEMP означает наличие собственной (временной, рабочей, приватной,NEW)"
"--переменной var для цикла.\n"
"--- Тип EXIT задается, если обнаружен выход из цикла\n"
"--- Тип VAR_DEP_IS говорит о том, что имеется зависимость по переменной var."
"--- Тип VAR_DEP_POS говорит о возможном наличии зависимости по переменной var"
"--(анализатор не может точно сказать, что зависимость есть или что ее нет)\n"
");\n",
"CREATE TABLE analyzed (\n"
"scal_dep,  -- глубина анализа на зависимости между скалярами,\n"
"--  0 - не было анализа,\n"
"--  1-был анализ на зависимости по скалярам без межпроцедурного анализа,\n"
"--  2 - с межпроцедурным анализом.\n"
"arr_dep,  -- глубина анализа на зависимости между массивами\n"
"red_dep,   -- глубина анализа на редукционные зависимости\n"
"priv_dep   -- глубина анализа на поиск приватных переменных\n"
");\n",
"CREATE TABLE userdir (\n"
"oper,  -- id таблицы operators, перед которым есть специальный комментарий\n"
"line,  -- номер строки\n"
"T_dir -- специальный комментарий\n"
");\n",
"CREATE TABLE classes (\n"
"id INT PRIMARY KEY,\n"
"T_ident, -- уникальное имя варианта задачи\n"
"T_comment -- комментарий, поясняющий вариант\n"
");\n",
"CREATE TABLE classizes (\n"
"class, -- id таблицы classes\n"
"var,  -- id таблицы vars\n"
"value -- целое значение параметра варианта задачи\n"
");\n",
"CREATE TABLE machs (\n"
"id INT PRIMARY KEY,\n"
"T_name,  -- имя машины\n"
"T_comm_type, -- коммуникационная среда\n"
"F_TStart,  -- латентность коммуникационной среды\n"
"F_TByte,  -- временные расходы на передачу каждого байта\n"
"proc_num,  -- количество процессоров\n"
"proc_perf  -- производительность процессоров\n"
");\n",
"CREATE TABLE grids (\n"
"id INT PRIMARY KEY,\n"
"T_ident, -- уникальное имя конфигурации\n"
"dims,  -- число измерений\n"
"T_comment -- поясняющий комментарий\n"
");\n",
"CREATE TABLE griddims (\n"
"grid,  -- id таблицы grids\n"
"dim,   -- измерение 1..dims\n"
"value -- размер по измерению\n"
");\n",
"CREATE TABLE pvers (\n"
"id  INT PRIMARY KEY,\n"
"T_ident, -- уникальное имя варианта распараллеливания\n"
"T_comment -- поясняющий комментарий\n"
");\n",
"CREATE TABLE pdir (\n"
"file,  -- id таблицы files\n"
"line,  -- номер строки, перед которой надо вставить директиву\n"
"oper,  -- id таблицы operators\n"
"pver,  -- id таблицы pvers, вариант распараллеливания\n"
"T_dir TEXT -- текст директивы\n"
");\n",
"CREATE TABLE parperf (\n"
"pver,  -- id таблицы pvers, вариант распараллеливания\n"
"grid,  -- id таблицы grids, вариант решетки\n"
"class, -- id таблицы classes, вариант задачи\n"
"mach,  -- id таблицы machs, вариант ЭВМ\n"
"loop,   -- id таблицы loops\n"
"F_seqtime -- время последовательного выполнения\n"
"F_partime -- время параллельного выполнения\n"
"T_file_pareff -- имя файла со всеми характеристиками\n"
"-- последовательного и параллельного выполнения\n"
");\n",
/*********************************************************/
#else
/******************************* 20.02.2007 **************/
"CREATE TABLE files     ( id INTEGER PRIMARY KEY, T_filename TEXT);\n",
"CREATE TABLE routines  ( id INTEGER PRIMARY KEY, "
                        "T_ident TEXT, file, line, root);\n",
"CREATE TABLE dummies   ( var, pos);\n",
"CREATE TABLE loops     ( id INTEGER PRIMARY KEY, "
                        "line, time, var, first, last, step );\n",
"CREATE TABLE looptree  ( loop, parent, tightly);\n",
"CREATE TABLE comid     ( id INTEGER PRIMARY KEY, ident );\n", //61
"CREATE TABLE comdef    ( id INTEGER PRIMARY KEY);\n",         //61
"CREATE TABLE comvar    ( def, var );\n",
"CREATE TABLE comdecl   ( pe, com, def );\n",
"CREATE TABLE operators ( id INTEGER PRIMARY KEY, isin, line, sageid);\n",
"CREATE TABLE branches  ( self, next, weight);\n",
"CREATE TABLE calls     ( id INTEGER PRIMARY KEY, caller, routine);\n",
"CREATE TABLE arguments ( call, post, usage);\n",  /* ??? */
"CREATE TABLE vars      ( id INTEGER PRIMARY KEY, "     // an
                        "T_ident TEXT, routine, T_type TEXT, dimno);\n",
"CREATE TABLE dims      ( var, dim, low, high);\n",
"CREATE TABLE expressions ( id INTEGER PRIMARY KEY, "   // an
                        "T_text TEXT);\n",
"CREATE TABLE postfix   ( expr, pfix );\n",
"CREATE TABLE monoms    ( id INTEGER PRIMARY KEY, coeff, var);\n"
"CREATE TABLE linexpr   ( expr, monom, sign);\n",
"CREATE TABLE depends   ( loop, T_type TEXT, var, T_redop TEXT);\n",
"CREATE TABLE usage     ( id INTEGER PRIMARY KEY, "     // an
                        "loop, var, T_mode TEXT);\n",
"CREATE TABLE indexes   ( usage, ind, expr);\n",
"CREATE TABLE classes   ( id INTEGER PRIMARY KEY, "     // an|us
                        "T_ident TEXT, T_comment TEXT);\n",
"CREATE TABLE classizes ( class, var, value);\n",
"CREATE TABLE grids     ( id INTEGER PRIMARY KEY, "     // us
                        "T_ident TEXT, dimsno, T_comment TEXT);\n",
"CREATE TABLE gridsizes ( grid, dim, value);\n",
"CREATE TABLE pvers     ( id INTEGER PRIMARY KEY, "     // ex
                        "T_ident TEXT, T_comment TEXT);\n",
"CREATE TABLE parloops  ( pvers, loop, dir);\n",
"CREATE TABLE pararray  ( pvers, var,  dir);\n",
"CREATE TABLE parperf   ( pvers, loop, grid, T_pareff TEXT);\n",
/*************************************************************/
#endif

"\n   -- END OF SCHEMA \n\n",
0
    }
;

char szTransaction[]="begin transaction;\n";
char szCommit[]="commit;\n";



int vrd_open(char * proj_name)
{
    char dbname[1000];
    char db_deb[1000];
    int init=1;
    int rc=0;

    strcpy(dbname,proj_name);
    strcpy(db_deb,proj_name);
    strcat(dbname, ".db");
    strcat(db_deb, ".deb");

    if( (deb = fopen( dbname, "r")) ) {
        init=0; fclose(deb); deb=NULL;}

if(vrdb_deb){  // debugging enabled
    deb=fopen(db_deb,"w");
////61    if(!deb) {fprintf(stderr,"Cannot open debug-file.\n"); exit(1);}
    } //else
{
#ifdef VRDB
    curdb = sqlite_open( dbname, 0,  NULL);
    if(!curdb) { ////61 fprintf(stderr,"Cannot open|create db-file.\n");
        rc = 1; }
#endif
    }
if(rc==0 && init) // new db successfully opened --
{
if(deb) {
    fprintf(deb,szTransaction);
    fprintf(deb,"%s\n",schema);
} // else
{  int si;
#ifdef VRDB
    rc = sqlite_exec(curdb, szTransaction, NULL, NULL, NULL);
#endif

    for(si=0; schema[si] ; si++) {
if(deb) { fprintf(deb,"%s",schema[si]);}
#ifdef VRDB
    rc = sqlite_exec(curdb, schema[si], NULL, NULL, NULL);
    if(rc) {
if(deb) { fprintf(deb," ### SQLite returns %d for '%s'\n", rc, schema[si]);
//   exit(rc);
        }
        return rc;
        }
#endif
    }


#ifdef VRDB
    vrd_flush();
#endif
    }
}
    return rc;
}

int vrd_flush(void)
{
    char buf[10000];

    sprintf(buf,"%s%s",szCommit, szTransaction);
if(deb) { fprintf(deb,"%s",buf);} // else
{
#ifdef VRDB
    sqlite_exec(curdb, buf, NULL, NULL, NULL);
#endif
    }
    return 0;
}
int vrd_close(void)
{
if(deb) { fprintf(deb,"COMMIT;\n"); fclose(deb); }
#ifdef VRDB
    if(curdb != NULL)
    {
        if(vrdb_result){
            sqlite_free_table(vrdb_result);
            vrdb_result=NULL;
        }
        sqlite_exec(curdb, szCommit, NULL, NULL, NULL);
        sqlite_close(curdb);
        curdb = NULL;
        return 0;
    }
#endif
    return 0;
}


int vrd_put_row(char * table, char * values)
{
    char buf[10000];
    int rc;
    sprintf(buf, "INSERT INTO %s\tVALUES ( %s ) ;", table, values);
if(deb) { fprintf(deb,"%s\n",buf); } // else
{
#ifdef VRDB
    rc = sqlite_exec( curdb, buf, NULL, NULL, NULL);
    return sqlite_last_insert_rowid( curdb );
#endif
    }
    return 0;
}

int vrd_select(char * sql, int* rows, int* cols,
        char*** fields, char*** col_names)
{
    char buf[1000];
    int rc;
    sprintf(buf," SELECT %s ;", sql);

if(deb) { fprintf(deb,"%s\n",buf);
    return 1;
    } // else
{
    *rows=0;
    *cols=0;
    *fields = NULL;
    *col_names = NULL;
#ifdef VRDB

    if(curdb == NULL) return 1;
    if(vrdb_result){
            sqlite_free_table(vrdb_result);
            vrdb_result=NULL;
    }

    sqlite_get_table( curdb, buf, &vrdb_result, rows, cols, NULL);
    *col_names = vrdb_result;
    *fields = vrdb_result + *cols;
#endif
        return 0;
    }

}
int vrd_get_table(char * table, int* rows, int* cols,
        char*** fields, char*** col_names)
{
    char buf[1000];
    int rc;

    sprintf(buf," * FROM %s WHERE 1 ;", table);
    rc= vrd_select(buf, rows, cols, fields, col_names);
    return rc;
}






