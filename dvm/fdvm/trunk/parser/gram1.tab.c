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
#define YYLAST   5564

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  338
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  514
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1239
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2436

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
    2172,  2176,  2178,  2183,  2187,  2189,  2193,  2195,  2199,  2204,
    2206,  2211,  2216,  2221,  2225,  2229,  2231,  2235,  2239,  2241,
    2245,  2249,  2251,  2255,  2259,  2261,  2265,  2266,  2272,  2279,
    2288,  2290,  2294,  2296,  2298,  2300,  2305,  2307,  2308,  2311,
    2315,  2318,  2323,  2324,  2326,  2332,  2337,  2344,  2349,  2351,
    2356,  2361,  2363,  2370,  2372,  2376,  2378,  2380,  2385,  2387,
    2389,  2393,  2395,  2397,  2401,  2403,  2404,  2406,  2409,  2413,
    2415,  2418,  2424,  2429,  2434,  2441,  2443,  2447,  2449,  2451,
    2458,  2463,  2465,  2469,  2471,  2473,  2475,  2477,  2479,  2483,
    2485,  2487,  2489,  2496,  2501,  2503,  2508,  2510,  2512,  2514,
    2516,  2521,  2524,  2532,  2534,  2539,  2541,  2543,  2555,  2556,
    2559,  2563,  2565,  2569,  2571,  2575,  2577,  2581,  2583,  2587,
    2589,  2593,  2595,  2599,  2608,  2610,  2614,  2617,  2620,  2628,
    2630,  2634,  2636,  2640,  2642,  2647,  2649,  2653,  2655,  2657,
    2658,  2660,  2662,  2665,  2667,  2669,  2671,  2673,  2675,  2677,
    2679,  2681,  2683,  2685,  2694,  2701,  2710,  2717,  2719,  2726,
    2733,  2740,  2747,  2749,  2753,  2759,  2761,  2765,  2774,  2781,
    2788,  2793,  2799,  2805,  2808,  2811,  2812,  2814,  2818,  2820,
    2825,  2833,  2835,  2839,  2843,  2845,  2849,  2855,  2859,  2863,
    2865,  2869,  2871,  2873,  2877,  2881,  2885,  2889,  2900,  2909,
    2920,  2921,  2922,  2924,  2927,  2932,  2937,  2944,  2946,  2948,
    2950,  2952,  2954,  2956,  2958,  2960,  2962,  2964,  2966,  2973,
    2978,  2983,  2987,  2997,  2999,  3001,  3005,  3007,  3013,  3019,
    3029,  3030,  3032,  3034,  3038,  3042,  3046,  3050,  3054,  3061,
    3065,  3069,  3073,  3077,  3085,  3091,  3093,  3095,  3099,  3104,
    3106,  3108,  3112,  3114,  3116,  3120,  3124,  3127,  3131,  3136,
    3141,  3147,  3153,  3155,  3158,  3163,  3168,  3173,  3174,  3176,
    3179,  3187,  3194,  3198,  3202,  3210,  3216,  3218,  3222,  3224,
    3229,  3232,  3236,  3240,  3245,  3252,  3256,  3259,  3263,  3265,
    3267,  3272,  3278,  3282,  3289,  3292,  3297,  3300,  3302,  3306,
    3310,  3311,  3313,  3316,  3319,  3322,  3325,  3335,  3341,  3343,
    3347,  3350,  3353,  3356,  3366,  3371,  3373,  3377,  3379,  3381,
    3384,  3385,  3393,  3395,  3400,  3402,  3406,  3408,  3410,  3412,
    3429,  3430,  3434,  3438,  3442,  3446,  3453,  3463,  3465,  3467,
    3469,  3471,  3473,  3475,  3477,  3479,  3481,  3483,  3485,  3487,
    3489,  3491,  3493,  3495,  3497,  3499,  3501,  3503,  3505,  3507,
    3509,  3511,  3513,  3515,  3517,  3520,  3523,  3528,  3532,  3537,
    3543,  3545,  3547,  3549,  3551,  3553,  3555,  3557,  3559,  3561,
    3567,  3570,  3573,  3576,  3579,  3582,  3588,  3590,  3592,  3594,
    3599,  3604,  3609,  3614,  3616,  3618,  3620,  3622,  3624,  3626,
    3628,  3630,  3632,  3634,  3636,  3638,  3640,  3642,  3644,  3649,
    3653,  3658,  3664,  3666,  3668,  3670,  3672,  3677,  3681,  3684,
    3689,  3693,  3698,  3702,  3707,  3713,  3715,  3717,  3719,  3721,
    3723,  3725,  3727,  3735,  3741,  3743,  3745,  3747,  3749,  3754,
    3758,  3763,  3769,  3771,  3773,  3778,  3782,  3787,  3793,  3795,
    3797,  3800,  3802,  3805,  3810,  3814,  3819,  3823,  3828,  3834,
    3836,  3838,  3840,  3842,  3844,  3846,  3848,  3850,  3852,  3854,
    3856,  3859,  3864,  3868,  3871,  3876,  3880,  3883,  3887,  3890,
    3893,  3896,  3899,  3902,  3905,  3909,  3912,  3918,  3921,  3927,
    3930,  3936,  3938,  3940,  3944,  3948,  3949,  3950,  3952,  3954,
    3956,  3958,  3960,  3962,  3966,  3969,  3975,  3980,  3983,  3989,
    3994,  3997,  4000,  4002,  4004,  4008,  4011,  4014,  4017,  4022,
    4027,  4032,  4037,  4042,  4047,  4049,  4051,  4053,  4057,  4060,
    4063,  4065,  4067,  4069,  4071,  4073,  4075,  4077,  4082,  4087,
    4092,  4095,  4097,  4099,  4103,  4105,  4107,  4113,  4119,  4121,
    4125,  4127,  4129,  4131,  4137,  4143,  4149,  4151,  4155,  4158
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
       8,   572,    -1,   477,    -1,   477,     7,   477,    -1,     7,
      15,   476,    21,    -1,   349,    -1,   259,   471,   349,   454,
      -1,   303,   471,   349,   454,    -1,   574,     8,   349,   454,
      -1,   136,   471,   576,    -1,   575,     8,   576,    -1,   349,
      -1,   211,   471,   578,    -1,   577,     8,   578,    -1,   349,
      -1,   205,   471,   580,    -1,   579,     8,   580,    -1,   349,
      -1,    70,   471,   582,    -1,   581,     8,   582,    -1,   349,
      -1,   175,   349,   454,    -1,    -1,    88,   471,   588,   591,
     583,    -1,   204,   533,   588,   592,   594,   583,    -1,   204,
     533,   592,   594,   583,     7,     7,   586,    -1,   587,    -1,
     586,     8,   587,    -1,   588,    -1,   589,    -1,   349,    -1,
     349,    15,   476,    21,    -1,   349,    -1,    -1,   592,   594,
      -1,    15,   593,    21,    -1,   594,   595,    -1,   593,     8,
     594,   595,    -1,    -1,    58,    -1,    58,    15,   554,   608,
      21,    -1,   126,    15,   596,    21,    -1,   258,    15,   596,
       8,   477,    21,    -1,   165,    15,   477,    21,    -1,     5,
      -1,   137,    15,   596,    21,    -1,    86,    15,   597,    21,
      -1,   349,    -1,    15,   598,    21,   356,   255,   600,    -1,
     599,    -1,   598,     8,   599,    -1,   477,    -1,   601,    -1,
     601,    15,   602,    21,    -1,   349,    -1,   603,    -1,   602,
       8,   603,    -1,   477,    -1,   747,    -1,    40,   604,   605,
      -1,   349,    -1,    -1,   606,    -1,    17,   607,    -1,   605,
      17,   607,    -1,   477,    -1,   545,   477,    -1,   545,   477,
       8,   545,   477,    -1,    43,   471,   612,   614,    -1,   199,
     533,   613,   614,    -1,   199,   533,   614,     7,     7,   611,
      -1,   613,    -1,   611,     8,   613,    -1,   349,    -1,   480,
      -1,    15,   619,    21,   356,   255,   615,    -1,   618,    15,
     616,    21,    -1,   617,    -1,   616,     8,   617,    -1,   477,
      -1,     5,    -1,   495,    -1,   349,    -1,   620,    -1,   619,
       8,   620,    -1,   349,    -1,     5,    -1,     7,    -1,   622,
       7,     7,   471,   349,   454,    -1,   621,     8,   349,   454,
      -1,   623,    -1,   622,     8,   356,   623,    -1,    82,    -1,
     259,    -1,   303,    -1,    94,    -1,    87,    15,   455,    21,
      -1,   228,   570,    -1,    43,    15,   619,    21,   356,   255,
     615,    -1,    43,    -1,    88,   592,   594,   583,    -1,    88,
      -1,    67,    -1,   380,     8,   356,    93,   471,    15,   625,
      21,     7,     7,   627,    -1,    -1,   626,     7,    -1,   625,
       8,     7,    -1,   628,    -1,   627,     8,   628,    -1,   349,
      -1,   127,   471,   630,    -1,   631,    -1,   630,     8,   631,
      -1,   349,    -1,    74,   471,   633,    -1,   634,    -1,   633,
       8,   634,    -1,   349,    -1,    51,   471,   636,    -1,    51,
     471,     8,   356,    67,     7,     7,   636,    -1,   637,    -1,
     636,     8,   637,    -1,   349,   454,    -1,   168,   533,    -1,
     182,   533,    15,   640,    21,   642,   646,    -1,   641,    -1,
     640,     8,   641,    -1,   480,    -1,   594,   173,   643,    -1,
     594,    -1,   480,    15,   644,    21,    -1,   645,    -1,   644,
       8,   645,    -1,   477,    -1,     5,    -1,    -1,   647,    -1,
     648,    -1,   647,   648,    -1,   652,    -1,   672,    -1,   680,
      -1,   649,    -1,   657,    -1,   659,    -1,   658,    -1,   650,
      -1,   653,    -1,   654,    -1,     8,   356,   209,    15,   695,
       7,   696,    21,    -1,     8,   356,   209,    15,   696,    21,
      -1,     8,   356,    71,    15,   651,     7,   696,    21,    -1,
       8,   356,    71,    15,   696,    21,    -1,   349,    -1,     8,
     356,   169,    15,   656,    21,    -1,     8,   356,   282,    15,
     656,    21,    -1,     8,   356,   191,    15,   656,    21,    -1,
       8,   356,   320,    15,   655,    21,    -1,   477,    -1,   477,
       8,   477,    -1,   477,     8,   477,     8,   477,    -1,   481,
      -1,   656,     8,   481,    -1,     8,   356,   135,    15,   695,
       7,   713,    21,    -1,     8,   356,   135,    15,   713,    21,
      -1,     8,   356,   229,    15,   477,    21,    -1,     8,   356,
      41,   660,    -1,     8,   356,    41,   660,   660,    -1,    15,
     594,   661,   662,    21,    -1,   148,     7,    -1,   180,     7,
      -1,    -1,   663,    -1,   662,     8,   663,    -1,   685,    -1,
     685,    15,   664,    21,    -1,   685,    15,   664,    21,    15,
     666,    21,    -1,   665,    -1,   664,     8,   665,    -1,   477,
       7,   477,    -1,   667,    -1,   666,     8,   667,    -1,   668,
       7,   669,     7,   670,    -1,   668,     7,   669,    -1,   668,
       7,   670,    -1,   668,    -1,   669,     7,   670,    -1,   669,
      -1,   670,    -1,   356,   217,   671,    -1,   356,   157,   671,
      -1,   356,   128,   671,    -1,    15,   475,    21,    -1,     8,
     356,   208,    15,   673,   677,   674,     8,   676,    21,    -1,
       8,   356,   208,    15,   673,   677,   674,    21,    -1,     8,
     356,   208,    15,   673,   675,   674,     7,   676,    21,    -1,
      -1,    -1,   349,    -1,   356,   677,    -1,   676,     8,   356,
     677,    -1,   678,    15,   481,    21,    -1,   679,    15,   656,
       8,   477,    21,    -1,   234,    -1,   192,    -1,   162,    -1,
     159,    -1,    35,    -1,    22,    -1,    24,    -1,    33,    -1,
     247,    -1,   158,    -1,   161,    -1,     8,   356,   223,    15,
     682,    21,    -1,     8,   356,   224,   681,    -1,     8,   356,
     226,   681,    -1,     8,   356,   221,    -1,     8,   356,   221,
      15,   685,    15,   571,    21,    21,    -1,   349,    -1,   683,
      -1,   682,     8,   683,    -1,   685,    -1,   685,    15,   684,
      78,    21,    -1,   685,    15,   684,   571,    21,    -1,   685,
      15,   684,   571,    21,    15,   356,    78,    21,    -1,    -1,
     480,    -1,   685,    -1,   686,     8,   685,    -1,   225,   533,
     681,    -1,   224,   533,   681,    -1,   227,   533,   681,    -1,
     226,   533,   681,    -1,   222,   533,   681,    15,   682,    21,
      -1,   206,   533,   675,    -1,   207,   533,   675,    -1,    72,
     533,   651,    -1,    73,   533,   651,    -1,   210,   533,    15,
     695,     7,   696,    21,    -1,   210,   533,    15,   696,    21,
      -1,   349,    -1,   697,    -1,   696,     8,   697,    -1,   685,
      15,   698,    21,    -1,   685,    -1,   699,    -1,   698,     8,
     699,    -1,   477,    -1,     7,    -1,   237,   471,   701,    -1,
     700,     8,   701,    -1,   349,   454,    -1,   238,   533,   703,
      -1,   238,   533,   703,   672,    -1,   238,   533,   703,   650,
      -1,   238,   533,   703,   672,   650,    -1,   238,   533,   703,
     650,   672,    -1,   349,    -1,   111,   533,    -1,   703,    15,
     477,    21,    -1,   703,    15,   495,    21,    -1,   174,   533,
     482,   707,    -1,    -1,   652,    -1,   109,   533,    -1,   160,
     533,   705,   356,   175,   590,   454,    -1,   160,   533,   705,
     356,   321,   481,    -1,   189,   533,   695,    -1,   212,   533,
     695,    -1,   135,   533,    15,   695,     7,   713,    21,    -1,
     135,   533,    15,   713,    21,    -1,   714,    -1,   713,     8,
     714,    -1,   685,    -1,   685,    15,   476,    21,    -1,   134,
     533,    -1,   134,   533,   652,    -1,   134,   533,   716,    -1,
     134,   533,   652,   716,    -1,     8,   356,   208,    15,   656,
      21,    -1,    50,   533,   721,    -1,    99,   533,    -1,    52,
     533,   721,    -1,   349,    -1,   720,    -1,   720,    15,   476,
      21,    -1,   120,   533,   481,    26,   481,    -1,    83,   533,
     726,    -1,    83,   533,   726,    15,   724,    21,    -1,   554,
     725,    -1,   724,     8,   554,   725,    -1,   545,   477,    -1,
     149,    -1,   100,   533,   726,    -1,   146,   533,   729,    -1,
      -1,   477,    -1,   101,   533,    -1,   241,   533,    -1,   242,
     533,    -1,    56,   533,    -1,    65,   533,   554,    15,   530,
      21,   390,   472,   656,    -1,   322,   533,    15,   736,    21,
      -1,   737,    -1,   736,     8,   737,    -1,   356,   315,    -1,
     356,   318,    -1,   356,   182,    -1,   220,   533,    15,   739,
      26,   607,    21,   594,   742,    -1,   480,    15,   740,    21,
      -1,   741,    -1,   740,     8,   741,    -1,   597,    -1,   747,
      -1,   132,   686,    -1,    -1,   153,   533,    15,   480,    18,
     744,    21,    -1,   480,    -1,   480,    15,   745,    21,    -1,
     746,    -1,   745,     8,   746,    -1,   747,    -1,     7,    -1,
       5,    -1,   329,   533,   477,     8,   356,   334,    15,   656,
      21,     8,   356,   333,    15,   476,    21,   749,    -1,    -1,
       8,   356,   182,    -1,     8,   356,   318,    -1,   330,   533,
     477,    -1,   331,   533,   477,    -1,   331,   533,   477,     8,
     356,   315,    -1,   332,   533,   477,     8,   356,   335,    15,
     480,    21,    -1,   804,    -1,   757,    -1,   756,    -1,   774,
      -1,   777,    -1,   778,    -1,   779,    -1,   780,    -1,   786,
      -1,   789,    -1,   794,    -1,   795,    -1,   796,    -1,   799,
      -1,   800,    -1,   801,    -1,   802,    -1,   803,    -1,   805,
      -1,   806,    -1,   807,    -1,   808,    -1,   809,    -1,   810,
      -1,   811,    -1,   812,    -1,   813,    -1,   268,   533,    -1,
     275,   533,    -1,   291,   533,   594,   758,    -1,   291,   533,
     594,    -1,   528,   594,   759,   594,    -1,   758,   528,   594,
     759,   594,    -1,   761,    -1,   770,    -1,   765,    -1,   766,
      -1,   762,    -1,   763,    -1,   764,    -1,   768,    -1,   769,
      -1,   816,    15,   817,   815,    21,    -1,   191,   760,    -1,
     282,   760,    -1,   285,   760,    -1,   265,   760,    -1,   299,
     760,    -1,    84,    15,   356,   767,    21,    -1,   191,    -1,
     299,    -1,   288,    -1,   304,    15,   477,    21,    -1,   289,
      15,   477,    21,    -1,   208,    15,   771,    21,    -1,   594,
     773,     7,   772,    -1,   656,    -1,    17,    -1,    16,    -1,
       5,    -1,    37,    -1,   162,    -1,   159,    -1,    35,    -1,
      22,    -1,    24,    -1,    33,    -1,   305,    -1,   306,    -1,
     307,    -1,   247,    -1,   297,   533,   594,   775,    -1,   297,
     533,   594,    -1,   528,   594,   776,   594,    -1,   775,   528,
     594,   776,   594,    -1,   761,    -1,   770,    -1,   762,    -1,
     763,    -1,   279,   533,   594,   793,    -1,   279,   533,   594,
      -1,   296,   533,    -1,   269,   533,   594,   781,    -1,   269,
     533,   594,    -1,   272,   533,   594,   793,    -1,   272,   533,
     594,    -1,   528,   594,   782,   594,    -1,   781,   528,   594,
     782,   594,    -1,   761,    -1,   770,    -1,   762,    -1,   763,
      -1,   784,    -1,   783,    -1,   290,    -1,   298,    15,   356,
     785,     8,   477,    21,    -1,   298,    15,   356,   785,    21,
      -1,   230,    -1,    94,    -1,   284,    -1,   295,    -1,   300,
     533,   594,   787,    -1,   300,   533,   594,    -1,   528,   594,
     788,   594,    -1,   787,   528,   594,   788,   594,    -1,   761,
      -1,   762,    -1,   280,   533,   594,   790,    -1,   280,   533,
     594,    -1,   528,   594,   791,   594,    -1,   790,   528,   594,
     791,   594,    -1,   793,    -1,   792,    -1,   266,   760,    -1,
     287,    -1,   302,   533,    -1,   281,   533,   594,   793,    -1,
     281,   533,   594,    -1,   292,   533,   594,   797,    -1,   292,
     533,   594,    -1,   528,   594,   798,   594,    -1,   797,   528,
     594,   798,   594,    -1,   761,    -1,   770,    -1,   765,    -1,
     766,    -1,   762,    -1,   763,    -1,   764,    -1,   768,    -1,
     769,    -1,   784,    -1,   783,    -1,   276,   533,    -1,   293,
     533,   594,   758,    -1,   293,   533,   594,    -1,   277,   533,
      -1,   294,   533,   594,   758,    -1,   294,   533,   594,    -1,
     278,   533,    -1,   301,   471,   760,    -1,   286,   533,    -1,
     273,   533,    -1,   290,   533,    -1,   274,   533,    -1,   264,
     533,    -1,   263,   533,    -1,   283,   533,   760,    -1,   283,
     533,    -1,   267,   533,    15,   480,    21,    -1,   267,   533,
      -1,   271,   533,    15,   480,    21,    -1,   271,   533,    -1,
      37,   349,   816,    37,   817,    -1,   814,    -1,   480,    -1,
     815,     8,   814,    -1,   815,     8,   480,    -1,    -1,    -1,
     819,    -1,   832,    -1,   820,    -1,   833,    -1,   821,    -1,
     822,    -1,   308,   533,   823,    -1,   310,   533,    -1,   312,
     533,    15,   829,    21,    -1,   312,   533,    15,    21,    -1,
     312,   533,    -1,   313,   533,    15,   829,    21,    -1,   313,
     533,    15,    21,    -1,   313,   533,    -1,   356,   357,    -1,
     824,    -1,   825,    -1,   824,     8,   825,    -1,   356,   826,
      -1,   356,   828,    -1,   356,   827,    -1,   147,    15,   829,
      21,    -1,   148,    15,   829,    21,    -1,   180,    15,   829,
      21,    -1,   318,    15,   829,    21,    -1,   319,    15,   829,
      21,    -1,   314,    15,   830,    21,    -1,   315,    -1,   656,
      -1,   831,    -1,   830,     8,   831,    -1,   356,   316,    -1,
     356,   317,    -1,   309,    -1,   311,    -1,   835,    -1,   836,
      -1,   837,    -1,   838,    -1,   839,    -1,   323,    15,   840,
      21,    -1,   324,    15,   844,    21,    -1,   325,    15,   849,
      21,    -1,   327,   851,    -1,   328,    -1,   841,    -1,   840,
       8,   841,    -1,   842,    -1,   843,    -1,   356,   208,    15,
     676,    21,    -1,   356,   191,    15,   656,    21,    -1,   845,
      -1,   844,     8,   845,    -1,   846,    -1,   847,    -1,   848,
      -1,   356,   228,    15,   682,    21,    -1,   356,    41,    15,
     682,    21,    -1,   356,   209,    15,   696,    21,    -1,   850,
      -1,   849,     8,   850,    -1,   356,   326,    -1,   349,    -1
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
    5045,  5049,  5060,  5071,  5075,  5077,  5081,  5083,  5085,  5100,
    5112,  5132,  5152,  5174,  5180,  5189,  5197,  5203,  5211,  5218,
    5224,  5233,  5237,  5243,  5251,  5265,  5279,  5284,  5300,  5315,
    5343,  5345,  5349,  5351,  5355,  5384,  5407,  5428,  5429,  5433,
    5454,  5456,  5460,  5468,  5472,  5477,  5479,  5481,  5483,  5489,
    5491,  5495,  5505,  5509,  5511,  5516,  5520,  5524,  5530,  5540,
    5542,  5546,  5548,  5550,  5557,  5575,  5576,  5580,  5582,  5586,
    5593,  5603,  5632,  5647,  5654,  5672,  5674,  5678,  5692,  5718,
    5731,  5747,  5749,  5752,  5754,  5760,  5764,  5792,  5794,  5798,
    5806,  5812,  5815,  5872,  5936,  5938,  5941,  5945,  5949,  5953,
    5970,  5982,  5986,  5990,  6000,  6005,  6010,  6017,  6026,  6026,
    6037,  6048,  6050,  6054,  6065,  6069,  6071,  6075,  6086,  6090,
    6092,  6096,  6108,  6110,  6117,  6119,  6123,  6139,  6147,  6158,
    6160,  6164,  6167,  6170,  6175,  6185,  6187,  6191,  6193,  6202,
    6203,  6207,  6209,  6214,  6215,  6216,  6217,  6218,  6219,  6220,
    6221,  6222,  6223,  6226,  6231,  6235,  6239,  6243,  6256,  6260,
    6264,  6268,  6271,  6273,  6275,  6279,  6281,  6285,  6290,  6294,
    6298,  6300,  6304,  6312,  6318,  6325,  6328,  6330,  6334,  6336,
    6340,  6352,  6354,  6358,  6362,  6364,  6368,  6370,  6372,  6374,
    6376,  6378,  6380,  6384,  6388,  6392,  6396,  6400,  6407,  6413,
    6418,  6421,  6424,  6437,  6439,  6443,  6445,  6450,  6456,  6462,
    6468,  6474,  6480,  6486,  6492,  6498,  6507,  6513,  6530,  6532,
    6540,  6548,  6550,  6554,  6558,  6560,  6564,  6566,  6574,  6578,
    6590,  6593,  6611,  6613,  6617,  6619,  6623,  6625,  6629,  6633,
    6637,  6646,  6650,  6654,  6659,  6663,  6675,  6677,  6681,  6686,
    6690,  6692,  6696,  6698,  6702,  6707,  6714,  6737,  6739,  6741,
    6743,  6745,  6749,  6760,  6764,  6779,  6786,  6793,  6794,  6798,
    6802,  6810,  6814,  6818,  6826,  6831,  6845,  6847,  6851,  6853,
    6862,  6864,  6866,  6868,  6904,  6908,  6912,  6916,  6920,  6932,
    6934,  6938,  6941,  6943,  6947,  6952,  6959,  6962,  6970,  6974,
    6979,  6981,  6988,  6992,  6996,  7000,  7004,  7008,  7011,  7013,
    7017,  7019,  7021,  7025,  7029,  7041,  7043,  7047,  7049,  7053,
    7056,  7059,  7063,  7069,  7081,  7083,  7087,  7089,  7093,  7101,
    7113,  7114,  7116,  7120,  7124,  7126,  7134,  7137,  7139,  7140,
    7141,  7142,  7143,  7144,  7145,  7146,  7147,  7148,  7149,  7150,
    7151,  7152,  7153,  7154,  7155,  7156,  7157,  7158,  7159,  7160,
    7161,  7162,  7163,  7164,  7167,  7173,  7179,  7185,  7191,  7195,
    7201,  7202,  7203,  7204,  7205,  7206,  7207,  7208,  7209,  7212,
    7217,  7222,  7228,  7234,  7240,  7245,  7251,  7257,  7263,  7270,
    7276,  7282,  7289,  7293,  7295,  7301,  7308,  7314,  7320,  7326,
    7332,  7338,  7344,  7350,  7356,  7362,  7368,  7374,  7384,  7389,
    7395,  7399,  7405,  7406,  7407,  7408,  7411,  7419,  7425,  7431,
    7436,  7442,  7449,  7455,  7459,  7465,  7466,  7467,  7468,  7469,
    7470,  7473,  7482,  7486,  7492,  7499,  7506,  7513,  7522,  7528,
    7534,  7538,  7544,  7545,  7548,  7554,  7560,  7564,  7571,  7572,
    7575,  7581,  7587,  7592,  7600,  7606,  7611,  7618,  7622,  7628,
    7629,  7630,  7631,  7632,  7633,  7634,  7635,  7636,  7637,  7638,
    7642,  7647,  7652,  7659,  7664,  7670,  7676,  7681,  7686,  7691,
    7695,  7700,  7705,  7709,  7714,  7718,  7724,  7729,  7735,  7740,
    7746,  7756,  7760,  7764,  7768,  7774,  7777,  7781,  7782,  7783,
    7784,  7785,  7786,  7789,  7793,  7797,  7799,  7801,  7805,  7807,
    7809,  7813,  7815,  7819,  7821,  7825,  7828,  7831,  7836,  7838,
    7840,  7842,  7844,  7848,  7852,  7857,  7861,  7863,  7867,  7869,
    7873,  7877,  7881,  7882,  7883,  7884,  7885,  7888,  7892,  7896,
    7900,  7904,  7908,  7910,  7914,  7915,  7918,  7922,  7926,  7928,
    7932,  7933,  7934,  7938,  7942,  7946,  7950,  7952,  7956,  7960
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
     567,   568,   569,   570,   571,   571,   572,   572,   572,   573,
     574,   574,   574,   575,   575,   576,   577,   577,   578,   579,
     579,   580,   581,   581,   582,   583,   583,   584,   585,   585,
     586,   586,   587,   587,   588,   589,   590,   591,   591,   592,
     593,   593,   594,   595,   595,   595,   595,   595,   595,   595,
     595,   596,   597,   598,   598,   599,   600,   600,   601,   602,
     602,   603,   603,   603,   604,   605,   605,   606,   606,   607,
     608,   608,   609,   610,   610,   611,   611,   612,   613,   614,
     615,   616,   616,   617,   617,   617,   618,   619,   619,   620,
     620,   620,   621,   621,   622,   622,   623,   623,   623,   623,
     623,   623,   623,   623,   623,   623,   623,   624,   626,   625,
     625,   627,   627,   628,   629,   630,   630,   631,   632,   633,
     633,   634,   635,   635,   636,   636,   637,   638,   639,   640,
     640,   641,   642,   642,   643,   644,   644,   645,   645,   646,
     646,   647,   647,   648,   648,   648,   648,   648,   648,   648,
     648,   648,   648,   649,   649,   650,   650,   651,   652,   652,
     653,   654,   655,   655,   655,   656,   656,   657,   657,   658,
     659,   659,   660,   661,   661,   661,   662,   662,   663,   663,
     663,   664,   664,   665,   666,   666,   667,   667,   667,   667,
     667,   667,   667,   668,   669,   670,   671,   672,   672,   672,
     673,   674,   675,   676,   676,   677,   677,   678,   678,   678,
     678,   678,   678,   678,   678,   678,   679,   679,   680,   680,
     680,   680,   680,   681,   682,   682,   683,   683,   683,   683,
     684,   685,   686,   686,   687,   687,   688,   688,   689,   690,
     691,   692,   693,   694,   694,   695,   696,   696,   697,   697,
     698,   698,   699,   699,   700,   700,   701,   702,   702,   702,
     702,   702,   703,   704,   705,   705,   706,   707,   707,   708,
     709,   709,   710,   711,   712,   712,   713,   713,   714,   714,
     715,   715,   715,   715,   716,   717,   718,   719,   720,   721,
     721,   722,   723,   723,   724,   724,   725,   726,   727,   728,
     729,   729,   730,   731,   732,   733,   734,   735,   736,   736,
     737,   737,   737,   738,   739,   740,   740,   741,   741,   742,
     742,   743,   744,   744,   745,   745,   746,   746,   747,   748,
     749,   749,   749,   750,   751,   751,   752,   753,   754,   754,
     754,   754,   754,   754,   754,   754,   754,   754,   754,   754,
     754,   754,   754,   754,   754,   754,   754,   754,   754,   754,
     754,   754,   754,   754,   755,   756,   757,   757,   758,   758,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   760,
     761,   762,   763,   764,   765,   766,   767,   767,   767,   768,
     769,   770,   771,   772,   773,   773,   773,   773,   773,   773,
     773,   773,   773,   773,   773,   773,   773,   773,   774,   774,
     775,   775,   776,   776,   776,   776,   777,   777,   778,   779,
     779,   780,   780,   781,   781,   782,   782,   782,   782,   782,
     782,   783,   784,   784,   785,   785,   785,   785,   786,   786,
     787,   787,   788,   788,   789,   789,   790,   790,   791,   791,
     792,   793,   794,   795,   795,   796,   796,   797,   797,   798,
     798,   798,   798,   798,   798,   798,   798,   798,   798,   798,
     799,   800,   800,   801,   802,   802,   803,   804,   805,   806,
     807,   808,   809,   810,   811,   811,   812,   812,   813,   813,
     814,   815,   815,   815,   815,   816,   817,   818,   818,   818,
     818,   818,   818,   819,   820,   821,   821,   821,   822,   822,
     822,   823,   823,   824,   824,   825,   825,   825,   826,   826,
     826,   826,   826,   827,   828,   829,   830,   830,   831,   831,
     832,   833,   834,   834,   834,   834,   834,   835,   836,   837,
     838,   839,   840,   840,   841,   841,   842,   843,   844,   844,
     845,   845,   845,   846,   847,   848,   849,   849,   850,   851
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
       3,     1,     4,     3,     1,     3,     1,     3,     4,     1,
       4,     4,     4,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     0,     5,     6,     8,
       1,     3,     1,     1,     1,     4,     1,     0,     2,     3,
       2,     4,     0,     1,     5,     4,     6,     4,     1,     4,
       4,     1,     6,     1,     3,     1,     1,     4,     1,     1,
       3,     1,     1,     3,     1,     0,     1,     2,     3,     1,
       2,     5,     4,     4,     6,     1,     3,     1,     1,     6,
       4,     1,     3,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     6,     4,     1,     4,     1,     1,     1,     1,
       4,     2,     7,     1,     4,     1,     1,    11,     0,     2,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     8,     1,     3,     2,     2,     7,     1,
       3,     1,     3,     1,     4,     1,     3,     1,     1,     0,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     8,     6,     8,     6,     1,     6,     6,
       6,     6,     1,     3,     5,     1,     3,     8,     6,     6,
       4,     5,     5,     2,     2,     0,     1,     3,     1,     4,
       7,     1,     3,     3,     1,     3,     5,     3,     3,     1,
       3,     1,     1,     3,     3,     3,     3,    10,     8,    10,
       0,     0,     1,     2,     4,     4,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     6,     4,
       4,     3,     9,     1,     1,     3,     1,     5,     5,     9,
       0,     1,     1,     3,     3,     3,     3,     3,     6,     3,
       3,     3,     3,     7,     5,     1,     1,     3,     4,     1,
       1,     3,     1,     1,     3,     3,     2,     3,     4,     4,
       5,     5,     1,     2,     4,     4,     4,     0,     1,     2,
       7,     6,     3,     3,     7,     5,     1,     3,     1,     4,
       2,     3,     3,     4,     6,     3,     2,     3,     1,     1,
       4,     5,     3,     6,     2,     4,     2,     1,     3,     3,
       0,     1,     2,     2,     2,     2,     9,     5,     1,     3,
       2,     2,     2,     9,     4,     1,     3,     1,     1,     2,
       0,     7,     1,     4,     1,     3,     1,     1,     1,    16,
       0,     3,     3,     3,     3,     6,     9,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     4,     3,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       2,     2,     2,     2,     2,     5,     1,     1,     1,     4,
       4,     4,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     3,
       4,     5,     1,     1,     1,     1,     4,     3,     2,     4,
       3,     4,     3,     4,     5,     1,     1,     1,     1,     1,
       1,     1,     7,     5,     1,     1,     1,     1,     4,     3,
       4,     5,     1,     1,     4,     3,     4,     5,     1,     1,
       2,     1,     2,     4,     3,     4,     3,     4,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     3,     2,     4,     3,     2,     3,     2,     2,
       2,     2,     2,     2,     3,     2,     5,     2,     5,     2,
       5,     1,     1,     3,     3,     0,     0,     1,     1,     1,
       1,     1,     1,     3,     2,     5,     4,     2,     5,     4,
       2,     2,     1,     1,     3,     2,     2,     2,     4,     4,
       4,     4,     4,     4,     1,     1,     1,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     4,
       2,     1,     1,     3,     1,     1,     5,     5,     1,     3,
       1,     1,     1,     5,     5,     5,     1,     3,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,    10,    11,     9,     0,     0,     3,   150,
     149,   783,   339,   537,   537,   537,   537,   537,   339,   537,
     554,   537,    20,   537,   537,   158,   537,   560,   339,   154,
     537,   339,   537,   537,   339,   485,   537,   537,   537,   338,
     537,   776,   537,   537,   340,   785,   537,   155,   156,   779,
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
       0,   339,     8,   339,   537,   537,   537,   777,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   339,   537,   778,   537,  1210,   537,
    1211,   537,   537,   537,     0,     0,     0,     0,  1221,   537,
     537,   537,   537,   609,     0,    37,   609,    73,    48,    49,
      50,    65,    66,    76,    68,    69,    67,   109,    58,     0,
     146,   151,    52,    70,    71,    72,    51,    59,    54,    55,
      56,    60,   207,    75,    74,    57,   609,   445,   440,   453,
       0,     0,     0,   456,   439,   438,     0,   508,   511,   537,
     509,     0,   537,     0,   537,     0,     0,   551,    53,   459,
     611,   614,   620,   616,   615,   621,   622,   623,   624,   613,
     630,   612,   631,   617,     0,   774,   618,   625,   627,   626,
     657,   632,   634,   635,   633,   636,   637,   638,   639,   640,
     619,   641,   642,   644,   645,   643,   647,   648,   646,   669,
     658,   659,   660,   661,   649,   650,   651,   652,   653,   654,
     655,   656,   662,   663,   664,   665,   666,   667,   668,   629,
     670,   628,  1019,  1018,  1020,  1021,  1022,  1023,  1024,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1017,
    1035,  1036,  1037,  1038,  1039,  1040,  1041,  1042,  1043,   460,
    1177,  1179,  1181,  1182,  1178,  1180,   461,  1212,  1213,  1214,
    1215,  1216,     0,     0,   340,     0,     0,     0,     0,     0,
       0,     0,   985,    35,     0,     0,   596,     0,     0,     0,
       0,     0,     0,   454,   507,   481,   210,     0,     0,     0,
     481,     0,   312,   339,   722,     0,   722,   538,     0,    23,
     481,     0,   481,   966,     0,   982,   483,   481,   481,   481,
      32,   484,    81,   444,   949,   481,   943,   105,   481,    37,
     481,     0,   340,     0,     0,    63,     0,     0,   329,    44,
       7,   960,     0,     0,     0,     0,     0,    77,   340,     0,
     980,   522,     0,     0,     0,   296,   295,     0,     0,   807,
       0,     0,   340,     0,     0,   538,     0,   340,     0,     0,
       0,   340,    33,   340,    22,   597,     0,    21,     0,     0,
       0,     0,     0,     0,     0,   398,   340,    45,   140,     0,
       0,     0,     0,     0,     0,     0,     0,   781,   340,     0,
     340,     0,     0,   983,   984,     0,   339,   340,     0,     0,
       0,   597,     0,  1163,  1162,  1167,  1044,   722,  1169,   722,
    1159,  1161,  1045,  1150,  1153,  1156,   722,   722,   722,  1165,
    1158,  1160,   722,   722,   722,   722,  1098,   722,   722,  1175,
    1132,     0,    45,  1184,  1187,  1190,     0,    45,    45,    45,
    1239,  1220,     0,     0,     0,     0,   610,     4,    20,    20,
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
     770,   771,   769,     0,   767,   757,     0,     0,   435,     0,
     323,     0,   524,   968,   969,   965,    45,   310,   802,   804,
     967,    36,    13,   596,     0,   481,     0,   192,     0,   310,
       0,   184,     0,   704,   702,   837,   921,   922,   801,   798,
     799,   482,   516,   222,   435,   310,   671,   977,   972,   470,
     341,     0,     0,     0,     0,     0,   714,   717,   706,     0,
     497,   677,   674,   675,   451,     0,     0,   500,   978,   442,
     443,   458,   452,   471,   106,   499,    45,   517,     0,   199,
       0,   382,     0,     0,    37,    25,   797,   794,   795,   324,
     326,     0,     0,    45,   961,   962,     0,   695,   693,   681,
     678,   679,     0,     0,    78,     0,    45,   981,   979,     0,
       0,   942,     0,    45,     0,    19,     0,     0,     0,     0,
     947,     0,     0,     0,   497,   523,     0,     0,   925,   952,
     597,     0,   597,   598,   139,    34,    12,   143,   574,     0,
     758,     0,     0,     0,   722,   701,   699,   882,   919,   920,
       0,   698,   696,   953,   399,   514,     0,     0,     0,   903,
       0,   915,   914,   917,   916,     0,   686,     0,   684,   689,
       0,     0,    37,    24,     0,   310,   934,   937,     0,    45,
       0,   302,   298,     0,     0,   575,   310,     0,   527,     0,
    1102,  1097,   527,  1134,  1164,     0,   527,   527,   527,   527,
     527,   527,  1157,   310,    46,  1183,  1192,  1193,     0,     0,
      45,     0,     0,  1222,  1224,  1225,     0,     0,  1228,  1230,
    1231,  1232,     0,     0,  1236,     0,  1013,  1014,     0,     0,
       0,    20,    43,    38,    42,     0,    40,    17,    46,   310,
     132,   134,   136,   110,     0,     0,    20,   339,   148,   538,
     596,   165,   146,   310,   179,   181,   183,   187,   527,   190,
     527,   196,   198,   200,   209,     0,   213,     0,    45,     0,
     449,   424,     0,   351,   364,   363,   376,   362,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   596,     0,     0,
     596,     0,     0,   398,   404,   396,   512,     0,     0,   515,
     568,   569,   573,     0,   565,     0,   567,     0,   606,     0,
       0,     0,     0,     0,   553,   567,   557,     0,     0,   580,
     547,   578,     0,     0,   351,   353,   550,   584,   583,   552,
     672,   310,   694,   697,   700,   703,   310,   339,     0,   935,
       0,    45,   752,   178,     0,     0,     0,     0,     0,     0,
     312,   806,     0,   529,     0,   475,   479,     0,   469,   596,
       0,   194,   185,     0,   321,     0,   208,     0,   673,   596,
       0,   780,   319,   316,   313,   315,   320,   310,   722,   719,
     728,   723,     0,     0,     0,     0,     0,   720,   706,   722,
       0,   784,     0,   498,   539,     0,     0,     0,    18,   204,
       0,     0,     0,   206,   195,     0,   494,   492,   489,     0,
      45,     0,   329,     0,     0,   332,   330,     0,    45,   963,
     381,   911,   958,     0,     0,   956,     0,     0,    87,    88,
      86,    85,    91,    90,   102,    95,    98,    97,   100,    99,
      96,   101,    94,    92,    89,    93,    83,     0,    84,   197,
       0,     0,     0,     0,     0,     0,   297,     0,   188,   436,
       0,    45,   948,   946,   133,   811,     0,   809,     0,     0,
     292,   539,   180,     0,   577,     0,   576,   287,   287,     0,
     753,     0,   722,   706,   929,     0,     0,   926,   284,   283,
      62,   281,     0,     0,     0,     0,     0,     0,     0,   683,
     682,   135,    14,   182,   936,    45,   939,   938,   146,     0,
     103,    47,     0,     0,   690,     0,   722,   527,     0,  1131,
    1101,  1096,   722,   527,  1133,  1176,   722,   527,   722,   527,
     527,   527,   722,   527,   722,   527,   691,     0,     0,     0,
       0,  1204,     0,     0,  1191,  1195,  1197,  1196,    45,  1186,
     845,  1205,     0,  1189,     0,     0,     0,   988,     0,     0,
      45,  1217,     0,     0,     0,    45,  1218,  1238,    45,  1219,
      45,    45,    45,    28,    37,     0,     0,    39,     0,    30,
     159,   116,   310,   339,   118,   120,     0,   121,   114,   122,
     130,   129,   123,   124,   125,     0,   112,   115,    26,     0,
     310,     0,     0,   144,   177,     0,     0,   222,   222,     0,
     224,   217,   221,     0,     0,     0,   352,     0,   359,   361,
     358,   357,   375,   377,   371,   365,   504,   368,   366,   369,
     367,   370,   372,   374,   360,   373,   378,   596,   411,   389,
       0,   343,     0,   414,   415,   401,   412,   403,     0,   596,
     513,     0,   532,   530,     0,   596,   564,   571,   572,   570,
     599,   608,   603,   605,   607,   604,   602,   563,   548,     0,
       0,     0,   351,     0,     0,     0,     0,     0,   692,   773,
       0,   783,   786,   776,     0,   785,   779,     0,   777,   778,
     775,   768,     0,   390,   391,   429,     0,     0,   506,     0,
       0,   349,     0,     0,   805,   477,   476,     0,   474,     0,
     193,     0,   527,   800,   427,   428,   432,     0,     0,     0,
     314,   317,   176,     0,   596,     0,     0,     0,     0,     0,
     707,   718,   310,   462,   722,   676,     0,   481,     0,     0,
     201,     0,   394,   971,     0,     0,     0,    16,   796,   327,
     337,     0,   333,   335,   331,     0,     0,     0,     0,     0,
       0,     0,   955,   680,    80,    79,   128,   126,   127,   340,
       0,   487,   423,     0,     0,     0,     0,   191,     0,   520,
       0,     0,   722,     0,     0,    64,   527,   505,   599,   138,
       0,   142,    45,     0,   706,     0,     0,     0,     0,   924,
       0,     0,     0,     0,     0,   904,   906,     0,   687,   685,
       0,    45,   941,    45,   940,   145,   340,     0,   502,     0,
    1166,     0,   722,  1168,     0,   722,     0,     0,   722,     0,
     722,     0,   722,     0,   722,     0,     0,     0,    45,     0,
       0,     0,  1194,     0,  1185,  1188,   992,   990,   991,    45,
     987,     0,    45,  1223,     0,     0,     0,  1229,  1237,     0,
       0,     0,    15,    29,    41,     0,   173,   160,   117,     0,
      45,     0,    45,    27,   159,   539,   539,   169,   172,   168,
       0,   186,   189,   214,     0,     0,     0,   247,   245,   252,
     249,   263,   256,   261,     0,     0,   215,   238,   250,   242,
     253,   243,   258,   244,     0,   237,     0,   232,   229,   218,
     219,     0,     0,   425,   351,     0,   387,   596,   347,   344,
     345,     0,   398,     0,   534,   533,     0,     0,   579,   352,
       0,     0,     0,   351,   586,   351,   590,   351,   588,   310,
       0,   596,   596,   596,   518,     0,     0,     0,   970,     0,
     311,   478,   480,   172,   322,     0,   596,   519,     0,   974,
     596,   973,   318,   320,   721,     0,     0,     0,   731,     0,
       0,     0,     0,   705,   464,   481,   501,     0,   203,   202,
     381,   493,   490,   488,     0,   491,     0,   328,     0,     0,
       0,     0,     0,     0,   957,     0,  1002,     0,     0,   422,
     417,   944,   945,   716,   310,   951,   437,   810,   813,   819,
     294,   293,     0,   287,     0,     0,   289,   288,     0,   754,
     755,   708,     0,   933,   932,     0,   930,     0,   927,   282,
       0,  1008,   997,     0,   995,   998,   749,     0,     0,   918,
     910,   688,     0,     0,     0,     0,     0,   300,     0,   299,
     307,     0,  1175,     0,  1175,  1175,  1111,     0,  1105,  1107,
    1108,  1106,   722,  1110,  1109,     0,  1175,   722,  1129,  1128,
       0,     0,  1172,  1171,     0,     0,  1175,     0,  1175,     0,
     722,  1050,  1054,  1055,  1056,  1052,  1053,  1057,  1058,  1051,
       0,  1139,  1143,  1144,  1145,  1141,  1142,  1146,  1147,  1140,
    1149,  1148,   722,     0,  1092,  1094,  1095,  1093,   722,     0,
    1122,  1123,   722,     0,     0,     0,     0,     0,     0,  1206,
       0,     0,   846,   989,     0,     0,     0,     0,     0,     0,
       0,  1015,     0,     0,     0,     0,   108,   788,     0,   111,
       0,   173,     0,   146,     0,   171,   170,   267,   253,   266,
       0,   255,   260,   254,   259,     0,     0,     0,     0,     0,
     222,   212,   223,   241,     0,   222,   234,   235,     0,     0,
       0,     0,   278,   223,   279,     0,     0,   227,   268,   273,
     276,   229,   220,     0,   503,     0,   413,   385,   388,     0,
     346,     0,   531,   566,   567,     0,     0,   351,     0,     0,
       0,   772,   766,   782,     0,   596,     0,     0,     0,   525,
     350,     0,   340,   526,     0,   976,     0,     0,     0,   735,
       0,   733,   730,   725,   729,   727,     0,    45,     0,   463,
     450,   205,   334,   336,     0,     0,     0,   959,   954,   131,
       0,  1001,   421,     0,     0,   416,   950,     0,    45,   808,
     820,   821,   826,   830,   823,   831,   832,   827,   829,   828,
     824,   825,     0,     0,     0,     0,   285,     0,     0,     0,
       0,   928,   923,   472,     0,   994,   722,   905,     0,     0,
     880,   104,   306,   301,   303,     0,     0,     0,  1060,   722,
    1061,  1062,    45,  1103,   722,  1130,  1126,   722,  1175,     0,
    1059,    45,  1063,     0,  1064,     0,  1048,   722,  1137,   722,
    1090,   722,  1120,   722,  1198,  1199,  1200,  1208,  1209,    45,
    1203,  1201,  1202,  1227,   892,   893,   894,   891,   896,   890,
     897,   889,   888,   887,   895,   883,     0,     0,    45,  1226,
    1234,  1235,  1233,     0,     0,    31,   175,   174,     0,     0,
     119,   113,   107,     0,     0,   161,   596,   166,     0,   248,
     246,   264,   257,   262,   216,   222,   596,     0,   240,   236,
     223,     0,   233,     0,   270,   269,     0,   225,   229,     0,
       0,     0,     0,     0,   230,     0,   426,   386,   348,   397,
       0,   581,   593,   595,   594,     0,     0,   393,   430,     0,
       0,   803,     0,   433,     0,   975,   750,   724,     0,    45,
       0,     0,     0,   838,   964,   839,  1007,     0,  1004,  1006,
     420,   419,     0,     0,   812,     0,   822,     0,   288,     0,
       0,   759,   756,   714,   709,   710,   712,   713,   931,   996,
    1000,     0,     0,   381,     0,     0,     0,     0,     0,   309,
     308,   521,     0,     0,     0,  1104,  1127,     0,  1174,  1173,
       0,     0,     0,  1049,  1138,  1091,  1121,  1207,     0,     0,
       0,     0,     0,     0,     0,   789,   162,   163,     0,     0,
     239,   596,   241,     0,   280,   228,     0,   272,   271,   274,
     275,   277,   473,     0,   764,   763,   765,     0,   761,   392,
     431,     0,   986,   434,     0,   734,     0,   726,     0,     0,
       0,  1003,   418,     0,     0,     0,     0,     0,   901,     0,
       0,     0,     0,     0,     0,   286,   291,   290,     0,     0,
       0,   993,   907,   908,     0,   836,   881,   881,   305,   304,
    1076,  1075,  1074,  1081,  1082,  1083,  1080,  1077,  1079,  1078,
    1087,  1084,  1085,  1086,     0,  1071,  1115,  1114,  1116,  1117,
       0,  1176,  1066,  1068,  1067,     0,  1070,  1069,     0,     0,
     884,     0,  1016,   790,     0,   172,   265,     0,     0,   227,
     226,     0,     0,   760,   510,     0,     0,     0,   466,  1005,
     818,   817,     0,   815,   722,   850,     0,     0,     0,     0,
       0,   899,   900,     0,     0,     0,     0,   711,   912,   999,
      45,     0,     0,     0,     0,     0,  1113,  1170,  1065,   885,
       0,    45,     0,     0,   251,   231,   495,   762,   751,   738,
     732,   736,     0,     0,   814,   855,   851,     0,     0,     0,
       0,     0,     0,     0,     0,   842,     0,   467,   715,     0,
       0,   835,    45,    45,   878,  1073,  1072,     0,     0,   354,
       0,   793,   787,   791,   167,     0,     0,   465,   816,     0,
       0,     0,     0,   848,   840,     0,   834,     0,   898,   849,
       0,   841,     0,   913,     0,     0,     0,  1112,   886,     0,
       0,   496,     0,   741,     0,   739,   742,   853,   854,     0,
     856,   858,     0,     0,     0,   843,   468,   909,   879,   877,
       0,   792,   744,   745,     0,   737,     0,   852,     0,   847,
     833,     0,     0,     0,     0,   743,   746,   740,   857,     0,
       0,   861,   902,   844,  1010,   747,     0,     0,     0,   859,
      45,  1009,   748,   863,   862,    45,     0,     0,     0,   864,
     869,   871,   872,  1011,  1012,     0,     0,     0,    45,   860,
      45,    45,   596,   875,   874,   873,   865,     0,   867,   868,
       0,   870,     0,    45,   876,   866
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   203,   373,   204,   822,   734,   205,
     887,   602,   786,   672,   552,   885,   886,   430,   888,  1204,
    1477,   206,   207,   603,  1107,  1108,   208,   209,   210,   562,
    1255,  1256,  1111,  1257,   211,   212,   213,   214,  1137,   215,
     216,  1138,   217,   565,   218,   219,   220,   221,  1526,  1527,
     902,  1538,   921,  1796,   222,   223,   224,   225,   226,   227,
     767,  1148,  1149,   228,   229,   230,   729,  1060,  1061,   231,
     232,   693,   441,   914,   915,  1554,   916,   917,  1834,  1564,
    1569,  1570,  1835,  1836,  1565,  1566,  1567,  1556,  1557,  1558,
    1559,  1808,  1561,  1562,  1563,  1810,  2044,  1838,  1839,  1840,
    1150,  1151,  1449,  1450,  1926,  1677,  1129,  1130,   233,   446,
     234,   832,  1943,  1944,  1709,  1710,  1011,   701,   702,  1034,
    1035,  1023,  1024,   235,   739,   740,   741,   742,  1076,  1411,
    1412,  1413,   386,   363,   393,  1300,  1578,  1301,  1360,   983,
     605,   624,   606,   607,   608,   609,  1355,  1063,   954,  1848,
     805,   610,   611,   612,   613,   614,  1305,  1580,   615,  1275,
    1845,  1376,  1356,  1377,  1004,  1120,   236,   237,  1889,   238,
     239,   675,  1016,  1017,   692,   412,   240,   241,   242,   243,
    1067,  1068,  1405,  1855,  1856,  1054,   244,   245,   246,   247,
    1186,   248,   957,  1313,   249,   365,   710,  1394,   250,   251,
     252,   253,   254,   635,   627,   963,   964,   965,   255,   256,
     257,   980,   981,   986,   987,   988,  1302,   788,   628,   783,
     547,   258,   259,   260,   696,   261,   712,   713,   262,   750,
     751,   263,   487,   817,   818,   820,   264,   265,   748,   266,
     802,   267,   796,   268,   684,  1051,   269,   270,  2094,  2095,
    2096,  2097,  1664,  1048,   396,   704,   705,  1047,  1629,  1692,
    1880,  1881,  2290,  2291,  2354,  2355,  2373,  2385,  2386,  1697,
    1878,   271,   272,  1679,   656,   791,   792,  1863,  2157,  2158,
    1864,   653,   654,   273,   274,   275,   276,  2008,  2009,  2322,
    2323,   277,   737,   738,   278,   689,   690,   279,   668,   669,
     280,   281,  1126,  1127,  1669,  2084,  2252,  2253,  1909,  1910,
    1911,  1912,  1913,   686,  1914,  1915,  1916,  2306,  1211,  1917,
    1918,  1919,  2255,  2331,  2359,  2360,  2390,  2391,  2408,  2409,
    2410,  2411,  2412,  2423,  1920,  2106,  2272,   798,  1786,  1995,
    1996,  1997,  1921,   810,  1464,  1465,  1938,  1144,  2269,   282,
     283,   284,   285,   286,   287,   288,   289,   779,  1146,  1147,
    1685,  1686,   290,   826,   291,   762,   292,   763,   293,  1123,
     294,   295,   296,   297,   298,  1084,  1085,   299,   745,   300,
     301,   302,   664,   665,   303,   304,  1379,  1619,   698,   305,
     306,   758,   307,   308,   309,   310,   311,   312,  1216,  1217,
     313,  1154,  1693,  1694,  2191,   314,  1657,  2077,  2078,  1695,
     315,  2401,   316,   317,   318,   319,   320,   321,   322,   323,
    1187,  1740,   844,  1718,  1719,  1720,  1744,  1745,  1746,  2225,
    1747,  1748,  1721,  2113,  2316,  2214,   324,  1193,  1768,   325,
     326,   327,   328,  1177,  1722,  1723,  1724,  2220,   329,  1195,
    1772,   330,  1183,  1727,  1728,  1729,   331,   332,   333,  1189,
    1762,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,  1733,  1734,   845,  1486,
     349,   350,   351,   352,   353,   855,   856,   857,  1205,  1206,
    1207,  1212,  1778,  1779,   354,   355,   356,   357,   358,   359,
     360,   361,   862,   863,   864,   865,   867,   868,   869,   870,
     871,   873,   874,   541
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1923
static const yytype_int16 yypact[] =
{
   -1923,   129, -1923, -1923, -1923, -1923,    18,  4442, -1923, -1923,
   -1923,   122, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,   473, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923,   130, -1923, -1923,   773,   146, -1923, -1923, -1923,   130,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923,   395,   395, -1923, -1923, -1923, -1923, -1923,   395,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
     132, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,   395, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923,   233, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
     409,   625, -1923, -1923, -1923, -1923, -1923,   130, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923,   130, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923,   695,   701,   734,   395, -1923, -1923,
   -1923, -1923, -1923,   435,   825,   745,   435, -1923, -1923, -1923,
     758,   779,   854,   863, -1923, -1923, -1923,   640,   911,   395,
   -1923, -1923,   919,   925,   945,   954,   635,   182,   959,   998,
    1006, -1923,   173, -1923, -1923, -1923,   435, -1923, -1923, -1923,
     841,    55,  1366,  2064, -1923, -1923,  2662, -1923,   880, -1923,
   -1923,  1346, -1923,   956, -1923,  1667,   956,  1013, -1923, -1923,
    1024, -1923, -1923, -1923,  1032,  1043,  1059,  1062,  1066, -1923,
   -1923, -1923, -1923,  1068,   667, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
    1085, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923,   128,   395,  1092,  1090,  1096,   952,   395,   395,
     139,   395, -1923,   395,   395,  1116, -1923,   109,  1119,   395,
     395,   395,   395, -1923, -1923,   395, -1923,  1123,   395,   991,
     395,  1136, -1923, -1923, -1923,   395, -1923,  1130,   395, -1923,
     395,  1156,   154, -1923,   991, -1923,   395,   395,   395,   395,
   -1923, -1923, -1923, -1923, -1923,   395, -1923,   395,   395,   745,
     395,  1161,  1092,   395,  1182, -1923,   395,   395, -1923, -1923,
   -1923,  1171,  1185,   395,   395,  1199,  1206,   395,  1092,  1216,
    2662, -1923,  1230,  1237,   395, -1923,  1187,   395,  1192, -1923,
    1244,   395,  1092,  1247,  1266, -1923,   952,  1092,   395,   395,
    2157,    63,   395,    90, -1923, -1923,   159, -1923,   194,   395,
     395,   395,  1276,   395,   395,  2662,   119, -1923, -1923,  1279,
     395,   395,   395,   395,   395,  2555,   395, -1923,  1092,   395,
    1092,   395,   395, -1923, -1923,   395, -1923,  1092,   395,  1287,
    1293, -1923,   395, -1923, -1923,  1296, -1923, -1923,  1297, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,  1303,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923,   395, -1923, -1923,  1304,  1305,  1309, -1923, -1923, -1923,
   -1923, -1923,  2662,  2662,  2662,  2662, -1923, -1923, -1923, -1923,
    1205,   171, -1923, -1923,   395,   395,   395,   395,  1236, -1923,
   -1923,  1208,   395,   395, -1923,   644,   395,   395,   395,   395,
     395,   235,   395,  1192,   395,   395,  1161, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923,  1037, -1923, -1923, -1923, -1923,
   -1923, -1923,  2662,  2662,  2662, -1923,  2662, -1923, -1923, -1923,
   -1923, -1923, -1923,  2662,  3403, -1923,    67,  1327, -1923,  1318,
   -1923,  1093,  1094,  1323, -1923, -1923,  1320,  2662, -1923, -1923,
    1239, -1923, -1923,  1316,  2131,  1327, -1923, -1923,   840,   -32,
   -1923,  1239, -1923, -1923, -1923,  1335,   284,   144,  3190,  3190,
     395,   395,   395,   395,   395,   395,   395,  1337, -1923,   395,
   -1923, -1923, -1923,   556, -1923, -1923,  1331,   395, -1923,  2662,
   -1923,  1110,   468, -1923,  1338, -1923, -1923,  1339,  1348, -1923,
   -1923, -1923, -1923, -1923,  2793,   395,  1342, -1923,   395,  1339,
     395, -1923,   952, -1923, -1923, -1923, -1923, -1923, -1923,  1350,
   -1923, -1923, -1923, -1923, -1923,  1339, -1923, -1923,  1344, -1923,
   -1923,   645,  1559,   395,   659,   571, -1923,  1349,  1195,  2662,
    1223, -1923,  1358, -1923, -1923,  2662,  2662, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,   395, -1923,
     395,  1352,   298,   395,   745, -1923, -1923,  1372, -1923,  1373,
   -1923,  1359,   993, -1923,  1376, -1923,   395, -1923, -1923, -1923,
    1377, -1923,  1361,  3456, -1923,   395, -1923,  5526, -1923,   395,
    2662, -1923,  1374, -1923,   395, -1923,   395,   395,   395,  1327,
     601,   395,   395,   395,  1223, -1923,   395,   643, -1923, -1923,
   -1923,  2131,   840, -1923, -1923, -1923, -1923, -1923, -1923,   128,
   -1923,  1331,  1383,  1349, -1923, -1923, -1923, -1923, -1923, -1923,
     395, -1923, -1923, -1923,  5526, -1923,   109,  1329,   395, -1923,
    1378, -1923, -1923, -1923, -1923,  1379,  3492,   662, -1923, -1923,
     233,   395,   745, -1923,   395,  1339, -1923,  1387,  1375, -1923,
     395, -1923,  1389,  2662,  2662, -1923,  1339,   395,   199,   395,
    1117,  1117,   210,  1117, -1923,  1384,   237,   295,   353,   362,
     434,   454, -1923,  1339,   507, -1923,  1393, -1923,   104,   152,
   -1923,   277,   663, -1923, -1923, -1923,    54,   665, -1923, -1923,
   -1923, -1923,  1077,   674, -1923,  3540,  5526,  3598,  3644,   395,
     395, -1923, -1923, -1923, -1923,   677, -1923, -1923,  1193,  1339,
   -1923, -1923, -1923, -1923,  1731,   395, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923,  1339, -1923, -1923, -1923, -1923,  1399, -1923,
    1399, -1923, -1923, -1923, -1923,   396, -1923,   334, -1923,  1398,
   -1923, -1923,  3683,  1408,  1409,  1409,  2961, -1923,  2662,  2662,
    2662,  2662,  2662,  2662,  2662,  2662,  2662,  2662,  2662,  2662,
    2662,  2662,  2662,  2662,  2662,  2662,  2662, -1923,  1353,  1291,
    1401,   341,   422,  2662, -1923, -1923, -1923,   699,  1815, -1923,
   -1923, -1923, -1923,   710, -1923,  1918,   615,  2662,  1415,  2131,
    2131,  2131,  2131,  2131, -1923,   780, -1923,   284,   284,  1327,
    1420, -1923,  3190,  5526,   134,   145, -1923,  1421,  1422, -1923,
   -1923,  1339, -1923, -1923, -1923, -1923,  1339, -1923,   198, -1923,
     128, -1923, -1923, -1923,   395,  3996,   395,  1418,  2662,  1367,
   -1923, -1923,   395, -1923,  2662,  4030, -1923,   731, -1923, -1923,
    1400, -1923, -1923,   769, -1923,   395, -1923,   395, -1923, -1923,
    1559, -1923, -1923, -1923, -1923, -1923,  4066,  1339, -1923, -1923,
   -1923,  1424,  1426,  1431,  1434,  1435,  1436, -1923,  1195, -1923,
     395, -1923,  4097, -1923, -1923,   395,  4148,  4189, -1923,  1437,
     784,  1428,  1323, -1923, -1923,   395, -1923,  1445, -1923,  1429,
   -1923,   395, -1923,  1325,   887, -1923, -1923,   -38, -1923, -1923,
    1449, -1923,  1446,  1453,   811, -1923,   395,  1442, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923,  1443, -1923, -1923,
     460,  1444,  1450,  4243,  2808,   -82, -1923,  1430, -1923, -1923,
     815, -1923, -1923, -1923, -1923, -1923,   826, -1923,  1448,   852,
   -1923, -1923, -1923,  2662, -1923,   979, -1923, -1923, -1923,   861,
   -1923,  1462, -1923,  1195,  1456,  1470,   889, -1923, -1923, -1923,
    1471, -1923,  1463,  1468,  1458,   395,  2662,  2662,  2555, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923,  1478,  1479, -1923,   369,
   -1923, -1923,  4274,  4310, -1923,  1467, -1923,   458,  1469, -1923,
   -1923, -1923, -1923,   465, -1923, -1923, -1923,   466, -1923,   484,
     498,   505, -1923,   511, -1923,   518, -1923,  1474,  1476,  1481,
    1482, -1923,  1485,  1486, -1923, -1923, -1923, -1923, -1923, -1923,
    1327,  1496,  1472, -1923,  1473,   -69,   903, -1923,  1491,  1492,
   -1923, -1923,  1493,  1494,  1495, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923,   745,   395,   135, -1923,  1497, -1923,
    1506, -1923,  1339, -1923, -1923, -1923,  1498, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923,  1036, -1923, -1923, -1923,   395,
    1339,   105,  1987, -1923, -1923,   395,   395, -1923,  2192,   334,
   -1923,  1499, -1923,  1455,  2662,  3190, -1923,  2662,  1409,  1409,
     574,   574,  2961,   835,  3258,  3036,  5526,  3036,  3036,  3036,
    3036,  3036,  3258,  1777,  1409,  1777,  3946,  1401, -1923, -1923,
    1500,  1507,  2600, -1923, -1923, -1923, -1923, -1923,  1512, -1923,
   -1923,   952,  5526, -1923,  2662, -1923, -1923, -1923, -1923,  5526,
     506,  5526,  1415,  1415,  1072,  1415,   608, -1923,  1420,  1514,
     284,  4389,  1517,  1518,  1521,  3190,  3190,  3190, -1923, -1923,
     395,  1505, -1923, -1923,  1515,  1349, -1923,   233, -1923, -1923,
   -1923, -1923,  1277,   622,   768, -1923,   910,   952, -1923,   952,
     915,  5526,  1524,   917, -1923,  5526,  2662,  2793, -1923,   921,
   -1923,   952,  1399, -1923,   805,   876, -1923,   926,  1368,   935,
   -1923,  2397, -1923,   571, -1923,  1522,   395,   395,  2662,   395,
   -1923, -1923,  1339, -1923, -1923, -1923,  1294,   395,  2662,   395,
   -1923,   395, -1923,  1327,  2662,  1520,  2808, -1923, -1923, -1923,
   -1923,   944, -1923,  1528, -1923,  1530,  1531,  1534,  1343,  2662,
     395,   395, -1923, -1923, -1923, -1923, -1923, -1923, -1923,  1092,
     395, -1923,  2877,  3293,  1532,   395,   395, -1923,   395, -1923,
     -58,   395, -1923,  2662,   395, -1923,  1399,  5526, -1923,  1547,
      76,  1547, -1923,   395,  1195,  1550,  2891,   395,   395, -1923,
     109,  2662,   776,  2662,   951, -1923,  1544,   955,  5526, -1923,
      35, -1923, -1923, -1923, -1923, -1923,  1092,    94, -1923,   395,
   -1923,   264, -1923, -1923,   281, -1923,   177,   753, -1923,   585,
   -1923,   448, -1923,    11, -1923,   395,   395,   395, -1923,   395,
     395,   507, -1923,   395, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923,   395, -1923, -1923,   395,   395,   395, -1923, -1923,  1226,
    1246,  1227, -1923, -1923, -1923,   395,   812, -1923, -1923,  1553,
   -1923,  1558, -1923, -1923,  1506, -1923, -1923, -1923, -1923,  5526,
    2496, -1923, -1923, -1923,   550,    68,    68,  1324,  1326, -1923,
   -1923,  1332,  1333,  1336,   536,   395, -1923, -1923, -1923, -1923,
    1566, -1923, -1923, -1923,  1499, -1923,  1576, -1923,   141,  1570,
   -1923,  1572,  4770, -1923,  1567,  1568,  1323, -1923, -1923,  4804,
   -1923,  2662,  2662,  1815, -1923,  5526,  1239,   284, -1923,   151,
    3190,  3190,  3190,   155, -1923,   178, -1923,   196, -1923,  1339,
     395, -1923,  1401, -1923, -1923,  1582,   973,  2662, -1923,  1584,
   -1923,  5526, -1923, -1923, -1923,  2662, -1923, -1923,  2662, -1923,
   -1923, -1923, -1923,  5526, -1923,  1368,  2662,  1571, -1923,  1573,
    1575,  4835,  1589, -1923,   143,   395, -1923,   978, -1923, -1923,
    1578,  5526, -1923, -1923,  4804, -1923,  1325, -1923,  1325,   395,
     395,   395,   999,  1001, -1923,   395,  1586,  1581,  2662,  4869,
    3100, -1923, -1923, -1923,  1339,  1327, -1923, -1923,  1433,  1599,
    5526, -1923,   395, -1923,  1593,  1594, -1923, -1923,  1355,  1603,
   -1923, -1923,  1605, -1923,  5526,  1009, -1923,  1016, -1923, -1923,
    4900, -1923, -1923,  1018, -1923, -1923,  5526,  1592,   395, -1923,
   -1923, -1923,  1600,  1610,  1406,  1555,   395,   395,  1609,  1624,
   -1923,   481, -1923,  1618, -1923, -1923, -1923,  1619, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923,   264, -1923, -1923, -1923, -1923,
     281,   395, -1923, -1923,  1025,  1620, -1923,  1621, -1923,  1622,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
     753, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923,   585, -1923, -1923, -1923, -1923, -1923,   448,
   -1923, -1923, -1923,    11,  1597,  1617,  1625,   962,  1028, -1923,
    1628,  1631,  1327, -1923,  1039,   831,  1051,  1054,  1065,  1071,
    1627, -1923,  1630,  1635,  2662,  2662, -1923, -1923,  1638, -1923,
    3007,   812,  2504, -1923,  1074, -1923,  5526, -1923, -1923, -1923,
    1652, -1923, -1923, -1923, -1923,   341,   341,   341,   341,   341,
    2192, -1923,  1647,  1634,  1648,  2192,  1570, -1923,   334,   141,
     107,   107, -1923, -1923, -1923,  1082,  1657,  1280,   272, -1923,
    1656,   141, -1923,  2662, -1923,  1646, -1923,  1323, -1923,  2600,
    5526,  1649, -1923, -1923,   840,  1641,  1655,  1083,  1659,  1660,
    1664, -1923, -1923, -1923,  1653,  1401,  1665,   108,   952, -1923,
    5526,   395,  1092,  5526,   108,  5526,  1368,  2662,  1666,  5526,
    1086, -1923, -1923, -1923, -1923, -1923,  2662, -1923,  1654, -1923,
   -1923, -1923, -1923, -1923,  1100,  1109,  1111, -1923, -1923, -1923,
     727, -1923,  5526,  2662,  2662,  4934, -1923,   395, -1923, -1923,
    1599, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923,  1663,    76,  1669,  3456, -1923,   395,   395,   395,
    2891, -1923, -1923, -1923,   776, -1923, -1923, -1923,  1614,   395,
   -1923, -1923,  1672,  1683, -1923,   395,   395,  2662, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,   177,
   -1923, -1923, -1923,  2662, -1923,  2662, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923,  1678,  1681, -1923, -1923,
   -1923, -1923, -1923,   395,   395, -1923,  5526,  5526,  1112,  1690,
   -1923, -1923, -1923,  1677,  4965, -1923, -1923, -1923,   550, -1923,
   -1923, -1923, -1923, -1923, -1923,  2192, -1923,   395, -1923, -1923,
    1684,  1674, -1923,   896,   272,   272,   141, -1923,   141,   107,
     107,   107,   107,   107,  1080,  4996, -1923, -1923, -1923, -1923,
    2662, -1923, -1923, -1923, -1923,  2088,  1686,   967, -1923,   395,
    1697,  1348,   395, -1923,   395, -1923,  5027, -1923,  2662, -1923,
    5058,  1480,  2662, -1923, -1923, -1923, -1923,  1114, -1923, -1923,
    5526,  5526,  2662,  1694, -1923,   933, -1923,  2662, -1923,  1689,
    1709, -1923, -1923,  1718,  1727, -1923, -1923, -1923, -1923, -1923,
    1606,  1716,  1115,  1733,  1735,  1118,  1131,   395,   395, -1923,
   -1923,  5526,   904,  1723,     0, -1923, -1923,  1708, -1923, -1923,
     260,  5089,  5120, -1923, -1923, -1923, -1923, -1923,   395,   395,
     831,  1140,  1725,  1742,  1744, -1923, -1923, -1923,  1987,  1732,
   -1923,  1401, -1923,   141, -1923,  1080,  1734,   272,   272, -1923,
   -1923, -1923, -1923,  5151, -1923,  4804, -1923,  1142, -1923,   982,
   -1923,   952,  1496, -1923,  1368, -1923,  1501, -1923,  1737,  5182,
     727, -1923,  5526,  2539,  1739,  1743,  1746,  1747,  1749,  1751,
     395,   395,  1752,  1753,  5213, -1923, -1923, -1923,  2662,   395,
     395, -1923, -1923,  1754,   395, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923,  1750, -1923, -1923, -1923, -1923, -1923,
    1144, -1923, -1923, -1923, -1923,  1760, -1923, -1923,   115,  1762,
   -1923,  1763, -1923, -1923,  1765, -1923, -1923,  1764,  1152,  1080,
   -1923,  2662,  2088, -1923, -1923,  2662,   395,  2662, -1923, -1923,
   -1923,  5526,  1164, -1923, -1923,  1739,   395,   395,   395,   395,
     395, -1923, -1923,  2662,  2662,  2662,  1166, -1923, -1923,  1766,
   -1923,  1169,  1776,  1180,   395,  2662, -1923, -1923, -1923, -1923,
    2662, -1923,   395,  1771, -1923, -1923,  5244, -1923,  5526, -1923,
   -1923,  1758,  5275,  2539, -1923,   389, -1923,  1780,  1183,  1191,
    1791,  1212,  1769,  1214,  5306,  5337,  1782,  5368, -1923,   395,
    1726, -1923, -1923, -1923, -1923,  1496, -1923,  5399,  5430,   806,
    1477, -1923,  1793, -1923, -1923,  2662,  2297, -1923, -1923,  1804,
    1805,   395,   395, -1923, -1923,   395, -1923,  2555, -1923, -1923,
    2662, -1923,  2662, -1923,  1796,  1217,  1218, -1923, -1923,  1806,
     395,  5526,   395,  5526,  1220, -1923, -1923, -1923, -1923,  1228,
   -1923,  1807,  1242,  1253,  1256,  5461,  5526, -1923, -1923, -1923,
    2662, -1923, -1923,  1809,  2297, -1923,   395, -1923,  2662, -1923,
   -1923,  1812,  2662,  1259,  2662,  1810, -1923, -1923, -1923,  5495,
    1261, -1923, -1923,  5526,  1820, -1923,  2662,  2662,  2662,  1819,
   -1923, -1923, -1923,  5526, -1923, -1923,   -66,   363,  1262, -1923,
    1828,  1829, -1923, -1923, -1923,  1823,  1823,  1823, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923,    15,  1838, -1923,
    1720, -1923,  1265, -1923, -1923, -1923
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1923, -1923, -1923, -1923, -1923,   -20,  1629,   972, -1923, -1923,
    -664,   -52, -1923, -1923,  -375, -1923,   618, -1923,   -50,   968,
   -1923, -1923, -1923,  2086,   -68, -1923, -1923, -1923, -1923, -1923,
   -1923,    59,   330,   692, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923,  -177,  -881, -1923, -1923, -1923,   788,   329,  1299,
   -1923,  -272, -1485,    64, -1923, -1923, -1923, -1923, -1923, -1923,
    1300,  -273,  -180, -1923, -1923, -1923,  1302, -1923,  -560, -1923,
   -1923, -1923, -1923,  1174, -1923, -1923,   602, -1219, -1497,   953,
     308, -1484,  -263,  -157,   965, -1923,    56,    65, -1734, -1923,
   -1475, -1205, -1473,  -417, -1923,  -135, -1540, -1743,  -874, -1923,
   -1923,   426,   750,   216,  -198,   -31, -1923,   447, -1923, -1923,
   -1923, -1923, -1923,  -213, -1923,   -48,  -328,   886, -1923,   869,
     519,   542,  -366, -1923, -1923,   832, -1923, -1923, -1923, -1923,
     257,   258,  1830,  2351,  -349, -1263,    61,  -514, -1143,   783,
    -537,  -597,  1281,   344,  1461,  -980,    46, -1923, -1923,  -601,
    -595,  -226, -1923,  -916, -1923,  -579,  -911, -1098, -1923, -1923,
   -1923,    41, -1923, -1923,  1225, -1923, -1923,  1679, -1923,  1680,
   -1923, -1923,   557, -1923,  -370,     3, -1923, -1923,  1685,  1695,
   -1923,   533, -1923,  -714,  -291,  1168, -1923,   963, -1923, -1923,
     -77, -1923,   924,   355, -1923,  3748,  -404, -1077, -1923, -1923,
   -1923, -1923, -1923, -1923,   331, -1923,   360,  -866, -1923, -1923,
   -1923,   307, -1253,  -613,   969,  -779,  -369,  -418,  -437,   630,
     336, -1923, -1923, -1923,  1310, -1923, -1923,   894, -1923, -1923,
     867, -1923,  1135, -1873,   798, -1923, -1923, -1923,  1315, -1923,
    1317, -1923,  1319, -1923,  1314, -1005, -1923, -1923, -1923,  -227,
    -133, -1923, -1923, -1923,  -393, -1923,  -296,   582,  -339,   581,
   -1923,  -100, -1923, -1923, -1923,  -405, -1923, -1923, -1923, -1766,
   -1923, -1923, -1923, -1923, -1923, -1401,  -549,    43, -1923,  -271,
   -1923,  1184,   974, -1923, -1923,   980, -1923, -1923, -1923, -1923,
    -378, -1923, -1923,   905, -1923, -1923,   958, -1923,   106,   984,
   -1923, -1923, -1923,   538, -1923, -1923, -1923,  -313, -1923, -1923,
      75, -1923,  -753,  -372,  -355, -1923, -1923, -1923, -1450, -1923,
   -1923, -1923,  -257, -1923, -1923,  -377, -1923,  -398, -1923,  -413,
   -1923,  -414, -1756, -1112,  -746, -1923,  -190,  -463, -1006, -1922,
   -1923, -1923, -1923,  -479, -1474,   310, -1923,  -732, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923,  -468, -1400,   553,
   -1923,    82, -1923,  1364, -1923,  1523, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1402,   596, -1923,  1274, -1923,
   -1923, -1923, -1923,  1651, -1923, -1923, -1923,   148,  1616, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,   516,
   -1923, -1923, -1923,    92, -1923, -1923, -1923, -1923,  -142, -1833,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
     461,   279,  -496, -1325, -1298, -1370, -1411, -1403, -1391, -1923,
   -1390, -1384, -1309, -1923, -1923, -1923, -1923, -1923,   261, -1923,
   -1923, -1923, -1923, -1923,   306, -1380, -1379, -1923, -1923, -1923,
     259, -1923, -1923,   303, -1923,   -25, -1923, -1923, -1923, -1923,
     271, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923, -1923, -1923, -1923,    77, -1923,    79,  -186,
   -1923, -1923, -1923, -1923, -1923, -1923, -1923,   830, -1923, -1923,
   -1923,  -795, -1923,    60, -1923, -1923, -1923, -1923, -1923, -1923,
   -1923, -1923, -1923,   821, -1923, -1923, -1923,   817, -1923, -1923,
   -1923, -1923,   816, -1923
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1176
static const yytype_int16 yytable[] =
{
     399,   661,   811,   812,   813,   814,   803,   676,   799,   687,
     411,   411,   955,  1467,  1082,   657,  1434,   419,  1653,  1069,
     699,  1263,   959,   782,  1354,   626,   989,   550,  1837,   626,
     714,   973,   717,   852,  1575,  1304,  1304,   720,   721,   722,
    1787,  1307,  1789,  1390,   726,   723,   445,  1375,   725,  1555,
     727,   774,  1680,  1804,  1446,   923,   426,  1687,  1823,   985,
     985,  1784,  1058,  1560,  1214,  2102,   413,  2079,   464,  1807,
     391,  1809,   467,   730,  1166,   794,   744,  1588,  1754,   447,
    1827,  1167,   947,   835,  -541,  1842,  1755,  2034,  2035,   755,
     775,  2028,  1314,  1435,  2216,  1222,   462,   391,  1756,  1757,
     708,   984,   984,   771,   680,  1758,  1702,  1002,   776,  1760,
    1761,  1415,   784,  1506,   787,  1788,  2413,  1743,   949,  1753,
    1535,  1766,  1829,  1674,   489,  1209,   391,   806,  1872,     2,
       3,  1415,   677,   650,     8,   651,  2279,   362,  1455,   821,
     882,   824,  1335,  2415,    46,   540,   678,   666,   830,   571,
     573,  1887,  -561,  -591,  -582,   578,  1829,  1830,  1831,  -592,
    1551,   394,  1741,  -585,  1751,  -591,  1764,   564,  1770,   716,
    1416,  -592,  2416,  1213,   789,  -585,   882,    74,  1749,  -137,
    1759,   577,  1767,   966,  2197,   973,  -589,   968,  -527,  1742,
     572,  1752,   883,  1765,   975,  1771,   429,   681,  -589,  1894,
    1895,  1896,  1712,  1334,  -587,   410,  -141,   577,  2230,   394,
      96,   838,   974,   840,  1731,   976,  -587,  1552,   577,  -527,
     841,   842,   843,   410,  1417,  -541,   846,   847,   848,   849,
    2217,   850,   851,   410,   626,   -61,   410,   410,   410,  1436,
     109,  1341,  1140,  1703,  1417,   577,  1507,   958,   485,  1508,
    -582,  -339,  2414,  1675,   600,  1637,  1832,   410,   677,  -339,
    -561,  -591,   707,  1223,   410,  1342,  1707,  -592,   410,  1553,
     410,  -585,   678,   581,   962,  -339,  1652,  2041,  1083,     4,
    1343,   410,  1224,   410,  2218,  1344,  1345,  1475,   410,  2033,
    1832,  2140,  1346,  1714,  -589,  2219,  2147,  2148,   908,   978,
     410,   949,  -527,   577,  1013,  1018,   410,   582,  1645,  2042,
     652,   655,  -587,   948,  1049, -1100,   662,   663,   667,   663,
    -137,   671,   673,   410,  1065,   679, -1125,   683,   685,   685,
     688,  2031,  1145,   691,  1588,   793,   695,  2079,   691,  1866,
    1811,  1813,  2029,   706,  1135,  1536,   711,  -141,   691,  1269,
     691,  1021,  1754, -1047,   411,   691,   691,   691,  1308,  1070,
    1755,   577,  1134,   691,  1136,   724,   691,  1028,   691,   973,
     577,   973,  1756,  1757,   735,   736,   -61,   892,   973,  1758,
    1743,   747,   749,  1760,  1761,   754,     5,   904,   905,   906,
     907,  -582,   761,  1753,   626,   765,  1540,  1888,   626,  1766,
    1142,  -561,  -591,   985,  1267,   626,  1407,   778,  -592,   719,
     785, -1136,  -585,   410,  1474,  1122,   706,   795,   797,   797,
    1472,   801,   778,  1466,   495,  1741,  1347,   807,   809,   809,
     809,   809,   809,  1268,   819,  -589,  1581,   823,  1751,   825,
     761,  1749,   577,   828,  1764,  1332,   831,  1162,  1770,  1681,
     836,  2222,  1742,  -587,  1759,  1712, -1100,  1348,  1802,  1803,
    1767,  1402,   577,   410,  2364,  1752,   577, -1125,  1218, -1152,
     410,  1765,  1713,   577,   577,  1771,   577,  1003, -1155,   853,
    -786,  -786,   854,  -527,   949,  1219,  1306,   861,   866,   872,
     600,  2415,   577,  2356, -1047,  1261,  2145,  1164,  1143,   884,
    1022,  1349,   889,   890,   891,   679,   577,  1947,  1174,   894,
     897,   898,  1618,   577,   903,   679,   679,   679,   679,   577,
    2416,  -563,   911,   912,   410,  1196,   577,  2092,   879,   880,
    2142,  1262,  1322,  1323,  1324,  1325,  1326,  2329,   973,  2105,
     895,  2356,   553,  1807,  1820,  1809,  1714,  1726,  2223,  1715,
   -1089,   410, -1136,  2131,  1716,   626,  1594,  1596,  1598,  2224,
    1250,  1240,  1717,  1251,  1000,  1075,  1545,  1546,  1179,  2330,
   -1119,   600,   579,  1821, -1099,  1264,  1040,  1001,  1297,   928,
    2417, -1124, -1046,   929,   632,  1007,   636,   638,   695,   991,
     747,   801,   795,   683,   996,   625,  1132,   825,   998,   625,
   -1135,  1555,  2056,  2239,  -384,   679,  2027,  1426,  1427,  1121,
   -1152,   944,  2162,   969, -1151,  1560,  1009,   970,  2395, -1155,
     969, -1154,  -563,   691,   970,  -382,  1020, -1088,   679,  1041,
    2402,   621,   622,   496, -1118,  -563,  1320,  1601,   971,  1712,
    1428,  1161,  1551,   570,  1163,   972,   949,   558,   559,   899,
     958,  1037,   972,  1030,  1197,  1198,  1713,  1042,  -527,   900,
    1378,  1133,  1573,  1338,  2429,  2431,  1031,  1038,  1339,  1735,
    1158,  1220,  -527,  1225,   647,   648,  1059,  2435,  1064,  2229,
    1039,  1066,  1228,  1159,  1221,  1236,  1226,  1199,  1082,  1082,
    1069, -1089,   546,  1077,  1080,  1229,   985,  1043,  1237,  1552,
    1774,  1775,  1776,  1109,  1780,  1781,  1110,  1309,  1044,  1382,
     537, -1119,  1116,  1115,  1117, -1099,   538,  1314,  1315,  1124,
    1310,  1128, -1124, -1046,   679,   973,   973,   973,   973,   973,
    1714,  1316,  1691,  1715,  2076,    50,  1045,   652,   984,  1367,
    1574, -1135,  1383,   626,   626,   626,   626,   626,  1080,   539,
    2283,  1553,  1368,  1391,   679, -1151,   985,   985,   985,  1877,
     551,  1176, -1154,  -563,   560,  1182,   554,   732, -1088,   679,
    1188,  -383,   679,  1192,  1194, -1118,  1712,  1371,  1170,  1169,
     391,  1691,  1466,  1602,  1466,   969,  2303,   555,   392,   970,
    1372,  1626,  1399,  1713,  2271,   769,   621,   622,  1593,  1595,
    1597,  1327,   777,   971,   625,  1400,  2027,  2299,  -382,   949,
    1215,  1594,  1596,  1598,  -846,  1180,  1181,   972,  1184,  1421,
     947,  1200,  1201,  1438,  2315,  1202,  1203,  1233,   823,  1046,
    1794,  1265,  1422,  1266,  1441,   118,  1439,  1735,  1795,  1638,
     928,  1639,   122,  1258,   929,   969,  1454,  1442,   580,   970,
    1736,   930,   931,  1984,  2298,  1985,   621,   622,  2301,  1522,
    1444,  1235,   556,   971,  1986,  1270,  1987,  1714,  1273,  1000,
    1715,   557,   944,  1445,  1737,  1716,  1259,   972,  2237,  -383,
    1481,   629,  1452,  1717,  1738,   637,  1484,  1354,    25,  1739,
    1487,   950,  1489,    29,  1375,   616,  1491,  1458,  1493,  1304,
    1304,  1304,  1304,  1304,  2019,  2020,  2021,  2022,  2023,  2200,
    1459,  1509,  2039,  2040,  1528,    47,    48,  2144,  1603,   563,
    2201,  2202,  2015,  1607,  1510,  1030,  2203,   566,  2204,  1309,
    2362,  1604,  1534,   567,  1616,  2363,  1608,  2205,  1610,  2206,
    1583,  2207,  1613,  1620,  1712,  1584,  1586,  1617,   652,   548,
      25,  1352,  1646,   568,  1358,    29,  1621,  2156,  1922,  1698,
     667,  1713,   569,  1607,   625,  1647,  1466,   574,   625,    90,
    -387,   631,  1699,   688,  2174,   625,  1701,    47,    48,    95,
     979,  1371,   953,  1581,   969,  -385,  1607,  1851,   970,  1988,
    1989,  1605,  1990,  1991,  1869,   621,   622,   953,  1392,  1891,
    1448,  2059,   971,   711,  1702,  1614,   575,  1607,  2064,  1421,
    1618,   985,   985,   985,   576,  1625,   972,  1930,  1736,   736,
    1897,   639,  1898,  1992,  1458,   121,  1934,  1636,  1418,   604,
    1931,    90,   640,  1959,   749,  1714,  1979,  1932,  1715,  1935,
     641,    95,  1737,  1531,  1532,  2266,  1960,  1503,  1630,  1980,
    1632,   642,  1738,  1857,  1595,  1597,    25,  1739,   549,  1998,
    1983,    29,  1698,  2208,  1633,  1993,  2209,   643,  2175,   150,
     644,  1440,  1999,  1458,   645,  2000,   646,   969,  1994,  1698,
    1655,   970,  2016,    47,    48,  1541,  2001,   121,   621,   622,
    2036,  -585,  2002,   649,  2068,  2017,  2039,  2040,  1634,   391,
    1482,   660,  1415,  2037,  1846,   658,  1485,  2069,  1503,   972,
    1488,   659,  1490,  1488,  1488,  1470,  1492,  1503,  1494,  1503,
    2133,  2073,  2170,  1158,  2176,   625,  1458,  1706,  1812,  1814,
    2074,   674,  2075,  2134,   682,  2171,  2193,    90,   694,  2195,
     697,  1703,  2177,   700,  2156,   709,  1668,    95,  1503,  1854,
    2242,  2210,  2275,  1984,  2178,  1985,  2179,  2180,  1501,  2181,
    2036,  2231,  2182,  2243,  1986,  2276,  1987,  2149,  2150,  2151,
     861,   715,  2293,  2285,  1607,   866,   728,  1458,   872,   743,
    1519,  1520,  1521,  1523,   884,  2294,  1725,  2308,  2313,  1730,
    2311,  1421,  1750,   121,  1763,   764,  1769,   733,  1773,  1503,
     746,  2314,  1210,  1210,  2333,   588,   589,  1533,  1849,  2211,
    2212,  2213,  2334,   679,   752,  1417,  1948,  1270,  1950,  1951,
    1458,   753,  1698,   757,  1074,  1998,  1998,  2383,  2374,   766,
    1955,   756,  1865,  2336,  1867,  2338,  2376,   150,  2368,  2369,
    1962,  2375,  1964,   893,   960,   759,  2047,  1874,   961,  2377,
    1421,  1876,   760,  2183,   781,   621,   622,   973,   804,   768,
     410,  1458,   772,  2379,  1158,  1890,   595,  1607,   816,  2398,
    2418,  1861,  1540,  1577,  2380,   597,   920,  2381,  1977,  1978,
    2394,   773,  2399,  2419,  1328,  1329,  2434,  -230,  1599,  1988,
    1989,   800,  1990,  1991,   808,  1615,  2039,  2040,  2245,  1858,
    1859,  1860,   833,   598,  2424,  2425,  2345,  2346,   834,  1190,
    1191,   837,   839,   625,   625,   625,   625,   625, -1175,   858,
     859,   979,   979,  1992,   860,   875,   876,   877,   878,   881,
     949,   599,   896,   950,  1628,  1628,  1906,  1628,   953,   951,
     952,   956,   967,   977,   997,   691,   789,  1059,   769,  1059,
    1006,   618,  1640,  1008,  1010,   619,  1012,  1019,  1025,  1029,
     626,   620,   621,   622,   394,  1993,  1055,   947,   623,  1672,
    1050,   769,  1053,   595,  1073,   922,   924,   925,  1994,   926,
    1071,  1072,   597,  1663,  1078,  1086,   927,  1087,   600,  1114,
    1141,  1152,  1128,  1155,  1156,  1165,  1168,  1171,  1676,  1185,
     804,  1208,  1678,  1227,  1179,   962,  1238,   577,   679,  1403,
     598,    13,    14,  1274,    15,    16,  1277,  1298,   929,    20,
    1299,  1704,  -342,  1705,   970,  1708,  1953,    23,  1330,  1336,
    1337,  1956,    27,  1359,  1362,    30,  1401,  1370,   599,  1384,
     601,  1385,  1005,    37,  1966,    38,  1386,    40,  1777,  1387,
    1388,  1389,  1398,  1404,  1410,  1406,  -925,  1015,  2268,  1215,
    1420,  1419,  1785,  1424,  1425,  1429,  1968,  1437,  1430,  1453,
      59,  1456,  1970,  1793,  1443,   623,  1972,  1457,  1461,  1460,
    1110,    70,  1800,  1462,  1463,  1036,  1471,  1473,  1480,  1495,
    1483,  1496,  1052,  1504,  1505,   600,  1497,  1498,  1056,  1057,
    1499,  1500,  2060,  1822,  1503,    85,  1511,  1512,  1514,  1515,
    1516,   899,  1525,  1530,  1568,  1577,  1833,  1571,    93,  1582,
     362,  1576,  1587,  2062,  1082,  1590,  1591,  2302,  1466,  1592,
     392,  1609,  1600,  1635,   962,  1640,   102,  1626,  1640,  1640,
    1640,  1643,   104,  1113,  1648,  1649,  1650,   601,  1862,  1651,
     108,  1416,   110,  1662,   112,  1673,   114,  1682,  2047,  1700,
    1790,  1791,  1792,   119,  1032,  1799,  1033,  2104,  1797,   590,
    1815,  1825,  1816,   591,   592,   593,   594,  2343,  1817,  1818,
     130,   131,  1819,   691,  1828,  1841,   595,  1843,  1846,  1847,
    1868,  1871,  1882,   596,  1883,   597,  1884,  1886,   143,  2361,
    1082,  1900,  1901,  1899,  -494,   587,  1907,  1908,  1924,  1925,
    1927,  1928,  1929,  1936,  1703,  1939,  1172,  1173,  1974,   155,
    1066,   815,   156,   598,   590,  1940,  1702,  1945,   591,   592,
     593,   594,  1946,  1949,  1952,  1961,  1963,  1965,  1975,  2025,
    2100,   595,  2003,  2196,  2361,  2004,  1976,  2138,   596,  1981,
     597,   599,  1982,  2112,  1941,  1942,  2005,  2141,  2115,  2010,
    2018,  2116,  -381,  2026,  2038,  2043,  2046,  2050,  2055,  2072,
    2049,  2123,   634,  2124,   979,  2125,  2051,  2126,   598,  1958,
    2052,  2053,   620,   621,   622,  2054,  2057,  2067,   410,  2087,
    2107,  2108,  2101,  2128,   595,  2089,  2129,  2135,  2136,  -224,
    2143,  2261,  2262,   597,   731,  2161,   599,  2159,   600,  2173,
    2186,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1286,
    1287,  1288,  1289,  1290,  1291,  1292,  1293,  1294,  1295,  1296,
    2187,   598,   731,  2188,  2168,  2189,   804,  2192,  2190,   731,
    -837,  1312,  2194,   410,  2215,  2221,  2232,   790,  1319,  2233,
    1321,  2234,  2247,  2236,  2254,  2240,  2246,  2274,  2256,   599,
     601,  2257,  2258,   600,  2259,  1331,  2260,  2263,  2264,  2270,
    2280,  2281,  2282,  2326,  2309,  1241,  2030,  1833,  1833,  1833,
    1665,  2278,   928,  2312,  2337,  2284,   929,  2332,  2297,  1833,
    2300,  1361,  2324,   930,   931,  2244,   623,  1365,  2335,   932,
     933,  2350,   935,  2341,  2344,   937,   938,   939,   940,   941,
    2349,  2357,  2358,  1036,   944,   601,   600,  2367,  1242,   667,
    1311,  2370,  2378,  1711,  1243,   590,  2384,  2396,  2400,   591,
     592,   593,   594,  2392,  2405,  2420,  2421,  2071,  2422,  1210,
    1210,  1210,   595,  1210,  1210,  2433,   561,  1782,  2415,   596,
    1244,   597,  1234,   909,  1524,  1210,  1239,  2090,  2085,  2011,
    1798,  1476,  1414,  1801,   901,  2012,  2235,  1026,   601,  1543,
    1271,  1676,  1826,   910,  1245,  1862,  1246,  2093,   913,   598,
    2238,  2146,  1272,  2139,  2032,  2024,  1689,  2103,  1451,  1923,
    2185,  1671,  2088,  2109,  1708,  2199,  1363,  1433,  2110,  1380,
    1622,  1606,  2114,  1892,  1409,   425,  1893,   599,  2432,  1247,
    2048,  2120,   770,  2058,  1248,  2063,  1447,   731,  1249,  1027,
     583,   584,  1250,  1317,  1612,  1251,   585,  1318,   590,  1777,
     625,   979,   591,   592,   593,   594,   586,  1642,  1852,  1361,
    1468,   816,  1131,  1369,   410,   595,  1853,  1252,  2130,  1395,
     990,  1333,   596,  1423,   597,  1160,  1469,   992,  2295,   995,
     993,  1253,  2267,   994,   600,  1624,  1627,  1254,  2165,  2387,
    2091,  2287,  2371,  1139,  1351,  1822,  1408,  2061,  1350,  1667,
    2328,   962,   598,  1373,  1833,  2086,  1833,  1833,  1833,  1833,
    1833,  1833,  1537,  1210,  1210,  1210,  1364,   590,  2296,  2388,
    2404,   591,   592,   593,   594,  2426,  2428,  2273,  1937,  1062,
     599,  1688,  2098,   999,   595,   827,   601,  1654,  1079,  2166,
     718,   596,   670,   597,  2065,  1783,  2099,  1081,  2249,  1967,
    1971,  1954,  1973,  1957,  1969,  2277,  2119,  2117,  1502,  2127,
    1112,  1513,  1517,     0,  1518,  1539,     0,   410,  1118,  1119,
       0,   598,     0,  1125,   797,  2198,  1942,  1572,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   600,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   599,
       0,  1081,     0,     0,     0,  1579,     0,     0,     0,  1153,
       0,  1833,     0,  2154,     0,  1432,     0,  1585,   590,     0,
       0,     0,   591,   592,   593,   594,     0,     0,     0,    13,
      14,     0,    15,    16,     0,   595,   410,    20,  1175,   601,
    1178,     0,   596,     0,   597,    23,     0,     0,   809,   809,
      27,     0,     0,    30,     0,     0,   600,  2093,     0,   731,
     731,    37,     0,    38,     0,    40,   781,   621,   622,  1611,
    1015,     0,   598,   962,     0,     0,     0,     0,   595,     0,
       0,     0,   780,     0,  1623,     0,     0,   597,    59,     0,
       0,  1631,   781,   621,   622,     0,     0,     0,     0,    70,
     599,  1361,     0,     0,   595,     0,     0,  1641,   601,  1644,
       0,     0,     0,   597,  2289,   598,     0,     0,     0,     0,
       0,     0,  1361,    85,  1080,     0,  1080,  1544,  1545,  1546,
       0,   769,     0,     0,     0,  1659,    93,   410,   769,  1547,
    2310,   598,     0,   599,     0,     0,  1670,     0,  1548,     0,
    2321,  2320,  1303,  1303,   102,     0,     0,   600,     0,  1684,
     104,     0,     0,     0,  1690,     0,  1696,     0,   108,   599,
     110,  1549,   112,     0,   114,     0,  1550,     0,   731,   731,
     623,   119,  1785,  1785,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   131,
     600,     0,     0,     0,  1551,  1353,   623,     0,     0,   601,
       0,     0,     0,     0,     0,     0,   143,     0,  2321,     0,
    2372,     0,  1691,     0,     0,     0,   600,   590,  1374,     0,
       0,   591,   592,   593,   594,     0,     0,   155,     0,     0,
     156,     0,     0,  1806,   595,     0,     0,     0,     0,     0,
       0,   596,   601,   597,     0,     0,     0,  2352,     0,     0,
       0,  1552,     0,     0,     0,     0,   731,  1210,     0,     0,
    2406,     0,     0,     0,     0,  2407,     0,     0,   601,     0,
       0,   598,     0,   364,  1850,   804,  1312,     0,  2407,   370,
    2427,  2430,     0,     0,     0,     0,     0,     0,     0,   377,
       0,     0,   379,  2430,     0,   382,     0,     0,     0,   599,
    1870,     0,   388,  1553,     0,     0,   395,     0,  1873,     0,
     398,  1875,  1032,     0,     0,     0,  1210,   590,     0,  1879,
       0,   591,   592,   593,   594,     0,     0,     0,   417,     0,
       0,     0,   421,   422,   595,     0,   410,     0,   427,   428,
       0,   596,     0,   597,   433,   434,  1081,   435,   436,   437,
     438,  1902,   439,  1905,     0,     0,   600,     0,     0,     0,
       0,   448,     0,     0,     0,     0,   452,     0,   454,     0,
       0,   598,   457,     0,     0,     0,   461,     0,   463,     0,
       0,     0,  2228,  1210,     0,   469,     0,     0,     0,   473,
       0,     0,     0,   476,     0,   478,     0,     0,     0,   599,
       0,     0,   486,   488,     0,     0,   490,   491,   601,     0,
       0,  1805,   497,     0,   498,     0,   590,     0,   502,  2013,
     591,   592,   593,   594,   590,     0,     0,     0,   591,   592,
     593,   594,     0,   595,     0,     0,   410,     0,     0,     0,
     596,   595,   597,     0,     0,   529,     0,   531,   596,     0,
     597,     0,     0,     0,  2250,     0,   600,  1542,     0,   590,
       0,     0,     0,   591,   592,   593,   594,     0,     0,     0,
     598,     0,   815,     0,     0,   590,   595,     0,   598,   591,
     592,   593,   594,   596,     0,   597,     0,  2006,  2007,     0,
       0,     0,   595,     0,     0,  2014,     0,     0,   599,   596,
       0,   597,     0,     0,     0,     0,   599,     0,   601,     0,
       0,  1210,     0,   598,     0,     0,     0,  1432,     0,     0,
     590,   731,     0,     0,   591,   592,   593,   594,  1210,   598,
       0,     0,     0,     0,  2319,   410,  2045,   595,     0,     0,
       0,   599,  1579,   410,   596,     0,   597,     0,     0,     0,
       0,     0,     0,     0,     0,   600,     0,   599,     0,     0,
       0,     0,     0,   600,     0,     0,     0,     0,     0,     0,
    2066,     0,     0,     0,   598,     0,     0,     0,   410,  2070,
       0,     0,   590,     0,     0,     0,   591,   592,   593,   594,
    1062,     0,  1062,     0,   410,     0,  2080,  2081,   600,   595,
     946,     0,   599,     0,     0,     0,   596,   601,   597,     0,
       0,  1081,  1081,     0,   600,   601,     0,     0,     0,     0,
       0,  1656,     0,  1684,     0,     0,     0,   731,     0,  1666,
       0,   816,  1125,     0,     0,     0,   598,     0,     0,   410,
    2111,     0,     0,     0,   790,     0,     0,     0,  1081,  1081,
     601,     0,     0,     0,   703,     0,  2121,     0,  2122,   600,
       0,     0,     0,     0,   599,     0,   601,     0,     0,     0,
     731,     0,     0,     0,     0,     0,   962,  1732,     0,     0,
       0,     0,     0,     0,     0,     0,   731,   731,   731,     0,
     731,   731,     0,     0,   731,     0,     0,     0,     0,     0,
       0,   410,   731,     0,     0,  1081,  1081,  1081,     0,     0,
    1014,   601,     0,   590,     0,     0,     0,   591,   592,   593,
     594,   600,     0,     0,     0,  1432,     0,     0,   590,     0,
     595,     0,   591,   592,   593,   594,     0,   596,     0,   597,
       0,     0,     0,  2153,     0,   595,  1824,     0,  2155,  1106,
       0,     0,   596,   946,   597,     0,     0,   829,     0,     0,
       0,  1879,     0,     0,     0,  2169,     0,   598,     0,     0,
       0,     0,     0,   601,     0,  2172,     0,     0,   731,     0,
    2184,     0,   598,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1658,   599,     0,   590,     0,     0,
     946,   591,   592,   593,   594,     0,     0,     0,  1683,     0,
     599,   590,   946,     0,   595,   591,   592,   593,   594,     0,
       0,   596,     0,   597,     0,     0,     0,     0,   595,     0,
       0,  1539,   410,     0,     0,   596,     0,   597,     0,     0,
     731,   731,   731,     0,     0,     0,     0,   410,     0,     0,
       0,   598,   600,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   598,  2251,   600,     0,     0,
       0,   946,   946,   946,   946,     0,   928,     0,     0,   599,
     929,  1361,     0,     0,     0,     0,     0,   930,   931,  1081,
       0,     0,     0,   599,   933,     0,   935,     0,     0,   937,
     938,   939,   940,   941,   601,     0,     0,     0,   944,     0,
       0,     0,     0,     0,     0,     0,   410,     0,   946,   601,
     946,   946,   946,   946,     0,     0,     0,     0,     0,     0,
     410,     0,     0,     0,  2286,  2155,   600,     0,  2288,     0,
    2292,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     600,   928,     0,     0,     0,   929,  2304,  2305,  2307,     0,
       0,  1241,   930,   931,     0,     0,     0,     0,  2317,   933,
       0, -1176,     0,  2318, -1176, -1176, -1176, -1176, -1176,   946,
       0,     0,     0,   944,     0,     0,  2251,     0,   601,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   946,   601,     0,  1242,     0,  1303,  1303,  1303,  1303,
    1303,   946,     0,     0,     0,     0,     0,  1904,  2351,  2353,
     590,     0,     0,     0,   591,   592,   593,   594,     0,     0,
     816,     0,   946,  2365,     0,  2366,  1244,   595,     0,     0,
       0,     0,     0,     0,   596,     0,   597,     0,   946,     0,
       0,     0,   946,   946,     0,     0,     0,     0,  1353,     0,
    1245,     0,  1246,  1361,     0,  1374,     0,  2353,     0,     0,
       0,  2389,     0,     0,   598,  2393,     0,  1696,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1696,
    2403,  2389,     0,     0,     0,  1247,     0,     0,  2083,     0,
    1248,     0,   599,     0,  1249,     0,     0,     0,  1250,   946,
     590,  1251,     0,     0,   591,   982,   593,   594,     0,   790,
       0,     0,     0,     0,     0,     0,     0,   595,     0,     0,
    1081,     0,     0,  1252,   596,     0,   597,     0,     0,   410,
       0,     0,     0,     0,     0,     0,     0,  1253,     0,     0,
    2118,     0,     0,  1254,     0,     0,     0,     0,  1260,   600,
       0,     0,     0,     0,   598,     0,     0,     0,   946,   946,
       0,     0,     0,   928,     0,     0,     0,   929,     0,     0,
       0,     0,     0,     0,   930,   931,     0,     0,     0,     0,
     932,   933,   599,   935,   731,  2132,   937,   938,   939,   940,
     941,     0,     0,   943,     0,   944,   945,     0,   928,     0,
    1660,   601,   929,   590,     0,     0,     0,     0,  1824,   930,
     931,     0,     0,     0,  1661,   932,   933,   934,   935,   410,
       0,   937,   938,   939,   940,   941,   942,     0,   943,     0,
     944,   945,     0,     0,     0,     0,     0,     0,     0,   600,
    2160,     0,     0,   731,     0,  2163,     0,     0,  1340,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   946,   946,   946,   946,   946,   946,
     946,   946,   946,   946,   946,   946,   946,   946,   946,   946,
     946,   946,   946,     0,     0,     0,     0,     0,     0,     0,
       0,   601,     0,     0,     0,     0,     0,     0,   946,     0,
       0,     0,     0,     0,     0,   946,     0,   946,   928,   731,
     731,     0,   929,   590,     0,     0,     0,   946,     0,   930,
     931,     0,     0,     0,     0,   932,   933,   934,   935,   936,
       0,   937,   938,   939,   940,   941,   942,     0,   943,     0,
     944,   945,     0,     0,     0,     0,     0,   946,     0,     0,
       0,   946,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1088,     0,     0,     0,  1089,   590,     0,     0,     0,
       0,  1081,  1090,  1091,     0,  1081,     0,     0,  1092,  1093,
    1094,  1095,     0,     0,  1096,  1097,  1098,  1099,  1100,  1101,
    1102,  1103,     0,  1104,  1105,     0,     0,   928,     0,  1157,
       0,   929,   590,     0,     0,     0,     0,     0,   930,   931,
       0,     0,     0,     0,   932,   933,   934,   935,     0,   946,
     937,   938,   939,   940,   941,   942,     0,   943,     0,   944,
     945,     0,     0,   946,     0,     0,     0,  1081,   731,  1081,
    1081,  1081,     0,     0,     0,   928,     0,     0,  1230,   929,
     590,     0,     0,     0,   946,   731,   930,   931,     0,     0,
       0,     0,   932,   933,   934,   935,     0,     0,   937,   938,
     939,   940,   941,   942,     0,   943,     0,   944,   945,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1081,     0,     0,     0,  1529,     0,     0,     0,     0,     0,
       0,     0,     0,   928,     0,     0,  1231,   929,   590,     0,
       0,     0,  1081,  1081,   930,   931,  1081,     0,     0,     0,
     932,   933,   934,   935,     0,   946,   937,   938,   939,   940,
     941,   942,     0,   943,     0,   944,   945,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   928,
       0,     0,  1232,   929,   590,     0,     0,  1081,   946,     0,
     930,   931,     0,     0,     0,   946,   932,   933,   934,   935,
       0,   946,   937,   938,   939,   940,   941,   942,     0,   943,
       0,   944,   945,     0,     0,     0,     0,     0,   928,     0,
       0,     0,   929,   590,     0,     0,     0,   946,     0,   930,
     931,     0,     0,     0,  1276,   932,   933,   934,   935,   946,
       0,   937,   938,   939,   940,   941,   942,   946,   943,     0,
     944,   945,     0,     0,     0,     0,     0,   946,     0,     0,
     946,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   946,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   946,     0,     0,     0,
       0,     0,   366,   367,   368,   369,     0,   371,     0,   372,
     946,   374,   375,     0,   376,     0,   946,     0,   378,     0,
     380,   381,   946,     0,   383,   384,   385,     0,   387,     0,
     389,   390,     0,     0,   397,     0,     0,     0,     0,   400,
     401,   402,   403,   404,   405,   406,   407,     0,   408,   409,
       0,     0,   414,   415,   416,     0,   418,     0,   420,     0,
       0,   423,   424,     0,     0,     0,     0,     0,     0,   431,
     432,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     440,     0,   442,     0,   443,   444,     0,     0,     0,   449,
     450,   451,     0,     0,   453,     0,     0,   455,   456,     0,
     458,   459,   460,     0,     0,     0,     0,   465,   466,     0,
       0,   468,     0,   470,   471,   472,     0,   474,   475,     0,
       0,   477,     0,   479,   480,   481,   482,   483,   484,     0,
       0,     0,   946,     0,     0,   492,   493,   494,     0,     0,
       0,     0,   499,   500,   501,     0,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,     0,   530,     0,   532,   946,   533,     0,   534,
     535,   536,     0,     0,     0,     0,     0,   542,   543,   544,
     545,   928,     0,     0,     0,   929,   946,     0,     0,   946,
       0,   946,   930,   931,     0,   946,     0,     0,   932,   933,
     934,   935,     0,     0,   937,   938,   939,   940,   941,   942,
       0,   943,     0,   944,   945,     0,     0,     0,   946,     0,
       0,   946,     0,     0,     0,     0,     0,   617,     0,     0,
     630,   928,   633,     0,     0,   929,   590,     0,     0,     0,
       0,  1106,   930,   931,     0,     0,     0,  1357,   932,   933,
     934,   935,     0,     0,   937,   938,   939,   940,   941,   942,
       0,   943,     0,   944,   945,   928,     0,  1366,     0,   929,
     590,     0,     0,     0,     0,     0,   930,   931,     0,     0,
       0,     0,   932,   933,   934,   935,     0,     0,   937,   938,
     939,   940,   941,   942,     0,   943,     0,   944,   945,     0,
       0,   928,     0,  1381,     0,   929,   590,     0,     0,     0,
       0,     0,   930,   931,     0,     0,     0,     0,   932,   933,
     934,   935,   946,   946,   937,   938,   939,   940,   941,   942,
     946,   943,   928,   944,   945,     0,   929,   590,     0,     0,
       0,     0,     0,   930,   931,     0,     0,     0,  1393,   932,
     933,   934,   935,     0,     0,   937,   938,   939,   940,   941,
     942,   946,   943,     0,   944,   945,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   946,   928,     0,     0,   946,   929,   590,     0,
       0,     0,     0,     0,   930,   931,   946,   946,     0,  1396,
     932,   933,   934,   935,     0,     0,   937,   938,   939,   940,
     941,   942,     0,   943,     0,   944,   945,     0,     0,     0,
       0,     0,     0,     0,   928,     0,     0,   946,   929,   590,
       0,     0,     0,     0,     0,   930,   931,   946,   946,     0,
    1397,   932,   933,   934,   935,     0,     0,   937,   938,   939,
     940,   941,   942,     0,   943,     0,   944,   945,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   946,
       0,   946,     0,     0,     0,     0,     0,     0,   928,     0,
       0,     0,   929,   590,     0,   946,     0,     0,   946,   930,
     931,     0,     0,     0,  1431,   932,   933,   934,   935,     0,
     946,   937,   938,   939,   940,   941,   942,     0,   943,   928,
     944,   945,     0,   929,   590,     0,     0,     0,     0,     0,
     930,   931,     0,     0,     0,  1478,   932,   933,   934,   935,
       0,     0,   937,   938,   939,   940,   941,   942,     0,   943,
       0,   944,   945,     0,     0,   928,     0,     0,     0,   929,
     590,     0,     0,     0,     0,     0,   930,   931,     0,   918,
     919,  1479,   932,   933,   934,   935,     0,   946,   937,   938,
     939,   940,   941,   942,     0,   943,     0,   944,   945,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   946,     0,   946,     0,     0,     0,   946,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     946,   946,     0,   946,   928,     0,     0,     0,   929,   590,
       0,     0,     0,   946,   946,   930,   931,     0,     0,     0,
    1589,   932,   933,   934,   935,     0,     0,   937,   938,   939,
     940,   941,   942,     0,   943,     0,   944,   945,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   946,     0,   946,
       0,     0,     0,     0,     0,     0,     0,     0,     9,     0,
       0,   946,   946,     0,     0,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   946,     0,     0,     0,   946,
       0,     0,     0,     0,     0,    11,    12,    13,    14,   946,
      15,    16,    17,    18,    19,    20,     0,     0,    21,    22,
       0,     0,     0,    23,    24,    25,     0,    26,    27,    28,
      29,    30,    31,     0,    32,    33,    34,    35,    36,    37,
       0,    38,    39,    40,    41,    42,    43,     0,     0,    44,
      45,    46,    47,    48,     0,     0,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,     0,    71,
       0,    72,    73,     0,    74,    75,    76,     0,     0,    77,
       0,     0,    78,    79,     0,    80,    81,    82,    83,     0,
      84,    85,    86,    87,    88,    89,    90,    91,    92,     0,
       0,     0,     0,     0,    93,    94,    95,    96,     0,     0,
       0,     0,    97,     0,     0,    98,    99,     0,     0,   100,
     101,     0,   102,     0,     0,     0,   103,     0,   104,     0,
     105,     0,     0,     0,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     0,   116,   117,   118,     0,   119,
       0,   120,   121,     0,   122,     0,   123,   124,   125,   126,
       0,     0,   127,   128,   129,     0,   130,   131,   132,     0,
     133,   134,   135,     0,   136,     0,   137,   138,   139,   140,
     141,     0,   142,     0,   143,   144,     0,     0,   145,   146,
     147,     0,     0,   148,   149,     0,   150,   151,     0,   152,
     153,     0,     0,     0,   154,   155,     0,     0,   156,     0,
       0,   157,     0,     0,     0,   158,   159,     0,     0,   160,
     161,   162,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,     0,   174,     0,     0,   175,     0,
       0,     0,   176,   177,   178,   179,   180,     0,   181,   182,
       0,     0,   183,   184,   185,   186,     0,     0,     0,     0,
     187,   188,   189,   190,   191,   192,     0,     0,     0,     0,
       0,     0,     0,     0,   193,   194,   195,   196,     0,   197,
     198,   199,   200,   201,   202,   928,     0,     0,     0,   929,
     590,     0,     0,     0,     0,     0,   930,   931,     0,     0,
       0,  1844,   932,   933,   934,   935,     0,     0,   937,   938,
     939,   940,   941,   942,     0,   943,     0,   944,   945,   928,
       0,  1660,     0,   929,   590,     0,     0,     0,     0,     0,
     930,   931,     0,     0,     0,     0,   932,   933,   934,   935,
       0,     0,   937,   938,   939,   940,   941,   942,     0,   943,
     928,   944,   945,     0,   929,   590,     0,     0,     0,     0,
       0,   930,   931,     0,     0,     0,  1885,   932,   933,   934,
     935,     0,     0,   937,   938,   939,   940,   941,   942,     0,
     943,     0,   944,   945,   928,     0,  1903,     0,   929,   590,
       0,     0,     0,     0,     0,   930,   931,     0,     0,     0,
       0,   932,   933,   934,   935,     0,     0,   937,   938,   939,
     940,   941,   942,     0,   943,   928,   944,   945,     0,   929,
     590,     0,     0,     0,     0,     0,   930,   931,     0,     0,
       0,  1933,   932,   933,   934,   935,     0,     0,   937,   938,
     939,   940,   941,   942,     0,   943,     0,   944,   945,   928,
       0,  2082,     0,   929,   590,     0,     0,     0,     0,     0,
     930,   931,     0,     0,     0,     0,   932,   933,   934,   935,
       0,     0,   937,   938,   939,   940,   941,   942,     0,   943,
     928,   944,   945,     0,   929,   590,     0,     0,     0,     0,
       0,   930,   931,     0,     0,     0,  2137,   932,   933,   934,
     935,     0,     0,   937,   938,   939,   940,   941,   942,     0,
     943,   928,   944,   945,     0,   929,   590,     0,     0,     0,
       0,     0,   930,   931,     0,     0,     0,  2152,   932,   933,
     934,   935,     0,     0,   937,   938,   939,   940,   941,   942,
       0,   943,   928,   944,   945,  2164,   929,   590,     0,     0,
       0,     0,     0,   930,   931,     0,     0,     0,     0,   932,
     933,   934,   935,     0,     0,   937,   938,   939,   940,   941,
     942,     0,   943,   928,   944,   945,     0,   929,   590,     0,
       0,     0,     0,     0,   930,   931,     0,     0,     0,  2167,
     932,   933,   934,   935,     0,     0,   937,   938,   939,   940,
     941,   942,     0,   943,   928,   944,   945,     0,   929,   590,
       0,     0,     0,     0,     0,   930,   931,     0,     0,     0,
    2226,   932,   933,   934,   935,     0,     0,   937,   938,   939,
     940,   941,   942,     0,   943,   928,   944,   945,     0,   929,
     590,     0,     0,     0,     0,     0,   930,   931,     0,     0,
       0,  2227,   932,   933,   934,   935,     0,     0,   937,   938,
     939,   940,   941,   942,     0,   943,   928,   944,   945,  2241,
     929,   590,     0,     0,     0,     0,     0,   930,   931,     0,
       0,     0,     0,   932,   933,   934,   935,     0,     0,   937,
     938,   939,   940,   941,   942,     0,   943,   928,   944,   945,
       0,   929,   590,     0,     0,     0,     0,     0,   930,   931,
       0,     0,     0,  2248,   932,   933,   934,   935,     0,     0,
     937,   938,   939,   940,   941,   942,     0,   943,   928,   944,
     945,  2265,   929,   590,     0,     0,     0,     0,     0,   930,
     931,     0,     0,     0,     0,   932,   933,   934,   935,     0,
       0,   937,   938,   939,   940,   941,   942,     0,   943,   928,
     944,   945,  2325,   929,   590,     0,     0,     0,     0,     0,
     930,   931,     0,     0,     0,     0,   932,   933,   934,   935,
       0,     0,   937,   938,   939,   940,   941,   942,     0,   943,
     928,   944,   945,     0,   929,   590,     0,     0,     0,     0,
       0,   930,   931,     0,     0,     0,  2327,   932,   933,   934,
     935,     0,     0,   937,   938,   939,   940,   941,   942,     0,
     943,   928,   944,   945,     0,   929,   590,     0,     0,     0,
       0,     0,   930,   931,     0,     0,     0,  2339,   932,   933,
     934,   935,     0,     0,   937,   938,   939,   940,   941,   942,
       0,   943,   928,   944,   945,  2340,   929,   590,     0,     0,
       0,     0,     0,   930,   931,     0,     0,     0,     0,   932,
     933,   934,   935,     0,     0,   937,   938,   939,   940,   941,
     942,     0,   943,   928,   944,   945,  2342,   929,   590,     0,
       0,     0,     0,     0,   930,   931,     0,     0,     0,     0,
     932,   933,   934,   935,     0,     0,   937,   938,   939,   940,
     941,   942,     0,   943,   928,   944,   945,     0,   929,   590,
       0,     0,     0,     0,     0,   930,   931,     0,     0,     0,
    2347,   932,   933,   934,   935,     0,     0,   937,   938,   939,
     940,   941,   942,     0,   943,   928,   944,   945,     0,   929,
     590,     0,     0,     0,     0,     0,   930,   931,     0,     0,
       0,  2348,   932,   933,   934,   935,     0,     0,   937,   938,
     939,   940,   941,   942,     0,   943,   928,   944,   945,  2382,
     929,   590,     0,     0,     0,     0,     0,   930,   931,     0,
       0,     0,     0,   932,   933,   934,   935,     0,     0,   937,
     938,   939,   940,   941,   942,     0,   943,     0,   944,   945,
     928,     0,  2397,     0,   929,   590,     0,     0,     0,     0,
       0,   930,   931,     0,     0,     0,     0,   932,   933,   934,
     935,     0,     0,   937,   938,   939,   940,   941,   942,     0,
     943,   928,   944,   945,     0,   929,   590,     0,     0,     0,
       0,     0,   930,   931,     0,     0,     0,     0,   932,   933,
     934,   935,     0,     0,   937,   938,   939,   940,   941,   942,
       0,   943,     0,   944,   945
};

static const yytype_int16 yycheck[] =
{
      50,   367,   481,   482,   483,   484,   474,   376,   471,   381,
      62,    63,   613,  1156,   746,   364,  1114,    69,  1420,   733,
     390,   902,   617,   460,  1004,   251,   639,   204,  1568,   255,
     400,   628,   402,   529,  1297,   951,   952,   407,   408,   409,
    1514,   952,  1516,  1048,   419,   415,    98,  1027,   418,  1268,
     420,   455,  1453,  1538,  1131,   592,    76,  1457,  1555,   638,
     639,  1511,   726,  1268,   859,  1938,    63,  1900,   118,  1544,
       7,  1544,   122,   422,   827,   468,   431,  1330,  1489,    99,
    1564,   827,    15,   501,   116,  1569,  1489,  1830,  1831,   438,
     456,  1825,   958,   175,    94,    41,   116,     7,  1489,  1489,
     396,   638,   639,   452,   377,  1489,    71,   656,   457,  1489,
    1489,   169,   461,   182,   463,  1515,   182,  1487,     3,  1489,
      15,  1491,    15,    47,   144,    21,     7,   476,  1613,     0,
       1,   169,    23,     5,   116,     7,    21,    15,  1143,   488,
       5,   490,     8,   128,    89,   197,    37,     8,   497,   226,
     227,     8,     8,     8,    20,   232,    15,    16,    17,     8,
      92,    15,  1487,     8,  1489,    20,  1491,   219,  1493,    15,
     208,    20,   157,    21,    15,    20,     5,   122,  1487,   116,
    1489,     8,  1491,   620,  2106,   782,     8,   624,    15,  1487,
       8,  1489,    21,  1491,   631,  1493,    64,   377,    20,  1649,
    1650,  1651,   191,   982,     8,   129,   116,     8,  2130,    15,
     155,   507,   630,   509,    37,   633,    20,   149,     8,    37,
     516,   517,   518,   129,   282,   257,   522,   523,   524,   525,
     230,   527,   528,   129,   460,   116,   129,   129,   129,   321,
     185,    43,   791,   208,   282,     8,   315,   616,    15,   318,
     116,   129,   318,   177,   149,  1398,   149,   129,    23,   129,
     116,   116,   395,   209,   129,    67,   172,   116,   129,   201,
     129,   116,    37,   218,   166,   129,  1419,     5,   746,   150,
      82,   129,   228,   129,   284,    87,    88,  1168,   129,  1829,
     149,  2025,    94,   282,   116,   295,  2039,  2040,   571,    15,
     129,     3,   129,     8,   673,   675,   129,   252,  1406,    37,
     362,   363,   116,   246,   707,   116,   368,   369,   370,   371,
     257,   373,   374,   129,    26,   377,   116,   379,   380,   381,
     382,  1828,   800,   385,  1587,   468,   388,  2170,   390,  1602,
    1545,  1546,  1826,   395,   781,  1261,   398,   257,   400,    15,
     402,   679,  1763,   116,   406,   407,   408,   409,   953,   734,
    1763,     8,   780,   415,   782,   417,   418,   695,   420,   966,
       8,   968,  1763,  1763,   426,   427,   257,   557,   975,  1763,
    1750,   433,   434,  1763,  1763,   437,   257,   567,   568,   569,
     570,   257,   444,  1763,   620,   447,  1262,   254,   624,  1769,
     793,   257,   257,   982,     8,   631,  1070,   459,   257,   406,
     462,   116,   257,   129,  1167,   770,   468,   469,   470,   471,
    1166,   473,   474,  1155,    15,  1750,   228,   477,   480,   481,
     482,   483,   484,    37,   486,   257,  1302,   489,  1763,   491,
     492,  1750,     8,   495,  1769,   982,   498,   822,  1773,  1454,
     502,   191,  1750,   257,  1763,   191,   257,   259,  1535,  1536,
    1769,  1062,     8,   129,  2337,  1763,     8,   257,   191,   116,
     129,  1769,   208,     8,     8,  1773,     8,   657,   116,   531,
       7,     8,   532,    15,     3,   208,    64,   537,   538,   539,
     149,   128,     8,  2326,   257,   899,  2036,   825,   794,   551,
     680,   303,   554,   555,   556,   557,     8,    26,   836,   559,
     562,   563,  1378,     8,   566,   567,   568,   569,   570,     8,
     157,    15,   574,   575,   129,   853,     8,  1928,   548,   549,
    2027,   900,   969,   970,   971,   972,   973,   148,  1135,  1939,
     560,  2374,   206,  2018,     8,  2018,   282,   266,   288,   285,
     116,   129,   257,  2003,   290,   781,  1335,  1336,  1337,   299,
     191,   889,   298,   194,     8,   742,    16,    17,   287,   180,
     116,   149,   236,    37,   116,   903,     5,    21,   947,     5,
     217,   116,   116,     9,   253,   662,   255,   256,   640,   641,
     642,   643,   644,   645,   646,   251,   776,   649,   648,   255,
     116,  1820,  1865,  2143,     3,   657,  1825,   147,   148,     8,
     257,    37,  2062,     5,   116,  1820,   666,     9,  2384,   257,
       5,   116,   116,   675,     9,     3,   678,   116,   680,    58,
    2396,    16,    17,     8,   116,   129,    21,    15,    23,   191,
     180,   821,    92,     8,   824,    37,     3,     7,     8,     5,
    1019,   703,    37,     8,   147,   148,   208,    86,    23,    15,
    1029,    18,  1275,   991,  2420,  2421,    21,     8,   996,    84,
       8,     8,    37,     8,     7,     8,   728,  2433,   730,  2129,
      21,   733,     8,    21,    21,     8,    21,   180,  1420,  1421,
    1404,   257,   257,   743,   746,    21,  1275,   126,    21,   149,
    1495,  1496,  1497,   755,  1499,  1500,   756,     8,   137,  1037,
      15,   257,   764,   763,   766,   257,    15,  1583,     8,   771,
      21,   773,   257,   257,   776,  1322,  1323,  1324,  1325,  1326,
     282,    21,     5,   285,     7,    95,   165,   789,  1275,     8,
    1277,   257,  1038,   969,   970,   971,   972,   973,   800,    15,
    2235,   201,    21,  1049,   806,   257,  1335,  1336,  1337,  1625,
      15,   838,   257,   257,   124,   842,     8,   423,   257,   821,
     847,     3,   824,   850,   851,   257,   191,     8,   830,   829,
       7,     5,  1514,    15,  1516,     5,  2260,     8,    15,     9,
      21,    15,     8,   208,  2194,   451,    16,    17,  1335,  1336,
    1337,    21,   458,    23,   460,    21,  2025,  2257,     3,     3,
     860,  1590,  1591,  1592,     8,   840,   841,    37,   843,     8,
      15,   314,   315,     8,  2274,   318,   319,   879,   880,   258,
      18,   908,    21,   910,     8,   195,    21,    84,    26,  1399,
       5,  1401,   202,   895,     9,     5,  1142,    21,     7,     9,
     265,    16,    17,    22,  2256,    24,    16,    17,  2258,  1234,
       8,   881,     8,    23,    33,   917,    35,   282,   918,     8,
     285,     8,    37,    21,   289,   290,   896,    37,  2141,     3,
    1176,   251,    21,   298,   299,   255,  1182,  1867,    63,   304,
    1186,    15,  1188,    68,  1874,    15,  1192,     8,  1194,  1815,
    1816,  1817,  1818,  1819,  1815,  1816,  1817,  1818,  1819,     5,
      21,     8,    16,    17,  1242,    90,    91,    21,     8,     8,
      16,    17,  1803,     8,    21,     8,    22,     8,    24,     8,
    2332,    21,  1260,     8,     8,  2335,    21,    33,    21,    35,
    1309,    37,    21,     8,   191,  1311,  1315,    21,  1000,   124,
      63,  1001,     8,     8,  1006,    68,    21,  2055,  1672,     8,
    1012,   208,     8,     8,   620,    21,  1698,     8,   624,   144,
       3,    15,    21,  1025,    41,   631,    21,    90,    91,   154,
     636,     8,    15,  1849,     5,     3,     8,  1582,     9,   158,
     159,  1357,   161,   162,    21,    16,    17,    15,  1050,    21,
      21,  1867,    23,  1055,    71,  1371,     8,     8,  1874,     8,
    1876,  1590,  1591,  1592,     8,  1384,    37,     8,   265,  1071,
      21,     8,    21,   192,     8,   200,     8,  1397,  1078,   246,
      21,   144,     8,     8,  1086,   282,     8,    21,   285,    21,
       8,   154,   289,     7,     8,  2188,    21,     8,  1387,    21,
    1389,     8,   299,  1590,  1591,  1592,    63,   304,   233,     8,
      21,    68,     8,   159,  1392,   234,   162,     8,   135,   244,
       8,  1121,    21,     8,     8,    21,     8,     5,   247,     8,
    1429,     9,     8,    90,    91,  1265,    21,   200,    16,    17,
       8,     8,    21,     8,     8,    21,    16,    17,  1394,     7,
    1177,   149,   169,    21,    21,    15,  1183,    21,     8,    37,
    1187,    15,  1189,  1190,  1191,  1165,  1193,     8,  1195,     8,
       8,    21,     8,     8,   191,   781,     8,  1476,  1545,  1546,
      21,    15,    21,    21,    15,    21,    21,   144,    15,    21,
     149,   208,   209,     7,  2242,    15,  1442,   154,     8,  1586,
       8,   247,     8,    22,   221,    24,   223,   224,  1208,   226,
       8,    21,   229,    21,    33,    21,    35,  2041,  2042,  2043,
    1220,    15,     8,    21,     8,  1225,    15,     8,  1228,     8,
    1230,  1231,  1232,  1235,  1236,    21,  1482,    21,     8,  1485,
      21,     8,  1488,   200,  1490,     8,  1492,    15,  1494,     8,
      15,    21,   858,   859,    21,   242,   243,  1259,  1577,   305,
     306,   307,    21,  1265,    15,   282,  1712,  1269,  1714,  1715,
       8,    15,     8,   440,   231,     8,     8,  2370,     8,    37,
    1726,    15,  1601,    21,  1603,    21,     8,   244,    21,    21,
    1736,    21,  1738,     7,     5,    15,  1847,  1616,     9,    21,
       8,  1620,    15,   320,    15,    16,    17,  1854,   475,    15,
     129,     8,    15,    21,     8,  1635,    27,     8,   485,     8,
       8,  1599,  2138,     8,    21,    36,   239,    21,   316,   317,
      21,    15,    21,    21,   977,   978,    21,     7,  1340,   158,
     159,    15,   161,   162,    15,  1372,    16,    17,  2164,  1590,
    1591,  1592,    15,    64,  2416,  2417,  2312,  2313,    15,   848,
     849,    15,    15,   969,   970,   971,   972,   973,    15,    15,
      15,   977,   978,   192,    15,   542,   543,   544,   545,   124,
       3,    92,   124,    15,  1386,  1387,  1664,  1389,    15,   246,
     246,    21,    26,     8,     7,  1397,    15,  1399,  1004,  1401,
     240,     5,  1404,    15,    15,     9,     8,    15,     8,    15,
    1586,    15,    16,    17,    15,   234,     8,    15,   129,  1446,
     175,  1027,   149,    27,    15,   592,   593,   594,   247,   596,
       8,     8,    36,  1435,     8,     8,   603,    26,   149,    15,
       7,    62,  1444,    15,    15,     8,    21,     8,  1450,    15,
     617,     8,  1452,   326,   287,   166,   213,     8,  1460,  1065,
      64,    45,    46,    15,    48,    49,     8,    64,     9,    53,
     129,  1471,    21,  1473,     9,  1477,  1722,    61,     8,     8,
       8,  1727,    66,    15,    67,    69,     8,    37,    92,    15,
     201,    15,   659,    77,  1740,    79,    15,    81,  1498,    15,
      15,    15,    15,     8,   129,    26,     7,   674,  2190,  1509,
       7,    15,  1512,    21,    21,    21,  1762,    37,    18,     7,
     104,    15,  1768,  1525,    26,   129,  1772,     7,    15,     8,
    1530,   115,  1532,    15,    26,   702,     8,     8,    21,    15,
      21,    15,   709,    21,    21,   149,    15,    15,   715,   716,
      15,    15,  1868,  1555,     8,   139,    15,    15,    15,    15,
      15,     5,    15,    15,    15,     8,  1568,    62,   152,     7,
      15,    21,     8,  1872,  2256,     8,     8,  2259,  2260,     8,
      15,     7,   255,   239,   166,  1587,   170,    15,  1590,  1591,
    1592,    21,   176,   760,    16,    15,    15,   201,  1600,    15,
     184,   208,   186,    21,   188,     8,   190,     7,  2159,    15,
     334,   315,   335,   197,     5,     7,     7,  1939,    15,    10,
     246,     5,   246,    14,    15,    16,    17,  2309,   246,   246,
     214,   215,   246,  1635,     8,    15,    27,    15,    21,    21,
       8,     7,    21,    34,    21,    36,    21,     8,   232,  2331,
    2332,    15,    21,  1655,    26,   239,   173,     8,    15,    15,
     255,     8,     7,    21,   208,    15,   833,   834,    21,   253,
    1672,     7,   256,    64,    10,    15,    71,    18,    14,    15,
      16,    17,     8,    15,    15,    15,    15,    15,    21,     5,
    1936,    27,    15,  2106,  2376,    15,    21,  2016,    34,    21,
      36,    92,    21,  1949,  1706,  1707,    21,  2026,  1954,    21,
       8,  1957,    15,    15,     7,     9,    20,    26,    15,    15,
      21,  1967,     5,  1969,  1330,  1971,    21,  1973,    64,  1731,
      21,    21,    15,    16,    17,    21,    21,    21,   129,    26,
      18,     8,    78,    15,    27,    26,    15,     7,    21,    15,
      26,  2180,  2181,    36,   423,     8,    92,    21,   149,    15,
      21,   928,   929,   930,   931,   932,   933,   934,   935,   936,
     937,   938,   939,   940,   941,   942,   943,   944,   945,   946,
      21,    64,   451,    15,   254,     8,   953,    21,   132,   458,
       7,   958,     7,   129,    21,    37,    21,   466,   965,     7,
     967,     7,    15,    21,    15,    21,   255,     7,    15,    92,
     201,    15,    15,   149,    15,   982,    15,    15,    15,    15,
       8,     8,     7,    15,     8,    44,  1828,  1829,  1830,  1831,
    1436,    21,     5,     7,    15,    21,     9,     7,  2256,  1841,
    2258,  1008,    21,    16,    17,  2161,   129,  1014,     7,    22,
      23,     8,    25,    21,    78,    28,    29,    30,    31,    32,
     333,     7,     7,  1030,    37,   201,   149,    21,    87,  1871,
       5,    15,    15,  1479,    93,    10,    17,    17,     8,    14,
      15,    16,    17,    21,    15,     7,     7,  1887,    15,  1495,
    1496,  1497,    27,  1499,  1500,     7,   217,  1503,   128,    34,
     119,    36,   880,   572,  1236,  1511,   888,  1925,  1908,  1800,
    1530,  1169,  1074,  1534,   565,  1801,  2138,   693,   201,  1267,
     917,  1923,  1564,   573,   143,  1927,   145,  1929,   576,    64,
    2143,  2038,   917,  2018,  1828,  1820,  1460,  1939,  1138,  1673,
    2088,  1444,  1923,  1945,  1946,  2108,  1010,  1114,  1946,  1030,
    1381,  1359,  1952,  1646,  1072,    75,  1648,    92,  2422,   178,
    1849,  1961,   451,  1867,   183,  1874,  1133,   636,   187,   694,
     241,   241,   191,     5,  1367,   194,   241,     9,    10,  1979,
    1586,  1587,    14,    15,    16,    17,   241,  1404,  1583,  1156,
    1157,  1158,   774,  1019,   129,    27,  1586,   216,  1998,  1055,
     640,   982,    34,  1086,    36,   820,  1158,   642,  2254,   645,
     643,   230,  2189,   644,   149,  1383,  1385,   236,  2068,  2374,
    1927,  2242,  2350,   789,  1000,  2027,  1071,  1871,   998,  1441,
    2293,   166,    64,  1025,  2036,  1910,  2038,  2039,  2040,  2041,
    2042,  2043,     5,  1649,  1650,  1651,  1012,    10,  2255,  2376,
    2398,    14,    15,    16,    17,  2418,  2420,  2197,  1698,   728,
      92,  1458,  1930,   649,    27,   492,   201,  1421,   744,  2069,
     404,    34,   371,    36,  1876,  1509,  1934,   746,  2170,  1750,
    1769,  1725,  1773,  1730,  1763,  2221,  1959,  1958,  1208,  1979,
     759,  1220,  1225,    -1,  1228,  1262,    -1,   129,   767,   768,
      -1,    64,    -1,   772,  2106,  2107,  2108,  1274,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      -1,   800,    -1,    -1,    -1,  1302,    -1,    -1,    -1,   808,
      -1,  2143,    -1,     5,    -1,     7,    -1,  1314,    10,    -1,
      -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,    45,
      46,    -1,    48,    49,    -1,    27,   129,    53,   837,   201,
     839,    -1,    34,    -1,    36,    61,    -1,    -1,  2180,  2181,
      66,    -1,    -1,    69,    -1,    -1,   149,  2189,    -1,   858,
     859,    77,    -1,    79,    -1,    81,    15,    16,    17,  1366,
    1367,    -1,    64,   166,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    -1,     5,    -1,  1381,    -1,    -1,    36,   104,    -1,
      -1,  1388,    15,    16,    17,    -1,    -1,    -1,    -1,   115,
      92,  1398,    -1,    -1,    27,    -1,    -1,  1404,   201,  1406,
      -1,    -1,    -1,    36,  2246,    64,    -1,    -1,    -1,    -1,
      -1,    -1,  1419,   139,  2256,    -1,  2258,    15,    16,    17,
      -1,  1867,    -1,    -1,    -1,  1432,   152,   129,  1874,    27,
    2270,    64,    -1,    92,    -1,    -1,  1443,    -1,    36,    -1,
    2282,  2281,   951,   952,   170,    -1,    -1,   149,    -1,  1456,
     176,    -1,    -1,    -1,  1461,    -1,  1463,    -1,   184,    92,
     186,    59,   188,    -1,   190,    -1,    64,    -1,   977,   978,
     129,   197,  2312,  2313,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   214,   215,
     149,    -1,    -1,    -1,    92,  1004,   129,    -1,    -1,   201,
      -1,    -1,    -1,    -1,    -1,    -1,   232,    -1,  2350,    -1,
    2352,    -1,     5,    -1,    -1,    -1,   149,    10,  1027,    -1,
      -1,    14,    15,    16,    17,    -1,    -1,   253,    -1,    -1,
     256,    -1,    -1,  1540,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,   201,    36,    -1,    -1,    -1,    40,    -1,    -1,
      -1,   149,    -1,    -1,    -1,    -1,  1065,  2003,    -1,    -1,
    2400,    -1,    -1,    -1,    -1,  2405,    -1,    -1,   201,    -1,
      -1,    64,    -1,    12,  1581,  1582,  1583,    -1,  2418,    18,
    2420,  2421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    31,  2433,    -1,    34,    -1,    -1,    -1,    92,
    1607,    -1,    41,   201,    -1,    -1,    45,    -1,  1615,    -1,
      49,  1618,     5,    -1,    -1,    -1,  2062,    10,    -1,  1626,
      -1,    14,    15,    16,    17,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    71,    72,    27,    -1,   129,    -1,    77,    78,
      -1,    34,    -1,    36,    83,    84,  1155,    86,    87,    88,
      89,  1658,    91,  1660,    -1,    -1,   149,    -1,    -1,    -1,
      -1,   100,    -1,    -1,    -1,    -1,   105,    -1,   107,    -1,
      -1,    64,   111,    -1,    -1,    -1,   115,    -1,   117,    -1,
      -1,    -1,  2128,  2129,    -1,   124,    -1,    -1,    -1,   128,
      -1,    -1,    -1,   132,    -1,   134,    -1,    -1,    -1,    92,
      -1,    -1,   141,   142,    -1,    -1,   145,   146,   201,    -1,
      -1,     5,   151,    -1,   153,    -1,    10,    -1,   157,     5,
      14,    15,    16,    17,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    -1,    27,    -1,    -1,   129,    -1,    -1,    -1,
      34,    27,    36,    -1,    -1,   184,    -1,   186,    34,    -1,
      36,    -1,    -1,    -1,     5,    -1,   149,  1266,    -1,    10,
      -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      64,    -1,     7,    -1,    -1,    10,    27,    -1,    64,    14,
      15,    16,    17,    34,    -1,    36,    -1,  1794,  1795,    -1,
      -1,    -1,    27,    -1,    -1,  1802,    -1,    -1,    92,    34,
      -1,    36,    -1,    -1,    -1,    -1,    92,    -1,   201,    -1,
      -1,  2257,    -1,    64,    -1,    -1,    -1,     7,    -1,    -1,
      10,  1330,    -1,    -1,    14,    15,    16,    17,  2274,    64,
      -1,    -1,    -1,    -1,  2280,   129,  1843,    27,    -1,    -1,
      -1,    92,  1849,   129,    34,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,    -1,    92,    -1,    -1,
      -1,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
    1877,    -1,    -1,    -1,    64,    -1,    -1,    -1,   129,  1886,
      -1,    -1,    10,    -1,    -1,    -1,    14,    15,    16,    17,
    1399,    -1,  1401,    -1,   129,    -1,  1903,  1904,   149,    27,
     604,    -1,    92,    -1,    -1,    -1,    34,   201,    36,    -1,
      -1,  1420,  1421,    -1,   149,   201,    -1,    -1,    -1,    -1,
      -1,  1430,    -1,  1930,    -1,    -1,    -1,  1436,    -1,  1438,
      -1,  1938,  1441,    -1,    -1,    -1,    64,    -1,    -1,   129,
    1947,    -1,    -1,    -1,  1453,    -1,    -1,    -1,  1457,  1458,
     201,    -1,    -1,    -1,   393,    -1,  1963,    -1,  1965,   149,
      -1,    -1,    -1,    -1,    92,    -1,   201,    -1,    -1,    -1,
    1479,    -1,    -1,    -1,    -1,    -1,   166,  1486,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1495,  1496,  1497,    -1,
    1499,  1500,    -1,    -1,  1503,    -1,    -1,    -1,    -1,    -1,
      -1,   129,  1511,    -1,    -1,  1514,  1515,  1516,    -1,    -1,
       7,   201,    -1,    10,    -1,    -1,    -1,    14,    15,    16,
      17,   149,    -1,    -1,    -1,     7,    -1,    -1,    10,    -1,
      27,    -1,    14,    15,    16,    17,    -1,    34,    -1,    36,
      -1,    -1,    -1,  2050,    -1,    27,  1555,    -1,  2055,   753,
      -1,    -1,    34,   757,    36,    -1,    -1,   496,    -1,    -1,
      -1,  2068,    -1,    -1,    -1,  2072,    -1,    64,    -1,    -1,
      -1,    -1,    -1,   201,    -1,  2082,    -1,    -1,  1587,    -1,
    2087,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    92,    -1,    10,    -1,    -1,
     804,    14,    15,    16,    17,    -1,    -1,    -1,     7,    -1,
      92,    10,   816,    -1,    27,    14,    15,    16,    17,    -1,
      -1,    34,    -1,    36,    -1,    -1,    -1,    -1,    27,    -1,
      -1,  2138,   129,    -1,    -1,    34,    -1,    36,    -1,    -1,
    1649,  1650,  1651,    -1,    -1,    -1,    -1,   129,    -1,    -1,
      -1,    64,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,  2173,   149,    -1,    -1,
      -1,   875,   876,   877,   878,    -1,     5,    -1,    -1,    92,
       9,  2188,    -1,    -1,    -1,    -1,    -1,    16,    17,  1698,
      -1,    -1,    -1,    92,    23,    -1,    25,    -1,    -1,    28,
      29,    30,    31,    32,   201,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,   922,   201,
     924,   925,   926,   927,    -1,    -1,    -1,    -1,    -1,    -1,
     129,    -1,    -1,    -1,  2241,  2242,   149,    -1,  2245,    -1,
    2247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,     5,    -1,    -1,    -1,     9,  2263,  2264,  2265,    -1,
      -1,    44,    16,    17,    -1,    -1,    -1,    -1,  2275,    23,
      -1,    25,    -1,  2280,    28,    29,    30,    31,    32,   983,
      -1,    -1,    -1,    37,    -1,    -1,  2293,    -1,   201,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1005,   201,    -1,    87,    -1,  1815,  1816,  1817,  1818,
    1819,  1015,    -1,    -1,    -1,    -1,    -1,     7,  2325,  2326,
      10,    -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,
    2337,    -1,  1036,  2340,    -1,  2342,   119,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,  1052,    -1,
      -1,    -1,  1056,  1057,    -1,    -1,    -1,    -1,  1867,    -1,
     143,    -1,   145,  2370,    -1,  1874,    -1,  2374,    -1,    -1,
      -1,  2378,    -1,    -1,    64,  2382,    -1,  2384,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2396,
    2397,  2398,    -1,    -1,    -1,   178,    -1,    -1,  1907,    -1,
     183,    -1,    92,    -1,   187,    -1,    -1,    -1,   191,  1113,
      10,   194,    -1,    -1,    14,    15,    16,    17,    -1,  1928,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
    1939,    -1,    -1,   216,    34,    -1,    36,    -1,    -1,   129,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   230,    -1,    -1,
    1959,    -1,    -1,   236,    -1,    -1,    -1,    -1,   897,   149,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,  1172,  1173,
      -1,    -1,    -1,     5,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    92,    25,  2003,  2004,    28,    29,    30,    31,
      32,    -1,    -1,    35,    -1,    37,    38,    -1,     5,    -1,
       7,   201,     9,    10,    -1,    -1,    -1,    -1,  2027,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,   129,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
    2059,    -1,    -1,  2062,    -1,  2064,    -1,    -1,   997,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1278,  1279,  1280,  1281,  1282,  1283,
    1284,  1285,  1286,  1287,  1288,  1289,  1290,  1291,  1292,  1293,
    1294,  1295,  1296,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   201,    -1,    -1,    -1,    -1,    -1,    -1,  1312,    -1,
      -1,    -1,    -1,    -1,    -1,  1319,    -1,  1321,     5,  2128,
    2129,    -1,     9,    10,    -1,    -1,    -1,  1331,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,  1361,    -1,    -1,
      -1,  1365,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
      -1,  2190,    16,    17,    -1,  2194,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,    -1,    -1,     5,    -1,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,  1433,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,    -1,  1447,    -1,    -1,    -1,  2256,  2257,  2258,
    2259,  2260,    -1,    -1,    -1,     5,    -1,    -1,     8,     9,
      10,    -1,    -1,    -1,  1468,  2274,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2309,    -1,    -1,    -1,  1243,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,     8,     9,    10,    -1,
      -1,    -1,  2331,  2332,    16,    17,  2335,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,  1539,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
      -1,    -1,     8,     9,    10,    -1,    -1,  2376,  1572,    -1,
      16,    17,    -1,    -1,    -1,  1579,    22,    23,    24,    25,
      -1,  1585,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,     9,    10,    -1,    -1,    -1,  1611,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,  1623,
      -1,    28,    29,    30,    31,    32,    33,  1631,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,  1641,    -1,    -1,
    1644,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1659,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1670,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    -1,    19,    -1,    21,
    1684,    23,    24,    -1,    26,    -1,  1690,    -1,    30,    -1,
      32,    33,  1696,    -1,    36,    37,    38,    -1,    40,    -1,
      42,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      -1,    -1,    64,    65,    66,    -1,    68,    -1,    70,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    94,    -1,    96,    97,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,   106,    -1,    -1,   109,   110,    -1,
     112,   113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,   123,    -1,   125,   126,   127,    -1,   129,   130,    -1,
      -1,   133,    -1,   135,   136,   137,   138,   139,   140,    -1,
      -1,    -1,  1806,    -1,    -1,   147,   148,   149,    -1,    -1,
      -1,    -1,   154,   155,   156,    -1,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,    -1,   185,    -1,   187,  1850,   189,    -1,   191,
     192,   193,    -1,    -1,    -1,    -1,    -1,   199,   200,   201,
     202,     5,    -1,    -1,    -1,     9,  1870,    -1,    -1,  1873,
      -1,  1875,    16,    17,    -1,  1879,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,  1902,    -1,
      -1,  1905,    -1,    -1,    -1,    -1,    -1,   249,    -1,    -1,
     252,     5,   254,    -1,    -1,     9,    10,    -1,    -1,    -1,
      -1,  1925,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,     5,    -1,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,  2006,  2007,    28,    29,    30,    31,    32,    33,
    2014,    35,     5,    37,    38,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,  2045,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2066,     5,    -1,    -1,  2070,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,  2080,  2081,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,  2111,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,  2121,  2122,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2153,
      -1,  2155,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,     9,    10,    -1,  2169,    -1,    -1,  2172,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
    2184,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,    -1,    -1,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,   581,
     582,    21,    22,    23,    24,    25,    -1,  2251,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2286,    -1,  2288,    -1,    -1,    -1,  2292,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2304,  2305,    -1,  2307,     5,    -1,    -1,    -1,     9,    10,
      -1,    -1,    -1,  2317,  2318,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2351,    -1,  2353,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,
      -1,  2365,  2366,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2389,    -1,    -1,    -1,  2393,
      -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,  2403,
      48,    49,    50,    51,    52,    53,    -1,    -1,    56,    57,
      -1,    -1,    -1,    61,    62,    63,    -1,    65,    66,    67,
      68,    69,    70,    -1,    72,    73,    74,    75,    76,    77,
      -1,    79,    80,    81,    82,    83,    84,    -1,    -1,    87,
      88,    89,    90,    91,    -1,    -1,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    -1,   117,
      -1,   119,   120,    -1,   122,   123,   124,    -1,    -1,   127,
      -1,    -1,   130,   131,    -1,   133,   134,   135,   136,    -1,
     138,   139,   140,   141,   142,   143,   144,   145,   146,    -1,
      -1,    -1,    -1,    -1,   152,   153,   154,   155,    -1,    -1,
      -1,    -1,   160,    -1,    -1,   163,   164,    -1,    -1,   167,
     168,    -1,   170,    -1,    -1,    -1,   174,    -1,   176,    -1,
     178,    -1,    -1,    -1,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,    -1,   193,   194,   195,    -1,   197,
      -1,   199,   200,    -1,   202,    -1,   204,   205,   206,   207,
      -1,    -1,   210,   211,   212,    -1,   214,   215,   216,    -1,
     218,   219,   220,    -1,   222,    -1,   224,   225,   226,   227,
     228,    -1,   230,    -1,   232,   233,    -1,    -1,   236,   237,
     238,    -1,    -1,   241,   242,    -1,   244,   245,    -1,   247,
     248,    -1,    -1,    -1,   252,   253,    -1,    -1,   256,    -1,
      -1,   259,    -1,    -1,    -1,   263,   264,    -1,    -1,   267,
     268,   269,    -1,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,    -1,   283,    -1,    -1,   286,    -1,
      -1,    -1,   290,   291,   292,   293,   294,    -1,   296,   297,
      -1,    -1,   300,   301,   302,   303,    -1,    -1,    -1,    -1,
     308,   309,   310,   311,   312,   313,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   322,   323,   324,   325,    -1,   327,
     328,   329,   330,   331,   332,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,     5,
      -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,     5,    -1,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,     5,    37,    38,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,     5,
      -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,     5,    37,    38,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,     5,    37,    38,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      38,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,     5,    37,    38,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
       5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38
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
     681,   681,   681,   681,   681,     7,   477,   571,   572,   349,
     573,   472,   345,   349,   472,   349,   701,   703,   349,   471,
     472,   349,   449,    15,    15,   555,   349,    15,   594,    15,
     594,   594,   594,   594,   760,   816,   594,   594,   594,   594,
     594,   594,   760,   349,   356,   823,   824,   825,    15,    15,
      15,   356,   840,   841,   842,   843,   356,   844,   845,   846,
     847,   848,   356,   849,   850,   477,   477,   477,   477,   343,
     343,   124,     5,    21,   349,   353,   354,   348,   356,   349,
     349,   349,   400,     7,   356,   343,   124,   349,   349,     5,
      15,   387,   388,   349,   400,   400,   400,   400,   399,   480,
     398,   349,   349,   404,   411,   412,   414,   415,   533,   533,
     239,   390,   477,   478,   477,   477,   477,   477,     5,     9,
      16,    17,    22,    23,    24,    25,    26,    28,    29,    30,
      31,    32,    33,    35,    37,    38,   361,    15,   246,     3,
      15,   246,   246,    15,   486,   487,    21,   530,   554,   488,
       5,     9,   166,   543,   544,   545,   556,    26,   556,     5,
       9,    23,    37,   479,   555,   556,   555,     8,    15,   481,
     549,   550,    15,   477,   478,   493,   551,   552,   553,   551,
     562,   349,   576,   578,   580,   582,   349,     7,   356,   701,
       8,    21,   614,   400,   502,   477,   240,   528,    15,   356,
      15,   454,     8,   554,     7,   477,   510,   511,   512,    15,
     349,   454,   400,   459,   460,     8,   411,   502,   454,    15,
       8,    21,     5,     7,   457,   458,   477,   349,     8,    21,
       5,    58,    86,   126,   137,   165,   258,   595,   591,   592,
     175,   583,   477,   149,   523,     8,   477,   477,   348,   349,
     405,   406,   480,   485,   349,    26,   349,   518,   519,   521,
     352,     8,     8,    15,   231,   380,   466,   356,     8,   716,
     349,   480,   685,   695,   713,   714,     8,    26,     5,     9,
      16,    17,    22,    23,    24,    25,    28,    29,    30,    31,
      32,    33,    34,    35,    37,    38,   361,   362,   363,   349,
     356,   370,   480,   477,    15,   356,   349,   349,   480,   480,
     503,     8,   652,   707,   349,   480,   640,   641,   349,   444,
     445,   523,   400,    18,   555,   556,   555,   376,   379,   619,
     614,     7,   592,   594,   685,   695,   696,   697,   399,   400,
     438,   439,    62,   480,   739,    15,    15,     7,     8,    21,
     570,   400,   352,   400,   454,     8,   650,   672,    21,   356,
     349,     8,   477,   477,   454,   480,   528,   781,   480,   287,
     793,   793,   528,   790,   793,    15,   528,   758,   528,   797,
     758,   758,   528,   775,   528,   787,   454,   147,   148,   180,
     314,   315,   318,   319,   357,   826,   827,   828,     8,    21,
     481,   656,   829,    21,   829,   356,   736,   737,   191,   208,
       8,    21,    41,   209,   228,     8,    21,   326,     8,    21,
       8,     8,     8,   349,   345,   343,     8,    21,   213,   357,
     454,    44,    87,    93,   119,   143,   145,   178,   183,   187,
     191,   194,   216,   230,   236,   368,   369,   371,   349,   343,
     471,   534,   554,   381,   454,   528,   528,     8,    37,    15,
     349,   417,   422,   356,    15,   497,    21,     8,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   554,    64,   129,
     473,   475,   554,   480,   491,   494,    64,   494,   488,     8,
      21,     5,   477,   531,   545,     8,    21,     5,     9,   477,
      21,   477,   556,   556,   556,   556,   556,    21,   549,   549,
       8,   477,   478,   552,   553,     8,     8,     8,   454,   454,
     471,    43,    67,    82,    87,    88,    94,   228,   259,   303,
     623,   620,   356,   480,   483,   484,   500,    21,   349,    15,
     476,   477,    67,   455,   637,   477,     7,     8,    21,   530,
      37,     8,    21,   634,   480,   483,   499,   501,   554,   724,
     457,     7,   454,   594,    15,    15,    15,    15,    15,    15,
     583,   594,   349,    21,   535,   565,    21,    21,    15,     8,
      21,     8,   487,   481,     8,   520,    26,   348,   631,   463,
     129,   467,   468,   469,   385,   169,   208,   282,   356,    15,
       7,     8,    21,   568,    21,    21,   147,   148,   180,    21,
      18,    21,     7,   477,   495,   175,   321,    37,     8,    21,
     356,     8,    21,    26,     8,    21,   535,   477,    21,   440,
     441,   440,    21,     7,   594,   583,    15,     7,     8,    21,
       8,    15,    15,    26,   682,   683,   685,   476,   477,   572,
     356,     8,   672,     8,   650,   381,   371,   358,    21,    21,
      21,   594,   528,    21,   594,   528,   817,   594,   528,   594,
     528,   594,   528,   594,   528,    15,    15,    15,    15,    15,
      15,   356,   825,     8,    21,    21,   182,   315,   318,     8,
      21,    15,    15,   841,    15,    15,    15,   845,   850,   356,
     356,   356,   352,   349,   354,    15,   386,   387,   454,   471,
      15,     7,     8,   349,   454,    15,   491,     5,   389,   477,
     545,   400,   480,   414,    15,    16,    17,    27,    36,    59,
      64,    92,   149,   201,   413,   415,   425,   426,   427,   428,
     429,   430,   431,   432,   417,   422,   423,   424,    15,   418,
     419,    62,   477,   551,   478,   473,    21,     8,   474,   477,
     495,   545,     7,   554,   460,   477,   554,     8,   550,    21,
       8,     8,     8,   478,   553,   478,   553,   478,   553,   349,
     255,    15,    15,     8,    21,   460,   459,     8,    21,     7,
      21,   477,   510,    21,   460,   528,     8,    21,   545,   725,
       8,    21,   458,   477,   595,   554,    15,   597,   349,   596,
     596,   477,   596,   454,   594,   239,   512,   476,   406,   406,
     349,   477,   519,    21,   477,   495,     8,    21,    16,    15,
      15,    15,   476,   713,   714,   472,   480,   744,     7,   477,
       7,    21,    21,   349,   590,   481,   480,   641,   594,   642,
     477,   445,   528,     8,    47,   177,   349,   443,   356,   611,
     613,   583,     7,     7,   477,   698,   699,   696,   697,   439,
     477,     5,   597,   740,   741,   747,   477,   607,     8,    21,
      15,    21,    71,   208,   356,   356,   472,   172,   349,   452,
     453,   481,   191,   208,   282,   285,   290,   298,   761,   762,
     763,   770,   782,   783,   784,   594,   266,   791,   792,   793,
     594,    37,   480,   814,   815,    84,   265,   289,   299,   304,
     759,   761,   762,   763,   764,   765,   766,   768,   769,   770,
     594,   761,   762,   763,   764,   765,   766,   768,   769,   770,
     783,   784,   798,   594,   761,   762,   763,   770,   776,   594,
     761,   762,   788,   594,   829,   829,   829,   356,   830,   831,
     829,   829,   481,   737,   656,   356,   676,   682,   696,   682,
     334,   315,   335,   349,    18,    26,   391,    15,   370,     7,
     356,   386,   535,   535,   390,     5,   477,   428,   429,   430,
     433,   429,   431,   429,   431,   246,   246,   246,   246,   246,
       8,    37,   349,   416,   480,     5,   418,   419,     8,    15,
      16,    17,   149,   349,   416,   420,   421,   434,   435,   436,
     437,    15,   419,    15,    21,   498,    21,    21,   487,   554,
     477,   488,   531,   544,   556,   521,   522,   478,   522,   522,
     522,   454,   349,   615,   618,   554,   473,   554,     8,    21,
     477,     7,   390,   477,   554,   477,   554,   545,   608,   477,
     598,   599,    21,    21,    21,    21,     8,     8,   254,   506,
     512,    21,   468,   469,   656,   656,   656,    21,    21,   349,
      15,    21,   477,     7,     7,   477,   454,   173,     8,   646,
     647,   648,   649,   650,   652,   653,   654,   657,   658,   659,
     672,   680,   521,   441,    15,    15,   442,   255,     8,     7,
       8,    21,    21,    21,     8,    21,    21,   683,   684,    15,
      15,   349,   349,   450,   451,    18,     8,    26,   760,    15,
     760,   760,    15,   594,   782,   760,   594,   791,   349,     8,
      21,    15,   760,    15,   760,    15,   594,   759,   594,   798,
     594,   776,   594,   788,    21,    21,    21,   316,   317,     8,
      21,    21,    21,    21,    22,    24,    33,    35,   158,   159,
     161,   162,   192,   234,   247,   677,   678,   679,     8,    21,
      21,    21,    21,    15,    15,    21,   477,   477,   625,   626,
      21,   369,   391,     5,   477,   381,     8,    21,     8,   494,
     494,   494,   494,   494,   425,     5,    15,   415,   426,   419,
     349,   416,   424,   434,   435,   435,     8,    21,     7,    16,
      17,     5,    37,     9,   434,   477,    20,   487,   474,    21,
      26,    21,    21,    21,    21,    15,   473,    21,   484,   545,
     460,   636,   472,   499,   545,   725,   477,    21,     8,    21,
     477,   356,    15,    21,    21,    21,     7,   745,   746,   747,
     477,   477,     7,   480,   643,   356,   648,    26,   443,    26,
     362,   615,   613,   349,   586,   587,   588,   589,   699,   741,
     594,    78,   571,   349,   651,   696,   673,    18,     8,   349,
     453,   477,   594,   771,   356,   594,   594,   816,   480,   814,
     356,   477,   477,   594,   594,   594,   594,   831,    15,    15,
     356,   656,   480,     8,    21,     7,    21,    21,   554,   433,
     426,   554,   416,    26,    21,   434,   421,   435,   435,   436,
     436,   436,    21,   477,     5,   477,   495,   616,   617,    21,
     480,     8,   656,   480,     8,   599,   356,    21,   254,   477,
       8,    21,   477,    15,    41,   135,   191,   209,   221,   223,
     224,   226,   229,   320,   477,   442,    21,    21,    15,     8,
     132,   742,    21,    21,     7,    21,   675,   677,   349,   451,
       5,    16,    17,    22,    24,    33,    35,    37,   159,   162,
     247,   305,   306,   307,   773,    21,    94,   230,   284,   295,
     785,    37,   191,   288,   299,   767,    21,    21,   481,   656,
     677,    21,    21,     7,     7,   389,    21,   473,   420,   434,
      21,     8,     8,    21,   460,   545,   255,    15,    21,   746,
       5,   477,   644,   645,    15,   660,    15,    15,    15,    15,
      15,   681,   681,    15,    15,     8,   476,   587,   685,   686,
      15,   696,   674,   674,     7,     8,    21,   817,    21,    21,
       8,     8,     7,   390,    21,    21,   477,   617,   477,   349,
     600,   601,   477,     8,    21,   594,   660,   695,   713,   656,
     695,   696,   685,   682,   477,   477,   655,   477,    21,     8,
     356,    21,     7,     8,    21,   656,   772,   477,   477,   481,
     356,   349,   627,   628,    21,     8,    15,    21,   645,   148,
     180,   661,     7,    21,    21,     7,    21,    15,    21,    21,
       8,    21,     8,   685,    78,   676,   676,    21,    21,   333,
       8,   477,    40,   477,   602,   603,   747,     7,     7,   662,
     663,   685,   713,   696,   571,   477,   477,    21,    21,    21,
      15,   628,   349,   604,     8,    21,     8,    21,    15,    21,
      21,    21,     8,   476,    17,   605,   606,   603,   663,   477,
     664,   665,    21,   477,    21,   607,    17,     7,     8,    21,
       8,   749,   607,   477,   665,    15,   356,   356,   666,   667,
     668,   669,   670,   182,   318,   128,   157,   217,     8,    21,
       7,     7,    15,   671,   671,   671,   667,   356,   669,   670,
     356,   670,   475,     7,    21,   670
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
#line 5086 "gram1.y"
    {
            if(parstate!=INEXEC) 
               err("Illegal shadow width specification", 56);  
            (yyval.ll_node) = make_llnd(fi,SHADOW_NAMES_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
          ;}
    break;

  case 689:
#line 5101 "gram1.y"
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

  case 690:
#line 5113 "gram1.y"
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
#line 5133 "gram1.y"
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

  case 692:
#line 5153 "gram1.y"
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

  case 693:
#line 5175 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 694:
#line 5181 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 695:
#line 5190 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 696:
#line 5198 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 697:
#line 5204 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 698:
#line 5212 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 699:
#line 5219 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 700:
#line 5225 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 701:
#line 5234 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 702:
#line 5238 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 703:
#line 5244 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 704:
#line 5252 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 705:
#line 5266 "gram1.y"
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

  case 706:
#line 5279 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 707:
#line 5285 "gram1.y"
    { PTR_LLND q;
             if(!(yyvsp[(4) - (5)].ll_node))
               err("Distribution format list is omitted", 51);
            /* if($6)
               err("NEW_VALUE specification in DISTRIBUTE directive");*/
             q = set_ll_list((yyvsp[(3) - (5)].ll_node),LLNULL,EXPR_LIST);
	     (yyval.bf_node) = get_bfnd(fi,DVM_DISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node));
            ;}
    break;

  case 708:
#line 5301 "gram1.y"
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

  case 709:
#line 5316 "gram1.y"
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

  case 710:
#line 5344 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 711:
#line 5346 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 712:
#line 5350 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 713:
#line 5352 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 714:
#line 5356 "gram1.y"
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

  case 715:
#line 5385 "gram1.y"
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

  case 716:
#line 5408 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 717:
#line 5428 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 718:
#line 5430 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 719:
#line 5434 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 720:
#line 5455 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 721:
#line 5457 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 722:
#line 5460 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 723:
#line 5469 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 724:
#line 5473 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 725:
#line 5478 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 726:
#line 5480 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 727:
#line 5482 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 728:
#line 5484 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 729:
#line 5490 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 730:
#line 5492 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 731:
#line 5496 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 732:
#line 5506 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 733:
#line 5510 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 734:
#line 5512 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 735:
#line 5517 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 736:
#line 5521 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 737:
#line 5525 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 738:
#line 5531 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 739:
#line 5541 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 740:
#line 5543 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 741:
#line 5547 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 742:
#line 5549 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 743:
#line 5551 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 744:
#line 5558 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 745:
#line 5575 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 746:
#line 5577 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 747:
#line 5581 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 748:
#line 5583 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 749:
#line 5587 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 750:
#line 5594 "gram1.y"
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

  case 751:
#line 5604 "gram1.y"
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

  case 752:
#line 5633 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 753:
#line 5648 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 754:
#line 5655 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 755:
#line 5673 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 756:
#line 5675 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 757:
#line 5679 "gram1.y"
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

  case 758:
#line 5693 "gram1.y"
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

  case 759:
#line 5719 "gram1.y"
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

  case 760:
#line 5732 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 761:
#line 5748 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 762:
#line 5750 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 763:
#line 5753 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 764:
#line 5755 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 765:
#line 5761 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 766:
#line 5765 "gram1.y"
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

  case 767:
#line 5793 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 768:
#line 5795 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 769:
#line 5799 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 770:
#line 5807 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 771:
#line 5813 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 772:
#line 5816 "gram1.y"
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

  case 773:
#line 5873 "gram1.y"
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

  case 774:
#line 5937 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 775:
#line 5939 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 776:
#line 5942 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 777:
#line 5946 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 778:
#line 5950 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 779:
#line 5954 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 780:
#line 5971 "gram1.y"
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

  case 781:
#line 5983 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 782:
#line 5987 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 783:
#line 5991 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 784:
#line 6001 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 785:
#line 6006 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 786:
#line 6011 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 787:
#line 6018 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 788:
#line 6026 "gram1.y"
    {ndim = 0;;}
    break;

  case 789:
#line 6027 "gram1.y"
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

  case 790:
#line 6038 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), q, EXPR_LIST);
            ;}
    break;

  case 791:
#line 6049 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 792:
#line 6051 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 793:
#line 6055 "gram1.y"
    {PTR_SYMB s;
           /* s = make_scalar($1,TYNULL,LOCAL);*/
            s = make_array((yyvsp[(1) - (1)].hash_entry),TYNULL,LLNULL,0,LOCAL);
            s->attr = s->attr | DVM_POINTER_BIT;
            if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
               errstr( "Inconsistent declaration of identifier %s", s->ident, 16);     
            (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL,s);
            ;}
    break;

  case 794:
#line 6066 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 795:
#line 6070 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 796:
#line 6072 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 797:
#line 6076 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 798:
#line 6087 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 799:
#line 6091 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 800:
#line 6093 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 801:
#line 6097 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 802:
#line 6109 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 803:
#line 6111 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 804:
#line 6118 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 805:
#line 6120 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 806:
#line 6124 "gram1.y"
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

  case 807:
#line 6140 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 808:
#line 6150 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 809:
#line 6159 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 810:
#line 6161 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 812:
#line 6168 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 813:
#line 6171 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 814:
#line 6176 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 815:
#line 6186 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 816:
#line 6188 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 817:
#line 6192 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 818:
#line 6194 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 819:
#line 6202 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 820:
#line 6204 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 821:
#line 6208 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 822:
#line 6210 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 833:
#line 6227 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 834:
#line 6232 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 835:
#line 6236 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 836:
#line 6240 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 837:
#line 6244 "gram1.y"
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

  case 838:
#line 6257 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 839:
#line 6261 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 840:
#line 6265 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 841:
#line 6269 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 842:
#line 6272 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 843:
#line 6274 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 844:
#line 6276 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 845:
#line 6280 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 846:
#line 6282 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 847:
#line 6286 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 848:
#line 6291 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 849:
#line 6295 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 850:
#line 6299 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 851:
#line 6301 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 852:
#line 6305 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 853:
#line 6313 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 854:
#line 6319 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 855:
#line 6325 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 856:
#line 6329 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 857:
#line 6331 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 858:
#line 6335 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 859:
#line 6337 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 860:
#line 6341 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 861:
#line 6353 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 862:
#line 6355 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 863:
#line 6359 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 864:
#line 6363 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 865:
#line 6365 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 866:
#line 6369 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 867:
#line 6371 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 868:
#line 6373 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 869:
#line 6375 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 870:
#line 6377 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 871:
#line 6379 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 872:
#line 6381 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 873:
#line 6385 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 874:
#line 6389 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 875:
#line 6393 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 876:
#line 6397 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 877:
#line 6401 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 878:
#line 6408 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 879:
#line 6414 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 880:
#line 6418 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 881:
#line 6421 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 882:
#line 6425 "gram1.y"
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

  case 883:
#line 6438 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 884:
#line 6440 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 885:
#line 6444 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 886:
#line 6446 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 887:
#line 6451 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 888:
#line 6457 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 889:
#line 6463 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 890:
#line 6469 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 891:
#line 6475 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 892:
#line 6481 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6487 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 894:
#line 6493 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 895:
#line 6499 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 896:
#line 6508 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6514 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 898:
#line 6531 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 899:
#line 6539 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 900:
#line 6547 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 901:
#line 6549 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 902:
#line 6551 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 903:
#line 6555 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 904:
#line 6559 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 905:
#line 6561 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 906:
#line 6565 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 907:
#line 6567 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 908:
#line 6575 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 909:
#line 6579 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 910:
#line 6590 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 911:
#line 6594 "gram1.y"
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

  case 912:
#line 6612 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 913:
#line 6614 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 914:
#line 6618 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 915:
#line 6620 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 916:
#line 6624 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 917:
#line 6626 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 918:
#line 6630 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 919:
#line 6634 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 920:
#line 6638 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 921:
#line 6647 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 922:
#line 6651 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 923:
#line 6655 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 924:
#line 6660 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 925:
#line 6664 "gram1.y"
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

  case 926:
#line 6676 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 927:
#line 6678 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 928:
#line 6682 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 929:
#line 6687 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 930:
#line 6691 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 931:
#line 6693 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 932:
#line 6697 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 933:
#line 6699 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 934:
#line 6703 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 935:
#line 6708 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 936:
#line 6715 "gram1.y"
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

  case 937:
#line 6738 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 938:
#line 6740 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 939:
#line 6742 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 940:
#line 6744 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 941:
#line 6746 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 942:
#line 6750 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 943:
#line 6761 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 944:
#line 6765 "gram1.y"
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

  case 945:
#line 6780 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 946:
#line 6787 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 947:
#line 6793 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 948:
#line 6795 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 949:
#line 6799 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 950:
#line 6803 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 951:
#line 6811 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 952:
#line 6815 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 953:
#line 6819 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 954:
#line 6827 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 955:
#line 6832 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 956:
#line 6846 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 957:
#line 6848 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 958:
#line 6852 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 959:
#line 6854 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 960:
#line 6863 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 961:
#line 6865 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 962:
#line 6867 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 963:
#line 6869 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 964:
#line 6905 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 965:
#line 6909 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 966:
#line 6913 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 967:
#line 6917 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 968:
#line 6921 "gram1.y"
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

  case 969:
#line 6933 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 970:
#line 6935 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 971:
#line 6939 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 972:
#line 6942 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 973:
#line 6944 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 974:
#line 6948 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 975:
#line 6953 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 976:
#line 6960 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 977:
#line 6963 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 978:
#line 6971 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 979:
#line 6975 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 980:
#line 6979 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 981:
#line 6982 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 982:
#line 6989 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 983:
#line 6993 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 984:
#line 6997 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 985:
#line 7001 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 986:
#line 7005 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 987:
#line 7009 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 988:
#line 7012 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 989:
#line 7014 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 990:
#line 7018 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 991:
#line 7020 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 992:
#line 7022 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 993:
#line 7026 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 994:
#line 7030 "gram1.y"
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

  case 995:
#line 7042 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 996:
#line 7044 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 997:
#line 7048 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 998:
#line 7050 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 999:
#line 7054 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1000:
#line 7056 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1001:
#line 7060 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1002:
#line 7064 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1003:
#line 7070 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1004:
#line 7082 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1005:
#line 7084 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1006:
#line 7088 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1007:
#line 7090 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1008:
#line 7094 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1009:
#line 7102 "gram1.y"
    { 
                PTR_LLND q;
                if((yyvsp[(16) - (16)].ll_node))
                  q = make_llnd(fi,ARRAY_OP, (yyvsp[(14) - (16)].ll_node), (yyvsp[(16) - (16)].ll_node), SMNULL);
                else
                  q = (yyvsp[(14) - (16)].ll_node);                  
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_CREATE_DIR,SMNULL,(yyvsp[(3) - (16)].ll_node),(yyvsp[(8) - (16)].ll_node),q); 
              ;}
    break;

  case 1010:
