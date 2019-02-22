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
     CP_CREATE = 321,
     CP_LOAD = 322,
     CP_SAVE = 323,
     CP_WAIT = 324,
     FILES = 325,
     VARLIST = 326,
     STATUS = 327,
     EXITINTERVAL = 328,
     TEMPLATE_CREATE = 329,
     SPF_ANALYSIS = 330,
     SPF_PARALLEL = 331,
     SPF_TRANSFORM = 332,
     SPF_NOINLINE = 333,
     SPF_PARALLEL_REG = 334,
     SPF_END_PARALLEL_REG = 335,
     SPF_PRIVATES_EXPANSION = 336,
     SPF_FISSION = 337,
     BINARY_OP = 340,
     UNARY_OP = 341
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
#define CP_CREATE 321
#define CP_LOAD 322
#define CP_SAVE 323
#define CP_WAIT 324
#define FILES 325
#define VARLIST 326
#define STATUS 327
#define EXITINTERVAL 328
#define TEMPLATE_CREATE 329
#define SPF_ANALYSIS 330
#define SPF_PARALLEL 331
#define SPF_TRANSFORM 332
#define SPF_NOINLINE 333
#define SPF_PARALLEL_REG 334
#define SPF_END_PARALLEL_REG 335
#define SPF_PRIVATES_EXPANSION 336
#define SPF_FISSION 337
#define BINARY_OP 340
#define UNARY_OP 341




