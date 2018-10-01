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
     EXITINTERVAL = 334,
     TEMPLATE_CREATE = 335,
     BINARY_OP = 338,
     UNARY_OP = 339
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
#define EXITINTERVAL 334
#define TEMPLATE_CREATE 335
#define BINARY_OP 338
#define UNARY_OP 339




/* Copy the first part of user declarations.  */
#line 337 "gram1.y"

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
#line 418 "gram1.y"
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
#line 867 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 622 "gram1.y"

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
#line 1023 "gram1.tab.c"

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
#define YYLAST   5590

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  340
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  517
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1246
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2451

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

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
     332,   333,   334,   335,   336,   337,     1,     2,   338,   339
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
    2141,  2143,  2145,  2147,  2151,  2155,  2158,  2162,  2164,  2168,
    2170,  2174,  2176,  2180,  2182,  2187,  2191,  2193,  2197,  2199,
    2203,  2208,  2210,  2215,  2220,  2225,  2229,  2233,  2235,  2239,
    2243,  2245,  2249,  2253,  2255,  2259,  2263,  2265,  2269,  2270,
    2276,  2283,  2292,  2294,  2298,  2300,  2302,  2304,  2309,  2311,
    2312,  2315,  2319,  2322,  2327,  2328,  2330,  2336,  2341,  2348,
    2353,  2355,  2360,  2365,  2367,  2374,  2376,  2380,  2382,  2386,
    2388,  2393,  2395,  2397,  2401,  2403,  2405,  2409,  2411,  2412,
    2414,  2417,  2421,  2423,  2426,  2432,  2437,  2442,  2449,  2451,
    2455,  2457,  2459,  2466,  2471,  2473,  2477,  2479,  2481,  2483,
    2485,  2487,  2491,  2493,  2495,  2497,  2504,  2509,  2511,  2516,
    2518,  2520,  2522,  2524,  2529,  2532,  2540,  2542,  2547,  2549,
    2551,  2563,  2564,  2567,  2571,  2573,  2577,  2579,  2583,  2585,
    2589,  2591,  2595,  2597,  2601,  2603,  2607,  2616,  2618,  2622,
    2625,  2628,  2636,  2638,  2642,  2644,  2648,  2650,  2655,  2657,
    2661,  2663,  2665,  2666,  2668,  2670,  2673,  2675,  2677,  2679,
    2681,  2683,  2685,  2687,  2689,  2691,  2693,  2702,  2709,  2718,
    2725,  2727,  2734,  2741,  2748,  2755,  2757,  2761,  2767,  2769,
    2773,  2782,  2789,  2796,  2801,  2807,  2813,  2816,  2819,  2820,
    2822,  2826,  2828,  2833,  2841,  2843,  2847,  2851,  2853,  2857,
    2863,  2867,  2871,  2873,  2877,  2879,  2881,  2885,  2889,  2893,
    2897,  2908,  2917,  2928,  2929,  2930,  2932,  2935,  2940,  2945,
    2952,  2954,  2956,  2958,  2960,  2962,  2964,  2966,  2968,  2970,
    2972,  2974,  2981,  2986,  2991,  2995,  3005,  3007,  3009,  3013,
    3015,  3021,  3027,  3037,  3038,  3040,  3042,  3046,  3050,  3054,
    3058,  3062,  3069,  3073,  3077,  3081,  3085,  3093,  3099,  3101,
    3103,  3107,  3112,  3114,  3116,  3120,  3122,  3124,  3128,  3132,
    3135,  3139,  3144,  3149,  3155,  3161,  3163,  3166,  3171,  3176,
    3181,  3182,  3184,  3187,  3195,  3202,  3206,  3210,  3218,  3224,
    3226,  3230,  3232,  3237,  3240,  3244,  3248,  3253,  3260,  3264,
    3267,  3271,  3273,  3275,  3280,  3286,  3290,  3297,  3300,  3305,
    3308,  3310,  3314,  3318,  3319,  3321,  3325,  3328,  3331,  3334,
    3337,  3347,  3353,  3355,  3359,  3362,  3365,  3368,  3378,  3383,
    3385,  3389,  3391,  3393,  3396,  3397,  3405,  3407,  3412,  3414,
    3418,  3420,  3422,  3424,  3441,  3442,  3446,  3450,  3454,  3458,
    3465,  3475,  3481,  3483,  3487,  3489,  3491,  3493,  3495,  3497,
    3499,  3501,  3503,  3505,  3507,  3509,  3511,  3513,  3515,  3517,
    3519,  3521,  3523,  3525,  3527,  3529,  3531,  3533,  3535,  3537,
    3539,  3541,  3544,  3547,  3552,  3556,  3561,  3567,  3569,  3571,
    3573,  3575,  3577,  3579,  3581,  3583,  3585,  3591,  3594,  3597,
    3600,  3603,  3606,  3612,  3614,  3616,  3618,  3623,  3628,  3633,
    3638,  3640,  3642,  3644,  3646,  3648,  3650,  3652,  3654,  3656,
    3658,  3660,  3662,  3664,  3666,  3668,  3673,  3677,  3682,  3688,
    3690,  3692,  3694,  3696,  3701,  3705,  3708,  3713,  3717,  3722,
    3726,  3731,  3737,  3739,  3741,  3743,  3745,  3747,  3749,  3751,
    3759,  3765,  3767,  3769,  3771,  3773,  3778,  3782,  3787,  3793,
    3795,  3797,  3802,  3806,  3811,  3817,  3819,  3821,  3824,  3826,
    3829,  3834,  3838,  3843,  3847,  3852,  3858,  3860,  3862,  3864,
    3866,  3868,  3870,  3872,  3874,  3876,  3878,  3880,  3883,  3888,
    3892,  3895,  3900,  3904,  3907,  3911,  3914,  3917,  3920,  3923,
    3926,  3929,  3933,  3936,  3942,  3945,  3951,  3954,  3960,  3962,
    3964,  3968,  3972,  3973,  3974,  3976,  3978,  3980,  3982,  3984,
    3986,  3990,  3993,  3999,  4004,  4007,  4013,  4018,  4021,  4024,
    4026,  4028,  4032,  4035,  4038,  4041,  4046,  4051,  4056,  4061,
    4066,  4071,  4073,  4075,  4077,  4081,  4084,  4087,  4089,  4091,
    4093,  4095,  4097,  4099,  4101,  4106,  4111,  4116,  4119,  4121,
    4123,  4127,  4129,  4131,  4137,  4143,  4145,  4149,  4151,  4153,
    4155,  4161,  4167,  4173,  4175,  4179,  4182
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     341,     0,    -1,    -1,   341,   342,   116,    -1,   343,   344,
     560,    -1,   343,   361,   560,    -1,   343,   506,   560,    -1,
     343,   133,   357,    -1,   343,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   345,   352,    -1,    57,   345,   353,
      -1,   233,   345,   347,   354,    -1,   346,   233,   345,   347,
     354,    -1,   124,   345,   348,   354,   350,    -1,   349,   354,
     350,    -1,   114,   351,   354,   350,    -1,   164,   345,   351,
      -1,    -1,   202,   358,    -1,   195,   358,    -1,    95,   358,
      -1,   351,    -1,   351,    -1,   382,   124,   345,   351,    -1,
     382,   346,   124,   345,   351,    -1,   346,   124,   345,   351,
      -1,   346,   382,   124,   345,   351,    -1,   358,   359,    -1,
     358,   213,    15,   351,    21,    -1,   129,    -1,    -1,   351,
      -1,    -1,   351,    -1,    -1,    15,    21,    -1,    15,   355,
      21,    -1,   356,    -1,   355,     8,   356,    -1,   351,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   366,    -1,   367,
      -1,   368,    -1,   398,    -1,   394,    -1,   561,    -1,   403,
      -1,   404,    -1,   405,    -1,   463,    -1,   384,    -1,   399,
      -1,   409,    -1,   216,   473,    -1,   216,   473,   474,   440,
      -1,   123,   472,    -1,   183,   473,    15,   446,    21,    -1,
     374,    -1,   375,    -1,   380,    -1,   377,    -1,   379,    -1,
     395,    -1,   396,    -1,   397,    -1,   362,    -1,   450,    -1,
     448,    -1,   376,    -1,   142,   473,    -1,   142,   473,   351,
      -1,   141,   473,    15,   364,    21,    -1,   140,   473,    15,
      26,    21,    -1,   107,   515,    -1,    10,    -1,   363,    -1,
     365,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   473,
     474,   351,    -1,   245,     8,   473,   358,   373,   474,   351,
      -1,   112,   473,    -1,   112,   473,   351,    -1,   382,   369,
     351,   473,   456,   388,   393,    -1,   368,     8,   351,   456,
     388,   393,    -1,    -1,     7,     7,    -1,     8,   358,   370,
       7,     7,    -1,   371,    -1,   370,     8,   358,   371,    -1,
     183,    -1,   373,    -1,    44,    -1,    87,   456,    -1,   119,
      -1,   145,    15,   372,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   358,   148,
      -1,   358,   180,    -1,   358,   147,    -1,   194,    -1,   191,
      -1,   145,   473,    15,   372,    21,   474,   351,    -1,   374,
       8,   351,    -1,   178,   473,   474,   351,    -1,   375,     8,
     351,    -1,   230,   473,   474,   402,    -1,   376,     8,   402,
      -1,   191,   473,    -1,   191,   473,   474,   378,   442,    -1,
      -1,   219,   473,    -1,   194,   473,    -1,   194,   473,   474,
     381,   442,    -1,    -1,   386,   383,   390,   383,    -1,   244,
      15,   351,    21,   383,    -1,    -1,   385,   351,    -1,   384,
       8,   351,    -1,    13,    -1,     6,    -1,   387,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   389,    -1,     5,   536,   493,   537,
     383,    -1,     5,   536,    15,   537,     5,    21,    -1,     5,
     536,    15,   537,   479,    21,    -1,    -1,   389,    -1,    15,
     556,   391,   392,    21,    -1,    15,   556,   391,   392,     8,
     556,   391,   392,    21,    -1,   479,    -1,     5,    -1,   547,
     479,    -1,   547,     5,    -1,    -1,    -1,    26,   479,    -1,
      18,   479,    -1,    87,   474,   473,   351,   456,    -1,   394,
       8,   351,   456,    -1,    44,   473,   474,   402,    -1,   395,
       8,   402,    -1,   187,   473,   474,   402,    -1,   396,     8,
     402,    -1,   236,   473,   474,   402,    -1,   397,     8,   402,
      -1,    67,   473,   402,    -1,    67,   473,   401,   402,    -1,
     398,   530,   401,   530,   402,    -1,   398,     8,   402,    -1,
     167,   473,   400,   482,    -1,   399,   530,   400,   530,   482,
      -1,   399,     8,   482,    -1,    37,   351,    37,    -1,    23,
      -1,    37,   351,    37,    -1,   351,   456,    -1,   119,   473,
     474,   351,    -1,   403,     8,   351,    -1,   143,   473,   474,
     351,    -1,   404,     8,   351,    -1,   117,   473,   406,    -1,
     405,     8,   406,    -1,    15,   407,    21,    -1,   408,     8,
     408,    -1,   407,     8,   408,    -1,   351,    -1,   351,    15,
     478,    21,    -1,   487,    -1,   410,    -1,    80,   472,   411,
     413,    -1,   410,   530,   413,    -1,    -1,    -1,   414,    37,
     415,    37,    -1,   416,    -1,   414,     8,   416,    -1,   427,
      -1,   415,     8,   427,    -1,   417,   419,    -1,   417,   419,
     420,    -1,   417,   419,   421,    -1,   417,   419,   420,   421,
      -1,   417,   424,    -1,    -1,   351,    -1,   351,    -1,    15,
     422,    21,    -1,    15,   423,     7,   423,    21,    -1,   436,
      -1,   422,     8,   436,    -1,    -1,   436,    -1,    15,   425,
       8,   418,    26,   422,    21,    -1,   426,    -1,   425,     8,
     426,    -1,   419,   420,    -1,   419,   421,    -1,   419,   420,
     421,    -1,   424,    -1,   428,    -1,   417,   418,     5,   428,
      -1,   431,     5,   428,    -1,   417,   418,    -1,   430,    -1,
     432,    -1,   434,    -1,    36,    -1,    36,   246,   496,    -1,
      27,    -1,    27,   246,   496,    -1,    64,    -1,   429,    -1,
     417,   482,    15,   556,   475,    21,    -1,    59,    -1,   431,
      -1,    17,   431,    -1,    16,   431,    -1,   149,    -1,   149,
     246,   496,    -1,   433,    -1,    17,   433,    -1,    16,   433,
      -1,   201,    -1,   201,   246,   496,    -1,    92,    -1,    92,
     246,   496,    -1,    15,   435,     8,   435,    21,    -1,   432,
      -1,   430,    -1,   437,    -1,    17,   437,    -1,    16,   437,
      -1,   436,    17,   437,    -1,   436,    16,   437,    -1,   438,
      -1,   437,     5,   438,    -1,   437,    37,   438,    -1,   439,
      -1,   439,     9,   438,    -1,   149,    -1,   418,    -1,    15,
     436,    21,    -1,   441,    -1,   440,     8,   441,    -1,   402,
      -1,   401,    -1,   443,   445,   444,    -1,   442,     8,   443,
     445,   444,    -1,    -1,    -1,   351,    -1,   177,    15,   364,
      21,    -1,    47,    15,    26,    21,    -1,   447,    -1,   446,
       8,   447,    -1,   351,    26,   479,    -1,   163,   449,    -1,
     351,    -1,   449,     8,   351,    -1,   248,   473,   451,    -1,
     248,   473,   451,     8,   360,   454,    -1,   248,   473,   451,
       8,   360,   172,    -1,   248,   473,   451,     8,   360,   172,
     452,    -1,   351,    -1,   453,    -1,   452,     8,   453,    -1,
     351,    18,   351,    -1,   351,    -1,   455,    -1,   454,     8,
     455,    -1,   351,    18,   351,    -1,    -1,    15,   457,    21,
      -1,    -1,   458,   459,    -1,   457,     8,   459,    -1,   460,
      -1,     7,    -1,   479,     7,    -1,   479,     7,   460,    -1,
       5,    -1,   479,    -1,   462,    -1,   461,     8,   462,    -1,
     149,    -1,   130,   473,   464,    -1,   131,    -1,   465,    -1,
     464,     8,   465,    -1,   466,    15,   469,    21,    -1,    -1,
     467,   468,    -1,   231,   387,    -1,   382,    -1,   470,    -1,
     469,     8,   470,    -1,   471,    -1,   471,    16,   471,    -1,
     129,    -1,    -1,    -1,    -1,     7,     7,    -1,    -1,   477,
      -1,   479,    -1,   497,    -1,   547,   479,    -1,   556,   476,
      -1,   477,     8,   556,   476,    -1,   479,    -1,   478,     8,
     479,    -1,   480,    -1,    15,   479,    21,    -1,   495,    -1,
     483,    -1,   491,    -1,   498,    -1,   479,    17,   479,    -1,
     479,    16,   479,    -1,   479,     5,   479,    -1,   479,    37,
     479,    -1,   479,     9,   479,    -1,   363,   479,    -1,    17,
     479,    -1,    16,   479,    -1,   479,    25,   479,    -1,   479,
      29,   479,    -1,   479,    31,   479,    -1,   479,    28,   479,
      -1,   479,    30,   479,    -1,   479,    32,   479,    -1,   479,
      24,   479,    -1,   479,    33,   479,    -1,   479,    38,   479,
      -1,   479,    35,   479,    -1,   479,    22,   479,    -1,    34,
     479,    -1,   479,    23,   479,    -1,   479,   363,   479,    -1,
      17,    -1,    16,    -1,   351,    -1,   482,    -1,   485,    -1,
     484,    -1,   482,    15,   556,   475,    21,    -1,   482,    15,
     556,   475,    21,   489,    -1,   485,    15,   475,    21,    -1,
     485,    15,   475,    21,   489,    -1,   483,     3,   129,    -1,
     482,    -1,   485,    -1,   482,    15,   556,   475,    21,    -1,
     485,    15,   475,    21,    -1,   482,   489,    -1,    -1,   489,
      -1,    15,   490,     7,   490,    21,    -1,    -1,   479,    -1,
     492,    -1,   492,   246,   496,    -1,   493,    -1,   493,   246,
     496,    -1,   494,   488,    -1,    36,    -1,    27,    -1,   201,
      -1,    92,    -1,   149,    -1,    64,    -1,   482,   246,    64,
      -1,   493,   246,    64,    -1,    15,   480,     8,   480,    21,
      -1,   482,    -1,   493,    -1,   479,     7,   479,    -1,   479,
       7,    -1,   479,     7,   479,     7,   479,    -1,   479,     7,
       7,   479,    -1,     7,   479,     7,   479,    -1,     7,     7,
     479,    -1,     7,   479,    -1,     7,    -1,    -1,    -1,    14,
     392,   499,   553,   500,    20,    -1,   482,    -1,   485,    -1,
     486,    -1,   502,     8,   556,   486,    -1,   502,     8,   556,
     547,   482,    -1,   501,    -1,   503,     8,   556,   501,    -1,
     503,     8,   556,   547,   482,    -1,    -1,   482,    -1,   505,
       8,   482,    -1,   527,    -1,   526,    -1,   509,    -1,   517,
     509,    -1,   102,   535,   515,    -1,   103,   535,   514,    -1,
     108,   515,    -1,   507,    -1,   517,   507,    -1,   518,   527,
      -1,   518,   239,    -1,   517,   518,   239,    -1,    97,   535,
      15,   479,    21,   239,   514,    -1,    96,   535,   514,    -1,
     106,   535,   514,    -1,   510,    -1,    76,   535,    -1,   519,
     527,    -1,   519,    -1,   517,   519,    -1,   105,   535,   514,
      -1,   562,    -1,   823,    -1,   839,    -1,    89,   535,    15,
     479,    21,    -1,    89,   535,   536,   525,   537,   596,   508,
      -1,    -1,     8,   358,   254,    15,   479,    21,    -1,   254,
      15,   479,    21,    -1,   185,   535,   536,   525,   537,   530,
     523,    26,   479,     8,   479,    -1,   185,   535,   536,   525,
     537,   530,   523,    26,   479,     8,   479,     8,   479,    -1,
      62,   535,   511,   514,    -1,    84,   535,   514,    -1,   110,
     535,   514,    -1,   218,   535,   358,    62,    15,   479,    21,
      -1,   517,   218,   535,   358,    62,    15,   479,    21,    -1,
      15,   513,    21,    -1,   479,    -1,   479,     7,    -1,     7,
     479,    -1,   479,     7,   479,    -1,   512,    -1,   513,     8,
     512,    -1,    -1,   351,    -1,    -1,   351,    -1,    75,    -1,
     516,     7,    -1,   155,   535,    15,   479,    21,    -1,   122,
     535,    15,   520,   522,    21,    -1,   521,    -1,   520,     8,
     521,    -1,   523,    26,   497,    -1,    -1,     8,   479,    -1,
     351,    -1,   523,    26,   479,     8,   479,    -1,   523,    26,
     479,     8,   479,     8,   479,    -1,    -1,   149,    -1,   113,
     535,   514,    -1,    98,   535,   514,    -1,    98,   535,    15,
     479,    21,   514,    -1,   252,   535,    15,   479,    21,    -1,
     517,   252,   535,    15,   479,    21,    -1,   528,   479,    26,
     479,    -1,   188,   535,   483,    18,   479,    -1,    48,   535,
     462,   240,   351,    -1,    77,   535,    -1,   529,    -1,   538,
      -1,    46,   535,    15,   479,    21,   462,     8,   462,     8,
     462,    -1,   531,    -1,   531,    15,    21,    -1,   531,    15,
     532,    21,    -1,   214,   535,   490,    -1,   534,   535,   490,
      -1,    79,   535,   514,    -1,   115,   535,   514,    -1,    45,
     535,    15,   504,   502,    21,    -1,    81,   535,    15,   504,
     503,    21,    -1,   170,   535,    15,   505,    21,    -1,   253,
     535,    15,   479,    21,   483,    26,   479,    -1,   152,   412,
      -1,   186,   535,   462,    -1,    49,   535,   351,    -1,    49,
     535,   351,   530,    15,   461,    21,    -1,    69,   535,    15,
     461,    21,   530,   479,    -1,    -1,     8,    -1,    61,   535,
     351,   556,    -1,   556,   533,    -1,   532,     8,   556,   533,
      -1,   479,    -1,   547,   479,    -1,     5,   462,    -1,   184,
      -1,   232,    -1,    -1,    -1,    -1,   539,   544,    -1,   539,
     559,    -1,   539,     5,    -1,   539,     9,    -1,   541,   544,
      -1,   548,   544,    -1,   548,   543,    -1,   548,   544,   551,
      -1,   548,   543,     8,   551,    -1,   549,   544,    -1,   549,
     544,   553,    -1,   550,    -1,   550,     8,   553,    -1,   540,
     535,   557,    -1,    53,    -1,   215,    -1,   104,    -1,   542,
     535,   557,    -1,   139,    -1,   176,    -1,    66,    -1,   559,
      -1,     5,    -1,    15,   558,    21,    -1,    15,   545,    21,
      -1,   546,    -1,   545,     8,   556,   546,    -1,   558,    -1,
       5,    -1,     9,    -1,   547,   479,    -1,   547,     5,    -1,
     547,     9,    -1,   166,    -1,   197,   535,   557,    -1,   256,
     535,   557,    -1,   190,   535,   558,   557,    -1,   190,   535,
       5,   557,    -1,   552,    -1,   551,     8,   552,    -1,   483,
      -1,    15,   551,     8,   524,    21,    -1,   480,    -1,   555,
      -1,   554,    -1,   480,     8,   480,    -1,   480,     8,   555,
      -1,   555,     8,   480,    -1,   555,     8,   555,    -1,   554,
       8,   480,    -1,   554,     8,   555,    -1,   495,    -1,    15,
     479,    21,    -1,    15,   480,     8,   524,    21,    -1,    15,
     555,     8,   524,    21,    -1,    15,   554,     8,   524,    21,
      -1,    -1,    -1,   559,    -1,    15,   558,    21,    -1,   483,
      -1,   491,    -1,   558,   481,   558,    -1,   558,     5,   558,
      -1,   558,    37,   558,    -1,   558,     9,   558,    -1,   481,
     558,    -1,   558,    23,   558,    -1,   129,    26,   479,    -1,
      -1,   257,    -1,   563,    -1,   611,    -1,   586,    -1,   565,
      -1,   576,    -1,   571,    -1,   623,    -1,   626,    -1,   702,
      -1,   568,    -1,   577,    -1,   579,    -1,   581,    -1,   583,
      -1,   631,    -1,   637,    -1,   634,    -1,   760,    -1,   758,
      -1,   587,    -1,   612,    -1,   641,    -1,   691,    -1,   689,
      -1,   690,    -1,   692,    -1,   693,    -1,   694,    -1,   695,
      -1,   696,    -1,   704,    -1,   706,    -1,   711,    -1,   708,
      -1,   710,    -1,   714,    -1,   712,    -1,   713,    -1,   725,
      -1,   729,    -1,   730,    -1,   733,    -1,   732,    -1,   734,
      -1,   735,    -1,   736,    -1,   737,    -1,   640,    -1,   719,
      -1,   720,    -1,   721,    -1,   724,    -1,   738,    -1,   741,
      -1,   746,    -1,   751,    -1,   753,    -1,   754,    -1,   755,
      -1,   756,    -1,   717,    -1,   759,    -1,    82,   473,   564,
      -1,   563,     8,   564,    -1,   351,   456,    -1,    94,   473,
     566,    -1,   567,    -1,   566,     8,   567,    -1,   351,    -1,
     138,   473,   569,    -1,   570,    -1,   569,     8,   570,    -1,
     351,    -1,   228,   473,   575,   572,    -1,    15,   573,    21,
      -1,   574,    -1,   573,     8,   574,    -1,   479,    -1,   479,
       7,   479,    -1,     7,    15,   478,    21,    -1,   351,    -1,
     259,   473,   351,   456,    -1,   303,   473,   351,   456,    -1,
     576,     8,   351,   456,    -1,   136,   473,   578,    -1,   577,
       8,   578,    -1,   351,    -1,   211,   473,   580,    -1,   579,
       8,   580,    -1,   351,    -1,   205,   473,   582,    -1,   581,
       8,   582,    -1,   351,    -1,    70,   473,   584,    -1,   583,
       8,   584,    -1,   351,    -1,   175,   351,   456,    -1,    -1,
      88,   473,   590,   593,   585,    -1,   204,   535,   590,   594,
     596,   585,    -1,   204,   535,   594,   596,   585,     7,     7,
     588,    -1,   589,    -1,   588,     8,   589,    -1,   590,    -1,
     591,    -1,   351,    -1,   351,    15,   478,    21,    -1,   351,
      -1,    -1,   594,   596,    -1,    15,   595,    21,    -1,   596,
     597,    -1,   595,     8,   596,   597,    -1,    -1,    58,    -1,
      58,    15,   556,   610,    21,    -1,   126,    15,   598,    21,
      -1,   258,    15,   598,     8,   479,    21,    -1,   165,    15,
     479,    21,    -1,     5,    -1,   137,    15,   598,    21,    -1,
      86,    15,   599,    21,    -1,   351,    -1,    15,   600,    21,
     358,   255,   602,    -1,   601,    -1,   600,     8,   601,    -1,
     479,    -1,   479,     7,   479,    -1,   603,    -1,   603,    15,
     604,    21,    -1,   351,    -1,   605,    -1,   604,     8,   605,
      -1,   479,    -1,   750,    -1,    40,   606,   607,    -1,   351,
      -1,    -1,   608,    -1,    17,   609,    -1,   607,    17,   609,
      -1,   479,    -1,   547,   479,    -1,   547,   479,     8,   547,
     479,    -1,    43,   473,   614,   616,    -1,   199,   535,   615,
     616,    -1,   199,   535,   616,     7,     7,   613,    -1,   615,
      -1,   613,     8,   615,    -1,   351,    -1,   482,    -1,    15,
     621,    21,   358,   255,   617,    -1,   620,    15,   618,    21,
      -1,   619,    -1,   618,     8,   619,    -1,   479,    -1,     5,
      -1,   497,    -1,   351,    -1,   622,    -1,   621,     8,   622,
      -1,   351,    -1,     5,    -1,     7,    -1,   624,     7,     7,
     473,   351,   456,    -1,   623,     8,   351,   456,    -1,   625,
      -1,   624,     8,   358,   625,    -1,    82,    -1,   259,    -1,
     303,    -1,    94,    -1,    87,    15,   457,    21,    -1,   228,
     572,    -1,    43,    15,   621,    21,   358,   255,   617,    -1,
      43,    -1,    88,   594,   596,   585,    -1,    88,    -1,    67,
      -1,   382,     8,   358,    93,   473,    15,   627,    21,     7,
       7,   629,    -1,    -1,   628,     7,    -1,   627,     8,     7,
      -1,   630,    -1,   629,     8,   630,    -1,   351,    -1,   127,
     473,   632,    -1,   633,    -1,   632,     8,   633,    -1,   351,
      -1,    74,   473,   635,    -1,   636,    -1,   635,     8,   636,
      -1,   351,    -1,    51,   473,   638,    -1,    51,   473,     8,
     358,    67,     7,     7,   638,    -1,   639,    -1,   638,     8,
     639,    -1,   351,   456,    -1,   168,   535,    -1,   182,   535,
      15,   642,    21,   644,   648,    -1,   643,    -1,   642,     8,
     643,    -1,   482,    -1,   596,   173,   645,    -1,   596,    -1,
     482,    15,   646,    21,    -1,   647,    -1,   646,     8,   647,
      -1,   479,    -1,     5,    -1,    -1,   649,    -1,   650,    -1,
     649,   650,    -1,   654,    -1,   674,    -1,   682,    -1,   651,
      -1,   659,    -1,   661,    -1,   660,    -1,   652,    -1,   655,
      -1,   656,    -1,     8,   358,   209,    15,   697,     7,   698,
      21,    -1,     8,   358,   209,    15,   698,    21,    -1,     8,
     358,    71,    15,   653,     7,   698,    21,    -1,     8,   358,
      71,    15,   698,    21,    -1,   351,    -1,     8,   358,   169,
      15,   658,    21,    -1,     8,   358,   282,    15,   658,    21,
      -1,     8,   358,   191,    15,   658,    21,    -1,     8,   358,
     320,    15,   657,    21,    -1,   479,    -1,   479,     8,   479,
      -1,   479,     8,   479,     8,   479,    -1,   483,    -1,   658,
       8,   483,    -1,     8,   358,   135,    15,   697,     7,   715,
      21,    -1,     8,   358,   135,    15,   715,    21,    -1,     8,
     358,   229,    15,   479,    21,    -1,     8,   358,    41,   662,
      -1,     8,   358,    41,   662,   662,    -1,    15,   596,   663,
     664,    21,    -1,   148,     7,    -1,   180,     7,    -1,    -1,
     665,    -1,   664,     8,   665,    -1,   687,    -1,   687,    15,
     666,    21,    -1,   687,    15,   666,    21,    15,   668,    21,
      -1,   667,    -1,   666,     8,   667,    -1,   479,     7,   479,
      -1,   669,    -1,   668,     8,   669,    -1,   670,     7,   671,
       7,   672,    -1,   670,     7,   671,    -1,   670,     7,   672,
      -1,   670,    -1,   671,     7,   672,    -1,   671,    -1,   672,
      -1,   358,   217,   673,    -1,   358,   157,   673,    -1,   358,
     128,   673,    -1,    15,   477,    21,    -1,     8,   358,   208,
      15,   675,   679,   676,     8,   678,    21,    -1,     8,   358,
     208,    15,   675,   679,   676,    21,    -1,     8,   358,   208,
      15,   675,   677,   676,     7,   678,    21,    -1,    -1,    -1,
     351,    -1,   358,   679,    -1,   678,     8,   358,   679,    -1,
     680,    15,   483,    21,    -1,   681,    15,   658,     8,   479,
      21,    -1,   234,    -1,   192,    -1,   162,    -1,   159,    -1,
      35,    -1,    22,    -1,    24,    -1,    33,    -1,   247,    -1,
     158,    -1,   161,    -1,     8,   358,   223,    15,   684,    21,
      -1,     8,   358,   224,   683,    -1,     8,   358,   226,   683,
      -1,     8,   358,   221,    -1,     8,   358,   221,    15,   687,
      15,   573,    21,    21,    -1,   351,    -1,   685,    -1,   684,
       8,   685,    -1,   687,    -1,   687,    15,   686,    78,    21,
      -1,   687,    15,   686,   573,    21,    -1,   687,    15,   686,
     573,    21,    15,   358,    78,    21,    -1,    -1,   482,    -1,
     687,    -1,   688,     8,   687,    -1,   225,   535,   683,    -1,
     224,   535,   683,    -1,   227,   535,   683,    -1,   226,   535,
     683,    -1,   222,   535,   683,    15,   684,    21,    -1,   206,
     535,   677,    -1,   207,   535,   677,    -1,    72,   535,   653,
      -1,    73,   535,   653,    -1,   210,   535,    15,   697,     7,
     698,    21,    -1,   210,   535,    15,   698,    21,    -1,   351,
      -1,   699,    -1,   698,     8,   699,    -1,   687,    15,   700,
      21,    -1,   687,    -1,   701,    -1,   700,     8,   701,    -1,
     479,    -1,     7,    -1,   237,   473,   703,    -1,   702,     8,
     703,    -1,   351,   456,    -1,   238,   535,   705,    -1,   238,
     535,   705,   674,    -1,   238,   535,   705,   652,    -1,   238,
     535,   705,   674,   652,    -1,   238,   535,   705,   652,   674,
      -1,   351,    -1,   111,   535,    -1,   705,    15,   479,    21,
      -1,   705,    15,   497,    21,    -1,   174,   535,   484,   709,
      -1,    -1,   654,    -1,   109,   535,    -1,   160,   535,   707,
     358,   175,   592,   456,    -1,   160,   535,   707,   358,   321,
     483,    -1,   189,   535,   697,    -1,   212,   535,   697,    -1,
     135,   535,    15,   697,     7,   715,    21,    -1,   135,   535,
      15,   715,    21,    -1,   716,    -1,   715,     8,   716,    -1,
     687,    -1,   687,    15,   478,    21,    -1,   134,   535,    -1,
     134,   535,   654,    -1,   134,   535,   718,    -1,   134,   535,
     654,   718,    -1,     8,   358,   208,    15,   658,    21,    -1,
      50,   535,   723,    -1,    99,   535,    -1,    52,   535,   723,
      -1,   351,    -1,   722,    -1,   722,    15,   478,    21,    -1,
     120,   535,   483,    26,   483,    -1,    83,   535,   728,    -1,
      83,   535,   728,    15,   726,    21,    -1,   556,   727,    -1,
     726,     8,   556,   727,    -1,   547,   479,    -1,   149,    -1,
     100,   535,   728,    -1,   146,   535,   731,    -1,    -1,   479,
      -1,   336,   535,   478,    -1,   101,   535,    -1,   241,   535,
      -1,   242,   535,    -1,    56,   535,    -1,    65,   535,   556,
      15,   532,    21,   392,   474,   658,    -1,   322,   535,    15,
     739,    21,    -1,   740,    -1,   739,     8,   740,    -1,   358,
     315,    -1,   358,   318,    -1,   358,   182,    -1,   220,   535,
      15,   742,    26,   609,    21,   596,   745,    -1,   482,    15,
     743,    21,    -1,   744,    -1,   743,     8,   744,    -1,   599,
      -1,   750,    -1,   132,   688,    -1,    -1,   153,   535,    15,
     482,    18,   747,    21,    -1,   482,    -1,   482,    15,   748,
      21,    -1,   749,    -1,   748,     8,   749,    -1,   750,    -1,
       7,    -1,     5,    -1,   329,   535,   479,     8,   358,   334,
      15,   658,    21,     8,   358,   333,    15,   478,    21,   752,
      -1,    -1,     8,   358,   182,    -1,     8,   358,   318,    -1,
     330,   535,   479,    -1,   331,   535,   479,    -1,   331,   535,
     479,     8,   358,   315,    -1,   332,   535,   479,     8,   358,
     335,    15,   482,    21,    -1,   337,   535,    15,   757,    21,
      -1,   486,    -1,   757,     8,   486,    -1,   809,    -1,   762,
      -1,   761,    -1,   779,    -1,   782,    -1,   783,    -1,   784,
      -1,   785,    -1,   791,    -1,   794,    -1,   799,    -1,   800,
      -1,   801,    -1,   804,    -1,   805,    -1,   806,    -1,   807,
      -1,   808,    -1,   810,    -1,   811,    -1,   812,    -1,   813,
      -1,   814,    -1,   815,    -1,   816,    -1,   817,    -1,   818,
      -1,   268,   535,    -1,   275,   535,    -1,   291,   535,   596,
     763,    -1,   291,   535,   596,    -1,   530,   596,   764,   596,
      -1,   763,   530,   596,   764,   596,    -1,   766,    -1,   775,
      -1,   770,    -1,   771,    -1,   767,    -1,   768,    -1,   769,
      -1,   773,    -1,   774,    -1,   821,    15,   822,   820,    21,
      -1,   191,   765,    -1,   282,   765,    -1,   285,   765,    -1,
     265,   765,    -1,   299,   765,    -1,    84,    15,   358,   772,
      21,    -1,   191,    -1,   299,    -1,   288,    -1,   304,    15,
     479,    21,    -1,   289,    15,   479,    21,    -1,   208,    15,
     776,    21,    -1,   596,   778,     7,   777,    -1,   658,    -1,
      17,    -1,    16,    -1,     5,    -1,    37,    -1,   162,    -1,
     159,    -1,    35,    -1,    22,    -1,    24,    -1,    33,    -1,
     305,    -1,   306,    -1,   307,    -1,   247,    -1,   297,   535,
     596,   780,    -1,   297,   535,   596,    -1,   530,   596,   781,
     596,    -1,   780,   530,   596,   781,   596,    -1,   766,    -1,
     775,    -1,   767,    -1,   768,    -1,   279,   535,   596,   798,
      -1,   279,   535,   596,    -1,   296,   535,    -1,   269,   535,
     596,   786,    -1,   269,   535,   596,    -1,   272,   535,   596,
     798,    -1,   272,   535,   596,    -1,   530,   596,   787,   596,
      -1,   786,   530,   596,   787,   596,    -1,   766,    -1,   775,
      -1,   767,    -1,   768,    -1,   789,    -1,   788,    -1,   290,
      -1,   298,    15,   358,   790,     8,   479,    21,    -1,   298,
      15,   358,   790,    21,    -1,   230,    -1,    94,    -1,   284,
      -1,   295,    -1,   300,   535,   596,   792,    -1,   300,   535,
     596,    -1,   530,   596,   793,   596,    -1,   792,   530,   596,
     793,   596,    -1,   766,    -1,   767,    -1,   280,   535,   596,
     795,    -1,   280,   535,   596,    -1,   530,   596,   796,   596,
      -1,   795,   530,   596,   796,   596,    -1,   798,    -1,   797,
      -1,   266,   765,    -1,   287,    -1,   302,   535,    -1,   281,
     535,   596,   798,    -1,   281,   535,   596,    -1,   292,   535,
     596,   802,    -1,   292,   535,   596,    -1,   530,   596,   803,
     596,    -1,   802,   530,   596,   803,   596,    -1,   766,    -1,
     775,    -1,   770,    -1,   771,    -1,   767,    -1,   768,    -1,
     769,    -1,   773,    -1,   774,    -1,   789,    -1,   788,    -1,
     276,   535,    -1,   293,   535,   596,   763,    -1,   293,   535,
     596,    -1,   277,   535,    -1,   294,   535,   596,   763,    -1,
     294,   535,   596,    -1,   278,   535,    -1,   301,   473,   765,
      -1,   286,   535,    -1,   273,   535,    -1,   290,   535,    -1,
     274,   535,    -1,   264,   535,    -1,   263,   535,    -1,   283,
     535,   765,    -1,   283,   535,    -1,   267,   535,    15,   482,
      21,    -1,   267,   535,    -1,   271,   535,    15,   482,    21,
      -1,   271,   535,    -1,    37,   351,   821,    37,   822,    -1,
     819,    -1,   482,    -1,   820,     8,   819,    -1,   820,     8,
     482,    -1,    -1,    -1,   824,    -1,   837,    -1,   825,    -1,
     838,    -1,   826,    -1,   827,    -1,   308,   535,   828,    -1,
     310,   535,    -1,   312,   535,    15,   834,    21,    -1,   312,
     535,    15,    21,    -1,   312,   535,    -1,   313,   535,    15,
     834,    21,    -1,   313,   535,    15,    21,    -1,   313,   535,
      -1,   358,   359,    -1,   829,    -1,   830,    -1,   829,     8,
     830,    -1,   358,   831,    -1,   358,   833,    -1,   358,   832,
      -1,   147,    15,   834,    21,    -1,   148,    15,   834,    21,
      -1,   180,    15,   834,    21,    -1,   318,    15,   834,    21,
      -1,   319,    15,   834,    21,    -1,   314,    15,   835,    21,
      -1,   315,    -1,   658,    -1,   836,    -1,   835,     8,   836,
      -1,   358,   316,    -1,   358,   317,    -1,   309,    -1,   311,
      -1,   840,    -1,   841,    -1,   842,    -1,   843,    -1,   844,
      -1,   323,    15,   845,    21,    -1,   324,    15,   849,    21,
      -1,   325,    15,   854,    21,    -1,   327,   856,    -1,   328,
      -1,   846,    -1,   845,     8,   846,    -1,   847,    -1,   848,
      -1,   358,   208,    15,   678,    21,    -1,   358,   191,    15,
     658,    21,    -1,   850,    -1,   849,     8,   850,    -1,   851,
      -1,   852,    -1,   853,    -1,   358,   228,    15,   684,    21,
      -1,   358,    41,    15,   684,    21,    -1,   358,   209,    15,
     698,    21,    -1,   855,    -1,   854,     8,   855,    -1,   358,
     326,    -1,   351,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   767,   767,   768,   772,   774,   788,   819,   828,   834,
     854,   863,   879,   891,   901,   908,   914,   919,   924,   948,
     975,   989,   991,   993,   997,  1014,  1028,  1052,  1068,  1082,
    1100,  1102,  1109,  1113,  1114,  1121,  1122,  1130,  1131,  1133,
    1137,  1138,  1142,  1146,  1152,  1162,  1166,  1171,  1178,  1179,
    1180,  1181,  1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,
    1190,  1191,  1196,  1201,  1208,  1210,  1211,  1212,  1213,  1214,
    1215,  1216,  1217,  1218,  1219,  1220,  1221,  1224,  1228,  1236,
    1244,  1253,  1261,  1265,  1267,  1271,  1273,  1275,  1277,  1279,
    1281,  1283,  1285,  1287,  1289,  1291,  1293,  1295,  1297,  1299,
    1301,  1303,  1305,  1310,  1319,  1329,  1337,  1347,  1368,  1388,
    1389,  1391,  1395,  1397,  1401,  1405,  1407,  1411,  1417,  1421,
    1423,  1427,  1431,  1435,  1439,  1443,  1449,  1453,  1457,  1463,
    1468,  1475,  1486,  1499,  1510,  1523,  1533,  1546,  1551,  1558,
    1561,  1566,  1571,  1578,  1581,  1591,  1605,  1608,  1627,  1654,
    1656,  1668,  1676,  1677,  1678,  1679,  1680,  1681,  1682,  1687,
    1688,  1692,  1694,  1701,  1706,  1707,  1709,  1711,  1724,  1730,
    1736,  1745,  1754,  1767,  1768,  1771,  1775,  1790,  1805,  1823,
    1844,  1864,  1886,  1903,  1921,  1928,  1935,  1942,  1955,  1962,
    1969,  1980,  1984,  1986,  1991,  2009,  2020,  2032,  2044,  2058,
    2064,  2071,  2077,  2083,  2091,  2098,  2114,  2117,  2126,  2128,
    2132,  2136,  2156,  2160,  2162,  2166,  2167,  2170,  2172,  2174,
    2176,  2178,  2181,  2184,  2188,  2194,  2198,  2202,  2204,  2209,
    2210,  2214,  2218,  2220,  2224,  2226,  2228,  2233,  2237,  2239,
    2241,  2244,  2246,  2247,  2248,  2249,  2250,  2251,  2252,  2253,
    2256,  2257,  2263,  2266,  2267,  2269,  2273,  2274,  2277,  2278,
    2280,  2284,  2285,  2286,  2287,  2289,  2292,  2293,  2302,  2304,
    2311,  2318,  2325,  2334,  2336,  2338,  2342,  2344,  2348,  2357,
    2364,  2371,  2373,  2377,  2381,  2387,  2389,  2394,  2398,  2402,
    2409,  2416,  2426,  2428,  2432,  2444,  2447,  2456,  2469,  2475,
    2481,  2487,  2495,  2505,  2507,  2511,  2532,  2557,  2559,  2563,
    2595,  2596,  2600,  2600,  2605,  2609,  2617,  2626,  2635,  2645,
    2651,  2654,  2656,  2660,  2668,  2683,  2690,  2692,  2696,  2712,
    2712,  2716,  2718,  2730,  2732,  2736,  2742,  2754,  2766,  2783,
    2812,  2813,  2821,  2822,  2826,  2828,  2830,  2841,  2845,  2851,
    2853,  2857,  2859,  2861,  2865,  2867,  2871,  2873,  2875,  2877,
    2879,  2881,  2883,  2885,  2887,  2889,  2891,  2893,  2895,  2897,
    2899,  2901,  2903,  2905,  2907,  2909,  2911,  2913,  2915,  2919,
    2920,  2931,  3005,  3017,  3019,  3023,  3154,  3204,  3248,  3290,
    3348,  3350,  3352,  3391,  3434,  3445,  3446,  3450,  3455,  3456,
    3460,  3462,  3468,  3470,  3476,  3486,  3492,  3499,  3505,  3513,
    3521,  3537,  3547,  3560,  3567,  3569,  3592,  3594,  3596,  3598,
    3600,  3602,  3604,  3606,  3610,  3610,  3610,  3624,  3626,  3649,
    3651,  3653,  3669,  3671,  3673,  3687,  3690,  3692,  3700,  3702,
    3704,  3706,  3760,  3780,  3795,  3804,  3807,  3857,  3863,  3868,
    3886,  3888,  3890,  3892,  3894,  3897,  3903,  3905,  3907,  3910,
    3912,  3914,  3941,  3950,  3959,  3960,  3962,  3967,  3974,  3982,
    3984,  3988,  3991,  3993,  3997,  4003,  4005,  4007,  4009,  4013,
    4015,  4024,  4025,  4032,  4033,  4037,  4041,  4062,  4065,  4069,
    4071,  4078,  4083,  4084,  4095,  4112,  4135,  4160,  4161,  4168,
    4170,  4172,  4174,  4176,  4180,  4256,  4268,  4275,  4277,  4278,
    4280,  4289,  4296,  4303,  4311,  4316,  4321,  4324,  4327,  4330,
    4333,  4336,  4340,  4358,  4363,  4382,  4401,  4405,  4406,  4409,
    4413,  4418,  4425,  4427,  4429,  4433,  4434,  4445,  4460,  4464,
    4471,  4474,  4484,  4497,  4510,  4514,  4517,  4520,  4524,  4533,
    4536,  4540,  4542,  4548,  4552,  4554,  4556,  4563,  4567,  4569,
    4571,  4575,  4594,  4610,  4619,  4628,  4630,  4634,  4660,  4675,
    4690,  4707,  4715,  4724,  4732,  4737,  4742,  4764,  4780,  4782,
    4786,  4788,  4795,  4797,  4799,  4803,  4805,  4807,  4809,  4811,
    4813,  4817,  4820,  4823,  4829,  4835,  4844,  4848,  4855,  4857,
    4861,  4863,  4865,  4870,  4875,  4880,  4885,  4894,  4899,  4905,
    4906,  4921,  4922,  4923,  4924,  4925,  4926,  4927,  4928,  4929,
    4930,  4931,  4932,  4933,  4934,  4935,  4936,  4937,  4938,  4939,
    4942,  4943,  4944,  4945,  4946,  4947,  4948,  4949,  4950,  4951,
    4952,  4953,  4954,  4955,  4956,  4957,  4958,  4959,  4960,  4961,
    4962,  4963,  4964,  4965,  4966,  4967,  4968,  4969,  4970,  4971,
    4972,  4973,  4974,  4975,  4976,  4977,  4978,  4979,  4980,  4981,
    4982,  4983,  4984,  4988,  4990,  5001,  5022,  5026,  5028,  5032,
    5045,  5049,  5051,  5055,  5066,  5077,  5081,  5083,  5087,  5089,
    5091,  5106,  5118,  5138,  5158,  5180,  5186,  5195,  5203,  5209,
    5217,  5224,  5230,  5239,  5243,  5249,  5257,  5271,  5285,  5290,
    5306,  5321,  5349,  5351,  5355,  5357,  5361,  5390,  5413,  5434,
    5435,  5439,  5460,  5462,  5466,  5474,  5478,  5483,  5485,  5487,
    5489,  5495,  5497,  5501,  5511,  5515,  5517,  5522,  5524,  5528,
    5532,  5538,  5548,  5550,  5554,  5556,  5558,  5565,  5583,  5584,
    5588,  5590,  5594,  5601,  5611,  5640,  5655,  5662,  5680,  5682,
    5686,  5700,  5726,  5739,  5755,  5757,  5760,  5762,  5768,  5772,
    5800,  5802,  5806,  5814,  5820,  5823,  5880,  5944,  5946,  5949,
    5953,  5957,  5961,  5978,  5990,  5994,  5998,  6008,  6013,  6018,
    6025,  6034,  6034,  6045,  6056,  6058,  6062,  6073,  6077,  6079,
    6083,  6094,  6098,  6100,  6104,  6116,  6118,  6125,  6127,  6131,
    6147,  6155,  6166,  6168,  6172,  6175,  6178,  6183,  6193,  6195,
    6199,  6201,  6210,  6211,  6215,  6217,  6222,  6223,  6224,  6225,
    6226,  6227,  6228,  6229,  6230,  6231,  6234,  6239,  6243,  6247,
    6251,  6264,  6268,  6272,  6276,  6279,  6281,  6283,  6287,  6289,
    6293,  6298,  6302,  6306,  6308,  6312,  6320,  6326,  6333,  6336,
    6338,  6342,  6344,  6348,  6360,  6362,  6366,  6370,  6372,  6376,
    6378,  6380,  6382,  6384,  6386,  6388,  6392,  6396,  6400,  6404,
    6408,  6415,  6421,  6426,  6429,  6432,  6445,  6447,  6451,  6453,
    6458,  6464,  6470,  6476,  6482,  6488,  6494,  6500,  6506,  6515,
    6521,  6538,  6540,  6548,  6556,  6558,  6562,  6566,  6568,  6572,
    6574,  6582,  6586,  6598,  6601,  6619,  6621,  6625,  6627,  6631,
    6633,  6637,  6641,  6645,  6654,  6658,  6662,  6667,  6671,  6683,
    6685,  6689,  6694,  6698,  6700,  6704,  6706,  6710,  6715,  6722,
    6745,  6747,  6749,  6751,  6753,  6757,  6768,  6772,  6787,  6794,
    6801,  6802,  6806,  6810,  6818,  6822,  6826,  6834,  6839,  6853,
    6855,  6859,  6861,  6870,  6872,  6874,  6876,  6912,  6916,  6920,
    6924,  6928,  6940,  6942,  6946,  6949,  6951,  6955,  6960,  6967,
    6970,  6978,  6982,  6987,  6989,  6996,  7001,  7005,  7009,  7013,
    7017,  7021,  7024,  7026,  7030,  7032,  7034,  7038,  7042,  7054,
    7056,  7060,  7062,  7066,  7069,  7072,  7076,  7082,  7094,  7096,
    7100,  7102,  7106,  7114,  7126,  7127,  7129,  7133,  7137,  7139,
    7147,  7151,  7154,  7156,  7159,  7161,  7162,  7163,  7164,  7165,
    7166,  7167,  7168,  7169,  7170,  7171,  7172,  7173,  7174,  7175,
    7176,  7177,  7178,  7179,  7180,  7181,  7182,  7183,  7184,  7185,
    7186,  7189,  7195,  7201,  7207,  7213,  7217,  7223,  7224,  7225,
    7226,  7227,  7228,  7229,  7230,  7231,  7234,  7239,  7244,  7250,
    7256,  7262,  7267,  7273,  7279,  7285,  7292,  7298,  7304,  7311,
    7315,  7317,  7323,  7330,  7336,  7342,  7348,  7354,  7360,  7366,
    7372,  7378,  7384,  7390,  7396,  7406,  7411,  7417,  7421,  7427,
    7428,  7429,  7430,  7433,  7441,  7447,  7453,  7458,  7464,  7471,
    7477,  7481,  7487,  7488,  7489,  7490,  7491,  7492,  7495,  7504,
    7508,  7514,  7521,  7528,  7535,  7544,  7550,  7556,  7560,  7566,
    7567,  7570,  7576,  7582,  7586,  7593,  7594,  7597,  7603,  7609,
    7614,  7622,  7628,  7633,  7640,  7644,  7650,  7651,  7652,  7653,
    7654,  7655,  7656,  7657,  7658,  7659,  7660,  7664,  7669,  7674,
    7681,  7686,  7692,  7698,  7703,  7708,  7713,  7717,  7722,  7727,
    7731,  7736,  7740,  7746,  7751,  7757,  7762,  7768,  7778,  7782,
    7786,  7790,  7796,  7799,  7803,  7804,  7805,  7806,  7807,  7808,
    7811,  7815,  7819,  7821,  7823,  7827,  7829,  7831,  7835,  7837,
    7841,  7843,  7847,  7850,  7853,  7858,  7860,  7862,  7864,  7866,
    7870,  7874,  7879,  7883,  7885,  7889,  7891,  7895,  7899,  7903,
    7904,  7905,  7906,  7907,  7910,  7914,  7918,  7922,  7926,  7930,
    7932,  7936,  7937,  7940,  7944,  7948,  7950,  7954,  7955,  7956,
    7960,  7964,  7968,  7972,  7974,  7978,  7982
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
  "CP_SAVE", "CP_WAIT", "FILES", "VARLIST", "STATUS", "EXITINTERVAL",
  "TEMPLATE_CREATE", "BINARY_OP", "UNARY_OP", "$accept", "program", "stat",
  "thislabel", "entry", "new_prog", "proc_attr", "procname", "funcname",
  "typedfunc", "opt_result_clause", "name", "progname", "blokname",
  "arglist", "args", "arg", "filename", "needkeyword", "keywordoff",
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
  "dvm_interval_dir", "interval_number", "dvm_exit_interval_dir",
  "dvm_endinterval_dir", "dvm_traceon_dir", "dvm_traceoff_dir",
  "dvm_barrier_dir", "dvm_check", "dvm_io_mode_dir", "mode_list",
  "mode_spec", "dvm_shadow_add", "template_ref", "shadow_axis_list",
  "shadow_axis", "opt_include_to", "dvm_localize", "localize_target",
  "target_subscript_list", "target_subscript", "aster_expr",
  "dvm_cp_create", "opt_mode", "dvm_cp_load", "dvm_cp_save", "dvm_cp_wait",
  "dvm_template_create", "template_list", "omp_specification_directive",
  "omp_execution_directive", "ompdvm_onethread",
  "omp_parallel_end_directive", "omp_parallel_begin_directive",
  "parallel_clause_list", "parallel_clause", "omp_variable_list_in_par",
  "ompprivate_clause", "ompfirstprivate_clause", "omplastprivate_clause",
  "ompcopyin_clause", "ompshared_clause", "ompdefault_clause", "def_expr",
  "ompif_clause", "ompnumthreads_clause", "ompreduction_clause",
  "ompreduction", "ompreduction_vars", "ompreduction_op",
  "omp_sections_begin_directive", "sections_clause_list",
  "sections_clause", "omp_sections_end_directive", "omp_section_directive",
  "omp_do_begin_directive", "omp_do_end_directive", "do_clause_list",
  "do_clause", "ompordered_clause", "ompschedule_clause", "ompschedule_op",
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
       0,   336,   337,     1,     2,     3,     4,     5,     6,     7,
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
     328,   329,   330,   331,   332,   333,   334,   335,   338,   339
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   340,   341,   341,   342,   342,   342,   342,   342,   342,
     342,   343,   344,   344,   344,   344,   344,   344,   344,   344,
     345,   346,   346,   346,   347,   348,   349,   349,   349,   349,
     350,   350,   351,   352,   352,   353,   353,   354,   354,   354,
     355,   355,   356,   356,   357,   358,   359,   360,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   362,   362,   362,
     362,   362,   363,   364,   364,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   366,   366,   367,   367,   368,   368,   369,
     369,   369,   370,   370,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   372,   372,   372,   373,
     373,   374,   374,   375,   375,   376,   376,   377,   377,   378,
     379,   380,   380,   381,   382,   382,   383,   384,   384,   385,
     385,   386,   387,   387,   387,   387,   387,   387,   387,   388,
     388,   389,   389,   389,   390,   390,   390,   390,   391,   391,
     391,   391,   392,   393,   393,   393,   394,   394,   395,   395,
     396,   396,   397,   397,   398,   398,   398,   398,   399,   399,
     399,   400,   401,   401,   402,   403,   403,   404,   404,   405,
     405,   406,   407,   407,   408,   408,   408,   409,   410,   410,
     411,   412,   413,   414,   414,   415,   415,   416,   416,   416,
     416,   416,   417,   418,   419,   420,   421,   422,   422,   423,
     423,   424,   425,   425,   426,   426,   426,   426,   427,   427,
     427,   428,   428,   428,   428,   428,   428,   428,   428,   428,
     428,   428,   429,   430,   430,   430,   431,   431,   432,   432,
     432,   433,   433,   433,   433,   434,   435,   435,   436,   436,
     436,   436,   436,   437,   437,   437,   438,   438,   439,   439,
     439,   440,   440,   441,   441,   442,   442,   443,   444,   445,
     445,   445,   446,   446,   447,   448,   449,   449,   450,   450,
     450,   450,   451,   452,   452,   453,   453,   454,   454,   455,
     456,   456,   458,   457,   457,   459,   459,   459,   459,   460,
     460,   461,   461,   462,   463,   463,   464,   464,   465,   467,
     466,   468,   468,   469,   469,   470,   470,   471,   472,   473,
     474,   474,   475,   475,   476,   476,   476,   477,   477,   478,
     478,   479,   479,   479,   480,   480,   480,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   480,   480,   481,
     481,   482,   483,   483,   483,   484,   484,   484,   484,   485,
     486,   486,   486,   486,   487,   488,   488,   489,   490,   490,
     491,   491,   491,   491,   491,   492,   492,   492,   492,   493,
     494,   494,   494,   495,   496,   496,   497,   497,   497,   497,
     497,   497,   497,   497,   499,   500,   498,   501,   501,   502,
     502,   502,   503,   503,   503,   504,   505,   505,   506,   506,
     506,   506,   506,   506,   506,   506,   506,   506,   506,   506,
     506,   506,   506,   506,   506,   506,   506,   506,   506,   506,
     506,   506,   507,   507,   508,   508,   508,   509,   509,   510,
     510,   510,   510,   510,   511,   512,   512,   512,   512,   513,
     513,   514,   514,   515,   515,   516,   517,   518,   519,   520,
     520,   521,   522,   522,   523,   524,   524,   525,   525,   526,
     526,   526,   526,   526,   527,   527,   527,   527,   527,   527,
     527,   527,   527,   527,   527,   527,   527,   527,   527,   527,
     527,   527,   528,   529,   529,   529,   529,   530,   530,   531,
     532,   532,   533,   533,   533,   534,   534,   535,   536,   537,
     538,   538,   538,   538,   538,   538,   538,   538,   538,   538,
     538,   538,   538,   539,   540,   540,   540,   541,   542,   542,
     542,   543,   543,   544,   544,   545,   545,   546,   546,   546,
     546,   546,   546,   547,   548,   549,   550,   550,   551,   551,
     552,   552,   553,   553,   553,   554,   554,   554,   554,   554,
     554,   555,   555,   555,   555,   555,   556,   557,   558,   558,
     559,   559,   559,   559,   559,   559,   559,   559,   559,   560,
     560,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     562,   562,   562,   562,   562,   562,   562,   562,   562,   562,
     562,   562,   562,   562,   562,   562,   562,   562,   562,   562,
     562,   562,   562,   562,   562,   562,   562,   562,   562,   562,
     562,   562,   562,   562,   562,   562,   562,   562,   562,   562,
     562,   562,   562,   563,   563,   564,   565,   566,   566,   567,
     568,   569,   569,   570,   571,   572,   573,   573,   574,   574,
     574,   575,   576,   576,   576,   577,   577,   578,   579,   579,
     580,   581,   581,   582,   583,   583,   584,   585,   585,   586,
     587,   587,   588,   588,   589,   589,   590,   591,   592,   593,
     593,   594,   595,   595,   596,   597,   597,   597,   597,   597,
     597,   597,   597,   598,   599,   600,   600,   601,   601,   602,
     602,   603,   604,   604,   605,   605,   605,   606,   607,   607,
     608,   608,   609,   610,   610,   611,   612,   612,   613,   613,
     614,   615,   616,   617,   618,   618,   619,   619,   619,   620,
     621,   621,   622,   622,   622,   623,   623,   624,   624,   625,
     625,   625,   625,   625,   625,   625,   625,   625,   625,   625,
     626,   628,   627,   627,   629,   629,   630,   631,   632,   632,
     633,   634,   635,   635,   636,   637,   637,   638,   638,   639,
     640,   641,   642,   642,   643,   644,   644,   645,   646,   646,
     647,   647,   648,   648,   649,   649,   650,   650,   650,   650,
     650,   650,   650,   650,   650,   650,   651,   651,   652,   652,
     653,   654,   654,   655,   656,   657,   657,   657,   658,   658,
     659,   659,   660,   661,   661,   662,   663,   663,   663,   664,
     664,   665,   665,   665,   666,   666,   667,   668,   668,   669,
     669,   669,   669,   669,   669,   669,   670,   671,   672,   673,
     674,   674,   674,   675,   676,   677,   678,   678,   679,   679,
     680,   680,   680,   680,   680,   680,   680,   680,   680,   681,
     681,   682,   682,   682,   682,   682,   683,   684,   684,   685,
     685,   685,   685,   686,   687,   688,   688,   689,   689,   690,
     690,   691,   692,   693,   694,   695,   696,   696,   697,   698,
     698,   699,   699,   700,   700,   701,   701,   702,   702,   703,
     704,   704,   704,   704,   704,   705,   706,   707,   707,   708,
     709,   709,   710,   711,   711,   712,   713,   714,   714,   715,
     715,   716,   716,   717,   717,   717,   717,   718,   719,   720,
     721,   722,   723,   723,   724,   725,   725,   726,   726,   727,
     728,   729,   730,   731,   731,   732,   733,   734,   735,   736,
     737,   738,   739,   739,   740,   740,   740,   741,   742,   743,
     743,   744,   744,   745,   745,   746,   747,   747,   748,   748,
     749,   749,   750,   751,   752,   752,   752,   753,   754,   754,
     755,   756,   757,   757,   758,   759,   759,   759,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
     759,   760,   761,   762,   762,   763,   763,   764,   764,   764,
     764,   764,   764,   764,   764,   764,   765,   766,   767,   768,
     769,   770,   771,   772,   772,   772,   773,   774,   775,   776,
     777,   778,   778,   778,   778,   778,   778,   778,   778,   778,
     778,   778,   778,   778,   778,   779,   779,   780,   780,   781,
     781,   781,   781,   782,   782,   783,   784,   784,   785,   785,
     786,   786,   787,   787,   787,   787,   787,   787,   788,   789,
     789,   790,   790,   790,   790,   791,   791,   792,   792,   793,
     793,   794,   794,   795,   795,   796,   796,   797,   798,   799,
     800,   800,   801,   801,   802,   802,   803,   803,   803,   803,
     803,   803,   803,   803,   803,   803,   803,   804,   805,   805,
     806,   807,   807,   808,   809,   810,   811,   812,   813,   814,
     815,   816,   816,   817,   817,   818,   818,   819,   820,   820,
     820,   820,   821,   822,   823,   823,   823,   823,   823,   823,
     824,   825,   826,   826,   826,   827,   827,   827,   828,   828,
     829,   829,   830,   830,   830,   831,   831,   831,   831,   831,
     832,   833,   834,   835,   835,   836,   836,   837,   838,   839,
     839,   839,   839,   839,   840,   841,   842,   843,   844,   845,
     845,   846,   846,   847,   848,   849,   849,   850,   850,   850,
     851,   852,   853,   854,   854,   855,   856
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
       1,     1,     1,     3,     3,     2,     3,     1,     3,     1,
       3,     1,     3,     1,     4,     3,     1,     3,     1,     3,
       4,     1,     4,     4,     4,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     0,     5,
       6,     8,     1,     3,     1,     1,     1,     4,     1,     0,
       2,     3,     2,     4,     0,     1,     5,     4,     6,     4,
       1,     4,     4,     1,     6,     1,     3,     1,     3,     1,
       4,     1,     1,     3,     1,     1,     3,     1,     0,     1,
       2,     3,     1,     2,     5,     4,     4,     6,     1,     3,
       1,     1,     6,     4,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     6,     4,     1,     4,     1,
       1,     1,     1,     4,     2,     7,     1,     4,     1,     1,
      11,     0,     2,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     8,     1,     3,     2,
       2,     7,     1,     3,     1,     3,     1,     4,     1,     3,
       1,     1,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     8,     6,     8,     6,
       1,     6,     6,     6,     6,     1,     3,     5,     1,     3,
       8,     6,     6,     4,     5,     5,     2,     2,     0,     1,
       3,     1,     4,     7,     1,     3,     3,     1,     3,     5,
       3,     3,     1,     3,     1,     1,     3,     3,     3,     3,
      10,     8,    10,     0,     0,     1,     2,     4,     4,     6,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     4,     4,     3,     9,     1,     1,     3,     1,
       5,     5,     9,     0,     1,     1,     3,     3,     3,     3,
       3,     6,     3,     3,     3,     3,     7,     5,     1,     1,
       3,     4,     1,     1,     3,     1,     1,     3,     3,     2,
       3,     4,     4,     5,     5,     1,     2,     4,     4,     4,
       0,     1,     2,     7,     6,     3,     3,     7,     5,     1,
       3,     1,     4,     2,     3,     3,     4,     6,     3,     2,
       3,     1,     1,     4,     5,     3,     6,     2,     4,     2,
       1,     3,     3,     0,     1,     3,     2,     2,     2,     2,
       9,     5,     1,     3,     2,     2,     2,     9,     4,     1,
       3,     1,     1,     2,     0,     7,     1,     4,     1,     3,
       1,     1,     1,    16,     0,     3,     3,     3,     3,     6,
       9,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     4,     3,     4,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     2,     2,     2,
       2,     2,     5,     1,     1,     1,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     5,     1,
       1,     1,     1,     4,     3,     2,     4,     3,     4,     3,
       4,     5,     1,     1,     1,     1,     1,     1,     1,     7,
       5,     1,     1,     1,     1,     4,     3,     4,     5,     1,
       1,     4,     3,     4,     5,     1,     1,     2,     1,     2,
       4,     3,     4,     3,     4,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     3,
       2,     4,     3,     2,     3,     2,     2,     2,     2,     2,
       2,     3,     2,     5,     2,     5,     2,     5,     1,     1,
       3,     3,     0,     0,     1,     1,     1,     1,     1,     1,
       3,     2,     5,     4,     2,     5,     4,     2,     2,     1,
       1,     3,     2,     2,     2,     4,     4,     4,     4,     4,
       4,     1,     1,     1,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     4,     2,     1,     1,
       3,     1,     1,     5,     5,     1,     3,     1,     1,     1,
       5,     5,     5,     1,     3,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,    10,    11,     9,     0,     0,     3,   150,
     149,   786,   339,   537,   537,   537,   537,   537,   339,   537,
     554,   537,    20,   537,   537,   158,   537,   560,   339,   154,
     537,   339,   537,   537,   339,   485,   537,   537,   537,   338,
     537,   779,   537,   537,   340,   788,   537,   155,   156,   782,
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
       0,   339,     8,   339,   537,   537,   537,   780,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   339,   537,   781,   537,  1217,   537,
    1218,   537,   537,   537,     0,     0,     0,     0,  1228,   537,
     537,   537,   537,   537,   537,   609,     0,    37,   609,    73,
      48,    49,    50,    65,    66,    76,    68,    69,    67,   109,
      58,     0,   146,   151,    52,    70,    71,    72,    51,    59,
      54,    55,    56,    60,   207,    75,    74,    57,   609,   445,
     440,   453,     0,     0,     0,   456,   439,   438,     0,   508,
     511,   537,   509,     0,   537,     0,   537,     0,     0,   551,
      53,   459,   611,   614,   620,   616,   615,   621,   622,   623,
     624,   613,   630,   612,   631,   617,     0,   777,   618,   625,
     627,   626,   658,   632,   634,   635,   633,   636,   637,   638,
     639,   640,   619,   641,   642,   644,   645,   643,   647,   648,
     646,   671,   659,   660,   661,   662,   649,   650,   651,   653,
     652,   654,   655,   656,   657,   663,   664,   665,   666,   667,
     668,   669,   670,   629,   672,   628,  1026,  1025,  1027,  1028,
    1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,
    1039,  1040,  1041,  1024,  1042,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1050,   460,  1184,  1186,  1188,  1189,  1185,  1187,
     461,  1219,  1220,  1221,  1222,  1223,     0,     0,   340,     0,
       0,     0,     0,     0,     0,     0,   989,    35,     0,     0,
     596,     0,     0,     0,     0,     0,     0,   454,   507,   481,
     210,     0,     0,     0,   481,     0,   312,   339,   724,     0,
     724,   538,     0,    23,   481,     0,   481,   969,     0,   986,
     483,   481,   481,   481,    32,   484,    81,   444,   952,   481,
     946,   105,   481,    37,   481,     0,   340,     0,     0,    63,
       0,     0,   329,    44,     7,   963,     0,     0,     0,     0,
       0,    77,   340,     0,   983,   522,     0,     0,     0,   296,
     295,     0,     0,   810,     0,     0,   340,     0,     0,   538,
       0,   340,     0,     0,     0,   340,    33,   340,    22,   597,
       0,    21,     0,     0,     0,     0,     0,     0,     0,   398,
     340,    45,   140,     0,     0,     0,     0,     0,     0,     0,
       0,   784,   340,     0,   340,     0,     0,   987,   988,     0,
     339,   340,     0,     0,     0,   597,     0,  1170,  1169,  1174,
    1051,   724,  1176,   724,  1166,  1168,  1052,  1157,  1160,  1163,
     724,   724,   724,  1172,  1165,  1167,   724,   724,   724,   724,
    1105,   724,   724,  1182,  1139,     0,    45,  1191,  1194,  1197,
       0,    45,    45,    45,  1246,  1227,     0,     0,     0,     0,
       0,     0,   610,     4,    20,    20,     0,     0,    45,     5,
       0,     0,     0,     0,     0,    45,    20,     0,     0,     0,
     147,   164,     0,     0,     0,     0,   528,     0,   528,     0,
       0,     0,     0,   528,   222,     6,   486,   537,   537,   446,
     441,     0,   457,   448,   447,   455,    82,   172,     0,     0,
       0,   406,     0,   405,   410,   408,   409,   407,   381,     0,
       0,   351,   382,   354,   384,   383,   355,   400,   402,   395,
     353,   356,   596,   398,   542,   543,     0,   380,   379,    32,
       0,   600,   601,   540,     0,   598,   597,     0,   544,   597,
     562,   546,   545,   598,   549,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,   773,   774,   772,     0,
     770,   760,     0,     0,   435,     0,   323,     0,   524,   971,
     972,   968,    45,   310,   805,   807,   970,    36,    13,   596,
       0,   481,     0,   192,     0,   310,     0,   184,     0,   706,
     704,   840,   924,   925,   804,   801,   802,   482,   516,   222,
     435,   310,   673,   980,   975,   470,   341,     0,     0,     0,
       0,     0,   716,   719,   708,     0,   497,   679,   676,   677,
     451,     0,     0,   500,   981,   442,   443,   458,   452,   471,
     106,   499,    45,   517,     0,   199,     0,   382,     0,     0,
      37,    25,   800,   797,   798,   324,   326,     0,     0,    45,
     964,   965,     0,   697,   695,   683,   680,   681,     0,     0,
      78,     0,    45,   984,   982,     0,     0,   945,     0,    45,
       0,    19,     0,     0,     0,     0,   950,     0,     0,     0,
     497,   523,     0,     0,   928,   955,   597,     0,   597,   598,
     139,    34,    12,   143,   574,     0,   761,     0,     0,     0,
     724,   703,   701,   885,   922,   923,     0,   700,   698,   956,
     399,   514,     0,     0,     0,   906,     0,   918,   917,   920,
     919,     0,   688,     0,   686,   691,     0,     0,    37,    24,
       0,   310,   937,   940,     0,    45,     0,   302,   298,     0,
       0,   575,   310,     0,   527,     0,  1109,  1104,   527,  1141,
    1171,     0,   527,   527,   527,   527,   527,   527,  1164,   310,
      46,  1190,  1199,  1200,     0,     0,    45,     0,     0,  1229,
    1231,  1232,     0,     0,  1235,  1237,  1238,  1239,     0,     0,
    1243,     0,  1017,  1018,     0,   985,   349,     0,     0,     0,
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
     578,     0,     0,   351,   353,   550,   584,   583,   552,   674,
     310,   696,   699,   702,   705,   310,   339,     0,   938,     0,
      45,   755,   178,     0,     0,     0,     0,     0,     0,   312,
     809,     0,   529,     0,   475,   479,     0,   469,   596,     0,
     194,   185,     0,   321,     0,   208,     0,   675,   596,     0,
     783,   319,   316,   313,   315,   320,   310,   724,   721,   730,
     725,     0,     0,     0,     0,     0,   722,   708,   724,     0,
     787,     0,   498,   539,     0,     0,     0,    18,   204,     0,
       0,     0,   206,   195,     0,   494,   492,   489,     0,    45,
       0,   329,     0,     0,   332,   330,     0,    45,   966,   381,
     914,   961,     0,     0,   959,     0,     0,    87,    88,    86,
      85,    91,    90,   102,    95,    98,    97,   100,    99,    96,
     101,    94,    92,    89,    93,    83,     0,    84,   197,     0,
       0,     0,     0,     0,     0,   297,     0,   188,   436,     0,
      45,   951,   949,   133,   814,     0,   812,     0,     0,   292,
     539,   180,     0,   577,     0,   576,   287,   287,     0,   756,
       0,   724,   708,   932,     0,     0,   929,   284,   283,    62,
     281,     0,     0,     0,     0,     0,     0,     0,   685,   684,
     135,    14,   182,   939,    45,   942,   941,   146,     0,   103,
      47,     0,     0,   692,     0,   724,   527,     0,  1138,  1108,
    1103,   724,   527,  1140,  1183,   724,   527,   724,   527,   527,
     527,   724,   527,   724,   527,   693,     0,     0,     0,     0,
    1211,     0,     0,  1198,  1202,  1204,  1203,    45,  1193,   848,
    1212,     0,  1196,     0,     0,     0,   992,     0,     0,    45,
    1224,     0,     0,     0,    45,  1225,  1245,    45,  1226,    45,
      45,    45,     0,   390,   391,  1022,     0,    28,    37,     0,
       0,    39,     0,    30,   159,   116,   310,   339,   118,   120,
       0,   121,   114,   122,   130,   129,   123,   124,   125,     0,
     112,   115,    26,     0,   310,     0,     0,   144,   177,     0,
       0,   222,   222,     0,   224,   217,   221,     0,     0,     0,
     352,     0,   359,   361,   358,   357,   375,   377,   371,   365,
     504,   368,   366,   369,   367,   370,   372,   374,   360,   373,
     378,   596,   411,   389,     0,   343,     0,   414,   415,   401,
     412,   403,     0,   596,   513,     0,   532,   530,     0,   596,
     564,   571,   572,   570,   599,   608,   603,   605,   607,   604,
     602,   563,   548,     0,     0,     0,   351,     0,     0,     0,
       0,     0,   694,   776,     0,   786,   789,   779,     0,   788,
     782,     0,   780,   781,   778,   771,     0,   429,     0,     0,
     506,     0,     0,     0,     0,   808,   477,   476,     0,   474,
       0,   193,     0,   527,   803,   427,   428,   432,     0,     0,
       0,   314,   317,   176,     0,   596,     0,     0,     0,     0,
       0,   709,   720,   310,   462,   724,   678,     0,   481,     0,
       0,   201,     0,   394,   974,     0,     0,     0,    16,   799,
     327,   337,     0,   333,   335,   331,     0,     0,     0,     0,
       0,     0,     0,   958,   682,    80,    79,   128,   126,   127,
     340,     0,   487,   423,     0,     0,     0,     0,   191,     0,
     520,     0,     0,   724,     0,     0,    64,   527,   505,   599,
     138,     0,   142,    45,     0,   708,     0,     0,     0,     0,
     927,     0,     0,     0,     0,     0,   907,   909,     0,   689,
     687,     0,    45,   944,    45,   943,   145,   340,     0,   502,
       0,  1173,     0,   724,  1175,     0,   724,     0,     0,   724,
       0,   724,     0,   724,     0,   724,     0,     0,     0,    45,
       0,     0,     0,  1201,     0,  1192,  1195,   996,   994,   995,
      45,   991,     0,    45,  1230,     0,     0,     0,  1236,  1244,
       0,     0,     0,   350,   596,   596,     0,  1021,    15,    29,
      41,     0,   173,   160,   117,     0,    45,     0,    45,    27,
     159,   539,   539,   169,   172,   168,     0,   186,   189,   214,
       0,     0,     0,   247,   245,   252,   249,   263,   256,   261,
       0,     0,   215,   238,   250,   242,   253,   243,   258,   244,
       0,   237,     0,   232,   229,   218,   219,     0,     0,   425,
     351,     0,   387,   596,   347,   344,   345,     0,   398,     0,
     534,   533,     0,     0,   579,   352,     0,     0,     0,   351,
     586,   351,   590,   351,   588,   310,     0,   596,   518,     0,
       0,   973,     0,   311,   478,   480,   172,   322,     0,   596,
     519,     0,   977,   596,   976,   318,   320,   723,     0,     0,
       0,   733,     0,     0,     0,     0,   707,   464,   481,   501,
       0,   203,   202,   381,   493,   490,   488,     0,   491,     0,
     328,     0,     0,     0,     0,     0,     0,   960,     0,  1006,
       0,     0,   422,   417,   947,   948,   718,   310,   954,   437,
     813,   816,   822,   294,   293,     0,   287,     0,     0,   289,
     288,     0,   757,   758,   710,     0,   936,   935,     0,   933,
       0,   930,   282,     0,  1012,  1001,     0,   999,  1002,   752,
       0,     0,   921,   913,   690,     0,     0,     0,     0,     0,
     300,     0,   299,   307,     0,  1182,     0,  1182,  1182,  1118,
       0,  1112,  1114,  1115,  1113,   724,  1117,  1116,     0,  1182,
     724,  1136,  1135,     0,     0,  1179,  1178,     0,     0,  1182,
       0,  1182,     0,   724,  1057,  1061,  1062,  1063,  1059,  1060,
    1064,  1065,  1058,     0,  1146,  1150,  1151,  1152,  1148,  1149,
    1153,  1154,  1147,  1156,  1155,   724,     0,  1099,  1101,  1102,
    1100,   724,     0,  1129,  1130,   724,     0,     0,     0,     0,
       0,     0,  1213,     0,     0,   849,   993,     0,     0,     0,
       0,     0,     0,     0,  1019,     0,   596,     0,  1023,     0,
       0,     0,   108,   791,     0,   111,     0,   173,     0,   146,
       0,   171,   170,   267,   253,   266,     0,   255,   260,   254,
     259,     0,     0,     0,     0,     0,   222,   212,   223,   241,
       0,   222,   234,   235,     0,     0,     0,     0,   278,   223,
     279,     0,     0,   227,   268,   273,   276,   229,   220,     0,
     503,     0,   413,   385,   388,     0,   346,     0,   531,   566,
     567,     0,     0,   351,     0,     0,     0,   775,   769,   785,
       0,     0,     0,   525,     0,   340,   526,     0,   979,     0,
       0,     0,   737,     0,   735,   732,   727,   731,   729,     0,
      45,     0,   463,   450,   205,   334,   336,     0,     0,     0,
     962,   957,   131,     0,  1005,   421,     0,     0,   416,   953,
       0,    45,   811,   823,   824,   829,   833,   826,   834,   835,
     830,   832,   831,   827,   828,     0,     0,     0,     0,   285,
       0,     0,     0,     0,   931,   926,   472,     0,   998,   724,
     908,     0,     0,   883,   104,   306,   301,   303,     0,     0,
       0,  1067,   724,  1068,  1069,    45,  1110,   724,  1137,  1133,
     724,  1182,     0,  1066,    45,  1070,     0,  1071,     0,  1055,
     724,  1144,   724,  1097,   724,  1127,   724,  1205,  1206,  1207,
    1215,  1216,    45,  1210,  1208,  1209,  1234,   895,   896,   897,
     894,   899,   893,   900,   892,   891,   890,   898,   886,     0,
       0,    45,  1233,  1241,  1242,  1240,     0,     0,     0,   393,
      31,   175,   174,     0,     0,   119,   113,   107,     0,     0,
     161,   596,   166,     0,   248,   246,   264,   257,   262,   216,
     222,   596,     0,   240,   236,   223,     0,   233,     0,   270,
     269,     0,   225,   229,     0,     0,     0,     0,     0,   230,
       0,   426,   386,   348,   397,     0,   581,   593,   595,   594,
       0,   430,     0,     0,   806,     0,   433,     0,   978,   753,
     726,     0,     0,    45,     0,     0,     0,   841,   967,   842,
    1011,     0,  1008,  1010,   420,   419,     0,     0,   815,     0,
     825,     0,   288,     0,     0,   762,   759,   716,   711,   712,
     714,   715,   934,  1000,  1004,     0,     0,   381,     0,     0,
       0,     0,     0,   309,   308,   521,     0,     0,     0,  1111,
    1134,     0,  1181,  1180,     0,     0,     0,  1056,  1145,  1098,
    1128,  1214,     0,     0,     0,     0,     0,   392,     0,     0,
     792,   162,   163,     0,     0,   239,   596,   241,     0,   280,
     228,     0,   272,   271,   274,   275,   277,   473,     0,   767,
     766,   768,     0,   764,   431,     0,   990,   434,     0,   738,
     736,     0,   728,     0,     0,     0,  1007,   418,     0,     0,
       0,     0,     0,   904,     0,     0,     0,     0,     0,     0,
     286,   291,   290,     0,     0,     0,   997,   910,   911,     0,
     839,   884,   884,   305,   304,  1083,  1082,  1081,  1088,  1089,
    1090,  1087,  1084,  1086,  1085,  1094,  1091,  1092,  1093,     0,
    1078,  1122,  1121,  1123,  1124,     0,  1183,  1073,  1075,  1074,
       0,  1077,  1076,     0,     0,   887,     0,  1020,   793,     0,
     172,   265,     0,     0,   227,   226,     0,     0,   763,   510,
       0,     0,     0,   466,  1009,   821,   820,     0,   818,   724,
     853,     0,     0,     0,     0,     0,   902,   903,     0,     0,
       0,     0,   713,   915,  1003,    45,     0,     0,     0,     0,
       0,  1120,  1177,  1072,   888,     0,    45,     0,     0,   251,
     231,   495,   765,   754,   741,   734,   739,     0,     0,   817,
     858,   854,     0,     0,     0,     0,     0,     0,     0,     0,
     845,     0,   467,   717,     0,     0,   838,    45,    45,   881,
    1080,  1079,     0,     0,   354,     0,   796,   790,   794,   167,
       0,     0,   465,   819,     0,     0,     0,     0,   851,   843,
       0,   837,     0,   901,   852,     0,   844,     0,   916,     0,
       0,     0,  1119,   889,     0,     0,   496,     0,   744,     0,
     742,   745,   856,   857,     0,   859,   861,     0,     0,     0,
     846,   468,   912,   882,   880,     0,   795,   747,   748,     0,
     740,     0,   855,     0,   850,   836,     0,     0,     0,     0,
     746,   749,   743,   860,     0,     0,   864,   905,   847,  1014,
     750,     0,     0,     0,   862,    45,  1013,   751,   866,   865,
      45,     0,     0,     0,   867,   872,   874,   875,  1015,  1016,
       0,     0,     0,    45,   863,    45,    45,   596,   878,   877,
     876,   868,     0,   870,   871,     0,   873,     0,    45,   879,
     869
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   205,   377,   206,   828,   740,   207,
     896,   608,   792,   678,   558,   894,   895,   434,   897,  1213,
    1488,   208,   209,   609,  1116,  1117,   210,   211,   212,   568,
    1269,  1270,  1120,  1271,   213,   214,   215,   216,  1146,   217,
     218,  1147,   219,   571,   220,   221,   222,   223,  1542,  1543,
     911,  1554,   930,  1812,   224,   225,   226,   227,   228,   229,
     773,  1157,  1158,   230,   231,   232,   735,  1069,  1070,   233,
     234,   699,   445,   923,   924,  1570,   925,   926,  1850,  1580,
    1585,  1586,  1851,  1852,  1581,  1582,  1583,  1572,  1573,  1574,
    1575,  1824,  1577,  1578,  1579,  1826,  2059,  1854,  1855,  1856,
    1159,  1160,  1460,  1461,  1939,  1690,  1138,  1139,   235,   450,
     236,   838,  1956,  1957,  1722,  1723,  1020,   707,   708,  1043,
    1044,  1032,  1033,   237,   745,   746,   747,   748,  1085,  1422,
    1423,  1424,   390,   367,   397,  1314,  1594,  1315,   885,   992,
     611,   630,   612,   613,   614,   615,  1245,  1072,   963,  1864,
     811,   616,   617,   618,   619,   620,  1319,  1596,   621,  1289,
    1861,  1387,  1368,  1388,  1013,  1129,   238,   239,  1902,   240,
     241,   681,  1025,  1026,   698,   416,   242,   243,   244,   245,
    1076,  1077,  1416,  1871,  1872,  1063,   246,   247,   248,   249,
    1195,   250,   966,  1327,   251,   369,   716,  1405,   252,   253,
     254,   255,   256,   641,   633,   972,   973,   974,   257,   258,
     259,   989,   990,   995,   996,   997,  1316,   794,   634,   789,
     553,   260,   261,   262,   702,   263,   718,   719,   264,   756,
     757,   265,   491,   823,   824,   826,   266,   267,   754,   268,
     808,   269,   802,   270,   690,  1060,   271,   272,  2108,  2109,
    2110,  2111,  1677,  1057,   400,   710,   711,  1056,  1642,  1705,
    1893,  1894,  2305,  2306,  2369,  2370,  2388,  2400,  2401,  1710,
    1891,   273,   274,  1692,   662,   797,   798,  1879,  2172,  2173,
    1880,   659,   660,   275,   276,   277,   278,  2023,  2024,  2337,
    2338,   279,   743,   744,   280,   695,   696,   281,   674,   675,
     282,   283,  1135,  1136,  1682,  2098,  2267,  2268,  1922,  1923,
    1924,  1925,  1926,   692,  1927,  1928,  1929,  2321,  1220,  1930,
    1931,  1932,  2270,  2346,  2374,  2375,  2405,  2406,  2423,  2424,
    2425,  2426,  2427,  2438,  1933,  2120,  2287,   804,  1799,  2008,
    2009,  2010,  1934,   816,  1475,  1476,  1951,  1153,  2284,   284,
     285,   286,   287,   288,   289,   290,   291,   785,  1155,  1156,
    1698,  1699,   292,   832,   293,   768,   294,   769,   295,  1132,
     296,   297,   298,   299,   300,  1093,  1094,   301,   751,   302,
     303,   304,   670,   671,   305,   306,  1390,  1632,   704,   307,
     308,   764,   309,   310,   311,   312,   313,   314,   315,  1225,
    1226,   316,  1163,  1706,  1707,  2206,   317,  1670,  2091,  2092,
    1708,   318,  2416,   319,   320,   321,   322,  1246,   323,   324,
     325,   326,   327,  1196,  1753,   850,  1731,  1732,  1733,  1757,
    1758,  1759,  2240,  1760,  1761,  1734,  2127,  2331,  2229,   328,
    1202,  1781,   329,   330,   331,   332,  1186,  1735,  1736,  1737,
    2235,   333,  1204,  1785,   334,  1192,  1740,  1741,  1742,   335,
     336,   337,  1198,  1775,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,  1746,
    1747,   851,  1497,   353,   354,   355,   356,   357,   861,   862,
     863,  1214,  1215,  1216,  1221,  1791,  1792,   358,   359,   360,
     361,   362,   363,   364,   365,   868,   869,   870,   871,   873,
     874,   875,   876,   877,   879,   880,   545
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -1954
static const yytype_int16 yypact[] =
{
   -1954,    96, -1954, -1954, -1954, -1954,   129,  4624, -1954, -1954,
   -1954,   157, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,   166, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954,   130, -1954, -1954,   601,   163, -1954, -1954, -1954,   130,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,   168,   168, -1954, -1954, -1954, -1954, -1954,   168,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
     255, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,   168, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954,   333, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
     367,   380, -1954, -1954, -1954, -1954, -1954,   130, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954,   130, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954,   425,   473,   503,   168, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954,   298,  1777,   568,   298, -1954,
   -1954, -1954,   617,   638,   686,   709, -1954, -1954, -1954,   751,
     720,   168, -1954, -1954,   743,   780,   786,   789,   542,   182,
     820,   826,   842, -1954,   139, -1954, -1954, -1954,   298, -1954,
   -1954, -1954,   765,   555,  1557,  2054, -1954, -1954,  1465, -1954,
     804, -1954, -1954,  2607, -1954,   854, -1954,  1385,   854,   913,
   -1954, -1954,   921, -1954, -1954, -1954,   939,   946,   956,   966,
     987, -1954, -1954, -1954, -1954,   991,  1078, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,  1006, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954,   137,   168,   887,  1015,
    1024,   901,   168,   168,   158,   168, -1954,   168,   168,  1041,
   -1954,   187,  1048,   168,   168,   168,   168, -1954, -1954,   168,
   -1954,  1055,   168,   932,   168,  1089, -1954, -1954, -1954,   168,
   -1954,  1092,   168, -1954,   168,  1098,   181, -1954,   932, -1954,
     168,   168,   168,   168, -1954, -1954, -1954, -1954, -1954,   168,
   -1954,   168,   168,   568,   168,  1102,   887,   168,  1112, -1954,
     168,   168, -1954, -1954, -1954,  1131,  1130,   168,   168,  1147,
    1154,   168,   887,  1166,  1465, -1954,  1184,  1203,   168, -1954,
    1205,   168,  1226, -1954,  1223,   168,   887,  1266,  1278, -1954,
     901,   887,   168,   168,  1424,    79,   168,   118, -1954, -1954,
     188, -1954,   254,   168,   168,   168,  1282,   168,   168,  1465,
     148, -1954, -1954,  1295,   168,   168,   168,   168,   168,  2697,
     168, -1954,   887,   168,   887,   168,   168, -1954, -1954,   168,
   -1954,   887,   168,  1297,  1334, -1954,   168, -1954, -1954,  1340,
   -1954, -1954,  1342, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954,  1344, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954,   168, -1954, -1954,  1346,  1351,
    1355, -1954, -1954, -1954, -1954, -1954,  1465,  1465,  1465,  1465,
    1465,  1365, -1954, -1954, -1954, -1954,  1162,   138, -1954, -1954,
     168,   168,   168,   168,  1325, -1954, -1954,  1265,   168,   168,
   -1954,   886,   168,   168,   168,   168,   168,   266,   168,  1226,
     168,   168,  1102, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954,  1014, -1954, -1954, -1954, -1954, -1954, -1954,  1465,  1465,
    1465, -1954,  1465, -1954, -1954, -1954, -1954, -1954, -1954,  1465,
    3244, -1954,    72,  1382, -1954,  1378, -1954,  1151,  1152,  1380,
   -1954, -1954,  1383,  1465, -1954, -1954,  1733, -1954, -1954,  1379,
    1335,  1382, -1954, -1954,   992,   -22, -1954,  1733, -1954, -1954,
   -1954,  1398,   369,   109,  2932,  2932,   168,   168,   168,   168,
     168,   168,   168,  1400, -1954,   168, -1954, -1954, -1954,   593,
   -1954, -1954,  1393,   168, -1954,  1465, -1954,  1170,   459, -1954,
    1396, -1954, -1954,  1399,  1407, -1954, -1954, -1954, -1954, -1954,
    2737,   168,  1401, -1954,   168,  1399,   168, -1954,   901, -1954,
   -1954, -1954, -1954, -1954, -1954,  1409, -1954, -1954, -1954, -1954,
   -1954,  1399, -1954, -1954,  1405, -1954, -1954,   602,  1178,   168,
     635,   498, -1954,  1408,  1249,  1465,  1273, -1954,  1417, -1954,
   -1954,  1465,  1465, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954,   168, -1954,   168,  1413,   478,   168,
     568, -1954, -1954,  1422, -1954,  1423, -1954,  1420,   834, -1954,
    1429, -1954,   168, -1954, -1954, -1954,  1437, -1954,  1426,  3275,
   -1954,   168, -1954,  5552, -1954,   168,  1465, -1954,  1433, -1954,
     168, -1954,   168,   168,   168,  1382,  1043,   168,   168,   168,
    1273, -1954,   168,   574, -1954, -1954, -1954,  1335,   992, -1954,
   -1954, -1954, -1954, -1954, -1954,   137, -1954,  1393,  1447,  1408,
   -1954, -1954, -1954, -1954, -1954, -1954,   168, -1954, -1954, -1954,
    5552, -1954,   187,  1394,   168, -1954,  1442, -1954, -1954, -1954,
   -1954,  1446,  3396,   641, -1954, -1954,   333,   168,   568, -1954,
     168,  1399, -1954,  1454,  1444, -1954,   168, -1954,  1455,  1465,
    1465, -1954,  1399,   168,   111,   168,  1179,  1179,   162,  1179,
   -1954,  1452,   191,   192,   214,   409,   523,   552, -1954,  1399,
     796, -1954,  1460, -1954,   136,   183, -1954,   398,   657, -1954,
   -1954, -1954,    51,   682, -1954, -1954, -1954, -1954,  1143,   734,
   -1954,  3436,  5552,  3508,  3553,  1466,  5552,   168,   168,   168,
   -1954, -1954, -1954, -1954,   755, -1954, -1954,  1272,  1399, -1954,
   -1954, -1954, -1954,  1711,   168, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,  1399, -1954, -1954, -1954, -1954,  1468, -1954,  1468,
   -1954, -1954, -1954, -1954,   213, -1954,   422, -1954,  1463, -1954,
   -1954,  3588,  1475,  1477,  1477,  2167, -1954,  1465,  1465,  1465,
    1465,  1465,  1465,  1465,  1465,  1465,  1465,  1465,  1465,  1465,
    1465,  1465,  1465,  1465,  1465,  1465, -1954,  1427,  1358,  1472,
     377,   104,  1465, -1954, -1954, -1954,   774,  1289, -1954, -1954,
   -1954, -1954,   782, -1954,  1304,   822,  1465,  1485,  1335,  1335,
    1335,  1335,  1335, -1954,  1135, -1954,   369,   369,  1382,  1487,
   -1954,  2932,  5552,   189,   222, -1954,  1489,  1492, -1954, -1954,
    1399, -1954, -1954, -1954, -1954,  1399, -1954,   585, -1954,   137,
   -1954, -1954, -1954,   168,  3742,   168,  1488,  1465,  1435, -1954,
   -1954,   168, -1954,  1465,  3677, -1954,   812, -1954, -1954,  1467,
   -1954, -1954,   827, -1954,   168, -1954,   168, -1954, -1954,  1178,
   -1954, -1954, -1954, -1954, -1954,  3776,  1399, -1954, -1954, -1954,
    1491,  1493,  1494,  1495,  1496,  1497, -1954,  1249, -1954,   168,
   -1954,  3807, -1954, -1954,   168,  3843,  3880, -1954,  1500,   865,
    1499,  1380, -1954, -1954,   168, -1954,  1509, -1954,  1498, -1954,
     168, -1954,  1389,    95, -1954, -1954,   345, -1954, -1954,  1513,
   -1954,  1506,  1515,   882, -1954,   168,  1502, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954,  1504, -1954, -1954,   465,
    1505,  1510,  3945,  2752,   -80, -1954,  1490, -1954, -1954,   890,
   -1954, -1954, -1954, -1954, -1954,   905, -1954,  1507,   944, -1954,
   -1954, -1954,  1465, -1954,  1159, -1954, -1954, -1954,   958, -1954,
    1523, -1954,  1249,  1516,  1528,   960, -1954, -1954, -1954,  1537,
   -1954,  1531,  1532,  1522,   168,  1465,  1465,  2697, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954,  1541,  1544, -1954,   480, -1954,
   -1954,  3990,  4051, -1954,  1538, -1954,   564,  1539, -1954, -1954,
   -1954, -1954,   567, -1954, -1954, -1954,   572, -1954,   613,   622,
     623, -1954,   625, -1954,   628, -1954,  1543,  1546,  1547,  1550,
   -1954,  1551,  1552, -1954, -1954, -1954, -1954, -1954, -1954,  1382,
    1561,  1549, -1954,  1553,   -71,   962, -1954,  1560,  1562, -1954,
   -1954,  1564,  1565,  1567, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,  1465,   578,   661, -1954,   983, -1954,   568,   168,
      99, -1954,  1569, -1954,  1586, -1954,  1399, -1954, -1954, -1954,
    1577, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,  1113,
   -1954, -1954, -1954,   168,  1399,   125,  1819, -1954, -1954,   168,
     168, -1954,   840,   422, -1954,  1578, -1954,  1533,  1465,  2932,
   -1954,  1465,  1477,  1477,   582,   582,  2167,   752,  3914,  2326,
    5552,  2326,  2326,  2326,  2326,  2326,  3914,  4086,  1477,  4086,
    1941,  1472, -1954, -1954,  1576,  1593,  2658, -1954, -1954, -1954,
   -1954, -1954,  1597, -1954, -1954,   901,  5552, -1954,  1465, -1954,
   -1954, -1954, -1954,  5552,   156,  5552,  1485,  1485,   922,  1485,
     632, -1954,  1487,  1599,   369,  4117,  1600,  1601,  1603,  2932,
    2932,  2932, -1954, -1954,   168,  1602, -1954, -1954,  1604,  1408,
   -1954,   333, -1954, -1954, -1954, -1954,  1360, -1954,   995,   901,
   -1954,   901,   997,  1613,  1003, -1954,  5552,  1465,  2737, -1954,
    1011, -1954,   901,  1468, -1954,   759,   764, -1954,  1017,  1406,
    1023, -1954,  2151, -1954,   498, -1954,  1606,   168,   168,  1465,
     168, -1954, -1954,  1399, -1954, -1954, -1954,  1388,   168,  1465,
     168, -1954,   168, -1954,  1382,  1465,  1607,  2752, -1954, -1954,
   -1954, -1954,  1028, -1954,  1608, -1954,  1614,  1615,  1616,  1414,
    1465,   168,   168, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
     887,   168, -1954,  2803,  3087,  1618,   168,   168, -1954,   168,
   -1954,   -59,   168, -1954,  1465,   168, -1954,  1468,  5552, -1954,
    1627,   438,  1627, -1954,   168,  1249,  1630,  2838,   168,   168,
   -1954,   187,  1465,   915,  1465,  1032, -1954,  1625,  1034,  5552,
   -1954,    29, -1954, -1954, -1954, -1954, -1954,   887,   358, -1954,
     168, -1954,   660, -1954, -1954,   -86, -1954,   119,   794, -1954,
     844, -1954,   579, -1954,   -30, -1954,   168,   168,   168, -1954,
     168,   168,   796, -1954,   168, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,   168, -1954, -1954,   168,   168,   168, -1954, -1954,
    1308,  1326,  1315,  5552, -1954,  1472,   168, -1954, -1954, -1954,
   -1954,   168,   869, -1954, -1954,  1628, -1954,  1637, -1954, -1954,
    1586, -1954, -1954, -1954, -1954,  5552,  2289, -1954, -1954, -1954,
     691,   460,   460,  1410,  1412, -1954, -1954,  1416,  1419,  1425,
     224,   168, -1954, -1954, -1954, -1954,  1646, -1954, -1954, -1954,
    1578, -1954,  1644, -1954,   133,  1639, -1954,  1640,  4158, -1954,
    1638,  1648,  1380, -1954, -1954,  4214, -1954,  1465,  1465,  1289,
   -1954,  5552,  1733,   369, -1954,   445,  2932,  2932,  2932,   448,
   -1954,   474, -1954,   524, -1954,  1399,   168, -1954, -1954,  1652,
    1037, -1954,  1663, -1954,  5552, -1954, -1954, -1954,  1465, -1954,
   -1954,  1465, -1954, -1954, -1954, -1954,  5552, -1954,  1406,  1465,
    1653, -1954,  1654,  1655,  4245,  1669, -1954,    73,   168, -1954,
    1039, -1954, -1954,  1656,  5552, -1954, -1954,  4214, -1954,  1389,
   -1954,  1389,   168,   168,   168,  1040,  1066, -1954,   168,  1664,
    1657,  1465,  4280,  2877, -1954, -1954, -1954,  1399,  1382, -1954,
   -1954,  1508,  1672,  5552, -1954,   168, -1954,  1668,  1670, -1954,
   -1954,  1431,  1676, -1954, -1954,  1680, -1954,  5552,  1080, -1954,
    1082, -1954, -1954,  4359, -1954, -1954,  1084, -1954, -1954,  5552,
    1673,   168, -1954, -1954, -1954,  1674,  1678,  1483,  1624,   168,
     168,  1682,  1694, -1954,   481, -1954,  1688, -1954, -1954, -1954,
    1689, -1954, -1954, -1954, -1954, -1954, -1954, -1954,   660, -1954,
   -1954, -1954, -1954,   -86,   168, -1954, -1954,  1087,  1690, -1954,
    1691, -1954,  1692, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954,   794, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954,   844, -1954, -1954, -1954,
   -1954, -1954,   579, -1954, -1954, -1954,   -30,  1695,  1696,  1697,
     899,  1114, -1954,  1698,  1699,  1382, -1954,  1115,  1049,  1117,
    1120,  1129,  1139,  1700, -1954,  1706,  1472,  1703, -1954,  1704,
    1465,  1465, -1954, -1954,  1705, -1954,  1545,   869,  2312, -1954,
    1149, -1954,  5552, -1954, -1954, -1954,  1702, -1954, -1954, -1954,
   -1954,   377,   377,   377,   377,   377,   840, -1954,  1714,  1707,
    1715,   840,  1639, -1954,   422,   133,   122,   122, -1954, -1954,
   -1954,  1157,  1724,   801,   423, -1954,  1725,   133, -1954,  1465,
   -1954,  1717, -1954,  1380, -1954,  2658,  5552,  1723, -1954, -1954,
     992,  1685,  1730,  1165,  1731,  1732,  1735, -1954, -1954, -1954,
    1720,    91,   901, -1954,   168,   887,  5552,    91,  5552,  1406,
    1465,  1736,  4610,  1198, -1954, -1954, -1954, -1954, -1954,  1465,
   -1954,  1743, -1954, -1954, -1954, -1954, -1954,  1201,  1209,  1212,
   -1954, -1954, -1954,  1156, -1954,  5552,  1465,  1465,  4957, -1954,
     168, -1954, -1954,  1672, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954,  1737,   438,  1739,  3275, -1954,
     168,   168,   168,  2838, -1954, -1954, -1954,   915, -1954, -1954,
   -1954,  2418,   168, -1954, -1954,  1722,  1738, -1954,   168,   168,
    1465, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,   119, -1954, -1954, -1954,  1465, -1954,  1465, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,  1744,
    1747, -1954, -1954, -1954, -1954, -1954,   168,   168,  1745,   811,
   -1954,  5552,  5552,  1215,  1760, -1954, -1954, -1954,  1749,  4991,
   -1954, -1954, -1954,   691, -1954, -1954, -1954, -1954, -1954, -1954,
     840, -1954,   168, -1954, -1954,  1753,  1748, -1954,   705,   423,
     423,   133, -1954,   133,   122,   122,   122,   122,   122,  1317,
    5022, -1954, -1954, -1954, -1954,  1465, -1954, -1954, -1954, -1954,
    1859, -1954,   168,  1765,  1407,   168, -1954,   168, -1954,  5053,
   -1954,  1465,  1465, -1954,  5084,  1524,  1465, -1954, -1954, -1954,
   -1954,  1216, -1954, -1954,  5552,  5552,  1465,  1761, -1954,    67,
   -1954,  1465, -1954,  1756,  1759, -1954, -1954,  1767,  1775, -1954,
   -1954, -1954, -1954, -1954,  1658,  1763,  1224,  1778,  1779,  1227,
    1042,   168,   168, -1954, -1954,  5552,   825,  1766,    -1, -1954,
   -1954,  1751, -1954, -1954,   -15,  5115,  5146, -1954, -1954, -1954,
   -1954, -1954,   168,   168,  1049,  1235,  1770,   868,  1792,  1794,
   -1954, -1954, -1954,  1819,  1782, -1954,  1472, -1954,   133, -1954,
    1317,  1787,   423,   423, -1954, -1954, -1954, -1954,  5177, -1954,
    4214, -1954,  1236, -1954, -1954,   901,  1561, -1954,  1406,  5552,
   -1954,  1554, -1954,  1796,  5208,  1156, -1954,  5552,  2357,  1797,
    1800,  1801,  1803,  1804,  1807,   168,   168,  1811,  1812,  5239,
   -1954, -1954, -1954,  1465,   168,   168, -1954, -1954,  1813,   168,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,  1824,
   -1954, -1954, -1954, -1954, -1954,  1238, -1954, -1954, -1954, -1954,
    1816, -1954, -1954,   205,  1830, -1954,  1831, -1954, -1954,  1834,
   -1954, -1954,  1821,  1239,  1317, -1954,  1465,  1859, -1954, -1954,
    1465,   168,  1465, -1954, -1954, -1954,  5552,  1246, -1954, -1954,
    1797,   168,   168,   168,   168,   168, -1954, -1954,  1465,  1465,
    1465,  1247, -1954, -1954,  1835, -1954,  1254,  1837,  1261,   168,
    1465, -1954, -1954, -1954, -1954,  1465, -1954,   168,  1826, -1954,
   -1954,  5270, -1954,  5552, -1954, -1954,  1833,  5301,  2357, -1954,
     321, -1954,  1842,  1263,  1264,  1844,  1269,  1843,  1270,  5332,
    5363,  1836,  5394, -1954,   168,  1774, -1954, -1954, -1954, -1954,
    1561, -1954,  5425,  5456,  1054,  1526, -1954,  1852, -1954, -1954,
    1465,  2078, -1954, -1954,  1854,  1856,   168,   168, -1954, -1954,
     168, -1954,  2697, -1954, -1954,  1465, -1954,  1465, -1954,  1851,
    1271,  1279, -1954, -1954,  1862,   168,  5552,   168,  5552,  1280,
   -1954, -1954, -1954, -1954,  1287, -1954,  1863,  1290,  1307,  1309,
    5487,  5552, -1954, -1954, -1954,  1465, -1954, -1954,  1864,  2078,
   -1954,   168, -1954,  1465, -1954, -1954,  1858,  1465,  1314,  1465,
    1868, -1954, -1954, -1954,  5521,  1316, -1954, -1954,  5552,  1872,
   -1954,  1465,  1465,  1465,  1876, -1954, -1954, -1954,  5552, -1954,
   -1954,   -48,    60,  1318, -1954,  1880,  1885, -1954, -1954, -1954,
    1881,  1881,  1881, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,   323,  1890, -1954,  1776, -1954,  1321, -1954, -1954,
   -1954
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1954, -1954, -1954, -1954, -1954,    -9,  1684,  1019, -1954, -1954,
    -655,   -52, -1954, -1954,  -383, -1954,   659, -1954,   -50,  1013,
   -1954, -1954, -1954,  2041,   -26, -1954, -1954, -1954, -1954, -1954,
   -1954,    97,   368,   738, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954,  -163,  -878, -1954, -1954, -1954,   835,   370,  1348,
   -1954,  -236, -1513,   105, -1954, -1954, -1954, -1954, -1954, -1954,
    1347,  -297,    -5, -1954, -1954, -1954,  1343, -1954,  -500, -1954,
   -1954, -1954, -1954,  1229, -1954, -1954,   648, -1234, -1493,  1004,
     352, -1439,  -225,  -118,  1010, -1954,    93,   107, -1739, -1954,
   -1506, -1216, -1485,  -218, -1954,   -93, -1532, -1591, -1403, -1954,
   -1954,   482,   797,   259,  -153,    18, -1954,   500, -1954, -1954,
   -1954, -1954, -1954,  -166, -1954,     0,  -503,   941, -1954,   923,
     575,   604,  -369, -1954, -1954,   900, -1954, -1954, -1954, -1954,
     324,   319,  1907,  2503,  -341, -1272,   121,  -450, -1001,  1099,
    -585,  -604,  1719,   -64,  1529,  -861,  -962, -1954, -1954,  -605,
    -581,  -233, -1954,  -898, -1954,  -539,  -926, -1108, -1954, -1954,
   -1954,   102, -1954, -1954,  1291, -1954, -1954,  1750, -1954,  1752,
   -1954, -1954,   614, -1954,  -375,    17, -1954, -1954,  1754,  1755,
   -1954,   581, -1954,  -714,  -453,  1214, -1954,  1128, -1954, -1954,
    -206, -1954,   972,   408, -1954,  4410,  -395, -1079, -1954, -1954,
   -1954, -1954, -1954, -1954,   861, -1954,   407,  -914, -1954, -1954,
   -1954,   388, -1262,  -600,  1021,  -892,  -368,  -396,  -443,   636,
     -46, -1954, -1954, -1954,  1367, -1954, -1954,   950, -1954, -1954,
     920, -1954,  1190, -1882,   850, -1954, -1954, -1954,  1370, -1954,
    1373, -1954,  1369, -1954,  1372,  -987, -1954, -1954, -1954,  -180,
      40, -1954, -1954, -1954,  -389, -1954,  -399,   631,  -309,   630,
   -1954,   -55, -1954, -1954, -1954,  -360, -1954, -1954, -1954, -1794,
   -1954, -1954, -1954, -1954, -1954, -1408,  -559,    88, -1954,  -227,
   -1954,  1237,  1022, -1954, -1954,  1027, -1954, -1954, -1954, -1954,
    -330, -1954, -1954,   975, -1954, -1954,  1025, -1954,   172,  1036,
   -1954, -1954, -1954,   606, -1954, -1954, -1954,  -246, -1954, -1954,
     140, -1954,  -760,  -376,  -361, -1954, -1954, -1954, -1457, -1954,
   -1954, -1954,  -205, -1954, -1954,  -327, -1954,  -346, -1954,  -362,
   -1954,  -363, -1582, -1054,  -757, -1954,  -138,  -467,  -940, -1953,
   -1954, -1954, -1954,  -482, -1470,   365, -1954,  -734, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954,  -471, -1410,   608,
   -1954,   141, -1954,  1430, -1954,  1584, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1399,   649, -1954,  1332, -1954,
   -1954, -1954, -1954,  1712, -1954, -1954, -1954,   197,  1681, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
     571, -1954, -1954, -1954,   149, -1954, -1954, -1954, -1954,   -88,
   -1842, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954,   537,   335,  -499, -1286, -1200, -1321, -1421,
   -1412, -1411, -1954, -1402, -1382, -1287, -1954, -1954, -1954, -1954,
   -1954,   322, -1954, -1954, -1954, -1954, -1954,   363, -1369, -1364,
   -1954, -1954, -1954,   325, -1954, -1954,   366, -1954,   518, -1954,
   -1954, -1954, -1954,   332, -1954, -1954, -1954, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954, -1954,   145,
   -1954,   142,  -126, -1954, -1954, -1954, -1954, -1954, -1954, -1954,
     902, -1954, -1954, -1954,  -815, -1954,   132, -1954, -1954, -1954,
   -1954, -1954, -1954, -1954, -1954, -1954,   892, -1954, -1954, -1954,
     891, -1954, -1954, -1954, -1954,   889, -1954
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1183
static const yytype_int16 yytable[] =
{
     403,   714,   667,   817,   818,   819,   820,   809,   805,   693,
     415,   415,   682,   932,   964,  1445,  1372,   423,  1091,   705,
     632,   788,   577,   579,   632,  1078,  1244,   663,   584,   720,
     982,   723,  1666,  1277,   858,  1321,   726,   727,   728,  1591,
     732,  1820,   968,   556,   729,   998,   449,   731,  1571,   733,
    1223,  1367,  1853,  1328,  1823,  1800,  1693,  1802,  1700,   993,
     993,  1457,  1318,  1318,   780,  1797,  1576,   430,   468,  2116,
    1401,  2093,   471,  1175,   750,  1825,  1176,  1067,  1839,  1767,
     417,  1900,  1604,   800,   686,   736,   395,   956,  1768,  1769,
     451,   781,  1231,  2231,  -541,  1446,     2,     3,  1770,  1348,
    1715,   761,  2043,  1011,   891,   994,   994,   466,  2189,   841,
    1426,  1517,   844,  1885,   846,   777,  1801,  -561,  1771,   583,
     782,   847,   848,   849,   790,   395,   793,   852,   853,   854,
     855,  1773,   856,   857,  2428,   493,  1774,  1845,  1715,   812,
    1551,  1843,   656,   891,   657,   544,  1858,   583,  1845,  1846,
    1847,   827,  1244,   830,  -527,   395,  1744,  1218,    25,   892,
     836,  1725,   559,    29,  1478,  1466,   672,  2212,  1320,   570,
     583,  -563,   366,  -789,  -789,  1386,  2237,  1756,   398,  1766,
    1739,  1779,  1030,   975,   982,    47,    48,   977,  2430,   631,
     578,  2245,   585,   631,   984,  -137,   722,  1349,  1037,   583,
     583,  1188,  2190,   795,  1222,  1907,  1908,  1909,   958,  -582,
     683,  1762,  1754,  1772,  1764,  1780,  1777,  2431,  1783,  -527,
     414,  1281,   583,  1428,   684,  -561,  2294, -1107,   414,  2232,
    -591,   632,  1836,   414,  -141,  -541,  1426,  1716,  1149,    90,
     983,  1447,  -591,   985,  1518,     8,     4,  1519,   414,    95,
    1282,   414,  1727,   606,   967,  2049,  2050,   971,  2191,  -339,
    1232,  1837,   414,  1807,   -61,   414,   414,   414,  -527,   398,
    2429,  1848,  -563,  2238,   606,  1716,  2192,  2432, -1132,  1233,
     917,  1092,  1848,  2233,  2239,  -563,  -339,   414,  2193,   683,
    2194,  2195,  -339,  2196,  2234,   121,  2197,   414,  1755,  1486,
    1765,  2155,  1778,   684,  1784,  -582,  1027, -1054, -1143,  1658,
     414,  1022,   414,  2048,   658,   661,   414,   414,   957,   433,
     668,   669,   673,   669,  1058,   677,   679,  1901,  1173,   685,
   -1159,   689,   691,   691,   694,  1154,  -137,   697,  -591,  1183,
     701,  1604,   697,  2093,  1144,  1827,  1829,   712,   489,  1428,
     717,  2046,   697,     5,   697,  1767,  1205,  1079,   415,   697,
     697,   697,  1556,   738,  1768,  1769,  -561,   697, -1107,   730,
     697,   982,   697,   982,  1770,  -141,   687,  1552,   741,   742,
     982,  1322,   499,   414,   987,   753,   755,  2198,   500,   760,
    1143,   775,  1145,   632,  1771,  1254,   767,   632,   783,   771,
     631,  1152,  1597,  2044,   632,   -61,  1346,  1773,  1650,  1278,
    1151,   784,  1774,  -563,   791,  1131,  1485,   583,  1483, -1132,
     712,   801,   803,   803,  1418,   807,   784,   725,  2056,  1665,
    1477,   813,   815,   815,   815,   815,   815,  1283,   825,   713,
     541,   829,  1756,   831,   767,  1171,  -582,   834, -1054, -1143,
     837,  2430,   994,  -592,   842,  1766,  -585,  1610,  1612,  1614,
    2057,  1779,  1016,  2162,  2163,  -592,  1413,   583,  -585,  2344,
    2379, -1159,  1818,  1819,  -527,  1631,  1762,  1754,  1694,  -591,
    2431,   958,  -589,   859,   958,  1687,   860,   414,   542,  1772,
    1764,   867,   872,   878,  -589,  1780,  1777,  1352,   414,  2371,
    1783,  2345,  1353,  1049,  1074,   893,   414,  1960,   898,   899,
     900,   685,   799,  1275,  1426,   903,   906,   907,   543,  2160,
     912,   685,   685,   685,   685, -1162,   606,  1823,   920,   921,
    1720,   583,  -587,  2106,  2018,  1336,  1337,  1338,  1339,  1340,
     982,  1276,  2119,  1393,  -587,   888,   889,  2371,  1825,  2157,
     576,   414,  1567,  1427,   632,   552,  1050,   904,   901,  2145,
     583,  -592,   631,  1755,  -585,  -527,   631,   414,   913,   914,
     915,   916,   583,   631,  1808,   583,  1765,   958,   988,  -527,
     583,  -382,  1778,   557,  1051,  1084,  1784,   937,  1311,  1227,
    -589,   938,  1142,  1534,   701,  1000,   753,   807,   801,   689,
    1005,  1009,  1571,   831,  1007,  2410,  1228,  2042,   395,  1568,
    1039,   685,  1437,  1438,  1010,  1688,   396,  2417,  2176,   953,
    1576,   583,  1018,  1040,  1052,   560,  2254,  1428,  1355,   697,
     583,   583,  1029,   583,   685,  1053,   583,   978,  1185, -1096,
    -587,   979,  1191,  1047,    46,  1439,   561,  1197,  1394,  1167,
    1201,  1203,  1356,  2164,  2165,  2166,  1048,  1046,  1012,  1402,
     967,  1569,  1168,  1054,  -383,  1229, -1162,  1357, -1126,   981,
    1389,  1264,  1358,  1359,  1265,  1244,  1535,    74,  1230,  1360,
   -1106,  1031,  1068, -1131,  1073,  1328,  2244,  1075, -1053,  1589,
    1234,  1787,  1788,  1789,   562,  1793,  1794,  1091,  1091,  1086,
    1089,  1078,  -592,  1235,   993,  -585,  1590,  1561,  1562,  1118,
      96,  1279,  1119,  1280,  1610,  1612,  1614,   563,  1125,  1124,
    1126,  2054,  2055,   631,  1890,  1133,  2159,  1137,   569, -1142,
     685,  -589,   982,   982,   982,   982,   982,  2298, -1158, -1161,
     109, -1095,  1237,   658, -1125,   632,   632,   632,   632,   632,
     994,   572,  1465,  1544,  1089,  1238,  1055,   937,   564,   565,
     685,   938,  -382,  1250,  1609,  1611,  1613,  -383,   939,   940,
    1725,  1550,   586,   587,   956,   685,  1251,  1141,   685,   959,
   -1096,  -587,  1323,  1567,  1179,  1178,  1492,  1726,   573,   953,
    1329,  1477,  1495,  1477,   574,  1324,  1498,   575,  1500,  2286,
    1219,  1219,  1502,  1330,  1504,  2318,  2042,   588,  -230, -1126,
     994,   994,   994,  1361,  -387,  2314,  1224,  2054,  2055,   622,
    1378, -1106,  1170,   775, -1131,  1172,   962,   978,   580, -1053,
    2215,   979,  2330,  1379,   581,  1382,  1247,   829,   627,   628,
    1568,  2216,  2217,  1334,  1362,   980,    50,  2218,  1383,  2219,
     582,  1725,  1272,  2444,  2446,  1560,  1561,  1562,  2220,   981,
    2221,  1727,  2222,  2316,  1728,  1538,  2450,  1563,  1726,   637,
   -1142,  -385,  2313,  1410,  1284,   566,  1564,  1287,  1748, -1158,
   -1161,  1249, -1095,   962,  2252, -1125,  1411,  1810,  1363,   635,
    1432,   908,  1569,   643,   395,  1811,  1273,    25,  1449,  1565,
    1646,   909,    29,  1433,  1566,  2034,  2035,  2036,  2037,  2038,
    1651,  1450,  1652,  1452,   631,   631,   631,   631,   631,  2071,
    1704,   645,   988,   988,    47,    48,  1453,   978,  1748,   646,
    1639,   979,  1567,  1318,  1318,  1318,  1318,  1318,   627,   628,
    2378,  2030,  1727,  1206,  1207,  1728,   118,   647,  2377,   775,
    1729,  1597,  1455,   122,   648,  1599,  1600,   658,  1730,   981,
    1366,  1602,  2171,  1370,   649,  1456,  1009,  2072,  1469,   673,
    1520,  1935,   775,  2077,   650,  1631,  1208,  1477,    90,  1463,
    1493,  1470,   694,  1521,  2223,  1725,  1496,  2224,    95,  1568,
    1499,  1536,  1501,  1499,  1499,   651,  1503,   978,  1505,   652,
    1619,   979,  1726,  1617,  1537,  1242,  1647,  1403,   627,   628,
    1414,  1039,   717,  1627,   655,   980,  1618,  1867,  1621,  1323,
    1244,  1873,  1611,  1613,  1623,  1629,  1386,  1638,   742,   981,
     664,  1633,  1626,  1649,   121,  1725,  1659,  1429,  1630,   665,
    1711,  1569,  1242,   755,  1634,  1382,  -384,  1242,  1242,  1660,
     666,  1130,  1726,  1712,  1681,  1714,   680,   958,  1883,  1749,
    1904,  1910,  -849,   688,  1997,  1083,  1998,   994,   994,   994,
     700,  1997,  2225,  1998,  1432,  1999,  1727,  2000,   150,  1728,
    1451,   703,  1999,  1750,  2000,   653,   654,  1911,  1943,  1643,
    1469,  1645,  1947,  1751,  1738,  1972,   706,  1743,  1752,  1668,
    1763,  1944,  1776,  1945,  1782,  1948,  1786,   715,  1973,  1749,
    1209,  1210,  1877,   721,  1211,  1212,   638,   734,   642,   644,
    1547,  1548,  1992,  1514,  1481,  2011,  1727,   739,  1711,  1728,
    2226,  2227,  2228,  1750,  1729,  1993,  1996,  1469,  2012,   749,
     978,  2013,  1730,  1751,   979,   752,  1719,  1711,  1752,  2171,
    2014,   627,   628,  1874,  1875,  1876,  1341,  2031,   980,  1870,
    2015,  1704,   758,  2090,   978,  2051,  1806,  1512,   979,   759,
    2032,   414,   981,  -585,  1919,   627,   628,  1628,  2052,   867,
    1459,   762,   980,  1041,   872,  1042,  1862,   878,   596,  1530,
    1531,  1532,   597,   598,   599,   600,   981,  1539,   893,   765,
    2001,  2002,  2281,  2003,  2004,   601,  2082,  2001,  2002,  1514,
    2003,  2004,   602,   770,   603,  1990,  1991,  1514,   766,  2083,
    1514,  1549,  2087,  2148,  2185,  1865,  1961,   685,  1963,  1964,
    2088,  1284,  1167,  2089,  2005,  1469,  2149,  2186,   774,  1556,
    1968,  2005,   604,  1514,  2257,  2208,  2290,  2051,  2210,  1881,
    1975,  1685,  1977,   929,  2308,  1242,  2246,  2258,  2062,  2291,
    2300,  1887,  1469,   772,  2260,  1889,   982,  2309,  2323,  2328,
     605,  1432,  1514,  1903,  1557,  2326,  2006,  1469,  1711,  2011,
     988,   778,  2329,  2006,  2348,  2349,   890,  2011,  2389,  2007,
    2351,  2353,  2383,   779,  1325,  2391,  2007,   806,  1432,   596,
    2384,  2390,  1615,   597,   598,   599,   600,   414,  2392,  1331,
     814,  2394,   839,  1332,   596,  1469,   601,  1167,   597,   598,
     599,   600,  1242,   602,  2413,   603,  2433,   606,  2395,  1593,
    2396,   601,   902,  2054,  2055,  2409,  1966,  2414,   602,  2434,
     603,  1969,  2449,  1828,  1830,  1641,  1641,   610,  1641,   840,
     787,   627,   628,   604,  1979,   843,   697,   845,  1068, -1182,
    1068,   864,   601,  1653,  1189,  1190,   865,  1193,   604,   632,
     866,   603,   594,   595,  1342,  1343,  1981,  2439,  2440,   607,
     887,   605,  1983,  1678,  2398,   958,  1985,  2360,  2361,   905,
     640,  1199,  1200,   959,  1676,   962,   605,   960,   961,   604,
     626,   627,   628,  1137,   965,   976,   986,  1006,   795,  1689,
    1015,  1017,   601,  1691,  1019,  1021,  1028,  1034,   414,   685,
    1038,   603,  1062,   398,  1059,  1064,  1724,   605,   956,   786,
    1080,  1081,  1717,   414,  1718,  1082,  1721,  1087,   606,   787,
     627,   628,  1219,  1219,  1219,  1095,  1219,  1219,  1123,   604,
    1795,   601,  1096,   606,  1150,   971,  1161,  1164,  1219,  1790,
     603,  1165,  1174,  1180,   629,  1177,  1188,  1194,  1217,  1236,
    1224,  2283,   775,  1798,  1242,   596,   583,   605,  1288,   597,
     598,   599,   600,  1291,   606,  1252,   938,  1313,   604,  1809,
     607,  1312,   601,  -342,   979,  1344,  1119,  1350,  1816,   602,
    1351,   603,  1373,  1371,  1381,   607,  1395,  1412,  1396,  1397,
    1398,  1399,  1400,  2073,   629,  1409,   605,  1415,  1421,  1838,
    -928,  1430,  1431,  1435,  1417,  1436,  1440,  1448,  1441,   604,
    1464,  1467,  1849,  1454,   606,  1468,   607,  1091,   631,   988,
    2317,  1477,  2062,   763,  2075,  1471,  1472,  1473,  1474,  1482,
    2114,  1653,  1484,   629,  1653,  1653,  1653,   605,  1506,  1491,
    1494,  1507,  1508,  2126,  1878,  1509,  1510,  1511,  2129,  1514,
    1515,  2130,   971,   606,  1516,  1522,  2118,  1523,   810,  1525,
    1526,  2137,  1527,  2138,  1541,  2139,   607,  2140,   822,  1255,
    2358,   908,  1546,  1584,   414,  1587,   697,  1592,  1219,  1219,
    1219,  1593,    13,    14,  1598,    15,    16,  1603,  1606,  1607,
      20,  1608,  2376,  1091,   606,  1616,  1912,   366,    23,   396,
    1622,  1639,  1427,    27,  1661,   607,    30,  1648,  1656,  1662,
    1663,  1664,  1256,  1075,    37,  1686,    38,  1695,    40,  1675,
    1713,  1804,  1803,  1813,  1815,   881,   882,   883,   884,   886,
    1805,  1841,  1844,  2211,  1857,  1859,  1831,  2376,  1832,  1862,
    1882,    59,  1833,  2153,  1258,  1834,   607,  1954,  1955,  1863,
    1884,  1835,    70,  2156,  1895,  1896,  1897,  1899,  1914,  1913,
    1921,  1920,  -494,  1937,  1941,  1938,  1940,  1942,  1259,  1952,
    1260,  1716,  1971,  1953,  1949,  1715,    85,   931,   933,   934,
    1958,   935,  1959,  1962,  1965,  1974,  1976,  1978,   936,    93,
    2033,  2065,  2040,  2276,  2277,  2016,  1987,  1988,  1989,  1994,
    1995,  2017,   810,  1261,  2019,  2020,  2025,   102,  1262,  -381,
    2041,  2053,  1263,   104,  2058,  2070,  1264,  2061,   969,  1265,
    2121,   108,   970,   110,  2064,   112,  2122,   114,   787,   627,
     628,  2066,  2067,  2068,   119,  1255,  2069,  2080,  2086,  2142,
     601,  1266,  2143,  2101,  1014,  2103,  2147,  2150,  -224,   603,
    2151,   130,   131,  2175,  2158,  1267,  2188,  2201,  2183,  1024,
    2202,  1268,  2203,  2204,  2207,  -840,  2209,  2230,  2236,   143,
    2205,  2247,  2045,  1849,  1849,  1849,   593,   604,  1256,  2248,
    2312,  2249,  2315,  2251,  1257,  1849,  2259,  1045,  2255,  2261,
     155,  2262,  2269,   156,  1061,  2271,  2272,   775,  2273,  2274,
    1065,  1066,  2275,   775,  1553,   605,  2278,  2279,  2285,   596,
    1258,  2289,   673,   597,   598,   599,   600,  2293,  2295,  2296,
      25,  2297,  2299,  2324,  2327,    29,   601,  2339,  2341,  2347,
    2085,  2350,  2359,   602,  1259,   603,  1260,  2356,  2352,  2364,
    2365,  2372,   629,  2373,  2169,  1122,  1443,    47,    48,   596,
    2310,  2099,  2382,   597,   598,   599,   600,  2385,  2393,  2407,
    2415,  2399,   606,   604,  1689,  2411,   601,  2435,  1878,  1261,
    2107,  2420,  2436,   602,  1262,   603,  2437,  2448,  1263,   971,
    2117,   554,  1264,   567,  2430,  1265,  2123,  1721,  1248,  1540,
    1253,   605,  2104,  2026,  1814,  2128,  1487,  2250,  1425,   910,
    1817,    90,  2027,   604,  2134,   922,   919,  1266,  1035,  1559,
    1285,    95,  1842,  2253,   607,  2161,  1286,  2047,  1181,  1182,
    2154,  1267,  1790,  2039,  1462,  1936,   937,  1268,   414,  2200,
     938,   605,  1219,  1702,  2102,  1684,  2214,   939,   940,  2124,
    1374,  2144,  1391,   941,   942,   943,   944,  1635,   606,   946,
     947,   948,   949,   950,   951,  1620,   952,   121,   953,   954,
    1906,  1420,   429,  1905,   776,   971,  2063,  2447,   414,  2076,
    1838,  1036,  1625,   589,  1140,   590,  1655,   591,   592,  1849,
    1380,  1849,  1849,  1849,  1849,  1849,  1849,  1868,   606,  1869,
     555,  1219,  1347,   999,  1406,  1434,  1169,  1480,  1001,  1003,
     607,   150,  1002,  1004,  2282,  1637,  1640,  2180,  2105,  2402,
    2302,  1365,  1148,  2181,  1364,  2386,  1292,  1293,  1294,  1295,
    1296,  1297,  1298,  1299,  1300,  1301,  1302,  1303,  1304,  1305,
    1306,  1307,  1308,  1309,  1310,  1419,  2074,  1375,  1680,  1384,
     607,   810,  2343,  2100,  2403,  2311,  1326,  2419,   803,  2213,
    1955,  2441,  2443,  1333,  2288,  1335,  1950,  1701,  2243,  1219,
     833,  1667,  1088,  1704,  2112,  1008,  2078,   676,   596,   724,
    1345,  1796,   597,   598,   599,   600,  2113,  2264,  1980,    13,
      14,  1967,    15,    16,  1984,   601,  1849,    20,  1982,  1970,
    2292,  1986,   602,  2131,   603,    23,   886,  2133,  2367,  1513,
      27,  1524,  1376,    30,  2141,  1528,  1529,     0,     0,     0,
       0,    37,     0,    38,     0,    40,     0,     0,  1045,     0,
       0,     0,   604,   815,   815,     0,   737,     0,     0,     0,
       0,     0,  2107,     0,     0,     0,  1041,     0,    59,     0,
       0,   596,     0,     0,     0,   597,   598,   599,   600,    70,
     605,     0,   937,     0,   737,     0,   938,     0,   601,     0,
       0,   737,     0,   939,   940,   602,     0,   603,     0,   796,
     942,     0,   944,    85,     0,   946,   947,   948,   949,   950,
       0,     0,     0,     0,   953,     0,    93,   414,  1219,  2304,
       0,     0,     0,     0,     0,   604,     0,     0,     0,  1089,
       0,  1089,  1444,     0,   102,  1219,     0,   606,     0,     0,
     104,  2334,     0,     0,     0,  2325,     0,     0,   108,     0,
     110,  1458,   112,   605,   114,  2336,  2335,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   886,  1479,   822,     0,   130,   131,
       0,     0,     0,     0,     0,     0,     0,  1798,  1798,   607,
     414,     0,     0,     0,     0,     0,   143,     0,     0,     0,
       0,     0,     0,     0,  1821,     0,     0,   918,     0,   596,
     606,     0,     0,   597,   598,   599,   600,   155,     0,     0,
     156,     0,     0,  2336,     0,  2387,   601,  2028,     0,     0,
       0,     0,   596,   602,     0,   603,   597,   598,   599,   600,
       0,   937,     0,     0,     0,   938,     0,     0,     0,   601,
       0,  1533,   939,   940,     0,     0,   602,     0,   603,   942,
       0, -1183,   607,   604, -1183, -1183, -1183, -1183, -1183,     0,
       0,   737,  2265,   953,     0,  2421,     0,   596,     0,     0,
    2422,   597,   598,   599,   600,  1555,   604,     0,     0,     0,
       0,   605,     0,  2422,   601,  2442,  2445,  1588,     0,     0,
       0,   602,     0,   603,     0,     0,     0,     0,  2445,     0,
       0,     0,     0,     0,   605,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1595,     0,     0,   414,     0,
       0,   604,     0,     0,     0,   821,     0,  1601,   596,     0,
       0,     0,   597,   598,   599,   600,     0,     0,   606,     0,
       0,   414,     0,     0,     0,   601,     0,     0,     0,   605,
       0,     0,   602,  1071,   603,     0,     0,     0,     0,     0,
       0,   606,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1090,     0,     0,     0,     0,  1624,  1024,     0,     0,
       0,     0,   604,     0,  1121,     0,   414,     0,     0,     0,
     607,  1636,  1127,  1128,     0,     0,  2115,  1134,  1644,     0,
       0,     0,     0,     0,     0,     0,   606,     0,   886,     0,
     605,     0,     0,   607,  1654,   368,  1657,     0,     0,     0,
       0,   374,     0,     0,     0,  1090,     0,     0,     0,   886,
       0,   381,     0,  1162,   383,     0,     0,   386,     0,     0,
       0,     0,  1672,     0,   392,     0,     0,   414,   399,     0,
       0,     0,   402,  1683,     0,     0,     0,     0,   607,     0,
       0,     0,  1184,     0,  1187,     0,  1697,   606,     0,     0,
     421,  1703,     0,  1709,   425,   426,     0,     0,     0,     0,
     431,   432,     0,   737,   737,     0,   437,   438,     0,   439,
     440,   441,   442,     0,   443,     0,     0,     0,     0,     0,
       0,     0,     0,   452,     0,     0,  1243,     0,   456,     0,
     458,     0,   624,     0,   461,     0,   625,     0,   465,   607,
     467,     0,   626,   627,   628,     0,     0,   473,     0,     0,
       0,   477,     0,     0,   601,   480,     0,   482,     0,     0,
       0,     0,     0,   603,   490,   492,     0,     0,   494,   495,
       0,   955,     0,     0,   501,  1822,   502,     0,     0,     0,
     506,     0,     0,     0,     0,  1443,     0,     0,   596,     0,
       0,   604,   597,   598,   599,   600,     0,     0,     0,  1317,
    1317,     0,     0,     0,     0,   601,     0,   533,     0,   535,
       0,     0,   602,     0,   603,     0,  1866,   810,  1326,   605,
       0,     0,     0,     0,   821,   737,   737,   596,     0,     0,
       0,   597,   598,   599,   600,     0,     0,     0,     0,     0,
       0,     0,   604,     0,   601,     0,     0,  1886,     0,     0,
    1888,   602,  1243,   603,     0,     0,   629,     0,  1892,     0,
       0,     0,     0,     0,  1023,     0,     0,   596,     0,     0,
     605,   597,   598,   599,   600,  1385,   606,     0,     0,  1443,
       0,   604,   596,     0,   601,     0,   597,   598,   599,   600,
    1915,   602,  1918,   603,     0,     0,     0,     0,     0,   601,
       0,     0,     0,     0,     0,     0,   602,   414,   603,   605,
       0,     0,     0,   737,     0,     0,     0,     0,     0,     0,
    1115,   604,     0,     0,   955,     0,     0,   606,   607,     0,
    1671,     0,     0,   596,     0,     0,   604,   597,   598,   599,
     600,     0,     0,     0,   971,     0,   414,     0,     0,   605,
     601,     0,     0,     0,     0,     0,     0,   602,     0,   603,
       0,     0,     0,     0,   605,  1696,   606,     0,   596,     0,
       0,   955,   597,   598,   599,   600,     0,     0,     0,   607,
       0,     0,     0,   955,     0,   601,   414,   604,     0,     0,
       0,     0,   602,     0,   603,     0,     0,     0,     0,     0,
       0,   414,     0,  1090,  1917,     0,   606,   596,     0,     0,
       0,   597,   598,   599,   600,   605,     0,     0,   607,     0,
     709,   606,   604,     0,   601,     0,     0,     0,     0,  2021,
    2022,   602,     0,   603,     0,     0,     0,  2029,     0,     0,
       0,     0,   955,   955,   955,   955,     0,   955,     0,     0,
     605,     0,   414,     0,     0,     0,     0,     0,   607,     0,
       0,   604,   596,     0,     0,     0,   597,   991,   599,   600,
       0,     0,   606,   607,     0,     0,     0,     0,  2060,   601,
       0,     0,     0,     0,  1595,     0,   602,   414,   603,   605,
       0,     0,   955,     0,   955,   955,   955,   955,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   606,     0,  2079,
       0,     0,     0,     0,     0,     0,   604,     0,  2084,  1558,
       0,     0,     0,   835,   607,     0,   414,     0,     0,     0,
       0,     0,     0,     0,     0,  2094,  2095,     0,     0,     0,
       0,     0,     0,     0,   605,     0,   606,     0,     0,     0,
       0,     0,     0,   955,     0,     0,     0,     0,     0,   607,
       0,     0,  1697,     0,     0,     0,     0,     0,     0,     0,
     822,     0,     0,     0,     0,   955,     0,     0,     0,  2125,
       0,   414,     0,   737,     0,   955,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2135,     0,  2136,   607,     0,
       0,   606,     0,     0,     0,     0,   955,     0,     0,     0,
       0,     0,   937,     0,  1673,     0,   938,   596,     0,     0,
       0,     0,   955,   939,   940,     0,   955,   955,  1674,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,     0,   953,   954,     0,     0,     0,  1071,
       0,  1071,     0,   607,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1090,  1090,     0,     0,     0,     0,     0,     0,     0,     0,
    1669,     0,     0,   955,  2168,     0,   737,     0,  1679,  2170,
       0,  1134,     0,     0,     0,     0,     0,     0,     0,     0,
    2179,  1892,     0,   796,     0,  2184,     0,  1090,  1090,     0,
       0,     0,     0,     0,     0,  2187,     0,     0,     0,     0,
    2199,     0,     0,     0,     0,     0,     0,     0,     0,   737,
       0,     0,     0,     0,     0,     0,  1745,     0,     0,     0,
       0,     0,   955,   955,     0,   737,   737,   737,     0,   737,
     737,     0,     0,   737,     0,     0,     0,     0,     0,     0,
       0,   737,     0,     0,  1090,  1090,  1090,     0,     0,   937,
       0,     0,  1555,   938,   596,  1243,     0,     0,     0,     0,
     939,   940,     0,     0,     0,     0,   941,   942,   943,   944,
     945,     0,   946,   947,   948,   949,   950,   951,     0,   952,
    1097,   953,   954,     0,  1098,   596,     0,  2266,     0,     0,
    1840,  1099,  1100,     0,     0,     0,     0,  1101,  1102,  1103,
    1104,     0,   886,  1105,  1106,  1107,  1108,  1109,  1110,  1111,
    1112,     0,  1113,  1114,     0,     0,     0,     0,     0,     0,
       0,     0,   737,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   955,   955,   955,   955,   955,   955,   955,
     955,   955,   955,   955,   955,   955,   955,   955,   955,   955,
     955,   955,     0,     0,     0,  2301,  2170,     0,     0,  2303,
       0,  2307,     0,     0,     0,     0,     0,   955,     0,     0,
       0,     0,     0,     0,   955,     0,   955,  2319,  2320,  2322,
       0,   737,   737,   737,     0,     0,   955,     0,     0,  2332,
       0,     0,     0,     0,  2333,     0,     0,     0,     0,     0,
       0,   937,     0,  1166,     0,   938,   596,  2266,     0,  1274,
       0,     0,   939,   940,     0,     0,     0,   955,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
    1090,   952,     0,   953,   954,     0,     0,     0,     0,  2366,
    2368,   937,     0,     0,  1239,   938,   596,     0,     0,     0,
       0,   822,   939,   940,  2380,     0,  2381,     0,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
       0,   952,     0,   953,   954,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   886,   955,     0,     0,  2368,     0,
       0,     0,  2404,     0,     0,     0,  2408,     0,  1709,   955,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1354,
    1709,  2418,  2404,   937,     0,     0,  1240,   938,   596,     0,
     955,     0,     0,     0,   939,   940,     0,     0,     0,     0,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,     0,   953,   954,     0,     0,     0,
    1317,  1317,  1317,  1317,  1317,     0,     0,     0,   937,     0,
       0,  1241,   938,   596,     0,     0,     0,     0,     0,   939,
     940,     0,     0,     0,   955,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,     0,
     953,   954,     0,   937,     0,     0,   955,   938,   596,     0,
    1243,     0,     0,     0,   939,   940,  1385,     0,     0,  1290,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,     0,   953,   954,     0,     0,   955,
       0,     0,     0,     0,     0,     0,   955,     0,     0,  2097,
       0,     0,   955,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     796,     0,     0,     0,     0,   955,     0,     0,     0,     0,
       0,  1090,     0,     0,     0,     0,     0,   955,     0,     0,
       0,     0,   937,     0,  1377,   955,   938,   596,     0,     0,
       0,  2132,     0,   939,   940,   955,     0,     0,   955,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,   955,   953,   954,     0,     0,     0,     0,
       0,     0,     0,     0,   955,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   737,  2146,     0,   955,     0,
       0,     0,     0,     0,   955,     0,     0,   937,     0,     0,
     955,   938,   596,     0,     0,     0,     0,     0,   939,   940,
    1545,  1840,     0,  1369,   941,   942,   943,   944,     0,     0,
     946,   947,   948,   949,   950,   951,     0,   952,     0,   953,
     954,   937,     0,  1392,     0,   938,   596,     0,     0,     0,
       0,  2174,   939,   940,   737,     0,  2177,     0,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
       0,   952,   937,   953,   954,     0,   938,   596,     0,     0,
       0,     0,     0,   939,   940,     0,     0,     0,  1404,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,     0,   953,   954,     0,     0,   937,     0,
       0,     0,   938,   596,     0,     0,     0,     0,     0,   939,
     940,   737,   737,   955,  1407,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,     0,
     953,   954,     0,     0,     0,   937,     0,     0,     0,   938,
     596,     0,     0,     0,     0,     0,   939,   940,     0,     0,
       0,  1408,   941,   942,   943,   944,     0,   955,   946,   947,
     948,   949,   950,   951,     0,   952,     0,   953,   954,   937,
       0,     0,     0,   938,  1090,     0,     0,   955,  1090,   955,
     939,   940,     0,   955,     0,     0,   941,   942,     0,   944,
       0,     0,   946,   947,   948,   949,   950,     0,     0,   952,
     937,   953,   954,     0,   938,   596,   955,     0,     0,   955,
       0,   939,   940,     0,     0,     0,  1442,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,  1115,
     952,     0,   953,   954,     0,     0,     0,     0,     0,     0,
    1090,   737,  1090,  1090,  1090,   937,     0,     0,     0,   938,
     596,     0,     0,     0,     0,     0,   939,   940,   737,     0,
       0,  1489,   941,   942,   943,   944,     0,     0,   946,   947,
     948,   949,   950,   951,     0,   952,     0,   953,   954,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1090,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   937,     0,     0,     0,
     938,   596,   955,   955,     0,  1090,  1090,   939,   940,  1090,
     955,     0,  1490,   941,   942,   943,   944,     0,     0,   946,
     947,   948,   949,   950,   951,     0,   952,     0,   953,   954,
       0,   937,     0,     0,     0,   938,     0,     0,     0,     0,
       0,   955,   939,   940,     0,     0,     0,     0,   941,   942,
    1090,   944,     0,     0,   946,   947,   948,   949,   950,     0,
     955,     0,   937,   953,     0,   955,   938,   596,     0,     0,
       0,     0,     0,   939,   940,   955,   955,     0,  1605,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,     0,   953,   954,     0,     0,     0,     0,
       0,     0,     0,   937,     0,     0,   955,   938,   596,     0,
       0,     0,     0,     0,   939,   940,   955,   955,     0,  1860,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,     0,   953,   954,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   955,
       0,   955,     0,     0,     0,     0,     0,     0,     0,   937,
     955,  1673,     0,   938,   596,   955,     0,     0,   955,     0,
     939,   940,     0,     0,     0,     0,   941,   942,   943,   944,
     955,     0,   946,   947,   948,   949,   950,   951,     0,   952,
     937,   953,   954,     0,   938,   596,     0,     0,     0,     0,
       0,   939,   940,     0,     0,     0,  1898,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,     0,
     952,     0,   953,   954,     0,   937,     0,  1916,     0,   938,
     596,     0,     0,     0,     0,     0,   939,   940,     0,     0,
       0,     0,   941,   942,   943,   944,     0,   955,   946,   947,
     948,   949,   950,   951,     0,   952,     0,   953,   954,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   955,     0,   955,     0,     0,     0,   955,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     955,   955,     0,   955,   937,     0,     0,     0,   938,   596,
       0,     0,     0,   955,   955,   939,   940,     0,     0,     0,
    1946,   941,   942,   943,   944,     0,     0,   946,   947,   948,
     949,   950,   951,     0,   952,     0,   953,   954,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   955,     0,   955,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   955,   955,     0,   370,   371,   372,   373,     0,   375,
       0,   376,     0,   378,   379,     0,   380,     0,     0,     0,
     382,     0,   384,   385,     0,   955,   387,   388,   389,   955,
     391,     0,   393,   394,     0,     0,   401,     0,     0,   955,
       0,   404,   405,   406,   407,   408,   409,   410,   411,     0,
     412,   413,     0,     0,   418,   419,   420,     0,   422,     0,
     424,     0,     0,   427,   428,     0,     0,     0,     0,     0,
       0,   435,   436,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   444,     0,   446,     0,   447,   448,     0,     0,
       0,   453,   454,   455,     0,     0,   457,     0,     0,   459,
     460,     0,   462,   463,   464,     0,     0,     0,     0,   469,
     470,     0,     0,   472,     0,   474,   475,   476,     0,   478,
     479,     0,     0,   481,     0,   483,   484,   485,   486,   487,
     488,     0,     0,     0,     0,     0,     0,   496,   497,   498,
       0,     0,     0,     0,   503,   504,   505,     0,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,     0,   534,     0,   536,     0,   537,
       0,   538,   539,   540,     0,     0,     0,     0,     0,   546,
     547,   548,   549,   550,   551,   937,     0,  2081,     0,   938,
     596,     0,     0,     0,     0,     0,   939,   940,     0,     0,
       9,     0,   941,   942,   943,   944,     0,    10,   946,   947,
     948,   949,   950,   951,     0,   952,     0,   953,   954,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   623,     0,     0,   636,     0,   639,    11,    12,    13,
      14,     0,    15,    16,    17,    18,    19,    20,     0,     0,
      21,    22,     0,     0,     0,    23,    24,    25,     0,    26,
      27,    28,    29,    30,    31,     0,    32,    33,    34,    35,
      36,    37,     0,    38,    39,    40,    41,    42,    43,     0,
       0,    44,    45,    46,    47,    48,     0,     0,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
       0,    71,     0,    72,    73,     0,    74,    75,    76,     0,
       0,    77,     0,     0,    78,    79,     0,    80,    81,    82,
      83,     0,    84,    85,    86,    87,    88,    89,    90,    91,
      92,     0,     0,     0,     0,     0,    93,    94,    95,    96,
       0,     0,     0,     0,    97,     0,     0,    98,    99,     0,
       0,   100,   101,     0,   102,     0,     0,     0,   103,     0,
     104,     0,   105,     0,     0,     0,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     0,   116,   117,   118,
       0,   119,     0,   120,   121,     0,   122,     0,   123,   124,
     125,   126,     0,     0,   127,   128,   129,     0,   130,   131,
     132,     0,   133,   134,   135,     0,   136,     0,   137,   138,
     139,   140,   141,     0,   142,     0,   143,   144,     0,     0,
     145,   146,   147,     0,     0,   148,   149,     0,   150,   151,
       0,   152,   153,     0,     0,     0,   154,   155,     0,     0,
     156,     0,     0,   157,     0,     0,     0,   158,   159,     0,
       0,   160,   161,   162,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,     0,   174,     0,     0,
     175,     0,     0,     0,   176,   177,   178,   179,   180,     0,
     181,   182,     0,     0,   183,   184,   185,   186,     0,     0,
       0,     0,   187,   188,   189,   190,   191,   192,     0,     0,
       0,     0,     0,     0,     0,     0,   193,   194,   195,   196,
       0,   197,   198,   199,   200,   201,   202,     0,     0,     0,
     203,   204,   937,     0,  2096,     0,   938,   596,     0,     0,
       0,     0,     0,   939,   940,     0,     0,     0,     0,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,     0,   953,   954,   937,   927,   928,     0,
     938,   596,     0,     0,     0,     0,     0,   939,   940,     0,
       0,     0,  2152,   941,   942,   943,   944,     0,     0,   946,
     947,   948,   949,   950,   951,     0,   952,   937,   953,   954,
       0,   938,   596,     0,     0,     0,     0,     0,   939,   940,
       0,     0,     0,  2167,   941,   942,   943,   944,     0,     0,
     946,   947,   948,   949,   950,   951,     0,   952,   937,   953,
     954,  2178,   938,   596,     0,     0,     0,     0,     0,   939,
     940,     0,     0,     0,     0,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,   937,
     953,   954,     0,   938,   596,     0,     0,     0,     0,     0,
     939,   940,     0,     0,     0,  2182,   941,   942,   943,   944,
       0,     0,   946,   947,   948,   949,   950,   951,     0,   952,
     937,   953,   954,     0,   938,   596,     0,     0,     0,     0,
       0,   939,   940,     0,     0,     0,  2241,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,     0,
     952,   937,   953,   954,     0,   938,   596,     0,     0,     0,
       0,     0,   939,   940,     0,     0,     0,  2242,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
       0,   952,   937,   953,   954,  2256,   938,   596,     0,     0,
       0,     0,     0,   939,   940,     0,     0,     0,     0,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,   937,   953,   954,     0,   938,   596,     0,
       0,     0,     0,     0,   939,   940,     0,     0,     0,  2263,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,   937,   953,   954,  2280,   938,   596,
       0,     0,     0,     0,     0,   939,   940,     0,     0,     0,
       0,   941,   942,   943,   944,     0,     0,   946,   947,   948,
     949,   950,   951,     0,   952,   937,   953,   954,  2340,   938,
     596,     0,     0,     0,     0,     0,   939,   940,     0,     0,
       0,     0,   941,   942,   943,   944,     0,     0,   946,   947,
     948,   949,   950,   951,     0,   952,   937,   953,   954,     0,
     938,   596,     0,     0,     0,     0,     0,   939,   940,     0,
       0,     0,  2342,   941,   942,   943,   944,     0,     0,   946,
     947,   948,   949,   950,   951,     0,   952,   937,   953,   954,
       0,   938,   596,     0,     0,     0,     0,     0,   939,   940,
       0,     0,     0,  2354,   941,   942,   943,   944,     0,     0,
     946,   947,   948,   949,   950,   951,     0,   952,   937,   953,
     954,  2355,   938,   596,     0,     0,     0,     0,     0,   939,
     940,     0,     0,     0,     0,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,   937,
     953,   954,  2357,   938,   596,     0,     0,     0,     0,     0,
     939,   940,     0,     0,     0,     0,   941,   942,   943,   944,
       0,     0,   946,   947,   948,   949,   950,   951,     0,   952,
     937,   953,   954,     0,   938,   596,     0,     0,     0,     0,
       0,   939,   940,     0,     0,     0,  2362,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,     0,
     952,   937,   953,   954,     0,   938,   596,     0,     0,     0,
       0,     0,   939,   940,     0,     0,     0,  2363,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
       0,   952,   937,   953,   954,  2397,   938,   596,     0,     0,
       0,     0,     0,   939,   940,     0,     0,     0,     0,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,     0,   953,   954,   937,     0,  2412,     0,
     938,   596,     0,     0,     0,     0,     0,   939,   940,     0,
       0,     0,     0,   941,   942,   943,   944,     0,     0,   946,
     947,   948,   949,   950,   951,     0,   952,   937,   953,   954,
       0,   938,   596,     0,     0,     0,     0,     0,   939,   940,
       0,     0,     0,     0,   941,   942,   943,   944,     0,     0,
     946,   947,   948,   949,   950,   951,     0,   952,     0,   953,
     954
};

static const yytype_int16 yycheck[] =
{
      50,   400,   371,   485,   486,   487,   488,   478,   475,   385,
      62,    63,   380,   598,   619,  1123,  1017,    69,   752,   394,
     253,   464,   228,   229,   257,   739,   887,   368,   234,   404,
     634,   406,  1431,   911,   533,   961,   411,   412,   413,  1311,
     423,  1554,   623,   206,   419,   645,    98,   422,  1282,   424,
     865,  1013,  1584,   967,  1560,  1525,  1464,  1527,  1468,   644,
     645,  1140,   960,   961,   459,  1522,  1282,    76,   118,  1951,
    1057,  1913,   122,   833,   435,  1560,   833,   732,  1571,  1500,
      63,     8,  1344,   472,   381,   426,     7,    15,  1500,  1500,
      99,   460,    41,    94,   116,   175,     0,     1,  1500,   991,
      71,   442,  1841,   662,     5,   644,   645,   116,    41,   505,
     169,   182,   511,  1626,   513,   456,  1526,     8,  1500,     8,
     461,   520,   521,   522,   465,     7,   467,   526,   527,   528,
     529,  1500,   531,   532,   182,   144,  1500,    15,    71,   480,
      15,  1580,     5,     5,     7,   197,  1585,     8,    15,    16,
      17,   492,  1013,   494,    15,     7,    37,    21,    63,    21,
     501,   191,   208,    68,  1165,  1152,     8,  2120,    64,   221,
       8,    15,    15,     7,     8,  1036,   191,  1498,    15,  1500,
     266,  1502,   685,   626,   788,    90,    91,   630,   128,   253,
       8,  2144,   238,   257,   637,   116,    15,     8,   701,     8,
       8,   287,   135,    15,    21,  1662,  1663,  1664,     3,    20,
      23,  1498,  1498,  1500,  1500,  1502,  1502,   157,  1504,    37,
     129,     8,     8,   282,    37,   116,    21,   116,   129,   230,
       8,   464,     8,   129,   116,   257,   169,   208,   797,   144,
     636,   321,    20,   639,   315,   116,   150,   318,   129,   154,
      37,   129,   282,   149,   622,  1846,  1847,   166,   191,   129,
     209,    37,   129,  1535,   116,   129,   129,   129,   129,    15,
     318,   149,   116,   288,   149,   208,   209,   217,   116,   228,
     577,   752,   149,   284,   299,   129,   129,   129,   221,    23,
     223,   224,   129,   226,   295,   200,   229,   129,  1498,  1177,
    1500,  2040,  1502,    37,  1504,   116,   681,   116,   116,  1417,
     129,   679,   129,  1845,   366,   367,   129,   129,   246,    64,
     372,   373,   374,   375,   713,   377,   378,   254,   831,   381,
     116,   383,   384,   385,   386,   806,   257,   389,   116,   842,
     392,  1603,   394,  2185,   787,  1561,  1562,   399,    15,   282,
     402,  1844,   404,   257,   406,  1776,   859,   740,   410,   411,
     412,   413,  1276,   427,  1776,  1776,   257,   419,   257,   421,
     422,   975,   424,   977,  1776,   257,   381,  1275,   430,   431,
     984,   962,    15,   129,    15,   437,   438,   320,     8,   441,
     786,   455,   788,   626,  1776,   898,   448,   630,   462,   451,
     464,   800,  1316,  1842,   637,   257,   991,  1776,  1409,   912,
     799,   463,  1776,   257,   466,   776,  1176,     8,  1175,   257,
     472,   473,   474,   475,  1079,   477,   478,   410,     5,  1430,
    1164,   481,   484,   485,   486,   487,   488,    15,   490,   399,
      15,   493,  1763,   495,   496,   828,   257,   499,   257,   257,
     502,   128,   991,     8,   506,  1776,     8,  1349,  1350,  1351,
      37,  1782,   668,  2054,  2055,    20,  1071,     8,    20,   148,
    2352,   257,  1551,  1552,    15,  1389,  1763,  1763,  1465,   257,
     157,     3,     8,   535,     3,    47,   536,   129,    15,  1776,
    1776,   541,   542,   543,    20,  1782,  1782,  1000,   129,  2341,
    1786,   180,  1005,     5,    26,   557,   129,    26,   560,   561,
     562,   563,   472,   908,   169,   565,   568,   569,    15,  2051,
     572,   573,   574,   575,   576,   116,   149,  2033,   580,   581,
     172,     8,     8,  1941,  1806,   978,   979,   980,   981,   982,
    1144,   909,  1952,  1046,    20,   554,   555,  2389,  2033,  2042,
       8,   129,    92,   208,   787,   257,    58,   566,   563,  2016,
       8,   116,   626,  1763,   116,    23,   630,   129,   573,   574,
     575,   576,     8,   637,  1536,     8,  1776,     3,   642,    37,
       8,     3,  1782,    15,    86,   748,  1786,     5,   956,   191,
     116,     9,    18,    15,   646,   647,   648,   649,   650,   651,
     652,     8,  1836,   655,   654,  2399,   208,  1841,     7,   149,
       8,   663,   147,   148,    21,   177,    15,  2411,  2075,    37,
    1836,     8,   672,    21,   126,     8,  2158,   282,    43,   681,
       8,     8,   684,     8,   686,   137,     8,     5,   844,   116,
     116,     9,   848,     8,    89,   180,     8,   853,  1047,     8,
     856,   857,    67,  2056,  2057,  2058,    21,   709,   663,  1058,
    1028,   201,    21,   165,     3,     8,   257,    82,   116,    37,
    1038,   191,    87,    88,   194,  1536,    15,   122,    21,    94,
     116,   686,   734,   116,   736,  1599,  2143,   739,   116,  1289,
       8,  1506,  1507,  1508,     8,  1510,  1511,  1431,  1432,   749,
     752,  1415,   257,    21,  1289,   257,  1291,    16,    17,   761,
     155,   917,   762,   919,  1606,  1607,  1608,     8,   770,   769,
     772,    16,    17,   787,  1638,   777,    21,   779,     8,   116,
     782,   257,  1336,  1337,  1338,  1339,  1340,  2250,   116,   116,
     185,   116,     8,   795,   116,   978,   979,   980,   981,   982,
    1289,     8,  1151,  1256,   806,    21,   258,     5,     7,     8,
     812,     9,     3,     8,  1349,  1350,  1351,     3,    16,    17,
     191,  1274,     7,   218,    15,   827,    21,   782,   830,    15,
     257,   257,     8,    92,   836,   835,  1185,   208,     8,    37,
       8,  1525,  1191,  1527,     8,    21,  1195,     8,  1197,  2209,
     864,   865,  1201,    21,  1203,  2275,  2040,   252,     7,   257,
    1349,  1350,  1351,   228,     3,  2272,   866,    16,    17,    15,
       8,   257,   827,   887,   257,   830,    15,     5,     8,   257,
       5,     9,  2289,    21,     8,     8,   888,   889,    16,    17,
     149,    16,    17,    21,   259,    23,    95,    22,    21,    24,
       8,   191,   904,  2435,  2436,    15,    16,    17,    33,    37,
      35,   282,    37,  2273,   285,  1248,  2448,    27,   208,    15,
     257,     3,  2271,     8,   926,   124,    36,   927,    84,   257,
     257,   890,   257,    15,  2156,   257,    21,    18,   303,   253,
       8,     5,   201,   257,     7,    26,   905,    63,     8,    59,
    1403,    15,    68,    21,    64,  1831,  1832,  1833,  1834,  1835,
    1410,    21,  1412,     8,   978,   979,   980,   981,   982,  1881,
       5,     8,   986,   987,    90,    91,    21,     5,    84,     8,
      15,     9,    92,  1831,  1832,  1833,  1834,  1835,    16,    17,
    2350,  1819,   282,   147,   148,   285,   195,     8,  2347,  1013,
     290,  1865,     8,   202,     8,  1323,  1325,  1009,   298,    37,
    1010,  1329,  2070,  1015,     8,    21,     8,  1881,     8,  1021,
       8,  1685,  1036,  1887,     8,  1889,   180,  1711,   144,    21,
    1186,    21,  1034,    21,   159,   191,  1192,   162,   154,   149,
    1196,     8,  1198,  1199,  1200,     8,  1202,     5,  1204,     8,
    1369,     9,   208,     8,    21,     8,  1405,  1059,    16,    17,
    1074,     8,  1064,  1382,     8,    23,    21,  1598,    21,     8,
    1881,  1606,  1607,  1608,    21,     8,  1887,  1395,  1080,    37,
      15,     8,    21,  1408,   200,   191,     8,  1087,    21,    15,
       8,   201,     8,  1095,    21,     8,     3,     8,     8,    21,
     149,     8,   208,    21,  1453,    21,    15,     3,    21,   265,
      21,    21,     8,    15,    22,   231,    24,  1606,  1607,  1608,
      15,    22,   247,    24,     8,    33,   282,    35,   244,   285,
    1130,   149,    33,   289,    35,     7,     8,    21,     8,  1398,
       8,  1400,     8,   299,  1493,     8,     7,  1496,   304,  1440,
    1499,    21,  1501,    21,  1503,    21,  1505,    15,    21,   265,
     314,   315,  1615,    15,   318,   319,   255,    15,   257,   258,
       7,     8,     8,     8,  1174,     8,   282,    15,     8,   285,
     305,   306,   307,   289,   290,    21,    21,     8,    21,     8,
       5,    21,   298,   299,     9,    15,  1487,     8,   304,  2257,
      21,    16,    17,  1606,  1607,  1608,    21,     8,    23,  1602,
      21,     5,    15,     7,     5,     8,  1534,  1217,     9,    15,
      21,   129,    37,     8,  1677,    16,    17,  1383,    21,  1229,
      21,    15,    23,     5,  1234,     7,    21,  1237,    10,  1239,
    1240,  1241,    14,    15,    16,    17,    37,  1249,  1250,    15,
     158,   159,  2203,   161,   162,    27,     8,   158,   159,     8,
     161,   162,    34,     8,    36,   316,   317,     8,    15,    21,
       8,  1273,    21,     8,     8,  1593,  1725,  1279,  1727,  1728,
      21,  1283,     8,    21,   192,     8,    21,    21,    15,  2153,
    1739,   192,    64,     8,     8,    21,     8,     8,    21,  1617,
    1749,  1457,  1751,   239,     8,     8,    21,    21,  1863,    21,
      21,  1629,     8,    37,  2178,  1633,  1870,    21,    21,     8,
      92,     8,     8,  1648,  1279,    21,   234,     8,     8,     8,
    1344,    15,    21,   234,    21,    21,   124,     8,     8,   247,
      21,    21,    21,    15,     5,     8,   247,    15,     8,    10,
      21,    21,  1354,    14,    15,    16,    17,   129,    21,     5,
      15,    21,    15,     9,    10,     8,    27,     8,    14,    15,
      16,    17,     8,    34,     8,    36,     8,   149,    21,     8,
      21,    27,     7,    16,    17,    21,  1735,    21,    34,    21,
      36,  1740,    21,  1561,  1562,  1397,  1398,   248,  1400,    15,
      15,    16,    17,    64,  1753,    15,  1408,    15,  1410,    15,
    1412,    15,    27,  1415,   846,   847,    15,   849,    64,  1602,
      15,    36,   244,   245,   986,   987,  1775,  2431,  2432,   201,
      15,    92,  1781,  1447,  2385,     3,  1785,  2327,  2328,   124,
       5,   854,   855,    15,  1446,    15,    92,   246,   246,    64,
      15,    16,    17,  1455,    21,    26,     8,     7,    15,  1461,
     240,    15,    27,  1463,    15,     8,    15,     8,   129,  1471,
      15,    36,   149,    15,   175,     8,  1490,    92,    15,     5,
       8,     8,  1482,   129,  1484,    15,  1488,     8,   149,    15,
      16,    17,  1506,  1507,  1508,     8,  1510,  1511,    15,    64,
    1514,    27,    26,   149,     7,   166,    62,    15,  1522,  1509,
      36,    15,     8,     8,   129,    21,   287,    15,     8,   326,
    1520,  2205,  1536,  1523,     8,    10,     8,    92,    15,    14,
      15,    16,    17,     8,   149,   213,     9,   129,    64,  1541,
     201,    64,    27,    21,     9,     8,  1546,     8,  1548,    34,
       8,    36,    67,    15,    37,   201,    15,     8,    15,    15,
      15,    15,    15,  1882,   129,    15,    92,     8,   129,  1571,
       7,    15,     7,    21,    26,    21,    21,    37,    18,    64,
       7,    15,  1584,    26,   149,     7,   201,  2271,  1602,  1603,
    2274,  2275,  2147,   444,  1885,     8,    15,    15,    26,     8,
    1949,  1603,     8,   129,  1606,  1607,  1608,    92,    15,    21,
      21,    15,    15,  1962,  1616,    15,    15,    15,  1967,     8,
      21,  1970,   166,   149,    21,    15,  1952,    15,   479,    15,
      15,  1980,    15,  1982,    15,  1984,   201,  1986,   489,    44,
    2324,     5,    15,    15,   129,    62,  1648,    21,  1662,  1663,
    1664,     8,    45,    46,     7,    48,    49,     8,     8,     8,
      53,     8,  2346,  2347,   149,   255,  1668,    15,    61,    15,
       7,    15,   208,    66,    16,   201,    69,   239,    21,    15,
      15,    15,    87,  1685,    77,     8,    79,     7,    81,    21,
      15,   315,   334,    15,     7,   546,   547,   548,   549,   550,
     335,     5,     8,  2120,    15,    15,   246,  2391,   246,    21,
       8,   104,   246,  2031,   119,   246,   201,  1719,  1720,    21,
       7,   246,   115,  2041,    21,    21,    21,     8,    21,    15,
       8,   173,    26,    15,     8,    15,   255,     7,   143,    15,
     145,   208,  1744,    15,    21,    71,   139,   598,   599,   600,
      18,   602,     8,    15,    15,    15,    15,    15,   609,   152,
       8,    26,     5,  2195,  2196,    15,    21,    21,    21,    21,
      21,    15,   623,   178,    21,    21,    21,   170,   183,    15,
      15,     7,   187,   176,     9,    15,   191,    20,     5,   194,
      18,   184,     9,   186,    21,   188,     8,   190,    15,    16,
      17,    21,    21,    21,   197,    44,    21,    21,    15,    15,
      27,   216,    15,    26,   665,    26,    21,     7,    15,    36,
      21,   214,   215,     8,    26,   230,    15,    21,   254,   680,
      21,   236,    15,     8,    21,     7,     7,    21,    37,   232,
     132,    21,  1844,  1845,  1846,  1847,   239,    64,    87,     7,
    2271,     7,  2273,    21,    93,  1857,  2175,   708,    21,   255,
     253,    15,    15,   256,   715,    15,    15,  1881,    15,    15,
     721,   722,    15,  1887,     5,    92,    15,    15,    15,    10,
     119,     7,  1884,    14,    15,    16,    17,    21,     8,     8,
      63,     7,    21,     8,     7,    68,    27,    21,    15,     7,
    1900,     7,    78,    34,   143,    36,   145,    21,    15,   333,
       8,     7,   129,     7,     5,   766,     7,    90,    91,    10,
    2269,  1921,    21,    14,    15,    16,    17,    15,    15,    21,
       8,    17,   149,    64,  1936,    17,    27,     7,  1940,   178,
    1942,    15,     7,    34,   183,    36,    15,     7,   187,   166,
    1952,   124,   191,   219,   128,   194,  1958,  1959,   889,  1250,
     897,    92,  1938,  1816,  1546,  1965,  1178,  2153,  1083,   571,
    1550,   144,  1817,    64,  1974,   582,   579,   216,   699,  1281,
     926,   154,  1580,  2158,   201,  2053,   926,  1844,   839,   840,
    2033,   230,  1992,  1836,  1147,  1686,     5,   236,   129,  2102,
       9,    92,  2016,  1471,  1936,  1455,  2122,    16,    17,  1959,
    1019,  2011,  1039,    22,    23,    24,    25,  1392,   149,    28,
      29,    30,    31,    32,    33,  1371,    35,   200,    37,    38,
    1661,  1081,    75,  1659,   455,   166,  1865,  2437,   129,  1887,
    2042,   700,  1378,   243,   780,   243,  1415,   243,   243,  2051,
    1028,  2053,  2054,  2055,  2056,  2057,  2058,  1599,   149,  1602,
     233,  2075,   991,   646,  1064,  1095,   826,  1167,   648,   650,
     201,   244,   649,   651,  2204,  1394,  1396,  2082,  1940,  2389,
    2257,  1009,   795,  2083,  1007,  2365,   937,   938,   939,   940,
     941,   942,   943,   944,   945,   946,   947,   948,   949,   950,
     951,   952,   953,   954,   955,  1080,  1884,  1021,  1452,  1034,
     201,   962,  2308,  1923,  2391,  2270,   967,  2413,  2120,  2121,
    2122,  2433,  2435,   974,  2212,   976,  1711,  1469,  2142,  2143,
     496,  1432,   750,     5,  1943,   655,  1889,   375,    10,   408,
     991,  1520,    14,    15,    16,    17,  1947,  2185,  1763,    45,
      46,  1738,    48,    49,  1782,    27,  2158,    53,  1776,  1743,
    2236,  1786,    34,  1971,    36,    61,  1017,  1972,    40,  1217,
      66,  1229,  1023,    69,  1992,  1234,  1237,    -1,    -1,    -1,
      -1,    77,    -1,    79,    -1,    81,    -1,    -1,  1039,    -1,
      -1,    -1,    64,  2195,  2196,    -1,   427,    -1,    -1,    -1,
      -1,    -1,  2204,    -1,    -1,    -1,     5,    -1,   104,    -1,
      -1,    10,    -1,    -1,    -1,    14,    15,    16,    17,   115,
      92,    -1,     5,    -1,   455,    -1,     9,    -1,    27,    -1,
      -1,   462,    -1,    16,    17,    34,    -1,    36,    -1,   470,
      23,    -1,    25,   139,    -1,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    37,    -1,   152,   129,  2272,  2261,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,  2271,
      -1,  2273,  1123,    -1,   170,  2289,    -1,   149,    -1,    -1,
     176,  2295,    -1,    -1,    -1,  2285,    -1,    -1,   184,    -1,
     186,  1142,   188,    92,   190,  2297,  2296,    -1,    -1,    -1,
      -1,   197,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1165,  1166,  1167,    -1,   214,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2327,  2328,   201,
     129,    -1,    -1,    -1,    -1,    -1,   232,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,   578,    -1,    10,
     149,    -1,    -1,    14,    15,    16,    17,   253,    -1,    -1,
     256,    -1,    -1,  2365,    -1,  2367,    27,     5,    -1,    -1,
      -1,    -1,    10,    34,    -1,    36,    14,    15,    16,    17,
      -1,     5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    27,
      -1,  1242,    16,    17,    -1,    -1,    34,    -1,    36,    23,
      -1,    25,   201,    64,    28,    29,    30,    31,    32,    -1,
      -1,   642,     5,    37,    -1,  2415,    -1,    10,    -1,    -1,
    2420,    14,    15,    16,    17,  1276,    64,    -1,    -1,    -1,
      -1,    92,    -1,  2433,    27,  2435,  2436,  1288,    -1,    -1,
      -1,    34,    -1,    36,    -1,    -1,    -1,    -1,  2448,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1316,    -1,    -1,   129,    -1,
      -1,    64,    -1,    -1,    -1,     7,    -1,  1328,    10,    -1,
      -1,    -1,    14,    15,    16,    17,    -1,    -1,   149,    -1,
      -1,   129,    -1,    -1,    -1,    27,    -1,    -1,    -1,    92,
      -1,    -1,    34,   734,    36,    -1,    -1,    -1,    -1,    -1,
      -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   752,    -1,    -1,    -1,    -1,  1377,  1378,    -1,    -1,
      -1,    -1,    64,    -1,   765,    -1,   129,    -1,    -1,    -1,
     201,  1392,   773,   774,    -1,    -1,    78,   778,  1399,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,  1409,    -1,
      92,    -1,    -1,   201,  1415,    12,  1417,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,   806,    -1,    -1,    -1,  1430,
      -1,    28,    -1,   814,    31,    -1,    -1,    34,    -1,    -1,
      -1,    -1,  1443,    -1,    41,    -1,    -1,   129,    45,    -1,
      -1,    -1,    49,  1454,    -1,    -1,    -1,    -1,   201,    -1,
      -1,    -1,   843,    -1,   845,    -1,  1467,   149,    -1,    -1,
      67,  1472,    -1,  1474,    71,    72,    -1,    -1,    -1,    -1,
      77,    78,    -1,   864,   865,    -1,    83,    84,    -1,    86,
      87,    88,    89,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,    -1,    -1,   887,    -1,   105,    -1,
     107,    -1,     5,    -1,   111,    -1,     9,    -1,   115,   201,
     117,    -1,    15,    16,    17,    -1,    -1,   124,    -1,    -1,
      -1,   128,    -1,    -1,    27,   132,    -1,   134,    -1,    -1,
      -1,    -1,    -1,    36,   141,   142,    -1,    -1,   145,   146,
      -1,   610,    -1,    -1,   151,  1556,   153,    -1,    -1,    -1,
     157,    -1,    -1,    -1,    -1,     7,    -1,    -1,    10,    -1,
      -1,    64,    14,    15,    16,    17,    -1,    -1,    -1,   960,
     961,    -1,    -1,    -1,    -1,    27,    -1,   184,    -1,   186,
      -1,    -1,    34,    -1,    36,    -1,  1597,  1598,  1599,    92,
      -1,    -1,    -1,    -1,     7,   986,   987,    10,    -1,    -1,
      -1,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    27,    -1,    -1,  1628,    -1,    -1,
    1631,    34,  1013,    36,    -1,    -1,   129,    -1,  1639,    -1,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    10,    -1,    -1,
      92,    14,    15,    16,    17,  1036,   149,    -1,    -1,     7,
      -1,    64,    10,    -1,    27,    -1,    14,    15,    16,    17,
    1671,    34,  1673,    36,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,   129,    36,    92,
      -1,    -1,    -1,  1074,    -1,    -1,    -1,    -1,    -1,    -1,
     759,    64,    -1,    -1,   763,    -1,    -1,   149,   201,    -1,
       7,    -1,    -1,    10,    -1,    -1,    64,    14,    15,    16,
      17,    -1,    -1,    -1,   166,    -1,   129,    -1,    -1,    92,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    36,
      -1,    -1,    -1,    -1,    92,     7,   149,    -1,    10,    -1,
      -1,   810,    14,    15,    16,    17,    -1,    -1,    -1,   201,
      -1,    -1,    -1,   822,    -1,    27,   129,    64,    -1,    -1,
      -1,    -1,    34,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,   129,    -1,  1164,     7,    -1,   149,    10,    -1,    -1,
      -1,    14,    15,    16,    17,    92,    -1,    -1,   201,    -1,
     397,   149,    64,    -1,    27,    -1,    -1,    -1,    -1,  1810,
    1811,    34,    -1,    36,    -1,    -1,    -1,  1818,    -1,    -1,
      -1,    -1,   881,   882,   883,   884,    -1,   886,    -1,    -1,
      92,    -1,   129,    -1,    -1,    -1,    -1,    -1,   201,    -1,
      -1,    64,    10,    -1,    -1,    -1,    14,    15,    16,    17,
      -1,    -1,   149,   201,    -1,    -1,    -1,    -1,  1859,    27,
      -1,    -1,    -1,    -1,  1865,    -1,    34,   129,    36,    92,
      -1,    -1,   931,    -1,   933,   934,   935,   936,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,  1890,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,  1899,  1280,
      -1,    -1,    -1,   500,   201,    -1,   129,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1916,  1917,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    -1,   149,    -1,    -1,    -1,
      -1,    -1,    -1,   992,    -1,    -1,    -1,    -1,    -1,   201,
      -1,    -1,  1943,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1951,    -1,    -1,    -1,    -1,  1014,    -1,    -1,    -1,  1960,
      -1,   129,    -1,  1344,    -1,  1024,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1976,    -1,  1978,   201,    -1,
      -1,   149,    -1,    -1,    -1,    -1,  1045,    -1,    -1,    -1,
      -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,  1061,    16,    17,    -1,  1065,  1066,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,  1410,
      -1,  1412,    -1,   201,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1431,  1432,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1441,    -1,    -1,  1122,  2065,    -1,  1447,    -1,  1449,  2070,
      -1,  1452,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2081,  2082,    -1,  1464,    -1,  2086,    -1,  1468,  1469,    -1,
      -1,    -1,    -1,    -1,    -1,  2096,    -1,    -1,    -1,    -1,
    2101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1490,
      -1,    -1,    -1,    -1,    -1,    -1,  1497,    -1,    -1,    -1,
      -1,    -1,  1181,  1182,    -1,  1506,  1507,  1508,    -1,  1510,
    1511,    -1,    -1,  1514,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1522,    -1,    -1,  1525,  1526,  1527,    -1,    -1,     5,
      -1,    -1,  2153,     9,    10,  1536,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,  2188,    -1,    -1,
    1571,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,  2203,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1603,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1292,  1293,  1294,  1295,  1296,  1297,  1298,
    1299,  1300,  1301,  1302,  1303,  1304,  1305,  1306,  1307,  1308,
    1309,  1310,    -1,    -1,    -1,  2256,  2257,    -1,    -1,  2260,
      -1,  2262,    -1,    -1,    -1,    -1,    -1,  1326,    -1,    -1,
      -1,    -1,    -1,    -1,  1333,    -1,  1335,  2278,  2279,  2280,
      -1,  1662,  1663,  1664,    -1,    -1,  1345,    -1,    -1,  2290,
      -1,    -1,    -1,    -1,  2295,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,     7,    -1,     9,    10,  2308,    -1,   906,
      -1,    -1,    16,    17,    -1,    -1,    -1,  1376,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
    1711,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,  2340,
    2341,     5,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,
      -1,  2352,    16,    17,  2355,    -1,  2357,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2385,  1444,    -1,    -1,  2389,    -1,
      -1,    -1,  2393,    -1,    -1,    -1,  2397,    -1,  2399,  1458,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1006,
    2411,  2412,  2413,     5,    -1,    -1,     8,     9,    10,    -1,
    1479,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
    1831,  1832,  1833,  1834,  1835,    -1,    -1,    -1,     5,    -1,
      -1,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,  1533,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,     5,    -1,    -1,  1555,     9,    10,    -1,
    1881,    -1,    -1,    -1,    16,    17,  1887,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,  1588,
      -1,    -1,    -1,    -1,    -1,    -1,  1595,    -1,    -1,  1920,
      -1,    -1,  1601,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1941,    -1,    -1,    -1,    -1,  1624,    -1,    -1,    -1,    -1,
      -1,  1952,    -1,    -1,    -1,    -1,    -1,  1636,    -1,    -1,
      -1,    -1,     5,    -1,     7,  1644,     9,    10,    -1,    -1,
      -1,  1972,    -1,    16,    17,  1654,    -1,    -1,  1657,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,  1672,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1683,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2016,  2017,    -1,  1697,    -1,
      -1,    -1,    -1,    -1,  1703,    -1,    -1,     5,    -1,    -1,
    1709,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
    1257,  2042,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,     5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,  2072,    16,    17,  2075,    -1,  2077,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,     5,    -1,
      -1,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,  2142,  2143,  1822,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,  1866,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,     5,
      -1,    -1,    -1,     9,  2205,    -1,    -1,  1886,  2209,  1888,
      16,    17,    -1,  1892,    -1,    -1,    22,    23,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    32,    -1,    -1,    35,
       5,    37,    38,    -1,     9,    10,  1915,    -1,    -1,  1918,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,  1938,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
    2271,  2272,  2273,  2274,  2275,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,  2289,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2324,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,
       9,    10,  2021,  2022,    -1,  2346,  2347,    16,    17,  2350,
    2029,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,     5,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,  2060,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
    2391,    25,    -1,    -1,    28,    29,    30,    31,    32,    -1,
    2079,    -1,     5,    37,    -1,  2084,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,  2094,  2095,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,  2125,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,  2135,  2136,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2168,
      -1,  2170,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
    2179,     7,    -1,     9,    10,  2184,    -1,    -1,  2187,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
    2199,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,     5,    -1,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,  2266,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2301,    -1,  2303,    -1,    -1,    -1,  2307,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2319,  2320,    -1,  2322,     5,    -1,    -1,    -1,     9,    10,
      -1,    -1,    -1,  2332,  2333,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2366,    -1,  2368,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2380,  2381,    -1,    14,    15,    16,    17,    -1,    19,
      -1,    21,    -1,    23,    24,    -1,    26,    -1,    -1,    -1,
      30,    -1,    32,    33,    -1,  2404,    36,    37,    38,  2408,
      40,    -1,    42,    43,    -1,    -1,    46,    -1,    -1,  2418,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      60,    61,    -1,    -1,    64,    65,    66,    -1,    68,    -1,
      70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    94,    -1,    96,    97,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,   106,    -1,    -1,   109,
     110,    -1,   112,   113,   114,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,   123,    -1,   125,   126,   127,    -1,   129,
     130,    -1,    -1,   133,    -1,   135,   136,   137,   138,   139,
     140,    -1,    -1,    -1,    -1,    -1,    -1,   147,   148,   149,
      -1,    -1,    -1,    -1,   154,   155,   156,    -1,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,    -1,   185,    -1,   187,    -1,   189,
      -1,   191,   192,   193,    -1,    -1,    -1,    -1,    -1,   199,
     200,   201,   202,   203,   204,     5,    -1,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
       6,    -1,    22,    23,    24,    25,    -1,    13,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   251,    -1,    -1,   254,    -1,   256,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    -1,    -1,
      56,    57,    -1,    -1,    -1,    61,    62,    63,    -1,    65,
      66,    67,    68,    69,    70,    -1,    72,    73,    74,    75,
      76,    77,    -1,    79,    80,    81,    82,    83,    84,    -1,
      -1,    87,    88,    89,    90,    91,    -1,    -1,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      -1,   117,    -1,   119,   120,    -1,   122,   123,   124,    -1,
      -1,   127,    -1,    -1,   130,   131,    -1,   133,   134,   135,
     136,    -1,   138,   139,   140,   141,   142,   143,   144,   145,
     146,    -1,    -1,    -1,    -1,    -1,   152,   153,   154,   155,
      -1,    -1,    -1,    -1,   160,    -1,    -1,   163,   164,    -1,
      -1,   167,   168,    -1,   170,    -1,    -1,    -1,   174,    -1,
     176,    -1,   178,    -1,    -1,    -1,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,    -1,   193,   194,   195,
      -1,   197,    -1,   199,   200,    -1,   202,    -1,   204,   205,
     206,   207,    -1,    -1,   210,   211,   212,    -1,   214,   215,
     216,    -1,   218,   219,   220,    -1,   222,    -1,   224,   225,
     226,   227,   228,    -1,   230,    -1,   232,   233,    -1,    -1,
     236,   237,   238,    -1,    -1,   241,   242,    -1,   244,   245,
      -1,   247,   248,    -1,    -1,    -1,   252,   253,    -1,    -1,
     256,    -1,    -1,   259,    -1,    -1,    -1,   263,   264,    -1,
      -1,   267,   268,   269,    -1,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,    -1,   283,    -1,    -1,
     286,    -1,    -1,    -1,   290,   291,   292,   293,   294,    -1,
     296,   297,    -1,    -1,   300,   301,   302,   303,    -1,    -1,
      -1,    -1,   308,   309,   310,   311,   312,   313,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   322,   323,   324,   325,
      -1,   327,   328,   329,   330,   331,   332,    -1,    -1,    -1,
     336,   337,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,     5,   587,   588,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,     5,    37,    38,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
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
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,     5,    37,    38,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
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
      33,    -1,    35,    -1,    37,    38,     5,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,     5,    37,    38,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   341,     0,     1,   150,   257,   342,   343,   116,     6,
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
     330,   331,   332,   336,   337,   344,   346,   349,   361,   362,
     366,   367,   368,   374,   375,   376,   377,   379,   380,   382,
     384,   385,   386,   387,   394,   395,   396,   397,   398,   399,
     403,   404,   405,   409,   410,   448,   450,   463,   506,   507,
     509,   510,   516,   517,   518,   519,   526,   527,   528,   529,
     531,   534,   538,   539,   540,   541,   542,   548,   549,   550,
     561,   562,   563,   565,   568,   571,   576,   577,   579,   581,
     583,   586,   587,   611,   612,   623,   624,   625,   626,   631,
     634,   637,   640,   641,   689,   690,   691,   692,   693,   694,
     695,   696,   702,   704,   706,   708,   710,   711,   712,   713,
     714,   717,   719,   720,   721,   724,   725,   729,   730,   732,
     733,   734,   735,   736,   737,   738,   741,   746,   751,   753,
     754,   755,   756,   758,   759,   760,   761,   762,   779,   782,
     783,   784,   785,   791,   794,   799,   800,   801,   804,   805,
     806,   807,   808,   809,   810,   811,   812,   813,   814,   815,
     816,   817,   818,   823,   824,   825,   826,   827,   837,   838,
     839,   840,   841,   842,   843,   844,    15,   473,   473,   535,
     535,   535,   535,   535,   473,   535,   535,   345,   535,   535,
     535,   473,   535,   473,   535,   535,   473,   535,   535,   535,
     472,   535,   473,   535,   535,     7,    15,   474,    15,   473,
     594,   535,   473,   358,   535,   535,   535,   535,   535,   535,
     535,   535,   535,   535,   129,   351,   515,   515,   535,   535,
     535,   473,   535,   351,   535,   473,   473,   535,   535,   472,
     345,   473,   473,    64,   357,   535,   535,   473,   473,   473,
     473,   473,   473,   473,   535,   412,   535,   535,   535,   351,
     449,   345,   473,   535,   535,   535,   473,   535,   473,   535,
     535,   473,   535,   535,   535,   473,   345,   473,   358,   535,
     535,   358,   535,   473,   535,   535,   535,   473,   535,   535,
     473,   535,   473,   535,   535,   535,   535,   535,   535,    15,
     473,   572,   473,   345,   473,   473,   535,   535,   535,    15,
       8,   473,   473,   535,   535,   535,   473,   535,   535,   535,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   535,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   535,
     535,   535,   535,   473,   535,   473,   535,   535,   535,   535,
     535,    15,    15,    15,   351,   856,   535,   535,   535,   535,
     535,   535,   257,   560,   124,   233,   382,    15,   354,   560,
       8,     8,     8,     8,     7,     8,   124,   346,   369,     8,
     351,   383,     8,     8,     8,     8,     8,   530,     8,   530,
       8,     8,     8,     8,   530,   560,     7,   218,   252,   507,
     509,   518,   519,   239,   527,   527,    10,    14,    15,    16,
      17,    27,    34,    36,    64,    92,   149,   201,   351,   363,
     479,   480,   482,   483,   484,   485,   491,   492,   493,   494,
     495,   498,    15,   535,     5,     9,    15,    16,    17,   129,
     481,   483,   491,   544,   558,   559,   535,    15,   544,   535,
       5,   543,   544,   559,   544,     8,     8,     8,     8,     8,
       8,     8,     8,     7,     8,     8,     5,     7,   351,   621,
     622,   351,   614,   474,    15,    15,   149,   462,   351,   351,
     722,   723,     8,   351,   638,   639,   723,   351,   353,   351,
      15,   511,   556,    23,    37,   351,   401,   402,    15,   351,
     584,   351,   653,   653,   351,   635,   636,   351,   514,   411,
      15,   351,   564,   149,   728,   514,     7,   457,   458,   473,
     595,   596,   351,   590,   596,    15,   536,   351,   566,   567,
     514,    15,    15,   514,   728,   515,   514,   514,   514,   514,
     351,   514,   354,   514,    15,   406,   474,   482,   483,    15,
     348,   351,   351,   632,   633,   464,   465,   466,   467,     8,
     654,   718,    15,   351,   578,   351,   569,   570,    15,    15,
     351,   474,    15,   479,   731,    15,    15,   351,   705,   707,
       8,   351,    37,   400,    15,   483,   484,   474,    15,    15,
     536,   462,   474,   483,   351,   697,     5,    15,   558,   559,
     474,   351,   352,   474,   557,    15,   482,   615,   616,   590,
     594,   351,   582,   351,   677,   677,    15,   351,   580,   697,
     479,   490,   474,   358,    15,   351,   683,   683,   683,   683,
     683,     7,   479,   573,   574,   351,   575,   474,   347,   351,
     474,   351,   703,   705,   351,   473,   474,   351,   451,    15,
      15,   557,   351,    15,   596,    15,   596,   596,   596,   596,
     765,   821,   596,   596,   596,   596,   596,   596,   765,   351,
     358,   828,   829,   830,    15,    15,    15,   358,   845,   846,
     847,   848,   358,   849,   850,   851,   852,   853,   358,   854,
     855,   479,   479,   479,   479,   478,   479,    15,   345,   345,
     124,     5,    21,   351,   355,   356,   350,   358,   351,   351,
     351,   402,     7,   358,   345,   124,   351,   351,     5,    15,
     389,   390,   351,   402,   402,   402,   402,   401,   482,   400,
     351,   351,   406,   413,   414,   416,   417,   535,   535,   239,
     392,   479,   480,   479,   479,   479,   479,     5,     9,    16,
      17,    22,    23,    24,    25,    26,    28,    29,    30,    31,
      32,    33,    35,    37,    38,   363,    15,   246,     3,    15,
     246,   246,    15,   488,   489,    21,   532,   556,   490,     5,
       9,   166,   545,   546,   547,   558,    26,   558,     5,     9,
      23,    37,   481,   557,   558,   557,     8,    15,   483,   551,
     552,    15,   479,   480,   495,   553,   554,   555,   553,   564,
     351,   578,   580,   582,   584,   351,     7,   358,   703,     8,
      21,   616,   402,   504,   479,   240,   530,    15,   358,    15,
     456,     8,   556,     7,   479,   512,   513,   514,    15,   351,
     456,   402,   461,   462,     8,   413,   504,   456,    15,     8,
      21,     5,     7,   459,   460,   479,   351,     8,    21,     5,
      58,    86,   126,   137,   165,   258,   597,   593,   594,   175,
     585,   479,   149,   525,     8,   479,   479,   350,   351,   407,
     408,   482,   487,   351,    26,   351,   520,   521,   523,   354,
       8,     8,    15,   231,   382,   468,   358,     8,   718,   351,
     482,   687,   697,   715,   716,     8,    26,     5,     9,    16,
      17,    22,    23,    24,    25,    28,    29,    30,    31,    32,
      33,    34,    35,    37,    38,   363,   364,   365,   351,   358,
     372,   482,   479,    15,   358,   351,   351,   482,   482,   505,
       8,   654,   709,   351,   482,   642,   643,   351,   446,   447,
     525,   402,    18,   557,   558,   557,   378,   381,   621,   616,
       7,   594,   596,   687,   697,   698,   699,   401,   402,   440,
     441,    62,   482,   742,    15,    15,     7,     8,    21,   572,
     402,   354,   402,   456,     8,   652,   674,    21,   358,   351,
       8,   479,   479,   456,   482,   530,   786,   482,   287,   798,
     798,   530,   795,   798,    15,   530,   763,   530,   802,   763,
     763,   530,   780,   530,   792,   456,   147,   148,   180,   314,
     315,   318,   319,   359,   831,   832,   833,     8,    21,   483,
     658,   834,    21,   834,   358,   739,   740,   191,   208,     8,
      21,    41,   209,   228,     8,    21,   326,     8,    21,     8,
       8,     8,     8,   482,   485,   486,   757,   351,   347,   345,
       8,    21,   213,   359,   456,    44,    87,    93,   119,   143,
     145,   178,   183,   187,   191,   194,   216,   230,   236,   370,
     371,   373,   351,   345,   473,   536,   556,   383,   456,   530,
     530,     8,    37,    15,   351,   419,   424,   358,    15,   499,
      21,     8,   479,   479,   479,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   479,   479,   479,   479,
     479,   556,    64,   129,   475,   477,   556,   482,   493,   496,
      64,   496,   490,     8,    21,     5,   479,   533,   547,     8,
      21,     5,     9,   479,    21,   479,   558,   558,   558,   558,
     558,    21,   551,   551,     8,   479,   480,   554,   555,     8,
       8,     8,   456,   456,   473,    43,    67,    82,    87,    88,
      94,   228,   259,   303,   625,   622,   358,   486,   502,    21,
     351,    15,   478,    67,   457,   639,   479,     7,     8,    21,
     532,    37,     8,    21,   636,   482,   485,   501,   503,   556,
     726,   459,     7,   456,   596,    15,    15,    15,    15,    15,
      15,   585,   596,   351,    21,   537,   567,    21,    21,    15,
       8,    21,     8,   489,   483,     8,   522,    26,   350,   633,
     465,   129,   469,   470,   471,   387,   169,   208,   282,   358,
      15,     7,     8,    21,   570,    21,    21,   147,   148,   180,
      21,    18,    21,     7,   479,   497,   175,   321,    37,     8,
      21,   358,     8,    21,    26,     8,    21,   537,   479,    21,
     442,   443,   442,    21,     7,   596,   585,    15,     7,     8,
      21,     8,    15,    15,    26,   684,   685,   687,   478,   479,
     574,   358,     8,   674,     8,   652,   383,   373,   360,    21,
      21,    21,   596,   530,    21,   596,   530,   822,   596,   530,
     596,   530,   596,   530,   596,   530,    15,    15,    15,    15,
      15,    15,   358,   830,     8,    21,    21,   182,   315,   318,
       8,    21,    15,    15,   846,    15,    15,    15,   850,   855,
     358,   358,   358,   479,    15,    15,     8,    21,   354,   351,
     356,    15,   388,   389,   456,   473,    15,     7,     8,   351,
     456,    15,   493,     5,   391,   479,   547,   402,   482,   416,
      15,    16,    17,    27,    36,    59,    64,    92,   149,   201,
     415,   417,   427,   428,   429,   430,   431,   432,   433,   434,
     419,   424,   425,   426,    15,   420,   421,    62,   479,   553,
     480,   475,    21,     8,   476,   479,   497,   547,     7,   556,
     462,   479,   556,     8,   552,    21,     8,     8,     8,   480,
     555,   480,   555,   480,   555,   351,   255,     8,    21,   462,
     461,    21,     7,    21,   479,   512,    21,   462,   530,     8,
      21,   547,   727,     8,    21,   460,   479,   597,   556,    15,
     599,   351,   598,   598,   479,   598,   456,   596,   239,   514,
     478,   408,   408,   351,   479,   521,    21,   479,   497,     8,
      21,    16,    15,    15,    15,   478,   715,   716,   474,   482,
     747,     7,   479,     7,    21,    21,   351,   592,   483,   482,
     643,   596,   644,   479,   447,   530,     8,    47,   177,   351,
     445,   358,   613,   615,   585,     7,     7,   479,   700,   701,
     698,   699,   441,   479,     5,   599,   743,   744,   750,   479,
     609,     8,    21,    15,    21,    71,   208,   358,   358,   474,
     172,   351,   454,   455,   483,   191,   208,   282,   285,   290,
     298,   766,   767,   768,   775,   787,   788,   789,   596,   266,
     796,   797,   798,   596,    37,   482,   819,   820,    84,   265,
     289,   299,   304,   764,   766,   767,   768,   769,   770,   771,
     773,   774,   775,   596,   766,   767,   768,   769,   770,   771,
     773,   774,   775,   788,   789,   803,   596,   766,   767,   768,
     775,   781,   596,   766,   767,   793,   596,   834,   834,   834,
     358,   835,   836,   834,   834,   483,   740,   658,   358,   678,
     684,   698,   684,   334,   315,   335,   556,   475,   486,   351,
      18,    26,   393,    15,   372,     7,   358,   388,   537,   537,
     392,     5,   479,   430,   431,   432,   435,   431,   433,   431,
     433,   246,   246,   246,   246,   246,     8,    37,   351,   418,
     482,     5,   420,   421,     8,    15,    16,    17,   149,   351,
     418,   422,   423,   436,   437,   438,   439,    15,   421,    15,
      21,   500,    21,    21,   489,   556,   479,   490,   533,   546,
     558,   523,   524,   480,   524,   524,   524,   456,   351,   617,
     620,   556,     8,    21,     7,   392,   479,   556,   479,   556,
     547,   610,   479,   600,   601,    21,    21,    21,    21,     8,
       8,   254,   508,   514,    21,   470,   471,   658,   658,   658,
      21,    21,   351,    15,    21,   479,     7,     7,   479,   456,
     173,     8,   648,   649,   650,   651,   652,   654,   655,   656,
     659,   660,   661,   674,   682,   523,   443,    15,    15,   444,
     255,     8,     7,     8,    21,    21,    21,     8,    21,    21,
     685,   686,    15,    15,   351,   351,   452,   453,    18,     8,
      26,   765,    15,   765,   765,    15,   596,   787,   765,   596,
     796,   351,     8,    21,    15,   765,    15,   765,    15,   596,
     764,   596,   803,   596,   781,   596,   793,    21,    21,    21,
     316,   317,     8,    21,    21,    21,    21,    22,    24,    33,
      35,   158,   159,   161,   162,   192,   234,   247,   679,   680,
     681,     8,    21,    21,    21,    21,    15,    15,   475,    21,
      21,   479,   479,   627,   628,    21,   371,   393,     5,   479,
     383,     8,    21,     8,   496,   496,   496,   496,   496,   427,
       5,    15,   417,   428,   421,   351,   418,   426,   436,   437,
     437,     8,    21,     7,    16,    17,     5,    37,     9,   436,
     479,    20,   489,   476,    21,    26,    21,    21,    21,    21,
      15,   486,   547,   462,   638,   474,   501,   547,   727,   479,
      21,     7,     8,    21,   479,   358,    15,    21,    21,    21,
       7,   748,   749,   750,   479,   479,     7,   482,   645,   358,
     650,    26,   445,    26,   364,   617,   615,   351,   588,   589,
     590,   591,   701,   744,   596,    78,   573,   351,   653,   698,
     675,    18,     8,   351,   455,   479,   596,   776,   358,   596,
     596,   821,   482,   819,   358,   479,   479,   596,   596,   596,
     596,   836,    15,    15,   358,   658,   482,    21,     8,    21,
       7,    21,    21,   556,   435,   428,   556,   418,    26,    21,
     436,   423,   437,   437,   438,   438,   438,    21,   479,     5,
     479,   497,   618,   619,   482,     8,   658,   482,     8,   479,
     601,   358,    21,   254,   479,     8,    21,   479,    15,    41,
     135,   191,   209,   221,   223,   224,   226,   229,   320,   479,
     444,    21,    21,    15,     8,   132,   745,    21,    21,     7,
      21,   677,   679,   351,   453,     5,    16,    17,    22,    24,
      33,    35,    37,   159,   162,   247,   305,   306,   307,   778,
      21,    94,   230,   284,   295,   790,    37,   191,   288,   299,
     772,    21,    21,   483,   658,   679,    21,    21,     7,     7,
     391,    21,   475,   422,   436,    21,     8,     8,    21,   462,
     547,   255,    15,    21,   749,     5,   479,   646,   647,    15,
     662,    15,    15,    15,    15,    15,   683,   683,    15,    15,
       8,   478,   589,   687,   688,    15,   698,   676,   676,     7,
       8,    21,   822,    21,    21,     8,     8,     7,   392,    21,
      21,   479,   619,   479,   351,   602,   603,   479,     8,    21,
     596,   662,   697,   715,   658,   697,   698,   687,   684,   479,
     479,   657,   479,    21,     8,   358,    21,     7,     8,    21,
     658,   777,   479,   479,   483,   358,   351,   629,   630,    21,
       8,    15,    21,   647,   148,   180,   663,     7,    21,    21,
       7,    21,    15,    21,    21,     8,    21,     8,   687,    78,
     678,   678,    21,    21,   333,     8,   479,    40,   479,   604,
     605,   750,     7,     7,   664,   665,   687,   715,   698,   573,
     479,   479,    21,    21,    21,    15,   630,   351,   606,     8,
      21,     8,    21,    15,    21,    21,    21,     8,   478,    17,
     607,   608,   605,   665,   479,   666,   667,    21,   479,    21,
     609,    17,     7,     8,    21,     8,   752,   609,   479,   667,
      15,   358,   358,   668,   669,   670,   671,   672,   182,   318,
     128,   157,   217,     8,    21,     7,     7,    15,   673,   673,
     673,   669,   358,   671,   672,   358,   672,   477,     7,    21,
     672
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
#line 767 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 769 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 773 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 775 "gram1.y"
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
#line 789 "gram1.y"
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
#line 820 "gram1.y"
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
#line 829 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 835 "gram1.y"
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
#line 855 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 864 "gram1.y"
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
#line 880 "gram1.y"
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
#line 892 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 902 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 909 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 915 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 920 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 925 "gram1.y"
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
#line 949 "gram1.y"
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
#line 975 "gram1.y"
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
#line 990 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 992 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 994 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 998 "gram1.y"
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
#line 1015 "gram1.y"
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
#line 1029 "gram1.y"
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
#line 1053 "gram1.y"
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
#line 1069 "gram1.y"
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
#line 1083 "gram1.y"
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
#line 1101 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1103 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1110 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1113 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1115 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1121 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1123 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1130 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1132 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1134 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1139 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1143 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1147 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1153 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1162 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1166 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1171 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1192 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1197 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1202 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1209 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1225 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1229 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1237 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1245 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1254 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1262 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1266 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1268 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1272 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1274 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1276 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1278 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1280 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1282 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1284 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1286 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1288 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1290 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1292 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1294 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1296 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1298 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1300 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1302 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1304 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1306 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1311 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1320 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1330 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1338 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1348 "gram1.y"
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
#line 1369 "gram1.y"
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
#line 1388 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1390 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1392 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1396 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1398 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1402 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1406 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1408 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1412 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1418 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1422 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1424 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1428 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1432 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1436 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1440 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1444 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1450 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1454 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1458 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1464 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1469 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1476 "gram1.y"
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
#line 1487 "gram1.y"
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
#line 1500 "gram1.y"
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
#line 1511 "gram1.y"
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
#line 1524 "gram1.y"
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
#line 1534 "gram1.y"
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
#line 1547 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1552 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1558 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1562 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1567 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1572 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1578 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1582 "gram1.y"
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
#line 1592 "gram1.y"
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
#line 1605 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1610 "gram1.y"
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
#line 1629 "gram1.y"
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
#line 1655 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1657 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1669 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1676 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1677 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1678 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1679 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1680 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1681 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1682 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1687 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1689 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1693 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1695 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1702 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1706 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1708 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1710 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1718 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1725 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1731 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1737 "gram1.y"
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
#line 1746 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1754 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1767 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1769 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1772 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1776 "gram1.y"
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
#line 1791 "gram1.y"
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
#line 1807 "gram1.y"
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
#line 1825 "gram1.y"
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
#line 1845 "gram1.y"
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
#line 1865 "gram1.y"
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
#line 1887 "gram1.y"
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
#line 1904 "gram1.y"
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
#line 1922 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1929 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1936 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1943 "gram1.y"
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
#line 1956 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1963 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1970 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1981 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 1985 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 1987 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 1992 "gram1.y"
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
#line 2010 "gram1.y"
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
#line 2021 "gram1.y"
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
#line 2033 "gram1.y"
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
#line 2045 "gram1.y"
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
#line 2059 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2065 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2072 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2078 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2084 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2092 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2099 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2118 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2132 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2136 "gram1.y"
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
#line 2181 "gram1.y"
    {;;}
    break;

  case 223:
#line 2185 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2189 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2195 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2199 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2203 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2205 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2209 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2211 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2215 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2219 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2221 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2225 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2227 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2229 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2234 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2258 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2303 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2305 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2312 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2319 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2326 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2335 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2337 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2339 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2343 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2345 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2349 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2358 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2365 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2372 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2374 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2378 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2382 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2388 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2390 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2394 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2398 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2403 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2410 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2417 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2427 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2429 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2433 "gram1.y"
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
#line 2445 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2448 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2457 "gram1.y"
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
#line 2470 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2476 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2482 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2488 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2496 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2506 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2508 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2512 "gram1.y"
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
#line 2533 "gram1.y"
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
#line 2558 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2560 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2564 "gram1.y"
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
#line 2595 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2597 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2600 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2601 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2606 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2610 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2618 "gram1.y"
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
#line 2627 "gram1.y"
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
#line 2636 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2646 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2655 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2657 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2661 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2669 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2684 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2691 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2693 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2697 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2712 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2713 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2717 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2719 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2731 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2733 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2737 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2743 "gram1.y"
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
#line 2755 "gram1.y"
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
#line 2766 "gram1.y"
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
#line 2783 "gram1.y"
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
#line 2821 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2823 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2827 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2829 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2831 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2842 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2846 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2852 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2854 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2858 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2862 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2866 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2868 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2872 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2874 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2876 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2878 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2880 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2882 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2884 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2886 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2888 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2890 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2892 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2894 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2896 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2898 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2900 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2902 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2904 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2906 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2908 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2910 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2912 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2914 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2916 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2919 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2920 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2932 "gram1.y"
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
#line 3006 "gram1.y"
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
#line 3018 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3020 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3024 "gram1.y"
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
#line 3155 "gram1.y"
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
#line 3205 "gram1.y"
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
#line 3249 "gram1.y"
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
#line 3291 "gram1.y"
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
#line 3349 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3351 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3353 "gram1.y"
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
#line 3393 "gram1.y"
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
#line 3435 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3445 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3447 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3451 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3455 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3457 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3461 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3463 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3469 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3471 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3477 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3487 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3493 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3500 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3506 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3514 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3522 "gram1.y"
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
#line 3538 "gram1.y"
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
#line 3548 "gram1.y"
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
#line 3561 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3568 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3570 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3593 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3595 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3597 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3599 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3601 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3603 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3605 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3607 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3610 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3610 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3611 "gram1.y"
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
#line 3625 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3627 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3650 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3652 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3654 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3670 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3672 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3674 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3687 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3691 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3693 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3701 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3703 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3705 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3707 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3761 "gram1.y"
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
#line 3783 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3796 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3805 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3808 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3858 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3864 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3869 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3887 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3889 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3891 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3893 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3895 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3898 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3904 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3906 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3908 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3911 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3913 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3915 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3942 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3951 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3959 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3961 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3963 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3968 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3975 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3983 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3985 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 3989 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 3992 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 3994 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 3998 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 4004 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 4006 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 4008 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 4010 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4014 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4016 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4024 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4026 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4032 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4034 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4038 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4042 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4063 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4066 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4070 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4072 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4079 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4083 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4085 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4101 "gram1.y"
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
#line 4114 "gram1.y"
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
#line 4137 "gram1.y"
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
#line 4160 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4162 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4169 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4171 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4173 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4175 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4177 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4182 "gram1.y"
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
#line 4257 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4269 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4276 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4279 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4281 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4290 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4297 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4304 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4312 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4317 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4322 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4325 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4328 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4331 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4334 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4337 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4355 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4359 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4364 "gram1.y"
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
#line 4383 "gram1.y"
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
#line 4402 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4410 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4414 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4419 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4426 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4428 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4430 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4433 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4434 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4445 "gram1.y"
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
#line 4460 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4464 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4472 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4475 "gram1.y"
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
#line 4485 "gram1.y"
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
#line 4498 "gram1.y"
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
#line 4511 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4515 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 546:
#line 4518 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4521 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 548:
#line 4525 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 549:
#line 4534 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 550:
#line 4537 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 551:
#line 4541 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 552:
#line 4543 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 553:
#line 4549 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4553 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 555:
#line 4555 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4557 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4564 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 558:
#line 4568 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 559:
#line 4570 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4572 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4576 "gram1.y"
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
#line 4595 "gram1.y"
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
#line 4611 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 564:
#line 4622 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 565:
#line 4629 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 566:
#line 4631 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 567:
#line 4635 "gram1.y"
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
#line 4661 "gram1.y"
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
#line 4676 "gram1.y"
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
#line 4691 "gram1.y"
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
#line 4708 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 572:
#line 4716 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 573:
#line 4725 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 574:
#line 4733 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 575:
#line 4738 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 576:
#line 4743 "gram1.y"
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
#line 4765 "gram1.y"
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
#line 4781 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 579:
#line 4783 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 580:
#line 4787 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 581:
#line 4789 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 582:
#line 4796 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 583:
#line 4798 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 584:
#line 4800 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 585:
#line 4804 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 586:
#line 4806 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 587:
#line 4808 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4810 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4812 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4814 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4818 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 592:
#line 4821 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 593:
#line 4824 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 594:
#line 4830 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 595:
#line 4836 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4844 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 597:
#line 4848 "gram1.y"
    { startioctl();;}
    break;

  case 598:
#line 4856 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 599:
#line 4858 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 600:
#line 4862 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4864 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 602:
#line 4866 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 603:
#line 4871 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 604:
#line 4876 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4881 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4886 "gram1.y"
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
#line 4895 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4900 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 609:
#line 4905 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 610:
#line 4907 "gram1.y"
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

  case 673:
#line 4989 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 674:
#line 4991 "gram1.y"
    { PTR_SYMB s;
                if((yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2)
                {
                  s = (yyvsp[(3) - (3)].ll_node)->entry.Template.ll_ptr1->entry.Template.symbol;
                  s->attr = s->attr | COMMON_BIT;
                }
	        add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	      ;}
    break;

  case 675:
#line 5002 "gram1.y"
    {PTR_SYMB s;
	      PTR_LLND q;
	    /* 27.06.18
	      if(! explicit_shape)   
                err("Explicit shape specification is required", 50);
	    */  
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

  case 676:
#line 5023 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 677:
#line 5027 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 678:
#line 5029 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 679:
#line 5033 "gram1.y"
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

  case 680:
#line 5046 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 681:
#line 5050 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 682:
#line 5052 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 683:
#line 5056 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
              else
                s->attr = s->attr | INHERIT_BIT;        
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 684:
#line 5067 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 685:
#line 5078 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 686:
#line 5082 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 687:
#line 5084 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 688:
#line 5088 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 689:
#line 5090 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 690:
#line 5092 "gram1.y"
    {
            if(parstate!=INEXEC) 
               err("Illegal shadow width specification", 56);  
            (yyval.ll_node) = make_llnd(fi,SHADOW_NAMES_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
          ;}
    break;

  case 691:
#line 5107 "gram1.y"
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

  case 692:
#line 5119 "gram1.y"
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

  case 693:
#line 5139 "gram1.y"
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

  case 694:
#line 5159 "gram1.y"
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

  case 695:
#line 5181 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 696:
#line 5187 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 697:
#line 5196 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 698:
#line 5204 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 699:
#line 5210 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 700:
#line 5218 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 701:
#line 5225 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 702:
#line 5231 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 703:
#line 5240 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 704:
#line 5244 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 705:
#line 5250 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 706:
#line 5258 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 707:
#line 5272 "gram1.y"
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

  case 708:
#line 5285 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 709:
#line 5291 "gram1.y"
    { PTR_LLND q;
             if(!(yyvsp[(4) - (5)].ll_node))
               err("Distribution format list is omitted", 51);
            /* if($6)
               err("NEW_VALUE specification in DISTRIBUTE directive");*/
             q = set_ll_list((yyvsp[(3) - (5)].ll_node),LLNULL,EXPR_LIST);
	     (yyval.bf_node) = get_bfnd(fi,DVM_DISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node));
            ;}
    break;

  case 710:
#line 5307 "gram1.y"
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

  case 711:
#line 5322 "gram1.y"
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

  case 712:
#line 5350 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 713:
#line 5352 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 714:
#line 5356 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 715:
#line 5358 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 716:
#line 5362 "gram1.y"
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

  case 717:
#line 5391 "gram1.y"
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

  case 718:
#line 5414 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 719:
#line 5434 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 720:
#line 5436 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 721:
#line 5440 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 722:
#line 5461 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 723:
#line 5463 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 724:
#line 5466 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 725:
#line 5475 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 726:
#line 5479 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 727:
#line 5484 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 728:
#line 5486 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 729:
#line 5488 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 730:
#line 5490 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 731:
#line 5496 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 732:
#line 5498 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 733:
#line 5502 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 734:
#line 5512 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 735:
#line 5516 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 736:
#line 5518 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 737:
#line 5523 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 738:
#line 5525 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 739:
#line 5529 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 740:
#line 5533 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 741:
#line 5539 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 742:
#line 5549 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 743:
#line 5551 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 744:
#line 5555 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 745:
#line 5557 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 746:
#line 5559 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 747:
#line 5566 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 748:
#line 5583 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 749:
#line 5585 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 750:
#line 5589 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 751:
#line 5591 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 752:
#line 5595 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 753:
#line 5602 "gram1.y"
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

  case 754:
#line 5612 "gram1.y"
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

  case 755:
#line 5641 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 756:
#line 5656 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 757:
#line 5663 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 758:
#line 5681 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 759:
#line 5683 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 760:
#line 5687 "gram1.y"
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

  case 761:
#line 5701 "gram1.y"
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

  case 762:
#line 5727 "gram1.y"
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

  case 763:
#line 5740 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 764:
#line 5756 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 765:
#line 5758 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 766:
#line 5761 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 767:
#line 5763 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 768:
#line 5769 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 769:
#line 5773 "gram1.y"
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

  case 770:
#line 5801 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 771:
#line 5803 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 772:
#line 5807 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 773:
#line 5815 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 774:
#line 5821 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 775:
#line 5824 "gram1.y"
    { PTR_SYMB s;
	             PTR_LLND q, r, p;
                     int numdim;
                     if((type_options & PROCESSORS_BIT)) { /* 27.06.18 || (type_options & TEMPLATE_BIT)){*/
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

  case 776:
#line 5881 "gram1.y"
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

  case 777:
#line 5945 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 778:
#line 5947 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 779:
#line 5950 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 780:
#line 5954 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 781:
#line 5958 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 782:
#line 5962 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 783:
#line 5979 "gram1.y"
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

  case 784:
#line 5991 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 785:
#line 5995 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 786:
#line 5999 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 787:
#line 6009 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 788:
#line 6014 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 789:
#line 6019 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 790:
#line 6026 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 791:
#line 6034 "gram1.y"
    {ndim = 0;;}
    break;

  case 792:
#line 6035 "gram1.y"
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

  case 793:
#line 6046 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), q, EXPR_LIST);
            ;}
    break;

  case 794:
#line 6057 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 795:
#line 6059 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 796:
#line 6063 "gram1.y"
    {PTR_SYMB s;
           /* s = make_scalar($1,TYNULL,LOCAL);*/
            s = make_array((yyvsp[(1) - (1)].hash_entry),TYNULL,LLNULL,0,LOCAL);
            s->attr = s->attr | DVM_POINTER_BIT;
            if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
               errstr( "Inconsistent declaration of identifier %s", s->ident, 16);     
            (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL,s);
            ;}
    break;

  case 797:
#line 6074 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 798:
#line 6078 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 799:
#line 6080 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 800:
#line 6084 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 801:
#line 6095 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 802:
#line 6099 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 803:
#line 6101 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 804:
#line 6105 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 805:
#line 6117 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 806:
#line 6119 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 807:
#line 6126 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 808:
#line 6128 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 809:
#line 6132 "gram1.y"
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

  case 810:
#line 6148 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 811:
#line 6158 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 812:
#line 6167 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 813:
#line 6169 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 815:
#line 6176 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 816:
#line 6179 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 817:
#line 6184 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 818:
#line 6194 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 819:
#line 6196 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 820:
#line 6200 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 821:
#line 6202 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 822:
#line 6210 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 823:
#line 6212 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 824:
#line 6216 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 825:
#line 6218 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 836:
#line 6235 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 837:
#line 6240 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 838:
#line 6244 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 839:
#line 6248 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 840:
#line 6252 "gram1.y"
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

  case 841:
#line 6265 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 842:
#line 6269 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 843:
#line 6273 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 844:
#line 6277 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 845:
#line 6280 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 846:
#line 6282 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 847:
#line 6284 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 848:
#line 6288 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 849:
#line 6290 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 850:
#line 6294 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 851:
#line 6299 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 852:
#line 6303 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 853:
#line 6307 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 854:
#line 6309 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 855:
#line 6313 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 856:
#line 6321 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 857:
#line 6327 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 858:
#line 6333 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 859:
#line 6337 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 860:
#line 6339 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 861:
#line 6343 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 862:
#line 6345 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 863:
#line 6349 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 864:
#line 6361 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 865:
#line 6363 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 866:
#line 6367 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 867:
#line 6371 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 868:
#line 6373 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 869:
#line 6377 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 870:
#line 6379 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 871:
#line 6381 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 872:
#line 6383 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 873:
#line 6385 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 874:
#line 6387 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 875:
#line 6389 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 876:
#line 6393 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 877:
#line 6397 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 878:
#line 6401 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 879:
#line 6405 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 880:
#line 6409 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 881:
#line 6416 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 882:
#line 6422 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 883:
#line 6426 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 884:
#line 6429 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 885:
#line 6433 "gram1.y"
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

  case 886:
#line 6446 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 887:
#line 6448 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 888:
#line 6452 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 889:
#line 6454 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 890:
#line 6459 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 891:
#line 6465 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 892:
#line 6471 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6477 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 894:
#line 6483 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 895:
#line 6489 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 896:
#line 6495 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6501 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 898:
#line 6507 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 899:
#line 6516 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 900:
#line 6522 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 901:
#line 6539 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 902:
#line 6547 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 903:
#line 6555 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 904:
#line 6557 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 905:
#line 6559 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 906:
#line 6563 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 907:
#line 6567 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 908:
#line 6569 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 909:
#line 6573 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 910:
#line 6575 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 911:
#line 6583 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 912:
#line 6587 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 913:
#line 6598 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 914:
#line 6602 "gram1.y"
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

  case 915:
#line 6620 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 916:
#line 6622 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 917:
#line 6626 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 918:
#line 6628 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 919:
#line 6632 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 920:
#line 6634 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 921:
#line 6638 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 922:
#line 6642 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 923:
#line 6646 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 924:
#line 6655 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 925:
#line 6659 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 926:
#line 6663 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 927:
#line 6668 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 928:
#line 6672 "gram1.y"
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
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 932:
#line 6695 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 933:
#line 6699 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 934:
#line 6701 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 935:
#line 6705 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 936:
#line 6707 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 937:
#line 6711 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 938:
#line 6716 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 939:
#line 6723 "gram1.y"
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

  case 940:
#line 6746 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 941:
#line 6748 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 942:
#line 6750 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 943:
#line 6752 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 944:
#line 6754 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 945:
#line 6758 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 946:
#line 6769 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 947:
#line 6773 "gram1.y"
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

  case 948:
#line 6788 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 949:
#line 6795 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 950:
#line 6801 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 951:
#line 6803 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 952:
#line 6807 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 953:
#line 6811 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 954:
#line 6819 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 955:
#line 6823 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 956:
#line 6827 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 957:
#line 6835 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 958:
#line 6840 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 959:
#line 6854 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 960:
#line 6856 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 961:
#line 6860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 962:
#line 6862 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 963:
#line 6871 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 964:
#line 6873 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 965:
#line 6875 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 966:
#line 6877 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 967:
#line 6913 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 968:
#line 6917 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 969:
#line 6921 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 970:
#line 6925 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 971:
#line 6929 "gram1.y"
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

  case 972:
#line 6941 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 973:
#line 6943 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 974:
#line 6947 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 975:
#line 6950 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 976:
#line 6952 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 977:
#line 6956 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 978:
#line 6961 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 979:
#line 6968 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 980:
#line 6971 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 981:
#line 6979 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 982:
#line 6983 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 983:
#line 6987 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 984:
#line 6990 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 985:
#line 6998 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_EXIT_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 986:
#line 7002 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 987:
#line 7006 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 988:
#line 7010 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 989:
#line 7014 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 990:
#line 7018 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 991:
#line 7022 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 992:
#line 7025 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 993:
#line 7027 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 994:
#line 7031 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 995:
#line 7033 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 996:
#line 7035 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 997:
#line 7039 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 998:
#line 7043 "gram1.y"
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

  case 999:
#line 7055 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1000:
#line 7057 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1001:
#line 7061 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1002:
#line 7063 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1003:
#line 7067 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1004:
#line 7069 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1005:
#line 7073 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1006:
#line 7077 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1007:
#line 7083 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1008:
#line 7095 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1009:
#line 7097 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1010:
#line 7101 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1011:
#line 7103 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1012:
#line 7107 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1013:
#line 7115 "gram1.y"
    { 
                PTR_LLND q;
                if((yyvsp[(16) - (16)].ll_node))
                  q = make_llnd(fi,ARRAY_OP, (yyvsp[(14) - (16)].ll_node), (yyvsp[(16) - (16)].ll_node), SMNULL);
                else
                  q = (yyvsp[(14) - (16)].ll_node);                  
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_CREATE_DIR,SMNULL,(yyvsp[(3) - (16)].ll_node),(yyvsp[(8) - (16)].ll_node),q); 
              ;}
    break;

  case 1014:
#line 7126 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1015:
#line 7128 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1016:
#line 7130 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1017:
#line 7134 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1018:
#line 7138 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1019:
#line 7140 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1020:
#line 7148 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1021:
#line 7152 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_CREATE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1022:
#line 7155 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1023:
#line 7157 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1051:
#line 7190 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1052:
#line 7196 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1053:
#line 7202 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1054:
#line 7208 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1055:
#line 7214 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1056:
#line 7218 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1066:
#line 7235 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1067:
#line 7240 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1068:
#line 7245 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1069:
#line 7251 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1070:
#line 7257 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1071:
#line 7263 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1072:
#line 7268 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1073:
#line 7274 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1074:
#line 7280 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1075:
#line 7286 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1076:
#line 7293 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1077:
#line 7299 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1078:
#line 7305 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1079:
#line 7312 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1081:
#line 7318 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1082:
#line 7324 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1083:
#line 7331 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1084:
#line 7337 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1085:
#line 7343 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1086:
#line 7349 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1087:
#line 7355 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1088:
#line 7361 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1089:
#line 7367 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1090:
#line 7373 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1091:
#line 7379 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1092:
#line 7385 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1093:
#line 7391 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1094:
#line 7397 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1095:
#line 7407 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1096:
#line 7412 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1097:
#line 7418 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1098:
#line 7422 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1103:
#line 7434 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1104:
#line 7442 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1105:
#line 7448 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1106:
#line 7454 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1107:
#line 7459 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1108:
#line 7465 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1109:
#line 7472 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1110:
#line 7478 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1111:
#line 7482 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1118:
#line 7496 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1119:
#line 7505 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1120:
#line 7509 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1121:
#line 7515 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1122:
#line 7522 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1123:
#line 7529 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1124:
#line 7536 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1125:
#line 7545 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1126:
#line 7551 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1127:
#line 7557 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1128:
#line 7561 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1131:
#line 7571 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1132:
#line 7577 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1133:
#line 7583 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1134:
#line 7587 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1137:
#line 7598 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1138:
#line 7604 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1139:
#line 7610 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1140:
#line 7615 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1141:
#line 7623 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1142:
#line 7629 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1143:
#line 7634 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1144:
#line 7641 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1145:
#line 7645 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1157:
#line 7665 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1158:
#line 7670 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1159:
#line 7675 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1160:
#line 7682 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1161:
#line 7687 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1162:
#line 7693 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1163:
#line 7699 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1164:
#line 7704 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1165:
#line 7709 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1166:
#line 7714 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1167:
#line 7718 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1168:
#line 7723 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1169:
#line 7728 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1170:
#line 7732 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1171:
#line 7737 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1172:
#line 7741 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1173:
#line 7747 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1174:
#line 7752 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1175:
#line 7758 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1176:
#line 7763 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1177:
#line 7769 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1178:
#line 7779 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1179:
#line 7783 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1180:
#line 7787 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1181:
#line 7791 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1182:
#line 7796 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1183:
#line 7799 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1190:
#line 7812 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1191:
#line 7816 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1192:
#line 7820 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1193:
#line 7822 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1194:
#line 7824 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1195:
#line 7828 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1196:
#line 7830 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1197:
#line 7832 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1198:
#line 7836 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1199:
#line 7838 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1200:
#line 7842 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1201:
#line 7844 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1202:
#line 7848 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1203:
#line 7851 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1204:
#line 7854 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1205:
#line 7859 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1206:
#line 7861 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1207:
#line 7863 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1208:
#line 7865 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1209:
#line 7867 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1210:
#line 7871 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1211:
#line 7875 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1212:
#line 7880 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1213:
#line 7884 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1214:
#line 7886 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1215:
#line 7890 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1216:
#line 7892 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1217:
#line 7896 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1218:
#line 7900 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1224:
#line 7911 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1225:
#line 7915 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1226:
#line 7919 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1227:
#line 7923 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1228:
#line 7927 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1229:
#line 7931 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1230:
#line 7933 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1233:
#line 7941 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1234:
#line 7945 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1235:
#line 7949 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1236:
#line 7951 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1240:
#line 7961 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1241:
#line 7965 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1242:
#line 7969 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1243:
#line 7973 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1244:
#line 7975 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1245:
#line 7979 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1246:
#line 7983 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;


/* Line 1267 of yacc.c.  */
#line 13702 "gram1.tab.c"
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



