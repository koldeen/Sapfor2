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
     BY = 320,
     IO_MODE = 321,
     CP_CREATE = 322,
     CP_LOAD = 323,
     CP_SAVE = 324,
     CP_WAIT = 325,
     FILES = 326,
     VARLIST = 327,
     STATUS = 328,
     EXITINTERVAL = 329,
     TEMPLATE_CREATE = 330,
     TEMPLATE_DELETE = 331,
     SPF_ANALYSIS = 332,
     SPF_PARALLEL = 333,
     SPF_TRANSFORM = 334,
     SPF_NOINLINE = 335,
     SPF_PARALLEL_REG = 336,
     SPF_END_PARALLEL_REG = 337,
     SPF_PRIVATES_EXPANSION = 338,
     SPF_FISSION = 339,
     SPF_SHRINK = 340,
     SPF_CHECKPOINT = 341,
     SPF_EXCEPT = 342,
     SPF_FILES_COUNT = 343,
     SPF_INTERVAL = 344,
     SPF_TIME = 345,
     SPF_ITER = 346,
     SPF_FLEXIBLE = 347,
     BINARY_OP = 350,
     UNARY_OP = 351
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
#define BY 320
#define IO_MODE 321
#define CP_CREATE 322
#define CP_LOAD 323
#define CP_SAVE 324
#define CP_WAIT 325
#define FILES 326
#define VARLIST 327
#define STATUS 328
#define EXITINTERVAL 329
#define TEMPLATE_CREATE 330
#define TEMPLATE_DELETE 331
#define SPF_ANALYSIS 332
#define SPF_PARALLEL 333
#define SPF_TRANSFORM 334
#define SPF_NOINLINE 335
#define SPF_PARALLEL_REG 336
#define SPF_END_PARALLEL_REG 337
#define SPF_PRIVATES_EXPANSION 338
#define SPF_FISSION 339
#define SPF_SHRINK 340
#define SPF_CHECKPOINT 341
#define SPF_EXCEPT 342
#define SPF_FILES_COUNT 343
#define SPF_INTERVAL 344
#define SPF_TIME 345
#define SPF_ITER 346
#define SPF_FLEXIBLE 347
#define BINARY_OP 350
#define UNARY_OP 351




