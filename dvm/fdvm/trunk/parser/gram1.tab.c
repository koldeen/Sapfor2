/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PERCENT = 1,
     AMPERSAND = 2,
     ASTER = 3,
     CLUSTER = 4,
     COLON = 5,
     COMMA = 6,
     DASTER = 7,
     DEFINED_OPERATOR = 8,
     DOT = 9,
     DQUOTE = 10,
     GLOBAL_A = 11,
     LEFTAB = 12,
     LEFTPAR = 13,
     MINUS = 14,
     PLUS = 15,
     POINT_TO = 16,
     QUOTE = 17,
     RIGHTAB = 18,
     RIGHTPAR = 19,
     AND = 20,
     DSLASH = 21,
     EQV = 22,
     EQ = 23,
     EQUAL = 24,
     FFALSE = 25,
     GE = 26,
     GT = 27,
     LE = 28,
     LT = 29,
     NE = 30,
     NEQV = 31,
     NOT = 32,
     OR = 33,
     TTRUE = 34,
     SLASH = 35,
     XOR = 36,
     REFERENCE = 37,
     AT = 38,
     ACROSS = 39,
     ALIGN_WITH = 40,
     ALIGN = 41,
     ALLOCATABLE = 42,
     ALLOCATE = 43,
     ARITHIF = 44,
     ASSIGNMENT = 45,
     ASSIGN = 46,
     ASSIGNGOTO = 47,
     ASYNCHRONOUS = 48,
     ASYNCID = 49,
     ASYNCWAIT = 50,
     BACKSPACE = 51,
     BAD_CCONST = 52,
     BAD_SYMBOL = 53,
     BARRIER = 54,
     BLOCKDATA = 55,
     BLOCK = 56,
     BOZ_CONSTANT = 57,
     BYTE = 58,
     CALL = 59,
     CASE = 60,
     CHARACTER = 61,
     CHAR_CONSTANT = 62,
     CHECK = 63,
     CLOSE = 64,
     COMMON = 65,
     COMPLEX = 66,
     COMPGOTO = 67,
     CONSISTENT_GROUP = 68,
     CONSISTENT_SPEC = 69,
     CONSISTENT_START = 70,
     CONSISTENT_WAIT = 71,
     CONSISTENT = 72,
     CONSTRUCT_ID = 73,
     CONTAINS = 74,
     CONTINUE = 75,
     CORNER = 76,
     CYCLE = 77,
     DATA = 78,
     DEALLOCATE = 79,
     HPF_TEMPLATE = 80,
     DEBUG = 81,
     DEFAULT_CASE = 82,
     DEFINE = 83,
     DERIVED = 84,
     DIMENSION = 85,
     DISTRIBUTE = 86,
     DOWHILE = 87,
     DOUBLEPRECISION = 88,
     DOUBLECOMPLEX = 89,
     DP_CONSTANT = 90,
     DVM_POINTER = 91,
     DYNAMIC = 92,
     ELEMENTAL = 93,
     ELSE = 94,
     ELSEIF = 95,
     ELSEWHERE = 96,
     ENDASYNCHRONOUS = 97,
     ENDDEBUG = 98,
     ENDINTERVAL = 99,
     ENDUNIT = 100,
     ENDDO = 101,
     ENDFILE = 102,
     ENDFORALL = 103,
     ENDIF = 104,
     ENDINTERFACE = 105,
     ENDMODULE = 106,
     ENDON = 107,
     ENDSELECT = 108,
     ENDTASK_REGION = 109,
     ENDTYPE = 110,
     ENDWHERE = 111,
     ENTRY = 112,
     EXIT = 113,
     EOLN = 114,
     EQUIVALENCE = 115,
     ERROR = 116,
     EXTERNAL = 117,
     F90 = 118,
     FIND = 119,
     FORALL = 120,
     FORMAT = 121,
     FUNCTION = 122,
     GATE = 123,
     GEN_BLOCK = 124,
     HEAP = 125,
     HIGH = 126,
     IDENTIFIER = 127,
     IMPLICIT = 128,
     IMPLICITNONE = 129,
     INCLUDE_TO = 130,
     INCLUDE = 131,
     INDEPENDENT = 132,
     INDIRECT_ACCESS = 133,
     INDIRECT_GROUP = 134,
     INDIRECT = 135,
     INHERIT = 136,
     INQUIRE = 137,
     INTERFACEASSIGNMENT = 138,
     INTERFACEOPERATOR = 139,
     INTERFACE = 140,
     INTRINSIC = 141,
     INTEGER = 142,
     INTENT = 143,
     INTERVAL = 144,
     INOUT = 145,
     IN = 146,
     INT_CONSTANT = 147,
     LABEL = 148,
     LABEL_DECLARE = 149,
     LET = 150,
     LOCALIZE = 151,
     LOGICAL = 152,
     LOGICALIF = 153,
     LOOP = 154,
     LOW = 155,
     MAXLOC = 156,
     MAX = 157,
     MAP = 158,
     MINLOC = 159,
     MIN = 160,
     MODULE_PROCEDURE = 161,
     MODULE = 162,
     MULT_BLOCK = 163,
     NAMEEQ = 164,
     NAMELIST = 165,
     NEW_VALUE = 166,
     NEW = 167,
     NULLIFY = 168,
     OCTAL_CONSTANT = 169,
     ONLY = 170,
     ON = 171,
     ON_DIR = 172,
     ONTO = 173,
     OPEN = 174,
     OPERATOR = 175,
     OPTIONAL = 176,
     OTHERWISE = 177,
     OUT = 178,
     OWN = 179,
     PARALLEL = 180,
     PARAMETER = 181,
     PAUSE = 182,
     PLAINDO = 183,
     PLAINGOTO = 184,
     POINTER = 185,
     POINTERLET = 186,
     PREFETCH = 187,
     PRINT = 188,
     PRIVATE = 189,
     PRODUCT = 190,
     PROGRAM = 191,
     PUBLIC = 192,
     PURE = 193,
     RANGE = 194,
     READ = 195,
     REALIGN_WITH = 196,
     REALIGN = 197,
     REAL = 198,
     REAL_CONSTANT = 199,
     RECURSIVE = 200,
     REDISTRIBUTE_NEW = 201,
     REDISTRIBUTE = 202,
     REDUCTION_GROUP = 203,
     REDUCTION_START = 204,
     REDUCTION_WAIT = 205,
     REDUCTION = 206,
     REMOTE_ACCESS_SPEC = 207,
     REMOTE_ACCESS = 208,
     REMOTE_GROUP = 209,
     RESET = 210,
     RESULT = 211,
     RETURN = 212,
     REWIND = 213,
     SAVE = 214,
     SECTION = 215,
     SELECT = 216,
     SEQUENCE = 217,
     SHADOW_ADD = 218,
     SHADOW_COMPUTE = 219,
     SHADOW_GROUP = 220,
     SHADOW_RENEW = 221,
     SHADOW_START_SPEC = 222,
     SHADOW_START = 223,
     SHADOW_WAIT_SPEC = 224,
     SHADOW_WAIT = 225,
     SHADOW = 226,
     STAGE = 227,
     STATIC = 228,
     STAT = 229,
     STOP = 230,
     SUBROUTINE = 231,
     SUM = 232,
     SYNC = 233,
     TARGET = 234,
     TASK = 235,
     TASK_REGION = 236,
     THEN = 237,
     TO = 238,
     TRACEON = 239,
     TRACEOFF = 240,
     TRUNC = 241,
     TYPE = 242,
     TYPE_DECL = 243,
     UNDER = 244,
     UNKNOWN = 245,
     USE = 246,
     VIRTUAL = 247,
     VARIABLE = 248,
     WAIT = 249,
     WHERE = 250,
     WHERE_ASSIGN = 251,
     WHILE = 252,
     WITH = 253,
     WRITE = 254,
     COMMENT = 255,
     WGT_BLOCK = 256,
     HPF_PROCESSORS = 257,
     IOSTAT = 258,
     ERR = 259,
     END = 260,
     OMPDVM_ATOMIC = 261,
     OMPDVM_BARRIER = 262,
     OMPDVM_COPYIN = 263,
     OMPDVM_COPYPRIVATE = 264,
     OMPDVM_CRITICAL = 265,
     OMPDVM_ONETHREAD = 266,
     OMPDVM_DO = 267,
     OMPDVM_DYNAMIC = 268,
     OMPDVM_ENDCRITICAL = 269,
     OMPDVM_ENDDO = 270,
     OMPDVM_ENDMASTER = 271,
     OMPDVM_ENDORDERED = 272,
     OMPDVM_ENDPARALLEL = 273,
     OMPDVM_ENDPARALLELDO = 274,
     OMPDVM_ENDPARALLELSECTIONS = 275,
     OMPDVM_ENDPARALLELWORKSHARE = 276,
     OMPDVM_ENDSECTIONS = 277,
     OMPDVM_ENDSINGLE = 278,
     OMPDVM_ENDWORKSHARE = 279,
     OMPDVM_FIRSTPRIVATE = 280,
     OMPDVM_FLUSH = 281,
     OMPDVM_GUIDED = 282,
     OMPDVM_LASTPRIVATE = 283,
     OMPDVM_MASTER = 284,
     OMPDVM_NOWAIT = 285,
     OMPDVM_NONE = 286,
     OMPDVM_NUM_THREADS = 287,
     OMPDVM_ORDERED = 288,
     OMPDVM_PARALLEL = 289,
     OMPDVM_PARALLELDO = 290,
     OMPDVM_PARALLELSECTIONS = 291,
     OMPDVM_PARALLELWORKSHARE = 292,
     OMPDVM_RUNTIME = 293,
     OMPDVM_SECTION = 294,
     OMPDVM_SECTIONS = 295,
     OMPDVM_SCHEDULE = 296,
     OMPDVM_SHARED = 297,
     OMPDVM_SINGLE = 298,
     OMPDVM_THREADPRIVATE = 299,
     OMPDVM_WORKSHARE = 300,
     OMPDVM_NODES = 301,
     OMPDVM_IF = 302,
     IAND = 303,
     IEOR = 304,
     IOR = 305,
     ACC_REGION = 306,
     ACC_END_REGION = 307,
     ACC_CHECKSECTION = 308,
     ACC_END_CHECKSECTION = 309,
     ACC_GET_ACTUAL = 310,
     ACC_ACTUAL = 311,
     ACC_TARGETS = 312,
     ACC_ASYNC = 313,
     ACC_HOST = 314,
     ACC_CUDA = 315,
     ACC_LOCAL = 316,
     ACC_INLOCAL = 317,
     ACC_CUDA_BLOCK = 318,
     BY = 319,
     IO_MODE = 320,
     SPF_ANALYSIS = 321,
     SPF_PARALLEL = 322,
     SPF_TRANSFORM = 323,
     SPF_NOINLINE = 324,
     SPF_PARALLEL_REG = 325,
     SPF_END_PARALLEL_REG = 326,
     CP_CREATE = 327,
     CP_LOAD = 328,
     CP_SAVE = 329,
     CP_WAIT = 330,
     FILES = 331,
     VARLIST = 332,
     STATUS = 333,
     BINARY_OP = 336,
     UNARY_OP = 337
   };
#endif
/* Tokens.  */
#define PERCENT 1
#define AMPERSAND 2
#define ASTER 3
#define CLUSTER 4
#define COLON 5
#define COMMA 6
#define DASTER 7
#define DEFINED_OPERATOR 8
#define DOT 9
#define DQUOTE 10
#define GLOBAL_A 11
#define LEFTAB 12
#define LEFTPAR 13
#define MINUS 14
#define PLUS 15
#define POINT_TO 16
#define QUOTE 17
#define RIGHTAB 18
#define RIGHTPAR 19
#define AND 20
#define DSLASH 21
#define EQV 22
#define EQ 23
#define EQUAL 24
#define FFALSE 25
#define GE 26
#define GT 27
#define LE 28
#define LT 29
#define NE 30
#define NEQV 31
#define NOT 32
#define OR 33
#define TTRUE 34
#define SLASH 35
#define XOR 36
#define REFERENCE 37
#define AT 38
#define ACROSS 39
#define ALIGN_WITH 40
#define ALIGN 41
#define ALLOCATABLE 42
#define ALLOCATE 43
#define ARITHIF 44
#define ASSIGNMENT 45
#define ASSIGN 46
#define ASSIGNGOTO 47
#define ASYNCHRONOUS 48
#define ASYNCID 49
#define ASYNCWAIT 50
#define BACKSPACE 51
#define BAD_CCONST 52
#define BAD_SYMBOL 53
#define BARRIER 54
#define BLOCKDATA 55
#define BLOCK 56
#define BOZ_CONSTANT 57
#define BYTE 58
#define CALL 59
#define CASE 60
#define CHARACTER 61
#define CHAR_CONSTANT 62
#define CHECK 63
#define CLOSE 64
#define COMMON 65
#define COMPLEX 66
#define COMPGOTO 67
#define CONSISTENT_GROUP 68
#define CONSISTENT_SPEC 69
#define CONSISTENT_START 70
#define CONSISTENT_WAIT 71
#define CONSISTENT 72
#define CONSTRUCT_ID 73
#define CONTAINS 74
#define CONTINUE 75
#define CORNER 76
#define CYCLE 77
#define DATA 78
#define DEALLOCATE 79
#define HPF_TEMPLATE 80
#define DEBUG 81
#define DEFAULT_CASE 82
#define DEFINE 83
#define DERIVED 84
#define DIMENSION 85
#define DISTRIBUTE 86
#define DOWHILE 87
#define DOUBLEPRECISION 88
#define DOUBLECOMPLEX 89
#define DP_CONSTANT 90
#define DVM_POINTER 91
#define DYNAMIC 92
#define ELEMENTAL 93
#define ELSE 94
#define ELSEIF 95
#define ELSEWHERE 96
#define ENDASYNCHRONOUS 97
#define ENDDEBUG 98
#define ENDINTERVAL 99
#define ENDUNIT 100
#define ENDDO 101
#define ENDFILE 102
#define ENDFORALL 103
#define ENDIF 104
#define ENDINTERFACE 105
#define ENDMODULE 106
#define ENDON 107
#define ENDSELECT 108
#define ENDTASK_REGION 109
#define ENDTYPE 110
#define ENDWHERE 111
#define ENTRY 112
#define EXIT 113
#define EOLN 114
#define EQUIVALENCE 115
#define ERROR 116
#define EXTERNAL 117
#define F90 118
#define FIND 119
#define FORALL 120
#define FORMAT 121
#define FUNCTION 122
#define GATE 123
#define GEN_BLOCK 124
#define HEAP 125
#define HIGH 126
#define IDENTIFIER 127
#define IMPLICIT 128
#define IMPLICITNONE 129
#define INCLUDE_TO 130
#define INCLUDE 131
#define INDEPENDENT 132
#define INDIRECT_ACCESS 133
#define INDIRECT_GROUP 134
#define INDIRECT 135
#define INHERIT 136
#define INQUIRE 137
#define INTERFACEASSIGNMENT 138
#define INTERFACEOPERATOR 139
#define INTERFACE 140
#define INTRINSIC 141
#define INTEGER 142
#define INTENT 143
#define INTERVAL 144
#define INOUT 145
#define IN 146
#define INT_CONSTANT 147
#define LABEL 148
#define LABEL_DECLARE 149
#define LET 150
#define LOCALIZE 151
#define LOGICAL 152
#define LOGICALIF 153
#define LOOP 154
#define LOW 155
#define MAXLOC 156
#define MAX 157
#define MAP 158
#define MINLOC 159
#define MIN 160
#define MODULE_PROCEDURE 161
#define MODULE 162
#define MULT_BLOCK 163
#define NAMEEQ 164
#define NAMELIST 165
#define NEW_VALUE 166
#define NEW 167
#define NULLIFY 168
#define OCTAL_CONSTANT 169
#define ONLY 170
#define ON 171
#define ON_DIR 172
#define ONTO 173
#define OPEN 174
#define OPERATOR 175
#define OPTIONAL 176
#define OTHERWISE 177
#define OUT 178
#define OWN 179
#define PARALLEL 180
#define PARAMETER 181
#define PAUSE 182
#define PLAINDO 183
#define PLAINGOTO 184
#define POINTER 185
#define POINTERLET 186
#define PREFETCH 187
#define PRINT 188
#define PRIVATE 189
#define PRODUCT 190
#define PROGRAM 191
#define PUBLIC 192
#define PURE 193
#define RANGE 194
#define READ 195
#define REALIGN_WITH 196
#define REALIGN 197
#define REAL 198
#define REAL_CONSTANT 199
#define RECURSIVE 200
#define REDISTRIBUTE_NEW 201
#define REDISTRIBUTE 202
#define REDUCTION_GROUP 203
#define REDUCTION_START 204
#define REDUCTION_WAIT 205
#define REDUCTION 206
#define REMOTE_ACCESS_SPEC 207
#define REMOTE_ACCESS 208
#define REMOTE_GROUP 209
#define RESET 210
#define RESULT 211
#define RETURN 212
#define REWIND 213
#define SAVE 214
#define SECTION 215
#define SELECT 216
#define SEQUENCE 217
#define SHADOW_ADD 218
#define SHADOW_COMPUTE 219
#define SHADOW_GROUP 220
#define SHADOW_RENEW 221
#define SHADOW_START_SPEC 222
#define SHADOW_START 223
#define SHADOW_WAIT_SPEC 224
#define SHADOW_WAIT 225
#define SHADOW 226
#define STAGE 227
#define STATIC 228
#define STAT 229
#define STOP 230
#define SUBROUTINE 231
#define SUM 232
#define SYNC 233
#define TARGET 234
#define TASK 235
#define TASK_REGION 236
#define THEN 237
#define TO 238
#define TRACEON 239
#define TRACEOFF 240
#define TRUNC 241
#define TYPE 242
#define TYPE_DECL 243
#define UNDER 244
#define UNKNOWN 245
#define USE 246
#define VIRTUAL 247
#define VARIABLE 248
#define WAIT 249
#define WHERE 250
#define WHERE_ASSIGN 251
#define WHILE 252
#define WITH 253
#define WRITE 254
#define COMMENT 255
#define WGT_BLOCK 256
#define HPF_PROCESSORS 257
#define IOSTAT 258
#define ERR 259
#define END 260
#define OMPDVM_ATOMIC 261
#define OMPDVM_BARRIER 262
#define OMPDVM_COPYIN 263
#define OMPDVM_COPYPRIVATE 264
#define OMPDVM_CRITICAL 265
#define OMPDVM_ONETHREAD 266
#define OMPDVM_DO 267
#define OMPDVM_DYNAMIC 268
#define OMPDVM_ENDCRITICAL 269
#define OMPDVM_ENDDO 270
#define OMPDVM_ENDMASTER 271
#define OMPDVM_ENDORDERED 272
#define OMPDVM_ENDPARALLEL 273
#define OMPDVM_ENDPARALLELDO 274
#define OMPDVM_ENDPARALLELSECTIONS 275
#define OMPDVM_ENDPARALLELWORKSHARE 276
#define OMPDVM_ENDSECTIONS 277
#define OMPDVM_ENDSINGLE 278
#define OMPDVM_ENDWORKSHARE 279
#define OMPDVM_FIRSTPRIVATE 280
#define OMPDVM_FLUSH 281
#define OMPDVM_GUIDED 282
#define OMPDVM_LASTPRIVATE 283
#define OMPDVM_MASTER 284
#define OMPDVM_NOWAIT 285
#define OMPDVM_NONE 286
#define OMPDVM_NUM_THREADS 287
#define OMPDVM_ORDERED 288
#define OMPDVM_PARALLEL 289
#define OMPDVM_PARALLELDO 290
#define OMPDVM_PARALLELSECTIONS 291
#define OMPDVM_PARALLELWORKSHARE 292
#define OMPDVM_RUNTIME 293
#define OMPDVM_SECTION 294
#define OMPDVM_SECTIONS 295
#define OMPDVM_SCHEDULE 296
#define OMPDVM_SHARED 297
#define OMPDVM_SINGLE 298
#define OMPDVM_THREADPRIVATE 299
#define OMPDVM_WORKSHARE 300
#define OMPDVM_NODES 301
#define OMPDVM_IF 302
#define IAND 303
#define IEOR 304
#define IOR 305
#define ACC_REGION 306
#define ACC_END_REGION 307
#define ACC_CHECKSECTION 308
#define ACC_END_CHECKSECTION 309
#define ACC_GET_ACTUAL 310
#define ACC_ACTUAL 311
#define ACC_TARGETS 312
#define ACC_ASYNC 313
#define ACC_HOST 314
#define ACC_CUDA 315
#define ACC_LOCAL 316
#define ACC_INLOCAL 317
#define ACC_CUDA_BLOCK 318
#define BY 319
#define IO_MODE 320
#define SPF_ANALYSIS 321
#define SPF_PARALLEL 322
#define SPF_TRANSFORM 323
#define SPF_NOINLINE 324
#define SPF_PARALLEL_REG 325
#define SPF_END_PARALLEL_REG 326
#define CP_CREATE 327
#define CP_LOAD 328
#define CP_SAVE 329
#define CP_WAIT 330
#define FILES 331
#define VARLIST 332
#define STATUS 333
#define BINARY_OP 336
#define UNARY_OP 337




/* Copy the first part of user declarations.  */
#line 335 "gram1.y"

#include <string.h>
#include "inc.h"
#include "extern.h"
#include "defines.h"
#include "fdvm.h"
#include "fm.h"

/* We may use builtin alloca */
#include "compatible.h"
#ifdef _NEEDALLOCAH_
#  include <alloca.h>
#endif

#define EXTEND_NODE 2  /* move the definition to h/ files. */

extern PTR_BFND global_bfnd, pred_bfnd;
extern PTR_SYMB star_symb;
extern PTR_SYMB global_list;
extern PTR_TYPE global_bool;
extern PTR_TYPE global_int;
extern PTR_TYPE global_float;
extern PTR_TYPE global_double;
extern PTR_TYPE global_char;
extern PTR_TYPE global_string;
extern PTR_TYPE global_string_2;
extern PTR_TYPE global_complex;
extern PTR_TYPE global_dcomplex;
extern PTR_TYPE global_gate;
extern PTR_TYPE global_event;
extern PTR_TYPE global_sequence;
extern PTR_TYPE global_default;
extern PTR_LABEL thislabel;
extern PTR_CMNT comments, cur_comment;
extern PTR_BFND last_bfnd;
extern PTR_TYPE impltype[];
extern int nioctl;
extern int maxdim;
extern long yystno;	/* statement label */
extern char stmtbuf[];	/* input buffer */
extern char *commentbuf;	/* comments buffer from scanner */
extern PTR_BLOB head_blob;
extern PTR_BLOB cur_blob;
extern PTR_TYPE vartype; /* variable type */
extern int end_group;
extern char saveall;
extern int privateall;
extern int needkwd;
extern int implkwd;
extern int opt_kwd_hedr;
/* added for FORTRAN 90 */
extern PTR_LLND first_unresolved_call;
extern PTR_LLND last_unresolved_call;
extern int data_stat;
extern char yyquote;

extern int warn_all;
extern int statement_kind; /* kind of statement: 1 - HPF-DVM-directive, 0 - Fortran statement*/ 
int extend_flag = 0;

static int do_name_err;
static int ndim;	/* number of dimension */
/*!!! hpf */
static int explicit_shape; /*  1 if shape specification is explicit */
/* static int varleng;*/	/* variable size */
static int lastwasbranch = NO;	/* set if last stmt was a branch stmt */
static int thiswasbranch = NO;	/* set if this stmt is a branch stmt */
static PTR_SYMB type_var = SMNULL;
static PTR_LLND stat_alloc = LLNULL; /* set if ALLOCATE/DEALLOCATE stmt has STAT-clause*/
/* static int subscripts_status = 0; */
static int type_options,type_opt;   /* The various options used to declare a name -
                                      RECURSIVE, POINTER, OPTIONAL etc.         */
static PTR_BFND module_scope;
static int position = IN_OUTSIDE;            
static int attr_ndim;           /* number of dimensions in DIMENSION (array_spec)
                                   attribute declaration */
static PTR_LLND attr_dims;     /* low level representation of array_spec in
                                   DIMENSION (array_spec) attribute declarartion. */
static int in_vec = NO;	      /* set if processing array constructor */


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 416 "gram1.y"
{
    int token;
    char charv;
    char *charp;
    PTR_BFND bf_node;
    PTR_LLND ll_node;
    PTR_SYMB symbol;
    PTR_TYPE data_type;
    PTR_HASH hash_entry;
    PTR_LABEL label;
}
/* Line 187 of yacc.c.  */
#line 863 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 619 "gram1.y"

void add_scope_level();
void delete_beyond_scope_level();
PTR_HASH look_up_sym();
PTR_HASH just_look_up_sym();
PTR_HASH just_look_up_sym_in_scope();
PTR_HASH look_up_op();
PTR_SYMB make_constant();
PTR_SYMB make_scalar();
PTR_SYMB make_array();
PTR_SYMB make_pointer();
PTR_SYMB make_function();
PTR_SYMB make_external();
PTR_SYMB make_intrinsic();
PTR_SYMB make_procedure();
PTR_SYMB make_process();
PTR_SYMB make_program();
PTR_SYMB make_module();
PTR_SYMB make_common();
PTR_SYMB make_parallel_region();
PTR_SYMB make_derived_type();
PTR_SYMB make_local_entity();
PTR_SYMB make_global_entity();
PTR_TYPE make_type_node();
PTR_TYPE lookup_type(), make_type();
void     process_type();
void     process_interface();
void     bind();
void     late_bind_if_needed();
PTR_SYMB component();
PTR_SYMB lookup_type_symbol();
PTR_SYMB resolve_overloading();
PTR_BFND cur_scope();
PTR_BFND subroutine_call();
PTR_BFND process_call();
PTR_LLND deal_with_options();
PTR_LLND intrinsic_op_node();
PTR_LLND defined_op_node();
int is_substring_ref();
int is_array_section_ref();
PTR_LLND dim_expr(); 
PTR_BFND exit_stat();
PTR_BFND make_do();
PTR_BFND make_pardo();
PTR_BFND make_enddoall();
PTR_TYPE install_array(); 
PTR_SYMB install_entry(); 
void install_param_list();
PTR_LLND construct_entry_list();
void copy_sym_data();
PTR_LLND check_and_install();
PTR_HASH look_up();
PTR_BFND get_bfnd(); 
PTR_BLOB make_blob();
PTR_LABEL make_label();
PTR_LABEL make_label_node();
int is_interface_stat();
PTR_LLND make_llnd (); 
PTR_LLND make_llnd_label (); 
PTR_TYPE make_sa_type(); 
PTR_SYMB procedure_call();
PTR_BFND proc_list();
PTR_SYMB set_id_list();
PTR_LLND set_ll_list();
PTR_LLND add_to_lowLevelList(), add_to_lowList();
PTR_BFND set_stat_list() ;
PTR_BLOB follow_blob();
PTR_SYMB proc_decl_init();
PTR_CMNT make_comment();
PTR_HASH correct_symtab();
char *copyn();
char *convic();
char *StringConcatenation();
int atoi();
PTR_BFND make_logif();
PTR_BFND make_if();
PTR_BFND make_forall();
void startproc();
void match_parameters();
void make_else();
void make_elseif();
void make_endif();
void make_elsewhere();
void make_elsewhere_mask();
void make_endwhere();
void make_endforall();
void make_endselect();
void make_extend();
void make_endextend();
void make_section();
void make_section_extend();
void doinclude();
void endproc();
void err();
void execerr();
void flline();
void warn();
void warn1();
void newprog();
void set_type();
void dclerr();
void enddcl();
void install_const();
void setimpl();
void copy_module_scope();

long convci();
void set_expr_type();
void errstr();
void yyerror();
void set_blobs();
void make_loop();
void startioctl();
void endioctl();
void redefine_func_arg_type();
int isResultVar();

/* used by FORTRAN M */
PTR_BFND make_processdo();
PTR_BFND make_processes();
PTR_BFND make_endprocesses();

PTR_BFND make_endparallel();/*OMP*/
PTR_BFND make_parallel();/*OMP*/
PTR_BFND make_endsingle();/*OMP*/
PTR_BFND make_single();/*OMP*/
PTR_BFND make_endmaster();/*OMP*/
PTR_BFND make_master();/*OMP*/
PTR_BFND make_endordered();/*OMP*/
PTR_BFND make_ordered();/*OMP*/
PTR_BFND make_endcritical();/*OMP*/
PTR_BFND make_critical();/*OMP*/
PTR_BFND make_endsections();/*OMP*/
PTR_BFND make_sections();/*OMP*/
PTR_BFND make_ompsection();/*OMP*/
PTR_BFND make_endparallelsections();/*OMP*/
PTR_BFND make_parallelsections();/*OMP*/
PTR_BFND make_endworkshare();/*OMP*/
PTR_BFND make_workshare();/*OMP*/
PTR_BFND make_endparallelworkshare();/*OMP*/
PTR_BFND make_parallelworkshare();/*OMP*/



/* Line 216 of yacc.c.  */
#line 1019 "gram1.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5420

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  338
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  514
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1238
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2432

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint16 yytranslate[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,     1,     2,   336,   337
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     8,    12,    16,    20,    24,    27,
      29,    31,    33,    37,    41,    46,    52,    58,    62,    67,
      71,    72,    75,    78,    81,    83,    85,    90,    96,   101,
     107,   110,   116,   118,   119,   121,   122,   124,   125,   128,
     132,   134,   138,   140,   142,   144,   145,   146,   147,   149,
     151,   153,   155,   157,   159,   161,   163,   165,   167,   169,
     171,   173,   176,   181,   184,   190,   192,   194,   196,   198,
     200,   202,   204,   206,   208,   210,   212,   214,   217,   221,
     227,   233,   236,   238,   240,   242,   244,   246,   248,   250,
     252,   254,   256,   258,   260,   262,   264,   266,   268,   270,
     272,   274,   276,   278,   283,   291,   294,   298,   306,   313,
     314,   317,   323,   325,   330,   332,   334,   336,   339,   341,
     346,   348,   350,   352,   354,   356,   358,   361,   364,   367,
     369,   371,   379,   383,   388,   392,   397,   401,   404,   410,
     411,   414,   417,   423,   424,   429,   435,   436,   439,   443,
     445,   447,   449,   451,   453,   455,   457,   459,   461,   463,
     464,   466,   472,   479,   486,   487,   489,   495,   505,   507,
     509,   512,   515,   516,   517,   520,   523,   529,   534,   539,
     543,   548,   552,   557,   561,   565,   570,   576,   580,   585,
     591,   595,   599,   601,   605,   608,   613,   617,   622,   626,
     630,   634,   638,   642,   646,   648,   653,   655,   657,   662,
     666,   667,   668,   673,   675,   679,   681,   685,   688,   692,
     696,   701,   704,   705,   707,   709,   713,   719,   721,   725,
     726,   728,   736,   738,   742,   745,   748,   752,   754,   756,
     761,   765,   768,   770,   772,   774,   776,   780,   782,   786,
     788,   790,   797,   799,   801,   804,   807,   809,   813,   815,
     818,   821,   823,   827,   829,   833,   839,   841,   843,   845,
     848,   851,   855,   859,   861,   865,   869,   871,   875,   877,
     879,   883,   885,   889,   891,   893,   897,   903,   904,   905,
     907,   912,   917,   919,   923,   927,   930,   932,   936,   940,
     947,   954,   962,   964,   966,   970,   974,   976,   978,   982,
     986,   987,   991,   992,   995,   999,  1001,  1003,  1006,  1010,
    1012,  1014,  1016,  1020,  1022,  1026,  1028,  1030,  1034,  1039,
    1040,  1043,  1046,  1048,  1050,  1054,  1056,  1060,  1062,  1063,
    1064,  1065,  1068,  1069,  1071,  1073,  1075,  1078,  1081,  1086,
    1088,  1092,  1094,  1098,  1100,  1102,  1104,  1106,  1110,  1114,
    1118,  1122,  1126,  1129,  1132,  1135,  1139,  1143,  1147,  1151,
    1155,  1159,  1163,  1167,  1171,  1175,  1179,  1182,  1186,  1190,
    1192,  1194,  1196,  1198,  1200,  1202,  1208,  1215,  1220,  1226,
    1230,  1232,  1234,  1240,  1245,  1248,  1249,  1251,  1257,  1258,
    1260,  1262,  1266,  1268,  1272,  1275,  1277,  1279,  1281,  1283,
    1285,  1287,  1291,  1295,  1301,  1303,  1305,  1309,  1312,  1318,
    1323,  1328,  1332,  1335,  1337,  1338,  1339,  1346,  1348,  1350,
    1352,  1357,  1363,  1365,  1370,  1376,  1377,  1379,  1383,  1385,
    1387,  1389,  1392,  1396,  1400,  1403,  1405,  1408,  1411,  1414,
    1418,  1426,  1430,  1434,  1436,  1439,  1442,  1444,  1447,  1451,
    1453,  1455,  1457,  1463,  1471,  1472,  1479,  1484,  1496,  1510,
    1515,  1519,  1523,  1531,  1540,  1544,  1546,  1549,  1552,  1556,
    1558,  1562,  1563,  1565,  1566,  1568,  1570,  1573,  1579,  1586,
    1588,  1592,  1596,  1597,  1600,  1602,  1608,  1616,  1617,  1619,
    1623,  1627,  1634,  1640,  1647,  1652,  1658,  1664,  1667,  1669,
    1671,  1682,  1684,  1688,  1693,  1697,  1701,  1705,  1709,  1716,
    1723,  1729,  1738,  1741,  1745,  1749,  1757,  1765,  1766,  1768,
    1773,  1776,  1781,  1783,  1786,  1789,  1791,  1793,  1794,  1795,
    1796,  1799,  1802,  1805,  1808,  1811,  1814,  1817,  1821,  1826,
    1829,  1833,  1835,  1839,  1843,  1845,  1847,  1849,  1853,  1855,
    1857,  1859,  1861,  1863,  1867,  1871,  1873,  1878,  1880,  1882,
    1884,  1887,  1890,  1893,  1895,  1899,  1903,  1908,  1913,  1915,
    1919,  1921,  1927,  1929,  1931,  1933,  1937,  1941,  1945,  1949,
    1953,  1957,  1959,  1963,  1969,  1975,  1981,  1982,  1983,  1985,
    1989,  1991,  1993,  1997,  2001,  2005,  2009,  2012,  2016,  2020,
    2021,  2023,  2025,  2027,  2029,  2031,  2033,  2035,  2037,  2039,
    2041,  2043,  2045,  2047,  2049,  2051,  2053,  2055,  2057,  2059,
    2061,  2063,  2065,  2067,  2069,  2071,  2073,  2075,  2077,  2079,
    2081,  2083,  2085,  2087,  2089,  2091,  2093,  2095,  2097,  2099,
    2101,  2103,  2105,  2107,  2109,  2111,  2113,  2115,  2117,  2119,
    2121,  2123,  2125,  2127,  2129,  2131,  2133,  2135,  2137,  2139,
    2141,  2143,  2147,  2151,  2154,  2158,  2160,  2164,  2166,  2170,
    2172,  2176,  2178,  2183,  2187,  2189,  2193,  2195,  2199,  2201,
    2206,  2211,  2216,  2220,  2224,  2226,  2230,  2234,  2236,  2240,
    2244,  2246,  2250,  2254,  2256,  2260,  2261,  2267,  2274,  2283,
    2285,  2289,  2291,  2293,  2295,  2300,  2302,  2303,  2306,  2310,
    2313,  2318,  2319,  2321,  2327,  2332,  2339,  2344,  2346,  2351,
    2356,  2358,  2365,  2367,  2371,  2373,  2375,  2380,  2382,  2384,
    2388,  2390,  2392,  2396,  2398,  2399,  2401,  2404,  2408,  2410,
    2413,  2419,  2424,  2429,  2436,  2438,  2442,  2444,  2446,  2453,
    2458,  2460,  2464,  2466,  2468,  2470,  2472,  2474,  2478,  2480,
    2482,  2484,  2491,  2496,  2498,  2503,  2505,  2507,  2509,  2511,
    2516,  2519,  2527,  2529,  2534,  2536,  2538,  2550,  2551,  2554,
    2558,  2560,  2564,  2566,  2570,  2572,  2576,  2578,  2582,  2584,
    2588,  2590,  2594,  2603,  2605,  2609,  2612,  2615,  2623,  2625,
    2629,  2631,  2635,  2637,  2642,  2644,  2648,  2650,  2652,  2653,
    2655,  2657,  2660,  2662,  2664,  2666,  2668,  2670,  2672,  2674,
    2676,  2678,  2680,  2689,  2696,  2705,  2712,  2714,  2721,  2728,
    2735,  2742,  2744,  2748,  2754,  2756,  2760,  2769,  2776,  2783,
    2788,  2794,  2800,  2803,  2806,  2807,  2809,  2813,  2815,  2820,
    2828,  2830,  2834,  2838,  2840,  2844,  2850,  2854,  2858,  2860,
    2864,  2866,  2868,  2872,  2876,  2880,  2884,  2895,  2904,  2915,
    2916,  2917,  2919,  2922,  2927,  2932,  2939,  2941,  2943,  2945,
    2947,  2949,  2951,  2953,  2955,  2957,  2959,  2961,  2968,  2973,
    2978,  2982,  2992,  2994,  2996,  3000,  3002,  3008,  3014,  3024,
    3025,  3027,  3029,  3033,  3037,  3041,  3045,  3049,  3056,  3060,
    3064,  3068,  3072,  3080,  3086,  3088,  3090,  3094,  3099,  3101,
    3103,  3107,  3109,  3111,  3115,  3119,  3122,  3126,  3131,  3136,
    3142,  3148,  3150,  3153,  3158,  3163,  3168,  3169,  3171,  3174,
    3182,  3189,  3193,  3197,  3205,  3211,  3213,  3217,  3219,  3224,
    3227,  3231,  3235,  3240,  3247,  3251,  3254,  3258,  3260,  3262,
    3267,  3273,  3277,  3284,  3287,  3292,  3295,  3297,  3301,  3305,
    3306,  3308,  3311,  3314,  3317,  3320,  3330,  3336,  3338,  3342,
    3345,  3348,  3351,  3361,  3366,  3368,  3372,  3374,  3376,  3379,
    3380,  3388,  3390,  3395,  3397,  3401,  3403,  3405,  3407,  3424,
    3425,  3429,  3433,  3437,  3441,  3448,  3458,  3460,  3462,  3464,
    3466,  3468,  3470,  3472,  3474,  3476,  3478,  3480,  3482,  3484,
    3486,  3488,  3490,  3492,  3494,  3496,  3498,  3500,  3502,  3504,
    3506,  3508,  3510,  3512,  3515,  3518,  3523,  3527,  3532,  3538,
    3540,  3542,  3544,  3546,  3548,  3550,  3552,  3554,  3556,  3562,
    3565,  3568,  3571,  3574,  3577,  3583,  3585,  3587,  3589,  3594,
    3599,  3604,  3609,  3611,  3613,  3615,  3617,  3619,  3621,  3623,
    3625,  3627,  3629,  3631,  3633,  3635,  3637,  3639,  3644,  3648,
    3653,  3659,  3661,  3663,  3665,  3667,  3672,  3676,  3679,  3684,
    3688,  3693,  3697,  3702,  3708,  3710,  3712,  3714,  3716,  3718,
    3720,  3722,  3730,  3736,  3738,  3740,  3742,  3744,  3749,  3753,
    3758,  3764,  3766,  3768,  3773,  3777,  3782,  3788,  3790,  3792,
    3795,  3797,  3800,  3805,  3809,  3814,  3818,  3823,  3829,  3831,
    3833,  3835,  3837,  3839,  3841,  3843,  3845,  3847,  3849,  3851,
    3854,  3859,  3863,  3866,  3871,  3875,  3878,  3882,  3885,  3888,
    3891,  3894,  3897,  3900,  3904,  3907,  3913,  3916,  3922,  3925,
    3931,  3933,  3935,  3939,  3943,  3944,  3945,  3947,  3949,  3951,
    3953,  3955,  3957,  3961,  3964,  3970,  3975,  3978,  3984,  3989,
    3992,  3995,  3997,  3999,  4003,  4006,  4009,  4012,  4017,  4022,
    4027,  4032,  4037,  4042,  4044,  4046,  4048,  4052,  4055,  4058,
    4060,  4062,  4064,  4066,  4068,  4070,  4072,  4077,  4082,  4087,
    4090,  4092,  4094,  4098,  4100,  4102,  4108,  4114,  4116,  4120,
    4122,  4124,  4126,  4132,  4138,  4144,  4146,  4150,  4153
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     339,     0,    -1,    -1,   339,   340,   116,    -1,   341,   342,
     558,    -1,   341,   359,   558,    -1,   341,   504,   558,    -1,
     341,   133,   355,    -1,   341,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   343,   350,    -1,    57,   343,   351,
      -1,   233,   343,   345,   352,    -1,   344,   233,   343,   345,
     352,    -1,   124,   343,   346,   352,   348,    -1,   347,   352,
     348,    -1,   114,   349,   352,   348,    -1,   164,   343,   349,
      -1,    -1,   202,   356,    -1,   195,   356,    -1,    95,   356,
      -1,   349,    -1,   349,    -1,   380,   124,   343,   349,    -1,
     380,   344,   124,   343,   349,    -1,   344,   124,   343,   349,
      -1,   344,   380,   124,   343,   349,    -1,   356,   357,    -1,
     356,   213,    15,   349,    21,    -1,   129,    -1,    -1,   349,
      -1,    -1,   349,    -1,    -1,    15,    21,    -1,    15,   353,
      21,    -1,   354,    -1,   353,     8,   354,    -1,   349,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   364,    -1,   365,
      -1,   366,    -1,   396,    -1,   392,    -1,   559,    -1,   401,
      -1,   402,    -1,   403,    -1,   461,    -1,   382,    -1,   397,
      -1,   407,    -1,   216,   471,    -1,   216,   471,   472,   438,
      -1,   123,   470,    -1,   183,   471,    15,   444,    21,    -1,
     372,    -1,   373,    -1,   378,    -1,   375,    -1,   377,    -1,
     393,    -1,   394,    -1,   395,    -1,   360,    -1,   448,    -1,
     446,    -1,   374,    -1,   142,   471,    -1,   142,   471,   349,
      -1,   141,   471,    15,   362,    21,    -1,   140,   471,    15,
      26,    21,    -1,   107,   513,    -1,    10,    -1,   361,    -1,
     363,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   471,
     472,   349,    -1,   245,     8,   471,   356,   371,   472,   349,
      -1,   112,   471,    -1,   112,   471,   349,    -1,   380,   367,
     349,   471,   454,   386,   391,    -1,   366,     8,   349,   454,
     386,   391,    -1,    -1,     7,     7,    -1,     8,   356,   368,
       7,     7,    -1,   369,    -1,   368,     8,   356,   369,    -1,
     183,    -1,   371,    -1,    44,    -1,    87,   454,    -1,   119,
      -1,   145,    15,   370,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   356,   148,
      -1,   356,   180,    -1,   356,   147,    -1,   194,    -1,   191,
      -1,   145,   471,    15,   370,    21,   472,   349,    -1,   372,
       8,   349,    -1,   178,   471,   472,   349,    -1,   373,     8,
     349,    -1,   230,   471,   472,   400,    -1,   374,     8,   400,
      -1,   191,   471,    -1,   191,   471,   472,   376,   440,    -1,
      -1,   219,   471,    -1,   194,   471,    -1,   194,   471,   472,
     379,   440,    -1,    -1,   384,   381,   388,   381,    -1,   244,
      15,   349,    21,   381,    -1,    -1,   383,   349,    -1,   382,
       8,   349,    -1,    13,    -1,     6,    -1,   385,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   387,    -1,     5,   534,   491,   535,
     381,    -1,     5,   534,    15,   535,     5,    21,    -1,     5,
     534,    15,   535,   477,    21,    -1,    -1,   387,    -1,    15,
     554,   389,   390,    21,    -1,    15,   554,   389,   390,     8,
     554,   389,   390,    21,    -1,   477,    -1,     5,    -1,   545,
     477,    -1,   545,     5,    -1,    -1,    -1,    26,   477,    -1,
      18,   477,    -1,    87,   472,   471,   349,   454,    -1,   392,
       8,   349,   454,    -1,    44,   471,   472,   400,    -1,   393,
       8,   400,    -1,   187,   471,   472,   400,    -1,   394,     8,
     400,    -1,   236,   471,   472,   400,    -1,   395,     8,   400,
      -1,    67,   471,   400,    -1,    67,   471,   399,   400,    -1,
     396,   528,   399,   528,   400,    -1,   396,     8,   400,    -1,
     167,   471,   398,   480,    -1,   397,   528,   398,   528,   480,
      -1,   397,     8,   480,    -1,    37,   349,    37,    -1,    23,
      -1,    37,   349,    37,    -1,   349,   454,    -1,   119,   471,
     472,   349,    -1,   401,     8,   349,    -1,   143,   471,   472,
     349,    -1,   402,     8,   349,    -1,   117,   471,   404,    -1,
     403,     8,   404,    -1,    15,   405,    21,    -1,   406,     8,
     406,    -1,   405,     8,   406,    -1,   349,    -1,   349,    15,
     476,    21,    -1,   485,    -1,   408,    -1,    80,   470,   409,
     411,    -1,   408,   528,   411,    -1,    -1,    -1,   412,    37,
     413,    37,    -1,   414,    -1,   412,     8,   414,    -1,   425,
      -1,   413,     8,   425,    -1,   415,   417,    -1,   415,   417,
     418,    -1,   415,   417,   419,    -1,   415,   417,   418,   419,
      -1,   415,   422,    -1,    -1,   349,    -1,   349,    -1,    15,
     420,    21,    -1,    15,   421,     7,   421,    21,    -1,   434,
      -1,   420,     8,   434,    -1,    -1,   434,    -1,    15,   423,
       8,   416,    26,   420,    21,    -1,   424,    -1,   423,     8,
     424,    -1,   417,   418,    -1,   417,   419,    -1,   417,   418,
     419,    -1,   422,    -1,   426,    -1,   415,   416,     5,   426,
      -1,   429,     5,   426,    -1,   415,   416,    -1,   428,    -1,
     430,    -1,   432,    -1,    36,    -1,    36,   246,   494,    -1,
      27,    -1,    27,   246,   494,    -1,    64,    -1,   427,    -1,
     415,   480,    15,   554,   473,    21,    -1,    59,    -1,   429,
      -1,    17,   429,    -1,    16,   429,    -1,   149,    -1,   149,
     246,   494,    -1,   431,    -1,    17,   431,    -1,    16,   431,
      -1,   201,    -1,   201,   246,   494,    -1,    92,    -1,    92,
     246,   494,    -1,    15,   433,     8,   433,    21,    -1,   430,
      -1,   428,    -1,   435,    -1,    17,   435,    -1,    16,   435,
      -1,   434,    17,   435,    -1,   434,    16,   435,    -1,   436,
      -1,   435,     5,   436,    -1,   435,    37,   436,    -1,   437,
      -1,   437,     9,   436,    -1,   149,    -1,   416,    -1,    15,
     434,    21,    -1,   439,    -1,   438,     8,   439,    -1,   400,
      -1,   399,    -1,   441,   443,   442,    -1,   440,     8,   441,
     443,   442,    -1,    -1,    -1,   349,    -1,   177,    15,   362,
      21,    -1,    47,    15,    26,    21,    -1,   445,    -1,   444,
       8,   445,    -1,   349,    26,   477,    -1,   163,   447,    -1,
     349,    -1,   447,     8,   349,    -1,   248,   471,   449,    -1,
     248,   471,   449,     8,   358,   452,    -1,   248,   471,   449,
       8,   358,   172,    -1,   248,   471,   449,     8,   358,   172,
     450,    -1,   349,    -1,   451,    -1,   450,     8,   451,    -1,
     349,    18,   349,    -1,   349,    -1,   453,    -1,   452,     8,
     453,    -1,   349,    18,   349,    -1,    -1,    15,   455,    21,
      -1,    -1,   456,   457,    -1,   455,     8,   457,    -1,   458,
      -1,     7,    -1,   477,     7,    -1,   477,     7,   458,    -1,
       5,    -1,   477,    -1,   460,    -1,   459,     8,   460,    -1,
     149,    -1,   130,   471,   462,    -1,   131,    -1,   463,    -1,
     462,     8,   463,    -1,   464,    15,   467,    21,    -1,    -1,
     465,   466,    -1,   231,   385,    -1,   380,    -1,   468,    -1,
     467,     8,   468,    -1,   469,    -1,   469,    16,   469,    -1,
     129,    -1,    -1,    -1,    -1,     7,     7,    -1,    -1,   475,
      -1,   477,    -1,   495,    -1,   545,   477,    -1,   554,   474,
      -1,   475,     8,   554,   474,    -1,   477,    -1,   476,     8,
     477,    -1,   478,    -1,    15,   477,    21,    -1,   493,    -1,
     481,    -1,   489,    -1,   496,    -1,   477,    17,   477,    -1,
     477,    16,   477,    -1,   477,     5,   477,    -1,   477,    37,
     477,    -1,   477,     9,   477,    -1,   361,   477,    -1,    17,
     477,    -1,    16,   477,    -1,   477,    25,   477,    -1,   477,
      29,   477,    -1,   477,    31,   477,    -1,   477,    28,   477,
      -1,   477,    30,   477,    -1,   477,    32,   477,    -1,   477,
      24,   477,    -1,   477,    33,   477,    -1,   477,    38,   477,
      -1,   477,    35,   477,    -1,   477,    22,   477,    -1,    34,
     477,    -1,   477,    23,   477,    -1,   477,   361,   477,    -1,
      17,    -1,    16,    -1,   349,    -1,   480,    -1,   483,    -1,
     482,    -1,   480,    15,   554,   473,    21,    -1,   480,    15,
     554,   473,    21,   487,    -1,   483,    15,   473,    21,    -1,
     483,    15,   473,    21,   487,    -1,   481,     3,   129,    -1,
     480,    -1,   483,    -1,   480,    15,   554,   473,    21,    -1,
     483,    15,   473,    21,    -1,   480,   487,    -1,    -1,   487,
      -1,    15,   488,     7,   488,    21,    -1,    -1,   477,    -1,
     490,    -1,   490,   246,   494,    -1,   491,    -1,   491,   246,
     494,    -1,   492,   486,    -1,    36,    -1,    27,    -1,   201,
      -1,    92,    -1,   149,    -1,    64,    -1,   480,   246,    64,
      -1,   491,   246,    64,    -1,    15,   478,     8,   478,    21,
      -1,   480,    -1,   491,    -1,   477,     7,   477,    -1,   477,
       7,    -1,   477,     7,   477,     7,   477,    -1,   477,     7,
       7,   477,    -1,     7,   477,     7,   477,    -1,     7,     7,
     477,    -1,     7,   477,    -1,     7,    -1,    -1,    -1,    14,
     390,   497,   551,   498,    20,    -1,   480,    -1,   483,    -1,
     484,    -1,   500,     8,   554,   484,    -1,   500,     8,   554,
     545,   480,    -1,   499,    -1,   501,     8,   554,   499,    -1,
     501,     8,   554,   545,   480,    -1,    -1,   480,    -1,   503,
       8,   480,    -1,   525,    -1,   524,    -1,   507,    -1,   515,
     507,    -1,   102,   533,   513,    -1,   103,   533,   512,    -1,
     108,   513,    -1,   505,    -1,   515,   505,    -1,   516,   525,
      -1,   516,   239,    -1,   515,   516,   239,    -1,    97,   533,
      15,   477,    21,   239,   512,    -1,    96,   533,   512,    -1,
     106,   533,   512,    -1,   508,    -1,    76,   533,    -1,   517,
     525,    -1,   517,    -1,   515,   517,    -1,   105,   533,   512,
      -1,   560,    -1,   818,    -1,   834,    -1,    89,   533,    15,
     477,    21,    -1,    89,   533,   534,   523,   535,   594,   506,
      -1,    -1,     8,   356,   254,    15,   477,    21,    -1,   254,
      15,   477,    21,    -1,   185,   533,   534,   523,   535,   528,
     521,    26,   477,     8,   477,    -1,   185,   533,   534,   523,
     535,   528,   521,    26,   477,     8,   477,     8,   477,    -1,
      62,   533,   509,   512,    -1,    84,   533,   512,    -1,   110,
     533,   512,    -1,   218,   533,   356,    62,    15,   477,    21,
      -1,   515,   218,   533,   356,    62,    15,   477,    21,    -1,
      15,   511,    21,    -1,   477,    -1,   477,     7,    -1,     7,
     477,    -1,   477,     7,   477,    -1,   510,    -1,   511,     8,
     510,    -1,    -1,   349,    -1,    -1,   349,    -1,    75,    -1,
     514,     7,    -1,   155,   533,    15,   477,    21,    -1,   122,
     533,    15,   518,   520,    21,    -1,   519,    -1,   518,     8,
     519,    -1,   521,    26,   495,    -1,    -1,     8,   477,    -1,
     349,    -1,   521,    26,   477,     8,   477,    -1,   521,    26,
     477,     8,   477,     8,   477,    -1,    -1,   149,    -1,   113,
     533,   512,    -1,    98,   533,   512,    -1,    98,   533,    15,
     477,    21,   512,    -1,   252,   533,    15,   477,    21,    -1,
     515,   252,   533,    15,   477,    21,    -1,   526,   477,    26,
     477,    -1,   188,   533,   481,    18,   477,    -1,    48,   533,
     460,   240,   349,    -1,    77,   533,    -1,   527,    -1,   536,
      -1,    46,   533,    15,   477,    21,   460,     8,   460,     8,
     460,    -1,   529,    -1,   529,    15,    21,    -1,   529,    15,
     530,    21,    -1,   214,   533,   488,    -1,   532,   533,   488,
      -1,    79,   533,   512,    -1,   115,   533,   512,    -1,    45,
     533,    15,   502,   500,    21,    -1,    81,   533,    15,   502,
     501,    21,    -1,   170,   533,    15,   503,    21,    -1,   253,
     533,    15,   477,    21,   481,    26,   477,    -1,   152,   410,
      -1,   186,   533,   460,    -1,    49,   533,   349,    -1,    49,
     533,   349,   528,    15,   459,    21,    -1,    69,   533,    15,
     459,    21,   528,   477,    -1,    -1,     8,    -1,    61,   533,
     349,   554,    -1,   554,   531,    -1,   530,     8,   554,   531,
      -1,   477,    -1,   545,   477,    -1,     5,   460,    -1,   184,
      -1,   232,    -1,    -1,    -1,    -1,   537,   542,    -1,   537,
     557,    -1,   537,     5,    -1,   537,     9,    -1,   539,   542,
      -1,   546,   542,    -1,   546,   541,    -1,   546,   542,   549,
      -1,   546,   541,     8,   549,    -1,   547,   542,    -1,   547,
     542,   551,    -1,   548,    -1,   548,     8,   551,    -1,   538,
     533,   555,    -1,    53,    -1,   215,    -1,   104,    -1,   540,
     533,   555,    -1,   139,    -1,   176,    -1,    66,    -1,   557,
      -1,     5,    -1,    15,   556,    21,    -1,    15,   543,    21,
      -1,   544,    -1,   543,     8,   554,   544,    -1,   556,    -1,
       5,    -1,     9,    -1,   545,   477,    -1,   545,     5,    -1,
     545,     9,    -1,   166,    -1,   197,   533,   555,    -1,   256,
     533,   555,    -1,   190,   533,   556,   555,    -1,   190,   533,
       5,   555,    -1,   550,    -1,   549,     8,   550,    -1,   481,
      -1,    15,   549,     8,   522,    21,    -1,   478,    -1,   553,
      -1,   552,    -1,   478,     8,   478,    -1,   478,     8,   553,
      -1,   553,     8,   478,    -1,   553,     8,   553,    -1,   552,
       8,   478,    -1,   552,     8,   553,    -1,   493,    -1,    15,
     477,    21,    -1,    15,   478,     8,   522,    21,    -1,    15,
     553,     8,   522,    21,    -1,    15,   552,     8,   522,    21,
      -1,    -1,    -1,   557,    -1,    15,   556,    21,    -1,   481,
      -1,   489,    -1,   556,   479,   556,    -1,   556,     5,   556,
      -1,   556,    37,   556,    -1,   556,     9,   556,    -1,   479,
     556,    -1,   556,    23,   556,    -1,   129,    26,   477,    -1,
      -1,   257,    -1,   561,    -1,   609,    -1,   584,    -1,   563,
      -1,   574,    -1,   569,    -1,   621,    -1,   624,    -1,   700,
      -1,   566,    -1,   575,    -1,   577,    -1,   579,    -1,   581,
      -1,   629,    -1,   635,    -1,   632,    -1,   755,    -1,   753,
      -1,   585,    -1,   610,    -1,   639,    -1,   689,    -1,   687,
      -1,   688,    -1,   690,    -1,   691,    -1,   692,    -1,   693,
      -1,   694,    -1,   702,    -1,   704,    -1,   709,    -1,   706,
      -1,   708,    -1,   712,    -1,   710,    -1,   711,    -1,   723,
      -1,   727,    -1,   728,    -1,   730,    -1,   731,    -1,   732,
      -1,   733,    -1,   734,    -1,   638,    -1,   717,    -1,   718,
      -1,   719,    -1,   722,    -1,   735,    -1,   738,    -1,   743,
      -1,   748,    -1,   750,    -1,   751,    -1,   752,    -1,   715,
      -1,   754,    -1,    82,   471,   562,    -1,   561,     8,   562,
      -1,   349,   454,    -1,    94,   471,   564,    -1,   565,    -1,
     564,     8,   565,    -1,   349,    -1,   138,   471,   567,    -1,
     568,    -1,   567,     8,   568,    -1,   349,    -1,   228,   471,
     573,   570,    -1,    15,   571,    21,    -1,   572,    -1,   571,
       8,   572,    -1,   477,    -1,   477,     7,   477,    -1,   349,
      -1,   259,   471,   349,   454,    -1,   303,   471,   349,   454,
      -1,   574,     8,   349,   454,    -1,   136,   471,   576,    -1,
     575,     8,   576,    -1,   349,    -1,   211,   471,   578,    -1,
     577,     8,   578,    -1,   349,    -1,   205,   471,   580,    -1,
     579,     8,   580,    -1,   349,    -1,    70,   471,   582,    -1,
     581,     8,   582,    -1,   349,    -1,   175,   349,   454,    -1,
      -1,    88,   471,   588,   591,   583,    -1,   204,   533,   588,
     592,   594,   583,    -1,   204,   533,   592,   594,   583,     7,
       7,   586,    -1,   587,    -1,   586,     8,   587,    -1,   588,
      -1,   589,    -1,   349,    -1,   349,    15,   476,    21,    -1,
     349,    -1,    -1,   592,   594,    -1,    15,   593,    21,    -1,
     594,   595,    -1,   593,     8,   594,   595,    -1,    -1,    58,
      -1,    58,    15,   554,   608,    21,    -1,   126,    15,   596,
      21,    -1,   258,    15,   596,     8,   477,    21,    -1,   165,
      15,   477,    21,    -1,     5,    -1,   137,    15,   596,    21,
      -1,    86,    15,   597,    21,    -1,   349,    -1,    15,   598,
      21,   356,   255,   600,    -1,   599,    -1,   598,     8,   599,
      -1,   477,    -1,   601,    -1,   601,    15,   602,    21,    -1,
     349,    -1,   603,    -1,   602,     8,   603,    -1,   477,    -1,
     747,    -1,    40,   604,   605,    -1,   349,    -1,    -1,   606,
      -1,    17,   607,    -1,   605,    17,   607,    -1,   477,    -1,
     545,   477,    -1,   545,   477,     8,   545,   477,    -1,    43,
     471,   612,   614,    -1,   199,   533,   613,   614,    -1,   199,
     533,   614,     7,     7,   611,    -1,   613,    -1,   611,     8,
     613,    -1,   349,    -1,   480,    -1,    15,   619,    21,   356,
     255,   615,    -1,   618,    15,   616,    21,    -1,   617,    -1,
     616,     8,   617,    -1,   477,    -1,     5,    -1,   495,    -1,
     349,    -1,   620,    -1,   619,     8,   620,    -1,   349,    -1,
       5,    -1,     7,    -1,   622,     7,     7,   471,   349,   454,
      -1,   621,     8,   349,   454,    -1,   623,    -1,   622,     8,
     356,   623,    -1,    82,    -1,   259,    -1,   303,    -1,    94,
      -1,    87,    15,   455,    21,    -1,   228,   570,    -1,    43,
      15,   619,    21,   356,   255,   615,    -1,    43,    -1,    88,
     592,   594,   583,    -1,    88,    -1,    67,    -1,   380,     8,
     356,    93,   471,    15,   625,    21,     7,     7,   627,    -1,
      -1,   626,     7,    -1,   625,     8,     7,    -1,   628,    -1,
     627,     8,   628,    -1,   349,    -1,   127,   471,   630,    -1,
     631,    -1,   630,     8,   631,    -1,   349,    -1,    74,   471,
     633,    -1,   634,    -1,   633,     8,   634,    -1,   349,    -1,
      51,   471,   636,    -1,    51,   471,     8,   356,    67,     7,
       7,   636,    -1,   637,    -1,   636,     8,   637,    -1,   349,
     454,    -1,   168,   533,    -1,   182,   533,    15,   640,    21,
     642,   646,    -1,   641,    -1,   640,     8,   641,    -1,   480,
      -1,   594,   173,   643,    -1,   594,    -1,   480,    15,   644,
      21,    -1,   645,    -1,   644,     8,   645,    -1,   477,    -1,
       5,    -1,    -1,   647,    -1,   648,    -1,   647,   648,    -1,
     652,    -1,   672,    -1,   680,    -1,   649,    -1,   657,    -1,
     659,    -1,   658,    -1,   650,    -1,   653,    -1,   654,    -1,
       8,   356,   209,    15,   695,     7,   696,    21,    -1,     8,
     356,   209,    15,   696,    21,    -1,     8,   356,    71,    15,
     651,     7,   696,    21,    -1,     8,   356,    71,    15,   696,
      21,    -1,   349,    -1,     8,   356,   169,    15,   656,    21,
      -1,     8,   356,   282,    15,   656,    21,    -1,     8,   356,
     191,    15,   656,    21,    -1,     8,   356,   320,    15,   655,
      21,    -1,   477,    -1,   477,     8,   477,    -1,   477,     8,
     477,     8,   477,    -1,   481,    -1,   656,     8,   481,    -1,
       8,   356,   135,    15,   695,     7,   713,    21,    -1,     8,
     356,   135,    15,   713,    21,    -1,     8,   356,   229,    15,
     477,    21,    -1,     8,   356,    41,   660,    -1,     8,   356,
      41,   660,   660,    -1,    15,   594,   661,   662,    21,    -1,
     148,     7,    -1,   180,     7,    -1,    -1,   663,    -1,   662,
       8,   663,    -1,   685,    -1,   685,    15,   664,    21,    -1,
     685,    15,   664,    21,    15,   666,    21,    -1,   665,    -1,
     664,     8,   665,    -1,   477,     7,   477,    -1,   667,    -1,
     666,     8,   667,    -1,   668,     7,   669,     7,   670,    -1,
     668,     7,   669,    -1,   668,     7,   670,    -1,   668,    -1,
     669,     7,   670,    -1,   669,    -1,   670,    -1,   356,   217,
     671,    -1,   356,   157,   671,    -1,   356,   128,   671,    -1,
      15,   475,    21,    -1,     8,   356,   208,    15,   673,   677,
     674,     8,   676,    21,    -1,     8,   356,   208,    15,   673,
     677,   674,    21,    -1,     8,   356,   208,    15,   673,   675,
     674,     7,   676,    21,    -1,    -1,    -1,   349,    -1,   356,
     677,    -1,   676,     8,   356,   677,    -1,   678,    15,   481,
      21,    -1,   679,    15,   656,     8,   477,    21,    -1,   234,
      -1,   192,    -1,   162,    -1,   159,    -1,    35,    -1,    22,
      -1,    24,    -1,    33,    -1,   247,    -1,   158,    -1,   161,
      -1,     8,   356,   223,    15,   682,    21,    -1,     8,   356,
     224,   681,    -1,     8,   356,   226,   681,    -1,     8,   356,
     221,    -1,     8,   356,   221,    15,   685,    15,   571,    21,
      21,    -1,   349,    -1,   683,    -1,   682,     8,   683,    -1,
     685,    -1,   685,    15,   684,    78,    21,    -1,   685,    15,
     684,   571,    21,    -1,   685,    15,   684,   571,    21,    15,
     356,    78,    21,    -1,    -1,   480,    -1,   685,    -1,   686,
       8,   685,    -1,   225,   533,   681,    -1,   224,   533,   681,
      -1,   227,   533,   681,    -1,   226,   533,   681,    -1,   222,
     533,   681,    15,   682,    21,    -1,   206,   533,   675,    -1,
     207,   533,   675,    -1,    72,   533,   651,    -1,    73,   533,
     651,    -1,   210,   533,    15,   695,     7,   696,    21,    -1,
     210,   533,    15,   696,    21,    -1,   349,    -1,   697,    -1,
     696,     8,   697,    -1,   685,    15,   698,    21,    -1,   685,
      -1,   699,    -1,   698,     8,   699,    -1,   477,    -1,     7,
      -1,   237,   471,   701,    -1,   700,     8,   701,    -1,   349,
     454,    -1,   238,   533,   703,    -1,   238,   533,   703,   672,
      -1,   238,   533,   703,   650,    -1,   238,   533,   703,   672,
     650,    -1,   238,   533,   703,   650,   672,    -1,   349,    -1,
     111,   533,    -1,   703,    15,   477,    21,    -1,   703,    15,
     495,    21,    -1,   174,   533,   482,   707,    -1,    -1,   652,
      -1,   109,   533,    -1,   160,   533,   705,   356,   175,   590,
     454,    -1,   160,   533,   705,   356,   321,   481,    -1,   189,
     533,   695,    -1,   212,   533,   695,    -1,   135,   533,    15,
     695,     7,   713,    21,    -1,   135,   533,    15,   713,    21,
      -1,   714,    -1,   713,     8,   714,    -1,   685,    -1,   685,
      15,   476,    21,    -1,   134,   533,    -1,   134,   533,   652,
      -1,   134,   533,   716,    -1,   134,   533,   652,   716,    -1,
       8,   356,   208,    15,   656,    21,    -1,    50,   533,   721,
      -1,    99,   533,    -1,    52,   533,   721,    -1,   349,    -1,
     720,    -1,   720,    15,   476,    21,    -1,   120,   533,   481,
      26,   481,    -1,    83,   533,   726,    -1,    83,   533,   726,
      15,   724,    21,    -1,   554,   725,    -1,   724,     8,   554,
     725,    -1,   545,   477,    -1,   149,    -1,   100,   533,   726,
      -1,   146,   533,   729,    -1,    -1,   477,    -1,   101,   533,
      -1,   241,   533,    -1,   242,   533,    -1,    56,   533,    -1,
      65,   533,   554,    15,   530,    21,   390,   472,   656,    -1,
     322,   533,    15,   736,    21,    -1,   737,    -1,   736,     8,
     737,    -1,   356,   315,    -1,   356,   318,    -1,   356,   182,
      -1,   220,   533,    15,   739,    26,   607,    21,   594,   742,
      -1,   480,    15,   740,    21,    -1,   741,    -1,   740,     8,
     741,    -1,   597,    -1,   747,    -1,   132,   686,    -1,    -1,
     153,   533,    15,   480,    18,   744,    21,    -1,   480,    -1,
     480,    15,   745,    21,    -1,   746,    -1,   745,     8,   746,
      -1,   747,    -1,     7,    -1,     5,    -1,   329,   533,   477,
       8,   356,   334,    15,   656,    21,     8,   356,   333,    15,
     476,    21,   749,    -1,    -1,     8,   356,   182,    -1,     8,
     356,   318,    -1,   330,   533,   477,    -1,   331,   533,   477,
      -1,   331,   533,   477,     8,   356,   315,    -1,   332,   533,
     477,     8,   356,   335,    15,   480,    21,    -1,   804,    -1,
     757,    -1,   756,    -1,   774,    -1,   777,    -1,   778,    -1,
     779,    -1,   780,    -1,   786,    -1,   789,    -1,   794,    -1,
     795,    -1,   796,    -1,   799,    -1,   800,    -1,   801,    -1,
     802,    -1,   803,    -1,   805,    -1,   806,    -1,   807,    -1,
     808,    -1,   809,    -1,   810,    -1,   811,    -1,   812,    -1,
     813,    -1,   268,   533,    -1,   275,   533,    -1,   291,   533,
     594,   758,    -1,   291,   533,   594,    -1,   528,   594,   759,
     594,    -1,   758,   528,   594,   759,   594,    -1,   761,    -1,
     770,    -1,   765,    -1,   766,    -1,   762,    -1,   763,    -1,
     764,    -1,   768,    -1,   769,    -1,   816,    15,   817,   815,
      21,    -1,   191,   760,    -1,   282,   760,    -1,   285,   760,
      -1,   265,   760,    -1,   299,   760,    -1,    84,    15,   356,
     767,    21,    -1,   191,    -1,   299,    -1,   288,    -1,   304,
      15,   477,    21,    -1,   289,    15,   477,    21,    -1,   208,
      15,   771,    21,    -1,   594,   773,     7,   772,    -1,   656,
      -1,    17,    -1,    16,    -1,     5,    -1,    37,    -1,   162,
      -1,   159,    -1,    35,    -1,    22,    -1,    24,    -1,    33,
      -1,   305,    -1,   306,    -1,   307,    -1,   247,    -1,   297,
     533,   594,   775,    -1,   297,   533,   594,    -1,   528,   594,
     776,   594,    -1,   775,   528,   594,   776,   594,    -1,   761,
      -1,   770,    -1,   762,    -1,   763,    -1,   279,   533,   594,
     793,    -1,   279,   533,   594,    -1,   296,   533,    -1,   269,
     533,   594,   781,    -1,   269,   533,   594,    -1,   272,   533,
     594,   793,    -1,   272,   533,   594,    -1,   528,   594,   782,
     594,    -1,   781,   528,   594,   782,   594,    -1,   761,    -1,
     770,    -1,   762,    -1,   763,    -1,   784,    -1,   783,    -1,
     290,    -1,   298,    15,   356,   785,     8,   477,    21,    -1,
     298,    15,   356,   785,    21,    -1,   230,    -1,    94,    -1,
     284,    -1,   295,    -1,   300,   533,   594,   787,    -1,   300,
     533,   594,    -1,   528,   594,   788,   594,    -1,   787,   528,
     594,   788,   594,    -1,   761,    -1,   762,    -1,   280,   533,
     594,   790,    -1,   280,   533,   594,    -1,   528,   594,   791,
     594,    -1,   790,   528,   594,   791,   594,    -1,   793,    -1,
     792,    -1,   266,   760,    -1,   287,    -1,   302,   533,    -1,
     281,   533,   594,   793,    -1,   281,   533,   594,    -1,   292,
     533,   594,   797,    -1,   292,   533,   594,    -1,   528,   594,
     798,   594,    -1,   797,   528,   594,   798,   594,    -1,   761,
      -1,   770,    -1,   765,    -1,   766,    -1,   762,    -1,   763,
      -1,   764,    -1,   768,    -1,   769,    -1,   784,    -1,   783,
      -1,   276,   533,    -1,   293,   533,   594,   758,    -1,   293,
     533,   594,    -1,   277,   533,    -1,   294,   533,   594,   758,
      -1,   294,   533,   594,    -1,   278,   533,    -1,   301,   471,
     760,    -1,   286,   533,    -1,   273,   533,    -1,   290,   533,
      -1,   274,   533,    -1,   264,   533,    -1,   263,   533,    -1,
     283,   533,   760,    -1,   283,   533,    -1,   267,   533,    15,
     480,    21,    -1,   267,   533,    -1,   271,   533,    15,   480,
      21,    -1,   271,   533,    -1,    37,   349,   816,    37,   817,
      -1,   814,    -1,   480,    -1,   815,     8,   814,    -1,   815,
       8,   480,    -1,    -1,    -1,   819,    -1,   832,    -1,   820,
      -1,   833,    -1,   821,    -1,   822,    -1,   308,   533,   823,
      -1,   310,   533,    -1,   312,   533,    15,   829,    21,    -1,
     312,   533,    15,    21,    -1,   312,   533,    -1,   313,   533,
      15,   829,    21,    -1,   313,   533,    15,    21,    -1,   313,
     533,    -1,   356,   357,    -1,   824,    -1,   825,    -1,   824,
       8,   825,    -1,   356,   826,    -1,   356,   828,    -1,   356,
     827,    -1,   147,    15,   829,    21,    -1,   148,    15,   829,
      21,    -1,   180,    15,   829,    21,    -1,   318,    15,   829,
      21,    -1,   319,    15,   829,    21,    -1,   314,    15,   830,
      21,    -1,   315,    -1,   656,    -1,   831,    -1,   830,     8,
     831,    -1,   356,   316,    -1,   356,   317,    -1,   309,    -1,
     311,    -1,   835,    -1,   836,    -1,   837,    -1,   838,    -1,
     839,    -1,   323,    15,   840,    21,    -1,   324,    15,   844,
      21,    -1,   325,    15,   849,    21,    -1,   327,   851,    -1,
     328,    -1,   841,    -1,   840,     8,   841,    -1,   842,    -1,
     843,    -1,   356,   208,    15,   676,    21,    -1,   356,   191,
      15,   656,    21,    -1,   845,    -1,   844,     8,   845,    -1,
     846,    -1,   847,    -1,   848,    -1,   356,   228,    15,   682,
      21,    -1,   356,    41,    15,   682,    21,    -1,   356,   209,
      15,   696,    21,    -1,   850,    -1,   849,     8,   850,    -1,
     356,   326,    -1,   349,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   764,   764,   765,   769,   771,   785,   816,   825,   831,
     851,   860,   876,   888,   898,   905,   911,   916,   921,   945,
     972,   986,   988,   990,   994,  1011,  1025,  1049,  1065,  1079,
    1097,  1099,  1106,  1110,  1111,  1118,  1119,  1127,  1128,  1130,
    1134,  1135,  1139,  1143,  1149,  1159,  1163,  1168,  1175,  1176,
    1177,  1178,  1179,  1180,  1181,  1182,  1183,  1184,  1185,  1186,
    1187,  1188,  1193,  1198,  1205,  1207,  1208,  1209,  1210,  1211,
    1212,  1213,  1214,  1215,  1216,  1217,  1218,  1221,  1225,  1233,
    1241,  1250,  1258,  1262,  1264,  1268,  1270,  1272,  1274,  1276,
    1278,  1280,  1282,  1284,  1286,  1288,  1290,  1292,  1294,  1296,
    1298,  1300,  1302,  1307,  1316,  1326,  1334,  1344,  1365,  1385,
    1386,  1388,  1392,  1394,  1398,  1402,  1404,  1408,  1414,  1418,
    1420,  1424,  1428,  1432,  1436,  1440,  1446,  1450,  1454,  1460,
    1465,  1472,  1483,  1496,  1507,  1520,  1530,  1543,  1548,  1555,
    1558,  1563,  1568,  1575,  1578,  1588,  1602,  1605,  1624,  1651,
    1653,  1665,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1684,
    1685,  1689,  1691,  1698,  1703,  1704,  1706,  1708,  1721,  1727,
    1733,  1742,  1751,  1764,  1765,  1768,  1772,  1787,  1802,  1820,
    1841,  1861,  1883,  1900,  1918,  1925,  1932,  1939,  1952,  1959,
    1966,  1977,  1981,  1983,  1988,  2006,  2017,  2029,  2041,  2055,
    2061,  2068,  2074,  2080,  2088,  2095,  2111,  2114,  2123,  2125,
    2129,  2133,  2153,  2157,  2159,  2163,  2164,  2167,  2169,  2171,
    2173,  2175,  2178,  2181,  2185,  2191,  2195,  2199,  2201,  2206,
    2207,  2211,  2215,  2217,  2221,  2223,  2225,  2230,  2234,  2236,
    2238,  2241,  2243,  2244,  2245,  2246,  2247,  2248,  2249,  2250,
    2253,  2254,  2260,  2263,  2264,  2266,  2270,  2271,  2274,  2275,
    2277,  2281,  2282,  2283,  2284,  2286,  2289,  2290,  2299,  2301,
    2308,  2315,  2322,  2331,  2333,  2335,  2339,  2341,  2345,  2354,
    2361,  2368,  2370,  2374,  2378,  2384,  2386,  2391,  2395,  2399,
    2406,  2413,  2423,  2425,  2429,  2441,  2444,  2453,  2466,  2472,
    2478,  2484,  2492,  2502,  2504,  2508,  2529,  2554,  2556,  2560,
    2592,  2593,  2597,  2597,  2602,  2606,  2614,  2623,  2632,  2642,
    2648,  2651,  2653,  2657,  2665,  2680,  2687,  2689,  2693,  2709,
    2709,  2713,  2715,  2727,  2729,  2733,  2739,  2751,  2763,  2780,
    2809,  2810,  2818,  2819,  2823,  2825,  2827,  2838,  2842,  2848,
    2850,  2854,  2856,  2858,  2862,  2864,  2868,  2870,  2872,  2874,
    2876,  2878,  2880,  2882,  2884,  2886,  2888,  2890,  2892,  2894,
    2896,  2898,  2900,  2902,  2904,  2906,  2908,  2910,  2912,  2916,
    2917,  2928,  3002,  3014,  3016,  3020,  3151,  3201,  3245,  3287,
    3345,  3347,  3349,  3388,  3431,  3442,  3443,  3447,  3452,  3453,
    3457,  3459,  3465,  3467,  3473,  3483,  3489,  3496,  3502,  3510,
    3518,  3534,  3544,  3557,  3564,  3566,  3589,  3591,  3593,  3595,
    3597,  3599,  3601,  3603,  3607,  3607,  3607,  3621,  3623,  3646,
    3648,  3650,  3666,  3668,  3670,  3684,  3687,  3689,  3697,  3699,
    3701,  3703,  3757,  3777,  3792,  3801,  3804,  3854,  3860,  3865,
    3883,  3885,  3887,  3889,  3891,  3894,  3900,  3902,  3904,  3907,
    3909,  3911,  3938,  3947,  3956,  3957,  3959,  3964,  3971,  3979,
    3981,  3985,  3988,  3990,  3994,  4000,  4002,  4004,  4006,  4010,
    4012,  4021,  4022,  4029,  4030,  4034,  4038,  4059,  4062,  4066,
    4068,  4075,  4080,  4081,  4092,  4109,  4132,  4157,  4158,  4165,
    4167,  4169,  4171,  4173,  4177,  4253,  4265,  4272,  4274,  4275,
    4277,  4286,  4293,  4300,  4308,  4313,  4318,  4321,  4324,  4327,
    4330,  4333,  4337,  4355,  4360,  4379,  4398,  4402,  4403,  4406,
    4410,  4415,  4422,  4424,  4426,  4430,  4431,  4442,  4457,  4461,
    4468,  4471,  4481,  4494,  4507,  4511,  4514,  4517,  4521,  4530,
    4533,  4537,  4539,  4545,  4549,  4551,  4553,  4560,  4564,  4566,
    4568,  4572,  4591,  4607,  4616,  4625,  4627,  4631,  4657,  4672,
    4687,  4704,  4712,  4721,  4729,  4734,  4739,  4761,  4777,  4779,
    4783,  4785,  4792,  4794,  4796,  4800,  4802,  4804,  4806,  4808,
    4810,  4814,  4817,  4820,  4826,  4832,  4841,  4845,  4852,  4854,
    4858,  4860,  4862,  4867,  4872,  4877,  4882,  4891,  4896,  4902,
    4903,  4918,  4919,  4920,  4921,  4922,  4923,  4924,  4925,  4926,
    4927,  4928,  4929,  4930,  4931,  4932,  4933,  4934,  4935,  4936,
    4939,  4940,  4941,  4942,  4943,  4944,  4945,  4946,  4947,  4948,
    4949,  4950,  4951,  4952,  4953,  4954,  4955,  4956,  4957,  4958,
    4959,  4960,  4961,  4962,  4963,  4964,  4965,  4966,  4967,  4968,
    4969,  4970,  4971,  4972,  4973,  4974,  4975,  4976,  4977,  4978,
    4979,  4983,  4985,  4996,  5016,  5020,  5022,  5026,  5039,  5043,
    5045,  5049,  5060,  5071,  5075,  5077,  5081,  5083,  5093,  5105,
    5125,  5145,  5167,  5173,  5182,  5190,  5196,  5204,  5211,  5217,
    5226,  5230,  5236,  5244,  5258,  5272,  5277,  5293,  5308,  5336,
    5338,  5342,  5344,  5348,  5377,  5400,  5421,  5422,  5426,  5447,
    5449,  5453,  5461,  5465,  5470,  5472,  5474,  5476,  5482,  5484,
    5488,  5498,  5502,  5504,  5509,  5513,  5517,  5523,  5533,  5535,
    5539,  5541,  5543,  5550,  5568,  5569,  5573,  5575,  5579,  5586,
    5596,  5625,  5640,  5647,  5665,  5667,  5671,  5685,  5711,  5724,
    5740,  5742,  5745,  5747,  5753,  5757,  5785,  5787,  5791,  5799,
    5805,  5808,  5865,  5929,  5931,  5934,  5938,  5942,  5946,  5963,
    5975,  5979,  5983,  5993,  5998,  6003,  6010,  6019,  6019,  6030,
    6041,  6043,  6047,  6058,  6062,  6064,  6068,  6079,  6083,  6085,
    6089,  6101,  6103,  6110,  6112,  6116,  6132,  6140,  6151,  6153,
    6157,  6160,  6163,  6168,  6178,  6180,  6184,  6186,  6195,  6196,
    6200,  6202,  6207,  6208,  6209,  6210,  6211,  6212,  6213,  6214,
    6215,  6216,  6219,  6224,  6228,  6232,  6236,  6249,  6253,  6257,
    6261,  6264,  6266,  6268,  6272,  6274,  6278,  6283,  6287,  6291,
    6293,  6297,  6305,  6311,  6318,  6321,  6323,  6327,  6329,  6333,
    6345,  6347,  6351,  6355,  6357,  6361,  6363,  6365,  6367,  6369,
    6371,  6373,  6377,  6381,  6385,  6389,  6393,  6400,  6406,  6411,
    6414,  6417,  6430,  6432,  6436,  6438,  6443,  6449,  6455,  6461,
    6467,  6473,  6479,  6485,  6491,  6500,  6506,  6523,  6525,  6533,
    6541,  6543,  6547,  6551,  6553,  6557,  6559,  6567,  6571,  6583,
    6586,  6604,  6606,  6610,  6612,  6616,  6618,  6622,  6626,  6630,
    6639,  6643,  6647,  6652,  6656,  6668,  6670,  6674,  6679,  6683,
    6685,  6689,  6691,  6695,  6700,  6707,  6730,  6732,  6734,  6736,
    6738,  6742,  6753,  6757,  6772,  6779,  6786,  6787,  6791,  6795,
    6803,  6807,  6811,  6819,  6824,  6838,  6840,  6844,  6846,  6855,
    6857,  6859,  6861,  6897,  6901,  6905,  6909,  6913,  6925,  6927,
    6931,  6934,  6936,  6940,  6945,  6952,  6955,  6963,  6967,  6972,
    6974,  6981,  6985,  6989,  6993,  6997,  7001,  7004,  7006,  7010,
    7012,  7014,  7018,  7022,  7034,  7036,  7040,  7042,  7046,  7049,
    7052,  7056,  7062,  7074,  7076,  7080,  7082,  7086,  7094,  7106,
    7107,  7109,  7113,  7117,  7119,  7127,  7130,  7132,  7133,  7134,
    7135,  7136,  7137,  7138,  7139,  7140,  7141,  7142,  7143,  7144,
    7145,  7146,  7147,  7148,  7149,  7150,  7151,  7152,  7153,  7154,
    7155,  7156,  7157,  7160,  7166,  7172,  7178,  7184,  7188,  7194,
    7195,  7196,  7197,  7198,  7199,  7200,  7201,  7202,  7205,  7210,
    7215,  7221,  7227,  7233,  7238,  7244,  7250,  7256,  7263,  7269,
    7275,  7282,  7286,  7288,  7294,  7301,  7307,  7313,  7319,  7325,
    7331,  7337,  7343,  7349,  7355,  7361,  7367,  7377,  7382,  7388,
    7392,  7398,  7399,  7400,  7401,  7404,  7412,  7418,  7424,  7429,
    7435,  7442,  7448,  7452,  7458,  7459,  7460,  7461,  7462,  7463,
    7466,  7475,  7479,  7485,  7492,  7499,  7506,  7515,  7521,  7527,
    7531,  7537,  7538,  7541,  7547,  7553,  7557,  7564,  7565,  7568,
    7574,  7580,  7585,  7593,  7599,  7604,  7611,  7615,  7621,  7622,
    7623,  7624,  7625,  7626,  7627,  7628,  7629,  7630,  7631,  7635,
    7640,  7645,  7652,  7657,  7663,  7669,  7674,  7679,  7684,  7688,
    7693,  7698,  7702,  7707,  7711,  7717,  7722,  7728,  7733,  7739,
    7749,  7753,  7757,  7761,  7767,  7770,  7774,  7775,  7776,  7777,
    7778,  7779,  7782,  7786,  7790,  7792,  7794,  7798,  7800,  7802,
    7806,  7808,  7812,  7814,  7818,  7821,  7824,  7829,  7831,  7833,
    7835,  7837,  7841,  7845,  7850,  7854,  7856,  7860,  7862,  7866,
    7870,  7874,  7875,  7876,  7877,  7878,  7881,  7885,  7889,  7893,
    7897,  7901,  7903,  7907,  7908,  7911,  7915,  7919,  7921,  7925,
    7926,  7927,  7931,  7935,  7939,  7943,  7945,  7949,  7953
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PERCENT", "AMPERSAND", "ASTER",
  "CLUSTER", "COLON", "COMMA", "DASTER", "DEFINED_OPERATOR", "DOT",
  "DQUOTE", "GLOBAL_A", "LEFTAB", "LEFTPAR", "MINUS", "PLUS", "POINT_TO",
  "QUOTE", "RIGHTAB", "RIGHTPAR", "AND", "DSLASH", "EQV", "EQ", "EQUAL",
  "FFALSE", "GE", "GT", "LE", "LT", "NE", "NEQV", "NOT", "OR", "TTRUE",
  "SLASH", "XOR", "REFERENCE", "AT", "ACROSS", "ALIGN_WITH", "ALIGN",
  "ALLOCATABLE", "ALLOCATE", "ARITHIF", "ASSIGNMENT", "ASSIGN",
  "ASSIGNGOTO", "ASYNCHRONOUS", "ASYNCID", "ASYNCWAIT", "BACKSPACE",
  "BAD_CCONST", "BAD_SYMBOL", "BARRIER", "BLOCKDATA", "BLOCK",
  "BOZ_CONSTANT", "BYTE", "CALL", "CASE", "CHARACTER", "CHAR_CONSTANT",
  "CHECK", "CLOSE", "COMMON", "COMPLEX", "COMPGOTO", "CONSISTENT_GROUP",
  "CONSISTENT_SPEC", "CONSISTENT_START", "CONSISTENT_WAIT", "CONSISTENT",
  "CONSTRUCT_ID", "CONTAINS", "CONTINUE", "CORNER", "CYCLE", "DATA",
  "DEALLOCATE", "HPF_TEMPLATE", "DEBUG", "DEFAULT_CASE", "DEFINE",
  "DERIVED", "DIMENSION", "DISTRIBUTE", "DOWHILE", "DOUBLEPRECISION",
  "DOUBLECOMPLEX", "DP_CONSTANT", "DVM_POINTER", "DYNAMIC", "ELEMENTAL",
  "ELSE", "ELSEIF", "ELSEWHERE", "ENDASYNCHRONOUS", "ENDDEBUG",
  "ENDINTERVAL", "ENDUNIT", "ENDDO", "ENDFILE", "ENDFORALL", "ENDIF",
  "ENDINTERFACE", "ENDMODULE", "ENDON", "ENDSELECT", "ENDTASK_REGION",
  "ENDTYPE", "ENDWHERE", "ENTRY", "EXIT", "EOLN", "EQUIVALENCE", "ERROR",
  "EXTERNAL", "F90", "FIND", "FORALL", "FORMAT", "FUNCTION", "GATE",
  "GEN_BLOCK", "HEAP", "HIGH", "IDENTIFIER", "IMPLICIT", "IMPLICITNONE",
  "INCLUDE_TO", "INCLUDE", "INDEPENDENT", "INDIRECT_ACCESS",
  "INDIRECT_GROUP", "INDIRECT", "INHERIT", "INQUIRE",
  "INTERFACEASSIGNMENT", "INTERFACEOPERATOR", "INTERFACE", "INTRINSIC",
  "INTEGER", "INTENT", "INTERVAL", "INOUT", "IN", "INT_CONSTANT", "LABEL",
  "LABEL_DECLARE", "LET", "LOCALIZE", "LOGICAL", "LOGICALIF", "LOOP",
  "LOW", "MAXLOC", "MAX", "MAP", "MINLOC", "MIN", "MODULE_PROCEDURE",
  "MODULE", "MULT_BLOCK", "NAMEEQ", "NAMELIST", "NEW_VALUE", "NEW",
  "NULLIFY", "OCTAL_CONSTANT", "ONLY", "ON", "ON_DIR", "ONTO", "OPEN",
  "OPERATOR", "OPTIONAL", "OTHERWISE", "OUT", "OWN", "PARALLEL",
  "PARAMETER", "PAUSE", "PLAINDO", "PLAINGOTO", "POINTER", "POINTERLET",
  "PREFETCH", "PRINT", "PRIVATE", "PRODUCT", "PROGRAM", "PUBLIC", "PURE",
  "RANGE", "READ", "REALIGN_WITH", "REALIGN", "REAL", "REAL_CONSTANT",
  "RECURSIVE", "REDISTRIBUTE_NEW", "REDISTRIBUTE", "REDUCTION_GROUP",
  "REDUCTION_START", "REDUCTION_WAIT", "REDUCTION", "REMOTE_ACCESS_SPEC",
  "REMOTE_ACCESS", "REMOTE_GROUP", "RESET", "RESULT", "RETURN", "REWIND",
  "SAVE", "SECTION", "SELECT", "SEQUENCE", "SHADOW_ADD", "SHADOW_COMPUTE",
  "SHADOW_GROUP", "SHADOW_RENEW", "SHADOW_START_SPEC", "SHADOW_START",
  "SHADOW_WAIT_SPEC", "SHADOW_WAIT", "SHADOW", "STAGE", "STATIC", "STAT",
  "STOP", "SUBROUTINE", "SUM", "SYNC", "TARGET", "TASK", "TASK_REGION",
  "THEN", "TO", "TRACEON", "TRACEOFF", "TRUNC", "TYPE", "TYPE_DECL",
  "UNDER", "UNKNOWN", "USE", "VIRTUAL", "VARIABLE", "WAIT", "WHERE",
  "WHERE_ASSIGN", "WHILE", "WITH", "WRITE", "COMMENT", "WGT_BLOCK",
  "HPF_PROCESSORS", "IOSTAT", "ERR", "END", "OMPDVM_ATOMIC",
  "OMPDVM_BARRIER", "OMPDVM_COPYIN", "OMPDVM_COPYPRIVATE",
  "OMPDVM_CRITICAL", "OMPDVM_ONETHREAD", "OMPDVM_DO", "OMPDVM_DYNAMIC",
  "OMPDVM_ENDCRITICAL", "OMPDVM_ENDDO", "OMPDVM_ENDMASTER",
  "OMPDVM_ENDORDERED", "OMPDVM_ENDPARALLEL", "OMPDVM_ENDPARALLELDO",
  "OMPDVM_ENDPARALLELSECTIONS", "OMPDVM_ENDPARALLELWORKSHARE",
  "OMPDVM_ENDSECTIONS", "OMPDVM_ENDSINGLE", "OMPDVM_ENDWORKSHARE",
  "OMPDVM_FIRSTPRIVATE", "OMPDVM_FLUSH", "OMPDVM_GUIDED",
  "OMPDVM_LASTPRIVATE", "OMPDVM_MASTER", "OMPDVM_NOWAIT", "OMPDVM_NONE",
  "OMPDVM_NUM_THREADS", "OMPDVM_ORDERED", "OMPDVM_PARALLEL",
  "OMPDVM_PARALLELDO", "OMPDVM_PARALLELSECTIONS",
  "OMPDVM_PARALLELWORKSHARE", "OMPDVM_RUNTIME", "OMPDVM_SECTION",
  "OMPDVM_SECTIONS", "OMPDVM_SCHEDULE", "OMPDVM_SHARED", "OMPDVM_SINGLE",
  "OMPDVM_THREADPRIVATE", "OMPDVM_WORKSHARE", "OMPDVM_NODES", "OMPDVM_IF",
  "IAND", "IEOR", "IOR", "ACC_REGION", "ACC_END_REGION",
  "ACC_CHECKSECTION", "ACC_END_CHECKSECTION", "ACC_GET_ACTUAL",
  "ACC_ACTUAL", "ACC_TARGETS", "ACC_ASYNC", "ACC_HOST", "ACC_CUDA",
  "ACC_LOCAL", "ACC_INLOCAL", "ACC_CUDA_BLOCK", "BY", "IO_MODE",
  "SPF_ANALYSIS", "SPF_PARALLEL", "SPF_TRANSFORM", "SPF_NOINLINE",
  "SPF_PARALLEL_REG", "SPF_END_PARALLEL_REG", "CP_CREATE", "CP_LOAD",
  "CP_SAVE", "CP_WAIT", "FILES", "VARLIST", "STATUS", "BINARY_OP",
  "UNARY_OP", "$accept", "program", "stat", "thislabel", "entry",
  "new_prog", "proc_attr", "procname", "funcname", "typedfunc",
  "opt_result_clause", "name", "progname", "blokname", "arglist", "args",
  "arg", "filename", "needkeyword", "keywordoff",
  "keyword_if_colon_follow", "spec", "interface", "defined_op", "operator",
  "intrinsic_op", "type_dcl", "end_type", "dcl", "options",
  "attr_spec_list", "attr_spec", "intent_spec", "access_spec", "intent",
  "optional", "static", "private", "private_attr", "sequence", "public",
  "public_attr", "type", "opt_key_hedr", "attrib", "att_type", "typespec",
  "typename", "lengspec", "proper_lengspec", "selector", "clause",
  "end_ioctl", "initial_value", "dimension", "allocatable", "pointer",
  "target", "common", "namelist", "namelist_group", "comblock", "var",
  "external", "intrinsic", "equivalence", "equivset", "equivlist",
  "equi_object", "data", "data1", "data_in", "in_data", "datapair",
  "datalvals", "datarvals", "datalval", "data_null", "d_name", "dataname",
  "datasubs", "datarange", "iconexprlist", "opticonexpr", "dataimplieddo",
  "dlist", "dataelt", "datarval", "datavalue", "BOZ_const", "int_const",
  "unsignedint", "real_const", "unsignedreal", "complex_const_data",
  "complex_part", "iconexpr", "iconterm", "iconfactor", "iconprimary",
  "savelist", "saveitem", "use_name_list", "use_key_word",
  "no_use_key_word", "use_name", "paramlist", "paramitem",
  "module_proc_stmt", "proc_name_list", "use_stat", "module_name",
  "only_list", "only_name", "rename_list", "rename_name", "dims",
  "dimlist", "@1", "dim", "ubound", "labellist", "label", "implicit",
  "implist", "impitem", "imptype", "@2", "type_implicit", "letgroups",
  "letgroup", "letter", "inside", "in_dcl", "opt_double_colon",
  "funarglist", "funarg", "funargs", "subscript_list", "expr", "uexpr",
  "addop", "ident", "lhs", "array_ele_substring_func_ref",
  "structure_component", "array_element", "asubstring", "opt_substring",
  "substring", "opt_expr", "simple_const", "numeric_bool_const",
  "integer_constant", "string_constant", "complex_const", "kind",
  "triplet", "vec", "@3", "@4", "allocate_object", "allocation_list",
  "allocate_object_list", "stat_spec", "pointer_name_list", "exec",
  "do_while", "opt_while", "plain_do", "case", "case_selector",
  "case_value_range", "case_value_range_list", "opt_construct_name",
  "opt_unit_name", "construct_name", "construct_name_colon", "logif",
  "forall", "forall_list", "forall_expr", "opt_forall_cond", "do_var",
  "dospec", "dotarget", "whereable", "iffable", "let", "goto", "opt_comma",
  "call", "callarglist", "callarg", "stop", "end_spec", "intonlyon",
  "intonlyoff", "io", "iofmove", "fmkwd", "iofctl", "ctlkwd", "infmt",
  "ioctl", "ctllist", "ioclause", "nameeq", "read", "write", "print",
  "inlist", "inelt", "outlist", "out2", "other", "in_ioctl", "start_ioctl",
  "fexpr", "unpar_fexpr", "cmnt", "dvm_specification", "dvm_exec",
  "dvm_template", "template_obj", "dvm_dynamic", "dyn_array_name_list",
  "dyn_array_name", "dvm_inherit", "dummy_array_name_list",
  "dummy_array_name", "dvm_shadow", "shadow_attr_stuff", "sh_width_list",
  "sh_width", "sh_array_name", "dvm_processors", "dvm_indirect_group",
  "indirect_group_name", "dvm_remote_group", "remote_group_name",
  "dvm_reduction_group", "reduction_group_name", "dvm_consistent_group",
  "consistent_group_name", "opt_onto", "dvm_distribute",
  "dvm_redistribute", "dist_name_list", "distributee", "dist_name",
  "pointer_ar_elem", "processors_name", "opt_dist_format_clause",
  "dist_format_clause", "dist_format_list", "opt_key_word", "dist_format",
  "array_name", "derived_spec", "derived_elem_list", "derived_elem",
  "target_spec", "derived_target", "derived_subscript_list",
  "derived_subscript", "dummy_ident", "opt_plus_shadow", "plus_shadow",
  "shadow_id", "shadow_width", "dvm_align", "dvm_realign",
  "realignee_list", "alignee", "realignee", "align_directive_stuff",
  "align_base", "align_subscript_list", "align_subscript",
  "align_base_name", "dim_ident_list", "dim_ident", "dvm_combined_dir",
  "dvm_attribute_list", "dvm_attribute", "dvm_pointer", "dimension_list",
  "@5", "pointer_var_list", "pointer_var", "dvm_heap",
  "heap_array_name_list", "heap_array_name", "dvm_consistent",
  "consistent_array_name_list", "consistent_array_name", "dvm_asyncid",
  "async_id_list", "async_id", "dvm_new_value", "dvm_parallel_on",
  "loop_var_list", "loop_var", "opt_on", "distribute_cycles",
  "par_subscript_list", "par_subscript", "opt_spec", "spec_list",
  "par_spec", "remote_access_spec", "consistent_spec", "consistent_group",
  "new_spec", "private_spec", "cuda_block_spec", "sizelist",
  "variable_list", "indirect_access_spec", "stage_spec", "across_spec",
  "in_out_across", "opt_in_out", "dependent_array_list", "dependent_array",
  "dependence_list", "dependence", "section_spec_list", "section_spec",
  "ar_section", "low_section", "high_section", "section", "reduction_spec",
  "opt_key_word_r", "no_opt_key_word_r", "reduction_group",
  "reduction_list", "reduction", "reduction_op", "loc_op", "shadow_spec",
  "shadow_group_name", "shadow_list", "shadow", "opt_corner",
  "array_ident", "array_ident_list", "dvm_shadow_start", "dvm_shadow_wait",
  "dvm_shadow_group", "dvm_reduction_start", "dvm_reduction_wait",
  "dvm_consistent_start", "dvm_consistent_wait", "dvm_remote_access",
  "group_name", "remote_data_list", "remote_data", "remote_index_list",
  "remote_index", "dvm_task", "task_array", "dvm_task_region", "task_name",
  "dvm_end_task_region", "task", "dvm_on", "opt_new_spec", "dvm_end_on",
  "dvm_map", "dvm_prefetch", "dvm_reset", "dvm_indirect_access",
  "indirect_list", "indirect_reference", "hpf_independent",
  "hpf_reduction_spec", "dvm_asynchronous", "dvm_endasynchronous",
  "dvm_asyncwait", "async_ident", "async", "dvm_f90", "dvm_debug_dir",
  "debparamlist", "debparam", "fragment_number", "dvm_enddebug_dir",
  "dvm_interval_dir", "interval_number", "dvm_endinterval_dir",
  "dvm_traceon_dir", "dvm_traceoff_dir", "dvm_barrier_dir", "dvm_check",
  "dvm_io_mode_dir", "mode_list", "mode_spec", "dvm_shadow_add",
  "template_ref", "shadow_axis_list", "shadow_axis", "opt_include_to",
  "dvm_localize", "localize_target", "target_subscript_list",
  "target_subscript", "aster_expr", "dvm_cp_create", "opt_mode",
  "dvm_cp_load", "dvm_cp_save", "dvm_cp_wait",
  "omp_specification_directive", "omp_execution_directive",
  "ompdvm_onethread", "omp_parallel_end_directive",
  "omp_parallel_begin_directive", "parallel_clause_list",
  "parallel_clause", "omp_variable_list_in_par", "ompprivate_clause",
  "ompfirstprivate_clause", "omplastprivate_clause", "ompcopyin_clause",
  "ompshared_clause", "ompdefault_clause", "def_expr", "ompif_clause",
  "ompnumthreads_clause", "ompreduction_clause", "ompreduction",
  "ompreduction_vars", "ompreduction_op", "omp_sections_begin_directive",
  "sections_clause_list", "sections_clause", "omp_sections_end_directive",
  "omp_section_directive", "omp_do_begin_directive",
  "omp_do_end_directive", "do_clause_list", "do_clause",
  "ompordered_clause", "ompschedule_clause", "ompschedule_op",
  "omp_single_begin_directive", "single_clause_list", "single_clause",
  "omp_single_end_directive", "end_single_clause_list",
  "end_single_clause", "ompcopyprivate_clause", "ompnowait_clause",
  "omp_workshare_begin_directive", "omp_workshare_end_directive",
  "omp_parallel_do_begin_directive", "paralleldo_clause_list",
  "paralleldo_clause", "omp_parallel_do_end_directive",
  "omp_parallel_sections_begin_directive",
  "omp_parallel_sections_end_directive",
  "omp_parallel_workshare_begin_directive",
  "omp_parallel_workshare_end_directive", "omp_threadprivate_directive",
  "omp_master_begin_directive", "omp_master_end_directive",
  "omp_ordered_begin_directive", "omp_ordered_end_directive",
  "omp_barrier_directive", "omp_atomic_directive", "omp_flush_directive",
  "omp_critical_begin_directive", "omp_critical_end_directive",
  "omp_common_var", "omp_variable_list", "op_slash_1", "op_slash_0",
  "acc_directive", "acc_region", "acc_checksection", "acc_get_actual",
  "acc_actual", "opt_clause", "acc_clause_list", "acc_clause",
  "data_clause", "targets_clause", "async_clause", "acc_var_list",
  "computer_list", "computer", "acc_end_region", "acc_end_checksection",
  "spf_directive", "spf_analysis", "spf_parallel", "spf_transform",
  "spf_parallel_reg", "spf_end_parallel_reg", "analysis_spec_list",
  "analysis_spec", "analysis_reduction_spec", "analysis_private_spec",
  "parallel_spec_list", "parallel_spec", "parallel_shadow_spec",
  "parallel_across_spec", "parallel_remote_access_spec",
  "transform_spec_list", "transform_spec", "region_name", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   334,   335,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   336,   337
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   338,   339,   339,   340,   340,   340,   340,   340,   340,
     340,   341,   342,   342,   342,   342,   342,   342,   342,   342,
     343,   344,   344,   344,   345,   346,   347,   347,   347,   347,
     348,   348,   349,   350,   350,   351,   351,   352,   352,   352,
     353,   353,   354,   354,   355,   356,   357,   358,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   360,   360,   360,
     360,   360,   361,   362,   362,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   364,   364,   365,   365,   366,   366,   367,
     367,   367,   368,   368,   369,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   370,   370,   370,   371,
     371,   372,   372,   373,   373,   374,   374,   375,   375,   376,
     377,   378,   378,   379,   380,   380,   381,   382,   382,   383,
     383,   384,   385,   385,   385,   385,   385,   385,   385,   386,
     386,   387,   387,   387,   388,   388,   388,   388,   389,   389,
     389,   389,   390,   391,   391,   391,   392,   392,   393,   393,
     394,   394,   395,   395,   396,   396,   396,   396,   397,   397,
     397,   398,   399,   399,   400,   401,   401,   402,   402,   403,
     403,   404,   405,   405,   406,   406,   406,   407,   408,   408,
     409,   410,   411,   412,   412,   413,   413,   414,   414,   414,
     414,   414,   415,   416,   417,   418,   419,   420,   420,   421,
     421,   422,   423,   423,   424,   424,   424,   424,   425,   425,
     425,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   427,   428,   428,   428,   429,   429,   430,   430,
     430,   431,   431,   431,   431,   432,   433,   433,   434,   434,
     434,   434,   434,   435,   435,   435,   436,   436,   437,   437,
     437,   438,   438,   439,   439,   440,   440,   441,   442,   443,
     443,   443,   444,   444,   445,   446,   447,   447,   448,   448,
     448,   448,   449,   450,   450,   451,   451,   452,   452,   453,
     454,   454,   456,   455,   455,   457,   457,   457,   457,   458,
     458,   459,   459,   460,   461,   461,   462,   462,   463,   465,
     464,   466,   466,   467,   467,   468,   468,   469,   470,   471,
     472,   472,   473,   473,   474,   474,   474,   475,   475,   476,
     476,   477,   477,   477,   478,   478,   478,   478,   478,   478,
     478,   478,   478,   478,   478,   478,   478,   478,   478,   478,
     478,   478,   478,   478,   478,   478,   478,   478,   478,   479,
     479,   480,   481,   481,   481,   482,   482,   482,   482,   483,
     484,   484,   484,   484,   485,   486,   486,   487,   488,   488,
     489,   489,   489,   489,   489,   490,   490,   490,   490,   491,
     492,   492,   492,   493,   494,   494,   495,   495,   495,   495,
     495,   495,   495,   495,   497,   498,   496,   499,   499,   500,
     500,   500,   501,   501,   501,   502,   503,   503,   504,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   504,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   504,   504,
     504,   504,   505,   505,   506,   506,   506,   507,   507,   508,
     508,   508,   508,   508,   509,   510,   510,   510,   510,   511,
     511,   512,   512,   513,   513,   514,   515,   516,   517,   518,
     518,   519,   520,   520,   521,   522,   522,   523,   523,   524,
     524,   524,   524,   524,   525,   525,   525,   525,   525,   525,
     525,   525,   525,   525,   525,   525,   525,   525,   525,   525,
     525,   525,   526,   527,   527,   527,   527,   528,   528,   529,
     530,   530,   531,   531,   531,   532,   532,   533,   534,   535,
     536,   536,   536,   536,   536,   536,   536,   536,   536,   536,
     536,   536,   536,   537,   538,   538,   538,   539,   540,   540,
     540,   541,   541,   542,   542,   543,   543,   544,   544,   544,
     544,   544,   544,   545,   546,   547,   548,   548,   549,   549,
     550,   550,   551,   551,   551,   552,   552,   552,   552,   552,
     552,   553,   553,   553,   553,   553,   554,   555,   556,   556,
     557,   557,   557,   557,   557,   557,   557,   557,   557,   558,
     558,   559,   559,   559,   559,   559,   559,   559,   559,   559,
     559,   559,   559,   559,   559,   559,   559,   559,   559,   559,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   561,   561,   562,   563,   564,   564,   565,   566,   567,
     567,   568,   569,   570,   571,   571,   572,   572,   573,   574,
     574,   574,   575,   575,   576,   577,   577,   578,   579,   579,
     580,   581,   581,   582,   583,   583,   584,   585,   585,   586,
     586,   587,   587,   588,   589,   590,   591,   591,   592,   593,
     593,   594,   595,   595,   595,   595,   595,   595,   595,   595,
     596,   597,   598,   598,   599,   600,   600,   601,   602,   602,
     603,   603,   603,   604,   605,   605,   606,   606,   607,   608,
     608,   609,   610,   610,   611,   611,   612,   613,   614,   615,
     616,   616,   617,   617,   617,   618,   619,   619,   620,   620,
     620,   621,   621,   622,   622,   623,   623,   623,   623,   623,
     623,   623,   623,   623,   623,   623,   624,   626,   625,   625,
     627,   627,   628,   629,   630,   630,   631,   632,   633,   633,
     634,   635,   635,   636,   636,   637,   638,   639,   640,   640,
     641,   642,   642,   643,   644,   644,   645,   645,   646,   646,
     647,   647,   648,   648,   648,   648,   648,   648,   648,   648,
     648,   648,   649,   649,   650,   650,   651,   652,   652,   653,
     654,   655,   655,   655,   656,   656,   657,   657,   658,   659,
     659,   660,   661,   661,   661,   662,   662,   663,   663,   663,
     664,   664,   665,   666,   666,   667,   667,   667,   667,   667,
     667,   667,   668,   669,   670,   671,   672,   672,   672,   673,
     674,   675,   676,   676,   677,   677,   678,   678,   678,   678,
     678,   678,   678,   678,   678,   679,   679,   680,   680,   680,
     680,   680,   681,   682,   682,   683,   683,   683,   683,   684,
     685,   686,   686,   687,   687,   688,   688,   689,   690,   691,
     692,   693,   694,   694,   695,   696,   696,   697,   697,   698,
     698,   699,   699,   700,   700,   701,   702,   702,   702,   702,
     702,   703,   704,   705,   705,   706,   707,   707,   708,   709,
     709,   710,   711,   712,   712,   713,   713,   714,   714,   715,
     715,   715,   715,   716,   717,   718,   719,   720,   721,   721,
     722,   723,   723,   724,   724,   725,   726,   727,   728,   729,
     729,   730,   731,   732,   733,   734,   735,   736,   736,   737,
     737,   737,   738,   739,   740,   740,   741,   741,   742,   742,
     743,   744,   744,   745,   745,   746,   746,   747,   748,   749,
     749,   749,   750,   751,   751,   752,   753,   754,   754,   754,
     754,   754,   754,   754,   754,   754,   754,   754,   754,   754,
     754,   754,   754,   754,   754,   754,   754,   754,   754,   754,
     754,   754,   754,   755,   756,   757,   757,   758,   758,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   760,   761,
     762,   763,   764,   765,   766,   767,   767,   767,   768,   769,
     770,   771,   772,   773,   773,   773,   773,   773,   773,   773,
     773,   773,   773,   773,   773,   773,   773,   774,   774,   775,
     775,   776,   776,   776,   776,   777,   777,   778,   779,   779,
     780,   780,   781,   781,   782,   782,   782,   782,   782,   782,
     783,   784,   784,   785,   785,   785,   785,   786,   786,   787,
     787,   788,   788,   789,   789,   790,   790,   791,   791,   792,
     793,   794,   795,   795,   796,   796,   797,   797,   798,   798,
     798,   798,   798,   798,   798,   798,   798,   798,   798,   799,
     800,   800,   801,   802,   802,   803,   804,   805,   806,   807,
     808,   809,   810,   811,   811,   812,   812,   813,   813,   814,
     815,   815,   815,   815,   816,   817,   818,   818,   818,   818,
     818,   818,   819,   820,   821,   821,   821,   822,   822,   822,
     823,   823,   824,   824,   825,   825,   825,   826,   826,   826,
     826,   826,   827,   828,   829,   830,   830,   831,   831,   832,
     833,   834,   834,   834,   834,   834,   835,   836,   837,   838,
     839,   840,   840,   841,   841,   842,   843,   844,   844,   845,
     845,   845,   846,   847,   848,   849,   849,   850,   851
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     3,     3,     4,     5,     5,     3,     4,     3,
       0,     2,     2,     2,     1,     1,     4,     5,     4,     5,
       2,     5,     1,     0,     1,     0,     1,     0,     2,     3,
       1,     3,     1,     1,     1,     0,     0,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     2,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     5,
       5,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     7,     2,     3,     7,     6,     0,
       2,     5,     1,     4,     1,     1,     1,     2,     1,     4,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     1,
       1,     7,     3,     4,     3,     4,     3,     2,     5,     0,
       2,     2,     5,     0,     4,     5,     0,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     5,     6,     6,     0,     1,     5,     9,     1,     1,
       2,     2,     0,     0,     2,     2,     5,     4,     4,     3,
       4,     3,     4,     3,     3,     4,     5,     3,     4,     5,
       3,     3,     1,     3,     2,     4,     3,     4,     3,     3,
       3,     3,     3,     3,     1,     4,     1,     1,     4,     3,
       0,     0,     4,     1,     3,     1,     3,     2,     3,     3,
       4,     2,     0,     1,     1,     3,     5,     1,     3,     0,
       1,     7,     1,     3,     2,     2,     3,     1,     1,     4,
       3,     2,     1,     1,     1,     1,     3,     1,     3,     1,
       1,     6,     1,     1,     2,     2,     1,     3,     1,     2,
       2,     1,     3,     1,     3,     5,     1,     1,     1,     2,
       2,     3,     3,     1,     3,     3,     1,     3,     1,     1,
       3,     1,     3,     1,     1,     3,     5,     0,     0,     1,
       4,     4,     1,     3,     3,     2,     1,     3,     3,     6,
       6,     7,     1,     1,     3,     3,     1,     1,     3,     3,
       0,     3,     0,     2,     3,     1,     1,     2,     3,     1,
       1,     1,     3,     1,     3,     1,     1,     3,     4,     0,
       2,     2,     1,     1,     3,     1,     3,     1,     0,     0,
       0,     2,     0,     1,     1,     1,     2,     2,     4,     1,
       3,     1,     3,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     5,     6,     4,     5,     3,
       1,     1,     5,     4,     2,     0,     1,     5,     0,     1,
       1,     3,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     5,     1,     1,     3,     2,     5,     4,
       4,     3,     2,     1,     0,     0,     6,     1,     1,     1,
       4,     5,     1,     4,     5,     0,     1,     3,     1,     1,
       1,     2,     3,     3,     2,     1,     2,     2,     2,     3,
       7,     3,     3,     1,     2,     2,     1,     2,     3,     1,
       1,     1,     5,     7,     0,     6,     4,    11,    13,     4,
       3,     3,     7,     8,     3,     1,     2,     2,     3,     1,
       3,     0,     1,     0,     1,     1,     2,     5,     6,     1,
       3,     3,     0,     2,     1,     5,     7,     0,     1,     3,
       3,     6,     5,     6,     4,     5,     5,     2,     1,     1,
      10,     1,     3,     4,     3,     3,     3,     3,     6,     6,
       5,     8,     2,     3,     3,     7,     7,     0,     1,     4,
       2,     4,     1,     2,     2,     1,     1,     0,     0,     0,
       2,     2,     2,     2,     2,     2,     2,     3,     4,     2,
       3,     1,     3,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     3,     3,     1,     4,     1,     1,     1,
       2,     2,     2,     1,     3,     3,     4,     4,     1,     3,
       1,     5,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     5,     5,     5,     0,     0,     1,     3,
       1,     1,     3,     3,     3,     3,     2,     3,     3,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     3,     1,     3,     1,     3,     1,
       3,     1,     4,     3,     1,     3,     1,     3,     1,     4,
       4,     4,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     0,     5,     6,     8,     1,
       3,     1,     1,     1,     4,     1,     0,     2,     3,     2,
       4,     0,     1,     5,     4,     6,     4,     1,     4,     4,
       1,     6,     1,     3,     1,     1,     4,     1,     1,     3,
       1,     1,     3,     1,     0,     1,     2,     3,     1,     2,
       5,     4,     4,     6,     1,     3,     1,     1,     6,     4,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     6,     4,     1,     4,     1,     1,     1,     1,     4,
       2,     7,     1,     4,     1,     1,    11,     0,     2,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     8,     1,     3,     2,     2,     7,     1,     3,
       1,     3,     1,     4,     1,     3,     1,     1,     0,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     8,     6,     8,     6,     1,     6,     6,     6,
       6,     1,     3,     5,     1,     3,     8,     6,     6,     4,
       5,     5,     2,     2,     0,     1,     3,     1,     4,     7,
       1,     3,     3,     1,     3,     5,     3,     3,     1,     3,
       1,     1,     3,     3,     3,     3,    10,     8,    10,     0,
       0,     1,     2,     4,     4,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     4,     4,
       3,     9,     1,     1,     3,     1,     5,     5,     9,     0,
       1,     1,     3,     3,     3,     3,     3,     6,     3,     3,
       3,     3,     7,     5,     1,     1,     3,     4,     1,     1,
       3,     1,     1,     3,     3,     2,     3,     4,     4,     5,
       5,     1,     2,     4,     4,     4,     0,     1,     2,     7,
       6,     3,     3,     7,     5,     1,     3,     1,     4,     2,
       3,     3,     4,     6,     3,     2,     3,     1,     1,     4,
       5,     3,     6,     2,     4,     2,     1,     3,     3,     0,
       1,     2,     2,     2,     2,     9,     5,     1,     3,     2,
       2,     2,     9,     4,     1,     3,     1,     1,     2,     0,
       7,     1,     4,     1,     3,     1,     1,     1,    16,     0,
       3,     3,     3,     3,     6,     9,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     4,     3,     4,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     2,
       2,     2,     2,     2,     5,     1,     1,     1,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     4,
       5,     1,     1,     1,     1,     4,     3,     2,     4,     3,
       4,     3,     4,     5,     1,     1,     1,     1,     1,     1,
       1,     7,     5,     1,     1,     1,     1,     4,     3,     4,
       5,     1,     1,     4,     3,     4,     5,     1,     1,     2,
       1,     2,     4,     3,     4,     3,     4,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       4,     3,     2,     4,     3,     2,     3,     2,     2,     2,
       2,     2,     2,     3,     2,     5,     2,     5,     2,     5,
       1,     1,     3,     3,     0,     0,     1,     1,     1,     1,
       1,     1,     3,     2,     5,     4,     2,     5,     4,     2,
       2,     1,     1,     3,     2,     2,     2,     4,     4,     4,
       4,     4,     4,     1,     1,     1,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     2,
       1,     1,     3,     1,     1,     5,     5,     1,     3,     1,
       1,     1,     5,     5,     5,     1,     3,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,    10,    11,     9,     0,     0,     3,   150,
     149,   782,   339,   537,   537,   537,   537,   537,   339,   537,
     554,   537,    20,   537,   537,   158,   537,   560,   339,   154,
     537,   339,   537,   537,   339,   485,   537,   537,   537,   338,
     537,   775,   537,   537,   340,   784,   537,   155,   156,   778,
      45,   537,   537,   537,   537,   537,   537,   537,   537,   556,
     537,   537,   483,   483,   537,   537,   537,   339,   537,     0,
     537,   339,   339,   537,   537,   338,    20,   339,   339,   325,
       0,   537,   537,   339,   339,   558,   339,   339,   339,   339,
     152,   339,   537,   211,   537,   157,   537,   537,     0,    20,
     339,   537,   537,   537,   559,   339,   537,   339,   535,   537,
     537,   339,   537,   537,   537,   339,    20,   339,    45,   537,
     537,   153,    45,   537,   339,   537,   537,   537,   339,   537,
     537,   555,   339,   537,   339,   537,   537,   537,   537,   537,
     537,   339,   339,   536,    20,   339,   339,   537,   537,   537,
       0,   339,     8,   339,   537,   537,   537,   776,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   339,   537,   777,   537,  1209,   537,
    1210,   537,   537,   537,     0,     0,     0,     0,  1220,   537,
     537,   537,   537,   609,     0,    37,   609,    73,    48,    49,
      50,    65,    66,    76,    68,    69,    67,   109,    58,     0,
     146,   151,    52,    70,    71,    72,    51,    59,    54,    55,
      56,    60,   207,    75,    74,    57,   609,   445,   440,   453,
       0,     0,     0,   456,   439,   438,     0,   508,   511,   537,
     509,     0,   537,     0,   537,     0,     0,   551,    53,   459,
     611,   614,   620,   616,   615,   621,   622,   623,   624,   613,
     630,   612,   631,   617,     0,   773,   618,   625,   627,   626,
     657,   632,   634,   635,   633,   636,   637,   638,   639,   640,
     619,   641,   642,   644,   645,   643,   647,   648,   646,   669,
     658,   659,   660,   661,   649,   650,   651,   652,   653,   654,
     655,   656,   662,   663,   664,   665,   666,   667,   668,   629,
     670,   628,  1018,  1017,  1019,  1020,  1021,  1022,  1023,  1024,
    1025,  1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1016,
    1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,   460,
    1176,  1178,  1180,  1181,  1177,  1179,   461,  1211,  1212,  1213,
    1214,  1215,     0,     0,   340,     0,     0,     0,     0,     0,
       0,     0,   984,    35,     0,     0,   596,     0,     0,     0,
       0,     0,     0,   454,   507,   481,   210,     0,     0,     0,
     481,     0,   312,   339,   721,     0,   721,   538,     0,    23,
     481,     0,   481,   965,     0,   981,   483,   481,   481,   481,
      32,   484,    81,   444,   948,   481,   942,   105,   481,    37,
     481,     0,   340,     0,     0,    63,     0,     0,   329,    44,
       7,   959,     0,     0,     0,     0,     0,    77,   340,     0,
     979,   522,     0,     0,     0,   296,   295,     0,     0,   806,
       0,     0,   340,     0,     0,   538,     0,   340,     0,     0,
       0,   340,    33,   340,    22,   597,     0,    21,     0,     0,
       0,     0,     0,     0,     0,   398,   340,    45,   140,     0,
       0,     0,     0,     0,     0,     0,     0,   780,   340,     0,
     340,     0,     0,   982,   983,     0,   339,   340,     0,     0,
       0,   597,     0,  1162,  1161,  1166,  1043,   721,  1168,   721,
    1158,  1160,  1044,  1149,  1152,  1155,   721,   721,   721,  1164,
    1157,  1159,   721,   721,   721,   721,  1097,   721,   721,  1174,
    1131,     0,    45,  1183,  1186,  1189,     0,    45,    45,    45,
    1238,  1219,     0,     0,     0,     0,   610,     4,    20,    20,
       0,     0,    45,     5,     0,     0,     0,     0,     0,    45,
      20,     0,     0,     0,   147,   164,     0,     0,     0,     0,
     528,     0,   528,     0,     0,     0,     0,   528,   222,     6,
     486,   537,   537,   446,   441,     0,   457,   448,   447,   455,
      82,   172,     0,     0,     0,   406,     0,   405,   410,   408,
     409,   407,   381,     0,     0,   351,   382,   354,   384,   383,
     355,   400,   402,   395,   353,   356,   596,   398,   542,   543,
       0,   380,   379,    32,     0,   600,   601,   540,     0,   598,
     597,     0,   544,   597,   562,   546,   545,   598,   549,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
     769,   770,   768,     0,   766,   756,     0,     0,   435,     0,
     323,     0,   524,   967,   968,   964,    45,   310,   801,   803,
     966,    36,    13,   596,     0,   481,     0,   192,     0,   310,
       0,   184,     0,   703,   701,   836,   920,   921,   800,   797,
     798,   482,   516,   222,   435,   310,   671,   976,   971,   470,
     341,     0,     0,     0,     0,     0,   713,   716,   705,     0,
     497,   677,   674,   675,   451,     0,     0,   500,   977,   442,
     443,   458,   452,   471,   106,   499,    45,   517,     0,   199,
       0,   382,     0,     0,    37,    25,   796,   793,   794,   324,
     326,     0,     0,    45,   960,   961,     0,   694,   692,   681,
     678,   679,     0,     0,    78,     0,    45,   980,   978,     0,
       0,   941,     0,    45,     0,    19,     0,     0,     0,     0,
     946,     0,     0,     0,   497,   523,     0,     0,   924,   951,
     597,     0,   597,   598,   139,    34,    12,   143,   574,     0,
     757,     0,     0,     0,   721,   700,   698,   881,   918,   919,
       0,   697,   695,   952,   399,   514,     0,     0,     0,   902,
       0,   914,   913,   916,   915,   686,     0,   684,   688,     0,
       0,    37,    24,     0,   310,   933,   936,     0,    45,     0,
     302,   298,     0,     0,   575,   310,     0,   527,     0,  1101,
    1096,   527,  1133,  1163,     0,   527,   527,   527,   527,   527,
     527,  1156,   310,    46,  1182,  1191,  1192,     0,     0,    45,
       0,     0,  1221,  1223,  1224,     0,     0,  1227,  1229,  1230,
    1231,     0,     0,  1235,     0,  1012,  1013,     0,     0,     0,
      20,    43,    38,    42,     0,    40,    17,    46,   310,   132,
     134,   136,   110,     0,     0,    20,   339,   148,   538,   596,
     165,   146,   310,   179,   181,   183,   187,   527,   190,   527,
     196,   198,   200,   209,     0,   213,     0,    45,     0,   449,
     424,     0,   351,   364,   363,   376,   362,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   596,     0,     0,   596,
       0,     0,   398,   404,   396,   512,     0,     0,   515,   568,
     569,   573,     0,   565,     0,   567,     0,   606,     0,     0,
       0,     0,     0,   553,   567,   557,     0,     0,   580,   547,
     578,     0,     0,   351,   353,   550,   584,   583,   552,   672,
     310,   693,   696,   699,   702,   310,   339,     0,   934,     0,
      45,   751,   178,     0,     0,     0,     0,     0,     0,   312,
     805,     0,   529,     0,   475,   479,     0,   469,   596,     0,
     194,   185,     0,   321,     0,   208,     0,   673,   596,     0,
     779,   319,   316,   313,   315,   320,   310,   721,   718,   727,
     722,     0,     0,     0,     0,     0,   719,   705,   721,     0,
     783,     0,   498,   539,     0,     0,     0,    18,   204,     0,
       0,     0,   206,   195,     0,   494,   492,   489,     0,    45,
       0,   329,     0,     0,   332,   330,     0,    45,   962,   381,
     910,   957,     0,     0,   955,     0,     0,    87,    88,    86,
      85,    91,    90,   102,    95,    98,    97,   100,    99,    96,
     101,    94,    92,    89,    93,    83,     0,    84,   197,     0,
       0,     0,     0,     0,     0,   297,     0,   188,   436,     0,
      45,   947,   945,   133,   810,     0,   808,     0,     0,   292,
     539,   180,     0,   577,     0,   576,   287,   287,     0,   752,
       0,   721,   705,   928,     0,     0,   925,   284,   283,    62,
     281,     0,     0,     0,     0,     0,     0,   683,   682,   135,
      14,   182,   935,    45,   938,   937,   146,     0,   103,    47,
       0,     0,   689,     0,   721,   527,     0,  1130,  1100,  1095,
     721,   527,  1132,  1175,   721,   527,   721,   527,   527,   527,
     721,   527,   721,   527,   690,     0,     0,     0,     0,  1203,
       0,     0,  1190,  1194,  1196,  1195,    45,  1185,   844,  1204,
       0,  1188,     0,     0,     0,   987,     0,     0,    45,  1216,
       0,     0,     0,    45,  1217,  1237,    45,  1218,    45,    45,
      45,    28,    37,     0,     0,    39,     0,    30,   159,   116,
     310,   339,   118,   120,     0,   121,   114,   122,   130,   129,
     123,   124,   125,     0,   112,   115,    26,     0,   310,     0,
       0,   144,   177,     0,     0,   222,   222,     0,   224,   217,
     221,     0,     0,     0,   352,     0,   359,   361,   358,   357,
     375,   377,   371,   365,   504,   368,   366,   369,   367,   370,
     372,   374,   360,   373,   378,   596,   411,   389,     0,   343,
       0,   414,   415,   401,   412,   403,     0,   596,   513,     0,
     532,   530,     0,   596,   564,   571,   572,   570,   599,   608,
     603,   605,   607,   604,   602,   563,   548,     0,     0,     0,
     351,     0,     0,     0,     0,     0,   691,   772,     0,   782,
     785,   775,     0,   784,   778,     0,   776,   777,   774,   767,
       0,   390,   391,   429,     0,     0,   506,     0,     0,   349,
       0,     0,   804,   477,   476,     0,   474,     0,   193,     0,
     527,   799,   427,   428,   432,     0,     0,     0,   314,   317,
     176,     0,   596,     0,     0,     0,     0,     0,   706,   717,
     310,   462,   721,   676,     0,   481,     0,     0,   201,     0,
     394,   970,     0,     0,     0,    16,   795,   327,   337,     0,
     333,   335,   331,     0,     0,     0,     0,     0,     0,     0,
     954,   680,    80,    79,   128,   126,   127,   340,     0,   487,
     423,     0,     0,     0,     0,   191,     0,   520,     0,     0,
     721,     0,     0,    64,   527,   505,   599,   138,     0,   142,
      45,     0,   705,     0,     0,     0,     0,   923,     0,     0,
       0,     0,     0,   903,   905,   687,   685,     0,    45,   940,
      45,   939,   145,   340,     0,   502,     0,  1165,     0,   721,
    1167,     0,   721,     0,     0,   721,     0,   721,     0,   721,
       0,   721,     0,     0,     0,    45,     0,     0,     0,  1193,
       0,  1184,  1187,   991,   989,   990,    45,   986,     0,    45,
    1222,     0,     0,     0,  1228,  1236,     0,     0,     0,    15,
      29,    41,     0,   173,   160,   117,     0,    45,     0,    45,
      27,   159,   539,   539,   169,   172,   168,     0,   186,   189,
     214,     0,     0,     0,   247,   245,   252,   249,   263,   256,
     261,     0,     0,   215,   238,   250,   242,   253,   243,   258,
     244,     0,   237,     0,   232,   229,   218,   219,     0,     0,
     425,   351,     0,   387,   596,   347,   344,   345,     0,   398,
       0,   534,   533,     0,     0,   579,   352,     0,     0,     0,
     351,   586,   351,   590,   351,   588,   310,     0,   596,   596,
     596,   518,     0,     0,     0,   969,     0,   311,   478,   480,
     172,   322,     0,   596,   519,     0,   973,   596,   972,   318,
     320,   720,     0,     0,     0,   730,     0,     0,     0,     0,
     704,   464,   481,   501,     0,   203,   202,   381,   493,   490,
     488,     0,   491,     0,   328,     0,     0,     0,     0,     0,
       0,   956,     0,  1001,     0,     0,   422,   417,   943,   944,
     715,   310,   950,   437,   809,   812,   818,   294,   293,     0,
     287,     0,     0,   289,   288,     0,   753,   754,   707,     0,
     932,   931,     0,   929,     0,   926,   282,     0,  1007,   996,
       0,   994,   997,   748,     0,     0,   917,   909,     0,     0,
       0,     0,     0,   300,     0,   299,   307,     0,  1174,     0,
    1174,  1174,  1110,     0,  1104,  1106,  1107,  1105,   721,  1109,
    1108,     0,  1174,   721,  1128,  1127,     0,     0,  1171,  1170,
       0,     0,  1174,     0,  1174,     0,   721,  1049,  1053,  1054,
    1055,  1051,  1052,  1056,  1057,  1050,     0,  1138,  1142,  1143,
    1144,  1140,  1141,  1145,  1146,  1139,  1148,  1147,   721,     0,
    1091,  1093,  1094,  1092,   721,     0,  1121,  1122,   721,     0,
       0,     0,     0,     0,     0,  1205,     0,     0,   845,   988,
       0,     0,     0,     0,     0,     0,     0,  1014,     0,     0,
       0,     0,   108,   787,     0,   111,     0,   173,     0,   146,
       0,   171,   170,   267,   253,   266,     0,   255,   260,   254,
     259,     0,     0,     0,     0,     0,   222,   212,   223,   241,
       0,   222,   234,   235,     0,     0,     0,     0,   278,   223,
     279,     0,     0,   227,   268,   273,   276,   229,   220,     0,
     503,     0,   413,   385,   388,     0,   346,     0,   531,   566,
     567,     0,     0,   351,     0,     0,     0,   771,   765,   781,
       0,   596,     0,     0,     0,   525,   350,     0,   340,   526,
       0,   975,     0,     0,     0,   734,     0,   732,   729,   724,
     728,   726,     0,    45,     0,   463,   450,   205,   334,   336,
       0,     0,     0,   958,   953,   131,     0,  1000,   421,     0,
       0,   416,   949,     0,    45,   807,   819,   820,   825,   829,
     822,   830,   831,   826,   828,   827,   823,   824,     0,     0,
       0,     0,   285,     0,     0,     0,     0,   927,   922,   472,
       0,   993,   721,   904,     0,     0,   879,   104,   306,   301,
     303,     0,     0,     0,  1059,   721,  1060,  1061,    45,  1102,
     721,  1129,  1125,   721,  1174,     0,  1058,    45,  1062,     0,
    1063,     0,  1047,   721,  1136,   721,  1089,   721,  1119,   721,
    1197,  1198,  1199,  1207,  1208,    45,  1202,  1200,  1201,  1226,
     891,   892,   893,   890,   895,   889,   896,   888,   887,   886,
     894,   882,     0,     0,    45,  1225,  1233,  1234,  1232,     0,
       0,    31,   175,   174,     0,     0,   119,   113,   107,     0,
       0,   161,   596,   166,     0,   248,   246,   264,   257,   262,
     216,   222,   596,     0,   240,   236,   223,     0,   233,     0,
     270,   269,     0,   225,   229,     0,     0,     0,     0,     0,
     230,     0,   426,   386,   348,   397,     0,   581,   593,   595,
     594,     0,     0,   393,   430,     0,     0,   802,     0,   433,
       0,   974,   749,   723,     0,    45,     0,     0,     0,   837,
     963,   838,  1006,     0,  1003,  1005,   420,   419,     0,     0,
     811,     0,   821,     0,   288,     0,     0,   758,   755,   713,
     708,   709,   711,   712,   930,   995,   999,     0,     0,   381,
       0,     0,     0,     0,     0,   309,   308,   521,     0,     0,
       0,  1103,  1126,     0,  1173,  1172,     0,     0,     0,  1048,
    1137,  1090,  1120,  1206,     0,     0,     0,     0,     0,     0,
       0,   788,   162,   163,     0,     0,   239,   596,   241,     0,
     280,   228,     0,   272,   271,   274,   275,   277,   473,     0,
     763,   762,   764,     0,   760,   392,   431,     0,   985,   434,
       0,   733,     0,   725,     0,     0,     0,  1002,   418,     0,
       0,     0,     0,     0,   900,     0,     0,     0,     0,     0,
       0,   286,   291,   290,     0,     0,     0,   992,   906,   907,
       0,   835,   880,   880,   305,   304,  1075,  1074,  1073,  1080,
    1081,  1082,  1079,  1076,  1078,  1077,  1086,  1083,  1084,  1085,
       0,  1070,  1114,  1113,  1115,  1116,     0,  1175,  1065,  1067,
    1066,     0,  1069,  1068,     0,     0,   883,     0,  1015,   789,
       0,   172,   265,     0,     0,   227,   226,     0,     0,   759,
     510,     0,     0,     0,   466,  1004,   817,   816,     0,   814,
     721,   849,     0,     0,     0,     0,     0,   898,   899,     0,
       0,     0,     0,   710,   911,   998,    45,     0,     0,     0,
       0,     0,  1112,  1169,  1064,   884,     0,    45,     0,     0,
     251,   231,   495,   761,   750,   737,   731,   735,     0,     0,
     813,   854,   850,     0,     0,     0,     0,     0,     0,     0,
       0,   841,     0,   467,   714,     0,     0,   834,    45,    45,
     877,  1072,  1071,     0,     0,   354,     0,   792,   786,   790,
     167,     0,     0,   465,   815,     0,     0,     0,     0,   847,
     839,     0,   833,     0,   897,   848,     0,   840,     0,   912,
       0,     0,     0,  1111,   885,     0,     0,   496,     0,   740,
       0,   738,   741,   852,   853,     0,   855,   857,     0,     0,
       0,   842,   468,   908,   878,   876,     0,   791,   743,   744,
       0,   736,     0,   851,     0,   846,   832,     0,     0,     0,
       0,   742,   745,   739,   856,     0,     0,   860,   901,   843,
    1009,   746,     0,     0,     0,   858,    45,  1008,   747,   862,
     861,    45,     0,     0,     0,   863,   868,   870,   871,  1010,
    1011,     0,     0,     0,    45,   859,    45,    45,   596,   874,
     873,   872,   864,     0,   866,   867,     0,   869,     0,    45,
     875,   865
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   203,   373,   204,   821,   734,   205,
     886,   602,   786,   672,   552,   884,   885,   430,   887,  1202,
    1474,   206,   207,   603,  1106,  1107,   208,   209,   210,   562,
    1253,  1254,  1110,  1255,   211,   212,   213,   214,  1136,   215,
     216,  1137,   217,   565,   218,   219,   220,   221,  1523,  1524,
     901,  1535,   920,  1792,   222,   223,   224,   225,   226,   227,
     767,  1147,  1148,   228,   229,   230,   729,  1059,  1060,   231,
     232,   693,   441,   913,   914,  1551,   915,   916,  1830,  1561,
    1566,  1567,  1831,  1832,  1562,  1563,  1564,  1553,  1554,  1555,
    1556,  1804,  1558,  1559,  1560,  1806,  2040,  1834,  1835,  1836,
    1149,  1150,  1447,  1448,  1922,  1674,  1128,  1129,   233,   446,
     234,   831,  1939,  1940,  1705,  1706,  1010,   701,   702,  1033,
    1034,  1022,  1023,   235,   739,   740,   741,   742,  1075,  1409,
    1410,  1411,   386,   363,   393,  1298,  1575,  1299,  1358,   982,
     605,   624,   606,   607,   608,   609,  1353,  1062,   953,  1844,
     805,   610,   611,   612,   613,   614,  1303,  1577,   615,  1273,
    1841,  1374,  1354,  1375,  1003,  1119,   236,   237,  1885,   238,
     239,   675,  1015,  1016,   692,   412,   240,   241,   242,   243,
    1066,  1067,  1403,  1851,  1852,  1053,   244,   245,   246,   247,
    1184,   248,   956,  1311,   249,   365,   710,  1392,   250,   251,
     252,   253,   254,   635,   627,   962,   963,   964,   255,   256,
     257,   979,   980,   985,   986,   987,  1300,   788,   628,   783,
     547,   258,   259,   260,   696,   261,   712,   713,   262,   750,
     751,   263,   487,   816,   817,   819,   264,   265,   748,   266,
     802,   267,   796,   268,   684,  1050,   269,   270,  2090,  2091,
    2092,  2093,  1661,  1047,   396,   704,   705,  1046,  1626,  1689,
    1876,  1877,  2286,  2287,  2350,  2351,  2369,  2381,  2382,  1694,
    1874,   271,   272,  1676,   656,   791,   792,  1859,  2153,  2154,
    1860,   653,   654,   273,   274,   275,   276,  2004,  2005,  2318,
    2319,   277,   737,   738,   278,   689,   690,   279,   668,   669,
     280,   281,  1125,  1126,  1666,  2080,  2248,  2249,  1905,  1906,
    1907,  1908,  1909,   686,  1910,  1911,  1912,  2302,  1209,  1913,
    1914,  1915,  2251,  2327,  2355,  2356,  2386,  2387,  2404,  2405,
    2406,  2407,  2408,  2419,  1916,  2102,  2268,   798,  1782,  1991,
    1992,  1993,  1917,   810,  1462,  1463,  1934,  1143,  2265,   282,
     283,   284,   285,   286,   287,   288,   289,   779,  1145,  1146,
    1682,  1683,   290,   825,   291,   762,   292,   763,   293,  1122,
     294,   295,   296,   297,   298,  1083,  1084,   299,   745,   300,
     301,   302,   664,   665,   303,   304,  1377,  1616,   698,   305,
     306,   758,   307,   308,   309,   310,   311,   312,  1214,  1215,
     313,  1153,  1690,  1691,  2187,   314,  1654,  2073,  2074,  1692,
     315,  2397,   316,   317,   318,   319,   320,   321,   322,   323,
    1185,  1736,   843,  1714,  1715,  1716,  1740,  1741,  1742,  2221,
    1743,  1744,  1717,  2109,  2312,  2210,   324,  1191,  1764,   325,
     326,   327,   328,  1175,  1718,  1719,  1720,  2216,   329,  1193,
    1768,   330,  1181,  1723,  1724,  1725,   331,   332,   333,  1187,
    1758,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,  1729,  1730,   844,  1483,
     349,   350,   351,   352,   353,   854,   855,   856,  1203,  1204,
    1205,  1210,  1774,  1775,   354,   355,   356,   357,   358,   359,
     360,   361,   861,   862,   863,   864,   866,   867,   868,   869,
     870,   872,   873,   541
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -2208
static const yytype_int16 yypact[] =
{
   -2208,   129, -2208, -2208, -2208, -2208,    19,  4739, -2208, -2208,
   -2208,   144, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,  1163, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208,    31, -2208, -2208,   198,   147, -2208, -2208, -2208,    31,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208,   161,   161, -2208, -2208, -2208, -2208, -2208,   161,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
     248, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,   161, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208,   347, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
     383,   450, -2208, -2208, -2208, -2208, -2208,    31, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208,    31, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208,   454,   533,   547,   161, -2208, -2208,
   -2208, -2208, -2208,   244,  1295,   572,   244, -2208, -2208, -2208,
     499,   563,   646,   693, -2208, -2208, -2208,   477,   742,   161,
   -2208, -2208,   761,   817,   833,   868,   546,   559,   874,   877,
     882, -2208,   132, -2208, -2208, -2208,   244, -2208, -2208, -2208,
     574,   456,  2103,  2324, -2208, -2208,  2873, -2208,   878, -2208,
   -2208,  2304, -2208,   886, -2208,  1337,   886,   908, -2208, -2208,
     913, -2208, -2208, -2208,   918,   923,   935,   940,   949, -2208,
   -2208, -2208, -2208,   959,  1188, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
     968, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208,   146,   161,   945,   964,   970,   842,   161,   161,
     105,   161, -2208,   161,   161,   981, -2208,   453,   984,   161,
     161,   161,   161, -2208, -2208,   161, -2208,  1004,   161,   859,
     161,  1015, -2208, -2208, -2208,   161, -2208,  1021,   161, -2208,
     161,  1029,   170, -2208,   859, -2208,   161,   161,   161,   161,
   -2208, -2208, -2208, -2208, -2208,   161, -2208,   161,   161,   572,
     161,  1041,   945,   161,  1046, -2208,   161,   161, -2208, -2208,
   -2208,  1073,  1082,   161,   161,  1092,  1097,   161,   945,  1103,
    2873, -2208,  1106,  1108,   161, -2208,  1119,   161,  1110, -2208,
    1128,   161,   945,  1130,  1134, -2208,   842,   945,   161,   161,
    1731,    90,   161,   112, -2208, -2208,   173, -2208,   177,   161,
     161,   161,  1137,   161,   161,  2873,   116, -2208, -2208,  1151,
     161,   161,   161,   161,   161,  2873,   161, -2208,   945,   161,
     945,   161,   161, -2208, -2208,   161, -2208,   945,   161,  1159,
    1191, -2208,   161, -2208, -2208,  1205, -2208, -2208,  1232, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,  1235,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208,   161, -2208, -2208,  1243,  1252,  1260, -2208, -2208, -2208,
   -2208, -2208,  2873,  2873,  2873,  2873, -2208, -2208, -2208, -2208,
    1104,   145, -2208, -2208,   161,   161,   161,   161,  1274, -2208,
   -2208,  1107,   161,   161, -2208,   692,   161,   161,   161,   161,
     161,   179,   161,  1110,   161,   161,  1041, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208,  1056, -2208, -2208, -2208, -2208,
   -2208, -2208,  2873,  2873,  2873, -2208,  2873, -2208, -2208, -2208,
   -2208, -2208, -2208,  2873,  1660, -2208,   142,  1239, -2208,  1278,
   -2208,  1055,  1057,  1290, -2208, -2208,  1299,  2873, -2208, -2208,
    2005, -2208, -2208,  1308,  1177,  1239, -2208, -2208,  1291,    -7,
   -2208,  2005, -2208, -2208, -2208,  1319,   180,   167,  2932,  2932,
     161,   161,   161,   161,   161,   161,   161,  1330, -2208,   161,
   -2208, -2208, -2208,   645, -2208, -2208,  1324,   161, -2208,  2873,
   -2208,  1101,   250, -2208,  1333, -2208, -2208,  1340,  1368, -2208,
   -2208, -2208, -2208, -2208,  2468,   161,  1387, -2208,   161,  1340,
     161, -2208,   842, -2208, -2208, -2208, -2208, -2208, -2208,  1380,
   -2208, -2208, -2208, -2208, -2208,  1340, -2208, -2208,  1392, -2208,
   -2208,   690,  1202,   161,   734,   133, -2208,  1398,  1240,  2873,
    1268, -2208,  1422, -2208, -2208,  2873,  2873, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,   161, -2208,
     161,  1416,   449,   161,   572, -2208, -2208,  1424, -2208,  1426,
   -2208,  1420,  1353, -2208,  1428, -2208,   161, -2208, -2208, -2208,
    1429, -2208,  1412,  3192, -2208,   161, -2208,  5321, -2208,   161,
    2873, -2208,  1425, -2208,   161, -2208,   161,   161,   161,  1239,
     617,   161,   161,   161,  1268, -2208,   161,   626, -2208, -2208,
   -2208,  1177,  1291, -2208, -2208, -2208, -2208, -2208, -2208,   146,
   -2208,  1324,  1434,  1398, -2208, -2208, -2208, -2208, -2208, -2208,
     161, -2208, -2208, -2208,  5321, -2208,   453,  1388,   161, -2208,
    1427, -2208, -2208, -2208, -2208,  3099,   736, -2208, -2208,   347,
     161,   572, -2208,   161,  1340, -2208,  1443,  1436, -2208,   161,
   -2208,  1447,  2873,  2873, -2208,  1340,   161,   188,   161,  1171,
    1171,   207,  1171, -2208,  1445,   381,   392,   433,   439,   459,
     463, -2208,  1340,   515, -2208,  1453, -2208,   152,   163, -2208,
     423,   752, -2208, -2208, -2208,   253,   759, -2208, -2208, -2208,
   -2208,  1136,   762, -2208,  3229,  5321,  3263,  3294,   161,   161,
   -2208, -2208, -2208, -2208,   764, -2208, -2208,  1250,  1340, -2208,
   -2208, -2208, -2208,  1178,   161, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208,  1340, -2208, -2208, -2208, -2208,  1457, -2208,  1457,
   -2208, -2208, -2208, -2208,   566, -2208,   205, -2208,  1452, -2208,
   -2208,  3328,  1460,  1462,  1462,  2682, -2208,  2873,  2873,  2873,
    2873,  2873,  2873,  2873,  2873,  2873,  2873,  2873,  2873,  2873,
    2873,  2873,  2873,  2873,  2873,  2873, -2208,  1405,  1343,  1459,
      68,   573,  2873, -2208, -2208, -2208,   767,  1246, -2208, -2208,
   -2208, -2208,   768, -2208,  1551,  1094,  2873,  1465,  1177,  1177,
    1177,  1177,  1177, -2208,  1146, -2208,   180,   180,  1239,  1470,
   -2208,  2932,  5321,   229,   264, -2208,  1473,  1474, -2208, -2208,
    1340, -2208, -2208, -2208, -2208,  1340, -2208,    49, -2208,   146,
   -2208, -2208, -2208,   161,  3413,   161,  1469,  2873,  1435, -2208,
   -2208,   161, -2208,  2873,  3494, -2208,   771, -2208, -2208,  1450,
   -2208, -2208,   799, -2208,   161, -2208,   161, -2208, -2208,  1202,
   -2208, -2208, -2208, -2208, -2208,  3544,  1340, -2208, -2208, -2208,
    1476,  1477,  1478,  1479,  1483,  1488, -2208,  1240, -2208,   161,
   -2208,  3581, -2208, -2208,   161,  3628,  3686, -2208,  1495,   807,
    1503,  1290, -2208, -2208,   161, -2208,  1506, -2208,  1489, -2208,
     161, -2208,  1393,   556, -2208, -2208,   -44, -2208, -2208,  1509,
   -2208,  1502,  1514,   810, -2208,   161,  1504, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208,  1505, -2208, -2208,    21,
    1510,  1512,  3733,  2575,   -92, -2208,  1486, -2208, -2208,   811,
   -2208, -2208, -2208, -2208, -2208,   815, -2208,  1498,   816, -2208,
   -2208, -2208,  2873, -2208,  1267, -2208, -2208, -2208,   827, -2208,
    1520, -2208,  1240,  1518,  1533,   832, -2208, -2208, -2208,  1534,
   -2208,  1526,  1528,  1521,   161,  2873,  2873, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208,  1536,  1538, -2208,   680, -2208, -2208,
    3771,  3818, -2208,  1527, -2208,   484,  1531, -2208, -2208, -2208,
   -2208,   486, -2208, -2208, -2208,   490, -2208,   492,   505,   545,
   -2208,   551, -2208,   557, -2208,  1542,  1544,  1547,  1548, -2208,
    1549,  1554, -2208, -2208, -2208, -2208, -2208, -2208,  1239,  1562,
    1550, -2208,  1552,   -76,   865, -2208,  1557,  1560, -2208, -2208,
    1564,  1566,  1567, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208,   572,   161,   151, -2208,  1568, -2208,  1572, -2208,
    1340, -2208, -2208, -2208,  1573, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208,  1216, -2208, -2208, -2208,   161,  1340,   113,
    1727, -2208, -2208,   161,   161, -2208,  1437,   205, -2208,  1574,
   -2208,  1529,  2873,  2932, -2208,  2873,  1462,  1462,   149,   149,
    2682,   875,  5352,  2947,  5321,  2947,  2947,  2947,  2947,  2947,
    5352,  5383,  1462,  5383,  4033,  1459, -2208, -2208,  1569,  1584,
    2400, -2208, -2208, -2208, -2208, -2208,  1586, -2208, -2208,   842,
    5321, -2208,  2873, -2208, -2208, -2208, -2208,  5321,   140,  5321,
    1465,  1465,   961,  1465,   655, -2208,  1470,  1590,   180,  3852,
    1591,  1593,  1594,  2932,  2932,  2932, -2208, -2208,   161,  1579,
   -2208, -2208,  1588,  1398, -2208,   347, -2208, -2208, -2208, -2208,
    1350,   619,   627, -2208,   873,   842, -2208,   842,   914,  5321,
    1601,   924, -2208,  5321,  2873,  2468, -2208,   925, -2208,   842,
    1457, -2208,   656,   665, -2208,   930,  1444,   947, -2208,  1899,
   -2208,   133, -2208,  1596,   161,   161,  2873,   161, -2208, -2208,
    1340, -2208, -2208, -2208,  1374,   161,  2873,   161, -2208,   161,
   -2208,  1239,  2873,  1595,  2575, -2208, -2208, -2208, -2208,   965,
   -2208,  1603, -2208,  1597,  1605,  1606,  1415,  2873,   161,   161,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208,   945,   161, -2208,
    2626,  3055,  1607,   161,   161, -2208,   161, -2208,   -37,   161,
   -2208,  2873,   161, -2208,  1457,  5321, -2208,  1616,    74,  1616,
   -2208,   161,  1240,  1622,  2661,   161,   161, -2208,   453,  2873,
     725,  2873,   966, -2208,  1615,  5321, -2208,    46, -2208, -2208,
   -2208, -2208, -2208,   945,    17, -2208,   161, -2208,   804, -2208,
   -2208,   259, -2208,   411,   840, -2208,   784, -2208,   404, -2208,
    -101, -2208,   161,   161,   161, -2208,   161,   161,   515, -2208,
     161, -2208, -2208, -2208, -2208, -2208, -2208, -2208,   161, -2208,
   -2208,   161,   161,   161, -2208, -2208,  1297,  1318,  1300, -2208,
   -2208, -2208,   161,   697, -2208, -2208,  1619, -2208,  1629, -2208,
   -2208,  1572, -2208, -2208, -2208, -2208,  5321,  2039, -2208, -2208,
   -2208,   560,   469,   469,  1391,  1394, -2208, -2208,  1395,  1396,
    1399,   576,   161, -2208, -2208, -2208, -2208,  1639, -2208, -2208,
   -2208,  1574, -2208,  1638, -2208,   749,  1633, -2208,  1637,  3883,
   -2208,  1632,  1634,  1290, -2208, -2208,  3917, -2208,  2873,  2873,
    1246, -2208,  5321,  2005,   180, -2208,   285,  2932,  2932,  2932,
     293, -2208,   295, -2208,   448, -2208,  1340,   161, -2208,  1459,
   -2208, -2208,  1646,   992,  2873, -2208,  1649, -2208,  5321, -2208,
   -2208, -2208,  2873, -2208, -2208,  2873, -2208, -2208, -2208, -2208,
    5321, -2208,  1444,  2873,  1636, -2208,  1641,  1642,  3952,  1656,
   -2208,    77,   161, -2208,   993, -2208, -2208,  1640,  5321, -2208,
   -2208,  3917, -2208,  1393, -2208,  1393,   161,   161,   161,  1003,
    1008, -2208,   161,  1657,  1652,  2873,  3987,  2722, -2208, -2208,
   -2208,  1340,  1239, -2208, -2208,  1501,  1670,  5321, -2208,   161,
   -2208,  1664,  1666, -2208, -2208,  1432,  1686, -2208, -2208,  1689,
   -2208,  5321,  1018, -2208,  1032, -2208, -2208,  4064, -2208, -2208,
    1033, -2208, -2208,  5321,  1678,   161, -2208, -2208,  1707,  1708,
    1516,  1654,   161,   161,  1709,  1720, -2208,   457, -2208,  1714,
   -2208, -2208, -2208,  1715, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208,   804, -2208, -2208, -2208, -2208,   259,   161, -2208, -2208,
    1038,  1718, -2208,  1719, -2208,  1724, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208,   840, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,   784,
   -2208, -2208, -2208, -2208, -2208,   404, -2208, -2208, -2208,  -101,
    1728,  1729,  1730,   936,  1054, -2208,  1732,  1735,  1239, -2208,
    1063,   906,  1064,  1069,  1071,  1072,  1742, -2208,  1744,  1739,
    2873,  2873, -2208, -2208,  1741, -2208,  1431,   697,  2094, -2208,
    1079, -2208,  5321, -2208, -2208, -2208,  1737, -2208, -2208, -2208,
   -2208,    68,    68,    68,    68,    68,  1437, -2208,  1749,  1760,
    1751,  1437,  1633, -2208,   205,   749,   111,   111, -2208, -2208,
   -2208,  1083,  1762,   920,   137, -2208,  1726,   749, -2208,  2873,
   -2208,  1750, -2208,  1290, -2208,  2400,  5321,  1755, -2208, -2208,
    1291,  1745,  1756,  1087,  1757,  1758,  1759, -2208, -2208, -2208,
    1767,  1459,  1768,     4,   842, -2208,  5321,   161,   945,  5321,
       4,  5321,  1444,  2873,  1769,  5321,  1088, -2208, -2208, -2208,
   -2208, -2208,  2873, -2208,  1773, -2208, -2208, -2208, -2208, -2208,
    1093,  1098,  1127, -2208, -2208, -2208,   794, -2208,  5321,  2873,
    2873,  4098, -2208,   161, -2208, -2208,  1670, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,  1771,    74,
    1772,  3192, -2208,   161,   161,   161,  2661, -2208, -2208, -2208,
     725, -2208, -2208, -2208,  2768,   161, -2208, -2208,  1765,  1785,
   -2208,   161,   161,  2873, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208,   411, -2208, -2208, -2208,  2873,
   -2208,  2873, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208,  1779,  1787, -2208, -2208, -2208, -2208, -2208,   161,
     161, -2208,  5321,  5321,  1129,  1793, -2208, -2208, -2208,  1784,
    4129, -2208, -2208, -2208,   560, -2208, -2208, -2208, -2208, -2208,
   -2208,  1437, -2208,   161, -2208, -2208,  1791,  1781, -2208,   830,
     137,   137,   749, -2208,   749,   111,   111,   111,   111,   111,
    1296,  4160, -2208, -2208, -2208, -2208,  2873, -2208, -2208, -2208,
   -2208,  1794,  1792,   743, -2208,   161,  1804,  1368,   161, -2208,
     161, -2208,  4191, -2208,  2873, -2208,  4235,  1563,  2873, -2208,
   -2208, -2208, -2208,  1138, -2208, -2208,  5321,  5321,  2873,  1799,
   -2208,   834, -2208,  2873, -2208,  1795,  1797, -2208, -2208,  1805,
    1814, -2208, -2208, -2208, -2208, -2208,  1693,  1806,  1156,  1819,
    1822,  1164,   999,   161,   161, -2208, -2208,  5321,   231,  1811,
     355, -2208, -2208,  1798, -2208, -2208,   -47,  4276,  4330, -2208,
   -2208, -2208, -2208, -2208,   161,   161,   906,  1167,  1813,  1829,
    1833, -2208, -2208, -2208,  1727,  1820, -2208,  1459, -2208,   749,
   -2208,  1296,  1823,   137,   137, -2208, -2208, -2208, -2208,  4361,
   -2208,  3917, -2208,  1181, -2208,   801, -2208,   842,  1562, -2208,
    1444, -2208,  1598, -2208,  1828,  4397,   794, -2208,  5321,  2234,
    1830,  1835,  1836,  1837,  1840,  1842,   161,   161,  1846,  1847,
    4476, -2208, -2208, -2208,  2873,   161,   161, -2208, -2208,  1848,
     161, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
    1857, -2208, -2208, -2208, -2208, -2208,  1182, -2208, -2208, -2208,
   -2208,  1844, -2208, -2208,   614,  1861, -2208,  1862, -2208, -2208,
    1867, -2208, -2208,  1856,  1213,  1296, -2208,  2873,  1794, -2208,
   -2208,  2873,   161,  2873, -2208, -2208, -2208,  5321,  1218, -2208,
   -2208,  1830,   161,   161,   161,   161,   161, -2208, -2208,  2873,
    2873,  2873,  1222, -2208, -2208,  1870, -2208,  1224,  1872,  1227,
     161,  2873, -2208, -2208, -2208, -2208,  2873, -2208,   161,  1860,
   -2208, -2208,  4725, -2208,  5321, -2208, -2208,  1869,  5067,  2234,
   -2208,    64, -2208,  1878,  1249,  1256,  1881,  1266,  1876,  1270,
    5101,  5132,  1871,  5163, -2208,   161,  1816, -2208, -2208, -2208,
   -2208,  1562, -2208,  5194,  5225,   696,  1570, -2208,  1887, -2208,
   -2208,  2873,  1832, -2208, -2208,  1890,  1892,   161,   161, -2208,
   -2208,   161, -2208,  2873, -2208, -2208,  2873, -2208,  2873, -2208,
    1879,  1271,  1277, -2208, -2208,  1886,   161,  5321,   161,  5321,
    1281, -2208, -2208, -2208, -2208,  1301, -2208,  1893,  1303,  1328,
    1336,  5256,  5321, -2208, -2208, -2208,  2873, -2208, -2208,  1885,
    1832, -2208,   161, -2208,  2873, -2208, -2208,  1884,  2873,  1363,
    2873,  1894, -2208, -2208, -2208,  5290,  1366, -2208, -2208,  5321,
    1902, -2208,  2873,  2873,  2873,  1897, -2208, -2208, -2208,  5321,
   -2208, -2208,   -72,   363,  1371, -2208,  1910,  1911, -2208, -2208,
   -2208,  1904,  1904,  1904, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208,   476,  1913, -2208,  1803, -2208,  1372, -2208,
   -2208, -2208
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2208, -2208, -2208, -2208, -2208,     8,  1704,  1043, -2208, -2208,
    -656,   -52, -2208, -2208,  -367, -2208,   700, -2208,   -50,  1040,
   -2208, -2208, -2208,  2177,    15, -2208, -2208, -2208, -2208, -2208,
   -2208,   141,   412,   773, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208,  -143,  -880, -2208, -2208, -2208,   869,   407,  1376,
   -2208,  -188, -1492,   150, -2208, -2208, -2208, -2208, -2208, -2208,
    1375,  -283,  -343, -2208, -2208, -2208,  1377, -2208,  -500, -2208,
   -2208, -2208, -2208,  1257, -2208, -2208,   687, -1258, -1489,  1039,
     393, -1446,  -183,   -77,  1052, -2208,   138,   156, -1739, -2208,
   -1490, -1201, -1482,  -213, -2208,   -41, -1499, -1740,  -640, -2208,
   -2208,   516,   838,   306,  -107,    59, -2208,   537, -2208, -2208,
   -2208, -2208, -2208,  -116, -2208,    47,  -631,   983, -2208,   967,
     611,   636,  -365, -2208, -2208,   926, -2208, -2208, -2208, -2208,
     351,   353,  1924,   772,  -349, -1275,   155,  -417, -1373,   774,
    -537,  -595,  1373,    12,  1553,  -968,   139, -2208, -2208,  -606,
    -608,  -237, -2208,  -851, -2208,  -582,  -904, -1097, -2208, -2208,
   -2208,   135, -2208, -2208,  1309, -2208, -2208,  1766, -2208,  1775,
   -2208, -2208,   641, -2208,  -378,    14, -2208, -2208,  1776,  1777,
   -2208,   606, -2208,  -720,  -178,  1238, -2208,  1140, -2208, -2208,
     -55, -2208,  1001,   443, -2208,  4527,  -402, -1059, -2208, -2208,
   -2208, -2208, -2208, -2208,   944, -2208,   441,  -835, -2208, -2208,
   -2208,   428, -1235,  -598,  1044,  -931,  -373,  -422,  -441,   414,
     190, -2208, -2208, -2208,  1386, -2208, -2208,   973, -2208, -2208,
     946, -2208,  1210, -1867,   879, -2208, -2208, -2208,  1397, -2208,
    1400, -2208,  1401, -2208,  1385,  -993, -2208, -2208, -2208,  -149,
    -261, -2208, -2208, -2208,  -387, -2208,  1442,   657,  -340,   654,
   -2208,   -24, -2208, -2208, -2208,  -328, -2208, -2208, -2208, -1535,
   -2208, -2208, -2208, -2208, -2208, -1389,  -561,   124, -2208,  -181,
   -2208,  1269,  1060, -2208, -2208,  1065, -2208, -2208, -2208, -2208,
    -286, -2208, -2208,   991, -2208, -2208,  1047, -2208,   196,  1053,
   -2208, -2208, -2208,   628, -2208, -2208, -2208,  -224, -2208, -2208,
     162, -2208,  -751,  -377,  -355, -2208, -2208, -2208, -1448, -2208,
   -2208, -2208,  -179, -2208, -2208,  -296, -2208,  -317, -2208,  -336,
   -2208,  -337, -2207,  -989,  -752, -2208,  -113,  -470,  -883, -1908,
   -2208, -2208, -2208,  -456, -1475,   386, -2208,  -701, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208,  -468, -1416,   629,
   -2208,   157, -2208,  1433, -2208,  1592, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -1386,   669, -2208,  1345, -2208,
   -2208, -2208, -2208,  1721, -2208, -2208, -2208,   218,  1687, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,   587,
   -2208, -2208, -2208,   164, -2208, -2208, -2208, -2208,   -71, -1827,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
     580,   350,  -524, -1308, -1199, -1323, -1408, -1406, -1398, -2208,
   -1388, -1382, -1253, -2208, -2208, -2208, -2208, -2208,   333, -2208,
   -2208, -2208, -2208, -2208,   384, -1381, -1375, -2208, -2208, -2208,
     337, -2208, -2208,   376, -2208,   520, -2208, -2208, -2208, -2208,
     348, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208, -2208, -2208, -2208,   158, -2208,   160,  -105,
   -2208, -2208, -2208, -2208, -2208, -2208, -2208,   909, -2208, -2208,
   -2208,  -809, -2208,   143, -2208, -2208, -2208, -2208, -2208, -2208,
   -2208, -2208, -2208,   898, -2208, -2208, -2208,   894, -2208, -2208,
   -2208, -2208,   896, -2208
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1175
static const yytype_int16 yytable[] =
{
     399,   799,   661,   676,   687,   851,   803,   954,  1552,   958,
     411,   411,   699,  1068,   626,   657,  1432,   419,   626,   782,
    1572,  1261,   714,  1634,   717,   811,   812,   813,   814,   720,
     721,   722,  1650,   972,   681,  1352,  1783,   723,  1785,  1684,
     725,   988,   727,  1800,  1649,  1081,   445,  1305,  1020,  1212,
    1332,  1803,   726,   774,  1388,   922,   984,   984,  1373,  1805,
    1780,   550,  1677,  1819,  1027,  1557,  1833,  2098,   464,  2075,
    1057,  1444,   467,   730,  1165,  1164,   744,   413,  1750,   834,
    1751,   794,  2024,  1433,   426,  1883,  2030,  2031,  1752,   755,
    1708,   775,  1339,  1585,   680,  1001,  1784,   391,  1753,  1302,
    1302,   983,   983,   771,  1754,  1756,  1503,   447,   776,  -541,
    2409,  1757,   784,   666,   787,  1823,  1340,  1698,  1868,   391,
    1838,  1671,  1312,   391,   462,  1413,  1825,   806,  1532,     2,
       3,  1341,  1413,   410,   707,     8,  1342,  1343,  1039,   820,
     577,   823,  2037,  1344,  2218,   540,   410,  -527,   829,  1453,
     881,   650,   489,   651,   927,  -563,   881,   946,   928,   362,
    -339,  1739,   394,  1749,  1414,  1762,   882,   564,  1424,  1425,
     961,   571,   573,  1207,  2038,  -561,  1737,   578,  1747,   965,
    1760,  1710,  1766,   967,  1211,   716,   943,   972,   789,  1703,
     974,  1040,   394,  1162,  2193,   977,   577,   410,  1890,  1891,
    1892,  1426,   677,   410,  1172,   391,  -137,   793,   973,  2425,
    2427,   975,  2325,   392,   891,   577,   678,   600,  2226,  1041,
    1267,  1194,  2431,   626,   903,   904,   905,   906,  -141,  1434,
    1139,  1745,   -61,  1755,   410,  1763,  2196,  1333,  1415,  1504,
     410,  2219,  1505,   957,  2326,  1415,  2410,  2197,  2198,  -582,
    -541,  1672,  2220,  2199,  1699,  2200,  -563,  1238,   577,  1042,
    1828,  -527,   600,   625,  2201,  -527,  2202,   625,  2203,  -563,
    1043,  1262,  -591,  -339,   410,   410,  -339,  1345,  1082,     4,
     410,   410,  2136,  -561,  -591,  1738,  1472,  1748,   907,  1761,
     410,  1767,   410,  -592,  1220,  2143,  2144,  1017,  1044,   410,
    1012,  -585,   410,  -589, -1099,  -592,   410,  1642,  1346,   410,
     652,   655,   429,  -585,  1002,  -589,   662,   663,   667,   663,
    1048,   671,   673, -1124,  1862,   679,  2029,   683,   685,   685,
     688,  1884,  1144,   691,   410,  2027,   695,  1021,   691,  2075,
    1134,  1807,  1809,   706,  1306,  -582,   711,  -137,   691,  1585,
     691,  1750,  1347,  1751,   411,   691,   691,   691,  1133,  1336,
    1135,  1752,   485,   691,  1337,   724,   691,  1069,   691,  -141,
     972,  1753,   972,   -61,   735,   736,  2025,  1754,  1756,   972,
    -591,   747,   749,   626,  1757,   754,     5,   626,   947,   577,
    2204,  1045,   761,  2205,   626,   765,   553,  -563,   495,   984,
     577,  -592,  1591,  1593,  1595,  1380,  1141,   778,  1533,  -585,
     785,  -589,  1469,  1405,  1471,  1121,   706,   795,   797,   797,
     719,   801,   778,  1739,  -561,  1537,   579,   807,   809,   809,
     809,   809,   809,  1131,   818,   732,  1749,   822,  1737,   824,
     761,   577,  1762,   827,  1330, -1099,   830,   577,  1727,  2212,
     835,  1747,   948,  1464,  1160,  1400,  -587,  1760,   496,  1678,
     948,  1766,  1221,   769, -1124,  1578,  2360,   577,  -587,   537,
     777,   577,   625,  1798,  1799,  1064,   677,  1159,  2206,   852,
    1161,  1222,   853,  1943,   558,   559,  -582,   860,   865,   871,
     678,  2411,   577,  1745,   577,  2352,  1259, -1046,   577,   883,
     577,   546,   888,   889,   890,   679,  1755,   554, -1135,   893,
     896,   897,  1763,   577,   902,   679,   679,   679,   679,  2101,
    2412,  -591,   910,   911,  1803,  1722,  1260,  1320,  1321,  1322,
    1323,  1324,  1805,  2141,  2138,  2088,  2207,  2208,  2209,   972,
     410,  1615,  -592,  2352,   626,    46,  1177,  1738,   538, -1151,
    -585,  2127,  -589,   577,   570, -1154,   878,   879,  1552,   577,
    1748,  1548,   539,  2023,  -587,   577,  1761,   572,   894,  -527,
    1767,   555,    50,  1295,  1265, -1088,  1542,  1543,    74, -1118,
    2413,   580,   410,  -527,  1816,  2213,  2052,   551,   695,   990,
     747,   801,   795,   683,   995,  1708,  -527,   824,   997,  1074,
   -1098,   560, -1123,  1266,  2411,   679, -1045,  1006, -1134,  1525,
    2158,    96,  1709,  1817,  1216,  1557,  1008,   948,  1549,    25,
    -384, -1150,  -382,   691,    29,  1120,  1019,  1531,   679,   948,
    -383,  1217,   625,  2412,  1598,  2275,   625,  1304, -1046,  2214,
    2235,   109,  1599,   625,  1132,   957,    47,    48,   978, -1135,
    2215,  1036,  1548,   999,   556,  1376,  1591,  1593,  1595,  -382,
     968, -1153,  1195,  1196,   969,   629,  1000, -1087,  -383,   637,
    1550,   946,   118, -1117,   581,  1570,  1058,  2225,  1063,   122,
     949,  1065,  1068,  1770,  1771,  1772,  1710,  1776,  1777,  1711,
   -1151,   984,   971,  1076,  1079,  1197, -1154,   898,  1029,   948,
      90,   557,   410,  1108,  -845,  -587,  1109,   899,   582,  1549,
      95,  1030,  1115,  1114,  1116,  1790, -1088,  1081,  1081,  1123,
   -1118,  1127,   600,  1791,   679,   972,   972,   972,   972,   972,
    1688,   626,   626,   626,   626,   626,   983,   652,  1571,  2279,
    1623, -1098,  1037, -1123,  1156,  1312,  -387, -1045,  1079, -1134,
     563,   984,   984,   984,   679,  1038,   121,  1157,   952,  1630,
    1218,  1550, -1150,  2023,  1825,  1826,  1827,  1223,   679,   566,
    1226,   679,  1234,  1219,  2267,  1307,  1313,  1168,  1167,  1365,
    1224,  2299,  1174,  1227,   364,  1235,  1180,  1873,  1308,  1314,
     370,  1186,  1366,   625,  1190,  1192,  1590,  1592,  1594,  1688,
     377,  2072, -1153,   379,  -385,  2295,   382,  1369, -1087,  1213,
    1464,  2262,  1464,   388, -1117,  1397,   952,   395,  1419,  1436,
    1370,   398,  2311,  1439,  1442,   567,  1231,   822,  1398,  1198,
    1199,  1420,  1437,  1200,  1201,   999,  1440,  1443,  2297,   417,
    1456,   568,  1256,   421,   422,  2391,  2035,  2036,  1450,   427,
     428,  2140,  1263,  1457,  1264,   433,   434,  2398,   435,   436,
     437,   438,  2233,   439,  1268,  1519,  2294,  1271,  1731,  1208,
    1208,  1248,   448,  1506,  1249,  2170,   569,   452,   410,   454,
     927,  1600,   574,   457,   928,   575,  1507,   461,  1233,   463,
     576,   929,   930,   616,  1601,  1352,   469,  1635,  1828,  1636,
     473,   631,  1373,  1257,   476,  1698,   478,  2015,  2016,  2017,
    2018,  2019,   943,   486,   488,  2359,   639,   490,   491,  2011,
    1538,   640,  1604,   497,  1731,   498,   641,  -230,  1980,   502,
    1981,   642,  1029,  1307,  1580,  1605,  2035,  2036,  1613,  1982,
    1583,  1983,  2358,   643,  1581,  1607,  1610,   652,   644,  1918,
    1350,  1614,   391,  1356,  2152,  1617,   529,   645,   531,   667,
    1302,  1302,  1302,  1302,  1302,  1857,   968,   646,  1618,  2171,
     969,  1847,   688,  1643,  1695,  1708,   649,   621,   622,   658,
     625,   625,   625,   625,   625,   659,  1644,  1696,   978,   978,
    1602,   660,  1709,  2379,  1464,  1708,   674,  1390,   971,   682,
    1369,  1604,   711,  1413,  1611,   984,   984,   984,   697,  1622,
    1578,  1604,  1709,  1865,  1887,   769,  1419,  1633,   736,   694,
     604,  1980,   700,  1981,  1893,  2172,  1926,  1416,  2055,  1894,
    1902,  1708,  1982,   749,  1983,  2060,   709,  1615,   769,  1927,
    1456,  1930,  1699,  2173,   715,  1627,  1955,  1629,  1709,  1732,
    1853,  1592,  1594,  1928,  1931,  2174,   728,  2175,  2176,  1956,
    2177,   733,  1975,  2178,  1984,  1985,  1710,  1986,  1987,  1711,
    1438,  1500,  1994,  1733,  1712,  1976,  1401,  1695,  1652,  1456,
    1695,   743,  1713,  1734,  1979,  1995,  1710,  2012,  1735,  1711,
    1996,  2032,  1997,  1998,  1712,  -585,  2064,   746,  1988,   968,
    2013,  1500,  1713,   969,  2033,  1732,  1500,   752,  1842,  2065,
     621,   622,   753,  1467,  2069,  1318,  1415,   970,   756,  2070,
    1479,   759,  1710,   760,  1702,  1711,  1482,   764,   410,  1733,
    1485,   971,  1487,  1485,  1485,  1500,  1489,  2129,  1491,  1734,
    1989,  2152,  1850,   768,  1735,   772,  2166,   766,  2071,   773,
    2130,   968,   800,  1990,  2179,   969,  1498,  1984,  1985,  2167,
    1986,  1987,   621,   622,  1156,   703,   808,  1325,   860,   970,
    -785,  -785,  1456,   865,   832,  1500,   871,  2189,  1516,  1517,
    1518,  1520,   883,   971,  1944,  2191,  1946,  1947,  2227,  2238,
    2271,  1988,   781,   621,   622,   647,   648,   632,  1951,   636,
     638,  1845,  2239,  2272,   595,  1530,   833,  1031,  1958,  1032,
    1960,   679,   590,   597,   757,  1268,   591,   592,   593,   594,
     836,  2032,  1239,  1528,  1529,  1861,  2289,  1863,   880,   595,
    1604,   895,  1456,  1989,  2281,  2309,   596,  2043,   597,  2290,
    1870,   598,   948,  2304,  1872,  2307,  1990,   838,  2310,   804,
   -1174,  1309,  1973,  1974,  1886,   972,   590,  1419,   857,   815,
     591,   592,   593,   594,  1500,  1240,   598,   858,   828,   599,
    2329,  1241,   968,   595,  1456,   859,   969,  2330,  1695,  1994,
     596,   892,   597,   621,   622,  1994,  1596,  2332,  1446,  2370,
     970,  2334,  2364,   949,   599,   919,   968,  1242,  2365,  1537,
     969,   950,  2371,   951,   971,   952,   623,   621,   622,  2372,
     598,  1419,  2035,  2036,   970,  1612,   874,   875,   876,   877,
     955,  1243,  2373,  1244,  2375,  2241,   600,   976,   971,  1808,
    1810,   410,  1625,  1625,   966,  1625,  1456,   996,   599,   789,
     978,  1005,   634,   691,  1156,  1058,   626,  1058,  1007,  2376,
    1637,   600,   620,   621,   622,  1009,  1245,  2377,    25,  1178,
    1179,  1246,  1182,    29,   595,  1247,   921,   923,   924,  1248,
     925,  1604,  1249,   597,  2394,   410,  1011,   926,   601,  2414,
    1574,  1660,   588,   589,  2390,    47,    48,  2395,  1024,  1669,
    1127,   804,  2415,  2430,  1250,   600,  1673,  2145,  2146,  2147,
    1675,   598,  1018,   601,  1326,  1327,   679,  1028,  1251,  1854,
    1855,  1856,   961,   394,  1252,  1049,    25,  1052,  1700,   548,
    1701,    29,  1704,  2420,  2421,  2341,  2342,  1188,  1189,   599,
    1054,   946,  1070,  1004,  1071,  1072,  1077,  1085,  1086,    90,
    1113,  1140,  1154,    47,    48,  1773,  1662,   601,  1014,    95,
    1151,  1163,  1541,  1542,  1543,  1169,  1213,  1166,  1177,  1781,
    1183,  1206,  1225,  1236,  1544,   577,   623,  1272,  1275,  1296,
    1789,   928,  1297,  1545,   969,  1239,  1035,  1109,  1328,  1796,
    -342,  1334,  1335,  1051,  1357,  2264,   600,  1368,  1707,  1055,
    1056,  1382,  1383,  1384,  1385,   121,  1546,    90,  1386,  2056,
    1818,  1547,  1360,  1387,  1208,  1208,  1208,    95,  1208,  1208,
    1396,  1399,  1778,  1829,  1402,  1404,  -924,  1417,  1240,  2058,
    1208,  1418,  1408,  1435,  1441,  1422,  1423,  1451,   549,  1548,
    1428,  1427,  1637,  1454,  1112,  1637,  1637,  1637,   601,   150,
    1455,  1459,  1458,  1460,  1468,  1858,  1470,  1461,  1477,  2043,
    1242,  1081,  1480,   121,  2298,  1464,  1315,  1492,  2100,  1493,
    1316,   590,  1494,  1495,  1496,   591,   592,   593,   594,  1497,
    1500,  1501,  1508,  1502,  1243,  1509,  1244,   898,   595,  1511,
     691,  1512,  1513,  1522,  1073,   596,  1549,   597,  1527,  1565,
    1573,  1568,  1574,  1579,   362,   625,   978,   150,  1584,  1587,
    1895,  1588,  1589,   392,  2339,  1597,  1170,  1171,  1606,  1245,
     961,  1623,  1646,  1632,  1246,   598,  1640,  1065,  1247,  1645,
    1647,  1648,  1248,  1414,  1670,  1249,  2357,  1081,  1659,  1679,
    1697,  1786,  2192,  1787,  1793,  1788,  1795,  1811,  1550,  2134,
    1812,  1813,  1814,   599,  1821,  1815,  1824,  1250,  1837,  2137,
    1937,  1938,  1839,  1842,  1864,  1843,  1867,  1878,  1208,  1208,
    1208,  1251,  1879,  1880,  1882,   927,  -494,  1252,  1258,   928,
     590,  2357,  1896,  1897,  1903,  1954,   929,   930,  1904,  1920,
     410,  1921,   931,   932,   933,   934,   935,  1923,   936,   937,
     938,   939,   940,   941,  1924,   942,  1925,   943,   944,  1932,
     600,  1276,  1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,
    1285,  1286,  1287,  1288,  1289,  1290,  1291,  1292,  1293,  1294,
    2257,  2258,  1935,  1936,  1699,  1698,   804,  1941,  1942,  1945,
    1948,  1310,  1534,  1957,  1959,  2039,   780,   590,  1317,  1961,
    1319,   591,   592,   593,   594,  2014,   781,   621,   622,  1970,
    1971,  1972,   601,  1977,   595,  1329,  1978,  1999,   595,  2000,
    2001,   596,  2006,   597,  -381,  2021,  2022,   597,  1338,  2034,
    2042,  2046,  2026,  1829,  1829,  1829,  2045,  2047,  2048,  2049,
    2050,  1359,  2051,  2103,  2293,  1829,  2296,  1363,  2068,  2053,
    2063,   598,  2240,  2104,  2124,   598,   731,  2083,  2085,  2150,
    2131,  1430,  2125,  1035,   590,  2132,  -224,  2139,   591,   592,
     593,   594,  2157,  2155,  2169,   667,  2182,  2164,  2183,   599,
    2184,   595,  2185,   599,   731,  2186,  -836,  2188,   596,  2190,
     597,   731,  2211,  2067,  2228,  2217,  2229,  1688,   708,   790,
    2230,  2232,   590,  2243,  2236,  2250,   591,   592,   593,   594,
    2252,  2253,  2254,  2242,  2081,  2255,   410,  2256,   598,   595,
     623,  2259,  2260,  2266,  2270,  2274,   596,  1673,   597,  2276,
    2277,  1858,  2348,  2089,  2278,   769,   600,  2280,  2305,  2308,
     600,  2320,   769,  2099,  2322,  2328,   599,  1431,  2331,  2105,
    1704,  2333,  2337,   961,  2340,  2346,   598,  2353,  2110,  2354,
    2363,  2366,  2380,  2345,  1031,  2388,  1445,  2116,  2374,   590,
    2396,  2392,  2401,   591,   592,   593,   594,  2416,  2417,  2418,
    2429,   561,  1232,   410,   599,  1773,   595,  1237,   601,  1465,
     815,  2411,   601,   596,  1521,   597,  2086,  2007,  1797,  1794,
    1473,   900,  1412,   600,  2126,   908,  2231,  2008,   909,   837,
    1025,   839,  1540,   912,  1822,  1269,  2234,  2142,   840,   841,
     842,   410,  2028,   598,   845,   846,   847,   848,  1270,   849,
     850,  1818,  2020,  2135,  1686,  1449,  1919,  2181,  2084,  1668,
    1829,   600,  1829,  1829,  1829,  1829,  1829,  1829,  2195,  2106,
    1619,   599,  1361,  1603,  1888,   601,  1378,  1407,  1889,   425,
    2044,  2428,  2054,  1026,   770,  2059,  1609,   583,  1639,   731,
     959,  1208,  1130,  1526,   960,  2162,   584,   585,   586,  1367,
     781,   621,   622,  1848,  1849,  1331,   989,  1393,   410,  1158,
     994,  1421,   595,   601,  1536,  1466,  2263,  1624,  1621,   991,
    2161,   597,  2383,   992,  1801,   993,  1569,  2087,   600,   590,
     797,  2194,  1938,   591,   592,   593,   594,  2283,  1138,  1349,
    2367,  1406,  1348,  2057,  1362,  2324,   595,  1664,  2082,   598,
    1208,  1371,  2292,   596,  1576,   597,  2384,  2400,  2422,  2424,
    2269,  1933,   998,  2094,   826,  1685,  1582,  1829,  1651,  1078,
    2061,   718,   670,  1779,  2095,  2245,  1963,   599,  1967,  2009,
     601,  1061,  1953,   598,   590,  1950,  1969,  1965,   591,   592,
     593,   594,  2273,  2115,  2113,  1499,  1510,  1514,  2123,  1080,
       0,   595,  1515,     0,   809,   809,     0,     0,   596,     0,
     597,   599,  1111,  2089,   623,     0,  2224,  1208,  1608,  1014,
    1117,  1118,     0,     0,     0,  1124,     0,     0,    13,    14,
       0,    15,    16,  1620,   600,     0,    20,     0,   598,     0,
    1628,     0,     0,     0,    23,     0,     0,     0,   410,    27,
    1359,   961,    30,  1080,     0,     0,  1638,     0,  1641,     0,
      37,  1152,    38,     0,    40,     0,   599,     0,   600,     0,
    2285,  1359,     0,     0,     0,     0,     0,     0,     0,     0,
    1079,     0,  1079,     0,  1656,     0,   601,    59,     0,  1173,
       0,  1176,     0,     0,     0,  1667,  2306,     0,    70,     0,
       0,     0,     0,   410,     0,     0,  2317,  2316,  1681,     0,
     731,   731,     0,  1687,     0,  1693,  1142,     0,     0,  2246,
     601,     0,    85,   600,   590,     0,     0,     0,   591,   592,
     593,   594,     0,     0,     0,    93,     0,     0,  1781,  1781,
       0,   595,     0,     0,     0,  1208,     0,     0,   596,     0,
     597,     0,     0,   102,     0,     0,     0,     0,     0,   104,
       0,     0,  1208,     0,     0,     0,     0,   108,  2315,   110,
       0,   112,     0,   114,  2317,   601,  2368,     0,   598,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,   618,
       0,  1802,     0,   619,     0,     0,     0,   130,   131,   620,
     621,   622,     0,  1301,  1301,     0,   599,     0,     0,     0,
       0,   595,     0,     0,     0,   143,     0,     0,     0,     0,
     597,     0,   587,     0,     0,     0,  2402,     0,     0,   731,
     731,  2403,  1846,   804,  1310,     0,   155,     0,     0,   156,
       0,     0,     0,   410,  2403,     0,  2423,  2426,   598,    13,
      14,     0,    15,    16,     0,     0,  1351,    20,  1866,  2426,
       0,     0,     0,   600,     0,    23,  1869,     0,     0,  1871,
      27,     0,     0,    30,     0,     0,   599,  1875,     0,  1372,
       0,    37,     0,    38,     0,    40,     0,  1430,     0,     0,
     590,     0,     0,     0,   591,   592,   593,   594,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   595,    59,  1898,
       0,  1901,     0,   623,   596,   601,   597,   731,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   600,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,   598,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1013,    93,     0,   590,  1381,
       0,     0,   591,   592,   593,   594,     0,     0,     0,     0,
    1389,     0,   599,     0,   102,   595,     0,     0,     0,     0,
     104,     0,   596,     0,   597,   601,     0,     0,   108,     0,
     110,     0,   112,     0,   114,     0,     0,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,  1080,     0,   410,
       0,     0,   598,     0,     0,     0,     0,     0,   130,   131,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   600,
       0,     0,     0,     0,     0,     0,   143,     0,     0,     0,
     599,     0,     0,     0,  2002,  2003,   961,     0,     0,     0,
       0,     0,  2010,     0,     0,     0,     0,   155,     0,     0,
     156,     0,  1430,  1452,     0,   590,     0,     0,     0,   591,
     592,   593,   594,     0,     0,     0,     0,   410,     0,     0,
       0,   601,   595,     0,     0,     0,     0,     0,     0,   596,
       0,   597,     0,  2041,     0,     0,  1478,   600,     0,  1576,
       0,     0,  1481,     0,     0,     0,  1484,     0,  1486,     0,
       0,     0,  1488,  1655,  1490,     0,   590,  1539,     0,   598,
     591,   592,   593,   594,     0,     0,     0,  2062,     0,     0,
       0,     0,     0,   595,     0,     0,  2066,     0,     0,     0,
     596,     0,   597,     0,     0,     0,     0,   599,  1680,   601,
       0,   590,     0,  2076,  2077,   591,   592,   593,   594,     0,
       0,     0,     0,     0,     0,     0,     0,   927,   595,     0,
     598,   928,     0,     0,     0,   596,     0,   597,   929,   930,
    1681,   731,     0,     0,   410,   932,     0,   934,   815,     0,
     936,   937,   938,   939,   940,     0,     0,  2107,   599,   943,
       0,     0,     0,     0,   600,   598,     0,     0,     0,  1900,
       0,     0,   590,  2117,     0,  2118,   591,   592,   593,   594,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   595,
       0,     0,     0,   599,     0,   410,   596,     0,   597,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1061,     0,  1061,     0,     0,   600,   601,     0,   590,     0,
       0,   945,   591,   592,   593,   594,   598,     0,     0,     0,
     410,  1080,  1080,     0,     0,   595,     0,     0,     0,     0,
       0,  1653,   596,     0,   597,     0,     0,   731,     0,  1663,
     600,     0,  1124,     0,   599,     0,     0,     0,     0,     0,
    2149,     0,     0,     0,   790,  2151,     0,   601,  1080,  1080,
       0,     0,   598,     0,  1631,     0,     0,     0,  1875,     0,
       0,     0,  2165,     0,     0,     0,  2097,     0,     0,   731,
       0,   410,  2168,     0,     0,     0,  1728,  2180,     0,     0,
     599,     0,   601,     0,     0,   731,   731,   731,     0,   731,
     731,   600,     0,   731,     0,     0,     0,     0,     0,     0,
       0,   731,  1665,   590,  1080,  1080,  1080,   591,   592,   593,
     594,     0,     0,     0,     0,     0,     0,   410,     0,     0,
     595,     0,     0,     0,     0,     0,     0,   596,  1536,   597,
       0,     0,     0,     0,     0,     0,     0,   600,     0,     0,
       0,  1721,     0,   601,  1726,  1820,     0,  1746,     0,  1759,
    1105,  1765,     0,  1769,   945,     0,     0,   598,     0,     0,
       0,     0,   590,  2247,     0,     0,   591,   981,   593,   594,
       0,     0,   927,     0,     0,     0,   928,   731,  1359,   595,
       0,     0,     0,   929,   930,   599,   596,     0,   597,   601,
     932,     0, -1175,     0,     0, -1175, -1175, -1175, -1175, -1175,
       0,   945,     0,     0,   943,     0,     0,     0,     0,     0,
       0,     0,   945,     0,     0,     0,   598,     0,     0,     0,
       0,     0,   410,     0,     0,     0,     0,     0,     0,     0,
       0,  2282,  2151,     0,     0,  2284,     0,  2288,     0,   731,
     731,   731,   600,     0,   599,     0,     0,     0,     0,     0,
       0,     0,     0,  2300,  2301,  2303,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2313,     0,     0,     0,     0,
    2314,   945,   945,   945,   945,     0,     0,     0,     0,     0,
     927,   410,  1657,  2247,   928,   590,     0,     0,  1080,     0,
       0,   929,   930,     0,   601,     0,  1658,   931,   932,   933,
     934,   600,     0,   936,   937,   938,   939,   940,   941,     0,
     942,     0,   943,   944,     0,  2347,  2349,     0,   945,     0,
     945,   945,   945,   945,   927,     0,  1155,   815,   928,   590,
    2361,     0,  2362,     0,     0,   929,   930,     0,     0,     0,
       0,   931,   932,   933,   934,     0,     0,   936,   937,   938,
     939,   940,   941,   601,   942,     0,   943,   944,     0,     0,
    1359,     0,     0,     0,  2349,     0,     0,     0,  2385,     0,
       0,     0,  2389,     0,  1693,     0,     0,     0,     0,   945,
    1949,     0,     0,     0,     0,  1952,  1693,  2399,  2385,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1962,     0,
       0,   945,     0,     0,  1301,  1301,  1301,  1301,  1301,     0,
       0,   945,     0,     0,     0,     0,     0,  1087,     0,     0,
    1964,  1088,   590,     0,     0,     0,  1966,     0,  1089,  1090,
    1968,     0,   945,     0,  1091,  1092,  1093,  1094,     0,     0,
    1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,   945,  1103,
    1104,     0,   945,   945,   927,     0,  1351,  1228,   928,   590,
       0,     0,     0,  1372,     0,   929,   930,     0,     0,     0,
       0,   931,   932,   933,   934,     0,     0,   936,   937,   938,
     939,   940,   941,     0,   942,     0,   943,   944,   927,     0,
       0,  1229,   928,   590,     0,     0,  2079,     0,     0,   929,
     930,     0,     0,     0,     0,   931,   932,   933,   934,   945,
       0,   936,   937,   938,   939,   940,   941,   790,   942,   927,
     943,   944,  1230,   928,   590,     0,     0,     0,  1080,     0,
     929,   930,     0,     0,     0,     0,   931,   932,   933,   934,
       0,     0,   936,   937,   938,   939,   940,   941,  2114,   942,
       0,   943,   944,   927,     0,     0,     0,   928,   590,     0,
       0,     0,     0,     0,   929,   930,     0,   945,   945,  1274,
     931,   932,   933,   934,     0,     0,   936,   937,   938,   939,
     940,   941,     0,   942,     0,   943,   944,     0,     0,     0,
       0,     0,   731,  2128,  2096,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2108,     0,     0,
       0,     0,  2111,     0,     0,  2112,  1820,     0,     0,     0,
       0,     0,     0,     0,     0,  2119,     0,  2120,     0,  2121,
       0,  2122,     0,     0,     0,     0,     0,     0,   927,     0,
       0,     0,   928,   590,     0,     0,     0,     0,  2156,   929,
     930,   731,     0,  2159,  1355,   931,   932,   933,   934,     0,
       0,   936,   937,   938,   939,   940,   941,     0,   942,     0,
     943,   944,     0,   945,   945,   945,   945,   945,   945,   945,
     945,   945,   945,   945,   945,   945,   945,   945,   945,   945,
     945,   945,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   945,     0,     0,
       0,     0,     0,     0,   945,     0,   945,   731,   731,   927,
       0,  1364,     0,   928,   590,     0,   945,     0,     0,     0,
     929,   930,     0,     0,     0,     0,   931,   932,   933,   934,
       0,     0,   936,   937,   938,   939,   940,   941,     0,   942,
       0,   943,   944,     0,     0,     0,   945,     0,     0,     0,
     945,     0,     0,     0,     0,     0,     0,     0,     0,   927,
       0,  1379,     0,   928,   590,     0,     0,     0,     0,  1080,
     929,   930,     0,  1080,     0,     0,   931,   932,   933,   934,
       0,     0,   936,   937,   938,   939,   940,   941,     0,   942,
       0,   943,   944,     0,     0,     0,   927,     0,     0,     0,
     928,   590,     0,     0,     0,     0,     0,   929,   930,     0,
       0,     0,  1391,   931,   932,   933,   934,     0,   945,   936,
     937,   938,   939,   940,   941,     0,   942,     0,   943,   944,
       0,     0,   945,     0,     0,  1080,   731,  1080,  1080,  1080,
       0,     0,     0,   927,     0,     0,     0,   928,   590,     0,
       0,     0,   945,   731,   929,   930,     0,     0,     0,  1394,
     931,   932,   933,   934,     0,     0,   936,   937,   938,   939,
     940,   941,     0,   942,     0,   943,   944,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1080,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   927,  2291,     0,     0,   928,   590,     0,     0,     0,
    1080,  1080,   929,   930,  1080,     0,     0,  1395,   931,   932,
     933,   934,     0,   945,   936,   937,   938,   939,   940,   941,
       0,   942,     0,   943,   944,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   927,     0,
       0,     0,   928,   590,     0,  1080,   945,     0,     0,   929,
     930,     0,     0,   945,  1429,   931,   932,   933,   934,   945,
       0,   936,   937,   938,   939,   940,   941,     0,   942,     0,
     943,   944,     0,     0,     0,     0,   927,     0,     0,     0,
     928,   590,     0,     0,     0,   945,     0,   929,   930,     0,
       0,     0,  1475,   931,   932,   933,   934,   945,     0,   936,
     937,   938,   939,   940,   941,   945,   942,     0,   943,   944,
       0,     0,     0,     0,     0,   945,     0,     0,   945,     0,
       0,     0,     0,   927,     0,     0,     0,   928,   590,     0,
       0,     0,     0,   945,   929,   930,     0,     0,     0,  1476,
     931,   932,   933,   934,   945,     0,   936,   937,   938,   939,
     940,   941,     0,   942,     0,   943,   944,   927,   945,     0,
       0,   928,   590,     0,   945,     0,     0,     0,   929,   930,
     945,     0,     0,  1586,   931,   932,   933,   934,     0,     0,
     936,   937,   938,   939,   940,   941,     0,   942,   927,   943,
     944,     0,   928,   590,     0,     0,     0,     0,     0,   929,
     930,     0,     0,     0,  1840,   931,   932,   933,   934,     0,
       0,   936,   937,   938,   939,   940,   941,     0,   942,     0,
     943,   944,   927,     0,  1657,     0,   928,   590,     0,     0,
       0,     0,     0,   929,   930,     0,     0,     0,     0,   931,
     932,   933,   934,     0,     0,   936,   937,   938,   939,   940,
     941,     0,   942,     0,   943,   944,     0,   927,     0,     0,
       0,   928,   590,     0,     0,     0,     0,     0,   929,   930,
       0,     0,     0,  1881,   931,   932,   933,   934,     0,   945,
     936,   937,   938,   939,   940,   941,     0,   942,     0,   943,
     944,     0,   927,     0,  1899,     0,   928,   590,     0,     0,
       0,     0,     0,   929,   930,     0,     0,     0,     0,   931,
     932,   933,   934,     0,     0,   936,   937,   938,   939,   940,
     941,     0,   942,   945,   943,   944,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   927,     0,
       0,     0,   928,   945,     0,     0,   945,     0,   945,   929,
     930,     0,   945,     0,     0,   931,   932,   933,   934,     0,
       0,   936,   937,   938,   939,   940,   941,     0,   942,   927,
     943,   944,     0,   928,   590,   945,     0,     0,   945,     0,
     929,   930,     0,     0,     0,  1929,   931,   932,   933,   934,
       0,     0,   936,   937,   938,   939,   940,   941,  1105,   942,
       0,   943,   944,   927,     0,  2078,     0,   928,   590,     0,
       0,     0,     0,     0,   929,   930,     0,     0,     0,     0,
     931,   932,   933,   934,     0,     0,   936,   937,   938,   939,
     940,   941,     0,   942,   927,   943,   944,     0,   928,   590,
       0,     0,     0,     0,     0,   929,   930,     0,     0,     0,
    2133,   931,   932,   933,   934,     0,     0,   936,   937,   938,
     939,   940,   941,     0,   942,   927,   943,   944,     0,   928,
     590,     0,     0,     0,     0,     0,   929,   930,     0,   945,
     945,  2148,   931,   932,   933,   934,     0,   945,   936,   937,
     938,   939,   940,   941,     0,   942,   927,   943,   944,  2160,
     928,   590,     0,     0,     0,     0,     0,   929,   930,     0,
       0,     0,     0,   931,   932,   933,   934,     0,   945,   936,
     937,   938,   939,   940,   941,     0,   942,     0,   943,   944,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   945,
     927,     0,     0,   945,   928,   590,     0,     0,     0,     0,
       0,   929,   930,   945,   945,     0,  2163,   931,   932,   933,
     934,     0,     0,   936,   937,   938,   939,   940,   941,     0,
     942,     0,   943,   944,     0,     0,     0,     0,     0,     0,
       0,   927,     0,     0,   945,   928,   590,     0,     0,     0,
       0,     0,   929,   930,   945,   945,     0,  2222,   931,   932,
     933,   934,     0,     0,   936,   937,   938,   939,   940,   941,
       0,   942,     0,   943,   944,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   945,     0,   945,     0,
       0,     0,     0,     0,     0,   927,     0,     0,     0,   928,
     590,     0,   945,     0,     0,   945,   929,   930,     0,     0,
       0,  2223,   931,   932,   933,   934,     0,   945,   936,   937,
     938,   939,   940,   941,     0,   942,   927,   943,   944,  2237,
     928,   590,     0,     0,     0,     0,     0,   929,   930,     0,
       0,     0,     0,   931,   932,   933,   934,     0,     0,   936,
     937,   938,   939,   940,   941,     0,   942,     0,   943,   944,
       0,     0,   927,     0,     0,     0,   928,   590,     0,     0,
       0,     0,     0,   929,   930,     0,     0,     0,  2244,   931,
     932,   933,   934,     0,   945,   936,   937,   938,   939,   940,
     941,     0,   942,     0,   943,   944,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   945,
       0,   945,     0,     0,     0,   945,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   945,   945,     0,
     945,   927,     0,     0,  2261,   928,   590,     0,     0,     0,
     945,   945,   929,   930,     0,     0,     0,     0,   931,   932,
     933,   934,     0,     0,   936,   937,   938,   939,   940,   941,
       0,   942,     0,   943,   944,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   945,     0,   945,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   945,   945,
       0,   366,   367,   368,   369,     0,   371,     0,   372,     0,
     374,   375,     0,   376,     0,     0,     0,   378,     0,   380,
     381,     0,   945,   383,   384,   385,   945,   387,     0,   389,
     390,     0,     0,   397,     0,     0,   945,     0,   400,   401,
     402,   403,   404,   405,   406,   407,     0,   408,   409,     0,
       0,   414,   415,   416,     0,   418,     0,   420,     0,     0,
     423,   424,     0,     0,     0,     0,     0,     0,   431,   432,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   440,
       0,   442,     0,   443,   444,     0,     0,     0,   449,   450,
     451,     0,     0,   453,     0,     0,   455,   456,     0,   458,
     459,   460,     0,     0,     0,     0,   465,   466,     0,     0,
     468,     0,   470,   471,   472,     0,   474,   475,     0,     0,
     477,     0,   479,   480,   481,   482,   483,   484,     0,     0,
       0,     0,     0,     0,   492,   493,   494,     0,     0,     0,
       0,   499,   500,   501,     0,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,     0,   530,     0,   532,     0,   533,     0,   534,   535,
     536,     0,     0,     0,     0,     0,   542,   543,   544,   545,
     927,     0,     0,  2321,   928,   590,     0,     0,     0,     0,
       0,   929,   930,     0,     0,     9,     0,   931,   932,   933,
     934,     0,    10,   936,   937,   938,   939,   940,   941,     0,
     942,     0,   943,   944,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   617,     0,     0,   630,
       0,   633,    11,    12,    13,    14,     0,    15,    16,    17,
      18,    19,    20,     0,     0,    21,    22,     0,     0,     0,
      23,    24,    25,     0,    26,    27,    28,    29,    30,    31,
       0,    32,    33,    34,    35,    36,    37,     0,    38,    39,
      40,    41,    42,    43,     0,     0,    44,    45,    46,    47,
      48,     0,     0,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,     0,    71,     0,    72,    73,
       0,    74,    75,    76,     0,     0,    77,     0,     0,    78,
      79,     0,    80,    81,    82,    83,     0,    84,    85,    86,
      87,    88,    89,    90,    91,    92,     0,     0,     0,     0,
       0,    93,    94,    95,    96,     0,     0,     0,     0,    97,
       0,     0,    98,    99,     0,     0,   100,   101,     0,   102,
       0,     0,     0,   103,     0,   104,     0,   105,     0,     0,
       0,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     0,   116,   117,   118,     0,   119,     0,   120,   121,
       0,   122,     0,   123,   124,   125,   126,     0,     0,   127,
     128,   129,     0,   130,   131,   132,     0,   133,   134,   135,
       0,   136,     0,   137,   138,   139,   140,   141,     0,   142,
       0,   143,   144,     0,     0,   145,   146,   147,     0,     0,
     148,   149,     0,   150,   151,     0,   152,   153,     0,     0,
       0,   154,   155,     0,     0,   156,     0,     0,   157,     0,
       0,     0,   158,   159,     0,     0,   160,   161,   162,     0,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,   174,     0,     0,   175,     0,     0,     0,   176,
     177,   178,   179,   180,     0,   181,   182,     0,     0,   183,
     184,   185,   186,     0,     0,     0,     0,   187,   188,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,   196,     0,   197,   198,   199,   200,
     201,   202,   927,     0,     0,     0,   928,   590,     0,     0,
       0,     0,     0,   929,   930,     0,     0,     0,  2323,   931,
     932,   933,   934,     0,     0,   936,   937,   938,   939,   940,
     941,     0,   942,     0,   943,   944,   927,     0,   917,   918,
     928,   590,     0,     0,     0,     0,     0,   929,   930,     0,
       0,     0,  2335,   931,   932,   933,   934,     0,     0,   936,
     937,   938,   939,   940,   941,     0,   942,   927,   943,   944,
    2336,   928,   590,     0,     0,     0,     0,     0,   929,   930,
       0,     0,     0,     0,   931,   932,   933,   934,     0,     0,
     936,   937,   938,   939,   940,   941,     0,   942,   927,   943,
     944,  2338,   928,   590,     0,     0,     0,     0,     0,   929,
     930,     0,     0,     0,     0,   931,   932,   933,   934,     0,
       0,   936,   937,   938,   939,   940,   941,     0,   942,   927,
     943,   944,     0,   928,   590,     0,     0,     0,     0,     0,
     929,   930,     0,     0,     0,  2343,   931,   932,   933,   934,
       0,     0,   936,   937,   938,   939,   940,   941,     0,   942,
     927,   943,   944,     0,   928,   590,     0,     0,     0,     0,
       0,   929,   930,     0,     0,     0,  2344,   931,   932,   933,
     934,     0,     0,   936,   937,   938,   939,   940,   941,     0,
     942,   927,   943,   944,  2378,   928,   590,     0,     0,     0,
       0,     0,   929,   930,     0,     0,     0,     0,   931,   932,
     933,   934,     0,     0,   936,   937,   938,   939,   940,   941,
       0,   942,     0,   943,   944,   927,     0,  2393,     0,   928,
     590,     0,     0,     0,     0,     0,   929,   930,     0,     0,
       0,     0,   931,   932,   933,   934,     0,     0,   936,   937,
     938,   939,   940,   941,     0,   942,   927,   943,   944,     0,
     928,   590,     0,     0,     0,     0,     0,   929,   930,     0,
       0,     0,     0,   931,   932,   933,   934,     0,     0,   936,
     937,   938,   939,   940,   941,     0,   942,   927,   943,   944,
       0,   928,     0,     0,     0,     0,     0,     0,   929,   930,
       0,     0,     0,     0,   931,   932,     0,   934,     0,     0,
     936,   937,   938,   939,   940,     0,     0,   942,   927,   943,
     944,     0,   928,     0,     0,     0,     0,     0,     0,   929,
     930,     0,     0,     0,     0,   931,   932,     0,   934,     0,
       0,   936,   937,   938,   939,   940,     0,     0,     0,     0,
     943
};

static const yytype_int16 yycheck[] =
{
      50,   471,   367,   376,   381,   529,   474,   613,  1266,   617,
      62,    63,   390,   733,   251,   364,  1113,    69,   255,   460,
    1295,   901,   400,  1396,   402,   481,   482,   483,   484,   407,
     408,   409,  1418,   628,   377,  1003,  1511,   415,  1513,  1455,
     418,   639,   420,  1535,  1417,   746,    98,   951,   679,   858,
     981,  1541,   419,   455,  1047,   592,   638,   639,  1026,  1541,
    1508,   204,  1451,  1552,   695,  1266,  1565,  1934,   118,  1896,
     726,  1130,   122,   422,   826,   826,   431,    63,  1486,   501,
    1486,   468,  1821,   175,    76,     8,  1826,  1827,  1486,   438,
     191,   456,    43,  1328,   377,   656,  1512,     7,  1486,   950,
     951,   638,   639,   452,  1486,  1486,   182,    99,   457,   116,
     182,  1486,   461,     8,   463,  1561,    67,    71,  1610,     7,
    1566,    47,   957,     7,   116,   169,    15,   476,    15,     0,
       1,    82,   169,   129,   395,   116,    87,    88,     5,   488,
       8,   490,     5,    94,   191,   197,   129,    15,   497,  1142,
       5,     5,   144,     7,     5,    15,     5,    15,     9,    15,
     129,  1484,    15,  1486,   208,  1488,    21,   219,   147,   148,
     166,   226,   227,    21,    37,     8,  1484,   232,  1486,   620,
    1488,   282,  1490,   624,    21,    15,    37,   782,    15,   172,
     631,    58,    15,   824,  2102,    15,     8,   129,  1646,  1647,
    1648,   180,    23,   129,   835,     7,   116,   468,   630,  2416,
    2417,   633,   148,    15,   557,     8,    37,   149,  2126,    86,
      15,   852,  2429,   460,   567,   568,   569,   570,   116,   321,
     791,  1484,   116,  1486,   129,  1488,     5,     8,   282,   315,
     129,   288,   318,   616,   180,   282,   318,    16,    17,    20,
     257,   177,   299,    22,   208,    24,   116,   888,     8,   126,
     149,   129,   149,   251,    33,    15,    35,   255,    37,   129,
     137,   902,     8,   129,   129,   129,   129,   228,   746,   150,
     129,   129,  2021,   116,    20,  1484,  1166,  1486,   571,  1488,
     129,  1490,   129,     8,    41,  2035,  2036,   675,   165,   129,
     673,     8,   129,     8,   116,    20,   129,  1404,   259,   129,
     362,   363,    64,    20,   657,    20,   368,   369,   370,   371,
     707,   373,   374,   116,  1599,   377,  1825,   379,   380,   381,
     382,   254,   800,   385,   129,  1824,   388,   680,   390,  2166,
     781,  1542,  1543,   395,   952,   116,   398,   257,   400,  1584,
     402,  1759,   303,  1759,   406,   407,   408,   409,   780,   990,
     782,  1759,    15,   415,   995,   417,   418,   734,   420,   257,
     965,  1759,   967,   257,   426,   427,  1822,  1759,  1759,   974,
     116,   433,   434,   620,  1759,   437,   257,   624,   246,     8,
     159,   258,   444,   162,   631,   447,   206,   257,    15,   981,
       8,   116,  1333,  1334,  1335,  1036,   793,   459,  1259,   116,
     462,   116,  1164,  1069,  1165,   770,   468,   469,   470,   471,
     406,   473,   474,  1746,   257,  1260,   236,   477,   480,   481,
     482,   483,   484,   776,   486,   423,  1759,   489,  1746,   491,
     492,     8,  1765,   495,   981,   257,   498,     8,    37,    94,
     502,  1759,     3,  1154,   821,  1061,     8,  1765,     8,  1452,
       3,  1769,   209,   451,   257,  1300,  2333,     8,    20,    15,
     458,     8,   460,  1532,  1533,    26,    23,   820,   247,   531,
     823,   228,   532,    26,     7,     8,   257,   537,   538,   539,
      37,   128,     8,  1746,     8,  2322,   898,   116,     8,   551,
       8,   257,   554,   555,   556,   557,  1759,     8,   116,   559,
     562,   563,  1765,     8,   566,   567,   568,   569,   570,  1935,
     157,   257,   574,   575,  2014,   266,   899,   968,   969,   970,
     971,   972,  2014,  2032,  2023,  1924,   305,   306,   307,  1134,
     129,  1376,   257,  2370,   781,    89,   287,  1746,    15,   116,
     257,  1999,   257,     8,     8,   116,   548,   549,  1816,     8,
    1759,    92,    15,  1821,   116,     8,  1765,     8,   560,    23,
    1769,     8,    95,   946,     8,   116,    16,    17,   122,   116,
     217,     7,   129,    37,     8,   230,  1861,    15,   640,   641,
     642,   643,   644,   645,   646,   191,    37,   649,   648,   742,
     116,   124,   116,    37,   128,   657,   116,   662,   116,  1240,
    2058,   155,   208,    37,   191,  1816,   666,     3,   149,    63,
       3,   116,     3,   675,    68,     8,   678,  1258,   680,     3,
       3,   208,   620,   157,    15,    21,   624,    64,   257,   284,
    2139,   185,    15,   631,    18,  1018,    90,    91,   636,   257,
     295,   703,    92,     8,     8,  1028,  1587,  1588,  1589,     3,
       5,   116,   147,   148,     9,   251,    21,   116,     3,   255,
     201,    15,   195,   116,   218,  1273,   728,  2125,   730,   202,
      15,   733,  1402,  1492,  1493,  1494,   282,  1496,  1497,   285,
     257,  1273,    37,   743,   746,   180,   257,     5,     8,     3,
     144,     8,   129,   755,     8,   257,   756,    15,   252,   149,
     154,    21,   764,   763,   766,    18,   257,  1418,  1419,   771,
     257,   773,   149,    26,   776,  1320,  1321,  1322,  1323,  1324,
       5,   968,   969,   970,   971,   972,  1273,   789,  1275,  2231,
      15,   257,     8,   257,     8,  1580,     3,   257,   800,   257,
       8,  1333,  1334,  1335,   806,    21,   200,    21,    15,  1390,
       8,   201,   257,  2021,    15,    16,    17,     8,   820,     8,
       8,   823,     8,    21,  2190,     8,     8,   829,   828,     8,
      21,  2256,   837,    21,    12,    21,   841,  1622,    21,    21,
      18,   846,    21,   781,   849,   850,  1333,  1334,  1335,     5,
      28,     7,   257,    31,     3,  2253,    34,     8,   257,   859,
    1511,  2184,  1513,    41,   257,     8,    15,    45,     8,     8,
      21,    49,  2270,     8,     8,     8,   878,   879,    21,   314,
     315,    21,    21,   318,   319,     8,    21,    21,  2254,    67,
       8,     8,   894,    71,    72,  2380,    16,    17,    21,    77,
      78,    21,   907,    21,   909,    83,    84,  2392,    86,    87,
      88,    89,  2137,    91,   916,  1232,  2252,   917,    84,   857,
     858,   191,   100,     8,   194,    41,     8,   105,   129,   107,
       5,     8,     8,   111,     9,     8,    21,   115,   880,   117,
       8,    16,    17,    15,    21,  1863,   124,  1397,   149,  1399,
     128,    15,  1870,   895,   132,    71,   134,  1811,  1812,  1813,
    1814,  1815,    37,   141,   142,  2331,     8,   145,   146,  1799,
    1263,     8,     8,   151,    84,   153,     8,     7,    22,   157,
      24,     8,     8,     8,  1307,    21,    16,    17,     8,    33,
    1313,    35,  2328,     8,  1309,    21,    21,   999,     8,  1669,
    1000,    21,     7,  1005,  2051,     8,   184,     8,   186,  1011,
    1811,  1812,  1813,  1814,  1815,  1596,     5,     8,    21,   135,
       9,  1579,  1024,     8,     8,   191,     8,    16,    17,    15,
     968,   969,   970,   971,   972,    15,    21,    21,   976,   977,
    1355,   149,   208,  2366,  1695,   191,    15,  1049,    37,    15,
       8,     8,  1054,   169,  1369,  1587,  1588,  1589,   149,  1382,
    1845,     8,   208,    21,    21,  1003,     8,  1395,  1070,    15,
     246,    22,     7,    24,    21,   191,     8,  1077,  1863,    21,
    1661,   191,    33,  1085,    35,  1870,    15,  1872,  1026,    21,
       8,     8,   208,   209,    15,  1385,     8,  1387,   208,   265,
    1587,  1588,  1589,    21,    21,   221,    15,   223,   224,    21,
     226,    15,     8,   229,   158,   159,   282,   161,   162,   285,
    1120,     8,     8,   289,   290,    21,  1064,     8,  1427,     8,
       8,     8,   298,   299,    21,    21,   282,     8,   304,   285,
      21,     8,    21,    21,   290,     8,     8,    15,   192,     5,
      21,     8,   298,     9,    21,   265,     8,    15,    21,    21,
      16,    17,    15,  1163,    21,    21,   282,    23,    15,    21,
    1175,    15,   282,    15,  1473,   285,  1181,     8,   129,   289,
    1185,    37,  1187,  1188,  1189,     8,  1191,     8,  1193,   299,
     234,  2238,  1583,    15,   304,    15,     8,    37,    21,    15,
      21,     5,    15,   247,   320,     9,  1206,   158,   159,    21,
     161,   162,    16,    17,     8,   393,    15,    21,  1218,    23,
       7,     8,     8,  1223,    15,     8,  1226,    21,  1228,  1229,
    1230,  1233,  1234,    37,  1708,    21,  1710,  1711,    21,     8,
       8,   192,    15,    16,    17,     7,     8,   253,  1722,   255,
     256,  1574,    21,    21,    27,  1257,    15,     5,  1732,     7,
    1734,  1263,    10,    36,   440,  1267,    14,    15,    16,    17,
      15,     8,    44,     7,     8,  1598,     8,  1600,   124,    27,
       8,   124,     8,   234,    21,     8,    34,  1843,    36,    21,
    1613,    64,     3,    21,  1617,    21,   247,    15,    21,   475,
      15,     5,   316,   317,  1632,  1850,    10,     8,    15,   485,
      14,    15,    16,    17,     8,    87,    64,    15,   496,    92,
      21,    93,     5,    27,     8,    15,     9,    21,     8,     8,
      34,     7,    36,    16,    17,     8,  1338,    21,    21,     8,
      23,    21,    21,    15,    92,   239,     5,   119,    21,  2134,
       9,   246,    21,   246,    37,    15,   129,    16,    17,     8,
      64,     8,    16,    17,    23,  1370,   542,   543,   544,   545,
      21,   143,    21,   145,    21,  2160,   149,     8,    37,  1542,
    1543,   129,  1384,  1385,    26,  1387,     8,     7,    92,    15,
    1328,   240,     5,  1395,     8,  1397,  1583,  1399,    15,    21,
    1402,   149,    15,    16,    17,    15,   178,    21,    63,   839,
     840,   183,   842,    68,    27,   187,   592,   593,   594,   191,
     596,     8,   194,    36,     8,   129,     8,   603,   201,     8,
       8,  1433,   242,   243,    21,    90,    91,    21,     8,  1444,
    1442,   617,    21,    21,   216,   149,  1448,  2037,  2038,  2039,
    1450,    64,    15,   201,   976,   977,  1458,    15,   230,  1587,
    1588,  1589,   166,    15,   236,   175,    63,   149,  1468,   124,
    1470,    68,  1474,  2412,  2413,  2308,  2309,   847,   848,    92,
       8,    15,     8,   659,     8,    15,     8,     8,    26,   144,
      15,     7,    15,    90,    91,  1495,  1434,   201,   674,   154,
      62,     8,    15,    16,    17,     8,  1506,    21,   287,  1509,
      15,     8,   326,   213,    27,     8,   129,    15,     8,    64,
    1522,     9,   129,    36,     9,    44,   702,  1527,     8,  1529,
      21,     8,     8,   709,    15,  2186,   149,    37,  1476,   715,
     716,    15,    15,    15,    15,   200,    59,   144,    15,  1864,
    1552,    64,    67,    15,  1492,  1493,  1494,   154,  1496,  1497,
      15,     8,  1500,  1565,     8,    26,     7,    15,    87,  1868,
    1508,     7,   129,    37,    26,    21,    21,     7,   233,    92,
      18,    21,  1584,    15,   760,  1587,  1588,  1589,   201,   244,
       7,    15,     8,    15,     8,  1597,     8,    26,    21,  2155,
     119,  2252,    21,   200,  2255,  2256,     5,    15,  1935,    15,
       9,    10,    15,    15,    15,    14,    15,    16,    17,    15,
       8,    21,    15,    21,   143,    15,   145,     5,    27,    15,
    1632,    15,    15,    15,   231,    34,   149,    36,    15,    15,
      21,    62,     8,     7,    15,  1583,  1584,   244,     8,     8,
    1652,     8,     8,    15,  2305,   255,   832,   833,     7,   178,
     166,    15,    15,   239,   183,    64,    21,  1669,   187,    16,
      15,    15,   191,   208,     8,   194,  2327,  2328,    21,     7,
      15,   334,  2102,   315,    15,   335,     7,   246,   201,  2012,
     246,   246,   246,    92,     5,   246,     8,   216,    15,  2022,
    1702,  1703,    15,    21,     8,    21,     7,    21,  1646,  1647,
    1648,   230,    21,    21,     8,     5,    26,   236,   896,     9,
      10,  2372,    15,    21,   173,  1727,    16,    17,     8,    15,
     129,    15,    22,    23,    24,    25,    26,   255,    28,    29,
      30,    31,    32,    33,     8,    35,     7,    37,    38,    21,
     149,   927,   928,   929,   930,   931,   932,   933,   934,   935,
     936,   937,   938,   939,   940,   941,   942,   943,   944,   945,
    2176,  2177,    15,    15,   208,    71,   952,    18,     8,    15,
      15,   957,     5,    15,    15,     9,     5,    10,   964,    15,
     966,    14,    15,    16,    17,     8,    15,    16,    17,    21,
      21,    21,   201,    21,    27,   981,    21,    15,    27,    15,
      21,    34,    21,    36,    15,     5,    15,    36,   996,     7,
      20,    26,  1824,  1825,  1826,  1827,    21,    21,    21,    21,
      21,  1007,    15,    18,  2252,  1837,  2254,  1013,    15,    21,
      21,    64,  2157,     8,    15,    64,   423,    26,    26,     5,
       7,     7,    15,  1029,    10,    21,    15,    26,    14,    15,
      16,    17,     8,    21,    15,  1867,    21,   254,    21,    92,
      15,    27,     8,    92,   451,   132,     7,    21,    34,     7,
      36,   458,    21,  1883,    21,    37,     7,     5,   396,   466,
       7,    21,    10,    15,    21,    15,    14,    15,    16,    17,
      15,    15,    15,   255,  1904,    15,   129,    15,    64,    27,
     129,    15,    15,    15,     7,    21,    34,  1919,    36,     8,
       8,  1923,    40,  1925,     7,  1863,   149,    21,     8,     7,
     149,    21,  1870,  1935,    15,     7,    92,  1113,     7,  1941,
    1942,    15,    21,   166,    78,     8,    64,     7,  1948,     7,
      21,    15,    17,   333,     5,    21,  1132,  1957,    15,    10,
       8,    17,    15,    14,    15,    16,    17,     7,     7,    15,
       7,   217,   879,   129,    92,  1975,    27,   887,   201,  1155,
    1156,   128,   201,    34,  1234,    36,  1921,  1796,  1531,  1527,
    1167,   565,  1073,   149,  1994,   572,  2134,  1797,   573,   507,
     693,   509,  1265,   576,  1561,   916,  2139,  2034,   516,   517,
     518,   129,  1824,    64,   522,   523,   524,   525,   916,   527,
     528,  2023,  1816,  2014,  1458,  1137,  1670,  2084,  1919,  1442,
    2032,   149,  2034,  2035,  2036,  2037,  2038,  2039,  2104,  1942,
    1379,    92,  1009,  1357,  1643,   201,  1029,  1071,  1645,    75,
    1845,  2418,  1863,   694,   451,  1870,  1365,   241,  1402,   636,
       5,  1999,   774,  1241,     9,  2065,   241,   241,   241,  1018,
      15,    16,    17,  1580,  1583,   981,   640,  1054,   129,   819,
     645,  1085,    27,   201,  1260,  1156,  2185,  1383,  1381,   642,
    2064,    36,  2370,   643,     5,   644,  1272,  1923,   149,    10,
    2102,  2103,  2104,    14,    15,    16,    17,  2238,   789,   999,
    2346,  1070,   997,  1867,  1011,  2289,    27,  1439,  1906,    64,
    2058,  1024,  2251,    34,  1300,    36,  2372,  2394,  2414,  2416,
    2193,  1695,   649,  1926,   492,  1456,  1312,  2139,  1419,   744,
    1872,   404,   371,  1506,  1930,  2166,  1746,    92,  1765,     5,
     201,   728,  1726,    64,    10,  1721,  1769,  1759,    14,    15,
      16,    17,  2217,  1955,  1954,  1206,  1218,  1223,  1975,   746,
      -1,    27,  1226,    -1,  2176,  2177,    -1,    -1,    34,    -1,
      36,    92,   759,  2185,   129,    -1,  2124,  2125,  1364,  1365,
     767,   768,    -1,    -1,    -1,   772,    -1,    -1,    45,    46,
      -1,    48,    49,  1379,   149,    -1,    53,    -1,    64,    -1,
    1386,    -1,    -1,    -1,    61,    -1,    -1,    -1,   129,    66,
    1396,   166,    69,   800,    -1,    -1,  1402,    -1,  1404,    -1,
      77,   808,    79,    -1,    81,    -1,    92,    -1,   149,    -1,
    2242,  1417,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2252,    -1,  2254,    -1,  1430,    -1,   201,   104,    -1,   836,
      -1,   838,    -1,    -1,    -1,  1441,  2266,    -1,   115,    -1,
      -1,    -1,    -1,   129,    -1,    -1,  2278,  2277,  1454,    -1,
     857,   858,    -1,  1459,    -1,  1461,   794,    -1,    -1,     5,
     201,    -1,   139,   149,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    -1,    -1,    -1,   152,    -1,    -1,  2308,  2309,
      -1,    27,    -1,    -1,    -1,  2253,    -1,    -1,    34,    -1,
      36,    -1,    -1,   170,    -1,    -1,    -1,    -1,    -1,   176,
      -1,    -1,  2270,    -1,    -1,    -1,    -1,   184,  2276,   186,
      -1,   188,    -1,   190,  2346,   201,  2348,    -1,    64,    -1,
     197,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
      -1,  1537,    -1,     9,    -1,    -1,    -1,   214,   215,    15,
      16,    17,    -1,   950,   951,    -1,    92,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    -1,   232,    -1,    -1,    -1,    -1,
      36,    -1,   239,    -1,    -1,    -1,  2396,    -1,    -1,   976,
     977,  2401,  1578,  1579,  1580,    -1,   253,    -1,    -1,   256,
      -1,    -1,    -1,   129,  2414,    -1,  2416,  2417,    64,    45,
      46,    -1,    48,    49,    -1,    -1,  1003,    53,  1604,  2429,
      -1,    -1,    -1,   149,    -1,    61,  1612,    -1,    -1,  1615,
      66,    -1,    -1,    69,    -1,    -1,    92,  1623,    -1,  1026,
      -1,    77,    -1,    79,    -1,    81,    -1,     7,    -1,    -1,
      10,    -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,   104,  1655,
      -1,  1657,    -1,   129,    34,   201,    36,  1064,    -1,   115,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     7,   152,    -1,    10,  1037,
      -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
    1048,    -1,    92,    -1,   170,    27,    -1,    -1,    -1,    -1,
     176,    -1,    34,    -1,    36,   201,    -1,    -1,   184,    -1,
     186,    -1,   188,    -1,   190,    -1,    -1,    -1,    -1,    -1,
      -1,   197,    -1,    -1,    -1,    -1,    -1,  1154,    -1,   129,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,   214,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
      -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,
      92,    -1,    -1,    -1,  1790,  1791,   166,    -1,    -1,    -1,
      -1,    -1,  1798,    -1,    -1,    -1,    -1,   253,    -1,    -1,
     256,    -1,     7,  1141,    -1,    10,    -1,    -1,    -1,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,   129,    -1,    -1,
      -1,   201,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    36,    -1,  1839,    -1,    -1,  1174,   149,    -1,  1845,
      -1,    -1,  1180,    -1,    -1,    -1,  1184,    -1,  1186,    -1,
      -1,    -1,  1190,     7,  1192,    -1,    10,  1264,    -1,    64,
      14,    15,    16,    17,    -1,    -1,    -1,  1873,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,  1882,    -1,    -1,    -1,
      34,    -1,    36,    -1,    -1,    -1,    -1,    92,     7,   201,
      -1,    10,    -1,  1899,  1900,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    27,    -1,
      64,     9,    -1,    -1,    -1,    34,    -1,    36,    16,    17,
    1926,  1328,    -1,    -1,   129,    23,    -1,    25,  1934,    -1,
      28,    29,    30,    31,    32,    -1,    -1,  1943,    92,    37,
      -1,    -1,    -1,    -1,   149,    64,    -1,    -1,    -1,     7,
      -1,    -1,    10,  1959,    -1,  1961,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    92,    -1,   129,    34,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1397,    -1,  1399,    -1,    -1,   149,   201,    -1,    10,    -1,
      -1,   604,    14,    15,    16,    17,    64,    -1,    -1,    -1,
     129,  1418,  1419,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,  1428,    34,    -1,    36,    -1,    -1,  1434,    -1,  1436,
     149,    -1,  1439,    -1,    92,    -1,    -1,    -1,    -1,    -1,
    2046,    -1,    -1,    -1,  1451,  2051,    -1,   201,  1455,  1456,
      -1,    -1,    64,    -1,  1392,    -1,    -1,    -1,  2064,    -1,
      -1,    -1,  2068,    -1,    -1,    -1,    78,    -1,    -1,  1476,
      -1,   129,  2078,    -1,    -1,    -1,  1483,  2083,    -1,    -1,
      92,    -1,   201,    -1,    -1,  1492,  1493,  1494,    -1,  1496,
    1497,   149,    -1,  1500,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1508,  1440,    10,  1511,  1512,  1513,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    34,  2134,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,    -1,
      -1,  1479,    -1,   201,  1482,  1552,    -1,  1485,    -1,  1487,
     753,  1489,    -1,  1491,   757,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    10,  2169,    -1,    -1,    14,    15,    16,    17,
      -1,    -1,     5,    -1,    -1,    -1,     9,  1584,  2184,    27,
      -1,    -1,    -1,    16,    17,    92,    34,    -1,    36,   201,
      23,    -1,    25,    -1,    -1,    28,    29,    30,    31,    32,
      -1,   804,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   815,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2237,  2238,    -1,    -1,  2241,    -1,  2243,    -1,  1646,
    1647,  1648,   149,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2259,  2260,  2261,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2271,    -1,    -1,    -1,    -1,
    2276,   874,   875,   876,   877,    -1,    -1,    -1,    -1,    -1,
       5,   129,     7,  2289,     9,    10,    -1,    -1,  1695,    -1,
      -1,    16,    17,    -1,   201,    -1,    21,    22,    23,    24,
      25,   149,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,  2321,  2322,    -1,   921,    -1,
     923,   924,   925,   926,     5,    -1,     7,  2333,     9,    10,
    2336,    -1,  2338,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,   201,    35,    -1,    37,    38,    -1,    -1,
    2366,    -1,    -1,    -1,  2370,    -1,    -1,    -1,  2374,    -1,
      -1,    -1,  2378,    -1,  2380,    -1,    -1,    -1,    -1,   982,
    1718,    -1,    -1,    -1,    -1,  1723,  2392,  2393,  2394,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1736,    -1,
      -1,  1004,    -1,    -1,  1811,  1812,  1813,  1814,  1815,    -1,
      -1,  1014,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
    1758,     9,    10,    -1,    -1,    -1,  1764,    -1,    16,    17,
    1768,    -1,  1035,    -1,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,  1051,    37,
      38,    -1,  1055,  1056,     5,    -1,  1863,     8,     9,    10,
      -1,    -1,    -1,  1870,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,     5,    -1,
      -1,     8,     9,    10,    -1,    -1,  1903,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,  1112,
      -1,    28,    29,    30,    31,    32,    33,  1924,    35,     5,
      37,    38,     8,     9,    10,    -1,    -1,    -1,  1935,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,  1955,    35,
      -1,    37,    38,     5,    -1,    -1,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,  1170,  1171,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,  1999,  2000,  1932,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1945,    -1,    -1,
      -1,    -1,  1950,    -1,    -1,  1953,  2023,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1963,    -1,  1965,    -1,  1967,
      -1,  1969,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,     9,    10,    -1,    -1,    -1,    -1,  2055,    16,
      17,  2058,    -1,  2060,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,  1276,  1277,  1278,  1279,  1280,  1281,  1282,
    1283,  1284,  1285,  1286,  1287,  1288,  1289,  1290,  1291,  1292,
    1293,  1294,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1310,    -1,    -1,
      -1,    -1,    -1,    -1,  1317,    -1,  1319,  2124,  2125,     5,
      -1,     7,    -1,     9,    10,    -1,  1329,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,    -1,    -1,    -1,  1359,    -1,    -1,    -1,
    1363,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
      -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,  2186,
      16,    17,    -1,  2190,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,    -1,    -1,    -1,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,  1431,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,  1445,    -1,    -1,  2252,  2253,  2254,  2255,  2256,
      -1,    -1,    -1,     5,    -1,    -1,    -1,     9,    10,    -1,
      -1,    -1,  1465,  2270,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2305,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,  2250,    -1,    -1,     9,    10,    -1,    -1,    -1,
    2327,  2328,    16,    17,  2331,    -1,    -1,    21,    22,    23,
      24,    25,    -1,  1536,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,     9,    10,    -1,  2372,  1569,    -1,    -1,    16,
      17,    -1,    -1,  1576,    21,    22,    23,    24,    25,  1582,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,  1608,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,  1620,    -1,    28,
      29,    30,    31,    32,    33,  1628,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,  1638,    -1,    -1,  1641,    -1,
      -1,    -1,    -1,     5,    -1,    -1,    -1,     9,    10,    -1,
      -1,    -1,    -1,  1656,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,  1667,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,     5,  1681,    -1,
      -1,     9,    10,    -1,  1687,    -1,    -1,    -1,    16,    17,
    1693,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,     5,    -1,    -1,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,  1802,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,  1846,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,     9,  1866,    -1,    -1,  1869,    -1,  1871,    16,
      17,    -1,  1875,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,    -1,     9,    10,  1898,    -1,    -1,  1901,    -1,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,  1921,    35,
      -1,    37,    38,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,     5,    37,    38,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,  2002,
    2003,    21,    22,    23,    24,    25,    -1,  2010,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,  2041,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2062,
       5,    -1,    -1,  2066,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,  2076,  2077,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,  2107,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,  2117,  2118,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2149,    -1,  2151,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,
      10,    -1,  2165,    -1,    -1,  2168,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,  2180,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,  2247,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2282,
      -1,  2284,    -1,    -1,    -1,  2288,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2300,  2301,    -1,
    2303,     5,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,
    2313,  2314,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2347,    -1,  2349,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2361,  2362,
      -1,    14,    15,    16,    17,    -1,    19,    -1,    21,    -1,
      23,    24,    -1,    26,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,  2385,    36,    37,    38,  2389,    40,    -1,    42,
      43,    -1,    -1,    46,    -1,    -1,  2399,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    -1,
      -1,    64,    65,    66,    -1,    68,    -1,    70,    -1,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      -1,    94,    -1,    96,    97,    -1,    -1,    -1,   101,   102,
     103,    -1,    -1,   106,    -1,    -1,   109,   110,    -1,   112,
     113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
     123,    -1,   125,   126,   127,    -1,   129,   130,    -1,    -1,
     133,    -1,   135,   136,   137,   138,   139,   140,    -1,    -1,
      -1,    -1,    -1,    -1,   147,   148,   149,    -1,    -1,    -1,
      -1,   154,   155,   156,    -1,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,    -1,   185,    -1,   187,    -1,   189,    -1,   191,   192,
     193,    -1,    -1,    -1,    -1,    -1,   199,   200,   201,   202,
       5,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,     6,    -1,    22,    23,    24,
      25,    -1,    13,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   249,    -1,    -1,   252,
      -1,   254,    43,    44,    45,    46,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    -1,    65,    66,    67,    68,    69,    70,
      -1,    72,    73,    74,    75,    76,    77,    -1,    79,    80,
      81,    82,    83,    84,    -1,    -1,    87,    88,    89,    90,
      91,    -1,    -1,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,   117,    -1,   119,   120,
      -1,   122,   123,   124,    -1,    -1,   127,    -1,    -1,   130,
     131,    -1,   133,   134,   135,   136,    -1,   138,   139,   140,
     141,   142,   143,   144,   145,   146,    -1,    -1,    -1,    -1,
      -1,   152,   153,   154,   155,    -1,    -1,    -1,    -1,   160,
      -1,    -1,   163,   164,    -1,    -1,   167,   168,    -1,   170,
      -1,    -1,    -1,   174,    -1,   176,    -1,   178,    -1,    -1,
      -1,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,    -1,   193,   194,   195,    -1,   197,    -1,   199,   200,
      -1,   202,    -1,   204,   205,   206,   207,    -1,    -1,   210,
     211,   212,    -1,   214,   215,   216,    -1,   218,   219,   220,
      -1,   222,    -1,   224,   225,   226,   227,   228,    -1,   230,
      -1,   232,   233,    -1,    -1,   236,   237,   238,    -1,    -1,
     241,   242,    -1,   244,   245,    -1,   247,   248,    -1,    -1,
      -1,   252,   253,    -1,    -1,   256,    -1,    -1,   259,    -1,
      -1,    -1,   263,   264,    -1,    -1,   267,   268,   269,    -1,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,    -1,   283,    -1,    -1,   286,    -1,    -1,    -1,   290,
     291,   292,   293,   294,    -1,   296,   297,    -1,    -1,   300,
     301,   302,   303,    -1,    -1,    -1,    -1,   308,   309,   310,
     311,   312,   313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   322,   323,   324,   325,    -1,   327,   328,   329,   330,
     331,   332,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,     5,    -1,   581,   582,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,     5,    37,    38,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      38,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,     5,    -1,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,     5,    37,    38,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    -1,    25,    -1,    -1,
      28,    29,    30,    31,    32,    -1,    -1,    35,     5,    37,
      38,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    -1,    25,    -1,
      -1,    28,    29,    30,    31,    32,    -1,    -1,    -1,    -1,
      37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   339,     0,     1,   150,   257,   340,   341,   116,     6,
      13,    43,    44,    45,    46,    48,    49,    50,    51,    52,
      53,    56,    57,    61,    62,    63,    65,    66,    67,    68,
      69,    70,    72,    73,    74,    75,    76,    77,    79,    80,
      81,    82,    83,    84,    87,    88,    89,    90,    91,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   117,   119,   120,   122,   123,   124,   127,   130,   131,
     133,   134,   135,   136,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   152,   153,   154,   155,   160,   163,   164,
     167,   168,   170,   174,   176,   178,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   193,   194,   195,   197,
     199,   200,   202,   204,   205,   206,   207,   210,   211,   212,
     214,   215,   216,   218,   219,   220,   222,   224,   225,   226,
     227,   228,   230,   232,   233,   236,   237,   238,   241,   242,
     244,   245,   247,   248,   252,   253,   256,   259,   263,   264,
     267,   268,   269,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   283,   286,   290,   291,   292,   293,
     294,   296,   297,   300,   301,   302,   303,   308,   309,   310,
     311,   312,   313,   322,   323,   324,   325,   327,   328,   329,
     330,   331,   332,   342,   344,   347,   359,   360,   364,   365,
     366,   372,   373,   374,   375,   377,   378,   380,   382,   383,
     384,   385,   392,   393,   394,   395,   396,   397,   401,   402,
     403,   407,   408,   446,   448,   461,   504,   505,   507,   508,
     514,   515,   516,   517,   524,   525,   526,   527,   529,   532,
     536,   537,   538,   539,   540,   546,   547,   548,   559,   560,
     561,   563,   566,   569,   574,   575,   577,   579,   581,   584,
     585,   609,   610,   621,   622,   623,   624,   629,   632,   635,
     638,   639,   687,   688,   689,   690,   691,   692,   693,   694,
     700,   702,   704,   706,   708,   709,   710,   711,   712,   715,
     717,   718,   719,   722,   723,   727,   728,   730,   731,   732,
     733,   734,   735,   738,   743,   748,   750,   751,   752,   753,
     754,   755,   756,   757,   774,   777,   778,   779,   780,   786,
     789,   794,   795,   796,   799,   800,   801,   802,   803,   804,
     805,   806,   807,   808,   809,   810,   811,   812,   813,   818,
     819,   820,   821,   822,   832,   833,   834,   835,   836,   837,
     838,   839,    15,   471,   471,   533,   533,   533,   533,   533,
     471,   533,   533,   343,   533,   533,   533,   471,   533,   471,
     533,   533,   471,   533,   533,   533,   470,   533,   471,   533,
     533,     7,    15,   472,    15,   471,   592,   533,   471,   356,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     129,   349,   513,   513,   533,   533,   533,   471,   533,   349,
     533,   471,   471,   533,   533,   470,   343,   471,   471,    64,
     355,   533,   533,   471,   471,   471,   471,   471,   471,   471,
     533,   410,   533,   533,   533,   349,   447,   343,   471,   533,
     533,   533,   471,   533,   471,   533,   533,   471,   533,   533,
     533,   471,   343,   471,   356,   533,   533,   356,   533,   471,
     533,   533,   533,   471,   533,   533,   471,   533,   471,   533,
     533,   533,   533,   533,   533,    15,   471,   570,   471,   343,
     471,   471,   533,   533,   533,    15,     8,   471,   471,   533,
     533,   533,   471,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   471,
     533,   471,   533,   533,   533,   533,   533,    15,    15,    15,
     349,   851,   533,   533,   533,   533,   257,   558,   124,   233,
     380,    15,   352,   558,     8,     8,     8,     8,     7,     8,
     124,   344,   367,     8,   349,   381,     8,     8,     8,     8,
       8,   528,     8,   528,     8,     8,     8,     8,   528,   558,
       7,   218,   252,   505,   507,   516,   517,   239,   525,   525,
      10,    14,    15,    16,    17,    27,    34,    36,    64,    92,
     149,   201,   349,   361,   477,   478,   480,   481,   482,   483,
     489,   490,   491,   492,   493,   496,    15,   533,     5,     9,
      15,    16,    17,   129,   479,   481,   489,   542,   556,   557,
     533,    15,   542,   533,     5,   541,   542,   557,   542,     8,
       8,     8,     8,     8,     8,     8,     8,     7,     8,     8,
       5,     7,   349,   619,   620,   349,   612,   472,    15,    15,
     149,   460,   349,   349,   720,   721,     8,   349,   636,   637,
     721,   349,   351,   349,    15,   509,   554,    23,    37,   349,
     399,   400,    15,   349,   582,   349,   651,   651,   349,   633,
     634,   349,   512,   409,    15,   349,   562,   149,   726,   512,
       7,   455,   456,   471,   593,   594,   349,   588,   594,    15,
     534,   349,   564,   565,   512,    15,    15,   512,   726,   513,
     512,   512,   512,   512,   349,   512,   352,   512,    15,   404,
     472,   480,   481,    15,   346,   349,   349,   630,   631,   462,
     463,   464,   465,     8,   652,   716,    15,   349,   576,   349,
     567,   568,    15,    15,   349,   472,    15,   477,   729,    15,
      15,   349,   703,   705,     8,   349,    37,   398,    15,   481,
     482,   472,    15,    15,   534,   460,   472,   481,   349,   695,
       5,    15,   556,   557,   472,   349,   350,   472,   555,    15,
     480,   613,   614,   588,   592,   349,   580,   349,   675,   675,
      15,   349,   578,   695,   477,   488,   472,   356,    15,   349,
     681,   681,   681,   681,   681,   477,   571,   572,   349,   573,
     472,   345,   349,   472,   349,   701,   703,   349,   471,   472,
     349,   449,    15,    15,   555,   349,    15,   594,    15,   594,
     594,   594,   594,   760,   816,   594,   594,   594,   594,   594,
     594,   760,   349,   356,   823,   824,   825,    15,    15,    15,
     356,   840,   841,   842,   843,   356,   844,   845,   846,   847,
     848,   356,   849,   850,   477,   477,   477,   477,   343,   343,
     124,     5,    21,   349,   353,   354,   348,   356,   349,   349,
     349,   400,     7,   356,   343,   124,   349,   349,     5,    15,
     387,   388,   349,   400,   400,   400,   400,   399,   480,   398,
     349,   349,   404,   411,   412,   414,   415,   533,   533,   239,
     390,   477,   478,   477,   477,   477,   477,     5,     9,    16,
      17,    22,    23,    24,    25,    26,    28,    29,    30,    31,
      32,    33,    35,    37,    38,   361,    15,   246,     3,    15,
     246,   246,    15,   486,   487,    21,   530,   554,   488,     5,
       9,   166,   543,   544,   545,   556,    26,   556,     5,     9,
      23,    37,   479,   555,   556,   555,     8,    15,   481,   549,
     550,    15,   477,   478,   493,   551,   552,   553,   551,   562,
     349,   576,   578,   580,   582,   349,     7,   356,   701,     8,
      21,   614,   400,   502,   477,   240,   528,    15,   356,    15,
     454,     8,   554,     7,   477,   510,   511,   512,    15,   349,
     454,   400,   459,   460,     8,   411,   502,   454,    15,     8,
      21,     5,     7,   457,   458,   477,   349,     8,    21,     5,
      58,    86,   126,   137,   165,   258,   595,   591,   592,   175,
     583,   477,   149,   523,     8,   477,   477,   348,   349,   405,
     406,   480,   485,   349,    26,   349,   518,   519,   521,   352,
       8,     8,    15,   231,   380,   466,   356,     8,   716,   349,
     480,   685,   695,   713,   714,     8,    26,     5,     9,    16,
      17,    22,    23,    24,    25,    28,    29,    30,    31,    32,
      33,    34,    35,    37,    38,   361,   362,   363,   349,   356,
     370,   480,   477,    15,   356,   349,   349,   480,   480,   503,
       8,   652,   707,   349,   480,   640,   641,   349,   444,   445,
     523,   400,    18,   555,   556,   555,   376,   379,   619,   614,
       7,   592,   594,   685,   695,   696,   697,   399,   400,   438,
     439,    62,   480,   739,    15,     7,     8,    21,   570,   400,
     352,   400,   454,     8,   650,   672,    21,   356,   349,     8,
     477,   477,   454,   480,   528,   781,   480,   287,   793,   793,
     528,   790,   793,    15,   528,   758,   528,   797,   758,   758,
     528,   775,   528,   787,   454,   147,   148,   180,   314,   315,
     318,   319,   357,   826,   827,   828,     8,    21,   481,   656,
     829,    21,   829,   356,   736,   737,   191,   208,     8,    21,
      41,   209,   228,     8,    21,   326,     8,    21,     8,     8,
       8,   349,   345,   343,     8,    21,   213,   357,   454,    44,
      87,    93,   119,   143,   145,   178,   183,   187,   191,   194,
     216,   230,   236,   368,   369,   371,   349,   343,   471,   534,
     554,   381,   454,   528,   528,     8,    37,    15,   349,   417,
     422,   356,    15,   497,    21,     8,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   554,    64,   129,   473,   475,
     554,   480,   491,   494,    64,   494,   488,     8,    21,     5,
     477,   531,   545,     8,    21,     5,     9,   477,    21,   477,
     556,   556,   556,   556,   556,    21,   549,   549,     8,   477,
     478,   552,   553,     8,     8,     8,   454,   454,   471,    43,
      67,    82,    87,    88,    94,   228,   259,   303,   623,   620,
     356,   480,   483,   484,   500,    21,   349,    15,   476,   477,
      67,   455,   637,   477,     7,     8,    21,   530,    37,     8,
      21,   634,   480,   483,   499,   501,   554,   724,   457,     7,
     454,   594,    15,    15,    15,    15,    15,    15,   583,   594,
     349,    21,   535,   565,    21,    21,    15,     8,    21,     8,
     487,   481,     8,   520,    26,   348,   631,   463,   129,   467,
     468,   469,   385,   169,   208,   282,   356,    15,     7,     8,
      21,   568,    21,    21,   147,   148,   180,    21,    18,    21,
       7,   477,   495,   175,   321,    37,     8,    21,   356,     8,
      21,    26,     8,    21,   535,   477,    21,   440,   441,   440,
      21,     7,   594,   583,    15,     7,     8,    21,     8,    15,
      15,    26,   682,   683,   685,   477,   572,   356,     8,   672,
       8,   650,   381,   371,   358,    21,    21,    21,   594,   528,
      21,   594,   528,   817,   594,   528,   594,   528,   594,   528,
     594,   528,    15,    15,    15,    15,    15,    15,   356,   825,
       8,    21,    21,   182,   315,   318,     8,    21,    15,    15,
     841,    15,    15,    15,   845,   850,   356,   356,   356,   352,
     349,   354,    15,   386,   387,   454,   471,    15,     7,     8,
     349,   454,    15,   491,     5,   389,   477,   545,   400,   480,
     414,    15,    16,    17,    27,    36,    59,    64,    92,   149,
     201,   413,   415,   425,   426,   427,   428,   429,   430,   431,
     432,   417,   422,   423,   424,    15,   418,   419,    62,   477,
     551,   478,   473,    21,     8,   474,   477,   495,   545,     7,
     554,   460,   477,   554,     8,   550,    21,     8,     8,     8,
     478,   553,   478,   553,   478,   553,   349,   255,    15,    15,
       8,    21,   460,   459,     8,    21,     7,    21,   477,   510,
      21,   460,   528,     8,    21,   545,   725,     8,    21,   458,
     477,   595,   554,    15,   597,   349,   596,   596,   477,   596,
     454,   594,   239,   512,   476,   406,   406,   349,   477,   519,
      21,   477,   495,     8,    21,    16,    15,    15,    15,   476,
     713,   714,   472,   480,   744,     7,   477,     7,    21,    21,
     349,   590,   481,   480,   641,   594,   642,   477,   445,   528,
       8,    47,   177,   349,   443,   356,   611,   613,   583,     7,
       7,   477,   698,   699,   696,   697,   439,   477,     5,   597,
     740,   741,   747,   477,   607,     8,    21,    15,    71,   208,
     356,   356,   472,   172,   349,   452,   453,   481,   191,   208,
     282,   285,   290,   298,   761,   762,   763,   770,   782,   783,
     784,   594,   266,   791,   792,   793,   594,    37,   480,   814,
     815,    84,   265,   289,   299,   304,   759,   761,   762,   763,
     764,   765,   766,   768,   769,   770,   594,   761,   762,   763,
     764,   765,   766,   768,   769,   770,   783,   784,   798,   594,
     761,   762,   763,   770,   776,   594,   761,   762,   788,   594,
     829,   829,   829,   356,   830,   831,   829,   829,   481,   737,
     656,   356,   676,   682,   696,   682,   334,   315,   335,   349,
      18,    26,   391,    15,   370,     7,   356,   386,   535,   535,
     390,     5,   477,   428,   429,   430,   433,   429,   431,   429,
     431,   246,   246,   246,   246,   246,     8,    37,   349,   416,
     480,     5,   418,   419,     8,    15,    16,    17,   149,   349,
     416,   420,   421,   434,   435,   436,   437,    15,   419,    15,
      21,   498,    21,    21,   487,   554,   477,   488,   531,   544,
     556,   521,   522,   478,   522,   522,   522,   454,   349,   615,
     618,   554,   473,   554,     8,    21,   477,     7,   390,   477,
     554,   477,   554,   545,   608,   477,   598,   599,    21,    21,
      21,    21,     8,     8,   254,   506,   512,    21,   468,   469,
     656,   656,   656,    21,    21,   349,    15,    21,   477,     7,
       7,   477,   454,   173,     8,   646,   647,   648,   649,   650,
     652,   653,   654,   657,   658,   659,   672,   680,   521,   441,
      15,    15,   442,   255,     8,     7,     8,    21,    21,    21,
       8,    21,    21,   683,   684,    15,    15,   349,   349,   450,
     451,    18,     8,    26,   760,    15,   760,   760,    15,   594,
     782,   760,   594,   791,   349,     8,    21,    15,   760,    15,
     760,    15,   594,   759,   594,   798,   594,   776,   594,   788,
      21,    21,    21,   316,   317,     8,    21,    21,    21,    21,
      22,    24,    33,    35,   158,   159,   161,   162,   192,   234,
     247,   677,   678,   679,     8,    21,    21,    21,    21,    15,
      15,    21,   477,   477,   625,   626,    21,   369,   391,     5,
     477,   381,     8,    21,     8,   494,   494,   494,   494,   494,
     425,     5,    15,   415,   426,   419,   349,   416,   424,   434,
     435,   435,     8,    21,     7,    16,    17,     5,    37,     9,
     434,   477,    20,   487,   474,    21,    26,    21,    21,    21,
      21,    15,   473,    21,   484,   545,   460,   636,   472,   499,
     545,   725,   477,    21,     8,    21,   477,   356,    15,    21,
      21,    21,     7,   745,   746,   747,   477,   477,     7,   480,
     643,   356,   648,    26,   443,    26,   362,   615,   613,   349,
     586,   587,   588,   589,   699,   741,   594,    78,   571,   349,
     651,   696,   673,    18,     8,   349,   453,   477,   594,   771,
     356,   594,   594,   816,   480,   814,   356,   477,   477,   594,
     594,   594,   594,   831,    15,    15,   356,   656,   480,     8,
      21,     7,    21,    21,   554,   433,   426,   554,   416,    26,
      21,   434,   421,   435,   435,   436,   436,   436,    21,   477,
       5,   477,   495,   616,   617,    21,   480,     8,   656,   480,
       8,   599,   356,    21,   254,   477,     8,    21,   477,    15,
      41,   135,   191,   209,   221,   223,   224,   226,   229,   320,
     477,   442,    21,    21,    15,     8,   132,   742,    21,    21,
       7,    21,   675,   677,   349,   451,     5,    16,    17,    22,
      24,    33,    35,    37,   159,   162,   247,   305,   306,   307,
     773,    21,    94,   230,   284,   295,   785,    37,   191,   288,
     299,   767,    21,    21,   481,   656,   677,    21,    21,     7,
       7,   389,    21,   473,   420,   434,    21,     8,     8,    21,
     460,   545,   255,    15,    21,   746,     5,   477,   644,   645,
      15,   660,    15,    15,    15,    15,    15,   681,   681,    15,
      15,     8,   476,   587,   685,   686,    15,   696,   674,   674,
       7,     8,    21,   817,    21,    21,     8,     8,     7,   390,
      21,    21,   477,   617,   477,   349,   600,   601,   477,     8,
      21,   594,   660,   695,   713,   656,   695,   696,   685,   682,
     477,   477,   655,   477,    21,     8,   356,    21,     7,     8,
      21,   656,   772,   477,   477,   481,   356,   349,   627,   628,
      21,     8,    15,    21,   645,   148,   180,   661,     7,    21,
      21,     7,    21,    15,    21,    21,     8,    21,     8,   685,
      78,   676,   676,    21,    21,   333,     8,   477,    40,   477,
     602,   603,   747,     7,     7,   662,   663,   685,   713,   696,
     571,   477,   477,    21,    21,    21,    15,   628,   349,   604,
       8,    21,     8,    21,    15,    21,    21,    21,     8,   476,
      17,   605,   606,   603,   663,   477,   664,   665,    21,   477,
      21,   607,    17,     7,     8,    21,     8,   749,   607,   477,
     665,    15,   356,   356,   666,   667,   668,   669,   670,   182,
     318,   128,   157,   217,     8,    21,     7,     7,    15,   671,
     671,   671,   667,   356,   669,   670,   356,   670,   475,     7,
      21,   670
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 764 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 766 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 770 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 772 "gram1.y"
    {
	       if ((yyvsp[(2) - (3)].bf_node) != BFNULL) 
               {	    
	          (yyvsp[(2) - (3)].bf_node)->label = (yyvsp[(1) - (3)].label);
	          (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
	 	  if (is_openmp_stmt) {            /*OMP*/
			is_openmp_stmt = 0;
			if((yyvsp[(2) - (3)].bf_node)) {                        /*OMP*/
				if ((yyvsp[(2) - (3)].bf_node)->decl_specs != -BIT_OPENMP) (yyvsp[(2) - (3)].bf_node)->decl_specs = BIT_OPENMP; /*OMP*/
			}                               /*OMP*/
		  }                                       /*OMP*/
               }
	    ;}
    break;

  case 6:
#line 786 "gram1.y"
    { PTR_BFND p;

	     if(lastwasbranch && ! thislabel)
               /*if (warn_all)
		 warn("statement cannot be reached", 36);*/
	     lastwasbranch = thiswasbranch;
	     thiswasbranch = NO;
	     if((yyvsp[(2) - (3)].bf_node)) (yyvsp[(2) - (3)].bf_node)->label = (yyvsp[(1) - (3)].label);
	     if((yyvsp[(1) - (3)].label) && (yyvsp[(2) - (3)].bf_node)) (yyvsp[(1) - (3)].label)->statbody = (yyvsp[(2) - (3)].bf_node); /*8.11.06 podd*/
	     if((yyvsp[(1) - (3)].label)) {
		/*$1->statbody = $2;*/ /*8.11.06 podd*/
		if((yyvsp[(1) - (3)].label)->labtype == LABFORMAT)
		  err("label already that of a format",39);
		else
		  (yyvsp[(1) - (3)].label)->labtype = LABEXEC;
	     }
	     if (is_openmp_stmt) {            /*OMP*/
			is_openmp_stmt = 0;
			if((yyvsp[(2) - (3)].bf_node)) {                        /*OMP*/
				if ((yyvsp[(2) - (3)].bf_node)->decl_specs != -BIT_OPENMP) (yyvsp[(2) - (3)].bf_node)->decl_specs = BIT_OPENMP; /*OMP*/
			}                               /*OMP*/
	     }                                       /*OMP*/
             for (p = pred_bfnd; (yyvsp[(1) - (3)].label) && 
		  ((p->variant == FOR_NODE)||(p->variant == WHILE_NODE)) &&
                  (p->entry.for_node.doend) &&
		  (p->entry.for_node.doend->stateno == (yyvsp[(1) - (3)].label)->stateno);
		  p = p->control_parent)
                ++end_group;
	     (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
     ;}
    break;

  case 7:
#line 817 "gram1.y"
    { /* PTR_LLND p; */
			doinclude( (yyvsp[(3) - (3)].charp) );
/*			p = make_llnd(fi, STRING_VAL, LLNULL, LLNULL, SMNULL);
			p->entry.string_val = $3;
			p->type = global_string;
			$$ = get_bfnd(fi, INCLUDE_STAT, SMNULL, p, LLNULL); */
			(yyval.bf_node) = BFNULL;
		;}
    break;

  case 8:
#line 826 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 832 "gram1.y"
    { PTR_CMNT p;
              PTR_BFND bif; 
	    
              if (last_bfnd && last_bfnd->control_parent &&((last_bfnd->control_parent->variant == LOGIF_NODE)
	         ||(last_bfnd->control_parent->variant == FORALL_STAT)))
  	         bif = last_bfnd->control_parent;
              else
                 bif = last_bfnd;
              p=bif->entry.Template.cmnt_ptr;
              if(p)
                 p->string = StringConcatenation(p->string,commentbuf);
              else
              {
                 p = make_comment(fi,commentbuf, FULL);
                 bif->entry.Template.cmnt_ptr = p;
              }
 	      (yyval.bf_node) = BFNULL;         
            ;}
    break;

  case 10:
#line 852 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 861 "gram1.y"
    {
	    if(yystno)
	      {
	      (yyval.label) = thislabel =	make_label_node(fi,yystno);
	      thislabel->scope = cur_scope();
	      if (thislabel->labdefined && (thislabel->scope == cur_scope()))
		 errstr("Label %s already defined",convic(thislabel->stateno),40);
	      else
		 thislabel->labdefined = YES;
	      }
	    else
	      (yyval.label) = thislabel = LBNULL;
	    ;}
    break;

  case 12:
#line 877 "gram1.y"
    { PTR_BFND p;

	        if (pred_bfnd != global_bfnd)
		    err("Misplaced PROGRAM statement", 33);
		p = get_bfnd(fi,PROG_HEDR, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
		(yyvsp[(3) - (3)].symbol)->entry.prog_decl.prog_hedr=p;
 		set_blobs(p, global_bfnd, NEW_GROUP1);
	        add_scope_level(p, NO);
	        position = IN_PROC;
	    ;}
    break;

  case 13:
#line 889 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 899 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 906 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 912 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 917 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 922 "gram1.y"
    {PTR_BFND p, bif;
	     PTR_SYMB q = SMNULL;
             PTR_LLND l = LLNULL;

	     if(parstate==OUTSIDE || procclass==CLMAIN || procclass==CLBLOCK)
	        err("Misplaced ENTRY statement", 35);

	     bif = cur_scope();
	     if (bif->variant == FUNC_HEDR) {
	        q = make_function((yyvsp[(2) - (4)].hash_entry), bif->entry.Template.symbol->type, YES);
	        l = construct_entry_list(q, (yyvsp[(3) - (4)].symbol), FUNCTION_NAME); 
             }
             else if ((bif->variant == PROC_HEDR) || 
                      (bif->variant == PROS_HEDR) || /* added for FORTRAN M */
                      (bif->variant == PROG_HEDR)) {
	             q = make_procedure((yyvsp[(2) - (4)].hash_entry), YES);
  	             l = construct_entry_list(q, (yyvsp[(3) - (4)].symbol), PROCEDURE_NAME); 
             }
	     p = get_bfnd(fi,ENTRY_STAT, q, l, (yyvsp[(4) - (4)].ll_node), LLNULL);
	     set_blobs(p, pred_bfnd, SAME_GROUP);
             q->decl = YES;   /*4.02.03*/
             q->entry.proc_decl.proc_hedr = p; /*5.02.03*/
	    ;}
    break;

  case 19:
#line 946 "gram1.y"
    { PTR_SYMB s;
	      PTR_BFND p;
/*
	      s = make_global_entity($3, MODULE_NAME, global_default, NO);
	      s->decl = YES;  
	      p = get_bfnd(fi, MODULE_STMT, s, LLNULL, LLNULL, LLNULL);
	      s->entry.Template.func_hedr = p;
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
*/
	      /*position = IN_MODULE;*/


               s = make_module((yyvsp[(3) - (3)].hash_entry));
	       s->decl = YES;   /* variable declaration has been seen. */
	        if (pred_bfnd != global_bfnd)
		    err("Misplaced MODULE statement", 33);
              p = get_bfnd(fi, MODULE_STMT, s, LLNULL, LLNULL, LLNULL);
	      s->entry.Template.func_hedr = p; /* !!!????*/
	      set_blobs(p, global_bfnd, NEW_GROUP1);
	      add_scope_level(p, NO);	
	      position =  IN_MODULE;    /*IN_PROC*/
              privateall = 0;
            ;}
    break;

  case 20:
#line 972 "gram1.y"
    { newprog(); 
	      if (position == IN_OUTSIDE)
	           position = IN_PROC;
              else if (position != IN_INTERNAL_PROC){ 
                if(!is_interface_stat(pred_bfnd))
	           position--;
              }
              else {
                if(!is_interface_stat(pred_bfnd))
                  err("Internal procedures can not contain procedures",304);
              }
	    ;}
    break;

  case 21:
#line 987 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 989 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 991 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 995 "gram1.y"
    { PTR_BFND p;

	      (yyval.symbol) = make_procedure((yyvsp[(1) - (1)].hash_entry), LOCAL);
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
             /* if (pred_bfnd != global_bfnd)
		 {
	         err("Misplaced SUBROUTINE statement", 34);
		 }  
              */
	      p = get_bfnd(fi,PROC_HEDR, (yyval.symbol), LLNULL, LLNULL, LLNULL);
              (yyval.symbol)->entry.proc_decl.proc_hedr = p;
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
            ;}
    break;

  case 25:
#line 1012 "gram1.y"
    { PTR_BFND p;

	      (yyval.symbol) = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
             /* if (pred_bfnd != global_bfnd)
	         err("Misplaced FUNCTION statement", 34); */
	      p = get_bfnd(fi,FUNC_HEDR, (yyval.symbol), LLNULL, LLNULL, LLNULL);
              (yyval.symbol)->entry.func_decl.func_hedr = p;
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
            ;}
    break;

  case 26:
#line 1026 "gram1.y"
    { PTR_BFND p;
             PTR_LLND l;

	      (yyval.symbol) = make_function((yyvsp[(4) - (4)].hash_entry), (yyvsp[(1) - (4)].data_type), LOCAL);
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
              l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
              l->type = (yyvsp[(1) - (4)].data_type);
	      p = get_bfnd(fi,FUNC_HEDR, (yyval.symbol), LLNULL, l, LLNULL);
              (yyval.symbol)->entry.func_decl.func_hedr = p;
            /*  if (pred_bfnd != global_bfnd)
	         err("Misplaced FUNCTION statement", 34);*/
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
/*
	      $$ = make_function($4, $1, LOCAL);
	      $$->decl = YES;
	      p = get_bfnd(fi,FUNC_HEDR, $$, LLNULL, LLNULL, LLNULL);
              if (pred_bfnd != global_bfnd)
	         errstr("cftn.gram: misplaced SUBROUTINE statement.");
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
*/
           ;}
    break;

  case 27:
#line 1050 "gram1.y"
    { PTR_BFND p;
             PTR_LLND l;
	      (yyval.symbol) = make_function((yyvsp[(5) - (5)].hash_entry), (yyvsp[(1) - (5)].data_type), LOCAL);
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
              if((yyvsp[(2) - (5)].ll_node)->variant == RECURSIVE_OP)
	         (yyval.symbol)->attr = (yyval.symbol)->attr | RECURSIVE_BIT;
              l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
              l->type = (yyvsp[(1) - (5)].data_type);
             /* if (pred_bfnd != global_bfnd)
	         err("Misplaced FUNCTION statement", 34);*/
	      p = get_bfnd(fi,FUNC_HEDR, (yyval.symbol), LLNULL, l, (yyvsp[(2) - (5)].ll_node));
              (yyval.symbol)->entry.func_decl.func_hedr = p;
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
            ;}
    break;

  case 28:
#line 1066 "gram1.y"
    { PTR_BFND p;

	      (yyval.symbol) = make_function((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
              if((yyvsp[(1) - (4)].ll_node)->variant == RECURSIVE_OP)
	        (yyval.symbol)->attr = (yyval.symbol)->attr | RECURSIVE_BIT;
              /*if (pred_bfnd != global_bfnd)
	         err("Misplaced FUNCTION statement",34);*/
	      p = get_bfnd(fi,FUNC_HEDR, (yyval.symbol), LLNULL, LLNULL, (yyvsp[(1) - (4)].ll_node));
              (yyval.symbol)->entry.func_decl.func_hedr = p;
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
            ;}
    break;

  case 29:
#line 1080 "gram1.y"
    { PTR_BFND p;
              PTR_LLND l;
	      (yyval.symbol) = make_function((yyvsp[(5) - (5)].hash_entry), (yyvsp[(2) - (5)].data_type), LOCAL);
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP)
	        (yyval.symbol)->attr = (yyval.symbol)->attr | RECURSIVE_BIT;
              l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
              l->type = (yyvsp[(2) - (5)].data_type);
             /* if (pred_bfnd != global_bfnd)
	          err("Misplaced FUNCTION statement",34);*/
	      p = get_bfnd(fi,FUNC_HEDR, (yyval.symbol), LLNULL, l, (yyvsp[(1) - (5)].ll_node));
              (yyval.symbol)->entry.func_decl.func_hedr = p;
	      set_blobs(p, pred_bfnd, NEW_GROUP1);
              add_scope_level(p, NO);
            ;}
    break;

  case 30:
#line 1098 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1100 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1107 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1110 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1112 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1118 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1120 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1127 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1129 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1131 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1136 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1140 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1144 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1150 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1159 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1163 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1168 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1189 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1194 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1199 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1206 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1222 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1226 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1234 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1242 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1251 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1259 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1263 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1265 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1269 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1271 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1273 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1275 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1277 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1279 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1281 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1283 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1285 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1287 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1289 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1291 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1293 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1295 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1297 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1299 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1301 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1303 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1308 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1317 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1327 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1335 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1345 "gram1.y"
    { 
	      PTR_LLND q, r, l;
	     /* PTR_SYMB s;*/
	      PTR_TYPE t;
	      int type_opts;

	      vartype = (yyvsp[(1) - (7)].data_type);
              if((yyvsp[(6) - (7)].ll_node) && vartype->variant != T_STRING)
                errstr("Non character entity  %s  has length specification",(yyvsp[(3) - (7)].hash_entry)->ident,41);
              t = make_type_node(vartype, (yyvsp[(6) - (7)].ll_node));
	      type_opts = type_options;
	      if ((yyvsp[(5) - (7)].ll_node)) type_opts = type_opts | DIMENSION_BIT;
	      if ((yyvsp[(5) - (7)].ll_node))
		 q = deal_with_options((yyvsp[(3) - (7)].hash_entry), t, type_opts, (yyvsp[(5) - (7)].ll_node), ndim, (yyvsp[(7) - (7)].ll_node), (yyvsp[(5) - (7)].ll_node));
	      else q = deal_with_options((yyvsp[(3) - (7)].hash_entry), t, type_opts, attr_dims, attr_ndim, (yyvsp[(7) - (7)].ll_node), (yyvsp[(5) - (7)].ll_node));
	      r = make_llnd(fi, EXPR_LIST, q, LLNULL, SMNULL);
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = vartype;
	      (yyval.bf_node) = get_bfnd(fi,VAR_DECL, SMNULL, r, l, (yyvsp[(2) - (7)].ll_node));
	    ;}
    break;

  case 108:
#line 1366 "gram1.y"
    { 
	      PTR_LLND q, r;
	    /*  PTR_SYMB s;*/
              PTR_TYPE t;
	      int type_opts;
              if((yyvsp[(5) - (6)].ll_node) && vartype->variant != T_STRING)
                errstr("Non character entity  %s  has length specification",(yyvsp[(3) - (6)].hash_entry)->ident,41);
              t = make_type_node(vartype, (yyvsp[(5) - (6)].ll_node));
	      type_opts = type_options;
	      if ((yyvsp[(4) - (6)].ll_node)) type_opts = type_opts | DIMENSION_BIT;
	      if ((yyvsp[(4) - (6)].ll_node))
		 q = deal_with_options((yyvsp[(3) - (6)].hash_entry), t, type_opts, (yyvsp[(4) - (6)].ll_node), ndim, (yyvsp[(6) - (6)].ll_node), (yyvsp[(4) - (6)].ll_node));
	      else q = deal_with_options((yyvsp[(3) - (6)].hash_entry), t, type_opts, attr_dims, attr_ndim, (yyvsp[(6) - (6)].ll_node), (yyvsp[(4) - (6)].ll_node));
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (6)].bf_node)->entry.Template.ll_ptr1);
       	    ;}
    break;

  case 109:
#line 1385 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1387 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1389 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1393 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1395 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1399 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1403 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1405 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1409 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1415 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1419 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1421 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1425 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1429 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1433 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1437 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1441 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1447 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1451 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1455 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1461 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1466 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1473 "gram1.y"
    { 
	      PTR_LLND q, r;
	      PTR_SYMB s;

              s = make_scalar((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);
	      s->attr = s->attr | type_opt;	
	      q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi, INTENT_STMT, SMNULL, r, (yyvsp[(4) - (7)].ll_node), LLNULL);
	    ;}
    break;

  case 132:
#line 1484 "gram1.y"
    { 
	      PTR_LLND q, r;
	      PTR_SYMB s;

              s = make_scalar((yyvsp[(3) - (3)].hash_entry), TYNULL, LOCAL);	
	      s->attr = s->attr | type_opt;
	      q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
  	    ;}
    break;

  case 133:
#line 1497 "gram1.y"
    { 
	      PTR_LLND q, r;
	      PTR_SYMB s;

              s = make_scalar((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
	      s->attr = s->attr | OPTIONAL_BIT;
	      q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi, OPTIONAL_STMT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 134:
#line 1508 "gram1.y"
    { 
	      PTR_LLND q, r;
	      PTR_SYMB s;

              s = make_scalar((yyvsp[(3) - (3)].hash_entry), TYNULL, LOCAL);	
	      s->attr = s->attr | OPTIONAL_BIT;
	      q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
  	    ;}
    break;

  case 135:
#line 1521 "gram1.y"
    { 
	      PTR_LLND r;
	      PTR_SYMB s;

              s = (yyvsp[(4) - (4)].ll_node)->entry.Template.symbol; 
              s->attr = s->attr | SAVE_BIT;
	      r = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi, STATIC_STMT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 136:
#line 1531 "gram1.y"
    { 
	      PTR_LLND r;
	      PTR_SYMB s;

              s = (yyvsp[(3) - (3)].ll_node)->entry.Template.symbol;
              s->attr = s->attr | SAVE_BIT;
	      r = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
  	    ;}
    break;

  case 137:
#line 1544 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1549 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1555 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1559 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1564 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1569 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1575 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1579 "gram1.y"
    {
	      type_options = 0;
              /* following block added by dbg */
	      ndim = 0;
	      attr_ndim = 0;
	      attr_dims = LLNULL;
	      /* end section added by dbg */
              (yyval.data_type) = make_type_node((yyvsp[(1) - (4)].data_type), (yyvsp[(3) - (4)].ll_node));
            ;}
    break;

  case 145:
#line 1589 "gram1.y"
    { PTR_TYPE t;

	      type_options = 0;
	      ndim = 0;
	      attr_ndim = 0;
	      attr_dims = LLNULL;
              t = lookup_type((yyvsp[(3) - (5)].hash_entry));
	      vartype = t;
	      (yyval.data_type) = make_type_node(t, LLNULL);
            ;}
    break;

  case 146:
#line 1602 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1607 "gram1.y"
    { PTR_TYPE p;
	      PTR_LLND q;
	      PTR_SYMB s;
              s = (yyvsp[(2) - (2)].hash_entry)->id_attr;
	      if (s)
		   s->attr = (yyvsp[(1) - (2)].token);
	      else {
		p = undeftype ? global_unknown : impltype[*(yyvsp[(2) - (2)].hash_entry)->ident - 'a'];
                s = install_entry((yyvsp[(2) - (2)].hash_entry), SOFT);
		s->attr = (yyvsp[(1) - (2)].token);
                set_type(s, p, LOCAL);
	      }
	      q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(2) - (2)].hash_entry)->id_attr);
	      q = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,ATTR_DECL, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 148:
#line 1626 "gram1.y"
    { PTR_TYPE p;
	      PTR_LLND q, r;
	      PTR_SYMB s;
	      int att;

	      att = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1->entry.Template.ll_ptr1->
		    entry.Template.symbol->attr;
              s = (yyvsp[(3) - (3)].hash_entry)->id_attr;
	      if (s)
		   s->attr = att;
	      else {
		p = undeftype ? global_unknown : impltype[*(yyvsp[(3) - (3)].hash_entry)->ident - 'a'];
                s = install_entry((yyvsp[(3) - (3)].hash_entry), SOFT);
		s->attr = att;
                set_type(s, p, LOCAL);
	      }
	      q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].hash_entry)->id_attr);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next) ;
	      r->entry.list.next = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);

	    ;}
    break;

  case 149:
#line 1652 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1654 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1666 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1673 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1674 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1675 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1676 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1677 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1678 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1679 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1684 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1686 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1690 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1692 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1699 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1703 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1705 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1707 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1715 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1722 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1728 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1734 "gram1.y"
    { /* $$ = make_llnd(fi, SPEC_PAIR, $2, LLNULL, SMNULL); */
	     char *q;
             q = (yyvsp[(1) - (2)].ll_node)->entry.string_val;
  	     if (strcmp(q, "len") == 0)
               (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
             else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);              
            ;}
    break;

  case 171:
#line 1743 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1751 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1764 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1766 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1769 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1773 "gram1.y"
    { PTR_SYMB s;
	      PTR_LLND q, r;
	      if(! (yyvsp[(5) - (5)].ll_node)) {
		err("No dimensions in DIMENSION statement", 42);
	      }
              if(statement_kind == 1) /*DVM-directive*/
                err("No shape specification", 65);                
	      s = make_array((yyvsp[(4) - (5)].hash_entry), TYNULL, (yyvsp[(5) - (5)].ll_node), ndim, LOCAL);
	      s->attr = s->attr | DIMENSION_BIT;
	      q = make_llnd(fi,ARRAY_REF, (yyvsp[(5) - (5)].ll_node), LLNULL, s);
	      s->type->entry.ar_decl.ranges = (yyvsp[(5) - (5)].ll_node);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,DIM_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 177:
#line 1788 "gram1.y"
    {  PTR_SYMB s;
	      PTR_LLND q, r;
	      if(! (yyvsp[(4) - (4)].ll_node)) {
		err("No dimensions in DIMENSION statement", 42);
	      }
	      s = make_array((yyvsp[(3) - (4)].hash_entry), TYNULL, (yyvsp[(4) - (4)].ll_node), ndim, LOCAL);
	      s->attr = s->attr | DIMENSION_BIT;
	      q = make_llnd(fi,ARRAY_REF, (yyvsp[(4) - (4)].ll_node), LLNULL, s);
	      s->type->entry.ar_decl.ranges = (yyvsp[(4) - (4)].ll_node);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1);
	;}
    break;

  case 178:
#line 1804 "gram1.y"
    {/* PTR_SYMB s;*/
	      PTR_LLND r;

	         /*if(!$5) {
		   err("No dimensions in ALLOCATABLE statement",305);		
	           }
	          s = make_array($4, TYNULL, $5, ndim, LOCAL);
	          s->attr = s->attr | ALLOCATABLE_BIT;
	          q = make_llnd(fi,ARRAY_REF, $5, LLNULL, s);
	          s->type->entry.ar_decl.ranges = $5;
                  r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                */
              (yyvsp[(4) - (4)].ll_node)->entry.Template.symbol->attr = (yyvsp[(4) - (4)].ll_node)->entry.Template.symbol->attr | ALLOCATABLE_BIT;
	      r = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi, ALLOCATABLE_STMT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 179:
#line 1822 "gram1.y"
    {  /*PTR_SYMB s;*/
	      PTR_LLND r;

	        /*  if(! $4) {
		      err("No dimensions in ALLOCATABLE statement",305);
		
	            }
	           s = make_array($3, TYNULL, $4, ndim, LOCAL);
	           s->attr = s->attr | ALLOCATABLE_BIT;
	           q = make_llnd(fi,ARRAY_REF, $4, LLNULL, s);
	           s->type->entry.ar_decl.ranges = $4;
	           r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                */
              (yyvsp[(3) - (3)].ll_node)->entry.Template.symbol->attr = (yyvsp[(3) - (3)].ll_node)->entry.Template.symbol->attr | ALLOCATABLE_BIT;
              r = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	;}
    break;

  case 180:
#line 1842 "gram1.y"
    { PTR_SYMB s;
	      PTR_LLND  r;
           
	          /*  if(! $5) {
		      err("No dimensions in POINTER statement",306);	    
	              } 
	             s = make_array($4, TYNULL, $5, ndim, LOCAL);
	             s->attr = s->attr | POINTER_BIT;
	             q = make_llnd(fi,ARRAY_REF, $5, LLNULL, s);
	             s->type->entry.ar_decl.ranges = $5;
                   */

                  /*s = make_pointer( $4->entry.Template.symbol->parent, TYNULL, LOCAL);*/ /*17.02.03*/
                 /*$4->entry.Template.symbol->attr = $4->entry.Template.symbol->attr | POINTER_BIT;*/
              s = (yyvsp[(4) - (4)].ll_node)->entry.Template.symbol; /*17.02.03*/
              s->attr = s->attr | POINTER_BIT;
	      r = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi, POINTER_STMT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 181:
#line 1862 "gram1.y"
    {  PTR_SYMB s;
	      PTR_LLND r;

     	        /*  if(! $4) {
	        	err("No dimensions in POINTER statement",306);
	            }
	           s = make_array($3, TYNULL, $4, ndim, LOCAL);
	           s->attr = s->attr | POINTER_BIT;
	           q = make_llnd(fi,ARRAY_REF, $4, LLNULL, s);
	           s->type->entry.ar_decl.ranges = $4;
                */

                /*s = make_pointer( $3->entry.Template.symbol->parent, TYNULL, LOCAL);*/ /*17.02.03*/
                /*$3->entry.Template.symbol->attr = $3->entry.Template.symbol->attr | POINTER_BIT;*/
              s = (yyvsp[(3) - (3)].ll_node)->entry.Template.symbol; /*17.02.03*/
              s->attr = s->attr | POINTER_BIT;
	      r = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	;}
    break;

  case 182:
#line 1884 "gram1.y"
    {/* PTR_SYMB s;*/
	      PTR_LLND r;


	     /* if(! $5) {
		err("No dimensions in TARGET statement",307);
	      }
	      s = make_array($4, TYNULL, $5, ndim, LOCAL);
	      s->attr = s->attr | TARGET_BIT;
	      q = make_llnd(fi,ARRAY_REF, $5, LLNULL, s);
	      s->type->entry.ar_decl.ranges = $5;
             */
              (yyvsp[(4) - (4)].ll_node)->entry.Template.symbol->attr = (yyvsp[(4) - (4)].ll_node)->entry.Template.symbol->attr | TARGET_BIT;
	      r = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi, TARGET_STMT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 183:
#line 1901 "gram1.y"
    {  /*PTR_SYMB s;*/
	      PTR_LLND r;

	     /* if(! $4) {
		err("No dimensions in TARGET statement",307);
	      }
	      s = make_array($3, TYNULL, $4, ndim, LOCAL);
	      s->attr = s->attr | TARGET_BIT;
	      q = make_llnd(fi,ARRAY_REF, $4, LLNULL, s);
	      s->type->entry.ar_decl.ranges = $4;
              */
              (yyvsp[(3) - (3)].ll_node)->entry.Template.symbol->attr = (yyvsp[(3) - (3)].ll_node)->entry.Template.symbol->attr | TARGET_BIT;
	      r = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	;}
    break;

  case 184:
#line 1919 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1926 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1933 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1940 "gram1.y"
    { PTR_LLND p, r;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      /*q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);*/
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(p, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 188:
#line 1953 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1960 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1967 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1978 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 1982 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 1984 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 1989 "gram1.y"
    {  PTR_SYMB s;
	
	      if((yyvsp[(2) - (2)].ll_node)) {
		s = make_array((yyvsp[(1) - (2)].hash_entry), TYNULL, (yyvsp[(2) - (2)].ll_node), ndim, LOCAL);
                s->attr = s->attr | DIMENSION_BIT;
		s->type->entry.ar_decl.ranges = (yyvsp[(2) - (2)].ll_node);
		(yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(2) - (2)].ll_node), LLNULL, s);
	      }
	      else {
		s = make_scalar((yyvsp[(1) - (2)].hash_entry), TYNULL, LOCAL);	
		(yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
	      }

          ;}
    break;

  case 195:
#line 2007 "gram1.y"
    { PTR_LLND p, q;
              PTR_SYMB s;

	      s = make_external((yyvsp[(4) - (4)].hash_entry), TYNULL);
	      s->attr = s->attr | EXTERNAL_BIT;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      p = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,EXTERN_STAT, SMNULL, p, LLNULL, LLNULL);
	    ;}
    break;

  case 196:
#line 2018 "gram1.y"
    { PTR_LLND p, q;
              PTR_SYMB s;

	      s = make_external((yyvsp[(3) - (3)].hash_entry), TYNULL);
	      s->attr = s->attr | EXTERNAL_BIT;
              p = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      q = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 197:
#line 2030 "gram1.y"
    { PTR_LLND p, q;
              PTR_SYMB s;

	      s = make_intrinsic((yyvsp[(4) - (4)].hash_entry), TYNULL); /*make_function($3, TYNULL, NO);*/
	      s->attr = s->attr | INTRINSIC_BIT;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      p = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,INTRIN_STAT, SMNULL, p,
			     LLNULL, LLNULL);
	    ;}
    break;

  case 198:
#line 2042 "gram1.y"
    { PTR_LLND p, q;
              PTR_SYMB s;

	      s = make_intrinsic((yyvsp[(3) - (3)].hash_entry), TYNULL); /* make_function($3, TYNULL, NO);*/
	      s->attr = s->attr | INTRINSIC_BIT;
              p = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      q = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 199:
#line 2056 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2062 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2069 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2075 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2081 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2089 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2096 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2115 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2129 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2133 "gram1.y"
    {
	      if (parstate == OUTSIDE)
	         { PTR_BFND p;

		   p = get_bfnd(fi,PROG_HEDR,
                                make_program(look_up_sym("_MAIN")),
                                LLNULL, LLNULL, LLNULL);
		   set_blobs(p, global_bfnd, NEW_GROUP1);
	           add_scope_level(p, NO);
		   position = IN_PROC; 
	  	   /*parstate = INDCL;*/
                 }
	      if(parstate < INDCL)
		{
		  /* enddcl();*/
		  parstate = INDCL;
		}
	    ;}
    break;

  case 222:
#line 2178 "gram1.y"
    {;;}
    break;

  case 223:
#line 2182 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2186 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2192 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2196 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2200 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2202 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2206 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2208 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2212 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2216 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2218 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2222 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2224 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2226 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2231 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2255 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2300 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2302 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2309 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2316 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2323 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2332 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2334 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2336 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2340 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2342 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2346 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2355 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2362 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2369 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2371 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2375 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2379 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2385 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2387 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2391 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2395 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2400 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2407 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2414 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2424 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2426 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2430 "gram1.y"
    { PTR_SYMB p;

                /* The check if name and expr have compatible types has
                   not been done yet. */ 
		p = make_constant((yyvsp[(1) - (3)].hash_entry), TYNULL);
 	        p->attr = p->attr | PARAMETER_BIT;
                p->entry.const_value = (yyvsp[(3) - (3)].ll_node);
		(yyval.ll_node) = make_llnd(fi,CONST_REF, LLNULL, LLNULL, p);
	    ;}
    break;

  case 295:
#line 2442 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2445 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2454 "gram1.y"
    { PTR_LLND p, q;
              PTR_SYMB s;

	      s = make_function((yyvsp[(3) - (3)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              p = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      q = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 298:
#line 2467 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2473 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2479 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2485 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2493 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2503 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2505 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2509 "gram1.y"
    {  PTR_HASH oldhash;
	       PTR_SYMB oldsym, newsym;
	       PTR_LLND l, m;

	       oldhash = just_look_up_sym_in_scope(module_scope, (yyvsp[(3) - (3)].hash_entry)->ident);
	       if (oldhash == HSNULL) {
                  errstr("Unknown identifier %s", (yyvsp[(3) - (3)].hash_entry)->ident,309);
	          (yyval.ll_node)= LLNULL;
	       }
	       else {
	         oldsym = oldhash->id_attr;
	         newsym = make_local_entity((yyvsp[(1) - (3)].hash_entry), oldsym->variant, oldsym->type, LOCAL);
	         /* copies data in entry.Template structure and attr */
	         copy_sym_data(oldsym, newsym);	         
	           /*newsym->entry.Template.base_name = oldsym;*//*19.03.03*/
	  	 l = make_llnd(fi, VAR_REF, LLNULL, LLNULL, oldsym);
		 m = make_llnd(fi, VAR_REF, LLNULL, LLNULL, newsym);
		 (yyval.ll_node) = make_llnd(fi, RENAME_NODE, m, l, SMNULL);
 	      }
            ;}
    break;

  case 306:
#line 2530 "gram1.y"
    {  PTR_HASH oldhash;
	       PTR_SYMB oldsym, newsym;
	       PTR_LLND m;

	       oldhash = just_look_up_sym_in_scope(module_scope, (yyvsp[(1) - (1)].hash_entry)->ident);
	       if (oldhash == HSNULL) {
                  errstr("Unknown identifier %s.", (yyvsp[(1) - (1)].hash_entry)->ident,309);
	          (yyval.ll_node)= LLNULL;
	       }
	       else {
	         oldsym = oldhash->id_attr;
	         newsym = make_local_entity((yyvsp[(1) - (1)].hash_entry), oldsym->variant, oldsym->type,
LOCAL);
	         /* copies data in entry.Template structure and attr */
	         copy_sym_data(oldsym, newsym);	         
	           /*newsym->entry.Template.base_name = oldsym;*//*19.03.03*/
	  	/* l = make_llnd(fi, VAR_REF, LLNULL, LLNULL, oldsym);*/
		 m = make_llnd(fi, VAR_REF, LLNULL, LLNULL, newsym);
		 (yyval.ll_node) = make_llnd(fi, RENAME_NODE, m, LLNULL, oldsym);
 	      }
            ;}
    break;

  case 307:
#line 2555 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2557 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2561 "gram1.y"
    {  PTR_HASH oldhash;
	       PTR_SYMB oldsym, newsym;
	       PTR_LLND l, m;

	       oldhash = just_look_up_sym_in_scope(module_scope, (yyvsp[(3) - (3)].hash_entry)->ident);
	       if (oldhash == HSNULL) {
                  errstr("Unknown identifier %s", (yyvsp[(3) - (3)].hash_entry)->ident,309);
	          (yyval.ll_node)= LLNULL;
	       }
	       else {
	         oldsym = oldhash->id_attr;
	         newsym = make_local_entity((yyvsp[(1) - (3)].hash_entry), oldsym->variant, oldsym->type,
LOCAL);
	         /* copies data in entry.Template structure and attr */
	         copy_sym_data(oldsym, newsym);	         
	           /*newsym->entry.Template.base_name = oldsym;*//*19.03.03*/
	  	 l = make_llnd(fi, VAR_REF, LLNULL, LLNULL, oldsym);
		 m = make_llnd(fi, VAR_REF, LLNULL, LLNULL, newsym);
		 (yyval.ll_node) = make_llnd(fi, RENAME_NODE, m, l, SMNULL);
 	      }
            ;}
    break;

  case 310:
#line 2592 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2594 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2597 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2598 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2603 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2607 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2615 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, LLNULL, SMNULL);
	      ++ndim;
              explicit_shape = 0;
	    ;}
    break;

  case 317:
#line 2624 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL);
	      ++ndim;
              explicit_shape = 0;
	    ;}
    break;

  case 318:
#line 2633 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2643 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2652 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2654 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2658 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2666 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2681 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2688 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2690 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2694 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2709 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2710 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2714 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2716 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2728 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2730 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2734 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2740 "gram1.y"
    { PTR_LLND p,q;
	      
	      setimpl(vartype, (int)(yyvsp[(1) - (3)].charv), (int)(yyvsp[(3) - (3)].charv));
	      p = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      p->entry.cval = (yyvsp[(1) - (3)].charv);
	      q = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      q->entry.cval = (yyvsp[(3) - (3)].charv);
	      (yyval.ll_node)= make_llnd(fi,DDOT, p, q, SMNULL);
	    ;}
    break;

  case 337:
#line 2752 "gram1.y"
    {
	      if(yyleng!=1 || yytext[0]<'a' || yytext[0]>'z')
		{
		  err("IMPLICIT item must be single letter", 37);
		  (yyval.charv) = '\0';
		}
	      else (yyval.charv) = yytext[0];
	    ;}
    break;

  case 338:
#line 2763 "gram1.y"
    {
	      if (parstate == OUTSIDE)
	         { PTR_BFND p;

		   p = get_bfnd(fi,PROG_HEDR,
                                make_program(look_up_sym("_MAIN")),
                                LLNULL, LLNULL, LLNULL);
		   set_blobs(p, global_bfnd, NEW_GROUP1);
	           add_scope_level(p, NO);
		   position = IN_PROC; 
	  	   parstate = INSIDE;
                 }
	  
	    ;}
    break;

  case 339:
#line 2780 "gram1.y"
    { switch(parstate)
		{
                case OUTSIDE:  
			{ PTR_BFND p;

			  p = get_bfnd(fi,PROG_HEDR,
                                       make_program(look_up_sym("_MAIN")),
                                       LLNULL, LLNULL, LLNULL);
			  set_blobs(p, global_bfnd, NEW_GROUP1);
			  add_scope_level(p, NO);
			  position = IN_PROC; 
	  		  parstate = INDCL; }
	                  break;
                case INSIDE:    parstate = INDCL;
                case INDCL:     break;

                case INDATA:
                         /*  err(
                     "Statement order error: declaration after DATA or function statement", 
                                 29);*/
                              break;

                default:
                           err("Declaration among executables", 30);
                }
        ;}
    break;

  case 342:
#line 2818 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2820 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2824 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2826 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2828 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2839 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2843 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2849 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2851 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2855 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2857 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2859 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2863 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2865 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2869 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2871 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2873 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2875 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2877 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2879 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2881 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2883 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2885 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2887 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2889 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2891 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2893 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2895 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2897 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2899 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2901 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2903 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2905 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2907 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2909 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2911 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2913 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2916 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2917 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2929 "gram1.y"
    { PTR_SYMB s;
	      PTR_TYPE t;
	     /* PTR_LLND l;*/

       	      if (!(s = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	     	 s->decl = SOFT;
	      } 
	
	      switch (s->variant)
              {
	      case CONST_NAME:
		   (yyval.ll_node) = make_llnd(fi,CONST_REF,LLNULL,LLNULL, s);
		   t = s->type;
	           if ((t != TYNULL) &&
                       ((t->variant == T_ARRAY) ||  (t->variant == T_STRING) ))
                                 (yyval.ll_node)->variant = ARRAY_REF;

                   (yyval.ll_node)->type = t;
	           break;
	      case DEFAULT:   /* if common region with same name has been
                                 declared. */
		   s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	     	   s->decl = SOFT;

	      case VARIABLE_NAME:
                   (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL, s);
	           t = s->type;
	           if (t != TYNULL) {
                     if ((t->variant == T_ARRAY) ||  (t->variant == T_STRING) ||
                         ((t->variant == T_POINTER) && (t->entry.Template.base_type->variant == T_ARRAY) ) )
                         (yyval.ll_node)->variant = ARRAY_REF;

/*  	              if (t->variant == T_DERIVED_TYPE)
                         $$->variant = RECORD_REF; */
	           }
                   (yyval.ll_node)->type = t;
	           break;
	      case TYPE_NAME:
  	           (yyval.ll_node) = make_llnd(fi,TYPE_REF,LLNULL,LLNULL, s);
	           (yyval.ll_node)->type = s->type;
	           break;
	      case INTERFACE_NAME:
  	           (yyval.ll_node) = make_llnd(fi, INTERFACE_REF,LLNULL,LLNULL, s);
	           (yyval.ll_node)->type = s->type;
	           break;
              case FUNCTION_NAME:
                   if(isResultVar(s)) {
                     (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL, s);
	             t = s->type;
	             if (t != TYNULL) {
                       if ((t->variant == T_ARRAY) ||  (t->variant == T_STRING) ||
                         ((t->variant == T_POINTER) && (t->entry.Template.base_type->variant == T_ARRAY) ) )
                         (yyval.ll_node)->variant = ARRAY_REF;
	             }
                     (yyval.ll_node)->type = t;
	             break;
                   }                                        
	      default:
  	           (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL, s);
	           (yyval.ll_node)->type = s->type;
	           break;
	      }
             /* if ($$->variant == T_POINTER) {
	         l = $$;
	         $$ = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	         $$->type = l->type->entry.Template.base_type;
	      }
              */ /*11.02.03*/
           ;}
    break;

  case 382:
#line 3003 "gram1.y"
    { PTR_SYMB  s;
	      (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
              s= (yyval.ll_node)->entry.Template.symbol;
              if ((((yyvsp[(1) - (1)].ll_node)->variant == VAR_REF) || ((yyvsp[(1) - (1)].ll_node)->variant == ARRAY_REF))  && (s->scope !=cur_scope()))  /*global_bfnd*/
              {
	          if(((s->variant == FUNCTION_NAME) && (!isResultVar(s))) || (s->variant == PROCEDURE_NAME) || (s->variant == ROUTINE_NAME))
                  { s = (yyval.ll_node)->entry.Template.symbol =  make_scalar(s->parent, TYNULL, LOCAL);
		    (yyval.ll_node)->type = s->type;  
		  }
              }
            ;}
    break;

  case 383:
#line 3015 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3017 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3021 "gram1.y"
    { int num_triplets;
	      PTR_SYMB s;  /*, sym;*/
	      /* PTR_LLND l; */
	      PTR_TYPE tp;
	      /* l = $1; */
	      s = (yyvsp[(1) - (5)].ll_node)->entry.Template.symbol;
            
	      /* Handle variable to function conversion. */
	      if (((yyvsp[(1) - (5)].ll_node)->variant == VAR_REF) && 
	          (((s->variant == VARIABLE_NAME) && (s->type) &&
                    (s->type->variant != T_ARRAY)) ||
  	            (s->variant == ROUTINE_NAME))) {
	        s = (yyvsp[(1) - (5)].ll_node)->entry.Template.symbol =  make_function(s->parent, TYNULL, NO);
	        (yyvsp[(1) - (5)].ll_node)->variant = FUNC_CALL;
              }
	      if (((yyvsp[(1) - (5)].ll_node)->variant == VAR_REF) && (s->variant == FUNCTION_NAME)) { 
                if(isResultVar(s))
	          (yyvsp[(1) - (5)].ll_node)->variant = ARRAY_REF;
                else
                  (yyvsp[(1) - (5)].ll_node)->variant = FUNC_CALL;
              }
	      if (((yyvsp[(1) - (5)].ll_node)->variant == VAR_REF) && (s->variant == PROGRAM_NAME)) {
                 errstr("The name '%s' is invalid in this context",s->ident,285);
                 (yyvsp[(1) - (5)].ll_node)->variant = FUNC_CALL;
              }
              /* l = $1; */
	      num_triplets = is_array_section_ref((yyvsp[(4) - (5)].ll_node));
	      switch ((yyvsp[(1) - (5)].ll_node)->variant)
              {
	      case TYPE_REF:
                   (yyvsp[(1) - (5)].ll_node)->variant = STRUCTURE_CONSTRUCTOR;                  
                   (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
                   (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
                   (yyval.ll_node)->type =  lookup_type(s->parent); 
	          /* $$ = make_llnd(fi, STRUCTURE_CONSTRUCTOR, $1, $4, SMNULL);
	           $$->type = $1->type;*//*18.02.03*/
	           break;
	      case INTERFACE_REF:
	       /*  sym = resolve_overloading(s, $4);
	           if (sym != SMNULL)
	  	   {
	              l = make_llnd(fi, FUNC_CALL, $4, LLNULL, sym);
	              l->type = sym->type;
	              $$ = $1; $$->variant = OVERLOADED_CALL;
	              $$->entry.Template.ll_ptr1 = l;
	              $$->type = sym->type;
	           }
	           else {
	             errstr("can't resolve call %s", s->ident,310);
	           }
	           break;
                 */ /*podd 01.02.03*/

                   (yyvsp[(1) - (5)].ll_node)->variant = FUNC_CALL;

	      case FUNC_CALL:
                   (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
                   (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
                   if(s->type) 
                     (yyval.ll_node)->type = s->type;
                   else
                     (yyval.ll_node)->type = global_default;
	           late_bind_if_needed((yyval.ll_node));
	           break;
	      case DEREF_OP:
              case ARRAY_REF:
	           /* array element */
	           if (num_triplets == 0) {
                       if ((yyvsp[(4) - (5)].ll_node) == LLNULL) {
                           s = (yyvsp[(1) - (5)].ll_node)->entry.Template.symbol = make_function(s->parent, TYNULL, NO);
                           s->entry.func_decl.num_output = 1;
                           (yyvsp[(1) - (5)].ll_node)->variant = FUNC_CALL;
                           (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
                       } else if ((yyvsp[(1) - (5)].ll_node)->type->variant == T_STRING) {
                           PTR_LLND temp = (yyvsp[(4) - (5)].ll_node);
                           int num_input = 0;

                           while (temp) {
                             ++num_input;
                             temp = temp->entry.Template.ll_ptr2;
                           }
                           (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
                           s = (yyvsp[(1) - (5)].ll_node)->entry.Template.symbol = make_function(s->parent, TYNULL, NO);
                           s->entry.func_decl.num_output = 1;
                           s->entry.func_decl.num_input = num_input;
                           (yyvsp[(1) - (5)].ll_node)->variant = FUNC_CALL;
                           (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
                       } else {
       	                   (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	                   (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
                           (yyval.ll_node)->type = (yyvsp[(1) - (5)].ll_node)->type->entry.ar_decl.base_type;
                       }
                   }
                   /* substring */
	           else if ((num_triplets == 1) && 
                            ((yyvsp[(1) - (5)].ll_node)->type->variant == T_STRING)) {
    	           /*
                     $1->entry.Template.ll_ptr1 = $4;
	             $$ = $1; $$->type = global_string;
                   */
	                  (yyval.ll_node) = make_llnd(fi, 
			  ARRAY_OP, LLNULL, LLNULL, SMNULL);
    	                  (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(1) - (5)].ll_node);
       	                  (yyval.ll_node)->entry.Template.ll_ptr2 = (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1;
	                  (yyval.ll_node)->type = global_string;
                   }           
                   /* array section */
                   else {
    	             (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	             (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node); tp = make_type(fi, T_ARRAY);     /**18.03.17*/
                     tp->entry.ar_decl.base_type = (yyvsp[(1) - (5)].ll_node)->type->entry.ar_decl.base_type; /**18.03.17 $1->type */
	             tp->entry.ar_decl.num_dimensions = num_triplets;
	             (yyval.ll_node)->type = tp;
                   }
	           break;
	      default:
                    if((yyvsp[(1) - (5)].ll_node)->entry.Template.symbol)
                      errstr("Can't subscript %s",(yyvsp[(1) - (5)].ll_node)->entry.Template.symbol->ident, 44);
                    else
	              err("Can't subscript",44);
             }
             /*if ($$->variant == T_POINTER) {
	        l = $$;
	        $$ = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	        $$->type = l->type->entry.Template.base_type;
	     }
              */  /*11.02.03*/

	     endioctl(); 
           ;}
    break;

  case 386:
#line 3152 "gram1.y"
    { int num_triplets;
	      PTR_SYMB s;
	      PTR_LLND l;

	      s = (yyvsp[(1) - (6)].ll_node)->entry.Template.symbol;
/*              if ($1->type->variant == T_POINTER) {
	         l = $1;
	         $1 = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	         $1->type = l->type->entry.Template.base_type;
	      } */
	      if (((yyvsp[(1) - (6)].ll_node)->type->variant != T_ARRAY) ||
                  ((yyvsp[(1) - (6)].ll_node)->type->entry.ar_decl.base_type->variant != T_STRING)) {
	         errstr("Can't take substring of %s", s->ident, 45);
              }
              else {
  	        num_triplets = is_array_section_ref((yyvsp[(4) - (6)].ll_node));
	           /* array element */
                if (num_triplets == 0) {
                   (yyvsp[(1) - (6)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (6)].ll_node);
                  /* $1->entry.Template.ll_ptr2 = $6;*/
	          /* $$ = $1;*/
                   l=(yyvsp[(1) - (6)].ll_node);
                   /*$$->type = $1->type->entry.ar_decl.base_type;*/
                   l->type = global_string;  /**18.03.17* $1->type->entry.ar_decl.base_type;*/
                }
                /* array section */
                else {
    	           (yyvsp[(1) - (6)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (6)].ll_node);
    	           /*$1->entry.Template.ll_ptr2 = $6;
	           $$ = $1; $$->type = make_type(fi, T_ARRAY);
                   $$->type->entry.ar_decl.base_type = $1->type;
	           $$->type->entry.ar_decl.num_dimensions = num_triplets;
                  */
                   l = (yyvsp[(1) - (6)].ll_node); l->type = make_type(fi, T_ARRAY);
                   l->type->entry.ar_decl.base_type = global_string;   /**18.03.17* $1->type*/
	           l->type->entry.ar_decl.num_dimensions = num_triplets;
               }
                (yyval.ll_node) = make_llnd(fi, ARRAY_OP, l, (yyvsp[(6) - (6)].ll_node), SMNULL);
	        (yyval.ll_node)->type = l->type;
              
              /* if ($$->variant == T_POINTER) {
	          l = $$;
	          $$ = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	          $$->type = l->type->entry.Template.base_type;
	       }
               */  /*11.02.03*/
             }
             endioctl();
          ;}
    break;

  case 387:
#line 3202 "gram1.y"
    {  int num_triplets;
	      PTR_LLND l,l1,l2;
              PTR_TYPE tp;

         /*   if ($1->variant == T_POINTER) {
	         l = $1;
	         $1 = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	         $1->type = l->type->entry.Template.base_type;
	      } */

              num_triplets = is_array_section_ref((yyvsp[(3) - (4)].ll_node));
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              l2 = (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr2;  
              l1 = (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1;                
              if(l2 && l2->type->variant == T_STRING)/*substring*/
                if(num_triplets == 1){
	           l = make_llnd(fi, ARRAY_OP, LLNULL, LLNULL, SMNULL);
    	           l->entry.Template.ll_ptr1 = l2;
       	           l->entry.Template.ll_ptr2 = (yyvsp[(3) - (4)].ll_node)->entry.Template.ll_ptr1;
	           l->type = global_string; 
                   (yyval.ll_node)->entry.Template.ll_ptr2 = l;                                          
                } else
                   err("Can't subscript",44);
              else if (l2 && l2->type->variant == T_ARRAY) {
                 if(num_triplets > 0) { /*array section*/
                   tp = make_type(fi,T_ARRAY);
                   tp->entry.ar_decl.base_type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                   tp->entry.ar_decl.num_dimensions = num_triplets;
                   (yyval.ll_node)->type = tp;
                   l2->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                   l2->type = (yyval.ll_node)->type;   
                  }                 
                 else {  /*array element*/
                   l2->type = l2->type->entry.ar_decl.base_type;
                   l2->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);   
                   if(l1->type->variant != T_ARRAY)  
                     (yyval.ll_node)->type = l2->type;
                 }
              } else 
                   {err("Can't subscript",44); /*fprintf(stderr,"%d  %d",$1->variant,l2);*/}
                   /*errstr("Can't subscript %s",l2->entry.Template.symbol->ident,441);*/
         ;}
    break;

  case 388:
#line 3246 "gram1.y"
    { int num_triplets;
	      PTR_LLND l,q;

          /*     if ($1->variant == T_POINTER) {
	         l = $1;
	         $1 = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	         $1->type = l->type->entry.Template.base_type;
	      } */

              (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
	      if (((yyvsp[(1) - (5)].ll_node)->type->variant != T_ARRAY) &&
                  ((yyvsp[(1) - (5)].ll_node)->type->entry.ar_decl.base_type->variant != T_STRING)) {
	         err("Can't take substring",45);
              }
              else {
  	        num_triplets = is_array_section_ref((yyvsp[(3) - (5)].ll_node));
                l = (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr2;
                if(l) {
                /* array element */
	        if (num_triplets == 0) {
                   l->entry.Template.ll_ptr1 = (yyvsp[(3) - (5)].ll_node);       	           
                   l->type = global_string;
                }
                /* array section */
                else {	
    	             l->entry.Template.ll_ptr1 = (yyvsp[(3) - (5)].ll_node);
	             l->type = make_type(fi, T_ARRAY);
                     l->type->entry.ar_decl.base_type = global_string;
	             l->type->entry.ar_decl.num_dimensions = num_triplets;
                }
	        q = make_llnd(fi, ARRAY_OP, l, (yyvsp[(5) - (5)].ll_node), SMNULL);
	        q->type = l->type;
                (yyval.ll_node)->entry.Template.ll_ptr2 = q;
                if((yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1->type->variant != T_ARRAY)  
                     (yyval.ll_node)->type = q->type;
               }
             }
          ;}
    break;

  case 389:
#line 3288 "gram1.y"
    { PTR_TYPE t;
	      PTR_SYMB  field;
	    /*  PTR_BFND at_scope;*/
              PTR_LLND l;


/*              if ($1->variant == T_POINTER) {
	         l = $1;
	         $1 = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	         $1->type = l->type->entry.Template.base_type;
	      } */

	      t = (yyvsp[(1) - (3)].ll_node)->type; 
	      
	      if (( ( ((yyvsp[(1) - (3)].ll_node)->variant == VAR_REF) 
	          ||  ((yyvsp[(1) - (3)].ll_node)->variant == CONST_REF) 
                  ||  ((yyvsp[(1) - (3)].ll_node)->variant == ARRAY_REF)
                  ||  ((yyvsp[(1) - (3)].ll_node)->variant == RECORD_REF)) && (t->variant == T_DERIVED_TYPE)) 
	          ||((((yyvsp[(1) - (3)].ll_node)->variant == ARRAY_REF) || ((yyvsp[(1) - (3)].ll_node)->variant == RECORD_REF)) && (t->variant == T_ARRAY) &&
                      (t = t->entry.ar_decl.base_type) && (t->variant == T_DERIVED_TYPE))) 
                {
                 t->name = lookup_type_symbol(t->name);
	         if ((field = component(t->name, yytext))) {                   
	            l =  make_llnd(fi, VAR_REF, LLNULL, LLNULL, field);
                    l->type = field->type;
                    if(field->type->variant == T_ARRAY || field->type->variant == T_STRING)
                      l->variant = ARRAY_REF; 
                    (yyval.ll_node) = make_llnd(fi, RECORD_REF, (yyvsp[(1) - (3)].ll_node), l, SMNULL);
                    if((yyvsp[(1) - (3)].ll_node)->type->variant != T_ARRAY)
                       (yyval.ll_node)->type = field->type;
                    else {
                       (yyval.ll_node)->type = make_type(fi,T_ARRAY);
                       if(field->type->variant != T_ARRAY) 
	                 (yyval.ll_node)->type->entry.ar_decl.base_type = field->type;
                       else
                         (yyval.ll_node)->type->entry.ar_decl.base_type = field->type->entry.ar_decl.base_type;
	               (yyval.ll_node)->type->entry.ar_decl.num_dimensions = t->entry.ar_decl.num_dimensions;
                       }
                 }
                  else  
                    errstr("Illegal component  %s", yytext,311);
              }                     
               else 
                    errstr("Can't take component  %s", yytext,311);
             ;}
    break;

  case 390:
#line 3346 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3348 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3350 "gram1.y"
    {  int num_triplets;
               PTR_TYPE tp;
              /* PTR_LLND l;*/
	      if ((yyvsp[(1) - (5)].ll_node)->type->variant == T_ARRAY)
              {
  	         num_triplets = is_array_section_ref((yyvsp[(4) - (5)].ll_node));
	         /* array element */
	         if (num_triplets == 0) {
       	            (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
       	            (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
                    (yyval.ll_node)->type = (yyvsp[(1) - (5)].ll_node)->type->entry.ar_decl.base_type;
                 }
                 /* substring */
	       /*  else if ((num_triplets == 1) && 
                          ($1->type->variant == T_STRING)) {
    	                  $1->entry.Template.ll_ptr1 = $4;
	                  $$ = $1; $$->type = global_string;
                 }   */ /*podd*/        
                 /* array section */
                 else {
    	             (yyvsp[(1) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	             (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node); tp = make_type(fi, T_ARRAY);
                     tp->entry.ar_decl.base_type = (yyvsp[(1) - (5)].ll_node)->type->entry.ar_decl.base_type;  /**18.03.17* $1->type */
	             tp->entry.ar_decl.num_dimensions = num_triplets;
                     (yyval.ll_node)->type = tp;
                 }
             } 
             else err("can't subscript",44);

            /* if ($$->variant == T_POINTER) {
	        l = $$;
	        $$ = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	        $$->type = l->type->entry.Template.base_type;
	     }
             */  /*11.02.03*/

            endioctl();
           ;}
    break;

  case 393:
#line 3390 "gram1.y"
    {  int num_triplets;
	      PTR_LLND l,l1,l2;

         /*   if ($1->variant == T_POINTER) {
	         l = $1;
	         $1 = make_llnd(fi, DEREF_OP, l, LLNULL, SMNULL);
	         $1->type = l->type->entry.Template.base_type;
	      } */

              num_triplets = is_array_section_ref((yyvsp[(3) - (4)].ll_node));
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              l2 = (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr2;  
              l1 = (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1;                
              if(l2 && l2->type->variant == T_STRING)/*substring*/
                if(num_triplets == 1){
	           l = make_llnd(fi, ARRAY_OP, LLNULL, LLNULL, SMNULL);
    	           l->entry.Template.ll_ptr1 = l2;
       	           l->entry.Template.ll_ptr2 = (yyvsp[(3) - (4)].ll_node)->entry.Template.ll_ptr1;
	           l->type = global_string; 
                   (yyval.ll_node)->entry.Template.ll_ptr2 = l;                                          
                } else
                   err("Can't subscript",44);
              else if (l2 && l2->type->variant == T_ARRAY) {
                 if(num_triplets > 0) { /*array section*/
                   (yyval.ll_node)->type = make_type(fi,T_ARRAY);
                   (yyval.ll_node)->type->entry.ar_decl.base_type = l2->type->entry.ar_decl.base_type;
                   (yyval.ll_node)->type->entry.ar_decl.num_dimensions = num_triplets;
                   l2->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                   l2->type = (yyval.ll_node)->type;   
                  }                 
                 else {  /*array element*/
                   l2->type = l2->type->entry.ar_decl.base_type;
                   l2->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);   
                   if(l1->type->variant != T_ARRAY)  
                     (yyval.ll_node)->type = l2->type;
                 }
              } else 
                   err("Can't subscript",44);
         ;}
    break;

  case 394:
#line 3432 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3442 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3444 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3448 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3452 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3454 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3458 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3460 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3466 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3468 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3474 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3484 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3490 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3497 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3503 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3511 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3519 "gram1.y"
    { PTR_TYPE t;
	      PTR_LLND p,q;
	      (yyval.ll_node) = make_llnd(fi,STRING_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
              if(yyquote=='\"') 
	        t = global_string_2;
              else
	        t = global_string;

	      p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      p->entry.ival = yyleng;
	      p->type = global_int;
              q = make_llnd(fi, LEN_OP, p, LLNULL, SMNULL); 
              (yyval.ll_node)->type = make_type_node(t, q);
	    ;}
    break;

  case 411:
#line 3535 "gram1.y"
    { PTR_TYPE t;
	      (yyval.ll_node) = make_llnd(fi,STRING_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
              if(yyquote=='\"') 
	        t = global_string_2;
              else
	        t = global_string;
	      (yyval.ll_node)->type = make_type_node(t, (yyvsp[(1) - (3)].ll_node));
            ;}
    break;

  case 412:
#line 3545 "gram1.y"
    { PTR_TYPE t;
	      (yyval.ll_node) = make_llnd(fi,STRING_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
              if(yyquote=='\"') 
	        t = global_string_2;
              else
	        t = global_string;
	      (yyval.ll_node)->type = make_type_node(t, (yyvsp[(1) - (3)].ll_node));
            ;}
    break;

  case 413:
#line 3558 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3565 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3567 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3590 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3592 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3594 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3596 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3598 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3600 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3602 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3604 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3607 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3607 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3608 "gram1.y"
    { PTR_TYPE array_type;
             (yyval.ll_node) = make_llnd (fi,CONSTRUCTOR_REF,(yyvsp[(4) - (6)].ll_node),LLNULL,SMNULL); 
             /*$$->type = $2->type;*/ /*28.02.03*/
             array_type = make_type(fi, T_ARRAY);
	     array_type->entry.ar_decl.num_dimensions = 1;
             if((yyvsp[(4) - (6)].ll_node)->type->variant == T_ARRAY)
	       array_type->entry.ar_decl.base_type = (yyvsp[(4) - (6)].ll_node)->type->entry.ar_decl.base_type;
             else
               array_type->entry.ar_decl.base_type = (yyvsp[(4) - (6)].ll_node)->type;
             (yyval.ll_node)->type = array_type;
           ;}
    break;

  case 427:
#line 3622 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3624 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3647 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3649 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3651 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3667 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3669 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3671 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3684 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3688 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3690 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3698 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3700 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3702 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3704 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3758 "gram1.y"
    { PTR_BFND biff;

	      (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      bind(); 
	      biff = cur_scope();
	      if ((biff->variant == FUNC_HEDR) || (biff->variant == PROC_HEDR)
		  || (biff->variant == PROS_HEDR) 
	          || (biff->variant == PROG_HEDR)
                  || (biff->variant == BLOCK_DATA)) {
                if(biff->control_parent == global_bfnd) position = IN_OUTSIDE;
		else if(!is_interface_stat(biff->control_parent)) position++;
              } else if  (biff->variant == MODULE_STMT)
                position = IN_OUTSIDE;
	      else err("Unexpected END statement read", 52);
             /* FB ADDED set the control parent so the empty function unparse right*/
              if ((yyval.bf_node))
                (yyval.bf_node)->control_parent = biff;
              delete_beyond_scope_level(pred_bfnd);
            ;}
    break;

  case 443:
#line 3780 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3793 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3802 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3805 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3855 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3861 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3866 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3884 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3886 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3888 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3890 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3892 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3895 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3901 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3903 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3905 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3908 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3910 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3912 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3939 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3948 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3956 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3958 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3960 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3965 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3972 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3980 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3982 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 3986 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 3989 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 3991 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 3995 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 4001 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 4003 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 4005 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 4007 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4011 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4013 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4021 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4023 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4029 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4031 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4035 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4039 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4060 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4063 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4067 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4069 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4076 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4080 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4082 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4098 "gram1.y"
    { PTR_SYMB  s;
      	      if (!(s = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	     	 s->decl = SOFT;
	      }
              (yyval.symbol) = s; 
	 ;}
    break;

  case 495:
#line 4111 "gram1.y"
    { PTR_SYMB s;
              PTR_LLND l;
              int vrnt;

            /*  s = make_scalar($1, TYNULL, LOCAL);*/ /*16.02.03*/
              s = (yyvsp[(1) - (5)].symbol);
	      if (s->variant != CONST_NAME) {
                if(in_vec) 
                   vrnt=SEQ;
                else
                   vrnt=DDOT;     
                l = make_llnd(fi, SEQ, make_llnd(fi, vrnt, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL),
                              LLNULL, SMNULL);
		(yyval.ll_node) = make_llnd(fi,IOACCESS, LLNULL, l, s);
		do_name_err = NO;
	      }
	      else {
		err("Symbolic constant not allowed as DO variable", 47);
		do_name_err = YES;
	      }
	    ;}
    break;

  case 496:
#line 4134 "gram1.y"
    { PTR_SYMB s;
              PTR_LLND l;
              int vrnt;
              /*s = make_scalar($1, TYNULL, LOCAL);*/ /*16.02.03*/
              s = (yyvsp[(1) - (7)].symbol);
	      if( s->variant != CONST_NAME ) {
                if(in_vec) 
                   vrnt=SEQ;
                else
                   vrnt=DDOT;     
                l = make_llnd(fi, SEQ, make_llnd(fi, vrnt, (yyvsp[(3) - (7)].ll_node), (yyvsp[(5) - (7)].ll_node), SMNULL), (yyvsp[(7) - (7)].ll_node),
                              SMNULL);
		(yyval.ll_node) = make_llnd(fi,IOACCESS, LLNULL, l, s);
		do_name_err = NO;
	      }
	      else {
		err("Symbolic constant not allowed as DO variable", 47);
		do_name_err = YES;
	      }
	    ;}
    break;

  case 497:
#line 4157 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4159 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4166 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4168 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4170 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4172 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4174 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4179 "gram1.y"
    { PTR_LLND p, r;
             PTR_SYMB s1, s2 = SMNULL, s3, arg_list;
	     PTR_HASH hash_entry;

	   /*  if (just_look_up_sym("=") != HSNULL) {
	        p = intrinsic_op_node("=", EQUAL, $2, $4);
   	        $$ = get_bfnd(fi, OVERLOADED_ASSIGN_STAT, SMNULL, p, $2, $4);
             }	      
             else */ if ((yyvsp[(2) - (4)].ll_node)->variant == FUNC_CALL) {
                if(parstate==INEXEC){
                  	  err("Declaration among executables", 30);
                 /*   $$=BFNULL;*/
 	         (yyval.bf_node) = get_bfnd(fi,STMTFN_STAT, SMNULL, (yyvsp[(2) - (4)].ll_node), LLNULL, LLNULL);
                } 
                else {	         
  	         (yyvsp[(2) - (4)].ll_node)->variant = STMTFN_DECL;
		 /* $2->entry.Template.ll_ptr2 = $4; */
                 if( (yyvsp[(2) - (4)].ll_node)->entry.Template.ll_ptr1) {
		   r = (yyvsp[(2) - (4)].ll_node)->entry.Template.ll_ptr1->entry.Template.ll_ptr1;
                   if(r->variant != VAR_REF && r->variant != ARRAY_REF){
                     err("A dummy argument of a statement function must be a scalar identifier", 333);
                     s1 = SMNULL;
                   }
                   else                       
		     s1 = r ->entry.Template.symbol;
                 } else
                   s1 = SMNULL;
		 if (s1)
	            s1->scope = cur_scope();
 	         (yyval.bf_node) = get_bfnd(fi,STMTFN_STAT, SMNULL, (yyvsp[(2) - (4)].ll_node), LLNULL, LLNULL);
	         add_scope_level((yyval.bf_node), NO);
                 arg_list = SMNULL;
		 if (s1) 
                 {
	            /*arg_list = SMNULL;*/
                    p = (yyvsp[(2) - (4)].ll_node)->entry.Template.ll_ptr1;
                    while (p != LLNULL)
                    {
		    /*   if (p->entry.Template.ll_ptr1->variant != VAR_REF) {
			  errstr("cftn.gram:1: illegal statement function %s.", $2->entry.Template.symbol->ident);
			  break;
		       } 
                    */
                       r = p->entry.Template.ll_ptr1;
                       if(r->variant != VAR_REF && r->variant != ARRAY_REF){
                         err("A dummy argument of a statement function must be a scalar identifier", 333);
                         break;
                       }
	               hash_entry = look_up_sym(r->entry.Template.symbol->parent->ident);
	               s3 = make_scalar(hash_entry, s1->type, IO);
	               if (arg_list == SMNULL) 
                          s2 = arg_list = s3;
             	       else 
                       {
                          s2->id_list = s3;
                          s2 = s3;
                       }
                       p = p->entry.Template.ll_ptr2;
                    }
                 }
  		    (yyvsp[(2) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		    install_param_list((yyvsp[(2) - (4)].ll_node)->entry.Template.symbol,
				       arg_list, LLNULL, FUNCTION_NAME);
	            delete_beyond_scope_level((yyval.bf_node));
		 
		/* else
		    errstr("cftn.gram: Illegal statement function declaration %s.", $2->entry.Template.symbol->ident); */
               }
	     }
	     else {
		(yyval.bf_node) = get_bfnd(fi,ASSIGN_STAT,SMNULL, (yyvsp[(2) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), LLNULL);
                 parstate = INEXEC;
             }
	  ;}
    break;

  case 505:
#line 4254 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4266 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4273 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4276 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4278 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4287 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4294 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4301 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4309 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4314 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4319 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4322 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4325 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4328 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4331 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4334 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4352 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4356 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4361 "gram1.y"
    { PTR_SYMB p;

	      if((yyvsp[(3) - (3)].hash_entry)->id_attr)
		p = (yyvsp[(3) - (3)].hash_entry)->id_attr;
	      else {
	        p = make_scalar((yyvsp[(3) - (3)].hash_entry), TYNULL, LOCAL);
		p->variant = LABEL_VAR;
	      }

	      if(p->variant == LABEL_VAR) {
		  (yyval.bf_node) = get_bfnd(fi,ASSGOTO_NODE,p,LLNULL,LLNULL,LLNULL);
		  thiswasbranch = YES;
	      }
	      else {
		  err("Must go to assigned variable", 48);
		  (yyval.bf_node) = BFNULL;
	      }
	    ;}
    break;

  case 525:
#line 4380 "gram1.y"
    { PTR_SYMB p;

	      if((yyvsp[(3) - (7)].hash_entry)->id_attr)
		p = (yyvsp[(3) - (7)].hash_entry)->id_attr;
	      else {
	        p = make_scalar((yyvsp[(3) - (7)].hash_entry), TYNULL, LOCAL);
		p->variant = LABEL_VAR;
	      }

	      if (p->variant == LABEL_VAR) {
		 (yyval.bf_node) = get_bfnd(fi,ASSGOTO_NODE,p,(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
		 thiswasbranch = YES;
	      }
	      else {
		err("Must go to assigned variable",48);
		(yyval.bf_node) = BFNULL;
	      }
	    ;}
    break;

  case 526:
#line 4399 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4407 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4411 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4416 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4423 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4425 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4427 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4430 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4431 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4442 "gram1.y"
    { if(parstate == OUTSIDE)
		{ PTR_BFND p;

		  p = get_bfnd(fi,PROG_HEDR, make_program(look_up_sym("_MAIN")), LLNULL, LLNULL, LLNULL);
		  set_blobs(p, global_bfnd, NEW_GROUP1);
		  add_scope_level(p, NO);
		  position = IN_PROC; 
		}
		if(parstate < INDATA) enddcl();
		parstate = INEXEC;
		yystno = 0;
	      ;}
    break;

  case 538:
#line 4457 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4461 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4469 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4472 "gram1.y"
    { PTR_LLND p, q = LLNULL;

		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  q->entry.string_val = (char *)"unit";
		  q->type = global_string;
		  p = make_llnd(fi, SPEC_PAIR, q, (yyvsp[(2) - (2)].ll_node), SMNULL);
		  (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = p;
		  endioctl();
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 542:
#line 4482 "gram1.y"
    { PTR_LLND p, q, r;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  q->entry.string_val = (char *)"unit";
		  q->type = global_string;
		  r = make_llnd(fi, SPEC_PAIR, p, q, SMNULL);
		  (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = r;
		  endioctl();
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 543:
#line 4495 "gram1.y"
    { PTR_LLND p, q, r;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"**";
		  p->type = global_string;
		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  q->entry.string_val = (char *)"unit";
		  q->type = global_string;
		  r = make_llnd(fi, SPEC_PAIR, p, q, SMNULL);
		  (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = r;
		  endioctl();
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 544:
#line 4508 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4512 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 546:
#line 4515 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4518 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 548:
#line 4522 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 549:
#line 4531 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 550:
#line 4534 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 551:
#line 4538 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 552:
#line 4540 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 553:
#line 4546 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4550 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 555:
#line 4552 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4554 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4561 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 558:
#line 4565 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 559:
#line 4567 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4569 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4573 "gram1.y"
    { PTR_LLND p;
		  PTR_LLND q = LLNULL;

		  if ((yyvsp[(1) - (1)].ll_node)->variant == INT_VAL)
 	          {
		        PTR_LABEL r;

			r = make_label_node(fi, (long) (yyvsp[(1) - (1)].ll_node)->entry.ival);
			r->scope = cur_scope();
			p = make_llnd_label(fi, LABEL_REF, r);
		  }
		  else p = (yyvsp[(1) - (1)].ll_node); 
		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  q->entry.string_val = (char *)"fmt";
		  q->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, q, p, SMNULL);
		  endioctl();
		;}
    break;

  case 562:
#line 4592 "gram1.y"
    { PTR_LLND p;
		  PTR_LLND q;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  q->entry.string_val = (char *)"fmt";
		  q->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, q, p, SMNULL);
		  endioctl();
		;}
    break;

  case 563:
#line 4608 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 564:
#line 4619 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 565:
#line 4626 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 566:
#line 4628 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 567:
#line 4632 "gram1.y"
    { PTR_LLND p;
		  PTR_LLND q;
 
		  nioctl++;
		  if ((nioctl == 2) && ((yyvsp[(1) - (1)].ll_node)->variant == INT_VAL))
 	          {
		        PTR_LABEL r;

			r = make_label_node(fi, (long) (yyvsp[(1) - (1)].ll_node)->entry.ival);
			r->scope = cur_scope();
			p = make_llnd_label(fi, LABEL_REF, r);
		  }
		  else p = (yyvsp[(1) - (1)].ll_node); 
		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  if (nioctl == 1)
		        q->entry.string_val = (char *)"unit"; 
		  else {
                     if(((yyvsp[(1) - (1)].ll_node)->variant == VAR_REF) && (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->variant == NAMELIST_NAME)
                       q->entry.string_val = (char *)"nml";
                     else
                       q->entry.string_val = (char *)"fmt";
                  }
		  q->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, q, p, SMNULL);
		;}
    break;

  case 568:
#line 4658 "gram1.y"
    { PTR_LLND p;
		  PTR_LLND q;

		  nioctl++;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  if (nioctl == 1)
		        q->entry.string_val = (char *)"unit"; 
		  else  q->entry.string_val = (char *)"fmt";
		  q->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, q, p, SMNULL);
		;}
    break;

  case 569:
#line 4673 "gram1.y"
    { PTR_LLND p;
		  PTR_LLND q;

		  nioctl++;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"**";
		  p->type = global_string;
		  q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  if (nioctl == 1)
		        q->entry.string_val = (char *)"unit"; 
		  else  q->entry.string_val = (char *)"fmt";
		  q->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, q, p, SMNULL);
		;}
    break;

  case 570:
#line 4688 "gram1.y"
    { 
		  PTR_LLND p;
		  char *q;

		  q = (yyvsp[(1) - (2)].ll_node)->entry.string_val;
  		  if ((strcmp(q, "end") == 0) || (strcmp(q, "err") == 0) || (strcmp(q, "eor") == 0) || ((strcmp(q,"fmt") == 0) && ((yyvsp[(2) - (2)].ll_node)->variant == INT_VAL)))
 	          {
		        PTR_LABEL r;

			r = make_label_node(fi, (long) (yyvsp[(2) - (2)].ll_node)->entry.ival);
			r->scope = cur_scope();
			p = make_llnd_label(fi, LABEL_REF, r);
		  }
		  else p = (yyvsp[(2) - (2)].ll_node);

		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL); ;}
    break;

  case 571:
#line 4705 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 572:
#line 4713 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 573:
#line 4722 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 574:
#line 4730 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 575:
#line 4735 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 576:
#line 4740 "gram1.y"
    {
	    PTR_LLND p, q, l;

	    if ((yyvsp[(3) - (4)].ll_node)->variant == INT_VAL)
		{
		        PTR_LABEL r;

			r = make_label_node(fi, (long) (yyvsp[(3) - (4)].ll_node)->entry.ival);
			r->scope = cur_scope();
			p = make_llnd_label(fi, LABEL_REF, r);
		}
	    else p = (yyvsp[(3) - (4)].ll_node);
	    
            q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	    q->entry.string_val = (char *)"fmt";
            q->type = global_string;
            l = make_llnd(fi, SPEC_PAIR, q, p, SMNULL);

            (yyval.bf_node) = get_bfnd(fi, PRINT_STAT, SMNULL, LLNULL, l, LLNULL);
	    endioctl();
	   ;}
    break;

  case 577:
#line 4762 "gram1.y"
    { PTR_LLND p, q, r;
		
	     p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	     p->entry.string_val = (char *)"*";
	     p->type = global_string;
	     q = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	     q->entry.string_val = (char *)"fmt";
             q->type = global_string;
             r = make_llnd(fi, SPEC_PAIR, q, p, SMNULL);
	     (yyval.bf_node) = get_bfnd(fi, PRINT_STAT, SMNULL, LLNULL, r, LLNULL);
	     endioctl();
           ;}
    break;

  case 578:
#line 4778 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 579:
#line 4780 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 580:
#line 4784 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 581:
#line 4786 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 582:
#line 4793 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 583:
#line 4795 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 584:
#line 4797 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 585:
#line 4801 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 586:
#line 4803 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 587:
#line 4805 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4807 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4809 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4811 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4815 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 592:
#line 4818 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 593:
#line 4821 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 594:
#line 4827 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 595:
#line 4833 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4841 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 597:
#line 4845 "gram1.y"
    { startioctl();;}
    break;

  case 598:
#line 4853 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 599:
#line 4855 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 600:
#line 4859 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4861 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 602:
#line 4863 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 603:
#line 4868 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 604:
#line 4873 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4878 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4883 "gram1.y"
    {
	      if((yyvsp[(1) - (2)].token) == SUBT_OP)
		{
		  (yyval.ll_node) = make_llnd(fi,SUBT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
		  set_expr_type((yyval.ll_node));
		}
	      else	(yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);
	    ;}
    break;

  case 607:
#line 4892 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4897 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 609:
#line 4902 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 610:
#line 4904 "gram1.y"
    { PTR_CMNT p;
	    p = make_comment(fi,*commentbuf, HALF);
	    if (cur_comment)
               cur_comment->next = p;
            else {
	       if ((pred_bfnd->control_parent->variant == LOGIF_NODE) ||(pred_bfnd->control_parent->variant == FORALL_STAT))

	           pred_bfnd->control_parent->entry.Template.cmnt_ptr = p;

	       else last_bfnd->entry.Template.cmnt_ptr = p;
            }
	    comments = cur_comment = CMNULL;
          ;}
    break;

  case 671:
#line 4984 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 672:
#line 4986 "gram1.y"
    { PTR_SYMB s;
                if((yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2)
                {
                  s = (yyvsp[(3) - (3)].ll_node)->entry.Template.ll_ptr1->entry.Template.symbol;
                  s->attr = s->attr | COMMON_BIT;
                }
	        add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	      ;}
    break;

  case 673:
#line 4997 "gram1.y"
    {PTR_SYMB s;
	      PTR_LLND q;
	      if(! explicit_shape) 
                err("Explicit shape specification is required", 50);
	      
	      s = make_array((yyvsp[(1) - (2)].hash_entry), TYNULL, (yyvsp[(2) - (2)].ll_node), ndim, LOCAL);
              if(s->attr & TEMPLATE_BIT)
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
              if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & DVM_POINTER_BIT))
                errstr( "Inconsistent declaration of identifier  %s ", s->ident, 16);
              else
	        s->attr = s->attr | TEMPLATE_BIT;
              if((yyvsp[(2) - (2)].ll_node)) s->attr = s->attr | DIMENSION_BIT;  
	      q = make_llnd(fi,ARRAY_REF, (yyvsp[(2) - (2)].ll_node), LLNULL, s);
	      s->type->entry.ar_decl.ranges = (yyvsp[(2) - (2)].ll_node);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	     ;}
    break;

  case 674:
#line 5017 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 675:
#line 5021 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 676:
#line 5023 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 677:
#line 5027 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if(s->attr &  DYNAMIC_BIT)
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
              if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & HEAP_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
              else
                s->attr = s->attr | DYNAMIC_BIT;        
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 678:
#line 5040 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 679:
#line 5044 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 680:
#line 5046 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 681:
#line 5050 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
              else
                s->attr = s->attr | INHERIT_BIT;        
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 682:
#line 5061 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 683:
#line 5072 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 684:
#line 5076 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 685:
#line 5078 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 686:
#line 5082 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 687:
#line 5084 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 688:
#line 5094 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if(s->attr & SHADOW_BIT)
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & HEAP_BIT)) 
                      errstr( "Inconsistent declaration of identifier %s", s->ident, 16); 
              else
        	      s->attr = s->attr | SHADOW_BIT;  
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 689:
#line 5106 "gram1.y"
    { PTR_SYMB s;
	      PTR_LLND q, r;
	      if(! explicit_shape) {
              err("Explicit shape specification is required", 50);
		/* $$ = BFNULL;*/
	      }
	      s = make_array((yyvsp[(3) - (4)].hash_entry), TYNULL, (yyvsp[(4) - (4)].ll_node), ndim, LOCAL);
              if(s->attr &  PROCESSORS_BIT)
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
              if((s->attr & ALIGN_BIT) ||(s->attr & DISTRIBUTE_BIT) ||(s->attr & TEMPLATE_BIT) || (s->attr & DYNAMIC_BIT) ||(s->attr & SHADOW_BIT) || (s->attr & TASK_BIT) || (s->attr & DVM_POINTER_BIT) || (s->attr & INHERIT_BIT))
                errstr("Inconsistent declaration of identifier %s", s->ident, 16);
              else
	        s->attr = s->attr | PROCESSORS_BIT;
              if((yyvsp[(4) - (4)].ll_node)) s->attr = s->attr | DIMENSION_BIT;
	      q = make_llnd(fi,ARRAY_REF, (yyvsp[(4) - (4)].ll_node), LLNULL, s);
	      s->type->entry.ar_decl.ranges = (yyvsp[(4) - (4)].ll_node);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,HPF_PROCESSORS_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 690:
#line 5126 "gram1.y"
    { PTR_SYMB s;
	      PTR_LLND q, r;
	      if(! explicit_shape) {
              err("Explicit shape specification is required", 50);
		/* $$ = BFNULL;*/
	      }
	      s = make_array((yyvsp[(3) - (4)].hash_entry), TYNULL, (yyvsp[(4) - (4)].ll_node), ndim, LOCAL);
              if(s->attr &  PROCESSORS_BIT)
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
              if((s->attr & ALIGN_BIT) ||(s->attr & DISTRIBUTE_BIT) ||(s->attr & TEMPLATE_BIT) || (s->attr & DYNAMIC_BIT) ||(s->attr & SHADOW_BIT) || (s->attr & TASK_BIT) || (s->attr & DVM_POINTER_BIT) || (s->attr & INHERIT_BIT))
                errstr("Inconsistent declaration of identifier %s", s->ident, 16);
              else
	        s->attr = s->attr | PROCESSORS_BIT;
              if((yyvsp[(4) - (4)].ll_node)) s->attr = s->attr | DIMENSION_BIT;
	      q = make_llnd(fi,ARRAY_REF, (yyvsp[(4) - (4)].ll_node), LLNULL, s);
	      s->type->entry.ar_decl.ranges = (yyvsp[(4) - (4)].ll_node);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,HPF_PROCESSORS_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 691:
#line 5146 "gram1.y"
    {  PTR_SYMB s;
	      PTR_LLND q, r;
	      if(! explicit_shape) {
		err("Explicit shape specification is required", 50);
		/*$$ = BFNULL;*/
	      }
	      s = make_array((yyvsp[(3) - (4)].hash_entry), TYNULL, (yyvsp[(4) - (4)].ll_node), ndim, LOCAL);
              if(s->attr &  PROCESSORS_BIT)
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
              if((s->attr & ALIGN_BIT) ||(s->attr & DISTRIBUTE_BIT) ||(s->attr & TEMPLATE_BIT) || (s->attr & DYNAMIC_BIT) ||(s->attr & SHADOW_BIT) || (s->attr & TASK_BIT) || (s->attr &  DVM_POINTER_BIT) || (s->attr & INHERIT_BIT) )
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16);
              else
	        s->attr = s->attr | PROCESSORS_BIT;
              if((yyvsp[(4) - (4)].ll_node)) s->attr = s->attr | DIMENSION_BIT;
	      q = make_llnd(fi,ARRAY_REF, (yyvsp[(4) - (4)].ll_node), LLNULL, s);
	      s->type->entry.ar_decl.ranges = (yyvsp[(4) - (4)].ll_node);
	      r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	      add_to_lowLevelList(r, (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1);
	;}
    break;

  case 692:
#line 5168 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 693:
#line 5174 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 694:
#line 5183 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 695:
#line 5191 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 696:
#line 5197 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 697:
#line 5205 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 698:
#line 5212 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 699:
#line 5218 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 700:
#line 5227 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 701:
#line 5231 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 702:
#line 5237 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 703:
#line 5245 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 704:
#line 5259 "gram1.y"
    { PTR_SYMB s;
            if(parstate == INEXEC){
              if (!(s = (yyvsp[(2) - (3)].hash_entry)->id_attr))
              {
	         s = make_array((yyvsp[(2) - (3)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
	     	 s->decl = SOFT;
	      } 
            } else
              s = make_array((yyvsp[(2) - (3)].hash_entry), TYNULL, LLNULL, 0, LOCAL);

              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (3)].ll_node), LLNULL, s);
            ;}
    break;

  case 705:
#line 5272 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 706:
#line 5278 "gram1.y"
    { PTR_LLND q;
             if(!(yyvsp[(4) - (5)].ll_node))
               err("Distribution format list is omitted", 51);
            /* if($6)
               err("NEW_VALUE specification in DISTRIBUTE directive");*/
             q = set_ll_list((yyvsp[(3) - (5)].ll_node),LLNULL,EXPR_LIST);
	     (yyval.bf_node) = get_bfnd(fi,DVM_DISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node));
            ;}
    break;

  case 707:
#line 5294 "gram1.y"
    { PTR_LLND q;
                /*  if(!$4)
                  {err("Distribution format is omitted", 51); errcnt--;}
                 */
              q = set_ll_list((yyvsp[(3) - (6)].ll_node),LLNULL,EXPR_LIST);
                 /* r = LLNULL;
                   if($6){
                     r = set_ll_list($6,LLNULL,EXPR_LIST);
                     if($7) r = set_ll_list(r,$7,EXPR_LIST);
                   } else
                     if($7) r = set_ll_list(r,$7,EXPR_LIST);
                 */
	      (yyval.bf_node) = get_bfnd(fi,DVM_REDISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].ll_node));;}
    break;

  case 708:
#line 5309 "gram1.y"
    {
                 /* r = LLNULL;
                    if($5){
                      r = set_ll_list($5,LLNULL,EXPR_LIST);
                      if($6) r = set_ll_list(r,$6,EXPR_LIST);
                    } else
                      if($6) r = set_ll_list(r,$6,EXPR_LIST);
                  */
	      (yyval.bf_node) = get_bfnd(fi,DVM_REDISTRIBUTE_DIR,SMNULL,(yyvsp[(8) - (8)].ll_node) ,(yyvsp[(3) - (8)].ll_node),(yyvsp[(5) - (8)].ll_node) );
             ;}
    break;

  case 709:
#line 5337 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 710:
#line 5339 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 711:
#line 5343 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 712:
#line 5345 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 713:
#line 5349 "gram1.y"
    {  PTR_SYMB s;
 
          if(parstate == INEXEC){
            if (!(s = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
	     	 s->decl = SOFT;
	      } 
            if(s->attr & PROCESSORS_BIT)
              errstr( "Illegal use of PROCESSORS name %s ", s->ident, 53);
            if(s->attr & TASK_BIT)
              errstr( "Illegal use of task array name %s ", s->ident, 71);

          } else {
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
            if(s->attr & DISTRIBUTE_BIT)
              errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
            else if( (s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
              errstr("Inconsistent declaration of identifier  %s",s->ident, 16);
            else
              s->attr = s->attr | DISTRIBUTE_BIT;
          } 
         if(s->attr & ALIGN_BIT)
               errstr("A distributee may not have the ALIGN attribute:%s",s->ident, 54);
          (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);               	  
	;}
    break;

  case 714:
#line 5378 "gram1.y"
    {  PTR_SYMB s;
          s = make_array((yyvsp[(1) - (4)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
        
          if(parstate != INEXEC) 
               errstr( "Illegal distributee:%s", s->ident, 312);
          else {
            if(s->attr & PROCESSORS_BIT)
               errstr( "Illegal use of PROCESSORS name %s ", s->ident, 53);  
            if(s->attr & TASK_BIT)
               errstr( "Illegal use of task array name %s ", s->ident, 71);        
            if(s->attr & ALIGN_BIT)
               errstr("A distributee may not have the ALIGN attribute:%s",s->ident, 54);
            if(!(s->attr & DVM_POINTER_BIT))
               errstr("Illegal distributee:%s", s->ident, 312);
          /*s->attr = s->attr | DISTRIBUTE_BIT;*/
	  (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s); 
          }
        
	;}
    break;

  case 715:
#line 5401 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 716:
#line 5421 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 717:
#line 5423 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 718:
#line 5427 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 719:
#line 5448 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 720:
#line 5450 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 721:
#line 5453 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 722:
#line 5462 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 723:
#line 5466 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 724:
#line 5471 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 725:
#line 5473 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 726:
#line 5475 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 727:
#line 5477 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 728:
#line 5483 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 729:
#line 5485 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 730:
#line 5489 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 731:
#line 5499 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 732:
#line 5503 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 733:
#line 5505 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 734:
#line 5510 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 735:
#line 5514 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 736:
#line 5518 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 737:
#line 5524 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 738:
#line 5534 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 739:
#line 5536 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 740:
#line 5540 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 741:
#line 5542 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 742:
#line 5544 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 743:
#line 5551 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 744:
#line 5568 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 745:
#line 5570 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 746:
#line 5574 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 747:
#line 5576 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 748:
#line 5580 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 749:
#line 5587 "gram1.y"
    { char *q;
          nioctl = 1;
          q = (yyvsp[(1) - (2)].ll_node)->entry.string_val;
          if((!strcmp(q,"shadow")) && ((yyvsp[(2) - (2)].ll_node)->variant == INT_VAL))                          (yyval.ll_node) = make_llnd(fi,SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
          else
          {  err("Illegal shadow width specification", 56);
             (yyval.ll_node) = LLNULL;
          }
        ;}
    break;

  case 750:
#line 5597 "gram1.y"
    { char *ql, *qh;
          PTR_LLND p1, p2;
          nioctl = 2;
          ql = (yyvsp[(1) - (5)].ll_node)->entry.string_val;
          qh = (yyvsp[(4) - (5)].ll_node)->entry.string_val;
          if((!strcmp(ql,"low_shadow")) && ((yyvsp[(2) - (5)].ll_node)->variant == INT_VAL) && (!strcmp(qh,"high_shadow")) && ((yyvsp[(5) - (5)].ll_node)->variant == INT_VAL)) 
              {
                 p1 = make_llnd(fi,SPEC_PAIR, (yyvsp[(1) - (5)].ll_node), (yyvsp[(2) - (5)].ll_node), SMNULL);
                 p2 = make_llnd(fi,SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                 (yyval.ll_node) = make_llnd(fi,CONS, p1, p2, SMNULL);
              } 
          else
          {  err("Illegal shadow width specification", 56);
             (yyval.ll_node) = LLNULL;
          }
        ;}
    break;

  case 751:
#line 5626 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 752:
#line 5641 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 753:
#line 5648 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 754:
#line 5666 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 755:
#line 5668 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 756:
#line 5672 "gram1.y"
    {  PTR_SYMB s;
          s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((s->attr & ALIGN_BIT)) 
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
          if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT)) 
                errstr( "Inconsistent declaration of identifier  %s", s->ident, 16); 
          else  if(s->attr & DISTRIBUTE_BIT)
               errstr( "An alignee may not have the DISTRIBUTE attribute:'%s'", s->ident,57);             else
                s->attr = s->attr | ALIGN_BIT;     
	  (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	;}
    break;

  case 757:
#line 5686 "gram1.y"
    {PTR_SYMB s;
        s = (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol;
        if(s->attr & PROCESSORS_BIT)
               errstr( "Illegal use of PROCESSORS name %s ", s->ident, 53);
        else  if(s->attr & TASK_BIT)
              errstr( "Illegal use of task array name %s ", s->ident, 71);
        else if( !(s->attr & DIMENSION_BIT) && !(s->attr & DVM_POINTER_BIT))
            errstr("The alignee %s isn't an array", s->ident, 58);
        else {
            /*  if(!(s->attr & DYNAMIC_BIT))
                 errstr("'%s' hasn't the DYNAMIC attribute", s->ident, 59);
             */
              if(!(s->attr & ALIGN_BIT) && !(s->attr & INHERIT_BIT))
                 errstr("'%s' hasn't the ALIGN attribute", s->ident, 60);
              if(s->attr & DISTRIBUTE_BIT)
                 errstr("An alignee may not have the DISTRIBUTE attribute: %s", s->ident, 57);

/*               if(s->entry.var_decl.local == IO)
 *                 errstr("An alignee may not be the dummy argument");
*/
          }
	  (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	;}
    break;

  case 758:
#line 5712 "gram1.y"
    { /* PTR_LLND r;
              if($7) {
                r = set_ll_list($6,LLNULL,EXPR_LIST);
                r = set_ll_list(r,$7,EXPR_LIST);
              }
              else
                r = $6;
              */
            (yyval.bf_node) = get_bfnd(fi,DVM_ALIGN_DIR,SMNULL,LLNULL,(yyvsp[(2) - (6)].ll_node),(yyvsp[(6) - (6)].ll_node));
           ;}
    break;

  case 759:
#line 5725 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 760:
#line 5741 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 761:
#line 5743 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 762:
#line 5746 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 763:
#line 5748 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 764:
#line 5754 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 765:
#line 5758 "gram1.y"
    { 
         /* if(parstate == INEXEC){ *for REALIGN directive*
              if (!($$ = $1->id_attr))
              {
	         $$ = make_array($1, TYNULL, LLNULL,0,LOCAL);
	     	 $$->decl = SOFT;
	      } 
          } else
             $$ = make_array($1, TYNULL, LLNULL, 0, LOCAL);
          */
          if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
          {
	       (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	       (yyval.symbol)->decl = SOFT;
	  } 
          (yyval.symbol)->attr = (yyval.symbol)->attr | ALIGN_BASE_BIT;
          if((yyval.symbol)->attr & PROCESSORS_BIT)
               errstr( "Illegal use of PROCESSORS name %s ", (yyval.symbol)->ident, 53);
          else  if((yyval.symbol)->attr & TASK_BIT)
               errstr( "Illegal use of task array name %s ", (yyval.symbol)->ident, 71);
          else
          if((parstate == INEXEC) /* for  REALIGN directive */
             &&   !((yyval.symbol)->attr & DIMENSION_BIT) && !((yyval.symbol)->attr & DVM_POINTER_BIT))
            errstr("The align-target %s isn't declared as array", (yyval.symbol)->ident, 61); 
         ;}
    break;

  case 766:
#line 5786 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 767:
#line 5788 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 768:
#line 5792 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 769:
#line 5800 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 770:
#line 5806 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 771:
#line 5809 "gram1.y"
    { PTR_SYMB s;
	             PTR_LLND q, r, p;
                     int numdim;
                     if((type_options & PROCESSORS_BIT) || (type_options & TEMPLATE_BIT)){
                       if(! explicit_shape) {
                         err("Explicit shape specification is required", 50);
		         /*$$ = BFNULL;*/
	               }
                     } 
                   /*  else {
                       if($6)
                         err("Shape specification is not permitted", 263);
                     } */

                     if(type_options & DIMENSION_BIT)
                       { p = attr_dims; numdim = attr_ndim;}
                     else
                       { p = LLNULL; numdim = 0; }
                     if((yyvsp[(6) - (6)].ll_node))          /*dimension information after the object name*/
                     { p = (yyvsp[(6) - (6)].ll_node); numdim = ndim;} /*overrides the DIMENSION attribute */
	             s = make_array((yyvsp[(5) - (6)].hash_entry), TYNULL, p, numdim, LOCAL);

                     if((type_options & COMMON_BIT) && !(type_options & TEMPLATE_BIT))
                     {
                        err("Illegal combination of attributes", 63);
                        type_options = type_options & (~COMMON_BIT);
                     }
                     if((type_options & PROCESSORS_BIT) &&((type_options & ALIGN_BIT) ||(type_options & DISTRIBUTE_BIT) ||(type_options & TEMPLATE_BIT) || (type_options & DYNAMIC_BIT) ||(type_options & SHADOW_BIT) ))
                        err("Illegal combination of attributes", 63);
                     else  if((type_options & PROCESSORS_BIT) && ((s->attr & ALIGN_BIT) ||(s->attr & DISTRIBUTE_BIT) ||(s->attr & TEMPLATE_BIT) || (s->attr & DYNAMIC_BIT) ||(s->attr & SHADOW_BIT)) )
                     {  errstr("Inconsistent declaration of  %s", s->ident, 16);
                        type_options = type_options & (~PROCESSORS_BIT);
                     }
                     else if ((s->attr & PROCESSORS_BIT) && ((type_options & ALIGN_BIT) ||(type_options & DISTRIBUTE_BIT) ||(type_options & TEMPLATE_BIT) || (type_options & DYNAMIC_BIT) ||(type_options & SHADOW_BIT))) 
                        errstr("Inconsistent declaration of  %s", s->ident, 16);
                     else if ((s->attr & INHERIT_BIT) && ((type_options & ALIGN_BIT) ||(type_options & DISTRIBUTE_BIT)))
                        errstr("Inconsistent declaration of  %s", s->ident, 16);
                     if(( s->attr & DISTRIBUTE_BIT) &&  (type_options & DISTRIBUTE_BIT))
                           errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & ALIGN_BIT) &&  (type_options & ALIGN_BIT))
                           errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & SHADOW_BIT) &&  (type_options & SHADOW_BIT))
                           errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & TEMPLATE_BIT) &&  (type_options & TEMPLATE_BIT))
                           errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & PROCESSORS_BIT) &&  (type_options & PROCESSORS_BIT))
                           errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
	             s->attr = s->attr | type_options;
                     if((yyvsp[(6) - (6)].ll_node)) s->attr = s->attr | DIMENSION_BIT;
                     if((s->attr & DISTRIBUTE_BIT) && (s->attr & ALIGN_BIT))
                       errstr("%s has the DISTRIBUTE and ALIGN attribute",s->ident, 64);
	             q = make_llnd(fi,ARRAY_REF, (yyvsp[(6) - (6)].ll_node), LLNULL, s);
	             if(p) s->type->entry.ar_decl.ranges = p;
	             r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	             (yyval.bf_node) = get_bfnd(fi,DVM_VAR_DECL, SMNULL, r, LLNULL,(yyvsp[(1) - (6)].ll_node));
	            ;}
    break;

  case 772:
#line 5866 "gram1.y"
    { PTR_SYMB s;
	             PTR_LLND q, r, p;
                     int numdim;
                    if((type_options & PROCESSORS_BIT) || (type_options & TEMPLATE_BIT)){
                       if(! explicit_shape) {
                         err("Explicit shape specification is required", 50);
		         /*$$ = BFNULL;*/
	               }
                     } 
                    /* else {
                       if($4)
                         err("Shape specification is not permitted", 263);
                     } */
                     if(type_options & DIMENSION_BIT)
                       { p = attr_dims; numdim = attr_ndim;}
                     else
                       { p = LLNULL; numdim = 0; }
                     if((yyvsp[(4) - (4)].ll_node))                   /*dimension information after the object name*/
                     { p = (yyvsp[(4) - (4)].ll_node); numdim = ndim;}/*overrides the DIMENSION attribute */
	             s = make_array((yyvsp[(3) - (4)].hash_entry), TYNULL, p, numdim, LOCAL);

                     if((type_options & COMMON_BIT) && !(type_options & TEMPLATE_BIT))
                     {
                        err("Illegal combination of attributes", 63);
                        type_options = type_options & (~COMMON_BIT);
                     }
                     if((type_options & PROCESSORS_BIT) &&((type_options & ALIGN_BIT) ||(type_options & DISTRIBUTE_BIT) ||(type_options & TEMPLATE_BIT) || (type_options & DYNAMIC_BIT) ||(type_options & SHADOW_BIT) ))
                       err("Illegal combination of attributes", 63);
                     else  if((type_options & PROCESSORS_BIT) && ((s->attr & ALIGN_BIT) ||(s->attr & DISTRIBUTE_BIT) ||(s->attr & TEMPLATE_BIT) || (s->attr & DYNAMIC_BIT) ||(s->attr & SHADOW_BIT)) )
                     {  errstr("Inconsistent declaration of identifier %s", s->ident, 16);
                        type_options = type_options & (~PROCESSORS_BIT);
                     }
                     else if ((s->attr & PROCESSORS_BIT) && ((type_options & ALIGN_BIT) ||(type_options & DISTRIBUTE_BIT) ||(type_options & TEMPLATE_BIT) || (type_options & DYNAMIC_BIT) ||(type_options & SHADOW_BIT))) 
                          errstr("Inconsistent declaration of identifier  %s", s->ident,16);
                     else if ((s->attr & INHERIT_BIT) && ((type_options & ALIGN_BIT) ||(type_options & DISTRIBUTE_BIT)))
                          errstr("Inconsistent declaration of identifier %s", s->ident, 16);
                     if(( s->attr & DISTRIBUTE_BIT) &&  (type_options & DISTRIBUTE_BIT))
                          errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & ALIGN_BIT) &&  (type_options & ALIGN_BIT))
                          errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & SHADOW_BIT) &&  (type_options & SHADOW_BIT))
                          errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & TEMPLATE_BIT) &&  (type_options & TEMPLATE_BIT))
                          errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
                     if(( s->attr & PROCESSORS_BIT) &&  (type_options & PROCESSORS_BIT))
                          errstr( "Multiple declaration of identifier  %s ", s->ident, 73);   
	             s->attr = s->attr | type_options;
                     if((yyvsp[(4) - (4)].ll_node)) s->attr = s->attr | DIMENSION_BIT;
                     if((s->attr & DISTRIBUTE_BIT) && (s->attr & ALIGN_BIT))
                           errstr("%s has the DISTRIBUTE and ALIGN attribute",s->ident, 64);
	             q = make_llnd(fi,ARRAY_REF, (yyvsp[(4) - (4)].ll_node), LLNULL, s);
	             if(p) s->type->entry.ar_decl.ranges = p;
	             r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	             add_to_lowLevelList(r, (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1);
	            ;}
    break;

  case 773:
#line 5930 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 774:
#line 5932 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 775:
#line 5935 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 776:
#line 5939 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 777:
#line 5943 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 778:
#line 5947 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 779:
#line 5964 "gram1.y"
    {
                if(! explicit_shape) {
                  err("Explicit shape specification is required", 50);
                }
                if(! (yyvsp[(3) - (4)].ll_node)) {
                  err("No shape specification", 65);
	        }
                type_opt = DIMENSION_BIT;
                attr_ndim = ndim; attr_dims = (yyvsp[(3) - (4)].ll_node);
                (yyval.ll_node) = make_llnd(fi,DIMENSION_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	       ;}
    break;

  case 780:
#line 5976 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 781:
#line 5980 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 782:
#line 5984 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 783:
#line 5994 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 784:
#line 5999 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 785:
#line 6004 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 786:
#line 6011 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 787:
#line 6019 "gram1.y"
    {ndim = 0;;}
    break;

  case 788:
#line 6020 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list(q, LLNULL, EXPR_LIST);
	       /*$$ = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);*/
	       /*$$->type = global_default;*/
	    ;}
    break;

  case 789:
#line 6031 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), q, EXPR_LIST);
            ;}
    break;

  case 790:
#line 6042 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 791:
#line 6044 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 792:
#line 6048 "gram1.y"
    {PTR_SYMB s;
           /* s = make_scalar($1,TYNULL,LOCAL);*/
            s = make_array((yyvsp[(1) - (1)].hash_entry),TYNULL,LLNULL,0,LOCAL);
            s->attr = s->attr | DVM_POINTER_BIT;
            if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
               errstr( "Inconsistent declaration of identifier %s", s->ident, 16);     
            (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL,s);
            ;}
    break;

  case 793:
#line 6059 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 794:
#line 6063 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 795:
#line 6065 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 796:
#line 6069 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 797:
#line 6080 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 798:
#line 6084 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 799:
#line 6086 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 800:
#line 6090 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 801:
#line 6102 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 802:
#line 6104 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 803:
#line 6111 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 804:
#line 6113 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 805:
#line 6117 "gram1.y"
    {  PTR_SYMB s;
              if((yyvsp[(2) - (2)].ll_node)){
                  s = make_array((yyvsp[(1) - (2)].hash_entry), global_default, (yyvsp[(2) - (2)].ll_node), ndim, LOCAL);
		  s->variant = ASYNC_ID;
                  s->attr = s->attr | DIMENSION_BIT;
                  s->type->entry.ar_decl.ranges = (yyvsp[(2) - (2)].ll_node);
                  (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(2) - (2)].ll_node), LLNULL, s);
              } else {
              s = make_local_entity((yyvsp[(1) - (2)].hash_entry), ASYNC_ID, global_default, LOCAL);
	      (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
              }
	   ;}
    break;

  case 806:
#line 6133 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 807:
#line 6143 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 808:
#line 6152 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 809:
#line 6154 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 811:
#line 6161 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 812:
#line 6164 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 813:
#line 6169 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 814:
#line 6179 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 815:
#line 6181 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 816:
#line 6185 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 817:
#line 6187 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 818:
#line 6195 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 819:
#line 6197 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 820:
#line 6201 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 821:
#line 6203 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 832:
#line 6220 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 833:
#line 6225 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 834:
#line 6229 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 835:
#line 6233 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 836:
#line 6237 "gram1.y"
    {  
            if(((yyval.symbol)=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL){
                errstr("'%s' is not declared as group", (yyvsp[(1) - (1)].hash_entry)->ident, 74);
                (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry),CONSISTENT_GROUP_NAME,global_default,LOCAL);
            } else {
                if((yyval.symbol)->variant != CONSISTENT_GROUP_NAME)
                   errstr("'%s' is not declared as group", (yyvsp[(1) - (1)].hash_entry)->ident, 74);
            }
          ;}
    break;

  case 837:
#line 6250 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 838:
#line 6254 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 839:
#line 6258 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 840:
#line 6262 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 841:
#line 6265 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 842:
#line 6267 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 843:
#line 6269 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 844:
#line 6273 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 845:
#line 6275 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 846:
#line 6279 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 847:
#line 6284 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 848:
#line 6288 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 849:
#line 6292 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 850:
#line 6294 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 851:
#line 6298 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 852:
#line 6306 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 853:
#line 6312 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 854:
#line 6318 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 855:
#line 6322 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 856:
#line 6324 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 857:
#line 6328 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 858:
#line 6330 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 859:
#line 6334 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 860:
#line 6346 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 861:
#line 6348 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 862:
#line 6352 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 863:
#line 6356 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 864:
#line 6358 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 865:
#line 6362 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 866:
#line 6364 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 867:
#line 6366 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 868:
#line 6368 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 869:
#line 6370 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 870:
#line 6372 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 871:
#line 6374 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 872:
#line 6378 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 873:
#line 6382 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 874:
#line 6386 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 875:
#line 6390 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 876:
#line 6394 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 877:
#line 6401 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 878:
#line 6407 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 879:
#line 6411 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 880:
#line 6414 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 881:
#line 6418 "gram1.y"
    { 
                  if(((yyval.symbol)=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL) {
                      errstr("'%s' is not declared as reduction group", (yyvsp[(1) - (1)].hash_entry)->ident, 69);
                      (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry),REDUCTION_GROUP_NAME,global_default,LOCAL);
                  } else {
                    if((yyval.symbol)->variant != REDUCTION_GROUP_NAME)
                      errstr("'%s' is not declared as reduction group", (yyvsp[(1) - (1)].hash_entry)->ident, 69);
                  }
                ;}
    break;

  case 882:
#line 6431 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 883:
#line 6433 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 884:
#line 6437 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 885:
#line 6439 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 886:
#line 6444 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 887:
#line 6450 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 888:
#line 6456 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 889:
#line 6462 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 890:
#line 6468 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 891:
#line 6474 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 892:
#line 6480 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6486 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 894:
#line 6492 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 895:
#line 6501 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 896:
#line 6507 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6524 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 898:
#line 6532 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 899:
#line 6540 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 900:
#line 6542 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 901:
#line 6544 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 902:
#line 6548 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 903:
#line 6552 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 904:
#line 6554 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 905:
#line 6558 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 906:
#line 6560 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 907:
#line 6568 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 908:
#line 6572 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 909:
#line 6583 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 910:
#line 6587 "gram1.y"
    { PTR_SYMB s;
         s = (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol;
         if(s->attr & PROCESSORS_BIT)
             errstr( "Illegal use of PROCESSORS name %s ", s->ident, 53);
         else if(s->attr & TASK_BIT)
             errstr( "Illegal use of task array name %s ", s->ident, 71);
         else
           if(s->type->variant != T_ARRAY) 
             errstr("'%s' isn't array", s->ident, 66);
           else 
              if((!(s->attr & DISTRIBUTE_BIT)) && (!(s->attr & ALIGN_BIT)))
               ; /*errstr("hpf.gram: %s is not distributed array", s->ident);*/
                
         (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
        ;}
    break;

  case 911:
#line 6605 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 912:
#line 6607 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 913:
#line 6611 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 914:
#line 6613 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 915:
#line 6617 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 916:
#line 6619 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 917:
#line 6623 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 918:
#line 6627 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 919:
#line 6631 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 920:
#line 6640 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 921:
#line 6644 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 922:
#line 6648 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 923:
#line 6653 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 924:
#line 6657 "gram1.y"
    {  
            if(((yyval.symbol)=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL){
                errstr("'%s' is not declared as group", (yyvsp[(1) - (1)].hash_entry)->ident, 74);
                (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry),REF_GROUP_NAME,global_default,LOCAL);
            } else {
              if((yyval.symbol)->variant != REF_GROUP_NAME)
                errstr("'%s' is not declared as group", (yyvsp[(1) - (1)].hash_entry)->ident, 74);
            }
          ;}
    break;

  case 925:
#line 6669 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 926:
#line 6671 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 927:
#line 6675 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 928:
#line 6680 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 929:
#line 6684 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 930:
#line 6686 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 931:
#line 6690 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 932:
#line 6692 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 933:
#line 6696 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 934:
#line 6701 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 935:
#line 6708 "gram1.y"
    { 
             PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (2)].hash_entry), global_int, (yyvsp[(2) - (2)].ll_node), ndim, LOCAL);
              if((yyvsp[(2) - (2)].ll_node)){
                  s->attr = s->attr | DIMENSION_BIT;
                  s->type->entry.ar_decl.ranges = (yyvsp[(2) - (2)].ll_node);
              }
              else
                  err("No dimensions in TASK directive", 75);
              if(ndim > 1)
                  errstr("Illegal rank of '%s'", s->ident, 76);
              if(s->attr & TASK_BIT)
                errstr( "Multiple declaration of identifier  %s ", s->ident, 73);
              if((s->attr & ALIGN_BIT) ||(s->attr & DISTRIBUTE_BIT) ||(s->attr & TEMPLATE_BIT) || (s->attr & DYNAMIC_BIT) ||(s->attr & SHADOW_BIT) || (s->attr & PROCESSORS_BIT)  || (s->attr & DVM_POINTER_BIT) || (s->attr & INHERIT_BIT))
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16);
              else
	        s->attr = s->attr | TASK_BIT;
    
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(2) - (2)].ll_node), LLNULL, s);	  
	    ;}
    break;

  case 936:
#line 6731 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 937:
#line 6733 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 938:
#line 6735 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 939:
#line 6737 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 940:
#line 6739 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 941:
#line 6743 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 942:
#line 6754 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 943:
#line 6758 "gram1.y"
    {  PTR_SYMB s;
              PTR_LLND q;
             /*
              s = make_array($1, TYNULL, LLNULL, 0, LOCAL);                           
	      if((parstate == INEXEC) && !(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);  
              q =  set_ll_list($3,LLNULL,EXPR_LIST);
	      $$ = make_llnd(fi,ARRAY_REF, q, LLNULL, s);
              */

              s = (yyvsp[(1) - (4)].symbol);
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, s);
	   ;}
    break;

  case 944:
#line 6773 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 945:
#line 6780 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 946:
#line 6786 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 947:
#line 6788 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 948:
#line 6792 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 949:
#line 6796 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 950:
#line 6804 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 951:
#line 6808 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 952:
#line 6812 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 953:
#line 6820 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 954:
#line 6825 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 955:
#line 6839 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 956:
#line 6841 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 957:
#line 6845 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 958:
#line 6847 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 959:
#line 6856 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 960:
#line 6858 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 961:
#line 6860 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 962:
#line 6862 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 963:
#line 6898 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 964:
#line 6902 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 965:
#line 6906 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 966:
#line 6910 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 967:
#line 6914 "gram1.y"
    {  
            if(((yyval.symbol)=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL) {
                errstr("'%s' is not declared as ASYNCID", (yyvsp[(1) - (1)].hash_entry)->ident, 115);
                (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry),ASYNC_ID,global_default,LOCAL);
            } else {
              if((yyval.symbol)->variant != ASYNC_ID)
                errstr("'%s' is not declared as ASYNCID", (yyvsp[(1) - (1)].hash_entry)->ident, 115);
            }
     ;}
    break;

  case 968:
#line 6926 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 969:
#line 6928 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 970:
#line 6932 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 971:
#line 6935 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 972:
#line 6937 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 973:
#line 6941 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 974:
#line 6946 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 975:
#line 6953 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 976:
#line 6956 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 977:
#line 6964 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 978:
#line 6968 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 979:
#line 6972 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 980:
#line 6975 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 981:
#line 6982 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 982:
#line 6986 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 983:
#line 6990 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 984:
#line 6994 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 985:
#line 6998 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 986:
#line 7002 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 987:
#line 7005 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 988:
#line 7007 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 989:
#line 7011 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 990:
#line 7013 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 991:
#line 7015 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 992:
#line 7019 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 993:
#line 7023 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 if(!((yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->attr & TEMPLATE_BIT))
                    errstr("'%s' isn't TEMPLATE", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 628);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 /*$$->type = $1->type->entry.ar_decl.base_type;*/
               ;}
    break;

  case 994:
#line 7035 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 995:
#line 7037 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 996:
#line 7041 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 997:
#line 7043 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 998:
#line 7047 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 999:
#line 7049 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1000:
#line 7053 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1001:
#line 7057 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1002:
#line 7063 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1003:
#line 7075 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1004:
#line 7077 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1005:
#line 7081 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1006:
#line 7083 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1007:
#line 7087 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1008:
#line 7095 "gram1.y"
    { 
                PTR_LLND q;
                if((yyvsp[(16) - (16)].ll_node))
                  q = make_llnd(fi,ARRAY_OP, (yyvsp[(14) - (16)].ll_node), (yyvsp[(16) - (16)].ll_node), SMNULL);
                else
                  q = (yyvsp[(14) - (16)].ll_node);                  
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_CREATE_DIR,SMNULL,(yyvsp[(3) - (16)].ll_node),(yyvsp[(8) - (16)].ll_node),q); 
              ;}
    break;

  case 1009:
#line 7106 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1010:
#line 7108 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1011:
#line 7110 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1012:
#line 7114 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1013:
#line 7118 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1014:
#line 7120 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1015:
#line 7128 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1043:
#line 7161 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1044:
#line 7167 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1045:
#line 7173 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1046:
#line 7179 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1047:
#line 7185 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1048:
#line 7189 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1058:
#line 7206 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1059:
#line 7211 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1060:
#line 7216 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1061:
#line 7222 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1062:
#line 7228 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1063:
#line 7234 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1064:
#line 7239 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1065:
#line 7245 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1066:
#line 7251 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1067:
#line 7257 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1068:
#line 7264 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1069:
#line 7270 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1070:
#line 7276 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1071:
#line 7283 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1073:
#line 7289 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1074:
#line 7295 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1075:
#line 7302 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1076:
#line 7308 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1077:
#line 7314 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1078:
#line 7320 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1079:
#line 7326 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1080:
#line 7332 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1081:
#line 7338 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1082:
#line 7344 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1083:
#line 7350 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1084:
#line 7356 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1085:
#line 7362 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1086:
#line 7368 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1087:
#line 7378 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1088:
#line 7383 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1089:
#line 7389 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1090:
#line 7393 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1095:
#line 7405 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1096:
#line 7413 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1097:
#line 7419 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1098:
#line 7425 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1099:
#line 7430 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1100:
#line 7436 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1101:
#line 7443 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1102:
#line 7449 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1103:
#line 7453 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1110:
#line 7467 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1111:
#line 7476 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1112:
#line 7480 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1113:
#line 7486 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1114:
#line 7493 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1115:
#line 7500 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1116:
#line 7507 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1117:
#line 7516 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1118:
#line 7522 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1119:
#line 7528 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1120:
#line 7532 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1123:
#line 7542 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1124:
#line 7548 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1125:
#line 7554 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1126:
#line 7558 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1129:
#line 7569 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1130:
#line 7575 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1131:
#line 7581 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1132:
#line 7586 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1133:
#line 7594 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1134:
#line 7600 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1135:
#line 7605 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1136:
#line 7612 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1137:
#line 7616 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1149:
#line 7636 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1150:
#line 7641 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1151:
#line 7646 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1152:
#line 7653 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1153:
#line 7658 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1154:
#line 7664 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1155:
#line 7670 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1156:
#line 7675 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1157:
#line 7680 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1158:
#line 7685 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1159:
#line 7689 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1160:
#line 7694 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1161:
#line 7699 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1162:
#line 7703 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1163:
#line 7708 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1164:
#line 7712 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1165:
#line 7718 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1166:
#line 7723 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1167:
#line 7729 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1168:
#line 7734 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1169:
#line 7740 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1170:
#line 7750 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1171:
#line 7754 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1172:
#line 7758 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1173:
#line 7762 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1174:
#line 7767 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1175:
#line 7770 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1182:
#line 7783 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1183:
#line 7787 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1184:
#line 7791 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1185:
#line 7793 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1186:
#line 7795 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1187:
#line 7799 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1188:
#line 7801 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1189:
#line 7803 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1190:
#line 7807 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1191:
#line 7809 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1192:
#line 7813 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1193:
#line 7815 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1194:
#line 7819 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1195:
#line 7822 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1196:
#line 7825 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1197:
#line 7830 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1198:
#line 7832 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1199:
#line 7834 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1200:
#line 7836 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1201:
#line 7838 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1202:
#line 7842 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1203:
#line 7846 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1204:
#line 7851 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1205:
#line 7855 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1206:
#line 7857 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1207:
#line 7861 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1208:
#line 7863 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1209:
#line 7867 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1210:
#line 7871 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1216:
#line 7882 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1217:
#line 7886 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1218:
#line 7890 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1219:
#line 7894 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1220:
#line 7898 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1221:
#line 7902 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1222:
#line 7904 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1225:
#line 7912 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1226:
#line 7916 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1227:
#line 7920 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1228:
#line 7922 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1232:
#line 7932 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1233:
#line 7936 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1234:
#line 7940 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1235:
#line 7944 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1236:
#line 7946 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1237:
#line 7950 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1238:
#line 7954 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;


/* Line 1267 of yacc.c.  */
#line 13616 "gram1.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