/* Copy the first part of user declarations.  */
#line 339 "gram1.y"

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
#line 420 "gram1.y"
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
#line 871 "gram1.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 624 "gram1.y"

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
#line 1027 "gram1.tab.c"

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
#define YYLAST   5643

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  342
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  517
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1249
/* YYNRULES -- Number of states.  */
#define YYNSTATES  2459

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

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
     332,   333,   334,   335,   336,   337,   338,   339,     1,     2,
     340,   341
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
    4155,  4161,  4167,  4173,  4175,  4179,  4182,  4188,  4191,  4197
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     343,     0,    -1,    -1,   343,   344,   116,    -1,   345,   346,
     562,    -1,   345,   363,   562,    -1,   345,   508,   562,    -1,
     345,   133,   359,    -1,   345,   247,    -1,   257,    -1,     1,
      -1,   150,    -1,   193,   347,   354,    -1,    57,   347,   355,
      -1,   233,   347,   349,   356,    -1,   348,   233,   347,   349,
     356,    -1,   124,   347,   350,   356,   352,    -1,   351,   356,
     352,    -1,   114,   353,   356,   352,    -1,   164,   347,   353,
      -1,    -1,   202,   360,    -1,   195,   360,    -1,    95,   360,
      -1,   353,    -1,   353,    -1,   384,   124,   347,   353,    -1,
     384,   348,   124,   347,   353,    -1,   348,   124,   347,   353,
      -1,   348,   384,   124,   347,   353,    -1,   360,   361,    -1,
     360,   213,    15,   353,    21,    -1,   129,    -1,    -1,   353,
      -1,    -1,   353,    -1,    -1,    15,    21,    -1,    15,   357,
      21,    -1,   358,    -1,   357,     8,   358,    -1,   353,    -1,
       5,    -1,    64,    -1,    -1,    -1,    -1,   368,    -1,   369,
      -1,   370,    -1,   400,    -1,   396,    -1,   563,    -1,   405,
      -1,   406,    -1,   407,    -1,   465,    -1,   386,    -1,   401,
      -1,   411,    -1,   216,   475,    -1,   216,   475,   476,   442,
      -1,   123,   474,    -1,   183,   475,    15,   448,    21,    -1,
     376,    -1,   377,    -1,   382,    -1,   379,    -1,   381,    -1,
     397,    -1,   398,    -1,   399,    -1,   364,    -1,   452,    -1,
     450,    -1,   378,    -1,   142,   475,    -1,   142,   475,   353,
      -1,   141,   475,    15,   366,    21,    -1,   140,   475,    15,
      26,    21,    -1,   107,   517,    -1,    10,    -1,   365,    -1,
     367,    -1,    17,    -1,    16,    -1,     5,    -1,     9,    -1,
      37,    -1,    23,    -1,    22,    -1,    35,    -1,    38,    -1,
      34,    -1,    25,    -1,    32,    -1,    29,    -1,    28,    -1,
      31,    -1,    30,    -1,    33,    -1,    24,    -1,   245,   475,
     476,   353,    -1,   245,     8,   475,   360,   375,   476,   353,
      -1,   112,   475,    -1,   112,   475,   353,    -1,   384,   371,
     353,   475,   458,   390,   395,    -1,   370,     8,   353,   458,
     390,   395,    -1,    -1,     7,     7,    -1,     8,   360,   372,
       7,     7,    -1,   373,    -1,   372,     8,   360,   373,    -1,
     183,    -1,   375,    -1,    44,    -1,    87,   458,    -1,   119,
      -1,   145,    15,   374,    21,    -1,   143,    -1,   178,    -1,
     187,    -1,   216,    -1,   230,    -1,   236,    -1,   360,   148,
      -1,   360,   180,    -1,   360,   147,    -1,   194,    -1,   191,
      -1,   145,   475,    15,   374,    21,   476,   353,    -1,   376,
       8,   353,    -1,   178,   475,   476,   353,    -1,   377,     8,
     353,    -1,   230,   475,   476,   404,    -1,   378,     8,   404,
      -1,   191,   475,    -1,   191,   475,   476,   380,   444,    -1,
      -1,   219,   475,    -1,   194,   475,    -1,   194,   475,   476,
     383,   444,    -1,    -1,   388,   385,   392,   385,    -1,   244,
      15,   353,    21,   385,    -1,    -1,   387,   353,    -1,   386,
       8,   353,    -1,    13,    -1,     6,    -1,   389,    -1,   144,
      -1,   200,    -1,    68,    -1,    90,    -1,    91,    -1,   154,
      -1,    63,    -1,    -1,   391,    -1,     5,   538,   495,   539,
     385,    -1,     5,   538,    15,   539,     5,    21,    -1,     5,
     538,    15,   539,   481,    21,    -1,    -1,   391,    -1,    15,
     558,   393,   394,    21,    -1,    15,   558,   393,   394,     8,
     558,   393,   394,    21,    -1,   481,    -1,     5,    -1,   549,
     481,    -1,   549,     5,    -1,    -1,    -1,    26,   481,    -1,
      18,   481,    -1,    87,   476,   475,   353,   458,    -1,   396,
       8,   353,   458,    -1,    44,   475,   476,   404,    -1,   397,
       8,   404,    -1,   187,   475,   476,   404,    -1,   398,     8,
     404,    -1,   236,   475,   476,   404,    -1,   399,     8,   404,
      -1,    67,   475,   404,    -1,    67,   475,   403,   404,    -1,
     400,   532,   403,   532,   404,    -1,   400,     8,   404,    -1,
     167,   475,   402,   484,    -1,   401,   532,   402,   532,   484,
      -1,   401,     8,   484,    -1,    37,   353,    37,    -1,    23,
      -1,    37,   353,    37,    -1,   353,   458,    -1,   119,   475,
     476,   353,    -1,   405,     8,   353,    -1,   143,   475,   476,
     353,    -1,   406,     8,   353,    -1,   117,   475,   408,    -1,
     407,     8,   408,    -1,    15,   409,    21,    -1,   410,     8,
     410,    -1,   409,     8,   410,    -1,   353,    -1,   353,    15,
     480,    21,    -1,   489,    -1,   412,    -1,    80,   474,   413,
     415,    -1,   412,   532,   415,    -1,    -1,    -1,   416,    37,
     417,    37,    -1,   418,    -1,   416,     8,   418,    -1,   429,
      -1,   417,     8,   429,    -1,   419,   421,    -1,   419,   421,
     422,    -1,   419,   421,   423,    -1,   419,   421,   422,   423,
      -1,   419,   426,    -1,    -1,   353,    -1,   353,    -1,    15,
     424,    21,    -1,    15,   425,     7,   425,    21,    -1,   438,
      -1,   424,     8,   438,    -1,    -1,   438,    -1,    15,   427,
       8,   420,    26,   424,    21,    -1,   428,    -1,   427,     8,
     428,    -1,   421,   422,    -1,   421,   423,    -1,   421,   422,
     423,    -1,   426,    -1,   430,    -1,   419,   420,     5,   430,
      -1,   433,     5,   430,    -1,   419,   420,    -1,   432,    -1,
     434,    -1,   436,    -1,    36,    -1,    36,   246,   498,    -1,
      27,    -1,    27,   246,   498,    -1,    64,    -1,   431,    -1,
     419,   484,    15,   558,   477,    21,    -1,    59,    -1,   433,
      -1,    17,   433,    -1,    16,   433,    -1,   149,    -1,   149,
     246,   498,    -1,   435,    -1,    17,   435,    -1,    16,   435,
      -1,   201,    -1,   201,   246,   498,    -1,    92,    -1,    92,
     246,   498,    -1,    15,   437,     8,   437,    21,    -1,   434,
      -1,   432,    -1,   439,    -1,    17,   439,    -1,    16,   439,
      -1,   438,    17,   439,    -1,   438,    16,   439,    -1,   440,
      -1,   439,     5,   440,    -1,   439,    37,   440,    -1,   441,
      -1,   441,     9,   440,    -1,   149,    -1,   420,    -1,    15,
     438,    21,    -1,   443,    -1,   442,     8,   443,    -1,   404,
      -1,   403,    -1,   445,   447,   446,    -1,   444,     8,   445,
     447,   446,    -1,    -1,    -1,   353,    -1,   177,    15,   366,
      21,    -1,    47,    15,    26,    21,    -1,   449,    -1,   448,
       8,   449,    -1,   353,    26,   481,    -1,   163,   451,    -1,
     353,    -1,   451,     8,   353,    -1,   248,   475,   453,    -1,
     248,   475,   453,     8,   362,   456,    -1,   248,   475,   453,
       8,   362,   172,    -1,   248,   475,   453,     8,   362,   172,
     454,    -1,   353,    -1,   455,    -1,   454,     8,   455,    -1,
     353,    18,   353,    -1,   353,    -1,   457,    -1,   456,     8,
     457,    -1,   353,    18,   353,    -1,    -1,    15,   459,    21,
      -1,    -1,   460,   461,    -1,   459,     8,   461,    -1,   462,
      -1,     7,    -1,   481,     7,    -1,   481,     7,   462,    -1,
       5,    -1,   481,    -1,   464,    -1,   463,     8,   464,    -1,
     149,    -1,   130,   475,   466,    -1,   131,    -1,   467,    -1,
     466,     8,   467,    -1,   468,    15,   471,    21,    -1,    -1,
     469,   470,    -1,   231,   389,    -1,   384,    -1,   472,    -1,
     471,     8,   472,    -1,   473,    -1,   473,    16,   473,    -1,
     129,    -1,    -1,    -1,    -1,     7,     7,    -1,    -1,   479,
      -1,   481,    -1,   499,    -1,   549,   481,    -1,   558,   478,
      -1,   479,     8,   558,   478,    -1,   481,    -1,   480,     8,
     481,    -1,   482,    -1,    15,   481,    21,    -1,   497,    -1,
     485,    -1,   493,    -1,   500,    -1,   481,    17,   481,    -1,
     481,    16,   481,    -1,   481,     5,   481,    -1,   481,    37,
     481,    -1,   481,     9,   481,    -1,   365,   481,    -1,    17,
     481,    -1,    16,   481,    -1,   481,    25,   481,    -1,   481,
      29,   481,    -1,   481,    31,   481,    -1,   481,    28,   481,
      -1,   481,    30,   481,    -1,   481,    32,   481,    -1,   481,
      24,   481,    -1,   481,    33,   481,    -1,   481,    38,   481,
      -1,   481,    35,   481,    -1,   481,    22,   481,    -1,    34,
     481,    -1,   481,    23,   481,    -1,   481,   365,   481,    -1,
      17,    -1,    16,    -1,   353,    -1,   484,    -1,   487,    -1,
     486,    -1,   484,    15,   558,   477,    21,    -1,   484,    15,
     558,   477,    21,   491,    -1,   487,    15,   477,    21,    -1,
     487,    15,   477,    21,   491,    -1,   485,     3,   129,    -1,
     484,    -1,   487,    -1,   484,    15,   558,   477,    21,    -1,
     487,    15,   477,    21,    -1,   484,   491,    -1,    -1,   491,
      -1,    15,   492,     7,   492,    21,    -1,    -1,   481,    -1,
     494,    -1,   494,   246,   498,    -1,   495,    -1,   495,   246,
     498,    -1,   496,   490,    -1,    36,    -1,    27,    -1,   201,
      -1,    92,    -1,   149,    -1,    64,    -1,   484,   246,    64,
      -1,   495,   246,    64,    -1,    15,   482,     8,   482,    21,
      -1,   484,    -1,   495,    -1,   481,     7,   481,    -1,   481,
       7,    -1,   481,     7,   481,     7,   481,    -1,   481,     7,
       7,   481,    -1,     7,   481,     7,   481,    -1,     7,     7,
     481,    -1,     7,   481,    -1,     7,    -1,    -1,    -1,    14,
     394,   501,   555,   502,    20,    -1,   484,    -1,   487,    -1,
     488,    -1,   504,     8,   558,   488,    -1,   504,     8,   558,
     549,   484,    -1,   503,    -1,   505,     8,   558,   503,    -1,
     505,     8,   558,   549,   484,    -1,    -1,   484,    -1,   507,
       8,   484,    -1,   529,    -1,   528,    -1,   511,    -1,   519,
     511,    -1,   102,   537,   517,    -1,   103,   537,   516,    -1,
     108,   517,    -1,   509,    -1,   519,   509,    -1,   520,   529,
      -1,   520,   239,    -1,   519,   520,   239,    -1,    97,   537,
      15,   481,    21,   239,   516,    -1,    96,   537,   516,    -1,
     106,   537,   516,    -1,   512,    -1,    76,   537,    -1,   521,
     529,    -1,   521,    -1,   519,   521,    -1,   105,   537,   516,
      -1,   564,    -1,   825,    -1,   841,    -1,    89,   537,    15,
     481,    21,    -1,    89,   537,   538,   527,   539,   598,   510,
      -1,    -1,     8,   360,   254,    15,   481,    21,    -1,   254,
      15,   481,    21,    -1,   185,   537,   538,   527,   539,   532,
     525,    26,   481,     8,   481,    -1,   185,   537,   538,   527,
     539,   532,   525,    26,   481,     8,   481,     8,   481,    -1,
      62,   537,   513,   516,    -1,    84,   537,   516,    -1,   110,
     537,   516,    -1,   218,   537,   360,    62,    15,   481,    21,
      -1,   519,   218,   537,   360,    62,    15,   481,    21,    -1,
      15,   515,    21,    -1,   481,    -1,   481,     7,    -1,     7,
     481,    -1,   481,     7,   481,    -1,   514,    -1,   515,     8,
     514,    -1,    -1,   353,    -1,    -1,   353,    -1,    75,    -1,
     518,     7,    -1,   155,   537,    15,   481,    21,    -1,   122,
     537,    15,   522,   524,    21,    -1,   523,    -1,   522,     8,
     523,    -1,   525,    26,   499,    -1,    -1,     8,   481,    -1,
     353,    -1,   525,    26,   481,     8,   481,    -1,   525,    26,
     481,     8,   481,     8,   481,    -1,    -1,   149,    -1,   113,
     537,   516,    -1,    98,   537,   516,    -1,    98,   537,    15,
     481,    21,   516,    -1,   252,   537,    15,   481,    21,    -1,
     519,   252,   537,    15,   481,    21,    -1,   530,   481,    26,
     481,    -1,   188,   537,   485,    18,   481,    -1,    48,   537,
     464,   240,   353,    -1,    77,   537,    -1,   531,    -1,   540,
      -1,    46,   537,    15,   481,    21,   464,     8,   464,     8,
     464,    -1,   533,    -1,   533,    15,    21,    -1,   533,    15,
     534,    21,    -1,   214,   537,   492,    -1,   536,   537,   492,
      -1,    79,   537,   516,    -1,   115,   537,   516,    -1,    45,
     537,    15,   506,   504,    21,    -1,    81,   537,    15,   506,
     505,    21,    -1,   170,   537,    15,   507,    21,    -1,   253,
     537,    15,   481,    21,   485,    26,   481,    -1,   152,   414,
      -1,   186,   537,   464,    -1,    49,   537,   353,    -1,    49,
     537,   353,   532,    15,   463,    21,    -1,    69,   537,    15,
     463,    21,   532,   481,    -1,    -1,     8,    -1,    61,   537,
     353,   558,    -1,   558,   535,    -1,   534,     8,   558,   535,
      -1,   481,    -1,   549,   481,    -1,     5,   464,    -1,   184,
      -1,   232,    -1,    -1,    -1,    -1,   541,   546,    -1,   541,
     561,    -1,   541,     5,    -1,   541,     9,    -1,   543,   546,
      -1,   550,   546,    -1,   550,   545,    -1,   550,   546,   553,
      -1,   550,   545,     8,   553,    -1,   551,   546,    -1,   551,
     546,   555,    -1,   552,    -1,   552,     8,   555,    -1,   542,
     537,   559,    -1,    53,    -1,   215,    -1,   104,    -1,   544,
     537,   559,    -1,   139,    -1,   176,    -1,    66,    -1,   561,
      -1,     5,    -1,    15,   560,    21,    -1,    15,   547,    21,
      -1,   548,    -1,   547,     8,   558,   548,    -1,   560,    -1,
       5,    -1,     9,    -1,   549,   481,    -1,   549,     5,    -1,
     549,     9,    -1,   166,    -1,   197,   537,   559,    -1,   256,
     537,   559,    -1,   190,   537,   560,   559,    -1,   190,   537,
       5,   559,    -1,   554,    -1,   553,     8,   554,    -1,   485,
      -1,    15,   553,     8,   526,    21,    -1,   482,    -1,   557,
      -1,   556,    -1,   482,     8,   482,    -1,   482,     8,   557,
      -1,   557,     8,   482,    -1,   557,     8,   557,    -1,   556,
       8,   482,    -1,   556,     8,   557,    -1,   497,    -1,    15,
     481,    21,    -1,    15,   482,     8,   526,    21,    -1,    15,
     557,     8,   526,    21,    -1,    15,   556,     8,   526,    21,
      -1,    -1,    -1,   561,    -1,    15,   560,    21,    -1,   485,
      -1,   493,    -1,   560,   483,   560,    -1,   560,     5,   560,
      -1,   560,    37,   560,    -1,   560,     9,   560,    -1,   483,
     560,    -1,   560,    23,   560,    -1,   129,    26,   481,    -1,
      -1,   257,    -1,   565,    -1,   613,    -1,   588,    -1,   567,
      -1,   578,    -1,   573,    -1,   625,    -1,   628,    -1,   704,
      -1,   570,    -1,   579,    -1,   581,    -1,   583,    -1,   585,
      -1,   633,    -1,   639,    -1,   636,    -1,   762,    -1,   760,
      -1,   589,    -1,   614,    -1,   643,    -1,   693,    -1,   691,
      -1,   692,    -1,   694,    -1,   695,    -1,   696,    -1,   697,
      -1,   698,    -1,   706,    -1,   708,    -1,   713,    -1,   710,
      -1,   712,    -1,   716,    -1,   714,    -1,   715,    -1,   727,
      -1,   731,    -1,   732,    -1,   735,    -1,   734,    -1,   736,
      -1,   737,    -1,   738,    -1,   739,    -1,   642,    -1,   721,
      -1,   722,    -1,   723,    -1,   726,    -1,   740,    -1,   743,
      -1,   748,    -1,   753,    -1,   755,    -1,   756,    -1,   757,
      -1,   758,    -1,   719,    -1,   761,    -1,    82,   475,   566,
      -1,   565,     8,   566,    -1,   353,   458,    -1,    94,   475,
     568,    -1,   569,    -1,   568,     8,   569,    -1,   353,    -1,
     138,   475,   571,    -1,   572,    -1,   571,     8,   572,    -1,
     353,    -1,   228,   475,   577,   574,    -1,    15,   575,    21,
      -1,   576,    -1,   575,     8,   576,    -1,   481,    -1,   481,
       7,   481,    -1,     7,    15,   480,    21,    -1,   353,    -1,
     259,   475,   353,   458,    -1,   303,   475,   353,   458,    -1,
     578,     8,   353,   458,    -1,   136,   475,   580,    -1,   579,
       8,   580,    -1,   353,    -1,   211,   475,   582,    -1,   581,
       8,   582,    -1,   353,    -1,   205,   475,   584,    -1,   583,
       8,   584,    -1,   353,    -1,    70,   475,   586,    -1,   585,
       8,   586,    -1,   353,    -1,   175,   353,   458,    -1,    -1,
      88,   475,   592,   595,   587,    -1,   204,   537,   592,   596,
     598,   587,    -1,   204,   537,   596,   598,   587,     7,     7,
     590,    -1,   591,    -1,   590,     8,   591,    -1,   592,    -1,
     593,    -1,   353,    -1,   353,    15,   480,    21,    -1,   353,
      -1,    -1,   596,   598,    -1,    15,   597,    21,    -1,   598,
     599,    -1,   597,     8,   598,   599,    -1,    -1,    58,    -1,
      58,    15,   558,   612,    21,    -1,   126,    15,   600,    21,
      -1,   258,    15,   600,     8,   481,    21,    -1,   165,    15,
     481,    21,    -1,     5,    -1,   137,    15,   600,    21,    -1,
      86,    15,   601,    21,    -1,   353,    -1,    15,   602,    21,
     360,   255,   604,    -1,   603,    -1,   602,     8,   603,    -1,
     481,    -1,   481,     7,   481,    -1,   605,    -1,   605,    15,
     606,    21,    -1,   353,    -1,   607,    -1,   606,     8,   607,
      -1,   481,    -1,   752,    -1,    40,   608,   609,    -1,   353,
      -1,    -1,   610,    -1,    17,   611,    -1,   609,    17,   611,
      -1,   481,    -1,   549,   481,    -1,   549,   481,     8,   549,
     481,    -1,    43,   475,   616,   618,    -1,   199,   537,   617,
     618,    -1,   199,   537,   618,     7,     7,   615,    -1,   617,
      -1,   615,     8,   617,    -1,   353,    -1,   484,    -1,    15,
     623,    21,   360,   255,   619,    -1,   622,    15,   620,    21,
      -1,   621,    -1,   620,     8,   621,    -1,   481,    -1,     5,
      -1,   499,    -1,   353,    -1,   624,    -1,   623,     8,   624,
      -1,   353,    -1,     5,    -1,     7,    -1,   626,     7,     7,
     475,   353,   458,    -1,   625,     8,   353,   458,    -1,   627,
      -1,   626,     8,   360,   627,    -1,    82,    -1,   259,    -1,
     303,    -1,    94,    -1,    87,    15,   459,    21,    -1,   228,
     574,    -1,    43,    15,   623,    21,   360,   255,   619,    -1,
      43,    -1,    88,   596,   598,   587,    -1,    88,    -1,    67,
      -1,   384,     8,   360,    93,   475,    15,   629,    21,     7,
       7,   631,    -1,    -1,   630,     7,    -1,   629,     8,     7,
      -1,   632,    -1,   631,     8,   632,    -1,   353,    -1,   127,
     475,   634,    -1,   635,    -1,   634,     8,   635,    -1,   353,
      -1,    74,   475,   637,    -1,   638,    -1,   637,     8,   638,
      -1,   353,    -1,    51,   475,   640,    -1,    51,   475,     8,
     360,    67,     7,     7,   640,    -1,   641,    -1,   640,     8,
     641,    -1,   353,   458,    -1,   168,   537,    -1,   182,   537,
      15,   644,    21,   646,   650,    -1,   645,    -1,   644,     8,
     645,    -1,   484,    -1,   598,   173,   647,    -1,   598,    -1,
     484,    15,   648,    21,    -1,   649,    -1,   648,     8,   649,
      -1,   481,    -1,     5,    -1,    -1,   651,    -1,   652,    -1,
     651,   652,    -1,   656,    -1,   676,    -1,   684,    -1,   653,
      -1,   661,    -1,   663,    -1,   662,    -1,   654,    -1,   657,
      -1,   658,    -1,     8,   360,   209,    15,   699,     7,   700,
      21,    -1,     8,   360,   209,    15,   700,    21,    -1,     8,
     360,    71,    15,   655,     7,   700,    21,    -1,     8,   360,
      71,    15,   700,    21,    -1,   353,    -1,     8,   360,   169,
      15,   660,    21,    -1,     8,   360,   282,    15,   660,    21,
      -1,     8,   360,   191,    15,   660,    21,    -1,     8,   360,
     320,    15,   659,    21,    -1,   481,    -1,   481,     8,   481,
      -1,   481,     8,   481,     8,   481,    -1,   485,    -1,   660,
       8,   485,    -1,     8,   360,   135,    15,   699,     7,   717,
      21,    -1,     8,   360,   135,    15,   717,    21,    -1,     8,
     360,   229,    15,   481,    21,    -1,     8,   360,    41,   664,
      -1,     8,   360,    41,   664,   664,    -1,    15,   598,   665,
     666,    21,    -1,   148,     7,    -1,   180,     7,    -1,    -1,
     667,    -1,   666,     8,   667,    -1,   689,    -1,   689,    15,
     668,    21,    -1,   689,    15,   668,    21,    15,   670,    21,
      -1,   669,    -1,   668,     8,   669,    -1,   481,     7,   481,
      -1,   671,    -1,   670,     8,   671,    -1,   672,     7,   673,
       7,   674,    -1,   672,     7,   673,    -1,   672,     7,   674,
      -1,   672,    -1,   673,     7,   674,    -1,   673,    -1,   674,
      -1,   360,   217,   675,    -1,   360,   157,   675,    -1,   360,
     128,   675,    -1,    15,   479,    21,    -1,     8,   360,   208,
      15,   677,   681,   678,     8,   680,    21,    -1,     8,   360,
     208,    15,   677,   681,   678,    21,    -1,     8,   360,   208,
      15,   677,   679,   678,     7,   680,    21,    -1,    -1,    -1,
     353,    -1,   360,   681,    -1,   680,     8,   360,   681,    -1,
     682,    15,   485,    21,    -1,   683,    15,   660,     8,   481,
      21,    -1,   234,    -1,   192,    -1,   162,    -1,   159,    -1,
      35,    -1,    22,    -1,    24,    -1,    33,    -1,   247,    -1,
     158,    -1,   161,    -1,     8,   360,   223,    15,   686,    21,
      -1,     8,   360,   224,   685,    -1,     8,   360,   226,   685,
      -1,     8,   360,   221,    -1,     8,   360,   221,    15,   689,
      15,   575,    21,    21,    -1,   353,    -1,   687,    -1,   686,
       8,   687,    -1,   689,    -1,   689,    15,   688,    78,    21,
      -1,   689,    15,   688,   575,    21,    -1,   689,    15,   688,
     575,    21,    15,   360,    78,    21,    -1,    -1,   484,    -1,
     689,    -1,   690,     8,   689,    -1,   225,   537,   685,    -1,
     224,   537,   685,    -1,   227,   537,   685,    -1,   226,   537,
     685,    -1,   222,   537,   685,    15,   686,    21,    -1,   206,
     537,   679,    -1,   207,   537,   679,    -1,    72,   537,   655,
      -1,    73,   537,   655,    -1,   210,   537,    15,   699,     7,
     700,    21,    -1,   210,   537,    15,   700,    21,    -1,   353,
      -1,   701,    -1,   700,     8,   701,    -1,   689,    15,   702,
      21,    -1,   689,    -1,   703,    -1,   702,     8,   703,    -1,
     481,    -1,     7,    -1,   237,   475,   705,    -1,   704,     8,
     705,    -1,   353,   458,    -1,   238,   537,   707,    -1,   238,
     537,   707,   676,    -1,   238,   537,   707,   654,    -1,   238,
     537,   707,   676,   654,    -1,   238,   537,   707,   654,   676,
      -1,   353,    -1,   111,   537,    -1,   707,    15,   481,    21,
      -1,   707,    15,   499,    21,    -1,   174,   537,   486,   711,
      -1,    -1,   656,    -1,   109,   537,    -1,   160,   537,   709,
     360,   175,   594,   458,    -1,   160,   537,   709,   360,   321,
     485,    -1,   189,   537,   699,    -1,   212,   537,   699,    -1,
     135,   537,    15,   699,     7,   717,    21,    -1,   135,   537,
      15,   717,    21,    -1,   718,    -1,   717,     8,   718,    -1,
     689,    -1,   689,    15,   480,    21,    -1,   134,   537,    -1,
     134,   537,   656,    -1,   134,   537,   720,    -1,   134,   537,
     656,   720,    -1,     8,   360,   208,    15,   660,    21,    -1,
      50,   537,   725,    -1,    99,   537,    -1,    52,   537,   725,
      -1,   353,    -1,   724,    -1,   724,    15,   480,    21,    -1,
     120,   537,   485,    26,   485,    -1,    83,   537,   730,    -1,
      83,   537,   730,    15,   728,    21,    -1,   558,   729,    -1,
     728,     8,   558,   729,    -1,   549,   481,    -1,   149,    -1,
     100,   537,   730,    -1,   146,   537,   733,    -1,    -1,   481,
      -1,   330,   537,   480,    -1,   101,   537,    -1,   241,   537,
      -1,   242,   537,    -1,    56,   537,    -1,    65,   537,   558,
      15,   534,    21,   394,   476,   660,    -1,   322,   537,    15,
     741,    21,    -1,   742,    -1,   741,     8,   742,    -1,   360,
     315,    -1,   360,   318,    -1,   360,   182,    -1,   220,   537,
      15,   744,    26,   611,    21,   598,   747,    -1,   484,    15,
     745,    21,    -1,   746,    -1,   745,     8,   746,    -1,   601,
      -1,   752,    -1,   132,   690,    -1,    -1,   153,   537,    15,
     484,    18,   749,    21,    -1,   484,    -1,   484,    15,   750,
      21,    -1,   751,    -1,   750,     8,   751,    -1,   752,    -1,
       7,    -1,     5,    -1,   323,   537,   481,     8,   360,   328,
      15,   660,    21,     8,   360,   327,    15,   480,    21,   754,
      -1,    -1,     8,   360,   182,    -1,     8,   360,   318,    -1,
     324,   537,   481,    -1,   325,   537,   481,    -1,   325,   537,
     481,     8,   360,   315,    -1,   326,   537,   481,     8,   360,
     329,    15,   484,    21,    -1,   331,   537,    15,   759,    21,
      -1,   488,    -1,   759,     8,   488,    -1,   811,    -1,   764,
      -1,   763,    -1,   781,    -1,   784,    -1,   785,    -1,   786,
      -1,   787,    -1,   793,    -1,   796,    -1,   801,    -1,   802,
      -1,   803,    -1,   806,    -1,   807,    -1,   808,    -1,   809,
      -1,   810,    -1,   812,    -1,   813,    -1,   814,    -1,   815,
      -1,   816,    -1,   817,    -1,   818,    -1,   819,    -1,   820,
      -1,   268,   537,    -1,   275,   537,    -1,   291,   537,   598,
     765,    -1,   291,   537,   598,    -1,   532,   598,   766,   598,
      -1,   765,   532,   598,   766,   598,    -1,   768,    -1,   777,
      -1,   772,    -1,   773,    -1,   769,    -1,   770,    -1,   771,
      -1,   775,    -1,   776,    -1,   823,    15,   824,   822,    21,
      -1,   191,   767,    -1,   282,   767,    -1,   285,   767,    -1,
     265,   767,    -1,   299,   767,    -1,    84,    15,   360,   774,
      21,    -1,   191,    -1,   299,    -1,   288,    -1,   304,    15,
     481,    21,    -1,   289,    15,   481,    21,    -1,   208,    15,
     778,    21,    -1,   598,   780,     7,   779,    -1,   660,    -1,
      17,    -1,    16,    -1,     5,    -1,    37,    -1,   162,    -1,
     159,    -1,    35,    -1,    22,    -1,    24,    -1,    33,    -1,
     305,    -1,   306,    -1,   307,    -1,   247,    -1,   297,   537,
     598,   782,    -1,   297,   537,   598,    -1,   532,   598,   783,
     598,    -1,   782,   532,   598,   783,   598,    -1,   768,    -1,
     777,    -1,   769,    -1,   770,    -1,   279,   537,   598,   800,
      -1,   279,   537,   598,    -1,   296,   537,    -1,   269,   537,
     598,   788,    -1,   269,   537,   598,    -1,   272,   537,   598,
     800,    -1,   272,   537,   598,    -1,   532,   598,   789,   598,
      -1,   788,   532,   598,   789,   598,    -1,   768,    -1,   777,
      -1,   769,    -1,   770,    -1,   791,    -1,   790,    -1,   290,
      -1,   298,    15,   360,   792,     8,   481,    21,    -1,   298,
      15,   360,   792,    21,    -1,   230,    -1,    94,    -1,   284,
      -1,   295,    -1,   300,   537,   598,   794,    -1,   300,   537,
     598,    -1,   532,   598,   795,   598,    -1,   794,   532,   598,
     795,   598,    -1,   768,    -1,   769,    -1,   280,   537,   598,
     797,    -1,   280,   537,   598,    -1,   532,   598,   798,   598,
      -1,   797,   532,   598,   798,   598,    -1,   800,    -1,   799,
      -1,   266,   767,    -1,   287,    -1,   302,   537,    -1,   281,
     537,   598,   800,    -1,   281,   537,   598,    -1,   292,   537,
     598,   804,    -1,   292,   537,   598,    -1,   532,   598,   805,
     598,    -1,   804,   532,   598,   805,   598,    -1,   768,    -1,
     777,    -1,   772,    -1,   773,    -1,   769,    -1,   770,    -1,
     771,    -1,   775,    -1,   776,    -1,   791,    -1,   790,    -1,
     276,   537,    -1,   293,   537,   598,   765,    -1,   293,   537,
     598,    -1,   277,   537,    -1,   294,   537,   598,   765,    -1,
     294,   537,   598,    -1,   278,   537,    -1,   301,   475,   767,
      -1,   286,   537,    -1,   273,   537,    -1,   290,   537,    -1,
     274,   537,    -1,   264,   537,    -1,   263,   537,    -1,   283,
     537,   767,    -1,   283,   537,    -1,   267,   537,    15,   484,
      21,    -1,   267,   537,    -1,   271,   537,    15,   484,    21,
      -1,   271,   537,    -1,    37,   353,   823,    37,   824,    -1,
     821,    -1,   484,    -1,   822,     8,   821,    -1,   822,     8,
     484,    -1,    -1,    -1,   826,    -1,   839,    -1,   827,    -1,
     840,    -1,   828,    -1,   829,    -1,   308,   537,   830,    -1,
     310,   537,    -1,   312,   537,    15,   836,    21,    -1,   312,
     537,    15,    21,    -1,   312,   537,    -1,   313,   537,    15,
     836,    21,    -1,   313,   537,    15,    21,    -1,   313,   537,
      -1,   360,   361,    -1,   831,    -1,   832,    -1,   831,     8,
     832,    -1,   360,   833,    -1,   360,   835,    -1,   360,   834,
      -1,   147,    15,   836,    21,    -1,   148,    15,   836,    21,
      -1,   180,    15,   836,    21,    -1,   318,    15,   836,    21,
      -1,   319,    15,   836,    21,    -1,   314,    15,   837,    21,
      -1,   315,    -1,   660,    -1,   838,    -1,   837,     8,   838,
      -1,   360,   316,    -1,   360,   317,    -1,   309,    -1,   311,
      -1,   842,    -1,   843,    -1,   844,    -1,   845,    -1,   846,
      -1,   332,    15,   847,    21,    -1,   333,    15,   851,    21,
      -1,   334,    15,   856,    21,    -1,   336,   858,    -1,   337,
      -1,   848,    -1,   847,     8,   848,    -1,   849,    -1,   850,
      -1,   360,   208,    15,   680,    21,    -1,   360,   191,    15,
     660,    21,    -1,   852,    -1,   851,     8,   852,    -1,   853,
      -1,   854,    -1,   855,    -1,   360,   228,    15,   686,    21,
      -1,   360,    41,    15,   686,    21,    -1,   360,   209,    15,
     700,    21,    -1,   857,    -1,   856,     8,   857,    -1,   360,
     335,    -1,   360,   339,    15,   644,    21,    -1,   360,   338,
      -1,   360,   338,    15,   644,    21,    -1,   353,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   769,   769,   770,   774,   776,   790,   821,   830,   836,
     856,   865,   881,   893,   903,   910,   916,   921,   926,   950,
     977,   991,   993,   995,   999,  1016,  1030,  1054,  1070,  1084,
    1102,  1104,  1111,  1115,  1116,  1123,  1124,  1132,  1133,  1135,
    1139,  1140,  1144,  1148,  1154,  1164,  1168,  1173,  1180,  1181,
    1182,  1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,
    1192,  1193,  1198,  1203,  1210,  1212,  1213,  1214,  1215,  1216,
    1217,  1218,  1219,  1220,  1221,  1222,  1223,  1226,  1230,  1238,
    1246,  1255,  1263,  1267,  1269,  1273,  1275,  1277,  1279,  1281,
    1283,  1285,  1287,  1289,  1291,  1293,  1295,  1297,  1299,  1301,
    1303,  1305,  1307,  1312,  1321,  1331,  1339,  1349,  1370,  1390,
    1391,  1393,  1397,  1399,  1403,  1407,  1409,  1413,  1419,  1423,
    1425,  1429,  1433,  1437,  1441,  1445,  1451,  1455,  1459,  1465,
    1470,  1477,  1488,  1501,  1512,  1525,  1535,  1548,  1553,  1560,
    1563,  1568,  1573,  1580,  1583,  1593,  1607,  1610,  1629,  1656,
    1658,  1670,  1678,  1679,  1680,  1681,  1682,  1683,  1684,  1689,
    1690,  1694,  1696,  1703,  1708,  1709,  1711,  1713,  1726,  1732,
    1738,  1747,  1756,  1769,  1770,  1773,  1777,  1792,  1807,  1825,
    1846,  1866,  1888,  1905,  1923,  1930,  1937,  1944,  1957,  1964,
    1971,  1982,  1986,  1988,  1993,  2011,  2022,  2034,  2046,  2060,
    2066,  2073,  2079,  2085,  2093,  2100,  2116,  2119,  2128,  2130,
    2134,  2138,  2158,  2162,  2164,  2168,  2169,  2172,  2174,  2176,
    2178,  2180,  2183,  2186,  2190,  2196,  2200,  2204,  2206,  2211,
    2212,  2216,  2220,  2222,  2226,  2228,  2230,  2235,  2239,  2241,
    2243,  2246,  2248,  2249,  2250,  2251,  2252,  2253,  2254,  2255,
    2258,  2259,  2265,  2268,  2269,  2271,  2275,  2276,  2279,  2280,
    2282,  2286,  2287,  2288,  2289,  2291,  2294,  2295,  2304,  2306,
    2313,  2320,  2327,  2336,  2338,  2340,  2344,  2346,  2350,  2359,
    2366,  2373,  2375,  2379,  2383,  2389,  2391,  2396,  2400,  2404,
    2411,  2418,  2428,  2430,  2434,  2446,  2449,  2458,  2471,  2477,
    2483,  2489,  2497,  2507,  2509,  2513,  2534,  2559,  2561,  2565,
    2597,  2598,  2602,  2602,  2607,  2611,  2619,  2628,  2637,  2647,
    2653,  2656,  2658,  2662,  2670,  2685,  2692,  2694,  2698,  2714,
    2714,  2718,  2720,  2732,  2734,  2738,  2744,  2756,  2768,  2785,
    2814,  2815,  2823,  2824,  2828,  2830,  2832,  2843,  2847,  2853,
    2855,  2859,  2861,  2863,  2867,  2869,  2873,  2875,  2877,  2879,
    2881,  2883,  2885,  2887,  2889,  2891,  2893,  2895,  2897,  2899,
    2901,  2903,  2905,  2907,  2909,  2911,  2913,  2915,  2917,  2921,
    2922,  2933,  3007,  3019,  3021,  3025,  3156,  3206,  3250,  3292,
    3350,  3352,  3354,  3393,  3436,  3447,  3448,  3452,  3457,  3458,
    3462,  3464,  3470,  3472,  3478,  3488,  3494,  3501,  3507,  3515,
    3523,  3539,  3549,  3562,  3569,  3571,  3594,  3596,  3598,  3600,
    3602,  3604,  3606,  3608,  3612,  3612,  3612,  3626,  3628,  3651,
    3653,  3655,  3671,  3673,  3675,  3689,  3692,  3694,  3702,  3704,
    3706,  3708,  3762,  3782,  3797,  3806,  3809,  3859,  3865,  3870,
    3888,  3890,  3892,  3894,  3896,  3899,  3905,  3907,  3909,  3912,
    3914,  3916,  3943,  3952,  3961,  3962,  3964,  3969,  3976,  3984,
    3986,  3990,  3993,  3995,  3999,  4005,  4007,  4009,  4011,  4015,
    4017,  4026,  4027,  4034,  4035,  4039,  4043,  4064,  4067,  4071,
    4073,  4080,  4085,  4086,  4097,  4114,  4137,  4162,  4163,  4170,
    4172,  4174,  4176,  4178,  4182,  4258,  4270,  4277,  4279,  4280,
    4282,  4291,  4298,  4305,  4313,  4318,  4323,  4326,  4329,  4332,
    4335,  4338,  4342,  4360,  4365,  4384,  4403,  4407,  4408,  4411,
    4415,  4420,  4427,  4429,  4431,  4435,  4436,  4447,  4462,  4466,
    4473,  4476,  4486,  4499,  4512,  4516,  4519,  4522,  4526,  4535,
    4538,  4542,  4544,  4550,  4554,  4556,  4558,  4565,  4569,  4571,
    4573,  4577,  4596,  4612,  4621,  4630,  4632,  4636,  4662,  4677,
    4692,  4709,  4717,  4726,  4734,  4739,  4744,  4766,  4782,  4784,
    4788,  4790,  4797,  4799,  4801,  4805,  4807,  4809,  4811,  4813,
    4815,  4819,  4822,  4825,  4831,  4837,  4846,  4850,  4857,  4859,
    4863,  4865,  4867,  4872,  4877,  4882,  4887,  4896,  4901,  4907,
    4908,  4923,  4924,  4925,  4926,  4927,  4928,  4929,  4930,  4931,
    4932,  4933,  4934,  4935,  4936,  4937,  4938,  4939,  4940,  4941,
    4944,  4945,  4946,  4947,  4948,  4949,  4950,  4951,  4952,  4953,
    4954,  4955,  4956,  4957,  4958,  4959,  4960,  4961,  4962,  4963,
    4964,  4965,  4966,  4967,  4968,  4969,  4970,  4971,  4972,  4973,
    4974,  4975,  4976,  4977,  4978,  4979,  4980,  4981,  4982,  4983,
    4984,  4985,  4986,  4990,  4992,  5003,  5024,  5028,  5030,  5034,
    5047,  5051,  5053,  5057,  5068,  5079,  5083,  5085,  5089,  5091,
    5093,  5108,  5120,  5140,  5160,  5182,  5188,  5197,  5205,  5211,
    5219,  5226,  5232,  5241,  5245,  5251,  5259,  5273,  5287,  5292,
    5308,  5323,  5351,  5353,  5357,  5359,  5363,  5392,  5415,  5436,
    5437,  5441,  5462,  5464,  5468,  5476,  5480,  5485,  5487,  5489,
    5491,  5497,  5499,  5503,  5513,  5517,  5519,  5524,  5526,  5530,
    5534,  5540,  5550,  5552,  5556,  5558,  5560,  5567,  5585,  5586,
    5590,  5592,  5596,  5603,  5613,  5642,  5657,  5664,  5682,  5684,
    5688,  5702,  5728,  5741,  5757,  5759,  5762,  5764,  5770,  5774,
    5802,  5804,  5808,  5816,  5822,  5825,  5883,  5947,  5949,  5952,
    5956,  5960,  5964,  5981,  5993,  5997,  6001,  6011,  6016,  6021,
    6028,  6037,  6037,  6048,  6059,  6061,  6065,  6076,  6080,  6082,
    6086,  6097,  6101,  6103,  6107,  6119,  6121,  6128,  6130,  6134,
    6150,  6158,  6169,  6171,  6175,  6178,  6181,  6186,  6196,  6198,
    6202,  6204,  6213,  6214,  6218,  6220,  6225,  6226,  6227,  6228,
    6229,  6230,  6231,  6232,  6233,  6234,  6237,  6242,  6246,  6250,
    6254,  6267,  6271,  6275,  6279,  6282,  6284,  6286,  6290,  6292,
    6296,  6301,  6305,  6309,  6311,  6315,  6323,  6329,  6336,  6339,
    6341,  6345,  6347,  6351,  6363,  6365,  6369,  6373,  6375,  6379,
    6381,  6383,  6385,  6387,  6389,  6391,  6395,  6399,  6403,  6407,
    6411,  6418,  6424,  6429,  6432,  6435,  6448,  6450,  6454,  6456,
    6461,  6467,  6473,  6479,  6485,  6491,  6497,  6503,  6509,  6518,
    6524,  6541,  6543,  6551,  6559,  6561,  6565,  6569,  6571,  6575,
    6577,  6585,  6589,  6601,  6604,  6622,  6624,  6628,  6630,  6634,
    6636,  6640,  6644,  6648,  6657,  6661,  6665,  6670,  6674,  6686,
    6688,  6692,  6697,  6701,  6703,  6707,  6709,  6713,  6718,  6725,
    6748,  6750,  6752,  6754,  6756,  6760,  6771,  6775,  6790,  6797,
    6804,  6805,  6809,  6813,  6821,  6825,  6829,  6837,  6842,  6856,
    6858,  6862,  6864,  6873,  6875,  6877,  6879,  6915,  6919,  6923,
    6927,  6931,  6943,  6945,  6949,  6952,  6954,  6958,  6963,  6970,
    6973,  6981,  6985,  6990,  6992,  6999,  7004,  7008,  7012,  7016,
    7020,  7024,  7027,  7029,  7033,  7035,  7037,  7041,  7045,  7057,
    7059,  7063,  7065,  7069,  7072,  7075,  7079,  7085,  7097,  7099,
    7103,  7105,  7109,  7117,  7129,  7130,  7132,  7136,  7140,  7142,
    7150,  7154,  7157,  7159,  7162,  7164,  7165,  7166,  7167,  7168,
    7169,  7170,  7171,  7172,  7173,  7174,  7175,  7176,  7177,  7178,
    7179,  7180,  7181,  7182,  7183,  7184,  7185,  7186,  7187,  7188,
    7189,  7192,  7198,  7204,  7210,  7216,  7220,  7226,  7227,  7228,
    7229,  7230,  7231,  7232,  7233,  7234,  7237,  7242,  7247,  7253,
    7259,  7265,  7270,  7276,  7282,  7288,  7295,  7301,  7307,  7314,
    7318,  7320,  7326,  7333,  7339,  7345,  7351,  7357,  7363,  7369,
    7375,  7381,  7387,  7393,  7399,  7409,  7414,  7420,  7424,  7430,
    7431,  7432,  7433,  7436,  7444,  7450,  7456,  7461,  7467,  7474,
    7480,  7484,  7490,  7491,  7492,  7493,  7494,  7495,  7498,  7507,
    7511,  7517,  7524,  7531,  7538,  7547,  7553,  7559,  7563,  7569,
    7570,  7573,  7579,  7585,  7589,  7596,  7597,  7600,  7606,  7612,
    7617,  7625,  7631,  7636,  7643,  7647,  7653,  7654,  7655,  7656,
    7657,  7658,  7659,  7660,  7661,  7662,  7663,  7667,  7672,  7677,
    7684,  7689,  7695,  7701,  7706,  7711,  7716,  7720,  7725,  7730,
    7734,  7739,  7743,  7749,  7754,  7760,  7765,  7771,  7781,  7785,
    7789,  7793,  7799,  7802,  7806,  7807,  7808,  7809,  7810,  7811,
    7814,  7818,  7822,  7824,  7826,  7830,  7832,  7834,  7838,  7840,
    7844,  7846,  7850,  7853,  7856,  7861,  7863,  7865,  7867,  7869,
    7873,  7877,  7882,  7886,  7888,  7892,  7894,  7898,  7902,  7906,
    7907,  7908,  7909,  7910,  7913,  7917,  7921,  7925,  7929,  7933,
    7935,  7939,  7940,  7943,  7947,  7951,  7953,  7957,  7958,  7959,
    7963,  7967,  7971,  7975,  7977,  7981,  7983,  7985,  7987,  7990
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
  "CP_CREATE", "CP_LOAD", "CP_SAVE", "CP_WAIT", "FILES", "VARLIST",
  "STATUS", "EXITINTERVAL", "TEMPLATE_CREATE", "SPF_ANALYSIS",
  "SPF_PARALLEL", "SPF_TRANSFORM", "SPF_NOINLINE", "SPF_PARALLEL_REG",
  "SPF_END_PARALLEL_REG", "SPF_PRIVATES_EXPANSION", "SPF_FISSION",
  "BINARY_OP", "UNARY_OP", "$accept", "program", "stat", "thislabel",
  "entry", "new_prog", "proc_attr", "procname", "funcname", "typedfunc",
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
       0,   338,   339,     1,     2,     3,     4,     5,     6,     7,
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
     340,   341
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   342,   343,   343,   344,   344,   344,   344,   344,   344,
     344,   345,   346,   346,   346,   346,   346,   346,   346,   346,
     347,   348,   348,   348,   349,   350,   351,   351,   351,   351,
     352,   352,   353,   354,   354,   355,   355,   356,   356,   356,
     357,   357,   358,   358,   359,   360,   361,   362,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   364,   364,   364,
     364,   364,   365,   366,   366,   367,   367,   367,   367,   367,
     367,   367,   367,   367,   367,   367,   367,   367,   367,   367,
     367,   367,   367,   368,   368,   369,   369,   370,   370,   371,
     371,   371,   372,   372,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   374,   374,   374,   375,
     375,   376,   376,   377,   377,   378,   378,   379,   379,   380,
     381,   382,   382,   383,   384,   384,   385,   386,   386,   387,
     387,   388,   389,   389,   389,   389,   389,   389,   389,   390,
     390,   391,   391,   391,   392,   392,   392,   392,   393,   393,
     393,   393,   394,   395,   395,   395,   396,   396,   397,   397,
     398,   398,   399,   399,   400,   400,   400,   400,   401,   401,
     401,   402,   403,   403,   404,   405,   405,   406,   406,   407,
     407,   408,   409,   409,   410,   410,   410,   411,   412,   412,
     413,   414,   415,   416,   416,   417,   417,   418,   418,   418,
     418,   418,   419,   420,   421,   422,   423,   424,   424,   425,
     425,   426,   427,   427,   428,   428,   428,   428,   429,   429,
     429,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   431,   432,   432,   432,   433,   433,   434,   434,
     434,   435,   435,   435,   435,   436,   437,   437,   438,   438,
     438,   438,   438,   439,   439,   439,   440,   440,   441,   441,
     441,   442,   442,   443,   443,   444,   444,   445,   446,   447,
     447,   447,   448,   448,   449,   450,   451,   451,   452,   452,
     452,   452,   453,   454,   454,   455,   455,   456,   456,   457,
     458,   458,   460,   459,   459,   461,   461,   461,   461,   462,
     462,   463,   463,   464,   465,   465,   466,   466,   467,   469,
     468,   470,   470,   471,   471,   472,   472,   473,   474,   475,
     476,   476,   477,   477,   478,   478,   478,   479,   479,   480,
     480,   481,   481,   481,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   482,   483,
     483,   484,   485,   485,   485,   486,   486,   486,   486,   487,
     488,   488,   488,   488,   489,   490,   490,   491,   492,   492,
     493,   493,   493,   493,   493,   494,   494,   494,   494,   495,
     496,   496,   496,   497,   498,   498,   499,   499,   499,   499,
     499,   499,   499,   499,   501,   502,   500,   503,   503,   504,
     504,   504,   505,   505,   505,   506,   507,   507,   508,   508,
     508,   508,   508,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   509,   509,   510,   510,   510,   511,   511,   512,
     512,   512,   512,   512,   513,   514,   514,   514,   514,   515,
     515,   516,   516,   517,   517,   518,   519,   520,   521,   522,
     522,   523,   524,   524,   525,   526,   526,   527,   527,   528,
     528,   528,   528,   528,   529,   529,   529,   529,   529,   529,
     529,   529,   529,   529,   529,   529,   529,   529,   529,   529,
     529,   529,   530,   531,   531,   531,   531,   532,   532,   533,
     534,   534,   535,   535,   535,   536,   536,   537,   538,   539,
     540,   540,   540,   540,   540,   540,   540,   540,   540,   540,
     540,   540,   540,   541,   542,   542,   542,   543,   544,   544,
     544,   545,   545,   546,   546,   547,   547,   548,   548,   548,
     548,   548,   548,   549,   550,   551,   552,   552,   553,   553,
     554,   554,   555,   555,   555,   556,   556,   556,   556,   556,
     556,   557,   557,   557,   557,   557,   558,   559,   560,   560,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   562,
     562,   563,   563,   563,   563,   563,   563,   563,   563,   563,
     563,   563,   563,   563,   563,   563,   563,   563,   563,   563,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     564,   564,   564,   565,   565,   566,   567,   568,   568,   569,
     570,   571,   571,   572,   573,   574,   575,   575,   576,   576,
     576,   577,   578,   578,   578,   579,   579,   580,   581,   581,
     582,   583,   583,   584,   585,   585,   586,   587,   587,   588,
     589,   589,   590,   590,   591,   591,   592,   593,   594,   595,
     595,   596,   597,   597,   598,   599,   599,   599,   599,   599,
     599,   599,   599,   600,   601,   602,   602,   603,   603,   604,
     604,   605,   606,   606,   607,   607,   607,   608,   609,   609,
     610,   610,   611,   612,   612,   613,   614,   614,   615,   615,
     616,   617,   618,   619,   620,   620,   621,   621,   621,   622,
     623,   623,   624,   624,   624,   625,   625,   626,   626,   627,
     627,   627,   627,   627,   627,   627,   627,   627,   627,   627,
     628,   630,   629,   629,   631,   631,   632,   633,   634,   634,
     635,   636,   637,   637,   638,   639,   639,   640,   640,   641,
     642,   643,   644,   644,   645,   646,   646,   647,   648,   648,
     649,   649,   650,   650,   651,   651,   652,   652,   652,   652,
     652,   652,   652,   652,   652,   652,   653,   653,   654,   654,
     655,   656,   656,   657,   658,   659,   659,   659,   660,   660,
     661,   661,   662,   663,   663,   664,   665,   665,   665,   666,
     666,   667,   667,   667,   668,   668,   669,   670,   670,   671,
     671,   671,   671,   671,   671,   671,   672,   673,   674,   675,
     676,   676,   676,   677,   678,   679,   680,   680,   681,   681,
     682,   682,   682,   682,   682,   682,   682,   682,   682,   683,
     683,   684,   684,   684,   684,   684,   685,   686,   686,   687,
     687,   687,   687,   688,   689,   690,   690,   691,   691,   692,
     692,   693,   694,   695,   696,   697,   698,   698,   699,   700,
     700,   701,   701,   702,   702,   703,   703,   704,   704,   705,
     706,   706,   706,   706,   706,   707,   708,   709,   709,   710,
     711,   711,   712,   713,   713,   714,   715,   716,   716,   717,
     717,   718,   718,   719,   719,   719,   719,   720,   721,   722,
     723,   724,   725,   725,   726,   727,   727,   728,   728,   729,
     730,   731,   732,   733,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   741,   742,   742,   742,   743,   744,   745,
     745,   746,   746,   747,   747,   748,   749,   749,   750,   750,
     751,   751,   752,   753,   754,   754,   754,   755,   756,   756,
     757,   758,   759,   759,   760,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   761,   761,   761,   761,   761,   761,   761,   761,   761,
     761,   762,   763,   764,   764,   765,   765,   766,   766,   766,
     766,   766,   766,   766,   766,   766,   767,   768,   769,   770,
     771,   772,   773,   774,   774,   774,   775,   776,   777,   778,
     779,   780,   780,   780,   780,   780,   780,   780,   780,   780,
     780,   780,   780,   780,   780,   781,   781,   782,   782,   783,
     783,   783,   783,   784,   784,   785,   786,   786,   787,   787,
     788,   788,   789,   789,   789,   789,   789,   789,   790,   791,
     791,   792,   792,   792,   792,   793,   793,   794,   794,   795,
     795,   796,   796,   797,   797,   798,   798,   799,   800,   801,
     802,   802,   803,   803,   804,   804,   805,   805,   805,   805,
     805,   805,   805,   805,   805,   805,   805,   806,   807,   807,
     808,   809,   809,   810,   811,   812,   813,   814,   815,   816,
     817,   818,   818,   819,   819,   820,   820,   821,   822,   822,
     822,   822,   823,   824,   825,   825,   825,   825,   825,   825,
     826,   827,   828,   828,   828,   829,   829,   829,   830,   830,
     831,   831,   832,   832,   832,   833,   833,   833,   833,   833,
     834,   835,   836,   837,   837,   838,   838,   839,   840,   841,
     841,   841,   841,   841,   842,   843,   844,   845,   846,   847,
     847,   848,   848,   849,   850,   851,   851,   852,   852,   852,
     853,   854,   855,   856,   856,   857,   857,   857,   857,   858
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
       5,     5,     5,     1,     3,     2,     5,     2,     5,     1
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
    1218,   537,   537,   537,   537,   537,   537,   537,   537,   537,
       0,     0,     0,     0,  1228,   609,     0,    37,   609,    73,
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
       0,     0,     0,     0,     0,     0,     0,    45,    45,    45,
    1249,  1227,   610,     4,    20,    20,     0,     0,    45,     5,
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
      46,  1190,  1199,  1200,     0,     0,    45,     0,  1017,  1018,
       0,   985,   349,     0,     0,     0,  1229,  1231,  1232,     0,
       0,  1235,  1237,  1238,  1239,     0,     0,  1243,     0,     0,
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
    1212,     0,  1196,     0,     0,     0,   992,    45,    45,    45,
       0,   390,   391,  1022,     0,     0,     0,    45,  1224,     0,
       0,     0,    45,  1225,  1245,  1247,     0,    45,  1226,    28,
      37,     0,     0,    39,     0,    30,   159,   116,   310,   339,
     118,   120,     0,   121,   114,   122,   130,   129,   123,   124,
     125,     0,   112,   115,    26,     0,   310,     0,     0,   144,
     177,     0,     0,   222,   222,     0,   224,   217,   221,     0,
       0,     0,   352,     0,   359,   361,   358,   357,   375,   377,
     371,   365,   504,   368,   366,   369,   367,   370,   372,   374,
     360,   373,   378,   596,   411,   389,     0,   343,     0,   414,
     415,   401,   412,   403,     0,   596,   513,     0,   532,   530,
       0,   596,   564,   571,   572,   570,   599,   608,   603,   605,
     607,   604,   602,   563,   548,     0,     0,     0,   351,     0,
       0,     0,     0,     0,   694,   776,     0,   786,   789,   779,
       0,   788,   782,     0,   780,   781,   778,   771,     0,   429,
       0,     0,   506,     0,     0,     0,     0,   808,   477,   476,
       0,   474,     0,   193,     0,   527,   803,   427,   428,   432,
       0,     0,     0,   314,   317,   176,     0,   596,     0,     0,
       0,     0,     0,   709,   720,   310,   462,   724,   678,     0,
     481,     0,     0,   201,     0,   394,   974,     0,     0,     0,
      16,   799,   327,   337,     0,   333,   335,   331,     0,     0,
       0,     0,     0,     0,     0,   958,   682,    80,    79,   128,
     126,   127,   340,     0,   487,   423,     0,     0,     0,     0,
     191,     0,   520,     0,     0,   724,     0,     0,    64,   527,
     505,   599,   138,     0,   142,    45,     0,   708,     0,     0,
       0,     0,   927,     0,     0,     0,     0,     0,   907,   909,
       0,   689,   687,     0,    45,   944,    45,   943,   145,   340,
       0,   502,     0,  1173,     0,   724,  1175,     0,   724,     0,
       0,   724,     0,   724,     0,   724,     0,   724,     0,     0,
       0,    45,     0,     0,     0,  1201,     0,  1192,  1195,   996,
     994,   995,    45,   991,     0,     0,     0,   350,   596,   596,
       0,  1021,     0,    45,  1230,     0,     0,     0,  1236,     0,
       0,  1244,    15,    29,    41,     0,   173,   160,   117,     0,
      45,     0,    45,    27,   159,   539,   539,   169,   172,   168,
       0,   186,   189,   214,     0,     0,     0,   247,   245,   252,
     249,   263,   256,   261,     0,     0,   215,   238,   250,   242,
     253,   243,   258,   244,     0,   237,     0,   232,   229,   218,
     219,     0,     0,   425,   351,     0,   387,   596,   347,   344,
     345,     0,   398,     0,   534,   533,     0,     0,   579,   352,
       0,     0,     0,   351,   586,   351,   590,   351,   588,   310,
       0,   596,   518,     0,     0,   973,     0,   311,   478,   480,
     172,   322,     0,   596,   519,     0,   977,   596,   976,   318,
     320,   723,     0,     0,     0,   733,     0,     0,     0,     0,
     707,   464,   481,   501,     0,   203,   202,   381,   493,   490,
     488,     0,   491,     0,   328,     0,     0,     0,     0,     0,
       0,   960,     0,  1006,     0,     0,   422,   417,   947,   948,
     718,   310,   954,   437,   813,   816,   822,   294,   293,     0,
     287,     0,     0,   289,   288,     0,   757,   758,   710,     0,
     936,   935,     0,   933,     0,   930,   282,     0,  1012,  1001,
       0,   999,  1002,   752,     0,     0,   921,   913,   690,     0,
       0,     0,     0,     0,   300,     0,   299,   307,     0,  1182,
       0,  1182,  1182,  1118,     0,  1112,  1114,  1115,  1113,   724,
    1117,  1116,     0,  1182,   724,  1136,  1135,     0,     0,  1179,
    1178,     0,     0,  1182,     0,  1182,     0,   724,  1057,  1061,
    1062,  1063,  1059,  1060,  1064,  1065,  1058,     0,  1146,  1150,
    1151,  1152,  1148,  1149,  1153,  1154,  1147,  1156,  1155,   724,
       0,  1099,  1101,  1102,  1100,   724,     0,  1129,  1130,   724,
       0,     0,     0,     0,     0,     0,  1213,     0,     0,   849,
     993,     0,  1019,     0,   596,     0,  1023,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   791,
       0,   111,     0,   173,     0,   146,     0,   171,   170,   267,
     253,   266,     0,   255,   260,   254,   259,     0,     0,     0,
       0,     0,   222,   212,   223,   241,     0,   222,   234,   235,
       0,     0,     0,     0,   278,   223,   279,     0,     0,   227,
     268,   273,   276,   229,   220,     0,   503,     0,   413,   385,
     388,     0,   346,     0,   531,   566,   567,     0,     0,   351,
       0,     0,     0,   775,   769,   785,     0,     0,     0,   525,
       0,   340,   526,     0,   979,     0,     0,     0,   737,     0,
     735,   732,   727,   731,   729,     0,    45,     0,   463,   450,
     205,   334,   336,     0,     0,     0,   962,   957,   131,     0,
    1005,   421,     0,     0,   416,   953,     0,    45,   811,   823,
     824,   829,   833,   826,   834,   835,   830,   832,   831,   827,
     828,     0,     0,     0,     0,   285,     0,     0,     0,     0,
     931,   926,   472,     0,   998,   724,   908,     0,     0,   883,
     104,   306,   301,   303,     0,     0,     0,  1067,   724,  1068,
    1069,    45,  1110,   724,  1137,  1133,   724,  1182,     0,  1066,
      45,  1070,     0,  1071,     0,  1055,   724,  1144,   724,  1097,
     724,  1127,   724,  1205,  1206,  1207,  1215,  1216,    45,  1210,
    1208,  1209,     0,     0,     0,   393,  1234,   895,   896,   897,
     894,   899,   893,   900,   892,   891,   890,   898,   886,     0,
       0,    45,  1233,  1241,  1242,  1240,  1248,  1246,    31,   175,
     174,     0,     0,   119,   113,   107,     0,     0,   161,   596,
     166,     0,   248,   246,   264,   257,   262,   216,   222,   596,
       0,   240,   236,   223,     0,   233,     0,   270,   269,     0,
     225,   229,     0,     0,     0,     0,     0,   230,     0,   426,
     386,   348,   397,     0,   581,   593,   595,   594,     0,   430,
       0,     0,   806,     0,   433,     0,   978,   753,   726,     0,
       0,    45,     0,     0,     0,   841,   967,   842,  1011,     0,
    1008,  1010,   420,   419,     0,     0,   815,     0,   825,     0,
     288,     0,     0,   762,   759,   716,   711,   712,   714,   715,
     934,  1000,  1004,     0,     0,   381,     0,     0,     0,     0,
       0,   309,   308,   521,     0,     0,     0,  1111,  1134,     0,
    1181,  1180,     0,     0,     0,  1056,  1145,  1098,  1128,  1214,
       0,     0,   392,     0,     0,     0,     0,     0,   792,   162,
     163,     0,     0,   239,   596,   241,     0,   280,   228,     0,
     272,   271,   274,   275,   277,   473,     0,   767,   766,   768,
       0,   764,   431,     0,   990,   434,     0,   738,   736,     0,
     728,     0,     0,     0,  1007,   418,     0,     0,     0,     0,
       0,   904,     0,     0,     0,     0,     0,     0,   286,   291,
     290,     0,     0,     0,   997,   910,   911,     0,   839,   884,
     884,   305,   304,  1083,  1082,  1081,  1088,  1089,  1090,  1087,
    1084,  1086,  1085,  1094,  1091,  1092,  1093,     0,  1078,  1122,
    1121,  1123,  1124,     0,  1183,  1073,  1075,  1074,     0,  1077,
    1076,     0,  1020,     0,     0,   887,   793,     0,   172,   265,
       0,     0,   227,   226,     0,     0,   763,   510,     0,     0,
       0,   466,  1009,   821,   820,     0,   818,   724,   853,     0,
       0,     0,     0,     0,   902,   903,     0,     0,     0,     0,
     713,   915,  1003,    45,     0,     0,     0,     0,     0,  1120,
    1177,  1072,    45,   888,     0,     0,     0,   251,   231,   495,
     765,   754,   741,   734,   739,     0,     0,   817,   858,   854,
       0,     0,     0,     0,     0,     0,     0,     0,   845,     0,
     467,   717,     0,     0,   838,    45,    45,   881,  1080,  1079,
       0,     0,     0,   354,   796,   790,   794,   167,     0,     0,
     465,   819,     0,     0,     0,     0,   851,   843,     0,   837,
       0,   901,   852,     0,   844,     0,   916,     0,     0,     0,
    1119,     0,   889,     0,   496,     0,   744,     0,   742,   745,
     856,   857,     0,   859,   861,     0,     0,     0,   846,   468,
     912,   882,   880,     0,   795,   747,   748,     0,   740,     0,
     855,     0,   850,   836,     0,     0,     0,     0,   746,   749,
     743,   860,     0,     0,   864,   905,   847,  1014,   750,     0,
       0,     0,   862,    45,  1013,   751,   866,   865,    45,     0,
       0,     0,   867,   872,   874,   875,  1015,  1016,     0,     0,
       0,    45,   863,    45,    45,   596,   878,   877,   876,   868,
       0,   870,   871,     0,   873,     0,    45,   879,   869
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,     7,   205,   377,   206,   828,   740,   207,
     896,   608,   792,   678,   558,   894,   895,   434,   897,  1213,
    1490,   208,   209,   609,  1116,  1117,   210,   211,   212,   568,
    1271,  1272,  1120,  1273,   213,   214,   215,   216,  1146,   217,
     218,  1147,   219,   571,   220,   221,   222,   223,  1546,  1547,
     911,  1558,   930,  1818,   224,   225,   226,   227,   228,   229,
     773,  1157,  1158,   230,   231,   232,   735,  1069,  1070,   233,
     234,   699,   445,   923,   924,  1574,   925,   926,  1856,  1584,
    1589,  1590,  1857,  1858,  1585,  1586,  1587,  1576,  1577,  1578,
    1579,  1830,  1581,  1582,  1583,  1832,  2067,  1860,  1861,  1862,
    1159,  1160,  1462,  1463,  1945,  1694,  1138,  1139,   235,   450,
     236,   838,  1962,  1963,  1726,  1727,  1020,   707,   708,  1043,
    1044,  1032,  1033,   237,   745,   746,   747,   748,  1085,  1424,
    1425,  1426,   390,   367,   397,  1316,  1598,  1317,   871,   992,
     611,   630,   612,   613,   614,   615,  1233,  1072,   963,  1870,
     811,   616,   617,   618,   619,   620,  1321,  1600,   621,  1291,
    1867,  1389,  1370,  1390,  1013,  1129,   238,   239,  1908,   240,
     241,   681,  1025,  1026,   698,   416,   242,   243,   244,   245,
    1076,  1077,  1418,  1877,  1878,  1063,   246,   247,   248,   249,
    1195,   250,   966,  1329,   251,   369,   716,  1407,   252,   253,
     254,   255,   256,   641,   633,   972,   973,   974,   257,   258,
     259,   989,   990,   995,   996,   997,  1318,   794,   634,   789,
     553,   260,   261,   262,   702,   263,   718,   719,   264,   756,
     757,   265,   491,   823,   824,   826,   266,   267,   754,   268,
     808,   269,   802,   270,   690,  1060,   271,   272,  2116,  2117,
    2118,  2119,  1681,  1057,   400,   710,   711,  1056,  1646,  1709,
    1899,  1900,  2313,  2314,  2377,  2378,  2396,  2408,  2409,  1714,
    1897,   273,   274,  1696,   662,   797,   798,  1885,  2180,  2181,
    1886,   659,   660,   275,   276,   277,   278,  2031,  2032,  2345,
    2346,   279,   743,   744,   280,   695,   696,   281,   674,   675,
     282,   283,  1135,  1136,  1686,  2106,  2275,  2276,  1928,  1929,
    1930,  1931,  1932,   692,  1933,  1934,  1935,  2329,  1220,  1936,
    1937,  1938,  2278,  2354,  2382,  2383,  2413,  2414,  2431,  2432,
    2433,  2434,  2435,  2446,  1939,  2128,  2295,   804,  1809,  2018,
    2019,  2020,  1940,   816,  1477,  1478,  1957,  1153,  2292,   284,
     285,   286,   287,   288,   289,   290,   291,   785,  1155,  1156,
    1702,  1703,   292,   832,   293,   768,   294,   769,   295,  1132,
     296,   297,   298,   299,   300,  1093,  1094,   301,   751,   302,
     303,   304,   670,   671,   305,   306,  1392,  1636,   704,   307,
     308,   764,   309,   310,   311,   312,   313,   314,   315,  1225,
    1226,   316,  1163,  1710,  1711,  2214,   317,  1674,  2099,  2100,
    1712,   318,  2424,   319,   320,   321,   322,  1234,   323,   324,
     325,   326,   327,  1196,  1757,   850,  1735,  1736,  1737,  1761,
    1762,  1763,  2248,  1764,  1765,  1738,  2135,  2339,  2237,   328,
    1202,  1785,   329,   330,   331,   332,  1186,  1739,  1740,  1741,
    2243,   333,  1204,  1789,   334,  1192,  1744,  1745,  1746,   335,
     336,   337,  1198,  1779,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,  1750,
    1751,   851,  1499,   353,   354,   355,   356,   357,   861,   862,
     863,  1214,  1215,  1216,  1221,  1795,  1796,   358,   359,   360,
     361,   362,   363,   364,   365,   875,   876,   877,   878,   880,
     881,   882,   883,   884,   886,   887,   551
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -2267
static const yytype_int16 yypact[] =
{
   -2267,   133, -2267, -2267, -2267, -2267,   107,  4454, -2267, -2267,
   -2267,   168, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,   663, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267,   181, -2267, -2267,   530,   173, -2267, -2267, -2267,   181,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267,   190,   190, -2267, -2267, -2267, -2267, -2267,   190,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
     249, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,   190, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267,   392, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
     403,   375, -2267, -2267, -2267, -2267, -2267,   181, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267,   181, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
     473,   499,   519,   190, -2267,   313,  1246,   552,   313, -2267,
   -2267, -2267,   593,   631,   635,   654, -2267, -2267, -2267,   849,
     677,   190, -2267, -2267,   680,   705,   725,   780,   582,   127,
     790,   798,   804, -2267,   172, -2267, -2267, -2267,   313, -2267,
   -2267, -2267,   614,  1028,  1633,  2004, -2267, -2267,  2864, -2267,
     823, -2267, -2267,  1730, -2267,   829, -2267,  1339,   829,   851,
   -2267, -2267,   854, -2267, -2267, -2267,   888,   892,   908,   924,
     958, -2267, -2267, -2267, -2267,   964,   745, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267,   968, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267,   169,   190,   715,   965,
     971,   891,   190,   190,   119,   190, -2267,   190,   190,  1052,
   -2267,   455,  1056,   190,   190,   190,   190, -2267, -2267,   190,
   -2267,  1067,   190,   903,   190,   991, -2267, -2267, -2267,   190,
   -2267,  1077,   190, -2267,   190,  1088,   175, -2267,   903, -2267,
     190,   190,   190,   190, -2267, -2267, -2267, -2267, -2267,   190,
   -2267,   190,   190,   552,   190,  1096,   715,   190,  1104, -2267,
     190,   190, -2267, -2267, -2267,  1048,  1110,   190,   190,  1132,
    1141,   190,   715,  1150,  2864, -2267,  1161,  1165,   190, -2267,
    1100,   190,  1099, -2267,  1175,   190,   715,  1195,  1211, -2267,
     891,   715,   190,   190,  1824,    82,   190,   111, -2267, -2267,
     177, -2267,   326,   190,   190,   190,  1215,   190,   190,  2864,
     117, -2267, -2267,  1220,   190,   190,   190,   190,   190,  2707,
     190, -2267,   715,   190,   715,   190,   190, -2267, -2267,   190,
   -2267,   715,   190,  1229,  1234, -2267,   190, -2267, -2267,  1237,
   -2267, -2267,  1256, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267,  1287, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267,   190, -2267, -2267,  1301,  1338,
    1342,  2864,  2864,  2864,  2864,  2864,  1344, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267,  1071,   140, -2267, -2267,
     190,   190,   190,   190,  1214, -2267, -2267,  1152,   190,   190,
   -2267,   563,   190,   190,   190,   190,   190,   621,   190,  1099,
     190,   190,  1096, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267,  1054, -2267, -2267, -2267, -2267, -2267, -2267,  2864,  2864,
    2864, -2267,  2864, -2267, -2267, -2267, -2267, -2267, -2267,  2864,
    3454, -2267,    66,  1358, -2267,  1349, -2267,  1135,  1146,  1368,
   -2267, -2267,  1374,  2864, -2267, -2267,  1223, -2267, -2267,  1378,
    1248,  1358, -2267, -2267,  1084,   -13, -2267,  1223, -2267, -2267,
   -2267,  1398,   347,   138,  3195,  3195,   190,   190,   190,   190,
     190,   190,   190,  1405, -2267,   190, -2267, -2267, -2267,   452,
   -2267, -2267,  1399,   190, -2267,  2864, -2267,  1176,   632, -2267,
    1408, -2267, -2267,  1412,  1421, -2267, -2267, -2267, -2267, -2267,
    3017,   190,  1418, -2267,   190,  1412,   190, -2267,   891, -2267,
   -2267, -2267, -2267, -2267, -2267,  1427, -2267, -2267, -2267, -2267,
   -2267,  1412, -2267, -2267,  1428, -2267, -2267,   605,  1315,   190,
     610,   753, -2267,  1430,  1267,  2864,  1298, -2267,  1440, -2267,
   -2267,  2864,  2864, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267,   190, -2267,   190,  1435,   160,   190,
     552, -2267, -2267,  1443, -2267,  1444, -2267,  1441,  1278, -2267,
    1449, -2267,   190, -2267, -2267, -2267,  1450, -2267,  1433,  3537,
   -2267,   190, -2267,  5574, -2267,   190,  2864, -2267,  1445, -2267,
     190, -2267,   190,   190,   190,  1358,   850,   190,   190,   190,
    1298, -2267,   190,   198, -2267, -2267, -2267,  1248,  1084, -2267,
   -2267, -2267, -2267, -2267, -2267,   169, -2267,  1399,  1455,  1430,
   -2267, -2267, -2267, -2267, -2267, -2267,   190, -2267, -2267, -2267,
    5574, -2267,   455,  1404,   190, -2267,  1454, -2267, -2267, -2267,
   -2267,  1456,  2894,   672, -2267, -2267,   392,   190,   552, -2267,
     190,  1412, -2267,  1457,  1452, -2267,   190, -2267,  1462,  2864,
    2864, -2267,  1412,   190,   149,   190,  1187,  1187,   191,  1187,
   -2267,  1460,   195,   211,   233,   282,   284,   330, -2267,  1412,
     584, -2267,  1468, -2267,   144,   189, -2267,  3598,  5574,  3654,
    3736,  1472,  5574,   190,   310,   687, -2267, -2267, -2267,    96,
     707, -2267, -2267, -2267, -2267,  1047,   762, -2267,   190,   190,
   -2267, -2267, -2267, -2267,   769, -2267, -2267,  1268,  1412, -2267,
   -2267, -2267, -2267,  1419,   190, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267,  1412, -2267, -2267, -2267, -2267,  1474, -2267,  1474,
   -2267, -2267, -2267, -2267,   131, -2267,   442, -2267,  1469, -2267,
   -2267,  3770,  1478,  1482,  1482,  1660, -2267,  2864,  2864,  2864,
    2864,  2864,  2864,  2864,  2864,  2864,  2864,  2864,  2864,  2864,
    2864,  2864,  2864,  2864,  2864,  2864, -2267,  1423,  1367,  1471,
     460,   488,  2864, -2267, -2267, -2267,   772,  1403, -2267, -2267,
   -2267, -2267,   774, -2267,  1910,   812,  2864,  1488,  1248,  1248,
    1248,  1248,  1248, -2267,  1037, -2267,   347,   347,  1358,  1490,
   -2267,  3195,  5574,   151,   158, -2267,  1491,  1493, -2267, -2267,
    1412, -2267, -2267, -2267, -2267,  1412, -2267,   548, -2267,   169,
   -2267, -2267, -2267,   190,  3801,   190,  1489,  2864,  1436, -2267,
   -2267,   190, -2267,  2864,  3835, -2267,   784, -2267, -2267,  1473,
   -2267, -2267,   819, -2267,   190, -2267,   190, -2267, -2267,  1315,
   -2267, -2267, -2267, -2267, -2267,  4078,  1412, -2267, -2267, -2267,
    1496,  1498,  1499,  1500,  1502,  1503, -2267,  1267, -2267,   190,
   -2267,  4128, -2267, -2267,   190,  4159,  4200, -2267,  1506,   826,
    1497,  1368, -2267, -2267,   190, -2267,  1516, -2267,  1501, -2267,
     190, -2267,  1379,   728, -2267, -2267,   325, -2267, -2267,  1518,
   -2267,  1511,  1524,   834, -2267,   190,  1512, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267,  1513, -2267, -2267,   428,
    1520,  1519,  4255,  3032,   -68, -2267,  1505, -2267, -2267,   846,
   -2267, -2267, -2267, -2267, -2267,   852, -2267,  1522,   860, -2267,
   -2267, -2267,  2864, -2267,  1111, -2267, -2267, -2267,   868, -2267,
    1537, -2267,  1267,  1534,  1543,   876, -2267, -2267, -2267,  1545,
   -2267,  1536,  1539,  1530,   190,  2864,  2864,  2707, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267,  1549,  1553, -2267,   -42, -2267,
   -2267,  4286,  4322, -2267,  1542, -2267,   368,  1544, -2267, -2267,
   -2267, -2267,   437, -2267, -2267, -2267,   453, -2267,   467,   469,
     494, -2267,   557, -2267,   558, -2267,  1551,  1552,  1555,  1556,
   -2267,  1557,  1558, -2267, -2267, -2267, -2267, -2267, -2267,  1358,
    1566,  1554, -2267,  1559,   -59,   896, -2267, -2267, -2267, -2267,
    2864,   613,   661, -2267,   913,  1561,  1563, -2267, -2267,  1564,
    1572,  1573, -2267, -2267, -2267,  1574,  1575, -2267, -2267, -2267,
     552,   190,   110, -2267,  1576, -2267,  1587, -2267,  1412, -2267,
   -2267, -2267,  1578, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267,  1018, -2267, -2267, -2267,   190,  1412,   106,  2206, -2267,
   -2267,   190,   190, -2267,  1014,   442, -2267,  1579, -2267,  1533,
    2864,  3195, -2267,  2864,  1482,  1482,   583,   583,  1660,   878,
    2101,  2168,  5574,  2168,  2168,  2168,  2168,  2168,  2101,  1938,
    1482,  1938,  5605,  1471, -2267, -2267,  1560,  1590,  1744, -2267,
   -2267, -2267, -2267, -2267,  1592, -2267, -2267,   891,  5574, -2267,
    2864, -2267, -2267, -2267, -2267,  5574,   464,  5574,  1488,  1488,
    1093,  1488,   618, -2267,  1490,  1593,   347,  4402,  1595,  1597,
    1599,  3195,  3195,  3195, -2267, -2267,   190,  1594, -2267, -2267,
    1596,  1430, -2267,   392, -2267, -2267, -2267, -2267,  1353, -2267,
     916,   891, -2267,   891,   918,  1605,   928, -2267,  5574,  2864,
    3017, -2267,   935, -2267,   891,  1474, -2267,   676,   708, -2267,
     954,  1448,   957, -2267,  2518, -2267,   753, -2267,  1600,   190,
     190,  2864,   190, -2267, -2267,  1412, -2267, -2267, -2267,  1377,
     190,  2864,   190, -2267,   190, -2267,  1358,  2864,  1601,  3032,
   -2267, -2267, -2267, -2267,   963, -2267,  1607, -2267,  1602,  1606,
    1609,  1417,  2864,   190,   190, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267,   715,   190, -2267,  3070,  2772,  1608,   190,   190,
   -2267,   190, -2267,    13,   190, -2267,  2864,   190, -2267,  1474,
    5574, -2267,  1618,    89,  1618, -2267,   190,  1267,  1620,  3153,
     190,   190, -2267,   455,  2864,   681,  2864,   966, -2267,  1613,
     969,  5574, -2267,    37, -2267, -2267, -2267, -2267, -2267,   715,
      19, -2267,   190, -2267,   640, -2267, -2267,   295, -2267,    95,
     581, -2267,   904, -2267,   -65, -2267,   267, -2267,   190,   190,
     190, -2267,   190,   190,   584, -2267,   190, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267,  1304,  1316,  1305,  5574, -2267,  1471,
     190, -2267,   190, -2267, -2267,   190,   190,   190, -2267,   190,
     190, -2267, -2267, -2267, -2267,   190,   620, -2267, -2267,  1615,
   -2267,  1626, -2267, -2267,  1587, -2267, -2267, -2267, -2267,  5574,
    2545, -2267, -2267, -2267,   556,    36,    36,  1390,  1392, -2267,
   -2267,  1396,  1400,  1401,   152,   190, -2267, -2267, -2267, -2267,
    1639, -2267, -2267, -2267,  1579, -2267,  1637, -2267,   139,  1636,
   -2267,  1638,  4784, -2267,  1627,  1631,  1368, -2267, -2267,  4818,
   -2267,  2864,  2864,  1403, -2267,  5574,  1223,   347, -2267,   192,
    3195,  3195,  3195,   214, -2267,   230, -2267,   232, -2267,  1412,
     190, -2267, -2267,  1646,   973, -2267,  1650, -2267,  5574, -2267,
   -2267, -2267,  2864, -2267, -2267,  2864, -2267, -2267, -2267, -2267,
    5574, -2267,  1448,  2864,  1640, -2267,  1641,  1645,  4849,  1651,
   -2267,    74,   190, -2267,   983, -2267, -2267,  1632,  5574, -2267,
   -2267,  4818, -2267,  1379, -2267,  1379,   190,   190,   190,   984,
     992, -2267,   190,  1652,  1647,  2864,  4883,  3409, -2267, -2267,
   -2267,  1412,  1358, -2267, -2267,  1514,  1665,  5574, -2267,   190,
   -2267,  1669,  1678, -2267, -2267,  1420,  1687, -2267, -2267,  1691,
   -2267,  5574,   995, -2267,  1006, -2267, -2267,  4914, -2267, -2267,
    1027, -2267, -2267,  5574,  1679,   190, -2267, -2267, -2267,  1686,
    1688,  1507,  1642,   190,   190,  1689,  1696, -2267,   203, -2267,
    1693, -2267, -2267, -2267,  1694, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267,   640, -2267, -2267, -2267, -2267,   295,   190, -2267,
   -2267,  1049,  1701, -2267,  1702, -2267,  1704, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267,   581, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
     904, -2267, -2267, -2267, -2267, -2267,   -65, -2267, -2267, -2267,
     267,  1690,  1699,  1706,   717,  1051, -2267,  1707,  1708,  1358,
   -2267,  1715, -2267,  1716,  1471,  1711, -2267,  1069,   926,  1073,
    1083,  1121,  1123,  1131,  1137,  1712,  2864,  2864, -2267, -2267,
    1713, -2267,  1918,   620,  2553, -2267,  1138, -2267,  5574, -2267,
   -2267, -2267,  1714, -2267, -2267, -2267, -2267,   460,   460,   460,
     460,   460,  1014, -2267,  1728,  1739,  1735,  1014,  1636, -2267,
     442,   139,   187,   187, -2267, -2267, -2267,  1143,  1745,  1311,
     157, -2267,  1746,   139, -2267,  2864, -2267,  1733, -2267,  1368,
   -2267,  1744,  5574,  1743, -2267, -2267,  1084,  1741,  1747,  1145,
    1749,  1752,  1753, -2267, -2267, -2267,  1750,     1,   891, -2267,
     190,   715,  5574,     1,  5574,  1448,  2864,  1754,  4948,  1153,
   -2267, -2267, -2267, -2267, -2267,  2864, -2267,  1762, -2267, -2267,
   -2267, -2267, -2267,  1154,  1160,  1164, -2267, -2267, -2267,   815,
   -2267,  5574,  2864,  2864,  4982, -2267,   190, -2267, -2267,  1665,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267,  1755,    89,  1756,  3537, -2267,   190,   190,   190,  3153,
   -2267, -2267, -2267,   681, -2267, -2267, -2267,  2856,   190, -2267,
   -2267,  1761,  1775, -2267,   190,   190,  2864, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,    95, -2267,
   -2267, -2267,  2864, -2267,  2864, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267,   190,   190,  1765,   714, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,  1772,
    1773, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,  5574,
    5574,  1180,  1783, -2267, -2267, -2267,  1770,  5013, -2267, -2267,
   -2267,   556, -2267, -2267, -2267, -2267, -2267, -2267,  1014, -2267,
     190, -2267, -2267,  1777,  1767, -2267,   848,   157,   157,   139,
   -2267,   139,   187,   187,   187,   187,   187,  1059,  5044, -2267,
   -2267, -2267, -2267,  2864, -2267, -2267, -2267, -2267,  2449, -2267,
     190,  1787,  1421,   190, -2267,   190, -2267,  5075, -2267,  2864,
    2864, -2267,  5106,  1548,  2864, -2267, -2267, -2267, -2267,  1183,
   -2267, -2267,  5574,  5574,  2864,  1781, -2267,   914, -2267,  2864,
   -2267,  1776,  1784, -2267, -2267,  1789,  1798, -2267, -2267, -2267,
   -2267, -2267,  1680,  1792,  1190,  1803,  1808,  1201,   907,   190,
     190, -2267, -2267,  5574,   808,  1799,    -9, -2267, -2267,  1788,
   -2267, -2267,   373,  5137,  5168, -2267, -2267, -2267, -2267, -2267,
    1204,  1805,   756,   190,   190,   926,  1817,  1820, -2267, -2267,
   -2267,  2206,  1807, -2267,  1471, -2267,   139, -2267,  1059,  1810,
     157,   157, -2267, -2267, -2267, -2267,  5199, -2267,  4818, -2267,
    1206, -2267, -2267,   891,  1566, -2267,  1448,  5574, -2267,  1577,
   -2267,  1818,  5230,   815, -2267,  5574,  2641,  1819,  1822,  1827,
    1828,  1829,  1830,   190,   190,  1831,  1834,  5261, -2267, -2267,
   -2267,  2864,   190,   190, -2267, -2267,  1835,   190, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267,  1845, -2267, -2267,
   -2267, -2267, -2267,  1216, -2267, -2267, -2267, -2267,  1814, -2267,
   -2267,  1846, -2267,   603,  1847, -2267, -2267,  1850, -2267, -2267,
    1832,  1239,  1059, -2267,  2864,  2449, -2267, -2267,  2864,   190,
    2864, -2267, -2267, -2267,  5574,  1253, -2267, -2267,  1819,   190,
     190,   190,   190,   190, -2267, -2267,  2864,  2864,  2864,  1260,
   -2267, -2267,  1853, -2267,  1261,  1851,  1262,   190,  2864, -2267,
   -2267, -2267, -2267, -2267,  2864,   190,  1841, -2267, -2267,  5292,
   -2267,  5574, -2267, -2267,  1848,  5323,  2641, -2267,    45, -2267,
    1857,  1265,  1269,  1859,  1270,  1852,  1277,  5354,  5385,  1854,
    5416, -2267,   190,  1790, -2267, -2267, -2267, -2267,  1566, -2267,
    5447,  1547,  5478,   885, -2267,  1861, -2267, -2267,  2864,  2485,
   -2267, -2267,  1864,  1869,   190,   190, -2267, -2267,   190, -2267,
    2707, -2267, -2267,  2864, -2267,  2864, -2267,  1862,  1280,  1284,
   -2267,  1863, -2267,   190,  5574,   190,  5574,  1286, -2267, -2267,
   -2267, -2267,  1300, -2267,  1867,  1302,  1303,  1318,  5509,  5574,
   -2267, -2267, -2267,  2864, -2267, -2267,  1868,  2485, -2267,   190,
   -2267,  2864, -2267, -2267,  1866,  2864,  1355,  2864,  1874, -2267,
   -2267, -2267,  5543,  1359, -2267, -2267,  5574,  1876, -2267,  2864,
    2864,  2864,  1880, -2267, -2267, -2267,  5574, -2267, -2267,   -38,
     385,  1363, -2267,  1890,  1891, -2267, -2267, -2267,  1884,  1884,
    1884, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
     398,  1893, -2267,  1774, -2267,  1370, -2267, -2267, -2267
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2267, -2267, -2267, -2267, -2267,   -19,  1682,  1015, -2267, -2267,
    -676,   -52, -2267, -2267,  -359, -2267,   651, -2267,   -50,  1008,
   -2267, -2267, -2267,  2075,   -37, -2267, -2267, -2267, -2267, -2267,
   -2267,    86,   359,   733, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267,  -169,  -892, -2267, -2267, -2267,   831,   363,  1347,
   -2267,  -239, -1508,   100, -2267, -2267, -2267, -2267, -2267, -2267,
    1350,  -281,    93, -2267, -2267, -2267,  1346, -2267,  -395, -2267,
   -2267, -2267, -2267,  1233, -2267, -2267,   650, -1261, -1487,  1009,
     350, -1497,  -230,  -123,  1013, -2267,    92,   108, -1764, -2267,
   -1495, -1209, -1490,  -469, -2267,   -92, -1552, -1559, -1056, -2267,
   -2267,   478,   805,   268,  -153,    17, -2267,   507, -2267, -2267,
   -2267, -2267, -2267,  -165, -2267,     7,  -595,   978, -2267,   937,
     606,   604,  -369, -2267, -2267,   920, -2267, -2267, -2267, -2267,
     336,   339,  1931,  2298,  -363, -1272,   145,  -427,  -995,  1041,
    -549,  -604,  1314,  -213,  1565,  -855,  -968, -2267, -2267,  -607,
    -596,  -233, -2267,  -932, -2267,  -590,  -927, -1110, -2267, -2267,
   -2267,   126, -2267, -2267,  1321, -2267, -2267,  1779, -2267,  1780,
   -2267, -2267,   644, -2267,  -346,    -1, -2267, -2267,  1785,  1786,
   -2267,   609, -2267,  -725,  -277,  1250, -2267,   962, -2267, -2267,
    -203, -2267,  1003,   430, -2267,  3878,  -412, -1089, -2267, -2267,
   -2267, -2267, -2267, -2267,  1144, -2267,   429,  -848, -2267, -2267,
   -2267,   184, -1252,  -602,  1043,  -871,  -379,  -404,  -422,    34,
     -66, -2267, -2267, -2267,  1394, -2267, -2267,   972, -2267, -2267,
     943, -2267,  1217, -1904,   875, -2267, -2267, -2267,  1397, -2267,
    1395, -2267,  1406, -2267,  1409, -1005, -2267, -2267, -2267,  -166,
    -259, -2267, -2267, -2267,  -360, -2267,  -250,   655,   -57,   649,
   -2267,   -36, -2267, -2267, -2267,  -342, -2267, -2267, -2267, -2266,
   -2267, -2267, -2267, -2267, -2267, -1428,  -551,   116, -2267,  -197,
   -2267,  1274,  1062, -2267, -2267,  1065, -2267, -2267, -2267, -2267,
    -299, -2267, -2267,  1002, -2267, -2267,  1055, -2267,   185,  1072,
   -2267, -2267,  -273,   636, -2267, -2267, -2267,  -222, -2267, -2267,
     166, -2267,  -749,  -381,  -364, -2267, -2267, -2267, -1471, -2267,
   -2267, -2267,  -192, -2267, -2267,  -302, -2267,  -323, -2267,  -341,
   -2267,  -344, -1766, -1052,  -756, -2267,  -118,  -472,  -926, -1753,
   -2267, -2267, -2267,  -479, -1502,   388, -2267,  -736, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267,  -463, -1431,   633,
   -2267,   164, -2267,  1461, -2267,  1611, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -1401,   688, -2267,  1365, -2267,
   -2267, -2267, -2267,  1760, -2267, -2267, -2267,   226,  1717, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
     615, -2267, -2267, -2267,   174, -2267, -2267, -2267, -2267,   -53,
   -1849, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267,   586,   374,  -512, -1327, -1295, -1274, -1416,
   -1403, -1393, -2267, -1392, -1389, -1242, -2267, -2267, -2267, -2267,
   -2267,   356, -2267, -2267, -2267, -2267, -2267,   402, -1388, -1386,
   -2267, -2267, -2267,   355, -2267, -2267,   399, -2267,   579, -2267,
   -2267, -2267, -2267,   367, -2267, -2267, -2267, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267, -2267,   171,
   -2267,   176,   -94, -2267, -2267, -2267, -2267, -2267, -2267, -2267,
     938, -2267, -2267, -2267,  -806, -2267,   163, -2267, -2267, -2267,
   -2267, -2267, -2267, -2267, -2267, -2267,   921, -2267, -2267, -2267,
     923, -2267, -2267, -2267, -2267,   915, -2267
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1183
static const yytype_int16 yytable[] =
{
     403,   682,   667,   805,   693,   663,   817,   818,   819,   820,
     415,   415,   964,  1447,  1078,   809,  1091,   423,  1232,  1279,
     632,   858,  1374,  1575,   632,   577,   579,   968,  1320,  1320,
     982,   584,  1670,  1810,  1323,  1812,  1859,   556,  1697,  1704,
     631,  1595,   788,   998,   631,  1369,   449,   780,   705,   932,
    1826,  1459,  1403,  2124,   994,   994,  1067,   430,   720,  1223,
     723,  1807,   417,   736,   732,   726,   727,   728,   468,  1829,
    2101,   750,   471,   729,  1831,  1580,   731,  1176,   733,   761,
     451,   956,  1906,  2051,  1175,  2239,  1771,  1849,  1845,   395,
    1030,   781,  1864,   777,  1608,   993,   993,   466,   782,  1772,
     686,   841,   790,  -541,   793,  1811,  1037,  1448,  1719,  1773,
    1774,  1011,   800,  1775,  1777,   891,  1778,   812,   395,  1330,
    1350,  1555,  1891,  1519,   395,   493,  1729,   672,  1571,   827,
     414,   830,  1748,     2,     3,   578,  1691,  1239,   836,  1283,
     713,  2418,   559,  1730,  2436,   891,  -561,  1468,   414,  1266,
     714,   550,  1267,  2425,  1851,  1852,  1853,   583,  1232,  1351,
    1842,   892,  2064,   958,  -527,  1218,  -591,   971,  1284,   570,
    1480,  -582,   585,  1758,   656,  1768,   657,  1781,  -591,  1787,
     583,  1388,  1428,   366,   982,  1572,  1074,  -527,   398,  1843,
     722,  1724,   795,  2352,  2065,  1913,  1914,  1915,  -137,   583,
    -592,   958,  1851,   583,   975,  1759,   958,  1769,   977,  1782,
    1222,  1788,  -592,   799,   738,   984,  1142,  1731,   414,   583,
    1732,  2240,  -585,     8,   414,  2353,  1760,  -141,  1770,  1966,
    1783,   632,   983,   -61,  -585,   985,  1173,  1573,  -589,   414,
    -587,   583,   775,   967,  -541,  1720,  1149,  1183,   414,   783,
    -589,   631,  -587,  1449,  -561,   606,  1520,  1805,  1766,  1521,
    1776,   844,  1784,   846,  1205, -1107,  1692,  -582,   414,   414,
     847,   848,   849,   414,  -591,  2241,   852,   853,   854,   855,
    2437,   856,   857,     4,  2163,  1488,  2242,   635,  1854,  1092,
     583,   643,   583,  2057,  2058,  1430,   917,  -339,   414,  2056,
    1022,  -527,  -339,  1256,   414,  1240,   414, -1132,  -592,  1662,
    -339, -1054,   957,   433,   658,   661,   414,  1280,   414,   414,
     668,   669,   673,   669,  1241,   677,   679, -1143,  1907,   685,
    -585,   689,   691,   691,   694,  1027,  1854,   697,   583,  -137,
     701,   398,   697,  1154,  2101,  1556,  -589,   712,  -587, -1159,
     717,  2052,   697,  1058,   697,  1608,  1833,  1835,   415,   697,
     697,   697,   987,  2054,  1771,  1144,  1324,   697,  -141,   730,
     697,   982,   697,   982,   -61,  2220,   583,  1772,   741,   742,
     982,  1079,  1143,   500,  1145,   753,   755,  1773,  1774,   760,
       5,  1775,  1777,   632,  1778,  -561,   767,   632, -1162,   771,
   -1096,   994,  2255,  1420,   632,  1354, -1107,   489,  -582,   725,
    1355,   784,  1131,   631,   791,  -591,  1654,   631,   499,  1485,
     712,   801,   803,   803,   631,   807,   784,  1487,  1479,   988,
    1560,   813,   815,   815,   815,   815,   815,  1669,   825,  1151,
    1758,   829,  1348,   831,   767,   583, -1126,   834, -1132,  -592,
     837,  1395, -1054,  1768,   842,   414,  2387,  1285,  1729,  1781,
    1009,   583,  1698,  1787,  1415,  1016,  1824,  1825, -1143,  1171,
    1601,  -585,  1759,  1010,   687,   583,   414,   583,   683,  -563,
    1614,  1616,  1618,   859, -1106,  1769,   860,  -589,   547,  -587,
   -1159,  1782,   684,  1760,  1428,  1788,  1277,   874,   879,   885,
    2379,  1235,   583,  2170,  2171,   893,  1770,  2168,   898,   899,
     900,   685,  1783,  2438,   548,   903,   906,   907,  1236,  2114,
     912,   685,   685,   685,   685,  1766,  2438,  2127,   920,   921,
    1278,  2150,  2004,  1429,   549,   888,   889,   395,  1776, -1162,
     982, -1096,  2439,  1635,  1784,   396,  1829,   904,  2379,  1731,
    1152,  1831,  1322, -1131,   632,  2439,  1338,  1339,  1340,  1341,
    1342,  1743,  1806,  2165,  2245,   583,   583,   557,   908, -1053,
     552,   414,  1565,  1566,   631,  1439,  1440,  1313,   909,  1084,
    -563,  1575,  1188, -1142,   414, -1158,  2050, -1126,   937,   414,
     576,  1357,   938,  -563,   701,  1000,   753,   807,   801,   689,
    1005,   560,  2440,   831,  1007,  -527,   958,  1430,  1441,   606,
   -1161,   685,  2184,  1039,  2262,  1358,  -382,   414,  1047,  -527,
     953,   586,  1018,   978,  2303, -1106,  1040,   979,  1528,   697,
    1359,  1048,  1029,  1580,   685,  1360,  1361,   606,  1816,   561,
     583,  1185,  1362,   562,   683,  1191,  1817,  -527,  1571,   967,
    1197,  1219,  1219,  1201,  1203,   981,   901,  1046,   684,  1391,
     775,  2246,   563,  1548,  -383,  1752,   913,   914,   915,   916,
    -789,  -789,  2247, -1095, -1125,  1232,  1529,  2452,  2454,  -382,
    1167,  1554,  1068,  2254,  1073,   569,  1708,  1075,   572,  1593,
    2458,   956,  1078,  1168, -1131,  1237,  1643,  1091,  1091,  1086,
    1089,   994,  1791,  1792,  1793,  1572,  1797,  1798,  1238,  1118,
   -1053,  -383,  1119,   573,  1281,  1242,  1282,  -387,  1125,  1124,
    1126,  -563,   395,   959, -1142,  1133, -1158,  1137,  1243,   962,
     685,  1206,  1207,   574,   982,   982,   982,   982,   982,  1614,
    1616,  1618,   993,   658,  1594,   632,   632,   632,   632,   632,
    2306, -1161,   653,   654,  1089,  1330,  1012,  1573,  1049,  -385,
     685,   994,   994,   994,  1208,   631,   631,   631,   631,   631,
    1247,   962,  1729,   988,   988,   685,  1363,  1252,   685,  1031,
    1325,  2326,  1331,  1248,  1179,  1178,  2294,  2050,   575,  1730,
    1253,    25,  1380,  1326,  1896,  1332,    29,  1396,   580,  1479,
     775,  1479,  1613,  1615,  1617,  1381,   581,  1364,  1404,  2322,
    1650,  1050,   582,  2223, -1095, -1125,  1224,   978,    47,    48,
    1708,   979,  2098,   775,  2224,  2225,  2338,  1384,   627,   628,
    2226,  1729,  2227,  1336,  1412,   980,  1249,   829,   622,  1051,
    1385,  2228,  1434,  2229,   637,  2230,  1753,  1413,  1730,   981,
    2324,  1365,  1274,  -384,  1451,  1435,   564,   565,  1130,   645,
    1454,  1416,   646,  1731,  2062,  2063,  1732,  1452,  1457,  2167,
    1754,  1251,    90,  1455,  1286,  1141,  1009,  1289,  2321,  1052,
    1755,  1458,    95,   937,  1471,  1756,  1275,   938,   958,  1465,
    1053,  1542,  2260,  -849,   939,   940,   647,  1472,  1209,  1210,
     648,  1467,  1211,  1212,  1522,  1320,  1320,  1320,  1320,  1320,
    2042,  2043,  2044,  2045,  2046,   953,   649,  1523,  1054,  2079,
    1170,  1530,  1731,  1172,  1621,  1732,  1230,  2386,   121,  2007,
    1733,  2008,   650,  2038,  1531,  1494,  1039,  1622,  1734,  1625,
    2009,  1497,  2010,  1325,    50,  1500,  1603,  1502,  2007,  1627,
    2008,  1504,  1606,  1506,  2385,  2197,  1630,   658,  1604,  2009,
    1368,  2010,  1633,  1372,  1941,  1637,   651,  2231,  2179,   673,
    2232,  1663,   652,   566,  1715,  1634,   655,  1230,  1638,  1479,
     664,  1384,   694,  1495,  1664,  1719,   665,  1716,  1752,  1498,
    1718,  1230,  1230,  1501,  1889,  1503,  1501,  1501,   706,  1505,
    1434,  1507,  1623,  1949,  1910,  1916,  1873,  1405,  2172,  2173,
    2174,  1055,   717,  1917,  1471,  1631,  1950,  1655,  1642,  1656,
     994,   994,   994,  1601,  1883,  1551,  1552,  1951,   742,  1564,
    1565,  1566,  1232,  1996,  1997,  1953,   414,  1431,  1388,  2080,
     666,  1567,   978,   755,   118,  2085,   979,  1635,  1954,  2198,
    1568,   122,   703,   627,   628,  2233,   749,  1978,  1343,  1998,
     980,  1879,  1615,  1617,  1653,  2011,  2012,   680,  2013,  2014,
    1979,   688,  1999,  1569,   981,  2062,  2063,  1516,  1570,  1672,
    1453,  2021,   700,  1428,  2011,  2012,  1925,  2013,  2014,   978,
    2006,  1715,   715,   979,  2022,  1729,  1834,  1836,   978,  2015,
     627,   628,   979,   721,  2023,  2199,  1571,   980,   770,   627,
     628,   734,  1730,  2234,  2235,  2236,   978,    46,  2015,   739,
     979,   981,  1720,  2200,  1483,   752,  1723,   627,   628,  1471,
     981,  1715,  1461,   988,   980,  2201,   772,  2202,  2203,  1454,
    2204,  2016,  2024,  2205,  2025,  1454,  2039,   758,   981,  1804,
      74,  2059,  2026,  -585,  2017,  2179,   759,  1651,  2027,  2040,
    2016,  2090,  1516,  1572,  2060,   762,  1868,  1514,  1516,  1753,
    1344,  1345,  1516,  2017,  2091,  2095,   765,  1524,  1525,  1526,
     766,  2096,  1632,    96,  1876,  2097,  1731,   874,  2156,  1732,
     774,  2193,   879,  1754,  1733,   890,  1430,   885,  1167,  1543,
     893,  2157,  1734,  1755,  2194,  1685,   594,   595,  1756,  1471,
     778,  2216,  1516,   109,  2265,  1573,  2289,  1967,  1871,  1969,
    1970,   902,  2218,  1553,  2298,  2251,   779,  2266,   969,   685,
     806,  1974,   970,  1286,  2206,   814,  1682,  2299,   787,   627,
     628,  1981,  1887,  1983,   839,  1742,   587,  2059,  1747,   840,
     601,  1767,   843,  1780,  1893,  1786,  1689,  1790,  1895,   603,
    2308,  2316,  2070,   787,   627,   628,  1813,  1814,  1230,  1471,
    2336,   845,   982,  1434,  2317,   601,   905,  1516,  1471,  1728,
     588,  2331,  2334,  2337,   603,  1715,  2356,   604,  2021,   610,
    2357,  2359,  2021,   929,  2397,  1219,  1219,  1219,  2361,  1219,
    1219,  2391, -1182,  1799,  1619,  2392,  1909,  2398,  2399,    25,
    1434,  1471,   604,  1560,    29,   605,   864,   775,  -230,  1219,
    1041,  2400,  1042,  2402,  2403,   596,  1167,  2062,  2063,   597,
     598,   599,   600,  1880,  1881,  1882,    47,    48,  2268,  2404,
     605,    25,   601,  1647,   640,  1649,    29,  1645,  1645,   602,
    1645,   603,   629,   865,   626,   627,   628,   866,   697,   873,
    1068,   958,  1068,  1230,   959,  1657,   601,  2421,    47,    48,
     554,  2441,   606,   632,  1561,   603,  2417,   629,  1597,   604,
    2422,   960,  1244,   962,  2442,  1245,  1246,  2447,  2448,   971,
      90,  2457,   961,   631,   988,   965,  1680,   606,  2406,   638,
      95,   642,   644,   604,   976,  1137,   986,   605,  1327,  2368,
    2369,  1693,  1006,   596,   795,  1695,  1015,   597,   598,   599,
     600,   685,    90,  1017,   607,  1189,  1190,  1019,  1193,  1021,
     601,   605,    95,  1028,  1721,  1034,  1722,   602,  1725,   603,
    1199,  1200,  1059,  1038,   414,   398,   121,  1062,  1064,   607,
     956,  1080,  1081,  1219,  1219,  1219,  1082,  1087,  1095,  1096,
    1123,  1794,  1150,  1257,   606,  1174,  1161,   604,   629,  1164,
    1180,  1165,  1224,  1177,  1188,  1194,  1217,  2291,   121,   555,
    1230,  1254,   583,  1808,  1290,   763,  1293,  1314,   606,  1972,
     150,   938,  -342,  1815,  1975,   605,  1315,   979,  1346,  1352,
    1119,  1353,  1822,  1375,  1373,  1414,  1258,  1985,  1423,  1083,
    1383,  1397,  1259,  1398,  1399,  1400,   607,  1401,  1402,  2081,
     810,  1411,   150,  1844,  1417,  -928,  1432,  1419,  2083,  1987,
     822,  1433,   414,  1437,  1438,  1989,  1855,  1443,  1260,  1991,
     607,  1442,  1450,  1091,  1466,  2070,  2325,  1479,  1456,  1469,
    1470,  1474,   606,  1473,  1475,  1657,  1476,  1484,  1657,  1657,
    1657,  1486,  1261,  1493,  1262,  1496,  1508,  1509,  1884,   971,
    1510,  1511,  1512,  1513,  1516,  1517,  1532,  2126,  1533,  1535,
    1518,  1596,   867,   868,   869,   870,   872,  1536,  1537,  1539,
    1540,  1545,   908,  1550,  1588,  1591,  2366,  1263,  1597,  1602,
     697,  1607,  1264,  1610,   607,  1611,  1265,  1612,  1620,   366,
    1266,   396,  1626,  1267,   971,  1643,  1652,  1666,  2384,  1091,
    1918,  1667,  1660,  1665,  1668,  1429,  1690,  1699,  1717,  1679,
    1819,  1802,  1801,  1821,  1803,  1268,  1837,  1075,  1838,   931,
     933,   934,  1839,   935,  1847,  1850,  1840,  1841,  1868,  1269,
     936,  1863,  1869,  1865,  1888,  1270,  2219,  1890,  -494,  1905,
    2161,  1901,  1902,  2384,   810,   937,  1903,  1919,  1920,   938,
    2164,  1960,  1961,  1927,   775,  1946,   939,   940,    13,    14,
     775,    15,    16,   942,  1943,   944,    20,  1926,   946,   947,
     948,   949,   950,  1944,    23,  1947,  1977,   953,  1948,    27,
    1955,  1958,    30,  1959,  1965,  2122,  1014,  1964,  1968,  1971,
      37,  1993,    38,  1719,    40,  1720,  1980,  1982,  2134,  1984,
    1994,  1024,  2041,  2137,  2284,  2285,  2138,  1995,  2000,  2001,
    2002,  2003,  2005,  2028,  2033,   624,  2145,    59,  2146,   625,
    2147,   737,  2148,  -381,  2048,   626,   627,   628,    70,  1045,
    2049,  1445,  2061,  2069,   596,  2066,  1061,   601,   597,   598,
     599,   600,  1065,  1066,  2072,  2078,   603,  2073,  2074,   737,
    2075,   601,    85,  2076,  2077,  2088,   737,  2094,   602,  2129,
     603,  2109,  2111,  2130,   796,    93,  2152,  2153,  2154,  1219,
    2158,  2159,  -224,  2166,   604,  2183,  2196,  2209,  2053,  1855,
    1855,  1855,  2191,   102,  2211,  2210,  2212,  1122,   604,   104,
    -840,  1855,  2213,  2215,  2267,  2217,  2320,   108,  2323,   110,
    2238,   112,   605,   114,  2256,  2244,  2252,  2257,  2259,   786,
     119,  2263,  2269,  2270,  2277,  2301,   605,  2279,   673,   787,
     627,   628,  2280,  2281,  2282,  2283,  2286,   130,   131,  2287,
    2293,   601,  2297,  2307,  2302,  2304,  2093,  2305,  2335,   629,
     603,  2332,  2347,  2349,  2355,   143,  2358,  2360,  2367,  2373,
    1219,  2380,   593,   414,  2371,  2364,  2381,  2107,  2393,   606,
    1181,  1182,  2401,  2390,  2423,  2407,   155,  2415,   604,   156,
    1693,  2419,   918,   606,  1884,  2428,  2115,  2443,  2444,  2445,
    2456,   567,  2438,  1544,  1250,  1255,  2125,  2112,  2034,  1820,
     971,  1489,  2131,  1725,  1427,  1333,   605,  1823,   910,  1334,
     596,  2136,  2258,  2035,   597,   598,   599,   600,   922,   919,
    2142,   607,  1035,  1563,  1848,  1287,  2261,   601,  2169,  1288,
    2253,  1219,  2055,   937,   602,   607,   603,   938,  1794,  2162,
    2047,  1706,  1464,   629,   939,   940,   737,  2208,  1942,  2110,
     941,   942,  1257,   944,  1688,  2222,   946,   947,   948,   949,
     950,  2155,  2132,   606,   604,   953,  1393,  1624,  1294,  1295,
    1296,  1297,  1298,  1299,  1300,  1301,  1302,  1303,  1304,  1305,
    1306,  1307,  1308,  1309,  1310,  1311,  1312,  1376,  1844,  1911,
    1639,  1422,   605,   810,  1912,  1258,   429,  1855,  1328,  1855,
    1855,  1855,  1855,  1855,  1855,  1335,  2071,  1337,  2455,  2084,
     776,  1036,   589,   590,  1629,   607,  1659,  2318,   591,   592,
    1140,  1382,  1347,  1874,  1349,  1875,  1408,  1260,  1436,   414,
     999,  2189,  1482,  1169,  1002,  1001,  2290,  1644,  1071,    13,
      14,  1641,    15,    16,  2188,  2410,  1003,    20,   872,   606,
    1004,  1261,  2113,  1262,  1378,    23,  1090,  1219,  2310,  1148,
      27,  1367,  1366,    30,  2394,  2082,   803,  2221,  1961,  1121,
    1045,    37,  1421,    38,  1219,    40,  2319,  1127,  1128,  1386,
    1684,  2343,  1134,  1377,  2351,  2108,  1263,  2411,  2427,  2451,
    2449,  1264,  2296,  1956,  1705,  1265,   937,   833,    59,  1266,
     938,   607,  1267,  2120,  1855,  1088,  1008,   939,   940,    70,
    1090,  2086,  1671,   941,   942,   724,   944,  2121,  1162,   946,
     947,   948,   949,   950,  1268,   676,   952,  1800,   953,   954,
    2272,  1986,  1990,    85,  1973,  1992,  1976,  1988,  1269,  2141,
    2300,   815,   815,  2139,  1270,  1515,    93,  1184,  1534,  1187,
    2115,  2149,  1541,     0,  1446,  1538,     0,     0,     0,     0,
       0,     0,     0,   937,   102,     0,     0,   938,   737,   737,
     104,     0,     0,  1460,   939,   940,     0,  1231,   108,     0,
     110,   942,   112, -1183,   114,     0, -1183, -1183, -1183, -1183,
   -1183,   119,     0,     0,     0,   953,   872,  1481,   822,     0,
       0,  1557,     0,     0,     0,     0,   596,  2312,   130,   131,
     597,   598,   599,   600,     0,     0,     0,  1089,     0,  1089,
       0,     0,     0,   601,     0,     0,   143,     0,     0,     0,
     602,     0,   603,  2333,     0,     0,     0,     0,     0,     0,
       0,     0,  2341,  2344,     0,     0,     0,   155,     0,     0,
     156,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     604,  1527,     0,     0,  1319,  1319,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1808,  1808,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   605,     0,
     737,   737,     0,     0,     0,     0,     0,     0,     0,     0,
     368,     0,     0,     0,     0,     0,   374,     0,     0,  1559,
       0,  2344,     0,  2395,     0,     0,   381,  1231,     0,   383,
       0,  1592,   386,     0,     0,   414,     0,     0,     0,   392,
       0,     0,     0,   399,     0,     0,     0,   402,     0,     0,
    1387,     0,     0,     0,     0,   606,     0,     0,     0,  1599,
       0,     0,     0,     0,     0,   421,     0,     0,     0,   425,
     426,  1605,   971,  2429,     0,   431,   432,     0,  2430,     0,
       0,   437,   438,     0,   439,   440,   441,   442,   737,   443,
       0,  2430,     0,  2450,  2453,     0,     0,     0,   452,     0,
       0,     0,     0,   456,     0,   458,  2453,   607,     0,   461,
       0,     0,     0,   465,     0,   467,     0,     0,     0,     0,
    1628,  1024,   473,     0,     0,     0,   477,     0,     0,     0,
     480,     0,   482,     0,     0,  1640,     0,     0,     0,   490,
     492,     0,  1648,   494,   495,     0,     0,     0,     0,   501,
       0,   502,   872,     0,  2177,   506,  1445,     0,  1658,   596,
    1661,     0,     0,   597,   598,   599,   600,     0,     0,     0,
       0,     0,     0,   872,     0,     0,   601,     0,  1090,     0,
       0,     0,   533,   602,   535,   603,  1676,     0,     0,     0,
    1708,     0,     0,     0,     0,   596,     0,  1687,     0,   597,
     598,   599,   600,     0,     0,     0,     0,     0,     0,     0,
    1701,     0,   601,   604,     0,  1707,     0,  1713,     0,   602,
       0,   603,     0,  1041,     0,  2375,     0,     0,   596,     0,
       0,     0,   597,   598,   599,   600,     0,     0,     0,     0,
       0,   605,     0,     0,     0,   601,     0,     0,     0,   604,
    1827,     0,   602,     0,   603,   596,     0,     0,  2036,   597,
     598,   599,   600,   596,     0,     0,     0,   597,   598,   599,
     600,     0,   601,     0,     0,     0,     0,   605,   414,   602,
     601,   603,   604,     0,     0,     0,     0,   602,     0,   603,
       0,     0,     0,     0,     0,     0,  1562,     0,   606,     0,
       0,  1828,     0,     0,     0,     0,     0,     0,     0,   604,
     605,     0,     0,     0,   414,     0,     0,   604,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   606,     0,     0,   605,     0,     0,
       0,     0,  1872,   810,  1328,   605,  2273,   414,     0,     0,
     607,   596,     0,     0,     0,   597,   598,   599,   600,     0,
     737,     0,     0,     0,     0,     0,     0,   606,   601,     0,
       0,     0,     0,  1892,   414,   602,  1894,   603,     0,     0,
       0,     0,   414,     0,  1898,   955,   607,     0,     0,     0,
       0,     0,     0,     0,   606,   709,     0,     0,     0,     0,
       0,     0,   606,     0,     0,   604,     0,     0,     0,     0,
       0,     0,     0,     0,   821,     0,  1921,   596,  1924,   607,
       0,   597,   598,   599,   600,     0,  1071,     0,  1071,     0,
       0,     0,     0,   605,   601,     0,     0,     0,     0,     0,
       0,   602,     0,   603,     0,     0,   607,  1090,  1090,     0,
       0,     0,     0,     0,   607,     0,     0,  1673,     0,     0,
       0,     0,     0,   737,     0,  1683,     0,     0,  1134,     0,
     414,   604,     0,     0,     0,     0,     0,   937,     0,  1677,
     796,   938,   596,     0,  1090,  1090,     0,     0,   939,   940,
     606,     0,     0,  1678,   941,   942,   943,   944,   835,   605,
     946,   947,   948,   949,   950,   951,   737,   952,     0,   953,
     954,     0,     0,  1749,     0,     0,     0,     0,     0,     0,
       0,     0,   737,   737,   737,     0,   737,   737,     0,     0,
     737,     0,     0,     0,  1115,     0,   414,     0,   955,     0,
       0,     0,   607,     0,  1231,     0,   737,     0,     0,  1090,
    1090,  1090,     0,  1134,  1134,     0,   606,  2029,  2030,     0,
       0,     0,     0,   821,     0,  2037,   596,     0,     0,     0,
     597,   598,   599,   600,   596,     0,     0,     0,   597,   598,
     599,   600,     0,   601,     0,   955,     0,     0,     0,  1846,
     602,   601,   603,     0,     0,     0,     0,   955,   602,   937,
     603,  1166,     0,   938,   596,     0,  2068,     0,   607,     0,
     939,   940,  1599,     0,     0,     0,   941,   942,   943,   944,
     604,   737,   946,   947,   948,   949,   950,   951,   604,   952,
       0,   953,   954,     0,  2123,     0,     0,  2087,     0,     0,
       0,     0,   955,   955,   955,   955,  2092,   955,   605,     0,
       0,     0,     0,     0,     0,     0,   605,     0,     0,     0,
       0,     0,     0,  2102,  2103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     737,   737,   737,     0,     0,   414,     0,     0,     0,     0,
    1701,     0,     0,   414,     0,     0,     0,     0,   822,     0,
       0,     0,     0,     0,     0,   606,   955,  2133,   955,   955,
     955,   955,     0,   606,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2143,  1023,  2144,     0,   596,     0,  1090,
       0,   597,   598,   599,   600,     0,     0,     0,     0,  1445,
       0,     0,   596,     0,   601,     0,   597,   598,   599,   600,
       0,   602,     0,   603,     0,     0,     0,   607,     0,   601,
       0,     0,     0,     0,     0,   607,   602,   955,   603,     0,
       0,     0,     0,     0,     0,     0,     0,  1675,     0,     0,
     596,   604,     0,     0,   597,   598,   599,   600,     0,   955,
       0,     0,     0,     0,     0,     0,   604,   601,     0,   955,
       0,     0,     0,     0,   602,     0,   603,     0,     0,   605,
       0,     0,     0,     0,  2176,     0,     0,     0,     0,  2178,
     955,     0,     0,     0,   605,     0,     0,     0,     0,     0,
    2187,  1898,     0,     0,   604,  2192,   955,     0,     0,     0,
     955,   955,     0,     0,     0,  2195,   414,     0,     0,     0,
    2207,  1319,  1319,  1319,  1319,  1319,     0,     0,     0,     0,
    1700,   414,   605,   596,     0,     0,   606,   597,   598,   599,
     600,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     601,   606,     0,     0,     0,     0,     0,   602,     0,   603,
       0,     0,     0,     0,     0,     0,     0,   955,     0,   414,
       0,  1231,  1559,     0,  1276,   596,     0,  1387,     0,   597,
     991,   599,   600,     0,     0,     0,     0,   604,   607,   606,
       0,     0,   601,     0,     0,     0,     0,     0,     0,   602,
       0,   603,     0,   607,     0,     0,     0,  2274,     0,     0,
    2105,     0,     0,     0,     0,   605,     0,     0,     0,     0,
       0,     0,   872,     0,     0,     0,   955,   955,     0,   604,
       0,   796,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   607,  1090,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   414,     0,     0,     0,     0,   605,     0,     0,
       0,     0,  2140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   606,     0,  1356,  2309,  2178,     0,     0,  2311,
       0,  2315,     0,     0,     0,     0,   737,  2151,     0,     0,
       0,     0,     0,     0,   414,     0,     0,  2327,  2328,  2330,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2340,
       0,     0,     0,     0,   606,  2342,     0,     0,     0,     0,
       0,     0,     0,     0,   607,     0,     0,  2274,     0,     0,
       0,     0,     0,     0,  1846,     0,     0,     0,     0,   955,
     955,   955,   955,   955,   955,   955,   955,   955,   955,   955,
     955,   955,   955,   955,   955,   955,   955,   955,     0,  2374,
    2376,     0,     0,     0,  2182,     0,   607,   737,     0,  2185,
       0,   822,     0,   955,  2388,     0,  2389,     0,     0,     0,
     955,     0,   955,     0,     0,     0,  1923,     0,     0,   596,
       0,     0,   955,   597,   598,   599,   600,     0,     0,     0,
       0,     0,     0,     0,   872,     0,   601,     0,  2376,     0,
       0,     0,  2412,   602,     0,   603,  2416,     0,  1713,     0,
       0,     0,     0,   955,     0,     0,     0,     0,     0,   937,
    1713,  2426,  2412,   938,   596,     0,     0,   737,   737,     0,
     939,   940,     0,   604,     0,     0,   941,   942,   943,   944,
     945,     0,   946,   947,   948,   949,   950,   951,     0,   952,
       0,   953,   954,     0,     0,     0,     0,     0,     0,     0,
       0,   605,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   955,     0,     0,     0,     0,     0,  1090,     0,     0,
       0,  1090,     0,     0,     0,   955,     0,     0,   414,     0,
       0,     0,  1097,     0,     0,     0,  1098,   596,     0,     0,
       0,     0,     0,  1099,  1100,     0,   955,  1549,   606,  1101,
    1102,  1103,  1104,     0,     0,  1105,  1106,  1107,  1108,  1109,
    1110,  1111,  1112,     0,  1113,  1114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1090,   737,  1090,  1090,  1090,     0,     0,
       0,     0,   955,   937,     0,     0,  1227,   938,   596,     0,
     607,   737,     0,     0,   939,   940,     0,     0,     0,     0,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,   955,   953,   954,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1090,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   937,
       0,     0,  1228,   938,   596,     0,     0,   955,  1090,  1090,
     939,   940,  1090,     0,   955,     0,   941,   942,   943,   944,
     955,     0,   946,   947,   948,   949,   950,   951,     0,   952,
       0,   953,   954,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   955,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1090,     0,   955,     0,     0,     0,     0,
       0,     0,     0,   955,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   955,     0,     0,   955,     0,     0,     0,
       0,   937,     0,     0,  1229,   938,   596,     0,     0,     0,
       0,   955,   939,   940,     0,     0,     0,     0,   941,   942,
     943,   944,   955,     0,   946,   947,   948,   949,   950,   951,
       0,   952,     0,   953,   954,   937,   955,     0,     0,   938,
     596,     0,   955,     0,     0,     0,   939,   940,   955,     0,
       0,  1292,   941,   942,   943,   944,     0,     0,   946,   947,
     948,   949,   950,   951,     0,   952,   937,   953,   954,     0,
     938,   596,     0,     0,     0,     0,     0,   939,   940,     0,
       0,     0,  1371,   941,   942,   943,   944,     0,     0,   946,
     947,   948,   949,   950,   951,     0,   952,     0,   953,   954,
     937,     0,  1379,     0,   938,   596,     0,     0,     0,     0,
       0,   939,   940,     0,     0,     0,     0,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,     0,
     952,     0,   953,   954,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   370,   371,   372,   373,     0,   375,     0,   376,
       0,   378,   379,   955,   380,     0,     0,     0,   382,     0,
     384,   385,     0,     0,   387,   388,   389,     0,   391,     0,
     393,   394,     0,     0,   401,     0,     0,     0,     0,   404,
     405,   406,   407,   408,   409,   410,   411,     0,   412,   413,
       0,     0,   418,   419,   420,     0,   422,   955,   424,     0,
       0,   427,   428,     0,     0,     0,     0,     0,     0,   435,
     436,     0,     0,     0,     0,     0,     0,   955,     0,   955,
     444,     0,   446,   955,   447,   448,     0,     0,     0,   453,
     454,   455,     0,     0,   457,     0,     0,   459,   460,     0,
     462,   463,   464,     0,     0,     0,   955,   469,   470,   955,
       0,   472,     0,   474,   475,   476,     0,   478,   479,     0,
       0,   481,     0,   483,   484,   485,   486,   487,   488,  1115,
       0,     0,     0,     0,     0,   496,   497,   498,     0,     0,
       0,     0,   503,   504,   505,     0,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,     0,   534,     0,   536,     0,   537,     0,   538,
     539,   540,   541,   542,   543,   544,   545,   546,     0,     0,
       0,     0,     0,   937,     0,  1394,     0,   938,   596,     0,
       0,     0,     0,     0,   939,   940,     0,     0,     0,     0,
     941,   942,   943,   944,   955,   955,   946,   947,   948,   949,
     950,   951,   955,   952,     0,   953,   954,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   623,
       0,     0,   636,   937,   639,     0,     0,   938,   596,     0,
       0,     0,     0,   955,   939,   940,     0,     0,     0,  1406,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,   955,   952,   937,   953,   954,   955,   938,   596,
       0,     0,     0,     0,     0,   939,   940,   955,   955,     0,
    1409,   941,   942,   943,   944,     0,     0,   946,   947,   948,
     949,   950,   951,     0,   952,     0,   953,   954,     0,     0,
       0,     0,     0,     0,     0,   937,     0,     0,   955,   938,
     596,     0,     0,     0,     0,     0,   939,   940,   955,   955,
       0,  1410,   941,   942,   943,   944,     0,     0,   946,   947,
     948,   949,   950,   951,     0,   952,     0,   953,   954,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   955,     0,   955,     0,     0,     0,     0,     0,     0,
     937,     0,   955,     0,   938,   596,     0,   955,     0,     0,
     955,   939,   940,     0,     0,     0,  1444,   941,   942,   943,
     944,     0,   955,   946,   947,   948,   949,   950,   951,     0,
     952,   937,   953,   954,     0,   938,   596,     0,     0,     0,
       0,     0,   939,   940,     0,     0,     0,  1491,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
       0,   952,     0,   953,   954,     0,     0,   937,     0,     0,
       0,   938,   596,     0,     0,     0,     0,     0,   939,   940,
       0,     0,     0,  1492,   941,   942,   943,   944,     0,   955,
     946,   947,   948,   949,   950,   951,     0,   952,     0,   953,
     954,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   955,     0,   955,     0,     0,     0,
     955,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   955,   955,     0,   955,     0,   937,     0,     0,
       0,   938,   596,     0,     0,   955,     0,   955,   939,   940,
       0,     0,     0,  1609,   941,   942,   943,   944,     0,     0,
     946,   947,   948,   949,   950,   951,     0,   952,     0,   953,
     954,     0,     0,     0,     0,     0,     0,     0,     0,   955,
       0,   955,     0,     0,     0,     0,     0,     0,     0,     0,
       9,     0,     0,   955,   955,   927,   928,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   955,     0,     0,
       0,   955,     0,     0,     0,     0,     0,    11,    12,    13,
      14,   955,    15,    16,    17,    18,    19,    20,     0,     0,
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
     197,     0,     0,     0,   198,   199,   200,   201,   202,   937,
     203,   204,     0,   938,   596,     0,     0,     0,     0,     0,
     939,   940,     0,     0,     0,  1866,   941,   942,   943,   944,
       0,     0,   946,   947,   948,   949,   950,   951,     0,   952,
       0,   953,   954,   937,     0,  1677,     0,   938,   596,     0,
       0,     0,     0,     0,   939,   940,     0,     0,     0,     0,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,   937,   953,   954,     0,   938,   596,
       0,     0,     0,     0,     0,   939,   940,     0,     0,     0,
    1904,   941,   942,   943,   944,     0,     0,   946,   947,   948,
     949,   950,   951,     0,   952,     0,   953,   954,   937,     0,
    1922,     0,   938,   596,     0,     0,     0,     0,     0,   939,
     940,     0,     0,     0,     0,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,   937,
     953,   954,     0,   938,   596,     0,     0,     0,     0,     0,
     939,   940,     0,     0,     0,  1952,   941,   942,   943,   944,
       0,     0,   946,   947,   948,   949,   950,   951,     0,   952,
       0,   953,   954,   937,     0,  2089,     0,   938,   596,     0,
       0,     0,     0,     0,   939,   940,     0,     0,     0,     0,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,     0,   953,   954,   937,     0,  2104,
       0,   938,   596,     0,     0,     0,     0,     0,   939,   940,
       0,     0,     0,     0,   941,   942,   943,   944,     0,     0,
     946,   947,   948,   949,   950,   951,     0,   952,   937,   953,
     954,     0,   938,   596,     0,     0,     0,     0,     0,   939,
     940,     0,     0,     0,  2160,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,   937,
     953,   954,     0,   938,   596,     0,     0,     0,     0,     0,
     939,   940,     0,     0,     0,  2175,   941,   942,   943,   944,
       0,     0,   946,   947,   948,   949,   950,   951,     0,   952,
     937,   953,   954,  2186,   938,   596,     0,     0,     0,     0,
       0,   939,   940,     0,     0,     0,     0,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,     0,
     952,   937,   953,   954,     0,   938,   596,     0,     0,     0,
       0,     0,   939,   940,     0,     0,     0,  2190,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
       0,   952,   937,   953,   954,     0,   938,   596,     0,     0,
       0,     0,     0,   939,   940,     0,     0,     0,  2249,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,   937,   953,   954,     0,   938,   596,     0,
       0,     0,     0,     0,   939,   940,     0,     0,     0,  2250,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,   937,   953,   954,  2264,   938,   596,
       0,     0,     0,     0,     0,   939,   940,     0,     0,     0,
       0,   941,   942,   943,   944,     0,     0,   946,   947,   948,
     949,   950,   951,     0,   952,   937,   953,   954,     0,   938,
     596,     0,     0,     0,     0,     0,   939,   940,     0,     0,
       0,  2271,   941,   942,   943,   944,     0,     0,   946,   947,
     948,   949,   950,   951,     0,   952,   937,   953,   954,  2288,
     938,   596,     0,     0,     0,     0,     0,   939,   940,     0,
       0,     0,     0,   941,   942,   943,   944,     0,     0,   946,
     947,   948,   949,   950,   951,     0,   952,   937,   953,   954,
    2348,   938,   596,     0,     0,     0,     0,     0,   939,   940,
       0,     0,     0,     0,   941,   942,   943,   944,     0,     0,
     946,   947,   948,   949,   950,   951,     0,   952,   937,   953,
     954,     0,   938,   596,     0,     0,     0,     0,     0,   939,
     940,     0,     0,     0,  2350,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,   937,
     953,   954,     0,   938,   596,     0,     0,     0,     0,     0,
     939,   940,     0,     0,     0,  2362,   941,   942,   943,   944,
       0,     0,   946,   947,   948,   949,   950,   951,     0,   952,
     937,   953,   954,  2363,   938,   596,     0,     0,     0,     0,
       0,   939,   940,     0,     0,     0,     0,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,     0,
     952,   937,   953,   954,  2365,   938,   596,     0,     0,     0,
       0,     0,   939,   940,     0,     0,     0,     0,   941,   942,
     943,   944,     0,     0,   946,   947,   948,   949,   950,   951,
       0,   952,   937,   953,   954,     0,   938,   596,     0,     0,
       0,     0,     0,   939,   940,     0,     0,     0,  2370,   941,
     942,   943,   944,     0,     0,   946,   947,   948,   949,   950,
     951,     0,   952,   937,   953,   954,     0,   938,   596,     0,
       0,     0,     0,     0,   939,   940,     0,     0,     0,  2372,
     941,   942,   943,   944,     0,     0,   946,   947,   948,   949,
     950,   951,     0,   952,   937,   953,   954,  2405,   938,   596,
       0,     0,     0,     0,     0,   939,   940,     0,     0,     0,
       0,   941,   942,   943,   944,     0,     0,   946,   947,   948,
     949,   950,   951,     0,   952,     0,   953,   954,   937,     0,
    2420,     0,   938,   596,     0,     0,     0,     0,     0,   939,
     940,     0,     0,     0,     0,   941,   942,   943,   944,     0,
       0,   946,   947,   948,   949,   950,   951,     0,   952,   937,
     953,   954,     0,   938,   596,     0,     0,     0,     0,     0,
     939,   940,     0,     0,     0,     0,   941,   942,   943,   944,
       0,     0,   946,   947,   948,   949,   950,   951,     0,   952,
     937,   953,   954,     0,   938,     0,     0,     0,     0,     0,
       0,   939,   940,     0,     0,     0,     0,   941,   942,   943,
     944,     0,     0,   946,   947,   948,   949,   950,   951,     0,
     952,     0,   953,   954
};

static const yytype_int16 yycheck[] =
{
      50,   380,   371,   475,   385,   368,   485,   486,   487,   488,
      62,    63,   619,  1123,   739,   478,   752,    69,   873,   911,
     253,   533,  1017,  1284,   257,   228,   229,   623,   960,   961,
     634,   234,  1433,  1535,   961,  1537,  1588,   206,  1466,  1470,
     253,  1313,   464,   645,   257,  1013,    98,   459,   394,   598,
    1558,  1140,  1057,  1957,   644,   645,   732,    76,   404,   865,
     406,  1532,    63,   426,   423,   411,   412,   413,   118,  1564,
    1919,   435,   122,   419,  1564,  1284,   422,   833,   424,   442,
      99,    15,     8,  1847,   833,    94,  1502,  1584,  1575,     7,
     685,   460,  1589,   456,  1346,   644,   645,   116,   461,  1502,
     381,   505,   465,   116,   467,  1536,   701,   175,    71,  1502,
    1502,   662,   472,  1502,  1502,     5,  1502,   480,     7,   967,
     991,    15,  1630,   182,     7,   144,   191,     8,    92,   492,
     129,   494,    37,     0,     1,     8,    47,    41,   501,     8,
     399,  2407,   208,   208,   182,     5,     8,  1152,   129,   191,
     400,   203,   194,  2419,    15,    16,    17,     8,  1013,     8,
       8,    21,     5,     3,    37,    21,     8,   166,    37,   221,
    1165,    20,   238,  1500,     5,  1502,     7,  1504,    20,  1506,
       8,  1036,   169,    15,   788,   149,    26,    15,    15,    37,
      15,   172,    15,   148,    37,  1666,  1667,  1668,   116,     8,
       8,     3,    15,     8,   626,  1500,     3,  1502,   630,  1504,
      21,  1506,    20,   472,   427,   637,    18,   282,   129,     8,
     285,   230,     8,   116,   129,   180,  1500,   116,  1502,    26,
    1504,   464,   636,   116,    20,   639,   831,   201,     8,   129,
       8,     8,   455,   622,   257,   208,   797,   842,   129,   462,
      20,   464,    20,   321,   116,   149,   315,  1529,  1500,   318,
    1502,   511,  1504,   513,   859,   116,   177,   116,   129,   129,
     520,   521,   522,   129,   116,   284,   526,   527,   528,   529,
     318,   531,   532,   150,  2048,  1177,   295,   253,   149,   752,
       8,   257,     8,  1852,  1853,   282,   577,   129,   129,  1851,
     679,   129,   129,   898,   129,   209,   129,   116,   116,  1419,
     129,   116,   246,    64,   366,   367,   129,   912,   129,   129,
     372,   373,   374,   375,   228,   377,   378,   116,   254,   381,
     116,   383,   384,   385,   386,   681,   149,   389,     8,   257,
     392,    15,   394,   806,  2193,  1277,   116,   399,   116,   116,
     402,  1848,   404,   713,   406,  1607,  1565,  1566,   410,   411,
     412,   413,    15,  1850,  1780,   787,   962,   419,   257,   421,
     422,   975,   424,   977,   257,  2128,     8,  1780,   430,   431,
     984,   740,   786,     8,   788,   437,   438,  1780,  1780,   441,
     257,  1780,  1780,   626,  1780,   257,   448,   630,   116,   451,
     116,   991,  2155,  1079,   637,  1000,   257,    15,   257,   410,
    1005,   463,   776,   626,   466,   257,  1411,   630,    15,  1175,
     472,   473,   474,   475,   637,   477,   478,  1176,  1164,   642,
    1278,   481,   484,   485,   486,   487,   488,  1432,   490,   799,
    1767,   493,   991,   495,   496,     8,   116,   499,   257,   257,
     502,  1046,   257,  1780,   506,   129,  2360,    15,   191,  1786,
       8,     8,  1467,  1790,  1071,   668,  1555,  1556,   257,   828,
    1318,   257,  1767,    21,   381,     8,   129,     8,    23,    15,
    1351,  1352,  1353,   535,   116,  1780,   536,   257,    15,   257,
     257,  1786,    37,  1767,   169,  1790,   908,   547,   548,   549,
    2349,   191,     8,  2062,  2063,   557,  1780,  2059,   560,   561,
     562,   563,  1786,   128,    15,   565,   568,   569,   208,  1947,
     572,   573,   574,   575,   576,  1767,   128,  1958,   580,   581,
     909,  2002,  1804,   208,    15,   554,   555,     7,  1780,   257,
    1144,   257,   157,  1391,  1786,    15,  2041,   566,  2397,   282,
     800,  2041,    64,   116,   787,   157,   978,   979,   980,   981,
     982,   266,  1530,  2050,   191,     8,     8,    15,     5,   116,
     257,   129,    16,    17,   787,   147,   148,   956,    15,   748,
     116,  1842,   287,   116,   129,   116,  1847,   257,     5,   129,
       8,    43,     9,   129,   646,   647,   648,   649,   650,   651,
     652,     8,   217,   655,   654,    23,     3,   282,   180,   149,
     116,   663,  2083,     8,  2166,    67,     3,   129,     8,    37,
      37,     7,   672,     5,    21,   257,    21,     9,    15,   681,
      82,    21,   684,  1842,   686,    87,    88,   149,    18,     8,
       8,   844,    94,     8,    23,   848,    26,    15,    92,  1028,
     853,   864,   865,   856,   857,    37,   563,   709,    37,  1038,
     873,   288,     8,  1258,     3,    84,   573,   574,   575,   576,
       7,     8,   299,   116,   116,  1530,    15,  2443,  2444,     3,
       8,  1276,   734,  2154,   736,     8,     5,   739,     8,  1291,
    2456,    15,  1417,    21,   257,     8,    15,  1433,  1434,   749,
     752,  1291,  1508,  1509,  1510,   149,  1512,  1513,    21,   761,
     257,     3,   762,     8,   917,     8,   919,     3,   770,   769,
     772,   257,     7,    15,   257,   777,   257,   779,    21,    15,
     782,   147,   148,     8,  1338,  1339,  1340,  1341,  1342,  1610,
    1611,  1612,  1291,   795,  1293,   978,   979,   980,   981,   982,
    2258,   257,     7,     8,   806,  1603,   663,   201,     5,     3,
     812,  1351,  1352,  1353,   180,   978,   979,   980,   981,   982,
       8,    15,   191,   986,   987,   827,   228,     8,   830,   686,
       8,  2283,     8,    21,   836,   835,  2217,  2048,     8,   208,
      21,    63,     8,    21,  1642,    21,    68,  1047,     8,  1535,
    1013,  1537,  1351,  1352,  1353,    21,     8,   259,  1058,  2280,
    1405,    58,     8,     5,   257,   257,   866,     5,    90,    91,
       5,     9,     7,  1036,    16,    17,  2297,     8,    16,    17,
      22,   191,    24,    21,     8,    23,   888,   889,    15,    86,
      21,    33,     8,    35,    15,    37,   265,    21,   208,    37,
    2281,   303,   904,     3,     8,    21,     7,     8,     8,     8,
       8,  1074,     8,   282,    16,    17,   285,    21,     8,    21,
     289,   890,   144,    21,   926,   782,     8,   927,  2279,   126,
     299,    21,   154,     5,     8,   304,   905,     9,     3,    21,
     137,  1250,  2164,     8,    16,    17,     8,    21,   314,   315,
       8,  1151,   318,   319,     8,  1837,  1838,  1839,  1840,  1841,
    1837,  1838,  1839,  1840,  1841,    37,     8,    21,   165,  1887,
     827,     8,   282,   830,     8,   285,     8,  2358,   200,    22,
     290,    24,     8,  1825,    21,  1185,     8,    21,   298,    21,
      33,  1191,    35,     8,    95,  1195,  1325,  1197,    22,    21,
      24,  1201,  1331,  1203,  2355,    41,    21,  1009,  1327,    33,
    1010,    35,     8,  1015,  1689,     8,     8,   159,  2078,  1021,
     162,     8,     8,   124,     8,    21,     8,     8,    21,  1715,
      15,     8,  1034,  1186,    21,    71,    15,    21,    84,  1192,
      21,     8,     8,  1196,    21,  1198,  1199,  1200,     7,  1202,
       8,  1204,  1371,     8,    21,    21,  1602,  1059,  2064,  2065,
    2066,   258,  1064,    21,     8,  1384,    21,  1412,  1397,  1414,
    1610,  1611,  1612,  1871,  1619,     7,     8,    21,  1080,    15,
      16,    17,  1887,   316,   317,     8,   129,  1087,  1893,  1887,
     149,    27,     5,  1095,   195,  1893,     9,  1895,    21,   135,
      36,   202,   149,    16,    17,   247,     8,     8,    21,     8,
      23,  1610,  1611,  1612,  1410,   158,   159,    15,   161,   162,
      21,    15,    21,    59,    37,    16,    17,     8,    64,  1442,
    1130,     8,    15,   169,   158,   159,  1681,   161,   162,     5,
      21,     8,    15,     9,    21,   191,  1565,  1566,     5,   192,
      16,    17,     9,    15,    21,   191,    92,    23,     8,    16,
      17,    15,   208,   305,   306,   307,     5,    89,   192,    15,
       9,    37,   208,   209,  1174,    15,  1489,    16,    17,     8,
      37,     8,    21,  1346,    23,   221,    37,   223,   224,     8,
     226,   234,    21,   229,    21,     8,     8,    15,    37,  1528,
     122,     8,    21,     8,   247,  2265,    15,  1407,    21,    21,
     234,     8,     8,   149,    21,    15,    21,  1217,     8,   265,
     986,   987,     8,   247,    21,    21,    15,  1227,  1228,  1229,
      15,    21,  1385,   155,  1606,    21,   282,  1237,     8,   285,
      15,     8,  1242,   289,   290,   124,   282,  1247,     8,  1251,
    1252,    21,   298,   299,    21,  1455,   244,   245,   304,     8,
      15,    21,     8,   185,     8,   201,  2211,  1729,  1597,  1731,
    1732,     7,    21,  1275,     8,    21,    15,    21,     5,  1281,
      15,  1743,     9,  1285,   320,    15,  1449,    21,    15,    16,
      17,  1753,  1621,  1755,    15,  1495,   218,     8,  1498,    15,
      27,  1501,    15,  1503,  1633,  1505,  1459,  1507,  1637,    36,
      21,     8,  1869,    15,    16,    17,  1539,  1540,     8,     8,
       8,    15,  1876,     8,    21,    27,   124,     8,     8,  1492,
     252,    21,    21,    21,    36,     8,    21,    64,     8,   248,
      21,    21,     8,   239,     8,  1508,  1509,  1510,    21,  1512,
    1513,    21,    15,  1516,  1356,    21,  1652,    21,     8,    63,
       8,     8,    64,  2161,    68,    92,    15,  1530,     7,  1532,
       5,    21,     7,    21,    21,    10,     8,    16,    17,    14,
      15,    16,    17,  1610,  1611,  1612,    90,    91,  2186,    21,
      92,    63,    27,  1400,     5,  1402,    68,  1399,  1400,    34,
    1402,    36,   129,    15,    15,    16,    17,    15,  1410,    15,
    1412,     3,  1414,     8,    15,  1417,    27,     8,    90,    91,
     124,     8,   149,  1606,  1281,    36,    21,   129,     8,    64,
      21,   246,   335,    15,    21,   338,   339,  2439,  2440,   166,
     144,    21,   246,  1606,  1607,    21,  1448,   149,  2393,   255,
     154,   257,   258,    64,    26,  1457,     8,    92,     5,  2335,
    2336,  1463,     7,    10,    15,  1465,   240,    14,    15,    16,
      17,  1473,   144,    15,   201,   846,   847,    15,   849,     8,
      27,    92,   154,    15,  1484,     8,  1486,    34,  1490,    36,
     854,   855,   175,    15,   129,    15,   200,   149,     8,   201,
      15,     8,     8,  1666,  1667,  1668,    15,     8,     8,    26,
      15,  1511,     7,    44,   149,     8,    62,    64,   129,    15,
       8,    15,  1522,    21,   287,    15,     8,  2213,   200,   233,
       8,   213,     8,  1533,    15,   444,     8,    64,   149,  1739,
     244,     9,    21,  1545,  1744,    92,   129,     9,     8,     8,
    1550,     8,  1552,    67,    15,     8,    87,  1757,   129,   231,
      37,    15,    93,    15,    15,    15,   201,    15,    15,  1888,
     479,    15,   244,  1575,     8,     7,    15,    26,  1891,  1779,
     489,     7,   129,    21,    21,  1785,  1588,    18,   119,  1789,
     201,    21,    37,  2279,     7,  2152,  2282,  2283,    26,    15,
       7,    15,   149,     8,    15,  1607,    26,     8,  1610,  1611,
    1612,     8,   143,    21,   145,    21,    15,    15,  1620,   166,
      15,    15,    15,    15,     8,    21,    15,  1958,    15,    15,
      21,    21,   541,   542,   543,   544,   545,    15,    15,    15,
      15,    15,     5,    15,    15,    62,  2332,   178,     8,     7,
    1652,     8,   183,     8,   201,     8,   187,     8,   255,    15,
     191,    15,     7,   194,   166,    15,   239,    15,  2354,  2355,
    1672,    15,    21,    16,    15,   208,     8,     7,    15,    21,
      15,   315,   328,     7,   329,   216,   246,  1689,   246,   598,
     599,   600,   246,   602,     5,     8,   246,   246,    21,   230,
     609,    15,    21,    15,     8,   236,  2128,     7,    26,     8,
    2039,    21,    21,  2399,   623,     5,    21,    15,    21,     9,
    2049,  1723,  1724,     8,  1887,   255,    16,    17,    45,    46,
    1893,    48,    49,    23,    15,    25,    53,   173,    28,    29,
      30,    31,    32,    15,    61,     8,  1748,    37,     7,    66,
      21,    15,    69,    15,     8,  1955,   665,    18,    15,    15,
      77,    21,    79,    71,    81,   208,    15,    15,  1968,    15,
      21,   680,     8,  1973,  2203,  2204,  1976,    21,    21,    21,
      15,    15,    21,    21,    21,     5,  1986,   104,  1988,     9,
    1990,   427,  1992,    15,     5,    15,    16,    17,   115,   708,
      15,     7,     7,    20,    10,     9,   715,    27,    14,    15,
      16,    17,   721,   722,    21,    15,    36,    26,    21,   455,
      21,    27,   139,    21,    21,    21,   462,    15,    34,    18,
      36,    26,    26,     8,   470,   152,    21,    15,    15,  2002,
       7,    21,    15,    26,    64,     8,    15,    21,  1850,  1851,
    1852,  1853,   254,   170,    15,    21,     8,   766,    64,   176,
       7,  1863,   132,    21,  2183,     7,  2279,   184,  2281,   186,
      21,   188,    92,   190,     7,    37,    21,     7,    21,     5,
     197,    21,   255,    15,    15,    21,    92,    15,  1890,    15,
      16,    17,    15,    15,    15,    15,    15,   214,   215,    15,
      15,    27,     7,    21,     8,     8,  1906,     7,     7,   129,
      36,     8,    21,    15,     7,   232,     7,    15,    78,     8,
    2083,     7,   239,   129,   327,    21,     7,  1927,    15,   149,
     839,   840,    15,    21,     8,    17,   253,    21,    64,   256,
    1942,    17,   578,   149,  1946,    15,  1948,     7,     7,    15,
       7,   219,   128,  1252,   889,   897,  1958,  1944,  1822,  1550,
     166,  1178,  1964,  1965,  1083,     5,    92,  1554,   571,     9,
      10,  1971,  2161,  1823,    14,    15,    16,    17,   582,   579,
    1980,   201,   699,  1283,  1584,   926,  2166,    27,  2061,   926,
    2153,  2154,  1850,     5,    34,   201,    36,     9,  1998,  2041,
    1842,  1473,  1147,   129,    16,    17,   642,  2110,  1690,  1942,
      22,    23,    44,    25,  1457,  2130,    28,    29,    30,    31,
      32,  2021,  1965,   149,    64,    37,  1039,  1373,   937,   938,
     939,   940,   941,   942,   943,   944,   945,   946,   947,   948,
     949,   950,   951,   952,   953,   954,   955,  1019,  2050,  1663,
    1394,  1081,    92,   962,  1665,    87,    75,  2059,   967,  2061,
    2062,  2063,  2064,  2065,  2066,   974,  1871,   976,  2445,  1893,
     455,   700,   243,   243,  1380,   201,  1417,  2277,   243,   243,
     780,  1028,   991,  1603,   991,  1606,  1064,   119,  1095,   129,
     646,  2091,  1167,   826,   649,   648,  2212,  1398,   734,    45,
      46,  1396,    48,    49,  2090,  2397,   650,    53,  1017,   149,
     651,   143,  1946,   145,  1023,    61,   752,  2280,  2265,   795,
      66,  1009,  1007,    69,  2373,  1890,  2128,  2129,  2130,   765,
    1039,    77,  1080,    79,  2297,    81,  2278,   773,   774,  1034,
    1454,  2304,   778,  1021,  2316,  1929,   178,  2399,  2421,  2443,
    2441,   183,  2220,  1715,  1471,   187,     5,   496,   104,   191,
       9,   201,   194,  1949,  2166,   750,   655,    16,    17,   115,
     806,  1895,  1434,    22,    23,   408,    25,  1953,   814,    28,
      29,    30,    31,    32,   216,   375,    35,  1522,    37,    38,
    2193,  1767,  1786,   139,  1742,  1790,  1747,  1780,   230,  1978,
    2244,  2203,  2204,  1977,   236,  1217,   152,   843,  1237,   845,
    2212,  1998,  1247,    -1,  1123,  1242,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,   170,    -1,    -1,     9,   864,   865,
     176,    -1,    -1,  1142,    16,    17,    -1,   873,   184,    -1,
     186,    23,   188,    25,   190,    -1,    28,    29,    30,    31,
      32,   197,    -1,    -1,    -1,    37,  1165,  1166,  1167,    -1,
      -1,     5,    -1,    -1,    -1,    -1,    10,  2269,   214,   215,
      14,    15,    16,    17,    -1,    -1,    -1,  2279,    -1,  2281,
      -1,    -1,    -1,    27,    -1,    -1,   232,    -1,    -1,    -1,
      34,    -1,    36,  2293,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2302,  2305,    -1,    -1,    -1,   253,    -1,    -1,
     256,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,  1230,    -1,    -1,   960,   961,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2335,  2336,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,
     986,   987,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,  1278,
      -1,  2373,    -1,  2375,    -1,    -1,    28,  1013,    -1,    31,
      -1,  1290,    34,    -1,    -1,   129,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    49,    -1,    -1,
    1036,    -1,    -1,    -1,    -1,   149,    -1,    -1,    -1,  1318,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    71,
      72,  1330,   166,  2423,    -1,    77,    78,    -1,  2428,    -1,
      -1,    83,    84,    -1,    86,    87,    88,    89,  1074,    91,
      -1,  2441,    -1,  2443,  2444,    -1,    -1,    -1,   100,    -1,
      -1,    -1,    -1,   105,    -1,   107,  2456,   201,    -1,   111,
      -1,    -1,    -1,   115,    -1,   117,    -1,    -1,    -1,    -1,
    1379,  1380,   124,    -1,    -1,    -1,   128,    -1,    -1,    -1,
     132,    -1,   134,    -1,    -1,  1394,    -1,    -1,    -1,   141,
     142,    -1,  1401,   145,   146,    -1,    -1,    -1,    -1,   151,
      -1,   153,  1411,    -1,     5,   157,     7,    -1,  1417,    10,
    1419,    -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,  1432,    -1,    -1,    27,    -1,  1164,    -1,
      -1,    -1,   184,    34,   186,    36,  1445,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    10,    -1,  1456,    -1,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1469,    -1,    27,    64,    -1,  1474,    -1,  1476,    -1,    34,
      -1,    36,    -1,     5,    -1,    40,    -1,    -1,    10,    -1,
      -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    27,    -1,    -1,    -1,    64,
       5,    -1,    34,    -1,    36,    10,    -1,    -1,     5,    14,
      15,    16,    17,    10,    -1,    -1,    -1,    14,    15,    16,
      17,    -1,    27,    -1,    -1,    -1,    -1,    92,   129,    34,
      27,    36,    64,    -1,    -1,    -1,    -1,    34,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,  1282,    -1,   149,    -1,
      -1,  1560,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      92,    -1,    -1,    -1,   129,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,    -1,    -1,    92,    -1,    -1,
      -1,    -1,  1601,  1602,  1603,    92,     5,   129,    -1,    -1,
     201,    10,    -1,    -1,    -1,    14,    15,    16,    17,    -1,
    1346,    -1,    -1,    -1,    -1,    -1,    -1,   149,    27,    -1,
      -1,    -1,    -1,  1632,   129,    34,  1635,    36,    -1,    -1,
      -1,    -1,   129,    -1,  1643,   610,   201,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   397,    -1,    -1,    -1,    -1,
      -1,    -1,   149,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    -1,  1675,    10,  1677,   201,
      -1,    14,    15,    16,    17,    -1,  1412,    -1,  1414,    -1,
      -1,    -1,    -1,    92,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    36,    -1,    -1,   201,  1433,  1434,    -1,
      -1,    -1,    -1,    -1,   201,    -1,    -1,  1443,    -1,    -1,
      -1,    -1,    -1,  1449,    -1,  1451,    -1,    -1,  1454,    -1,
     129,    64,    -1,    -1,    -1,    -1,    -1,     5,    -1,     7,
    1466,     9,    10,    -1,  1470,  1471,    -1,    -1,    16,    17,
     149,    -1,    -1,    21,    22,    23,    24,    25,   500,    92,
      28,    29,    30,    31,    32,    33,  1492,    35,    -1,    37,
      38,    -1,    -1,  1499,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1508,  1509,  1510,    -1,  1512,  1513,    -1,    -1,
    1516,    -1,    -1,    -1,   759,    -1,   129,    -1,   763,    -1,
      -1,    -1,   201,    -1,  1530,    -1,  1532,    -1,    -1,  1535,
    1536,  1537,    -1,  1539,  1540,    -1,   149,  1816,  1817,    -1,
      -1,    -1,    -1,     7,    -1,  1824,    10,    -1,    -1,    -1,
      14,    15,    16,    17,    10,    -1,    -1,    -1,    14,    15,
      16,    17,    -1,    27,    -1,   810,    -1,    -1,    -1,  1575,
      34,    27,    36,    -1,    -1,    -1,    -1,   822,    34,     5,
      36,     7,    -1,     9,    10,    -1,  1865,    -1,   201,    -1,
      16,    17,  1871,    -1,    -1,    -1,    22,    23,    24,    25,
      64,  1607,    28,    29,    30,    31,    32,    33,    64,    35,
      -1,    37,    38,    -1,    78,    -1,    -1,  1896,    -1,    -1,
      -1,    -1,   867,   868,   869,   870,  1905,   872,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    -1,  1922,  1923,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1666,  1667,  1668,    -1,    -1,   129,    -1,    -1,    -1,    -1,
    1949,    -1,    -1,   129,    -1,    -1,    -1,    -1,  1957,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   931,  1966,   933,   934,
     935,   936,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1982,     7,  1984,    -1,    10,    -1,  1715,
      -1,    14,    15,    16,    17,    -1,    -1,    -1,    -1,     7,
      -1,    -1,    10,    -1,    27,    -1,    14,    15,    16,    17,
      -1,    34,    -1,    36,    -1,    -1,    -1,   201,    -1,    27,
      -1,    -1,    -1,    -1,    -1,   201,    34,   992,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,
      10,    64,    -1,    -1,    14,    15,    16,    17,    -1,  1014,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    27,    -1,  1024,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    92,
      -1,    -1,    -1,    -1,  2073,    -1,    -1,    -1,    -1,  2078,
    1045,    -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
    2089,  2090,    -1,    -1,    64,  2094,  1061,    -1,    -1,    -1,
    1065,  1066,    -1,    -1,    -1,  2104,   129,    -1,    -1,    -1,
    2109,  1837,  1838,  1839,  1840,  1841,    -1,    -1,    -1,    -1,
       7,   129,    92,    10,    -1,    -1,   149,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,   149,    -1,    -1,    -1,    -1,    -1,    34,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1122,    -1,   129,
      -1,  1887,  2161,    -1,   906,    10,    -1,  1893,    -1,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    64,   201,   149,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    36,    -1,   201,    -1,    -1,    -1,  2196,    -1,    -1,
    1926,    -1,    -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    -1,  2211,    -1,    -1,    -1,  1181,  1182,    -1,    64,
      -1,  1947,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   201,  1958,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   129,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      -1,    -1,  1978,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,    -1,  1006,  2264,  2265,    -1,    -1,  2268,
      -1,  2270,    -1,    -1,    -1,    -1,  2002,  2003,    -1,    -1,
      -1,    -1,    -1,    -1,   129,    -1,    -1,  2286,  2287,  2288,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2298,
      -1,    -1,    -1,    -1,   149,  2304,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   201,    -1,    -1,  2316,    -1,    -1,
      -1,    -1,    -1,    -1,  2050,    -1,    -1,    -1,    -1,  1294,
    1295,  1296,  1297,  1298,  1299,  1300,  1301,  1302,  1303,  1304,
    1305,  1306,  1307,  1308,  1309,  1310,  1311,  1312,    -1,  2348,
    2349,    -1,    -1,    -1,  2080,    -1,   201,  2083,    -1,  2085,
      -1,  2360,    -1,  1328,  2363,    -1,  2365,    -1,    -1,    -1,
    1335,    -1,  1337,    -1,    -1,    -1,     7,    -1,    -1,    10,
      -1,    -1,  1347,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2393,    -1,    27,    -1,  2397,    -1,
      -1,    -1,  2401,    34,    -1,    36,  2405,    -1,  2407,    -1,
      -1,    -1,    -1,  1378,    -1,    -1,    -1,    -1,    -1,     5,
    2419,  2420,  2421,     9,    10,    -1,    -1,  2153,  2154,    -1,
      16,    17,    -1,    64,    -1,    -1,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1446,    -1,    -1,    -1,    -1,    -1,  2213,    -1,    -1,
      -1,  2217,    -1,    -1,    -1,  1460,    -1,    -1,   129,    -1,
      -1,    -1,     5,    -1,    -1,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,  1481,  1259,   149,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2279,  2280,  2281,  2282,  2283,    -1,    -1,
      -1,    -1,  1527,     5,    -1,    -1,     8,     9,    10,    -1,
     201,  2297,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,  1559,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  2332,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
      -1,    -1,     8,     9,    10,    -1,    -1,  1592,  2354,  2355,
      16,    17,  2358,    -1,  1599,    -1,    22,    23,    24,    25,
    1605,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1628,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2399,    -1,  1640,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1648,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1658,    -1,    -1,  1661,    -1,    -1,    -1,
      -1,     5,    -1,    -1,     8,     9,    10,    -1,    -1,    -1,
      -1,  1676,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,  1687,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,     5,  1701,    -1,    -1,     9,
      10,    -1,  1707,    -1,    -1,    -1,    16,    17,  1713,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    37,    38,
       5,    -1,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    -1,    19,    -1,    21,
      -1,    23,    24,  1828,    26,    -1,    -1,    -1,    30,    -1,
      32,    33,    -1,    -1,    36,    37,    38,    -1,    40,    -1,
      42,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      -1,    -1,    64,    65,    66,    -1,    68,  1872,    70,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,  1892,    -1,  1894,
      92,    -1,    94,  1898,    96,    97,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,   106,    -1,    -1,   109,   110,    -1,
     112,   113,   114,    -1,    -1,    -1,  1921,   119,   120,  1924,
      -1,   123,    -1,   125,   126,   127,    -1,   129,   130,    -1,
      -1,   133,    -1,   135,   136,   137,   138,   139,   140,  1944,
      -1,    -1,    -1,    -1,    -1,   147,   148,   149,    -1,    -1,
      -1,    -1,   154,   155,   156,    -1,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,    -1,   185,    -1,   187,    -1,   189,    -1,   191,
     192,   193,   194,   195,   196,   197,   198,   199,    -1,    -1,
      -1,    -1,    -1,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,  2029,  2030,    28,    29,    30,    31,
      32,    33,  2037,    35,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   251,
      -1,    -1,   254,     5,   256,    -1,    -1,     9,    10,    -1,
      -1,    -1,    -1,  2068,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,  2087,    35,     5,    37,    38,  2092,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,  2102,  2103,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,  2133,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,  2143,  2144,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  2176,    -1,  2178,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,  2187,    -1,     9,    10,    -1,  2192,    -1,    -1,
    2195,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,  2207,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    37,    38,    -1,    -1,     5,    -1,    -1,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,  2274,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2309,    -1,  2311,    -1,    -1,    -1,
    2315,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2327,  2328,    -1,  2330,    -1,     5,    -1,    -1,
      -1,     9,    10,    -1,    -1,  2340,    -1,  2342,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  2374,
      -1,  2376,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       6,    -1,    -1,  2388,  2389,   587,   588,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2412,    -1,    -1,
      -1,  2416,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,  2426,    48,    49,    50,    51,    52,    53,    -1,    -1,
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
     326,    -1,    -1,    -1,   330,   331,   332,   333,   334,     5,
     336,   337,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,     5,    -1,
       7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    38,     5,    -1,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    37,    38,     5,    -1,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,
      -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,     5,    37,    38,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,     5,    37,    38,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    -1,    -1,    28,
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
       5,    37,    38,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,     5,    37,    38,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,     5,    37,    38,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,     5,    37,    38,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      32,    33,    -1,    35,     5,    37,    38,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    -1,    37,    38,     5,    -1,
       7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,     5,
      37,    38,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    -1,    35,
       5,    37,    38,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   343,     0,     1,   150,   257,   344,   345,   116,     6,
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
     311,   312,   313,   322,   323,   324,   325,   326,   330,   331,
     332,   333,   334,   336,   337,   346,   348,   351,   363,   364,
     368,   369,   370,   376,   377,   378,   379,   381,   382,   384,
     386,   387,   388,   389,   396,   397,   398,   399,   400,   401,
     405,   406,   407,   411,   412,   450,   452,   465,   508,   509,
     511,   512,   518,   519,   520,   521,   528,   529,   530,   531,
     533,   536,   540,   541,   542,   543,   544,   550,   551,   552,
     563,   564,   565,   567,   570,   573,   578,   579,   581,   583,
     585,   588,   589,   613,   614,   625,   626,   627,   628,   633,
     636,   639,   642,   643,   691,   692,   693,   694,   695,   696,
     697,   698,   704,   706,   708,   710,   712,   713,   714,   715,
     716,   719,   721,   722,   723,   726,   727,   731,   732,   734,
     735,   736,   737,   738,   739,   740,   743,   748,   753,   755,
     756,   757,   758,   760,   761,   762,   763,   764,   781,   784,
     785,   786,   787,   793,   796,   801,   802,   803,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   819,   820,   825,   826,   827,   828,   829,   839,   840,
     841,   842,   843,   844,   845,   846,    15,   475,   475,   537,
     537,   537,   537,   537,   475,   537,   537,   347,   537,   537,
     537,   475,   537,   475,   537,   537,   475,   537,   537,   537,
     474,   537,   475,   537,   537,     7,    15,   476,    15,   475,
     596,   537,   475,   360,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   129,   353,   517,   517,   537,   537,
     537,   475,   537,   353,   537,   475,   475,   537,   537,   474,
     347,   475,   475,    64,   359,   537,   537,   475,   475,   475,
     475,   475,   475,   475,   537,   414,   537,   537,   537,   353,
     451,   347,   475,   537,   537,   537,   475,   537,   475,   537,
     537,   475,   537,   537,   537,   475,   347,   475,   360,   537,
     537,   360,   537,   475,   537,   537,   537,   475,   537,   537,
     475,   537,   475,   537,   537,   537,   537,   537,   537,    15,
     475,   574,   475,   347,   475,   475,   537,   537,   537,    15,
       8,   475,   475,   537,   537,   537,   475,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   475,   537,   475,   537,   537,   537,   537,
     537,   537,   537,   537,   537,   537,   537,    15,    15,    15,
     353,   858,   257,   562,   124,   233,   384,    15,   356,   562,
       8,     8,     8,     8,     7,     8,   124,   348,   371,     8,
     353,   385,     8,     8,     8,     8,     8,   532,     8,   532,
       8,     8,     8,     8,   532,   562,     7,   218,   252,   509,
     511,   520,   521,   239,   529,   529,    10,    14,    15,    16,
      17,    27,    34,    36,    64,    92,   149,   201,   353,   365,
     481,   482,   484,   485,   486,   487,   493,   494,   495,   496,
     497,   500,    15,   537,     5,     9,    15,    16,    17,   129,
     483,   485,   493,   546,   560,   561,   537,    15,   546,   537,
       5,   545,   546,   561,   546,     8,     8,     8,     8,     8,
       8,     8,     8,     7,     8,     8,     5,     7,   353,   623,
     624,   353,   616,   476,    15,    15,   149,   464,   353,   353,
     724,   725,     8,   353,   640,   641,   725,   353,   355,   353,
      15,   513,   558,    23,    37,   353,   403,   404,    15,   353,
     586,   353,   655,   655,   353,   637,   638,   353,   516,   413,
      15,   353,   566,   149,   730,   516,     7,   459,   460,   475,
     597,   598,   353,   592,   598,    15,   538,   353,   568,   569,
     516,    15,    15,   516,   730,   517,   516,   516,   516,   516,
     353,   516,   356,   516,    15,   408,   476,   484,   485,    15,
     350,   353,   353,   634,   635,   466,   467,   468,   469,     8,
     656,   720,    15,   353,   580,   353,   571,   572,    15,    15,
     353,   476,    15,   481,   733,    15,    15,   353,   707,   709,
       8,   353,    37,   402,    15,   485,   486,   476,    15,    15,
     538,   464,   476,   485,   353,   699,     5,    15,   560,   561,
     476,   353,   354,   476,   559,    15,   484,   617,   618,   592,
     596,   353,   584,   353,   679,   679,    15,   353,   582,   699,
     481,   492,   476,   360,    15,   353,   685,   685,   685,   685,
     685,     7,   481,   575,   576,   353,   577,   476,   349,   353,
     476,   353,   705,   707,   353,   475,   476,   353,   453,    15,
      15,   559,   353,    15,   598,    15,   598,   598,   598,   598,
     767,   823,   598,   598,   598,   598,   598,   598,   767,   353,
     360,   830,   831,   832,    15,    15,    15,   481,   481,   481,
     481,   480,   481,    15,   360,   847,   848,   849,   850,   360,
     851,   852,   853,   854,   855,   360,   856,   857,   347,   347,
     124,     5,    21,   353,   357,   358,   352,   360,   353,   353,
     353,   404,     7,   360,   347,   124,   353,   353,     5,    15,
     391,   392,   353,   404,   404,   404,   404,   403,   484,   402,
     353,   353,   408,   415,   416,   418,   419,   537,   537,   239,
     394,   481,   482,   481,   481,   481,   481,     5,     9,    16,
      17,    22,    23,    24,    25,    26,    28,    29,    30,    31,
      32,    33,    35,    37,    38,   365,    15,   246,     3,    15,
     246,   246,    15,   490,   491,    21,   534,   558,   492,     5,
       9,   166,   547,   548,   549,   560,    26,   560,     5,     9,
      23,    37,   483,   559,   560,   559,     8,    15,   485,   553,
     554,    15,   481,   482,   497,   555,   556,   557,   555,   566,
     353,   580,   582,   584,   586,   353,     7,   360,   705,     8,
      21,   618,   404,   506,   481,   240,   532,    15,   360,    15,
     458,     8,   558,     7,   481,   514,   515,   516,    15,   353,
     458,   404,   463,   464,     8,   415,   506,   458,    15,     8,
      21,     5,     7,   461,   462,   481,   353,     8,    21,     5,
      58,    86,   126,   137,   165,   258,   599,   595,   596,   175,
     587,   481,   149,   527,     8,   481,   481,   352,   353,   409,
     410,   484,   489,   353,    26,   353,   522,   523,   525,   356,
       8,     8,    15,   231,   384,   470,   360,     8,   720,   353,
     484,   689,   699,   717,   718,     8,    26,     5,     9,    16,
      17,    22,    23,    24,    25,    28,    29,    30,    31,    32,
      33,    34,    35,    37,    38,   365,   366,   367,   353,   360,
     374,   484,   481,    15,   360,   353,   353,   484,   484,   507,
       8,   656,   711,   353,   484,   644,   645,   353,   448,   449,
     527,   404,    18,   559,   560,   559,   380,   383,   623,   618,
       7,   596,   598,   689,   699,   700,   701,   403,   404,   442,
     443,    62,   484,   744,    15,    15,     7,     8,    21,   574,
     404,   356,   404,   458,     8,   654,   676,    21,   360,   353,
       8,   481,   481,   458,   484,   532,   788,   484,   287,   800,
     800,   532,   797,   800,    15,   532,   765,   532,   804,   765,
     765,   532,   782,   532,   794,   458,   147,   148,   180,   314,
     315,   318,   319,   361,   833,   834,   835,     8,    21,   485,
     660,   836,    21,   836,   360,   741,   742,     8,     8,     8,
       8,   484,   487,   488,   759,   191,   208,     8,    21,    41,
     209,   228,     8,    21,   335,   338,   339,     8,    21,   353,
     349,   347,     8,    21,   213,   361,   458,    44,    87,    93,
     119,   143,   145,   178,   183,   187,   191,   194,   216,   230,
     236,   372,   373,   375,   353,   347,   475,   538,   558,   385,
     458,   532,   532,     8,    37,    15,   353,   421,   426,   360,
      15,   501,    21,     8,   481,   481,   481,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   481,
     481,   481,   481,   558,    64,   129,   477,   479,   558,   484,
     495,   498,    64,   498,   492,     8,    21,     5,   481,   535,
     549,     8,    21,     5,     9,   481,    21,   481,   560,   560,
     560,   560,   560,    21,   553,   553,     8,   481,   482,   556,
     557,     8,     8,     8,   458,   458,   475,    43,    67,    82,
      87,    88,    94,   228,   259,   303,   627,   624,   360,   488,
     504,    21,   353,    15,   480,    67,   459,   641,   481,     7,
       8,    21,   534,    37,     8,    21,   638,   484,   487,   503,
     505,   558,   728,   461,     7,   458,   598,    15,    15,    15,
      15,    15,    15,   587,   598,   353,    21,   539,   569,    21,
      21,    15,     8,    21,     8,   491,   485,     8,   524,    26,
     352,   635,   467,   129,   471,   472,   473,   389,   169,   208,
     282,   360,    15,     7,     8,    21,   572,    21,    21,   147,
     148,   180,    21,    18,    21,     7,   481,   499,   175,   321,
      37,     8,    21,   360,     8,    21,    26,     8,    21,   539,
     481,    21,   444,   445,   444,    21,     7,   598,   587,    15,
       7,     8,    21,     8,    15,    15,    26,   686,   687,   689,
     480,   481,   576,   360,     8,   676,     8,   654,   385,   375,
     362,    21,    21,    21,   598,   532,    21,   598,   532,   824,
     598,   532,   598,   532,   598,   532,   598,   532,    15,    15,
      15,    15,    15,    15,   360,   832,     8,    21,    21,   182,
     315,   318,     8,    21,   360,   360,   360,   481,    15,    15,
       8,    21,    15,    15,   848,    15,    15,    15,   852,    15,
      15,   857,   356,   353,   358,    15,   390,   391,   458,   475,
      15,     7,     8,   353,   458,    15,   495,     5,   393,   481,
     549,   404,   484,   418,    15,    16,    17,    27,    36,    59,
      64,    92,   149,   201,   417,   419,   429,   430,   431,   432,
     433,   434,   435,   436,   421,   426,   427,   428,    15,   422,
     423,    62,   481,   555,   482,   477,    21,     8,   478,   481,
     499,   549,     7,   558,   464,   481,   558,     8,   554,    21,
       8,     8,     8,   482,   557,   482,   557,   482,   557,   353,
     255,     8,    21,   464,   463,    21,     7,    21,   481,   514,
      21,   464,   532,     8,    21,   549,   729,     8,    21,   462,
     481,   599,   558,    15,   601,   353,   600,   600,   481,   600,
     458,   598,   239,   516,   480,   410,   410,   353,   481,   523,
      21,   481,   499,     8,    21,    16,    15,    15,    15,   480,
     717,   718,   476,   484,   749,     7,   481,     7,    21,    21,
     353,   594,   485,   484,   645,   598,   646,   481,   449,   532,
       8,    47,   177,   353,   447,   360,   615,   617,   587,     7,
       7,   481,   702,   703,   700,   701,   443,   481,     5,   601,
     745,   746,   752,   481,   611,     8,    21,    15,    21,    71,
     208,   360,   360,   476,   172,   353,   456,   457,   485,   191,
     208,   282,   285,   290,   298,   768,   769,   770,   777,   789,
     790,   791,   598,   266,   798,   799,   800,   598,    37,   484,
     821,   822,    84,   265,   289,   299,   304,   766,   768,   769,
     770,   771,   772,   773,   775,   776,   777,   598,   768,   769,
     770,   771,   772,   773,   775,   776,   777,   790,   791,   805,
     598,   768,   769,   770,   777,   783,   598,   768,   769,   795,
     598,   836,   836,   836,   360,   837,   838,   836,   836,   485,
     742,   328,   315,   329,   558,   477,   488,   660,   360,   680,
     686,   700,   686,   644,   644,   353,    18,    26,   395,    15,
     374,     7,   360,   390,   539,   539,   394,     5,   481,   432,
     433,   434,   437,   433,   435,   433,   435,   246,   246,   246,
     246,   246,     8,    37,   353,   420,   484,     5,   422,   423,
       8,    15,    16,    17,   149,   353,   420,   424,   425,   438,
     439,   440,   441,    15,   423,    15,    21,   502,    21,    21,
     491,   558,   481,   492,   535,   548,   560,   525,   526,   482,
     526,   526,   526,   458,   353,   619,   622,   558,     8,    21,
       7,   394,   481,   558,   481,   558,   549,   612,   481,   602,
     603,    21,    21,    21,    21,     8,     8,   254,   510,   516,
      21,   472,   473,   660,   660,   660,    21,    21,   353,    15,
      21,   481,     7,     7,   481,   458,   173,     8,   650,   651,
     652,   653,   654,   656,   657,   658,   661,   662,   663,   676,
     684,   525,   445,    15,    15,   446,   255,     8,     7,     8,
      21,    21,    21,     8,    21,    21,   687,   688,    15,    15,
     353,   353,   454,   455,    18,     8,    26,   767,    15,   767,
     767,    15,   598,   789,   767,   598,   798,   353,     8,    21,
      15,   767,    15,   767,    15,   598,   766,   598,   805,   598,
     783,   598,   795,    21,    21,    21,   316,   317,     8,    21,
      21,    21,    15,    15,   477,    21,    21,    22,    24,    33,
      35,   158,   159,   161,   162,   192,   234,   247,   681,   682,
     683,     8,    21,    21,    21,    21,    21,    21,    21,   481,
     481,   629,   630,    21,   373,   395,     5,   481,   385,     8,
      21,     8,   498,   498,   498,   498,   498,   429,     5,    15,
     419,   430,   423,   353,   420,   428,   438,   439,   439,     8,
      21,     7,    16,    17,     5,    37,     9,   438,   481,    20,
     491,   478,    21,    26,    21,    21,    21,    21,    15,   488,
     549,   464,   640,   476,   503,   549,   729,   481,    21,     7,
       8,    21,   481,   360,    15,    21,    21,    21,     7,   750,
     751,   752,   481,   481,     7,   484,   647,   360,   652,    26,
     447,    26,   366,   619,   617,   353,   590,   591,   592,   593,
     703,   746,   598,    78,   575,   353,   655,   700,   677,    18,
       8,   353,   457,   481,   598,   778,   360,   598,   598,   823,
     484,   821,   360,   481,   481,   598,   598,   598,   598,   838,
     660,   484,    21,    15,    15,   360,     8,    21,     7,    21,
      21,   558,   437,   430,   558,   420,    26,    21,   438,   425,
     439,   439,   440,   440,   440,    21,   481,     5,   481,   499,
     620,   621,   484,     8,   660,   484,     8,   481,   603,   360,
      21,   254,   481,     8,    21,   481,    15,    41,   135,   191,
     209,   221,   223,   224,   226,   229,   320,   481,   446,    21,
      21,    15,     8,   132,   747,    21,    21,     7,    21,   679,
     681,   353,   455,     5,    16,    17,    22,    24,    33,    35,
      37,   159,   162,   247,   305,   306,   307,   780,    21,    94,
     230,   284,   295,   792,    37,   191,   288,   299,   774,    21,
      21,    21,    21,   485,   660,   681,     7,     7,   393,    21,
     477,   424,   438,    21,     8,     8,    21,   464,   549,   255,
      15,    21,   751,     5,   481,   648,   649,    15,   664,    15,
      15,    15,    15,    15,   685,   685,    15,    15,     8,   480,
     591,   689,   690,    15,   700,   678,   678,     7,     8,    21,
     824,    21,     8,    21,     8,     7,   394,    21,    21,   481,
     621,   481,   353,   604,   605,   481,     8,    21,   598,   664,
     699,   717,   660,   699,   700,   689,   686,   481,   481,   659,
     481,    21,     8,   360,    21,     7,     8,    21,   660,   779,
     481,   360,   481,   485,   353,   631,   632,    21,     8,    15,
      21,   649,   148,   180,   665,     7,    21,    21,     7,    21,
      15,    21,    21,     8,    21,     8,   689,    78,   680,   680,
      21,   327,    21,     8,   481,    40,   481,   606,   607,   752,
       7,     7,   666,   667,   689,   717,   700,   575,   481,   481,
      21,    21,    21,    15,   632,   353,   608,     8,    21,     8,
      21,    15,    21,    21,    21,     8,   480,    17,   609,   610,
     607,   667,   481,   668,   669,    21,   481,    21,   611,    17,
       7,     8,    21,     8,   754,   611,   481,   669,    15,   360,
     360,   670,   671,   672,   673,   674,   182,   318,   128,   157,
     217,     8,    21,     7,     7,    15,   675,   675,   675,   671,
     360,   673,   674,   360,   674,   479,     7,    21,   674
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
#line 769 "gram1.y"
    { (yyval.bf_node) = BFNULL; ;}
    break;

  case 3:
#line 771 "gram1.y"
    { (yyval.bf_node) = set_stat_list((yyvsp[(1) - (3)].bf_node),(yyvsp[(2) - (3)].bf_node)); ;}
    break;

  case 4:
#line 775 "gram1.y"
    { lastwasbranch = NO;  (yyval.bf_node) = BFNULL; ;}
    break;

  case 5:
#line 777 "gram1.y"
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
#line 791 "gram1.y"
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
#line 822 "gram1.y"
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
#line 831 "gram1.y"
    {
	      err("Unclassifiable statement", 10);
	      flline();
	      (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 9:
#line 837 "gram1.y"
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
#line 857 "gram1.y"
    { 
	      flline();	 needkwd = NO;	inioctl = NO;
/*!!!*/
              opt_kwd_ = NO; intonly = NO; opt_kwd_hedr = NO; opt_kwd_r = NO; as_op_kwd_= NO; optcorner = NO;
	      yyerrok; yyclearin;  (yyval.bf_node) = BFNULL;
	    ;}
    break;

  case 11:
#line 866 "gram1.y"
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
#line 882 "gram1.y"
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
#line 894 "gram1.y"
    {  PTR_BFND q = BFNULL;

	      (yyvsp[(3) - (3)].symbol)->variant = PROCEDURE_NAME;
	      (yyvsp[(3) - (3)].symbol)->decl = YES;   /* variable declaration has been seen. */
	      q = get_bfnd(fi,BLOCK_DATA, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
	      set_blobs(q, global_bfnd, NEW_GROUP1);
              add_scope_level(q, NO);
	    ;}
    break;

  case 14:
#line 904 "gram1.y"
    { 
              install_param_list((yyvsp[(3) - (4)].symbol), (yyvsp[(4) - (4)].symbol), LLNULL, PROCEDURE_NAME); 
	      /* if there is only a control end the control parent is not set */
              
	     ;}
    break;

  case 15:
#line 911 "gram1.y"
    { install_param_list((yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].symbol), LLNULL, PROCEDURE_NAME); 
              if((yyvsp[(1) - (5)].ll_node)->variant == RECURSIVE_OP) 
                   (yyvsp[(4) - (5)].symbol)->attr = (yyvsp[(4) - (5)].symbol)->attr | RECURSIVE_BIT;
              pred_bfnd->entry.Template.ll_ptr3 = (yyvsp[(1) - (5)].ll_node);
            ;}
    break;

  case 16:
#line 917 "gram1.y"
    {
              install_param_list((yyvsp[(3) - (5)].symbol), (yyvsp[(4) - (5)].symbol), (yyvsp[(5) - (5)].ll_node), FUNCTION_NAME);  
  	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(5) - (5)].ll_node);
            ;}
    break;

  case 17:
#line 922 "gram1.y"
    {
              install_param_list((yyvsp[(1) - (3)].symbol), (yyvsp[(2) - (3)].symbol), (yyvsp[(3) - (3)].ll_node), FUNCTION_NAME); 
	      pred_bfnd->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
	    ;}
    break;

  case 18:
#line 927 "gram1.y"
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
#line 951 "gram1.y"
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
#line 977 "gram1.y"
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
#line 992 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, RECURSIVE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 22:
#line 994 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PURE_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 23:
#line 996 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, ELEMENTAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 24:
#line 1000 "gram1.y"
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
#line 1017 "gram1.y"
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
#line 1031 "gram1.y"
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
#line 1055 "gram1.y"
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
#line 1071 "gram1.y"
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
#line 1085 "gram1.y"
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
#line 1103 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 31:
#line 1105 "gram1.y"
    { PTR_SYMB s;
              s = make_scalar((yyvsp[(4) - (5)].hash_entry), TYNULL, LOCAL);
              (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 32:
#line 1112 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 33:
#line 1115 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_MAIN")); ;}
    break;

  case 34:
#line 1117 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry));
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
            ;}
    break;

  case 35:
#line 1123 "gram1.y"
    { (yyval.symbol) = make_program(look_up_sym("_BLOCK")); ;}
    break;

  case 36:
#line 1125 "gram1.y"
    {
              (yyval.symbol) = make_program((yyvsp[(1) - (1)].hash_entry)); 
	      (yyval.symbol)->decl = YES;   /* variable declaration has been seen. */
	    ;}
    break;

  case 37:
#line 1132 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 38:
#line 1134 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 39:
#line 1136 "gram1.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); ;}
    break;

  case 41:
#line 1141 "gram1.y"
    { (yyval.symbol) = set_id_list((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol)); ;}
    break;

  case 42:
#line 1145 "gram1.y"
    {
	      (yyval.symbol) = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, IO);
            ;}
    break;

  case 43:
#line 1149 "gram1.y"
    { (yyval.symbol) = make_scalar(look_up_sym("*"), TYNULL, IO); ;}
    break;

  case 44:
#line 1155 "gram1.y"
    { char *s;

	      s = copyn(yyleng+1, yytext);
	      s[yyleng] = '\0';
	      (yyval.charp) = s;
	    ;}
    break;

  case 45:
#line 1164 "gram1.y"
    { needkwd = 1; ;}
    break;

  case 46:
#line 1168 "gram1.y"
    { needkwd = NO; ;}
    break;

  case 47:
#line 1173 "gram1.y"
    { colon_flag = YES; ;}
    break;

  case 61:
#line 1194 "gram1.y"
    {
	      saveall = YES;
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 62:
#line 1199 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,SAVE_DECL, SMNULL, (yyvsp[(4) - (4)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 63:
#line 1204 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL, SMNULL);
	      p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,FORMAT_STAT, SMNULL, p, LLNULL, LLNULL);
             ;}
    break;

  case 64:
#line 1211 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,PARAM_DECL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 77:
#line 1227 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, SMNULL, LLNULL, LLNULL, LLNULL); 
             /* add_scope_level($$, NO); */    
            ;}
    break;

  case 78:
