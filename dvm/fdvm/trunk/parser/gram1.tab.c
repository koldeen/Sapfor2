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
     ACC_ROUTINE = 319,
     ACC_TIE = 320,
     BY = 321,
     IO_MODE = 322,
     CP_CREATE = 323,
     CP_LOAD = 324,
     CP_SAVE = 325,
     CP_WAIT = 326,
     FILES = 327,
     VARLIST = 328,
     STATUS = 329,
     EXITINTERVAL = 330,
     TEMPLATE_CREATE = 331,
     TEMPLATE_DELETE = 332,
     SPF_ANALYSIS = 333,
     SPF_PARALLEL = 334,
     SPF_TRANSFORM = 335,
     SPF_NOINLINE = 336,
     SPF_PARALLEL_REG = 337,
     SPF_END_PARALLEL_REG = 338,
     SPF_PRIVATES_EXPANSION = 339,
     SPF_FISSION = 340,
     SPF_SHRINK = 341,
     SPF_CHECKPOINT = 342,
     SPF_EXCEPT = 343,
     SPF_FILES_COUNT = 344,
     SPF_INTERVAL = 345,
     SPF_TIME = 346,
     SPF_ITER = 347,
     SPF_FLEXIBLE = 348,
     BINARY_OP = 351,
     UNARY_OP = 352
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
#define ACC_ROUTINE 319
#define ACC_TIE 320
#define BY 321
#define IO_MODE 322
#define CP_CREATE 323
#define CP_LOAD 324
#define CP_SAVE 325
#define CP_WAIT 326
#define FILES 327
#define VARLIST 328
#define STATUS 329
#define EXITINTERVAL 330
#define TEMPLATE_CREATE 331
#define TEMPLATE_DELETE 332
#define SPF_ANALYSIS 333
#define SPF_PARALLEL 334
#define SPF_TRANSFORM 335
#define SPF_NOINLINE 336
#define SPF_PARALLEL_REG 337
#define SPF_END_PARALLEL_REG 338
#define SPF_PRIVATES_EXPANSION 339
#define SPF_FISSION 340
#define SPF_SHRINK 341
#define SPF_CHECKPOINT 342
#define SPF_EXCEPT 343
#define SPF_FILES_COUNT 344
#define SPF_INTERVAL 345
#define SPF_TIME 346
#define SPF_ITER 347
#define SPF_FLEXIBLE 348
#define BINARY_OP 351
#define UNARY_OP 352