/* Copy the first part of user declarations.  */
#line 349 "gram1.y"

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
#line 430 "gram1.y"
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
#line 891 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 636 "gram1.y"

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
#line 1048 "gram1.tab.c"

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
#define YYLAST   5780

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  352
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  527
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1274
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2522

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   351

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
     342,   343,   344,   345,   346,   347,   348,   349,     1,     2,
     350,   351
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
    2686,  2688,  2690,  2692,  2694,  2696,  2698,  2700,  2702,  2711,
    2718,  2727,  2734,  2736,  2743,  2750,  2757,  2764,  2766,  2770,
    2776,  2778,  2782,  2791,  2798,  2805,  2810,  2816,  2822,  2825,
    2828,  2829,  2831,  2835,  2837,  2842,  2850,  2852,  2856,  2860,
    2862,  2866,  2872,  2876,  2880,  2882,  2886,  2888,  2890,  2894,
    2898,  2902,  2906,  2917,  2926,  2937,  2938,  2939,  2941,  2944,
    2949,  2954,  2961,  2963,  2965,  2967,  2969,  2971,  2973,  2975,
    2977,  2979,  2981,  2983,  2990,  2995,  3000,  3004,  3014,  3016,
    3018,  3022,  3024,  3030,  3036,  3046,  3047,  3049,  3051,  3055,
    3059,  3063,  3067,  3071,  3078,  3082,  3086,  3090,  3094,  3102,
    3108,  3110,  3112,  3116,  3121,  3123,  3125,  3129,  3131,  3133,
    3137,  3141,  3144,  3148,  3153,  3158,  3164,  3170,  3172,  3175,
    3180,  3185,  3190,  3191,  3193,  3196,  3204,  3211,  3215,  3219,
    3227,  3233,  3235,  3239,  3241,  3246,  3249,  3253,  3257,  3262,
    3269,  3273,  3276,  3280,  3282,  3284,  3289,  3295,  3299,  3306,
    3309,  3314,  3317,  3319,  3323,  3327,  3328,  3330,  3334,  3337,
    3340,  3343,  3346,  3356,  3362,  3364,  3368,  3371,  3374,  3377,
    3387,  3392,  3394,  3398,  3400,  3402,  3405,  3406,  3414,  3416,
    3421,  3423,  3427,  3429,  3431,  3433,  3450,  3451,  3455,  3459,
    3463,  3467,  3474,  3484,  3490,  3492,  3496,  3502,  3504,  3506,
    3508,  3510,  3512,  3514,  3516,  3518,  3520,  3522,  3524,  3526,
    3528,  3530,  3532,  3534,  3536,  3538,  3540,  3542,  3544,  3546,
    3548,  3550,  3552,  3554,  3556,  3559,  3562,  3567,  3571,  3576,
    3582,  3584,  3586,  3588,  3590,  3592,  3594,  3596,  3598,  3600,
    3606,  3609,  3612,  3615,  3618,  3621,  3627,  3629,  3631,  3633,
    3638,  3643,  3648,  3653,  3655,  3657,  3659,  3661,  3663,  3665,
    3667,  3669,  3671,  3673,  3675,  3677,  3679,  3681,  3683,  3688,
    3692,  3697,  3703,  3705,  3707,  3709,  3711,  3716,  3720,  3723,
    3728,  3732,  3737,  3741,  3746,  3752,  3754,  3756,  3758,  3760,
    3762,  3764,  3766,  3774,  3780,  3782,  3784,  3786,  3788,  3793,
    3797,  3802,  3808,  3810,  3812,  3817,  3821,  3826,  3832,  3834,
    3836,  3839,  3841,  3844,  3849,  3853,  3858,  3862,  3867,  3873,
    3875,  3877,  3879,  3881,  3883,  3885,  3887,  3889,  3891,  3893,
    3895,  3898,  3903,  3907,  3910,  3915,  3919,  3922,  3926,  3929,
    3932,  3935,  3938,  3941,  3944,  3948,  3951,  3957,  3960,  3966,
    3969,  3975,  3977,  3979,  3983,  3987,  3988,  3989,  3991,  3993,
    3995,  3997,  3999,  4001,  4003,  4007,  4010,  4016,  4021,  4024,
    4030,  4035,  4038,  4041,  4043,  4045,  4049,  4052,  4055,  4058,
    4063,  4068,  4073,  4078,  4083,  4088,  4090,  4092,  4094,  4098,
    4101,  4104,  4106,  4108,  4112,  4115,  4118,  4120,  4122,  4124,
    4126,  4128,  4130,  4135,  4140,  4145,  4148,  4150,  4152,  4156,
    4158,  4160,  4166,  4172,  4174,  4178,  4180,  4182,  4184,  4190,
    4196,  4202,  4204,  4208,  4211,  4217,  4220,  4226,  4232,  4234,
    4236,  4240,  4245,  4247,  4251,  4257,  4263,  4269,  4275,  4283,
    4285,  4289,  4292,  4295,  4298
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     353,     0,    -1,    -1,   353,   354,   116,    -1,   355,   356,
     573,    -1,   355,   373,   573,    -1,   355,   518,   573,    -1,
     355,   133,   369,    -1,   355,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   357,   364,    -1,    57,   357,   365,
      -1,   233,   357,   359,   366,    -1,   358,   233,   357,   359,
     366,    -1,   124,   357,   360,   366,   362,    -1,   361,   366,
     362,    -1,   114,   363,   366,   362,    -1,   164,   357,   363,
      -1,    -1,   202,   370,    -1,   195,   370,    -1,    95,   370,
      -1,   363,    -1,   363,    -1,   394,   124,   357,   363,    -1,
     394,   358,   124,   357,   363,    -1,   358,   124,   357,   363,
      -1,   358,   394,   124,   357,   363,    -1,   370,   371,    -1,
     370,   213,    15,   363,    21,    -1,   129,    -1,    -1,   363,
      -1,    -1,   363,    -1,    -1,    15,    21,    -1,    15,   367,
      21,    -1,   368,    -1,   367,     8,   368,    -1,   363,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   378,    -1,   379,
      -1,   380,    -1,   410,    -1,   406,    -1,   574,    -1,   415,
      -1,   416,    -1,   417,    -1,   475,    -1,   396,    -1,   411,
      -1,   421,    -1,   216,   485,    -1,   216,   485,   486,   452,
      -1,   123,   484,    -1,   183,   485,    15,   458,    21,    -1,
     386,    -1,   387,    -1,   392,    -1,   389,    -1,   391,    -1,
     407,    -1,   408,    -1,   409,    -1,   374,    -1,   462,    -1,
     460,    -1,   388,    -1,   142,   485,    -1,   142,   485,   363,
      -1,   141,   485,    15,   376,    21,    -1,   140,   485,    15,
      26,    21,    -1,   107,   527,    -1,    10,    -1,   375,    -1,
     377,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   485,
     486,   363,    -1,   245,     8,   485,   370,   385,   486,   363,
      -1,   112,   485,    -1,   112,   485,   363,    -1,   394,   381,
     363,   485,   468,   400,   405,    -1,   380,     8,   363,   468,
     400,   405,    -1,    -1,     7,     7,    -1,     8,   370,   382,
       7,     7,    -1,   383,    -1,   382,     8,   370,   383,    -1,
     183,    -1,   385,    -1,    44,    -1,    87,   468,    -1,   119,
      -1,   145,    15,   384,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   370,   148,
      -1,   370,   180,    -1,   370,   147,    -1,   194,    -1,   191,
      -1,   145,   485,    15,   384,    21,   486,   363,    -1,   386,
       8,   363,    -1,   178,   485,   486,   363,    -1,   387,     8,
     363,    -1,   230,   485,   486,   414,    -1,   388,     8,   414,
      -1,   191,   485,    -1,   191,   485,   486,   390,   454,    -1,
      -1,   219,   485,    -1,   194,   485,    -1,   194,   485,   486,
     393,   454,    -1,    -1,   398,   395,   402,   395,    -1,   244,
      15,   363,    21,   395,    -1,    -1,   397,   363,    -1,   396,
       8,   363,    -1,    13,    -1,     6,    -1,   399,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   401,    -1,     5,   548,   505,   549,
     395,    -1,     5,   548,    15,   549,     5,    21,    -1,     5,
     548,    15,   549,   491,    21,    -1,    -1,   401,    -1,    15,
     569,   403,   404,    21,    -1,    15,   569,   403,   404,     8,
     569,   403,   404,    21,    -1,   491,    -1,     5,    -1,   560,
     491,    -1,   560,     5,    -1,    -1,    -1,    26,   491,    -1,
      18,   491,    -1,    87,   486,   485,   363,   468,    -1,   406,
       8,   363,   468,    -1,    44,   485,   486,   414,    -1,   407,
       8,   414,    -1,   187,   485,   486,   414,    -1,   408,     8,
     414,    -1,   236,   485,   486,   414,    -1,   409,     8,   414,
      -1,    67,   485,   414,    -1,    67,   485,   413,   414,    -1,
     410,   542,   413,   542,   414,    -1,   410,     8,   414,    -1,
     167,   485,   412,   494,    -1,   411,   542,   412,   542,   494,
      -1,   411,     8,   494,    -1,    37,   363,    37,    -1,    23,
      -1,    37,   363,    37,    -1,   363,   468,    -1,   119,   485,
     486,   363,    -1,   415,     8,   363,    -1,   143,   485,   486,
     363,    -1,   416,     8,   363,    -1,   117,   485,   418,    -1,
     417,     8,   418,    -1,    15,   419,    21,    -1,   420,     8,
     420,    -1,   419,     8,   420,    -1,   363,    -1,   363,    15,
     490,    21,    -1,   499,    -1,   422,    -1,    80,   484,   423,
     425,    -1,   422,   542,   425,    -1,    -1,    -1,   426,    37,
     427,    37,    -1,   428,    -1,   426,     8,   428,    -1,   439,
      -1,   427,     8,   439,    -1,   429,   431,    -1,   429,   431,
     432,    -1,   429,   431,   433,    -1,   429,   431,   432,   433,
      -1,   429,   436,    -1,    -1,   363,    -1,   363,    -1,    15,
     434,    21,    -1,    15,   435,     7,   435,    21,    -1,   448,
      -1,   434,     8,   448,    -1,    -1,   448,    -1,    15,   437,
       8,   430,    26,   434,    21,    -1,   438,    -1,   437,     8,
     438,    -1,   431,   432,    -1,   431,   433,    -1,   431,   432,
     433,    -1,   436,    -1,   440,    -1,   429,   430,     5,   440,
      -1,   443,     5,   440,    -1,   429,   430,    -1,   442,    -1,
     444,    -1,   446,    -1,    36,    -1,    36,   246,   508,    -1,
      27,    -1,    27,   246,   508,    -1,    64,    -1,   441,    -1,
     429,   494,    15,   569,   487,    21,    -1,    59,    -1,   443,
      -1,    17,   443,    -1,    16,   443,    -1,   149,    -1,   149,
     246,   508,    -1,   445,    -1,    17,   445,    -1,    16,   445,
      -1,   201,    -1,   201,   246,   508,    -1,    92,    -1,    92,
     246,   508,    -1,    15,   447,     8,   447,    21,    -1,   444,
      -1,   442,    -1,   449,    -1,    17,   449,    -1,    16,   449,
      -1,   448,    17,   449,    -1,   448,    16,   449,    -1,   450,
      -1,   449,     5,   450,    -1,   449,    37,   450,    -1,   451,
      -1,   451,     9,   450,    -1,   149,    -1,   430,    -1,    15,
     448,    21,    -1,   453,    -1,   452,     8,   453,    -1,   414,
      -1,   413,    -1,   455,   457,   456,    -1,   454,     8,   455,
     457,   456,    -1,    -1,    -1,   363,    -1,   177,    15,   376,
      21,    -1,    47,    15,    26,    21,    -1,   459,    -1,   458,
       8,   459,    -1,   363,    26,   491,    -1,   163,   461,    -1,
     363,    -1,   461,     8,   363,    -1,   248,   485,   463,    -1,
     248,   485,   463,     8,   372,   466,    -1,   248,   485,   463,
       8,   372,   172,    -1,   248,   485,   463,     8,   372,   172,
     464,    -1,   363,    -1,   465,    -1,   464,     8,   465,    -1,
     467,    -1,   363,    -1,   467,    -1,   466,     8,   467,    -1,
     363,    18,   363,    -1,    -1,    15,   469,    21,    -1,    -1,
     470,   471,    -1,   469,     8,   471,    -1,   472,    -1,     7,
      -1,   491,     7,    -1,   491,     7,   472,    -1,     5,    -1,
     491,    -1,   474,    -1,   473,     8,   474,    -1,   149,    -1,
     130,   485,   476,    -1,   131,    -1,   477,    -1,   476,     8,
     477,    -1,   478,    15,   481,    21,    -1,    -1,   479,   480,
      -1,   231,   399,    -1,   394,    -1,   482,    -1,   481,     8,
     482,    -1,   483,    -1,   483,    16,   483,    -1,   129,    -1,
      -1,    -1,    -1,     7,     7,    -1,    -1,   489,    -1,   491,
      -1,   509,    -1,   560,   491,    -1,   569,   488,    -1,   489,
       8,   569,   488,    -1,   491,    -1,   490,     8,   491,    -1,
     492,    -1,    15,   491,    21,    -1,   507,    -1,   495,    -1,
     503,    -1,   510,    -1,   491,    17,   491,    -1,   491,    16,
     491,    -1,   491,     5,   491,    -1,   491,    37,   491,    -1,
     491,     9,   491,    -1,   375,   491,    -1,    17,   491,    -1,
      16,   491,    -1,   491,    25,   491,    -1,   491,    29,   491,
      -1,   491,    31,   491,    -1,   491,    28,   491,    -1,   491,
      30,   491,    -1,   491,    32,   491,    -1,   491,    24,   491,
      -1,   491,    33,   491,    -1,   491,    38,   491,    -1,   491,
      35,   491,    -1,   491,    22,   491,    -1,    34,   491,    -1,
     491,    23,   491,    -1,   491,   375,   491,    -1,    17,    -1,
      16,    -1,   363,    -1,   494,    -1,   497,    -1,   496,    -1,
     494,    15,   569,   487,    21,    -1,   494,    15,   569,   487,
      21,   501,    -1,   497,    15,   487,    21,    -1,   497,    15,
     487,    21,   501,    -1,   495,     3,   129,    -1,   494,    -1,
     497,    -1,   494,    15,   569,   487,    21,    -1,   497,    15,
     487,    21,    -1,   494,   501,    -1,    -1,   501,    -1,    15,
     502,     7,   502,    21,    -1,    -1,   491,    -1,   504,    -1,
     504,   246,   508,    -1,   505,    -1,   505,   246,   508,    -1,
     506,   500,    -1,    36,    -1,    27,    -1,   201,    -1,    92,
      -1,   149,    -1,    64,    -1,   494,   246,    64,    -1,   505,
     246,    64,    -1,    15,   492,     8,   492,    21,    -1,   494,
      -1,   505,    -1,   491,     7,   491,    -1,   491,     7,    -1,
     491,     7,   491,     7,   491,    -1,   491,     7,     7,   491,
      -1,     7,   491,     7,   491,    -1,     7,     7,   491,    -1,
       7,   491,    -1,     7,    -1,    -1,    -1,    14,   404,   511,
     566,   512,    20,    -1,   494,    -1,   497,    -1,   498,    -1,
     514,     8,   569,   498,    -1,   514,     8,   569,   560,   494,
      -1,   513,    -1,   515,     8,   569,   513,    -1,   515,     8,
     569,   560,   494,    -1,    -1,   494,    -1,   517,     8,   494,
      -1,   539,    -1,   538,    -1,   521,    -1,   529,   521,    -1,
     102,   547,   527,    -1,   103,   547,   526,    -1,   108,   527,
      -1,   519,    -1,   529,   519,    -1,   530,   539,    -1,   530,
     239,    -1,   529,   530,   239,    -1,    97,   547,    15,   491,
      21,   239,   526,    -1,    96,   547,   526,    -1,   106,   547,
     526,    -1,   522,    -1,    76,   547,    -1,   531,   539,    -1,
     531,    -1,   529,   531,    -1,   105,   547,   526,    -1,   575,
      -1,   836,    -1,   854,    -1,    89,   547,    15,   491,    21,
      -1,    89,   547,   548,   537,   549,   609,   520,    -1,    -1,
       8,   370,   254,    15,   491,    21,    -1,   254,    15,   491,
      21,    -1,   185,   547,   548,   537,   549,   542,   535,    26,
     491,     8,   491,    -1,   185,   547,   548,   537,   549,   542,
     535,    26,   491,     8,   491,     8,   491,    -1,    62,   547,
     523,   526,    -1,    84,   547,   526,    -1,   110,   547,   526,
      -1,   218,   547,   370,    62,    15,   491,    21,    -1,   529,
     218,   547,   370,    62,    15,   491,    21,    -1,    15,   525,
      21,    -1,   491,    -1,   491,     7,    -1,     7,   491,    -1,
     491,     7,   491,    -1,   524,    -1,   525,     8,   524,    -1,
      -1,   363,    -1,    -1,   363,    -1,    75,    -1,   528,     7,
      -1,   155,   547,    15,   491,    21,    -1,   122,   547,    15,
     532,   534,    21,    -1,   533,    -1,   532,     8,   533,    -1,
     535,    26,   509,    -1,    -1,     8,   491,    -1,   363,    -1,
     535,    26,   491,     8,   491,    -1,   535,    26,   491,     8,
     491,     8,   491,    -1,    -1,   149,    -1,   113,   547,   526,
      -1,    98,   547,   526,    -1,    98,   547,    15,   491,    21,
     526,    -1,   252,   547,    15,   491,    21,    -1,   529,   252,
     547,    15,   491,    21,    -1,   540,   491,    26,   491,    -1,
     188,   547,   495,    18,   491,    -1,    48,   547,   474,   240,
     363,    -1,    77,   547,    -1,   541,    -1,   550,    -1,    46,
     547,    15,   491,    21,   474,     8,   474,     8,   474,    -1,
     543,    -1,   543,    15,    21,    -1,   543,    15,   544,    21,
      -1,   214,   547,   502,    -1,   546,   547,   502,    -1,    79,
     547,   526,    -1,   115,   547,   526,    -1,    45,   547,    15,
     516,   514,    21,    -1,    81,   547,    15,   516,   515,    21,
      -1,   170,   547,    15,   517,    21,    -1,   253,   547,    15,
     491,    21,   495,    26,   491,    -1,   152,   424,    -1,   186,
     547,   474,    -1,    49,   547,   363,    -1,    49,   547,   363,
     542,    15,   473,    21,    -1,    69,   547,    15,   473,    21,
     542,   491,    -1,    -1,     8,    -1,    61,   547,   363,   569,
      -1,   569,   545,    -1,   544,     8,   569,   545,    -1,   491,
      -1,   560,   491,    -1,     5,   474,    -1,   184,    -1,   232,
      -1,    -1,    -1,    -1,   551,   557,    -1,   551,   572,    -1,
     551,     5,    -1,   551,     9,    -1,   553,   557,    -1,   555,
      -1,   561,   557,    -1,   561,   556,    -1,   561,   557,   564,
      -1,   561,   556,     8,   564,    -1,   562,   557,    -1,   562,
     557,   566,    -1,   563,    -1,   563,     8,   566,    -1,   552,
     547,   570,    -1,    53,    -1,   215,    -1,   104,    -1,   554,
     547,   570,    -1,   176,    -1,    66,    -1,   139,   547,   570,
     557,    -1,   139,   547,   570,   557,   566,    -1,   572,    -1,
       5,    -1,    15,   571,    21,    -1,    15,   558,    21,    -1,
     559,    -1,   558,     8,   569,   559,    -1,   571,    -1,     5,
      -1,     9,    -1,   560,   491,    -1,   560,     5,    -1,   560,
       9,    -1,   166,    -1,   197,   547,   570,    -1,   256,   547,
     570,    -1,   190,   547,   571,   570,    -1,   190,   547,     5,
     570,    -1,   565,    -1,   564,     8,   565,    -1,   495,    -1,
      15,   564,     8,   536,    21,    -1,   492,    -1,   568,    -1,
     567,    -1,   492,     8,   492,    -1,   492,     8,   568,    -1,
     568,     8,   492,    -1,   568,     8,   568,    -1,   567,     8,
     492,    -1,   567,     8,   568,    -1,   507,    -1,    15,   491,
      21,    -1,    15,   492,     8,   536,    21,    -1,    15,   568,
       8,   536,    21,    -1,    15,   567,     8,   536,    21,    -1,
      -1,    -1,   572,    -1,    15,   571,    21,    -1,   495,    -1,
     503,    -1,   571,   493,   571,    -1,   571,     5,   571,    -1,
     571,    37,   571,    -1,   571,     9,   571,    -1,   493,   571,
      -1,   571,    23,   571,    -1,   129,    26,   491,    -1,    -1,
     257,    -1,   576,    -1,   624,    -1,   599,    -1,   578,    -1,
     589,    -1,   584,    -1,   636,    -1,   639,    -1,   714,    -1,
     581,    -1,   590,    -1,   592,    -1,   594,    -1,   596,    -1,
     644,    -1,   650,    -1,   647,    -1,   773,    -1,   771,    -1,
     600,    -1,   625,    -1,   654,    -1,   703,    -1,   701,    -1,
     702,    -1,   704,    -1,   705,    -1,   706,    -1,   707,    -1,
     708,    -1,   716,    -1,   718,    -1,   723,    -1,   720,    -1,
     722,    -1,   726,    -1,   724,    -1,   725,    -1,   737,    -1,
     741,    -1,   742,    -1,   745,    -1,   744,    -1,   746,    -1,
     747,    -1,   748,    -1,   749,    -1,   653,    -1,   731,    -1,
     732,    -1,   733,    -1,   736,    -1,   750,    -1,   753,    -1,
     758,    -1,   763,    -1,   765,    -1,   766,    -1,   767,    -1,
     768,    -1,   770,    -1,   729,    -1,   772,    -1,    82,   485,
     577,    -1,   576,     8,   577,    -1,   363,   468,    -1,    94,
     485,   579,    -1,   580,    -1,   579,     8,   580,    -1,   363,
      -1,   138,   485,   582,    -1,   583,    -1,   582,     8,   583,
      -1,   363,    -1,   228,   485,   588,   585,    -1,    15,   586,
      21,    -1,   587,    -1,   586,     8,   587,    -1,   491,    -1,
     491,     7,   491,    -1,     7,    15,   490,    21,    -1,   363,
      -1,   259,   485,   363,   468,    -1,   303,   485,   363,   468,
      -1,   589,     8,   363,   468,    -1,   136,   485,   591,    -1,
     590,     8,   591,    -1,   363,    -1,   211,   485,   593,    -1,
     592,     8,   593,    -1,   363,    -1,   205,   485,   595,    -1,
     594,     8,   595,    -1,   363,    -1,    70,   485,   597,    -1,
     596,     8,   597,    -1,   363,    -1,   175,   363,   468,    -1,
      -1,    88,   485,   603,   606,   598,    -1,   204,   547,   603,
     607,   609,   598,    -1,   204,   547,   607,   609,   598,     7,
       7,   601,    -1,   602,    -1,   601,     8,   602,    -1,   603,
      -1,   604,    -1,   363,    -1,   363,    15,   490,    21,    -1,
     363,    -1,    -1,   607,   609,    -1,    15,   608,    21,    -1,
     609,   610,    -1,   608,     8,   609,   610,    -1,    -1,    58,
      -1,    58,    15,   569,   623,    21,    -1,   126,    15,   611,
      21,    -1,   258,    15,   611,     8,   491,    21,    -1,   165,
      15,   491,    21,    -1,     5,    -1,   137,    15,   611,    21,
      -1,    86,    15,   612,    21,    -1,   363,    -1,    15,   613,
      21,   370,   255,   615,    -1,   614,    -1,   613,     8,   614,
      -1,   491,    -1,   491,     7,   491,    -1,   616,    -1,   616,
      15,   617,    21,    -1,   363,    -1,   618,    -1,   617,     8,
     618,    -1,   491,    -1,   762,    -1,    40,   619,   620,    -1,
     363,    -1,    -1,   621,    -1,    17,   622,    -1,   620,    17,
     622,    -1,   491,    -1,   560,   491,    -1,   560,   491,     8,
     560,   491,    -1,    43,   485,   627,   629,    -1,   199,   547,
     628,   629,    -1,   199,   547,   629,     7,     7,   626,    -1,
     628,    -1,   626,     8,   628,    -1,   363,    -1,   494,    -1,
      15,   634,    21,   370,   255,   630,    -1,   633,    15,   631,
      21,    -1,   632,    -1,   631,     8,   632,    -1,   491,    -1,
       5,    -1,   509,    -1,   363,    -1,   635,    -1,   634,     8,
     635,    -1,   363,    -1,     5,    -1,     7,    -1,   637,     7,
       7,   485,   363,   468,    -1,   636,     8,   363,   468,    -1,
     638,    -1,   637,     8,   370,   638,    -1,    82,    -1,   259,
      -1,   303,    -1,    94,    -1,    87,    15,   469,    21,    -1,
     228,   585,    -1,    43,    15,   634,    21,   370,   255,   630,
      -1,    43,    -1,    88,   607,   609,   598,    -1,    88,    -1,
      67,    -1,   394,     8,   370,    93,   485,    15,   640,    21,
       7,     7,   642,    -1,    -1,   641,     7,    -1,   640,     8,
       7,    -1,   643,    -1,   642,     8,   643,    -1,   363,    -1,
     127,   485,   645,    -1,   646,    -1,   645,     8,   646,    -1,
     363,    -1,    74,   485,   648,    -1,   649,    -1,   648,     8,
     649,    -1,   363,    -1,    51,   485,   651,    -1,    51,   485,
       8,   370,    67,     7,     7,   651,    -1,   652,    -1,   651,
       8,   652,    -1,   363,   468,    -1,   168,   547,    -1,   182,
     547,    15,   655,    21,   656,   660,    -1,   494,    -1,   655,
       8,   494,    -1,   609,   173,   657,    -1,   609,    -1,   494,
      15,   658,    21,    -1,   659,    -1,   658,     8,   659,    -1,
     491,    -1,     5,    -1,    -1,   661,    -1,   662,    -1,   661,
     662,    -1,   666,    -1,   686,    -1,   694,    -1,   663,    -1,
     671,    -1,   673,    -1,   672,    -1,   664,    -1,   667,    -1,
     668,    -1,     8,   370,   209,    15,   709,     7,   710,    21,
      -1,     8,   370,   209,    15,   710,    21,    -1,     8,   370,
      71,    15,   665,     7,   710,    21,    -1,     8,   370,    71,
      15,   710,    21,    -1,   363,    -1,     8,   370,   169,    15,
     670,    21,    -1,     8,   370,   282,    15,   670,    21,    -1,
       8,   370,   191,    15,   670,    21,    -1,     8,   370,   320,
      15,   669,    21,    -1,   491,    -1,   491,     8,   491,    -1,
     491,     8,   491,     8,   491,    -1,   495,    -1,   670,     8,
     495,    -1,     8,   370,   135,    15,   709,     7,   727,    21,
      -1,     8,   370,   135,    15,   727,    21,    -1,     8,   370,
     229,    15,   491,    21,    -1,     8,   370,    41,   674,    -1,
       8,   370,    41,   674,   674,    -1,    15,   609,   675,   676,
      21,    -1,   148,     7,    -1,   180,     7,    -1,    -1,   677,
      -1,   676,     8,   677,    -1,   699,    -1,   699,    15,   678,
      21,    -1,   699,    15,   678,    21,    15,   680,    21,    -1,
     679,    -1,   678,     8,   679,    -1,   491,     7,   491,    -1,
     681,    -1,   680,     8,   681,    -1,   682,     7,   683,     7,
     684,    -1,   682,     7,   683,    -1,   682,     7,   684,    -1,
     682,    -1,   683,     7,   684,    -1,   683,    -1,   684,    -1,
     370,   217,   685,    -1,   370,   157,   685,    -1,   370,   128,
     685,    -1,    15,   489,    21,    -1,     8,   370,   208,    15,
     687,   691,   688,     8,   690,    21,    -1,     8,   370,   208,
      15,   687,   691,   688,    21,    -1,     8,   370,   208,    15,
     687,   689,   688,     7,   690,    21,    -1,    -1,    -1,   363,
      -1,   370,   691,    -1,   690,     8,   370,   691,    -1,   692,
      15,   495,    21,    -1,   693,    15,   670,     8,   491,    21,
      -1,   234,    -1,   192,    -1,   162,    -1,   159,    -1,    35,
      -1,    22,    -1,    24,    -1,    33,    -1,   247,    -1,   158,
      -1,   161,    -1,     8,   370,   223,    15,   696,    21,    -1,
       8,   370,   224,   695,    -1,     8,   370,   226,   695,    -1,
       8,   370,   221,    -1,     8,   370,   221,    15,   699,    15,
     586,    21,    21,    -1,   363,    -1,   697,    -1,   696,     8,
     697,    -1,   699,    -1,   699,    15,   698,    78,    21,    -1,
     699,    15,   698,   586,    21,    -1,   699,    15,   698,   586,
      21,    15,   370,    78,    21,    -1,    -1,   494,    -1,   699,
      -1,   700,     8,   699,    -1,   225,   547,   695,    -1,   224,
     547,   695,    -1,   227,   547,   695,    -1,   226,   547,   695,
      -1,   222,   547,   695,    15,   696,    21,    -1,   206,   547,
     689,    -1,   207,   547,   689,    -1,    72,   547,   665,    -1,
      73,   547,   665,    -1,   210,   547,    15,   709,     7,   710,
      21,    -1,   210,   547,    15,   710,    21,    -1,   363,    -1,
     711,    -1,   710,     8,   711,    -1,   699,    15,   712,    21,
      -1,   699,    -1,   713,    -1,   712,     8,   713,    -1,   491,
      -1,     7,    -1,   237,   485,   715,    -1,   714,     8,   715,
      -1,   363,   468,    -1,   238,   547,   717,    -1,   238,   547,
     717,   686,    -1,   238,   547,   717,   664,    -1,   238,   547,
     717,   686,   664,    -1,   238,   547,   717,   664,   686,    -1,
     363,    -1,   111,   547,    -1,   717,    15,   491,    21,    -1,
     717,    15,   509,    21,    -1,   174,   547,   496,   721,    -1,
      -1,   666,    -1,   109,   547,    -1,   160,   547,   719,   370,
     175,   605,   468,    -1,   160,   547,   719,   370,   322,   495,
      -1,   189,   547,   709,    -1,   212,   547,   709,    -1,   135,
     547,    15,   709,     7,   727,    21,    -1,   135,   547,    15,
     727,    21,    -1,   728,    -1,   727,     8,   728,    -1,   699,
      -1,   699,    15,   490,    21,    -1,   134,   547,    -1,   134,
     547,   666,    -1,   134,   547,   730,    -1,   134,   547,   666,
     730,    -1,     8,   370,   208,    15,   670,    21,    -1,    50,
     547,   735,    -1,    99,   547,    -1,    52,   547,   735,    -1,
     363,    -1,   734,    -1,   734,    15,   490,    21,    -1,   120,
     547,   495,    26,   495,    -1,    83,   547,   740,    -1,    83,
     547,   740,    15,   738,    21,    -1,   569,   739,    -1,   738,
       8,   569,   739,    -1,   560,   491,    -1,   149,    -1,   100,
     547,   740,    -1,   146,   547,   743,    -1,    -1,   491,    -1,
     331,   547,   490,    -1,   101,   547,    -1,   241,   547,    -1,
     242,   547,    -1,    56,   547,    -1,    65,   547,   569,    15,
     544,    21,   404,   486,   670,    -1,   323,   547,    15,   751,
      21,    -1,   752,    -1,   751,     8,   752,    -1,   370,   315,
      -1,   370,   318,    -1,   370,   182,    -1,   220,   547,    15,
     754,    26,   622,    21,   609,   757,    -1,   494,    15,   755,
      21,    -1,   756,    -1,   755,     8,   756,    -1,   612,    -1,
     762,    -1,   132,   700,    -1,    -1,   153,   547,    15,   494,
      18,   759,    21,    -1,   494,    -1,   494,    15,   760,    21,
      -1,   761,    -1,   760,     8,   761,    -1,   762,    -1,     7,
      -1,     5,    -1,   324,   547,   491,     8,   370,   329,    15,
     670,    21,     8,   370,   328,    15,   490,    21,   764,    -1,
      -1,     8,   370,   182,    -1,     8,   370,   318,    -1,   325,
     547,   491,    -1,   326,   547,   491,    -1,   326,   547,   491,
       8,   370,   315,    -1,   327,   547,   491,     8,   370,   330,
      15,   494,    21,    -1,   332,   547,    15,   769,    21,    -1,
     498,    -1,   769,     8,   498,    -1,   333,   547,    15,   655,
      21,    -1,   822,    -1,   775,    -1,   774,    -1,   792,    -1,
     795,    -1,   796,    -1,   797,    -1,   798,    -1,   804,    -1,
     807,    -1,   812,    -1,   813,    -1,   814,    -1,   817,    -1,
     818,    -1,   819,    -1,   820,    -1,   821,    -1,   823,    -1,
     824,    -1,   825,    -1,   826,    -1,   827,    -1,   828,    -1,
     829,    -1,   830,    -1,   831,    -1,   268,   547,    -1,   275,
     547,    -1,   291,   547,   609,   776,    -1,   291,   547,   609,
      -1,   542,   609,   777,   609,    -1,   776,   542,   609,   777,
     609,    -1,   779,    -1,   788,    -1,   783,    -1,   784,    -1,
     780,    -1,   781,    -1,   782,    -1,   786,    -1,   787,    -1,
     834,    15,   835,   833,    21,    -1,   191,   778,    -1,   282,
     778,    -1,   285,   778,    -1,   265,   778,    -1,   299,   778,
      -1,    84,    15,   370,   785,    21,    -1,   191,    -1,   299,
      -1,   288,    -1,   304,    15,   491,    21,    -1,   289,    15,
     491,    21,    -1,   208,    15,   789,    21,    -1,   609,   791,
       7,   790,    -1,   670,    -1,    17,    -1,    16,    -1,     5,
      -1,    37,    -1,   162,    -1,   159,    -1,    35,    -1,    22,
      -1,    24,    -1,    33,    -1,   305,    -1,   306,    -1,   307,
      -1,   247,    -1,   297,   547,   609,   793,    -1,   297,   547,
     609,    -1,   542,   609,   794,   609,    -1,   793,   542,   609,
     794,   609,    -1,   779,    -1,   788,    -1,   780,    -1,   781,
      -1,   279,   547,   609,   811,    -1,   279,   547,   609,    -1,
     296,   547,    -1,   269,   547,   609,   799,    -1,   269,   547,
     609,    -1,   272,   547,   609,   811,    -1,   272,   547,   609,
      -1,   542,   609,   800,   609,    -1,   799,   542,   609,   800,
     609,    -1,   779,    -1,   788,    -1,   780,    -1,   781,    -1,
     802,    -1,   801,    -1,   290,    -1,   298,    15,   370,   803,
       8,   491,    21,    -1,   298,    15,   370,   803,    21,    -1,
     230,    -1,    94,    -1,   284,    -1,   295,    -1,   300,   547,
     609,   805,    -1,   300,   547,   609,    -1,   542,   609,   806,
     609,    -1,   805,   542,   609,   806,   609,    -1,   779,    -1,
     780,    -1,   280,   547,   609,   808,    -1,   280,   547,   609,
      -1,   542,   609,   809,   609,    -1,   808,   542,   609,   809,
     609,    -1,   811,    -1,   810,    -1,   266,   778,    -1,   287,
      -1,   302,   547,    -1,   281,   547,   609,   811,    -1,   281,
     547,   609,    -1,   292,   547,   609,   815,    -1,   292,   547,
     609,    -1,   542,   609,   816,   609,    -1,   815,   542,   609,
     816,   609,    -1,   779,    -1,   788,    -1,   783,    -1,   784,
      -1,   780,    -1,   781,    -1,   782,    -1,   786,    -1,   787,
      -1,   802,    -1,   801,    -1,   276,   547,    -1,   293,   547,
     609,   776,    -1,   293,   547,   609,    -1,   277,   547,    -1,
     294,   547,   609,   776,    -1,   294,   547,   609,    -1,   278,
     547,    -1,   301,   485,   778,    -1,   286,   547,    -1,   273,
     547,    -1,   290,   547,    -1,   274,   547,    -1,   264,   547,
      -1,   263,   547,    -1,   283,   547,   778,    -1,   283,   547,
      -1,   267,   547,    15,   494,    21,    -1,   267,   547,    -1,
     271,   547,    15,   494,    21,    -1,   271,   547,    -1,    37,
     363,   834,    37,   835,    -1,   832,    -1,   494,    -1,   833,
       8,   832,    -1,   833,     8,   494,    -1,    -1,    -1,   837,
      -1,   850,    -1,   838,    -1,   851,    -1,   839,    -1,   840,
      -1,   852,    -1,   308,   547,   841,    -1,   310,   547,    -1,
     312,   547,    15,   847,    21,    -1,   312,   547,    15,    21,
      -1,   312,   547,    -1,   313,   547,    15,   847,    21,    -1,
     313,   547,    15,    21,    -1,   313,   547,    -1,   370,   371,
      -1,   842,    -1,   843,    -1,   842,     8,   843,    -1,   370,
     844,    -1,   370,   846,    -1,   370,   845,    -1,   147,    15,
     847,    21,    -1,   148,    15,   847,    21,    -1,   180,    15,
     847,    21,    -1,   318,    15,   847,    21,    -1,   319,    15,
     847,    21,    -1,   314,    15,   848,    21,    -1,   315,    -1,
     670,    -1,   849,    -1,   848,     8,   849,    -1,   370,   316,
      -1,   370,   317,    -1,   309,    -1,   311,    -1,   321,   485,
     853,    -1,   370,   371,    -1,   370,   845,    -1,   855,    -1,
     856,    -1,   857,    -1,   858,    -1,   859,    -1,   873,    -1,
     334,    15,   860,    21,    -1,   335,    15,   864,    21,    -1,
     336,    15,   869,    21,    -1,   338,   871,    -1,   339,    -1,
     861,    -1,   860,     8,   861,    -1,   862,    -1,   863,    -1,
     370,   208,    15,   690,    21,    -1,   370,   191,    15,   670,
      21,    -1,   865,    -1,   864,     8,   865,    -1,   866,    -1,
     867,    -1,   868,    -1,   370,   228,    15,   696,    21,    -1,
     370,    41,    15,   696,    21,    -1,   370,   209,    15,   710,
      21,    -1,   870,    -1,   869,     8,   870,    -1,   370,   337,
      -1,   370,   341,    15,   655,    21,    -1,   370,   340,    -1,
     370,   340,    15,   655,    21,    -1,   370,   342,    15,   872,
      21,    -1,   363,    -1,   498,    -1,   872,     8,   498,    -1,
     343,    15,   874,    21,    -1,   875,    -1,   874,     8,   875,
      -1,   370,   244,    15,   876,    21,    -1,   370,   329,    15,
     655,    21,    -1,   370,   344,    15,   655,    21,    -1,   370,
     345,    15,   491,    21,    -1,   370,   346,    15,   878,     8,
     491,    21,    -1,   877,    -1,   876,     8,   877,    -1,   370,
     315,    -1,   370,   349,    -1,   370,   347,    -1,   370,   348,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   782,   782,   783,   787,   789,   803,   834,   843,   849,
     869,   878,   894,   906,   916,   923,   929,   934,   939,   963,
     990,  1004,  1006,  1008,  1012,  1029,  1043,  1067,  1083,  1097,
    1115,  1117,  1124,  1128,  1129,  1136,  1137,  1145,  1146,  1148,
    1152,  1153,  1157,  1161,  1167,  1177,  1181,  1186,  1193,  1194,
    1195,  1196,  1197,  1198,  1199,  1200,  1201,  1202,  1203,  1204,
    1205,  1206,  1211,  1216,  1223,  1225,  1226,  1227,  1228,  1229,
    1230,  1231,  1232,  1233,  1234,  1235,  1236,  1239,  1243,  1251,
    1259,  1268,  1276,  1280,  1282,  1286,  1288,  1290,  1292,  1294,
    1296,  1298,  1300,  1302,  1304,  1306,  1308,  1310,  1312,  1314,
    1316,  1318,  1320,  1325,  1334,  1344,  1352,  1362,  1383,  1403,
    1404,  1406,  1410,  1412,  1416,  1420,  1422,  1426,  1432,  1436,
    1438,  1442,  1446,  1450,  1454,  1458,  1464,  1468,  1472,  1478,
    1483,  1490,  1501,  1514,  1525,  1538,  1548,  1561,  1566,  1573,
    1576,  1581,  1586,  1593,  1596,  1606,  1620,  1623,  1642,  1669,
    1671,  1683,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1702,
    1703,  1707,  1709,  1716,  1721,  1722,  1724,  1726,  1739,  1745,
    1751,  1760,  1769,  1782,  1783,  1786,  1790,  1805,  1820,  1838,
    1859,  1879,  1901,  1918,  1936,  1943,  1950,  1957,  1970,  1977,
    1984,  1995,  1999,  2001,  2006,  2024,  2035,  2047,  2059,  2073,
    2079,  2086,  2092,  2098,  2106,  2113,  2129,  2132,  2141,  2143,
    2147,  2151,  2171,  2175,  2177,  2181,  2182,  2185,  2187,  2189,
    2191,  2193,  2196,  2199,  2203,  2209,  2213,  2217,  2219,  2224,
    2225,  2229,  2233,  2235,  2239,  2241,  2243,  2248,  2252,  2254,
    2256,  2259,  2261,  2262,  2263,  2264,  2265,  2266,  2267,  2268,
    2271,  2272,  2278,  2281,  2282,  2284,  2288,  2289,  2292,  2293,
    2295,  2299,  2300,  2301,  2302,  2304,  2307,  2308,  2317,  2319,
    2326,  2333,  2340,  2349,  2351,  2353,  2357,  2359,  2363,  2372,
    2379,  2386,  2388,  2392,  2396,  2402,  2404,  2409,  2413,  2417,
    2424,  2431,  2441,  2443,  2447,  2459,  2462,  2471,  2484,  2490,
    2496,  2502,  2510,  2520,  2522,  2526,  2528,  2561,  2563,  2567,
    2606,  2607,  2611,  2611,  2616,  2620,  2628,  2637,  2646,  2656,
    2662,  2665,  2667,  2671,  2679,  2694,  2701,  2703,  2707,  2723,
    2723,  2727,  2729,  2741,  2743,  2747,  2753,  2765,  2777,  2794,
    2823,  2824,  2832,  2833,  2837,  2839,  2841,  2852,  2856,  2862,
    2864,  2868,  2870,  2872,  2876,  2878,  2882,  2884,  2886,  2888,
    2890,  2892,  2894,  2896,  2898,  2900,  2902,  2904,  2906,  2908,
    2910,  2912,  2914,  2916,  2918,  2920,  2922,  2924,  2926,  2930,
    2931,  2942,  3016,  3028,  3030,  3034,  3165,  3215,  3259,  3301,
    3359,  3361,  3363,  3402,  3445,  3456,  3457,  3461,  3466,  3467,
    3471,  3473,  3479,  3481,  3487,  3497,  3503,  3510,  3516,  3524,
    3532,  3548,  3558,  3571,  3578,  3580,  3603,  3605,  3607,  3609,
    3611,  3613,  3615,  3617,  3621,  3621,  3621,  3635,  3637,  3660,
    3662,  3664,  3680,  3682,  3684,  3698,  3701,  3703,  3711,  3713,
    3715,  3717,  3771,  3791,  3806,  3815,  3818,  3868,  3874,  3879,
    3897,  3899,  3901,  3903,  3905,  3908,  3914,  3916,  3918,  3921,
    3923,  3925,  3952,  3961,  3970,  3971,  3973,  3978,  3985,  3993,
    3995,  3999,  4002,  4004,  4008,  4014,  4016,  4018,  4020,  4024,
    4026,  4035,  4036,  4043,  4044,  4048,  4052,  4073,  4076,  4080,
    4082,  4089,  4094,  4095,  4106,  4123,  4146,  4171,  4172,  4179,
    4181,  4183,  4185,  4187,  4191,  4268,  4280,  4287,  4289,  4290,
    4292,  4301,  4308,  4315,  4323,  4328,  4333,  4336,  4339,  4342,
    4345,  4348,  4352,  4370,  4375,  4394,  4413,  4417,  4418,  4421,
    4425,  4430,  4437,  4439,  4441,  4445,  4446,  4457,  4472,  4476,
    4483,  4486,  4496,  4509,  4522,  4525,  4527,  4530,  4533,  4537,
    4546,  4549,  4553,  4555,  4561,  4565,  4567,  4569,  4576,  4580,
    4582,  4586,  4588,  4592,  4611,  4627,  4636,  4645,  4647,  4651,
    4677,  4692,  4707,  4724,  4732,  4741,  4749,  4754,  4759,  4781,
    4797,  4799,  4803,  4805,  4812,  4814,  4816,  4820,  4822,  4824,
    4826,  4828,  4830,  4834,  4837,  4840,  4846,  4852,  4861,  4865,
    4872,  4874,  4878,  4880,  4882,  4887,  4892,  4897,  4902,  4911,
    4916,  4922,  4923,  4938,  4939,  4940,  4941,  4942,  4943,  4944,
    4945,  4946,  4947,  4948,  4949,  4950,  4951,  4952,  4953,  4954,
    4955,  4956,  4959,  4960,  4961,  4962,  4963,  4964,  4965,  4966,
    4967,  4968,  4969,  4970,  4971,  4972,  4973,  4974,  4975,  4976,
    4977,  4978,  4979,  4980,  4981,  4982,  4983,  4984,  4985,  4986,
    4987,  4988,  4989,  4990,  4991,  4992,  4993,  4994,  4995,  4996,
    4997,  4998,  4999,  5000,  5001,  5002,  5006,  5008,  5019,  5040,
    5044,  5046,  5050,  5063,  5067,  5069,  5073,  5084,  5095,  5099,
    5101,  5105,  5107,  5109,  5124,  5136,  5156,  5176,  5198,  5204,
    5213,  5221,  5227,  5235,  5242,  5248,  5257,  5261,  5267,  5275,
    5289,  5303,  5308,  5324,  5339,  5367,  5369,  5373,  5375,  5379,
    5408,  5431,  5452,  5453,  5457,  5478,  5480,  5484,  5492,  5496,
    5501,  5503,  5505,  5507,  5513,  5515,  5519,  5529,  5533,  5535,
    5540,  5542,  5546,  5550,  5556,  5566,  5568,  5572,  5574,  5576,
    5583,  5601,  5602,  5606,  5608,  5612,  5619,  5629,  5658,  5673,
    5680,  5698,  5700,  5704,  5718,  5744,  5757,  5773,  5775,  5778,
    5780,  5786,  5790,  5818,  5820,  5824,  5832,  5838,  5841,  5899,
    5963,  5965,  5968,  5972,  5976,  5980,  5997,  6009,  6013,  6017,
    6027,  6032,  6037,  6044,  6053,  6053,  6064,  6075,  6077,  6081,
    6092,  6096,  6098,  6102,  6113,  6117,  6119,  6123,  6135,  6137,
    6144,  6146,  6150,  6166,  6174,  6185,  6187,  6191,  6194,  6199,
    6209,  6211,  6215,  6217,  6226,  6227,  6231,  6233,  6238,  6239,
    6240,  6241,  6242,  6243,  6244,  6245,  6246,  6247,  6250,  6255,
    6259,  6263,  6267,  6280,  6284,  6288,  6292,  6295,  6297,  6299,
    6303,  6305,  6309,  6314,  6318,  6322,  6324,  6328,  6336,  6342,
    6349,  6352,  6354,  6358,  6360,  6364,  6376,  6378,  6382,  6386,
    6388,  6392,  6394,  6396,  6398,  6400,  6402,  6404,  6408,  6412,
    6416,  6420,  6424,  6431,  6437,  6442,  6445,  6448,  6461,  6463,
    6467,  6469,  6474,  6480,  6486,  6492,  6498,  6504,  6510,  6516,
    6522,  6531,  6537,  6554,  6556,  6564,  6572,  6574,  6578,  6582,
    6584,  6588,  6590,  6598,  6602,  6614,  6617,  6635,  6637,  6641,
    6643,  6647,  6649,  6653,  6657,  6661,  6670,  6674,  6678,  6683,
    6687,  6699,  6701,  6705,  6710,  6714,  6716,  6720,  6722,  6726,
    6731,  6738,  6761,  6763,  6765,  6767,  6769,  6773,  6784,  6788,
    6803,  6810,  6817,  6818,  6822,  6826,  6834,  6838,  6842,  6850,
    6855,  6869,  6871,  6875,  6877,  6886,  6888,  6890,  6892,  6928,
    6932,  6936,  6940,  6944,  6956,  6958,  6962,  6965,  6967,  6971,
    6976,  6983,  6986,  6994,  6998,  7003,  7005,  7012,  7017,  7021,
    7025,  7029,  7033,  7037,  7040,  7042,  7046,  7048,  7050,  7054,
    7058,  7070,  7072,  7076,  7078,  7082,  7085,  7088,  7092,  7098,
    7110,  7112,  7116,  7118,  7122,  7130,  7142,  7143,  7145,  7149,
    7153,  7155,  7163,  7167,  7170,  7172,  7176,  7180,  7182,  7183,
    7184,  7185,  7186,  7187,  7188,  7189,  7190,  7191,  7192,  7193,
    7194,  7195,  7196,  7197,  7198,  7199,  7200,  7201,  7202,  7203,
    7204,  7205,  7206,  7207,  7210,  7216,  7222,  7228,  7234,  7238,
    7244,  7245,  7246,  7247,  7248,  7249,  7250,  7251,  7252,  7255,
    7260,  7265,  7271,  7277,  7283,  7288,  7294,  7300,  7306,  7313,
    7319,  7325,  7332,  7336,  7338,  7344,  7351,  7357,  7363,  7369,
    7375,  7381,  7387,  7393,  7399,  7405,  7411,  7417,  7427,  7432,
    7438,  7442,  7448,  7449,  7450,  7451,  7454,  7462,  7468,  7474,
    7479,  7485,  7492,  7498,  7502,  7508,  7509,  7510,  7511,  7512,
    7513,  7516,  7525,  7529,  7535,  7542,  7549,  7556,  7565,  7571,
    7577,  7581,  7587,  7588,  7591,  7597,  7603,  7607,  7614,  7615,
    7618,  7624,  7630,  7635,  7643,  7649,  7654,  7661,  7665,  7671,
    7672,  7673,  7674,  7675,  7676,  7677,  7678,  7679,  7680,  7681,
    7685,  7690,  7695,  7702,  7707,  7713,  7719,  7724,  7729,  7734,
    7738,  7743,  7748,  7752,  7757,  7761,  7767,  7772,  7778,  7783,
    7789,  7799,  7803,  7807,  7811,  7817,  7820,  7824,  7825,  7826,
    7827,  7828,  7829,  7830,  7833,  7837,  7841,  7843,  7845,  7849,
    7851,  7853,  7857,  7859,  7863,  7865,  7869,  7872,  7875,  7880,
    7882,  7884,  7886,  7888,  7892,  7896,  7901,  7905,  7907,  7911,
    7913,  7917,  7921,  7925,  7929,  7931,  7935,  7936,  7937,  7938,
    7939,  7940,  7943,  7947,  7951,  7955,  7959,  7963,  7965,  7969,
    7970,  7973,  7977,  7981,  7983,  7987,  7988,  7989,  7993,  7997,
    8001,  8005,  8007,  8011,  8013,  8015,  8017,  8020,  8024,  8028,
    8030,  8034,  8038,  8040,  8044,  8046,  8048,  8050,  8052,  8056,
    8058,  8062,  8064,  8068,  8070
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
  "ACC_LOCAL", "ACC_INLOCAL", "ACC_CUDA_BLOCK", "ACC_ROUTINE", "BY",
  "IO_MODE", "CP_CREATE", "CP_LOAD", "CP_SAVE", "CP_WAIT", "FILES",
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
  "indirect_access_spec", "stage_spec", "across_spec", "in_out_across",
  "opt_in_out", "dependent_array_list", "dependent_array",
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
  "dvm_template_create", "template_list", "dvm_template_delete",
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
  "acc_routine", "opt_targets_clause", "spf_directive", "spf_analysis",
  "spf_parallel", "spf_transform", "spf_parallel_reg",
  "spf_end_parallel_reg", "analysis_spec_list", "analysis_spec",
  "analysis_reduction_spec", "analysis_private_spec", "parallel_spec_list",
  "parallel_spec", "parallel_shadow_spec", "parallel_across_spec",
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
       0,   348,   349,     1,     2,     3,     4,     5,     6,     7,
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
     350,   351
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   352,   353,   353,   354,   354,   354,   354,   354,   354,
     354,   355,   356,   356,   356,   356,   356,   356,   356,   356,
     357,   358,   358,   358,   359,   360,   361,   361,   361,   361,
     362,   362,   363,   364,   364,   365,   365,   366,   366,   366,
     367,   367,   368,   368,   369,   370,   371,   372,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   374,   374,   374,
     374,   374,   375,   376,   376,   377,   377,   377,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   377,   377,
     377,   377,   377,   378,   378,   379,   379,   380,   380,   381,
     381,   381,   382,   382,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   384,   384,   384,   385,
     385,   386,   386,   387,   387,   388,   388,   389,   389,   390,
     391,   392,   392,   393,   394,   394,   395,   396,   396,   397,
     397,   398,   399,   399,   399,   399,   399,   399,   399,   400,
     400,   401,   401,   401,   402,   402,   402,   402,   403,   403,
     403,   403,   404,   405,   405,   405,   406,   406,   407,   407,
     408,   408,   409,   409,   410,   410,   410,   410,   411,   411,
     411,   412,   413,   413,   414,   415,   415,   416,   416,   417,
     417,   418,   419,   419,   420,   420,   420,   421,   422,   422,
     423,   424,   425,   426,   426,   427,   427,   428,   428,   428,
     428,   428,   429,   430,   431,   432,   433,   434,   434,   435,
     435,   436,   437,   437,   438,   438,   438,   438,   439,   439,
     439,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   441,   442,   442,   442,   443,   443,   444,   444,
     444,   445,   445,   445,   445,   446,   447,   447,   448,   448,
     448,   448,   448,   449,   449,   449,   450,   450,   451,   451,
     451,   452,   452,   453,   453,   454,   454,   455,   456,   457,
     457,   457,   458,   458,   459,   460,   461,   461,   462,   462,
     462,   462,   463,   464,   464,   465,   465,   466,   466,   467,
     468,   468,   470,   469,   469,   471,   471,   471,   471,   472,
     472,   473,   473,   474,   475,   475,   476,   476,   477,   479,
     478,   480,   480,   481,   481,   482,   482,   483,   484,   485,
     486,   486,   487,   487,   488,   488,   488,   489,   489,   490,
     490,   491,   491,   491,   492,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   492,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   492,   492,   492,   492,   492,   493,
     493,   494,   495,   495,   495,   496,   496,   496,   496,   497,
     498,   498,   498,   498,   499,   500,   500,   501,   502,   502,
     503,   503,   503,   503,   503,   504,   504,   504,   504,   505,
     506,   506,   506,   507,   508,   508,   509,   509,   509,   509,
     509,   509,   509,   509,   511,   512,   510,   513,   513,   514,
     514,   514,   515,   515,   515,   516,   517,   517,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     518,   518,   519,   519,   520,   520,   520,   521,   521,   522,
     522,   522,   522,   522,   523,   524,   524,   524,   524,   525,
     525,   526,   526,   527,   527,   528,   529,   530,   531,   532,
     532,   533,   534,   534,   535,   536,   536,   537,   537,   538,
     538,   538,   538,   538,   539,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   540,   541,   541,   541,   541,   542,   542,   543,
     544,   544,   545,   545,   545,   546,   546,   547,   548,   549,
     550,   550,   550,   550,   550,   550,   550,   550,   550,   550,
     550,   550,   550,   550,   551,   552,   552,   552,   553,   554,
     554,   555,   555,   556,   556,   557,   557,   558,   558,   559,
     559,   559,   559,   559,   559,   560,   561,   562,   563,   563,
     564,   564,   565,   565,   566,   566,   566,   567,   567,   567,
     567,   567,   567,   568,   568,   568,   568,   568,   569,   570,
     571,   571,   572,   572,   572,   572,   572,   572,   572,   572,
     572,   573,   573,   574,   574,   574,   574,   574,   574,   574,
     574,   574,   574,   574,   574,   574,   574,   574,   574,   574,
     574,   574,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   575,   575,   576,   576,   577,   578,
     579,   579,   580,   581,   582,   582,   583,   584,   585,   586,
     586,   587,   587,   587,   588,   589,   589,   589,   590,   590,
     591,   592,   592,   593,   594,   594,   595,   596,   596,   597,
     598,   598,   599,   600,   600,   601,   601,   602,   602,   603,
     604,   605,   606,   606,   607,   608,   608,   609,   610,   610,
     610,   610,   610,   610,   610,   610,   611,   612,   613,   613,
     614,   614,   615,   615,   616,   617,   617,   618,   618,   618,
     619,   620,   620,   621,   621,   622,   623,   623,   624,   625,
     625,   626,   626,   627,   628,   629,   630,   631,   631,   632,
     632,   632,   633,   634,   634,   635,   635,   635,   636,   636,
     637,   637,   638,   638,   638,   638,   638,   638,   638,   638,
     638,   638,   638,   639,   641,   640,   640,   642,   642,   643,
     644,   645,   645,   646,   647,   648,   648,   649,   650,   650,
     651,   651,   652,   653,   654,   655,   655,   656,   656,   657,
     658,   658,   659,   659,   660,   660,   661,   661,   662,   662,
     662,   662,   662,   662,   662,   662,   662,   662,   663,   663,
     664,   664,   665,   666,   666,   667,   668,   669,   669,   669,
     670,   670,   671,   671,   672,   673,   673,   674,   675,   675,
     675,   676,   676,   677,   677,   677,   678,   678,   679,   680,
     680,   681,   681,   681,   681,   681,   681,   681,   682,   683,
     684,   685,   686,   686,   686,   687,   688,   689,   690,   690,
     691,   691,   692,   692,   692,   692,   692,   692,   692,   692,
     692,   693,   693,   694,   694,   694,   694,   694,   695,   696,
     696,   697,   697,   697,   697,   698,   699,   700,   700,   701,
     701,   702,   702,   703,   704,   705,   706,   707,   708,   708,
     709,   710,   710,   711,   711,   712,   712,   713,   713,   714,
     714,   715,   716,   716,   716,   716,   716,   717,   718,   719,
     719,   720,   721,   721,   722,   723,   723,   724,   725,   726,
     726,   727,   727,   728,   728,   729,   729,   729,   729,   730,
     731,   732,   733,   734,   735,   735,   736,   737,   737,   738,
     738,   739,   740,   741,   742,   743,   743,   744,   745,   746,
     747,   748,   749,   750,   751,   751,   752,   752,   752,   753,
     754,   755,   755,   756,   756,   757,   757,   758,   759,   759,
     760,   760,   761,   761,   762,   763,   764,   764,   764,   765,
     766,   766,   767,   768,   769,   769,   770,   771,   772,   772,
     772,   772,   772,   772,   772,   772,   772,   772,   772,   772,
     772,   772,   772,   772,   772,   772,   772,   772,   772,   772,
     772,   772,   772,   772,   773,   774,   775,   775,   776,   776,
     777,   777,   777,   777,   777,   777,   777,   777,   777,   778,
     779,   780,   781,   782,   783,   784,   785,   785,   785,   786,
     787,   788,   789,   790,   791,   791,   791,   791,   791,   791,
     791,   791,   791,   791,   791,   791,   791,   791,   792,   792,
     793,   793,   794,   794,   794,   794,   795,   795,   796,   797,
     797,   798,   798,   799,   799,   800,   800,   800,   800,   800,
     800,   801,   802,   802,   803,   803,   803,   803,   804,   804,
     805,   805,   806,   806,   807,   807,   808,   808,   809,   809,
     810,   811,   812,   813,   813,   814,   814,   815,   815,   816,
     816,   816,   816,   816,   816,   816,   816,   816,   816,   816,
     817,   818,   818,   819,   820,   820,   821,   822,   823,   824,
     825,   826,   827,   828,   829,   829,   830,   830,   831,   831,
     832,   833,   833,   833,   833,   834,   835,   836,   836,   836,
     836,   836,   836,   836,   837,   838,   839,   839,   839,   840,
     840,   840,   841,   841,   842,   842,   843,   843,   843,   844,
     844,   844,   844,   844,   845,   846,   847,   848,   848,   849,
     849,   850,   851,   852,   853,   853,   854,   854,   854,   854,
     854,   854,   855,   856,   857,   858,   859,   860,   860,   861,
     861,   862,   863,   864,   864,   865,   865,   865,   866,   867,
     868,   869,   869,   870,   870,   870,   870,   870,   871,   872,
     872,   873,   874,   874,   875,   875,   875,   875,   875,   876,
     876,   877,   877,   878,   878
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
       1,     1,     1,     1,     1,     1,     1,     1,     8,     6,
       8,     6,     1,     6,     6,     6,     6,     1,     3,     5,
       1,     3,     8,     6,     6,     4,     5,     5,     2,     2,
       0,     1,     3,     1,     4,     7,     1,     3,     3,     1,
       3,     5,     3,     3,     1,     3,     1,     1,     3,     3,
       3,     3,    10,     8,    10,     0,     0,     1,     2,     4,
       4,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     4,     4,     3,     9,     1,     1,
       3,     1,     5,     5,     9,     0,     1,     1,     3,     3,
       3,     3,     3,     6,     3,     3,     3,     3,     7,     5,
       1,     1,     3,     4,     1,     1,     3,     1,     1,     3,
       3,     2,     3,     4,     4,     5,     5,     1,     2,     4,
       4,     4,     0,     1,     2,     7,     6,     3,     3,     7,
       5,     1,     3,     1,     4,     2,     3,     3,     4,     6,
       3,     2,     3,     1,     1,     4,     5,     3,     6,     2,
       4,     2,     1,     3,     3,     0,     1,     3,     2,     2,
       2,     2,     9,     5,     1,     3,     2,     2,     2,     9,
       4,     1,     3,     1,     1,     2,     0,     7,     1,     4,
       1,     3,     1,     1,     1,    16,     0,     3,     3,     3,
       3,     6,     9,     5,     1,     3,     5,     1,     1,     1,
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
       1,     1,     1,     1,     3,     2,     5,     4,     2,     5,
       4,     2,     2,     1,     1,     3,     2,     2,     2,     4,
       4,     4,     4,     4,     4,     1,     1,     1,     3,     2,
       2,     1,     1,     3,     2,     2,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     2,     1,     1,     3,     1,
       1,     5,     5,     1,     3,     1,     1,     1,     5,     5,
       5,     1,     3,     2,     5,     2,     5,     5,     1,     1,
       3,     4,     1,     3,     5,     5,     5,     5,     7,     1,
       3,     2,     2,     2,     2
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
     537,   537,   537,   537,   339,   537,   784,   537,  1221,   537,
    1222,   537,   537,   339,   537,   537,   537,   537,   537,   537,
     537,   537,     0,     0,     0,     0,  1236,     0,   611,     0,
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
     630,  1029,  1028,  1030,  1031,  1032,  1033,  1034,  1035,  1036,
    1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,  1027,  1045,
    1046,  1047,  1048,  1049,  1050,  1051,  1052,  1053,   460,  1187,
    1189,  1191,  1192,  1188,  1190,  1193,   461,  1226,  1227,  1228,
    1229,  1230,  1231,     0,     0,   340,     0,     0,     0,     0,
       0,     0,     0,   991,    35,     0,     0,   598,     0,     0,
       0,     0,     0,     0,   454,   507,   481,   210,     0,     0,
       0,   481,     0,   312,   339,   727,     0,   727,   538,     0,
      23,   481,     0,   481,   971,     0,   988,   483,   481,   481,
     481,    32,   484,    81,   444,   954,   481,   948,   105,   481,
      37,   481,     0,   340,     0,     0,    63,     0,     0,   329,
      44,     7,   965,     0,     0,     0,   599,     0,     0,    77,
     340,     0,   985,   522,     0,     0,     0,   296,   295,     0,
       0,   813,     0,     0,   340,     0,     0,   538,     0,   340,
       0,     0,     0,   340,    33,   340,    22,   599,     0,    21,
       0,     0,     0,     0,     0,     0,     0,   398,   340,    45,
     140,     0,     0,     0,     0,     0,     0,     0,     0,   787,
     340,     0,   340,     0,     0,   989,   990,     0,   339,   340,
       0,     0,     0,   599,     0,  1173,  1172,  1177,  1054,   727,
    1179,   727,  1169,  1171,  1055,  1160,  1163,  1166,   727,   727,
     727,  1175,  1168,  1170,   727,   727,   727,   727,  1108,   727,
     727,  1185,  1142,     0,    45,  1195,  1198,  1201,    45,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    45,    45,
    1258,  1235,    45,   612,     4,    20,    20,     0,     0,    45,
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
     973,   974,   970,    45,   310,   808,   810,   972,    36,    13,
     598,     0,   481,     0,   192,     0,   310,     0,   184,     0,
     709,   707,   842,   926,   927,   807,   804,   805,   482,   516,
     222,   435,   310,   676,   982,   977,   470,   341,     0,     0,
       0,     0,     0,   719,   722,   711,     0,   497,   682,   679,
     680,   451,     0,     0,   500,   983,   442,   443,   458,   452,
     471,   106,   499,    45,   517,     0,   199,     0,   382,     0,
       0,    37,    25,   803,   800,   801,   324,   326,     0,     0,
      45,   966,   967,     0,   700,   698,   686,   683,   684,     0,
       0,     0,    78,     0,    45,   986,   984,     0,     0,   947,
       0,    45,     0,    19,     0,     0,     0,     0,   952,     0,
       0,     0,   497,   523,     0,     0,   930,   957,   599,     0,
     599,   600,   139,    34,    12,   143,   576,     0,   764,     0,
       0,     0,   727,   706,   704,   887,   924,   925,     0,   703,
     701,   958,   399,   514,     0,     0,     0,   908,     0,   920,
     919,   922,   921,     0,   691,     0,   689,   694,     0,     0,
      37,    24,     0,   310,   939,   942,     0,    45,     0,   302,
     298,     0,     0,   577,   310,     0,   527,     0,  1112,  1107,
     527,  1144,  1174,     0,   527,   527,   527,   527,   527,   527,
    1167,   310,    46,  1194,  1203,  1204,     0,     0,    46,  1223,
      45,     0,  1019,  1020,     0,   987,   349,     0,     0,     0,
       0,  1237,  1239,  1240,     0,     0,  1243,  1245,  1246,  1247,
       0,     0,  1251,     0,     0,  1262,     0,     0,    20,    43,
      38,    42,     0,    40,    17,    46,   310,   132,   134,   136,
     110,     0,     0,    20,   339,   148,   538,   598,   165,   146,
     310,   179,   181,   183,   187,   527,   190,   527,   196,   198,
     200,   209,     0,   213,     0,    45,     0,   449,   424,     0,
     351,   364,   363,   376,   362,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   598,     0,     0,   598,     0,     0,
     398,   404,   396,   512,     0,     0,   515,   570,   571,   575,
       0,   567,     0,   569,     0,   608,     0,     0,     0,     0,
       0,   554,   569,   558,     0,     0,   582,   548,   580,     0,
       0,   351,   353,   551,   586,   585,   553,   677,   310,   699,
     702,   705,   708,   310,   339,     0,   940,     0,    45,   758,
     178,     0,     0,     0,     0,     0,     0,   312,   812,     0,
     529,     0,   475,   479,     0,   469,   598,     0,   194,   185,
       0,   321,     0,   208,     0,   678,   598,     0,   786,   319,
     316,   313,   315,   320,   310,   727,   724,   733,   728,     0,
       0,     0,     0,     0,   725,   711,   727,     0,   790,     0,
     498,   539,     0,     0,     0,    18,   204,     0,     0,     0,
     206,   195,     0,   494,   492,   489,     0,    45,     0,   329,
       0,     0,   332,   330,     0,    45,   968,   381,   916,   963,
       0,     0,   961,     0,   561,     0,    87,    88,    86,    85,
      91,    90,   102,    95,    98,    97,   100,    99,    96,   101,
      94,    92,    89,    93,    83,     0,    84,   197,     0,     0,
       0,     0,     0,     0,   297,     0,   188,   436,     0,    45,
     953,   951,   133,   815,     0,     0,     0,   292,   539,   180,
       0,   579,     0,   578,   287,   287,     0,   759,     0,   727,
     711,   934,     0,     0,   931,   284,   283,    62,   281,     0,
       0,     0,     0,     0,     0,     0,   688,   687,   135,    14,
     182,   941,    45,   944,   943,   146,     0,   103,    47,     0,
       0,   695,     0,   727,   527,     0,  1141,  1111,  1106,   727,
     527,  1143,  1186,   727,   527,   727,   527,   527,   527,   727,
     527,   727,   527,   696,     0,     0,     0,     0,  1215,     0,
       0,  1202,  1206,  1208,  1207,    45,  1197,   850,  1216,     0,
    1200,     0,  1224,  1225,     0,     0,   994,    45,    45,    45,
       0,   390,   391,  1024,     0,     0,     0,     0,    45,  1232,
       0,     0,     0,    45,  1233,  1253,  1255,     0,     0,    45,
    1234,     0,     0,     0,     0,     0,    45,  1261,    28,    37,
       0,     0,    39,     0,    30,   159,   116,   310,   339,   118,
     120,     0,   121,   114,   122,   130,   129,   123,   124,   125,
       0,   112,   115,    26,     0,   310,     0,     0,   144,   177,
       0,     0,   222,   222,     0,   224,   217,   221,     0,     0,
       0,   352,     0,   359,   361,   358,   357,   375,   377,   371,
     365,   504,   368,   366,   369,   367,   370,   372,   374,   360,
     373,   378,   598,   411,   389,     0,   343,     0,   414,   415,
     401,   412,   403,     0,   598,   513,     0,   532,   530,     0,
     598,   566,   573,   574,   572,   601,   610,   605,   607,   609,
     606,   604,   565,   549,     0,     0,     0,   351,     0,     0,
       0,     0,     0,   697,   779,     0,   789,   792,   782,     0,
     791,   785,     0,   783,   784,   781,   774,     0,   429,     0,
       0,   506,     0,     0,     0,     0,   811,   477,   476,     0,
     474,     0,   193,     0,   527,   806,   427,   428,   432,     0,
       0,     0,   314,   317,   176,     0,   598,     0,     0,     0,
       0,     0,   712,   723,   310,   462,   727,   681,     0,   481,
       0,     0,   201,     0,   394,   976,     0,     0,     0,    16,
     802,   327,   337,     0,   333,   335,   331,     0,     0,     0,
       0,     0,     0,     0,   960,   685,   562,    80,    79,   128,
     126,   127,   340,     0,   487,   423,     0,     0,     0,     0,
     191,     0,   520,     0,     0,   727,     0,     0,    64,   527,
     505,   601,   138,     0,   142,    45,     0,   711,     0,     0,
       0,     0,   929,     0,     0,     0,     0,     0,   909,   911,
       0,   692,   690,     0,    45,   946,    45,   945,   145,   340,
       0,   502,     0,  1176,     0,   727,  1178,     0,   727,     0,
       0,   727,     0,   727,     0,   727,     0,   727,     0,     0,
       0,    45,     0,     0,     0,  1205,     0,  1196,  1199,   998,
     996,   997,    45,   993,     0,     0,     0,   350,   598,   598,
       0,  1023,  1026,     0,    45,  1238,     0,     0,     0,  1244,
       0,     0,     0,  1252,    45,     0,     0,     0,    45,  1263,
      15,    29,    41,     0,   173,   160,   117,     0,    45,     0,
      45,    27,   159,   539,   539,   169,   172,   168,     0,   186,
     189,   214,     0,     0,     0,   247,   245,   252,   249,   263,
     256,   261,     0,     0,   215,   238,   250,   242,   253,   243,
     258,   244,     0,   237,     0,   232,   229,   218,   219,     0,
       0,   425,   351,     0,   387,   598,   347,   344,   345,     0,
     398,     0,   534,   533,     0,     0,   581,   352,     0,     0,
       0,   351,   588,   351,   592,   351,   590,   310,     0,   598,
     518,     0,     0,   975,     0,   311,   478,   480,   172,   322,
       0,   598,   519,     0,   979,   598,   978,   318,   320,   726,
       0,     0,     0,   736,     0,     0,     0,     0,   710,   464,
     481,   501,     0,   203,   202,   381,   493,   490,   488,     0,
     491,     0,   328,     0,     0,     0,     0,     0,     0,   962,
       0,  1008,     0,     0,   422,   417,   949,   950,   721,   310,
     956,   437,   816,   818,   824,   294,   293,     0,   287,     0,
       0,   289,   288,     0,   760,   761,   713,     0,   938,   937,
       0,   935,     0,   932,   282,     0,  1014,  1003,     0,  1001,
    1004,   755,     0,     0,   923,   915,   693,     0,     0,     0,
       0,     0,   300,     0,   299,   307,     0,  1185,     0,  1185,
    1185,  1121,     0,  1115,  1117,  1118,  1116,   727,  1120,  1119,
       0,  1185,   727,  1139,  1138,     0,     0,  1182,  1181,     0,
       0,  1185,     0,  1185,     0,   727,  1060,  1064,  1065,  1066,
    1062,  1063,  1067,  1068,  1061,     0,  1149,  1153,  1154,  1155,
    1151,  1152,  1156,  1157,  1150,  1159,  1158,   727,     0,  1102,
    1104,  1105,  1103,   727,     0,  1132,  1133,   727,     0,     0,
       0,     0,     0,     0,  1217,     0,     0,   851,   995,     0,
    1021,     0,   598,     0,  1025,     0,     0,     0,     0,     0,
       0,     0,     0,  1259,     0,     0,     0,  1269,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   794,     0,   111,
       0,   173,     0,   146,     0,   171,   170,   267,   253,   266,
       0,   255,   260,   254,   259,     0,     0,     0,     0,     0,
     222,   212,   223,   241,     0,   222,   234,   235,     0,     0,
       0,     0,   278,   223,   279,     0,     0,   227,   268,   273,
     276,   229,   220,     0,   503,     0,   413,   385,   388,     0,
     346,     0,   531,   568,   569,     0,     0,   351,     0,     0,
       0,   778,   772,   788,     0,     0,     0,   525,     0,   340,
     526,     0,   981,     0,     0,     0,   740,     0,   738,   735,
     730,   734,   732,     0,    45,     0,   463,   450,   205,   334,
     336,     0,     0,     0,   964,   959,   131,     0,  1007,   421,
       0,     0,   416,   955,     0,    45,   814,   825,   826,   831,
     835,   828,   836,   837,   832,   834,   833,   829,   830,     0,
       0,     0,     0,   285,     0,     0,     0,     0,   933,   928,
     472,     0,  1000,   727,   910,     0,     0,   885,   104,   306,
     301,   303,   305,     0,     0,     0,  1070,   727,  1071,  1072,
      45,  1113,   727,  1140,  1136,   727,  1185,     0,  1069,    45,
    1073,     0,  1074,     0,  1058,   727,  1147,   727,  1100,   727,
    1130,   727,  1209,  1210,  1211,  1219,  1220,    45,  1214,  1212,
    1213,     0,     0,     0,   393,  1242,   897,   898,   899,   896,
     901,   895,   902,   894,   893,   892,   900,   888,     0,     0,
      45,  1241,  1249,  1250,  1248,  1256,  1254,     0,  1257,  1271,
    1272,    45,  1264,  1265,  1266,  1267,  1273,  1274,     0,    31,
     175,   174,     0,     0,   119,   113,   107,     0,     0,   161,
     598,   166,     0,   248,   246,   264,   257,   262,   216,   222,
     598,     0,   240,   236,   223,     0,   233,     0,   270,   269,
       0,   225,   229,     0,     0,     0,     0,     0,   230,     0,
     426,   386,   348,   397,     0,   583,   595,   597,   596,     0,
     430,     0,     0,   809,     0,   433,     0,   980,   756,   729,
       0,     0,    45,     0,     0,     0,   843,   969,   844,  1013,
       0,  1010,  1012,   420,   419,     0,     0,   817,     0,   827,
       0,   288,     0,     0,   765,   762,   719,   714,   715,   717,
     718,   936,  1002,  1006,     0,     0,   381,     0,     0,     0,
       0,   309,   308,   521,     0,     0,     0,  1114,  1137,     0,
    1184,  1183,     0,     0,     0,  1059,  1148,  1101,  1131,  1218,
       0,     0,   392,     0,     0,     0,  1260,  1270,     0,     0,
       0,   795,   162,   163,     0,     0,   239,   598,   241,     0,
     280,   228,     0,   272,   271,   274,   275,   277,   473,     0,
     770,   769,   771,     0,   767,   431,     0,   992,   434,     0,
     741,   739,     0,   731,     0,     0,     0,  1009,   418,     0,
       0,     0,     0,     0,   906,     0,     0,     0,     0,     0,
       0,   286,   291,   290,     0,     0,     0,   999,   912,   913,
       0,   841,   886,   886,   304,  1086,  1085,  1084,  1091,  1092,
    1093,  1090,  1087,  1089,  1088,  1097,  1094,  1095,  1096,     0,
    1081,  1125,  1124,  1126,  1127,     0,  1186,  1076,  1078,  1077,
       0,  1080,  1079,     0,  1022,     0,     0,   889,  1268,   796,
       0,   172,   265,     0,     0,   227,   226,     0,     0,   766,
     510,     0,     0,     0,   466,  1011,   823,   822,     0,   820,
     727,   855,     0,     0,     0,     0,     0,   904,   905,     0,
       0,     0,     0,   716,   917,  1005,    45,     0,     0,     0,
       0,     0,  1123,  1180,  1075,    45,   890,     0,     0,     0,
     251,   231,   495,   768,   757,   744,   737,   742,     0,     0,
     819,   860,   856,     0,     0,     0,     0,     0,     0,     0,
       0,   847,     0,   467,   720,     0,     0,   840,    45,    45,
     883,  1083,  1082,     0,     0,     0,   354,   799,   793,   797,
     167,     0,     0,   465,   821,     0,     0,     0,     0,   853,
     845,     0,   839,     0,   903,   854,     0,   846,     0,   918,
       0,     0,     0,  1122,     0,   891,     0,   496,     0,   747,
       0,   745,   748,   858,   859,     0,   861,   863,     0,     0,
       0,   848,   468,   914,   884,   882,     0,   798,   750,   751,
       0,   743,     0,   857,     0,   852,   838,     0,     0,     0,
       0,   749,   752,   746,   862,     0,     0,   866,   907,   849,
    1016,   753,     0,     0,     0,   864,    45,  1015,   754,   868,
     867,    45,     0,     0,     0,   869,   874,   876,   877,  1017,
    1018,     0,     0,     0,    45,   865,    45,    45,   598,   880,
     879,   878,   870,     0,   872,   873,     0,   875,     0,    45,
     881,   871
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   208,   384,   209,   840,   751,   210,
     914,   619,   804,   689,   569,   912,   913,   441,   915,  1231,
    1520,   211,   212,   620,  1135,  1136,   213,   214,   215,   579,
    1300,  1301,  1139,  1302,   216,   217,   218,   219,  1164,   220,
     221,  1165,   222,   582,   223,   224,   225,   226,  1584,  1585,
     929,  1596,   948,  1866,   227,   228,   229,   230,   231,   232,
     785,  1175,  1176,   233,   234,   235,   746,  1087,  1088,   236,
     237,   710,   453,   941,   942,  1612,   943,   944,  1904,  1622,
    1627,  1628,  1905,  1906,  1623,  1624,  1625,  1614,  1615,  1616,
    1617,  1878,  1619,  1620,  1621,  1880,  2128,  1908,  1909,  1910,
    1177,  1178,  1492,  1493,  1993,  1732,  1156,  1157,   238,   458,
     239,   850,  2010,  2011,  1764,  2012,  1038,   718,   719,  1061,
    1062,  1050,  1051,   240,   756,   757,   758,   759,  1103,  1453,
    1454,  1455,   397,   374,   404,  1345,  1636,  1346,   885,  1010,
     622,   641,   623,   624,   625,   626,  1253,  1090,   981,  1918,
     823,   627,   628,   629,   630,   631,  1350,  1638,   632,  1320,
    1915,  1418,  1399,  1419,  1031,  1148,   241,   242,  1956,   243,
     244,   692,  1043,  1044,   709,   423,   245,   246,   247,   248,
    1094,  1095,  1447,  1925,  1926,  1081,   249,   250,   251,   252,
    1213,   253,   984,  1358,   254,   376,   727,  1436,   255,   256,
     257,   258,   259,   260,   652,   644,   990,   991,   992,   261,
     262,   263,  1007,  1008,  1013,  1014,  1015,  1347,   769,   645,
     801,   564,   264,   265,   266,   713,   267,   729,   730,   268,
     767,   768,   269,   499,   835,   836,   838,   270,   271,   765,
     272,   820,   273,   814,   274,   701,  1078,   275,   276,  2177,
    2178,  2179,  2180,  1719,  1075,   407,   721,   722,  1074,  1684,
    1747,  1947,  1948,  2376,  2377,  2440,  2441,  2459,  2471,  2472,
    1752,  1945,   277,   278,  1734,   673,   809,   810,  1933,  2243,
    2244,  1934,   670,   671,   279,   280,   281,   282,  2092,  2093,
    2408,  2409,   283,   754,   755,   284,   706,   707,   285,   685,
     686,   286,   287,  1154,  1724,  2167,  2338,  2339,  1976,  1977,
    1978,  1979,  1980,   703,  1981,  1982,  1983,  2392,  1238,  1984,
    1985,  1986,  2341,  2417,  2445,  2446,  2476,  2477,  2494,  2495,
    2496,  2497,  2498,  2509,  1987,  2189,  2358,   816,  1847,  2067,
    2068,  2069,  1988,   828,  1507,  1508,  2005,  1171,  2355,   288,
     289,   290,   291,   292,   293,   294,   295,   797,  1173,  1174,
    1740,  1741,   296,   844,   297,   780,   298,   781,   299,  1151,
     300,   301,   302,   303,   304,  1111,  1112,   305,   762,   306,
     307,   308,   681,   682,   309,   310,  1421,  1674,   715,   311,
     312,   776,   313,   314,   315,   316,   317,   318,   319,  1245,
    1246,   320,  1181,  1748,  1749,  2277,   321,  1712,  2160,  2161,
    1750,   322,  2487,   323,   324,   325,   326,  1254,   327,   328,
     329,   330,   331,   332,  1214,  1795,   862,  1773,  1774,  1775,
    1799,  1800,  1801,  2310,  1802,  1803,  1776,  2195,  2402,  2299,
     333,  1220,  1823,   334,   335,   336,   337,  1204,  1777,  1778,
    1779,  2305,   338,  1222,  1827,   339,  1210,  1782,  1783,  1784,
     340,   341,   342,  1216,  1817,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
    1788,  1789,   863,  1529,   358,   359,   360,   361,   362,   873,
     874,   875,  1232,  1233,  1234,  1239,  1833,  1834,   363,   364,
     365,   879,   366,   367,   368,   369,   370,   371,   890,   891,
     892,   893,   895,   896,   897,   898,   899,   901,   902,   561,
    1854,   372,   904,   905,  1856,  1857,  1862
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -2051
static const yytype_int16 yypact[] =
{
   -2051,    85, -2051, -2051, -2051, -2051,    38,  4777, -2051, -2051,
   -2051,   145, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,   668, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051,    91, -2051, -2051,   756,   151, -2051, -2051, -2051,    91,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051,   224,   224, -2051, -2051, -2051, -2051, -2051,   224,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
     222, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,   224, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051,   446, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
     484,   382, -2051, -2051, -2051, -2051, -2051,    91, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051,    91, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051,   488,   508,   548,   224, -2051,   581,   377,  1024,
     626,   377, -2051, -2051, -2051,   648,   651,   686,   708, -2051,
   -2051, -2051,   694,   712,   224, -2051, -2051,   718,   727,   766,
     784,   692,   203,   809,   813,   834, -2051,   149, -2051, -2051,
   -2051,   377, -2051, -2051, -2051,   857,   986,  1852,  2016, -2051,
   -2051,  2662, -2051,   856, -2051, -2051,  1539, -2051,   864, -2051,
   -2051,  1655,   864,   841, -2051, -2051,   894, -2051, -2051, -2051,
     900,   920,   932,   957,   984, -2051, -2051, -2051, -2051,   998,
    1032, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051,  1000, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051,   115,   224,   987,   997,  1014,   883,   224,
     224,   148,   224, -2051,   224,   224,  1030, -2051,   176,  1033,
     224,   224,   224,   224, -2051, -2051,   224, -2051,  1036,   224,
     911,   224,  1056, -2051, -2051, -2051,   224, -2051,  1053,   224,
   -2051,   224,  1055,   158, -2051,   911, -2051,   224,   224,   224,
     224, -2051, -2051, -2051, -2051, -2051,   224, -2051,   224,   224,
     626,   224,  1071,   987,   224,  1081, -2051,   224,   224, -2051,
   -2051, -2051,  1108,  1103,   224,   224, -2051,  1105,  1107,   224,
     987,  1111,  2662, -2051,  1125,  1148,   224, -2051,  1120,   224,
    1132, -2051,  1160,   224,   987,  1178,  1180, -2051,   883,   987,
     224,   224,  1791,    77,   224,   134, -2051, -2051,   172, -2051,
     174,   224,   224,   224,  1197,   224,   224,  2662,   144, -2051,
   -2051,  1225,   224,   224,   224,   224,   224,  2626,   224, -2051,
     987,   224,   987,   224,   224, -2051, -2051,   224, -2051,   987,
     224,  1231,  1235, -2051,   224, -2051, -2051,  1246, -2051, -2051,
    1249, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051,  1256, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051,   224, -2051, -2051,  1271,  1288, -2051,  1295,
    2662,  2662,  2662,  2662,  2662,  1299,  1302, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051,  1049,   141, -2051,
   -2051,   224,   224,   224,   224,  1313, -2051, -2051,  1171,   224,
     224, -2051,   573,   224,   224,   224,   224,   224,   271,   224,
    1132,   224,   224,  1071, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051,  1085, -2051, -2051, -2051, -2051, -2051, -2051,  2662,
    2662,  2662, -2051,  2662, -2051, -2051, -2051, -2051, -2051, -2051,
    2662,  3058, -2051,    66,  1319, -2051,  1311, -2051,  1086,  1106,
    1359, -2051, -2051,  1337,  2662, -2051, -2051,  1503, -2051, -2051,
    1355,  1344,  1319, -2051, -2051,   630,    -5, -2051,  1503, -2051,
   -2051, -2051,  1385,   180,   163,  2768,  2768,   224,   224,   224,
     224,   224,   224,   224,  1389, -2051,   224, -2051, -2051, -2051,
     281, -2051, -2051,  1383,   224, -2051,  2662, -2051,  1170,   529,
   -2051,  1405, -2051, -2051,  1414,  1392, -2051, -2051, -2051, -2051,
   -2051,  2677,   224,  1439, -2051,   224,  1414,   224, -2051,   883,
   -2051, -2051, -2051, -2051, -2051, -2051,  1448, -2051, -2051, -2051,
   -2051, -2051,  1414, -2051, -2051,  1455, -2051, -2051,   517,  1220,
     224,   592,    90, -2051,  1457,  1247,  2662,  1326, -2051,  1472,
   -2051, -2051,  2662,  2662, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051,   224, -2051,   224,  1466,   206,
     224,   626, -2051, -2051,  1474, -2051,  1476, -2051,  1470,  1255,
   -2051,  1484, -2051,   224, -2051, -2051, -2051,  1487, -2051,   864,
    1475,  3167, -2051,   224, -2051,  5742, -2051,   224,  2662, -2051,
    1481, -2051,   224, -2051,   224,   224,   224,  1319,   929,   224,
     224,   224,  1326, -2051,   224,   499, -2051, -2051, -2051,  1344,
     630, -2051, -2051, -2051, -2051, -2051, -2051,   115, -2051,  1383,
    1491,  1457, -2051, -2051, -2051, -2051, -2051, -2051,   224, -2051,
   -2051, -2051,  5742, -2051,   176,  1441,   224, -2051,  1489, -2051,
   -2051, -2051, -2051,  1490,  3365,   658, -2051, -2051,   446,   224,
     626, -2051,   224,  1414, -2051,  1498,  1492, -2051,   224, -2051,
    1502,  2662,  2662, -2051,  1414,   224,   207,   224,  1228,  1228,
     215,  1228, -2051,  1496,   305,   337,   398,   465,   466,   479,
   -2051,  1414,   959, -2051,  1508, -2051,   182,   186,  1203, -2051,
   -2051,  3586,  5742,  3627,  3667,  1515,  5742,   224,   224,    23,
     678, -2051, -2051, -2051,    55,   735, -2051, -2051, -2051, -2051,
     594,   736, -2051,   439,   780, -2051,   224,   224, -2051, -2051,
   -2051, -2051,   783, -2051, -2051,  1314,  1414, -2051, -2051, -2051,
   -2051,  1637,   224, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
    1414, -2051, -2051, -2051, -2051,  1518, -2051,  1518, -2051, -2051,
   -2051, -2051,   280, -2051,   185, -2051,  1519, -2051, -2051,  3720,
    1525,  1533,  1533,  2503, -2051,  2662,  2662,  2662,  2662,  2662,
    2662,  2662,  2662,  2662,  2662,  2662,  2662,  2662,  2662,  2662,
    2662,  2662,  2662,  2662, -2051,  1483,  1420,  1537,    29,   169,
    2662, -2051, -2051, -2051,   807,  1433, -2051, -2051, -2051, -2051,
     811, -2051,  1167,   835,  2662,  1548,  1344,  1344,  1344,  1344,
    1344, -2051,   902, -2051,   180,   180,  1319,  1552, -2051,  2768,
    5742,   159,   209, -2051,  1556,  1560, -2051, -2051,  1414, -2051,
   -2051, -2051, -2051,  1414, -2051,   536, -2051,   115, -2051, -2051,
   -2051,   224,  3843,   224,  1554,  2662,  1504, -2051, -2051,   224,
   -2051,  2662,  3877, -2051,   815, -2051, -2051,  1540, -2051, -2051,
     816, -2051,   224, -2051,   224, -2051, -2051,  1220, -2051, -2051,
   -2051, -2051, -2051,  3936,  1414, -2051, -2051, -2051,  1558,  1561,
    1563,  1565,  1568,  1569, -2051,  1247, -2051,   224, -2051,  3980,
   -2051, -2051,   224,  4023,  4054, -2051,  1570,   825,  1578,  1359,
   -2051, -2051,   224, -2051,  1580, -2051,  1566, -2051,   224, -2051,
    1460,   107, -2051, -2051,    76, -2051, -2051,  1594, -2051,  1589,
    1598,   879, -2051,   224,  2768,  1586, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051,  1587, -2051, -2051,   349,  1590,
    1592,  4085,  2723,   -65, -2051,  1577, -2051, -2051,   880, -2051,
   -2051, -2051, -2051, -2051,   882,  1591,   901, -2051, -2051, -2051,
    2662, -2051,  1604, -2051, -2051, -2051,   906, -2051,  1608, -2051,
    1247,  1601,  1611,   908, -2051, -2051, -2051,  1616, -2051,  1614,
    1615,  1593,   224,  2662,  2662,  2626, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051,  1618,  1625, -2051,   775, -2051, -2051,  4135,
    4199, -2051,  1621, -2051,   481,  1622, -2051, -2051, -2051, -2051,
     542, -2051, -2051, -2051,   572, -2051,   596,   609,   611, -2051,
     617, -2051,   618, -2051,  1620,  1629,  1630,  1631, -2051,  1632,
    1633, -2051, -2051, -2051, -2051, -2051, -2051,  1319,  1641,  1635,
   -2051,  1636, -2051, -2051,   -46,   909, -2051, -2051, -2051, -2051,
    2662,   515,   645, -2051,   938,   947,  1638,  1644, -2051, -2051,
    1646,  1649,  1651, -2051, -2051, -2051,  1652,  1658,  1661, -2051,
   -2051,  1662,  1663,  1665,  1668,  1669, -2051, -2051, -2051,   626,
     224,   119, -2051,  1671, -2051,  1645, -2051,  1414, -2051, -2051,
   -2051,  1672, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
    1058, -2051, -2051, -2051,   224,  1414,   122,  1473, -2051, -2051,
     224,   224, -2051,   846,   185, -2051,  1674, -2051,  1575,  2662,
    2768, -2051,  2662,  1533,  1533,   676,   676,  2503,   633,  3275,
    3092,  5742,  3092,  3092,  3092,  3092,  3092,  3275,  1402,  1533,
    1402,  3216,  1537, -2051, -2051,  1673,  1643,  2465, -2051, -2051,
   -2051, -2051, -2051,  1683, -2051, -2051,   883,  5742, -2051,  2662,
   -2051, -2051, -2051, -2051,  5742,   545,  5742,  1548,  1548,  1276,
    1548,   682, -2051,  1552,  1684,   180,  4241,  1685,  1690,  1693,
    2768,  2768,  2768, -2051, -2051,   224,  1687, -2051, -2051,  1691,
    1457, -2051,   446, -2051, -2051, -2051, -2051,  1456, -2051,   950,
     883, -2051,   883,   952,  1698,   956, -2051,  5742,  2662,  2677,
   -2051,   972, -2051,   883,  1518, -2051,   797,   842, -2051,   976,
    1546,   988, -2051,  2125, -2051,    90, -2051,  1699,   224,   224,
    2662,   224, -2051, -2051,  1414, -2051, -2051, -2051,  1479,   224,
    2662,   224, -2051,   224, -2051,  1319,  2662,  1692,  2723, -2051,
   -2051, -2051, -2051,   995, -2051,  1705, -2051,  1700,  1707,  1708,
    1517,  2662,   224,   224, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051,   987,   224, -2051,  2841,  3001,  1706,   224,   224,
   -2051,   224, -2051,     8,   224, -2051,  2662,   224, -2051,  1518,
    5742, -2051,  1720,   108,  1720, -2051,   224,  1247,  1724,  2872,
     224,   224, -2051,   176,  2662,   584,  2662,  1005, -2051,  1717,
    1006,  5742, -2051,    45, -2051, -2051, -2051, -2051, -2051,   987,
      30, -2051,   224, -2051,   595, -2051, -2051,   -45, -2051,   101,
     820, -2051,   799, -2051,    10, -2051,   -44, -2051,   224,   224,
     224, -2051,   224,   224,   959, -2051,   224, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051,  1404,  1421,  1408,  5742, -2051,  1537,
     224, -2051, -2051,   224, -2051, -2051,   224,   224,   224, -2051,
     224,   224,   224, -2051, -2051,   224,   224,  2662, -2051, -2051,
   -2051, -2051, -2051,   224,   796, -2051, -2051,  1726, -2051,  1728,
   -2051, -2051,  1645, -2051, -2051, -2051, -2051,  5742,  2329, -2051,
   -2051, -2051,   118,   375,   375,  1493,  1497, -2051, -2051,  1499,
    1500,  1505,   469,   224, -2051, -2051, -2051, -2051,  1737, -2051,
   -2051, -2051,  1674, -2051,  1736, -2051,   114,  1733, -2051,  1734,
    4287, -2051,  1729,  1731,  1359, -2051, -2051,  4351, -2051,  2662,
    2662,  1433, -2051,  5742,  1503,   180, -2051,   248,  2768,  2768,
    2768,   296, -2051,   394, -2051,   397, -2051,  1414,   224, -2051,
   -2051,  1745,  1010, -2051,  1747, -2051,  5742, -2051, -2051, -2051,
    2662, -2051, -2051,  2662, -2051, -2051, -2051, -2051,  5742, -2051,
    1546,  2662,  1758, -2051,  1760,  1764,  4382,  1749, -2051,    89,
     224, -2051,  1016, -2051, -2051,  1761,  5742, -2051, -2051,  4351,
   -2051,  1460, -2051,  1460,   224,   224,   224,  1035,  1059, -2051,
     224,  1740,  1765,  2662,  4418,  2912, -2051, -2051, -2051,  1414,
    1319, -2051, -2051,  1617,  1781,  5742, -2051,   224, -2051,  1776,
    1777, -2051, -2051,  1538,  1786, -2051, -2051,  1792, -2051,  5742,
    1061, -2051,  1083, -2051, -2051,  4486, -2051, -2051,  1092, -2051,
   -2051,  5742,  1779,   224, -2051, -2051, -2051,  1783,  1788,  1597,
    1738,   224,   224,  1795,  1802, -2051,   334, -2051,  1796, -2051,
   -2051, -2051,  1799, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
     595, -2051, -2051, -2051, -2051,   -45,   224, -2051, -2051,  1113,
    1801, -2051,  1804, -2051,  1806, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051,   820, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,   799, -2051,
   -2051, -2051, -2051, -2051,    10, -2051, -2051, -2051,   -44,  1805,
    1808,  1809,   491,  1128, -2051,  1811,  1812,  1319, -2051,  1810,
   -2051,  1819,  1537,  1814, -2051,  1129,   891,  1137,  1139,  1143,
    1144,  1158,  1159, -2051,  1179,   -68,  1181, -2051,  1184,  1188,
    4521,   874,  1815,  1816,  2662,  2662, -2051, -2051,  1818, -2051,
    1807,   796,  2345, -2051,  1202, -2051,  5742, -2051, -2051, -2051,
    1828, -2051, -2051, -2051, -2051,    29,    29,    29,    29,    29,
     846, -2051,  1825,  1817,  1826,   846,  1733, -2051,   185,   114,
     117,   117, -2051, -2051, -2051,  1212,  1835,  1094,   458, -2051,
    1834,   114, -2051,  2662, -2051,  1797, -2051,  1359, -2051,  2465,
    5742,  1824, -2051, -2051,   630,  1831,  1829,  1224,  1833,  1837,
    1843, -2051, -2051, -2051,  1851,   110,   883, -2051,   224,   987,
    5742,   110,  5742,  1546,  2662,  1847,  4775,  1258, -2051, -2051,
   -2051, -2051, -2051,  2662, -2051,  1856, -2051, -2051, -2051, -2051,
   -2051,  1259,  1261,  1262, -2051, -2051, -2051,   217, -2051,  5742,
    2662,  2662,  5112, -2051,   224, -2051, -2051,  1781, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,  1848,
     108,  1849,  3167, -2051,   224,   224,   224,  2872, -2051, -2051,
   -2051,   584, -2051, -2051, -2051,  2557,   224, -2051, -2051,  1795,
    1844, -2051, -2051,   224,   224,  2662, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051,   101, -2051, -2051,
   -2051,  2662, -2051,  2662, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051,   224,   224,  1857,   844, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,  1862,  1864,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051,   224, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,  2662, -2051,
    5742,  5742,  1268,  1873, -2051, -2051, -2051,  1860,  5150, -2051,
   -2051, -2051,   118, -2051, -2051, -2051, -2051, -2051, -2051,   846,
   -2051,   224, -2051, -2051,  1867,  1858, -2051,   615,   458,   458,
     114, -2051,   114,   117,   117,   117,   117,   117,  1174,  5181,
   -2051, -2051, -2051, -2051,  2662, -2051, -2051, -2051, -2051,  1536,
   -2051,   224,  1877,  1392,   224, -2051,   224, -2051,  5212, -2051,
    2662,  2662, -2051,  5243,  1634,  2662, -2051, -2051, -2051, -2051,
    1280, -2051, -2051,  5742,  5742,  2662,  1872, -2051,   850, -2051,
    2662, -2051,  1868,  1869, -2051, -2051,  1876,  1884, -2051, -2051,
   -2051, -2051, -2051,  1763,  1875,  1286,  1886,  1892,  1290,   843,
     224, -2051, -2051,  5742,   647,  1881,    -2, -2051, -2051,  1866,
   -2051, -2051,   299,  5274,  5305, -2051, -2051, -2051, -2051, -2051,
    1294,  1885,   866,   224,   224,   891, -2051, -2051,  5336,  1900,
    1901, -2051, -2051, -2051,  1473,  1888, -2051,  1537, -2051,   114,
   -2051,  1174,  1889,   458,   458, -2051, -2051, -2051, -2051,  5367,
   -2051,  4351, -2051,  1317, -2051, -2051,   883,  1641, -2051,  1546,
    5742, -2051,  1656, -2051,  1897,  5398,   217, -2051,  5742,  2398,
    1899,  1902,  1904,  1907,  1908,  1909,   224,   224,  1912,  1913,
    5429, -2051, -2051, -2051,  2662,   224,   224, -2051, -2051,  1915,
     224, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,  1925,
   -2051, -2051, -2051, -2051, -2051,  1323, -2051, -2051, -2051, -2051,
    1894, -2051, -2051,  1926, -2051,   140,  1927, -2051, -2051, -2051,
    1929, -2051, -2051,  1895,  1342,  1174, -2051,  2662,  1536, -2051,
   -2051,  2662,   224,  2662, -2051, -2051, -2051,  5742,  1343, -2051,
   -2051,  1899,   224,   224,   224,   224,   224, -2051, -2051,  2662,
    2662,  2662,  1354, -2051, -2051,  1931, -2051,  1357,  1930,  1362,
     224,  2662, -2051, -2051, -2051, -2051, -2051,  2662,   224,  1920,
   -2051, -2051,  5460, -2051,  5742, -2051, -2051,  1928,  5491,  2398,
   -2051,   356, -2051,  1939,  1364,  1365,  1940,  1374,  1933,  1376,
    5522,  5553,  1932,  5584, -2051,   224,  1871, -2051, -2051, -2051,
   -2051,  1641, -2051,  5615,  1623,  5646,   954, -2051,  1947, -2051,
   -2051,  2662,  2109, -2051, -2051,  1950,  1951,   224,   224, -2051,
   -2051,   224, -2051,  2626, -2051, -2051,  2662, -2051,  2662, -2051,
    1938,  1380,  1382, -2051,  1945, -2051,   224,  5742,   224,  5742,
    1384, -2051, -2051, -2051, -2051,  1396, -2051,  1949,  1407,  1432,
    1436,  5677,  5742, -2051, -2051, -2051,  2662, -2051, -2051,  1948,
    2109, -2051,   224, -2051,  2662, -2051, -2051,  1952,  2662,  1438,
    2662,  1954, -2051, -2051, -2051,  5711,  1444, -2051, -2051,  5742,
    1958, -2051,  2662,  2662,  2662,  1953, -2051, -2051, -2051,  5742,
   -2051, -2051,   -64,   500,  1450, -2051,  1965,  1967, -2051, -2051,
   -2051,  1960,  1960,  1960, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051,   444,  1969, -2051,  1850, -2051,  1453, -2051,
   -2051, -2051
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2051, -2051, -2051, -2051, -2051,   -11,  1755,  1073, -2051, -2051,
    -672,   -52, -2051, -2051,  -380, -2051,   700, -2051,   -50,  -642,
   -2051, -2051, -2051,  2096,   -10, -2051, -2051, -2051, -2051, -2051,
   -2051,   113,   396,   793, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051,  -157,  -899, -2051, -2051, -2051,   892,   403,  1417,
   -2051,  -228, -1551,   129, -2051, -2051, -2051, -2051, -2051, -2051,
    1412,  -289,    -1, -2051, -2051, -2051,  1413, -2051,  -958, -2051,
   -2051, -2051, -2051,  1297, -2051, -2051,   693, -1274, -1546,  1064,
     388, -1540,  -218,  -110,  1070, -2051,   120,   126, -1789, -2051,
   -1528, -1253, -1527,  -298, -2051,   -85, -1564, -1642,  -909, -2051,
   -2051,   521,   860,   298,  -144,    39, -2051,   543, -2051, -2051,
   -2051, -2051, -2051,  -158, -2051, -1465,  -471,  1002, -2051,   977,
     612,   631,  -377, -2051, -2051,   942, -2051, -2051, -2051, -2051,
     344,   341,  1971,  3447,  -360, -1294,   128,  -460, -1014,   803,
    -555,  -620,  1793,   157,  1588,  -863, -1015, -2051, -2051,  -618,
    -602,  -238, -2051,  -944, -2051,  -628,  -938, -1122, -2051, -2051,
   -2051,   109, -2051, -2051,  1341, -2051, -2051,  1830, -2051,  1832,
   -2051, -2051,   646, -2051,  -382,    15, -2051, -2051,  1840,  1841,
   -2051,   608, -2051,  -728,  -307,  1264, -2051,   996, -2051, -2051,
     -87, -2051,  1011,   417, -2051,  4578,  -411, -1101, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051,  -192, -2051,   416,  -952, -2051,
   -2051, -2051,   343, -1282,  -614,  1054,  -945,  -384,  -350,  -429,
     754,   300, -2051, -2051, -2051,  1422, -2051, -2051,   999, -2051,
   -2051,   967, -2051,  1245, -1944,   903, -2051, -2051, -2051,  1430,
   -2051,  1434, -2051,  1429, -2051,  1437,  -996, -2051, -2051, -2051,
    -179,  -254, -2051, -2051, -2051,  -400, -2051,   800,   675,  -443,
     674, -2051,   -48, -2051, -2051, -2051,  -356, -2051, -2051, -2051,
   -1584, -2051, -2051, -2051, -2051, -2051, -1437,  -547,   112, -2051,
    -221, -2051,  1304,  1082, -2051, -2051,  1087, -2051, -2051, -2051,
   -2051,  -323, -2051, -2051,  1017, -2051, -2051,  1065, -2051,   178,
    1079, -2051, -2051,  -830, -2051, -2051, -2051,  -258, -2051, -2051,
     150, -2051,  -756,  -383,  -365, -2051, -2051, -2051, -1500, -2051,
   -2051, -2051,  -213, -2051, -2051,  -333, -2051,  -352, -2051,  -371,
   -2051,  -372, -1829, -1136,  -769, -2051,  -139,  -481,  -936, -2050,
   -2051, -2051, -2051,  -489, -1515,   393, -2051,  -755, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051,  -472, -1460,   650,
   -2051,   156, -2051,  1482, -2051,  1650, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -1436,   684, -2051,  1395, -2051,
   -2051, -2051, -2051,  1775, -2051, -2051, -2051,   220,  1743, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
     613, -2051, -2051, -2051,   165, -2051, -2051, -2051, -2051,   -96,
   -1848, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051,   610,   359,  -528, -1348, -1340, -1409,
   -1449, -1438, -1434, -2051, -1430, -1429, -1349, -2051, -2051, -2051,
   -2051, -2051,   345, -2051, -2051, -2051, -2051, -2051,   387, -1424,
   -1420, -2051, -2051, -2051,   342, -2051, -2051,   386, -2051,   285,
   -2051, -2051, -2051, -2051,   354, -2051, -2051, -2051, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,
     147, -2051,   152,  -131, -2051, -2051, -2051, -2051, -2051, -2051,
   -2051,   941, -2051,  1301, -2051,  -763, -2051,   133, -2051, -2051,
   -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051, -2051,   923,
   -2051, -2051, -2051,   919, -2051, -2051, -2051, -2051,   914, -2051,
   -2051, -2051, -2051,   912, -2051,   103, -2051
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1186
static const yytype_int16 yytable[] =
{
     410,   678,   817,   693,   829,   830,   831,   832,  1109,   704,
     422,   422,   982,   870,   821,   674,  1398,   430,   643,   716,
    1477,  1403,  1096,   643,  1252,  1000,  1708,  1012,  1012,   731,
    1308,   734,   986,  1359,  1349,  1349,   737,   738,   739,  1613,
    1742,  1352,  1016,   800,   740,  1874,   457,   742,  1633,   744,
     743,  1848,   567,  1850,   950,  1765,   792,  1489,  1255,  1735,
    1618,  2185,  1907,  1845,  1379,   437,   649,  1893,   476,   653,
     655,  1085,   479,   747,  1877,  1879,  1194,   761,   424,  1432,
     812,   974,  1897,  1809,   402,     2,     3,  1912,   459,  1193,
     773,   793,  2301,  1646,  1810,  1067,  1260,  1954,  1811,   697,
    1011,  1011,  1812,  1813,   789,   474,  2112,  1849,  1815,   794,
    1478,  -541,  1816,   802,  1241,   805,  1757,  1939,  2499,  2162,
     667,  1798,   668,  1808,   909,  1821,  1029,   806,   824,  1899,
    1900,  1901,  1899,   501,  1603,  1604,  1549,  1593,  1786,  2283,
     839,   402,   842,   976,   588,   590,   909,  1767,  1068,   848,
     595,   402,   724,   560,     8,  1729,   683,   594,   421,   421,
     373,  2366,   910,   853,  -527,  2317,   405,  1380,  1252,  1510,
      25,  -563,   581,   733,  1498,    29,  1069,  1457,   617,  -584,
    1000,  1804,  1796,  1814,  1806,  1822,  1819,   807,  1825,   405,
    1797,  1417,  1807,  -137,  1820,  1005,  1826,    47,    48,   694,
    1314,  1767,  1762,  1236,  1961,  1962,  1963,  1240,   993,   976,
    1609,   589,   995,   695,  1256,   594,  1070,  -593,  1768,  1002,
    -339,  1781,  1746,   594,  2159,  1048,   811,  1071,  2302,  -593,
     421,  1257,  1092,  1351,   643,     4,  1242,   421,  1769,   421,
    -527,  1055,  1206,   421,   421,  1457,   421,  2079,   421,   985,
    -141,    90,  -541,  1758,  2500,  1072,  -594,  1479,  2118,  2119,
     -61,    95,  1167,  1902,  1261,  1843,  1902,  1610,  -594,  1550,
     421,   617,  1551,  1284,  -339,  -584,   989,   421,  -527,  -563,
    -339,  2080,  2303,  1262,  1458,  1730,   440,   421,  1312,  1027,
    1459,  1110,  1769,  2304,   694,  1770,  1518,  1001,   421,   935,
    1003,   421,  1028,   421,  -587,   421,  1040,   121,   695,   421,
    1045,   421,   975,   594,   421,   421,  -587,  1313,   617,  1611,
    2226,   669,   672, -1110,  1076,  -593,  1700,   679,   680,   684,
     680, -1135,   688,   690,  -137,  2117,   696,   976,   700,   702,
     702,   705,     5,  1955,   708,   594,  1172,   712,  1073,   708,
    1881,  1883,  2115,   421,   723,  1598,  2113,   728,  1459,   708,
    2015,   708,  1594,  1646,  -594,   422,   708,   708,   708,  1809,
    1162,  1097,  1191,  1000,   708,  1000,   741,   708,  1353,   708,
    1810,  1012,  1000,  1201,  1811,   752,   753,   698,  1812,  1813,
     508,  -141,   764,   766,  1815,  1639,  1798,   772,  1816,   643,
    1223,   -61,  -591,   643,   779,  -589,   594,   783,  2162,  1808,
     643,  1169,  -587,   642,  -591,  1821,  -584,  -589,   642,   796,
    -563, -1057,   803,  1150,  1515,  1449,  1692,  1509,   723,   813,
     815,   815,   736,   819,   796,  1652,  1654,  1656,  1517,   825,
     827,   827,   827,   827,   827,  1285,   837,  1707,  1161,   841,
    1163,   843,   779, -1146,  1377,   846,  1804,  1796,   849,  1309,
    1189,   497,   854,  2125, -1110,  1797,  -593,  1609,  1673,  1814,
    1806,  1444, -1135,   594,   594,  1822,  1819,  1890,  1807,  2450,
    1825,  2233,  2234,  1693,  1820,  1694,  1012,   594,  1826,   594,
    2307,   871,  1872,  1873,   872,  2126,  1469,  1470,   878,   507,
    1466,  1736,   976,   557,  2415,  -594,  1891,   889,   894,   900,
    -591,   570,   903,  -589, -1162,  1306,   911,  1160,  -382,   916,
     917,   918,   696,   558,  1610,  1057,   921,   924,   925,  1471,
    1558,   930,   696,   696,   696,   696,  2416,   594,  1058,   938,
     939,   596,  1000,  1307,  -527,  1844,  2188,  1383,  2053,  2192,
     594,  2210,  1384,  -587,   906,   907,  2231,  1853,  2175,  1011,
    -565,   643, -1057,   559,  2442,  2228,   922,  1367,  1368,  1369,
    1370,  1371,  2501,   919,  1877,  1879,  1611,  1114,   926,  1386,
     594, -1165, -1099,   931,   932,   933,   934,  2308,   927,  1746,
    1342,   749,  1034,  1424, -1146, -1129,   562, -1109,  2309,  1681,
    1065,  2502,  1102,  1387,   594,   712,  1018,   764,   819,   813,
     700,  1023,  2442,  1066,   843,  1025,  1613,   594,  1388,   594,
     787,  2111,   696,  1389,  1390,   594,   594,   795,  2501,   642,
    1391,  2123,  2124,  1036,   563,   996,  2230,  1618,   955,   997,
     708,   568,   956,  1047,  2247,   696,   638,   639,  -383,   957,
     958,  -591,  2285,   998,  -589, -1162,   571,  2502, -1134,   572,
    1559,  -565,   985,  2286,  2287,  2325,  1185,   999,  1064,  2288,
     971,  2289,  1420,  1030,  -565,  -792,  -792,  2515,  2517,  1186,
    2290,   955,  2291,  1271,  2292,   956,  1258,   996, -1056,  1359,
    2521,   997,  1012,  1086,   573,  1091,  1049,  1252,  1093,  1259,
     587,   575,   576,  1652,  1654,  1656,  1631,  1109,  1109,  1252,
    1104,  1107, -1145,   971,  2316,  -527,   574,  2503,  1096,   999,
     580,  1137, -1165, -1099,  1138, -1161,   583, -1164,  1944,  -527,
    1144,  1143,  1145, -1098, -1128,   584, -1129,  1152, -1109,  1155,
    1851,  1852,   696,  1263,  1269,  1858,  1859,  1000,  1000,  1000,
    1000,  1000,  1012,  1012,  1012,   669,  1264,  1270,   643,   643,
     643,   643,   643,   402,  1392,  1011,  1107,  1632,  1272,  1203,
    2369,   403,   696,  1209,   585,  1829,  1830,  1831,  1215,  1835,
    1836,  1219,  1221,  1273,  1274,  1275,  1767,   696,  1276,    50,
     696,  1281,   586,  1159,   642,  1393,  1197,  1196,   642, -1134,
    -382,  1277,  -565,  1768,  1282,   642,  2293,  2045,  2046,  2294,
    1006,  1509,   974,  1509,  1864,  1354,  1586,   591,   577,  1360,
    2357,   592,  1865,  1409,  1413,  1651,  1653,  1655,  1355, -1056,
    1244,  2389,  1361,  1441,  1592,  2111,  1410,  1414,  1188,  1394,
     996,  1190,   593,  2385,   997,  -383,  1442,  -387,  1310,   656,
    1311,   638,   639, -1145,  1278,   841,  1365,   977,   998,   980,
    2401,  1602,  1603,  1604,   597,  2056, -1161,  2057, -1164,  -385,
    1303,   633,   999,  1605, -1098, -1128,  2058,  1769,  2059,   648,
    1770,   980,  1606,  1790,  2387,  1771,  2481,  1463,  1481,   118,
    1484,  2260,  1315,  1772,  2295,  1318,   122,  1280,  2488,  1580,
    1464,  1482,   657,  1485,  1790,  1607,  2384,   996,   658,  1487,
    1608,   997,  1304,  2056,  1027,  2057,  1501,  1552,   638,   639,
    2140,  1757,  1488,  1372,  2058,   998,  2059,  1495,   659,  1502,
    1553,  1265,  -384,  2323,  1266,  1267,  1268,  1149,  1609,   999,
     660,  1349,  1349,  1349,  1349,  1349,  1560,  2103,  2104,  2105,
    2106,  2107,  2296,  2297,  2298,  1484,   642,   976,  1659,  1561,
    1250,  2449,  -851,  1688,  1057,   661,  1295,  1639,  1562,  1296,
    1641,  1660,   421,  1663,  2099,   669,  1644,  1665,  1397,  1642,
    1354,  1401,  2448,  2141,  1671,  2261,  1685,   684,  1687,  2146,
    1767,  1673,   662,  1668,   402,  1610,  1675,  1672,  1509,  1989,
     705,  2060,  2061,  1701,  2062,  2063,   663,  1768,   666,  1676,
     646,  1767,   675,  1753,  1250,   654,  1702,  2242,  1413,  1457,
    1012,  1012,  1012,  1661,  1250,  1434,  1754,  1756,  1768,   676,
     728,  1937,   677,  1237,  1237,  2064,  1669,  1958,  1921,   664,
     665,  2262,  1680,  1250,   787,   691,   753,  1611,   699,  2060,
    2061,   711,  2062,  2063,   621,  1460,  1964,  1691,  1758,  2263,
     714,   766,  2216,   717,  1791,  1589,  1590,  1463,   726,  1997,
     732,  2264,  1252,  2265,  2266,    46,  2267,  2065,  1417,  2268,
    1965,  1769,  1998,  2064,  1770,  1791,   745,    25,  1792,  1771,
    2066,  1501,    29,  1927,  1653,  1655,   750,  1772,  1793,  1483,
    2001,  -230,  1769,  1794,  1999,  1770,  1224,  1225,    74,  1792,
    2123,  2124,  1710,  2002,    47,    48,   760,  1525,   763,  1793,
     770,  2027,   771,  1528,  1794,  2065,   774,  1531,   782,  1533,
    1531,  1531,  1459,  1535,  2028,  1537,  2047,  1546,  2066,  1226,
     777,    96,  1513,  1207,  1208,  2070,  1211,  1753,   565,  2048,
    2055,  1501,  1753,   642,   642,   642,   642,   642,  2071,  1761,
    2072,  1006,  1006,   778,  2073,  2074,  1484,  1484,    90,   784,
    2269,   109,  1362,   908,  1842,   786,  1363,   607,    95,  2075,
    2076,   608,   609,   610,   611,  1544,  1931,  2077,   787,  2081,
    2123,  2124,  1484,   790,   612,   791,  1484,  1554,  1555,  1556,
    2078,   613,  2082,   614,   598,  2083,  2242,   725,   889,  2084,
    2100,   787,   818,   894,  1252,  1924,  2235,  2236,  2237,   900,
    2120,  2086,  2087,  2101,   121,  1059,   903,  1060,  1581,   911,
     607,   615,  -587,  2121,   608,   609,   610,   611,   599,  2016,
     826,  2018,  2019,   605,   606,  1916,   851,   612,  1973,  1445,
     852,  1919,  1591,  2023,   613,   775,   614,   566,   696,   616,
    2352,   855,  1315,  2030,   857,  2032,  2151,  1546,   150,  1546,
    1546, -1185,  1598,  1227,  1228,  1935,  2219,  1229,  1230,  2152,
    2156,   996,  2157,  2158,   615,   997,   876,  1941,  2256,  2220,
     822,  1943,   638,   639,  1185,   923,   421,  2331,  1501,  2131,
     834,  2257,  1546,   877,  1000,  1882,  1884,  2279,  1957,  1599,
     880,  2281,   616,   999,   887,  2313,   617,   888,    25,   856,
     920,   858,   976,    29,   947,  2328,   977,  1670,   859,   860,
     861,  2361,   978,  1657,   864,   865,   866,   867,  2329,   868,
     869,  1928,  1929,  1930,  2362,    47,    48,  1373,  1374,   421,
    2120,  2379,   979,   881,   882,   883,   884,   886,   983,   799,
     638,   639,  1250,  2371,  2380,  1501,  2510,  2511,   618,   617,
    2399,   612,  1463,  1546,   980,  2394,  1683,  1683,  2397,  1683,
     614,   994,  1501,  2400,  1753,  2419,  2420,   708,  2070,  1086,
    2070,  1086,  2460,  1004,  1695,  2422,  1024,  2424,   807,    90,
    1039,  2454,  1727,  2455,  2462,  2461,   643,   955,   615,    95,
    1033,   956,   949,   951,   952,  1463,   953,  2463,   957,   958,
    1035,   618,  1077,   954,   959,   960,  1718,   962,  2465,  1037,
     964,   965,   966,   967,   968,  1155,   616,   822,  1356,   971,
    1501,  1731,  2469,   607,  1185,  1733,  1250,   608,   609,   610,
     611,   696,  2484,  2466,  1046,   121,  1052,  2467,  2504,  2480,
     612,  1635,  2431,  2432,  1759,  2485,  1760,   613,  1763,   614,
    1056,  2505,   405,   640,  2520,  1080,  1217,  1218,  1595,  1032,
    1082,   974,  1098,   607,  1099,  1100,  1101,   608,   609,   610,
     611,  1832,  1105,   617,  1042,  1113,  1142,   615,  1168,   150,
     612,  1115,  1244,  1179,  1182,  1183,  1192,   613,   987,   614,
    1198,  1212,   988,  1195,  1846,  1206,  1235,  1227,   799,   638,
     639,  2354,  1063,  1250,  1855,   616,   594,  1283,  1861,  1079,
     612,  1863,  1006,  1322,  1319,  1083,  1084,   615,  1138,   614,
    1870,  2240,   956,  1475,   635,   618,   607,  1343,   636,  1344,
     608,   609,   610,   611,   637,   638,   639,   997,  -342,  2142,
    1375,  1892,   421,   612,  1381,   616,   612,   615,  1382,  1402,
     613,  1404,   614,  1426,  1903,   614,  1427,  1412,  1428,  2144,
    1429,  1141,   617,  1430,  1431,  1440,  1443,  1109,  1446,  1452,
    2388,  1509,  1448,  1695,  2131,   616,  1695,  1695,  1695,   989,
     615,  -930,   421,   615,  1461,  1462,  1932,  1467,  1468,   996,
    1473,  1472,  1170,   997,  1480,  1496,  1499,  1486,  1500,  1506,
     638,   639,   617,  2187,  1503,  1491,  1514,   998,   616,  1504,
    1505,   616,   640,  1516,   618,  1538,  1720,  1629,   708,   989,
    2429,   999,  1523,  1526,  1539,  1540,  1541,  1542,  1543,  1546,
     926,  1635,   617,  1563,  1199,  1200,  1547,  1548,  1966,  1564,
     651,  1566,  2447,  1109,  1567,   421,  1568,  1570,   640,   989,
     637,   638,   639,  1571,   618,  1093,  1572,  1574,  1575,  1766,
    1576,  1286,   612,  1577,  1578,   617,  1583,  1588,   617,  1626,
    1640,   614,  1645,  1648,  1634,  1237,  1237,  1237,  1649,  1237,
    1237,  1650,   373,  1837,   618,  1664,   403,  2447,  2282,  2008,
    2009,  1658,   989,  1698,  1681,  1704,  2224,   787,  1690,   615,
    1237,  1703,  1705,  1706,  1287,  1458,  2227,  1717,  1728,   787,
    1288,  1737,  1755,  1839,  2026,  1869,  1840,   618,  1841,  1885,
     618,  1867,  1895,  1886,  1898,  1887,  1888,   616,  1911,  1913,
    1916,  1889,  1917,  1936,  1938,  1967,  1289,  1953,  1323,  1324,
    1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,  1334,
    1335,  1336,  1337,  1338,  1339,  1340,  1341,  2347,  2348,  1949,
    1290,  1950,  1291,   822,   640,  1951,  1968,  -494,  1357,  1975,
    1974,  1991,  1992,  1994,  1995,  1364,   798,  1366,  2006,  1996,
    2003,   642,  1006,  2007,   617,  1758,   799,   638,   639,  1757,
    2014,  2017,  1376,  2013,  2020,  1292,  2029,  2130,   612,  2031,
    1293,  2033,  2109,  2088,  1294,  2051,  2042,   614,  1295,  2043,
    2044,  1296,  2049,  2050,  2052,  2054,  2102,  2089,   886,  2094,
    -381,  2110,  2122,  2127,  1407,  2133,  2114,  1903,  1903,  1903,
    2135,  1286,  2190,  1297,  2136,   615,   618,  2134,  2137,  1903,
    1063,  1237,  1237,  1237,  2138,  1425,  2139,  1298,  2149,  2330,
    2383,  2155,  2386,  1299,  2170,  2172,  1433,  2213,  2212,  2214,
    2221,  2222,  -224,   616,  2229,  2246,   684,  2259,  2254,  2272,
    2273,  2274,  2275,  -842,  1287,  2276,  2278,    13,    14,  2280,
      15,    16,  2300,  2306,  2154,    20,  2314,  2319,  2320,  2322,
    2326,  2332,  2333,    23,  2340,  2364,  2370,  2342,    27,  2343,
     640,    30,  2344,  2345,  2346,  2168,  1289,  2349,  2350,    37,
    2356,    38,  2360,    40,  2365,  2367,  2368,  2398,  1731,  2395,
     617,  2410,  1932,  2412,  2176,  1476,  2418,  2421,  2423,  2430,
    1290,  2434,  1291,  2427,  2186,  2436,    59,  2443,  2444,  2453,
    2456,  2191,  1763,  1490,  2464,  2470,  2486,    70,  2491,  1497,
    2196,  2482,  2506,  2478,  2507,  2508,  2519,   578,  2501,  2202,
    1279,  1582,  2173,  2095,  1868,  1292,   886,  1511,   834,  1519,
    1293,    85,   618,  1456,  1294,  1871,  2321,  1832,  1295,   928,
    2096,  1296,   937,  1524,    93,  1601,   940,  1053,  1316,  1527,
    1896,  2324,  2232,  1530,  1317,  1532,  2108,  2225,  2116,  1534,
    2215,  1536,   102,  1297,  1744,  1494,  1990,  2271,   104,  2171,
    1726,  1855,  2284,  1662,  1422,  1677,   108,  1298,   110,  1405,
     112,  1451,   114,  1299,  1960,  1959,   436,  2132,  2518,   119,
    2145,   788,  1054,  1557,  1697,  1667,  1158,  1411,  1922,  1892,
    1923,    13,    14,  1378,    15,    16,   130,   131,  1903,    20,
    1903,  1903,  1903,  1903,  1903,  1903,   600,    23,   601,  1017,
    1465,  1437,    27,  1187,   143,    30,   602,   603,  1512,  1019,
    1021,   604,   787,    37,  1020,    38,  2353,    40,   787,  1022,
    1679,  1682,  2252,  2251,  2473,   155,  2174,  2373,   156,  1396,
    1597,  1166,  1395,  2457,  1746,  1450,  2143,  1415,  1406,   607,
      59,  2414,  1630,   608,   609,   610,   611,  2169,  2382,  2474,
    1059,    70,  2490,  2512,  2514,   607,   612,   815,  2009,   608,
     609,   610,   611,   613,  2359,   614,  2004,  1709,  1026,  2438,
    1637,  1743,   612,  2181,   845,    85,  1106,   687,   735,   613,
    2335,   614,  1643,  2147,  2035,  1838,  2182,  2022,    93,  2039,
    2041,  2025,  2037,   615,  2201,  2363,  1545,  1903,  2199,  1243,
    2209,  1565,  1569,  1573,  2217,     0,   102,     0,  1579,   615,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
     108,   616,   110,     0,   112,     0,   114,     0,  1237,     0,
       0,  1666,  1042,   119,   827,   827,     0,   616,     0,     0,
       0,     0,     0,  2176,     0,     0,  1678,   748,     0,     0,
     130,   131,     0,  1686,   787,     0,  1689,     0,   421,     0,
       0,     0,     0,   886,     0,     0,     0,     0,   143,  1696,
       0,  1699,     0,     0,   421,     0,   748,     0,   617,     0,
       0,     0,     0,   748,   886,     0,     0,     0,     0,   155,
       0,   808,   156,     0,   617,     0,     0,     0,  1714,     0,
    2375,     0,     0,     0,     0,  1723,     0,     0,     0,  1725,
    1107,     0,  1107,     0,     0,     0,     0,     0,     0,     0,
       0,  1237,  1739,     0,     0,     0,  2396,  1745,     0,  1751,
     618,     0,     0,     0,     0,  2404,  2407,     0,     0,     0,
       0,     0,     0,     0,     0,  1780,   618,     0,  1785,     0,
       0,  1805,     0,  1818,  1875,  1824,     0,  1828,     0,   607,
       0,     0,     0,   608,   609,   610,   611,     0,  1846,  1846,
    2097,     0,     0,     0,     0,   607,   612,     0,     0,   608,
     609,   610,   611,   613,     0,   614,     0,     0,     0,     0,
    2315,  1237,   612,     0,     0,     0,     0,     0,     0,   613,
    1860,   614,   936,     0,  2407,     0,  2458,     0,     0,     0,
       0,     0,     0,   615,     0,     0,     0,     0,     0,     0,
       0,  1876,     0,  2336,     0,     0,     0,     0,   607,   615,
       0,     0,   608,   609,   610,   611,     0,     0,     0,     0,
       0,   616,     0,     0,     0,   612,     0,     0,     0,     0,
       0,     0,   613,     0,   614,     0,  2492,   616,     0,     0,
       0,  2493,  1920,   822,  1357,     0,   748,     0,     0,     0,
       0,     0,     0,     0,  2493,     0,  2513,  2516,   421,     0,
       0,     0,   615,     0,     0,     0,     0,     0,     0,  2516,
       0,     0,  1475,  1940,   421,   607,  1942,     0,   617,   608,
     609,   610,   611,     0,  1946,     0,     0,     0,     0,     0,
     616,     0,   612,     0,   617,     0,     0,     0,     0,   613,
    1237,   614,     0,     0,     0,     0,     0,     0,   955,     0,
       0,     0,   956,     0,     0,     0,  1969,  1237,  1972,   957,
     958,     0,     0,     0,  2406,     0,   960,   421,   962,   615,
     618,   964,   965,   966,   967,   968,     0,     0,  1089,     0,
     971,     0,     0,     0,     0,     0,   618,   617,     0,     0,
       0,     0,     0,     0,     0,     0,  1108,   616,     0,     0,
       0,     0,     0,     0,   833,     0,     0,   607,     0,     0,
    1140,   608,   609,   610,   611,     0,     0,  2021,  1146,  1147,
       0,     0,  2024,  1153,   612,     0,     0,     0,     0,     0,
       0,   613,     0,   614,   421,  2034,     0,     0,     0,   618,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1108,     0,     0,   617,     0,     0,  2036,     0,  1180,
       0,   615,     0,  2038,     0,     0,     0,  2040,     0,     0,
       0,   989,     0,   833,     0,  2184,   607,     0,     0,     0,
     608,   609,   610,   611,     0,     0,     0,     0,  1202,   616,
    1205,     0,     0,   612,     0,     0,     0,     0,     0,     0,
     613,     0,   614,     0,     0,     0,   618,  2090,  2091,   748,
     748,     0,   607,     0,     0,  2098,   608,   609,   610,   611,
    1251,  1153,     0,     0,  1041,     0,   421,   607,     0,   612,
     615,   608,   609,   610,   611,     0,   613,     0,   614,     0,
       0,     0,     0,     0,   612,     0,   617,     0,     0,     0,
       0,   613,     0,   614,     0,     0,  2129,   973,   616,     0,
       0,     0,  1637,     0,     0,     0,   615,     0,     0,     0,
    1475,     0,     0,   607,     0,     0,     0,   608,   609,   610,
     611,   615,     0,     0,     0,     0,     0,  2148,     0,     0,
     612,     0,     0,     0,   616,   421,  2153,   613,   618,   614,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   616,
       0,  1348,  1348,  2163,  2164,   617,     0,     0,   607,     0,
       0,     0,   608,  1009,   610,   611,     0,   615,     0,     0,
       0,   421,     0,     0,     0,   612,     0,   748,   748,     0,
    1739,     0,   613,  2183,   614,     0,   421,     0,   834,     0,
       0,   617,     0,     0,     0,   616,     0,  2194,  2193,     0,
       0,     0,  2197,     0,  1251,  2198,   617,   618,     0,     0,
       0,     0,   615,     0,  2203,  2205,  2204,  2206,     0,  2207,
       0,  2208,     0,     0,     0,     0,     0,  1416,  1713,     0,
       0,   607,   421,     0,     0,   608,   609,   610,   611,     0,
     616,     0,     0,   618,     0,     0,     0,  1134,   612,     0,
       0,   973,   617,     0,     0,   613,     0,   614,   618,  1738,
       0,     0,   607,     0,     0,   748,   608,   609,   610,   611,
       0,  2218,     0,     0,     0,     0,     0,   421,     0,   612,
       0,     0,     0,     0,     0,   615,   613,     0,   614,     0,
       0,     0,     0,     0,     0,     0,     0,   617,   973,  1971,
       0,     0,   607,     0,   618,     0,   608,   609,   610,   611,
     973,     0,     0,   616,     0,     0,   615,  2239,     0,   612,
       0,     0,  2241,     0,     0,     0,   613,     0,   614,     0,
       0,     0,     0,  2250,  1946,     0,     0,     0,  2255,     0,
       0,     0,     0,     0,   616,     0,     0,     0,  2258,   618,
     421,     0,     0,  2270,     0,  1108,   615,   973,   973,   973,
     973,     0,   973,     0,     0,     0,     0,     0,     0,     0,
     617,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   421,     0,     0,   616,     0,   955,     0,  1715,     0,
     956,   607,     0,     0,     0,     0,     0,   957,   958,     0,
       0,   617,  1716,   959,   960,   961,   962,  1597,     0,   964,
     965,   966,   967,   968,   969,     0,   970,     0,   971,   972,
       0,   421,   618,     0,     0,   973,     0,   973,   973,   973,
     973,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   617,  2337,   955,     0,     0,     0,   956,   607,     0,
       0,     0,     0,   618,   957,   958,     0,   886,     0,     0,
     959,   960,   961,   962,   963,     0,   964,   965,   966,   967,
     968,   969,     0,   970,     0,   971,   972,   955,     0,     0,
       0,   956,     0,     0,  1600,     0,   973,     0,   957,   958,
       0,     0,     0,   618,     0,   960,     0, -1186,     0,     0,
   -1186, -1186, -1186, -1186, -1186,     0,     0,     0,   973,   971,
    2372,  2241,     0,     0,  2374,     0,  2378,     0,   973,     0,
    2381,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2390,  2391,  2393,     0,     0,     0,     0,   973,
       0,     0,     0,     0,  2403,     0,     0,     0,   748,     0,
    2405,     0,  1116,     0,     0,   973,  1117,   607,     0,   973,
     973,     0,  2337,  1118,  1119,     0,     0,     0,     0,  1120,
    1121,  1122,  1123,     0,     0,  1124,  1125,  1126,  1127,  1128,
    1129,  1130,  1131,     0,  1132,  1133,     0,     0,     0,     0,
       0,     0,     0,     0,  2437,  2439,     0,     0,     0,     0,
       0,   955,     0,     0,     0,   956,   834,     0,     0,  2451,
       0,  2452,   957,   958,  1089,     0,  1089,   973,   959,   960,
     961,   962,     0,     0,   964,   965,   966,   967,   968,   969,
       0,   970,     0,   971,   972,  1108,  1108,     0,     0,   886,
       0,     0,     0,  2439,     0,     0,  1711,  2475,     0,     0,
       0,  2479,   748,  1751,  1721,     0,     0,  1722,     0,     0,
     955,     0,     0,     0,   956,  1751,  2489,  2475,     0,   808,
       0,   957,   958,  1108,  1108,   973,   973,   959,   960,     0,
     962,     0,     0,   964,   965,   966,   967,   968,     0,     0,
     970,     0,   971,   972,     0,   748,     0,     0,     0,     0,
       0,     0,  1787,     0,     0,     0,     0,     0,     0,     0,
       0,   748,   748,   748,     0,   748,   748,     0,     0,   748,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1251,     0,     0,   748,     0,     0,  1108,
    1108,  1108,     0,  1153,  1153,  1251,     0,     0,  1153,  1153,
     955,     0,  1184,     0,   956,   607,     0,     0,     0,     0,
       0,   957,   958,     0,     0,     0,     0,   959,   960,   961,
     962,     0,     0,   964,   965,   966,   967,   968,   969,     0,
     970,     0,   971,   972,     0,     0,  1894,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   973,   973,
     973,   973,   973,   973,   973,   973,   973,   973,   748,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   973,     0,     0,     0,     0,     0,   375,
     973,     0,   973,     0,     0,   381,     0,     0,     0,     0,
       0,     0,   973,     0,     0,   388,     0,     0,   390,     0,
       0,   393,     0,     0,     0,     0,     0,     0,   399,     0,
       0,     0,   406,     0,     0,     0,   409,   748,   748,   748,
       0,     0,     0,   973,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   428,     0,     0,     0,   432,   433,
       0,     0,     0,     0,   438,   439,     0,     0,     0,     0,
     444,   445,     0,   447,   448,   449,   450,     0,   451,     0,
       0,     0,     0,     0,     0,     0,  1108,   460,     0,     0,
       0,     0,   464,     0,   466,     0,     0,     0,   469,     0,
       0,     0,   473,     0,   475,     0,     0,     0,     0,     0,
       0,   481,   973,     0,     0,   485,     0,     0,     0,   488,
       0,   490,     0,     0,     0,     0,   973,     0,   498,   500,
       0,   955,   502,   503,  1247,   956,   607,     0,   509,     0,
     510,     0,   957,   958,   514,     0,     0,   973,   959,   960,
     961,   962,     0,     0,   964,   965,   966,   967,   968,   969,
       0,   970,     0,   971,   972,     0,     0,     0,     0,     0,
       0,   541,   955,   543,     0,  1248,   956,   607,     0,     0,
     548,     0,     0,   957,   958,     0,     0,     0,     0,   959,
     960,   961,   962,   973,     0,   964,   965,   966,   967,   968,
     969,     0,   970,     0,   971,   972,     0,     0,     0,     0,
       0,     0,   955,     0,     0,  1249,   956,   607,  1348,  1348,
    1348,  1348,  1348,   957,   958,     0,     0,     0,     0,   959,
     960,   961,   962,   973,     0,   964,   965,   966,   967,   968,
     969,     0,   970,     0,   971,   972,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   955,   973,     0,  1251,   956,
     607,     0,     0,   973,  1416,     0,   957,   958,     0,   973,
       0,  1321,   959,   960,   961,   962,     0,     0,   964,   965,
     966,   967,   968,   969,     0,   970,     0,   971,   972,     0,
       0,     0,   973,     0,     0,     0,     0,  2166,     0,     0,
       0,     0,     0,     0,   973,     0,     0,     0,     0,     0,
       0,     0,   973,     0,     0,     0,     0,     0,   808,     0,
       0,     0,   973,     0,     0,   973,     0,     0,     0,  1108,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     973,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2200,   973,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   973,     0,     0,     0,     0,
       0,   973,     0,     0,   748,  2211,     0,   973,   955,     0,
       0,   720,   956,   607,     0,     0,     0,     0,     0,   957,
     958,     0,     0,     0,  1400,   959,   960,   961,   962,     0,
    1251,   964,   965,   966,   967,   968,   969,     0,   970,     0,
     971,   972,   955,     0,  1408,     0,   956,   607,     0,     0,
       0,     0,     0,   957,   958,     0,     0,     0,     0,   959,
     960,   961,   962,     0,  1894,   964,   965,   966,   967,   968,
     969,     0,   970,     0,   971,   972,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2245,     0,     0,   748,     0,  2248,
       0,   955,     0,  1423,     0,   956,   607,     0,     0,     0,
       0,     0,   957,   958,     0,   847,   973,     0,   959,   960,
     961,   962,     0,     0,   964,   965,   966,   967,   968,   969,
       0,   970,   973,   971,   972,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   955,     0,     0,     0,   956,
     607,     0,     0,     0,     0,     0,   957,   958,     0,     0,
       0,  1435,   959,   960,   961,   962,   748,   748,   964,   965,
     966,   967,   968,   969,     0,   970,   973,   971,   972,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   955,     0,
       0,     0,   956,   607,     0,     0,   973,     0,   973,   957,
     958,     0,   973,     0,  1438,   959,   960,   961,   962,     0,
       0,   964,   965,   966,   967,   968,   969,     0,   970,   955,
     971,   972,     0,   956,   607,   973,     0,     0,   973,  1108,
     957,   958,     0,  1108,     0,  1439,   959,   960,   961,   962,
       0,     0,   964,   965,   966,   967,   968,   969,  1134,   970,
     955,   971,   972,     0,   956,   607,     0,     0,     0,     0,
       0,   957,   958,     0,     0,     0,  1474,   959,   960,   961,
     962,     0,     0,   964,   965,   966,   967,   968,   969,     0,
     970,     0,   971,   972,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1108,   748,  1108,  1108,  1108,
     955,     0,     0,     0,   956,   607,     0,     0,     0,     0,
       0,   957,   958,   748,     0,     0,  1521,   959,   960,   961,
     962,     0,     0,   964,   965,   966,   967,   968,   969,     0,
     970,     0,   971,   972,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   973,   973,  1108,     0,
       0,     0,     0,     0,   973,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   955,     0,     0,     0,   956,   607,
    1108,  1108,     0,     0,  1108,   957,   958,     0,     0,     0,
    1522,   959,   960,   961,   962,   973,     0,   964,   965,   966,
     967,   968,   969,     0,   970,     0,   971,   972,     0,     0,
       0,     0,     0,     0,   973,     0,   955,     0,     0,   973,
     956,   607,     0,     0,     0,  1108,     0,   957,   958,   973,
     973,     0,  1647,   959,   960,   961,   962,     0,     0,   964,
     965,   966,   967,   968,   969,     0,   970,     0,   971,   972,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   973,
       0,     0,   955,     0,     0,     0,   956,   607,     0,   973,
     973,     0,     0,   957,   958,     0,     0,     0,  1914,   959,
     960,   961,   962,     0,   973,   964,   965,   966,   967,   968,
     969,     0,   970,     0,   971,   972,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   973,     0,   973,     0,     0,
       0,     0,     0,     0,     0,     0,   973,     0,     0,     0,
       0,   973,     0,     0,   973,     0,   955,     0,  1715,     0,
     956,   607,     0,     0,     0,     0,   973,   957,   958,     0,
       0,  1305,     0,   959,   960,   961,   962,     0,     0,   964,
     965,   966,   967,   968,   969,     0,   970,   955,   971,   972,
       0,   956,   607,     0,     0,     0,     0,     0,   957,   958,
       0,     0,     0,  1952,   959,   960,   961,   962,     0,     0,
     964,   965,   966,   967,   968,   969,     0,   970,     0,   971,
     972,     0,     0,   955,     0,  1970,     0,   956,   607,     0,
       0,     0,     0,   973,   957,   958,     0,     0,     0,     0,
     959,   960,   961,   962,     0,     0,   964,   965,   966,   967,
     968,   969,     0,   970,     0,   971,   972,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   973,     0,
     973,  1385,     0,     0,   973,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   973,   973,     0,   973,
       0,   955,     0,     0,     0,   956,   607,     0,     0,   973,
       0,   973,   957,   958,     0,     0,     0,  2000,   959,   960,
     961,   962,     0,     0,   964,   965,   966,   967,   968,   969,
       0,   970,     0,   971,   972,     0,   955,     0,     0,     0,
     956,   607,     0,   973,     0,   973,     0,   957,   958,     0,
       0,     0,  2085,   959,   960,   961,   962,   973,   973,   964,
     965,   966,   967,   968,   969,     0,   970,     0,   971,   972,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   973,     0,     0,     0,   973,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   973,     0,     0,     0,     0,
       0,     0,   377,   378,   379,   380,     0,   382,     0,   383,
       0,   385,   386,     0,   387,     0,     0,     0,   389,     0,
     391,   392,     0,     0,   394,   395,   396,     0,   398,     0,
     400,   401,     0,     0,   408,     0,     0,     0,     0,   411,
     412,   413,   414,   415,   416,   417,   418,     0,   419,   420,
       0,     0,   425,   426,   427,     0,   429,     0,   431,     0,
       0,   434,   435,     0,     0,     0,     0,     0,     0,   442,
     443,     0,     0,   446,     0,     0,     0,     0,     0,     0,
     452,     0,   454,     0,   455,   456,     0,     0,     0,   461,
     462,   463,     0,     0,   465,     0,     0,   467,   468,     0,
     470,   471,   472,     0,     0,     0,     0,   477,   478,     0,
       0,   480,     0,   482,   483,   484,     0,   486,   487,     0,
       0,   489,     0,   491,   492,   493,   494,   495,   496,     0,
       0,     0,     0,     0,     0,   504,   505,   506,     0,     0,
       0,     0,   511,   512,   513,  1587,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,     0,   542,     0,   544,     0,   545,     0,   546,
     547,     0,   549,   550,   551,   552,   553,   554,   555,   556,
     955,     0,  2150,     9,   956,   607,     0,     0,     0,     0,
      10,   957,   958,     0,     0,     0,     0,   959,   960,   961,
     962,     0,     0,   964,   965,   966,   967,   968,   969,     0,
     970,     0,   971,   972,     0,     0,     0,     0,     0,     0,
      11,    12,    13,    14,     0,    15,    16,    17,    18,    19,
      20,     0,   634,    21,    22,   647,     0,   650,    23,    24,
      25,     0,    26,    27,    28,    29,    30,    31,     0,    32,
      33,    34,    35,    36,    37,     0,    38,    39,    40,    41,
      42,    43,     0,     0,    44,    45,    46,    47,    48,     0,
       0,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     0,    71,     0,    72,    73,     0,    74,
      75,    76,     0,     0,    77,     0,     0,    78,    79,     0,
      80,    81,    82,    83,     0,    84,    85,    86,    87,    88,
      89,    90,    91,    92,     0,     0,     0,     0,     0,    93,
      94,    95,    96,     0,     0,     0,     0,    97,     0,     0,
      98,    99,     0,     0,   100,   101,     0,   102,     0,     0,
       0,   103,     0,   104,     0,   105,     0,     0,     0,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     0,
     116,   117,   118,     0,   119,     0,   120,   121,     0,   122,
       0,   123,   124,   125,   126,     0,     0,   127,   128,   129,
       0,   130,   131,   132,     0,   133,   134,   135,     0,   136,
       0,   137,   138,   139,   140,   141,     0,   142,     0,   143,
     144,     0,     0,   145,   146,   147,     0,     0,   148,   149,
       0,   150,   151,     0,   152,   153,     0,     0,     0,   154,
     155,     0,     0,   156,     0,     0,   157,     0,     0,     0,
     158,   159,     0,     0,   160,   161,   162,     0,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,     0,
     174,     0,     0,   175,     0,     0,     0,   176,   177,   178,
     179,   180,     0,   181,   182,     0,     0,   183,   184,   185,
     186,     0,     0,     0,     0,   187,   188,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,   193,     0,
     194,   195,   196,   197,   198,     0,     0,     0,   199,   200,
     201,   202,   203,   204,     0,   205,   206,   955,     0,  2165,
     207,   956,   607,     0,     0,     0,     0,     0,   957,   958,
       0,     0,     0,     0,   959,   960,   961,   962,     0,     0,
     964,   965,   966,   967,   968,   969,     0,   970,     0,   971,
     972,     0,     0,     0,     0,   955,     0,     0,     0,   956,
     607,     0,     0,     0,     0,     0,   957,   958,     0,     0,
       0,  2223,   959,   960,   961,   962,   945,   946,   964,   965,
     966,   967,   968,   969,     0,   970,   955,   971,   972,     0,
     956,   607,     0,     0,     0,     0,     0,   957,   958,     0,
       0,     0,  2238,   959,   960,   961,   962,     0,     0,   964,
     965,   966,   967,   968,   969,     0,   970,   955,   971,   972,
    2249,   956,   607,     0,     0,     0,     0,     0,   957,   958,
       0,     0,     0,     0,   959,   960,   961,   962,     0,     0,
     964,   965,   966,   967,   968,   969,     0,   970,   955,   971,
     972,     0,   956,   607,     0,     0,     0,     0,     0,   957,
     958,     0,     0,     0,  2253,   959,   960,   961,   962,     0,
       0,   964,   965,   966,   967,   968,   969,     0,   970,   955,
     971,   972,     0,   956,   607,     0,     0,     0,     0,     0,
     957,   958,     0,     0,     0,  2311,   959,   960,   961,   962,
       0,     0,   964,   965,   966,   967,   968,   969,     0,   970,
     955,   971,   972,     0,   956,   607,     0,     0,     0,     0,
       0,   957,   958,     0,     0,     0,  2312,   959,   960,   961,
     962,     0,     0,   964,   965,   966,   967,   968,   969,     0,
     970,   955,   971,   972,     0,   956,   607,     0,     0,     0,
       0,     0,   957,   958,     0,     0,     0,  2318,   959,   960,
     961,   962,     0,     0,   964,   965,   966,   967,   968,   969,
       0,   970,   955,   971,   972,  2327,   956,   607,     0,     0,
       0,     0,     0,   957,   958,     0,     0,     0,     0,   959,
     960,   961,   962,     0,     0,   964,   965,   966,   967,   968,
     969,     0,   970,   955,   971,   972,     0,   956,   607,     0,
       0,     0,     0,     0,   957,   958,     0,     0,     0,  2334,
     959,   960,   961,   962,     0,     0,   964,   965,   966,   967,
     968,   969,     0,   970,   955,   971,   972,  2351,   956,   607,
       0,     0,     0,     0,     0,   957,   958,     0,     0,     0,
       0,   959,   960,   961,   962,     0,     0,   964,   965,   966,
     967,   968,   969,     0,   970,   955,   971,   972,  2411,   956,
     607,     0,     0,     0,     0,     0,   957,   958,     0,     0,
       0,     0,   959,   960,   961,   962,     0,     0,   964,   965,
     966,   967,   968,   969,     0,   970,   955,   971,   972,     0,
     956,   607,     0,     0,     0,     0,     0,   957,   958,     0,
       0,     0,  2413,   959,   960,   961,   962,     0,     0,   964,
     965,   966,   967,   968,   969,     0,   970,   955,   971,   972,
       0,   956,   607,     0,     0,     0,     0,     0,   957,   958,
       0,     0,     0,  2425,   959,   960,   961,   962,     0,     0,
     964,   965,   966,   967,   968,   969,     0,   970,   955,   971,
     972,  2426,   956,   607,     0,     0,     0,     0,     0,   957,
     958,     0,     0,     0,     0,   959,   960,   961,   962,     0,
       0,   964,   965,   966,   967,   968,   969,     0,   970,   955,
     971,   972,  2428,   956,   607,     0,     0,     0,     0,     0,
     957,   958,     0,     0,     0,     0,   959,   960,   961,   962,
       0,     0,   964,   965,   966,   967,   968,   969,     0,   970,
     955,   971,   972,     0,   956,   607,     0,     0,     0,     0,
       0,   957,   958,     0,     0,     0,  2433,   959,   960,   961,
     962,     0,     0,   964,   965,   966,   967,   968,   969,     0,
     970,   955,   971,   972,     0,   956,   607,     0,     0,     0,
       0,     0,   957,   958,     0,     0,     0,  2435,   959,   960,
     961,   962,     0,     0,   964,   965,   966,   967,   968,   969,
       0,   970,   955,   971,   972,  2468,   956,   607,     0,     0,
       0,     0,     0,   957,   958,     0,     0,     0,     0,   959,
     960,   961,   962,     0,     0,   964,   965,   966,   967,   968,
     969,     0,   970,     0,   971,   972,   955,     0,  2483,     0,
     956,   607,     0,     0,     0,     0,     0,   957,   958,     0,
       0,     0,     0,   959,   960,   961,   962,     0,     0,   964,
     965,   966,   967,   968,   969,     0,   970,   955,   971,   972,
       0,   956,   607,     0,     0,     0,     0,     0,   957,   958,
       0,     0,     0,     0,   959,   960,   961,   962,     0,     0,
     964,   965,   966,   967,   968,   969,     0,   970,     0,   971,
     972
};

static const yytype_int16 yycheck[] =
{
      50,   378,   483,   387,   493,   494,   495,   496,   763,   392,
      62,    63,   630,   541,   486,   375,  1031,    69,   256,   401,
    1142,  1035,   750,   261,   887,   645,  1462,   655,   656,   411,
     929,   413,   634,   985,   978,   979,   418,   419,   420,  1313,
    1500,   979,   656,   472,   426,  1596,    98,   429,  1342,   431,
     430,  1566,   209,  1568,   609,  1520,   467,  1158,   888,  1496,
    1313,  2005,  1626,  1563,  1009,    76,   258,  1613,   118,   261,
     262,   743,   122,   433,  1602,  1602,   845,   442,    63,  1075,
     480,    15,  1622,  1532,     7,     0,     1,  1627,    99,   845,
     450,   468,    94,  1375,  1532,     5,    41,     8,  1532,   388,
     655,   656,  1532,  1532,   464,   116,  1895,  1567,  1532,   469,
     175,   116,  1532,   473,   877,   475,    71,  1668,   182,  1967,
       5,  1530,     7,  1532,     5,  1534,   673,   477,   488,    15,
      16,    17,    15,   144,    16,    17,   182,    15,    37,  2189,
     500,     7,   502,     3,   231,   232,     5,   191,    58,   509,
     237,     7,   406,   205,   116,    47,     8,     8,   129,   129,
      15,    21,    21,   513,    15,  2215,    15,     8,  1031,  1183,
      63,     8,   224,    15,  1170,    68,    86,   169,   149,    20,
     800,  1530,  1530,  1532,  1532,  1534,  1534,    15,  1536,    15,
    1530,  1054,  1532,   116,  1534,    15,  1536,    90,    91,    23,
      15,   191,   172,    21,  1704,  1705,  1706,    21,   637,     3,
      92,     8,   641,    37,   191,     8,   126,     8,   208,   648,
     129,   266,     5,     8,     7,   696,   480,   137,   230,    20,
     129,   208,    26,    64,   472,   150,   878,   129,   282,   129,
      37,   712,   287,   129,   129,   169,   129,   315,   129,   633,
     116,   144,   257,   208,   318,   165,     8,   322,  1900,  1901,
     116,   154,   809,   149,   209,  1559,   149,   149,    20,   315,
     129,   149,   318,   915,   129,   116,   166,   129,   129,   116,
     129,   349,   284,   228,   208,   177,    64,   129,     8,     8,
     282,   763,   282,   295,    23,   285,  1195,   647,   129,   588,
     650,   129,    21,   129,     8,   129,   690,   200,    37,   129,
     692,   129,   246,     8,   129,   129,    20,    37,   149,   201,
    2109,   373,   374,   116,   724,   116,  1448,   379,   380,   381,
     382,   116,   384,   385,   257,  1899,   388,     3,   390,   391,
     392,   393,   257,   254,   396,     8,   818,   399,   258,   401,
    1603,  1604,  1898,   129,   406,  1307,  1896,   409,   282,   411,
      26,   413,  1306,  1645,   116,   417,   418,   419,   420,  1818,
     799,   751,   843,   993,   426,   995,   428,   429,   980,   431,
    1818,  1009,  1002,   854,  1818,   437,   438,   388,  1818,  1818,
       8,   257,   444,   445,  1818,  1347,  1805,   449,  1818,   637,
     871,   257,     8,   641,   456,     8,     8,   459,  2256,  1818,
     648,   811,   116,   256,    20,  1824,   257,    20,   261,   471,
     257,   116,   474,   788,  1193,  1097,  1440,  1182,   480,   481,
     482,   483,   417,   485,   486,  1380,  1381,  1382,  1194,   489,
     492,   493,   494,   495,   496,   916,   498,  1461,   798,   501,
     800,   503,   504,   116,  1009,   507,  1805,  1805,   510,   930,
     840,    15,   514,     5,   257,  1805,   257,    92,  1420,  1818,
    1818,  1089,   257,     8,     8,  1824,  1824,     8,  1818,  2423,
    1828,  2123,  2124,  1441,  1824,  1443,  1114,     8,  1828,     8,
     191,   543,  1593,  1594,   544,    37,   147,   148,   548,    15,
    1114,  1497,     3,    15,   148,   257,    37,   557,   558,   559,
     116,   211,   562,   116,   116,   926,   568,    18,     3,   571,
     572,   573,   574,    15,   149,     8,   576,   579,   580,   180,
      15,   583,   584,   585,   586,   587,   180,     8,    21,   591,
     592,   241,  1162,   927,    15,  1560,  2006,  1018,  1842,  2014,
       8,  2051,  1023,   257,   565,   566,  2120,  1572,  1995,  1114,
      15,   799,   257,    15,  2412,  2111,   577,   996,   997,   998,
     999,  1000,   128,   574,  2102,  2102,   201,   769,     5,    43,
       8,   116,   116,   584,   585,   586,   587,   288,    15,     5,
     974,   434,   679,  1064,   257,   116,    15,   116,   299,    15,
       8,   157,   759,    67,     8,   657,   658,   659,   660,   661,
     662,   663,  2460,    21,   666,   665,  1890,     8,    82,     8,
     463,  1895,   674,    87,    88,     8,     8,   470,   128,   472,
      94,    16,    17,   683,   257,     5,    21,  1890,     5,     9,
     692,    15,     9,   695,  2144,   697,    16,    17,     3,    16,
      17,   257,     5,    23,   257,   257,     8,   157,   116,     8,
      15,   116,  1046,    16,    17,  2229,     8,    37,   720,    22,
      37,    24,  1056,   674,   129,     7,     8,  2506,  2507,    21,
      33,     5,    35,   244,    37,     9,     8,     5,   116,  1641,
    2519,     9,  1320,   745,     8,   747,   697,  1560,   750,    21,
       8,     7,     8,  1648,  1649,  1650,  1320,  1462,  1463,  1572,
     760,   763,   116,    37,  2214,    23,     8,   217,  1446,    37,
       8,   773,   257,   257,   774,   116,     8,   116,  1680,    37,
     782,   781,   784,   116,   116,     8,   257,   789,   257,   791,
    1570,  1571,   794,     8,     8,  1575,  1576,  1367,  1368,  1369,
    1370,  1371,  1380,  1381,  1382,   807,    21,    21,   996,   997,
     998,   999,  1000,     7,   228,  1320,   818,  1322,   329,   856,
    2321,    15,   824,   860,     8,  1538,  1539,  1540,   865,  1542,
    1543,   868,   869,   344,   345,   346,   191,   839,     8,    95,
     842,     8,     8,   794,   637,   259,   848,   847,   641,   257,
       3,    21,   257,   208,    21,   648,   159,   316,   317,   162,
     653,  1566,    15,  1568,    18,     8,  1287,     8,   124,     8,
    2280,     8,    26,     8,     8,  1380,  1381,  1382,    21,   257,
     880,  2346,    21,     8,  1305,  2109,    21,    21,   839,   303,
       5,   842,     8,  2343,     9,     3,    21,     3,   935,     8,
     937,    16,    17,   257,   906,   907,    21,    15,    23,    15,
    2360,    15,    16,    17,     7,    22,   257,    24,   257,     3,
     922,    15,    37,    27,   257,   257,    33,   282,    35,    15,
     285,    15,    36,    84,  2344,   290,  2470,     8,     8,   195,
       8,    41,   944,   298,   247,   945,   202,   908,  2482,  1279,
      21,    21,     8,    21,    84,    59,  2342,     5,     8,     8,
      64,     9,   923,    22,     8,    24,     8,     8,    16,    17,
    1935,    71,    21,    21,    33,    23,    35,    21,     8,    21,
      21,   337,     3,  2227,   340,   341,   342,     8,    92,    37,
       8,  1885,  1886,  1887,  1888,  1889,     8,  1885,  1886,  1887,
    1888,  1889,   305,   306,   307,     8,   799,     3,     8,    21,
       8,  2421,     8,  1434,     8,     8,   191,  1919,    21,   194,
    1354,    21,   129,    21,  1873,  1027,  1360,    21,  1028,  1356,
       8,  1033,  2418,  1935,     8,   135,  1429,  1039,  1431,  1941,
     191,  1943,     8,    21,     7,   149,     8,    21,  1753,  1727,
    1052,   158,   159,     8,   161,   162,     8,   208,     8,    21,
     256,   191,    15,     8,     8,   261,    21,  2139,     8,   169,
    1648,  1649,  1650,  1400,     8,  1077,    21,    21,   208,    15,
    1082,    21,   149,   876,   877,   192,  1413,    21,  1640,     7,
       8,   191,  1426,     8,   887,    15,  1098,   201,    15,   158,
     159,    15,   161,   162,   251,  1105,    21,  1439,   208,   209,
     149,  1113,  2077,     7,   265,     7,     8,     8,    15,     8,
      15,   221,  1935,   223,   224,    89,   226,   234,  1941,   229,
      21,   282,    21,   192,   285,   265,    15,    63,   289,   290,
     247,     8,    68,  1648,  1649,  1650,    15,   298,   299,  1149,
       8,     7,   282,   304,    21,   285,   147,   148,   122,   289,
      16,    17,  1472,    21,    90,    91,     8,  1204,    15,   299,
      15,     8,    15,  1210,   304,   234,    15,  1214,     8,  1216,
    1217,  1218,   282,  1220,    21,  1222,     8,     8,   247,   180,
      15,   155,  1192,   858,   859,     8,   861,     8,   124,    21,
      21,     8,     8,   996,   997,   998,   999,  1000,    21,  1519,
      21,  1004,  1005,    15,    21,    21,     8,     8,   144,    37,
     320,   185,     5,   124,  1558,    15,     9,    10,   154,    21,
      21,    14,    15,    16,    17,  1235,  1657,     8,  1031,     8,
      16,    17,     8,    15,    27,    15,     8,  1247,  1248,  1249,
      21,    34,    21,    36,   218,    21,  2328,   407,  1258,    21,
       8,  1054,    15,  1263,  2077,  1644,  2125,  2126,  2127,  1269,
       8,   347,   348,    21,   200,     5,  1276,     7,  1280,  1281,
      10,    64,     8,    21,    14,    15,    16,    17,   252,  1767,
      15,  1769,  1770,   247,   248,    21,    15,    27,  1719,  1092,
      15,  1635,  1304,  1781,    34,   452,    36,   233,  1310,    92,
    2274,    15,  1314,  1791,    15,  1793,     8,     8,   244,     8,
       8,    15,  2224,   314,   315,  1659,     8,   318,   319,    21,
      21,     5,    21,    21,    64,     9,    15,  1671,     8,    21,
     487,  1675,    16,    17,     8,   124,   129,  2249,     8,  1917,
     497,    21,     8,    15,  1924,  1603,  1604,    21,  1690,  1310,
      15,    21,    92,    37,    15,    21,   149,    15,    63,   519,
       7,   521,     3,    68,   239,     8,    15,  1414,   528,   529,
     530,     8,   246,  1385,   534,   535,   536,   537,    21,   539,
     540,  1648,  1649,  1650,    21,    90,    91,  1004,  1005,   129,
       8,     8,   246,   550,   551,   552,   553,   554,    21,    15,
      16,    17,     8,    21,    21,     8,  2502,  2503,   201,   149,
       8,    27,     8,     8,    15,    21,  1428,  1429,    21,  1431,
      36,    26,     8,    21,     8,    21,    21,  1439,     8,  1441,
       8,  1443,     8,     8,  1446,    21,     7,    21,    15,   144,
       8,    21,  1489,    21,     8,    21,  1644,     5,    64,   154,
     240,     9,   609,   610,   611,     8,   613,    21,    16,    17,
      15,   201,   175,   620,    22,    23,  1478,    25,    21,    15,
      28,    29,    30,    31,    32,  1487,    92,   634,     5,    37,
       8,  1493,  2456,    10,     8,  1495,     8,    14,    15,    16,
      17,  1503,     8,    21,    15,   200,     8,    21,     8,    21,
      27,     8,  2398,  2399,  1514,    21,  1516,    34,  1520,    36,
      15,    21,    15,   129,    21,   149,   866,   867,     5,   676,
       8,    15,     8,    10,     8,    15,   231,    14,    15,    16,
      17,  1541,     8,   149,   691,     8,    15,    64,     7,   244,
      27,    26,  1552,    62,    15,    15,     8,    34,     5,    36,
       8,    15,     9,    21,  1564,   287,     8,   314,    15,    16,
      17,  2276,   719,     8,  1574,    92,     8,   213,  1578,   726,
      27,  1583,  1375,     8,    15,   732,   733,    64,  1588,    36,
    1590,     5,     9,     7,     5,   201,    10,    64,     9,   129,
      14,    15,    16,    17,    15,    16,    17,     9,    21,  1936,
       8,  1613,   129,    27,     8,    92,    27,    64,     8,    15,
      34,    67,    36,    15,  1626,    36,    15,    37,    15,  1939,
      15,   778,   149,    15,    15,    15,     8,  2342,     8,   129,
    2345,  2346,    26,  1645,  2212,    92,  1648,  1649,  1650,   166,
      64,     7,   129,    64,    15,     7,  1658,    21,    21,     5,
      18,    21,   812,     9,    37,     7,    15,    26,     7,    26,
      16,    17,   149,  2006,     8,    21,     8,    23,    92,    15,
      15,    92,   129,     8,   201,    15,  1479,    62,  1690,   166,
    2395,    37,    21,    21,    15,    15,    15,    15,    15,     8,
       5,     8,   149,    15,   851,   852,    21,    21,  1710,    15,
       5,    15,  2417,  2418,    15,   129,    15,    15,   129,   166,
      15,    16,    17,    15,   201,  1727,    15,    15,    15,  1522,
      15,    44,    27,    15,    15,   149,    15,    15,   149,    15,
       7,    36,     8,     8,    21,  1538,  1539,  1540,     8,  1542,
    1543,     8,    15,  1546,   201,     7,    15,  2462,  2189,  1761,
    1762,   255,   166,    21,    15,    15,  2100,  1560,   239,    64,
    1563,    16,    15,    15,    87,   208,  2110,    21,     8,  1572,
      93,     7,    15,   329,  1786,     7,   315,   201,   330,   246,
     201,    15,     5,   246,     8,   246,   246,    92,    15,    15,
      21,   246,    21,     8,     7,    15,   119,     8,   955,   956,
     957,   958,   959,   960,   961,   962,   963,   964,   965,   966,
     967,   968,   969,   970,   971,   972,   973,  2266,  2267,    21,
     143,    21,   145,   980,   129,    21,    21,    26,   985,     8,
     173,    15,    15,   255,     8,   992,     5,   994,    15,     7,
      21,  1644,  1645,    15,   149,   208,    15,    16,    17,    71,
       8,    15,  1009,    18,    15,   178,    15,    20,    27,    15,
     183,    15,     5,     8,   187,    15,    21,    36,   191,    21,
      21,   194,    21,    21,    15,    21,     8,    21,  1035,    21,
      15,    15,     7,     9,  1041,    21,  1898,  1899,  1900,  1901,
      21,    44,     8,   216,    21,    64,   201,    26,    21,  1911,
    1057,  1704,  1705,  1706,    21,  1065,    15,   230,    21,  2246,
    2342,    15,  2344,   236,    26,    26,  1076,    15,    21,    15,
       7,    21,    15,    92,    26,     8,  1938,    15,   254,    21,
      21,    15,     8,     7,    87,   132,    21,    45,    46,     7,
      48,    49,    21,    37,  1954,    53,    21,     7,     7,    21,
      21,   255,    15,    61,    15,    21,    21,    15,    66,    15,
     129,    69,    15,    15,    15,  1975,   119,    15,    15,    77,
      15,    79,     7,    81,     8,     8,     7,     7,  1990,     8,
     149,    21,  1994,    15,  1996,  1142,     7,     7,    15,    78,
     143,   328,   145,    21,  2006,     8,   104,     7,     7,    21,
      15,  2013,  2014,  1160,    15,    17,     8,   115,    15,  1169,
    2020,    17,     7,    21,     7,    15,     7,   222,   128,  2029,
     907,  1281,  1992,  1870,  1588,   178,  1183,  1184,  1185,  1196,
     183,   139,   201,  1101,   187,  1592,  2224,  2047,   191,   582,
    1871,   194,   590,  1203,   152,  1312,   593,   710,   944,  1209,
    1622,  2229,  2122,  1213,   944,  1215,  1890,  2102,  1898,  1219,
    2070,  1221,   170,   216,  1503,  1165,  1728,  2171,   176,  1990,
    1487,  2081,  2190,  1402,  1057,  1423,   184,   230,   186,  1037,
     188,  1099,   190,   236,  1703,  1701,    75,  1919,  2508,   197,
    1941,   463,   711,  1250,  1446,  1409,   792,  1046,  1641,  2111,
    1644,    45,    46,  1009,    48,    49,   214,   215,  2120,    53,
    2122,  2123,  2124,  2125,  2126,  2127,   246,    61,   246,   657,
    1113,  1082,    66,   838,   232,    69,   246,   246,  1185,   659,
     661,   239,  1935,    77,   660,    79,  2275,    81,  1941,   662,
    1425,  1427,  2152,  2151,  2460,   253,  1994,  2328,   256,  1027,
    1307,   807,  1025,  2436,     5,  1098,  1938,  1052,  1039,    10,
     104,  2379,  1319,    14,    15,    16,    17,  1977,  2341,  2462,
       5,   115,  2484,  2504,  2506,    10,    27,  2189,  2190,    14,
      15,    16,    17,    34,  2283,    36,  1753,  1463,   666,    40,
    1347,  1501,    27,  1997,   504,   139,   761,   382,   415,    34,
    2256,    36,  1359,  1943,  1805,  1552,  2001,  1780,   152,  1824,
    1828,  1785,  1818,    64,  2027,  2306,  1235,  2229,  2026,   878,
    2047,  1258,  1263,  1269,  2081,    -1,   170,    -1,  1276,    64,
      -1,    -1,   176,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,    92,   186,    -1,   188,    -1,   190,    -1,  2051,    -1,
      -1,  1408,  1409,   197,  2266,  2267,    -1,    92,    -1,    -1,
      -1,    -1,    -1,  2275,    -1,    -1,  1423,   434,    -1,    -1,
     214,   215,    -1,  1430,  2077,    -1,  1436,    -1,   129,    -1,
      -1,    -1,    -1,  1440,    -1,    -1,    -1,    -1,   232,  1446,
      -1,  1448,    -1,    -1,   129,    -1,   463,    -1,   149,    -1,
      -1,    -1,    -1,   470,  1461,    -1,    -1,    -1,    -1,   253,
      -1,   478,   256,    -1,   149,    -1,    -1,    -1,  1475,    -1,
    2332,    -1,    -1,    -1,    -1,  1485,    -1,    -1,    -1,  1486,
    2342,    -1,  2344,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2144,  1499,    -1,    -1,    -1,  2356,  1504,    -1,  1506,
     201,    -1,    -1,    -1,    -1,  2365,  2368,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1525,   201,    -1,  1528,    -1,
      -1,  1531,    -1,  1533,     5,  1535,    -1,  1537,    -1,    10,
      -1,    -1,    -1,    14,    15,    16,    17,    -1,  2398,  2399,
       5,    -1,    -1,    -1,    -1,    10,    27,    -1,    -1,    14,
      15,    16,    17,    34,    -1,    36,    -1,    -1,    -1,    -1,
    2213,  2214,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
    1577,    36,   589,    -1,  2436,    -1,  2438,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1598,    -1,     5,    -1,    -1,    -1,    -1,    10,    64,
      -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    36,    -1,  2486,    92,    -1,    -1,
      -1,  2491,  1639,  1640,  1641,    -1,   653,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2504,    -1,  2506,  2507,   129,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,  2519,
      -1,    -1,     7,  1670,   129,    10,  1673,    -1,   149,    14,
      15,    16,    17,    -1,  1681,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    27,    -1,   149,    -1,    -1,    -1,    -1,    34,
    2343,    36,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,     9,    -1,    -1,    -1,  1713,  2360,  1715,    16,
      17,    -1,    -1,    -1,  2367,    -1,    23,   129,    25,    64,
     201,    28,    29,    30,    31,    32,    -1,    -1,   745,    -1,
      37,    -1,    -1,    -1,    -1,    -1,   201,   149,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   763,    92,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    10,    -1,    -1,
     777,    14,    15,    16,    17,    -1,    -1,  1777,   785,   786,
      -1,    -1,  1782,   790,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    36,   129,  1795,    -1,    -1,    -1,   201,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   818,    -1,    -1,   149,    -1,    -1,  1817,    -1,   826,
      -1,    64,    -1,  1823,    -1,    -1,    -1,  1827,    -1,    -1,
      -1,   166,    -1,     7,    -1,    78,    10,    -1,    -1,    -1,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,   855,    92,
     857,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    36,    -1,    -1,    -1,   201,  1864,  1865,   876,
     877,    -1,    10,    -1,    -1,  1872,    14,    15,    16,    17,
     887,   888,    -1,    -1,     7,    -1,   129,    10,    -1,    27,
      64,    14,    15,    16,    17,    -1,    34,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    27,    -1,   149,    -1,    -1,    -1,
      -1,    34,    -1,    36,    -1,    -1,  1913,   621,    92,    -1,
      -1,    -1,  1919,    -1,    -1,    -1,    64,    -1,    -1,    -1,
       7,    -1,    -1,    10,    -1,    -1,    -1,    14,    15,    16,
      17,    64,    -1,    -1,    -1,    -1,    -1,  1944,    -1,    -1,
      27,    -1,    -1,    -1,    92,   129,  1953,    34,   201,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      -1,   978,   979,  1970,  1971,   149,    -1,    -1,    10,    -1,
      -1,    -1,    14,    15,    16,    17,    -1,    64,    -1,    -1,
      -1,   129,    -1,    -1,    -1,    27,    -1,  1004,  1005,    -1,
    1997,    -1,    34,  2003,    36,    -1,   129,    -1,  2005,    -1,
      -1,   149,    -1,    -1,    -1,    92,    -1,  2017,  2015,    -1,
      -1,    -1,  2022,    -1,  1031,  2025,   149,   201,    -1,    -1,
      -1,    -1,    64,    -1,  2031,  2035,  2033,  2037,    -1,  2039,
      -1,  2041,    -1,    -1,    -1,    -1,    -1,  1054,     7,    -1,
      -1,    10,   129,    -1,    -1,    14,    15,    16,    17,    -1,
      92,    -1,    -1,   201,    -1,    -1,    -1,   771,    27,    -1,
      -1,   775,   149,    -1,    -1,    34,    -1,    36,   201,     7,
      -1,    -1,    10,    -1,    -1,  1092,    14,    15,    16,    17,
      -1,  2088,    -1,    -1,    -1,    -1,    -1,   129,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    64,    34,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   822,     7,
      -1,    -1,    10,    -1,   201,    -1,    14,    15,    16,    17,
     834,    -1,    -1,    92,    -1,    -1,    64,  2134,    -1,    27,
      -1,    -1,  2139,    -1,    -1,    -1,    34,    -1,    36,    -1,
      -1,    -1,    -1,  2150,  2151,    -1,    -1,    -1,  2155,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,  2165,   201,
     129,    -1,    -1,  2170,    -1,  1182,    64,   881,   882,   883,
     884,    -1,   886,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   129,    -1,    -1,    92,    -1,     5,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,   149,    21,    22,    23,    24,    25,  2224,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,   129,   201,    -1,    -1,   949,    -1,   951,   952,   953,
     954,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,  2259,     5,    -1,    -1,    -1,     9,    10,    -1,
      -1,    -1,    -1,   201,    16,    17,    -1,  2274,    -1,    -1,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,     5,    -1,    -1,
      -1,     9,    -1,    -1,  1311,    -1,  1010,    -1,    16,    17,
      -1,    -1,    -1,   201,    -1,    23,    -1,    25,    -1,    -1,
      28,    29,    30,    31,    32,    -1,    -1,    -1,  1032,    37,
    2327,  2328,    -1,    -1,  2331,    -1,  2333,    -1,  1042,    -1,
    2340,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2349,  2350,  2351,    -1,    -1,    -1,    -1,  1063,
      -1,    -1,    -1,    -1,  2361,    -1,    -1,    -1,  1375,    -1,
    2367,    -1,     5,    -1,    -1,  1079,     9,    10,    -1,  1083,
    1084,    -1,  2379,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2411,  2412,    -1,    -1,    -1,    -1,
      -1,     5,    -1,    -1,    -1,     9,  2423,    -1,    -1,  2426,
      -1,  2428,    16,    17,  1441,    -1,  1443,  1141,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,  1462,  1463,    -1,    -1,  2456,
      -1,    -1,    -1,  2460,    -1,    -1,  1473,  2464,    -1,    -1,
      -1,  2468,  1479,  2470,  1481,    -1,    -1,  1484,    -1,    -1,
       5,    -1,    -1,    -1,     9,  2482,  2483,  2484,    -1,  1496,
      -1,    16,    17,  1500,  1501,  1199,  1200,    22,    23,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    32,    -1,    -1,
      35,    -1,    37,    38,    -1,  1522,    -1,    -1,    -1,    -1,
      -1,    -1,  1529,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1538,  1539,  1540,    -1,  1542,  1543,    -1,    -1,  1546,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1560,    -1,    -1,  1563,    -1,    -1,  1566,
    1567,  1568,    -1,  1570,  1571,  1572,    -1,    -1,  1575,  1576,
       5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,  1613,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1323,
    1324,  1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,
    1334,  1335,  1336,  1337,  1338,  1339,  1340,  1341,  1645,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1357,    -1,    -1,    -1,    -1,    -1,    12,
    1364,    -1,  1366,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    -1,  1376,    -1,    -1,    28,    -1,    -1,    31,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    49,  1704,  1705,  1706,
      -1,    -1,    -1,  1407,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    77,    78,    -1,    -1,    -1,    -1,
      83,    84,    -1,    86,    87,    88,    89,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1753,   100,    -1,    -1,
      -1,    -1,   105,    -1,   107,    -1,    -1,    -1,   111,    -1,
      -1,    -1,   115,    -1,   117,    -1,    -1,    -1,    -1,    -1,
      -1,   124,  1476,    -1,    -1,   128,    -1,    -1,    -1,   132,
      -1,   134,    -1,    -1,    -1,    -1,  1490,    -1,   141,   142,
      -1,     5,   145,   146,     8,     9,    10,    -1,   151,    -1,
     153,    -1,    16,    17,   157,    -1,    -1,  1511,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,   184,     5,   186,    -1,     8,     9,    10,    -1,    -1,
     193,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,  1557,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,     5,    -1,    -1,     8,     9,    10,  1885,  1886,
    1887,  1888,  1889,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,  1597,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,  1630,    -1,  1935,     9,
      10,    -1,    -1,  1637,  1941,    -1,    16,    17,    -1,  1643,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,  1666,    -1,    -1,    -1,    -1,  1974,    -1,    -1,
      -1,    -1,    -1,    -1,  1678,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1686,    -1,    -1,    -1,    -1,    -1,  1995,    -1,
      -1,    -1,  1696,    -1,    -1,  1699,    -1,    -1,    -1,  2006,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1714,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2027,  1725,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1739,    -1,    -1,    -1,    -1,
      -1,  1745,    -1,    -1,  2051,  2052,    -1,  1751,     5,    -1,
      -1,   404,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
    2077,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      37,    38,     5,    -1,     7,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    -1,  2111,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2141,    -1,    -1,  2144,    -1,  2146,
      -1,     5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,   508,  1860,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,  1876,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,  2213,  2214,    28,    29,
      30,    31,    32,    33,    -1,    35,  1920,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,     9,    10,    -1,    -1,  1940,    -1,  1942,    16,
      17,    -1,  1946,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,    -1,     9,    10,  1969,    -1,    -1,  1972,  2276,
      16,    17,    -1,  2280,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,  1992,    35,
       5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2342,  2343,  2344,  2345,  2346,
       5,    -1,    -1,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,  2360,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2090,  2091,  2395,    -1,
      -1,    -1,    -1,    -1,  2098,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,    10,
    2417,  2418,    -1,    -1,  2421,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,  2129,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,  2148,    -1,     5,    -1,    -1,  2153,
       9,    10,    -1,    -1,    -1,  2462,    -1,    16,    17,  2163,
    2164,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2193,
      -1,    -1,     5,    -1,    -1,    -1,     9,    10,    -1,  2203,
    2204,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,  2218,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2239,    -1,  2241,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2250,    -1,    -1,    -1,
      -1,  2255,    -1,    -1,  2258,    -1,     5,    -1,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,  2270,    16,    17,    -1,
      -1,   924,    -1,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,     5,    37,    38,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,  2337,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2372,    -1,
    2374,  1024,    -1,    -1,  2378,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2390,  2391,    -1,  2393,
      -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,  2403,
      -1,  2405,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,     5,    -1,    -1,    -1,
       9,    10,    -1,  2437,    -1,  2439,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,  2451,  2452,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2475,    -1,    -1,    -1,  2479,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2489,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    -1,    19,    -1,    21,
      -1,    23,    24,    -1,    26,    -1,    -1,    -1,    30,    -1,
      32,    33,    -1,    -1,    36,    37,    38,    -1,    40,    -1,
      42,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      -1,    -1,    64,    65,    66,    -1,    68,    -1,    70,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    94,    -1,    96,    97,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,   106,    -1,    -1,   109,   110,    -1,
     112,   113,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,   123,    -1,   125,   126,   127,    -1,   129,   130,    -1,
      -1,   133,    -1,   135,   136,   137,   138,   139,   140,    -1,
      -1,    -1,    -1,    -1,    -1,   147,   148,   149,    -1,    -1,
      -1,    -1,   154,   155,   156,  1288,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,    -1,   185,    -1,   187,    -1,   189,    -1,   191,
     192,    -1,   194,   195,   196,   197,   198,   199,   200,   201,
       5,    -1,     7,     6,     9,    10,    -1,    -1,    -1,    -1,
      13,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,    45,    46,    -1,    48,    49,    50,    51,    52,
      53,    -1,   254,    56,    57,   257,    -1,   259,    61,    62,
      63,    -1,    65,    66,    67,    68,    69,    70,    -1,    72,
      73,    74,    75,    76,    77,    -1,    79,    80,    81,    82,
      83,    84,    -1,    -1,    87,    88,    89,    90,    91,    -1,
      -1,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    -1,   117,    -1,   119,   120,    -1,   122,
     123,   124,    -1,    -1,   127,    -1,    -1,   130,   131,    -1,
     133,   134,   135,   136,    -1,   138,   139,   140,   141,   142,
     143,   144,   145,   146,    -1,    -1,    -1,    -1,    -1,   152,
     153,   154,   155,    -1,    -1,    -1,    -1,   160,    -1,    -1,
     163,   164,    -1,    -1,   167,   168,    -1,   170,    -1,    -1,
      -1,   174,    -1,   176,    -1,   178,    -1,    -1,    -1,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,    -1,
     193,   194,   195,    -1,   197,    -1,   199,   200,    -1,   202,
      -1,   204,   205,   206,   207,    -1,    -1,   210,   211,   212,
      -1,   214,   215,   216,    -1,   218,   219,   220,    -1,   222,
      -1,   224,   225,   226,   227,   228,    -1,   230,    -1,   232,
     233,    -1,    -1,   236,   237,   238,    -1,    -1,   241,   242,
      -1,   244,   245,    -1,   247,   248,    -1,    -1,    -1,   252,
     253,    -1,    -1,   256,    -1,    -1,   259,    -1,    -1,    -1,
     263,   264,    -1,    -1,   267,   268,   269,    -1,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,    -1,
     283,    -1,    -1,   286,    -1,    -1,    -1,   290,   291,   292,
     293,   294,    -1,   296,   297,    -1,    -1,   300,   301,   302,
     303,    -1,    -1,    -1,    -1,   308,   309,   310,   311,   312,
     313,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   321,    -1,
     323,   324,   325,   326,   327,    -1,    -1,    -1,   331,   332,
     333,   334,   335,   336,    -1,   338,   339,     5,    -1,     7,
     343,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,   598,   599,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,     5,    37,    38,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
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
       0,   353,     0,     1,   150,   257,   354,   355,   116,     6,
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
     311,   312,   313,   321,   323,   324,   325,   326,   327,   331,
     332,   333,   334,   335,   336,   338,   339,   343,   356,   358,
     361,   373,   374,   378,   379,   380,   386,   387,   388,   389,
     391,   392,   394,   396,   397,   398,   399,   406,   407,   408,
     409,   410,   411,   415,   416,   417,   421,   422,   460,   462,
     475,   518,   519,   521,   522,   528,   529,   530,   531,   538,
     539,   540,   541,   543,   546,   550,   551,   552,   553,   554,
     555,   561,   562,   563,   574,   575,   576,   578,   581,   584,
     589,   590,   592,   594,   596,   599,   600,   624,   625,   636,
     637,   638,   639,   644,   647,   650,   653,   654,   701,   702,
     703,   704,   705,   706,   707,   708,   714,   716,   718,   720,
     722,   723,   724,   725,   726,   729,   731,   732,   733,   736,
     737,   741,   742,   744,   745,   746,   747,   748,   749,   750,
     753,   758,   763,   765,   766,   767,   768,   770,   771,   772,
     773,   774,   775,   792,   795,   796,   797,   798,   804,   807,
     812,   813,   814,   817,   818,   819,   820,   821,   822,   823,
     824,   825,   826,   827,   828,   829,   830,   831,   836,   837,
     838,   839,   840,   850,   851,   852,   854,   855,   856,   857,
     858,   859,   873,    15,   485,   485,   547,   547,   547,   547,
     547,   485,   547,   547,   357,   547,   547,   547,   485,   547,
     485,   547,   547,   485,   547,   547,   547,   484,   547,   485,
     547,   547,     7,    15,   486,    15,   485,   607,   547,   485,
     370,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   129,   363,   527,   527,   547,   547,   547,   485,   547,
     363,   547,   485,   485,   547,   547,   484,   357,   485,   485,
      64,   369,   547,   547,   485,   485,   547,   485,   485,   485,
     485,   485,   547,   424,   547,   547,   547,   363,   461,   357,
     485,   547,   547,   547,   485,   547,   485,   547,   547,   485,
     547,   547,   547,   485,   357,   485,   370,   547,   547,   370,
     547,   485,   547,   547,   547,   485,   547,   547,   485,   547,
     485,   547,   547,   547,   547,   547,   547,    15,   485,   585,
     485,   357,   485,   485,   547,   547,   547,    15,     8,   485,
     485,   547,   547,   547,   485,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   547,   547,   547,   547,   547,   547,   547,   547,   547,
     547,   485,   547,   485,   547,   547,   547,   547,   485,   547,
     547,   547,   547,   547,   547,   547,   547,    15,    15,    15,
     363,   871,    15,   257,   573,   124,   233,   394,    15,   366,
     573,     8,     8,     8,     8,     7,     8,   124,   358,   381,
       8,   363,   395,     8,     8,     8,     8,     8,   542,     8,
     542,     8,     8,     8,     8,   542,   573,     7,   218,   252,
     519,   521,   530,   531,   239,   539,   539,    10,    14,    15,
      16,    17,    27,    34,    36,    64,    92,   149,   201,   363,
     375,   491,   492,   494,   495,   496,   497,   503,   504,   505,
     506,   507,   510,    15,   547,     5,     9,    15,    16,    17,
     129,   493,   495,   503,   557,   571,   572,   547,    15,   557,
     547,     5,   556,   557,   572,   557,     8,     8,     8,     8,
       8,     8,     8,     8,     7,     8,     8,     5,     7,   363,
     634,   635,   363,   627,   486,    15,    15,   149,   474,   363,
     363,   734,   735,     8,   363,   651,   652,   735,   363,   365,
     363,    15,   523,   569,    23,    37,   363,   413,   414,    15,
     363,   597,   363,   665,   665,   363,   648,   649,   363,   526,
     423,    15,   363,   577,   149,   740,   526,     7,   469,   470,
     485,   608,   609,   363,   603,   609,    15,   548,   363,   579,
     580,   526,    15,    15,   526,   740,   527,   526,   526,   526,
     526,   363,   526,   366,   526,    15,   418,   486,   494,   495,
      15,   360,   363,   363,   645,   646,   476,   477,   478,   479,
       8,   666,   730,    15,   363,   591,   363,   582,   583,   570,
      15,    15,   363,   486,    15,   491,   743,    15,    15,   363,
     717,   719,     8,   363,    37,   412,    15,   495,   496,   486,
      15,    15,   548,   474,   486,   495,   363,   709,     5,    15,
     571,   572,   486,   363,   364,   486,   570,    15,   494,   628,
     629,   603,   607,   363,   595,   363,   689,   689,    15,   363,
     593,   709,   491,   502,   486,   370,    15,   363,   695,   695,
     695,   695,   695,     7,   491,   586,   587,   363,   588,   486,
     359,   363,   486,   363,   715,   717,   363,   485,   486,   363,
     463,    15,    15,   570,   363,    15,   609,    15,   609,   609,
     609,   609,   778,   834,   609,   609,   609,   609,   609,   609,
     778,   363,   370,   841,   842,   843,    15,    15,   370,   853,
      15,   491,   491,   491,   491,   490,   491,    15,    15,   370,
     860,   861,   862,   863,   370,   864,   865,   866,   867,   868,
     370,   869,   870,   370,   874,   875,   357,   357,   124,     5,
      21,   363,   367,   368,   362,   370,   363,   363,   363,   414,
       7,   370,   357,   124,   363,   363,     5,    15,   401,   402,
     363,   414,   414,   414,   414,   413,   494,   412,   363,   363,
     418,   425,   426,   428,   429,   547,   547,   239,   404,   491,
     492,   491,   491,   491,   491,     5,     9,    16,    17,    22,
      23,    24,    25,    26,    28,    29,    30,    31,    32,    33,
      35,    37,    38,   375,    15,   246,     3,    15,   246,   246,
      15,   500,   501,    21,   544,   569,   502,     5,     9,   166,
     558,   559,   560,   571,    26,   571,     5,     9,    23,    37,
     493,   570,   571,   570,     8,    15,   495,   564,   565,    15,
     491,   492,   507,   566,   567,   568,   566,   577,   363,   591,
     593,   595,   597,   363,     7,   370,   715,     8,    21,   629,
     414,   516,   491,   240,   542,    15,   370,    15,   468,     8,
     569,     7,   491,   524,   525,   526,    15,   363,   468,   414,
     473,   474,     8,   425,   516,   468,    15,     8,    21,     5,
       7,   471,   472,   491,   363,     8,    21,     5,    58,    86,
     126,   137,   165,   258,   610,   606,   607,   175,   598,   491,
     149,   537,     8,   491,   491,   362,   363,   419,   420,   494,
     499,   363,    26,   363,   532,   533,   535,   366,     8,     8,
      15,   231,   394,   480,   370,     8,   730,   363,   494,   699,
     709,   727,   728,     8,   557,    26,     5,     9,    16,    17,
      22,    23,    24,    25,    28,    29,    30,    31,    32,    33,
      34,    35,    37,    38,   375,   376,   377,   363,   370,   384,
     494,   491,    15,   370,   363,   363,   494,   494,   517,     8,
     666,   721,   363,   494,   655,   363,   458,   459,   537,   414,
      18,   570,   571,   570,   390,   393,   634,   629,     7,   607,
     609,   699,   709,   710,   711,   413,   414,   452,   453,    62,
     494,   754,    15,    15,     7,     8,    21,   585,   414,   366,
     414,   468,     8,   664,   686,    21,   370,   363,     8,   491,
     491,   468,   494,   542,   799,   494,   287,   811,   811,   542,
     808,   811,    15,   542,   776,   542,   815,   776,   776,   542,
     793,   542,   805,   468,   147,   148,   180,   314,   315,   318,
     319,   371,   844,   845,   846,     8,    21,   495,   670,   847,
      21,   847,   371,   845,   370,   751,   752,     8,     8,     8,
       8,   494,   497,   498,   769,   655,   191,   208,     8,    21,
      41,   209,   228,     8,    21,   337,   340,   341,   342,     8,
      21,   244,   329,   344,   345,   346,     8,    21,   363,   359,
     357,     8,    21,   213,   371,   468,    44,    87,    93,   119,
     143,   145,   178,   183,   187,   191,   194,   216,   230,   236,
     382,   383,   385,   363,   357,   485,   548,   569,   395,   468,
     542,   542,     8,    37,    15,   363,   431,   436,   370,    15,
     511,    21,     8,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   491,   491,
     491,   491,   569,    64,   129,   487,   489,   569,   494,   505,
     508,    64,   508,   502,     8,    21,     5,   491,   545,   560,
       8,    21,     5,     9,   491,    21,   491,   571,   571,   571,
     571,   571,    21,   564,   564,     8,   491,   492,   567,   568,
       8,     8,     8,   468,   468,   485,    43,    67,    82,    87,
      88,    94,   228,   259,   303,   638,   635,   370,   498,   514,
      21,   363,    15,   490,    67,   469,   652,   491,     7,     8,
      21,   544,    37,     8,    21,   649,   494,   497,   513,   515,
     569,   738,   471,     7,   468,   609,    15,    15,    15,    15,
      15,    15,   598,   609,   363,    21,   549,   580,    21,    21,
      15,     8,    21,     8,   501,   495,     8,   534,    26,   362,
     646,   477,   129,   481,   482,   483,   399,   169,   208,   282,
     370,    15,     7,     8,    21,   583,   566,    21,    21,   147,
     148,   180,    21,    18,    21,     7,   491,   509,   175,   322,
      37,     8,    21,   370,     8,    21,    26,     8,    21,   549,
     491,    21,   454,   455,   454,    21,     7,   609,   598,    15,
       7,     8,    21,     8,    15,    15,    26,   696,   697,   699,
     490,   491,   587,   370,     8,   686,     8,   664,   395,   385,
     372,    21,    21,    21,   609,   542,    21,   609,   542,   835,
     609,   542,   609,   542,   609,   542,   609,   542,    15,    15,
      15,    15,    15,    15,   370,   843,     8,    21,    21,   182,
     315,   318,     8,    21,   370,   370,   370,   491,    15,    15,
       8,    21,    21,    15,    15,   861,    15,    15,    15,   865,
      15,    15,    15,   870,    15,    15,    15,    15,    15,   875,
     366,   363,   368,    15,   400,   401,   468,   485,    15,     7,
       8,   363,   468,    15,   505,     5,   403,   491,   560,   414,
     494,   428,    15,    16,    17,    27,    36,    59,    64,    92,
     149,   201,   427,   429,   439,   440,   441,   442,   443,   444,
     445,   446,   431,   436,   437,   438,    15,   432,   433,    62,
     491,   566,   492,   487,    21,     8,   488,   491,   509,   560,
       7,   569,   474,   491,   569,     8,   565,    21,     8,     8,
       8,   492,   568,   492,   568,   492,   568,   363,   255,     8,
      21,   474,   473,    21,     7,    21,   491,   524,    21,   474,
     542,     8,    21,   560,   739,     8,    21,   472,   491,   610,
     569,    15,   612,   363,   611,   611,   491,   611,   468,   609,
     239,   526,   490,   420,   420,   363,   491,   533,    21,   491,
     509,     8,    21,    16,    15,    15,    15,   490,   727,   728,
     486,   494,   759,     7,   491,     7,    21,    21,   363,   605,
     495,   494,   494,   609,   656,   491,   459,   542,     8,    47,
     177,   363,   457,   370,   626,   628,   598,     7,     7,   491,
     712,   713,   710,   711,   453,   491,     5,   612,   755,   756,
     762,   491,   622,     8,    21,    15,    21,    71,   208,   370,
     370,   486,   172,   363,   466,   467,   495,   191,   208,   282,
     285,   290,   298,   779,   780,   781,   788,   800,   801,   802,
     609,   266,   809,   810,   811,   609,    37,   494,   832,   833,
      84,   265,   289,   299,   304,   777,   779,   780,   781,   782,
     783,   784,   786,   787,   788,   609,   779,   780,   781,   782,
     783,   784,   786,   787,   788,   801,   802,   816,   609,   779,
     780,   781,   788,   794,   609,   779,   780,   806,   609,   847,
     847,   847,   370,   848,   849,   847,   847,   495,   752,   329,
     315,   330,   569,   487,   498,   670,   370,   690,   696,   710,
     696,   655,   655,   498,   872,   370,   876,   877,   655,   655,
     491,   370,   878,   363,    18,    26,   405,    15,   384,     7,
     370,   400,   549,   549,   404,     5,   491,   442,   443,   444,
     447,   443,   445,   443,   445,   246,   246,   246,   246,   246,
       8,    37,   363,   430,   494,     5,   432,   433,     8,    15,
      16,    17,   149,   363,   430,   434,   435,   448,   449,   450,
     451,    15,   433,    15,    21,   512,    21,    21,   501,   569,
     491,   502,   545,   559,   571,   535,   536,   492,   536,   536,
     536,   468,   363,   630,   633,   569,     8,    21,     7,   404,
     491,   569,   491,   569,   560,   623,   491,   613,   614,    21,
      21,    21,    21,     8,     8,   254,   520,   526,    21,   482,
     483,   670,   670,   670,    21,    21,   363,    15,    21,   491,
       7,     7,   491,   468,   173,     8,   660,   661,   662,   663,
     664,   666,   667,   668,   671,   672,   673,   686,   694,   535,
     455,    15,    15,   456,   255,     8,     7,     8,    21,    21,
      21,     8,    21,    21,   697,   698,    15,    15,   363,   363,
     464,   465,   467,    18,     8,    26,   778,    15,   778,   778,
      15,   609,   800,   778,   609,   809,   363,     8,    21,    15,
     778,    15,   778,    15,   609,   777,   609,   816,   609,   794,
     609,   806,    21,    21,    21,   316,   317,     8,    21,    21,
      21,    15,    15,   487,    21,    21,    22,    24,    33,    35,
     158,   159,   161,   162,   192,   234,   247,   691,   692,   693,
       8,    21,    21,    21,    21,    21,    21,     8,    21,   315,
     349,     8,    21,    21,    21,    21,   347,   348,     8,    21,
     491,   491,   640,   641,    21,   383,   405,     5,   491,   395,
       8,    21,     8,   508,   508,   508,   508,   508,   439,     5,
      15,   429,   440,   433,   363,   430,   438,   448,   449,   449,
       8,    21,     7,    16,    17,     5,    37,     9,   448,   491,
      20,   501,   488,    21,    26,    21,    21,    21,    21,    15,
     498,   560,   474,   651,   486,   513,   560,   739,   491,    21,
       7,     8,    21,   491,   370,    15,    21,    21,    21,     7,
     760,   761,   762,   491,   491,     7,   494,   657,   370,   662,
      26,   457,    26,   376,   630,   628,   363,   601,   602,   603,
     604,   713,   756,   609,    78,   586,   363,   665,   710,   687,
       8,   363,   467,   491,   609,   789,   370,   609,   609,   834,
     494,   832,   370,   491,   491,   609,   609,   609,   609,   849,
     670,   494,    21,    15,    15,   370,   498,   877,   491,     8,
      21,     7,    21,    21,   569,   447,   440,   569,   430,    26,
      21,   448,   435,   449,   449,   450,   450,   450,    21,   491,
       5,   491,   509,   631,   632,   494,     8,   670,   494,     8,
     491,   614,   370,    21,   254,   491,     8,    21,   491,    15,
      41,   135,   191,   209,   221,   223,   224,   226,   229,   320,
     491,   456,    21,    21,    15,     8,   132,   757,    21,    21,
       7,    21,   689,   691,   465,     5,    16,    17,    22,    24,
      33,    35,    37,   159,   162,   247,   305,   306,   307,   791,
      21,    94,   230,   284,   295,   803,    37,   191,   288,   299,
     785,    21,    21,    21,    21,   495,   670,   691,    21,     7,
       7,   403,    21,   487,   434,   448,    21,     8,     8,    21,
     474,   560,   255,    15,    21,   761,     5,   491,   658,   659,
      15,   674,    15,    15,    15,    15,    15,   695,   695,    15,
      15,     8,   490,   602,   699,   700,    15,   710,   688,   688,
       7,     8,    21,   835,    21,     8,    21,     8,     7,   404,
      21,    21,   491,   632,   491,   363,   615,   616,   491,     8,
      21,   609,   674,   709,   727,   670,   709,   710,   699,   696,
     491,   491,   669,   491,    21,     8,   370,    21,     7,     8,
      21,   670,   790,   491,   370,   491,   495,   363,   642,   643,
      21,     8,    15,    21,   659,   148,   180,   675,     7,    21,
      21,     7,    21,    15,    21,    21,     8,    21,     8,   699,
      78,   690,   690,    21,   328,    21,     8,   491,    40,   491,
     617,   618,   762,     7,     7,   676,   677,   699,   727,   710,
     586,   491,   491,    21,    21,    21,    15,   643,   363,   619,
       8,    21,     8,    21,    15,    21,    21,    21,     8,   490,
      17,   620,   621,   618,   677,   491,   678,   679,    21,   491,
      21,   622,    17,     7,     8,    21,     8,   764,   622,   491,
     679,    15,   370,   370,   680,   681,   682,   683,   684,   182,
     318,   128,   157,   217,     8,    21,     7,     7,    15,   685,
     685,   685,   681,   370,   683,   684,   370,   684,   489,     7,
      21,   684
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
#line 782 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 784 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 788 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 790 "gram1.y"
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
#line 804 "gram1.y"
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
#line 835 "gram1.y"
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
#line 844 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 850 "gram1.y"
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
#line 870 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 879 "gram1.y"
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
#line 895 "gram1.y"
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
#line 907 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 917 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 924 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 930 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 935 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 940 "gram1.y"
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
#line 964 "gram1.y"
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
#line 990 "gram1.y"
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
#line 1005 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 1007 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 1009 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 1013 "gram1.y"
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
#line 1030 "gram1.y"
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
#line 1044 "gram1.y"
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
#line 1068 "gram1.y"
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
#line 1084 "gram1.y"
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
#line 1098 "gram1.y"
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
#line 1116 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1118 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1125 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1128 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1130 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1136 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1138 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1145 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1147 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1149 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1154 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1158 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1162 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1168 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1177 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1181 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1186 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1207 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1212 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1217 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1224 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1240 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1244 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1252 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1260 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1269 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1277 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1281 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1283 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1287 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1289 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1291 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1293 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1295 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1297 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1299 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1301 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1303 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1305 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1307 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1309 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1311 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1313 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1315 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1317 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1319 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1321 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1326 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1335 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1345 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1353 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1363 "gram1.y"
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
#line 1384 "gram1.y"
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
#line 1403 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1405 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1407 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1411 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1413 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1417 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1421 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1423 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1427 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1433 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1437 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1439 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1443 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1447 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1451 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1455 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1459 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1465 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1469 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1473 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1479 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1484 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1491 "gram1.y"
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
#line 1502 "gram1.y"
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
#line 1515 "gram1.y"
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
#line 1526 "gram1.y"
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
#line 1539 "gram1.y"
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
#line 1549 "gram1.y"
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
#line 1562 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1567 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1573 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1577 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1582 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1587 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1593 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1597 "gram1.y"
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
#line 1607 "gram1.y"
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
#line 1620 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1625 "gram1.y"
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
#line 1644 "gram1.y"
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
#line 1670 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1672 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1684 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1691 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1692 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1693 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1694 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1695 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1696 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1697 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1702 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1704 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1708 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1710 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1717 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1721 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1723 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1725 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1733 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1740 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1746 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1752 "gram1.y"
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
#line 1761 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1769 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1782 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1784 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1787 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1791 "gram1.y"
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
#line 1806 "gram1.y"
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
#line 1822 "gram1.y"
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
#line 1840 "gram1.y"
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
#line 1860 "gram1.y"
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
#line 1880 "gram1.y"
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
#line 1902 "gram1.y"
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
#line 1919 "gram1.y"
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
#line 1937 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1944 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1951 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1958 "gram1.y"
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
#line 1971 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1978 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1985 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1996 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 2000 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 2002 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 2007 "gram1.y"
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
#line 2025 "gram1.y"
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
#line 2036 "gram1.y"
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
#line 2048 "gram1.y"
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
#line 2060 "gram1.y"
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
#line 2074 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2080 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2087 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2093 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2099 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2107 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2114 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2133 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2147 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2151 "gram1.y"
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
#line 2196 "gram1.y"
    {;;}
    break;

  case 223:
#line 2200 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2204 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2210 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2214 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2218 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2220 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2224 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2226 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2230 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2234 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2236 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2240 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2242 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2244 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2249 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2273 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2318 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2320 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2327 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2334 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2341 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2350 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2352 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2354 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2358 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2360 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2364 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2373 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2380 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2387 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2389 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2393 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2397 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2403 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2405 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2409 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2413 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2418 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2425 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2432 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2442 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2444 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2448 "gram1.y"
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
#line 2460 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2463 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2472 "gram1.y"
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
#line 2485 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2491 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2497 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2503 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2511 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2521 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2523 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2527 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 306:
#line 2529 "gram1.y"
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
#line 2562 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2564 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2568 "gram1.y"
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
#line 2606 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2608 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2611 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2612 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2617 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2621 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2629 "gram1.y"
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
#line 2638 "gram1.y"
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
#line 2647 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2657 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2666 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2668 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2672 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2680 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2695 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2702 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2704 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2708 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2723 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2724 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2728 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2730 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2742 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2744 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2748 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2754 "gram1.y"
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
#line 2766 "gram1.y"
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
#line 2777 "gram1.y"
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
#line 2794 "gram1.y"
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
#line 2832 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2834 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2838 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2840 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2842 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2853 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2857 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2863 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2865 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2869 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2871 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2873 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2877 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2879 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2883 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2885 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2887 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2889 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2891 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2893 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2895 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2897 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2899 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2901 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2903 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2905 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2907 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2909 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2911 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2913 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2915 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2917 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2919 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2921 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2923 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2925 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2927 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2930 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2931 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2943 "gram1.y"
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
#line 3017 "gram1.y"
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
#line 3029 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3031 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3035 "gram1.y"
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
#line 3166 "gram1.y"
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
#line 3216 "gram1.y"
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
#line 3260 "gram1.y"
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
#line 3302 "gram1.y"
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
#line 3360 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3362 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3364 "gram1.y"
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
#line 3404 "gram1.y"
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
#line 3446 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3456 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3458 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3462 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3466 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3468 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3472 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3474 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3480 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3482 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3488 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3498 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3504 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3511 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3517 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3525 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3533 "gram1.y"
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
#line 3549 "gram1.y"
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
#line 3559 "gram1.y"
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
#line 3572 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3579 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3581 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3604 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3606 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3608 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3610 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3612 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3614 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3616 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3618 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3621 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3621 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3622 "gram1.y"
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
#line 3636 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3638 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3661 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3663 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3665 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3681 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3683 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3685 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3698 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3702 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3704 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3712 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3714 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3716 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3718 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3772 "gram1.y"
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
#line 3794 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3807 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3816 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3819 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3869 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3875 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3880 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3898 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3900 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3902 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3904 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3906 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3909 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3915 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3917 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3919 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3922 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3924 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3926 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3953 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3962 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3970 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3972 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3974 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3979 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3986 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3994 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3996 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 4000 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 4003 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 4005 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 4009 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 4015 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 4017 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 4019 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 4021 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4025 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4027 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4035 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4037 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4043 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4045 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4049 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4053 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4074 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4077 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4081 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4083 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4090 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4094 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4096 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4112 "gram1.y"
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
#line 4125 "gram1.y"
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
#line 4148 "gram1.y"
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
#line 4171 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4173 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4180 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4182 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4184 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4186 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4188 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4193 "gram1.y"
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
#line 4269 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4281 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4288 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4291 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4293 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4302 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4309 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4316 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4324 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4329 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4334 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4337 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4340 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4343 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4346 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4349 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4367 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4371 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4376 "gram1.y"
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
#line 4395 "gram1.y"
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
#line 4414 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4422 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4426 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4431 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4438 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4440 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4442 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4445 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4446 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4457 "gram1.y"
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
#line 4472 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4476 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4484 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4487 "gram1.y"
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
#line 4497 "gram1.y"
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
#line 4510 "gram1.y"
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
#line 4523 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4526 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 546:
#line 4528 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4531 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 548:
#line 4534 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 549:
#line 4538 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 550:
#line 4547 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 551:
#line 4550 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 552:
#line 4554 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 553:
#line 4556 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4562 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 555:
#line 4566 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4568 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4570 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 558:
#line 4577 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 559:
#line 4581 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4583 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4587 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, (yyvsp[(4) - (4)].ll_node), LLNULL);;}
    break;

  case 562:
#line 4589 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, (yyvsp[(5) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), LLNULL);;}
    break;

  case 563:
#line 4593 "gram1.y"
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
#line 4612 "gram1.y"
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
#line 4628 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 566:
#line 4639 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 567:
#line 4646 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 568:
#line 4648 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 569:
#line 4652 "gram1.y"
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
#line 4678 "gram1.y"
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
#line 4693 "gram1.y"
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
#line 4708 "gram1.y"
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
#line 4725 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 574:
#line 4733 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 575:
#line 4742 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 576:
#line 4750 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 577:
#line 4755 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 578:
#line 4760 "gram1.y"
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
#line 4782 "gram1.y"
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
#line 4798 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 581:
#line 4800 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 582:
#line 4804 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 583:
#line 4806 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 584:
#line 4813 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 585:
#line 4815 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 586:
#line 4817 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 587:
#line 4821 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4823 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4825 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4827 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4829 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 592:
#line 4831 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 593:
#line 4835 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 594:
#line 4838 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 595:
#line 4841 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4847 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 597:
#line 4853 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 598:
#line 4861 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 599:
#line 4865 "gram1.y"
    { startioctl();;}
    break;

  case 600:
#line 4873 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4875 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 602:
#line 4879 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 603:
#line 4881 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 604:
#line 4883 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4888 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4893 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 607:
#line 4898 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4903 "gram1.y"
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
#line 4912 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 610:
#line 4917 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 611:
#line 4922 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 612:
#line 4924 "gram1.y"
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
#line 5007 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 677:
#line 5009 "gram1.y"
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
#line 5020 "gram1.y"
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
#line 5041 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 680:
#line 5045 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 681:
#line 5047 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 682:
#line 5051 "gram1.y"
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
#line 5064 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 684:
#line 5068 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 685:
#line 5070 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 686:
#line 5074 "gram1.y"
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
#line 5085 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 688:
#line 5096 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 689:
#line 5100 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 690:
#line 5102 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 691:
#line 5106 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 692:
#line 5108 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 693:
#line 5110 "gram1.y"
    {
            if(parstate!=INEXEC) 
               err("Illegal shadow width specification", 56);  
            (yyval.ll_node) = make_llnd(fi,SHADOW_NAMES_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
          ;}
    break;

  case 694:
#line 5125 "gram1.y"
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
#line 5137 "gram1.y"
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
#line 5157 "gram1.y"
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
#line 5177 "gram1.y"
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
#line 5199 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 699:
#line 5205 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 700:
#line 5214 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 701:
#line 5222 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 702:
#line 5228 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 703:
#line 5236 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 704:
#line 5243 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 705:
#line 5249 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 706:
#line 5258 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 707:
#line 5262 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 708:
#line 5268 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 709:
#line 5276 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 710:
#line 5290 "gram1.y"
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
#line 5303 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 712:
#line 5309 "gram1.y"
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
#line 5325 "gram1.y"
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
#line 5340 "gram1.y"
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
#line 5368 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 716:
#line 5370 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 717:
#line 5374 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 718:
#line 5376 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 719:
#line 5380 "gram1.y"
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
#line 5409 "gram1.y"
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
#line 5432 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 722:
#line 5452 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 723:
#line 5454 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 724:
#line 5458 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 725:
#line 5479 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 726:
#line 5481 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 727:
#line 5484 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 728:
#line 5493 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 729:
#line 5497 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 730:
#line 5502 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 731:
#line 5504 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 732:
#line 5506 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 733:
#line 5508 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 734:
#line 5514 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 735:
#line 5516 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 736:
#line 5520 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 737:
#line 5530 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
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
#line 5541 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 741:
#line 5543 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 742:
#line 5547 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 743:
#line 5551 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 744:
#line 5557 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 745:
#line 5567 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 746:
#line 5569 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 747:
#line 5573 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 748:
#line 5575 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 749:
#line 5577 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 750:
#line 5584 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 751:
#line 5601 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 752:
#line 5603 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 753:
#line 5607 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 754:
#line 5609 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 755:
#line 5613 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 756:
#line 5620 "gram1.y"
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
#line 5630 "gram1.y"
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
#line 5659 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 759:
#line 5674 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 760:
#line 5681 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 761:
#line 5699 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 762:
#line 5701 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 763:
#line 5705 "gram1.y"
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
#line 5719 "gram1.y"
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
#line 5745 "gram1.y"
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
#line 5758 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 767:
#line 5774 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 768:
#line 5776 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 769:
#line 5779 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 770:
#line 5781 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 771:
#line 5787 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 772:
#line 5791 "gram1.y"
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
#line 5819 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 774:
#line 5821 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 775:
#line 5825 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 776:
#line 5833 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 777:
#line 5839 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 778:
#line 5842 "gram1.y"
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
#line 5900 "gram1.y"
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
#line 5964 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 781:
#line 5966 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 782:
#line 5969 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 783:
#line 5973 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 784:
#line 5977 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 785:
#line 5981 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 786:
#line 5998 "gram1.y"
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
#line 6010 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 788:
#line 6014 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 789:
#line 6018 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 790:
#line 6028 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 791:
#line 6033 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 792:
#line 6038 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 793:
#line 6045 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 794:
#line 6053 "gram1.y"
    {ndim = 0;;}
    break;

  case 795:
#line 6054 "gram1.y"
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
#line 6065 "gram1.y"
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
#line 6076 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 798:
#line 6078 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 799:
#line 6082 "gram1.y"
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
#line 6093 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 801:
#line 6097 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 802:
#line 6099 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 803:
#line 6103 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 804:
#line 6114 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 805:
#line 6118 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 806:
#line 6120 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 807:
#line 6124 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 808:
#line 6136 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 809:
#line 6138 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 810:
#line 6145 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 811:
#line 6147 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 812:
#line 6151 "gram1.y"
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
#line 6167 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 814:
#line 6177 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
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
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 818:
#line 6195 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 819:
#line 6200 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 820:
#line 6210 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 821:
#line 6212 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 822:
#line 6216 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 823:
#line 6218 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 824:
#line 6226 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 825:
#line 6228 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 826:
#line 6232 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 827:
#line 6234 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 838:
#line 6251 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 839:
#line 6256 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 840:
#line 6260 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 841:
#line 6264 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 842:
#line 6268 "gram1.y"
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

  case 843:
#line 6281 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 844:
#line 6285 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 845:
#line 6289 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 846:
#line 6293 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 847:
#line 6296 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 848:
#line 6298 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 849:
#line 6300 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 850:
#line 6304 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 851:
#line 6306 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 852:
#line 6310 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 853:
#line 6315 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 854:
#line 6319 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 855:
#line 6323 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 856:
#line 6325 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 857:
#line 6329 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 858:
#line 6337 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 859:
#line 6343 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 860:
#line 6349 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
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
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 864:
#line 6361 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 865:
#line 6365 "gram1.y"
    { /*  PTR_LLND p;
                       p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
                       p->entry.string_val = (char *) "corner";
                       p->type = global_string;
                   */
                   (yyvsp[(1) - (7)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (7)].ll_node);  
                   (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 866:
#line 6377 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 867:
#line 6379 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 868:
#line 6383 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 869:
#line 6387 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 870:
#line 6389 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 871:
#line 6393 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 872:
#line 6395 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 873:
#line 6397 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 874:
#line 6399 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 875:
#line 6401 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 876:
#line 6403 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 877:
#line 6405 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 878:
#line 6409 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 879:
#line 6413 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 880:
#line 6417 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 881:
#line 6421 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 882:
#line 6425 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 883:
#line 6432 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 884:
#line 6438 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 885:
#line 6442 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 886:
#line 6445 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 887:
#line 6449 "gram1.y"
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

  case 888:
#line 6462 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 889:
#line 6464 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 890:
#line 6468 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 891:
#line 6470 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 892:
#line 6475 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6481 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 894:
#line 6487 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 895:
#line 6493 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 896:
#line 6499 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6505 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 898:
#line 6511 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 899:
#line 6517 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 900:
#line 6523 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 901:
#line 6532 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 902:
#line 6538 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 903:
#line 6555 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 904:
#line 6563 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 905:
#line 6571 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 906:
#line 6573 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 907:
#line 6575 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 908:
#line 6579 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 909:
#line 6583 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 910:
#line 6585 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 911:
#line 6589 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 912:
#line 6591 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 913:
#line 6599 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 914:
#line 6603 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 915:
#line 6614 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 916:
#line 6618 "gram1.y"
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

  case 917:
#line 6636 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 918:
#line 6638 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 919:
#line 6642 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 920:
#line 6644 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 921:
#line 6648 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 922:
#line 6650 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 923:
#line 6654 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 924:
#line 6658 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 925:
#line 6662 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 926:
#line 6671 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 927:
#line 6675 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 928:
#line 6679 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 929:
#line 6684 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 930:
#line 6688 "gram1.y"
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

  case 931:
#line 6700 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 932:
#line 6702 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 933:
#line 6706 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 934:
#line 6711 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 935:
#line 6715 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 936:
#line 6717 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 937:
#line 6721 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 938:
#line 6723 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 939:
#line 6727 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 940:
#line 6732 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 941:
#line 6739 "gram1.y"
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

  case 942:
#line 6762 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 943:
#line 6764 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 944:
#line 6766 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 945:
#line 6768 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 946:
#line 6770 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 947:
#line 6774 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 948:
#line 6785 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 949:
#line 6789 "gram1.y"
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

  case 950:
#line 6804 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 951:
#line 6811 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 952:
#line 6817 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 953:
#line 6819 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 954:
#line 6823 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 955:
#line 6827 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 956:
#line 6835 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 957:
#line 6839 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 958:
#line 6843 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 959:
#line 6851 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 960:
#line 6856 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 961:
#line 6870 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 962:
#line 6872 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 963:
#line 6876 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 964:
#line 6878 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 965:
#line 6887 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 966:
#line 6889 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 967:
#line 6891 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 968:
#line 6893 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 969:
#line 6929 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 970:
#line 6933 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 971:
#line 6937 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 972:
#line 6941 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 973:
#line 6945 "gram1.y"
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

  case 974:
#line 6957 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 975:
#line 6959 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 976:
#line 6963 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 977:
#line 6966 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 978:
#line 6968 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 979:
#line 6972 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 980:
#line 6977 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 981:
#line 6984 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 982:
#line 6987 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 983:
#line 6995 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 984:
#line 6999 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 985:
#line 7003 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 986:
#line 7006 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 987:
#line 7014 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_EXIT_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 988:
#line 7018 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 989:
#line 7022 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 990:
#line 7026 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 991:
#line 7030 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 992:
#line 7034 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 993:
#line 7038 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 994:
#line 7041 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 995:
#line 7043 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 996:
#line 7047 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 997:
#line 7049 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 998:
#line 7051 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 999:
#line 7055 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 1000:
#line 7059 "gram1.y"
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

  case 1001:
#line 7071 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1002:
#line 7073 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1003:
#line 7077 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1004:
#line 7079 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1005:
#line 7083 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1006:
#line 7085 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1007:
#line 7089 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1008:
#line 7093 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1009:
#line 7099 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1010:
#line 7111 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1011:
#line 7113 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1012:
#line 7117 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1013:
#line 7119 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1014:
#line 7123 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1015:
#line 7131 "gram1.y"
    { 
                PTR_LLND q;
                if((yyvsp[(16) - (16)].ll_node))
                  q = make_llnd(fi,ARRAY_OP, (yyvsp[(14) - (16)].ll_node), (yyvsp[(16) - (16)].ll_node), SMNULL);
                else
                  q = (yyvsp[(14) - (16)].ll_node);                  
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_CREATE_DIR,SMNULL,(yyvsp[(3) - (16)].ll_node),(yyvsp[(8) - (16)].ll_node),q); 
              ;}
    break;

  case 1016:
#line 7142 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1017:
#line 7144 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1018:
#line 7146 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1019:
#line 7150 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1020:
#line 7154 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1021:
#line 7156 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1022:
#line 7164 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1023:
#line 7168 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_CREATE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1024:
#line 7171 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1025:
#line 7173 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1026:
#line 7177 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_DELETE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1054:
#line 7211 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1055:
#line 7217 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1056:
#line 7223 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1057:
#line 7229 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1058:
#line 7235 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1059:
#line 7239 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1069:
#line 7256 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1070:
#line 7261 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1071:
#line 7266 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1072:
#line 7272 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1073:
#line 7278 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1074:
#line 7284 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1075:
#line 7289 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1076:
#line 7295 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1077:
#line 7301 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1078:
#line 7307 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1079:
#line 7314 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1080:
#line 7320 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1081:
#line 7326 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1082:
#line 7333 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1084:
#line 7339 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1085:
#line 7345 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1086:
#line 7352 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1087:
#line 7358 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1088:
#line 7364 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1089:
#line 7370 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1090:
#line 7376 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1091:
#line 7382 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1092:
#line 7388 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1093:
#line 7394 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1094:
#line 7400 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1095:
#line 7406 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1096:
#line 7412 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1097:
#line 7418 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1098:
#line 7428 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1099:
#line 7433 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1100:
#line 7439 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1101:
#line 7443 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1106:
#line 7455 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1107:
#line 7463 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1108:
#line 7469 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1109:
#line 7475 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1110:
#line 7480 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1111:
#line 7486 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1112:
#line 7493 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1113:
#line 7499 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1114:
#line 7503 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1121:
#line 7517 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1122:
#line 7526 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1123:
#line 7530 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1124:
#line 7536 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1125:
#line 7543 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1126:
#line 7550 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1127:
#line 7557 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1128:
#line 7566 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1129:
#line 7572 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1130:
#line 7578 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1131:
#line 7582 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1134:
#line 7592 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1135:
#line 7598 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1136:
#line 7604 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1137:
#line 7608 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1140:
#line 7619 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1141:
#line 7625 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1142:
#line 7631 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1143:
#line 7636 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1144:
#line 7644 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1145:
#line 7650 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1146:
#line 7655 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1147:
#line 7662 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1148:
#line 7666 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1160:
#line 7686 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1161:
#line 7691 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1162:
#line 7696 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1163:
#line 7703 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1164:
#line 7708 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1165:
#line 7714 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1166:
#line 7720 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1167:
#line 7725 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1168:
#line 7730 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1169:
#line 7735 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1170:
#line 7739 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1171:
#line 7744 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1172:
#line 7749 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1173:
#line 7753 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1174:
#line 7758 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1175:
#line 7762 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1176:
#line 7768 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1177:
#line 7773 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1178:
#line 7779 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1179:
#line 7784 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1180:
#line 7790 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1181:
#line 7800 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1182:
#line 7804 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1183:
#line 7808 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1184:
#line 7812 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1185:
#line 7817 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1186:
#line 7820 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1194:
#line 7834 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1195:
#line 7838 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1196:
#line 7842 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1197:
#line 7844 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1198:
#line 7846 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1199:
#line 7850 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1200:
#line 7852 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1201:
#line 7854 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1202:
#line 7858 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1203:
#line 7860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1204:
#line 7864 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1205:
#line 7866 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1206:
#line 7870 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1207:
#line 7873 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1208:
#line 7876 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1209:
#line 7881 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1210:
#line 7883 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1211:
#line 7885 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1212:
#line 7887 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1213:
#line 7889 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1214:
#line 7893 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1215:
#line 7897 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1216:
#line 7902 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1217:
#line 7906 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1218:
#line 7908 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1219:
#line 7912 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1220:
#line 7914 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1221:
#line 7918 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1222:
#line 7922 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1223:
#line 7926 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ROUTINE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1224:
#line 7930 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1225:
#line 7932 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1232:
#line 7944 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1233:
#line 7948 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1234:
#line 7952 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1235:
#line 7956 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1236:
#line 7960 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1237:
#line 7964 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1238:
#line 7966 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1241:
#line 7974 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1242:
#line 7978 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1243:
#line 7982 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1244:
#line 7984 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1248:
#line 7994 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1249:
#line 7998 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1250:
#line 8002 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1251:
#line 8006 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1252:
#line 8008 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1253:
#line 8012 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1254:
#line 8014 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FISSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1255:
#line 8016 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1256:
#line 8018 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1257:
#line 8021 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_SHRINK_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1258:
#line 8025 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;

  case 1259:
#line 8029 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1260:
#line 8031 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1261:
#line 8035 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_CHECKPOINT_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1262:
#line 8039 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1263:
#line 8041 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1264:
#line 8045 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_TYPE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1265:
#line 8047 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_VARLIST_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1266:
#line 8049 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_EXCEPT_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1267:
#line 8051 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FILES_COUNT_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1268:
#line 8053 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_INTERVAL_OP,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);;}
    break;

  case 1269:
#line 8057 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1270:
#line 8059 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1271:
#line 8063 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1272:
#line 8065 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FLEXIBLE_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1273:
#line 8069 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_TIME_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1274:
#line 8071 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_ITER_OP, LLNULL,LLNULL,SMNULL);;}
    break;


/* Line 1267 of yacc.c.  */
#line 13950 "gram1.tab.c"
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