#line 1231 "gram1.y"
    { PTR_SYMB s;

	      s = make_procedure((yyvsp[(3) - (3)].hash_entry), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_STMT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 79:
#line 1239 "gram1.y"
    { PTR_SYMB s;

	      s = make_function((yyvsp[(4) - (5)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_OPERATOR, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 80:
#line 1247 "gram1.y"
    { PTR_SYMB s;


	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
	      (yyval.bf_node) = get_bfnd(fi, INTERFACE_ASSIGNMENT, s, LLNULL, LLNULL, LLNULL);
              /*add_scope_level($$, NO);*/
	    ;}
    break;

  case 81:
#line 1256 "gram1.y"
    { parstate = INDCL;
              (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	      /*process_interface($$);*/ /*podd 01.02.03*/
              /*delete_beyond_scope_level(pred_bfnd);*/
	    ;}
    break;

  case 82:
#line 1264 "gram1.y"
    { (yyval.hash_entry) = look_up_sym(yytext); ;}
    break;

  case 83:
#line 1268 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 84:
#line 1270 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry); ;}
    break;

  case 85:
#line 1274 "gram1.y"
    { (yyval.hash_entry) = look_up_op(PLUS); ;}
    break;

  case 86:
#line 1276 "gram1.y"
    { (yyval.hash_entry) = look_up_op(MINUS); ;}
    break;

  case 87:
#line 1278 "gram1.y"
    { (yyval.hash_entry) = look_up_op(ASTER); ;}
    break;

  case 88:
#line 1280 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DASTER); ;}
    break;

  case 89:
#line 1282 "gram1.y"
    { (yyval.hash_entry) = look_up_op(SLASH); ;}
    break;

  case 90:
#line 1284 "gram1.y"
    { (yyval.hash_entry) = look_up_op(DSLASH); ;}
    break;

  case 91:
#line 1286 "gram1.y"
    { (yyval.hash_entry) = look_up_op(AND); ;}
    break;

  case 92:
#line 1288 "gram1.y"
    { (yyval.hash_entry) = look_up_op(OR); ;}
    break;

  case 93:
#line 1290 "gram1.y"
    { (yyval.hash_entry) = look_up_op(XOR); ;}
    break;

  case 94:
#line 1292 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NOT); ;}
    break;

  case 95:
#line 1294 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQ); ;}
    break;

  case 96:
#line 1296 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NE); ;}
    break;

  case 97:
#line 1298 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GT); ;}
    break;

  case 98:
#line 1300 "gram1.y"
    { (yyval.hash_entry) = look_up_op(GE); ;}
    break;

  case 99:
#line 1302 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LT); ;}
    break;

  case 100:
#line 1304 "gram1.y"
    { (yyval.hash_entry) = look_up_op(LE); ;}
    break;

  case 101:
#line 1306 "gram1.y"
    { (yyval.hash_entry) = look_up_op(NEQV); ;}
    break;

  case 102:
#line 1308 "gram1.y"
    { (yyval.hash_entry) = look_up_op(EQV); ;}
    break;

  case 103:
#line 1313 "gram1.y"
    {
             PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(4) - (4)].hash_entry), TYNULL, LOCAL);	
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, LLNULL, LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 104:
#line 1322 "gram1.y"
    { PTR_SYMB s;
         
             type_var = s = make_derived_type((yyvsp[(7) - (7)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
             (yyval.bf_node) = get_bfnd(fi, STRUCT_DECL, s, (yyvsp[(5) - (7)].ll_node), LLNULL, LLNULL);
             add_scope_level((yyval.bf_node), NO);
	   ;}
    break;

  case 105:
#line 1332 "gram1.y"
    {
	     (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);
           ;}
    break;

  case 106:
#line 1340 "gram1.y"
    {
             (yyval.bf_node) = get_bfnd(fi, CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL);
	     if (type_var != SMNULL)
               process_type(type_var, (yyval.bf_node));
             type_var = SMNULL;
	     delete_beyond_scope_level(pred_bfnd);	
           ;}
    break;

  case 107:
#line 1350 "gram1.y"
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
#line 1371 "gram1.y"
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
#line 1390 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 110:
#line 1392 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 111:
#line 1394 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node); ;}
    break;

  case 112:
#line 1398 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 113:
#line 1400 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); ;}
    break;

  case 114:
#line 1404 "gram1.y"
    { type_options = type_options | PARAMETER_BIT; 
              (yyval.ll_node) = make_llnd(fi, PARAMETER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 115:
#line 1408 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 116:
#line 1410 "gram1.y"
    { type_options = type_options | ALLOCATABLE_BIT;
              (yyval.ll_node) = make_llnd(fi, ALLOCATABLE_OP, LLNULL, LLNULL, SMNULL);
	    ;}
    break;

  case 117:
#line 1414 "gram1.y"
    { type_options = type_options | DIMENSION_BIT;
	      attr_ndim = ndim;
	      attr_dims = (yyvsp[(2) - (2)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DIMENSION_OP, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 118:
#line 1420 "gram1.y"
    { type_options = type_options | EXTERNAL_BIT;
              (yyval.ll_node) = make_llnd(fi, EXTERNAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 119:
#line 1424 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node); ;}
    break;

  case 120:
#line 1426 "gram1.y"
    { type_options = type_options | INTRINSIC_BIT;
              (yyval.ll_node) = make_llnd(fi, INTRINSIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 121:
#line 1430 "gram1.y"
    { type_options = type_options | OPTIONAL_BIT;
              (yyval.ll_node) = make_llnd(fi, OPTIONAL_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 122:
#line 1434 "gram1.y"
    { type_options = type_options | POINTER_BIT;
              (yyval.ll_node) = make_llnd(fi, POINTER_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 123:
#line 1438 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, SAVE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 124:
#line 1442 "gram1.y"
    { type_options = type_options | SAVE_BIT; 
              (yyval.ll_node) = make_llnd(fi, STATIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 125:
#line 1446 "gram1.y"
    { type_options = type_options | TARGET_BIT; 
              (yyval.ll_node) = make_llnd(fi, TARGET_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 126:
#line 1452 "gram1.y"
    { type_options = type_options | IN_BIT;  type_opt = IN_BIT; 
              (yyval.ll_node) = make_llnd(fi, IN_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 127:
#line 1456 "gram1.y"
    { type_options = type_options | OUT_BIT;  type_opt = OUT_BIT; 
              (yyval.ll_node) = make_llnd(fi, OUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 128:
#line 1460 "gram1.y"
    { type_options = type_options | INOUT_BIT;  type_opt = INOUT_BIT;
              (yyval.ll_node) = make_llnd(fi, INOUT_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 129:
#line 1466 "gram1.y"
    { type_options = type_options | PUBLIC_BIT; 
              type_opt = PUBLIC_BIT;
              (yyval.ll_node) = make_llnd(fi, PUBLIC_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 130:
#line 1471 "gram1.y"
    { type_options =  type_options | PRIVATE_BIT;
               type_opt = PRIVATE_BIT;
              (yyval.ll_node) = make_llnd(fi, PRIVATE_OP, LLNULL, LLNULL, SMNULL);
            ;}
    break;

  case 131:
#line 1478 "gram1.y"
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
#line 1489 "gram1.y"
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
#line 1502 "gram1.y"
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
#line 1513 "gram1.y"
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
#line 1526 "gram1.y"
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
#line 1536 "gram1.y"
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
#line 1549 "gram1.y"
    {
	      privateall = 1;
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 138:
#line 1554 "gram1.y"
    {
	      /*type_options = type_options | PRIVATE_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PRIVATE_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 139:
#line 1560 "gram1.y"
    {type_opt = PRIVATE_BIT;;}
    break;

  case 140:
#line 1564 "gram1.y"
    { 
	      (yyval.bf_node) = get_bfnd(fi, SEQUENCE_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
            ;}
    break;

  case 141:
#line 1569 "gram1.y"
    {
	      /*saveall = YES;*/ /*14.03.03*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, LLNULL, LLNULL, LLNULL);
	    ;}
    break;

  case 142:
#line 1574 "gram1.y"
    {
	      /*type_options = type_options | PUBLIC_BIT;*/
	      (yyval.bf_node) = get_bfnd(fi, PUBLIC_STMT, SMNULL, (yyvsp[(5) - (5)].ll_node), LLNULL, LLNULL);
            ;}
    break;

  case 143:
#line 1580 "gram1.y"
    {type_opt = PUBLIC_BIT;;}
    break;

  case 144:
#line 1584 "gram1.y"
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
#line 1594 "gram1.y"
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
#line 1607 "gram1.y"
    {opt_kwd_hedr = YES;;}
    break;

  case 147:
#line 1612 "gram1.y"
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
#line 1631 "gram1.y"
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
#line 1657 "gram1.y"
    { (yyval.token) = ATT_GLOBAL; ;}
    break;

  case 150:
#line 1659 "gram1.y"
    { (yyval.token) = ATT_CLUSTER; ;}
    break;

  case 151:
#line 1671 "gram1.y"
    {
/*		  varleng = ($1<0 || $1==TYLONG ? 0 : typesize[$1]); */
		  vartype = (yyvsp[(1) - (1)].data_type);
		;}
    break;

  case 152:
#line 1678 "gram1.y"
    { (yyval.data_type) = global_int; ;}
    break;

  case 153:
#line 1679 "gram1.y"
    { (yyval.data_type) = global_float; ;}
    break;

  case 154:
#line 1680 "gram1.y"
    { (yyval.data_type) = global_complex; ;}
    break;

  case 155:
#line 1681 "gram1.y"
    { (yyval.data_type) = global_double; ;}
    break;

  case 156:
#line 1682 "gram1.y"
    { (yyval.data_type) = global_dcomplex; ;}
    break;

  case 157:
#line 1683 "gram1.y"
    { (yyval.data_type) = global_bool; ;}
    break;

  case 158:
#line 1684 "gram1.y"
    { (yyval.data_type) = global_string; ;}
    break;

  case 159:
#line 1689 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 160:
#line 1691 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 161:
#line 1695 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(3) - (5)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 162:
#line 1697 "gram1.y"
    { PTR_LLND l;

                 l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL); 
                 l->entry.string_val = (char *)"*";
                 (yyval.ll_node) = make_llnd(fi, LEN_OP, l,l, SMNULL);
                ;}
    break;

  case 163:
#line 1704 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, LEN_OP, (yyvsp[(5) - (6)].ll_node), (yyvsp[(5) - (6)].ll_node), SMNULL);;}
    break;

  case 164:
#line 1708 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 165:
#line 1710 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 166:
#line 1712 "gram1.y"
    { /*$$ = make_llnd(fi, PAREN_OP, $2, LLNULL, SMNULL);*/  (yyval.ll_node) = (yyvsp[(3) - (5)].ll_node);  ;}
    break;

  case 167:
#line 1720 "gram1.y"
    { if((yyvsp[(7) - (9)].ll_node)->variant==LENGTH_OP && (yyvsp[(3) - (9)].ll_node)->variant==(yyvsp[(7) - (9)].ll_node)->variant)
                (yyvsp[(7) - (9)].ll_node)->variant=KIND_OP;
                (yyval.ll_node) = make_llnd(fi, CONS, (yyvsp[(3) - (9)].ll_node), (yyvsp[(7) - (9)].ll_node), SMNULL); 
            ;}
    break;

  case 168:
#line 1727 "gram1.y"
    { if(vartype->variant == T_STRING)
                (yyval.ll_node) = make_llnd(fi,LENGTH_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
              else
                (yyval.ll_node) = make_llnd(fi,KIND_OP,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL);
            ;}
    break;

  case 169:
#line 1733 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 170:
#line 1739 "gram1.y"
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
#line 1748 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
	      l->entry.string_val = (char *)"*";
              (yyval.ll_node) = make_llnd(fi,LENGTH_OP,l,LLNULL,SMNULL);
            ;}
    break;

  case 172:
#line 1756 "gram1.y"
    {endioctl();;}
    break;

  case 173:
#line 1769 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 174:
#line 1771 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node); ;}
    break;

  case 175:
#line 1774 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, POINTST_OP, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 176:
#line 1778 "gram1.y"
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
#line 1793 "gram1.y"
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
#line 1809 "gram1.y"
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
#line 1827 "gram1.y"
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
#line 1847 "gram1.y"
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
#line 1867 "gram1.y"
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
#line 1889 "gram1.y"
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
#line 1906 "gram1.y"
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
#line 1924 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, SMNULL);
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 185:
#line 1931 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,COMM_STAT, SMNULL, q, LLNULL, LLNULL);
	    ;}
    break;

  case 186:
#line 1938 "gram1.y"
    { PTR_LLND p, q;

              p = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      q = make_llnd(fi,COMM_LIST, p, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(q, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 187:
#line 1945 "gram1.y"
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
#line 1958 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(4) - (4)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (4)].symbol));
	      (yyval.bf_node) = get_bfnd(fi,NAMELIST_STAT, SMNULL, r, LLNULL, LLNULL);
	    ;}
    break;

  case 189:
#line 1965 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(5) - (5)].ll_node), LLNULL, SMNULL);
	      r = make_llnd(fi,NAMELIST_LIST, q, LLNULL, (yyvsp[(3) - (5)].symbol));
	      add_to_lowList(r, (yyvsp[(1) - (5)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 190:
#line 1972 "gram1.y"
    { PTR_LLND q, r;

              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      for (r = (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1;
		   r->entry.list.next;
		   r = r->entry.list.next);
	      add_to_lowLevelList(q, r->entry.Template.ll_ptr1);
	    ;}
    break;

  case 191:
#line 1983 "gram1.y"
    { (yyval.symbol) =  make_local_entity((yyvsp[(2) - (3)].hash_entry), NAMELIST_NAME,global_default,LOCAL); ;}
    break;

  case 192:
#line 1987 "gram1.y"
    { (yyval.symbol) = NULL; /*make_common(look_up_sym("*"));*/ ;}
    break;

  case 193:
#line 1989 "gram1.y"
    { (yyval.symbol) = make_common((yyvsp[(2) - (3)].hash_entry)); ;}
    break;

  case 194:
#line 1994 "gram1.y"
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
#line 2012 "gram1.y"
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
#line 2023 "gram1.y"
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
#line 2035 "gram1.y"
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
#line 2047 "gram1.y"
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
#line 2061 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,EQUI_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node),
			     LLNULL, LLNULL);
	    ;}
    break;

  case 200:
#line 2067 "gram1.y"
    { 
	      add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	    ;}
    break;

  case 201:
#line 2074 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EQUI_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
           ;}
    break;

  case 202:
#line 2080 "gram1.y"
    { PTR_LLND p;
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (3)].ll_node), p, SMNULL);
	    ;}
    break;

  case 203:
#line 2086 "gram1.y"
    { PTR_LLND p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 204:
#line 2094 "gram1.y"
    {  PTR_SYMB s;
           s=make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
           (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$=$1; $$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 205:
#line 2101 "gram1.y"
    {  PTR_SYMB s;
           s=make_array((yyvsp[(1) - (4)].hash_entry),TYNULL,LLNULL,0,LOCAL);
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, s);
           s->attr = s->attr | EQUIVALENCE_BIT;
            /*$$->entry.Template.symbol->attr = $$->entry.Template.symbol->attr | EQUIVALENCE_BIT; */
        ;}
    break;

  case 207:
#line 2120 "gram1.y"
    { PTR_LLND p;
              data_stat = NO;
	      p = make_llnd(fi,STMT_STR, LLNULL, LLNULL,
			    SMNULL);
              p->entry.string_val = copys(stmtbuf);
	      (yyval.bf_node) = get_bfnd(fi,DATA_DECL, SMNULL, p, LLNULL, LLNULL);
            ;}
    break;

  case 210:
#line 2134 "gram1.y"
    {data_stat = YES;;}
    break;

  case 211:
#line 2138 "gram1.y"
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
#line 2183 "gram1.y"
    {;;}
    break;

  case 223:
#line 2187 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);;}
    break;

  case 224:
#line 2191 "gram1.y"
    { (yyval.symbol)= make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL); 
              (yyval.symbol)->attr = (yyval.symbol)->attr | DATA_BIT; 
            ;}
    break;

  case 225:
#line 2197 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_SUBS, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 226:
#line 2201 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_RANGE, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 227:
#line 2205 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 228:
#line 2207 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 229:
#line 2211 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 230:
#line 2213 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 231:
#line 2217 "gram1.y"
    {(yyval.ll_node)= make_llnd(fi, DATA_IMPL_DO, (yyvsp[(2) - (7)].ll_node), (yyvsp[(6) - (7)].ll_node), (yyvsp[(4) - (7)].symbol)); ;}
    break;

  case 232:
#line 2221 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 233:
#line 2223 "gram1.y"
    { (yyval.ll_node) = add_to_lowLevelList((yyvsp[(3) - (3)].ll_node), (yyvsp[(1) - (3)].ll_node)); ;}
    break;

  case 234:
#line 2227 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 235:
#line 2229 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (2)].ll_node), LLNULL, (yyvsp[(1) - (2)].symbol)); ;}
    break;

  case 236:
#line 2231 "gram1.y"
    {
              (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr2 = (yyvsp[(3) - (3)].ll_node);
              (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(2) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); 
            ;}
    break;

  case 237:
#line 2236 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DATA_ELT, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 251:
#line 2260 "gram1.y"
    {if((yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->variant != TYPE_NAME)
               errstr("Undefined type %s",(yyvsp[(2) - (6)].ll_node)->entry.Template.symbol->ident,319); 
           ;}
    break;

  case 268:
#line 2305 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ICON_EXPR, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 269:
#line 2307 "gram1.y"
    {
              PTR_LLND p;

              p = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 270:
#line 2314 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL);
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 271:
#line 2321 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 272:
#line 2328 "gram1.y"
    {
              PTR_LLND p;
 
              p = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node));
              (yyval.ll_node) = make_llnd(fi,ICON_EXPR, p, LLNULL, SMNULL);
            ;}
    break;

  case 273:
#line 2337 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 274:
#line 2339 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 275:
#line 2341 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 276:
#line 2345 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 277:
#line 2347 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 278:
#line 2351 "gram1.y"
    {
              PTR_LLND p;

              p = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
              p->entry.ival = atoi(yytext);
              p->type = global_int;
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 279:
#line 2360 "gram1.y"
    {
              PTR_LLND p;
 
              p = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, p, LLNULL, SMNULL);
            ;}
    break;

  case 280:
#line 2367 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (3)].ll_node), LLNULL, SMNULL);
            ;}
    break;

  case 281:
#line 2374 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 282:
#line 2376 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 283:
#line 2380 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
             (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
           ;}
    break;

  case 284:
#line 2384 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol)); 
            (yyval.ll_node)->entry.Template.symbol->attr = (yyval.ll_node)->entry.Template.symbol->attr | SAVE_BIT;
          ;}
    break;

  case 285:
#line 2390 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 286:
#line 2392 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), EXPR_LIST); ;}
    break;

  case 287:
#line 2396 "gram1.y"
    { as_op_kwd_ = YES; ;}
    break;

  case 288:
#line 2400 "gram1.y"
    { as_op_kwd_ = NO; ;}
    break;

  case 289:
#line 2405 "gram1.y"
    { 
             PTR_SYMB s; 
             s = make_scalar((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);	
	     s->attr = s->attr | type_opt;
	     (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
            ;}
    break;

  case 290:
#line 2412 "gram1.y"
    { PTR_SYMB s;
	      s = make_function((yyvsp[(3) - (4)].hash_entry), global_default, LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,OPERATOR_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 291:
#line 2419 "gram1.y"
    { PTR_SYMB s;
	      s = make_procedure(look_up_sym("="), LOCAL);
	      s->variant = INTERFACE_NAME;
              s->attr = s->attr | type_opt;
              (yyval.ll_node) = make_llnd(fi,ASSIGNMENT_OP, LLNULL, LLNULL, s);
	    ;}
    break;

  case 292:
#line 2429 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 293:
#line 2431 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 294:
#line 2435 "gram1.y"
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
#line 2447 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, MODULE_PROC_STMT, SMNULL, (yyvsp[(2) - (2)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 296:
#line 2450 "gram1.y"
    { PTR_SYMB s;
 	      PTR_LLND q;

	      s = make_function((yyvsp[(1) - (1)].hash_entry), TYNULL, LOCAL);
	      s->variant = ROUTINE_NAME;
              q = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	    ;}
    break;

  case 297:
#line 2459 "gram1.y"
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
#line 2472 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL);
              /*add_scope_level($3->entry.Template.func_hedr, YES);*/ /*17.06.01*/
              copy_module_scope((yyvsp[(3) - (3)].symbol),LLNULL); /*17.03.03*/
              colon_flag = NO;
            ;}
    break;

  case 299:
#line 2478 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), (yyvsp[(6) - (6)].ll_node), LLNULL, LLNULL); 
              /*add_scope_level(module_scope, YES); *//* 17.06.01*/
              copy_module_scope((yyvsp[(3) - (6)].symbol),(yyvsp[(6) - (6)].ll_node)); /*17.03.03 */
              colon_flag = NO;
            ;}
    break;

  case 300:
#line 2484 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, LLNULL, LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (6)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 301:
#line 2490 "gram1.y"
    { PTR_LLND l;

	      l = make_llnd(fi, ONLY_NODE, (yyvsp[(7) - (7)].ll_node), LLNULL, SMNULL);
              (yyval.bf_node) = get_bfnd(fi, USE_STMT, (yyvsp[(3) - (7)].symbol), l, LLNULL, LLNULL);
            ;}
    break;

  case 302:
#line 2498 "gram1.y"
    {
              if ((yyvsp[(1) - (1)].hash_entry)->id_attr == SMNULL)
	         warn1("Unknown module %s", (yyvsp[(1) - (1)].hash_entry)->ident,308);
              (yyval.symbol) = make_global_entity((yyvsp[(1) - (1)].hash_entry), MODULE_NAME, global_default, NO);
	      module_scope = (yyval.symbol)->entry.Template.func_hedr;
           
            ;}
    break;

  case 303:
#line 2508 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 304:
#line 2510 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 305:
#line 2514 "gram1.y"
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
#line 2535 "gram1.y"
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
#line 2560 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 308:
#line 2562 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 309:
#line 2566 "gram1.y"
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
#line 2597 "gram1.y"
    { ndim = 0;	explicit_shape = 1; (yyval.ll_node) = LLNULL; ;}
    break;

  case 311:
#line 2599 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 312:
#line 2602 "gram1.y"
    { ndim = 0; explicit_shape = 1;;}
    break;

  case 313:
#line 2603 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXPR_LIST, (yyvsp[(2) - (2)].ll_node), LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
	    ;}
    break;

  case 314:
#line 2608 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 315:
#line 2612 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
	      ++ndim;
	    ;}
    break;

  case 316:
#line 2620 "gram1.y"
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
#line 2629 "gram1.y"
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
#line 2638 "gram1.y"
    {
	      if(ndim == maxdim)
		err("Too many dimensions", 43);
	      else if(ndim < maxdim)
		(yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      ++ndim;
	    ;}
    break;

  case 319:
#line 2648 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,STAR_RANGE, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->type = global_default;
              explicit_shape = 0;
	    ;}
    break;

  case 321:
#line 2657 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 322:
#line 2659 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 323:
#line 2663 "gram1.y"
    {PTR_LABEL p;
	     p = make_label_node(fi,convci(yyleng, yytext));
	     p->scope = cur_scope();
	     (yyval.ll_node) = make_llnd_label(fi,LABEL_REF, p);
	  ;}
    break;

  case 324:
#line 2671 "gram1.y"
    { /*PTR_LLND l;*/

          /*   l = make_llnd(fi, EXPR_LIST, $3, LLNULL, SMNULL);*/
             (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
             redefine_func_arg_type();
           ;}
    break;

  case 325:
#line 2686 "gram1.y"
    { /*undeftype = YES;
	    setimpl(TYNULL, (int)'a', (int)'z'); FB COMMENTED---> NOT QUITE RIGHT BUT AVOID PB WITH COMMON*/
	    (yyval.bf_node) = get_bfnd(fi,IMPL_DECL, SMNULL, LLNULL, LLNULL, LLNULL);
	  ;}
    break;

  case 326:
#line 2693 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 327:
#line 2695 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 328:
#line 2699 "gram1.y"
    { 

            (yyval.ll_node) = make_llnd(fi, IMPL_TYPE, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
            (yyval.ll_node)->type = vartype;
          ;}
    break;

  case 329:
#line 2714 "gram1.y"
    { implkwd = YES; ;}
    break;

  case 330:
#line 2715 "gram1.y"
    { vartype = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 331:
#line 2719 "gram1.y"
    { (yyval.data_type) = (yyvsp[(2) - (2)].data_type); ;}
    break;

  case 332:
#line 2721 "gram1.y"
    { (yyval.data_type) = (yyvsp[(1) - (1)].data_type);;}
    break;

  case 333:
#line 2733 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 334:
#line 2735 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 335:
#line 2739 "gram1.y"
    {
	      setimpl(vartype, (int)(yyvsp[(1) - (1)].charv), (int)(yyvsp[(1) - (1)].charv));
	      (yyval.ll_node) = make_llnd(fi,CHAR_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.cval = (yyvsp[(1) - (1)].charv);
	    ;}
    break;

  case 336:
#line 2745 "gram1.y"
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
#line 2757 "gram1.y"
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
#line 2768 "gram1.y"
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
#line 2785 "gram1.y"
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
#line 2823 "gram1.y"
    { (yyval.ll_node) = LLNULL; endioctl(); ;}
    break;

  case 343:
#line 2825 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);  endioctl();;}
    break;

  case 344:
#line 2829 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 345:
#line 2831 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 346:
#line 2833 "gram1.y"
    { PTR_LLND l;
	      l = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL);
	      l->type = (yyvsp[(2) - (2)].ll_node)->type;
              (yyval.ll_node) = l; 
	    ;}
    break;

  case 347:
#line 2844 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 348:
#line 2848 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl(); 
            ;}
    break;

  case 349:
#line 2854 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 350:
#line 2856 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 351:
#line 2860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 352:
#line 2862 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 353:
#line 2864 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 354:
#line 2868 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 355:
#line 2870 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 356:
#line 2874 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 357:
#line 2876 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", ADD_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 358:
#line 2878 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", SUBT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 359:
#line 2880 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("*", MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 360:
#line 2882 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("/", DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 361:
#line 2884 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("**", EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 362:
#line 2886 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(1) - (2)].hash_entry), (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 363:
#line 2888 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("+", UNARY_ADD_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 364:
#line 2890 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("-", MINUS_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 365:
#line 2892 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eq.", EQ_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 366:
#line 2894 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".gt.", GT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 367:
#line 2896 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".lt.", LT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 368:
#line 2898 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", GTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 369:
#line 2900 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ge.", LTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 370:
#line 2902 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".ne.", NOTEQL_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 371:
#line 2904 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".eqv.", EQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 372:
#line 2906 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".neqv.", NEQV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 373:
#line 2908 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".xor.", XOR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 374:
#line 2910 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".or.", OR_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 375:
#line 2912 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".and.", AND_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 376:
#line 2914 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node(".not.", NOT_OP, (yyvsp[(2) - (2)].ll_node), LLNULL); ;}
    break;

  case 377:
#line 2916 "gram1.y"
    { (yyval.ll_node) = intrinsic_op_node("//", CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 378:
#line 2918 "gram1.y"
    { (yyval.ll_node) = defined_op_node((yyvsp[(2) - (3)].hash_entry), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node)); ;}
    break;

  case 379:
#line 2921 "gram1.y"
    { (yyval.token) = ADD_OP; ;}
    break;

  case 380:
#line 2922 "gram1.y"
    { (yyval.token) = SUBT_OP; ;}
    break;

  case 381:
#line 2934 "gram1.y"
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
#line 3008 "gram1.y"
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
#line 3020 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 384:
#line 3022 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 385:
#line 3026 "gram1.y"
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
#line 3157 "gram1.y"
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
#line 3207 "gram1.y"
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
#line 3251 "gram1.y"
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
#line 3293 "gram1.y"
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
#line 3351 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 391:
#line 3353 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 392:
#line 3355 "gram1.y"
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
#line 3395 "gram1.y"
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
#line 3437 "gram1.y"
    { 
	      if ((yyvsp[(1) - (2)].ll_node)->type->variant == T_STRING) {
                 (yyvsp[(1) - (2)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (2)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node); (yyval.ll_node)->type = global_string;
              }
              else errstr("can't subscript of %s", (yyvsp[(1) - (2)].ll_node)->entry.Template.symbol->ident,44);
            ;}
    break;

  case 395:
#line 3447 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 396:
#line 3449 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 397:
#line 3453 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL); ;}
    break;

  case 398:
#line 3457 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 399:
#line 3459 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 400:
#line 3463 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 401:
#line 3465 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 402:
#line 3471 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 403:
#line 3473 "gram1.y"
    { PTR_TYPE t;
               t = make_type_node((yyvsp[(1) - (3)].ll_node)->type, (yyvsp[(3) - (3)].ll_node));
               (yyval.ll_node) = (yyvsp[(1) - (3)].ll_node);
               (yyval.ll_node)->type = t;
             ;}
    break;

  case 404:
#line 3479 "gram1.y"
    {
              if ((yyvsp[(2) - (2)].ll_node) != LLNULL)
		 (yyval.ll_node) = make_llnd(fi, ARRAY_OP, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); 
	      else 
                 (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);
             ;}
    break;

  case 405:
#line 3489 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 1;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 406:
#line 3495 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,BOOL_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.bval = 0;
	      (yyval.ll_node)->type = global_bool;
	    ;}
    break;

  case 407:
#line 3502 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,FLOAT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_float;
	    ;}
    break;

  case 408:
#line 3508 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DOUBLE_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.string_val = copys(yytext);
	      (yyval.ll_node)->type = global_double;
	    ;}
    break;

  case 409:
#line 3516 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	      (yyval.ll_node)->entry.ival = atoi(yytext);
	      (yyval.ll_node)->type = global_int;
	    ;}
    break;

  case 410:
#line 3524 "gram1.y"
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
#line 3540 "gram1.y"
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

  case 413:
#line 3563 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,COMPLEX_VAL, (yyvsp[(2) - (5)].ll_node), (yyvsp[(4) - (5)].ll_node), SMNULL);
	      (yyval.ll_node)->type = global_complex;
	    ;}
    break;

  case 414:
#line 3570 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 415:
#line 3572 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 416:
#line 3595 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 417:
#line 3597 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 418:
#line 3599 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),SMNULL),(yyvsp[(5) - (5)].ll_node),SMNULL); ;}
    break;

  case 419:
#line 3601 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,(yyvsp[(1) - (4)].ll_node),LLNULL,SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 420:
#line 3603 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (4)].ll_node),SMNULL),(yyvsp[(4) - (4)].ll_node),SMNULL); ;}
    break;

  case 421:
#line 3605 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL),(yyvsp[(3) - (3)].ll_node),SMNULL); ;}
    break;

  case 422:
#line 3607 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,(yyvsp[(2) - (2)].ll_node),SMNULL); ;}
    break;

  case 423:
#line 3609 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,LLNULL,SMNULL); ;}
    break;

  case 424:
#line 3612 "gram1.y"
    {in_vec=YES;;}
    break;

  case 425:
#line 3612 "gram1.y"
    {in_vec=NO;;}
    break;

  case 426:
#line 3613 "gram1.y"
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
#line 3627 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 428:
#line 3629 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 429:
#line 3652 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 430:
#line 3654 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 431:
#line 3656 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
                  endioctl();
                ;}
    break;

  case 432:
#line 3672 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 433:
#line 3674 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl(); ;}
    break;

  case 434:
#line 3676 "gram1.y"
    { stat_alloc = make_llnd(fi, SPEC_PAIR, (yyvsp[(4) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), SMNULL);
             endioctl();
           ;}
    break;

  case 435:
#line 3689 "gram1.y"
    {stat_alloc = LLNULL;;}
    break;

  case 436:
#line 3693 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 437:
#line 3695 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 438:
#line 3703 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 439:
#line 3705 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 440:
#line 3707 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 441:
#line 3709 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 442:
#line 3763 "gram1.y"
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
#line 3785 "gram1.y"
    {
              make_extend((yyvsp[(3) - (3)].symbol));
              (yyval.bf_node) = BFNULL; 
              /* delete_beyond_scope_level(pred_bfnd); */
             ;}
    break;

  case 444:
#line 3798 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONTROL_END, SMNULL, LLNULL, LLNULL, LLNULL); 
	    bind(); 
	    delete_beyond_scope_level(pred_bfnd);
	    position = IN_OUTSIDE;
          ;}
    break;

  case 445:
#line 3807 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 446:
#line 3810 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);
            ;}
    break;

  case 447:
#line 3860 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = LOGIF_NODE;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 448:
#line 3866 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 449:
#line 3871 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(2) - (3)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (3)].ll_node);
	      set_blobs((yyval.bf_node), pred_bfnd, NEW_GROUP1); 
            ;}
    break;

  case 450:
#line 3889 "gram1.y"
    { make_elseif((yyvsp[(4) - (7)].ll_node),(yyvsp[(7) - (7)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL;;}
    break;

  case 451:
#line 3891 "gram1.y"
    { make_else((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 452:
#line 3893 "gram1.y"
    { make_endif((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 453:
#line 3895 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 454:
#line 3897 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CONTAINS_STMT, SMNULL, LLNULL, LLNULL, LLNULL); ;}
    break;

  case 455:
#line 3900 "gram1.y"
    { thiswasbranch = NO;
              (yyvsp[(1) - (2)].bf_node)->variant = FORALL_STAT;
              (yyval.bf_node) = make_logif((yyvsp[(1) - (2)].bf_node), (yyvsp[(2) - (2)].bf_node));
	      set_blobs((yyvsp[(1) - (2)].bf_node), pred_bfnd, SAME_GROUP);
	    ;}
    break;

  case 456:
#line 3906 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 457:
#line 3908 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(2) - (2)].bf_node); (yyval.bf_node)->entry.Template.ll_ptr3 = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 458:
#line 3910 "gram1.y"
    { make_endforall((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 459:
#line 3913 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 460:
#line 3915 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 461:
#line 3917 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 462:
#line 3944 "gram1.y"
    { 	     
	     /*  if($5 && $5->labdefined)
		 execerr("no backward DO loops", (char *)NULL); */
	       (yyval.bf_node) = make_do(WHILE_NODE, LBNULL, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL);
	       /*$$->entry.Template.ll_ptr3 = $1;*/	     
           ;}
    break;

  case 463:
#line 3953 "gram1.y"
    {
               if( (yyvsp[(4) - (7)].label) && (yyvsp[(4) - (7)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(WHILE_NODE, (yyvsp[(4) - (7)].label), SMNULL, (yyvsp[(7) - (7)].ll_node), LLNULL, LLNULL);            
	    ;}
    break;

  case 464:
#line 3961 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 465:
#line 3963 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(5) - (6)].ll_node);;}
    break;

  case 466:
#line 3965 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 467:
#line 3970 "gram1.y"
    {  
               if( (yyvsp[(4) - (11)].label) && (yyvsp[(4) - (11)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (11)].label), (yyvsp[(7) - (11)].symbol), (yyvsp[(9) - (11)].ll_node), (yyvsp[(11) - (11)].ll_node), LLNULL);            
	    ;}
    break;

  case 468:
#line 3977 "gram1.y"
    {
               if( (yyvsp[(4) - (13)].label) && (yyvsp[(4) - (13)].label)->labdefined)
		  err("No backward DO loops", 46);
	        (yyval.bf_node) = make_do(FOR_NODE, (yyvsp[(4) - (13)].label), (yyvsp[(7) - (13)].symbol), (yyvsp[(9) - (13)].ll_node), (yyvsp[(11) - (13)].ll_node), (yyvsp[(13) - (13)].ll_node));            
	    ;}
    break;

  case 469:
#line 3985 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CASE_NODE, (yyvsp[(4) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 470:
#line 3987 "gram1.y"
    { /*PTR_LLND p;*/
	     /* p = make_llnd(fi, DEFAULT, LLNULL, LLNULL, SMNULL); */
	      (yyval.bf_node) = get_bfnd(fi, DEFAULT_NODE, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 471:
#line 3991 "gram1.y"
    { make_endselect((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 472:
#line 3994 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(6) - (7)].ll_node), LLNULL, LLNULL) ; ;}
    break;

  case 473:
#line 3996 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, SWITCH_NODE, SMNULL, (yyvsp[(7) - (8)].ll_node), LLNULL, (yyvsp[(1) - (8)].ll_node)) ; ;}
    break;

  case 474:
#line 4000 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 475:
#line 4006 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 476:
#line 4008 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (2)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 477:
#line 4010 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, LLNULL, (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 478:
#line 4012 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL); ;}
    break;

  case 479:
#line 4016 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 480:
#line 4018 "gram1.y"
    { PTR_LLND p;
	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 481:
#line 4026 "gram1.y"
    { (yyval.symbol) = SMNULL; ;}
    break;

  case 482:
#line 4028 "gram1.y"
    { (yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSTRUCT_NAME, global_default,
                                     LOCAL); ;}
    break;

  case 483:
#line 4034 "gram1.y"
    {(yyval.hash_entry) = HSNULL;;}
    break;

  case 484:
#line 4036 "gram1.y"
    { (yyval.hash_entry) = (yyvsp[(1) - (1)].hash_entry);;}
    break;

  case 485:
#line 4040 "gram1.y"
    {(yyval.hash_entry) = look_up_sym(yytext);;}
    break;

  case 486:
#line 4044 "gram1.y"
    { PTR_SYMB s;
	             s = make_local_entity( (yyvsp[(1) - (2)].hash_entry), CONSTRUCT_NAME, global_default, LOCAL);             
                    (yyval.ll_node) = make_llnd(fi, VAR_REF, LLNULL, LLNULL, s);
                   ;}
    break;

  case 487:
#line 4065 "gram1.y"
    { (yyval.bf_node) = make_if((yyvsp[(4) - (5)].ll_node)); ;}
    break;

  case 488:
#line 4068 "gram1.y"
    { (yyval.bf_node) = make_forall((yyvsp[(4) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node)); ;}
    break;

  case 489:
#line 4072 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, EXPR_LIST, (yyvsp[(1) - (1)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 490:
#line 4074 "gram1.y"
    { PTR_LLND p;	      
	      p = make_llnd(fi, EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(p, (yyvsp[(1) - (3)].ll_node));
	    ;}
    break;

  case 491:
#line 4081 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi, FORALL_OP, (yyvsp[(3) - (3)].ll_node), LLNULL, (yyvsp[(1) - (3)].symbol)); ;}
    break;

  case 492:
#line 4085 "gram1.y"
    { (yyval.ll_node)=LLNULL;;}
    break;

  case 493:
#line 4087 "gram1.y"
    { (yyval.ll_node)=(yyvsp[(2) - (2)].ll_node);;}
    break;

  case 494:
#line 4103 "gram1.y"
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
#line 4116 "gram1.y"
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
#line 4139 "gram1.y"
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
#line 4162 "gram1.y"
    { (yyval.label) = LBNULL; ;}
    break;

  case 498:
#line 4164 "gram1.y"
    {
	       (yyval.label)  = make_label_node(fi,convci(yyleng, yytext));
	       (yyval.label)->scope = cur_scope();
	    ;}
    break;

  case 499:
#line 4171 "gram1.y"
    { make_endwhere((yyvsp[(3) - (3)].symbol)); (yyval.bf_node) = BFNULL; ;}
    break;

  case 500:
#line 4173 "gram1.y"
    { make_elsewhere((yyvsp[(3) - (3)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 501:
#line 4175 "gram1.y"
    { make_elsewhere_mask((yyvsp[(4) - (6)].ll_node),(yyvsp[(6) - (6)].symbol)); lastwasbranch = NO; (yyval.bf_node) = BFNULL; ;}
    break;

  case 502:
#line 4177 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 503:
#line 4179 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_BLOCK_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), LLNULL, (yyvsp[(1) - (6)].ll_node)); ;}
    break;

  case 504:
#line 4184 "gram1.y"
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
#line 4259 "gram1.y"
    { /*PTR_SYMB s;*/
	
	      /*s = make_scalar($2, TYNULL, LOCAL);*/
  	      (yyval.bf_node) = get_bfnd(fi, POINTER_ASSIGN_STAT, SMNULL, (yyvsp[(3) - (5)].ll_node), (yyvsp[(5) - (5)].ll_node), LLNULL);
	    ;}
    break;

  case 506:
#line 4271 "gram1.y"
    { PTR_SYMB p;

	      p = make_scalar((yyvsp[(5) - (5)].hash_entry), TYNULL, LOCAL);
	      p->variant = LABEL_VAR;
  	      (yyval.bf_node) = get_bfnd(fi,ASSLAB_STAT, p, (yyvsp[(3) - (5)].ll_node),LLNULL,LLNULL);
            ;}
    break;

  case 507:
#line 4278 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,CONT_STAT,SMNULL,LLNULL,LLNULL,LLNULL); ;}
    break;

  case 509:
#line 4281 "gram1.y"
    { inioctl = NO; ;}
    break;

  case 510:
#line 4283 "gram1.y"
    { PTR_LLND	p;

	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(10) - (10)].ll_node), LLNULL, SMNULL);
	      p = make_llnd(fi,EXPR_LIST, (yyvsp[(8) - (10)].ll_node), p, SMNULL);
	      (yyval.bf_node)= get_bfnd(fi,ARITHIF_NODE, SMNULL, (yyvsp[(4) - (10)].ll_node),
			    make_llnd(fi,EXPR_LIST, (yyvsp[(6) - (10)].ll_node), p, SMNULL), LLNULL);
	      thiswasbranch = YES;
            ;}
    break;

  case 511:
#line 4292 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (1)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT, $1, LLNULL, LLNULL, LLNULL);
*/	      endioctl(); 
            ;}
    break;

  case 512:
#line 4299 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (3)].symbol), LLNULL, LLNULL, PLAIN);
/*	      match_parameters($1, LLNULL);
	      $$= get_bfnd(fi,PROC_STAT,$1,LLNULL,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 513:
#line 4306 "gram1.y"
    {
	      (yyval.bf_node) = subroutine_call((yyvsp[(1) - (4)].symbol), (yyvsp[(3) - (4)].ll_node), LLNULL, PLAIN);
/*	      match_parameters($1, $3);
	      $$= get_bfnd(fi,PROC_STAT,$1,$3,LLNULL,LLNULL);
*/	      endioctl(); 
	    ;}
    break;

  case 514:
#line 4314 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,RETURN_STAT,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = YES;
	    ;}
    break;

  case 515:
#line 4319 "gram1.y"
    {
	      (yyval.bf_node) = get_bfnd(fi,(yyvsp[(1) - (3)].token),SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	      thiswasbranch = ((yyvsp[(1) - (3)].token) == STOP_STAT);
	    ;}
    break;

  case 516:
#line 4324 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, CYCLE_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 517:
#line 4327 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, EXIT_STMT, (yyvsp[(3) - (3)].symbol), LLNULL, LLNULL, LLNULL); ;}
    break;

  case 518:
#line 4330 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, ALLOCATE_STMT,  SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc, LLNULL); ;}
    break;

  case 519:
#line 4333 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, DEALLOCATE_STMT, SMNULL, (yyvsp[(5) - (6)].ll_node), stat_alloc , LLNULL); ;}
    break;

  case 520:
#line 4336 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, NULLIFY_STMT, SMNULL, (yyvsp[(4) - (5)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 521:
#line 4339 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi, WHERE_NODE, SMNULL, (yyvsp[(4) - (8)].ll_node), (yyvsp[(6) - (8)].ll_node), (yyvsp[(8) - (8)].ll_node)); ;}
    break;

  case 522:
#line 4357 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 523:
#line 4361 "gram1.y"
    {
	      (yyval.bf_node)=get_bfnd(fi,GOTO_NODE,SMNULL,LLNULL,LLNULL,(PTR_LLND)(yyvsp[(3) - (3)].ll_node));
	      thiswasbranch = YES;
	    ;}
    break;

  case 524:
#line 4366 "gram1.y"
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
#line 4385 "gram1.y"
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
#line 4404 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,COMGOTO_NODE, SMNULL, (yyvsp[(4) - (7)].ll_node), (yyvsp[(7) - (7)].ll_node), LLNULL); ;}
    break;

  case 529:
#line 4412 "gram1.y"
    { (yyval.symbol) = make_procedure((yyvsp[(3) - (4)].hash_entry), YES); ;}
    break;

  case 530:
#line 4416 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 531:
#line 4421 "gram1.y"
    { 
               (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
               endioctl();
            ;}
    break;

  case 532:
#line 4428 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 533:
#line 4430 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 534:
#line 4432 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,LABEL_ARG,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 535:
#line 4435 "gram1.y"
    { (yyval.token) = PAUSE_NODE; ;}
    break;

  case 536:
#line 4436 "gram1.y"
    { (yyval.token) = STOP_STAT; ;}
    break;

  case 537:
#line 4447 "gram1.y"
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
#line 4462 "gram1.y"
    { intonly = YES; ;}
    break;

  case 539:
#line 4466 "gram1.y"
    { intonly = NO; ;}
    break;

  case 540:
#line 4474 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 541:
#line 4477 "gram1.y"
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
#line 4487 "gram1.y"
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
#line 4500 "gram1.y"
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
#line 4513 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 545:
#line 4517 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 546:
#line 4520 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 547:
#line 4523 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 548:
#line 4527 "gram1.y"
    { (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (4)].ll_node);
		  (yyvsp[(1) - (4)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (4)].bf_node); ;}
    break;

  case 549:
#line 4536 "gram1.y"
    { (yyvsp[(1) - (2)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (2)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (2)].bf_node); ;}
    break;

  case 550:
#line 4539 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr2 = (yyvsp[(2) - (3)].ll_node);
		  (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 551:
#line 4543 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (1)].bf_node); ;}
    break;

  case 552:
#line 4545 "gram1.y"
    { (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node);
		  (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 553:
#line 4551 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 554:
#line 4555 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, BACKSPACE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 555:
#line 4557 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, REWIND_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 556:
#line 4559 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, ENDFILE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 557:
#line 4566 "gram1.y"
    { (yyval.bf_node) = (yyvsp[(1) - (3)].bf_node); ;}
    break;

  case 558:
#line 4570 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, INQUIRE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 559:
#line 4572 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, OPEN_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 560:
#line 4574 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, CLOSE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 561:
#line 4578 "gram1.y"
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
#line 4597 "gram1.y"
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
#line 4613 "gram1.y"
    { PTR_LLND p;

		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"unit";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, p, (yyvsp[(2) - (3)].ll_node), SMNULL);
		  endioctl();
		;}
    break;

  case 564:
#line 4624 "gram1.y"
    { 
		  (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);
		  endioctl();
		 ;}
    break;

  case 565:
#line 4631 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); endioctl();;}
    break;

  case 566:
#line 4633 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST); endioctl();;}
    break;

  case 567:
#line 4637 "gram1.y"
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
#line 4663 "gram1.y"
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
#line 4678 "gram1.y"
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
#line 4693 "gram1.y"
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
#line 4710 "gram1.y"
    { PTR_LLND p;
                  
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 572:
#line 4718 "gram1.y"
    { PTR_LLND p;
		  p = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  p->entry.string_val = (char *)"*";
		  p->type = global_string;
		  (yyval.ll_node) = make_llnd(fi, SPEC_PAIR, (yyvsp[(1) - (2)].ll_node), p, SMNULL);
		;}
    break;

  case 573:
#line 4727 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
		  (yyval.ll_node)->entry.string_val = copys(yytext);
		  (yyval.ll_node)->type = global_string;
	        ;}
    break;

  case 574:
#line 4735 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, READ_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 575:
#line 4740 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi, WRITE_STAT, SMNULL, LLNULL, LLNULL, LLNULL);;}
    break;

  case 576:
#line 4745 "gram1.y"
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
#line 4767 "gram1.y"
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
#line 4783 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);;}
    break;

  case 579:
#line 4785 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST);;}
    break;

  case 580:
#line 4789 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 581:
#line 4791 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
		;}
    break;

  case 582:
#line 4798 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);  (yyval.ll_node)->type = (yyvsp[(1) - (1)].ll_node)->type;;}
    break;

  case 583:
#line 4800 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 584:
#line 4802 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 585:
#line 4806 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 586:
#line 4808 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 587:
#line 4810 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 588:
#line 4812 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 589:
#line 4814 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 590:
#line 4816 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); (yyval.ll_node)->type = (yyvsp[(1) - (3)].ll_node)->type;;}
    break;

  case 591:
#line 4820 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST);
	          (yyval.ll_node)->type = global_complex; ;}
    break;

  case 592:
#line 4823 "gram1.y"
    { (yyval.ll_node) =  set_ll_list((yyvsp[(2) - (3)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (3)].ll_node)->type; ;}
    break;

  case 593:
#line 4826 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 594:
#line 4832 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 595:
#line 4838 "gram1.y"
    {
		  (yyvsp[(4) - (5)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(2) - (5)].ll_node);
		  (yyval.ll_node) =  set_ll_list((yyvsp[(4) - (5)].ll_node), LLNULL, EXPR_LIST);
                  (yyval.ll_node)->type = (yyvsp[(2) - (5)].ll_node)->type; 
		;}
    break;

  case 596:
#line 4846 "gram1.y"
    { inioctl = YES; ;}
    break;

  case 597:
#line 4850 "gram1.y"
    { startioctl();;}
    break;

  case 598:
#line 4858 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 599:
#line 4860 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node); ;}
    break;

  case 600:
#line 4864 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 601:
#line 4866 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 602:
#line 4868 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,(yyvsp[(2) - (3)].token), (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 603:
#line 4873 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,MULT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 604:
#line 4878 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,DIV_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 605:
#line 4883 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,EXP_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 606:
#line 4888 "gram1.y"
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
#line 4897 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,CONCAT_OP, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);
	      set_expr_type((yyval.ll_node));
	    ;}
    break;

  case 608:
#line 4902 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 609:
#line 4907 "gram1.y"
    { comments = cur_comment = CMNULL; ;}
    break;

  case 610:
#line 4909 "gram1.y"
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
#line 4991 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_TEMPLATE_STAT, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL); ;}
    break;

  case 674:
#line 4993 "gram1.y"
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
#line 5004 "gram1.y"
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
#line 5025 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DYNAMIC_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 677:
#line 5029 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 678:
#line 5031 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 679:
#line 5035 "gram1.y"
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
#line 5048 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INHERIT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 681:
#line 5052 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 682:
#line 5054 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 683:
#line 5058 "gram1.y"
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
#line 5069 "gram1.y"
    { PTR_LLND q;
             q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              /* (void)fprintf(stderr,"hpf.gram: shadow\n");*/ 
	     (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_DIR,SMNULL,q,(yyvsp[(4) - (4)].ll_node),LLNULL);
            ;}
    break;

  case 685:
#line 5080 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 686:
#line 5084 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 687:
#line 5086 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 688:
#line 5090 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 689:
#line 5092 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 690:
#line 5094 "gram1.y"
    {
            if(parstate!=INEXEC) 
               err("Illegal shadow width specification", 56);  
            (yyval.ll_node) = make_llnd(fi,SHADOW_NAMES_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL);
          ;}
    break;

  case 691:
#line 5109 "gram1.y"
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
#line 5121 "gram1.y"
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
#line 5141 "gram1.y"
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
#line 5161 "gram1.y"
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
#line 5183 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 696:
#line 5189 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 697:
#line 5198 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
          if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Multiple declaration of identifier  %s ", (yyval.symbol)->ident, 73);
           (yyval.symbol)->attr = (yyval.symbol)->attr | INDIRECT_BIT;
          ;}
    break;

  case 698:
#line 5206 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 699:
#line 5212 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
                ;}
    break;

  case 700:
#line 5220 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REF_GROUP_NAME,global_default,LOCAL);
           if((yyval.symbol)->attr &  INDIRECT_BIT)
                errstr( "Inconsistent declaration of identifier  %s ", (yyval.symbol)->ident, 16);
          ;}
    break;

  case 701:
#line 5227 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 702:
#line 5233 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
	           ;
                ;}
    break;

  case 703:
#line 5242 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), REDUCTION_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 704:
#line 5246 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
	           (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_GROUP_DIR, SMNULL, r, LLNULL, LLNULL);
                ;}
    break;

  case 705:
#line 5252 "gram1.y"
    {  PTR_LLND q,r;
                   q = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(3) - (3)].symbol));
                   r = make_llnd(fi,EXPR_LIST, q, LLNULL, SMNULL);
                   add_to_lowLevelList(r, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);	           
                ;}
    break;

  case 706:
#line 5260 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), CONSISTENT_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 707:
#line 5274 "gram1.y"
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
#line 5287 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 709:
#line 5293 "gram1.y"
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
#line 5309 "gram1.y"
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
#line 5324 "gram1.y"
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
#line 5352 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 713:
#line 5354 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 714:
#line 5358 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 715:
#line 5360 "gram1.y"
    {(yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 716:
#line 5364 "gram1.y"
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
#line 5393 "gram1.y"
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
#line 5416 "gram1.y"
    {  PTR_SYMB s;
          if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
            s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
          if((parstate == INEXEC) && !(s->attr & PROCESSORS_BIT))
               errstr( "'%s' is not processor array ", s->ident, 67);
	  (yyval.symbol) = s;
	;}
    break;

  case 719:
#line 5436 "gram1.y"
    { (yyval.ll_node) = LLNULL;  ;}
    break;

  case 720:
#line 5438 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (2)].ll_node);;}
    break;

  case 721:
#line 5442 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 722:
#line 5463 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 723:
#line 5465 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); ;}
    break;

  case 724:
#line 5468 "gram1.y"
    { opt_kwd_ = YES; ;}
    break;

  case 725:
#line 5477 "gram1.y"
    {  
               (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, SMNULL);
        ;}
    break;

  case 726:
#line 5481 "gram1.y"
    {  err("Distribution format BLOCK(n) is not permitted in FDVM", 55);
          (yyval.ll_node) = make_llnd(fi,BLOCK_OP, (yyvsp[(4) - (5)].ll_node), LLNULL, SMNULL);
          endioctl();
        ;}
    break;

  case 727:
#line 5486 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 728:
#line 5488 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  (yyvsp[(5) - (6)].ll_node),  LLNULL,  (yyvsp[(3) - (6)].symbol)); ;}
    break;

  case 729:
#line 5490 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,BLOCK_OP,  LLNULL, (yyvsp[(3) - (4)].ll_node),  SMNULL); ;}
    break;

  case 730:
#line 5492 "gram1.y"
    { 
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 731:
#line 5498 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, LLNULL, LLNULL, (yyvsp[(3) - (4)].symbol)); ;}
    break;

  case 732:
#line 5500 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_OP, (yyvsp[(3) - (4)].ll_node), LLNULL, SMNULL); ;}
    break;

  case 733:
#line 5504 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
       
	      (yyval.symbol) = s;
	   ;}
    break;

  case 734:
#line 5514 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DERIVED_OP, (yyvsp[(2) - (6)].ll_node), (yyvsp[(6) - (6)].ll_node), SMNULL); ;}
    break;

  case 735:
#line 5518 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 736:
#line 5520 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 737:
#line 5525 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 738:
#line 5527 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 739:
#line 5531 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));
	    ;}
    break;

  case 740:
#line 5535 "gram1.y"
    { 
              (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));
	    ;}
    break;

  case 741:
#line 5541 "gram1.y"
    { 
              if (!((yyval.symbol) = (yyvsp[(1) - (1)].hash_entry)->id_attr))
              {
	         (yyval.symbol) = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL,0,LOCAL);
	         (yyval.symbol)->decl = SOFT;
	      } 
            ;}
    break;

  case 742:
#line 5551 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 743:
#line 5553 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 744:
#line 5557 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 745:
#line 5559 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 746:
#line 5561 "gram1.y"
    {
                      (yyvsp[(2) - (3)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (3)].ll_node); 
                      (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);   
                   ;}
    break;

  case 747:
#line 5568 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
	    (yyval.ll_node) = make_llnd(fi,DUMMY_REF, LLNULL, LLNULL, s);
            /*$$->type = global_int;*/
          ;}
    break;

  case 748:
#line 5585 "gram1.y"
    {  (yyval.ll_node) = LLNULL; ;}
    break;

  case 749:
#line 5587 "gram1.y"
    {  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 750:
#line 5591 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 751:
#line 5593 "gram1.y"
    {  (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 752:
#line 5597 "gram1.y"
    {  if((yyvsp[(1) - (1)].ll_node)->type->variant != T_STRING)
                 errstr( "Illegal type of shadow_name", 627);
               (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); 
            ;}
    break;

  case 753:
#line 5604 "gram1.y"
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
#line 5614 "gram1.y"
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
#line 5643 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 756:
#line 5658 "gram1.y"
    { PTR_LLND q;
              q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
              (yyval.bf_node) = (yyvsp[(4) - (4)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = q;
            ;}
    break;

  case 757:
#line 5665 "gram1.y"
    {
              (yyval.bf_node) = (yyvsp[(3) - (6)].bf_node);
              (yyval.bf_node)->variant = DVM_REALIGN_DIR; 
              (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(6) - (6)].ll_node);
            ;}
    break;

  case 758:
#line 5683 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 759:
#line 5685 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 760:
#line 5689 "gram1.y"
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
#line 5703 "gram1.y"
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
#line 5729 "gram1.y"
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
#line 5742 "gram1.y"
    {
           (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));        
          ;}
    break;

  case 764:
#line 5758 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 765:
#line 5760 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 766:
#line 5763 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 767:
#line 5765 "gram1.y"
    {
                  (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
                  (yyval.ll_node)->entry.string_val = (char *) "*";
                  (yyval.ll_node)->type = global_string;
                 ;}
    break;

  case 768:
#line 5771 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 769:
#line 5775 "gram1.y"
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
#line 5803 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 771:
#line 5805 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 772:
#line 5809 "gram1.y"
    { PTR_SYMB s;
            s = make_scalar((yyvsp[(1) - (1)].hash_entry),TYNULL,LOCAL);
            if(s->type->variant != T_INT || s->attr & PARAMETER_BIT)             
              errstr("The align-dummy %s isn't a scalar integer variable", s->ident, 62); 
	   (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
           (yyval.ll_node)->type = global_int;
         ;}
    break;

  case 773:
#line 5817 "gram1.y"
    {  
          (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
          (yyval.ll_node)->entry.string_val = (char *) "*";
          (yyval.ll_node)->type = global_string;
        ;}
    break;

  case 774:
#line 5823 "gram1.y"
    {   (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 775:
#line 5826 "gram1.y"
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

  case 776:
#line 5884 "gram1.y"
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

  case 777:
#line 5948 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); type_options = type_opt; ;}
    break;

  case 778:
#line 5950 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST); type_options = type_options | type_opt;;}
    break;

  case 779:
#line 5953 "gram1.y"
    { type_opt = TEMPLATE_BIT;
               (yyval.ll_node) = make_llnd(fi,TEMPLATE_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 780:
#line 5957 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 781:
#line 5961 "gram1.y"
    { type_opt = PROCESSORS_BIT;
                (yyval.ll_node) = make_llnd(fi,PROCESSORS_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 782:
#line 5965 "gram1.y"
    { type_opt = DYNAMIC_BIT;
                (yyval.ll_node) = make_llnd(fi,DYNAMIC_OP,LLNULL,LLNULL,SMNULL);
               ;}
    break;

  case 783:
#line 5982 "gram1.y"
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
#line 5994 "gram1.y"
    { type_opt = SHADOW_BIT;
                  (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
                 ;}
    break;

  case 785:
#line 5998 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,(yyvsp[(3) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),SMNULL);
                 ;}
    break;

  case 786:
#line 6002 "gram1.y"
    { type_opt = ALIGN_BIT;
                  (yyval.ll_node) = make_llnd(fi,ALIGN_OP,LLNULL,SMNULL,SMNULL);
                ;}
    break;

  case 787:
#line 6012 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);
                ;}
    break;

  case 788:
#line 6017 "gram1.y"
    { 
                 type_opt = DISTRIBUTE_BIT;
                 (yyval.ll_node) = make_llnd(fi,DISTRIBUTE_OP,LLNULL,LLNULL,SMNULL);
                ;}
    break;

  case 789:
#line 6022 "gram1.y"
    {
                 type_opt = COMMON_BIT;
                 (yyval.ll_node) = make_llnd(fi,COMMON_OP, LLNULL, LLNULL, SMNULL);
                ;}
    break;

  case 790:
#line 6029 "gram1.y"
    { 
	      PTR_LLND  l;
	      l = make_llnd(fi, TYPE_OP, LLNULL, LLNULL, SMNULL);
	      l->type = (yyvsp[(1) - (11)].data_type);
	      (yyval.bf_node) = get_bfnd(fi,DVM_POINTER_DIR, SMNULL, (yyvsp[(11) - (11)].ll_node),(yyvsp[(7) - (11)].ll_node), l);
	    ;}
    break;

  case 791:
#line 6037 "gram1.y"
    {ndim = 0;;}
    break;

  case 792:
#line 6038 "gram1.y"
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
#line 6049 "gram1.y"
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
#line 6060 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 795:
#line 6062 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 796:
#line 6066 "gram1.y"
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
#line 6077 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_HEAP_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 798:
#line 6081 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 799:
#line 6083 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 800:
#line 6087 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | HEAP_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 801:
#line 6098 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 802:
#line 6102 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 803:
#line 6104 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 804:
#line 6108 "gram1.y"
    {  PTR_SYMB s;
	      s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              s->attr = s->attr | CONSISTENT_BIT;
              if((s->attr & PROCESSORS_BIT) ||(s->attr & TASK_BIT)  || (s->attr & TEMPLATE_BIT) || (s->attr & ALIGN_BIT) || (s->attr & DISTRIBUTE_BIT) || (s->attr & INHERIT_BIT) || (s->attr & DYNAMIC_BIT) || (s->attr & SHADOW_BIT) || (s->attr & DVM_POINTER_BIT)) 
                errstr("Inconsistent declaration of identifier  %s", s->ident, 16); 
      
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, LLNULL, LLNULL, s);
	   ;}
    break;

  case 805:
#line 6120 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 806:
#line 6122 "gram1.y"
    { PTR_LLND p;
              p = make_llnd(fi,COMM_LIST, LLNULL, LLNULL, SMNULL);              
              (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCID_DIR, SMNULL, (yyvsp[(8) - (8)].ll_node), p, LLNULL);
            ;}
    break;

  case 807:
#line 6129 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 808:
#line 6131 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 809:
#line 6135 "gram1.y"
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
#line 6151 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_NEW_VALUE_DIR,SMNULL, LLNULL, LLNULL,LLNULL);;}
    break;

  case 811:
#line 6161 "gram1.y"
    {  if((yyvsp[(6) - (7)].ll_node) &&  (yyvsp[(6) - (7)].ll_node)->entry.Template.symbol->attr & TASK_BIT)
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_TASK_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                    else
                        (yyval.bf_node) = get_bfnd(fi,DVM_PARALLEL_ON_DIR,SMNULL,(yyvsp[(6) - (7)].ll_node),(yyvsp[(7) - (7)].ll_node),(yyvsp[(4) - (7)].ll_node));
                 ;}
    break;

  case 812:
#line 6170 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 813:
#line 6172 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 815:
#line 6179 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 816:
#line 6182 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 817:
#line 6187 "gram1.y"
    {
          if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
           errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66);
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
         ;}
    break;

  case 818:
#line 6197 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 819:
#line 6199 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 820:
#line 6203 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 821:
#line 6205 "gram1.y"
    {
             (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
             (yyval.ll_node)->entry.string_val = (char *) "*";
             (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 822:
#line 6213 "gram1.y"
    {  (yyval.ll_node) = LLNULL;;}
    break;

  case 823:
#line 6215 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 824:
#line 6219 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 825:
#line 6221 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (2)].ll_node),(yyvsp[(2) - (2)].ll_node),EXPR_LIST); ;}
    break;

  case 836:
#line 6238 "gram1.y"
    { if((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT)
                            errstr("'%s' is not remote group name", (yyvsp[(5) - (8)].symbol)->ident, 68);
                          (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 837:
#line 6243 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 838:
#line 6247 "gram1.y"
    {
                          (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                        ;}
    break;

  case 839:
#line 6251 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,CONSISTENT_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 840:
#line 6255 "gram1.y"
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
#line 6268 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 842:
#line 6272 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,NEW_SPEC_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 843:
#line 6276 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 844:
#line 6280 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_BLOCK_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 845:
#line 6283 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 846:
#line 6285 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 847:
#line 6287 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(3) - (5)].ll_node),EXPR_LIST); (yyval.ll_node) = set_ll_list((yyval.ll_node),(yyvsp[(5) - (5)].ll_node),EXPR_LIST);;}
    break;

  case 848:
#line 6291 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 849:
#line 6293 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 850:
#line 6297 "gram1.y"
    { if(!((yyvsp[(5) - (8)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(5) - (8)].symbol)->ident, 313);
                      (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(7) - (8)].ll_node),LLNULL,(yyvsp[(5) - (8)].symbol));
                    ;}
    break;

  case 851:
#line 6302 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,INDIRECT_ACCESS_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 852:
#line 6306 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,STAGE_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 853:
#line 6310 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 854:
#line 6312 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL);;}
    break;

  case 855:
#line 6316 "gram1.y"
    {  if((yyvsp[(3) - (5)].ll_node))
                     (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),SMNULL);
                   else
                     (yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
                ;}
    break;

  case 856:
#line 6324 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "in";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 857:
#line 6330 "gram1.y"
    {
	      (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "out";
              (yyval.ll_node)->type = global_string;
            ;}
    break;

  case 858:
#line 6336 "gram1.y"
    {  (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 859:
#line 6340 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 860:
#line 6342 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 861:
#line 6346 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 862:
#line 6348 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                    (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);  
                  ;}
    break;

  case 863:
#line 6352 "gram1.y"
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
#line 6364 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 865:
#line 6366 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 866:
#line 6370 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, (yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), SMNULL);;}
    break;

  case 867:
#line 6374 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 868:
#line 6376 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 869:
#line 6380 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (5)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 870:
#line 6382 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,(yyvsp[(3) - (3)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 871:
#line 6384 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),make_llnd(fi,DDOT,LLNULL,(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 872:
#line 6386 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 873:
#line 6388 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 874:
#line 6390 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,(yyvsp[(1) - (1)].ll_node),LLNULL,SMNULL),SMNULL); ;}
    break;

  case 875:
#line 6392 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT,LLNULL,make_llnd(fi,DDOT,LLNULL,(yyvsp[(1) - (1)].ll_node),SMNULL),SMNULL); ;}
    break;

  case 876:
#line 6396 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 877:
#line 6400 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 878:
#line 6404 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(3) - (3)].ll_node);;}
    break;

  case 879:
#line 6408 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (3)].ll_node);;}
    break;

  case 880:
#line 6412 "gram1.y"
    {PTR_LLND q;
                /* q = set_ll_list($9,$6,EXPR_LIST); */
                 q = set_ll_list((yyvsp[(6) - (10)].ll_node),LLNULL,EXPR_LIST); /*podd 11.10.01*/
                 q = add_to_lowLevelList((yyvsp[(9) - (10)].ll_node),q);        /*podd 11.10.01*/
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 881:
#line 6419 "gram1.y"
    {PTR_LLND q;
                 q = set_ll_list((yyvsp[(6) - (8)].ll_node),LLNULL,EXPR_LIST);
                 (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,q,LLNULL,SMNULL);
                ;}
    break;

  case 882:
#line 6425 "gram1.y"
    {  (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(9) - (10)].ll_node),LLNULL,(yyvsp[(6) - (10)].symbol)); ;}
    break;

  case 883:
#line 6429 "gram1.y"
    { opt_kwd_r = YES; ;}
    break;

  case 884:
#line 6432 "gram1.y"
    { opt_kwd_r = NO; ;}
    break;

  case 885:
#line 6436 "gram1.y"
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
#line 6449 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 887:
#line 6451 "gram1.y"
    {(yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),EXPR_LIST);;}
    break;

  case 888:
#line 6455 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (4)].ll_node),(yyvsp[(3) - (4)].ll_node),SMNULL);;}
    break;

  case 889:
#line 6457 "gram1.y"
    {(yyvsp[(3) - (6)].ll_node) = set_ll_list((yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),EXPR_LIST);
            (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (6)].ll_node),(yyvsp[(3) - (6)].ll_node),SMNULL);;}
    break;

  case 890:
#line 6462 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "sum";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 891:
#line 6468 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "product";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 892:
#line 6474 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 893:
#line 6480 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 894:
#line 6486 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "or";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 895:
#line 6492 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "and";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 896:
#line 6498 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "eqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 897:
#line 6504 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "neqv";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 898:
#line 6510 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 899:
#line 6519 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "maxloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 900:
#line 6525 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "minloc";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 901:
#line 6542 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_RENEW_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 902:
#line 6550 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_START_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 903:
#line 6558 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_WAIT_OP,LLNULL,LLNULL,(yyvsp[(4) - (4)].symbol));;}
    break;

  case 904:
#line 6560 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 905:
#line 6562 "gram1.y"
    {  (yyvsp[(5) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(7) - (9)].ll_node); (yyval.ll_node) = make_llnd(fi,SHADOW_COMP_OP,(yyvsp[(5) - (9)].ll_node),LLNULL,SMNULL);;}
    break;

  case 906:
#line 6566 "gram1.y"
    {(yyval.symbol) = make_local_entity((yyvsp[(1) - (1)].hash_entry), SHADOW_GROUP_NAME,global_default,LOCAL);;}
    break;

  case 907:
#line 6570 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);;}
    break;

  case 908:
#line 6572 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);;}
    break;

  case 909:
#line 6576 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 910:
#line 6578 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (5)].ll_node),p,SMNULL);
         ;}
    break;

  case 911:
#line 6586 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (5)].ll_node);
          (yyval.ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);  
        ;}
    break;

  case 912:
#line 6590 "gram1.y"
    { PTR_LLND p;
          p = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
          p->entry.string_val = (char *) "corner";
          p->type = global_string;
          (yyvsp[(1) - (9)].ll_node)-> entry.Template.ll_ptr1 = (yyvsp[(4) - (9)].ll_node);  
          (yyval.ll_node) = make_llnd(fi,ARRAY_OP,(yyvsp[(1) - (9)].ll_node),p,SMNULL);
       ;}
    break;

  case 913:
#line 6601 "gram1.y"
    { optcorner = YES; ;}
    break;

  case 914:
#line 6605 "gram1.y"
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
#line 6623 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 916:
#line 6625 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 917:
#line 6629 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 918:
#line 6631 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 919:
#line 6635 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 920:
#line 6637 "gram1.y"
    {errstr("Missing DVM directive prefix", 49);;}
    break;

  case 921:
#line 6641 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_GROUP_DIR,(yyvsp[(3) - (6)].symbol),(yyvsp[(5) - (6)].ll_node),LLNULL,LLNULL);;}
    break;

  case 922:
#line 6645 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 923:
#line 6649 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REDUCTION_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 924:
#line 6658 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_START_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 925:
#line 6662 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CONSISTENT_WAIT_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 926:
#line 6666 "gram1.y"
    { if(((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                errstr("'%s' is not remote group name", (yyvsp[(4) - (7)].symbol)->ident, 68);
           (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
         ;}
    break;

  case 927:
#line 6671 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_REMOTE_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 928:
#line 6675 "gram1.y"
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
#line 6687 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 930:
#line 6689 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 931:
#line 6693 "gram1.y"
    {
              (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
              (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
            ;}
    break;

  case 932:
#line 6698 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 933:
#line 6702 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 934:
#line 6704 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 935:
#line 6708 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 936:
#line 6710 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 937:
#line 6714 "gram1.y"
    {  PTR_LLND q;
             q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
             (yyval.bf_node) = get_bfnd(fi,DVM_TASK_DIR,SMNULL,q,LLNULL,LLNULL);
          ;}
    break;

  case 938:
#line 6719 "gram1.y"
    {   PTR_LLND q;
              q = make_llnd(fi,EXPR_LIST, (yyvsp[(3) - (3)].ll_node), LLNULL, SMNULL);
	      add_to_lowLevelList(q, (yyvsp[(1) - (3)].bf_node)->entry.Template.ll_ptr1);
          ;}
    break;

  case 939:
#line 6726 "gram1.y"
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
#line 6749 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 941:
#line 6751 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 942:
#line 6753 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (4)].symbol),LLNULL,(yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 943:
#line 6755 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(4) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 944:
#line 6757 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_TASK_REGION_DIR,(yyvsp[(3) - (5)].symbol),(yyvsp[(5) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),LLNULL);;}
    break;

  case 945:
#line 6761 "gram1.y"
    { PTR_SYMB s;
              if((s=(yyvsp[(1) - (1)].hash_entry)->id_attr) == SMNULL)
                s = make_array((yyvsp[(1) - (1)].hash_entry), TYNULL, LLNULL, 0, LOCAL);
              
              if(!(s->attr & TASK_BIT))
                 errstr("'%s' is not task array", s->ident, 77);
              (yyval.symbol) = s;
              ;}
    break;

  case 946:
#line 6772 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_END_TASK_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 947:
#line 6776 "gram1.y"
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
#line 6791 "gram1.y"
    {  PTR_LLND q; 
              q =  set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	      (yyval.ll_node) = make_llnd(fi,ARRAY_REF, q, LLNULL, (yyvsp[(1) - (4)].symbol));
	   ;}
    break;

  case 949:
#line 6798 "gram1.y"
    {              
         (yyval.bf_node) = get_bfnd(fi,DVM_ON_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),LLNULL);
    ;}
    break;

  case 950:
#line 6804 "gram1.y"
    {(yyval.ll_node) = LLNULL;;}
    break;

  case 951:
#line 6806 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 952:
#line 6810 "gram1.y"
    {(yyval.bf_node) = get_bfnd(fi,DVM_END_ON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 953:
#line 6814 "gram1.y"
    { PTR_LLND q;
        /* if(!($6->attr & PROCESSORS_BIT))
           errstr("'%s' is not processor array", $6->ident, 67);
         */
        q = make_llnd(fi,ARRAY_REF, (yyvsp[(7) - (7)].ll_node), LLNULL, (yyvsp[(6) - (7)].symbol));
        (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (7)].ll_node),q,LLNULL);
      ;}
    break;

  case 954:
#line 6822 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_MAP_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),LLNULL,(yyvsp[(6) - (6)].ll_node)); ;}
    break;

  case 955:
#line 6826 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_PREFETCH_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 956:
#line 6830 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_RESET_DIR,(yyvsp[(3) - (3)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 957:
#line 6838 "gram1.y"
    { if(!((yyvsp[(4) - (7)].symbol)->attr & INDIRECT_BIT))
                         errstr("'%s' is not indirect group name", (yyvsp[(4) - (7)].symbol)->ident, 313);
                      (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,(yyvsp[(4) - (7)].symbol),(yyvsp[(6) - (7)].ll_node),LLNULL,LLNULL);
                    ;}
    break;

  case 958:
#line 6843 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INDIRECT_ACCESS_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 959:
#line 6857 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 960:
#line 6859 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 961:
#line 6863 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 962:
#line 6865 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node); (yyval.ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);;}
    break;

  case 963:
#line 6874 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 964:
#line 6876 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);;}
    break;

  case 965:
#line 6878 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, LLNULL, (yyvsp[(3) - (3)].ll_node), LLNULL);;}
    break;

  case 966:
#line 6880 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,HPF_INDEPENDENT_DIR,SMNULL, (yyvsp[(3) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node),LLNULL);;}
    break;

  case 967:
#line 6916 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(5) - (6)].ll_node),LLNULL,SMNULL);;}
    break;

  case 968:
#line 6920 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCHRONOUS_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 969:
#line 6924 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDASYNCHRONOUS_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 970:
#line 6928 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ASYNCWAIT_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 971:
#line 6932 "gram1.y"
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
#line 6944 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,VAR_REF, LLNULL, LLNULL, (yyvsp[(1) - (1)].symbol));;}
    break;

  case 973:
#line 6946 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ARRAY_REF, (yyvsp[(3) - (4)].ll_node), LLNULL, (yyvsp[(1) - (4)].symbol));;}
    break;

  case 974:
#line 6950 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_F90_DIR,SMNULL,(yyvsp[(3) - (5)].ll_node),(yyvsp[(5) - (5)].ll_node),LLNULL);;}
    break;

  case 975:
#line 6953 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 976:
#line 6955 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_DEBUG_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),(yyvsp[(5) - (6)].ll_node),LLNULL);;}
    break;

  case 977:
#line 6959 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(2) - (2)].ll_node), LLNULL, EXPR_LIST);
              endioctl();
            ;}
    break;

  case 978:
#line 6964 "gram1.y"
    { 
              (yyval.ll_node) = set_ll_list((yyvsp[(1) - (4)].ll_node), (yyvsp[(4) - (4)].ll_node), EXPR_LIST);
              endioctl();
            ;}
    break;

  case 979:
#line 6971 "gram1.y"
    { (yyval.ll_node)  = make_llnd(fi, KEYWORD_ARG, (yyvsp[(1) - (2)].ll_node), (yyvsp[(2) - (2)].ll_node), SMNULL); ;}
    break;

  case 980:
#line 6974 "gram1.y"
    {
	         (yyval.ll_node) = make_llnd(fi,INT_VAL, LLNULL, LLNULL, SMNULL);
	         (yyval.ll_node)->entry.ival = atoi(yytext);
	         (yyval.ll_node)->type = global_int;
	        ;}
    break;

  case 981:
#line 6982 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDDEBUG_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 982:
#line 6986 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 983:
#line 6990 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 984:
#line 6993 "gram1.y"
    { if((yyvsp[(1) - (1)].ll_node)->type->variant != T_INT)             
                    err("Illegal interval number", 78);
                  (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                 ;}
    break;

  case 985:
#line 7001 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_EXIT_INTERVAL_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 986:
#line 7005 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_ENDINTERVAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 987:
#line 7009 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEON_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 988:
#line 7013 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TRACEOFF_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 989:
#line 7017 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 990:
#line 7021 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CHECK_DIR,SMNULL,(yyvsp[(9) - (9)].ll_node),(yyvsp[(5) - (9)].ll_node),LLNULL); ;}
    break;

  case 991:
#line 7025 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_IO_MODE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 992:
#line 7028 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 993:
#line 7030 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 994:
#line 7034 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 995:
#line 7036 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 996:
#line 7038 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,PARALLEL_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 997:
#line 7042 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_SHADOW_ADD_DIR,SMNULL,(yyvsp[(4) - (9)].ll_node),(yyvsp[(6) - (9)].ll_node),(yyvsp[(9) - (9)].ll_node)); ;}
    break;

  case 998:
#line 7046 "gram1.y"
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
#line 7058 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1000:
#line 7060 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1001:
#line 7064 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1002:
#line 7066 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1003:
#line 7070 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1004:
#line 7072 "gram1.y"
    { (yyval.ll_node) = LLNULL; opt_kwd_ = NO;;}
    break;

  case 1005:
#line 7076 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_LOCALIZE_DIR,SMNULL,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),LLNULL); ;}
    break;

  case 1006:
#line 7080 "gram1.y"
    {
                 if((yyvsp[(1) - (1)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (1)].ll_node)->entry.Template.symbol->ident, 66); 
                 (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);
                ;}
    break;

  case 1007:
#line 7086 "gram1.y"
    {
                 if((yyvsp[(1) - (4)].ll_node)->type->variant != T_ARRAY) 
                    errstr("'%s' isn't array", (yyvsp[(1) - (4)].ll_node)->entry.Template.symbol->ident, 66); 
                                 
                 (yyvsp[(1) - (4)].ll_node)->entry.Template.ll_ptr1 = (yyvsp[(3) - (4)].ll_node);
                 (yyval.ll_node) = (yyvsp[(1) - (4)].ll_node);
                 (yyval.ll_node)->type = (yyvsp[(1) - (4)].ll_node)->type->entry.ar_decl.base_type;
                ;}
    break;

  case 1008:
#line 7098 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1009:
#line 7100 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1010:
#line 7104 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1011:
#line 7106 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,DDOT, LLNULL, LLNULL, SMNULL);;}
    break;

  case 1012:
#line 7110 "gram1.y"
    { 
            (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL, LLNULL, LLNULL, SMNULL);
            (yyval.ll_node)->entry.string_val = (char *) "*";
            (yyval.ll_node)->type = global_string;
          ;}
    break;

  case 1013:
#line 7118 "gram1.y"
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
#line 7129 "gram1.y"
    { (yyval.ll_node) = LLNULL; ;}
    break;

  case 1015:
#line 7131 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi, PARALLEL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1016:
#line 7133 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP, LLNULL, LLNULL, SMNULL); ;}
    break;

  case 1017:
#line 7137 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_LOAD_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1018:
#line 7141 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1019:
#line 7143 "gram1.y"
    {
                PTR_LLND q;
                q = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);
                (yyval.bf_node) = get_bfnd(fi,DVM_CP_SAVE_DIR,SMNULL,(yyvsp[(3) - (6)].ll_node),q,LLNULL);
              ;}
    break;

  case 1020:
#line 7151 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_CP_WAIT_DIR,SMNULL,(yyvsp[(3) - (9)].ll_node),(yyvsp[(8) - (9)].ll_node),LLNULL); ;}
    break;

  case 1021:
#line 7155 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,DVM_TEMPLATE_CREATE_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL); ;}
    break;

  case 1022:
#line 7158 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node), LLNULL, EXPR_LIST); ;}
    break;

  case 1023:
#line 7160 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node), (yyvsp[(3) - (3)].ll_node), EXPR_LIST); ;}
    break;

  case 1051:
#line 7193 "gram1.y"
    {
          (yyval.bf_node) = get_bfnd(fi,OMP_ONETHREAD_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1052:
#line 7199 "gram1.y"
    {
  	   (yyval.bf_node) = make_endparallel();
	;}
    break;

  case 1053:
#line 7205 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1054:
#line 7211 "gram1.y"
    {
  	   (yyval.bf_node) = make_parallel();
	   opt_kwd_ = NO;
	;}
    break;

  case 1055:
#line 7217 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1056:
#line 7221 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);	
	;}
    break;

  case 1066:
#line 7238 "gram1.y"
    {
		(yyval.ll_node) = (yyvsp[(4) - (5)].ll_node);
        ;}
    break;

  case 1067:
#line 7243 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_PRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1068:
#line 7248 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_FIRSTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1069:
#line 7254 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_LASTPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1070:
#line 7260 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYIN,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1071:
#line 7266 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SHARED,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1072:
#line 7271 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_DEFAULT,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1073:
#line 7277 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "private";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1074:
#line 7283 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "shared";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1075:
#line 7289 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "none";
		(yyval.ll_node)->type = global_string;
	;}
    break;

  case 1076:
#line 7296 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_IF,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1077:
#line 7302 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NUM_THREADS,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1078:
#line 7308 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
		(yyval.ll_node) = make_llnd(fi,OMP_REDUCTION,q,LLNULL,SMNULL);
	;}
    break;

  case 1079:
#line 7315 "gram1.y"
    {(yyval.ll_node) = make_llnd(fi,DDOT,(yyvsp[(2) - (4)].ll_node),(yyvsp[(4) - (4)].ll_node),SMNULL);;}
    break;

  case 1081:
#line 7321 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "+";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1082:
#line 7327 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "-";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1083:
#line 7334 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "*";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1084:
#line 7340 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "/";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1085:
#line 7346 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "min";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1086:
#line 7352 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "max";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1087:
#line 7358 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".or.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1088:
#line 7364 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".and.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1089:
#line 7370 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".eqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1090:
#line 7376 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) ".neqv.";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1091:
#line 7382 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "iand";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1092:
#line 7388 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ieor";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1093:
#line 7394 "gram1.y"
    {
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "ior";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1094:
#line 7400 "gram1.y"
    { err("Illegal reduction operation name", 70);
               errcnt--;
              (yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
              (yyval.ll_node)->entry.string_val = (char *) "unknown";
              (yyval.ll_node)->type = global_string;
             ;}
    break;

  case 1095:
#line 7410 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1096:
#line 7415 "gram1.y"
    {
  	   (yyval.bf_node) = make_sections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1097:
#line 7421 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1098:
#line 7425 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1103:
#line 7437 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endsections();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
                opt_kwd_ = NO;
	;}
    break;

  case 1104:
#line 7445 "gram1.y"
    {
   	        (yyval.bf_node) = make_endsections();
	        opt_kwd_ = NO; 
	;}
    break;

  case 1105:
#line 7451 "gram1.y"
    {
           (yyval.bf_node) = make_ompsection();
	;}
    break;

  case 1106:
#line 7457 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1107:
#line 7462 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1108:
#line 7468 "gram1.y"
    {
		PTR_LLND q;
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
	        (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,q,LLNULL,LLNULL);
      	        opt_kwd_ = NO;
	;}
    break;

  case 1109:
#line 7475 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1110:
#line 7481 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1111:
#line 7485 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1118:
#line 7499 "gram1.y"
    {
		/*$$ = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		$$->entry.string_val = (char *) "ORDERED";
		$$->type = global_string;*/
                (yyval.ll_node) = make_llnd(fi,OMP_ORDERED,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1119:
#line 7508 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (7)].ll_node),(yyvsp[(6) - (7)].ll_node),SMNULL);
	;}
    break;

  case 1120:
#line 7512 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_SCHEDULE,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1121:
#line 7518 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "STATIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1122:
#line 7525 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "DYNAMIC";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1123:
#line 7532 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "GUIDED";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1124:
#line 7539 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,KEYWORD_VAL,LLNULL,LLNULL,SMNULL);
		(yyval.ll_node)->entry.string_val = (char *) "RUNTIME";
		(yyval.ll_node)->type = global_string;
		
	;}
    break;

  case 1125:
#line 7548 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1126:
#line 7554 "gram1.y"
    {
  	   (yyval.bf_node) = make_single();
	   opt_kwd_ = NO;
	;}
    break;

  case 1127:
#line 7560 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1128:
#line 7564 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1131:
#line 7574 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1132:
#line 7580 "gram1.y"
    {
  	   (yyval.bf_node) = make_endsingle();
	   opt_kwd_ = NO;
	;}
    break;

  case 1133:
#line 7586 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1134:
#line 7590 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1137:
#line 7601 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_COPYPRIVATE,(yyvsp[(2) - (2)].ll_node),LLNULL,SMNULL);
	;}
    break;

  case 1138:
#line 7607 "gram1.y"
    {
		(yyval.ll_node) = make_llnd(fi,OMP_NOWAIT,LLNULL,LLNULL,SMNULL);
	;}
    break;

  case 1139:
#line 7613 "gram1.y"
    {
           (yyval.bf_node) = make_workshare();
	;}
    break;

  case 1140:
#line 7618 "gram1.y"
    {
		PTR_LLND q;
   	        (yyval.bf_node) = make_endworkshare();
		q = set_ll_list((yyvsp[(4) - (4)].ll_node),LLNULL,EXPR_LIST);
                (yyval.bf_node)->entry.Template.ll_ptr1 = q;
  	        opt_kwd_ = NO;
	;}
    break;

  case 1141:
#line 7626 "gram1.y"
    {
   	        (yyval.bf_node) = make_endworkshare();
                opt_kwd_ = NO;
	;}
    break;

  case 1142:
#line 7632 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,(yyvsp[(4) - (4)].ll_node),LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1143:
#line 7637 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1144:
#line 7644 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(3) - (4)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1145:
#line 7648 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (5)].ll_node),(yyvsp[(4) - (5)].ll_node),EXPR_LIST);
	;}
    break;

  case 1157:
#line 7668 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_END_PARALLEL_DO_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1158:
#line 7673 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections((yyvsp[(4) - (4)].ll_node));
	   opt_kwd_ = NO;
	;}
    break;

  case 1159:
#line 7678 "gram1.y"
    {
           (yyval.bf_node) = make_parallelsections(LLNULL);
	   opt_kwd_ = NO;
	;}
    break;

  case 1160:
#line 7685 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelsections();
	;}
    break;

  case 1161:
#line 7690 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (4)].ll_node);
	   opt_kwd_ = NO;
	;}
    break;

  case 1162:
#line 7696 "gram1.y"
    {
           (yyval.bf_node) = make_parallelworkshare();
	   opt_kwd_ = NO;
	;}
    break;

  case 1163:
#line 7702 "gram1.y"
    {
           (yyval.bf_node) = make_endparallelworkshare();
	;}
    break;

  case 1164:
#line 7707 "gram1.y"
    { 
	   (yyval.bf_node) = get_bfnd(fi,OMP_THREADPRIVATE_DIR, SMNULL, (yyvsp[(3) - (3)].ll_node), LLNULL, LLNULL);
	;}
    break;

  case 1165:
#line 7712 "gram1.y"
    {
  	   (yyval.bf_node) = make_master();
	;}
    break;

  case 1166:
#line 7717 "gram1.y"
    {
  	   (yyval.bf_node) = make_endmaster();
	;}
    break;

  case 1167:
#line 7721 "gram1.y"
    {
  	   (yyval.bf_node) = make_ordered();
	;}
    break;

  case 1168:
#line 7726 "gram1.y"
    {
  	   (yyval.bf_node) = make_endordered();
	;}
    break;

  case 1169:
#line 7731 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_BARRIER_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1170:
#line 7735 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_ATOMIC_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1171:
#line 7740 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);
	;}
    break;

  case 1172:
#line 7744 "gram1.y"
    {
           (yyval.bf_node) = get_bfnd(fi,OMP_FLUSH_DIR,SMNULL,LLNULL,LLNULL,LLNULL);
	;}
    break;

  case 1173:
#line 7750 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1174:
#line 7755 "gram1.y"
    {
  	   (yyval.bf_node) = make_critical();
	;}
    break;

  case 1175:
#line 7761 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
           (yyval.bf_node)->entry.Template.ll_ptr1 = (yyvsp[(4) - (5)].ll_node);
	;}
    break;

  case 1176:
#line 7766 "gram1.y"
    {
  	   (yyval.bf_node) = make_endcritical();
	;}
    break;

  case 1177:
#line 7772 "gram1.y"
    { 
		PTR_SYMB s;
		PTR_LLND l;
		s = make_common((yyvsp[(2) - (5)].hash_entry)); 
		l = make_llnd(fi,VAR_REF, LLNULL, LLNULL, s);
		(yyval.ll_node) = make_llnd(fi,OMP_THREADPRIVATE, l, LLNULL, SMNULL);
	;}
    break;

  case 1178:
#line 7782 "gram1.y"
    {
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1179:
#line 7786 "gram1.y"
    {	
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST);
	;}
    break;

  case 1180:
#line 7790 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1181:
#line 7794 "gram1.y"
    { 
		(yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST);
	;}
    break;

  case 1182:
#line 7799 "gram1.y"
    {
		operator_slash = 1;
	;}
    break;

  case 1183:
#line 7802 "gram1.y"
    {
		operator_slash = 0;
	;}
    break;

  case 1190:
#line 7815 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_REGION_DIR,SMNULL,(yyvsp[(3) - (3)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1191:
#line 7819 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1192:
#line 7823 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1193:
#line 7825 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1194:
#line 7827 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_GET_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1195:
#line 7831 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,(yyvsp[(4) - (5)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1196:
#line 7833 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1197:
#line 7835 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_ACTUAL_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1198:
#line 7839 "gram1.y"
    { (yyval.ll_node) = LLNULL;;}
    break;

  case 1199:
#line 7841 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node); ;}
    break;

  case 1200:
#line 7845 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1201:
#line 7847 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1202:
#line 7851 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1203:
#line 7854 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1204:
#line 7857 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(2) - (2)].ll_node);;}
    break;

  case 1205:
#line 7862 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INOUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1206:
#line 7864 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_IN_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1207:
#line 7866 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_OUT_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1208:
#line 7868 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_LOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1209:
#line 7870 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_INLOCAL_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1210:
#line 7874 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_TARGETS_OP,(yyvsp[(3) - (4)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1211:
#line 7878 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_ASYNC_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1212:
#line 7883 "gram1.y"
    { (yyval.ll_node) = (yyvsp[(1) - (1)].ll_node);;}
    break;

  case 1213:
#line 7887 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1214:
#line 7889 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1215:
#line 7893 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_HOST_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1216:
#line 7895 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_CUDA_OP, LLNULL,LLNULL,SMNULL);;}
    break;

  case 1217:
#line 7899 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_REGION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1218:
#line 7903 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,ACC_END_CHECKSECTION_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1224:
#line 7914 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_ANALYSIS_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1225:
#line 7918 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1226:
#line 7922 "gram1.y"
    {  (yyval.bf_node) = get_bfnd(fi,SPF_TRANSFORM_DIR,SMNULL,(yyvsp[(3) - (4)].ll_node),LLNULL,LLNULL);;}
    break;

  case 1227:
#line 7926 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_PARALLEL_REG_DIR,(yyvsp[(2) - (2)].symbol),LLNULL,LLNULL,LLNULL);;}
    break;

  case 1228:
#line 7930 "gram1.y"
    { (yyval.bf_node) = get_bfnd(fi,SPF_END_PARALLEL_REG_DIR,SMNULL,LLNULL,LLNULL,LLNULL);;}
    break;

  case 1229:
#line 7934 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1230:
#line 7936 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1233:
#line 7944 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REDUCTION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL); ;}
    break;

  case 1234:
#line 7948 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACC_PRIVATE_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1235:
#line 7952 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1236:
#line 7954 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1240:
#line 7964 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SHADOW_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1241:
#line 7968 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,ACROSS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1242:
#line 7972 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,REMOTE_ACCESS_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1243:
#line 7976 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (1)].ll_node),LLNULL,EXPR_LIST); ;}
    break;

  case 1244:
#line 7978 "gram1.y"
    { (yyval.ll_node) = set_ll_list((yyvsp[(1) - (3)].ll_node),(yyvsp[(3) - (3)].ll_node),EXPR_LIST); ;}
    break;

  case 1245:
#line 7982 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_NOINLINE_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1246:
#line 7984 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_FISSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1247:
#line 7986 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,LLNULL,LLNULL,SMNULL);;}
    break;

  case 1248:
#line 7988 "gram1.y"
    { (yyval.ll_node) = make_llnd(fi,SPF_PRIVATES_EXPANSION_OP,(yyvsp[(4) - (5)].ll_node),LLNULL,SMNULL);;}
    break;

  case 1249:
#line 7991 "gram1.y"
    { (yyval.symbol) = make_parallel_region((yyvsp[(1) - (1)].hash_entry));;}
    break;


/* Line 1267 of yacc.c.  */
#line 13736 "gram1.tab.c"
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