#line 7113 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1011:
#line 7115 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1012:
#line 7117 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1013:
#line 7121 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1014:
#line 7125 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1015:
#line 7127 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1016:
#line 7135 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1044:
#line 7168 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1045:
#line 7174 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1046:
#line 7180 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1047:
#line 7186 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1048:
#line 7192 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1049:
#line 7196 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1059:
#line 7213 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1060:
#line 7218 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1061:
#line 7223 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1062:
#line 7229 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1063:
#line 7235 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1064:
#line 7241 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1065:
#line 7246 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1066:
#line 7252 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1067:
#line 7258 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1068:
#line 7264 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1069:
#line 7271 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1070:
#line 7277 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1071:
#line 7283 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1072:
#line 7290 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1074:
#line 7296 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1075:
#line 7302 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1076:
#line 7309 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1077:
#line 7315 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1078:
#line 7321 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1079:
#line 7327 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1080:
#line 7333 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1081:
#line 7339 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1082:
#line 7345 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1083:
#line 7351 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1084:
#line 7357 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1085:
#line 7363 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1086:
#line 7369 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1087:
#line 7375 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1088:
#line 7385 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1089:
#line 7390 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1090:
#line 7396 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1091:
#line 7400 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1096:
#line 7412 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1097:
#line 7420 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1098:
#line 7426 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1099:
#line 7432 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1100:
#line 7437 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1101:
#line 7443 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1102:
#line 7450 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1103:
#line 7456 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1104:
#line 7460 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1111:
#line 7474 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1112:
#line 7483 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1113:
#line 7487 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1114:
#line 7493 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1115:
#line 7500 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1116:
#line 7507 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1117:
#line 7514 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1118:
#line 7523 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1119:
#line 7529 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1120:
#line 7535 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1121:
#line 7539 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1124:
#line 7549 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1125:
#line 7555 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1126:
#line 7561 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1127:
#line 7565 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1130:
#line 7576 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1131:
#line 7582 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1132:
#line 7588 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1133:
#line 7593 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1134:
#line 7601 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1135:
#line 7607 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1136:
#line 7612 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1137:
#line 7619 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1138:
#line 7623 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1150:
#line 7643 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1151:
#line 7648 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1152:
#line 7653 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1153:
#line 7660 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1154:
#line 7665 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1155:
#line 7671 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1156:
#line 7677 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1157:
#line 7682 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1158:
#line 7687 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1159:
#line 7692 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1160:
#line 7696 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1161:
#line 7701 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1162:
#line 7706 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1163:
#line 7710 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1164:
#line 7715 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1165:
#line 7719 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1166:
#line 7725 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1167:
#line 7730 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1168:
#line 7736 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1169:
#line 7741 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1170:
#line 7747 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1171:
#line 7757 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1172:
#line 7761 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1173:
#line 7765 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1174:
#line 7769 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1175:
#line 7774 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1176:
#line 7777 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1183:
#line 7790 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1184:
#line 7794 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1185:
#line 7798 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1186:
#line 7800 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1187:
#line 7802 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1188:
#line 7806 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1189:
#line 7808 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1190:
#line 7810 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1191:
#line 7814 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1192:
#line 7816 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1193:
#line 7820 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1194:
#line 7822 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1195:
#line 7826 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1196:
#line 7829 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1197:
#line 7832 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1198:
#line 7837 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1199:
#line 7839 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1200:
#line 7841 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1201:
#line 7843 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1202:
#line 7845 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1203:
#line 7849 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1204:
#line 7853 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1205:
#line 7858 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1206:
#line 7862 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1207:
#line 7864 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1208:
#line 7868 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1209:
#line 7870 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1210:
#line 7874 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1211:
#line 7878 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1217:
#line 7889 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1218:
#line 7893 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1219:
#line 7897 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1220:
#line 7901 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1221:
#line 7905 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1222:
#line 7909 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1223:
#line 7911 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1226:
#line 7919 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1227:
#line 7923 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1228:
#line 7927 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1229:
#line 7929 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1233:
#line 7939 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1234:
#line 7943 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1235:
#line 7947 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1236:
#line 7951 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1237:
#line 7953 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1238:
#line 7957 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1239:
#line 7961 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;


/* Line 1267 of yacc.c.  */
#line 13653 "gram1.tab.c"
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