/* Copy the first part of user declarations.  */
#line 350 "gram1.y"

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
#line 431 "gram1.y"
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
#line 893 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 637 "gram1.y"

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
void delete_symbol();
void replace_symbol_in_expr();
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
#line 1050 "gram1.tab.c"

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
#define YYLAST   5731

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  353
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  530
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1280
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2535

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   352

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
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,     1,
       2,   351,   352
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
     947,   954,   962,   964,   966,   970,   972,   974,   976,   980,
     984,   985,   989,   990,   993,   997,   999,  1001,  1004,  1008,
    1010,  1012,  1014,  1018,  1020,  1024,  1026,  1028,  1032,  1037,
    1038,  1041,  1044,  1046,  1048,  1052,  1054,  1058,  1060,  1061,
    1062,  1063,  1066,  1067,  1069,  1071,  1073,  1076,  1079,  1084,
    1086,  1090,  1092,  1096,  1098,  1100,  1102,  1104,  1108,  1112,
    1116,  1120,  1124,  1127,  1130,  1133,  1137,  1141,  1145,  1149,
    1153,  1157,  1161,  1165,  1169,  1173,  1177,  1180,  1184,  1188,
    1190,  1192,  1194,  1196,  1198,  1200,  1206,  1213,  1218,  1224,
    1228,  1230,  1232,  1238,  1243,  1246,  1247,  1249,  1255,  1256,
    1258,  1260,  1264,  1266,  1270,  1273,  1275,  1277,  1279,  1281,
    1283,  1285,  1289,  1293,  1299,  1301,  1303,  1307,  1310,  1316,
    1321,  1326,  1330,  1333,  1335,  1336,  1337,  1344,  1346,  1348,
    1350,  1355,  1361,  1363,  1368,  1374,  1375,  1377,  1381,  1383,
    1385,  1387,  1390,  1394,  1398,  1401,  1403,  1406,  1409,  1412,
    1416,  1424,  1428,  1432,  1434,  1437,  1440,  1442,  1445,  1449,
    1451,  1453,  1455,  1461,  1469,  1470,  1477,  1482,  1494,  1508,
    1513,  1517,  1521,  1529,  1538,  1542,  1544,  1547,  1550,  1554,
    1556,  1560,  1561,  1563,  1564,  1566,  1568,  1571,  1577,  1584,
    1586,  1590,  1594,  1595,  1598,  1600,  1606,  1614,  1615,  1617,
    1621,  1625,  1632,  1638,  1645,  1650,  1656,  1662,  1665,  1667,
    1669,  1680,  1682,  1686,  1691,  1695,  1699,  1703,  1707,  1714,
    1721,  1727,  1736,  1739,  1743,  1747,  1755,  1763,  1764,  1766,
    1771,  1774,  1779,  1781,  1784,  1787,  1789,  1791,  1792,  1793,
    1794,  1797,  1800,  1803,  1806,  1809,  1811,  1814,  1817,  1821,
    1826,  1829,  1833,  1835,  1839,  1843,  1845,  1847,  1849,  1853,
    1855,  1857,  1862,  1868,  1870,  1872,  1876,  1880,  1882,  1887,
    1889,  1891,  1893,  1896,  1899,  1902,  1904,  1908,  1912,  1917,
    1922,  1924,  1928,  1930,  1936,  1938,  1940,  1942,  1946,  1950,
    1954,  1958,  1962,  1966,  1968,  1972,  1978,  1984,  1990,  1991,
    1992,  1994,  1998,  2000,  2002,  2006,  2010,  2014,  2018,  2021,
    2025,  2029,  2030,  2032,  2034,  2036,  2038,  2040,  2042,  2044,
    2046,  2048,  2050,  2052,  2054,  2056,  2058,  2060,  2062,  2064,
    2066,  2068,  2070,  2072,  2074,  2076,  2078,  2080,  2082,  2084,
    2086,  2088,  2090,  2092,  2094,  2096,  2098,  2100,  2102,  2104,
    2106,  2108,  2110,  2112,  2114,  2116,  2118,  2120,  2122,  2124,
    2126,  2128,  2130,  2132,  2134,  2136,  2138,  2140,  2142,  2144,
    2146,  2148,  2150,  2152,  2154,  2156,  2158,  2162,  2166,  2169,
    2173,  2175,  2179,  2181,  2185,  2187,  2191,  2193,  2198,  2202,
    2204,  2208,  2210,  2214,  2219,  2221,  2226,  2231,  2236,  2240,
    2244,  2246,  2250,  2254,  2256,  2260,  2264,  2266,  2270,  2274,
    2276,  2280,  2281,  2287,  2294,  2303,  2305,  2309,  2311,  2313,
    2315,  2320,  2322,  2323,  2326,  2330,  2333,  2338,  2339,  2341,
    2347,  2352,  2359,  2364,  2366,  2371,  2376,  2378,  2385,  2387,
    2391,  2393,  2397,  2399,  2404,  2406,  2408,  2412,  2414,  2416,
    2420,  2422,  2423,  2425,  2428,  2432,  2434,  2437,  2443,  2448,
    2453,  2460,  2462,  2466,  2468,  2470,  2477,  2482,  2484,  2488,
    2490,  2492,  2494,  2496,  2498,  2502,  2504,  2506,  2508,  2515,
    2520,  2522,  2527,  2529,  2531,  2533,  2535,  2540,  2543,  2551,
    2553,  2558,  2560,  2562,  2574,  2575,  2578,  2582,  2584,  2588,
    2590,  2594,  2596,  2600,  2602,  2606,  2608,  2612,  2614,  2618,
    2627,  2629,  2633,  2636,  2639,  2647,  2649,  2653,  2657,  2659,
    2664,  2666,  2670,  2672,  2674,  2675,  2677,  2679,  2682,  2684,
    2686,  2688,  2690,  2692,  2694,  2696,  2698,  2700,  2702,  2704,
    2713,  2720,  2729,  2736,  2738,  2745,  2752,  2759,  2766,  2768,
    2772,  2778,  2780,  2784,  2791,  2793,  2797,  2806,  2813,  2820,
    2825,  2831,  2837,  2840,  2843,  2844,  2846,  2850,  2852,  2857,
    2865,  2867,  2871,  2875,  2877,  2881,  2887,  2891,  2895,  2897,
    2901,  2903,  2905,  2909,  2913,  2917,  2921,  2932,  2941,  2952,
    2953,  2954,  2956,  2959,  2964,  2969,  2976,  2978,  2980,  2982,
    2984,  2986,  2988,  2990,  2992,  2994,  2996,  2998,  3005,  3010,
    3015,  3019,  3029,  3031,  3033,  3037,  3039,  3045,  3051,  3061,
    3062,  3064,  3066,  3070,  3074,  3078,  3082,  3086,  3093,  3097,
    3101,  3105,  3109,  3117,  3123,  3125,  3127,  3131,  3136,  3138,
    3140,  3144,  3146,  3148,  3152,  3156,  3159,  3163,  3168,  3173,
    3179,  3185,  3187,  3190,  3195,  3200,  3205,  3206,  3208,  3211,
    3219,  3226,  3230,  3234,  3242,  3248,  3250,  3254,  3256,  3261,
    3264,  3268,  3272,  3277,  3284,  3288,  3291,  3295,  3297,  3299,
    3304,  3310,  3314,  3321,  3324,  3329,  3332,  3334,  3338,  3342,
    3343,  3345,  3349,  3352,  3355,  3358,  3361,  3371,  3377,  3379,
    3383,  3386,  3389,  3392,  3402,  3407,  3409,  3413,  3415,  3417,
    3420,  3421,  3429,  3431,  3436,  3438,  3442,  3444,  3446,  3448,
    3465,  3466,  3470,  3474,  3478,  3482,  3489,  3499,  3505,  3507,
    3511,  3517,  3519,  3521,  3523,  3525,  3527,  3529,  3531,  3533,
    3535,  3537,  3539,  3541,  3543,  3545,  3547,  3549,  3551,  3553,
    3555,  3557,  3559,  3561,  3563,  3565,  3567,  3569,  3571,  3574,
    3577,  3582,  3586,  3591,  3597,  3599,  3601,  3603,  3605,  3607,
    3609,  3611,  3613,  3615,  3621,  3624,  3627,  3630,  3633,  3636,
    3642,  3644,  3646,  3648,  3653,  3658,  3663,  3668,  3670,  3672,
    3674,  3676,  3678,  3680,  3682,  3684,  3686,  3688,  3690,  3692,
    3694,  3696,  3698,  3703,  3707,  3712,  3718,  3720,  3722,  3724,
    3726,  3731,  3735,  3738,  3743,  3747,  3752,  3756,  3761,  3767,
    3769,  3771,  3773,  3775,  3777,  3779,  3781,  3789,  3795,  3797,
    3799,  3801,  3803,  3808,  3812,  3817,  3823,  3825,  3827,  3832,
    3836,  3841,  3847,  3849,  3851,  3854,  3856,  3859,  3864,  3868,
    3873,  3877,  3882,  3888,  3890,  3892,  3894,  3896,  3898,  3900,
    3902,  3904,  3906,  3908,  3910,  3913,  3918,  3922,  3925,  3930,
    3934,  3937,  3941,  3944,  3947,  3950,  3953,  3956,  3959,  3963,
    3966,  3972,  3975,  3981,  3984,  3990,  3992,  3994,  3998,  4002,
    4003,  4004,  4006,  4008,  4010,  4012,  4014,  4016,  4018,  4022,
    4025,  4031,  4036,  4039,  4045,  4050,  4053,  4056,  4058,  4060,
    4064,  4067,  4070,  4073,  4078,  4083,  4088,  4093,  4098,  4103,
    4105,  4107,  4109,  4113,  4116,  4119,  4121,  4123,  4127,  4130,
    4133,  4135,  4137,  4139,  4141,  4143,  4145,  4150,  4155,  4160,
    4163,  4165,  4167,  4171,  4173,  4175,  4177,  4183,  4189,  4195,
    4197,  4201,  4203,  4205,  4207,  4213,  4219,  4225,  4227,  4231,
    4234,  4240,  4243,  4249,  4255,  4257,  4259,  4263,  4268,  4270,
    4274,  4280,  4286,  4292,  4298,  4306,  4308,  4312,  4315,  4318,
    4321
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     354,     0,    -1,    -1,   354,   355,   116,    -1,   356,   357,
     574,    -1,   356,   374,   574,    -1,   356,   519,   574,    -1,
     356,   133,   370,    -1,   356,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   358,   365,    -1,    57,   358,   366,
      -1,   233,   358,   360,   367,    -1,   359,   233,   358,   360,
     367,    -1,   124,   358,   361,   367,   363,    -1,   362,   367,
     363,    -1,   114,   364,   367,   363,    -1,   164,   358,   364,
      -1,    -1,   202,   371,    -1,   195,   371,    -1,    95,   371,
      -1,   364,    -1,   364,    -1,   395,   124,   358,   364,    -1,
     395,   359,   124,   358,   364,    -1,   359,   124,   358,   364,
      -1,   359,   395,   124,   358,   364,    -1,   371,   372,    -1,
     371,   213,    15,   364,    21,    -1,   129,    -1,    -1,   364,
      -1,    -1,   364,    -1,    -1,    15,    21,    -1,    15,   368,
      21,    -1,   369,    -1,   368,     8,   369,    -1,   364,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   379,    -1,   380,
      -1,   381,    -1,   411,    -1,   407,    -1,   575,    -1,   416,
      -1,   417,    -1,   418,    -1,   476,    -1,   397,    -1,   412,
      -1,   422,    -1,   216,   486,    -1,   216,   486,   487,   453,
      -1,   123,   485,    -1,   183,   486,    15,   459,    21,    -1,
     387,    -1,   388,    -1,   393,    -1,   390,    -1,   392,    -1,
     408,    -1,   409,    -1,   410,    -1,   375,    -1,   463,    -1,
     461,    -1,   389,    -1,   142,   486,    -1,   142,   486,   364,
      -1,   141,   486,    15,   377,    21,    -1,   140,   486,    15,
      26,    21,    -1,   107,   528,    -1,    10,    -1,   376,    -1,
     378,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   486,
     487,   364,    -1,   245,     8,   486,   371,   386,   487,   364,
      -1,   112,   486,    -1,   112,   486,   364,    -1,   395,   382,
     364,   486,   469,   401,   406,    -1,   381,     8,   364,   469,
     401,   406,    -1,    -1,     7,     7,    -1,     8,   371,   383,
       7,     7,    -1,   384,    -1,   383,     8,   371,   384,    -1,
     183,    -1,   386,    -1,    44,    -1,    87,   469,    -1,   119,
      -1,   145,    15,   385,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   371,   148,
      -1,   371,   180,    -1,   371,   147,    -1,   194,    -1,   191,
      -1,   145,   486,    15,   385,    21,   487,   364,    -1,   387,
       8,   364,    -1,   178,   486,   487,   364,    -1,   388,     8,
     364,    -1,   230,   486,   487,   415,    -1,   389,     8,   415,
      -1,   191,   486,    -1,   191,   486,   487,   391,   455,    -1,
      -1,   219,   486,    -1,   194,   486,    -1,   194,   486,   487,
     394,   455,    -1,    -1,   399,   396,   403,   396,    -1,   244,
      15,   364,    21,   396,    -1,    -1,   398,   364,    -1,   397,
       8,   364,    -1,    13,    -1,     6,    -1,   400,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   402,    -1,     5,   549,   506,   550,
     396,    -1,     5,   549,    15,   550,     5,    21,    -1,     5,
     549,    15,   550,   492,    21,    -1,    -1,   402,    -1,    15,
     570,   404,   405,    21,    -1,    15,   570,   404,   405,     8,
     570,   404,   405,    21,    -1,   492,    -1,     5,    -1,   561,
     492,    -1,   561,     5,    -1,    -1,    -1,    26,   492,    -1,
      18,   492,    -1,    87,   487,   486,   364,   469,    -1,   407,
       8,   364,   469,    -1,    44,   486,   487,   415,    -1,   408,
       8,   415,    -1,   187,   486,   487,   415,    -1,   409,     8,
     415,    -1,   236,   486,   487,   415,    -1,   410,     8,   415,
      -1,    67,   486,   415,    -1,    67,   486,   414,   415,    -1,
     411,   543,   414,   543,   415,    -1,   411,     8,   415,    -1,
     167,   486,   413,   495,    -1,   412,   543,   413,   543,   495,
      -1,   412,     8,   495,    -1,    37,   364,    37,    -1,    23,
      -1,    37,   364,    37,    -1,   364,   469,    -1,   119,   486,
     487,   364,    -1,   416,     8,   364,    -1,   143,   486,   487,
     364,    -1,   417,     8,   364,    -1,   117,   486,   419,    -1,
     418,     8,   419,    -1,    15,   420,    21,    -1,   421,     8,
     421,    -1,   420,     8,   421,    -1,   364,    -1,   364,    15,
     491,    21,    -1,   500,    -1,   423,    -1,    80,   485,   424,
     426,    -1,   423,   543,   426,    -1,    -1,    -1,   427,    37,
     428,    37,    -1,   429,    -1,   427,     8,   429,    -1,   440,
      -1,   428,     8,   440,    -1,   430,   432,    -1,   430,   432,
     433,    -1,   430,   432,   434,    -1,   430,   432,   433,   434,
      -1,   430,   437,    -1,    -1,   364,    -1,   364,    -1,    15,
     435,    21,    -1,    15,   436,     7,   436,    21,    -1,   449,
      -1,   435,     8,   449,    -1,    -1,   449,    -1,    15,   438,
       8,   431,    26,   435,    21,    -1,   439,    -1,   438,     8,
     439,    -1,   432,   433,    -1,   432,   434,    -1,   432,   433,
     434,    -1,   437,    -1,   441,    -1,   430,   431,     5,   441,
      -1,   444,     5,   441,    -1,   430,   431,    -1,   443,    -1,
     445,    -1,   447,    -1,    36,    -1,    36,   246,   509,    -1,
      27,    -1,    27,   246,   509,    -1,    64,    -1,   442,    -1,
     430,   495,    15,   570,   488,    21,    -1,    59,    -1,   444,
      -1,    17,   444,    -1,    16,   444,    -1,   149,    -1,   149,
     246,   509,    -1,   446,    -1,    17,   446,    -1,    16,   446,
      -1,   201,    -1,   201,   246,   509,    -1,    92,    -1,    92,
     246,   509,    -1,    15,   448,     8,   448,    21,    -1,   445,
      -1,   443,    -1,   450,    -1,    17,   450,    -1,    16,   450,
      -1,   449,    17,   450,    -1,   449,    16,   450,    -1,   451,
      -1,   450,     5,   451,    -1,   450,    37,   451,    -1,   452,
      -1,   452,     9,   451,    -1,   149,    -1,   431,    -1,    15,
     449,    21,    -1,   454,    -1,   453,     8,   454,    -1,   415,
      -1,   414,    -1,   456,   458,   457,    -1,   455,     8,   456,
     458,   457,    -1,    -1,    -1,   364,    -1,   177,    15,   377,
      21,    -1,    47,    15,    26,    21,    -1,   460,    -1,   459,
       8,   460,    -1,   364,    26,   492,    -1,   163,   462,    -1,
     364,    -1,   462,     8,   364,    -1,   248,   486,   464,    -1,
     248,   486,   464,     8,   373,   467,    -1,   248,   486,   464,
       8,   373,   172,    -1,   248,   486,   464,     8,   373,   172,
     465,    -1,   364,    -1,   466,    -1,   465,     8,   466,    -1,
     468,    -1,   364,    -1,   468,    -1,   467,     8,   468,    -1,
     364,    18,   364,    -1,    -1,    15,   470,    21,    -1,    -1,
     471,   472,    -1,   470,     8,   472,    -1,   473,    -1,     7,
      -1,   492,     7,    -1,   492,     7,   473,    -1,     5,    -1,
     492,    -1,   475,    -1,   474,     8,   475,    -1,   149,    -1,
     130,   486,   477,    -1,   131,    -1,   478,    -1,   477,     8,
     478,    -1,   479,    15,   482,    21,    -1,    -1,   480,   481,
      -1,   231,   400,    -1,   395,    -1,   483,    -1,   482,     8,
     483,    -1,   484,    -1,   484,    16,   484,    -1,   129,    -1,
      -1,    -1,    -1,     7,     7,    -1,    -1,   490,    -1,   492,
      -1,   510,    -1,   561,   492,    -1,   570,   489,    -1,   490,
       8,   570,   489,    -1,   492,    -1,   491,     8,   492,    -1,
     493,    -1,    15,   492,    21,    -1,   508,    -1,   496,    -1,
     504,    -1,   511,    -1,   492,    17,   492,    -1,   492,    16,
     492,    -1,   492,     5,   492,    -1,   492,    37,   492,    -1,
     492,     9,   492,    -1,   376,   492,    -1,    17,   492,    -1,
      16,   492,    -1,   492,    25,   492,    -1,   492,    29,   492,
      -1,   492,    31,   492,    -1,   492,    28,   492,    -1,   492,
      30,   492,    -1,   492,    32,   492,    -1,   492,    24,   492,
      -1,   492,    33,   492,    -1,   492,    38,   492,    -1,   492,
      35,   492,    -1,   492,    22,   492,    -1,    34,   492,    -1,
     492,    23,   492,    -1,   492,   376,   492,    -1,    17,    -1,
      16,    -1,   364,    -1,   495,    -1,   498,    -1,   497,    -1,
     495,    15,   570,   488,    21,    -1,   495,    15,   570,   488,
      21,   502,    -1,   498,    15,   488,    21,    -1,   498,    15,
     488,    21,   502,    -1,   496,     3,   129,    -1,   495,    -1,
     498,    -1,   495,    15,   570,   488,    21,    -1,   498,    15,
     488,    21,    -1,   495,   502,    -1,    -1,   502,    -1,    15,
     503,     7,   503,    21,    -1,    -1,   492,    -1,   505,    -1,
     505,   246,   509,    -1,   506,    -1,   506,   246,   509,    -1,
     507,   501,    -1,    36,    -1,    27,    -1,   201,    -1,    92,
      -1,   149,    -1,    64,    -1,   495,   246,    64,    -1,   506,
     246,    64,    -1,    15,   493,     8,   493,    21,    -1,   495,
      -1,   506,    -1,   492,     7,   492,    -1,   492,     7,    -1,
     492,     7,   492,     7,   492,    -1,   492,     7,     7,   492,
      -1,     7,   492,     7,   492,    -1,     7,     7,   492,    -1,
       7,   492,    -1,     7,    -1,    -1,    -1,    14,   405,   512,
     567,   513,    20,    -1,   495,    -1,   498,    -1,   499,    -1,
     515,     8,   570,   499,    -1,   515,     8,   570,   561,   495,
      -1,   514,    -1,   516,     8,   570,   514,    -1,   516,     8,
     570,   561,   495,    -1,    -1,   495,    -1,   518,     8,   495,
      -1,   540,    -1,   539,    -1,   522,    -1,   530,   522,    -1,
     102,   548,   528,    -1,   103,   548,   527,    -1,   108,   528,
      -1,   520,    -1,   530,   520,    -1,   531,   540,    -1,   531,
     239,    -1,   530,   531,   239,    -1,    97,   548,    15,   492,
      21,   239,   527,    -1,    96,   548,   527,    -1,   106,   548,
     527,    -1,   523,    -1,    76,   548,    -1,   532,   540,    -1,
     532,    -1,   530,   532,    -1,   105,   548,   527,    -1,   576,
      -1,   839,    -1,   857,    -1,    89,   548,    15,   492,    21,
      -1,    89,   548,   549,   538,   550,   610,   521,    -1,    -1,
       8,   371,   254,    15,   492,    21,    -1,   254,    15,   492,
      21,    -1,   185,   548,   549,   538,   550,   543,   536,    26,
     492,     8,   492,    -1,   185,   548,   549,   538,   550,   543,
     536,    26,   492,     8,   492,     8,   492,    -1,    62,   548,
     524,   527,    -1,    84,   548,   527,    -1,   110,   548,   527,
      -1,   218,   548,   371,    62,    15,   492,    21,    -1,   530,
     218,   548,   371,    62,    15,   492,    21,    -1,    15,   526,
      21,    -1,   492,    -1,   492,     7,    -1,     7,   492,    -1,
     492,     7,   492,    -1,   525,    -1,   526,     8,   525,    -1,
      -1,   364,    -1,    -1,   364,    -1,    75,    -1,   529,     7,
      -1,   155,   548,    15,   492,    21,    -1,   122,   548,    15,
     533,   535,    21,    -1,   534,    -1,   533,     8,   534,    -1,
     536,    26,   510,    -1,    -1,     8,   492,    -1,   364,    -1,
     536,    26,   492,     8,   492,    -1,   536,    26,   492,     8,
     492,     8,   492,    -1,    -1,   149,    -1,   113,   548,   527,
      -1,    98,   548,   527,    -1,    98,   548,    15,   492,    21,
     527,    -1,   252,   548,    15,   492,    21,    -1,   530,   252,
     548,    15,   492,    21,    -1,   541,   492,    26,   492,    -1,
     188,   548,   496,    18,   492,    -1,    48,   548,   475,   240,
     364,    -1,    77,   548,    -1,   542,    -1,   551,    -1,    46,
     548,    15,   492,    21,   475,     8,   475,     8,   475,    -1,
     544,    -1,   544,    15,    21,    -1,   544,    15,   545,    21,
      -1,   214,   548,   503,    -1,   547,   548,   503,    -1,    79,
     548,   527,    -1,   115,   548,   527,    -1,    45,   548,    15,
     517,   515,    21,    -1,    81,   548,    15,   517,   516,    21,
      -1,   170,   548,    15,   518,    21,    -1,   253,   548,    15,
     492,    21,   496,    26,   492,    -1,   152,   425,    -1,   186,
     548,   475,    -1,    49,   548,   364,    -1,    49,   548,   364,
     543,    15,   474,    21,    -1,    69,   548,    15,   474,    21,
     543,   492,    -1,    -1,     8,    -1,    61,   548,   364,   570,
      -1,   570,   546,    -1,   545,     8,   570,   546,    -1,   492,
      -1,   561,   492,    -1,     5,   475,    -1,   184,    -1,   232,
      -1,    -1,    -1,    -1,   552,   558,    -1,   552,   573,    -1,
     552,     5,    -1,   552,     9,    -1,   554,   558,    -1,   556,
      -1,   562,   558,    -1,   562,   557,    -1,   562,   558,   565,
      -1,   562,   557,     8,   565,    -1,   563,   558,    -1,   563,
     558,   567,    -1,   564,    -1,   564,     8,   567,    -1,   553,
     548,   571,    -1,    53,    -1,   215,    -1,   104,    -1,   555,
     548,   571,    -1,   176,    -1,    66,    -1,   139,   548,   571,
     558,    -1,   139,   548,   571,   558,   567,    -1,   573,    -1,
       5,    -1,    15,   572,    21,    -1,    15,   559,    21,    -1,
     560,    -1,   559,     8,   570,   560,    -1,   572,    -1,     5,
      -1,     9,    -1,   561,   492,    -1,   561,     5,    -1,   561,
       9,    -1,   166,    -1,   197,   548,   571,    -1,   256,   548,
     571,    -1,   190,   548,   572,   571,    -1,   190,   548,     5,
     571,    -1,   566,    -1,   565,     8,   566,    -1,   496,    -1,
      15,   565,     8,   537,    21,    -1,   493,    -1,   569,    -1,
     568,    -1,   493,     8,   493,    -1,   493,     8,   569,    -1,
     569,     8,   493,    -1,   569,     8,   569,    -1,   568,     8,
     493,    -1,   568,     8,   569,    -1,   508,    -1,    15,   492,
      21,    -1,    15,   493,     8,   537,    21,    -1,    15,   569,
       8,   537,    21,    -1,    15,   568,     8,   537,    21,    -1,
      -1,    -1,   573,    -1,    15,   572,    21,    -1,   496,    -1,
     504,    -1,   572,   494,   572,    -1,   572,     5,   572,    -1,
     572,    37,   572,    -1,   572,     9,   572,    -1,   494,   572,
      -1,   572,    23,   572,    -1,   129,    26,   492,    -1,    -1,
     257,    -1,   577,    -1,   625,    -1,   600,    -1,   579,    -1,
     590,    -1,   585,    -1,   637,    -1,   640,    -1,   717,    -1,
     582,    -1,   591,    -1,   593,    -1,   595,    -1,   597,    -1,
     645,    -1,   651,    -1,   648,    -1,   776,    -1,   774,    -1,
     601,    -1,   626,    -1,   655,    -1,   706,    -1,   704,    -1,
     705,    -1,   707,    -1,   708,    -1,   709,    -1,   710,    -1,
     711,    -1,   719,    -1,   721,    -1,   726,    -1,   723,    -1,
     725,    -1,   729,    -1,   727,    -1,   728,    -1,   740,    -1,
     744,    -1,   745,    -1,   748,    -1,   747,    -1,   749,    -1,
     750,    -1,   751,    -1,   752,    -1,   654,    -1,   734,    -1,
     735,    -1,   736,    -1,   739,    -1,   753,    -1,   756,    -1,
     761,    -1,   766,    -1,   768,    -1,   769,    -1,   770,    -1,
     771,    -1,   773,    -1,   732,    -1,   775,    -1,    82,   486,
     578,    -1,   577,     8,   578,    -1,   364,   469,    -1,    94,
     486,   580,    -1,   581,    -1,   580,     8,   581,    -1,   364,
      -1,   138,   486,   583,    -1,   584,    -1,   583,     8,   584,
      -1,   364,    -1,   228,   486,   589,   586,    -1,    15,   587,
      21,    -1,   588,    -1,   587,     8,   588,    -1,   492,    -1,
     492,     7,   492,    -1,     7,    15,   491,    21,    -1,   364,
      -1,   259,   486,   364,   469,    -1,   303,   486,   364,   469,
      -1,   590,     8,   364,   469,    -1,   136,   486,   592,    -1,
     591,     8,   592,    -1,   364,    -1,   211,   486,   594,    -1,
     593,     8,   594,    -1,   364,    -1,   205,   486,   596,    -1,
     595,     8,   596,    -1,   364,    -1,    70,   486,   598,    -1,
     597,     8,   598,    -1,   364,    -1,   175,   364,   469,    -1,
      -1,    88,   486,   604,   607,   599,    -1,   204,   548,   604,
     608,   610,   599,    -1,   204,   548,   608,   610,   599,     7,
       7,   602,    -1,   603,    -1,   602,     8,   603,    -1,   604,
      -1,   605,    -1,   364,    -1,   364,    15,   491,    21,    -1,
     364,    -1,    -1,   608,   610,    -1,    15,   609,    21,    -1,
     610,   611,    -1,   609,     8,   610,   611,    -1,    -1,    58,
      -1,    58,    15,   570,   624,    21,    -1,   126,    15,   612,
      21,    -1,   258,    15,   612,     8,   492,    21,    -1,   165,
      15,   492,    21,    -1,     5,    -1,   137,    15,   612,    21,
      -1,    86,    15,   613,    21,    -1,   364,    -1,    15,   614,
      21,   371,   255,   616,    -1,   615,    -1,   614,     8,   615,
      -1,   492,    -1,   492,     7,   492,    -1,   617,    -1,   617,
      15,   618,    21,    -1,   364,    -1,   619,    -1,   618,     8,
     619,    -1,   492,    -1,   765,    -1,    40,   620,   621,    -1,
     364,    -1,    -1,   622,    -1,    17,   623,    -1,   621,    17,
     623,    -1,   492,    -1,   561,   492,    -1,   561,   492,     8,
     561,   492,    -1,    43,   486,   628,   630,    -1,   199,   548,
     629,   630,    -1,   199,   548,   630,     7,     7,   627,    -1,
     629,    -1,   627,     8,   629,    -1,   364,    -1,   495,    -1,
      15,   635,    21,   371,   255,   631,    -1,   634,    15,   632,
      21,    -1,   633,    -1,   632,     8,   633,    -1,   492,    -1,
       5,    -1,   510,    -1,   364,    -1,   636,    -1,   635,     8,
     636,    -1,   364,    -1,     5,    -1,     7,    -1,   638,     7,
       7,   486,   364,   469,    -1,   637,     8,   364,   469,    -1,
     639,    -1,   638,     8,   371,   639,    -1,    82,    -1,   259,
      -1,   303,    -1,    94,    -1,    87,    15,   470,    21,    -1,
     228,   586,    -1,    43,    15,   635,    21,   371,   255,   631,
      -1,    43,    -1,    88,   608,   610,   599,    -1,    88,    -1,
      67,    -1,   395,     8,   371,    93,   486,    15,   641,    21,
       7,     7,   643,    -1,    -1,   642,     7,    -1,   641,     8,
       7,    -1,   644,    -1,   643,     8,   644,    -1,   364,    -1,
     127,   486,   646,    -1,   647,    -1,   646,     8,   647,    -1,
     364,    -1,    74,   486,   649,    -1,   650,    -1,   649,     8,
     650,    -1,   364,    -1,    51,   486,   652,    -1,    51,   486,
       8,   371,    67,     7,     7,   652,    -1,   653,    -1,   652,
       8,   653,    -1,   364,   469,    -1,   168,   548,    -1,   182,
     548,    15,   656,    21,   657,   661,    -1,   495,    -1,   656,
       8,   495,    -1,   610,   173,   658,    -1,   610,    -1,   495,
      15,   659,    21,    -1,   660,    -1,   659,     8,   660,    -1,
     492,    -1,     5,    -1,    -1,   662,    -1,   663,    -1,   662,
     663,    -1,   667,    -1,   689,    -1,   697,    -1,   664,    -1,
     674,    -1,   676,    -1,   675,    -1,   665,    -1,   668,    -1,
     669,    -1,   672,    -1,     8,   371,   209,    15,   712,     7,
     713,    21,    -1,     8,   371,   209,    15,   713,    21,    -1,
       8,   371,    71,    15,   666,     7,   713,    21,    -1,     8,
     371,    71,    15,   713,    21,    -1,   364,    -1,     8,   371,
     169,    15,   671,    21,    -1,     8,   371,   282,    15,   671,
      21,    -1,     8,   371,   191,    15,   671,    21,    -1,     8,
     371,   320,    15,   670,    21,    -1,   492,    -1,   492,     8,
     492,    -1,   492,     8,   492,     8,   492,    -1,   496,    -1,
     671,     8,   496,    -1,     8,   371,   322,    15,   673,    21,
      -1,   658,    -1,   673,     8,   658,    -1,     8,   371,   135,
      15,   712,     7,   730,    21,    -1,     8,   371,   135,    15,
     730,    21,    -1,     8,   371,   229,    15,   492,    21,    -1,
       8,   371,    41,   677,    -1,     8,   371,    41,   677,   677,
      -1,    15,   610,   678,   679,    21,    -1,   148,     7,    -1,
     180,     7,    -1,    -1,   680,    -1,   679,     8,   680,    -1,
     702,    -1,   702,    15,   681,    21,    -1,   702,    15,   681,
      21,    15,   683,    21,    -1,   682,    -1,   681,     8,   682,
      -1,   492,     7,   492,    -1,   684,    -1,   683,     8,   684,
      -1,   685,     7,   686,     7,   687,    -1,   685,     7,   686,
      -1,   685,     7,   687,    -1,   685,    -1,   686,     7,   687,
      -1,   686,    -1,   687,    -1,   371,   217,   688,    -1,   371,
     157,   688,    -1,   371,   128,   688,    -1,    15,   490,    21,
      -1,     8,   371,   208,    15,   690,   694,   691,     8,   693,
      21,    -1,     8,   371,   208,    15,   690,   694,   691,    21,
      -1,     8,   371,   208,    15,   690,   692,   691,     7,   693,
      21,    -1,    -1,    -1,   364,    -1,   371,   694,    -1,   693,
       8,   371,   694,    -1,   695,    15,   496,    21,    -1,   696,
      15,   671,     8,   492,    21,    -1,   234,    -1,   192,    -1,
     162,    -1,   159,    -1,    35,    -1,    22,    -1,    24,    -1,
      33,    -1,   247,    -1,   158,    -1,   161,    -1,     8,   371,
     223,    15,   699,    21,    -1,     8,   371,   224,   698,    -1,
       8,   371,   226,   698,    -1,     8,   371,   221,    -1,     8,
     371,   221,    15,   702,    15,   587,    21,    21,    -1,   364,
      -1,   700,    -1,   699,     8,   700,    -1,   702,    -1,   702,
      15,   701,    78,    21,    -1,   702,    15,   701,   587,    21,
      -1,   702,    15,   701,   587,    21,    15,   371,    78,    21,
      -1,    -1,   495,    -1,   702,    -1,   703,     8,   702,    -1,
     225,   548,   698,    -1,   224,   548,   698,    -1,   227,   548,
     698,    -1,   226,   548,   698,    -1,   222,   548,   698,    15,
     699,    21,    -1,   206,   548,   692,    -1,   207,   548,   692,
      -1,    72,   548,   666,    -1,    73,   548,   666,    -1,   210,
     548,    15,   712,     7,   713,    21,    -1,   210,   548,    15,
     713,    21,    -1,   364,    -1,   714,    -1,   713,     8,   714,
      -1,   702,    15,   715,    21,    -1,   702,    -1,   716,    -1,
     715,     8,   716,    -1,   492,    -1,     7,    -1,   237,   486,
     718,    -1,   717,     8,   718,    -1,   364,   469,    -1,   238,
     548,   720,    -1,   238,   548,   720,   689,    -1,   238,   548,
     720,   665,    -1,   238,   548,   720,   689,   665,    -1,   238,
     548,   720,   665,   689,    -1,   364,    -1,   111,   548,    -1,
     720,    15,   492,    21,    -1,   720,    15,   510,    21,    -1,
     174,   548,   497,   724,    -1,    -1,   667,    -1,   109,   548,
      -1,   160,   548,   722,   371,   175,   606,   469,    -1,   160,
     548,   722,   371,   323,   496,    -1,   189,   548,   712,    -1,
     212,   548,   712,    -1,   135,   548,    15,   712,     7,   730,
      21,    -1,   135,   548,    15,   730,    21,    -1,   731,    -1,
     730,     8,   731,    -1,   702,    -1,   702,    15,   491,    21,
      -1,   134,   548,    -1,   134,   548,   667,    -1,   134,   548,
     733,    -1,   134,   548,   667,   733,    -1,     8,   371,   208,
      15,   671,    21,    -1,    50,   548,   738,    -1,    99,   548,
      -1,    52,   548,   738,    -1,   364,    -1,   737,    -1,   737,
      15,   491,    21,    -1,   120,   548,   496,    26,   496,    -1,
      83,   548,   743,    -1,    83,   548,   743,    15,   741,    21,
      -1,   570,   742,    -1,   741,     8,   570,   742,    -1,   561,
     492,    -1,   149,    -1,   100,   548,   743,    -1,   146,   548,
     746,    -1,    -1,   492,    -1,   332,   548,   491,    -1,   101,
     548,    -1,   241,   548,    -1,   242,   548,    -1,    56,   548,
      -1,    65,   548,   570,    15,   545,    21,   405,   487,   671,
      -1,   324,   548,    15,   754,    21,    -1,   755,    -1,   754,
       8,   755,    -1,   371,   315,    -1,   371,   318,    -1,   371,
     182,    -1,   220,   548,    15,   757,    26,   623,    21,   610,
     760,    -1,   495,    15,   758,    21,    -1,   759,    -1,   758,
       8,   759,    -1,   613,    -1,   765,    -1,   132,   703,    -1,
      -1,   153,   548,    15,   495,    18,   762,    21,    -1,   495,
      -1,   495,    15,   763,    21,    -1,   764,    -1,   763,     8,
     764,    -1,   765,    -1,     7,    -1,     5,    -1,   325,   548,
     492,     8,   371,   330,    15,   671,    21,     8,   371,   329,
      15,   491,    21,   767,    -1,    -1,     8,   371,   182,    -1,
       8,   371,   318,    -1,   326,   548,   492,    -1,   327,   548,
     492,    -1,   327,   548,   492,     8,   371,   315,    -1,   328,
     548,   492,     8,   371,   331,    15,   495,    21,    -1,   333,
     548,    15,   772,    21,    -1,   499,    -1,   772,     8,   499,
      -1,   334,   548,    15,   656,    21,    -1,   825,    -1,   778,
      -1,   777,    -1,   795,    -1,   798,    -1,   799,    -1,   800,
      -1,   801,    -1,   807,    -1,   810,    -1,   815,    -1,   816,
      -1,   817,    -1,   820,    -1,   821,    -1,   822,    -1,   823,
      -1,   824,    -1,   826,    -1,   827,    -1,   828,    -1,   829,
      -1,   830,    -1,   831,    -1,   832,    -1,   833,    -1,   834,
      -1,   268,   548,    -1,   275,   548,    -1,   291,   548,   610,
     779,    -1,   291,   548,   610,    -1,   543,   610,   780,   610,
      -1,   779,   543,   610,   780,   610,    -1,   782,    -1,   791,
      -1,   786,    -1,   787,    -1,   783,    -1,   784,    -1,   785,
      -1,   789,    -1,   790,    -1,   837,    15,   838,   836,    21,
      -1,   191,   781,    -1,   282,   781,    -1,   285,   781,    -1,
     265,   781,    -1,   299,   781,    -1,    84,    15,   371,   788,
      21,    -1,   191,    -1,   299,    -1,   288,    -1,   304,    15,
     492,    21,    -1,   289,    15,   492,    21,    -1,   208,    15,
     792,    21,    -1,   610,   794,     7,   793,    -1,   671,    -1,
      17,    -1,    16,    -1,     5,    -1,    37,    -1,   162,    -1,
     159,    -1,    35,    -1,    22,    -1,    24,    -1,    33,    -1,
     305,    -1,   306,    -1,   307,    -1,   247,    -1,   297,   548,
     610,   796,    -1,   297,   548,   610,    -1,   543,   610,   797,
     610,    -1,   796,   543,   610,   797,   610,    -1,   782,    -1,
     791,    -1,   783,    -1,   784,    -1,   279,   548,   610,   814,
      -1,   279,   548,   610,    -1,   296,   548,    -1,   269,   548,
     610,   802,    -1,   269,   548,   610,    -1,   272,   548,   610,
     814,    -1,   272,   548,   610,    -1,   543,   610,   803,   610,
      -1,   802,   543,   610,   803,   610,    -1,   782,    -1,   791,
      -1,   783,    -1,   784,    -1,   805,    -1,   804,    -1,   290,
      -1,   298,    15,   371,   806,     8,   492,    21,    -1,   298,
      15,   371,   806,    21,    -1,   230,    -1,    94,    -1,   284,
      -1,   295,    -1,   300,   548,   610,   808,    -1,   300,   548,
     610,    -1,   543,   610,   809,   610,    -1,   808,   543,   610,
     809,   610,    -1,   782,    -1,   783,    -1,   280,   548,   610,
     811,    -1,   280,   548,   610,    -1,   543,   610,   812,   610,
      -1,   811,   543,   610,   812,   610,    -1,   814,    -1,   813,
      -1,   266,   781,    -1,   287,    -1,   302,   548,    -1,   281,
     548,   610,   814,    -1,   281,   548,   610,    -1,   292,   548,
     610,   818,    -1,   292,   548,   610,    -1,   543,   610,   819,
     610,    -1,   818,   543,   610,   819,   610,    -1,   782,    -1,
     791,    -1,   786,    -1,   787,    -1,   783,    -1,   784,    -1,
     785,    -1,   789,    -1,   790,    -1,   805,    -1,   804,    -1,
     276,   548,    -1,   293,   548,   610,   779,    -1,   293,   548,
     610,    -1,   277,   548,    -1,   294,   548,   610,   779,    -1,
     294,   548,   610,    -1,   278,   548,    -1,   301,   486,   781,
      -1,   286,   548,    -1,   273,   548,    -1,   290,   548,    -1,
     274,   548,    -1,   264,   548,    -1,   263,   548,    -1,   283,
     548,   781,    -1,   283,   548,    -1,   267,   548,    15,   495,
      21,    -1,   267,   548,    -1,   271,   548,    15,   495,    21,
      -1,   271,   548,    -1,    37,   364,   837,    37,   838,    -1,
     835,    -1,   495,    -1,   836,     8,   835,    -1,   836,     8,
     495,    -1,    -1,    -1,   840,    -1,   853,    -1,   841,    -1,
     854,    -1,   842,    -1,   843,    -1,   855,    -1,   308,   548,
     844,    -1,   310,   548,    -1,   312,   548,    15,   850,    21,
      -1,   312,   548,    15,    21,    -1,   312,   548,    -1,   313,
     548,    15,   850,    21,    -1,   313,   548,    15,    21,    -1,
     313,   548,    -1,   371,   372,    -1,   845,    -1,   846,    -1,
     845,     8,   846,    -1,   371,   847,    -1,   371,   849,    -1,
     371,   848,    -1,   147,    15,   850,    21,    -1,   148,    15,
     850,    21,    -1,   180,    15,   850,    21,    -1,   318,    15,
     850,    21,    -1,   319,    15,   850,    21,    -1,   314,    15,
     851,    21,    -1,   315,    -1,   671,    -1,   852,    -1,   851,
       8,   852,    -1,   371,   316,    -1,   371,   317,    -1,   309,
      -1,   311,    -1,   321,   486,   856,    -1,   371,   372,    -1,
     371,   848,    -1,   858,    -1,   859,    -1,   860,    -1,   861,
      -1,   862,    -1,   877,    -1,   335,    15,   863,    21,    -1,
     336,    15,   868,    21,    -1,   337,    15,   873,    21,    -1,
     339,   875,    -1,   340,    -1,   864,    -1,   863,     8,   864,
      -1,   865,    -1,   866,    -1,   867,    -1,   371,   208,    15,
     693,    21,    -1,   371,   191,    15,   671,    21,    -1,   371,
     183,    15,   459,    21,    -1,   869,    -1,   868,     8,   869,
      -1,   870,    -1,   871,    -1,   872,    -1,   371,   228,    15,
     699,    21,    -1,   371,    41,    15,   699,    21,    -1,   371,
     209,    15,   713,    21,    -1,   874,    -1,   873,     8,   874,
      -1,   371,   338,    -1,   371,   342,    15,   656,    21,    -1,
     371,   341,    -1,   371,   341,    15,   656,    21,    -1,   371,
     343,    15,   876,    21,    -1,   364,    -1,   499,    -1,   876,
       8,   499,    -1,   344,    15,   878,    21,    -1,   879,    -1,
     878,     8,   879,    -1,   371,   244,    15,   880,    21,    -1,
     371,   330,    15,   656,    21,    -1,   371,   345,    15,   656,
      21,    -1,   371,   346,    15,   492,    21,    -1,   371,   347,
      15,   882,     8,   492,    21,    -1,   881,    -1,   880,     8,
     881,    -1,   371,   315,    -1,   371,   350,    -1,   371,   348,
      -1,   371,   349,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   783,   783,   784,   788,   790,   804,   835,   844,   850,
     870,   879,   895,   907,   917,   924,   930,   935,   940,   964,
     991,  1005,  1007,  1009,  1013,  1030,  1044,  1068,  1084,  1098,
    1116,  1118,  1125,  1129,  1130,  1137,  1138,  1146,  1147,  1149,
    1153,  1154,  1158,  1162,  1168,  1178,  1182,  1187,  1194,  1195,
    1196,  1197,  1198,  1199,  1200,  1201,  1202,  1203,  1204,  1205,
    1206,  1207,  1212,  1217,  1224,  1226,  1227,  1228,  1229,  1230,
    1231,  1232,  1233,  1234,  1235,  1236,  1237,  1240,  1244,  1252,
    1260,  1269,  1277,  1281,  1283,  1287,  1289,  1291,  1293,  1295,
    1297,  1299,  1301,  1303,  1305,  1307,  1309,  1311,  1313,  1315,
    1317,  1319,  1321,  1326,  1335,  1345,  1353,  1363,  1384,  1404,
    1405,  1407,  1411,  1413,  1417,  1421,  1423,  1427,  1433,  1437,
    1439,  1443,  1447,  1451,  1455,  1459,  1465,  1469,  1473,  1479,
    1484,  1491,  1502,  1515,  1526,  1539,  1549,  1562,  1567,  1574,
    1577,  1582,  1587,  1594,  1597,  1607,  1621,  1624,  1643,  1670,
    1672,  1684,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1703,
    1704,  1708,  1710,  1717,  1722,  1723,  1725,  1727,  1740,  1746,
    1752,  1761,  1770,  1783,  1784,  1787,  1791,  1806,  1821,  1839,
    1860,  1880,  1902,  1919,  1937,  1944,  1951,  1958,  1971,  1978,
    1985,  1996,  2000,  2002,  2007,  2025,  2036,  2048,  2060,  2074,
    2080,  2087,  2093,  2099,  2107,  2114,  2130,  2133,  2142,  2144,
    2148,  2152,  2172,  2176,  2178,  2182,  2183,  2186,  2188,  2190,
    2192,  2194,  2197,  2200,  2204,  2210,  2214,  2218,  2220,  2225,
    2226,  2230,  2234,  2236,  2240,  2242,  2244,  2249,  2253,  2255,
    2257,  2260,  2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,
    2272,  2273,  2279,  2282,  2283,  2285,  2289,  2290,  2293,  2294,
    2296,  2300,  2301,  2302,  2303,  2305,  2308,  2309,  2318,  2320,
    2327,  2334,  2341,  2350,  2352,  2354,  2358,  2360,  2364,  2373,
    2380,  2387,  2389,  2393,  2397,  2403,  2405,  2410,  2414,  2418,
    2425,  2432,  2442,  2444,  2448,  2460,  2463,  2472,  2485,  2491,
    2497,  2503,  2511,  2521,  2523,  2527,  2529,  2562,  2564,  2568,
    2607,  2608,  2612,  2612,  2617,  2621,  2629,  2638,  2647,  2657,
    2663,  2666,  2668,  2672,  2680,  2695,  2702,  2704,  2708,  2724,
    2724,  2728,  2730,  2742,  2744,  2748,  2754,  2766,  2778,  2795,
    2824,  2825,  2833,  2834,  2838,  2840,  2842,  2853,  2857,  2863,
    2865,  2869,  2871,  2873,  2877,  2879,  2883,  2885,  2887,  2889,
    2891,  2893,  2895,  2897,  2899,  2901,  2903,  2905,  2907,  2909,
    2911,  2913,  2915,  2917,  2919,  2921,  2923,  2925,  2927,  2931,
    2932,  2943,  3017,  3029,  3031,  3035,  3166,  3216,  3260,  3302,
    3360,  3362,  3364,  3403,  3446,  3457,  3458,  3462,  3467,  3468,
    3472,  3474,  3480,  3482,  3488,  3498,  3504,  3511,  3517,  3525,
    3533,  3549,  3559,  3572,  3579,  3581,  3604,  3606,  3608,  3610,
    3612,  3614,  3616,  3618,  3622,  3622,  3622,  3636,  3638,  3661,
    3663,  3665,  3681,  3683,  3685,  3699,  3702,  3704,  3712,  3714,
    3716,  3718,  3772,  3792,  3807,  3816,  3819,  3869,  3875,  3880,
    3898,  3900,  3902,  3904,  3906,  3909,  3915,  3917,  3919,  3922,
    3924,  3926,  3953,  3962,  3971,  3972,  3974,  3979,  3986,  3994,
    3996,  4000,  4003,  4005,  4009,  4015,  4017,  4019,  4021,  4025,
    4027,  4036,  4037,  4044,  4045,  4049,  4053,  4074,  4077,  4081,
    4083,  4090,  4095,  4096,  4107,  4124,  4147,  4172,  4173,  4180,
    4182,  4184,  4186,  4188,  4192,  4269,  4281,  4288,  4290,  4291,
    4293,  4302,  4309,  4316,  4324,  4329,  4334,  4337,  4340,  4343,
    4346,  4349,  4353,  4371,  4376,  4395,  4414,  4418,  4419,  4422,
    4426,  4431,  4438,  4440,  4442,  4446,  4447,  4458,  4473,  4477,
    4484,  4487,  4497,  4510,  4523,  4526,  4528,  4531,  4534,  4538,
    4547,  4550,  4554,  4556,  4562,  4566,  4568,  4570,  4577,  4581,
    4583,  4587,  4589,  4593,  4612,  4628,  4637,  4646,  4648,  4652,
    4678,  4693,  4708,  4725,  4733,  4742,  4750,  4755,  4760,  4782,
    4798,  4800,  4804,  4806,  4813,  4815,  4817,  4821,  4823,  4825,
    4827,  4829,  4831,  4835,  4838,  4841,  4847,  4853,  4862,  4866,
    4873,  4875,  4879,  4881,  4883,  4888,  4893,  4898,  4903,  4912,
    4917,  4923,  4924,  4939,  4940,  4941,  4942,  4943,  4944,  4945,
    4946,  4947,  4948,  4949,  4950,  4951,  4952,  4953,  4954,  4955,
    4956,  4957,  4960,  4961,  4962,  4963,  4964,  4965,  4966,  4967,
    4968,  4969,  4970,  4971,  4972,  4973,  4974,  4975,  4976,  4977,
    4978,  4979,  4980,  4981,  4982,  4983,  4984,  4985,  4986,  4987,
    4988,  4989,  4990,  4991,  4992,  4993,  4994,  4995,  4996,  4997,
    4998,  4999,  5000,  5001,  5002,  5003,  5007,  5009,  5020,  5041,
    5045,  5047,  5051,  5064,  5068,  5070,  5074,  5085,  5096,  5100,
    5102,  5106,  5108,  5110,  5125,  5137,  5157,  5177,  5199,  5205,
    5214,  5222,  5228,  5236,  5243,  5249,  5258,  5262,  5268,  5276,
    5290,  5304,  5309,  5325,  5340,  5368,  5370,  5374,  5376,  5380,
    5409,  5432,  5453,  5454,  5458,  5479,  5481,  5485,  5493,  5497,
    5502,  5504,  5506,  5508,  5514,  5516,  5520,  5530,  5534,  5536,
    5541,  5543,  5547,  5551,  5557,  5567,  5569,  5573,  5575,  5577,
    5584,  5602,  5603,  5607,  5609,  5613,  5620,  5630,  5659,  5674,
    5681,  5699,  5701,  5705,  5719,  5745,  5758,  5774,  5776,  5779,
    5781,  5787,  5791,  5819,  5821,  5825,  5833,  5839,  5842,  5900,
    5964,  5966,  5969,  5973,  5977,  5981,  5998,  6010,  6014,  6018,
    6028,  6033,  6038,  6045,  6054,  6054,  6065,  6076,  6078,  6082,
    6093,  6097,  6099,  6103,  6114,  6118,  6120,  6124,  6136,  6138,
    6145,  6147,  6151,  6167,  6175,  6186,  6188,  6192,  6195,  6200,
    6210,  6212,  6216,  6218,  6227,  6228,  6232,  6234,  6239,  6240,
    6241,  6242,  6243,  6244,  6245,  6246,  6247,  6248,  6249,  6252,
    6257,  6261,  6265,  6269,  6282,  6286,  6290,  6294,  6297,  6299,
    6301,  6305,  6307,  6311,  6315,  6317,  6321,  6326,  6330,  6334,
    6336,  6340,  6348,  6354,  6361,  6364,  6366,  6370,  6372,  6376,
    6388,  6390,  6394,  6398,  6400,  6404,  6406,  6408,  6410,  6412,
    6414,  6416,  6420,  6424,  6428,  6432,  6436,  6443,  6449,  6454,
    6457,  6460,  6473,  6475,  6479,  6481,  6486,  6492,  6498,  6504,
    6510,  6516,  6522,  6528,  6534,  6543,  6549,  6566,  6568,  6576,
    6584,  6586,  6590,  6594,  6596,  6600,  6602,  6610,  6614,  6626,
    6629,  6647,  6649,  6653,  6655,  6659,  6661,  6665,  6669,  6673,
    6682,  6686,  6690,  6695,  6699,  6711,  6713,  6717,  6722,  6726,
    6728,  6732,  6734,  6738,  6743,  6750,  6773,  6775,  6777,  6779,
    6781,  6785,  6796,  6800,  6815,  6822,  6829,  6830,  6834,  6838,
    6846,  6850,  6854,  6862,  6867,  6881,  6883,  6887,  6889,  6898,
    6900,  6902,  6904,  6940,  6944,  6948,  6952,  6956,  6968,  6970,
    6974,  6977,  6979,  6983,  6988,  6995,  6998,  7006,  7010,  7015,
    7017,  7024,  7029,  7033,  7037,  7041,  7045,  7049,  7052,  7054,
    7058,  7060,  7062,  7066,  7070,  7082,  7084,  7088,  7090,  7094,
    7097,  7100,  7104,  7110,  7122,  7124,  7128,  7130,  7134,  7142,
    7154,  7155,  7157,  7161,  7165,  7167,  7175,  7179,  7182,  7184,
    7188,  7192,  7194,  7195,  7196,  7197,  7198,  7199,  7200,  7201,
    7202,  7203,  7204,  7205,  7206,  7207,  7208,  7209,  7210,  7211,
    7212,  7213,  7214,  7215,  7216,  7217,  7218,  7219,  7222,  7228,
    7234,  7240,  7246,  7250,  7256,  7257,  7258,  7259,  7260,  7261,
    7262,  7263,  7264,  7267,  7272,  7277,  7283,  7289,  7295,  7300,
    7306,  7312,  7318,  7325,  7331,  7337,  7344,  7348,  7350,  7356,
    7363,  7369,  7375,  7381,  7387,  7393,  7399,  7405,  7411,  7417,
    7423,  7429,  7439,  7444,  7450,  7454,  7460,  7461,  7462,  7463,
    7466,  7474,  7480,  7486,  7491,  7497,  7504,  7510,  7514,  7520,
    7521,  7522,  7523,  7524,  7525,  7528,  7537,  7541,  7547,  7554,
    7561,  7568,  7577,  7583,  7589,  7593,  7599,  7600,  7603,  7609,
    7615,  7619,  7626,  7627,  7630,  7636,  7642,  7647,  7655,  7661,
    7666,  7673,  7677,  7683,  7684,  7685,  7686,  7687,  7688,  7689,
    7690,  7691,  7692,  7693,  7697,  7702,  7707,  7714,  7719,  7725,
    7731,  7736,  7741,  7746,  7750,  7755,  7760,  7764,  7769,  7773,
    7779,  7784,  7790,  7795,  7801,  7811,  7815,  7819,  7823,  7829,
    7832,  7836,  7837,  7838,  7839,  7840,  7841,  7842,  7845,  7849,
    7853,  7855,  7857,  7861,  7863,  7865,  7869,  7871,  7875,  7877,
    7881,  7884,  7887,  7892,  7894,  7896,  7898,  7900,  7904,  7908,
    7913,  7917,  7919,  7923,  7925,  7929,  7933,  7937,  7941,  7943,
    7947,  7948,  7949,  7950,  7951,  7952,  7955,  7959,  7963,  7967,
    7971,  7975,  7977,  7981,  7982,  7983,  7986,  7990,  7994,  7998,
    8000,  8004,  8005,  8006,  8010,  8014,  8018,  8022,  8024,  8028,
    8030,  8032,  8034,  8037,  8041,  8045,  8047,  8051,  8055,  8057,
    8061,  8063,  8065,  8067,  8069,  8073,  8075,  8079,  8081,  8085,
    8087
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
  "ACC_LOCAL", "ACC_INLOCAL", "ACC_CUDA_BLOCK", "ACC_ROUTINE", "ACC_TIE",
  "BY", "IO_MODE", "CP_CREATE", "CP_LOAD", "CP_SAVE", "CP_WAIT", "FILES",
  "VARLIST", "STATUS", "EXITINTERVAL", "TEMPLATE_CREATE",
  "TEMPLATE_DELETE", "SPF_ANALYSIS", "SPF_PARALLEL", "SPF_TRANSFORM",
  "SPF_NOINLINE", "SPF_PARALLEL_REG", "SPF_END_PARALLEL_REG",
  "SPF_PRIVATES_EXPANSION", "SPF_FISSION", "SPF_SHRINK", "SPF_CHECKPOINT",
  "SPF_EXCEPT", "SPF_FILES_COUNT", "SPF_INTERVAL", "SPF_TIME", "SPF_ITER",
  "SPF_FLEXIBLE", "BINARY_OP", "UNARY_OP", "$accept", "program", "stat",
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
  "intonlyoff", "io", "iofmove", "fmkwd", "iofctl", "ctlkwd", "inquire",
  "infmt", "ioctl", "ctllist", "ioclause", "nameeq", "read", "write",
  "print", "inlist", "inelt", "outlist", "out2", "other", "in_ioctl",
  "start_ioctl", "fexpr", "unpar_fexpr", "cmnt", "dvm_specification",
  "dvm_exec", "dvm_template", "template_obj", "dvm_dynamic",
  "dyn_array_name_list", "dyn_array_name", "dvm_inherit",
  "dummy_array_name_list", "dummy_array_name", "dvm_shadow",
  "shadow_attr_stuff", "sh_width_list", "sh_width", "sh_array_name",
  "dvm_processors", "dvm_indirect_group", "indirect_group_name",
  "dvm_remote_group", "remote_group_name", "dvm_reduction_group",
  "reduction_group_name", "dvm_consistent_group", "consistent_group_name",
  "opt_onto", "dvm_distribute", "dvm_redistribute", "dist_name_list",
  "distributee", "dist_name", "pointer_ar_elem", "processors_name",
  "opt_dist_format_clause", "dist_format_clause", "dist_format_list",
  "opt_key_word", "dist_format", "array_name", "derived_spec",
  "derived_elem_list", "derived_elem", "target_spec", "derived_target",
  "derived_subscript_list", "derived_subscript", "dummy_ident",
  "opt_plus_shadow", "plus_shadow", "shadow_id", "shadow_width",
  "dvm_align", "dvm_realign", "realignee_list", "alignee", "realignee",
  "align_directive_stuff", "align_base", "align_subscript_list",
  "align_subscript", "align_base_name", "dim_ident_list", "dim_ident",
  "dvm_combined_dir", "dvm_attribute_list", "dvm_attribute", "dvm_pointer",
  "dimension_list", "@5", "pointer_var_list", "pointer_var", "dvm_heap",
  "heap_array_name_list", "heap_array_name", "dvm_consistent",
  "consistent_array_name_list", "consistent_array_name", "dvm_asyncid",
  "async_id_list", "async_id", "dvm_new_value", "dvm_parallel_on",
  "ident_list", "opt_on", "distribute_cycles", "par_subscript_list",
  "par_subscript", "opt_spec", "spec_list", "par_spec",
  "remote_access_spec", "consistent_spec", "consistent_group", "new_spec",
  "private_spec", "cuda_block_spec", "sizelist", "variable_list",
  "tie_spec", "tied_array_list", "indirect_access_spec", "stage_spec",
  "across_spec", "in_out_across", "opt_in_out", "dependent_array_list",
  "dependent_array", "dependence_list", "dependence", "section_spec_list",
  "section_spec", "ar_section", "low_section", "high_section", "section",
  "reduction_spec", "opt_key_word_r", "no_opt_key_word_r",
  "reduction_group", "reduction_list", "reduction", "reduction_op",
  "loc_op", "shadow_spec", "shadow_group_name", "shadow_list", "shadow",
  "opt_corner", "array_ident", "array_ident_list", "dvm_shadow_start",
  "dvm_shadow_wait", "dvm_shadow_group", "dvm_reduction_start",
  "dvm_reduction_wait", "dvm_consistent_start", "dvm_consistent_wait",
  "dvm_remote_access", "group_name", "remote_data_list", "remote_data",
  "remote_index_list", "remote_index", "dvm_task", "task_array",
  "dvm_task_region", "task_name", "dvm_end_task_region", "task", "dvm_on",
  "opt_new_spec", "dvm_end_on", "dvm_map", "dvm_prefetch", "dvm_reset",
  "dvm_indirect_access", "indirect_list", "indirect_reference",
  "hpf_independent", "hpf_reduction_spec", "dvm_asynchronous",
  "dvm_endasynchronous", "dvm_asyncwait", "async_ident", "async",
  "dvm_f90", "dvm_debug_dir", "debparamlist", "debparam",
  "fragment_number", "dvm_enddebug_dir", "dvm_interval_dir",
  "interval_number", "dvm_exit_interval_dir", "dvm_endinterval_dir",
  "dvm_traceon_dir", "dvm_traceoff_dir", "dvm_barrier_dir", "dvm_check",
  "dvm_io_mode_dir", "mode_list", "mode_spec", "dvm_shadow_add",
  "template_ref", "shadow_axis_list", "shadow_axis", "opt_include_to",
  "dvm_localize", "localize_target", "target_subscript_list",
  "target_subscript", "aster_expr", "dvm_cp_create", "opt_mode",
  "dvm_cp_load", "dvm_cp_save", "dvm_cp_wait", "dvm_template_create",
  "template_list", "dvm_template_delete", "omp_specification_directive",
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
  "acc_routine", "opt_targets_clause", "spf_directive", "spf_analysis",
  "spf_parallel", "spf_transform", "spf_parallel_reg",
  "spf_end_parallel_reg", "analysis_spec_list", "analysis_spec",
  "analysis_reduction_spec", "analysis_private_spec",
  "analysis_parameter_spec", "parallel_spec_list", "parallel_spec",
  "parallel_shadow_spec", "parallel_across_spec",
  "parallel_remote_access_spec", "transform_spec_list", "transform_spec",
  "region_name", "array_element_list", "spf_checkpoint",
  "checkpoint_spec_list", "checkpoint_spec", "spf_type_list", "spf_type",
  "interval_spec", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   349,   350,     1,     2,     3,     4,     5,     6,     7,
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
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   351,   352
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   353,   354,   354,   355,   355,   355,   355,   355,   355,
     355,   356,   357,   357,   357,   357,   357,   357,   357,   357,
     358,   359,   359,   359,   360,   361,   362,   362,   362,   362,
     363,   363,   364,   365,   365,   366,   366,   367,   367,   367,
     368,   368,   369,   369,   370,   371,   372,   373,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   375,   375,   375,
     375,   375,   376,   377,   377,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   379,   379,   380,   380,   381,   381,   382,
     382,   382,   383,   383,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   385,   385,   385,   386,
     386,   387,   387,   388,   388,   389,   389,   390,   390,   391,
     392,   393,   393,   394,   395,   395,   396,   397,   397,   398,
     398,   399,   400,   400,   400,   400,   400,   400,   400,   401,
     401,   402,   402,   402,   403,   403,   403,   403,   404,   404,
     404,   404,   405,   406,   406,   406,   407,   407,   408,   408,
     409,   409,   410,   410,   411,   411,   411,   411,   412,   412,
     412,   413,   414,   414,   415,   416,   416,   417,   417,   418,
     418,   419,   420,   420,   421,   421,   421,   422,   423,   423,
     424,   425,   426,   427,   427,   428,   428,   429,   429,   429,
     429,   429,   430,   431,   432,   433,   434,   435,   435,   436,
     436,   437,   438,   438,   439,   439,   439,   439,   440,   440,
     440,   441,   441,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   442,   443,   443,   443,   444,   444,   445,   445,
     445,   446,   446,   446,   446,   447,   448,   448,   449,   449,
     449,   449,   449,   450,   450,   450,   451,   451,   452,   452,
     452,   453,   453,   454,   454,   455,   455,   456,   457,   458,
     458,   458,   459,   459,   460,   461,   462,   462,   463,   463,
     463,   463,   464,   465,   465,   466,   466,   467,   467,   468,
     469,   469,   471,   470,   470,   472,   472,   472,   472,   473,
     473,   474,   474,   475,   476,   476,   477,   477,   478,   480,
     479,   481,   481,   482,   482,   483,   483,   484,   485,   486,
     487,   487,   488,   488,   489,   489,   489,   490,   490,   491,
     491,   492,   492,   492,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   494,
     494,   495,   496,   496,   496,   497,   497,   497,   497,   498,
     499,   499,   499,   499,   500,   501,   501,   502,   503,   503,
     504,   504,   504,   504,   504,   505,   505,   505,   505,   506,
     507,   507,   507,   508,   509,   509,   510,   510,   510,   510,
     510,   510,   510,   510,   512,   513,   511,   514,   514,   515,
     515,   515,   516,   516,   516,   517,   518,   518,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   520,   520,   521,   521,   521,   522,   522,   523,
     523,   523,   523,   523,   524,   525,   525,   525,   525,   526,
     526,   527,   527,   528,   528,   529,   530,   531,   532,   533,
     533,   534,   535,   535,   536,   537,   537,   538,   538,   539,
     539,   539,   539,   539,   540,   540,   540,   540,   540,   540,
     540,   540,   540,   540,   540,   540,   540,   540,   540,   540,
     540,   540,   541,   542,   542,   542,   542,   543,   543,   544,
     545,   545,   546,   546,   546,   547,   547,   548,   549,   550,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     551,   551,   551,   551,   552,   553,   553,   553,   554,   555,
     555,   556,   556,   557,   557,   558,   558,   559,   559,   560,
     560,   560,   560,   560,   560,   561,   562,   563,   564,   564,
     565,   565,   566,   566,   567,   567,   567,   568,   568,   568,
     568,   568,   568,   569,   569,   569,   569,   569,   570,   571,
     572,   572,   573,   573,   573,   573,   573,   573,   573,   573,
     573,   574,   574,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   576,   576,   576,   576,
     576,   576,   576,   576,   576,   576,   577,   577,   578,   579,
     580,   580,   581,   582,   583,   583,   584,   585,   586,   587,
     587,   588,   588,   588,   589,   590,   590,   590,   591,   591,
     592,   593,   593,   594,   595,   595,   596,   597,   597,   598,
     599,   599,   600,   601,   601,   602,   602,   603,   603,   604,
     605,   606,   607,   607,   608,   609,   609,   610,   611,   611,
     611,   611,   611,   611,   611,   611,   612,   613,   614,   614,
     615,   615,   616,   616,   617,   618,   618,   619,   619,   619,
     620,   621,   621,   622,   622,   623,   624,   624,   625,   626,
     626,   627,   627,   628,   629,   630,   631,   632,   632,   633,
     633,   633,   634,   635,   635,   636,   636,   636,   637,   637,
     638,   638,   639,   639,   639,   639,   639,   639,   639,   639,
     639,   639,   639,   640,   642,   641,   641,   643,   643,   644,
     645,   646,   646,   647,   648,   649,   649,   650,   651,   651,
     652,   652,   653,   654,   655,   656,   656,   657,   657,   658,
     659,   659,   660,   660,   661,   661,   662,   662,   663,   663,
     663,   663,   663,   663,   663,   663,   663,   663,   663,   664,
     664,   665,   665,   666,   667,   667,   668,   669,   670,   670,
     670,   671,   671,   672,   673,   673,   674,   674,   675,   676,
     676,   677,   678,   678,   678,   679,   679,   680,   680,   680,
     681,   681,   682,   683,   683,   684,   684,   684,   684,   684,
     684,   684,   685,   686,   687,   688,   689,   689,   689,   690,
     691,   692,   693,   693,   694,   694,   695,   695,   695,   695,
     695,   695,   695,   695,   695,   696,   696,   697,   697,   697,
     697,   697,   698,   699,   699,   700,   700,   700,   700,   701,
     702,   703,   703,   704,   704,   705,   705,   706,   707,   708,
     709,   710,   711,   711,   712,   713,   713,   714,   714,   715,
     715,   716,   716,   717,   717,   718,   719,   719,   719,   719,
     719,   720,   721,   722,   722,   723,   724,   724,   725,   726,
     726,   727,   728,   729,   729,   730,   730,   731,   731,   732,
     732,   732,   732,   733,   734,   735,   736,   737,   738,   738,
     739,   740,   740,   741,   741,   742,   743,   744,   745,   746,
     746,   747,   748,   749,   750,   751,   752,   753,   754,   754,
     755,   755,   755,   756,   757,   758,   758,   759,   759,   760,
     760,   761,   762,   762,   763,   763,   764,   764,   765,   766,
     767,   767,   767,   768,   769,   769,   770,   771,   772,   772,
     773,   774,   775,   775,   775,   775,   775,   775,   775,   775,
     775,   775,   775,   775,   775,   775,   775,   775,   775,   775,
     775,   775,   775,   775,   775,   775,   775,   775,   776,   777,
     778,   778,   779,   779,   780,   780,   780,   780,   780,   780,
     780,   780,   780,   781,   782,   783,   784,   785,   786,   787,
     788,   788,   788,   789,   790,   791,   792,   793,   794,   794,
     794,   794,   794,   794,   794,   794,   794,   794,   794,   794,
     794,   794,   795,   795,   796,   796,   797,   797,   797,   797,
     798,   798,   799,   800,   800,   801,   801,   802,   802,   803,
     803,   803,   803,   803,   803,   804,   805,   805,   806,   806,
     806,   806,   807,   807,   808,   808,   809,   809,   810,   810,
     811,   811,   812,   812,   813,   814,   815,   816,   816,   817,
     817,   818,   818,   819,   819,   819,   819,   819,   819,   819,
     819,   819,   819,   819,   820,   821,   821,   822,   823,   823,
     824,   825,   826,   827,   828,   829,   830,   831,   832,   832,
     833,   833,   834,   834,   835,   836,   836,   836,   836,   837,
     838,   839,   839,   839,   839,   839,   839,   839,   840,   841,
     842,   842,   842,   843,   843,   843,   844,   844,   845,   845,
     846,   846,   846,   847,   847,   847,   847,   847,   848,   849,
     850,   851,   851,   852,   852,   853,   854,   855,   856,   856,
     857,   857,   857,   857,   857,   857,   858,   859,   860,   861,
     862,   863,   863,   864,   864,   864,   865,   866,   867,   868,
     868,   869,   869,   869,   870,   871,   872,   873,   873,   874,
     874,   874,   874,   874,   875,   876,   876,   877,   878,   878,
     879,   879,   879,   879,   879,   880,   880,   881,   881,   882,
     882
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
       6,     7,     1,     1,     3,     1,     1,     1,     3,     3,
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
       2,     2,     2,     2,     2,     1,     2,     2,     3,     4,
       2,     3,     1,     3,     3,     1,     1,     1,     3,     1,
       1,     4,     5,     1,     1,     3,     3,     1,     4,     1,
       1,     1,     2,     2,     2,     1,     3,     3,     4,     4,
       1,     3,     1,     5,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     5,     5,     5,     0,     0,
       1,     3,     1,     1,     3,     3,     3,     3,     2,     3,
       3,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     3,
       1,     3,     1,     3,     1,     3,     1,     4,     3,     1,
       3,     1,     3,     4,     1,     4,     4,     4,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     0,     5,     6,     8,     1,     3,     1,     1,     1,
       4,     1,     0,     2,     3,     2,     4,     0,     1,     5,
       4,     6,     4,     1,     4,     4,     1,     6,     1,     3,
       1,     3,     1,     4,     1,     1,     3,     1,     1,     3,
       1,     0,     1,     2,     3,     1,     2,     5,     4,     4,
       6,     1,     3,     1,     1,     6,     4,     1,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     6,     4,
       1,     4,     1,     1,     1,     1,     4,     2,     7,     1,
       4,     1,     1,    11,     0,     2,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     8,
       1,     3,     2,     2,     7,     1,     3,     3,     1,     4,
       1,     3,     1,     1,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     8,
       6,     8,     6,     1,     6,     6,     6,     6,     1,     3,
       5,     1,     3,     6,     1,     3,     8,     6,     6,     4,
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
       1,     3,     2,     2,     2,     2,     9,     5,     1,     3,
       2,     2,     2,     9,     4,     1,     3,     1,     1,     2,
       0,     7,     1,     4,     1,     3,     1,     1,     1,    16,
       0,     3,     3,     3,     3,     6,     9,     5,     1,     3,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     3,     4,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     2,     2,     2,     2,     2,     5,
       1,     1,     1,     4,     4,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     4,     5,     1,     1,     1,     1,
       4,     3,     2,     4,     3,     4,     3,     4,     5,     1,
       1,     1,     1,     1,     1,     1,     7,     5,     1,     1,
       1,     1,     4,     3,     4,     5,     1,     1,     4,     3,
       4,     5,     1,     1,     2,     1,     2,     4,     3,     4,
       3,     4,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     3,     2,     4,     3,
       2,     3,     2,     2,     2,     2,     2,     2,     3,     2,
       5,     2,     5,     2,     5,     1,     1,     3,     3,     0,
       0,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       5,     4,     2,     5,     4,     2,     2,     1,     1,     3,
       2,     2,     2,     4,     4,     4,     4,     4,     4,     1,
       1,     1,     3,     2,     2,     1,     1,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     2,
       1,     1,     3,     1,     1,     1,     5,     5,     5,     1,
       3,     1,     1,     1,     5,     5,     5,     1,     3,     2,
       5,     2,     5,     5,     1,     1,     3,     4,     1,     3,
       5,     5,     5,     5,     7,     1,     3,     2,     2,     2,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,    10,    11,     9,     0,     0,     3,   150,
     149,   789,   339,   537,   537,   537,   537,   537,   339,   537,
     555,   537,    20,   537,   537,   158,   537,   560,   339,   154,
     537,   339,   537,   537,   339,   485,   537,   537,   537,   338,
     537,   782,   537,   537,   340,   791,   537,   155,   156,   785,
      45,   537,   537,   537,   537,   537,   537,   537,   537,   557,
     537,   537,   483,   483,   537,   537,   537,   339,   537,     0,
     537,   339,   339,   537,   537,   338,    20,   339,   339,   325,
       0,   537,   537,   339,   339,   537,   339,   339,   339,   339,
     152,   339,   537,   211,   537,   157,   537,   537,     0,    20,
     339,   537,   537,   537,   559,   339,   537,   339,   535,   537,
     537,   339,   537,   537,   537,   339,    20,   339,    45,   537,
     537,   153,    45,   537,   339,   537,   537,   537,   339,   537,
     537,   556,   339,   537,   339,   537,   537,   537,   537,   537,
     537,   339,   339,   536,    20,   339,   339,   537,   537,   537,
       0,   339,     8,   339,   537,   537,   537,   783,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   339,   537,   784,   537,  1225,   537,
    1226,   537,   537,   339,   537,   537,   537,   537,   537,   537,
     537,   537,     0,     0,     0,     0,  1240,     0,   611,     0,
      37,   611,    73,    48,    49,    50,    65,    66,    76,    68,
      69,    67,   109,    58,     0,   146,   151,    52,    70,    71,
      72,    51,    59,    54,    55,    56,    60,   207,    75,    74,
      57,   611,   445,   440,   453,     0,     0,     0,   456,   439,
     438,     0,   508,   511,   537,   509,     0,   537,     0,   537,
     545,     0,     0,   552,    53,   459,   613,   616,   622,   618,
     617,   623,   624,   625,   626,   615,   632,   614,   633,   619,
       0,   780,   620,   627,   629,   628,   660,   634,   636,   637,
     635,   638,   639,   640,   641,   642,   621,   643,   644,   646,
     647,   645,   649,   650,   648,   674,   661,   662,   663,   664,
     651,   652,   653,   655,   654,   656,   657,   658,   659,   665,
     666,   667,   668,   669,   670,   671,   672,   673,   631,   675,
     630,  1033,  1032,  1034,  1035,  1036,  1037,  1038,  1039,  1040,
    1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1031,  1049,
    1050,  1051,  1052,  1053,  1054,  1055,  1056,  1057,   460,  1191,
    1193,  1195,  1196,  1192,  1194,  1197,   461,  1230,  1231,  1232,
    1233,  1234,  1235,     0,     0,   340,     0,     0,     0,     0,
       0,     0,     0,   995,    35,     0,     0,   598,     0,     0,
       0,     0,     0,     0,   454,   507,   481,   210,     0,     0,
       0,   481,     0,   312,   339,   727,     0,   727,   538,     0,
      23,   481,     0,   481,   975,     0,   992,   483,   481,   481,
     481,    32,   484,    81,   444,   958,   481,   952,   105,   481,
      37,   481,     0,   340,     0,     0,    63,     0,     0,   329,
      44,     7,   969,     0,     0,     0,   599,     0,     0,    77,
     340,     0,   989,   522,     0,     0,     0,   296,   295,     0,
       0,   813,     0,     0,   340,     0,     0,   538,     0,   340,
       0,     0,     0,   340,    33,   340,    22,   599,     0,    21,
       0,     0,     0,     0,     0,     0,     0,   398,   340,    45,
     140,     0,     0,     0,     0,     0,     0,     0,     0,   787,
     340,     0,   340,     0,     0,   993,   994,     0,   339,   340,
       0,     0,     0,   599,     0,  1177,  1176,  1181,  1058,   727,
    1183,   727,  1173,  1175,  1059,  1164,  1167,  1170,   727,   727,
     727,  1179,  1172,  1174,   727,   727,   727,   727,  1112,   727,
     727,  1189,  1146,     0,    45,  1199,  1202,  1205,    45,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    45,    45,
    1264,  1239,    45,   612,     4,    20,    20,     0,     0,    45,
       5,     0,     0,     0,     0,     0,    45,    20,     0,     0,
       0,   147,   164,     0,     0,     0,     0,   528,     0,   528,
       0,     0,     0,     0,   528,   222,     6,   486,   537,   537,
     446,   441,     0,   457,   448,   447,   455,    82,   172,     0,
       0,     0,   406,     0,   405,   410,   408,   409,   407,   381,
       0,     0,   351,   382,   354,   384,   383,   355,   400,   402,
     395,   353,   356,   598,   398,   542,   543,     0,   380,   379,
      32,     0,   602,   603,   540,     0,   600,   599,     0,   544,
     599,   564,   547,   546,   600,   550,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,   776,   777,   775,
       0,   773,   763,     0,     0,   435,     0,   323,     0,   524,
     977,   978,   974,    45,   310,   808,   810,   976,    36,    13,
     598,     0,   481,     0,   192,     0,   310,     0,   184,     0,
     709,   707,   843,   930,   931,   807,   804,   805,   482,   516,
     222,   435,   310,   676,   986,   981,   470,   341,     0,     0,
       0,     0,     0,   719,   722,   711,     0,   497,   682,   679,
     680,   451,     0,     0,   500,   987,   442,   443,   458,   452,
     471,   106,   499,    45,   517,     0,   199,     0,   382,     0,
       0,    37,    25,   803,   800,   801,   324,   326,     0,     0,
      45,   970,   971,     0,   700,   698,   686,   683,   684,     0,
       0,     0,    78,     0,    45,   990,   988,     0,     0,   951,
       0,    45,     0,    19,     0,     0,     0,     0,   956,     0,
       0,     0,   497,   523,     0,     0,   934,   961,   599,     0,
     599,   600,   139,    34,    12,   143,   576,     0,   764,     0,
       0,     0,   727,   706,   704,   891,   928,   929,     0,   703,
     701,   962,   399,   514,     0,     0,     0,   912,     0,   924,
     923,   926,   925,     0,   691,     0,   689,   694,     0,     0,
      37,    24,     0,   310,   943,   946,     0,    45,     0,   302,
     298,     0,     0,   577,   310,     0,   527,     0,  1116,  1111,
     527,  1148,  1178,     0,   527,   527,   527,   527,   527,   527,
    1171,   310,    46,  1198,  1207,  1208,     0,     0,    46,  1227,
      45,     0,  1023,  1024,     0,   991,   349,     0,     0,     0,
       0,  1241,  1243,  1244,  1245,     0,     0,  1249,  1251,  1252,
    1253,     0,     0,  1257,     0,     0,  1268,     0,     0,    20,
      43,    38,    42,     0,    40,    17,    46,   310,   132,   134,
     136,   110,     0,     0,    20,   339,   148,   538,   598,   165,
     146,   310,   179,   181,   183,   187,   527,   190,   527,   196,
     198,   200,   209,     0,   213,     0,    45,     0,   449,   424,
       0,   351,   364,   363,   376,   362,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   598,     0,     0,   598,     0,
       0,   398,   404,   396,   512,     0,     0,   515,   570,   571,
     575,     0,   567,     0,   569,     0,   608,     0,     0,     0,
       0,     0,   554,   569,   558,     0,     0,   582,   548,   580,
       0,     0,   351,   353,   551,   586,   585,   553,   677,   310,
     699,   702,   705,   708,   310,   339,     0,   944,     0,    45,
     758,   178,     0,     0,     0,     0,     0,     0,   312,   812,
       0,   529,     0,   475,   479,     0,   469,   598,     0,   194,
     185,     0,   321,     0,   208,     0,   678,   598,     0,   786,
     319,   316,   313,   315,   320,   310,   727,   724,   733,   728,
       0,     0,     0,     0,     0,   725,   711,   727,     0,   790,
       0,   498,   539,     0,     0,     0,    18,   204,     0,     0,
       0,   206,   195,     0,   494,   492,   489,     0,    45,     0,
     329,     0,     0,   332,   330,     0,    45,   972,   381,   920,
     967,     0,     0,   965,     0,   561,     0,    87,    88,    86,
      85,    91,    90,   102,    95,    98,    97,   100,    99,    96,
     101,    94,    92,    89,    93,    83,     0,    84,   197,     0,
       0,     0,     0,     0,     0,   297,     0,   188,   436,     0,
      45,   957,   955,   133,   815,     0,     0,     0,   292,   539,
     180,     0,   579,     0,   578,   287,   287,     0,   759,     0,
     727,   711,   938,     0,     0,   935,   284,   283,    62,   281,
       0,     0,     0,     0,     0,     0,     0,   688,   687,   135,
      14,   182,   945,    45,   948,   947,   146,     0,   103,    47,
       0,     0,   695,     0,   727,   527,     0,  1145,  1115,  1110,
     727,   527,  1147,  1190,   727,   527,   727,   527,   527,   527,
     727,   527,   727,   527,   696,     0,     0,     0,     0,  1219,
       0,     0,  1206,  1210,  1212,  1211,    45,  1201,   851,  1220,
       0,  1204,     0,  1228,  1229,     0,     0,   998,    45,    45,
      45,     0,   390,   391,  1028,     0,     0,     0,     0,     0,
      45,  1236,     0,     0,     0,    45,  1237,  1259,  1261,     0,
       0,    45,  1238,     0,     0,     0,     0,     0,    45,  1267,
      28,    37,     0,     0,    39,     0,    30,   159,   116,   310,
     339,   118,   120,     0,   121,   114,   122,   130,   129,   123,
     124,   125,     0,   112,   115,    26,     0,   310,     0,     0,
     144,   177,     0,     0,   222,   222,     0,   224,   217,   221,
       0,     0,     0,   352,     0,   359,   361,   358,   357,   375,
     377,   371,   365,   504,   368,   366,   369,   367,   370,   372,
     374,   360,   373,   378,   598,   411,   389,     0,   343,     0,
     414,   415,   401,   412,   403,     0,   598,   513,     0,   532,
     530,     0,   598,   566,   573,   574,   572,   601,   610,   605,
     607,   609,   606,   604,   565,   549,     0,     0,     0,   351,
       0,     0,     0,     0,     0,   697,   779,     0,   789,   792,
     782,     0,   791,   785,     0,   783,   784,   781,   774,     0,
     429,     0,     0,   506,     0,     0,     0,     0,   811,   477,
     476,     0,   474,     0,   193,     0,   527,   806,   427,   428,
     432,     0,     0,     0,   314,   317,   176,     0,   598,     0,
       0,     0,     0,     0,   712,   723,   310,   462,   727,   681,
       0,   481,     0,     0,   201,     0,   394,   980,     0,     0,
       0,    16,   802,   327,   337,     0,   333,   335,   331,     0,
       0,     0,     0,     0,     0,     0,   964,   685,   562,    80,
      79,   128,   126,   127,   340,     0,   487,   423,     0,     0,
       0,     0,   191,     0,   520,     0,     0,   727,     0,     0,
      64,   527,   505,   601,   138,     0,   142,    45,     0,   711,
       0,     0,     0,     0,   933,     0,     0,     0,     0,     0,
     913,   915,     0,   692,   690,     0,    45,   950,    45,   949,
     145,   340,     0,   502,     0,  1180,     0,   727,  1182,     0,
     727,     0,     0,   727,     0,   727,     0,   727,     0,   727,
       0,     0,     0,    45,     0,     0,     0,  1209,     0,  1200,
    1203,  1002,  1000,  1001,    45,   997,     0,     0,     0,   350,
     598,   598,     0,  1027,  1030,     0,     0,    45,  1242,     0,
       0,     0,  1250,     0,     0,     0,  1258,    45,     0,     0,
       0,    45,  1269,    15,    29,    41,     0,   173,   160,   117,
       0,    45,     0,    45,    27,   159,   539,   539,   169,   172,
     168,     0,   186,   189,   214,     0,     0,     0,   247,   245,
     252,   249,   263,   256,   261,     0,     0,   215,   238,   250,
     242,   253,   243,   258,   244,     0,   237,     0,   232,   229,
     218,   219,     0,     0,   425,   351,     0,   387,   598,   347,
     344,   345,     0,   398,     0,   534,   533,     0,     0,   581,
     352,     0,     0,     0,   351,   588,   351,   592,   351,   590,
     310,     0,   598,   518,     0,     0,   979,     0,   311,   478,
     480,   172,   322,     0,   598,   519,     0,   983,   598,   982,
     318,   320,   726,     0,     0,     0,   736,     0,     0,     0,
       0,   710,   464,   481,   501,     0,   203,   202,   381,   493,
     490,   488,     0,   491,     0,   328,     0,     0,     0,     0,
       0,     0,   966,     0,  1012,     0,     0,   422,   417,   953,
     954,   721,   310,   960,   437,   816,   818,   824,   294,   293,
       0,   287,     0,     0,   289,   288,     0,   760,   761,   713,
       0,   942,   941,     0,   939,     0,   936,   282,     0,  1018,
    1007,     0,  1005,  1008,   755,     0,     0,   927,   919,   693,
       0,     0,     0,     0,     0,   300,     0,   299,   307,     0,
    1189,     0,  1189,  1189,  1125,     0,  1119,  1121,  1122,  1120,
     727,  1124,  1123,     0,  1189,   727,  1143,  1142,     0,     0,
    1186,  1185,     0,     0,  1189,     0,  1189,     0,   727,  1064,
    1068,  1069,  1070,  1066,  1067,  1071,  1072,  1065,     0,  1153,
    1157,  1158,  1159,  1155,  1156,  1160,  1161,  1154,  1163,  1162,
     727,     0,  1106,  1108,  1109,  1107,   727,     0,  1136,  1137,
     727,     0,     0,     0,     0,     0,     0,  1221,     0,     0,
     852,   999,     0,  1025,     0,   598,     0,  1029,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1265,     0,     0,
       0,  1275,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   794,     0,   111,     0,   173,     0,   146,     0,   171,
     170,   267,   253,   266,     0,   255,   260,   254,   259,     0,
       0,     0,     0,     0,   222,   212,   223,   241,     0,   222,
     234,   235,     0,     0,     0,     0,   278,   223,   279,     0,
       0,   227,   268,   273,   276,   229,   220,     0,   503,     0,
     413,   385,   388,     0,   346,     0,   531,   568,   569,     0,
       0,   351,     0,     0,     0,   778,   772,   788,     0,     0,
       0,   525,     0,   340,   526,     0,   985,     0,     0,     0,
     740,     0,   738,   735,   730,   734,   732,     0,    45,     0,
     463,   450,   205,   334,   336,     0,     0,     0,   968,   963,
     131,     0,  1011,   421,     0,     0,   416,   959,     0,    45,
     814,   825,   826,   831,   835,   828,   836,   837,   838,   832,
     834,   833,   829,   830,     0,     0,     0,     0,   285,     0,
       0,     0,     0,   937,   932,   472,     0,  1004,   727,   914,
       0,     0,   889,   104,   306,   301,   303,   305,     0,     0,
       0,  1074,   727,  1075,  1076,    45,  1117,   727,  1144,  1140,
     727,  1189,     0,  1073,    45,  1077,     0,  1078,     0,  1062,
     727,  1151,   727,  1104,   727,  1134,   727,  1213,  1214,  1215,
    1223,  1224,    45,  1218,  1216,  1217,     0,     0,     0,   393,
    1248,  1247,   901,   902,   903,   900,   905,   899,   906,   898,
     897,   896,   904,   892,     0,     0,    45,  1246,  1255,  1256,
    1254,  1262,  1260,     0,  1263,  1277,  1278,    45,  1270,  1271,
    1272,  1273,  1279,  1280,     0,    31,   175,   174,     0,     0,
     119,   113,   107,     0,     0,   161,   598,   166,     0,   248,
     246,   264,   257,   262,   216,   222,   598,     0,   240,   236,
     223,     0,   233,     0,   270,   269,     0,   225,   229,     0,
       0,     0,     0,     0,   230,     0,   426,   386,   348,   397,
       0,   583,   595,   597,   596,     0,   430,     0,     0,   809,
       0,   433,     0,   984,   756,   729,     0,     0,    45,     0,
       0,     0,   844,   973,   845,  1017,     0,  1014,  1016,   420,
     419,     0,     0,   817,     0,   827,     0,   288,     0,     0,
     765,   762,   719,   714,   715,   717,   718,   940,  1006,  1010,
       0,     0,   381,     0,     0,     0,     0,   309,   308,   521,
       0,     0,     0,  1118,  1141,     0,  1188,  1187,     0,     0,
       0,  1063,  1152,  1105,  1135,  1222,     0,     0,   392,     0,
       0,     0,  1266,  1276,     0,     0,     0,   795,   162,   163,
       0,     0,   239,   598,   241,     0,   280,   228,     0,   272,
     271,   274,   275,   277,   473,     0,   770,   769,   771,     0,
     767,   431,     0,   996,   434,     0,   741,   739,     0,   731,
       0,     0,     0,  1013,   418,     0,     0,     0,     0,     0,
     910,     0,     0,     0,     0,     0,     0,     0,   286,   291,
     290,     0,     0,     0,  1003,   916,   917,     0,   842,   890,
     890,   304,  1090,  1089,  1088,  1095,  1096,  1097,  1094,  1091,
    1093,  1092,  1101,  1098,  1099,  1100,     0,  1085,  1129,  1128,
    1130,  1131,     0,  1190,  1080,  1082,  1081,     0,  1084,  1083,
       0,  1026,     0,     0,   893,  1274,   796,     0,   172,   265,
       0,     0,   227,   226,     0,     0,   766,   510,     0,     0,
       0,   466,  1015,   823,   822,     0,   820,   727,   859,     0,
       0,     0,     0,     0,   908,   909,     0,     0,     0,     0,
       0,   716,   921,  1009,    45,     0,     0,     0,     0,     0,
    1127,  1184,  1079,    45,   894,     0,     0,     0,   251,   231,
     495,   768,   757,   744,   737,   742,     0,     0,   819,   864,
     860,     0,     0,     0,     0,     0,     0,     0,     0,   848,
       0,   854,     0,   467,   720,     0,     0,   841,    45,    45,
     887,  1087,  1086,     0,     0,     0,   354,   799,   793,   797,
     167,     0,     0,   465,   821,     0,     0,     0,     0,   857,
     846,     0,   840,     0,   907,   858,     0,   847,     0,   853,
       0,   922,     0,     0,     0,  1126,     0,   895,     0,   496,
       0,   747,     0,   745,   748,   862,   863,     0,   865,   867,
       0,     0,     0,   849,   855,   468,   918,   888,   886,     0,
     798,   750,   751,     0,   743,     0,   861,     0,   856,   839,
       0,     0,     0,     0,   749,   752,   746,   866,     0,     0,
     870,   911,   850,  1020,   753,     0,     0,     0,   868,    45,
    1019,   754,   872,   871,    45,     0,     0,     0,   873,   878,
     880,   881,  1021,  1022,     0,     0,     0,    45,   869,    45,
      45,   598,   884,   883,   882,   874,     0,   876,   877,     0,
     879,     0,    45,   885,   875
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   208,   384,   209,   840,   751,   210,
     915,   619,   804,   689,   569,   913,   914,   441,   916,  1232,
    1522,   211,   212,   620,  1136,  1137,   213,   214,   215,   579,
    1302,  1303,  1140,  1304,   216,   217,   218,   219,  1165,   220,
     221,  1166,   222,   582,   223,   224,   225,   226,  1587,  1588,
     930,  1599,   949,  1870,   227,   228,   229,   230,   231,   232,
     785,  1176,  1177,   233,   234,   235,   746,  1088,  1089,   236,
     237,   710,   453,   942,   943,  1615,   944,   945,  1908,  1625,
    1630,  1631,  1909,  1910,  1626,  1627,  1628,  1617,  1618,  1619,
    1620,  1882,  1622,  1623,  1624,  1884,  2134,  1912,  1913,  1914,
    1178,  1179,  1494,  1495,  1998,  1735,  1157,  1158,   238,   458,
     239,   850,  2015,  2016,  1767,  2017,  1039,   718,   719,  1062,
    1063,  1051,  1052,   240,   756,   757,   758,   759,  1104,  1455,
    1456,  1457,   397,   374,   404,  1347,  1639,  1348,   885,  1011,
     622,   641,   623,   624,   625,   626,  1254,  1091,   982,  1922,
     823,   627,   628,   629,   630,   631,  1352,  1641,   632,  1322,
    1919,  1420,  1401,  1421,  1032,  1149,   241,   242,  1960,   243,
     244,   692,  1044,  1045,   709,   423,   245,   246,   247,   248,
    1095,  1096,  1449,  1929,  1930,  1082,   249,   250,   251,   252,
    1214,   253,   985,  1360,   254,   376,   727,  1438,   255,   256,
     257,   258,   259,   260,   652,   644,   991,   992,   993,   261,
     262,   263,  1008,  1009,  1014,  1015,  1016,  1349,   769,   645,
     801,   564,   264,   265,   266,   713,   267,   729,   730,   268,
     767,   768,   269,   499,   835,   836,   838,   270,   271,   765,
     272,   820,   273,   814,   274,   701,  1079,   275,   276,  2183,
    2184,  2185,  2186,  1722,  1076,   407,   721,   722,  1075,  1687,
    1750,  1951,  1952,  2384,  2385,  2452,  2453,  2472,  2484,  2485,
    1755,  1949,   277,   278,  1737,   673,   809,   810,  1937,  2249,
    2250,  1938,   670,   671,   279,   280,   281,   282,  2098,  2099,
    2418,  2419,   283,   754,   755,   284,   706,   707,   285,   685,
     686,   286,   287,  1155,  1727,  2173,  2345,  2346,  1980,  1981,
    1982,  1983,  1984,   703,  1985,  1986,  1987,  2400,  1239,  1988,
    2402,  1989,  1990,  1991,  2348,  2427,  2457,  2458,  2489,  2490,
    2507,  2508,  2509,  2510,  2511,  2522,  1992,  2195,  2366,   816,
    1851,  2073,  2074,  2075,  1993,   828,  1509,  1510,  2010,  1172,
    2363,   288,   289,   290,   291,   292,   293,   294,   295,   797,
    1174,  1175,  1743,  1744,   296,   844,   297,   780,   298,   781,
     299,  1152,   300,   301,   302,   303,   304,  1112,  1113,   305,
     762,   306,   307,   308,   681,   682,   309,   310,  1423,  1677,
     715,   311,   312,   776,   313,   314,   315,   316,   317,   318,
     319,  1246,  1247,   320,  1182,  1751,  1752,  2284,   321,  1715,
    2166,  2167,  1753,   322,  2500,   323,   324,   325,   326,  1255,
     327,   328,   329,   330,   331,   332,  1215,  1798,   862,  1776,
    1777,  1778,  1802,  1803,  1804,  2317,  1805,  1806,  1779,  2201,
    2412,  2306,   333,  1221,  1826,   334,   335,   336,   337,  1205,
    1780,  1781,  1782,  2312,   338,  1223,  1830,   339,  1211,  1785,
    1786,  1787,   340,   341,   342,  1217,  1820,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,  1791,  1792,   863,  1531,   358,   359,   360,   361,
     362,   873,   874,   875,  1233,  1234,  1235,  1240,  1836,  1837,
     363,   364,   365,   879,   366,   367,   368,   369,   370,   371,
     890,   891,   892,   893,   894,   896,   897,   898,   899,   900,
     902,   903,   561,  1858,   372,   905,   906,  1860,  1861,  1866
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -2192
static const yytype_int16 yypact[] =
{
   -2192,    98, -2192, -2192, -2192, -2192,    31,  4976, -2192, -2192,
   -2192,   149, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,   715, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192,    84, -2192, -2192,   508,   164, -2192, -2192, -2192,    84,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,   106,   106, -2192, -2192, -2192, -2192, -2192,   106,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
     207, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,   106, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192,   275, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
     417,   449, -2192, -2192, -2192, -2192, -2192,    84, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,    84, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,   448,   457,   475,   106, -2192,   491,   260,  1725,
     553,   260, -2192, -2192, -2192,   569,   585,   638,   641, -2192,
   -2192, -2192,   593,   659,   106, -2192, -2192,   663,   700,   711,
     800,   611,   269,   804,   851,   887, -2192,   178, -2192, -2192,
   -2192,   260, -2192, -2192, -2192,   902,    43,  1758,  2186, -2192,
   -2192,  2351, -2192,   898, -2192, -2192,  2159, -2192,   905, -2192,
   -2192,  1764,   905,   909, -2192, -2192,   926, -2192, -2192, -2192,
     946,   952,   956,   967,   976, -2192, -2192, -2192, -2192,   982,
     831, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,   997, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192,   152,   106,  1013,  1001,  1027,   896,   106,
     106,   216,   106, -2192,   106,   106,  1035, -2192,   445,  1039,
     106,   106,   106,   106, -2192, -2192,   106, -2192,  1054,   106,
     928,   106,  1100, -2192, -2192, -2192,   106, -2192,  1095,   106,
   -2192,   106,  1097,   165, -2192,   928, -2192,   106,   106,   106,
     106, -2192, -2192, -2192, -2192, -2192,   106, -2192,   106,   106,
     553,   106,  1109,  1013,   106,  1118, -2192,   106,   106, -2192,
   -2192, -2192,  1113,  1123,   106,   106, -2192,  1149,  1158,   106,
    1013,  1170,  2351, -2192,  1177,  1207,   106, -2192,  1127,   106,
    1139, -2192,  1209,   106,  1013,  1235,  1237, -2192,   896,  1013,
     106,   106,  2316,    69,   106,    78, -2192, -2192,   181, -2192,
     185,   106,   106,   106,  1243,   106,   106,  2351,    96, -2192,
   -2192,  1287,   106,   106,   106,   106,   106,  2479,   106, -2192,
    1013,   106,  1013,   106,   106, -2192, -2192,   106, -2192,  1013,
     106,  1315,  1336, -2192,   106, -2192, -2192,  1341, -2192, -2192,
    1351, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192,  1359, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192,   106, -2192, -2192,  1362,  1368, -2192,  1371,
    2351,  2351,  2351,  2351,  2351,  1394,  1405, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192,  1046,   153, -2192,
   -2192,   106,   106,   106,   106,  1212, -2192, -2192,  1119,   106,
     106, -2192,   671,   106,   106,   106,   106,   106,   319,   106,
    1139,   106,   106,  1109, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,  1016, -2192, -2192, -2192, -2192, -2192, -2192,  2351,
    2351,  2351, -2192,  2351, -2192, -2192, -2192, -2192, -2192, -2192,
    2351,  2820, -2192,   174,  1290, -2192,  1423, -2192,  1023,  1080,
    1431, -2192, -2192,  1260,  2351, -2192, -2192,  1307, -2192, -2192,
    1376,  2445,  1290, -2192, -2192,   910,    11, -2192,  1307, -2192,
   -2192, -2192,  1415,   191,    94,  2774,  2774,   106,   106,   106,
     106,   106,   106,   106,  1342, -2192,   106, -2192, -2192, -2192,
     664, -2192, -2192,  1452,   106, -2192,  2351, -2192,  1229,   613,
   -2192,  1456, -2192, -2192,  1477,  1487, -2192, -2192, -2192, -2192,
   -2192,  2515,   106,  1483, -2192,   106,  1477,   106, -2192,   896,
   -2192, -2192, -2192, -2192, -2192, -2192,  1491, -2192, -2192, -2192,
   -2192, -2192,  1477, -2192, -2192,  1486, -2192, -2192,   688,  1089,
     106,   763,    90, -2192,  1494,  1331,  2351,  1361, -2192,  1507,
   -2192, -2192,  2351,  2351, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192,   106, -2192,   106,  1501,   299,
     106,   553, -2192, -2192,  1513, -2192,  1518, -2192,  1514,  1358,
   -2192,  1522, -2192,   106, -2192, -2192, -2192,  1530, -2192,   905,
    1516,  3004, -2192,   106, -2192,  5662, -2192,   106,  2351, -2192,
    1525, -2192,   106, -2192,   106,   106,   106,  1290,   627,   106,
     106,   106,  1361, -2192,   106,   215, -2192, -2192, -2192,  2445,
     910, -2192, -2192, -2192, -2192, -2192, -2192,   152, -2192,  1452,
    1544,  1494, -2192, -2192, -2192, -2192, -2192, -2192,   106, -2192,
   -2192, -2192,  5662, -2192,   445,  1490,   106, -2192,  1538, -2192,
   -2192, -2192, -2192,  1545,  3109,   786, -2192, -2192,   275,   106,
     553, -2192,   106,  1477, -2192,  1554,  1547, -2192,   106, -2192,
    1557,  2351,  2351, -2192,  1477,   106,   196,   106,  1279,  1279,
     203,  1279, -2192,  1555,   221,   246,   272,   280,   301,   372,
   -2192,  1477,   783, -2192,  1561, -2192,   124,   182,  1257, -2192,
   -2192,  3172,  5662,  3222,  3531,  1564,  5662,   106,   106,   470,
     798, -2192, -2192, -2192, -2192,    64,   827, -2192, -2192, -2192,
   -2192,  1120,   828, -2192,   521,   829, -2192,   106,   106, -2192,
   -2192, -2192, -2192,   832, -2192, -2192,  1360,  1477, -2192, -2192,
   -2192, -2192,  1401,   106, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192,  1477, -2192, -2192, -2192, -2192,  1567, -2192,  1567, -2192,
   -2192, -2192, -2192,   458, -2192,   241, -2192,  1563, -2192, -2192,
    3580,  1573,  1574,  1574,  1402, -2192,  2351,  2351,  2351,  2351,
    2351,  2351,  2351,  2351,  2351,  2351,  2351,  2351,  2351,  2351,
    2351,  2351,  2351,  2351,  2351, -2192,  1521,  1453,  1565,    73,
     526,  2351, -2192, -2192, -2192,   856,  1323, -2192, -2192, -2192,
   -2192,   880, -2192,  1469,  1174,  2351,  1578,  2445,  2445,  2445,
    2445,  2445, -2192,  1502, -2192,   191,   191,  1290,  1582, -2192,
    2774,  5662,   134,   142, -2192,  1585,  1586, -2192, -2192,  1477,
   -2192, -2192, -2192, -2192,  1477, -2192,   595, -2192,   152, -2192,
   -2192, -2192,   106,  3694,   106,  1590,  2351,  1539, -2192, -2192,
     106, -2192,  2351,  3728, -2192,   882, -2192, -2192,  1560, -2192,
   -2192,   883, -2192,   106, -2192,   106, -2192, -2192,  1089, -2192,
   -2192, -2192, -2192, -2192,  3763,  1477, -2192, -2192, -2192,  1595,
    1596,  1598,  1599,  1600,  1601, -2192,  1331, -2192,   106, -2192,
    3811, -2192, -2192,   106,  3845,  3890, -2192,  1606,   924,  1614,
    1431, -2192, -2192,   106, -2192,  1622, -2192,  1607, -2192,   106,
   -2192,  1506,   589, -2192, -2192,   383, -2192, -2192,  1631, -2192,
    1621,  1641,   927, -2192,   106,  2774,  1630, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,  1632, -2192, -2192,   451,
    1633,  1637,  3927,  2585,   -53, -2192,  1613, -2192, -2192,   936,
   -2192, -2192, -2192, -2192, -2192,   941,  1634,   944, -2192, -2192,
   -2192,  2351, -2192,  1603, -2192, -2192, -2192,   945, -2192,  1650,
   -2192,  1331,  1643,  1652,   966, -2192, -2192, -2192,  1654, -2192,
    1649,  1651,  1642,   106,  2351,  2351,  2479, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192,  1659,  1663, -2192,   592, -2192, -2192,
    3961,  4036, -2192,  1653, -2192,   459,  1655, -2192, -2192, -2192,
   -2192,   463, -2192, -2192, -2192,   469, -2192,   471,   479,   481,
   -2192,   528, -2192,   548, -2192,  1657,  1658,  1660,  1662, -2192,
    1664,  1665, -2192, -2192, -2192, -2192, -2192, -2192,  1290,  1675,
    1667, -2192,  1669, -2192, -2192,   -46,   970, -2192, -2192, -2192,
   -2192,  2351,   747,   801, -2192,   972,   977,  1670,  1671,  1677,
   -2192, -2192,  1679,  1681,  1682, -2192, -2192, -2192,  1684,  1685,
    1686, -2192, -2192,  1687,  1696,  1699,  1700,  1701, -2192, -2192,
   -2192,   553,   106,   156, -2192,  1702, -2192,  1713, -2192,  1477,
   -2192, -2192, -2192,  1707, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,   987, -2192, -2192, -2192,   106,  1477,   126,  1348,
   -2192, -2192,   106,   106, -2192,  1187,   241, -2192,  1708, -2192,
    1666,  2351,  2774, -2192,  2351,  1574,  1574,   698,   698,  1402,
     697,  2029,  2241,  5662,  2241,  2241,  2241,  2241,  2241,  2029,
    3276,  1574,  3276,  5693,  1565, -2192, -2192,  1704,  1676,  2395,
   -2192, -2192, -2192, -2192, -2192,  1719, -2192, -2192,   896,  5662,
   -2192,  2351, -2192, -2192, -2192, -2192,  5662,   510,  5662,  1578,
    1578,   870,  1578,   764, -2192,  1582,  1722,   191,  4085,  1723,
    1727,  1728,  2774,  2774,  2774, -2192, -2192,   106,  1712, -2192,
   -2192,  1724,  1494, -2192,   275, -2192, -2192, -2192, -2192,  1492,
   -2192,   978,   896, -2192,   896,  1007,  1731,  1009, -2192,  5662,
    2351,  2515, -2192,  1019, -2192,   896,  1567, -2192,   858,   877,
   -2192,  1031,  1579,  1038, -2192,  1629, -2192,    90, -2192,  1734,
     106,   106,  2351,   106, -2192, -2192,  1477, -2192, -2192, -2192,
    1511,   106,  2351,   106, -2192,   106, -2192,  1290,  2351,  1732,
    2585, -2192, -2192, -2192, -2192,  1043, -2192,  1736, -2192,  1739,
    1740,  1741,  1549,  2351,   106,   106, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192,  1013,   106, -2192,  2674,  3060,  1738,
     106,   106, -2192,   106, -2192,   -25,   106, -2192,  2351,   106,
   -2192,  1567,  5662, -2192,  1752,   455,  1752, -2192,   106,  1331,
    1754,  2712,   106,   106, -2192,   445,  2351,   686,  2351,  1045,
   -2192,  1747,  1053,  5662, -2192,    59, -2192, -2192, -2192, -2192,
   -2192,  1013,   115, -2192,   106, -2192,   661, -2192, -2192,   317,
   -2192,   154,   852, -2192,   759, -2192,   405, -2192,   -31, -2192,
     106,   106,   106, -2192,   106,   106,   783, -2192,   106, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,  1440,  1448,  1441,  5662,
   -2192,  1565,   106, -2192, -2192,   106,   106, -2192, -2192,   106,
     106,   106, -2192,   106,   106,   106, -2192, -2192,   106,   106,
    2351, -2192, -2192, -2192, -2192, -2192,   106,   844, -2192, -2192,
    1756, -2192,  1767, -2192, -2192,  1713, -2192, -2192, -2192, -2192,
    5662,  1904, -2192, -2192, -2192,   117,    85,    85,  1531,  1541,
   -2192, -2192,  1546,  1548,  1550,   586,   106, -2192, -2192, -2192,
   -2192,  1771, -2192, -2192, -2192,  1708, -2192,  1776, -2192,   776,
    1770, -2192,  1775,  4116, -2192,  1765,  1774,  1431, -2192, -2192,
    4153, -2192,  2351,  2351,  1323, -2192,  5662,  1307,   191, -2192,
     143,  2774,  2774,  2774,   148, -2192,   197, -2192,   199, -2192,
    1477,   106, -2192, -2192,  1789,  1060, -2192,  1791, -2192,  5662,
   -2192, -2192, -2192,  2351, -2192, -2192,  2351, -2192, -2192, -2192,
   -2192,  5662, -2192,  1579,  2351,  1778, -2192,  1780,  1781,  4187,
    1797, -2192,   144,   106, -2192,  1062, -2192, -2192,  1782,  5662,
   -2192, -2192,  4153, -2192,  1506, -2192,  1506,   106,   106,   106,
    1063,  1087, -2192,   106,  1794,  1792,  2351,  4239,  2743, -2192,
   -2192, -2192,  1477,  1290, -2192, -2192,  1639,  1802,  5662, -2192,
     106, -2192,  1799,  1803, -2192, -2192,  1562,  1812, -2192, -2192,
    1814, -2192,  5662,  1105, -2192,  1106, -2192, -2192,  4312, -2192,
   -2192,  1107, -2192, -2192,  5662,  1801,   106, -2192, -2192, -2192,
    1808,  1810,  1618,  1761,   106,   106,  1811,  1825, -2192,   577,
   -2192,  1819, -2192, -2192, -2192,  1821, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192,   661, -2192, -2192, -2192, -2192,   317,   106,
   -2192, -2192,  1110,  1823, -2192,  1826, -2192,  1827, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,   852, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192,   759, -2192, -2192, -2192, -2192, -2192,   405, -2192, -2192,
   -2192,   -31,  1822,  1824,  1833,   813,  1111, -2192,  1834,  1836,
    1290, -2192,  1829, -2192,  1832,  1565,  1837, -2192,  1128,  1131,
    1133,  1142,  1146,  1157,  1161,  1163,  1180, -2192,  1185,   228,
    1188, -2192,  1204,  1205,  4346,   744,  1840,  1838,  2351,  2351,
   -2192, -2192,  1839, -2192,  1504,   844,  2008, -2192,  1219, -2192,
    5662, -2192, -2192, -2192,  1853, -2192, -2192, -2192, -2192,    73,
      73,    73,    73,    73,  1187, -2192,  1849,  1835,  1851,  1187,
    1770, -2192,   241,   776,   155,   155, -2192, -2192, -2192,  1226,
    1861,  1443,   401, -2192,  1862,   776, -2192,  2351, -2192,  1850,
   -2192,  1431, -2192,  2395,  5662,  1855, -2192, -2192,   910,  1846,
    1856,  1228,  1857,  1859,  1864, -2192, -2192, -2192,  1867,    49,
     896, -2192,   106,  1013,  5662,    49,  5662,  1579,  2351,  1865,
    4380,  1240, -2192, -2192, -2192, -2192, -2192,  2351, -2192,  1868,
   -2192, -2192, -2192, -2192, -2192,  1249,  1251,  1254, -2192, -2192,
   -2192,   775, -2192,  5662,  2351,  2351,  4417, -2192,   106, -2192,
   -2192,  1802, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192,  1863,   455,  1866,  3004, -2192,   106,
     106,   106,  2712, -2192, -2192, -2192,   686, -2192, -2192, -2192,
    2441,   106, -2192, -2192,  1811,  1883, -2192, -2192,   106,   106,
    2351, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,   154, -2192, -2192, -2192,  2351, -2192,  2351, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,   106,   106,  1873,   908,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192,  1881,  1884, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192,   106, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192,  2351, -2192,  5662,  5662,  1259,  1891,
   -2192, -2192, -2192,  1880,  4454, -2192, -2192, -2192,   117, -2192,
   -2192, -2192, -2192, -2192, -2192,  1187, -2192,   106, -2192, -2192,
    1887,  1877, -2192,   868,   401,   401,   776, -2192,   776,   155,
     155,   155,   155,   155,  1145,  4485, -2192, -2192, -2192, -2192,
    2351, -2192, -2192, -2192, -2192,  1540, -2192,   106,  1907,  1487,
     106, -2192,   106, -2192,  4531, -2192,  2351,  2351, -2192,  4584,
    1668,  2351, -2192, -2192, -2192, -2192,  1266, -2192, -2192,  5662,
    5662,  2351,  1897, -2192,   951, -2192,  2351, -2192,  1895,  1902,
   -2192, -2192,  1912,  1924, -2192, -2192, -2192, -2192, -2192,  1804,
    1914,  1275,  1930,  1932,  1276,   875,   106, -2192, -2192,  5662,
     841,  1920,   386, -2192, -2192,  1908, -2192, -2192,   -36,  4615,
    4651, -2192, -2192, -2192, -2192, -2192,  1277,  1929,  1008,   106,
     106,  1133, -2192, -2192,  4729,  1944,  1945, -2192, -2192, -2192,
    1348,  1935, -2192,  1565, -2192,   776, -2192,  1145,  1936,   401,
     401, -2192, -2192, -2192, -2192,  4975, -2192,  4153, -2192,  1278,
   -2192, -2192,   896,  1675, -2192,  1579,  5662, -2192,  1698, -2192,
    1946,  5309,   775, -2192,  5662,  2146,  1947,  1948,  1949,  1955,
    1956,  1959,   106,   106,  1961,  1962,  1964,  5349, -2192, -2192,
   -2192,  2351,   106,   106, -2192, -2192,  1965,   106, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,  1953, -2192, -2192, -2192,
   -2192, -2192,  1292, -2192, -2192, -2192, -2192,  1960, -2192, -2192,
    1975, -2192,   615,  1977, -2192, -2192, -2192,  1979, -2192, -2192,
    1966,  1299,  1145, -2192,  2351,  1540, -2192, -2192,  2351,   106,
    2351, -2192, -2192, -2192,  5662,  1300, -2192, -2192,  1947,   106,
     106,   106,   106,   106, -2192, -2192,  2351,  2351,   106,  2351,
    1306, -2192, -2192,  1980, -2192,  1310,  1982,  1311,   106,  2351,
   -2192, -2192, -2192, -2192, -2192,  2351,   106,  1970, -2192, -2192,
    5380, -2192,  5662, -2192, -2192,  1978,  5411,  2146, -2192,    60,
   -2192,  1985,  1333,  1334,  1987,  1339,  1983,  1340,  5442,  5473,
    1974, -2192,  1377,  5504, -2192,   106,  1921, -2192, -2192, -2192,
   -2192,  1675, -2192,  5535,  1672,  5566,   689, -2192,  1992, -2192,
   -2192,  2351,  1890, -2192, -2192,  1996,  1997,   106,   106, -2192,
   -2192,   106, -2192,  2479, -2192, -2192,  2351, -2192,   106, -2192,
    2351, -2192,  1984,  1384,  1387, -2192,  1993, -2192,   106,  5662,
     106,  5662,  1389, -2192, -2192, -2192, -2192,  1392, -2192,  1994,
    1393,  1396,  1408,  5597, -2192,  5662, -2192, -2192, -2192,  2351,
   -2192, -2192,  1995,  1890, -2192,   106, -2192,  2351, -2192, -2192,
    1989,  2351,  1414,  2351,  1998, -2192, -2192, -2192,  5631,  1433,
   -2192, -2192,  5662,  2009, -2192,  2351,  2351,  2351,  2001, -2192,
   -2192, -2192,  5662, -2192, -2192,   -44,    86,  1434, -2192,  2013,
    2014, -2192, -2192, -2192,  2012,  2012,  2012, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,   509,  2021, -2192,  1901,
   -2192,  1436, -2192, -2192, -2192
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2192, -2192, -2192, -2192, -2192,     5,  1809,  1122, -2192, -2192,
    -672,   -52, -2192, -2192,  -379, -2192,   749, -2192,   -50,  -691,
   -2192, -2192, -2192,  2334,    39, -2192, -2192, -2192, -2192, -2192,
   -2192,   166,   450,   846, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,  -178,  -900, -2192, -2192, -2192,   948,   460,  1474,
   -2192,  -168, -1547,   188, -2192, -2192, -2192, -2192, -2192, -2192,
    1478,  -245,   -24, -2192, -2192, -2192,  1476, -2192,  -370, -2192,
   -2192, -2192, -2192,  1363, -2192, -2192,   756, -1274, -1550,  1126,
     461, -1499,  -160,   -45,  1137, -2192,   183,   190, -1807, -2192,
   -1551, -1225, -1549,  -462, -2192,   -21, -1572, -1316,  -855, -2192,
   -2192,   583,   923,   359,   -85,    99,   530,   604, -2192, -2192,
   -2192, -2192, -2192,  -100, -2192, -1453,  -407,  1059, -2192,  1040,
     674,   699,  -377, -2192, -2192,  1002, -2192, -2192, -2192, -2192,
     397,   398,  2031,  2865,  -363, -1296,   184,  -412, -1018,  1155,
    -573,  -625,  1885,  -172,  1647,  -863, -1011, -2192, -2192,  -615,
    -608,  -223, -2192,  -921, -2192,  -562,  -951, -1127, -2192, -2192,
   -2192,   186, -2192, -2192,  1419, -2192, -2192,  1886, -2192,  1888,
   -2192, -2192,   722, -2192,  -376,    33, -2192, -2192,  1889,  1892,
   -2192,   691, -2192,  -723,  -307,  1350, -2192,   969, -2192, -2192,
    -209, -2192,  1093,   501, -2192,  4777,  -422, -1097, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192,  -197, -2192,   499,  -926, -2192,
   -2192, -2192,   305, -1298,  -622,  1143,  -899,  -373,  -287,  -453,
     500,   263, -2192, -2192, -2192,  1495, -2192, -2192,  1064, -2192,
   -2192,  1041, -2192,  1316, -1936,   963, -2192, -2192, -2192,  1499,
   -2192,  1509, -2192,  1498, -2192,  1505,  -998, -2192, -2192, -2192,
    -116,  -235, -2192, -2192, -2192,  -400, -2192,  -298,   743,  -346,
     742, -2192,    15, -2192, -2192, -2192,  -296, -2192, -2192, -2192,
   -1651, -2192, -2192, -2192, -2192, -2192, -1435,  -533,   180, -2192,
    -154, -2192,  1378,  1156, -2192, -2192,  1162, -2192, -2192, -2192,
   -2192,  -261, -2192, -2192,  1090, -2192, -2192,  1140, -2192,   248,
    1152, -2192, -2192,  -815, -2192, -2191, -2192,  -193, -2192, -2192,
     217, -2192,  -768,  -384,  -367, -2192, -2192, -2192, -1526, -2192,
   -2192, -2192, -2192, -2192,  -149, -2192, -2192,  -275, -2192,  -295,
   -2192,  -316, -2192,  -315, -1878, -1051,  -759, -2192,   -84,  -476,
    -928, -1975, -2192, -2192, -2192,  -490, -1522,   452, -2192,  -724,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,  -484,
   -1470,   702, -2192,   205, -2192,  1551, -2192,  1710, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -1455,   746, -2192,
    1451, -2192, -2192, -2192, -2192,  1842, -2192, -2192, -2192,   268,
    1807, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,   662, -2192, -2192, -2192,   212, -2192, -2192, -2192,
   -2192,   -43, -1904, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192,   624,   418,  -528, -1419,
   -1418, -1335, -1446, -1437, -1427, -2192, -1426, -1411, -1235, -2192,
   -2192, -2192, -2192, -2192,   400, -2192, -2192, -2192, -2192, -2192,
     442, -1406, -1405, -2192, -2192, -2192,   402, -2192, -2192,   440,
   -2192,    97, -2192, -2192, -2192, -2192,   408, -2192, -2192, -2192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192, -2192,   204, -2192,   206,   -73, -2192, -2192, -2192, -2192,
   -2192, -2192, -2192,  1005, -2192,  1364, -2192,  -742, -2192,   192,
   -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192, -2192,
   -2192,   983, -2192, -2192, -2192, -2192,   980, -2192, -2192, -2192,
   -2192,   985, -2192, -2192, -2192, -2192,   971, -2192,   161, -2192
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1190
static const yytype_int16 yytable[] =
{
     410,   678,   821,   829,   830,   831,   832,   817,   704,  1711,
     422,   422,   674,   870,   693,   983,  1479,   430,  1405,   800,
    1001,  1400,   588,   590,  1253,   716,   987,  1097,   595,  1354,
    1310,   567,  1745,   643,  1017,   731,   951,   734,   643,  1110,
    1849,  1616,   737,   738,   739,   792,   457,  1852,  1636,  1854,
     740,   743,  1878,   742,  1881,   744,  1883,  1911,  1351,  1351,
    1361,   649,  1491,  1738,   653,   655,  1897,  2168,   476,  1768,
     747,  1086,   479,  1256,  2191,   761,   402,  1194,  1434,  1649,
     812,   437,  1012,  1012,   642,   402,  1195,   773,  1812,   642,
    1621,   793,  2118,  1013,  1013,  1068,   424,  1813,     2,     3,
    1853,   789,  -563,   402,   459,  1262,   794,  1814,  1815,   725,
     802,  1381,   805,  1799,  1800,  1809,  1810,  1822,  1823,  1828,
    1829,   474,  1480,  1816,  1943,   824,  1901,  -541,  1818,  1819,
    1760,  1916,    46,  1606,  1607,  1242,  1551,   839,  2512,   842,
    1030,  1596,  1382,   697,  1459,  1237,   848,     8,  1069,   501,
    -593,  -594,  1958,   560,  -584,  2314,  -587,   667,   910,   668,
    1770,   910,  -593,  -594,   373,    74,  1512,  2401,  -587,  1253,
    1903,   724,   581,  1500,   911,  1001,  1070,  1612,   421,   405,
     733,  1965,  1966,  1967,   994,  -137,   594,  1243,   996,   975,
     806,  1789,  1419,  -527,  -141,  1003,   807,  1801,    96,  1811,
     405,  1824,   421,  1241,   594,  -591,  1006,  -589,  2425,  1612,
    -563,   594,   -61,  -339,  2514,   990,  1071,  -591,   977,  -589,
    2290,   856,   617,   858,   683,  1286,   853,  1072,   109,   594,
     859,   860,   861,  1161,  1613,   421,   864,   865,   866,   867,
    2426,   868,   869,  2515,   421,   811,  2324,  2464,     4,   643,
    -584,  1772,  2315,   421,   594,  1073,  1316,  1461,  -593,  -594,
     986,   598,   749,  2316,  -587,  1846,  1613,  1761,  -541,  1552,
    1481,   440,  1553,  1263,  2513,   617,  1168,   589,  -339,  1111,
     594,   421,   421,   421,   421,   421,  1614,  1765,   594,  1049,
     497,   787,  1264,  -339,   421,   599,  1520,  1807,   795,  1817,
     642,  1825,   977,  2516,  1906,  1056,  -527,  -527,  2232,   594,
     421,   421, -1114,  -591,   421,  -589,  1046,  1041,  1614, -1139,
     421,   669,   672,  1703,  1077,  1093,  -137,   679,   680,   684,
     680,  2123,   688,   690,  1173,  -141,   696, -1061,   700,   702,
     702,   705,   694,   936,   708,   421,  1163,   712,  1074,   708,
    1649,  -563,  2121,   -61,   723,     5,   695,   728,  2168,   708,
    1002,   708, -1150,  1004,   698,   422,   708,   708,   708,  1001,
     421,  1001,  1098,  1355,   708,  1812,   741,   708,  1001,   708,
     594,  1885,  1887,  1601,  1813,   752,   753,  1597, -1166,  1799,
    1800,  -584,   764,   766,  1814,  1815, -1169,   772,  1959,  -593,
    -594,  2119,  1809,  1810,   779,  -587,  2131,   783,  1822,  1823,
    1816,  1170,  1828,  1829,   643,  1818,  1819, -1103,   643,   796,
     976,  1151,   803,  1642,  1695,   643,  1451,  1519,   723,   813,
     815,   815,   507,   819,   796,  1517,  1192,  1379,  2132,   825,
     827,   827,   827,   827,   827,  1710,   837,  1202,  1013,   841,
     736,   843,   779, -1114,  -591,   846,  -589,   508,   849,  1511,
   -1139,  1190,   854,   557,  1224,   642,  1314,   594,   694,   642,
    1035,   594,   558,  1801,   570,  1446,   642,   594, -1061,   594,
    2308,  1007,   695,  1655,  1657,  1659,  1811,   594, -1133,   594,
     559,   871,  1824,  1468,   872,  1315,  1676,  2462,   878,  1876,
    1877,  1739,  1732, -1150,   596,  1308,   562,   889,   895,   901,
    1287,  1162,   904,  1164,  1171,   402,   912,   563,  2454,   917,
     918,   919,   696,   403,  1311,  -565,   922,   925,   926, -1166,
    2216,   931,   696,   696,   696,   696,   594, -1169,  1001,   939,
     940,  2194,  1012,  2085,  1369,  1370,  1371,  1372,  1373,  2058,
     920,  1847,  1459,  1013,  2237,  1309,   594,  1881, -1103,  1883,
     932,   933,   934,   935,  1857,  2181,  2198,  2234,   568,  2454,
     907,   908,  1115,  1807,   421, -1113,   643,   571,  2086, -1138,
     977,  1103,   923,  1784,   421, -1060,  1817, -1149,  2124,  2125,
    1353,  1460,  1825,   572,  1894, -1165,  1770, -1168,  1471,  1472,
     575,   576,  1344,  2020,  1207,   712,  1019,   764,   819,   813,
     700,  1024,  1385,  1771,   843,  1026,  2309,  1386,   977,   587,
    1616,   594,   696,  1895,  2253,  2117,  -565,   642,  -527, -1133,
    -384,  1473,  1733,  1037,  -527,  1150,  2374,  2514,  1388,  -565,
     708,  2528,  2530,  1048, -1102,   696,   573,  1204,  -527,   574,
    1031,  1210,    25,  1257,  2534,   421,  1216,    29,  1426,  1220,
    1222,  1258,  1389,  2332, -1132,  1461,  2515,   580,  1065,  1621,
    2310,   583,  1028,  1050,   986,   617,   927,  1390,  1259,    47,
      48,  2311,  1391,  1392,  1422,  1029,   928,  1772,    50,  1393,
    1773,  1749,   977,  1087,  2323,  1092,  1058,  -852,  1094,  1253,
    1634,  1684,   956,   956,  1238,  1238,   957,   957,   584,  1059,
    1105,  1108,  1253,   958,   959,   787, -1113,   577,  1361,   585,
   -1138,  1138,  -792,  -792,  1139,  1097, -1060,  1312, -1149,  1313,
    1145,  1144,  1146,    90,   972,   972, -1165,  1153, -1168,  1156,
    1110,  1110,   696,    95,  1001,  1001,  1001,  1001,  1001,  1012,
    -382,  1635,  1655,  1657,  1659,   669,   646,  1948,  1855,  1856,
    1013,   654,  1560,  1862,  1863,  1273,  1108,  -565,  1427,   997,
    1160,  1066,   696,   998,   643,   643,   643,   643,   643,  1435,
    1749,  2377,  2165,  1297,  1067, -1102,  1298,   696,   118,   121,
     696,  1903,  1904,  1905,  1186,   122,  1198,  1197,  1832,  1833,
    1834,  1000,  1838,  1839,  -383, -1132,  1260,  1187,   586,  1654,
    1656,  1658,   591,  2239,  2240,  1189,  1561,  2365,  1191,  1261,
    1013,  1013,  1013,  1394,  2393,   642,   642,   642,   642,   642,
    1245,  2397,  2494,  1007,  1007,  1265,  1271,  1278,   664,   665,
    1283,  2117,  2411,  1793,  2501,  1511,  2292,  1511,  1266,  1272,
    1279,  1274,  1770,  1284,  1395,  1280,   841,  2293,  2294,   592,
     787,  -382,  1868,  2295,  1356,  2296,  1275,  1276,  1277,  1771,
    1869,  1305,  1499,   975,  2297,   997,  2298,  1357,  2299,   998,
    -383,  2395,  1589,   787,  2129,  2130,   638,   639,  1362,  2236,
    1411,  1415,   978,  1317,  2392,   593,  1320,  2062,  1396,  2063,
    1595,  1363,  1583,  1412,  1416,   421,  1526,  1000,  2064,   597,
    2065,  -387,  1529,   633,  1282,   997,  1532,   656,  1534,   998,
     648,  1447,  1536,   981,  1538,  1906,   638,   639,  2146,  1306,
    1225,  1226,  1443,   999,   657,  1465,  1793,  2330,  2109,  2110,
    2111,  2112,  2113,  1772,  1483,  1444,  1773,  1000,  1466,  1486,
    1770,  1774,  1489,  1028,   658,  1208,  1209,  1484,  1212,  1775,
     659,  2461,  1487,  1227,   660,  1490,  1497,  1771,  1351,  1351,
    1351,  1351,  1351,  2460,  1503,   661,   669,  2105,  1554,  1399,
    1562,  1645,  1403,  1644,   662,  1486,  1662,  1504,   684,  1647,
     663,  1555,  2266,  1563,  1592,  1593,  1527,  1642,  1564,  1663,
    2300,   705,  1530,  2301,   421,   666,  1533,  1994,  1535,  1533,
    1533,  -385,  1537,  2147,  1539,  1251,   675,  1058,  2248,  2152,
     402,  1676,  1760,   981,  1794,  1664,  1436,  1356,  1666,  1691,
    1668,   728,  1511,  2066,  2067,  1925,  2068,  2069,  1672,  1674,
    1671,  1772,   676,  1770,  1773,   677,  1678,   753,  1795,  1774,
     691,  1704,  1675,  1756,   699,  1683,  1462,  1775,  1796,  1679,
    1771,  1251,   766,  1797,  1705,  1694,  1757,  2070,  1415,   711,
    1251,  1251,  2222,  1696,  1759,  1697,  1253,   714,  1931,  1656,
    1658,  1941,  1419,  1962,  1968,  1688,  2267,  1690,  2302,  1013,
    1013,  1013,  2092,  2093,  1060,  1465,  1061,  1228,  1229,   607,
    1485,  1230,  1231,   608,   609,   610,   611,   717,  1969,  2071,
     726,  1713,   732,  2002,  1503,  2006,   612,  1794,  2032,  2052,
    1459,   760,  2072,   613,   745,   614,  2003,  2004,  2007,  2050,
    2051,  2033,  2053,   750,  1772,   782,  1489,  1773,   763,  1548,
    1692,  1795,  2268,  1515,  1886,  1888,  2303,  2304,  2305,  2060,
    2076,  1796,  2061,   615,  1756,  2062,  1797,  2063,  1764,  1761,
    2269,  2129,  2130,  2077,   770,  1503,  2064,  2078,  2065,  1756,
     909,  1486,  2270,   771,  2271,  2272,   784,  2273,  2079,   997,
    2274,   616,  2080,   998,  2081,   774,  1546,  1845,  1486,  1726,
     638,   639,   777,  2083,  1928,  1367,  2087,   999,  1556,  1557,
    1558,  2082,  1605,  1606,  1607,  1007,  2084,  1673,  2248,  2088,
     889,  1000,  1486,  1486,  1608,   895,   605,   606,   421,   921,
    1253,   901,   778,  1609,   786,  2089,  2090,  2106,   904,  1783,
    1584,   912,  1788,  1461,  2126,  1808,  -587,  1821,   617,  1827,
    2107,  1831,  2021,   924,  2023,  2024,  1610,  2127,  2157,  1920,
     790,  1611,   791,  1935,  1594,   948,  2028,  1548,   818,  1548,
     696,  2158,  1548,  2360,  1317,  1923,  2035,  2225,  2037,   979,
    2162,  2275,  2163,  2276,  2262,  2164,  2241,  2242,  2243,  1612,
    2226,   984,  1730,  1186,  1503,  1548,  2335,  2263,  1602,  1939,
     618,  2066,  2067,   977,  2068,  2069,  2286,  2288,  2320,  2336,
    2369,  1945,   826,  1001,  1601,  1947,  2137,  2126,  2387,  1723,
    1375,  1376,   988,  2370,  1251,  1977,   989,  1961,  1503,  2409,
    2379,  2388,   799,   638,   639,  2070,   980,  2404,  1358,  2338,
     851,  2407,  2410,   607,   612,  1660,  1613,   608,   609,   610,
     611,  1465,  1548,   614,  1932,  1933,  1934,  1503,  1756,  1025,
     612,   852,  1769,  1598,  2429,  2430,   855,   613,   607,   614,
    2432,  2434,   608,   609,   610,   611,   857,  2071,  1238,  1238,
    1238,   615,  1238,  1238, -1189,   612,  1840,   876,  1686,  1686,
    2072,  1686,   613,   877,   614,  2438,   880,   615,  1614,   708,
     787,  1087,  2076,  1087,  1238,  2076,  1698,  2473,  2439,   616,
    2475,  1465,   995,   787,  1503,  2467,   621,   956,  2468,   887,
    2474,   957,   615,  2476,  2478,   616,  1186,  2479,   958,   959,
     888,    25,  1251,  1005,   643,   961,    29,   963,  1721,  2480,
     965,   966,   967,   968,   969,  2493,   640,  1156,   978,   972,
     616,  2497,  2517,  1734,  1638,  1288,   981,  1736,    47,    48,
    -230,  2482,   421,   696,  2498,  2518,   617,  2533,  1267,  2129,
    2130,  1268,  1269,  1270,  2523,  2524,  1762,   807,  1763,  1034,
    1766,  1036,   617,   990,  1364,   642,  1007,   421,  1365,   607,
    2443,  2444,  2026,   608,   609,   610,   611,  2029,  1289,   990,
    1218,  1219,  1038,  1835,  1290,  1040,   612,   617,  1047,  1053,
    2039,  1057,    90,   613,  1245,   614,  1078,   997,   618,   405,
    1081,   998,    95,  1156,   990,  1083,   975,  1850,   638,   639,
    1291,  1099,  2041,  1374,   618,   999,  1100,  1859,  2043,  1101,
    1106,  1865,  2045,   615,  1867,  1238,  1238,  1238,  1114,  1000,
    1143,  1139,  1116,  1874,  1292,  2246,  1293,  1477,  1288,   618,
     607,  1169,  1180,  1183,   608,   609,   610,   611,   121,  2362,
    1184,   616,  1193,  2148,  1896,  1199,  1207,   612,  1196,  1236,
    1213,  1228,  1251,  1285,   613,   594,   614,  1907,  1321,  1294,
    2150,  1324,  1346,   957,  1295,  1345,  -342,   998,  1296,  1102,
    1377,  1289,  1297,  1383,  1384,  1298,  1698,  1414,   421,  1698,
    1698,  1698,   150,  2137,   615,  1404,  1406,   775,   997,  1936,
    1428,  1429,   998,  1430,  1431,  1432,  1433,  1299,   617,   638,
     639,  1442,  1445,  1291,  1493,  1110,   999,  2193,  2396,  1511,
    1448,  1300,   616,  1450,  1060,  1454,  1463,  1301,  -934,   607,
    1000,   708,   822,   608,   609,   610,   611,  1292,  1464,  1293,
    1482,  1469,   834,  1470,  1474,  1475,   612,  1498,  1501,  1502,
    1488,  1970,  1505,   613,  1506,   614,  1507,  1516,  1508,   421,
     618,  1518,  1540,  1541,  1525,  1542,  1528,  1543,  1094,  1544,
    1545,  2441,  1294,  1548,  1638,  1565,  1566,  1295,  1549,   617,
    1550,  1296,  1567,   615,  1569,  1297,  1570,  1571,  1298,  1573,
    1574,  1575,  1577,  2459,  1110,   881,   882,   883,   884,   886,
    2189,  1578,  2013,  2014,  1579,  1580,  1581,  1586,   927,  2289,
    1299,   616,  1591,  1629,  2200,  1637,  1643,   373,  1632,  2203,
    1648,  1651,  2204,  2230,  1300,  1652,  1653,  2031,  1667,   403,
    1301,   618,  2211,  2233,  2212,   990,  2213,  1661,  2214,  1684,
    1693,  2459,  1706,  1701,  1707,  1708,  1709,  1460,   421,  1720,
    1731,  1740,  1758,  1843,   950,   952,   953,   787,   954,   651,
    1842,  1871,  1844,   787,  1873,   955,  1899,  1889,   617,   637,
     638,   639,  2354,  2355,  1902,  1915,  1920,  1890,    25,   822,
    1917,   612,  1891,    29,  1892,  1921,  1893,  1940,  1942,  1953,
     614,  1954,  1955,    13,    14,  1957,    15,    16,  -494,  1971,
    1979,    20,  1978,  1972,  1996,    47,    48,  1999,  1997,    23,
    2000,  2001,  2008,  2011,    27,  2012,  1761,    30,   615,  2018,
     618,  1033,  1760,  2019,  2022,    37,  2025,    38,  2034,    40,
    2115,  2036,  2038,  2047,  2056,  2048,  1043,  2057,  2094,   565,
    2120,  1907,  1907,  1907,  2049,  2054,   616,  2055,  2059,  2095,
    2100,  2108,    59,  1907,  -381,  2391,  2116,  2394,  2128,    90,
    2136,  2133,  2140,    70,  1064,  2337,  2139,  2141,  2142,    95,
    2143,  1080,  2145,  2161,  1238,  2144,  2155,  1084,  1085,  2176,
     684,  2196,  2178,   640,  2218,  1749,  2219,    85,  2227,  2220,
     607,  2228,  -224,  2235,   608,   609,   610,   611,  2160,  1879,
      93,   787,  2265,   617,   607,  2252,  2279,   612,   608,   609,
     610,   611,  2260,  2280,   613,   121,   614,  2281,   102,  2174,
    2450,   612,  2282,  1142,   104,  2285,  2283,  -843,   613,  2287,
     614,  2307,   108,  1734,   110,  2313,   112,  1936,   114,  2182,
    2321,  2326,  2327,  2339,   615,   119,  2329,  2333,   566,  2192,
    2368,  2340,  2347,  2349,  2350,   618,  2197,  1766,   615,   150,
    2351,  2352,   130,   131,  2353,  2202,  2356,  2357,  1238,  2358,
    2364,  2372,   616,  2373,  2208,  2375,  2376,  2378,  2405,  2408,
     143,  2420,  2428,  2422,  2431,  2437,   616,   604,  2433,  2442,
    2448,  2446,  1835,  2455,  2456,  2466,  1200,  1201,  2469,  2477,
    2491,   155,  2483,  2103,   156,  2495,  2504,  2499,   607,   421,
    2519,  2520,   608,   609,   610,   611,  2221,  2521,  2532,  2514,
    1281,   578,  1585,   421,   956,   612,  2179,  1859,   957,   617,
    2101,  1872,   613,  1521,   614,   958,   959,  2322,  1238,  2389,
    1458,   960,   961,   617,   963,  1875,   929,   965,   966,   967,
     968,   969,  2328,  2102,   971,  1896,   972,   973,   938,   941,
    1604,  1318,   615,  1054,  1907,  2331,  1907,  1907,  1907,  1907,
    1907,  1907,  1319,  2238,  2114,  2122,  1900,  2231,  1747,  1496,
    1995,   618,  2278,  1729,  2177,  1848,  2291,  1407,  1424,  1680,
     616,  1963,  1453,  1665,  1964,   618,   436,  2138,  2258,  2531,
     788,  1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,
    1334,  1335,  1336,  1337,  1338,  1339,  1340,  1341,  1342,  1343,
    1055,  2151,   600,  1670,   601,   602,   822,   421,   603,  1700,
    1413,  1359,  1159,   815,  2014,  1926,  1927,  1439,  1366,  1514,
    1368,  2343,  1018,  1380,  1188,  1467,   607,   617,  1020,  1022,
     608,   609,   610,   611,   635,  1378,  2361,  1023,   636,  1021,
    1682,  1685,  2257,   612,   637,   638,   639,  2486,  1238,  2180,
     613,  2381,   614,  1907,  1398,  1167,   612,  2470,  1397,  1452,
    2149,   886,  1408,  1417,  2424,   614,  1238,  1409,  2175,  2390,
    2487,  2525,  2503,  2416,  2527,  1746,  2367,  2187,  2009,   618,
     615,  1712,  1107,  1064,   845,  2153,  1841,  1027,  2188,  2342,
     827,   827,   735,   615,   687,  2027,  2040,  2044,  2030,  2042,
    2182,    13,    14,  2046,    15,    16,  2207,  2205,   616,    20,
    2371,  1547,  1244,  1568,  2215,  1572,   956,    23,  2223,  1582,
     957,   616,    27,     0,     0,    30,  1576,   958,   959,     0,
       0,     0,     0,    37,   961,    38, -1190,    40,     0, -1190,
   -1190, -1190, -1190, -1190,     0,   421,     0,     0,   972,     0,
       0,     0,     0,     0,     0,     0,     0,  2383,   640,     0,
      59,     0,     0,     0,     0,   617,     0,  1108,  1478,  1108,
       0,    70,     0,     0,     0,     0,     0,     0,   617,     0,
       0,     0,     0,     0,  2406,     0,  1492,     0,     0,   748,
       0,   798,     0,  2414,  2417,    85,     0,     0,     0,     0,
       0,   799,   638,   639,     0,     0,     0,     0,    93,   886,
    1513,   834,     0,   612,     0,     0,     0,   618,   748,     0,
       0,     0,   614,     0,     0,   748,   102,     0,  1850,  1850,
     618,   607,   104,   808,     0,   608,   609,   610,   611,     0,
     108,     0,   110,     0,   112,     0,   114,     0,   612,     0,
     615,     0,     0,   119,     0,   613,     0,   614,     0,     0,
       0,     0,     0,     0,     0,     0,  2417,     0,  2471,     0,
     130,   131,  1477,     0,     0,   607,  1559,     0,   616,   608,
     609,   610,   611,     0,     0,   615,     0,     0,   143,     0,
       0,     0,   612,     0,     0,     0,     0,     0,     0,   613,
       0,   614,     0,     0,     0,     0,     0,     0,     0,   155,
       0,     0,   156,   616,     0,   640,     0,     0,   833,  2505,
       0,   607,     0,     0,  2506,   608,   609,   610,   611,   615,
     799,   638,   639,     0,  1600,   617,     0,  2506,   612,  2526,
    2529,     0,   612,     0,   937,   613,  1633,   614,     0,     0,
     421,   614,  2529,     0,     0,     0,   833,   616,     0,   607,
       0,     0,     0,   608,   609,   610,   611,     0,     0,     0,
     617,     0,     0,     0,  1640,   615,   612,     0,     0,   615,
       0,     0,     0,   613,     0,   614,  1646,   618,     0,  2190,
       0,     0,  1042,     0,   421,   607,     0,     0,     0,   608,
     609,   610,   611,   616,     0,     0,     0,   616,   748,     0,
       0,     0,   612,   615,   617,     0,     0,     0,     0,   613,
       0,   614,   618,     0,     0,     0,     0,     0,     0,     0,
       0,   990,     0,     0,     0,  1669,  1043,     0,     0,     0,
     421,   616,     0,     0,   640,     0,     0,     0,     0,   615,
    1681,     0,     0,     0,     0,     0,     0,  1689,     0,     0,
     617,     0,  1477,     0,   617,   607,   618,   886,     0,   608,
     609,   610,   611,  1699,     0,  1702,     0,   616,   421,     0,
       0,     0,   612,     0,     0,     0,     0,     0,   886,   613,
       0,   614,     0,     0,     0,     0,     0,     0,   617,     0,
    1090,     0,  1717,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   618,  1728,   421,     0,   618,     0,  1109,   615,
       0,     0,     0,     0,     0,     0,  1742,     0,     0,     0,
       0,  1748,  1141,  1754,   617,     0,     0,     0,     0,     0,
    1147,  1148,     0,     0,     0,  1154,     0,   616,     0,     0,
     618,  1716,     0,     0,   607,     0,     0,     0,   608,   609,
     610,   611,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   612,     0,  1109,     0,     0,     0,     0,   613,     0,
     614,  1181,     0,     0,   421,     0,   618,     0,     0,  1741,
       0,     0,   607,     0,     0,     0,   608,   609,   610,   611,
       0,     0,     0,     0,   617,  1864,     0,     0,   615,   612,
    1203,     0,  1206,     0,     0,     0,   613,     0,   614,     0,
    1975,     0,     0,   607,     0,     0,  1880,   608,   609,   610,
     611,   748,   748,     0,     0,     0,   616,     0,     0,     0,
     612,     0,  1252,  1154,     0,     0,   615,   613,     0,   614,
       0,     0,     0,     0,   607,     0,   618,     0,   608,  1010,
     610,   611,     0,     0,     0,     0,     0,  1924,   822,  1359,
       0,   612,     0,   421,   616,     0,     0,   615,   613,     0,
     614,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   617,     0,   956,     0,     0,  1944,   957,
     607,  1946,     0,     0,     0,   616,   958,   959,   615,  1950,
       0,   421,   960,   961,   962,   963,   964,     0,   965,   966,
     967,   968,   969,   970,     0,   971,     0,   972,   973,     0,
       0,   617,     0,     0,  1350,  1350,   616,     0,     0,     0,
       0,  1973,   421,  1976,     0,   618,     0,   375,     0,     0,
       0,     0,     0,   381,     0,     0,     0,     0,     0,     0,
     748,   748,   617,   388,     0,     0,   390,     0,     0,   393,
       0,     0,     0,   421,     0,     0,   399,     0,     0,     0,
     406,     0,     0,   618,   409,     0,     0,  1252,     0,     0,
       0,     0,     0,   617,     0,     0,     0,     0,     0,     0,
       0,     0,   428,     0,     0,     0,   432,   433,     0,     0,
    1418,     0,   438,   439,   618,     0,     0,     0,   444,   445,
       0,   447,   448,   449,   450,   974,   451,     0,     0,     0,
       0,     0,     0,     0,     0,   460,     0,     0,     0,     0,
     464,     0,   466,     0,     0,   618,   469,     0,   748,     0,
     473,     0,   475,     0,     0,     0,     0,     0,     0,   481,
       0,     0,     0,   485,     0,     0,     0,   488,     0,   490,
       0,     0,     0,     0,     0,     0,   498,   500,     0,  1117,
     502,   503,     0,  1118,   607,     0,   509,     0,   510,     0,
    1119,  1120,   514,  2096,  2097,     0,  1121,  1122,  1123,  1124,
       0,  2104,  1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,
       0,  1133,  1134,     0,     0,     0,     0,     0,     0,   541,
       0,   543,     0,     0,     0,     0,     0,     0,   548,     0,
       0,     0,     0,     0,     0,   956,     0,  1718,  1109,   957,
     607,     0,  2135,     0,     0,     0,   958,   959,  1640,     0,
       0,  1719,   960,   961,   962,   963,     0,     0,   965,   966,
     967,   968,   969,   970,     0,   971,     0,   972,   973,     0,
       0,     0,     0,  2154,     0,  1135,     0,     0,     0,   974,
       0,     0,  2159,     0,   956,     0,  1185,     0,   957,   607,
       0,     0,     0,     0,     0,   958,   959,     0,     0,  2169,
    2170,   960,   961,   962,   963,     0,     0,   965,   966,   967,
     968,   969,   970,     0,   971,     0,   972,   973,     0,     0,
       0,     0,     0,     0,     0,     0,   974,  1742,     0,     0,
       0,     0,     0,     0,     0,   834,     0,     0,   974,     0,
       0,     0,     0,     0,     0,  2199,     0,   956,     0,     0,
    1248,   957,   607,     0,     0,     0,     0,     0,   958,   959,
       0,  2209,     0,  2210,   960,   961,   962,   963,  1603,     0,
     965,   966,   967,   968,   969,   970,     0,   971,     0,   972,
     973,     0,     0,     0,     0,   974,   974,   974,   974,     0,
     974,     0,     0,     0,     0,     0,     0,   956,     0,     0,
    1249,   957,   607,     0,     0,     0,     0,     0,   958,   959,
       0,     0,     0,     0,   960,   961,   962,   963,     0,  2224,
     965,   966,   967,   968,   969,   970,     0,   971,     0,   972,
     973,     0,   748,     0,     0,     0,     0,     0,     0,   720,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   956,     0,     0,   974,   957,   974,   974,   974,   974,
       0,     0,   958,   959,     0,  2245,     0,     0,   960,   961,
    2247,   963,     0,     0,   965,   966,   967,   968,   969,     0,
       0,  2256,  1950,   972,     0,     0,  2261,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2264,     0,  1090,     0,
    1090,  2277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   974,     0,     0,     0,  1109,
    1109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1714,     0,     0,     0,     0,     0,   748,   974,  1724,     0,
       0,  1725,     0,   847,     0,     0,     0,   974,     0,     0,
       0,     0,     0,   808,     0,  1600,     0,  1109,  1109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   974,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   748,
       0,     0,     0,     0,   974,     0,  1790,     0,   974,   974,
    2344,     0,     0,     0,     0,   748,   748,   748,     0,   748,
     748,     0,     0,   748,     0,     0,   886,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1252,     0,     0,
       0,   748,     0,     0,  1109,  1109,  1109,     0,  1154,  1154,
    1252,     0,     0,  1154,  1154,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   974,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2380,
    2247,     0,     0,  2382,     0,  2386,     0,     0,     0,     0,
       0,  1898,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2398,  2399,     0,  2403,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2413,     0,     0,     0,     0,     0,
    2415,     0,     0,   748,   974,   974,   956,     0,     0,  1250,
     957,   607,  2344,     0,     0,     0,     0,   958,   959,     0,
       0,     0,     0,   960,   961,   962,   963,     0,     0,   965,
     966,   967,   968,   969,   970,     0,   971,     0,   972,   973,
       0,     0,     0,     0,     0,     0,  2449,  2451,     0,     0,
       0,     0,     0,     0,     0,   956,     0,     0,   834,   957,
     607,  2463,   748,   748,   748,  2465,   958,   959,     0,     0,
       0,  1323,   960,   961,   962,   963,     0,     0,   965,   966,
     967,   968,   969,   970,     0,   971,     0,   972,   973,     0,
       0,     0,     0,     0,   886,     0,     0,     0,  2451,     0,
       0,     0,  2488,     0,     0,     0,  2492,     0,  1754,     0,
       0,  1109,     0,     0,     0,     0,     0,     0,     0,     0,
    1754,  2502,  2488,     0,     0,     0,     0,     0,     0,   974,
     974,   974,   974,   974,   974,   974,   974,   974,   974,   974,
     974,   974,   974,   974,   974,   974,   974,   974,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   974,     0,     0,     0,     0,     0,   956,
     974,     0,   974,   957,   607,     0,     0,     0,     0,     0,
     958,   959,   974,     0,     0,  1402,   960,   961,   962,   963,
       0,     0,   965,   966,   967,   968,   969,   970,     0,   971,
       0,   972,   973,   956,     0,  1410,     0,   957,   607,     0,
       0,     0,     0,   974,   958,   959,     0,     0,     0,     0,
     960,   961,   962,   963,     0,     0,   965,   966,   967,   968,
     969,   970,     0,   971,     0,   972,   973,     0,   956,     0,
    1425,     0,   957,   607,  1350,  1350,  1350,  1350,  1350,   958,
     959,     0,     0,     0,     0,   960,   961,   962,   963,     0,
    1307,   965,   966,   967,   968,   969,   970,     0,   971,     0,
     972,   973,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   974,     0,     0,     0,   956,     0,     0,     0,
     957,   607,     0,     0,  1252,     0,   974,   958,   959,     0,
    1418,     0,  1437,   960,   961,   962,   963,     0,     0,   965,
     966,   967,   968,   969,   970,     0,   971,   974,   972,   973,
     956,     0,     0,     0,   957,   607,     0,     0,     0,     0,
       0,   958,   959,  2172,     0,     0,  1440,   960,   961,   962,
     963,     0,     0,   965,   966,   967,   968,   969,   970,     0,
     971,     0,   972,   973,     0,   808,     0,     0,     0,     0,
    1387,     0,     0,   974,     0,   956,  1109,     0,     0,   957,
     607,     0,     0,     0,     0,     0,   958,   959,     0,     0,
       0,  1441,   960,   961,   962,   963,     0,  2206,   965,   966,
     967,   968,   969,   970,     0,   971,     0,   972,   973,     0,
       0,     0,   956,     0,   974,     0,   957,   607,     0,     0,
       0,   748,  2217,   958,   959,     0,     0,     0,  1476,   960,
     961,   962,   963,     0,     0,   965,   966,   967,   968,   969,
     970,     0,   971,     0,   972,   973,   956,   974,  1252,     0,
     957,   607,     0,     0,   974,     0,     0,   958,   959,     0,
     974,     0,  1523,   960,   961,   962,   963,     0,     0,   965,
     966,   967,   968,   969,   970,     0,   971,     0,   972,   973,
       0,     0,  1898,   974,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   974,     0,     0,     0,     0,
       0,     0,     0,   974,     0,     0,     0,     0,     0,     0,
       0,     0,  2251,   974,     0,   748,   974,  2254,     0,     0,
       0,   956,     0,     0,     0,   957,   607,     0,     0,     0,
       0,   974,   958,   959,     0,     0,     0,  1524,   960,   961,
     962,   963,   974,     0,   965,   966,   967,   968,   969,   970,
       0,   971,     0,   972,   973,     0,   974,     0,     0,     0,
       0,     0,   974,     0,     0,     0,     0,     0,   974,     0,
     956,     0,     0,     0,   957,   607,     0,     0,     0,     0,
       0,   958,   959,     0,   748,   748,  1650,   960,   961,   962,
     963,     0,     0,   965,   966,   967,   968,   969,   970,     0,
     971,   956,   972,   973,     0,   957,   607,     0,     0,     0,
       0,     0,   958,   959,     0,     0,     0,  1918,   960,   961,
     962,   963,     0,     0,   965,   966,   967,   968,   969,   970,
       0,   971,     0,   972,   973,  1590,     0,     0,   956,     0,
    1718,     0,   957,   607,     0,     0,     0,     0,  1109,   958,
     959,     0,  1109,     0,     0,   960,   961,   962,   963,     0,
       0,   965,   966,   967,   968,   969,   970,     0,   971,     0,
     972,   973,   956,     0,     0,     0,   957,   607,   974,     0,
       0,     0,     0,   958,   959,     0,     0,     0,  1956,   960,
     961,   962,   963,     0,   974,   965,   966,   967,   968,   969,
     970,     0,   971,     0,   972,   973,     0,     0,     0,     0,
       0,     0,     0,     0,  1109,   748,  1109,  1109,  1109,     0,
       0,     0,     0,  2172,   956,     0,  1974,     0,   957,   607,
       0,     0,     0,   748,     0,   958,   959,     0,   974,     0,
       0,   960,   961,   962,   963,     0,     0,   965,   966,   967,
     968,   969,   970,     0,   971,     0,   972,   973,   974,     0,
     974,     0,     0,     0,   974,     0,     0,     0,     0,     0,
    1109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   974,     0,     0,
     974,     0,  1109,  1109,     0,     0,  1109,   956,     0,     0,
       0,   957,   607,  2172,     0,     0,     0,     0,   958,   959,
       0,  1135,     0,  2005,   960,   961,   962,   963,     0,     0,
     965,   966,   967,   968,   969,   970,     0,   971,     0,   972,
     973,   956,     0,     0,     0,   957,   607,     0,     0,     0,
    1109,     0,   958,   959,     0,     0,     0,  2091,   960,   961,
     962,   963,     0,     0,   965,   966,   967,   968,   969,   970,
       0,   971,     0,   972,   973,   956,     0,  2156,     0,   957,
     607,     0,     0,     0,     0,     0,   958,   959,     0,     0,
       0,     0,   960,   961,   962,   963,     0,     0,   965,   966,
     967,   968,   969,   970,     0,   971,     0,   972,   973,     0,
       0,     0,   956,     0,  2171,     0,   957,   607,     0,     0,
     974,   974,     0,   958,   959,     0,     0,     0,   974,   960,
     961,   962,   963,     0,     0,   965,   966,   967,   968,   969,
     970,     0,   971,     0,   972,   973,     0,     0,     0,   956,
       0,     0,     0,   957,   607,     0,     0,     0,     0,   974,
     958,   959,     0,     0,     0,  2229,   960,   961,   962,   963,
       0,     0,   965,   966,   967,   968,   969,   970,   974,   971,
     956,   972,   973,   974,   957,   607,     0,     0,     0,     0,
       0,   958,   959,   974,   974,     0,  2244,   960,   961,   962,
     963,     0,     0,   965,   966,   967,   968,   969,   970,     0,
     971,     0,   972,   973,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   974,     0,     0,   956,     0,     0,  2255,
     957,   607,     0,   974,   974,     0,     0,   958,   959,     0,
       0,     0,     0,   960,   961,   962,   963,     0,   974,   965,
     966,   967,   968,   969,   970,     0,   971,     0,   972,   973,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   974,
       0,   974,     0,     0,     0,     0,     0,     0,     0,   956,
     974,     0,     0,   957,   607,   974,     0,     0,   974,     0,
     958,   959,     0,     0,     0,  2259,   960,   961,   962,   963,
       0,   974,   965,   966,   967,   968,   969,   970,     0,   971,
     956,   972,   973,     0,   957,   607,     0,     0,     0,     0,
       0,   958,   959,     0,     0,     0,  2318,   960,   961,   962,
     963,     0,     0,   965,   966,   967,   968,   969,   970,     0,
     971,     0,   972,   973,     0,     0,   956,     0,     0,     0,
     957,   607,     0,     0,     0,     0,     0,   958,   959,     0,
       0,     0,  2319,   960,   961,   962,   963,     0,   974,   965,
     966,   967,   968,   969,   970,     0,   971,     0,   972,   973,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   974,     0,   974,     0,     0,     0,
     974,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   974,   974,   956,     0,     0,   974,   957,   607,
       0,     0,     0,     0,     0,   958,   959,   974,     0,   974,
    2325,   960,   961,   962,   963,     0,     0,   965,   966,   967,
     968,   969,   970,     0,   971,     0,   972,   973,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   974,     0,   974,     0,     0,     0,     0,
       0,   377,   378,   379,   380,     0,   382,   974,   383,   974,
     385,   386,     0,   387,     0,     0,     0,   389,     0,   391,
     392,     0,     0,   394,   395,   396,     0,   398,     0,   400,
     401,     0,   974,   408,     0,     0,   974,     0,   411,   412,
     413,   414,   415,   416,   417,   418,   974,   419,   420,     0,
       0,   425,   426,   427,     0,   429,     0,   431,     0,     0,
     434,   435,     0,     0,     0,     0,     0,     0,   442,   443,
       0,     0,   446,     0,     0,     0,     0,     0,     0,   452,
       0,   454,     0,   455,   456,     0,     0,     0,   461,   462,
     463,     0,     0,   465,     0,     0,   467,   468,     0,   470,
     471,   472,     0,     0,     0,     0,   477,   478,     0,     0,
     480,     0,   482,   483,   484,     0,   486,   487,     0,     0,
     489,     0,   491,   492,   493,   494,   495,   496,     0,     0,
       0,     0,     0,     0,   504,   505,   506,     0,     0,     0,
       0,   511,   512,   513,     0,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,     0,   542,     0,   544,     0,   545,     0,   546,   547,
       0,   549,   550,   551,   552,   553,   554,   555,   556,     0,
     956,     0,     9,  2334,   957,   607,     0,     0,     0,    10,
       0,   958,   959,     0,     0,     0,     0,   960,   961,   962,
     963,     0,     0,   965,   966,   967,   968,   969,   970,     0,
     971,     0,   972,   973,     0,     0,     0,     0,     0,    11,
      12,    13,    14,     0,    15,    16,    17,    18,    19,    20,
       0,   634,    21,    22,   647,     0,   650,    23,    24,    25,
       0,    26,    27,    28,    29,    30,    31,     0,    32,    33,
      34,    35,    36,    37,     0,    38,    39,    40,    41,    42,
      43,     0,     0,    44,    45,    46,    47,    48,     0,     0,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     0,    71,     0,    72,    73,     0,    74,    75,
      76,     0,     0,    77,     0,     0,    78,    79,     0,    80,
      81,    82,    83,     0,    84,    85,    86,    87,    88,    89,
      90,    91,    92,     0,     0,     0,     0,     0,    93,    94,
      95,    96,     0,     0,     0,     0,    97,     0,     0,    98,
      99,     0,     0,   100,   101,     0,   102,     0,     0,     0,
     103,     0,   104,     0,   105,     0,     0,     0,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,   116,
     117,   118,     0,   119,     0,   120,   121,     0,   122,     0,
     123,   124,   125,   126,     0,     0,   127,   128,   129,     0,
     130,   131,   132,     0,   133,   134,   135,     0,   136,     0,
     137,   138,   139,   140,   141,     0,   142,     0,   143,   144,
       0,     0,   145,   146,   147,     0,     0,   148,   149,     0,
     150,   151,     0,   152,   153,     0,     0,     0,   154,   155,
       0,     0,   156,     0,     0,   157,     0,     0,     0,   158,
     159,     0,     0,   160,   161,   162,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,   174,
       0,     0,   175,     0,     0,     0,   176,   177,   178,   179,
     180,     0,   181,   182,     0,     0,   183,   184,   185,   186,
       0,     0,     0,     0,   187,   188,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,     0,   193,     0,     0,
     194,   195,   196,   197,   198,     0,     0,     0,   199,   200,
     201,   202,   203,   204,   956,   205,   206,     0,   957,   607,
     207,     0,     0,     0,     0,   958,   959,     0,     0,     0,
    2341,   960,   961,   962,   963,     0,     0,   965,   966,   967,
     968,   969,   970,     0,   971,     0,   972,   973,     0,     0,
       0,     0,     0,     0,   956,     0,     0,  2359,   957,   607,
       0,     0,     0,     0,     0,   958,   959,     0,     0,     0,
       0,   960,   961,   962,   963,   946,   947,   965,   966,   967,
     968,   969,   970,     0,   971,   956,   972,   973,  2421,   957,
     607,     0,     0,     0,     0,     0,   958,   959,     0,     0,
       0,     0,   960,   961,   962,   963,     0,     0,   965,   966,
     967,   968,   969,   970,     0,   971,   956,   972,   973,     0,
     957,   607,     0,     0,     0,     0,     0,   958,   959,     0,
       0,     0,  2423,   960,   961,   962,   963,     0,     0,   965,
     966,   967,   968,   969,   970,     0,   971,   956,   972,   973,
       0,   957,   607,     0,     0,     0,     0,     0,   958,   959,
       0,     0,     0,  2435,   960,   961,   962,   963,     0,     0,
     965,   966,   967,   968,   969,   970,     0,   971,   956,   972,
     973,  2436,   957,   607,     0,     0,     0,     0,     0,   958,
     959,     0,     0,     0,     0,   960,   961,   962,   963,     0,
       0,   965,   966,   967,   968,   969,   970,     0,   971,   956,
     972,   973,  2440,   957,   607,     0,     0,     0,     0,     0,
     958,   959,     0,     0,     0,     0,   960,   961,   962,   963,
       0,     0,   965,   966,   967,   968,   969,   970,     0,   971,
     956,   972,   973,     0,   957,   607,     0,     0,     0,     0,
       0,   958,   959,     0,     0,     0,  2445,   960,   961,   962,
     963,     0,     0,   965,   966,   967,   968,   969,   970,     0,
     971,   956,   972,   973,     0,   957,   607,     0,     0,     0,
       0,     0,   958,   959,     0,     0,     0,  2447,   960,   961,
     962,   963,     0,     0,   965,   966,   967,   968,   969,   970,
       0,   971,   956,   972,   973,  2481,   957,   607,     0,     0,
       0,     0,     0,   958,   959,     0,     0,     0,     0,   960,
     961,   962,   963,     0,     0,   965,   966,   967,   968,   969,
     970,     0,   971,     0,   972,   973,   956,     0,  2496,     0,
     957,   607,     0,     0,     0,     0,     0,   958,   959,     0,
       0,     0,     0,   960,   961,   962,   963,     0,     0,   965,
     966,   967,   968,   969,   970,     0,   971,   956,   972,   973,
       0,   957,   607,     0,     0,     0,     0,     0,   958,   959,
       0,     0,     0,     0,   960,   961,   962,   963,     0,     0,
     965,   966,   967,   968,   969,   970,     0,   971,   956,   972,
     973,     0,   957,     0,     0,     0,     0,     0,     0,   958,
     959,     0,     0,     0,     0,   960,   961,   962,   963,     0,
       0,   965,   966,   967,   968,   969,   970,     0,   971,     0,
     972,   973
};

static const yytype_int16 yycheck[] =
{
      50,   378,   486,   493,   494,   495,   496,   483,   392,  1464,
      62,    63,   375,   541,   387,   630,  1143,    69,  1036,   472,
     645,  1032,   231,   232,   887,   401,   634,   750,   237,   980,
     930,   209,  1502,   256,   656,   411,   609,   413,   261,   763,
    1566,  1315,   418,   419,   420,   467,    98,  1569,  1344,  1571,
     426,   430,  1599,   429,  1605,   431,  1605,  1629,   979,   980,
     986,   258,  1159,  1498,   261,   262,  1616,  1971,   118,  1522,
     433,   743,   122,   888,  2010,   442,     7,   845,  1076,  1377,
     480,    76,   655,   656,   256,     7,   845,   450,  1534,   261,
    1315,   468,  1899,   655,   656,     5,    63,  1534,     0,     1,
    1570,   464,     8,     7,    99,    41,   469,  1534,  1534,   407,
     473,  1010,   475,  1532,  1532,  1534,  1534,  1536,  1536,  1538,
    1538,   116,   175,  1534,  1671,   488,  1625,   116,  1534,  1534,
      71,  1630,    89,    16,    17,   877,   182,   500,   182,   502,
     673,    15,     8,   388,   169,    21,   509,   116,    58,   144,
       8,     8,     8,   205,    20,   191,     8,     5,     5,     7,
     191,     5,    20,    20,    15,   122,  1184,  2358,    20,  1032,
      15,   406,   224,  1171,    21,   800,    86,    92,   129,    15,
      15,  1707,  1708,  1709,   637,   116,     8,   878,   641,    15,
     477,    37,  1055,    15,   116,   648,    15,  1532,   155,  1534,
      15,  1536,   129,    21,     8,     8,    15,     8,   148,    92,
     116,     8,   116,   129,   128,   166,   126,    20,     3,    20,
    2195,   519,   149,   521,     8,   916,   513,   137,   185,     8,
     528,   529,   530,    18,   149,   129,   534,   535,   536,   537,
     180,   539,   540,   157,   129,   480,  2221,  2438,   150,   472,
     116,   282,   288,   129,     8,   165,    15,   282,   116,   116,
     633,   218,   434,   299,   116,  1561,   149,   208,   257,   315,
     323,    64,   318,   209,   318,   149,   809,     8,   129,   763,
       8,   129,   129,   129,   129,   129,   201,   172,     8,   696,
      15,   463,   228,   129,   129,   252,  1196,  1532,   470,  1534,
     472,  1536,     3,   217,   149,   712,    37,   129,  2115,     8,
     129,   129,   116,   116,   129,   116,   692,   690,   201,   116,
     129,   373,   374,  1450,   724,    26,   257,   379,   380,   381,
     382,  1903,   384,   385,   818,   257,   388,   116,   390,   391,
     392,   393,    23,   588,   396,   129,   799,   399,   258,   401,
    1648,   257,  1902,   257,   406,   257,    37,   409,  2262,   411,
     647,   413,   116,   650,   388,   417,   418,   419,   420,   994,
     129,   996,   751,   981,   426,  1821,   428,   429,  1003,   431,
       8,  1606,  1607,  1309,  1821,   437,   438,  1308,   116,  1808,
    1808,   257,   444,   445,  1821,  1821,   116,   449,   254,   257,
     257,  1900,  1821,  1821,   456,   257,     5,   459,  1827,  1827,
    1821,   811,  1831,  1831,   637,  1821,  1821,   116,   641,   471,
     246,   788,   474,  1349,  1442,   648,  1098,  1195,   480,   481,
     482,   483,    15,   485,   486,  1194,   843,  1010,    37,   489,
     492,   493,   494,   495,   496,  1463,   498,   854,  1010,   501,
     417,   503,   504,   257,   257,   507,   257,     8,   510,  1183,
     257,   840,   514,    15,   871,   637,     8,     8,    23,   641,
     679,     8,    15,  1808,   211,  1090,   648,     8,   257,     8,
      94,   653,    37,  1382,  1383,  1384,  1821,     8,   116,     8,
      15,   543,  1827,  1115,   544,    37,  1422,  2433,   548,  1596,
    1597,  1499,    47,   257,   241,   927,    15,   557,   558,   559,
     917,   798,   562,   800,   812,     7,   568,   257,  2422,   571,
     572,   573,   574,    15,   931,    15,   576,   579,   580,   257,
    2056,   583,   584,   585,   586,   587,     8,   257,  1163,   591,
     592,  2011,  1115,   315,   997,   998,   999,  1000,  1001,  1845,
     574,  1562,   169,  1115,  2126,   928,     8,  2108,   257,  2108,
     584,   585,   586,   587,  1575,  2000,  2019,  2117,    15,  2473,
     565,   566,   769,  1808,   129,   116,   799,     8,   350,   116,
       3,   759,   577,   266,   129,   116,  1821,   116,  1904,  1905,
      64,   208,  1827,     8,     8,   116,   191,   116,   147,   148,
       7,     8,   975,    26,   287,   657,   658,   659,   660,   661,
     662,   663,  1019,   208,   666,   665,   230,  1024,     3,     8,
    1894,     8,   674,    37,  2150,  1899,   116,   799,    15,   257,
       3,   180,   177,   683,    23,     8,    21,   128,    43,   129,
     692,  2519,  2520,   695,   116,   697,     8,   856,    37,     8,
     674,   860,    63,   183,  2532,   129,   865,    68,  1065,   868,
     869,   191,    67,  2235,   116,   282,   157,     8,   720,  1894,
     284,     8,     8,   697,  1047,   149,     5,    82,   208,    90,
      91,   295,    87,    88,  1057,    21,    15,   282,    95,    94,
     285,     5,     3,   745,  2220,   747,     8,     8,   750,  1562,
    1322,    15,     5,     5,   876,   877,     9,     9,     8,    21,
     760,   763,  1575,    16,    17,   887,   257,   124,  1644,     8,
     257,   773,     7,     8,   774,  1448,   257,   936,   257,   938,
     782,   781,   784,   144,    37,    37,   257,   789,   257,   791,
    1464,  1465,   794,   154,  1369,  1370,  1371,  1372,  1373,  1322,
       3,  1324,  1651,  1652,  1653,   807,   256,  1683,  1573,  1574,
    1322,   261,    15,  1578,  1579,   244,   818,   257,  1066,     5,
     794,     8,   824,     9,   997,   998,   999,  1000,  1001,  1077,
       5,  2328,     7,   191,    21,   257,   194,   839,   195,   200,
     842,    15,    16,    17,     8,   202,   848,   847,  1540,  1541,
    1542,    37,  1544,  1545,     3,   257,     8,    21,     8,  1382,
    1383,  1384,     8,  2129,  2130,   839,    15,  2287,   842,    21,
    1382,  1383,  1384,   228,  2350,   997,   998,   999,  1000,  1001,
     880,  2353,  2483,  1005,  1006,     8,     8,     8,     7,     8,
       8,  2115,  2368,    84,  2495,  1569,     5,  1571,    21,    21,
      21,   330,   191,    21,   259,   907,   908,    16,    17,     8,
    1032,     3,    18,    22,     8,    24,   345,   346,   347,   208,
      26,   923,  1170,    15,    33,     5,    35,    21,    37,     9,
       3,  2351,  1289,  1055,    16,    17,    16,    17,     8,    21,
       8,     8,    15,   945,  2349,     8,   946,    22,   303,    24,
    1307,    21,  1281,    21,    21,   129,  1204,    37,    33,     7,
      35,     3,  1210,    15,   909,     5,  1214,     8,  1216,     9,
      15,  1093,  1220,    15,  1222,   149,    16,    17,  1939,   924,
     147,   148,     8,    23,     8,     8,    84,  2233,  1889,  1890,
    1891,  1892,  1893,   282,     8,    21,   285,    37,    21,     8,
     191,   290,     8,     8,     8,   858,   859,    21,   861,   298,
       8,  2431,    21,   180,     8,    21,    21,   208,  1889,  1890,
    1891,  1892,  1893,  2428,     8,     8,  1028,  1877,     8,  1029,
       8,  1358,  1034,  1356,     8,     8,     8,    21,  1040,  1362,
       8,    21,    41,    21,     7,     8,  1205,  1923,    21,    21,
     159,  1053,  1211,   162,   129,     8,  1215,  1730,  1217,  1218,
    1219,     3,  1221,  1939,  1223,     8,    15,     8,  2145,  1945,
       7,  1947,    71,    15,   265,  1402,  1078,     8,    21,  1436,
      21,  1083,  1756,   158,   159,  1643,   161,   162,  1415,     8,
      21,   282,    15,   191,   285,   149,     8,  1099,   289,   290,
      15,     8,    21,     8,    15,  1428,  1106,   298,   299,    21,
     208,     8,  1114,   304,    21,  1441,    21,   192,     8,    15,
       8,     8,  2083,  1443,    21,  1445,  1939,   149,  1651,  1652,
    1653,    21,  1945,    21,    21,  1431,   135,  1433,   247,  1651,
    1652,  1653,   348,   349,     5,     8,     7,   314,   315,    10,
    1150,   318,   319,    14,    15,    16,    17,     7,    21,   234,
      15,  1474,    15,     8,     8,     8,    27,   265,     8,     8,
     169,     8,   247,    34,    15,    36,    21,    21,    21,   316,
     317,    21,    21,    15,   282,     8,     8,   285,    15,     8,
    1438,   289,   191,  1193,  1606,  1607,   305,   306,   307,    21,
       8,   299,    21,    64,     8,    22,   304,    24,  1521,   208,
     209,    16,    17,    21,    15,     8,    33,    21,    35,     8,
     124,     8,   221,    15,   223,   224,    37,   226,    21,     5,
     229,    92,    21,     9,    21,    15,  1236,  1560,     8,  1487,
      16,    17,    15,     8,  1647,    21,     8,    23,  1248,  1249,
    1250,    21,    15,    16,    17,  1377,    21,  1416,  2335,    21,
    1260,    37,     8,     8,    27,  1265,   247,   248,   129,     7,
    2083,  1271,    15,    36,    15,    21,    21,     8,  1278,  1527,
    1282,  1283,  1530,   282,     8,  1533,     8,  1535,   149,  1537,
      21,  1539,  1770,   124,  1772,  1773,    59,    21,     8,    21,
      15,    64,    15,  1660,  1306,   239,  1784,     8,    15,     8,
    1312,    21,     8,  2281,  1316,  1638,  1794,     8,  1796,   246,
      21,   320,    21,   322,     8,    21,  2131,  2132,  2133,    92,
      21,    21,  1491,     8,     8,     8,     8,    21,  1312,  1662,
     201,   158,   159,     3,   161,   162,    21,    21,    21,    21,
       8,  1674,    15,  1928,  2230,  1678,  1921,     8,     8,  1481,
    1005,  1006,     5,    21,     8,  1722,     9,  1693,     8,     8,
      21,    21,    15,    16,    17,   192,   246,    21,     5,  2255,
      15,    21,    21,    10,    27,  1387,   149,    14,    15,    16,
      17,     8,     8,    36,  1651,  1652,  1653,     8,     8,     7,
      27,    15,  1524,     5,    21,    21,    15,    34,    10,    36,
      21,    21,    14,    15,    16,    17,    15,   234,  1540,  1541,
    1542,    64,  1544,  1545,    15,    27,  1548,    15,  1430,  1431,
     247,  1433,    34,    15,    36,     8,    15,    64,   201,  1441,
    1562,  1443,     8,  1445,  1566,     8,  1448,     8,    21,    92,
       8,     8,    26,  1575,     8,    21,   251,     5,    21,    15,
      21,     9,    64,    21,    21,    92,     8,    21,    16,    17,
      15,    63,     8,     8,  1647,    23,    68,    25,  1480,    21,
      28,    29,    30,    31,    32,    21,   129,  1489,    15,    37,
      92,     8,     8,  1495,     8,    44,    15,  1497,    90,    91,
       7,  2469,   129,  1505,    21,    21,   149,    21,   338,    16,
      17,   341,   342,   343,  2515,  2516,  1516,    15,  1518,   240,
    1522,    15,   149,   166,     5,  1647,  1648,   129,     9,    10,
    2408,  2409,  1780,    14,    15,    16,    17,  1785,    87,   166,
     866,   867,    15,  1543,    93,     8,    27,   149,    15,     8,
    1798,    15,   144,    34,  1554,    36,   175,     5,   201,    15,
     149,     9,   154,  1565,   166,     8,    15,  1567,    16,    17,
     119,     8,  1820,    21,   201,    23,     8,  1577,  1826,    15,
       8,  1581,  1830,    64,  1586,  1707,  1708,  1709,     8,    37,
      15,  1591,    26,  1593,   143,     5,   145,     7,    44,   201,
      10,     7,    62,    15,    14,    15,    16,    17,   200,  2283,
      15,    92,     8,  1940,  1616,     8,   287,    27,    21,     8,
      15,   314,     8,   213,    34,     8,    36,  1629,    15,   178,
    1943,     8,   129,     9,   183,    64,    21,     9,   187,   231,
       8,    87,   191,     8,     8,   194,  1648,    37,   129,  1651,
    1652,  1653,   244,  2218,    64,    15,    67,   452,     5,  1661,
      15,    15,     9,    15,    15,    15,    15,   216,   149,    16,
      17,    15,     8,   119,    21,  2349,    23,  2011,  2352,  2353,
       8,   230,    92,    26,     5,   129,    15,   236,     7,    10,
      37,  1693,   487,    14,    15,    16,    17,   143,     7,   145,
      37,    21,   497,    21,    21,    18,    27,     7,    15,     7,
      26,  1713,     8,    34,    15,    36,    15,     8,    26,   129,
     201,     8,    15,    15,    21,    15,    21,    15,  1730,    15,
      15,  2405,   178,     8,     8,    15,    15,   183,    21,   149,
      21,   187,    15,    64,    15,   191,    15,    15,   194,    15,
      15,    15,    15,  2427,  2428,   550,   551,   552,   553,   554,
    2008,    15,  1764,  1765,    15,    15,    15,    15,     5,  2195,
     216,    92,    15,    15,  2022,    21,     7,    15,    62,  2027,
       8,     8,  2030,  2106,   230,     8,     8,  1789,     7,    15,
     236,   201,  2040,  2116,  2042,   166,  2044,   255,  2046,    15,
     239,  2475,    16,    21,    15,    15,    15,   208,   129,    21,
       8,     7,    15,   315,   609,   610,   611,  1939,   613,     5,
     330,    15,   331,  1945,     7,   620,     5,   246,   149,    15,
      16,    17,  2272,  2273,     8,    15,    21,   246,    63,   634,
      15,    27,   246,    68,   246,    21,   246,     8,     7,    21,
      36,    21,    21,    45,    46,     8,    48,    49,    26,    15,
       8,    53,   173,    21,    15,    90,    91,   255,    15,    61,
       8,     7,    21,    15,    66,    15,   208,    69,    64,    18,
     201,   676,    71,     8,    15,    77,    15,    79,    15,    81,
       5,    15,    15,    21,    15,    21,   691,    15,     8,   124,
    1902,  1903,  1904,  1905,    21,    21,    92,    21,    21,    21,
      21,     8,   104,  1915,    15,  2349,    15,  2351,     7,   144,
      20,     9,    26,   115,   719,  2252,    21,    21,    21,   154,
      21,   726,    15,    15,  2056,    21,    21,   732,   733,    26,
    1942,     8,    26,   129,    21,     5,    15,   139,     7,    15,
      10,    21,    15,    26,    14,    15,    16,    17,  1958,     5,
     152,  2083,    15,   149,    10,     8,    21,    27,    14,    15,
      16,    17,   254,    21,    34,   200,    36,    15,   170,  1979,
      40,    27,     8,   778,   176,    21,   132,     7,    34,     7,
      36,    21,   184,  1995,   186,    37,   188,  1999,   190,  2001,
      21,     7,     7,   255,    64,   197,    21,    21,   233,  2011,
       7,    15,    15,    15,    15,   201,  2018,  2019,    64,   244,
      15,    15,   214,   215,    15,  2025,    15,    15,  2150,    15,
      15,    21,    92,     8,  2034,     8,     7,    21,     8,     7,
     232,    21,     7,    15,     7,    21,    92,   239,    15,    78,
       8,   329,  2052,     7,     7,    21,   851,   852,    15,    15,
      21,   253,    17,     5,   256,    17,    15,     8,    10,   129,
       7,     7,    14,    15,    16,    17,  2076,    15,     7,   128,
     908,   222,  1283,   129,     5,    27,  1997,  2087,     9,   149,
    1874,  1591,    34,  1197,    36,    16,    17,  2219,  2220,  2347,
    1102,    22,    23,   149,    25,  1595,   582,    28,    29,    30,
      31,    32,  2230,  1875,    35,  2117,    37,    38,   590,   593,
    1314,   945,    64,   710,  2126,  2235,  2128,  2129,  2130,  2131,
    2132,  2133,   945,  2128,  1894,  1902,  1625,  2108,  1505,  1166,
    1731,   201,  2177,  1489,  1995,  1565,  2196,  1038,  1058,  1425,
      92,  1704,  1100,  1404,  1706,   201,    75,  1923,  2158,  2521,
     463,   956,   957,   958,   959,   960,   961,   962,   963,   964,
     965,   966,   967,   968,   969,   970,   971,   972,   973,   974,
     711,  1945,   246,  1411,   246,   246,   981,   129,   246,  1448,
    1047,   986,   792,  2195,  2196,  1644,  1647,  1083,   993,  1186,
     995,     5,   657,  1010,   838,  1114,    10,   149,   659,   661,
      14,    15,    16,    17,     5,  1010,  2282,   662,     9,   660,
    1427,  1429,  2157,    27,    15,    16,    17,  2473,  2350,  1999,
      34,  2335,    36,  2235,  1028,   807,    27,  2448,  1026,  1099,
    1942,  1036,  1040,  1053,  2387,    36,  2368,  1042,  1981,  2348,
    2475,  2517,  2497,  2375,  2519,  1503,  2290,  2002,  1756,   201,
      64,  1465,   761,  1058,   504,  1947,  1554,   666,  2006,  2262,
    2272,  2273,   415,    64,   382,  1783,  1808,  1827,  1788,  1821,
    2282,    45,    46,  1831,    48,    49,  2032,  2031,    92,    53,
    2313,  1236,   878,  1260,  2052,  1265,     5,    61,  2087,  1278,
       9,    92,    66,    -1,    -1,    69,  1271,    16,    17,    -1,
      -1,    -1,    -1,    77,    23,    79,    25,    81,    -1,    28,
      29,    30,    31,    32,    -1,   129,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2339,   129,    -1,
     104,    -1,    -1,    -1,    -1,   149,    -1,  2349,  1143,  2351,
      -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,
      -1,    -1,    -1,    -1,  2364,    -1,  1161,    -1,    -1,   434,
      -1,     5,    -1,  2373,  2376,   139,    -1,    -1,    -1,    -1,
      -1,    15,    16,    17,    -1,    -1,    -1,    -1,   152,  1184,
    1185,  1186,    -1,    27,    -1,    -1,    -1,   201,   463,    -1,
      -1,    -1,    36,    -1,    -1,   470,   170,    -1,  2408,  2409,
     201,    10,   176,   478,    -1,    14,    15,    16,    17,    -1,
     184,    -1,   186,    -1,   188,    -1,   190,    -1,    27,    -1,
      64,    -1,    -1,   197,    -1,    34,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2448,    -1,  2450,    -1,
     214,   215,     7,    -1,    -1,    10,  1251,    -1,    92,    14,
      15,    16,    17,    -1,    -1,    64,    -1,    -1,   232,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   253,
      -1,    -1,   256,    92,    -1,   129,    -1,    -1,     7,  2499,
      -1,    10,    -1,    -1,  2504,    14,    15,    16,    17,    64,
      15,    16,    17,    -1,  1309,   149,    -1,  2517,    27,  2519,
    2520,    -1,    27,    -1,   589,    34,  1321,    36,    -1,    -1,
     129,    36,  2532,    -1,    -1,    -1,     7,    92,    -1,    10,
      -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
     149,    -1,    -1,    -1,  1349,    64,    27,    -1,    -1,    64,
      -1,    -1,    -1,    34,    -1,    36,  1361,   201,    -1,    78,
      -1,    -1,     7,    -1,   129,    10,    -1,    -1,    -1,    14,
      15,    16,    17,    92,    -1,    -1,    -1,    92,   653,    -1,
      -1,    -1,    27,    64,   149,    -1,    -1,    -1,    -1,    34,
      -1,    36,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   166,    -1,    -1,    -1,  1410,  1411,    -1,    -1,    -1,
     129,    92,    -1,    -1,   129,    -1,    -1,    -1,    -1,    64,
    1425,    -1,    -1,    -1,    -1,    -1,    -1,  1432,    -1,    -1,
     149,    -1,     7,    -1,   149,    10,   201,  1442,    -1,    14,
      15,    16,    17,  1448,    -1,  1450,    -1,    92,   129,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,  1463,    34,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,
     745,    -1,  1477,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   201,  1488,   129,    -1,   201,    -1,   763,    64,
      -1,    -1,    -1,    -1,    -1,    -1,  1501,    -1,    -1,    -1,
      -1,  1506,   777,  1508,   149,    -1,    -1,    -1,    -1,    -1,
     785,   786,    -1,    -1,    -1,   790,    -1,    92,    -1,    -1,
     201,     7,    -1,    -1,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    -1,   818,    -1,    -1,    -1,    -1,    34,    -1,
      36,   826,    -1,    -1,   129,    -1,   201,    -1,    -1,     7,
      -1,    -1,    10,    -1,    -1,    -1,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,   149,  1580,    -1,    -1,    64,    27,
     855,    -1,   857,    -1,    -1,    -1,    34,    -1,    36,    -1,
       7,    -1,    -1,    10,    -1,    -1,  1601,    14,    15,    16,
      17,   876,   877,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      27,    -1,   887,   888,    -1,    -1,    64,    34,    -1,    36,
      -1,    -1,    -1,    -1,    10,    -1,   201,    -1,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,  1642,  1643,  1644,
      -1,    27,    -1,   129,    92,    -1,    -1,    64,    34,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,    -1,     5,    -1,    -1,  1673,     9,
      10,  1676,    -1,    -1,    -1,    92,    16,    17,    64,  1684,
      -1,   129,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,   149,    -1,    -1,   979,   980,    92,    -1,    -1,    -1,
      -1,  1716,   129,  1718,    -1,   201,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
    1005,  1006,   149,    28,    -1,    -1,    31,    -1,    -1,    34,
      -1,    -1,    -1,   129,    -1,    -1,    41,    -1,    -1,    -1,
      45,    -1,    -1,   201,    49,    -1,    -1,  1032,    -1,    -1,
      -1,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
    1055,    -1,    77,    78,   201,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    88,    89,   621,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,
     105,    -1,   107,    -1,    -1,   201,   111,    -1,  1093,    -1,
     115,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,   128,    -1,    -1,    -1,   132,    -1,   134,
      -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,     5,
     145,   146,    -1,     9,    10,    -1,   151,    -1,   153,    -1,
      16,    17,   157,  1868,  1869,    -1,    22,    23,    24,    25,
      -1,  1876,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,   184,
      -1,   186,    -1,    -1,    -1,    -1,    -1,    -1,   193,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,     7,  1183,     9,
      10,    -1,  1917,    -1,    -1,    -1,    16,    17,  1923,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,  1948,    -1,   771,    -1,    -1,    -1,   775,
      -1,    -1,  1957,    -1,     5,    -1,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,  1974,
    1975,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   822,  2002,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2010,    -1,    -1,   834,    -1,
      -1,    -1,    -1,    -1,    -1,  2020,    -1,     5,    -1,    -1,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,  2036,    -1,  2038,    22,    23,    24,    25,  1313,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,    -1,    -1,    -1,   881,   882,   883,   884,    -1,
     886,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,  2094,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,  1377,    -1,    -1,    -1,    -1,    -1,    -1,   404,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,   950,     9,   952,   953,   954,   955,
      -1,    -1,    16,    17,    -1,  2140,    -1,    -1,    22,    23,
    2145,    25,    -1,    -1,    28,    29,    30,    31,    32,    -1,
      -1,  2156,  2157,    37,    -1,    -1,  2161,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2171,    -1,  1443,    -1,
    1445,  2176,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1011,    -1,    -1,    -1,  1464,
    1465,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1475,    -1,    -1,    -1,    -1,    -1,  1481,  1033,  1483,    -1,
      -1,  1486,    -1,   508,    -1,    -1,    -1,  1043,    -1,    -1,
      -1,    -1,    -1,  1498,    -1,  2230,    -1,  1502,  1503,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1064,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1524,
      -1,    -1,    -1,    -1,  1080,    -1,  1531,    -1,  1084,  1085,
    2265,    -1,    -1,    -1,    -1,  1540,  1541,  1542,    -1,  1544,
    1545,    -1,    -1,  1548,    -1,    -1,  2281,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1562,    -1,    -1,
      -1,  1566,    -1,    -1,  1569,  1570,  1571,    -1,  1573,  1574,
    1575,    -1,    -1,  1578,  1579,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2334,
    2335,    -1,    -1,  2338,    -1,  2340,    -1,    -1,    -1,    -1,
      -1,  1616,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2356,  2357,    -1,  2359,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2369,    -1,    -1,    -1,    -1,    -1,
    2375,    -1,    -1,  1648,  1200,  1201,     5,    -1,    -1,     8,
       9,    10,  2387,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,  2421,  2422,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,  2433,     9,
      10,  2436,  1707,  1708,  1709,  2440,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,  2469,    -1,    -1,    -1,  2473,    -1,
      -1,    -1,  2477,    -1,    -1,    -1,  2481,    -1,  2483,    -1,
      -1,  1756,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2495,  2496,  2497,    -1,    -1,    -1,    -1,    -1,    -1,  1325,
    1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,  1334,  1335,
    1336,  1337,  1338,  1339,  1340,  1341,  1342,  1343,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1359,    -1,    -1,    -1,    -1,    -1,     5,
    1366,    -1,  1368,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,  1378,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,  1409,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,     5,    -1,
       7,    -1,     9,    10,  1889,  1890,  1891,  1892,  1893,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
     925,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1478,    -1,    -1,    -1,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,  1939,    -1,  1492,    16,    17,    -1,
    1945,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,  1513,    37,    38,
       5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,  1978,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,  2000,    -1,    -1,    -1,    -1,
    1025,    -1,    -1,  1559,    -1,     5,  2011,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,  2032,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,     5,    -1,  1600,    -1,     9,    10,    -1,    -1,
      -1,  2056,  2057,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,     5,  1633,  2083,    -1,
       9,    10,    -1,    -1,  1640,    -1,    -1,    16,    17,    -1,
    1646,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,  2117,  1669,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1681,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1689,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2147,  1699,    -1,  2150,  1702,  2152,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
      -1,  1717,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,  1728,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,  1742,    -1,    -1,    -1,
      -1,    -1,  1748,    -1,    -1,    -1,    -1,    -1,  1754,    -1,
       5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,  2219,  2220,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,  1290,    -1,    -1,     5,    -1,
       7,    -1,     9,    10,    -1,    -1,    -1,    -1,  2283,    16,
      17,    -1,  2287,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,     5,    -1,    -1,    -1,     9,    10,  1864,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,  1880,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2349,  2350,  2351,  2352,  2353,    -1,
      -1,    -1,    -1,  2358,     5,    -1,     7,    -1,     9,    10,
      -1,    -1,    -1,  2368,    -1,    16,    17,    -1,  1924,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,  1944,    -1,
    1946,    -1,    -1,    -1,  1950,    -1,    -1,    -1,    -1,    -1,
    2405,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1973,    -1,    -1,
    1976,    -1,  2427,  2428,    -1,    -1,  2431,     5,    -1,    -1,
      -1,     9,    10,  2438,    -1,    -1,    -1,    -1,    16,    17,
      -1,  1997,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,
    2475,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,     5,    -1,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
    2096,  2097,    -1,    16,    17,    -1,    -1,    -1,  2104,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,     5,
      -1,    -1,    -1,     9,    10,    -1,    -1,    -1,    -1,  2135,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,  2154,    35,
       5,    37,    38,  2159,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,  2169,  2170,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2199,    -1,    -1,     5,    -1,    -1,     8,
       9,    10,    -1,  2209,  2210,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,  2224,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2245,
      -1,  2247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
    2256,    -1,    -1,     9,    10,  2261,    -1,    -1,  2264,    -1,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,  2277,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,     5,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,  2344,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2380,    -1,  2382,    -1,    -1,    -1,
    2386,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2398,  2399,     5,    -1,    -1,  2403,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,  2413,    -1,  2415,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2449,    -1,  2451,    -1,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,    -1,    19,  2463,    21,  2465,
      23,    24,    -1,    26,    -1,    -1,    -1,    30,    -1,    32,
      33,    -1,    -1,    36,    37,    38,    -1,    40,    -1,    42,
      43,    -1,  2488,    46,    -1,    -1,  2492,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,  2502,    60,    61,    -1,
      -1,    64,    65,    66,    -1,    68,    -1,    70,    -1,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    92,
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
      -1,   194,   195,   196,   197,   198,   199,   200,   201,    -1,
       5,    -1,     6,     8,     9,    10,    -1,    -1,    -1,    13,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    -1,    48,    49,    50,    51,    52,    53,
      -1,   254,    56,    57,   257,    -1,   259,    61,    62,    63,
      -1,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
      74,    75,    76,    77,    -1,    79,    80,    81,    82,    83,
      84,    -1,    -1,    87,    88,    89,    90,    91,    -1,    -1,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    -1,   117,    -1,   119,   120,    -1,   122,   123,
     124,    -1,    -1,   127,    -1,    -1,   130,   131,    -1,   133,
     134,   135,   136,    -1,   138,   139,   140,   141,   142,   143,
     144,   145,   146,    -1,    -1,    -1,    -1,    -1,   152,   153,
     154,   155,    -1,    -1,    -1,    -1,   160,    -1,    -1,   163,
     164,    -1,    -1,   167,   168,    -1,   170,    -1,    -1,    -1,
     174,    -1,   176,    -1,   178,    -1,    -1,    -1,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,    -1,   193,
     194,   195,    -1,   197,    -1,   199,   200,    -1,   202,    -1,
     204,   205,   206,   207,    -1,    -1,   210,   211,   212,    -1,
     214,   215,   216,    -1,   218,   219,   220,    -1,   222,    -1,
     224,   225,   226,   227,   228,    -1,   230,    -1,   232,   233,
      -1,    -1,   236,   237,   238,    -1,    -1,   241,   242,    -1,
     244,   245,    -1,   247,   248,    -1,    -1,    -1,   252,   253,
      -1,    -1,   256,    -1,    -1,   259,    -1,    -1,    -1,   263,
     264,    -1,    -1,   267,   268,   269,    -1,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,    -1,   283,
      -1,    -1,   286,    -1,    -1,    -1,   290,   291,   292,   293,
     294,    -1,   296,   297,    -1,    -1,   300,   301,   302,   303,
      -1,    -1,    -1,    -1,   308,   309,   310,   311,   312,   313,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   321,    -1,    -1,
     324,   325,   326,   327,   328,    -1,    -1,    -1,   332,   333,
     334,   335,   336,   337,     5,   339,   340,    -1,     9,    10,
     344,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,   598,   599,    28,    29,    30,
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
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      38,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   354,     0,     1,   150,   257,   355,   356,   116,     6,
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
     311,   312,   313,   321,   324,   325,   326,   327,   328,   332,
     333,   334,   335,   336,   337,   339,   340,   344,   357,   359,
     362,   374,   375,   379,   380,   381,   387,   388,   389,   390,
     392,   393,   395,   397,   398,   399,   400,   407,   408,   409,
     410,   411,   412,   416,   417,   418,   422,   423,   461,   463,
     476,   519,   520,   522,   523,   529,   530,   531,   532,   539,
     540,   541,   542,   544,   547,   551,   552,   553,   554,   555,
     556,   562,   563,   564,   575,   576,   577,   579,   582,   585,
     590,   591,   593,   595,   597,   600,   601,   625,   626,   637,
     638,   639,   640,   645,   648,   651,   654,   655,   704,   705,
     706,   707,   708,   709,   710,   711,   717,   719,   721,   723,
     725,   726,   727,   728,   729,   732,   734,   735,   736,   739,
     740,   744,   745,   747,   748,   749,   750,   751,   752,   753,
     756,   761,   766,   768,   769,   770,   771,   773,   774,   775,
     776,   777,   778,   795,   798,   799,   800,   801,   807,   810,
     815,   816,   817,   820,   821,   822,   823,   824,   825,   826,
     827,   828,   829,   830,   831,   832,   833,   834,   839,   840,
     841,   842,   843,   853,   854,   855,   857,   858,   859,   860,
     861,   862,   877,    15,   486,   486,   548,   548,   548,   548,
     548,   486,   548,   548,   358,   548,   548,   548,   486,   548,
     486,   548,   548,   486,   548,   548,   548,   485,   548,   486,
     548,   548,     7,    15,   487,    15,   486,   608,   548,   486,
     371,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   129,   364,   528,   528,   548,   548,   548,   486,   548,
     364,   548,   486,   486,   548,   548,   485,   358,   486,   486,
      64,   370,   548,   548,   486,   486,   548,   486,   486,   486,
     486,   486,   548,   425,   548,   548,   548,   364,   462,   358,
     486,   548,   548,   548,   486,   548,   486,   548,   548,   486,
     548,   548,   548,   486,   358,   486,   371,   548,   548,   371,
     548,   486,   548,   548,   548,   486,   548,   548,   486,   548,
     486,   548,   548,   548,   548,   548,   548,    15,   486,   586,
     486,   358,   486,   486,   548,   548,   548,    15,     8,   486,
     486,   548,   548,   548,   486,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   548,   548,   548,   548,   548,   548,   548,   548,   548,
     548,   486,   548,   486,   548,   548,   548,   548,   486,   548,
     548,   548,   548,   548,   548,   548,   548,    15,    15,    15,
     364,   875,    15,   257,   574,   124,   233,   395,    15,   367,
     574,     8,     8,     8,     8,     7,     8,   124,   359,   382,
       8,   364,   396,     8,     8,     8,     8,     8,   543,     8,
     543,     8,     8,     8,     8,   543,   574,     7,   218,   252,
     520,   522,   531,   532,   239,   540,   540,    10,    14,    15,
      16,    17,    27,    34,    36,    64,    92,   149,   201,   364,
     376,   492,   493,   495,   496,   497,   498,   504,   505,   506,
     507,   508,   511,    15,   548,     5,     9,    15,    16,    17,
     129,   494,   496,   504,   558,   572,   573,   548,    15,   558,
     548,     5,   557,   558,   573,   558,     8,     8,     8,     8,
       8,     8,     8,     8,     7,     8,     8,     5,     7,   364,
     635,   636,   364,   628,   487,    15,    15,   149,   475,   364,
     364,   737,   738,     8,   364,   652,   653,   738,   364,   366,
     364,    15,   524,   570,    23,    37,   364,   414,   415,    15,
     364,   598,   364,   666,   666,   364,   649,   650,   364,   527,
     424,    15,   364,   578,   149,   743,   527,     7,   470,   471,
     486,   609,   610,   364,   604,   610,    15,   549,   364,   580,
     581,   527,    15,    15,   527,   743,   528,   527,   527,   527,
     527,   364,   527,   367,   527,    15,   419,   487,   495,   496,
      15,   361,   364,   364,   646,   647,   477,   478,   479,   480,
       8,   667,   733,    15,   364,   592,   364,   583,   584,   571,
      15,    15,   364,   487,    15,   492,   746,    15,    15,   364,
     720,   722,     8,   364,    37,   413,    15,   496,   497,   487,
      15,    15,   549,   475,   487,   496,   364,   712,     5,    15,
     572,   573,   487,   364,   365,   487,   571,    15,   495,   629,
     630,   604,   608,   364,   596,   364,   692,   692,    15,   364,
     594,   712,   492,   503,   487,   371,    15,   364,   698,   698,
     698,   698,   698,     7,   492,   587,   588,   364,   589,   487,
     360,   364,   487,   364,   718,   720,   364,   486,   487,   364,
     464,    15,    15,   571,   364,    15,   610,    15,   610,   610,
     610,   610,   781,   837,   610,   610,   610,   610,   610,   610,
     781,   364,   371,   844,   845,   846,    15,    15,   371,   856,
      15,   492,   492,   492,   492,   491,   492,    15,    15,   371,
     863,   864,   865,   866,   867,   371,   868,   869,   870,   871,
     872,   371,   873,   874,   371,   878,   879,   358,   358,   124,
       5,    21,   364,   368,   369,   363,   371,   364,   364,   364,
     415,     7,   371,   358,   124,   364,   364,     5,    15,   402,
     403,   364,   415,   415,   415,   415,   414,   495,   413,   364,
     364,   419,   426,   427,   429,   430,   548,   548,   239,   405,
     492,   493,   492,   492,   492,   492,     5,     9,    16,    17,
      22,    23,    24,    25,    26,    28,    29,    30,    31,    32,
      33,    35,    37,    38,   376,    15,   246,     3,    15,   246,
     246,    15,   501,   502,    21,   545,   570,   503,     5,     9,
     166,   559,   560,   561,   572,    26,   572,     5,     9,    23,
      37,   494,   571,   572,   571,     8,    15,   496,   565,   566,
      15,   492,   493,   508,   567,   568,   569,   567,   578,   364,
     592,   594,   596,   598,   364,     7,   371,   718,     8,    21,
     630,   415,   517,   492,   240,   543,    15,   371,    15,   469,
       8,   570,     7,   492,   525,   526,   527,    15,   364,   469,
     415,   474,   475,     8,   426,   517,   469,    15,     8,    21,
       5,     7,   472,   473,   492,   364,     8,    21,     5,    58,
      86,   126,   137,   165,   258,   611,   607,   608,   175,   599,
     492,   149,   538,     8,   492,   492,   363,   364,   420,   421,
     495,   500,   364,    26,   364,   533,   534,   536,   367,     8,
       8,    15,   231,   395,   481,   371,     8,   733,   364,   495,
     702,   712,   730,   731,     8,   558,    26,     5,     9,    16,
      17,    22,    23,    24,    25,    28,    29,    30,    31,    32,
      33,    34,    35,    37,    38,   376,   377,   378,   364,   371,
     385,   495,   492,    15,   371,   364,   364,   495,   495,   518,
       8,   667,   724,   364,   495,   656,   364,   459,   460,   538,
     415,    18,   571,   572,   571,   391,   394,   635,   630,     7,
     608,   610,   702,   712,   713,   714,   414,   415,   453,   454,
      62,   495,   757,    15,    15,     7,     8,    21,   586,   415,
     367,   415,   469,     8,   665,   689,    21,   371,   364,     8,
     492,   492,   469,   495,   543,   802,   495,   287,   814,   814,
     543,   811,   814,    15,   543,   779,   543,   818,   779,   779,
     543,   796,   543,   808,   469,   147,   148,   180,   314,   315,
     318,   319,   372,   847,   848,   849,     8,    21,   496,   671,
     850,    21,   850,   372,   848,   371,   754,   755,     8,     8,
       8,     8,   495,   498,   499,   772,   656,   183,   191,   208,
       8,    21,    41,   209,   228,     8,    21,   338,   341,   342,
     343,     8,    21,   244,   330,   345,   346,   347,     8,    21,
     364,   360,   358,     8,    21,   213,   372,   469,    44,    87,
      93,   119,   143,   145,   178,   183,   187,   191,   194,   216,
     230,   236,   383,   384,   386,   364,   358,   486,   549,   570,
     396,   469,   543,   543,     8,    37,    15,   364,   432,   437,
     371,    15,   512,    21,     8,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   492,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   570,    64,   129,   488,   490,   570,
     495,   506,   509,    64,   509,   503,     8,    21,     5,   492,
     546,   561,     8,    21,     5,     9,   492,    21,   492,   572,
     572,   572,   572,   572,    21,   565,   565,     8,   492,   493,
     568,   569,     8,     8,     8,   469,   469,   486,    43,    67,
      82,    87,    88,    94,   228,   259,   303,   639,   636,   371,
     499,   515,    21,   364,    15,   491,    67,   470,   653,   492,
       7,     8,    21,   545,    37,     8,    21,   650,   495,   498,
     514,   516,   570,   741,   472,     7,   469,   610,    15,    15,
      15,    15,    15,    15,   599,   610,   364,    21,   550,   581,
      21,    21,    15,     8,    21,     8,   502,   496,     8,   535,
      26,   363,   647,   478,   129,   482,   483,   484,   400,   169,
     208,   282,   371,    15,     7,     8,    21,   584,   567,    21,
      21,   147,   148,   180,    21,    18,    21,     7,   492,   510,
     175,   323,    37,     8,    21,   371,     8,    21,    26,     8,
      21,   550,   492,    21,   455,   456,   455,    21,     7,   610,
     599,    15,     7,     8,    21,     8,    15,    15,    26,   699,
     700,   702,   491,   492,   588,   371,     8,   689,     8,   665,
     396,   386,   373,    21,    21,    21,   610,   543,    21,   610,
     543,   838,   610,   543,   610,   543,   610,   543,   610,   543,
      15,    15,    15,    15,    15,    15,   371,   846,     8,    21,
      21,   182,   315,   318,     8,    21,   371,   371,   371,   492,
      15,    15,     8,    21,    21,    15,    15,    15,   864,    15,
      15,    15,   869,    15,    15,    15,   874,    15,    15,    15,
      15,    15,   879,   367,   364,   369,    15,   401,   402,   469,
     486,    15,     7,     8,   364,   469,    15,   506,     5,   404,
     492,   561,   415,   495,   429,    15,    16,    17,    27,    36,
      59,    64,    92,   149,   201,   428,   430,   440,   441,   442,
     443,   444,   445,   446,   447,   432,   437,   438,   439,    15,
     433,   434,    62,   492,   567,   493,   488,    21,     8,   489,
     492,   510,   561,     7,   570,   475,   492,   570,     8,   566,
      21,     8,     8,     8,   493,   569,   493,   569,   493,   569,
     364,   255,     8,    21,   475,   474,    21,     7,    21,   492,
     525,    21,   475,   543,     8,    21,   561,   742,     8,    21,
     473,   492,   611,   570,    15,   613,   364,   612,   612,   492,
     612,   469,   610,   239,   527,   491,   421,   421,   364,   492,
     534,    21,   492,   510,     8,    21,    16,    15,    15,    15,
     491,   730,   731,   487,   495,   762,     7,   492,     7,    21,
      21,   364,   606,   496,   495,   495,   610,   657,   492,   460,
     543,     8,    47,   177,   364,   458,   371,   627,   629,   599,
       7,     7,   492,   715,   716,   713,   714,   454,   492,     5,
     613,   758,   759,   765,   492,   623,     8,    21,    15,    21,
      71,   208,   371,   371,   487,   172,   364,   467,   468,   496,
     191,   208,   282,   285,   290,   298,   782,   783,   784,   791,
     803,   804,   805,   610,   266,   812,   813,   814,   610,    37,
     495,   835,   836,    84,   265,   289,   299,   304,   780,   782,
     783,   784,   785,   786,   787,   789,   790,   791,   610,   782,
     783,   784,   785,   786,   787,   789,   790,   791,   804,   805,
     819,   610,   782,   783,   784,   791,   797,   610,   782,   783,
     809,   610,   850,   850,   850,   371,   851,   852,   850,   850,
     496,   755,   330,   315,   331,   570,   488,   499,   459,   671,
     371,   693,   699,   713,   699,   656,   656,   499,   876,   371,
     880,   881,   656,   656,   492,   371,   882,   364,    18,    26,
     406,    15,   385,     7,   371,   401,   550,   550,   405,     5,
     492,   443,   444,   445,   448,   444,   446,   444,   446,   246,
     246,   246,   246,   246,     8,    37,   364,   431,   495,     5,
     433,   434,     8,    15,    16,    17,   149,   364,   431,   435,
     436,   449,   450,   451,   452,    15,   434,    15,    21,   513,
      21,    21,   502,   570,   492,   503,   546,   560,   572,   536,
     537,   493,   537,   537,   537,   469,   364,   631,   634,   570,
       8,    21,     7,   405,   492,   570,   492,   570,   561,   624,
     492,   614,   615,    21,    21,    21,    21,     8,     8,   254,
     521,   527,    21,   483,   484,   671,   671,   671,    21,    21,
     364,    15,    21,   492,     7,     7,   492,   469,   173,     8,
     661,   662,   663,   664,   665,   667,   668,   669,   672,   674,
     675,   676,   689,   697,   536,   456,    15,    15,   457,   255,
       8,     7,     8,    21,    21,    21,     8,    21,    21,   700,
     701,    15,    15,   364,   364,   465,   466,   468,    18,     8,
      26,   781,    15,   781,   781,    15,   610,   803,   781,   610,
     812,   364,     8,    21,    15,   781,    15,   781,    15,   610,
     780,   610,   819,   610,   797,   610,   809,    21,    21,    21,
     316,   317,     8,    21,    21,    21,    15,    15,   488,    21,
      21,    21,    22,    24,    33,    35,   158,   159,   161,   162,
     192,   234,   247,   694,   695,   696,     8,    21,    21,    21,
      21,    21,    21,     8,    21,   315,   350,     8,    21,    21,
      21,    21,   348,   349,     8,    21,   492,   492,   641,   642,
      21,   384,   406,     5,   492,   396,     8,    21,     8,   509,
     509,   509,   509,   509,   440,     5,    15,   430,   441,   434,
     364,   431,   439,   449,   450,   450,     8,    21,     7,    16,
      17,     5,    37,     9,   449,   492,    20,   502,   489,    21,
      26,    21,    21,    21,    21,    15,   499,   561,   475,   652,
     487,   514,   561,   742,   492,    21,     7,     8,    21,   492,
     371,    15,    21,    21,    21,     7,   763,   764,   765,   492,
     492,     7,   495,   658,   371,   663,    26,   458,    26,   377,
     631,   629,   364,   602,   603,   604,   605,   716,   759,   610,
      78,   587,   364,   666,   713,   690,     8,   364,   468,   492,
     610,   792,   371,   610,   610,   837,   495,   835,   371,   492,
     492,   610,   610,   610,   610,   852,   671,   495,    21,    15,
      15,   371,   499,   881,   492,     8,    21,     7,    21,    21,
     570,   448,   441,   570,   431,    26,    21,   449,   436,   450,
     450,   451,   451,   451,    21,   492,     5,   492,   510,   632,
     633,   495,     8,   671,   495,     8,   492,   615,   371,    21,
     254,   492,     8,    21,   492,    15,    41,   135,   191,   209,
     221,   223,   224,   226,   229,   320,   322,   492,   457,    21,
      21,    15,     8,   132,   760,    21,    21,     7,    21,   692,
     694,   466,     5,    16,    17,    22,    24,    33,    35,    37,
     159,   162,   247,   305,   306,   307,   794,    21,    94,   230,
     284,   295,   806,    37,   191,   288,   299,   788,    21,    21,
      21,    21,   496,   671,   694,    21,     7,     7,   404,    21,
     488,   435,   449,    21,     8,     8,    21,   475,   561,   255,
      15,    21,   764,     5,   492,   659,   660,    15,   677,    15,
      15,    15,    15,    15,   698,   698,    15,    15,    15,     8,
     491,   603,   702,   703,    15,   713,   691,   691,     7,     8,
      21,   838,    21,     8,    21,     8,     7,   405,    21,    21,
     492,   633,   492,   364,   616,   617,   492,     8,    21,   610,
     677,   712,   730,   671,   712,   713,   702,   699,   492,   492,
     670,   658,   673,   492,    21,     8,   371,    21,     7,     8,
      21,   671,   793,   492,   371,   492,   496,   364,   643,   644,
      21,     8,    15,    21,   660,   148,   180,   678,     7,    21,
      21,     7,    21,    15,    21,    21,     8,    21,     8,    21,
       8,   702,    78,   693,   693,    21,   329,    21,     8,   492,
      40,   492,   618,   619,   765,     7,     7,   679,   680,   702,
     730,   713,   587,   492,   658,   492,    21,    21,    21,    15,
     644,   364,   620,     8,    21,     8,    21,    15,    21,    21,
      21,     8,   491,    17,   621,   622,   619,   680,   492,   681,
     682,    21,   492,    21,   623,    17,     7,     8,    21,     8,
     767,   623,   492,   682,    15,   371,   371,   683,   684,   685,
     686,   687,   182,   318,   128,   157,   217,     8,    21,     7,
       7,    15,   688,   688,   688,   684,   371,   686,   687,   371,
     687,   490,     7,    21,   687
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
#line 783 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 785 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 789 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 791 "gram1.y"
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
#line 805 "gram1.y"
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
#line 836 "gram1.y"
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
#line 845 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 851 "gram1.y"
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
#line 871 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 880 "gram1.y"
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
#line 896 "gram1.y"
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
#line 908 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 918 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 925 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 931 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 936 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 941 "gram1.y"
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
#line 965 "gram1.y"
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
#line 991 "gram1.y"
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
#line 1006 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 1008 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 1010 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 1014 "gram1.y"
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
#line 1031 "gram1.y"
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
#line 1045 "gram1.y"
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
#line 1069 "gram1.y"
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
#line 1085 "gram1.y"
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
#line 1099 "gram1.y"
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
#line 1117 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1119 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1126 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1129 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1131 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1137 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1139 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1146 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1148 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1150 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1155 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1159 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1163 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1169 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1178 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1182 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1187 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1208 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1213 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1218 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1225 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1241 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1245 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1253 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1261 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1270 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1278 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1282 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1284 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1288 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1290 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1292 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1294 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1296 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1298 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1300 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1302 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1304 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1306 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1308 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1310 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1312 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1314 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1316 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1318 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1320 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1322 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1327 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1336 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1346 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1354 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1364 "gram1.y"
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
#line 1385 "gram1.y"
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
#line 1404 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1406 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1408 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1412 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1414 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1418 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1422 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1424 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1428 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1434 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1438 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1440 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1444 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1448 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1452 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1456 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1460 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1466 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1470 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1474 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1480 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1485 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1492 "gram1.y"
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
#line 1503 "gram1.y"
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
#line 1516 "gram1.y"
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
#line 1527 "gram1.y"
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
#line 1540 "gram1.y"
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
#line 1550 "gram1.y"
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
#line 1563 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1568 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1574 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1578 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1583 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1588 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1594 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1598 "gram1.y"
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
#line 1608 "gram1.y"
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
#line 1621 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1626 "gram1.y"
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
#line 1645 "gram1.y"
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
#line 1671 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1673 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1685 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1692 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1693 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1694 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1695 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1696 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1697 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1698 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1703 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1705 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1709 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1711 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1718 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1722 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1724 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1726 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1734 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1741 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1747 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1753 "gram1.y"
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
#line 1762 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1770 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1783 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1785 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1788 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1792 "gram1.y"
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
#line 1807 "gram1.y"
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
#line 1823 "gram1.y"
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
#line 1841 "gram1.y"
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
#line 1861 "gram1.y"
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
#line 1881 "gram1.y"
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
#line 1903 "gram1.y"
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
#line 1920 "gram1.y"
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
#line 1938 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1945 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1952 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1959 "gram1.y"
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
#line 1972 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1979 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1986 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1997 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 2001 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 2003 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 2008 "gram1.y"
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
#line 2026 "gram1.y"
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
#line 2037 "gram1.y"
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
#line 2049 "gram1.y"
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
#line 2061 "gram1.y"
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
#line 2075 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2081 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2088 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2094 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2100 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2108 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2115 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2134 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2148 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2152 "gram1.y"
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
#line 2197 "gram1.y"
    {;;}
    break;

  case 223:
#line 2201 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2205 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2211 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2215 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2219 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2221 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2225 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2227 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2231 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2235 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2237 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2241 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2243 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2245 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2250 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2274 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2319 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2321 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2328 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2335 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2342 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2351 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2353 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2355 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2359 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2361 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2365 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2374 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2381 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2388 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2390 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2394 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2398 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2404 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2406 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2410 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2414 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2419 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2426 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2433 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2443 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2445 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2449 "gram1.y"
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
#line 2461 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2464 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2473 "gram1.y"
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
#line 2486 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2492 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2498 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2504 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2512 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2522 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2524 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2528 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 306:
#line 2530 "gram1.y"
    {  PTR_HASH oldhash,copyhash;
	       PTR_SYMB oldsym, newsym;
	       PTR_LLND m;

	       oldhash = just_look_up_sym_in_scope(module_scope, (yyvsp[(1) - (1)].hash_entry)->ident);
	       if (oldhash == HSNULL) {
                  errstr("Unknown identifier %s.", (yyvsp[(1) - (1)].hash_entry)->ident,309);
	          (yyval.ll_node)= LLNULL;
	       }
	       else {
                 oldsym = oldhash->id_attr;
                 copyhash=just_look_up_sym_in_scope(cur_scope(), (yyvsp[(1) - (1)].hash_entry)->ident);
	         if( copyhash && copyhash->id_attr && copyhash->id_attr->entry.Template.tag==module_scope->id)
                 {
                   newsym = copyhash->id_attr;
                   newsym->entry.Template.tag = 0;
                 }
                 else
                 {
	           newsym = make_local_entity((yyvsp[(1) - (1)].hash_entry), oldsym->variant, oldsym->type,LOCAL);
	           /* copies data in entry.Template structure and attr */
	           copy_sym_data(oldsym, newsym);	         
	             /*newsym->entry.Template.base_name = oldsym;*//*19.03.03*/
                 }
	  	/* l = make_llnd(fi, VAR_REF, LLNULL, LLNULL, oldsym);*/
		 m = make_llnd(fi, VAR_REF, LLNULL, LLNULL, newsym);
		 (yyval.ll_node) = make_llnd(fi, RENAME_NODE, m, LLNULL, oldsym);
 	      }
            ;}
    break;

  case 307:
#line 2563 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2565 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2569 "gram1.y"
    {  PTR_HASH oldhash,copyhash;
	       PTR_SYMB oldsym, newsym;
	       PTR_LLND l, m;

	       oldhash = just_look_up_sym_in_scope(module_scope, (yyvsp[(3) - (3)].hash_entry)->ident);
	       if (oldhash == HSNULL) {
                  errstr("Unknown identifier %s", (yyvsp[(3) - (3)].hash_entry)->ident,309);
	          (yyval.ll_node)= LLNULL;
	       }
	       else {
                 oldsym = oldhash->id_attr;
                 copyhash = just_look_up_sym_in_scope(cur_scope(), (yyvsp[(3) - (3)].hash_entry)->ident);
	         if(copyhash && copyhash->id_attr && copyhash->id_attr->entry.Template.tag==module_scope->id)
                 {
                    delete_symbol(copyhash->id_attr);
                    copyhash->id_attr = SMNULL;
                 }
                   newsym = make_local_entity((yyvsp[(1) - (3)].hash_entry), oldsym->variant, oldsym->type, LOCAL);
	           /* copies data in entry.Template structure and attr */
	           copy_sym_data(oldsym, newsym);	
                         
	           /*newsym->entry.Template.base_name = oldsym;*//*19.03.03*/
	  	 l  = make_llnd(fi, VAR_REF, LLNULL, LLNULL, oldsym);
		 m  = make_llnd(fi, VAR_REF, LLNULL, LLNULL, newsym);
		 (yyval.ll_node) = make_llnd(fi, RENAME_NODE, m, l, SMNULL);
 	      }
            ;}
    break;

  case 310:
#line 2607 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2609 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2612 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2613 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2618 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2622 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2630 "gram1.y"
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
#line 2639 "gram1.y"
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
#line 2648 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2658 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2667 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2669 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2673 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2681 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2696 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2703 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2705 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2709 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2724 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2725 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2729 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2731 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2743 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2745 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2749 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2755 "gram1.y"
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
#line 2767 "gram1.y"
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
#line 2778 "gram1.y"
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
#line 2795 "gram1.y"
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
#line 2833 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2835 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2839 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2841 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2843 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2854 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2858 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2864 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2866 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2870 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2872 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2874 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2878 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2880 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2884 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2886 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2888 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2890 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2892 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2894 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2896 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2898 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2900 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2902 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2904 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2906 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2908 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2910 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2912 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2914 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2916 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2918 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2920 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2922 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2924 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2926 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2928 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2931 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2932 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2944 "gram1.y"
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
#line 3018 "gram1.y"
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
#line 3030 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3032 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3036 "gram1.y"
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
#line 3167 "gram1.y"
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
#line 3217 "gram1.y"
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
#line 3261 "gram1.y"
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
#line 3303 "gram1.y"
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
#line 3361 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3363 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3365 "gram1.y"
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
#line 3405 "gram1.y"
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
#line 3447 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3457 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3459 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3463 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3467 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3469 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3473 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3475 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3481 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3483 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3489 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3499 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3505 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3512 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3518 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3526 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3534 "gram1.y"
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
#line 3550 "gram1.y"
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
#line 3560 "gram1.y"
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
#line 3573 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3580 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3582 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3605 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3607 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3609 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3611 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3613 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3615 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3617 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3619 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3622 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3622 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3623 "gram1.y"
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
#line 3637 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3639 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3662 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3664 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3666 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3682 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3684 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3686 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3699 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3703 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3705 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3713 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3715 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3717 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3719 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3773 "gram1.y"
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
#line 3795 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3808 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3817 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3820 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3870 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3876 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3881 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3899 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3901 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3903 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3905 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3907 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3910 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3916 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3918 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3920 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3923 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3925 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3927 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3954 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3963 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3971 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3973 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3975 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3980 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3987 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3995 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3997 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 4001 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 4004 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 4006 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 4010 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 4016 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 4018 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 4020 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 4022 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4026 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4028 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4036 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4038 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4044 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4046 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4050 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4054 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4075 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4078 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4082 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4084 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4091 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4095 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4097 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4113 "gram1.y"
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
#line 4126 "gram1.y"
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
#line 4149 "gram1.y"
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
#line 4172 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4174 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4181 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4183 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4185 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4187 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4189 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4194 "gram1.y"
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
                       replace_symbol_in_expr(s3,(yyvsp[(4) - (4)].ll_node));
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
#line 4270 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4282 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4289 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4292 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4294 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4303 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4310 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4317 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4325 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4330 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4335 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4338 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4341 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4344 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4347 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4350 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4368 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4372 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4377 "gram1.y"
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
#line 4396 "gram1.y"
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
#line 4415 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4423 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4427 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4432 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4439 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4441 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4443 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4446 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4447 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4458 "gram1.y"
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
#line 4473 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4477 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4485 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4488 "gram1.y"
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
#line 4498 "gram1.y"
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
#line 4511 "gram1.y"
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
#line 4524 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4527 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 546:
#line 4529 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4532 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 548:
#line 4535 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 549:
#line 4539 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 550:
#line 4548 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 551:
#line 4551 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 552:
#line 4555 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 553:
#line 4557 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4563 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 555:
#line 4567 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4569 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4571 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 558:
#line 4578 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 559:
#line 4582 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4584 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4588 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, (yyvsp[(4) - (4)].ll_node), LLNULL);;}
    break;

  case 562:
#line 4590 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, (yyvsp[(5) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), LLNULL);;}
    break;

  case 563:
#line 4594 "gram1.y"
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

  case 564:
#line 4613 "gram1.y"
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

  case 565:
#line 4629 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 566:
#line 4640 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 567:
#line 4647 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 568:
#line 4649 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 569:
#line 4653 "gram1.y"
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

  case 570:
#line 4679 "gram1.y"
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

  case 571:
#line 4694 "gram1.y"
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

  case 572:
#line 4709 "gram1.y"
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

  case 573:
#line 4726 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 574:
#line 4734 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 575:
#line 4743 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 576:
#line 4751 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 577:
#line 4756 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 578:
#line 4761 "gram1.y"
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

  case 579:
#line 4783 "gram1.y"
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

  case 580:
#line 4799 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 581:
#line 4801 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 582:
#line 4805 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 583:
#line 4807 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 584:
#line 4814 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 585:
#line 4816 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 586:
#line 4818 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 587:
#line 4822 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4824 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4826 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4828 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4830 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 592:
#line 4832 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 593:
#line 4836 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 594:
#line 4839 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 595:
#line 4842 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4848 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 597:
#line 4854 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 598:
#line 4862 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 599:
#line 4866 "gram1.y"
    { startioctl();;}
    break;

  case 600:
#line 4874 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4876 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 602:
#line 4880 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 603:
#line 4882 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 604:
#line 4884 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4889 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4894 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 607:
#line 4899 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4904 "gram1.y"
    {
	      if((yyvsp[(1) - (2)].token) == SUBT_OP)
		{
		  (yyval.ll_node) = make_llnd(fi,SUBT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
		  set_expr_type((yyval.ll_node));
		}
	      else	(yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);
	    ;}
    break;

  case 609:
#line 4913 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 610:
#line 4918 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 611:
#line 4923 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 612:
#line 4925 "gram1.y"
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

  case 676:
#line 5008 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 677:
#line 5010 "gram1.y"
    { PTR_SYMB s;
                if((yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2)
                {
                  s = (yyvsp[(3) - (3)].ll_node)->entry.Template.ll_ptr1->entry.Template.symbol;
                  s->attr = s->attr | COMMON_BIT;
                }
	        add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	      ;}
    break;

  case 678:
#line 5021 "gram1.y"
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

  case 679:
#line 5042 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 680:
#line 5046 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 681:
#line 5048 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 682:
#line 5052 "gram1.y"
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

  case 683:
#line 5065 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 684:
#line 5069 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 685:
#line 5071 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 686:
#line 5075 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
              else
                s->attr = s->attr | INHERIT_BIT;        
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 687:
#line 5086 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 688:
#line 5097 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 689:
#line 5101 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 690:
#line 5103 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 691:
#line 5107 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 692:
#line 5109 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 693:
#line 5111 "gram1.y"
    {
            if(parstate!=INEXEC) 
               err("Illegal shadow width specification", 56);  
            (yyval.ll_node) = make_llnd(fi,SHADOW_NAMES_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
          ;}
    break;

  case 694:
#line 5126 "gram1.y"
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

  case 695:
#line 5138 "gram1.y"
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

  case 696:
#line 5158 "gram1.y"
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

  case 697:
#line 5178 "gram1.y"
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

  case 698:
#line 5200 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 699:
#line 5206 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 700:
#line 5215 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 701:
#line 5223 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 702:
#line 5229 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 703:
#line 5237 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 704:
#line 5244 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 705:
#line 5250 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 706:
#line 5259 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 707:
#line 5263 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 708:
#line 5269 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 709:
#line 5277 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 710:
#line 5291 "gram1.y"
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

  case 711:
#line 5304 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 712:
#line 5310 "gram1.y"
    { PTR_LLND q;
             if(!(yyvsp[(4) - (5)].ll_node))
               err("Distribution format list is omitted", 51);
            /* if($6)
               err("NEW_VALUE specification in DISTRIBUTE directive");*/
             q = set_ll_list((yyvsp[(3) - (5)].ll_node),LLNULL,EXPR_LIST);
	     (yyval.bf_node) = get_bfnd(fi,DVM_DISTRIBUTE_DIR,SMNULL,q,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node));
            ;}
    break;

  case 713:
#line 5326 "gram1.y"
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

  case 714:
#line 5341 "gram1.y"
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

  case 715:
#line 5369 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 716:
#line 5371 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 717:
#line 5375 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 718:
#line 5377 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 719:
#line 5381 "gram1.y"
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

  case 720:
#line 5410 "gram1.y"
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

  case 721:
#line 5433 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 722:
#line 5453 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 723:
#line 5455 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 724:
#line 5459 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 725:
#line 5480 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 726:
#line 5482 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 727:
#line 5485 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 728:
#line 5494 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 729:
#line 5498 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 730:
#line 5503 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 731:
#line 5505 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 732:
#line 5507 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 733:
#line 5509 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 734:
#line 5515 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 735:
#line 5517 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 736:
#line 5521 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 737:
#line 5531 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 738:
#line 5535 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 739:
#line 5537 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 740:
#line 5542 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 741:
#line 5544 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 742:
#line 5548 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 743:
#line 5552 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 744:
#line 5558 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 745:
#line 5568 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 746:
#line 5570 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 747:
#line 5574 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 748:
#line 5576 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 749:
#line 5578 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 750:
#line 5585 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 751:
#line 5602 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 752:
#line 5604 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 753:
#line 5608 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 754:
#line 5610 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 755:
#line 5614 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 756:
#line 5621 "gram1.y"
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

  case 757:
#line 5631 "gram1.y"
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

  case 758:
#line 5660 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 759:
#line 5675 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 760:
#line 5682 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 761:
#line 5700 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 762:
#line 5702 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 763:
#line 5706 "gram1.y"
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

  case 764:
#line 5720 "gram1.y"
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

  case 765:
#line 5746 "gram1.y"
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

  case 766:
#line 5759 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 767:
#line 5775 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 768:
#line 5777 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 769:
#line 5780 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 770:
#line 5782 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 771:
#line 5788 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 772:
#line 5792 "gram1.y"
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

  case 773:
#line 5820 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 774:
#line 5822 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 775:
#line 5826 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 776:
#line 5834 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 777:
#line 5840 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 778:
#line 5843 "gram1.y"
    { PTR_SYMB s;
	             PTR_LLND q, r, p;
                     int numdim;
                     if(type_options & PROCESSORS_BIT) {    /* 27.06.18 || (type_options & TEMPLATE_BIT)){ */
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

  case 779:
#line 5901 "gram1.y"
    { PTR_SYMB s;
	             PTR_LLND q, r, p;
                     int numdim;
                    if(type_options & PROCESSORS_BIT) { /*23.10.18  || (type_options & TEMPLATE_BIT)){ */
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

  case 780:
#line 5965 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 781:
#line 5967 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 782:
#line 5970 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 783:
#line 5974 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 784:
#line 5978 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 785:
#line 5982 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 786:
#line 5999 "gram1.y"
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

  case 787:
#line 6011 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 788:
#line 6015 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 789:
#line 6019 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 790:
#line 6029 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 791:
#line 6034 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 792:
#line 6039 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 793:
#line 6046 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 794:
#line 6054 "gram1.y"
    {ndim = 0;;}
    break;

  case 795:
#line 6055 "gram1.y"
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

  case 796:
#line 6066 "gram1.y"
    { PTR_LLND  q;
             if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		q = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL);
	      ++ndim;
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), q, EXPR_LIST);
            ;}
    break;

  case 797:
#line 6077 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 798:
#line 6079 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 799:
#line 6083 "gram1.y"
    {PTR_SYMB s;
           /* s = make_scalar($1,TYNULL,LOCAL);*/
            s = make_array((yyvsp[(1) - (1)].hash_entry),TYNULL,LLNULL,0,LOCAL);
            s->attr = s->attr | DVM_POINTER_BIT;
            if((s->attr & PROCESSORS_BIT) || (s->attr & TASK_BIT) || (s->attr & INHERIT_BIT))
               errstr( "Inconsistent declaration of identifier %s", s->ident, 16);     
            (yyval.ll_node) = make_llnd(fi,VAR_REF,LLNULL,LLNULL,s);
            ;}
    break;

  case 800:
#line 6094 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 801:
#line 6098 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 802:
#line 6100 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 803:
#line 6104 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 804:
#line 6115 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 805:
#line 6119 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 806:
#line 6121 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 807:
#line 6125 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 808:
#line 6137 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 809:
#line 6139 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 810:
#line 6146 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 811:
#line 6148 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 812:
#line 6152 "gram1.y"
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

  case 813:
#line 6168 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 814:
#line 6178 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 815:
#line 6187 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 816:
#line 6189 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 817:
#line 6193 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 818:
#line 6196 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 819:
#line 6201 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
             errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
          (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
          (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
          (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
        ;}
    break;

  case 820:
#line 6211 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 821:
#line 6213 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 822:
#line 6217 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 823:
#line 6219 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 824:
#line 6227 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 825:
#line 6229 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 826:
#line 6233 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 827:
#line 6235 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 839:
#line 6253 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 840:
#line 6258 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 841:
#line 6262 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 842:
#line 6266 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 843:
#line 6270 "gram1.y"
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

  case 844:
#line 6283 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 845:
#line 6287 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 846:
#line 6291 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 847:
#line 6295 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 848:
#line 6298 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 849:
#line 6300 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 850:
#line 6302 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 851:
#line 6306 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 852:
#line 6308 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 853:
#line 6312 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TIE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 854:
#line 6316 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 855:
#line 6318 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 856:
#line 6322 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 857:
#line 6327 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 858:
#line 6331 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 859:
#line 6335 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 860:
#line 6337 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 861:
#line 6341 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 862:
#line 6349 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 863:
#line 6355 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 864:
#line 6361 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 865:
#line 6365 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 866:
#line 6367 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 867:
#line 6371 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 868:
#line 6373 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 869:
#line 6377 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 870:
#line 6389 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 871:
#line 6391 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 872:
#line 6395 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 873:
#line 6399 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 874:
#line 6401 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 875:
#line 6405 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 876:
#line 6407 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 877:
#line 6409 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 878:
#line 6411 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 879:
#line 6413 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 880:
#line 6415 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 881:
#line 6417 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 882:
#line 6421 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 883:
#line 6425 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 884:
#line 6429 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 885:
#line 6433 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 886:
#line 6437 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 887:
#line 6444 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 888:
#line 6450 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 889:
#line 6454 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 890:
#line 6457 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 891:
#line 6461 "gram1.y"
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

  case 892:
#line 6474 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 893:
#line 6476 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 894:
#line 6480 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 895:
#line 6482 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 896:
#line 6487 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6493 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 898:
#line 6499 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 899:
#line 6505 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 900:
#line 6511 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 901:
#line 6517 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 902:
#line 6523 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 903:
#line 6529 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 904:
#line 6535 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 905:
#line 6544 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 906:
#line 6550 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 907:
#line 6567 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 908:
#line 6575 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 909:
#line 6583 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 910:
#line 6585 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 911:
#line 6587 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 912:
#line 6591 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 913:
#line 6595 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 914:
#line 6597 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 915:
#line 6601 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 916:
#line 6603 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 917:
#line 6611 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 918:
#line 6615 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 919:
#line 6626 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 920:
#line 6630 "gram1.y"
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

  case 921:
#line 6648 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 922:
#line 6650 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 923:
#line 6654 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 924:
#line 6656 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 925:
#line 6660 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 926:
#line 6662 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 927:
#line 6666 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 928:
#line 6670 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 929:
#line 6674 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 930:
#line 6683 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 931:
#line 6687 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 932:
#line 6691 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 933:
#line 6696 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 934:
#line 6700 "gram1.y"
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

  case 935:
#line 6712 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 936:
#line 6714 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 937:
#line 6718 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 938:
#line 6723 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 939:
#line 6727 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 940:
#line 6729 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 941:
#line 6733 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 942:
#line 6735 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 943:
#line 6739 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 944:
#line 6744 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 945:
#line 6751 "gram1.y"
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

  case 946:
#line 6774 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 947:
#line 6776 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 948:
#line 6778 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 949:
#line 6780 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 950:
#line 6782 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 951:
#line 6786 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 952:
#line 6797 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 953:
#line 6801 "gram1.y"
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

  case 954:
#line 6816 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 955:
#line 6823 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 956:
#line 6829 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 957:
#line 6831 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 958:
#line 6835 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 959:
#line 6839 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 960:
#line 6847 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 961:
#line 6851 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 962:
#line 6855 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 963:
#line 6863 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 964:
#line 6868 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 965:
#line 6882 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 966:
#line 6884 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 967:
#line 6888 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 968:
#line 6890 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 969:
#line 6899 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 970:
#line 6901 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 971:
#line 6903 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 972:
#line 6905 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 973:
#line 6941 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 974:
#line 6945 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 975:
#line 6949 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 976:
#line 6953 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 977:
#line 6957 "gram1.y"
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

  case 978:
#line 6969 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 979:
#line 6971 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 980:
#line 6975 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 981:
#line 6978 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 982:
#line 6980 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 983:
#line 6984 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 984:
#line 6989 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 985:
#line 6996 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 986:
#line 6999 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 987:
#line 7007 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 988:
#line 7011 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 989:
#line 7015 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 990:
#line 7018 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 991:
#line 7026 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_EXIT_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 992:
#line 7030 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 993:
#line 7034 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 994:
#line 7038 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 995:
#line 7042 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 996:
#line 7046 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 997:
#line 7050 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 998:
#line 7053 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 999:
#line 7055 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1000:
#line 7059 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1001:
#line 7061 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1002:
#line 7063 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1003:
#line 7067 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 1004:
#line 7071 "gram1.y"
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

  case 1005:
#line 7083 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1006:
#line 7085 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1007:
#line 7089 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1008:
#line 7091 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1009:
#line 7095 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1010:
#line 7097 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1011:
#line 7101 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1012:
#line 7105 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1013:
#line 7111 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1014:
#line 7123 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1015:
#line 7125 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1016:
#line 7129 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1017:
#line 7131 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1018:
#line 7135 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1019:
#line 7143 "gram1.y"
    { 
                PTR_LLND q;
                if((yyvsp[(16) - (16)].ll_node))
                  q = make_llnd(fi,ARRAY_OP, (yyvsp[(14) - (16)].ll_node), (yyvsp[(16) - (16)].ll_node), SMNULL);
                else
                  q = (yyvsp[(14) - (16)].ll_node);                  
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_CREATE_DIR,SMNULL,(yyvsp[(3) - (16)].ll_node),(yyvsp[(8) - (16)].ll_node),q); 
              ;}
    break;

  case 1020:
#line 7154 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1021:
#line 7156 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1022:
#line 7158 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1023:
#line 7162 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1024:
#line 7166 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1025:
#line 7168 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1026:
#line 7176 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1027:
#line 7180 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_CREATE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1028:
#line 7183 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1029:
#line 7185 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1030:
#line 7189 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_DELETE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1058:
#line 7223 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1059:
#line 7229 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1060:
#line 7235 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1061:
#line 7241 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1062:
#line 7247 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1063:
#line 7251 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1073:
#line 7268 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1074:
#line 7273 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1075:
#line 7278 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1076:
#line 7284 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1077:
#line 7290 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1078:
#line 7296 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1079:
#line 7301 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1080:
#line 7307 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1081:
#line 7313 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1082:
#line 7319 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1083:
#line 7326 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1084:
#line 7332 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1085:
#line 7338 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1086:
#line 7345 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1088:
#line 7351 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1089:
#line 7357 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1090:
#line 7364 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1091:
#line 7370 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1092:
#line 7376 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1093:
#line 7382 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1094:
#line 7388 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1095:
#line 7394 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1096:
#line 7400 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1097:
#line 7406 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1098:
#line 7412 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1099:
#line 7418 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1100:
#line 7424 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1101:
#line 7430 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1102:
#line 7440 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1103:
#line 7445 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1104:
#line 7451 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1105:
#line 7455 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1110:
#line 7467 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1111:
#line 7475 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1112:
#line 7481 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1113:
#line 7487 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1114:
#line 7492 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1115:
#line 7498 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1116:
#line 7505 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1117:
#line 7511 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1118:
#line 7515 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1125:
#line 7529 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1126:
#line 7538 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1127:
#line 7542 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1128:
#line 7548 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1129:
#line 7555 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1130:
#line 7562 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1131:
#line 7569 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1132:
#line 7578 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1133:
#line 7584 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1134:
#line 7590 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1135:
#line 7594 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1138:
#line 7604 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1139:
#line 7610 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1140:
#line 7616 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1141:
#line 7620 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1144:
#line 7631 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1145:
#line 7637 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1146:
#line 7643 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1147:
#line 7648 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1148:
#line 7656 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1149:
#line 7662 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1150:
#line 7667 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1151:
#line 7674 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1152:
#line 7678 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1164:
#line 7698 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1165:
#line 7703 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1166:
#line 7708 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1167:
#line 7715 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1168:
#line 7720 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1169:
#line 7726 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1170:
#line 7732 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1171:
#line 7737 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1172:
#line 7742 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1173:
#line 7747 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1174:
#line 7751 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1175:
#line 7756 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1176:
#line 7761 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1177:
#line 7765 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1178:
#line 7770 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1179:
#line 7774 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1180:
#line 7780 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1181:
#line 7785 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1182:
#line 7791 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1183:
#line 7796 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1184:
#line 7802 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1185:
#line 7812 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1186:
#line 7816 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1187:
#line 7820 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1188:
#line 7824 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1189:
#line 7829 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1190:
#line 7832 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1198:
#line 7846 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1199:
#line 7850 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1200:
#line 7854 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1201:
#line 7856 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1202:
#line 7858 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1203:
#line 7862 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1204:
#line 7864 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1205:
#line 7866 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1206:
#line 7870 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1207:
#line 7872 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1208:
#line 7876 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1209:
#line 7878 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1210:
#line 7882 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1211:
#line 7885 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1212:
#line 7888 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1213:
#line 7893 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1214:
#line 7895 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1215:
#line 7897 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1216:
#line 7899 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1217:
#line 7901 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1218:
#line 7905 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1219:
#line 7909 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1220:
#line 7914 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1221:
#line 7918 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1222:
#line 7920 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1223:
#line 7924 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1224:
#line 7926 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1225:
#line 7930 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1226:
#line 7934 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1227:
#line 7938 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ROUTINE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1228:
#line 7942 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1229:
#line 7944 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1236:
#line 7956 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1237:
#line 7960 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1238:
#line 7964 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1239:
#line 7968 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1240:
#line 7972 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1241:
#line 7976 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1242:
#line 7978 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1246:
#line 7987 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1247:
#line 7991 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1248:
#line 7995 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PARAMETER_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1249:
#line 7999 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1250:
#line 8001 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1254:
#line 8011 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1255:
#line 8015 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1256:
#line 8019 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1257:
#line 8023 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1258:
#line 8025 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1259:
#line 8029 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1260:
#line 8031 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FISSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1261:
#line 8033 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1262:
#line 8035 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1263:
#line 8038 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_SHRINK_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1264:
#line 8042 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;

  case 1265:
#line 8046 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1266:
#line 8048 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1267:
#line 8052 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_CHECKPOINT_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1268:
#line 8056 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1269:
#line 8058 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1270:
#line 8062 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_TYPE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1271:
#line 8064 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_VARLIST_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1272:
#line 8066 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_EXCEPT_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1273:
#line 8068 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FILES_COUNT_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1274:
#line 8070 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_INTERVAL_OP,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);;}
    break;

  case 1275:
#line 8074 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1276:
#line 8076 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1277:
#line 8080 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1278:
#line 8082 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FLEXIBLE_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1279:
#line 8086 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_TIME_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1280:
#line 8088 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_ITER_OP, LLNULL,LLNULL,SMNULL);;}
    break;


/* Line 1267 of yacc.c.  */
#line 13972 "gram1.tab.c"
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



